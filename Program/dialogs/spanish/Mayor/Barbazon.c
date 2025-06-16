// Жак Барбазон в Ле Франсуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	//--> -----------------------------------------------блок angry-------------------------------------------------
	if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
	{
		npchar.angry.ok = 1;
		if (!CheckAttribute(npchar, "angry.first")) // ловушка первого срабатывания
		{
			NextDiag.TempNode = NextDiag.CurrentNode;
			Dialog.CurrentNode = "AngryExitAgain";
			npchar.angry.first = 1;
		}
		else
		{
			switch (npchar.angry.kind) // сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
			{
			case "repeat":
				if (npchar.angry.name == "Firsttime")
					Dialog.CurrentNode = "AngryRepeat_1";
				if (npchar.angry.name == "I_know_you_good")
					Dialog.CurrentNode = "AngryRepeat_2";
				break;
			}
		}
	}
	//<-- -------------------------------------------блок angry------------------------------------------------------

	switch (Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча---------------------------------------
	case "First time":
		dialog.text = NPCStringReactionRepeat("¿Tienes algo que decirme? ¿No? ¡Entonces lárgate de aquí!", "Creo que me he explicado claramente, deja de molestarme.", "¡Aunque ya me he explicado, sigues molestándome!", "Está bien, me estoy cansando de esta grosería.", "repeat", 3, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Ya me estoy yendo.", "Claro, Jacques...", "Lo siento, Jacques...", "¡Ay...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";

		if (sti(pchar.GenQuest.Piratekill) > 20)
		{
			dialog.text = RandPhraseSimple("¿Estás loco? ¿Querías jugar a ser carnicero? Todos los piratas están enfadados contigo, chico, será mejor que dejes este lugar...", "  Parece que te has vuelto loco, muchacho. ¿Querías estirar un poco las manos? Sin ofender, pero no tienes nada que hacer aquí. ¡Piérdete! ");
			link.l1 = RandPhraseSimple("Escucha, quiero arreglar la situación...", "Ayúdame a resolver este problema...");
			link.l1.go = "pirate_town";
			break;
		}

		//----------------------------------Сага - искушение Барбазона---------------------------------------
		if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
		{
			link.l1 = "Necesito hablar contigo, Jacques... En privado.";
			link.l1.go = "Temptation";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
		{
			link.l1 = "Vengo de Saint Martin, Jacques...";
			link.l1.go = "Temptation_6";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
		{
			link.l1 = "¿Y cuándo vas a dejar de ladrar y empezar a hablar como un hombre, Jacques? ¿No esperabas verme?";
			link.l1.go = "terrax";
		}

		// поручение капитана - выкуп
		if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
		{
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Estoy aquí por tu prisionero.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
			}

			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
			{
				link.l1 = "Hola, Jacques, estoy aquí por tu misión.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar, "GenQuest.CaptainComission.vikupzaplatil"))
			{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
				link.l1 = "Estoy aquí por tu prisionero.";
				link.l1.go = "CapComission6";
			}
		}
		if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
		{
			link.l1 = "He oído que estás involucrado en negocios relacionados con prisioneros...";
			link.l1.go = "Marginpassenger";
		}
		break;

	case "Exit":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	case "I_know_you_good":
		dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ". ¿Qué necesitas esta vez?", "¿Has olvidado algo? Estoy escuchando.", "¿Cuánto tiempo durará esto?... Si no tienes nada que hacer, ¡entonces no molestes a los demás!", "¡Me has pedido que sea educado! ¡Pero exijo lo mismo de ti!", "repeat", 10, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("No es nada. Solo una visita.", "Nada...", "Está bien...", "Tienes razón. Lo siento.", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		NextDiag.TempNode = "I_know_you_good";

		if (sti(pchar.GenQuest.Piratekill) > 20)
		{
			dialog.text = RandPhraseSimple("¿Estás loco? ¿Querías jugar al carnicero? Todos los piratas están enfadados contigo, chico, será mejor que te largues de aquí...", "  Parece que te has vuelto loco, chico. ¿Querías estirar un poco las manos? Sin ofender, pero no tienes nada que hacer aquí. ¡Piérdete!");
			link.l1 = RandPhraseSimple("Escucha, quiero arreglar la situación...", "Ayúdame a resolver este problema...");
			link.l1.go = "pirate_town";
			break;
		}

		// поручение капитана - выкуп
		if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
		{
			link.l1 = "Estoy aquí por tu prisionero.";
			link.l1.go = "CapComission1";
			DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
		}
		if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") //  правка лесник,новая проверка ,исключающая тут же сдачу задания
		{
			link.l1 = "Hola, Jacques, es sobre tu misión.";
			link.l1.go = "CapComission3";
		}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "Estoy aquí por tu prisionero.";
				link.l1.go = "CapComission6";
			}*/
		if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
		{
			link.l1 = "He oído que estás involucrado en negocios relacionados con prisioneros...";
			link.l1.go = "Marginpassenger";
		}
		break;

		//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
	case "Temptation":
		dialog.text = "¿Sabes que molestarme es arriesgado? Bien, te escucho.";
		link.l1 = "Tengo una deuda. Una grande. El momento de pagar es pronto y no tengo monedas. La buena gente ha susurrado que tienes un talento para hacer planes y siempre sabes dónde agarrar un gran botín...";
		link.l1.go = "Temptation_1";
		break;

	case "Temptation_1":
		dialog.text = "¡Escucha, chico! Soy Jacques el Bondadoso solo para aquellos que me son leales. Soy Barbazón para los demás y a veces el mismo Lucifer. ¿Cómo podría saber que puedo confiar en ti?";
		link.l1 = "Prueba conmigo. ¡Juro que no te arrepentirás!";
		link.l1.go = "Temptation_2";
		break;

	case "Temptation_2":
		dialog.text = "Mm... Supongo que sabes lo que Jacques el Bondadoso le hace a la gente que lo engaña, ¿verdad? De cualquier manera, no te confundiré con detalles terribles. Tengo una pequeña misión. Si tienes éxito, entonces todos tus problemas financieros desaparecerán.";
		link.l1 = "No dudes de mí, he estado en muchas peleas y...";
		link.l1.go = "Temptation_3";
		break;

	case "Temptation_3":
		dialog.text = "¡Cállate y escúchame! Hace unas semanas, una patrulla holandesa capturó a uno de mis empleados no lejos de Saint Martin. Me estaba entregando seda holandesa. Es muy rara, los holandeses traen aquí solo pequeños lotes para las necesidades de la armada de la Compañía.\nAsí que, logré morder seis fardos de seda y Simon Morel se suponía que los traería en su bergantín 'Salt Dog', pero se topó con una patrulla holandesa por accidente. O no por accidente. Eso es lo que dijo el navegante de Morel, me contó que fue el único que sobrevivió a la pelea.\nTambién me dio el cuaderno de bitácora de Morel que confirma la historia. Según el cuaderno, Morel había arrojado la seda durante un intento de escape. Es extraño, ¿no? La seda es liviana. Deberían haber arrojado sus cañones, de todos modos no tenían ninguna posibilidad contra la patrulla.";
		link.l1 = "Algo anda muy mal aquí.";
		link.l1.go = "Temptation_4";
		break;

	case "Temptation_4":
		dialog.text = "Todo es posible. Muchos hombres valientes trabajan para mí y muchos menos inteligentes. Sin ofender, je. Debes revisar el lugar donde Morel se deshizo de la carga. Está a 21 grados 10' Norte y 61 grados 30' Oeste según el cuaderno de bitácora del capitán.\nLos holandeses enrollan la seda alrededor de barras de corcho, así que los fardos deben estar aún sobre el agua. Debe haber seis fardos. Zarpa inmediatamente, el tiempo es crucial.";
		link.l1 = "¡Estoy en camino!";
		link.l1.go = "Temptation_5";
		break;

	case "Temptation_5":
		DialogExit();
		SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		pchar.quest.BarbTemptation.win_condition.l1 = "location";
		pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
		pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
		pchar.questTemp.Saga.BarbTemptation = "silk";
		AddQuestRecord("BarbTemptation", "2");
		break;

	case "Temptation_6":
		dialog.text = "¡Estupendo! ¿Has encontrado mi seda?";
		link.l1 = "Sí, seis de ellos como dijiste.";
		link.l1.go = "temptation_wrong";
		if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
		{
			link.l2 = "Sí. Pero había más de los que dijiste, nueve de ellos, no seis. Los traje a todos aquí, tu parte es averiguar cómo pudo suceder esto.";
			link.l2.go = "temptation_right";
		}
		break;

	case "temptation_wrong":
		dialog.text = "Respuesta equivocada. Deberían haber sido nueve fardos. Y si encontraste seis de ellos, entonces debiste haber encontrado el resto. Así que eres o una rata o solo un idiota perezoso. Me debes tres fardos de seda y tres más como... 'compensación moral' por intentar engañarme.";
		if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
		{
			link.l1 = "¡Qué listillo! Lo recordaré. Aquí tienes tu seda y olvidemos mi error.";
			link.l1.go = "temptation_wrong_1";
		}
		link.l2 = "Me han dicho que había seis pacas, ni una más. Te he dado todo lo que encontré y me importa un carajo lo que pienses. No tengo más seda.";
		link.l2.go = "temptation_wrong_2";
		break;

	case "temptation_wrong_1":
		RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
		dialog.text = "Está bien. Espero que no vuelva a suceder porque quiero darte una tarea importante. ¿Cuánto dinero quieres ganar?";
		link.l1 = "El dinero siempre es bienvenido, por ahora cincuenta mil pesos estarían bien.";
		link.l1.go = "junior";
		break;

	case "temptation_wrong_2":
		dialog.text = "¡Oh, así es como hablas ahora! No te saldrás con la tuya. Te he advertido: ¡maldita sea, no intentes engañarme! ¡Guardias! ¡Hay una maldita rata en la residencia!";
		link.l1 = "¡Mierda!";
		link.l1.go = "temptation_wrong_fight";
		break;

	case "temptation_wrong_fight":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetWarriorType(npchar);
		ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
		LAi_SetImmortal(npchar, true);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		for (i = 1; i <= 3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_" + i, "citiz_4" + (i + 6), "man", "man", 80, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
			ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "temptation_right":
		RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
		dialog.text = "Buen trabajo. Te estaba probando por codicia y has pasado mi prueba. Debía haber nueve fardos. Uno de ellos es tuyo. Ahora podemos hablar en serio. ¿Cuánto dinero necesitas?";
		link.l1 = "El dinero siempre es bienvenido, por ahora cincuenta mil pesos estarían bien.";
		link.l1.go = "junior";
		break;

	case "junior":
		dialog.text = "Tienes una oportunidad de ganar aún más. Un hombre serio me ha pedido encontrar a un tipo confiable como tú para una misión delicada y peligrosa. Este hombre es muy rico y te recompensará adecuadamente si no le fallas.";
		link.l1 = "Estoy listo.";
		link.l1.go = "junior_1";
		break;

	case "junior_1":
		dialog.text = "Está bien. Escucha ahora. Tienes que encontrar a su agente llamado 'Canalla'. Es el capitán de la polacra 'Marlin', eso es todo lo que sé de él. Lo encontrarás en Kapsterville. La contraseña es 'la caza ha comenzado'. Él te dirá qué hacer. No me debes nada. Solo quiero ayudarte. Si tienes la suerte, nos volveremos a encontrar.";
		link.l1 = "Gracias por tu ayuda. ¡Estoy en camino!";
		link.l1.go = "junior_2";
		break;

	case "junior_2":
		DialogExit();
		AddQuestRecord("BarbTemptation", "7");
		Saga_SetJuniorInCharles(); // ставим Валета
		pchar.questTemp.Saga.BarbTemptation = "valet";
		break;

	case "terrax":
		dialog.text = "¿Qué?! ¡Te arrancaré tu...";
		link.l1 = "No lo harás, Barbazon. ¡Veamos nuestras cartas! Trabajo para Jan Svenson. He revelado tu conspiración con Jackman. Sé todo, lo que planeabas y qué papel tenías también. Jackman y su hermano están muertos, el primero mató a Blaze Sharp y eso determinó su destino, el segundo no fue lo suficientemente hablador, me temo...";
		link.l1.go = "terrax_1";
		break;

	case "terrax_1":
		dialog.text = "¡Maldita sea! Tyrex nunca me perdonará por eso, pero todavía estoy...";
		link.l1 = "No hagas nada estúpido, Jacques. Sabía que no sería una conversación fácil, así que me he preparado. Echa un vistazo a la ventana... tu choza está rodeada por mis mosqueteros. Mi gente está por todo tu pueblo y hay un grupo de fuerza de choque justo afuera de las puertas. ¿Quieres comenzar una masacre? ¡Suficientemente fácil!";
		link.l1.go = "terrax_2";
		break;

	case "terrax_2":
		dialog.text = "¡Maldito seas! ¿Qué quieres?";
		link.l1 = "No me creerás, Barbazon, pero todo lo que quiero es... ¡Paz! Quiero paz. Por eso no le contaré a Tyrex sobre tu participación en esta conspiración contra él. Pero solo si haces lo que quiero...";
		link.l1.go = "terrax_3";
		break;

	case "terrax_3":
		dialog.text = "¿Qué quieres de mí? ¿Dinero? ¿Cuánto?";
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
		{
			link.l1 = "Oh, no, déjaselo a tus agentes sin cerebro. Necesito algo diferente. Necesito tu voto para Steven Dodson.";
		}
		else
		{
			link.l1 = "Oh, no, déjalo a tus agentes sin cerebro. Necesito algo diferente. Necesito tu voto para Marcus Tyrex.";
		}
		link.l1.go = "terrax_4";
		break;

	case "terrax_4":
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			sTemp = "Y Steven Dodson está de nuestro lado.";
		else
			sTemp = "";
		dialog.text = "¿En serio? Déjame pensar... ¿y qué si digo que no?";
		link.l1 = "Entonces estarás solo. Absolutamente solo. Svenson, Tyrex y Hawk irán contra ti." + sTemp + "Solo les mostraré la carta del Bribón, el hermano de Jackman, y mi palabra también será de confianza. Ahora, ¿cuánto tiempo crees que te quedarás en tu cómodo lugar después de eso?";
		link.l1.go = "terrax_5";
		break;

	case "terrax_5":
		dialog.text = "¿Hawk? ¡¿Está vivo?!";
		link.l1 = "Lo es. Lo salvé de la trampa tendida por Jackman. Así que el amigo más cercano de Jacob será su enemigo de sangre. Y me uniré a ellos, recuerda eso, Barbazon.";
		link.l1.go = "terrax_6";
		break;

	case "terrax_6":
		dialog.text = "¡Jackman no es mi amigo! ¡Malditos sean! ¡Me han acorralado!";
		link.l1 = "Tonterías. Vota por el hombre que te dije y nada cambiará para ti. Ya te lo dije, Jacques, quiero paz. Podría hacer que todos los barones te odien, pero no lo haré... aún.";
		link.l1.go = "terrax_7";
		break;

	case "terrax_7":
		GiveItem2Character(pchar, "splinter_jb"); // дать осколок
		dialog.text = "Bien. De acuerdo. Tienes mi palabra. Aquí, toma mi fragmento de piedra, lo necesitas, ¿verdad?";
		link.l1 = "Exactamente. Me alegra que hayamos llegado a un acuerdo, Jacques. Y toma la carta del 'Canalla' como un dulce recuerdo. O mejor aún, quémala, no querrás que la encuentren. Ah, y una cosa más...";
		link.l1.go = "terrax_8";
		break;

	case "terrax_8":
		RemoveItems(pchar, "letter_chad", 1);
		dialog.text = "¿Una última cosa?! ¿Qué más necesitas de mí?";
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
		{
			link.l1 = "Déjame recordarte algo. No hace mucho tiempo, enviaste a tu perro Ignacio Marco para asesinarme. Fui yo quien lo mató. Fui yo quien enterró tu plan de saquear un galeón español de oro. Fui yo quien envió a tus amigos a la emboscada española cerca de San Martín. ¡Mi nombre es Charlie Prince! Hemos terminado ahora, Jacques, y sé más cortés conmigo la próxima vez que nos veamos. Créeme, 'chico', nos volveremos a encontrar, y más de una vez, supongo.";
			link.l1.go = "terrax_8_1";
		}
		else
		{
			if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "Déjame recordarte algo. No hace mucho tiempo enviaste a tu perro Ignacio Marco a asesinarme. Fui yo quien lo mató. Fui yo quien enterró tu plan de saquear un galeón español de oro. ¡Mi nombre es Charlie Prince! Hemos terminado ahora, Jacques, y sé más cortés conmigo, la próxima vez que nos veamos. Créeme, 'chico', nos volveremos a encontrar, y más de una vez, supongo. No olvides que tengo a todos los barones piratas de mi lado. Adiós, Barbazon...";
				link.l1.go = "terrax_9";
			}
			else
			{
				link.l1 = "Sé más cortés conmigo la próxima vez que nos veamos. Créeme, 'chico', nos volveremos a encontrar, y más de una vez, supongo. No olvides, tengo a todos los barones piratas de mi lado. Adiós, Barbazon...";
				link.l1.go = "terrax_9";
			}
		}
		break;

	case "terrax_8_1":
		dialog.text = "";
		link.l1 = "No lo olvides, tengo a todos los barones piratas de mi lado. Adiós, Barbazon...";
		link.l1.go = "terrax_9";
		break;

	case "terrax_9":
		DialogExit();
		NextDiag.CurrentNode = "I_know_you_good";
		AddQuestRecord("BarbTemptation", "26");
		if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm"))
			Saga_GiveCalendar();
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("Saga_SGM_" + i);
			LAi_SetCitizenType(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.lifeday = 0;
		}
		ChangeCharacterComplexReputation(pchar, "fame", 1);
		bDisableFastReload = false;
		LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

		//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
	case "CapComission1":
		dialog.text = "Ja, ja. ¿Crees que tengo sólo un prisionero aquí? Nómbralo.";
		link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". ¿Está aquí?";
		link.l1.go = "CapComission2";
		DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
		break;

	case "CapComission2":
		if (CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
		{
			dialog.text = "Lo era. Lo he vendido a ese propietario de plantación de Barbados, el coronel Bishop, cuando estuvo aquí hace una semana.";
			link.l1 = "Maldición...";
			link.l1.go = "CapComission2_1";
		}
		else
		{
			dialog.text = "Ah, al fin. Estaba pensando en venderlo a ese dueño de plantación de Barbados, llegará en una o dos semanas... ¿Tienes un rescate?";
			link.l1 = "Mira, hay un pequeño problema... En realidad, no tengo tanto dinero. Pero estoy dispuesto a trabajar.";
			link.l1.go = "CapComission2_2";
			if (makeint(pchar.money) > 150000)
			{
				link.l2 = "Es bueno que no lo hayas vendido. Aquí están tus monedas - 150.000 pesos. ¿Dónde puedo conseguirlo?";
				link.l2.go = "CapComission2_3";
			}
		}
		break;

	case "CapComission2_1":
		dialog.text = "Fuiste demasiado lento... ¿Y por qué te importa él? Solo he estado negociando con sus parientes.";
		link.l1 = "Me han pedido que venga aquí.";
		link.l1.go = "CapComission2_11";
		break;

	case "CapComission2_11":
		dialog.text = "Bueno, llegas tarde. No puedo hacer nada.";
		link.l1 = "Escucha, ¿por cuánto lo has vendido si no es un secreto?";
		link.l1.go = "CapComission2_12";
		break;

	case "CapComission2_12":
		dialog.text = "Eh, no lo es. Pero no te lo diré... Te reirías si lo hiciera. ¡Ja-ja-ja-ja! Adiós.";
		link.l1 = "Nos vemos.";
		link.l1.go = "exit";
		AddQuestRecord("CaptainComission1", "10");
		AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon"); // правка лесник.  в СЖ запись ниже не работает
		// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		CaptainComission_GenerateManager();
		break;

	case "CapComission2_2":
		if (rand(3) == 1)
		{

			dialog.text = "Bueno, " + pchar.name + ", no funciona así. Vuelve con el dinero y obtendrás a tu debilucho, ja-ja.";
			link.l1 = "Está bien. Nos vemos.";
			link.l1.go = "CapComission2_4";
		}
		else
		{
			dialog.text = "Bueno, bueno... Tengo un asunto... Ni siquiera sé por dónde empezar. Necesito hundir a un pirata que ha cruzado la línea.";
			link.l1 = "¿No se le puede matar simplemente en la selva?";
			link.l1.go = "CapComission2_2_1";
		}
		break;

	case "CapComission2_2_1":
		dialog.text = "No es así como funciona el negocio, ¿sabes...? No necesito su muerte, necesito enseñar a algunos a no tomar mi parte del botín. Pero si va a alimentar a los tiburones, no me molestará.";
		link.l1 = "¿Por qué no envías a tus propios hombres tras él?";
		link.l1.go = "CapComission2_2_2";
		break;

	case "CapComission2_2_2":
		CaptainComission_GetRandomShore();
		pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
		pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
		pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
		sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
		dialog.text = "Mm... Bueno, " + GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " ha convencido a algunos piratas de que su parte del botín se guarda en nuestro escondite no muy lejos de " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Sus dos barcos '" + pchar.GenQuest.CaptainComission.ShipName1 + "' y '" + pchar.GenQuest.CaptainComission.ShipName2 + "' izó anclas no hace mucho y navegó hacia " + sLoc + "¿Ahora ves por qué no puedo confiar en mis hombres para hacer ese trabajo?";
		link.l1 = "Lo hago. ¿Cuánto tiempo tengo?";
		link.l1.go = "CapComission2_2_3";
		break;

	case "CapComission2_2_3":
		dialog.text = "De 12 a 15 días no más, es importante para mí que no lleguen al escondite, o no tendrá sentido hundirlos con el valioso cargamento. En ese caso, sería mejor que lo trajeran aquí...";
		link.l1 = "Está bien, estoy dentro. Intentaré atraparlos.";
		link.l1.go = "CapComission2_2_4";
		break;

	case "CapComission2_2_4":
		AddQuestRecord("CaptainComission1", "24");
		AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon"); // правка
		// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
		AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
		AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
		AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat"));				 // belamour gen
		AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
		pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
		pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
		pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips";
		SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);

		DialogExit();
		break;

	case "CapComission2_3":
		dialog.text = "No te preocupes. Mis hombres lo llevarán a tu barco. ¿Y por qué te importa él?";
		link.l1 = "No. Sus parientes me pidieron que lo entregara.";
		link.l1.go = "CapComission2_31";
		break;

	case "CapComission2_31":
		dialog.text = "Ah, eso está bien. Casi me sentí mal por ofrecer un precio tan bajo por tu hombre. ¡Ja-ja-ja-ja! Adiós.";
		link.l1 = "Nos vemos.";
		link.l1.go = "CapComission2_32";
		break;

	case "CapComission2_32":
		AddQuestRecord("CaptainComission1", "9");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
		addMoneyToCharacter(pchar, -150000);
		pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник
		DialogExit();
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission2_4":
		if (!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
		{
			AddQuestRecord("CaptainComission1", "31");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon"); // лесник
																				// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
		}
		pchar.GenQuest.CaptainComission.RepeatSpeak = true;
		DialogExit();
		break;

	case "CapComission3":
		dialog.text = "Entonces, " + GetFullName(pchar) + ", ¿hundiste a mis compinches? Je-je-je...";
		if (pchar.GenQuest.CaptainComission.PirateShips == "goaway")
		{
			link.l1 = "No. No logré atraparlos. Y no los encontré al regresar.";
			link.l1.go = "CapComission4";
		}
		if (pchar.GenQuest.CaptainComission.PirateShips == "died")
		{
			link.l1 = "Lo hice. Los envié a alimentar a los tiburones.";
			link.l1.go = "CapComission5";
		}
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

	case "CapComission4":
		dialog.text = "¡Maldita sea! ¡Los hayas conocido o no, ya no importa! ¿Y cuál será tu próxima sugerencia?";
		link.l1 = "¿Tal vez tienes un trabajo más fácil para mí?";
		link.l1.go = "CapComission4_1";
		link.l2 = "Escucha, " + NPChar.name + ", baja el precio por el prisionero...";
		link.l2.go = "CapComission4_2";
		break;

	case "CapComission4_1":
		dialog.text = "No.";
		link.l1 = "Entonces, adiós...";
		link.l1.go = "CapComission4_3";
		break;

	case "CapComission4_2":
		dialog.text = "¿Bajar el precio?! ¡Acabo de perder mi alijo por tu incompetencia! ¡Y ahora puedo subir el precio! Puedes llevártelo por 200.000 pesos si quieres, o puedes largarte al demonio de aquí.";
		link.l1 = "Es demasiado caro... Adiós...";
		link.l1.go = "CapComission4_4";
		if (sti(pchar.money) >= 200000)
		{
			link.l2 = "Maldita sea, toma tus monedas.";
			link.l2.go = "CapComission4_5";
		}
		break;

	case "CapComission4_3":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddQuestRecord("CaptainComission1", "27");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник
		// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		break;

	case "CapComission4_4":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddQuestRecord("CaptainComission1", "28");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник
		// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		break;

	case "CapComission4_5":
		dialog.text = "Puedes llevarte a este debilucho...";
		link.l1 = "Adiós.";
		link.l1.go = "CapComission4_6";
		break;

	case "CapComission4_6":
		addMoneyToCharacter(pchar, -200000);
		AddQuestRecord("CaptainComission1", "29");
		AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
		// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
		DialogExit();
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission5":
		dialog.text = "¡Jo-jo! ¡Bien hecho! Lleva a tu debilucho y buena suerte.";
		link.l1 = "Gracias. Adiós.";
		link.l1.go = "CapComission5_1";
		break;

	case "CapComission5_1":
		AddQuestRecord("CaptainComission1", "34");
		AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
			 ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "¿Trajiste el rescate?"+GetSexPhrase("","")+"¿Acaso no bromeaba cuando dije que lo vendería a los plantadores?";
			link.l1 = "Escucha, "+NPChar.name+",   aquí está el asunto... En fin, no tengo ese dinero. Pero estoy dispuesto"+GetSexPhrase("","а")+" trabajar.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Es bueno que no lo hayas vendido. Aquí tienes tus monedas - 150000 pesos. ¿Dónde puedo conseguirlo?"link.l2.go ="CapComision2_3";
			}
		break;*/
	case "CapComission6": // лесник . пусть шарль бабло ищет,или забить на пленника.
		dialog.text = "¿Has traído el dinero? No estaba bromeando con vender a ese hombre a la plantación.";
		link.l1 = "No tengo el dinero, " + NPChar.name + ", pero estoy trabajando en ello.";
		link.l1.go = "exit";
		if (makeint(pchar.money) > 150000)
		{
			link.l2 = "Es bueno que no lo hayas vendido. Aquí tienes tus monedas - 150.000 pesos. ¿Dónde puedo conseguirlo?" link.l2.go = "CapComission2_3";
		}
		break;

		//--------------------------------------------Похититель------------------------------------------------------
	case "Marginpassenger":
		dialog.text = "¿Y por qué te importa lo que hago? Sabes, sería mejor que te largaras...";
		link.l1 = "Tshh, cálmate. Tengo asuntos contigo. Se trata de tu prisionero.";
		link.l1.go = "Marginpassenger_1";
		break;

	case "Marginpassenger_1":
		dialog.text = "Ah, bien. ¿A quién quieres rescatar?";
		link.l1 = "Espera. No estoy aquí para pagar un rescate, estoy aquí para ofrecerte que compres a un prisionero. Y bueno, tendrás la oportunidad de obtener un rescate por él.";
		link.l1.go = "Marginpassenger_2";
		break;

	case "Marginpassenger_2":
		dialog.text = "Hum. ¿Y por qué necesitas mi intervención? ¿Por qué no quieres obtener el dinero directamente para ti?";
		link.l1 = "Es bastante arriesgado para mí. Puedo tener problemas con las autoridades.";
		link.l1.go = "Marginpassenger_3";
		break;

	case "Marginpassenger_3":
		dialog.text = "Ja-ja... está bien entonces. Vamos a echar un vistazo. ¿Quién es tu prisionero?";
		link.l1 = "Esto es " + pchar.GenQuest.Marginpassenger.Text + " " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City + "Gen") + ".";
		link.l1.go = "Marginpassenger_4";
		break;

	case "Marginpassenger_4":
		int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
		dialog.text = "Veo... sería un buen trato si no estás mintiendo. Supongo que puedo pagarte por este hombre " + iTemp + "pesos o darte alguna información interesante en su lugar. Es tu elección.";
		link.l1 = "Sería mejor que tomara pesos. Ya tuve suficiente de este negocio...";
		link.l1.go = "Marginpassenger_money";
		link.l2 = "¡Ja! Cuéntame más. Estoy seguro de que me darás algo interesante.";
		link.l2.go = "Marginpassenger_offer";
		break;

	case "Marginpassenger_money":
		dialog.text = "Dinero entonces. Llévalos. Ahora, no es tu problema. Entrega el objeto de la venta aquí.";
		link.l1 = "Ya debe estar cerca de las puertas del pueblo. ¡Gracias! Realmente me has ayudado.";
		link.l1.go = "Marginpassenger_money_1";
		break;

	case "Marginpassenger_money_1":
		iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
		dialog.text = "De nada, tráeme más... ¡Nos vemos!";
		link.l1 = "Buena suerte...";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, iTemp);
		sld = characterFromId("MarginPass");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		AddQuestRecord("Marginpassenger", "12");
		AddQuestUserData("Marginpassenger", "sSum", iTemp);
		CloseQuestHeader("Marginpassenger");
		DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;

	case "Marginpassenger_offer":
		pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
		pchar.GenQuest.Marginpassenger.GoodsQty = 200 + rand(10) * 10;
		switch (hrand(1))
		{
		case 0: // бухта на южном мейне
			SelectSouthshore();
			while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore))
				SelectSouthshore();
			dialog.text = "Es bueno hacer negocios con un hombre inteligente. Ahora escucha: en pocos días a " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat") + " una expedición española llegará de la Tierra Firme, cargada de mercancías valiosas. Estarán esperando un barco que supuestamente llevará el cargamento. Si llegas allí en una semana, tendrás la oportunidad de llevarte el cargamento para ti.\nSi fuera tú, ya estaría yendo a mi barco. Y trae al prisionero aquí.";
			link.l1 = "¡Gracias! Las mercancías serán una buena compensación por mis problemas. Y mi pasajero ya debe estar cerca de las puertas de la ciudad. Será llevado a ti.";
			link.l1.go = "Marginpassenger_offer_1";
			break;

		case 1: // просто кораблик
			SelectSouthcity();
			pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Es bueno hacer negocios con un hombre inteligente. Ahora escucha: en aproximadamente una semana un bergantín español '" + pchar.GenQuest.Marginpassenger.ShipName1 + " cargado con mercancías valiosas zarpará desde " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen") + " a " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen") + "  Si te das prisa, lo atraparás fácilmente.\n¿Todavía estás aquí? Si fuera tú, ya estaría yendo a mi barco. Y trae al prisionero aquí.";
			link.l1 = "¡Gracias! Las mercancías serán una buena compensación por mis problemas. Y mi pasajero ya debe estar cerca de las puertas de la ciudad. Será traído a ti.";
			link.l1.go = "Marginpassenger_offer_2";
			break;
		}
		sld = characterFromId("MarginPass");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		pchar.GenQuest.Marginpassenger = "final";
		break;

	case "Marginpassenger_offer_1":
		DialogExit();
		AddQuestRecord("Marginpassenger", "13");
		AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat")); // лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
			break;

	case "Marginpassenger_offer_2":
		DialogExit();
		AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5 + rand(2), false);
			break;

			//---------------------------------------попытка залезть в сундуки --------------------------------------------
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¡Robo!!! Eso es inaceptable! Prepárate, " + GetSexPhrase("chico", "chica") + "...", "¡Oye, ¿qué demonios estás haciendo ahí?! ¿Pensaste que podrías robarme? Estás acabado... ", "Espera, ¿qué diablos? ¡Quita tus manos! ¡Resulta que eres un ladrón! Hasta aquí llegaste, bastardo...");
		link.l1 = LinkRandPhrase("¡Mierda!", "¡Carramba!!", "¡Maldita sea!!");
		link.l1.go = "PL_Q3_fight";
		break;

		// ----------------------------------------------блок нод angry--------------------------------------------------
	case "AngryRepeat_1":
		dialog.text = "¡Lárgate de aquí!";
		link.l1 = "Ups...";
		link.l1.go = "AngryExitAgainWithOut";
		if (CheckAttribute(npchar, "angry.terms")) // примиряемся через 10 дней.
		{
			if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
			{
				dialog.text = "No me molestes con tus charlas baratas. La próxima vez, no te gustará el resultado...";
				link.l1 = "Lo tengo.";
				link.l1.go = NextDiag.TempNode;
				CharacterDelAngry(npchar);
			}
		}
		break;
	case "AngryRepeat_2":
		dialog.text = RandPhraseSimple("Se acabó, no hay nada que hablar.", "Ya no quiero hablar contigo, así que será mejor que no me molestes.");
		link.l1 = RandPhraseSimple("Como desees...", "Mm, bien entonces...");
		link.l1.go = "AngryExitAgain";
		if (CheckAttribute(npchar, "angry.terms")) // примиряемся через 10 дней.
		{
			if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
			{
				dialog.text = "¿Espero que muestres más respeto y dejes de ser grosero?";
				link.l1 = "Puedes estar seguro, Jacques, lo haré.";
				link.l1.go = NextDiag.TempNode;
				CharacterDelAngry(npchar);
			}
		}
		break;

	case "AngryExitAgain":
		DialogExit();
		DeleteAttribute(npchar, "angry.ok");
		break;

	case "AngryExitAgainWithOut":
		DialogExit();
		DeleteAttribute(npchar, "angry.ok");
		DoReloadCharacterToLocation("LeFransua_town", "reload", "reload6");
		break;

	case "pirate_town":
		dialog.text = "¿Solucionar el problema? ¿Entiendes lo que has hecho? De todos modos, tráeme un millón de pesos y persuadiré a los muchachos para que olviden tus 'hazañas'. Si no te gusta la idea, entonces puedes irte al infierno.";
		if (sti(Pchar.money) >= 1000000)
		{
			link.l1 = "Está bien, estoy listo para pagar.";
			link.l1.go = "pirate_town_pay";
		}
		link.l2 = "Entendido. Me voy.";
		link.l2.go = "pirate_town_exit";
		break;

	case "pirate_town_exit":
		DialogExit();
		bDisableFastReload = true; // закрыть переход
		pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
		pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
		pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;

	case "pirate_town_pay":
		dialog.text = "¡Bien! Considérate limpio de nuevo. Pero espero que no vuelvas a hacer cosas tan repugnantes.";
		link.l1 = "No lo haré.   Demasiado caro para mí.   Adiós...";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -1000000);
		pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
	case 0:
		pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
		pchar.GenQuest.Marginpassenger.Southcity1 = "Havana";
		break;

	case 1:
		pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
		pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago";
		break;

	case 2:
		pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
		pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo";
		break;
	}
}
