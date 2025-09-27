// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Mów, słucham";
			link.l1 = "Byłem w błędzie. Żegnaj.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Oficerze, słyszałem, że w waszym więzieniu jest człowiek o imieniu Folke Deluc. Czy jest coś, co mogę zrobić, aby go uwolnić?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Oficerze, to ja znowu w sprawie więźnia Folke Deluc. Kupiłem prawa do jego długu i chcę, aby ten człowiek został uwolniony i przekazany mnie. Oto jego dokumenty dłużne, proszę spojrzeć.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "Dzień dobry, oficerze. Chciałbym zapytać o mojego członka załogi...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "Oto papiery, teraz wypuść mojego człowieka.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Ach, ten marynarz? Pożyczył znaczną sumę od naszego bankiera, nie zwrócił jej i nawet próbował uciec. Ale szybko go znaleziono. Od tego czasu jest aresztowany i pozostanie tutaj, dopóki nie spłaci długu.";
			link.l1 = "Hm. A jak to zrobi, siedząc w więzieniu?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Nie obchodzi mnie to, monsieur.";
			link.l1 = "Zabawne... A ileż to biedna dusza jest winna?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Nie wiem. Zapytaj bankiera, a on poda ci szczegóły.";
			link.l1 = "Widzę, dzięki za informację, oficerze.";
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
			dialog.text = "Hm. Wszystko się zgadza. Czy naprawdę chcesz, żebym uwolnił tego więźnia?";
			link.l1 = "Tak. Potrzebuję, by spłacił dług, i wiem, jak może to zrobić.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "Dobrze, nie mam powodów, by ci odmówić. Deluc zostanie tu wkrótce przyprowadzony. Muszę cię jednak ostrzec, że ten lis przy pierwszej okazji ucieknie, więc nie żyw złudzeń co do niego.";
			link.l1 = "Zrozumiałem, oficerze. A teraz chcę zabrać mojego dłużnika.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Tak, oczywiście. Sierżancie! Przyprowadź więźnia! Folke Deluc, wydaje się, że teraz ma nowego pana!";
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
			dialog.text = "Ha! Powiadam, plotki o twej sytuacji będą bawić Saint-Pierre przez długi czas. Ale nie bierz tego do siebie, Kapitanie. Zdecydowanie jesteś ofiarą złego losu. Wejdź i nie martw się: twój nawigator nie ucieknie od tej rozmowy, ha ha!";
			link.l1 = "Zabawne. Dziękuję, oficerze.";
            link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			pchar.questTemp.jailCanMove = true;
			AddLandQuestMark(characterFromId("Folke"), "questmarkmain");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "Zrozumiano, Kapitanie. Postąpimy zgodnie z Twoimi instrukcjami.";
			link.l1 = "... ";
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
