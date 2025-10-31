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
				dialog.text = RandPhraseSimple("Kém? Ôrség!", "Riadó! Betolakodó van itt!");
				link.l1 = "Pofa be! Elmegyek.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Azt mondják, hogy te vagy az, aki uralja ezt a várost, "+ GetSexPhrase("uram","kisasszony") +".", "Micsoda kellemes találkozás, a város vezetôje egy kérdéssel fordult hozzám.");
					link.l1 = RandPhraseSimple("Meggondoltam magam.", "Egyszerûen csak felfedezem ezt a várost. Viszontlátásra.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Lenne egy kérdésem önhöz.", "Információra van szükségem.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Az üzletrôl szeretnék beszélni.", "A pénzügyek tekintetében...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("Mit akarsz? Menj tovább.", "Ne állj az utamba, tûnj el!");
					link.l1 = RandPhraseSimple("Hé, hagyd abba az ugatást, jó?", "Nyugodj meg, vagy még megbánod!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Lenne egy kérdésem önhöz.", "Egy pillanatnyi figyelmet kérek. Lenne egy kérdésem.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Az üzletrôl szeretnék beszélni.", "A pénzügyek tekintetében...");
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
				dialog.Text =NPCharRepPhrase(npchar,
                                LinkRandPhrase("A nevem ", "A nevem ", "Hívhatsz ")
                                +GetFullName(npchar)
                                +LinkRandPhrase(". Mire van szüksége?", ". Nem láttam még "
                                +NPCharSexPhrase(NPChar, "itt", "láttam már ott")
                                +", ki vagy te?", ". Ki vagy te és mit akarsz tôlem?"),

        		                LinkRandPhrase("Üdvözletem, " + GetAddress_Form(NPChar) + ". A nevem " + GetFullName(npchar) + ". És a tiéd?",
                                 "Helló, " + GetAddress_Form(NPChar) + "! A nevem " + GetFullName(npchar) + ". Megmondanád a neved?",
                                 "Igen, " + GetAddress_Form(NPChar) + ". Mit szeretnél? Egyébként a nevem " + GetFullName(npchar) + ". És maga?"));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase("A mennydörgés! ", "A pokol harangjai! ", "Bad cess to you! ") + "Igen, én vagyok a kapitány "+ GetFullName(Pchar)+ LinkRandPhrase(", tényleg nem hallottál még rólam"+NPCharSexPhrase(NPChar,", gazember?","?"), " és "+ GetSexPhrase("a leghírhedtebb kalóz","a leghírhedtebb kalózhölgy") +" ezeken a vizeken! ", " és égjek a pokolban, ha ez nem igaz!"),
                                LinkRandPhrase("én vagyok a kapitány" + GetFullName(Pchar) + ".", "nevem " + GetFullName(Pchar) + ".", "Hívhatsz Kapitánynak. " + GetFullName(Pchar)));

                //LinkRandPhrase("Kapitány vagyok" + GetFullName(Pchar) + ".", "nevem " + GetFullName(Pchar) + ".", "Hívhatsz Kapitánynak. " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Kapitány, segítene nekem, kérem?";
					link.l1 = LinkRandPhrase("Sajnálom, nem. Kevés szabadidôm van.", "Sajnálom, nem tudok. Túl elfoglalt vagyok.", "Nem, nem tudok. Sürgôs ügyeim vannak, amelyek a figyelmemet igénylik.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Persze, hogy tudok. Mi a probléma?", "Igen, segítek. Mesélj még az üzletedrôl.", "Meséljen többet arról az üzletérôl...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Igen, kapitány, hallgatom.";
					link.l1 = NPChar.name + ", Megtaláltam a jegygyûrûdet.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("Többet szeretnék megtudni errôl a városról.", "Mesélj nekem errôl a városról.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Lenne egy kérdésem önhöz.", "Információra van szükségem.");
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
						link.l3 = RandPhraseSimple("Az üzletrôl szeretnék beszélni.", "A pénzügyek tekintetében...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("Várjatok! Mondd el, ki vagy - most azonnal! Egy ellenséges kémet keresek a " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "kormányzójának kérésére !", 
						"Állj! A város érdekében " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " a kormányzó megbízásából dolgozom. Egy ellenséges ügynök után kutatok a városban.", 
						"Állj, barátom! A helyi kormányzó " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " egy kémet akar találni a városban."), 
						LinkRandPhrase("Várjon, hölgyem! Mondja el, ki maga - most azonnal! Egy ellenséges kémet keresek a " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "kormányzó kérésére !", 
						"Asszony, le kell tartóztatnom! A város " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " érdekében tevékenykedem a kormányzó megbízásából. Egy ellenséges ügynök után kutatok a városban", 
						"Állj meg, szépségem! A helyi kormányzó " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " egy kémet akar találni a városban..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Talán tudsz nekem tanácsot adni. Szeretnék vásárolni "+pchar.GenQuest.Device.Shipyarder.Type+", és azt mondták, hogy az önök városában árulják. Nos, valaki az utcán árulta. Tud errôl valamit?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Tudtad", "Tudtad", "Hallottad") + " , hogy nemrég razziát tartottak egy helyi templomban?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Ó, te vagy az, "+GetFullName(Pchar)
                        +" "+ GetSexPhrase(", vén csirkefogó","- dögös hölgy") +"", "Jó újra látni téged, "+ GetSexPhrase("öreg fickó","szépség") +" "
                        + Pchar.name, "Ó, a jó öreg "+ GetSexPhrase("kapitány","hölgy") +" "
                         +GetFullName(Pchar))
                                        +LinkRandPhrase(". Azt hittem, hogy meghaltál!", ". És bizonyára "+ GetSexPhrase("részeg, mint mindig.","máris rosszul van.") +"", ". És, ahogy látom, még mindig szabadlábon!")
                                        +LinkRandPhrase(" Szóval, mondd el a véleményed - mire van szükséged?", " Ezúttal mire van szükséged?", " Már megint a semmiért zaklatsz?"),
                                        LinkRandPhrase(TimeGreeting() + ", kapitány ", "Helló, "+GetAddress_Form(NPChar)+" ", "üdvözlöm, kapitány ")+GetFullName(Pchar)
                                        +LinkRandPhrase(". Mit is "+ GetSexPhrase("egy ilyen gáláns úriember","egy ilyen daliás hölgy") +", mint? Szüksége lehet valamire tôlem?", ". Miért jöttél?", ". Ezúttal mit akarsz tudni?")

                                        ),
                                        
                        PCharRepPhrase(LinkRandPhrase("Helló, kapitány ", "Helló. Ó, te vagy az "+GetAddress_Form(NPChar)+" ", "Ó, kapitány ")
                                        +GetFullName(Pchar)
                                        +LinkRandPhrase(", azt hittem"+NPCharSexPhrase(NPChar, " ", " ")+", hogy soha többé nem találkozunk,",
                                                         ", nem mondhatom, hogy örülök"+NPCharSexPhrase(NPChar, " ", " ")+", hogy látlak, de", ", látom, még élsz. Sajnálatos. Szóval,")
                                        +LinkRandPhrase(" mire van szükséged?", " miért jöttél?", " miben tudok "+NPCharSexPhrase(NPChar, "segíteni?", "segíthetek?")),
                                        LinkRandPhrase(TimeGreeting() + ", kapitány " + GetFullName(Pchar) + ". Miben segíthetek?",
                                        "Ó, csak nem"+ GetSexPhrase("","") +" kapitány " + GetFullName(Pchar) + "! Ezúttal mit szeretne tudni?",
                                        "Hello, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". Kértél valamit?"))
                                        );                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Nem, te hallasz dolgokat. Most már megyek.", "Nem, semmi - én csak a"+ GetSexPhrase("","") +" kocsmába indultam."),
                                        RandPhraseSimple("Nem, semmi. Sok szerencsét neked!", "Csak körülnézek. Viszontlátásra."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Milyen kérdések?";
			link.l1 = "Ismerôs a név ezekben az újságokban?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Nem érdekelnek az ismeretlen papírok. Különben sem tudok olvasni. Menj az uzsoráshoz, az az ördög biztosan tud írni-olvasni.",
										"Fogalmam sincs, mirôl beszélsz. Kérdezôsködjön a városlakóknál, kapitány " + GetFullName(Pchar) + ".", 
										"Tényleg nincs ötletem, hogyan segíthetnék, kapitány " + GetFullName(Pchar) + ". Próbálja megkérdezni az uzsorást - talán ô tudja.");
			link.l1 = "Örömmel követem a tanácsát!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("De nem hazudik, kapitány " + GetFullName(Pchar)+"?",
                                                                    "És akkor mi van, " + PChar.name+"?",
                                                                    "Emlékezni fogok rád, " + GetFullName(Pchar)+".")
                                                                     + "És most mi az, amire szükséged van?",
                                                    LinkRandPhrase("Örvendek, kapitány " + PChar.name,
                                                                    "Örülök,"+NPCharSexPhrase(NPChar, " ", " ")+" hogy megismerhetem, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "Örvendek, kapitány " + PChar.name) + ". De gondolom, nem csak azért jött ide, hogy megtudja a nevemet?");

            link.l1 = PCharRepPhrase("Szerettem volna"+ GetSexPhrase("","") +" tudni valamit errôl a lyukról, amit ti városnak hívtok!", "akartam"+ GetSexPhrase("","") +" tudni valamit errôl a városról.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Lenne egy kérdésem önhöz.", "Információra van szükségem.");
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
					link.l3 = RandPhraseSimple("Az üzletrôl szeretnék beszélni.", "A pénzügyek tekintetében...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Talán tudsz nekem tanácsot adni. Szeretnék vásárolni "+pchar.GenQuest.Device.Shipyarder.Type+", és azt mondták, hogy az önök városában árulják. Nos, valaki az utcán árulta. Tud errôl valamit?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("Várjatok! Mondd el, ki vagy - most azonnal! Egy ellenséges kémet keresek a " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "kormányzójának kérésére !", 
					"Állj! A" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " érdekében dolgozom a kormányzó megbízásából. Egy ellenséges ügynök után kutatok a városban.", 
					"Állj, barátom! A helyi kormányzó " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " egy kémet akar találni a városban."), 
					LinkRandPhrase("Várjon, hölgyem! Mondja el, ki maga - most azonnal! Egy ellenséges kémet keresek " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "kormányzó kérésére !", 
					"Asszony, le kell tartóztatnom! A város " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " érdekében tevékenykedem a kormányzó megbízásából. Egy ellenséges ügynök után kutatok a városban.", 
					"Álljon fel, gyönyörû nô! A helyi kormányzó " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " egy kémet akar felkutatni a városban..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Tudja", "Hallotta", "Hallotta") + " , hogy nemrég razziát tartottak egy helyi templomban?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Nem, te hallasz dolgokat. Most már megyek.", "Nem, semmi - csak a kocsmába indultam."),
                                        RandPhraseSimple("Nem, semmi. Sok szerencsét neked!", "Csak körülnézek. Viszontlátásra."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Ó, igen, majdnem annyira örülök"+NPCharSexPhrase(NPChar, " ", " ")+" , hogy látlak, mint egy pohár piának. Kérdezz, amit csak akarsz.", "Szeret beszélgetni, kapitány? Nos, én is... Fôleg egy csésze rum mellett.", "Igen, " + PChar.name + "?"),
                                        LinkRandPhrase("Mire van szüksége?", "Értem, kapitány "+PChar.name+". Ön"+ GetSexPhrase("","") +" elég beszédes. ", "Elfárasztott"+ GetSexPhrase("","") +" a kérdéseivel, kapitány. Jobb, ha segít nekem a rummal.")),
		                PCharRepPhrase(LinkRandPhrase("Mit akar tudni "+ GetAddress_Form(NPChar) + "?", "Hallgatom magát, kapitány.", "Mennem kell, úgyhogy kérem, siessen, kapitány úr."),
                                        LinkRandPhrase("Mindig örülök"+NPCharSexPhrase(NPChar, " ", " ")+"  a jó társaságnak, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Beszélj a véleményedrôl.",
                                                        "Igen, " + GetAddress_Form(NPChar) + "?",
                                                        "Szeret beszélgetni, kapitány? Nos, én is..."))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase ("Milyen pletyka népszerû a helyi kocsmában?",
                                    "Mi történik ezeken a földeken?",
                                    "Mi újság a parton?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("El tudna irányítani oda?", "Nem találom az utat egy bizonyos helyre...", "Meg tudná mutatni az utat...?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("Tudni akarom, hogy mit mondanak az emberek egy bizonyos személyrôl.", "Nem tudod, mit mondanak az emberek egy bizonyos személyrôl?", "Szeretnék megtudni valamit a helyiekrôl.");
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
				link.l3 = "Kérem, meséljen többet a telepükrôl.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("Fontos dolgom van!", "Fontos dolgom van veled.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("Nem, te hallasz dolgokat. Most már megyek.", "Nem, semmi - csak a kocsmába indultam."),
                                        RandPhraseSimple("Nem, semmi. Sok szerencsét neked!", "Csak körülnézek. Viszontlátásra."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Kirôl szeretnél tudni?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "A kormányzóról.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "A helyi kocsma tulajdonosáról.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "A kikötômesterrôl.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "A helyi bolt tulajdonosáról.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Mindegy, felejtsd el.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
		
		case "colony":
			dialog.text = LinkRandPhrase("Ôszintén szólva, nem sokat tudok róla, de azért egy-két dolgot el tudok mondani.",
                           "És mi érdekli a kolóniánkban?", "Persze. Mit szeretne tudni?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "Milyen város ez?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "Mit tudsz a várost védô erôdrôl?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Váltsunk témát.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "Most viccelsz? Vagy viccelsz? Nézd meg a képernyôd jobb sarkát.";
			link.l1 = "Igen, az én hibám.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "Nem tudok róla semmit.";
			link.l1 = "Kár.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Még sosem hallottam róla... Mi is ez tulajdonképpen? Én még soha nem hallottam ilyesmirôl"+ NPCharSexPhrase(npchar, "","") +".";
			link.l1 = "Nos, ez egy hajóépítô szerszám, "+pchar.GenQuest.Device.Shipyarder.Describe+". Árult valaki ilyet a városban? Talán. Észrevette, hogy valaki ilyesmit hord magánál?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hmm... Igen, azt hiszem, láttam már valakit, akinek hasonló kinézetû dolga volt. Néhány órával ezelôtt sétálgatott vele. Érdekes eszköz, az biztos.";
				link.l1 = "És hogy nézett ki, és hová ment? Nagy szükségem van arra a hangszerre.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nem, én nem láttam semmi ilyesmit.";
				link.l1 = "Értem. Nos - itt az ideje, hogy körbekérdezôsködjek!";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar, "És mi köze van ennek hozzám? Helyi vagyok!", "Nos, miért zaklatsz ezzel? Én ebben a városban élek, és nem tudok az ilyen dolgokról semmit!"), 
				NPCharSexPhrase(npchar, "Mit is akar tôlem? Nem megmondtam már, hogy nem én vagyok a kém?!", "Nem mondtam már, hogy helybéli vagyok?!"), 
				NPCharSexPhrase(npchar, "Kedvesem, már megint te vagy az! Hagyj békén - én helybéli vagyok!", "Miért zaklatsz már megint a hülye kérdéseiddel?"), 
				NPCharSexPhrase(npchar, "Már megint! Na ez már felháborító!", "Figyeljen, csak hagyjon békén, rendben? Hagyjál már békén, kérlek!"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ki tudja megerôsíteni az állítását?", "Ó, elnézést - már megkérdeztem...",
                      "Sajnálom, olyan sokan vannak...", "Rendben, rendben...", npchar, Dialog.CurrentNode);
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
				dialog.text = "Bárki megteheti! Figyelj, miért zaklatsz folyton?! Ha problémád van, menj a kormányzóhoz, és rendezd el az egészet!",
				link.l1 = "Hmm... Valószínûleg jobb, ha nem zaklatod ôt ilyen pitiáner dologgal. Én hiszek neked.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Bárki ebben a városban! " + NPCharSexPhrase(npchar, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]) + " megteheti, most például, hogy " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], "ô", "ô") + " ott áll.",
				"Ó, Uram, hát például " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], GetAddress_FormToNPC(NPChar) + " " + characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])) + " meg tudja csinálni.");				
			link.l1 = "Rendben, akkor lássuk.";
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
			dialog.text = "Igen, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], " valóban helyi.", "valóban helyi lakos.");
			link.l1 = RandPhraseSimple("Látom"+ GetSexPhrase("","") +". Köszönöm a segítséget.", "Minden tiszta. Köszönöm a segítséget.");
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
			dialog.text = "Tudod, tegnap a városon kívül voltam, sétálgattam, és elvesztettem a jegygyûrûmet... "+ GetSexPhrase("Kapitány, megkeresné, kérem?","Hölgyem, kérem, segítsen megtalálni!") +"";
			link.l1 = "Persze "+ GetSexPhrase("megtehetem! Egy ilyen szép lánynak, mint te, bármit meg tudok csinálni!","Segítek neked. Az egyház arra tanít minket, hogy segítsünk a rászorulókon.") +"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("Nem, nem tudok. Sajnálom. Túl sok dolgom van.", "Sajnálom, nem tudok. Csak eszembe jutott"+ GetSexPhrase("","") +", hogy még mindig vannak befejezetlen ügyeim...", "Nagyon kevés idôm van, így nem tudok segíteni neked semmiben...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+ GetSexPhrase("Kapitány","Lady") +", ez tényleg nagyszerû! Kérem, keresse meg nekem ezt a gyûrût, a férjem csak " + sti(NPChar.LifeDay) + " napokon belül érkezik, és nem szeretném, ha a jegygyûrûm nélkül látna.";
			link.l1 = RandPhraseSimple("Azt mondod, hol vesztetted el?", "Szóval hol is vesztetted el?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "A városkapuk mögött...";
			link.l1 = "Nos, akkor elmegyek megkeresni...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "Igen, kérem. És siessen - ne feledje, hogy már csak " + sti(NPChar.LifeDay) + " napjai vannak.";
			link.l1 = "Emlékszem.";
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
			dialog.text = ""+ GetSexPhrase("Kapitány","ifjú hölgy") +"! Annyira boldog vagyok! Hogyan köszönhetném meg?";
			link.l1 = "Ó, nem kell megköszönni - teljesen önzetlenül tettem.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "Pár száz pezó biztosan nem ártana...";
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
			dialog.text = "Ó, "+ GetSexPhrase("kapitány, ön olyan nemes ember","hölgy, ön olyan nemes") +"! Biztosan imádkozni fogok érted a templomban! Viszontlátásra...";
			link.l1 = "Isten veled, " + NPChar.name + ".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "Ó, de persze. Itt -" + FindRussianMoneyString(iTemp) + ". Ez minden, amim van. Kérem, vegye el ezt a pénzt... És viszlát.";
			link.l1 = "Viszlát, " + GetFullName(NPChar) + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Nem, nem tudok róla semmit.", "Nem tudok semmit ezzel kapcsolatban.", "Nem tudok semmit.");
					link.l1 = LinkRandPhrase("Rendben, köszönöm.", "Értem, köszönöm.", "Rendben, kérem, bocsásson meg.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Én nem tudok róla semmit, de megkérdezheti a kocsma vendégeit - ôk biztosan tudnak egy-két dolgot mondani.", "Nem tudok semmit sem mondani. Kérdezôsködj a kocsmában.", "Nem tudok semmi konkrétumot, de hallottam, hogy pletykáltak a kocsmában.");
				link.l1 = "Nos, ez legalább valami.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen - mint a város polgára, arra kell kérnem, hogy ne járkáljon felemelt pengével.", "Figyeljen - mint e város polgára, meg kell kérnem, hogy tartózkodjon attól, hogy felnyílt pengével járkáljon.");
				link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Vigyázz a lovakra "+ GetSexPhrase("haver","lass") +" , amikor fegyverrel a kezedben rohangálsz. Ettôl ideges leszek...", "Nem szeretem, ha "+ GetSexPhrase("férfiak","bárki") +" fegyverrel a kézben járkálnak. Megijeszt...");
				link.l1 = RandPhraseSimple("Megvan.", "Elrakom.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
