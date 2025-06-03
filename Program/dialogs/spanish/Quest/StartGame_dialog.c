// Диалог начала игры (туториал) 03.10.06 boal
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref sld;

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Finish_2":
		SetAchievement("Test_Ach");
		dialog.text = "Capitán, una última pregunta. ¿Qué mensaje debo transmitir a la tripulación?";
		link.l1 = "¿Qué quieres decir?";
		link.l1.go = "Finish_2_0";
		break;

	case "Finish_2_0":
		dialog.text = "La gente quiere saber qué esperar. Parece que aún no te has decidido.";
		link.l1 = "¿Cuáles son mis opciones?";
		link.l1.go = "Finish_2_0_1";
		break;

	case "Finish_2_0_1":
		dialog.text = "Bueno, Capitán, el Caribe es un lugar único. Puedes dedicarte al comercio, saquear, sumergirte en asuntos turbios o embarcarte en búsquedas de tesoros; hay innumerables caminos para convertirse en una leyenda en estas aguas. La tripulación y yo lo hemos discutido, y estamos listos para apoyar cualquier elección que hagas.";
		link.l1 = "¿Tengo que elegir sólo uno?";
		link.l1.go = "Finish_2_0_2";
		break;

	case "Finish_2_0_2":
		dialog.text = "No, ciertamente no, pero es una buena idea establecer nuestras prioridades iniciales.";
		link.l1 = "¡Como cualquier hombre sensato, quiero amasar una fortuna! Un millón de pesos sería suficiente.";
		link.l1.go = "Finish_2_1";
		link.l2 = "Me propongo ganar respeto, del tipo que tenía l'Olonnais después de saquear Maracaibo.";
		link.l2.go = "Finish_2_2";
		link.l3 = "¡Aventura! Anhelo explorar lugares exóticos y encontrarme con personajes curiosos.";
		link.l3.go = "Finish_2_3";
		link.l4 = "¡Siempre he soñado con el atractivo romántico de ser un cazador de tesoros!";
		link.l4.go = "Finish_2_4";
		link.l5 = "Guarda tus consejos, Alonso. ¿Por qué limitarme? ¡Sé lo que quiero, y lo quiero todo!";
		link.l5.go = "Finish_2_5";
		break;

	case "Finish_2_1":
		pchar.questTemp.SanBoxTarget = 1;
		dialog.text = "Eso es una gran ambición, Capitán. La forma más rápida es asaltar barcos mercantes y dedicarse al contrabando. También podrías optar por el comercio honesto, pero llevará un poco más de tiempo. Sin embargo, no tienes que limitarte: acepta cualquier trabajo y métete en todos los líos que puedas encontrar. Así es como te harás rico. Informaré a la tripulación, Capitán. ¡Que la fortuna nos favorezca a todos!";
		link.l1 = "Empezar juego";
		link.l1.go = "Finish_3";
		break;

	case "Finish_2_2":
		pchar.questTemp.SanBoxTarget = 2;
		dialog.text = "¿Pero sabes cómo terminó l'Olonnais? Bueno, no te juzgaré, Capitán. Derramar sangre inocente puede ser lucrativo, pero prepárate para las consecuencias. Necesitarás un barco formidable, quizás incluso un escuadrón, para conquistar el fuerte y establecer una base. Alternativamente, podrías tomar la ciudad por tierra, cuatrocientos hombres deberían ser suficientes, pero ten por seguro que una guarnición no suprimida te empujará de vuelta a la jungla rápidamente. Transmitiré tu decisión a la tripulación, Capitán. ¡Que la fortuna nos favorezca a todos!";
		link.l1 = "Empezar juego";
		link.l1.go = "Finish_3";
		break;

	case "Finish_2_3":
		pchar.questTemp.SanBoxTarget = 3;
		dialog.text = "¡Tenemos abundancia de ambos, capitán! Visite las ciudades, mezcle con los lugareños, y las aventuras lo buscarán. Solo recuerde que la gente seria solo buscará su ayuda una vez que haya demostrado su valía y construido una reputación. A la tripulación le gustará eso. ¡Que la fortuna nos favorezca a todos!";
		link.l1 = "Empezar juego";
		link.l1.go = "Finish_3";
		break;

	case "Finish_2_4":
		pchar.questTemp.SanBoxTarget = 4;
		dialog.text = "No hay mucho romanticismo en ese oficio, Capitán. Es una búsqueda larga pero rentable, especialmente si la suerte está de tu lado. Busca mapas del tesoro en los vendedores de la taberna y mantén los ojos abiertos: te encontrarás con muchos cazadores rivales que quieren enriquecerse a tu costa. Además, los tesoros más valiosos a menudo requieren ensamblar la mitad de un mapa a partir de hallazgos más simples, ¡así que adelante! ¡Que la fortuna nos favorezca a todos!";
		link.l1 = "Comenzar juego";
		link.l1.go = "Finish_3";
		break;

	case "Finish_2_5":
		pchar.questTemp.SanBoxTarget = 5;
		dialog.text = "Entonces entiendes lo que se necesita para convertirse en una leyenda del Caribe, Capitán. La tripulación cree en ti y espera con ansias tus logros. ¡Que la fortuna nos favorezca a todos!";
		link.l1 = "Comenzar juego";
		link.l1.go = "Finish_3";
		break;

	case "Finish_3":
		DoQuestFunctionDelay("Tut_locCamera_2", 0.1);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_RemoveCheckMinHP(Pchar); // снимем проверки
		LAi_SetImmortal(pchar, false);
		LAi_SetPlayerType(pchar);
		InterfaceStates.Buttons.Save.enable = true;
		DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		SetFunctionTimerCondition("SanBoxStatusCityRemove", 0, 0, 30, false);
		bGameMenuStart = false;
		//AddQuestRecordInfo("Guide_AtSea", "1");
		//AddQuestRecordInfo("Guide_OnLand", "1");
		DoQuestFunctionDelay("Tutorial_CameraControlFP", 2.5);
		// DoQuestFunctionDelay("Tutorial_Rest", 2.5);
		break;

	case "ChangePIRATES":
		LAi_SetCitizenTypeNoGroup(NPChar);
		LAi_SetPlayerType(pchar);
		NextDiag.CurrentNode = "Node_5";
		DialogExit();
		pchar.SystemInfo.ChangePIRATES = true;
		LaunchCharacter(pchar);
		break;

	case "ChangePIRATES_Jess":
		LAi_SetCitizenTypeNoGroup(NPChar);
		LAi_SetPlayerType(pchar);
		NextDiag.CurrentNode = "Node_5_Jess";
		DialogExit();
		pchar.SystemInfo.ChangePIRATES = true;
		LaunchCharacter(pchar);
		break;

	case "Teach_battle_1":
		LAi_SetPlayerType(pchar);
		NextDiag.CurrentNode = "Teach_6";
		AddDialogExitQuestFunction("Tut_TeachBattle");
		DialogExit();
		break;

	case "First time":
		NextDiag.TempNode = "First time";
		EndQuestMovie();
		InterfaceStates.Buttons.Save.enable = false;
		LAi_LockFightMode(Pchar, false);
		LAi_SetActorTypeNoGroup(Pchar);
		LAi_ActorTurnToCharacter(Pchar, NPChar);
		if (pchar.name == "Jessica")
		{
			dialog.text = "¡Has regresado, capitán, por fin! Gracias a Dios, casi habíamos perdido toda esperanza.";
			if (bBettaTestMode)
			{
				link.l0 = "BetaTest - omitir y comenzar el juego";
				link.l0.go = "Finish_2";
			}
			link.l1 = "¿Alonso? ¿Qué demonios ha pasado? ¿Y por qué tengo un dolor de cabeza tan terrible?";
			link.l1.go = "Node_1_Jess";
		}
		else
		{
			dialog.text = "Bueno, capitán, ahora te ves como tú mismo. ¿Cómo te sientes?";
			// link.l2 = "BetaTest - Comenzar la prueba de la misión de Longway";
			// link.l2.go = "PZ_Test_Start_1";
			if (bBettaTestMode)
			{
				link.l0 = "BetaTest - omitir y comenzar el juego";
				link.l0.go = "Finish_2";
			}
			link.l1 = "Mm... ¿y cómo era yo antes?";
			link.l1.go = "Node_1";
		}
		locCameraFromToPos(-2.04, 4.95, 13.26, true, -0.82, 2.52, 7.87);
		break;

	case "PZ_Test_Start_1":
		dialog.text = "¿Dónde empezamos?";
		link.l0 = "Episodio 0. PRÓLOGO. (desde el principio)";
		link.l0.go = "PZ_Test_Start_S_samogo_nachala";
		link.l1 = "Episodio 1. FIEL AL JURAMENTO.";
		link.l1.go = "PZ_Test_Start_BasTer";
		link.l2 = "Episodio 2-3. СТРАНИЦЫ ИСТОРИИ.";
		link.l2.go = "PZ_Test_Start_Formosa";
		link.l4 = "Episodio 4. ESTRELLA ENGAÑOSA.";
		link.l4.go = "PZ_Test_Start_Etap4";
		link.l51 = "Episodio 5-6. ESTRELLA FUGAZ. (CON Helen)";
		link.l51.go = "PZ_Test_Start_Etap5_Helena";
		link.l52 = "Episodio 5-6. ESTRELLA FUGAZ. (CON Mary)";
		link.l52.go = "PZ_Test_Start_Etap5_Mary";
		break;

	case "PZ_Test_Start_Etap5_Helena":
		DialogExit();
		LAi_SetPlayerType(pchar);
		InterfaceStates.Buttons.Save.enable = true;
		bGameMenuStart = false;
		RemoveAllCharacterItems(pchar, true);
		AddMoneyToCharacter(pchar, 10000000);
		pchar.rank = 35;
		LAi_SetHP(pchar, 400.0, 400.0);
		SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
		SetSelfSkill(PChar, 50, 50, 50, 50, 50);
		SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
		LAi_SetHP(pchar, 400.0, 400.0);
		SetCharacterPerk(pchar, "BasicDefense");
		SetCharacterPerk(pchar, "AdvancedDefense");
		SetCharacterPerk(pchar, "Ciras");
		SetCharacterPerk(pchar, "SwordplayProfessional");
		SetCharacterPerk(pchar, "CriticalHit");
		SetCharacterPerk(pchar, "AgileMan");
		SetCharacterPerk(pchar, "BladeDancer");
		SetCharacterPerk(pchar, "Sliding");
		SetCharacterPerk(pchar, "HardHitter");
		SetCharacterPerk(pchar, "EnergyPlus");
		SetCharacterPerk(pchar, "Medic");
		SetCharacterPerk(pchar, "Gunman");
		SetCharacterPerk(pchar, "GunProfessional");
		SetCharacterPerk(pchar, "Tireless");
		SetCharacterPerk(pchar, "IronWill");
		SetCharacterPerk(pchar, "CrewDamageUp");
		SetCharacterPerk(pchar, "CriticalShoot");
		SetCharacterPerk(pchar, "LongRangeShoot");
		SetCharacterPerk(pchar, "CannonProfessional");
		SetCharacterPerk(pchar, "LongRangeGrappling");
		SetCharacterPerk(pchar, "MusketsShoot");
		SetCharacterPerk(pchar, "GrapplingProfessional");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "ShipSpeedUp");
		SetCharacterPerk(pchar, "ShipTurnRateUp");
		SetCharacterPerk(pchar, "BasicBattleState");
		SetCharacterPerk(pchar, "AdvancedBattleState");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "StormProfessional");
		SetCharacterPerk(pchar, "SailingProfessional");
		SetCharacterPerk(pchar, "SailsMan");
		SetCharacterPerk(pchar, "WindCatcher");
		SetCharacterPerk(pchar, "SeaDogProfessional");
		SetCharacterPerk(pchar, "Trustworthy");
		GiveItem2Character(PChar, "blade_16");
		GiveItem2Character(PChar, "blade_13");
		EquipCharacterByItem(Pchar, "blade_13");
		GiveItem2Character(PChar, "pistol5");
		EquipCharacterByItem(Pchar, "pistol5");
		GiveItem2Character(PChar, "cirass8");
		EquipCharacterByItem(Pchar, "cirass8");
		GiveItem2Character(PChar, "spyglass4");
		EquipCharacterByItem(Pchar, "spyglass4");
		GiveItem2Character(PChar, "talisman2");
		EquipCharacterByItem(Pchar, "talisman2");
		GiveItem2Character(PChar, "talisman13");
		AddItems(Pchar, "cartridge", 50);
		AddItems(Pchar, "potion4", 20);
		LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
		AddItems(pchar, "gold_dublon", 500);
		// Мой корабль
		pchar.Ship.Type = GenerateShipExt(SHIP_LINESHIP, true, pchar);
		pchar.Ship.name = "Aventura";
		SetSailsColor(pchar, 0); // белый хлопковый парус
		SetBaseShipData(pchar);
		pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
		SetCrewQuantityFull(pchar);
		pchar.Ship.Crew.Morale = 100;
		pchar.Ship.Crew.Exp.Sailors = 100;
		pchar.Ship.Crew.Exp.Cannoners = 100;
		pchar.Ship.Crew.Exp.Soldiers = 100;
		UpgradeShipParameter(pchar, "SpeedRate"); // апгрейдить скорость
		UpgradeShipParameter(pchar, "TurnRate");  // маневренность
		UpgradeShipParameter(pchar, "HP");		  // корпус
		ChangeCrewExp(pchar, "Sailors", 100);
		ChangeCrewExp(pchar, "Cannoners", 100);
		ChangeCrewExp(pchar, "Soldiers", 100);
		SetCharacterGoods(pchar, GOOD_BALLS, 2000);
		SetCharacterGoods(pchar, GOOD_GRAPES, 700);
		SetCharacterGoods(pchar, GOOD_KNIPPELS, 600);
		SetCharacterGoods(pchar, GOOD_BOMBS, 2000);
		SetCharacterGoods(pchar, GOOD_FOOD, 2000);
		SetCharacterGoods(pchar, GOOD_POWDER, 5000);
		SetCharacterGoods(pchar, GOOD_WEAPON, 750);
		SetCharacterGoods(pchar, GOOD_MEDICAMENT, 900);
		SetCharacterGoods(pchar, GOOD_RUM, 800);
		setCharacterShipLocation(pchar, "Pirates_town");
		setWDMPointXZ("Pirates_town");
		// Longway
		sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
		sld.name = "Longway";
		sld.lastname = "";
		sld.greeting = "Longway";
		sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
		sld.dialog.currentnode = "Longway_officer";
		sld.CompanionDisable = true;
		sld.rank = 20;
		sld.money = 5000;
		SetSelfSkill(sld, 45, 45, 45, 40, 50);
		SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
		SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
		LAi_SetHP(sld, 250, 250);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "StormProfessional");
		SetCharacterPerk(sld, "WindCatcher");
		SetCharacterPerk(sld, "SailsMan");
		SetCharacterPerk(sld, "SailingProfessional");
		GiveItem2Character(sld, "blade_08");
		sld.equip.blade = "blade_08";
		GiveItem2Character(sld, "pistol3");
		EquipCharacterbyItem(sld, "pistol3");
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
		TakeNItems(sld, "grapeshot", 50);
		AddItems(sld, "gunpowder", 50);
		TakeNItems(sld, "potion2", 1);
		//
		sld.quest.OfficerPrice = sti(pchar.rank) * 200;
		sld.OfficerWantToGo.DontGo = true;
		sld.loyality = MAX_LOYALITY;
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		SetCharacterPerk(sld, "ShipEscape");
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.greeting = "Longway";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		// Tichingitu
		sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
		sld.name = "Tichingitu";
		sld.lastname = "";
		sld.greeting = "Tichingitu";
		sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
		sld.dialog.currentnode = "Tichingitu";
		sld.rank = 20;
		LAi_SetHP(sld, 200.0, 200.0);
		SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
		SetSelfSkill(sld, 50, 50, 50, 70, 50);
		SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		AddItems(sld, "mushket1", 1);
		sld.CanTakeMushket = true;
		GiveItem2Character(sld, "blade_10");
		sld.equip.blade = "blade_10";
		GiveItem2Character(sld, "pistol1");
		sld.equip.gun = "pistol1";
		GiveItem2Character(sld, "cirass1");
		EquipCharacterbyItem(sld, "cirass1");
		AddItems(sld, "cartridge", 50);
		sld.quest.OfficerPrice = sti(pchar.rank) * 20;
		sld.OfficerWantToGo.DontGo = true;
		sld.CompanionDisable = true;
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.dialog.currentnode = "Tichingitu_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		AddItems(sld, "potion2", 10);
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		SetCharacterPerk(sld, "ShipEscape");
		// Элен:
		pchar.questTemp.Saga.Helena_officer = "true";
		sld = characterFromId("Helena");
		sld.greeting = "helena_hire";
		sld.quest.OfficerPrice = sti(pchar.rank) * 500;
		sld.OfficerWantToGo.DontGo = true; // не пытаться уйти
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		sld.DontClearDead = true;
		sld.dialog.currentnode = "Helena_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		sld.rank = 35;
		LAi_SetHP(sld, 500.0, 500.0);
		SetSelfSkill(sld, 100, 90, 100, 100, 90);
		SetShipSkill(sld, 100, 40, 40, 40, 40, 40, 40, 40, 40);
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "ByWorker");
		SetCharacterPerk(sld, "ByWorker2");
		SetCharacterPerk(sld, "Grus");
		GiveItem2Character(sld, "pirate_cutlass");
		sld.equip.blade = "pirate_cutlass";
		GiveItem2Character(sld, "pistol4");
		sld.equip.gun = "pistol4";
		GiveItem2Character(sld, "cirass4");
		EquipCharacterbyItem(sld, "cirass4");
		AddItems(sld, "cartridge", 50);
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
		AddItems(sld, "potion2", 10);
		AddItems(sld, "potion4", 5);
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		LAi_SetImmortal(sld, false);
		// Baсker
		sld = GetCharacter(NPC_GenerateCharacter("Baker", "Baker", "man", "man_B", 1, ENGLAND, -1, false, "quest"));
		sld.name = "Raymond";
		sld.lastname = "Backer";
		sld.greeting = "baker";
		sld.Dialog.Filename = "Quest\Saga\Baker.c";
		sld.dialog.currentnode = "Baker_officer";
		sld.rank = 28;
		LAi_SetHP(sld, 150, 150);
		SetSelfSkill(sld, 20, 20, 70, 20, 40);
		SetShipSkill(sld, 20, 40, 10, 10, 15, 5, 8, 95, 50);
		SetSPECIAL(sld, 6, 6, 7, 6, 9, 6, 5);
		SetCharacterPerk(sld, "Doctor1");
		SetCharacterPerk(sld, "Doctor2");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "BasicCommerce");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Gunman");
		GiveItem2Character(sld, "blade_11");
		sld.equip.blade = "blade_11";
		GiveItem2Character(sld, "pistol1");
		EquipCharacterbyItem(sld, "pistol1");
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
		TakeNItems(sld, "bullet", 20);
		AddItems(sld, "gunpowder", 20);
		sld.quest.OfficerPrice = sti(pchar.rank) * 500;
		sld.OfficerWantToGo.DontGo = true; // не пытаться уйти
		sld.CompanionDisable = true;	   // нельзя в компаньоны
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		sld.DontClearDead = true;
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");

		// Телепорт
		DoQuestReloadToLocation("Pirates_town", "reload", "reload1", "PZ_Etap5_Start");
		// выключить сторонние квесты
		PChar.quest.Red_Chieftain.over = "yes";
		PChar.quest.False_Trace.over = "yes";
		PChar.quest.FalseTrace_Prepare.over = "yes";
		// Остальное
		sld = characterFromID("Charles_Priest");
		sld.name = "Georges";
		sld.lastname = "Gravel";
		break;

	case "PZ_Test_Start_Etap5_Mary":
		DialogExit();
		LAi_SetPlayerType(pchar);
		InterfaceStates.Buttons.Save.enable = true;
		bGameMenuStart = false;
		RemoveAllCharacterItems(pchar, true);
		AddMoneyToCharacter(pchar, 10000000);
		pchar.rank = 35;
		LAi_SetHP(pchar, 400.0, 400.0);
		SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
		SetSelfSkill(PChar, 50, 50, 50, 50, 50);
		SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
		LAi_SetHP(pchar, 400.0, 400.0);
		SetCharacterPerk(pchar, "BasicDefense");
		SetCharacterPerk(pchar, "AdvancedDefense");
		SetCharacterPerk(pchar, "Ciras");
		SetCharacterPerk(pchar, "SwordplayProfessional");
		SetCharacterPerk(pchar, "CriticalHit");
		SetCharacterPerk(pchar, "AgileMan");
		SetCharacterPerk(pchar, "BladeDancer");
		SetCharacterPerk(pchar, "Sliding");
		SetCharacterPerk(pchar, "HardHitter");
		SetCharacterPerk(pchar, "EnergyPlus");
		SetCharacterPerk(pchar, "Medic");
		SetCharacterPerk(pchar, "Gunman");
		SetCharacterPerk(pchar, "GunProfessional");
		SetCharacterPerk(pchar, "Tireless");
		SetCharacterPerk(pchar, "IronWill");
		SetCharacterPerk(pchar, "CrewDamageUp");
		SetCharacterPerk(pchar, "CriticalShoot");
		SetCharacterPerk(pchar, "LongRangeShoot");
		SetCharacterPerk(pchar, "CannonProfessional");
		SetCharacterPerk(pchar, "LongRangeGrappling");
		SetCharacterPerk(pchar, "MusketsShoot");
		SetCharacterPerk(pchar, "GrapplingProfessional");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "ShipSpeedUp");
		SetCharacterPerk(pchar, "ShipTurnRateUp");
		SetCharacterPerk(pchar, "BasicBattleState");
		SetCharacterPerk(pchar, "AdvancedBattleState");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "StormProfessional");
		SetCharacterPerk(pchar, "SailingProfessional");
		SetCharacterPerk(pchar, "SailsMan");
		SetCharacterPerk(pchar, "WindCatcher");
		SetCharacterPerk(pchar, "SeaDogProfessional");
		SetCharacterPerk(pchar, "Trustworthy");
		GiveItem2Character(PChar, "blade_16");
		GiveItem2Character(PChar, "blade_13");
		EquipCharacterByItem(Pchar, "blade_13");
		GiveItem2Character(PChar, "pistol5");
		EquipCharacterByItem(Pchar, "pistol5");
		GiveItem2Character(PChar, "cirass8");
		EquipCharacterByItem(Pchar, "cirass8");
		GiveItem2Character(PChar, "spyglass4");
		EquipCharacterByItem(Pchar, "spyglass4");
		GiveItem2Character(PChar, "talisman2");
		EquipCharacterByItem(Pchar, "talisman2");
		GiveItem2Character(PChar, "talisman13");
		AddItems(Pchar, "cartridge", 50);
		AddItems(Pchar, "potion4", 20);
		LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
		AddItems(pchar, "gold_dublon", 500);
		// Мой корабль
		pchar.Ship.Type = GenerateShipExt(SHIP_LINESHIP, true, pchar);
		pchar.Ship.name = "Aventura";
		SetSailsColor(pchar, 0); // белый хлопковый парус
		SetBaseShipData(pchar);
		pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
		SetCrewQuantityFull(pchar);
		pchar.Ship.Crew.Morale = 100;
		pchar.Ship.Crew.Exp.Sailors = 100;
		pchar.Ship.Crew.Exp.Cannoners = 100;
		pchar.Ship.Crew.Exp.Soldiers = 100;
		UpgradeShipParameter(pchar, "SpeedRate"); // апгрейдить скорость
		UpgradeShipParameter(pchar, "TurnRate");  // маневренность
		UpgradeShipParameter(pchar, "HP");		  // корпус
		ChangeCrewExp(pchar, "Sailors", 100);
		ChangeCrewExp(pchar, "Cannoners", 100);
		ChangeCrewExp(pchar, "Soldiers", 100);
		SetCharacterGoods(pchar, GOOD_BALLS, 2000);
		SetCharacterGoods(pchar, GOOD_GRAPES, 700);
		SetCharacterGoods(pchar, GOOD_KNIPPELS, 600);
		SetCharacterGoods(pchar, GOOD_BOMBS, 2000);
		SetCharacterGoods(pchar, GOOD_FOOD, 2000);
		SetCharacterGoods(pchar, GOOD_POWDER, 5000);
		SetCharacterGoods(pchar, GOOD_WEAPON, 750);
		SetCharacterGoods(pchar, GOOD_MEDICAMENT, 900);
		SetCharacterGoods(pchar, GOOD_RUM, 800);
		setCharacterShipLocation(pchar, "Pirates_town");
		setWDMPointXZ("Pirates_town");
		// Longway
		sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
		sld.name = "Longway";
		sld.lastname = "";
		sld.greeting = "Longway";
		sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
		sld.dialog.currentnode = "Longway_officer";
		sld.CompanionDisable = true;
		sld.rank = 20;
		sld.money = 5000;
		SetSelfSkill(sld, 45, 45, 45, 40, 50);
		SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
		SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
		LAi_SetHP(sld, 250, 250);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "StormProfessional");
		SetCharacterPerk(sld, "WindCatcher");
		SetCharacterPerk(sld, "SailsMan");
		SetCharacterPerk(sld, "SailingProfessional");
		GiveItem2Character(sld, "blade_08");
		sld.equip.blade = "blade_08";
		GiveItem2Character(sld, "pistol3");
		EquipCharacterbyItem(sld, "pistol3");
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
		TakeNItems(sld, "grapeshot", 50);
		AddItems(sld, "gunpowder", 50);
		TakeNItems(sld, "potion2", 1);
		//
		sld.quest.OfficerPrice = sti(pchar.rank) * 200;
		sld.OfficerWantToGo.DontGo = true;
		sld.loyality = MAX_LOYALITY;
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.greeting = "Longway";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		// Tichingitu
		sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
		sld.name = "Tichingitu";
		sld.lastname = "";
		sld.greeting = "Tichingitu";
		sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
		sld.dialog.currentnode = "Tichingitu";
		sld.rank = 20;
		LAi_SetHP(sld, 200.0, 200.0);
		SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
		SetSelfSkill(sld, 50, 50, 50, 70, 50);
		SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		AddItems(sld, "mushket1", 1);
		sld.CanTakeMushket = true;
		GiveItem2Character(sld, "blade_10");
		sld.equip.blade = "blade_10";
		GiveItem2Character(sld, "pistol1");
		sld.equip.gun = "pistol1";
		GiveItem2Character(sld, "cirass1");
		EquipCharacterbyItem(sld, "cirass1");
		AddItems(sld, "cartridge", 50);
		sld.quest.OfficerPrice = sti(pchar.rank) * 20;
		sld.OfficerWantToGo.DontGo = true;
		sld.CompanionDisable = true;
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.dialog.currentnode = "Tichingitu_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		AddItems(sld, "potion2", 10);
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		// Мэри:
		pchar.questTemp.LSC.Mary_officer = "true";
		sld = characterFromId("Mary");
		sld.quest.OfficerPrice = sti(pchar.rank) * 500;
		sld.OfficerWantToGo.DontGo = true; // не пытаться уйти
		sld.CompanionDisable = true;	   // нельзя в компаньоны
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		sld.DontClearDead = true;
		sld.dialog.currentnode = "Mary_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		sld.rank = 35;
		LAi_SetHP(sld, 500.0, 500.0);
		SetSelfSkill(sld, 100, 90, 100, 100, 90);
		SetShipSkill(sld, 100, 40, 40, 40, 40, 40, 40, 40, 40);
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "ByWorker");
		SetCharacterPerk(sld, "ByWorker2");
		SetCharacterPerk(sld, "Grus");
		GiveItem2Character(sld, "blade_31");
		sld.equip.blade = "blade_31";
		GiveItem2Character(sld, "pistol4");
		sld.equip.gun = "pistol4";
		GiveItem2Character(sld, "cirass4");
		EquipCharacterbyItem(sld, "cirass4");
		AddItems(sld, "cartridge", 50);
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
		AddItems(sld, "potion2", 10);
		AddItems(sld, "potion4", 5);
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		// Baсker
		sld = GetCharacter(NPC_GenerateCharacter("Baker", "Baker", "man", "man_B", 1, ENGLAND, -1, false, "quest"));
		sld.name = "Raymond";
		sld.lastname = "Backer";
		sld.greeting = "baker";
		sld.Dialog.Filename = "Quest\Saga\Baker.c";
		sld.dialog.currentnode = "Baker_officer";
		sld.rank = 28;
		LAi_SetHP(sld, 150, 150);
		SetSelfSkill(sld, 20, 20, 70, 20, 40);
		SetShipSkill(sld, 20, 40, 10, 10, 15, 5, 8, 95, 50);
		SetSPECIAL(sld, 6, 6, 7, 6, 9, 6, 5);
		SetCharacterPerk(sld, "Doctor1");
		SetCharacterPerk(sld, "Doctor2");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "BasicCommerce");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Gunman");
		GiveItem2Character(sld, "blade_11");
		sld.equip.blade = "blade_11";
		GiveItem2Character(sld, "pistol1");
		EquipCharacterbyItem(sld, "pistol1");
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
		TakeNItems(sld, "bullet", 20);
		AddItems(sld, "gunpowder", 20);
		sld.quest.OfficerPrice = sti(pchar.rank) * 500;
		sld.OfficerWantToGo.DontGo = true; // не пытаться уйти
		sld.CompanionDisable = true;	   // нельзя в компаньоны
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		sld.DontClearDead = true;
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");

		// Телепорт
		DoQuestReloadToLocation("Pirates_town", "reload", "reload1", "PZ_Etap5_Start");
		// выключить сторонние квесты
		PChar.quest.Red_Chieftain.over = "yes";
		PChar.quest.False_Trace.over = "yes";
		PChar.quest.FalseTrace_Prepare.over = "yes";
		// Остальное
		sld = characterFromID("Charles_Priest");
		sld.name = "Georges";
		sld.lastname = "Gravel";
		break;

	case "PZ_Test_Start_Etap4":
		DialogExit();
		LAi_SetPlayerType(pchar);
		InterfaceStates.Buttons.Save.enable = true;
		bGameMenuStart = false;
		locations[FindLocation("Shore9")].DisableEncounters = true;
		RemoveAllCharacterItems(pchar, true);
		AddMoneyToCharacter(pchar, 10000000);
		pchar.rank = 25;
		SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
		SetSelfSkill(PChar, 50, 50, 50, 50, 50);
		SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
		SetCharacterPerk(pchar, "BasicDefense");
		SetCharacterPerk(pchar, "AdvancedDefense");
		SetCharacterPerk(pchar, "Ciras");
		SetCharacterPerk(pchar, "SwordplayProfessional");
		SetCharacterPerk(pchar, "CriticalHit");
		SetCharacterPerk(pchar, "AgileMan");
		SetCharacterPerk(pchar, "BladeDancer");
		SetCharacterPerk(pchar, "Sliding");
		SetCharacterPerk(pchar, "HardHitter");
		SetCharacterPerk(pchar, "EnergyPlus");
		SetCharacterPerk(pchar, "Medic");
		SetCharacterPerk(pchar, "Gunman");
		SetCharacterPerk(pchar, "GunProfessional");
		SetCharacterPerk(pchar, "Tireless");
		SetCharacterPerk(pchar, "IronWill");
		SetCharacterPerk(pchar, "CrewDamageUp");
		SetCharacterPerk(pchar, "CriticalShoot");
		SetCharacterPerk(pchar, "LongRangeShoot");
		SetCharacterPerk(pchar, "CannonProfessional");
		SetCharacterPerk(pchar, "LongRangeGrappling");
		SetCharacterPerk(pchar, "MusketsShoot");
		SetCharacterPerk(pchar, "GrapplingProfessional");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "ShipSpeedUp");
		SetCharacterPerk(pchar, "ShipTurnRateUp");
		SetCharacterPerk(pchar, "BasicBattleState");
		SetCharacterPerk(pchar, "AdvancedBattleState");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "StormProfessional");
		SetCharacterPerk(pchar, "SailingProfessional");
		SetCharacterPerk(pchar, "SailsMan");
		SetCharacterPerk(pchar, "WindCatcher");
		SetCharacterPerk(pchar, "SeaDogProfessional");
		SetCharacterPerk(pchar, "Trustworthy");
		GiveItem2Character(PChar, "blade_16");
		GiveItem2Character(PChar, "blade_13");
		EquipCharacterByItem(Pchar, "blade_13");
		GiveItem2Character(PChar, "pistol5");
		EquipCharacterByItem(Pchar, "pistol5");
		GiveItem2Character(PChar, "cirass8");
		EquipCharacterByItem(Pchar, "cirass8");
		GiveItem2Character(PChar, "spyglass4");
		EquipCharacterByItem(Pchar, "spyglass4");
		GiveItem2Character(PChar, "talisman2");
		EquipCharacterByItem(Pchar, "talisman2");
		GiveItem2Character(PChar, "talisman13");
		AddItems(Pchar, "cartridge", 50);
		AddItems(Pchar, "potion4", 20);
		LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
		AddItems(pchar, "gold_dublon", 500);
		// Мой корабль
		pchar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, pchar);
		pchar.Ship.name = "MAYFANG";
		SetBaseShipData(pchar);
		pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
		SetCrewQuantity(pchar, 170);
		pchar.ship.Crew.Morale = 100;
		ChangeCrewExp(pchar, "Sailors", 100);
		ChangeCrewExp(pchar, "Cannoners", 100);
		ChangeCrewExp(pchar, "Soldiers", 100);
		SetCharacterGoods(pchar, GOOD_BALLS, 300);
		SetCharacterGoods(pchar, GOOD_GRAPES, 800);
		SetCharacterGoods(pchar, GOOD_KNIPPELS, 800);
		SetCharacterGoods(pchar, GOOD_BOMBS, 300);
		SetCharacterGoods(pchar, GOOD_POWDER, 1500);
		SetCharacterGoods(pchar, GOOD_FOOD, 3000);
		SetCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
		SetCharacterGoods(pchar, GOOD_WEAPON, 500);
		SetCharacterGoods(pchar, GOOD_RUM, 500);
		setCharacterShipLocation(pchar, "Shore9");
		setWDMPointXZ("Shore9");
		// Longway
		sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
		sld.name = "Longway";
		sld.lastname = "";
		sld.greeting = "Longway";
		sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
		sld.dialog.currentnode = "Longway_officer";
		sld.CompanionDisable = true;
		sld.rank = 20;
		sld.money = 5000;
		SetSelfSkill(sld, 45, 45, 45, 40, 50);
		SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
		SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
		LAi_SetHP(sld, 250, 250);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "StormProfessional");
		SetCharacterPerk(sld, "WindCatcher");
		SetCharacterPerk(sld, "SailsMan");
		SetCharacterPerk(sld, "SailingProfessional");
		GiveItem2Character(sld, "blade_08");
		sld.equip.blade = "blade_08";
		GiveItem2Character(sld, "pistol3");
		EquipCharacterbyItem(sld, "pistol3");
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
		TakeNItems(sld, "grapeshot", 50);
		AddItems(sld, "gunpowder", 50);
		TakeNItems(sld, "potion2", 1);
		//
		sld.quest.OfficerPrice = sti(pchar.rank) * 200;
		sld.OfficerWantToGo.DontGo = true;
		sld.loyality = MAX_LOYALITY;
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.greeting = "Longway";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

		// Tichingitu
		sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
		sld.name = "Tichingitu";
		sld.lastname = "";
		sld.greeting = "Tichingitu";
		sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
		sld.dialog.currentnode = "Tichingitu";
		sld.rank = 20;
		LAi_SetHP(sld, 200.0, 200.0);
		SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
		SetSelfSkill(sld, 50, 50, 50, 70, 50);
		SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		AddItems(sld, "mushket1", 1);
		sld.CanTakeMushket = true;
		GiveItem2Character(sld, "blade_10");
		sld.equip.blade = "blade_10";
		GiveItem2Character(sld, "pistol1");
		sld.equip.gun = "pistol1";
		GiveItem2Character(sld, "cirass1");
		EquipCharacterbyItem(sld, "cirass1");
		AddItems(sld, "cartridge", 50);
		sld.quest.OfficerPrice = sti(pchar.rank) * 20;
		sld.OfficerWantToGo.DontGo = true;
		sld.CompanionDisable = true;
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.dialog.currentnode = "Tichingitu_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		AddItems(sld, "potion2", 10);
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		// Элен
		sld = characterFromId("Helena");
		GiveItem2Character(sld, "pirate_cutlass");
		EquipCharacterbyItem(sld, "pirate_cutlass");
		LAi_SetImmortal(sld, false);
		sld.quest.OfficerPrice = sti(pchar.rank) * 500;
		sld.OfficerWantToGo.DontGo = true; // не пытаться уйти
		DeleteAttribute(sld, "CompanionDisable");
		DeleteAttribute(sld, "HalfImmortal");
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		sld.CompanionDisable = true; // нельзя в компаньоны - чтобы не утонула
		sld.HalfImmortal = true;	 // чтобы не убили в сухопутном бою
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		sld.DontClearDead = true;
		sld.dialog.currentnode = "Helena_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		pchar.questTemp.Saga.Helena_friend = "true"; // друг

		// Телепорт
		DoQuestReloadToLocation("Shore9", "reload", "reload1", "PZ_Etap4_Start");
		// выключить сторонние квесты
		PChar.quest.Red_Chieftain.over = "yes";
		PChar.quest.False_Trace.over = "yes";
		PChar.quest.FalseTrace_Prepare.over = "yes";
		// Остальное
		sld = characterFromID("Charles_Priest");
		sld.name = "Georges";
		sld.lastname = "Gravel";
		break;

	case "PZ_Test_Start_S_samogo_nachala":
		DialogExit();
		LAi_SetPlayerType(pchar);
		InterfaceStates.Buttons.Save.enable = true;
		bGameMenuStart = false;
		RemoveAllCharacterItems(pchar, true);
		AddMoneyToCharacter(pchar, 10000000);
		pchar.rank = 25;
		SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
		SetSelfSkill(PChar, 50, 50, 50, 50, 50);
		SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
		SetCharacterPerk(pchar, "BasicDefense");
		SetCharacterPerk(pchar, "AdvancedDefense");
		SetCharacterPerk(pchar, "Ciras");
		SetCharacterPerk(pchar, "SwordplayProfessional");
		SetCharacterPerk(pchar, "CriticalHit");
		SetCharacterPerk(pchar, "AgileMan");
		SetCharacterPerk(pchar, "BladeDancer");
		SetCharacterPerk(pchar, "Sliding");
		SetCharacterPerk(pchar, "HardHitter");
		SetCharacterPerk(pchar, "EnergyPlus");
		SetCharacterPerk(pchar, "Medic");
		SetCharacterPerk(pchar, "Gunman");
		SetCharacterPerk(pchar, "GunProfessional");
		SetCharacterPerk(pchar, "Tireless");
		SetCharacterPerk(pchar, "IronWill");
		SetCharacterPerk(pchar, "CrewDamageUp");
		SetCharacterPerk(pchar, "CriticalShoot");
		SetCharacterPerk(pchar, "LongRangeShoot");
		SetCharacterPerk(pchar, "CannonProfessional");
		SetCharacterPerk(pchar, "LongRangeGrappling");
		SetCharacterPerk(pchar, "MusketsShoot");
		SetCharacterPerk(pchar, "GrapplingProfessional");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "ShipSpeedUp");
		SetCharacterPerk(pchar, "ShipTurnRateUp");
		SetCharacterPerk(pchar, "BasicBattleState");
		SetCharacterPerk(pchar, "AdvancedBattleState");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "StormProfessional");
		SetCharacterPerk(pchar, "SailingProfessional");
		SetCharacterPerk(pchar, "SailsMan");
		SetCharacterPerk(pchar, "WindCatcher");
		SetCharacterPerk(pchar, "SeaDogProfessional");
		SetCharacterPerk(pchar, "Trustworthy");
		GiveItem2Character(PChar, "blade_16");
		GiveItem2Character(PChar, "blade_13");
		EquipCharacterByItem(Pchar, "blade_13");
		GiveItem2Character(PChar, "pistol5");
		EquipCharacterByItem(Pchar, "pistol5");
		GiveItem2Character(PChar, "cirass8");
		EquipCharacterByItem(Pchar, "cirass8");
		GiveItem2Character(PChar, "spyglass4");
		EquipCharacterByItem(Pchar, "spyglass4");
		GiveItem2Character(PChar, "talisman2");
		EquipCharacterByItem(Pchar, "talisman2");
		GiveItem2Character(PChar, "talisman13");
		AddItems(Pchar, "cartridge", 50);
		AddItems(Pchar, "potion4", 20);
		LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
		AddItems(pchar, "gold_dublon", 500);
		// Мой корабль
		pchar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, pchar);
		pchar.Ship.name = "MAYFANG";
		SetBaseShipData(pchar);
		pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
		SetCrewQuantity(pchar, 170);
		pchar.ship.Crew.Morale = 100;
		ChangeCrewExp(pchar, "Sailors", 100);
		ChangeCrewExp(pchar, "Cannoners", 100);
		ChangeCrewExp(pchar, "Soldiers", 100);
		SetCharacterGoods(pchar, GOOD_BALLS, 300);
		SetCharacterGoods(pchar, GOOD_GRAPES, 800);
		SetCharacterGoods(pchar, GOOD_KNIPPELS, 800);
		SetCharacterGoods(pchar, GOOD_BOMBS, 300);
		SetCharacterGoods(pchar, GOOD_POWDER, 1500);
		SetCharacterGoods(pchar, GOOD_FOOD, 3000);
		SetCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
		SetCharacterGoods(pchar, GOOD_WEAPON, 500);
		SetCharacterGoods(pchar, GOOD_RUM, 500);
		setCharacterShipLocation(pchar, "SentJons_town");
		setWDMPointXZ("SentJons_town");
		// Longway
		sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
		sld.name = "Longway";
		sld.lastname = "";
		sld.greeting = "Longway";
		sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
		sld.dialog.currentnode = "Longway_officer";
		sld.CompanionDisable = true;
		sld.rank = 20;
		sld.money = 5000;
		SetSelfSkill(sld, 45, 45, 45, 40, 50);
		SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
		SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
		LAi_SetHP(sld, 250, 250);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "StormProfessional");
		SetCharacterPerk(sld, "WindCatcher");
		SetCharacterPerk(sld, "SailsMan");
		SetCharacterPerk(sld, "SailingProfessional");
		GiveItem2Character(sld, "blade_08");
		sld.equip.blade = "blade_08";
		GiveItem2Character(sld, "pistol3");
		EquipCharacterbyItem(sld, "pistol3");
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
		TakeNItems(sld, "grapeshot", 50);
		AddItems(sld, "gunpowder", 50);
		TakeNItems(sld, "potion2", 1);
		//
		sld.quest.OfficerPrice = sti(pchar.rank) * 200;
		sld.OfficerWantToGo.DontGo = true;
		sld.loyality = MAX_LOYALITY;
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.greeting = "Longway";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

		// Tichingitu
		sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
		sld.name = "Tichingitu";
		sld.lastname = "";
		sld.greeting = "Tichingitu";
		sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
		sld.dialog.currentnode = "Tichingitu";
		sld.rank = 20;
		LAi_SetHP(sld, 200.0, 200.0);
		SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
		SetSelfSkill(sld, 50, 50, 50, 70, 50);
		SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		AddItems(sld, "mushket1", 1);
		sld.CanTakeMushket = true;
		GiveItem2Character(sld, "blade_10");
		sld.equip.blade = "blade_10";
		GiveItem2Character(sld, "pistol1");
		sld.equip.gun = "pistol1";
		GiveItem2Character(sld, "cirass1");
		EquipCharacterbyItem(sld, "cirass1");
		AddItems(sld, "cartridge", 50);
		sld.quest.OfficerPrice = sti(pchar.rank) * 20;
		sld.OfficerWantToGo.DontGo = true;
		sld.CompanionDisable = true;
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.dialog.currentnode = "Tichingitu_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		AddItems(sld, "potion2", 10);
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;

		// Телепорт
		DoQuestReloadToLocation("SentJons_town", "reload", "reload1", "PZ_BETA_Test_Start_S_samogo_nachala_2");
		// выключить сторонние квесты
		PChar.quest.Red_Chieftain.over = "yes";
		PChar.quest.False_Trace.over = "yes";
		PChar.quest.FalseTrace_Prepare.over = "yes";
		// Остальное
		SetQuestHeader("Holl_Gambit");
		AddQuestRecord("Holl_Gambit", "1-1");
		AddQuestRecord("Holl_Gambit", "1-3");
		AddQuestRecord("Holl_Gambit", "1-6");
		break;

	case "PZ_Test_Start_BasTer":
		DialogExit();
		LAi_SetPlayerType(pchar);
		InterfaceStates.Buttons.Save.enable = true;
		bGameMenuStart = false;
		RemoveAllCharacterItems(pchar, true);
		AddMoneyToCharacter(pchar, 10000000);
		pchar.rank = 25;
		SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
		SetSelfSkill(PChar, 50, 50, 50, 50, 50);
		SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
		SetCharacterPerk(pchar, "BasicDefense");
		SetCharacterPerk(pchar, "AdvancedDefense");
		SetCharacterPerk(pchar, "Ciras");
		SetCharacterPerk(pchar, "SwordplayProfessional");
		SetCharacterPerk(pchar, "CriticalHit");
		SetCharacterPerk(pchar, "AgileMan");
		SetCharacterPerk(pchar, "BladeDancer");
		SetCharacterPerk(pchar, "Sliding");
		SetCharacterPerk(pchar, "HardHitter");
		SetCharacterPerk(pchar, "EnergyPlus");
		SetCharacterPerk(pchar, "Medic");
		SetCharacterPerk(pchar, "Gunman");
		SetCharacterPerk(pchar, "GunProfessional");
		SetCharacterPerk(pchar, "Tireless");
		SetCharacterPerk(pchar, "IronWill");
		SetCharacterPerk(pchar, "CrewDamageUp");
		SetCharacterPerk(pchar, "CriticalShoot");
		SetCharacterPerk(pchar, "LongRangeShoot");
		SetCharacterPerk(pchar, "CannonProfessional");
		SetCharacterPerk(pchar, "LongRangeGrappling");
		SetCharacterPerk(pchar, "MusketsShoot");
		SetCharacterPerk(pchar, "GrapplingProfessional");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "ShipSpeedUp");
		SetCharacterPerk(pchar, "ShipTurnRateUp");
		SetCharacterPerk(pchar, "BasicBattleState");
		SetCharacterPerk(pchar, "AdvancedBattleState");
		SetCharacterPerk(pchar, "ShipDefenseProfessional");
		SetCharacterPerk(pchar, "StormProfessional");
		SetCharacterPerk(pchar, "SailingProfessional");
		SetCharacterPerk(pchar, "SailsMan");
		SetCharacterPerk(pchar, "WindCatcher");
		SetCharacterPerk(pchar, "SeaDogProfessional");
		SetCharacterPerk(pchar, "Trustworthy");
		GiveItem2Character(PChar, "blade_16");
		GiveItem2Character(PChar, "blade_13");
		EquipCharacterByItem(Pchar, "blade_13");
		GiveItem2Character(PChar, "pistol5");
		EquipCharacterByItem(Pchar, "pistol5");
		GiveItem2Character(PChar, "cirass8");
		EquipCharacterByItem(Pchar, "cirass8");
		GiveItem2Character(PChar, "spyglass4");
		EquipCharacterByItem(Pchar, "spyglass4");
		GiveItem2Character(PChar, "talisman2");
		EquipCharacterByItem(Pchar, "talisman2");
		GiveItem2Character(PChar, "talisman13");
		AddItems(Pchar, "cartridge", 50);
		AddItems(Pchar, "potion4", 20);
		LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
		AddItems(pchar, "gold_dublon", 500);
		// Мой корабль
		pchar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, pchar);
		pchar.Ship.name = "MAYFANG";
		SetBaseShipData(pchar);
		pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
		SetCrewQuantity(pchar, 170);
		pchar.ship.Crew.Morale = 100;
		ChangeCrewExp(pchar, "Sailors", 100);
		ChangeCrewExp(pchar, "Cannoners", 100);
		ChangeCrewExp(pchar, "Soldiers", 100);
		SetCharacterGoods(pchar, GOOD_BALLS, 300);
		SetCharacterGoods(pchar, GOOD_GRAPES, 800);
		SetCharacterGoods(pchar, GOOD_KNIPPELS, 800);
		SetCharacterGoods(pchar, GOOD_BOMBS, 300);
		SetCharacterGoods(pchar, GOOD_POWDER, 1500);
		SetCharacterGoods(pchar, GOOD_FOOD, 3000);
		SetCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
		SetCharacterGoods(pchar, GOOD_WEAPON, 500);
		SetCharacterGoods(pchar, GOOD_RUM, 500);
		setCharacterShipLocation(pchar, "Mayak4");
		setWDMPointXZ("Mayak4");
		// Longway
		sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
		sld.name = "Longway";
		sld.lastname = "";
		sld.greeting = "Longway";
		sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
		sld.dialog.currentnode = "Longway_officer";
		sld.CompanionDisable = true;
		sld.rank = 20;
		sld.money = 5000;
		SetSelfSkill(sld, 45, 45, 45, 40, 50);
		SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
		SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
		LAi_SetHP(sld, 250, 250);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "StormProfessional");
		SetCharacterPerk(sld, "WindCatcher");
		SetCharacterPerk(sld, "SailsMan");
		SetCharacterPerk(sld, "SailingProfessional");
		GiveItem2Character(sld, "blade_08");
		sld.equip.blade = "blade_08";
		GiveItem2Character(sld, "pistol3");
		EquipCharacterbyItem(sld, "pistol3");
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
		TakeNItems(sld, "grapeshot", 50);
		AddItems(sld, "gunpowder", 50);
		TakeNItems(sld, "potion2", 1);
		//
		sld.quest.OfficerPrice = sti(pchar.rank) * 200;
		sld.OfficerWantToGo.DontGo = true;
		sld.loyality = MAX_LOYALITY;
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;
		// AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.greeting = "Longway";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

		// Tichingitu
		sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
		sld.name = "Tichingitu";
		sld.lastname = "";
		sld.greeting = "Tichingitu";
		sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
		sld.dialog.currentnode = "Tichingitu";
		sld.rank = 20;
		LAi_SetHP(sld, 200.0, 200.0);
		SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
		SetSelfSkill(sld, 50, 50, 50, 70, 50);
		SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		AddItems(sld, "mushket1", 1);
		sld.CanTakeMushket = true;
		GiveItem2Character(sld, "blade_10");
		sld.equip.blade = "blade_10";
		GiveItem2Character(sld, "pistol1");
		sld.equip.gun = "pistol1";
		GiveItem2Character(sld, "cirass1");
		EquipCharacterbyItem(sld, "cirass1");
		AddItems(sld, "cartridge", 50);
		sld.quest.OfficerPrice = sti(pchar.rank) * 20;
		sld.OfficerWantToGo.DontGo = true;
		sld.CompanionDisable = true;
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		LAi_SetOfficerType(sld);
		sld.dialog.currentnode = "Tichingitu_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		AddItems(sld, "potion2", 10);
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0;
		sld.Health.maxHP = 60.0;

		// Телепорт
		DoQuestReloadToLocation("Mayak4", "goto", "goto2", "PZ_BETA_Test_Start_BasTer");
		// выключить сторонние квесты
		PChar.quest.Red_Chieftain.over = "yes";
		PChar.quest.False_Trace.over = "yes";
		PChar.quest.FalseTrace_Prepare.over = "yes";
		// Остальное
		break;

	case "PZ_Test_Start_Formosa":
		DialogExit();

		SetMainCharacterIndex(GetCharacterIndex("Longway"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		InterfaceStates.Buttons.Save.enable = true;
		bGameMenuStart = false;
		RemoveAllCharacterItems(pchar, true);
		// AddMoneyToCharacter(pchar, 10000000);
		GiveItem2Character(PChar, "blade_11");
		EquipCharacterByItem(Pchar, "blade_11");
		RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
		pchar.rank = 25;
		SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
		SetSelfSkill(PChar, 50, 50, 50, 50, 50);
		SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);

		// Телепорт
		DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		// выключить сторонние квесты
		PChar.quest.Red_Chieftain.over = "yes";
		PChar.quest.False_Trace.over = "yes";
		PChar.quest.FalseTrace_Prepare.over = "yes";
		break;

	case "Node_1":
		bGameMenuStart = false;
		StartBattleLandInterface();
		dialog.text = "Como esos ateos de piel roja, incluso hablabas en su idioma.";
		link.l1 = "¡Maldita sea! ¡Alonso, ¿de qué demonios estás hablando?!";
		link.l1.go = "Node_2";
		break;

	case "Node_1_Jess":
		dialog.text = "¿No recuerdas eso, verdad? Seguro, alguien más moriría de una contusión así o estaría sonriendo y ensuciándose los pantalones por el resto de su vida, pero parece que tú eres un hueso duro de roer. Aunque estás más débil y es un problema para ti incluso mantenerte en pie. Ha pasado casi medio año que hemos estado tratando de curarte.";
		link.l1 = "Dime sobre esa contusión, no recuerdo nada.";
		link.l1.go = "Node_2_Jess";
		break;

	case "Node_2":
		dialog.text = "No te preocupes, no debes preocuparte. Respira el aire fresco y mira al mar, entonces tu cabeza estará bien. El doctor dijo que no recordarás nada si te recuperas. Así que no intentes recordar, no lo necesitas.";
		link.l1 = "Tengo curiosidad por mi otra opción.";
		link.l1.go = "Node_3";
		break;

	case "Node_2_Jess":
		dialog.text = "La Máscara ...";
		link.l1 = "¡Maldita sea! La Máscara ha intentado matarme... No se puede confiar en nadie... ¿Y qué pasa con Lawrence? ¿Está vivo?";
		link.l1.go = "Node_3_Jess";
		break;

	case "Node_3":
		dialog.text = "La doctora dijo que sería un manicomio seguro. La personalidad dividida, dijo. Y Hopkins y yo no vimos ninguna otra personalidad aquí, excepto la tuya ...";
		link.l1 = "¡Tonterías! ¿Realmente me pasó a mí?";
		link.l1.go = "Node_4";
		break;

	case "Node_3_Jess":
		dialog.text = "No, gracias a Dios. Oh, lo siento... Fue ahorcado por orden de la Máscara. Y dicen que la Máscara fue cortada por Shark. Creo que todos se lo merecían, eran unos bastardos ambos. Estos canallas eran un gran problema para nosotros.";
		link.l1 = "No hables mal de los muertos... No podemos cambiar el pasado. Dios será su juez... Gracias, camaradas, por salvarme, no lo olvidaré.";
		link.l1.go = "Node_4_Jess";
		break;

	case "Node_4":
		dialog.text = "Te lo juro. Nosotros también estábamos asustados, no tendríamos idea de qué hacer en caso de que estuvieras muerto. ¡Y qué te dieron de beber esos mendigos culirrojos! Bueno, gracias a Dios, ahora estás bien. ¿Cómo te sientes?";
		// link.l1 = "Para beber, dices... parece familiar, no recuerdo nada... Déjame recoger mis pensamientos.";
		// link.l1.go  = "ChangePIRATES";
		link.l2 = "Me siento bien. Solo me siento mareado, es como estar borracho...";
		link.l2.go = "Node_5";
		break;

	case "Node_4_Jess":
		dialog.text = "...";
		// link.l1 = "Mm... dame un minuto, necesito ordenar mis pensamientos.";
		// link.l1.go  = "ChangePIRATES_Jess";
		link.l2 = "Me siento bien ahora. Gracias por tu preocupación, Alonso.";
		link.l2.go = "Node_5_Jess";
		break;

	case "Node_5":
		dialog.text = "El alcohol está prohibido para ti ahora. No queremos que tu personalidad dividida regrese. Sería bueno practicar un poco de esgrima. Apuesto a que has olvidado cómo manejar una hoja.";
		link.l1 = "Estás leyendo mi mente. Bueno, intentemos, me siento tan fuerte como un oso.";
		link.l1.go = "Teach_1";
		link.l2 = "No te preocupes, mis manos están mucho mejor comparadas con mi cabeza. Será mejor que vaya al puerto, me he descontrolado demasiado.";
		link.l2.go = "Finish_1";
		break;

	case "Node_5_Jess":
		dialog.text = "Ves, sabía que todo estaría bien... Pero una herida en la cabeza no es una broma, tomará tiempo recuperar tus habilidades. ¿No te gustaría practicar un poco de esgrima?";
		link.l1 = "Buena idea. Déjame probar mis habilidades.";
		link.l1.go = "Teach_1_Jess";
		link.l2 = "No, no quiero. Confío en mis habilidades.";
		link.l2.go = "Finish_1";
		break;

	case "Finish_1":
		if (pchar.name == "Jessica")
		{
			dialog.text = "Ahora estamos en el puerto " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId + "Gen") + "Necesitamos de alguna manera comenzar una nueva vida sin todas estas Máscaras y Beltropes, que se pudran todos en el infierno... Y no te defraudaremos, capitán. Nos quedaremos contigo hasta el final.";
			link.l1 = "¡Pues, supongo que tengo suerte de estar vivo! No os defraudaré ni decepcionaré a ninguno de vosotros. Eso sería todo, necesito desembarcar.";
			link.l1.go = "Finish_2";
			link.l2 = "Un bastardo menos, un bastardo más, es lo que es, Alonso. ¿Me darás un par de consejos antes de que desembarque?";
			link.l2.go = "Advice_1";
		}
		else
		{
			dialog.text = "Ahora estamos en el puerto del asentamiento " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId + "Gen") + ", ponte cómodo, pero vuelve. Ya perdimos el verdadero negocio, tuvimos que vender el viejo barco, pero no sacarás mucho con esto. Así que, fuimos interrumpidos por la anticipación de tu recuperación. Y los muchachos todavía creen en ti, de lo contrario ya habrían huido hace mucho tiempo...";
			link.l1 = "Espléndido. Bien, voy a tierra... No te preocupes, no me perderé.";
			link.l1.go = "Finish_2";
			link.l2 = "¿Si crees que no estoy listo?";
			link.l2.go = "Advice_1";
		}
		break;

	case "Advice_1":
		dialog.text = "Bueno, capitán... Necesitamos reparar el barco, contratar más hombres y comprar suministros. ¡Y busquemos algunas aventuras! Por supuesto, sería bueno obtener una carta de corso en caso de que vayamos a asaltar los mares. Nos otorgará todos los derechos para hacerlo y podremos decir a nuestras familias que nuestro trabajo es completamente legal. Y tú podrás hacerte un nombre...";
		link.l1 = "¿Qué más debo saber?";
		link.l1.go = "Advice_2";
		link.l2 = "Espléndido. Bien, voy a tierra...";
		link.l2.go = "Finish_2";
		break;

	case "Advice_2":
		dialog.text = "Tienes que conocer los precios actuales de las mercancías en las tiendas del archipiélago para comerciar con ganancias. Visita las tiendas personalmente, pregunta a los mercaderes o recoge chismes.";
		link.l1 = "Continúa.";
		link.l1.go = "Advice_3";
		link.l2 = "Espléndido. Bien, voy a tierra...";
		link.l2.go = "Finish_2";
		break;

	case "Advice_3":
		dialog.text = "Los cañones pueden dañarse y tendrás que reemplazarlos. También puedes quitar algunos de ellos para hacer espacio para las mercancías.";
		link.l1 = "Continúa.";
		link.l1.go = "Advice_4";
		link.l2 = "Espléndido. Bien, voy a tierra...";
		link.l2.go = "Finish_2";
		break;

	case "Advice_4":
		dialog.text = "Tienes que saber algo en caso de que vayamos a convertirnos en corsarios... Los capitanes compran barcos capturados por precios muy bajos, pero puedes revender los barcos con un gran beneficio.";
		link.l1 = "Continúa.";
		link.l1.go = "Advice_5";
		link.l2 = "Espléndido. Bien, voy a tierra...";
		link.l2.go = "Finish_2";
		break;

	case "Advice_5":
		dialog.text = "No arruines tus relaciones con los contrabandistas, ellos pueden proporcionarte una buena renta incluso con riesgo para tu vida.";
		link.l1 = "Continúa.";
		link.l1.go = "Advice_6";
		link.l2 = "Espléndido. Bien, voy a tierra...";
		link.l2.go = "Finish_2";
		break;

	case "Advice_6":
		dialog.text = "Contrata a algunos oficiales, no tenemos ninguno en este momento. Si tu autoridad es baja, entonces no podrás contratar muchos oficiales. En ese caso, debes encontrar personas que puedan trabajar en dos o tres puestos al mismo tiempo. Solo tres sabelotodos son suficientes para ocupar todos los puestos en nuestro barco.";
		link.l1 = "Continúa.";
		link.l1.go = "Advice_7";
		link.l2 = "Espléndido. Bien, voy a tierra...";
		link.l2.go = "Finish_2";
		break;

	case "Advice_7":
		dialog.text = "El robo no es un buen negocio, pero a veces realmente necesitas saquear un cofre en la casa, el banco o la tienda de alguien. Trata de esperar hasta que el dueño se dé la vuelta y solo entonces saquea el cofre. Y recuerda que tendrás problemas si alguien te ve. ¡Así que intenta ser más ágil!";
		link.l1 = "Continúa.";
		link.l1.go = "Advice_8";
		link.l2 = "Espléndido. Bien, voy a tierra...";
		link.l2.go = "Finish_2";
		break;

	case "Advice_8":
		dialog.text = "Quizás, un día necesites entrar en la ciudad enemiga. ¡Recuerda bien lo que te voy a decir ahora! No hay soldados en las puertas ni en el puerto por la noche. Así que será mejor que entres en la ciudad enemiga por la noche y solo intentes evitar las patrullas. Los soldados no tienen ojos en la espalda y solo ven las cosas frente a ellos. Escabúllete hasta la taberna y espera allí hasta que llegue la mañana y luego haz tus asuntos. Pero mantente alejado de los soldados de todos modos.";
		link.l1 = "Continúa.";
		link.l1.go = "Advice_9";
		link.l2 = "Espléndido. Bien, voy a tierra...";
		link.l2.go = "Finish_2";
		break;

	case "Advice_9":
		dialog.text = "También puedes izar la bandera enemiga si la tienes, y confiar en tu suerte y sigilo. La forma más confiable es comprar una licencia de la compañía comercial y nadie te detendrá. Solo no olvides izar la bandera correcta, sería tonto intentar mostrar una licencia mientras tu bandera es inglesa en un fuerte español.";
		link.l1 = "Continúa.";
		link.l1.go = "Advice_10";
		link.l2 = "Espléndido. Bien, voy a tierra...";
		link.l2.go = "Finish_2";
		break;

	case "Advice_10":
		dialog.text = "Sabe que se pueden encontrar prisiones en casi todos los puertos coloniales.";
		link.l1 = "Gracias. Tengo que desembarcar ahora.";
		link.l1.go = "Finish_2";
		break;
	/////   фехт
	case "Teach_1":
		dialog.text = "Bueno, comencemos entonces. Siempre fuiste bueno en eso, pero te lo recordaré. Hay tres movimientos de ataque: golpe normal, golpe fuerte y golpe perforante. También hay un ataque grupal de protección. Y una pistola, por supuesto, solo para saludar a tu oponente desde la distancia.";
		link.l1 = "Está bien, está bien, vayamos directamente al grano.";
		link.l1.go = "Teach_2";
		break;

	case "Teach_1_Jess":
		dialog.text = "Bueno,  comencemos entonces. Siempre has sido bueno en eso, pero te lo recordaré. Hay tres movimientos de ataque: golpe normal, golpe fuerte y golpe penetrante. También hay un ataque grupal defensivo. Y una pistola, por supuesto, solo para saludar a tu oponente desde la distancia.";
		link.l1 = "Continúa.";
		link.l1.go = "Teach_2";
		break;

	case "Teach_2":
		dialog.text = "...";
		link.l1 = "Muy bien... ¿El siguiente?";
		link.l1.go = "Teach_3";
		link.l2 = "¿Cuál es la energía?";
		link.l2.go = "Teach_2_1";
		break;

	case "Teach_2_1":
		dialog.text = "La energía es el indicador de tu resistencia en una pelea. Todos los movimientos de ataque requieren algo de energía. Te cansarás durante la pelea y a veces necesitarás descansar un poco para restaurar tu resistencia." + "La máxima de tu energía depende del valor actual de tu reacción.";
		link.l1 = "Continúa.";
		link.l1.go = "Teach_3";
		break;

	case "Teach_3":
		dialog.text = "Evita pelear con los numerosos enemigos o estarás muerto en segundos. Es posible luchar con dos de ellos, pero no es tan sencillo enfrentarse a tres o más enemigos a la vez. Observa su energía; cuando esté baja, empezarán a parar o a fintar. Ten cuidado o te cortarán la cabeza pronto.";
		link.l1 = "Continúa.";
		link.l1.go = "Teach_4";
		break;

	case "Teach_4":
		dialog.text = "Si finges a tu enemigo, recibirá un buen daño, especialmente si luchas con un arma ligera y pequeña. Y si logras parar sus ataques, perderá su energía y ritmo, permitiéndote golpearlo aún más fuerte.";
		link.l1 = "Continúa.";
		link.l1.go = "Teach_5";
		break;

	case "Teach_5":
		dialog.text = "Todas las armas son diferentes. Hay tipos ligeros, medianos y pesados. El peso determina las pérdidas de energía. Puedes luchar durante mucho tiempo con una pequeña daga, pero un hacha pesada te ayudará a matar instantáneamente a tu oponente, mientras que un sable puede ayudarte a luchar contra muchos enemigos a la vez.";
		link.l1 = "Continúa.";
		link.l1.go = "Teach_6";
		break;

	case "Teach_6":
		pchar.HeroParam.Teach_battle = 1;
		Tut_RestoreState();
		dialog.text = "¿Practicamos un poco? Te ofrezco un calentamiento. Lucharemos de verdad, pero no a muerte. Puedes curarte con elixires, pociones o ron, pero no los desperdicies ahora, es solo un entrenamiento.";
		link.l1 = "¡Vamos y no esperes piedad!";
		link.l1.go = "Teach_battle_1";
		link.l2 = "No, gracias, ya lo tengo.";
		link.l2.go = "Finish_1";
		break;

	case "Teach_battle_lose":
		Tut_RestoreState();
		dialog.text = LinkRandPhrase("Pues... Ahora estás realmente débil. Sé atento, bloquea y para más. Cuidado con los ataques fuertes, tus bloqueos no te salvarán de ellos, usa fintas, para o intenta retroceder.", "No dejes que los ataques pesados hagan contacto, atrapa los golpes del enemigo con tus fintas o intenta desviarlos. Ten cuidado y vigila las fintas o tus ataques serán atrapados y usados en tu contra.", "Corre o salta si tu energía está baja. Puedes intentar engañar a tu oponente. Debes saber que no es fácil fingir el golpe del enemigo, pero puedes burlarlo. Si lo logras, evitarás su golpe y lo golpearás de vuelta.") + "¿Intentamos de nuevo?";
		if (sti(pchar.rank) < 3) // чтоб не качались до упора
		{
			link.l1 = "¡Por supuesto!";
			link.l1.go = "Teach_battle_1";
		}
		link.l2 = "No, tuve suficiente. Lo tengo.";
		link.l2.go = "Finish_1";
		break;

	case "Teach_battle_win":
		pchar.HeroParam.Teach_battle = 2;
		Tut_RestoreState();
		dialog.text = "Bien. ¡Bien hecho!  Yo no estaba luchando sucio, pero tus oponentes podrían tener sus propios elixires y no serán derrotados tan fácilmente." + "Bueno, hagámoslo un poco más difícil. ¿Qué tal si luchas contra dos oponentes a la vez?";
		link.l1 = "Intentémoslo. ¡Oye, Hopkins! ¡Toma tu espada y sube a bordo!";
		link.l1.go = "Teach_battle_1";
		link.l2 = "No gracias, he tenido suficiente práctica.";
		link.l2.go = "Finish_1";
		break;

	case "Teach_battle_win_2":
		Tut_RestoreState();
		sld = characterFromID("Sailor_2");
		LAi_SetCitizenType(sld);
		if (pchar.name == "Jessica")
		{
			dialog.text = "¡Bien hecho, capitán! Las lecciones de Beltrope no fueron en vano, era un buen maestro. Ahora, el último consejo. Pelear con un solo tipo de arma mejorará mucho tu habilidad. Si quieres restaurar tus habilidades con cada tipo de espada, entonces cámbialas más a menudo.";
		}
		else
		{
			dialog.text = "Sí, tus manos están bien, tuvimos razón al esconder nuestras espadas. Ahora, el último consejo. Luchar con un solo tipo de arma aumentará mucho tu habilidad. Si quieres restaurar tus habilidades con cada tipo de espada, entonces cámbialas más a menudo.";
		}
		link.l1 = "¡Gracias!";
		link.l1.go = "Finish_1";
		break;

	case "Teach_battle_win_3":
		Tut_RestoreState();
		sld = characterFromID("Sailor_2");
		LAi_SetCitizenType(sld);
		dialog.text = "Bueno, no está mal. Has conseguido un oponente pero eran dos. Necesitas algo de práctica. Los enemigos pueden atacar de tres o cuatro a la vez. ¿Intentamos de nuevo?";
		if (sti(pchar.rank) < 3) // чтоб не качались до упора
		{
			link.l1 = "¡Por supuesto!";
			link.l1.go = "Teach_battle_1";
		}
		link.l2 = "No, he tenido suficiente. Lo tengo.";
		link.l2.go = "Finish_1";
		break;
	}
}
