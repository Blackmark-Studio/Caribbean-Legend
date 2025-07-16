// Маркус Тиракс, барон Ла Веги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ach książę, wreszcie jesteś. Przynajmniej jeden z was raczył się pojawić! Robota czeka, a wy wszyscy zniknęliście! Gdzie do diabła wszyscy się podziali?";
					link.l1 = "Nie mam pojęcia... Marcus, koniec z tym. Mam dość. Martwi mężczyźni przychodzą do mnie w snach, a sam Lucyfer dmucha mi w kark. Ostatnio przelano zbyt wiele krwi.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Masz dla mnie jakieś 'zajęcia'?";
				link.l1 = "Witaj, Marcus. Tak, mam jedną 'sprawę'. Zyskowną i praktyczną.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Przyniosłeś pieniądze?";
				link.l1 = "Zrobiłem to.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "To nasz klient! Robota skończona, twój Baron siedzi w dobrze strzeżonym lochu. Może chciałbyś rzucić okiem, he-he?!";
				link.l1 = "Na to będę miał mnóstwo czasu, ha-ha. Czy dobrze go traktują?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, co do diabła?!";
				link.l1 = "Marcus, wszystko poszło nie tak. Nie mogłem ani przyjść, ani cię poinformować...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Oto nasz lalkarz!";
				link.l1 = "Ha-ha! Przedstawienie było doskonałe!";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Czy masz mi coś do powiedzenia? Nie? To zostaw mnie w spokoju!","Ha, "+pchar.name+"! Masz do mnie interes? Nie? To nie zawracaj mi głowy.")+"","Myślałem, że wyraziłem się jasno... Kazałem ci odejść, ale ty wciąż mnie irytujesz!","Racja, zaczynam mieć dość tej nieuprzejmości.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Już odchodzę.","Jasne, Marcus...","Przepraszam, Marcus...","Ojej...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Czyś ty oszalał? Chciałeś się bawić w rzeźnika, co? Wszyscy piraci są na ciebie wściekli, chłopcze, lepiej opuść to miejsce...","Wydaje się, że zamieniłeś się w wściekłego psa, chłopcze. Chciałeś trochę rozprostować ręce? Bez obrazy, ale nie ma tu dla ciebie nic. Zjeżdżaj!");
				link.l1 = RandPhraseSimple("Słuchaj, chcę naprawić tę sytuację.","Pomóż mi rozwiązać ten problem, proszę...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marku, czy kiedykolwiek przestaniesz się na mnie gniewać? Uratowałem twojego przyjaciela, Vincenta, który z nami najeżdżał Cartagenę, a także uratowałem twoją skórę! Czyżby Bernard ci nawet o tym nie powiedział?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Dlaczego jesteś taki niegrzeczny, Marcusie? Czy Bernard nic o mnie nie mówił?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "Szukam roboty... Masz coś dochodowego na myśli?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Mam trochę jedwabiu na sprzedaż.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "Znalazłem ci kupca. To szkutnik z Port Royal. Potrzebuje jedwabiu okrętowego do swojej produkcji i będzie mógł kupować partie po sto beli co miesiąc za 25 dublonów za belę. Jego ludzie będą odbierać towar od 10 do 15, w nocy, miejsce to Przylądek Negril. Hasło - 'Kupiec z Lyonu'. Łysy Geffrey już dostarczył pierwszą partię na Jamajkę.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "Znalazłem ci kupca. To budowniczy statków z Port Royal. Potrzebuje jedwabiu do swoich produkcji i będzie mógł kupować partie po sto sztuk co miesiąc za 25 dublonów za sztukę. Jego ludzie będą odbierać towary od 10 do 15, w nocy, miejsce to Negril Cape. Hasło - 'Kupiec z Lyonu'. Zajęło mi to ponad dwa miesiące, aby znaleźć takiego kupca, Geffrey musiał już sprzedać jedwab przemytnikom. Przykro mi, Marcus.";
				link.l1.go = "mtraxx_15";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Oszalałeś? Chciałeś bawić się w rzeźnika? Wszyscy piraci są na ciebie wściekli, chłopcze, lepiej opuść to miejsce...","Wygląda na to, że zamieniłeś się w wściekłego psa, chłopcze. Chciałeś trochę porozciągać ręce? Bez obrazy, ale tu dla ciebie nie ma miejsca. Zjeżdżaj!");
				link.l1 = RandPhraseSimple("Słuchaj, chcę naprawić sytuację...","Pomóż mi rozwiązać ten problem, proszę...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, co do diabła?!";
				link.l1 = "Marcus, wszystko poszło nie tak. Nie mogłem ani przyjść, ani cię poinformować...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Miło cię widzieć, przyjacielu!";
				link.l1 = "Miło cię widzieć również. Dziękuję za niesamowite widowisko!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Cieszę się, że cię widzę, chłopcze! Jak mogę ci pomóc?";
				link.l1 = "Mam dla ciebie propozycję. Godna pirata, wiesz!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "To nasz klient! Robota zrobiona, twój Baron siedzi w dobrze strzeżonym lochu. Może chciałbyś rzucić okiem, he-he?!";
				link.l1 = "Będę miał mnóstwo czasu, by to zrobić, ha-ha. Czy dobrze go traktują?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Masz dla mnie jakieś sprawy?";
				link.l1 = "Witaj, Marcus. Tak, jedna sprawa. Dochodowa i piracka.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Czy przyniosłeś pieniądze?";
				link.l1 = "Zrobiłem to.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "To nasz klient! Robota skończona, wasz Baron siedzi w dobrze strzeżonym lochu. Może chcesz rzucić okiem, he-he?!";
				link.l1 = "Będę miał mnóstwo czasu, żeby to zrobić, ha-ha. Czy dobrze go traktują?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, co do diabła?!";
				link.l1 = "Marku, wszystko poszło nie tak. Nie mogłem ani przyjść, ani cię poinformować...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Oto nasz marionetkarz!";
				link.l1 = "Ha-ha! Widowisko było doskonałe!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Miło cię widzieć, chłopcze! Jak mogę ci pomóc?";
				link.l1 = "Marcus, muszę z tobą porozmawiać. Nie jestem pewien, czy ci się to spodoba, ale i tak potrzebuję twojej pomocy.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ha, oto jesteś, "+pchar.name+". Czekałem na twój przyjazd. Leśny Diabeł zaintrygował mnie twoim problemem związanym z Tortugą...";
				link.l1 = "Powiedział mi, że znalazłeś rozwiązanie. Czy mam rację?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Mam jedwab na sprzedaż.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", cieszę się, że cię widzę! Czego potrzebujesz tym razem, kumplu?","Czego chcesz?","Znowu? Nie zawracaj ludziom głowy, jeśli nie masz nic do roboty!","Ty jesteś "+GetSexPhrase("dobry korsarz","dobra dziewczynka")+", więc możesz żyć na razie. Ale nie chcę już z tobą rozmawiać.","powtórz",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Chciałem cię tylko zobaczyć.","Nic."," Dobrze, Marcus, przepraszam.","Do diabła, naprawdę mi przykro, Marcus!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Napad!!! To jest nie do przyjęcia! Przygotuj się na śmierć, szczurze...","Hej, co ty tam robisz?! Myślałeś, że możesz mnie okraść? Jesteś skończony...","Zaraz, co u diabła?! Okazuje się, że jesteś złodziejem! To już koniec, łajdaku...");
			link.l1 = LinkRandPhrase("Gówno!","Carramba!","Ah, do diabła!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(" "+GetSexPhrase("Spływaj","Odejdź")+" stąd!","Wynocha z mojego domu!");
			link.l1 = "Ojej...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Nie rozpraszaj mnie swoją bezwartościową gadaniną. Następnym razem nie skończy się to dla ciebie tak dobrze...";
        			link.l1 = "Zrozumiałem, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Jestem tobą zmęczony.","Nie chcę z tobą rozmawiać, więc lepiej trzymaj się ode mnie z daleka.");
			link.l1 = RandPhraseSimple("Cóż...","Hm, dobrze więc...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Mam nadzieję, że nie będziesz mnie już męczyć swoimi pustymi gadkami, bo będę musiał cię zabić. Mówię, że nie będzie mi to sprawiać przyjemności.";
        			link.l1 = "Możesz być tego pewien, Marcus, nie będę...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "Ha! Bohater z Turks? Przepraszam za szorstkie przywitanie, chłopcze. Bernard już mi opowiedział o twoim wspaniałym zaangażowaniu i wspomniał coś o pułapce na mnie. Chciałbym usłyszeć szczegóły...";
			link.l1 = "To była pułapka, rzeczywiście. Polowali na ciebie, nie na Bernarda. On był tylko przynętą.";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "Plan był prosty. Miałeś uratować przyjaciela i być pierwszym, który wejdzie na pokład 'Separatora'. I w tym momencie mieli ostrzelać statek i wysadzić go w kawałki. Brygantyna była naładowana prochem jak piekło siarką.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Do diabła! Czyj to był pomysł na to szaleństwo?! I jak mogłem się dowiedzieć, gdzie ukrywali Bernarda?!";
			link.l1 = "Autorami tego planu byli Jackman i jego brat David. Posłaniec miał cię poinformować, że 'Separator' czeka na twoją pomoc w południowej zatoce Turks. Wybrali mnie jako tego posłańca i to był ich błąd.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Nie pojmuję! Jaką rolę odgrywasz w tym wszystkim?";
			link.l1 = "Od dawna obserwuję tego drania Jackmana. Pracuję z Janem Svensonem, jeśli nie wiesz. Ja i Leśny Diabeł postanowiliśmy go zdemaskować. Jan jest pewien, że to on odpowiada za śmierć Blaze'a, a Steven został oskarżony niesłusznie.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Heh! Ale na ciele Blaze'a znaleziono ząb rekina z jego inicjałami - S.D. - ta rzecz należy do Stevena, wszyscy to wiedzą...";
			link.l1 = "To było sfabrykowane. Jackman postawił wszystko na jedną kartę. Pozbył się Nathaniela Hawka i zajął jego miejsce w Maroon Town, potem zamordował Sharpa i obwinił Rekina za morderstwo. Mam wystarczające dowody na jego zbrodnie. Znalazłem je w skrzyni Jakuba. Tam była druga część mapy Sharpa i odłamek Hawka.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "Cholera! Więc Steven jest niewinny? A czemu Jacob to wszystko zrobił?";
			link.l1 = "Spodziewał się zostać przywódcą Bractwa i oczekiwał czegoś związanego z Isla Tesoro. Nie mógł uzyskać twojego i Svensona wsparcia, więc postanowił pozbyć się was obu. Ty byłeś pierwszy na liście. Jan jako najniebezpieczniejszy był drugi.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "Gdzie jest ten drań?! Rozszarpię go na kawałki!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman i jego brat nie żyją, podobnie jak reszta jego łowców. Osobiście się nimi zająłem. Ten drań już nikomu nie zaszkodzi. Marcus, czy zagłosujesz na Stevena Dodsona? To moja osobista przysługa.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman i jego brat są martwi, podobnie jak reszta łowców. Osobiście się z nimi rozprawiłem. Ten drań już nikomu nie zaszkodzi. Niestety, Steven został zabity...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Jasne, że zagłosuję! Zawsze uważałem Rekina za najgodniejszego z nas po Błysku. I prawie uwierzyłem w jego winę. Wszyscy uwierzyliśmy! Oto, weź mój odłamek.";
			link.l1 = "Bardzo dobrze! Teraz możesz swobodnie oddychać.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Prawda... Jak rozumiem, reprezentujesz interesy Rekina?";
			link.l1 = "Tak. Ja i Jan Svenson. Dobrze, Marcus, do zobaczenia!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Martwy?! Jak to? To też robota Jackmana?";
			link.l1 = "Nie. Jego własny bosman to zrobił, Chad Kapper się nazywał. Już dostał to, na co zasłużył... Marcus, Svenson uważa, że jesteś najgodniejszym, aby zostać nowym przywódcą Bractwa. Reszta baronów poprze tę decyzję. Czy przyjmujesz to?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Heh! Nie musisz pytać mnie dwa razy. To wielki zaszczyt być Głową Bractwa! Nawet nie myśl, że się nie zgodzę.";
			link.l1 = "Świetnie. Cieszę się, że to zaakceptowałeś.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Proszę, weź mój odłamek. Dostarcz go Svensonowi. Rozumiem, że on tu rządzi?";
			link.l1 = "Tak, to on. Dobrze, Marcusie, do zobaczenia!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Tak, i chcę ci podziękować za uratowanie mojego przyjaciela Bernarda. Weź tę sakiewkę pełną złota.";
			link.l1 = "Dzięki! Żegnaj!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You have received 300 doubloons");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "Tak, opowiedział mi o wspaniałym przybyciu Charlie'ego Prince'a na Turków... Mówisz, że uratował mi skórę? Jak? Bernard wspomniał coś o pułapce...";
			link.l1 = "Tak, to była pułapka. To ty byłeś celem, a Bernard był tylko przynętą...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ha-ha-ha, pracujesz dla Diabła Lasu, co książę? Więc zarabiasz lepiej z nim niż ze mną? Powiedz mi szczerze!";
			link.l1 = "Marcus, odłóżmy przeszłość na bok raz na zawsze. Mamy teraz wspólny cel i jest ważniejszy niż łupienie karawan. Cholera! To teraz najważniejsza rzecz! Przyszłość Braci jest zagrożona!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Dobrze, książę, zrozumiałem! W końcu jesteś wolnym kaprem, praca dla Leśnego Diabła była twoim wyborem i podjąłeś dobrą decyzję... Steven więc... Mówiłeś, że został oczerniony, prawda?";
			link.l1 = "Absolutnie słusznie.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Oczywiście, postaram się jak najlepiej ci pomóc! Mów dalej.";
			link.l1 = "Rzuć okiem, Marcus... Oto ząb rekina. Co możesz mi o nim powiedzieć?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! To jest ząb białego rekina, którego zabił Steven Dodson, próbując zaimponować pewnej dziewczynie. Od tamtej pory ludzie zaczęli nazywać go Rekin. Niewielu mogło to zrobić pod wodą, używając tylko szabli. Ale był młody i głupi, a Beatrice Sharp była najpiękniejszą dziewczyną na Karaibach... Więc, jak to zdobyłeś?";
			link.l1 = "Dał mi go były kat z Saint John's. Ten ząb został użyty do zabicia jednego człowieka. Nazywał się... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "To stara historia. Steven zabił tego człowieka. Był wstrząśnięty śmiercią Beatrice i myślał, że Leadbeater to jedyna żyjąca osoba odpowiedzialna za jej śmierć. Ale później znalazł jakieś papiery na zwłokach Joshuy, przestudiował je i pożałował swojego czynu.\nMaska nie była winna śmierci Beatrice, potrzebował tylko Rzeźnika. Zazdrosna była dziewczyna Rzeźnika, Jessica, wszystko to ukartowała.";
			link.l1 = "Przeczytałeś te papiery?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Czemu miałbym? Oczywiście, że nie. Nie interesowałem się nimi. Ale mogę ci powiedzieć, dlaczego Maska ścigał Rzeźnika, jeśli masz trochę wolnego czasu. Pijany Steven opowiadał mi tę historię wiele razy.";
			link.l1 = "Mam czas. Uwierz mi, moje zainteresowanie ma cel. Mogę nawet napisać tę historię.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Wiem, że nigdy nie marnujesz czasu. Słuchaj zatem. Joshua Leadbeater był angielskim kapitanem marynarki, a legendarny 'Neptune' był pod jego dowództwem...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... ale Leadbeater przeżył i został podjęty przez jakiś statek. Jego rana oszpeciła go i odtąd nosił maskę. Po pewnym czasie ludzie zaczęli go nazywać Maską. Zemsta na człowieku, który oszpecił go na całe życie, stała się jego życiowym celem.";
			link.l1 = "Widzę... Zapisałem to wszystko. Myślę, że muszę to przeczytać jeszcze raz i porównać z informacjami, które już mam. Smutna historia, rzeczywiście. Czy widziałeś kiedyś Jessikę?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Jasne! Towarzyszyła Rzeźnikowi we wszystkich jego podróżach, dopóki nie porzucił jej dla Beatrycze. Jess nie mogła mu tego wybaczyć. Ludzie nazywali ją talizmanem Rzeźnika, bo zawsze miał szczęście, gdy była przy nim.\nWierzcie lub nie, ale jak tylko pozbył się jej na Barbadosie, jego interesy poszły źle, łupy stały się marne, a 'Neptune' stał się częstym gościem w stoczni Isla Tesoro. Ale można to wytłumaczyć tym, że Rzeźnik większość czasu spędzał z Beatrycze w kabinie, a nie na rufie.\nBeatrycze nie była jak Jessica, nie była uzależniona od przygód i wojny, chociaż Nicholas nauczył ją szermierki i żeglugi. Tak, uwielbiała morskie romanse, ale brakowało jej twardości. 'Neptune' Rzeźnika nie był dla niej odpowiednim miejscem. W końcu, to ją zabiło.";
			link.l1 = "A co z Jessicą?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Och, to była wyjątkowa kobieta... Każdy marynarz z 'Neptuna' słuchał jej rozkazów, i to nie tylko dlatego, że była dziewczyną kapitana. Jess była mistrzynią fechtunku i żeglarstwa, wysiłki Rzeźnika nie poszły na marne. Była twarda i lekkomyślna, a do tego była przepiękna.\nWielu mężczyzn chciało z nią dzielić łoże, ale ona chciała tylko Rzeźnika, zaczepianie jej było naprawdę ryzykowne, wielu odczuło skutki na własnej skórze dosłownie, a dla najbardziej uporczywych jej lekcje fechtunku okazały się ostatnimi w ich życiu.\nJess posiadała bardzo szczególny miecz, jedyny w swoim rodzaju na Karaibach, nie mam pojęcia, skąd go wzięła. Miecz z płomiennym ostrzem. Ostrza nie można było chwycić ręką, a nawet najlżejszy dotyk pozostawiał straszną ranę.\nJess była poszukiwaczką przygód nie z urodzenia, ale z powołania. A tak przy okazji, jeśli chcesz dowiedzieć się o niej więcej, możesz porozmawiać ze znajomym. On może ci o niej opowiedzieć dużo więcej niż ja.";
			link.l1 = "Naprawdę? A kim jest ten człowiek?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Diabeł Lasu nigdy się do tego nie przyzna, ale miał plany z Jessiką. To był czas, kiedy już przejął Zachodnią Główną i jego sława była czymś godnym zazdrości, więc tygrysica była dla niego dobra. \nGdy Rzeźnik pozbył się Jess, Jan zaczął podejrzanie często odwiedzać Barbados, sprawiając, że garnizon trząsł się ze strachu, ha. Jak wiesz, Jessica była córką plantatora z Bridgetown. \nW sumie jego plany były dobrze znane w prywatnych kręgach, ale nikt nie odważył się wyrazić swojej opinii na ten temat. Może Jan teraz siedzi na tyłku w Blueweld, ale wtedy każde złe słowo pod jego adresem mogło źle się skończyć. \nW końcu im się nie udało. Jess nie mogła żyć z bólem spowodowanym zdradą Rzeźnika i zemściła się rok później z pomocą Maski. Ta zemsta skończyła się tragicznie dla wszystkich: dla Rzeźnika, dla Beatrice, dla Maski i dla niej samej. Wszyscy zginęli.";
			link.l1 = "Nie. Rzeźnik wciąż żyje.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Co?! Czy ja cię źle usłyszałem?! On żyje?!";
			link.l1 = "Tak. Kapitan Rzeźnik nie został powieszony. Hm, właściwie to został, ale dzięki Jacobowi Jackmanowi i Henremu Katowi, którzy nastraszyli kata, wyszedł z tego żywy. Wieszanie było tylko przedstawieniem. Mam na to dowód.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Niesamowite! A gdzie on teraz jest?";
			link.l1 = "Znany jest jako Lawrence Beltrop i mieszka w Port-Royal. Ale wygląda na to, że się nie zmienił i wciąż jest niebezpieczny. Jackman, który narobił sporo zamieszania w Bractwie, wykonywał jego rozkazy.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Do diabła! Ćwierćmistrz w końcu odnalazł swojego kapitana! Po tylu latach... Mówisz, Beltrop... czekaj! Teraz widzę, dlaczego w papierach Blaze'a był ten dziwny protokół przesłuchania... Wygląda na to, że Blaze odkrył coś interesującego o Rzeźniku-Beltropie...";
			link.l1 = "O czym ty mówisz?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Kiedy przejąłem tę rezydencję, znalazłem trochę czasu, aby przejrzeć papiery Blaze'a. Znalazłem protokół przesłuchania kogoś o imieniu Samuel Brooks. Było tam mnóstwo szczegółów o przygodach Thomasa Beltrope'a, słynnego pirata i najbliższego przyjaciela Nicolasa Sharpa. Wygląda na to, że jest ojcem Rzeźnika.";
			link.l1 = "Interesujące. Wygląda na to, że dzieci Beltropa i Sharpa kontynuują pracę swoich ojców...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Wydaje się, że tak... Powiedz mi, przyjacielu, dlaczego tak interesujesz się przeszłością ludzi, którzy już dawno nie żyją? O co tu chodzi?";
			link.l1 = "Potrzebuję dokumentów, które mogłyby udowodnić, że Ellen McArthur jest córką Beatrice Sharp i wnuczką Nicolasa Sharpa, i ma pełne prawo nosić to nazwisko. Nie obchodzi mnie, że jej nazwisko mogło być Beltrop.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Nie znalazłem nic o Ellen McArthur w archiwach Blaze'a. Dziwne, że Beatrice nie powiedziała Blaze'owi o narodzinach jego siostrzenicy. To do niej niepodobne.";
			link.l1 = "Słuchaj, może jest coś więcej w papierach Sharpa o tej historii? Potrzebuję każdego szczegółu, jaki mogę zdobyć!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm... Może. Według notatek Blaze'a, próbował znaleźć wyspę, gdzie zginęła jego siostra. Są kopie archiwalnych dokumentów dotyczących ekspedycji karnej Leadbeatera. Nic ciekawego, poza kilkoma liczbami szerokości geograficznej.\nTen równoleżnik przecina Morze Karaibskie na północy. Ale nie ma śladu długości geograficznej. Oczywiście, poszukiwania Blaze'a nie powiodły się, nawet nie możesz sobie wyobrazić, ile małych wysp znajduje się na tej szerokości geograficznej.";
			link.l1 = "A jaki jest szerokość geograficzna?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Zobaczmy... Tutaj: 21 32' Północ. Nie wiem, jak to może ci pomóc.";
			link.l1 = "Może tak. Dzięki wielkie, Marcus, za twoją szczerą opowieść. Do zobaczenia!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Cóż, mogę coś dla ciebie zrobić. Jak wiesz, bezpieczeństwo Tortugi zapewnia nie tylko fort La Roche, ale także piracka eskadra nieustannie strzegąca brzegów wyspy. Port Tortuga jest bezpieczny, ci chłopcy znają się na rzeczy i mają potężne okręty. Levasseur od dawna przyciąga tych kapitanów.\nSą zdolni do walki nawet z eskadrą liniową i będą poważnymi przeciwnikami. Tak więc, będąc strażnikiem Kodeksu i przywódcą Braci Wybrzeża, mogę sprawić, że te wartowniki opuszczą brzegi Tortugi.";
			link.l1 = "I to wszystko?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Czy to nie wystarczy? I tak nie mogę ci więcej pomóc. Musisz zniszczyć fort, ale przynajmniej nie musisz walczyć z tymi okrętami strażniczymi. Uwierz mi, są bardziej niebezpieczne niż Fort, więc moja pomoc ułatwi ci zadanie.";
			link.l1 = "Cóż, skoro i tak muszę go zaatakować, to odejście pirackiej eskadry naprawdę pomoże. Dzięki, Marcus! Kiedy mogę zaatakować Tortugę?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Zawsze, kiedy zechcesz. Okręty strażnicze odpłyną na mój sygnał.";
			link.l1 = "Dobrze. Muszę więc iść, by się przygotować.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "Rozwiązać problem? Czy masz pojęcie, co narobiłeś? Tak czy inaczej, przynieś mi milion pesos, a przekonam chłopaków, żeby zapomnieli o twoim uczynku. Jeśli nie podoba ci się ten pomysł, to możesz iść do diabła.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Dobrze, jestem gotów zapłacić.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Żegnaj...";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Dobrze! Uznaj się znowu za oczyszczonego. Ale mam nadzieję, że nie będziesz już robić takich obrzydliwych rzeczy.";
			link.l1 = "Nie będę. Zbyt drogo dla mnie. Żegnaj...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Najpierw zdobądź sobie statek, a potem pytaj o robotę. Lądowy szczur nie ma tu czego szukać. Zjeżdżaj!";
				link.l1 = "Hmm... Widzę.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "Na Boga, czyś ty zupełnie postradał zmysły? Pół hiszpańskiego świata cię ściga. Narobisz więcej szkód niż pożytku. Rozwiąż swoje problemy, potem się zgłoś. To wszystko, co chciałem powiedzieć! Wynocha stąd!";
				link.l1 = "Hmm... Rozumiem.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Chcesz trochę akcji, co? Ha-ha! Dobrze... Ale ostrzegam cię, chłopcze, nie znajdziesz ze mną spokoju. Jeśli boisz się zapachu prochu albo nie potrafisz przelać krwi - drzwi są za tobą. Nie znoszę mięczaków. Również nie wytrzymasz ze mną długo, jeśli jesteś kapusiem albo szczurem, który lubi kraść partnerowi udział w łupach. Więc jak? Wchodzisz w to?";
			link.l1 = "Jestem z tobą, Marcus. Nie boję się walczyć i żaden pies nie może mi zarzucić, że jestem tchórzem czy zdrajcą.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Whoa, to dla mnie za trudne! Przepraszam, Marcusie, ale lepiej już się oddalę...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "Cóż, nadal tu jesteś?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Mam trochę jedwabiu do sprzedania.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "Już odchodzę.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ha-ha, no cóż, mój dzielny mały piracie, porozmawiajmy więc o interesach. Moje źródło w Santo Domingo poinformowało mnie o jakimś hiszpańskim kapitanie, który jest tak bogaty w niebieski bursztyn, że rozdaje go dziwkom. Słyszałeś o niebieskim bursztynie?";
			link.l1 = "Mam. Rzadki i cenny kamień.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Dokładnie. Nawet tutaj, bankierzy i jubilerzy płacą za to dobre pieniądze, a w starej, dobrej Europie można dostać dziesięć razy więcej. Bursztyn nie jest rzadkim kamieniem na Karaibach, ale niebieski jest rzadkością. A teraz mamy jakiegoś kastylijskiego chytrusa, który przechwala się, że ma więcej niebieskiego bursztynu niż bankierzy z Kuby i Hispanioli mają żółtego razem.";
			link.l1 = "Czy można ufać opowieściom jakiegoś pijanego Hiszpana? Znalazł trzy doubloony i wszystkim opowiada, że odnalazł El Dorado.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Nie zrobiłbym tego, ale faktycznie rozdawał niebieski bursztyn dziwkom. Coś w jego przechwałkach musi być prawdziwe. Idź do Santo Domingo i zbadaj sprawę. Jeśli znajdziesz złoże niebieskiego bursztynu, to będzie jeszcze lepiej. Zrób to, a gwarantuję ci nagrodę i szacunek w La Vega.";
			link.l1 = "A co jeśli twoje informacje są bezwartościowe?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "W takim razie udowodnij mi, że Kastylijczyk to kłamca.";
			link.l1 = "Dobrze. Kto jest Twoim źródłem w Santo Domingo?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Wait a minute, take a trading license for 60 days."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Wait a minute, take a 60-day trade license and a Spanish flag to land in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
						GiveNationLicence(HOLLAND, 60);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here you go, a 60-day trading license, longer than yours. As well as the Spanish flag for landing in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							GiveNationLicence(HOLLAND, 60);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here, take the Spanish flag for the Santo Domingo landings. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Potrzebujesz dziewki z burdelu imieniem Gabriela Chapado. Powiedz moje imię i hasło - 'Bursztynowy Naszyjnik'. Ona przekaże ci szczegóły. I nie trać czasu - informacja jest jeszcze świeża, ale za dzień lub dwa może się zdezaktualizować."+sTemp;
			link.l1 = "Zrozumiano, Marcus. Kieruję się do Santo Domingo.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.Block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "Już zostałem poinformowany o twoim przybyciu. Zdaj mi raport!";
			link.l1 = "Zajęłam się tym miłośnikiem niebieskiego bursztynu, chociaż to nie było łatwe. Udało mi się znaleźć jego złoża i je splądrować. Przyniosłam ci "+FindRussianQtyString(i)+" kawałki błękitnego bursztynu.";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Cóż to... Synu, pamiętasz moje ostrzeżenie o niebezpieczeństwach bycia szczurem? Co mi wtedy powiedziałeś? Żaden pies nie może cię za to winić? Myślisz, że jestem głupi, dzieciaku? Doskonale wiem, że splądrowałeś "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" kawałki niebieskiego bursztynu na Wybrzeżu Komarów. Teraz biegnij, mała szczuro, biegnij, i módl się, byśmy się nigdy więcej nie spotkali!";
				link.l1 = "Cholera!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					DeleteAttribute(pchar,"perks.list.FlagSpa"); 
					log_info("You have given spanish flag");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Świetna robota, chłopcze! Pokazałeś się z najlepszej strony: poradziłeś sobie z trudną sprawą i przyniosłeś wszystko, co zrabowałeś. Dobra robota! Cieszę się, że się na tobie nie pomyliłem.";
				link.l1 = "A co z moim udziałem, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+FindRussianQtyString(i)+" pieces of blue amber");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
            dialog.text = "Mówisz jak prawdziwy pirat, ha-ha-ha! Połowa łupu jest twoja. Weź to.";
			link.l1 = "Dzięki, kapitanie. Masz coś jeszcze dla mnie?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "Zawsze mam zadania dla zdolnych chłopców. Jest pewna delikatna sprawa, którą chcę, abyś się zajął. W Capsterville stoi statek o nazwie 'Wąż', pod dowództwem Geffreya Brooke'a, znanego również jako Łysy Geffrey. Pracuje dla mnie. Doskonały wojownik, wie wszystko o broni palnej i mieczach, ale kompletny idiota w każdej innej dziedzinie życia. Ale nie bądźmy zbyt surowi dla Łysego, nikt nie jest doskonały, ha-ha!\nWięc. Ten twardziel zaatakował konwój holenderski na północ od Saint Martin i zdobył barkę wypełnioną workami z pszenicą. Rzecz w tym, że udało mu się znaleźć ukryty jedwab okrętowy wśród worków. Naprawdę duży ładunek. Ten towar jest niezwykle cenny i rzadki, Holendrzy przywożą go z Europy wyłącznie dla potrzeb swojego wojska. Ten jedwab jest używany do specjalnych żagli, które zwiększają prędkość statku i zdolność żeglowania pod wiatr.\nKupno jest prawie niemożliwe, sprzedaż nie stanowi problemu, ale trudno jest znaleźć odpowiednią cenę. Ci przeklęci handlarze zawsze obniżają cenę! Wiem, że są na Karaibach ludzie gotowi zapłacić dobrą cenę w dublonach za zakup tego jedwabiu, a twoim celem jest znalezienie takich ludzi.\nCo? Jakikolwiek głupiec może splądrować karawany, ale handel to tylko dla ludzi, którzy mają choćby oznakę istnienia mózgu w czaszce. Planuję sprzedawać jedwab okrętowy co miesiąc, więc twoim celem jest znalezienie stałego kupca, który zapłaci co najmniej dwadzieścia złotych dublonów za belkę. Masz na to dwa miesiące, nie mogę trzymać Łysego Geffreya w Capsterville na zawsze.\nTo wszystko. Wypłyń do Capsterville i porozmawiaj z Geffreyem, zanim sprzeda ładunek przemytnikom za grosze. Już ci mówiłem, że jest trochę 'prostoduszny'.";
			link.l1 = "Hm... Rozumiem. Już jestem w drodze.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "Ha! Oto odważny kapitan "+GetFullName(pchar)+"! A co z kupcem?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "Znalazłem ci kupca. To szkutnik z Port Royal. Potrzebuje jedwabiu okrętowego do swojej produkcji i będzie mógł kupować partie po sto bel co miesiąc za 25 dublonów za belę. Jego ludzie będą odbierać towar od 10 do 15, w nocy, miejsce to Negril Cape. Hasło - 'Kupiec z Lyonu'. Zajęło mi ponad dwa miesiące, by znaleźć takiego kupca, Geffrey musiał już sprzedać jedwab przemytnikom. Przykro mi, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "Znalazłem dla ciebie kupca. To szkutnik z Port Royal. Potrzebuje jedwabiu do produkcji statków i będzie mógł kupować partie po sto zwojów co miesiąc za 25 дублонов за zwój. Jego ludzie będą odbierać towary od 10 do 15, w nocy, lokalizacja to Przylądek Negril. Hasło - 'Kupiec z Lyonu'. Łysy Geffrey już dostarczył pierwszą partię na Jamajkę.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "To wspaniale, mój przyjacielu! Dobra robota. Trudno znaleźć człowieka, który potrafi używać zarówno rąk, jak i głowy. Zobacz się ze mną za 20 dni, aby odebrać swoją nagrodę. Łysy Geffrey do tego czasu przyniesie pieniądze z pierwszej transakcji."; // правки прогона 3
			link.l1 = "Bardzo dobrze, Marcus. Do zobaczenia wkrótce. Mam nadzieję, że będziesz miał dla mnie kolejną robotę.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "Zrobię to. Do zobaczenia później.";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Szkoda, ale to wciąż ogromny sukces. Dobra robota! Nie dostaniesz swojej części od partii Geffreya, ale zasługujesz na nagrodę. Zobacz się ze mną za miesiąc, sprzedam wtedy pierwszą partię twojemu nabywcy i wtedy porozmawiamy.";
			link.l1 = "Bardzo dobrze, Marcus. Do zobaczenia wkrótce. Mam nadzieję, że będziesz miał dla mnie kolejną robotę.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "Nareszcie jesteś, "+pchar.name+"Porozmawiajmy o twojej nagrodzie.";
			link.l1 = "Ha-ha-ha, takie rozmowy to ja lubię! Zamieniam się w słuch.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Bald Geffrey sprzedał twemu kupcowi pierwszą partię 105 zwojów żaglowego jedwabiu. Skoro spodziewałem się sprzedać to po dwadzieścia doublonów za zwój, myślę, że uczciwie będzie oddać ci różnicę. To moja decyzja. Twój udział to 525 doublonów plus premia - doubloon za zwój. W sumie to 630 doublonów. Weź je.";
			link.l1 = "Podziękowania, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("You have received 630 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Jeszcze jedna rzecz. Możesz z tego uzyskać dodatkowy zysk.";
			link.l1 = "Interesujące... Mów dalej.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Twój kupiec chce, aby dostarczono więcej niż 100 bel jedwabiu w ciągu najbliższych dwóch miesięcy. Jeśli masz jakieś, przynieś mi od 20 do 100 beli za cenę 24 doblonów. Oferta będzie ważna przez dwa miesiące.";
			link.l1 = "Dobrze! Przyniosę więcej, jeśli będę miał jakiekolwiek.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Ile masz?";
			link.l1 = " "+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "Bardzo dobrze. Weź złoto - 24 doubloony za rzut, jak się umówiliśmy.";
			link.l1 = "Wdzięczność!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "Wezmę sto zwitków. Weź złoto - 24 doubloony za zwitek, jak się umówiliśmy.";
			link.l1 = "Wdzięczność!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Porozmawiajmy o czymś pilniejszym, chcesz zająć się czymś niebezpiecznym?";
			link.l1 = "Jasne! Ja i moi ludzie jesteśmy gotowi do wypłynięcia natychmiast.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "Na miłość boską, "+pchar.name+"gdzie, do diabła, byłeś? Pamiętasz, kiedy powiedziałem ci, żebyś do mnie przyszedł? Miałem dla ciebie robotę, a teraz jest zmarnowana dzięki twojemu doskonałemu wyczuciu czasu. Naprawdę mnie wkurzyłeś, chłopcze. Zjeżdżaj, nie pracuję z ludźmi, na których nie mogę polegać.";
			link.l1 = "No, cholera...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", as well as a trade license for 40 days."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", as well as a trade license for 40 days. Besides, how are you going to fool the bungler in the fort?! You will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
						GiveNationLicence(HOLLAND, 40);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here, a trading license for 40 days, more than yours. As well as the Spanish flag for landing in Maracaibo. You will return it upon arrival. The new generation, pah...";
							GiveNationLicence(HOLLAND, 40);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Then listen closely. Two months ago I had an appointment with a captain by the name of Jean Picard, also known as Jean the Handsome. He didn't show up to the meeting and since I was going to discuss serious matters with him, I did some investigation regarding his whereabouts. Turned out our good brave privateer and his brigantine had managed to engage in a fight with a Spanish heavy galleon under command of don Eduardo de Losad and he is a tough son of a bitch. As a result, Jean and what's left of his crew was taken to Maracaibo and sold to a local plantation. This is where he is, busy with honest labor, at the moment.\nYour tasks are: firstsly - investigate the details of his misfortunes, secondly - get him out from plantation alive and bring him here; I really need details of his story. I am assigning a captain of a barquentine called 'Moray' to assist you in this. Captain's name is Paul Chant also known as Pelly the Cutlass. Remember Geffrey? He is almost as dumb as him, but good at fighting too.\nHe will be waiting for you at cape Ragget Point, on Barbados. Find him and his 'Moray' and sail to Maracaibo. Cutlass will follow your orders without asking stupid questions. Actually, he won't be asking questions at all. Just do your job and come back here, I'll be waiting for you. Here is ten thousand pesos for future expenses"+sTemp+". Any questions?";
			link.l1 = "Nie. Wszystko jasne. Kierujemy się na Barbados.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Życzę ci więc szczęścia. Działaj szybko, nie każ Cutlassowi i biednemu Jeanowi czekać.";
			link.l1 = "Pewnie, szefie! Już idę.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "Witaj z powrotem, mój dzielny korsarzu, ha-ha! Zniszczyłeś hiszpańską eskadrę? Picard już mi powiedział. Dobra robota!";
			link.l1 = "Tak, moi chłopcy porządnie im przyłożyli, gdy odpływaliśmy z Maracaibo.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "Witamy z powrotem, mój odważny korsarzu, ha-ha! Picard już mi powiedział. Dobra robota!";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "Widzę w twoich oczach, że czekasz na swoją nagrodę. Słusznie. Jean ci zapłaci, w końcu to jego życie staraliśmy się tam uratować. Wyślij mu rachunek, ale później - chłopak nie ma załogi i statku. To sprytny dzieciak, tak jak ty, więc jego obecny stan nie potrwa długo.";
			link.l1 = " Cóż... Poczekam na odpowiedni moment. Jakieś zlecenie dla mnie, Marcus? Bez ratowania czy szukania kogokolwiek?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "Zmęczony byciem najjaśniejszą świecą? Muszę cię rozczarować: mam dość bezmózgich osiłków jak Cutlass, twoje talenty wykorzystam odpowiednio. Będę miał dla ciebie zadanie za miesiąc, teraz powinieneś popłynąć na Isla Tesoro i zobaczyć się z Pasquale Lavoisierem, on jest kupcem z Sharptown.\nProsił, żeby jak najszybciej przysłać mu surowego pirata do poważnego interesu - najprawdopodobniej to, czego chcesz: mniej myślenia, więcej strzelania. Masz tydzień, żeby się mu pokazać, więc nie trać czasu, bo stracisz tę misję. I bądź grzeczny, nie próbuj go oszukać, ten człowiek jest szanowany wśród Braci. Teraz idź i zobacz się ze mną za miesiąc. Nie spóźnij się!";
			link.l1 = "Dobrze, Marcus. Do zobaczenia!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "Ho ho! Martwy człowiek powrócił! Już cię pochowaliśmy, chłopcze! Ale wygląda na to, że wciąż żyjesz.";
			link.l1 = "Jak widzisz, Marcus...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "To dlaczego podróż z Maracaibo na Hispaniolę zajęła ci tyle czasu? Już nie należysz do mojej organizacji, chłopcze. Cieszę się, że jesteś żywy, ale nie ma tu już dla ciebie pracy.";
			link.l1 = "Eh!.. Jaka szkoda...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "Do diabła "+pchar.name+" , gdzie byłeś?! Mówiłem ci, żebyś się ze mną zobaczył za miesiąc! To nie jest wojsko, ale trochę cholernej dyscypliny się oczekuje! Zjeżdżaj, nie będę z tobą więcej pracować!";
				link.l1 = "Jak sobie życzysz...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = " "+pchar.name+", mówiłem ci 'zobacz się ze mną za miesiąc'. Nie mam teraz dla ciebie czasu.";
				link.l1 = "Dobrze...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "Agent Lavoisiera powiedział mi, że oszukałeś go z jego czarnym drewnem. Ostrzegałem cię, żebyś nie był szczurem i był uczciwy wobec Pasquale'a. Złamałeś oba moje zasady. Jesteś mądrym dzieciakiem, ale to jest nie do przyjęcia. Wynoś się stąd i zapomnij drogę do tego miejsca.";
				link.l1 = "Cholera...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "Agent Lavoisiera powiedział mi, że zrobiłeś go w konia z jego czarnym drewnem - nie dostarczyłeś całego ładunku. Gdyby to był bezmózgi Szabla albo Łysy, może bym uwierzył, że nie zdobyli całego ładunku, ale taki sprytny dzieciak jak ty... Postanowiłeś oszukać Pasquale? Prosiłem cię 'nie oszukuj go'! Nie mam już do ciebie zaufania i nie mam z tobą żadnych interesów. Wynoś się stąd i zapomnij drogę do tego miejsca!";
				link.l1 = "Twój Lavoisier to sam szczur!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ha! Charlie Prince, odważny kapitan! To twoje nowe imię w La Vega, jeśli jeszcze nie wiedziałeś. Więc, czy podobało ci się bycie brutalem? Nie? Czy tym razem Pani Fortuna cię opuściła? Tak właśnie żyją moi bezmózgi agenci jak Cutlass: dziś bawi się w burdelu, marnując wszystko, co zarobił, za tydzień jest u moich drzwi, błagając o parę tysięcy, żeby zapłacić swojej załodze pełnej idiotów, takich jak on. Cóż, nieważne. Przejdźmy do interesów?";
				link.l1 = "Jasne!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "Ha! Charlie Prince, odważny kapitan! Ha-ha! Agent Lavoisiera powiedział mi, że dobrze ci poszło. Cieszę się, że udało ci się okazać pewien szacunek naszemu dorobkiewiczowi.";
			link.l1 = "Nie zaszkodziłoby, gdyby był bardziej hojny...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Pamiętasz, co mówiłem o bezmyślnych brutali i nabywcach kradzionych towarów? Właśnie. Nigdy więcej nie bierz takiej roboty. Zostaw to Szabli i takim jak on. Nieważne. Pogadajmy o interesach?";
			link.l1 = "Na pewno!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Świetnie! Jean Picard tu przychodzi, opowie ci więcej. Ty i Jean będziecie razem pracować nad tą misją. Dodatkowo to jego szansa, by spłacić ci dług... O, tam jest!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "cartridge", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "Mój człowiek dołączy do twojego rajdu. Nazywa się Luka Bayard, znany głównie jako Luke Leprechaun. On i jego ludzie to bukanierzy - łowcy, którzy spędzili większość życia na polowaniu w lasach Hispanioli. Są mistrzami wędrowania przez dżunglę, dodaj do nich swoich wojowników i uznaj Meridę za swoją. Weźmiesz trzecią część łupu. Resztę zabierze Jean. Jean, oddasz swój dług temu dzielnemu kapitanowi ze swojej części, a potem przyniesiesz mi to, co zostanie. Rozliczymy się między sobą wtedy. Pytania? Wspaniale! Leprechaun będzie czekał na ciebie w naszym porcie. Powodzenia korsarze, ha-ha!";
			link.l1 = "... ";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "Witaj z powrotem, mój dzielny rozbójniku! Plotki o twoim napadzie już do nas dotarły.";
			link.l1 = "Nie mogę powiedzieć, że lubię to słyszeć. Takie rzeczy lepiej, żeby pozostały nieznane...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Uwierz mi, nigdy nie są, przyjacielu. Nieważne. Czy Picard spłacił swój dług wobec ciebie?";
			link.l1 = "Tak.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Bardzo dobrze. Czy Luke Leprechaun zrobił na tobie dobre wrażenie?";
			link.l1 = "Zrobił to.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Doskonałe w takim razie. Wszyscy są zadowoleni, wszyscy są opłaceni.";
			link.l1 = "Masz dla mnie robotę, Marcus?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "Wiesz, Marcus, przemyślałem wszystko i ta robota nie jest dla mnie. Przykro mi, ale już podjąłem decyzję.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "Jeszcze żadnej prawdziwej roboty. Choć mam osobistą przysługę do załatwienia. Zainteresowany?";
			link.l1 = "Oczywiście, szefie. Jaka przysługa?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "Przy brzegu La Vega stoi pinasa 'Kittie'. Czeka tam już od dni na eskortę do Bridgetown. Nie ma mowy, żebym pozwolił jej płynąć tam samotnie z oczywistych powodów. Czy byłbyś na tyle uprzejmy, by ją eskortować? Będę miał dla ciebie prawdziwą robotę, gdy wrócisz. I, oczywiście, pieniądze, żeby ci zapłacić za tę eskortę.";
			link.l1 = "Umowa stoi.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Nieźle! Dobra żegluga.";
			link.l1 = "Dzięki!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "Co?! Wyciągnąłem cię z ulicy, napełniłem kieszenie bursztynem i klejnotami! Tak mi się odpłacasz?";
			link.l1 = "Merida pokazała mi, że nie jestem wystarczająco bezduszny do tej roboty. Nie tak bezduszny jak ty i twoi ludzie. Nie bądź zły.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "Słabeusz! No, spadaj! Idź się męczyć z ładunkiem albo, lepiej jeszcze, zapij się na śmierć jak reszta nieudaczników!";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ach, oto jesteś... Już na ciebie czekałem. Oto 10.000 za eskortę 'Kittie'.";
			link.l1 = "Dzięki... Mam coś do omówienia z tobą, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "Czyżby?! Ha-ha! Strzelaj!..";
			link.l1 = "Pamiętasz, jak Jean Picard został zniewolony? Najpierw splądrował holenderski karawan razem z brytyjskim korsarzem, a potem to samo zrobiono z nim przez hiszpański ciężki galeon.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Pamiętaj. I co?";
			link.l1 = "Zostałem zaczepiony w Bridgetown przez Ignacio Marco. Ten sam portugalski kapr, który służy Anglii. Zaproponował mi splądrowanie holenderskiej karawany w pobliżu brzegów niezamieszkałej wyspy pomiędzy Curaçao a Trynidadem.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "No, no... Zgodziłeś się?";
			link.l1 = "Zrobiłem to. Po pierwsze, był to dobry interes. Po drugie, przypomniałem sobie historię Picarda i postanowiłem to zbadać...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "Założę się, że tak zrobiłeś.";
			link.l1 = "Tak. Był karawan, zrobiliśmy robotę czysto i schludnie. Potem podzieliliśmy łupy na brzegu, ale najpierw cicho posłałem wartownika z lunetą na wzgórze. I to się opłaciło, bo wkrótce pojawiła się hiszpańska eskadra prowadzona przez ciężki galeon.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "Twój wspólnik z pewnością uciekł, więc Hiszpanie cię ścigali?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Dokładnie. Nawet na niego nie zwrócili uwagi. Szkoda dla nich: tak mocno walczyliśmy z Hiszpanami, że nigdy tego nie zapomną. Ci Kastylijczycy byli dobrymi wojownikami, ale udało nam się zniszczyć całą eskadrę.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Dokładnie. Nawet nie zwrócili na niego uwagi. Chociaż udało mi się uciec. Dzięki mojemu strażnikowi...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Heh! Rozwalić eskadrę Eduardo de Losad! Tyś morski diabeł, książę! Założę się, że Hiszpanie już wysłali łowców za twoim tyłkiem.";
			link.l1 = "Niedobrze dla nich... Niemniej jednak powinniśmy rozprawić się z tym szumowiną Ignacio. Jeśli wiesz, co mam na myśli.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Heh! Mogę sobie tylko wyobrazić burdel, jaki się rozpętał, gdy Kastylijczycy zorientowali się, że im się wymknąłeś! Dobra robota!";
			link.l1 = "Ich problem, nie mój. Niemniej jednak powinniśmy zająć się tym łajdakiem Ignacio. Jeśli wiesz, co mam na myśli.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "Zajmę się tym. Powinniśmy dowiedzieć się więcej o tym Ignacio Marco. Może pracować dla kogoś. Jego 'zainteresowanie' moimi ludźmi jest podejrzane. Jakim statkiem włada?";
			link.l1 = "Polaker, 'Torero'. Unikalny statek, musi być oryginalnego projektu.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Dobrze, łatwiej będzie ją wtedy śledzić... Zrozumiałem. A dla ciebie, książę, mam robotę. Gotowy na to?";
			link.l1 = RandSwear()+"Jak najbardziej, szefie!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Słuchaj zatem. Jakiś czas temu mieliśmy w naszej okolicy ciekawego pirata. Nazywał się Wulfric Iogansen, znany również jako Czerwony Wilk. Bardzo barwna postać. Przybył tutaj z północy Europy kilka lat temu. Ten Wiking nie płacił Levasseur'owi za ochronę, nie zaprzyjaźniał się i trzymał się na uboczu. Bardzo tajemniczy typ, nikt z jego załogi nigdy nie opuścił go żywy. Krążyły pogłoski, że osobiście odcinał języki tym, którzy w karczmach rozwodzili się o ich napadach...\nW przeciwieństwie do większości z nas, Wulfric nigdy nie trwonił pieniędzy na dziwki czy trunki. Nigdy nie sprzedawał swego łupu za grosze. Nigdy nie ufał bankierom i nigdy nie zmieniał statków. Miał świetną korwetę, 'Freyja', i lojalną załogę, której dobrze płacił za służbę i milczenie. Wierzę, że planował zgromadzić jak najwięcej złota, a potem wrócić do Europy i żyć tam jak król.\nNie powiodło mu się to z powodu hiszpańskich łowców. Ten człowiek wyrządził Hiszpanii kolosalne szkody i straty, więc ekspedycje karne dopadły go na wodach Hispanioli, zatopiły 'Freyję' i zabiły całą załogę wraz z Wilkiem. Otoczony na płytkiej wodzie przez hiszpańskie statki, Czerwony Wilk spotkał swoją śmierć.\nRzecz w tym, że wszyscy w La Vega wiedzieli o skarbach Wilka i nawet znaleźli zatopioną 'Freyję', ale ani miejscowi, ani indiańscy nurkowie nie znaleźli żadnych skarbów. Nie był głupcem i musiał mieć gdzieś w tamtym miejscu ogromny skarb, o którym wiedział tylko on i jego załoga, ale nie możemy ich zapytać z... oczywistych powodów. Ale teraz nadchodzi ciekawa część: mam jego nienaruszony dziennik okrętowy, który był ukryty w zamkniętej skrzyni na jego statku. Nie ma w nim oczywistych wskazówek do skarbu, ale możesz spróbować je znaleźć między słowami. Przeczytaj dziennik, dowiedz się, gdzie Wiking ukrył swoje skarby po dwóch latach rabowania na Karaibach i znajdź je. Jeśli ci się uda, dwie trzecie są twoje. Wchodzisz w to?";
			link.l1 = "Hm... brzmi to jak szukanie czarnego kota w ciemnym pokoju. Gdzie jest dziennik?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Proszę, weź to. Powodzenia!";
			link.l1 = "Dzięki, przyda mi się...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "Ach, oto nasz dzielny kapitan. Co z skarbami Czerwonego Wilka?";
			link.l1 = "Pracuję nad tym. Potrzebuję twojej pomocy w tej sprawie.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "Zamieniam się w słuch.";
			link.l1 = "Jest słowo, którego nie znam, zapisane kilka razy w dzienniku Wulfrica 'Gord'. Muszę poznać jego znaczenie, aby kontynuować śledztwo.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Gord, powiadasz... Nigdy o tym nie słyszałem. Dobrze, zobacz się ze mną za tydzień: skonsultuję się z kilkoma mądrzejszymi, którzy służą jako kwatermistrze na statkach. Przynajmniej wiedzą, jak liczyć i czytać. Może dadzą nam jakiś pomysł.";
			link.l1 = "Dobrze Marcus. W takim razie widzimy się za tydzień.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "Mam dla ciebie odpowiedź. Jeden mądrala mnie oświecił. Gord to ufortyfikowane osiedle wolnego jarla.";
			link.l1 = "Wolny jarl? Kto to taki?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Coś w rodzaju pirackiego admirała Wikingów. Na przykład, ja jestem wolnym jarlem, a La Vega to mój gród. Wygląda na to, że Czerwony Wilk lubił historię swoich przodków, ha-ha! Czy ta informacja ci pomogła?";
			link.l1 = "Jeszcze nie wiem. Powinienem najpierw porównać notatki. Gord oznacza osadę wtedy... Dziękuję, Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "Więc? Twoja zadowolona gęba mówi mi, że odniosłeś sukces.";
			link.l1 = "Tak. Skarb Czerwonego Wilka został znaleziony! Choć nie było łatwo.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "Ile nasz Wiking zakosił?";
			link.l1 = "750.000 pesos i 900 dublonów.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Ho-ho! Dobrze się spisałeś, książę. Co z moim udziałem?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Oto, bierz to. Zgodnie z naszą umową: 250 000 pesos i 300 dublonów.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Wszystkie peso i dublony są w mojej kajucie. Daj mi minutę, by je tu przynieść!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "Przyniosłeś mój udział?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Proszę, weź to. Zgodnie z naszą umową: 250 000 pesos i 300 doublonów.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Tak-tak, już jestem w drodze!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Bardzo dobrze. Znowu świetnie się spisałeś. Dobra robota!";
			link.l1 = "Markusie, odkopałeś coś na temat Ignacia Marco?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "Tak, ale najpierw muszę to zweryfikować...";
			link.l1 = "Co?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "Podejrzewam, że Marco jest z kimś powiązany... I musisz to dla mnie odkryć. Popłyń na Martynikę. Zostaw swój statek w Saint Pierre i przedostań się do Le Francois przez dżunglę. Powiedziano mi, że nasz człowiek został tam widziany. Nie pytaj piratów naokoło, po prostu obserwuj. Gdy znajdziesz tego człowieka, śledź go i zobacz, dokąd pójdzie lub z kim się spotka. Nie atakuj go ani jego statku, bo w ten sposób zrujnujesz plan, który właśnie przygotowuję! Ostrzegłem cię!\nŚledź go i obserwuj, wróć do mnie, gdy dowiesz się wystarczająco dużo. Rozumiem, że twoje ręce chcą udusić drania, ale zachowaj spokój. Teraz idź. Masz trzy tygodnie. Powodzenia.";
			link.l1 = "Już idę, szefie.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "Cholera, książę! Mógłbyś mieć zemstę i piekielną sumę pieniędzy, gdybyś nie był tak wolny! Nie spodziewałem się tego po tobie, ale ponieważ jesteś dobrym dzieciakiem, wybaczam ci. Będziesz miał szansę odzyskać swoją reputację w moich oczach za miesiąc. Zbieram wszystkich na rajd!\nPrzyjdź do mnie za miesiąc na jednym, ale potężnym statku. Luke, Cutlass, Geffrey i Jean też wezmą w tym udział. Nie spóźnij się, nawet o dzień!";
				link.l1 = "Rozumiem, Marcus. To się więcej nie powtórzy!";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "Dobre wyczucie czasu! Zgłoś się do mnie, teraz.";
			link.l1 = "Znalazłem mojego dłużnika w Le Francois. Jego polakra była częścią eskadry składającej się z korwety i fregaty. Sam Marco składał wizytę u Barbasona, mieli spotkanie u niego przez dwie godziny, inni goście zostali odesłani przez jego strażników. Potem wyszedł z domu z dwoma ponurymi typami: jeden był rudowłosy i brodaty w reiterze z kirysem, drugi miał wąsy i nosił ciężką zbroję. Wszyscy poszli do portu i odpłynęli, zanim dotarłem do Saint Pierre.";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "To dobrze. Teraz widzę cały obraz. Te dwa dranie, których widziałeś, pracują albo dla Barbazona, albo dla Jackmana. Są prawie tacy jak mój Łysy i Szabla, ale lepiej walczą. Rudzielca nazywają Włóczęga, jest kapitanem 'Mątwy', korwety, a gość z wąsem to Upiór, pływa na 'Bezlitosnej', fregacie. Co do naszego przyjaciela Ignacio - pracuje nie tylko dla Brytów i hiszpańskiego dona Losada, ale także dla Barbazona. Dlatego próbował wrobić ciebie i Picarda.";
			link.l1 = "Dlaczego?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "Rozkaz Barbazona. Nie wiedziałeś, ale Jacques nigdy nie przepuści okazji, by nasikać mi do owsianki. Nigdy nie wystąpiłby przeciwko mnie otwarcie z oczywistych powodów, więc działa za moimi plecami. Wiedział, że Picard i ty jesteście moimi ludźmi. Wysłać swojego najemnika za tobą to było w jego stylu i nie wysłał idioty, jak się przekonałeś.";
			link.l1 = "Odwiedzę Barbazona, jak tylko załatwię sprawy z Marco...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Wybij sobie tę bzdurę z głowy! Nie masz szans przeciwko Barbazonowi w otwartej walce. Łatwo cię załatwi. Odpłacimy mu jego własnym podstępem - uderzając w jego wspólników. Jesteś gotowy to zrobić? To brudna robota.";
			link.l1 = "Brzmi jak interes dla mnie!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Włóczęga, Goul i inny człowiek Barbazona zwany Joker Jim mają plan, by przechwycić jeden z hiszpańskich statków Złotej Floty. Całą operację zaplanował sam Barbazon, a ja zdołałem dowiedzieć się szczegółów od moich szpiegów. Jeden ciężki galeon Złotej Floty zatrzymał się w Hawanie w stoczni, podczas gdy cała eskadra odpłynęła do Hiszpanii. Galeon został naprawiony i wkrótce ruszy do Europy, wraz z dwoma innymi statkami. Eskadra wyruszy z Kuby na północny wschód, ale nie wiem, jaką trasą.\nZostałem poinformowany, że hiszpańskie statki zamierzają żeglować do Santo Domingo, potem wzdłuż brzegów Puerto Rico i prosto na ocean. Barbazon również o tym wie. Jednakże, ponieważ Hispaniola może być opłynięta nie tylko od południa, ale także od północy, zmieniając trasę i wychodząc na ocean przez Turks lub Isla-Tesoro, bez wchodzenia do Santo Domingo, Jacques postanowił działać ostrożnie i wysłał przebiegłego lisiego Ignacio na Kubę.\nMarco ma za zadanie zdobyć grafik żeglugi hiszpańskiego galeonu, który ma wypłynąć z Kuby i ma się później spotkać z resztą Floty. Ma kontakty wśród Hiszpanów, więc to zadanie nie będzie dla niego problemem. Reszta bandy Barbazona czeka na Marco na Saint Martin, co jest optymalnym miejscem, by rozpocząć polowanie na tę zdobycz. Ponieważ Marco i Holendrzy nie są w najlepszych stosunkach, nie będzie mógł dostać się w wody Saint Martin, więc będzie musiał wysłać swoim kamratom wiadomość na odległość...";
			link.l1 = "Chyba wiem, co mam tu robić...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "Uderza mnie, że jesteś taki bystry, ale jeszcze nie skończyłem. Zmieszałem te plany z pomocą Gabrieli Chapady. Znasz ją. Razem poinformowaliśmy Hiszpanów, że piracka zasadzka będzie ustawiona niedaleko Portoryko. Więc galeon nie będzie tamtędy płynął, ale zamiast tego wysłali tam potajemnie eskadrę łowców piratów. Masz kilka zadań. Pierwsze to znaleźć i przejąć 'Torero'. Sądzę, że wiesz, co zrobić z jej kapitanem.";
			link.l1 = "Oczywiście...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "Po drugie, będziesz musiał dowiedzieć się prawdziwego kursu hiszpańskiego złotego galeonu. Marco musi mieć jej rozkład. Zdobądź go i prześlij mi.";
			link.l1 = "Jak?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "Powietrzem. Weź klatkę... To jest Spyke, pocztowy gołąb urodzony i wychowany tutaj, w La Vega. Zawsze znajdzie drogę powrotną, nawet z Trynidadu. Gdy zdobędziesz harmonogram, napisz notatkę, przyczep ją do jego nogi i wypuść go. Spyke przyleci do mnie za kilka godzin. Dbaj o niego, książę!";
			link.l1 = "Oczywiście, szefie!";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Trzecie, wypłyń do Saint Martin na 'Torero'. Tylko na niej samej! Inaczej zaczną się podejrzewać zbyt wcześnie. Wyślij im sygnał, aby popłynęli do Puerto Rico, gdzie czekają Hiszpanie. Ich kody sygnałowe muszą być w papierach Marco. Albo możesz nauczyć się ich od niego osobiście.";
			link.l1 = "Rozumiem. Sprytny ruch, by wysłać ludzi Barbazona do Hiszpanów, ha-ha!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Dokładnie! Zadaszę mu cios z cienia. Tak jak on to zrobił. I jeszcze jedno: gdy tylko wyślesz im sygnał, natychmiast żegluj, aby przechwycić hiszpański galeon i jego eskortę. Nie będzie czasu do stracenia.";
			link.l1 = "Na polakrze? Przeciwko ciężkiej galeonie i jeszcze dwóm statkom, i to na pewno nie są szkunery? Rozszarpią mnie na strzępy!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "Przestań płakać jak mała dziewczynka! Czemu myślisz, że wyślesz mi Spyke'a? Nie zostaniesz bez posiłków. Po prostu nie pozwól karawanie uciec, nie pozwól im dotrzeć do oceanu. Zrozumiano?";
			link.l1 = "Tak, szefie.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "Twoja nagroda to duży ładunek złota plus polakra Marco. Mówią, że to przeklęcie dobry statek. Jakieś pytania? Rozumiesz swoją misję?";
			link.l1 = "Nie jestem Cutlass, wiem, co robić. Gdzie powinienem przechwycić 'Torero'?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "Podczas gdy my tu gadamy, statek szybko płynie prosto do Philipsburga z Kuby. Musi być teraz gdzieś w okolicach Tortugi albo trochę na wschód od niej. Więc podnieście kotwice i żeglujcie do Saint Martin, złapcie 'Torero' niedaleko wyspy, tylko nie dopuście, by ludzie Barbazona zobaczyli walkę, bo inaczej mój plan weźmie w łeb.";
			link.l1 = "Już się robi!";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			SetCharacterPerk(pchar, "FlagSpa");
			log_info("You have received a spanish flag");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "Co do diabła? To by cię trzepnęło pogrzebaczem z kominka, książę. Nie myślałem, że będę musiał mówić o elementarnych rzeczach. Trzymaj hiszpańską flagę, inaczej wszystko zawalisz, zanim nawet zaczniesz. Oddaj mi ją. A teraz wynoś się stąd!";
			link.l1 = "Już jestem na morzu, Szefie";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "Więc książę, spieprzyłeś wszystko, co?";
			link.l1 = "Zrobiłem to. Ta misja była o wiele większym wyzwaniem, niż myślałem. Możesz wygłosić mi wkurzającą mowę i pokazać mi drzwi.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "Chodź, przestań. To się zdarza. Jesteś dobrym korsarzem i wszyscy czasem zawodzimy. Szkoda, że nie zdobyliśmy tego złota... ale jeśli nie zdobyliśmy go w jednym miejscu, powinniśmy w innym, ha-ha! Będziesz miał szansę odzyskać swoją reputację: przyjdź do mnie za trzy tygodnie, i najlepiej na silniejszym statku, ale tylko na jednym - będziemy całą flotyllą. Zbieram wszystkich na rajd!\nPrzyjdź do mnie za trzy tygodnie na jednym, ale potężnym statku. Luke, Cutlass, Geffrey i Jean również wezmą w tym udział. Nie spóźnij się!";
			link.l1 = "Nie będę, szefie!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given a spanish flag");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "Ho-ho, Ahoj, dzieciaku! Nie spodziewałeś się mnie tu zobaczyć, prawda? Ha-ha-ha! W końcu znaleźliśmy hiszpańską karawanę...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Tak szefie, mamy, chociaż nie było łatwo.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Tak, ale złoty galeon zatonął ze swoim całym złotem.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "Ile złota zdobyliśmy, książę?";
			if (iTotalTemp < 1) link.l1 = "Eh... Nic.";
			else link.l1 = "Heh... "+iTotalTemp+"w sumie!";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "Cholera! Hiszpanie musieli to wrzucić do morza, żebyśmy tego nie dostali. Przynajmniej za to zapłacili. Tak samo jak ludzie Barbazona, co też jest zwycięstwem...";
				link.l1 = "Przepraszam za złoto... Co dalej, Marcus? Jedziemy do La Vega?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Żałosne. To nawet nie rekompensuje mojej podróży tutaj. Hiszpanie musieli to wyrzucić do morza, żebyśmy tego nie dostali. Przynajmniej za to zapłacili. Tak samo jak ludzie Barbazona, co jest również zwycięstwem...";
				link.l1 = "Przepraszam za złoto... Podzielmy się nim mimo wszystko.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "To marna zdobycz. Ledwie wystarczy na pokrycie kosztów. Hiszpanie musieli część z tego wrzucić do morza, żebyśmy tego nie dostali. Przynajmniej za to zapłacili. Tak samo jak ludzie Barbazona, co też jest zwycięstwem...";
				link.l1 = "Przykro mi z powodu złota... Podzielmy je mimo wszystko.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Nieźle, choć spodziewałem się lepszego. Hiszpanie musieli wyrzucić część tego do morza, abyśmy tego nie dostali. Przynajmniej za to zapłacili. Jak również ludzie Barbazona, co też jest zwycięstwem...";
				link.l1 = "Podzielmy łup!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Znakomicie! Zdobyliśmy niezłą zdobycz, mój przyjacielu! A ludzie Barbazona dostali to, na co zasłużyli, ha-ha!";
			link.l1 = "Heh, to kupa złota! Podzielmy się tym!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "„... jak zawsze robimy w Bractwie - sprawiedliwy podział dla każdego. Możesz zatrzymać 'Torero', to twoja zdobycz.”";
			link.l1 = "Co dalej, Marcus? Czy płyniemy do La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "Zdecydowanie będę w La Vega, czekać będę na ciebie przez trzy tygodnie. Przyjdź, gdy będziesz gotowy. Najlepiej na mocniejszym statku, ale tylko na jednym - będziemy całą eskadrą. Zbieram wszystkich moich ludzi na wyprawę. Pójdziesz pod moim dowództwem, Jean Przystojniak, Łysy Geoffrey, Tasak Pelly i Luke Krasnal również. Przygotuj się. Czeka nas poważna wyprawa i całkiem spore łupy. Wszystkie szczegóły poznasz później.";
			link.l1 = "Dobrze, szefie! Do zobaczenia w La Vega za trzy tygodnie.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "Żegnaj, łotrze! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "Czy coś jeszcze?";
			link.l1 = "Nie, raczej nie. Już idę na swój statek.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Heh! A czyja to wina, książę? Twoja?";
			link.l1 = "Przykro mi, szefie, ale obaj byliśmy wystarczająco dobrzy... Ty też świetnie strzelałeś. Nawiasem mówiąc, dobre celowanie...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Cokolwiek. Wina leży po obu stronach. Jednak nie jesteśmy z pustymi rękami - ludzie Barbazona dostali to, co dla nich mieliśmy, co samo w sobie jest zwycięstwem...";
			link.l1 = "Przepraszam za złoto... Co dalej, Marcus? Czy płyniemy do La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Ty, książę, ogłupiałeś? Mówiłem ci, żebyś przyprowadził tylko jeden statek! Idź pozbyć się nadmiaru i wracaj jak najszybciej! Teraz!";
				link.l1 = "Dobrze, dobrze!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = " Książę, czy postanowiłeś być moim drugim Kordelasem? Dlaczego przyprowadziłeś do mnie statek handlowy? Liczyłem na ciebie! Idź i przynieś porządny okręt wojenny! Teraz! ";
				link.l1 = "Dobrze, dobrze!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Książę, zaskoczyłeś mnie. Mówiłem ci, żebyś przyprowadził okręt wojenny! Jak masz mi pomóc na tej łajbie? Wróć tutaj z okrętem trzeciej lub drugiej rangi, nie mniej i nie więcej! Teraz! Nie będę na nikogo czekać.";
				link.l1 = "Dobrze, dobrze!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Książę, dlaczego nie przyniesiesz tutaj Suwerena Mórz? Kiedy kazałem ci przynieść okręt wojenny, nie miałem na myśli przynieść pieprzonego okrętu liniowego! Wróć tutaj na okręcie trzeciej lub drugiej rangi! Teraz! Nie zamierzam na nikogo czekać.";
				link.l1 = "Dobrze, dobrze!";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "Dobre wyczucie czasu, korsarzu! Cieszę się, że widzę cię w jednym kawałku! Gotowy na rejs?";
			link.l1 = "Pewna rzecz, szefie. Zawsze gotowy.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "Przy okazji, chcesz wiedzieć o eskadrze Barbazona, którą wysłałeś do Puerto-Rico?";
			link.l1 = "Całkowicie wyleciało mi to z głowy. Pewnie, że chcę. Czy znaleźli swój koniec?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "Do diabła, tak właśnie było! Okręt flagowy - fregata Joker Jima 'Sowa', spłonęła doszczętnie. Sam Joker Jim zniknął bez śladu. Tramp i Ghoul dostali mocno po łapach, ale udało im się uciec: Tramp - na Tortugę, pod ochronę dział La Rochy, Ghoul - na Isla Tesoro. Pasquale powiedział mi, że Ghoul również osadził swój statek na rafach w pobliżu Sharptown i ledwo z nich zszedł. Mistrz Alexus ma teraz sporo pracy, hehe. Generalnie, Hiszpanie mnie trochę zawiedli. Myślałem, że pozabijają wszystkich.";
			link.l1 = "Heh. Cóż, i tak nasikaliśmy w buty Barbazona. Przekazaliśmy mu wiadomość.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "Prawda. Porozmawiajmy o interesach.";
			link.l1 = "Zamieniam się w słuch.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "Moja służba wywiadowcza w postaci mojego dobrego przyjaciela Bernarda Vensana doniosła o ogromnej kupie złotych sztabek, które Hiszpanie przechowują w Kartagenie. Pod jej fortem, żeby być bardziej precyzyjnym. Normalnie byłoby to przypisane Złotej Flocie Hiszpanii, ale tym razem to my je zabierzemy. Zmierzamy do Głównego Południa, by szturmować Kartagenę.";
			link.l1 = "Argh! Czy dobrze usłyszałem? Zamierzamy splądrować całą kolonię, z cholerną fortecą?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "Nie wybieram się z tobą do Cartageny, Marcus. Spalenie całego miasta to nie moja historia.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "Słyszałeś dobrze. To dokładnie to, co zamierzamy zrobić. Mój okręt wojenny zajmie się fortem, oczywiście z twoją pomocą. Śmiały Jeffrey przewiezie wojska lądowe na swoim nowym East-indianie skradzionym Holendrom. Pelly w końcu pozbył się swojego zużytego brygantyny i zdobył porządną korwetę, oczywiście nie bez mojej pomocy finansowej. Paul Chant i ty jesteście odpowiedzialni za zniszczenie floty patrolowej, a także wasze załogi wezmą udział w szturmie, a ty, Charles, taki dobry wojownik i kapitan, pomożesz mi zniszczyć fort.\nJean Picard się nie pojawił, co jest dziwne, ponieważ jego korweta była widziana w Port Royal. Cóż, jeśli nie interesuje go hiszpańskie złoto, to jego problem, więc niech go diabli wezmą. Zamiast niego, do rajdu dołączy mój przyjaciel Bernard Vensan. Plus, Leprechaun ze swoimi bukanierami wesprze nasze wojska. Weźmiemy złoto z fortu i okup z miasta. Nie zapomną tego, ha-ha!\n Teraz odpocznij. I dołącz do mnie i innych kapitanów w tawernie dziś wieczorem! Powinniśmy wypić za naszą sprawę! Zamówię barmanowi, żeby wyprosił wszystkich miejscowych alkoholików, więc tylko szóstka z nas i kilka czarujących dziewczyn będzie w tawernie. Dziś wieczorem pijesz ze swoimi towarzyszami, a jutro rano poprowadzisz eskadrę, wytyczysz kurs. I postaraj się doprowadzić nas do Kartageny tak szybko, jak to możliwe. Wszystko jasne?";
			link.l1 = "Aye, aye, szefie!";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "Ty... ty... Szalony Książę! Zastawiasz na mnie pułapkę?! Wiesz co, do diabła z tobą! Miałeś szansę dołączyć do Bractwa, miałeś szansę uciec z szeregów tego bezużytecznego bydła. A ty po prostu tchórzliwie zmarnowałeś tę szansę. Wynoś się ze swoim jęczeniem! Słabeusz! Jeszcze raz cię zobaczę - spuszczę psy!";
			link.l1 = "... ";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "Książę, w końcu! Spójrz, chłopaki - przygotowaliśmy dla niego prezent, a on włóczy się, nie wiadomo gdzie! Siadaj, zaczynamy!\nWięc, dzielni korsarze! Złoto Cartagena na nas czeka, ha-ha! I zdobędziemy je, przysięgam na grzmot! Ale ci, którzy dobrze pracują, muszą też dobrze odpoczywać! Dlatego dzisiaj spędzimy cudowny czas w tym wspaniałym przybytku. Nalej sobie rumu, im więcej, tym lepiej! Napełnijcie swoje kufle po brzegi! Za wiatr skarbów, za wiatr szczęścia! Pijemy do dna!\nDla was, najlepsze piwo z piwnic naszej tawerny, i najpiękniejsze damy na wyspie, ha-ha-ha!\nA dla ciebie, Charles, od nas - wspaniały kapelusz. Spróbuj go, i nie dyskutuj!\nKorsarze, śpiewajcie naszą piosenkę! Naszą ulubioną!..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "Czas pokazać im, kim jesteśmy, korsarze. Leprechaunie! Zabierz swoich ludzi i przejmij kontrolę nad bramami miasta. Nie chcemy, żeby wysłali posiłki do fortu! Uderzcie ich mocno w plecy, gdy będziemy przemykać przez żołnierzy fortu!";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "Książę i Paul! Widzieliście tę eskadrę wojenną z trzema statkami, pozbądźcie się ich. Trzymajcie się z dala od fortu i nie wchodźcie na ich pokłady. Nie mamy czasu ani możliwości, by zajmować się zdobyczami. Wszystko jasne?! Książę, mówię zwłaszcza do ciebie, wiem o twoim uzależnieniu od bohaterstwa, będziesz miał na to okazję później!\nNie zbliżajcie się zbytnio do fortu, pozbądźcie się tych statków i wracajcie! Będziemy na was czekać tutaj. Wszystko jasne? Świetnie, ha-ha-ha-ha! Atak!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "Więc hiszpańska eskadra zniknęła na dobre. Teraz nadszedł czas, by 'Czerwony Smok' odegrał swoją rolę. Zmienimy fort Cartageny w kupę gruzu. Jesteś ze mną?";
			link.l1 = "Jasne!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = " 'Czerwony Smok' to bardzo solidny statek z potężną artylerią, twój nie ma z nią szans. Więc bądź ostrożny, nie baw się w bohatera i trzymaj się z dala od moich armat!";
			link.l1 = "... ";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"Piekielna walka! To jest to, moi dzielni korsarze! Kartagena jest nasza! Opór padł! Śmiało, Leprechaun! Chodź ze mną do fortu - Bernie musiał już znaleźć złoto. Książę, weź Cutlassa i negocjuj z gubernatorem, żeby zapłacił nam okup 250.000 pesos! Mają pieniądze, więc bądź wytrwały. Wiem, że potrafisz.";
			link.l1 = "Heh! Z przyjemnością, szefie!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "Jak się miewasz, książę?";
			link.l1 = "Wszystko jest wspaniałe. Zmusiłem najbogatszych z Cartageny do zapłacenia 350.000 pesos.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ho-ho, to mój chłopak! Ale gdzie są pieniądze?";
				link.l1 = RandSwear()+"Przyniosę to za chwilę!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ho-ho, to mój chłopak! Ty i Cutlass możecie zatrzymać po 50.000 jako premię za szybkość i zaradność. Reszta zostanie podzielona między nas wszystkich później.";
				link.l1 = "Proszę bardzo!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Więc? Przestań się wygłupiać i przynieś tu monety!";
				link.l1 = "Już idę!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Świetnie! Ty i Cutlass możecie zatrzymać po 50.000 jako premię za szybkość i zaradność. Reszta zostanie podzielona między nas wszystkich później.";
				link.l1 = "Oto masz!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "Pewnie martwisz się o nasze złoto? Znalezione - 5.000 jednostek i już jest transportowane na nasze statki. Podział już zrobiony, ludzie się z nim zgodzili, mamy nadzieję, że Cutlass i ty też nie będziecie mieli nic przeciwko.";
			link.l1 = "Jaki jest mój udział?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Odkąd cała operacja została zaplanowana przeze mnie, a 'Czerwony Smok' wykonał najtrudniejszą robotę z fortem, ja i moi ludzie otrzymamy połowę łupu. Druga połowa zostanie podzielona między kapitanów pozostałych czterech statków zgodnie z liczbą ich załóg. Masz "+GetCrewQuantity(pchar)+" ludzie do dyspozycji, twój udział to "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" sztuk złota i "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+"pesos.";
			link.l1 = "Cóż, skoro wszystkim to pasuje, to mi też!";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Znakomicie. Gratulacje za tę udaną podróż, korsarze! Nic tu po nas, czas wracać do domu. Wszyscy, w tym ja, dostajemy miesiąc urlopu. Nie ty, Książę, jednakże mam dla ciebie inne zadanie. Widzisz, Janette, Madame z burdelu na Tortudze, skarżyła się na ciebie: powiedziała, że Charlie Prince nie poświęca zbyt wiele uwagi i miłości jej przybytku. Dlatego nakazuję ci żeglować do Tortugi, iść do Janette i wydać tam swoje premie. Zasłużyłeś na to. Spraw, by Madame i jej dziewczęta były szczęśliwe. Nie chcę cię widzieć, zanim nie odpoczniesz na Tortudze, ha-ha-ha!";
			link.l1 = "Zrozumiałem, szefie. To najprzyjemniejsze zadanie, jakie kiedykolwiek otrzymałem. Zostanie wykonane!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Żegnajcie, panowie! Wsiadajcie na swoje statki i stawiajcie żagle! Do zobaczenia w La Vega!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "Co?! Jean to teraz dziwka Anglików, Śmiały i Szabla zniknęli, Leprechaun i jego ludzie zniknęli bez śladu! A teraz ty?!";
			link.l1 = "Marcus, podjąłem decyzję. Zarobiłem nieźle, ty też zgarnąłeś na mnie fortunę. Ale mam dość. Odchodzę.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "Ty, podobnie jak Picard, myślisz, że możesz mieć lepsze zarobki na własną rękę? Tak? Myślisz, że poradzisz sobie beze mnie? Ha-ha-ha! Wynoś się stąd, książę, nie trzymam cię. Wkrótce, bardzo wkrótce zobaczysz, jak bardzo się myliłeś, a wtedy wrócisz błagając mnie, bym przyjął z powrotem twoją żałosną dupę. I wiesz co? Nie zrobię tego! Ha-ha! Znikaj mi z oczu!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Trafiłeś we właściwe miejsce! Wyrzuć to z siebie!";
			link.l1 = "Jest taki facet, który nie boi się piratów. Nie traktuje ich poważnie. Trzeba go nauczyć szacunku. Pamiętaj, nie zabijaj go.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Ha! Toż to nikt inny jak stary Charles! Założę się, że znowu wpakowałeś się w jakieś tarapaty! Przejdźmy do szczegółów, kto tym razem jest celem i czego mamy go nauczyć?";
			link.l1 = "Gość z Europy, inspektor francuskiego Ministerstwa Finansów - baron Noel Forget. Chce założyć tu Francuską Kompanię Handlową, ale ja i mój bliski przyjaciel jesteśmy temu przeciwni. Próbowaliśmy przekonać barona, że handel tutaj byłby bardzo ryzykowny z powodu Holendrów, Anglików, a zwłaszcza piratów po pokonaniu Levasseura, ale nie posłuchał. Musimy wzbudzić w nim strach, sprawić, by poczuł to na własnej skórze.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Ho-ho! Trafiłeś we właściwe miejsce! Wypluwaj to!";
			link.l1 = "Jest pewien facet, który nie boi się piratów. Nie traktuje ich poważnie. Trzeba go nauczyć szacunku. Pamiętaj, nie zabijaj go.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Hę! Dlaczego nagle postanowiłeś ujarzmić piratów? Dobra, nie obchodzi mnie to, dopóki mi płacisz. Przejdźmy do szczegółów, kto jest teraz celem i czego mamy go nauczyć?";
			link.l1 = "Gość z Europy, inspektor francuskiego Ministerstwa Finansów - baron Noel Forget. Chce założyć tu Francuską Kompanię Handlową, ale ja i mój bliski przyjaciel się temu sprzeciwiamy. Próbowaliśmy przekonać barona, że handel tutaj byłby bardzo ryzykowny z powodu Holendrów, Anglików i szczególnie piratów po pokonaniu Levasseura, ale on nie słuchał. Musimy wzbudzić w nim strach, by poczuł to na własnej skórze.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Tak-tak... Prawdziwy baron! Czy powinniśmy zaatakować jego statek?";
			link.l1 = "Oto plan: jego statek wkrótce odpłynie do Capsterville z Port-au-Prince. Musisz przechwycić barona w pobliżu Saint Kitts i wziąć go jako zakładnika. Lepiej byłoby, gdybyś nie zatopił statku i unikał zabijania ludzi. W końcu Francuzi są naszymi przyjaciółmi. Czy dasz radę to zrobić?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Cóż, niczego nie mogę obiecać. Ale spróbuję. Jaki to statek?";
			link.l1 = "Brygantyna zwana 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Brygantyna nie dorówna mojemu 'Czerwonemu smokowi'. Łatwo sobie z nimi poradzimy. Jeśli się poddadzą, daruję im życie.";
			link.l1 = "Znakomicie. Wzbudź strach i zaoferuj im poddanie się. Następnie zaprowadź Barona do ładowni pełnej szczurów. Spróbuj znaleźć najbrudniejsze miejsce, jakie możesz, ale nie trzymaj go tam dłużej niż dzień, bo może się rozchorować i umrzeć. Potem umieść go w kajucie, znajdź i zamknij w jakimś odosobnionym miejscu. Ubierz kilku swoich ludzi jak schwytanych francuskich kupców i spraw, by się tak zachowywali. Przez trzy dni z rzędu, powinni opowiadać mu o tym, jak bezwzględni piraci ich ścigają, rabują, żądają okupów, torturują... z wszystkimi wymaganymi szczegółami.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! To musi być najzabawniejsza robota, jaką podjąłem od bardzo dawna! No cóż, znajdę takich aktorów, chłopcze. Nie wątp, po ich opowieściach twój baron się zesra w spodnie! Pokażą mu blizny od szabel i rozgrzanych wyciorów...";
			link.l1 = "Idealnie! Wtedy zmusisz go, by napisał list do de Poincy, prosząc o okup. Trzydzieści pięćset tysięcy za taką szychę to nie tak dużo.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Dobrze. Co zrobimy dalej?";
			link.l1 = "A wtedy przyprowadzisz Barona na Turks. Tam weźmiesz okup, a Barona oddasz mnie. I dodatkowo powinieneś mu powiedzieć, że wszyscy Francuzi odpowiedzą za Tortugę i Levasseura, i to nie raz.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! Toż to sztuczka nie z tej ziemi! Osobiście, cóż, wiesz co zrobiliśmy z Levasseurem, a teraz... ha-ha-ha!.. Dobrze, chłopcze. Zrobimy to! Mówisz, że statek wkrótce przypłynie?";
			link.l1 = "Wkrótce. Musimy być na czatach.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ha-ha-ha! Toż to piekielny sztuczka! Ile mam cię skasować za tę farsę? Dobrze, sto tysięcy zamknie sprawę. Daj mi pieniądze.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Weź to.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "Dobrze, przyniosę to.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Doskonale! Mówisz, że statek wkrótce przybędzie?";
			link.l1 = "Wkrótce. Musimy być czujni.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Nie martw się, nie zawiodę cię. Zajmę się tym osobiście. Gdy usłyszysz plotkę, że Baron został pojmany, przyjdź do mnie.";
			link.l1 = "Dobrze. Dziękuję, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Oczywiście, chłopcze. Jak się umawialiśmy. Straszne opowieści o złych piratach, mordujących niewinnych francuskich kupców, dźwięki bicza, jęki i krzyki. Piec z węglem i przypalone kajdany. Tak właśnie powinno być.";
			link.l1 = "Ej, ej! Nie tak prędko, chłopcze! Potrzebuję go żywego";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Nie martw się, on przeżyje. Napisał ten list drżącą ręką. Oto on.";
			link.l1 = "Co tam jest napisane? Błaga Poincy'ego, by go stąd wyciągnął?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Tak jest, chłopcze! On błaga, ha!";
			link.l1 = "Pozbądź się tego listu, albo lepiej - spal go. Spotkamy się na Turks za tydzień. Musi wyglądać, jakbyśmy potrzebowali czasu na zebranie okupu.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Rozumiem. Za tydzień, północna zatoka na Turkach. Nie zapomnij wziąć pieniędzy: to musi wyglądać ładnie. Po tym wszystkim, przyjdź do mnie, omówimy to.";
			link.l1 = "Oczywiście, do zobaczenia później, Marcus!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hej, żabojadzie! Stój!";
			link.l1 = "Nie ruszam się.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Tu jest twój Baron. Trochę zniszczony, heh, ale w jednym kawałku. Wciąż rozpoznawalny? Ha-ha-ha!";
			link.l1 = "Tak... poniekąd.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Doskonale. Teraz oddaj pieniądze, albo z nim koniec! I nie próbuj nas oszukać, mamy cię na muszce!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Oto, weź to.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Cholera! Zostawiłem to na statku...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Jesteś sprytnym dzieciakiem, francuziku. Weź swoją 'eminencję'. I powiedz Poincy, że powinien przygotować pieniądze: będziecie musieli zapłacić za to, co zrobiliście Levasseur i Tortudze. A wasi handlarze zapłacą nam swoimi towarami i statkami. Ha-ha-ha! Nie zapomnij przywieźć nam więcej baronów na archipelag, przynoszą nam sporo zysków! Ha-ha-ha!";
			link.l1 = "Proszę, idź na mój statek, Baronie.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "I nawet nie myśl o ściganiu nas, kapitanie. Wiesz, kim jestem. Trzymam więcej żabojadów w niewoli, a jeśli nie wrócę do domu na czas, wszyscy zostaną straceni. Zrozumiano?";
			link.l1 = "Przyjdzie czas, kiedy się z wami rozprawimy, przeklęci bluźniercy!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha! Pewnie, że tak!";
			link.l1 = "... ";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Żartujesz sobie ze mnie?! To jakiś rodzaj sztuczki?!";
			link.l1 = "Chwila, zaraz to przyniosę...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "Understood, please provide the text for translation.";
			link.l1 = "Argh, Marcus, co zrobił twój gamoń!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, co ty robiłeś? Gdzie są pieniądze? Nie powiedziałem moim chłopakom, że to nie było prawdziwe... i więc ten idiota zdecydował, że chcesz nas oszukać...";
			link.l1 = "To katastrofa! Baron nie żyje... Co teraz zrobi de Poincy?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, co robiłeś? Gdzie są pieniądze? Nie powiedziałem moim chłopakom, że to nie było prawdziwe... i ten idiota zdecydował, że chciałeś ich oszukać...";
			link.l1 = "To katastrofa! Baron nie żyje... Co teraz zrobi de Poincy?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "No cóż, chłopcze, to twoja wina, mam nadzieję, że to rozumiesz. Może to i lepiej, martwy człowiek nie może wyrządzić żadnej szkody.";
			link.l1 = "Co za idiota ze mnie! Wszystko zepsułem. Dobrze, pójdę do Poincy... Wybacz mi moją głupotę, Marcus, do zobaczenia.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Cóż, chłopcze, to twoja wina, mam nadzieję, że to rozumiesz. Może tak będzie najlepiej.";
			link.l1 = "Co za idiota ze mnie! Wszystko schrzaniłem. Dobrze, pójdę do Poincy... Wybacz mi moją głupotę, Marcus, do zobaczenia.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Musisz odpocząć, tracisz formę. Odwiedzaj mnie czasem, załatwię ci trochę rumu i piękne dziewki.";
			link.l1 = "Dziękuję, odwiedzę cię, kiedy będę mógł.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Nie ma za co, chłopcze. To była dla mnie najlepsza zabawa w tym roku! Tak się uśmialiśmy, ja i moi chłopcy! Więc chciałem ci za to podziękować. Oto twoje pieniądze.";
			link.l1 = "Powinieneś zatrzymać część za swoje występy.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Weź swoje pieniądze, 'intrygancie'. Ha-ha! To było zabawne.";
			link.l1 = "Dziękuję za pomoc, Marcus. Powodzenia!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Zapomnij o tym. Zrobiłem to ze względu na naszą przyjaźń. Bracia Wybrzeża są ci winni znacznie więcej, a jednak nie zażądałeś ani jednego dubloona.";
			link.l1 = "Jednak weź przynajmniej pięćdziesiąt tysięcy za usługi i rekompensatę. Dziękuję, Marcus!";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Nie ma za co. Charles, wpadnij do mnie, gdy tylko będziesz miał trochę czasu!";
			link.l1 = "Z przyjemnością!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Spóźniłeś się o tydzień! Nie powiedziałem moim chłopakom, że to nie było prawdziwe... Odmówili dłużej czekać i postanowili zakończyć twojego Barona!";
			link.l1 = "Co za idiota ze mnie! Wszystko schrzaniłem! Co powiem Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "Spóźniłeś się o tydzień! Nie powiedziałem moim chłopakom, że to nie było prawdziwe... Odmówili czekać dłużej i postanowili zakończyć twojego Barona!";
			link.l1 = "Co za idiota ze mnie! Wszystko schrzaniłem! Co ja powiem Poincy?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "No cóż, chłopcze, to twoja wina, mam nadzieję, że to rozumiesz. Może tak będzie dla ciebie lepiej.";
			link.l1 = "Dobrze, pójdę do Poincy... Wybacz mi, że byłem głupcem, Marcusie, do zobaczenia...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "Sam wpakowałeś się w to bagno, to twoja wina.";
			link.l1 = "Do zobaczenia później, chyba...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "Musisz odpocząć, tracisz formę. Przyjdź do mnie czasem, załatwię ci rum i piękne dziewczęta.";
			link.l1 = "Dziękuję, odwiedzę cię, gdy będę mógł.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "Minęło trochę czasu, książę.";
				link.l1 = "Nie jestem pewien, czy to imię przyniosło mi coś poza pechem, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "De Maure! Co cię tu sprowadza?";
				link.l1 = "Ahoy, Marcus. Chciałem cię o coś zapytać.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "Widzę, że jest odwrotnie. Co cię tu sprowadza?";
			link.l1 = "Słyszałeś o nowym burdelu na Tortudze?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "W takim razie, pytaj. Wiesz, że nie lubię formalności, więc przejdź do rzeczy.";
			link.l1 = "Słyszałeś o nowym burdelu w Tortudze?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ2":
			dialog.text = "Jesteś pijany? Co to za pytanie? Nie marnuj mojego czasu, jeśli naprawdę o tym chciałeś pogadać.";
			link.l1 = "Chyba nie słyszałeś? Niedawno otwarto tam nowy burdel - bardzo drogi, gdzie pracują tylko najpiękniejsze, zdrowe i dobrze ubrane dziewczęta.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "O, to! Oczywiście, że słyszałem - kto nie słyszał?";
			link.l1 = "Cóż, dopiero co się o tym dowiedziałem.";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "Ha-ha-ha-ha, ty łajdaku, niech mnie kule biją! Ale wciąż, dlaczego o tym ze mną dyskutujesz? Czemu nie spróbujesz najpierw z Hawkiem? He he. Chociaż... już się tam trochę zabawiłeś?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "Mam. Tak przy okazji, przyjmują tylko doubloony.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "Odwiedziłem to miejsce, ale nie skorzystałem z usług. Jednakże...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "Więc przyszedłeś się popisać! Ha, co za łobuz.";
			link.l1 = "Właściwie, nie. Naprawdę chciałem cię o coś zapytać, Marcus.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "Nie zrobiłeś tego?! Jesteś idiotą, De Maure. Gdybym był na twoim miejscu...";
			link.l1 = "Wiem, że zaczęłabyś prawdziwą rozróbę. Ale to nie do końca to, o czym chciałem z tobą porozmawiać.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			dialog.text = "Co jest? No dalej, nie trzymaj mnie w niepewności.";
			link.l1 = "Szukam właścicielki tego miejsca. Powiedziano mi, że chciała się z tobą spotkać i zaproponować możliwość inwestycji w jej handel. Nie sposób jej pomylić - jest Chinką.";
			link.l1.go = "PZ6";
		break;
		
		case "PZ6":
			dialog.text = "Ho ho. Nie, nie miałem ostatnio przyjemności spotkać żadnych chińskich kobiet. Ale nie miałbym nic przeciwko spotkaniu z nią i zainwestowaniu w jej interes. W końcu nie można tak po prostu wkroczyć na terytorium Levasseura, a jako poddany twojego króla, byłby zmuszony otworzyć ogień na moją 'Smok' swoimi przybrzeżnymi okrętami, gdy tylko ją zauważy.";
			link.l1 = "Wydaje się, że najpierw rozważa Port-au-Prince...";
			link.l1.go = "PZ7";
		break;
		
		case "PZ7":
			dialog.text = "Tak myślisz? To błąd. Nawet jeśli de Mussac ma więcej pieniędzy niż ja, w co wątpię, nie stać go na to, by przeznaczyć jakąkolwiek część budżetu miasta na burdel, nieważne ile złota przynosi.";
			link.l1 = "Dobry punkt. Wyraźnie nie przemyślała dokładnie tego swojego ambitnego planu.";
			link.l1.go = "PZ8";
		break;
		
		case "PZ8":
			dialog.text = "Wiesz, zawsze się zastanawiałem, jak inne burdele utrzymują się na powierzchni. To nie jest zdolność kobiety do myślenia, a tym bardziej do rządzenia - zapamiętaj moje słowa.";
			link.l1 = "„Cóż, mylisz się co do tego. Dzięki za twój czas, Marcus! Jeśli spotkam ją pierwszą, dam jej znać, że będziesz się cieszył, widząc ją.”";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}