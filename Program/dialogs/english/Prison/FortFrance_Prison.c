// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I'm listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Officer, I have heard that there is a man named Folke Deluc in your prison. Is there anything I can do to secure his release?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Officer, it's me again about the prisoner Folke Deluc. I have bought the rights to his debt and I want this man released and handed over to me. Here are his debt papers, take a look.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "Good afternoon, officer. I want to inquire about my crewman...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "Here are the papers, now release my man.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, that sailor? He borrowed a significant sum from our banker, hasn't returned it, and even tried to escape. But he was found quickly. Since then, he has been under arrest and will stay here until he repays his debt.";
			link.l1 = "Hm. And how will he do that while staying in prison?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "I don't care about it, monsieur.";
			link.l1 = "Funny... And how much does this poor soul owe?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "I don't know. Ask the banker and he will give you the details.";
			link.l1 = "I see. Thank you for the information, officer.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Sharlie_3":
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
			dialog.text = "Hm. They are all correct. Do you really want me to release that prisoner?";
			link.l1 = "Yes. I need him to repay the debt, and I know a way he can do it.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "Fine, I have no reason to refuse you. Deluc will be brought here soon. But I have to warn you, this fox will run away at the first opportunity, so don't have any illusions about him.";
			link.l1 = "I understand, officer. Now I wish to take my debtor.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Yes, of course. Sergeant! Bring forth the prisoner! Folke Deluc, it seems he has a new master now!";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			// замораживаем ГГ
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto17"); // 170712
			// создаем штурмана
			ref sld;
			InitFolke("Folke", "Deluc");
		break;
		//<-- Бремя гасконца
		
		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		case "Del_Deluck":
			DelLandQuestMark(npchar);
			dialog.text = "Ha! I say, the gossip about your predicament will entertain Saint-Pierre for a long time. But don't take it personally, Captain. You're clearly the victim of bad fortune. Come in and don't worry: your navigator won't be getting away from this conversation, ha ha!";
			link.l1 = "Hilarious. Thank you, officer.";
            link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			pchar.questTemp.jailCanMove = true;
			AddLandQuestMark(characterFromId("Folke"), "questmarkmain");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "Understood, Captain. We'll proceed accordingly.";
			link.l1 = "...";
			link.l1.go = "Del_DeluckSvoboda_2";
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
		break;
		
		case "Del_DeluckSvoboda_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto17");
			
			sld = CharacterFromID("Folke");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_10";
			ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto23");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "FolkeStay", -1);
								
			sld = GetCharacter(NPC_GenerateCharacter("Del_Ohranik", "sold_fra_2", "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto12");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("Folke"), "", -1);
			
			StartQuestMovie(true, false, true);
			DoQuestCheckDelay("Del_Turma", 0.1);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
