// Диалог начала игры (туториал) 03.10.06 boal
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref sld;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Finish_2":
			SetAchievement("Test_Ach");
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
			//DoQuestFunctionDelay("Tutorial_Rest", 2.5);
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
				dialog.text = "돌아오셨군요, 선장님, 드디어! 신께 감사드리오, 우리는 거의 모든 희망을 잃을 뻔했소.";
				if (bBettaTestMode)
				{
					link.l0 = "베타테스트 - 건너뛰고 게임 시작";
					link.l0.go = "Finish_2";
				}
				link.l1 = "알론소? 대체 무슨 일이 있었던 거야? 그리고 왜 이렇게 머리가 지끈거리지?";
				link.l1.go = "Node_1_Jess";
			}
			else
			{
				dialog.text = "음, 선장님, 이제야 본래 모습이로군. 기분이 어떠신가?";
				//link.l2 = "베타테스트 - 롱웨이의 퀘스트 테스트 시작";
				//link.l2.go = "PZ_Test_Start_1";
				if (bBettaTestMode)
				{
					link.l0 = "베타테스트 - 건너뛰고 게임 시작";
					link.l0.go = "Finish_2";
				}
				link.l1 = "흠... 그 전에는 내가 어땠지?";
				link.l1.go = "Node_1";
			}
			locCameraFromToPos(-2.04, 4.95, 13.26, true, -0.82, 2.52, 7.87);
		break;
		
		case "PZ_Test_Start_1":
			dialog.text = "어디서부터 시작하지?";
			link.l0 = "에피소드 0. 프롤로그. (처음부터)";
			link.l0.go  = "PZ_Test_Start_S_samogo_nachala";
			link.l1 = "에피소드 1. 맹세를 지키는 자.";
			link.l1.go  = "PZ_Test_Start_BasTer";
			link.l2 = "에피소드 2-3. 역사 속의 한 페이지.";
			link.l2.go  = "PZ_Test_Start_Formosa";
			link.l4 = "에피소드 4. 속이는 별.";
			link.l4.go  = "PZ_Test_Start_Etap4";
			link.l51 = "에피소드 5-6. 떨어지는 별. (엘렌과 함께)";
			link.l51.go  = "PZ_Test_Start_Etap5_Helena";
			link.l52 = "에피소드 5-6. 떨어지는 별. (메리와 함께)";
			link.l52.go  = "PZ_Test_Start_Etap5_Mary";
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
			SetSailsColor(pchar, 0); //белый хлопковый парус
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 100;
			pchar.Ship.Crew.Exp.Sailors = 100;
			pchar.Ship.Crew.Exp.Cannoners = 100;
			pchar.Ship.Crew.Exp.Soldiers = 100;
			UpgradeShipParameter(pchar, "SpeedRate"); //апгрейдить скорость
			UpgradeShipParameter(pchar, "TurnRate");  //маневренность
			UpgradeShipParameter(pchar, "HP");        //корпус
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
			//Longway
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
		
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// Tichingitu
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
		
			// Элен:
			pchar.questTemp.Saga.Helena_officer = "true";
			sld = characterFromId("Helena");
			sld.greeting = "helena_hire";
			sld.quest.OfficerPrice = sti(pchar.rank) * 500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
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
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			LAi_SetImmortal(sld, false);
			// Baсker
			sld = GetCharacter(NPC_GenerateCharacter("Baker", "Baker", "man", "man_B", 1, ENGLAND, -1, false, "quest"));
			SetHeroAutolevel(sld);
			sld.name = "Raymond";
			sld.lastname = "Baсker";
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
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.CompanionDisable = true; //нельзя в компаньоны
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.DontClearDead = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			
			//Телепорт
			DoQuestReloadToLocation("Pirates_town", "reload", "reload1", "PZ_Etap5_Start");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
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
			SetSailsColor(pchar, 0); //белый хлопковый парус
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 100;
			pchar.Ship.Crew.Exp.Sailors = 100;
			pchar.Ship.Crew.Exp.Cannoners = 100;
			pchar.Ship.Crew.Exp.Soldiers = 100;
			UpgradeShipParameter(pchar, "SpeedRate"); //апгрейдить скорость
			UpgradeShipParameter(pchar, "TurnRate");  //маневренность
			UpgradeShipParameter(pchar, "HP");        //корпус
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
			//Longway
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// Tichingitu
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			// Мэри:
			pchar.questTemp.LSC.Mary_officer = "true";
			sld = characterFromId("Mary");
			sld.quest.OfficerPrice = sti(pchar.rank) * 500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.CompanionDisable = true;       //нельзя в компаньоны
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
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			// Baсker
			sld = GetCharacter(NPC_GenerateCharacter("Baker", "Baker", "man", "man_B", 1, ENGLAND, -1, false, "quest"));
			SetHeroAutolevel(sld);
			sld.name = "Raymond";
			sld.lastname = "Baсker";
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
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.CompanionDisable = true; //нельзя в компаньоны
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.DontClearDead = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			
			//Телепорт
			DoQuestReloadToLocation("Pirates_town", "reload", "reload1", "PZ_Etap5_Start");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
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
			pchar.Ship.name="MAYFANG";
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
			//Longway
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			// Tichingitu
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			//Элен
			 sld = characterFromId("Helena");
			GiveItem2Character(sld, "pirate_cutlass");
			EquipCharacterbyItem(sld, "pirate_cutlass");
			LAi_SetImmortal(sld, false);
			sld.quest.OfficerPrice = sti(pchar.rank) * 500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			DeleteAttribute(sld, "CompanionDisable");
			DeleteAttribute(sld, "HalfImmortal");
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			sld.CompanionDisable = true;       //нельзя в компаньоны - чтобы не утонула
			sld.HalfImmortal = true;           //чтобы не убили в сухопутном бою
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.DontClearDead = true;
			sld.dialog.currentnode = "Helena_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			pchar.questTemp.Saga.Helena_friend = "true"; // друг
			
			//Телепорт
			DoQuestReloadToLocation("Shore9", "reload", "reload1", "PZ_Etap4_Start");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
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
			pchar.Ship.name="MAYFANG";
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
			//Longway
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			// Tichingitu
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			
			//Телепорт
			DoQuestReloadToLocation("SentJons_town", "reload", "reload1", "PZ_BETA_Test_Start_S_samogo_nachala_2");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
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
			pchar.Ship.name="MAYFANG";
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
			//Longway
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			//AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			// Tichingitu
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			SetHeroAutolevel(sld);
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
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			
			//Телепорт
			DoQuestReloadToLocation("Mayak4", "goto", "goto2", "PZ_BETA_Test_Start_BasTer");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
		break;
		
		case "PZ_Test_Start_Formosa":
			DialogExit();
			
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			RemoveAllCharacterItems(pchar, true);
			//AddMoneyToCharacter(pchar, 10000000);
			GiveItem2Character(PChar, "blade_11");
			EquipCharacterByItem(Pchar, "blade_11");
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			pchar.rank = 25;
			SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
			SetSelfSkill(PChar, 50, 50, 50, 50, 50);
			SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
			
			//Телепорт
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
		break;

        case "Node_1":
			bGameMenuStart = false;
			StartBattleLandInterface();
			dialog.text = "그 붉은 피부의 이교도들처럼, 너도 그놈들 언어로 말하고 있었잖아.";
			link.l1 = "젠장! 알론소, 도대체 무슨 소리를 하는 거야?!";
			link.l1.go  = "Node_2";
		break;
		
		case "Node_1_Jess":
			dialog.text = "그걸 기억하지 못하지? 보통 사람 같으면 그런 타박상에 죽었거나, 평생 바지에 실례하면서 멍청하게 웃고 살았겠지. 그런데 넌 꽤 질긴 놈인 것 같다. 지금은 좀 약해졌고, 서 있는 것조차 힘들지. 우리가 너를 치료하려고 애쓴 지도 거의 반년이나 됐어.";
			link.l1 = "그 타박상에 대해 말해 줘, 나는 아무것도 기억이 안 나.";
			link.l1.go  = "Node_2_Jess";
		break;
		
		case "Node_2":
			dialog.text = "걱정하지 마, 너무 신경 쓰지 마. 신선한 공기 좀 마시고 바다를 봐, 그러면 머리도 괜찮아질 거야. 의사가 말하길, 정신이 들면 아무것도 기억 못 할 거라더라. 그러니까 억지로 기억하려고 하지 마, 그럴 필요 없어.";
			link.l1 = "다른 선택지는 무엇인지 궁금하군.";
			link.l1.go  = "Node_3";
		break;
		
		case "Node_2_Jess":
			dialog.text = "가면 ...";
			link.l1 = "젠장! 가면이 날 죽이려고 했어... 아무도 믿을 수 없어... 그리고 로렌스는? 살아 있는 건가?";
			link.l1.go  = "Node_3_Jess";
		break;
		
		case "Node_3":
			dialog.text = "의사가 분명히 정신병원에 가야 한다고 했지. 분열된 인격이라고 하더군. 그런데 홉킨스랑 나는 여기서 다른 인격은 못 봤어, 너 말고는 ...";
			link.l1 = "말도 안 돼! 그게 정말 내게 일어난 일이란 말이야?";
			link.l1.go  = "Node_4";
		break;
		
		case "Node_3_Jess":
			dialog.text = "아니, 다행히도 그런 일은 없었어. 아, 미안해... 그는 가면의 명령으로 교수형을 당했지. 그리고 가면은 상어에게 죽임을 당했다더군, 사람들이 그러더라고. 내 생각엔 둘 다 그런 꼴을 당할 만했어, 둘 다 개자식들이었으니까. 이런 악당들은 우리한테 너무 골칫거리였지.";
			link.l1 = "죽은 사람 험담하지 마라... 지난 일은 바꿀 수 없어. 그들의 심판자는 신이시다... 고맙네, 친구들, 날 구해줘서. 이 은혜 잊지 않겠네.";
			link.l1.go  = "Node_4_Jess";
		break;
		
		case "Node_4":
			dialog.text = "맹세코 말이야. 우리도 겁먹었었어, 네가 죽었으면 어쩌나 정말 몰랐지. 그리고 그 빨간 엉덩이 거지들이 너한테 뭘 마시게 한 거야! 뭐, 어쨌든 이제 괜찮으니 다행이지. 기분은 어때?";
			//link.l1 = "마신다고...? 어디서 본 것 같은데, 아무것도 기억이 안 나... 생각 좀 정리할게.";
			//link.l1.go  = "ChangePIRATES";
			link.l2 = "괜찮아. 그냥 어지럽고, 마치 취한 것 같아...";
			link.l2.go  = "Node_5";
		break;
		
		case "Node_4_Jess":
			dialog.text = "...";
			//link.l1 = "흠... 잠깐만, 생각 좀 정리해야겠어.";
			//link.l1.go  = "ChangePIRATES_Jess";
			link.l2 = "이제 괜찮아. 걱정해줘서 고마워, Alonso.";
			link.l2.go  = "Node_5_Jess";
		break;
		
		case "Node_5":
			dialog.text = "이제 술은 금지야. 네 또 다른 인격이 돌아오는 건 원치 않으니까. 검술 연습이나 좀 해봐. 칼 다루는 법도 다 잊었겠지.";
			link.l1 = "내 마음을 읽는군. 좋아, 한번 해보자고. 지금 곰처럼 힘이 넘치거든.";
			link.l1.go  = "Teach_1";
			link.l2 = "걱정 마, 내 손이 머리보다 훨씬 낫거든. 항구로 가는 게 좋겠어, 내가 너무 날뛰었으니까.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Node_5_Jess":
			dialog.text = "봐, 다 잘될 거라고 내가 알았지... 하지만 머리 부상은 장난이 아니야; 실력을 되찾으려면 시간이 좀 걸릴 거야. 검술 연습 좀 해볼래?";
			link.l1 = "좋은 생각이야. 내 실력을 시험해 보지.";
			link.l1.go  = "Teach_1_Jess";
			link.l2 = "아니, 나는 원하지 않아. 내 실력에는 자신 있으니까.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Finish_1":
			if (pchar.name == "Jessica")
			{
				dialog.text = "우리는 지금 항구에 있다 "+XI_ConvertString("Colony"+pchar.HeroParam.ToCityId+"Gen")+"우리는 어떻게든 이 가면들과 벨트로프 없이 새로운 삶을 시작해야 해, 그놈들 모두 지옥에서 썩어버리길... 그리고 선장님, 절대 실망시키지 않을 겁니다. 끝까지 함께하겠습니다.";
				link.l1 = "글쎄, 내가 살아 있는 것만으로도 운이 좋은 거겠지! 너희를 실망시키지 않을 거야, 누구도 실망시키지 않을 거고. 이제 됐다, 나는 육지로 나가봐야겠어.";
				link.l1.go  = "Finish_2";
				link.l2 = "놈 하나 줄고, 놈 하나 늘고, 세상사 다 그런 거지, 알론소. 내가 상륙하기 전에 조언 몇 가지 해줄 수 있겠나?";
				link.l2.go  = "Advice_1";
			}
			else
			{
				dialog.text = "우리는 지금 정착지 항구에 있다 "+XI_ConvertString("Colony"+pchar.HeroParam.ToCityId+"Gen")+", 편하게 쉬어, 하지만 꼭 돌아와. 진짜 기회를 이미 놓쳤거든 - 우리가 옛 배를 팔아야 했지만, 이 배로는 큰돈 못 받아. 그래서 네가 회복되길 기다리느라 우리도 중간에 멈췄지. 그리고 녀석들은 아직도 널 믿고 있어, 아니었으면 진작에 다 도망쳤을 거야...";
				link.l1 = "훌륭하군. 좋아, 나 육지로 나간다... 걱정 마, 길 잃지 않을 테니까.";
				link.l1.go  = "Finish_2";
				link.l2 = "내가 준비가 안 됐다고 생각하나?";
				link.l2.go  = "Advice_1";
			}
		break;
		
		case "Advice_1":
			dialog.text = "음, 선장... 우린 배를 수리하고, 인원도 더 뽑아야 하고, 보급품도 사야 해. 그리고 모험도 좀 찾아보자고! 물론, 공해에서 약탈할 생각이라면 사략허가장을 받아두는 게 현명할 거야. 그걸 받으면 당당하게 약탈할 수 있고, 가족들에게도 우리가 합법적으로 일한다고 말할 수 있지. 그리고 선장도 이름을 날릴 수 있을 거야...\n";
			link.l1 = "또 알아야 할 게 뭐지?";
			link.l1.go  = "Advice_2";
			link.l2 = "훌륭해. 좋아, 나 이제 상륙한다...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_2":
			dialog.text = "군도 상점들의 현재 상품 가격을 알아야 이익을 남기며 거래할 수 있다. 직접 상점에 들르거나, 상인들에게 물어보거나, 소문을 들어보아라.";
			link.l1 = "계속해.";
			link.l1.go  = "Advice_3";
			link.l2 = "훌륭해. 좋아, 나 육지로 나간다...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_3":
			dialog.text = "대포가 손상될 수 있으니 교체해야 할 수도 있다. 또한 일부 대포를 제거해서 화물을 실을 공간을 만들 수도 있다.";
			link.l1 = "계속해.";
			link.l1.go  = "Advice_4";
			link.l2 = "훌륭하군. 좋아, 나는 이제 상륙하러 간다...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_4":
			dialog.text = "우리가 사략선이 되려면 알아둬야 할 게 있어... 선주들은 나포한 배를 아주 헐값에 사들이지만, 네가 직접 배를 다시 팔면 큰 이익을 남길 수 있지.";
			link.l1 = "계속해.";
			link.l1.go  = "Advice_5";
			link.l2 = "훌륭하군. 좋아, 나는 이제 상륙하러 간다...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_5":
			dialog.text = "밀수업자들과의 관계를 망치지 마라, 그놈들은 네 목숨을 걸게 하더라도 꽤 괜찮은 수입을 챙겨줄 수 있으니까.";
			link.l1 = "계속해.";
			link.l1.go  = "Advice_6";
			link.l2 = "훌륭하군. 좋아, 난 이제 상륙하러 간다...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_6":
			dialog.text = "장교들을 좀 고용해. 지금은 아무도 없어. 권위가 낮으면 장교를 많이 못 뽑을 거야. 그런 경우엔 두세 가지 직책을 동시에 맡을 수 있는 사람을 찾아야 해. 우리 배에선 뭐든 아는 놈 셋만 있으면 모든 자리를 채울 수 있지.";
			link.l1 = "계속해.";
			link.l1.go  = "Advice_7";
			link.l2 = "훌륭하군. 좋아, 난 이제 상륙하러 간다...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = "도둑질이 좋은 일은 아니지만, 가끔은 남의 집이나 은행, 상점에 있는 상자를 털어야 할 때가 있지. 주인이 너에게서 시선을 돌릴 때까지 기다렸다가 그때 상자를 털어라. 그리고 누군가가 널 보면 곤란해질 테니 명심해. 그러니 좀 더 재빠르게 움직여!";
			link.l1 = "계속해.";
			link.l1.go  = "Advice_8";
			link.l2 = "훌륭하군. 좋아, 나는 이제 상륙하러 간다...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = "어쩌면 언젠가 적의 도시로 들어가야 할 일이 생길지도 몰라. 내가 지금부터 하는 말을 잘 기억해둬! 밤에는 성문이나 항구에 병사가 없어. 그러니 적의 도시에 들어가려면 밤에 들어가서 순찰대를 피하는 게 좋아. 병사들은 뒤통수에 눈이 달린 게 아니라 앞만 볼 수 있거든. 술집에 몰래 들어가서 아침이 될 때까지 기다렸다가, 그 다음에 네 볼일을 봐. 그래도 병사들은 계속 피하는 게 좋아.";
			link.l1 = "계속해.";
			link.l1.go  = "Advice_9";
			link.l2 = "훌륭하군. 좋아, 나는 이제 상륙하러 간다...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = "적국의 깃발을 가지고 있다면 그것을 올리고, 운과 은신에 기대볼 수도 있지. 가장 확실한 방법은 무역 회사에서 허가증을 사는 거야. 그러면 아무도 널 막지 않을 거다. 단, 올바른 깃발을 올리는 걸 잊지 마라 — 스페인 요새에서 영국 깃발을 달고 허가증을 보여주려 한다면 그건 어리석은 짓이지.";
			link.l1 = "계속해.";
			link.l1.go  = "Advice_10";
			link.l2 = "훌륭하군. 좋아, 나는 이제 상륙하러 간다...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = "거의 모든 식민지 항구에는 감옥이 있다는 걸 알아두시오.";
			link.l1 = "고마워. 이제 상륙해야겠어.";
			link.l1.go  = "Finish_2";
		break;
		/////   фехт 
		case "Teach_1":
			dialog.text = "자, 그럼 시작하자. 넌 원래 이런 건 잘했지만, 다시 한 번 상기시켜주지. 공격 동작은 세 가지가 있어 — 일반 타격, 강타, 그리고 관통 타격이지. 방어용 단체 공격도 있고. 그리고 물론, 권총도 있지. 멀리서 상대에게 인사하는 용도니까.";
			link.l1 = "좋아, 좋아, 바로 본론으로 들어가자.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_1_Jess":
			dialog.text = "자, 그럼 시작하자. 넌 원래 이런 건 잘했지만, 다시 한 번 상기시켜 주지. 공격 동작은 세 가지가 있어. 일반 타격, 강한 일격, 그리고 관통 공격이지. 그리고 방어용 단체 공격도 있다. 물론 권총도 있지, 멀리서 상대에게 인사하는 용도로 말이야.";
			link.l1 = "계속해.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_2":
			dialog.text = "...";
			link.l1 = "좋아... 다음은?";
			link.l1.go  = "Teach_3";
			link.l2 = "에너지가 무엇이지?";
			link.l2.go  = "Teach_2_1";
		break;
		
		case "Teach_2_1":
			dialog.text = "에너지는 전투에서 당신의 체력 상태를 나타내는 지표다. 모든 공격 동작에는 일정량의 에너지가 필요하다.\n전투 중에는 점점 지치게 되며, 때로는 체력을 회복하기 위해 휴식이 필요할 것이다."+"당신의 최대 에너지는 현재 반응 수치에 따라 달라집니다.";
			link.l1 = "계속해.";
			link.l1.go  = "Teach_3";
		break;
		
		case "Teach_3":
			dialog.text = "적이 많으면 싸움을 피하라, 그렇지 않으면 순식간에 죽게 될 것이다.\n둘 정도는 상대할 수 있지만, 세 명 이상을 한꺼번에 상대하는 건 그리 쉽지 않다.\n적의 기력을 잘 살펴라. 기력이 떨어지면 막거나 속임수를 쓸 것이다.\n방심하면 곧 네 목이 잘릴 테니 조심해라.";
			link.l1 = "계속해.";
			link.l1.go  = "Teach_4";
		break;
		
		case "Teach_4":
			dialog.text = "적을 속이면, 특히 가볍고 작은 무기로 싸울 때 큰 피해를 입힐 수 있다.\n그리고 상대의 공격을 받아넘길 수 있다면, 그는 기력과 리듬을 잃게 되어 네가 더 강하게 공격할 수 있게 된다.";
			link.l1 = "계속해.";
			link.l1.go  = "Teach_5";
		break;
		
		case "Teach_5":
			dialog.text = "모든 무기는 다르다. 가벼운 것, 보통 것, 무거운 것이 있지. 무게에 따라 체력 소모가 달라진다. 작은 단검으로는 오래 싸울 수 있지만, 무거운 도끼는 상대를 단번에 죽일 수 있고, 세이버는 여러 적을 한꺼번에 상대하는 데 도움이 된다.";
			link.l1 = "계속해.";
			link.l1.go  = "Teach_6";
		break;
		
		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			Tut_RestoreState();
			dialog.text = "조금 연습해 볼까? 몸 좀 풀자고. 진짜로 싸우긴 하겠지만, 죽을 때까지는 아니야. 엘릭서나 약, 럼주로 회복해도 되지만, 지금은 아까우니 너무 쓰지 마—이건 그냥 훈련이니까.";
			link.l1 = "가자, 자비는 기대하지 마!";
			link.l1.go  = "Teach_battle_1";
			link.l2 = "아니, 고맙지만 이미 가지고 있어.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = LinkRandPhrase("음... 지금 너 정말 약하구나. 정신 똑바로 차리고, 막고 받아내는 걸 더 신경 써. 강한 공격 조심해, 막기만으론 못 막아내니까, 속임수 쓰거나 받아내거나, 아니면 뒤로 물러서 봐.","강한 공격이 닿지 않게 하고, 적의 공격은 페인트로 받아 넘기거나 막아내도록 해라. 조심해서 페인트에 주의하지 않으면 네 공격이 잡혀서 되려 당할 수 있다.","기력이 부족하면 도망치거나 뛰어 피하라. 상대를 속이는 척을 시도해 볼 수도 있다. 적의 공격을 속이기는 쉽지 않다는 걸 명심해라. 그래도 속일 수는 있다. 성공하면 적의 공격을 피하고 반격할 수 있다.")+"다시 한 번 해볼까?";
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = "물론이지!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2 = "아니, 이제 됐어. 알겠어.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = "좋아. 잘했어! 나는 비열하게 싸우지 않았지만, 네 상대들은 자신들만의 엘릭서를 가지고 있을 수도 있고 그렇게 쉽게 쓰러지지 않을 거야. "+"좋아, 좀 더 어렵게 해보자. 두 명을 한꺼번에 상대하는 건 어때?";
			link.l1 = "해보자. 이봐, 홉킨스! 칼 챙기고 배에 올라타!";
			link.l1.go  = "Teach_battle_1";
			link.l2 = "고맙지만, 연습은 이제 충분해.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			if (pchar.name == "Jessica")
			{
				dialog.text = "잘했네, 선장! 벨트로프의 가르침이 헛되지 않았어; 그는 훌륭한 스승이었지. 이제 마지막으로 한 가지 조언을 주겠네. 한 종류의 무기로 계속 싸우면 그 무기에 대한 실력이 크게 늘 것이야. 만약 모든 종류의 검술 실력을 회복하고 싶다면, 무기를 자주 바꾸게.";
			}
			else
			{
				dialog.text = "그래, 네 손은 멀쩡하군. 우리가 칼을 숨긴 건 옳은 판단이었지. 이제 마지막으로 한 가지 조언을 해주마.\n한 종류의 무기만 계속 쓰면 그 무기에 대한 실력이 크게 늘 거다. 모든 종류의 칼 실력을 고루 키우고 싶다면, 자주 바꿔가며 싸워라.";
			}
			link.l1 = "고마워!";
			link.l1.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = "음, 나쁘지 않아. 상대 하나는 해치웠지만 두 명이었지. 연습이 좀 더 필요하겠군. 적들은 한 번에 셋이나 넷씩 덤벼들 수도 있어. 다시 한 번 해볼까?";
   			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = "물론이지!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2 = "아니, 이제 됐어. 이해했어.";
			link.l2.go  = "Finish_1";
		break;
	}
}
