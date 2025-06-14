// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Oczywisty błąd. Powiedz o tym deweloperom.";
			link.l1 = "O, zrobię to.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Co się tu, do diabła, dzieje, panowie? Słyszałem walkę.";
			link.l1 = "Witaj, oficerze, słyszałem krzyki kobiety i...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Kapitan "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "Możesz teraz odejść, kapitanie. Widzę, co się tu stało, wezwemy cię, jeśli będziemy mieli pytania.";
			link.l1 = "Bardzo dobrze...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Co do diabła się tu dzieje, panowie? Słyszałem walkę.";
			link.l1 = "Dziękuję oficerze, słyszałem jak kobieta krzyczy o pomoc i zobaczyłem, jak ten dżentelmen został zaatakowany przez dwóch łotrów. Próbowałem uratować biedaka, ale niestety, byłem za późno. Dranie go zabili!";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Niech mnie kule biją... On jest Hiszpanem! Co on tu robi? Hm. A kimże jesteś ty, panie?";
			link.l1 = " "+GetFullName(pchar)+". Kapitan "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Kapitanie, na razie możesz odejść. Twoje słowa zgadzają się ze słowami świadka. Wezwiemy cię, jeśli zajdzie taka potrzeba.";
			link.l1 = "Bardzo dobrze...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "Pozwól, że wszystko wyjaśnię, señor! Nazywam się Don Domingo Ortiz Albalate z Santo Domingo. Przybyłem do Port-au-Prince na zaproszenie młodej señority i zatrzymałem się w tej tabernie, czekając na umówione spotkanie. Podczas gdy zajmowałem się swoimi sprawami, zostałem zaatakowany przez tych dwóch maldita ladrones. Jadłbym teraz z aniołami, gdyby nie ten Buen Samaritano, który się zjawił.";
			link.l1 = "Don Domingo Ortiz Albalate? Jesteś Hiszpanem?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "Tak hiszpański jak sam król Felipe, ha! Chciałbym również zaznaczyć, że moje dokumenty są w buen orden. Jestem szlachcicem z Hiszpanii, nie jakimś pirata sucia!";
			link.l1 = "Don Domingo, najszczersze przeprosiny za ten niefortunny incydent! Proszę, chodźcie z nami na kilka pytań i butelkę wina do garnizonu. My się wszystkim zajmiemy. A co do was...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = "Senor Kapitanie! Senor Kapitanie! Przysięgam na Santiago i Błogosławioną Dziewicę, że jesteś szlachetnym człowiekiem, a prawdziwy syn Kastylii zawsze nagradza taką szlachetność! Chciałbym, abyś został nagrodzony później, gdy zakończę swoje sprawy tutaj. Proszę, zaszczyć mnie wizytą w moim skromnym domu w Santo Domingo! Jest blisko bram miasta. Wystawię dla ciebie ucztę, mój buen caballero Carlos! Zapamiętaj moje imię, to Don Domingo Ortiz Albalate!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Kapitan "+GetFullName(pchar)+"?! O Madre de Dios! Co za katastrofa! To rzeź! Co tu się stało, buen amigo? Kim są ci ludzie?";
			link.l1 = "Cieszę się, że cię widzę, Don Domingo. To są... Przyszedłem cię odwiedzić. Widzisz tamtego faceta? To Ugo, twój sługa i on...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo?! O nie, zostałeś oszukany, kapitanie!";
			link.l1 = "Rozumiem, wydaje się, że często mi się to przytrafia. Trzech łotrów włamało się do twojego domu, zamordowało twojego lojalnego człowieka Ugo - znalazłem jego ciało już na górze - a potem przygotowali zasadzkę na ciebie. Moje przybycie nie było częścią ich planu. Nie przeżyli naszego spotkania.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Santa Maria, ora pro nobis! Walczysz swym mieczem niczym mistrzowie szermierki z Toledo! Dobrze, że jesteś po mojej stronie! Och, mój biedny Ugo! Wychował mnie od dziecka, a teraz... zamordowany przez maldita canallas!";
			link.l1 = "Don Domingo, wygląda na to, że nie jesteś poza niebezpieczeństwem. Twój człowiek Ugo coś wiedział, przeczytaj tę notatkę. Znalazłem ją na stole.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Daj mi to... (czyta) To niemożliwe... o, nie! To niewiarygodne! Tio Luis... Ale...";
			link.l1 = "Masz jakiś trop, kto to zrobił?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Tylko podejrzenia... straszliwe podejrzenia, mi amigo! Jak mógł mój matki brat zrobić coś takiego?";
			link.l1 = "Możesz mnie wtajemniczyć? Przykro mi, Don Domingo, ale z mojego doświadczenia wynika, że krewni często są najgorszymi wrogami, jakich człowiek może mieć...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Si, masz rację, Carlos! Powiem ci wszystko! Już dwukrotnie mnie uratowałeś i wydaje się, że jesteś jedynym człowiekiem, któremu mogę teraz zaufać! Ale opuśćmy to okropne miejsce, robi mi się niedobrze. Muszę powiadomić alcalde o tym bałaganie, oni zajmą się biednym Ugo. Co powiesz na odrobinę wina w lokalnej tabernie, żeby uspokoić nerwy?";
			link.l1 = "Twoje nerwy z pewnością potrzebują tego bardziej niż moje, prowadź senor!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "Wiesz, przyjacielu, pozwól, że opowiem ci... skróconą wersję historii mojej rodziny. Moja matka, Dona Isabella Ortiz, poślubiła mojego ojca, markiza Ricardo Albalate, i przyjęła jego nazwisko zgodnie ze zwyczajem. Jej brat, Luis Ortiz, był dowódcą garnizonu w koloniach, ale po ślubie mojej matki mój ojciec mianował go zarządcą plantacji cukru niedaleko Portobello. To była ogromna i bogata plantacja, bardzo dochodowa. Po tragicznej śmierci moich rodziców na morzu kilka lat temu, jako ich jedyny syn odziedziczyłem wszystko, łącznie z plantacją. Mój wujek zachował swoje stanowisko i byłem zadowolony z czynszu, który mi płacił. Zawsze płacił na czas.";
			link.l1 = "Więc myślisz, że twój wujek...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Tak. Obecnie jest tylko najemcą. To ja jestem właścicielem plantacji, nie on. Ale! Jeśli coś mi się stanie - stanie się to jego własnością.";
			link.l1 = "Wiesz, Domingo, znałem ludzi, którzy z zimną krwią zamordowaliby wszystkich swoich krewnych dla łupu znacznie mniej soczystego niż ten.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "Ty zdecydowanie musisz lepiej dobierać towarzystwo, Carlos. Mój drogi Ugo wspomniał o papierach mego wuja w swoim ostatnim liście... To bezpośrednia wskazówka. Och, nie chcę w to wierzyć! Ale... moja kuzynka, Margarita Ortiz, która mieszka w Hiszpanii, niedawno się zaręczyła. Czy to może być przyczyna, mój dobry kapitanie?";
			link.l1 = "Twój kochający wujek może nagle potrzebować trochę pieniędzy...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Pieniądze?! Ależ oczywiście... ale nie zapomnij o tytule markiza! To uczyniłoby mojego kuzyna odpowiednią partią dla jej przyszłego męża! Jesu Christo! Jaki byłem głupi!";
			link.l1 = "Ten tytuł szlachecki ma większą wartość niż plantacja cukru.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Poczekaj, przyjacielu! Właśnie sobie przypomniałem, że to nie był pierwszy zamach na moje życie! Miałem spotkanie z żebrakiem na ulicy kilka tygodni temu! Pijany kanalia obraził mnie w sposób, którego nie mogłem zignorować. Okazał się przeklętym dobrym szermierzem, dobył stali i nawet udało mu się zranić mnie rapierem, zanim go zabiłem.";
			link.l1 = "Jakim cudem znalazłeś się w tawernie w Port-au-Prince? Wspomniałeś coś o młodej senoricie?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(czerwieniejąc) Panie... Tak kapitanie, na miejscu była młoda i piękna señorita... teraz widzę, że była tylko przynętą na pułapkę. Dranie, dranie są wszędzie, nikomu nie można ufać! Biedny Ugo... teraz nie żyje.";
			link.l1 = "Powinieneś coś z tym zrobić, Domingo. Może uciekniesz do Hiszpanii?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "Do Hiszpanii? I zostawić moją plantację temu łajdakowi? Kapitanie, jestem markizem Domingo Ortiz Albalate!";
			link.l1 = "Ale...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = "Mój przyjacielu Carlosie, czy mogę prosić o twoją pomoc? Po śmierci Ugo nie mam przy sobie nikogo, komu mógłbym zaufać. Już dwukrotnie mnie uratowałeś! Dwukrotnie! Jestem ci ogromnie wdzięczny, jestem na zawsze twoim dłużnikiem, a jednak ośmielam się prosić cię o kolejną przysługę. Przysięgam na Błogosławioną Matkę, że ci się to opłaci!";
			link.l1 = "Dobrze, jesteś dobrym człowiekiem jak na Hiszpana. Co mogę dla ciebie zrobić, Domingo?";
			link.l1.go = "noble_20";
		break;
		
		case "noble_20":
			dialog.text = "Chodźmy na moją plantację w Portabello! Wiem, że mój wujek jest w tej chwili w Cartagenie. Ugo wspomniał o jakichś papierach, więc sprawdźmy księgi i dokumenty Don Luisa Ortiza! Może znajdziemy coś, co pomoże nam wyciągnąć jego plugawą intrygę na światło dzienne. To dość daleko do Portobello, ale zapłacę ci w pełni za podróż!";
			link.l1 = "Byłoby niedorzecznością odrzucić cię w tym momencie, Don Domingo. Jestem zbyt głęboko zaangażowany, by się teraz wycofać.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Dzięki Bogu, wiedziałem, że mi pomożesz, amigo! Weź te dwadzieścia tysięcy pesos jako zapłatę za podróż do Portobello. Kiedy wypływamy? Musimy się spieszyć, zanim mój wuj wróci z Cartagena!";
			link.l1 = "Nie traćmy więc czasu.";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20) link.l1.go = "noble_22";
			else link.l1.go = "noble_22x";
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Oto licencja Holenderskiej Kompanii Zachodnioindyjskiej. Ważna przez dwadzieścia dni, wpiszmy tu twoje nazwisko. Gotowe. To powinno pomóc nam uniknąć kłopotów z Costa Garda.";
			link.l1 = "Znakomicie!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Teraz mogę wejść na pokład twego statku, przyjacielu?";
			link.l1 = "Uważaj się za szanownego gościa. Jak tylko złapiemy odpowiedni wiatr - wypływamy w rejs.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "Więc kapitanie Carlos, oto jesteśmy. Teraz powinniśmy znaleźć dom mojego wuja i sprawdzić, co jest w środku.";
			link.l1 = "Don Domingo, czy powinniśmy spodziewać się problemów z wartą?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "Nie. Chociaż... hm. Istnieje szansa, że Luis ich przeciwko mnie nastawił. Tak czy inaczej, rozwaga zawsze jest lepszą częścią odwagi. Znajdźmy dom, którego potrzebujemy.";
			link.l1 = "Czyż nie wiesz już tego? To twoja plantacja.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Hm.. Szczerze mówiąc, ostatni raz byłem tutaj, gdy miałem zaledwie osiem lat. Jednakże zamierzam to naprawić jak najszybciej!";
			link.l1 = "Rozumiem. Zatem zacznijmy szukać. Dom twojego wujka musi być największy tutaj.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "Co tu masz, mój przyjacielu?";
			link.l1 = "Rzuć okiem, Don Domingo. Wygląda na księgi rachunkowe. To może być interesujące.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(czytając) Hm... Tak. Spójrz na to... Ay caramba! Sto tysięcy pesos! I kolejne sto pięćdziesiąt tysięcy! A tutaj... (przewracając kartki) Wujku Luis!";
			link.l1 = "Coś interesującego?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Coś ciekawego! Mój drogi wujek miał dochody pięciokrotnie większe, niż mi mówił! Złodziej! Defraudant!";
			link.l1 = "Nie mogę powiedzieć, że jestem zaskoczony. Nie można nikomu całkowicie ufać bez sprawdzenia faktycznego stanu interesów od czasu do czasu. To po prostu zdrowy rozsądek.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "Zdrowy rozsądek dla zwykłych ludzi, być może. Moje wychowanie zaślepiło mnie na takie oszustwa wśród dżentelmenów, których uważałem za honorowych! Masz rację jak zawsze, Carlos! Mój własny wujek mnie okrada! Mierda! To moja wina, ale naprawię to. Jestem właścicielem tej plantacji i mój wujek został dziś zwolniony ze swoich obowiązków! Jest nikim! Dopilnuję, by go wciągnięto pod kilem!";
			link.l1 = "Don Domingo... Nie sądzisz, że twój wuj może się nie zgodzić z taką decyzją?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "Nie obchodzi mnie, czy się zgadza, czy nie! Jestem markizem Domingo Ortiz Albalate, a Luis Ortiz to tylko dzierżawca, i to były dzierżawca! A on...";
			link.l1 = "Uspokój się, señor. Jesteś tu nieznajomą twarzą, a ja jestem Francuzem żeglującym pod holenderską licencją z... burzliwą przeszłością z hiszpańskimi patrolami antykorsarskimi. Co do twojego wuja, to on praktycznie rządzi tym miastem. Pomyśl o strażnikach i lokalnym gubernatorze. Myślisz, że wybiorą twoją stronę?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "Atakujesz punkt szpadą... Może... Nie. Hiszpańscy żołnierze nigdy nie odważą się podnieść ręki na szlachcica! Mój wuj może mnie wyzwać, jeśli ma odwagę!";
			link.l1 = "Chociaż, proponuję pójść inną drogą. A co powiesz na sąd?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ha! Masz rację, Carlos. Chodźmy porozmawiać z odpowiednimi władzami. Mój wuj popełnił błąd, zapisując dokładne szczegóły w swoich notatkach o handlu z przemytnikami. Kupił od nich niewolników za bardzo tanio. Te księgi będą nam bardzo pomocne, wątpię, że drań będzie w stanie mi w jakikolwiek sposób zaszkodzić, siedząc w lochach. Chodźmy, przyjacielu! Do Portobello!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "To nic innego jak plugawstwo i bezczelne kłamstwo! Jak śmie on szargać dobre imię moich rodziców swoim niegodnym językiem! Niech go diabli, sprawię, że za to zapłaci! Wyciągaj swój miecz, ty morderco!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Wujek Luis jest tam, gdzie jego dusza powinna być - w piekle... Carlos, wysłał cię do mnie mój anioł stróż! Cieszę się, że nie zaufałeś słowu tego łajdaka. Szczerze mówiąc, obawiałem się, że po prostu zostawisz mnie tutaj samego, żeby walczyć z tym kanalią\nTak, señor, sam nie jestem doskonały, ale to... to plugawa kłamstwo o tym, że wynająłem piratów, aby zamordowali moich własnych rodziców! Obwiniać mnie o to... to! Bah! Zasłużony los.";
			link.l1 = "Cieszę się, że dotarliśmy, Don Domingo. Co teraz? Mam nadzieję, że nie naruszyliśmy hiszpańskiego prawa.";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "Z prawem? Ha-ha! Nie, Carlos, pokażę tę wspaniałą księgę rachunkową z wszystkimi operacjami przemytniczymi mojego wuja. Nie zapomnij o kilku zamachach na moje życie, mamy wielką liczbę świadków po jego ostatniej próbie właśnie teraz. Nie martw się o to, mi buen amigo. To moje miasto, czas im wszystkim pokazać!";
			link.l1 = "Proszę postępuj ostrożnie, señor. Niech myślą o tobie lepiej niż myśleli o twoim zmarłym wujku.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "To jest plan, kapitanie. Ale nie okażę litości nikomu, kto ośmieli się mnie sprzeciwić. Pozwól, że wyrażę moją szczerą wdzięczność dla Ciebie, Carlosie! Proszę, idź do tawerny, odpocznij, napij się kielicha lub dwóch. Chętnie bym do Ciebie dołączył, ale miałeś rację. Czas, bym zmądrzał i sam przejął kontrolę nad plantacją. Zobacz się ze mną tutaj jutro, kapitanie!";
			link.l1 = "Bardzo dobrze, Don Domingo. Do zobaczenia jutro.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Ah, oto jesteś, mój dobry przyjacielu!";
			link.l1 = "Jak się masz, don Domingo? Jak tam twoja plantacja?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "Plantacja jest wspaniała, nie mogę tego samego powiedzieć o pieniądzach - okazuje się, że mój drogi wujek przesyłał wszystkie pieniądze do banku w Kartagenie. Odzyskanie mojego złota zajmie dużo czasu prawnikom. Ale to w porządku, mogę to załatwić. Nie smuć się kapitanie, dotrzymam obietnic, by wynagrodzić cię za twoją szlachetność, uczciwość i przyjaźń!";
			link.l1 = "Nie myślałem o nagrodzie, gdy walczyłem po twojej stronie, señor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "Znam to, kapitanie, i to mówi wiele o twoim charakterze! Każdy dobry uczynek musi zostać nagrodzony. Więc, chociaż w tej chwili nie mam pieniędzy, wydam rozkazy, aby załadować twój statek towarami z mojej plantacji. Mam na myśli kawę, świetną partię tego. Jestem pewien, że będziesz mógł sprzedać to z dużym zyskiem.";
			link.l1 = "O! To jest miłe..";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Ponadto mam kilka rzeczy, które dla mnie mają małą wartość, ale dla każdego żeglarza, takiego jak ty, są bezcenne. Dobra luneta i trzy amulety. Proszę, przyjmij to, teraz wszystko jest twoje.";
			link.l1 = "Wdzięczność!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "W końcu obdarzam cię moją szpadą jako wyrazem mojej niezmierzonej wdzięczności. Służyła mi dobrze, teraz niech służy tobie jeszcze lepiej. Spójrz na nią i pamiętaj o swoim dobrym hiszpańskim przyjacielu - markizie Domingo Albalate!";
			link.l1 = "Dziękuję bardzo, senor! Nie spodziewałem się...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "A teraz, niestety, muszę się pożegnać. Powinienem udać się do Portobello, aby zobaczyć się z gubernatorem, a następnie do Kartageny... Podsumowując, moje beztroskie życie dobiegło końca, czas żyć jak dorosły mężczyzna.";
			link.l1 = "Cóż, teraz jesteś znacznie mądrzejszy...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "To prawda. To była przyjemność, mój przyjacielu! Odwiedź mnie czasem. Pomyślnych wiatrów na morzu!";
			link.l1 = "Nawzajem, w twoim biznesie plantacyjnym, don Domingo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "Eh, jesteśmy spóźnieni, señor! Co za szkoda, mój dobry stary wujek już zrobił porządek w swoich papierach. Wygląda na to, że ktoś mu powiedział o Santo Domingo i podjął środki ostrożności... Ale nie zamierzam tego tak zostawić! Powinienem zobaczyć się z gubernatorem Portobello, aby rozpocząć procedurę prawną przeciwko mojemu wujowi. Mam dość tego, że zarządza moim majątkiem.";
			link.l1 = "Dobra decyzja.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "Chcę ci podziękować, kapitanie! To była przyjemność! Podaruję ci moją szpadę jako znak mojej wdzięczności. Dobrze mi służyła, niech teraz służy ci jeszcze lepiej. Spójrz na nią i pamiętaj o swoim dobrym hiszpańskim przyjacielu - markizie Domingo Albalate!";
			link.l1 = "Dziękuję ci bardzo, señor! Nie spodziewałem się...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "A teraz, niestety, muszę się pożegnać. Powinienem udać się do Portobello. Moje beztroskie życie się skończyło, czas żyć jak dorosły mężczyzna. Szczęśliwej podróży na morzu!";
			link.l1 = "Powodzenia z wujem, don Domingo! Jestem pewien, że zwyciężysz!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			dialog.text = "Wygląda na to, że dotarłem na czas. Mój beztroski siostrzeniec i jego anioł stróż Kapitan "+GetFullName(pchar)+" . Nie wyglądaj tak zaskoczony, Francuzie, wiem kim jesteś.";
			link.l1 = "Luis Ortiz?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "Masz rację, kapitanie, ale wszystko inne masz źle. Nie powinieneś wtykać nosa w sprawy rodzinne innych ludzi. Nawet nie masz pojęcia, kogo chronisz. Mój rozwiąźny siostrzeniec Domingo to bezwartościowy hulaka, numer jeden odwiedzający każdą tawernę i burdel, który zalicza lub przynajmniej próbuje zaliczyć każdą dziewkę na horyzoncie. Płacę mu czynsz każdego miesiąca, a on marnuje go w ciągu kilku dni, zawsze żądając więcej i więcej. Raz po raz. Jego nieustanne niegodne zachowanie doprowadziło do szaleństwa jego matkę i moją siostrę.\nSłyszałem plotki, że ten niegrzeczny chłopak nawet wynajął i skierował kilka angielskich kaprów na pewien statek markiza Ricardo Albalate, który zatopili razem z tym godnym człowiekiem i moją drogą siostrą. Domingo tak bardzo pragnął pieniędzy naszej rodziny, że byłby zdolny zabić za nie... Niestety, nie udało mi się zdobyć wystarczających dowodów, aby wysłać tego łajdaka na szubienicę.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			dialog.text = "Typowe. Krzyki, brzęk mieczy i kielichów, pełno hałasu i wściekłości, a nic to nie znaczy. Ile ci zapłacił, kapitanie, za ochronę?";
			link.l1 = "Z tego co rozumiem, po tym jak nie udało ci się znaleźć żadnych dowodów przeciwko swojemu siostrzeńcowi, zacząłeś wysyłać za nim zabójców. Wygląda na to, że proste postępowanie sądowe by wystarczyło.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "Kłamiesz. Domingo tutaj narobił sobie niezliczoną ilość wrogów. Zostawił po sobie ślad porzuconych kochanek i zdradzonych mężów. Zastanawiam się, jak udało mu się przetrwać tak długo! Zapytaj go, ile ślubów zrujnował? Ilu obrażonych narzeczonych zranił lub zabił?";
			link.l1 = "Jego sługa Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ach Ugo! Najgorszy łotr z nich wszystkich! Ugo uwielbiał swego hulaszczego pana. Wszystkie zbrodnie jego pana były dla niego niczym dziecięce psoty. Pamiętaj, Francuzie, interesy rodzinne są tylko dla rodziny. Ci, którzy wtykają nos i wścibiają się, znajdą się w tarapatach.";
			link.l1 = "Teraz mi grozisz.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "To nie groźba, kapitanie, a obietnica. Posłuchaj chłopcze, daleko zaszedłeś, ale ponieważ uważam cię za zwiedzioną ofiarę, a nie wroga, wysłuchaj mojej prostej i szczodrej oferty: odejdź. Nie chcę tu przelewać krwi. Nie potrzebujemy twojej pomocy w rozwiązywaniu naszych rodzinnych spraw. Jestem nawet gotów wynagrodzić ci kłopoty, które przeżyłeś z powodu mojego idiotycznego siostrzeńca - "+FindRussianMoneyString(iTotalTemp)+"reali. Weź je i zostaw nas w spokoju. Odrzuć moją ofertę, a odeślemy cię z powrotem na twój statek w cienkich plasterkach.";
			link.l1 = "'Rodzina przede wszystkim' – to zawsze mówię. To nie moja sprawa, więc oddaj pieniądze i 'vaya con Dios.'";
			link.l1.go = "uncle_7";
			link.l2 = "Twoja opowieść śmierdzi gorzej niż nawóz z twojej plantacji. Don Domingo może nie jest świętym, ale ty señor jesteś diabłem!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "Wiedziałem, że jesteś rozsądnym człowiekiem. Weź swoje pieniądze i adios, kapitanie. Spróbuj nie grzebać w cudzym brudzie w przyszłości - nigdy tego nie doceniają.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			dialog.text = "Diabeł? Cóż, z przyjemnością wyślę cię do piekła!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+"senor. Jak mogę służyć?";
			link.l1 = "Witajcie. Wybaczcie, ale czy to rezydencja Senora Domingo Albalate?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Si, to jest dom Albalate. Jest skromny, ale wygodny. Nazywam się Ugo, służę młodemu panu. Czy jesteś tu dla niego?";
			link.l1 = "Si, señor. Don Domingo zaprosił mnie do siebie niedawno. Był bardzo przekonujący. Czy mogę go zobaczyć?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Ach, mój drogi caballero, Don Domingo nie jest teraz w domu. Osobiście sam chciałbym wiedzieć, gdzie znaleźć tego niegrzecznego chłopca... eh, przepraszam, młodego senora. Czy mogę zapytać, czego od niego potrzebujesz?";
			link.l1 = "„Cóż... Pomogłem Don Domingo przez przypadek. Został zaatakowany przez dwóch łotrów w tawernie w Port-au-Prince. Pomogłem waszemu panu w obronie przed tymi... jak ich nazwał... maldita canalla. Don Domingo zaprosił mnie, bym go odwiedził tutaj, kiedy zakończy swoje śledztwo. Myślałem, że wszystko powinno być już załatwione, więc spodziewałem się zobaczyć go w domu.”";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Madre de Dios! Jakie straszliwe historie opowiadasz tutaj! Muszę natychmiast zobaczyć się z komendantem - ostrzec go o niebezpieczeństwach, z którymi Don Domingo właśnie się mierzy! Señor, musisz iść, a ja powinienem się spieszyć!";
			link.l1 = "Spokojnie, Ugo. Twój młody pan jest bezpieczny. Wspomniał, że jego dokumenty są w porządku, mieli go już wypuścić, dlatego tu jestem. Wierzę, że wkrótce go zobaczymy.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "O! Jak mogłeś? Mój młody pan, ten naiwny chłopiec - i w rękach tych żabojadów Francuzów?! Nie wspominając o ladronos grożących jego życiu? Nie, muszę zobaczyć się z komendantem! Panie, proszę idź!";
			link.l1 = "Dobrze, dobrze, nie bądź taki nachalny. Już odchodzę.";
			link.l1.go = "ugo_exit";
			link.l2 = "Señor, czemu tak nerwowo? Już ci mówiłem, że nie ma zagrożenia dla twojego pana. Pozwól mi tu zostać i poczekać na przybycie Señora Domingo, jestem bardzo zmęczony moją długą podróżą i doceniłbym twoją gościnność. Chciałbym trochę chłodnej, świeżej wody i gorącej kąpieli, aby spłukać sól z mojego gardła. Potem możesz pójść do miejscowego garnizonu i robić, co chcesz.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = "Señor, opuść ten dom natychmiast!";
			link.l1 = "Ugo, naprawdę wątpię, by służący mógł rozmawiać z dżentelmenem w ten sposób. Również wątpię, czy Don Domingo zaakceptowałby takie traktowanie człowieka, który uratował mu życie!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "O naprawdę? (wołając na górę) Chłopcy, schodźcie na dół, mamy problem!";
			link.l1 = "Co do cholery?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
