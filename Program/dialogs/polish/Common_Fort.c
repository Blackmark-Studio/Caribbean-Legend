// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Szpieg! Złóż broń i idź za mną!","Wrogi agent! Łapać "+GetSexPhrase("go","ją")+"!");
				link.l1 = RandPhraseSimple("Chyba cię coś boli!","Spadaj!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Kim jesteś i co tu robisz?","Stój nieruchomo! Kim jesteś? Z jakiego powodu próbujesz wejść do twierdzy?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Oficerze, mam "+GetRusNameNationLicence(sti(npchar.nation))+", więc jestem tutaj na legalnych podstawach. Proszę, spójrz...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Pirat jest w forcie?! Chwytajcie go"+GetSexPhrase("on","jej")+"!","To pirat, węszący coś w naszym forcie! Do więzienia!!!");
							link.l1 = RandPhraseSimple("Tak, jestem piratem, i co teraz?","Heh, złap mnie jeśli potrafisz...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Czy nie widzisz "+NationNameGenitive(sti(pchar.nation))+" flagi na maszcie mojego statku?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "Zrzuciłem kotwicę niedaleko "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" pod flagą "+NationNameGenitive(sti(pchar.nation))+"! Jakiś problem?";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							notification("Trustworthy", "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Skill Check Failed", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Och, kapitanie, tak wspaniale się z tobą bawiliśmy na morzu! Ileż to razem statków zatopiliśmy pod twoim dowództwem! A tutaj...";
									link.l1 = "I tutaj, mój przyjacielu, możesz nacieszyć oczy uroczymi damami, których nie zobaczysz na morzu.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Kapitanie, co zrobiliśmy, aby na to zasłużyć?! Nie jesteśmy lądowymi szczurami, prawda?";
									link.l1 = "Cicho, marynarzu! Twoje stanowisko jest bardzo ważne i honorowe, więc przestań narzekać.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Co się dzieje na morzu, kapitanie? Czy kiedykolwiek to znowu zobaczymy?";
									link.l1 = "Ależ oczywiście, żeglarzu! Jak tylko zostaniesz zwolniony ze służby, możesz udać się na molo i cieszyć się morzem, ile tylko chcesz.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Chcę poskarżyć się, kapitanie: każdemu z nas brakuje morza. Wszyscy jesteśmy całkowicie znudzeni tą lądową służbą!";
									link.l1 = "Mam dość tego jęczenia! Macie tu wystarczająco dużo rumu! Służcie tam, gdzie kapitan was umieścił, albo ktoś zostanie powieszony jako przykład dla innych.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Powiedzę ci w zaufaniu, kapitanie, nowy gubernator to łapówkarz i defraudant. Ale to naprawdę nie moja sprawa...";
									link.l1 = "Dokładnie, korsarzu. Twoim zadaniem jest stać na swoim posterunku i utrzymywać porządek. A moim zadaniem jest powiesić gubernatora na rei. Dobra robota!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Dziękujemy za to, że o nas nie zapomniałeś, kapitanie! Pójdziemy za tobą przez ogień i wodę!";
									link.l1 = "Znam twój typ, łajdaki! Wszystko, co naprawdę kochasz, to złoto. Jest impreza w karczmie dzisiaj wieczorem, piwo na mój koszt. Nie zapomnij się pokazać.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, kapitanie! Tylko pomyśl, czy korsarz naprawdę może być stróżem porządku?! Minęło tak wiele czasu od naszego ostatniego prawdziwego interesu!";
									link.l1 = "Nie ma czasu na odpoczynek, korsarzu! Wrogie floty przemierzają wody w pobliżu naszych wysp, a my musimy być gotowi na rzeź w każdej chwili.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Kapitanie, słyszałem, że Korona wysłała w naszym kierunku kolejny szwadron?";
									link.l1 = "Oczywiście, korsarzu. Dopóki żyjemy, nie będzie dla nas spokoju. A nawet w piekle będziemy walczyć z diabłami!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Kurde, to było naprawdę mocne piwo wczoraj, kapitanie! Szkoda, że ciebie tam nie było.";
									link.l1 = "Nie wielka sprawa, nadrobię to. I nie zazdroszczę wam, chłopaki.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Powiedziałbym Ci w zaufaniu, kapitanie, bo zawsze dobrze się z nami obchodziłeś, wczoraj spędziliśmy naprawdę miło czas z bardzo sympatyczną laską...";
									link.l1 = "Heh, korsarzu, sznur to jest to, czego naprawdę potrzebujesz!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Kapitanie! Proszę, uwolnij mnie od tego przeklętego obowiązku! Po prostu nie mogę już dłużej grać roli stróża porządku.";
									link.l1 = "Nocna warta na statku też nie jest łatwa. Przyjacielu, obowiązek to obowiązek, cokolwiek by to nie było i gdziekolwiek by to nie było.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Jest ważna sprawa!","Mam do ciebie sprawę.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "Hej, kolego! Możesz mi zrobić małą przysługę?";
							link.l1 = "Zależy co trzeba zrobić.";
							link.l1.go = "Wine_soldier";
							link.l2 = "Nie mam czasu na to.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "Hej, kumple! Czy możesz mi zrobić małą przysługę?";
								link.l1 = "Zależy co trzeba zrobić.";
								link.l1.go = "Wine_soldier";
								link.l2 = "Nie mam na to czasu.";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Wasza Ekscelencjo, Generale Gubernatorze! Czym mogę służyć?";
							link.l1 = "Nie potrzebuję niczego, dziękuję.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "To jest dla mnie wielki honor, Panie Gubernatorze Generale! Jak mogę Ci pomóc?";
								link.l1 = "Wykonuj swoją służbę sumiennie - nie wymagam od ciebie niczego więcej.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Dobrze cię widzieć, Wasza Ekscelencjo! Co skromny żołnierz może zrobić dla gubernatora generalnego naszych kolonii?";
								link.l1 = "Osobiście, nie potrzebuję od ciebie niczego. Kontynuuj swoją służbę.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Wiceadmirał, Wasza Ekscelencjo! Pozwólcie mi zgłosić: podczas mojej warty...";
							link.l1 = "Uspokój się, żołnierzu, nie potrzebuję twojego raportu. Zgłoś się do swojego szefa.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Cieszę się, że cię widzę, Wiceadmirał! Mogę ci jakoś pomóc?";
								link.l1 = "Nie, tylko sprawdzałem, jak jesteś uważny. Cieszę się, że mnie rozpoznałeś.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Wiceadmirał, dla mnie to zaszczyt! Co mogę dla ciebie zrobić?";
								link.l1 = "Służ "+NationNameGenitive(sti(npchar.nation))+", żołnierzu! To najlepsze, co możesz zrobić.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Pozdrowienia, kapitanie! Jeśli masz dla mnie jakieś instrukcje, to proszę o wybaczenie: choć jestem w służbie "+NationNameGenitive(sti(npchar.nation))+", odpowiadam tylko komendantowi i gubernatorowi."; 
							link.l1 = "Mam swoich oficerów i załogę, którzy odpowiadają na moje prowadzenie. Wykonaj swoje obowiązki, żołnierzu.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Kapitanie, czy możesz zabrać mnie do służby na twoim statku? Ta sama służba za "+NationNameGenitive(sti(npchar.nation))+", ale wolę morze."; 
								link.l1 = "Jesteś potrzebny tam, gdzie cię przydzielono, więc wykonuj swoją służbę z honorem. Zamkniesz oczy na sekundę, a oni zabiorą to na morze.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, masz szczęście: jesteś kapitanem statku w służbie "+NationNameGenitive(sti(npchar.nation))+"... A ja tu tkwię cały dzień."; 
								link.l1 = "Czy myślisz, że właśnie przybyłem na Karaiby i tydzień później zostałem kapitanem? To wszystko lata ciężkiej pracy...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Nie widzisz? Jestem na służbie. Przestań mi przeszkadzać.";
							link.l1 = "Dobrze, dobrze...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Czy zamierzasz mi powiedzieć o jakiejś podejrzanej aktywności?";
							link.l1 = "Nie, wcale nie, a tak przy okazji jestem kapitanem. Widzę, że już nie słuchasz? Do widzenia.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "To jest obiekt wojskowy, więc nie hałasuj za bardzo tutaj.";
							link.l1 = "Dobrze, będę to miał na uwadze.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Taka ładna pogoda, a ja muszę tu stać. W mieście, przynajmniej są dziewczyny, a co mamy tutaj? Tylko szczury dookoła.";
							link.l1 = ""+GetSexPhrase("Rozumiem, ale nic nie mogę zrobić, aby pomóc - to przecież twój obowiązek.","Hej! Co ze mną nie tak? Czyż nie jestem dziewczyną?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Jeśli lubisz rozmawiać, znajdź kogoś innego. Muszę tutaj utrzymać porządek, a nie mam czasu na tanie gadanie.";
							link.l1 = "Och, nie, tylko sprawdzam, czy nadal żyjesz. Stałeś jak statua.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Pewnie myślisz, że dni pracy w garnizonie to bułka z masłem? Absolutnie nie! To ciężka i ważna praca. Pamiętam raz... ";
							link.l1 = "Opowiesz mi tę historię innym razem. Teraz trochę się spieszę.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Ostrożnie tutaj, jesteś w forcie! Bądź cichy jak mysz!";
							link.l1 = "Jak mówisz, żołnierzu.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hej! Czy masz może jakąś wodę? Umieram z pragnienia.";
							link.l1 = "Nie, kolego, zachowaj cierpliwość...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Jakie to nudne jest życie w garnizonie, tylko wieśniacy jak ty wokół! Teraz, garnizon miasta na pewno ma lepsze czasy...";
							link.l1 = "A ty nazywasz to 'byciem na służbie'? W ten sposób na pewno przepuścisz szpiega!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Wyglądasz na silnego gościa, co nie? Chciałbyś zaciągnąć się do służby w garnizonie fortu? Mamy przestronne koszary, dwie posiłki dziennie i darmowe gorzałki.","Och, młoda pani, nie masz pojęcia, jak przyjemnie jest spotkać taką miłą damę na tym zapomnianym końcu świata!")+"";
							link.l1 = ""+GetSexPhrase("To z pewnością kuszące, ale muszę odmówić. Wszystkie te ćwiczenia koszarowe po prostu nie są dla mnie.","Dziękuję za komplement, żołnierzu.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "To cholerna gorąco... Chętnie oddałbym połowę mojego życia, aby wrócić do Europy.";
							link.l1 = "Tak, widzę, że twoje zdrowie nie jest przystosowane do lokalnego klimatu.";
							link.l1.go = "exit";
						break;
					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "No tak... jasne. Słuchaj, to co "+GetSexPhrase("chciał","chciała")+" zapytać...";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "Widzisz, bardzo chcę trochę wina... Ale nie lokalnej swawoli zrobionej z zgniłych owoców, które sprzedaje się za dwa pesos za beczkę - chcę butelkę prawdziwego europejskiego wina. Możesz to zdobyć w mieście od kupców. Jest dość drogie, ale zapłacę w pełnej kwocie i nawet dorzucę na wierzch trzysta pesos. Czy przyniesiesz mi trochę?";
			link.l1 = "A dlaczego nie możesz tego zdobyć sam? Nie będziesz musiał przepłacać, po prostu poczekaj, aż zostaniesz zwolniony ze swojego stanowiska i idź po to. Gdzie jest haczyk?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "Nie ma żadnego haczyka. Po prostu nie mogę opuścić fortu, aby pójść do miasta, dopóki nie dostanę urlopu, co nie nastąpi w najbliższym czasie. Poza tym, nasz dowódca surowo zakazał picia w forcie, niech go diabli! Więc, pomożesz żołnierzowi?";
			link.l1 = "Cóż, dlaczego nie? Przyniosę ci to wino, i tak mam trochę wolnego czasu.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "Przykro mi, kolego, ale nie mogę tego zrobić. Szukaj kogoś innego, kto ci pomoże.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "Świetnie! Bardzo ci dziękuję! Dzisiaj mam wachtę, więc przyjdź jutro. Znajdziesz mnie na szczycie fortu, tam możesz mi podrzucić butelkę, żeby nikt nie zauważył...";
			link.l1 = "Dobrze. Poczekaj na mnie, przyjdę do ciebie jutro.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Wydaje mi się, że to jakaś sztuczka. Porozmawiajmy z komendantem, "+GetSexPhrase("kumpel","drogi")+", i wszystko zrozumiesz...","Hmm... Coś mi mówi, że nie jesteś tym, za kogo się podajesz... Oddaj swoją broń "+GetAddress_Form(npchar)+", i podążaj za mną do dalszego śledztwa!");
			link.l1 = RandPhraseSimple("Spadaj!","Gdy dwa niedziele przychodzą w jeden tydzień...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Och, rozumiem... Wszystko wygląda w porządku, możesz iść, "+GetAddress_Form(pchar)+".","Musiałem się trochę zmęczyć stojąc na wachcie... Wszystko wydaje się być w porządku, "+GetAddress_Form(pchar)+", Przykro mi.");
			link.l1 = "Nie ma problemu!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Tylko pomyśl o tym! Taka bezczelność! Przyjść tutaj pod przykrywką kupca! Twoje zdjęcia są umieszczone w każdym baraku, ty bękart! Tym razem ci się nie uda! Chwytajcie go!";
				link.l1 = RandPhraseSimple("Arrgh!..","Cóż, sam o to prosiłeś...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "Przyszedłeś tutaj handlować? Mogę zapytać jak? Gdzie jest twój statek? Wiesz, to wszystko wygląda bardzo podejrzanie, i jestem zmuszony zatrzymać cię, aż wszystko wyjaśnimy. Oddaj broń i chodź za mną!";
				link.l1 = RandPhraseSimple("Spadaj!","Gdy dwa niedziele przychodzą w jeden tydzień...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Twoja licencja musi zostać unieważniona, ponieważ wygasła i z tego powodu nie jest ważna. Oddaj swoją broń i podążaj za mną w celu dalszego śledztwa!";
				link.l1 = RandPhraseSimple("Spieprzaj!","Gdy dwa niedziele przychodzą w jeden tydzień...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Wszystko wygląda w porządku. Niemniej jednak, muszę zauważyć, że twoja licencja wygasa dzisiaj. Tym razem cię przepuszczę, ale nadal będziesz musiał zdobyć nową licencję.";
				link.l1 = "Dziękuję, zrobię to w najbliższej dogodnej chwili.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Wszystko wygląda w porządku. Aczkolwiek muszę zaznaczyć, że Twoja licencja wygaśnie wkrótce. Jest jeszcze ważna tylko przez "+FindRussianDaysString(iTemp)+". Więc miej to na uwadze, "+GetAddress_Form(npchar)+".";
				link.l1 = "Dziękuję, kupię nowy jak tylko będę miał okazję.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Cóż, wszystko wygląda dobrze. Twoja licencja jest ważna na "+FindRussianDaysString(iTemp)+". Możesz przejść.","Wszystko jest jasne, "+GetAddress_Form(npchar)+". Możesz swobodnie wchodzić i wychodzić z miasta, twoja licencja jest ważna na  "+FindRussianDaysString(iTemp)+". Przepraszam za kłopot.","Wszystko wygląda dobrze, "+GetAddress_Form(npchar)+", już cię tu nie zatrzymuję.");
				link.l1 = RandPhraseSimple("Świetnie. Najlepsze pozdrowienia.","Dziękuję, oficerze.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "Kapitanie, proszę odłożyć swoją broń: jest zabronione wyciągać je w naszym mieście.";
				link.l1 = LinkRandPhrase("Dobrze, schowam to...","Już zrobione.","Jak mówisz...");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("Spadaj!","Chyba skorzystam z tego!","Schowam to, kiedy nadejdzie odpowiedni czas.");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Dlaczego do diabła biegasz z obnażonym ostrzem? Natychmiast schowaj swoją broń!","Rozkazuję ci natychmiast schować broń!","Hej, "+GetSexPhrase("kumpel","dziewczynko")+", przestań przerażać ludzi! Schowaj swoją broń.");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Spadaj!","Nie ma nic złego w marzeniach...","Gdy dwa niedziele przychodzą w jeden tydzień.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
