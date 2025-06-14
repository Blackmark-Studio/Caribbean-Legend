// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
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
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple("Piraci w mieście?! Nie mogę w to uwierzyć... Zatrzymać "+GetSexPhrase("go","ją")+"!!","To pirat! Łapać "+GetSexPhrase("go","ją")+"!!!");
					link.l1 = RandPhraseSimple("Jestem piratem i co z tego?","Heh, możesz spróbować...");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("Kim jesteś i co tu robisz?","Stój tam! Kim jesteś i z jakiego prawa próbujesz wejść do miasta?");
						link.l2 = "Zrzuciłem kotwicę niedaleko "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" pod flagą "+NationNameGenitive(sti(npchar.nation))+". Jakiś problem? (Prawdopodobieństwo oszustwa "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("Szpieg! Złóż broń i chodź za mną!","Wrogi agent! Łapać "+GetSexPhrase("go","ją")+"!");
						link.l1 = RandPhraseSimple("A żeby cie jakieś choróbsko zabrało na tamten świat! Albo nie, sam cię tam wyśle!!","Kurwa mać! Musiałeś się akurat spojrzeć w moją strone?! Wiesz co to dla ciebie oznacza?!","Mogłeś mnie zignorować i przeżyłbyś. Teraz zginiesz, a za twój nędzny żołd nie będzie jak pogrzebu urządzić!","Eh, i tak już mi się znudziło skradanie. Czas się przejść przez legowisko w należyty sposób!");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("Kim jesteś i co tutaj robisz?","Stój! Kim jesteś i jakim prawem próbujesz wejść do miasta?");
						link.l1 = "Spójrz na ten papier, żołnierzu. Jestem tutaj za zgodą inkwizytora, ojca Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("Kim jesteś i co tutaj robisz?","Stój! Kim jesteś i jakim prawem próbujesz wejść do miasta?");
						link.l1 = "Spójrz na ten papier, żołnierzu. Jestem tutaj za zgodą inkwizytora, ojca Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("Zachowuj się i nie przeszkadzaj niewolnikom.","No dalej, idź swoją drogą!","Ach, to ty. Proszę, już o tobie nas poinformowano.");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("Kim jesteś i co tu robisz?","Stój tam! Kim jesteś i z jakiego prawda próbujesz wejść do miasta?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Oficerze, ja mam "+GetRusNameNationLicence(HOLLAND)+", więc jestem tutaj na legalnych podstawach. Proszę, spójrz...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Nie widzisz flagi "+NationNameGenitive(sti(pchar.nation))+"na maszcie mojego statku?! (Prawdopodobieństwo oszustwa "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "Zrzuciłem kotwicę niedaleko "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" pod flagą "+NationNameGenitive(sti(pchar.nation))+". Jakiś problem? (Prawdopodobieństwo oszustwa "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Piraci w mieście?! Nie mogę w to uwierzyć... Aresztujcie go!","To pirat! Schwytać go!");
							link.l1 = RandPhraseSimple("Tak, jestem piratem - i co teraz?","Heh, złap mnie jeśli potrafisz...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Czy nie widzisz flagi "+NationNameGenitive(sti(pchar.nation))+" na moim statku?! (Prawdopodobieństwo oszustwa "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "Zrzuciłem kotwicę niedaleko "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" pod flagą "+NationNameGenitive(sti(pchar.nation))+". Jakiś problem? (Prawdopodobieństwo oszustwa "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, kapitanie, tak wspaniale spędziliśmy z tobą czas na morzu! Ile to statków razem zatopiliśmy pod twoim dowództwem! A teraz...";
									link.l1 = "I tutaj, mój przyjacielu, możesz nacieszyć oczy uroczymi damami, nie zobaczysz ich na morzu.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Kapitanie, co zrobiliśmy, żeby na to zasłużyć?! Nie jesteśmy lądowymi szczurami, prawda?";
									link.l1 = "Cicho, marynarzu! Twoje stanowisko jest bardzo ważne i honorowe, więc przestań narzekać.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Co się dzieje na morzu, kapitanie? Czy kiedykolwiek to znowu zobaczymy?";
									link.l1 = "Ależ oczywiście, marynarzu! Kiedy tylko zostaniesz zwolniony z obowiązków, możesz udać się na molo i cieszyć się morzem, ile tylko chcesz.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Chcę złożyć skargę, kapitanie: każdy z nas tęskni za morzem. Jesteśmy całkowicie znudzeni tą lądową służbą!";
									link.l1 = "Mam dość tego biadolenia! Masz tu też wystarczająco dużo rumu! Służ tam, gdzie kapitan cię postawił, a inaczej ktoś zostanie powieszony na przykład dla innych.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Powiedziałbym Ci w zaufaniu, kapitanie, że nowy gubernator to łapówkarz i defraudant. Ale to naprawdę nie moja sprawa...";
									link.l1 = "Dokładnie, korsarzu. Twoim zadaniem jest stać na swoim posterunku i utrzymywać porządek. A powiesić gubernatora na rei to moja sprawa. Dobra robota!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Dziękujemy, że o nas nie zapomniałeś, kapitanie! Pójdziemy za tobą przez ogień i wodę!";
									link.l1 = "Znam twój typ, łajdaki! Wszystko, co naprawdę kochasz, to złoto. Dziś wieczorem jest impreza w karczmie, pijemy za mój rachunek. Nie zapomnij się pojawić.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, kapitanie! Tylko pomyśl, czy korsarz może naprawdę być stróżem porządku?! Minęło tak wiele czasu od kiedy ostatnio zajmowaliśmy się prawdziwym biznesem!";
									link.l1 = "Nie ma czasu na relaks, korsarzu! Wrogie armady przeszukują wody w pobliżu naszych wysp, a my musimy być gotowi na rzeź w każdej chwili.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Kapitanie, słyszałem, że Korona wysłała w naszą stronę kolejny szwadron?";
									link.l1 = "Oczywiście, korsarzu. Dopóki żyjemy, nie będzie dla nas pokoju. A nawet w piekle będziemy walczyć z diabłami!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Kurde, to było naprawdę mocne piwo wczoraj, kapitanie! Szkoda, że tam nie było cię.";
									link.l1 = "Nie wielka sprawa, nadrobię to. I nie zazdroszczę wam, chłopaki.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Powiedzę ci w zaufaniu, kapitanie, bo zawsze dobrze się z nami obchodziłeś, wczoraj mieliśmy naprawdę dobry czas z bardzo miłą dziewczyną...";
									link.l1 = "Heh, korsarzu, na pewno potrzebujesz szubienicy!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Kapitanie! Proszę, uwolnij mnie od tego przeklętego obowiązku! Po prostu nie mogę już dłużej udawać strażnika porządku.";
									link.l1 = "Nocna warta na statku też nie jest łatwa. Przyjacielu, obowiązek to obowiązek, cokolwiek i gdziekolwiek jest.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Jest ważna sprawa!","Mam do ciebie sprawę.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("Uwaga! Zbrojny, chory psychol jest tu!","Do broni, do broni! Jakiś szalony dranie jest tutaj!");
								link.l1 = RandPhraseSimple("He? Co?","Eh, dlaczego to robisz?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("Masz do mnie sprawę, kapitanie?","Ja tu załatwiam sprawy, jeśli czegoś potrzebujesz - pytaj, nie zwlekaj."),RandPhraseSimple("Kapitanie, jestem bardzo zajęty, więc szukaj innych rozmówców.","Czy coś jest nie tak, kapitanie? Jeśli nie ma pytań, pozwól mi przejść."),"Przejdź, kapitanie, śpieszę się.");
							link.l1 = LinkRandPhrase("Przepraszam, przyjacielu, "+GetSexPhrase("pomyliłem się","pomyliłam się")+" ","Dobrze, zajmij się swoimi sprawami.","Nie, nic.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("Mam do ciebie kilka pytań.","Mam do ciebie sprawę."),RandPhraseSimple("Widzę, że się spieszyłeś. Jedno pytanie i będziesz wolny.","Ja "+GetSexPhrase("chciał","chciała")+"zapytać o coś."),"Twoje sprawy poczekają. Chciałem zapytać o coś "+GetSexPhrase("chciał","chciała")+".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("Co chcesz? Przejdź obok.","Przestań blokować drogę, cofnij się.");
					            link.l1 = RandPhraseSimple("Wiesz co? Nie szczekaj!","Ogranicz swój zapał. Nie ochłone tak szybko!");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("Mam do ciebie kilka pytań.","Mam do ciebie sprawę."),RandPhraseSimple(" Widzę, że się spieszysz. Jedno pytanie i będziesz wolny.","Ja "+GetSexPhrase("chciałem","chciałam")+" zapytać o coś."),"Twoje sprawy poczekają. Chciałem zapytać o coś.");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Spójrzcie  "+GetSexPhrase("na tego łajdaka! Odważył się pokazać swoją twarz","na tamtą szmate! Ośmieliła się pokazać swoją twarz")+" w "+XI_ConvertString("Colony"+npchar.city)+". Brać "+GetSexPhrase("go","ją")+"!!!","Hej, rozpoznaje cię, "+GetSexPhrase("łotrze","cwaniaro")+"! Łapać "+GetSexPhrase("go","ją")+"!!!");
							link.l1 = RandPhraseSimple("Argh!..","Cóż, sam się o to prosiłeś...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "O, popatrz! Pani "+pchar.GenQuest.EncGirl.name+" sama zaszczyciła nas swoją obecnością! Zastanawiam się, jak miałaś odwagę? Szukaliśmy ciebie! Proszę iść do lochu - twoja cela jest gotowa i czeka na ciebie. ";
							link.l1 = "Jakie to kompletna bzdura, o czym ty mówisz!? Ja i mój "+GetSexPhrase("kawaler","towarzysz")+" spacerowaliśmy po dżungli, zbierając kwiaty. Zostaw mnie w spokoju! Gdzie są maniery tych despotów?! Jak tylko zobaczą atrakcyjną dziewczynę, zaczynają ją dręczyć! "+GetSexPhrase("Moja droga, powiedz tym durniom, żeby spadli i zostawili uczciwą kobietę w spokoju!","Kochanie, proszę powiedz tym durniom...")+"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "O, tutaj jesteś, piękna! Twój tata zaciągnął całą załogę, aby cię znaleźć i przyprowadzić do domu.";
							link.l1 = "Zejdź z drogi! Wiem, dokąd idę i nie potrzebuję twojej pomocy! Kapitanie, powiedz im, żeby odsunęli ode mnie swoje łapy.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях
					
					// --> Sinistra Длинные тени старых грехов
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_1"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Słuchaj, Charlie, mamy kilku nowych rekrutów w forcie. Zieloni jak trawa... Mógłbyś wpaść i pokazać im, jak celować?";
							link.l1 = "Jeśli Kapitan Fleetwood i ja nie wypłyniemy w najbliższych dniach - z przyjemnością.";
							link.l1.go = "Knippel_Soldiers_1";
							break;
						}
						break;
					}
					
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_2"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Charlie, mój dyżur się kończy, może napijesz się ze mną?";
							link.l1 = "Z przyjemnością, kumplu! Pozwól mi tylko zobaczyć, czego kapitan chce.";
							link.l1.go = "Knippel_Soldiers_2";
							break;
						}
						break;
					}
					
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_3"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Dobranoc, Charlie! Nie wyglądasz zbyt dobrze. Wszystko w porządku?";
							link.l1 = "Obudzili mnie w środku nocy, co myślisz? Nie mogę złapać przerwy.";
							link.l1.go = "Knippel_Soldiers_3";
							break;
						}
						break;
					}
					// <-- Длинные тени старых грехов

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "Życie żołnierza to harmonogram - straż, patrolowanie ... Czego chcesz, "+GetAddress_Form(NPChar)+"?";
						link.l1 = "Słuchaj, to z tobą ten pijak ostatnio się tu bił? Cóż, chociaż, najwyraźniej, tak, z tobą...";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Wasza Wysokość, Gubernatorze Generale! Jak mogę służyć?";
							link.l1 = "Nie potrzebuję niczego, dziękuję.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "To jest dla mnie wielki honor, Panie Gubernatorze Generale! Jak mogę ci pomóc?";
								link.l1 = "Wykonuj swoje obowiązki sumiennie - nie wymagam od ciebie niczego więcej.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Dobrze Cię widzieć, Wasza Ekscelencjo! Co pokorny żołnierz może zrobić dla gubernatora-generalnego naszych kolonii?";
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
							link.l1 = "Uspokój się, żołnierzu, nie potrzebuję twojego raportu. Zgłoś się do swojego oficera.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Cieszę się, że cię widzę, wiceadmirał! Czy mogę ci w czymś pomóc?";
								link.l1 = "Nie, tylko sprawdzałem, jak uważny jesteś. Cieszę się, że mnie rozpoznałeś.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Wiceadmirał, to dla mnie zaszczyt! Co mogę dla ciebie zrobić?";
								link.l1 = "Służyć "+NationNameGenitive(sti(npchar.nation))+", żołnierzu! To najlepsze, co możesz zrobić.";
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
							dialog.text = "Pozdrowienia, kapitanie! Jeśli masz dla mnie jakieś instrukcje, to przepraszam: chociaż jestem w służbie "+NationNameGenitive(sti(npchar.nation))+", Odpowiadam tylko komendantowi i gubernatorowi."; 
							link.l1 = "Mam swoich oficerów i załogę, którzy słuchają moich wskazówek. Wykonaj swoje obowiązki, żołnierzu.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Kapitanie, czy możesz przyjąć mnie do służby na swoim statku? Tak samo służę za "+NationNameGenitive(sti(npchar.nation))+", ale wolę morze."; 
								link.l1 = "Potrzebny jesteś tam, gdzie cię przydzielono, więc wykonuj swoją służbę z honorem. Zamkniesz oczy na sekundę, a oni zabiorą to na morze.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, masz szczęście: jesteś kapitanem statku na służbie "+NationNameGenitive(sti(npchar.nation))+"... A ja tkwię tu cały dzień."; 
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
							dialog.text = "Czy zamierzasz mi opowiedzieć o jakiejś podejrzanej aktywności?";
							link.l1 = "Nie, wcale nie, a tak przy okazji jestem kapitanem. Widzę, że już nie słuchasz? Do widzenia.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "To jest obiekt wojskowy, więc nie rób tu zbyt dużo hałasu.";
							link.l1 = "Dobrze, będę miał to na uwadze.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Taka piękna pogoda, a ja muszę tu stać. W mieście są przynajmniej dziewczęta, a co mamy tutaj? Tylko szczury dookoła.";
							link.l1 = ""+GetSexPhrase("Współczuję, ale nic nie mogę zrobić, aby pomóc - to przecież twój obowiązek.","Hej! Co ze mną nie tak? Czyż nie jestem dziewczyną?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Jeśli lubisz rozmawiać, znajdź kogoś innego. Muszę tu utrzymać porządek i nie mam czasu na tanie rozmowy.";
							link.l1 = "Och, nie, tylko sprawdzam, czy jeszcze żyjesz. Stałeś jak posąg.";
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
							dialog.text = "Hej! Masz może jakąś wodę? Umieram z pragnienia.";
							link.l1 = "Nie, przyjacielu, bądź cierpliwy...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Jak nudne jest życie w garnizonie, tylko wieśniaki jak ty wokół! Teraz, garnizon miasta na pewno ma lepsze czasy...";
							link.l1 = "I ty nazywasz to 'byciem na służbie'? W ten sposób na pewno przepuścisz szpiega!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Wyglądasz na silnego gościa, co nie? Chciałbyś zaciągnąć się do służby w garnizonie fortu? Mamy przestronne koszary, dwa posiłki dziennie i alkohol za darmo.","Och, młoda damo, nie masz pojęcia, jak miło jest spotkać taką miłą damę w tym zapadłym miejscu!")+"";
							link.l1 = ""+GetSexPhrase("To na pewno kuszące, ale muszę odmówić. Ten cały koszarowy dryl to po prostu nie dla mnie.","Dziękuję za komplement, żołnierzu.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Te cholerne gorąco... Chętnie oddałbym wszystko, aby wrócić do Europy.";
							link.l1 = "Tak, widzę, że twoje zdrowie nie jest dostosowane do lokalnego klimatu.";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Chwileczkę. Chciałem zapytać o coś "+GetSexPhrase("chciał","chciała")+"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Wydaje mi się, że to jakaś sztuczka. Porozmawiamy z komendantem, "+GetSexPhrase("przyjacielu","moja droga")+", i wszystko sobie wyjaśnimy...","Hmm... Coś mi mówi, że nie jesteś tym, za kogo się podajesz... Oddaj swoją broń "+GetAddress_Form(npchar)+", i podążaj za mną!");
			link.l1 = RandPhraseSimple("Nigdzie nie ide! Spieprzaj!","Myślisz, że się poddam? Zaryzykuje drugą opcję...");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Och, rozumiem... Wszystko wydaje się w porządku, możesz iść, "+GetAddress_Form(pchar)+".","Musiałem się trochę zmęczyć stojąc na straży... Wydaje się, że wszystko jest w porządku, "+GetAddress_Form(pchar)+", Przepraszam.");
			link.l1 = "Nie ma problemu!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("Ach, rozumiem... Wszystko wydaje się być w porządku, możesz iść, "+GetAddress_Form(pchar)+".","Zobaczmy... Cóż, wszystko wydaje się być w porządku, "+GetAddress_Form(pchar)+", Przepraszam.");
			link.l1 = "Nie ma problemu!";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Właśnie przyszło mi to do głowy! Taka bezczelność! Przybyć tu pod pozorem kupca! Twoje portrety wiszą w każdych koszarach, ty sukinsynie! Tym razem ci się to nie uda! Łapcie go!";
				link.l1 = RandPhraseSimple("Arrgh!..","No cóż, sam się o to prosiłeś...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "Przybyłeś tutaj handlować? Mogę zapytać jak? Gdzie jest twój statek? Wiesz, to wszystko wygląda bardzo podejrzanie, dlatego jestem zmuszony cię zatrzymać, dopóki nie wyjaśnimy tego wszystkiego. Oddaj swoją broń i idź za mną!";
				link.l1 = RandPhraseSimple("Spierdalaj!","Myślisz, że się poddam? Zaryzykuje drugą opcję...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Twoja licencja musiała zostać unieważniona, ponieważ wygasła i z tego powodu jest nieważna. Oddaj swoją broń i podążaj za mną w celu dalszego śledztwa!";
				link.l1 = RandPhraseSimple("Spadaj!","Myślisz, że się poddam? Zaryzykuje drugą opcję...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Wszystko wygląda w porządku. Niemniej jednak muszę zauważyć, że twoja licencja wygasa dokładnie dzisiaj. Tym razem cię przepuszczę, ale nadal będziesz musiał zdobyć nową licencję.";
				link.l1 = "Dziękuję, kupię nową, jak tylko będę miał okazję.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Wszystko wygląda w porządku. Muszę jednak zauważyć, że twoja licencja wkrótce wygaśnie. Jest jeszcze ważna tylko przez "+FindRussianDaysString(iTemp)+". Miej to na uwadze, "+GetAddress_Form(npchar)+".";
				link.l1 = "Dziękuję, kupię nową jak najszybciej, gdy będzie to możliwe.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Cóż, wszystko wygląda dobrze. Twoja licencja jest ważna jeszcze przez "+FindRussianDaysString(iTemp)+". Możesz przejść.","Wszystko jest jasne, "+GetAddress_Form(npchar)+". Możesz swobodnie wchodzić i wychodzić z miasta, twoja licencja jest ważna jeszcze przez "+FindRussianDaysString(iTemp)+". Przepraszam za kłopot.","Wszystko wygląda dobrze, "+GetAddress_Form(npchar)+", już cię tu nie zatrzymuję.");
				link.l1 = RandPhraseSimple("Świetnie. Najlepsze pozdrowienia.","Dziękuję, oficerze.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Hej, kolego, niczego nie psuj w latarni morskiej.","Ta latarnia morska to bardzo ważny obiekt miasta. Bądź ostrożny!");
			link.l1 = RandPhraseSimple("W porządku, nie martw się.","Dobrze, nie martw się.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Nie chodź blisko dział - to jest wojskowy obiekt!","Obcy nie mają dostępu do dział!","Jeśli zauważę, że kręcisz się w pobliżu dział, jesteś skończony!");
			link.l1 = RandPhraseSimple("Przyjąłem.","W porządku, rozumiem.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "A kim jesteś, kapitanie? Czyżbyś przypadkiem nie był wspólnikiem najbardziej notorycznego złodzieja w tej osadzie?";
			link.l1 = "Kogo ty właśnie nazwałeś wspólnikiem w przestępstwie?! Czy ty jesteś oślepiony słońcem, czy co?! Hej, zdejmij swoje łapy od dziewczyny!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Właściwie, to ja..."+GetSexPhrase("poznałem ją","poznałam ją")+" niedawno...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+GetSexPhrase("Panie","Panno")+", mamy rozkaz zatrzymać ją i zabrać do lochu. A jeśli myślisz, że możesz nas zatrzymać, mylisz się.";
			link.l1 = "Zobaczmy, więc...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "Ach, naprawdę? W takim razie radziłbym ci sprawdzić swoje kieszenie. Ta dama jest profesjonalistką, wiesz";
			link.l1 = "Dziękuję, zrobię to. Jak mogłem się tak ośmieszyć...";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+GetSexPhrase("Panie","Panno")+", mamy rozkaz znaleźć tę damę i przyprowadzić ją do jej ojca.";
			link.l1 = "No cóż, rozkaz to rozkaz - idź więc dalej.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Za późno na to, bo już rozmawiam z jej ojcem.";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Kapitanie, mamy rozkaz, a jeśli myślisz, że możesz nas zatrzymać, jesteś w błędzie.";
				link.l1 = "Zobaczmy, więc...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Heh, "+GetSexPhrase("jesteś szczęściarzem","jesteś szczęśliwą dziewczyną")+". Jej ojciec obiecał hojną nagrodę temu, kto przyprowadzi ją z powrotem do niego.";
				link.l1 = "Nie rozpaczaj - przed tobą jeszcze wiele nagród.";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "Tak, ze mną. Niech siedzi za kratkami, zastanowi się nad swoim zachowaniem. A jeśli przyszedłeś mi za niego grozić, to uwierz mi: Mogę się nawet zwrócić do komendanta fortu.";
			link.l1 = "Tak, nie przyszedłem grozić, ale prosić cię o wycofanie swoich roszczeń przeciwko niemu. Widzisz, to stary znajomy mojego, po prostu się upił, ale dla pijaka, wiesz, morze jest po kolana...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "Czyli dał mi w twarz, kiedy byłem na służbie, a teraz powinien być wypuszczony? Dlaczego miałoby do tego dojść?";
			link.l1 = "Co powiesz na pięćset pesos jako przeprosiny za jego zachowanie?";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "Czy tak myślisz? Obraził mój honor, i myślisz, że to może być przebaczone za pięćset pesos? Czy myślisz, że mój honor można kupić?";
			link.l1 = "...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "Nie, Kapitanie, to wszystko jest sprawiedliwe. On na to zasłużył. I proszę cię, abyś nie odciągał mnie już od mojej służby.";
				link.l1 = "Cóż, masz rację.";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "Tysiąc. I ani peso mniej.";
				link.l1 = "Nie, może nie jestem gotów zapłacić tak dużo za jedno siniaka.";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "Oh... Dobrze, chwileczkę. Oto pióro i pergamin. Napisz, że wycofujesz wszelkie roszczenia wobec mojego przyjaciela.";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "W takim razie proszę cię, abyś już nie odciągał mnie od mojej służby.";
			link.l1 = "Nie zrobię tego.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Oto jesteś.";
			link.l1 = "Powodzenia w pracy.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Длинные тени старых грехов
		case "Knippel_Soldiers_1":
			dialog.text = "I może naucz ich paru swoich sekretów, żeby nie zabrać ich ze sobą do grobu?";
			link.l1 = "Heh-heh, uh, nie, kumple, moje sekrety są tylko moje, i jakie to byłyby sekrety?";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			pchar.questTemp.Knippel.Soldiers_2 = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Knippel_Soldiers_2":
			dialog.text = "Rozumiem, znowu zrezygnujesz, jak zawsze.";
			link.l1 = "No cóż, jeśli ryba ucieka - to zły rybak. To jak z kulkami armatnimi - dobra nigdy cię nie zawiedzie, wystarczy dobrze celować...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			pchar.questTemp.Knippel.Soldiers_3 = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Knippel_Soldiers_3":
			dialog.text = "Przynajmniej nie wstajesz co noc. I spędzasz więcej czasu na statku niż na lądzie. Z kim rozmawiasz?";
			link.l1 = "Ach, co ty wiesz o trudach służby, kumplu! Jak to było w Royal Navy!.. Nie możesz sobie nawet wyobrazić.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
			LAi_CharacterDisableDialog(npchar);
		break;
		// <-- Длинные тени старых грехов
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "Kapitanie, proszę schować swoją broń: chodzenie z wyciągniętą bronią jest zabronione naszym mieście.";
			link.l1 = LinkRandPhrase("Dobrze, schowam to...","Już się robi.","Skoro tak mówisz...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Jebać cię!","A co mi zrobisz?!","Schowam to, kiedy nadejdzie odpowiedni czas.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Hej, co to za machanie bronią?! Schowaj to natychmiast!","Rozkazuję ci natychmiast schować broń!","Hej, "+GetAddress_Form(NPChar)+", przestań straszyć ludzi! Schowaj swoją broń.");
			link.l1 = LinkRandPhrase("Dobrze, schowam to...","Już się robi.","Skoro tak mówisz...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Spadaj!","A co mi zrobisz?!","Schowam to, gdy nadejdzie odpowiedni czas.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
