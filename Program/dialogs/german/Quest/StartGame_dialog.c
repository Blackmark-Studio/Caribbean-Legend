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
			dialog.text = "Kapitän, eine letzte Frage. Welche Botschaft soll ich der Besatzung übermitteln?";
			link.l1 = "Was meinst du?";
			link.l1.go  = "Finish_2_0";
		break;
		
		case "Finish_2_0":
			dialog.text = "Die Leute wollen wissen, was sie erwartet. Es sieht so aus, als hättest du dich noch nicht entschieden.";
			link.l1 = "Welche Optionen habe ich?";
			link.l1.go  = "Finish_2_0_1";
		break;
		
		case "Finish_2_0_1":
			dialog.text = "Nun, Kapitän, die Karibik ist ein einzigartiger Ort. Du kannst Handel treiben, plündern, dich in zwielichtige Angelegenheiten stürzen oder auf Schatzjagd gehen - es gibt unzählige Wege, um in diesen Gewässern zur Legende zu werden. Die Crew und ich haben darüber gesprochen, und wir sind bereit, jede Entscheidung zu unterstützen, die du triffst.";
			link.l1 = "Muss ich nur einen auswählen?";
			link.l1.go  = "Finish_2_0_2";
		break;
		
		case "Finish_2_0_2":
			dialog.text = "Nein, sicherlich nicht, aber es ist eine gute Idee, unsere ersten Prioritäten zu setzen.";
			link.l1 = "Wie jeder vernünftige Mann, will ich ein Vermögen anhäufen! Eine Million Pesos würde ausreichen.";
			link.l1.go  = "Finish_2_1";
			link.l2 = "Ich beabsichtige, Respekt zu verdienen - die Art, die l'Olonnais hatte, nachdem er Maracaibo geplündert hatte.";
			link.l2.go  = "Finish_2_2";
			link.l3 = "Abenteuer! Ich sehne mich danach, exotische Orte zu erkunden und neugierige Charaktere zu treffen.";
			link.l3.go  = "Finish_2_3";
			link.l4 = "Ich habe immer von der romantischen Anziehungskraft geträumt, ein Schatzjäger zu sein!";
			link.l4.go  = "Finish_2_4";
			link.l5 = "Spar dir deinen Rat, Alonso. Warum sollte ich mich beschränken? Ich weiß, was ich will, und ich will alles!";
			link.l5.go  = "Finish_2_5";
		break;
		
		case "Finish_2_1":
			pchar.questTemp.SanBoxTarget = 1;
			dialog.text = "Das ist ein ganzes Vorhaben, Kapitän. Der schnellste Weg besteht darin, Handelsschiffe zu überfallen und sich am Schmuggel zu beteiligen. Sie könnten sich auch für ehrlichen Handel entscheiden, aber das wird etwas mehr Zeit in Anspruch nehmen. Sie müssen sich jedoch nicht beschränken - nehmen Sie jeden Job an und stürzen Sie sich in jedes Unheil, das Sie finden können. So wird man reich. Ich werde die Besatzung informieren, Kapitän. Möge uns allen das Glück hold sein!";
			link.l1 = "Spiel starten";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_2":
			pchar.questTemp.SanBoxTarget = 2;
			dialog.text = "Aber wissen Sie, wie l'Olonnais sein Ende fand? Nun, ich werde Sie nicht beurteilen, Kapitän. Unschuldiges Blut zu vergießen kann lukrativ sein, aber seien Sie auf die Konsequenzen vorbereitet. Sie werden ein formidables Schiff brauchen, vielleicht sogar eine Staffel, um die Festung zu erobern und einen Stützpunkt zu errichten. Alternativ könnten Sie die Stadt über Land einnehmen - vierhundert Mann sollten ausreichen, aber seien Sie versichert, eine ununterdrückte Garnison wird Sie schnell zurück in den Dschungel kämpfen. Ich werde Ihre Wahl der Mannschaft mitteilen, Kapitän. Möge uns allen das Glück hold sein!";
			link.l1 = "Spiel starten";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_3":
			pchar.questTemp.SanBoxTarget = 3;
			dialog.text = "Wir haben beides im Überfluss, Kapitän! Besuchen Sie die Städte, mischen Sie sich unter die Einheimischen, und Abenteuer werden Sie suchen. Denken Sie nur daran, dass ernsthafte Leute nur Ihre Hilfe suchen werden, nachdem Sie Ihren Mut bewiesen und einen Ruf aufgebaut haben. Das wird der Crew gefallen. Möge das Glück uns allen hold sein!";
			link.l1 = "Spiel starten";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_4":
			pchar.questTemp.SanBoxTarget = 4;
			dialog.text = "Es gibt nicht viel Romantik in diesem Handwerk, Kapitän. Es ist eine langwierige, aber profitable Beschäftigung, besonders wenn das Glück auf Ihrer Seite ist. Suchen Sie nach Schatzkarten bei Wirtshausverkäufern und halten Sie die Augen offen - Sie werden auf viele rivalisierende Jäger stoßen, die auf Ihre Kosten reich werden wollen. Darüber hinaus erfordern die wertvollsten Schätze oft das Zusammensetzen der Hälfte einer Karte aus einfacheren Funden, also nur zu! Möge das Glück uns allen hold sein!";
			link.l1 = "Spiel starten";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_5":
			pchar.questTemp.SanBoxTarget = 5;
			dialog.text = "Dann verstehen Sie, was es braucht, um eine Karibische Legende zu werden, Kapitän. Die Mannschaft glaubt an Sie und erwartet Ihre Erfolge mit Spannung. Moge das Glück uns allen hold sein!";
			link.l1 = "Spiel starten";
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
				dialog.text = "Sie sind endlich zurück, Kapitän! Gott sei Dank, wir haben fast alle Hoffnung verloren.";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - überspringen und das Spiel starten";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Alonso? Was zum Teufel ist passiert? Und warum habe ich solch einen schrecklichen Kopfschmerz?";
				link.l1.go = "Node_1_Jess";
			}
			else
			{
				dialog.text = "Nun, Kapitän, jetzt sehen Sie wieder aus wie Sie selbst. Wie fühlen Sie sich?";
				//link.l2 = "BetaTest - Starte den Test des Longway-Quests";
				//link.l2.go = "PZ_Test_Start_1";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - überspringen und das Spiel starten";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Hm... und wie war ich vorher?";
				link.l1.go = "Node_1";
			}
			locCameraFromToPos(-2.04, 4.95, 13.26, true, -0.82, 2.52, 7.87);
		break;
		
		case "PZ_Test_Start_1":
			dialog.text = "Wo fangen wir an?";
			link.l0 = "Episode 0. PROLOG. (von Anfang an)";
			link.l0.go  = "PZ_Test_Start_S_samogo_nachala";
			link.l1 = "Episode 1. TREU DEM EID.";
			link.l1.go  = "PZ_Test_Start_BasTer";
			link.l2 = "Folge 2-3. GESCHICHTSSEITEN.";
			link.l2.go  = "PZ_Test_Start_Formosa";
			link.l4 = "Episode 4. TRÜGERISCHER STERN.";
			link.l4.go  = "PZ_Test_Start_Etap4";
			link.l51 = "Folge 5-6. FALLENDER STERN. (Mit Helen)";
			link.l51.go  = "PZ_Test_Start_Etap5_Helena";
			link.l52 = "Folge 5-6. FALLENDER STERN. (Mit Mary)";
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
			dialog.text = "Wie diese rot-häutigen Atheisten, du hast sogar in ihrer Sprache gesprochen.";
			link.l1 = "Verdammt! Alonso, wovon zum Teufel redest du?!";
			link.l1.go  = "Node_2";
		break;
		
		case "Node_1_Jess":
			dialog.text = "Du erinnerst dich nicht daran, oder? Sicher, jemand anderes würde an einer Prellung wie dieser sterben oder den Rest seines Lebens lächelnd seine Hosen verschmutzen, aber es scheint, dass du ein harter Bursche bist. Aber du bist schwächer und es ist ein Problem für dich, auf den Beinen zu bleiben. Wir versuchen seit fast einem halben Jahr, dich zu heilen.";
			link.l1 = "Erzähl mir von dieser Prellung, ich erinnere mich an nichts.";
			link.l1.go  = "Node_2_Jess";
		break;
		
		case "Node_2":
			dialog.text = "Mach dir keine Sorgen, du musst dir keine Sorgen machen. Atme die frische Luft ein und schaue auf das Meer, dann wird es deinem Kopf besser gehen. Der Arzt meinte, dass du dich an nichts erinnern wirst, wenn du wieder zu dir kommst. Versuche also nicht, dich zu erinnern, das brauchst du nicht.";
			link.l1 = "Ich bin neugierig auf meine andere Option.";
			link.l1.go  = "Node_3";
		break;
		
		case "Node_2_Jess":
			dialog.text = "Die Maske ...";
			link.l1 = "Verdammt! Die Maske hat versucht, mich zu töten... Niemandem kann man trauen... Und was ist mit Lawrence? Lebt er noch?";
			link.l1.go  = "Node_3_Jess";
		break;
		
		case "Node_3":
			dialog.text = "Der Doktor sagte, es wäre sicherlich ein Irrenhaus. Er sprach von einer gespaltenen Persönlichkeit. Und Hopkins und ich haben hier keine andere Persönlichkeit gesehen als dich ...";
			link.l1 = "Unsinn! Ist mir das wirklich passiert?";
			link.l1.go  = "Node_4";
		break;
		
		case "Node_3_Jess":
			dialog.text = "Nein, Gott sei Dank. Oh, es tut mir leid... Er wurde auf Befehl der Maske gehängt. Und die Maske wurde vom Hai zerschnitten, so sagt man. Ich denke, sie haben es alle verdient, sie waren beide Bastarde. Diese Schurken waren zu große Probleme für uns.";
			link.l1 = "Redet nicht schlecht über die Toten... Wir können die Vergangenheit nicht ändern. Gott wird ihr Richter sein... Danke, Kumpels, dass ihr mich gerettet habt, das werde ich nicht vergessen.";
			link.l1.go  = "Node_4_Jess";
		break;
		
		case "Node_4":
			dialog.text = "Ich schwöre es dir. Wir hatten auch Angst, wir hätten keine Ahnung, was wir tun sollten, falls du tot wärst. Und was haben diese rotärschigen Bettler dir zu trinken gegeben! Nun, Gott sei Dank, geht es dir jetzt gut. Wie fühlst du dich?";
			//link.l1 = "Zum Trinken, sagst du... sieht bekannt aus, ich erinnere mich an nichts... Lass mich meine Gedanken sammeln.";
			//link.l1.go  = "ChangePIRATES";
			link.l2 = "Mir geht es gut. Ich fühle mich nur schwindelig, es ist wie betrunken zu sein...";
			link.l2.go  = "Node_5";
		break;
		
		case "Node_4_Jess":
			dialog.text = "...";
			//link.l1 = "Hm... gib mir eine Minute, ich muss meine Gedanken sammeln.";
			//link.l1.go  = "ChangePIRATES_Jess";
			link.l2 = "Fühle mich jetzt gut. Danke für deine Sorgen, Alonso.";
			link.l2.go  = "Node_5_Jess";
		break;
		
		case "Node_5":
			dialog.text = "Alkohol ist jetzt für dich verboten. Wir wollen deine gespaltene Persönlichkeit nicht zurück. Es wäre gut, ein bisschen Fechten zu üben. Ich wette, du hast vergessen, wie man mit einer Klinge umgeht.";
			link.l1 = "Du liest meine Gedanken. Nun, lass es uns versuchen, ich fühle mich so stark wie ein Bär.";
			link.l1.go  = "Teach_1";
			link.l2 = "Mach dir keine Sorgen, meine Hände sind viel besser im Vergleich zu meinem Kopf. Ich sollte besser zum Hafen gehen, ich bin zu wild geworden.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Node_5_Jess":
			dialog.text = "Siehst du, ich wusste, dass alles gut werden würde... Aber eine Kopfwunde ist kein Scherz, es wird Zeit brauchen, um deine Fähigkeiten wiederherzustellen. Möchtest du nicht etwas Fechten üben?";
			link.l1 = "Gute Idee. Lass mich meine Fähigkeiten testen.";
			link.l1.go  = "Teach_1_Jess";
			link.l2 = "Nein, ich will nicht. Ich bin zuversichtlich in meinen Fähigkeiten.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Finish_1":
			if (pchar.name == "Jessica")
			{
				dialog.text = "Wir sind jetzt im Hafen "+XI_ConvertString("Kolonie"+pchar.HeroParam.ToCityId+"Gen")+". Wir müssen irgendwie ein neues Leben beginnen, ohne all diese Masken und Beltropes, mögen sie alle in der Hölle schmoren... Und wir werden Sie nicht enttäuschen, Kapitän. Wir bleiben bis zum Ende bei Ihnen.";
				link.l1 = "Nun, ich schätze, ich habe Glück, am Leben zu sein! Ich werde euch nicht im Stich lassen noch werde ich euch enttäuschen. Das wäre alles, ich muss landen.";
				link.l1.go  = "Finish_2";
				link.l2 = "Einen Bastard weniger, einen Bastard mehr, es ist wie es ist, Alonso. Gibst du mir ein paar Ratschläge, bevor ich an Land gehe?";
				link.l2.go  = "Advice_1";
			}
			else
			{
				dialog.text = "Wir sind jetzt im Hafen der Siedlung "+XI_ConvertString("Kolonie"+pchar.HeroParam.ToCityId+"Gen")+", mach es dir bequem, aber komm zurück. Wir haben bereits den eigentlichen Fall verpasst - wir mussten das alte Schiff verkaufen, aber du wirst auf diesem nicht viel bekommen. Also, wir wurden durch die Vorfreude auf deine Genesung unterbrochen. Und die Jungs glauben immer noch an dich, sonst wären sie schon vor langer Zeit geflohen...";
				link.l1 = "Prächtig. Gut, ich gehe an Land... Keine Sorge, ich werde mich nicht verlaufen.";
				link.l1.go  = "Finish_2";
				link.l2 = "Wenn Sie denken, dass ich nicht bereit bin?";
				link.l2.go  = "Advice_1";
			}
		break;
		
		case "Advice_1":
			dialog.text = "Nun, Kapitän... Wir müssen das Schiff reparieren, mehr Männer anheuern und Vorräte kaufen. Und lasst uns einige Abenteuer finden! Es wäre natürlich schön, einen Kaperbrief zu bekommen, falls wir die hohe See überfallen wollen. Es wird uns alle Rechte dazu gewähren und wir können unseren Familien sagen, dass unser Job völlig legal ist. Und Sie werden in der Lage sein, sich einen Namen zu machen ...";
			link.l1 = "Was sollte ich sonst noch wissen?";
			link.l1.go  = "Advice_2";
			link.l2 = "Prächtig. Gut, ich gehe an Land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_2":
			dialog.text = "Sie müssen die aktuellen Preise für Waren in den Geschäften des Archipels kennen, um mit Gewinn handeln zu können. Besuchen Sie persönlich Geschäfte, fragen Sie Händler oder hören Sie Gerüchte.";
			link.l1 = "Mach weiter.";
			link.l1.go  = "Advice_3";
			link.l2 = "Prächtig. Gut, ich gehe an Land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_3":
			dialog.text = "Kanonen können beschädigt werden und Sie müssen sie ersetzen. Sie können auch einige von ihnen entfernen, um Platz für die Waren zu sparen.";
			link.l1 = "Mach weiter.";
			link.l1.go  = "Advice_4";
			link.l2 = "Prächtig. Gut, ich gehe an Land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_4":
			dialog.text = "Du musst etwas wissen, falls wir Freibeuter werden wollen... Schiffseigner kaufen eroberte Schiffe zu sehr niedrigen Preisen, aber du kannst Schiffe mit großem Gewinn weiterverkaufen.";
			link.l1 = "Geh weiter.";
			link.l1.go  = "Advice_5";
			link.l2 = "Prächtig. Gut, ich gehe an Land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_5":
			dialog.text = "Verderben Sie nicht Ihre Beziehungen mit den Schmugglern, sie können Ihnen auch unter Lebensgefahr ein gutes Einkommen verschaffen.";
			link.l1 = "Mach weiter.";
			link.l1.go  = "Advice_6";
			link.l2 = "Herrlich. Gut, ich gehe an Land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_6":
			dialog.text = "Stellt einige Offiziere ein, wir haben im Moment keine. Wenn deine Autorität gering ist, wirst du nicht viele Offiziere einstellen können. In diesem Fall solltest du Leute finden, die in der Lage sind, zwei oder drei Positionen gleichzeitig zu besetzen. Nur drei Besserwisser reichen aus, um alle Positionen auf unserem Schiff zu besetzen.";
			link.l1 = "Weiter.";
			link.l1.go  = "Advice_7";
			link.l2 = "Prächtig. Gut, ich gehe an Land...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = "Diebstahl ist kein guter Handel, aber manchmal musst du wirklich eine Truhe in jemandes Haus, Bank oder Laden plündern. Versuche zu warten, bis der Meister sich von dir abwendet und plündere dann erst eine Truhe. Und denke daran, dass du Ärger bekommst, wenn dich jemand bemerkt. Sei also versuche, flinker zu sein!";
			link.l1 = "Geh weiter.";
			link.l1.go  = "Advice_8";
			link.l2 = "Prächtig. Gut, ich gehe an Land...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = "Vielleicht wirst du eines Tages in die feindliche Stadt gelangen müssen. Merke dir gut, was ich dir jetzt sage! Nachts sind keine Soldaten an den Toren oder im Hafen. Also ist es besser, du betrittst die feindliche Stadt nachts und versuchst, Patrouillen zu vermeiden. Soldaten haben keine Augen im Nacken und sehen nur, was vor ihnen ist. Schleiche dich zur Taverne und warte dort, bis der Morgen anbricht, und dann erledige dein Geschäft. Aber halte dich trotzdem von den Soldaten fern.";
			link.l1 = "Mach weiter.";
			link.l1.go  = "Advice_9";
			link.l2 = "Prächtig. Gut, ich gehe an Land...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = "Sie können auch die feindliche Flagge hissen, wenn Sie sie haben, und auf Ihr Glück und Tarnung hoffen. Der zuverlässigste Weg ist der Kauf einer Lizenz der Handelsgesellschaft und niemand wird Sie aufhalten. Vergessen Sie nur nicht, die richtige Flagge zu hissen, es wäre albern, eine Lizenz zu zeigen, während Ihre Flagge in einer spanischen Festung Englisch ist.";
			link.l1 = "Mach weiter.";
			link.l1.go  = "Advice_10";
			link.l2 = "Herrlich. Gut, ich gehe an Land...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = "Wisse, dass Gefängnisse in fast jedem kolonialen Hafen zu finden sind.";
			link.l1 = "Danke. Ich muss jetzt landen.";
			link.l1.go  = "Finish_2";
		break;
		/////   фехт 
		case "Teach_1":
			dialog.text = "Nun, dann lass uns beginnen. Du warst immer gut darin, aber ich werde dich erinnern. Es gibt drei Angriffsbewegungen - normaler Schlag, schwerer Schlag und durchdringender Schlag. Es gibt auch einen schützenden Gruppenangriff. Und natürlich eine Pistole, nur um deinen Gegner aus der Ferne zu begrüßen.";
			link.l1 = "Gut, gut, lass uns gleich zur Sache kommen.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_1_Jess":
			dialog.text = "Nun, dann lasst uns anfangen. Du warst immer gut darin, aber ich werde dich erinnern. Es gibt drei Angriffsbewegungen - normaler Schlag, schwerer Schlag und durchdringender Schlag. Es gibt auch einen schützenden Gruppenangriff. Und natürlich eine Pistole, nur um deinen Gegner aus der Ferne zu begrüßen.";
			link.l1 = "Mach weiter.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_2":
			dialog.text = "...";
			link.l1 = "Sehr gut... Was als nächstes?";
			link.l1.go  = "Teach_3";
			link.l2 = "Was ist die Energie?";
			link.l2.go  = "Teach_2_1";
		break;
		
		case "Teach_2_1":
			dialog.text = "Energie ist der Indikator für deine Ausdauer im Kampf. Alle Angriffsbewegungen erfordern etwas Energie. Du wirst während des Kampfes müde und manchmal musst du dich etwas ausruhen, um deine Ausdauer wiederherzustellen."+"Das Maximum Ihrer Energie hängt vom aktuellen Wert Ihrer Reaktion ab.";
			link.l1 = "Mach weiter.";
			link.l1.go  = "Teach_3";
		break;
		
		case "Teach_3":
			dialog.text = "Vermeide den Kampf mit den zahlreichen Feinden oder du wirst in Sekunden tot sein. Es ist möglich, gegen zwei von ihnen zu kämpfen, aber es ist nicht so einfach, sich mit drei oder mehr Feinden gleichzeitig auseinanderzusetzen. Beobachte ihre Energie, wenn sie niedrig ist, werden sie anfangen zu parieren oder zu fälschen. Sei vorsichtig oder dein Kopf wird bald abgeschnitten sein.";
			link.l1 = "Geh weiter.";
			link.l1.go  = "Teach_4";
		break;
		
		case "Teach_4":
			dialog.text = "Wenn Sie Ihren Feind täuschen, wird er besonders Schaden nehmen, wenn Sie mit einer leichten und kleinen Waffe kämpfen. Und wenn es Ihnen gelingt, seine Angriffe zu parieren, wird er seine Energie und seinen Rhythmus verlieren, was Ihnen erlaubt, noch härter zuzuschlagen.";
			link.l1 = "Mach weiter.";
			link.l1.go  = "Teach_5";
		break;
		
		case "Teach_5":
			dialog.text = "Alle Waffen sind unterschiedlich. Es gibt leichte, mittlere und schwere Typen. Das Gewicht bestimmt den Energieverlust. Mit einem kleinen Dolch kannst du lange kämpfen, aber eine schwere Axt hilft dir, deinen Gegner sofort zu töten, während ein Säbel dir im Kampf gegen viele Feinde gleichzeitig helfen kann.";
			link.l1 = "Mach weiter.";
			link.l1.go  = "Teach_6";
		break;
		
		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			Tut_RestoreState();
			dialog.text = "Lass uns ein bisschen üben? Ich biete dir ein Aufwärmen an. Wir werden wirklich kämpfen, aber nicht bis zum Tod. Du kannst dich mit Elixiere, Tränke oder Rum heilen, aber verschwende sie jetzt nicht, es ist nur ein Training.";
			link.l1 = "Lass uns gehen und erwarte keine Gnade!";
			link.l1.go  = "Teach_battle_1";
			link.l2 = "Nein, danke, ich habe es schon.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = LinkRandPhrase("Nun... Du bist wirklich schwach jetzt. Sei aufmerksam, blockiere und pariere mehr. Achte auf die schweren Angriffe, deine Blocks werden dich nicht davor retten, benutze Feinte, pariere oder versuche zurückzutreten.","Lassen Sie die schweren Angriffe nicht zur Geltung kommen, fangen Sie die Schläge des Feindes mit Ihren Finten ab oder versuchen Sie, sie zu parieren. Seien Sie vorsichtig und achten Sie auf Finten, sonst werden Ihre Angriffe abgefangen und gegen Sie gewendet.","Laufe oder springe weg, wenn deine Energie niedrig ist. Du kannst versuchen, deinen Gegner zu täuschen. Wisse, dass es nicht einfach ist, den Schlag des Feindes zu parieren, aber du kannst ihn täuschen. Wenn du Erfolg hast, wirst du seinem Schlag ausweichen und ihn zurückschlagen.")+"Lass es uns noch einmal versuchen?";
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = "Sicher!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2 = "Nein, ich habe genug. Ich habe es verstanden.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = "Gut. Gut gemacht! Ich habe nicht unfair gekämpft, aber deine Gegner könnten ihre eigenen Elixiere haben und sie werden nicht so leicht besiegt."+"Nun, machen wir es ein bisschen schwieriger. Wie wäre es, wenn du gegen zwei Gegner auf einmal kämpfst?";
			link.l1 = "Lass es uns versuchen. Hey, Hopkins! Nimm dein Schwert und komm an Bord!";
			link.l1.go  = "Teach_battle_1";
			link.l2 = "Nein danke, ich habe genug geübt.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			if (pchar.name == "Jessica")
			{
				dialog.text = "Gut gemacht, Kapitän! Beltropes Lektionen waren nicht umsonst, er war ein guter Lehrer. Nun, der letzte Ratschlag. Das Kämpfen mit einer Art von Waffe wird Ihre Fähigkeiten stark verbessern. Wenn Sie Ihre Fähigkeiten mit jeder Art von Klingen wiederherstellen möchten, wechseln Sie sie öfter.";
			}
			else
			{
				dialog.text = "Ja, deine Hände sind in Ordnung, wir haben richtig gehandelt, unsere Klingen zu verbergen. Nun, der letzte Rat. Mit einer Art von Waffe zu kämpfen, wird deine Fähigkeiten stark verbessern. Wenn du deine Fähigkeiten mit jeder Art von Klingen wiederherstellen willst, dann wechsle sie öfter.";
			}
			link.l1 = "Danke!";
			link.l1.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = "Nun, nicht schlecht. Du hast einen Gegner erwischt, aber es waren zwei von ihnen. Es braucht etwas Übung. Feinde können zu dritt oder viert gleichzeitig angreifen. Lass es uns noch einmal versuchen?";
   			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = "Sicher!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2 = "Nein, ich habe genug. Ich habe es verstanden.";
			link.l2.go  = "Finish_1";
		break;
	}
}
