// boal 25/04/04 общий диалог горожан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
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
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
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
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Szpieg? Strażnicy!","Alarm! Jest intruz!");
				link.l1 = "Zamknij się. Wychodzę.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Mówią, że to ty rządzisz tym miastem, "+GetSexPhrase("panie","panno")+".","Jakie przyjemne spotkanie, szef miasta zwrócił się do mnie z pytaniem.");
					link.l1 = RandPhraseSimple("Zmieniłem zdanie.","Po prostu zwiedzam to miasto. Do widzenia.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Chcę omówić interesy.","W sprawie finansów...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("Co chcesz? Idź dalej.","Nie stój na drodze, znikaj!");
					link.l1 = RandPhraseSimple("Hej, przestań szczekać, dobrze?","Uspokój się, bo możesz tego pożałować!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Chwila twojej uwagi, proszę. Mam pytanie.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Chcę porozmawiać o interesach.","Odnośnie finansów...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Mam na imię ","Mam na imię ","Możesz mi mówić ")+GetFullName(npchar)+LinkRandPhrase(". Czego potrzebujesz?",". Nie mam "+NPCharSexPhrase(NPChar,"widziałem cię tu wcześniej","widziałem cię tam wcześniej")+", kim jesteś?",". Kim jesteś i czego ode mnie potrzebujesz?"),LinkRandPhrase("Pozdrowienia, "+GetAddress_Form(NPChar)+". Nazywam się "+GetFullName(npchar)+". A twój?","Witaj, "+GetAddress_Form(NPChar)+"! Jestem "+GetFullName(npchar)+". Czy mogę znać twoje imię?","Tak, "+GetAddress_Form(NPChar)+". Co chcesz? A tak przy okazji, moje imię to "+GetFullName(npchar)+". A ty kim jesteś?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Na gromy!","Do diabła!","Niech cię cholera weźmie!")+"Tak, jestem Kapitanem "+GetFullName(Pchar)+LinkRandPhrase(", naprawdę o mnie nie słyszałeś"+NPCharSexPhrase(NPChar,", łotrzyku?","?")," i "+GetSexPhrase("najbardziej notoryczny pirat","najbardziej notoryczna dama-pirat")+" w tych wodach! "," i niechaj spłonę w piekle, jeśli to nie prawda!"),LinkRandPhrase("Jestem kapitanem"+GetFullName(Pchar)+".","Mam na imię "+GetFullName(Pchar)+".","Możesz nazywać mnie Kapitanem "+GetFullName(Pchar)));

                //LinkRandPhrase("I am Captain" + GetFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) + ".", "You may call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Kapitanie, czy mógłbyś mi pomóc?";
					link.l1 = LinkRandPhrase("Przepraszam, nie. Mam mało wolnego czasu.","Przykro mi, nie mogę. Zbyt zajęty.","Nie, nie mogę. Mam pilne sprawy, które wymagają mojej uwagi.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Oczywiście, że mogę. Jaki jest problem?","Tak, pomogę ci. Opowiedz mi więcej o swoim interesie.","Opowiedz mi więcej o swoim interesie...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Tak, Kapitanie, słucham.";
					link.l1 = NPChar.name+", znalazłem twój pierścionek ślubny.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("Chcę dowiedzieć się więcej o tym mieście.","Opowiedz mi o tym mieście.");
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
						link.l3 = RandPhraseSimple("Chcę omówić interesy.","Jeśli chodzi o finanse...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Zaczekaj! Powiedz mi kim jesteś - natychmiast! Szukam szpiega wroga na prośbę gubernatora "+XI_ConvertString("Kolonia"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Stój! Działam w interesie miasta "+XI_ConvertString("Kolonia"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" na rozkaz gubernatora. Szukam w mieście wroga agenta.","Zatrzymaj się, przyjacielu! Lokalny gubernator "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" chce znaleźć szpiega w mieście."),LinkRandPhrase("Zaczekaj, damo! Powiedz mi kim jesteś - natychmiast! Szukam szpiega wroga na prośbę gubernatora "+XI_ConvertString("Colonia"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Kobieta, muszę cię zatrzymać! Działam w interesie miasta "+XI_ConvertString("Colonia"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" na rozkaz gubernatora. Przeszukuję miasto w poszukiwaniu wrogiego agenta","Stój nieruchomo, piękno! Lokalny gubernator "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" chce znaleźć szpiega w mieście..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Może możesz mi dać jakąś radę. Chcę kupić "+pchar.GenQuest.Device.Shipyarder.Type+", a dowiedziałem się, że sprzedawano to w twoim mieście. No, ktoś to sprzedawał na ulicach. Czy wiesz coś o tym?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Czy jesteś świadomy","Czy wiedziałeś","Słyszałeś")+" że miejscowy kościół został ostatnio napadnięty?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("O, to ty, "+GetFullName(Pchar)+" "+GetSexPhrase(", stary łajdaku","- pani cwaniaczka")+"","Dobrze cię znowu widzieć, "+GetSexPhrase("stary kolego","piękno")+" "+Pchar.name,"Oh, to dobry stary "+GetSexPhrase("Kapitan","pani")+" "+GetFullName(Pchar))+LinkRandPhrase(". Myślałem, że nie żyjesz!",". I na pewno, "+GetSexPhrase("pijany jak zwykle.","już pod wpływem pogody.")+"",". I widzę, że jesteś nadal na wolności!")+LinkRandPhrase("No więc, mów co myślisz - czego potrzebujesz?","Co tym razem potrzebujesz?","Znowu męczysz mnie na próżno?"),LinkRandPhrase(TimeGreeting()+", Kapitan ","Witaj, "+GetAddress_Form(NPChar)+" ","Witam cię, Kapitanie ")+GetFullName(Pchar)+LinkRandPhrase(". Co by mogło "+GetSexPhrase("taki galantny dżentelmen","tak urocza dama")+", jak? Czy mogłbyś czegoś potrzebować ode mnie?",". Po co przyszedłeś?",". Co chcesz wiedzieć tym razem?")),PCharRepPhrase(LinkRandPhrase("Witaj, Kapitanie ","Witaj. O, to ty "+GetAddress_Form(NPChar)+" ","Oh, Kapitanie ")+GetFullName(Pchar)+LinkRandPhrase(", myślałem"+NPCharSexPhrase(NPChar," "," ")+"nigdy więcej się nie spotkamy,",", nie mogę powiedzieć, że mi miło"+NPCharSexPhrase(NPChar," "," ")+"widzieć cię, ale",", Widzę, że jeszcze żyjesz. Żałosne. Więc,")+LinkRandPhrase(" czego potrzebujesz?","Po co przyszedłeś?"," co mogę "+NPCharSexPhrase(NPChar,"pomóc ci czymś?","pomóc ci w czymś?")),LinkRandPhrase(TimeGreeting()+", Kapitan "+GetFullName(Pchar)+". Czym mogę ci pomóc?","O, jeśli to nie jest"+GetSexPhrase("","")+" Kapitan "+GetFullName(Pchar)+"! Co chciałbyś wiedzieć tym razem?","Witaj, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Czy chciałeś coś?")));                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Nie, coś ci się wydaje. Teraz muszę iść.","Nie, nic - właśnie szedłem"+GetSexPhrase("","")+" do tawerny."),RandPhraseSimple("Nie, nic. Powodzenia!","Tylko się rozglądam. Do widzenia."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Jakie pytania?";
			link.l1 = "Czy nazwa w tych papierach coś ci mówi?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Nie obchodzą mnie obce papiery. Poza tym nie umiem czytać. Idź do lichwiarza, ten diabeł na pewno umie czytać i pisać.","Nie mam pojęcia, o czym mówisz. Zapytaj mieszkańców miasta, Kapitanie "+GetFullName(Pchar)+".","Naprawdę nie mam pojęcia, jak ci pomóc, Kapitanie "+GetFullName(Pchar)+". Spróbuj zapytać lichwiarza - być może, on może coś wiedzieć.");
			link.l1 = "Chętnie posłucham Twojej rady!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Ale czy nie kłamiesz, Kapitanie "+GetFullName(Pchar)+"?","I cóż z tego, "+PChar.name+"?","Pamiętam o tobie, "+GetFullName(Pchar)+".")+"I teraz, czego potrzebujesz?",LinkRandPhrase("Miło cię poznać, Kapitanie "+PChar.name,"Cieszę się"+NPCharSexPhrase(NPChar," "," ")+", spotkać cię, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Miło cię poznać, Kapitanie "+PChar.name)+". Ale rozumiem, przyszedłeś tutaj nie tylko po to, żeby dowiedzieć się mojego imienia?");

            link.l1 = PCharRepPhrase("Chciałem"+GetSexPhrase("","")+" aby coś wiedzieć o tej dziurze, którą nazywasz miastem!","Chciałem"+GetSexPhrase("","")+" wiedzieć coś o tym mieście.");
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
					link.l3 = RandPhraseSimple("Chcę omówić biznes.","Odnośnie finansów...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Może możesz mi dać jakąś radę. Chcę kupić "+pchar.GenQuest.Device.Shipyarder.Type+", a powiedziano mi, że sprzedawano to w twoim mieście. No, ktoś sprzedawał to na ulicach. Czy coś o tym wiesz?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Stój! Powiedz mi kim jesteś - natychmiast! Szukam szpiega wroga na prośbę gubernatora "+XI_ConvertString("Colonia"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Stój! Działam w interesie"+XI_ConvertString("Colonia"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"na rozkaz gubernatora. Szukam po mieście wrogiego agenta.","Stój, przyjacielu! Miejscowy gubernator "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" chce znaleźć szpiega w mieście."),LinkRandPhrase("Czekaj, damo! Powiedz mi kim jesteś - natychmiast! Szukam wroga szpiega na prośbę gubernatora "+XI_ConvertString("Kolonia"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Kobieta, muszę cię zatrzymać! Działam w interesie miasta "+XI_ConvertString("Kolonia"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" na rozkaz gubernatora. Szukam w mieście wrogiego agenta.","Stój, piękna kobieta! Lokalny gubernator "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" chce poszukać szpiega w mieście..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Czy jesteś świadomy","Słyszałeś","Słyszałeś")+"że miejscowy kościół został niedawno napadnięty?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Nie, słyszysz rzeczy. Teraz pójdę.","Nie, nic - właśnie szedłem do karczmy."),RandPhraseSimple("Nie, nic. Powodzenia!","Tylko się rozglądam. Do widzenia."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("O tak, jestem prawie tak szczęśliwy"+NPCharSexPhrase(NPChar," "," ")+" aby widzieć cię jako kufel gorzałki. Pytaj o co chcesz.","Lubisz rozmawiać, Kapitanie? Cóż, ja także... Szczególnie przy kubku rumu.","Tak, "+PChar.name+"?"),LinkRandPhrase("Czego potrzebujesz?","Rozumiem, Kapitanie "+PChar.name+". Jesteś"+GetSexPhrase("","")+" całkiem gadał. ","Zmęczyłeś mnie"+GetSexPhrase("","")+" ze swoimi pytaniami, Kapitanie. Lepiej pomóż mi z rumem.")),PCharRepPhrase(LinkRandPhrase("Co chcesz wiedzieć "+GetAddress_Form(NPChar)+"?","Słucham cię, Kapitanie.","Muszę iść, więc proszę, bądź szybki, Kapitanie."),LinkRandPhrase("Zawsze zadowolony"+NPCharSexPhrase(NPChar," "," ")+"  mieć dobrą kompanię, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Mów, co myślisz.","Tak, "+GetAddress_Form(NPChar)+"?","Lubisz gawędzić, Kapitanie? No cóż, ja też...")));

            // homo 25/06/06
			link.l1 = LinkRandPhrase("Jakie plotki krążą w lokalnej tawernie?","Co się dzieje w tych stronach?","Co nowego na lądzie tutaj?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("Czy możesz mnie tam skierować?","Nie mogę znaleźć drogi do pewnego miejsca...","Czy mógłbyś pokazać drogę...?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("Chcę wiedzieć, co ludzie mówią o pewnej osobie.","Czy nie wiesz, co ludzie mówią o pewnej osobie?","Chciałbym dowiedzieć się czegoś o miejscowych.");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = "Proszę, opowiedz mi więcej o swojej kolonii.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("Mam ważne sprawy!","Mam z tobą interesy.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("Nie, coś ci się wydaje. Teraz muszę iść.","Nie, nic - właśnie szedłem do tawerny."),RandPhraseSimple("Nie, nic. Powodzenia dla ciebie!","Tylko się rozglądam. Do widzenia."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "O kim chciałbyś wiedzieć?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "O gubernatorze.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "O właścicielu miejscowej karczmy.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "O nadzorcy portu.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "O właścicielu lokalnego sklepu.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Nie przejmuj się, zapomnij o tym.";
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
		
		case "colony":
			dialog.text = LinkRandPhrase("Szczerze mówiąc, nie wiem o tym wiele, ale mogę ci powiedzieć jedną czy dwie rzeczy.","I co cię interesuje w naszej kolonii?","Pewnie. Co chciałbyś wiedzieć?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "Jakie to jest miasto?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "Co wiesz o forcie broniącym miasta?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Zmieńmy temat.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "Czy żartujesz? Czy to żart? Spójrz w prawy róg swojego ekranu.";
			link.l1 = "Tak, moja wina.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "Nie wiem o tym nic.";
			link.l1 = "Szkoda.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nigdy o tym nie słyszałem... Co to właściwie jest? Nigdy o czymś takim nie słyszałem przez cały mój czas"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Cóż, to narzędzie stoczniowe, "+pchar.GenQuest.Device.Shipyarder.Describe+". Czy ktokolwiek sprzedawał coś takiego w mieście? Może. Zauważyłeś, że ktoś miał coś takiego przy sobie?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hmm... Tak, chyba widziałem osobę z podobnym urządzeniem. Chodził tam z tym kilka godzin temu. Ciekawe urządzenie, z pewnością.";
				link.l1 = "A jak on wyglądał i gdzie poszedł? Bardzo potrzebuję tego instrumentu.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nie, nie widziałem czegoś takiego.";
				link.l1 = "Rozumiem. Cóż - czas zapytać dookoła!";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"A co to ma do mnie? Ja jestem miejscowy!","Cóż, dlaczego zawracasz mi głowę tym? Mieszkam w tym mieście i nic o takich rzeczach nie wiem!"),NPCharSexPhrase(npchar,"Co znowu ode mnie chcesz? Czy nie mówiłem ci już, że nie jestem szpiegiem?!","Nie mówiłem ci już, że jestem stąd?!"),NPCharSexPhrase(npchar,"Mój drogi, to znowu ty! Zostaw mnie w spokoju - jestem miejscowy!","Dlaczego znowu dokuczysz mi swoimi głupimi pytaniami?"),NPCharSexPhrase(npchar,"Znowu! To już jest skandal!","Słuchaj, po prostu zostaw mnie w spokoju, dobrze? Proszę!"),"blokada",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Kto może potwierdzić twoje oświadczenie?","Och, przepraszam - już cię pytałem...","Przepraszam, jest tak wiele osób...","Dobrze, dobrze...",npchar,Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "Każdy może! Posłuchaj, dlaczego ciągle mnie dręczysz?! Jeśli masz problem, idź do gubernatora i wszystko załatwij!",link.l1 ="Hmm... To prawdopodobnie najlepiej nie przeszkadzać mu z taką drobnostką. Wierzę ci.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Każdy w tym mieście! "+NPCharSexPhrase(npchar,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])+" może to zrobić, na przykład, teraz kiedy "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],"on","ona")+" stoi właśnie tam.","Ach, Panie, no, na przykład, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]))+" mogę to zrobić.");				
			link.l1 = "Dobrze, zobaczmy, więc.";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "Tak, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]," rzeczywiście jest miejscowy.","ona rzeczywiście jest miejscową.");
			link.l1 = RandPhraseSimple("Widzę"+GetSexPhrase("","")+". Dziękuję za pomoc.","Wszystko jasne. Dziękuję za pomoc.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "Widzisz, wczoraj byłem poza miastem, spacerowałem i zgubiłem mój pierścionek ślubny... "+GetSexPhrase("Kapitanie, czy mógłbyś to proszę poszukać?","Pani, proszę, pomóż mi to znaleźć!")+"";
			link.l1 = "Oczywiście "+GetSexPhrase("Mogę! Dla takiej pięknej dziewczyny jak ty, mogę zrobić wszystko!","Pomogę ci. Kościół uczy nas pomagać potrzebującym.")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("Nie, nie mogę. Przykro mi. Mam zbyt wiele do zrobienia.","Przykro mi, nie mogę. Właśnie sobie przypomniałem"+GetSexPhrase("","")+", że mam jeszcze nieukończone sprawy...","Nie mam zbyt wiele czasu, więc nie mogę ci z niczym pomóc...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Kapitan","Pani")+", to naprawdę wspaniale! Proszę, znajdź ten pierścień dla mnie, mój mąż przyjeżdża za chwilę "+sti(NPChar.LifeDay)+" dni, i nie chciałbym, aby widział mnie bez mojego pierścionka ślubnego.";
			link.l1 = RandPhraseSimple("Gdzie to zgubiłeś, mówisz?","Właściwie gdzie to zgubiłeś?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "Prawo za bramami miasta...";
			link.l1 = "No cóż, w takim razie wybieram się na poszukiwania...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "Tak, proszę to zrobić. I pospiesz się - pamiętaj, że masz tylko "+sti(NPChar.LifeDay)+" dni.";
			link.l1 = "Pamiętam.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("The ring shall be in the locator - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+GetSexPhrase("Kapitan","młoda dama")+"! Jestem taki szczęśliwy! Jak mogę Ci podziękować?";
			link.l1 = "Och, nie ma potrzeby dziękować - zrobiłem to całkiem bezinteresownie.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "Kilka setek pesos na pewno by nie zaszkodziło...";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "Oh, "+GetSexPhrase("Kapitanie, jesteś taką szlachetną osobą","pani, jesteś tak szlachetna")+"! Na pewno pomodlę się za ciebie w kościele! Do widzenia...";
			link.l1 = "Żegnaj, "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "O, ale oczywiście. Proszę -"+FindRussianMoneyString(iTemp)+". To wszystko, co mam. Proszę, weź te pieniądze... I żegnaj.";
			link.l1 = "Do widzenia, "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Nie, nic o tym nie wiem.","Nie wiem nic na ten temat.","Nic nie wiem.");
					link.l1 = LinkRandPhrase("Dobrze, dzięki.","Rozumiem, dzięki.","Dobrze, wybacz mi proszę.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Nie wiem nic na ten temat, ale możesz zapytać gości w karczmie - na pewno ci coś opowiedzą.","Nie mogę ci nic powiedzieć. Zapytaj w karczmie.","Nie wiem nic konkretnego, ale słyszałem, że były plotki w karczmie.");
				link.l1 = "Cóż, to przynajmniej coś.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj - jako obywatel tego miasta, muszę cię prosić, abyś powstrzymał się od chodzenia z nieskutą bronią.","Słuchaj - jako obywatel tego miasta, muszę cię prosić, abyś powstrzymał się od chodzenia z niewłożonym mieczem.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Powstrzymaj swoje konie "+GetSexPhrase("kumpel","dziewczyno")+" gdy biegasz z bronią w ręku. To mnie denerwuje...","Nie podoba mi się, kiedy "+GetSexPhrase("mężczyźni","ktokolwiek")+" chodź z gotowymi do walki bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Rozumiem.","Schowam to.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
