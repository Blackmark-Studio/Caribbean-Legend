void ProcessDialogEvent()
{
	object dlgContext;
	ref NPChar, TempChar, sld;
	aref Link, Diag;
	
	int i, iTemp;
	string sTemp, sTemp1;
	string sGroup;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			
			dialog.text = DLG_Convert("Hunter_dialog_First_time_text_1", "Dialogs\Hunter_dialog.txt");
			Link.l1 = DLG_Convert("Hunter_dialog_First_time_l1_1", "Dialogs\Hunter_dialog.txt");
			Link.l1.go = "meeting"; 
		break;

		case "meeting":
			dlgContext.valueText = XI_ConvertString(Nations[int(NPChar.nation)].Name);
			dialog.text = DLG_Convert("Hunter_dialog_meeting_text_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
			Link.l1 = DLG_Convert("Hunter_dialog_meeting_l1_1", "Dialogs\Hunter_dialog.txt");
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			dlgContext.personName = GetFullName(TempChar);
    			Link.l2 = DLG_Convert("Hunter_dialog_meeting_l2_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
    			Link.l2.go = "lier";
			}
            Link.l3 = DLG_Convert("Hunter_dialog_meeting_l3_1", "Dialogs\Hunter_dialog.txt");
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSkillAfterPenalty(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = DLG_Convert("Hunter_dialog_lier_text_1", "Dialogs\Hunter_dialog.txt");
                Link.l1 = DLG_Convert("Hunter_dialog_lier_l1_1", "Dialogs\Hunter_dialog.txt");
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = DLG_Convert("Hunter_dialog_lier_text_2", "Dialogs\Hunter_dialog.txt");
                Link.l1 = DLG_Convert("Hunter_dialog_lier_l1_2", "Dialogs\Hunter_dialog.txt");
			    Link.l1.go = "Cost_Head";
			    Link.l2 = DLG_Convert("Hunter_dialog_lier_l2_1", "Dialogs\Hunter_dialog.txt");
			    Link.l2.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
            
        break;
        
        case "lier_2":
            AddDialogExitQuest("GoAway_Hunters_Land");
            DialogExit();
        break;
        // boal <--
        
        case "battle":
            AddDialogExitQuest("Battle_Hunters_Land");    // BOAL Весь код я перенес сюда по всем нациям, просто не переименовал
            DialogExit();
        break;

        case "Cost_Head2":
            LandHunterIncreaseRep(NPChar);
            AddMoneyToCharacter(pchar, -int(PChar.HunterCost));
            AddDialogExitQuest("GoAway_Hunters_Land"); 
            DialogExit();
        break;

        case "Cost_Head":
			dlgContext.hunterCost = PChar.HunterCost;
			dialog.text = DLG_Convert("Hunter_dialog_Cost_Head_text_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
            if(int(Pchar.money) < int(PChar.HunterCost))
            {
                Link.l1 = DLG_Convert("Hunter_dialog_Cost_Head_l1_1", "Dialogs\Hunter_dialog.txt");
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = DLG_Convert("Hunter_dialog_Cost_Head_l1_2", "Dialogs\Hunter_dialog.txt");
                Link.l1.go = "Cost_Head2";
                Link.l2 = DLG_Convert("Hunter_dialog_Cost_Head_l2_1", "Dialogs\Hunter_dialog.txt");
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = DLG_Convert("Hunter_dialog_NoMoney_text_1", "Dialogs\Hunter_dialog.txt");
			Link.l1 = DLG_Convert("Hunter_dialog_NoMoney_l1_1", "Dialogs\Hunter_dialog.txt");
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = DLG_Convert("Hunter_dialog_TreasureHunter_text_1", "Dialogs\Hunter_dialog.txt");
            Link.l1 = DLG_Convert("Hunter_dialog_TreasureHunter_l1_1", "Dialogs\Hunter_dialog.txt");
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			dlgContext.personName = GetFullName(TempChar);
    			Link.l2 = DLG_Convert("Hunter_dialog_TreasureHunter_l2_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = DLG_Convert("Hunter_dialog_TreasureHunter_l3_1", "Dialogs\Hunter_dialog.txt");
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSkillAfterPenalty(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = DLG_Convert("Hunter_dialog_TreasureHunterLier_text_1", "Dialogs\Hunter_dialog.txt");
                Link.l1 = DLG_Convert("Hunter_dialog_TreasureHunterLier_l1_1", "Dialogs\Hunter_dialog.txt");
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = DLG_Convert("Hunter_dialog_TreasureHunterLier_text_2", "Dialogs\Hunter_dialog.txt");
			    Link.l1 = DLG_Convert("Hunter_dialog_TreasureHunterLier_l1_2", "Dialogs\Hunter_dialog.txt");
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = DLG_Convert("Hunter_dialog_TreasureCaptain_text_1", "Dialogs\Hunter_dialog.txt");
			Link.l1 = DLG_Convert("Hunter_dialog_TreasureCaptain_l1_1", "Dialogs\Hunter_dialog.txt");
			Link.l1.go = "TreasureCaptain_fight"; 
		break;
		
		case "TreasureCaptain_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_sailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "TreasureOfficer":
			dialog.text = DLG_Convert("Hunter_dialog_TreasureOfficer_text_1", "Dialogs\Hunter_dialog.txt");
			Link.l1 = DLG_Convert("Hunter_dialog_TreasureOfficer_l1_1", "Dialogs\Hunter_dialog.txt");
			Link.l1.go = "TreasureOfficer_fight"; 
		break;
		
		case "TreasureOfficer_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// генератор "Повод для спешки"
		case "ReasonToFast_THunter_1":
			if(CheckAttribute(pchar,"GenQuest.CannotWait"))	DeleteAttribute(pchar, "GenQuest.CannotWait");
			dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_1_text_1", "Dialogs\Hunter_dialog.txt");
			link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_1_l1_1", "Dialogs\Hunter_dialog.txt");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_1_l2_1", "Dialogs\Hunter_dialog.txt");
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dlgContext.mapOwnerName = GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN);
			dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_2_text_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_2_l1_1", "Dialogs\Hunter_dialog.txt");
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", int(pchar.questTemp.ReasonToFast.p8)) >= int(pchar.questTemp.ReasonToFast.p8)
				&& ReasonToFast_CheckTreasureQty("Chest", int(pchar.questTemp.ReasonToFast.p7)) >= int(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_2_l2_1", "Dialogs\Hunter_dialog.txt");
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_3_text_1", "Dialogs\Hunter_dialog.txt");
			link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_3_l1_1", "Dialogs\Hunter_dialog.txt");
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_4_text_1", "Dialogs\Hunter_dialog.txt");
			link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_THunter_4_l1_1", "Dialogs\Hunter_dialog.txt");
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;
		
		case "ReasonToFast_THunter_GoAway":			
			iTemp = ReasonToFast_CheckTreasureQty("icollection", int(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", int(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "24");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");	
			}
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFastTHunter_Fight":
			sGroup = "LAND_HUNTER";
			sTemp = "LandHunter0";
			iTemp = int(pchar.HunterCost.Qty);
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			for(i = 1; i <= iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_TrHuntersDied");	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "ReasonToFast_HunterShore1":
			dlgContext.contactName = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM);
			dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore1_text_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore1_l1_1", "Dialogs\Hunter_dialog.txt");
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dlgContext.mapOwnerName = GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN);
				dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore11_text_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
				dlgContext.contactName = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT);
				link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore11_l1_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
				link.l1.go = "ReasonToFast_HunterShore12_1";
				dlgContext.contactName = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM);
				link.l2 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore11_l2_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore11_text_2", "Dialogs\Hunter_dialog.txt");
				if(ReasonToFast_CheckTreasureQty("icollection", int(pchar.questTemp.ReasonToFast.p8)) >= int(pchar.questTemp.ReasonToFast.p8)
					&& ReasonToFast_CheckTreasureQty("Chest", int(pchar.questTemp.ReasonToFast.p7)) >= int(pchar.questTemp.ReasonToFast.p7))
				{
					dlgContext.contactName = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT);
					link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore11_l1_2", "Dialogs\Hunter_dialog.txt", &dlgContext);
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				dlgContext.contactName = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM);
				link.l2 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore11_l2_2", "Dialogs\Hunter_dialog.txt", &dlgContext);
				link.l2.go = "ReasonToFast_HunterShore23";				
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore12_1":
			TakeNItems(pchar, "mapQuest", -1); 
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "карту");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore12_2":
			iTemp = ReasonToFast_CheckTreasureQty("icollection", int(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", int(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}			
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "ценности");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore2":
			dlgContext.contactName = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN);
			dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore2_text_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore2_l1_1", "Dialogs\Hunter_dialog.txt");
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dlgContext.moneyAmount = int(pchar.questTemp.ReasonToFast.p10);
			dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore21_text_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
			dlgContext.contactName = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT);
			link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore21_l1_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
			link.l1.go = "ReasonToFast_HunterShore22";
			dlgContext.contactName = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM);
			link.l2 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore21_l2_1", "Dialogs\Hunter_dialog.txt", &dlgContext);
			link.l2.go = "ReasonToFast_HunterShore23";
		break;
		
		case "ReasonToFast_HunterShore22":
			if(int(pchar.money) >= int(pchar.questTemp.ReasonToFast.p10))
			{
				AddMoneyToCharacter(pchar, -int(int(pchar.questTemp.ReasonToFast.p10)));
				AddQuestRecord("ReasonToFast", "20");
				AddQuestUserData("ReasonToFast", "sText", "деньги");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				DialogExit();	
				AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
			}
			else
			{
				dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore22_text_1", "Dialogs\Hunter_dialog.txt");
				link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore22_l1_1", "Dialogs\Hunter_dialog.txt");
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore23_text_1", "Dialogs\Hunter_dialog.txt");
			link.l1 = DLG_Convert("Hunter_dialog_ReasonToFast_HunterShore23_l1_1", "Dialogs\Hunter_dialog.txt");
			link.l1.go = "ReasonToFastTHunter_Fight";
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
				pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
			}
		break;
		// генератор "Повод для спешки"
	}
}

string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	string ret = "";

	if (CheckAttribute(&locations[nLoc],"islandId"))
	{
		if (locations[nLoc].islandId != "Mein")
		{
			ret = DLG_Convert("Hunter_dialog_GetLocHunterName_island_1", "Dialogs\Hunter_dialog.txt") + GetIslandNameByID(locations[nLoc].islandId);
		}
		else
		{
			ret = DLG_Convert("Hunter_dialog_GetLocHunterName_mainland_1", "Dialogs\Hunter_dialog.txt");
		}
	}
	//
	if (CheckAttribute(&locations[nLoc],"fastreload"))
	{
		ret += " (" +GetCityName(locations[nLoc].fastreload) + ")";
	}

	return ret;	
}