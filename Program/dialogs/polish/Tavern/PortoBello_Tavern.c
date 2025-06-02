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
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
