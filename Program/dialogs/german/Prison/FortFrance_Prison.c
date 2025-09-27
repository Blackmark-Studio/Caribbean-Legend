// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Sprechen Sie, ich höre zu";
			link.l1 = "Ich habe mich geirrt. Lebewohl.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Offizier, ich habe gehört, dass ein Mann namens Folke Deluc in Ihrem Gefängnis ist. Gibt es etwas, was ich tun kann, um ihn freizulassen?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Offizier, es ist wieder ich wegen des Gefangenen Folke Deluc. Ich habe die Rechte an seiner Schuld gekauft und ich will, dass dieser Mann freigelassen und mir übergeben wird. Hier sind seine Schuldscheine, schau sie dir an.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "Guten Tag, Offizier. Ich möchte mich über meinen Crewmitglied erkundigen...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "Hier sind die Papiere, jetzt lasst meinen Mann frei.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Ach, dieser Seemann? Er hatte eine erhebliche Summe von unserem Bankier geliehen, sie nicht zurückgegeben und sogar versucht zu fliehen. Aber er wurde schnell gefunden. Seitdem ist er in Haft und er wird hier bleiben, bis er seine Schulden beglichen hat.";
			link.l1 = "Hm. Und wie wird er das tun, während er im Gefängnis bleibt?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Es ist mir egal, Monsieur.";
			link.l1 = "Lustig... Und wie viel schuldet diese arme Seele?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Ich weiß es nicht. Frage den Bankier und er wird dir Details geben.";
			link.l1 = "Ich verstehe, Danke für Ihre Informationen, Offizier.";
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
			dialog.text = "Hm. Sie sind alle korrekt. Wollen Sie wirklich, dass ich diesen Gefangenen freilasse?";
			link.l1 = "Ja. Ich brauche ihn, um die Schuld zu begleichen, und ich kenne den Weg, wie er das tun kann.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "Gut, ich habe keinen Grund, Ihnen zu verweigern. Deluc wird bald hierher gebracht. Aber ich muss Sie warnen, dass dieser Fuchs bei der ersten Gelegenheit weglaufen wird, also machen Sie sich keine Illusionen über ihn.";
			link.l1 = "Ich habe es verstanden, Offizier. Und jetzt möchte ich meinen Schuldner mitnehmen.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Ja, sicher. Sergeant! Bring den Gefangenen her! Folke Deluc, es scheint, dass er jetzt einen neuen Meister hat!";
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
			dialog.text = "Ha! Ich sage dir, das Gerede über deine Misere wird Saint-Pierre lange unterhalten. Aber nimm es nicht persönlich, Kapitän. Du bist ganz klar ein Opfer des schlechten Schicksals. Komm herein und mach dir keine Sorgen: dein Navigator wird diesem Gespräch nicht entkommen, ha ha!";
			link.l1 = "Zum Schreien komisch. Danke, Offizier.";
            link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			pchar.questTemp.jailCanMove = true;
			AddLandQuestMark(characterFromId("Folke"), "questmarkmain");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "Verstanden, Kapitän. Wir werden entsprechend vorgehen.";
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
