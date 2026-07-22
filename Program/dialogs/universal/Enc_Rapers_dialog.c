void ProcessDialogEvent()
{
	object dlgContext;
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = DLG_Convert("Enc_Rapers_dialog_First_time_text_1", "Dialogs\Enc_Rapers_dialog.txt");
				link.l1 = DLG_Convert("Enc_Rapers_dialog_First_time_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
				link.l1.go = "Node_Fight";
				link.l2 = DLG_Convert("Enc_Rapers_dialog_First_time_l2_1", "Dialogs\Enc_Rapers_dialog.txt");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(int(pchar.rank) < 10)
				{
					dialog.text = DLG_Convert("Enc_Rapers_dialog_First_time_text_2", "Dialogs\Enc_Rapers_dialog.txt");
					link.l1 = DLG_Convert("Enc_Rapers_dialog_First_time_l1_2", "Dialogs\Enc_Rapers_dialog.txt");
					link.l1.go = "Node_Fight";
					link.l2 = DLG_Convert("Enc_Rapers_dialog_First_time_l2_2", "Dialogs\Enc_Rapers_dialog.txt");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = DLG_Convert("Enc_Rapers_dialog_First_time_text_3", "Dialogs\Enc_Rapers_dialog.txt");
					link.l1 = DLG_Convert("Enc_Rapers_dialog_First_time_l1_3", "Dialogs\Enc_Rapers_dialog.txt");
					link.l1.go = "Node_3";
					link.l2 = DLG_Convert("Enc_Rapers_dialog_First_time_l2_3", "Dialogs\Enc_Rapers_dialog.txt");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(int(pchar.rank) < 20)
				{	
					dialog.text = DLG_Convert("Enc_Rapers_dialog_First_time_text_4", "Dialogs\Enc_Rapers_dialog.txt");
					link.l1 = DLG_Convert("Enc_Rapers_dialog_First_time_l1_4", "Dialogs\Enc_Rapers_dialog.txt");
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = DLG_Convert("Enc_Rapers_dialog_First_time_text_5", "Dialogs\Enc_Rapers_dialog.txt");
					link.l1 = DLG_Convert("Enc_Rapers_dialog_First_time_l1_5", "Dialogs\Enc_Rapers_dialog.txt");
					link.l1.go = "Node_3";
					link.l2 = DLG_Convert("Enc_Rapers_dialog_First_time_l2_4", "Dialogs\Enc_Rapers_dialog.txt");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_Fight_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_Fight_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * int(pchar.rank);
			dlgContext.price = int(pchar.GenQuest.EncGirl.price);
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_3_text_1", "Dialogs\Enc_Rapers_dialog.txt", &dlgContext);
			if(int(pchar.money) >= int(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_3_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
				link.l1.go = "Node_4";
			}	
			link.l2 = DLG_Convert("Enc_Rapers_dialog_Node_3_l2_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ её выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -int(int(pchar.GenQuest.EncGirl.price)));
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_5_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_5_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "Exit_NoFight";
			link.l2 = DLG_Convert("Enc_Rapers_dialog_Node_5_l2_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l2.go = "Node_6";
			link.l3 = DLG_Convert("Enc_Rapers_dialog_Node_5_l3_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_6_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_6_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = DLG_Convert("Enc_Rapers_dialog_Node_7_fatherNom_1", "Dialogs\Enc_Rapers_dialog.txt");
					pchar.GenQuest.EncGirl.FatherGen = DLG_Convert("Enc_Rapers_dialog_Node_7_fatherGen_1", "Dialogs\Enc_Rapers_dialog.txt");
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = DLG_Convert("Enc_Rapers_dialog_Node_7_fatherNom_2", "Dialogs\Enc_Rapers_dialog.txt");
					pchar.GenQuest.EncGirl.FatherGen = DLG_Convert("Enc_Rapers_dialog_Node_7_fatherGen_2", "Dialogs\Enc_Rapers_dialog.txt");
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = DLG_Convert("Enc_Rapers_dialog_Node_7_fatherNom_3", "Dialogs\Enc_Rapers_dialog.txt");
					pchar.GenQuest.EncGirl.FatherGen = DLG_Convert("Enc_Rapers_dialog_Node_7_fatherGen_3", "Dialogs\Enc_Rapers_dialog.txt");
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = DLG_Convert("Enc_Rapers_dialog_Node_7_fatherNom_4", "Dialogs\Enc_Rapers_dialog.txt");
					pchar.GenQuest.EncGirl.FatherGen = DLG_Convert("Enc_Rapers_dialog_Node_7_fatherGen_4", "Dialogs\Enc_Rapers_dialog.txt");
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dlgContext.fatherName = pchar.GenQuest.EncGirl.FatherNom;
			dlgContext.cityName = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_7_text_1", "Dialogs\Enc_Rapers_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_7_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_8_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_8_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = DLG_Convert("Enc_Rapers_dialog_Node_9_sTemp_1", "Dialogs\Enc_Rapers_dialog.txt");
				break;
				case 1:
					sTemp = DLG_Convert("Enc_Rapers_dialog_Node_9_sTemp_2", "Dialogs\Enc_Rapers_dialog.txt");
				break;
				case 2:
					sTemp = DLG_Convert("Enc_Rapers_dialog_Node_9_sTemp_3", "Dialogs\Enc_Rapers_dialog.txt");
				break;
				case 3:
					sTemp = DLG_Convert("Enc_Rapers_dialog_Node_9_sTemp_4", "Dialogs\Enc_Rapers_dialog.txt");
				break;
				case 4:
					sTemp = DLG_Convert("Enc_Rapers_dialog_Node_9_sTemp_5", "Dialogs\Enc_Rapers_dialog.txt");
				break;
			}
			dlgContext.pirateName = GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_GEN);
			dlgContext.pirateName2 = GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM);
			dlgContext.tempText = sTemp;
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_9_text_1", "Dialogs\Enc_Rapers_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_9_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_10_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_10_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_11_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_11_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar1_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar1_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = int(int(pchar.money)/5) + 5000;
			if(int(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(int(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dlgContext.moneyAmount = int(pchar.GenQuest.EncGirl.BerglarSum);
				dialog.text = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar2_text_1", "Dialogs\Enc_Rapers_dialog.txt", &dlgContext);
				if(int(pchar.money) >= int(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar2_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar2_l2_1", "Dialogs\Enc_Rapers_dialog.txt");
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar2_text_2", "Dialogs\Enc_Rapers_dialog.txt");
				link.l1 = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar2_l1_2", "Dialogs\Enc_Rapers_dialog.txt");
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar2_l2_2", "Dialogs\Enc_Rapers_dialog.txt");
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -int(int(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar3_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar3_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar3_1_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar3_1_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar4_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1 = DLG_Convert("Enc_Rapers_dialog_EncGirl_Berglar4_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = DLG_Convert("Enc_Rapers_dialog_Node_2_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			Link.l1 = DLG_Convert("Enc_Rapers_dialog_Node_2_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = DLG_Convert("Enc_Rapers_dialog_OnceAgain_text_1", "Dialogs\Enc_Rapers_dialog.txt");
			Link.l1 = DLG_Convert("Enc_Rapers_dialog_OnceAgain_l1_1", "Dialogs\Enc_Rapers_dialog.txt");
			Link.l1.go = "Exit_NoFight";
			Link.l2 = DLG_Convert("Enc_Rapers_dialog_OnceAgain_l2_1", "Dialogs\Enc_Rapers_dialog.txt");
			Link.l2.go = "Node_2";
		break;				
	}
}
