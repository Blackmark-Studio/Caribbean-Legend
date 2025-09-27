void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Mire van szükséged?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		case "dwh_gypsy_0":
			dialog.text = "...";
			link.l1 = "Figyelj, sötét szemöldökû, hallottam, hogy gyógyítasz embereket, még súlyos betegségekbôl is. Igaz ez?";
			link.l1.go = "dwh_gypsy_1";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_gypsy_1":
			dialog.text = "Igazság, "+GetSexPhrase("drága","szépség")+". Nekem minden betegséggel megvan a saját módszerem. Segítettem már talpra állni közembereknek, kereskedôknek, még a gazdagoknak is. Miért, még a kormányzó is az én fôzeteimhez fordult, amikor senki más nem tudott segíteni. A betegség nem fél az aranytól, de nem tud ellenállni a gyógyszereimnek.";
			link.l1 = "Akkor miért nem hajlandó kezelni egy súlyosan beteg lányt, Thomas Morrison lányát?";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;
		
		case "dwh_gypsy_2":
			dialog.text = "Ki mondott neked ilyen badarságot, "+GetSexPhrase("falconet","dovey")+"? Nem tagadtam meg a segítséget. Az apja volt az, aki elzavart a házból. Megbeszéltük, hogy én kezelem ôt, és hirtelen meggondolta magát. Kidobott, mintha esküdt ellenség lennék.";
			link.l1 = "Szóval arra ítélte a lányát, hogy a saját kezével szenvedjen?";
			link.l1.go = "dwh_gypsy_2_1";
		break;
		
		case "dwh_gypsy_2_1":
			dialog.text = "Nem, nem, ô egy gondoskodó apa. Nehéz elképzelni, hogy miért viselkedett így.";
			link.l1 = "Próbált még egyszer beszélni vele?";
			link.l1.go = "dwh_gypsy_3";
		break;
		
		case "dwh_gypsy_3":
			dialog.text = "Még a ház közelébe sem enged. Figyelj, "+GetSexPhrase("drágám","szépség")+", mivel érdekel egy szegény lány sorsa, talán megpróbálhatnád kideríteni, mi folyik itt? Beszélj Tamással, segíts megmenteni a gyereket a szenvedéstôl.";
			link.l1 = "Természetesen segítek. Hol találom Thomast?";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "Nem, sötét szemöldökû. Akárhogy is van, biztos vagyok benne, hogy az apjának megvannak az okai arra, hogy visszautasítsa a segítségét. Nem fogok belekeveredni. Hadd döntsön ô - ô a lánya.";
			link.l2.go = "dwh_gypsy_otkaz";
		break;
		
		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;
		
		case "dwh_gypsy_4":
			dialog.text = "A házuk a fal mellett van, a város északi részén, egy oszlopos, nagyszerû kúria mellett. Menj tovább, "+GetSexPhrase("falconet","dovey")+", beszélj vele, és gyere vissza hozzám.";
			link.l1 = "Hamarosan visszajövök.";
			link.l1.go = "dwh_gypsy_5";
		break;
		
		case "dwh_gypsy_5":
			DialogExit();
			
			AddQuestRecord("DWH", "2");
			
			sld = CharacterFromID("DWH_gypsy");
			sld.dialog.currentnode = "dwh_gypsy_repeat";
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_Tomas", "citiz_13", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Thomas";
			sld.lastname = "Morrison";
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas";
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "goto", "goto1");
			sld.City = "SentJons";
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "dwh_gypsy_repeat":
			dialog.text = "Nos, "+GetSexPhrase("drágám","édesem")+", beszéltél már Thomasszal?";
			link.l1 = "Még nem.";
			link.l1.go = "dwh_exit";
		break;

		case "dwh_exit":
			DialogExit();
			NextDiag.TempNode = "dwh_gypsy_repeat";
		break;
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! Mi szél hozott az otthonomba?";
			link.l1 = "A nevem Captain "+GetFullName(pchar)+". A cigányasszony kérésére vagyok itt. Tudni akarja, miért utasította vissza a segítségét. Tényleg olyan helyzetben vagy, hogy visszautasítasz minden esélyt, bármilyen kicsi is legyen az, hogy meggyógyítsd a lányodat?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_1":
			dialog.text = "Ó, kapitány... Kérem, értse meg, vissza kellett utasítanom, de nem önszántamból. Higgye el, bármit megadnék, hogy Esther meggyógyuljon.";
			link.l1 = "Mi késztethette arra, hogy visszautasítsa a segítséget, amire olyan nagy szüksége van?";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "Tudja, a családunk mindig is hívô volt. A feleségem, Olivia halála után egyedül a hitem tartotta meg a lelkemet. Amikor a cigány felajánlotta a segítségét, beleegyeztem - bármit, hogy megmentsem a lányomat. De... a papunk rájött erre.";
			link.l1 = "Hadd találjam ki: ellenzi az ilyen szolgáltatásokat?";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "Pontosan így van. Meggyôzött arról, hogy csak az ima és az Úr akarata gyógyíthatja meg a lányomat. És arra az esetre, ha letérek errôl az útról - egy 'kapcsoló' segítségével - az egyházból való kiközösítéssel fenyegetett meg. Megértette? Kiközösítés!";
			link.l1 = "Tehát Eszter egészsége kizárólag a pap szavától függ?";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "A lányom és én az egyház által élünk. A hit a mindenünk. Ha a cigány elbukik, nemcsak a lányomat veszítem el, hanem azt is, ami még megmaradt a helyembôl ezen a világon. Az emberek el fognak fordulni, az egyház elutasít minket. Eszter és én teljesen egyedül maradunk.";
			link.l1 = "És ha a pap beleegyezik? Akkor megengedné a cigánynak, hogy megpróbálja?";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "Igen. Ha az egyház megáldaná a tetteit... Akkor bíznék benne. Kész vagyok bármit kipróbálni, ami segíthet.";
			link.l1 = "Értem. Rendben, Thomas, segítek neked. Beszélek a papoddal. Talán meg tudom gyôzni.";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "Te... te tényleg hajlandó vagy segíteni nekünk? Kapitány, imádkozni fogok a sikerért. De ne feledje... a papunk makacs és elvhû, nem lesz könnyû meggyôzni.";
			link.l1 = "Az elveket le lehet gyôzni meggyôzô érvekkel. Várjatok meg, hamarosan visszatérek.";
			link.l1.go = "Tomas_7";
		break;

		case "Tomas_7":
			DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("DWH", "3");
			pchar.questTemp.DWH_pastor = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "Thomas, sikerült meggyôznöm a papot.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "Tényleg? Hihetetlen! Akkor hívjuk meg a cigányt, amilyen hamar csak lehet.";
			link.l1 = "Természetesen meg fogjuk, de van egy apróság. A pap reméli, hogy ez nem fogja megrendíteni a hitedet, és ôszinte bûnbánatot és jócselekedeteket vár. Ilyen cselekedet lehet például egy új harang vásárlása a plébánia számára.";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "Ó, kapitány... Egy harang jó sokba kerül. Lehet, hogy meg kell válnom valamitôl a néhai feleségem ékszereibôl. De Estherért kész vagyok mindent odaadni, amim van - és még többet is. Persze, könyörgök majd az Úrnak a bocsánatáért. Elmegyek a kovácshoz, leadom a rendelést, és megkeresem a cigányt.\nKérem, mondja meg a papnak, hogy a harang hamarosan elkészül. Ha kell, még a föld alól is kihozom.";
			link.l1 = "Jól van, Tamás.";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			
			LAi_SetActorType(npchar);
			pchar.questTemp.DWH_pastor_PrinesDengi = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "Elmondtam a papnak, amit mondtál. Nem fog többé az utadba állni, úgyhogy elkezdheted.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "Köszönöm, kapitány, hogy részt vettél a munkában! Kérem, vegye el ezt az ötven dublont. Ez a legkevesebb, amit tehetek önért, és ez minden, amim jelenleg van...";
			link.l1 = "Ostobaság! Nem pénzért segítettem neked. Szóval, minden készen áll a... hmm... kezeléshez?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Nos, ha ragaszkodik hozzá... Tehetek még valamit?";
			link.l2.go = "Tomas_16_2";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
		break;

		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "Ahhoz, hogy elkészítsem a lány egészségét helyreállító gyógymódot, mangarózára van szükségem - egy ritka növényre, amely olyan helyeken nô, amelyeket ember ritkán érint. Ismerek egy barlangot a városon kívül, ahol gyakran mászkálnak... csavargók. A mangarosát füstölésre égetik, nem tudva az erejérôl. Segítsetek, "+GetSexPhrase("falconet","dovey")+", szerezzetek nekem mangarosát, nélküle semmi sem mûködik.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "Mangarosa? Ismerem azt a növényt.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "Hogy néz ki?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "Elég magas növény, hasadt levelekkel és kellemes, szédítô illattal. Semmi mással össze nem téveszthetô.";
			link.l1 = "Rendben, megkeresem ezt a mangarosát.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "Te is kevered a dohányoddal?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Nem, egyáltalán nem! Van egy Amelia nevû gyógyító. Olyan bájitalokat fôz belôle, amik szó szerint kifordíthatják az elmédet.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "Nem, de néhányszor már kezeltem mangarosát.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "Szóval ismered Ameliát? Nos, "+GetSexPhrase("falconet","dovey")+", hamarosan igazi konkurenciát fogsz nekem állítani. De ennek most nincs itt az ideje. Menj, hozd a mangarózát, én pedig mindent elôkészítek.";
			link.l1 = "Máris megyek.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "Látom, nem vagy egy átlagos, "+GetSexPhrase("falconet","dovey")+". Tudásod hatalmas, elméd éles, mint a penge! Nem félsz az ismeretlenbe merészkedni, buzgón megragadod azt, amitôl mások ódzkodnak. Thomas szerencsés, hogy a segítségedre van szüksége. Most menj, hozd ide a mangarózát, én pedig meggyógyítom a lányt.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			
			AddQuestRecord("DWH", "5");
			
			// поход за мангаросой
			LAi_LocationDisableOfficersGen("Antigua_Grot", true);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = true;
			PChar.quest.DWH_Grot.win_condition.l1 = "location";
			PChar.quest.DWH_Grot.win_condition.l1.location = "Antigua_Grot";
			PChar.quest.DWH_Grot.function = "DWH_Grot";
		break;
		
		case "Bandit_1":
			dialog.text = "Ha-ha. Én mondom neked, Mark, ô egy bolond. Még a házát sem zárja be.";
			link.l1 = "Biztos vagy benne, hogy a tyúkja nem ül otthon?";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestFunctionDelay("DWH_Grot_2", 4.0);
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Lám, lám, friss hal úszik a hálóba! Gyerünk, ne csak álljatok ott! Fordítsd ki a zsebeidet, gyorsan, mielôtt elszáll a jó kedvünk.";
			link.l1 = "Nyugalom, banditák. Üzleti ügyben vagyok itt. "+sld.name+" küldött. Mangarosa kell nekem.";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Azt mondod, hogy a "+sld.name+" küldött? Rendben, megvan a mangarosa. Adj tíz aranyat, és a tiéd.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Tessék, tessék.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "Pénzt? Minek? Nem osztogatok alamizsnát. De adhatok helyette két kiló acélt!";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "Rendben, itt a mangarosa. És ne feledd, nem láttál minket.";
			link.l1 = "Heh. Nem kellett a figyelmeztetés.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_LocationDisableOfficersGen("Antigua_Grot", false);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = false;
			
			/*if (CheckAttribute(pchar, "questTemp.DWH_GoodChoice"))*/ SetFunctionLocatorCondition("DWH_VorovstvoSunduk", "Antigua_Grot", "box", "box1", false)
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_3";
			AddLandQuestMark(sld, "questmarkmain");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DWH_Podkreplenie");
			}
		break;
		
		case "Bandit_7":
			DialogExit();
			
			chrDisableReloadToLocation = true;
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			GiveItem2Character(NPChar, "cannabis7");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=3; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_"+i, "citiz_48", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
				if (i==4) sld.model = "citiz_49";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Antigua_Grot", "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "DWH_Grot_4");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "Nézze meg, "+npchar.name+", ez az a növény, amire szüksége van?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Elhoztad, amit kértem?";
				link.l1 = "Még nem, de dolgozom rajta.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "Igen, ez az. Most már mindenem megvan, amire szükségem van, és elkezdhetem.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "Menjünk gyorsan, nem vesztegethetjük az idôt.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "Kapitány, ha nem bánja, késôbb beszélünk. Most jön a legfontosabb rész... a kezelés.";
			link.l1 = "Természetesen, Thomas. Remélem, a lánya hamarosan felépül.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+"Thomas nem önszántából utasította el önt. A pap kiátkozással fenyegette meg, ha elfogadja a segítségét.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "Azonnal tudtam, "+GetSexPhrase("drága","szépség")+", hogy nehéz szívvel adta nekem ezt a visszautasítást.";
			link.l1 = "Van rá mód, hogy segítsek neki anélkül, hogy az egyház megsértôdne?";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "Ó, "+GetSexPhrase("drága","szépség")+", nem könnyû dolog, de az utakat ismerem, tudom, mit kell tennem. Csakhogy a segítséged nélkül nem boldogulok, érted.";
			link.l1 = "Természetesen számíthatsz rám.";
			link.l1.go = "gypsy_10";
			link.l2 = "Sajnálom, sötét szemöldökû, de erre egyáltalán nincs idôm. Mindent megtettem, ami tôlem telt. Most a saját dolgaimmal kell foglalkoznom.";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "Akkor itt van, amire szükségem van: egy tárgy, ami a lányé, két szál datura, egy szál ipecac és egy szál verbéna. Ha mindezt elhozod nekem, akkor készíthetek neki egy gyógyító italt.";
			link.l1 = "Rendben van, hozok mindent, amire szükségem van.";
			link.l1.go = "gypsy_11";
		break;

		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Tamás, sajnos a pap nem hallgatott a szavaimra. De a cigány és én segíthetünk neked. Szükségem van...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "Azt akarod mondani, hogy menjek szembe az egyházzal?";
			link.l1 = "Mindent csendben fogunk csinálni, senki sem fogja megtudni. Hamarosan a lánya újra élvezni fogja az életet, és szabadon sétálhat a városban, ahogy egy fiatal hölgyhöz illik.";
			link.l1.go = "Tomas_23";
			link.l2 = "A fenébe is, Thomas Morrison, azt akarja, hogy a lánya felépüljön, vagy csak szép szavak mögé bújik?";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "Rendben, egyetértek. De kérem, cselekedjen óvatosan. Nem akarok felesleges pletykákat és bajt.";
			link.l1 = "Nem akarok kellemetlen pletykákat, és nem akarok kellemetlen pletykákat. Szóval, szükségem van a lánya egy személyes tárgyára. Valami, amihez ragaszkodik.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "Rendben, egyetértek. De kérem, cselekedjen óvatosan. Nem akarok felesleges pletykákat és bajt.";
			link.l1 = "Nem akarok kellemetlen pletykákat, és nem akarok kellemetlen pletykákat. Szóval, szükségem van a lánya egy személyes tárgyára. Valami, amihez ragaszkodik.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "Hmm... Igen! Tudom, mi lesz jó. Várjon meg itt, mindjárt jövök.";
			link.l1 = "Várni fogok...";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("Néhány perc múlva...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "Tessék. Ezek jáde gyöngyök. Eszter soha nem vette le ôket, nagyon kedvesek neki.";
			link.l1 = "Kitûnô. Most már csak várnia kell. Hamarosan találkozunk, Thomas.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "gypsy_21":
			dialog.text = "Sikerült mindent beszerezned, amire szükséged van?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "Sikerült mindent beszereznem.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Emlékeztess, mit kell hoznom.";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "Akkor itt van, amire szükségem van: egy tárgy, ami a lányé, két szár datura, két szár ipecac és egy szál verbéna. Ha mindezt elhozod nekem, akkor készíthetek neki egy gyógynövényes fôzetet.";
			link.l1 = "Rendben van, hozok mindent, amire szükségem van.";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "Kitûnô. Most már készíthetek egy gyógyító fôzetet a lánynak. Legkorábban holnap reggelre lesz kész. A szokásos módon megtalálsz a város utcáin.";
			link.l1 = "Rendben, akkor viszlát.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "Nos, "+npchar.name+", készen áll a bájitalod?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "Itt van, "+GetSexPhrase("drága","szépség")+". A lány tegye fel ezeket a gyöngyöket, és igya ki a fiola tartalmát az aljáig. Legfeljebb egy hónap múlva teljesen egészséges lesz.";
			link.l1 = "Ezt azonnal elviszem Thomasnak. Isten veled, sötét szemöldökû.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "Thomas, minden készen áll. Eszter tegye fel ezeket a gyöngyöket, és ürítse ki az üvegcsét a bájitallal egy menetben.";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "Köszönöm, "+pchar.name+"! Kérem, bocsásson meg, nem akarok egy percet sem vesztegetni...";
			link.l1 = "Persze, persze.";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "Üdvözlet, "+pchar.name+"! Az én Eszterem meggyógyult! Teljesen egészséges és most a templomban van, hálát adva a mi Urunknak Istenünknek, hogy elküldött téged és a cigányt hozzánk!";
			link.l1 = "Tamás, nagyon örülök, hogy minden rendben ment! Vigyázz a kislányra, hosszú és boldog élet áll most már elôtte.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "Fogd ezt a háromszáz dublont. Sajnos, többet nem tudok felajánlani, mivel adósságba kellett mennem, hogy összegyûjtsem ezt az összeget. De tudd, hogy sem szavak, sem arany nem fejezheti ki azt a hálát, amit irántad érzek, kapitány. Nemcsak az életéért való félelemtôl szabadítottál meg, hanem a családunknak is reményt adtál a jövôre nézve. Mindig az adósa leszek!";
			link.l1 = "Köszönöm! Háromszáz dublon elég nagylelkû, úgyhogy nyugodj meg - több mint eléggé megköszönted!";
			link.l1.go = "Tomas_43";
			link.l2 = "Nem fogadom el a pénzed, Thomas. Eszedbe se jusson ragaszkodni hozzá! Inkább vegyél a fiatal Eszternek egy szép ruhát, megérdemli.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+"...látogasson meg minket bármikor. Mindig szívesen látunk téged nálunk. És beszélj a cigányasszonnyal is, látni akart téged.";
			link.l1 = "Megtiszteltetésnek veszem! Most mennem kell - a dagály nem vár a kapitányra.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "Persze, persze. Isten legyen veled, "+GetFullName(pchar)+"!";
			link.l1 = "Viszontlátásra.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "Ön egy nagyon nemes ember, "+GetFullName(pchar)+"! Szûz Mária legyen veled! Látogass meg minket, nálunk mindig szívesen látott vendég vagy. És még, "+pchar.name+", beszélj a cigánnyal, látni akart téged.";
			link.l1 = "Biztos vagyok benne! Most mennem kell - a tenger hívogat.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("Hallottad? "+GetFullName(pchar)+" procured a remedy for Thomas Morrison's daughter that miraculously restored the poor girl's health!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison naponta gyújt egy gyertyát a plébánián, hogy az egészségére legyen. "+GetFullName(pchar)+". They say thanks to his (her) efforts, Thomas's daughter was freed from a prolonged illness.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison a szemünk láttára virágzott ki. Mintha sosem lett volna beteg. Senki sem tudja igazán megmagyarázni, mitôl vonult vissza a betegség.", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_41":
			dialog.text = "És tessék, "+GetSexPhrase("falconet","dovey")+"! Tudtam, hogy vissza fogsz térni. Hála az erôfeszítéseidnek, a lány felépült, és most úgy mozog, mint egy galamb. Az egész város csodálattal beszél róla.";
			link.l1 = "Nos, sötétbegy, ez nem csak az én mûvem - ne adj nekem túl sok hitelt. A te fôzeted volt az, ami helyreállította az egészségét, úgyhogy ne becsüld le a részed ebben.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "Kedves szíved van, "+GetSexPhrase("sólyom","dovey")+", és éles eszed! Nagyszerûségre vagy hivatott - ez a jóslatom.";
			link.l1 = "Heh... nos, köszönöm, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "És tessék, "+GetSexPhrase("falconet","dovey")+"! Tudtam, hogy megint fel fogsz itt bukkanni. Hála az erôfeszítéseidnek, a lány meggyógyult, és most úgy repdes, mint egy galamb. Az egész város csodálja ôt.";
			link.l1 = "Na, na, te magad mentetted meg a lányt, és azt akarod, hogy én arassam le a babérokat? Ez nem fog menni! Te készítetted a bájitalt, te állítottad talpra a lányt, neked kell elvinned a dicsôséget.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "Kedves szíved van, "+GetSexPhrase("sólyom","dovey")+", és nemes lelked. Van egy ajándékom számodra - olyan, amit minden kapitány értékelne. Tessék. Mostantól a patkányoknak a hajódon nem lesz se boldogság, se nyugalom!";
			link.l1 = "Ajándék nekem? A csillagokra, ez nagyon váratlan!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "A lelked tiszta, látom, hogy nem fogsz mangarózát égetni a pillanatnyi örömért. Ha sürgôsen szükséged van rá, gyere hozzám, "+GetSexPhrase("falconet","dovey")+". Három szár háromszázötven dublonnába kerül\nEz a gyógynövény szeszélyes, nem mindenki találja meg. Úgyhogy ne siettessetek - havonta egy alkalomnál gyakrabban ne kérjetek, úgysem fogom tudni beszerezni.";
			}
			else
			{
				dialog.text = "Fényes a lelked, látom, hogy nem vagy ostoba, a gyógynövényekhez sem értesz rosszabbul, mint néhány gyógyító. Sok mindent megtalálsz, bár a szerencse nem mindig mosolyog. Van egy ritka növény, amit nem mindenki talál. Úgy hívják, hogy mangarosa. Ha valaha is szükséged lesz rá, gyere hozzám, "+GetSexPhrase("falconet","dovey")+". Három szárat kapok, de nem adom ingyen - háromszázötven dublont elfogadok\nDe ez a gyógynövény akaratos, úgyhogy ne siettess. Ne kérj havonta egynél gyakrabban - még ha a sors összes kártyáját kiteríted is, nem fogom hamarabb megkapni.";
			}
			link.l1 = "Nos, köszönöm, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "Kapitány, folyton arra gondolok - bizonyára maga az Úr irányította ide a megfelelô idôben! Megmentette a lányomat, és ezt soha nem fogom elfelejteni.";
			link.l1 = "Talán, Thomas. Az Úr útjai kifürkészhetetlenek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "Kér egy kis bort, kapitány? Van valami különleges a kedves vendégeknek.";
			link.l1 = "Köszönöm, Thomas, de sajnos mennem kell.";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "Mire van szükséged, sólymom?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Mondd csak, sötét szemöldökû, hoznál nekem mangarosát?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Csak beugrottam köszönni. Ideje mennem!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "Ki más, mint én, "+GetSexPhrase("drága","szépség")+", szerezne neked egy ilyen ritkaságot? Háromszázötven dublon - és a tiéd, három szár, se több, se kevesebb.";
			if (PCharDublonsTotal() >= 350)
			{
				link.l1 = "Az ára tisztességes. Az arany a tiéd.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "A pokolba az egésszel! Túl kevés az erszényem. Visszatérek, ha a szerencse rám mosolyog.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "Így már jobb. Vedd el. És vigyázz, hogy ne pazarold feleslegesen, tudod - a mangarosa nem közönséges gyógynövény, olyan erô rejtôzik benne, amit nem mindenki tud kezelni.";
			link.l1 = "Ne aggódj, sötét szemöldökû, találok majd méltó felhasználási módot az erejének.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 3);
			RemoveDublonsFromPCharTotal(350);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}
