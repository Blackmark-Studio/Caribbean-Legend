
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			DialogExit();
		break;

		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"! Disculpe... ¿es usted mariner"+GetSexPhrase("o","a")+"?";
			link.l1 = "Soy el/la capitán "+GetFullName(pchar)+", a su servicio.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "Yo soy Lea. Lea Carno... "+GetSexPhrase("Monsieur","Mademoiselle")+" capitán, ¿hace mucho que llegó? ¿No ha visto en el mar un balandro pesquero llamado 'Cormorán'? Verá... mi marido, Pierre... salió al mar hace dos días y no ha regresado.";
			link.l1 = "¿‘Cormorán’? No, no he visto ninguna embarcación con ese nombre. Lo recordaría. Lamento oír eso, madame. Espero que su esposo esté bien y solo se haya retrasado en el camino.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "¿‘Cormorán’? ¡Ja ja! ¿Ese es el nombre del barco o el apodo de su dueño? Aunque, en fin... No he visto ni uno ni otro.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "No sé qué pensar... Él nunca se retrasaba. Siempre regresaba antes del mediodía. Y ahora... Algo ha pasado. Lo presiento.";
			link.l1 = "Acuda a las autoridades. Enviarán un barco de patrulla para rastrear la costa.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "No sé qué pensar... Él nunca se retrasaba. Siempre regresaba antes del mediodía. Y ahora... Algo ha pasado. Lo presiento.";
			link.l1 = "Acuda a las autoridades. Enviarán un barco de patrulla para rastrear la costa.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "No, "+GetSexPhrase("Monsieur","Mademoiselle")+" capitán, claro que ya hablé con el comandante. ¿Y de qué sirvió? Solo se encogió de hombros... Dijo que no tenía barcos disponibles para buscar a mi esposo\n¿Y yo qué puedo hacer? Solo quedarme aquí, mirar al horizonte, esperar... y tener esperanza.";
			link.l1 = "No se angustie tanto, madame Lea. No es momento de desesperarse. Creo que puedo dedicar un día para ayudarla a buscarlo.";
			link.l1.go = "Agree To Help";
			link.l2 = "¿Y por qué tanto alboroto? Tal vez la brisa matinal lo llevó a los brazos de alguna encantadora dama. Se dará un paseo, tomará aire fresco y volverá.";
			link.l2.go = "bad joke";
			link.l3 = "¿Un consejo? Deje de romperse los ojos mirando al horizonte. Mejor vaya a la taberna de Le François y busque allí a su esposo. Con todo respeto, probablemente solo decidió tomarse un descanso de las obligaciones conyugales, y usted está haciendo una tragedia de ello. Buena suerte en su búsqueda.";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" capitán, yo... no sé ni cómo agradecerle... ¡No se imagina lo que esto significa para mí! Todos solo se encogen de hombros... Pero usted... usted está dispuest"+GetSexPhrase("o","a")+" a ayudar. ¡Gracias!";
			link.l1 = "Todavía no hay nada que agradecer. Mejor dígame dónde solía pescar su esposo. ¿Tenía un lugar fijo o iba variando?";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "¿Una dama encantadora?! ¿De verdad cree que es momento para bromas? ¡Siento que está en peligro... y usted se burla de mi dolor! (llora) Todo en el mundo está en mi contra ahora mismo. Nadie quiere ayudar... Nadie entiende lo difícil que es esto para mí.";
			link.l1 = "Madame Lea, por el amor de Dios, perdone mi falta de tacto. No era mi intención ofenderla. Le prometo que buscaré a su esposo. Solo dígame por dónde empezar.";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "¿Usted...? ¿De verdad quiere ayudarme?";
			link.l1 = "Por supuesto. Es lo mínimo que puedo hacer para redimirme por una broma tan imperdonable e inapropiada.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "Gracias, "+GetSexPhrase("Monsieur","Mademoiselle")+" capitán. Gracias... La verdad, me ha tomado por sorpresa, no sé qué decir...";
			link.l1 = "Aún no me agradezca. Mejor dígame dónde solía pescar su esposo. ¿Tenía un lugar fijo, o cambiaba a menudo?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "Bueno... Pierre... Rara vez decía dónde pescaba exactamente. Lo llamaba 'su secreto'. Pero si eso ayuda a encontrarlo... Tal vez... No sé... Usted sí quiere ayudarme, ¿verdad, "+GetSexPhrase("Monsieur","Mademoiselle")+" capitán?";
			link.l1 = "¿Duda en contarme el lugar secreto de pesca de su esposo? Le aseguro que ese secreto de familia quedará entre nosotros, se lo juro como capitán. Necesito saber dónde empezar a buscar.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "Tiene razón, "+GetSexPhrase("Monsieur","Mademoiselle")+" capitán... Perdón. Ese lugar era muy importante para Pierre. Siempre decía que era su único secreto, su pequeño rincón\nPero sé dónde está. Si eso ayuda a encontrarlo... Él solía pescar en la bahía de Le Marin. Está en la costa sur, no muy lejos de la ciudad. ¡Por favor, encuéntrelo, se lo ruego!";
			link.l1 = "No se preocupe, Lea, todo estará bien. Haré todo lo posible. ¿Tal vez tenía enemigos? ¿Alguien lo amenazó?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "¿Enemigos? ¿Pierre? ¡Es el hombre más bondadoso del mundo! Nunca haría daño a nadie... Solo es un simple pescador. ¿A quién podría haber molestado? No entiendo qué pudo haber pasado... Todo esto es tan extraño... y aterrador...";
			link.l1 = "No se preocupe, madame Lea. Iré de inmediato a buscarlo. Estoy segur"+GetSexPhrase("o","a")+" de que su esposo está bien. Lo traeré de vuelta a sus brazos cuidadosos. Tenga fe.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" capitán, dígame, ¿tiene noticias? ¿Ha averiguado algo? ¿Algo en absoluto?";
			link.l1 = "Lamentablemente, todavía no. ¡Pero sigo buscando, Lea!";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "¿Qué más quiere "+GetSexPhrase("Monsieur","Mademoiselle")+"? ¿No se ha burlado ya bastante de una pobre mujer?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" capitán! ¡Pierre! ¡Qué alegría verlos! ¡Logró encontrarlo!";
			link.l1 = "Lea, permítame presentarle a Pierre Carno, en persona. No puedo decir que esté completamente sano y salvo, pero estoy segur"+GetSexPhrase("o","a")+" de que usted y su cuidado lo curarán en poco tiempo.";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "¡Pierre! ¡Santa Virgen María! ¡Estaba tan preocupada por ti! ¿Dónde has estado? No tienes ni color en el rostro... Estás tan pálido... ¡Ay! ¿¡Y eso qué es!? ¿¡Qué son esas... horribles heridas!? ¡Cortes... y quemaduras!";
			link.l1 = "Todo está bien, mi adorada. Son solo rasguños. ¡Estoy tan feliz de volver a verte! Si no fuera por el capitán... le debo la vida.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" capitán... yo... no sé ni cómo agradecerle... ¡Lo encontró! ¡Salvó a mi Pierre! Gracias... gracias por todo. ¡Que Dios lo bendiga, "+GetSexPhrase("Monsieur","Mademoiselle")+" capitán!";
			link.l1 = "Vamos, no diga más. Ahora lo más importante es que Pierre coma bien y descanse.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		case "Kontr Le Maren":
			dialog.text = "¡Por fin apareciste, "+GetSexPhrase("perro","sinvergüenza")+"! ¿Dónde demonios te habías metido? ¡Llevamos tres días en esta playa, sofocados por el calor! ¿Dónde está nuestra carga?";
			link.l1 = "Parece que la fiesta no empieza sin mí, ¿verdad, caballeros? Bueno, llegué un poco tarde"+GetSexPhrase("","a")+", ¡pero mejor tarde que nunca!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "¿Me está hablando a mí? Hmm, tal vez primero aprenda modales y después podrá hacer preguntas.";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Experiencia ganada", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Experiencia ganada", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", eres un idiota sin sesos! ¡Abre los ojos, tonto — ese ni siquiera es de los nuestros!";
			link.l1 = "¡Argh... Otro perro del gobernador! ¡Era de esperarse! Ya que esta estúpida se metió aquí sola, lancémosla en la cueva con su amiguito. ¡Nos divertiremos un rato! Y de paso le sacaremos todo lo que sepa sobre los planes de su amo.";
			if (pchar.sex == "man")
			{
				link.l1 = "¡Argh... Otro perro del gobernador! ¡Era de esperarse! Ya que este desgraciado se metió aquí solo, lancémoslo en la cueva con su amiguito. Que vea cómo sabemos torturar. ¡Pronto soltará la lengua y contará todos los sucios planes de su amo!";
			}
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.40, 2.38, 5.79, true, -0.49, 0.5, 7.59);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;

		case "Kontr Le Maren1":
			dialog.text = "¿Qué estás soñando, animal? ¡Límpiate la baba! Mejor vendámosla... ya sabes a quién. Por una chica así, soltará una bolsa de monedas, y nosotros vamos a festejar todo un mes.";
			if (pchar.sex == "man")
			{
				dialog.text = "¿Y para qué demonios queremos otro mono más? Presionaremos al compinche y lo soltará todo. Y a este lo matamos aquí mismo para que no estorbe.";
			}
			link.l1 = "¡Mil tiburones se traguen tu panza, Simon! ¡Eres el contrabandista más astuto de todo el archipiélago!";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {	
				notification("Falta una pistola", "NONE");
				link.l2 = "Si ese es el más listo de ustedes, no quiero ni imaginar la tontería que reina en las cabezas de los demás.";
				link.l2.go = "Kontr Le Maren3";
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_1");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				}
				else
				{
				link.l1 = "(Para sí)(Pistolas) Mientras estos charlatanes están distraídos, tengo la oportunidad perfecta para dar un golpe sorpresa.";
				link.l1.go = "murder";
				notification("Prueba superada", SKILL_PISTOL);
				locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
			notification("Habilidad insuficiente (20)", SKILL_PISTOL);
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			sld = CharacterFromID("VPVL_contr_2");
			CharacterTurnByChr(sld, CharacterFromID("Blaze"));
			locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
			}
			link.l2 = "Si ese es el más listo de ustedes, no quiero ni imaginar la tontería que reina en las cabezas de los demás.";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "¡Ahora mismo te arrancaré la lengua, "+GetSexPhrase("cachorro insolente","alimaña asquerosa")+", para que no ladres nunca más!";
			link.l1 = "¿Arrancarla? Bueno, inténtalo, a ver si puedes.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;

		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
				case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... Perdóneme... Mis pensamientos están dispersos como restos flotantes... ¿Ha venido a terminar lo que ellos comenzaron?";
			link.l1 = "¿Es usted Pierre Carno?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "Sí, soy yo. ¿Conoce mi nombre?";
			link.l1 = "Por supuesto. ¿Por qué más estaría aquí?";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "Perdóneme, no entiendo nada... El dolor y el hambre me han quitado la capacidad de pensar con claridad... ¿Por qué vino aquí?";
			link.l1 = "Su fiel esposa ha mantenido vigilia en el muelle desde que usted desapareció, con la esperanza de ver las velas del Cormorán. Su angustia me conmovió profundamente, y no pude quedarme de brazos cruzados. Decidí buscarle yo mismo.";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "Mi esposa... mi querida Lea... Estaba convencido de que jamás volvería a verla...";
			link.l1 = "Ya todo ha pasado. Ella lo espera en el muelle, sin perder la esperanza. Vamos, salgamos de aquí. Le ayudaré a levantarse.";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "Uff... Perdón, "+GetSexPhrase("Monsieur","Mademoiselle")+"... necesito un momento... mis piernas no me responden, están entumecidas... le agradezco de corazón. Si no fuera por usted... ¡Que el cielo lo bendiga!... No me ha dicho su nombre. ¿Cómo debería dirigirme a usted?";
			link.l1 = "Capitán "+GetFullName(pchar)+". Mientras se recupera, cuénteme cómo acabó aquí. ¿Iba a tratar con esos... sujetos?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "¿Yo? Por supuesto que no, capitán. No es mi oficio. Solo soy un pescador. El día había comenzado de maravilla. Estaba pescando en la parte occidental de la bahía. La captura fue espectacular\nTenía tanta prisa por meter los peces en los barriles y lanzar las redes de nuevo que no noté que la corriente llevaba mi bote hacia los arrecifes. Las tablas son tan delgadas como cáscaras de huevo. Bastó un golpe menor y el agua comenzó a inundarlo. El 'Cormorán', ya bien cargado, se hundió rápidamente.";
			link.l1 = "¿Y entonces llegó a la orilla, y los contrabandistas pensaron que era un sabueso del gobernador?";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "Exactamente. Apenas logré llegar a la costa a través de esas malditas olas. Necesitaba secarme, descansar un poco y reunir fuerzas antes de emprender el regreso. Todo ocurrió tan rápido... Cuando finalmente me decidí a ir al pueblo, me topé con esos canallas\nMe tomaron por un agente del gobernador. No tuve tiempo ni de decir una palabra antes de que me ataran y me trajeran aquí. Me torturaron y me dejaron sin comer durante dos días, exigiendo que revelara a todos los espías del gobernador y sus planes. ¡Pero cómo iba a confesar algo que ni siquiera sé!";
			link.l1 = "No eran muy listos, por eso terminaron muertos. En fin, todo eso ya quedó atrás. Es libre. Es hora de que su esposa tenga un poco de alivio — seguramente está agotada de tanto sufrir.";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "Lo único que deseo es abrazarla cuanto antes. Creo que ya puedo caminar.";
			link.l1 = "Entonces no perdamos tiempo.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Capitán, le suplico que se reúna conmigo en la taberna mañana cuando la campana toque las seis. Mi conciencia nunca descansaría si no honrara adecuadamente mi deuda con usted. En este momento... mi mente aún está a la deriva como restos flotantes, incapaz de encontrar palabras dignas de lo que ha hecho. Se lo ruego, venga. Es un asunto que pesa mucho en mi corazón.";
			link.l1 = "No temáis, buen Pierre. Cuando suene la hora señalada, estaré allí para compartir una jarra con vos.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "¡Capitán! ¡Alabados sean los santos! ¡Venga, póngase cómodo en mi mesa!";
			link.l1 = "¡Con gusto!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "¡Alcemos nuestras jarras por vuestra continua buena fortuna y salud!";
			link.l1 = "¡No, no solo a la mía! ¡A vuestra buena salud también! El color ha vuelto a vuestras mejillas desde que os encontré en aquella miserable cueva. ¡Que el diablo se lleve al último!";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "¡Capitán, mi lengua flaquea al buscar palabras lo suficientemente poderosas para expresar mi gratitud sin límites! Cuando otros habrían pasado de largo sin una mirada, usted alteró su rumbo por un extraño—un simple pescador sin importancia. Tal nobleza de espíritu merece su justa recompensa, y quisiera darle todo lo que queda en mi posesión.\nContemplad estos tesoros. Veinte piezas de ámbar dorado como el sol y cinco raros especímenes azules, apreciados por mercaderes a lo largo del Mar Español. Los rescaté de un galeón reclamado por las profundidades. Ahora os servirán a vos.\nAdemás, deseo otorgaros mis instrumentos de navegación y aparejos. Hasta que la Fortuna sonría y me conceda otra embarcación, estas herramientas no sirven más que para acumular polvo.";
			link.l1 = "Acepto vuestra generosa ofrenda con corazón humilde, Pierre. Estos tesoros me servirán bien en las mareas. Sin embargo, el mayor tesoro es que estáis una vez más en vuestro propio umbral, con la vigilia de vuestra fiel esposa finalmente terminada. Las peores tormentas han pasado, y aguas más tranquilas se extienden ante vuestra familia.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Pierre, gracias por vuestra generosidad, pero guardaos todo eso. Ahora os es más útil a vos—para reparar la barca, comprar aparejos, redes, barriles. Me basta con vuestra gratitud y saber que estáis de nuevo con vuestra esposa. ¡Cuidaos el uno al otro!";
			link.l2.go = "PierWontGift1";
		break;

		case "PierTakeGift":
			dialog.text = "Mi mente aún da vueltas como un barco en una tempestad cuando medito sobre las pruebas que he soportado. ¡Bebamos profundamente por nuevos comienzos para mi humilde hogar y por el noble corazón que late en vuestro pecho, Capitán!";
			link.l1 = "¡Y por la Dama Fortuna misma, Pierre! ¡Que reparta su caprichosa sonrisa sobre todos nosotros en igual medida!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;
		
		case "PierWontGift1":
			dialog.text = "Capitán, no puedo dejar esta deuda sin pagar... Me arrancaste de las mismas fauces de la muerte, y estoy a tu sombra como un hombre que debe cada uno de sus futuros alientos a otro. Ya que rechazas mis humildes ofrendas, al menos permitidme compartir los secretos de las aguas poco profundas con vuestra tripulación—cómo leer las aguas, dónde se reúnen los peces con las mareas cambiantes. Tal conocimiento mantendrá carne fresca en vuestra cocina y ahorrará a vuestra bolsa el coste de provisiones cuando toquéis tierra. ¿Qué decís a tal arreglo?";
			link.l1 = "¡Ahora esa es una proposición digna de consideración! Como dicen los viejos lobos de mar, dale a un hombre un pescado y cenará por un día, pero enséñale dónde lanzar su red, ¡y festejará hasta su viaje final bajo las olas!";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "¡Sabia sabiduría de un marinero experimentado! Mi espíritu se eleva al saber que puedo ser de utilidad. ¿Otro trago de ron para sellar nuestro pacto?";
			link.l1 = "¡A vientos favorables y mares propicios para vos y los vuestros, Pierre! ¡Que vuestras redes siempre suban rebosantes!";
			link.l1.go = "ZastavkaVPVL";
		break;

		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Pasaron cuatro horas...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
				int foodDays = CalculateShipFood(&pchar);
				dialog.text = "¡Por la barba de Neptuno! ¡Ese ron está potente! Otro trago y... hik... ¡estaré cantando una tonada que despierte al mismísimo kraken! ¡Hasta el puerto entero oirá mi voz!";
				link.l1 = "Guarda esa canción para aguas más tranquilas, Pierre. Hik... Ya me dan ganas de unirme al coro, pero... eh... los deberes me llaman. ¡Cuídese... hik... y cuide bien de su esposa!";
				link.l1.go = "PierTalkTavern4";
				WaitDate("", 0, 0, 0, 4, 10);
				LAi_AlcoholSetDrunk(pchar, 71, 5600);
				notification("Consumo de provisiones del barco -15%", "None");
			}
			else
			{
				dialog.text = "¡Por la barba de Neptuno! ¡Ese ron está potente! Otro trago y... hik... ¡estaré cantando una tonada que despierte al mismísimo kraken! ¡Hasta el puerto entero oirá mi voz!";
				link.l1 = "Guarda esa canción para aguas más tranquilas, Pierre. Hik... Ya me dan ganas de unirme al coro, pero... eh... los deberes me llaman. ¡Cuídese... hik... y cuide bien de su esposa!";
				link.l1.go = "PierTalkTavern4";
				WaitDate("", 0, 0, 0, 4, 10);
				LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "Ah, Capitán... ¡tenéis el corazón de un verdadero marinero! Mi deuda nunca podrá ser saldada, ¿sabéis? Si alguna vez volvéis a fondear en nuestro puerto... nuestro hogar será vuestro hogar, como si hubiéramos nacido de la misma madre. ¡Palabra de honor! ¡Brindaremos juntos de nuevo cuando Fortuna os traiga de vuelta a estas costas!";
			link.l1 = "¡Mantén el rumbo, Pierre! Hik... me voy antes de que las piernas me fallen.";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
			CloseQuestHeader("VPVL");
		break;

		case "Exit2":
			DialogExit()
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "Too-o-o, the deep blue se-e-ea, and the trade winds fair... hik... to the fishin' grounds we sa-a-ail at first light! ¡Capitán! ¿Aún estáis aquí? ¡Tabernero! ¡El mejor ron para esta mesa!";
			link.l1 = "¡Ya zarpo, Pierre! Hik... mientras todavía pueda encontrar mi barco.";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = "¡Capitán "+pchar.name+"! ¡Qué alegría veros! ¿Qué tal un trago de ron por este reencuentro?";
			link.l1 = "Yo también me alegro de veros, Pierre. Pero me temo que tendré que declinar esta vez. El deber me exige la mente clara. Tal vez la próxima vez.";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "Claro, claro, Capitán. Primero el deber, luego el descanso. Espero que nos volvamos a ver, ¡y entonces sin duda brindaremos!";
			link.l1 = "Seguro que sí, Pierre. ¡Hasta la próxima!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "¡Capitán! ¿Ya os habéis liberado de vuestros asuntos?";
			link.l1 = "Por desgracia no, Pierre. El deber no me suelta aún.";
			link.l1.go = "Exit";
		break;
	}
}   