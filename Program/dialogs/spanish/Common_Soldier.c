// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int DeceptionChance = 0;
	int DeceptionPenalty = 0;
	if (CheckAttribute(pchar, "StealtDeceptionPenalty"))
		DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);

	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK) * 100 / 110);
	if (DeceptionChance - DeceptionPenalty > 50)
		DeceptionChance -= DeceptionPenalty;
	if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK) * 100 / 310);
		if (DeceptionChance - DeceptionPenalty > 50)
			DeceptionChance -= DeceptionPenalty;
	}
	if (sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if (DeceptionChance - DeceptionPenalty > 50)
			DeceptionChance -= DeceptionPenalty;
	}
	if (DeceptionChance > 90)
		DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
	/* // вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
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
	switch (Dialog.CurrentNode)
	{
	case "Exit":
		sTemp = npchar.location;
		if (findsubstr(sTemp, "_townhall", 0) != -1)
			AddDialogExitQuest("MainHeroFightModeOff");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "First time":
		NextDiag.TempNode = "First time";
		if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
		{
			// заглушка на пирата
			if (sti(pchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("¿Piratas en la ciudad?! No puedo creerlo... Confisca " + GetSexPhrase("él", "ella") + "¡¡", "¡Ese es un pirata! Capturad " + GetSexPhrase("él", "ella") + "¡¡¡");
				link.l1 = RandPhraseSimple("Soy un pirata, ¿y qué?", "Je, puedes intentarlo...");
				link.l1.go = "fight";
				break;
			}
			else
			{
				if (DeceptionChance > (10 + rand(150) + rand(150)))
				{
					dialog.text = RandPhraseSimple("¿Quién eres y qué haces aquí?", "¡Alto ahí! ¿Quién eres y con qué derecho intentas entrar a la ciudad?");
					link.l2 = "Anclé cerca de " + XI_ConvertString(GetIslandByCityName(npchar.city) + "Gen") + " bajo la bandera de " + NationNameGenitive(sti(npchar.nation)) + "¿Qué es lo que no entiendes? (Probabilidad de engaño " + DeceptionChance + "%%)";
					link.l1.go = "NotPegYou";
				}
				else
				{
					dialog.text = RandPhraseSimple("¡Un espía! ¡Entrega tu arma y sígueme!", "¡Un agente enemigo! Aprehende " + GetSexPhrase("él", "ella") + "¡!");
					link.l1 = RandPhraseSimple("¡Cállate, marica!", "¡Que te jodan!");
					link.l1.go = "fight";
				}
			}
		}
		else
		{
			// eddy. проверяем, не казачок ли. -->
			if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// грамота Винсенто
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
				{
					dialog.text = RandPhraseSimple("¿Quién eres y qué estás haciendo aquí?", "¡Alto ahí! ¿Quién eres tú, y con qué derecho intentas entrar a la ciudad?");
					link.l1 = "Mira este papel, soldado. Estoy aquí con permiso del Inquisidor, Padre Vincento.";
					link.l1.go = "vincento";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
				{
					dialog.text = RandPhraseSimple("¿Quién eres y qué estás haciendo aquí?", "¡Alto ahí! ¿Quién eres y con qué derecho intentas entrar a la ciudad?");
					link.l1 = "Mira este papel, soldado. Estoy aquí con permiso del Inquisidor, Padre Vincento.";
					link.l1.go = "vincento";
					break;
				}
				if (PChar.location == "Maracaibo_Plantation")
				{
					dialog.text = LinkRandPhrase("Compórtate y no molestes a los esclavos.", "¡Vamos, sigue adelante!", "Ah, eres tú. Adelante, ya hemos sido informados sobre ti.");
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				dialog.text = RandPhraseSimple("¿Quién eres y qué estás haciendo aquí?", "¡Detente ahí mismo! ¿Quién eres y con qué derecho intentas entrar a la ciudad?");
				//==> по лицензии
				if (CheckNationLicence(HOLLAND))
				{
					link.l1 = "Oficial, tengo " + GetRusNameNationLicence(HOLLAND) + ", así que estoy aquí en términos legales. Aquí, por favor echa un vistazo...";
					link.l1.go = "LicenceOk";
					if (findsubstr(pchar.location.from_sea, "_town", 0) != -1) // если причалил в городе
					{
						link.l2 = "¿No ves la bandera de " + NationNameGenitive(sti(pchar.nation)) + "¿en el mástil de mi barco?! (Probabilidad de engaño " + DeceptionChance + "%%)";
					}
					else // если причалил не в городе
					{
						link.l2 = "Eché el ancla cerca de " + XI_ConvertString(GetIslandByCityName(npchar.city) + "Gen") + " bajo la bandera de " + NationNameGenitive(sti(pchar.nation)) + ". ¿Qué no entiendes? (Probabilidad de engaño " + DeceptionChance + "%%)";
					}
					if (DeceptionChance < (10 + rand(50) + rand(50)))
					{
						link.l2.go = "PegYou";
					}
					else
					{
						link.l2.go = "NotPegYou";
					}
				}
				else
				{
					//==> по флагу
					// заглушка на пирата
					if (sti(pchar.nation) == PIRATE)
					{
						dialog.text = RandPhraseSimple("¿Piratas en la ciudad?! No puedo creerlo... ¡Capturadlo!", "¡Ese es un pirata! ¡Atrapadlo!");
						link.l1 = RandPhraseSimple("Sí, soy un pirata, ¿y qué?", "Je, atrápame si puedes...");
						link.l1.go = "fight";
						break;
					}
					if (findsubstr(pchar.location.from_sea, "_town", 0) != -1) // если причалил в городе
					{
						link.l1 = "¿No ves la bandera de " + NationNameGenitive(sti(pchar.nation)) + " ¿en mi barco?! (Probabilidad de engaño " + DeceptionChance + "%%)";
					}
					else // если причалил не в городе
					{
						link.l1 = "Eché el ancla cerca de " + XI_ConvertString(GetIslandByCityName(npchar.city) + "Gen") + " bajo la bandera " + NationNameGenitive(sti(pchar.nation)) + "¿Qué es lo que no entiendes? (Probabilidad de engaño " + DeceptionChance + "%%)";
					}
					if (DeceptionChance < (10 + rand(50) + rand(50)))
					{
						link.l1.go = "PegYou";
					}
					else
					{
						link.l1.go = "NotPegYou";
					}
				}
			}
			// <-- eddy. проверяем, не казачок ли.
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					if (sti(rColony.HeroOwn) == true) // наш горожанин
					{
						switch (rand(10))
						{
						case 0:
							dialog.text = "¡Oh, capitán, hemos pasado un tiempo tan maravilloso contigo en el mar! ¡Cuántos barcos hemos hundido juntos bajo tu mando! Y aquí...";
							link.l1 = "Y aquí, mi amigo, puedes deleitar tus ojos con damas encantadoras, no las verás en el mar.";
							link.l1.go = "exit";
							break;

						case 1:
							dialog.text = "Capitán, ¿qué hemos hecho para merecer esto?! No somos ratas de tierra, ¿verdad?";
							link.l1 = "¡Silencio, marinero! Tu puesto es muy importante y honorífico, así que deja de quejarte.";
							link.l1.go = "exit";
							break;

						case 2:
							dialog.text = "¿Qué sucede en el mar, capitán? ¿Volveremos a verlo alguna vez?";
							link.l1 = "¡Pero por supuesto, marinero! Una vez que estés liberado de tu deber, puedes dirigirte al muelle y disfrutar del mar tanto como quieras.";
							link.l1.go = "exit";
							break;

						case 3:
							dialog.text = "Quiero quejarme, capitán: a todos nosotros nos falta el mar. ¡Estamos totalmente hartos de este deber terrestre!";
							link.l1 = "¡Me canso de este lloriqueo! ¡También tienes suficiente ron aquí! Sirve donde el capitán te ha colocado, o alguien será colgado como ejemplo para los demás.";
							link.l1.go = "exit";
							break;

						case 4:
							dialog.text = "Te diré en confidencia, capitán, el nuevo gobernador es un sobornador y malversador. Pero eso realmente no es asunto mío...";
							link.l1 = "Exactamente, corsario. Tu trabajo es permanecer en tu puesto y mantener el orden. Y colgar al gobernador en la verga es mi trabajo. ¡Buen trabajo!";
							link.l1.go = "exit";
							break;

						case 5:
							dialog.text = "¡Gracias por no olvidarte de nosotros, capitán! ¡Te seguiríamos a través del fuego y el agua!";
							link.l1 = "Conozco tu tipo, ¡malhechores! Todo lo que realmente amas es el oro. Hay una fiesta en la taberna esta noche, las bebidas corren por mi cuenta. No olvides presentarte.";
							link.l1.go = "exit";
							break;

						case 6:
							dialog.text = "¡Je, capitán! Solo piénsalo, ¿puede un corsario ser realmente un guardián del orden? ¡Ha pasado tanto tiempo desde que estuvimos en el verdadero negocio!";
							link.l1 = "¡No hay tiempo para relajarse, corsario! Las armadas enemigas están peinando las aguas cerca de nuestras islas, y debemos estar listos para un baño de sangre en cualquier momento.";
							link.l1.go = "exit";
							break;

						case 7:
							dialog.text = "Capitán, ¿escuché que la Corona había enviado otro escuadrón en nuestro camino?";
							link.l1 = "Por supuesto, corsario. Mientras vivamos, no habrá paz para nosotros. ¡E incluso en el Infierno estaremos luchando contra diablos!";
							link.l1.go = "exit";
							break;

						case 8:
							dialog.text = "¡Yo-ho-ho! Maldición, esa fue una bebida realmente fuerte ayer, capitán! Es una lástima que no estuvieras allí.";
							link.l1 = "No es gran cosa, lo compensaré. Y no os envidio, chicos.";
							link.l1.go = "exit";
							break;

						case 9:
							dialog.text = "Te lo diré en confianza, capitán, porque siempre nos has tratado bien, ayer lo pasamos muy bien con una chica muy agradable...";
							link.l1 = "Je, corsario, ¡una soga es algo que realmente necesitas!";
							link.l1.go = "exit";
							break;

						case 10:
							dialog.text = "¡Capitán! Por favor, libérame de este maldito deber! Simplemente no puedo seguir desempeñando el papel de guardián del orden.";
							link.l1 = "La guardia nocturna en un barco tampoco es fácil. Amigo, el deber es el deber, sea lo que sea y esté donde esté.";
							link.l1.go = "exit";
							break;
						}
						// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
						/* link.l2 = RandPhraseSimple("¡Hay un asunto importante!","Tengo un asunto contigo.");
						link.l2.go = "quests";//(перессылка в файл города) */
						break;
					}
					else
					{ // пираты, не наши
						if (sti(pchar.GenQuest.Piratekill) > 20)
						{
							dialog.text = RandPhraseSimple("¡Alerta! ¡Un enfermo psicópata armado está aquí!", "¡A las armas, a las armas! ¡Algún maldito loco está aquí!");
							link.l1 = RandPhraseSimple("¿Eh? ¿Qué?", "Uh, ¿por qué estás haciendo esto?");
							link.l1.go = "pirate_fight";
						}
						else
						{
							/* dialog.text = LinkRandPhrase(RandPhraseSimple("¿Tiene algún asunto conmigo, capitán?","Me estoy moviendo por asuntos aquí, si necesitas algo, pregunta, no te demores."),RandPhraseSimple("Capitán, estoy muy ocupado, así que busque a otros interlocutores.","¿Algo anda mal, capitán? Si no hay preguntas, permíteme ir."),"Abra paso, capitán, tengo prisa.");
						link.l1 = LinkRandPhrase("Lo siento, amigo, yo "+GetSexPhrase("se perdió","Se perdió")+" ","Bueno, ocúpate de tus asuntos.","No, nada.");
						link.l1.go = "exit";
						link.l2 = LinkRandPhrase(RandPhraseSimple("Tengo un par de preguntas para ti.","Tengo un asunto contigo."),RandPhraseSimple("Veo que tienes prisa. Una pregunta y serás libre.","Yo "+GetSexPhrase("quería","quería")+" preguntar algo."),"Tus asuntos pueden esperar. Quería preguntarte algo "+GetSexPhrase("quería","quería")+".");
							link.l2.go = "quests";//(перессылка в файл города) */

							// Экку Korsar - что-то они больно вежливые для пиратов были...
							dialog.text = RandPhraseSimple("¿Qué quieres? Pasa de largo.", "Deja de bloquear el camino, retrocede.");
							link.l1 = RandPhraseSimple("¿Sabes? ¡No ladres!", "Reduce tu ardor. ¡No lo enfriaré rápidamente!");
							link.l1.go = "exit";
							/* link.l2 = LinkRandPhrase(RandPhraseSimple("Tengo un par de preguntas para ti.","Tengo un asunto contigo."),RandPhraseSimple("Veo que tienes prisa. Una pregunta y serás libre.","Yo "+GetSexPhrase("quería","quería")+" preguntar algo."),"Tus asuntos pueden esperar. Yo quiero preguntar algo "+GetSexPhrase("quería","quería")+".");
						link.l2.go = "quests";//(перессылка в файл города) */
						}
						break;
					}
				}
				else
				{ // если негодяй, имеющий НЗГ к дружественной или нейтральной нации
					if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
					{
						dialog.text = RandPhraseSimple("Solo mira  " + GetSexPhrase("¡a ese canalla! Se atrevió a mostrar su rostro", "a ese malandrín! Se atrevió a mostrar su rostro") + " en " + XI_ConvertString("Colony" + npchar.city) + ". Aprende " + GetSexPhrase("él", "ella") + "!!!", "Ja, te reconocí, " + GetSexPhrase("granuja", "granuja") + "¡Captura " + GetSexPhrase("él", "ella") + "!!!");
						link.l1 = RandPhraseSimple("¡Argh!..", "Bueno, lo has pedido...");
						link.l1.go = "fight";
						break;
					}
				}

				// --> девица в джунглях
				if (rand(2) == 1 && CheckAttribute(pchar, "GenQuest.EncGirl") && CheckAttribute(pchar, "GenQuest.EncGirl.MeetSoldiers"))
				{
					if (sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)
					{
						dialog.text = "¡Oh, mira quién está ahí! ¡La mismísima " + pchar.GenQuest.EncGirl.name + " ha venido en persona! ¿Cómo te atreves? ¡Te hemos estado buscando! Por favor, procede al calabozo, tu celda está lista y esperándote. ";
						link.l1 = "¿Qué disparates estás hablando? Te equivocas de persona. Mi " + GetSexPhrase("novio", "novia") + " y yo estábamos dando un paseo por la jungla, recogiendo flores. ¡Déjame en paz! ¿Dónde están los modales de estos tipos? ¡En cuanto ven a una chica atractiva, empiezan a fastidiarla! ¡" + GetSexPhrase("Mi querida, dile a esos idiotas que se pierdan y dejen en paz a una mujer honesta", "Cariño, por favor dile a esos idiotas...") + "!";
						link.l1.go = "GirlEnc_1";
					}
					if (sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)
					{
						dialog.text = "¡Oh, ahí estás, hermosa! Tu padre ha levantado a toda la guarnición para encontrarte y llevarte de vuelta a casa.";
						link.l1 = "¡Piérdete! Sé a dónde voy y no necesito tu ayuda. ¡Capitán, diles que aparten sus manos de mí!";
						link.l1.go = "GirlEnc_2";
					}
					DeleteAttribute(pchar, "GenQuest.EncGirl.MeetSoldiers");
				}
				// <-- девица в джунглях

				// --> Sinistra Длинные тени старых грехов
				if (CheckAttribute(pchar, "questTemp.Knippel.Soldiers_1"))
				{
					switch (0)
					{
					case 0:
						dialog.text = "Escucha, Charlie, tenemos algunos reclutas nuevos en el fuerte. Verdes como la hierba... ¿Podrías pasar y enseñarles cómo apuntar?";
						link.l1 = "Si el Capitán Fleetwood y yo no zarpamos en los próximos días, con gusto.";
						link.l1.go = "Knippel_Soldiers_1";
						break;
					}
					break;
				}

				if (CheckAttribute(pchar, "questTemp.Knippel.Soldiers_2"))
				{
					switch (0)
					{
					case 0:
						dialog.text = "Charlie, mi turno casi termina, ¿te apetece una bebida?";
						link.l1 = "Con gusto, compañero! Permíteme ver qué quiere el capitán.";
						link.l1.go = "Knippel_Soldiers_2";
						break;
					}
					break;
				}

				if (CheckAttribute(pchar, "questTemp.Knippel.Soldiers_3"))
				{
					switch (0)
					{
					case 0:
						dialog.text = "¡Buena noche, Charlie! No pareces muy bien. ¿Todo está bien?";
						link.l1 = "Me despertaron en medio de la noche, ¿qué te parece? No puedo pillar un respiro.";
						link.l1.go = "Knippel_Soldiers_3";
						break;
					}
					break;
				}
				// <-- Длинные тени старых грехов

				// --> belamour ночной приключенец
				if (CheckAttribute(pchar, "GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
				{
					dialog.text = "La vida de un soldado está programada, de guardia, patrullando ... ¿Qué quieres, " + GetAddress_Form(NPChar) + "?";
					link.l1 = "Escucha, ¿fue contigo que un borracho tuvo una pelea aquí recientemente? Bueno, aunque, aparentemente, sí, contigo...";
					link.l1.go = "NightAdventure_CitizenHomieSolder";
					break;
				}
				// <-- ночной приключенец

				// belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->

				// Шарль де Мор генерал-губернатор французских колоний
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					switch (rand(2))
					{
					case 0:
						dialog.text = "Vuestra Excelencia, Gobernador General! ¿Cómo puedo servir?";
						link.l1 = "No necesito nada, gracias.";
						link.l1.go = "exit";
						break;

					case 1:
						dialog.text = "Es un gran honor para mí, Sr. Gobernador General. ¿Cómo puedo ayudarle?";
						link.l1 = "Cumple con tu servicio conscientemente, no requiero nada más de ti.";
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
				if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
				{
					switch (rand(2))
					{
					case 0:
						dialog.text = "Vicealmirante, ¡Su Excelencia! Permítame informar: durante mi guardia...";
						link.l1 = "Cálmate, soldado, no necesito tu informe. Informa a tu oficial.";
						link.l1.go = "exit";
						break;

					case 1:
						dialog.text = "¡Encantado de verte, Vicealmirante! ¿Puedo ayudarte en algo?";
						link.l1 = "No, solo estaba comprobando cuán atento eres. Me alegra que me hayas reconocido.";
						link.l1.go = "exit";
						break;

					case 2:
						dialog.text = "Vicealmirante, ¡es un honor para mí! ¿Qué puedo hacer por usted?";
						link.l1 = "Sirve " + NationNameGenitive(sti(npchar.nation)) + ", ¡soldado! Es lo mejor que puedes hacer.";
						link.l1.go = "exit";
						break;
					}
					break;
				}
				// Офицер с патентом
				if (IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
				{
					switch (rand(2))
					{
					case 0:
						dialog.text = "¡Saludos, capitán! Si tienes alguna instrucción para mí, entonces te ruego disculpas: aunque estoy al servicio de " + NationNameGenitive(sti(npchar.nation)) + ", solo respondo ante el comandante y el gobernador.";
						link.l1 = "Tengo a mis oficiales y tripulación respondiendo a mi guía. Cumple tu deber, soldado.";
						link.l1.go = "exit";
						break;

					case 1:
						dialog.text = "Capitán, ¿puede llevarme a servir en su barco? El mismo servicio para " + NationNameGenitive(sti(npchar.nation)) + ", pero prefiero el mar.";
						link.l1 = "Se te necesita donde se te ha asignado, así que realiza tu servicio con honor. Cierras los ojos por un segundo, y te lo llevarán al mar.";
						link.l1.go = "exit";
						break;

					case 2:
						dialog.text = "Oh, estás de suerte: eres el capitán del barco al servicio de " + NationNameGenitive(sti(npchar.nation)) + "... Y estoy atrapado aquí todo el día.";
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
					dialog.text = "¿Vas a contarme acerca de alguna actividad sospechosa?";
					link.l1 = "No, ninguno en absoluto, y por cierto, soy un capitán. ¿Veo que ya no estás escuchando? Adiós.";
					link.l1.go = "exit";
					break;

				case 2: ///////////////////////////////////////////
					dialog.text = "Esta es una instalación militar, así que no hagas mucho ruido aquí.";
					link.l1 = "Está bien, lo tendré en cuenta.";
					link.l1.go = "exit";
					break;

				case 3:
					dialog.text = "Un tiempo tan bueno, y estoy obligado a quedarme aquí. En el pueblo, al menos hay chicas, ¿y qué tenemos aquí? Solo ratas alrededor.";
					link.l1 = "" + GetSexPhrase("Siento simpatía, pero no hay nada que pueda hacer para ayudar, es tu deber después de todo.", "¡Oye! ¿Qué pasa conmigo? ¿No soy una chica?") + "";
					link.l1.go = "exit";
					break;

				case 4: ///////////////////////////////////////////
					dialog.text = "Si te gusta hablar, busca a alguien más. Debo mantener el orden aquí, y no tengo tiempo para charlas baratas.";
					link.l1 = "Oh, no, solo estoy comprobando si aún estás vivo. Estabas parado como una estatua.";
					link.l1.go = "exit";
					break;

				case 5: ////////////////////////////////////////////
					dialog.text = "¿Probablemente piensas que los días de trabajo en la guarnición son pan comido? ¡Absolutamente no! Es un trabajo duro e importante. Recuerdo una vez...";
					link.l1 = "Me contarás esa historia en otro momento. Ahora tengo un poco de prisa.";
					link.l1.go = "exit";
					break;

				case 6: ////////////////////////////////////////////
					dialog.text = "¡Cuidado aquí, estás en un fuerte! ¡Sé tan silencioso como un ratón!";
					link.l1 = "Como usted diga, soldado.";
					link.l1.go = "exit";
					break;

				case 7:
					dialog.text = "¡Eh! ¿Tienes agua, por casualidad? Me estoy muriendo de sed.";
					link.l1 = "No, amigo, ten paciencia...";
					link.l1.go = "exit";
					break;

				case 8: /////////////////////////////////////////////
					dialog.text = "¡Qué aburrida es la vida de la guarnición, solo paletos como tú alrededor! Ahora, la guarnición de la ciudad seguramente tiene mejores tiempos...";
					link.l1 = "¿Y llamas a esto 'estar de guardia'? ¡De esta manera seguramente dejarás que un espía se te escape!";
					link.l1.go = "exit";
					break;

				case 9: /////////////////////////////////////////////
					dialog.text = "" + GetSexPhrase("Pareces un hombre fuerte, ¿no es así? ¿Te gustaría alistarte en la guarnición del fuerte? Tenemos cuarteles espaciosos, dos comidas al día y licor gratis.", "¡Oh, joven dama, no tienes idea de lo agradable que es encontrar a una damisela tan agradable en este fin del mundo!") + "";
					link.l1 = "" + GetSexPhrase("Eso es ciertamente tentador, pero aún debo rechazarlo. Todo ese entrenamiento de cuartel simplemente no es para mí.", "Gracias por el cumplido, soldado.") + ".";
					link.l1.go = "exit";
					break;

				case 10:
					dialog.text = "Este maldito calor... Daría gustosamente la mitad de mi vida para volver a Europa.";
					link.l1 = "Sí, puedo ver que tu salud no es adecuada para este clima.";
					link.l1.go = "exit";
					break;
				}
				// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
				/* link.l3 = "Un momento. Quería preguntar algo "+GetSexPhrase("quería","quería")+"...";
				link.l3.go = "quests";//(перессылка в файл города) */
			}
		}
		break;
	//============================== ноды на разборки при распознавании =========================
	case "PegYou":
		dialog.text = RandPhraseSimple("Me parece que es alguna trampa. Hablemos con el comandante, " + GetSexPhrase("compañero", "querido") + ", y descúbrelo todo...", "Hmm... Algo me dice que no eres quien pretendes ser... Entrega tu arma " + GetAddress_Form(npchar) + ", ¡y sígueme para una investigación más profunda!");
		link.l1 = RandPhraseSimple("¡Al diablo contigo!", "Cuando dos domingos llegan en una semana...");
		link.l1.go = "fight";
		if (!CheckAttribute(pchar, "questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		break;

	case "NotPegYou":
		dialog.text = RandPhraseSimple("Oh, ya veo... Todo parece estar en orden, eres libre de irte, " + GetAddress_Form(pchar) + ".", "Debo de haberme cansado un poco de estar de guardia... Todo parece estar bien, " + GetAddress_Form(pchar) + ", lo siento.");
		link.l1 = "¡No hay problema!";
		link.l1.go = "exit";
		if (!CheckAttribute(pchar, "questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
		{
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
			pchar.questTemp.stels.landSolder = GetDataDay();
		}
		break;

	case "vincento":
		dialog.text = RandPhraseSimple("Ah, ya veo... Todo parece estar en orden, eres libre de irte, " + GetAddress_Form(pchar) + ".", "Veamos ahora... Bueno, todo parece estar en orden, " + GetAddress_Form(pchar) + ", lo siento.");
		link.l1 = "¡Eso te enseñará!";
		link.l1.go = "exit";
		break;

	case "LicenceOk":
		iTemp = GetDaysContinueNationLicence(HOLLAND);
		if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
		{
			dialog.text = "¡Solo piénsalo! ¡Qué insolencia! ¡Venir aquí bajo la apariencia de un comerciante! ¡Tus retratos están colgados en cada cuartel, maldito! ¡No te saldrás con la tuya esta vez! ¡Atrápenlo!";
			link.l1 = RandPhraseSimple("¡Arrgh!..", "Bueno, lo has pedido...");
			link.l1.go = "fight";
			TakeNationLicence(HOLLAND);
			break;
		}
		if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town", 0) == -1) // если причалил не в городе 300912
		{
			dialog.text = "¿Has venido a comerciar aquí? ¿Puedo preguntar cómo? ¿Dónde está tu barco? Sabes, todo parece muy sospechoso, y me veo obligado a detenerte hasta que lo resolvamos todo. ¡Entrega tu arma y sígueme!";
			link.l1 = RandPhraseSimple("¡Que te jodan!", "Cuando dos domingos lleguen en una semana...");
			link.l1.go = "fight";
			TakeNationLicence(HOLLAND);
			break;
		}
		if (iTemp == -1)
		{
			dialog.text = "¡Tu licencia debe ser revocada ya que está caducada, y por esa razón no es válida. ¡Rinde tu arma y sígueme para una investigación más profunda!";
			link.l1 = RandPhraseSimple("¡Que te jodan!", "Cuando dos domingos llegan en una semana...");
			link.l1.go = "fight";
			TakeNationLicence(HOLLAND);
			break;
		}
		if (iTemp == 0)
		{
			dialog.text = "Hmm... Todo parece estar en orden. Sin embargo, debo notar que tu licencia expira hoy. Te dejaré pasar esta vez, pero aún tendrás que obtener una nueva licencia.";
			link.l1 = "Gracias, conseguiré uno nuevo a la mayor brevedad posible.";
			link.l1.go = "exit";
		}
		if (iTemp > 0 && iTemp <= 10)
		{
			dialog.text = "Hmm... Todo parece estar en orden. Aún así, debo notar que tu licencia expirará pronto. Todavía es válida solo por " + FindRussianDaysString(iTemp) + ". Así que ten eso en cuenta, " + GetAddress_Form(npchar) + ".";
			link.l1 = "Gracias, conseguiré uno nuevo a la mayor brevedad posible.";
			link.l1.go = "exit";
		}
		if (iTemp > 10)
		{
			dialog.text = LinkRandPhrase("Bueno, todo parece en orden. Tu licencia es válida por otro " + FindRussianDaysString(iTemp) + ". Puedes pasar.", "Todo está claro, " + GetAddress_Form(npchar) + ". Puedes entrar y salir libremente de la ciudad, tu licencia es válida por otro " + FindRussianDaysString(iTemp) + ". Lo siento por molestarte.", "Todo parece estar bien, " + GetAddress_Form(npchar) + ", ya no te retengo aquí.");
			link.l1 = RandPhraseSimple("Excelente. Mis mejores deseos.", "Gracias, oficial.");
			link.l1.go = "exit";
		}
		break;
	//============================== ноды маяка Порт Рояля =========================
	case "PortRoyal_Mayak":
		dialog.text = RandPhraseSimple("Eh, camarada, no rompas nada en el faro.", "Este faro es un objeto de ciudad muy importante. ¡Ten cuidado!");
		link.l1 = RandPhraseSimple("Está bien, no te preocupes.", "Está bien, no te preocupes.");
		link.l1.go = "exit";
		NextDiag.TempNode = "PortRoyal_Mayak";
		break;
	case "PortRoyal_Gans":
		dialog.text = LinkRandPhrase("¡No camines cerca de los cañones, es una instalación militar!", "¡A los extraños no se les permite cerca de los cañones!", "¡Si te veo rondando cerca de los cañones, estás acabado!");
		link.l1 = RandPhraseSimple("Lo conseguí.", "Está bien, lo tengo.");
		link.l1.go = "exit";
		NextDiag.TempNode = "PortRoyal_Gans";
		break;

	// --> генератор "A damsel in the jungle"
	case "GirlEnc_1":
		dialog.text = "¿Y quién eres tú, capitán? ¿No serás por casualidad, un cómplice del ladrón más notorio de este asentamiento?";
		link.l1 = "¿¡A quién acabas de llamar cómplice de crimen?! ¿¡Estás insolado o qué?! ¡Eh, quita tus zarpas de la chica!";
		link.l1.go = "GirlEnc_11";
		link.l2 = "De hecho, yo he " + GetSexPhrase("llegué a conocerla", "llegué a conocerla") + " recientemente...";
		link.l2.go = "GirlEnc_12";
		break;

	case "GirlEnc_11":
		dialog.text = "" + GetSexPhrase("Señor", "Señorita") + ", tenemos una orden de detenerla y llevarla a la mazmorra. Y si crees que puedes detenernos, estás equivocado.";
		link.l1 = "Veamos, entonces...";
		link.l1.go = "GirlEnc_11End";
		break;

	case "GirlEnc_11End":
		DialogExit();
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		sld = CharacterFromID("CangGirl");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
		sld.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "GirlEnc_12":
		dialog.text = "¿Oh, en serio? En ese caso te aconsejaría que revises tus bolsillos. Esa mujer es una profesional, ya sabes.";
		link.l1 = "Gracias, lo haré. ¿Cómo pude hacerme el tonto de tal manera?";
		link.l1.go = "GirlEnc_12End";
		break;

	case "GirlEnc_12End":
		pchar.money = sti(pchar.money) - makeint(sti(pchar.money) / 20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		sld = CharacterFromID("CangGirl");
		LAi_SetActorType(sld);
		LAi_ActorStay(sld);
		LAi_CharacterDisableDialog(sld);
		sld.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		break;

	case "GirlEnc_2":
		dialog.text = "" + GetSexPhrase("Señor", "Señorita") + ", tenemos una orden de encontrar a esa dama y llevarla a su padre.";
		link.l1 = "Bueno, una orden es una orden, adelante, entonces.";
		link.l1.go = "GirlEnc_2End";
		link.l2 = "Demasiado tarde para eso, porque ya estoy hablando con su padre.";
		link.l2.go = "GirlEnc_21";
		break;

	case "GirlEnc_2End":
		NextDiag.CurrentNode = NextDiag.TempNode;
		sld = CharacterFromID("CangGirl");
		LAi_SetActorType(sld);
		LAi_ActorStay(sld);
		LAi_CharacterDisableDialog(sld);
		sld.lifeDay = 0;
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddQuestRecord("JungleGirl", "11");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		CloseQuestHeader("JungleGirl");
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		break;

	case "GirlEnc_21":
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
		{
			dialog.text = "Capitán, tenemos una orden, y si piensas que puedes detenernos, estás equivocado.";
			link.l1 = "Veamos, entonces...";
			link.l1.go = "GirlEnc_21End";
		}
		else
		{
			dialog.text = "Heh, " + GetSexPhrase("eres un hombre afortunado", "eres una chica afortunada") + ". Su padre prometió una generosa recompensa al que la traiga de vuelta a él.";
			link.l1 = "No desesperes, aún te esperan muchas recompensas.";
			link.l1.go = "exit";
		}
		break;

	case "GirlEnc_21End":
		DialogExit();
		AddQuestRecord("JungleGirl", "12");
		AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
		CloseQuestHeader("JungleGirl");
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		sld = CharacterFromID("CangGirl");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
		sld.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- генератор "A damsel in the jungle"
	// --> belamour ночной приключенец
	case "NightAdventure_CitizenHomieSolder":
		dialog.text = "Sí, conmigo. Deja que se siente detrás de las rejas, que piense en su comportamiento. Y si has venido a amenazarme por él, entonces créeme: incluso puedo llegar al comandante del fuerte.";
		link.l1 = "Sí, no vine a amenazar, sino a pedirte que retires tus reclamaciones contra él. Verás, es un viejo conocido mío, simplemente se emborrachó, pero para un borracho, el mar está hasta las rodillas ...";
		link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;

	case "NightAdventure_CitizenHomieSolder_1":
		dialog.text = "Es decir, ¿me dio un ojo morado mientras estaba de servicio, y ahora debería ser liberado? ¿Por qué sucedería eso?";
		link.l1 = "¿Qué tal quinientos pesos como disculpa por su comportamiento?";
		link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;

	case "NightAdventure_CitizenHomieSolder_2":
		dialog.text = "¿Piensas eso? Ha insultado mi honor, ¿y piensas que esto puede ser perdonado por quinientos pesos? ¿Crees que mi honor puede ser comprado?";
		link.l1 = "...";
		link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;

	case "NightAdventure_CitizenHomieSolder_3":
		if (pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
		{
			DeleteAttribute(pchar, "GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "No, Capitán, es todo justo. Lo merecía. Y le pido que no me distraiga más de mi servicio.";
			link.l1 = "Bueno, tienes razón.";
			link.l1.go = "exit";
		}
		if (pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
		{
			dialog.text = "Mil. Y ni un peso menos.";
			link.l1 = "No, quizás no estoy listo para pagar tanto por un moretón.";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Oh... Bien, espera. Aquí tienes una pluma y pergamino de inmediato. Escribe que estás renunciando a cualquier reclamo contra mi amigo.";
				link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
			}
		}
		break;

	case "NightAdventure_CitizenHomieSolder_3NM":
		DeleteAttribute(pchar, "GenQuest.NightAdventureSolNum");
		pchar.quest.NightAdventure_SeaExit.over = "yes";
		pchar.quest.NightAdventure_JungleExit.over = "yes";
		SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		dialog.text = "Entonces te pido que no me distraigas más de mi servicio.";
		link.l1 = "No lo haré.";
		link.l1.go = "exit";
		break;

	case "NightAdventure_CitizenHomieSolder_3GM":
		DeleteAttribute(pchar, "GenQuest.NightAdventureSolNum");
		pchar.GenQuest.NightAdventureToPrisoner = true;
		AddMoneyToCharacter(pchar, -1000);
		dialog.text = "Aquí estás.";
		link.l1 = "Buena suerte en el trabajo.";
		link.l1.go = "exit";
		break;
	// <-- ночной приключенец

	// --> Sinistra Длинные тени старых грехов
	case "Knippel_Soldiers_1":
		dialog.text = "¿Y tal vez enseñarles algunos de tus secretos también, para que no se los lleven a la tumba contigo?";
		link.l1 = "Je-je, eh, no, compañero, mis secretos son solo míos, ¿y qué tipo de secretos serían entonces?";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
		pchar.questTemp.Knippel.Soldiers_2 = true;
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Knippel_Soldiers_2":
		dialog.text = "Entendido, vas a abandonar nuevamente, como siempre.";
		link.l1 = "Bueno, si el pez se escapa, es un mal pescador. Es igual con las balas de cañón, una buena nunca te falla, solo apunta bien...";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
		pchar.questTemp.Knippel.Soldiers_3 = true;
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Knippel_Soldiers_3":
		dialog.text = "Al menos no te levantas todas las noches. Y pasas más tiempo en el barco que en tierra. ¿Con quién estás hablando?";
		link.l1 = "¡Ah, qué sabes tú de las dificultades del servicio, compañero! ¡Cómo era en la Real Armada!.. No puedes ni imaginarlo.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
		LAi_CharacterDisableDialog(npchar);
		break;
	// <-- Длинные тени старых грехов

	// замечение по обнажённому оружию
	case "SoldierNotBlade":
		// belamour legendary edition если у герой офицер нации -->
		if (IsOfficerFullEquip())
		{
			dialog.text = "Capitán, le pido que guarde sus armas: está prohibido desenfundarlas en nuestra ciudad.";
			link.l1 = LinkRandPhrase("Está bien, lo guardaré...", "Ya hecho.", "Como usted dice...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¡Que te jodan!", "¡Supongo que voy a usarlo!", "Lo guardaré cuando llegue el momento adecuado.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
			break;
		}
		// <-- legendary edition
		dialog.text = LinkRandPhrase("¡Eh, qué pasa con todo ese manejo de armas! ¡Guárdala de inmediato!", "¡Te ordeno que guardes tu arma de inmediato!", "Oye, " + GetAddress_Form(NPChar) + ", ¡deja de asustar a la gente! Guarda tu arma.");
		link.l1 = LinkRandPhrase("Está bien, lo guardaré...", "Ya hecho.", "Como usted diga...");
		link.l1.go = "exit";
		link.l2 = LinkRandPhrase("¡Al diablo contigo!", "¡Supongo que voy a usarlo!", "Lo guardaré cuando llegue el momento adecuado.");
		link.l2.go = "fight";
		npchar.greeting = "soldier_common";
		NextDiag.TempNode = "First Time";
		break;

	case "pirate_fight":
		DialogExit();
		SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		LAi_group_Attack(NPChar, Pchar);
		DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
