// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "Señor, ha elegido un maldito mal momento para charlar. Toda la guarnición está buscándole. Será mejor que se escabulla rápido...";
			link.l1 = "No te preocupes. No me quedaré mucho tiempo.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail", 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Bienvenido, capitán. ¿Le interesaría una oferta intrigante? ";
				link.l1 = "Todo tipo de personas por aquí parecen tener tales ofertas, y soy un hombre curioso. ¿Qué es?";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "Buen día. Bienvenido a mi botica. Tengo medicinas para tratar la mayoría de las enfermedades e infirmidades. ¿Qué puedo ofrecerle?";
			link.l1 = "Escucha, John, hay rumores de que alguien vive en tu lugar en el segundo piso...";
			link.l1.go = "guardoftruth";
			break;
		}
		//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Buen día. Me alegra verte en mi botica. Tengo medicinas para tratar la mayoría de las enfermedades y dolencias. ¿Qué puedo ofrecerte?";
				link.l1 = "Hola señor Murdock. Estoy aquí en nombre de Lucas Rodenburg. Me envió a usted para discutir un asunto relacionado con Richard Fleetwood.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Buenas tardes. ¿Qué tipo de problema tienes? ¡Tengo tanto jarabe para la tos como polvo para la diarrea!";
				link.l1 = "Hola, señor Murdock. Estoy aquí en nombre de Lucas Rodenburg. Me envió para discutir un asunto relacionado con Richard Fleetwood.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ahhh, aquí está el perro contratado por Rodenburg... Hercule, Longway, ¿podríais salir aquí?\n¡Matad a este hombre!";
				link.l1 = "¡Espera, tengo una receta!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "Buenas tardes. Me alegra verte en mi botica. Tengo medicinas para tratar la mayoría de las enfermedades y dolencias. ¿Qué puedo ofrecerte?";
			link.l1 = "Nada en este momento, gracias. Me siento bastante bien.";
			link.l1.go = "exit";
			break;
		}
		//----------------------------------------------за Англию---------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
		{
			dialog.text = "Hola, invitado no invitado. No cubres tu rostro con una máscara y no pareces un ladrón. Por lo tanto, llego a la conclusión de que necesitas algo más de un pobre boticario. ¿Quizás algo para la diarrea?";
			link.l1 = "Hola a ti también, Johan van Merden. Traigo saludos de Hercule Tonzag. Veo que conoces este nombre.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
		}
		//--------------------------------------------против всех--------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
			{
				dialog.text = "Ah, así que aquí estás. Bueno, ¿has conocido a Hércules? ";
				link.l1 = "Sí. Hemos llegado a un acuerdo. John, voy a ayudar a Hercule, y tengo varias preguntas para ti sobre Richard Fleetwood.";
				link.l1.go = "About_Fleetwood";
				break;
			}
			if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
			{
				dialog.text = "¡Hola! Me alegra verte, " + pchar.name + "¡!";
				link.l1 = "Hola, John. ¿Descubriste algo sobre Fleetwood?";
				link.l1.go = "About_Fleetwood_9";
				pchar.quest.Wait_FleetwoodOver.over = "yes"; // снять таймер
				break;
			}
			if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
			{
				dialog.text = "Llegas tarde. El pájaro ha volado del nido. Charlie Knippel visitó Willemstad y trajo una chica de allí para Richard. Ahora zarpan hacia Inglaterra con un escuadrón militar en uno o dos días. Fleetwood se ha ido, nunca lo verás en esta vida.";
				link.l1 = "Maldita sea. Me había olvidado por completo de Richard y perdí la noción del tiempo. Nos vemos.";
				link.l1.go = "About_Fleetwood_17";
				break;
			}
			if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
			{
				dialog.text = "Bienvenido de nuevo, " + pchar.name + "¡Nada para ti ahora mismo. No hay noticias sobre Fleetwood, y Charlie Knippel aún no ha regresado de Curazao...";
				link.l1 = "Y nunca lo hará. Ni él, ni su bergantín.";
				link.l1.go = "Abigile";
				break;
			}
			if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
			{
				dialog.text = "¡Ah, tenemos invitados! ¡Hola, Charlie! ¡Buenas tardes, señorita!";
				link.l1 = "¡Buenas tardes, John! Permíteme presentarte a mi compañera, la prometida de Richard, la encantadora Abigail Shneur.";
				link.l1.go = "Abigile_7_1";
				break;
			}
			if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
			{
				dialog.text = "Mantén la voz baja... ¿Qué vas a hacer a continuación?";
				link.l1 = "¿Próximo? Preferiría dormir un poco, pero desafortunadamente no hay tiempo para eso. Voy a sacar a Fleetwood del agujero en el que se esconde y terminar el trabajo de Hercule.";
				link.l1.go = "Abigile_9";
				break;
			}
			if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
			{
				dialog.text = "¿Has terminado de escribir? Déjame ver... ¡Dios mío, Charlie, eres un verdadero loco! ¿No crees que te has pasado un poco con tantos detalles? Quiero decir, ¿la parte sobre los dedos, las orejas y el rostro de la señorita Shneur? Tienes un talento enfermizo, eso seguro. ¡Maldita sea, estoy a punto de perder el almuerzo!";
				link.l1 = "Estoy faroleando, John. No mataré a la chica. Podría hacer que se despida de su dedo... Pero nada más. A fin de cuentas, le quedan nueve más.";
				link.l1.go = "Abigile_15";
				break;
			}
			if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
			{
				dialog.text = "¿Fue bien? Puedo verlo en tus ojos: ¡lo hiciste!";
				link.l1 = "Sí. Fleetwood aceptó mis términos. Las fauces de la trampa se están cerrando. Ahora esperamos.";
				link.l1.go = "Abigile_23";
				break;
			}
			if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
			{
				dialog.text = "¡Ah, bienvenido de nuevo, mi amigo! ¿Qué puedes contarme?";
				link.l1 = "Fleetwood está muerto. Todo salió según el plan. Llegó a la isla, donde había organizado una emboscada en la playa. Luchó bastante, pero no le sirvió de nada. Solo uno de nosotros salió de esa playa con vida.";
				link.l1.go = "Abigile_27";
				break;
			}
			if (pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Está bien " + pchar.name + ", tengo una oferta seria para ti. El asunto del que voy a hablar es muy peligroso, pero, considerando la forma en que te deshiciste de Fleetwood, estoy seguro de que puedes manejarlo. Tienes un... raro talento para resolver problemas difíciles.";
				link.l1 = "Me halagas. Sigue hablando.";
				link.l1.go = "Lucas";
				break;
			}
			if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
			{
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				dialog.text = "Bienvenido de nuevo, " + pchar.name + ". ¿Alguna buena noticia para mí?";
				link.l1 = "John, de ahora en adelante puedes dormir sin un cuchillo bajo la almohada. Lucas ya no será una amenaza para ti. Está arrestado y encerrado, y está a punto de ser enviado a Holanda en un futuro cercano, donde será juzgado por insurrección, intento de asesinato y otros delitos.";
				link.l1.go = "Lucas_10";
				break;
			}
			if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
			{
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				dialog.text = "Me alegra verte, " + pchar.name + "¡Estás vivo, y eso es bueno! ¿Alguna novedad?";
				link.l1 = "Sí. Van Berg se ha ido para siempre. Tal como dijiste, me rastreó y atacó en el momento más inoportuno. Van Berg era un hueso duro de roer, pero al final lo quebré.";
				link.l1.go = "Final";
				break;
			}
			dialog.text = "¿Necesitas algo más?";
			link.l1 = "No, John, nada. Me voy.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Buenas tardes. Me alegra verte en mi botica. Tengo medicinas para tratar la mayoría de las enfermedades y dolencias. ¿Qué puedo ofrecerte?";
		link.l1 = "Nada por el momento, gracias. Me siento bastante bien.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

		//--------------------------------------------за Голландию-----------------------------------------------------
	case "Knippel_exit":
		dialog.text = "No tengo idea de qué está hablando, señor. ¿Qué Lucas Rodenburg? No tengo tratos con los holandeses. Debe estar equivocado.";
		link.l1 = "¿Qué? ¡Mynheer Rodenburg me envió a usted!";
		link.l1.go = "Knippel_exit_1";
		break;

	case "Knippel_exit_1":
		dialog.text = "Déjame decirte una vez más - no conozco a ningún hombre llamado Mynheer Rodenburg. En cuanto a los holandeses, no trato con ellos. Hay solo dos cosas que no soporto en este mundo: las personas que son intolerantes con las culturas ajenas, y los holandeses. Así que si no necesitas ninguna medicina, por favor, déjame hacer mi trabajo.";
		link.l1 = "Más curioso y más curioso...";
		link.l1.go = "exit";
		break;

	case "Knippel":
		dialog.text = "Bueno bueno... ¿Eres del Mynheer Rodenburg? Está bien. Te escucho.";
		link.l1 = "Necesito organizar una reunión con el Capitán Fleetwood en un lugar apartado. Tomé prestado el 'Mirage' de Jacob van Berg, el corsario holandés que el Sr. Fleetwood tanto desea capturar. Me gustaría informarle que el 'Mirage' estará convenientemente fondeado frente a la costa de Dominica en un futuro cercano.";
		link.l1.go = "Knippel_1";
		break;

	case "Knippel_1":
		dialog.text = "¿Te dio Jacob su barco? Hm, así que ahora necesitas a alguien que le diga al señor Fleetwood que el 'Espejismo' pronto estará frente a la costa de Dominica, ya que tú no puedes contarle eso a Richard por razones particulares...";
		link.l1 = "Exactamente. Mynheer Rodenburg recomendó que me dirigiera a usted con este asunto.";
		link.l1.go = "Knippel_2";
		break;

	case "Knippel_2":
		dialog.text = "En este caso, Charlie Knippel es el hombre que necesitas. Un amigo leal de Fleetwood... y su espía. Habla con él y menciona todo lo que quieras que Richard sepa. Ten cuidado, Knippel puede parecer bastante simple, pero no es ningún tonto.\nPuedes encontrarlo en una pequeña cabaña, no lejos de la orilla del mar. Debe estar allí.";
		link.l1 = "Ya veo. Gracias, señor Murdock. ¡Adiós!";
		link.l1.go = "Knippel_3";
		break;

	case "Knippel_3":
		DialogExit();
		pchar.questTemp.HWIC.Holl = "toKnippel";
		AddQuestRecord("Holl_Gambit", "1-16");
		AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;

	case "Merdok_fight":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешим драться
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		sld = characterFromId("Tonzag");
		PlaySound("Voice\Spanish\hambit\Ercule Tongzag-04.wav");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		// а вот и китаец нарисовался
		sld = characterFromId("Longway");
		LAi_SetWarriorType(sld);
		FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy")) // враг
		{
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			PlaySound("Voice\Spanish\hambit\Longway-02.wav");
		}
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend")) // друг
		{
			LAi_warrior_DialogEnable(sld, true);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.dialog.currentnode = "Longway_hire";
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			PlaySound("Voice\Spanish\hambit\Longway-02.wav");
		}
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral"))
			sld.lifeday = 0; // нейтрал - просто нет
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//-------------------------------------------------за Англию-----------------------------------------------------
	case "Merdok_talk":
		dialog.text = "¿De veras? Pensé que el pobre Gastón llevaba ya tiempo ardiendo en el infierno.";
		link.l1 = "Bien podría ser, pero claramente no hay nadie como Gaston. Encontré su cabeza en el tesoro de un viejo judío en la isla secreta. Pero aún así logró enviarte saludos. También mencionó que tenemos un enemigo común: el Sr. Rodenburg. Tonzag dijo que podrías tener documentos importantes para Lucas que podrían atraerlo de su escondite en Curazao.";
		link.l1.go = "Merdok_talk_1";
		break;

	case "Merdok_talk_1":
		dialog.text = "Tenía razón. Es mi archivo lo que le quita el sueño a Rodenburg. Parece que todavía anda por aquí solo por eso. La cuestión es que le prometieron un trabajo cómodo en el Comité de Directores de la Compañía en las Provincias Unidas. Si la información de este archivo, que contiene muchas cosas interesantes sobre el pasado y el presente de Lucas, se hace ampliamente conocida, sus aspiraciones de carrera se verán truncadas. En ese caso, lo mejor que podría esperar es ser decapitado en lugar de ahorcado.";
		link.l1 = "Dame el archivo, y me encargaré de nuestro enemigo.";
		link.l1.go = "Merdok_talk_2";
		break;

	case "Merdok_talk_2":
		dialog.text = "Debes pensar que soy un tonto. Sigo vivo solo porque aún lo tengo conmigo. ¿Cómo sé que no estás trabajando para Lucas ahora?";
		link.l1 = "Tendrás que aceptar mi palabra - o morir.";
		link.l1.go = "Merdok_talk_3";
		break;

	case "Merdok_talk_3":
		PlaySound("Voice\Spanish\hambit\John Mardock-08.wav");
		dialog.text = "¡Respuesta incorrecta, morirás aquí y ahora! ¡Longway, gongji!";
		link.l1 = "¡Oh, ho, el chino aparece de las sombras! No os preocupéis, os haré chop suey a ambos!";
		link.l1.go = "Merdok_fightEng";
		break;

	case "Merdok_fightEng":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешим драться
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		sld = characterFromId("Longway");
		FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
		PlaySound("Voice\Spanish\hambit\Longway-02.wav");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//----------------------------------------против всех-------------------------------------------------------
	case "MC_InHouse":
		PlaySound("Voice\Spanish\hambit\John Mardock-09.wav");
		dialog.text = "Finalmente, estás de nuevo en pie. Temía que no fueras a despertar.";
		link.l1 = "¿Qué...? ¿Quién eres tú? ¿Dónde diablos estoy? ¿Cómo llegué aquí?";
		link.l1.go = "MC_InHouse_1";
		break;

	case "MC_InHouse_1":
		dialog.text = "Calma, no hagas tantas preguntas a la vez, no es bueno que te emociones tanto. Me llamo John Murdock, soy farmacéutico aquí en St. John's. Habías perdido el conocimiento en una pelea con los hombres de Fleetwood. Debo decir que te dieron una buena paliza... Fue Hércules quien te trajo aquí a mi botica, y, bueno, he curado tus heridas con mis pociones y medicinas.";
		link.l1 = "¿Hercule? ¿Quién? ¿El hombre que vino a ayudarme en la calle?";
		link.l1.go = "MC_InHouse_2";
		break;

	case "MC_InHouse_2":
		dialog.text = "Sí. Ese es él. Por cierto, le gustaría hablar contigo. Necesitas encontrarte con él en la ciudad. ¿Aún puedes caminar? Bien. Sal de noche - usa el túnel secreto que empieza detrás de la puerta en la planta baja de mi casa. No salgas hasta que oscurezca - los hombres de Fleetwood te están buscando.";
		link.l1 = "Sí... ¿Dónde está mi barco?";
		link.l1.go = "MC_InHouse_3";
		break;

	case "MC_InHouse_3":
		if (pchar.Ship.Type == SHIP_NOTUSED)
		{
			dialog.text = "Tu barco fue confiscado y tu tripulación se dispersó por miedo a ser asesinada por los hombres de Fleetwood. Lo siento.";
			link.l1 = "Mierda...";
		}
		else
		{
			dialog.text = "Está en el puerto, en su lugar habitual.";
			link.l1 = "Uf... es bueno oír eso. Pensé que la había perdido.";
		}
		link.l1.go = "MC_InHouse_4";
		break;

	case "MC_InHouse_4":
		dialog.text = "Debes conocer a Hércules. Ve a la ciudad por la noche a través del túnel secreto. Él se acercará a ti. Ahora descansa un poco, y yo debo volver a mi trabajo.";
		link.l1 = "Está bien, John. Y... ¡gracias por tu ayuda y curación!";
		link.l1.go = "MC_InHouse_5";
		break;

	case "MC_InHouse_5":
		NextDiag.CurrentNode = "First time";
		DialogExit();
		npchar.greeting = "merdok_2";
		AddQuestRecord("Holl_Gambit", "3-12");
		pchar.questTemp.HWIC.Self = "MainBegin"; // новый флаг квеста
		sld = characterFromId("Bridgetown_tavernkeeper");
		sld.model = "barmen_3";
		sld.greeting = "barmen_1";
		sld.name = "Harry";
		sld.lastname = "Fletcher";											   // перерисуем бармена Бриджтауна
		LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);		   // закрыть выход из аптеки через дверь
		LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);	   // открыть подземелье из дома
		LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false); // открыть дом из подземелья
		pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
		pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
		pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
		pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
		break;

	case "About_Fleetwood":
		DelLandQuestMark(npchar);
		dialog.text = "¿Fleetwood? ¿Qué quieres saber sobre él?";
		link.l1 = "Todo. Cuéntame todo lo que sabes. Me parece que no es ningún secreto para ti por qué Hércules vino a Antigua. Estoy de su lado.";
		link.l1.go = "About_Fleetwood_1";
		break;

	case "About_Fleetwood_1":
		dialog.text = "Muy bien. Capitán Richard Fleetwood de la Real- quiero decir, la Marina del Commonwealth... maldita sea, sigo olvidando que ese fanático Cromwell está al mando y cambió el nombre. Sin embargo, Fleetwood es un buen luchador y un marinero experimentado. Comanda una fragata llamada 'Valkyrie' - un excelente barco, debo mencionar, con una tripulación de marineros y marines de élite. Lleva a cabo una guerra privada contra las Provincias Unidas en general y con la Compañía Holandesa de las Indias Occidentales en particular. Ha saqueado innumerables barcos mercantes holandeses y ha elevado el costo del seguro hasta el techo. El gobernador de Curazao puso una recompensa récord por su cabeza.";
		link.l1 = "Hmm... Parece un poco inusual que un oficial de la 'Armada del Commonwealth' se dedique a la piratería...";
		link.l1.go = "About_Fleetwood_2";
		break;

	case "About_Fleetwood_2":
		dialog.text = "Sí, en efecto. Está caminando por la cuerda floja. Los ingleses no reconocen oficialmente sus acciones y se niegan a tener algo que ver con ello, pero en realidad lo alientan detrás de escena. Tengo razones para suponer que está de alguna manera conectado con la red de espías ingleses en el Caribe, y con esos canallas no se juega.";
		link.l1 = "Un hombre serio... ¿Es esto todo? Hercule me habló de un ayudante suyo... otro Charlie... ¿cómo se llama... Canister? ¿Cañonazo?";
		link.l1.go = "About_Fleetwood_3";
		break;

	case "About_Fleetwood_3":
		dialog.text = "¿Knippel? Sí, hay un tipo así. Charlie Knippel solía ser artillero maestro en la Armada Inglesa, ahora retirado. Ahora lleva una vida tranquila en la costa. Es los ojos y oídos de Fleetwood en St. John's, así que ten cuidado con él y ni pienses en interrogarlo sobre Richard - acabarás en prisión o peor.";
		link.l1 = "Ya veo. ¿Puedes decirme algo más digno de mención sobre Fleetwood?";
		link.l1.go = "About_Fleetwood_4";
		break;

	case "About_Fleetwood_4":
		dialog.text = "Un ídolo para todas las mujeres en Antigua desde los dieciséis hasta los sesenta. Parece que eso es todo sobre él. Bueno, creo que sabes lo que le ha pasado ahora. Se queda en cama lamiéndose las heridas.";
		link.l1 = "Debe tener algunos puntos débiles o vicios...";
		link.l1.go = "About_Fleetwood_5";
		break;

	case "About_Fleetwood_5":
		dialog.text = "¿Qué quieres decir?";
		link.l1 = "Bueno, tal vez le guste apostar o beba mucho o no pueda resistirse al sexo opuesto, algo por el estilo. ¿Está casado?";
		link.l1.go = "About_Fleetwood_6";
		break;

	case "About_Fleetwood_6":
		dialog.text = "No, soltero. En cuanto a las cosas que mencionaste, no es conocido por ninguna de ellas.";
		link.l1 = "Ya veo. Pero, quizás, ¿todavía hay algo especial en él? ¡Incluso una persona como él debe tener algunos puntos débiles!";
		link.l1.go = "About_Fleetwood_7";
		break;

	case "About_Fleetwood_7":
		dialog.text = "No lo sé. Escucha, hagámoslo así. Ven a verme en una semana, y yo investigaré la vida privada de Fleetwood. ¿Trato?";
		link.l1 = "Trato hecho. ¡Gracias, John! Estaré aquí en una semana.";
		link.l1.go = "About_Fleetwood_8";
		break;

	case "About_Fleetwood_8":
		DialogExit();
		pchar.questTemp.HWIC.Self = "WaitFleetwood";
		SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
		SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
		SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false); // чтобы не опаздывал
		LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);  // открыть выход из аптеки
		AddQuestRecord("Holl_Gambit", "3-14");
		break;

	case "About_Fleetwood_9":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("SentJons");
		dialog.text = "Sí, pero no mucho, por desgracia. Y me temo que de todos modos no sirve de mucho.";
		link.l1 = "¡Escúpelo! Cada pequeño detalle es muy importante si tiene algo que ver con Fleetwood.";
		link.l1.go = "About_Fleetwood_10";
		break;

	case "About_Fleetwood_10":
		dialog.text = "No hace mucho tiempo, Richard recogió a dos refugiados judíos de una isla desconocida, un anciano y su hija, navegando hacia Willemstad. El barco en el que navegaban fue hundido por piratas. Fleetwood los trajo en secreto a Curazao, arriesgando su propio cuello. Han pasado varios meses desde entonces. Ahora ha enviado a su fiel perro Charlie Knippel a Willemstad...";
		link.l1 = "Mm... ¿Cómo está conectado?";
		link.l1.go = "About_Fleetwood_11";
		break;

	case "About_Fleetwood_11":
		dialog.text = "Conseguí averiguar que Charlie recibió la orden de traer aquí a una chica desde Willemstad, una judía llamada Abigail Shneur. Sí, la misma chica de la isla. Parece que Richard se enamoró de ella, ya que envía a su mejor agente por ella.\nEso es todo. No sé si esto ayuda en algo.";
		link.l1 = "¡Oh ho ho! ¡Jajaja! Parece que nuestro solterón ha caído ante los astutos encantos de la judía. ¡Este es un trabajo excelente, John, gracias! Ahora, ¿cuándo partirá nuestro amigo Knippel hacia Curazao?";
		link.l1.go = "About_Fleetwood_12";
		break;

	case "About_Fleetwood_12":
		dialog.text = "Partió ayer.";
		link.l1 = "¿Y en qué barco?";
		link.l1.go = "About_Fleetwood_13";
		break;

	case "About_Fleetwood_13":
		dialog.text = "Sabía que preguntarías eso. Está en un bergantín comisionado por la Mancomunidad, oh al diablo con eso, la 'Armada Real'. Su nombre es 'Zeekalf'.";
		link.l1 = "¿'Zeekalf'? Ese es un nombre muy holandés para un barco inglés... ohhh ya entiendo.";
		link.l1.go = "About_Fleetwood_14";
		break;

	case "About_Fleetwood_14":
		dialog.text = "Eres un pensador rápido... Su nombre anterior era 'Royal Mary', pero para este viaje se ha llamado 'Zeekalf'. Y está ondeando la bandera holandesa.";
		link.l1 = "Tu ayuda ha sido invaluable, John. Me marcho ahora. Regresaré pronto y necesitaré tu habitación en el segundo piso, donde me alojaste mientras me recuperaba.";
		link.l1.go = "About_Fleetwood_15";
		break;

	case "About_Fleetwood_15":
		dialog.text = "¿Qué tramas?";
		link.l1 = "Te contaré todo cuando regrese. ¡Deséame suerte, John! Adiós.";
		link.l1.go = "About_Fleetwood_16";
		break;

	case "About_Fleetwood_16":
		DialogExit();
		AddQuestRecord("Holl_Gambit", "3-16");
		pchar.questTemp.HWIC.Self = "HuntKnippel";
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
		pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
		pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
		pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
		LocatorReloadEnterDisable("SentJons_town", "houseH1", true); // закрыть хижину Чарли
		AddMapQuestMarkIsland("Curacao", true);
		break;

	case "About_Fleetwood_17":
		DialogExit();
		AddQuestRecord("Holl_Gambit", "3-15");
		pchar.questTemp.HWIC.Self = "end";
		pchar.questTemp.HWIC.Detector = "self_fail";
		CloseQuestHeader("Holl_Gambit");
		break;

	case "Abigile":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("SentJons");
		dialog.text = "¿De veras? ¿Por qué estás tan seguro?";
		link.l1 = "Porque Charlie está en el fondo del mar alimentando a los peces. Abordé el 'Zeekalf' y envié a Knippel al infierno. Por supuesto, lo interrogué antes de eso... Tenía una carta consigo, lo que me permitió hacerme pasar por Knippel cuando hablé con nuestra judía Abigail, la amada de nuestro valiente Richard.";
		link.l1.go = "Abigile_1";
		break;

	case "Abigile_1":
		dialog.text = "Mm...Eso es astuto. Entonces, estás diciendo que...";
		link.l1 = "Sí. He traído a la judía a Antigua. Está a bordo de mi barco. ¡Ahora tengo un as de triunfo en mi juego de cartas con Fleetwood! Hará cualquier cosa por ella...";
		link.l1.go = "Abigile_2";
		break;

	case "Abigile_2":
		dialog.text = "¿Estás seguro? Podría ser que todo no sea tan simple como insinúas...";
		link.l1 = "¡Oh sí, estoy absolutamente seguro! Por la carta, he deducido que el padre de Abigail estaba en contra de su matrimonio con Richard por dinero. Como puedes imaginar, típico suegro judío. Así que Fleetwood decidió pagarle una dote a su padre, ¡200000 pesos! Dime ahora, ¿cuántas chicas en el mundo valen tanto dinero?";
		link.l1.go = "Abigile_3";
		break;

	case "Abigile_3":
		dialog.text = "¡Je! ¡Ciertamente no una judía! No he conocido a una cristiana que valga eso en mi vida, eso es seguro." + pchar.name + ", eres un pícaro astuto. ¿Qué harás con ella?";
		link.l1 = "Traeré a la judía aquí y la mantendremos en tu habitación. Le diré que Richard ha ido al mar y aún no ha regresado, así que será nuestra invitada por una semana. Ella piensa que yo soy Charlie Knippel.";
		link.l1.go = "Abigile_4";
		break;

	case "Abigile_4":
		dialog.text = "Eso es interesante. ¿Así que decidiste mantener a la chica en mi casa? Hmm...";
		link.l1 = "John, ella es una judía. Una vagabunda apátrida traída de una colonia holandesa. Aquí en St. John's no es nadie y nadie la conoce. Ten por seguro que podemos hacer lo que queramos y no se atreverá a decir una palabra. No tiene ni un centavo ni un amigo a su nombre. Y de todas formas, no será nuestra invitada por mucho tiempo. Atraeré a Fleetwood con ella como cebo, y después de eso ya no habrá necesidad de ella.";
		link.l1.go = "Abigile_5";
		break;

	case "Abigile_5":
		dialog.text = "Estás empezando a asustarme, Charles. ¿No vas a aprovecharte de esta chica, verdad? ¿O llevarla al mismo fin que Knippel?";
		link.l1 = "No, por supuesto que no. 'Pillo astuto' puedo ser, pero no soy enemigo de las chicas hermosas - judías o cristianas. O de las feas, ya que estamos. Si se porta bien, la llevaré con su padre en Willemstad cuando todo esto termine. El viejo tacaño probablemente caerá de rodillas y me dará las gracias por salvarla de ese pérfido inglés.";
		link.l1.go = "Abigile_6";
		// belamour legendary edition -->
		link.l2 = "Ella tiene un papel que desempeñar en esta farsa. Cuando la obra termine, no tendré uso para ella.";
		link.l2.go = "Abigile_6a";
		break;

	case "Abigile_6a":
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		AddCharacterExpToSkill(pchar, "Sneak", 60);
		dialog.text = "Entiendo, así que por ahora tengo que cuidarla.";
		link.l1 = "No insistiré, compañero. Si estás totalmente en contra de esto, ella puede quedarse a bordo de mi barco. Pero entonces tendré que ponerle grilletes por seguridad y mantenerla en la bodega con las ratas para protegerla de mi tripulación. Es una novedad para ellos tener mujeres a bordo, ya sabes. Sería una pena tratar así a una chica tan encantadora.";
		link.l1.go = "Abigile_7";
		break;

	case "Abigile_6":
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		AddCharacterExpToSkill(pchar, "Leadership", 60);
		// <-- legendary edition
		dialog.text = "Ya veo, así que por ahora tengo que cuidar de ella.";
		link.l1 = "No insistiré, compañero. Si estás totalmente en contra de esto, ella puede quedarse a bordo de mi barco. Pero entonces tendré que ponerle grilletes por seguridad y mantenerla en la bodega con las ratas para protegerla de mi tripulación. Tener mujeres a bordo es una novedad para ellos, ya sabes. Sería una pena tratar así a una chica tan encantadora.";
		link.l1.go = "Abigile_7";
		break;

	case "Abigile_7":
		dialog.text = "Entiendo. Muy bien, tráela aquí. Es mi deber ayudarte en tu lucha contra Fleetwood. Tráela aquí y prepararé su 'habitación de huéspedes'.";
		link.l1 = "Gracias John. Sabía que podía contar contigo.";
		link.l1.go = "exit";
		pchar.questTemp.HWIC.Self = "AbigileInCabin";
		DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
		AddQuestRecord("Holl_Gambit", "3-24");
		// поставим табурет
		sld = ItemsFromID("lcheer");
		sld.shown = true;
		sld.startLocation = "SentJons_HouseF3";
		sld.startLocator = "goto2";
		AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;

	case "Abigile_7_1":
		DelLandQuestMark(npchar);
		dialog.text = "¡Oh! Mi placer. Estoy feliz de dar la bienvenida a una mujer tan importante y... elegante. Señorita, ¿podría subir al segundo piso, por favor? Hay una cena esperándola y la cama está hecha. Estoy seguro de que querrá tener una buena noche de sueño después de un viaje tan largo.";
		link.l1 = "Sí. Abigail seguramente está cansada después de un viaje tan largo desde Willemstad.";
		link.l1.go = "Abigile_8";
		break;

	case "Abigile_8":
		DialogExit();
		sld = characterFromId("Abigile");
		sld.dialog.currentnode = "Abigile_kidnapping_11";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "Abigile_9":
		dialog.text = "¿Tienes un plan ya?";
		link.l1 = "Lo haré. Necesitamos escribir una carta a Richard con una demanda de rescate por Abigail. Organiza un encuentro en alguna isla deshabitada como Turks. Y si no cumple, entonces, le enviaremos a su querida hebrea en pedazos, por así decirlo.";
		link.l1.go = "Abigile_10";
		break;

	case "Abigile_10":
		dialog.text = "¿Cuál es la necesidad de tales complicaciones con una isla deshabitada?";
		link.l1 = "Tierra neutral. Es más seguro. De todas formas, no voy a traer a Abigail. Necesito a Fleetwood. Ciertamente preparará una emboscada en Antigua, pero en Turks no tendrá tal ventaja.";
		link.l1.go = "Abigile_11";
		break;

	case "Abigile_11":
		dialog.text = "Justo. ¿Quién entregará la carta? Es muy peligroso.";
		link.l1 = "Un extraño. Escoge a un borracho de la taberna, uno que parezca fiable. Están dispuestos a hacer lo que les pidas por un poco de dinero para ron. Si Richard lo mata en un arranque de ira, enviaremos a otro. Y adjuntaremos uno de los dedos de Abi en la carta. Eso lo hará mucho más obediente.";
		link.l1.go = "Abigile_12";
		break;

	case "Abigile_12":
		dialog.text = "" + pchar.name + "...";
		link.l1 = "No te preocupes, John. Estoy seguro de que no llegará a eso. Solo tienes que encontrar un mensajero y yo redactaré la carta de inmediato. ¿Tienes papel y tinta?";
		link.l1.go = "Abigile_13";
		break;

	case "Abigile_13":
		dialog.text = "Sí, lo sé. Y también conozco a un borracho adecuado. Recomiendo a Jack Harrison. Pasa todas las noches en la taberna, emborrachándose con ron. Lo encontrarás fácilmente.";
		link.l1 = "Bien, tráeme pluma y tinta y redactaré la nota de rescate para Richard.";
		link.l1.go = "Abigile_14";
		break;

	case "Abigile_14":
		DialogExit();
		StartQuestMovie(true, false, true);
		locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;

	case "Abigile_15":
		dialog.text = "¿Cuándo le vas a entregar la carta? ¿Vas a observar la entrega en progreso?";
		link.l1 = "Claro. Richard no es un tonto, pero dudo que se arriesgue. Al menos, eso espero. No quiero hacerle daño a la chica, pero lo haré si es necesario. Bueno, es hora de encontrar al borracho que mencionaste. Jack... ¿cuál era su nombre completo?";
		link.l1.go = "Abigile_20";
		break;

	case "Abigile_20":
		dialog.text = "Su nombre es Jack Harrison. Suele visitar la taberna por la tarde. ¡Ten cuidado!";
		link.l1 = "Todo estará bien. Espérame.";
		link.l1.go = "Abigile_22";
		break;

	case "Abigile_22":
		DialogExit();
		LAi_SetOwnerType(npchar);
		pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
		AddDialogExitQuestFunction("CreateDrunckardInTavern");
		AddQuestRecord("Holl_Gambit", "3-25");
		break;

	case "Abigile_23":
		DelLandQuestMark(npchar);
		dialog.text = "Bueno, yo no diría eso. Fleetwood es astuto y peligroso. Además, es un maestro espadachín y un marinero experimentado. No será una presa fácil.";
		link.l1 = "Dejé de tomar el camino fácil cuando llegué al Caribe. Bueno, John, es hora de que me vaya. Por cierto, mencionaste que nuestro valiente Fleetwood tiene un buen barco, ¿no es así?";
		link.l1.go = "Abigile_24";
		break;

	case "Abigile_24":
		dialog.text = "Tiene el bergantín más fino que he visto jamás. Y he visto unos cuantos.";
		link.l1 = "Eso es bueno. Me gustan los barcos finos. ¡Es hora de levar anclas!";
		link.l1.go = "Abigile_26";
		break;

	case "Abigile_26":
		DialogExit();
		pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
		pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
		pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
		pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
		AddQuestRecord("Holl_Gambit", "3-28");
		AddMapQuestMarkShore("Shore57", false);
		break;

	case "Abigile_27":
		int iVal = 0;
		for (i = 0; i < COMPANION_MAX; i++)
		{
			iTemp = GetCompanionIndex(PChar, i);
			if (iTemp > 0)
			{
				sld = GetCharacter(iTemp);
				if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
					iVal = 1;
			}
		} // установили признак наличия Валькирии в эскадре.
		if (iVal != 0)
		{
			dialog.text = "¡Estoy sin palabras! ¡Una combinación excelente, una gran idea y una ejecución magistral! Mis felicitaciones, " + pchar.name + "¡Y también has logrado tomar su bergantín como premio!";
			link.l1 = "¡Gracias! ¿Y dónde está Hércules? Me gustaría verlo. La última vez que nos encontramos, me dijo que podría encontrarlo con tu ayuda.";
			link.l1.go = "Abigile_28";
		}
		else
		{
			dialog.text = "¡Una combinación excelente, una gran idea y una implementación magistral! ¡Mis felicitaciones, " + pchar.name + "!";
			link.l1 = "¡Gracias! ¿Y dónde está Hércules? Me gustaría verlo. La última vez que nos vimos, me dijo que podría encontrarlo con tu ayuda.";
			link.l1.go = "Abigile_28";
		}
		break;

	case "Abigile_28":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("SentJons");
		dialog.text = "Lo espero en cualquier momento. Debería llegar aquí a través del túnel secreto. Y deberías explicarte a Abigail. Ella ha comenzado a preocuparse por la ausencia de Richard.";
		link.l1 = "De acuerdo, pero ¿no deberíamos enviarla a casa?";
		link.l1.go = "Abigile_29";
		break;

	case "Abigile_29":
		dialog.text = "Aún no... Necesito hablar contigo primero. Pero primero espera la llegada de Hercule. Ve y consuela a Abigail. Cuéntale una historia, inventa algo. Luego ven al sótano. ¿De acuerdo?";
		link.l1 = "Sí, sí, John.";
		link.l1.go = "Abigile_30";
		break;

	case "Abigile_30":
		DialogExit();
		npchar.greeting = "merdok_4";
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
		pchar.questTemp.HWIC.Self = "AbigileLie";
		sld = characterFromId("Abigile");
		LAi_SetCitizenType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		AddQuestRecord("Holl_Gambit", "3-34");
		break;

	case "Lucas":
		DelLandQuestMark(npchar);
		dialog.text = "Bueno, ha llegado el momento de poner las cartas sobre la mesa. Como ya has adivinado, no soy solo un simple boticario. Mi verdadero nombre es Johan van Merden y hasta hace poco he sido un agente de la Compañía Holandesa de las Indias Occidentales y la mano derecha de su vicepresidente Lucas Rodenburg.";
		link.l1 = "¡De verdad! Es interesante...";
		link.l1.go = "Lucas_1";
		break;

	case "Lucas_1":
		dialog.text = "Ahora es diferente. Lucas quiere dejar el juego y regresar a los Países Bajos, así que necesita enterrar todo y a todos los conectados con su pasado\nCreo que aún respiro solo por mis archivos que contienen toda la información sobre los crímenes de Lucas... como la historia del 'barco fantasma' que es solo un barco pirata ordinario bajo el mando del temerario e inescrupuloso bribón Jacob van Berg. Rodenburg contrató al hombre para saquear y hundir barcos comerciales ingleses\nVan Berg también es responsable de hundir el fluyt con Abigail y su padre a bordo. Abigail es una figura importante en este juego, Rodenburg también quería su mano y corazón, al igual que Fleetwood, así que me sorprendió bastante cuando la trajiste aquí...";
		link.l1 = "Rodenburg...ese es el yerno del que hablaba el excéntrico padre de Abigail!";
		link.l1.go = "Lucas_2";
		break;

	case "Lucas_2":
		dialog.text = "Sí, por eso quiero que se quede aquí un poco. Podría ser mi última carta en el juego contra Rodenburg, aunque preferiría no usarla más, es una buena chica, no quiero que sufra. Creo que Lucas elegiría mi archivo en lugar de ella, si se le presentara la opción.\nAsí que te propongo ser mi aliado en el juego contra Lucas... deshazte de él, usa cualquier medio necesario. La recompensa será sustancial.";
		link.l1 = "Hmm... No creo que vaya a ser más difícil que con Fleetwood. ";
		link.l1.go = "Lucas_3";
		break;

	case "Lucas_3":
		dialog.text = "No, estás equivocado. Al final, Fleetwood era un lobo solitario, actuando por su cuenta. Rodenburg es vicepresidente de la Compañía. Es un hombre muy influyente, solo el gobernador de Curazao tiene más poder. Jacob van Berg es su agente, un hombre muy peligroso. Lucas se sienta en su trasero en Willemstad bajo la protección de los guardias de la Compañía, son tan buenos como los hombres de Fleetwood.\nEsto no va a ser fácil.";
		link.l1 = "Las reglas del juego son las mismas: atraer al tigre fuera de su guarida... Ya tengo un plan. ¿Qué más puedes contarme sobre Lucas?";
		link.l1.go = "Lucas_4";
		break;

	case "Lucas_4":
		dialog.text = "Bueno, te he contado casi todo. Él posee un barco veloz llamado 'Meifeng' - Viento Hermoso. Su capitán es un chino llamado Longway - un hombre leal a Rodenburg. Él también es un enemigo al que no te gustaría enfrentarte. No hay aficionados en la tripulación de Lucas.";
		link.l1 = "Ya teníamos un as bajo la manga desde el principio: tu archivo. Si valora su vida más que a la judía, hará cualquier cosa para mantener la información del archivo en secreto... Pero... ¿realmente existe el archivo, John? ¿Estás fanfarroneando?";
		link.l1.go = "Lucas_5";
		break;

	case "Lucas_5":
		dialog.text = "El archivo sí existe. Y Lucas lo sabe. ¿Has encontrado algo ya?";
		link.l1 = "Tengo. John, si realmente fueras el agente de la compañía, deberías saber algo.";
		link.l1.go = "Lucas_6";
		break;

	case "Lucas_6":
		dialog.text = "¿Qué exactamente? Pregúntame.";
		link.l1 = "Necesito interceptar un barco de la compañía. Preferiblemente, un barco sin escolta - un mensajero o algo así. ¿Puedes decirme algo al respecto?";
		link.l1.go = "Lucas_7";
		break;

	case "Lucas_7":
		dialog.text = "Hm... No poseo tal información. ¡Espera! Estoy seguro de que la Compañía tiene un paquebote en las rutas marítimas entre Philipsburg y Willemstad una vez al mes. Ella entrega documentos de negocios. Es una bergantina llamada 'Hoop'.\nPartirá de Philipsburg hoy o mañana.";
		link.l1 = "¡Aye, eso es! Todo lo que necesito para ir a las costas de San Cristóbal. La ruta marítima hacia Curazao pasa justo al lado.";
		link.l1.go = "Lucas_8";
		break;

	case "Lucas_8":
		dialog.text = "Buena suerte, " + pchar.name + ". No te preguntaré sobre los detalles de tu plan. ¡Estaré esperando tu regreso!";
		link.l1 = "Todo estará bien, John. ¡Cuida a la judía y trátala bien!";
		link.l1.go = "Lucas_9";
		break;

	case "Lucas_9":
		DialogExit();
		RemoveItems(PChar, "MC_Letter", 1);
		GiveItem2Character(pchar, "MC_Letter");
		ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
		AddQuestRecordInfo("LetterToLucas", "1");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
		pchar.questTemp.HWIC.Self = "LetterToLucas";
		sld = characterFromId("Tonzag");
		sld.dialog.currentnode = "Tonzag_hired";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddQuestRecord("Holl_Gambit", "3-36");
		// установим таймер на генерацию энкаунтера
		pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
		pchar.quest.HWIC_Cureer.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.HWIC_Cureer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.HWIC_Cureer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false); // таймер
		break;

	case "Lucas_10":
		dialog.text = "¡Increíble! ¡No puedo creer lo que escucho! ¿Cómo sucedió eso?";
		link.l1 = "He capturado el barco correo y envié una carta a Lucas en nombre de Fleetwood, en la cual afirmé que había tomado posesión de cierto archivo que pertenecía a un boticario de San Juan, y que pronto las pruebas de todas sus fechorías se conocerán desde aquí hasta Ámsterdam y Londres. Esperaba que empezara a cazarme, pero resultó ser al revés.";
		link.l1.go = "Lucas_11";
		break;

	case "Lucas_11":
		dialog.text = "";
		link.l1 = "Lucas acusó a Matthias Beck de traición y de tratos con los ingleses, lo metió tras las rejas y se instaló en el palacio del gobernador. Lo más probable es que eliminara al capitán del bergantín. ¡Luego le dijo a su fiel chino del Meifeng que hundiera el barco con el director de la Compañía, Peter Stuyvesant, a bordo!";
		link.l1.go = "Lucas_12";
		break;

	case "Lucas_12":
		dialog.text = "Rodenburg es un hombre despiadado. Pero ni siquiera yo pensé que podría llegar a tales extremos...";
		link.l1 = "He capturado el Meifeng y he interrogado a Longway. Me lo contó todo. Encontré a Stuyvesant y le advertí sobre las intenciones de Rodenburg y navegamos juntos a Willemstad. Stuyvesant liberó a Beck y arrestó a Lucas. Ahora está en prisión.";
		link.l1.go = "Lucas_13";
		break;

	case "Lucas_13":
		dialog.text = "¡Je! Tienes un verdadero talento, amigo mío... Deberías hacer carrera en la Marina de la Compañía o como político en las Provincias Unidas; ¡tienes todas las de ganar para convertirte en gobernador! ¿Y qué le hiciste a Longway?";
		link.l1 = "Lo dejé ir. Se rindió honorablemente, así que no le hice ningún daño.";
		link.l1.go = "Lucas_14";
		break;

	case "Lucas_14":
		dialog.text = "Eso es bueno. Longway es un buen hombre, a diferencia de su antiguo jefe. Bueno, " + pchar.name + ", ¡has hecho un gran trabajo! Prepararé tu recompensa, pero necesitaré algo de tiempo... Mientras tanto...";
		link.l1 = "John, a decir verdad, hay una mosca en la sopa. Longway y luego Rodenburg me dijeron que Jacob van Berg me está cazando. ¿Qué tan malo es eso?";
		link.l1.go = "Lucas_15";
		break;

	case "Lucas_15":
		dialog.text = "¿Jacob van Berg? Charlie, esto es serio. Es un pirata despiadado, un marinero y luchador hábil que hace parecer a Fleetwood un gatito. Un cazador profesional. Él fue el que destruyó los barcos por órdenes de Rodenburg.\nTe encontrará, así que debes prepararte. Yo también debería tomar precauciones para mí mismo.";
		link.l1 = "¿Cómo puedo encontrar a este van Berg?";
		link.l1.go = "Lucas_16";
		break;

	case "Lucas_16":
		dialog.text = "No lo sé. Lucas y Longway eran los únicos que sabían dónde encontrarlo. Así que ten cuidado y estate listo\nEstoy cerrando el lugar. Ve por el túnel secreto si quieres verme. Y lleva a la judía contigo, es demasiado peligroso para que se quede aquí.";
		link.l1 = "No te preocupes, John. Que aparezca y yo me ocuparé de él. ¿Dónde está Abigail?";
		link.l1.go = "Lucas_17";
		break;

	case "Lucas_17":
		dialog.text = "Se ha ido a la iglesia. Lo siento por ella. Ha estado muy alterada recientemente.";
		link.l1 = "Bueno... Eso es una agradable sorpresa. Quizás ella se dé cuenta de que Cristo es el Mesías que su pueblo ha esperado durante tanto tiempo. Bueno, es hora de llevarla de vuelta a su padre.";
		link.l1.go = "Lucas_18";
		break;

	case "Lucas_18":
		dialog.text = "Quería verte. Estoy seguro de que te pedirá que la lleves de vuelta a casa.";
		link.l1 = "Abi, ¿eh?";
		link.l1.go = "Lucas_19";
		break;

	case "Lucas_19":
		dialog.text = "Bueno, tengo que admitir que nos hemos hecho amigos. No me arrepiento de que haya estado viviendo en mi casa, y gracias a Dios nunca sabrá por qué fue traída aquí.";
		link.l1 = "Está bien, John, iré a la iglesia para encontrarme con Abigail. Luego me dirijo a Willemstad.";
		link.l1.go = "Lucas_20";
		break;

	case "Lucas_20":
		DialogExit();
		sld = characterFromId("Abigile");
		AddLandQuestMark(sld, "questmarkmain");
		ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1"); // Аби - в церковь
		AddQuestRecord("Holl_Gambit", "3-56");
		pchar.questTemp.HWIC.Self = "AbiReturnHome";
		LocatorReloadEnterDisable("SentJons_town", "HouseF3", true); // закрыть аптеку
		break;

	case "Final":
		dialog.text = "¿Tú... aplastaste sus nueces? Oh - una metáfora. ¡Pues, con nueces o sin ellas, lo hiciste! ¡Felicitaciones!";
		link.l1 = "No te mentiría, je. Ahora puedes respirar tranquilo, John.";
		link.l1.go = "Final_1";
		break;

	case "Final_1":
		dialog.text = "¡Finalmente! Creo que es mejor renunciar a todos estos juegos políticos e intrigas. Ahora es momento de hablar sobre tu recompensa por el trabajo.";
		link.l1 = "Bueno, realmente lo apreciaría.";
		link.l1.go = "Final_2";
		break;

	case "Final_2":
		dialog.text = "Voy a dejar el Caribe para siempre. Como muestra de agradecimiento por tu ayuda y por rescatarme de Rodenburg, te otorgo la escritura de propiedad de esta casa y mi farmacia. Ahora todo es tuyo. Toma las llaves.";
		link.l1 = "¡Eso es estupendo! Estoy bastante feliz. Tienes una casa muy cómoda y una bodega acogedora...";
		link.l1.go = "Final_3";
		break;

	case "Final_3":
		GiveItem2Character(pchar, "Drugstore_keys"); // ключ
		dialog.text = "Y también, por favor, acepte esta modesta suma de 100 000 pesos y este mosquete. Me sirvió fielmente una vez, y te servirá bien a ti también.";
		link.l1 = "¡No rechazo tales regalos!";
		link.l1.go = "Final_4";
		LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);	 // открыть аптеку
		LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
		pchar.quest.Jino_Door.win_condition.l1 = "locator";
		pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
		pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
		pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
		pchar.quest.Jino_Door.function = "OpenRoomDoor"; // на локатор комнаты Джино
		Achievment_Set("ach_10");
		break;

	case "Final_4":
		AddMoneyToCharacter(pchar, 100000);
		GiveItem2Character(pchar, "mushket2");
		dialog.text = "En la habitación de arriba encontrarás a un joven filósofo natural. Es el mejor boticario que conozco. Fue él quien preparó estas mezclas, que te ayudaron a recuperarte en un par de días. Cuida de su manutención y su conocimiento compensará todos tus gastos con creces.";
		link.l1 = "¿Mi propio ratón de biblioteca personal? Muy bien, me encargaré de él.";
		link.l1.go = "Final_5";
		break;

	case "Final_5":
		dialog.text = "Tengo que decir adiós ahora. Voy al sótano a empacar mis pertenencias. Mañana no estaré aquí, zarpo de Antigua. Estoy feliz de haberte conocido y estoy feliz de que estuvieras de mi lado y no con mis enemigos.";
		link.l1 = "También me alegra conocerte, John. Tal vez, nos volvamos a encontrar...";
		link.l1.go = "Final_6";
		break;

	case "Final_6":
		dialog.text = "No en esta vida, amigo mío. Me voy a empacar. Adiós, " + pchar.name + ".";
		link.l1 = "¡Adiós, John! ¡Buena suerte para ti!";
		link.l1.go = "Final_7";
		break;

	case "Final_7":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		npchar.lifeday = 0;
		pchar.questTemp.HWIC.Self = "final";
		AddQuestRecord("Holl_Gambit", "3-64");
		CloseQuestHeader("Holl_Gambit");
		pchar.questTemp.HWIC.Detector = "self_win";
		CheckPortugalHWIC();
		break;

	// Страж Истины
	case "guardoftruth":
		dialog.text = "Ah, buen señor, no escuche esos tontos rumores. No hay nadie allí. Está mi laboratorio, las mezclas se están preparando, ¿sabe usted...?";
		link.l1 = "Dejando las bromas a un lado, John. ¿Te suena el nombre de Gino Gvineili?";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "Mm...";
		link.l1 = "¡Ajá!  Puedo verlo en tus ojos - tengo razón... ¡Ahí es donde vive y para quién prepara sus hierbas!";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "Señor, le digo una vez más - no hay nadie aquí.";
		link.l1 = "Dejemos las excusas a un lado, John. No haré daño a tu alquimista, pero si el Padre Vincento de Santiago lo encuentra, no puedo estar seguro. El Inquisidor ya planea enviar a sus 'Domini Canes' a Antigua...";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "¿Qué quieres de él?";
		link.l1 = "Solo para hablar. Tiene información bastante importante para mí. Prometo que no lo entregaré a la Inquisición y no le haré daño de ninguna manera.";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		dialog.text = "Gino es un buen tipo. No creas nada de lo que te haya dicho el Padre Vincento sobre él. Y recuerda - yo defenderé a mi alquimista.";
		link.l1 = "Te di mi palabra. ¿No es eso suficiente para ti?";
		link.l1.go = "guardoftruth_5";
		break;

	case "guardoftruth_5":
		dialog.text = "Sube las escaleras, entonces. La puerta está abierta. Y espero que mantengas tu palabra.";
		link.l1 = "Ten la seguridad de que lo haré.";
		link.l1.go = "guardoftruth_6";
		break;

	case "guardoftruth_6":
		DialogExit();
		pchar.questTemp.Guardoftruth = "jino1";
		AddQuestRecord("Guardoftruth", "36");
		LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;

	// алхимический набор
	case "alchemy":
		dialog.text = "Capitán, ¿no le gustaría familiarizarse con las artes herméticas? Esto podría serle muy útil.";
		link.l1 = "Lo siento, pero mi ocupación es algo diferente. Estoy acostumbrado a sostener la empuñadura de una espada en mi mano, no frascos o tubos de ensayo.";
		link.l1.go = "alchemy_exit";
		link.l2 = "'Hay más cosas en el cielo y en la tierra de las que sueñas en tu filosofía.' Por supuesto, me encantaría. ¿Qué se necesita?";
		link.l2.go = "alchemy_1";
		npchar.quest.alchemy = true;
		break;

	case "alchemy_exit":
		dialog.text = "Como desees. Solo ofrecí...";
		link.l1 = "...";
		link.l1.go = "exit";
		break;

	case "alchemy_1":
		dialog.text = "Deberías aprender a mezclar hierbas con tus propias manos. Pero no tendrás éxito sin un equipo de alquimista. Echa un vistazo a esta bolsa. Hay todo lo que un alquimista principiante necesita: tubos de ensayo, frascos, un alambique, espátulas, tubos de vidrio, un quemador y un montón de cosas similares...";
		link.l1 = "¡Muy interesante! ¿Y qué puedo preparar con ello?";
		link.l1.go = "alchemy_2";
		break;

	case "alchemy_2":
		dialog.text = "Bueno, no podrás transmutar plomo en oro, pero sí podrás mezclar ingredientes según varias recetas y así obtener pociones y otras cosas útiles.";
		link.l1 = "¿Recetas?";
		link.l1.go = "alchemy_3";
		break;

	case "alchemy_3":
		dialog.text = "Verdad. Debes conocer una receta para hacer una poción o un objeto. Las recetas se pueden comprar a los mercaderes o encontrarse en cualquier lugar. Una vez que hayas estudiado una receta, deberías recolectar cada ingrediente necesario y hacer exactamente lo que está escrito allí\n Usa tus herramientas de alquimia, encuentra o compra un mortero y maja, busca un crisol, ay, no poseo uno extra para darte. Hierbas, licores, pociones, minerales, basura - todo servirá, siempre y cuando tengas la receta correcta y las herramientas.";
		link.l1 = "Muy interesante. ¿Y cuánto quieres por este equipo?";
		link.l1.go = "alchemy_4";
		break;

	case "alchemy_4":
		dialog.text = "Veinte mil pesos. Este es un equipo muy bueno y cubrirá su costo muy rápidamente.";
		link.l1 = "Te estás burlando de mí, ¿verdad? ¿Un bolso con cristalería por el precio de un lanchón? No, pasaré.";
		link.l1.go = "alchemy_exit";
		if (sti(pchar.money) >= 20000)
		{
			link.l2 = "Estoy de acuerdo. Creo que será interesante intentar hacer algo con mis propias manos.";
			link.l2.go = "alchemy_5";
		}
		break;

	case "alchemy_5":
		AddMoneyToCharacter(pchar, -20000);
		Log_Info("Tienes el kit del alquimista.");
		GiveItem2Character(pchar, "alchemy_tool");
		PlaySound("interface\important_item.wav");
		dialog.text = "No te arrepentirás de esta compra, estoy absolutamente seguro. Definitivamente, es más rentable hacer pociones tú mismo cuando las necesites, en lugar de visitar los puestos de los herbolarios para comprar todo lo que necesitas por piezas. Además, no siempre será posible comprar todo lo que necesitas. ";
		link.l1 = "Aprendamos. ¡Creo que puedo hacerlo!";
		link.l1.go = "alchemy_6";
		break;

	case "alchemy_6":
		DialogExit();
		PlaySound("interface\notebook.wav");
		Log_Info("Para fabricar tus propias hierbas y amuletos debes tener la habilidad Alquimia.");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//--> блок реагирования на попытку залезть в сундук
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("Eres un " + GetSexPhrase("¡ladrón, señor! Guardias, llévenlo", "¡ladrona, chica! Guardias, llévensela") + "!!!", "¡Mira eso! Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre. ¡Atrapen al ladrón!", "¡Guardias! ¡Robo! ¡Atrapen al ladrón!!!");
		link.l1 = "¡Maldita sea!";
		link.l1.go = "exit";
		LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
