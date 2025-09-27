// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Mi a baj?";
			link.l1 = "Nem, semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Köszönöm a segítségét, kapitány!";
			link.l1 = "Istenem... Még szebb vagy, mint ahogy elképzeltem!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "A pokolba a szépségemmel! Tudod, mennyi bánatot okozott nekem? A saját orromat is levágnám, ha nem rombolná a hírnevemet. Az a szemétláda nem engedte, hogy élve elhagyjam a Corvette-et, folyton azt hajtogatta, hogy én 'túl sokat tudok.' Aztán tegnap azt mondta, hogy megunta a várakozást, és akaratom ellenére elvisz engem\njobbkor nem is jöhettél volna! De hol a jó modorom, a nevem Helen McArthur. A papám Rumbának hívott, mert folyton véletlenül összetörtem a finom porcelánt, amit ô 'vett', , úgyhogy most már így hív a csapatom.";
			link.l1 = "A nevem "+GetFullName(pchar)+" és azért vagyok itt, hogy megmentselek. Napok óta kutatom a Karib-térséget, hogy megtaláljalak Ms. Gladys kedvéért.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Ms. Gladys!? Hogy van?";
			link.l1 = "Betegre aggódja magát. De hamarosan látni fogod, elhajózunk Blueweldbe. Útközben elmondhatsz mindent, ami veled történt.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Hogy ôszinte legyek, "+pchar.name+", most azonnal szeretnék enni és aludni egyet. Kimerült vagyok azok után a napok után, amiket a szörny hajóján töltöttem...";
			link.l1 = "Természetesen Ms. McArthur. Utasítom a stewardot, hogy szolgáljon fel önnek ételt és készítsen önnek egy ágyat a saját kabinjában.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "De Maure kapitány, még egyszer szívbôl köszönöm az idôben történô mentést. Meg kell látogatnia engem és az anyámat. A házunk nem messze van innen, a móló felôl balra. És tudnia kell, hogy "+pchar.name+", soha nem bocsátom meg önnek, ha búcsú nélkül elhajózik!";
			link.l1 = "Részemrôl a megtiszteltetés, Ms. McArthur. Biztosan fel fogom keresni önt!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Á, hát itt van, de Maure kapitány! Nagyon örülök, hogy itt van, rengeteg kérdésem van önhöz.";
			link.l1 = "Sajnálom, Ms. McArthur, de egy kicsit el kell halasztanunk a beszélgetésünket. Több információra van szükségem, mielôtt kielégítô válaszokat tudnék adni. Most arra kérem, hogy ne mutatkozzon az utcán. Remélem, hogy a várakozás nem tart sokáig. Bízzon bennem és várjon.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "Te magad mondtad, hogy nem bocsátanád meg, ha nem ugranék be.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "Á, hát itt vagy, kapitányom! A szemeid azt mondják, hogy híreid vannak számomra!";
			link.l1 = "Svenson kapitány azt mondta, hogy velem akar hajózni. Nagyra értékelem a kívánságát, ráadásul Ms. Gladys említette, hogy hiányzik a tenger. Üdvözlöm a fedélzeten, Ms. Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Svenson kapitány mondta, hogy velem akar hajózni. Nagyra értékelem a kívánságát, ráadásul Ms. Gladys említette, hogy hiányzott a tenger. Üdvözlöm a legénységemben, Ms. Helen Sharp!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Igenis, kapitány! Utálom, hogy ezt kell mondanom, uram, de ki tudok állni magamért, és nem tûröm, hogy a férfiak szabadkozzanak. Nem vagyok felelôs levágott kezekért vagy kivájt szemekért.";
			link.l1 = "Ne aggódjon, a fegyelem rendíthetetlen a hajómon. Kérdeznem kell valamit...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...Igen?";
			link.l1 = "Jan Svenson és én megtudtuk, hogy ön az Isla Tesoro jogos örököse. Igen, ez igaz, ne rázza a fejét! Nálam van a térkép fele, ami bizonyítja a jogait. Nem lesz könnyû, de Jan és én mindent megteszünk, hogy segítsünk neked a jogos tulajdonosává válni.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", komolyan mondod? Nem szép dolog így kötekedni egy szegény lánnyal! Hogyan lehet jogom egy egész sziget tulajdonjogára?!";
			link.l1 = "Teljesen komolyan gondolom, Ms. McArthur. És segíteni fogok, hogy megszerezze a születési jogát. Vitorlázzunk most!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "Mit mondott? Helen Sharp? Miért Sharp?";
			link.l1 = "Helen, te vagy Beatrice Sharp lánya és a Sharp dinasztia egyetlen örököse. Ez a térkép fele, amit Ms. Gladys ôrzött ennyi éven át. Ez a bizonyíték az Isla Tesoro-hoz való jogodról. Nem lesz könnyû, de én és Jan Svenson mindent megteszünk, hogy segítsünk neked megörökölni a nagyapád szigetét.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			notification("Helen helyesel", "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Ó... Szegény anyám! Bárcsak egy nap megtalálnám a sírját, és ott imádkozhatnék a lelkéért. De... várj! Ez lehetetlen!";
			link.l1 = "Mi az, Ms. Sharp?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "A cigányasszony jóslata valóra vált... Végre megértettem.";
			link.l1 = "Mi? Milyen prófécia?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", naivnak nevezhetsz, de azért elmondom neked. Amikor kislány voltam egy cigányasszony azt mondta nekem: 'Sorsod annak az embernek a kezében lesz, aki nem veszi el az özvegyasszony pénzét, aki visszaadja a halott ember aranyát és aki megnevezi az anya\nAkkor azt hittem, hogy ez mind badarság, de valahogy neked sikerült a jóslat minden részét beteljesítened, errôl nem lehet tudni!";
			link.l1 = "A sorsa, azt mondja... Nos, talán igaza van. Nem fogok csalódást okozni. Együtt fogjuk megkeresni az édesanyja sírját. És most... Ms. Helen Sharp! Készüljön fel az indulásra, és ne késsen!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Kapitány "+pchar.name+"! Van egy ötletem...";
			link.l1 = ""+npchar.name+"? Itt nem biztonságos, és mondtam, hogy maradj a hajón...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "Charles, annyi puskapor van ebbe az öreg kádba tömve, hogy ha felrobban, az egész sziget egyenesen a Szent Péter kapuig repül! Teljesen mindegy, hogy azt mondod, bújjak el, vagy sem, szóval hallgass rám!";
			link.l1 = "Rendben, beszélj gyorsan!";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "A korvett és a fregatt. Nem ismerik fel Knive hajóját ellenségesnek. Kihasználhatjuk ellenük az önelégültségüket. Fogjunk néhány hordó puskaport, gyújtsunk be egy gyújtózsinórt, és hajózzunk a hajókhoz\nHa közel engednek minket, meggyújtjuk a gyújtózsinórt, ledobjuk a hordót az egyikre, és elhajózunk, amilyen gyorsan csak tudunk. Aztán végignézzük a látványos robbanást... Mit szólsz hozzá?";
			link.l1 = "Egy rögtönzött tûzhajó... nagyon ravasz! A terved elég ôrült ahhoz, hogy talán mûködjön... ha elég közel tudunk kerülni anélkül, hogy felismernének minket.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Mit veszíthetünk "+pchar.name+"? Nem lesz könnyû egyszerre két hajóval harcolni, de lesz esélyünk kiegyenlíteni az esélyeket...";
			link.l1 = "Jól van. Lássunk hozzá! Fiúk! Fogjatok három hordó puskaport! Elmegyünk innen a pokolba! Imádom a fantáziádat, "+npchar.name+"... Én magam sosem jutottam volna erre az ötletre.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Igenis kapitány, mi a baj?";
			link.l1 = "Jackman hajója a Sabo-Matila-öbölben van, a nehéz fregatt 'Centurion'. Ez a hajó egykor a Hawkes-ok tulajdona volt, tehát Jackman kabinjában fontos tárgyaknak és dokumentumoknak kell lenniük... fel kell szállnunk rá.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Könnyebb mondani, mint megtenni. Hogy akarod ezt megtenni a mi polakreinkkel? Túlszárnyalnak minket.";
			link.l1 = "Igaza van. Jackmannak legalább kétszer annyi embere van, mint nekünk, és mindannyian tapasztalt vívók. Ôrültség lenne megtámadni ôket elôzetes bombázás nélkül. De az elhúzódó harc sem a legjobb megoldás. Ezért gondolkodtam azon, hogy mit tegyünk.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", még nem ismertek fel minket ellenségként, akárcsak azok az idióták a törököknél... Megpróbálhatjuk újra a trükkünket...";
			link.l1 = "Helen, épp most mondtam, hogy fel kell szállnunk a fregattra, és át kell kutatnunk, a felrobbantás nem jöhet szóba.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Várj egy percet, "+pchar.name+", nem fogjuk elsüllyeszteni. Tegyünk egy kis csavart a dologba.  Figyelj, fogunk néhány üres rumos hordót, és megtöltjük ôket puskaporral, grapeshot-tal és rövid gyújtózsinórral. Aztán közelebb hajózunk a fregattjukhoz, és a rögtönzött robbanóanyagot a fedélzetükre dobjuk.";
			link.l1 = "Ha! A nôi leleményességed továbbra is lenyûgöz! Tûzhajó helyett egy fougasse-t javasolsz? Gondolod, hogy mûködhet?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "És miért is ne? Az ô szabaddeszkájuk magasabb, mint a miénk, de két-három ember egy csiga segítségével könnyedén fel tud emelni és el tud dobni egy teljesen megrakott hordót. Kiáltunk - 'Itt van egy kis ingyen rum a Knive-tól! És a hordók felrobbannak, mielôtt még reagálhatnának.";
			link.l1 = "A robbanó lövedék a legjobb embereit a fedélzeten darált hússá változtatja... A fenébe, ez csábítóan hangzik.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Dobjunk egyszerre öt hordót a hátsó fedélzetrôl a hajófenékre. "+pchar.name+", megvan a meglepetés ereje. Még semmit sem fognak sejteni! És aztán azonnal elhajózunk tôlük, mielôtt esélyük lenne a fedélzetre lépni.";
			link.l1 = "Nos, próbáljuk meg. Nem azonosíthatnak minket, mielôtt a robbanó hordók a fedélzetükre kerülnek... Nem lesz könnyû lezárni. Jackman nem olyan nagy bolond, mint Ghoul volt.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Kockáztassuk meg, "+pchar.name+"! Ahogy már mondtam, mit veszíthetünk?";
			link.l1 = "Jó érv... Álljatok a fiúk mellé! Készítsétek fel a fougassokat és készüljetek a harcra!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Nos, kedves kapitányom... Itt az ideje, hogy elbúcsúzzunk egymástól. A szolgálatom véget ért, és itt az ideje, hogy megszokjam, hogy Isla Tesoro kalózkirálynôje vagyok. Remélem, hogy méltó utódja leszek a nagybátyámnak. Köszönöm a segítségeteket.";
				link.l1 = "Igen, kár, hogy el kell válnunk tôled, de ilyenek a sors szeszélyei. Most sokkal fontosabb feladataid vannak, mint a hajómon szolgálni.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "Szeretnék a hajótokon maradni. Közel hozzád... De ez lehetetlen. Légy boldog, Charles. És jobb, ha méltó hozzád!";
					link.l1 = "Sajnálom, Helen.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "Ez olyan furcsa, "+pchar.name+"! Most lettem egy egész sziget tulajdonosa, de nem érzem magam Isla Tesoro királynôjének... Gondolom, a Testvériség új feje jobban fogja irányítani a kolóniát, mint én. Még sokat kell tanulnom.";
					link.l1 = "Ne aggódj emiatt, Helen, te olyan nô vagy, aki tud vigyázni magára - ahogyan azt nekem is mondtad, amikor elôször jöttél a fedélzetre.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "Nos, akkor is barátok maradunk, nem igaz?";
			link.l1 = "Persze... Helen, találkozunk még az Isla Tesoro-n. Elvigyelek a szigetedre?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "Igazad van... Nézd, én is megmentettem a zsákmányom egy részét, amíg a hajódon utaztam. Fogadd el, és meg se próbáld visszautasítani az ajánlatomat - nem akarok az adósod lenni.";
			link.l1 = "Hé, várj egy pillanatot...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Tudom, mit fogsz mondani. Persze, a segítséged sokkal jelentôsebb volt, mint ez a csekély kincsesláda. De ez minden, ami most a birtokomban van, és vissza kell fizetnem. Vedd el, ha nem viszed el te magad, akkor a kabinodban hagyom.";
			link.l1 = "Most már egyedül fogsz vitorlázni? Talán elvihetnélek Isla Tesoróra?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("Kaptál egy ládát dublonnal");
			PlaySound("interface\important_item.wav");
			dialog.text = "Erre nincs szükség, "+pchar.name+". Én magam is eljutok a szigetre. Nálam van a kardom és a pisztolyom, egy darabig elég lesz... Biztos vagyok benne, hogy Isla Tesoro királynôjének nem kell aggódnia a bevételek miatt, ha egyszer odaérek.";
			link.l1 = "Igenis, felség. Sok szerencsét kívánok az új életedhez.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Elég ebbôl, még viccbôl is. Még mindig Helen vagyok. De nem csak ezt akartam mondani. Újra megtaláltam az apámat, bár ez egy kicsit furcsa volt. Egy angol nemes jó nevével fizetett az örökségemért, és ez zavar. Az angol nemzetközösség vadászik rá, és nem akarom, hogy te, "+pchar.name+", részt vegyél benne.";
			link.l1 = "Térj észhez, Helen! Ô egy bandita és egy kalóz!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Kalóz? És ki a fasz vagy te, hogy ilyet mondj? Ô az apám, és csak ez számít nekem! És én, egy bandita és egy kalóz lánya, leszarom, hogy mit gondol róla az angol igazságszolgáltatás. Ha megpróbálsz bármi módon ártani az apámnak, elfelejtek minden jót, amit eddig tettél velem, ezt tudd. Tekintsd ezt figyelmeztetésnek.";
			link.l1 = "Így van? Igazából lány, jobb lenne, ha udvariasabb lennél. Nem vettem észre, hogy panaszkodtál volna a kalózkodásomra, amikor megmentettem a csinos bôrödet annak az erôszaktevô Donovannak a kezébôl, vagy amikor megosztoztunk a fogságból származó nyereségen!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "I..... Sajnálom. Visszavonom, bocsáss meg nekem. Elvesztettem a fejem... De ettôl még szeretnék a barátod maradni, ami lehetetlen lenne, ha elkezdenéd üldözni az apámat.";
			link.l1 = "Megértettem. De soha ne merészelj megfenyegetni, asszony. Tudnod kellene már a hajómról, hogy nem félek senkitôl és semmitôl. Különösen nem tûröm a tiszteletlenséget egy nôtôl - kalózkirálynô vagy sem. Lehet, hogy úriember vagyok, de még a türelmemnek is van határa. Most, hogy ezt elintéztük, viszlát. Sok szerencsét kívánok.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Köszönöm.... Talán még találkozunk, "+pchar.name+"...";
			link.l1 = "És miért is ne? A jövôben többször is meglátogatom Isla Tesorót. Ott találkozunk... Viszlát, Helen.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "Biztos vagyok benne. "+pchar.name+", szeretnék a hajódon maradni, ha megengeded. Veled maradni...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(válassza Máriát) Nem érted, Helen. Az egész jövôd elôtted áll, és nincs miért aggódnod. Nekem csak háború, politikai intrikák és teljes bizonytalanság áll elôttem. Neked kell megszervezned a saját életedet, egy ilyen vad vándornak, mint én, nincs benne helye.";
				link.l1.go = "result_10";
				link.l2 = "(válassza Helent) Ez több, mint amit remélni tudtam, Helen. Persze nem akarlak elveszíteni, de jobb lenne, ha Isla Tesoróra mennél. Ki tudja, hová vezet még a sorsom. Jelenleg háború, politikai intrikák és bizonytalanság vár rám.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "Ez több, mint amit remélni tudtam, Helen. Természetesen nem akarlak elveszíteni, de jobb lenne, ha Isla Tesoróra mennél. Ki tudja, hová vezet még a sorsom. Jelenleg háború, politikai intrikák és bizonytalanság vár rám.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Ne hazudj nekem. Csak nem akarsz... Mondd meg, ki ô? Az a vörös hajú szajha az Elhagyott Hajók Városából, igazam van?";
			link.l1 = "Helen! Próbálom elmondani, hogy szerintem mi a legjobb neked! Hogyhogy nem érted ezt?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Ó, persze, persze, hogy az vagy... És hogy tudott téged elbûvölni, mi? Mi az, amivel ô rendelkezik, amivel én nem?! Tényleg ennyire jó? Eh, "+pchar.name+"... Nos, ez a te döntésed, nekem nincs más hátra, minthogy a szigetemre menjek. Nem állhatok kettôtök közé\nKöszönök mindent, amit értem tettél, Charles. Te vagy a legjobb ember, akivel valaha találkoztam. Remélem, hogy barátok maradhatunk?";
			link.l1 = "Persze... Helen, találkozunk még Isla Tesoro-n. Akarod, hogy elvigyelek oda?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Nem szükséges. Veszek egy új hajót. Elegendô pénzt gyûjtöttem össze egy szkúner megvásárlására és felszerelésére, amíg a parancsnokságod alatt szolgálok. Újra egy új 'Rainbow' hajón fogok hajózni.";
			link.l1 = "Örülök, Helen, hogy ilyen... takarékos voltál. De egy szkúneren hajózni nem illik Isla Tesoro kalózkirálynôjéhez. Hamarosan szerezned kell egy fregattot magadnak.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Talán, "+pchar.name+". Rendben. Elmegyek a hajógyárba, de elôbb... adj egy búcsúcsókot... Kérlek...?";
			link.l1 = "Helen...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "Az én sorsom a te sorsod, mióta találkoztunk. Hát nem érted ezt? "+pchar.name+"? Követni foglak a világ végéig!";
			link.l1 = "És mi van az apáddal? Laurence Beltrope? Ô az ellenségem...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Az apám Sean McArthur. Szerettem ôt és gyászoltam a halálát. Ô volt az egyetlen apám. És az a kalóz... Nem is akarok beszélni róla.";
			link.l1 = "Helen... Drága Helénám!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", Mindig is el akartam mondani, hogy te vagy a legnagyszerûbb ember, akivel valaha találkoztam! Annyi mindent tettél értem, amit soha nem fogok tudni meghálálni. Veled akarok maradni. Örökre. Hozzád megyek, ha akarod... Szeretlek.";
			link.l1 = "Együtt leszünk. Megígérem!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "Megígéred, hogy most azonnal megteszel nekem valamit? És kérlek, ne nevess!";
			link.l1 = "Megígérem, kedvesem!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Hívj az igazi nevemen. Hívj a nevemen!";
			link.l1 = "Szeretlek, Helen Sharp.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", Kedvesem... Ölelj át! Túl régóta várok erre a pillanatra!";
			link.l1 = "Helen, kedvesem...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Ez... hihetetlen volt! Nem akarok máshova menni... Maradjunk itt reggelig. A világ várhat!";
			link.l1 = "Hagyjuk, hogy várjon, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Másnap reggel...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Выполнено требование для Дороже золота
			pchar.questTemp.GoldenGirl_Ready = true;
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Kapitány! Jackman meghalt... Végre biztonságban van a családom?";
			link.l1 = "Igen, Helen, mindannyian biztonságban vagytok. De 'Centurion' elsüllyedt, és vele együtt az összes dokumentum is, amely segíthetne megtalálni édesanyád sírját, és bizonyíthatná, hogy jogod van Isla Tesoróra igényt tartani... Eh... Most már egyedül kell megrohamoznom Tortugát...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", Ne aggódj annyira. Semmit sem tehetünk ellene. Miattam se aggódj, én jól fogok élni a sziget nélkül is. Köszönök mindent, amit értem tettél!";
			link.l1 = "Úgy hangzik, mintha... el akarnál hagyni, igaz?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Igen, kapitányom. Sikerült elég pénzt összegyûjtenem egy szkúner megvásárlására és felszerelésére. El fogok hajózni a 'Rainbow' még egyszer. Blueweldben újra találkozunk... Én hazamegyek.";
			link.l1 = "Nos... sok szerencsét, Helen!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Nos, kapitányom... Úgy tûnik, kudarcot vallottunk. Viszontlátásra. Hazamegyek. Elég pénzt kerestem a parancsnokságod alatt, hogy vegyek magamnak egy új szkúnert. Még találkozunk a tengeren!";
			link.l1 = "Sok szerencsét, Helen. Sajnálok mindent. Viszontlátásra.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Kapitány úr! Jackman meghalt... Úgy tûnik, hogy a családom biztonságban van, nem igaz?";
			link.l1 = "Igen, Helen, biztonságban van. De nem vagyok boldog, túl sok idôt vesztettem, és Isla Tesoro most már angol gyarmat. Az örökséged nélkül maradtál, így nekem kell megrohamoznom Tortugát...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", Mit mondott neked az ügyvéd?";
			link.l1 = "Túl sok idôt vesztettem, és Isla Tesoro most már angol gyarmat. Örökség nélkül maradtál, így nekem kell megrohamoznom Tortugát... Sajnos, vesztettünk.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Nem, drágám, ez nem fog menni.";
				link.l1 = "Akkor miért nem?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", ma nem érzem jól magam. Ne érezd magad rosszul, kérlek, nem a te hibád. Ne csináljuk ma...",""+pchar.name+", kedvesem, olyan fáradt voltam az elmúlt napokban. Hogy ôszinte legyek, csak aludni szeretnék. Bocsáss meg nekem. Csináljuk máskor.");
				link.l1 = RandPhraseSimple("Jól van...","Semmi baj. Ahogy akarod...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", a hangulat megfelelô, gyerünk!",""+pchar.name+", persze, nincs kérdés! Gyerünk, menjünk!");
				link.l1 = RandPhraseSimple("Ez az én lányom...","Olyan szép vagy, Helen...");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Csodálatos volt, "+pchar.name+"!..","Nagyszerû voltál, mint mindig, kedves..."), RandPhraseSimple("Nagyszerû volt, Charles!","Csodálatosan éreztem magam, kedvesem!"), RandPhraseSimple("Veled sosem unatkozom, kapitányom!","Csodálatos voltál, drágám!"));
			link.l1 = RandPhraseSimple("Szeretlek...","Mindig jó veled lenni, Helen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", Tudod, hogy mindig örülök, ha... De ez most nem a megfelelô idô - el kell kapnunk azt a gazember Thibaut-t, mielôtt megszökik.";
				link.l1 = "Igazad van, mint mindig, Helen...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Nem, drágám, ez nem fog menni.";
				link.l1 = "Akkor miért nem?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", ma nem érzem jól magam. Ne érezd magad megbántva, kérlek. Ne csináljuk ma...",""+pchar.name+", kedvesem, olyan fáradt voltam az elmúlt napokban. Hogy ôszinte legyek, csak aludni szeretnék. Bocsáss meg nekem. Csináljuk máskor.");
				link.l1 = RandPhraseSimple("Jól van...","Semmi baj. Ahogy akarod...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", szeretlek! Gyerünk, menjünk!",""+pchar.name+", aye aye kapitány! Gyerünk, gyerünk!");
				link.l1 = RandPhraseSimple("Te vagy az én jó kislányom...","Gyönyörû vagy, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "LoveSex_Room_Go");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Igen, "+pchar.name+"?","Igen, kapitányom?","Figyelek, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "Ezt nézze, kapitányom!";
				link.l1 = "Hû, micsoda fogás! Látom, nem vesztegetted az idôt, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Drágám, a prostituáltaknál tett látogatásaidról...";
				npchar.quest.refusesex = true;
				link.l1 = "Micsoda? Helen, ezt teljesen félreértetted! Én csak...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, meglátogatom Tayasal elveszett indiai városát. Nem fogok hazudni neked: ez az utazás nagyon veszélyes, sôt - a bálványon keresztül történô teleportálással jár. Követsz engem?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Helen, adj egy teljes jelentést a hajóról.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Azt akarom, hogy minden alkalommal, amikor kikötünk, vásároljon bizonyos árukat.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Az Ön utasítására érkeztem, kapitány.";
				Link.l2 = "Helen, több parancsot kell adnom neked.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "Szerinted ez vicces?";
					link.l1 = "Szép hajó, ugye? Megkaptad, Helen! Gondolj csak bele, milyen férfi az, aki a Karib-tengeren egy igazi hajót ad a hölgyének, mi?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, szükségem van a tanácsodra.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, van egy rendelésem a számodra...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, maradjunk kettesben a kabinban... pár órára? Mit gondolsz?","Drágám, töltsük el a következô néhány órát tete-a-tete? Tetszik ez az ötlet?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, miért nem bérelünk ki egy szobát, és maradunk ott kettesben... a következô néhány órára? Mit szólnál hozzá?","Drágám, töltsük el a következô néhány órát tete-a-tete? Bérelhetnénk egy szobát... mit szólsz hozzá?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Helen, drágám, meghívhatlak egy kis minôségi idôtöltésre a kocsmába?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Helen, úgy tûnik, megtaláltam a hódolód - Francis - utolsó végrendeletét. Rád hagyta az örökségét.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "Azt hiszem, ez a bicska most már a tiéd. Blaise az úgynevezett nagybátyád...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Most semmi, Helen.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, kedvesem, beteg vagy, vagy mi van? Azt várod, hogy lemegyek, átfésüljem a raktérséget, és elkezdjem számolni a patkányokat?";
			Link.l1 = "Rendben, bocsánat drágám, az én hibám...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Én pedig egy saját hajót akarok, száz ágyúval, ami 20 csomóval repül. Egész életemben olyan kapitány voltam, mint te. Menj, keress magadnak egy rohadt pénztáros, és zaklasd vele.";
			link.l1 = "Igen, igazad van, Helen. Sajnálom.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Csupa fül vagyok.";
			Link.l1 = "A beszállási szabályzatunkról...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "A hajóról, amit irányít...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Eddig semmi.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Mi a kívánsága, kapitányom?";
			Link.l1 = "Nem akarom, hogy bárhova is felszálljon. Vigyázzon magára és az embereire.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Azt akarom, hogy az elsô adandó alkalommal szálljon fel az ellenséges hajókra.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Igen, kapitányom?";
			Link.l1 = "Nagyra értékelném, ha a beszállás után tartózkodna a hajócserétôl. Túl értékes számomra.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Ha véletlenül bárkinek a fedélzetére lép, nézze meg alaposan a zsákmányolt hajót. Ha jó a hajó, nyugodtan elviheti magának.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Rendben, meggondolom.";
			Link.l1 = "Majd gondolkodik rajta... Rendben, mintha én amúgy is tudnék neki parancsokat adni.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Rendben, meggondolom.";
			Link.l1 = "Majd gondolkodik rajta... Rendben, mintha én amúgy is tudnék neki parancsokat adni.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Rendben, meggondolom.";
			Link.l1 = "Majd gondolkodik rajta... Rendben, mintha én amúgy is tudnék neki parancsokat adni.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Rendben, meggondolom.";
			Link.l1 = "Majd gondolkodik rajta... Rendben, mintha én amúgy is tudnék neki parancsokat adni.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Rendelések?";
            Link.l1 = "Álljatok ide!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Kövessetek és tartsátok a lépést!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Változtassátok meg a lôszer típusát a lôfegyvereitekhez.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Válaszd kia lôszer típusát:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
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
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Azonnal, kapitány!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Azonnal, kapitány!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Hát itt vagy! Végre megtaláltalak... Ez nem semmi volt, kapitányom! Még sosem láttam ilyen tetôfutást és ugrást ilyen lélegzetelállító magasságból! A szívem majd' felrobbant! Egy nap még megölsz ezekkel a trükkjeiddel, kedvesem... Ó, nem vagy egyedül... Ki ez a lány?";
			link.l1 = "Ô Catherine Fox, Fox ezredes, a híres angol tengerészgyalogezred, a 'Sea Foxes'. parancsnokának lánya, akit Antiguára viszünk.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Valóban... Üdvözöljük a fedélzeten, Ms. Fox! Ne, ne, ne fogja de Maure kapitány karját, egyedül is tud járni! És most menjünk a hosszúhajóra - el kell tûnnünk innen."; 
			link.l1 = "Ha! Köszönöm, Helen! Mihez kezdenék nélküled? Catherine, kövess minket!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Végre felébredtél, drágám! Hogy érzed magad? Halálra rémítettél...";
			link.l1 = "Helen, mi történt? Szétrepedt a fejem...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Amikor beléptünk a kapitányi kabinba, te még mindig a padlón feküdtél. Szinte megállt a szívem! A fiúk felkaptak és visszahúztak a hajónkra - éppen idôben, mert a fedélzeten heverô halottak újra kelni kezdtek.\nMicsoda borzalom! Ez majdnem elég ahhoz, hogy megtaláljam Istent! Teljesen áthatolhatatlanok voltak a pengéinkkel és a golyóinkkal szemben! Gyorsan elvágtuk a köteleket, és megpróbáltunk elhajózni, de egy sortûz a hajójukról súlyosan megrongálta a hajónkat, és elvesztettük az irányítást. Aztán felhúzták a vitorlákat, és egy szempillantás alatt eltûntek.\nA hajónk zátonyra futott, így erre a partra kellett menekülnünk, mielôtt a vihar elpusztíthatta volna. Sok jó ember meghalt ma, de a hajó végül is túlélte... ha csak nem parancsoltam volna, hogy hagyjuk el...";
			link.l1 = "Nem a te hibád, Helen. Ez volt a helyes döntés. Mihez kezdenék nélküled?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Bevonszoltalak a hajóba, aztán partra vittelek. Halottnak tûntél, csak a szíved dobogott nagyon gyengén. Nézd! Még mindig remeg a kezem.";
			link.l1 = "Köszönöm, szerelmem. Köszönettel tartozom neked. Mióta fekszem itt?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Egy egész napig. Kimostam és bekötöztem a sebeidet, adtam neked gyógyszert és öntöttem rád egy kis rumot. Most már meg kell gyógyulnod!";
			link.l1 = "Ezúttal nem fogok meghalni, drágám. Bár nem érzem jól magam...blurgh....";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Mondd meg....Az igazi 'Repülô Hollandi', Charles volt? Miért támadtak meg minket? És miért nem lôttek ránk a közeledéskor, hanem rögtön a beszállás után kötöttek ki, hogy elsüllyesszenek minket?";
			link.l1 = "A kapitányuknak szüksége volt arra az amulettre, amelyrôl Tuttuathapakkal, egy indián sámánnal beszéltem. Hogy miért volt rá szükségük, nem tudom... de amint a vezetôjük megszerezte az amulettet, elintézett minket... Mindenható Istenem, micsoda nyomorult rémálom! Egy hajó, amelyen élôholtak vannak! Lehetetlen elhinni...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Igen, most rajtunk volt a sor, hogy találkozzunk a 'repülô hollanddal'. Gah! Beleborzongok a bôrömbe! A következô kikötôben, ahol megállunk, elmegyek a templomba, gyertyát gyújtok, és imádkozom a mi Urunkhoz, Jézus Krisztushoz a csodálatos megszabadulásunkért. A pokolba is, annyira hálás vagyok, hogy még néhány pápai szenthez is imádkozom...";
			link.l1 = "Ott leszek veled Heléna, már régen nem voltam rendes gyónáson... De elôbb vissza kell mennünk abba a faluba. Mindent el kell mondanom Tuttuathapaknak. Az az átkozott hajó megtámadott minket az amulett miatt! Remélem, annak a vörösbôrû ördögnek van valami ötlete, hogy mi a fenének lehetett szüksége az élôholtaknak rá.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Jól van, rendben. De óvatosnak kell lennünk - a sebeid alig gyógyultak be.";
			link.l1 = "De ugye segítesz nekem gyorsabban meggyógyulni? Szeretlek, Helen...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Én is szeretlek, drágám...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", Egyszer már mondtam neked, hogy most már közös a sorsunk. A te sorsod az én sorsom is. Mikor indulunk?";
			link.l1 = "Nagyon örülök, hogy ezt hallom. Majd késôbb elmondom, amikor oda megyünk. Fel kell készülnünk.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Készen állok, kapitányom! Követni foglak a világ végéig!";
			link.l1 = "Köszönöm, szerelmem...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "Ó, "+pchar.name+"! Örülök, hogy látlak! Mit csinálsz itt Isla Tesoro-n?";
			link.l1 = "Ugyanazt, mint mindig - üzletelek. Csak be akartam ugrani és látni téged is. Hogy mennek a dolgok, Helen?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "Mi a baj a mi drága kormányozónkkal, kapitány? Ezúttal kinek a seggét rúgjuk szét? Spanyolok, kalózok, vagy valaki rosszabb?";
			link.l1 = "Rosszabbul, Helen, sokkal rosszabbul. A kormányzó egy drága kurtizánnál szándékozik látogatást tenni, és nekem el kell kísérnem ôt, mint kuriózum. Megígérte az úrnôjének, hogy egy igazi magánembert, kalandort és mindenes tengeri kutyát hoz magával. Szóval unalmas beszéd, túlárazott bor és unalmas nemesek várnak rám.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Épp ellenkezôleg, meghívás egy kellemes társasági eseményre, amelyet egy úri hölgy vezet. Ôexcellenciája meglepett azzal, hogy megkért, kísérjem el, de ôszintén szólva örülök, hogy a változatosság kedvéért elvonatkoztathatok a munkától.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Igen... tehát a félelmetes Charles de Maure kapitány beöltözik és úgy táncol majd, mint egy házi majom a szórakoztatásukra? Milyen édes! Van egy jobb ötletem. Vitorlázzunk fel és tûnjünk el innen. Ha kedvetek van egy hosszú, megérdemelt vakációhoz, hajózzunk el Isla Tesoro-ra. Ott mindig szívesen látnak minket. Napozás, fehér homok, régi barátok, rumos puncs, kikapcsolódás - amit csak akarsz.";
			link.l1 = "Nézze, ez mind fantasztikusan hangzik, és én szívesen... de majd késôbb. Megígértem a kormányzónak, hogy ez a dolog fontos az öregnek és...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "És mi van? Azt hiszed, hogy a nemesi véred egy fikarcnyit is jelent nekik? Lehet, hogy nem vagyok francia vérû, de mindent tudok az ô 'high society' jukról, és számukra Charles de Maure nem olyan kapitány, akit az emberek követnek és az életüket is rájuk bízzák. Ô nem olyan úriember, mint ôk. Az igazi úriemberek nem mennek a tengerre és nem harcolnak puskaporfüst ködében. Charles de Maure csak egy furcsa kiegészítôje az étkezésüknek. Mint egy háziállat leopárd vagy egy házi néger, aki öltözködni játszik! Egy díszes játék! Mióta hagyja magát ilyen bánásmódban részesíteni?!";
			link.l1 = "Helen, kérlek, nyugodj meg. Biztos vagyok benne, hogy a kormányzó megelégedésére és a jövôbeli jólétünk érdekében el tudok viselni néhány kellemetlen pillantást. Jó, ha vannak erôs barátaink. Elvégre ez könnyebb lesz, mint egy internátus vezetése! És ezek 'a semmirekellôk' nem mindig ilyenek. Még a felsôbb körökben is vannak méltó emberek... legalábbis elvileg.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Tökmindegy. (megsimítja a haját) De figyelmeztetlek titeket - kizárt, hogy belepréseljem magam egy díszes ruhába. Ha kényszerítesz rá, akkor a nadrágomban megyek. Nem érdekel, ha a Karib-tenger összes úrihölgye elájul a rosszallásától.";
			link.l1 = "Nem akartalak kényszeríteni. Nincs értelme, hogy mindketten szenvedjünk. Túl leszek ezen a partin, aztán elhajózunk Isla Tesoróra. Jutalomként félretettem egy láda kiváló spanyol madeirát a raktérben...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Oh ho ho, Charles! Azt mondod, hogy nem vagyok jó egy ilyen nagyra becsült társaságban? Hogy egy nadrágos lány tönkretenné az estédet? Milyen érdekes. Rendben, de ne felejts el úgy öltözni, mint egy fopi. A díszes ruhás majmok még egy kurtizán szívét is megérinthetik. Boldog elôadást!";
			link.l1 = "Helen, várj! Az istenit... nôk!";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Igen, megérdemeltünk egy kis pihenést. De a fenébe is, ha ezért díszes ruhába préselem magam. Mit gondolsz, meddig fognak eljutni a pletykák a férfinak és matróznak öltözött nôdrôl?";
			link.l1 = "Ah...nem hiszem, hogy ez egy jó ötlet. Hogy is mondjam... ez nem egy olyan esemény, amire a férfiak elhozzák a feleségüket vagy a tiszteletreméltó hölgyeket...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Há! Kurvák és romlottság! Egyszerûen csodálatos - szóval orgiára mész! Akkor miért nem mondtad, baszd meg? Szerencsés vagy, hogy nem vagyok egy féltékeny ribanc, és nem lôlek le ott, ahol állsz. Legalábbis most nem.";
			link.l1 = "Helen kérem, én csak elkísérem a kormányzónkat, ô kért meg rá, és nagyon kitartó volt ebben. Nem lesz kurtizánbaszás\nVárj, ez rosszul jött ki... úgy értem, kurtizánbaszás lesz... ó, az istenit! Csak tiszteletemet teszem!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Javaslom, hogy öltözzön fel divatosan, hogy 'tiszteletét tegye,' Captain de Maure. Ez egy elôkelô társaság, meg minden. Tiszta botrány, ha gallér és mandzsetta nélkül jelenik meg. Még egy orgiára is. Jó szórakozást.";
			link.l1 = "Helen, várj! Az istenit... nôk!";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Bilincs és gallér, kapitány. És talán csipke. Úgy hallottam, újra divatba jött. De mit tudom én!";
			link.l1 = "Ó, Helen, gyerünk!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Ezt nézd meg! Kedves kapitányom, hazatért az orgiáról!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "A helyi nemesek még mindig helyeslik az új majmukat? Azt mondják, hogy a tegnap esti teljesítménye legendás volt! Hajókon és kurvákon játszott, párbajra hívta ki a magas származású hercegeket? Megmagyaráznád, mi a fene folyik itt?";
			link.l1 = "Helen, hadd magyarázzam meg! Ez nem ilyen egyszerû. A fenébe is, sajnálom, de sosem gondoltam volna, hogy Madame Botot-nál kell éjszakáznom. Csak aludtam ott, igen, egyedül, esküszöm! És igen, nyertem egy fregattot egy kártyapartiban. Képzelje csak el!";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Hát akkor! Ön vagy egy nagy hazudozó, egy szent, vagy egy bolond. A szajhákról és a megnyert hajókról majd késôbb beszélünk - most pedig mesélj el mindent a párbajról, és arról, hogy miért pletykál mindenki arról, hogy kihívtál egy trónörököst?";
			link.l1 = "Nem egy trónörökös, csak egy gróf fattyúja. Ô egy nagyon befolyásos nemes fia, de Levi Vantadur gróf. Nézze, nem én kezdtem! Ô hívott ki elôször, és most meg kell nyernem a párbajt anélkül, hogy túlságosan megsebezném, hogy elkerüljem az apja haragját.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Oh, 'csak egy gróf fia' huh? Most komolyan beszélsz, Charles?! És ezt hogy fogjuk csinálni? Mi van, ha megcsal? Meg fog ölni téged!";
			link.l1 = "Ezért adott nekem a kegyelmes uram nemes másodperceket. Csak ôket fogom magammal vinni - ha a dolog balul sül el, legalább bizonyíthatom, hogy minden a párbajkódex és a törvények szerint történt. Arra kérlek, hogy vigyázz a fregattra, amíg távol vagyok.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Gyôzôdjünk meg róla, hogy jól értettem-e... Egy egész napot és egy éjszakát voltál távol, és nyertél egy kurvát és egy fregattot egy kártyajátékban. És most egy nemes kurvával fogsz harcolni, akit nem szabad megölnöd, miközben *Én* csak ülök itt és várok? Hogy kéne éreznem magam emiatt?!";
			link.l1 = "Helen, figyelj, minden jogod megvan rá, hogy haragudj rám, és nagyon sajnálom, de ez csak...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Tudod mit, elegem van ebbôl. Csak menj és csináld a dolgod! Majd én leporolom a kabinodat és kimosom a szennyesedet! Ne is hidd, hogy tiszta a levegô. Majd beszélünk errôl, ha ennek vége. Gondoskodom az új fregattjáról, nagyszerû de Maure kapitány, ne aggódjon. Ó, és de Maure kapitány, próbáljon meg nem meghalni... mert azt tervezem, hogy utána én magam ölöm meg magát. Most pedig bocsásson meg, bezárom magam a kabinomba, és megiszom egy üveg finom madeira-t, amit a kabinjában találtam.";
			link.l1 = "Helen, hadd magyarázzam meg! Baszd meg... Már megint itt tartunk!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Úgy hallottam, a legújabb párizsi divat szerint az urak inkább kártyapartiban nyernek hajókat és kurtizánokat, minthogy megvennék ôket! Sôt, ha valaki jó benyomást akar kelteni magáról, párbajra kell hívnia elôzô tulajdonosaikat. Ezúttal mi a fenébe keveredtél?!";
			link.l1 = "Helen, ez nem ilyen egyszerû. A fenébe is, sajnálom, de soha nem gondoltam volna, hogy Madame Botot-nál kell éjszakáznom! A tegnap este egy kimerítô és brutális eszmei harcba torkollott. És igen, nyertem egy átkozott fregattot kártyán. Képzeld el!";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Szép volt. Úgy érted, hogy egy kurtizánt is nyertél? És a fregatt, amit nyertél, mit tettél fel ellene? Nem a mi hajónk, nem tudtad volna...";
			link.l1 = "Muszáj volt. Nézd, most már mindegy, végül is én nyertem. Az ellenfelem párbajra hívott ki, és csalással vádolt. Ô egy rendkívül befolyásos nemes fattya, de Levi Vantadur gróf. Ami azt jelenti, hogy mindent meg kell tennem, hogy ne öljem meg, vagy ne bántsam túlságosan.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Vajon ô is ezt fogja tenni? Elment az eszed, Charles? Kockáztatni a hajódat, kockáztatni az életedet egy másik nô miatt?! Tényleg megéri? Semmit sem jelentek neked?!";
			link.l1 = "Helen, nincs okod féltékenykedni, esküszöm. Csak úgy megtörtént. Meg kellett tennem, és a kormányzó nemes tiszteket biztosított nekem másodmagammal, hogy minden a szabályok szerint történjen. Nem vihetlek magammal sem téged, sem az embereink közül senkit. Kérlek, vigyázz a fregattra, amíg távol vagyok.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Egyszerûen nagyszerû! Elôször is, elmész egy orgiára idegen nôkkel, és másnap reggel megjelensz, és még csak le sem vágtalak ezért. Most meg azt mondod, hogy majdnem elvesztettük a hajónkat egy kártyapartiban, de nyertünk egy kurtizánt! És most meg azon vagy, hogy harcolj érte 'honor' milyen magas származású kurva ellen, akit még megölni sem szabad! Hogy kellene nekem mindezzel kapcsolatban éreznem magam? Mondd csak!";
			link.l1 = "Helen, figyelj, minden jogod megvan ahhoz, hogy dühös légy rám, de hadd magyarázzam meg...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "Tudod mit, elegem van ebbôl. Menj, és vívd meg az átkozott párbajt. Majd én vigyázok az új fregattodra, nagy de Maure kapitány, ne aggódj. Most pedig bocsásson meg, bezárom magam a kabinomba, és megiszom egy üveg finom madeira-t, amit a kabinjában találtam. De ha valami történik veled, Istenre esküszöm, hogy pokoli tüzet zúdítok erre a városra, és eltemetem ezt a bordélyházat és szeretett excellenciád palotáját!";
			link.l1 = "Helen, minden rendben lesz, bízz bennem... Várj, hová mész?! Bassza meg! Már megint itt tartunk...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, van egy kis magyarázkodnivalód. Elmondanád, hogy mi a fene történt? Nem állítottam be megfelelô ôrséget, a fiúk pedig ittak... néhány gazember megtámadta a hajónkat, és megkötöztek minket, miközben aludtunk. Aztán a mocskos söpredék elkezdte kérdezgetni, hogy meddig mennél el a megmentésemért. Végül bezártak a raktérbe. Már nem is számoltam, hány napot vártam!";
			link.l1 = "Az a szemétláda meg akarta hálálni a szégyent, amit okoztam neki. Attól féltem, hogy veled is tesz valamit! Hála Istennek, jól vagy!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Gondolom, tenned kellett valamit, hogy visszaszerezz engem? Valami rosszat, igaz?";
			link.l1 = "Csak az számít, hogy újra velem vagy. Cserbenhagytalak, Helen. Annyira sajnálom! Remélem, hogy a szívedben megtalálod a megbocsátást!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Már megtettem. Sok idôm volt átgondolni, amit mondtam... Én is sajnálom, Charles. Bárcsak ne vettem volna túlságosan magamra a márkival való kapcsolataidat. Aznap éjjel rendes ôrséget állítottam volna, résen lettem volna. Ah! Én csak egy haszontalan nô vagyok!";
			link.l1 = "Ne mondogasd ezt, a múlt az múlt. Szeretlek, és soha többé nem hagylak el. Megígérem!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Azt hiszem, jobb, ha nem tudom, hogy pontosan mit tettél, igaz? Rendben, újra együtt vagyunk, és ez a lényeg.";
			link.l1 = "Nincsenek titkaim elôtted. Elmondom neked...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Eltelt egy kis idô...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Micsoda zûrzavar... Tudom, hogy nem volt más választásod, de hogyan magyarázd meg ezt Di Lu Parkesnek és a barátainak? Úgy értem, most már bûnözô vagy!";
				link.l1 = "Én választottam ezt az árat, de tényleg nem volt más választásom. Ne aggódj, megtalálom a módját, hogy helyrehozzam a dolgot, és helyreállítsam a jó hírünket. Ha nem, akkor mindig szívesen látnak minket Isla Tesoro-ban! Megoldom, ha velem tartasz.";
			}
			else
			{
				dialog.text = "Micsoda történet, Charles... Azt hiszem, nem volt más választásod, de mi lesz ezután? Az az angol rendbe hozza a dolgokat, vagy háború lesz? Biztos, hogy nem akarsz eljönni Basse-Terre-be, hogy tanúja legyél, ahogy megbilincselik azt a fattyút?";
				link.l1 = "Tudod, Helen, két héttel ezelôtt még soha nem hagytam volna ki. De ma azt mondom, hogy a pokolba vele! Már nem is érdekel a jogos büntetése. Újra együtt vagyunk, csak ez számít!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Tudod, hogy mindig veled leszek. Ha! Ez nem olyan, mint amikor elôször kerültünk nyakig a fenékvízben. Újra meg fogjuk csinálni.";
				link.l1 = "Ez igaz. Vitorlát bontunk, drágám! A horizont vár ránk!";
			}
			else
			{
				dialog.text = "Tetszik a gondolkodásod, Charles! Nincs több nemes: Franciák, britek, spanyolok - mindegy. Azt hiszem, kiérdemeltük a vakációt!";
				link.l1 = "Egyetértek. Csak te és én! Nincs többé kormányzó és magas származású fattyú!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Igenis, kapitány!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Jól hangzik! Megyek, szólok a fiúknak, hogy ideje horgonyt vetni! És Charles...";
				link.l1 = "Tudom, Helen, tudom. Mindjárt csatlakozom hozzád.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, megcsináltad! A portugálok mindent elmondtak! Micsoda történet!";
			link.l1 = "Hála Istennek, hogy élsz, Helen! El sem tudod képzelni, mennyire örülök, hogy újra látlak!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Ha már itt tartunk. Megígérted, hogy elmondasz valamit, emlékszel? Valami nagyot és bonyolultat. Itt a lehetôség, kapitány. Mi a fene történt?!";
			link.l1 = "Szeretlek, Helen. A többi lényegtelen.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Igen, ez hasznos volt, de... A fenébe, én is, Charles. Én is szeretlek. Istenem, annyira hiányoztál!";
			link.l1 = "Nekem is. Gyere velem, nem hagylak itt ma este, még akkor sem, ha leszakad az ég erre a nyomorult városra. Soha többé nem hagylak el. Soha többé.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Azt hiszem, jobb, ha nem tudom, hogy pontosan mit csináltál, igaz? Igen, újra együtt vagyunk, és ez a legfontosabb.";
			link.l1 = "Nincsenek titkaim elôtted. Elmondom neked...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Eltelt egy kis idô...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Hihetetlen! Azt mondtad, hogy Franciaország és Anglia miattam áll a háború küszöbén?";
			link.l1 = "Nem, Helen. Azért, mert nagyon rosszul ítéltem meg a dolgot. De vissza kellett hoznom téged, és mindent helyre kellett hoznom.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Ez mind nagyon megható és romantikus, még azt is kész vagyok elfelejteni, hogyan kezdôdött az egész. Majdnem kész. De most komolyan, azért tartóztattak le, mert a portugálok rosszul adták meg az átkozott brigantin nevét?";
			link.l1 = "Épp ellenkezôleg, ô adta meg a helyeset! Bárcsak tudnám, hogyan és miért sikerült ezt összehoznia. Egyébként, hol van maga az ember?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Elment. Rögtön azután, hogy idehozott. Nem akartam használni a 'hospitáliát' a kurtizántól, amit megnyertél, ezért Bartholomewval béreltem egy szobát nekem. Kifizette, és szó nélkül eltûnt. Igazából várj, nem, de azért hagyott neked egy levelet!";
			link.l1 = "Egy levelet? Bartholomewtól, a portugáltól? Ez újdonság. Nem tetszik, hogy ez hova vezet...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Rendben, itt hagyom, hogy elolvassa, amíg én megyek és köszönök a fiúknak. Biztos aggódnak. Soha nem gondoltam volna, hogy valaha is hiányozni fognak azok a komor lógós pofák! Addig is próbálj meg nem belekeveredni egy újabb katasztrófába!";
			link.l1 = "A fenébe... Még mindig nem hiszem el, hogy visszahoztalak!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Fehér homok, tiszta zöld víz, te, én és egy jó bor - Charles, ez annyira romantikus! Gyakran kellene ilyen sétákat tennünk együtt, rendben!";
			link.l1 = "Örülök, hogy tetszik. Azt hiszem, most már több idôt kellene szakítanunk erre.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, miben sántikálsz, és miért térdelsz? Ez olyan hirtelen jött...";
			link.l1 = "Helen, szeretlek. És veled akarok élni minden napot, ami nekem fentrôl adatik. Ezért itt és most, e tengerrel és éggel szemben arra kérlek téged - Helen Beatrice Sharp -, hogy add meg nekem azt a megtiszteltetést, hogy velem állj az emberek és Isten elôtt, amíg a halál el nem választ. Én, Charles de Maure, Chevalier de Monper, kérdezem öntôl - hozzám jön feleségül?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Tudod, sosem szerettem ezeket a formaságokat, de veled vagyok a világ végéig. És ami a kérdésedet illeti, a válasz... ó, bocsánat, kiborultam!";
				link.l1 = "Nem baj, ez csak bor, és sosem szerettem ezt az inget...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, természetesen igen! Igen, igen, és még egyszer igen!!! De remélem, nem tervezed, hogy visszavonulunk valami poros családi kastélyba, ahol életünk végéig répát termesztünk?";
				link.l1 = "Nos, van egy családi kastélyunk, de nem poros, és nem is fogunk ott maradni. A mi életünk a szabadság és a horizont a kezünkben!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Akkor tósztot mondok rád, kapitányom, férjem, és az esküvônkre!";
			link.l1 = "Rád, szerelmem! És a közös jövônkre, annyi minden vár ránk!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Aztán tószt rád, kapitányom, férjem, és az esküvônkre!";
			link.l1 = "Rád, szerelmem! És a közös jövônkre, annyi minden vár ránk!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Szóval, Benoit apát visszatért, és készen áll, hogy feleségül vegyen minket. De csak hogy tudd, még egy ilyen alkalomra sem fogok ruhát viselni! Gondolod, hogy ha nadrágot viselek, az nagy feltûnést kelt?";
			link.l1 = "Helen, én bármilyen öltözékben szeretlek, majd túlteszik magukat rajta. Elôször is konzultálni akartam veled a vendégekrôl és a szertartásról.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Igen, van egy probléma - a legtöbb legjobb barátunk, akikkel szívesen megosztanánk ezt a napot, nem léphet be a városba, nemhogy a templomba. Ezért - házasodjunk meg itt, az összes fontos emberrel, ahogyan az várható volt, aztán hajózzunk át Isla Tessoróra, és ünnepeljük meg rendesen az igazi barátainkkal, mit gondolsz?";
			link.l1 = "Nekem jól hangzik! Beszélek Benoit apáttal, de ki kell küldenünk a meghívókat, és még...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Nyugodjon meg, kapitány. A kedves jövendôbelije majd átveszi a teher egy részét! Mindent elintézek Isla Tesorón, és írok a barátainknak, csak mondd meg: mekkora esküvôt szeretnél?";
			link.l1 = "Csak te, én és a legközelebbi barátaink. A sok hivatalos csicsergés után itt Martinique-on egy kis ôszinte meghittségre vágyunk majd.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Mindenkinek emlékeznie kell erre a napra! Hívjatok mindenkit! Senki sem maradhat ki!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Hangulatos és barátságos - olvasol a gondolataimban! El kell látogatnunk Sharptownba, és én mindent elôkészítek. Azt hiszem, ötven hordó rum és két tucat hordó bor elég lesz. Továbbá az ételekhez és a szórakozáshoz háromszázezer darab nyolcezerre lesz szükségünk.";
			link.l1 = "Emlékeztess - miért nem intézed újra a hajó pénzügyeit? Majd én elintézem az egészet. Csak egy gyors látogatás az apátnál, aztán kihajózunk Sharptownba.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Szóval, olyan bulit akarsz tartani, mint az igazi tengeri farkasok? Rendben! El kell látogatnunk Sharptownba, én pedig mindent elôkészítek. Komolyan fel kell majd raktároznunk - szerintem száz hordó rum és ötven hordó bor elég lesz. Az egyéb kiadásokra pedig legalább ötszázezer nyolcezret.";
			link.l1 = "Meghívod a Parti Testvérek egészét? Ó, a pokolba is, hát rajta! Majd én beszerzem az ellátmányt. Csak egy gyors látogatás az apátnál, és már indulunk is Sharptownba.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, én elintézem a rakodást, aztán kiosztom a meghívókat a bárónak, és megegyezem a kocsmárossal. Nem tarthat túl sokáig.";
			link.l1 = "Ne aggódj, kedvesem, majd elfoglalom magam jövedelmezô munkával... Vagy csak szundikálok egyet a homokban. Nem gondoltam volna, hogy könnyebb lesz megrohamozni Tortugát, mint megtervezni a saját esküvômet, az isten szerelmére.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Több óra is eltelt...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Kipihented magad, Charles? Van egy jó és egy rossz hírem. A rossz hír az, hogy a helyiek annyira jól érezték magukat a múlt héten, hogy véletlenül felgyújtották azt az átkozott 'Old Woodpecker' tavernát! Itt a jó hír, a báró megígérte, hogy mire visszaérünk, nagyobbra és jobbra építik újjá, mint volt. Elintéztem, hogy el tudjunk indulni.";
			link.l1 = "Remélem, hogy a mi esküvônk nem hagy hasonló hamukupacot a városban, amikor elmegyünk. Ez rohadt nagy kár, nekem nagyon tetszett a 'Old Woodpecker'-ben - hangulatos, meghitt, csak egy halvány hányás- és tölgyfaillat! Hát igen, drágám, igazad van - mennünk kell.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Jan már a városban van Gladysszel, el tudod képzelni? Nem gondoltam volna, hogy valaha is eljönnek az esküvômre! Ó, édes Jézusom! Még amikor abban a szörnyû indiai templomvárosban voltunk, akkor sem féltem annyira, mint most!";
			link.l1 = "Minden rendben van, drágám, minden rendben van. Én is aggódom - az idegesség normális. Mivel a vendégek már megérkeztek, el kell mennem Benoit atyához, hogy megtudjam, mikor kezdôdik a szertartás.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Átkozottul hosszú és nehéz nap lesz... Meglátogatom Jant és Gladyst.";
			link.l1 = "Örülök, hogy el tudtak jönni. Az öreg Svensson úgy szereti önt, mint a saját lányát, McArthur asszony pedig még jobban. Jó, hogy ma itt vannak. Menj, és ne aggódj - minden rendben lesz.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Igen.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Igen.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Igen.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Én, Charles Henry de Maure, chevalier de Monper, feleségül veszlek téged, Helen Beatrice Sharp, a mai naptól fogva, jóban és rosszban, gazdagságban és szegénységben, egészségben és betegségben, amíg a halál el nem választ minket egymástól. Isten szent törvénye szerint, Isten jelenlétében teszem ezt a fogadalmat.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Én, Helen Beatrice Sharp, téged, Charles Henry de Maure-t, férjemül fogadlak, hogy a mai naptól fogva jóban-rosszban, gazdagságban és szegénységben, betegségben és egészségben, amíg a halál el nem választ minket egymástól. Isten szent törvénye szerint, Isten jelenlétében teszem ezt a fogadalmat.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Ámen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Helen Beatrice de Maure, Madame de Monper - ó, ez jól hangzik, drága férjem!";
			link.l1 = "Nem hallottam még jobbat, feleségem!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Tudod - gondoltam, hogy ez nem változtat semmin, és valószínûleg nem is változtatott -, eddig is szerettelek, és veled akartam élni a hátralévô napokat, de ez a nap, ez a szent szertartás... Igazán boldog vagyok, Charles! Olyan boldog, mint még soha, és nézd meg Gladyst és Jant - ragyognak! Annyi boldog arc van körülöttük! Egyébként - itt az ideje, hogy körbejárd a vendégeket, és elfogadd a gratulációkat. Gyere vissza, ha végeztél, ne felejtsd el - várnak minket Sharptownban.";
			link.l1 = "Azonnal megyek, drágám! Egy csókot, mielôtt elmegyek!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Szia férjem, beszéltél már a vendégekkel?";
			link.l1 = "Még nem, légy türelmes, feleségem, hamarosan visszajövök.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Igen, még soha nem hallottam ennyi gratulációt egyszerre. És tudod mit - szerintem a legtöbbjük ôszintén beszélt!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Igen, ezek a nemesek meglepôen ôszinték - bevallom, én több hamisságra és képmutatásra számítottam. Vagy csak annyira boldog vagyok, hogy nem veszek észre semmit. De végül is a barátaink Sharptownban várnak ránk! Mikor hajózunk ki?";
			link.l1 = "Most rögtön. Sasokon' szárnyakon repülünk egyenesen egy baráti lakomára. Remélem, a feleségem, nem bánja, ha ezt az éjszakát a kabinunkban tölti?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Ó igen, férjem, te olyan romantikus vagy! És ne rángatózz így, most már jogom van nyilvánosan megcsókolni téged... Igen, most már mehetünk!";
			link.l1 = "Navigátor, irány Sharptown, és ne zavarj minket semmiért! Nem érdekel, ha egy szellemflotta közeledik felénk!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Ó, drága férjem, olyan boldog vagyok! A mai egy csodálatos nap...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Gyere, Charles! Ez a hazug még azelôtt halott lesz, hogy a földre érne!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Jól vagyok, Charles, minden rendben. Hogy van Nathan?";
			link.l1 = "Annyi vér... Dannie, lélegzik? Látom, hogy lélegzik!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Gyorsabban, drágám, ne vesztegesd az idôt!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Charles, jól vagy? Micsoda vérfürdô! Sajnálom, az emeleten ragadtunk, egy tucatnyi ilyen szemétláda volt, úgyhogy elôször velük kellett foglalkoznom!";
			link.l1 = "Semmi baj, elintéztem. Örülök, hogy végre befejezhettem a történetet Jacques-kal... végre. Megkapta, amit megérdemelt.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Rendben, kedvesem, fejezzük be itt és menjünk vissza. Nem tudok nem gondolni Nathanre, hogy van? Ô védett meg attól a golyótól!";
			link.l1 = "Igazad van, édesem, én is aggódom. Menj csak, mögötted vagyok.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Megtaláltuk Marcust! A raktérben volt, megkötözve és eszméletlenül.";
			link.l1 = "Életben van?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Ne aggódj, kedvesem, Tyrex báró tovább fog élni, mint mi. Most ébredt fel, és máris zsibong, folyton rumot, a szablyáját és a hidat követeli - ebben a sorrendben.";
			link.l1 = "Ez a mi öreg Marcusunk! Hadd pihenjen egy kicsit a szegély, amíg mi itt befejezzük, aztán visszamegyünk a partra.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Annyira sajnálom, drágám... Elôször hûséges barátunk, Tichingitu, most meg Gino... Barbazont egy tucatszor meg kellett volna ölni mindazért, amit tett!";
				link.l1 = "Sajnos én csak egyszer tettem meg. Én is rosszul érzem magam... De gyôztünk, és soha többé nem fog bántani senkit.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Szörnyen érzem magam Gino miatt, Charles! Amikor megtudtam, nem hittem el! Hogy vagy, szerelmem?";
					link.l1 = "Én sem tudom elhinni... micsoda út ez... Nem gondoltam volna, hogy ez a nap így fog alakulni.";
				}
				else
				{
					dialog.text = "Vajon a jövô történészei megírják majd a nagy csatát a Privát-öbölben? A napról, amikor a Parti Testvérek bárói nyílt csatában találkoztak - fogadok, hogy a spanyol Costa Garda hála könnyeit törölgetik! De, ismét gyôztünk! Barátaink élnek, ellenségeink pedig halottak - dicsôséges nászajándék!";
					link.l1 = "Igen, micsoda ünnep, de megcsináltuk, angyalom! Megcsináltuk.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Gyerünk, Dannie talált nekünk egy házat itt a város szélén, nem akarok most visszatérni a hajóra, amíg nem takarítottuk ki. Leülünk és iszunk azokra, akik nem jutottak el.";
			link.l1 = "Igen, Helen, menjünk.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Olyan rosszul érzem magam Gino miatt, Charles! Amikor megtudtam, nem hittem el! Hogy vagy?";
				link.l1 = "Én sem tudom elhinni... micsoda halál... Nem gondoltam volna, hogy ez a nap így fog alakulni.";
			}
			else
			{
				dialog.text = "Láttad Sólymot? Dannie kiengedett, amikor Gino azt mondta 'a veszély elmúlt'. Örülök, hogy minden rendben van. A barátaink élnek, az ellenségeink pedig halottak - dicsôséges nászajándék!";
				link.l1 = "Én is, drágám. És gyôztünk. Barbazon halott, a bárók összegyûjtik, ami a legénységükbôl megmaradt. A harcnak vége.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, látom, alig állsz még, de meglátogattam a kocsmát, és nem fogod elhinni, mit hallottam a csapostól.";
			link.l1 = "Igen, Jantól hallottam, ô is ott volt. Nekem úgy tûnik, hogy a mi kedves indiánunk hadiösvényre lépett. Sétáljunk el a Sabo-Matila-öbölbe, néhányan látták, hogy abba az irányba távozott.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Istenem! Ez a szellem, Tichingitu! Hú, de jót röhögök! Miért nem veszünk át mi európaiak is egy ilyen szokást?! Jaj Charles, majdnem elaludtál a lábadon! Gyere, Dannie talált nekünk egy házat itt a külvárosban - pihenned kell egy kicsit.";
			link.l1 = "Menjünk... Azt hiszem, már elaludtam azon a parton.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... Semmi baj.";
			link.l1 = "Jó hallani.";
			link.l1.go = "exit";
			link.l2 = "Tényleg?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Igen.";
			link.l1 = "Jó hallani.";
			link.l1.go = "exit";
			link.l2 = "Gyerünk, látom, hogy valami zavar téged!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Teljesen jól vagyok, hagyjuk!\nCharles, menj a pokolba! Utálom a dungeonokat, utállak téged, és utálom ezt az átkozott szigetet! Azonnal vigyél ki innen!\nBocsánat... Tényleg nem szeretem a börtönöket, ne érj hozzám!";
			link.l1 = "Bocsánat, bocsánat. Mindannyian félünk valamitôl.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "AAAA! Engedj ki minket innen! Charles, csinálj valamit!";
			link.l1 = "Szedd össze magad!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Kapitányom, az ellenség áttörte a hajótestet a második fedélzeten, és partra szállt egy csapat. Az egész hajón harcok dúlnak, és az ágyúszemélyzet nagy része kiesett! Meg kell mentenünk a legénységet és Hercule-t! Maga megy, vagy menjek én?";
			link.l1 = "Ezúttal én magam megyek, Helen! Vedd át a hajó irányítását és vigyél ki minket innen!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Igenis, kapitányom. Nem hagylak cserben, és légy óvatos!";
			link.l1 = "Tudom, Helen. És te is légy óvatos!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Gyôzelem, kapitányom! A partraszálló csapat megsemmisült, az ellenség a visszavonulást választotta, és dél felé vette az irányt. A hajó állapota elfogadható. A legénység él: " + GetCrewQuantity(pchar) + " emberek. Jelentés elkészült!";
			link.l1 = "Köszönöm, Helen, és mi...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Vetkôzz le, gyôztes, a jutalmad az, hogy azt csinálsz velem, amit csak akarsz!";
			link.l1 = "Uh...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "Gyerünk!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "Ó, szia, Hercule. Sajnálom, hogy pont rosszkor ért minket! De a fenébe is, örülök, hogy életben vagy és valaki más vérével vagy borítva - természetes állapot neked, mi?!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Hát, Helen, te aztán nem vagy semmi!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "Még el sem kezdtem, kapitányom. Ünnepelhetünk?";
			link.l1 = "Nem kell meggyôzni!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Ne nézz oda, ne nézz oda, ne nézz oda... Ez egy másik világ, kapitányom! Ez nem lehet ilyen!";
			link.l1 = "Azt hiszem, ez már a mi világunk, drágám. És igazad van, ne lógjunk itt...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Attól tartok, ez a járvány megviseli a lányaidat, Rodrigo. Foglald le ôket kötéssel vagy valamivel!";
			link.l1 = "Ez a beszélgetés nyilvánvalóan nem vezet sehova. Megegyeztünk, hogy holnap elmegyünk a templomba. Imádkozni... természetesen.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Büszke vagyok rád, szerelmem!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Nos, Charles...";
			link.l1 = "Mi jár a fejedben, Helen?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "Az, hogy a Karib-tenger legbotrányosabb párja két egész szigetet birtokol! Az én kalózparadicsom, Isla Tesora és a te ígéret földed - mit gondolsz, meddig bírják ki, ha a civilizáció végre eljut Nyugat-Indiába?";
			link.l1 = "Elég sokáig ahhoz, hogy egy életen át kitartson, drágám. És utána? Nem tudjuk irányítani, hogy mi történik akkor. Majd mások elmesélik a történetünket. A legfontosabb, hogy te és én itt és most, együtt és boldogan vagyunk.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Ha már a boldogságról beszélünk... Most felmegyek az emeletre: Meg kell gyújtanom a gyertyákat, be kell ágyaznom, talán írni a naplómba...";
			link.l1 = "Én'még egy kicsit itt maradok, aztán feljövök, hogy segítsek neked 'ágyazni.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Ne tartson túl sokáig...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "Tényleg ennyire elfoglalt vagy? Kár, de megértem. Majd találok valami mást, amivel elfoglalhatom magam.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "Jó, hogy emlékszel. El akartam mondani, hogy nagyon hálás vagyok. Nem minden nap menti meg valaki az embert a... tudod mitôl. Menjünk, igyunk valamit. Én fizetek.";
			link.l1 = "Helen... Mit fog mondani Gladys?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Nagyon vicces, Charles. Gyerünk, és ne idegesíts!";
			link.l1 = "Ez egy randi?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "Jövök, nem kell idegeskedni.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "Ha-ha! Csak szeretnéd! Teljesen le kéne rúgnom magam!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "Így már jobb.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "...sok erénye volt, de nem bírta az alkoholt. Így ismerkedtünk meg.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "...apám ragaszkodott a katonai szolgálathoz. Én engedtem, és elmentem Párizsba egy ajánlólevéllel. De soha nem jutottam el a kijelölt címre, és mûvész lettem.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ah, most már értem, milyen erényekrôl beszélsz. Mi volt a neve?";
			link.l1 = "Lulu.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Lulu... Ezekkel a történetekkel teljesen tönkretetted nekem Párizst. Azt hittem, hogy a nagyszerû élet városa, de ez csak úgy hangzik, mint valami nagy, puccos bordélyház.";
			link.l1 = "Elítéled a bordélyházakat?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Igen, kapitány, és nem értem azokat a férfiakat, akik látogatják ôket.";
			link.l1 = "(a bögrébe bámulok)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(szörnyen köhögök)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Uh... mindenkinek a sajátja... Azt hiszem.";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(nevetés) Ha! Látnod kellett volna az arcodat! Megijedtél? Emeljünk még egyet! Párizsra!";
			link.l1 = "Párizsra!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(nevetés) Y-you?! Egy mûvész? Szóval az angol flotta szépsége és büszkesége, az erôszaktevô és csak egy szemétláda Donovan egy párizsi mûvész keze által halt meg? Á, kár, hogy nem a makulátlan jabotját viselte a beszálláshoz, és nem verte meg azt a söpredéket bottal!";
			link.l1 = "Igen, nagyon sajnálatos. A jabot csak véletlenül a mosásban volt aznap.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(nevetés) Nos, köszönöm, Charles. Nem tudom, hogy a ma este hátralévô része hogyan fog alakulni, de az este már így is nagyszerû volt. Talán még azt is megengedem, hogy megfestse a portrémat. De vigyázz, nem olyan stílusban, mint ahogyan a párizsi lányokat festetted!";
			link.l1 = "Ha! Persze csak ha beleegyezem, hogy megfestem magát.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "Bocsásson meg, kapitányom, hallgassuk meg a kalandjait és a nemes... kurtizánok életét mindkét nembôl. Cápa harapj meg, soha nem fogom elhinni, hogy nem találtál valami érdemlegesebb elfoglaltságot az idôddel! Azt se merészeld nekem mondani, hogy csak vásznakat maszatoltál és apuci pénzét pazaroltad. Egy napot sem éltél volna túl velünk, ha ez igaz lenne.";
			link.l1 = "Voltak... más elfoglaltságaim.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "Összekötöttem az udvari életet a katonai szolgálattal, de nem... hehe, persze nem egészen úgy, ahogy apám akarta. Néhány szökés az ablakon át és egy verekedés - és összebarátkoztam a gárdistákkal. És természetesen sok mindent felszedtem, megkeményítettem a testemet. Az idôsebb bajtársak megtanítottak, hogyan kell ütést bevinni, páncélt viselni, kardot kezelni, és rendesen pihenni. Az utóbbi persze különösen jól jött nekem. Nem fogod elhinni, de nem mindenki tud reggeltôl délig kardot lóbálni, majd déltôl másnap reggelig inni.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "Azt hiszed, könnyû volt a fôvárosban egy rossz hírû, üres erszénnyel rendelkezô nemesnek, aki már az elsô napon elveszítette apu ajánlólevelét? Meg kellett erôsödnöm, és nem hagynom, hogy bárki kigúnyoljon. Az otthoni vívóleckéket nem felejtettem el, és minden oldalpillantásra párbajjal válaszoltam. Aztán tényleg belevágtam. Mégsem öltem meg senkit, és sikerült elhagynom Párizst, mielôtt összefutottam volna egy tapasztalt vívóval, aki végzett volna velem.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "Sok idôt töltöttem a temetôkben. Ne gondolj semmi rosszra - ez csak egy népszerû hobbi volt a társasági körömben. Bátorságból éjjel elmentünk egy temetôbe, üres üvegeket tettünk a kerítésre, és idôzített idôzítôvel lövöldöztünk rájuk. Egy éjszaka alatt száz golyót és egy láda pezsgôt pazaroltunk el. Most persze szégyellem az ilyen viselkedést, de akkor a gyôztes egy szolid fônyereményt vitt el, és kapott néhány... szívességet a nôi oldalról. Mindent felhasználtam - még a puskaporos keverékekkel is bíbelôdtem egy kicsit. De hogy miért nem jutott eszébe egyikünknek sem megtanulni, hogyan kell papírpatront készíteni - sosem fogom megtudni.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "Tanultam, méghozzá elég szorgalmasan - még ahhoz is közel voltam, hogy bejussak a Sorbonne-ra. Dolgoztam egy irodában, amíg unalmassá nem vált, és általában véve - mindenbôl csináltam egy kicsit. A tanár, apám régi barátja, inkább a gyakorlatot részesítette elônyben, mint az elméletet, így minden oldalról láthattam Párizst, és különbözô emberekkel beszélgethettem: a banditáktól a nemesekig. Mindez végül is jól jött itt.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "És... ennyi? Tehát még mindig van benned valami, kapitányom. Valami, amit még nem láttál magadban. Egészségedre!";
			link.l1 = "Jó tósztot!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "Meséld el a történetedet, Helen. Az én fôvárosi kalandjaim elhalványulnak ahhoz képest, hogy egy harminc év alatti lány egy schoonert irányít száz emberrel a fedélzeten.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "Harminc alatt, mi, Charles? Egy ilyen erôs megjegyzésért a következô kört neked kell kifizetned! Az összes emberem meghalt, és már nem parancsolok szkúnernek. Ôszintén szólva, nem tudom, hogy fogok-e még valaha parancsnok lenni.";
			link.l1 = "Sajnálom, Helen. Nem akartalak megbántani. De miért gondolja, hogy a kapitányi karrierjének vége?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Mert a legénységem halott, és egy másik legénység soha nem fog elfogadni. Eh! Jól van, kapitányom, sokat meséltél az életedrôl, most én jövök! Az igazság nem ennek a bögrének az alján van, úgyhogy hagyjuk a rejtélyt.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "Az én esetem, Charles, egyedülálló. Apám az egyik legjobb tengerész volt errefelé, az Erdôördög nagyra becsülte, a legénysége imádta, engem pedig jobban szeretett, mint magát az életet.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Ha ezek közül akár csak egyet is elvennél, akkor vagy Londonba küldött volna, hogy ott éljek... civilizáltan, vagy itt hagyott volna elsorvadni, mint az anyámat. Eleinte minden remekül mûködött: szabadságot akartam, igazi szabadságot, Charles, és egy hadihajó ügyes irányítása egy hûséges legénységgel pontosan ezt adja. És apám mindent megadott nekem, amit csak tudott. Tizenkét évesen kimentem vele a tengerre, az elsô hat hónapot azzal töltöttem, hogy patkányokat kergettem a raktérben, és csak ezután engedték, hogy a matrózok között dolgozzak.";
			link.l1 = "Sean MacArthur csinált belôled hajópatkányt? Sajnálom, Helen, de ebbôl már nincs visszaút! Hogyan fogadott el a legénység?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Nos, talán egy kicsit túlzok a jó sztori kedvéért? Az apám legénysége elfogadott engem; jó embereket gyûjtött össze. De azóta félek... a rakodótértôl és általában minden kis sötét helytôl. Ha! Svensson majdnem megölte apámat, amikor rájött!";
			link.l1 = "Ô fontos neked. Nyilvánvalóan szerepet játszott a sorsodban, nem kevesebbet, mint Sean.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Igen, az. Az összes báró egyenesen azt mondta apámnak, hogy bolond, de az Erdôördög volt az, aki jóváhagyta, és kezet fogott vele, miután megdöntöttem a legénység árbocmászási rekordját. Az a pillanat örökre megmarad bennem: a legénység diadalmas kiáltása és, bármerre néztem, a tiszta tengeri horizont. És apám elismerô pillantása, nem láthattam, de teljes szívembôl éreztem.";
			link.l1 = "A diadalom azzal ért véget, hogy az elsô napon, útban Guadeloupe felé leestem a kötélzetrôl.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1 + " A kormányosom, Deluc is sokatmondóan nézett rám."
			}
			link.l1.go = "drinking_my_background_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ah-ha-ha-ha! El tudom képzelni! Ne aggódj, az már régen volt, most már igazi tengeri farkas vagy!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "A mi gyôzelmeinkre!";
			link.l1 = "Halljuk, halljuk!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... Aztán fokozatosan emelkedtem a ranglétrán, a kapitány asztalánál szolgáltam a tanácskozásokon apámmal és a tisztekkel. Sokat tanultam. Tizenöt éves koromtól kezdve hadjáratokra vittek, és már az elsô csatámban megöltem egy embert. Undorító hadjárat volt; nem hétfôn kellett volna kihajóznunk... Tényleg nem kellett volna!";
			link.l1 = "Tizenöt évesen? Megijesztesz, Helen.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "Nem is értettem, mi történt. A holland kereskedônek megvolt az elôôrse - a Társaság zsoldosai. Úgy döntöttek, hogy bátran játszanak, és ellentámadásba lendültek a poop fedélzetünkön. Én pedig, a bolond, minden életféltés nélkül kidugtam szôke fejemet. Azonnal kaptam egy pisztolycsapást. De egy pillanattal azelôtt még sikerült beledöfnöm a pengémet valami bolondba a századból.";
			link.l1 = "Te jó ég, mi lesz Sean-nal? Hogyhogy nem rúgott partra azután?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "Apám sem úszta meg sértetlenül azt a csatát, és a betört, buta fejem látványa bizonyára nem segített. Lassan hanyatlani kezdett, és valószínûleg rajtam kívül senki sem vette észre. Aztán eltûnt. A végakarata szerint én örököltem a Szivárványt a legénységével együtt, és annyi pénzt, hogy egy évig a hajót a felszínen tarthassam.";
			link.l1 = "És a legénység elfogadta magát kapitánynak?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "Nem tündérmesében élünk, kapitányom. Néhányan ellenségesen fogadták apám akaratát - a dolgok kellemetlen fordulatot vettek\nHa legalább egy matróz elhagyta volna a Szivárványt, nem volt hajlandó a parancsnokságom alatt szolgálni, az nagyon rosszat tett volna a megítélésemnek. De Svensson közbelépett, és mindenkit rendbe hozott. Senki sem hagyta el nyíltan a legénységet... akkoriban. Hét éven át parancsoltam a szépségemnek, kétes árut szállítottam az Erdei Ördögnek, kincsek után kutattam, éltem... De most már mindez a múlté.";
			link.l1 = "Nem a múltban. Azt hiszem, az a sorsod, hogy újra a saját zászlód alatt hajózz! Igyunk erre!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "Lehet, hogy a hajót nem tudjuk visszaszerezni, de a pengéd még mindig veled van.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "Tudod, ha így mondod, én is elhiszem. Igyunk rá!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Tengerészeti képességek +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "De vajon a pengém boldoggá tesz-e engem? A válasz valószínûleg valahol ennek a bögrének az alján van. Igyunk!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Személyes képességek +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "Gondolkodtam az európai életeden... Nézd, te egy városi piperkôc vagy, én meg csak egy átlagos lány, de mi már nevet szereztünk magunknak a világ legveszélyesebb szegletében.";
			link.l1 = "Úgy hangzik, mint egy tószt! Szóval, van valami, ami összeköt minket?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Nos, én az apám vállán állok. Nem tudom, te hogy vagy vele, de talán a te családod sem volt rád kisebb hatással? Talán még nem is vetted észre?";
			link.l1 = "Majd megkérdezem a kedves bátyámat, amint kihozom a börtönbôl.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Nos, ennyi volt, kapitányom. Elmondtuk a történeteinket, itt az ideje, hogy befejezzük az éjszakát.";
			link.l1 = "Hmm, reméltem, hogy másképp ér véget az este.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "Az éjszakának még nincs vége. Javasolok egy játékot: ha jól játszod ki a kártyáidat, talán az imáid meghallgatásra találnak.";
			link.l1 = "Kártyázni fogunk? Benne vagyok!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Nyugalom, tengeri farkas. Nem fogok veled vetkôzôs pókert játszani.";
			link.l1 = "Igen, igazad van, Helen. Itt nincs magánéletünk.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "Nem ez az egyetlen dolog, amink nincs, Charles... Ez nem egy kártyajáték, de ne aggódj, fogadok, hogy mestere vagy. 'Soha' - nem hallottam róla?";
			link.l1 = "Ismerôs. Az elôzô életembôl. És gyakran játszol vele?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Mindig is ki akartam próbálni, de nem volt kivel játszani.";
			link.l1 = "Elég merész játék az elsô közös italunkhoz. Biztos vagy benne?";
			link.l1.go = "drinking_game_5";
			link.l2 = "Egyébként, hol vannak a többiek? Egyedül vagyunk itt?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Igen, a közelmúlt eseményei után szükségem van egy kis életre. Valami bolondságot csinálni, tudod?";
			link.l1 = "Nem, mindig rosszul végzôdik, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Gyerünk, kezdjük! Hölgyeké az elsôbbség!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Mindenkit hazaküldtem - nem kell, hogy kívülállók hallják.";
			link.l1 = "Nem, mindig rosszul végzôdik, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Gyerünk, csináljuk! Hölgyeké az elsôbbség!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Kár, de talán igazad van. Akkor még egy italt?";
			link.l1 = "Gyerünk, kezdjük! Hölgyeké az elsôbbség!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "Elintéztem - az emeleti szoba a tiéd. Valami fontos francia tiszt foglalta el, de az Erdei Ördög fiai udvariasan megkérték, hogy hagyja el a helyet. Menj, vegyél magadhoz egy kis lôtt szemet - nem hagyom, hogy ilyen állapotban az utcán csavarogj, vagy ami még rosszabb, hogy a tengerbe menj.";
			link.l1 = "Igenis, asszonyom!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "A végén mindig rosszul végzôdik, Rumba. Hic! Ez azt jelenti, hogy kezded!";
			link.l1 = "Óvatosan, drágám! Hmm. Még sosem üldöztem patkányokat a raktérben!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "Szóval így van ez? Veled kell vigyázni! (Italok)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "Brr! Csak az emléke... Nos, készülj fel, szépfiú: Még sosem estem le az udvarról!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "Szép volt! Engedje meg, kisasszony, hogy igyak önre! (Italok)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "Sosem voltam babonás.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "És még te nevezed magad tengerésznek! Nagyon jól tudod, milyen emberek vagyunk. Soha nem tudhatod, mit hoz az út, nem tudhatod, mikor és hol fogsz partot látni, ha egyáltalán. A térképeken és navigációs eszközökön túl kell keresni a válaszokat! Az egészségedre! (Italok)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "És a lányokra, akiket személyesen festettél... Tetszett nekik az eredmény?";
			link.l1 = "A festmények nem mindig tetszettek nekik, de... az eredmény - mindig.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "Charles! Ha akkor találkoztunk volna, lelôttelek volna, vagy túszul ejtettelek volna váltságdíjért. Egyébként pedig soha nem fogtam ecsetet.";
			link.l1 = "Hé! Hát ez teljesen banális. Kedves Helen, ha elkezdem sorolni a dolgokat, amiket sosem vettél fel...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "Jól van, rendben, tisztességes leszek. Te jössz, kapitányom.";
			link.l1 = "(Kortyolgat) Hic!. Hmm...nekem még sosem ütöttek fejbe a modelljeim pisztolymarkolattal.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(Kortyolgat) Ugh. Rosszul játsszuk ezt a játékot, drágám. Azt hittem, iszogatunk és megismerjük egymást, de ehelyett szurkálódásokat váltunk és... és... és... Hic. A francba!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Tegyük ezt érdekesebbé! És lehetôleg valami mást, mint amirôl egy órája beszélgettünk!";
			link.l1 = "Még sosem ébredtem ismeretlen helyen egy ivászat után.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Aú! A fenébe, Charles! (Italok)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "I... Hic... nem tudom elhinni. Bevallom, bûnös - a kis Rumba szokott a fenekére csapni. De én még soha nem voltam börtönben!";
			link.l1 = "Honnan...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "Hahaha! Igyál, igyál!";
			link.l1 = "Ezt még megbánom. (Italok)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "Gyerünk, kedvesem. Az utolsó kérdés és az utolsó esély, hogy túljátsszon engem!";
			link.l1 = "Nem... Én... Menjünk egy kis friss levegôre.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "Sokszor ittam már, de így még soha... Még sosem ittam le magam ennyire egy lánnyal. Esküszöm a szavamra, az ivás valóban nagy bûn...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "Eh!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "V-várj... Te nem iszol?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "Ah-ha-ha! Ez nagyon vicces! Magas célod van, kapitányom. Hadd legyen... hic!.... ismert...";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "Hogy az a szerencsétlenségem, hogy csak férfiakból álló legénységben élek, és óvatosan kell viselkednem. Én becsületes lány vagyok.";
			link.l1 = "Örülök neked, H-Helen.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "Még boldogabb leszel, mert én nyertem! De, hogy ôszinte legyek, én sem rúgtam még be ennyire egy pasival.";
			link.l1 = "(Némán iszik egy kortyot) T-neked. Gratulálok... h-hic...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "Hé, hé, hé! Kapitány, hová megy? Talán megsértôdött?";
			link.l1 = "Szükségem van... egy kis szünetre? Csak megkeresem a kardomat...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Kapitány, készen állsz? Nincs visszaút, és ha bármi rosszul sül el, feleségül veszlek.";
			link.l1 = "Fúúú! Legalább hadd szívjak egy kis friss levegôt! Biztos vagy benne, Helen?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "Igen, a fenébe is, és ne állj ott, mint egy rúd! El kell veszítenem magam, még ha csak egy éjszakára is!";
			link.l1 = "Attól tartok, hogy ezután az éjszaka után én leszek az, aki el akarja veszíteni magát. Menjünk, mielôtt az egész várost felébresztjük.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Cap, fogd a kulcsot és menj fel az emeletre. Ott kell lennie egy ládának; valószínûleg láttad, amikor Svenssonnál volt. Fogd a hordót, és azonnal menj vissza.";
			link.l1 = "Várj csak, drágám, miért kell kirabolnom a fônöködet?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "Ne butáskodj! Gyerekkorom óta itt vagyok; ha a tulajdonosok visszatérnek, el tudom intézni, és fedezlek. Gyerünk, most ne engedd le a vitorlát!";
			link.l1 = "Éles, mint a kés, egy igazi csempész! Tarts ki, gyors leszek.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "Megvan?";
			link.l1 = "Naná! Nem az elsô láda, amit kiürítek, és biztosan nem az utolsó!";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "Büszke vagyok rád! Haha! Elsô osztályú ír whisky, 'Bushmills'! A kocsmában nem szolgálnak fel nekünk ilyen italt.";
			link.l1 = "Jól hangzik, de Svensson nem fogja észrevenni, hogy hiányzik?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "Biztosan észreveszi, de ô maga nem iszik ilyet. Úgy tûnik, hogy ezt ajándékba tartogatta a kalóztársának, Dodsonnak, és Dodson vagy eltûnt, vagy megölt valakit...";
			link.l1 = "Ez szörnyû! Egy ilyen ajándék semmiképpen sem mehet kárba. Fogd meg a hordót, és változtassunk a helyzeten!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Jól mondtad, Kapitány. Még egy dolog - mondd csak, vittél még valamit a ládából? Válaszolj ôszintén.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Elvettem valamit, szokásból, tudod.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "Nem. Nem biztos, hogy kalóz vagyok, de tolvaj biztosan nem.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				notification("Helen helyteleníti.", "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "Valahogy hiszek neked... egy bolond vagyok!";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Menj, és gyôzôdj meg róla, hogy nem vittél el semmit valamiért.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "Hé, hé, drágám! Koncentrálj! Az arcom, amit a tengeri szellô csókol, itt van!";
			link.l1 = "Fúúú, hát a jelmezed nem semmi! Biztos sok pénzt spóroltál a varróanyagon. És én... hic! Sok mindent láttam! De ez... De ez a legjobb dolog, amit eddig láttam.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "Mindenki ezt mondja, de én valamiért hiszek neked! Tényleg tetszik?";
			link.l1 = "Hát persze, nagyon elônyösen kiemeli az alakodat, bár...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "Ó, most mindent elrontottál!";
			link.l1 = "... bár nincs kétségem afelôl, hogy a hétköznapi emberek körében is csodálatot vált ki!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "Inkább csodálattal tölt el ez a furcsa, széles körben elterjedt szokás az egyszerû és kevésbé egyszerû emberek körében, hogy ilyen melegben sûrû európai ruházatot viselnek. Ettôl még komikusabbnak tûnnek a falvaink... Tetszik a ruhám, Charles. Szépnek érzem magam benne, és ez fontos egy nônek.";
			link.l1 = "Ugyanolyan szép maradnál a ruha nélkül is, Helen.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "Óvatosan, kapitányom! Ha ilyen kedves dolgokat mondasz, megronthatod szegény lányt!";
			link.l1 = "Ha ô nem ellenzi, akkor én sem ellenzem.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "Hee-hee! Jobb, ha valami másról kérdezel. Szeretem, ha kíváncsi vagy.";
			link.l1 = "Akkor tegyünk fel egy kérdést a jelmezedrôl. Nem hiszem, hogy a tengeri kutyák komolyan tudnak venni egy kapitányt ilyen öltözékben.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "És nem hiszem, hogy a tengeri kutyák általában egy nôt kapitánynak látnak, így a ruhám valószínûleg nem növelte a problémáimat. Vagy talán nem volt ideje hozzátenni, mivel ez egy új dolog. Én magam varrtam!\nAh-ha-ha-ha! Régebben én is hordtam egy olyan... hogy is hívják? A katonaság még mindig hordja ôket! B-r-r-r... Ha most meglátok egy ilyet, rosszul leszek.";
			link.l1 = "Egyenruhák?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "Ó, pontosan, egyenruha! Egy piros egyenruha! Mint amit az a fickó visel.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Ó, sajnálom, ôrnagy úr, hadd kínáljam meg egy kis finom ír whiskey-vel, bocsánatkérésként... hic!....bocsánatkérésként.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "Charles nem fog bajba kerülni, ugye, ôrnagy? Mondja, hogy nem, kérem szépen!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "Annyira örülök! Igyunk!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "Upf. Nézd, mit találtam!";
			link.l1 = "Helen... Azt tervezed, hogy ezt használod... hogy feldobd a hangulatodat?!... Eszedbe se jusson! A datura teljesen le tudja gyôzni az embert, elszívja az erejét, összetöri az akaratát! Mielôtt észrevennéd, egy élô holttest leszel, majd nagyon gyorsan egy halott...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Charles, de... most...";
			link.l1 = "Nincs de. Sajnálom, hogy ilyen durva vagyok, de ez nem vicc. Ezt elveszem tôled. Nem hiszem el, hogy mit gondoltál... Tessék, idd meg ezt, és térj magadhoz.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "Sajnálom, Charles. Teljesen igazad van, tudom. Egy pillanatnyi gyengeség. Nem fog újra megtörténni. Köszönöm, hogy megmentettél az ördög kísértésétôl...";
			link.l1 = "Felejtsük el... Most pedig mondd, hogyan sikerült kivívnod a tiszteletet a városban, jó kapcsolatot ápolnod a helyôrségi tisztekkel, és összebarátkoznod a bennszülöttekkel?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "Tisztelik Svenssont, és ennek egy része rám is átragadt. A mi kis városunk kizárólag Jan üzleteibôl él. A kakaóültetvényei hasznának egy részét megosztja a vöröskabátosokkal, és a miskitók neki köszönhetik a teljes megélhetésüket.";
			link.l1 = "Hogy történhetett ez?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "Amikor a kasztíliaiak voltak hatalmon, nem nagyon zavarták az indiánokat. De miután kirúgták a nemes Hidalgókat, a mieink úgy döntöttek, hogy átveszik az irányítást a helyi erdôk felett. Jan akkoriban elég határozottan megoldotta az ügyet - még Londonba is küldött embereket! Persze nem jószívûségbôl: kakaót bányászni egy olyan erdôben, ahol minden bokor gyûlöli az embert, reménytelen vállalkozás. Most azonban az indiánok nemcsak segítenek Jannak a Porto Bellóból Blueweldbe csempészni, hanem a saját erdejüket is kivágják fillérekért. Bravó, Erdei Ördög, bravó!";
			link.l1 = "Úgy hangzik, mintha nem teljesen helyeselnéd a módszereit.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "Szeretem és tisztelem a miskitókat, de Jan stratégiáját is tisztelem. Nem tündérmesében élünk, kapitányom.";
			link.l1 = "Hm... Úgy látom, a kapcsolatod Svenssonhoz bonyolultabb, mint amilyennek elsô pillantásra tûnik...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "Sôt, még annál is jobban, mint gondolnád. A feleségének jó oka van rá, hogy mérges legyen rám... Jan már tizenöt éves korom óta szemezget velem. Nagyjából akkoriban kezdtem el egyenrangú félként járni a Szivárvány fedélzetén, és úgy látszik, akkoriban valami kattant az Erdei Ördög elméjében... De túl sokat mondtam, kapitányom. Ne mélyedjünk el ebben a témában; a patrónusunkról pletykálni nem túl tisztességes dolog.";
			link.l1 = "Akkor váltsunk témát. Azt akartam mondani, hogy te egyértelmûen beleillesz ebbe a társaságba, és a sajátjuknak tartanak.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "Csak történetesen sokkal könnyebb nekem indiánok, cigányok és más tisztességes félkegyelmûek társaságában lenni. Anyu pörköltje, a tengerparti tábortüzek és a Szivárvány gangja - egy hangulatos kis világot építettem magamnak, kapitány. Kár, hogy mindez éppen akkor omlott össze, amikor azt hittem, mindent kitaláltam.";
			link.l1 = "A hordó majdnem üres... Még egy utolsó kör?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "Ez annyira jó... Örülök, hogy beleegyezett, hogy idôt töltsön velem, kapitány. Nagy szükségem volt rá. Azt hiszem, magának is.";
			link.l1 = "Igen, már egy perce nem voltam ilyen nyugodt. Ez valami emlékezetes lesz!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "Valószínûleg azt hiszi, hogy az ördög tudja, mit gondol most rólam. Természetemnél fogva nagyon zárkózott ember vagyok, Charles. Én csak... a fenébe is, csak érezni akartam, hogy élek! Csak beszélni akartam valakivel!";
			link.l1 = "Mi van Gladysszel? Jan?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "Anya csak sír, és Jan most más embernek tûnik. Lehet, hogy csak képzelôdöm, nem tudom, de mintha most szégyellne engem? Bocsáss meg, én... (szipog).\nThat's enough, old girl. Bocsánat, kicsit elragadtattam magam.";
			link.l1 = "Nem kell bocsánatot kérned. Én mindent értek, vagy legalábbis azt hiszem, hogy értek.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "Mindezt azért mondom, mert még csak most találkoztunk, és nem szoktam ilyen nyíltan beszélni még azokkal sem, akiket már régóta ismerek. Rumbának hívnak, állítólag a jellemem miatt, de mint láthatod, ez egy félreértés. Elfogyott a pia?";
			link.l1 = "Egy ideje, és már hajnalodik.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "Sajnálom, kapitányom, ha más elvárásai voltak az esténkkel kapcsolatban. I... Nem tudok. Ma nem.";
			} else {
				dialog.text = "Akkor köszönöm az estét, kapitány. Ki tudja, talán még egyszer megismételjük.";
			}
			link.l1 = "Természetesen, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Köszönöm, hogy elhozott ide, kapitány. Nézzünk körül, rendben? Vizsgáljuk meg az örökségemet.";
			link.l1 = "Nem jártál már itt korábban?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "Nem, elég messze van, ráadásul nem vagyok kalóz. Ez a hely sosem volt különösebben lenyûgözô, és miután megölték Blaise-t... Jobb, ha nem idôzünk itt.";
			link.l1 = "Nem is fogunk. Már megbántam, hogy idehoztalak.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "Muszáj volt, kapitány? Miért harcolsz ilyen gyorsan? Hát, azt hiszem, nem csak a gyôztesnek kell gyôznie. Gyerünk, nézzük meg a rezidenciát, amúgy sincs itt semmi más látnivaló.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						notification("Helen helyteleníti.", "Helena");
					} else {
						dialog.text = "Dicséret, kapitányom, hogy megpróbálta bölcsen megoldani a problémát, mielôtt verekedésbe keveredett volna. Gyerünk, nézzük meg a rezidenciát; amúgy sincs itt semmi más látnivaló.";
					}
					
					link.l1 = "Mi van azzal a hatalmas hajóval, amit partra húztak?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "Ügyesen átverted azokat a bolondokat, kapitányom! Majdnem kitört belôlem a nevetés, ôszintén! Gyerünk, nézzük meg a rezidenciát; amúgy sincs itt semmi más látnivaló.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen helyesel", "Helena");
					
					link.l1 = "Mi van azzal a hatalmas hajóval, amit partra húztak?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "Várjon, hadd szusszanjon egy lány! Tényleg te vagy az a Charlie Prince?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen helyesel", "Helena");
					
					link.l1 = "Volt egy ilyen idôszak az életrajzomban, igen. Le vagy nyûgözve?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Igen, igazad van. Szívesen felfedezném, de ôszintén szólva, Charles, kicsit félek tôle. Gyerünk, menjünk.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "Istenem, igen! Késôbb mindent elmesélsz, rendben? Mert én csak történeteket hallottam... nagyon illetlen történeteket!";
			link.l1 = "Mindent elmondok... majdnem mindent.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "Kíváncsian várom! Gyere, nézzük meg a rezidenciát, úgysem érdemes itt mást látni.";
			link.l1 = "Mi van azzal a hatalmas hajóval, amit partra húztak?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "Egy szûkös, hideg viskó, abszurd igényekkel. Már most úgy érzem, mintha csapdába estem volna!";
			link.l1 = "Látom, hogy eddig nem vagy elégedett a potenciális ingatlannal?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "Nem, Charles. Talán túlságosan kényes vagyok, de egyelôre megtestesíti mindazt, amitôl félek és amit gyûlölök. Remélem, ki tudom majd adni... Bár nem tudom, mire költsem a pénzt.";
			link.l1 = "Ne becsülje alá a bérleti díj értékét. Nekem nincs bérleti díjam, és gyakran kell kitalálnom, hogyan fizessem ki a legénységemet. Veszel magadnak egy új hajót, 'Rainbow II' - jól hangzik, nem gondolod?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "Sokféleképpen költhetsz pénzt magadra. Kezdd egy személyre szabott karddal és egy üveg kiváló borral. Kényeztesd magad, Helen, megérdemled.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Köszönöm, kapitányom. Ezt örömmel hallom. Különösen jó másodszorra hallani. Jól ismersz engem.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				notification("Helen helyesel", "Helena");
			} else {
				dialog.text = "Köszönöm, kapitányom. Ezt örömmel hallom.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "Gondolja, hogy megérdemlem? Soha nem költöttem pénzt ilyen apróságokra, de azt hiszem, mindennek megvan az elsô alkalom. Látom, nem hagyja abba, hogy elfeledtesse velem a tengert, ugye, kapitány? Talán igaza van...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				notification("Helen helyteleníti.", "Helena");
			} else {
				dialog.text = "Gondolja, hogy megérdemlem? Soha nem költöttem pénzt ilyen apróságokra, de azt hiszem, mindennek megvan az elsô alkalom.";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "Mindenesetre az ellenôrzés befejezôdött. Úgy tûnik, itt nincsenek értéktárgyak - a csôcseléknek már sikerült mindent kifosztania, és biztos vagyok benne, hogy a második emelet is hasonló állapotban van.";
			link.l1 = "Mintha megváltoztál volna, Helen. Amikor legutóbb együtt lógtunk, te... nem is tudom, nyitottabb voltál?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Semmi sem változott, kapitányom, de egy szegény lány vállára sok minden hárult, haha! Nem akartalak megbántani. Csak most sok mindent át kell gondolnom. Tudod, ilyen éles fordulatok az életben nem minden nap történnek. És még rengeteg idônk van együtt!";
				link.l1 = "Örülök, hogy ezt hallom! Menjünk innen.";
			} else {
				dialog.text = "Sok minden megváltozott, kapitány. Attól tartok, most már érettebbnek kell lennem, és másképp kell látnom az életet. Ez nem egy tündérmese a hercegnôrôl és az örökségrôl; ez nagypolitika, és nekem még fel kell ismernem a helyemet benne. És a családom helyét is.";
				link.l1 = "Örülök, hogy ezt tisztáztuk. Menjünk innen.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "Igen?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "Hé, még nem mindent fosztottak ki! Nézd, Helen! Ez a szablya legendásnak tûnik, tekintve, hogy még a helyi csôcselék is habozott zsebre vágni.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "Nem, semmit.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "Hû, ez... maga Blaise legendás kardja! A kalózok túlságosan tisztelték ôt ahhoz, hogy még a halála után is elvigyék a szablyát az otthonából. A pénzt és az értéktárgyakat persze elvitték, de még a leendô akasztófamadaraknak is maradtak maradványai a becsületbôl...";
			link.l1 = "Úgy tûnik, valaki itt egyértelmûen rendet rak. Mintha a tulajdonos visszajönne... Ez nem egy otthon, ez egy emlékhely!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Köszönöm az éles megfigyelést, Charles. Teljesen tönkretetted ezt a helyet a szememben, ha-ha!";
			link.l1 = "Azt hiszem, ez a bicska most már a tiéd. Blaise az úgynevezett nagybátyád...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "Még több borzalmat adsz hozzá, kapitányom. I... Nem tudok... Attól félek, hogy ha elfogadom, akkor az eddigi életemnek vége szakad.";
			link.l1 = "Akkor ne az örökség részeként fogadd el, hanem egy jóképû férfi ajándékaként.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "Ki lehet az? Csak vicceltem! Köszönöm, hogy eloszlatta sötét gondolataimat, kapitányom. Ígérem, sokat fogok edzeni, hogy méltó legyek erre a pengére!";
			link.l1 = "Maga méltó a legjobb fegyverhez, Helen. Menjünk, itt végeztünk.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "Hû, ez... maga Blaise legendás kardja! A kalózok túlságosan tisztelték ôt ahhoz, hogy még a halála után is elvegyék a szablyát az otthonából. A pénzt és az értéktárgyakat persze elvitték, de még a leendô akasztófamadaraknak is maradtak becsületmaradványaik\nI... Nem tehetem. Attól félek, hogy ha elfogadom, akkor az eddigi életem teljesen véget ér.";
			link.l1 = "Akkor ne az örökség részeként fogadd el, hanem egy jóképû férfi ajándékaként.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "Ki lenne az? Csak vicceltem! Köszönöm, hogy eloszlatta sötét gondolataimat, kapitányom.";
			link.l1 = "Méltó vagy a legjobb fegyverhez, Helen. Örülök, hogy tetszik.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "Ígérem, sokat fogok edzeni, hogy méltó legyek ehhez a pengéhez!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "A kapitányom! Charlie!";
			link.l1 = "Charlie? Ez új! Örülök, hogy látlak, kedvesem.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "Véletlenül elcsúsztam, ha! Én is örülök, hogy látlak...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "Ennyit a testvéri szolidaritásról! Kapitányom, én... Nagyon aggódtam és nagyon hiányoztál!";
			link.l1 = "Szóval miért kellett hazarohannod?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "Hogy... Ó, igen! Van egy kis ajándékom a számodra!";
			link.l1 = "Három amulett... Helen, miért? Követni akartál?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "Gyere ide, te bolond!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "Csak el ne merd rontani ezt a pillanatot - egész életemben ezt képzeltem!";
			link.l1 = "Nem fogok, Helen.";
			link.l1.go = "after_kiss_a";
			link.l2 = "Egész életedben arra vártál, hogy találkozzunk? Hízelgô!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Helen, van valami... Az Igazság Szigetén találkoztam egy nôvel, és...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "A fenébe is, igazad van! Mindent el fogsz nekem mondani, mindent! Várni foglak a hajón, kapitányom!";
			link.l1 = "Várjon!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "Bolond! Meg akarsz bántani? Rendben, megsértettél! Ha-ha! Most megyek a hajóra, mielôtt Danny még több gúnyt ûz belôlem...";
			link.l1 = "Várjon!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "Bolond! Megkértelek, hogy ne rontsd el a pillanatot! Találkoztál... nos, találkoztál - még nem látok gyûrût az ujjadon. De ne hidd, hogy megúszod - várom a részletes történetet, amikor visszatérsz a hajóra.";
			link.l1 = "Várjon!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "Kapitányom, mi újság? Látom a sápadt arcodon, hogy az ügyvéd úgy döntött, ahelyett, hogy segítene, inkább még több gondot okoz neked.";
			link.l1 = "Igazad van, Helen. Loxley tekintélyes elôleget követelt, és maga az ügy is szép summába fog kerülni. Megyek, megrázom Jant - elegem van! Mintha a Testvérek úgy döntöttek volna, hogy minden költségüket rám hárítják!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "Nincs benne semmi rosszindulat, Charles. Ôk már csak ilyenek - a kisujjukat sem mozdítják, ha nem muszáj. Biztos vagyok benne, hogy Jan segíteni fog neked, és én sem fogok tétlenül állni.";
			link.l1 = "Tudom, Helen. Mondd el, mi jár a fejedben.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "Régen Jannek dolgoztam - értékes fát csempészett Maine-szerte. De leleményes lány vagyok, és az összes ilyen út során félretettem valamit magamnak.";
			link.l1 = "És Jan nem jött rá? Okos!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "Jó pénztárosom volt. Röviden, összegyûjtöttem egy tisztességes mennyiségû pénzt, és nem messze innen elrejtettem. Most mész Janhoz? Akkor látogassunk el San Juan del Norte-ba. Van a közelben egy barlang, és csak néhány matrózra lesz szükségünk, hogy segítsenek nekünk, így nem kell mindent magunknak cipelnünk.";
			link.l1 = "Már mindent kitaláltál, ugye? Köszönöm, Helen, mindenképpen meglátogatjuk, ha lesz rá idônk.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "Kapitányom, mi újság? Látom a sápadt arcodon, hogy az ügyvéd úgy döntött, ahelyett, hogy segítene, inkább még több gondot okoz neked.";
			link.l1 = "Igazad van, Helen. Loxley tekintélyes elôleget követelt, és maga az ügy is szép summába fog kerülni. Megyek, megrázom Jant - elegem van! Mintha a Testvérek úgy döntöttek volna, hogy minden költségüket rám hárítják!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "Azt hitted, hogy egy tündérmesében vagy? Ne aggódj, itt mindannyian egy csónakban evezünk, és én segítek neked. Elvégre nekem is jár az örökség, nem igaz?";
			link.l1 = "Ez igaz... Mondd el, mi jár a fejedben!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "Van valamim San Juan del Norte-ban. Van egy barlang a közelben - csak meg kell szereznünk néhány matrózt, hogy ne kelljen mindent magunknak cipelnünk.";
			link.l1 = "Már mindent kitaláltál, ugye? Köszönöm, Helen, mindenképpen meglátogatjuk, ha lesz rá idônk.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "Ez az, Charles! De egyedül kell menned - utálom a barlangokat!";
			link.l1 = "Mint minden zárt teret, tudom, Helen. Várjatok meg itt.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "Van egy kis gond! Egy csapat katona jön erre, és fenyegetôen néznek ki. Légy óvatos, Charles, ezek nem csak egyszerû parti ôrök - egy francia tiszt is van köztük! Könyörgöm, ne csinálj semmi ostobaságot!";
			link.l1 = "Mikor csináltam én valaha is bármi ostobaságot?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ha, a második lehetôség csábítóbbnak hangzik, de remélem, nem vagy túl büszke magadra, Charles?";
			} else {
				dialog.text = "Nem mondhatom, hogy meglepôdtem, Charles...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "Befejezted? Most én következem!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "A nevem Helen MacArthur! Kapitány, tudja, ki vagyok és kinek dolgozom! Tájékoztassa az embereit, különösen ezt a földön fekvô idiótát, a mai eredményekrôl, amelyeket most fogok bejelenteni!";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "Tiltakozás? Nem érdekel, ha magának Cromwellnek ír. Elôször is, Monsieur de Maure ma nem vesztette el a becsületét.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "Másodszor, de Tavann ezredest lelôtte egy nagyon pikáns ruhás lány, mert prostituáltnak nevezte.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Harmadszor, azonnal vonja vissza a katonáit, és felejtse el, ami történt, hacsak nem akarja, hogy az erdei ördög is tudjon róla.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "Látom, nincs kérdés. Szép napot, kapitány.";
			link.l1 = "Te jó ég, Helen, te aztán lángolsz!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Késôbb, Charles. Menjünk innen, mielôtt magához térnek a sokkból. Én is remegek mindenütt. Beszélhetnénk Blueweldben?";
			link.l1 = "Egyetértek.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Tûnjünk el innen, mielôtt magához térnek a sokkból. Még mindig vissza kell szereznünk a vasfát, emlékszel? Beszélhetünk Blueweldben.";
			link.l1 = "Hûha! Még csak nem is gratuláltál? Rendben, menjünk.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "Végre otthon...";
			link.l1 = "Mit gondolsz a történtekrôl?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "Nem értem a párbajokat. Egy férfi szórakozása, ami általában két holttesttel végzôdik, és egy szerencsés napon még többel is. És a becsület... Azt hiszem, a becsület arra a vágyra épül, hogy a végsôkig elkerüljük a konfliktust, mivel az ritkán bizonyul méltónak. Ha! Csak hallgassatok rám - fecsegek valami ostobaságot!";
			link.l1 = "Ez egy érdekes nézôpont, Helen. Bár nem mindenki értene vele egyet.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "Kár, hogy a kezükre játszottál. Az ezredes egyértelmûen megszállott volt, a többiek pedig csak a látványosságra és némi pletykaanyagra vágytak. Nos, nem fogom az orrom alá dörgölni - ma már így is elég volt belôle.";
			link.l1 = "Igen, a párbajok után mindig van egyfajta ürességérzet. Mára elég volt a kalandokból. Mit szeretnél legközelebb csinálni?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "Ugh! Csak azt akartam mondani, hogy büszke vagyok ránk. Igazi bátorságot mutattál ma, kapitányom. Nem engedett a legénység hisztériájának, akik egyszer csak parancsolgatni akartak. Kitartottál a vörös egyenruha színlelése és a kék megszállottsága ellen. Az ezredes egyértelmûen a halált kereste, de nem kapott mást, mint egy sebet a nem megfelelô helyen, ha-ha!";
			link.l1 = "Köszönöm, Helen. Ragyogóan elkormányoztál minket a csapástól, mint egy igazi tengerésztiszt. Büszke vagy magadra?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Igen, szükségem volt rá. Csak kár, hogy kék egyenruha volt, és nem piros, de legalább a viselôje megkapta, amit megérdemelt.";
			link.l1 = "Az a személy valóban jelentéktelen, elismerem. Mára elég volt a kalandokból. Mit szeretnél legközelebb csinálni?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "Hazafelé tartok, kapitányom. Hiányoltam a... Gladys. Kár, hogy most otthon van, különben meghívtalak volna magamhoz!";
			link.l1 = "Valóban, ez nagy kár!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "Ne bosszankodj. Hamarosan, kedvesem. Addig is...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, ez még jobb, mint az elsô. Emlékszel? A bálvány mellett?";
				link.l1 = "Ezt nem lehet elfelejteni, kedvesem.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "Csak ne merd elrontani ezt a pillanatot - egész életemben ezt képzeltem!";
				link.l1 = "Nem fogok, Helen.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "Egész életedben arra vártál, hogy találkozzunk? Hízelgô!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "Szedd össze magad, kislány! A viszontlátásra, kapitányom.";
			link.l1 = "Addig is, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "A fenébe is! Hamarosan találkozunk, kapitányom.";
			link.l1 = "Míg újra találkozunk, Helen. Istenem, micsoda lány...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "Bolond! Meg akarsz bántani? Rendben, megsértettél! Ha-ha! Hamarosan találkozunk, kapitányom.";
			link.l1 = "Míg újra találkozunk, Helen. Istenem, micsoda lány...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "Hazamegyek, kapitány. Gondolom, a pénzügyek az ügyvéddel már rendezôdtek? Nehéz akadályok állnak elôttünk, úgyhogy mostantól próbáljuk meg elkerülni a bajt. A bajok majd megtalálnak minket.";
			link.l1 = "Hû, tényleg?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Sajnálom, hogy nyers voltam, kapitány. Az én sorsom is most dôl el, tudod.";
			link.l1 = "Tudom, megpróbálom a lehetô legméltóságteljesebben kezelni. Találkozunk a hajón, Helen.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "Mi a következô lépés? Majd én megmutatom.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, ez még jobb, mint az elsô. Emlékszel? A bálvány mellett?";
				link.l1 = "Ezt nem lehet elfelejteni, kedvesem.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "Csak ne merd elrontani ezt a pillanatot - egész életemben ezt képzeltem!";
				link.l1 = "Nem fogok, Helen.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "Egész életedben arra vártál, hogy találkozzunk? Hízelgô!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "A fenébe is! Hûha! Gladys most nincs itthon. Nem akarsz bejönni?";
			link.l1 = "Meghívsz? És mit fogunk csinálni?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "Nem, Helen. Egy másik nô vár rám a Justice Islanden. Nem tehetem ezt vele.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "Majd máskor, kedvesem. Nagyon akarom, de a mai nap majdnem elintézett. Majd bepótoljuk, és tízszeresen kárpótoljuk az elmaradt idôt.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "A fenébe is! Hûha! Gladys most nincs itthon. Nem akarsz bejönni?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Nem, Helen. Egy másik nô vár rám a Justice Islanden. Nem tehetem ezt vele.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Majd máskor, kedvesem. Nagyon akarom, de a mai nap majdnem elintézett. Majd bepótoljuk, és tízszeresen kárpótoljuk az elmaradt idôt.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Meghívsz? És mit fogunk csinálni?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "Bolond! Meg akarsz bántani? Rendben, megsértettél! Ha-ha! Kárpótolnia kell, kapitányom. Hûha! Gladys most nincs itthon. Nem akarsz bejönni?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Nem, Helen. Egy másik nô vár rám a Justice Islanden. Nem tehetem ezt vele.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Majd máskor, kedvesem. Nagyon akarom, de a mai nap majdnem elintézett. Majd bepótoljuk, és tízszeresen kárpótoljuk az elmaradt idôt.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Meghívsz? És mit fogunk csinálni?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "Á, szóval nem vagyok elég ügyes a csábítás mûvészetében? És ô igen? Ki ô?";
			link.l1 = "A neve Mary Casper, és én szeretem ôt.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "Az a vörös hajú a piros egyenruhában? A piros egyenruhában... Nos, ha kellett volna egy jel, akkor itt van. Nem így kell lennie. És ne aggódjon, kapitány, ez nem befolyásolja a szolgálatomat a hajóján.";
			link.l1 = "Sajnálom, Helen.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "Ó, a kapitányom! Veszélyes egy nôt ilyen állapotban hagyni! Tartom a szavát, és most fusson... Egyedül kell maradnom, és megpróbálok megbirkózni a problémámmal... egyedül! Találkozunk a hajón!";
			link.l1 = "Micsoda lány!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "Ne aggódj, kedvesem, majd én elkísérlek, ha eltévednél.";
			link.l1 = "Nos akkor... vezess!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "Ne mondj semmit, könyörgöm.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... persze a mai napig az én ismereteim errôl a témáról kizárólag a 'Rainbow' csapat vulgáris beszélgetésein alapultak, már persze ha lehet beszélgetésnek nevezni.";
			link.l1 = "És milyen volt? Megfelelt a valóság az elvárásaidnak?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "Nagyon élveztem, de úgy érzem, hogy nem éltem át teljesen. És hogy...";
			link.l1 = "Hadd mutassam meg! Folytathatjuk?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "Ó, most már értem! Egyszerûen csodálatos volt, kapitányom!";
			link.l1 = "Meglepett, hogy finoman fogalmazzak!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "Ah-ha-ha-ha! Ez aztán jó volt, az biztos! Most vagy bedugja a fülét viasszal, vagy felszalad az erôd legmagasabb emelvényére!";
			link.l1 = "Ez váratlan volt, de nagyon vicces, ah-ha-ha-ha!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "Készen állsz, kapitányom?";
			link.l1 = "Máris?! Ne, Helen, könyörülj rajtam, kérlek. Gladys' hirtelen megjelenése határozottan nem javított a hangulaton.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Nos, mit tehetsz... Bár...";
			link.l1 = "Ne, ne, engedd le a vitorlákat!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "Rendben, akkor maradjunk együtt egy kicsit. A jövônk olyan homályos és ijesztô, de hosszú idô óta elôször nem félek semmi mástól. Tudom, hogy néhány új félelem kúszik be, de nem ma. Ma nem, kapitányom.";
			link.l1 = "Ma nem, kedvesem. Ma nem.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "Beszélhetek, kapitány?";
			link.l1 = "Igen, Helen?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "Ismerem ezt a Kígyószemet - jó ember, de egy kicsit furcsa. Rendszeresen küldi az embereket küldetésekre, ki tudja miért. Úgy látom, téged is ért ez a kétes megtiszteltetés.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "Így van, három amulettet kell vinnem neki, különben nem fog tudni segíteni nekem eljutni Sólyomhoz. De tudod mi a vicces? Már nálam voltak! Talán már a kezdetektôl fogva tudta ezt?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "Így van, el kell hoznom neki három amulettet, különben nem fog tudni segíteni nekem eljutni Sólyomhoz. Most nem tudom kitalálni, hol találom ôket, és az idô is fogytán van.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "Ó, micsoda szégyen! Örülök, hogy nem kellett rohangálnod, hogy megszerezd azokat az amuletteket a világítótoronyôröktôl, de reméltem, hogy most az egyszer hasznodra lehetek, reméltem, hogy bizonyíthatok.";
			link.l1 = "Badarság, Helen. Nem kell semmit sem bizonyítanod nekem.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "Segítek neked! Bevallom, reméltem, hogy egyszer hasznodra lehetek, reméltem, hogy bizonyíthatok.";
			link.l1 = "Badarság, Helen. Nem kell semmit sem bizonyítanod nekem.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "Ennek ellenére segíteni akarok neked. Tessék, itt a kulcs a szobámhoz... Úgy értem, a ládát a szobámban! Nem sok minden van benne, de neked jól fog jönni. És... Charles, csak próbálj meg nem kitörni a nevetéstôl!";
			link.l1 = "Nem is akartam. Látom, te is szereted ezeket a dolgokat.";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "Tengerész vagyok, kapitányom, akárcsak te. A mi szakmánkban mindent meg kell tennünk, hogy a szerencsét a mi oldalunkra állítsuk.";
			link.l1 = "Köszönöm, Helen. Nagyon hálás vagyok érte.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "Drágám, van egy ajándékom a számodra!";
			link.l1 = "Látom, ott van - áll és mosolyog!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "Ah-ha, hagyd abba! Egyszer szállítottam egy tisztességes adag selymet a helyi hajóépítônek, úgyhogy most tartozik nekem egy teljes hajófelújítással. Arra gondoltam, hogy odaadom neki 'Rainbow' ezért a munkáért, de nem így kellett volna lennie. Az ön hajójának viszont nagyon jól jönne egy ilyen gondoskodás, nem gondolja?";
			link.l1 = "Valóban, ez egy nagyszerû ajándék, Helen - pont a te ízlésed szerint!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "Örülök, hogy tetszik. Látogassa meg bármikor, és mondja meg neki, hogy én küldtem. Megteszik majd a tôlük telhetô legjobb munkát.";
			link.l1 = "Mindenképpen!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "Beszélhetek, kapitányom?";
			link.l1 = "Természetesen, kedvesem.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("A hölgyednek hiányzol, és figyelmet követel. Szabad kérnem, hogy rendezzenek be neki egy szobát, és szenteljenek neki egy kis idôt", "Jelentem: jelenlétedre a helyi kocsma egyik ágyában van szükség. Csak öt perc az idôdbôl, de a legénység reméli, hogy tovább maradsz!", "Zendülés a hajón, kapitányom! Az a feladatom, hogy négyszemközt adjak át neked egy fekete jelet. Haladéktalanul jöjjön velem!");
			link.l1 = "A kérését teljesítem, Sharp tiszt!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "Ma nem, kedvesem. Túl sok minden történik most.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "Ó, és mit akarsz, mit csináljon egy szegény lány, mi? Rendben, kedvesem, akkor majd máskor.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "Ha! Nem kell kétszer kérnie! Persze, menjünk!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "Most rögtön átdoblak a fedélzeten!";
			link.l1 = "Hé, hé, hé! Nyugodj meg, drágám!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "Gyere ide, te gazember!";
			link.l1 = "Csak vicceltem, Helen! Nem akartalak megbántani!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "Tényleg? Szopj le egy viccelôdôt...";
			link.l1 = "Te vagy a legszebb, és ôrülten szeretlek!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Tûnj el, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "Te magad vagy a ribanc! Örülj, hogy Jan becsületes nôt csinált belôled, különben még mindig minden járókelônek széttárnád a lábad!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "Szajha! Menjünk, Charles!";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "A bicska tökéletesen illik a kezembe! Nem tudom, hogy magyarázzam meg... Mindig is nehezen bírtam más típusú hideg fegyverekkel, mint például a rapírokkal és kardokkal. De ez a bicska más tészta! Csodálatos érzés! Köszönöm, Charles!";
			link.l1 = "A sors mindig ránk talál. Örülök neked, Helen!";
			link.l1.go = "exit";
			notification("Közepes fegyverek +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Tartogasd a történeteidet másnak, nálam nem fognak mûködni. Úgy nézek ki, mint egy naiv, szerelmes bolond? Úgy értem, ôrülten szerelmes vagyok beléd, de bolondnak nevezni túlzás lenne\n Figyelj, drágám, tégy, amit akarsz, de ne feledd, hogy nálam jobb nôt nem találsz. Ha bordélyházakban akarod keresni, csak rajta, de akkor végleg eltûnök az életedbôl.";
			link.l1 = "Helen, én...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "Mindent megértek, Charles. Te csak engem szeretsz, és ezek csak természetes késztetések. Tudod, mi az én természetes késztetésem? Tisztelet a férfiaktól. Egy nô nem elégedhet meg csak a szerelemmel, drágám. Felejtsük el egyelôre ezt a félreértést, de gondolkodjunk el egy kicsit a szavaimon. Jól vagy?";
			link.l1 = "Rendben, Helen.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "Tudod, hogy megy ez. Hadd hûljön ki egy lány elôször.";
			link.l1 = "Sóhaj...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Francis... Emlékszem rá. Mindig várta, hogy megérkezzek Port Royalba, és reménytelenül romantikus volt. Élveztem, hogy egy olyan valakivel tölthetem az idômet, aki távol van a tengertôl - azok a versek és szerenádok... Ez valami új volt. Egy pillantás egy olyan világba, amelyet sosem ismertem.\nFrancis gazdag, intelligens és jóképû volt - igazi fogás. Bármelyik helyi lány megôrült volna a figyelméért, de akkoriban engem inkább az érdekelt, hogy a Szivárványt a felszínen tartsam.";
			link.l1 = "Úgy tûnik, a költô érzékeny lelke nem bírta elviselni az elutasítást. Minden levelében csak rólad beszélt, felidézve a találkozási helyeket. Ha akarod, odaadhatok neked mindent, amit hátrahagyott.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "Nem tudtam, hogy beteg volt. Ez az egész most olyan ostobaságnak tûnik. Ami az ajándékát illeti... Elegem van a végrendeletekbôl és az örökségekbôl. Hidd el, mindenem megvan, amire szükségem van - és még több is. Jobb, ha megtartod.";
			link.l1 = "Így vagy úgy, de az öröksége végül is téged fog szolgálni - ami azt jelenti, hogy akaratlanul is teljesítettem az utolsó kívánságát. Micsoda történet.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}
