// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "Beszélj a kapitányunkkal. Nincs mit mondanom.";
			Link.l1 = "Rendben.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Beszélj a kapitányunkkal. Nincs mit mondanom.";
			Link.l1 = "Rendben.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Uram, keres valakit?";
					Link.l1 = "Igen, haver. Beszélhetnék a kapitánnyal?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "Ha a kapitányunkat keresi. Nemrég szállt partra.";
					Link.l1 = "Bírság";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Ó, egyedül jöttél ide. Ha! Ebben az esetben menjen a kapitányunkhoz. Mesélj neki a szomorú tetteidrôl...", "Hû, úgy tûnik, hogy megôrültél, barátom. Menj a kapitányunkhoz és ô majd beszél veled.");
				Link.l1 = "Sajnálom...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "Jobb, ha a kikötôben keresed.";
			Link.l1 = "Köszönöm, barátom.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Nos, ez aztán a nagy zûrzavar, kapitány! A kocsmában voltunk, ittunk, ahogy szoktunk, amikor sikoltozást hallottunk. Kirohantunk a kocsmából, és láttuk, hogy le akarnak tartóztatni. Basszák meg! Úgy döntöttünk, hogy elhagyjuk ezt a barátságtalan kikötôt.";
			link.l1 = "Igen, bizonyára néhány embernek kicsit furcsa az igazságérzetük.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Kapitány! Ne aggódj így! Világos volt, hogy nincs mód a nyugodt menekülésre, ezért úgy döntöttünk, hogy meglátogatjuk a helyi bankárt, hogy ellenôrizzük a ládáit. Itt van a részed - " + sti(pchar.questTemp.ReasonToFast.p9) + " pezó...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Kapitány! Ne aggódj így! Világos volt, hogy nincs mód a békés menekülésre, ezért úgy döntöttünk, hogy meglátogatjuk a helyi bankárt, és megnézzük a ládáit. A zálogládában volt egy szép kard is. Itt van a részed - " + sti(pchar.questTemp.ReasonToFast.p9) + " pezó és egy kard...";
			}		
			link.l1 = "Szép munka fiúk! Szép munka! Büszke vagyok rátok.";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Kapitány, a barátja megszökött.";
			link.l1 = "Milyen barát?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Nos, a barátja, akit a tömlöcbôl hoztál el.";
			link.l1 = "Hogy a faszba sikerült elveszítened?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "Nem a mi hibánk volt, kapitány. A latrinán keresztül a tengerbe ugrott... Megpróbáltuk lelôni, de túl sötét volt...";
			link.l1 = "A francba! Tényleg elszabadult a pokol! Mindannyiótokat kiraknak, és elküldünk a cukornáddal dolgozni! Elveszíteni egy ilyen értékes nagyágyút! Hihetetlen!";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Kapitány, bocsásson meg nekünk, a mi hibánk volt - a fogoly megszökött.";
			link.l1 = "Milyen fogoly? Ki szökött meg?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Nos, ó, elfelejtettem a nevét, " + pchar.GenQuest.Hold_GenQuest.CapName + ", igaz?";
			link.l1 = "A francba! Hova néztél?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "Kijött a raktérbôl, és leugrott a bástyáról. Nem lôttük le, hogy ne legyen zajos, és amíg elôkészítettünk egy hosszú csónakot, megmentették a kibaszott halászok.";
			link.l1 = "És miért fizetek neked! Korbácsoljátok meg az ôrség vezetôjét, és egy hétre vonjátok meg tôle a rumot. Állj fel! Horgonyt vetünk...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Üdvözlöm, kapitány. Nem történt baleset a...";
			link.l1 = "Rendben, rendben, értem.... Ott van a fogoly a raktérben. A neve " + pchar.GenQuest.Hold_GenQuest.CapName + ". Fogjatok néhány embert és szállítsátok a kikötôbe. Most már szabad.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "Tényleg szabad? Egy hosszúhajón kell leszállítanunk?";
			link.l1 = "Nem, egy kibaszott teknôsön... Azt hittem, elég világos voltam. És siessetek! Horgonyt kell vetnünk az apály kezdetére.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Kapitány, nincsenek emberek a hajón! Valami nagyon nincs rendben... Tommy azt mondta, hogy látott egy macskát a pilótafülkében, és az volt az egyetlen élô lélek...";
			Link.l1 = "Idióta, a macskáknak nincs lelkük. Úgy tûnik, mintha már régóta nem járt volna templomban, vagy egyáltalán nem is járt ott. Voltál már a kapitányi kabinban? Szükségem van egy naplóra.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "Nem, nekik van lelkük. Nem volt hajónapló és egyetlen navigációs mûszer sem. Még egy hosszú csónak sem...";
			Link.l1 = "Nincsenek. Elfáradt a viharban?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "De igen, kapitány. A macskáknak van lelkük. Kapitány, a hosszú csónakot elvágták, és találtunk egy kardot a pilótafülke padlóján. Rozsdás és véres. Tessék, nézze meg...";
			Link.l1 = "Hagyd abba ezt a szart, dobd el, és ne beszélj a macskákról, a fenébe is! Ellenôrizzük a raktérben és menjünk... Valami nagyon nem stimmel itt, és ez kurvára nem tetszik...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "Kapitány, rossz érzésem van ezzel a hellyel kapcsolatban... Talán itt az ideje, hogy elmenjünk?";
					Link.l1 = "Igen... Menjetek a hajóra.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Kapitány, én nem maradok ezen a furcsa hajón, ha hajlandó vagy elvinni a kikötôbe. Jobb, ha én magam ugrom a tengerbe.";
					Link.l1 = "Nem vagyok hajlandó erre... Egy kicsit félek is...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Talán el kellene süllyesztenünk, kapitány?";
					Link.l1 = "Hogy az itt élô halott matrózok lelkei meglátogassanak minket rémálmainkban?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Istenem, ne! Kapitány... miért mondja ezt?";
			Link.l1 = "Ne sápadj el, csak vicceltem... Menjetek a hajóra. És azt hiszem, mégiscsak igazad van, talán a macskáknak tényleg van lelkük...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Beszéljen a fônökkel. Nincs mit mondanom neked.", "A posztomon vagyok. Minden kérdéssel forduljon az erôd parancsnokához.");
			Link.l1 = "Rendben.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("Most nagyon elfoglalt vagyok. Hagyjatok békén.", "Ne vonja el a figyelmemet a munkámról. Nincs mirôl beszélni.");
			Link.l1 = "Kár...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Morgan el akart mondani neked 'egy-két dolgot'... Valahol itt van, a fedélzeten.", "Heh, keressétek meg Morgant. Rossz hírek várnak rád...");
			Link.l1 = "Rendben.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
