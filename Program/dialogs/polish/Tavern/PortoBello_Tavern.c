// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"... ","Przez cały ten dzień to już trzeci raz, kiedy mówisz o jakimś pytaniu...","Wiecej pytań, jak mniemam?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do powiedzenia."),"Gdzież to moja pamięć się podziała...","Tak, to naprawdę trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Słuchaj, widziałeś korsarza o imieniu Francois Gontier? Niedawno był tutaj, w waszym mieście.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Słuchaj, czy mógłbyś mi powiedzieć, gdzie znaleźć kupca o imieniu Jaime Silicio? Miał do ciebie przyjść...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Spójrz, szukam człowieka o imieniu Bertrand Pinette, słyszałeś o nim? Przybył do Portobello niedawno. Imponujący jegomość w falistej peruce. Kupiec. Może tu był...";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "Powiesz mi, gdzie mogę znaleźć Marisę Calderę?";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("Nie, nie wiem. Nie zatrzymał się w tawernie i nie widziałem go też w mieście.","Już o to pytałeś, a ja ci odpowiedziałem.","Powiedziałem ci 'już o to pytałeś, Gontierze'.","Słuchaj, odejdź i przestań mnie nękać! Czy całkiem straciłeś rozum?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Cóż, będę szukał dalej.","Hm, chyba tak...","Tak, właśnie o to pytałem...","Przepraszam, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "Przebacz mi, señor, ale tylko zdrajca albo pijak rozmawiałby o takich sprawach z nieznajomym. Nie chcę żadnych kłopotów.";
			link.l1 = "Pijak, powiadasz? Do zobaczenia, kumplu.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Nie słyszałem o nim, kumpel.";
			link.l1 = "Jest znajomym don Carlosa de Milyar. Na pewno nigdy o nim nie słyszałeś?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Jestem. Jeśli on jest przyjacielem de Milyara - idź do gubernatora i zapytaj o señor Carlosa. On opowie ci o tym twoim handlarzu.";
			link.l1 = "Zrobię to. Dzięki za radę!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "Marisa? Hm... Dawno jej nie widziałem. Odkąd dowiedziała się o śmierci męża, nie pokazywała się w mieście.";
			link.l1 = "Więc jest wdową?";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Tavern_1_2":
			dialog.text = "Tak. Jej mąż był kapitanem handlowego pinasa 'Falałamacz'. Dzięki licencji Holenderskiej Kompanii Zachodnioindyjskiej miał dostęp niemal do wszystkich portów archipelagu. Mówi się, że nie przeżył ataku piratów w drodze z Belize do Capsterville. To tu nie jest rzadkość, ale dla niej był to prawdziwy cios.";
			link.l1 = "Więc po prostu zniknęła?";
			link.l1.go = "LFD_Tavern_1_3";
		break;
		
		case "LFD_Tavern_1_3":
			dialog.text = "Cóż, powiedzieć, że zniknęła, to przesada. Ale od tamtej pory prawie jej nie widać w mieście. Dziwna sprawa... Od czasu do czasu różni mężczyźni pytają o nią. Tak jak ty, kapitanie. Gdyby nie była taka pobożna, pomyślałbym, że... ukrywa się i zarabia jak potrafi. Ale Marisa przed śmiercią męża nie opuściła żadnej mszy. Żyła niemal w kościele, więc to raczej niemożliwe.";
			link.l1 = "To wszystko? Nic więcej nie wiesz?";
			link.l1.go = "LFD_Tavern_1_4";
		break;
		
		case "LFD_Tavern_1_4":
			dialog.text = "Wszystko, co wiem, kapitanie, już ci powiedziałem.";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;
		
		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
