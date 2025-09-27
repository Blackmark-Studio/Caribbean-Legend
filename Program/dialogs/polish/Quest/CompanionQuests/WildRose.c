void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "Czego chcecie?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+" , spójrz tutaj!";
			link.l1 = "Cicho, "+npchar.name+", możemy nie być tu sami.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"? Szłaś za mną krok w krok, tak, co nie?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "Wygląda na to, że nie na darmo, tak, co nie!   Co tu się stało?";
			link.l1 = "Gdybym wiedział, "+npchar.name+", gdybym wiedział...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "O Boże...";
			link.l1 = "Tak, biedaczysko chyba nieźle się nacierpiało przed śmiercią. Nikomu nie życzyłabym takiego końca...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "A to kto tam, jej mąż? Co do diabła robili w dżungli?! Naprawdę nie słyszeli o zbiegłych niewolnikach?";
			link.l1 = "Obawiam się, że na to pytanie już nie będą w stanie odpowiedzieć...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "Myślisz, że ten, kto to zrobił, wciąż jest gdzieś w pobliżu, tak, co nie?";
			link.l1 = "Bardzo możliwe. Dlatego powinniśmy zachowywać się ciszej – musimy zobaczyć ich pierwsi.";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "Za późno, "+pchar.name+". Wygląda na to, że już nas zauważyli. Spójrz tam.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "No proszę, chłopaki, tylko spójrzcie. Mamy tu prawdziwą dolinę zakochanych, co nie, he-he. Ledwo dwoje gołąbków oddało dusze Bogu, a już na ich miejsce zjawiła się kolejna para...";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "Bardzo dowcipnie. Ale chyba nie umiesz liczyć – w przeciwieństwie do tych biedaków, my wcale nie jesteśmy tu sami.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "No z nami będzie trochę trudniej, tak, co nie...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "Powiedziałbym, że jesteście mądrzejsi od nich – ale to byłoby bezbożne kłamstwo. Nawet w takiej liczbie nie dalibyście rady tym draniom. A twoją ślicznotkę spotkałby los tej dziewczyny, która leży ci pod nogami...";
			link.l1 = "Mówisz o zbiegłych niewolnikach? To jeden z nich? Czyli jesteście ludźmi Bishopa?";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "Na wszystkie pytania – tak. Przez ponad dwa dni razem z żołnierzami ganialiśmy ich po całej wyspie. Potem łajdaki się rozdzielili. Część uciekła w stronę jaskini – za nimi poszła straż, reszta – zwiała do zatoki. W wyniku ich zasadzki pół mili na zachód stąd straciliśmy kilku chłopaków, a kiedy dochodziliśmy do siebie i przegrupowywaliśmy się, oni zabawiali się z tą głupią dziewuchą...";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
		break;
		
		case "Naemnik_4":
			dialog.text = "Nie dotykaj tej swojej wykałaczki, szczylu – nie denerwuj mnie ani moich chłopaków. Ciekawe, jakby ci pomogła, gdybyś znalazł się otoczony przez tuzin tych drani, których położyliśmy w zatoce. No, tylko jednemu się poszczęściło – ale to nie potrwa długo... Jak tylko ten drań trafi w ręce Bishopa...";
			link.l1 = "Więc jesteście jego najemnikami?";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "No przecież to nie byli żołnierze z garnizonu. Gdyby nie ci safanduły, złapalibyśmy tych łotrów już wczoraj – i ten głupiec ze swoją żoną by żyli...";
			link.l1 = "Więc to nie wasza robota...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Za kogo ty nas masz, co? My, jasne, nie jesteśmy aniołami, ale jak nam się zachce, to idziemy do burdelu, a nie...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "Kłamie, kłamie – podły łajdak! Nie słuchajcie go, "+GetAddress_Form(NPChar)+"! Nawet palcem nie tknęliśmy tych biedaków!";
			link.l1 = "Tak?   I dlaczego mielibyśmy uwierzyć właśnie tobie, a nie jemu?";
			link.l1.go = "Naemnik_8";
			link.l2 = "Tak? A może to ty tak naprawdę kłamiesz? Na świętoszka to jakoś nie wyglądasz.";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "No pomyślcie sami, na Boga! Uciekaliśmy przed tym potworem Bishopem, dwa dni błąkaliśmy się po dżungli, zacierając ślady – po co? Żeby teraz skrzywdzić biedną damę i pozwolić tym krwiopijcom nas dogonić?! Moi przyjaciele ledwo dowlekli się wtedy na tę plażę, "+GetAddress_Form(NPChar)+"! Nie mieliśmy nawet siły strzelać z naszych muszkietów, tak, co nie? Inaczej nie pozwolilibyśmy tym łajdakom zrobić swojego czarnego dzieła... To wszystko oni, widzieliśmy to, tak, co nie!..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "No pomyślcie sami, na Boga! Uciekaliśmy przed tym potworem Bishopem, dwa dni błąkaliśmy się po dżungli, zacieraliśmy ślady – po co? Żeby teraz skrzywdzić biedną damę i pozwolić tym krwiopijcom nas dogonić?! Moi przyjaciele ledwo dowlokli się wtedy na tę plażę, "+GetAddress_Form(NPChar)+"! Nie mieliśmy nawet siły strzelać z naszych muszkietów, tak, co nie, inaczej nie pozwolilibyśmy tym łajdakom zrobić tego podłego czynu... To wszystko oni, widzieliśmy!..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "Zamknij się, Casper, ty parszywy psie!";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "Co ty powiedziałeś?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "Nie słyszysz, panienko? Powiedziałem mu, żeby zamknął jadaczkę. Nasz Jerry potrafi godzinami opowiadać bajki – ma do tego prawdziwy talent! Bishop chciał mu odciąć język i kazać go zjeść, ale się rozmyślił – a szkoda, do diabła!";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "Ale... Nazwałeś go Kasperem, tak, co nie...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "Słuchaj, chłopcze, wytłumacz swojej panience, że ludzie, nawet tacy jak ten niedojrzały, oprócz imienia mają też nazwisko. Nieraz słyszałem, że ładne dziewczyny bywają głupie jak worek słomy, ale żeby aż tak, to niech mnie piorun trafi...";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "Właśnie to ci teraz zrobię, tak, co nie!";
			link.l1 = "Mary, zaczekaj! Poradzę sobie z tym sam. Schowaj broń do pochwy. Natychmiast.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "O, tak mamy tu szlachetnego dżentelmena. No cóż, twoje zachowanie jest rzeczywiście bardziej godne niż wrzaski tego śliskiego typa. Krzyczał głośniej niż jego biedna żonka – aż było słychać zza tamtego wzgórza. Przyznam, nawet nam się przysłużył – właśnie tak namierzyliśmy tych drani...";
			link.l1 = "Tutaj, na Karaibach, szlachetność to prawdziwa rzadkość. A teraz wszyscy odetchnijmy — nie ma nic szlachetnego w tym, żeby właśnie teraz i tutaj udać się na tamten świat.";
			link.l1.go = "Naemnik_17";
			link.l2 = "Łajdaki tutaj to tylko wy. Natychmiast przeproś Mary, i może obejdzie się bez rozlewu krwi.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "Trudno się nie zgodzić. Tylko najpierw uspokój swoją...";
			link.l1 = "Nazywa się Mary Casper. Myślę, że to wiele wyjaśni.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "Kasper? Ona co, jego córka, haha?";
			link.l1 = "Bardzo w to wątpię. Ale mam nadzieję, że teraz będziesz miał dość rozumu, żeby cofnąć swoje słowa.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "Z powrotem? A co, jeśli nie? Wyzwasz mnie na pojedynek? Śmiało... Jeśli tylko nie boisz się zostawić swojej ukochanej zupełnie samej, pośrodku dżungli, he-he. Ja i chłopaki będziemy baaardzo zadowoleni z takiego obrotu spraw.";
			link.l1 = "No i pokazaliście swoją prawdziwą twarz. Niezbyt dobrze wam szło udawanie.";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "Pan to jednak pełen sprzeczności — taki pokojowo nastawiony, a jednocześnie prostak. Niemniej jednak, ciekawi mnie: błaga pan o przebaczenie tej rudowłosej wariatki?";
			link.l1 = "Nazywa się Mary Casper, i jeśli teraz nie...";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "Kasper? Niech mnie diabli! Jerry, to przypadkiem nie twoja córeczka, co? Ha-ha-ha-ha! Nie wierzę własnym uszom! Takie rzeczy się zdarzają!";
			link.l1 = "A wiesz, jak jeszcze bywa? Tacy jak ty – gamonie, co o honorze słyszeli tylko z opowieści – zachowują się wobec dam, jakby urodzili się w stajni. Zresztą, czemu się dziwić – kiedy zamiast rozumu masz trociny, to i manier nie ma skąd wziąć.";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "Ba... Ależ z ciebie zuchwały robak. Powiedz mi, przyjacielu, czy twoja dziewczyna jest taka dobra w hamaku? Chociaż jestem pewien, że nie — i z przyjemnością sam to sprawdzę...";
			link.l1 = "No i się zdradziłeś. Na długo cię nie starczyło. Do walki!";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "Ale im nieźle przyłożyłeś, "+GetAddress_Form(NPChar)+", - tych łajdaków. Niech płoną w piekle! Szkoda, że nie zdążyłem wam pomóc. Muszkiet, który wypatrzyłem po drodze, leżał zbyt daleko. Chyba ktoś z naszych go zgubił, kiedy uciekaliśmy. Chciałbym zastrzelić tego drania Primera własnoręcznie.";
			link.l1 = "Wygląda na to, że Primer musiał ci nieźle dokuczyć, skoro postanowiłeś wrócić.";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "Oj, jeszcze jak doskwierał. Przez tego drania mam całe plecy w bliznach. Ale najgorsze było to, że mógł nam zakazać pić wodę, kiedy tylko miał na to ochotę.";
			link.l1 = "Szkoda, że żaden z tych drani nie przeżył. Można by go było oddać żołnierzom – którzy, jestem pewna, wkrótce się tu zjawią.";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "Nie do końca rozumiem, po co, eee, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "No bo wiesz... Komendant wymusiłby na nim przyznanie się, oczyszczając wasze imiona – twoje i twoich poległych przyjaciół.";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "Aha, na pewno, ha-ha. A potem William Bishop obedrze mnie ze skóry – opowiadał mi o tym jeden czarnuch z plantacji... Bishop nie patyczkuje się z uciekinierami – i czy jesteś czarny, czy biały, to nie ma znaczenia.";
			link.l1 = "Obawiam się, że tak czy inaczej będziesz musiał wrócić na plantację...";
			link.l1.go = "Djerry_5";
			link.l2 = "Czyli dobrowolnie na plantację nie wrócisz, tak, co nie?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "A jesteś niezłym żartownisiem – mówili ci to już, tak, co nie? "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Bez żadnych żartów, "+npchar.name+". Myślisz, że znalazłem się tu przypadkiem? Poszedłem do selwy, żeby odnaleźć wasz oddział, odprowadzić z powrotem na plantację – no i trochę zarobić złota. Ale został tylko ty. Za ciebie dużo nie dostanę, więc może cię puszczę wolno. Ale powiedz mi – co ty w ogóle sobie myślałeś? Zostałeś sam. Wszyscy inni nie żyją. Na co liczysz, do diabła? Chować się po górach i krzakach, aż dostaniesz kulkę, zdechniesz od febry albo zostaniesz żarciem dla jaguarów?";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "Ale z pana niezły żartowniś – mówili już panu o tym, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Żadnych żartów, "+npchar.name+". Myślisz, że trafiłem tu przypadkiem? Wyruszyłem do selwy, żeby odnaleźć wasz oddział, sprowadzić go z powrotem na plantację — i trochę zarobić na złocie. Ale został tylko ty. Za ciebie dużo nie dostanę, więc może cię puszczę. Ale powiedz mi — co ty sobie w ogóle wyobrażałeś? Zostałeś sam. Wszyscy inni nie żyją. Na co, do diabła, liczysz? Że będziesz się chował po górach i krzakach, aż nie dostaniesz kulki, nie padniesz na febrę albo nie staniesz się karmą dla jaguarów?";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "Lepiej już tak, jak Boga kocham, "+GetAddress_Form(NPChar)+" - moim zdaniem to i tak lepsze, niż zdechnąć od mąk, które przygotował dla mnie Bishop. Ale tak naprawdę, nie jest aż tak źle - przy przylądku Ragged Point mam schowaną łódź z żaglem.";
			link.l1 = "Najbliżej od Barbadosu są ziemie Dominiki z tubylcami i Tobago z Hiszpanami. Nawet nie wiem, co dla ciebie... gorsze.";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "Myślę, że zaryzykuję z donami – na Tobago często zatrzymują się przemytnicy i piraci. O, widzę, że potępiasz mój wybór, "+GetAddress_Form(NPChar)+". Szczerze służyłem swojej ojczyźnie – ale co mam zrobić, skoro ona wysłała mnie do kamieniołomów?";
			link.l1 = "Nie oceniam, "+npchar.name+" . Każdy ma swoją drogę. A teraz weź więcej prochu i kul – i ruszaj. Zanim zjawią się tu żołnierze.";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "Dziękuję, "+GetAddress_Form(NPChar)+". I panią, młoda damo, e-e, Mary. (kłania się). Oczywiście nie jesteśmy rodziną, ale spotkać kogoś o tym samym nazwisku w takiej, e-e, sytuacji... to naprawdę niespodziewane i...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "Chyba tak, tak, co nie? A teraz żegnaj, Jerry.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", jesteś czymś zaniepokojona? Tak szybko pożegnałaś się ze swoim imiennikiem, tak, co nie?";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "Po prostu chciałam jak najszybciej pozbyć się towarzystwa tego człowieka... Jego historia jest szyta grubymi nićmi, tak, co nie?";
			link.l1 = "O czym ty mówisz, kochanie?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "Po tym, co usłyszałam z ust tego pachołka Bishopa, nie mam wątpliwości, że ci biedacy zginęli właśnie z jego ręki. Ale co do tego... Kasperze – słuchałeś uważnie, co on mówił?";
			link.l1 = "A co ci nie pasowało, kochanie?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "Mówi, że na plaży ukryta jest łódź. Ale z plantacji uciekło ponad dwadzieścia osób. To znaczy, że łódź musi być całkiem spora, tak, co nie? Jerry to dezerter z floty, nie może nie rozumieć, że samemu z tak dużą łajbą raczej sobie nie poradzi, tak...";
			link.l1 = "Musi tylko postawić żagiel i obrać kurs – resztę zrobi wiatr. Tak, co nie? Ryzykuje naprawdę sporo, ale chyba śmierć na morzu jest lepsza niż z ręki kata-plantatora.";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "Niech będzie. Ale właśnie teraz zrozumiałam, że coś jeszcze się nie zgadza... Według jego słów, on i jego przyjaciele z daleka obserwowali, jak najemnicy znęcają się nad tą biedaczką...";
			link.l1 = "Zamiast pędzić co sił do swojej łodzi... Tak, wiem, do czego zmierzasz, "+npchar.name+". Chyba warto zadać panu Kasperowi jeszcze kilka pytań...";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " Hej, "+npchar.name+", stary! Zaczekaj chwilę...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " Cholera!!! Mary, uważaj!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "Podły drań! Uratowaliśmy mu życie, a on! Co z tego wychodzi, "+pchar.name+"? Wychodzi na to...";
			link.l1 = "Tak, "+npchar.name+", już nie żyje nikt, kto znał prawdę o tym, co się wydarzyło...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "Powinniśmy się stąd zwijać, "+pchar.name+". Jeśli żołnierze nas tu znajdą, będziemy mieli przechlapane, tak, co nie?";
			link.l1 = "Masz rację, Mary. Chodźmy...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "Wiesz, "+pchar.name+", po tym wszystkim mam ochotę porządnie się napić, tak, co nie?";
			link.l1 = "Nie będę się sprzeciwiał, kochanie. Sam mam ochotę zwilżyć gardło. Chodźmy zajrzeć do 'Irlandzkiego Rogacza'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "Wybacz, że cię obudziłem, kapitanie...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Zapukałeś, i za to dzięki. A teraz mów, czego ode mnie chcesz?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "Dobrze, że wpadłeś na pomysł zapukać, przyjacielu. Gdybyś się tu wdarł bez pytania, już byś zjeżdżał po schodach\nNa co się gapisz? Mów, po co tu swoją osobę przywlokłeś?";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "Jeden z mieszkańców chce się z tobą zobaczyć – Lewis Gernon. Mówi, że ma do ciebie ważną sprawę.";
			link.l1 = "Pierwszy raz słyszę to imię. Mam nadzieję, że naprawdę ma coś ważnego, skoro tak mnie odrywa od... sprawy. Niech wchodzi...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "Dzień dobry, panie "+pchar.lastname+". Panna... Casper.";
			link.l1 = ""+TimeGreeting()+", panie "+npchar.lastname+". Nie przypominam sobie, żebyśmy się wcześniej spotkali. Skąd więc nas znacie?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "Nie przypominacie sobie? Ach, rozumiem... Moja twarz była cała umazana krwią i kurzem, sam się przeraziłem, kiedy kilka godzin temu zobaczyłem się w lustrze...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "Ty... ty jesteś tym mężczyzną, tak, co nie, znaleźliśmy cię i...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "I moją Susan. Moją biedną Suzi...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "Myśleliśmy, że nie żyjecie. Tak samo jak... Ona była waszą żoną, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "Tak, proszę pani. Była moją żoną, a ja zamarłem ze strachu... i nie mogłem nic zrobić. Boże mój, Boże mój...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(płacze)   Oni mnie pobili i zmusili patrzeć na to...";
			link.l1 = "Wstańcie, "+GetAddress_Form(NPChar)+" . Nie jesteście niczemu winni. Nikt nie dałby rady samotnie przeciwko tylu łajdakom.";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "Było ich tak wielu, tak wielu... Ale jednak ja...";
			link.l1 = "Ale jednak pan przeżył, a mordercy pańskiej żony smażą się w piekle. To marne, ale jednak jakieś pocieszenie, panie "+npchar.lastname+". Jednak chciałam o coś zapytać...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "Tak, panie "+pchar.lastname+"?";
			link.l1 = "Kto to był? Najemnicy Bishopa czy zbiegli niewolnicy?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "Zrobili to Jerry Casper i reszta uciekinierów. Niesłusznie podejrzewaliście Bruce'a Primera i jego ludzi.";
			link.l1 = "Najemników Bishopa?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "Tak. Bruce, oczywiście, był niezłym łajdakiem i robił dla Bishopa wiele brudnej roboty – ale gwałcicielem nie był.";
			link.l1 = "Jakoś mi się tak nie wydawało. Ale nie będę się z panem spierać, "+npchar.name+". Jednak skoro byłeś przytomny i wszystko widziałeś, mógłbyś wstać i...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "Wybacz mi, "+GetAddress_Form(NPChar)+". Możesz uważać mnie za żałosnego tchórza — ale byłem tak przerażony, że nie mogłem się ruszyć. Kiedy ci dranie zagrodzili drogę mnie i Suzy, najpierw wrzasnąłem ile sił w płucach, chciałem wezwać pomoc.";
			link.l1 = "I pobili was.";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "Jerry walnął mnie kolbą muszkietu, a potem powiedział, że potnie mnie na kawałki, prosto na oczach Susan. Ja... wstyd mi się do tego przyznać, ale chyba na chwilę nawet straciłam przytomność ze strachu. A oni w tym czasie...";
			link.l1 = "Rozumiem pana, panie "+npchar.lastname+". W twoim zachowaniu nie ma niczego haniebnego. Niewielu potrafiłoby to znieść. Szkoda, że nie zareagowałeś – ale tego, co się stało, już nie odwrócimy. Cieszę się jednak, że przynajmniej jednego z zabójców twojej żony odesłaliśmy na tamten świat – choć prawie udało mu się nas wykiwać.";
			link.l1.go = "Lewis_14";
			link.l2 = "Czyli prawie zginęliśmy w walce z najemnikami Bishopa tylko dlatego, że się baliście, tak, co nie? Świetna wymówka, "+npchar.name+". Dobrze, że w ogóle, choć z opóźnieniem, udało nam się zorientować w sytuacji...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "Tak, "+GetAddress_Form(NPChar)+". Przyszedłem wam za to podziękować. Nawet jeśli najpierw mu uwierzyliście...";
			link.l1 = "Bruce Primer naprawdę się do tego przyłożył. Powinien bardziej uważać na to, co mówi...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "Tak, "+GetAddress_Form(NPChar)+". Przyszedłem wam za to podziękować. Nawet jeśli na początku mu uwierzyliście...";
			link.l1 = "Bruce Primer naprawdę się postarał, tak, co nie? Powinien bardziej uważać na to, co mówi...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "Niestety, wszyscy tego dnia popełniliśmy błędy... My ze Susan nie powinnyśmy były wybierać się na spacer do Ragged Point, Bruce powinien był w porę ugryźć się w język... A ty nie powinieneś był ufać Jeremy'emu. Ale dzięki pannie Casper sprawiedliwość została przywrócona.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "Domyślam się, o co chce mnie pan zapytać, panie "+sld.lastname+". Ale nie mam z tym człowiekiem nic wspólnego.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "Wiem, panno. Zrozumiałem to od razu, gdy tylko wszedłem do tego pokoju. On i pani nie mają ze sobą najmniejszego podobieństwa. A jednak, Susan... była pewna, że nic na tym świecie nie dzieje się przypadkiem.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "Twoja żona miała rację. Sama się o tym przekonałam nie raz, tak, co nie? I "+pchar.name+" też.";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "Zgadza się. Jednak nie sądzę, żeby to był czas na filozoficzne rozmowy. Wątpię, żeby to wam pomogło, "+npchar.name+". Z czymś takim poradzi sobie tylko czas.";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "Chyba ma pan rację, panie "+pchar.lastname+". No cóż, dziękuję wam raz jeszcze i żegnajcie. Będę się za was modlić, za was i za pannę Casper.";
			link.l1 = "Wszystkiego dobrego, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Wiem, kochanie, prawie pozwoliłem temu draniowi uciec...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "Drania o imieniu Jerry Casper.";
			link.l1 = "Zgadza się... Poczekaj... ty myślisz, że on...";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "Wiem, że to bardzo głupie...";
			link.l1 = "Jeszcze jak! A gdybyś miała na nazwisko Smith albo Jones? Tych po ulicach chodzi bez liku – i któryś z nich na pewno robi jakieś świństwa... A ten Jerry, niech go piekło pochłonie – może on wcale żadnym Casperem nie jest...";
			link.l1.go = "Mary_34";
			link.l2 = "Tak jest, kochanie. Ten cholerny Jerry mógł się w ogóle nie przedstawić swoim nazwiskiem – i tyle.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "A jednak... Wiem, że mnie nie rozumiesz, ale po prostu wyobraź sobie, co byś pomyślał, gdyby on miał takie nazwisko "+pchar.lastname+".";
			link.l1 = "To nie to samo, Mary. "+pchar.lastname+" - szlachecka rodzina, a...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "A jednak... Wiem, że mnie nie rozumiesz, ale po prostu wyobraź sobie, co byś myślał, gdyby on miał takie nazwisko "+pchar.lastname+".";
			link.l1 = "To nie to samo, Mary. "+pchar.lastname+" - szlacheckie nazwisko, a...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "A Kasperowie to tak, ludzie bez rodu, bez plemienia, tak, co nie? Chyba powinnam codziennie dziękować Panu naszemu za to, że w ogóle zwróciłeś na mnie uwagę, a nie na jakąś nadętą...";
			link.l1 = ""+npchar.name+", nie o to mi chodziło - przecież to rozumiesz. Członków rodu szlacheckiego łączą więzy krwi - a to zupełnie co innego, niż po prostu mieć z kimś to samo nazwisko. Które, jak już mówiłem, ktoś mógł sobie po prostu przywłaszczyć...";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "Nie tylko o to chodzi, "+pchar.name+"...";
			link.l1 = "Kochanie, mieliśmy długi i ciężki dzień. Przeszliśmy niejedną milę przez dżunglę, mogliśmy zginąć... a potem nawet porządnie się nie wyspaliśmy. Nic dziwnego, że w twojej głowie pojawiły się różne dziwne myśli. Oboje po prostu musimy się porządnie wyspać.";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "Wcale nie uważam, że to dziwne, ale dobrze... pogadamy jutro.";
			link.l1 = "Na świeży umysł szybciej się we wszystkim połapiemy. Połóż się, kochana, musimy zostawić ten dzień za sobą.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "Wszystko z tobą w porządku, "+GetAddress_Form(NPChar)+"? Wyglądacie dziwnie, jakbyście ducha zobaczyli. Może napijecie się rumu? Albo wina? Mamy świetny wybór, tak, co nie? Przydałoby się wam trochę się rozluźnić.";
			link.l1 = "Do diabła z piciem. Szukam dziewczyny...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "To pan się pomylił, kapitanie. To jest tawerna, a nie burdel. Proszę wyjść na zewnątrz, a naprzeciwko zobaczy pan...";
			link.l1 = "Słuchaj, nie mam teraz głowy do żartów. Szukam rudowłosej dziewczyny w czerwonym kaftanie, jest uzbrojona. Nazywa się Mary Casper.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "No skoro nie czas na żarty, to nie mam wam nic do powiedzenia. Moja zmiana zaczęła się godzinę temu i żadnej rudej w czerwonym kaftanie tu nie widziałam.";
			link.l1 = "Czyli odeszła w nocy... Ale dokąd mogła pójść?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "Dzień dobry, kochanie! Ależ się wyspałeś...";
			link.l2 = "Ależ mnie przez ciebie nastraszyło, tak, co nie? "+npchar.name+". Nie znikaj już tak, bez ostrzeżenia...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "Nie chciałam cię budzić. No i wiesz, ty też czasem tak znikasz bez słowa, tak, co nie...";
			link.l1 = "I ty postanowiłaś odpowiedzieć mi tym samym?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "Tak naprawdę, po prostu musiałam pobyć sama ze swoimi myślami, tak, co nie? Nie chciałam, żebyś się martwił.";
			link.l1 = "Coś cię martwi?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "Nasza wczorajsza rozmowa. O nazwiskach, więzach krwi...";
			link.l1 = "Czyli jednak się na mnie obraziłaś...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "Wcale nie, kochanie, zupełnie nie o to mi chodziło. Po prostu nagle zdałam sobie sprawę, że tak naprawdę nic nie wiem o swojej rodzinie. Ty na przykład – jesteś synem szlacheckiego rodu. Chłopaki na statku czasem coś opowiadają o swoich bliskich. A ja? Ja nawet nie mam o czym mówić – nigdy nie znałam swoich rodziców. Cholera, nawet nie wiem, gdzie się urodziłam...";
			link.l1 = "Czy nie na Wyspie Sprawiedliwości?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "Eric, człowiek, który mnie wychował, właśnie tak twierdził. Ale skoro tak – dlaczego nikt z mieszkańców Wyspy nigdy nie opowiadał o moich rodzicach, nawet ich nie wspominał? Raz zapytałam o to Donalda Greenspiego, ale nie powiedział nic sensownego.";
			link.l1 = "Albo po prostu nie chciał mówić.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "No właśnie! I ja pomyślałam dokładnie to samo, tak, co nie? Wiesz, wcześniej po prostu sobie żyłam, nie zastanawiając się nad tym za bardzo. Ale wczoraj, kiedy natknęliśmy się na tego drania Jerry'ego... zapytałam siebie – kim był mój ojciec? Moja mama? Dlaczego nigdy mi o nich nie opowiadano, jakby w ogóle nie istnieli? A co jeśli mój ojciec był takim samym łajdakiem jak ten Jerry?";
			link.l1 = "To nie ma żadnego znaczenia, "+npchar.name+". Wychowali cię inni ludzie – i zrobili to naprawdę dobrze.";
			link.l1.go = "Mary_50";
			link.l1 = "Wątpię, żeby tak było. I nie bardzo rozumiem, jakie to ma znaczenie, skoro wcześniej jakoś o tym nie myślałaś.";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "Ale dla mnie to ważne, "+pchar.name+", tak, co nie? Chcę wiedzieć, mam prawo wiedzieć, kim byli moi rodzice. Czy ty się z tym nie zgadzasz?";
			link.l1 = "Oczywiście, zgadzam się, inaczej być nie może. Ale jeśli próbować dowiedzieć się czegoś o twoim ojcu i matce, to tylko na Wyspie Sprawiedliwości. Przecież nawet nie znasz ich imion, tak, co nie?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "Ale dla mnie to ważne, "+pchar.name+", tak, co nie? Chcę, mam prawo wiedzieć, kim byli moi rodzice. Czy ty się z tym nie zgadzasz?";
			link.l1 = "Oczywiście, że się zgadzam, inaczej być nie może. Ale jeśli próbować dowiedzieć się czegoś o twoim ojcu i matce, to tylko na Wyspie Sprawiedliwości. Przecież nawet nie znasz ich imion, tak, co nie?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "Tak jest, kochany. Przy mnie ani razu o nich nie wspominali, tak, co nie?";
			link.l1 = "Czyli do miejskich archiwów angielskich kolonii póki co się nie wybieramy. Najpierw musimy wrócić na to cmentarzysko statków i spróbować znaleźć jakieś ślady twojego pochodzenia właśnie tam.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "Cieszę się, że mnie rozumiesz, "+pchar.name+". Dziękuję ci.";
			link.l1 = ""+npchar.name+", naprawdę mnie zaskakujesz. To najmniejsze, co mogę dla ciebie zrobić, kochana.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "Jakoś przeżyłam prawie dwadzieścia lat, nic o nich nie wiedząc...";
			// dialog.text = "W końcu przez ponad dwadzieścia lat zupełnie mnie to nie obchodziło...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "No więc mogę jeszcze trochę wytrzymać, tak, co nie?";
			link.l1 = "Widzę, że to dla ciebie ważne i potrzebne, "+npchar.name+". Postaram się więc nie kazać ci długo czekać. A teraz chodźmy, musimy wracać na statek. Tam jestem o ciebie spokojniejsza, przynajmniej trochę.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "Rodzinne brzegi... Wiesz, "+pchar.name+" , wydaje mi się, że gdybyśmy trafili tu za dziesięć lat, wszystko wyglądałoby dokładnie tak samo jak teraz, tak, co nie.";
			link.l1 = "Może być, "+npchar.name+", może być. Statki wewnętrznego kręgu pozostaną na wodzie, ale ludzie tutaj będą już inni.";
			link.l1.go = "Mary_62";
			link.l2 = "Bardzo w to wątpię – tutaj wszystko trzyma się już tylko na słowie honoru. I na geniuszu Mechanika.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "A ja przecież ledwo pamiętam tych, którzy mieszkali na tych wrakach jeszcze dziesięć, piętnaście lat temu. Tylko tych najbliższych mi ludzi – Alana, Erika...";
			link.l1 = "Chyba tak już musi być. Nie da się pamiętać wszystkiego i wszystkich. Mnie też zacierają się w pamięci imiona i twarze – z czasów Paryża, nie mówiąc już o Gaskonii. A myślałem, że to zdarza się tylko starym ludziom.";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "A ja przecież nawet dobrze nie pamiętam tych, którzy mieszkali na tych wrakach jeszcze dziesięć, piętnaście lat temu. Tylko tych najbliższych mi ludzi – Alana, Erika...";
			link.l1 = "Chyba tak już musi być. Nie da się pamiętać wszystkiego i wszystkich. Mnie też zacierają się w pamięci imiona i twarze – z czasów Paryża, nie mówiąc już o Gaskonii. A myślałem, że to spotyka tylko starców.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "Ale to miejsce... Jakby inny świat, tak, co nie? Wyobraź sobie, niektórzy z tych, co przybyli tu niedawno, twierdzą, że czas płynie tu prawie trzy razy szybciej niż na Wielkiej Ziemi...";
			link.l1 = "Ha-ha, ile ty wtedy miałbyś lat?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "Naprawdę mówiłam poważnie, "+pchar.name+", tak, co nie!";
			link.l1 = "No dobrze, ale tak na poważnie, czas zabrać się do roboty. Czy wśród narwali jest ktoś starszy od Grinspiego?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "Mmm, nie, chyba nie. Ale już ci mówiłam, że nic mi nie powiedział, kiedy go o to zapytałam.";
			link.l1 = "I mimo wszystko, nie mam innych pomysłów, kto mógłby nam pomóc rozwikłać wydarzenia sprzed dwudziestu lat. Przynajmniej na razie. Tak że obieramy kurs na 'Esmeraldę'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "A, "+pchar.name+" i Mary, cóż za spotkanie! Cieszę się, że was tu widzę... żywych, he-he. W ostatnim miesiącu przy zewnętrznym pierścieniu rozbiły się ze dwa albo trzy statki – morze jest teraz cholernie niespokojne. Tak, co nie, i nie wyważajcie zamkniętych drzwi – jeszcze zamek rozwalicie, a ja potem będę musiał go naprawiać. Przyszliście do Donalda, tak, co nie?";
			link.l1 = "I tobie miłego dnia, przyjacielu. Do niego samego. Ale, sądząc po tym, że drzwi są zamknięte, albo przeniósł się na inny statek, albo nie chce widzieć starych znajomych.";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "Ani jedno, ani drugie, ha-ha. Grinspie jest teraz na zewnętrznym pierścieniu, na ćwiczeniach.";
			link.l1 = "Ćwiczeniach? Naprawdę? On co, szykuje się do nowej wojny z Rivadosem?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "Ona tak naprawdę nigdy się nie skończyła, "+pchar.name+". Ostatnio po prostu bójek jest tu znacznie mniej niż dawniej. Ale i tak w tawernie u Sancho co i rusz ktoś komuś daje w mordę... a czasem i nóż pójdzie w ruch.";
			link.l1 = "Hmm, wydaje mi się, że wcześniej członkowie klanów nie pojawiali się w tawernie.";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "No, trochę się zmieniło od waszego wyjazdu z Wyspy. Donaldowi i Eddiemu udaje się trzymać ludzi w ryzach. Na razie. Ale kto wie, co będzie jutro? To właśnie stary Donnie wszystko to zaczął...";
			link.l1 = "Z takim trudem powstrzymałem rzeź na Wyspie, żebyście tu znowu bawili się w żołnierzyki? I od dawna on siedzi na zewnętrznym pierścieniu?";
			link.l1.go = "Schmidt_5";
			link.l2 = "Ćwiczenia to dobra rzecz, tak, co nie, ale czy nie zaszkodzą już i tak kruchemu rozejmowi? I jak długo Greenspy już ćwiczy chłopaków, tak, co nie?";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "Trzeci dzień już. Powinien wrócić jutro przed południem. Z takim zapałem, jak oni tam czyszczą muszkiety, to do jutra nie będzie już z czego strzelać! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "Trzeci dzień już. Ma wrócić jutro przed południem. Z takim zapałem, jak oni tam czyszczą muszkiety, to do jutra nie będą mieli już z czego strzelać! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "Czy moja kajuta na 'Ceres Smithy' jest jeszcze wolna? Czy może już ktoś się tam wprowadził?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "Tam wszystko jest tak samo, jak wtedy, gdy byłaś tam ostatni raz. Nawet drzwi nie otwieraliśmy. Zamka przez ten cały czas, prawdę mówiąc, też nie czyściliśmy ani nie smarowaliśmy. Więc jeśli nagle trzeba będzie go wyłamać – tylko powiedzcie.";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "Na pewno. Dzięki, Jurgen.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "Naprawdę wszystko zostało po staremu. Wszystko jest na swoim miejscu – jakbym stąd wcale nie odchodziła... To tutaj spotkaliśmy się po raz pierwszy, "+pchar.name+". Pamiętasz?";
			link.l1 = "Jeszcze jak! Tak załatwiłaś tamtych dwóch, że pomyślałem – oby i mnie nie spotkał ich los!";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "Wszystko przecież było zupełnie inaczej, tak, co nie! Ty dosłownie wyrwałeś mnie z łap śmierci!";
			link.l1 = "Wydaje się, że to spotkanie było mi przeznaczone przez sam los.";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "Naprawdę tak myślisz, kochanie?";
			link.l1 = "Oczywiście, kochanie. I od tamtej pory każdego dnia dziękuję jej za to, że zaprowadziła mnie prosto na 'Ceres Smithy'.";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... Powiedz, co pomyślałeś, kiedy zobaczyłeś mnie po raz pierwszy?";
			link.l1 = "No... Pamiętam tylko, że kiedy to się stało, serce jakby chciało wyrwać się z piersi. Byłaś taka...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "Jaka?";
			link.l1 = "Nie przypominasz żadnej z tych, które znałem wcześniej. Twoja gracja, głos... i ten czerwony kaftan. Nie miałem najmniejszych szans się oprzeć. Przyznam, zawsze mnie to ciekawiło: dlaczego właśnie on? Dlaczego czerwony kaftan, a nie sukienka, koszula czy gorset?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "Znalazłam go, gdy miałam dziewięć lat, na zewnętrznym pierścieniu. Wtedy uwielbiałam tam spacerować – odkrywać wszystko, co nowe, znajdować rzeczy, których nie było na wyspie, zwłaszcza książki. Strasznie chciałam go przymierzyć, ale wtedy mogłam się w nim co najwyżej utopić. Schowałam go tam, gdzie wszystkie swoje znaleziska – w jednym z wronich gniazd wystających z wody.";
			link.l1 = "A kiedy stał się dla ciebie odpowiedni, przypomniałaś sobie o nim?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "Kilka lat temu, włócząc się po pierścieniu, natknęłam się na książkę o dzielnym kapitanie w czerwonym mundurze. Niczego się nie bał, walczył z setkami wrogów dla miłości swojego życia i nie znał strachu. Wtedy po raz pierwszy go sobie wyobraziłam. On dodaje mi odwagi...";
			link.l1 = "I niepowtarzalny urok, kochanie! Ale wiesz co? W tej chwili pragnę tylko jednego... zdjąć go z ciebie...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "No to na co czekasz, mój dzielny kapitanie?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "Dzień dobry, kochany. Narwale właśnie wróciły na 'Esmeraldę' i 'San Gabriel', a Donald z nimi. Widziałam go w jednej z szalup, tak, co nie?";
			link.l1 = "Dzień dobry, dzień dobry... Przyznam, po takiej nocy spałabym do południa, a ty już na nogach, śmigasz.";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "Wczoraj rozmawialiśmy o kaftanie i o bocianim gnieździe, gdzie kiedyś go schowałam... I nagle ogarnęła mnie taka tęsknota za tamtymi czasami, kiedy chowałam się tam przed wszystkimi, żeby w ciszy czytać książki o wielkim świecie... Nie wytrzymałam i popłynęłam tam. Kiedyś mogłam tam siedzieć godzinami, ale dziś... po prostu przywitałam tam świt. I zrozumiałam: najbardziej na świecie chcę być przy tobie.";
			link.l1 = "A ja z tobą, "+npchar.name+". No to idziemy   do Donalda? Będziemy mieli o czym pogadać, tak, co nie?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", Mary, miło cię widzieć! Już mi doniesiono o twojej wczorajszej wizycie. Myślałem, żeby sam zajrzeć do ciebie na 'Ceres Smithy', ale wyprzedziłaś starego. Ech, chciałbym mieć twoje lata...";
			link.l1 = "No, masz tej swojej energii aż nadto, jak już zdążyliśmy się przekonać. Jak poszły ćwiczenia?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "Lepiej, niż się spodziewałam. Przećwiczyliśmy abordaż na okręty wroga, szturmowanie kajut... No, naprawdę się postaraliśmy. Jasne, trochę poganiałam chłopaków, ale wyszło im to tylko na dobre. Dawno nie rozprostowywali kości, oj dawno, ha-ha.";
			link.l1 = "I co takiego, pozwól zapytać, skłoniło cię do takich wyczynów? Znudziło ci się na Wyspie, tak, co nie?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "Hmm, słyszę nutkę niezadowolenia w twoim głosie, "+pchar.name+". Mogę, oczywiście, zrozumieć jego powody...";
			link.l1 = "Naprawdę, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "Musiałeś się nieźle nabiegać po tych zgniłych wrakach, żebyśmy się tu nawzajem nie pozabijali – nie zapomniałem o tym. Nikt o tym nie zapomniał.";
			link.l1 = "I tak mi się odwdzięczyłeś za moje starania! Widać, mówią prawdę – prawdziwego wojownika świat tylko przygniata.";
			link.l1.go = "Grinspy_5";
			link.l2 = "I trzeba przyznać, na twoją rozwagę liczyłem znacznie bardziej niż na rozsądek piratów czy rivaudos, tak, co nie?";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "Pozwól mi dokończyć. Tak, co nie, udało nam się zachować pokój – ale nasze sprzeczności wcale nie zniknęły. Przynajmniej jeśli chodzi o tych czarnych bezbożników. W zeszłym tygodniu podczas bójki w tawernie zginął jeden z narwali. Ale i my nie pozostaliśmy im dłużni...";
			link.l1 = "Tak, tak, właśnie tak to się zwykle zaczyna.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = "Pozwól mi dokończyć. Tak, co nie? Udało nam się zachować pokój – ale nasze sprzeczności wcale nie zniknęły. Przynajmniej jeśli chodzi o czarnych bezbożników. W zeszłym tygodniu podczas bójki w tawernie zginął jeden z narwali. Ale i my nie pozostaliśmy im dłużni...";
			link.l1 = "Tak, tak, właśnie tak to się zwykle zaczyna.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "Mylisz się w dwóch rzeczach, "+pchar.name+". Po pierwsze, to się nie zaczyna, tylko trwa dalej. Jeśli naiwnie myślałeś, że to już koniec, to się mylisz. Po drugie, nie jestem świętoszkiem, żeby nadstawiać drugi policzek. Murzyni znowu się rozzuchwalili i wcale mi się to nie podoba. Dexterowi, swoją drogą, też nie, ale on uważa się za wielkiego polityka i woli trzymać się z dala od konfliktu. Dlatego po namyśle wybrałem, moim zdaniem, najbardziej... bezbolesny sposób, żeby zachować kruchy pokój.";
			link.l1 = "Postanowiłeś nastraszyć rivaados swoimi naukami?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "Jakieś dwa tygodnie temu do zewnętrznego pierścienia przybił angielski galeon z ładunkiem wojskowym – było tam dosłownie wszystko... Ale najważniejsze to pięćdziesiąt nowych muszkietów i porządny proch. No i szalupy... Farba na nich jeszcze nie zdążyła wyschnąć! Stare już się całkiem rozleciały, a po sztormach niewiele łodzi zostaje w całości, powiem ci...";
			link.l1 = "I wszystko to stało się własnością narwali?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "Może i podzieliłbym się z Admirałem, ale skoro on uważa się za najmądrzejszego, to ja też nie chcę wyjść na głupca. Mój plan, tak na marginesie, zadziałał, no właśnie.";
			link.l1 = "Czarny Eddie przysłał ci list, w którym obiecał już więcej nie wbijać noży w twoich ludzi?";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "Czarny Eddie kazał swoim czarnuchom siedzieć cicho. Obawiałem się, że pod moją nieobecność sprowokują więcej problemów — ale stało się dokładnie odwrotnie: rivados siedzą cicho i trzymają się z dala zarówno od moich ludzi, jak i od cywilów, których też wcześniej zaczepiali. Murzyni to murzyni — rozumieją tylko siłę. Tak mówił Alan, i niech ten statek pójdzie na dno w tej chwili, jeśli się mylił!";
			link.l1 = "A jeśli za jakiś czas znowu zaczną się buntować, to dla postrachu zasypiesz 'Furię' i 'Protektora' ołowianym deszczem ze swoich nowych muszkietów, tak, co nie?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "Pomysł jest śmiały i zuchwały, ale myślę, że do tego nie dojdzie. Może tylko zrobimy wrażenie, że szykujemy rajd na ich statki – a potem Leighton zbierze się w sobie i jednak się wtrąci. Choć trochę mu odbiło, to jednak facet jest przewidujący. Zniszczenie ani naszego klanu, ani czarnych nie leży w jego interesie – trzy mniej więcej równe ośrodki siły zapewniają jakiś tam balans. Wystarczy, że jeden z nich padnie – i wszystko się posypie. Jestem pewna, że on to rozumie – ale z jakiegoś powodu to ja muszę odwalać za niego robotę.";
			link.l1 = "Może do niego zajrzę, póki tu będziemy – jeśli oczywiście nie zacznie swoich nauk w odpowiedzi, ha-ha.";
			link.l1.go = "Grinspy_12";
			link.l2 = "Postaram się do niego zajrzeć przy okazji – pogadać o tym. Może posłucha, tak, co nie?";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "Jeśli ktoś zdoła go przekonać, żeby trzymał czarnych w ryzach, to właśnie ty, "+pchar.name+". Jednak po waszych twarzach widzę, że nie przyszliście tu po to, żeby pogadać o polityce. Mówcie, co was sprowadza.";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "Moi rodzice, Donald.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "Nie do końca rozumiem, czego ode mnie chcesz, Mary.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "Opowiedz mi o nich, proszę cię, tak, co nie? Przecież ich znałeś! Już kiedyś cię o nich pytałam, ale wtedy nie chciałeś odpowiedzieć na moje pytania...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "I dlatego postanowiłaś przyprowadzić tu Charles’a, ha-ha-ha! No nieźle, dziewczyno, niech mnie piorun trafi! Jeśli nie rozmawiałem z tobą o twoim ojcu i matce, to tylko dlatego, że nigdy ich nie znałem, ot i wszystko!";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "Ale przecież jesteś najstarszym członkiem naszego klanu, tak, co nie! Byłeś tu, odkąd tylko pamiętam...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "Pojawiłem się na Wyspie nieco mniej niż dwadzieścia lat temu, już po twoich narodzinach. Byłaś wtedy zupełnym maluchem, biegającym i czołgającym się pod stołami i taboretami, nie dającym spokoju Erikowi Udetowi... Oczywiście zapytałem go, skąd się tu wzięło takie niespokojne stworzenie – i usłyszałem, że urodziłaś się na Wyspie kilka lat wcześniej. Nie powiedział nic ani o twoim ojcu, ani o twojej matce. A jeśli nawet coś wspomniał – to albo nie zapamiętałem, albo już zapomniałem...";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = "Tyle lat minęło... Rozumiem, Donald, tak, co nie.";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = "Szkoda, że nie ma tu z nami Erika – on trafił w to miejsce jeszcze na długo przede mną. A tak przy okazji, kiedy opowiadał o twoich kolejnych wybrykach, często wspominał Aurélie Bertin. Ta staruszka była w tobie zakochana po uszy, to akurat dobrze pamiętam... Nigdy się nad tym nie zastanawiałem, ale myślę, że kiedy się urodziłaś, ona już była na Wyspie. Może uda jej się ci pomóc?";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = "Może być. Dobry powód, żeby ją odwiedzić – nawet nie pamiętam, kiedy ostatni raz do niej zaglądałam. Niezręcznie wyszło, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "Nie sądzę, żeby była na ciebie zła. Ale nie dręcz jej za bardzo – słyszałam, że się rozchorowała. Jeszcze czego brakowało...";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "Milcz, Donald, jeszcze kłopotu narobisz! Aurélie wszystkich nas przeżyje, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "Chodź, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "Na razie, "+npchar.name+". Do zobaczenia wkrótce.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "Panie miłosierny, mało mi serce z piersi nie wyskoczyło. Można tak ludzi straszyć?..";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "Jillian! Nie spodziewałam się cię tu zobaczyć, tak, co nie? Co ty tu robisz? I gdzie jest Aurélie?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "I tobie cześć, Mary. I wam, "+pchar.name+". Oreli jest chora, nie wiedziałaś? Opiekuję się nią na prośbę brata Juliana. Przekazuje mi mikstury, którymi ją poię, ale... wydaje się, że niewiele pomagają. Teraz jest w kajucie na rufie, śpi. Zaprowadziłam ją tam, żeby tu posprzątać.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "Dowiedzieliśmy się dopiero dzisiaj, tak, co nie. Donald nam powiedział. Jak ona?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "Źle. Skarży się na osłabienie, prawie nie wstaje z łóżka. Czasem bełkocze coś niewyraźnie, jakieś bzdury... Już tyle historii wysłuchałam o dawnych czasach, że straciłam im rachubę.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "Hmm, właśnie po taką historię tu przyszliśmy. Mam nadzieję, że nie odmówi nam rozmowy...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "Czy to naprawdę aż tak konieczne, Mary? Nie sądzę, żeby warto było ją niepokoić w takim stanie.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "Chodzi o moich rodziców. Aurélie mogła ich znać. To dla mnie bardzo ważne, Gillian, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "Na wyspie nie ma żadnego lekarstwa, które mogłoby poprawić jej stan?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "Brat Julian przygotowuje dla niej nalewki. Ale pomagają tylko na jakiś czas. I tak, ona odmawia ich picia, więc muszę jej je niemal siłą wlewać do ust. Czasem boję się, że może się nimi zwyczajnie zachłysnąć – trzeba ją jeszcze zmusić, żeby wszystko przełknęła...";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "Biedna Aurélie! Naprawdę nikt na Wyspie nie może jej pomóc?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = "Sama przecież wiesz, że nie ma tu porządnego medyka. Tak, co nie?   I czym ty tu możesz pomóc?   Starość, jak wiadomo, nikogo nie oszczędza...";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", może przyprowadzić kogoś z naszego statku?";
			link.l1 = "Obawiam się, "+npchar.name+", tutaj nie potrzeba chirurga okrętowego, tylko doświadczonego medyka.";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "Teraz jestem gotowa uwierzyć nawet w magię, jeśli to pomoże, tak, co nie.";
			link.l1 = "Hmm... Magię? Może warto zwrócić się do Chimisetu...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "Chimisetu? Czarownikowi czarnych? "+pchar.name+", wy tak na serio?";
			link.l1 = "Jak nigdy. Czy jest czarny, czy biały – to ostatnia rzecz, która mnie teraz obchodzi. Kto jeszcze może pomóc Aurélie – nie wiem. Myślę, że wy też nie. A skoro tak – zejdźcie mi z drogi i nawet nie próbujcie mi przeszkadzać.";
			link.l1.go = "Jillian_16";
			link.l2 = "Bardziej niż bardzo. Aureliemu nie pomagają ani lekarstwa, ani modlitwy brata Juliana. Chimiset to nasza ostatnia nadzieja.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "Nie wierzę własnym uszom! Ale to przecież... bezbożnik!";
			link.l1 = "A to jest umierająca kobieta, która jest o krok od tego, by zapomnieć, jak się nazywa. Tak, co nie, on jest czarownikiem, ale słyszałam, że oni potrafią naprawdę wiele, bardzo wiele. I jeśli on zdoła przywrócić jej rozum – czy to teraz naprawdę takie ważne, jakiej jest wiary?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "Nie wierzę własnym uszom! Ale to przecież... bezbożnik!";
			link.l1 = "A to - umierająca kobieta, która jest o krok od zapomnienia własnego imienia. Tak, co nie, on jest czarownikiem, ale słyszałam, że oni potrafią naprawdę wiele, bardzo wiele. I jeśli on zdoła przywrócić jej rozum - czy to teraz naprawdę takie ważne, jakiej jest wiary?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", posłuchaj, sama również cenię Aurélie... Bóg mi świadkiem — robię wszystko, co w mojej mocy, by ulżyć jej w cierpieniu! Ale czy naprawdę zamierzasz pozwolić czarnemu heretykowi odprawić w tej kajucie jakiś swój rytuał? A co, jeśli podczas niego spali statek albo zechce złożyć kogoś w ofierze?";
			link.l1 = "Na to nie pozwolimy, "+npchar.name+", zapewniam was.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "A ja zapewniam was oboje, że jeśli ktoś się o tym dowie... Czy wy w ogóle rozumiecie, co tu się zacznie? Pozostałym mieszkańcom to się nie spodoba, a już narwalom – w szczególności!";
			link.l1 = "Ma pan rację. Nie trzeba tu ciągnąć Chimiseta, tylko zaprowadzić do niego Orelie.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "Nie widzieliście jej – ta staruszka ledwo trzyma się na nogach. To będzie cud, jeśli nie wypadnie za burtę!";
			link.l1 = "No cóż, czasem pozostaje nam tylko liczyć na cud. Tak, co nie, i, Jillian...";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "Co jeszcze?";
			link.l1 = "Mam nadzieję, że zachowacie to w tajemnicy. Jesteście mądrą dziewczyną i dobrze to oceniliście... Zamieszki na Wyspie mogą łatwo przerodzić się w rozlew krwi, a przecież nikomu na tym nie zależy, tak, co nie?";
			link.l1.go = "Jillian_22";
			link.l2 = "Nikomu ani słowa, jasne? Zaufaliśmy wam – nie każcie nam tego żałować. Myślę, że rozumiecie, że jeśli nasz plan przestanie być tajemnicą, na Wyspie zacznie się taka rzeź, jakiej jeszcze nie widziała.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "Dobrze. Ale wtedy zróbcie tak, żeby nikt nie widział, jak ciągniecie ją na 'Protektora'... Inaczej będę musiała odpowiadać na niewygodne pytania.";
			link.l1 = "Oszczędzimy wam kłopotliwych odpowiedzi. Zrobimy to w nocy.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "Dobrze. Ale wtedy zróbcie tak, żeby nikt nie widział, jak ciągniecie ją na 'Protektora'... Inaczej będę musiała odpowiadać na niewygodne pytania.";
			link.l1 = "Na to nie pozwolimy. Zrobimy to w nocy.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "Przyjdźcie po północy. Ona tu będzie. I na miłość boską, bądźcie ostrożni.";
			link.l1 = "Możesz się nie martwić, "+npchar.name+", będziemy wyjątkowo uważni.";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "Przyjdźcie po północy. Ona tu będzie...";
				link.l1 = "Dobrze.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "Orelia jest gotowa. Możecie ją prowadzić.";
				link.l1 = "Świetnie. To w drogę.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "Młodzi ludzie, a dokąd... dokąd my idziemy?! Przecież to statek Rivadose! Gdzie jest Erik?!";
			link.l1 = "Eric zaprzyjaźnił się z Eddiem Blackiem, tak, co nie?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "Co ty wygadujesz, chłopcze! Tak, co nie, Erik nie znosi Murzynów nawet na krok!";
			link.l1 = "No nieźle! To chodźmy i zapytajmy go, co do diabła on tu właściwie robi!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "Patrzcie tylko, kto do nas zawitał! "+GetFullName(pchar)+" we własnej osobie! Cieszę się, że widzę mojego białego brata, ha-ha! Opowiadaj, po co przyszedłeś!";
			link.l1 = "I tobie cześć, "+npchar.name+". Chciałbym wpaść po prostu na kufel rumu, tak, co nie, ale obawiam się, że mam do ciebie, a właściwie do Chimiset, pilną sprawę.";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "Jesteśmy ci winni przysługę nie do spłacenia, mój przyjacielu. Zrobimy wszystko, co w naszej mocy.";
			link.l1 = "Dobrze, jeśli tak. Bo nie mam już na kogo liczyć.";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "Z którą z tych dam potrzebujesz pomocy, "+pchar.name+"?";
			link.l1 = "Nie wiem, mówisz poważnie czy żartujesz, "+npchar.name+", ale nie jest mi do śmiechu. Pomocy potrzebuje Aurélie, oczywiście.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "Erik! ERIK! Pokaż się, stary łotrze! Co to za wybryki?! Natychmiast przynieś tu swój chudy tyłek!";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "Więc to jednak prawda... Moi ludzie donosili mi, że ta rozwalina ma nie po kolei w głowie. Teraz widzę – mówili prawdę. Ale nie do końca rozumiem, czego ty chcesz od Rivadose...";
			link.l1 = "Pozwól mi porozmawiać z Chimisetem, a wszystko zrozumiesz...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "Mów, mój drogi przyjacielu. Jestem gotów uważnie cię wysłuchać.";
			link.l1 = "Będę mówił krótko, Chimiset. Oreli posiada informacje, których potrzebujemy razem z Mary. Jednak ze względu na jej stan, spowodowany, jeśli dobrze rozumiem, po prostu wiekiem, nie możemy ani uzyskać od niej tych wiadomości, ani mieć pewności, że okażą się prawdziwe. Słyszałem o cudach, do których zdolni są zarówno indiańscy, jak i afrykańscy szamani – dlatego właśnie przyszedłem prosić cię o pomoc, Chimiset.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "Słyszałem cię, mój przyjacielu. Szamani mają moce tajemnicze i mistyczne, często niepojęte i niepodlegające ludziom z zewnątrz, nawet własnym współplemieńcom, nie mówiąc już o białych. Jedni nazywają to czarami, inni - cudem. Naprawdę potrafimy wiele – ale nikt nie zdoła zmusić rzeki, by popłynęła pod prąd... Ani jej zatrzymać – też nie.";
			link.l1 = "Co masz na myśli, Chimiset?";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "Mówię o rzece czasu, mój przyjacielu. Albo o rzece życia – jak wolisz. Widzisz, masz całkowitą rację – źródło tej biedy tkwi właśnie w jej latach, a nie w czymkolwiek innym.";
			link.l1 = "Słyszałem o tym trochę. Wiem tylko, że to wcale nie taki rzadki problem, tak, co nie?";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "Masz rację. Ludzi w jej wieku często porywa w doliny snów, a czasem — koszmarów. Wracają stamtąd, tylko po to by znów odejść — nie z własnej woli, lecz przez nieznane siły, które ich tam ciągną. Z czasem choroba się nasila — i wtedy człowiek nie pamięta już ani siebie, ani swoich przyjaciół.";
			link.l1 = "Czyli nic nie możesz z tym zrobić, tak, co nie?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "Wygnać chorobę – nie. Na to mnie nie stać. Ale mogę zrobić coś innego...";
			link.l1 = "Co dokładnie?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "W chwili, gdy ta kobieta odzyska przytomność, odprawię szybki rytuał, do którego wcześniej się przygotuję...";
			link.l1 = "Czy on, jeśli nie zatrzyma, to chociaż spowolni rozwój choroby?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "Nie do końca. To zmusi ją do wezwania wszystkich sił życiowych, żeby jak najdłużej zachować zdrowy rozsądek.";
			link.l1 = "Jak długo to znaczy jak długo?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "To nie zależy od rytuału, tylko od człowieka. Jednemu wystarczy sił na tydzień, innemu – na miesiąc... Słyszałem o mężczyźnie, który zachował zdrowy rozum i pamięć przez ponad rok... I kiedy już wszyscy myśleli, że został wyleczony, choroba wróciła – i zabrała go tej samej nocy.";
			link.l1 = "Żeby dowiedzieć się tego, co nam trzeba – godzina wystarczy. Kiedy będziesz mógł przeprowadzić rytuał, Chimiset?";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "Zabiorę tę kobietę od razu, zaprowadzę ją do ładowni — tam urządzono sanktuarium... właśnie na takie sprawy. Dalej wszystko będzie zależało od tego, kiedy wróci do normalnego stanu... Ale myślę, że do rana się uporamy.";
			link.l1 = "W takim razie nie będę wam przeszkadzać. I niech ci pomoże... twój Bóg, Chimiset.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "Dzięki! Pomóż mi zaprowadzić białą kobietę do ładowni.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "Wszystko się udało, biały bracie. Udało nam się...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "O, "+GetFullName(pchar)+"! Nie wiedziałam, że wróciliście z Mary na Wyspę! Co za miłe spotkanie!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Chimiset, dziękuję ci! Nawet nie wiem, jak ci się odwdzięczyć...";
			link.l1.go = "Chimset_14";
			link.l2 = "No proszę, Chimiset – dałeś radę! No, ja w ciebie wcale nie wątpiłam...";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "Wszyscy Rivadose są ci dozgonnie wdzięczni, mój przyjacielu! Drzwi 'Protektora' są dla ciebie zawsze otwarte.";
			link.l1 = "Mam nadzieję, że nie będę musiał was już więcej niepokoić... Mary, Aurélie, musimy wracać na 'Plutona'.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "Wszyscy Rivadoczy są ci dozgonnie wdzięczni, mój przyjacielu! Drzwi 'Protektora' zawsze stoją dla ciebie otworem.";
			link.l1 = "Mam nadzieję, że nie będę musiał już was niepokoić... Mary, Aurelie, musimy wracać na 'Plutona'.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "Już nawet nie pamiętam, jak opuściłam swoją kajutę... Ech, ta starość – pamięć mam do niczego, tak, co nie? ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "No proszę, młoda damo, a co to pani zapomniała w mojej kajucie?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "Orelie, ja...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "Oreli, poprosiłam ją, żeby tu posprzątała, kiedy cię nie było. Nie ma sensu, żebyś z chorymi kolanami się schylała...";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "Posprzątać?! Ty...";
			link.l1 = "Dżillian, dziękuję ci za pomoc. (szeptem) Udało nam się. Chimiset dał radę.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "Nie wierzę...";
			link.l1 = "Jak widzisz. A teraz, proszę, pozwól nam porozmawiać.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "No cóż, młodzi ludzie, dziękuję, że odprowadziliście staruszkę. Obawiam się, że wkrótce już w ogóle przestanę wychodzić na zewnątrz. Moje nogi, moje nogi...";
			link.l1 = "Jeśli pozwolisz, "+npchar.name+", zostaniemy u was na chwilkę – naprawdę niedługo. Mamy z Mary do was bardzo ważną sprawę.";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "Jeśli znowu nie będę musiała włóczyć się na inny statek, to pomogę, jak tylko będę mogła. Słucham was.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "Oreli, chcę, żebyś opowiedziała mi o moich rodzicach. I o dniu, kiedy się urodziłam. To przecież stało się tutaj, na Wyspie, tak? Donald twierdzi, że tak było, ale przecież wtedy go tu jeszcze nie było, więc nie może tego wiedzieć na pewno. Ty jednak mieszkasz tu znacznie dłużej od niego, tak, co nie! Przecież ponad dwadzieścia lat, prawda?";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "Cicho, cicho, dziewczyno, nie trajkocz tak, proszę cię! Bo nie nadążam za tobą...";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "Rozumiem, tak, co nie. Dobrze, spróbujmy jeszcze raz...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "Nie trzeba, Mary, jeszcze nie jest ze mną tak źle, ha-ha... Usłyszałam, co mi powiedziałaś. Ale, skoro naprawdę mieszkam na Wyspie najdłużej ze wszystkich, mam nadzieję, że podejdziesz do mojego wieku z szacunkiem i wyrozumiałością...";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "Oczywiście, Aurélie! Jak mogłaś pomyśleć inaczej?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "Ech, patrzę na tę dzisiejszą młodzież i... nie, nie, my tak się nie zachowywaliśmy wobec starszych. Ale ciebie to oczywiście nie dotyczy. Chciałam tylko powiedzieć, że będzie nam łatwiej, jeśli będę odpowiadać na twoje pytania po kolei, a nie na wszystkie naraz...";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "Rozumiem, Aurélie. Jak sobie życzysz, tak, co nie. Czyli byłaś na Wyspie, kiedy się urodziłam? Jeśli to rzeczywiście stało się tutaj, oczywiście...";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "Na Wyspę trafiłam w 1633 roku, ten dzień czasem śni mi się w koszmarach. Sztorm, nasz 'Reprisal' – fluita, na której płynęliśmy z mężem do Florydy – miota się po falach, aż strach, że zaraz wywróci się do góry stępką, a my odmawiamy wszystkie znane modlitwy i wymyślamy nowe... A potem trzask i...";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "Więc trafiłaś tu pięć lat przed moim urodzeniem, tak, co nie.";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "Mniej więcej tak. Wtedy wszystko wyglądało tu trochę inaczej – 'San Jeronimo' jeszcze trzymał się na wodzie, zewnętrzny pierścień statków był mniejszy może o połowę, jeśli nie o dwie... I to jeszcze nie wszystkie statki wciąż unoszą się na wodzie! Powiem wam jedno, młodzi ludzie, jeśli spojrzycie w pogodny dzień na dno – przerazicie się, ile tam wraków statków leży...";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "Interesuje nas statek, na którym tutaj przypłynęli moi rodzice. Ze mną... albo beze mnie?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "Z tobą, dziewczyno, z tobą.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "Czyli jednak urodziłam się na Wielkiej Ziemi?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "Nie, miałam na myśli 'z tobą' w trochę innym sensie. Byłaś w brzuchu swojej matki i urodziłaś się tydzień później.";
			link.l1 = "Według ciebie, Aurélie, to jest zabawne?";
			link.l1.go = "Oreli_32";
			link.l2 = "Ale z wiekiem nie stracił pan poczucia humoru, Aurélie.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "No, z siebie śmieję się dużo częściej niż z innych. Przepraszam, Mary, nie chciałam cię urazić.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "No, z siebie śmieję się znacznie częściej niż z innych. Przepraszam, Mary, nie chciałam cię urazić.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "Wszystko w porządku, Aurélie. Proszę – mów dalej, tak, co nie? Co stało się z moimi rodzicami po moim urodzeniu?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "Po tym? Moja droga, to cud, że oboje w ogóle tego dożyli! Jakaż to była straszna burza tamtej czerwcowej nocy! Kiedy rano szalupa dostarczyła twoją matkę na wewnętrzny pierścień, mało kto wierzył własnym oczom — że kobieta w zaawansowanej ciąży, która miała lada moment rodzić, przetrwała takie potworne rozbicie statku. Biedna Teresa, pamiętam to jak dziś...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "Teresa? Tak miała na imię?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "Tak, tak się przedstawiła – i to było chyba prawie wszystko, co powiedziała. Pod koniec dnia zapadła w majaczenie, w którym trwała aż do samych narodzin. Nikt nie był pewien, czy zdoła urodzić, a tym bardziej wszyscy wątpili, że dziecko przyjdzie na świat żywe – po tym wszystkim, co przeszła. Ale Teresa dała radę. Dała radę – i wyzionęła ducha. Niech Bóg ma jej duszę w swojej opiece...";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "Mama zginęła, a ja zostałam z ojcem? Ale dlaczego wszyscy wtedy twierdzili, że wychowywał mnie Erik Udett? I...";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Mary, kochanie, przecież prosiłam... Nie zasypuj mnie tyloma pytaniami...";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "Wybacz, Aurélie, zapomniałam się, tak, co nie? Mój ojciec, on też przeżył katastrofę statku?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "Twój ojciec... Wiesz, niewiele mogę powiedzieć o twoim ojcu – poza tym, że nikomu nie życzyłabym takiego taty. Kilka dni po twoim narodzeniu zniknął, zostawiając cię na pastwę losu. Miałaś szczęście, że Erik miał tak dobre i łagodne serce – jak suchar namoczony w kubku grogu...";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "Powiedz chociaż, jak on się nazywał, tak, co nie!";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "O-och... Czy to był Jeffrey, czy John, niech mnie pamięć nie zawodzi...";
			link.l1 = "Czyli nie pamiętacie? Tak, co nie? "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "Wątpisz w moje słowa, młody człowieku?!";
			link.l1 = "Cicho, "+npchar.name+", spokojnie. Nie chciałem cię urazić. Po prostu wydawało mi się, że dość... dobrze pamiętasz tamte dni, i tyle.";
			link.l1.go = "Oreli_45";
			link.l2 = "Nie mam żadnych wątpliwości, "+npchar.name+". Po prostu staram się dobrze zapamiętać wszystkie szczegóły – nic więcej. Ale to całe zamieszanie trochę utrudnia sprawę.";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "Pamięć to wybredna dama, "+pchar.name+", dość wybredna. Zwłaszcza, kiedy minęło tyle lat. Trudno zapomnieć Teresę – przez cały tydzień patrzyłam na jej cierpienia! O-och, jakże mi jej było żal!";
			link.l1 = "A jej mąż, czy nie był przy niej?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "Pamięć to wybredna dama, "+pchar.name+", dość wybredna. Zwłaszcza, gdy minęło tyle lat. Trudno zapomnieć Teresę – przez cały tydzień patrzyłam na jej cierpienia! Ojej, jak bardzo było mi jej żal!";
			link.l1 = "A jej mąż, czy nie był przy niej?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "Bardzo rzadko. Prawie cały tydzień gdzieś znikał – szukał lekarstw i mikstur, których wtedy na Wyspie bardzo brakowało...";
			link.l1 = "Więc był dobrym mężem – skoro próbował pomóc żonie.";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "Mężem to on może i był dobrym. Przeciwnego nie twierdziłam, pozwolę sobie zauważyć. Nie próbuj mnie mącić, młodzieńcze!";
			link.l1 = "Nawet o tym nie myślałam, zapewniam, "+npchar.name+". Po prostu oczywiste jest, że nie macie o nim najlepszego zdania. I to, że nie pamiętacie jego imienia...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "Widziałam tego mężczyznę prawie przelotnie w ciemności kajuty 'Ceres Smithy', tam, gdzie teraz mieszka herr Jurgen. Przychodził tylko nocą, a jego twarz pamiętam bardzo niewyraźnie. Co do jego imienia – nikt go po imieniu nie nazywał, tylko po nazwisku. Kasper to, Kasper tamto...";
			link.l1 = "Rozumiem cię, "+npchar.name+". Czyli Mary się urodziła, a kilka dni później on zniknął bez śladu. Zabili go?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "Trudne pytanie, młody człowieku. Wie pan, w tym miejscu trudno cokolwiek utrzymać w tajemnicy – wszystko jest na widoku. Kiedy wybucha jakaś awantura – nawet na pokładzie statku – już następnego dnia wie o niej cała Wyspa.";
			link.l1 = "Nic dziwnego.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "Ciał zabitych nie zawsze się znajduje – doświadczeni gracze topią zwłoki, owijając ręce i nogi knypplami albo przywiązując do nich kule lub kamienie. A kraby na dnie kończą robotę. Jednak osobiste rzeczy zmarłych od razu albo po jakimś czasie znów wypływają na powierzchnię.";
			link.l1 = "Z dna?!";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "Oczywiście, że nie! Miałam na myśli, że wpadają w oko – pierścionek, pistolet z grawerem, szabla za zasługi... Rzadko kto o to pyta. Człowieka już nie wrócisz, a niepotrzebne konflikty nikomu nie są potrzebne.";
			link.l1 = "Czy Geoffrey albo John Casper mieli jakieś charakterystyczne rzeczy?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+", niech was Pan Bóg ma w opiece — ja nawet imienia jego nie mogę sobie przypomnieć, a wy mi tu takie pytania zadajecie! Jeśli coś było, to nie słyszałam, żeby ta rzecz trafiła do któregoś z mieszkańców Wyspy. W tamtych czasach pracowałam jako kelnerka w tawernie, i mało który plotek mnie omijał. Ale to wcale nie znaczy, że wiedziałam absolutnie wszystko.";
			link.l1 = "Kiedy mówią, że ludzie znikają bez śladu – zwykle mają na myśli, że zostali zabici. Ale w przypadku pana Kaspera wyraźnie nie jest pani tego pewna...";
			link.l1.go = "Oreli_54";
		break;

		case "Oreli_54":
			dialog.text = "Mówię tylko, że 'zniknął' wcale nie musi znaczyć 'zginął'. Zwłaszcza w tamtych latach, kiedy między Wyspą a Kubą regularnie kursowały tartany przemytników i paserów... Wie pan, nie pamiętam rysów jego twarzy, ale jego spojrzenie... To było spojrzenie człowieka, który nigdzie nie przepadnie. Albo przynajmniej święcie w to wierzy.";
			link.l1 = "Tartany, tartany... Nie ma rzeczy niemożliwych. Gdybyśmy znali jego imię, moglibyśmy przejrzeć archiwa kolonialne z tamtych lat. Ale byłoby o wiele łatwiej, gdybyśmy mieli typ i nazwę statku, na którym tutaj 'przybył'.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "A co się tak na mnie gapisz, chłopcze? Myślisz, że ja to sobie przypomnę?";
			link.l1 = "Mamy na to nadzieję, "+npchar.name+" - biorąc pod uwagę, jak wiele już nam opowiedzieliście.";
			link.l1.go = "Oreli_56";
			link.l2 = "Hm... Mam co do tego spore wątpliwości.";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "Może jeszcze zapytasz, ile miał dział i jakiego kalibru? Kochany, wiesz, ile tu przez te lata zatonęło statków? I myślisz, że wszystkie pamiętam? Poza tym, z tamtego okrętu uratowało się zaledwie kilku ludzi – nawet dnia się na wodzie nie utrzymał, co nie...";
			link.l1 = "Jasne... To zrozumiałe, minęło dwadzieścia lat. Dziękuję, że chociaż nie zapomnieliście tego, co nam wtedy opowiedziano.";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "Może jeszcze zapytasz, ile miał dział i jakiego kalibru? Kochany, wiesz, ile statków zatonęło tu przez te lata? I myślisz, że wszystkie pamiętam? Poza tym, z tego okrętu uratowało się zaledwie kilku ludzi – nawet dnia nie wytrzymał na powierzchni, co nie...";
			link.l1 = "Jasne... To zrozumiałe, minęło przecież dwadzieścia lat. Dziękuję, że chociaż to, co nam opowiedziano, nie zostało przez was zapomniane.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "Mam nadzieję, że nie żartujecie sobie i nie próbujecie śmiać się ze starej kobiety, której pamięć zamieniła się w sito.";
			link.l1 = "W żadnym razie, "+npchar.name+" . Naprawdę bardzo nam pomogliście. Wracajcie do zdrowia. No a my pójdziemy. ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "Czyli Teresa... Tak miała na imię. Moja biedna mama, tak, co nie...";
			link.l1 = "No, przynajmniej teraz wiemy, po kim masz tyle siły i uporu. Ciężarna kobieta na tonącym statku... Aż ciarki przechodzą na samą myśl o tym, tak, co nie?";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "Ale co ona robiła w takim stanie na tym statku, "+pchar.name+"?! Trzeba być szaloną, żeby się na coś takiego zdecydować!";
			link.l1 = "Odpowiedzieć na to pytanie może tylko twój ojciec – John, Jack, Jacob, Jasper, Jordan...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "Postanowiłeś przypomnieć sobie wszystkie angielskie imiona zaczynające się na „J”? Aurelie przecież wymieniła tylko Jeffreya i Johna, tak, co nie?";
			link.l1 = "Może po prostu nie pamiętała reszty, tak jak ja? No wiesz, wiek i te sprawy...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", myślisz...";
			link.l1 = "Nie ufałbym teraz jej pamięci całkowicie. Ale nawet jeśli tak, będziemy musieli sięgnąć nie do kolonialnych, a do marynarskich archiwów z 1638 roku, co jest o wiele trudniejsze: to przecież informacje poufne, zwłaszcza jeśli dotyczą oficerów. I bardzo wątpię, żeby zwykłemu marynarzowi pozwolono było wprowadzić żonę na pokład.";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "Z drugiej strony, znaleźć informacje o oficerze jest dużo łatwiej niż o zwykłym marynarzu.";
			link.l1 = "Jeśli zna się nazwę okrętu. Albo jego pełne imię. A nie 'Jeffrey czy John albo, w ostateczności, Jack...'. To i tak będziemy mieli szczęście, jeśli to był okręt wojenny. U handlarzy z listami załogi jest znacznie gorzej.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "Ale co my teraz zrobimy, "+pchar.name+"? Porozmawiać z Aurélie jeszcze raz? Przecież już wyciągnęliśmy z niej wszystko, co się dało, tak, co nie?";
			link.l1 = "Nie z Aurélie. Z Donaldem.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "A jak on nam pomoże? Przecież mówił, że w 1638 roku nawet nie było go w pobliżu Wyspy Sprawiedliwości, tak, co nie?";
			link.l1 = "Ale inne narwale tu były, tak, co nie?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "Nie bardzo rozumiem, do czego zmierzasz.";
			link.l1 = "Zobaczysz, kochana, zobaczysz. Jest jeszcze jedna nitka, za którą można pociągnąć. Chodź.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "O, znowu wy! No i jak wam idą poszukiwania?";
			link.l1 = "Cześć, "+npchar.name+".   Mogło być lepiej – na razie błądzimy jakby w tej jaskini pełnej tajemnic i zagadek. Ale czuję, że wyjście już blisko.";
			link.l1.go = "Grinspy_32";
			link.l2 = "I tobie dzień dobry, "+npchar.name+". Lepiej, niż mogłabym sobie wyobrazić na początku. Sytuacja... nie jest aż tak beznadziejna.";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "Cieszę się, że to słyszę. Naprawdę. Ale znowu oboje czegoś ode mnie chcecie, tak, co nie? Czego się dowiedzieliście?";
			link.l1 = "Mary urodziła się tutaj, na Wyspie, w czerwcu 1638 roku. Jej matka, Teresa, zmarła zaraz po porodzie. Ojciec – niejaki Casper – zapadł się pod ziemię kilka dni po narodzinach Mary. O nim nie wiemy nic, poza tym, że jego imię zaczyna się na 'J.'. Są tacy, którzy twierdzą, że nie został pożarty przez kraby na tutejszych mieliznach, tylko opuścił Wyspę na jednej z tartan przemytników...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "Cieszę się to słyszeć. Naprawdę. Ale znowu czegoś ode mnie chcecie, tak, co nie? Czego się dowiedzieliście?";
			link.l1 = "Mary urodziła się tutaj, na Wyspie, w czerwcu 1638 roku. Jej matka, Teresa, zmarła zaraz po porodzie. Ojciec – niejaki Casper – przepadł bez wieści kilka dni po narodzinach Mary. Nic o nim nie wiemy, poza tym, że jego imię zaczyna się na „J”. Niektórzy twierdzą, że nie został pożarty przez kraby na tutejszych mieliznach, tylko opuścił Wyspę na jednej z tartan przemytników...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "I zostawił córkę? Dziwne zachowanie.";
			link.l1 = "Tak właśnie jest. Ale nikt, oprócz tego całego pana J., nie potrafi tego wyjaśnić.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "Myślicie, że on jeszcze żyje? I dlatego go szukacie?";
			link.l1 = "Nie tylko o to chodzi. Chcemy się dowiedzieć, kim był, jak żył. Dla Mary to bardzo ważne.";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "Hmm, rozumiem. I przykro mi, że właściwie nie mogę wam za bardzo pomóc...";
			link.l1 = "Właściwie, możesz. Powiedz, narwale przecież prowadzą jakieś zapiski o statkach, które zginęły przy Wyspie?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "Nie do końca rozumiem, co masz na myśli, "+pchar.name+".";
			link.l1 = "Grinspie, Grinspie... Nie zapominaj, że wciąż grzejesz tyłek w tym fotelu tylko dzięki mnie. Więc bądź łaskaw – nie wystawiaj mojej cierpliwości na próbę.";
			link.l1.go = "Grinspy_38";
			link.l2 = "Jestem pewna, że rozumiesz, Donaldzie. I w imię naszej przyjaźni nie będziesz kręcił, tak, co nie?";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "Hm...";
			link.l1 = "Do zewnętrznego pierścienia co jakiś czas przybijają statki. Niektóre od razu idą na dno, inne przez jakiś czas utrzymują się na wodzie – wtedy są przeszukiwane i zabiera się z nich wszystko, co cenne. Nie wiem, jak to jest z rivaudos, ale wątpię, żeby narwale bili się o każdą znalezioną na pokładzie błahostkę – raczej wszystko wrzucają do wspólnego kotła, potem robią spis wszystkiego, a dopiero później następuje podział łupów.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "Hmm...";
			link.l1 = "Do zewnętrznego pierścienia co jakiś czas przybijają statki. Niektóre od razu idą na dno, inne przez jakiś czas utrzymują się na powierzchni – wtedy są przeszukiwane i zabiera się z nich wszystko, co cenne. Nie wiem, jak to jest z rivaudos, ale wątpię, żeby narwale walczyli o każdą znalezioną na pokładzie błahostkę – raczej wszystko wrzucają do wspólnego kotła, potem robi się spis wszystkiego, a dopiero później następuje podział łupów.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "Nie jesteś głupi, "+pchar.name+". W przeciwieństwie do wielu tutaj. Tak, mniej więcej właśnie tak to wygląda. Osobiście nie znoszę tej papierkowej roboty, ale tak było już za czasów Alana Milrowa i tych, którzy dowodzili klanem 'Narwal' przed nim. Sporządzamy takie zapisy – i co więcej: odnotowujemy nawet te statki, do których pierwsi dotarli Rivadose lub piraci. Ale w takich przypadkach, rzecz jasna, nie wiemy, kto i co było na pokładzie...";
			link.l1 = "Sądząc po tym, że rodziców Mary przywieziono po katastrofie statku na 'Ceres Smithy', to właśnie narwale znaleźli ich statek. A więc powinna być odpowiednia wzmianka.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "Może i tak. Nie mogę powiedzieć na pewno. I nie będę w stanie.";
			link.l1 = "Teraz to już nie rozumiem, co masz na myśli, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "Dzienniki strat zatopionych statków. Kiedy Leighton Dexter został admirałem po odejściu Dodsona, zabrał nam te dokumenty.";
			link.l1 = "Po prostu wziął i zabrał? I ty nic nie powiedziałeś?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "No po pierwsze, był całkiem uprzejmy. Po drugie, obiecał je wkrótce oddać. A po trzecie... na co mi, do diabła, te papiery?";
			link.l1 = "Nie najgorsze te notatki, tak, co nie?";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "Mówię ci, to po prostu tradycja, mająca głównie na celu, żeby członkowie naszego klanu nie podusili się nawzajem o łupy z okrętów. Statek wyrzuciło na brzeg, zabraliśmy z niego wszystko, co się dało, sporządziliśmy spis, coś podzieliliśmy, coś schowaliśmy do naszych ładowni – i tyle. Po co zagracać szafy? Zrobiło się w nich trochę miejsca – chyba nawet powinnam za to podziękować Admirałowi.";
			link.l1 = "No dobrze, wszystko jasne. W takim razie obieramy kurs na 'San Augustin'. Ale może jeszcze do ciebie zajrzymy, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "A, "+pchar.name+", wejdź, wejdź. Przyszedłeś do mnie w interesach, przyjacielu, czy po prostu wpadłeś pogadać?";
            link.l1 = "Tym razem chodzi o sprawę. Powiedzmy, że osobistą.";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "I całkiem ważne dla ciebie – sądząc po tym, jak bardzo jesteś poruszony.";
            link.l1 = "Naprawdę? Raczej zmęczony. Ostatnio musiałem się sporo nachodzić po twoich włościach. Stawy już dają o sobie znać – a ja naiwnie myślałem, że to spotyka tylko staruszków takich jak ty.";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "Trochę się zasapałem – i tyle. Widzisz, nie tylko w fotelu siedzę. A ciebie, widzę, nogi już zupełnie nie trzymają, ha-ha-ha!";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "A ty myślałeś, czemu tak przyrosłem tyłkiem do tego krzesła, he-he? Wiesz, światopogląd potrafi się mocno zmienić, kiedy zrozumiesz, że zdrowia nie kupisz nawet za wszystkie skarby tej Wyspy.";
            link.l1 = "Zabawne – właśnie o tym przyszedłem porozmawiać.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "A ty myślałeś, dlaczego przysiadłem tyłkiem do tego krzesła, he-he? Wiesz, światopogląd może się naprawdę zmienić, kiedy zrozumiesz, że zdrowia nie kupisz nawet za wszystkie skarby tej Wyspy.";
            link.l1 = "Zabawne – właśnie o tym przyszedłem porozmawiać.";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "O moje zdrowie?";
            link.l1 = "Nie, o bogactwach Wyspy. A mówiąc trochę dokładniej, o ich spisie. A jeśli być całkiem precyzyjną, to o dziennikach, które ten spis zawierają.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "Khe-khe... "+pchar.name+", nie do końca łapię, o co ci chodzi?";
            link.l1 = "Niedawno zabrałeś narwalom dzienniki statków przybitych do Wyspy...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "Tak, i ten głupek Greenspy postanowił wysłać cię po nich? Ale bezczelny, tak, co nie?";
            link.l1 = "Wcale nie, "+npchar.name+", Donald nie ma z tym nic wspólnego. To ja przyszedłem do niego z tym pytaniem, a on skierował mnie do ciebie. Ale twoja reakcja, muszę przyznać, trochę mnie rozbawiła. Nie zdradzisz, po co ci były potrzebne zapiski o narwalach?";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "Czemu by ci nie opowiedzieć? Mnie, jak się pewnie domyślasz, same statki zupełnie nie obchodzą. Tak samo jak skarby, które wypełniają ich ładownie, szczerze mówiąc, też nie. Tu dla wszystkich starczy, jeśli tylko nie będą zbyt chciwi – tak uważam. To, co mnie naprawdę interesuje, to broń: muszkiety, szable... armaty w końcu. Tak, ci spryciarze czasem nawet je zabierają. Głupim czarnuchom na to rozumu nie starcza, ale narwalom...";
            link.l1 = "I ty postanowiłeś sprawdzić, jak bardzo ludzie Greenspy są gotowi na nową rundę starcia?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "I zasugerować, że ja i moi ludzie mamy się na baczności. Przekaz jest dość jasny, ale biorąc pod uwagę ten cyrk, który Donald odstawił z tymi ćwiczeniami, całkiem możliwe, że uznał, iż interesują mnie jego pieniądze.";
            link.l1 = "No tak, widzę, że sytuacja rozwija się trochę nie po twojej myśli, tak, co nie? A co z Rivadosem? Czarny Eddie nie sprawia problemów?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Rivados, Eddie... Wstrętni Murzyni – nie bez powodu Rekin ich tak nienawidził.";
            link.l1 = "Czyli sprawia ci to przyjemność.";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "Właśnie o to chodzi, że nie, niech mnie diabli wezmą! Czarnuchy przycichły, zaszyły się na swoich statkach...";
            link.l1 = "No to czego, do diabła, ci wtedy nie pasuje, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "Jak by ci to wytłumaczyć, "+pchar.name+"... Widzisz, to jest jak wiatr na otwartym morzu. Czasem jest słaby, czasem silny, a czasem zamienia się w prawdziwy sztorm. Ale tak czy inaczej, wiatr pcha statek naprzód, a dobry kapitan potrafi go okiełznać.";
            link.l1 = "Lekka bryza zawsze lepsza niż okrutna burza.";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "Tak, co nie? Ale czasem bywa tak, że w ogóle nie ma wiatru. Cisza na morzu – i wtedy żaden szypper nic nie poradzi. Siedzisz po prostu na rufie, patrzysz na gładką taflę wody i zastanawiasz się, co, do diabła, będzie dalej. Z Eddiem i jego kumplem Chimisetem jest dokładnie tak samo – coś knują, czuję to całym sobą, i to nie wróży nic dobrego, przysięgam na gromy!";
            link.l1 = "Może powinieneś ruszyć tyłek z krzesła i pogadać z Edwardem twarzą w twarz. A jeszcze lepiej – zebrać się we trójkę, z Donaldem, i wszystko szczerze omówić. To o wiele lepsze, niż znowu utopić Wyspę we krwi. Ale dobra... Wróćmy do tego, po co tu przyszedłem.";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "Więc interesują cię skarby narwali, mam rację?   Czego tam szukasz?";
            link.l1 = "Interesują mnie listy zatopionych tutaj statków. Konkretnie — z roku 1638. Chodzi o to, że próbujemy znaleźć informacje o rodzicach Mary. Z matką sprawa jest w miarę jasna — ale z ojcem już tak powiedzieć się nie da. Informacje o nim są bardzo mgliste, nie znamy nawet jego imienia, a jedyną wskazówką, jaką mamy, jest nazwa statku, który rozbił się przy zewnętrznym pierścieniu w czerwcu 1638 roku...";
			link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "To szlachetna sprawa – sam kiedyś dręczyłem się myślą, kim właściwie był mój własny ojciec. Ale pomóc wam nie jestem w stanie.";
            link.l1 = "A dlaczego, jeśli to nie tajemnica?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "Nie mam przed tobą żadnych sekretów, "+pchar.name+". To wcale nie o mnie chodzi, tylko o Donaldzie – przekazał mi dokumenty dopiero od roku 1651. Zapytałem, co z wcześniejszymi zapisami, chociażby z poprzedniej dekady – i usłyszałem, że nie ma już żadnych papierów. To wszystko, co dostał w spadku po Alanie Milrow – tak powiedział.";
            link.l1 = "Nie sądzę, żeby miał powody kłamać.";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "Myślę tak samo, przyjacielu. Biorąc pod uwagę, że bez żadnych pytań oddał mi nowe zapiski. Co więcej, wydawało mi się, że był nawet w pewnym sensie zadowolony, że pozbył się tych gratów... Kto wie, może Milrow po prostu pozbył się papierów z minionych dekad... Spalił je, albo może...";
            link.l1 = "Nie, to niemożliwe.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "Nie, to niemożliwe. Alan by tak nie zrobił.";
            link.l1 = "Dlaczego jesteś tego taka pewna, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "Wydawało mi się, że on raczej wolał nóż i topór niż całą tę biurokrację. Jestem zaskoczona, że w ogóle umiał czytać.";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "On bardzo troskliwie podchodził do wszystkich zapisków dotyczących Wyspy. Uważał je za część jej historii. A historia, i to nie tylko tego miejsca, była prawdziwą pasją Alana, tak, co nie? Studiował wszystkie dostępne mu dokumenty historyczne, książki... Czasem wydawało mi się, że byłby z niego lepszy uczony niż wojownik – raz nawet mu to powiedziałam.";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
            dialog.text = "On bardzo troskliwie podchodził do wszystkich zapisków dotyczących Wyspy. Uważał je za część jej historii. A historia, i to nie tylko tego miejsca, była prawdziwą pasją Alana, tak, co nie? Studiował wszystkie dostępne mu dokumenty historyczne, książki... Czasem wydawało mi się, że byłby z niego o wiele lepszy uczony niż awanturnik – raz nawet mu to powiedziałam.";
            link.l1 = "Może rzeczywiście powinien był wybrać okulary, papier i pióro zamiast szabli i pistoletu – kto wie, może dalej by tu deptał zgniłe deski tych statków. Ale skoro Milrow był takim miłośnikiem archiwaliów, to gdzie podział te zapiski? Załóżmy, że jedną kartkę mógł przypadkiem zalać atramentem – ale przecież było ich dziesiątki, jeśli nie setki, prawda?";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_18":
            dialog.text = "Wiem tylko, że przechowywał takie dokumenty jak największy skarb. Może ktoś je ukradł, albo sam komuś je oddał...";
            link.l1 = "Ukradł? Komu mogłyby się przydać informacje o dawno już opróżnionych od pokładu do kilu statkach? Oddał – to bardziej prawdopodobne, tylko komu i po co?";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "Jakiemuś podobnemu miłośnikowi historii, ha-ha-ha! Zgadzam się z Charles'em – nie mam pojęcia, komu jeszcze mogłyby się przydać te stare bazgroły.";
            link.l1 = "Ktoś jednak ich potrzebował. Trzeba będzie się nad tym zastanowić. Dobra, "+npchar.name+", nie będziemy cię już więcej zatrzymywać. Jeszcze się zobaczymy.";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", cieszę się, że znowu się widzimy. Jak tam u was z Mary?";
			link.l1 = "I my cieszymy się, że cię widzimy, "+npchar.name+". A to, jak nam się ułoży - będzie zależeć od ciebie.";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "Intrygujący początek rozmowy, muszę przyznać. I trochę przerażający, patrząc na wasze miny.";
			link.l1 = "Nie bój się, "+npchar.name+", bo to przecież nie twoja wina. Po prostu trochę się zmęczyliśmy bieganiem po tych skrzypiących wrakach statków. No i dzień dziś duszny, tak, co nie?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "Ten upał wcale nam nie dodaje sił. Do tego musieliśmy trochę pobiegać po Wyspie, zanim cię znaleźliśmy – twoja pomoc jest potrzebna.";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "Ekhm, tak, lekki wietrzyk teraz by się bardzo przydał, tak, co nie? Więc co mogę dla was zrobić?";
			link.l1 = "Widzisz, ja i Mary prowadzimy śledztwo, by rzucić światło na wydarzenia sprzed dwudziestu lat.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "Ekhm, tak, lekki wietrzyk naprawdę by się teraz przydał, tak, co nie? Więc, co mogę dla was zrobić?";
			link.l1 = "Widzisz, ja i Mary prowadzimy śledztwo, by rzucić światło na wydarzenia sprzed dwudziestu lat.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "Brzmi ciekawie.   I czego to dotyczy?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "Moich rodziców, Antonio. Razem z Charles'em próbujemy dowiedzieć się, kim byli. I co się z nimi stało. Moja mama zmarła przy porodzie, to już ustaliliśmy. Ale z ojcem to nie takie proste...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "W którym roku się urodziłaś, przypomnij mi...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "W 1638 roku. W czerwcu.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "Miałem wtedy tylko dwanaście lat, Mary. Niezbyt dobrze pamiętam tamte czasy. Jakieś wspomnienia, jasne, teraz przemykają mi przez głowę, ale szczerze mówiąc, trudno byłoby je poskładać w całość. Przepraszam, ale raczej nie będę w stanie ci pomóc...";
			link.l1 = "Nie do końca o to nam chodzi, Antonio. Ale jeśli przypomnisz sobie coś z tamtego dnia, kiedy Mary przyszła na świat, będziemy ci bardzo wdzięczni.";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "W czym więc mogę wam pomóc, "+pchar.name+"?";
			link.l1 = "Mówiłeś mi, że interesujesz się historią. Zarówno światową, jak i tą Wyspy, tak, co nie?";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "To prawda. Przeczytałem najróżniejsze książki, przestudiowałem wszystkie rękopisy, które tylko udało mi się zdobyć...";
			link.l1 = "Właśnie o rękopisach będzie mowa. Oprócz ciebie na Wyspie był tylko jeden człowiek, który pasjonował się historią nie mniej niż ty...";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Alan Milrow. Tak, rozmawialiśmy o tym, kiedy nie był zajęty opracowywaniem planów zniszczenia rivaudos, a potem także piratów. Był bystrym facetem, naprawdę nieprzeciętnych talentów.";
			link.l1 = "Nie wątpię – chłopak był naprawdę niezły. Miał coś, co może nam się przydać. Coś, co nie ma żadnej praktycznej wartości dla nikogo na Wyspie Sprawiedliwości, poza wami dwojgiem. Dzienniki ewidencji statków rozbitych przy Wyspie, zawierające także opisy zdjętych z nich ładunków i kosztowności oraz, być może, nazwiska pasażerów...";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "Tak jest.";
			link.l1 = "Więc widziałeś ich, tak, co nie?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "Nie tylko widziałem – przepisywałem zawarte w nich informacje do swoich notatek. Podczas jednej z naszych rozmów wspomniał o istnieniu tych dzienników, więc poprosiłem go o nie do przestudiowania – próbuję stworzyć coś w rodzaju Kronik Wyspy Sprawiedliwości i te zapiski bardzo mi się przydały\nAlan był zachwycony moim pomysłem – napisać historię tego miejsca. Co prawda nie oddał mi wszystkich notatek, zostawił sobie te z lat 1650-tych, ale wtedy wystarczyło mi to, co dostałem.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = "Są tam przecież zapiski z 1638 roku? Proszę, powiedz, że są, tak, co nie!";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "Mam całą stertę tych dzienników – sięgają aż do 1620 roku. To właśnie wtedy, według Alana, zaczęto je prowadzić. I tak, rok 1638 też tam jest, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "Pozwolisz nam się z nimi zapoznać?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "Nie wygląda na to, żebym miała wybór, ha-ha-ha! Sekunda. Wszyscy są tutaj, w dolnej szufladzie tej szafki.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = "Proszę. Rozgość się, rozejrzyj...";
			link.l1 = "Tym się zajmiemy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "Oto, "+pchar.name+" , patrz, tak, co nie! Joshua i Teresa Casperowie! Nie mogę uwierzyć – udało się nam, udało, tak, co nie! I nazwa statku – 'Wrangler'! Teraz możemy dowiedzieć się wszystkiego o moim ojcu – kim był, jak się tu znalazł...";
			link.l1 = "Boję się, "+npchar.name+", za bardzo się spieszysz... To może nie być takie proste, jak się wydaje. Okręt Jego Królewskiej Mości... Trzeba się zastanowić, kto mógłby nam pomóc zdobyć informacje z archiwów Królewskiej Floty...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "Pomyślmy! Pomyślmy, a dostaniemy, "+pchar.name+"! Najtrudniejsze już za nami, tak, co nie!";
			link.l1 = "Może warto też porozmawiać z panami Youngiem i Friddicksem. Jednak nie przypominam sobie takich osób na Wyspie.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Bo ich tu nie ma, "+pchar.name+". Ci dwaj zmarli następnej nocy po tym, jak ich uratowano razem z Casperami.";
			link.l1 = "Ciekawe. Ciężarna kobieta przeżyła jeszcze tydzień, a dwóch marynarzy z Królewskiej Floty zmarło nagle...";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = "Z tego co pamiętam, oni już wtedy byli źli. Teraz sobie przypomniałem, "+pchar.name+" - byłem przecież niedaleko 'Ceres Smithy', kiedy ich zabrano na jej pokład... Tak, byłem na 'Esmeraldzie' - razem z Aurélie Bertin, chyba. Był tam też Chimiset - szaman tych czarnych bezbożników, który z jakiegoś powodu przyszedł do sklepu. Najpierw wydawało mi się, że tamci dwaj marynarze już nie żyją - ale umarli dopiero po dobie...";
			link.l1 = "No cóż, nic na to nie poradzimy. Ale i tak dowiedzieliśmy się sporo. Dzięki za pomoc, Antonio.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = "To nie moja wina, "+pchar.name+". To wszystko zasługa Alana – mało który z tych kirasjerów potrafiłby dostrzec prawdziwą wartość tych zapisków. A przecież to właśnie dzięki takim dokumentom odtwarza się historię!";
			link.l1 = "Mam nadzieję, że kiedyś razem z Mary przeczytamy twoje Kroniki, przyjacielu. Trzymaj dziennik, nie zgub go. No, musimy już iść. Może jeszcze się zobaczymy, przyjacielu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Bo ich tu nie ma, "+pchar.name+". Ci dwaj zmarli następnej nocy po tym, jak zostali uratowani razem z Casperami.";
			link.l1 = "Ciekawe. Ciężarna kobieta przeżyła jeszcze tydzień, a dwóch marynarzy z Królewskiej Floty zmarło nagle...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "Miło cię znowu widzieć, mój przyjacielu. Z czym do mnie przychodzisz?";
			link.l1 = "Z prośbą, "+npchar.name+"... A właściwie z pytaniem.";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "Zadaj swoje pytanie. Albo powiedz, o co prosisz. Zrobię wszystko, co w mojej mocy, żeby ci pomóc.";
			link.l1 = "Dobrze.   Jak długo mieszkasz na Wyspie?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "Dziesiątki i dziesiątki lat, mój przyjacielu. Trafiłem tutaj jako dziecko, ale już byłem rozgarnięty — na pokładzie statku handlującego niewolnikami. Moja historia niewiele różni się od wielu innych, które tu słyszałeś. Sztorm, katastrofa morska... Angielski galeon, w którego ładowni byłem zamknięty, nie dotarł nawet do zewnętrznego pierścienia — rozpadł się na pół po uderzeniu w jedną z raf, na którą rzuciła go fala.";
			link.l1 = "Jak ty się uchowałeś? Rafy są przecież dość daleko od zewnętrznego pierścienia, a dopłynąć stamtąd przez sztormowe fale to, powiedzmy sobie szczerze, nie lada wyzwanie...";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "Bogowie byli po mojej stronie tamtej nocy. Udało mi się uwolnić z kajdan, a potem złapać za kawałek tego, co kiedyś było szalupą. Był ze mną mój towarzysz, Asana – razem walczyliśmy z falami, aż nie straciliśmy przytomności ze zmęczenia.";
			link.l1 = "Zostałeś wyrzucony na jeden z tych statków?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "Tak, weszliśmy do dziury w ładowni... Tam znowu straciłem przytomność, byłem już tak wyczerpany. Ocknąłem się, gdy Asana zaczął wrzeszczeć – rozszarpywał go na kawałki gigantyczny krab, który wdrapał się na ten sam statek, na który nas wyrzuciło. Patrzyłem na to i wiedziałem, że będę następny – sparaliżowany strachem i bezsilnością, nie mogłem się ruszyć z miejsca.";
			link.l1 = "Mogłeś spróbować pomóc przyjacielowi. Ale wtedy nie rozmawialibyśmy teraz, tak, co nie? Jak ci się udało uciec?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "Masz szczęście, że zaczął nie od ciebie, "+npchar.name+". Jak się uratowałeś – wskoczyłeś z powrotem do wody i odpłynąłeś?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "Krzyki Asany usłyszeli jacyś Riwados, którzy wyruszyli na łowy po skarby z ładowni statków po kolejnym huraganie. Otoczyli bestię i zabili ją. Asanie nie dało się już pomóc, ale mnie poszczęściło się znacznie bardziej. Tak właśnie trafiłem tutaj. Ale teraz odpowiedz mi ty, mój przyjacielu – dlaczego chciałeś to wiedzieć?";
			link.l1 = "Tak naprawdę, "+npchar.name+", chciałam się dowiedzieć nie tego, jak tu trafiłeś, tylko kiedy to się stało.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "Krzyki Asany usłyszało kilku rivados, którzy wyruszyli na łowy po skarby z ładowni statków po kolejnym huraganie. Otoczyli bestię i zabili ją. Asanie nie dało się już pomóc, ale mnie poszczęściło się znacznie bardziej. Tak właśnie trafiłem tutaj. Ale teraz odpowiedz mi ty, mój przyjacielu – po co chciałeś to wiedzieć?";
			link.l1 = "Tak naprawdę, "+npchar.name+", chciałam się dowiedzieć nie tego, jak tu trafiłeś, tylko kiedy to się stało.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "Hmm, według waszego kalendarza to był rok 1623, koniec lata – dokładniej nie potrafię powiedzieć...";
			link.l1 = "To nawet nie jest potrzebne. Czyli w 1638 roku byłeś już od piętnastu lat na Wyspie.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "Wygląda na to, mój przyjacielu.";
			link.l1 = "W czerwcu tamtego roku do zewnętrznego pierścienia huragan przygnał bryg 'Wrangler', okręt floty Jego Królewskiej Mości Karola I, króla Anglii. Z całej załogi przeżyło tylko czterech – wśród nich rodzice Mary: Joshua i Teresa Casperowie.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "Tak, pamiętam to, mój drogi. Niby przez mgłę, ale pamiętam...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "Pamiętasz, naprawdę? No opowiedz!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "Mogę powiedzieć niewiele. Cztery osoby: oficer, jego żona i dwóch marynarzy. Kobieta była w ciąży i ci, którzy ich uratowali, myśleli, że nie przeżyje do rana – ale okazała się silna jak lwica, za to ci dwaj marynarze opuścili ten świat już mniej niż dobę później... Widziałem ich: byli słabi, ale sił życiowych mieli jednak całkiem sporo...";
			link.l1 = "Sugerujesz, że zostali zabici?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "Jeśli nawet tak było, to nie było na to świadków, ani ran na ich ciałach, mój przyjacielu...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "Powiedziałeś 'oficer', tak, co nie... Mój ojciec naprawdę był oficerem?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "Miał na sobie mundur oficerski – to chyba jedyne, co pamiętam, kiedy próbuję sobie przypomnieć, jak wyglądał.";
			link.l1 = "Jeśli był oficerem, to nic innego nie mógł nosić – raczej wątpię, żeby jego garderoba była szczególnie różnorodna... Może przypomnisz sobie jeszcze jakieś szczegóły, "+npchar.name+"? Jakieś znaki szczególne... Powiedzmy, blizna na twarzy albo jeszcze jakieś okaleczenie...";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "Nie pamiętam niczego szczególnego, mój przyjacielu. Jego twarz niemal zatarła się w mojej pamięci – minęło już dwadzieścia lat... Ale spojrzenie – to pamiętam doskonale. Rozmawiałem z tym człowiekiem tylko raz, ale spojrzenia jego szarych oczu – takich jak u Mary – nie zapomnę nigdy. Było w nim pomieszanie rozpaczy, strachu, jak u osaczonej antylopy, a jednocześnie – wściekłości i determinacji godnych lwa...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "Rozmawiałeś z nim, tak, co nie? O czym?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "Stało się to na kilka godzin przed twoimi narodzinami. Pojawił się tutaj, na pokładzie 'Protektora', i zażądał spotkania ze mną. Przywódca rivados, Mogedi, był zaskoczony jego zuchwałością — ale ten człowiek nagle mnie zaintrygował. Gdy stanął przede mną, padł na kolana i błagał, bym uratował jego żonę... Ktoś, w ciągu tego krótkiego czasu, kiedy tu byli, zdążył mu o mnie opowiedzieć. Zgodziłem się, choć Mogedi protestował...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = "Więc jestem ci winna życie, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "Nie ma sensu kłamać – dotarliśmy do twojej matki, ale za późno: narwale nie chciały mnie wpuścić na 'Ceres Smity'. Twojemu ojcu udało się ich... przekonać, ale biedną Teresę zobaczyłem dopiero na jej ostatnim tchnieniu. Zdołała cię urodzić i, gdybym zjawił się wcześniej, może uratowałbym jej życie, ale...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "Mama umarła, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "Niestety. Spojrzała na ciebie i wydała ostatnie tchnienie, ale zanim to się stało, jakby zebrała w sobie resztki sił i zawołała jakiegoś Ruperta. Krzyknęła jego imię na całe gardło, jakby wołała o pomoc – i umarła.";
			link.l1 = "Ruperta? Nie Joshua?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "Gdy ci to opowiadałem, mój przyjacielu, jakbym na nowo przeżył tamtą chwilę. Nigdy tego nie zapomnę – ani jej ostatniego krzyku, ani twarzy wykrzywionej cierpieniem. I tak, ostatnie słowo, które padło z jej ust, to było właśnie 'Rupert'.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "Czy ona była piękna, moja mama? Możesz opisać, jak wyglądała, Chimisette?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = "To nie ma sensu, Mary. Wystarczy, że spojrzysz w lustro – jesteście do siebie podobne jak dwie krople wody. Tylko oczy masz po ojcu.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "A co z nim się stało? Udało nam się ustalić, że kilka dni po moim urodzeniu zapadł się pod ziemię, tak, co nie? Ale przecież go nie zabili, prawda?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "Gdy tylko dowiedział się, że Teresa jest umierająca, Joshua wpadł w prawdziwą furię — przysięgam, nawet lwy na sawannie nie rzucają się na zdobycz z takim gniewem, z jakim twój ojciec zaatakował tych narwali, którzy blokowali mi dostęp do fleuty... Trzeba było z sześciu ludzi, żeby go obezwładnić — i to dopiero po tym, jak wrzucił do wody dwóch wojowników klanu w pełnym rynsztunku.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "I co z nim zrobili - powiedz, no dalej!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "Został wrzucony do jednej z cel na 'Tartarusie'. Nikt nie odważył się go sądzić – chciano, żeby ta sprawa najpierw ucichła... Prawie wszyscy mu współczuli, ale niewielu chciało mieszkać z takim człowiekiem pod jednym dachem. Joshua zniknął po kilku dniach – wtedy też z Wyspy odpłynęło kilka łodzi przemytników. Nikt go nie widział w łodziach – to właśnie wywołało plotki o jego śmierci.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "Czyli wierzysz, że on żyje, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "Powiem tylko to, co z pewnością powiedzą wam też inni – nikt nie znalazł jego ciała. Może jednak ukrył się na dnie którejś z łodzi, a może poderżnięto mu gardło w tej celi i rzucono krabom...";
			link.l1 = "To, że zniknął dokładnie wtedy, gdy odpłynęli ci handlarze, raczej przemawia za pierwszym - takie przypadki się nie zdarzają. I może komuś zdradził swoje plany? Jeśli uciekł, to uciekł, zostawiając tu nowo narodzoną córkę, co w pewnym sensie jest całkiem rozsądne - niemowlę mogłoby nie przetrwać podróży do brzegów Kuby w lichym czółnie... Ale na pewno zamierzał po nią wrócić.";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "Nie wiem tego, mój drogi. Jeśli Joshua Casper z kimś wtedy rozmawiał, to chyba tylko ze swoimi strażnikami – ale wszyscy oni dawno już opuścili ten grzeszny świat. Ach tak, pewnego dnia przyszedł do niego padre Domingo – był księdzem dla białych przed bratem Julianem...";
			link.l1 = "On co, chciał się wyspowiadać? Chyba bał się umrzeć podczas ucieczki.";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "Nie jestem w stanie rzucić światła na to, czego nie wiem, mój przyjacielu. Tak, co nie? A i Domingo też wam już nic nie opowie – utonął z piętnaście lat temu. Albo ktoś mu przyłożył w łeb, albo po prostu się upił – to akurat bardzo lubił...";
			link.l1 = "Ale może Domingo prowadził dziennik... albo opowiadał o tej rozmowie z Joshuą swojemu bratu Julianowi?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "Muszę z nim porozmawiać, "+pchar.name+", tak, co nie? I jak najszybciej. Nie chcę nawet myśleć o powrocie na statek, dopóki się z tym nie uporamy.";
			link.l1 = "Jeśli w ogóle jest tu jeszcze coś do wyjaśnienia. Julian może o tym nawet nie wiedzieć – ale my się tego na pewno dowiemy. Dzięki ci, Chimiset.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "Zawsze jestem do twoich usług, mój przyjacielu. Ale pozwól, że dam wam obojgu radę.";
			link.l1 = "A jaki?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "Nie zapuszczajcie się zbyt głęboko w zarośla podczas polowania – możecie już stamtąd nie wyjść.";
			link.l1 = "Będziemy o tym pamiętać, szamanie. A teraz – żegnaj.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "Witam was w cieniu domu Bożego, moje dzieci. Przyszliście się wyspowiadać czy po prostu pomodlić się?";
			link.l1 = "Cześć, bracie Julianie. Obawiam się, że wyliczanie naszych grzechów zajęłoby zbyt wiele czasu – którego, niestety, nie mamy. Ale możesz być pewien – jako dobrzy katolicy odwiedzamy kościół w każdym porcie.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "Witamy, bracie Julianie. Modlitwą do naszego Pana, jak przystało dobrym katolikom, zaczynamy dzień i nią też go kończymy.";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = "Dobrzy katolicy, żyjący bez ślubu pod jednym dachem... To niemal bluźnierstwo, synu mój. A to, przypomnę, grzech śmiertelny!";
			link.l1 = "Czyż nie jest powiedziane w Piśmie, że miłość zakrywa wszystkie grzechy?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = "Dobrzy katolicy, żyjący bez ślubu pod jednym dachem... To już prawie bluźnierstwo, synu mój. A przypomnę, to grzech śmiertelny!";
			link.l1 = "Czyż nie jest powiedziane w Piśmie, że miłość zakrywa wszystkie grzechy?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "Miłość polega na tym, byśmy postępowali według Jego przykazań – czy muszę ci je przypominać, synu mój?";
			link.l1 = "Może innym razem. Jesteśmy tu w innej sprawie.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "Zagubione dusze nigdy nie jest za późno, by wrócić na właściwą drogę... Ale słucham was, moje dzieci.";
			link.l1 = "Rzeczywiście trochę się zagubiliśmy, bracie Julianie. W gąszczu przeszłości. I mamy nadzieję, że zdołacie nam pomóc odnaleźć drogę do światła.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "Bardzo dowcipnie, synu mój. Powinieneś pamiętać, że to nie człowiek prowadzi ku światłu, lecz Pan – i podążając za Nim, pamiętaj, że niezbadane są Jego drogi.";
			link.l1 = "Będę mówił krótko, bracie Julianie. Próbujemy dowiedzieć się wszystkiego, co możliwe, o rodzicach Mary. Z jej matką, Teresą, sprawa jest w miarę jasna – przybyła na Wyspę razem z mężem i zmarła przy porodzie tydzień później. A ojciec... Zniknął kilka dni po narodzinach Mary, uciekając wtedy z 'Tartarus'. Według plotek, ostatnią osobą, z którą tu rozmawiał, był padre Domingo – wasz poprzednik.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "W takim razie spóźniliście się o ponad półtorej dekady, moje dzieci.";
			link.l1 = "Tak, wiemy, że padre zginął już dość dawno. I wtedy ty, bracie Julianie, byłeś jeszcze zbyt młody, żeby znaleźć się na Wyspie w odpowiednim stanie, tak, co nie?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "Znalazłem się tutaj kilka lat po jego śmierci. Sporo mnie kosztowało, żeby na tym statku wszystko doprowadzić do porządku, ale z Bożą pomocą dałem radę, synu mój.";
			link.l1 = "Kiedy się tu rozglądaliście, nie natknęliście się przypadkiem na jakieś zapiski ojca Domingo?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "Ma pan na myśli coś konkretnego, synu mój?";
			link.l1 = "Interesują nas dzienniki albo jakieś księgi rachunkowe... Mało nadziei na cud, ale padre mógł zostawić treść tej rozmowy w którejś ze swoich notatek. Zakładamy, że ojciec Mary opuścił wyspę na jednej z łodzi przemytników – może wspomniał padre, dokąd zamierza się udać i kiedy wróci po córkę?";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "Nie znalazłem żadnych dzienników ani niczego podobnego, to na pewno, ale za to różne zapiski... Jeśli chodzi o prowadzenie spraw kościelnych, był naprawdę skrupulatny – nie każdego sługę Pan obdarza taką pedanterią. Ale w jego papierach są tylko suche liczby i nazwiska – i nic więcej.";
			link.l1 = "Z tego, co udało nam się ustalić, Joshua Casper – tak właśnie się nazywał – w przypływie gniewu po śmierci żony zabił dwóch członków klanu 'Narwal', którzy odmówili wpuszczenia czarownika Riwadosa Chimisetę do matki Mary...";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "Zachowali się jak dzieci prawdziwego Kościoła! Za tym sługą Diabła tęsknią lochy Inkwizycji!";
			link.l1 = "Panie, myślę, że Pan Bóg byłby przerażony, gdyby się dowiedział, ilu ludzi zostało zamęczonych w Jego imię. Kasper miał więcej szczęścia – wrzucono go do celi na 'Tartarusie', ale do wyroku nie doszło.";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "Tak, tak, bez wątpienia. Kaspera wrzucono do jednej z cel 'Tartaru', ale wyroku nie wydano – nie wszyscy potępili czyn męża, który stracił żonę.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "Co było dalej – ten heretyk uciekł?";
			link.l1 = "Nie minął nawet tydzień, a Joshua zniknął. A tej nocy, zanim to się stało, odwiedził go padre Domingo. Pytanie brzmi – po co? Wątpię, żeby protestant, którym Casper z pewnością był, poszedłby spowiadać się katolickiemu księdzu – jak sądzicie?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "Co było dalej – ten heretyk uciekł?";
			link.l1 = "Nie minął nawet tydzień, a Joshua zniknął. A w noc przed tym odwiedził go padre Domingo. Pojawia się pytanie – po co? Wątpię, żeby protestant, którym Casper z pewnością był, poszedłby spowiadać się katolickiemu księdzu – jak sądzisz?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "Nigdy nie jest za późno, by zwrócić się ku prawdziwej wierze, synu mój. Ale myślisz słusznie. Jeśli nie potrzebował spowiedzi, to może rozmawiał z padre o pogrzebie żony – o ile, oczywiście, była katoliczką. Albo o chrzcie córki, a raczej o jego odmowie, bo protestanci nie chrzczą niemowląt, wierząc, że człowiek powinien samodzielnie i świadomie podjąć decyzję o przyjęciu chrztu.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "Ale mnie ochrzczono, bracie Julianie. Eric Udett mi o tym mówił.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "To tylko moje domysły, córko moja. Prawdy nie znam. Pan otwiera nam oczy tylko na to, co naprawdę ważne i potrzebne.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "I dla mnie właśnie tak jest, tak, co nie? Może na stronach zapisków ojca Domingo jednak zostało coś, czego nie zauważyłeś, bracie Julianie? Przecież tylko je przeglądałeś, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "Nie miałam tam czego szukać, córko moja. Widzę, że od dawna i z wielkim zaangażowaniem zajmujecie się tą sprawą – Pan prowadzi was tą ciernistą drogą. Jeśli jest ci pisane znaleźć to, czego szukasz, taka jest Jego wola i nie mnie się jej sprzeciwiać. Mogę wam dać zapiski Domingo z roku twoich narodzin, może znajdziecie w nich coś pożytecznego.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "To byłoby bardzo wielkoduszne z twojej strony, bracie Julianie. Zachowały się zapisy z roku 1638?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "No proszę... (zdmuchuje kurz). Chyba to właśnie to. Księga rachunkowa z roku 1638 po Narodzeniu Chrystusa.";
			link.l1 = "Pozwól, bracie Julian...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "Patrz, "+pchar.name+": 3 sierpnia. W ten dzień ochrzczono mnie i Fabiana. A urodziłam się 22 czerwca. Ale o moim ojcu ani słowa, tak, co nie?";
			link.l1 = "Wszystko tak, jak mówił brat Julian – suche liczby i nazwiska. Co ciekawe, padre Domingo tak bardzo oddał się swojej gorliwości, że odprawiał nabożeństwa nawet za protestantów – wątpię, żeby van Eckus, Young i Friddicks byli katolikami.";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "Mogli przecież przyjąć prawdziwą wiarę tuż przed wejściem do Królestwa Bożego, synu mój.";
			link.l1 = "Oczywiście, brat Julianie – czymże innym mieliby się zajmować? Zwłaszcza jeśli zginęli jak Sorrento i Rojas – sądzę, że to właśnie te narwale, które zagrodziły drogę Chimiseto.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "Lepiej by było, gdyby padre Domingo zapisywał całe drugie imiona, tak, co nie? Co właściwie znaczą te „W.” i „Dż.” po imionach mojej mamy i moim?";
			link.l1 = "A kim jest ten Fabian, który był ochrzczony razem z tobą tego samego dnia?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "Syn Cecile Gallard. Och, właśnie sobie przypomniałam! To ona mnie wykarmiła, choć nigdy nie była dla mnie szczególnie czuła. Pewnie dlatego, że ja przeżyłam, a Fabian nie. On zmarł kilka miesięcy po narodzinach, tak, co nie?";
			link.l1 = "Może warto z nią porozmawiać, skoro z tej książeczki nie dowiedzieliśmy się prawie niczego pożytecznego – no chyba że liczyć daty twojego urodzenia i chrztu.";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "Nie jest dużo młodsza od Aurelii, "+pchar.name+". Pozostaje tylko mieć nadzieję, że chociaż ona ma wszystko w porządku z głową.   Ale co zamierzasz się od niej dowiedzieć?";
			link.l1 = "No cóż, skoro była twoją mamką – całkiem możliwe, że mogła dowiedzieć się od ojca Domingo jakichś szczegółów jego rozmowy z Joshuą. Komu, jak nie jej, mógł to opowiedzieć? Może jeszcze Aurélie albo Ericowi. Ale wydaje mi się, że z tej pierwszej wycisnęliśmy już wszystko, co się dało, a ten drugi już nikomu nic nie powie.";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "Ta dobra kobieta jest wierną parafianką tego Bożego przybytku. Nie opuszcza żadnej mszy i regularnie się spowiada. Myślę, że naprawdę może wam pomóc, moje dzieci.";
			link.l1 = "Dziękuję wam, ojcze. Żegnajcie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" i Mary Casper. Co za miłe spotkanie!";
			link.l1 = "Wzajemnie, "+npchar.name+". Właściwie to przyszliśmy do was. Chcielibyśmy z wami coś omówić.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "Tak? No dobrze, słucham cię uważnie.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "Chodzi o moich rodziców, Cecylio. O mojej mamie dowiedzieliśmy się już wszystkiego, co mogliśmy... Zmarła zaraz po moim urodzeniu. Ale ojciec... on zniknął bez śladu kilka dni później. Jesteśmy skłonni sądzić, że nie zginął, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = "No tak, kogoś takiego jak on naprawdę trzeba się było postarać posłać na tamten świat...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "Widziałaś go?! Rozmawiałaś z nim?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "Moja dziewczynko, widziałam, jak poradził sobie z dwoma narwalami prawie gołymi rękami...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "Z Sorrento i Rojasem?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "Wtedy miałam tyle roboty, że nie miałam głowy do zapamiętywania imion tych łotrów – a teraz to już w ogóle ich nie pamiętam.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "Dobrze, to nieważne. Kontynuuj, proszę, Cecile.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "A co tu dalej opowiadać? Zrzucił tamtych dwóch do wody, poszli na dno jak kamień, a jego samego obezwładnili i zabrali na 'Tartarus'. I dobrze zrobili – kto wie, kogo jeszcze ten zabijaka chciałby utopić...";
			link.l1 = "Zabijaka? Trochę ostro, nie uważa pani, pani Gallard? Mówimy o człowieku, o oficerze, który właśnie stracił żonę...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "Widzę, że nie macie o nim najlepszego zdania – nie o każdym oficerze tak mówią.";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "Oficerze, no-no. Mundur to miał naprawdę porządny, pamiętam jak dziś. Prawie jak spod igły. Ale widziałam już wielu oficerów, młody człowieku. I wszyscy oni zachowywali się o wiele godniej niż ten... pan.";
			link.l1 = "Zrobił coś jeszcze? Oprócz zabicia tamtych dwóch?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "Panie oficerze, no-no. Mundur to miał naprawdę porządny, pamiętam jak dziś. Prawie jak spod igły. Ale widziałam już wielu oficerów, młody człowieku. I wszyscy oni zachowywali się o wiele godniej niż ten... pan.";
			link.l1 = "Zrobił coś jeszcze? Oprócz zabicia tamtych dwóch?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "Zażądał, żeby do celi przyszedł do niego ksiądz – padre De la Cruz...";
			link.l1 = "No proszę! Właśnie o tym chcieliśmy z wami porozmawiać. Znacie szczegóły tamtej rozmowy?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "No pewnie, młody człowieku! Ten łajdak-protestant zażądał od ojca, żeby nie chrzcił jego córki – mimo że jej matka była Irlandką, czyli katoliczką.";
			link.l1 = "Pierwszy raz chyba słyszę, żeby Angielka tak mówiła o protestancie... Ekhm, przepraszam, że przerwałem, pani "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "Kiedyś sama byłam protestantką, co tu dużo ukrywać. Ale brat Julian potrafił sprowadzić mnie na właściwą drogę.";
			link.l1 = "No proszę... Prawdziwie zdolny sługa Pański. Ale odbiegliśmy od tematu. Czyli Kasper chciał, żeby jego córka wychowywała się w wierze protestanckiej.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "Tak właśnie powiedział naszemu padre De la Cruz. A jeszcze – kazał nazwać dziewczynkę Julią...";
			link.l1 = "Więc to o to chodzi z tym 'J.'. Mary Julia Casper... Ale czemu nazwali ją Mary?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "Bo tak chciała jej matka, właśnie dlatego. Kiedy dziewczynkę wyjęto z jej łona, matka wyszeptała imię – Mary. Ja przy tym nie byłam, ale Aurélie Bertin była obecna przy porodzie. Możecie ją zapytać, jeśli chcecie...";
			link.l1 = "Czyli wzięli pod uwagę właśnie życzenie matki.";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = "Czy mogło być inaczej – w końcu ten nieudaczny ojczulek jakby zapadł się pod ziemię, tak, co nie?";
			link.l1 = "Biorąc pod uwagę... talenty padre De la Cruz, wątpię, by zdanie ojca zostało wzięte pod uwagę, nawet gdyby został na 'Tartarusie'. Domingo nic wam nie mówił - nie był wtajemniczony w plany Caspera dotyczące ucieczki i ewentualnego powrotu po dziewczynkę?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "Może macie rację. Ale wracając do rozmowy ojca Domingo z panem Casperem – ksiądz nie wspominał, czy Joshua rozmawiał z nim o ucieczce i możliwym terminie powrotu po córkę?";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = "O niczym takim nie opowiadał. Tak, co nie, sami pomyślcie, "+npchar.name+", gdybyście zamierzali uciec z więzienia, opowiadalibyście o tym pierwszemu lepszemu? Ten facet na pewno by tego nie zrobił, tak wam powiem.";
			link.l1 = "Więc i ten trop zaprowadził nas donikąd. No cóż, dziękuję pani za poświęcony czas, pani "+npchar.lastname+". Jeszcze się zobaczymy.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = "O niczym takim nie wspominał. Tak, co nie, sami pomyślcie, "+npchar.name+", gdybyście zamierzali uciec z więzienia, opowiedzielibyście o tym pierwszemu lepszemu? Ten facet na pewno by nie opowiedział, tak wam powiem.";
			link.l1 = "Więc i ten trop zaprowadził nas donikąd. No cóż, dziękuję pani za poświęcony czas, pani "+npchar.lastname+". Jeszcze się zobaczymy.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "Dowiedzieliśmy się całkiem sporo ciekawych rzeczy, "+pchar.name+". Ale praktycznie nie posunęliśmy się naprzód, tak, co nie?";
			link.l1 = "I nawet trochę się pogubili. Ciekawe, kim jest ten Rupert, do którego twoja matka wołała przed śmiercią?";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "Może brat albo... bliski przyjaciel?";
			link.l1 = "Przyjaciel, mówisz, no no... Ciekawe, czy Joshua o nim wiedział...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "Co masz na myśli, "+pchar.name+"?";
			link.l1 = "Trzeba to wszystko porządnie przemyśleć. Na szczęście będziemy mieli na to mnóstwo czasu, szukając kogoś, kto może nam pomóc w dalszych poszukiwaniach. Wykonaliśmy kawał dobrej roboty. Ale to jeszcze nie koniec. Do kancelarii Królewskiej Marynarki Wojennej sami się nie dostaniemy, a na dodatek mieści się ona po drugiej stronie oceanu, w Londynie... Masz pomysł, kto mógłby nam w tej sprawie pomóc?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "A co z Sergem Benoit, Charles?";
			link.l1 = "Abbat? Ma szerokie kontakty, to prawda, ale raczej nie zdoła dostać się do archiwów Królewskiej Floty.";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "Jeśli sam nie da rady – może nas skontaktuje z kimś, kto to potrafi, tak, co nie?";
			link.l1 = "Chyba tak. Czyli obieramy kurs na Saint-Pierre.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "No to teraz pozostaje nam tylko czekać, tak, co nie?";
			link.l1 = "Jestem pewna, że wszystkiego się dowie, "+npchar.name+". Czas minie szybko, nawet się nie obejrzysz. A póki co - mamy co robić.";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "Sugerujesz coś konkretnego, kochany?";
			link.l1 = "Mamy mnóstwo spraw na głowie, ale może teraz wrócimy na statek, zamkniemy drzwi i poświęcimy trochę czasu tylko sobie? Co ty na to?";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "A wiedziałam, że to zaproponujesz, tak, co nie! Powiem ci tak: nie traćmy czasu!";
			link.l1 = "Chodźmy już, moja najdroższa.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "Och, "+pchar.name+", nawet nie wiesz, po prostu nie wiesz, jaki ciężar właśnie spadł mi z serca, tak, co nie!";
			link.l1 = "Doskonale sobie wyobrażam, kochana – aż cała promieniejesz, ha-ha! Jak widzisz, wszystko było nie na darmo.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "Mój ojciec był sławnym oficerem, wyobraź sobie! Ale jakże szkoda, że nigdy nie było nam dane się spotkać. I przecież do dziś nie wiemy, czy dotarł na Wielki Ląd, tak, co nie...";
			link.l1 = "Gdyby tak się stało, na pewno wróciłby do służby i prędzej czy później ktoś by o nim usłyszał. Wątpię, żeby taki człowiek potrafił usiedzieć spokojnie w jednym miejscu – no bo, po kim ty to masz?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "Naprawdę myślisz, że on nie żyje? Wpadł w ręce Hiszpanów na Kubie, albo został zabity na Wyspie Sprawiedliwości?";
			link.l1 = "Staram się trzeźwo patrzeć prawdzie w oczy, "+npchar.name+". W tamtych latach z Wyspą istniała jakaś tam komunikacja, przemytnicy pływali tam swoimi tartanami z godną pozazdroszczenia regularnością. Gdyby tylko udało mu się opuścić Wyspę, nie wątpię, że po jakimś czasie wróciłby tam po ciebie.";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "Żeby mnie stamtąd zabrać. Ale wtedy byśmy się nie spotkali, tak, co nie.";
			link.l1 = "Takie jest życie, kochana. Nigdy nie wiesz, gdzie znajdziesz, a gdzie stracisz. Mam nadzieję, że nie żałujesz, że jesteś tu ze mną, tak, co nie?";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "Nie słyszałam w życiu większej głupoty, tak, co nie! "+pchar.name+", jesteś najlepszy, jesteś wspaniały! Dziękuję ci, że włożyłeś tyle wysiłku, żeby mi pomóc to wszystko wyjaśnić. To dla mnie naprawdę ważne, tak, co nie! Ale chodźmy przejrzeć te dokumenty – może znajdziemy w nich coś, czego nasz przyjaciel nam nie powiedział...";
			link.l1 = "Dobry pomysł. Zaczynajmy od razu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "No więc, "+pchar.name+", zauważyłeś coś ciekawego?";
			link.l1 = "Tak, "+npchar.name+". Coś jest...";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "Wyglądasz, jakbyś ducha zobaczył, tak, co nie.";
			link.l1 = "Wspomina się tu o jakimś Rupercie Northwoodzie.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "Rupert Northwood?! Naprawdę - ten słynny?";
			link.l1 = "Cicho, "+npchar.name+" - nie krzycz tak. Hm... Myślę, że tak, co nie – to właśnie ten człowiek, o którym mówił Chimiset. Inaczej być nie może – takie przypadki się nie zdarzają.";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "I co o tym wszystkim myślisz, "+pchar.name+"?";
			link.l1 = "Ta historia robi się coraz bardziej zagmatwana. Wynika z tego, że z Plymouth wypłynął 'Cornwall', do Antigua dotarł również 'Cornwall', a na rafach Wyspy Sprawiedliwości rozbił się już 'Wrangler' — i za każdym razem dowodził nimi ten sam Joshua Casper, który zdołał potajemnie od Admiralicji poślubić kobietę, błagającą w przedśmiertnych drgawkach kogoś imieniem Rupert.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "Nic nie rozumiem. Nawet nie wiem, kto jeszcze mógłby rzucić na to choć trochę światła. Im bardziej próbujemy dowiedzieć się czegoś o moim ojcu, tym bardziej toniemy w bagnie coraz to nowych tajemnic i sekretów, tak, co nie?";
			link.l1 = "Jeśli ktoś w ogóle jest w stanie coś wyjaśnić – to albo Joshua Casper, albo Rupert Northwood.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "Northwood? Ale przecież on nie żyje, tak, co nie? Chyba nie sądzisz, że raport sporządzony po przybyciu 'Cornwalla' do St. John's zawiera fałszywe informacje?";
			link.l1 = "Ach, ta twoja naiwność, "+npchar.name+"... Zaczynam myśleć, że cała ta historia jest dosłownie przesiąknięta kłamstwami. Pomyśl sama: Joshua Casper był wzorowym oficerem – mnóstwo odznaczeń i ani jednej nagany. Jakoś to się nie klei z tym, czego dowiedzieliśmy się o nim na Wyspie Sprawiedliwości, gdzie bez wahania posłał do piachu dwóch ludzi, nie sądzisz?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "Walczył o życie swojej żony, mojej matki, "+pchar.name+"!";
			link.l1 = "Bez wątpienia, ale zastanówmy się, skąd ona się w ogóle wzięła? I co ważniejsze – po co on w ogóle ukrył przed Admiralicją swoje małżeństwo? Facet służbista do szpiku kości, wierny regulaminowi i obowiązkowi oficer – inaczej jego sprawa nie byłaby tak czysta – a tu nagle taki wybryk.";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "A może kryje się za tym jakaś piękna i romantyczna historia? Tak przecież, choć rzadko, ale się zdarza, tak, co nie?";
			link.l1 = "Nie zrozum mnie źle, Mary, ale to wszystko nie wygląda na romantyczną historię. Bardziej przypomina jakąś inscenizację, odegraną bez wyraźnego powodu. Po co było zmieniać nazwę okrętu w drodze na Providence? Przecież to jednostka wojskowa — za takie sztuczki można trafić pod sąd wojenny.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "Zgadzam się – dobre pytanie.";
			link.l1 = "Z tym Rupertem Northwoodem też coś jest nie tak, tak, co nie? W bitwie zginęła prawie połowa załogi, ale, co dziwne, żaden oficer poza nim. I dlaczego twoja matka przed śmiercią wołała właśnie Ruperta, a nie swojego męża, Joshuę?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "Czyli jesteś pewien, że pierwszy oficer jednak nie zginął w walce z Hiszpanami, tak, co nie? I że wcale nie jestem córką Joshuy Caspera, tylko Ruperta Northwooda – do tego zmierzasz?";
			link.l1 = "Jak już mówiłem – prawdę zna tylko jedna osoba. Albo Joshua Casper, który z jakiegoś powodu nazwał Teresę swoją żoną, albo Rupert Northwood, który równie zagadkowo przyjął imię swojego kapitana.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "No i diabelstwo, tak, co nie! I co my teraz zrobimy, "+pchar.name+"? Teraz jeszcze bardziej chcę dotrzeć do prawdy, ale i tak już wyciągnęliśmy ze wszystkich wszystko, co tylko się dało.";
			link.l1 = "Jeśli gdziekolwiek są odpowiedzi, to na Wyspie Sprawiedliwości – nigdzie indziej nie zostało już ludzi, chyba że za oceanem, którzy choćby przelotnie znali twoich rodziców. Myślę, że warto jeszcze raz porozmawiać z Aurélie Bertin – może przypomni sobie coś jeszcze, czego moglibyśmy się uchwycić.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "Ale co właściwie chcesz się od niej dowiedzieć? Wydaje się, że i tak powiedziała nam już wszystko, co wiedziała.";
			link.l1 = "Opowiedziała nam to, o co ją pytaliśmy, i całkiem możliwe, że pominęła jakiś ważny szczegół. Może twój ojciec miał bliznę na twarzy, albo brakowało mu któregoś palca u ręki... Wątpię, by człowiek, który wymyślił te wszystkie sztuczki ze zmianą nazwy statku i, być może, własnego imienia, mógł tak po prostu zginąć bez śladu na wyspie albo w lochach kastylijczyków.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "Chyba masz rację...";
			link.l1 = "A jeśli zdecydujemy się kontynuować poszukiwania – już nie na zakurzonych półkach Admiralicji, ale tutaj, na Archipelagu, będziemy potrzebować czegoś więcej niż tylko imienia, i to jeszcze fałszywego.";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "Wiesz, aż mam ciarki na całym ciele od tego wszystkiego, tak, co nie. Sama nie wiem, czy to przez to, jakie to wszystko... ekscytujące, czy przez myśl, że mój ojciec mógł wcale nie różnić się od tego drania z plantacji Bishopa.";
			link.l1 = "Tak czy inaczej, obiecuję, że zrobimy wszystko, co w naszej mocy, żeby się we wszystkim połapać. Tak, co nie? Więc nie traćmy czasu. Ruszajmy!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "Chodźmy już, "+pchar.name+", nie będziemy niepotrzebnie tracić czasu, tak, co nie?";
			link.l1 = "Mam nadzieję, że Aurélie jest w swojej kajucie i nie będziemy musieli przeszukiwać całej Wyspy w jej poszukiwaniu...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "Wygląda na to, że znowu nam się nie poszczęściło, tak, co nie? I gdzie ona mogła się podziać?";
			link.l1 = "Mam nadzieję, że choroba nie odzyskała znowu władzy nad jej umysłem...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "O, znowu tu jesteście. No, witajcie... O co chodzi, znowu potrzebujecie Aurélie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "Nie można ci odmówić sprytu, Jillian. Nie wiesz przypadkiem, gdzie ona jest?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "W kościele, miała się spowiadać. Jeśli się pospieszysz, to ją tam zastaniesz.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "No skoro już się spowiada, to na pewno jest przy zdrowych zmysłach i pamięci, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "Trudno powiedzieć... Ostatnie trzy dni jest jakaś nieobecna, nie może sobie znaleźć miejsca. Wie pan, strasznie się czymś przejęła, jak tylko zobaczyła maszty waszego statku za zewnętrznym pierścieniem.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "Ciekawe, z jakiego powodu, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "No cóż, pewnie odpycha ją sama myśl, że może znowu zostać przez ciebie wypytana. Ale kiedy to ciebie obchodziły cudze problemy, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "Nie waż się rozmawiać ze mną w takim tonie, Jillian. Tym razem ci wybaczę, ale tylko spróbuj powiedzieć coś takiego ponownie...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "Ależ nerwowa z niej osoba, jak coś nie po jej myśli, prawda?";
			link.l1 = "Lepiej jej nie prowokować bez potrzeby, "+npchar.name+". Wiecie przecież, że ona nie nosi szpady tylko dla ozdoby, tak, co nie?";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "I pozwolilibyście, żeby coś takiego się stało, "+pchar.name+"?";
			link.l1 = "Po prostu nie widzieliście Mary w walce, "+npchar.name+". Inaczej nie łudziliby się, że ktoś albo coś może ją powstrzymać. Jeszcze się zobaczymy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "Pewnie chcesz mnie o coś zapytać, "+pchar.name+", tak, co nie...";
			link.l1 = "Szczerze mówiąc, niezbyt mnie obchodzi, co się między wami wydarzyło, choć domyślam się, jak miała na imię ta kotka. A raczej jak się nazywała. Bardzo chcesz o tym pogadać?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "Nie dogadaliście się z Jillian? A może raczej... o kogoś poszło?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "Hmm, tak naprawdę, nie.";
			link.l1 = "Jak powiesz. A teraz chodźmy szukać Aurélie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "Ta mokra kobieta nigdy mi nie wybaczy, że Alan wybrał mnie zamiast niej. Choć mogłaby – biorąc pod uwagę, że już go nie ma... Szczerze mówiąc, "+pchar.name+", nie bardzo chciałabym o tym rozmawiać, tak, co nie.";
			link.l1 = "Jak powiesz, kochana. To chodźmy szukać Aurélie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", Mary! Znowu jesteś na Wyspie, ale radość, tak, co nie!";
			link.l1 = "Miło widzieć, że jesteście w dobrym zdrowiu, "+npchar.name+". Tak naprawdę przyszliśmy na Wyspę, żeby jeszcze raz z wami porozmawiać. Ale nie martwcie się, to nie zajmie dużo czasu.";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "Och, młodzi ludzie, wcale nie żałujecie starej kobiety. Ale czułam, że pan przyjdzie. To znowu o twoich rodzicach, tak, Mary?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialog("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "Proszę cię, Aurélie. Wiem, że trudno ci to wspominać, biorąc pod uwagę, ile czasu już minęło, ale spróbuj jeszcze raz, proszę, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "Powiedziałam wam już wszystko, co pamiętam. Nie mam pojęcia, co jeszcze chcecie ze mnie wyciągnąć.";
			link.l1 = "Zadamy wam kilka pytań, "+npchar.name+". Proszę, postaraj się przypomnieć sobie cokolwiek – jakieś szczegóły albo detale. Nie będziemy na ciebie naciskać...";
			link.l1.go = "WildRose_Oreli_65";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_65":
			dialog.text = "Czy wy właśnie teraz się tym nie zajmujecie?";
			link.l1 = "Zrobiliście już dla nas tak wiele, "+npchar.name+"... Mamy tylko nadzieję, że w labiryntach twojej pamięci znajdzie się jeszcze coś, co bardzo nam pomoże.";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "Przeszliśmy długą drogę, "+npchar.name+". Nawet sobie nie wyobrażacie, ile wysiłku i czasu nas to kosztowało. Ale zabłądziliśmy, i tylko wy oraz wasza pamięć możecie wyprowadzić nas na ścieżkę prawdy.";
			link.l2.go = "WildRose_Oreli_66_2";
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "Pamięci... Co z niej zostało, z tej pamięci. Czasem rano nie mogę sobie przypomnieć, jak się nazywam, a wy chcecie ode mnie szczegółów – wydarzeń sprzed dwudziestu lat. No dobrze, pytajcie.";
			link.l1 = "Interesuje nas pan Kasper, ojciec Mary. Czy może pan sobie przypomnieć coś szczególnego w jego wyglądzie? Może miał bliznę na twarzy albo mocno utykał...";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "Pamięci... Co z niej zostało, z tej pamięci. Czasem rano nie mogę sobie przypomnieć, jak dojść do latryny, a wy chcecie ode mnie szczegółów o tym, co się działo dwadzieścia lat temu na tych wrakach. No dobrze, niech wam będzie, pytajcie.";
			link.l1 = "Interesuje nas pan Casper, ojciec Mary. Czy może pan sobie przypomnieć coś szczególnego w jego wyglądzie? Może miał bliznę na twarzy albo mocno utykał...";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "Och... Wydaje mi się, że już wspominałam, że widziałam go tylko w zupełnych ciemnościach, w ładowni 'Ceres Smithy', gdzie urządzili legowisko dla biednej Teresy. Na pewno nie utykał – przeciwnie, był bardzo żwawym mężczyzną.";
			link.l1 = "A jego wiek? Był młody czy już w latach?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "Nie nazwałabym go starcem... Ale nie zwracałam na niego szczególnej uwagi – bardziej martwiłam się o Teresę. Wyglądał, szczerze mówiąc, kiepsko – przypominał jakieś widmo. Zresztą, pamiętaj, że przez cały tydzień, kiedy jego żona była w ciąży, prawie w ogóle nie spał... Cały czas biegał po Wyspie, bez chwili wytchnienia.";
			link.l1 = "Żonę, znaczy, bardzo kochał. A ty przecież spędzałaś z nią dużo czasu, tak, co nie? Nic nie mówiła o mężu?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "Teresa ciągle o niego pytała. Dużo spała, czasem majaczyła, ale kiedy przychodziła do siebie, od razu pytała, gdzie on jest. I biedaczka bardzo, bardzo na niego czekała. Ale w najważniejszym momencie – on jednak nie przyszedł.";
			link.l1 = "Rozumiem. Najwyraźniej ich miłość była odwzajemniona... Cóż, dziękujemy ci, Aurélie. Bardzo nam pomogłaś.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "I to wszystko? Myślałam, że nasza rozmowa potrwa jeszcze z godzinę, tak, co nie?";
			link.l1 = "Obiecywaliśmy przecież, że nie będziemy was długo męczyć. Dbajcie o siebie, "+npchar.name+". Wszystkiego dobrego.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "Poczekajcie, młodzi ludzie! Mam dla was jeszcze coś... A właściwie – dla ciebie, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_72_a": //
			dialog.text = "No proszę, dziewczynko, weź... Gdy tylko zobaczyłam żagle twojego statku, zabrałam ten kapelusz, żeby o nim nie zapomnieć. Ale wyjść na przystań... nie odważyłam się.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialog("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "Co to jest, Aurélie? Kapelusz?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "Kapelusz twojej matki, Teresy. Miała go przy sobie, kiedy rozbitków przywieziono na 'Ceres Smithy'. Kiedy Teresa zmarła, podniosłam ten kapelusz z podłogi obok jej łóżka – tak, co nie, a potem o nim zapomniałam... Przypomniałam sobie dopiero dziś, podczas naszej rozmowy.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialog("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "Oreli... Przechowywałaś ją tyle lat! I... i nie wyrzuciłaś jej, nie sprzedałaś... Dziękuję, dziękuję ci! Nawet nie wiesz, jak bardzo to... cenne i ważne dla mnie, tak, co nie!";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "Wybacz, Mary – już dawno powinienem był ci ją oddać... Ale z moją pamięcią to już jak z dziurawym sitem – no i...";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialog("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "Lepszej chwili nie wymyślisz, Aurélie! Przymierzę ją od razu, tak, co nie?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "No i co, kochanie, jak ci się podobam?.. ";
			link.l1 = "Jesteś piękna. Tak, co nie, a kapelusz... jeszcze nie wyszedł z mody, więc też wygląda świetnie.";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "Naprawdę? Tak się cieszę, że ci się podoba, tak, co nie!";
			link.l1 = "Czy może być inaczej?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "Dzięki jeszcze raz, Aurélie – sprawiłaś, że ten dzień stał się trochę jaśniejszy! Wszystkiego dobrego, odpoczywaj.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "Czyli to jednak był Rupert. Rupert Northwood, tak, co nie.";
			link.l1 = "Oczywiście, że tak, kochana. Zrobił wszystko, żeby uratować żonę... albo ukochaną, nie wiem. To właściwie nie ma znaczenia. Najważniejsze, że teraz wiemy, kogo mamy szukać.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "A co się stało z prawdziwym Joshuą Casperem, kapitanem 'Cornwalla'?";
			link.l1 = "Dobre pytanie, ale teraz nie najważniejsze. Dlaczego Rupert nie wrócił po ciebie, skoro tak kochał Theresę – to jest o wiele ciekawsze. I to będzie pierwsze, o co go zapytamy. Jeśli w ogóle żyje i jeśli go znajdziemy. Jedno jest pewne – do floty nie wrócił. Nie miał powodu aż tak ryzykować.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "Co mogło go skłonić, żeby przyjąć imię Joshua Casper? Co się wydarzyło na pokładzie 'Cornwalla', który stał się 'Wranglerem'? Czy naprawdę mój ojciec jest przestępcą, "+pchar.name+"?";
			link.l1 = "Obawiam się, że takiej możliwości też nie można wykluczyć, "+npchar.name+". Powinniśmy być gotowi na absolutnie wszystko.";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "Nie chcę nawet o tym myśleć...";
			link.l1 = "Na razie musimy myśleć o czymś innym – gdzie go szukać. Mógł dołączyć do piratów albo przemytników. Albo zaszył się w jakimś mieście i nie wychyla się. Wszystko możliwe.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "I co proponujesz zrobić? Jak mamy go znaleźć? Wchodzić do każdej kolonii, wymawiać jego imię i liczyć, że ktoś coś słyszał o Rupercie Northwoodzie?";
			link.l1 = "Albo Joshua Casper. Mógł całkiem dobrze dalej żyć pod nazwiskiem swojego dawnego kapitana - najprawdopodobniej już nieżyjącego. Ale to wiązało się z pewnym ryzykiem, bo zaginionego brygu mogli zacząć szukać. Zwłaszcza że na nim była skrzynia srebra, przeznaczona dla garnizonu Providence.";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "Masz rację, tak, co nie?";
			link.l1 = "A ten rzekomo zaginiony u wybrzeży Azorów Rupert Northwood raczej nie wzbudziłby niczyjego zainteresowania. Choć niewątpliwie jest tu jeszcze nad czym się zastanowić.";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "Ile jeszcze czasu na to zmarnujemy, "+pchar.name+"?! Przecież on może być gdziekolwiek, w którejkolwiek kolonii, tak, co nie!";
			link.l1 = "O ile w ogóle przeżył. Ale się z tobą nie zgadzam. Mało prawdopodobne, by mówił płynnie po hiszpańsku, więc na Kubie ani na Hispanioli raczej nie miałby czego szukać. Mógł znać francuski i popłynąć na Tortugę albo do którejś z kolonii na Małych Antylach. Albo osiadł na Zachodnim Mainie, pod skrzydłami rodaków. Rzeczywiście, możemy stracić na jego poszukiwania wiele miesięcy — i wcale nie jest pewne, że go znajdziemy.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "Ale nie chcę się poddać, "+pchar.name+". Tylko nie teraz, kiedy już tyle się dowiedzieliśmy, tak, co nie!";
			link.l1 = "Nie o to mi chodziło, tak, co nie? "+npchar.name+". Nie musimy szukać go sami - lepiej zwrócić się do kogoś z kontaktami. Raz już to zadziałało, tak, co nie? Czemu nie spróbować jeszcze raz?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "Proponujesz znowu poprosić o pomoc opata? Wydawało mi się, że dał nam do zrozumienia, że na dalszą pomoc w tej sprawie nie mamy co liczyć, tak, co nie?";
			link.l1 = "To byłoby już zbyt bezczelne wobec staruszka, masz rację.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "Ale do kogo więc mamy się zwrócić? Kto ma pieniądze i kontakty na takie przedsięwzięcie?";
			link.l1 = "Cóż, koszty poszukiwań z pewnością spadną na nas. A jeśli chodzi o kontakty... Myślę, że mógłby nam pomóc Fadiej Moskowit. Na pewno zna kompetentnych ludzi, których można by wysłać do kolonii. Albo przynajmniej podpowie, do kogo się zwrócić.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "Czyli ruszamy do Bas-Ter?";
			link.l1 = "Tak, zajrzyjmy do naszego przyjaciela. To chyba nie jest dla niego najtrudniejsze zadanie, tak, co nie?";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "Podniesiemy kotwicę jutro, co powiesz? Chciałabym spędzić resztę tego dnia i noc tylko z tobą, na 'Ceres Smithy'.";
			link.l1 = "Od takich propozycji się nie odmawia, kochana. Zdecydowanie zasłużyliśmy na chwilę odpoczynku.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "Co, już opuszczacie Wyspę? Nawet na pogrzeb nie zostaniecie, tak, co nie?";
			link.l1 = "Pogrzeb?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "A, tak nie wiecie. Rozumiem... Aurélie Bertin zmarła tej nocy.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "Co?! Niemożliwe – przecież jeszcze wczoraj z nią rozmawialiśmy i była cała i zdrowa. Albo ktoś ją...";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "Nie, Mary. Aurelie zmarła we śnie. Przyszłam dziś do niej, żeby przynieść maści na stawy, które zrobił brat Julian – i wtedy ją znalazłam. Leżała na łóżku, z dziwnym uśmiechem na twarzy. Ale już blada i zimna.   Przez ostatni tydzień staruszka była jakaś nieobecna, nawet pomyślałam, że choroba, którą wypędził czarny czarownik, wróciła. Ale myślała całkiem jasno i chyba nie majaczyła.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "Przynajmniej nie cierpiała, tak, co nie.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "Zostaniecie więc na pogrzeb? Odbędzie się jutro, na najdalszej rafie – tam jest wystarczająco głęboko i kraby tam nie zaglądają.";
			link.l1 = "Zostaniemy, Gillian. Aurélie zrobiła dla Mary tak wiele, że nie możemy postąpić inaczej. Jeśli nikt nie ma nic przeciwko, zorganizujemy procesję na naszym statku. Pochowamy ją na otwartym morzu, z wszelkimi honorami.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "Nikt się nie będzie sprzeciwiał. To wygodniejsze i w końcu bezpieczniejsze, niż łazić po wrakach.";
			link.l1 = "W takim razie zajmijcie się organizacją pogrzebu – Mary wam pomoże. Ja muszę jeszcze z kimś porozmawiać...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "I znowu tu jesteś, mój drogi przyjacielu! Co mogę dla ciebie zrobić tym razem?";
			link.l1 = "Cześć, "+npchar.name+". Słyszałeś już o tym, co wydarzyło się tej nocy?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "Chodzi ci o śmierć Aurelii? Widzę, że o to pytasz. Słyszałam, oczywiście. Przecież mieszkała na 'Pluto', a to praktycznie teren Rivadów. No i ludzie na innych statkach tylko o tym gadają.";
			link.l1 = "Widziałam się z nią ledwie wczoraj i była w dobrym zdrowiu — no, chyba że przez ostatni tydzień czymś się wyraźnie martwiła. A kiedy zobaczyła nasz statek, zupełnie się roztrzęsła.";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "Człowiek czuje, kiedy rzeka jego życia wysycha. Jedni okazują to wszystkim wokół, inni skrywają w sobie, ale każdy to odczuwa – prędzej czy później, zwłaszcza ci, którzy potrafią słuchać własnego serca.";
			link.l1 = "Wydawało mi się, że była zdrowa, prawie jak młoda łania, "+npchar.name+". I coś tu się nie zgadza...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "I mimo wszystko, ona wcale nie była u kresu sił, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "Przyjacielu, umysł i ciało to rzeczy zupełnie różnego porządku. Umysł kieruje ciałem, czasem ciało próbuje przejąć kontrolę nad umysłem. Są ze sobą ściśle powiązane, ale jednak nie stanowią jednej całości. Człowiek może wyglądać na całkowicie zdrowego z zewnątrz, ale jego dusza już kroczy ścieżką śmierci.";
			link.l1 = "Jesteś bystry, mój przyjacielu, naprawdę bystry. Jeśli poczujesz, że prawda krąży gdzieś w pobliżu, rzucisz się za nią jak lew za zebrą — i będziesz ją ścigać, dopóki jej nie dopadniesz. Zrozumiałem to od razu, w chwili, gdy cię zobaczyłem.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "Przyjacielu, umysł i ciało to rzeczy zupełnie różnego porządku. Umysł kieruje ciałem, czasem ciało próbuje przejąć kontrolę nad umysłem. Są ze sobą ściśle powiązane, ale jednak nie stanowią jednej całości. Człowiek może wyglądać na całkowicie zdrowego z zewnątrz, ale jego dusza już kroczy ścieżką śmierci.";
			link.l1 = "Wiesz, przyszło mi do głowy, że Aurelie jakby na nas czekała, wiedziała, że do niej przyjdziemy. Przecież staruszka mogła umrzeć dzień wcześniej albo później, ale stało się to niemal od razu po tym, jak powiedziała nam coś ważnego o ojcu Mary."link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "Jesteś bystry, mój przyjacielu, bardzo bystry. Jeśli poczujesz, że prawda krąży gdzieś w pobliżu, rzucisz się za nią jak lew za zebrą – i będziesz ją ścigać, aż w końcu ją dopadniesz. Zrozumiałem to od razu, w tej samej chwili, gdy cię zobaczyłem.";
			link.l1 = "Nie... Poczekaj. Ten rytuał, który odprawiłeś w ładowni 'Protektora'... on nie spowolnił choroby Aurelii, prawda? Więc co właściwie wtedy zrobiłeś?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "Można zasypać rzekę kamieniami, ale to nie powstrzyma jej biegu. Wiedziałem, że potrzebujecie od Aurelii czegoś ważnego – i że nie dotrzecie do tego od razu. Ale ile czasu zajmie wam ta droga, nie było mi dane wiedzieć. Dlatego wzniosłem tamę, skupiając całą jej życiową siłę na powstrzymaniu choroby, aż do chwili, gdy spełni swoje przeznaczenie. I gdy tylko to się stało, tama runęła...";
			link.l1 = "Więc wychodzi na to, że Aurélie... w chwili śmierci była zupełnie nie sobą, nie była świadoma siebie – tak jak myśleliśmy?";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "Skupiła całą swoją siłę na tym, by zachować zdrowy umysł i jasną pamięć, a gdy to przestało być potrzebne, choroba uderzyła w nią niczym ogromna fala, porywając ją do doliny śmierci. Czy jej odejście było łagodne, czy też odeszła do waszego Boga, dręczona duchami przeszłości i przerażającymi koszmarami — nie potrafię powiedzieć, bo nie jest mi to dane wiedzieć.";
			link.l1 = "Dobrze wiedziałeś, do czego to doprowadzi, tak, co nie? Czemu, do diabła, nie ostrzegłeś mnie o konsekwencjach?! No, mów!";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "Wiedziałeś przecież, co robisz, "+npchar.name+". Czemu nie uprzedziłeś mnie, do czego to może doprowadzić?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "Bo postanowiłem ci pomóc, mój przyjacielu, dowiedzieć się tego, czego potrzebowaliście, a jej – wypełnić swoje przeznaczenie. Gdybym ci powiedział, co ją czeka, mógłbyś się na to nie zdecydować – i Aurélie zabrałaby swoje tajemnice ze sobą na tamten świat. Jaki byłby z tego pożytek? Umarłaby na próżno. Jak antylopa powalona przez lwa, ale przez niego nie zjedzona, tylko zostawiona na pastwę sępom.";
			link.l1 = "Przeznaczenie, pożytek... Jesteś prawdziwym sędzią losu, "+npchar.name+". Bóg w ludzkiej postaci.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "Bo postanowiłem ci pomóc, mój przyjacielu, dowiedzieć się tego, czego potrzebowaliście, a jej – wypełnić swoje przeznaczenie. Gdybym ci powiedział, co ją czeka, mógłbyś się na to nie zdecydować – i Aurélie po prostu zabrałaby swoje tajemnice ze sobą na tamten świat. Jaki byłby z tego pożytek? Umarłaby na próżno. Jak antylopa zaduszona przez lwa, ale nie zjedzona przez niego, tylko zostawiona na pastwę sępom.";
			link.l1 = "Przeznaczenie, pożytek... Jesteś prawdziwym sędzią losu, "+npchar.name+". Bóg w ludzkiej postaci.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "Słyszę w twoim głosie niezadowolenie, mój przyjacielu. Ale nie, wcale nie uważam się za boga – i uwierz, nawet on nie jest wszechmocny. Ani ten, w którego wierzycie wy, ani ci, którym my oddajemy cześć. Bogowie nie są w stanie dać człowiekowi większej siły, niż ta, którą został obdarzony przy narodzinach. My, szamani, potrafimy jedynie skierować ją w tę czy inną stronę – i nic ponadto.";
			link.l1 = "I ty skierowałeś ich na drogę, która skazała ją na zgubę...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "Jedynie wskazałem Aurélie drogę, którą idąc, pomogła Mary — osobie, z którą była związana od samego jej urodzenia. W końcu twoja towarzyszka przyszła na świat na jej oczach. Proszę, nie patrz na mnie jak na szaleńca. Wszak nie powiesz chyba, że dostrzegłeś we mnie dobrodusznego czarodzieja, który jednym ruchem ręki potrafi cofnąć bieg czasu?";
			link.l1 = "Nie wiem, co ci powiedzieć, "+npchar.name+". Może to wszystko naprawdę nie było na darmo. Ale tak nie można było postąpić. Powinieneś był mi powiedzieć, a ja – podjąć decyzję. Jednak tego, co się stało, nie da się cofnąć. No cóż, trzymaj się, przyjacielu.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "Nie tak wyobrażałam sobie nasze ostatnie spotkanie, mój przyjacielu...";
			link.l1 = "Skąd wziąłeś, że to ona jest ostatnia?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "Niektóre rzeki wpadają do innych, stając się ich częścią, inne wysychają, a jeszcze inne – tak jak nasza – kończą swój bieg wielkim wodospadem...";
			link.l1 = "Znowu zagadki, Chimiset? Wystarczy mi na dziś. Myślę, że jeszcze się zobaczymy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "Tak i myślałam, że cię tu znajdę, tak, co nie? Czego chciałeś od Chimiceta, "+pchar.name+"? Co ci powiedział?";
			link.l1 = "Nie tego się spodziewałam – a raczej, nie tego chciałam usłyszeć. Ale gdzieś w głębi przeczuwałam to.";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "Opowiesz mi, tak, co nie?";
			link.l1 = "Nie, "+npchar.name+". Tym razem - nie. Wszystko, co zostało powiedziane w kajucie 'Protektora', tam pozostanie, między mną a Chimisetem.";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "Dawno nie słyszałam takiej stanowczości w twoim głosie, "+pchar.name+". Ale dobra, mamy też inne zmartwienia, tak, co nie. Pogrzeb odbędzie się jutro, o zachodzie słońca, o siódmej.";
			link.l1 = "Chodźmy, pomogę wam wszystko przygotować.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "Wygląda na to, że wszyscy, którzy chcieli, już się zebrali, tak, co nie?";
			link.l1 = "Myślałem, że będzie tu więcej ludzi. Przynajmniej spośród tych spokojnych.";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "No, Kuranaia nikt nie zapraszał, tak samo jak Rivadose. Abbott, wstrętny zarozumiały indor, oświadczył, że ma ważniejsze sprawy niż pogrzeb katoliczki, coś podobnego wymamrotali też Lauderdale i Musket. Cassel, ten prostak, po prostu powiedział, że nie przyjdzie. A wszyscy inni są tutaj.";
			link.l1 = "Niektóre rzeczy zawsze będą poza moim zrozumieniem. No, niech Bóg ich osądzi. A oto brat Julian... Teraz wszystko się zacznie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "Chociaż nasze serca przepełnione są żalem, podziękujmy Bogu za wszystkie dobra, którymi obdarzył zmarłą Aurélie, i zawołajmy: Dziękujemy Ci, Boże, Ojcze nasz\n"+"Przez wszystkie lata i dni, które Aurélie spędziła  z nami\n"+"Za wielki dar świętego chrztu, dzięki któremu Aurélie stała się Twoją córką\n"+"Za zdolności i wiedzę, którymi ją obdarzyłeś\n"+"Za jej służbę dobru rodziny i innych ludzi\n"+"Za jej cierpliwość wobec naszych błędów\n"+"Módlmy się do Boga, aby przyjął do swej chwały naszą zmarłą siostrę Aurélie, i zawołajmy: Prosimy Cię, Panie\n"+"Niech dobre uczynki Aurelii przyniosą obfite owoce\n"+"Niech to, co ona zaczęła, zostanie dokończone\n"+"Wybacz jej grzechy, które popełniła\n"+"Niech pamięć o niej żyje w naszych sercach\n"+"Módlmy się do Boga, aby umocnił wiarę i nadzieję cierpiących, i wołajmy do Niego: Panie, pomnóż naszą wiarę\n"+"Przez Syna Twego, który stał się człowiekiem\n"+"Przez Twojego Syna, Jezusa Chrystusa, który nas nieskończenie umiłował\n"+"Przez Syna Twego, który przyjął śmierć za nasze grzechy i zmartwychwstał dla naszego zbawienia\n"+"Przez Syna Twego, który otworzył nam drogę do nieba\n"+"Wraz ze wszystkimi wiernymi, którzy poprzedzili nas w niebiańskiej ojczyźnie, pomódlmy się tak, jak nauczył nas Zbawiciel.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "Wszechmogący Boże, wysłuchaj naszych modlitw zanoszonych z wiarą w Twego Zmartwychwstałego Syna i umocnij naszą nadzieję, że razem ze zmarłą służebnicą Twoją i my wszyscy dostąpimy zmartwychwstania. Przez Chrystusa, Pana naszego, Twojego Syna, który z Tobą żyje i króluje w jedności Ducha Świętego, Bóg przez wszystkie wieki wieków. Amen.";
			link.l1 = "Boże, Ojcze Wszechmogący, tajemnica krzyża jest naszą siłą, a Zmartwychwstanie Twojego Syna — fundamentem naszej nadziei; uwolnij swoją zmarłą służebnicę z więzów śmierci i dołącz ją do grona zbawionych. Przez Chrystusa, Pana naszego. Amen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", chodźmy szybko do kajuty, tak, co nie? Zaraz się rozpłaczę... Nie chcę, żeby ktoś to widział.";
			link.l1 = "Oczywiście, "+npchar.name+". Chodźmy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "Dopiero po śmierci człowieka zaczynasz go naprawdę doceniać – słyszałeś coś takiego, "+pchar.name+"?";
			link.l1 = "Tak – i nie raz.";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "Erik lubił to powtarzać. Myślę, że mówił o swojej rodzinie. Nigdy go o nią nie pytałam – wydawało mi się, że jeszcze zdążę. A potem on umarł, tak, co nie. Teraz odeszła też Aurélie – i dopiero teraz zrozumiałam, jak rzadko poświęcałam jej czas i uwagę. Znacznie rzadziej, niż na to zasługiwała.";
			link.l1 = "To nie twoja wina. Nie jest nam dane wiedzieć, kiedy Pan zabierze naszych bliskich do siebie. I nigdy nie spędzamy z nimi wystarczająco dużo czasu. Nigdy.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "Może i tak, tak, co nie? A jeszcze Erik często powtarzał – i Aurélie się z nim zgadzała – że każde miejsce to przede wszystkim ludzie. Nie domy, drzewa, drogi – tylko ludzie. Kiedy myślisz o jakimś punkcie na mapie, przypominasz sobie najpierw właśnie tych, którzy tam mieszkają. Albo mieszkali.";
			link.l1 = "Nigdy się nad tym nie zastanawiałam. Ale chyba Eric miał rację – w końcu co wart jest dom, do którego wchodzisz i już nie spotkasz ojca ani brata?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = "Założyłbym się, że nie. Kiedy wspominam na przykład Paryż, to w głowie pojawiają mi się obrazy uliczek, zapachy... Z ludzi pamiętam tylko nielicznych – reszta prawie całkiem zniknęła z pamięci, choć minęło zaledwie kilka lat.";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "Myślę, że Eric i Aurélie rozmawiali o Wyspie, tak, co nie? I o tych ludziach, którzy tu mieszkali – dawno, dawno temu. Byłam wtedy mała i tego nie rozumiałam, ale teraz – pojęłam to w pełni. Przecież dłużej ode mnie mieszkają tu Antonio, Cécile... i niektórzy Rivadoci, jak Chimiseta – ale z żadnym z nich nigdy nie byłam blisko. Reszta: Eric, Aurélie, Alan i wielu innych – nie żyją.";
			link.l1 = "Rozumiem. Świat stał się... odrobinę mniejszy, tak, co nie?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "Myślę, że Eric i Aurélie rozmawiali o Wyspie, tak, co nie. I o tych ludziach, którzy tu mieszkali – dawno, dawno temu. Byłam wtedy mała i nie rozumiałam tego, ale teraz – pojęłam to w pełni. Przecież dłużej ode mnie mieszkają tu Antonio, Cécile... i niektórzy Rivadose, jak Chimiseta – ale z żadnym z nich nigdy nie byłam blisko. A reszta: Eric, Aurélie, Alan i wielu innych – nie żyją.";
			link.l1 = "Rozumiem. Świat stał się... odrobinę mniejszy, tak, co nie?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "Raczej opustoszał. Ten świat – to, co jest wewnątrz zewnętrznego pierścienia. Opustoszał, tak, co nie? A wkrótce może całkiem zniknąć.";
			link.l1 = "O czym ty mówisz, Mary?.";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "Czy nie poczułeś tego, "+pchar.name+"? Teraz, kiedy staliśmy przy grobie Aurelii.";
			link.l1 = "Co dokładnie?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "Nie wiem, jak to wyjaśnić. Wiesz, jak pachnie powietrze przed burzą? Przypomnij sobie – kiedy pojawiłeś się tu po raz pierwszy, jaka napięta była atmosfera... Wszyscy byli gotowi rzucić się sobie do gardeł, wielu wydawało się, że czuć proch i krew. Po tym, jak zabiłeś Chada, wszystko się zmieniło – jakby oddychało się lżej... Ale teraz – to uczucie znowu wróciło.";
			link.l1 = "Tak, też coś takiego poczułam. Ale może to przez tę atmosferę? W końcu to pogrzeb...";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "Jesteś przemęczona, "+npchar.name+". Odpoczniesz – i od razu poczujesz się lepiej. Tak, co nie? No i czy na pogrzebie można czuć się inaczej?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "Kiedy oddawaliśmy morzu Erika i wielu innych mieszkańców Wyspy – czegoś takiego nie było, mówię ci. Czuło się jakieś... zjednoczenie. A dziś – niektórzy patrzyli na siebie niemal jak wilki, choć modlili się tą samą modlitwą.";
			link.l1 = "Masz na myśli Leightona i Donalda?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "Kiedy oddawaliśmy morzu Erika i wielu innych mieszkańców Wyspy – tak nie było, mówię ci. Czuło się jakieś... zjednoczenie. A dziś – niektórzy patrzyli na siebie niemal jak wilki, choć modlili się tą samą modlitwą.";
			link.l1 = "Masz na myśli Leightona i Donalda?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "Więc też to zauważyłeś, tak, co nie.";
			link.l1 = "Dexter nerwowo reaguje na zakusy Greenspiego w sprawie ćwiczeń – a jakże inaczej?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "To się dobrze nie skończy, tak, co nie?";
			link.l1 = "Jeśli tak, to dziś odbył się nie tylko pogrzeb Aurelii Bertin, ale też tego... Miasta Utraconych Okrętów.";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "Miasto Utraconych Okrętów?";
			link.l1 = "Wybacz, Mary, ale jakoś nie mogę nazwać tego miejsca Wyspą Sprawiedliwości, tak, co nie?";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "Teraz, kiedy zobaczyłam świat i zrozumiałam, jaki jest ogromny, to miejsce wydaje mi się... więzieniem, tak, co nie. Trudno uwierzyć, że tutaj dorastałam.";
			link.l1 = "I nie mogę uwierzyć, że wśród tych wraków statków mogła rozkwitnąć tak dzika, piękna róża jak ty.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "Chcę pożegnać się z tym miejscem, "+pchar.name+"... Chyba już nigdy tu nie wrócimy, tak, co nie.   Nie chcę wracać.   Nie chcę na własne oczy zobaczyć tego, co tu może się wydarzyć.";
			link.l1 = " Pogadam z Eddiem i Donaldem. Może uda się trochę ostudzić ich zapał. ";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "Nie rozumiesz... To tylko odwlecze nieuniknione, więc nie warto się starać. Przyjdzie dzień, kiedy tu wrócimy – a tutaj\nTak będzie lepiej, "+pchar.name+", tak... Nic mnie tu już nie trzyma.";
			link.l1 = "Jak powiesz, kochana. Skończymy wszystkie sprawy – i odejdziemy stąd na zawsze.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "Rupert Casper? Joshua Northwood, tak, co nie?";
			link.l1 = "Myślał"+GetSexPhrase("em","am")+" o tym przez całą drogę, "+npchar.name+". I doszedł"+GetSexPhrase("em","am")+" do wniosku, że twój ojciec raczej nie ukrywałby się pod imieniem i nazwiskiem, których już wcześniej używał. Z drugiej strony, mógł nie chcieć całkiem zrezygnować z prawdziwego imienia lub nazwiska — co, jeśli w niewłaściwym momencie nie zareaguje na obce?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "Mógł się nazywać jakkolwiek, tak, co nie?";
			link.l1 = "Mógł, oczywiście. I może właśnie tak zrobił. Jeśli przeżył na Kubie, dokąd dotarł na tartanie przemytników. Jeśli dotarł, a nie stał się pożywką dla krabów z Wyspy Sprawiedliwości. Teraz pozostaje nam tylko czekać – na szczęście nie tak długo, jak wtedy. Myślę, że miesiąc damy radę wytrzymać bez trudu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "Mój ojciec żyje, "+pchar.name+". A przecież ja zawsze to wiedziałam, tak, co nie!";
			link.l1 = "Tak jak i ja, kochana. No cóż, czas już spotkać się z tym Jérômem – i to jak najszybciej, tak, co nie?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "W końcu dotarliśmy, tak, co nie. I co teraz, "+pchar.name+"?";
			link.l1 = "Trzeba znaleźć Jérôme’a. Albo wyleguje się w pokoju w tawernie, albo wynajmuje jakiś domek – na to na pewno ma pieniądze.";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "Biorąc pod uwagę, ile zapłacił mu Fadiej... Myślę, że na pewno wolałby tę drugą opcję.";
			link.l1 = "Zgadzam się. Możemy wypytać o niego właściciela 'Szklanego Oka', albo popytać zwykłych mieszkańców. Chodźmy, czas jest cenny.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "No proszę, no proszę... A oto i nasze gołąbeczki. Chłopaki, bierzemy się do roboty – i składamy mu raport.";
			link.l1 = "Jérôme Sauvernier? Co tu się, do diabła, dzieje?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "Wy sukinsyny, kh-kh. No nic...";
				link.l1 = "Radziłabym ci ugryźć się w język, jeśli ci życie miłe... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "To też. A teraz gadaj: do diabła, czemu się na nas rzuciliście – i to jeszcze razem z Souvernie...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "Wasz Sovereign to chciwy, tchórzliwy drań. Wystarczyło, żeby Casper mu porządnie przyłożył, a potem obiecał trochę grosza – od razu grzecznie nabazgrał ten liścik, kcha-kcha...";
			link.l1 = "Więc naprawdę go znalazł.";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "Znalazłem, znalazłem. Tak że niedługo zdechniesz. Tak samo jak twoja dziewczyna. Kasper was oboje na paski potnie, he-he. I tak już jestem trupem, ale pomogę ci znaleźć twoją śmierć. Szkoda, że nie usłyszę, jak będziecie błagać o litość, gdy traficie w jego ręce...";
			link.l1 = "Tak, długo już nie pożyję, to prawda. Więc mów szybciej, zanim wyzionę ducha.";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "Chcecie go spotkać – ruszajcie do zatoki Chetumal, tam właśnie przebywa. Szukać go nie trzeba, sam was znajdzie.";
			link.l1 = "No to świetnie. Teraz możesz umierać ile dusza zapragnie. A ja muszę już iść.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "Mam taką nadzieję. A teraz idź do diabła.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "O Boże, "+pchar.name+"... Nie mogę w to uwierzyć, po prostu nie mogę, tak, co nie! To zrobił mój ojciec?!";
			link.l1 = "Chyba tak, "+npchar.name+". Nie wiem, co nim kierowało i kim on, do diabła, w ogóle jest... Ale raczej to nie może być jakiś inny Rupert Casper. Takie przypadki się nie zdarzają.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "I co teraz zrobimy?   Co mu powiem, patrząc mu w oczy?";
			link.l1 = "Najpierw trzeba do niego dotrzeć. Najpewniej sam się postawił poza prawem, skoro jego poszukiwania wywołały... aż tak nerwową reakcję. Ale, jakby nie było, to wciąż twój ojciec. Na którego poszukiwania straciliśmy mnóstwo wysiłku, czasu i pieniędzy.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "A co jeśli nawet nie będzie chciał z nami rozmawiać? Dlaczego kazał nas zabić?";
			link.l1 = "Chociażby dlatego, że mógł nawet nie wiedzieć, kto dokładnie go szuka. Fadiey mógł po prostu podać imię, a szczegóły dotyczące ciebie przemilczeć. W przeciwnym razie, myślę, nie musielibyśmy teraz brudzić ostrzy krwią.";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "I co teraz? Ruszamy do zatoki Chetumal? Ale jeśli zastawił na nas pułapkę tutaj... kto wie, co czeka nas tam?";
			link.l1 = "Mamy przewagę czasową, zanim on się dowie, co tu zaszło. Skorzystajmy z niej. Popłyniemy statkiem do zatoki, a na pomoc wyślemy oddział pod dowództwem jednego z oficerów, który ruszy lądem.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "Brzmi rozsądnie, tak, co nie? Ale kto stanie na jego czele?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Tichingitu. W walkach na lądzie jest zahartowany. Nikt nie poradzi sobie lepiej od niego.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Klod. On oczywiście nie będzie zachwycony, tak, co nie, ale nic – przeżyje.";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Hercule. On to wie, jak się takie sprawy załatwia.";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Tommy. Nawet jeśli coś pójdzie nie tak, ten facet sobie poradzi, uwierz mi.";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Longway. On już nie raz tropił wroga w dżungli.";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Alonso. Macha szablą jak mało kto, tak, co nie, i głowę też ma nie od parady.";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Tichingitu uważnie słuchać, kapitan "+pchar.name+".";
			link.l1 = "Mój przyjacielu, czeka cię odpowiedzialne zadanie. W zatoce Chetumal ukryła się banda łotrów. Musisz ich wytropić i zniszczyć. My podpłyniemy naszym statkiem od strony morza.";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "Ty masz poprowadzić oddział naszych ludzi przez dżunglę, żeby wyjść tym łajdakom na tyły. Masz do mnie jakieś pytania?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "U Indianina nie ma pytań. Jutro w południe oddział będzie na miejscu i tam będzie czekać w zasadzce.";
			link.l1 = "Bardzo dobrze, Tichingitu. Powodzenia.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = "Wzywałeś, kapitanie?";
			link.l1 = "Mam dla ciebie sprawę, Claude.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "Trzeba zebrać oddział ludzi i poprowadzić go przez dżunglę do zatoki Chetumal. Tam czeka na nas banda pewnego Ruperta Caspera. Szykują nam niemiłą niespodziankę. W rzeczywistości to my ją im zrobimy, a dokładniej – ty. Załadujesz na nich na mój sygnał. Pytania?";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "Nienawidzę włóczyć się po dżungli. Ale, jak to mówią, rozkaz to rozkaz. Spotkamy się na miejscu, myślę, że gdzieś jutro w południe.";
			link.l1 = "Powodzenia, Claude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = "Słucham cię, kapitanie.";
			link.l1 = "Hercule, mam dla ciebie robotę.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "Trzeba komuś wpakować parę kul w tę rozbrykaną łepetynę? To ja zawsze, przecież wiesz.";
			link.l1 = "Prawie zgadłeś. Musisz poprowadzić oddział naszych ludzi z okrętu, przeprowadzić ich przez dżunglę do zatoki Chetumal. Tam urządzicie zasadzkę na bandę, która, jak sądzę, będzie tam na nas czekać.";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "Myślałem, że mówisz o czymś poważnym, kapitanie. A ty prawie o wyprawie do tawerny zacząłeś gadać. Jutro w południe możesz być pewny, że będziemy na miejscu.";
			link.l1 = "Widzimy się już na miejscu. Powodzenia, Herculé.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = "Hej, kapitanie, czemu jesteś taki poważny – jakbyś szedł na pogrzeb, tak, co nie?";
			link.l1 = "Żartujesz sobie, Tommy? Chcesz, żebym ja też zażartowała? Wypłaty za ten miesiąc nie dostaniesz. I za następny też nie. Czemu się tak spiąłeś?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "I nawet zażartować nie można...";
			link.l1 = "Wszystko w swoim czasie, Tommy. Tego musisz się jeszcze nauczyć, tak, co nie? A teraz słuchaj mnie uważnie: zbierz drużynę i ruszaj przez selwę do zatoki Chetumal. Jak dotrzecie – czekajcie na mój rozkaz.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "Przebijać się przez dżunglę? Dotrzemy tam najwcześniej jutro w południe, tak, co nie?";
			link.l1 = "Więc widzimy się tam jutro w południe. Bez rozkazu nie wchodzić do walki, nie opuszczać pozycji. Jasne? Widzę, że jasne. A teraz – do dzieła.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Longway słucha was, panie kapitanie.";
			link.l1 = "Kolego, mam dla ciebie zadanie.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "Musisz poprowadzić oddział naszych ludzi, którzy przez dżunglę dotrą do zatoki Chetumal. Tam może dojść do starcia z wrogiem, więc przygotuj swoich ludzi jak należy.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Longwei wszystko rozumie, nie martwić się, panie kapitanie. Dotrzemy na miejsce mniej więcej jutro w południe.";
			link.l1 = "Idź i uważaj na siebie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "Wzywałeś, kapitanie?";
			link.l1 = "Tak. Słuchaj uważnie, Alonso.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "Ty na czele oddziału wojowników musisz przejść przez dżunglę i dotrzeć do zatoki Chetumal. Tam najpewniej czeka banda łotrów. Musisz zająć pozycje i zaatakować ich od tyłu na mój sygnał.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "Bułka z masłem, kapitanie. Ale nie schodźcie na ląd w zatoce wcześniej niż jutro w południe – szybciej z chłopakami tam nie dotrzemy.";
			link.l1 = "Przygotuj się porządnie, Alonso. I niech Bóg nam dopomoże.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Charles, widziałeś, tak, co nie?";
			link.l1 = "Wygląda na to, że już na nas czekają. Na pewno czają się za tamtym zakrętem.";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "Jednak jeszcze nie zrobili z nas sita. Nawet nie próbują tego zrobić, tak, co nie?";
			link.l1 = "Może najpierw będzie chciał z nami jednak porozmawiać. Nie prowokujmy go – pójdźmy tam sami, nasza drużyna nas zabezpieczy. Chodźmy, skończmy z tym wszystkim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "Stój! Ani kroku dalej! Chłopaki, jeśli ten fircyk się ruszy – zróbcie z niego sito. Dziewczyny nie ruszać.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "Tato?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			if (CheckCharacterItem(sld, "MarysHat")) // У Мэри есть своя шляпа
			{
				dialog.text = "Taaak, sporo widziałem w swoim długim i niełatwym życiu. Za każdym razem myślę, że nic mnie już nie zaskoczy — i za każdym razem się mylę. A więc jednak przeżyłaś tam... I nawet kapelusz Teresy ocaliłaś. Już nie sądziłem, że kiedykolwiek jeszcze go zobaczę.";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = "Tak, co nie, sporo już widziałem w swoim długim i niełatwym życiu. Za każdym razem myślę, że już nic mnie nie zaskoczy – i za każdym razem się mylę. Czyli jednak przeżyłaś tam, Julia...";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "Mi ją przekazała Aurélie, przed swoją... śmiercią.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "Jakie to wzruszające... Zaraz się popłaczę. A już myślałem, że Teresę pochowano razem z nią. Nie rozstawała się z nią ani na sekundę, odkąd jej ją podarowałem. Twoja matka, choć była zwykłą kelnerką, to ducha przygody miała tyle, że aż się z niej wylewał. Kiedy podczas abordażu 'Fleur-de-Lys' ją znalazłem, od razu wiedziałem, że Teresa będzie za nią szaleć. Wyglądała w niej zabawnie, ale nic sobie z tego nie robiła: zdejmowała ten kapelusz tylko do snu. Ale tobie, Julia, naprawdę pasuje.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "Julia? Nie, mylisz się, mam na imię Mary...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "Hm, więc tak to wygląda. Wynika z tego, że ci łajdacy zignorowali moje słowa i wzięli sprawy w swoje ręce. No, po tych katolickich psach niczego innego nie można się było spodziewać.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "Ty... Ty... Ty naprawdę jesteś moim ojcem?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "No cóż, gdyby było inaczej, ty i twój kumpel już leżelibyście na ziemi, pełni ołowiu. Już dawno nie wierzę ani w Boga, ani w Diabła, ale chyba jednak istnieją. Ten pierwszy na pewno – skoro obdarzył cię urodą Teresy. I właśnie to uratowało ci teraz życie. Jak to mówią: niepojęte są wyroki Pana, tak, co nie? Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "Tato... Ja... ja nie rozumiem, tak, co nie...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = "Ale co ty możesz zrozumieć, tak, co nie...";
			link.l1 = "Jakoś nie wygląda na to, żebyście się cieszyli na widok córki, panie Kasper. Zwłaszcza że sam pan ją rozpoznał.";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "Nie brakuje ci sprytu, młokosie... Jak ci tam na imię?";
			link.l1 = ""+GetFullName(pchar)+".  Kiedy was szukaliśmy, ciągle się zastanawialiśmy, jak sobie radziliście przez ten cały czas. Jeśli w ogóle przeżyliście. Ale widzę, że nieźle się tu urządziliście, panie... Northwood.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "A-a, tak wy dokopaliście się nawet do tego. No, szacunek, monsieur żabojad, co tu dużo mówić – zważywszy, że zadbałem o to, żeby wszystkie końce były ucięte.";
			link.l1 = "Nie tylko o tym. Wiemy też o 'Cornwallu', o jego ładunku i o Joshuę Casperze, którego imię przywłaszczyłaś sobie na jakiś czas, a nazwisko — chyba już na zawsze.";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "Brawo (bije brawo). Jestem pod wrażeniem. Sam do tego doszedłeś, czy moje ukochane dziecię też się do tego przyczyniło?";
			link.l1 = "Bez Mary nic by mi się nie udało. Bardzo chciała dowiedzieć się wszystkiego o swoich rodzicach. Z losem Teresy poradziliśmy sobie bez problemu, ale twoje ślady śledziliśmy całkiem długo...";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "To wszystko takie słodkie, że aż łzy napływają do oczu. No i co, córeczko, jesteś zadowolona? Usatysfakcjonowana? Chcesz przytulić tatusia?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "Nie rozumiem, ojcze... Czemu się nade mną znęcasz? Za co?! (krzyczy) Przecież to ty zostawiłeś mnie tam – na tych wrakach statków! A potem nawet nie pomyślałeś, żeby wrócić, tak, co nie? Dlaczego? Kim ty w ogóle jesteś, kim są ci ludzie za twoimi plecami?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "Powiedz, "+pchar.lastname+", ona często tak histeryzuje? To po matce. Teresa była wspaniałą dziewczyną, najlepszą, jaką kiedykolwiek spotkałem. Ale uwielbiała się rozklejać i urządzać sceny, tak, co nie... Co tu dużo mówić... Irlandka.";
			link.l1 = "Nie ważcie się jej obrażać! Mary nie jest winna waszym nieszczęściom i na pewno nie zasługuje na takie traktowanie.";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "Chciałeś mnie uciszyć, gówniarzu?!";
			link.l1 = "Wręcz przeciwnie. Chcę, żebyście opowiedzieli nam swoją historię. To bardzo ważne dla Mary, tak, co nie? Ale nie pozwolę wam jej poniżać. Więc trzymajcie się w ryzach.";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "Myślisz, że mam wielką ochotę wypłakiwać się wam w kamizelkę? Moje życie potoczyło się, jak się potoczyło, i — jak to mówicie wy, papieże — Bóg mi świadkiem, że niczego nie żałuję. Poza tym, że wtedy straciłem Teresę — przez nią. Czy cię nienawidzę, córeczko? Może kiedyś tak było... ale teraz mam cię gdzieś.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "Obwiniasz mnie o śmierć mamy?! Ty... W czym niby zawiniłam: że się urodziłam, tak, co nie? Dobrze, ojcze, "+pchar.name+", masz rację – opowiedz nam wszystko, a potem się odwrócimy i odejdziemy. I już nigdy więcej się przed tobą nie pojawię, skoro ty... (zaczyna płakać).";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "Taaak, wykapana Teresa. Jakbym cofnął się o dwadzieścia lat, ha-ha. Do diabła z wami. Nie chciałem do tego wszystkiego wracać... Więc jeśli pod koniec tej opowieści zdecyduję się wpakować ci kulkę w czoło, kochanie — miej pretensje tylko do siebie.";
			link.l1 = "Wtedy kulka poleci i w pana stronę, Rupert. A wydaje mi się, że to nie leży w pańskich planach – wygląda pan na kogoś, kto ceni sobie życie.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_20": //
			dialog.text = "Wiem, ile jest warte, chłopcze. To dwie różne rzeczy. Ale co ty możesz o tym wiedzieć? Dobra, przejdźmy do rzeczy. Chcecie wiedzieć o mnie wszystko? No to proszę bardzo. Urodziłem się na farmie, niedaleko Eastbourne — małego miasteczka nad kanałem La Manche — w 1611 roku. Może rok wcześniej albo później — moja matka ciągle myliła daty, co zresztą nie dziwi, biorąc pod uwagę, ile w siebie lała.";
			link.l1 = "Trudne dzieciństwo? Rozumiem.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "Sam chciałeś — to teraz słuchaj z zamkniętą gębą, a nie żartuj. Ojca nie miałem, i nawet nie wiedziałem dlaczego — ale, w przeciwieństwie do ciebie, córeczko, nic mnie to nie obchodziło. Nazwisko, które po nim odziedziczyłem, całkowicie mi odpowiadało. Kiedy miałem trzynaście lat, pewnej nocy na wybrzeżu wylądowali korsarze z Dunkierki. Taa, dziś niechętnie się o tym wspomina, ale oberwało się od nich nie tylko Holendrom, lecz także nam — tym, którzy mieszkali na wschodnim wybrzeżu starej Anglii.";
			link.l1 = "Słyszałam o tym. Ci ludzie nikogo nie oszczędzali. Jak wam udało się przeżyć?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "Wiem o ich okrucieństwach. Nikogo nie oszczędzali – ani starców, ani dzieci. Tym bardziej to niezwykłe, że udało wam się stamtąd wydostać.";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "Tej nocy ta papieska hołota spaliła kilka farm, w tym także naszą. Mnie udało się uciec, ale moja mamusia, która tak się opiła cydru, że nie mogła ruszyć swojego tłustego tyłka z łóżka, spłonęła w nim żywcem. Sama sobie winna, oczywiście – ale jednak była moją matką.";
			link.l1 = "I wtedy znienawidziłeś wszystkich papistów?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "Tej nocy ta papieska swołocz spaliła kilka farm, w tym także naszą. Ja zdołałem uciec, ale moja mamusia, która tak się obżarła cydru, że nie mogła ruszyć swojego tłustego tyłka z łóżka, spłonęła w nim żywcem. Sama sobie winna, jasne – ale jednak była moją matką.";
			link.l1 = "I wtedy znienawidziłeś wszystkich papistów?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "Wtedy znienawidziłem głód, dowcipnisiu. Tobie to pewnie obce, ale ja poczułem go na własnej skórze — i to porządnie. Wyruszyłem na północ, do stolicy, gdzie zaciągnąłem się do floty — tam częściej częstowano batem niż strawą, ale parę tuzinów razów w zupełności mi wystarczyło, żeby zmądrzeć. Potem się wciągnąłem — i pokochałem życie na morzu. Zwłaszcza że nudno tam nie było...";
			link.l1 = "No tak, wierzę na słowo. Sława angielskiej floty wyprzedza ją samą.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "W 1633 roku zdałam egzamin na stopień porucznika i dostałam przydział na bryg 'Cornwall'.";
			link.l1 = "Pod dowództwo Joshuy Caspera.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "Ooo, tak, taaak... Joshua Casper... Takiego drania to ze świecą szukać na całej przeklętej flocie, tak, co nie? Tyle lat już minęło, a ta kanalia wciąż nawiedza mnie w snach.";
			link.l1 = "Czym się tak wyróżnił? Wystawiał cię na dodatkową wachtę – za nadmierny zapał? Albo był potajemnie papistą?";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "Ten okrutny drań tak dręczył załogę, że ludzie ze zmęczenia zaczynali wpadać za burtę. Skoro znasz jego imię i wiesz, że dowodził 'Cornwallem', to na pewno widziałeś jego papiery – lśniące jak wylizany koci zadek\nNagród nasz bohaterski Joshua miał całą szkatułkę. Wielu naiwnych chłopaków takich jak ty chciało służyć pod jego dowództwem – co by nie mówić, żabojadów kosił jak naostrzona kosa mokrą po deszczu trawę – ale gdy tylko trafiali na 'Cornwalla', bardzo szybko rozumieli swój błąd\nByliśmy śmiertelnie zmęczeni tym wszystkim, "+pchar.lastname+". Ktoś nawet pisał podania o przeniesienie – ale ginęły one na półkach Admiralicji albo w jej piecach. Jednak życie dało nam szansę – przenieśli nie nas z 'Cornwalla', tylko kogoś innego – na niego. John Lawson – ulubieniec Cromwella, na pewno o nim słyszałeś.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "Dupy lizać potrafił już wtedy – i może z Kasperem by się dogadali, tak, co nie, ale ja do tego nie dopuściłem. Podstawiłem małego Johnny’ego, a nieogarnięty w sytuacji Joshua w furii obił go swoją laską.";
			link.l1 = "Prawdziwe upokorzenie dla oficera. I Lawson wszystko powiedział ojcu?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "Jeszcze jak. Ale widzisz, system nie może pożreć sam siebie. Sprawa nie wyszła na jaw – Lawsonowi zaproponowano przedwczesny awans, a Joshuę i 'Cornwalla' zepchnięto w cień – z Londynu przeniesiono nas do Plymouth, na południe Anglii. Moglibyśmy dalej siać postrach wśród was, żabojadów, ale 'Cornwalla' przerobili na okręt zaopatrzeniowy, przewożący wojskowe ładunki do Dundalk, małego irlandzkiego miasteczka.";
			link.l1 = "I tam spotkaliście Teresę?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "Już podczas naszej pierwszej wizyty tam. Teresa O'Fatt, jak już mówiłem, była kelnerką w jednej z miejscowych tawern. Trzy dni wystarczyły nam, by zrozumieć – byliśmy sobie pisani. Myślę, że i ty mnie tu zrozumiesz, "+pchar.lastname+", tak, co nie?";
			link.l1 = "Chyba tak.";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "Patrząc na ciebie teraz, nie powiedziałbyś, że znasz słowo 'miłość'.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "Nie spotkałem nikogo piękniejszego – ani wcześniej, ani przez następnych dwadzieścia lat. Chyba po raz pierwszy w życiu poczułem się naprawdę szczęśliwym człowiekiem, i ona też – jak sama twierdziła.";
			link.l1 = "I zaproponowałeś jej, żeby wyjechała z tobą?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "Nie spotkałem nikogo piękniejszego – ani wcześniej, ani przez następne dwadzieścia lat. Chyba po raz pierwszy w życiu poczułem się naprawdę szczęśliwym człowiekiem, i ona też – jak sama twierdziła.";
			link.l1 = "I zaproponowałeś jej, żeby pojechała z tobą?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "Oczywiście, że nie – to było niemożliwe, bo 'Cornwall' wciąż był okrętem wojennym z parszywym kapitanem na czele. Po tygodniu, który wydawał się wiecznością, nasza brygantyna odpłynęła z powrotem do Plymouth. Do Dundalk wróciliśmy po dwóch miesiącach – i wtedy Teresa zszokowała mnie wiadomością: była w ciąży.";
			link.l1 = "Tak, to się zdarza, kiedy kładziesz dziewczynę do łóżka.";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "Nie wymądrzaj się, żabojadzie. Teresa płakała mi na ramieniu, a ja zastanawiałem się, co z tym zrobić. Chciałem z nią zostać, bardzo chciałem – ale już wtedy jakby przeczuwałem, że od tego dziecka niczego dobrego się nie doczekamy\nPróbowałem przekonać Teresę, żeby się go pozbyła, póki jeszcze nie było za późno – ale zamiast tego wywołałem jeszcze gwałtowniejszą histerię. Co wtedy zrobić, nie wymyśliliśmy – postanowiliśmy poczekać jeszcze dwa miesiące, do następnego powrotu 'Cornwalla' do Dundalk, bo wtedy Admiralicja jeszcze nie zmieniła gniewu na łaskę wobec Caspera.";
			link.l1 = "I przynieśliście ją na 'Cornwalla'?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "Musiałem podjąć decyzję szybko. Wiedziałem, że Kasper nie zniesie kobiety na pokładzie, więc planowałem w noc po wypłynięciu ukraść szalupę i dopłynąć nią do Dublina, który akurat miałby się znaleźć po naszej prawej burcie.";
			link.l1 = "I co się stało? Złapali was?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "Teresę znaleziono wcześniej. Kasper zdążył już wlać w siebie porcję whisky, więc był głuchy na wszelkie prośby i po prostu kazał wyrzucić dziewczynę za burtę. Na wszystkie moje błagania tylko śmiał się do rozpuku – cholera, opowiadam to, a w głowie wciąż słyszę jego śmiech...";
			link.l1 = "I wtedy postanowiliście wzniecić bunt?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "Nie miałem innego wyjścia. Wyrwałem pistolet z pasa stojącego obok wachmistrza i zrobiłem dziurę w czole tego skurwiela. Na pokładzie natychmiast wybuchła rzeź — nikt nie lubił kapitana, ale strach przed trybunałem był silniejszy. Kosztowało to życie prawie jednej trzeciej załogi — kiedy w końcu oprzytomnieliśmy, cały pokład 'Cornwalla' tonął we krwi i był zasłany ciałami naszych martwych towarzyszy.";
			link.l1 = "Po czymś takim do Anglii raczej nie chcieliście wracać. Tam czekałaby na was stryczek.";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "Byłem pewien, że przeprowadzę 'Cornwalla' przez ocean. Tutaj nasze gęby były nikomu nieznane i to dawało nam szansę na nowe życie. Przekonać resztę oficerów nie było trudno – zadziałał nie tyle mój autorytet, co zawartość kilku skrzyń, o której zwykli marynarze nie mieli pojęcia. Załoga zdecydowała – Joshua Casper powinien przeżyć. Razem z garstką oficerów postanowiliśmy zyskać trochę czasu i poświęcić jedną ze skrzyń.\nAle jakaś kanalia wygadała się o drugiej skrzyni – i to wprowadziło rozłam w załodze.";
			link.l1 = "Zbuntowali się teraz przeciwko wam?";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "Nie, ale liczba chętnych do dalszej służby naszemu wspaniałemu królowi gwałtownie się zmniejszyła. Tych, którzy byli gotowi zostać piratami, też było niewielu. Więc znaleźliśmy rozwiązanie pośrednie – postanowiliśmy rzucić kotwicę w jednym z francuskich portów. Tam planowaliśmy sprzedać statek, podzielić pieniądze uzyskane za niego i te, które były w skrzyni, a potem – rozejść się każdy w swoją stronę.";
			link.l1 = "I nie przeszkadzało ci, że będziesz musiała żyć wśród tych znienawidzonych przez ciebie katolików?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "Nie obchodziło mnie już, gdzie zejdziemy na ląd: Teresa, choć na pokaz trzymała się dzielnie, czuła się dokładnie tak, jak każda ciężarna kobieta po trzech miesiącach nieustannego kołysania. I, tak jak trzy miesiące wcześniej, nie miałem nic przeciwko towarzystwu katolików – byle tylko być przy niej.";
			link.l1 = "Ale na północno-zachodzie Morza Karaibskiego nie ma i nie było żadnych francuskich osad.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "W chwili, gdy sytuacja na pokładzie 'Cornwalla' osiągnęła punkt wrzenia, byliśmy już w połowie drogi z wiatrem w żagle, który teraz nie pozwalał nam obrać kursu na Saint Kitts...";
			link.l1 = "I wybraliście Tortugę jako cel podróży?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "W tamtych latach to była jeszcze zwykła wioska. Żeby opóźnić ewentualny pościg ze strony władz, zmieniliśmy tablicę rufową z nazwą brygu – tak 'Cornwall' stał się 'Wranglerem'.";
			link.l1 = "Ale jakoś do Żółwiej Wyspy nie dotarliście. Nie mogliście się aż tak bardzo pomylić z kursem, żeby zamiast na Tortugę trafić na zachód od Kuby?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "Ja, żebyś wiedział, jestem doświadczonym nawigatorem – nie byle kim. Nie było żadnej pomyłki, trzymaliśmy kurs dokładnie na północ. Ale ledwo weszliśmy w Przesmyk Zawietrzny, zerwał się straszny szkwał. Do dziś się zastanawiam – jakim cudem nie roztrzaskało nas o brzeg Kuby, tylko poniosło wzdłuż niego?..";
			link.l1 = "Prawdziwy cud – inaczej tego nie nazwę.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "Przytuliwszy szlochającą Teresę, gorliwie błagałem Pana, by zesłał nam ratunek. I On naprawdę pomógł, tak, co nie?";
			link.l1 = "Przywiało was na Wyspę Sprawiedliwości.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "Sprawiedliwości stało się zadość – o tak! Od uderzenia o rafę 'Wrangler' pękł na pół, ale w zadziwiający sposób utrzymał się na wodzie – na tyle, że prąd poniósł go do innych, spiętrzonych na sobie wraków. Sztorm szalał jeszcze niemal dwa dni, a kiedy wreszcie ucichł – uratowali nas mieszkańcy tej nieszczęsnej wysepki.";
			link.l1 = "Ciebie, Teresę i jeszcze dwóch marynarzy. O tym, co było dalej, mamy już wyobrażenie. Lepiej opowiedz, jak udało ci się wydostać z więzienia i opuścić wyspę.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "Lepiej by było, gdyby wtedy mnie rozstrzelali... Gdybym tylko wiedział, co mnie czeka, sam bym się przykłuł do krat i nie ruszyłbym się z miejsca.";
			link.l1 = "Czyżby na tartanie było mniej wygodnie niż na brygu, tak, co nie "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "Tylko nie mówcie, że wpadliście w sztorm jeszcze i na tartanie.";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "Tartanie? Ha-ha-ha... Tak, właśnie taki był mój plan. Myślałam, że mam szczęście. Szef straży więziennej okazał się byłym oficerem angielskiej floty, który przejął się moim losem. To on opowiedział mi o tartanach kubańskich przemytników i o tym, że planowano mnie stracić. Chyba można by go nazwać człowiekiem honoru – sam zaproponował, żebym wyszła na wolność i powierzyła swój los przeznaczeniu.";
			link.l1 = "Nie rozumiem... Jeśli nie na tartanach, to jak opuściliście wyspę?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "Tartanie? Ha-ha-ha... Tak, właśnie taki był mój plan. Myślałam, że mam szczęście. Szef straży więziennej okazał się byłym oficerem angielskiej floty, który przejął się moim losem. To on opowiedział mi o tartanach kubańskich przemytników i o tym, że zamierzali mnie stracić. Chyba można by go nazwać człowiekiem honoru – sam zaproponował, by mnie wypuścić, żebym powierzyła się losowi.";
			link.l1 = "Nie rozumiem... Jeśli nie na tartanach, to jak opuściliście wyspę?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "Jeśli się zamkniesz i posłuchasz, zrozumiesz. Płynąłem do tartanów, długo płynąłem — aż za ścianą deszczu zobaczyłem światło. To było coś absolutnie niewiarygodnego, do cholery. Lśniło jak słońce na pokładzie jednego z półzatopionych galeonów, więc skierowałem się w jego stronę. Jeszcze nie wiedząc, że popełniam największy błąd w swoim życiu. Wydostałem się z wody po trapie burtowym — i stanąłem naprzeciw światła. Błyszczało nad złotą statuą i...";
			link.l1 = "Idol Kukulkana. Tak, wtedy 'San Jeronimo' jeszcze nie poszedł na dno...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "Więc ty też go widziałeś, "+pchar.lastname+"?";
			link.l1 = "Nie tylko widziałem. Przemieszczałem się w przestrzeni z jego pomocą, i to kilka razy.";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "Kłamiesz! Kilka razy, mówisz?! Jak możesz więc tu stać, cały aż kipiący zdrowiem?!";
			link.l1 = "Po przeniesieniu wypiłem indiański eliksir, to właśnie on pomógł mi przeżyć i odzyskać siły.";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "Aha, o to chodzi. A wiesz, ile ja sił odzyskiwałam? Wiesz?!";
			link.l1 = "Domyślam się. Dotknęliście idola, a on przeniósł was na Dominikę – do wioski Indian, tam złożyli was w ofierze posągowi i trafiliście na Main, tak, co nie?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "Właśnie tak. Nigdy wcześniej nie czułem takiego bólu, jak wtedy, gdy leżałem obok tamtej statuy. Nie wiem, do czego to porównać. Może gdyby zawalił się na ciebie kamienny dom — nawet wtedy nie poczułbyś takiego cierpienia. Ledwo odzyskałem przytomność, zobaczyłem, jak znów zbliża się do mnie tłum tubylców. Gdybym znał ich język — przysięgam, błagałbym, żeby zabili mnie na miejscu.";
			link.l1 = "To byli Indianie Miskito z wioski niedaleko stąd?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "To właśnie они. Zaciągnęli mnie do jednej z chat, gdzie jakiś dziwny tubylec, zupełnie do nich niepodobny, wlał mi coś prosto do ust. Ból trochę zelżał, ale całkiem nie przeszedł. Wieczorem wyciągnęli mnie do ogniska, a ten wymalowany drań zaczął odprawiać jakiś rytuał. Żałosny łajdak.";
			link.l1 = "Oko Węża... Powinieneś był być mu wdzięczny za uratowanie własnej skóry.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "Ocalenie?.. Trzy lata, "+pchar.lastname+". Przez trzy lata leżałem prawie bez ruchu, załatwiałem się pod siebie, budziłem się we własnych wymiocinach – bo już nie mogłem znieść tych wszystkich śmierdzących wywarów i nalewek, które wlewano mi do gardła na siłę! A potem jeszcze prawie rok uczyłem się chodzić od nowa.";
			link.l1 = "Rozdzierająca serce historia. Ale szczerze mówiąc, nawet mi was żal.";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "Wsadź swoje współczucie swojemu Papie w jego tłusty katolicki tyłek. Nie potrzebuję niczyjej litości. Mam mówić dalej, czy musisz się popłakać, szczylu?";
			link.l1 = "Podróż nie dodała panu ogłady. Ale nic, dla Mary wytrzymam. Chociaż najważniejsze już, jak sądzę, wiemy – to jednak wysłuchamy pana do końca.";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "Podnosząc się z trudem na nogi, opuściłem tę przeklętą wioskę i dotarłem na wybrzeże, do zatoki Amatique. Tam spotkałem przemytników, których statek rzucił kotwicę w pobliżu, i dołączyłem do nich, przedstawiając się jako Rupert Casper – z własnego имienia nie zamierzałem rezygnować, ale i nazwisko jednego ze sprawców wszystkich moich nieszczęść też zachowałem. Żeby nie zapomnieć, dlaczego się tu znalazłem.";
			link.l1 = "Zawsze winni są inni, Northwood... Tylko nie ty sam. No, można cię zrozumieć – lata upokorzeń i cierpień, teraz siedzisz w tych lasach. Jak tu nie zwariować?";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "Przeszedł pan przez wiele, Northwood – nie da się zaprzeczyć. I proszę, gdzie pan trafił... W lasach, na skraju cywilizacji. Tu można zwariować...";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "Jestem panem tych lasów, "+pchar.lastname+". Przez ponad piętnaście lat przeszedłem drogę od żałosnego majtka na statku przemytników do ich herszta. Nie kapitana jakiegoś stateczku – tylko pana całego wybrzeża, od zatoki Amatique po Zatokę Zguby.";
			link.l1 = "No cóż, odrodzenie godne podziwu, przyznaję.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "Jestem panem tych lasów, "+pchar.lastname+". Przez ponad piętnaście lat przeszedłem drogę od żałosnego marynarza na statku przemytników do ich herszta. Nie kapitana jakiejś łajby – tylko pana całego wybrzeża, od zatoki Amatique po Zatokę Zguby.";
			link.l1 = "No cóż, odrodzenie godne uznania, przyznaję.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "Ktoś mówi, że to tutaj jest włości Leśnego Diabła... Bezczelne kłamstwo – to moje ziemie. I Swenson o tym wie, ha-ha-ha. Nie raz wysyłał tu swoich ludzi, próbował odkryć moją tożsamość – i żaden z nich do niego nie wrócił. Żywy, he-he. Na palcach jednej ręki można policzyć tych, którzy znają imię, pod którym zaczynałem karierę przemytnika, i wiedzą, gdzie w tych lasach mieszkam.";
			link.l1 = "Więc teraz nazywacie się inaczej. Teraz już rozumiem, czemu wieść, że ktoś szuka Ruperta Caspera, tak was przeraziła.";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "Panika? Naprawdę, chłopcze? To ty tu panikujesz – na moim terenie, otoczony moimi ludźmi, całkowicie pod moją władzą! Mogę z tobą zrobić, co tylko zechcę. I z nią też – choćby tylko za to, że przez nią musiałem tyle wycierpieć!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "Jesteś szalony, po prostu kompletnie szalony, tak, co nie? Nie znam takiego lekarstwa ani lekarza, który mógłby cię wyleczyć, Rupert Northwood! Przeszedłeś przez straszne męki, ale... jak możesz za wszystko obwiniać mnie?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "Już ci mówiłam – gdyby nie ty, nic by się nie wydarzyło. Po prostu to przyznaj, i tyle.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "Zostaw go, "+npchar.name+". Usłyszeliśmy już wystarczająco. Naprawdę są drogi, których nie warto przechodzić do samego końca. Miałem złe przeczucie, kiedy zdecydowaliśmy się na to wszystko. Ale go nie posłuchałem. Szkoda.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "Tak, co nie, wtedy oboje nie znaleźlibyście się tutaj, w potrzasku, bezsilni, by cokolwiek zrobić. Poczuj teraz na własnej skórze, córeczko, to, co ja przeżywałem!";
			link.l1 = "A kto ci powiedział, że jesteśmy bezsilni, by coś zrobić? Oddzi-a-a-ł, do boju!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "W czym rzecz, szczylu? Kogoś zgubiłeś? Ha-ha-ha... Ha-ha-ha. HA-HA-HA-HA-HA-HA!!! O rany, zobaczyłbyś teraz swoją minę, głupku! Ej, Mason, przynieś tu mój prezent dla naszych gości.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "Draniu! Gdzie są moi ludzie?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "Mówisz o tej garstce głupców, którzy postanowili urządzić na mnie zasadzkę? Mój przyjaciel karczmarz w porę mnie ostrzegł o twoim pojawieniu się w mieście, więc przyjąłem ich jak należy... Kilku udało się wymknąć. Ale nie martw się – jednego schwytałem żywcem. Żebyś na własne oczy zobaczył, jaki los was dziś czeka.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "Draniu! Odpowiesz mi za to! (płacze) Przysięgam, tak, co nie!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "Alonso! Jak się cieszę, że cię widzę!";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "A ja to dopiero się cieszę, że was widzę, kapitanie! Ktoś temu łajdakowi szepnął, że go szukacie — i spotkał nas grad kartaczy w samym разгаре drogi. Mnie z garstką chłopaków udało się wycofać i pognaliśmy co sił do portu, żeby was ostrzec. Na szczęście, gdy tylko wartownik na czatach zobaczył mnie na barkasie, który naprędce kupiłem w mieście, od razu zorientował się, o co chodzi. Szybko zebrał ludzi — i ruszyliśmy tutaj, na ratunek.";
			link.l1 = "Dzięki ci, przyjacielu. Ocaliłeś nas przed niechybną śmiercią.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "Nic takiego. Co robimy dalej, kapitanie?";
			link.l1 = "Zbierz ludzi i idźcie na statek. My z Mary musimy zostać sami.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "O Boże, "+pchar.name+"... Wciąż nie mogę, po prostu nie mogę w to uwierzyć. Mój ojciec... On jest potworem... Dlaczego mi to zrobił? Czy on naprawdę oszalał?";
			link.l1 = "Musiał przejść przez straszliwe męki. Bunt na 'Cornwallu', ucieczka przez Atlantyk, burza i śmierć twojej matki. Nie wyobrażam sobie, jak przetrwał podróż przez portale tych idoli bez eliksiru Komanczów – ale to właśnie zniszczyło jego rozum.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "A co jeśli on już taki był wcześniej? Albo był takim samym łajdakiem, tylko trochę łagodniejszym, ale naprawdę kochał moją mamę? Może te wydarzenia po prostu uwolniły to, co w nim siedziało? I jeśli tak... to co, jeśli i we mnie jest coś z niego? Przecież to możliwe, "+pchar.name+", tak, co nie?";
			link.l1 = "Zdecydowanie coś po nim odziedziczyłaś, "+npchar.name+". W dzisiejszej walce zauważyłem – walczysz z tym samym uporem, z tym samym ogniem w oczach i tą samą wściekłością, co on. Ale jego szaleństwa w tobie nie ma. Jesteś zupełnie inna. Żywa, otwarta, z sercem na dłoni. Właśnie za to cię pokochałem. I wygląda na to, że Northwood miał rację: charakter masz cały po matce.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "Naprawdę tak myślisz, kochanie?";
			link.l1 = "Oczywiście, kochanie. Gdybym spotkał go tak po prostu, nie wiedząc kim jest – nigdy bym nie pomyślał, że jesteście rodziną.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "Wiesz, na Wyspie Sprawiedliwości nie ma zbyt wielu rozrywek. Od dziecka pokochałam szermierkę – najpierw walczyłam z chłopakami, drewnianymi kijami, a potem już i z dorosłymi mężczyznami, prawdziwymi klingami, tak, co nie? Zawsze chciałam być z nimi na równi... ale jakby zawsze czułam się słabsza, nawet kiedy wygrywałam. Wtedy po prostu wracałam do domu – i znowu ćwiczyłam. Trenowałam godzinami, aż ręce zaczynały mi drżeć, tak, co nie? To jest właśnie ten ogień? Ta wściekłość, o której mówisz?";
			link.l1 = "W pewnym sensie – tak, co nie? Wydaje mi się, że ten ogień daje ci o wiele więcej siły, niż sama w sobie widzisz. I, chcesz czy nie, to dar od twojego ojca. Choć wcale nie zamierzał ci niczego dawać.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "Myślisz, że dobrze zrobiliśmy, że zaczęliśmy grzebać w przeszłości, tak, co nie?";
			link.l1 = "Teraz, kiedy już wszystko wiemy... to nie wydaje się aż tak dobrym pomysłem. Ale jeśli chcesz poznać prawdę, musisz być gotów na to, że może ci się ona nie spodobać.";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "Masz rację, "+pchar.name+", tak... Zostańmy tu jeszcze trochę. Nie chcę teraz wracać na statek. Chcę po prostu... posiedzieć tu, w ciszy.";
			link.l1 = "Oczywiście, kochanie. Sam też chciałem to zaproponować.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
	}
} 
