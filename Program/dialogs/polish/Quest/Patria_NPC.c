// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "Czego szukasz?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "Miło cię poznać, kapitanie!";
			link.l1 = "Miło mi cię poznać również, monsieur Forget. To rzadka okazja spotkać gościa z metropolii tutaj na pustkowiu...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "Jestem rad, że podczas tej podróży będę na twoim statku, kapitanie. Chevalier de Poincy opowiedział mi wiele interesujących historii o tobie. Jestem pewien, że po kolacji w mesie będziemy mieli mnóstwo tematów do omówienia. Kieliszek wina również mógłby się przydać.";
			link.l1 = "Jestem całkowicie gotowy na przyjemną rozmowę, zwłaszcza gdy jestem najedzony. Byłbym zadowolony być twoim towarzyszem, Baronie.";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Doskonałe. Gdy dotrzemy do kolonii, poproszę cię, abyś zaprowadził mnie do gubernatora, a ja osobiście wyjaśnię mu, co należy zrobić. Ty po prostu poczekasz, aż zakończę swoje sprawy. Zgoda?";
			link.l1 = "Aye, monsieur Forget. Witaj na pokładzie!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "Tortuga to mała kolonia, kapitanie. Szacuję, że zajmie mi około trzech dni, aby zbadać wszystko, co potrzebuję na tej wyspie.";
			link.l1 = "Zrozumiano, baronie. Zatem za trzy dni przybędę tutaj, by cię odebrać. Powodzenia!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "Moja praca na Tortudze jest skończona, czas podnieść kotwicę.";
			link.l1 = "Zrozumiano, Baronie. Natychmiast ruszamy w drogę.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Tak-tak, na pewno zgłosimy to w Capsterville. Zagrożenie zdobycia tak ważnej kolonii... nie do pomyślenia, osobiście dopilnuję, aby Chevalier de Poincy podjął surowe i bezwzględne środki! Kapitanie, pozostanę na tej wyspie przez tydzień, jest tu wiele plantacji, to zajmie trochę czasu.";
			link.l1 = "Zrozumiano, Baronie. Będę czekał na ciebie przy pałacu gubernatora za siedem dni. Baw się dobrze i nie przepracowuj się!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "Tam jesteś, kapitanie. Moja praca na Hipanioli jest skończona, czas podnieść kotwicę.";
			link.l1 = "Zrozumiano, Baronie. Wyruszymy natychmiast.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Kapitanie, ta wyspa wydaje mi się znajoma. Czyż to nie jest Święty Krzysztof?";
			link.l1 = "Tak, baronie, dokładnie. Prawie tam jesteśmy.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "Prawie tam?! Czy nie mieliśmy odwiedzić też Saint-Martin? To również należy do francuskich kolonii.";
			link.l1 = "Mówisz o Sint Maarten? To holenderska kolonia, monsieur Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "Czyżby? W Paryżu uważano to za francuskie. Jak to możliwe?";
			link.l1 = "Nie mam pojęcia, Baronie. Odkąd po raz pierwszy postawiłem stopę na archipelagu, Sint Maarten było holenderską kolonią. Może o czymś nie wiem. Powinieneś rozważyć rozmowę z Chevalierem de Poincy w tej sprawie.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "Dobrze, kapitanie, niech tak będzie. I tak prawie jesteśmy w Capsterville.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", kapitanie. Cieszę się, że cię widzę. Słyszałem, że awansowałeś, przyjmij moje gratulacje! Prawdę mówiąc, naprawdę jesteś jednym z najbardziej rozsądnych i utalentowanych oficerów w służbie de Poincy'ego.";
			link.l1 = "Dziękuję, monsieur.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "W końcu pozostała tylko jedna kolonia, Saint-Martin. Szczerze mówiąc, zmęczyły mnie już te podróże. Będę zadowolony, gdy zakończę tę inspekcję i zacznę przygotowywać następną kampanię handlową Francuskich Indii Zachodnich. Czy jesteśmy gotowi, by podnieść kotwicę?";
			link.l1 = "Tak jest, baronie. Wsiadaj na pokład.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Kapitanie, czy mógłbyś mi powiedzieć, co się właśnie stało? Czy to oznacza wojnę? Dlaczego, na miłość boską, prawie zostaliśmy zatopieni przez Holendrów?";
			link.l1 = "Baronie, sam nic nie rozumiem! To musi być jakieś nieporozumienie, bez wątpienia.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "Kapitanie, mogę się założyć, że to 'nieporozumienie' ma imię! Peter Stuyvesant, tak zwany 'najemca' Saint-Martin i wspólnik naszego drogiego Chevaliera de Poincy!";
			link.l1 = "Nie mam pojęcia, Baron. Lepiej się pospieszyć do Capsterville i zameldować o tej sprawie Gubernatorowi Generalnemu.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "Bez wątpienia, to właśnie zrobimy! I zażądam wyjaśnień! Wiedziałem, że wynajęcie wyspy Holendrom to był duży błąd! Opuszczajmy to miejsce jak najszybciej, kapitanie, zanim ktoś zdecyduje się nas ścigać!";
			link.l1 = "Dokładnie, monsieur ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Monsieur, najpierw pozwól mi pogratulować Ci awansu! Gorąco poparłem decyzję monseigneur de Poincy o przyznaniu Ci rangi wiceadmirała. Zasługujesz na ten tytuł! Właśnie wróciłem z Saint-Martin. W magazynach Philipsburg przeprowadziliśmy kontrolę, skonfiskowano wszystkie holenderskie towary i teraz należą do skarbu Francji. Ty, jako dowódca operacji bojowej, otrzymałeś udział w łupach. Zgadzam się z Chevalierem, że to sprawiedliwe. Twoje towary zostały przeniesione do magazynu sklepu na St. Christopher, i możesz je odebrać, kiedy tylko chcesz.";
			link.l1 = "Dziękuję, Baronie. Niech towary tam pozostaną na jakiś czas. Po moim powrocie z Curacao, je zabiorę.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "Powodzenia w następnej kampanii, Wiceadmirał! Jestem pewien, że powrócisz z zwycięstwem i sprawiedliwie ukarzesz tego łajdaka Stuyvesanta.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "Któż to do nas zawitał! Wiceadmirał Charles de Maure! Cieszę się, że cię widzę! Co cię sprowadza do Port-au-Prince?";
			link.l1 = "Miło mi również cię poznać, Baronie. Jestem tu z powodu moich obowiązków, musiałem złożyć monsieur Jeremy'emu Deschamps du Mussaca wizytę grzecznościową...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "To spotkanie jest naprawdę szczęśliwe, ponieważ długo czekałem, aby spotkać się z tobą osobiście. Chcę z tobą porozmawiać, ale nie tutaj.";
			link.l1 = "Chodźmy zatem do tawerny, co?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "Nie ma tu niepożądanych uszu, możemy rozmawiać bezpiecznie...";
			link.l1 = "Zamieniam się w słuch, Baronie.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Wiceadmirał, zdajesz się być człowiekiem honoru. Taki dzielny oficer marynarki po prostu musi taki być...";
			link.l1 = "Hmm... Myślę, że nie do końca cię rozumiem, monsieur...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Monsieur de Maure, chciałem cię zapytać: co myślisz o swoim suwerenie, gubernatorze generalnym Philippe de Poincy?";
			link.l1 = "Obowiązkiem oficera nie jest myśleć o swoim dowódcy, lecz wykonywać jego rozkazy.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Oh, zostaw to, Wiceadmirał, nie jesteśmy w koszarach ani w sali de Poincy'ego. Powiem to w ten sposób: czy nie uważasz, że monsieur de Poincy... nadużywa swojej władzy? Wciąż nie mogę zapomnieć, jak prawie poszliśmy na dno pod działami Fortu Saint-Martin. Jestem pewien, że zdrada Holendrów miała powód.";
			link.l1 = "Chcieli podbić wyspę.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Tak, tak, ale dlaczego dokładnie w tym samym momencie, kiedy postanowiłem to sprawdzić? Dlaczego nie miesiąc wcześniej? Albo dwa miesiące później? Nie wierzę, że to był przypadek, monseigneur. Nie masz żadnych podejrzeń? Oboje mieliśmy tam nasze życie na szali.";
			link.l1 = "Ryzykuję życie każdego dnia, monseigneur Forget. Myślę, że to rozumiesz...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "Twoja odwaga jest niezaprzeczalna. Ale to nie to, co chciałem powiedzieć. Widzisz... Kiedy wykonywałem swoją pracę na Saint-Martin, który został wyzwolony przez ciebie, wielokrotnie słyszałem szepty od miejscowych o jakiejś kopalni w głębi wyspy. Próbowałem pytać ludzi o to, ale tylko udawali głupich. Bali się... Było oczywiste, że nie wydawałem się zbyt godny zaufania, ale to tylko wzmocniło moje podejrzenia: czy ta tajemnicza kopalnia może być przyczyną tego wszystkiego, Monsieur de Maure? Wojny toczą się z powodu złota, prawda?";
			link.l1 = "Na archipelagu znajduje się wiele kopalni. Większość z nich jest wyczerpana i stała się bezwartościowa. Znam jedną dużą działającą kopalnię złota, którą posiadają Hiszpanie na Południowej Głównej. Ale nigdy nie słyszałem o wydobywaniu złota na Saint-Martin.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "Jesteście biegli w sztuce retoryki, Wiceadmirał! Rozumiem: nie ufacie mi. Jestem tu nowy... Monsieur de Maure, ale jestem wpływową osobą w Paryżu. Minister Finansów to mój bliski przyjaciel. Regularnie odwiedzam króla. Moja władza jest znacznie większa niż władza Philippe'a de Poincy, formalnie, oczywiście, bo tutaj gubernator generalny jest najważniejszą osobą. Ale prawdę mówiąc, tutaj, w koloniach, rządzi tylko prawo najsilniejszego.";
			link.l1 = "Całkowicie się z tobą zgadzam.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "Ale nie w Paryżu. Tam najbardziej wpływowymi osobami są Król i Minister Finansów... mój bliski przyjaciel. Monsieur de Maure, jesteś genialnym wojskowym, ale wierzę, że Phillip de Poincy wykorzystuje cię do własnych celów. Jesteś inteligentny, więc musisz mieć podejrzenia. Możesz mi zaufać. Gwarantuję ci pełną anonimowość i wsparcie władz Paryża. Przysięgam na mój tytuł.";
			link.l1 = "***POZOSTAŃ WIERNY POINCY***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***STRONA Z BARONEM FORGETEM***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "Rozumiem cię, Monsieur Forger. Dla człowieka nieobeznanego z lokalnym sposobem myślenia, działania de Poincy'ego mogą rzeczywiście wydawać się dziwne. Kiedy po raz pierwszy przybyłem na Archipelag, byłem dosłownie wstrząśnięty tym, co się tutaj dzieje. Wciąż pamiętam pierwsze słowa, które mi powiedziano: 'Jeśli spotkasz niechroniony hiszpański statek, możesz spróbować go abordażować.' Zdrada, oszustwo, podstęp - są tutaj obecne na każdym kroku. Piractwo, grabież, rabunek...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "Jesteśmy w stanie pokoju z Hiszpanią w Europie. Ale tutaj jesteśmy zaciekłymi wrogami. Holendrzy dzisiaj wydają się przyjaźni i nieszkodliwi, a jutro urzędnik Kompanii konfiskuje twoje towary tylko dlatego, że nagle ogłoszono, że są zakazane do importu, chociaż nie mogłeś o tym wiedzieć. Angielski oficer otwarcie piratuje, zatapiając statki Kompanii, a Kompania wynajmuje zbira, który udaje statek widmo i przeraża brytyjskich kupców...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "W tej wilczej norze czasami musimy podejmować dziwne decyzje, które nie są do końca oczywiste dla kogoś nieznającego tego wszystkiego. A to, co wydaje się podejrzane dla ciebie, jest w rzeczywistości jedynym słusznym działaniem. Trudno jest jednocześnie siedzieć na kilku krzesłach i nadal zarządzać wysyłaniem zysków do macierzystego państwa. Chevalier de Poincy radzi sobie z tym doskonale, jest doświadczonym zarządcą i wizjonerskim politykiem. Oczywiście, może popełniać błędy, ale wszyscy je popełniamy w pewnym momencie naszego życia...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "I musisz się liczyć ze wszystkim i ze wszystkimi. Z ambicjami Hiszpanów, którzy wierzą, że cały Nowy Świat należy do nich, z chciwością holenderskich kupców, z zimną rozwagą i bezwzględną brutalnością Anglików. A nawet z piratami.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "Z piratami?!";
			link.l1 = "Tak, dobrze słyszałeś. Holendrzy i Brytyjczycy aktywnie współpracują z piratami... nieoficjalnie, oczywiście. Bractwo Wybrzeża to poważna siła, która może rzucić wyzwanie każdemu narodowi w regionie, są w ciągłym konflikcie z każdym, kogo napotkają i nikt nie jest w stanie ich powstrzymać. Jedyną rzeczą, która czyni ich nieco mniej niebezpiecznymi, jest fakt, że są rozproszeni i działają na własną rękę. Czy wiedziałeś, że były gubernator Tortugi, Levasseur, faktycznie stworzył państwo w państwie, opierając się całkowicie na piratach?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "Wierzę, że coś o tym słyszałem...";
			link.l1 = "Kilka potężnych okrętów kaperskich, które chroniły wyspę, było stale zacumowanych w porcie Tortugi. Levasseur zdradził Francję, stając się swego rodzaju lokalną władzą. A teraz, po zniszczeniu pirackiego gniazda na Tortudze wraz z ich przywódcą, piraci są strasznie wściekli na Francuzów...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "Nie mówisz!";
			link.l1 = "Tak. Musieliśmy to zrobić, w przeciwnym razie Tortuga byłaby dla nas stracona, chociaż wynik, który uzyskaliśmy, nie był najlepszy. Żaden francuski statek handlowy nie może teraz czuć się bezpiecznie na Karaibach. Hiszpanie, którzy również nie mają umów z baronami pirackimi, przynajmniej mają floty silnych galeonów i potężnych okrętów wojennych zdolnych do odparcia filibustierów. Podobnie jak Holendrzy z ich Wschodnimi Indiami i xebecami. Ale nie możemy się czymś takim pochwalić, niestety. A francuscy piraci często rabują francuskich kupców.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "To szaleństwo! Czy nie ma sposobu, by położyć temu kres?";
			link.l1 = "Wielu próbowało. W końcu, zamiast walczyć, kupują ich lojalność złotem. Wydają listy kaperskie, mam na myśli.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Hmm...";
			link.l1 = "Zatem, mówiąc z doświadczenia, francuska kompania handlowa tutaj na Archipelagu to bardzo zły pomysł. Czy teraz rozumiesz, z jakimi trudnościami będziesz musiał się zmierzyć? Ile szubrawców chce tu uszczknąć swoją część dochodów? I nie zamierzają łatwo z tego rezygnować. A piraci, oni są zdolni do niewyobrażalnych rzeczy, nazwij ich szaleńcami, jeśli chcesz, ale prawie zawsze osiągają swoje brudne cele. Aby chronić statki handlowe, musiałbyś utrzymywać ogromną flotę wojenną, ale czy to będzie opłacalne z finansowego punktu widzenia?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "A francuscy kupcy jakoś sobie tutaj radzą?";
			link.l1 = "Dokładnie, jakoś. Zwłaszcza teraz, gdy forteca piracka Levasseura na Tortudze została zdobyta...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Twoje słowa zgadzają się z tym, co powiedział de Poincy.";
			link.l1 = "To prawda. Tak tu jest na archipelagu, zawsze tak było.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "Jesteś tak chętny w tym, co mówisz. Nawet ja nie wiedziałem o wielu z tych rzeczy i, masz rację: wciąż nie wiem. Myślę, że moje podejrzenia wobec Poincy były niewłaściwe. Otworzyłeś mi oczy. Dziękuję ci, Wiceadmirał. Ale francuski minister liczy na stworzenie Kompanii. Król potrzebuje pieniędzy...";
			link.l1 = "Rozumiem. Ale proszę, weź pod uwagę to, co właśnie powiedziałem, jeśli stworzenie Francuskich Indii Zachodnich jest nieuniknione, to proszę upewnić się, że mamy silną flotę wojenną, aby je chronić.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "Wasza łaska jest naprawdę godna podziwu, Wiceadmirał! Taki szlachetny temperament! Nie dziwię się, że byliście tu tak długo i nie spieszyliście się z powrotem do domu. Ale zobaczymy się ponownie: wrócę tu za pół roku. Francuska Kompania Handlowa powstanie. A z piratami, myślę, że trochę przesadzacie. W końcu mamy okręty wojenne i dzielnych kapitanów, takich jak wy.";
			link.l1 = "Przykro mi, Baronie, ale jestem tylko jednym człowiekiem, a oprócz mnie Francja ma tylko jeden silny statek w archipelagu 'Eclatant', to nie wystarczy, stracimy dużo więcej niż zyskamy... Eh, cóż, jak to się mówi, jak jest, tak jest, myślę, że coś wymyślimy w międzyczasie... Kiedy będziesz się wybierał do Francji?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "W ciągu dwóch tygodni wrócę do Saint Christopher, a stamtąd udam się do domu. Monsieur de Poincy dał mi dobrą łajbę - bryg o nazwie 'Favory' i wspaniałego kapitana. Statek jest szybki, a kapitan doświadczony, ale oczywiście byłem bezpieczniejszy z tobą. Pamiętam nasze podróże przez archipelag, Wiceadmirał, to było naprawdę cudowne doświadczenie.";
			link.l1 = "Dziękuję za miłe słowa, Baronie. Cóż, chyba nadszedł czas, byśmy się rozstali...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Wszyscy tutaj się wykorzystują nawzajem. Chevalier używał mnie w swoich sprawach długo zanim zostałem oficerem marynarki.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "I czy to jest akceptowalne? Co o tym sądzisz?";
			link.l1 = "Nie. Ale Chevalier nie dał mi wyboru: albo wykonam jego rozkazy, albo mój brat pozostanie za kratami do końca swoich dni, a dobre imię mojej rodziny zostanie zniszczone.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "Okropne! To czysty terroryzm! Czy miał jakiś powód dla takich gróźb?";
			link.l1 = "Mój brat miał nieszczęście być jego zaufanym człowiekiem. Tak jak ja teraz.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "Gdzie jest teraz twój brat?";
			link.l1 = "Udało mi się go uwolnić, ale straciłem go już następnego dnia, wybrał, że nie będzie już nikomu służyć.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "Wiedziałem, że Poincy nie jest tym, za kogo się podaje! Wilk w owczej skórze! Wiceadmirał, możesz mi zaufać. Jestem człowiekiem honoru. I uwolnię cię od tego jarzma twego 'patrona', jeśli znajdziemy namacalne dowody jego przestępczej działalności. Czy wiesz coś o tej nudnej historii ze Stuyvesantem? Mów otwarcie, i nie martw się, jesteś tylko wojskowym i byłeś zobowiązany wykonywać swoje rozkazy.";
			link.l1 = "  Wiem. Rzeczywiście, na Saint-Martin jest kopalnia. Tylko że nie wydobywają tam złota, lecz sól. Hiszpanie bardzo jej potrzebują. Poincy nie mógł handlować z Hiszpanami bezpośrednio, więc Stuyvesant działał jako pośrednik.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "Więc Poincy i Stuyvesant są partnerami w interesach?";
			link.l1 = "Kiedyś tak było. Po tym jak wyraziłeś chęć inspekcji Saint-Martin, Stuyvesant postanowił wyeliminować Poincy'ego z gry, zagarniając wszystkie zyski z kopalni soli dla siebie. Poincy nie mógł nikomu powiedzieć... Ale Stuyvesant się przeliczył, jak widzimy.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "Czy myślisz, że kopalnia nadal działa?";
			link.l1 = "Jestem tego pewien. Wygląda na to, że Poincy ma teraz nowego sojusznika handlowego. To nikt inny jak sam pułkownik Doily.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "Czy możemy przedstawić jakieś dowody ministerstwu?";
			link.l1 = "Hmm. Podczas szturmu na kopalnię, który, nawiasem mówiąc, prowadzony był przez Hiszpanów, a nie Holendrów, schwytaliśmy właściciela. Jest on nadal na moim statku. Możesz z nim porozmawiać. Jest szansa, że w zamian za wolność opowie wiele interesujących rzeczy.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Chodźmy natychmiast na twój statek. Rozkaż, aby twój więzień został dostarczony do twojej kajuty. Porozmawiam z nim.";
			link.l1 = "Zgoda, chodźmy.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Świetnie, wiceadmirale. Porozmawiam z nim. Proszę, zostań tutaj.";
			link.l1 = "Oczywiście...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "Spisałem wszystkie dowody dotyczące twojego jeńca, a on je podpisał. Teraz musimy spełnić to, co mu obiecałem, gdy tylko nadarzy się dogodna okazja, zatrzymajmy się w Kartagenie i pozwólmy mu wysiąść. Ale sam wszystko słyszałeś\nCo za drań z tego naszego Poincy! Wynajął wyspę Holendrom, prowadził tam nielegalne interesy i pozwolił Hiszpanom tam przybywać i zarządzać kopalnią! Boję się pomyśleć, ile pieniędzy brakuje w skarbie królewskim z powodu jego egoizmu!";
			link.l1 = "Czy te dowody wystarczą, by postawić Poincy'ego w stan oskarżenia?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Niestety, obawiam się, że nie. Dowody są bardzo ważne, ale to nie wystarczy. Ale nie chcę, abyś był w to wszystko zaangażowany z powodów, które obaj rozumiemy.";
			link.l1 = "Hiszpan zgodził się zeznawać przed waszą komisją, gdy ta tu dotrze.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "To się stanie nie wcześniej niż za sześć miesięcy, a kto wie, co stanie się z tym Hiszpanem, i czy będziemy w stanie go później odnaleźć w Kartagenie... Musimy mieć jeszcze bardziej wartościowe dowody. Mianowicie - dowód, że kopalnia wciąż prowadzi tajne działania i nadal napełnia kieszenie naszego drogiego gubernatora generalnego.";
			link.l1 = "Więc sugerujesz, żebyśmy popłynęli na Saint-Martin?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Tak. Czy wiesz, jak dostać się do kopalni?";
			link.l1 = "Tak.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "Wtedy, w nocy, ty i ja zakradniemy się tam, cicho, by nikt nas nie zobaczył, i sprawdzimy, co się tam dzieje.";
			link.l1 = "Bardzo dobrze.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "A co z Kawalerem, co? Teraz rozumiem, dlaczego z taką odwagą zasugerował mi, że założenie Francuskiej Kompanii Handlowej na Archipelagu byłoby nieopłacalne... Oczywiście, dla niego byłoby to bardzo nieopłacalne!";
			link.l1 = "Skoro teraz jesteśmy sojusznikami, Baronie, powiem ci całą prawdę, Poincy poprosił mnie... abym cię przekonał, żebyś nie zakładał tutaj Kompanii Handlowej.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "Więc tak to jest! Mam nadzieję, że przynajmniej nie poprosił cię, byś mnie wyeliminował szablą lub pistoletem?";
			link.l1 = "Nie. Trzeba było cię przekonać w inny sposób.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "Poincy zapłaci za to, ale teraz musimy natychmiast żeglować do Saint-Martin. Hiszpan zostanie dostarczony na Main później. Wyruszamy, wiceadmirał!";
			link.l1 = "To będzie trochę dziwne, że opuszczasz wyspę na moim statku, nie sądzisz?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "Nie sądzę. Czyż nie miałeś mnie przekonać? Właśnie to zrobiłeś, haha! Tak, zanim popłynę do Europy, powiem Kawalerowi, że zgadzam się z jego argumentami i Kompania Handlowa nie zostanie utworzona. Niech żyje w błogiej iluzji, na razie... Ruszajmy!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "  Prowadź, wiceadmirał. Noc ukryje nas w swoim całunie ciemności.  ";
			link.l1 = "Chodź za mną...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(szeptem) Widziałem to! Widziałem to! Widziałeś to? Czerwone kurtki! To angielscy żołnierze!";
			link.l1 = "Powiedziałem ci - Poincy teraz prowadzi interesy z pułkownikiem Doily.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "Miałeś rację. Widziałem wystarczająco. Teraz wynośmy się stąd, jak najszybciej, zanim nas zauważą!";
			link.l1 = "Zgoda...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "Widzisz, do czego prowadzą 'komercyjne projekty' naszego drogiego Kawalera! Anglicy zachowują się jak gospodarze na francuskiej wyspie! To oburzające!";
			link.l1 = "Musimy się ruszać, bo ktoś na pewno tu przyjdzie. Nie możemy sobie pozwolić na rozpoznanie.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Wiceadmirał, cały czas myślałem podczas naszej podróży do Saint-Martin i zdecydowałem się na coś: czy możesz zorganizować mi spotkanie z Peterem Stuyvesantem?";
			link.l1 = "Ze Stuyvesantem? Ale dlaczego?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "Były wspólnik biznesowy może mieć poważne wskazówki i poważne dowody na udział Chevalierów. Jestem pewien, że Stuyvesant nie jest zbyt zadowolony z Poincy i będzie szukał zemsty, zwłaszcza po tych ostatnich wydarzeniach...";
			link.l1 = "Wierzę, baronie. Osobiście nie odważę się pójść do pałacu Stuyvesanta. To zbyt ryzykowne dla mnie, po wszystkim, co im uczyniłem...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "Już o tym myślałem. Popłyniemy na Curacao, wysiądziemy w zatoce daleko od miasta i wyślemy naszego pojmanego Hiszpana z kopalni z listem do Stuyvesanta. Nie wspomnę tam o tobie, zamiast tego poinformuję go, że prowadzę śledztwo przeciwko Poincy'emu czy coś w tym stylu. Myślę, że Holender przybędzie na spotkanie.";
			link.l1 = "Hmm. Nie sądzę, że to dobry pomysł. Stuyvesant nie jest głupcem, bierze, co może, może nawet spróbować cię uwięzić i zażądać ogromnego okupu, ale jeśli sprawimy, że uwierzy, że wszystko, co się stało, było z powodu Poincy'ego, może stanąć po naszej stronie. Cóż, jeśli jesteś tak zdeterminowany, spróbujmy.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Panie de Maure, proszę wybaczyć moją głupotę. Miałeś rację co do Stuyvesanta. Powinienem był się domyślić, że tylko jeszcze większy łajdak mógłby wyzwać de Poincy'ego!";
			link.l1 = "Hah! Milion... Poincy chciał milion, Stuyvesant chce milion... Wygląda na to, że kręcimy się w kółko...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "O czym mówisz, wiceadmirał?";
			link.l1 = "Kiedy przybyłem na Karaiby, Poincy chciał, żebym zapłacił milion jako okup za mojego brata.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "I tyle zapłaciłeś?";
			link.l1 = "Zarobiłem to i zapłaciłem. Oczywiście nie w ciągu miesiąca. Prawdę mówiąc, byłem wtedy tylko szczurem lądowym. A jednak Chevalier nie pozwolił Michelowi odejść.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "A potem zaciągnąłeś się do pracy dla Poincego? Szczerze, nie rozumiem cię.";
			link.l1 = "Zaciągnąłem się, aby służyć Francji i tym, których kocham, nie kłaniam się nikomu poza królem.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Przepraszam, Monsieur de Maure. Oczywiście, służysz Francji i Królowi! Poincy odpowie za wszystko! Włącznie z całym bólem, jaki ci wyrządził.";
			link.l1 = "Bardzo dobrze, Baronie, znajdę milion, który mogę poświęcić. Wsiadaj na pokład... Rozwiążę ten problem.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "Chciałeś się ze mną spotkać, wiceadmirał?";
			link.l1 = "Tak. Spotkałem się ze Stuyvesantem. Oto jego księga.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Nie wierzę! Hmm, zobaczmy... (czyta)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "To już koniec! Nasz drogi Kawaler jest zgubiony. Gdy tylko cały ten rachunek zostanie przedstawiony Ministrowi Finansów... Nie mogę sobie nawet wyobrazić, co się z nim stanie. Nie będziemy nawet musieli szukać Hiszpana z Kartageny. Monsieur de Maure, czy naprawdę zapłaciłeś milion za tę książkę?";
			link.l1 = "Tak zrobiłem. Gdybym spróbował czegoś innego, Francja mogłaby stracić swoje kolonie na Karaibach z powodu wojny domowej, którą mógłbym wygrać, ale jakim admirałem bym był, gdybym walczył z własnym ludem.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "Jesteś naprawdę godzien swego imienia. Przysięgam ci, wiceadmirał, że odzyskasz to. Jestem pewien, że znajdziemy pokaźną sumę pieniędzy w skrzyniach Poincego i jego lichwiarzach. Proszę tylko, byś poczekał sześć miesięcy, aż wrócę z Europy z komisją.";
			link.l1 = "I nie zapomnij przyprowadzić regiment dobrze wyszkolonych i uzbrojonych żołnierzy. I statek taki jak 'Eclatant'. Wierzę również, że kapitan 'Eclatant' stanie po naszej stronie, gdy nadejdzie czas.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "Nie wątp w to, on jest też człowiekiem honoru. Zdałem sobie sprawę, że wartości moralne odgrywają dużą rolę w podejmowaniu własnych decyzji. Świetnie się spisałeś, że mi zaufałeś i zdemaskowałeś tego państwowego przestępcę. Teraz zabierz mnie do Capsterville, gdzie zdam raport Poincy'emu o sukcesie twojej misji - udało ci się mnie przekonać i porzucę pomysł stworzenia kompanii handlowej. Być może Poincy nawet cię za to nagrodzi - weź nagrodę z czystym sumieniem i nie martw się o nic, zasłużyłeś na nią jak mało kto. Nie zostaniesz w to wplątany, a twoje imię nie zostanie splamione występkami twojego przełożonego, w rzeczywistości powiem o tobie same najlepsze rzeczy, gdy spotkam się z królem. Baron Forget to człowiek honoru i człowiek danego słowa.";
			link.l1 = "Cieszę się, baronie. Wyruszajmy!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "Więc, Wiceadmirał, w końcu dotarliśmy. Twoja misja dobiegła końca, teraz to moja sprawa. Idź zajmij się swoimi sprawami, broń interesów Francji, jak to robiłeś wcześniej. Za około sześć miesięcy ta nikczemna historia dobiegnie końca. Wyślę kuriera, aby cię odnalazł, gdy będziesz potrzebny. Żegnaj, Monsieur de Maure, miałem wielkie szczęście spotkać tutaj honorowego człowieka! Minister i Król usłyszą o tobie, to obiecuję. I usłyszą same najlepsze rzeczy.";
			link.l1 = "Dziękuję, Baronie. Szerokiej drogi!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Cieszę się, że cię widzę, wiceadmirał. Jestem tu znowu, jak obiecałem. A ze mną - pierwszy asystent Ministra Finansów, Baron Olivier Bourdin.";
			link.l1 = "Gdzie jest Chevalier de Poincy?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Gdzie powinien być, w więzieniu. Został aresztowany i zostanie przewieziony do Francji na śledztwo i proces. Z uwagi na jego pozycję, z pewnością uniknie egzekucji, ale nie uniknie ogromnej grzywny, degradacji i, prawdopodobnie, uwięzienia.";
			link.l1 = " Czy aresztowanie przebiegło spokojnie?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Nie do końca. Chevalier miał tutaj, w rezydencji, całą straż lojalnych żołnierzy. Ale byliśmy gotowi na taką eskalację z wyprzedzeniem.";
			link.l1 = "Cóż, w takim razie gratuluję ci, baronie! Być może teraz zajmiesz się francuską Kompanią Handlową?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "Ja? Tak. Jego łaska, monsieur Bourdin - wróci do Francji razem z Chevalier de Poincy. A ty, wiceadmirał, także powinieneś spodziewać się pewnych zmian. Teraz masz nowe stanowisko. Jego łaska powie ci więcej.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Monsieur de Maure! Zaczekaj chwilę!";
			link.l1 = "Tak, baronie. Słucham.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "Jeśli chodzi o milion, który zapłaciłeś Stuyvesantowi... Nie powiedziałem o tym ministerstwu, aby... uniknąć pytań, jak to się stało, że francuski oficer wszedł w posiadanie takiej sumy pieniędzy. Mogło to być dla ciebie szkodliwe, ponieważ prawdopodobnie poprosiliby cię o powiększenie skarbca króla z własnych środków.";
			link.l1 = "Rozumiem, dziękuję.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "Wszystkie pieniądze znalezione w posiadaniu Poincy'ego w Casterville zostały skonfiskowane przez barona Bourdina. Ale, jak się okazuje, Poincy miał również skrytkę, którą angielscy lichwiarze ukrywali dla niego. Porozmawiam z nim o zwrocie inwestycji, a potem znajdę sposób, aby ci to wynagrodzić.";
			link.l1 = "Obawiam się, że nie będzie ci łatwo odebrać coś z rąk angielskich lichwiarzy.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "Zgadzam się. Ale będziemy nad tym pracować i będę cię informować o wynikach.";
			link.l1 = "Jak sobie życzysz.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Wiceadmirał, nie wyglądasz za dobrze, czy to tylko moje wrażenie? Dopiero co otrzymałeś najwyższą pozycję w koloniach!";
			link.l1 = "Nie, wcale nie... To tylko wszystko stało się tak niespodziewanie, i jestem trochę zagubiony.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "Nie martw się. Przyzwyczaisz się do swojej nowej pozycji. A poza tym, całkiem dobrze radziłeś sobie jako gubernator Saint-Martin przez pół roku, więc to nie będzie dla ciebie nic nowego.";
			link.l1 = "Och, jestem pewny, że się przyzwyczaję. Byłem w gorszych sytuacjach podczas mojego pobytu tutaj na Karaibach. Myślę, że i z tą sobie poradzę.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "Cóż, dobrze. Dodatkowo mam dla ciebie jeszcze jedną niespodziankę. Jestem pewien, że ci się spodoba. Ale najpierw proszę cię, abyś wrócił do rezydencji. Myślę, że ktoś tam na nas czeka.";
			link.l1 = "Zaintrygowałeś mnie, Monsieur Forget. Cóż, wracajmy.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "Nic nie szkodzi, Markizie. Prawdziwy kapitan zawsze najpierw powinien troszczyć się o swój statek, prawda? Charles, czy pamiętasz Markiza Huberta Dassiera, kapitana okrętu liniowego 'Eclatant'?";
			link.l1 = "Oczywiście, że pamiętam! Gdyby nie on, nie byłbym dziś żywy. Najsilniejsza przyjaźń między oficerami marynarki pochodzi z bitew, które są toczone ramię w ramię. A Monsieur Dassier okazał się niezwykle doświadczonym kapitanem.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "Wiceadmirał, mam zaszczyt poinformować Was o następującym. Oprócz Waszej nominacji na Pełniącego Obowiązki Gubernatora Generalnego francuskich kolonii na archipelagu, poruszyłem również kwestię Waszego okrętu flagowego.";
			link.l1 = "Okręt flagowy?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "Dokładnie. O ile mi wiadomo, kiedy wstąpiłeś na służbę Francji, otrzymałeś do dyspozycji lekki fregatę 'Gryffondor'. To wspaniały statek, bez wątpienia, ale wciąż jest tylko dla oficera, a nie dla wiceadmirała, a teraz gubernatora generalnego. Jesteś tutaj twarzą Francji. I twój okręt flagowy powinien być odpowiedni. Dlatego postanowiliśmy, że statek, który przeszedł swoje pierwsze bitwy tutaj na Karaibach, zostanie dodany do twojej eskadry...";
			link.l1 = "Monsieur Forget, czy próbujesz powiedzieć...";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "Od teraz, duma francuskiej marynarki, 66-działowy okręt wojenny 'Eclatant', jest do twojej dyspozycji! Ta decyzja jest zatwierdzona przez króla!";
			link.l1 = "Ale Baron, nie mogę po prostu wziąć...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "Możesz, Charles. To nie podlega dyskusji. We Francji 'Eclatant' został nieco zmodernizowany specjalnie dla ciebie, ponieważ, jak się okazało, nie ma tak dużych bitew morskich na Karaibach jak w Europie, a zatem wymagania wobec poszczególnych statków są wyższe. Tutaj wszystko zależy od charakterystyki statku i doświadczenia jego kapitana. 'Eclatant' miał wzmocniony kadłub, zwiększony tonaż i załogę, nieco przeprojektowano takielunek, aby umożliwić ostrzejsze kursy, a także całkowicie wymieniono wszystkie działa na kaliber czterdziestu dwóch funtów, są to najsilniejsze działa, jakie posiadamy.";
			link.l1 = "Tak, teraz ten statek jest po prostu panem mórz... Ale Monsieur Forget, bo kapitanem tego statku jest markiz Hubert Dassier. Nie mogę mu tego odebrać...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "To tylko, że jeszcze ci nie powiedziałem, że sam markiz wyraził silne pragnienie służby pod twoim dowództwem... Monsieur Dassier?";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "Tak, Monsieur Dassier, wierzę, że nie będziemy cię dłużej zatrzymywać.";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "Między nami, Charles, zdecydowanie radziłbym Ci zostawić markiza na swojej służbie. Zapewniam Cię, że nie znajdziesz tak doświadczonego kapitana.";
			link.l1 = "Wierz mi, baronie, miałem zaszczyt widzieć to osobiście podczas walk przeciwko Hiszpanii i Holandii. Monsieur Dassier jest rzeczywiście doskonałym oficerem bojowym, a także moim przyjacielem.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "Cóż, teraz pozwól mi odejść, Wasza Łaskawość, Gubernatorze-Generalny! Sprawy nie mogą czekać: praca nad stworzeniem kompanii handlowej jest w pierwszym dniu jej powstania. Do zobaczenia wkrótce!";
			link.l1 = "Powodzenia, Monsieur Forget. I powodzenia z twoimi przedsięwzięciami handlowymi!";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "Pozwól mi wyrazić najszczersze uznanie dla ciebie, wiceadmirał! Uratowałeś mi życie, uwalniając mnie od tych przeklętych piratów. Dziękuję ci, jak również Philippe de Poincy. Muszę przyznać, że całkowicie myliłem się w mojej ocenie jego, i proszę cię o wybaczenie za to. Ty i Chevalier mieliście rację: Francuska Kompania Handlowa będzie miała tutaj wiele kłopotów, i wygląda na to, że będziemy tutaj tylko tracić pieniądze\nTylko doświadczeni ludzie, tacy jak Poincy, i tak odważni żołnierze jak ty, mogą stawić czoła tym wilkom, które żyją na każdej wyspie tutaj. Muszę udać się do pałacu, a potem wyjadę do Europy tak szybko, jak to możliwe, i zapomnę o tym koszmarze.";
			link.l1 = "Cieszę się, że wszystko dobrze się skończyło, baronie. Do widzenia!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", monsieur. Co sprowadza cię na pokład 'Eclatant'?";
			link.l1 = TimeGreeting()+", monsieur. Pozwólcie, że się przedstawię - Kapitan Charles de Maure, przybywam od Gubernatora Generalnego francuskich kolonii w Archipelagu, Chevaliera de Poincy. Otrzymałem rozkaz włączenia waszego statku do mojej eskadry i przyjęcia pod moje dowództwo. Oto list...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "To jakaś pomyłka, monsieur. Stoicie na okręcie liniowym marynarki francuskiej, a ja słucham tylko rozkazów wydawanych przez tych, którzy służą Królewskiej Marynarce. A wy nie wydajecie się mieć żadnych oznak ani przynależności do tej floty. Być może mylicie nasz statek z innym.";
			link.l1 = "Ale...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "Hę, nawet cię nie poznałem w tym mundurze, Kapitanie. Cóż, pokaż mi swój list, chcę przejrzeć jego zawartość.";
				link.l1 = "Proszę.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "Omówiliśmy już wszystko, monseigneur...";
				link.l1 = "Hmm...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Cóż, zobaczmy... (czytając) Interesujące. Więc ja i mój statek mamy być pod twoim dowództwem, kapitanie de Maure?";
			link.l1 = "To jest rozkaz Gubernatora Generalnego.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Tak-tak, rozkazy nie podlegają kwestionowaniu. Bardzo dobrze. Pozwól, że się przedstawię: Jestem Markiz Hubert Dassier, Kapitan 66-działowego okrętu liniowego francuskiej marynarki wojennej o nazwie 'Eclatant', wraz z tym dobrze wyszkolonym załogą, i przysięgam na mój honor, jest to jeden z najlepszych statków, jakie Francja kiedykolwiek miała.";
			link.l1 = "Cieszę się, że to słyszę, gdyż zadanie, które powierzył nam gubernator generalny, będzie wymagało dobrej znajomości nawigacji i artylerii.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "Czy opowiesz mi o szczegółach tej nadchodzącej operacji?";
			link.l1 = "Oczywiście. Przeniesiemy się na hiszpańską wyspę Trynidad, położoną około tygodnia podróży na południowy wschód stąd. Gwałtownie zaatakujemy fort strzegący kolonii San Jose i zrównamy go z ziemią. Następnie porozmawiamy z Hiszpanami o naszym odszkodowaniu za niedawny atak na francuską osadę Saint-Pierre.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "Rozumiem. Kiedy wyruszamy?";
			link.l1 = "Tak szybko, jak to możliwe. Musimy ukończyć to zadanie w ciągu miesiąca, więc mamy więcej niż wystarczająco czasu.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "W porządku, Kapitanie de Maure. Wypłyniemy na Twój rozkaz.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "Czy masz jakieś rozkazy, lub może pytania, Kapitanie de Maure?";
			link.l1 = "Jeszcze nie...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "Ale, kapitanie de Maure, najpierw musisz zmniejszyć swoją eskadrę - mój statek nie może do ciebie dołączyć, bo eskadra będzie zbyt duża.";
			link.l1 = "Hm. Masz rację. Zostawię jeden statek tutaj w porcie.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Jeszcze nie zmniejszyłeś swojej eskadry, monsieur?";
				link.l1 = "Tak-tak, pamiętam, pracuję nad tym.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "Zatem 'Eclatant' jest gotowy dołączenia do twej eskadry, monsieur.";
				link.l1 = "W takim razie pójdę na mój statek, a ty powinieneś przygotować się do wypłynięcia na morze.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Witaj, Komodorze. Czy mamy przed sobą kolejną bitwę?";
			link.l1 = "Rzeczywiście, tak jest. Ponownie połączymy siły. Zamierzamy szturmować Philipsburg. Gubernator Generalny powierzył nam zadanie oczyszczenia Saint-Martin z Holendrów.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "Mamy, kapitanie, ale nieco później. Powiem ci kiedy. 'Eclatant' musi być gotowy do wypłynięcia na morze w każdej chwili.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Wszystko jest jasne. To będzie trudna misja, monseigneur. Z tego, co słyszałem, fort w Philipsburgu ma dużo dział.";
			link.l1 = "Jestem tego pewien, przyjacielu, ale damy sobie radę. Przygotuj się na wejście na morze, wkrótce wyruszamy.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "Cieszę się, że widzę cię na pokładzie 'Eclatant', wiceadmirale! Jakie są twoje rozkazy?";
			link.l1 = "Przygotuj 'Eclatant' do wypłynięcia. Najpierw popłyniemy na wybrzeże Jamajki, a potem, razem z eskadrą pułkownika D'Oyleya, zaatakujemy Curacao.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "Rozkazy będą, kapitanie, ale później. Powiem ci, kiedy. 'Eclatant' musi być gotowy do wypłynięcia na morze w każdej chwili.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = " 'Eclatant' i jego załoga są gotowi, wiceadmirał!";
			link.l1 = "Doskonale. Zatem wyruszamy natychmiast.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "Przepraszam panowie, nie mogłem dołączyć do was wcześniej, byłem zajęty wydawaniem rozkazów na statku. Już myślałem, że się spóźniłem, bo nie znalazłem was w rezydencji, i dlatego zamierzałem wrócić na statek...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "Był to dla mnie zaszczyt walczyć u boku Waszmości, monsieur de Maure! Muszę rzec, że rzadko spotykam tak kompetentnych i zręcznych oficerów jak Waszmość. Jestem pewien, że sam nie poradziłbym sobie tak szybko z fortem tej hiszpańskiej kolonii na Trynidadzie!";
			link.l1 = "Nie doceniasz się, Monsieur Dassier. Poradziliśmy sobie z tym razem.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "Zgadza się. Chociaż jestem markizem, nadal jestem żeglarzem. Dla mnie, archipelag Karaibów jest nowy, niezbadany i pełen nowych przygód. Ostatnim razem byłem tutaj tylko kilka miesięcy, ale gdy wróciłem do Europy, zacząłem tęsknić za tym miejscem. Chciałbym służyć tutaj naszemu Ojczyźnie. A ty jesteś bardzo utalentowanym i doświadczonym kapitanem, udało ci się zdobyć mój szczery szacunek i moją przyjaźń. Byłbym zaszczycony mogąc służyć pod twoim dowództwem, wiceadmirał!";
			link.l1 = "Otóż nie mogę, a co więcej! - Nie chcę Ci odmówić, Monsieur Dassier!";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "Rozumiem też, że Eclatant jest teraz twoim okrętem flagowym, więc doskonale zrozumiem, jeśli zdecydujesz się osobiście objąć nad nim dowodzenie. W takim przypadku możesz pozostawić mnie jako swojego oficera, przydzielić mi inny statek lub po prostu zwolnić mnie z obowiązków - Monsieur Forget łaskawie obiecał mi, że wtedy znajdzie mi godną pozycję we flocie Francuskiej Kompanii Zachodnioindyjskiej.";
			link.l1 = "Mogę cię zapewnić, mój przyjacielu, że do tego nie dojdzie. Jesteś jednym z najlepszych kapitanów, jakich kiedykolwiek spotkałem, a z tobą u boku będziemy niepowstrzymani.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "Dziękuję za tak pochlebną ocenę moich umiejętności. I jeszcze jedno, wiceadmirał. Nie znam obecnej liczebności twojej eskadry, więc na wszelki wypadek będę czekał na ciebie na mostku kapitańskim Eclatant w doku Capsterville. Jak tylko zdecydujesz się przejąć okręt pod swoją komendę - daj mi znać.";
			link.l1 = "Bardzo dobrze, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "W takim razie proszę o pozwolenie na oddalenie się. Wiceadmirał, Baronie...";
			link.l1 = "Do zobaczenia wkrótce, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "Wiceadmirał, witaj na pokładzie. Czy chciałbyś wziąć Eclatant pod swoje dowództwo?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "Jeszcze nie, Markizie. Czekaj na rozkazy.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "Tak, Markizie, proszę cię o dołączenie do mojej eskadry. Ten piękny statek będzie symbolem wielkości i potęgi Francji na Karaibach!";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "Nie mogę się bardziej zgodzić, Wasza Ekscelencjo!";
			link.l1 = "... Teraz zobaczmy, do czego jesteśmy naprawdę zdolni!";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "O, cóż za znajomość! Czyżby to sam kapitan Charles de Maure?! Słyszałem, że teraz masz stanowisko w francuskiej marynarce. Co za niespodzianka, biorąc pod uwagę dla kogo, powiedzmy, 'pracowałeś' wcześniej...";
				link.l1 = "Pozdrowienia, sir. Czy mówisz o sprawie z Isla Tesoro? Och, ale to nie ja napisałem angielskie prawa, według których wyspa została przekazana spadkobiercy odkrywcy, który ją znalazł, zgodnie z jego wolą. Więc nie jestem za to winny, tylko pomogłem pannie Sharp dostać to, co jej się prawnie należało.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", Kapitanie. Przypuszczam, że przedstawiciel francuskiej marynarki przybył na Antiguę z ważnym celem?";
				link.l1 = "Rzeczywiście, sir. Zostałem wysłany tutaj przez Generała Gubernatora francuskich kolonii, Philippe'a de Poincy. Saint-Christopher został oblężony przez eskadry marynarki hiszpańskiej i holenderskiej. Chevalier prosi o pomoc od ciebie i sir Jonathana Foxa również. Oto jego list dla ciebie, pułkowniku.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "Zastanawiam się, Kapitanie, ile pieniędzy zarobiłeś na tym? Przypuszczam, że całkiem dużo, skoro udało ci się zapłacić za usługi łotra Loxleya, które wcale nie są tanie. Jestem pewien, że baronowie piratów regularnie płacą ci odliczenia za utrzymanie wyspy w ich posiadaniu. Oboje doskonale wiemy, że Helen Sharp to tylko maska.";
			link.l1 = "Pułkowniku, obaj wiemy, że baronowie piratów działają głównie w interesie Anglii, nieoficjalnie, oczywiście... Bez nich byłoby dość trudno oprzeć się hegemonii Hiszpanów w regionie, nie zgadzasz się? Zatem, z punktu widzenia polityków, fakt, że Bracia Wybrzeża zatrzymali wyspę dla siebie, był być może nawet bardziej opłacalny, niż gdyby Isla Tesoro stała się angielską bazą morską...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "To jest być może prawdą, kapitanie, ale... niech tak będzie. Przybyłeś na Antiguę z jakimś ważnym celem, jak mniemam? Może ma to związek z faktem, że relacje dwóch dawnych sojuszników - Francji i Holandii, znacznie się pogorszyły?";
			link.l1 = "Zgadza się. Zostałem wysłany przez gubernatora generalnego francuskich kolonii, Philippe'a de Poincy. Saint-Christopher jest oblegane przez hiszpańską i holenderską flotę. Chevalier prosi o twoją pomoc. Oto jego list do was, pułkowniku.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Niech no zobaczę... (czytanie)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... bardzo intrygujące! Kapitanie, twój dowódca wie, jak wzbudzić moje zainteresowanie, nie jest to takie niezwykłe, że ludzie nazywają go przebiegłym lisem. Powinniśmy byli to zrobić już dawno, zamiast próbować zaprzyjaźnić się z Holendrami. Jak wiemy doskonale, co oznacza Holenderska Kompania i ich Dyrektor. Cóż, myślę, że w tej sytuacji naprawdę nie powinniśmy odmawiać pomocy oblężonemu Casterville, a mamy więcej niż wystarczająco wojsk, aby to umożliwić.\nJakie są liczby i rodzaje statków w ich eskadrach, Kapitanie?";
			link.l1 = "Policzyłem sześć statków: jeden osiemdziesięciodziałowy okręt liniowy trzeciej rangi i pięć statków czwartej. Mogą mieć również fregaty i galeony.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Hmm... Możemy wystawić naszą eskadrę, składającą się ze statku pierwszej rangi o stu działach, dwóch statków czwartej rangi i ciężkiej fregaty, przeciwko ich.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Sir, mamy również 66-działowy okręt wojenny, 'Eclatant', płynący na pomoc obronie Saint-Christopher z wybrzeża Gwadelupy.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "Okręt pierwszej rangi będzie wielką pomocą w nadchodzącej bitwie.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Doskonale. W takim razie jesteśmy daleko poza zasięgiem ognia naszych wrogów. Zwycięstwo będzie nasze.";
			link.l1 = "I nie zapominajmy o moim własnym statku, panie. Nie zamierzam przegapić takiej bitwy, nawet o tym nie myśl.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "To prawda. Z pomocą fortu Casterville zwycięstwo będzie nasze.";
			link.l1 = "I nie zapominajmy o moim własnym okręcie, panie. Nie przegapię takiej bitwy, nawet o tym nie myśl.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "Oczywiście, monsieur de Maure. Cokolwiek by się nie działo, opowieści o twoich żeglarskich talentach można usłyszeć w całym archipelagu. Twój okręt flagowy poprowadzi eskadrę.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Zatrzymam resztę okrętów z mojego szwadronu, potem wrócę do ciebie i rzucimy się na pomoc oblężonym.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Przygotuję mój statek wkrótce, i popędzimy na pomoc oblężonym.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "Więc, jesteś gotowy do wypłynięcia?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Poczekaj tylko chwilę, panie.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Tak, panie.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "Zatem zacznijmy, a niech Bóg nam dopomoże!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "Czy ma pan jeszcze jakieś pytania, sir?";
			link.l1 = "Nie, pułkowniku...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Zdobądź list dla Stuyvesant, panie. Jeśli nie wiesz, kim jestem, pozwól, że się przedstawię: pułkownik Edward Doily, gubernator Port-Royal i dowódca tej ekspedycji!\nSzczerze mówiąc, mam ogromną chęć zniszczyć kryjówkę bandytów znaną jako Willemstad. Najpodlejsza, dwulicowa i nikczemna organizacja na Karaibach, znana jako Holenderska Kompania Zachodnioindyjska, która uważa, że cały handel na Archipelagu to wyłącznie ich prawo, i która zatrudnia takich jak Jacob van Berg i innych piratów, by przejmować i zatapiać statki angielskich kupców...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "Jestem tu, by położyć kres tym oburzającym czynom i, na szczęście dla ciebie, proponuję dyplomatyczne wyjście. Na razie... Ale jeśli dyrektor tej ohydnej organizacji nie przybędzie tutaj na rozmowy, zrujnuję jego interes. Po szturmie miasta zostawię tylko zgliszcza, a proch, który znajdziemy, umieścimy w piwnicy waszego fortu i wysadzimy go w powietrze. Ten sam los czeka wasze plantacje, a sam Stuyvesant zawiśnie na reje mojego okrętu flagowego...";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "Będziesz potrzebował więcej niż rok, aby odbudować swoją kolonię, a potem nie będziesz miał czasu na swoje intrygi i spiski. Przekaż swojemu 'Mynheerowi Dyrektorowi' wszystko, co właśnie powiedziałem, i nie myśl, że to żarty i puste obietnice. Moja cierpliwość się wyczerpała, więc musisz mnie doskonale zrozumieć. Rozumiesz, oficerze?!";
			link.l1 = "Wszystko jest doskonale jasne, panie pułkowniku.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Świetnie. Zatem odejdź. Daję ci dokładnie jeden dzień na przemyślenie tego. Jeśli po dwudziestu czterech godzinach Peter Stuyvesant nie będzie tu stał tak jak ty teraz, niech obwinia za to siebie.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = " Myślę, że ten przeklęty pies Stuyvesant przyjdzie tutaj. A jeśli nie - może winić tylko siebie!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "Zrobiłeś dobrą robotę z fortecą, monsieur de Maure. Teraz podejdziemy do bram miasta lądem. Ja wezmę działa stąd, droga tutaj jest krótsza i łatwiejsza, a ty wysadzisz kompanię swoich marynarzy na Przylądku Santa-Maria i ruszysz do Willemstad. Jeśli spotkasz wrogów po drodze, wiesz co robić. Nikt nie może zostać za nami.";
			link.l1 = "Oczywiście, pułkowniku. Spotkam się z tobą przy bramach!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Zatem, wygląda na to, że nasza misja zakończyła się całkiem pomyślnie. Gratulacje, Kapitanie! Och, przepraszam - Wiceadmirał! Wracajmy na statki. Powiem moim ludziom, żeby stali na straży - ten głupiec Stuyvesant raczej nie zaryzykuje ataku podczas naszego odwrotu, ale ostrożność nie zaszkodzi.";
			link.l1 = "Jestem pewien, że Holendrzy nie odważą się złamać traktatu, który dopiero co został podpisany.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "To była przyjemność pracować z tobą, monsieur de Maure. Myślę, że spotkamy się ponownie w Port-Royal lub Capsterville.";
			link.l1 = "Bez wątpienia, pułkowniku. Teraz, powiedzmy naszym ludziom, aby się wycofali.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "Wydaje się, że Holendrzy w końcu zrozumieli, że nie mają szans podejść do nas od strony fortu tą wąską ścieżką pod ostrzałem naszej artylerii. A ci, którzy utknęli w mieście, prawdopodobnie nie zaryzykują wycieczki, chyba że są całkowicie szaleni. Teraz zasiejemy trochę paniki: zbombardujmy miasto naszymi działami. Ludzie na moim statku to zobaczą i sprawią, że będzie wyglądało, jakby przygotowywali się do desantu. Po godzinie lub dwóch Stuyvesant narobi w spodnie i będzie gotowy wysłać posłów do zawarcia rozejmu.";
			link.l1 = "Wszystko idzie zgodnie z naszym planem, pułkowniku! Zróbmy to!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "Przybyłem tu, aby rozpocząć negocjacje. Jakie są wasze żądania?";
			link.l1 = "Żądamy spotkania z dyrektorem Kompanii, Peterem Stuyvesantem. Konkretnie, chcemy porozmawiać o tym, że z winy jego kompanii, jak i jego samego, Willemstad jest obecnie zagrożone zniszczeniem.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Bardzo dobrze, powiem o tym panu Stuyvesantowi, i zorganizujemy bezpieczną trasę do miasta dla waszej delegacji...";
			link.l1 = "A co z bezpiecznym wyjściem?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "Nie rozumiem, panie?";
			link.l1 = "Powiedziałem: czy zorganizujesz nam bezpieczne wyjście z miasta? Nie jestem tego pewien. Obawiam się, że mynheer Stuyvesant może po prostu zdecydować się wziąć naszych posłańców do niewoli. Z tego powodu zapraszam mynheera Stuyvesanta, aby pojawił się tutaj na negocjacje.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "Ale...";
			link.l1 = "Oficerze, my tu dyktujemy warunki. Twoja flota jest zniszczona, garnizon odcięty od miasta, a my przenikniemy przez obronę Willemstad jak fregata przez łódkę, jeśli zdecydujemy się szturmować miasto. Teraz otrzymasz list dla pana Stuyvesanta i przekażesz mu go wraz z naszym zaproszeniem...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "Więc Kapitanie, wezwałeś posłów rozejmu, bo chciałeś podyktować swoje żądania?";
			link.l1 = "Masz absolutną rację, señor. Pozwól, że krótko wyjaśnię powód mojego przybycia na Trynidad - to nasza odpowiedź na wasz ostatni atak na Saint-Pierre. Znacznie uszkodziliście miasto, a teraz będziecie zmuszeni to zrekompensować. Cena rekompensaty wynosi trzysta tysięcy peso. A to nie jest tak wiele, biorąc pod uwagę nikczemne czyny, jakie wasi żołnierze popełnili na Martynice.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Przepraszam, señor, ale co ma San Jose do Saint-Pierre? Dlaczego nasza kolonia musi płacić?";
			link.l1 = "Ponieważ napastnicy byli Hiszpanami, a nie Holendrami czy Anglikami. Następnie wystawicie rachunek na Providence dla Don de Mendosa, wraz z moimi najszczerszymi pozdrowieniami. Jak rozumiecie, w przypadku odmowy zapłaty odszkodowania, rozkażę moim ludziom zejść na ląd, a wtedy San Jose straci znacznie więcej. Jestem pewien, że wasz gubernator kolonii podejmie właściwą decyzję. Macie jeden dzień na odpowiedź. Życzę wam wszystkiego najlepszego, señores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "Więc, jak rozumiem, gubernator podjął właściwą decyzję?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Zgarnij swoje trzysta tysięcy i wynoś się z naszej kolonii.";
			link.l1 = "Doskonale, señores. Zapewniam was - to było najlepsze rozwiązanie. Mam nadzieję, że to zniechęci Don de Mendosę i innych do atakowania naszych kolonii. Nie zapomnijcie wysłać wiadomości do Providence i do niego osobiście. Życzę wam wszystkiego dobrego, panowie.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Kapitanie Charles de Maure, pozwól mi złożyć raport: Kawaler Philippe de Poincy chciał cię powiadomić, że baron Noel Forget jest gotowy do wyjazdu na Saint-Martin i będzie czekał na ciebie na molo.";
			link.l1 = "Wyśmienicie! Dziękuję, monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "Kapitanie Charles de Maure! Generalny Gubernator wzywa cię natychmiast. Potężna eskadra wroga pojawiła się u wybrzeży Saint-Christopher!";
			link.l1 = "W takim razie nie traćmy czasu!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "Kim jesteś? Co tu robisz?";
			link.l1 = "Ech...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "Nie wolno tu wchodzić obcym! Kim jesteście, szpiedzy? Zaprowadzę was do biura komendanta, oni się wami zajmą.";
			link.l1 = "Ale nie możemy iść do biura komendanta...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "Jeśli sam nie pójdziesz - będziemy musieli cię zaciągnąć siłą! Oddaj broń!";
			link.l1 = "Nie ma umowy...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "Więc, wszystko jasne?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Tak, monsieur. List ma być wręczony osobiście mynheerowi Peterowi Stuyvesantowi lub Mathiasowi Beckowi.";
			link.l1 = "Jestem pewien, że nie będziesz miał problemów ze znalezieniem statku z Willemstad do Cartagena. Daliśmy ci wszystkie niezbędne fundusze na opłacenie podróży i zakwaterowania. A w razie potrzeby - potwierdzisz swoje raporty przed francuską komisją za pół roku?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Panie, jestem wierny mojemu słowu.";
			link.l1 = "Bardzo dobrze. Zatem życzę ci szczęścia. Ta ścieżka prowadzi do Willemstad, idź nią. To niedaleko stąd.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Wiceadmirał Charles de Maure, prawda?";
			link.l1 = "Dokładnie. Z kim mam zaszczyt rozmawiać?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Mam dla ciebie wiadomość od barona Noela Forgeta. Kazał ci przybyć do pałacu gubernatora w Casterville tak szybko, jak to możliwe.";
			link.l1 = "Oh! Wspaniała nowina! Dziękuję, wyruszam natychmiast!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Witam, wiceadmirał. Baron Forget opowiadał mi o tobie historie. Wiele historii. Składam ci najszczersze podziękowania za twoją lojalną i błyskotliwą służbę dla dobra Francji w koloniach, a także za pomoc w odkryciu machinacji oszusta de Poincy. Teraz ja i Minister Finansów zajmiemy się nim osobiście, a ty zajmiesz miejsce swojego byłego dowódcy. Przynajmniej na razie.";
			link.l1 = "Ale...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "Żadnych 'ale', wiceadmirał! Ta decyzja została już podjęta i zatwierdzona przez Króla. Mam tutaj rozkaz podpisany osobiście przez niego, dotyczący mianowania cię de facto Gubernatorem Generalnym francuskich kolonii w Archipelagu. Nie mamy lepszych kandydatów na to stanowisko. Twoje wybitne doświadczenie w wojnie, twoja znajomość regionu i ludzi, którzy są odpowiedzialni za wszystko tutaj, twoje umiejętności i talenty są godne tego wysokiego i szanowanego stanowiska. Jeśli mogę być z tobą szczery, spodziewam się, że po pewnym czasie zostaniesz mianowany na to stanowisko ponownie, bez części 'de facto'.";
			link.l1 = "Ale marzyłem o powrocie do Paryża...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "Francja potrzebuje cię tutaj! Minister finansów gromadzi teraz flotę w Europie, a nasza obecność tutaj, w Archipelagu, również nie pozostanie niezauważona. Twoim głównym zadaniem będzie wzmocnienie i umocnienie kolonii oraz zwiększenie siły militarnej naszej floty, podczas gdy Baron Forget i Francuska Kompania Handlowa Zachodnich Indii skupią się na handlu i rozwoju krajowym! A kto inny, jeśli nie ty, może pomóc przygotować francuską marynarkę wojenną?\nWięc, zacznij działać, Gubernatorze Generalny! Wiem, że nie lubisz siedzieć w pokoju cały dzień, ale twoje zadanie nawet tego nie wymaga!";
			link.l1 = "Natychmiast, Wasza Łaskawość! Rozkazy nie podlegają dyskusji!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "Cieszę się, że mnie dobrze zrozumiałeś. Poproszę cię również, abyś złożył wizytę Chevalierowi de Poincy: nalegał na spotkanie z tobą. Nie możemy odmówić mu takiej przyjemności przed jego wyjazdem do Paryża, prawda? Znajdziesz go w więzieniu.";
			link.l1 = "Bardzo dobrze, wasza Wysokość...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...zostanie wstrzymane, rozumiesz? Zamówiłem te materiały kilka miesięcy temu!";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "A jak oni zdecydowali, co zabrać na pierwszy statek, a co na drugi?! Ja nie jestem jakąś tam szwaczką z zadupia - mam nawet zlecenie od gubernatora generalnego, jego Ekscelencji kawalera de Poincy!";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "Cóż, co jeszcze mogę teraz zrobić... Poczekam. Ale wiedz, że nie ponoszę odpowiedzialności za niezrealizowane zamówienia!";
			link.l1 = "Witam. Widzę, że masz kłopoty?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "Kłopoty? To łagodne określenie! O, chyba cię rozpoznaję... Jesteś nowym wiceadmirałem, prawda?";
			link.l1 = "Szybko pojmujesz. To prawda, przed tobą stoi drugi człowiek w koloniach francuskich, wiceadmirał floty francuskiej, Charles de Maure.";
			link.l1.go = "Tailor_06";
			link.l2 = "Daruj sobie te formalności, nie jesteśmy na statku. I nie martw się, nie zawołam straży tylko dlatego, że nie rozpoznałeś mnie od razu. Po prostu nazywaj mnie Charles de Maure.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "Wasza Ekscelencjo, proszę wybaczyć mi, że od razu Was nie rozpoznałem! Tak, macie rację, napotkałem nieprzewidziane okoliczności.";
			link.l1 = "I jakież to miałyby być okoliczności? Jak rozumiem, nie przywieźli ci materiałów z Paryża?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "O, bardzo dziękuję. Masz rację, napotkałem nieprzewidziane okoliczności, dlatego od razu nie zorientowałem się, kto stoi przede mną.";
			link.l1 = "A jakie to byłyby okoliczności? Z tego co rozumiem, nie przywieźli ci materiałów z Paryża?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "Tak, to prawda. Zamówiłem je kilka miesięcy temu. Gubernator podpisał wtedy rozkaz o twoim mianowaniu i nalegał, abym przygotował wszystkie niezbędne materiały na nowy mundur admirała, przekonany, że zostanie to zatwierdzone w metropolii.";
			link.l1 = "I materiały nie zostały dostarczone, jak mniemam?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "Wyobraź sobie! Wyjaśniłem, jak to jest ważne, złożyłem zamówienie... Ale oni mają pilniejsze przesyłki do załatwienia! Co mam zrobić? Składać zamówienia z rocznym wyprzedzeniem, licząc, że łaskawie przywiozą mi materiały?";
			link.l1 = "Czego dokładnie ci brakuje? Może można to zdobyć na Karaibach?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "Nawet jeśli to możliwe, nie mam pojęcia gdzie... Nie znajdziesz tu dobrych materiałów. Chociaż... Mogłabym użyć twojej starej oficerskiej kurtki jako podstawy, jeśli pozwolisz. Pewnie nie będzie ci potrzebna, gdy będziesz miał mundur admirała, prawda?";
			link.l1 = "Gdybym miał mundur admirała, to oczywiście, nie potrzebowałbym prostego oficerskiego żakietu. Co jeszcze?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "Muszę znaleźć spinki do mankietów i kołnierzyk do munduru. Zazwyczaj zamawiam je bezpośrednio z paryskich warsztatów. Nawet jeśli są bardzo podstawowe, mogę je przerobić i nadać im bardziej reprezentacyjny wygląd. Choć w takim przypadku będę potrzebował ich więcej...";
			link.l1 = "Skoro nie ma paryskich warsztatów na Karaibach, znajdę ci całą partię lokalnych ubrań z odpinanymi kołnierzykami i mankietami. Co jeszcze?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "Do ostatnich szlifów potrzebuję tkanin najwyższej jakości. Mam prządkę, która potrafi zrobić taką tkaninę nawet z grubego włókna. Ale do tego potrzebuję surowca – najlepiej bawełny. Jeden bel wystarczy z nadmiarem.";
			link.l1 = "To również można zdobyć. Co dalej?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "Mieli dostarczyć trójrożny kapelusz admirała z Paryża, ale mogę go zrobić sam, jeśli będę miał materiał. Chociaż dla ciebie kapelusz miał być z tkaniny, skórzany byłby lepszy na słone wiatry i palące słońce Karaibów. Trwałby dłużej.";
			link.l1 = "I'll get you the leather; don't worry. I won't even have to chase bulls through the jungles of Espanola. Is that all?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "Mieli również dostarczyć jedwab najwyższej jakości z Lyonu. Jest lekki, przewiewny, łatwo wchłania wilgoć i jeszcze szybciej schnie. A co najważniejsze, nie rozciąga się i zachowuje swój kształt.";
			link.l1 = "Tak, rozumiem, o jakim jedwabiu mówisz. Jednak może być trudniej zdobyć go w koloniach.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "To wszystko, jeśli chodzi o materiały. Słyszałem również, że otrzymałeś najwyższe odznaczenie Francji... Order Świętego Ludwika nie powinien być noszony jak jakaś błyskotka na pasku. Ma swoje miejsce. Przynieś mi go, a przyszyję go, jak należy.";
			link.l1 = "Dobrze, przyniosę to też. Tylko tego nie zgub!";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "Na pewno nie! Będę tego strzegł za cenę życia!";
			link.l1 = "Dobrze więc. Jeśli to wszystko, pójdę po materiały.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "Jest jeszcze jedna rzecz... Moje narzędzia krawieckie stały się bezużyteczne. Zamówiłem nowe z Paryża, ale niestety... Gdybyś mógł znaleźć wszystkie potrzebne materiały i pożyczyć mi narzędzia, jeśli je masz - tylko pożyczyć, nowe zdobędę później! - natychmiast zacznę szyć.";
			link.l1 = "Cóż, co mogę zrobić? Przyniosę ci wszystko, czego potrzebujesz. Gdzie mogę cię znaleźć? Nie będziesz na mnie czekał w porcie, prawda?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "Mój warsztat znajduje się w budynku tuż przy nabrzeżu - kiedy zejdziecie na ląd, będzie po waszej prawej stronie.";
			link.l1 = "Zgoda. Zdobędę dla ciebie materiały.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "Witaj, wiceadmirał! Czy przyniosłeś wszystko, co potrzebne do nowego munduru?";
			link.l1 = "Jeszcze nie, nie miałem czasu. Poczekaj, zdobędę wszystko.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "Tak, przyniosłem wszystko. Oto moja stara kurtka, Order i narzędzia krawieckie. Resztę materiałów moi żeglarze wkrótce przyniosą do twojego warsztatu.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "Wspaniale! Szczerze mówiąc, nie sądziłem, że uda ci się to wszystko zdobyć. Jestem przyzwyczajony do pracy tylko z tkaninami z Paryża, ale wygląda na to, że można zrobić całkiem przyzwoite garnitury z lokalnych materiałów.";
			link.l1 = "Jak długo potrwa, zanim mój nowy mundur będzie gotowy?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "Zwykle zajmuje to nie mniej niż tydzień, ale biorąc pod uwagę, że klientami są dwaj najwyżsi urzędnicy Francji w koloniach... Przyjdź do mnie za trzy dni, a obiecuję, że wszystko będzie gotowe najlepiej, jak to możliwe! Nie musimy brać miar, zrobię wszystko na podstawie twojej starej kurtki.";
			link.l1 = "Świetnie! Wrócę za trzy dni.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "Viceadmirał! To przyjemność cię zobaczyć!";
				link.l1 = "Cóż, przyszedłem po nowy mundur, tak jak się umówiliśmy.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "Witaj, wiceadmirał! Przepraszam, ale twój mundur jeszcze nie jest gotowy.";
				link.l1 = "Cóż, czy mogę przynajmniej zerknąć, co się dzieje?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "Nie, nie! W tej chwili wygląda to zupełnie nieprezentacyjnie, a nie chcę zawieść twoich oczekiwań. Proszę o cierpliwość.";
			link.l1 = "Okej, poczekam.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "Tak, oczywiście! Muszę ci powiedzieć, że wyszło nie gorzej niż te robione w Paryżu! Miałeś rację, nawet w koloniach można znaleźć odpowiedni materiał, jeśli wiesz, gdzie szukać. Chwileczkę. Oto jest! Proszę, obejrzyj i przymierz.";
			link.l1 = "Dziękuję. Doskonała jakość! I dobrze pasuje.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "Nie tylko dobrze! Możesz z dumą nosić to jako wiceadmirał Francji w koloniach! A twój Order, jak obiecałem, jest teraz na swoim właściwym miejscu, a nie dynda na twoim pasie.";
			link.l1 = "Dobra robota! Gdy spotkasz Kawalera de Poincy, możesz mu powiedzieć, że jestem zadowolony.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "Na pewno mu powiem! Niech uniform służy ci wiernie! Powodzenia!";
			link.l1 = "Dziękuję! Do widzenia.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("You have received the Vice-Admiral's uniform!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "Które ostrze chciałbyś ulepszyć?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt") + ": Attack - " + FloatToString(stf(rItem.attack),1) + ", balance - " + FloatToString(stf(rItem.Balance),1) + ", weight - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "Zmieniam zdanie";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
