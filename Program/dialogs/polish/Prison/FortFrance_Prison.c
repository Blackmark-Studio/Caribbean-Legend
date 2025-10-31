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
			// создаем штурмана
			sld = InitFolke("Folke", "Deluc");
			pchar.questTemp.Sharlie = "takeskiper";	
			ForceHeroAutolevel(sld);
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Бремя гасконца
		
		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		case "Del_Deluck":
			DelLandQuestMark(npchar);
			dialog.text = "Ha! Powiadam, plotki o twej sytuacji będą bawić Saint-Pierre przez długi czas. Ale nie bierz tego do siebie, Kapitanie. Zdecydowanie jesteś ofiarą złego losu. Wejdź i nie martw się: twój nawigator nie ucieknie od tej rozmowy, ha ha!";
			link.l1 = "Zabawne. Dziękuję, oficerze.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_prison");
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
			
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_10";
			
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
