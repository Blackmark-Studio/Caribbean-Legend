int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

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
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua"))
			{
				dialog.text = "Witaj, moje dziecko. Cieszę się, że przyszedłeś. Chciałem z tobą porozmawiać.";
				link.l1 = ""+TimeGreeting()+", ojcze. Słucham.";
				link.l1.go = "SharlieEpilog_Benua_1";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_back"))
			{
				link.l99 = "Chciałbym porozmawiać o moim ojcu.";
				link.l99.go = "SharlieEpilog_Benua_3";
			}
			//<-- Эпилог
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
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "Witaj, ojcze. Potrzebujemy Twojej pomocy — w dość nietrywialnej sprawie.";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "Ojcze, zdobyłem potrzebną sumę. Osiemset złotych.";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "Witaj, mój synu. Przypuszczam, że przybyłeś, aby sprawdzić wyniki twojej... khm, waszej sprawy?";
				link.l1 = "Jak zawsze jesteś przenikliwy, ojcze. Nie zwlekaj, powiedz, czy twój człowiek dowiedział się czegoś?";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Дикая Роза
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
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
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
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater"))
			{
				link.l1 = "Wróćmy do kwestii zapłaty za dostarczenie rozkazów.";
				link.l1.go = "SharlieEpilog_Benua_DublonsLater_2";
			}
			if (CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				link.l1 = "Chcę wysłać rozkaz...";
				link.l1.go = "SharlieEpilog_Benua_Delivery";
			}
			//<-- Эпилог
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
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Tak, te plotki dotarły również do naszego kościoła. Mogę pomóc ci w twoim dylemacie. To coś, co można rozwiązać. Potrzebuję " + sTemp + ", aby wygładzić twój problem.";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "Świetnie! Oto złoto.";
					link.l1.go = "agree";
				}
				link.l2 = "W takim razie to odpowiedni czas, bym znalazł te dublony.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Tak, plotki o twoich 'wyczynach' dotarły również do naszego kościoła. Splamiłeś swoją reputację, mój synu. Powinieneś być bardziej rozważny. Ale mogę ci pomóc. Potrzebuję " + sTemp + ", aby złagodzić twoje kłopoty.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Świetnie! Oto złoto.";
						link.l1.go = "agree";
					}
					link.l2 = "W takim razie to jest odpowiedni czas, bym znalazł te dublony.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Tak, mój synu. Jesteś tak samo zdesperowany jak twój brat... To prawdopodobnie cecha rodzinna. Nie mogę całkowicie naprawić sytuacji, ale mimo to, wierzę, że mogę złagodzić twój ponury kłopot. A później możemy złożyć więcej ofiar, jeśli zechcesz. Potrzebuję na razie " + sTemp + " i od razu zacznę rozwiązywać twój dylemat.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Świetnie! Oto złoto.";
						link.l1.go = "agree";
					}
					link.l2 = "W takim razie nadszedł czas, by odnaleźć dubloony.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Teraz będziesz musiał poczekać co najmniej dwa tygodnie. Myślę, że w tym czasie uda mi się spotkać i porozmawiać z odpowiednimi ludźmi.";
			link.l1 = "Dziękuję, ojcze! Będę czekał...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
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
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Moje gratulacje, synu. Twój ojciec może być z ciebie dumny, a ja również jestem dumny. Bądźcie szczęśliwi i dbajcie o siebie w tym trudnym czasie.";
			link.l1 = "Dziękuję, Święty Ojcze. To była wspaniała msza i cieszę się, że to właśnie Ty ją poprowadziłeś.";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "Więc przyszliście do mnie po radę, dzieci moje? Cóż, całkowicie słucham.";
			link.l1 = "Raczej po pomoc, ojcze. Pomoc człowieka mającego kontakty i znającego wielu ludzi...";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "Przepraszam, że ci przerywam, mój synu, ale chcę przypomnieć, że jestem zwykłym opatem, a nie tajnym agentem.";
			link.l1 = "Ale przecież zwykły opat może znać tajnego agenta, prawda? Albo podpowiedzieć, jak do niego dotrzeć?";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "Sprawa, z powodu której przyszliśmy, rzeczywiście dotyczy pewnych dawno zapomnianych tajemnic... Staramy się je wydobyć na światło dzienne.";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Cóż, młodzieńcze, zaczyna mi się to nie podobać. Przejdź do sedna, a potem zobaczymy, czym mogę ci pomóc... i czy w ogóle mogę.";
			link.l1 = "Tak, ojcze. Postaram się przedstawić sytuację krótko...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+", nie trzeba mówić zagadkami — przyznam, że to męczy.";
			link.l1 = "Tak, ojcze. Postaram się przedstawić sytuację krótko...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "Kontynuuj, mój synu.";
			link.l1 = "Moja towarzyszka — Mary Casper — próbuje odnaleźć swojego ojca lub przynajmniej jakieś informacje o nim. Udało nam się ustalić, że był oficerem angielskiej floty i służył na brygu 'Rangler', który rozbił się przy przylądku Catoce w 1638 roku.";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "I masz nadzieję, że wciąż żyje? Po tylu latach?";
			link.l1 = "Nawet jeśli nie przeżył katastrofy, Mary chce wiedzieć, skąd pochodzi jej ojciec, jakim człowiekiem był, jak prowadził życie... Oficjalne dokumenty są skąpe w szczegóły — ale mogą zawierać coś cennego, prawda, ojcze?";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "Masz rację w swoich rozważaniach, mój synu. Rozpoczęliście dobrą i Bogu przyjemną sprawę. Ale wciąż nie mogę pojąć, czego dokładnie ode mnie oczekujecie?";
			link.l1 = "Przecież żyjesz na Archipelagu od dawna, ojcze. Być może znasz kogoś, kto ma dostęp do kolonialnych archiwów dokumentów dotyczących angielskich oficerów floty?";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "Potrzebujemy człowieka mającego dostęp do kolonialnych archiwów, w których przechowywane są informacje o oficerach angielskiej floty. Z pewnością znasz kogoś takiego, ojcze.";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "Rozumiesz, o co prosisz, mój synu? Chodzi nie tylko o to, że takie informacje mogą być tajemnicą wojskową...";
			link.l1 = "A czym jeszcze, ojcze? Powiem od razu...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Rozumiesz, o co prosisz, mój synu? Chodzi nie tylko o to, że takie informacje mogą być tajemnicą wojskową...";
			link.l1 = "A czym jeszcze, ojcze? Powiem od razu...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "Problem tkwi w tych właśnie archiwach kolonialnych. Dwadzieścia lat temu Jamajka była pod Hiszpanami, a Saint Johns i Bridgetown — w ciągłym zagrożeniu napadami. Mało prawdopodobne, by przydzielono tam okręty Królewskiej Floty...";
			link.l1 = "Mówisz o archiwum Admiralicji w Londynie, ojcze?";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "Być może. Dokumenty powinny zostać przekazane do Admiralicji. Zdobycie ich — nie jest proste.";
			link.l1 = "Ale to możliwe, prawda, ojcze?";
			link.l1.go = "WildRose_Abb_11";
		break;
		
		case "WildRose_Abb_11":
			dialog.text = "Nie ma rzeczy niemożliwych, mój synu. Ale będzie to wymagało wysiłku... i zapłaty.";
			link.l1 = "Oczywiście, ojcze. Mam przekazać pieniądze Panu, czy spotkam się z kimś innym?";
			link.l1.go = "WildRose_Abb_12";
		break;

		case "WildRose_Abb_12":
			dialog.text = "Spotkam się z kimś innym osobiście, mój synu. Od Ciebie potrzebuję... ośmiuset dukatów.";
			link.l1 = "Dobrze, ojcze. Ile czasu to zajmie?";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "Zakładam, że dwa miesiące. A przy okazji, nie podałeś mi imienia osoby, której szukacie.";
			link.l1 = "Ta osoba nazywa się Joshua Casper.";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "Zapamiętałem. Jeśli jesteś gotów przekazać całą kwotę teraz — jutro wyślę wiadomość.";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Oczywiście, ojcze. Proszę bardzo, osiemset złotych.";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "Nie, ojcze, nie mam przy sobie takich pieniędzy. Wkrótce wrócę i je przyniosę.";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Bardzo dobrze, "+pchar.name+". Wróć za dwa miesiące — jestem pewien, że do tego czasu będę miał dla Ciebie odpowiedź.";
			link.l1 = "Dziękuję, ojcze. Do zobaczenia wkrótce!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "Jak powiesz, mój synu.";
			link.l1 = "Wkrótce wrócę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;
		
		case "WildRose_Abb_16":
			dialog.text = "Dowiedział się zarówno o Joshua Casperze, jak i jego statku, który okazał się jednak wcale nie być 'Ranglerem'. Bryg o takiej nazwie nigdy nie wchodził w skład Królewskiej Floty.";
			link.l1 = "Hmm... Jestem absolutnie pewien, że statek, na którym służył Joshua Casper, nosił dokładnie tę nazwę... A co z samym Joshuą?";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "Ten człowiek był doskonałym oficerem, z licznymi zasługami i odznaczeniami — wszystko to zapisane w jego aktach osobistych. Choć nie należał do prawdziwej wiary, był godnym kapitanem. Mademoiselle może być dumna z takich korzeni.";
			link.l1 = "To dobre wieści, ojcze. Ale jeśli pozwolisz, wróćmy do statku. Jeśli nie nazywał się 'Rangler' — to jak wtedy?";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "'Cornwall'. Opuścił Plymouth w styczniu 1638 roku z rozkazem dostarczenia żołdu do garnizonów na Antigua i Providence.";
			link.l1 = "Niewiarygodne...";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "Czy statek dotarł do miejsca przeznaczenia, nie wiem. Ale zawijał do Saint Johns. W archiwum portowym zachował się raport kapitana Caspera z 2 czerwca tego roku.";
			link.l1 = "A wiedziałem, że nie jesteś tak prosty, jak chcesz wyglądać, ojcze! Ten dokument, jak przypuszczam, zawiera jakieś ważne informacje?";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "Jesteśmy Ci wdzięczni, ojcze. Skoro wspomniałeś o tym dokumencie — zawierał on coś ważnego?";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Chyba tylko raport o walce z hiszpańskim galeonem 'Toro' przy Azorach, w której zginęła jedna trzecia załogi — przeczytaj raport, wszystko tam jest zawarte.";
			link.l1 = "Jeszcze jedno pytanie: skoro udało Ci się zapoznać z zapisami administracji portu Antigua, czy gdzieś pojawiło się imię Joshua Caspera?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Chyba tylko raport o walce z hiszpańskim galeonem 'Toro' przy Azorach, w której zginęła jedna trzecia załogi — przeczytaj raport, wszystko tam jest zawarte.";
			link.l1 = "Jeszcze jedno pytanie: skoro udało Ci się zapoznać z zapisami administracji portu Antigua, czy gdzieś pojawiło się imię Joshua Caspera?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "Chcesz ode mnie zbyt wiele, mój synu. Jeśli sugerujesz, że mógł przeżyć katastrofę i potem wrócić do floty — w to szczerze wątpię.";
			link.l1 = "Drogi Boże są niezgłębione, ojcze.";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "Zaprawdę, mój synu. Ale widzisz, w jego aktach osobistych zapisano, że Joshua Casper urodził się w 1586 roku...";
			link.l1 = "Chyba masz rację, ojcze.";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "Wiesz, ojcze, przez lata spędzone na Karaibach widziałem tyle rzeczy, że uwierzę nawet w najbardziej nieprawdopodobne historie.";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Oczywiście, taki oficer zasługiwał na śmierć w walce. Ale jeśli patrzeć filozoficznie, w pewnym sensie to też była walka...";
			link.l1 = "Filozofia to nie moja mocna strona, ojcze. Jednak dziękuję za wszystko...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Oczywiście, taki oficer zasługiwał na śmierć w walce. Ale jeśli patrzeć filozoficznie, w pewnym sensie to też była walka...";
			link.l1 = "Filozofia to nie moja mocna strona, ojcze. Jednak dziękuję za wszystko...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "Bóg prowadzi was tą drogą, dzieci moje, a pomoc wam to mój skromny obowiązek. Ale obawiam się, że więcej w tej sprawie nie mogę wam pomóc...";
			link.l1 = "Rozumiem, ojcze. Pozwólcie nam się ukłonić.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		//--> Эпилог
		case "SharlieEpilog_Benua_1":
			dialog.text = "Głęboko niepokoi mnie stan twojego ojca. Nie wiem, czy wspomniał ci o tym w liście, ale w swoim posłaniu do mnie przyznał, że opuszczają go siły fizyczne i przypuszcza, że nie pożyje już długo.";
			link.l1 = "Wspominał, że choroba nie ustępuje... Ale o swoich obawach chyba milczał.";
			link.l1.go = "SharlieEpilog_Benua_2";
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua");
		break;

		case "SharlieEpilog_Benua_2":
			dialog.text = "Więcej powiedzieć ci nie mogę – to wszystko, co mi przekazał, ale jedno jest jasne: boi się stanąć przed Panem, nie zobaczywszy cię ponownie.";
			link.l1 = "Mówił o tym. Przyznam, sam myślałem, by go odwiedzić... Ale...";
			link.l1.go = "SharlieEpilog_Benua_3";
		break;

		case "SharlieEpilog_Benua_3":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_1"))
			{
				dialog.text = "Synu mój, tylko Panu wiadomo, ile każdemu z nas zostało. Nie zwlekaj ze spotkaniem: czasem jeden uścisk potrafi przynieść duszy spokój, którego nie da tysiąc modlitw.";
				npchar.SharlieEpilog_BenuaRazgovor_1 = true;
			}
			else
			{
				dialog.text = ""+pchar.name+", mam nadzieję, że nie będziesz dłużej odkładać wizyty u niego? Pamiętaj, że czas działa na twoją niekorzyść...";
			}
			link.l1 = "Ma ojciec rację, ojcze. Natychmiast rozpocznę przygotowania do wyprawy. Zważywszy na moje obecne stanowisko – mogę potrzebować sporo czasu, by wszystko uporządkować...";
			link.l1.go = "SharlieEpilog_Benua_5";
			link.l2 = "Rozumiem obawy ojca, święty ojcze, i obiecuję się nad tym zastanowić. Ale teraz mam pilne sprawy, które nie mogą czekać. Wrócimy do tej rozmowy później.";
			link.l2.go = "SharlieEpilog_Benua_4_exit";
		break;
		
		case "SharlieEpilog_Benua_4_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_2");
		break;
		
		case "SharlieEpilog_Benua_5":
			dialog.text = "Jeśli masz długi, synu mój, radziłbym zacząć od ich spłaty. Lichwiarze to ludzie bardzo pamiętliwi: mogą poważnie zaszkodzić twojej reputacji, a wraz z nią – dobremu imieniu całej rodziny, nawet w Starym Świecie\n"+
			"Co do reszty – w imię mojej przyjaźni z twoim ojcem i na chwałę Pana – udzielę ci wszelkiej możliwej pomocy. Możesz przekazać pisemne instrukcje, a ja dopilnuję, by dotarły do adresatów na czas. Będziesz musiał jedynie opłacić usługi kurierskie. Myślę, że dwieście doblonów wystarczy na pokrycie kosztów przesyłek.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Dziękuję, święty ojcze. Pańska pomoc bardzo się przyda. Proszę, oto one.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Dziękuję za troskę, święty ojcze. Niestety, w tej chwili nie mam przy sobie wymaganej kwoty. Wrócimy do tej sprawy później.";
			link.l2.go = "SharlieEpilog_Benua_DublonsLater";
			SharlieEpilog_Benua_Dlg_1();
		break;
		
		case "SharlieEpilog_Benua_DublonsLater":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_3");
		break;
		
		case "SharlieEpilog_Benua_DublonsLater_2":
			dialog.text = "Oczywiście, "+pchar.name+". Rozumiem, że przyniosłeś dwieście doblonów?";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Oczywiście. Proszę, oto one.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Niestety, nadal nie mam potrzebnej sumy.";
			link.l2.go = "exit";
		break;
		
		case "SharlieEpilog_Benua_6":
			dialog.text = "Wspaniale, synu mój.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			RemoveDublonsFromPCharTotal(200);
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater");
		break;
		
		case "SharlieEpilog_Benua_Delivery":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				dialog.text = "A więc, od czego wolisz zacząć?";
				npchar.SharlieEpilog_BenuaRazgovor_2 = true;
			}
			else
			{
				dialog.text = "Kogo i o czym chcesz powiadomić?";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona"))
			{
				link.l1 = "Pewnego razu udało mi się odnaleźć wyspę, której nie ma na mapach. Było tam już kilku osadników, nad którymi objąłem opiekę. Po moim odpłynięciu będą potrzebowali nowego 'gubernatora'.";
				link.l1.go = "SharlieEpilog_Benua_IslaMona";
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Baron"))
			{
				link.l2 = "Chciałbym wysłać list do Marcusa Tiraxa z La Vegi. Sprawa nie jest pilna, ale list musi dotrzeć na czas.";
				link.l2.go = "SharlieEpilog_Benua_Baron";
			}
			if (CheckCharacterItem(PChar, "patent_fra") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Patent"))
			{
				link.l3 = "Mam ważny patent francuski – chcę powiadomić kancelarię w Capsterville o swojej decyzji.";
				link.l3.go = "SharlieEpilog_Benua_Patent";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Money"))
			{
				link.l4 = "Święty ojcze, przez lata spędzone na tych ziemiach udało mi się zgromadzić niemały majątek. Ale zanim stanie się on własnością mojej rodziny, chciałbym go oczyścić. Zmyć krew, z którą być może jest związany. Pragnę opuścić ten kraj nie jako zbój z łupem, lecz jako człowiek o czystym sumieniu i dobrej reputacji w oczach społeczeństwa.";
				link.l4.go = "SharlieEpilog_Benua_Money";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Svenson") && CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona_France"))
			{
				link.l5 = "Chciałbym powiadomić Jana Svensona z Blueveldu o swoim wyjeździe. Byłoby niegrzecznie opuścić archipelag bez słowa.";
				link.l5.go = "SharlieEpilog_Benua_Svenson";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Houk"))
			{
				link.l6 = "Chcę poinformować rodzinę Houków z Maroon Town o mojej podróży.";
				link.l6.go = "SharlieEpilog_Benua_Houk";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Jino"))
			{
				link.l7 = "Chcę powiadomić Gino Guinelego z Saint John's o wyjeździe do Starego Świata.";
				link.l7.go = "SharlieEpilog_Benua_Jino";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L"))
			{
				link.l85 = "To wszystko, ojcze... Wygląda na to, że jestem gotów wyruszyć w drogę.";
				link.l85.go = "SharlieEpilog_Benua_TimeToGoHome";
			}
			link.l99 = "Przepraszam, święty ojcze, muszę już iść.";
			link.l99.go = "SharlieEpilog_exit";
		break;
		
		case "SharlieEpilog_exit":
			DialogExit();
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
		case "SharlieEpilog_Benua_Jino":
			dialog.text = "Oczywiście, synu mój.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Jino_2";
			pchar.questTemp.SharlieEpilog_Jino = true;
		break;
		
		case "SharlieEpilog_Benua_Jino_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Jino_3";
			AddQuestRecord("SharlieEpilog", "8_1");
		break;
		
		case "SharlieEpilog_Benua_Jino_3":
			dialog.text = "...";
			link.l1 = "Gotowe. Można wysyłać.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Houk":
			dialog.text = "Oczywiście, synu mój.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Houk_2";
			pchar.questTemp.SharlieEpilog_Houk = true;
		break;
		
		case "SharlieEpilog_Benua_Houk_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Houk_3";
			AddQuestRecord("SharlieEpilog", "8");
		break;
		
		case "SharlieEpilog_Benua_Houk_3":
			dialog.text = "...";
			link.l1 = "Gotowe. Można wysyłać.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Svenson":
			dialog.text = "Jan Svenson z Blueveldu... Zapamiętam. Daj list – i dziś jeszcze ruszy w drogę.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Svenson_2";
			pchar.questTemp.SharlieEpilog_Svenson = true;
		break;
		
		case "SharlieEpilog_Benua_Svenson_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Svenson_3";
			AddQuestRecord("SharlieEpilog", "7");
		break;
		
		case "SharlieEpilog_Benua_Svenson_3":
			dialog.text = "...";
			link.l1 = "Dom Jana znaleźć nietrudno. Wystarczy zapytać kogokolwiek – trudno o osobę w całym Blueveldzie, która nie wiedziałaby, kim jest i gdzie mieszka.";
			link.l1.go = "SharlieEpilog_Benua_Svenson_4";
		break;
		
		case "SharlieEpilog_Benua_Svenson_4":
			dialog.text = "Nie martw się, synu mój, nasi ludzie znają się na swoim fachu. List trafi tam, gdzie trzeba – i na czas.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money":
			dialog.text = "Chcesz, żeby Kościół pobłogosławił złoto zdobyte nieuczciwie?";
			link.l1 = "Raczej zdobyte na służbie Francji i Jego Królewskiej Mości.";
			link.l1.go = "SharlieEpilog_Benua_Money_2";
		break;
		
		case "SharlieEpilog_Benua_Money_2":
			dialog.text = "Rozumiem cię, synu mój. Mógłbym powiedzieć, że Kościół nie oczyszcza pieniędzy i nie anuluje sposobu, w jaki zostały zdobyte. Ale czy byłby z tego pożytek, jeśli głodni nadal będą głodować, bezdomni spać pod gołym niebem, a chorzy umierać bez pomocy? Jestem gotów udzielić błogosławieństwa – w zamian za to, że niewielka część tych środków posłuży nie tobie, lecz tym, którzy potrzebują pomocy.";
			link.l1 = "Oczywiście, święty ojcze, jestem gotów ofiarować tyle, ile uznacie za stosowne.";
			link.l1.go = "SharlieEpilog_Benua_Money_3";
		break;
		
		case "SharlieEpilog_Benua_Money_3":
			dialog.text = "A więc – jaką kwotę chcesz zabrać ze sobą?";
			link.l1 = "Dziesięć milionów peso.";
			link.l1.go = "SharlieEpilog_Benua_Money_4";
			if (sti(pchar.Money) >= 250000)
			{
				link.l2 = "Dwadzieścia pięć milionów peso.";
				link.l2.go = "SharlieEpilog_Benua_Money_5";
			}
			if (sti(pchar.Money) >= 500000)
			{
				link.l3 = "Pięćdziesiąt milionów peso.";
				link.l3.go = "SharlieEpilog_Benua_Money_6";
			}
		break;
		
		case "SharlieEpilog_Benua_Money_4":
			dialog.text = "W takim razie darowizna w wysokości stu tysięcy peso będzie wystarczająca. Dzięki tym środkom będziemy mogli organizować posiłki dla potrzebujących jeszcze przez wiele miesięcy. Czy jesteś gotów przekazać tę kwotę już teraz, synu mój?";
			link.l1 = "Oczywiście. Proszę, oto one. Cieszę się, że mogę pomóc tym, którzy naprawdę tego potrzebują, i jestem pewien, że pod waszym nadzorem te pieniądze posłużą sprawie mądrze i uczciwie.";
			link.l1.go = "SharlieEpilog_Benua_Money_4_1";
			link.l2 = "Wybaczcie, muszę to jeszcze raz dokładnie przemyśleć.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money_5":
			dialog.text = "W takim razie twoja darowizna powinna wynieść dwieście pięćdziesiąt tysięcy peso. Środki te pozwolą nam zbudować sierociniec, który będzie rozsławiał twoje imię i przynajmniej przez pewien czas zapewni jego utrzymanie. Czy jesteś gotów przekazać tę kwotę już teraz, synu mój?";
			link.l1 = "Oczywiście. Proszę, oto one. Cieszę się, że mogę pomóc tym, którzy naprawdę tego potrzebują, i jestem pewien, że pod waszym nadzorem te pieniądze posłużą sprawie mądrze i uczciwie.";
			link.l1.go = "SharlieEpilog_Benua_Money_5_1";
			link.l2 = "Wybaczcie, muszę to jeszcze raz dokładnie przemyśleć.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money_6":
			dialog.text = "Cóż, wygląda na to, że nie traciłeś czasu, "+pchar.name+". Myślę, że darowizna w wysokości pięciuset tysięcy peso będzie w pełni wystarczająca. Dzięki takiemu wkładowi będziemy mogli zbudować szpital i zapewnić mu wszystko, co potrzebne, na długie lata. Czy jesteś gotów przekazać tę kwotę już teraz, synu mój?";
			link.l1 = "Oczywiście. Proszę, oto one. Cieszę się, że mogę pomóc tym, którzy naprawdę tego potrzebują, i jestem pewien, że pod waszym nadzorem te pieniądze posłużą sprawie mądrze i uczciwie.";
			link.l1.go = "SharlieEpilog_Benua_Money_6_1";
			link.l2 = "Wybaczcie, muszę to jeszcze raz dokładnie przemyśleć.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money_4_1":
			dialog.text = "Doskonale, synu mój.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -100000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "10000000");
			AddQuestUserData("SharlieEpilog", "tSum", "100000");
			pchar.questTemp.SharlieEpilog_gold_S = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;
		
		case "SharlieEpilog_Benua_Money_5_1":
			dialog.text = "Doskonale, synu mój.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -250000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "25000000");
			AddQuestUserData("SharlieEpilog", "tSum", "250000");
			pchar.questTemp.SharlieEpilog_gold_M = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;
		
		case "SharlieEpilog_Benua_Money_6_1":
			dialog.text = "Doskonale, synu mój.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -500000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "50000000");
			AddQuestUserData("SharlieEpilog", "tSum", "500000");
			pchar.questTemp.SharlieEpilog_gold_L = true;
			pchar.questTemp.SharlieEpilog_Money = true;
			Achievment_Set("ach_CL_205");
		break;
		
		case "SharlieEpilog_Benua_Patent":
			dialog.text = "Jaką więc podejmiesz decyzję, synu mój?";
			link.l1 = "Mimo że czeka mnie długa podróż, chciałbym zachować patent – podobnie jak moją lojalność wobec Francji i Króla.";
			link.l1.go = "SharlieEpilog_Benua_Patent_2";
			link.l2 = "Postanowiłem zrzec się patentu. Przede mną długa droga i nie wiem, kiedy powrócę. Sądzę, że rozsądniej będzie nie dźwigać ciężaru obowiązków służbowych i zasad, których być może nie zdołam wypełniać.";
			link.l2.go = "SharlieEpilog_Benua_Patent_6";
			pchar.questTemp.SharlieEpilog_Patent = true;
		break;
		
		case "SharlieEpilog_Benua_Patent_2":
			dialog.text = "Cieszę się, że doszedłeś do takiej decyzji, synu mój. Nasze państwo potrzebuje dziś silnych i odważnych rycerzy bardziej niż kiedykolwiek. Powiedz jednak, "+pchar.name+", czy nie przyszło ci na myśl, by się ustatkować, odnaleźć dom i przestać narażać życie co godzinę? Albowiem nie na wieczność człowiek ma wystawiać się na próbę w ogniu.";
			link.l1 = "Nie jestem pewien, czy potrafiłbym po prostu siedzieć z założonymi rękami, święty ojcze. Lecz jak powiedziano w Piśmie: 'nawet wojownikom Pana dany jest odpoczynek, gdy ich trud dobiegnie końca'. Choć wciąż daleko mi do końca tej drogi, mam nadzieję sam wybrać dzień, w którym na zawsze włożę klingę do pochwy.";
			link.l1.go = "SharlieEpilog_Benua_Patent_3";
		break;
		
		case "SharlieEpilog_Benua_Patent_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_4";
			AddQuestRecord("SharlieEpilog", "5_2");
		break;

		case "SharlieEpilog_Benua_Patent_4":
			dialog.text = "Doskonale, synu mój. Myślę, że Jego Królewska Mość nie pozostawi bez uwagi twojej lojalności i oddania.";
			link.l1 = "Obecnie moje myśli są zupełnie gdzie indziej... Mam nadzieję, że ojciec nie będzie nalegał, abym zamieszkał w naszym majątku. Nie sądzę, bym był na to gotów. Na szczęście będę miał dość czasu, by to przemyśleć.";
			link.l1.go = "SharlieEpilog_Benua_Patent_5";
		break;

		case "SharlieEpilog_Benua_Patent_5":
			dialog.text = "...";
			link.l1 = "Zatem wróćmy teraz do spraw doczesnych.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Patent_6":
			dialog.text = "To rozsądna decyzja. Muszę jednak zauważyć, że twoje odejście znacznie osłabi potęgę Francji na tych wodach.";
			link.l1 = "Jestem pewien, że pod wodzą Jego Królewskiej Mości nie brakuje godnych kapitanów, by wielkość Francji pozostała niezachwiana.";
			link.l1.go = "SharlieEpilog_Benua_Patent_7";
		break;
		
		case "SharlieEpilog_Benua_Patent_7":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_8";
			AddQuestRecord("SharlieEpilog", "5_1");
		break;

		case "SharlieEpilog_Benua_Patent_8":
			dialog.text = "...";
			link.l1 = "To wszystko. Jakby ciężar spadł z ramion. Szczerze mówiąc, zapomniałem już, kim byłem, kiedy przybyłem tu, na Karaiby... Tyle rzeczy się wydarzyło.";
			link.l1.go = "SharlieEpilog_Benua_Patent_9";
		break;

		case "SharlieEpilog_Benua_Patent_9":
			dialog.text = "Możliwe, że słyszałeś to już nieraz, synu mój: ścieżki Pana są niezbadane. Wszystko, co zostało ci przeznaczone z góry, przeszedłeś z godnością. Wierzę jednak, że twoje próby jeszcze się nie skończyły, a być może twoja chwała dopiero zmierza ku swemu zenitowi.";
			link.l1 = "Chwała ciąży, święty ojcze. Nie każdy, kto do niej dąży, potrafi unieść jej ciężar... i zatrzymać się w porę.";
			link.l1.go = "SharlieEpilog_Benua_Patent_10";
		break;

		case "SharlieEpilog_Benua_Patent_10":
			dialog.text = "...";
			link.l1 = "Zatem wróćmy teraz do spraw doczesnych.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Baron":
			dialog.text = "Synu mój, masz sprawy z głową piratów?";
			link.l1 = "Zna ojciec Strażnika Kodeksu?";
			link.l1.go = "SharlieEpilog_Benua_Baron_2";
			pchar.questTemp.SharlieEpilog_Baron = true;
		break;
		
		case "SharlieEpilog_Benua_Baron_2":
			dialog.text = "Ze Strażnikiem Kodeksu? Nie, jego nie znam. Znam Marcusa Tiraxa – kata, za którym ciągnie się tyle krwi, że nawet setki lat spędzonych na modlitwach nie wystarczą, by uzyskać przebaczenie Pana. A jednak... naprawdę masz z nim interesy?";
			link.l1 = "Musiałem zdobyć jego zaufanie... żeby wyciągnąć Michela z więzienia. Tak czy inaczej, zrozumiałem swój błąd i nie zamierzam już utrzymywać kontaktu. Tym listem zrywam ostatnią nić, która nas łączy.";
			link.l1.go = "SharlieEpilog_Benua_Baron_3";
			link.l2 = "Teraz to już nieważne. Opuszczam archipelag, i nasze drogi same się rozejdą, święty ojcze.";
			link.l2.go = "SharlieEpilog_Benua_Baron_7";
		break;
		
		case "SharlieEpilog_Benua_Baron_3":
			dialog.text = "A co to za nić, synu mój? Mam nadzieję, że nie splamiona krwią niewinnych?";
			link.l1 = "Formalnie byłem uznawany za przywódcę pirackiej osady Le-François. W rzeczywistości wszystkim kierował ktoś inny. Dziś wyrzekam się tytułu barona piratów – definitywnie i bez powrotu.";
			link.l1.go = "SharlieEpilog_Benua_Baron_4";
		break;
		
		case "SharlieEpilog_Benua_Baron_4":
			dialog.text = "Cieszę się, że wkroczyłeś na właściwą drogę, synu mój, i będę się modlił o zbawienie twojej duszy. Każdy może się potknąć, lecz Pan wybacza tylko tym, których skrucha jest szczera.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Baron_5";
		break;
		
		case "SharlieEpilog_Benua_Baron_5":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_6";
			AddQuestRecord("SharlieEpilog", "4_1");
		break;
		
		case "SharlieEpilog_Benua_Baron_6":
			dialog.text = "Doskonale, "+pchar.name+". Przekaż mi list – dopilnuję, by dotarł do adresata. I nie zapominaj się modlić, synu mój. Tylko skrucha i modlitwa mogą obmyć duszę nawet z najcięższych grzechów.";
			link.l1 = "Dziękuję, święty ojcze. Może nie wszystko jeszcze stracone.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Baron_7":
			dialog.text = "Niezależnie od tego, jak wielki jest grzech, synu mój, drzwi przebaczenia zawsze pozostają otwarte. Skrucha, modlitwa i dobre uczynki oczyszczają duszę tak, jak deszcz zmywa kurz z kamienia.";
			link.l1 = "Wszystko w swoim czasie, święty ojcze. Teraz muszę zająć się sprawami doczesnymi.";
			link.l1.go = "SharlieEpilog_Benua_Baron_8";
		break;
		
		case "SharlieEpilog_Benua_Baron_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_9";
			AddQuestRecord("SharlieEpilog", "4_2");
		break;
		
		case "SharlieEpilog_Benua_Baron_9":
			dialog.text = "...";
			link.l1 = "Proszę, oto on.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_IslaMona":
			dialog.text = "Dobrze, synu mój, że postanowiłeś zadbać o tych ludzi i nie zapomniałeś o nich. Komu chciałbyś przekazać tę wyspę?";
			link.l1 = "Myślę, że powinien nad nią powiewać francuski sztandar. Prędzej czy później ktoś ją odkryje, a inne państwa mogą zechcieć ją przejąć. Nie mogę do tego dopuścić.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France";
			link.l2 = "Ta wyspa i jej mieszkańcy zasługują na to, by żyć wolni, a nie pod królewską władzą. Chcę wysłać list do mojego przyjaciela, Jana Svensona z Blueveldu. Wierzę, że zgodzi się objąć ją swoją opieką. Proszę jednak, święty ojcze – zachowaj tę rozmowę w tajemnicy, dla dobra i bezpieczeństwa tych ludzi.";
			link.l2.go = "SharlieEpilog_Benua_IslaMona_Pirate";
			pchar.questTemp.SharlieEpilog_IslaMona = true;
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France":
			dialog.text = "Postępujesz mądrze, "+pchar.name+". Pod opieką Króla ta wyspa zazna porządku i bezpieczeństwa.";
			link.l1 = "Wyślę stosowny list do kancelarii w Capsterville oraz do ludzi na wyspie. Wspomnę o współrzędnych na kopercie.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_2";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_France_3";
			pchar.questTemp.SharlieEpilog_IslaMona_France = true;
			AddQuestRecord("SharlieEpilog", "3_1");
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_3":
			dialog.text = "...";
			link.l1 = "Proszę, oto on. Mam nadzieję, że wasi ludzie zdołają odnaleźć wyspę, zanim przybędzie tam flota Jego Królewskiej Mości.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_4";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_4":
			dialog.text = "Nie martw się, synu mój. Powierzę dostarczenie tych listów najlepszym kurierom.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_Pirate":
			dialog.text = "Nie mnie oceniać, czy twoja droga jest słuszna, synu mój. Prędzej czy później ktoś odkryje tę wyspę, a jedna z potęg zechce ją sobie przywłaszczyć. To tylko kwestia czasu. Ale skoro podjąłeś taką decyzję – widocznie taka była wola Boża. Nie obawiaj się – nie narażę tych ludzi na niebezpieczeństwo i odmówię za nich modlitwę.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_Pirate_2";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_Pirate_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_Pirate_3";
			pchar.questTemp.SharlieEpilog_IslaMona_Pirate = true;
			AddQuestRecord("SharlieEpilog", "3_2");
		break;
		
		case "SharlieEpilog_Benua_IslaMona_Pirate_3":
			dialog.text = "Jan Svenson z Blueveldu, prawda?";
			link.l1 = "Dokładnie tak, święty ojcze. A drugi list należy dostarczyć bezpośrednio na wyspę. Współrzędne są zapisane na kopercie.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome":
			dialog.text = "Doskonale, synu mój. O ile się nie mylę, przybyłeś tu na pinasie '"+GetShipName("Ulysse")+"'?";
			link.l1 = "Zgadza się. Ale dlaczego ojciec pyta?";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_2";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_2":
			dialog.text = "Ponieważ ten okręt został niedawno wystawiony na aukcji. A ty, Charles, masz szansę wrócić do domu na tym samym statku – tylko już jako jego kapitan.";
			link.l1 = "Hm... Muszę przyznać, że to kusząca propozycja. Chyba zajrzę do administracji portu. Dziękuję, święty ojcze.";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_3";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_3":
			DialogExit();
			NextDiag.CurrentNode = "First Time";
			AddDialogExitQuestFunction("SharlieEpilog_PU_Ulysse_1");
		break;
		//<-- Эпилог
		
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
