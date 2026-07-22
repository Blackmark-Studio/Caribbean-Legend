void ProcessDialogEvent()
{
	object dlgContext;
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = int(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = DLG_Convert("Enc_Carib_dialog_First_time_text_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1 = DLG_Convert("Enc_Carib_dialog_First_time_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				if("quest.agressive" in npchar)
					sld.quest.agressive = true;
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (int(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_text_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_l1_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = DLG_Convert("Enc_Carib_dialog_war_indian_l2_1", "Dialogs\Enc_Carib_dialog.txt");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_text_2", "Dialogs\Enc_Carib_dialog.txt");
				link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_l1_2", "Dialogs\Enc_Carib_dialog.txt");
				link.l1.go = "war_indian_1";
				link.l2 = DLG_Convert("Enc_Carib_dialog_war_indian_l2_2", "Dialogs\Enc_Carib_dialog.txt");
				if (int(pchar.questTemp.Indian.relation)+(int(GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = DLG_Convert("Enc_Carib_dialog_war_indian_l3_1", "Dialogs\Enc_Carib_dialog.txt");
				if (int(pchar.questTemp.Indian.relation)+(int(GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP)/6)+int(GetSkillAfterPenalty(pchar, SKILL_SNEAK)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_1_text_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_1_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_2_1_text_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_2_1_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			npchar.quest.agressive = true;
			dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_2_2_text_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_2_2_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_3_1_text_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_3_1_l1_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l1.go = "war_indian_trade";
				link.l2 = DLG_Convert("Enc_Carib_dialog_war_indian_3_1_l2_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l2.go = "exit_fight";
			}
			else
			{
				npchar.quest.agressive = true;
				dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_3_1_text_2", "Dialogs\Enc_Carib_dialog.txt");
				link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_3_1_l1_2", "Dialogs\Enc_Carib_dialog.txt");
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			npchar.quest.agressive = true;
			dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_3_2_text_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_3_2_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_trade_text_1", "Dialogs\Enc_Carib_dialog.txt");
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					dlgContext.valueText = XI_ConvertString("pistol"+i);
					link.(sLink) = DLG_Convert("Enc_Carib_dialog_war_indian_trade_link_dyn_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = DLG_Convert("Enc_Carib_dialog_gun_1_gun_1", "Dialogs\Enc_Carib_dialog.txt");
			if (hrand(1) == 0)
			{
				dlgContext.valueText = (rand(2)+2);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_1_item_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = hrand(1)+1;
				dlgContext.qtyText = FindRussianQtyString(iTotalTemp);
				sText = DLG_Convert("Enc_Carib_dialog_gun_1_stext_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			}
			else
			{
				dlgContext.valueText = (hrand(9)+14);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_1_item_2", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = hrand(2)+1;
				dlgContext.qtyText = FindRussianQtyString(iTotalTemp);
				sText = DLG_Convert("Enc_Carib_dialog_gun_1_stext_2", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			}
			dlgContext.offerText = sText;
			dialog.text = DLG_Convert("Enc_Carib_dialog_gun_1_text_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_Carib_dialog_gun_1_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_Convert("Enc_Carib_dialog_gun_1_l2_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = DLG_Convert("Enc_Carib_dialog_gun_2_gun_1", "Dialogs\Enc_Carib_dialog.txt");
			if (hrand(3) < 2)
			{
				dlgContext.valueText = (rand(2)+2);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_2_item_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = hrand(2)+2;
				dlgContext.qtyText = FindRussianQtyString(iTotalTemp);
				sText = DLG_Convert("Enc_Carib_dialog_gun_2_stext_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			}
			else
			{
				dlgContext.valueText = (hrand(3)+1);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_2_item_2", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = hrand(2)+2;
				dlgContext.qtyText = FindRussianQtyString(iTotalTemp);
				sText = DLG_Convert("Enc_Carib_dialog_gun_2_stext_2", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			}
			dlgContext.offerText = sText;
			dialog.text = DLG_Convert("Enc_Carib_dialog_gun_2_text_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_Carib_dialog_gun_2_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_Convert("Enc_Carib_dialog_gun_2_l2_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = DLG_Convert("Enc_Carib_dialog_gun_3_gun_1", "Dialogs\Enc_Carib_dialog.txt");
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				dlgContext.qty = qty;
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_3_item_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = hrand(6)+qty*15;
				dlgContext.qtyText = FindRussianQtyString(iTotalTemp);
				sText = DLG_Convert("Enc_Carib_dialog_gun_3_stext_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			}
			else
			{
				dlgContext.valueText = (hrand(2)+2);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_3_item_2", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = hrand(2)+5;
				dlgContext.qtyText = FindRussianQtyString(iTotalTemp);
				sText = DLG_Convert("Enc_Carib_dialog_gun_3_stext_2", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			}
			dlgContext.offerText = sText;
			dialog.text = DLG_Convert("Enc_Carib_dialog_gun_3_text_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_Carib_dialog_gun_3_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_Convert("Enc_Carib_dialog_gun_3_l2_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = DLG_Convert("Enc_Carib_dialog_gun_4_gun_1", "Dialogs\Enc_Carib_dialog.txt");
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				dlgContext.valueText = (qty+4);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_4_item_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = hrand(10)+qty*30;
				dlgContext.qtyText = FindRussianQtyString(iTotalTemp);
				sText = DLG_Convert("Enc_Carib_dialog_gun_4_stext_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			}
			else
			{
				dlgContext.valueText = (hrand(10)+1);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_4_item_2", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = 1;
				sText = DLG_Convert("Enc_Carib_dialog_gun_4_stext_2", "Dialogs\Enc_Carib_dialog.txt");
			}
			dlgContext.offerText = sText;
			dialog.text = DLG_Convert("Enc_Carib_dialog_gun_4_text_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_Carib_dialog_gun_4_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_Convert("Enc_Carib_dialog_gun_4_l2_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = DLG_Convert("Enc_Carib_dialog_gun_5_gun_1", "Dialogs\Enc_Carib_dialog.txt");
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_5_item_1", "Dialogs\Enc_Carib_dialog.txt");
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_5_item_2", "Dialogs\Enc_Carib_dialog.txt");
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				dlgContext.valueText = (qty+6);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_5_item_3", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				dlgContext.qtyText = FindRussianQtyString(iTotalTemp);
				sText = DLG_Convert("Enc_Carib_dialog_gun_5_stext_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			}
			else
			{
				dlgContext.valueText = (hrand(10)+1);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_5_item_4", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = 1;
				sText = DLG_Convert("Enc_Carib_dialog_gun_5_stext_2", "Dialogs\Enc_Carib_dialog.txt");
			}
			dlgContext.offerText = sText;
			dialog.text = DLG_Convert("Enc_Carib_dialog_gun_5_text_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_Carib_dialog_gun_5_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_Convert("Enc_Carib_dialog_gun_5_l2_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = DLG_Convert("Enc_Carib_dialog_gun_6_gun_1", "Dialogs\Enc_Carib_dialog.txt");
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				dlgContext.valueText = (qty+4);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_6_item_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = hrand(8)+qty*20;
				dlgContext.qtyText = FindRussianQtyString(iTotalTemp);
				sText = DLG_Convert("Enc_Carib_dialog_gun_6_stext_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			}
			else
			{
				dlgContext.valueText = (hrand(10)+1);
				npchar.quest.item = DLG_Convert("Enc_Carib_dialog_gun_6_item_2", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
				iTotalTemp = 1;
				sText = DLG_Convert("Enc_Carib_dialog_gun_6_stext_2", "Dialogs\Enc_Carib_dialog.txt");
			}
			dlgContext.offerText = sText;
			dialog.text = DLG_Convert("Enc_Carib_dialog_gun_6_text_1", "Dialogs\Enc_Carib_dialog.txt", &dlgContext);
			link.l1 = DLG_Convert("Enc_Carib_dialog_gun_6_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = DLG_Convert("Enc_Carib_dialog_gun_6_l2_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = int(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			//Log_Info("Вы отдали "+XI_ConvertString(npchar.quest.gun)+"");
			//Log_Info("Вы получили "+XI_ConvertString(npchar.quest.item)+" в количестве "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (int(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_trade_agree_text_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_trade_agree_l1_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_trade_agree_text_2", "Dialogs\Enc_Carib_dialog.txt");
				if (CheckCaribGuns())
				{
					link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_trade_agree_l1_2", "Dialogs\Enc_Carib_dialog.txt");
					link.l1.go = "war_indian_trade";
				}
				link.l2 = DLG_Convert("Enc_Carib_dialog_war_indian_trade_agree_l2_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_trade_exit_text_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_trade_exit_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (int(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				npchar.quest.agressive = true;
				dialog.text = DLG_Convert("Enc_Carib_dialog_war_indian_trade_bad_text_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l1 = DLG_Convert("Enc_Carib_dialog_war_indian_trade_bad_l1_1", "Dialogs\Enc_Carib_dialog.txt");
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = DLG_Convert("Enc_Carib_dialog_peace_indian_text_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1 = DLG_Convert("Enc_Carib_dialog_peace_indian_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "peace_indian_1";
			link.l2 = DLG_Convert("Enc_Carib_dialog_peace_indian_l2_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = DLG_Convert("Enc_Carib_dialog_peace_indian_1_text_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1 = DLG_Convert("Enc_Carib_dialog_peace_indian_1_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = DLG_Convert("Enc_Carib_dialog_peace_indian_2_text_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1 = DLG_Convert("Enc_Carib_dialog_peace_indian_2_l1_1", "Dialogs\Enc_Carib_dialog.txt");
			link.l1.go = "exit_fight";
		break;
	}
}