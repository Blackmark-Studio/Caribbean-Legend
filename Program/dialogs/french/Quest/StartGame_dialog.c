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
			dialog.text = "Capitaine, une dernière question. Quel message dois-je transmettre à l'équipage ?";
			link.l1 = "Que voulez-vous dire ?";
			link.l1.go  = "Finish_2_0";
		break;
		
		case "Finish_2_0":
			dialog.text = "Les gens veulent savoir à quoi s'attendre. On dirait que tu n'as pas encore pris ta décision.";
			link.l1 = "Quelles sont mes options ?";
			link.l1.go  = "Finish_2_0_1";
		break;
		
		case "Finish_2_0_1":
			dialog.text = "Eh bien, Cap, les Caraïbes sont un endroit unique. Vous pouvez vous lancer dans le commerce, piller, vous plonger dans des affaires louches ou partir à la chasse aux trésors - il y a d'innombrables chemins pour devenir une légende dans ces eaux. L'équipage et moi avons discuté et nous sommes prêts à soutenir quel que soit le choix que vous ferez.";
			link.l1 = "Dois-je en choisir un seul ?";
			link.l1.go  = "Finish_2_0_2";
		break;
		
		case "Finish_2_0_2":
			dialog.text = "Non, certainement pas, mais c'est une bonne idée de fixer nos priorités initiales.";
			link.l1 = "Comme tout homme sensé, je veux amasser une fortune ! Un million de pesos suffirait.";
			link.l1.go  = "Finish_2_1";
			link.l2 = "Je vise à gagner le respect - celui que l'Olonnais avait après avoir pillé Maracaibo.";
			link.l2.go  = "Finish_2_2";
			link.l3 = "Aventure ! Je brûle d'explorer des contrées exotiques et de rencontrer des personnages curieux.";
			link.l3.go  = "Finish_2_3";
			link.l4 = "J'ai toujours rêvé de l'attrait romantique d'être un chasseur de trésors !";
			link.l4.go  = "Finish_2_4";
			link.l5 = "Sauve tes conseils, Sandro. Pourquoi me limiter? Je sais ce que je veux, et je le veux tout!";
			link.l5.go  = "Finish_2_5";
		break;
		
		case "Finish_2_1":
			pchar.questTemp.SanBoxTarget = 1;
			dialog.text = "Voilà une sacrée ambition, Capitaine. Le moyen le plus rapide est d'attaquer les navires marchands et de se livrer à la contrebande. Vous pourriez aussi choisir le commerce honnête, mais cela prendra un peu plus de temps. Cependant, vous n'êtes pas obligé de vous limiter - acceptez n'importe quel travail et plongez-vous dans toutes les frasques possibles. C'est ainsi que vous ferez fortune. J'informerai l'équipage, Capitaine. Que la fortune nous soit favorable à tous !";
			link.l1 = "Démarrer le jeu";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_2":
			pchar.questTemp.SanBoxTarget = 2;
			dialog.text = "Mais savez-vous comment l'Olonnais a rencontré sa fin ? Eh bien, je ne vous jugerai pas, Capitaine. Répandre le sang des innocents peut être lucratif, mais préparez-vous aux conséquences. Vous aurez besoin d'un navire formidable, peut-être même d'une escadre, pour conquérir le fort et établir un point d'appui. Sinon, vous pourriez prendre la ville par terre - quatre cents hommes devraient suffire, mais soyez sûr qu'une garnison non réprimée vous repoussera rapidement dans la jungle. Je transmettrai votre choix à l'équipage, Capitaine. Que la fortune nous soit favorable à tous !";
			link.l1 = "Démarrer le jeu";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_3":
			pchar.questTemp.SanBoxTarget = 3;
			dialog.text = "Nous avons une abondance des deux, Capitaine ! Visitez les villes, mêlez-vous aux habitants, et les aventures viendront à vous. Rappelez-vous simplement que les gens sérieux ne chercheront votre aide que lorsque vous aurez prouvé votre valeur et bâti une réputation. L'équipage appréciera cela. Que la fortune nous soit favorable à tous !";
			link.l1 = "Lancer le jeu";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_4":
			pchar.questTemp.SanBoxTarget = 4;
			dialog.text = "Il n'y a pas beaucoup de romantisme dans ce métier, Capitaine. C'est une quête longue mais lucrative, surtout si la chance est de votre côté. Cherchez des cartes au trésor chez les vendeurs de tavernes et restez vigilant - vous rencontrerez quantité de chasseurs rivaux cherchant à s'enrichir à vos dépens. De plus, les trésors les plus précieux nécessitent souvent d'assembler la moitié d'une carte à partir de trouvailles plus simples, alors allez-y ! Que la fortune nous favorise tous !";
			link.l1 = "Lancer le jeu";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_5":
			pchar.questTemp.SanBoxTarget = 5;
			dialog.text = "Alors vous comprenez ce qu'il faut pour devenir une légende des Caraïbes, Capitaine. L'équipage croit en vous et attend impatiemment vos exploits. Que la fortune nous favorise tous !";
			link.l1 = "Lancer le jeu";
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
				dialog.text = "Tu es de retour, capitaine, enfin ! Dieu merci, nous avions presque perdu tout espoir.";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - passer et commencer le jeu";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Sandro ? Que diable s'est-il passé ? Et pourquoi ai-je un mal de tête aussi terrible ?";
				link.l1.go = "Node_1_Jess";
			}
			else
			{
				dialog.text = "Eh bien, capitaine, maintenant vous ressemblez à vous-même. Comment vous sentez-vous ?";
				//link.l2 = "BêtaTest - Commencer le test de la quête Longway";
				//link.l2.go = "PZ_Test_Start_1";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - passer et commencer le jeu";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Hum... et comment étais-je avant ?";
				link.l1.go = "Node_1";
			}
			locCameraFromToPos(-2.04, 4.95, 13.26, true, -0.82, 2.52, 7.87);
		break;
		
		case "PZ_Test_Start_1":
			dialog.text = "Où commençons-nous ?";
			link.l0 = "Épisode 0. PROLOGUE. (dès le début)";
			link.l0.go  = "PZ_Test_Start_S_samogo_nachala";
			link.l1 = "Épisode 1. FIDÈLE À SON SERMENT.";
			link.l1.go  = "PZ_Test_Start_BasTer";
			link.l2 = "Épisode 2-3. PAGES D'HISTOIRE.";
			link.l2.go  = "PZ_Test_Start_Formosa";
			link.l4 = "L'épisode 4. L'ÉTOILE TROMPEUSE.";
			link.l4.go  = "PZ_Test_Start_Etap4";
			link.l51 = "Épisode 5-6. ÉTOILE FILANTE. (Avec Hélène)";
			link.l51.go  = "PZ_Test_Start_Etap5_Helena";
			link.l52 = "Épisode 5-6. ÉTOILE FILANTE. (Avec Mary)";
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
			dialog.text = "Comme ces athées à la peau rouge, tu parlais même leur langue.";
			link.l1 = "Merde ! Sandro, de quoi diable parles-tu ?!";
			link.l1.go  = "Node_2";
		break;
		
		case "Node_1_Jess":
			dialog.text = "Tu ne te souviens pas de ça, n'est-ce pas ? Bien sûr, quelqu'un d'autre mourrait d'une contusion pareille ou sourirait et souillerait son pantalon pour le reste de sa vie, mais il semble que tu es coriace. Bien que tu sois plus faible et que c'est un problème pour toi de rester même debout. Cela fait presque un demi-an que nous essayons de te soigner.";
			link.l1 = "Parle-moi de cette contusion, je ne me souviens de rien.";
			link.l1.go  = "Node_2_Jess";
		break;
		
		case "Node_2":
			dialog.text = "Ne t'inquiète pas, il ne faut pas t'inquiéter. Respire l'air frais et regarde la mer, ta tête ira bien alors. Le docteur a dit que tu ne te souviendras de rien si tu reprends connaissance. Donc n'essaie pas de te souvenir, tu n'en as pas besoin.";
			link.l1 = "Je suis curieux de connaître mon autre option.";
			link.l1.go  = "Node_3";
		break;
		
		case "Node_2_Jess":
			dialog.text = "Le Masque ...";
			link.l1 = "Merde ! Le Masque a essayé de me tuer... On ne peut faire confiance à personne... Et Lawrence ? Est-il vivant ?";
			link.l1.go  = "Node_3_Jess";
		break;
		
		case "Node_3":
			dialog.text = "Le docteur a dit que ce serait sûrement un asile. La personnalité dédoublée, a-t-il dit. Et Hopkins et moi n'avons vu aucune autre personnalité ici que la vôtre ...";
			link.l1 = "Balivernes ! Cela m'est-il vraiment arrivé ?";
			link.l1.go  = "Node_4";
		break;
		
		case "Node_3_Jess":
			dialog.text = "Non, Dieu merci. Oh, je suis désolé... Il a été pendu sur ordre du Masque. Et le Masque a été coupé par le Requin, comme on dit. Je pense qu'ils l'ont tous mérité, c'étaient des salauds tous les deux. Ces vauriens étaient vraiment trop de soucis pour nous.";
			link.l1 = "Ne parle pas mal des morts... Nous ne pouvons pas changer le passé. Dieu sera leur juge... Merci, les amis, de m'avoir sauvé, je ne l'oublierai pas.";
			link.l1.go  = "Node_4_Jess";
		break;
		
		case "Node_4":
			dialog.text = "Je te le jure. Nous avions peur aussi, nous n'aurions aucune idée de quoi faire si tu étais mort. Et qu'est-ce que ces gueux au cul rouge t'ont donné à boire ! Eh bien, Dieu merci, tu vas bien maintenant. Comment te sens-tu ?";
			//link.l1 = "Boire, dis-tu... ça me dit quelque chose, mais je ne me souviens de rien... Laisse-moi rassembler mes pensées.";
			//link.l1.go  = "ChangePIRATES";
			link.l2 = "Je me sens bien. Ça me donne juste le vertige, c'est comme être ivre...";
			link.l2.go  = "Node_5";
		break;
		
		case "Node_4_Jess":
			dialog.text = "...";
			//link.l1 = "Hum... donne-moi une minute, il faut que je rassemble mes pensées.";
			//link.l1.go  = "ChangePIRATES_Jess";
			link.l2 = "Je me sens bien maintenant. Merci de t'inquiéter, Sandro.";
			link.l2.go  = "Node_5_Jess";
		break;
		
		case "Node_5":
			dialog.text = "L'alcool t'est désormais interdit. On ne veut pas que ta double personnalité fasse son retour. Ce serait bien de pratiquer un peu l'escrime. Je parie que tu as oublié comment manier une lame.";
			link.l1 = "Tu lis dans mes pensées. Eh bien, essayons, je me sens fort comme un ours.";
			link.l1.go  = "Teach_1";
			link.l2 = "Ne t'inquiète pas, mes mains sont bien meilleures comparées à ma tête. Je ferais mieux d'aller au port, je suis devenu trop déchaîné.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Node_5_Jess":
			dialog.text = "Voyez-vous, je savais que tout irait bien... Mais une blessure à la tête n'est pas une plaisanterie, il faudra du temps pour rétablir vos compétences. Ne voudriez-vous pas pratiquer un peu l'escrime ?";
			link.l1 = "Bonne idee. Laisse-moi tester mes competences.";
			link.l1.go  = "Teach_1_Jess";
			link.l2 = "Non, je ne veux pas. Je suis confiant en mes compétences.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Finish_1":
			if (pchar.name == "Jessica")
			{
				dialog.text = "Nous sommes maintenant au port "+XI_ConvertString("Colony"+pchar.HeroParam.ToCityId+"Gen")+"Nous devons d'une manière ou d'une autre commencer une nouvelle vie sans tous ces Masques et Beltropes, qu'ils pourrissent tous en enfer... Et nous ne vous laisserons pas tomber, capitaine. Nous resterons avec vous jusqu'à la fin.";
				link.l1 = "Eh bien, je suppose que j'ai de la chance d'être en vie ! Je ne vous laisserai pas tomber, ni ne décevrai aucun d'entre vous. Ce sera tout, j'ai besoin de débarquer.";
				link.l1.go  = "Finish_2";
				link.l2 = "Un salaud de moins, un salaud de plus, c'est comme ça, Sandro. Peux-tu me donner quelques conseils avant que je débarque ?";
				link.l2.go  = "Advice_1";
			}
			else
			{
				dialog.text = "Nous sommes maintenant dans le port de la colonie "+XI_ConvertString("Colony"+pchar.HeroParam.ToCityId+"Gen")+", mets-toi à l'aise, mais reviens. Nous avons déjà raté la véritable affaire - nous avons dû vendre le vieux navire, mais tu n'en tireras pas grand-chose. Donc, nous avons été interrompus par l'attente de ton rétablissement. Et les gars croient encore en toi, sinon ils auraient fui depuis longtemps...";
				link.l1 = "Splendide. Bien, je vais à terre... Ne t'inquiète pas, je ne me perdrai pas.";
				link.l1.go  = "Finish_2";
				link.l2 = "Si tu penses que je ne suis pas prêt ?";
				link.l2.go  = "Advice_1";
			}
		break;
		
		case "Advice_1":
			dialog.text = "Eh bien, capitaine... Nous devons réparer le navire, engager plus d'hommes et acheter des provisions. Et trouvons-nous quelques aventures ! Bien sûr, ce serait bien d'obtenir une lettre de marque au cas où nous déciderions de faire des raids en haute mer. Elle nous accordera tous les droits pour le faire et nous pourrons dire à nos familles que notre travail est entièrement légal. Et vous pourrez vous faire un nom...";
			link.l1 = "Que devrais-je savoir d'autre ?";
			link.l1.go  = "Advice_2";
			link.l2 = "Splendide. Très bien, je vais à terre...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_2":
			dialog.text = "Tu dois connaitre les prix actuels des marchandises dans les magasins de l'archipel pour commercer avec profit. Visite les magasins personnellement, demande aux marchands ou ramasse des commérages.";
			link.l1 = "Continuez.";
			link.l1.go  = "Advice_3";
			link.l2 = "Splendide. Bien, je vais à terre...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_3":
			dialog.text = "Les canons peuvent être endommagés et il faudra les remplacer. Vous pouvez aussi en retirer certains pour faire de la place pour les marchandises.";
			link.l1 = "Continuez.";
			link.l1.go  = "Advice_4";
			link.l2 = "Splendide. Bien, je vais à terre...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_4":
			dialog.text = "Tu dois savoir quelque chose si nous allons devenir corsaires... Les maitres de navires achètent des bateaux capturés à des prix très bas mais tu peux revendre les navires avec un grand profit.";
			link.l1 = "Continuez.";
			link.l1.go  = "Advice_5";
			link.l2 = "Splendide. Bien, je vais à terre...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_5":
			dialog.text = "Ne gâtez pas vos relations avec les contrebandiers, ils sont capables de vous procurer un bon revenu même au péril de votre vie.";
			link.l1 = "Continue.";
			link.l1.go  = "Advice_6";
			link.l2 = "Splendide. Bien, je vais à terre...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_6":
			dialog.text = "Loue des officiers, nous n'en avons pas pour le moment. Si ton autorité est basse, alors tu ne pourras pas recruter beaucoup d'officiers. Dans ce cas, il te faudra trouver des gens capables de travailler sur deux ou trois postes à la fois. Trois touche-à-tout suffisent pour occuper tous les postes sur notre navire.";
			link.l1 = "Continue.";
			link.l1.go  = "Advice_7";
			link.l2 = "Splendide. Bien, je vais à terre...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = "Le vol n'est pas une bonne affaire, mais parfois, il faut vraiment piller un coffre chez quelqu'un, à la banque ou dans un magasin. Essayez d'attendre que le maître vous tourne le dos avant de piller un coffre. Et souvenez-vous que vous aurez des ennuis si quelqu'un vous surprend. Alors, essayez d'être plus agile !";
			link.l1 = "Continue.";
			link.l1.go  = "Advice_8";
			link.l2 = "Splendide. Très bien, je vais à terre...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = "Peut-être, un jour tu auras besoin de t'introduire dans la ville ennemie. Souviens-toi bien de ce que je vais te dire maintenant ! Il n'y a pas de soldats aux portes ni dans le port la nuit. Alors il vaut mieux entrer dans la ville ennemie la nuit et simplement essayer d'éviter les patrouilles. Les soldats n'ont pas d'yeux dans le dos et ils ne voient que ce qui est devant eux. Faufiles-toi jusqu'à la taverne et attends là jusqu'au matin, puis fais tes affaires. Mais tiens-toi à l'écart des soldats quoi qu'il en soit.";
			link.l1 = "Continue.";
			link.l1.go  = "Advice_9";
			link.l2 = "Splendide. Bien, je vais à terre...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = "Vous pouvez également hisser le pavillon ennemi si vous l'avez, et compter sur votre chance et votre furtivité. Le moyen le plus fiable est d'acheter une patente de la compagnie commerciale et personne ne vous arrêtera. N'oubliez juste pas de hisser le bon pavillon, il serait idiot d'essayer de montrer une patente alors que votre pavillon est anglais dans un fort espagnol.";
			link.l1 = "Continue.";
			link.l1.go  = "Advice_10";
			link.l2 = "Splendide. Très bien, je vais à terre...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = "Sachez que des prisons peuvent être trouvées dans presque tous les ports coloniaux.";
			link.l1 = "Merci. Je dois accoster maintenant.";
			link.l1.go  = "Finish_2";
		break;
		/////   фехт 
		case "Teach_1":
			dialog.text = "Eh bien, commençons alors. Tu étais toujours bon dans ce domaine mais je vais te le rappeler. Il y a trois coups d'attaque - coup normal, frappe lourde et coup perçant. Il y a aussi une attaque de groupe protectrice. Et un pistolet, bien sûr, juste pour saluer ton adversaire de loin.";
			link.l1 = "D'accord, d'accord, allons droit au but.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_1_Jess":
			dialog.text = "Eh bien, commençons alors. Tu étais toujours bon dans ce domaine, mais je vais te rappeler. Il y a trois coups d'attaque - coup normal, frappe lourde et coup pénétrant. Il y a aussi une attaque de groupe défensive. Et un pistolet, bien sûr, juste pour saluer ton adversaire à distance.";
			link.l1 = "Continue.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_2":
			dialog.text = "... ";
			link.l1 = "Très bien... Suivant ?";
			link.l1.go  = "Teach_3";
			link.l2 = "Quelle est l'énergie ?";
			link.l2.go  = "Teach_2_1";
		break;
		
		case "Teach_2_1":
			dialog.text = "L'energie est l'indicateur de votre endurance au combat. Tous les mouvements d'attaque requierent de l'energie. Vous vous fatiguerez au cours du combat et parfois vous aurez besoin de repos pour restaurer votre endurance."+"La quantité maximale de votre énergie dépend de la valeur actuelle de votre réaction.";
			link.l1 = "Continue.";
			link.l1.go  = "Teach_3";
		break;
		
		case "Teach_3":
			dialog.text = "Evitez de combattre avec les nombreux ennemis ou vous serez mort en quelques secondes. Il est possible de se battre avec deux d'entre eux, mais il n'est pas si simple d'affronter trois ou plus d'ennemis à la fois. Surveillez leur énergie : quand elle sera basse, ils commenceront à parer ou à feindre. Soyez prudent ou votre tête sera bientôt tranchée.";
			link.l1 = "Allez-y.";
			link.l1.go  = "Teach_4";
		break;
		
		case "Teach_4":
			dialog.text = "Si vous feintez votre ennemi, il subira de lourds dommages, surtout si vous vous battez avec une arme légère et petite. Et si vous parvenez à parer ses attaques, il perdra son énergie et son rythme, vous permettant de le frapper encore plus fort.";
			link.l1 = "Continuez.";
			link.l1.go  = "Teach_5";
		break;
		
		case "Teach_5":
			dialog.text = "Tous les armes sont differentes. Il y a des types legeres, moyennes et lourdes. Le poids determine les pertes d'energie. Vous pouvez combattre longtemps avec un petit poignard, mais une lourde hache vous aidera a tuer instantanement votre adversaire, tandis qu'un sabre peut vous aider a combattre de nombreux ennemis a la fois.";
			link.l1 = "Continue.";
			link.l1.go  = "Teach_6";
		break;
		
		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			Tut_RestoreState();
			dialog.text = "Entraînons-nous un peu ? Je te propose un échauffement. Nous nous battrons pour de vrai mais pas à mort. Tu peux te soigner avec des élixirs, des potions ou du rhum, mais ne les gaspille pas maintenant, ce n'est qu'un entraînement.";
			link.l1 = "Allons-y et n'attendez pas de pitié !";
			link.l1.go  = "Teach_battle_1";
			link.l2 = "Non, merci, je l'ai déjà.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = LinkRandPhrase("Eh bien... Tu es vraiment faible maintenant. Sois attentif, bloque et pare davantage. Fais attention aux attaques lourdes, tes blocages ne te sauveront pas, utilise une feinte, pare ou essaie de reculer.","Naissez pas les attaques lourdes faire contact, attrapez les coups de l'ennemi avec vos feintes ou essayez de les parer. Soyez prudent et surveillez les feintes, ou vos attaques seront attrapées et retournées contre vous.","Fuis ou saute loin si ton énergie est basse. Tu peux essayer de feinter ton adversaire. Sache que ce n'est pas facile de feinter le coup de l'ennemi mais tu peux le berner. Si tu réussis, tu éviteras son coup et tu le frapperas en retour.")+"Recommençons ?";
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = "D'accord !";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2 = "Non, j'en ai assez. J'ai compris.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = "Bien. Bien joué ! Je ne me battais pas de manière déloyale, mais tes adversaires pourraient avoir leurs propres élixirs et ils ne se laisseront pas vaincre si facilement. "+"Eh bien, rendons cela un peu plus difficile. Que diriez-vous de vous battre contre deux adversaires à la fois ?";
			link.l1 = "Essayons. Hé, Hopkins ! Prends ta lame et monte à bord !";
			link.l1.go  = "Teach_battle_1";
			link.l2 = "Non merci, j'ai eu assez de pratique.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			if (pchar.name == "Jessica")
			{
				dialog.text = "Bien joué, capitaine ! Les leçons de Beltrope n'ont pas été perdues, c'était un bon professeur. Maintenant, le dernier conseil. Se battre avec un seul type d'arme augmentera grandement votre compétence. Si vous voulez restaurer vos compétences avec chaque type de lame, alors changez-les plus souvent.";
			}
			else
			{
				dialog.text = "Oui, tes mains vont bien, nous avions raison de cacher nos lames. Maintenant, le dernier conseil. Combattre avec un seul type d'arme augmentera grandement ton habileté. Si tu veux restaurer tes compétences avec chaque type de lames, alors change-les plus souvent.";
			}
			link.l1 = "Merci !";
			link.l1.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = "Eh bien, pas mal. Vous avez eu un adversaire mais ils étaient deux. Cela nécessite un peu de pratique. Les ennemis peuvent attaquer par trois ou quatre à la fois. On réessaie ?";
   			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = "Bien sûr !";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2 = "Non, j'en ai assez. Je l'ai compris.";
			link.l2.go  = "Finish_1";
		break;
	}
}
