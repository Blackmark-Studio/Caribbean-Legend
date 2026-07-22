void ProcessDialogEvent()
{
	object dlgContext;
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Begin_1_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Begin_1_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Begin_2_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Begin_2_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Begin_3_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Begin_3_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Begin_11_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Begin_11_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Begin_21_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Begin_21_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Begin_31_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Begin_31_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_First_time_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			Link.l1 = DLG_Convert("Enc_RapersGirl_dialog_First_time_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_2_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			Link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_2_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_text_2", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_text_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_l1_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_text_4", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_l1_4", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_text_5", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_l1_5", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, int((int(pchar.rank))*25 + frand(2)*500));
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_11_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_11_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_12_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_12_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_121Next";
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_12_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_22_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_22_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_122Next";
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_22_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_31_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_31_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_32";
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_31_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			dlgContext.valueText = GenerateRandomName(int(npchar.nation), "man");
			pchar.GenQuest.EncGirl.sLoverId = DLG_Convert("Enc_RapersGirl_dialog_Node_32_sLoverId_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext); 
			dlgContext.loverName = pchar.GenQuest.EncGirl.sLoverId;
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_32_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_32_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_12End_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_12End_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_1Next_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_1Next_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_1End";
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_1Next_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_1End_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_3End_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_3Final_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_3Final_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(int(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_13_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
						link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_13_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_13_text_2", "Dialogs\Enc_RapersGirl_dialog.txt");
						link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_13_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_13_text_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_13_l1_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_13_text_4", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_13_l1_4", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dlgContext.bigCoins = int(pchar.GenQuest.EncGirl.BigCoins);
			dlgContext.smallCoins = int(pchar.GenQuest.EncGirl.SmallCoins);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_131_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_131_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_131End";
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_131_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			dlgContext.valueText = rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			pchar.GenQuest.EncGirl.mapOwner = DLG_Convert("Enc_RapersGirl_dialog_Node_132_mapOwner_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext); 
			dlgContext.pirateName = GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_VOC);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dlgContext.pirateName = GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_1_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_1_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_2_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_2_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_2_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l2.go = "Node_132_3";
			}
			link.l3 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_2_l3_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_132_2End_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_3_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_3_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * int(pchar.rank);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_4_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			dlgContext.mapPrice = int(pchar.GenQuest.EncGirl.mapPrice);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_4_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSkillAfterPenalty(pchar, SKILL_COMMERCE) + GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP) + GetSkillAfterPenalty(pchar, SKILL_SNEAK)) > (rand(220) + 100) && (int(pchar.money) >= int(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_5_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_5_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_5_text_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_5_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -int(int(pchar.GenQuest.EncGirl.mapPrice)));
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap, "");
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_8_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_8_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_9_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_9_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dlgContext.valueText = XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Dat");
			dlgContext.valueText2 = XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen");
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_10_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_10_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_11_1_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_11_1_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_11_2_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_11_2_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_12_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_12_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_13_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_13_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_15_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_15_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			//Log_Info("Вы получили свою долю клада");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_17_text_1", "Dialogs\Enc_RapersGirl_dialog.txt"); 
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_17_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_18_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_18_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_19_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_19_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_132_20_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_132_20_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_133_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_133_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1.go = "Node_133_1";
			if(int(pchar.money) >= 15000)
			{
				link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_133_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
            sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_133_1_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", int(pchar.GenQuest.EncGirl.BigCoins));
			AddQuestUserData("JungleGirl", "sText2", int(pchar.GenQuest.EncGirl.SmallCoins));
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_134_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			if (GetCharacterItem(pchar, "jewelry52") >= int(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= int(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_134_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_134_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -int(pchar.GenQuest.EncGirl.BigCoins));
			TakeNItems(pchar, "jewelry53", -int(pchar.GenQuest.EncGirl.SmallCoins));
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_134_1_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_134_1_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_134_2_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_134_2_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_135_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_135_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_135End_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForSave_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForSave_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForSave_text_2", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForSave_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_210";
					link.l2 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForSave_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForSave_text_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForSave_l1_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_200_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_200_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_200End";
				link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_200_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l2.go = "Node_201";
			}
			else
			{
				dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_200_text_2", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_200_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_200End";
				link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_200_l2_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_201_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_201_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_202_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_202_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_203_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_203_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_200End";
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_203_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_204_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_204_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_206_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_206_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_207_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_207_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_208_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_208_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = int(int(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_209_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_210_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_210_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_211_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_211_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_220_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_220_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_221";
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_220_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_222_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_222_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_224_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_224_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && int(pchar.rank) > 15)
				{
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_225_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_225_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_226";
					link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_225_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_225_text_2", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_225_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_225_text_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_225_l1_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_225_text_4", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_225_l1_4", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l1.go = "Node_226";
					link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_225_l2_2", "Dialogs\Enc_RapersGirl_dialog.txt");
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_226_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_226_1_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && int(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_228_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_228_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_232";
				link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_228_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_228_text_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_228_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_228_l2_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_229_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_229_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_230_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_230_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_231_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_231_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_231_1_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_232_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(int(pchar.GenQuest.EncGirl.nation));
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_233_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_233_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_234_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_234_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_235";
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_234_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_236";													
			if(int(pchar.money) >= 5000)
			{
				link.l3 = DLG_Convert("Enc_RapersGirl_dialog_Node_234_l3_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_235_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_235_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_236_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_236_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSkillAfterPenalty(pchar, SKILL_SNEAK) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_240_1_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_240_1_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_240_1_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_241_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_241_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_242_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			if(int(pchar.money) >= 5000)
			{
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_242_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_237";
			}
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_242_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_245_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_245_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_246_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_246_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_247_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_237_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			if(int(pchar.money)>=5000)
			{
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_237_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_237_1";
			}
			if(int(pchar.money)>=25000)
			{
				link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_237_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l2.go = "Node_237_2";
			}
			if(int(pchar.money)>=35000)
			{
				link.l3 = DLG_Convert("Enc_RapersGirl_dialog_Node_237_l3_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_237_1_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_237_1_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_237_2_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_237_2_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_237_3_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_237_3_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(DLG_Convert("Enc_RapersGirl_dialog_Node_238_rumour_1", "Dialogs\Enc_RapersGirl_dialog.txt"), int(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_250_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_250_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			dlgContext.valueText = GenerateRandomName(int(npchar.nation), "man");
			pchar.GenQuest.EncGirl.sLoverId = DLG_Convert("Enc_RapersGirl_dialog_Node_251_sLoverId_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext); 
			dlgContext.loverName = pchar.GenQuest.EncGirl.sLoverId;
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_251_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext); // belamour
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_251_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dlgContext.valueText = XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city);
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_253_text_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_253_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_260_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_260_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_260End";
				link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_260_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_260_text_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_260_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_260End_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = DLG_Convert("Enc_RapersGirl_dialog_Node_261_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1 = DLG_Convert("Enc_RapersGirl_dialog_Node_261_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l1.go = "Node_262";
			link.l2 = DLG_Convert("Enc_RapersGirl_dialog_Node_261_l2_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			dlgContext.valueText = LAi_FindNearestFreeLocator2Pchar("reload");
			sTemp = DLG_Convert("Enc_RapersGirl_dialog_Node_262_stemp_1", "Dialogs\Enc_RapersGirl_dialog.txt", &dlgContext);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(int(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_1_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				Link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_1_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_1_text_2", "Dialogs\Enc_RapersGirl_dialog.txt");
					Link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_1_l1_2", "Dialogs\Enc_RapersGirl_dialog.txt");
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, int(PChar.rank)*100);
					dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_1_text_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					Link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksForHelp_1_l1_3", "Dialogs\Enc_RapersGirl_dialog.txt");
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = DLG_Convert("Enc_RapersGirl_dialog_ThanksAgain_text_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			Link.l1 = DLG_Convert("Enc_RapersGirl_dialog_ThanksAgain_l1_1", "Dialogs\Enc_RapersGirl_dialog.txt");
			Link.l1.go = "exit";
		break;
	}
}
