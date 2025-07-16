// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Un error evidente. Infórmalo a los desarrolladores.";
		link.l1 = "Oh, lo haré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// квестодатель
	case "citizen":
		DelMapQuestMarkCity("Baster");
		LAi_SetImmortal(npchar, false);
		LAi_RemoveLoginTime(npchar);
		dialog.text = "Saludos, capitán! Tengo una propuesta de negocio que encontrará muy interesante.";
		link.l1 = "Continúa, monsieur.";
		link.l1.go = "citizen_1";
		break;

	case "citizen_1":
		dialog.text = "Quiero contratar tu nave para un trabajo de transporte desde Guadalupe hasta el Continente Español.";
		link.l1 = "¿Quieres navegar allí como pasajero?";
		link.l1.go = "citizen_2";
		link.l2 = "¿La Española? Paso. No somos realmente amigos de los españoles. Te sugiero que encuentres otro tonto.";
		link.l2.go = "citizen_no";
		break;

	case "citizen_no":
		dialog.text = "Como usted diga, capitán, aunque no es un viaje de alto riesgo. Adiós.";
		link.l1 = "Adiós.";
		link.l1.go = "citizen_exit";
		break;

	case "citizen_no_1":
		dialog.text = "Como desees, capitán. ¡Adiós!";
		link.l1 = "Adiós.";
		link.l1.go = "citizen_exit";
		break;

	case "citizen_exit":
		DialogExit();
		chrDisableReloadToLocation = false;
		npchar.lifeday = 0;
		DelLandQuestMark(npchar); // Rebbebion, снять марку
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;

	case "citizen_2":
		dialog.text = "No del todo, monsieur. Un pasajero es un hombre dependiente de la voluntad del capitán. Quiero contratarte a ti, a tu tripulación y a tu barco, para llevarme junto con dos amigos míos a Panamá.";
		link.l1 = "¿A Panamá? ¿Cómo? ¿Quieres navegar alrededor de todo el continente?";
		link.l1.go = "citizen_3";
		break;

	case "citizen_3":
		dialog.text = "¡Ja, ja, ja! Buena broma, capitán. Por supuesto que no. Todo lo que tienes que hacer es llevarnos a la Bahía de los Mosquitos, que no está lejos de Portobello. Nos las arreglaremos para llegar a Panamá por nuestra cuenta, no será nuestro primer recorrido por la jungla.";
		link.l1 = "¿Qué hay del pago?";
		link.l1.go = "citizen_4";
		break;

	case "citizen_4":
		dialog.text = "Dos cofres de doblones. Trescientas piezas. Recibirás uno por adelantado una vez que estemos a bordo. El segundo cofre será tuyo tan pronto como lleguemos a nuestro destino.";
		link.l1 = "Una recompensa seria por un trabajo tan fácil. ¿Cuál es el truco, buen hombre?";
		link.l1.go = "citizen_5";
		break;

	case "citizen_5":
		dialog.text = "Capitán, el tiempo es oro, mis amigos y yo no lo tenemos. Tenemos que zarpar de aquí esta noche y debemos estar allí en diez días. Este será nuestro segundo período. Entonces, ¿estás dentro?";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "citizen_6";
		link.l2 = "Lo siento, monsieur, pero su propuesta me suena demasiado sospechosa. Encuéntrese otro tonto.";
		link.l2.go = "citizen_no_1";
		break;

	case "citizen_6":
		dialog.text = "Espléndido. Mis amigos están en la jungla en este momento, les informaré sobre nuestro acuerdo. Nos encontrarás en la Playa Capster esta noche a las diez. ¡No llegues tarde, Capitán!";
		link.l1 = "Está bien. Playa Capster, esta noche, a las diez.";
		link.l1.go = "citizen_7";
		break;

	case "citizen_7":
		dialog.text = "Un minuto, capitán, ni siquiera nos presentamos. Mi nombre es Bertrand Pinette. Y usted es...";
		link.l1 = "" + GetFullName(pchar) + ". Capitán " + GetFullName(pchar) + " . Nos vemos, monsieur Pinette.";
		link.l1.go = "citizen_8";
		break;

	case "citizen_8":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", 20.0);
		AddQuestRecord("FMQ_Guadeloupe", "1");
		pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
		pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
		pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
		pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
		pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
		pchar.quest.FMQG_Capster.win_condition.l3 = "location";
		pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
		pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
		SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
		pchar.questTemp.FMQG = "begin";
		pchar.GenQuest.SmugglersBlock = "baster_tavern";
		DelLandQuestMark(npchar); // Rebbebion, снять марку
		break;

	case "citizen_9":
		DelLandQuestMark(npchar);
		dialog.text = "Capitán " + GetFullName(pchar) + ", ahí estás. ¿Estamos listos para zarpar?";
		link.l1 = "Sí. Bienvenido a bordo.";
		link.l1.go = "citizen_10";
		break;

	case "citizen_10":
		dialog.text = "Muy bien. Acepta tu adelanto - un cofre lleno de doblones. Y recuerda - solo tienes diez días para llevarnos a nuestro destino. ¡Ni un día más!";
		link.l1 = "Recuerdo los términos. No te preocupes, llegaremos a tiempo. Tomen asiento.";
		link.l1.go = "citizen_11";
		break;

	case "citizen_11":
		DialogExit();
		GiveItem2Character(pchar, "chest");
		Log_Info("Has recibido un cofre lleno de doblones");
		PlaySound("interface\important_item.wav");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
		for (i = 2; i <= 3; i++)
		{
			sld = characterFromId("FMQG_pass_" + i);
			LAi_ActorRunToLocation(sld, "officers", "sea_" + i, "none", "", "", "", 10.0);
		}
		pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
		pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
		pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
		if (bImCasual)
		{
			NewGameTip("Modo exploración: se duplica la duración de las misiones");
			SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
			SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
		}
		else
		{
			SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
			SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
		}
		pchar.questTemp.FMQG = "sail";
		DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;

	case "citizen_12":
		dialog.text = "Así que, Capitán, has cumplido completamente tu parte del trato. Es mi turno ahora. Acepta este cofre junto con nuestra más profunda gratitud.";
		link.l1 = "Un placer hacer negocios contigo, monsieur.";
		link.l1.go = "citizen_13";
		break;

	case "citizen_13":
		GiveItem2Character(pchar, "chest");
		Log_Info("Has recibido un cofre lleno de doblones");
		PlaySound("interface\important_item.wav");
		AddCharacterExpToSkill(pchar, "Sailing", 200);	  // навигация
		AddCharacterExpToSkill(pchar, "Leadership", 200); // авторитет
		AddCharacterExpToSkill(pchar, "Sneak", 100);	  // скрытность
		dialog.text = "Igualmente. Adiós, capitán " + GetFullName(pchar) + ".";
		link.l1 = "¡Adiós!";
		link.l1.go = "citizen_14";
		break;

	case "citizen_14":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
		for (i = 2; i <= 3; i++)
		{
			sld = characterFromId("FMQG_pass_" + i);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			sld.lifeday = 0;
		}
		AddQuestRecord("FMQ_Guadeloupe", "6");
		CloseQuestHeader("FMQ_Guadeloupe");
		pchar.questTemp.FMQG = "pause";
		pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
		pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
		pchar.quest.FMQG_Continue.win_condition.l2 = "location";
		pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
		pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
		/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
		pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
		pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
		pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
		// SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // лесник - открыть оружие снова.
		AddMapQuestMarkCity("baster", false);
		break;

	case "citizen_12a":
		dialog.text = "Entonces, capitán, aquí estamos. Has cumplido solo la mitad de tu parte del trato, así que haré lo mismo. Guarda tu adelanto como pago completo. Espero que no te opongas, fue tu culpa después de todo.";
		link.l1 = "No puedo decir que me guste esto, pero admito que tienes razón. Partamos nuestros caminos ahora.";
		link.l1.go = "citizen_13a";
		break;

	case "citizen_13a":
		AddCharacterExpToSkill(pchar, "Sailing", 50);	 // навигация
		AddCharacterExpToSkill(pchar, "Leadership", 50); // авторитет
		AddCharacterExpToSkill(pchar, "Sneak", 50);		 // скрытность
		dialog.text = "De todos modos, gracias por el servicio, capitán " + GetFullName(pchar) + "¡Adiós!";
		link.l1 = "Adiós.";
		link.l1.go = "citizen_14";
		break;

	case "citizen_15":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("bridgetown");
		dialog.text = "¡Oh! ¡Qué encuentro! " + TimeGreeting() + ", " + GetFullName(pchar) + "¡¿Pero cómo?!";
		link.l1 = TimeGreeting() + ", monsieur Pinette. No fue fácil encontrarte.";
		link.l1.go = "citizen_16";
		break;

	case "citizen_16":
		sld = characterFromId("Baster_usurer");
		dialog.text = "¿Y cuál es la razón, capitán?";
		link.l1 = "Mi buen señor, hay un hombre llamado " + GetFullName(sld) + " y está muy ansioso por verte. Supongo que sabes por qué.";
		link.l1.go = "citizen_17";
		break;

	case "citizen_17":
		sld = characterFromId("Baster_usurer");
		dialog.text = "Por supuesto que sí, pero tú, mi querido Capitán, también debes saber que no estoy ansioso por ver al monsieur " + GetFullName(sld) + " en absoluto. ¿Eres su cazarrecompensas? No lo entiendo.";
		link.l1 = "Por desgracia, pero eso es quien soy en este momento y no estoy contento por ello. Cometí un error y ahora monsieur " + GetFullName(sld) + ", maldito sea, me ha presentado con una elección. O es tu glorioso regreso a Guadalupe o es mi trasero como cómplice en tu pequeña empresa de liberar a don Carlos de Milyar. Eso me dolerá, lo sabes.";
		link.l1.go = "citizen_18";
		break;

	case "citizen_18":
		sld = characterFromId("Baster_usurer");
		dialog.text = "¡Ah, ese bastardo! ¡Es una manera muy pecaminosa de chantajear a la gente!.. Entonces, Capitán, ¿qué va a ser, vas a tomar una decisión o vas a permitir que alguien así te chantajee?";
		link.l1 = "¿Y qué piensas? Creo que vienes conmigo a Basse-Terre.";
		link.l1.go = "citizen_19";
		link.l2 = "¿Tengo elección aquí?";
		link.l2.go = "citizen_25";
		break;

	case "citizen_19":
		dialog.text = "Oh, debo decepcionarte, Capitán. No tengo deseo de abordar tu hermoso barco. No lograrás nada por la fuerza aquí, el lugar está rodeado de guardias y gritaré por ayuda en caso de que muestres alguna intención violenta. Claro, puedes intentar apuñalarme, pero nuestro buen amigo no obtendrá ninguna moneda de un cadáver frío. Así que, la forma más inteligente para ti en este momento es dejarme en paz. Te permitiré irte ileso. ";
		link.l1 = "¿Realmente crees que me iré así nomás después de todo lo que ha pasado? ¡Me has arrastrado a este lío, maldito, es hora de pagar!";
		link.l1.go = "citizen_20";
		link.l2 = "Tienes razón, supongo. Me gusta la idea de apuñalarte, pero es inútil. Ni siquiera sueñes con que esto es el final. Me voy ahora a Basse-Terre, donde informaré a nuestro buen amigo sobre tu paradero. Y luego enviará hombres enmascarados tras de ti.";
		link.l2.go = "citizen_21";
		break;

	case "citizen_20":
		dialog.text = "¡A-ah! ¡Soldados! ¡Ayuda!!!";
		link.l1 = "... ";
		link.l1.go = "citizen_fight";
		break;

	case "citizen_21":
		dialog.text = "Pero por supuesto. Dile a tu jefe que mantenga a sus hombres enmascarados a raya - me estoy volviendo muy popular estos días. Adiós, Capitán.";
		link.l1 = "... ";
		link.l1.go = "citizen_22";
		break;

	case "citizen_22":
		DialogExit();
		LAi_SetActorType(npchar);
		AddQuestRecord("FMQ_Guadeloupe", "19");
		pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
		pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
		pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;

	case "citizen_23":
		DelLandQuestMark(npchar);
		dialog.text = "¡Espera! ¡Me rindo! ¡Me rindo!";
		link.l1 = "¡Exactamente! ¡Ahora suelta tu arma y marcha hacia el barco!";
		link.l1.go = "citizen_24";
		break;

	case "citizen_24":
		DialogExit();
		chrDisableReloadToLocation = false;
		RemoveAllCharacterItems(npchar, true);
		DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;

	case "citizen_25":
		dialog.text = "Siempre hay una elección, capitán. Hasta donde entiendo, ¿no me estarías cazando si no hubiera amenazas de ese banquero?";
		link.l1 = "Exactamente.";
		link.l1.go = "citizen_26";
		break;

	case "citizen_26":
		dialog.text = "Bien. Entonces te organizaré una forma sólida de cerrarle la boca. Escribamos una carta que llevarás a tu patrón. Dile que si alguna vez empieza a hablar, el gobernador de Guadalupe se enterará del hombre que planeó e invirtió en la desaparición del Courage, un bergantín mensajero en una misión para transportar un gran lote de diamantes.";
		link.l1 = "Hum. Creo que empiezo a entender, monsieur Pinette.";
		link.l1.go = "citizen_27";
		break;

	case "citizen_27":
		dialog.text = "Me alegra que seas tan listo, Capitán. De Lion personalmente clavará la cabeza del astuto avaro en las puertas de la ciudad si descubre la verdad detrás de la desaparición del Courage. En esta carta que estoy a punto de escribir, encontrarás pruebas que calmarán al chantajista. Dame un minuto para conseguir mi pluma.";
		link.l1 = "Está bien...";
		link.l1.go = "citizen_28";
		break;

	case "citizen_28":
		LAi_Fade("", "");
		GiveItem2Character(pchar, "letter_baker");
		ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
		dialog.text = "(escribiendo) Aquí, tómalo. Hay dos cartas similares en este paquete. Dale una al banquero, que la disfrute. Guarda la otra para ti y mantenla oculta.";
		link.l1 = "¿Es la información confiable?";
		link.l1.go = "citizen_29";
		break;

	case "citizen_29":
		sld = characterFromId("Baster_usurer");
		AddLandQuestMark(sld, "questmarkmain");
		AddMapQuestMarkCity("Baster", false);
		dialog.text = "Puedo jurarlo, me has ayudado y ahora te ayudaré yo a ti. Ten la seguridad de que el chantajista te dejará en paz una vez que lea este testamento. Ah, sí... Una cosa más, capitán. Ya que resolvimos esto pacíficamente... Tengo un alijo y te diré dónde encontrarlo si me prometes mantenerte alejado de mis operaciones en el futuro. De todas formas, no me dejarán poner un pie en Guadalupe nunca más.";
		link.l1 = "Si la carta funciona como se pretende, entonces, por supuesto, puedo prometerte eso.";
		link.l1.go = "citizen_30";
		break;

	case "citizen_30":
		dialog.text = "Entonces es un trato. Busca entre las rocas dentro de la cueva de Guadalupe. Que te sirva como modesta compensación por tus problemas. Que Dios te acompañe, capitán.";
		link.l1 = "Lo mismo para usted, monsieur Pinette.";
		link.l1.go = "citizen_31";
		break;

	case "citizen_31":
		DialogExit();
		pchar.questTemp.FMQG = "letter";
		AddQuestRecord("FMQ_Guadeloupe", "24");
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 1;
		break;

	case "citizen_fight":
		chrDisableReloadToLocation = true;
		LAi_group_Delete("EnemyFight");
		DialogExit();
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		AddDialogExitQuest("MainHeroFightModeOn");
		DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
		pchar.questTemp.FMQG = "fail";
		AddQuestRecord("FMQ_Guadeloupe", "18");
		CloseQuestHeader("FMQ_Guadeloupe");
		break;

	// вестовой к ростовщику
	case "cureer":
		DelMapQuestMarkCity("baster");
		LAi_SetImmortal(npchar, false);
		DelLandQuestMark(npchar);
		npchar.lifeday = 0;
		dialog.text = "¡Saludos, monsieur! Usted es el capitán " + GetFullName(pchar) + ", ¿correcto?";
		link.l1 = "Correcto. ¿Qué puedo hacer por ti?";
		link.l1.go = "cureer_1";
		break;

	case "cureer_1":
		sld = characterFromId("BasTer_usurer");
		dialog.text = "Monsieur " + GetFullName(pchar) + ", el dueño del banco de Basse-Terre te pide que lo visites lo antes posible. Me ordenó que revisara nuestra oficina del puerto todos los días para asegurarse de que tu llegada no pase desapercibida.";
		link.l1 = "Interesante, ¿y por qué estaría tan ansioso por verme?";
		link.l1.go = "cureer_2";
		break;

	case "cureer_2":
		dialog.text = "Monsieur " + GetFullName(sld) + " te dirá personalmente por qué. Espero que no rechaces su invitación.";
		link.l1 = "Hm.. Bien. Estos banqueros son gente poderosa y nunca pierden tiempo con peces pequeños. Iré a ver al hombre lo antes posible.";
		link.l1.go = "cureer_3";
		break;

	case "cureer_3":
		dialog.text = "Gracias, Capitán. ¡Adiós!";
		link.l1 = "Adiós.";
		link.l1.go = "cureer_4";
		break;

	case "cureer_4":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
		LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
		LocatorReloadEnterDisable("Baster_town", "gate_back", true); // закрыть выходы из города
		pchar.questTemp.FMQG = "continue";
		pchar.quest.FMQG_Block.over = "yes";
		pchar.quest.FMQG_Block1.over = "yes";
		AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;

	// Жан Дено
	case "Juan":
		dialog.text = "¡Argh! ¡Malditos sinvergüenzas! No puede ser un encuentro casual...";
		link.l1 = "Es cierto, Jean... perdón, quise decir Juan. Te he localizado. Ahora, ¿serías tan amable de meterte en mi bodega de carga? Desahógate un poco y hablaremos.";
		link.l1.go = "Juan_1";
		break;

	case "Juan_1":
		DialogExit();
		Lai_SetPlayerType(pchar);
		DeleteAttribute(npchar, "DontRansackCaptain");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
		pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
		pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
		AddQuestRecord("FMQ_Guadeloupe", "14");
		pchar.questTemp.FMQG = "juan_capture";
		DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;

	case "Juan_2":
		dialog.text = "";
		link.l1 = "He cumplido mi parte del trato. Ahora es tu turno. Dispárale y ten en cuenta las consecuencias de mentir.";
		link.l1.go = "Juan_3";
		break;

	case "Juan_3":
		dialog.text = "Encontrarás a Bertrand Pinette en Barbados, en la plantación principal, para ser más específico. Iba a continuar sus operaciones allí. El supervisor de la plantación es amigo suyo.";
		link.l1 = "¿Qué tipo de operaciones?";
		link.l1.go = "Juan_4";
		break;

	case "Juan_4":
		dialog.text = "Lo mismo que tenía en Guadalupe. Comercio semi-legal, contrabando, esclavos. Creo que tiene la intención de hacer negocios de esclavos y comercio de azúcar, ¿por qué si no se habría mudado a una plantación?";
		link.l1 = "Ya veo. ¿Tiene algún patrón entre las autoridades inglesas?";
		link.l1.go = "Juan_5";
		break;

	case "Juan_5":
		dialog.text = "Supongo. Un personaje curioso, él es. Siempre tiene amigos por todas partes.";
		link.l1 = "¿Algo más?";
		link.l1.go = "Juan_6";
		break;

	case "Juan_6":
		dialog.text = "¿Como qué? Astuto e inteligente, siempre sabe cosas, siempre tiene un as en la manga. No tuve mucho tiempo para aprender más sobre él.";
		link.l1 = "Entendido. Bien, tengo que navegar a Bridgetown. Eres libre de irte, don Juan. Ni se te ocurra advertir a Pinette. Si no lo encuentro allí, será tu trasero en juego de nuevo.";
		link.l1.go = "Juan_7";
		break;

	case "Juan_7":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
		npchar.lifeday = 0;
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		pchar.questTemp.FMQG = "headhunter_pinett";
		AddQuestRecord("FMQ_Guadeloupe", "17");
		// Пинетта - в Бриджтаун
		sld = characterFromId("FMQG_pass_1");
		ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
		sld.Dialog.currentnode = "citizen_15";
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		AddMapQuestMarkCity("bridgetown", false);
		break;

	case "killer":
		dialog.text = "Lo siento, amigo. Nada personal. Sabes demasiado, ese es tu problema.";
		link.l1 = "...";
		link.l1.go = "killer_1";
		break;

	case "killer_1":
		DialogExit();
		AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза
		LAi_group_Delete("EnemyFight");
		int n = 2;
		if (MOD_SKILL_ENEMY_RATE > 6)
			n = 3;
		for (i = 1; i <= n; i++)
		{
			sld = characterFromId("FMQG_killer_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
