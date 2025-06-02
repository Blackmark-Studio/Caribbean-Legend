// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham cię, jakie masz pytanie?"),"To już drugi raz, kiedy próbujesz zapytać...","To już trzeci raz, kiedy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracuję nad sprawami kolonii, a ty nadal mnie niepokoisz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie teraz. Złe miejsce i czas."),"Prawda... Ale później, nie teraz...","Zapytam... Ale trochę później...","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "Wasza Ekscelencjo, chciałbym zgłosić nielegalną działalność handlową na tej wyspie.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "Chciałbym usłyszeć raport z Twojej misji dotyczącej przemytu jedwabnego żagielka.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "Przybyłem w imieniu gubernatora generalnego Philippe'a de Poincy. Moim zadaniem jest przywieźć do was niewolników schwytanych od Holendrów, zgadza się?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "Przyprowadziłem ci niewolników, zgodnie z umową.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "Przybyłem na rozkaz gubernatora generalnego Phillipe'a de Poincy, aby wziąć udział we wspólnej ekspedycji na Curacao przeciwko Holendrom.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "Moja eskadra została uszczuplona, możemy teraz wyruszyć.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Interesujące. Zamieniam się w słuch.";
			link.l1 = "Mam z wiarygodnego źródła, że holenderski brygantyna 'Utrecht' pod angielską banderą od dłuższego czasu rozładowuje duże ilości jedwabnego płótna w Zatoce Portland. Działają już od ponad roku, nocą, między 10 a 15 dniem każdego miesiąca.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Czy jesteś pewien, że można ufać twojemu źródłu?";
			link.l1 = "Czasami nie ufam nawet sobie, jednak człowiek, który ujawnił tę informację, jest godny zaufania. Poza tym nie miał powodu kłamać.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "Zgoda, kapitanie. To poważna sprawa i muszę działać na podstawie przedstawionych informacji, nawet jeśli twój informator skłamał lub po prostu się pomylił. Wyślę patrol przybrzeżny o określonej porze, a jeśli twoje informacje się potwierdzą, zostaniesz hojnie wynagrodzony, takie nielegalne działania powinny być surowo tłumione.";
			link.l1 = "Zobaczę cię "+sTemp+" miesiąca 16-ego. Sytuacja z pewnością rozwiąże się do tego czasu.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = sti(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "Twoje informacje okazały się trafne, kapitanie. Zastawiliśmy zasadzkę na przestępców podczas transakcji. 'Utrecht' próbował uciec i walczył, ale został zatopiony przez naszą korwetę patrolową. Czterech kupujących stawiało opór przy aresztowaniu. Jeden został zabity strzałem, a pozostali trzej uciekli do dżungli. Cały ładunek 80 beli jedwabiu został przekazany do skarbca Port Royal. Choć nie udało nam się ustalić przywódcy tej sieci, zabity człowiek jest niezidentyfikowany, a inni uciekli, ogłaszam tę operację pełnym sukcesem. Wątpię, czy ci łajdacy odważą się kiedykolwiek tu wrócić.\nZrobiłeś nam wielką przysługę, kapitanie, będąc sumiennym i wskazując oszustów. Oto 10 000 pesos jako twoja nagroda.";
			link.l1 = "Wielce zobowiązany, Wasza Ekscelencjo. Cieszę się, że wszystko poszło zgodnie z planem i przemytnicy dostali to, na co zasłużyli. Z tym kończę, życzę miłego dnia.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "Dokładnie tak. Ilu niewolników przywiozłeś?";
				link.l1 = "Jeszcze nad tym pracuję. Wkrótce powrócę z wynikami.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "Zgadza się. Ilu niewolników przywiozłeś?";
			link.l1 = " "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "Hmm, Chevalier obiecał, że będzie nie mniej niż 3000 niewolników";
			link.l1 = "To prawda. To moja wina: niektórzy z niewolników zginęli pod ostrzałem wrogiego statku, inni zmarli w drodze. Naprawię swój błąd i wrócę do ciebie. Wszystko zostanie zrobione zgodnie z umową.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "Doskonale! Z Chevalier de Poincy można naprawdę robić interesy. Powiedz gubernatorowi generalnemu, że moja eskadra do ataku na Curacao będzie gotowa za miesiąc. Jestem pewien, że wyśle cię do mnie na tę kampanię, więc wkrótce się zobaczymy, Monsieur de Maure.";
			link.l1 = "Chętnie spotkałbym się z tobą ponownie, pułkowniku. A teraz pozwól, że się pożegnam.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "Nie wątpiłem, że to będziesz ty. Jeszcze lepiej! Nasza eskadra jest gotowa. Okręt liniowy 1. rangi i dwa statki 4. rangi. Maksymalna wielkość całej eskadry nie może przekroczyć pięciu statków.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "W takim razie zostawię dodatkowe statki w dokach i zatrzymam tylko dwa. W rezultacie będziemy mieć pięć statków.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "Tak, dokładnie pięć, i ani jednego więcej. Powinniśmy wyruszać.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "Doskonale. Teraz wyjaśnię ci plan, według którego będziemy działać: być może zechcesz coś zmienić lub dodać, wtedy to omówimy.";
			link.l1 = "Słucham, pułkowniku.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "Nie ma sensu zdobywać Curacao: to główna holenderska kolonia w archipelagu, i nawet jeśli zdobędziemy ich flagę w forcie Willemstad i zatkniemy angielską lub francuską, bardzo trudno będzie utrzymać wyspę. Holendrzy zrobią wszystko, by ją odzyskać i skierują na nią eskadry wojskowe. Ogólnie rzecz biorąc, nie ma sensu jej zdobywać, ponieważ nie jest to konieczne. Ważniejsze dla nas jest zmuszenie Steivesanta do podpisania traktatu na korzystnych dla nas warunkach, a aby to zrobić, wystarczy zniszczyć główne obrony wroga i postawić Holendrów pod groźbą całkowitego zniszczenia kolonii Willemstad.";
			link.l1 = "O czym będzie traktat?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "Traktat został sporządzony przeze mnie i kawalera de Poincy. Dotyczy różnych aspektów handlu, zakończenia 'wojny handlowej' między Kompanią a Anglią, odrzucenia roszczeń Stuyvesanta do wyspy Sint Maarten i innych punktów politycznych, które są dla ciebie mało interesujące.";
			link.l1 = "Zrozumiano.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "Plan jest taki: najpierw wszystkimi siłami zaatakujemy fort i go zniszczymy. Holendrzy będą spodziewać się desantu, ale tego nie zrobimy, największe straty zazwyczaj ponoszone są podczas zdobywania bastionu od strony morza. Zamiast tego wylądujemy zespołami szturmowymi w dwóch punktach na wyspie: na Przylądku Santa Maria i w lagunie Blanca, a następnie przemieścimy się lądem do bramy miasta Willemstad. Rozkazałem zabrać ze sobą artylerię polową na statki - na Curacao nie ma trudno dostępnych zarośli, i będziemy mogli toczyć działa na kołach po ziemi bez większych trudności.\nPodczas gdy Holendrzy będą zdezorientowani tym, co się dzieje, zajmiemy miasto z widoku dżungli i zablokujemy możliwość wysłania posiłków z fortu drogą lądową. Następnie poddamy miasto ostrzałowi artyleryjskiemu. Z pewnością garnizon fortu spróbuje zaatakować, ale nic nie zdziałają przeciwko artylerii polowej i naszym muszkieterom, a jeśli ich działa w forcie nadal będą funkcjonalne, nie będą mogli ich przetransportować do dżungli.\nDodatkowo nasze statki będą symulować przygotowania do desantu od strony morza, aby wzbudzić strach wśród wrogów i obniżyć ich morale. Po pewnym czasie, gdy Holendrzy w pełni zdadzą sobie sprawę z ich rozpaczliwej sytuacji, wezwijmy parlamentarzystów do negocjacji. Co myślisz, kapitanie?";
			link.l1 = "Genialny plan! A najlepsze w tym jest to, że nie stracimy żadnych żołnierzy przy murach fortu.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "Cieszę się, że spodobały ci się moje pomysły. Ruszajmy więc!";
			link.l1 = "Ruszajmy!";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
