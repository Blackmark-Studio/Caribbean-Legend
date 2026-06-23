// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zjeżdżaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "O! Tutaj jesteś, przyjacielu. A ja myślałem, że muszę cię sam znaleźć. Potrzebuję cię, przyjacielu.";
				link.l1 = "Dziś jesteś podejrzanie przyjazny, Richardzie. No cóż, słucham.";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Czego chcesz? Szczerze mówiąc, nie jestem dziś w dobrym nastroju. Właściwie zapomniałem, kiedy ostatnio byłem w nim.";
				link.l1 = "Naprawdę jest aż tak źle, kumplu?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Czy opowiesz mi najnowsze plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Źle? Nie, nie jest źle. Po prostu nie jestem w odpowiednim nastroju. Więc czego chciałeś?";
			link.l1 = "Po prostu chciałem cię poznać. Jestem tu nowy, więc po prostu spaceruję po Wyspie i poznaję ludzi.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Naprawdę? No dobrze. Jestem Richard Shambon. Dawno temu handlowałem cennymi towarami, a niektóre z nich były nielegalne, ale przez ostatnie dziewięć lat przeszukiwałem wraki statków, szukając złomu i wymieniając go na jedzenie i złoto.";
			link.l1 = "I ja jestem "+GetFullName(pchar)+", kapitanie...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Masz na myśli byłego kapitana, ha-ha?";
			link.l1 = "Cóż, właściwie mój statek jest teraz w Blueweld. A tutaj przypłynąłem na tartanie.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "„Naprawdę? Niemożliwe! A gdzie teraz jest twoja tartana?”";
			link.l1 = "Hm... na dnie.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "A-ach... A myślałem... Nieważne, druh, lepiej wypiję trochę rumu...";
			link.l1 = "Powodzenia z tym. Miło było z tobą porozmawiać. Do zobaczenia!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi ostatnie plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "I czy byłem inny wcześniej? Daj spokój, każdy miewa złe dni! Powiedz mi, chodzą plotki na Wyspie, że jesteś doskonałym wojownikiem. Czy to prawda?";
			link.l1 = "Nie wiem, co mówią, ale wiem, jak posługiwać się mieczem, jeśli o to pytasz.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "Zrozumiałem. Widzę, że te plotki były prawdziwe... Słuchaj, "+pchar.name+", pamiętasz, jak mówiłem ci o zewnętrznym pierścieniu? I o cennych rzeczach, które tam znajdziesz?";
			link.l1 = " Wszyscy lubicie mówić o tym pierścieniu... I wszyscy mówicie to samo.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "Co tu dużo mówić, ha-ha! Dobrze. Przejdę do rzeczy. (ścisza głos) Znalazłem nienaruszony statek na zewnętrznym pierścieniu, jest w dobrym stanie, co jest dość rzadkie\nStatek jest duży, to pinasa. Została tu przygnana niedawno, około dwóch miesięcy temu lub nawet mniej. Inni jeszcze jej nie znaleźli, więc jest szansa zarobić trochę pieniędzy, plądrując jej ładownie i kajuty.";
			link.l1 = "Miło, cieszę się z tego. Ale jak to mnie dotyczy? Chcesz mnie prosić, żebym poszedł tam z tobą?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "Dokładnie! Słuchaj. Dziób pinasy jest uszkodzony. Te przeklęte kraby wykorzystały dziurę, by się dostać do środka i zbudowały tam cholernie gniazdo. Wkradanie się tam, gdy są w środku, nie wchodzi w grę, a ja nie mam pojęcia, jak wspiąć się na wyższy pokład.\nNigdy nie byłem dobrym wojownikiem i od lat nie dotknąłem ostrza, więc nie będę w stanie sam zabić tych stworzeń. Dlatego przyszedłem do ciebie.";
			link.l1 = "Więc proponujesz, żebym zabił wszystkie kraby na tym statku, prawda?";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "Tak. Zawarzymy umowę. Pokażę ci drogę do statku, a ty wyeliminujesz kraby. Podzielimy się wszystkimi łupami, które tam znajdziemy. To uczciwa umowa - ja znalazłem statek, a ty go oczyścisz.";
			link.l1 = "Nie, kumplu, nie interesuje mnie to. To nie w moim stylu walczyć z krabami wewnątrz półzatopionego statku dla jakichś wątpliwych trofeów. Znajdź sobie innego śmiałka, który wyciągnie dla ciebie kasztany z ognia.";
			link.l1.go = "ring_exit";
			link.l2 = "Interesujące... Od dawna myślałem, żeby sprawdzić zewnętrzny pierścień. Umowa stoi! Zabiję kraby.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "Szkoda... Popełniłeś błąd. Na statkach zewnętrznego pierścienia jest mnóstwo soczystych rzeczy... I nikt wcześniej nie był na tym statku. Dobrze, to twoja wola. Żegnaj...";
			link.l1 = "Żegnaj, kumplu...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "Cieszę się, że miałem rację co do ciebie, przyjacielu. Mam przeczucie, że znajdziemy w niej wiele interesujących rzeczy...";
			link.l1 = "Zobaczymy. Wiesz, ile tam jest krabów?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "Myślę, że około czterech lub pięciu z nich... Cóż, średnio.";
			link.l1 = "Działa dla mnie. Kiedy wyruszamy?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "Chodźmy tam jutro, musimy się przygotować. Weź antidota od brata Juliana, szczypce kraba są trujące. Ostrożność jest wskazana. Spotkajmy się jutro o ósmej rano na 'skośnym pokładzie'. Wiesz, gdzie to jest?";
			link.l1 = "Nie wiem. Wyjaśnij.";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "Za 'San Augustine' znajduje się wrak starego statku. Jej dziób jest pod wodą, a rufa uniesiona wysoko. Dlatego nazywają ją 'ukośny pokład'. Można tam dotrzeć tylko płynąc. Po prostu zacznij pływać z miejsca pod mostem i zawróć z dowolnej strony 'San Augustine'. Popłyniemy razem stąd.";
			link.l1 = "Zgoda. Do zobaczenia jutro!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "8 godzina, 'skośny pokład'...";
			link.l1 = "Tak, tak, pamiętam to...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "Aha, tu jesteś, przyjacielu. Gotów zrobić sałatkę z krabów?";
			link.l1 = "Z pewnością!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "Bardzo dobrze. Teraz odwróć głowę na zewnętrzny pierścień i spójrz. Widzisz tam dwa wraki statków wystające z wody?";
			link.l1 = "Hm... Tak, robię.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "Teraz spójrz między nimi na zewnętrzny pierścień. Widzisz galeon z podniesionym dziobem? Jest właśnie w naszą stronę. Przyjrzyj się uważnie.";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "Myślę, że to widzę... Tak!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "To nasz cel. Płyń prosto i nie skręcaj. Pokażę ci drogę powrotną, gdy dotrzemy do zewnętrznego pierścienia. Wejście do ładowni to dziura w dziobie statku. Wiedz, że nie wejdę tam, dopóki nie zabijesz wszystkich krabów.";
			link.l1 = " Tak, mieliśmy wczoraj umowę, pamiętam. Ty pokażesz statek, a ja zabiję kraby. Popływamy?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "Jasne! Pójdę za tobą.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "Heh, dobra robota! Zabiłeś całe to plugastwo!";
			link.l1 = "  Pamiętam, że ktoś mówił mi o 'czterech lub pięciu' krabach... Przypomnij mi, kto to był?";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "Kumpel, nigdy nie wchodziłem do ładowni, żeby je dokładnie policzyć. Po prostu zajrzałem przez otwór. Nie miałem zamiaru cię okłamywać.";
			link.l1 = "Cokolwiek. Sprawdźmy ładownię...";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "Oczywiście! Właśnie dlatego tu jesteśmy, prawda?";
			link.l1 = "Dokładnie! Nie traćmy czasu...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "Poczekaj chwilę, kumplu, jeszcze nie sprawdziłem wszystkich miejsc, które chciałem. Szukaj lepiej, może znajdziesz więcej wartościowych rzeczy.";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "Nic specjalnego. Szkoda, że nie ma tu cennych towarów. W beczkach są zapasy, a w skrzyniach kopra. Jednak znalazłem też skrzynię z drogim winem. A co ty masz?";
			link.l1 = "Też nic ciekawego. Kilka skrzyń jest całkiem wartościowych, ale reszta to peklowana wołowina i kopra, jak powiedziałeś.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "Niewystarczająco... Chodźmy na górę i sprawdźmy górny pokład i kajuty.";
			link.l1 = "Chodźmy.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "Do diabła! Spójrz tylko na to! Cholerni, piekielni kraby dostały się na pokład! I jak udało im się tego dokonać?!";
			link.l1 = "Nie bądź tchórzem! Zostań tutaj, nie ruszaj się i nie zwracaj na siebie ich uwagi. Natychmiast się z nimi rozprawię...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "Ha! Więc opowieści o twych umiejętnościach szermierczych były prawdziwe! Gdybym tu był sam, skoczyłbym za burtę...";
			link.l1 = "Słuchaj, a jak stałeś się przemytnikiem w przeszłości, co? Czy może uciekałeś od wszystkich?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "Przyjacielu, po pierwsze, byłem młodszy, silniejszy i bardziej lekkomyślny. Po drugie, nie jestem najemnikiem, by toczyć wojny - jestem przemytnikiem i zawsze staramy się unikać rozlewu krwi. Po trzecie, zawsze byłem za żaglami i sterem, a nie za ostrzami i pistoletami. I w końcu, lata życia tutaj mnie zmiękczyły\nWięc nie obwiniaj mnie. Sprawdźmy górny pokład. Wygląda na to, że statek był w poważnej walce - spójrz na szkody...";
			link.l1 = "Masz rację. Statek na pewno był pod ciężkim ostrzałem. Dobrze, poszukajmy czegoś interesującego.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "Tak. I musimy znaleźć wejścia do wewnętrznych komnat.";
			link.l1 = "Umowa stoi, nie traćmy czasu. Zawołaj mnie, jeśli zobaczysz kraba.";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "Znowu nic wartościowego... Znalazłem kilka interesujących drobiazgów i to wszystko. Ale to w porządku, zwykle na pokładach nie ma cennych skarbów. Najlepsze muszą być w kajutach. Tam jest wejście do kwater kapitana. Sprawdźmy to.";
			link.l1 = "Uważaj, kto wie, co tam na nas czeka. Może lepiej, żebym wszedł tam pierwszy?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "Chodźmy, "+pchar.name+"  Nie będę się już więcej chować za twoimi plecami. To wstyd, to pewne...";
			link.l1 = "Idź dalej...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "Wygląda na to, że miałem szczęście - ani krabów, ani innego paskudztwa tutaj. A teraz przewrócimy tę kabinę do góry nogami, cholera, przysięgam, że zaczynam się wściekać. Znalazłem tylko dwa cholerne tuziny dublonów i kilka drobiazgów!";
			link.l1 = "Spokojnie. Miałeś rację, wszystkie cenne rzeczy zawsze są schowane w kajucie kapitana. Zobaczmy, co mamy!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "Ha-ha! Tak jak myślałem! Znam nawyki kupców, lubią robić tajne skrytki i tam ukrywać skarby statku! Kapitan tej pinasy był sprytnym łajdakiem, ale mnie tak łatwo nie oszuka! Spójrz, co znalazłem! Nigdy byś tego nie znalazł beze mnie!";
			link.l1 = "Pokaż mi!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "Czterdzieści tysięcy pesos, dwie skrzynie pełne dublonów, paczka szmaragdów i mnóstwo klejnotów! Właściciel był całkiem bogaty... Dobrze, przynajmniej to wynagrodzi nasz trud, chociaż liczyłem na więcej. Podzielmy to sprawiedliwie.";
			link.l1 = "Doskonale, Richard. Przynajmniej zarobiliśmy trochę pieniędzy!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "Cóż, i zatrzymajmy to, co każdy z nas znalazł na pokładach, dla siebie. Zgadzasz się? Czy znalazłeś coś użytecznego w skrzyniach i szafkach?";
			link.l1 = "Kilka indiańskich rzeczy, amulety, papiery i tak dalej.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "Zachowaj to dla siebie. W końcu zrobiłeś najbardziej ryzykowną robotę.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = " Dobrze. I znalazłem coś jeszcze, co taki poszukiwacz skarbów jak Ty może uznać za przydatne. Tutaj, na biurku leżał dziennik kapitana. Historia tam zapisana jest bardzo smutna... ale w pewien sposób nas dotyczy. W ładowni ukryta jest skrzynia pełna złota! Przeczytaj to! ";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Dobrze. Ale znalazłem jeszcze jedną rzecz - dziennik kapitana.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "Dobrze, zgadzam się na takie warunki, ha-ha. Więc co, czas wracać?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "Tak. Nie mów nikomu innemu o statku, to będzie nasza tajemnica. Pewnie, nie potrzebujemy kopry, ale zapasy będą dla nas przydatne. Nie będziemy już musieli kupować ich od admirała.";
			link.l1 = "Dobrze, zgadzam się. Mam nadzieję, że inni nie znajdą statku zbyt szybko. Chodźmy!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "Przeczytałeś to?";
			link.l1 = "Jeszcze nie...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "Więc przeczytajmy to! Możemy się z tego dowiedzieć ważnej informacji. Również ciekawe będzie dowiedzieć się, jak ona tu trafiła. Przeczytaj to!";
			link.l1 = "Hm. Dobrze, przeczytam to teraz...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "Przeczytałeś to? Co tam jest?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "A więc, posłuchaj... Historia jest bardzo smutna... ale w jakiś sposób dotyczy nas teraz. Twoje umiejętności poszukiwania skarbów mogą nam pomóc. Jest ukryta skrzynia pełna złota w ładowni! Przeczytaj to!";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Poczekaj chwilę. Przeczytam i powiem ci...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "Naprawdę? "+pchar.name+", ja... cóż, nie czytam zbyt dobrze. Powiedz mi, co tam dokładnie jest napisane, co?";
			link.l1 = "Krótka wersja: ta pinasa przepływała przez Morze Karaibskie z Południowej Ameryki do Nowej Hiszpanii. Kapitan poślubił księżniczkę indiańskiego plemienia z dolnego Orinoko. Powiedziała mu, gdzie jej lud składał ofiary...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "Bryłki złota były ich ofiarami. Oczywiście, nasz dzielny kapitan obrabował ten skarb złota z pomocą swojego pierwszego oficera i kwatermistrza. Umieścili go w ładowni, w jednym z pudeł i przykryli koprą...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "Ale wydaje się, że rabunek świętego miejsca Indian został ukarany. Statek zatrzymał się w martwej ciszy, zapasy wody się kończyły, zaczęła się epidemia gorączki i piraci zaatakowali statek. Marynarze obwinili indyjską dziewczynę, żonę kapitana, i zażądali, aby ją wyrzucić za burtę. Oczywiście kapitan odmówił i załoga rozpoczęła bunt...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "Kapitan przegrał tę walkę. Według ostatnich notatek - zamknął się z indiańską dziewczyną w kajucie i próbował strzelać do rozwścieczonych marynarzy, którzy wyważali drzwi. I nadciągała na nich burza... wydaje się, że to ona przyniosła statek tutaj. Koniec tej historii jest jasny: dziewczyna została zastrzelona, a kapitan z pewnością zabity przez buntowników.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "Hm. To naprawdę smutna historia. Ale czy mnie nie nabierasz? Czy w ładowni jest skrzynia ze złotem? Nie wierzę własnym uszom! Która to? Chodźmy tam! Sprawdzę każdą belę, każdą beczkę!";
			link.l1 = "Chodźmy. Ja też nie mogę się doczekać, aby rozpocząć poszukiwania.";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "Ha-ha! Znaleźliśmy to! Naprawdę istnieje! Spójrz na tę wielką stertę! Cała skrzynia! Jest tam pięć tysięcy bryłek, nie mniej! Nigdy nie widziałem tyle złota!";
			link.l1 = "Gratulacje, partnerze. Wygląda na to, że nasze przedsięwzięcie zakończyło się sukcesem... Co zrobimy ze wszystkimi tymi złotami?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "Co masz na myśli? Podzielimy się na pół!";
			link.l1 = "Z pewnością zrobimy to. Gdzie chcesz to trzymać? Zostawisz to tutaj?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "Ha! Z pewnością ukryję złoto w moich skrytkach i nikt ich nigdy nie znajdzie. Ukrywanie to coś, co dobrze znam! Przenieśmy połowę złota do tej beczki, to będzie moja część. Zabiorę to przed zachodem słońca.\nMożesz zrobić, co chcesz ze swoją częścią. Ale lepiej, żebyś też przeniósł je do własnych skrytek. Nie obwiniaj mnie, jeśli twoje złoto zniknie. Jestem uczciwym człowiekiem, w moim rodzaju uczciwości i nie odważę się zabrać twojej części. Ale inni, ci, którzy przyjdą tu później... mogą je znaleźć.";
			link.l1 = "Dobrze. Zdecyduję, co zrobić ze złotem. Włóżmy twoją część do beczki...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "Zrobione... Dziękuję, "+pchar.name+", że poszedłeś ze mną. Nie mógłbym tego zrobić bez ciebie. Teraz powinienem rozważyć zbudowanie tartany... by odpłynąć stąd... Ach, nieważne. Pomyślę o tym później\nMam pracę do zrobienia - przemieszczenie złota w bezpieczne miejsca. Żegnaj, przyjacielu, życzę ci, abyś mądrze wykorzystał swój łup!";
			link.l1 = "Żegnaj, Richardzie. To był wspaniały dzień dzisiaj. Do zobaczenia!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Pytania? Och, dobrze, jeśli naprawdę tego potrzebujesz...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak się tu dostałeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Czy chcesz opuścić Wyspę?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Czy kiedykolwiek zastanawiałeś się nad dołączeniem do jednego z klanów? Na przykład do Narwali?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Czy to prawda, że można znaleźć wiele ciekawych rzeczy na zewnętrznym pierścieniu?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Żadnych pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Przez dziesięć lat ja i moi towarzysze żeglowaliśmy z Kuby na Wyspę na dobrze wyposażonej tartanie. Trzymaliśmy lokalizację Wyspy w tajemnicy - przewoziliśmy tusze byków i sprzedawaliśmy świeże mięso za towary i złoto z ładowni miejscowych statków\nDobre czasy! Zapas żywności zawsze był tu problemem, głównie chleb i solona wołowina, więc płacili nam za soczyste mięso przyprawami, które w Europie kosztują fortunę! Każda podróż przynosiła mi tyle pieniędzy, że mogłem kupić każdą dziwkę z Tortugi\nAle wszystko ma swój koniec, tak samo nasze zadowolone życie. Pogoda się pogorszyła - burze stały się silniejsze, więc żeglowanie na Wyspę stało się znacznie bardziej niebezpieczne. Niektórzy z moich towarzyszy opuścili interes, ale nie ja i tuzin odważnych ludzi\nW końcu zostaliśmy wyrzuceni na rafę dwie mile od Wyspy. Wciąż nie wiem, jak udało mi się przepłynąć przez burzliwe morze. Tak oto stałem się jednym z tych, z którymi handlowałem w przeszłości.";
			link.l1 = "Interesująca opowieść...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ha! Wydostanę się stąd, do diabła! Ale później. Co miałbym robić na Kubie? Nie mam już tam przyjaciół, a moja kieszeń jest pusta. Zacznę budować łódź, jak tylko znajdę statek z cennym ładunkiem na zewnętrznym pierścieniu albo stos dublonów.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "A dlaczego miałbym? Stać na straży jak idiota co trzeci dzień i trzymać ludzi z dala od San Gabriel? I nie lubią zatrudniać nowych ludzi. To tubylcy... A Murzyni są tacy sami. Nie, lepiej będę sam.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Jasne! To właśnie sprawia, że Wyspa i miejscowi wciąż żyją. Wiesz, kiedy odbywają się tu przyjęcia? Kiedy przybywa nowy statek. Ale tak czy inaczej, na zewnętrznym pierścieniu jest mnóstwo nietkniętych statków wypełnionych złotem i towarami. Problem w tym, że zewnętrzny pierścień jest prawie niemożliwy do zbadania, rzeczy są tam nieuporządkowane, jeśli się zaplączesz, poślizgniesz się lub źle spadniesz - możesz znaleźć się w dziurze, z której nie wyjdziesz sam. Wtedy jesteś skończony. Wiele osób zginęło w ten sposób.";
			link.l1 = "Hm... Interesujące.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie pogrążyłem się w zadumie, a ty postanowiłeś sprawdzić mój kufer!","Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Do diabła!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Niemądra dziewczyno!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. Przez nią czuję się nieswojo.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż go, to nie dla ciebie...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, schowaj swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, gdy biegniesz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z gotową bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Zrozumiano.","Zabieram to.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
