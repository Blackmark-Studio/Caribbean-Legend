// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("¡Un espía! ¡Entrega tu arma y sígueme!","¡Un agente enemigo! Captura "+GetSexPhrase("él","ella")+"¡!");
				link.l1 = RandPhraseSimple("¡Cállate, marica!","¡Que te jodan!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("¿Quién eres y qué haces aquí?","¡Quieto! ¿Quién eres? ¿Por qué motivo intentas entrar al fuerte?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Oficial, tengo "+GetRusNameNationLicence(sti(npchar.nation))+", así que estoy aquí por motivos legales. Aquí, por favor echa un vistazo...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("¿Un pirata en el fuerte? ¡Captúren"+GetSexPhrase("lo","la")+"!","¡Ese es un pirata, olfateando algo en nuestro fuerte! ¡A la cárcel!");
							link.l1 = RandPhraseSimple("Sí, soy un pirata, ¿y qué?","Heh, atrápame si puedes...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "¿No ves la bandera de "+NationNameGenitive(sti(pchar.nation))+"¿en el mástil de mi barco?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "Eché el ancla cerca de "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" bajo la bandera de"+NationNameGenitive(sti(pchar.nation))+"¿Necesitas algo más?";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							notification("Trustworthy", "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Skill Check Failed", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "¡Oh, capitán, hemos pasado tan buenos momentos contigo en el mar! ¡Cuántos barcos hemos hundido juntos bajo tu mando! Y aquí...";
									link.l1 = "Y aquí, mi amigo, puedes deleitar tus ojos con encantadoras damas, no las verás en el mar.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "¡Capitán!, ¿qué hemos hecho para merecer esto? ¡No somos ratas de tierra! ¿Verdad?";
									link.l1 = "¡Silencio, marinero! Tu puesto es muy importante y honorífico, así que deja de quejarte.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "¿Qué está pasando en el mar, capitán? ¿Lo volveremos a ver alguna vez?";
									link.l1 = "¡Pero por supuesto, marinero! Una vez que te liberes del deber, puedes dirigirte al muelle y disfrutar del mar tanto como quieras.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Quiero quejarme, capitán: a todos nos falta el mar. ¡Estamos totalmente hartos de este deber terrestre!";
									link.l1 = "¡Me canso de estos quejidos! ¡También tienes suficiente ron aquí! Sirve donde el capitán te ha colocado, o alguien será colgado como ejemplo para los demás.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Te lo diré en confianza, capitán, el nuevo gobernador es un sobornador y malversador. Pero eso realmente no es asunto mío...";
									link.l1 = "Exactamente, corsario. Tu trabajo es estar en tu puesto y mantener el orden. Y colgar al gobernador en el verga es mi asunto. ¡Buen trabajo!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "¡Gracias por no olvidarte de nosotros, capitán! ¡Te seguiríamos a través del fuego y el agua!";
									link.l1 = "Conozco tu tipo, ¡malhechores! Todo lo que realmente amas es el oro. Hay una fiesta en la taberna esta noche, las bebidas corren por mi cuenta. No olvides aparecer.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "¡Je, capitán! Solo piénsalo, ¿puede un corsario ser realmente un guardián del orden? ¡Ha pasado tanto tiempo desde que estuvimos en el verdadero negocio!";
									link.l1 = "¡No hay tiempo para relajarse, corsario! Las armadas enemigas están peinando las aguas cerca de nuestras islas, y debemos estar listos para un baño de sangre en cualquier momento.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Capitán, ¿escuché que la Corona ha enviado otra escuadra hacia nosotros?";
									link.l1 = "Por supuesto, corsario. Mientras vivamos, no habrá paz para nosotros. ¡Y hasta en el Infierno estaremos luchando contra demonios!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "¡Yo-ho-ho! Maldición, eso fue un licor realmente fuerte ayer, capitán! Es una lástima que no estuvieras allí.";
									link.l1 = "No es gran cosa, lo compensaré. Y no os envidio, chicos.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Te lo diré en confianza, capitán, porque siempre nos has tratado bien, ayer pasamos un buen rato con una chica realmente agradable...";
									link.l1 = "Je, corsario, ¡una soga es algo que realmente necesitas!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "¡Capitán! Por favor, líbrame de este maldito deber. Simplemente no puedo desempeñar el papel de un guardián del orden más.";
									link.l1 = "El turno de noche en un barco tampoco es fácil. Amigo, el deber es el deber, sea lo que sea y esté donde esté.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("¡Hay un asunto importante!","Tengo un asunto contigo.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "¡Eh, compañero! ¿Puedes hacerme un pequeño favor?";
							link.l1 = "Depende de lo que necesite hacerse.";
							link.l1.go = "Wine_soldier";
							link.l2 = "No tengo tiempo para esto.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "¡Eh, compañero! ¿Podrías hacerme un pequeño favor?";
								link.l1 = "Depende de lo que necesite hacerse.";
								link.l1.go = "Wine_soldier";
								link.l2 = "No tengo tiempo para esto.";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Su Excelencia, Gobernador General! ¿Qué puedo servirle?";
							link.l1 = "No necesito nada, gracias.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Es un gran honor para mí, Sr. Gobernador General. ¿Cómo puedo ayudarlo?";
								link.l1 = "Realiza tu servicio concienzudamente, no requiero nada más de ti.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "¡Bueno verte, Su Excelencia! ¿Qué puede hacer un humilde soldado por el gobernador general de nuestras colonias?";
								link.l1 = "Personalmente, no necesito nada de ti. Sigue sirviendo.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Vicealmirante, ¡Su Excelencia! Permítame informar: durante mi guardia...";
							link.l1 = "Cálmate, soldado, no necesito tu informe. Informa a tu jefe.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "¡Encantado de verte, Vicealmirante! ¿Puedo ayudarte con algo?";
								link.l1 = "No, solo estaba comprobando cuán atento eres. Me alegra que me hayas reconocido.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Vicealmirante, ¡esto es un honor para mí! ¿Qué puedo hacer por usted?";
								link.l1 = "Sirve "+NationNameGenitive(sti(npchar.nation))+", ¡soldado! Es lo mejor que puedes hacer.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "¡Saludos, capitán! Si tienes alguna instrucción para mí, entonces te pido perdón: aunque estoy al servicio de "+NationNameGenitive(sti(npchar.nation))+", solo respondo ante el comandante y el gobernador."; 
							link.l1 = "Tengo a mis oficiales y tripulación respondiendo a mi guía. Haz tu deber, soldado.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Capitán, ¿puede llevarme a servir en su barco? El mismo servicio para "+NationNameGenitive(sti(npchar.nation))+", pero prefiero el mar."; 
								link.l1 = "Se necesita donde se te ha asignado, así que realiza tu servicio con honor. Cierras los ojos por un segundo, y lo llevarán al mar.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, estás de suerte: eres el capitán del barco al servicio de "+NationNameGenitive(sti(npchar.nation))+"... Y estoy atascado aquí todo el día."; 
								link.l1 = "¿Crees que acabo de llegar al Caribe y me convertí en capitán una semana después? Son todos años de duro trabajo...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "¿No puedes ver? Estoy de servicio. Deja de molestarme.";
							link.l1 = "Está bien, está bien...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "¿Vas a contarme sobre alguna actividad sospechosa?";
							link.l1 = "No, ninguno en absoluto, y soy un capitán, por cierto. ¿Veo que ya no estás escuchando? Adiós.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Esta es una instalación militar, así que no hagas demasiado ruido aquí.";
							link.l1 = "Está bien, lo tendré en cuenta.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Un tiempo tan justo, y estoy obligado a quedarme aquí. En el pueblo, al menos hay chicas, ¿y qué tenemos aquí? Solo ratas alrededor.";
							link.l1 = ""+GetSexPhrase("Simpatizo, pero no hay nada que pueda hacer para ayudar, después de todo, es tu deber.","¡Eh! ¿Qué pasa conmigo? ¿Acaso no soy una chica?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Si te gusta hablar, busca a alguien más. Debo mantener el orden aquí, y no tengo tiempo para charlas baratas.";
							link.l1 = "Oh, no, solo estoy comprobando si aún estás vivo. Estabas parado como una estatua.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Probablemente piensas que los días de trabajo en la guarnición son un paseo, ¿no? ¡Absolutamente no! Es un trabajo duro e importante. Recuerdo una vez... ";
							link.l1 = "Me contarás esa historia en otro momento. Ahora tengo un poco de prisa.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "¡Cuidado aquí, estás en un fuerte! ¡Sé tan silencioso como un ratón!";
							link.l1 = "Como digas, soldado.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "¡Eh! ¿Tienes agua, por casualidad? Me estoy muriendo de sed.";
							link.l1 = "No, compañero, mantén tu paciencia...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "¡Qué aburrida es la vida en la guarnición, solo paletos como tú alrededor! Ahora, seguro que la guarnición de la ciudad pasa mejores tiempos...";
							link.l1 = "¿Y a esto llamas 'estar de guardia'? ¡De seguro dejarás que un espía se te escape de esta manera!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Pareces un hombre fuerte, ¿no es así? ¿Te gustaría alistarte para el servicio en la guarnición del fuerte? Tenemos cuarteles espaciosos, dos comidas al día y licor gratis.","¡Oh, joven dama, no tienes idea de lo agradable que es encontrar a una doncella tan agradable en este fin del mundo!")+"";
							link.l1 = ""+GetSexPhrase("Eso es ciertamente tentador, pero aún debo rechazar. Todo ese entrenamiento de cuartel simplemente no es para mí.","Gracias por el cumplido, soldado.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Este maldito calor... Con gusto daría la mitad de mi vida para volver a Europa.";
							link.l1 = "Sí, puedo ver que tu salud no es apta para este clima.";
							link.l1.go = "exit";
						break;
					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Mmm... claro. Yo estaba pensando que "+GetSexPhrase("quería","quería")+" preguntar...";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "Verás, quiero mucho un vino... Pero no la bazofia local hecha de frutas podridas, que se vende por dos pesos el barril, quiero una botella de verdadero vino europeo. Puedes conseguirlo en el pueblo de los comerciantes. Es bastante caro, pero pagaré en su totalidad e incluso añadiré trescientos pesos encima. Entonces, ¿me traerás algo?";
			link.l1 = "¿Y por qué no puedes conseguirlo tú mismo? No tendrás que pagar de más, solo espera hasta que te liberen de tu puesto y ve a por ello. ¿Cuál es el truco?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "No hay trampa. Simplemente no puedo abandonar el fuerte para ir a la ciudad hasta que obtenga mi permiso, lo cual no va a ocurrir pronto. Además, nuestro comandante prohibió estrictamente toda bebida en el fuerte, ¡maldito sea! Entonces, ¿ayudarás a un soldado?";
			link.l1 = "Bueno, ¿por qué no? Te traeré ese vino, de todos modos tengo algo de tiempo libre.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "Lo siento, compañero, pero no puedo hacer eso. Busca a alguien más para que te ayude.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "¡Genial! ¡Muchas gracias! Hoy estoy de guardia, así que ven mañana. Me encontrarás en lo alto del fuerte, allí puedes pasarme la botella, para que nadie se dé cuenta...";
			link.l1 = "Está bien. Espérame, vendré a verte mañana.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Me parece que es alguna trampa. Hablemos con el comandante, "+GetSexPhrase("compañero","querido")+", y descifrarlo todo..."," Hmm... Algo me dice que no eres quien finges ser... Entrega tu arma "+GetAddress_Form(npchar)+", ¡y sígueme para una investigación más a fondo!");
			link.l1 = RandPhraseSimple("¡A la mierda contigo!","Cuando dos domingos vienen en una semana...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, ya veo... Todo parece estar en orden, eres libre de irte, "+GetAddress_Form(pchar)+".","Debo de haberme cansado un poco de estar de guardia... Todo parece estar bien, "+GetAddress_Form(pchar)+", lo siento.");
			link.l1 = "¡No hay problema!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "¡Solo ven a pensarlo! ¡Tal insolencia! ¡Venir aquí bajo la apariencia de un mercader! ¡Tus retratos están publicados en cada cuartel, maldito bastardo! ¡No te saldrás con la tuya esta vez! ¡Atrápenlo!";
				link.l1 = RandPhraseSimple("¡Arrgh!..","Bueno, lo pediste...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "¿Has venido a comerciar aquí? ¿Puedo preguntar cómo? ¿Dónde está tu barco? Sabes, todo parece muy sospechoso, y me veo obligado a detenerte hasta que lo averigüemos todo. ¡Entrega tu arma y sígueme!";
				link.l1 = RandPhraseSimple("¡A la mierda contigo!","Cuando dos domingos vienen en una semana...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Tu licencia tiene que ser revocada ya que está vencida, y por esa razón no es válida. ¡Entrega tu arma y sígueme para una investigación adicional!";
				link.l1 = RandPhraseSimple("¡Al diablo contigo!","Cuando dos domingos llegan en una semana...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Todo parece estar en orden. Sin embargo, debo notar que tu licencia expira hoy. Te dejaré pasar esta vez, pero aún tendrás que obtener una nueva licencia.";
				link.l1 = "Gracias, lo haré a la mayor brevedad posible.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Todo parece estar en orden. Aun así, debo señalar que tu licencia expirará pronto. Todavía es válida solo por "+FindRussianDaysString(iTemp)+". Así que ten eso en cuenta, "+GetAddress_Form(npchar)+".";
				link.l1 = "Gracias, conseguiré uno nuevo a la mayor brevedad posible.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Bueno, todo parece estar en orden. Tu licencia es válida por "+FindRussianDaysString(iTemp)+". Puedes pasar.","Todo está claro, "+GetAddress_Form(npchar)+". Puedes entrar y salir libremente de la ciudad, tu licencia es válida para  "+FindRussianDaysString(iTemp)+". Lo siento por molestarte.","Todo parece estar bien, "+GetAddress_Form(npchar)+", ya no te retengo aquí.");
				link.l1 = RandPhraseSimple("Excelente. Mis mejores deseos.","Gracias, oficial.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "Capitán, le pido que guarde sus armas: está prohibido desenfundarlas en nuestra ciudad.";
				link.l1 = LinkRandPhrase("Está bien, lo guardaré...","Ya hecho.","Como usted dice...");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("¡Que te jodan!","¡Supongo que lo voy a usar!","Lo guardaré cuando llegue el momento adecuado.");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("¿Por qué diablos andas por ahí con una espada desenvainada? ¡Guarda tu arma de inmediato!","¡Te ordeno que enfundes tu arma inmediatamente!","Oye, "+GetSexPhrase("compañero","chica")+", ¡deja de asustar a la gente! Envaina tu arma.");
			link.l1 = LinkRandPhrase("Bien.","Bien.","Como usted diga...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¡Que te jodan!","No hay mal en soñar...","Cuando dos domingos llegan en una semana.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
