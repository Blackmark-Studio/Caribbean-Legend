//Jason общий диалог мещан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity, sTitle;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Mówią, że jesteś panem tego miasta, "+GetSexPhrase("panie","panna")+".","Co za miłe spotkanie, "+GetSexPhrase("panie","panno")+"!");
					link.l1 = RandPhraseSimple("Zmieniam zdanie. Powodzenia!","Po prostu spaceruję po mieście. Do widzenia.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Chcę omówić sprawy finansowe.","O finansach...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("Alarm! Uzbrojony szaleniec tutaj! Do broni!","Do broni! Uzbrojony szaleniec jest tutaj!");
						link.l1 = RandPhraseSimple("Co?!","Co ty robisz?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("Czego chcesz? Ruszaj dalej.","Przestań blokować mi drogę, zjeżdżaj.");
						link.l1 = RandPhraseSimple("Wiesz co? Nie szczekaj!","Uspokój się. Albo zrobię to osobiście!");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("Chcę cię o coś zapytać.","Proszę o chwilę uwagi. Jedno pytanie.");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("Chcę omówić sprawy finansowe.","O finansach...");
								link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
							}
						}
					}
				}
				break;
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsWarShipType(pchar), IsRaiderShipType(pchar))) ok = false;
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//горожанин-пассажир
				{
					dialog.text = "Dzień dobry, "+GetAddress_Form(NPChar)+" Widzę, że jesteś kapitanem własnego statku. Chcę cię prosić o przysługę...";
					link.l1 = "Słucham, "+GetAddress_FormToNPC(NPChar)+"  Czego chcesz?";
					link.l1.go = "passenger";
					link.l2 = "Przepraszam, "+GetAddress_FormToNPC(NPChar)+", ale się spieszę.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Jestem ","Moje imię to ","Możesz mnie nazywać ")+GetFullName(npchar)+LinkRandPhrase("  Czego chcesz?","Nie widziałem cię tu wcześniej. Kim jesteś?","Kim jesteś i czego ode mnie chcesz?"),LinkRandPhrase("Pozdrowienia, "+GetAddress_Form(NPChar)+"  Nazywam się "+GetFullName(npchar)+" . A jak masz na imię?","Cześć, "+GetAddress_Form(NPChar)+"! Jestem "+GetFullName(npchar)+" Czy mogę poznać twe imię?","Tak, "+GetAddress_Form(NPChar)+". Czego chcesz? A tak przy okazji, nazywam się "+GetFullName(npchar)+" A jak się nazywasz?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Do diabła ze mną! ","Cholera! ","Do diabła z tobą! ")+"Tak, jestem kapitanem "+GetFullName(Pchar)+LinkRandPhrase(", czy nigdy nie słyszałeś "+NPCharSexPhrase(NPChar,", łajdaku?","?")," i "+GetSexPhrase("najsłynniejszy pirat","najsłynniejsza dziewczyna-pirat")+"na morzu!"," i niech mnie diabli wezmą, jeśli się mylę!"),LinkRandPhrase("Jestem "+GetFullName(Pchar)+", kapitanie."," Nazywam się "+GetFullName(Pchar)+".","Możesz mnie nazywać kapitanem "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Całe miasto jest na krawędzi - przybył don Fernando de Alamida, królewski inspektor. Wiesz, wiele tu widziałem, ale to... To nie żal zmienia ludzi, ale to, jak sobie z nim radzą. Mówią, że stał się innym człowiekiem po śmierci ojca. Teraz nie znajdziesz bardziej nieprzekupnego i... bezlitosnego sługi Korony w całym Archipelagu.","Spójrz tylko na 'Świętą Łaskę'! Mówią, że sam król zlecił jej budowę według specjalnych projektów. I zauważ - ani jednej ryski. Jakby sama Matka Boska ją chroniła. Choć słyszałem plotki... może to wcale nie Matka Boska.","Wiesz, ile razy próbowali zabić don Fernanda? Dwanaście ataków na otwartych wodach - i to tylko w zeszłym roku! Cóż, z tak wierną i wyszkoloną załogą, i pod ochroną Pana - przetrwa trzynasty również!"),LinkRandPhrase("Słyszałeś? Don Fernando de Alamida przybył do naszego miasta i mówią, że jest teraz gdzieś na ulicach. Chciałbym zobaczyć go na własne oczy...","Skomplikowany człowiek, ten don Fernando. Niektórzy mówią, że jest zbawcą, oczyszczającym Ojczyznę z plugastwa. Inni szepczą, że coś w nim pękło po śmierci ojca i wkrótce wszyscy będziemy płakać. Ale powiem ci jedno: nie obawiaj się jego. Obawiaj się tych, którzy uczynili go takim, jakim jest.","Taki przystojny mężczyzna, ten don Fernando! Ale wiesz, co jest dziwne? Jakby nikogo nie zauważał. Cały oddany obowiązkom i służbie. Słyszałam, że była jakaś dziewczyna... ale po spotkaniu z jakimś księdzem całkowicie odrzucił ziemskie przyjemności. Jakby złożył ślub."),RandPhraseSimple(RandPhraseSimple("Przeklęty inspektor! Gdy on tu jest - miasto jak martwe. Żadnego handlu, żadnej zabawy. Nawet oddychać, zdaje się, trzeba ciszej. I wiesz, co jest najbardziej przerażające? Tak jest w każdym porcie. Jak w zegarku. Jego Królewska Mość nie mógłby celowo wymyślić tej tortury dla nas wszystkich!","Don Fernando znowu odwiedził sierociniec. Hojnie dotuje, modli się godzinami. Taki szlachetny człowiek powinien być stawiany za wzór tym przeklętym defraudatorom!"),RandPhraseSimple("Ha! 'Święty' Fernando znów zamknął wszystkie domy publiczne. No cóż, nieważne, niedługo odpłynie i znów je otworzą.","Ins... inspektor przybył, oto co! Don Fernando de Almeyda, czy jak mu tam, Alamida! Tak ważny, że sam gubernator obchodzi się z nim jak z jajkiem. Mówią, że patrzy ci w oczy i od razu widzi wszystkie twoje grzechy. Przerażające!")));
					link.l1 = "... ";
					link.l1.go = "exit";
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== Леди Бет в порту города
			}
			else
			{
				link.l1 = PCharRepPhrase("Chcę tylko zapytać o tę dziurę, którą nazywasz 'miastem'.","Chcę zapytać cię o coś związanego z tym miastem.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("Chcę omówić sprawy finansowe.","O kwestiach finansowych...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Słuchaj, mam nadzieję, że możesz mi pomóc. Chcę kupić "+pchar.GenQuest.Device.Shipyarder.Type+", i powiedziano mi, że ta rzecz była sprzedawana w twoim mieście. Cóż, ktoś sprzedawał to na ulicach. Wiesz coś o tym?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Czy wiesz ","Czy jesteś świadomy ","Słyszałeś ")+"że lokalny kościół został niedawno okradziony?";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ach, to ty "+GetFullName(Pchar)+" "+GetSexPhrase(" - stary przyjacielu!"," - piękna!")+"","Cieszę się, że cię widzę, "+GetSexPhrase("stary przyjacielu!","ślicznotko!")+" "+Pchar.name,"O, to jest "+GetSexPhrase("sam kapitan","sama kapitan")+" "+GetFullName(Pchar))+RandPhraseSimple(" . Myślałem, że nie żyjesz!",". A być może "+GetSexPhrase("Pijany jak zawsze.","trochę pijany."))+LinkRandPhrase("Śmiało, czego potrzebujesz?"," Co tym razem?","Znowu mnie niepokoisz?"),LinkRandPhrase(TimeGreeting()+", kapitanie ","Dobry dzień dla ciebie, "+GetAddress_Form(NPChar)+" ","Witaj, kapitanie ")+GetFullName(Pchar)+LinkRandPhrase(" Jak mogę pomóc "+GetSexPhrase("tak zacny człowiek","taka godna dziewczyna")+", jak ty?"," . Dlaczego tu jesteś?"," Co chcesz wiedzieć tym razem?")),PCharRepPhrase(LinkRandPhrase("Cześć, kapitanie ","Pozdrowienia, ah, to ty "+GetAddress_Form(NPChar)+" ","Ah, kapitanie ")+GetFullName(Pchar)+LinkRandPhrase(", myślałem, że już nigdy się nie spotkamy, i",", nie powiem, że cieszę się na twój widok, ale",", widzę, że wciąż żyjesz, jaka szkoda i")+LinkRandPhrase(" czego chcesz?","dlaczego tu jesteś?"," jak mogę ci pomóc?"),LinkRandPhrase(TimeGreeting()+", kapitanie "+GetFullName(Pchar)+" Jak mogę ci pomóc?","O, to kapitan "+GetFullName(Pchar)+"! Jak mogę ci pomóc?","Pozdrowienia, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+"Chcesz czegoś?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Twoje uszy cię zwodzą. Muszę iść.","Nie, to nic, byłem w drodze do tawerny."),RandPhraseSimple("Dobrze, cokolwiek. Powodzenia!","Po prostu spaceruję po mieście. Żegnaj."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Pytania?";
			link.l1 = "Czy nazwisko na tych dokumentach coś ci mówi?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Nie obchodzi mnie jakiś losowy papier, a poza tym nie umiem czytać. Idź do lichwiarza, mówią, że on potrafi robić cuda z literami, ha!","Nie wiem, o czym mówisz, zapytaj kogoś innego, kapitanie"+GetFullName(Pchar)+".","Nie wiem, jak ci pomóc, kapitanie "+GetFullName(Pchar)+"Spróbuj porozmawiać z lichwiarzem, on może coś wiedzieć.");
			link.l1 = "Dzięki.";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Czyżbyś kłamał, kapitanie "+GetFullName(Pchar)+"?","Więc co "+PChar.name+"?","Zapamiętam cię, "+GetFullName(Pchar)+".")+"Teraz powiedz mi, czego chcesz?",LinkRandPhrase("Miło cię poznać, kapitanie "+PChar.name,"Rad z naszego spotkania, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"To przyjemność, kapitanie "+PChar.name)+" . Ale wątpię, że chciałeś tylko poznać moje imię, prawda?");
            link.l1 = PCharRepPhrase("Chcę tylko zapytać o to dziadostwo, które nazywasz 'miastem'.","Chcę cię zapytać o coś związanego z tym miastem.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("Chcę omówić sprawy finansowe.","O finansach...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Słuchaj, mam nadzieję, że możesz mi pomóc. Chcę kupić "+pchar.GenQuest.Device.Shipyarder.Type+", a powiedziano mi, że ta rzecz była sprzedawana w twoim mieście. Cóż, ktoś sprzedawał ją na ulicach. Wiesz coś na ten temat?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Czy wiesz ","Czy jesteś świadomy ","Słyszałeś ")+" że lokalny kościół został niedawno okradziony?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Twoje uszy cię zwodzą. Muszę iść.","Nie, to nic takiego, byłem w drodze do tawerny."),RandPhraseSimple("Cóż, to nic. Powodzenia!","Po prostu spaceruję po mieście. Żegnaj."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Och, i cieszę się, że cię widzę, jakbym się cieszył z gorzałki, pytaj o co chcesz.","Lubi pan gawędzić, kapitanie? Ja też... Zwłaszcza przy kubku rumu.","Tak, "+PChar.name+"? "),LinkRandPhrase("Czego jeszcze chcesz?","Przyjmuję to, kapitanie "+PChar.name+", że lubisz sobie pogadać?")),PCharRepPhrase(LinkRandPhrase("Czego jeszcze chcesz, "+GetAddress_Form(NPChar)+"?","Słucham, kapitanie.","Muszę iść, więc pytaj mnie szybko, kapitanie."),LinkRandPhrase("Zawsze się cieszę z miłego towarzystwa, "+GetAddress_Form(NPChar)+" "+PChar.lastname+" Mów.","Tak, "+GetAddress_Form(NPChar)+"?","Lubisz rozmawiać, kapitanie? Ja też... ")));
			link.l1 = LinkRandPhrase("Jakie plotki krążą po tym mieście?","Jakieś wieści z tych stron?","Jak tam życie na lądzie?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("Pokażesz mi drogę?","Nie mogę znaleźć drogi do jednego miejsca...","Pomóż mi dotrzeć do jednego miejsca...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Chcę wiedzieć, co ludzie mówią o pewnej osobie.","Czy wiesz, co ludzie mówią o jednej osobie?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Chcę dowiedzieć się więcej o miejscowych.","Możesz mi powiedzieć coś o miejscowych?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Twoje uszy cię zwodzą. Muszę iść.","Nie, to nic, jestem w drodze do tawerny."),RandPhraseSimple("No cóż, to nic takiego. Powodzenia!","Po prostu spaceruję po mieście. Do widzenia."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Kto cię interesuje?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Chcę wiedzieć więcej o gubernatorze.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Chcę dowiedzieć się więcej o właścicielu lokalnej tawerny.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Chcę wiedzieć więcej o miejscowym mistrzu stoczni.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Chcesz wiedzieć więcej o właścicielu miejscowego sklepu.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "To nic. Zapomnij o tym.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Dzięki.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nigdy o tym nie słyszałem... Żyję tu od dawna i nigdy czegoś takiego nie widziałem.";
			link.l1 = "Cóż, to jest narzędzie do budowy statków, "+pchar.GenQuest.Device.Shipyarder.Describe+" . Czy ktoś sprzedawał coś takiego w mieście? A może nosił to przy sobie i zauważyłeś?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Tak, widziałem człowieka z tą rzeczą kilka godzin temu. Spacerował ulicami. To było interesujące narzędzie.";
				link.l1 = "Jak wyglądał i dokąd zmierzał? Naprawdę potrzebuję czegoś takiego.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nie, nie widziałem niczego takiego.";
				link.l1 = "Rozumiem. Będę pytać dalej.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Nie, nic o tym nie wiem.","Nie, powinienem iść.","Nie wiem nic.");
					link.l1 = LinkRandPhrase("Dobrze, dziękuję.","Rozumiem, dzięki.","Dobrze, przepraszam.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Nie wiem nic na ten temat, ale możesz spróbować zapytać bywalców w tawernie, oni z pewnością powiedzą ci więcej.","Nie mogę ci nic powiedzieć, zapytaj kogoś w karczmie.");
				link.l1 = "Dzięki za to.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				dialog.text = "Kapitanie, muszę dostać się do kolonii zwanej "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", jak najszybciej, to jest na "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+", w "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Wasz statek wygląda solidnie w porównaniu z większością tych małych łajb pływających tutaj. Mogę wam zapłacić "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+"Co powiesz?";
			}
			else
			{
				dialog.text = "Kapitanie, muszę dostać się do kolonii "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", jest na "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", w "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Wiem, że to brzmi niezwykle ryzykownie, ale może "+FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money))+"byłoby miłym wzmocnieniem dla ciebie?";
			}
			link.l1 = "Hm. Ja również zmierzam w tę stronę, więc jestem gotów zabrać cię na pokład na tych warunkach.";
			link.l1.go = "passenger_1";
			link.l2 = "Przepraszam,  "+GetAddress_FormToNPC(NPChar)+", ale płynę w innym kierunku. Nie mogę ci pomóc.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Szkoda. Cóż, poczekam na inny statek. Żegnaj.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Świetnie, bo jestem zmęczony czekaniem. Dostaniesz swoją zapłatę, gdy tam dotrzemy.";
			link.l1 = "Idź na mój statek, "+GetAddress_FormToNPC(NPChar)+" Wkrótce wypływamy.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "citizen");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Jesteśmy na miejscu, doskonale! Ta podróż na twoim statku była całkiem satysfakcjonująca. Dziękuję. Weź swoje pieniądze, panie.";
			link.l1 = "Powodzenia, "+GetAddress_FormToNPC(NPChar)+"Żegnaj.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Townpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<-- горожанин-пассажир
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jako obywatel tego miasta proszę cię, abyś schował swoją broń.","Słuchaj, jako obywatel tego miasta proszę cię, abyś schował swoją broń.");
				link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy jakiś obcy chodzi przede mną z nagim mieczem...");
				link.l1 = RandPhraseSimple("Zrozumiałem.","Nie martw się.");
			}
			link.l1.go = "exit";
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
