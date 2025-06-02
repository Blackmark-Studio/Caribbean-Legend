//Jason общий диалог мещанок
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
    string sTemp, sCity;
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
				    dialog.text = RandPhraseSimple("Mówią, że to miasto do ciebie należy, "+GetSexPhrase("panie","panna")+".","Co za miłe spotkanie! Co za miłe spotkanie! Sam gubernator rozmawia ze mną!");
					link.l1 = RandPhraseSimple("Zmieniłem zdanie. Powodzenia!","Po prostu spaceruję po mieście. Żegnaj.");
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
				    dialog.text = RandPhraseSimple("Czego chcesz? Ruszaj dalej.","Przestań blokować mi drogę, zjeżdżaj.");
					link.l1 = RandPhraseSimple("Co robisz?","Uspokój się. Albo zrobię to sam.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Chcę cię zapytać.","Chwila uwagi, proszę. Jedno pytanie.");
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
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Jestem"," Nazywam się ","Możesz mnie nazywać ")+GetFullName(npchar)+LinkRandPhrase(" . Czego chcesz?","Nie widziałem cię wcześniej "+", kim jesteś?","Kim jesteś i czego ode mnie chcesz?"),LinkRandPhrase("Pozdrowienia, "+GetAddress_Form(NPChar)+". Nazywam się "+GetFullName(npchar)+"  A jak się nazywasz?","Cześć "+GetAddress_Form(NPChar)+"! Jestem "+GetFullName(npchar)+" Czy mogę poznać twe imię?","Tak, "+GetAddress_Form(NPChar)+". Czego chcesz? A tak przy okazji, nazywam się "+GetFullName(npchar)+" A jak się zwiesz?"));
				Link.l1 = pcharrepphrase(LinkRandPhrase("Do diabła!","Cholera! ","Do diabła z tobą! ")+"Tak, jestem kapitanem "+GetFullName(Pchar)+LinkRandPhrase(", czyżbyś nigdy o mnie nie słyszał, bękarcie?"," i "+GetSexPhrase("najbardziej znany pirat","najsłynniejsza dziewczyna-piratka")+"na morzu!"," i niech mnie diabli wezmą, jeśli się mylę!"),LinkRandPhrase("Jestem "+GetFullName(Pchar)+", kapitanie.","Nazywam się "+GetFullName(Pchar)+".","Możesz mnie nazywać kapitanem "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Całe miasto jest na krawędzi - don Fernando de Alamida, królewski inspektor, przybył. Wiesz, widziałem tu wiele, ale to... To nie żałoba zmienia ludzi, ale jak sobie z nią radzą. Mówią, że stał się innym człowiekiem po śmierci ojca. Teraz nie znajdziesz bardziej nieprzekupnego i... bezlitosnego sługi Korony w całym Archipelagu.","Spójrz tylko na 'Świętą Miłosierdzie'! Mówią, że sam król kazał ją zbudować według specjalnych projektów. I zauważ - ani jednego zadrapania. Jakby sama Maryja Dziewica ją chroniła. Choć słyszałem plotki... może to wcale nie Dziewica.","Wiesz, ile razy próbowali zabić don Fernando? Dwanaście ataków na otwartych wodach - i to tylko w zeszłym roku! Cóż, z tak lojalną i wyszkoloną załogą, i pod ochroną Pana - przetrwa też trzynasty!"),LinkRandPhrase("Słyszałeś? Don Fernando de Alamida przybył do naszego miasta, a mówią, że jest teraz gdzieś na ulicach. Chciałbym go zobaczyć na własne oczy...","Skomplikowany człowiek, ten don Fernando. Niektórzy mówią, że to zbawca, oczyszczający Ojczyznę z plugastwa. Inni szepczą, że coś w nim pękło po śmierci ojca i wkrótce wszyscy będziemy płakać. Ale powiem ci jedno: nie lękaj się jego. Bój się tych, którzy go takim uczynili.","Jaki przystojny mężczyzna, ten don Fernando! Ale wiesz, co jest dziwne? Jakby nikogo nie zauważał. Cały w obowiązkach i służbie. Słyszałam, że była jakaś dziewczyna... ale po spotkaniu z jakimś księdzem całkowicie odrzucił ziemskie przyjemności. Jakby złożył śluby."),RandPhraseSimple(RandPhraseSimple("Przeklęty inspektor! Jak on tu jest - miasto jak martwe. Ani handlu, ani zabawy. Nawet oddychać, zdaje się, trzeba ciszej. A wiesz, co jest najstraszniejsze? Tak samo jest w każdym porcie. Jak w zegarku. Jego Królewska Mość nie mógłby celowo wymyślić tej tortury dla nas wszystkich!","Don Fernando odwiedził znowu sierociniec. Hojnie daruje, modli się godzinami. Taki godny człowiek powinien być przykładem dla tych przeklętych defraudantów!"),RandPhraseSimple("Ha! 'Święty' Fernando znowu zamknął wszystkie burdele. No cóż, nie martw się, wkrótce odpłynie, a one się na nowo otworzą.","Ins... inspektor przyjechał, oto co! Don Fernando de Almeyda, czy jak mu tam, Alamida! Tak ważny, że sam gubernator się przed nim płaszczy. Mówią, że spojrzy ci w oczy i od razu zobaczy wszystkie twoje grzechy. Przerażające!")));
					link.l1 = "...";
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
				link.l1 = "Chciałem tylko porozmawiać o tym mieście.";
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję trochę informacji.");
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
						link.l3 = RandPhraseSimple("Chcę porozmawiać o sprawach finansowych.","O finansach...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Słuchaj, mam nadzieję, że możesz mi pomóc. Chcę kupić "+pchar.GenQuest.Device.Shipyarder.Type+", i powiedziano mi, że ta rzecz została sprzedana w waszym mieście. Cóż, ktoś sprzedawał ją na targu ulicznym. Wiesz coś o tym?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Czy wiesz ","Czy jesteś świadomy ","Słyszałeś ")+"że lokalny kościół został niedawno okradziony?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ach, to ty "+GetFullName(Pchar)+" "+GetSexPhrase(" - stary przyjacielu!"," - ślicznotko!")+"","Cieszę się, że cię widzę, "+GetSexPhrase("stary przyjacielu!","ślicznotko!")+" "+Pchar.name,"O, to jest "+GetSexPhrase("sam kapitan","sama kapitan")+" "+GetFullName(Pchar))+RandPhraseSimple(" Myślałem, że nie żyjesz!",". I być może "+GetSexPhrase("pijany jak zawsze.","trochę pijany."))+LinkRandPhrase(" Kontynuuj, czego potrzebujesz?"," Co tym razem?"," Znowu mnie niepokoisz?"),LinkRandPhrase(TimeGreeting()+", kapitanie ","Dzień dobry, "+GetAddress_Form(NPChar)+" ","Witaj, kapitanie ")+GetFullName(Pchar)+LinkRandPhrase("Jak mogę pomóc "+GetSexPhrase("taki zacny człowiek","taka godna dziewczyna")+", jak ty?"," . Dlaczego tu jesteś?"," Czego chcesz się dowiedzieć tym razem?")),PCharRepPhrase(LinkRandPhrase("Witaj, kapitanie ","Pozdrowienia, ach, to ty "+GetAddress_Form(NPChar)+" ","Ah, kapitanie ")+GetFullName(Pchar)+LinkRandPhrase(", myślałem, że nigdy się już nie spotkamy, i",", nie powiem, że cieszę się na twój widok, ale",", Widzę, że nadal żyjesz, co za wstyd i")+LinkRandPhrase(" czego chcesz?"," dlaczego tu jesteś?"," jak mogę ci pomóc?"),LinkRandPhrase(TimeGreeting()+", kapitanie "+GetFullName(Pchar)+"Jak mogę ci pomóc?","O, to kapitan "+GetFullName(Pchar)+"! Jak mogę ci pomóc?","Pozdrowienia, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+" . Czy chcesz czegoś?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Twoje uszy cię zwodzą. Muszę iść.","Nie, to nic, byłem w drodze do tawerny."),RandPhraseSimple("Niech będzie, cokolwiek. Powodzenia!","Po prostu spaceruję po mieście. Żegnaj."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Pytania?";
			link.l1 = "Czy nazwa na tych papierach coś dla ciebie znaczy?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Nie obchodzi mnie jakiś nieznany papier i nie umiem czytać. Idź do lichwiarza, mówią, że on potrafi czytać te diabelskie litery.","Nie wiem, o czym mówisz, zapytaj innych mieszkańców miasta, kapitanie"+GetFullName(Pchar)+".","Nie wiem nawet, jak ci pomóc, kapitanie "+GetFullName(Pchar)+"Spróbuj porozmawiać z lichwiarzem, może coś wie.");
			link.l1 = "Z wielką przyjemnością posłucham twojej rady!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Nie kłamiesz czasem, kapitanie "+GetFullName(Pchar)+"?","A co z tego"+PChar.name+"?","Zapamiętam cię, "+GetFullName(Pchar)+".")+" Teraz powiedz mi, czego chcesz?",LinkRandPhrase("Miło cię poznać, kapitanie "+PChar.name,"Rad, że się spotkaliśmy,"+GetAddress_Form(NPChar)+" "+PChar.lastname,"To przyjemność, kapitanie "+PChar.name)+" Ale wątpię, że chciałeś tylko poznać moje imię, prawda?");
            link.l1 = PCharRepPhrase("Chciałbym tylko zapytać o coś związanego z tą dziurą, którą nazywacie 'miastem'.","Chcę zapytać cię o coś związanego z tym miastem.");
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
   				link.l16 = "Słuchaj, mam nadzieję, że możesz mi pomóc. Chcę kupić "+pchar.GenQuest.Device.Shipyarder.Type+" i powiedziano mi, że ta rzecz została sprzedana w waszym mieście. Cóż, ktoś sprzedawał ją na ulicach. Czy wiesz coś na ten temat?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор

			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = RandPhraseSimple("Czy wiesz ","Czy zdajesz sobie sprawę ","Słyszałeś ")+" że lokalny kościół został ostatnio okradziony?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Twoje uszy cię zwodzą. Muszę iść.","Nie, to nic, byłem w drodze do tawerny."),RandPhraseSimple("Cóż, to nic. Powodzenia!","Po prostu spaceruję po mieście. Do widzenia."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("O, i cieszę się, że cię widzę, jak cieszę się z gorzałki, pytaj o co chcesz.","Lubisz rozmowy, kapitanie? Ja też... Zwłaszcza przy kubku rumu.","Tak, "+PChar.name+"?"),RandPhraseSimple("Czego jeszcze chcesz?","Tak sądzę, kapitanie "+PChar.name+", że lubisz pogawędki?")),PCharRepPhrase(LinkRandPhrase("Czego jeszcze chcesz "+GetAddress_Form(NPChar)+"?","Słucham, kapitanie.","Muszę iść, więc pytaj szybko, kapitanie."),LinkRandPhrase("Zawsze cieszę się z miłego towarzystwa, "+GetAddress_Form(NPChar)+" "+PChar.lastname+" Mów.","Tak, "+GetAddress_Form(NPChar)+"?","Lubisz rozmawiać, kapitanie? Ja też... ")));
			link.l1 = LinkRandPhrase("Jakie plotki krążą po tym mieście?","Jakieś wieści z tych stron?","Jak tam życie na lądzie?");
			link.l1.go = "rumours_towngirl";
			link.l2 = LinkRandPhrase("Możesz mi pokazać drogę?","Nie mogę znaleźć drogi do jednego miejsca...","Pomóż mi dotrzeć do jednego miejsca...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Chcę wiedzieć, co ludzie mówią o pewnej osobie.","Czy wiesz, co ludzie mówią o jednej osobie?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Chcę dowiedzieć się więcej o miejscowych.","Czy możesz mi powiedzieć coś o miejscowych?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Twoje uszy cię zwodzą. Muszę iść.","Nie, to nic, byłem w drodze do tawerny."),RandPhraseSimple("Cóż, to nic. Powodzenia!","Po prostu spaceruję po mieście. Żegnaj."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Kim jesteś zainteresowany?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Chcę wiedzieć więcej o gubernatorze.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Chcesz wiedzieć więcej o właścicielu miejscowej tawerny.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Chcesz wiedzieć więcej o miejscowym mistrzu stoczni?";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Chcę wiedzieć więcej o właścicielu lokalnego sklepu.";
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
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nigdy o tym nie słyszałem... Mieszkam tu już od dawna i nigdy czegoś takiego nie widziałem.";
			link.l1 = "Cóż, to jest narzędzie do budowy statków, "+pchar.GenQuest.Device.Shipyarder.Describe+"Czy ktoś sprzedawał coś takiego w mieście? A może ktoś to nosił, a ty zauważyłeś?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Tak, widziałem człowieka z tym przedmiotem kilka godzin temu. Spacerował ulicami. To było interesujące narzędzie.";
				link.l1 = "Jak wyglądał i dokąd zmierzał? Naprawdę potrzebuję czegoś takiego.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nie, nie widziałem nic podobnego.";
				link.l1 = "Rozumiem. W takim razie będę dalej pytał.";
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
				dialog.text = RandPhraseSimple("Nie wiem nic na ten temat, ale możesz spróbować zapytać stałych bywalców w tawernie, z pewnością powiedzą ci więcej.","Nie mogę ci nic powiedzieć, zapytaj kogoś w tawernie.");
				link.l1 = "Dzięki za to.";
				link.l1.go = "exit";
			}
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jako obywatel tego miasta proszę cię, byś schował swój miecz.","Słuchaj, jako obywatel tego miasta proszę cię, abyś schował szablę.");
				link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, biegnąc z bronią. Mogę się zdenerwować...","Nie lubię, gdy jakiś nieznajomy chodzi przede mną z dobytym orężem. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Zrozumiałem.","Nie martw się.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
