void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Czego potrzebujesz?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "Coś jeszcze, Kapitanie?";
			link.l1 = "Niczego na razie...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "Ha-ha-ha! Señor Hesucristo! Chwała Santiago Obrońcy! Chwała Maryi Pannie! Jesteśmy ocaleni! Ha-ha-ha!";
			link.l1 = "Hiszpanie! Do broni!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Cześć. Rozumiem, że masz problemy? Kim jesteś?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "Dobrze, dobrze, uspokój się. To tylko nawyk.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "Ha-ha! Señor, moje imię to Rodrigo Jimenez. Jestem geodetą i, z woli losu, el jefe tych nieszczęsnych ludzi.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "My... zostaliśmy tu zrzuceni. Ale, señor, nie jesteśmy przestępcami! Ha-ha-ha-ha!";
			link.l1 = "Co jest zabawnego?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Ach... Przepraszam, señor! To wszystko moja przypadłość, od dzieciństwa śmieję się, gdy jestem bardzo zdenerwowany. Ha.";
			link.l1 = "I został wybrany jako przywódca?.. Dobrze. Ludzie nie lądują na bezludnych wyspach bez powodu, senor. Masz ochotę wyjaśnić? Daję ci tylko jedną szansę.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "Przepraszam, obawiam się, że nie dosłyszałem twojego imienia, panie. Czy jesteś Anglikiem?";
			link.l1 = nationManName[sti(pchar.BaseNation)]+" . Czy to takie ważne? Nie martwmy się teraz o moje imię.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "W istocie, będąc uznawani za heretyków przez katolicki Kościół Hiszpański, musimy stawić się przed sprawiedliwym sądem Świętej Inkwizycji. Dlatego twoja narodowość jest dla nas tak ważna. Hiszpański kapitan byłby zobowiązany wydać nas lokalnym władzom. Nie przetrwalibyśmy czegoś takiego ponownie! Ha-ha!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "Ha-ha-ha-ha-ha-ha! Takie nasze szczęście, cóż, i tak nie mamy nic do stracenia. "+dialog.text;
			link.l1 = "Cóż, na twoje szczęście sprawy Inkwizycji mnie nie dotyczą. I co z tego? Jesteście poganami?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "Nie, przysięgam ci! Nasza społeczność zajmowała się rzemiosłem i handlem w wspaniałym mieście Kadyks przez pięćdziesiąt lat. Wszystko szło dobrze, nawet nabyliśmy statek i licencję na handel z koloniami naszego Imperium. Teraz rozumiem, że wtedy przekroczyliśmy jakąś granicę i byliśmy całkowicie nieprzygotowani na naszych nowych konkurentów... i ich metody.";
			link.l1 = "Nie podzieliłeś się handlem z kimś w Europie i w rezultacie cała społeczność utknęła na bezludnej wyspie na Karaibach? A ja myślałem, że mam problemy życiowe...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "Niestety, tak jest w istocie. Nasza społeczność została założona przez Żydów, którzy przeszli na nową wiarę i otrzymali możliwość powrotu do Hiszpanii. Ta starożytna historia wystarczyła do oskarżeń i oficjalnego dochodzenia.";
			link.l1 = "I więc uciekłeś...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "Tak! Ha-ha-ha! Na naszym własnym statku! Płynęliśmy do Curacao, aby zbudować nowy dom i nowy interes. Jednakże, nie doceniliśmy wytrwałości Inkwizycji i zapłaciliśmy za to wysoką cenę. Ich kurier przechwycił nas niedaleko stąd i rozkazał kapitanowi zabrać nas z powrotem do domu...";
			link.l1 = "Cholera!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "Jest jeszcze więcej! Ha! Nasz kapitan nie chciał zawracać sobie głowy przewożeniem nas z powrotem przez Atlantyk ani zwalnianiem nas pod jego odpowiedzialnością w najbliższym porcie. I, podejmując prawdziwie salomonową decyzję, dał nam jedzenie, wysadził nas tutaj i to było na tyle.";
			link.l1 = "To rzeczywiście tragiczna opowieść, bez wątpienia. Podsumujmy: nie możesz wrócić do domu, przyjazne kolonie cię wydadzą, a obce porty cię nie przyjmą - nie ma końca wojny w tym regionie. Jakie masz plany?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "Namalowałeś tak ponury obraz, panie, że brak mi słów. Jakby nie było lepszego miejsca dla nas niż ta wyspa.";
			link.l1 = "Nie sądzę, jest lepsza wyspa.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "Naprawdę? Czy to hiszpański?";
			link.l1 = "To moje. Z przeznaczenia odziedziczyłem dawną kryjówkę piratów na bezludnej wyspie. Teraz to moja baza, i chcę ją rozbudować, zbadać wyspę, a jeśli to możliwe, zbudować tam fabrykę.";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "Czy jesteś piratem?";
			link.l1 = "Tak.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "Nie.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "Nowy Świat! Rzeczywiście, jesteśmy tutaj. W domach mówią, że piraci to prawdziwe demony, a nie nawet ludzie. Żrą dzieci, gwałcą kobiety i zdzierają skórę z dobrych katolików. Czy to prawda?";
			link.l1 = "To zależy od dnia tygodnia. Porozmawiajmy o tym innym razem. Szukam ludzi. Pracowitych i zdolnych osób, gotowych żyć z dala od cywilizacji przez kilka lat. Czy byłbyś zainteresowany czymś takim?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "Szkoda, skoro już jestem przestępcą, chciałbym zobaczyć przynajmniej jednego pirata.";
			link.l1 = "Być może będziesz miał jeszcze taką okazję. Porozmawiajmy o tym innym razem. Szukam pracowitych i zdolnych osób, które są chętne żyć z dala od cywilizacji przez kilka lat. Czy interesowałoby cię coś takiego?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "Nie mamy innego wyjścia. Ale to wcale nie jest zła opcja. Przyjmiemy ją, jeśli pozwolisz nam żyć i pracować w pokoju. I obiecaj, że pewnego dnia odeślesz nas do domu! Daj nam swoje słowo, panie, i powiedz swoje imię..";
			link.l1 = "Ja, Kapitan "+GetFullName(pchar)+", daję ci moje słowo. ?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "Ha-ha! Jesteśmy uratowani! Niech tak będzie! Jest nas kilka rodzin, około 30 osób. Wszyscy są piśmienni, wykształceni w rzemiosłach i handlu.";
			link.l1 = "Los zadecydował... Proszę, wejdźcie na pokład!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Miło cię poznać, Senor Rodgar. Wygląda na to, że będziemy musieli razem żyć i pracować przez długi czas... Boże, jak wytrzymujesz to gorąco?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "Jeśli nie masz nic przeciwko, wejdę: Kapitanie, daj nam dzień na osiedlenie się i szybkie sprawdzenie zapasów i terenu. Jestem pewien, że Senor Rodgar ma mnóstwo pomysłów, co zrobić z tym kawałkiem ziemi. Myślę, że stworzymy dobrą drużynę.";
			link.l1 = "Tak naprawdę nie masz wyboru, Hymenese. Ha-ha.!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "Ha-ha-ha-ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "Tak, kapitanie?";
			link.l1 = "Hymeńczyku, masz dla mnie jakieś dobre wieści?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Kapitano, to jest koszmar. Twój dom nie jest zły, oczywiście. Ale poza tym... Niemożliwe jest mieszkać w tych chatkach, otoczonych zaroślami, a Senor Rodgar nawet nie wie, co się dzieje na drugim końcu wyspy!! Niewiarygodne! Ha-ha!";
			link.l1 = "Czy jesteś zdenerwowany, czy naprawdę się z tego śmiejesz teraz?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "Oczywiście, że to zabawne! Co oni robili przez te wszystkie lata? Przede wszystkim musimy dokończyć budowę kilku domów i naprawić te chuty do akceptowalnego stanu. Ludzie muszą żyć godnie, by pracować pilnie. Ponadto poproszę piratów, aby przeprowadzili pełne rozpoznanie wyspy. Może to miejsce jest bogate nie tylko w skały i piasek. Kiedy wszystko będzie gotowe, będę mógł dokładnie powiedzieć, co zrobić z tą ziemią.";
			link.l1 = "Brzmi świetnie! Czego się ode mnie wymaga?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Materiały na domy, meble i tymczasowe schronienia. Wszystko obliczyłem. Oto lista.";
			link.l1 = "Imponujące...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "Naprawdę? Panie, zbudowaliśmy katedry! To jest dopiero imponujące....";
			link.l1 = "Jestem skłonny ci uwierzyć! Tylko nie zbuduj tu przypadkiem katedry. Czy za każdym razem będę musiał przywozić tu dużo materiału?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "Nie, te materiały utrzymają nas przez chwilę, ale wciąż będziemy musieli później coś dostarczyć. Jeśli chcesz uniknąć takich problemów w przyszłości, przynieś dwa razy więcej materiałów.";
			link.l1 = "Cóż, przekonałeś mnie. Zobaczę, co da się zrobić. Jakieś terminy?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "Nie, panie. Ale uprzejmie proszę, byś nie zwlekał - to praca, którą trzeba wykonać, by posunąć sprawy naprzód. Ludzie też potrzebują gdzieś mieszkać. Załaduj materiały do magazynu i nie zapomnij mnie poinformować, gdy wszystko będzie gotowe. Och, prawie zapomniałem! Porozmawiaj z panem Rodgarem o eksploracji wyspy.";
			link.l1 = "Zgoda!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "Tak, Kapitanie?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "Witaj, Hymenez. Sprawdź magazyn.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "Cześć, Hymenezie. Moi ludzie przeszukali całą wyspę. Co powiesz?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "Poradziłeś sobie z tym obowiązkiem znakomicie! Jeśli kiedykolwiek będziesz w Kadyksie, przyjdź do mnie pracować jako magazynier!";
			link.l1 = " Właśnie idę! Powiedz mi, compadre, co teraz zamierzasz zrobić?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Señor Kapitanie, najpierw zajmijmy się zakwaterowaniem i zaopatrzeniem. Potem zrobimy plany. Oczekuję towarów z twojej listy w magazynie.";
			link.l1 = "Dobrze, rozumiem. Najpierw musimy zbudować domy i uporządkować to miejsce. Towary wkrótce tu będą.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Kapitánie, najpierw zajmijmy się kwaterą i zaopatrzeniem. Plany możemy zrobić później. Czekam na towary z twojej listy w magazynie. A twój piracki przyjaciel również oczekuje zapasów i medykamentów.";
			link.l1 = "Dobrze, rozumiem. Najpierw musimy zbudować domy i uporządkować to miejsce. Towary wkrótce tutaj będą. I dla mojego pirackiego przyjaciela też.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Daj nam sześć miesięcy, Kapitanie, a nie poznasz tego miejsca.";
			link.l1 = "Chcesz powiedzieć, że za sześć miesięcy nie będzie ani ciebie, ani osady, ani materiałów tutaj? Do zobaczenia później!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "Zaczniemy pracować, jak tylko załatwisz sprawy z tym bandytą. Żądał od ciebie prowiantu i lekarstw, i zgadzam się z nim - to rozsądne żądanie.";
			link.l1 = "Przekażę mu twoje słowa.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "Cóż, kapitanie? Czy zrobiłeś wszystko, o co prosił twój pirat?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "Rozwiązałem wszystkie sprawy z Rodgarem. Rozpoznanie wyspy się rozpoczęło, zapasy i leki są w magazynie. Teraz twoja kolej.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "Nie martw się, rozpracujemy to. Ja się tym zajmuję.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "Senor Kapitanie! Co o tym sądzisz? Ha-ha-ha?";
			link.l1 = "Jest znacznie przyjemniej. Raport, Himenes!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "Teraz możesz tu faktycznie zamieszkać! Posprzątaliśmy i odbudowaliśmy wszystkie domy, oprócz twojego, oczywiście. Niezbyt luksusowo, ale nie gorzej niż w naszym Belize.";
			link.l1 = "Belize od dawna należy do Anglii, Himenes.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "Nie jestem pewien, czy domy o tym wiedzą, kapitanie, ha-ha!";
			link.l1 = "Teraz masz gdzie mieszkać, a osada wygląda po ludzku. Co dalej?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Rozejrzyj się, porozmawiaj z Seniorem Janssenem, a potem wróć do mnie. Omówimy wyniki rekonesansu wyspy i nasze plany.";
			link.l1 = "Odkąd zacząłeś tak nazywać Rodgara? Czyż nie byliście ciągle w niezgodzie?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "I nadal je mamy. Ale musimy jakoś zbudować działające relacje.";
			link.l1 = "Dziękuję, Rodrigo. Wkrótce wrócę.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Kapitán. Señor Janssen.";
			link.l1 = "Chodź, opowiedz mi o wynikach rekonesansu wyspy.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Tak, Kapitanie. Kilka miejsc osobiście sprawdziłem z naszym poszukiwaczem. Cóż, co mogę powiedzieć... Isla Mona to biedna, mała i dość nieciekawa wyspa. Jest bardzo mało miejsca na budowę, krajobraz jest trudny, stromy, a ziemia prawie nie jest urodzajna. Trzy plaże, jedna zalana jaskinia, gęste zarośla, kilka papug, stado kóz i my...";
			link.l1 = "Czy ty poważnie? Chcesz powiedzieć, że najcenniejszym skarbem na tej wyspie jest stado kóz?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "Ha-ha-ha-ha! Zapytałbym, Senor! Ha-ha! Nie pozwoliłeś mi skończyć!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Dobrze, dobrze, uspokój się i kontynuuj. Wiesz, zainwestowałem tu dużo pieniędzy.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "A nie na próżno! W jaskini jest dość świeżej wody, jest wystarczająco dużo ziemi, aby uprawiać drzewa owocowe, a kozy można hodować. Dzięki rybołówstwu i wysiłkom twoich towarzyszy, kwestia jedzenia zostanie rozwiązana bardzo szybko.";
			link.l1 = "Więc nie będziesz musiał przynosić tu więcej jedzenia? Niezłe. Miałem nadzieję, że to miejsce może funkcjonować bez mojej ciągłej opieki. Kontynuujmy.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "Masz rację we wszystkim, Senor. Ale to nie wszystkie nowiny! Po pierwsze, Senor Rodgar wpadł na pomysł zbudowania tawerny. Nie wiem, co ci to da, ale ten łotr coś knuje.";
			link.l1 = " On chce się upić, oto co!";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "Po drugie, Zatoka Gubernatora okazała się znacznie głębsza, niż pierwotnie sądziliśmy. Możemy zbudować pełnoprawne molo.";
			link.l1 = "Nie do końca rozumiem, jak to mi się przysłuży, ale to już dobra wiadomość. To nie wszystko, mam nadzieję?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "Znaleźliśmy gaj drzew bacote. Idealne miejsce na fabrykę.";
			link.l1 = "Sprawiasz, że jestem szczęśliwy, Rodrigo! Doprawdy, doskonałe wieści!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "To wszystko na teraz, señor. Może w przyszłości będziemy mieli więcej pomysłów. Rozumiesz, najlepsze pomysły przychodzą podczas pracy! O co chciałbyś zapytać?";
			link.l1 = "Opowiedz mi o bacote. Brzmi obiecująco.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "W mojej ocenie, mała fabryka będzie w stanie wydobywać to cenne drewno przez kilka lat. Rezerwy są skromne, ale zasób jest strategiczny. Możemy wykarczować teren w centrum wyspy i zbudować tam dom z magazynem. To początek. Oprócz materiałów budowlanych, będziemy również potrzebować około 15 kompletów kajdanek i muszkietów.";
			link.l1 = "A po co nam kajdanki? I dlaczego dokładnie piętnaście?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "To ciężka praca, señor. Rzekłbym nawet, że to praca niewolnicza.";
			link.l1 = "Rozumiem. He-he...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "Czyś ty oszalał? Nie zostanę właścicielem niewolników!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "A czemu potrzebujemy muszkietu? I czemu tylko jednego?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "Zgadzam się z piratem, señor. Nie rozumiem cię, kapitanie. Cała gospodarka tego regionu opiera się na pracy niewolników i tak pozostanie przez wiele lat. Jak jesteśmy lepsi?";
			link.l1 = "Podejmę decyzję. Tymczasem powiedz mi, po co ci muszkiet? I dlaczego dokładnie jeden?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "Oczywiście, fabryka będzie wymagała konserwacji. Dzięki jej budowie, ta wyspa będzie miała gospodarkę z tobą jako głównym partnerem handlowym. Sami nakarmimy niewolników, ale za ochronę i produkcję będziesz musiał zapłacić z własnej kieszeni. Osadnicy wezmą sto dublonów i pięć butelek wina za każdą partię. W sprawach bezpieczeństwa negocjuj z Senorem Janssenem.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "Czterdzieści miar co miesiąc. A złoto jest na przyszłość. Pewnego dnia zabierzesz nas stąd, pamiętasz swoją obietnicę? Każda praca musi być opłacona, a za twoje dublony zapłacimy myśliwym i rzemieślnikom za ich pracę w osadzie. W ten sposób będziemy mieć handel, a z nim - cywilizację!";
			link.l1 = "To jest duch! Dobrze! Na razie wszystko brzmi wystarczająco przekonująco...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "Co jeszcze cię interesuje?";
			link.l1 = "Więc, jaka jest historia z tą tawerną? Czemu nie zbudować teatru?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Kapitanie, ostrzegałem go, że nie spodoba ci się pomysł z domem. Ale to jedyna opcja. Masz największy dom w... ekhem, mieście, przerobimy parter na salę, ustawimy stoły i kuchnię. Napitki i jedzenie będziemy przechowywać w jaskiniach pod domem. Mamy ludzi do gotowania i grania muzyki. Drugie piętro pozostanie twoje i nie będziemy go ruszać. Sami przeniesiemy wszystkie twoje rzeczy z parteru na górę.";
			link.l1 = "Dobrze. Więc co dokładnie da nam tawerna?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "Zdobędziemy trochę życia kulturalnego, a ty będziesz miał okazję mieć około trzystu ludzi w rezerwie, tuż w sercu Karaibów.";
			link.l1 = "Interesujące... Zastanowię się nad tym.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "Co cię jeszcze interesuje?";
			link.l1 = "Cóż, a co z molo?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "To proste. Oczyścimy Zatokę Gubernatora z raf, zainstalujemy sygnalizację świetlną i zbudujemy molo. Señor Janssen twierdzi, że będzie można schronić w zatoce trzy statki, albo jeden pierwszej klasy. I będzie ci przyjemniej tu wracać, nie ciągnąc za każdym razem łodzi po plaży.";
			link.l1 = "To byłoby miłe.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "Czego chciałbyś się dowiedzieć?";
			link.l1 = "To wszystko na teraz. Wrócę, gdy zdecyduję, co zbudować.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Senor Kapitanie, weź ten dokument. Pozwoliłem sobie zapisać wszystkie szczegóły, aby nie powtarzać ich tuzin razy. Przestudiuj to, przynieś materiały i wyznacz zadanie.";
			link.l1 = "Dziękuję, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно еще 10 рабов
			{
				dialog.text = "Senor Kapitanie, potrzebujemy 10 niewolników do pracy w fabryce - mówiłem ci, nie zapomniałeś?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Już dostarczone. Rozładuj je i rozpocznij produkcję.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "Moja pamięć jest nienaruszona. Wkrótce ich przyniosę.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "Więc, Senor Kapitanie, co powiesz?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "Chcę czystą zatokę i bezpieczne molo. Będzie to baza dla mojej floty.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Śmiało, zbuduj tawernę. Wszyscy to docenią, a ja będę mógł tu trzymać rezerwy.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Zacznij budować plantację. Czas odzyskać inwestycje.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Rodrigo, szczególnie wartościowi specjaliści i sprzęt zostali dostarczeni do fabryki. Możesz zacząć pracować.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Rodrigo, przyszedłem po mój żelazne drewno.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Rodrigo, czy zakończyliśmy naszą wielką budowę?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, zbudujmy twój kościół.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, przyniosłem twoje kościelne przedmioty.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Nic na razie...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "Materiały są dostępne, wszystko jest gotowe. Budowa potrwa 4 miesiące.";
				link.l1 = "Nie śpieszysz się, co! No cóż, powodzenia, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "Obawiam się, że nie ma wystarczającej ilości materiałów w magazynie. Proszę, sprawdź listę ponownie.";
				link.l1 = "Ja się tym zajmę.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "Materiały są dostępne, wszystko jest gotowe. Budowa potrwa 3 miesiące.";
				link.l1 = "Nie spieszysz się, prawda! No cóż, powodzenia, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "Obawiam się, że w magazynie nie ma wystarczającej ilości materiałów. Proszę, sprawdź jeszcze raz listę.";
				link.l1 = "Zajmę się tym.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "Materiały są dostępne, wszystko jest gotowe. Budowa potrwa 6 miesięcy.";
				link.l1 = "Nie śpieszysz się, prawda! Powodzenia, Rodrigo.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "Obawiam się, że w magazynie nie ma wystarczającej ilości materiałów. Proszę, sprawdź ponownie listę.";
				link.l1 = "Zajmę się tym.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Witaj, Kapitanie. Jak ci się podoba twój nowy port?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "Ciemno, Rodrigo! O mało co nie rozbiliśmy się o twój chwalony pomost! Dobra robota, że przynajmniej go oświetliłeś!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "Niezłe, Rodrigo! Wydaje się to małą rzeczą, ale miło jest przechadzać się po tych deskach na brzeg. I zatoka stała się łatwiejsza do nawigacji. Więc, chyba teraz mogę pomieścić więcej statków w tej małej zatoce?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Tak, Kapitanie. Muszę przyznać, że to budzi pewną dumę. Proszę, daj mi znać, jak chciałbyś kontynuować nasz wielki projekt budowlany.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "Mówiąc o budowie. Moja fabryka powinna już być ukończona. Prawda, Rodrigo?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "H-hik! Kapitanie! Świętujemy tutaj!";
			link.l1 = "Rodgar. Rodrigo. Och, cholera!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "Co się stało, k-k-kapitanie? Nie podoba ci się kolor ścian?";
			link.l1 = "Teraz dopiero zauważyłem, że wy dwaj macie to samo imię! Ha-ha-ha! Hiszpan i pirat, z tym samym imieniem, zbudowali tawernę na bezludnej wyspie i piją razem, jakby bogowie indiańscy mieli wszystkich pożreć i zakończyć świat o wschodzie słońca! Ha-ha! Jestem z wami!";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "Ha-ha-ha! Tak prawdziwe! Punkt!";
			link.l1 = "Punkty!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = " Wszystko gotowe. Ruszamy? Pozwól, że pokażę ci twoją fabrykę.";
			link.l1 = "Prowadź.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Kapitana, prawie wszystko jest gotowe do rozpoczęcia operacji. Mieszkania dla robotników, magazyn na surowce, strefa przetwarzania - zbudowano godną fabrykę. Już oznaczyliśmy najbardziej obiecujące drzewa do wycinki w dżungli. Przyprowadź piętnastu robotników i uzgodniony ekwipunek - 15 kajdan i muszkietów, a zaczniemy pracę.";
			link.l1 = "My? Masz na myśli niewolników?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "Ha! Niewol... Niewolnicy będą ciąć, osadnicy przetwarzać, a piraci pilnować. Wszyscy będą mieli robotę - podjąłeś się poważnego przedsięwzięcia, Kapitanie.";
			link.l1 = "Prawie jak ziemia obiecana, co? Poczekaj na towary, czas na polowanie.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "Smętny los... Nigdy nie opuszczą tego miejsca.";
			link.l1 = "Rodgar... to znaczy, Rodrigo! Po pierwsze, mogą odpłynąć. A po drugie, gdybyś spotkał kogoś innego na Terks, twój los nie byłby lepszy.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "Doskonale to wiem, Kapitanie. I nie zapominam o tym. Pozwól, że opowiem ci o działaniu tej fabryki. Od przyszłego miesiąca, piętnastego dnia, dostarczymy czterdzieści bali przetworzonego bacout. Oczywiście, nie musisz przychodzić po każdą dostawę co miesiąc - wszystkie partie będą przechowywane i czekały na ciebie tutaj, w fabryce.";
			link.l1 = "Więc mogę zabrać kilka partii naraz?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "Naturalnie w granicach rozsądku - nie trzymaj się z dala zbyt długo. Ludzie nie będą pracować latami bez zapłaty, nie wiedząc, czy ich jedyny klient wciąż żyje czy nie. Myślę, że dostarczymy sześć partii, zanim zawiesimy operacje.";
			link.l1 = "Czy muszę odebrać wszystkie towary naraz? A co z ceną, przypomnij mi?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Tak, wszystko naraz. Cena standardowego kłody bacout to dziesięć dublonów. Dodatkowo, za każdą partię, będziesz musiał dać pięć butelek dobrego rumu i tyle samo butelek wina. Rodgar twierdzi, że nigdzie indziej na świecie nie znajdziesz takich cen.";
			link.l1 = "Rzeczywiście, zgadzam się! Dzięki, Rodrigo. Do roboty!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "Doskonale! Teraz znowu zaczniemy pracę!";
			link.l1 = "Dobrze.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Oczywiście, kapitanie, weź to. Mamy następujące partie gotowe na następny termin: "+sti(pchar.questTemp.IslaMona.Factory.Part)+",  to "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" drewno. Dlatego jesteś nam winien "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+"  doblony, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" butelki rumu, i "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" butelki wina, czy masz to wszystko?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Oczywiście. Oto twoja zapłata.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "Wydaje się, że nie mam wszystkiego. Zaraz to przyniosę.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Znakomicie. Przetransportujemy tytoń z fabryki do twojego magazynu, skąd będziesz mógł go odebrać, kiedykolwiek zechcesz.";
				link.l1 = "Świetnie. Przygotuj następną partię.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "Trzymaj się, kapitanie! Twój magazyn jest pełen - nie będziemy w stanie załadować całego zebranego tytoniu. Zrób miejsce w magazynie - wtedy wróć do mnie.";
				link.l1 = "Dobrze, zajmę się tym.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "Oczywiście, kapitanie!";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "Ha! Kapitanie, obawiam się, że budowanie czegokolwiek innego byłoby niepotrzebnym szaleństwem i zbytkiem. Chyba że...";
			link.l1 = "A jeśli nie?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Kapitánie, niezręcznie mi o to pytać... Już zainwestowałeś ogromną sumę w to miejsce!";
			link.l1 = "Burdel?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "Kościół?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Przysięgam na świętego Santiago, to by nie było złe! Ale pierwszej nocy nasze kobiety by to spaliły. Razem z nami. Nie, kapitanie, mówię o kościele. Tak, mamy przyzwoite mieszkania i płace, morze i rozrywkę, rodziny i przyjaciół. Ale wciąż czegoś brakuje, rozumiesz?";
			link.l1 = "Potrafię sobie wyobrazić.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "Widzisz mnie na wylot, kapitanie. Tak, mamy przyzwoite zakwaterowanie i płacę, morze i rozrywki, rodziny i przyjaciół. Ale wciąż czegoś brakuje, rozumiesz?";
			link.l1 = "Mogę sobie wyobrazić.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Dokładnie. Nie możemy zbudować Domu Bożego bez twojej pomocy. Takie miejsce musi być wyjątkowe, musi być nie z tego świata. A zatem powinno być kosztowne. Będziemy potrzebować świec, sztabek złota, bursztynu i, oczywiście, materiałów budowlanych, i to nie tanich. Nie przyniesie ci to żadnego zysku, więc nie śmiem prosić.";
			link.l1 = "Więc, czy potrzebujesz tu sprowadzić księdza?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "Nie.";
			link.l1 = "Czy już macie wśród siebie księdza?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "Nie, kapitanie. I myślę, że już wszystko rozumiesz.";
			link.l1 = "Więc, czy święci ojcowie z Inkwizycji mieli powód, by was prześladować? Jesteście heretykami?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "Według kanonicznych praw, jesteśmy najgorszymi heretykami. Nie wierzymy, że komunikacja z Bogiem koniecznie wymaga pośrednika z tego świata.";
			link.l1 = "Z tego świata?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Kapitanie, nie jesteśmy satanistami, a nasza wspólnota nie jest sektą. Jesteśmy chrześcijanami, jak ty, ale patrzymy na rzeczy z bardzo szerokiej perspektywy. Zbyt szerokiej, według niektórych bardzo wykształconych i godnych ludzi. Jeśli kiedykolwiek znajdziesz miejsce w sercu na otwartość i zrozumienie, wtedy powiem ci więcej. Ale na razie po prostu weź tę listę. Na wszelki wypadek.";
			link.l1 = "Powinieneś był mi o tym powiedzieć wcześniej, Rodrigo. Nie chcę pewnego pięknego dnia wrócić i zobaczyć na mojej ziemi sabatu czarownic lub narodzin nowej wiary! Podczas gdy czekasz - podejmę decyzję.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Imponująca lista. Zaczynam rozumieć, dlaczego święci ojcowie potrzebują tyle pieniędzy! Zastanowię się nad twoją ofertą, Rodrigo, i podejmę decyzję.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "Jeśli wynik będzie pozytywny, przyniosę wszystkie towary z twojej listy do magazynu, a skarby położę ci na stole.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "Jeśli wynik będzie pozytywny, przywiozę wszystkie towary z twojej listy do magazynu i rozłożę skarby na stole.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "W imieniu całej naszej społeczności dziękuję ci, kapitanie. Nie pożałujesz tego, przysięgam!";
			link.l1 = "Pożałuję tylko wtedy, gdy zbudujesz coś zupełnie tandetnego.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "Kapitanie, wszystkie materiały budowlane są na stanie! Rozpoczniemy budowę, gdy przyniesiesz wymienione luksusowe przedmioty. Zostaną użyte do biżuterii i narzędzi rytualnych. Jeszcze raz bardzo dziękuję, Kapitanie! Muchas gracias!";
			link.l1 = "Nie ma za co!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "Bardzo dziękuję, kapitanie! Wszystko jest gotowe, zaczynamy budowę. Wróć za kilka miesięcy na pierwszą wizytę. Ach, i jeszcze jedno, winogrona są dojrzałe! Zrobimy domowe wino, urządzimy święto i ucztę na Twoją cześć!";
				link.l1 = "Myślę, że wszyscy zasługujemy na świętowanie. Wrócę za dwa miesiące.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Kapitane, wciąż są "+sAdd+" został.";
				link.l1 = "Oczywiście, tylko daj mi trochę więcej czasu, proszę. Szczerze mówiąc, gdyby nie te świece, pomyślałbym, że zamierzasz zakopać skarb.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "A ja myślałem, że pozbyłeś się tego idiotycznego nawyku.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "that we won't have to sit here for weeks waiting for events to unfold.";
			else sTemp = "that not everyone will have to participate in the battle.";
			dialog.text = "Ha-ha-ha-ha-ha... ha. Też tak myślałem, kapitanie! Rodgar ma rację, twoja obecność już oznacza, "+sTemp+"";
			link.l1 = "Już wiem, co się stało. Czy są jakieś ofiary?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "Nie martw się tak bardzo, Rodgar. To nie twoja wina, fizylierzy przybyli zbyt szybko. I tak nie bylibyśmy w stanie utrzymać ich za naszymi liniami, a nie było czasu, by wszystkich posłać pod miecz.";
			link.l1 = "Co z Hiszpanami?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "Tylko trzech z nich dotarło do nas, a tylko jeden przeżył. Sam kapitan! Podobno bardzo poważny wojskowy marynarz. Ale nie może nam jeszcze pomóc - będzie musiał zostać w łóżku przez co najmniej kilka dni. A propos, kapitanie, słyszeliśmy strzały i, sądząc po twoim wyglądzie, ty również.";
				link.l1 = "Można tak powiedzieć. Nieproszeni goście wyraźnie nie spodziewali się tak niespodziewanej wizyty i zostali z powrotem wrzuceni do morza.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Tylko trzech z nich dotarło do nas, a przeżył tylko jeden. Sam kapitan! Podobno bardzo poważny wojskowy żeglarz. Ale na razie nie może nam pomóc - będzie musiał zostać w łóżku przez co najmniej kilka dni.";
				if (i >= 50) 
				{
					link.l1 = "Ostatnim razem zostawiłem tu całkiem sporo ludzi na straży, więc powinno was być znacznie więcej niż fizylierów. Dlaczego po prostu nie wrzuciliście ich wszystkich z powrotem do morza od razu?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Dobrze, rozwiążmy ten problem. Plan jest taki: zwabię ich na otwarty atak, i to natychmiast. Nie ma sensu zwlekać. Przygotujcie się z kartaczami i muszkietami, piraci przy bramach, reszta zostaje w domu - i siedźcie cicho.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Kapitanie, to wszyscy zawodowi żołnierze, z dowódcą. A my nawet nie mamy odpowiedniej broni. Tak, oczywiście, mogliśmy ich przytłoczyć liczbą, ale stracilibyśmy co najmniej dwa razy więcej ludzi, a każda osoba jest tu cenna i potrzebna.";
			link.l1 = "Dobrze, rozwiążmy ten problem. Plan jest taki: wywabię ich na otwarty atak, i to natychmiast. Nie ma sensu zwlekać. Przygotujcie śrut i muszkiety, piraci przy bramach, reszta zostaje w domu - i siedzieć cicho.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "Kapitanie, jesteśmy gotowi do walki!";
			link.l1 = "Wiem, Rodrigo. Ale nie pozwoliłeś mi dokończyć: jeśli choć jeden wróg zdoła przedrzeć się przez bramy, musicie wszyscy rzucić się na niego z każdej strony. A w bitwie wasze szanse na dostanie kuli lub odłamka maleją. Jeszcze jakieś pytania?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "Znakomicie! To nieprzyjemne, oczywiście, że taki niefortunny los spotkał twoich rodaków. Ale jestem wdzięczny, że ponownie stanąłeś po naszej stronie.";
			link.l1 = "To nie było łatwe, Rodrigo. Zwykli ludzie nazwą to zdradą i będą mieli rację.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "To moja ziemia, Rodrigo. Musi być zawsze broniona, bez względu na to, przez kogo.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Tak, stary Rodrigo nie spodziewał się, gdy opuszczał Kadyks, że takie przygody czekają na niego w Nowym Świecie.";
			link.l1 = "Nie mów mi. Czasami mam dokładnie te same myśli.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "To nieprzyjemne, oczywiście, że taki niefortunny los spotkał twoich rodaków. Ale jestem wdzięczny, że po raz kolejny stanąłeś po naszej stronie.";
			link.l1 = "Nie było łatwo, Rodrigo. Zwykli ludzie nazwą to zdradą, i będą mieli rację.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "To jest moja ziemia, Rodrigo. Trzeba jej zawsze bronić, bez względu na to, przed kim.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Rozumiem, kapitanie. Pozwólcie mi więc krótko przedstawić sytuację w naszej osadzie podczas waszej nieobecności.";
			link.l1 = "Naprawdę? Zaczekaj... Kapitanie?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "Rozumiem, kapitanie. Pozwólże mi zatem przedstawić krótki przegląd sytuacji w naszej osadzie podczas twej nieobecności.";
			link.l1 = "Naprawdę? Chwileczkę... Kapitanie?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "Nie chciałem urazić. Po prostu Rodgar wypowiada to słowo tak smakowicie, że też chciałem spróbować. Bardzo... Piracko.";
			link.l1 = "Nie ma sprawy, tylko jestem zaskoczony. Więc co się tutaj stało?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Najpierw zbudowaliśmy kościół. To zajmie chwilę, wejdź. Jest coś do zobaczenia. Dokonałeś wielkiego czynu, kapitanie. Może ci się to nie wydawać, ale możliwość komunikacji z Bogiem jest dla nas bardzo, bardzo ważna. Od tego dnia nazywamy Isla Mona naszym hogar.";
			link.l1 = "Dom, słodki dom? Zdecydowanie rzucę okiem. Czy niosłem te wszystkie świece na próżno?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "Nie za darmo! Po drugie, fabryka została zrujnowana - straciliśmy całą siłę roboczą. Będziesz musiał przywieźć nową partię niewolników. Na szczęście, po ponownym oszacowaniu wydajności pracy, doszliśmy do wniosku, że dziesięciu niewolników będzie więcej niż wystarczająco. Więc, mniej zamieszania dla ciebie.";
			link.l1 = "Dobrze. Coś jeszcze?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Wszystko gotowe na obchody. No, prawie: musimy tu posprzątać, pochować ciała tych biednych dusz... Więc przyjdź jutro do kościoła i zaczniemy.";
			link.l1 = "Do kościoła? Dziwne miejsce na rozpoczęcie zabawy. Czy zamierzasz się oświadczyć, Rodrigo?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "Ha-ha! Nie, kapitanie, choć niektóre z naszych dziewcząt nie miałyby nic przeciwko. Nam nie przeszkadza, jeśli to zrobisz.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "Zgoda, przyjdziemy jutro do kościoła. Oczywiście, żeby się pomodlić.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "I jeszcze jedno, kapitanie. Przed świętowaniem idź i zajmij się najpierw więźniem. Decyzja musi zostać podjęta, i rozumiem, że będzie to i tak nieprzyjemne.";
			link.l1 = "Dobrze. Pójdę teraz.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "Wszyscy tu są! Señor, nie wiemy, czego początkowo chciałeś od tego miejsca i jak teraz je sobie wyobrażasz. Dla nas było to najpierw wymuszone schronienie, a teraz stało się prawdziwym domem. Twoi marynarze, piraci i zbiegli hiszpańscy heretycy tutaj żyją. W każdym innym miejscu na ziemi już dawno poderżnęlibyśmy sobie gardła. Ale tutaj jesteśmy przyjaciółmi, pracujemy i cieszymy się życiem. Isla Mona nie jest dla nikogo z nas ostatecznym punktem na mapie tego świata, ale być może tutaj spędzimy najszczęśliwsze i najowocniejsze lata naszego życia. A to jest twoja zasługa, twoja ziemia i twoi ludzie. Muchas gracias, "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "W porządku, w porządku. Kapitanie, zebraliśmy dla ciebie dary - mnóstwo przydatnych i po prostu przyjemnych rzeczy. Niektóre przywieźliśmy ze sobą, a niektóre wykonaliśmy sami. Przyjmij ten dar z czystym sercem, a resztę damy ci naszą ciężką pracą.";
			link.l1 = "Dziękuję... Nie spodziewałem się tego. Tak mało jasnych chwil i zwykłej ludzkiej życzliwości w mojej odysei... To wiele dla mnie znaczy, uwierz mi.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "I teraz - z powrotem do pracy!";
			link.l1 = "Nie, teraz do tawerny! Rodrigo, ruszajmy!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Tak, rozkoszujmy się tą wspaniałą chwilą nieco dłużej.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "Ha-ha! Hic!";
			link.l1 = "Tak przy okazji, widzę, że prawie przestałeś dziko śmiać się ze wszystkiego i z niczego. Świeże powietrze Karaibów?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "Bardziej jak zgubny wpływ Rodgara. Patrząc na niego, nauczyłem się wszystko szlag trafić.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "Znam tam wielu szanowanych ludzi.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "Nie, wolę dalej pić rum i patrzeć na ciebie spode łba.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "Kapitanie! Hic!";
			link.l1 = "Witaj również, Rodrigo. Widzę, że wieczór był pełen wydarzeń?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Lepiej... nie pytaj. Miesiąc... nie będę pić. Och. Mam wieści! Kapitan... oprzytomniał.";
			link.l1 = "Jedyny ocalały Hiszpan?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "Hik! Auć! Tak, umieścili go w faktorii, w domu pod strażą.";
			link.l1 = "Dobrze. Pójdę do niego. Uważaj, żeby nie przesadzić.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "Popływałem sobie i wszystko jest jak nowe! Będziemy żyć i pracować. Spróbuję utrzymać faktorium w działaniu tak długo, jak to możliwe. No i naprawy, drobne prace budowlane. Może nawet zdecyduję o dzieciach z moją.";
			link.l1 = "Radować się dla was wszystkich! To była bardzo nerwowa, kosztowna... i wspaniała przygoda, i cieszę się, że się nam udało. Powodzenia wszystkim, a tym z nas, którzy wyruszają w rejs, jeszcze więcej szczęścia!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "Stój! Kapralu "+GetFullName(npchar)+"Znajdujesz się na terenie walk! Natychmiast się przedstaw i podaj cel swojej obecności tutaj!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Kapralu, spocznij! "+GetFullName(pchar)+", kapitan francuskiej marynarki wojennej. Rozkazuję ci eskortować mnie do twojego przełożonego. Wykonaj rozkaz!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", kapitan statku o nazwie '"+pchar.ship.name+"'. Przybyłem na tę wyspę całkowicie przez przypadek - dla ewentualnych napraw i uzupełnienia zapasów świeżej wody.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "Tak jest, panie kapitanie! Proszę za mną. Tylko błagam, bądźcie ostrożni! Ta wyspa roi się od bandytów.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Przepraszam, kapitanie. Nie jesteś w mundurze, więc jestem zobowiązany sprawdzić twoje oficerskie patenty.";
				link.l1 = "Widzisz. Zadowolony? Teraz - szybko wykonać rozkaz, kapralu!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "Musisz iść ze mną, Kapitanie. Nasz starszy oficer porozmawia z tobą. Od tej chwili twój statek jest uznawany za tymczasowo zarekwirowany na potrzeby floty francuskiej. Natychmiast powiadom obecny wachty i podążaj za mną.";
			link.l1 = "Zarekwirować statek Charle Prince? Nie sądzę!";
			link.l1.go = "Capral_5";
			link.l2 = "Wygląda na to, że nie mam wyboru. Zrobię, jak mówisz.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Panie Kapitanie, ścieżka do obozu wroga jest po naszej prawej stronie. Odprowadzę cię.";
				link.l1 = "Spocznij, kapralu. Wolę iść sam.";
			}
			else
			{
				dialog.text = "Kapitanie, ścieżka do obozu wroga jest po naszej prawej. Nie zgubisz się.";
				link.l1 = "Dziękuję za troskę.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Kapitan "+GetFullName(pchar)+"! Dzięki Bogu! Pozwól, że się przedstawię - porucznik "+GetFullName(npchar)+". Wielki admirator wasz! Nie wiem, co robicie na tym nędznym kawałku ziemi, ale jesteście w samą porę!\nMuszę przyznać, Kapitanie, że staliście się bardzo popularni wśród naszego korpusu oficerskiego. Chociaż wielu irytuje wasz... 'specjalny' styl służby, wszyscy zgadzają się, że wasz patent czyni naszą flotę silniejszą. Obecnie znajdujemy się w całkowicie patowej sytuacji, więc pomoc kogoś takiego jak wy będzie trudna do przecenienia!";
				link.l1 = "Co mogę zrobić? I co się tutaj dzieje?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Kapitan "+GetFullName(pchar)+" Twoje imię było wielokrotnie wspominane w raportach floty. I zawsze w bardzo wątpliwym świetle. Jednak teraz masz szansę przerwać ten mniej zaszczytny trend i służyć ojczyźnie.";
				link.l1 = "Co mogę zrobić? I co tu się dzieje?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "Byliśmy na 'Warriorze', na rutynowej misji - polując na szczególnie zuchwałych hiszpańskich korsarzy. Sprawa jest zazwyczaj bardzo prosta: szpieg dostarcza obszar i dane na temat celu, a ty chwytasz go zza horyzontu. Nie ma tu nic specjalnego do opowiadania, a wszystko skończyło się bardzo źle: Hiszpanie znaleźli nas pierwsi i zaatakowali, mimo że sami byli na korwecie. Gdybyśmy mieli coś poważniejszego, nie poszlibyśmy razem na dno... ale przynajmniej udało nam się wysadzić cały ich kadłub. Przeżył tylko mój oddział. Kastylijczycy jednak też mieli kogoś, kto przeżył. Ale nie na długo, haha!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "Fregata 'Wojownik'? Kapitan Shocke zginął?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "Nie dziwi mnie, że pytałeś o niego, Kapitanie. Słyszałem o twoim udziale w przechwyceniu 'Alcantary'. Wielki wyczyn, już wtedy położyłeś fundament pod swój patent! Komandor Shocke nie zginął, wręcz przeciwnie! Został awansowany i na jego prośbę wysłano go na służbę na Morze Śródziemne. Możemy mu tylko zazdrościć w sytuacji, w jakiej się teraz znajdujemy. Więc, właściwie, o naszej sytuacji...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "Znaleźliśmy osadę na wyspie - całkiem zaludnioną kryjówkę bandytów dla - posłuchaj tylko - piratów i Hiszpanów. Niewiarygodne! Wiesz, zazwyczaj te dranie tylko się tną i wieszają, ale tutaj - patrz: w samym centrum archipelagu, pracują razem jak rodzina, aby wydobywać drewno korsarskie. Widziałeś molo, które dla siebie zbudowali? Goście nie przychodzą do tej bandy na łódkach wiosłowych. Nasze zadanie jest niezwykle jasne: z twoją pomocą przejmujemy osadę, zabieramy drewno korsarskie i więźniów, a ty zabierzesz wszystkich do Capsterburga. Tymczasem władze same się tym zajmą... A gdy będą się tym zajmować, my poradzimy sobie z drewnem korsarskim i porządnie to uczcimy z innymi oficerami z mojej domowej eskadry!";
			link.l1 = "Co powstrzymało cię przed samodzielnym zdobyciem osady do tego czasu?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "There are probably many more bandits than us - we saw tents on the shore. And besides tents, they also have a wall, gates, cannon!";
			else sTemp = "There are probably not so many bandits, otherwise they would have kicked us out of here already, but they still have a wall, gates, cannon and plenty of time!";
			dialog.text = "Co nas powstrzymało?! Mamy tylko dwunastu strzelców i siedmiu marynarzy. Wszyscy zmęczeni i wyczerpani. Ocaliliśmy tylko pięć muszkietów, z najwyżej jednym nabojem każdy!"+sTemp+"";
			link.l1 = "   Ale czy masz plan?   ";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Posłuchaj, nie marnowaliśmy czasu. Przede wszystkim przejęliśmy tę fabrykę, zdobywając tym samym zapasy jedzenia i wody, a co najważniejsze - pełny magazyn drewna korsarskiego i ponad tuzin niewolników! I tak nie bylibyśmy w stanie pilnować niewolników, więc od razu przeprowadziliśmy rozpoznanie bojem, wysyłając ich do ataku na ich dawnych panów pod osłoną naszych muszkietów. W ten sposób dowiedzieliśmy się, że bandyci mają na stanie broń.";
			link.l1 = "Czy dobrze rozumiem, że teraz chcesz wysłać mnie i moich ludzi, abyśmy zajęli się tą bronią zamiast niewolników?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "Nie, ale możesz udać się do bandytów na negocjacje. Twoje przybycie oznacza, że ich kryjówka jest odkryta, a teraz żołnierze króla mają statek i posiłki. Cóż, podczas gdy oni nadstawiają uszu i oceniają głębokość swojej głębokości, podejdziesz jak najbliżej działa, rzucisz pod nie granat ręczny i nie dasz się zabić, dopóki nasi ludzie i twoi ludzie nie podejdą. Jeśli nie jesteś pewien, czy sobie poradzisz, spróbuj wysłać jednego ze swoich ludzi zamiast siebie.";
			link.l1 = "Pozwól mi najpierw pójść do nich bez bomby i zaproponować im kapitulację. Rozejrzę się, zrozumiem ich nastrój i siły, zasieję wątpliwości w ich duszach. Jeśli się nie poddadzą, wtedy pójdę do nich znowu, ale z bombą.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... a do tego czasu już się do ciebie przyzwyczają, więc łatwiej będzie przeprowadzić sabotaż! Sprytne! Cóż, niczego innego się po tobie nie spodziewałem, Kapitanie. Działaj, kiedy będziesz gotów. Ale jednak, oto... Może się przydać.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... a do tego czasu już się do ciebie przyzwyczają, więc będzie łatwiej przeprowadzić sabotaż. Tak zrobimy. Kontynuuj!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "Była tu długotrwała bitwa z Hiszpanami. Oba statki poszły na dno, a ocaleni wylądowali tutaj. Głównie Francuzi, ale niektórzy z naszych wrogów również zdołali przeżyć. I więcej nie musisz wiedzieć, przepraszam, Kapitanie. To tajna informacja, rozumiesz.";
			link.l1 = "Zrozumiano.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "Znaleźliśmy osadę na wyspie - całkiem zaludnione legowisko bandytów dla - posłuchaj tylko - piratów i Hiszpanów. Niewiarygodne! Wiesz, zazwyczaj te łajdaki tylko się tną i wieszają, ale tutaj - patrz: w samym sercu archipelagu, współpracują jak rodzina, by zdobyć drewno korsarskie. Widziałeś molo, które sobie zbudowali? Goście nie przypływają do tej rasy na łódkach. Nasze zadanie jest niezwykle jasne: z twoją pomocą przejmujemy osadę, zabieramy drewno korsarskie i więźniów, a ty zabierasz wszystkich do Capsterburga. Tymczasem władze same się tym zajmą... A podczas gdy będą to rozwiązywać, mogę nawet być gotów dać ci możliwość zabrania trochę cennego drewna na twoje potrzeby.";
			link.l1 = "Co przeszkodziło ci w zdobyciu osiedla na własną rękę do tego czasu?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "Masz! Jakieś wieści?";
			link.l1 = "Czy to honorowa straż?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "Oczywiście, wkrótce zostanie podjęta decyzja dotycząca naszych dalszych działań. Nie chciałbym szukać moich ludzi po całej wyspie, aby wydawać nowe rozkazy.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Wyśmienita inicjatywa! Otrzymasz swoje rozkazy. Przeprowadziłem rozpoznanie: wróg jest słaby, a działo nie ma amunicji. Rozkazuję natychmiast zaatakować kryjówkę bandytów, poruczniku. Przestań pieścić ręce. Po prostu kolejny dzień w flocie. Wykonać!";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "Moim zdaniem, mogłeś ich wziąć zaraz po 'niewolniczym' rozpoznaniu siłą. Ich obrona jest śmieszna, tylko paru poważnych wojowników. Nie ma co się zastanawiać - moglibyśmy pić zdobyczne wino, siedząc na górze żelaznego drewna.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "Potwierdzam, kapitanie!";
			link.l1 = "O...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = " I czy to są wyniki twojego rozpoznania? Rozumiem, że może być dziwne oczekiwać zbyt wiele od osoby cywilnej, ale potrzebuję faktów! Faktów, Kapitanie, nie twojej opinii!";
			link.l1 = "Obrażasz mnie, poruczniku. Meldować!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "Teraz jest z tobą ocalały kapitan hiszpańskiego statku, który zatopiłeś. Doświadczony dowódca, który wkrótce dojdzie do siebie. Jeśli się spóźnisz, on się zregeneruje i zorganizuje obronę według zasad sztuki wojennej, a wtedy będziemy mieli ciężki czas. Musimy się pospieszyć - powtarzam, są słabi i zdemoralizowani.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "Wkrótce nadejdą posiłki - by zabrać drewno korsarzy. Nie sądzę, że to blef: sam widziałeś doki i stos towarów gotowych do dostarczenia w magazynie fabryki. Musimy się spieszyć - powtarzam, są słabi i zdemoralizowani. Jeśli się opóźnisz, będziesz czekał na przybycie pirackiego statku.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Prawie połowa mieszkańców tej dziury to kobiety. Walczyłeś nie nawet przeciwko milicji: przez cały ten czas nie było przeciwko tobie więcej niż tuzin wojowników. Są słabi i zdemoralizowani.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "The cannon is out of ammunition. I've seen enough guns in my lifetime and can tell when a crew is ready to fire and when it's not. Without their artillery, they're nothing but poor warriors; they are weak and demoralized.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "Myśl o trofeach i chwale, Poruczniku! Samodzielne zwycięstwo nad hiszpańskim korsarzem, zdobycie bandyckiego gniazda i unikalnego źródła drewna bukanierskiego - to wszystko wymaga dowodzenia własnym statkiem! Powtarzam, są słabi i zdemoralizowani, czas ich rozgromić!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenna informacja, i miałeś rację, nie ma potrzeby się tu ociągać. Moi ludzie są wszyscy tutaj, jesteśmy silni, wyszkoleni i gotowi. Wszystko zakończy się w ciągu pół godziny. Kapitanie, proszę przygotować się na przyjęcie ludzi, więźniów i ładunku na swój statek. Nie będziemy się tu długo zatrzymywać.";
				link.l1 = "Wszystko gotowe, poruczniku. Czekaliśmy tylko na ciebie. Do zobaczenia później!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenne informacje. W takim razie, udaj się na nabrzeże i przygotuj swoją drużynę abordażową. Razem szturmujemy gniazdo bandytów natychmiast. Najlepsi z moich i twoich ludzi poprowadzą awangardę - to oni zdobędą bramy. Resztę omówimy po wspólnej inspekcji naszych sił. Nie zawiedź mnie i swojego kraju, "+GetFullName(pchar)+".";
				link.l1 = "...Niech tak będzie. Do zobaczenia później, poruczniku.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenne informacje, i miałeś rację, nie ma potrzeby się tu ociągać. Moi ludzie są tu wszyscy, jesteśmy silni, przeszkoleni i gotowi. Wszystko będzie skończone za pół godziny. Kapitanie, proszę przygotować się na przyjęcie ludzi, więźniów i ładunku na swój statek. Nie będziemy się tu długo ociągać.";
				link.l1 = "Wszystko gotowe, poruczniku. Czekaliśmy tylko na ciebie. Do zobaczenia później!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenna informacja. W takim razie, udaj się na dok i przygotuj swoją załogę abordażową. Razem natychmiast szturmujemy gniazdo bandytów. Najlepsi z moich i twoich ludzi poprowadzą awangardę - to oni zdobędą bramy. Resztę omówimy po wspólnej inspekcji naszych sił. Nie zawiedź mnie i swojego kraju, "+GetFullName(pchar)+".";
				link.l1 = "...Niech tak będzie. Do zobaczenia później, poruczniku.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenna informacja, i miałeś rację, nie ma potrzeby tu zwlekać. Moi ludzie są tu wszyscy, jesteśmy silni, przeszkoleni i gotowi. Wszystko zakończy się za pół godziny. Kapitanie, proszę przygotować się na przyjęcie ludzi, więźniów i ładunku na swój statek. Nie będziemy tu długo zwlekać.";
				link.l1 = "Wszystko gotowe, poruczniku. Czekaliśmy tylko na ciebie. Do zobaczenia później!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (70)", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenna informacja. W takim razie udaj się na dok i przygotuj swoją załogę abordażową. Razem szturmujemy gniazdo bandytów i to natychmiast. Najlepsi z moich i twoich ludzi poprowadzą awangardę - to oni zdobędą bramy. Resztę omówimy po wspólnym przeglądzie naszych sił. Nie zawiedź mnie i swojego kraju, "+GetFullName(pchar)+".";
				link.l1 = "...Niech tak będzie. Do zobaczenia później, poruczniku.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenna informacja i miałeś rację, nie ma potrzeby się tu ociągać. Moi ludzie są wszyscy tutaj, jesteśmy silni, przeszkoleni i gotowi. Wszystko skończy się za pół godziny. Kapitanie, proszę przygotować się na przyjęcie ludzi, więźniów i ładunku na swoim statku. Nie będziemy tu długo zwlekać.";
				link.l1 = "Wszystko gotowe, poruczniku. Czekaliśmy tylko na ciebie. Do zobaczenia później!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenne informacje. W takim razie, skieruj się na przystań i przygotuj swój zespół abordażowy. Razem szturmujemy gniazdo bandytów natychmiast. Najlepsi z moich i twoich ludzi poprowadzą awangardę - to oni zdobędą bramy. Resztę omówimy po wspólnym przeglądzie naszych sił. Nie zawiedź mnie ani swojej ojczyzny, "+GetFullName(pchar)+".";
				link.l1 = "...Niech tak będzie. Do zobaczenia później, poruczniku.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenne informacje i miałeś rację, nie ma potrzeby tu zwlekać. Moi ludzie są wszyscy tutaj, jesteśmy silni, wyszkoleni i gotowi. Wszystko zakończy się w pół godziny. Kapitanie, proszę przygotować się na przyjęcie ludzi, więźniów i ładunku na swój statek. Nie będziemy tu długo zwlekać.";
				link.l1 = "Wszystko gotowe, poruczniku. Czekaliśmy tylko na ciebie. Do zobaczenia później!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (90)", SKILL_LEADERSHIP);
				dialog.text = "Dziękuję, Kapitanie. To cenna informacja. W takim razie, udaj się na dok i przygotuj swoją drużynę abordażową. Zaatakujemy gniazdo bandytów razem i natychmiast. Najlepsi z moich i twoich ludzi poprowadzą awangardę – to oni zdobędą bramy. Resztę omówimy po wspólnym przeglądzie naszych sił. Nie zawiedź mnie i swojego kraju, "+GetFullName(pchar)+".";
				link.l1 = "...Niech tak będzie. Do zobaczenia później, poruczniku.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "I ja, idiota, podziwiałem cię! A-agh! Duma Francji, Kapitan "+GetFullName(pchar)+"!! Nie jesteś godzien swego patentu!!!";
			else dialog.text = ""+GetFullName(pchar)+", szumowino, zdrajco, i przeklęty piracie! Powinienem był zgadnąć, że ta plugawa nora to twoje śmierdzące królestwo! Francja nie zapomina ani nie wybacza ludziom takim jak ty!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "Gotowy, kapitanie? Twoja drużyna wygląda na godną!";
			link.l1 = "Dziękuję, poruczniku. Czy możemy zacząć?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "Tak, ruszajmy natychmiast!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "Ha! "+GetFullName(pchar)+"! Cóż za spotkanie. Hej, złapcie go! Ten drań jest właścicielem wszystkiego tutaj! To jego wyspa!";
			link.l1 = "Co za dzień...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Kapitanie, jakie są rozkazy? Jest sygnał, by być w gotowości i wysłać abordażystów.";
			link.l1 = "Rozkaz obowiązuje. Chłopcy, za mną, musimy oczyścić nasz dom z nieproszonych gości. Nagroda jest moja, wszystkie trofea są wasze!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "Hura!";
			link.l1 = "Do boju!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Witajcie, senor. Czy jesteście właścicielem tej ziemi? Pozwólcie, że się przedstawię, Wielki Francisco de Alba, były kapitan korwety 'Perro Marino'.";
			link.l1 = "Tak, to jest moja ziemia. Ja jestem "+GetFullName(pchar)+", kapitan statku '"+pchar.ship.name+"'. Wielmożny? Nie mieliśmy tu wcześniej tak znamienitych gości.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "O, Monsieur "+GetFullName(pchar)+"! Twoje imię jest dobrze znane. Widzisz, ostatnio twoje imię tak często pojawiało się w raportach Casa de Contratacion, że naprawdę spodziewałem się rozkazów, by się z tobą rozprawić.";
			link.l1 = "Chcesz ubić ze mną interes?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = " Myślę, że nie ma sensu udawać. Moim zadaniem jest szukać i niszczyć wrogów Hiszpanii i króla Filipa na wszystkich morzach świata.";
			link.l1 = "To szczęście, że takie rozkazy jeszcze nie nadeszły. Jesteś oczywiście bardzo utalentowanym oficerem marynarki.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "To, że teraz jestem pół-martwym więźniem na maleńkiej wyspie pełnej piratów, a moi rodacy są w ucieczce, tylko potwierdza twoje wnioski, ha-ha! To była bardzo niebezpieczna sprawa, ale rozkazy to rozkazy. Prawie się udało! Bardzo żałuję moich ludzi - znałem ich wszystkich po imieniu, służyliśmy razem przez wiele lat. Ale mój kraj będzie musiał przelać więcej krwi swoich synów, by utrzymać swój status imperium. Nasza rodzina wie to lepiej niż większość.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Wracajmy teraz do bardziej palących spraw. Cóż mam z tobą począć, Grand?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "A tak przy okazji, Monsieur de Mor, 'Wojownik' - ten mały statek był ci znajomy, prawda? Twoja śmiała operacja w Porto Bello nie przeszła niezauważona. Odważna, wręcz samobójcza. Bardzo potrzebowałeś pieniędzy, mam rację? Ha!";
			link.l1 = "Dużo o mnie wiesz, Grand. Ale przejdźmy do twojego losu.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "Co tu jest do rozważenia? Jak w każdej dobrej historii, masz trzy opcje: zabić mnie, zostawić tutaj albo uwolnić. Jeśli mnie uwolnisz, daję ci słowo rodziny de Alba, że nigdy nikomu nie powiem o tym miejscu i twoim zaangażowaniu w moje nieszczęścia. Co więcej, będę twoim dłużnikiem, i dopóki ten dług nie zostanie spłacony, nigdy nie stanę przeciwko tobie.";
			link.l1 = "Nie mogę ryzykować, Grand.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "Spędzisz tu trochę czasu. Będziesz żyć i pracować na równych warunkach ze swoimi rodakami.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Witamy na pokładzie mojego statku, Grand. Wysadzę cię przy latarni morskiej w Santiago, gdy nadejdzie czas. Mam nadzieję, że dotrzymasz słowa.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "Rozumiem, señor. Cóż, w każdym razie, już jestem martwy w tej bitwie razem z moimi ludźmi. To dobre zakończenie.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "Przyznaję, nie lubię być nieśmiałym. Ale nie ma hańby w byciu więźniem, więc przyjmuję twój dar życia i będę żyć w pokoju z tymi miłymi i najwyraźniej bardzo szczęśliwymi ludźmi. Niemniej jednak, jeśli kiedykolwiek opuszczę to miejsce, nie będę ci nic winien.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "Dam ci moje słowo i słowo rodziny de Alba! Do zobaczenia na statku!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Kapitan "+GetFullName(pchar)+"! You saved my life and brought me back to my own. I understand how difficult it was to take such a risk - I would never have dared to do such a thing. I owe you, senor. I give you my word that I will never tell anyone about the circumstances of that ill-fated battle. When you return to the Old World, be sure to find me; you will always be welcome at our family estate in Madrid. For now, take this...";
			link.l1 = "Kawałek mapy?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "To wszystko, co miałem przy sobie wartościowego. Nie mam wątpliwości, że łatwo znajdziesz drugi kawałek. Żegnaj! I powodzenia, mój przyjacielu.";
			link.l1 = "Żegnaj, Grand. Pamiętaj o swoim słowie i powodzenia!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("Witajcie! Jak się macie, Kapitanie? Wszystko idzie dobrze dla nas.","Praca dla społeczności to największa radość!","Twoja wyspa jest wspaniała, kapitanie, i zrobimy wszystko dla jej dobrobytu.");
			link.l1 = LinkRandPhrase("Miło to słyszeć.","Cieszę się, że wszystko w porządku.","Podziwiam twój entuzjazm, amigo.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Nie bierz tego za bezczelność, señor, ale życie tutaj jest niemożliwe.","Wszystko jest lepsze niż siedzenie w celach Inkwizycji..."),RandPhraseSimple("Dziękujemy za uratowanie nas, Kapitanie.","Czy ci... piraci to twoi przyjaciele?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Nie jest tu źle! Tylko trochę nudno.","Kapitanie, miło cię widzieć. Wpadnij kiedyś!"),RandPhraseSimple("Ktoś znalazł czaszki na plaży i przyniósł je na poranne spotkanie. Czy zawsze tak tu jest?","Powiem ci sekret, Senor Himenes wyraźnie korzysta ze świeżego powietrza i bezpieczeństwa tego miejsca."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Nie jest tu źle! Tylko trochę nudno.","Kapitanie, miło cię widzieć. Wpadnij kiedyś!"),RandPhraseSimple("Ktoś znalazł czaszki na plaży i przyniósł je na poranne spotkanie. Czy zawsze tak tu jest?","Powiem ci sekret, Señor Himenes wyraźnie korzysta z świeżego powietrza i bezpieczeństwa tego miejsca."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Niech cię Bóg błogosławi, Kapitanie!","Raz w tygodniu organizujemy występy na plaży i w tawernie. Wpadnij kiedyś."),RandPhraseSimple("Twoi marynarze ciągle przynoszą nam wszelkiego rodzaju błyskotki w zamian za świeże jedzenie. Dziękujemy za zachęcanie do tego.","To niesamowite, że to miejsce jeszcze nie zostało odkryte. Mam nadzieję, że tak pozostanie."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Dziękuję, senor. Dzięki tobie ujrzeliśmy prawdziwy Nowy Świat. Niech cię Bóg błogosławi!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("Bezpieczeństwo i spokój - to mi się tu podoba!","Wspaniały raj! No, prawie...","Jesteśmy szczęśliwi, że znaleźliśmy tu nowy dom, po tylu trudnościach.");
			link.l1 = LinkRandPhrase("Jestem szczęśliwy z powodu ciebie i twojej społeczności.","Tak, ja również lubię tę małą wyspę.","Miło wiedzieć, że jesteś zadowolony.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Oh... Witaj.","Seniorze, kim są ci... szorstcy ludzie z bronią?","Dziękujemy, że nas uratowałeś, Kapitanie.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase(" Nasi ludzie wykonali świetną robotę - domy są doskonałe. Ale my też ciężko pracowaliśmy!","Senor Kapitanie, nie martw się: kobiety naszego małego klanu nie boją się trudności i tymczasowych niewygód.","Takie powietrze tutaj! I morze! Czujesz się bliżej Boga!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("Nasi ludzie wykonali świetną robotę - domy są doskonałe. Ale my też ciężko pracowaliśmy!","Senor Kapitanie, nie martw się: kobiety naszego małego klanu nie boją się trudności i tymczasowych niedogodności.","Co za powietrze tutaj! I morze! Czujesz się bliżej Boga!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Wracaj częściej, Senor Kapitanie. Zawsze się cieszę na twój widok.","Senor Rodgar to niesamowity gawędziarz. Można go słuchać bez końca!","Hehe. Mówią, że ktoś z naszej grupy już oczekuje powiększenia rodziny. Życie toczy się dalej nawet na Isla Mona!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "Ty... Muchas gracias, señor! Przybywaj częściej...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Wszystko w porządku, Kapitanie!","Niewolnicy pod kontrolą, nie martw się."),RandPhraseSimple("Nie musisz się martwić, bunt jest wykluczony.","Dziękujemy za rum! Zabieramy się do pracy!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Hiszpanie? Nie spodziewaliśmy się tego po was.","Teraz musimy iść całą drogę na plażę, aby tylko spać w spokoju!"),RandPhraseSimple(" Dlaczego zdecydowałeś się na to wszystko - co, kapitanie?","Szef ci wtedy ufał - i nie pomylił się. Znowu w ciebie uwierzymy."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("Po wyczerpującej harówce, nie grzechem jest wypić kielicha lub dwa...","I'm almost done and heading home; the wife must be waiting...","Ah, it's nice to relax in our tavern after work! We're all grateful to you, captain!");
			link.l1 = LinkRandPhrase("Ciesz się napitkiem, kompadre, ha-ha!","Odpocznij, kumplu, tylko nie przesadzaj, bo żona cię zgani, ha-ha!","Weź to na luz, kumplu, życie to nie tylko praca!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Who's that pretty mulatto woman living here?";
				else sTemp = "Captain, nice place you got here!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("Kapitanie, masz tu niezłe miejsce!","Wyobraź sobie, że nagle zostalibyśmy pozbawieni rumu. Z pewnością zdobyłbyś więcej, prawda?"),RandPhraseSimple("Marzyłem o takich wakacjach od dawna. Chciałbym jednak burdel... ot, taka dzika myśl, Kapitanie.",sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Dzięki za wakacje, kapitanie.","Ładne miejsce, które tu zbudowaliście - macie talent do utrzymywania porządku, kapitanie."),RandPhraseSimple("Świeże żarcie, gorzała, twardy grunt pod stopami. To jak sen.","Chciałbym zostać tu trochę dłużej."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Jestem tak zmęczony - ledwo mogę ustać.","Nie mam już siły tak żyć!"),RandPhraseSimple("Ta robota jest dla mnie zbyt ciężka.","Nadzorcy nie zostawili żywej komórki na mojej skórze!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("Czy mogę ci w czymś pomóc, kapitanie?","Wejdź, spróbuj lokalnej paelli. Tylko na miłość boską, nie pytaj, z czego jest zrobiona!","Witamy, kapitanie. Jak ci się tu podoba?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("Witaj, señorze!","Witaj, kapitanie. Czy zostaniesz?","Przychodzisz do mnie? Proszę, wejdź, nie zwracaj uwagi na bałagan, señor.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}