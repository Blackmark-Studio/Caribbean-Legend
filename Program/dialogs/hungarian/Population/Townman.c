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
				    dialog.text = RandPhraseSimple("Azt mondják, hogy öné ez a város, "+ GetSexPhrase("uram","kisasszony") + ".", "Micsoda kellemes találkozás, "+ GetSexPhrase("uram","kisasszony") + "!");
					link.l1 = RandPhraseSimple("Meggondoltam magam. Sok szerencsét!", "Csak sétálok a városban. Viszlát.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Lenne egy kérdésem hozzád.", "Szükségem van néhány információra.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Pénzügyi kérdéseket szeretnék megbeszélni.", "Pénzügyekrôl...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("Riadó! Egy fegyveres ôrült van itt! Fegyverbe!", "Fegyverbe! Egy fegyveres ôrült van itt!");
						link.l1 = RandPhraseSimple("Micsoda?!", "Mit csinálsz?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("Mit akarsz? Menj tovább.", "Ne álld el az utamat, tûnj el.");
						link.l1 = RandPhraseSimple("Tudod mit? Ne ugass!", "Nyugodj meg. Vagy én magam teszem meg!");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("Szeretném megkérdezni.", "Egy perc figyelmet kérek. Egy kérdés.");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("Pénzügyi kérdéseket szeretnék megbeszélni.", "Pénzügyekrôl...");
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
					dialog.text = "Jó napot, "+GetAddress_Form(NPChar)+". Látom, hogy ön a saját hajójának kapitánya. Egy szívességet szeretnék kérni...";
					link.l1 = "Figyelek, "+GetAddress_FormToNPC(NPChar)+". Mit akarsz?";
					link.l1.go = "passenger";
					link.l2 = "Sajnálom, "+GetAddress_FormToNPC(NPChar)+", de sietek.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text =NPCharRepPhrase(npchar,
				LinkRandPhrase("A nevem ", "A nevem ", "Hívhatsz ")
				+GetFullName(npchar)
				+LinkRandPhrase(". Mit akarsz?", ". Még nem láttalak korábban. Ki vagy te?", ". Ki vagy te és mit akarsz tôlem?"),

				LinkRandPhrase("Üdvözletem, " + GetAddress_Form(NPChar) + ". A nevem " + GetFullName(npchar) + ". És téged hogy hívnak?",
				 "Helló, " + GetAddress_Form(NPChar) + "! Én vagyok " + GetFullName(npchar) + ". Megtudhatom a neved?",
				 "Igen, " + GetAddress_Form(NPChar) + ". Mit szeretnél? És egyébként a nevem " + GetFullName(npchar) + ". És téged hogy hívnak?"));

				Link.l1 = pcharrepphrase(
				LinkRandPhrase("A fenébe! ", "Francba! ", "A fenébe! ") + "Igen, én vagyok a kapitány "+ GetFullName(Pchar)+ LinkRandPhrase(", nem hallottad még soha "+NPCharSexPhrase(NPChar,", fattyú?","?"), " és "+ GetSexPhrase("a leghíresebb kalóz","a leghíresebb kalózlány") +" a tengeren!", " és a fenébe is, ha tévedek!"),
				LinkRandPhrase("vagyok " + GetFullName(Pchar) + ", kapitány.", "nevem " + GetFullName(Pchar) + ".", "Hívhatsz kapitánynak "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Az egész város izgatott - don Fernando de Alamida, a királyi felügyelô megérkezett. Tudja, sok mindent láttam már itt, de ez... Nem a gyász változtatja meg az embert, hanem az, ahogyan kezeli. Azt mondják, más ember lett az apja halála után. Most már nem találsz megvesztegethetetlenebb és... kíméletlenebb szolgáját a Koronának az egész szigetvilágban.", "Nézd csak meg a 'Holy Mercy'! Azt mondják, maga a király rendelte meg, hogy különleges tervek alapján épüljön. És vegyük észre - egyetlen karcolás sincs rajta. Mintha maga Szûz Mária védelmezné. Bár hallottam pletykákat... talán nem is a Szûzanya.", "Tudod, hányszor próbálták már megölni don Fernandót? Tizenkét támadás nyílt vízen - és ez csak az elmúlt évben! Nos, egy ilyen hûséges és képzett legénységgel, és az Úr oltalma alatt - túl fogja élni a tizenharmadikat is!"), LinkRandPhrase("Hallottad? Don Fernando de Alamida megérkezett városunkba, és azt mondják, most is valahol az utcán van. Szeretném a saját szememmel látni ôt...", "Bonyolult ember ez a don Fernando. Egyesek szerint ô a megmentô, aki megtisztítja a hazát a mocsoktól. Mások azt suttogják, hogy valami megtört benne az apja halála után, és hamarosan mindannyian sírni fogunk. De én azt mondom nektek: ne féljetek tôle. Féljetek azoktól, akik azzá tették, ami.", "Milyen jóképû ember ez a don Fernando! De tudod mi a furcsa? Olyan, mintha senkit sem venne észre. Csupa kötelesség és szolgálat. Hallottam, hogy volt egy lány... de miután találkozott valami pappal, teljesen elutasította a világi örömöket. Mintha fogadalmat tett volna."), RandPhraseSimple(RandPhraseSimple("Átkozott felügyelô! Amíg ô itt van - a város olyan, mintha halott lenne. Se kereskedelem, se szórakozás. Még a légzés is, úgy tûnik, csendesebbnek kell lennie. És tudod, mi a legijesztôbb? Minden kikötôben ugyanez a helyzet. Mint az óramû. Ô királyi felsége nem találhatta ki szándékosan ezt a kínzást mindannyiunk számára!", "Don Fernando ismét meglátogatta az árvaházat. Nagylelkûen adakozik, órákig imádkozik. Egy ilyen méltó embert példaként kellene állítani az átkozott sikkasztók elé!"), RandPhraseSimple("Ha! 'Szent' Fernando ismét bezáratta az összes bordélyházat. Sebaj, nemsokára elhajózik, és újra kinyitnak.", "Megérkezett az insp... felügyelô, ez az! Don Fernando de Almeyda, vagy hogy is hívják, Alamida! Annyira fontos, hogy maga a kormányzó is lábujjhegyen járkál körülötte. Azt mondják, belenéz a szemedbe, és rögtön meglátja minden bûnödet. Félelmetes!")));
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
				link.l1 = PCharRepPhrase("Csak szeretnék kérdezni valamit errôl a lyukról, amit te úgy hívsz, hogy 'a város'.", "Szeretnék kérdezni valamit errôl a városról.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Lenne egy kérdésem hozzád.", "Szükségem van néhány információra.");
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
						link.l3 = RandPhraseSimple("Pénzügyi kérdéseket szeretnék megbeszélni.", "Pénzügyekrôl...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Figyelj, remélem, hogy tudsz nekem segíteni. Szeretnék venni egy "+pchar.GenQuest.Device.Shipyarder.Type+", és azt mondták, hogy ezt a dolgot az önök városában árulják. Nos, valaki árulta az utcán. Tudsz valamit?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Tudja ", "Tudja ", "Hallotta ") + " , hogy a helyi templomot nemrég kirabolták?";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Á, te vagy az "+GetFullName(Pchar)
                        +" "+ GetSexPhrase("- régi barátom!","- szépséges!") +"", "Örülök, hogy látlak, "+ GetSexPhrase("öreg barátom!","csinos!") +" "
                        + Pchar.name, "Ó, ez a "+ GetSexPhrase("kapitány maga","kapitány maga") +" "
                         +GetFullName(Pchar))
						+RandPhraseSimple(". Azt hittem, hogy meghaltál!", ". És talán "+ GetSexPhrase("részeg, mint mindig.","egy kicsit részeg.") )
						+LinkRandPhrase(" Gyerünk, mire van szükséged?", " Mi ez az idô?", " Már megint zavarsz?"),
						LinkRandPhrase(TimeGreeting() + ", kapitány ", "Jó napot kívánok, "+GetAddress_Form(NPChar)+" ", "Üdvözlöm, kapitány ")+GetFullName(Pchar)
						+LinkRandPhrase(". Hogyan segíthetnék "+ GetSexPhrase("egy ilyen méltó embernek","egy ilyen méltó lánynak") +", mint te?", ". Miért vagy itt?", ". Ezúttal mit akarsz tudni?")),             
                        PCharRepPhrase(LinkRandPhrase("Hello, kapitány ", "Üdvözlet, ah, te vagy az "+GetAddress_Form(NPChar)+" ", "Ah, kapitány ")
						+GetFullName(Pchar)
						+LinkRandPhrase(", azt hittem, hogy soha többé nem találkozunk, és",
										 ", nem mondom, hogy örülök, hogy látlak, de", ", látom, hogy még mindig élsz, milyen kár, és")
						+LinkRandPhrase(" mit akarsz?", " miért vagy itt?", " hogyan segíthetek neked?"),
						LinkRandPhrase(TimeGreeting() + ", kapitány " + GetFullName(Pchar) + ". Miben segíthetek?",
						"Ó, ez a kapitány " + GetFullName(Pchar) + "! Miben segíthetek?",
						"Üdvözlöm, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". Kér valamit?"))
						);  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("A füled becsap téged. Mennem kell.", "Nem, semmi baj, a kocsmába tartottam."),
						RandPhraseSimple("Rendben, mindegy. Sok szerencsét!", "Csak sétálgatok a városban. Búcsúzom."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Kérdéseid vannak?";
			link.l1 = "Mond önnek valamit a név ezeken a papírokon?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Leszarok valami random papírt, ráadásul olvasni sem tudok. Menj az uzsoráshoz, azt mondják, hogy ô ért a szarhoz a betûkkel, ha!",
			"Nem tudom mirôl beszélsz, kérdezz meg valaki mást, kapitány" + GetFullName(Pchar) + ".", 
			"Nem tudom, hogyan segíthetnék, kapitány " + GetFullName(Pchar) + ". Próbáljon meg beszélni az uzsorással, talán ô tudja.");
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("Nem hazudik, kapitány " + GetFullName(Pchar)+"?",
				"Szóval mi " + PChar.name+"?",
				"Emlékezni fogok rád, " + GetFullName(Pchar)+".")
				 + " Most mondd meg, mit akarsz?",
				LinkRandPhrase("Örvendek, kapitány " + PChar.name,
				"Örülök, hogy találkoztunk, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
				 "Örvendek, kapitány " + PChar.name) + ". De kétlem, hogy csak a nevemet akartad tudni, igaz?");
            link.l1 = PCharRepPhrase("Csak szeretnék kérdezni valamit errôl a szarfészekrôl, amit te úgy hívsz 'town'.", "Szeretnék kérdezni valamit errôl a városról.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Lenne egy kérdésem hozzád.", "Szükségem van néhány információra.");
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
					link.l3 = RandPhraseSimple("Pénzügyi kérdéseket szeretnék megbeszélni.", "Pénzügyekrôl...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Figyelj, remélem, hogy tudsz nekem segíteni. Szeretnék venni egy "+pchar.GenQuest.Device.Shipyarder.Type+", és azt mondták, hogy ezt a dolgot az önök városában árulják. Nos, valaki az utcán árulta. Tudsz róla valamit?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Tudja ", "Tudja ", "Hallotta ") + " , hogy nemrég kirabolták a helyi templomot?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("A füled becsap téged. Mennem kell.", "Nem, semmi baj, a kocsmába tartottam."),
                                        RandPhraseSimple("Nos, ez semmiség, Sok szerencsét!", "Csak sétálgatok a városban. Viszontlátásra."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
				PCharRepPhrase(LinkRandPhrase("Ó, és örülök, hogy látlak, ahogy én is örülök a piának, kérdezz, amit akarsz.", "Szeretne beszélgetni, kapitány? Én is... Fôleg egy pohár rummal.", "Igen, " + PChar.name + "?"),
				LinkRandPhrase("Mit akarsz még?", "Gondolom, kapitány "+PChar.name+", hogy szeret beszélgetni?")),
		        PCharRepPhrase(LinkRandPhrase("Mit akar még, "+ GetAddress_Form(NPChar) + "?", "Figyelek, kapitány úr.", "Mennem kell, úgyhogy kérdezzen gyorsan, kapitány úr."),
                LinkRandPhrase("Mindig örülök egy kellemes társaságnak, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Beszélj!",
                "Igen, " + GetAddress_Form(NPChar) + "?",
                "Szeretne beszélgetni, kapitány? Én is... ")));
			link.l1 = LinkRandPhrase ("Milyen pletykák keringenek ebben a városban?","Van valami hír ezen a vidéken?","Hogy megy a földi élet?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("Megmutatná az utat?", "Nem találom az utat egy helyre...", "Segíts nekem eljutni egy helyre...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Szeretném tudni, mit mondanak az emberek egy emberrôl.", "Tudod, mit mondanak az emberek egy emberrôl?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Szeretnék többet megtudni a helyiekrôl.", "Tudna valamit mondani a helyiekrôl?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("A füled becsap téged. Mennem kell.", "Nem, semmi baj, a kocsmába tartok."),
            RandPhraseSimple("Nos, ez semmiség. Sok szerencsét!", "Csak sétálok a városban. Viszontlátásra."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Ki érdekli?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Többet akarok tudni a kormányzóról.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Többet akarsz tudni a helyi kocsma tulajdonosáról.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Szeretnék többet tudni a helyi hajógyár mesterérôl.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Szeretnék többet tudni a helyi bolt tulajdonosáról.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Semmit. Felejtsd el.";
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
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Soha nem hallottam róla... Régóta élek itt, és még sosem láttam ilyet.";
			link.l1 = "Nos, ez egy hajóépítô eszköz, "+pchar.GenQuest.Device.Shipyarder.Describe+". Árult valaki ilyesmit a városban? Vagy esetleg hordta magával és észrevette?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Igen, láttam egy férfit azzal a dologgal néhány órával ezelôtt. Az utcán sétált. Érdekes eszköz volt.";
				link.l1 = "Hogy nézett ki és hova tartott? Nekem tényleg szükségem van valami ilyesmire.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nem, én nem láttam semmi ilyesmit.";
				link.l1 = "Értem. Akkor tovább kérdezôsködöm.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Nem, errôl nem tudok semmit.", "Nem, mennem kell.", "Nem tudok semmit.");
					link.l1 = LinkRandPhrase("Rendben, köszönöm.", "Értem, köszönöm.", "Rendben, elnézést.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Errôl nem tudok semmit, de megpróbálhatod megkérdezni a kocsma törzsvendégeit, ôk biztosan többet tudnak mondani.", "Nem tudok semmit mondani, kérdezzen meg valakit a kocsmában.");
				link.l1 = "Köszönöm szépen.";
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
				dialog.text = "Kapitány, minél hamarabb el kell jutnom a " + XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+" nevû kolóniára, amely a "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+", a "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". A hajója szilárdnak tûnik az itt hajózó kis hajók többségéhez képest. Tudok fizetni neked "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+". Mit szólsz hozzá?";
			}
			else
			{
				dialog.text = "Kapitány, el kell jutnom a kolóniához " + XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", ez egy "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", egy "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Tudom, hogy ez rendkívül kockázatosnak hangzik, de talán " + FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)) + " egy jó kis lökést adna neked?";
			}
			link.l1 = "Hm. Én is erre tartok, úgyhogy kész vagyok ilyen feltételekkel a fedélzetre venni.";
			link.l1.go = "passenger_1";
			link.l2 = "Sajnálom,  "+GetAddress_FormToNPC(NPChar)+", de én más irányba hajózom. Nem tudok segíteni neked.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Kár érte. Nos, akkor várok egy másik hajóra. Viszontlátásra.";
			link.l1 = "Viszlát.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Remek, mert már belefáradtam a várakozásba. Majd megkapod a fizetséged, ha ott leszünk.";
			link.l1 = "Menj a hajómra, "+GetAddress_FormToNPC(NPChar)+". Hamarosan indulunk.";
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
			dialog.text = "Itt vagyunk, kiváló! Ez az utazás a hajóján nagyon kielégítô volt. Köszönöm. Fogadja el a pénzét, uram.";
			link.l1 = "Sok sikert, "+GetAddress_FormToNPC(NPChar)+"! Búcsúzás.";
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
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, mint a város polgára arra kérem, hogy tegye hüvelybe a pengéjét.", "Figyelj, mint e város polgára arra kérlek, hogy tedd hüvelybe a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, amikor fegyverrel futsz. Ideges tudok lenni...", "Nem szeretem, ha egy idegen meztelen karddal sétál elôttem...");
				link.l1 = RandPhraseSimple("Megvan.", "Ne aggódj.");
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
