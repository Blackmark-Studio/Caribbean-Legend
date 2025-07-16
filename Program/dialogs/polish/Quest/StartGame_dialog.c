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
			dialog.text = "Kapitanie, ostatnie pytanie. Jaką wiadomość mam przekazać załodze?";
			link.l1 = "Co masz na myśli?";
			link.l1.go  = "Finish_2_0";
		break;
		
		case "Finish_2_0":
			dialog.text = "Ludzie chcą wiedzieć, czego się spodziewać. Wygląda na to, że jeszcze się nie zdecydowałeś.";
			link.l1 = "Jakie mam opcje?";
			link.l1.go  = "Finish_2_0_1";
		break;
		
		case "Finish_2_0_1":
			dialog.text = "Cóż, Kapitanie, Karaiby to wyjątkowe miejsce. Możesz zająć się handlem, grabieżą, zanurzyć się w szemrane interesy lub wyruszyć na poszukiwanie skarbów - jest niezliczona ilość dróg do stania się legendą na tych wodach. Załoga i ja przedyskutowaliśmy to i jesteśmy gotowi wesprzeć każdą decyzję, którą podejmiesz.";
			link.l1 = "Czy muszę wybrać tylko jedną?";
			link.l1.go  = "Finish_2_0_2";
		break;
		
		case "Finish_2_0_2":
			dialog.text = "Nie, z pewnością nie, ale to dobry pomysł, by ustalić nasze początkowe priorytety.";
			link.l1 = "Jak każdy rozsądny człowiek, pragnę zgromadzić fortunę! Milion pesos by wystarczyło.";
			link.l1.go  = "Finish_2_1";
			link.l2 = "Pragnę zdobyć szacunek - taki, jaki miał l'Olonnais po splądrowaniu Maracaibo.";
			link.l2.go  = "Finish_2_2";
			link.l3 = "Przygoda! Pragnę zwiedzać egzotyczne miejsca i spotykać ciekawych bohaterów.";
			link.l3.go  = "Finish_2_3";
			link.l4 = "Zawsze marzyłem o romantycznym uroku bycia poszukiwaczem skarbów!";
			link.l4.go  = "Finish_2_4";
			link.l5 = "Zachowaj swoje rady, Alonso. Czemu się ograniczać? Wiem, czego chcę, i chcę to wszystko!";
			link.l5.go  = "Finish_2_5";
		break;
		
		case "Finish_2_1":
			pchar.questTemp.SanBoxTarget = 1;
			dialog.text = "To całkiem ambicja, Kapitanie. Najszybszym sposobem jest atakowanie statków handlowych i zajmowanie się przemytem. Możesz również wybrać uczciwy handel, ale to zajmie trochę więcej czasu. Jednak nie musisz się ograniczać - podejmuj się każdej pracy i wplątuj się we wszelkie kłopoty, jakie znajdziesz. Tak się zdobywa fortunę. Poinformuję załogę, Kapitanie. Oby fortuna sprzyjała nam wszystkim!";
			link.l1 = "Rozpocznij grę";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_2":
			pchar.questTemp.SanBoxTarget = 2;
			dialog.text = " Ale czy wiesz, jak l'Olonnais zakończył swój żywot? Cóż, nie będę cię osądzał, Kapitanie. Przelewanie niewinnej krwi może być opłacalne, ale bądź gotów na konsekwencje. Będziesz potrzebował okrętu bojowego, a może nawet eskadry, aby zdobyć fort i ustanowić przyczółek. Alternatywnie, możesz zdobyć miasto lądem - czterystu ludzi powinno wystarczyć, ale zapewniam, że niespacyfikowany garnizon szybko odeprze cię z powrotem do dżungli. Przekażę twój wybór załodze, Kapitanie. Oby fortuna sprzyjała nam wszystkim!";
			link.l1 = "Rozpocznij grę";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_3":
			pchar.questTemp.SanBoxTarget = 3;
			dialog.text = "Mamy obfitość obu, Kapitanie! Odwiedzaj miasta, mieszaj się z miejscowymi, a przygody same Cię znajdą. Tylko pamiętaj, że poważni ludzie poproszą o Twoją pomoc dopiero, gdy udowodnisz swoją wartość i zbudujesz reputację. Załoga to doceni. Niech fortuna nam sprzyja!";
			link.l1 = "Rozpocznij grę";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_4":
			pchar.questTemp.SanBoxTarget = 4;
			dialog.text = "Nie ma w tym fachu zbyt wiele romansu, Kapitanie. To zajęcie długotrwałe, ale dochodowe, zwłaszcza jeśli szczęście ci sprzyja. Szukaj map skarbów u sprzedawców w tawernach i miej oczy szeroko otwarte - spotkasz wielu rywalizujących łowców, którzy chcą się wzbogacić twoim kosztem. Ponadto, najcenniejsze skarby często wymagają złożenia połowy mapy z prostszych znalezisk, więc do dzieła! Niech fortuna sprzyja nam wszystkim!";
			link.l1 = "Rozpocznij grę";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_5":
			pchar.questTemp.SanBoxTarget = 5;
			dialog.text = "W takim razie rozumiesz, co jest potrzebne, aby stać się legendą Karaibów, Kapitanie. Załoga wierzy w ciebie i z niecierpliwością oczekuje na twoje osiągnięcia. Niech fortuna nam wszystkim sprzyja!";
			link.l1 = "Rozpocznij grę";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_3":
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
				dialog.text = "Nareszcie jesteś z powrotem, kapitanie! Dzięki Bogu, prawie straciliśmy wszelką nadzieję.";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - pomiń i rozpocznij grę";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Alonso? Co się, u diabła, stało? I dlaczego mam taki okropny ból głowy?";
				link.l1.go = "Node_1_Jess";
			}
			else
			{
				dialog.text = "Cóż, kapitanie, teraz wyglądasz jak powinieneś. Jak się czujesz?";
				//link.l2 = "BetaTest - Rozpocznij test zadania Longwaya";
				//link.l2.go = "PZ_Test_Start_1";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - pomiń i rozpocznij grę";
					link.l0.go = "Finish_2";
				}
				link.l1 = " Hm... a jak było ze mną wcześniej?";
				link.l1.go = "Node_1";
			}
			locCameraFromToPos(-2.04, 4.95, 13.26, true, -0.82, 2.52, 7.87);
		break;
		
		case "PZ_Test_Start_1":
			dialog.text = "Od czego zaczynamy?";
			link.l0 = "Epizod 0. PROLOG. (od samego początku)";
			link.l0.go  = "PZ_Test_Start_S_samogo_nachala";
			link.l1 = "Epizod 1. WIERNY PRZYSIĘDZE.";
			link.l1.go  = "PZ_Test_Start_BasTer";
			link.l2 = "Epizod 2-3. KARTY HISTORII.";
			link.l2.go  = "PZ_Test_Start_Formosa";
			link.l4 = "Epizod 4. ZŁUDNA GWIAZDA.";
			link.l4.go  = "PZ_Test_Start_Etap4";
			link.l51 = "Epizod 5-6. SPADAJĄCA GWIAZDA. (Z Eleną)";
			link.l51.go  = "PZ_Test_Start_Etap5_Helena";
			link.l52 = "Epizod 5-6. SPADAJĄCA GWIAZDA. (Z Mery)";
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
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
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
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
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
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			LAi_SetImmortal(sld, false);
			// Baсker
			sld = GetCharacter(NPC_GenerateCharacter("Baker", "Baker", "man", "man_B", 1, ENGLAND, -1, false, "quest"));
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
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			// Baсker
			sld = GetCharacter(NPC_GenerateCharacter("Baker", "Baker", "man", "man_B", 1, ENGLAND, -1, false, "quest"));
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
			dialog.text = "Jak ci czerwonoskórzy ateiści, nawet mówiłeś w ich języku.";
			link.l1 = "Do diabła! Alonso, co ty, u licha, wygadujesz?!";
			link.l1.go  = "Node_2";
		break;
		
		case "Node_1_Jess":
			dialog.text = "Nie pamiętasz tego, prawda? Pewnie, ktoś inny umarłby od takiego urazu albo śmiałby się i psuł spodnie do końca życia, ale wydaje się, że jesteś twardzielem. Choć jesteś słabszy i nawet stanie na nogach jest dla ciebie problemem. Minęło już prawie pół roku, odkąd próbujemy cię wyleczyć.";
			link.l1 = "Opowiedz mi o tym siniaku, nic nie pamiętam.";
			link.l1.go  = "Node_2_Jess";
		break;
		
		case "Node_2":
			dialog.text = "Nie martw się, nie musisz się martwić. Wdychaj świeże powietrze i spójrz na morze, wtedy twoja głowa będzie w porządku. Lekarz powiedział, że niczego nie będziesz pamiętać, gdy dojdziesz do siebie. Więc nie próbuj sobie przypominać, nie potrzebujesz tego.";
			link.l1 = "Jestem ciekaw mojej innej opcji.";
			link.l1.go  = "Node_3";
		break;
		
		case "Node_2_Jess":
			dialog.text = "Maska ...";
			link.l1 = "Do diabła! Mask próbował mnie zabić... Nikomu nie można ufać... A co z Lawrence'em? Czy żyje?";
			link.l1.go  = "Node_3_Jess";
		break;
		
		case "Node_3":
			dialog.text = "Doktor powiedział, że to na pewno będzie azyl. Rozdwojenie jaźni, powiedział. A Hopkins i ja nie widzieliśmy tu żadnej innej osobowości oprócz ciebie ...";
			link.l1 = " Bzdura! Czy to naprawdę mi się przydarzyło?";
			link.l1.go  = "Node_4";
		break;
		
		case "Node_3_Jess":
			dialog.text = "Nie, dzięki Bogu. Och, przepraszam... Został powieszony na rozkaz Maski. A Maskę przeciął Rekin, tak mówią. Myślę, że wszyscy na to zasłużyli, byli łajdakami obaj. Ci łotrzy byli dla nas zbyt dużym kłopotem.";
			link.l1 = "Nie mów brzydko o zmarłych... Nie możemy zmienić przeszłości. Bóg będzie ich sędzią... Dziękuję wam, towarzysze, za ocalenie mnie, nie zapomnę tego.";
			link.l1.go  = "Node_4_Jess";
		break;
		
		case "Node_4":
			dialog.text = "Przysięgam ci. My też byliśmy przerażeni, nie mielibyśmy pojęcia, co zrobić, gdybyś był martwy. A co ci te czerwone sukinsyny dały do picia! No cóż, dzięki Bogu, teraz jesteś w porządku. Jak się czujesz?";
			//link.l1 = "Pić, mówisz... wygląda znajomo, niczego nie pamiętam... Pozwól mi zebrać myśli.";
			//link.l1.go  = "ChangePIRATES";
			link.l2 = "Czuję się dobrze. Po prostu czuję się oszołomiony, to tak jakby być pijanym...";
			link.l2.go  = "Node_5";
		break;
		
		case "Node_4_Jess":
			dialog.text = "...";
			//link.l1 = "Hm... daj mi chwilę, muszę zebrać myśli.";
			//link.l1.go  = "ChangePIRATES_Jess";
			link.l2 = "Czuję się teraz dobrze. Dzięki za troskę, Alonso.";
			link.l2.go  = "Node_5_Jess";
		break;
		
		case "Node_5":
			dialog.text = "Alkohol jest teraz dla ciebie zabroniony. Nie chcemy, by wróciła twoja rozdwojona osobowość. Dobrze byłoby trochę poćwiczyć szermierkę. Założę się, że zapomniałeś, jak się posługiwać ostrzem.";
			link.l1 = " Czytasz mi w myślach. No cóż, spróbujmy, czuję się silny jak niedźwiedź.";
			link.l1.go  = "Teach_1";
			link.l2 = "Nie martw się, moje ręce są znacznie lepsze w porównaniu do mojej głowy. Lepiej pójdę do portu, za bardzo się rozbrykałem.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Node_5_Jess":
			dialog.text = "Widzisz, wiedziałem, że wszystko będzie dobrze... Ale rana w głowie to nie żart, potrzeba czasu, aby przywrócić twoje umiejętności. Nie chciałbyś poćwiczyć trochę fechtunku?";
			link.l1 = "Dobry pomysł. Pozwól, że wypróbuję swoje umiejętności.";
			link.l1.go  = "Teach_1_Jess";
			link.l2 = "Nie, nie chcę. Jestem pewny swoich umiejętności.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Finish_1":
			if (pchar.name == "Jessica")
			{
				dialog.text = "Jesteśmy teraz w porcie "+XI_ConvertString("Colony"+pchar.HeroParam.ToCityId+"Gen")+". Musimy jakoś zacząć nowe życie bez tych wszystkich Masek i Beltropów, niech wszyscy zgniją w piekle... I nie zawiedziemy cię, kapitanie. Zostaniemy z tobą do końca.";
				link.l1 = "No cóż, chyba mam szczęście, że żyję! Nie zawiodę cię ani was wszystkich. To wszystko, muszę wylądować.";
				link.l1.go  = "Finish_2";
				link.l2 = "Jeden drań mniej, jeden drań więcej, tak już jest, Alonso. Dasz mi parę rad przed lądowaniem?";
				link.l2.go  = "Advice_1";
			}
			else
			{
				dialog.text = "Jesteśmy teraz w porcie osady "+XI_ConvertString("Colony"+pchar.HeroParam.ToCityId+"Gen")+", rozgość się, ale wracaj. Już przegapiliśmy prawdziwą sprawę - musieliśmy sprzedać stary statek, ale na tym wiele nie zarobisz. Przerwała nam jednak nadzieja na twoje wyzdrowienie. A chłopaki wciąż w ciebie wierzą, inaczej dawno by się rozbiegli...";
				link.l1 = "Znakomicie. Dobrze, schodzę na ląd... Nie martw się, nie zgubię się.";
				link.l1.go  = "Finish_2";
				link.l2 = "Jeśli myślisz, że nie jestem gotowy?";
				link.l2.go  = "Advice_1";
			}
		break;
		
		case "Advice_1":
			dialog.text = "Wiesz, kapitanie... Musimy naprawić statek, zwerbować więcej ludzi i kupić zapasy. I poszukajmy jakichś przygód! Oczywiście, przyda się nam list kaperski na wypadek, gdybyśmy zamierzali plądrować otwarte morza. Da nam to wszelkie prawa do tego i będziemy mogli powiedzieć naszym rodzinom, że nasza praca jest całkowicie legalna. A ty będziesz mógł zdobyć sobie imię...";
			link.l1 = "Co jeszcze powinienem wiedzieć?";
			link.l1.go  = "Advice_2";
			link.l2 = "Znakomicie. Dobrze, idę na ląd...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_2":
			dialog.text = "Musisz znać aktualne ceny towarów w sklepach archipelagu, aby handlować z zyskiem. Odwiedzaj sklepy osobiście, pytaj kupców lub zbieraj plotki.";
			link.l1 = "Idź dalej.";
			link.l1.go  = "Advice_3";
			link.l2 = "Znakomicie. Dobrze, schodzę na ląd...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_3":
			dialog.text = "Armaty mogą ulec uszkodzeniu i będziesz musiał je wymienić. Możesz także zabrać część z nich, aby zaoszczędzić miejsce na towary.";
			link.l1 = "Idź dalej.";
			link.l1.go  = "Advice_4";
			link.l2 = "Wspaniale. Dobrze, idę na ląd...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_4":
			dialog.text = "Musisz coś wiedzieć, jeśli zamierzamy zostać kaperami... Kapitanowie statków kupują zdobyte statki za bardzo niskie ceny, ale możesz je odsprzedać z dużym zyskiem.";
			link.l1 = "Kontynuuj.";
			link.l1.go  = "Advice_5";
			link.l2 = "Znakomicie. Dobrze, schodzę na ląd...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_5":
			dialog.text = "Nie psuj swoich relacji z przemytnikami, potrafią zapewnić ci niezły dochód, nawet ryzykując twoim życiem.";
			link.l1 = "Kontynuuj.";
			link.l1.go  = "Advice_6";
			link.l2 = "Wspaniale. Dobrze, schodzę na ląd...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_6":
			dialog.text = "Wynajmij kilku oficerów, nie mamy teraz żadnych. Jeśli twoja władza jest niska, nie będziesz w stanie zatrudnić wielu oficerów. W takim przypadku powinieneś znaleźć ludzi, którzy potrafią pracować na dwóch lub trzech stanowiskach jednocześnie. Wystarczy trzech wszystkowiedzących, aby obsadzić wszystkie stanowiska na naszym statku.";
			link.l1 = "Idź dalej.";
			link.l1.go  = "Advice_7";
			link.l2 = "Wspaniale. Dobrze, schodzę na ląd...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = "Kradzież to nie jest dobry interes, ale czasem naprawdę musisz splądrować skrzynię w czyimś domu, banku lub sklepie. Spróbuj poczekać, aż gospodarz odwróci się od ciebie i dopiero wtedy splądruj skrzynię. I pamiętaj, że będziesz miał kłopoty, jeśli ktoś cię zauważy. Więc postaraj się być bardziej zwinny!";
			link.l1 = "Idź dalej.";
			link.l1.go  = "Advice_8";
			link.l2 = "Wspaniale. Dobrze, idę na ląd...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = "Może, pewnego dnia będziesz musiał dostać się do wrogiego miasta. Dobrze zapamiętaj, co teraz powiem! W nocy przy bramach i w porcie nie ma żołnierzy. Lepiej wejść do wrogiego miasta nocą i po prostu starać się unikać patroli. Żołnierze nie mają oczu na plecach i widzą tylko to, co przed nimi. Zakradnij się do tawerny i czekaj tam do rana, a potem załatw swoje sprawy. Ale trzymaj się z dala od żołnierzy, mimo wszystko.";
			link.l1 = "Idź dalej.";
			link.l1.go  = "Advice_9";
			link.l2 = "Znakomicie. Dobrze, idę na ląd...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = "Możesz również podnieść wrogą banderę, jeśli ją masz, i liczyć na szczęście i skrytość. Najbardziej niezawodnym sposobem jest zakup licencji od kompanii handlowej i nikt cię nie zatrzyma. Tylko nie zapomnij podnieść właściwej bandery, byłoby głupio próbować pokazać licencję, gdy twoja bandera jest angielska w hiszpańskim forcie.";
			link.l1 = "Śmiało.";
			link.l1.go  = "Advice_10";
			link.l2 = "Wspaniale. Dobrze, idę na ląd...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = "Wiedz, że więzienia można znaleźć w prawie każdym kolonialnym porcie.";
			link.l1 = "Dzięki. Muszę teraz zejść na ląd.";
			link.l1.go  = "Finish_2";
		break;
		/////   фехт 
		case "Teach_1":
			dialog.text = "Cóż, zacznijmy zatem. Zawsze byłeś w tym dobry, ale przypomnę ci. Są trzy rodzaje ataku - zwykły cios, ciężki cios i przebijający cios. Jest także obronny atak grupowy. I pistolet, oczywiście, żeby przywitać przeciwnika z dystansu.";
			link.l1 = "Dobrze, dobrze, przejdźmy od razu do interesów.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_1_Jess":
			dialog.text = "Cóż, zacznijmy zatem. Zawsze byłeś w tym dobry, ale przypomnę ci. Są trzy ruchy atakujące - normalne uderzenie, ciężki cios i przebijające pchnięcie. Jest także obrona grupowa. I pistolet, oczywiście, żeby przywitać przeciwnika z dystansu.";
			link.l1 = "Śmiało.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_2":
			dialog.text = "...";
			link.l1 = "Bardzo dobrze... Następny?";
			link.l1.go  = "Teach_3";
			link.l2 = "Co to za energia?";
			link.l2.go  = "Teach_2_1";
		break;
		
		case "Teach_2_1":
			dialog.text = " Energia jest wskaźnikiem twojej wytrzymałości w walce. Wszystkie ataki wymagają trochę energii. Zmęczysz się podczas walki i czasami musisz odpocząć, aby odzyskać swoją wytrzymałość."+"Maksimum twojej energii zależy od aktualnej wartości twojej reakcji.";
			link.l1 = "Idź dalej.";
			link.l1.go  = "Teach_3";
		break;
		
		case "Teach_3":
			dialog.text = "Unikaj walki z licznymi wrogami, bo w przeciwnym razie zginiesz w kilka sekund. Można walczyć z dwoma naraz, ale nie jest to takie proste, gdy masz do czynienia z trzema lub więcej przeciwnikami jednocześnie. Obserwuj ich energię; kiedy będzie niska, zaczną parować lub udawać ataki. Bądź ostrożny, bo wkrótce możesz stracić głowę.";
			link.l1 = "Idź dalej.";
			link.l1.go  = "Teach_4";
		break;
		
		case "Teach_4":
			dialog.text = "Jeśli zmylesz wroga, otrzyma on znaczne obrażenia, zwłaszcza jeśli walczysz lekką i małą bronią. A jeśli będziesz w stanie sparować jego ataki, straci energię i rytm, co pozwoli ci uderzyć go jeszcze mocniej.";
			link.l1 = "Idź dalej.";
			link.l1.go  = "Teach_5";
		break;
		
		case "Teach_5":
			dialog.text = "Każda broń jest inna. Istnieją rodzaje lekkie, średnie i ciężkie. Waga determinuje straty energii. Możesz walczyć długo z małym sztyletem, ale ciężki topór pomoże ci natychmiast zabić przeciwnika, podczas gdy szabla może pomóc w walce z wieloma wrogami naraz.";
			link.l1 = "Idź dalej.";
			link.l1.go  = "Teach_6";
		break;
		
		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			Tut_RestoreState();
			dialog.text = "Poćwiczmy trochę? Proponuję ci rozgrzewkę. Będziemy walczyć na serio, ale nie na śmierć. Możesz leczyć się eliksirami, miksturami lub rumem, ale nie marnuj ich teraz, to tylko trening.";
			link.l1 = "Chodźmy i nie spodziewaj się litości!";
			link.l1.go  = "Teach_battle_1";
			link.l2 = "Nie, dziękuję, już to mam.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = LinkRandPhrase("Cóż... Teraz jesteś naprawdę słaby. Bądź uważny, blokuj i paruj więcej. Uważaj na ciężkie ataki, twoje bloki cię przed nimi nie uratują, używaj finty, paruj lub spróbuj się cofnąć.","Nie pozwól, by ciężkie ataki dosięgły celu, przechwyć ciosy wroga za pomocą swoich zmyłek lub spróbuj je sparować. Bądź ostrożny i uważaj na zmyłki, bo inaczej twoje ataki zostaną przechwycone i obrócone przeciwko tobie.","Uciekaj lub skacz, jeśli masz mało energii. Możesz spróbować zmylić przeciwnika. Wiedz, że nie jest łatwo zmylić cios przeciwnika, ale możesz go oszukać. Jeśli ci się uda, unikniesz jego ciosu i oddasz mu.")+"Spróbujmy jeszcze raz?";
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = "Jasne!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2 = "Nie, miałem dość. Zrozumiałem.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = "Dobrze. Świetna robota! Nie walczyłem nieuczciwie, ale twoi przeciwnicy mogą mieć własne eliksiry i nie będą tak łatwo pokonani. "+"Cóż, uczyńmy to nieco trudniejszym. Co powiesz na walkę przeciwko dwóm przeciwnikom jednocześnie?";
			link.l1 = "Spróbujmy. Hej, Hopkins! Weź swój ostrze i wejdź na pokład!";
			link.l1.go  = "Teach_battle_1";
			link.l2 = "Nie, dziękuję, miałem już dość praktyki.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			if (pchar.name == "Jessica")
			{
				dialog.text = "Dobra robota, kapitanie! Lekcje Beltrope'a nie poszły na marne, był dobrym nauczycielem. Teraz ostatnia rada. Walka jednym rodzajem broni znacznie podniesie twoje umiejętności. Jeśli chcesz przywrócić swoje umiejętności we wszystkich rodzajach ostrzy, zmieniaj je częściej.";
			}
			else
			{
				dialog.text = "Tak, twoje ręce są w porządku, dobrze zrobiliśmy, chowając nasze ostrza. Teraz ostatnia rada. Walka jednym rodzajem broni znacznie podniesie twoje umiejętności. Jeśli chcesz przywrócić swoje umiejętności z każdym rodzajem ostrzy, to zmieniaj je częściej.";
			}
			link.l1 = "Dzięki!";
			link.l1.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = "Cóż, nieźle. Masz jednego przeciwnika, ale było ich dwóch. Potrzeba trochę praktyki. Wrogowie mogą atakować trzema lub czterema naraz. Spróbujmy jeszcze raz?";
   			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = "Pewnie!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2 = "Nie, mam dość. Rozumiem.";
			link.l2.go  = "Finish_1";
		break;
	}
}
