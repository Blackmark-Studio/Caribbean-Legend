// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Śmiało, czego chcesz?"," Właśnie o tym rozmawialiśmy. Musiałeś zapomnieć... ","To już trzeci raz dzisiaj, kiedy mówisz o jakimś pytaniu...","Słuchaj, to jest sklep. Ludzie tutaj kupują towar. Nie przeszkadzaj mi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Prawda, z jakiegoś powodu zapomniałem...","Tak, to naprawdę już trzeci raz...","Hm, nie zamierzam...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Słuchaj, "+npchar.name+", widziałeś ostatnio Miguela Dichoso na Isla Tesoro?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = " "+npchar.name+", jestem tutaj w imieniu Marcusa Tyrexa. Powiedział, że potrzebujesz kogoś do wykonania zadania.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = " "+npchar.name+", 'Rosbohom' został znaleziony i zdobyty. Czy powinniśmy zacząć rozładowywać i liczyć?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "Tak, mam. Kupił tu zaopatrzenie dla swojego statku. Nawiasem mówiąc, to było bardzo niedawno. Dosłownie przegapiliście się o kilka dni. A propos, może nadal być w tej osadzie. Nie szpieguję dla ludzi, wiesz. Popytaj jeszcze trochę, a kto wie, może znajdziesz swojego don.";
			link.l1 = "W porządku. Dzięki za informacje!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "Dokładnie! Dobrze, że przybyłeś na czas. Teraz pozwól, że opowiem ci sedno sprawy...";
			link.l1 = "Zamieniam się w słuch.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "W tej chwili "+sTemp+", holenderski statek o nazwie 'Rosbohom', przybywa na nasze wody wraz z jednym okrętem eskortowym. Jest załadowany hebanem i płynie z Willemstad, aby spotkać się z innym okrętem eskortowym, by zapewnić bezpieczną podróż do Europy. Nie wiem, jaką trasę obiera, czy przez Sint Maarten, czy przez Espanyol, ale znam współrzędne ich punktu spotkania\nTwoim zadaniem jest znaleźć tam Holendrów, wejść na pokład handlarza i dostarczyć mi jego ładunek. Zapłacę, jak tylko ładunek zostanie dostarczony.";
			link.l1 = "Zrozumiałem. Czas i miejsce?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = " "+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" Północ i "+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+" Zachód. To musi być gdzieś na południe lub południowy zachód od Isla Tesoro, nie jestem w tym dobry, nie jestem żeglarzem, ale ty jesteś. Masz około pięciu dni na wykonanie zadania.";
			link.l1 = "Zrozumiano... Mam to. Nie traćmy więc czasu!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Pomódl się, kapitanie. Będę czekał na ciebie i ładunek.";
			link.l1 = "... ";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "Żartujesz sobie ze mnie, młodzieńcze? W twoich ładowniach nie ma ani jednej deski z hebanu! To bezczelne oszustwo! Wynoś się stąd! Poinformuję o tym Marcusa! Wynoś się!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "Żartujesz sobie ze mnie, chłopcze? Twój ładownia ma tylko kilka drzazg hebanu! To zuchwałe oszustwo! Wynoś się stąd! Powiadomię o tym Marcusa! Wynoś się!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "Rosbohom miał przynajmniej "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+"hebanowca. Dlaczego przyniosłeś mi mniej?";
				link.l1 = "Cóż... wiesz, musiałem pozbyć się części tego podczas walki. Plus szczury, niech je szlag...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "Bardzo dobrze. Ile masz? "+FindRussianQtyString(iTotalTemp)+"Splendid! Zapłacę ci 150 pesos za sztukę.";
			link.l1 = "150 sztuk ośmiu? Myślę, że to heban kosztuje znacznie więcej.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "Szczury? No cóż... Ale dobrze. 100 pesos za sztukę i możesz odejść.";
			link.l1 = "100 pesos tylko? To jest rozbój!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Rabunek to wasze rzemiosło, kapitanie, ja jestem prostym kupcem. Weźcie swoje pieniądze i przestańmy się kłócić, już zdobyliście niezłą sumkę sprzedając część mojego ładunku gdzie indziej.";
			link.l1 = "Pierdól się w takim razie!";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "I masz rację, kapitanie, ale najpierw spróbuj sprzedać skradzione towary, a ja zobaczę, ile inni kupcy ci za nie zapłacą. Oferowana cena jest bardzo wysoka. Po drugie, to był mój trop, nigdy nie znalazłbyś tej karawany sam, a na dodatek były na niej inne wartościowe rzeczy i towary, których nie roszczę sobie prawa. Po trzecie, dam ci najlepsze rekomendacje w oczach Marcusa Tyrexa i to kosztuje dużo, uwierz mi. I wreszcie, po czwarte, biedny kupiec musi jakoś zarabiać na życie.";
			link.l1 = "O rety! Muszę się wycofać w obliczu takich argumentów "+npchar.name+"Zróbmy rachunki.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Wspaniale. Weź swoje monety. To była przyjemność. Odwiedzaj mój sklep od czasu do czasu. Niech ci szczęście sprzyja na morzu!";
			link.l1 = "  A ty w swoim handlu... ";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
