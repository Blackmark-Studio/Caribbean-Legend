void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "Jeśli czytasz tę linię, to błąd w kodzie";
			Link.l1 = "Wyjście";
			Link.l1.go = "exit";
			
			//--> Вступительный туториал на палубе корабля за Шарля
		if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
		{
			dialog.text = "Ekscytujące, do diabła! Prawdziwa bitwa morska!\nSzkoda oczywiście, że samej walki stąd nie zobaczę... No cóż. Myślę, że już wystarczająco poznałem się na marynarce, by wiarygodnie wyobrazić sobie przebieg wydarzeń\nPewnie pięciu piratów... Jeden duży okręt, kilka średnich i drobnica. W sam raz na naszego pinasa. Historia będzie przednia — Lulu będzie zachwycona!";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
			pchar.wind.speed = 18.0;
			fWeatherSpeed = stf(18.0);
			//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
		}
		//<-- Вступительный туториал на палубе корабля за Шарля

			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "Cóż, znaleźliśmy to miejsce na mapie. Powinienem to zaznaczyć, a potem możemy ruszyć na poszukiwania.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "Dobrze, jesteśmy tutaj. Powinienem schować mój statek w południowej zatoce, a potem wrócić pieszo przez dżunglę i zorganizować niemiłą niespodziankę dla Fleetwooda.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "Hm... Zaufanie temu łotrzykowi jest niebezpieczne, choć jego historia wydaje się prawdziwa. Być może tym razem nie kłamie. Ale tak czy inaczej, powinienem porozmawiać z jego żoną... Bosmanie! Przyprowadź mi tę więźniarkę!";
    			link.l1 = "Aye Aye, kapitanie!";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- Ложный след
			
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "To wydaje się być miejsce. To jedno z niewielu drzew bez soku w okolicy. Powinienem tu kopać.";
    			link.l1 = "(wykopać skarb)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- Португалец
			// Сага
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "Co się dzieje? Gdzie ja jestem?! Co to za miejsce?";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> приколы со стуком в дверь Диффиндура, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "To jest drzwi prowadzące do wewnętrznych pomieszczeń statku. Są zamknięte... Hawk musi być tu. Co znowu wspominał Ole? Powinienem użyć sekretnego pukania.";
    			link.l1 = "Puknij dwa razy.";
    			link.l1.go = "knock_2";
				link.l2 = "Pukaj trzy razy.";
    			link.l2.go = "knock_3";
				link.l3 = "Puknij raz, przerwa, puknij trzy razy.";
    			link.l3.go = "knock_1_3";
				link.l4 = "Pukaj dwa razy, zrób przerwę, pukaj dwa razy.";
    			link.l4.go = "knock_2_2";
				link.l5 = "Pukaj trzy razy, zrób przerwę, pukaj raz.";
    			link.l5.go = "knock_3_1";
    		}
			//<-- приколы со стуком в дверь Диффиндура, LSC
			
			//--> напялили водолазный скафандр, для перехода в режим шага
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "O rety! To naprawdę ciężkie!";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- водолазный скафандр
			// отказ от телепортации
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "Nie-nie-nie! Nie ma mowy! Trzy razy to już było więcej niż wystarczająco!";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "To jest zrobione. Levasseur nie żyje. Okazało się to być o wiele łatwiejsze, niż przypuszczałem... Ale coś nie pasuje. Thibaut nawet nie rozmawiał z Martene! To oznacza, że albo Robert mnie zdradził, albo zdarzył się jakiś wypadek. Ale gdzie mógł uciec ten drań Thibaut? Musi polować na Catherine. Muszę działać szybko, jeśli chcę zabrać dziewczynę spod jego nosa...";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "Skrzynie pełne skarbów, starożytnego miasta Indian... nie wierzę w takie zbiegi okoliczności... założę się, że mój brat miał coś wspólnego ze zniknięciem fregaty Dichoso. Pewnie upewnił się, że Dichoso nigdy nie otworzy znów swoich ust\nAlbo może pracował z nim, Hiszpanie musieli mieć powody, aby sądzić, że Dichoso jest gdzieś tutaj. To nie ma sensu. Ale jestem pewien, że złoto Indian, które Michel dostarczał de Poincy, jak i złoto Miguela Dichoso to to samo złoto. Historia więźnia zgadza się z tym, co oficer powiedział mi o przygodach mojego brata\nŚmieszne, Michel nie dostarczył złota, podobnie jak Miguel! Więc gdzie teraz są te skarby? Może to była przyczyna, dla której mój brat tak się spieszył\nErgo, znalezienie złota będzie jak zabicie dwóch much jednym uderzeniem: spojrzę znowu w bezczelne oczy mojego brata i... tak, złoto zawsze jest dobre. Ale jak do diabła je znajdę? Wygląda na to, że czas nawiązać bliższe stosunki z Hiszpanami\nDon Ramon Mendoza nie wchodzi w grę, wątpię, że dam sobie z nim radę, ale święty ojciec Vincento, najgorszy wróg barona... on się nada. Jego rodzaj nie jest skrupulatny, ale kocha pieniądze i podstępne środki\nDichoso, Dichoso... słyszałem to nazwisko wcześniej... czy nie? Cokolwiek, do diabła z tym. Powinienem iść do oficera i zgłosić się po hiszpańskiego więźnia. Potem mogę udać się do Santiago w dowolnym momencie.";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "Wanilia została załadowana na karawelę, a jej żagle dawno zniknęły za horyzontem - a to przeklęte galeony wróciły do portu zamiast wypłynąć na otwarte morze. Nie mogę pokazać się ze swoim statkiem w porcie - lepiej, jeśli myślą, że opuściłem Gwadelupę... Chyba przejdę do miasta przez dżunglę i dowiem się coś o moim drogim Marchais...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "Na górnym pokładzie jest tylko kilku strażników, wszyscy dość senni. Myślę, że mogę ich wszystkich wyeliminować jeden po drugim, jeśli podejdę cicho od tyłu i uderzę ich w tył głowy kastetem...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "Nie zamknięty pusty dom z przytulnym pokojem na drugim piętrze, a w pobliżu mieszkań Calhouna... To jest po prostu odpowiedź na dziewiczą modlitwę... Jeśli wyjdę przez okno i przejdę po abat-jour dachu, z łatwością dostanę się do pokoju Archiego. Ale musi to być zrobione w nocy, abym nie został złapany...";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// Поиски Ксочитэма
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "W końcu! Znalazłem miejsce wskazane przez 'manifestację': to indyjski idol. Kiedy jestem blisko, 'Strzała Drogi' przestaje oscylować i wskazuje w jednym kierunku. Cóż, wydaje się logiczne - indyjska magia i indyjski idol. Teraz powinienem zaznaczyć na mapie miejsce wskazane przez 'Strzałę Drogi', a potem udam się na Dominikę.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "W końcu! Znalazłem miejsce wskazane przez 'manifestację': to jest idol Indianina. Kiedy jestem blisko, 'Strzała Drogi' przestaje oscylować i wskazuje jeden kierunek. Cóż, wydaje się to logiczne - magia indiańska i idol indiański. Teraz powinienem zaznaczyć miejsce wskazane przez 'Strzałę Drogi' na mapie, a potem pójdę do Main.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "Oba przejawy zostały znalezione! Teraz muszę zaznaczyć drugi kierunek na mapie. Przecięcie tych dwóch kierunków pokaże mi lokalizację wyspy Ksocheatem.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// рассуждения по Тайясалю
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "Alonso de Maldonado powiedział, że jest ścieżka do Tayasal, która zaczyna się na północy od Jukatanu. Oznacza to, że powinienem zagłębić się w dżunglę tego obszaru. Ale Gino powiedział, że pierwotnie statuy teleportacyjne miały przenosić ludzi do Tayasal\nA szaman Miskito, Wężowe Oko, powiedział mi, że idole miały służyć do wysyłania 'pożartych' do tego miejsca. Ale dlaczego zatem te portale są zepsute? Hm. Poza tym, mapa Dwóch Manifestacji pokazuje dziwne koło blisko statuy Miskito\nCo to do diabła oznacza? Kolejne magiczne miejsce? Czy pokazuje, że statua ma tam dodatkowe funkcje? Myślę, że powinienem odwiedzić szamana. Albo mogę iść na północny zachód od Main i szukać tam ścieżki, w jednej z lokalnych zatok.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Alonso de Maldonado powiedział, że jest inna droga do Tayasal z północnej części półwyspu Jukatan. To oznacza, że muszę szukać ścieżki w głąb selva. Prawdopodobnie ścieżka, której potrzebuję, zaczyna się w jednej z zatoczek na północnym zachodzie Main.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// решаем - титры или фриплей 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "To jest zrobione. Koniec mojej długiej podróży. Nie mogłem sobie wyobrazić, że ratowanie mojego brata z więzienia oznaczało przygotowanie się do ostatecznej walki przeciwko niemu! Że prawie skazałem nasz świat. Dzięki Bogu, to już koniec\nNie ma mnie już na Karaibach. Czas wrócić do domu, do Francji. Ale... czy na pewno tego chcę?";
				link.l1 = "Tak, wracam do Europy.";
				link.l1.go = "final_1";
				link.l2 = "Nie, zostaję tutaj na Karaibach.";
				link.l2.go = "final_2";
    		}
			// фэйловый финал 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "Słyszałeś pułkownika? Buntownicy ukrywają się tam! Przeszukaj wszystko, przewróć dom do góry nogami i zaaresztuj każdego, kogo tam znajdziesz! Do dzieła!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "To najlepsze miejsce na zasadzkę. Powinienem tu poczekać na przybycie Pinette.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "Hm. Ta historia nie brzmi dobrze. Sądzę, że ta łódka ze św. Jonesa nigdy nie miała istnieć. Porucznik wciąga mnie w swoją wojskową operację. Po co mi to? Nie jestem na wojnie z Holendrami... Co powinienem zrobić? Czy powinienem odejść i pozwolić Brytyjczykom bawić się samym? Czy powinienem zostać?";
				link.l1 = "Odejdź.";
				link.l1.go = "FMQN_1";
				link.l2 = "Zostań.";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "No więc, skrzynia jest przygotowana. Mogłem próbować znaleźć wszystkie potrzebne materiały sam, ale wolałbym pójść i zobaczyć się z Fadeyem. Wydaje mi się, że to człowiek, który może zdobyć cokolwiek.";
    			link.l1 = "*UŻYJ OPCJI GŁOŚNEGO MYŚLENIA, ABY ZAKOŃCZYĆ ZBIERANIE AMUNICJI*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "Cóż, musimy zbudować sześć długich łodzi. Do tego potrzebuję cieślę, 20 desek i 10 pakietów skóry";
    			link.l1 = "*WYBIERZ OPCJĘ GŁOŚNEGO MYŚLENIA, ABY ZACZĄĆ BUDOWĘ DŁUGICH ŁODZI*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "Więc, zamierzam po prostu wysadzić tę stertę starych drzew w powietrze. Wszystko, czego potrzebuję do tego, to 300 jednostek prochu strzelniczego, żeby być pewnym.";
    			link.l1 = "*użyj opcji Głośne Myślenie, aby zamówić umieszczenie prochu strzelniczego*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" Wyjście jest zablokowane! Wygląda na to, że zablokowali drzwi czymś ciężkim! "+RandSwear()+"\nCicho... Co do diabła?";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "To jest to... Koniec drogi\n Wygląda na to, że don Enrico był poważny: nie ma wyjścia z tych lochów. Miałem chwilę nadziei, gdy znalazłem drugie drzwi na poziomie wody, ale teraz... Straciłem rachubę czasu - jak długo czaiłem się w tych ciemnych tunelach? Pół dnia, cały dzień? To miejsce jest tak ciche i straszne jak trumna\nKiedyś mieli tu kościół, dokładnie tu. Co za idealne miejsce na modlitwę. Zgrzeszyłem dużo, za dużo... Będę się modlił i spał tutaj, moje rany i zmęczenie mnie zabijają. Jeśli mam szczęście, nigdy nie wstanę...";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "Ja, Charles de Maure, francuski kapitan i szlachcic, przysięgam sobie i swoim sumieniem, że na dobre skończyłem z moją piracką przeszłością!";
    			link.l1.go = "Good_Choice";
				link.l2 = "Tak! Tak! Ah ha ha!! Udało mi się, przeżyłem! Jedz to, Zorro! Idź do diabła, Marcus! Teraz jestem sam! Charlie Prince mógł umrzeć, ale Charlesa de Maure nikt nigdy nie zabije!";
    			link.l2.go = "Bad_Choice";
			}
			// <-- legendary edition
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "Co powinniśmy zrobić?";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "... oczywiście, Levasseur to nie głupiec. W przeciwnym razie dlaczego musieliby nas aresztować właśnie w tym momencie?\nI nie powiedzieli ani słowa!\n"+dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "Helen, dlaczego jesteś taka cicha?";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "Mary, dlaczego wyglądasz tak szczęśliwie?!";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "Tichingitu? Powiedz coś odpowiedniego do sytuacji.";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "Hercule, czy mnie słyszysz? Co zamierzamy robić?";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "Nic nie da się zrobić. Chyba będę chwilę nosić buty Michela.";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "O mój Boże, zabili Hercule!";
				link.l1.go = "exit";
				link.l2 = "Wy łajdaki!";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "Co za wieczór! Dlaczego słuchałem jej? Brat miał rację - dziewczyny tutaj są zupełnie inne. Może dodają coś do rumu?";
				link.l1 = "Czas iść spać, a potem - do Cartageny!";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "Ani jednej rzeczy nie skradziono, choć wszystko jest rozrzucone dookoła. Nawet cenne przedmioty pozostały nietknięte. ";
				link.l1 = "Oni nie próbowali mnie okraść - szukali czegoś konkretnego. Ale czego? I co ważniejsze, kogo...?";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuest("PZ_OsmatrivaemSunduk_3");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "Zaczekajmy do zmierzchu i zaatakujmy!";
				link.l1 = "W międzyczasie zaczniemy przygotowywać długie łodzie.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "O mój Boże... Nie, nie, nie...";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "O Boże, o Boże, o Boże... Dlaczego? O Boże, dlaczego... ale zrobiłem wszystko, co mogłem...";
				link.l1 = "To wszystko moja wina, tylko moja. Nie dotarłem tutaj na czas. Jest mi tak przykro... Proszę, proszę wybacz mi.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("To była jedna diablińska walka... Teraz możemy nazwać tych tchórzów, którzy uciekli...","Ha! To było łatwe. A ci lądowi szczury po prostu się rozbiegli!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Hmm... Więc co powinienem teraz zrobić?","Co robić teraz?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "Wezwanie towarzysza.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Odpocznij do rana.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Odpoczywaj do nocy.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Odpocznij do następnego poranka.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Zwerbuj niewolników do załogi.";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "Zacznij zdobywać najbliższe miasto.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "Powinienem odpocząć...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "Chcę zmienić amunicję do broni palnej.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "Chcę zmienić amunicję do muszkietu.";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "Chcę wybrać priorytetową broń do walki.";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "Chcę wybrać eliksir do stałego użytku.";
			Link.l19.go = "ChoosePotion";
			
			//--> Голландский гамбит
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "Spróbuj znaleźć wyspę na podstawie współrzędnych na mapie.";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Wezwij Adama Raynera.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Aresztuj Adama Raynera.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//<-- Ложный след
			// Addon 2016-1 Jason Пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
	        {
	        	Link.l17 = "Podlicz zawartość skrzyni i zdecyduj, że skończysz zbierać amunicję dla Picarda.";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "Wydać rozkaz ataku na plantację w Maracaibo.";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "Wydać rozkaz zbudowania długich łodzi.";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "Polecenie dostarczenia prochu do martwego szańca.";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason Долго и счастливо
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "Pomyśl o ślubie.";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "Złóż propozycję małżeństwa.";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "Przygotujcie świętowanie.";
	    		Link.l18.go = "LH_marry_4";
	    	}
			// -->Авторемонт			
			if(Pchar.Location == Pchar.location.from_sea && CheckOfficersPerk(pchar, "SelfRepair") && CheckSelfRepairConditions()) 
			{
				Link.l14 = "Zacznij naprawiać statki";
				Link.l14.go = "StartSelfRepair";
			}			
			// <--Авторемонт
			//--> завершение игры
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "Zakończ sprawy na Karaibach i popłynąć do Europy.";
	    		Link.l15.go = "final_1";
	    	}
			//<-- завершение игры
			Link.l20 = RandPhraseSimple("Nie teraz. Nie ma czasu.","Nie ma na to czasu, za dużo do zrobienia.");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		
		case "StartSelfRepair":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchRepair(pchar);
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wybierz typ amunicji:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;
		
		case "SetGunBullets2":
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Wybierz rodzaj amunicji:";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Na początku walki użyję:";
			Link.l1 = "Szabla";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muszkiet";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "Wybierz miksturę:";
	    	Link.l1 = "Eliksir uzdrawiający.";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "Eliksir.";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "Mieszanina.";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "Korzeń imbiru.";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "Rum.";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "Wino.";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "Chcę wybierać eliksiry automatycznie.";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "Czekaj, zmieniłem zdanie..";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("A healing essence will be used by default.");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("An elixir will be used by default.");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("A mixture will be used by default.");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("A ginger root will be used by default.");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("Rum will be used by default.");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("Wine will be used by default.");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("Potions will be selected automatically.");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "Moglibyśmy zacząć zdobywać miasto, ale statek nie wytrzymałby długo salw z dział fortu, a my nie będziemy mogli wysłać desantu.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "Nie, jeszcze nie jestem tak szalony..";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "Nie ma sensu atakować tej kopalni bez wcześniejszego zebrania informacji o wydobywanym tam złocie i srebrze. W przeciwnym razie wyślę moich ludzi na daremną śmierć.";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "Atak "+GetCityName(chr.City)+".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "Przestań się bawić! Stop!";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "Przestań się bawić! Stop!";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "Do broni!";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Stop!";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Heh! There aren't enough people in the crew; we need at least "+needCrew+" men.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Nie rozpraszajcie się! Kontynuujcie atak!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "Żaden z niewolników nie chce dołączyć do załogi.";
	            Link.l1 = "Do diabła z nimi!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "Na statku nie ma wolnego miejsca dla nowych marynarzy.";
	                Link.l1 = "Heh! Będę musiał przenieść część załogi na inny statek.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "Twój załoga może zostać uzupełniona "+pchar.GenQuest.SlavesToCrew+" niewolnicy, którzy chcą służyć pod twoim dowództwem. Czy chciałbyś zaakceptować?";
	                Link.l1 = "Tak";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "Nie";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			bOk = ShipBonus2Artefact(pchar, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(pchar.Ship.Type)], "DeadSailors.RecruitSlaveBonus");
			if(!bOk)
			{
				// belamour legendary edition перк получил время работы, старый метод не подходит
				if (GetOfficersPerkUsing(pchar, "IronWill"))
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
				}
				else
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
				}
			}
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Ten słodki statek jest teraz mój, a ja jestem tu kapitanem! Szkoda, że musiałem zabić całą załogę.";
			Link.l1 = "Czas wylądować na brzeg...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Którego towarzysza przywołać?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "Inny raz.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> Голландский гамбит
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "Szkoda, że nie mam niezbędnych instrumentów nawigacyjnych do określania szerokości i długości geograficznej. Będę musiał poszukać wyspy innym razem.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- Голландский гамбит
		
		//--> Ложный след
		case "FalseTrace_Cabin":
			dialog.text = "Bosmanie! Przyprowadź mi natychmiast Adama Raynera!";
			link.l1 = "Tak jest, kapitanie!";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- Ложный след
		
		//--> LSC, приколы со стуком в дверь
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "No więc, zapukałem, teraz poczekajmy na odpowiedź...";
			link.l1 = "(czekaj)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "No więc, zapukałem, teraz poczekajmy na odpowiedź...";
			link.l1 = "(czekaj)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "No więc, zapukałem, teraz poczekajmy na odpowiedź...";
			link.l1 = "(czekaj)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "No więc, zapukałem, teraz poczekajmy na odpowiedź...";
			link.l1 = "(czekaj)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "No więc, zapukałem, teraz poczekajmy na odpowiedź...";
			link.l1 = "(czekaj)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "On nie otwiera drzwi... Chyba użyłem złego tajnego pukania. Dobrze, przyjdę jutro i spróbuję ponownie. Dzisiaj na pewno nie otworzy drzwi.";
			link.l1 = "(wyjdź)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "O rany! On odpowiedział i otworzył drzwi! Teraz mogę wejść...";
			link.l1 = "(wejdź)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, приколы со стуком в дверь
		
		// суп из черепахи
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "Caramba! Więc to jest opóźnione wsparcie dla Levasseura... Nie ma mowy, abym mógł wyjść przez drzwi... Dobrze, pójdę śladem Thibauta - przez okno! W końcu ten łobuz jakoś zdołał wymknąć się!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// защита Сен-Пьера
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "Więc, naszą misją jest odparcie ataku przeklętych Hiszpanów i uratowanie Saint Pierre. Fort został zdobyty, a walka toczy się na ulicach. W zatoce Saint Pierre znajduje się potężna eskadra, a ich flagowym okrętem jest okręt liniowy. Atakowanie go teraz nie ma sensu, fort i miasto są pod kontrolą wroga, więc nie pozwolą nam wylądować w porcie\nDlatego zdecydowałem się przejść przez dżunglę i uderzyć na nich od tyłu przez bramy miasta. Gdy fort i miasto zostaną oczyszczone z Hiszpanów, zajmiemy się eskadrą. Bez wsparcia ognia fortu stanie się o wiele bardziej podatna\nTo nie będzie łatwe, więc wydałem rozkaz wypłacenia dodatkowego stu tysięcy pesos do podziału między załogą, oprócz normalnej pensji. Ruszajmy!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// финал игры
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
			{
				dialog.text = "Zaczekaj, dokąd idę? Nie mogę opuścić stanowiska Gubernatora-Generalnego bez pozwolenia z Paryża! W przeciwnym razie na pewno zostanę aresztowany za nieautoryzowane opuszczenie powierzonych kolonii, gdy wrócę do Francji. Paryżu, będę za tobą tęsknił ...";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "Więc nie marnujmy więcej czasu! Tęsknię za polami mojej drogiej Gaskonii! Podnosimy żagle!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "Wierzę, że to jest słuszna decyzja! Co zostało w dobrej, starej Europie czekające na mnie, kiedy znalazłem się tutaj? Poza tym, mogę wrócić do Francji kiedy tylko zechcę!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN_1":
			dialog.text = "To najlepsza droga. Powinienem wejść na pokład i odpłynąć stąd.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "Nie, nie ma mowy, zostaję. Ale do diabła, nie będę tu stał czekając na Boga wie co. Powinienem popłynąć do portu w Philipsburgu i zbadać sytuację. Nie podoba mi się pomysł bycia narzędziem w rękach jakiegoś przeklętego, kłamliwego Anglika.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // анализируем содержимое сундука
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
			{
				dialog.text = "Trzydzieści sztuk zimnej stali jest w skrzyni! Czy powinienem teraz przestać, czy powinienem zbierać więcej broni palnej, ładunków i mikstur?";
				link.l1 = "To wystarczy!";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "Nie, powinienem dalej napełniać tę skrzynię.";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "Wypełnij zawartością skrzyni Fadey'a i weź nadmiar."; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "Trzydzieści sztuk zimnej stali jeszcze nie jest zebranych! Powinienem przynieść więcej.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Zamykanie skrzyni i robienie planu, jak ją przemycić na plantację.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "Idź, naaaapadnij! Hurra!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
			{
				if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
				{
					dialog.text = "Wszystkie potrzebne materiały są przygotowane, powinniśmy natychmiast zacząć budować długie łodzie.";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "Nie mam doświadczonego stolarza, który mógłby wykonać tę pracę. Powinienem przydzielić oficera na to stanowisko.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Za mało materiałów, potrzebujemy przynajmniej 20 paczek desek plus 10 bel skóry.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
			{
				if (GetCrewQuantity(pchar) >= 20) // наличие команды
				{
					dialog.text = "Wszystko gotowe do wybuchu!";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "Potrzebuję co najmniej 20 ludzi do dostarczenia prochu strzelniczego.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Za mało prochu, potrzeba co najmniej 300.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "Czy to były drzwi?";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "Dobrze! Mamy gości... Jan?..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour legendary edition -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// <-- legendary edition
		
		// Jason Долго и счастливо
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "Ja i "+sTemp+"Jesteśmy razem już od dawna, a nasze więzi są silniejsze niż jakiekolwiek kościelne przysięgi, ale chcę, abyśmy obaj zapamiętali ten moment. Dlatego muszę zdecydować, gdzie mam jej oświadczyć się:";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Isla Tessoro - ta wyspa ma duże znaczenie w naszej historii. Myślę, że nie ma lepszego miejsca - Zatoka Sabu Matila jest urocza o zachodzie słońca!";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = "Tortuga - symbol wolności naszych czasów, a widok z latarni morskiej na cieśninę Tortu zasługuje na pędzel każdego malarza!";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "Jamajka - to takie zróżnicowane miejsce! A podziwianie świtu w Portland Cove to moje wyobrażenie raju na ziemi.";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ale nie możemy tego zrobić bez powagi kościoła - wszystko powinno być zgodne ze wszystkimi kanonami, aby mój ojciec był zmuszony zaakceptować mój wybór. Więc, będę potrzebować księdza, a nie widzę nikogo godnego tej pozycji oprócz opata Benoita. Jest starym przyjacielem mojego ojca i z nim zaczęły się moje przygody w Nowym Świecie. Myślę, że zgodzi się zrobić mi tę cześć.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ale nie możemy tego zrobić bez powagi kościoła - wszystko powinno być zgodne z kanonami, aby mój ojciec był zmuszony zaakceptować mój wybór. Więc, będę potrzebował księdza, i nie widzę nikogo godnego tej pozycji poza Opatem Benoit. Jest on starym przyjacielem mojego ojca i to od niego zaczęły się moje przygody w Nowym Świecie. Myślę, że zgodzi się mi zrobić tę przysługę.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ale nie możemy tego zrobić bez powagi kościoła - wszystko powinno być zgodnie z wszelkimi kanonami, aby mój ojciec był zmuszony zaakceptować mój wybór. Więc, będę potrzebować księdza, a nie widzę nikogo godnego tej pozycji poza opatem Benoit. Jest starym przyjacielem mojego ojca i od niego zaczęły się moje przygody w Nowym Świecie. Myślę, że zgodzi się mi zrobić ten honor.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Cóż, to może się zdarzyć bez uroczystości ludzkości. Chociaż wolałbym omówić to z "+sTemp+" trochę później.";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "Cóż, jestem gotowy!";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "Wszystko jest przygotowane!";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "Niezbędne towary i monety nie zostały jeszcze zebrane!";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void DialogExit_Self()
{
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
    DialogExit();
	locCameraSleep(false); //boal
}
