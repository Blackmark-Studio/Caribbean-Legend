// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "Dobrze cię widzieć, mój synu.  Czy przybyłeś, aby spłacić swój dług?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Tak, ojcze.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "Przepraszam za opóźnienie, ale nie jestem tu z tego powodu. Jednak niedługo go spłace, nie martw się.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Czy czegoś potrzebujesz, mój synu?";
				link.l1 = "Tak, ojcze. Chciałbym zobaczyć mojego brata, Michela de Monpera. On powiedział...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Czy czegoś potrzebujesz, mój synu?";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Tak, ojcze. Potrzebuję twojej pomocy. Nazywam się "+GetFullName(pchar)+". Michel de Monper doradził mi, bym z tobą porozmawiał.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Tak, ojcze. Potrzebuję twojej pomocy. Nazywam się "+GetFullName(pchar)+". Mój brat, Michel de Monper, doradził mi, abym z tobą porozmawiał.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Tak, ojcze. Potrzebuję statku, aby pomóc Michelowi, lecz dopiero co przybyłem na Karaiby i mój portfel jest pusty. Mój brat powiedział mi, że mógłbyś mi pożyczyć trochę pieniędzy...";
				link.l1.go = "FastStart_2";
			}
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Tak, ojcze. Potrzebuję twojej pomocy.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Tak, ojcze.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "Nie, nic, ojcze.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "Co cię do mnie sprowadza, mój synu?";
			link.l1 = "Witaj, Ojcze. Zostałem poinformowany, że powinienem z tobą porozmawiać. Nazywam się Charles de Maure. Szukam Michela de Monpera. Z tego co wiem, powinien być gdzieś na Martynice. Jestem... jego bratem.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Brat Michela de Monper? De Maure? Jakie to dziwne...";
			link.l1 = "Rozumiem twoje wątpliwości, ojcze. Po prostu mamy różne nazwiska. Mój ojciec to Henri de Monper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "„A-ah, teraz rozumiem. Znałem osobiście Henriego de Monpera. Odwróć się w stronę światła, młodzieńcze. Tak! Wyglądasz dokładnie jak on. Te same rysy, te same szlachetne cechy! Cieszę się, że widzę syna Henriego de Monpera w naszej parafii.\nA odnośnie twojego pytania, powiem ci, że Michel jest wysokim rangą oficerem Zakonu Maltańskiego, ale ma... kłopoty. Na szczęście, jeden z rycerzy Zakonu obecnie mnie odwiedza. Wierzę, że zgodzi się towarzyszyć ci do twojego nieszczęsnego brata, niech Pan zmiłuje się nad jego losem...”";
			link.l1 = "Kim jest ten człowiek, święty ojcze?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "Mój synu, przyjdź jutro rano. W tej chwili nie mam ci nic więcej do powiedzenia.";
			link.l1 = "W porządku.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "Witaj, mój synu. Jak obiecałem, osoba, o której wspominałem wczoraj, już tu na ciebie czeka. Jest gotów zabrać cię do twojego brata, który, jak słyszałem, jest nieszczęśliwy. Niech Pan zmiłuje się nad jego duszą...";
			link.l1 = "Kim jest ten człowiek, święty ojcze?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "Tak, Charles, jestem tego świadomy. Ale muszę cię rozczarować. Michela tutaj nie ma.";
			link.l1 = "Co masz na myśli, że go tu nie ma? Powiedział, że będzie na mnie czekał u was w kościele! Ojcze, co się stało? Gdzie jest mój brat?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "Mój synu, twój brat tutaj był i opuścił mój skromny przybytek późno wczoraj w nocy. Dokąd poszedł, nie wiem. Ale zostawił ten list dla ciebie.";
			link.l1 = "Nie mogę w to uwierzyć... Po prostu nie moge! po tym wszystkim, co dla niego zrobiłem! Daj mi ten list!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Nie wpadaj w taki gniew, Charles. Oto list. Przeczytaj go, a potem... potem chciałbym z tobą porozmawiać. Ale najpierw przeczytaj wiadomość od twojego brata.";
			link.l1 = "Palę się z niecierpliwości, żeby sprawdzić co ten mój paskudny brat dla mnie nabazgrolił!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = " Widzę, że przeczytałeś list. Teraz chciałbym ci coś powiedzieć, Charles...";
				link.l1 = "  Ale... jak to możliwe? Co to za bzdury? Wiem, że mój brat jest osobliwy, ale nie jest szaleńcem! ";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "Mój synu, przeczytaj list. Porozmawiamy później.";
				link.l1 = "Tak, ojcze...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Działania twego brata także mnie zaskoczyły, Charles. Wciąż czuję chwile konsternacji. Lojalny sługa Zakonu i Trójcy, a zachowuje się jak dezerter.";
			link.l1 = "Czy masz jakiekolwiek pojęcie, co mogłoby być powodem tak dziwnego zachowania?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Niestety, nie wiem. Ale przypuszczam, że ma własne motywy, głębokie motywy. Zaniechanie całej przeszłości sugerowałoby niezwykle istotny powód. Nie potrafię sobię nawet wyobrazić, co to mogłoby być. Ale czuję, że to wiąże się z czymś niezwykle złym... wręcz okropnym.";
			link.l1 = "Cóż to mogłoby być, ojcze?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "Mój synu, kapłan nie widzi oczami, lecz sercem. Nie potrafię ci tego wyjaśnić słowami, ale... twój brat postanowił zrobić coś nieczystego, brudnego. Nigdy nie myślałem, że moje usta mogą to wypowiedzieć. Jednakże...";
			link.l1 = "Cóż, nie wątpię, że mój brat zaplanował coś nieczystego. Mogę nawet zrozumieć, co dokładnie zamierza zrobić. To 'coś' obejmuje coś żółtego i wydaje przyjemny brzęk.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "Nie sądzę, że żądza złota napędza twojego brata. Powiedziałbym, że potrzebuje czegoś większego.";
			link.l1 = "Dużo nauczyłem się od Michela i pojąłem jego filozofię, więc myślę, że potrafię zrozumieć, co jest dla niego ważne, a co nie. Ale zapamiętam twoje cenne słowa, ojcze.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "Niech Bóg cię błogosławi, synu. Idź, idź teraz. Niech Pan nad tobą czuwa!";
			link.l1 = "Dziękuję, ojcze. Do widzenia!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			pchar.questTemp.Sharlie = "escape";
			CloseQuestHeader("Sharlie");
			AddQuestRecord("Guardoftruth", "1");
			pchar.questTemp.Guardoftruth = "begin";
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// ставим пленного испанца
			sld = GetCharacter(NPC_GenerateCharacter("spa_baseprisoner", "q_spa_off_1", "man", "man", 30, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_13", "pistol1", "bullet", 150);
			sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "spa_prisoner";
			RemoveAllCharacterItems(sld, true);
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest1");
			LAi_CharacterDisableDialog(sld);//запрет диалога
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Brat Michela de Monpera? De Maure? Jakie to dziwne...";
			link.l1 = "Rozumiem twoje wątpliwości, ojcze. Po prostu mamy różne nazwiska. Mój ojciec to Henri de Monper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "A-ah, teraz rozumiem. Osobiście znałem Henriego de Monpera. Obróć się ku światłu, młodzieńcze... Tak! Wyglądasz jak on. Te same rysy, ten sam szlachetny profil! Cieszę się, że widzę syna Henriego de Monpera w naszej parafii.\nJuż słyszałem, że Michela odwiedził jakiś człowiek, który przybył z Europy, ale nie mogłem sobie wyobrazić, że to jego własny brat. Mam nadzieję, że będziesz w stanie pomóc Michelowi, przechodzi trudny okres. Tak czy inaczej, jak mogę być użyteczny?";
			link.l1 = "Michel powiedział mi, że będziesz w stanie pomóc, jeśli kiedykolwiek wpadnę w kłopoty z władzami.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "To ci powiedział Michel? Rozumiem. Cóż, mogę pomóc w takich sprawach. Mam pewne wpływy w Świętym Kościele Rzymskim i koloniach holenderskich. Dlatego mogę pośredniczyć między tobą a władzami hiszpańskimi, jak również holenderskimi. Oczywiście, niewiele będę mógł zrobić, jeśli twoje przewinienia będą zbyt poważne - w takim przypadku można osiągnąć jedynie niewielkie złagodzenie.\nTo będzie wymagało kilku interwencji dla pełnego pojednania. Poza tym, w każdym przypadku będziesz musiał dostarczyć mi złote dublony na cele charytatywne i wydatki podróżne. Ponadto, mogę pomóc ci tylko z jednym narodem na raz. Jeśli te warunki są dla ciebie do przyjęcia, nie wahaj się zwrócić do mnie, a zobaczymy, co da się zrobić.";
			link.l1 = "Dziękuję! Będę o tym pamiętał.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "Co mogę dla ciebie zrobić, mój synu? Mów, słucham cię.";
			link.l1 = "Michel powiedział mi, że będziesz mógł pomóc, jeśli kiedykolwiek wpadnę w kłopoty z władzami.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "Jak mogę ci pomóc, mój synu?";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Mam kłopoty z hiszpańskimi władzami.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Wpadłem w kłopoty z holenderskimi władzami.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Przepraszam, myślę, że tym razem poradzę sobie sam.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "Więc, szlachetni señorowie chętnie wsadzą cię do lochów Hawany...";
			link.l1 = "Dokładnie tak, ojcze...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "A więc, sprytni kupcy nie mogą się doczekać, żeby umieścić cię w lochach Willemstad...";
			link.l1 = "Dokładnie tak, ojcze...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Tak, te plotki dotarły również do naszego kościoła. Mogę pomóc ci w twoim dylemacie. To coś, co można rozwiązać. Potrzebuję dwustu pięćdziesięciu złotych dublonów, aby wygładzić twój problem.";
				if (PCharDublonsTotal() >= 250) // Sinistra legendary edition
				{
					link.l1 = "Świetnie! Oto złoto.";
					link.l1.go = "agree";
					iTotalTemp = 250;
				}
				link.l2 = "W takim razie to odpowiedni czas, bym znalazł te dublony.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Tak, plotki o twoich 'wyczynach' dotarły również do naszego kościoła. Splamiłeś swoją reputację, mój synu. Powinieneś być bardziej rozważny. Ale mogę ci pomóc. Potrzebuję pięćset złotych dublonów, aby złagodzić twoje kłopoty.";
					if (PCharDublonsTotal() >= 500) // Sinistra legendary edition
					{
						link.l1 = "Świetnie! Oto złoto.";
						link.l1.go = "agree";
						iTotalTemp = 500;
					}
					link.l2 = "W takim razie to jest odpowiedni czas, bym znalazł te dublony.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Tak, mój synu. Jesteś tak samo zdesperowany jak twój brat... To prawdopodobnie cecha rodzinna. Nie mogę całkowicie naprawić sytuacji, ale mimo to, wierzę, że mogę złagodzić twój ponury kłopot. A później możemy złożyć więcej ofiar, jeśli zechcesz. Potrzebuję na razie sześciuset złotych dublonów i od razu zacznę rozwiązywać twój dylemat.";
					if (PCharDublonsTotal() >= 600) // Sinistra legendary edition
					{
						link.l1 = "Świetnie! Oto złoto.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "W takim razie nadszedł czas, by odnaleźć dubloony.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iTotalTemp); // Sinistra legendary edition
			Log_Info("Przekazałeś "+iTotalTemp+" dublonów");
			PlaySound("interface\important_item.wav");
			dialog.text = "Teraz będziesz musiał poczekać co najmniej dwa tygodnie. Myślę, że w tym czasie uda mi się spotkać i porozmawiać z odpowiednimi ludźmi.";
			link.l1 = "Dziękuję, ojcze! Będę czekał...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            rate = 10 + rand(5);
            rate = GetIntByCondition(HasShipTrait(pchar, "trait23"), rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? I jesteś bratem Michela de Monpera? Dziwne...";
			link.l1 = "Rozumiem twoje wątpliwości, ojcze. Mój ojciec to Henri de Monper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "A-ach, rozumiem. Znałem Henriego de Monpera osobiście. Podejdź do światła, młodzieńcze. Tak! Te same oczy, te same szlachetne rysy! Cieszę się, że widzę syna Henriego de Monpera w moim kościele. Mam nadzieję, że będziesz w stanie pomóc swojemu bratu. Ostatnio miał dużo pecha.";
			link.l1 = "Tak, ojcze. Potrzebuję statku, aby pomóc Michelowi, lecz właśnie przybyłem na Karaiby i mój portfel jest pusty. Mój brat powiedział mi, że mógłbyś pożyczyć mi trochę pieniędzy...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "Michel ci to powiedział?";
			link.l1 = "Ojcze, być może nie brzmię zbyt wiarygodnie, ale to prawda. Im szybciej zdobędę statek, tym szybciej będę mógł wydostać brata z więzienia.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "Rozumiem, mój synu. Słyszę, że mówisz prawdę. Cóż, dla dobra Michela i twego ojca pomogę ci. Mam trochę oszczędności, weź je. Zakładam, że 50 000 pesos i 100 doublonów wystarczy.";
			link.l1 = "Dziękuję, ojcze. Jakie są warunki?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Bez pośpiechu. Pół roku na spłatę wystarczy.";
			link.l1 = "Bardzo dobrze, święty ojcze. Jeszcze raz dziękuję!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Idź z moim błogosławieństwem, synu.";
			link.l1 = "... ";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Wspaniale, mój synu. Mam nadzieję, że te pieniądze ci się przydały.";
			link.l1 = "Nawet nie wiesz jak bardzo, Ojcze! Dziękuję!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, nie mogę uwierzyć własnym oczom! Co cię tu sprowadza?!";
			link.l1 = "Niech mnie Bóg błogosławi, Święty Ojcze, bo przychodzę z dobrą nowiną - żenię się, i chciałbym, abyś był kapłanem na moim weselu.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "Mój synu, to cudowne! Czyli otrzymałeś ten list od ojca i postanowiłeś, jak zwykle, działać według własnego rozumienia? Szczerze się z tego cieszę! Ale obawiam się, że nie mogę ci pomóc, chyba że zdecydujesz się ożenić tutaj, w tym kościele.";
			link.l1 = "Rozumiem, że Wasza misja utknęła w martwym punkcie, Święty Ojcze? Czy mogę w czymś pomóc? Ponieważ ślub odbędzie się w hiszpańskiej kaplicy, oczywiście jest to przygoda, którą chciałbym podjąć, ale jestem zdeterminowany, by zorganizować uroczystość na Martynice. Umiarkowanie wspaniała, w obecności szanowanych świadków i honorowych gości.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "Przykro mi, mój synu, ale cała twoja władza nic nie znaczy przeciwko uporowi najwyższych hierarchów Kościoła katolickiego, zwłaszcza w koloniach hiszpańskich. Nie porozumieliśmy się w kwestii podziału wpływów misji katolickich między naszymi krajami, a teraz jestem tu, jako honorowy gość i honorowy zakładnik. Hiszpanie czekają na lepszą ofertę z naszej strony. Wysłałem wiadomość do Europy, mam nadzieję, że odpowiedź nadejdzie za dwa miesiące i będziemy mogli wznowić negocjacje. Jeśli nie dotrze za dwa miesiące, to na pewno dotrze w ciągu następnych sześciu miesięcy.\nA tak, choć Papież i Mazarin doszli do kompromisu w ostatnich tygodniach, to za wcześnie, by mówić o prawdziwie serdecznych relacjach. Szczerze mówiąc, nie jestem pewien, czy kiedykolwiek dojdziemy do porozumienia. Wydaje mi się, że Palotti po prostu trzyma mnie jako argument w swoich własnych politycznych rozgrywkach. Jednak muszę przyznać, że inkwizytor ma doskonałą kawę!";
			link.l1 = "Nie mam ani sześciu miesięcy, ani dwóch miesięcy! Muszę spełnić życzenie mego ojca, inaczej zmusi mnie do ślubu bez mojej zgody. A jego zdrowie nie jest już takie, jak dawniej, jednak chciałbym mieć czas, by przedstawić mu moją wybrankę i przyszłą panią Monper.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "Obawiam się, że będziesz musiał znaleźć innego księdza na swój ślub, mój synu. Niestety, zostanę tu na długo.";
			link.l1 = "Co byś powiedział, gdybym cię oddzielił od kawy inkwizytora?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "Chętnie przyjąłbym twoją pomoc. Podejrzewam, że nie zostałem wybrany do tej misji przypadkowo. W najgorszym wypadku, po prostu zapomną o opacie Benoit. I choć Pan nakazał mi znosić, obciążony jestem moim wnioskiem, mimo wszystkich jego... błogosławieństw. Ale, powtarzam - mało prawdopodobne, by ojciec Palotti wysłuchał twoich próśb.";
			link.l1 = "W takim razie oszczędzę sobie trochę czasu i nie będę próbował go przekonać. Po prostu opuścimy kościół, jak tylko skończy się msza, i udamy się do mojego statku. Nie wahaj się, Święty Ojcze - widzieli nasze spotkanie i rozpoznają mnie, a będzie o wiele trudniej ci pomóc, jeśli będę musiał wyciągnąć cię z rezydencji gubernatora.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "To ryzykowne, synu, bardzo ryzykowne. Na zewnątrz czeka grupa strażników, aby odprowadzić mnie do posiadłości, a miasto jest pełne żołnierzy.";
			link.l1 = "Zaatakujemy z zaskoczenia, ojcze Benoit. Musisz mi tylko zaufać, a wszystko będzie w porządku. Mam pewne... doświadczenie w tych sprawach.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "Jak sobie życzysz. Ale proszę, zrób to bez zbędnego rozlewu krwi! Sam miałem już tego rodzaju doświadczenia... Prowadź nas, mój synu. Jestem tuż za tobą. Ale nie chwycę za broń, więc nawet nie pytaj.";
			link.l1 = "Nawet o tym nie myślałem, Ojcze. Poradzę sobie. Podążaj za mną, ale uważaj, mogą do nas strzelać.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "Mój synu, nie miałem czasu podziękować ci za moje uwolnienie. Najwidoczniej hiszpański biskup i inkwizytor Palotti chcieli zakłócić ledwo co nawiązane relacje między naszym kardynałem a Stolicą Apostolską, więc działałeś całkowicie w interesie naszego kraju. Znowu. Ale nikt ci nie powie 'dziękuję', oprócz mnie.";
			link.l1 = "Zwykła sprawa, Święty Ojcze. Cieszę się, że udało mi się pomóc. Ale, muszę cię też o coś zapytać, pamiętasz?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Oczywiście! Przejdźmy więc do przyjemnych spraw - Charles, jak idą przygotowania do twojego najważniejszego dnia?";
			link.l1 = "Powoli nabiera to kształtu. Znam kampanie wojskowe, które były przygotowywane łatwiej i szybciej, ale warto!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Oczywiście, mój synu! A przy tej okazji chcę coś wyjaśnić - jak widzisz swoją ceremonię ślubną?";
			link.l1 = "Masz na myśli, jak nadęty?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Oczywiście! Ponieważ muszę przygotować kościół, a być może, zechcesz zaprosić kilka ważnych osób.";
			link.l1 = "Nic specjalnego, Święty Ojcze. Ci, których uważam za naszych przyjaciół, będą czekać na nas gdzie indziej. Tutaj będą tylko kilku urzędników, moi ludzie i kilku zwykłych gapiów.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Cóż, myślę, że poradzimy sobie z niewielką darowizną.";
			link.l1 = "To nie brzmi zbyt strasznie. A ileż to wyniesie taka darowizna w złocie?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "Na chór, uroczystą usługę i inne wydatki - sto pięćdziesiąt, nie więcej. Plus, zwyczajowa darowizna od nowożeńców, w sumie - dwieście dublonów.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Proszę, Święty Ojcze.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Dobrze... Będę musiał przejść się do banku i wrócić.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "A co z twoją ofiarą, mój synu?";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Oto ona, Święty Ojcze.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Tak, tak, wkrótce to przyniosę...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "Pozostaje jeszcze pytanie, na które trzeba odpowiedzieć - kto poprowadzi pannę młodą do ołtarza i poświadczy jej małżeństwo?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson, z Blueweld. Jest Anglikiem, ale osobą szanowaną i przywiązaną do Helen, jakby była jego własną córką, a jej adopcyjna matka to Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Baron Noel Forget, jestem pewien, że odda mi tę przysługę.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Chevalier Philippe de Poincy, jestem pewien, że uczyni mi ten zaszczyt.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Cóż, a kto zaświadczy za pana młodego? Pamiętaj, musi to być człowiek szlachetnego pochodzenia i godnej reputacji.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Baron Noel Forget, jestem pewien, że dołoży wszelkich starań, by mnie uhonorować.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Chevalier Philippe de Poincy, jestem pewien, że uczyni mi ten zaszczyt.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey - szanowany kupiec z Gwadelupy. Wystarczy, że zaopatrzę się w jego ulubiony trunek.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey - szanowany kupiec z Gwadelupy. Muszę tylko zaopatrzyć się w jego ulubiony trunek.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Świetnie, wyślę zaproszenia, ale goście będą potrzebowali trochę czasu, żeby tu dotrzeć. Myślę, że wszystko będzie gotowe za miesiąc, a wskazane osoby przybędą do miasta.";
			link.l1 = "Dobrze! W takim razie mam czas załatwić kilka spraw. Do zobaczenia wkrótce, Święty Ojcze, i życz mi powodzenia!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Świetnie, wyślę zaproszenia, ale goście będą potrzebowali trochę czasu, aby tu dotrzeć. Myślę, że wszystko będzie gotowe za miesiąc, a wskazane osoby dotrą do miasta.";
			link.l1 = "Dobrze! W takim razie mam czas załatwić parę spraw. Do zobaczenia wkrótce, Święty Ojcze i życz mi powodzenia!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Świetnie, wyślę zaproszenia, ale goście będą potrzebowali trochę czasu, żeby tu dotrzeć. Myślę, że wszystko będzie gotowe za miesiąc, a wskazane osoby przybędą do miasta.";
			link.l1 = "Dobrze! To mam czas załatwić parę spraw. Do zobaczenia wkrótce, Święty Ojcze, i życz mi powodzenia!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "Więc nadszedł dzień, mój synu! Wszystko jest gotowe - za parę godzin będziemy mogli zacząć. Wyglądasz blado!";
			link.l1 = "Jestem trochę zdenerwowany, Ojcze Święty.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "To normalne. To najważniejszy dzień w twoim życiu i szczerze się cieszę za ciebie, jak wszyscy, którzy przyszli. Mam nadzieję, że pamiętasz przynajmniej podstawowe modlitwy - nigdy za bardzo nie rozpieszczałeś kościoła swoją uwagą, prawda? Niemniej jednak pomogę ci w każdym przypadku.\nI jeszcze jedna rzecz - o ile rozumiem, panna młoda nie zmieni swoich zasad i nie zobaczymy jej w sukni? Cóż, towarzystwo wyższe zaraz zobaczy kolejną niespodziankę od ciebie - jesteś pełen zaskoczeń. W każdym razie, idź mój synu, doprowadź się do porządku i zaczniemy.";
			link.l1 = "Tak, Święty Ojcze. Zróbmy to.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Pater noster, qui es in caelis, sanctificetur nomen tuum, ad...";
			link.l1 = "...przyjdź królestwo Twoje";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...fiat voluntas tua, sicut in caelo et in terra. Chleba naszego powszedniego daj nam dzisiaj, i odpuść nam nasze winy jako i my...";
			link.l1 = "...jako i my odpuszczamy naszym dłużnikom";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...sicut erat in principio, et nunc et semper, et in saecula saeculorum. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Najdrożsi, zgromadziliśmy się tutaj w obliczu Boga i w obecności tego zgromadzenia, aby połączyć tego mężczyznę i tę kobietę w świętym małżeństwie. Ukochani "+sld.name+" i ty, Charles, wysłuchaliście słowa Bożego, który przypomniał wam o znaczeniu ludzkiej miłości i małżeństwa. Teraz, w imieniu świętego Kościoła, pragnę zakwestionować wasze intencje.\n"+sld.name+" i ty, Charles, czy macie dobrowolne i szczere pragnienie połączenia się ze sobą więzią małżeńską, w obliczu naszego Pana?";
			link.l1 = "Tak.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Czy zamierzacie być sobie wierni w zdrowiu i chorobie, w szczęściu i nieszczęściu, aż do końca życia?";
			link.l1 = "Tak.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Czy macie zamiar kochać i przyjąć dzieci, które nasz Pan wam pośle, i wychować je w wierze chrześcijańskiej?";
			link.l1 = "Tak.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Cóż, zwróćcie się do siebie i złóżcie przysięgę.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Jeśli ktoś z obecnych tutaj zna powód, dla którego ta para nie powinna zostać połączona w świętym małżeństwie, niech przemówi teraz albo niechaj na wieki zamilczy.\nWobec tego, przed obliczem Pana i zgromadzonym tutaj ludem, ogłaszam was mężem i żoną! In nomine Patris, et Filii, et Spiritus Sancti. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Szeptem) Charles, mój synu, proszę cię, tylko ruszaj ustami, nie próbuj wydawać żadnego dźwięku...";
			else sTemp = "";
			dialog.text = "Nowożeńcy, uklęknijcie i módlcie się razem. Oratio fidelium. "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Mineło troche czasu...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Moje gratulacje, synu. Twój ojciec może być z ciebie dumny, a ja również jestem dumny. Bądźcie szczęśliwi i dbajcie o siebie w tym trudnym czasie.";
			link.l1 = "Dziękuję, Święty Ojcze. To była wspaniała msza i cieszę się, że to właśnie Ty ją poprowadziłeś.";
			link.l1.go = "LH_abbat_38";
		break;
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
