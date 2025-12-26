int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "Stój, "+GetTitle(NPChar, true)+". Dalej przejścia nie ma.";
			link.l1 = "Dlaczego?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "Widzicie tę wieżę? Biuro Holenderskiej Kompanii Zachodnioindyjskiej. Dział rejestru okrętów i archiwum. Wstęp tylko po wcześniejszym umówieniu.";
			link.l1 = "A jak się uzyskuje takie spotkanie?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "Kto musi wiedzieć, ten wie. Mynheer dyrektor nie pracuje z byle kim.";
			link.l1 = "'Mynheer dyrektor'? Kto to taki?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "Zarządca van Doorn. Może nie jest dokładnie dyrektorem, ale wszyscy tak go nazywają. Pracuje tu od dziesięciu lat — zaprowadził porządek. Teraz każdy statek na Karaibach przechodzi przez jego biuro.";
			link.l1 = "Wszystkie statki? Nawet okręty wojenne?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "Tylko najlepsze statki i najbogatsi kapitanowie. Bycie klientem naszego biura to wielki zaszczyt!";
			link.l1 = "Jakie usługi świadczycie?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "Nie powiedziano mi szczegółów — ja tylko pilnuję wejścia. Ale słyszałem, że ludzie wychodzą zadowoleni.";
			link.l1 = "Impozujące.";
			link.l1.go = "ClockTower_Johan_7";
		break;

		case "ClockTower_Johan_7":
			dialog.text = "A powiem wam jeszcze coś. Widzicie ten zegar? Europejski cud — nigdzie w naszej dziczy takiego nie znajdziecie. Mynheer dyrektor osobiście się nim opiekuje.";
			link.l1 = "Może się dogadamy?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "Naprawdę nie mogę nic zrobić, żeby się dostać do środka?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "Nie biorę łapówek!";
			link.l1 = "Przepraszam. Jesteś porządnym facetem. Jak masz na imię?";
			link.l1.go = "ClockTower_Johan_9";
		break;

		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"... Słuchajcie... Rozumiem, że nie jesteście stąd. Ale tu panuje porządek. Mynheer dyrektor zawsze mówi: raz odpuścisz — i nasza wieża runie. Chcecie wejść? Pomóżcie miastu — a was zauważą.";
			link.l1 = "Rozumiem. Do widzenia, żołnierzu.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "Cóż, nie wiem. Mynheer dyrektor nagradza przyjaciół Willemstad. Pomóżcie miastu — a was zauważą. Rozumiem, że nie jesteście stąd. Ale tu panuje porządek. Mynheer dyrektor zawsze mówi: raz odpuścisz — i nasza wieża runie.";
			link.l1 = "Rozumiem. A jak masz na imię?";
			link.l1.go = "ClockTower_Johan_10";
		break;

		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar, true)+".";
			link.l1 = "A ja jestem kapitan "+GetFullName(pchar)+". Do widzenia, żołnierzu.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "Coś się stało?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+". Mogę panu w czymś pomóc?";
				link.l1 = "Nie, "+npchar.name+". Służ dalej.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "Coś się stało?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "Gratulacje. Macie umówione spotkanie.";
			link.l1 = "Spotkanie? Z kim?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "Ze zastępcą mynheer dyrektora. Usłyszał o waszej pomocy dla miasta i kazał mi was zaprosić.";
			link.l1 = "A co z samym dyrektorem?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "Ee... Nie mam uprawnień, żeby wam o tym opowiadać. Powodzenia tam, mynheer kapitanie.";
			link.l1 = "Dziękuję.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "Witamy w dziale rejestru okrętów HKZI. "+UpperFirst(GetTitle(NPChar, false))+"?..";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+", zastępca dyrektora.\n"+
						 "Słyszałem, że przynieśliście Willemstad sporo pożytku. Być może nasze biuro również może wam się przydać.";
			link.l1 = "Dlatego tu jestem.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "Cieszę się, że mogłem być przydatny stolicy Curaçao.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "Każdy kapitan — francuski, hiszpański, holenderski — może zamówić u nas audyt statku. Sprawdzamy olinowanie, działa, takielunek. Znajdujemy słabe punkty, dajemy zalecenia.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "Każdy kapitan — francuski, hiszpański, holenderski — może zamówić u nas audyt statku. Sprawdzamy olinowanie, działa, takielunek. Znajdujemy słabe punkty, dajemy zalecenia.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "A jeśli jeden audyt wam nie wystarczy, możemy też załatwić nowe dokumenty okrętowe. Innymi słowy, praca naszego biura uczyni wasz statek lepszym — bez marnowania cennego mahoniu i jedwabiu.";
			link.l1 = "Jak to możliwe?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"? Nie macie pojęcia, jak potężne jest miejsce, do którego weszliście, i ile może zdziałać zwykłe pociągnięcie pióra.";
			link.l1 = "Za dublony, jak rozumiem?";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "Oczywiście. Nasze usługi nie są tanie i zależą od rozmiaru waszego statku. Ale zawsze się zwracają. Kapitan, który przeszedł przez nas, rzadko ponosi porażkę\n"+
						 "Jednakże nie tylko zabieramy wasze złoto — dajemy też możliwość jego zarobienia. Piraci tak się rozmnożyli, że nawet na Małych Antylach kapitanowie muszą wyposażać eskadry, by odstraszyć te szkodniki. Przynieście dowody zniszczenia — a otrzymacie wypłatę w tych samych dublonach.";
			link.l1 = "Jakiego rodzaju dowody?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "Dzienniki okrętowe. Nawet ta hołota musi prowadzić jakieś dokumenty — inaczej nie da się porządnie dowodzić nawet lugrem. Poza tym, że dzienniki są bezwarunkowym dowodem zbrodni, zawsze znajdą miejsce w naszych archiwach. Przydatne w sporach ubezpieczeniowych\n"+
						 "Jeśli wasza zainteresowała naszymi usługami, na liście klientów zwolniło się miejsce — jeden z kapitanów niedawno zakończył współpracę. Wykonajcie zadanie — a miejsce będzie wasze.";
			link.l1 = "Po co takie komplikacje? Czy moje dublony nie wystarczą?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+", stawiamy na jakość, a nie ilość. Każdy klient naszego biura otrzymuje najlepszą obsługę i osobistą uwagę samego mynheer dyrektora. A to ostatnie, uwierzcie mi, kosztuje znaczne pieniądze nawet dla naszej bynajmniej nie biednej kompanii. Ponieważ w miesiącu jest tylko trzydzieści dni, możemy sobie pozwolić tylko na trzydziestu klientów.";
			link.l1 = "Co trzeba zrobić?";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "Przynieście pięć pirackich dzienników okrętowych — to udowodni waszą skuteczność. Nagroda zależy od tego, jak niebezpieczni byli ich właściciele.";
			link.l1 = "Dobrze. Zrobię to.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "Muszę to przemyśleć.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "A gdzie sam dyrektor?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "Doskonale. Czekam na wyniki i mam nadzieję na współpracę.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "Jak sobie życzycie. Oferta pozostaje aktualna. Ale wasze miejsce może zostać zajęte szybciej, niż myślicie.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "Na morzu. Mynheer van Doorn łączy zarządzanie biurem z dowodzeniem okrętem flagowym.";
			link.l1 = "Jak mu się to udaje?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "Pracuje osiemnaście godzin dziennie. Śpi tutaj, w biurze na górze. Mówi, że sen to strata czasu. Cztery godziny mu wystarczają.";
			link.l1 = "A co z hałasem tych ogromnych mechanizmów zegarowych? Jak w ogóle można tu spać?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "Będziecie mogli go sami o to zapytać i może czegoś się nauczyć. On zawsze chętnie rozmawia z klientami. Rozumiemy się?";
			link.l1 = "Całkowicie.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "Nie do końca...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "Miłego dnia, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Ma pan dzienniki ze sobą?";
			link.l1 = "Widzę, że jesteś dobrze poinformowany, Johan.";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "Ha! To nie jest przystań ani brama do miasta, a ja nie jestem zwykłym wartownikiem na posterunku, lecz pracownikiem kompanii.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Ma pan dzienniki ze sobą?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Przyniosłem dzienniki. Przepuścisz mnie?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "Innym razem.";
			link.l2.go = "ClockTower_Johan_34";
		break;

		case "ClockTower_Johan_33":
			dialog.text = "Cieszę się, że się udało! Proszę, czekają na pana.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;

		case "ClockTower_Johan_34":
			dialog.text = "Życzę miłego dnia, mynheer kapitanie.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "Kapitanie! Wróciliście. Przynieśliście dzienniki?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Tak. Wszystkie pięć.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Później.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
		break;

		case "ClockTower_Visser_22":
			dialog.text = "Doskonale. Pokażcie.\n"+
						"Tak, wszystko w porządku. To prawdziwe pirackie statki. Dobra robota. Należy się wam #количество_дублонов dublonów.\n"+
						"Proszę, weźcie. I podpiszcie się tutaj, proszę.";
			link.l1 = "Czyli jestem na liście?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromPCharTotal("ClockTower_PirateJournal", 5);       
		break;

		case "ClockTower_Visser_23":
			dialog.text = "Prawie. Najpierw musimy załatwić dokumenty. To zajmie kilka minut.\n"+
						"Pełne imię i nazwisko?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "Obywatelstwo?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "Nazwa waszego statku?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Typ statku?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "Liczba dział?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "Wielkość załogi?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "Dobrze. Teraz proszę się podpisać tutaj. I tutaj. I tutaj też.";
			link.l1 = "To wszystko?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "Prawie. Pozostaje tylko wpisać was do rejestru. Oczywiście mynheer dyrektor powinien najpierw poznać was osobiście... Ale to formalność — jestem upoważniony do przyjmowania nowych klientów.\n"+
					"...Ale znowu się rozgadałem. Pozwólcie, że jeszcze raz zapoznam was z naszą listą usług.\n"+
					"Ubezpieczenie. Kosztowne, ale żadna eskadra wojenna nie tknie statków ubezpieczonych przez kompanię. Będziecie mogli trzymać ile chcecie statków w przechowalni portowej bez obawy utraty ich podczas oblężenia kolonii.\n"+
					"Audyt statku — nieznacznie zwiększa wszystkie charakterystyki bez wydawania dóbr strategicznych. Sprawdzimy wszystko: olinowanie, ładownię, kwatery załogi. Damy zalecenia. Cena zależy od rozmiaru statku.\n"+
					"Wpis statku do naszego rejestru. Zwiększa bezpieczeństwo statku w regionie Karaibów, tak że łowcy nagród, piraci i wojskowi dwa razy się zastanowią, zanim was zaatakują.\n"+
					"Audyt i wpis do rejestru mogą być przeprowadzone tylko raz dla konkretnego statku. Więc jeśli już wydaliście pieniądze, dbajcie o swój statek. Nie macie pojęcia, jak bardzo to irytuje moje kierownictwo, gdy kapitanowie niedbale traktują swoje statki i zmieniają je jak rękawiczki!\n"+
					"Ale znowu się rozgadałem. Teraz co do powtarzalnych usług...\n"+
					"Zmiana dokumentów. Wiecie, że statki mogą mieć różne specjalizacje. Ale nawet nie podejrzewacie, że to zależy przede wszystkim od tego, jak statek jest udokumentowany. Jeśli nie podoba wam się, że wasz okręt wojenny jest udokumentowany pod oblężenie fortów, wiecie, do kogo się zwrócić.\n"+
					"No cóż, o nagrodach za oddawanie pirackich dzienników okrętowych już słyszeliście... Im niebezpieczniejszy pirat, tym więcej zapłacimy za jego dziennik.";
			link.l1 = "Imponujące. Muszę powiedzieć, mynheer Visser, że wasze biuro naprawdę...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "'"+GetShipName("Amsterdam")+"' w porcie! Mynheer dyrektor wrócił!";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "Co?! Już?! Ale miał wrócić dopiero za trzy dni!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "Mynheer dyrektor już zszedł na ląd! Idzie prosto tutaj!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "Boże... Jeśli was zobaczy...";
			link.l1 = "W czym problem? Sami powiedzieliście przed chwilą, że macie uprawnienia do przyjmowania nowych klientów.";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "Mam! Ale on nie lubi, kiedy... Nieważne. Kapitanie, czekajcie na zewnątrz. Przy wejściu. Mynheer dyrektor będzie chciał z wami porozmawiać.";
			link.l1 = "Ze mną?";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "Osobiście sprawdza każdego nowego klienta. Zawsze. Idźcie, szybko!";
			link.l1 = "Nie oddam dublonów za dzienniki!";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "Szkoda, zostałbym posłuchać.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;

		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;

		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "Co to było, Johan?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "Mynheer dyrektor wrócił.";
			link.l1 = "I co w tym strasznego?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "Nic strasznego! Po prostu... Mynheer dyrektor nie lubi niespodzianek. Wszystko musi iść zgodnie z planem. A tu jest nowy klient, którego jeszcze nie sprawdził.";
			link.l1 = "Maarten powiedział, że ma uprawnienia, by wpisać mnie do rejestru.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "Nie, nie o to chodzi. Mynheer dyrektor po prostu... cóż, chce wszystko kontrolować sam. Każdy drobiazg. Mówi, że inaczej wszystko się rozleci. Zobaczycie, zaraz znowu zacznie się martwić o swój zegar.";
			link.l1 = "Co?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "Mynheer van Doorn, gdy się zirytuje, zatrzymuje zegar i zaczyna w nim grzebać. Czasem miasto zostaje bez czasu przez pół dnia. A to się zdarza...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "Och... Słyszycie? Zaczęło się.";
			link.l1 = "Szef wrócił. Normalka.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "Słyszę, jasne. Robią Maartenowi pranie mózgu.";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "Niestety, teraz to już normalka.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "Nie powinniście tak mówić. To niesprawiedliwe, jeśli mnie pytacie.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "Chyba się uciszyło. Zaraz was zaproszą.";
			link.l1 = "Będę miał kłopoty?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "Nie martwcie się. Przecież nic złego nie zrobiliście.";
			link.l1 = "Pocieszające.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "No przestańcie! Mynheer dyrektor czasem potrafi być zbyt surowy... Ale jest hojny i uprzejmy... O, mówiłem!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "O, mówiłem!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "Mynheer dyrektor czeka na was w środku.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Wasz statek — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" dział i "+GetMaxCrewQuantity(pchar)+" członków załogi.";
			link.l1 = "Wszystko się zgadza.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "To niesprawiedliwe, że ja wiem o was wszystko, a wy o mnie nic poza plotkami Johana. Hendrik van Doorn. Kierownik działu rejestru Holenderskiej Kompanii Zachodnioindyjskiej na Karaibach. Dowódca fregaty Amsterdam. "+shipType+". "+GetCannonQuantity(npchar)+" dział i "+GetMaxCrewQuantity(npchar)+" członków załogi.";
			link.l1 = "Miło poznać.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "Zdobyliście pięć pirackich dzienników okrętowych. Mój zastępca wysoko was ocenił, wpisał do rejestru klientów i zapoznał z usługami mojego biura\n"+
						"Ale ostateczną decyzję o dopuszczeniu zawsze podejmuję ja. Osobiście. Po rozmowie. Maarten mógł zaproponować kandydata — nic więcej.";
			link.l1 = "W takim razie zaczynajmy.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "Potrzebuję kapitanów, którzy skutecznie walczą z piratami, a jednocześnie odnoszą wystarczające sukcesy handlowe, by móc sobie pozwolić na nasze usługi. Spełniacie te kryteria?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "Zniszczyłem Mortimera Grimma. Kapitana bryga Memento.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "Myślę, że wasza kompania wysoko oceniła moje zwycięstwo nad Albertem Blackwoodem. Szniawa Lady Beth była poważnym przeciwnikiem.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida nie był piratem, ale...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "Pokonałem postrach wszystkich żeglujących. Musicie to wiedzieć.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "Właśnie wpisaliście mój statek do rejestru. Myślicie, że niekompetentny kapitan mógłby go utrzymać?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "Radzę sobie świetnie, a pieniądze na Karaibach rosną na drzewach.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Mynheer Visser już zweryfikował moją kompetencję. Czy ocena waszego własnego zastępcy nie wystarczy?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "Grimm? Nasza organizacja nigdy nie miała pretensji do Grimma, wręcz przeciwnie. Ale do tego, kto zajął jego miejsce... Wiem, kim był i w jakim celu pierwotnie przybył na Karaiby. Takie zbrodnie nie ulegają przedawnieniu i cieszę się, że ukaraliście zbrodniarza i prawdziwego wroga mojego kraju.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "Jeśli dobrze pamiętam raport z incydentu na Kajmanach, nie mieliście szansy się o tym przekonać. Moim zdaniem sytuacja nie jest do końca jednoznaczna, ale wasze zwycięstwo było bez wątpienia kompetentne.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "Ale mógł stać się czymś znacznie gorszym, tak. Godny przeciwnik, choć przegrał nie z wami, a ze swoimi niewdzięcznymi zwierzchnikami. Jestem Holendrem, więc wiem, o czym mówię, jeśli chodzi o wojnę z Kastylią.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("Flying Heart")+"'. Wciąż mnie dziwi, że uczciwi ludzie nie rozbiegają się na widok tej potworności wpływającej do portu. Wiele w tej historii mnie zaskakuje, kapitanie. Ale pewnego dnia znajdzie swoje miejsce w naszych księgach i straci cały swój czar. A wy... unieśmiertelniliście się.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "Zdziwilibyście się. Ale w waszym przypadku nie ma wątpliwości, to prawda.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "I dlatego nic nie są warte. Chyba że to dublony, oczywiście.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\nJesteście dopuszczeni do usług biura. Witamy w rejestrze klientów szanownej Holenderskiej Kompanii Zachodnioindyjskiej.";
			link.l1 = "Dziękuję.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "To obopólnie korzystna współpraca. Zyskujecie dostęp do najlepszych usług na Karaibach. My zyskujemy niezawodnego partnera.";
			link.l1 = "Dobrze.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "Czekajcie! Słyszycie?";
			link.l1 = "Nic nie słyszę.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "Właśnie o to chodzi! Wystarczyło wyjechać na tydzień...";
			link.l1 = "Coś nie tak?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "Z zegarem. Muszę sprawdzić mechanizm. Przepraszam. To... ważne.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "Chyba wszystko w porządku. Jeszcze raz przepraszam. Macie pytania?";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "Jeszcze pytania?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "Wasz zastępca szczegółowo wyjaśnił usługi biura. Jak to w ogóle możliwe?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "Jak łączycie dwa stanowiska? Kapitana i dyrektora?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "Jak pracujecie w takich warunkach? Hałas mechanizmów zegarowych, ciemność i okna zasłonięte grubymi zasłonami.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "Nie, dziękuję za wasz czas. A co z usługami biura?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "Nie ma tu żadnej czarnej magii, "+GetTitle(NPChar, false)+". Pióro i atrament rządzą światem. Kościół zapisuje narodziny, chrzest, ślub i śmierć człowieka. Zmień choćby jedną linijkę — a jego los się zmieni. Statek jest nieco bardziej skomplikowany, ale i w jego przypadku pociągnięcie pióra wiele zmienia. Nie będę ukrywał, jestem dumny z tego, co udało mi się osiągnąć. A jednak wiem, że może być lepiej. A gdyby wpisać do ksiąg rachunkowych nie tylko statki i ludzi, ale cały świat?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "Bo ktoś musi. Poprzedni kapitan Amsterdamu zginął w walce z grupą z Antigui. Kompania nie znalazła godnego zastępstwa. Zaproponowałem siebie. Przeszedłem szkolenie. Zdałem egzaminy. Otrzymałem patent\n"+
			"Tak, jestem kiepskim kapitanem. Znacznie gorszym niż wy — to pewne. Ale dobry menedżer może dowodzić czymkolwiek, a nie tylko statkiem. Trudno nauczyć się dowodzić trzema ludźmi. Ale gdy się nauczysz, możesz dowodzić trzema tysiącami. Biuro, statek, miasto, a nawet ogromna kompania — nie ma granic, dopóki znajdujesz utalentowanych ludzi i ufasz im, że cię zastąpią... To ostatnie jest najtrudniejsze. Prawdziwe przekleństwo.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "A do tego nie ma czym oddychać. "+UpperFirst(GetTitle(NPChar, false))+", człowiek sam kształtuje swoje otoczenie. Tutaj nic i nikt mnie nie rozprasza, wszystko jest pod ręką i podlega tylko mnie i czasowi. Gdybym mógł, komunikowałbym się z zewnętrznym światem wyłącznie przez papier. Niestety, to niemożliwe. I nie bierzcie tego do siebie, "+GetTitle(NPChar, false)+". Lepiej być samemu, ale nie w samotności. Jeśli rozumiecie, o czym mówię.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Przyjmujemy tylko po wcześniejszym umówieniu. Macie wyznaczone... "+pchar.quest.ClockTower.date+" "+month+". Jeśli nie przyjdziecie w wyznaczonym dniu, nic się nie stanie. Zwróćcie się do Johana, a poinformuje was o następnym dostępnym terminie.";
			link.l1 = "Po co takie komplikacje?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Nasza praca jest droga, ponieważ dokonujemy prawdziwych cudów i przynosimy wielkie korzyści naszym klientom. Konflikt interesów jest niemożliwy, dlatego poświęcamy cały dzień roboczy potrzebom konkretnej osoby. Wasz najbliższy dzień: "+pchar.quest.ClockTower.date+" "+month+"\n"+
			"Jeśli zobaczycie Vissera... Maarten postąpił słusznie, proponując waszą kandydaturę. Przekażcie mu to. Jest dobrym zastępcą. Niech nie wątpi.";
			link.l1 = "Dobrze.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "Miłego dnia, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "Jak poszło?";
			link.l1 = "To był długi dzień, ale van Doorn potwierdził twoją decyzję.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "Dzięki Bogu. Czyli wszystko zrobiłem dobrze.";
			link.l1 = "Kazał mi przekazać, że jesteś dobrym zastępcą.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "Naprawdę? On... powiedział to?";
			link.l1 = "Tak. Rzeczywiście to powiedział.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "Cholera. Nie powinien był tego mówić. Teraz będę czuł się jak niewdzięczna świnia. A może on to przewidział i wszystko zaplanował?";
			link.l1 = "Mynheer zastępco, nagle przestałeś być sobą.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Kapitanie, jestem człowiekiem interesu, ty także, więc nie będę przeciągał.\n"+
						 "Mynheer dyrektor już dawno u nas nie pracuje.";
			link.l1 = "Słucham?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "Przyjechał tu na kontrakcie z jednym celem — zorganizować pracę działu rejestru okrętów. Poradził sobie znakomicie, wyszkolił swojego następcę, awansował mnie... i tyle.";
			link.l1 = "Co, i tyle?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "Jego kontrakt dawno się skończył. Nie wiemy dokładnie kiedy, ale jesteśmy całkowicie pewni, że ten człowiek nie ma już prawa zajmować swojego stanowiska.";
			link.l1 = "Rozumiem. Grube ryby w centralnym skrzydle tego budynku się denerwują.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "Rozumiem. Zmęczyłeś się czekaniem, aż zwolni dla ciebie swoje krzesło.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "Dokładnie! I nic nie mogą na to poradzić!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "Nie będę kłamał. Naprawdę jestem zmęczony. Do diabła, van Doorn awansował mnie właśnie po to, żebym go zastąpił, gdy kontrakt się skończy!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "A mimo to nigdy nie próbowałbym podkopywać tego przeklętego krzesła tylko dlatego, że czuję się oszukany! Bóg mi świadkiem, jestem wdzięczny i podziwiam tego człowieka!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "Nie, mynheer. To nasi wspólni przełożeni chcą pozbyć się van Doorna. Ci sami, którzy siedzą za murem wieży — w centralnym skrzydle tego budynku! Ale nawet oni nie są w stanie go poskromić!";
			link.l1 = "Co w tym trudnego? Van Doorn raczej nie jest ważniejszy od Stuyvesanta.";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "To nie jest statek ani królewski dwór, kapitanie. Nasza kompania to zupełnie nowy typ organizacji. Nie można po prostu wskazać palcem i zwolnić tak cennego człowieka.\n"+
						 "Po pierwsze, nikt nie wie, gdzie jest oryginał kontraktu van Doorna. Ergo, nie ma żadnych podstaw do zwolnienia. Gdybyśmy spróbowali, przysłałby hordę prawników, i to my skończylibyśmy mu winni.\n"+
						 "Po drugie, kierownictwo popełniło błąd, gdy dało van Doornowi patent na Amsterdam. Może i jest słabym kapitanem, ale zebrał załogę — najlepszą w całym regionie. Wystarczy, że wyda rozkaz, a elitarni żołnierze Kompanii zajmą ten budynek bez mrugnięcia okiem.\n"+
						 "Po trzecie, jego żona go uwielbia. Nieważne, że nie widział jej od kilku lat. Córka samego De Witta jest zdolna na wiele dla ukochanego męża. A Rada Siedemnastu musi się z tym pogodzić.\n"+
						 "Innymi słowy, dyrektoriat bardzo hojnie zapłaci za twoją pomoc. I zachowa twoje przywileje w biurze rejestru okrętów.";
			link.l1 = "Imponujące. Naprawdę jesteś człowiekiem interesu, Maarten. Sprzedajesz mi zdradę z takim samym profesjonalizmem, z jakim jeszcze niedawno sprzedawałeś usługi swojego biura.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "To niełatwe, gdy sam van Doorn nauczył cię sztuki negocjacji i szczerze wierzysz w to, co mówisz.";
			link.l1 = "Więc czego ode mnie chcesz?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "Coś, co może zrobić tylko osoba z zewnątrz. Włam się do biura nocą i znajdź tam oryginał kontraktu van Doorna. Dopilnuję, żeby drzwi były otwarte.";
			link.l1 = "Dlaczego sam tego nie zrobisz? I co mi przeszkadza pójść teraz i opowiedzieć wszystko twojemu przełożonemu?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "Ponieważ van Doorn ma zwyczaj przyjmować nocą kogo tylko chce, z wyjątkiem pracowników kompanii. Nikt się nie zdziwi, widząc cię wychodzącego z tej wieży o nietypowej porze.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Co do twojej groźby... Teraz nie dostaniesz się do dyrektora, masz przecież wyznaczony inny dzień. "+pchar.quest.ClockTower.date+" "+month+", prawda? Do tego czasu pilność wiadomości nieco spadnie. A poza tym, dyrektor nigdy nie nagradza donosicieli. I zawsze chroni swoich pracowników.";
			link.l1 = "Wygodne dla ciebie.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "To nie jest zdrada, kapitanie. Po prostu chcemy przestrzegać kontraktu i zabezpieczyć kompanię. I Willemstad, któremu tak bardzo pomogłeś, nawiasem mówiąc.";
			link.l1 = "Pomyślę o tym. Ale niczego nie obiecuję.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "Nie wymagam od ciebie więcej, kapitanie. Przede wszystkim jesteś naszym klientem. Jak by to się nie skończyło, jestem bardzo dumny, że to właśnie ja cię znalazłem i wpisałem do rejestru biura.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "Zawsze możesz mnie znaleźć w centralnym skrzydle. Miłego dnia.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "Dzień dobry, "+GetTitle(NPChar, false)+". Są jakieś wieści?";
			link.l1 = "Jeszcze nic.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", dziś jest pański dzień. Proszę bardzo.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "Miłego dnia, "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", czekają na pana innego dnia. Z przyjemnością zobaczymy pana: "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "Miłego dnia, "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "Dziękuję, Johan.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", jesteś trochę spóźniony. Biuro jest zamknięte.";
					link.l1 = "Cześć, "+npchar.name+". Słyszałem, że pracuje nawet w nocy.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "To prawda. Różni ludzie się pojawiają. Nawet księża czasem wpadają, he-he. Ale wszyscy muszą najpierw przejść przeze mnie. A co do ciebie, nie dostałem żadnych instrukcji.";
			link.l1 = "Chwila, stoiszz tu na posterunku dobę w dobę? Jak to możliwe?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "Tak. Mynheer dyrektor właśnie tak zarządził. Jak mu się to udaje, nie wiem, ale i tak wystarcza mi czasu na odpoczynek i służbę. A jeszcze podnieśli mi żołd — grzech narzekać!";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "Coś jeszcze?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "Powinieneś mnie przepuścić. Pracuję dla najwyższego kierownictwa kompanii.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(Zabić go)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "Tak trzymaj, żołnierzu.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;

		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;

		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;

		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "Äh. Czego pan ode mnie chce, mynheer kapitanie? Jestem tylko zwykłym żołnierzem, nic nie wiem.";
				link.l1 = "Wszystko wiesz, Johan. Nie jesteś taki prosty. Panowie w wysokich gabinetach może i nie muszą ci się tłumaczyć, ale o czarnym kocie między nimi na pewno słyszałeś.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "Jestem małym człowiekiem, ale nie będę przeskakiwał przez głowę mojego bezpośredniego przełożonego. Przepraszam, "+GetTitle(NPChar, true)+".";
				link.l1 = "Jeszcze wrócimy do tej rozmowy.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;

		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "To prawda, "+GetTitle(NPChar, true)+". Mynheer dyrektor za długo siedzi. Nadciąga burza.";
			link.l1 = "Co słyszałeś?";
			link.l1.go = "ClockTower_Johan_56";
		break;

		case "ClockTower_Johan_56":
			dialog.text = "Wszyscy się boją, że jeśli nie dziś, to jutro przejmie władzę. Jest zbyt wielkim człowiekiem dla naszej zadupy. Dusi wszystkich swoimi kontrolami, każdy podpis musi przejść przez niego.\nPowiem szczerze, a pan sam widział: za każdym razem, gdy Amsterdam wpływa do portu, od razu podnosi się zła atmosfera.";
			link.l1 = "Mogę to rozwiązać, ale do tego musisz mnie przepuścić.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "Proszę, mynheer kapitanie. Tylko błagam, nie zgub mnie: jeśli mynheer dyrektor się dowie, stracę głowę, a muszę nakarmić rodzinę.";
			link.l1 = "Postaram się.";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "Jest pan dobrym człowiekiem, mynheer kapitanie. Może będę mógł panu pomóc: wiem, że w jednej z książek mynheer dyrektor trzyma klucz. Do czego on jest — nie wiem, ale może się przyda.";
			link.l1 = "Dziękuję, Johan.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "Stój. Jest pan na terenie Holenderskiej Kompanii Zachodnioindyjskiej. Dział rejestru okrętów i archiwum. Wejście tylko po zapisie.";
			link.l1 = "Jestem "+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Ma pan zapis? Proszę.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Pański zapis jest na inny dzień: "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "Dzień dobry, "+GetTitle(NPChar, false)+". Są jakieś wieści?";
			link.l1 = "Tak. Oto kontrakt.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "Niewiarygodne... Skończył się siedem lat temu!";
			link.l1 = "Czyli to jest to, czego potrzebowałeś?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "Dokładnie! Z tym dokumentem kompania może go legalnie odwołać. Żadnych kruczków. Żadnych wymówek. Czas minął — kropka.";
			link.l1 = "Co dalej?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "Wyślę kontrakt do Amsterdamu. Rada Siedemnastu podejmie decyzję. Doornowi każą wrócić. Nie będzie mógł odmówić.";
			link.l1 = "A jeśli odmówi?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "Nie może. Niech jego żona jest córką udziałowca, wielkiego pensjonariusza, ale nawet jej ojciec nie pójdzie przeciw Radzie. A sama Catharina... Czeka dziesięć lat. Jeśli dowie się, że może wrócić, ale odmawia — to ją zabije.";
			link.l1 = "Okrutne.";
			link.l1.go = "ClockTower_Visser_76";
		break;

		case "ClockTower_Visser_76":
			dialog.text = "Tak. Ale to jedyny sposób. Dziękuję, kapitanie. Wykonałeś ważną pracę.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;

		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "Twoja nagroda — pięćset dublonów. I daję ci słowo: za dwa-trzy miesiące, gdy zajmę fotel dyrektora, otrzymasz nieograniczony dostęp do usług biura. Bez kolejek. Bez zapisów. O każdej porze.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "I zabiłeś Johana. Już i tak zdradziłem człowieka, którym się podziwiam i któremu wszystko zawdzięczam. Teraz jeszcze to.\n"+
							 "Może na twoim statku ludzie są jak drzazgi, ale kompania ceni swoich pracowników. I obrzydza mnie bycie współwinnym morderstwa.\n"+
							 "Twoje dublony trafią do rodziny Johana, ale drugą część umowy wykonam.\n"+
							 "Daję ci słowo: za dwa-trzy miesiące, gdy zajmę fotel dyrektora, otrzymasz nieograniczony dostęp do usług biura.";
			}
			link.l1 = "Liczę na twoje słowo. Miłego dnia.";
			link.l1.go = "ClockTower_Visser_78";
		break;

		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;

		case "ClockTower_Visser_79":
			dialog.text = "Dzień dobry, "+GetTitle(NPChar, false)+". Jeszcze nie ma wiadomości. Nie martw się, pamiętam naszą umowę.";
			link.l1 = "Spodziewam się.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;

		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"! Proszę wejść, proszę. Cieszę się, że pana widzę.";
			link.l1 = "Gratuluję nominacji.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "Dziękuję. Rada Siedemnastu podejmie decyzję szybciej, niż się spodziewałem. Kontrakt okazał się wystarczającym dowodem. Mynheera van Doorna odsunięto od zarządzania biurem.";
			link.l1 = "I jak to przyjął?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "Umie przegrywać. Po prostu zebrał swoje rzeczy osobiste z biura i wyszedł. Choć czy naprawdę przegrał?\n"+
						 "Pozostawili mu dowództwo nad Amsterdamem. Pod tym względem kompania z pewnością popełniła błąd. Nie powinni byli dawać mu tego statku wtedy.\n"+
						 "Nie doceniliśmy go. Spodziewam się, że na koniec wszystko nie obróci się na gorsze.";
			link.l1 = "Jak może być gorzej?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "Mynheer van Doorn wie, kto wydobył kontrakt z jego biura.";
			link.l1 = "Skąd?!";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "Nie patrz tak na mnie! Nic mu nie powiedziałem. Sam to wszystko zrozumiał.";
			link.l1 = "I co teraz?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "Teraz uważa cię za wroga. Ale dopóki nie stanowisz zagrożenia dla Republiki Siedmiu Zjednoczonych Prowincji — nie tknie cię.\n"+
						 "Van Doorn zawsze umiał oddzielić sprawy osobiste od służbowych. Pytanie brzmi, czy ty potrafisz?";
			link.l1 = "A co, jeśli nie potrafię?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "Wtedy cię znajdzie. I wykona swoją pracę. Nie dawaj mu powodu.";
			link.l1 = "Postaram się.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "Miłego dnia, "+GetTitle(NPChar, false)+". Korzystaj z usług naszego... mojego biura w każdej chwili.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", czekają na pana. Mynheer Visser kazał wpuszczać wszystkich klientów swobodnie. Mówi, że stare zasady były zbyt surowe.";
			link.l1 = "Dziękuję, Johan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "Proszę wchodzić w dowolnych godzinach pracy. Zapisy zniesiono.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "Masz minutę?";
			link.l1 = "Dla ciebie — zawsze.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "Ach, gdyby tak było, mój kapitanie. Masz w życiu i inne pasje. Właśnie teraz na przykład twoja śliczna głowa zajęta jest zupełnie nie mną, prawda?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "No właśnie. Znam dobrze swojego mężczyznę. A zapał marynarza — tym bardziej mi znany. Więc powiedz wprost, kochany...\n"+
						 "Ile nas będzie kosztować zdobycie okrętu flagowego szanownej Holenderskiej Zachodnioindyjskiej Kompanii Handlowej?";
			link.l1 = "Żeby van Doorn sam po nas przyszedł, będę musiał stać się wrogiem Willemstadu.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "Och, mój kapitanie... Więc tak to będzie. Nie pierwszy raz, co?";
			link.l1 = "Jakbyś nie aprobowała.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "Zakochałam się w tobie takim, jakim jesteś. I zawsze będę po twojej stronie. Po prostu pamiętaj o ciężarze odpowiedzialności, który my... to znaczy ty nosisz wobec swoich ludzi.";
			link.l1 = "Zresztą po to mamy naszego Alonso. On ci przypomni.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "Jak tylko wypłyniemy w morze, mój kapitanie.";
			link.l1 = "Więc nie zwlekajmy, kochanie.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "Charles? Chcę cię o coś zapytać.";
			link.l1 = "Oczywiście, Mary. Co się stało?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "Ja... martwię się o ciebie, wiesz. Znam to spojrzenie. Myślisz o czymś złym.";
			link.l1 = "Bzdury. Sam nie pamiętam, o czym właśnie myślałem. Skąd ty możesz wiedzieć?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "Po prostu wiem! Widziałam ten Amsterdam, wiesz. Piękny statek. Bardzo piękny. Ale...\n"+
						 "Już wszystko postanowiłeś... Jak wcześniej, prawda?";
			link.l1 = "Van Doorn sam po nas przyjdzie, ale w tym celu będę musiał stać się wrogiem Willemstadu.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "Czy to jest tego warte, Charles?";
			link.l1 = "Nie wiem, Mary.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "Chcę, żebyś był szczęśliwy, wiesz. Ale mimo to poproszę Alonso, żeby jeszcze bardziej cię namawiał, żebyś to odpuścił, tak!";
			link.l1 = "To do niego pasuje. Chodźmy, kochanie.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Cap, musimy pogadać.";
			link.l1 = "Słucham.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "Nie teraz, Alonso.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "Jest taka sprawa, cap, ale będzie pan musiał mnie wysłuchać. To jest, eee, jak to się mówi...\n"+
						 "Sprawa pilna — o!\n"+
						 "Więc ptaszek mi powiedział, że osobiście wyrzucił pan jednego z dyrektorów kompanii z ciepłej posadki, a ten pielęgnuje urazę i teraz poluje na nas swoją wspaniałą fregatą.";
			link.l1 = "To wyraźna przesada.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "Pan wie, jak ludzie lubią młynkować językami, cap. Niech plotka tydzień się uwarzy — i usłyszy pan, że van Doorna omotała córka plantatora, że na Amsterdamie załoga z żywych trupów, a w ładowni — skarby samego Cortésa.\n"+
						 "Ale mnie bardziej interesuje rzeczywisty stan rzeczy. Więc, cap, będzie bijatyka czy nie?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;

		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;

		case "ClockTower_Alonso_4_2":
			dialog.text = "Co, nawiasem mówiąc, byłoby cholernie zabawne, nie sprzeczam się! Holenderski okręt flagowy! Ha! Wyobrażam sobie miny tych serożerców, gdy my...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;

		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;

		case "ClockTower_Alonso_4_4":
			dialog.text = "Tomaso, zamknij się.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;

		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "Jeśli ma być bijatyka, to nie tak szybko. Van Doorn się nie będzie mścił, nie jest takim człowiekiem. Najpierw będziemy musieli porządnie rozzłościć Holendrów.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "ClockTower_Alonso_4_6":
			dialog.text = "Dzięki, cap, to uspokoi załogę.";
			link.l1 = "A ciebie?";
			link.l1.go = "ClockTower_Alonso_5";
		break;

		case "ClockTower_Alonso_5":
			dialog.text = "Moją troską jest chronić załogę. Przed nimi samymi i... przed panem, jeśli się uda. Pan i tak zrobi to, co zaplanował.";
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "Tak trzymaj, Alonso.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;

		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_6":
			dialog.text = "Uparty jak hiszpański muł!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;

		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;

		case "ClockTower_Alonso_7":
			dialog.text = "Panie, za co mi to.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;

		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "Wszystko komplikujesz! Cap chce ładny statek — damy mu ładny statek! Jesteśmy jedną załogą!";
			link.l1 = "Tak trzymaj, Alonso. Tomaso, wynoś się.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Wasz statek — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" dział i "+GetMaxCrewQuantity(pchar)+" członków załogi.";
			link.l1 = "Jest pan jak zawsze dokładny, mynheer dyrektorze.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "Ten tytuł już do mnie nie należy — dzięki pańskim staraniom. Ale nawet nie myślcie, że zaatakowałem was z drobnego poczucia zemsty. Wykonywałem swoją pracę.\n"+
						 "I najwyraźniej sobie z nią nie poradziłem. Zresztą nie mogłem: kiedyś mówiłem panu, że jest pan o wiele lepszym kapitanem niż ja.";
			link.l1 = "Sam pan wziął ten ciężar! Pański kontrakt wygasł siedem lat temu. Co panu przeszkadzało po prostu wrócić do domu?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "Co panu przeszkadza zrobić to samo? Zna pan odpowiedź, kapitanie. Ma pan marzenie. Nie ma pan innego życia. A gdy tylko puszczasz kontrolę — wszystko się wali.\n"+
						 "Mógłbym zaprowadzić porządek w tym zakątku. Zatrzymać nieskończony cykl przemocy. Gdybym nie osłabił kontroli. Gdybym zdusił swój strach i zrobił to, co dawno trzeba było zrobić.\n"+
						 "Ale dość patosu. Jestem tak samo kiepskim wojownikiem jak kapitanem, ale ludzi potrafię dobierać. Sam pan uczynił się moją ostatnią pracą, kapitanie. Dziś w rejestrze biura będzie o dwóch kapitanów mniej!";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "Mówiłeś tam coś o strachu. Więc przeczytaj ten list.";
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "O jednego. Do boju!";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "Od Cathariny?! Jak śmiesz mieszać sprawy osobiste z pracą?!";
			link.l1 = "Jak pan widzi, list jest wciąż zapieczętowany. Czekam.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...nie może już dłużej czekać... odejdzie do innego... jeśli nie wrócę?!";
			link.l1 = "Biuro już pan stracił. Pańska załoga ginie właśnie teraz. Czy jest pan gotów stracić jeszcze i rodzinę?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "Tylko nie tak. Kapitanie, czy przyjmuje pan moją kapitulację?";
			link.l1 = "Tak. Wynoś się z mojego statku.";
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "Nie. To była ostatnia przysługa dla skazańca. Do boju!";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "W takim razie gratuluję zwycięstwa, kapitanie "+GetFullName(pchar)+". Dziś w rejestrze będzie o tylko jednego kapitana mniej. Żegnajcie.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+". Nie spodziewałem się, że odważy się pan tu przyjść.";
			link.l1 = "Dlaczego nie? Wciąż jestem pańskim klientem i potrzebuję usług biura.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "Usługi? USŁUGI?! Po tym, co pan zrobił? Jest pan wrogiem szanownej Holenderskiej Kompanii Zachodnioindyjskiej! Inny kapitan zajmie pańskie miejsce klienta!";
			link.l1 = "Wątpliwe. Proszę spojrzeć, co znalazłem w papierach van Doorna.";
			link.l1.go = "ClockTower_Visser_103";
		break;

		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "Pański poprzednik uznał, że poniżej jego godności jest użycie tego dokumentu — nawet gdy jego krzesło zaczęło się chwiać.";
			link.l1.go = "ClockTower_Visser_104";
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;

		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "Miał pan szczęście, że miał pan takiego przełożonego. Za takie sztuczki czekałby pana proces — w najlepszym razie.";
			link.l1.go = "ClockTower_Visser_105";
		break;

		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "Jest pan człowiekiem interesu. Wie pan, do czego zmierzam.";
			link.l1.go = "ClockTower_Visser_106";
		break;

		case "ClockTower_Visser_106":
			dialog.text = "Pan... Pańskie miejsce w rejestrze zostało przywrócone.";
			link.l1 = "Eh, Maarten. Chciał pan zająć miejsce dyrektora, choć dał panu wszystko. Uratował pana przed procesem i nawet nie uznał za konieczne, by pana o tym poinformować.";
			link.l1.go = "ClockTower_Visser_107";
		break;

		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "Ten grzeszek nigdy nie pozwoli panu wznieść się wyżej i pozostawi pana żyjącego w ciągłym strachu.";
			link.l1.go = "ClockTower_Visser_108";
		break;

		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "Teraz pańska kolej być przywiązanym do tego miejsca. Ale takiego zastępcy, jakiego miał van Doorn, pan na pewno nie będzie miał.";
			link.l1.go = "ClockTower_Visser_109";
		break;

		case "ClockTower_Visser_109":
			dialog.text = "Dosyć. Chce mnie pan całkowicie dobić?!";
			link.l1 = "Nie do końca. Chcę, żeby wpisał pan mój nowy statek do rejestru. Nie chcę żadnych nieporozumień.";
			link.l1.go = "ClockTower_Visser_110";
		break;

		case "ClockTower_Visser_110":
			dialog.text = "Pański statek to Amsterdam. Okręt flagowy HKZI. Nie można go po prostu... przerejestować.";
			link.l1 = "Dlaczego nie? Papier wszystko wytrzyma. Czy nie tak działa pański system?";
			link.l1.go = "ClockTower_Visser_111";
		break;

		case "ClockTower_Visser_111":
			dialog.text = "Boże, ale wszystko ma przecież granice!";
			link.l1 = "Wierzę w siłę tego miejsca. Pan też powinien.";
			link.l1.go = "ClockTower_Visser_112";
		break;

		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;

		case "ClockTower_Visser_113":
			dialog.text = "Pełne imię?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;

		case "ClockTower_Visser_114":
			dialog.text = "Obywatelstwo?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "Nazwa pańskiego statku?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Typ statku?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "Liczba dział?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "Wielkość załogi?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "Dobrze. Teraz proszę się podpisać tutaj. I tutaj. I tu również.";
			link.l1 = "To wszystko?";
			link.l1.go = "ClockTower_Visser_120";
		break;

		case "ClockTower_Visser_120":
			dialog.text = "To wszystko.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;

		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "Zapomniał pan coś powiedzieć.";
			link.l1.go = "ClockTower_Visser_122";
		break;

		case "ClockTower_Visser_122":
			dialog.text = "\nWitamy w rejestrze klientów szanownej Holenderskiej Kompanii Zachodnioindyjskiej.";
			link.l1 = "Do zobaczenia, mynheer dyrektorze.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+". W czym mogę i moje biuro pomóc panu dziś?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "Cieszę się, że pana widzę, "+GetTitle(NPChar, false)+"! Zawsze do usług. Co pana dziś interesuje?";
				}
				else
				{
					dialog.text = "No? Co pana dziś interesuje?";
				}
			}
			link.l1 = "Przeprowadzi pan audyt mojego statku? Chcę poprawić jego charakterystyki.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "Nie jestem zadowolony ze specjalizacji mojego statku. Zdobędzie pan nowe dokumenty?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "Wpisze pan mój statek do rejestru kompanii? Niech piraci i łowcy pomyślą dwa razy.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "Chcę ubezpieczyć moje statki przechowywane w zarządach portowych. Obecne i przyszłe.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "Przyjmujecie przecież dzienniki okrętowe kapitanów piratów, prawda?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "Chyba nie dzisiaj. Miłego dnia.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Koszt zależy od rozmiaru statku. O którym statku mówimy?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Niestety, audyt jest jednorazową usługą dla każdego pojedynczego statku. Coś jeszcze?";
				link.l1 = "W takim razie w innym terminie.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "Zobaczmy... To będzie kosztować " + n + " dublonów.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proszę zaczynać.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "Chociaż... zróbmy to innym razem.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Jestem zmuszony odmówić. Zgodnie z rejestrem wasz statek wiele lat temu trafił do morskiego diabła i takiego ducha przeszłości nie da się usunąć jednym pociągnięciem pióra. Zanim będziemy mogli współpracować, musicie go odrestaurować. Mówią, że na Isla Tesoro jest mistrz, który podejmie się takiej pracy.";
				link.l1 = "Rozumiem, dziękuję.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Statek już został ulepszony.";
				link.l1 = "Rozumiem, dziękuję.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "Gotowe.";
			link.l1 = "Dziękuję.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Koszt zależy od rozmiaru statku. O którym statku mówimy?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Niestety, wpis do rejestru jest jednorazową usługą dla każdego pojedynczego statku. Coś jeszcze?";
				link.l1 = "W takim razie w innym terminie.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "Zobaczmy... To będzie kosztować " + n + " dublonów.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proszę zaczynać.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "Chociaż... zróbmy to innym razem.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Jestem zmuszony odmówić. Zgodnie z rejestrem wasz statek wiele lat temu trafił do morskiego diabła i takiego ducha przeszłości nie da się usunąć jednym pociągnięciem pióra. Zanim będziemy mogli współpracować, musicie go odrestaurować. Mówią, że na Isla Tesoro jest mistrz, który podejmie się takiej pracy.";
				link.l1 = "Rozumiem, dziękuję.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Statek już został ulepszony.";
				link.l1 = "Rozumiem, dziękuję.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "Gotowe.";
			link.l1 = "Dziękuję.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Koszt zależy od rozmiaru statku. O którym statku mówimy?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Hm. Nie widzę żadnego z pańskich statków w porcie.";
				link.l1 = "W takim razie w innym terminie.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "Zobaczmy... To będzie kosztować " + n + " dublonów.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proszę zaczynać.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "Chociaż... zróbmy to innym razem.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "Przykro mi, ale to niemożliwe. Pański statek jest unikalnym egzemplarzem, opisanym w legendach. Nic nie może go zmienić prostemu ruchem pióra.";
				link.l1 = "Rozumiem, dziękuję.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "O jakiej specjalizacji mówimy? Pański statek jest uniwersalny, bez charakterystycznych cech.";
				link.l1 = "Przyjemnie słyszeć, dziękuję.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;

		// Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "Zobaczmy... To będzie kosztować " + n + " dublonów.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "Proszę zaczynać.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "Chociaż... zróbmy to innym razem.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "Gotowe.";
			link.l1 = "Dziękuję.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;

		// Награда за пиратов
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "Całkowicie słusznie. Nagroda zależy od liczby dzienników i od względnego niebezpieczeństwa ich właścicieli.\n" +
						  "Ile dzienników pan przyniósł?";
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;

		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "Kompania dziękuje panu za pracę. Należy się panu " + JournalsCost() + " dublonów. Proszę odebrać i się podpisać.";
			link.l1 = "Dziękuję.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "Nie widzę twojego statku w porcie.";
	link.l1 = "W takim razie w innym terminie.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
