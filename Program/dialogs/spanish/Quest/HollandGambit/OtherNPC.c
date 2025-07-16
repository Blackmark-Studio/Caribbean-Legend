// диалоги прочих НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Un error. Díselo a los desarrolladores.";
		link.l1 = "¡Lo haré!";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		if (npchar.id == "HWICFernando")
			NextDiag.CurrentNode = "Fernando";
		DialogExit();
		break;

		//---------------------------------------за Голландию--------------------------------------------------
		// сопроводить торговца
	case "Baltazar":
		pchar.quest.Create_BaltazarOver.over = "yes"; // снять прерывание
		dialog.text = "¡Qué golpe de suerte! Capitán, resulta que necesito una escolta a Philipsburg con mucha urgencia...";
		link.l1 = "¿Eres Balthazar Ridderbock?";
		link.l1.go = "Baltazar_1";
		DelLandQuestMark(npchar);
		break;

	case "Baltazar_1":
		dialog.text = "¡Maldita sea, ya soy más famoso que el virrey! ¿Quién eres tú? ¿Qué quieres?";
		link.l1 = "Soy el Capitán " + GetFullName(pchar) + ". Me envió Lucas Rodenburg. Estoy autorizado para tomarle a usted y su barco bajo mi protección.";
		link.l1.go = "Baltazar_2";
		break;

	case "Baltazar_2":
		dialog.text = "¡Oh, el señor Rodenburg debe haber escuchado mis súplicas de ayuda! Verá, hay un corsario...";
		link.l1 = "Salgamos de los detalles de tu historia, ya los conozco.";
		link.l1.go = "Baltazar_3";
		break;

	case "Baltazar_3":
		dialog.text = "¡Por supuesto! Ya he perdido demasiado tiempo... Tengo que llegar a Philipsburg en no más de dos semanas.";
		link.l1 = "Entonces ve a tu barco y prepárate para zarpar. ¡Levantamos anclas de inmediato!";
		link.l1.go = "Baltazar_4";
		break;

	case "Baltazar_4":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
		SetCharacterRemovable(npchar, false);
		npchar.CompanionEnemyEnable = false; // всегда друзья
		SetCompanionIndex(pchar, -1, sti(npchar.index));
		npchar.loyality = MAX_LOYALITY;
		AddQuestRecord("Holl_Gambit", "1-3");
		AddMapQuestMarkCity("Marigo", true);
		if (bImCasual)
		{
			NewGameTip("Modo exploración: se duplica la duración de las misiones");
			SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
		}
		else
			SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); // таймер
		pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";		   // прерывание на потопление сопровождаемого
		pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
		pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
		pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location"; // прерывание на выполнение
		pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
		pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
		if (rand(1) == 0)
		{
			BaltazarPirateGlobalCreate();
		}
		else
		{
			pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
			pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location"; // прерывание на выполнение
			pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
			pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
		}
		break;

	case "Baltazar_5":
		dialog.text = "¡Gracias por tu ayuda, capitán! Tu protección no podría haber llegado en mejor momento, por favor acepta mi agradecimiento y estos 5 000 pesos.";
		link.l1 = "Mm... Esta no es una recompensa muy generosa por salvar una vida...";
		link.l1.go = "Baltazar_6";
		break;

	case "Baltazar_6":
		dialog.text = "Además, enviaré una carta al señor Rodenburg cuando tenga la oportunidad, con la mejor valoración posible de tus acciones. Ahora debo irme.";
		link.l1 = "Bueno, adiós entonces, Baltasar.";
		link.l1.go = "Baltazar_7";
		break;

	case "Baltazar_7":
		DialogExit();
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
		AddQuestRecord("Holl_Gambit", "1-6");
		AddMoneyToCharacter(pchar, 5000);
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		ChangeCharacterNationReputation(pchar, HOLLAND, 1);
		ChangeOfficersLoyality("good_all", 1);
		pchar.questTemp.HWIC.Holl = "BaltazarCom";
		AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		AddMapQuestMarkCity("Villemstad", true);
		break;

	// командировка в Сантьяго
	case "Santiago_Trip":
		dialog.text = "¡Señor! Espere... parece que ha dejado caer algo...";
		link.l1 = "¿Qué? ¡Ah?!";
		link.l1.go = "Santiago_Trip_1";
		break;

	case "Santiago_Trip_1":
		DialogExit();
		PlaySound("People Fight\Death_NPC_08.wav");
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam("Te han dejado inconsciente por la espalda", "", 0, 4);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 15, 10); // крутим время
		RecalculateJumpTable();
		DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;

	case "Santiago_Trip_2":
		dialog.text = "Lo siento, amigo mío, tuve que darte un golpe leve para que no causaras problemas. Me doy cuenta de que probablemente te duele la cabeza, pero bueno, sobrevivirás. Si hay tiempo para eso...";
		link.l1 = "¿Quién eres, maldita sea, y qué está pasando aquí?";
		link.l1.go = "Santiago_Trip_3";
		break;

	case "Santiago_Trip_3":
		dialog.text = "Tranquilo, tranquilo, mi amigo, o tendré que calmarte una vez más. No queremos que esos matones irrumpan, haciendo sonar sus espadas oxidadas, ¿verdad? Necesitamos hablar en silencio.";
		link.l1 = "Devuélveme mi espada, cabrón, y tendremos una buena charla, ¡lo juro!";
		link.l1.go = "Santiago_Trip_4";
		break;

	case "Santiago_Trip_4":
		dialog.text = "Eres un hombrecito rápido, ¿verdad? No hay necesidad de usar el acero por ahora. Dime lo que quiero saber y, quizás, saldrás de aquí entero. ¿Estoy claro? Entonces, charlemos un poco.\n¿Sigues callado? Bien, entonces tenemos un trato. ¿Qué llevabas de Rodenburg al banquero?";
		link.l1 = "Una carta.";
		link.l1.go = "Santiago_Trip_5";
		break;

	case "Santiago_Trip_5":
		dialog.text = "Astuto. Sé que no era un ramo de margaritas. ¿Qué había en esa carta, muchacho?";
		link.l1 = "¿Cómo lo sé? No tengo la costumbre de leer la correspondencia que se me confía. Tal vez era un mensaje de amor. Ya sabes lo que dicen sobre la gente de poder...";
		link.l1.go = "Santiago_Trip_6";
		break;

	case "Santiago_Trip_6":
		dialog.text = "...Un capitán honesto es algo bastante raro de ver en estos tiempos miserables. Bueno, eso son malas noticias para ti. ¿Qué dijo ese maldito banquero cuando recibió el paquete? ¿Qué tipo de negocio tiene con los holandeses?";
		link.l1 = "Están traficando con perfume de contrabando de Francia... o mierda de vaca bávara, creo.";
		link.l1.go = "Santiago_Trip_7";
		link.l2 = "La pregunta era sobre la compensación por algo. Eso es todo lo que sé.";
		link.l2.go = "Santiago_Trip_8";
		break;

	case "Santiago_Trip_7":
		dialog.text = "Eres un tipo valiente... Y con sentido del humor, también. Sería una lástima matarte. A Gaston le habrías caído bien. Aunque... quédate aquí por el momento. Debo ir a comprobar algo, y Miguel se encargará de ti mientras estoy fuera.";
		link.l1 = "¡Lo juro, 'mi amigo', te arrepentirás de esto!";
		link.l1.go = "Santiago_Trip_9";
		break;

	case "Santiago_Trip_8":
		dialog.text = "Ahí va la arrogancia... Cuando las cosas se ven sombrías, nuestro valiente capitán muestra razonabilidad. Podrías haberlo hecho mucho antes y nos habrías ahorrado tiempo y problemas. Bueno, tengo que ir a comprobar algo, pero luego volveré y hablaremos, si aún es necesario, eso es. Quédate aquí por el momento. Miguel te cuidará mientras estoy fuera.";
		link.l1 = "¡Lo juro, 'mi amigo' - te arrepentirás de esto!";
		link.l1.go = "Santiago_Trip_11";
		break;

	case "Santiago_Trip_9":
		dialog.text = "Pero por supuesto. Mantén el silencio, 'héroe', quizás, todo aún estará bien.";
		link.l1 = "... ";
		link.l1.go = "Santiago_Trip_11";
		break;

	case "Santiago_Trip_10":
		dialog.text = "Quédate aquí y espera que tu flexibilidad se justifique a sí misma.";
		link.l1 = "...";
		link.l1.go = "Santiago_Trip_11";
		break;

	case "Santiago_Trip_11":
		DialogExit();
		AddQuestRecord("Holl_Gambit", "1-44");
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
		pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
		pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
		pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;

	case "Santiago_Trip_12":
		dialog.text = "¡¿Qué demonios?!";
		link.l1 = "¡Prepárate a morir, bribón!";
		link.l1.go = "Santiago_Trip_13";
		break;

	case "Santiago_Trip_13":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Santiago_Trip_14":
		dialog.text = "¡Qué lío! Me preguntaba de qué se trataba todo este ruido. Mis felicitaciones, eres un tipo listo.";
		link.l1 = "Más listo de lo que piensas... ¡Veamos ahora qué puedes hacer contra un adversario armado!";
		link.l1.go = "Santiago_Trip_15";
		break;

	case "Santiago_Trip_15":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// офицер-посланник по 5 заданию
	case "HollQuest_Officer":
		dialog.text = "El señor Lucas Rodenburg quiere verte de inmediato. Ven a verlo enseguida.";
		link.l1 = "En mi camino.";
		link.l1.go = "HollQuest_Officer_exit";
		break;

	case "HollQuest_Officer_exit":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
		pchar.questTemp.HWIC.Holl = "MerdokStart";
		AddQuestRecord("Holl_Gambit", "1-36");
		break;

		//---------------------------------------------против всех----------------------------------------------
		// убрать испанского идальго
	case "Fernando":
		dialog.text = "¿Qué quieres de mí?";
		link.l1 = "¡Tu cabeza!";
		link.l1.go = "Fernando_fight";
		link.l2 = "Nada, no importa.";
		link.l2.go = "exit";
		NextDiag.TempNode = "Fernando_repeat";
		break;

	case "Fernando_repeat":
		dialog.text = "¿Eres tú otra vez? ¿Qué quieres de mí?! ¡Explícate!";
		link.l1 = "¡Tu cabeza!";
		link.l1.go = "Fernando_fight";
		link.l2 = "Nada, no importa.";
		link.l2.go = "exit";
		NextDiag.TempNode = "Fernando_repeat";
		break;

	case "Fernando_fight":
		chrDisableReloadToLocation = true; // выходы закроем
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
		LAi_group_Attack(NPChar, Pchar);
		SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
		pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
		pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;

	// в доме Флитвуда
	case "Fleetwood_soldier": // для любителей сунуть нос куда не надо
		if (CheckAttribute(npchar, "quest.talked"))
		{
			dialog.text = "¿Eres tú otra vez? ¿Por qué andas husmeando por aquí? No me gusta nada. Muy bien, te arrestaré y te enviaré a la oficina del comandante para una investigación. ¡Chicos, apresad a este tipo!";
			link.l1 = "Pero solo quería...";
			link.l1.go = "Fleetwood_soldier_4";
		}
		else
		{
			dialog.text = "¿Quién eres y qué quieres? ¡Explícate!";
			link.l1 = "Lo siento, señor, parece que he llegado a la casa equivocada. Le pido disculpas.";
			link.l1.go = "Fleetwood_soldier_1";
			link.l2 = "Me gustaría ver a Richard Fleetwood.";
			link.l2.go = "Fleetwood_soldier_2";
		}
		break;

	case "Fleetwood_soldier_1":
		dialog.text = "Así es. Estás hablando con el hombre equivocado. ¡Sé tan amable de irte de inmediato!";
		link.l1 = "Sí. Seguro.";
		link.l1.go = "Fleetwood_soldier_3";
		break;

	case "Fleetwood_soldier_2":
		dialog.text = "¿De verdad? ¿Quién te dijo que él vivía aquí? Parece sospechoso... Muy bien, te arrestaré y te enviaré a la oficina del comandante para una investigación. ¡Chicos, apresen a este tipo!";
		link.l1 = "Pero solo quería ver a Richard...";
		link.l1.go = "Fleetwood_soldier_4";
		break;

	case "Fleetwood_soldier_3":
		DialogExit();
		npchar.quest.talked = "true";
		DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
		pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
		pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
		pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier"; // для настырных
		break;

	case "Fleetwood_soldier_4":
		DialogExit();
		GoToPrison("SentJons", 1000, 10);
		break;

	case "Theft_soldier":
		dialog.text = "¡Ah! ¿Ladrones? ¿Espías? ¡Agarra bien tu sombrero ahora!";
		link.l1 = "¡Arre!";
		link.l1.go = "Attack_Theft_soldier";
		break;

	case "Attack_Theft_soldier":
		LAi_group_Delete("EnemyFight");
		LAi_SetHP(npchar, 500, 500);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Attack_soldier":
		dialog.text = "¡Ah! ¿Qué hace este tipo aquí? ¡Chicos, tenemos un espía aquí! ¡A las armas!";
		link.l1 = "¡Hop!";
		link.l1.go = "Attack_soldier_fight";
		break;

	case "Attack_soldier_fight":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // снять запрет драки
		LAi_group_Delete("EnemyFight");
		for (i = 1; i <= 4; i++)
		{
			sld = characterFromId("Attack_sold_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// Книппель-пленник в трюме
	case "Sailor_deck":
		chrDisableReloadToLocation = true;
		dialog.text = "Capitán, hemos interrogado a este granuja, tal como nos dijiste. Tuvimos que cauterizarlo un poco... Tenía esta carta con él. Intentó comérsela, pero no lo dejamos. Tal como pensábamos, iba a llevarse a una chica en Willemstad y llevarla a su jefe.";
		link.l1 = "¿Una carta? Vamos a echarle un vistazo. Luego hablaré con él yo mismo.";
		link.l1.go = "Sailor_deck_1";
		break;

	case "Sailor_deck_1":
		DialogExit();
		AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
		GiveItem2Character(pchar, "NPC_Letter");
		AddQuestRecordInfo("LetterToAbi", "1");
		break;

	case "Sailor_deck_2":
		dialog.text = "¿Cuáles son tus órdenes, Capitán?";
		link.l1 = "Lanza el cadáver por la borda. ¡Y prepárate para desembarcar!";
		link.l1.go = "Sailor_deck_3";
		// belamour legendary edition -->
		link.l2 = "Entiérrenlo en el mar con todos los honores militares. Ese viejo luchó valientemente hasta el último momento. Incluso cargó y apuntó ese cañón después de que fuera derribado de su carro. Una verdadera lástima. En otro mundo podríamos haber sido camaradas...";
		link.l2.go = "Sailor_deck_3a";
		break;

	case "Sailor_deck_3a":
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		AddCharacterExpToSkill(pchar, "Leadership", 120);
		dialog.text = "¡Aye, Capitán!";
		link.l1 = "...";
		link.l1.go = "Sailor_deck_4";
		break;

	case "Sailor_deck_3":
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		AddCharacterExpToSkill(pchar, "Sneak", 120);
		AddCharacterExpToSkill(pchar, "FencingL", 30);
		AddCharacterExpToSkill(pchar, "FencingS", 30);
		AddCharacterExpToSkill(pchar, "FencingH", 30);
		AddCharacterExpToSkill(pchar, "Pistol", 30);
		// <-- legendary edition
		dialog.text = "¡Sí, Capitán!";
		link.l1 = "...";
		link.l1.go = "Sailor_deck_4";
		break;

	case "Sailor_deck_4":
		DialogExit();
		chrDisableReloadToLocation = false;
		AddQuestRecord("Holl_Gambit", "3-21");
		LAi_SetActorType(pchar);
		sld = characterFromId("KnippelClone");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.lifeday = 0;
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("Sailor_" + i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
		}
		pchar.questTemp.HWIC.Self = "toVillemstad";
		sld = characterFromId("Solomon");
		sld.greeting = "solomon_2";
		AddLandQuestMark(sld, "questmarkmain");
		AddMapQuestMarkCity("Villemstad", false);
		LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);   // откроем дом Аби
		LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true); // закроем комнату Аби
		break;

	// Лонгвэй-пленник в трюме
	case "Sailor_deck_5":
		chrDisableReloadToLocation = true;
		dialog.text = "Hemos preparado al chino para el interrogatorio, tal como ordenaste, capitán. No llevaba nada encima, ni papeles. Se ha preparado un brasero, y en este momento estamos calentando los grilletes y las tenazas al rojo vivo.";
		link.l1 = "Buen trabajo, Alonso. Pero antes de que empieces, me gustaría intentar razonar con él. ¿Quizás decida cooperar de buena gana?";
		link.l1.go = "Sailor_deck_6";
		break;

	case "Sailor_deck_6":
		dialog.text = "Como usted diga, Capitán.";
		link.l1 = "... ";
		link.l1.go = "exit";
		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		break;

	case "Sailor_deck_7":
		dialog.text = "¿Sí, Capitán?";
		link.l1 = "Ponedle grilletes y vigiladlo en todo momento hasta que lleguemos a Guadalupe. Vosotros tres debéis estar siempre aquí. Respondéis con vuestras vidas por él.";
		link.l1.go = "Sailor_deck_8";
		break;

	case "Sailor_deck_8":
		dialog.text = "¡A la orden, Capitán!";
		link.l1 = "";
		link.l1.go = "Sailor_deck_9";
		break;

	case "Sailor_deck_9":
		chrDisableReloadToLocation = false;
		AddQuestRecord("Holl_Gambit", "3-48");
		sld = characterFromId("LongwayClone");
		LAi_SetActorType(sld);
		LAi_SetGroundSitType(sld);
		DialogExit();
		pchar.quest.Longway_Shore.win_condition.l1 = "location";
		pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
		pchar.quest.Longway_Shore.function = "LongwayInShore";
		AddMapQuestMarkShore("Shore31", true);
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		break;

	// пьяница - передача письма Флитвуду
	case "Drunkard":
		DelLandQuestMark(npchar);
		dialog.text = "¡H-ic! ¡Buenas noches, señor! ¿Qué le gustaría? ¿Quizás pueda comprarle una bebida a un viejo borracho? Y yo...";
		link.l1 = "Escucha aquí, viejo borracho... ¿Eres Jack Harrison?";
		link.l1.go = "Drunkard_1";
		break;

	case "Drunkard_1":
		dialog.text = "¡Oh! Sí, ese soy yo. ¿Quién más podría ser? ¿Por qué? ¿Qué haremos con un marinero borracho...?";
		link.l1 = "¡Oh mi Señor, dame paciencia! ¿Qué marinero? Está escrito en tu cara que eres un simple terrícola... ¿Quieres ganar algo de dinero?";
		link.l1.go = "Drunkard_2";
		break;

	case "Drunkard_2":
		dialog.text = "Siempre quiero ganar dinero. ¿Qué debo hacer? Pero no mataré a nadie. Y tampoco robaré nada. Y no eres mi tipo.";
		link.l1 = "No tendrás que matar a nadie, y dudo que realmente seas capaz de hacerlo. Eres demasiado torpe. Ahora. Aquí tienes una carta. Tómala y entrégala en la casa a la izquierda de la residencia del gobernador. Es para Richard Fleetwood.";
		link.l1.go = "Drunkard_3";
		break;

	case "Drunkard_3":
		dialog.text = "¿Para Richard Fleetwood? No... Me arrestarán en cuanto me vean.";
		link.l1 = "Cállate y escucha. Nadie va a arrestarte. Dirás que vienes de parte de Charlie Knippel en relación con Abigail. Te dejarán entrar. Repite lo que he dicho.";
		link.l1.go = "Drunkard_4";
		break;

	case "Drunkard_4":
		dialog.text = "¿Quién es Abigail? Conozco a Knippel...";
		link.l1 = "No es asunto tuyo. Cuanto menos sepas, más vivirás. Bueno, estoy esperando. Repite.";
		link.l1.go = "Drunkard_5";
		break;

	case "Drunkard_5":
		dialog.text = "He venido de parte de Charlie Knippel respecto a tu... Abigail. Eso es todo.";
		link.l1 = "Bien hecho. Recibirás 5000 pesos por el trabajo.";
		link.l1.go = "Drunkard_6";
		break;

	case "Drunkard_6":
		if (makeint(Pchar.money) >= 5000)
		{
			dialog.text = "¿5000 pesos? Oh.... ¿Sólo por entregar una carta?";
			link.l1 = "No. Se te dará otra carta. Vendrás con ella a la taberna y te sentarás aquí. La tomaré de ti. No hagas nada estúpido y no tengas miedo - te estaré vigilando y estaré cerca. Toma esta suma como adelanto para que te sientas más tranquilo.";
			link.l1.go = "Drunkard_7";
		}
		else
		{
			dialog.text = "¿Cinco mil? ¿Tienes siquiera tanto dinero?";
			link.l1 = "¡Ja! Por supuesto que sí. Lo traeré ahora.";
			link.l1.go = "Drunkard_no_money";
			NextDiag.CurrentNode = "Drunkard_no_money";
		}
		break;

	case "Drunkard_no_money":
		dialog.text = "¿Has traído los cinco mil?";
		if (makeint(Pchar.money) >= 5000)
		{
			link.l1 = "Sí. Aquí tienes. No te preocupes.";
			link.l1.go = "Drunkard_7";
		}
		else
		{
			link.l1 = "No. Espera. Volveré pronto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Drunkard_no_money";
		}
		break;

	case "Drunkard_7":
		AddMoneyToCharacter(pchar, -5000);
		RemoveItems(PChar, "MC_Letter", 1);
		dialog.text = "¿Hmm... debería ir ahora, señor?";
		link.l1 = "No, el jueves por la mañana... ¡Por supuesto, ahora mismo, cabeza de chorlito! ¡Ahora termina tu ron y vete!";
		link.l1.go = "Drunkard_8";
		break;

	case "Drunkard_8":
		DialogExit();
		AddQuestRecord("Holl_Gambit", "3-26");
		LAi_SetStayType(npchar);
		LAi_RemoveLoginTime(npchar); // удалить время загрузки
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
		chrDisableReloadToLocation = true; // закрыть локацию
		LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
		LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
		LocatorReloadEnterDisable("SentJons_town", "gate_back", true); // чтобы не сбежал
		break;

	case "Drunkard_9":
		DelLandQuestMark(npchar);
		dialog.text = "Ah, aquí está usted, señor... Habría sido mejor no hacerlo. Richard se enfureció cuando terminó de leer. Pensé que me mataría.";
		link.l1 = "¡Pero aquí estás! No te preocupes, no se atrevería a hacer eso; eras muy valioso para él en ese momento, ¡ja, ja! No puedes ni imaginar cuánto...";
		link.l1.go = "Drunkard_10";
		break;

	case "Drunkard_10":
		dialog.text = "Necesito tomar un trago... Aquí está su respuesta para ti.";
		link.l1 = "¡Dámelo! ¡Y cierra la boca!";
		link.l1.go = "Drunkard_11";
		break;

	case "Drunkard_11":
		GiveItem2Character(pchar, "MC_Letter");
		ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
		AddQuestRecordInfo("FleetwoodAnswer", "1");
		dialog.text = "Será difícil para mí hablar en los próximos días... Adiós... Deseo no volver a verte nunca más.";
		link.l1 = "¡Tómalo con calma, viejo borracho, ja-ja-ja! ¿Qu-é va-mos a ha-cer con un mari-ne-ro borra-cho...? ¡Bebe y relájate, ya todo ha terminado!";
		link.l1.go = "Drunkard_12";
		break;

	case "Drunkard_12":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		AddQuestRecord("Holl_Gambit", "3-27");
		pchar.questTemp.HWIC.Self = "FleetwoodAgree";
		AddCharacterExpToSkill(pchar, "Sneak", 300); // скрытность
		AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;

	// кэп курьерского судна
	case "Cureer_abordage":
		dialog.text = "¿Por qué diablos has atacado mi barco? No tengo ni objetos de valor ni dinero, solo papeles que de todas formas no te sirven de nada.";
		link.l1 = "Cállate. Has perdido, así que ahora me escucharás. No necesito ni tu barco, ni tus papeles. Necesito que le des este mensaje a tu jefe, esa rata sucia de Lucas Rodenburg. Dile que el capitán Fleetwood le envía saludos.";
		link.l1.go = "Cureer_abordage_1";
		break;

	case "Cureer_abordage_1":
		dialog.text = "¿Capitán Fleetwood? Pero...";
		link.l1 = "¿Le entregarás esta carta a tu jefe o debería atravesarte? También puedo buscar a otro candidato para la entrega. Robo barcos de tu sucia Compañía cada fin de semana por aburrimiento, para que lo sepas.";
		link.l1.go = "Cureer_abordage_2";
		break;

	case "Cureer_abordage_2":
		dialog.text = "Está bien, señor Fleetwood. Lo entregaré.";
		link.l1 = "Eso es genial. Ahora podemos despedirnos, Mynheer. Puedes considerarte muy afortunado hoy. ¡Y no olvides visitar una iglesia al llegar!";
		link.l1.go = "Cureer_abordage_3";
		break;

	case "Cureer_abordage_3":
		DialogExit();
		sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
		Lai_SetPlayerType(pchar);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, true);
		sld.ShipEnemyDisable = true;
		pchar.quest.HWICCureer_AfterBattle.over = "yes";
		pchar.quest.HWICCureerOnMapOver.over = "yes";
		AddQuestRecord("Holl_Gambit", "3-39");
		Log_TestInfo("LA CARTA HA SIDO ENTREGADA");
		RemoveItems(PChar, "MC_Letter", 1);
		pchar.questTemp.HWIC.Self = "LetterToLucasSent";
		pchar.quest.Curacao_exploring.win_condition.l1 = "location";
		pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
		pchar.quest.Curacao_exploring.function = "CuracaoExploring";
		DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
		AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddMapQuestMarkIsland("Curacao", true);
		break;

	// Матиас Бек в тюрьме
	case "MatiasBek": // на случай если геймер захочет пообщаться
		dialog.text = "¡Fui arrestado ilegalmente! ¡No tengo conexión con los ingleses! Esas son todas intrigas de Rodenburg. No importa. Peter Stuyvesant llegará pronto, ¡él lo resolverá todo!";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "MatiasBek";
		break;

	// стражник у входа в резиденцию
	case "QuestGuard":
		dialog.text = "El señor Lucas Rodenburg no desea ver a nadie en este momento. Tenga la amabilidad de abandonar la residencia de inmediato.";
		link.l1 = "Mm. Ya veo. Intentaré pasarme en una semana...";
		link.l1.go = "exit";
		NextDiag.TempNode = "QuestGuard";
		break;

	// Питер Стайвесант
	case "Stivesant":
		dialog.text = "Vamos a la residencia, Capitán. Ya he enviado a mi gente al fuerte para obtener información sobre Matthias Beck. Si realmente está en prisión en este momento, ya debe haber sido liberado y acompañado a la ciudad. ¡Sígueme!";
		link.l1 = "Sí, Mynheer Stuyvesant.";
		link.l1.go = "Stivesant_1";
		break;

	case "Stivesant_1":
		DialogExit();
		AddLandQuestMark(npchar, "questmarkmain");
		LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;

	case "ArestLucas_1":
		dialog.text = "¡Lucas! ¿Qué está ocurriendo aquí? ¿Dónde está Matthias Beck? ¿Es cierto que lo has enviado a prisión?";
		link.l1 = "";
		link.l1.go = "ArestLucas_2";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;

	case "ArestLucas_2":
		StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_3":
		dialog.text = "Hola, Mynheer Stuyvesant. Tengo pruebas de su conexión con la inteligencia británica y directamente con el capitán Fleetwood. Alertó al maldito británico para atacar nuestro bergantín correo y hacerse con la correspondencia confidencial de la Compañía.";
		link.l1 = "";
		link.l1.go = "ArestLucas_4";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;

	case "ArestLucas_4":
		StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_5":
		dialog.text = "¿Dónde conseguiste esta información?";
		link.l1 = "";
		link.l1.go = "ArestLucas_6";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;

	case "ArestLucas_6":
		StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_7":
		dialog.text = "Fue reclamado por el capitán del bergantín mensajero. Richard Fleetwood abordó su barco y le quitó los papeles; luego el barco quedó libre. Nadie, excepto yo, tú y Matthias Beck, tenía información ni sobre la ruta ni sobre el horario.";
		link.l1 = "";
		link.l1.go = "ArestLucas_8";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;

	case "ArestLucas_8":
		StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_9":
		dialog.text = "¿Y por eso has decidido que Beck avisó a Fleetwood para que atacara el bergantín? ¡Qué tontería! Fleetwood es un pirata ordinario; sólo ataca barcos mercantes. ¿Por qué iba a necesitar los papeles, que, por cierto, sólo contenían información contable?";
		link.l1 = "";
		link.l1.go = "ArestLucas_10";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;

	case "ArestLucas_10":
		StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_11":
		dialog.text = "Mynheer, el mensajero también transportaba otros documentos importantes de la Compañía, no solo los informes habituales. Y ahora todos están en manos de los británicos. Por eso decidí poner a Beck bajo arresto.";
		link.l1 = "";
		link.l1.go = "ArestLucas_12";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;

	case "ArestLucas_12":
		StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_13":
		dialog.text = "¡Maldita sea! ¡Esto es una verdadera usurpación de poder! ¿Te has dado cuenta de lo que has estado haciendo, Lucas? ¿Dónde está el capitán del bergantín correo?";
		link.l1 = "";
		link.l1.go = "ArestLucas_14";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;

	case "ArestLucas_14":
		StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_15":
		dialog.text = "Se ha ido a Philipsburg, Mynheer.";
		link.l1 = "";
		link.l1.go = "ArestLucas_16";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;

	case "ArestLucas_16":
		StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_17":
		dialog.text = "Está bien, entonces. He ordenado liberar a Beck. Lo traerán aquí y luego los tres tendremos una charla.";
		link.l1 = "";
		link.l1.go = "ArestLucas_18";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;

	case "ArestLucas_18":
		StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_19":
		dialog.text = "Está bien, no me importa. Nosotros tres - está bien. Hablemos.";
		link.l1 = "";
		link.l1.go = "ArestLucas_20";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;

	case "ArestLucas_20":
		DialogExit();
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
		locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
		DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;

	case "ArestLucas_40":
		dialog.text = "¡Pagarás por tu anarquía, Rodenburg! Tus acusaciones son absurdas. Ni siquiera me dejaste ver al capitán de la bergantín. No presentaste ninguna prueba, todas las acusaciones vinieron de ti personalmente.\n¡Juro por el Señor, soy inocente! ¡No tengo ni he tenido contacto alguno con los británicos!";
		link.l1 = "";
		link.l1.go = "ArestLucas_41";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;

	case "ArestLucas_41":
		StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_42":
		dialog.text = "¿Oh, de veras? Entonces, ¿cómo se enteró Fleetwood de nuestro bergantín y que no solo tenía los documentos habituales a bordo?";
		link.l1 = "";
		link.l1.go = "ArestLucas_43";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;

	case "ArestLucas_43":
		dialog.text = "...";
		link.l1 = "Rodenburg está mintiendo. Richard Fleetwood no pudo haber atacado el bergantín correo.";
		link.l1.go = "ArestLucas_44";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, pchar);
		sld = characterFromId("Stivesant");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		sld = characterFromId("Villemstad_Mayor");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		break;

	case "ArestLucas_44":
		dialog.text = "¿Y quién eres tú, señor? ¿En qué bases haces tales declaraciones?";
		link.l1 = "Mi nombre es " + GetFullName(pchar) + ". Yo personalmente eliminé al capitán Fleetwood atrayéndolo a una trampa. Su cadáver está siendo devorado por gaviotas en las costas de los Turcos. Los oficiales no lograron protegernos, a nosotros, los comerciantes holandeses, de su agresión, así que lo liquidé yo mismo. Y sucedió antes de que el bergantín correo fuera saqueado...";
		link.l1.go = "ArestLucas_46";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, pchar);
		break;

	case "ArestLucas_46":
		dialog.text = "";
		link.l1 = "Fleetwood simplemente no pudo haberlo hecho, ya estaba muerto. Me he enterado por los lugareños en la taberna que Mathias Beck fue arrestado, así que decidí investigar el asunto, porque siempre creí que el señor Beck es un hombre de reputación cristalina...";
		link.l1.go = "ArestLucas_47";
		break;

	case "ArestLucas_47":
		dialog.text = "";
		link.l1 = "La gente en el puerto me dijo que cargaste tu jabeque con todo tipo de criminales y mercenarios, los guardias de la Compañía se quedaron en tierra. Seguí tu barco y lo capturé, matando a cada matón que contrataste. Interrogué al capitán Longway, a cambio de su libertad me contó todo, señor Rodenburg...";
		link.l1.go = "ArestLucas_48";
		break;

	case "ArestLucas_48":
		dialog.text = "";
		link.l1 = "Planeabas tomar el poder sobre Curazao y ordenaste a Longway hundir el galeón del señor Stuyvesant. Conociendo tus métodos, estoy seguro de que el pobre capitán del bergantín está muerto. Debes haber organizado un ataque al buque correo para crear un precedente, ¿verdad? ¿Y este acto fue realizado por tu asesino, llamado Jacob van Berg? Longway me contó mucho sobre ese hombre.";
		link.l1.go = "ArestLucas_49";
		break;

	case "ArestLucas_49":
		dialog.text = "¡Esto ... esto es una mentira descarada! ¿De qué estás hablando, Mynheer? ¿Quién diablos eres tú?";
		link.l1 = "¡Soy un capitán independiente que quería limpiar el mar y la tierra de ese sinvergüenza Fleetwood y que se involucró en tus intrigas políticas! Advertí al señor Stuyvesant del peligro en el que se encontraba. ¡Y estoy aquí para poner fin a tus depredaciones en Curazao, junto con las autoridades legales!";
		link.l1.go = "ArestLucas_50";
		break;

	case "ArestLucas_50":
		dialog.text = "¡Qué insolencia! ¡Responderás por tus palabras, Mynheer 'capitán independiente'! Tú...";
		link.l1 = "";
		link.l1.go = "ArestLucas_51";
		break;

	case "ArestLucas_51":
		StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_52":
		dialog.text = "¡Basta, Lucas! ¡Pagarás por tus crímenes! He oído y visto suficiente. Lucas Rodenburg, te arresto por un intento contra la vida del director de la Compañía, por un intento de tomar el poder por la fuerza y por la sospecha de asesinar al capitán del barco mensajero.\nAdemás, estoy seguro de que durante la investigación oficial descubriremos más sobre las partes interesantes de tu biografía. Serás puesto bajo custodia y entregado a Ámsterdam, donde serás procesado. ¡Llévenlo!";
		link.l1 = "";
		link.l1.go = "ArestLucas_53";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		sld = characterFromId("Lucas");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));
		break;

	case "ArestLucas_53":
		StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;

	case "ArestLucas_54":
		dialog.text = "Pero...";
		link.l1 = "";
		link.l1.go = "ArestLucas_55";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;

	case "ArestLucas_55":
		DialogExit();
		LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
		sld = characterFromId("Lucas");
		LAi_SetImmortal(sld, true); // защита от хитреца
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
		for (i = 3; i <= 5; i++)
		{
			sld = characterFromId("StivesantGuard_" + i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
		}
		LAi_SetActorType(PChar);
		locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
		DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;

	case "Stivesant_10":
		dialog.text = "Capitán " + GetFullName(pchar) + "¡En nombre de la administración de la colonia de Willemstad, le pido amablemente que acepte nuestra sincera gratitud por sus acciones, que nos ayudaron a arrestar a ese peligroso criminal. También me gustaría agradecerle personalmente, ya que probablemente le deba mi vida!";
		link.l1 = "Actué por el bien de todas las colonias holandesas, Mynheer.";
		link.l1.go = "Stivesant_11";
		break;

	case "Stivesant_11":
		dialog.text = "Tu modestia impone respeto, mi amigo. Ahora me gustaría resolver algunas formalidades: dado que capturaste el Meifeng solo con buenos propósitos y en apuros, no puede haber reclamaciones. Pero este barco pertenece a la Compañía y te pido amablemente que lo devuelvas.";
		link.l1 = "Ciertamente, señor.";
		link.l1.go = "Stivesant_12";
		break;

	case "Stivesant_12":
		// удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // удаляем атрибут квестового корабля
		if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0); // сажаем на тартану
		}
		else
		{
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int iTemp = GetCompanionIndex(PChar, i);
				if (iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
		dialog.text = "Por favor, ven a mi residencia mañana - serás recompensado en nombre de la República de las Provincias Libres por tus acciones en su mejor interés. Te ruego amablemente que no abandones la ciudad.";
		link.l1 = "De acuerdo, señor. Pasaré mañana.";
		link.l1.go = "Stivesant_13";
		break;

	case "Stivesant_13":
		DialogExit();
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		sld.dialog.currentnode = "Bek_2";
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "Bek_2":
		dialog.text = "También me gustaría agradecerle personalmente, Capitán, por su espíritu emprendedor y oportuna asistencia. No olvide venir aquí mañana, prepararé un valioso regalo para usted.";
		link.l1 = "¡Gracias, señor Beck! ¡Allí estaré!";
		link.l1.go = "Bek_3";
		break;

	case "Bek_3":
		DialogExit();
		pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
		pchar.quest.Award_FromPiter.win_condition.l1.date.hour = 9.0;
		pchar.quest.Award_FromPiter.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Award_FromPiter.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
		bDisableFastReload = false;
		LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
		LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
		LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true); // закрыть вход в резиденцию
		LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);		// закрыть боковой вход в резиденцию
		AddQuestRecord("Holl_Gambit", "3-53");
		DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
		for (i = 4; i <= 5; i++)
		{
			sld = characterFromId("StivesantGuard_" + i);
			sld.lifeday = 0; // подчистим солдат
		}
		break;

	case "Stivesant_14":
		dialog.text = "" + GetFullName(pchar) + ", en nombre de la República de las Provincias Libres, se le otorga por la presente un arma personal y dinero por la cantidad de 100 000 pesos por la iniciativa tomada en la liquidación del enemigo de todos los holandeses, el criminal del estado Richard Fleetwood. ¡Felicitaciones!";
		link.l1 = "¡Gracias, Mynheer Styuvesant!";
		link.l1.go = "Stivesant_15";
		break;

	case "Stivesant_15":
		dialog.text = "Además, por un coraje sin precedentes, por la exposición de una traicionera conspiración dentro de la Compañía y por la arriesgada operación de capturar al ex vicepresidente de la Compañía, se le otorgan 150 000 pesos. También se le permitirá firmar contratos con la Compañía Holandesa de las Indias Occidentales.\nEstoy seguro de que nuestro nuevo vicedirector encontrará un trabajo bien remunerado para un capitán tan valiente como usted.";
		link.l1 = "¡Gracias! Lo tendré en cuenta.";
		link.l1.go = "Stivesant_16";
		break;

	case "Stivesant_16":
		AddMoneyToCharacter(pchar, 250000);
		GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		dialog.text = "Ten en cuenta que siempre puedes contar con mi asistencia en cualquier asunto mientras actúes del lado y en interés de Holanda. Ahora escuchemos lo que tiene que decir el gobernador de Willemstad, Matthias Beck.";
		link.l1 = "";
		link.l1.go = "Stivesant_17";
		break;

	case "Stivesant_17":
		DialogExit();
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		LAi_SetActorType(sld);
		sld.dialog.currentnode = "Bek_4";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "Bek_4":
		dialog.text = "Expreso mi más sincera gratitud, Capitán, por su valentía y perspicacia al descubrir un complot contra el estado. Me gustaría presentarle este valioso instrumento de navegación, que es invaluable para cualquier hombre de guerra.";
		link.l1 = "Gracias, señor Beck";
		link.l1.go = "Bek_5";
		break;

	case "Bek_5":
		GiveItem2Character(pchar, "bussol");
		dialog.text = "Quisiera que supieras: ahora eres mi amigo, y eso significa mucho. Siempre serás un huésped bienvenido en mi residencia. Ven cuando quieras y por cualquier motivo: estaré feliz de proporcionarte cualquier ayuda que necesites.";
		link.l1 = "¡Me alegra escuchar eso, Mynheer!";
		link.l1.go = "Bek_6";
		break;

	case "Bek_6": // наведем порядок в городе
		DialogExit();
		AddQuestRecord("Holl_Gambit", "3-54");
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		LAi_SetHuberStayType(sld);
		sld.Dialog.Filename = "Common_Mayor.c"; // patch-8
		sld.dialog.currentnode = "First time";
		sld.quest.meeting = "1";
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("StivesantGuard_" + i);
			sld.lifeday = 0; // подчистим солдат
		}
		sld = characterFromId("Stivesant");
		LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
		bDisableFastReload = false;
		LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
		LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
		LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
		AddCharacterExpToSkill(pchar, "Fortune", 100); // везение
		DelMapQuestMarkCity("Villemstad");
		break;

	case "Bek_7":
		dialog.text = "Holanda está orgullosa de usted, Mynheer. Capitanes como usted son la columna vertebral de la Flota Holandesa en el Caribe. Aquí tiene, por favor acepte su recompensa.";
		link.l1 = "Gracias, señor. ¡Es un honor servir a Holanda!";
		link.l1.go = "Bek_8";
		break;

	case "Bek_8":
		TakeNItems(pchar, "gold_dublon", 1000);
		ChangeCharacterComplexReputation(pchar, "authority", 5);
		ChangeCharacterNationReputation(pchar, HOLLAND, 20);
		DialogExit();
		sld = characterFromId("Lucas");
		LAi_SetActorType(sld);
		sld.dialog.currentnode = "LucasAward_2";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "Stivesant_18":
		dialog.text = "Me alegra verte. ¿Cómo estás?";
		link.l1 = "Estoy bien. Solo pasé a verte.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Stivesant_18";
		break;

	// Jason НСО
	case "Stivesant_19":
		if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
		{
			dialog.text = "¡Mira quién es! Es " + GetFullName(pchar) + ". Recientemente enviamos a nuestros cazatalentos, quienes tuvieron que traerte aquí. Y ese servicio costó mucho.";
			link.l1 = "Uhm... Debería irme...";
			link.l1.go = "arest";
			break;
		}
		// belamour legendary edition фикс проверки мундира с мушкетом
		if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
		{
			dialog.text = "¿Eres capitán de la Marina Francesa? Bien, tengo poco tiempo, pero escucharé lo que tienes que decir. ¿Qué te trae por aquí?";
			link.l1 = "Mynheer Stuyvesant, he venido de Saint Christopher con un mensaje del Gobernador General de las colonias francesas, el Caballero de Poincy.";
			link.l1.go = "Stivesant_20";
		}
		else
		{
			dialog.text = "Disculpe, Capitán, pero estoy extremadamente ocupado en este momento y no puedo dedicarle suficiente tiempo. Hable con el señor Mathias Beck, déjelo escuchar lo que tiene que decir.";
			link.l1 = "Mm...";
			link.l1.go = "Stivesant_19_1";
		}
		break;

	case "Stivesant_19_1":
		DialogExit();
		npchar.dialog.currentnode = "Stivesant_19";
		break;

	case "Stivesant_20":
		sld = characterFromId("Patria_FlautCap");
		dialog.text = "¿Del Caballero de Poincy? Definitivamente no esperaba que tomara tan poco... ejem... ¿cómo está el Caballero?";
		link.l1 = "Todo está bien, Mynheer. Monsieur de Poincy me ordenó entregarle esta carta. Mi otra tarea era escoltar '" + sld.ship.name + "con carga para su compañía al puerto de Willemstad. El barco está en el muelle y la carga no fue dañada.";
		link.l1.go = "Stivesant_21";
		break;

	case "Stivesant_21":
		dialog.text = "¿Una flota con carga para nuestra compañía? Intrigante... ¿Y la carta, Capitán?";
		link.l1 = "Aquí. Por favor, tómalo.";
		link.l1.go = "Stivesant_22";
		break;

	case "Stivesant_22":
		RemoveItems(pchar, "Reserve_item_01", 1);
		dialog.text = "Hmmm... (leyendo). Una inspección del estado padre... Ahem... Vaya, bueno... eso es interesante, je-je... Por cierto, Capitán, ¿he oído que Francia está en guerra con España en el Caribe? El asedio y saqueo del fuerte de San José, la destrucción del escuadrón de guerra español frente a la costa oriental de Cuba...";
		link.l1 = "Fuera de la costa occidental de La Española, por Port-au-Prince, señor. Y el único objetivo del asedio de San José era obtener una compensación financiera de los españoles por su ataque a Saint-Pierre. Estamos en malos términos con España desde hace tiempo... ¿Cuándo debo regresar para recoger la respuesta?";
		link.l1.go = "Stivesant_23";
		break;

	case "Stivesant_23":
		dialog.text = "No te detendré, Capitán, eres un hombre militar, probablemente tengas muchos asuntos y estoy seguro de que el Chevalier espera ansiosamente tu regreso. Sé tan amable de esperar aquí, en la sala de estar, durante dos horas hasta que componga una respuesta a esa carta. Toma asiento y descansa aquí, te servirán vino o ron, si lo deseas...";
		link.l1 = "Mi gratitud, Mynheer, preferiría una copa de buen vino...";
		link.l1.go = "Stivesant_24";
		break;

	case "Stivesant_24":
		chrDisableReloadToLocation = true;				// закрыть локацию
		pchar.quest.Patria_CureerTimeOver.over = "yes"; // снять таймер
		pchar.quest.Patria_CureerFail.over = "yes";		// снять прерывание
		sld = characterFromId("Patria_FlautCap");
		RemoveCharacterCompanion(pchar, sld);
		sld.lifeday = 0;
		DialogExit();
		npchar.dialog.currentnode = "Stivesant_25";
		LAi_SetActorType(npchar);
		ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
		LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
		pchar.questTemp.Patria = "epizode_4_return";
		break;

	case "Stivesant_25":
		GiveItem2Character(pchar, "Reserve_item_01");
		ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
		dialog.text = "La respuesta para monsieur de Poincy está lista. Aquí, por favor, llévela... Buena suerte, capitán.";
		link.l1 = "Gracias, señor. ¡Adiós!";
		link.l1.go = "Stivesant_26";
		break;

	case "Stivesant_26":
		DialogExit();
		npchar.dialog.currentnode = "Stivesant_19";
		chrDisableReloadToLocation = false;
		AddQuestRecord("Patria", "23");
		SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;

	case "Stivesant_27":
		if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
		{
			dialog.text = "¡Mira quién es! Es " + GetFullName(pchar) + "Recientemente hemos enviado a nuestros cazatalentos, quienes debían traerte aquí. Y ese servicio ha costado mucho.";
			link.l1 = "Uhm... Debería irme...";
			link.l1.go = "arest";
			break;
		}
		if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
		{
			dialog.text = "Has venido otra vez con un mensaje del Gobernador General Philippe de Poincy, ¿verdad?";
			link.l1 = "Sí, Mynheer Stuyvesant. En las costas de Sint Maarten hubo un desagradable malentendido: un barco que transportaba al inspector de París, el Barón Noel Forget, fue disparado por el fuerte de Philipsburg, y...";
			link.l1.go = "Stivesant_28";
		}
		else
		{
			dialog.text = "Disculpe, Capitán, pero estoy extremadamente ocupado en este momento y no puedo dedicarle suficiente tiempo. Hable con mynheer Mathias Beck, que él escuche lo que tiene que decir.";
			link.l1 = "Mm...";
			link.l1.go = "Stivesant_27_1";
		}
		break;

	case "Stivesant_27_1":
		DialogExit();
		npchar.dialog.currentnode = "Stivesant_27";
		break;

	case "Stivesant_28":
		if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
		{
			dialog.text = "Y por eso estás aquí, Capitán. No entraré en discusiones diplomáticas: dile al Caballero que ya no está a cargo de Sint Maarten. Basta de él. Y en cuanto a la inspección del estado matriz, que se invente algo. Nunca fue difícil para de Poincy poner todo patas arriba.";
			link.l1 = "¿Es eso exactamente lo que debo decirle?";
			link.l1.go = "Stivesant_29";
		}
		else
		{
			dialog.text = "Y por eso estás aquí, Capitán. No entraré en discusiones diplomáticas: tu señor ha sido demasiado codicioso en Sint Maarten últimamente, así que es hora de moderar su insaciable hambre. Y creo que él lo entiende perfectamente. A ti, Capitán Charles de Maure, también tenemos preguntas sobre eventos recientes relacionados con el bandido británico llamado Richard Fleetwood, así que tendrás que quedarte aquí un tiempo. \n¡Sargento! ¡Tomen las armas del capitán y llévenlo a la oficina del comandante!";
			link.l1 = "¡Retrasar a un oficial francés en servicio es inaceptable!";
			link.l1.go = "Stivesant_31";
		}
		break;

	case "Stivesant_29":
		dialog.text = "No podría haberlo dicho mejor yo mismo, Capitán. Su comandante entenderá todo, pero no necesita profundizar en ello, eso no cambiará nada. Le deseo lo mejor. ¡Sargento, lleve a Monsieur Charles de Maure a la salida!";
		link.l1 = "...";
		link.l1.go = "Stivesant_30";
		break;

	case "Stivesant_30":
		DialogExit();
		DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;

	case "Stivesant_31":
		dialog.text = "Lamentablemente, tengo una opinión diferente. ¡Sargento! ¡En caso de resistencia, usen la fuerza!";
		link.l1 = "Simplemente no sabes con quién estás tratando todavía, Mynheer ...";
		link.l1.go = "Stivesant_32";
		break;

	case "Stivesant_32":
		DialogExit();
		Patria_DiplomatFight();
		break;

	case "Stivesant_33":
		dialog.text = "Es un poco extraño verte, Capitán Charles de Maure, en este papel... Espero que puedas garantizar inmunidad para aquellos que vienen a ti para negociaciones.";
		link.l1 = "Puedes estar seguro de ello, señor Stuyvesant.";
		link.l1.go = "Stivesant_34";
		break;

	case "Stivesant_34":
		dialog.text = "Entonces, ¿puedes darme la oportunidad de leer el acuerdo que has preparado? Según entiendo, ¿contiene contenido de la carta?";
		link.l1 = "Precisamente, señor, solo en forma oficial. Por parte de Francia - restauración de relaciones a neutrales, renuncia a cualquier reclamación sobre la isla de Sint Maarten. Por parte de Inglaterra - el fin de la guerra comercial. Los detalles están todos descritos aquí ... Y, por supuesto, compensación financiera por los daños que sufrimos debido a las acciones militares que ustedes iniciaron.";
		link.l1.go = "Stivesant_35";
		break;

	case "Stivesant_35":
		dialog.text = "Por favor, sea tan amable de darme el documento.";
		link.l1 = "Por supuesto.";
		link.l1.go = "Stivesant_36";
		break;

	case "Stivesant_36":
		dialog.text = "...(leyendo)...";
		link.l1 = "... ";
		link.l1.go = "Stivesant_37";
		break;

	case "Stivesant_37":
		LAi_Fade("", "");
		dialog.text = "Ya que no me dejaste elección, firmaré este acuerdo. Pero para mí, la protección de Willemstad y sus habitantes es de suma importancia";
		link.l1 = "Entonces validaremos las tres copias con firmas. Estoy autorizado por el Gobernador General Philippe de Poincy para endosar el documento por el lado de Francia, el Coronel Doily lo firmará por Inglaterra.";
		link.l1.go = "Stivesant_38";
		break;

	case "Stivesant_38":
		dialog.text = "...(firmando)...";
		link.l1 = "¡Perfecto! Ahora deberíamos firmar esto...";
		link.l1.go = "Stivesant_39";
		break;

	case "Stivesant_39":
		LAi_Fade("", "");
		dialog.text = "Entonces, ¿creo que levantarás el sitio ahora?";
		link.l1 = "Sin duda. Espero que todas las condiciones del acuerdo sean respetadas por el lado holandés sin violaciones.";
		link.l1.go = "Stivesant_40";
		break;

	case "Stivesant_40":
		dialog.text = "Si no hay violaciones por parte de Inglaterra o Francia, entonces cumpliremos con los términos del contrato, no te preocupes.";
		link.l1 = "Siempre es mejor comerciar que luchar, Mynheer Stuyvesant. Y ahora puede regresar a Willemstad con seguridad. El asedio se levantará y nuestra escuadra pronto abandonará las aguas de Curazao.";
		link.l1.go = "Stivesant_41";
		break;

	case "Stivesant_41":
		DialogExit(); // Стайвесант уходит, подходит д'Ойли
		Patria_CuracaoStivesantGo();
		break;

	case "Stivesant_42":
		dialog.text = "Entonces, ¿sois el Barón Noel Forget? ¡Ah, y vos debéis ser el mismísimo Monsieur Charles de Maure! ¡Saludos, Vicealmirante! Hay una razón por la cual se os conoce como el intrigante más astuto del archipiélago: uno nunca sabe de qué lado estáis en este momento...";
		link.l1 = "El Vicealmirante está del lado del Rey y del vuestro sinceramente, su representante titulado, en este momento.";
		link.l1.go = "Stivesant_43";
		break;

	case "Stivesant_43":
		dialog.text = "El Rey está lejos de aquí, y también lo está Francia, Barón, pero San Cristóbal y el Caballero de Poincy están cerca. Él es el verdadero dueño de las colonias francesas. De facto... Sin embargo, ¿estás aquí para conseguir algo que comprometa a de Poincy ante los ojos del ministro de finanzas?";
		link.l1 = "Precisamente, Mynheer.";
		link.l1.go = "Stivesant_44";
		break;

	case "Stivesant_44":
		dialog.text = "Tengo tales documentos. Este es un libro mayor completo con mis cuentas y las de De Poincy para la mina y algunos otros asuntos. También en él encontrarás un montón de papeles relacionados con este negocio, con la firma personal de Philippe de Poincy. Te garantizo que el contenido de estos papeles en manos de una persona interesada hundirá al Chevalier más profundo que el fondo del Mar Caribe.";
		link.l1 = "¿Qué quieres por este libro de cuentas?";
		link.l1.go = "Stivesant_45";
		break;

	case "Stivesant_45":
		dialog.text = "Lo vendo por una canción. Apenas un millón de pesos en plata.";
		link.l1 = "¡¿Un millón de pesos?!!";
		link.l1.go = "Stivesant_46";
		break;

	case "Stivesant_46":
		dialog.text = "Eso es correcto, Barón. Esta cantidad al menos cubrirá parcialmente las pérdidas causadas por la reciente guerra. Le daré un consejo: recurra al Monsieur Charles de Maure. Durante su servicio para de Poincy y ejem... otras personas, probablemente hizo una gran fortuna, y conseguir un millón no será un problema para él. Estoy casi seguro de ello.\nLe daré un plazo - un mes. Después de este tiempo, si no trae la cantidad indicada, enviaré una carta al Caballero, en la que describiré los detalles de su visita a mí. Puede adivinar lo que sucede después.";
		link.l1 = "¡Me estás chantajeando! ¡Debes entender que no puedo tener un millón en las colonias!";
		link.l1.go = "Stivesant_47";
		break;

	case "Stivesant_47":
		dialog.text = "Por supuesto que entiendo. Por lo tanto, inmediatamente le señalé a la persona que tiene este millón. Si Monsieur de Maure se niega, lo mejor para usted, Barón, es zarpar hacia Europa antes de que el Caballero reciba mi carta, de lo contrario corre el riesgo de quedarse aquí para siempre. En cuanto a Monsieur de Maure... por supuesto, perderá su rango de almirante, pero saldrá... y tal vez incluso se deshaga de de Poincy con sus métodos, estoy perfectamente de acuerdo con eso.\nBueno, caballeros, me han escuchado. Los estaré esperando con un millón en un mes en mi residencia. Entrada y salida libres garantizadas.";
		link.l1 = "...";
		link.l1.go = "Stivesant_48";
		break;

	case "Stivesant_48":
		DialogExit();
		LAi_SetActorType(pchar);
		SetMainCharacterIndex(GetCharacterIndex("Blaze"));
		pchar = GetMainCharacter();
		LAi_SetPlayerType(pchar);
		locCameraTarget(pchar);
		locCameraFollow();
		EndQuestMovie();
		InterfaceStates.Buttons.Save.enable = true;
		bDisableCharacterMenu = false;
		sld = CharacterFromID("Noel");
		sld.dialog.currentnode = "noel_84";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		sld = CharacterFromID("Stivesant");
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
		for (i = 1; i <= 3; i++)
		{
			sld = CharacterFromID("Stivesant_sold_" + i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
		}
		break;

	case "Stivesant_49":
		if (sti(pchar.money) >= 1000000)
		{
			dialog.text = "No dudé ni por un momento, vicealmirante Charles de Maure, que me traerías este dinero. Quizás, incluso, te pedí demasiado poco, pero bueno... El barón es solo un peón en tu próximo juego, ¿verdad? El rango y el dinero no son suficientes para ti, ahora quieres ocupar el lugar de De Poincy, ¿no es así? Tienes que admitirlo, un millón es una suma pequeña para el puesto de Gobernador General de las colonias francesas. Recuperarás ese dinero en cuestión de meses, dada tu férrea determinación.";
			link.l1 = "Tome su millón, Mynheer. Me gustaría recibir mi libro de cuentas prometido.";
			link.l1.go = "Stivesant_50";
		}
		else
		{
			dialog.text = "Mejor concéntrate en reunir el millón, Monsieur, en lugar de perder el tiempo en visitas inútiles.";
			link.l1 = "...";
			link.l1.go = "Stivesant_49_1";
		}
		break;

	case "Stivesant_49_1":
		DialogExit();
		npchar.dialog.currentnode = "Stivesant_49";
		break;

	case "Stivesant_50":
		pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
		AddMoneyToCharacter(pchar, -1000000);
		GiveItem2Character(pchar, "Reserve_item_01");
		ref itm = ItemsFromID("Reserve_item_01");
		itm.picIndex = 15;
		itm.picTexture = "ITEMS_26";
		itm.price = 0;
		itm.Weight = 2.0;
		itm.name = "itmname_Reserve_item_01_1";
		ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
		dialog.text = "Por supuesto, Vicealmirante. Y no frunza el ceño: cuando se convierta en Gobernador General, verá que la Compañía Holandesa de las Indias Occidentales es un socio comercial más rentable que los codiciosos y belicosos británicos. ¿No sabe usted que si le da un dedo a un británico, se llevará toda la mano? Si no, lo aprenderá por las malas. Así que aún no me despido de usted. Guarde sus papeles. Espero que su barón sea lo suficientemente competente para derrotar al Caballero.";
		link.l1 = "Te lo agradezco Adiós, Mynheer Stuvesant.";
		link.l1.go = "Stivesant_51";
		break;

	case "Stivesant_51":
		DialogExit();
		AddQuestRecord("Patria", "84");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
		pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
		pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;

	case "vanberg_sold":
		dialog.text = "¡Ja-ja-ja! ¡Mira eso! Jacob tenía razón, como siempre: este zorro fue a la isla por una buena razón. Parece que hay una buena pila de oro en el cofre. Muy imprudente de tu parte venir aquí solo, amigo. Pero, de nuevo, ¡facilita mucho nuestro trabajo!";
		link.l1 = "¡Esos bastardos me han encontrado! No lo vi venir... ¡Pero no seré una presa fácil!";
		link.l1.go = "vanberg_sold_1";
		break;

	case "vanberg_sold_1":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		for (i = 1; i <= 4; i++)
		{
			sld = characterFromId("vanberg_sold_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Abihouselady":
		dialog.text = "¿Estás buscando a alguien?";
		link.l1 = "Así es. ¿Dónde están Solomon y Abigail Shneur?";
		link.l1.go = "Abihouselady_1";
		break;

	case "Abihouselady_1":
		dialog.text = "Ya no viven aquí. Simplemente no podían permitirse el lugar. Abigail, pobre chica, trabaja como una de las sirvientas del gobernador. Trabaja duro cada día para ganarse la vida para ella y su padre. Salomón bebe en la taberna todos los días, no puede soportar lo que les pasó. Ahora viven en una pequeña choza no lejos del mar...";
		link.l1 = "Oh... Está bien, gracias por la información. Tengo que irme.";
		link.l1.go = "Abihouselady_2";
		break;

	case "Abihouselady_2":
		DialogExit();
		NextDiag.CurrentNode = "Abihouselady_3";
		break;

	case "Abihouselady_3":
		dialog.text = "¿Qué más le gustaría saber, señor?";
		link.l1 = "Nada, no importa.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Abihouselady_3";
		break;

	// удаление Мейфенг при провале квеста
	case "TempOffGuard":
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // удаляем атрибут квестового корабля
		if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0); // сажаем на тартану
		}
		else
		{
			for (i = 1; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if (iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
		dialog.text = "Capitán, usted se apropió indebidamente de un barco de la Compañía Holandesa de las Indias Occidentales. Estoy autorizado a confiscarlo y a usar la fuerza en caso de resistencia. Esta es una orden de Peter Stuyvesant.";
		link.l1 = "Bueno, si es una orden del propio Peter Stuyvesant... No iré a la guerra con Holanda por un barco. Tómalo.";
		link.l1.go = "TempOffGuard_1";
		break;

	case "TempOffGuard_1":
		dialog.text = "Bien por ti mostrar razón.";
		link.l1 = "... ";
		link.l1.go = "TempOffGuard_2";
		break;

	case "TempOffGuard_2":
		DialogExit();
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
		chrDisableReloadToLocation = false; // открыть локацию
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;

	// Jason НСО
	case "arest":
		dialog.text = "Por supuesto que es hora de irse, incluso tendrás compañía. ¡Guardias! ¡Atrápenlo!";
		link.l1 = "¡Hazme hacerlo!";
		link.l1.go = "fight";
		break;

	case "fight":
		Pchar.quest.ArestInResidenceEnd.win_condition.l1 = "ExitFromLocation";
		Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		Pchar.quest.ArestInResidenceEnd.win_condition = "ArestInResidenceEnd";
		Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_LockFightMode(Pchar, true); // ножками путь убегает
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_group_Attack(NPChar, Pchar);							   // не работает на бессмертного мера :(
		i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
		if (i != -1)
		{
			LAi_group_Attack(&Characters[i], Pchar);
		}
		break;

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		dialog.text = NPCharSexPhrase(NPChar, "¡Oye, escucha! Como ciudadano de esta ciudad, te pido amablemente que no camines por ahí con una espada desenvainada.", "Sabes, como ciudadano de este pueblo, te pido amablemente que no pasees con una hoja desenvainada.");
		link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como dices...");
		link.l1.go = "exit";
		break;
	}
}
