// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie jakiś czas temu...","Nie spotkałem jeszcze ludzi z taką ciekawością na mojej stoczni ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moja robota to budowanie statków. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do omówienia."),"Gdzież to podziała się moja pamięć...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ”ЊЉ-Њартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "Twój człowiek powiedział mi, że chcesz mnie widzieć. Jestem cały uszy.";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "Wykonałem zadanie. "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_OIL))+"beczki z żywicą są w moich ładowniach.";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ”ЊЉ-Њартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "Tak-tak, kapitanie "+GetFullName(pchar)+"  Widziałem, jak twój statek wpływał do naszego portu i od razu wysłałem do ciebie mojego pracownika. Przejdźmy więc do rzeczy: jesteś nowicjuszem, ale mówią, że już stałeś się doświadczonym żeglarzem i fortuna ci sprzyja. Dlatego mam dla ciebie propozycję biznesową.";
			link.l1 = "Interesujące! Mów dalej, opowiedz mi.";
			link.l1.go = "FMQM_1";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_1":
			dialog.text = "Słyszałeś kiedyś o specjalnej żywicy, którą Hiszpanie produkują na wyspie Trynidad? To rzadki zasób o strategicznej wartości, używany do wzmacniania kadłubów statków. Każda beczka kosztuje sporo, ponieważ Hiszpanie kierują całą żywicę na potrzeby swojej floty. Każda władza kolonialna kontroluje handel tym towarem, mówiąc prosto, to czysta kontrabanda\nPotrzebuję tej żywicy do specjalnego zamówienia. Oczywiście, nasz sklep jej nie ma, to samo można powiedzieć o naszych lokalnych magazynach wojskowych albo po prostu nie chcieli jej sprzedać. To naprawdę nieistotne. Ważne jest, że potrzebuję tej żywicy i wiem, gdzie ją zdobyć. Wszystko, czego potrzebuję, to kapitan, który nie ma problemu z abordażami.";
			link.l1 = "Wydaje mi się, że zaczynam rozumieć twój punkt widzenia...";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "Wspaniale. Teraz posłuchaj, mały konwój handlowy został zlokalizowany w pobliżu Trynidadu, a dokładniej w porcie San Jose. Jeden statek przewozi porządną partię żywicy, tej samej żywicy, której pilnie potrzebuję. Powiem ci więcej, jeśli podoba ci się pomysł plądrowania wrogów naszego narodu. Jakie jest twoje zdanie?";
			link.l1 = "Podoba mi się twoja propozycja. Jestem gotów spróbować.";
			link.l1.go = "FMQM_3";
			link.l2 = "Podziękuję, monsieur. Mój statek i załoga nie są w najlepszej formie w tej chwili.";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "Dobrze, masz prawo robić, co chcesz. Przepraszam za zajęcie twojego czasu, kapitanie.";
			link.l1 = "Żegnaj.";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратскаЯ линейка
			dialog.text = "W takim razie słuchaj: konwój składa się z trzech statków, żywica będzie wśród innych towarów na "+sTemp+" zwany 'Bensecho'. To twój główny cel. Jak już wspomniałem, Hiszpanie płyną z San Jose - Trynidad, do San Juan - Puerto Rico. Z wiatrem w żagle wyruszą jutro, więc możesz wybrać, gdzie ich zaatakować.";
			link.l1 = "Zrozumiano. A co z nagrodą?";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "Wszystko, co mnie interesuje, to żywica. Zapłacę piętnaście złotych dublonów za każdą beczkę tego towaru. Według moich informacji, 'Bensecho' przewozi około stu beczek.";
			link.l1 = "Na wszystkie diabły! Toż to wielka suma!";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "Tak. Już ci mówiłem, że ten towar jest bardzo drogi i rzadki.";
			link.l1 = "Powiedziałeś mi również, że to kontrabanda.";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "Nie martw się, nie będzie potrzeby, abyś zanosił to do sklepu lub do przemytników. Przyjdź do mnie, gdy robota będzie skończona, zacumujemy twój statek w mojej stoczni do naprawy, a potem w nocy potajemnie rozładujemy cały ładunek. Nikt niczego nie podejrzewa.";
			link.l1 = "Wyprzedzasz mnie, mistrzu. Bardzo dobrze. Bez marnowania czasu. Już wyruszam w morze.";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "Z Bogiem, kapitanie.";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "Doskonale! Zacumujmy twój statek w doku, jak się wcześniej umówiliśmy. Rozładujemy go tam dziś w nocy. Wróć na swój statek, a ja przygotuję dla ciebie pieniądze.";
			link.l1 = "Zróbmy to.";
			link.l1.go = "FMQM_10";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
