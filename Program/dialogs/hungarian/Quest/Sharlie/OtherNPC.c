// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Szükséged van valamire?";
			link.l1 = "Nem, most nem.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "A fenébe a szememmel, végre szárazföld! Ébredjen, Monsieur... akárhogy is hívják... Megérkeztünk!";
			link.l1 = "A-ah! Már reggel van? Mi ez az istenverte hôség és páratartalom?";
			link.l1.go = "Startsailor_1";
			link.l2 = "Én mondom! Charles de Maure! Egy nemesember, tudod. Hogy tudsz egyáltalán inni ebben a hôségben? Inkább egy kis vizet innék, az ég szerelmére.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Szokjon hozzá, Monsieur. Ez az egyetlen idôjárás, ami itt van... mindig lehet rosszabb is.";
			link.l1 = "Hogy lehetne rosszabb!? Csak egy vászon ing van rajtam, és a hátamon csorog az izzadság!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Majd meglátja, haha! Lehet, hogy hurrikánszezon lesz! Siessen, uram. A hosszúhajó nem fog várni magára. Ugye nem akarsz Martinique-ig úszni?";
			link.l1 = "Adjon egy percet, jó? Hol a kardom? Á, itt van...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Már nem Európában van... Legyen óvatos, Monsieur. Nyugtalan idôk járnak. A pletykák szerint az Amerikai Szigetek Társasága eladta Martinique szigetét néhány vallási fanatikusnak, keresztes lovagnak vagy valami hasonló ostobaságnak. Még mindig nem vettem észre semmi szokatlant, legalábbis a fedélzetrôl nézve. De mivel már egy ideje nem vagyunk itt, sok minden változhatott a távollétem alatt.";
			link.l1 = "Keresztesek? Ostobaság!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Akár hülyeség, akár nem, a pletykák elszaporodtak. Már így is elég bajban vagyunk. Kannibálok a dzsungelben, trópusi láz, kalózok, banditák a sikátorokban, nem is beszélve a spanyolokról és az angolokról...";
			link.l1 = "Ó, már megint itt tartunk... Jelenleg az egyetlen baj, amit látok, az a nyomasztó hôség és a szúnyogok... Rendben, készen állok. Mehetünk?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Menjen fel a fedélzetre és szálljon be a hajóba, uram. Isten hozta a Karib-tengeren!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "Itt nincs más idôjárás,'Ôlordsága'. Ha valami, akkor csak rosszabb lesz.";
			link.l1 = "Az idôjárás elviselhetetlen, ahogy a társaságom is az elmúlt hónapokban. Remélem, vannak tisztességes emberek a szigetvilágban.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Nos, akkor azt hiszem, mindannyian örülni fogunk, hogy végre elhagy minket, monsieur. A hajó már vár. Ne ugorjon ki a nadrágjából örömében. És ne felejtse el a holmiját - a hajó továbbindul, és ha nem teszi, akár el is felejtheti.";
			link.l1 = "Mintha csak az ön örömére hagynám itt ôket. Pezó, kard - úgy tûnik, nem raboltak ki.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "Mi persze becsületes emberek vagyunk, de jól gondolkodik - mindig tartsa szemmel a holmiját, különben valaki még kiüríti a zsebeit. Mint a régi Európában. Vagy bárhol máshol. De ez a hely nem olyan, mint otthon. Néhány fanatikus bázist létesített itt. Azt beszélik, hogy titokban megvették az egész szigetet. Szóval, maradjatok éberek és ne keltsetek feltûnést.";
			link.l1 = "Micsoda ostobaság!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "Ez a pletyka. Legyetek hálásak, hogy megosztottam veletek, és hogy aggódtok az itt tartózkodásotok miatt. Máskülönben az a finom gascogne-i rózsa elszáradna a tûzô nap alatt. Képtelenség vagy sem, tartsa meg az eszét - van elég bajunk a fanatikusok nélkül is. Banditák a sikátorokban és a dzsungelben, kalózok a tengeren, és vörös bôrû kannibálok...";
			link.l1 = "Most, most! Majd én elintézem. Lehet, hogy most egy kicsit melegem van, de én otthon napszítta vagyok, nem úgy, mint mondjuk azok a normannok. És ha bármit meg lehet oldani egy karddal, rám számíthatsz. De a szúnyogok - az tiszta gyötrelem! Nos, minden holmim megvan. A hajó készen áll, azt mondod?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Várja türelmetlenül. Remélem, hogy maga is el tud jönni, monsieur? Irány felfelé, és remélhetôleg onnan nem téved el. Ó, és üdvözlöm a szigetvilágban, hehe-hehe.";
			link.l1 = "Igen, köszönöm. Az egyetlen vigasz, hogy nem leszek itt sokáig.";
			link.l1.go = "Startsailor_6";
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "Elnézést, "+GetAddress_FormToNPC(NPChar)+", meg tudná mondani, hol találom Michel de Monper-t? Valahol a városában kell lennie.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Hmm... Úgy látom, hogy nemrég érkezett ide, mivel bátran kérdezôsködik... Azt tanácsolom, hogy hagyja abba, különben bajba kerül. És a kérdéseddel kapcsolatban... Beszélj az apáttal. A templomban találod meg.";
			link.l1 = "Köszönöm!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Állj! Azonnal adja le a fegyvereit, uram, és kövessen minket!";
			link.l1 = "Mi az ördög ez?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_enterSoldiers_2");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Örülök, hogy látom, Monsieur de Maure. Mi az alkalom?";
				link.l1 = TimeGreeting()+", ...tiszt. Szeretnék beszélni a bátyámmal, Michel de Monperrel. Természetesen nem hivatalosan. A Karib-tengeren teljesített szolgálatáról szeretnék tájékozódni.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Hogy ment a kihallgatás? Talált valami érdemlegeset?";
				link.l1 = "Igen, igen. Annyira, hogy ezt a spanyolt magammal viszem a hajómra. Ô egy fontos tanú, és további kihallgatásra el kell szállítani Szent Kristófra.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "Mi dolga van itt, Monsieur?";
				link.l1 = "A bátyámat, Michel de Monper-t keresem.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Monsieur, figyelmeztetnem kell, hogy ön egy katonai kantonban van. Viselkedjen ennek megfelelôen.";
				link.l1 = "Igenis, uram. Igen, uram.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "Monsieur, figyelmeztetnem kell, hogy ön egy katonai kantonban van. Viselkedjen ennek megfelelôen.";
				link.l1 = "Igenis, uram. Igen, uram.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "Michel de Monper jelenleg Philippe de Poincy lovag személyes parancsára az egyik kazamatánkban van ôrizetben. Menjen le az alsó szintre. Ott találod a kazamatákat, amelyeket raktárnak és celláknak használunk. Azt hiszem, megtalálod az utat.";
			link.l1 = "Köszönöm!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Jó napot, uram. Segíthetek valamiben?";
			link.l1 = "Köszönöm, katona, de nem, jól vagyok. Menjen csak.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Köszönöm, hogy megvárt, uram. Szóval Michel de Monper-t keresi? Ön a testvére?";
			link.l1 = "Igen, így van. Én vagyok a testvére, Charles. Azonnal találkoznom kell vele. Michel bajban van?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Sajnos igen, Monsieur. Michel be van zárva az egyik lenti kazamatába. Chevalier de Poincy, az újvilági francia gyarmatok fôkormányzója személyesen írta alá a letartóztatási parancsot. Mindannyian megdöbbentünk. Az ön bátyja a férfias erény, fegyelem és bátorság példaképe, rendünk büszkesége! A legrosszabb az, hogy nekünk, a barátainak kell rács mögé zárnunk és közönséges bûnözôként ôriznünk! Minden tôlünk telhetôt megteszünk, hogy kényelembe helyezzük, de... a börtön az mégiscsak börtön.";
			link.l1 = "Mivel vádolják? Elkövetett valamilyen bûncselekményt?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "A fôkormányzó hivatala sikkasztással vádolja Michelt! Milyen nevetséges! Mindannyian meg vagyunk gyôzôdve arról, hogy ez politikai indíttatású. Elmondok valamit bizalmasan. Michel részt vett bizonyos titkos akciókban a Rend nevében. Talán többet tudott meg, mint kellett volna. Vagy ami még rosszabb, feldühített néhány befolyásos embert. De pénzt lopni? Ezt senki sem hiszi el. Ez csak színlelés, nem valódi ok, gyáva és aljas színlelés! De elég a szavakból. A bátyád már nagyon várja, hogy találkozzunk, biztos vagyok benne, hogy mindent ô maga fog elmondani neked.";
			link.l1 = "Jól van. Hol van a börtönöd?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "A földalatti fegyverraktárunkban, itt a városban. Kövessetek. Megmutatom az utat.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_1");
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "Itt vagyunk. Ez a mi bázisunk - a Jeruzsálemi, Rodoszi és Máltai Szent János Katonai Gyógyító Rend karibi káptalanja. A kazamaták alattunk vannak. Menjetek le a folyosón az étkezô és a kápolna mellett. Az ott lévô lépcsôn az alsó szintre juthatsz. Keressen egy cellákkal szegélyezett folyosót. A bátyádat a hátsó részhez közeli cellában fogod megtalálni.\nMenj, Charles, és Isten legyen veled. Kérlek, segíts Michelnek! Ô feddhetetlen, erre itt mindenki kész megesküdni.";
			link.l1 = "Azért jöttem ebbe a szarfészekbe, hogy lássam a bátyámat. Remélem, hogy legalább ôt ki tudom hozni ebbôl a szorult helyzetbôl.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_2");
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "Szóval Michel de Monper-t kerested? És te vagy a testvére?";
			link.l1 = "Igen, így van. Én vagyok a testvére, Charles. Azonnal találkoznom kell vele. Bajba került, ugye?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "Sajnos igen, uram. Michel le van tartóztatva és a börtönünkben van. Chevalier de Poincy, a francia gyarmatok fôkormányzója maga adta és írta alá a parancsot. Mindannyian megdöbbentünk.\nA testvére a férfiasság, a szilárdság és a bátorság példaképe, rendünk büszkesége! A legrosszabb az, hogy nekünk, a barátainak, be kell zárnunk a celláját és bûnözôként kell ôriznünk! Mindent megteszünk, hogy megkönnyítsük az állapotát, de... a börtön az börtön.";
			link.l1 = "Mivel vádolják ôt? Bûnt követett el?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "Badarság! Tiszta képtelenség! Michel-t csalással és az állam pénzének ellopásával vádolják. Nevetséges! Mindannyian biztosak vagyunk benne, hogy ez csak egy politikai játszma. Michel részt vett a rend titkos mûveleteiben, talán többet tudott meg, mint kellett volna.\nVagy valami más. De pénzt lopni! Ezt senki sem hiszi el. Ez csak ürügy, nem indok, ilyen durva és ostoba ürügy! De elég a szavakból. A bátyád már nagyon várja, hogy találkozzunk, biztos vagyok benne, hogy mindent ô maga fog elmondani.";
			link.l1 = "Jól van. Hol van a börtön?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "A földalatti bázisunkon, itt a városban. Kövessetek. Megmutatom az utat.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_3");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "Aztán áthajolt a korláton, és úgy kiöntötte, hogy maga a Karib-tenger is kizöldült! Ha-ha-ha-ha!";
			link.l1 = "Alonso?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "Ó! Charles, épp most meséltem a fiúknak a hôstetteinkrôl!";
			link.l1 = "Észrevettem. Figyelj, Alonso. Én... kapitány lettem.";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Máris? Azt hittem, legalább egy hónapra van szükséged, ha-ha!";
			link.l1 = "Komolyan mondom!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Ha csak én lennék, azonnal jelentkeznék. De negyven lélek van velem az Ulyssesrôl. Rám bízták a jövôjüket; biztosnak kell lennem abban, hogy nem hagyja cserben ôket\n."+
			"Milyen típusú hajód van?";
			link.l1 = "A hajó az hajó, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "név")))+". Miért, ez ennyire fontos?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Tudod, az Ulysses után inkább nem szolgálnánk fel valami kéreg vagy tartán. Már láttuk a hajóját, és a fiúk helyeslik\n"+
			"Most pedig a pénz. Elôre kérünk 4800 pezót. Utána a szokásos módon osztozunk. Semmi ésszerûtlen, biztosíthatom önöket. Meg tudod oldani?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "Nagyon jó, megvan! Itt az érméje.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Sajnos, most nincs nálam ennyi pénz.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "Van valami élelem a raktérben, kapitány? És gyógyszer? Nincs? Nos, az nem jó. Menjen ki és szerezze meg a minimumot az utunkhoz, aztán jöjjön vissza és megbeszéljük. Menj a boltba, és vedd meg, amire szükséged van.";
				link.l1 = "Hm. Igazad van. Rendben, úgy lesz.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "Bah! Gratulálok... Kapitány! Azonnal összeszedem a fiúkat, és elindulunk a hajód felé.";
				link.l1 = "Örülök, hogy folytathatjuk a kalandunkat, Alonso. Készítsétek fel a hajót a tengerre!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Nos, amint találsz elég pénzt, gyere vissza. Itt találsz minket a kocsmában. Egyébként sincs más hajó a környéken. Mi csak iszogatunk és kurvázunk a pénzünkkel, harhar!";
			link.l1 = "Megpróbálok minél hamarabb visszajönni.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "Visszajöttél, kapitány? Készen állsz, hogy felvegyél engem és a társaimat? A pénztárcánk kezd könnyed lenni, újra éreznünk kell a tengeri szellôt az arcunkon!";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Még nem, még mindig mindent elôkészítek.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Igen. Vegye fel az elôleget. Mostantól a szolgálataimra álltok.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Ahoy kapitány! Mi kell?","Hello Monsieur. Mit tehetek önért?","Jó napot. Mit szeretne?");
			link.l1 = RandPhraseSimple("Lenne egy kérdésem hozzád.", "Információra van szükségem errôl a kolóniáról.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Csak köszönni. Au revoir!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("Mi ez?", "Mire van szüksége?");
			link.l1 = "Figyelj, "+GetAddress_FormToNPC(NPChar)+", a helyzet a következô... Egy navigátort keresek. Talán tudsz valakit, aki alkalmas lenne erre a munkára itt a városban?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "Navigátor? Hm. Nos, én ismerek egyet... Csak egy gond van - börtönben van, adósok börtönében. Szegény fattyú már majdnem egy hónapja van bezárva a kazamatákba, amíg ô vagy valaki más ki nem fizeti a tartozását.";
			link.l1 = "Adós? Hm... Mi a neve?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "A neve Folke Deluc. Kérdezze a börtönparancsnokot, ha látni akarja. De nem hiszem, hogy kiengedik onnan, ha nem fizeted ki a tartozását, mert ô biztos nem az, hahaha!";
			link.l1 = "Talán majd én. Köszönöm az információt, barátom.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "Minek köszönhetem ezt a megtiszteltetést, Monsieur?";
			link.l1 = "Helló, Folke. Egyszerû, van egy hajóm, de nincs navigátorom. És szükségem van egyre. Szóval kiváltottam az adósságodat...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "Azt mondja, azért rángatott ki innen, hogy felvegyen a legénységébe?";
			link.l1 = "Pontosan. Azt hiszem, hamar megtéríti a pénzt, amit magára költöttem. Nos... meglátjuk, hogy megy ez.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "Hálás vagyok, uram. Elegem van ebbôl a rohadt, nyirkos cellából. Nagy örömömre szolgálna, ha még egyszer visszatérhetnék a fedélzetre. Ah, a tenger...";
			link.l1 = "Örülök, hogy megegyeztünk, Folke. Még valami, van más képességed is a hajóvezetésen kívül?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Egy kicsit mindenbôl, kapitány. A holland Nyugat-indiai Társaság egy magánhajóján szolgáltam. Ott megtanultam, hogyan kell bánni az ágyúkkal, így ha szükség van rám, tüzértisztként is szolgálhatok. A kereskedelem és a hajózási feladatok a leggyengébb területeim.";
			link.l1 = "Köszönöm, hogy megosztotta velem, most pedig kövessen a hajóhoz. Szeretném, ha tapasztalt szemeddel figyelnéd a legénységet, amint mindent elôkészítenek az induláshoz. Aztán, szeretném, ha minél hamarabb Guadeloupe felé vennénk az irányt.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Igenis, kapitány! Várni fogom a kabinjában. *A tengeren az akció menü segítségével beléphet a kabinba és a hajó más területeire*";
			link.l1 = "Köszönöm, Folke. Viszlát a fedélzeten.";
			link.l1.go = "Folke_5";
			Log_Info("Megkaptad az amulettet 'Kereskedô Rózsafüzére'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Az elsô tisztje várja önt. A (ENTER) akciómenü segítségével menj a kabinba.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Remek hajó, kapitány! Egészen tisztességes kis hajó, szép kötélzettel és szilárd faanyaggal. Egy ilyen hajóval nem csak Guadeloupe-ba jutunk el biztonságban, de ha akarjuk, akár az egész Karib-térséget is bejárhatjuk.";
			link.l1 = "Kiváló. Legalább nem dobtam ki a pénzem egy lyukas kádra... Van valami tanácsod, mielôtt kihajózunk, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "A fenébe is, ez a hajó szivárog, mint egy szita, kapitány. Majdnem futás lesz, hogy átkelhessünk Guadeloupe-ra. Ha egy darabban akarnak megérkezni Basse-Terre-be, akkor azonnal be kell vinni a hajógyárba javításra.";
			link.l1 = "Nem volt más választásom, ez volt az egyetlen eladó hajó! És elég sokat kértek érte. Mint tudja, jelenleg nincs idônk megjavítani... Van valami tanácsod, mielôtt kihajózunk?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Nos, jól el vagyunk látva lôporral és lôszerrel, kapitány. Egyelôre ennyi elég lesz; csak ne felejtsd el idôben pótolni.";
				link.l1 = "Nos, ez magától értetôdô. Egyéb észrevétel?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "Köszönöm az emlékeztetôt. Véletlenül van nálam egy egész láda sörét!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "Nincs elég lôszer a tárban, kapitány. Szükségünk van legalább száz ágyúgolyóra, lánglövedékre és bombára, valamint száz zsák szôlôlövedékre és kétszáz hordó puskaporra. Vegye fel a szükséges anyagot, kapitány. Nem kerül sokba, de megmenti az életünket, ha kalózok vagy spanyolok támadnak ránk.";
				link.l1 = "Megérdemli a befektetést. Elmegyek a kereskedôhöz.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...És mióta cipeled?";
			link.l1 = "Majdnem két hete.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
			Achievment_Set("ach_CL_164");
		break;
		
		case "Folke_8_2":
			dialog.text = "De miért, kapitány?!";
			link.l1 = "Szeretem gyûjteni az apróságokat. Soha nem lehet tudni, mi bizonyulhat hasznosnak.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Hát, kár magáért. Ez a lövedék sosem fog a játékfegyverünkhöz illeni. Valójában még sosem láttam ekkora sörétet. Egy ilyen az Adeline-t a mélybe küldené.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Befejezte a lôszer vásárlását, kapitány?";
			if (bOk)
			{
				link.l1 = "Igen, megvettem. Egyéb észrevétel?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Most nincs, még dolgozom rajta.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Jól van, elég fegyvert vettél a legénységednek. Ha nincs elég fegyverünk, sokkal több embert fogunk elveszíteni a partraszállás során. Isten óvjon minket ettôl. Ne felejtsd el gyakran ellenôrizni a rakodótérben lévô mennyiséget\nBölcs dolog, ha néhány fegyverrel többet tartunk, mint amennyire szükségünk lesz. Az átkozott patkányok szeretik megrágni a fából készült markolatokat és a faköteleket.";
				link.l1 = "Értettem. Látom, van még valami, amit hozzá akarsz tenni?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "Nincs elég fegyverünk a fedélzeten a legénység számára. Ha nincs elég fegyverünk, sokkal több embert fogunk elveszíteni a partraszállás során. Isten óvjon meg minket ettôl. Ha jól tudom, negyven embere van a legénységnek\nVásároljon mindegyiküknek elegendô fegyvert, vagy akár vegyen még néhányat, ötven készletnek elegendônek kell lennie. Bölcs dolog néhány fegyverrel többet tartani, mint amennyire szükségünk lesz. Az átkozott patkányok szeretik megrágni a fából készült markolatokat és a patkánytartókat.";
				link.l1 = "Ezt fogom tenni. Hamarosan visszajövök.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Befejezte a fegyverek beszerzését, kapitány?";
			if (bOk)
			{
				link.l1 = "A fegyverek a raktérben vannak. Látom, van még valami, amit hozzá akar adni.";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Most nincs, még dolgozom rajta.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "Nem, azt hiszem, ez van. Van elég élelmünk, a legénységnek a rumról is gondoskodtál. Ez bölcs dolog, hiszen nincs jobb gyógyír minden betegségre, mint egy jó hûvös korsó rum a mûszak után. A tengerészek szeretik és tisztelik azokat a kapitányokat, akik megadják nekik a napi rumadagjukat. Soha nem akarja hallani, hogy az emberei megkérdezik: 'Miért fogyott el a rum?'";
				link.l1 = "Most már kihajózhatunk?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Igen. Étel és rum. Katasztrofális, ha nincs elég étel a fedélzeten. Mindig legyen több élelem, mint amennyire úgy gondolod, hogy szükséged lesz. Soha nem lehet tudni, hogy meddig tart az utazás - egy szélcsend vagy egy erôs szélvihar bármilyen tervet tönkretehet. Az emberek lázadnak vagy éhen halnak, ha elfogy az élelem\nA rumkészlet nem olyan kritikus, de erôsen ajánlom, hogy mindig legyen a fedélzeten, nincs jobb gyógymód minden betegségre, mint egy jó hideg korsó rum a mûszak után. A tengerészek szeretik és tisztelik azokat a kapitányokat, akik napi rumadagot adnak nekik\nSzóval menj, és vedd meg a szükséges készleteket - legalább száz láda élelmiszert és tíz hordó rumot. Soha ne akarja hallani, hogy az emberei megkérdezik: 'Miért fogyott el a rum?'";
				link.l1 = "Azt hiszem, igazad van. Megyek, meglátogatom a kereskedôt.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Befejezte az élelem és a rum vásárlását, kapitány?";
			if (bOk)
			{
				link.l1 = "Megvettük a rumot és a rumot? Most már kihajózhatunk?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "Nem, még dolgozom rajta.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Igenis, kapitány. Felszedhetjük a horgonyt, és észak felé vehetjük az irányt, Guadeloupe felé, ahogy akarta.";
			// belamour legendary edition -->
			link.l1 = "Szép munka, Folke. Nélküled nem sikerült volna.";
			link.l1.go = "Folke_13";
			link.l2 = "Rendben, lássunk munkához, lássuk, hogy megéri-e a pénzt.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "Akkor engem nevezz ki navigátornak, én pedig megyek a helyemre a fedélzeten.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "Akkor engem nevezz ki navigátornak, én pedig megyek a helyemre a fedélzeten.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Üdvözlöm az új tisztet a fedélzeten! Nyomd meg az F4-et, hogy kijelölje ôt navigátorának.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "Készen állunk az indulásra, kapitány!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Kapitány, állítson be navigátornak, különben gyorsan zátonyra futunk.";
				link.l1 = "Értettem, most már megteszem.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Elnézést kérek. "+GetFullName(pchar)+"?";
			link.l1 = "Helyes. Mivel tartozom ezért az alkalomért, uram?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Engedje meg, hogy bemutatkozzam - "+GetFullName(npchar)+". Cesar Craig küldött ide. Biztosan ismeri ôt. Ô a Le Francois kocsma tulajdonosa. Amennyire ô értesült, önök Guadeloupe-ra készülnek indulni. Szeretne felajánlani önnek egy kis könnyû pénzt.";
			link.l1 = "Hm... Érdekes! És hogy lett Cesar Craig ilyen jól informált?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "Egyszerû, kapitány. Az önök hajója az egyetlen hajó St. Pierre-ben jelenleg, bárki, akinek két füle és egy szeme van, mindent tud arról, hogy kik maguk és hová tartanak. Itt kint a kolóniákon a pletykák gyorsabban szállnak, mint a sirályok. Szóval érdekli az ajánlatunk?";
			link.l1 = "Persze. Soha nem ellenkezem, ha pénzt akarok keresni.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Most már beszélgetünk, haver! Látom, hogy jó orrod van az üzlethez. Itt az ajánlatom. Cesarnak sürgôsen szüksége van egy adag borra Guadeloupe-ra. Kétszáz hordó, a hajójuk raktere simán elbírja. A fizetés tízezer pezó egy könnyû munkáért - Cesar siet, és a maga hajója az egyetlen hajó a kikötôben. Egyet kell értenie, az ilyen jövedelmezô ajánlatok ritkák.";
			link.l1 = "A fenébe, tízezer pezó? Nos, megegyeztünk!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Irány Le Francois, és beszélj Cesarral. Ô majd mindent elintéz. Csak annyit kell tenned, hogy lehorgonyozol a Le Francois elôtti öbölben. Ne hagyj cserben, haver, Cesar ezer pezót ígért, ha meggyôzlek...";
			link.l1 = "Ne aggódj, tekintsd úgy, hogy meggyôztél. Amint készen állok az indulásra, egyenesen Le Francoisba hajózom.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Hurrá! Elmegyek az ezresemért. Köszönöm, haver!";
			link.l1 = "Szívesen...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Kapitány, a fedélzeti csapat készen áll! Várjuk a parancsot!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Igenis, kapitány! Készüljetek fiúk, kövessétek a kapitányt! Vigyázz, egy-kettô-három!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Mierda, francia erôsítés! Sorakozó! Lorenzo, menj a táborba és riadóztasd ôket! Dögöljetek meg, rohadékok!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "Megértettétek, hogy nem vagyok felhatalmazva ilyen információk terjesztésére?";
			link.l1 = "Megértetted, hogy csak az én idôben történô közbelépésemnek köszönhetô, hogy St. Pierre-t nem pusztították el a spanyolok? A bátyám eltûnt, elhagyta a rendet! Biztos okkal tette. Én, mint Sir Philippe de Poincy képviselôje, fel vagyok hatalmazva, hogy nyomozzak!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "Rendben, rendben, Monsieur de Maure. Válaszolni fogok a kérdéseire. Elôbb nyugodjon meg. Most pedig kérdezzen.";
			link.l1 = "Mi történt azelôtt, hogy Michelt bezárták az ôrségbe?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper néhány kalózbáróval tárgyalt a Tortugán történô rendszerváltásról.";
			link.l1 = "Ezt már tudom. Mi van még?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "Egy másik hadmûveletet is tervezett a spanyolok ellen. Pontosabban egy spanyol hajó elfoglalását, amelynek fedélzetén értékes rakomány volt. Michelnek a nehéz korvett ágyúi alá kellett volna csalnia a célpontot 'Gryffondor'. Jó darabig nem láttunk belôle semmit, amíg ezt tervezte.\nDe a terv balul sült el. A spanyol szállítóhajó nem érkezett meg, és magát Michelt a helyi halászok találták meg félholtan a Le Marin-öböl partján partra vetve. Úgy tûnik, a mûvelet kudarcba fulladt.\nA háború az háború, és a dolgok elromlanak. Csoda, hogy Michel egyáltalán túlélte, de Chevalier de Poincy dühbe gurult. Megvádolta Michelt a rend pénzének elsikkasztásával, és bebörtönözte. Természetesen egy szót sem hittünk el a vádakból. Michel becsületes ember, a rend igazi lovagja. Csak Isten tudja, mi indította be a fôkormányzót. Talán Chevalier de Poincy maga fogja elmondani?";
			link.l1 = "Lehetséges. Ez minden, amit tudsz?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Sajnos, nincs több mondanivaló. A bátyja mûveleteinek részleteit csak ô és Chevalier de Poincy ismerte. A Máltai Szent János Rend lovagjai vagyunk. A parancsot teljesítjük.";
			link.l1 = "Ha a lovag ennyire megbízik Michelben, akkor bizonyára már korábban is sikerrel hajtotta végre titkos terveit. Tudsz valamilyen sikeres akcióról, amit Michel végrehajtott?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Határozottan. Michel de Monper mostani kudarca egyben az elsô kudarca is volt, ezért is döbbentett meg minket a Chevalier reakciója. Nem is olyan régen, 'Gryffindor' megfogott egy ezüsttel megrakott spanyol kincses gályát Michel gondos tervezésének köszönhetôen. Ez önmagában kárpótolhatta volna a jövôbeni kudarcok tucatjait. És mégis, a bátyját letartóztatták.";
			link.l1 = "Értem. Van valami ötlete, hogy Michel miért menekült el St. Pierre-bôl?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Gyanítom, hogy Michel és de Poincy közötti személyközi konfliktus volt az oka a letartóztatásának. Nyilvánvaló, hogy a bátyja attól tart, hogy a Chevalier a szabadulása után is üldözni fogja, ezért óvintézkedéseket tett. És tudja mit, Monsieur de Maure - itt senki sem hibáztatja ôt a döntéséért!\nA férfi bátran dolgozott a rend javára, és mégis egy bûzös cellába dobták a legelsô kudarca miatt, miközben súlyosan megsebesült! Egy olyan kudarcért, ami nem is volt olyan rossz, senki sem halt meg, és egyetlen hajó sem süllyedt el!\nMellesleg, ez a beszélgetés szigorúan bizalmas, és még eskü alatt sem fogom megismételni, amit az imént mondtam, világos, Monsieur de Maure?";
			link.l1 = "Igen, uram. Már el is felejtettem, hogy ezt a beszélgetést már lefolytattuk. Mondja, a St. Pierre elleni spanyol támadást kiválthatta-e az, hogy a rend a spanyol hajókat fosztogatta? Talán az a spanyol gálya ezüsttel, amit említett? A kasztíliaiak rendkívül buzgón keresték az önök bázisát...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Kétlem. Nagyon kevesen tudnak a Rend karibi jelenlétérôl, és minden spanyolok elleni bevetésünket gondosan megterveztük. Kérdezzék meg a spanyol tisztet, akit foglyul ejtettünk, ô most éppen a mi szárnyainkban hûti tüzes kasztíliai indulatát. Már kihallgattuk ôt. A St. Pierre elleni támadás egy közönséges rajtaütés volt, amelyet egy Ramon de Mendoza y Riba nevû spanyol nagybáró szervezett a saját haszna érdekében és a francia gyarmatok megfélemlítésére. Emellett az Escorial kegyeit is meg akarta szerezni.";
			link.l1 = "Beszélni fogok ezzel a spanyollal. Hol találom meg?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Lent, ugyanabban a cellában, ahol a bátyját tartották fogva.";
			link.l1 = "Ismerem az utat. Visszajövök, miután kihallgattam a spanyolt. Lehet, hogy lesz még néhány kérdésem.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Hát ez nem semmi! Ugye megérti, hogy nem engedhetem el azt a foglyot? Az a gazember segített vezetni a St. Pierre elleni támadást!";
			link.l1 = "Biztos úr, ez egy fontos tanú. A St. Pierre elleni támadás nem egy egyszerû razzia volt, ami zsákmányt keresett. Don Ramon Mendosa valami mást keresett. Meg kell találnunk a pontos indítékot. Szóval, kiadja nekem ezt a spanyolt, vagy engedélyt kell kérnem de Poincy-tól?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "A mindenható Istenre... Rendben, vigyék. Úgyis fel akartam akasztani ezt a fattyút a St. Pierre téren, mint egy közönséges kalózt... Most már a te problémád. Gondoskodj róla, hogy ne ússza meg az igazságszolgáltatást!";
			link.l1 = "Kétségtelenül. Felelni fogok ezért a spanyolért de Poincy elôtt. Bilincseljék meg a foglyot, és szállítsák a hosszúhajómhoz a városi kikötôben.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Rendben, kapitány.";
			link.l1 = "Még egy dolog, tiszt úr. Ismerôs önnek a Miguel Dichoso név?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "Nem. Soha nem hallottam még. Miért kérdezi?";
			link.l1 = "Biztos benne? Tehát nem találkozott még senkivel ezen a néven, sem itt a kantonban, sem a kormányzói palotában, sem St. Pierre-ben?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "Nem, nem találkoztam. Ahonnan én jövök, ott nem nézzük jó szemmel a spanyolokat.";
			link.l1 = "Rendben van. Mindegy, ez várható volt. Túl könnyû lett volna... Köszönöm, biztos úr! Nagyon segítôkész volt.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Szívesen látjuk... Mit gondol, Monsieur de Maure, hol van most a bátyja?";
			link.l1 = "Erre a kérdésre magam is szeretném tudni a választ. És elôbb-utóbb ki is fogom deríteni. Au revoir!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Te vagy a kapitány "+GetFullName(pchar)+"?";
			link.l1 = "Igen, én vagyok. Mit tehetek önért?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Üdvözlöm, kapitány. Vincento atya küldött önhöz. Van valamim a számodra...";
			link.l1 = "Vincento atya? Már nem dolgozom Ôkegyelmességének. Nem, miután elküldte Alonso de Maldonadót, Diego de Montoya esküdtjét, hogy megöljön. Átadhatja ezt az üzenetet a tisztelendô atyának: kudarcot vallott.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Várjon, kapitány. Vincento atya számított ilyen reakcióra tôled, és figyelmeztetett is erre. Biztosíthatom, hogy Ôkegyelmessége nem akar rosszat önnek. Kérem, olvassa el ezt a levelet. Nagyon, nagyon fontos.";
			link.l1 = "Vincento atya nem kíván nekem rosszat? Hm. Talán nem mondott semmit rólam és Don de Maldonadóról? Már értem, miért kellene hinnem önnek.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Fogja ezt a levelet, kapitány. Olvassa el, és hozza meg a saját döntését. Csak tudd, hogy az egész kereszténység sorsa a te kezedben van. Ne vegye ezt félvállról. Isten áldja meg önt, és állítsa lábát az igaz útra!";
			link.l1 = "Rendben, adja ide a levelet.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Tessék, tessék. Imádkozom, hogy helyesen döntsön. Pax vobiscum.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "Üdvözletem, fiam. Az Úr legyen veled.";
			link.l1 = "És veled is, Adrian atya. Ôkegyelmessége azt mondta, hogy tudsz nekem amuletteket és gyógyszert adni.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Igen, természetesen. Különleges szállítmányt kaptam Santiagóból, csak neked. Itt vannak áldott amulettek és gyógyító italok. És mindennek tetejébe egy ritka, egyedi Ometochtli tinktúra, amely legyôzhetetlenné tesz a harcban. Ez mind a tiéd, fiam. Fogadd el és lásd, hogy az Úr jó.";
			link.l1 = "Köszönöm!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Ha szükséged van még gyógyító gyógynövényekre, minden nap tudok neked adni egy-egy fiolát. Annyit készítek belôlük, amennyire szükséged van.";
			link.l1 = "Hálás vagyok neked, Adrian atya. Ezt észben fogom tartani.";
			link.l1.go = "exit";
			link.l2 = "Remek. Most azonnal szükségem van rá.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Isten áldjon meg és tartson meg, fiam. Mit szeretnél?";
			link.l1 = "Szeretnék venni néhány gyógyító italt.";
			link.l1.go = "potion";
			link.l2 = "Jelenleg semmit, egy utazásra készülök. Csak beugrottam köszönni, hogy lássam, hogy vagy.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Természetesen, fiam. Milyen gyógyszerre van szükséged?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Csak egy egyszerû orvosságra.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Egy egészséget adó elixír.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Egy ellenszer.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Egy gyógynövénykeverék.";
				link.l4.go = "potion4";
			}
			link.l5 = "Elnézést a zavarásért, atyám. Meggondoltam magam.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Egy gyógyító esszencia? Az 90 pezó, fiam. Természetesen az alapanyagokért.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Köszönöm, atyám.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Sajnos, nincs rá pénzem... Késôbb visszajövök.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Egy egészséget adó elixír? 500 pezó, fiam.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Köszönöm, atyám.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Sajnos, nincs rá pénzem... Késôbb visszajövök.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Egy ellenszert? 200 pezó, fiam.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Köszönöm, atyám.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Sajnos, nincs rá pénzem... Késôbb visszajövök.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Gyógynövénykeverék? 900 pezó, fiam.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Köszönöm, atyám.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Sajnos, nincs rá pénzem... Késôbb visszajövök.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "'Mert visszaadom neked az egészséget, és meggyógyítalak a sebeidbôl, mondja az Úr.' Itt van a te gyógyszered. Dominus vobiscum!";
			link.l1 = "Köszönöm, Adrian atya.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Kapitány "+GetFullName(pchar)+"?";
			link.l1 = "Igen, ez én vagyok. Mit akarsz?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "Üzenetem van számodra Miguel Dichoso kapitánytól. Azt mondja, ismered ôt.";
			link.l1 = "Igen, hallottam róla. Soha nem volt szerencsém személyesen találkozni vele.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Dichoso kapitány szeretne változtatni ezen. Személyesen akar találkozni veled. Ajánlata van számodra egy expedícióval kapcsolatban, amely a spanyol fôsziget mélyére, Tayasal elveszett indián városába vezet. Azt mondta nekem, hogy az ön tapasztalata és az ô tudása párosulva kielégítô eredményeket fog hozni.";
			link.l1 = "Ezek voltak a pontos szavai?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Így van. Dichoso kapitány várja önt a Szent Kristófon. A capsterville-i temetô nagy kriptájában fog várakozni, hogy elkerülje a kíváncsi szemeket és füleket.";
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso figyelmeztetett, hogy habozni fogsz. Azt mondta, hogy ajánljak fel garanciákat arra, hogy a tárgyalások során nem esik bántódásod, bárhogy is döntesz. Azt is hozzátette, hogy amit egy bizonyos szigeten találtál, az csak egy aprócska elôétel volt ahhoz képest, amit Tayasalban találsz majd.";
			link.l1 = "Valóban így van... ez nagyon érdekes. De miért nem látogat meg engem Dichoso kapitány személyesen? Miért küldött egy harmadik személyt?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso elôször az Isla Tesorón kereste önt, aztán itt, és most Szent Kristófra megy, abban a reményben, hogy ott megtalálja önt. Maga Philippe de Poincy egyik tisztje, ugye? Úgy volt, hogy itt várok rád, arra az esetre, ha megérkezel Blueweldbe.";
			link.l1 = "Akkor minden tiszta. Nos, rendben. Nem vesztegetem az idôt, Capsterville-be kell mennem.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Nos, végre találkozunk, kapitány "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Hol van Miguel Dichoso? És ne próbáljon meg kibújni ebbôl. Tudom, hogy ki ô valójában, és azt hiszem, maga is tudja.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Gondolom, ez Miguel Dichoso személyesen elôttem?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Jól gondolja, kapitány. Már régóta egymás sarkában vagyunk, nem igaz?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Már abból is tudom, hogy hazudsz, ha rád nézek, haver. Te nem Dichoso vagy. Elolvastam a 'Santa Quiteria' kapitányának naplóbejegyzéseit, és körbekérdeztem a külsejérôl. Nem hasonlítasz rá. Még csak egy sebhely sincs az arcodon a lovassági kardtól. Ugyan már, még egy pantomimmal is megpróbálhattad volna legalább felrajzolni!";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Pontosan. Ha jól értem, azért vagyunk itt, hogy Tayasal elveszett városáról beszéljünk?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Ha! Akkor nincs értelme folytatni ezt a bohózatot. Miguel figyelmeztetett, hogy egy ravasz gazember vagy...";
			link.l1 = "Hol van Miguel Dichoso?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "Nincs itt. Engem hatalmaztak fel, hogy találkozzak önnel és beszéljek önnel az ô nevében.";
			link.l1 = "Nem fogok egy bábuval beszélni. A király miatt vagyok itt. Hol van?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Nem egy kellemes beszélgetôpartner, kapitány. Elvesztette a nyugalmát.";
			link.l1 = "Elég a játékból, értem én. Ez megint egy rajtaütés. Új trükkökkel kell elôrukkolnotok, fiúk.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "Haha, megint igazad van, haver! Az embereim várnak rád a katakombákba vezetô ajtó mögött. Ráadásul a muskétásaim a sírkövek mögött rejtôznek, lövésre készen. Nincs menekvés. Szóval bármennyire is ismétlôdô ez a trükk, te máris belemásztál! A vágyad, hogy lásd Tayasalt, felülmúlta a józan eszedet!";
			link.l1 = "Remek helyet választottál a harcra, söpredék! Nem kell messzire mennem, hogy eltemesselek téged és a rabló barátaidat.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Haha! Tetszik a szellemességed! Akárcsak Miguelé! Mondj, amit akarsz, mindketten ugyanabból a ruhából vagytok kivágva... Azt teszem, amit parancsolt - a lehetô leggyorsabban és fájdalommentesen küldelek a pokolba. Fegyverbe, fiúk!";
			link.l1 = "Jobb emberek is próbálkoztak már nálatok. Add át üdvözletem az ördögnek, gazember!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "Tényleg el akarsz jutni a városba? Megértem, kapitány, de nem hiszem, hogy ez jó ötlet.";
			link.l1 = "Akkor mirôl akarunk itt beszélgetni?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "Nem akarok hosszú, romantikus beszélgetésbe bocsátkozni veled. Ön itt van, és ez nekem elég.";
			link.l1 = "Elég a játékból, értem én. Ez megint egy rajtaütés. Új trükkökkel kell elôrukkolnotok, fiúk.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "Várom a parancsát, kapitány!";
			link.l1 = "A dzsungelen keresztül a capsterville-i temetô felé vesszük az irányt. Ha odaértünk, ne menjünk be a temetôbe. A kapu elôtt foglaljanak tüzelôállást, és figyeljenek, amikor bemegyek. Ha harcot hallotok, azonnal rohanjatok be.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "Várom a parancsát, kapitány!";
			link.l1 = "A dzsungelen keresztül megyünk a capsterville-i temetôbe. Ha odaértünk, ne menjetek be a temetôbe. Az ösvény mentén vegyétek fel a tüzelôállásokat, vegyétek körbe a temetôt, és figyeljetek, mikor megyek be. Ez az egész terv csapdától bûzlik. Amint meglátjátok az ellenséget, azonnal támadjatok.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "Rendben. Elôre!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "Hobart százados! A kémünk információi szerint a lázadók ebben a birtokon rejtôzködnek. Öt dragonyos áll a rendelkezésére. Kutassák át az épületet, és fogjanak el mindenkit, aki ott lóg! Ne bánjanak kesztyûs kézzel ezekkel a söpredékekkel. A király nevében cselekszel!";
			link.l1 = "Igenis, uram!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "Tsk! A tenger fia!";
			link.l1 = "Eh... mi? Hozzám beszélsz?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "Hát persze. Kakaólevél vagyok. Üzleti ügyben jöttem hozzád, Tenger Fia.";
			link.l1 = "Nem tudom, hogy néz ki a kakaó, vagy hogy miért neveztek el róla. De rendben, mondd el, mit akarsz, gyorsan.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "Tsk! Menj a városba. Vegyél két pisztolyt és két tíz puskaport és töltényt. Add ide nekem. Jutalom jár érte. A tenger fia elégedett lesz.";
			link.l1 = "Két pisztolyt és húsz töltényt? Ez minden? Akkor miért nem veszed meg magadnak?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "Nem érted, sápadtarcú? Ki adna el nekem tûzfegyvert?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "Tudod, találkoztam már a fajtáddal Martinique-on... Kannibálokkal. Elraboltak egy lányt és két férfit. Megsütötték és megették az egyik férfit. Ha bármelyiküknek lett volna fegyvere, most nem beszélgetnénk errôl.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "És miért van szükséged fegyverre, Kakaólevél? Meg akarsz ölni valakit?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "Goo-oo! Kakaólevél nem rabló, az én harcom csak a te törzsed harcosainak szól. Sápadtarcúak jönnek a földünkre, rabszolgákká tesznek minket. Kakaólevél maga is harcol. Fogjatok egy rabszolgát. Nem jó, nem rossz. Így megy ez. Indián, fehér, nincs különbség. Tûzfegyverekkel nem mindegy.";
			link.l1 = "És miért van szükséged fegyverre, Kakaólevél? Meg akarsz ölni valakit?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "Harcolni. De egyenlô feltételek mellett. A sápadtarcúaknak van tûzfegyverük, az indiánoknak nincs. Ez nem igazságos. És hogy egy indiánnak tûzfegyvere van - ez védelmet jelent a sápadtarcúak igazságtalan bánásmódja, megalázása vagy sértegetése ellen.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "Igen, kapitány. A sápadtarcúak lenéznek minket.";
			link.l1 = "Észrevettem. Európában arról prédikálnak, hogy az indiánokat megtanítják az igaz hitre, és hogy mindannyian békésen dolgozunk együtt az ültetvényeken...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Tichingitu talán nem érti a kapitányt, de érti Kakaólevelet. Bosszút akar állni.";
			link.l1 = "Úgy tûnik... Nem akarsz te is bosszút állni a legutóbbi fogvatartóinkon?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Talán. De Tichingitu nem fog ehhez folyamodni. Tichingitu most veled van. És Tichingitu a saját fejét használja. Túl sok vér fog folyni. Fehér vér. Indián vér. Túl sok szenvedés. Ez nem helyes.";
			link.l1 = "Igen, már most is rossz a helyzet, és ha segítünk Kakaólevélnek fegyvereket szerezni, az csak rosszabb lesz... De igaza van. És még mindig van egy csapat, akit hamarosan ki kell fizetnem.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Használja a saját fejét, kapitány.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "A tenger fia sokat beszél. Úgy néz ki, mint egy bajszos squaw.";
			link.l1 = "Egy bajuszos fickónak néz ki. Magyarázd meg ezt nekem, Kakaólevél. Én is sápadtarcú vagyok, és te fegyvereket kérsz tôlem, hogy sápadtarcúakkal harcoljak. Ez nem ellentmondásos? Miért közelítesz felém?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "Hallottam a beszélgetésedet azzal a furcsán öltözött indiánnal. Te nem olyan vagy, mint a többi sápadtarcú. Te megérted Tichingitu-t. És biztos vagyok benne, hogy érted Kakaólevelet is.";
			link.l1 = "Ó... Mit ajánlasz fegyverekért, Kakaólevél?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "Az istenek könnyeit. Gyöngyöknek hívod ôket. Sok gyöngy.";
			link.l1 = "Meghoztam a döntésem, Kakaólevél. Várj itt, megyek a fegyverkereskedôhöz. Megveszem, amire szükségem van, és visszajövök.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "Meghoztam a döntésem, Kakaólevél. Véletlenül már megvan, amire szükséged van. Tessék, tessék.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "Meghoztam a döntésem, Kakaólevél. Nem akarok felesleges bajt okozni. Tôlem nem kapsz lôfegyvert. Menjetek tovább.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "Tsk!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "Uh-oh! Van a Tenger Fiának muskétája? Nagy árat fizess egy muskétáért!";
			link.l1 = "Nem, de egy ágyú a hajómról megteszi? Tûnj el most, Kakaólevél, mielôtt észrevesznek és letartóztatnak.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("Kaptál 180 kis gyöngyöt.");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "Jó üzlet! Tenger Fia, ha a Selva-ba mész, vigyél magaddal egy tûzfegyvert. Ha találkozol egy indiánnal, legyél alkudozó.";
			link.l1 = "Ezt megjegyzem. Viszlát, Kakaólevél.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			ReturnOfficer_Tichingitu();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "Kakaólevél várni fog.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Bah, úgy néz ki, mintha itt bennszülöttek gyülekeznének!\nMég mindig vissza akarsz menni a börtönbe, kutya?\nMit keresel itt, Monsieur?";
			}
			else
			{
				dialog.text = "Állj! Mit keres itt, Monsieur?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Hé, söpredék, erre a derék polgárra vártál?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "Nekem minden sápadtarcú egyforma. De ezt még sosem láttam. Te, harcos, tedd velem, amit tenned kell. Kezd fárasztó lenni. Kakaólevél készen áll, hogy szembenézzen az erdô szellemeivel.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "A pokol vár rád, nem az erdô szellemei.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Kapitány, távozhatsz. Ne állj az utamba. A város védelme komoly dolog.";
			link.l1 = "Értem... De mi van ezzel az indiánnal?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "Miért érdeklik az indiánok, Monsieur? Bár... nos, igen, ön frissen érkezett Európából\nHow's Paris? Még mindig szétnyomják a városi patkányokat, vagy már meghívják ôket az úrvacsorára? Nálunk ugyanis patkányok helyett bennszülöttek élnek. Üzletelnek a kalózokkal, megtámadják a favágókat, megeszik az embereket, a fenébe\nHárom nappal ezelôtt valami okos egyén már eladott egy muskétát az ilyeneknek. És képzeld, mi történt? Azok a szemetek megölték az összes katonát az ôrjáratban, amelyet egyébként a barátom és bajtársam vezetett. Megtaláltuk az áruló gyarmatosítót, és felkötöttük a napon száradni, hogy példát statuáljunk vele. Fegyvert adni indiánoknak! Ez árulás! Árulás Franciaország ellen! Már egy ideje követjük ezt a színes majmot, mivel már ismerôs arccá vált a különbözô rendezvényeken\nHát, most eléri gyors és megérdemelt végét. Továbbléphet, kapitány. Ne keveredjen bele olyan ügyekbe, amelyek nem tartoznak magára. Maga nem része ennek a háborúnak... Még nem... Vagy mégis?!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Megbízható", "Trustworthy");
				link.l1 = "(Megbízható) Tudja, biztos úr... Charles de Maure kapitány vagyok, a Fadey Muscovite vendége. Bizonyos érdekeltségünk van ebben az indiánban... úgyhogy ne zavarjuk egymás kötelességeit. Egyetért, hadnagy úr?";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "Az újonnan érkezôkkel szembeni viselkedés, a bennszülöttekkel szembeni viselkedés... Gyarmatosítók, bennszülöttek... Még nem értem ezt az egészet, de ebben a pillanatban, hadnagy úr, az összehasonlítás nem kedvez önnek... A csatára!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "Igaza van, hadnagy úr, nem vagyok az. Viszontlátásra.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "Ahem! Értettem, kapitány. Kérem, adja át üdvözletemet Fadey úrnak. Osztag, folytassátok a járôrözést!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "Ajjaj!";
			link.l1 = "Igen, nos, még én is meglepôdtem, hogy ez mûködött. Itt vannak az árucikkeid, Kakaólevél.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "A tenger fia jól beszél. Egy indiánt megmenteni nagy dolog! Nagy jutalom!";
			link.l1 = "Hû, ez aztán a zsákmány... És egy lyukas kô, meg valami amulett.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("Kaptál 180 kis gyöngyöt.");
			Log_info("Amulettet kaptál 'Cascavella'}");
			Log_info("Megkapta Védelmezô 'Adder kô'");
			Log_info("Kaptál 3 Datura gyógynövényt.");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "Van a Tenger Fiának muskétája? Nagy árat fizet egy muskétáért!";
			link.l1 = "Nem, de egy ágyú a hajómról megteszi? Tûnj el most, Kakaólevél, mielôtt észrevesznek és letartóztatnak.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "Jó üzlet! Tenger Fia, ha a Selva-ba mész, vigyél magaddal egy tûzfegyvert. Ha találkozol egy indiánnal, legyél alkudozó.";
			link.l1 = "Ezt megjegyzem. Viszlát, Kakaólevél.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "Uh-oh! Rossz döntés, tenger fia. Miért tetted ezt?";
			link.l1 = "Ugh... Öt perccel ezelôtt még helyesnek tûnt... Most már nem vagyok benne olyan biztos. .... Végül is megöltem a sajátjaimat. Most mit kellene tennem? Mi van, ha rájönnek? A francba! A francba!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Most rajtaütés lesz. A katonák mindenkit megölnek. Két ôrjárat nem bocsát meg. Kakaófalevél futás. És te, a tenger fia... miért? Kakaólevél úgyis meghal. A szellemek így akarják.";
			link.l1 = "Ó... az egyezségünk még mindig áll?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Rossz döntés, Tenger Fia. De köszönöm. Nagy jutalom.";
			link.l1 = "Nem is olyan nagy, mindent összevetve...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("Kaptál 180 kis gyöngyöt.");
			Log_info("Amulettet kaptál 'Cascavella'}");
			Log_info("Megkapta Védelmezô 'Adder kô'");
			Log_info("Kaptál 3 Datura gyógynövényt.");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Tenger fia, ha túléled, és elmész a Selva-ba, vigyél magaddal egy tûzfegyvert. Találkozol egy indiánnal, és alkudozol.";
			link.l1 = "Ezt megjegyzem a jövôre nézve. Viszlát, Kakaólevél.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Üdvözlet, Charles de Maure kapitány. A nevem Charles Barbier. Szánna rám egy percet az idejébôl?";
			link.l1 = "De Maure kapitány... Igen, én vagyok az! Kérem, folytassa, Monsieur Barbier.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "Mindig öröm találkozni egy kollégával, különösen egy olyannal, akivel közös a nevem! Van egy ajánlatom az ön számára, kapitány. Tudja, szükségem van egy kísérôre St. Pierre-be, és...";
			link.l1 = "Ismerem St. Pierre-t! De az csak kétnapos út! És be kell vallanom, hogy még eléggé zöldfülû vagyok a kísérô szerepéhez. Csak egy hete vettem át a hajó parancsnokságát.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "Értékelem az ôszinteségét, kapitány. Charles, bocsássa meg a kötetlenségemet, de pontosan ön az a személy, akire szükségem van.";
			link.l1 = "Hmm... Emlékszem egy hasonló ajánlatra nem is olyan régen. Egy kalózok által elkövetett rajtaütéshez vezetett Le Francois közelében.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "Hallottam errôl az esetrôl, ezért kerestem meg önt\nElôször is, meglehetôsen értékes szállítmányt viszek, és mindig leselkednek rám ragadozók. Azonban a Le Francois melletti kalózok felett aratott nemrégiben aratott diadala elgondolkodtatja az ottani gazembereket\nMásrészt, a Fadey Muscovite-tal való kapcsolata erôs megerôsítés.";
			link.l1 = "Meggyôzô érv, Monsieur. És milyen ellentételezést javasol ezért a szívességért?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "Ez nem szívesség, kapitány, hanem egy kölcsönösen elônyös vállalkozás! Negyven aranyat fizetek, ha idôben elkísér St. Pierre-be.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Megbízható", "Trustworthy");
				link.l1 = "(Megbízható) Mivel az ellenkezô irányba tartok, Monsieur, elôre kérem a fizetséget.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "Nem rossz ajánlat - úgyis abba az irányba tartok. Megegyeztünk!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "Értékes szállítmány, azt mondja? Sajnos, uram, egyelôre elegem van a kalandokból.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "Nehéz visszautasítani egy ilyen komoly fiatalembert, kapitány. Itt van a negyven dublonja. Késedelem nélkül kihajózunk? Az idô pénz.";
			link.l1 = "Nem maradunk sokáig, uram. Hamarosan indulunk.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("Kaptál 40 dublont");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "Kitûnô! Azonnal felkészülök az indulásra!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "Értettem, kapitány. Nem akarok tolakodó lenni. Viszlát, és jó napot.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Köszönöm a példás kíséretet, kapitány. Örülök, hogy nem történt semmi incidens.";
				link.l1 = "Öröm volt önnel üzletelni, Monsieur. Most pedig, ha megbocsát, sok dolgom van.";
			}
			else
			{	
				dialog.text = "Köszönöm a példás kíséretét, kapitány. Örülök, hogy nem történt semmi incidens. Itt a fizetség - negyven dublont teljes egészében.";
				link.l1 = "Öröm volt önnel üzletelni, Monsieur. Most pedig, ha megbocsát, sok dolgom van.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("Kaptál 40 dublont");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Charles...";
			link.l1 = "Igen, Charles? Úgy látom, gondterhelt vagy. Valami baj van?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Nos, mivel megbízható ember vagy, és ismered Fadeyt... Nézze, a kereskedelem kockázatos dolog, igaz?";
			link.l1 = "Ha maga mondja.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "Sikerült szereznem egy csomó kötelet olcsón Guadeloupe-on... tudod... Úgy terveztem, hogy gyorsan eladom ôket St. Pierre-ben, és a bevételbôl kávét veszek Willemstadban. Jó tervnek tûnt.";
			link.l1 = "Nem kérdôjelezem meg a becsületességét, Monsieur, de ez az egész eléggé kétesnek hangzik. Úgy beszél a rakományáról, mintha arany lenne. Eközben a hajóm tele van ezekkel a kötelekkel, és piszkosul olcsók.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Charles, ezek a kötelek a legjobb minôségûek, kiváló kenderbôl készültek, és a moszkvai cár gyáraiban szôtték ôket. Stratégiai célokat szolgálnak, és a hadihajók kötélzetéhez használják ôket. Az angolok monopolizálják a kereskedelmi útvonalakat Moszkva felé, és tiltják az ilyen kötelek szabad kereskedelmét. Más nemzetek is intenzíven versengenek azért, hogy az európai hajógyáraik számára biztosítsák a rendelkezésre álló készletek egészét.";
			link.l1 = "Tehát ez csempészet?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Igen. Sajnos tavaly összevesztem a santiagói csempészekkel. Már majdnem elfelejtettem, de ezek az emberek szoros kapcsolatokat ápolnak és hosszú emlékezetûek. Egy jótanács: kerülje el, hogy felbôszítse ôket és felrúgja az üzleteket; ezt a helyzetet késôbb nem fogja helyrehozni.";
			link.l1 = "Köszönöm, de a csempészet nem érdekel.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "Kár! A tisztességes kereskedelem szép hasznot hozhat, de jelentôs vagyont sosem fogsz felhalmozni. Mindazonáltal nem ok nélkül kezdeményeztem ezt a meglehetôsen bizonytalan beszélgetést önnel. Javaslom, hogy vásároljon tôlem egy szállítmány kötelet. A helyi csempészek gyakran megfordulnak a kocsmában, és lelkes vevôi lesznek ennek a szállítmánynak. Gondolj csak bele! Ma jelentôs hasznot húzhatsz belôle anélkül, hogy a nyílt tengerre merészkednél.";
			link.l1 = "Mennyit kérsz a rakományért?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "Tízezer pezót. Ez szerény összeg, és a kötelek csempészeknek való továbbértékesítése jelentôs hasznot hoz.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "Sosem bocsátanám meg magamnak, ha kihagynék egy ilyen lehetôséget. Vigye az ezüstöt, és gondoskodjon róla, hogy az áru azonnal a hajómra kerüljön.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "Ez egy bizonytalan vállalkozás, barátom. Találkozzunk félúton, rendben? Elfogadom a kötelet hétezerért.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "Ez jelentôs összeg, uram. Megértem a helyzetét, de nem vállalhatok ekkora kockázatot.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "Hálám, Charles! Megkíméltél az anyagi tönkremeneteltôl! Az árut gyorsan és a legnagyobb óvatossággal fogjuk elszállítani\nMegengedi, hogy kereskedôtársként egy tanácsot adjak: ha egyszer felfogadott egy tisztességes pénztárost, szerezzen be kávét Saint-Pierre-ben, és adja el nyereséggel Willemstadban. A helyi fôvárosok bôségesen fizetnek a gyarmati árukért, és jelentôs haszonnal exportálják Európába. Sok szerencsét a vállalkozásodhoz, barátom!";
			link.l1 = "Viszontlátásra, uram.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("Kaptál 30 kötelet");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				Notification_Skill(true, 25, SKILL_COMMERCE);
				dialog.text = "Hálám, Charles! Megkíméltél az anyagi tönkremeneteltôl! Az árut gyorsan és a legnagyobb óvatossággal fogjuk elszállítani\nMegengedi, hogy kereskedôtársként egy tanácsot adjak: ha egyszer felfogadott egy tisztességes pénztárost, szerezzen be kávét Saint-Pierre-ben, és adja el nyereséggel Willemstadban. A helyi fôvárosok bôségesen fizetnek a gyarmati árukért, és jelentôs haszonnal exportálják Európába. Sok szerencsét a vállalkozásodhoz, barátom!";
				link.l1 = "Viszontlátásra, uram.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("Kaptál 30 kötelet");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				Notification_Skill(false, 25, SKILL_COMMERCE);
				dialog.text = "Nem tehetem, kapitány. Az árum komoly, és komoly kezelést igényel. A legtöbb szabad kapitány nem mer stratégiai árukkal kereskedni. Sajnálatos módon az alkudozás itt nem indokolt.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "Sosem bocsátanám meg magamnak, ha kihagynék egy ilyen lehetôséget. Vigye az ezüstöt, és gondoskodjon róla, hogy az áru azonnal a hajómra kerüljön.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "Ez jelentôs összeg, uram. Megértem a helyzetét, de nem vállalhatok ekkora kockázatot.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "Kár érte! Viszlát, kapitány.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Baj van, kapitány.";
			link.l1 = "Nos?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "A navigátorunkat letartóztatták és a helyi börtönbe vitték. Azt mondják, adósságprobléma.";
			link.l1 = "Mi, már megint?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "Ô egy rosszcsont, kapitány.";
			link.l1 = "Micsoda szörnyû idôzítés! Navigátor nélkül itt ragadtunk. Megint nekem kell letennem érte az óvadékot! Beszélek a parancsnokkal...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "Beszélhetek, kapitány?";
			link.l1 = "Menjen csak.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "Minek ez a sok fáradozás? Egy ilyen ember csak bajt hoz a hajóra.";
			link.l1 = "Van más választásom? Alig van más navigátor, így a lehetôségeim eléggé korlátozottak.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "Igaz, hogy nehéz elsôrangú navigátort találni, de még nem kell mester, csak egy hozzáértô. A helyzeted megváltozott az elmúlt héten, ugye tudod? Már nem kell a hordó fenekét kaparni, hogy embereket találj a legénységedbe. Az emberek most arról beszélnek, hogyan gyôzted le azt a kalózt, és milyen kapcsolataid vannak. A legénység is mögötted áll, kapitány, kedvelünk téged.";
			link.l1 = "Ez megnyugtató, Alonso. És mi a legénység véleménye Delucról?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "Gyorsan tanul, kapitány. A legénység azt mondja, hogy bár jó képességû tiszt, és tisztességesen bánik velünk, nem éri meg a fáradságot. Egy nagy kereskedôhajó csak úgy elengedte a tisztjeit - talán a kocsmában keresgél? A megfelelô fickó biztosan ott van. És felejtsd el Delucot; ezt beszélik az emberek.";
			link.l1 = "Köszönöm a tanácsot, Alonso. Tudtam, hogy számíthatok rád. Menj vissza a hajóra, és vedd át az ôrséget, amíg én ezt elintézem.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "Igenis!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Alonso_DlgExit");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Sapka...";
			link.l1 = "Millió kérdésem lenne, de csak egyet teszek fel: hogyan sikerült újabb adósságokat felhalmoznod, miközben egész idô alatt velem voltál, és tengerészetet tanítottál nekem!";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "Szégyellem bevallani, kapitány, de már jóval azelôtt kölcsönöztem különbözô kölcsönzôktôl, hogy csatlakoztam volna a legénységéhez. Az volt a tervem, hogy meghúzom magam, és addig dolgozom a hajóján, amíg nem keresek eleget, hogy kifizessem az összes adósságomat. De elkövettem azt a hibát, hogy elhagytam a hajót, hogy itt St. Pierre-ben összejöjjek egy bizonyos nôvel, és a katonák letartóztattak a hajóról. Martinique-on nem halmoztam fel újabb adósságot, hiszen önök kifizették az utolsó adósságomat, esküszöm!";
			link.l1 = "Maga egy idióta, Deluc, és St. Pierre nevetségessé tett engem!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Lenyûgözô, Folke. Köszönöm az anekdotát.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Mit fog tenni, kapitány? Megint ki tudsz menteni? Tudja, nem lesz könnyû új navigátort találni...";
			link.l1 = "Egyelôre maradj nyugton. Majd én döntök. Lehet, hogy újra meglátogatom a bankárt.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Mit fog tenni, kapitány? Megint ki tudsz menteni? Tudja, nem lesz könnyû új navigátort találni...";
			link.l1 = "Egyelôre maradj nyugton. Majd én döntök. Lehet, hogy újra meglátogatom a bankárt.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "Nem mintha lenne hova mennem...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Folke_DlgExit_1");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Kapitány, köszönöm. Rendezte az adósságomat, de most még nagyobb adóssággal tartozom önnek - az életemmel. És igazán hálás vagyok érte! Biztosíthatom, hogy ennél hûségesebb embert sehol a világon nem talál!";
			link.l1 = "Azt hiszem, néhány adósságot csak úgy lehet visszafizetni, ha újabbakat vállalunk. Menjünk vissza dolgozni, Folke. Sok a tennivaló a tengeren.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "Ezt ne felejtsd el, Deluc. Legközelebb egyszerûen lelôlek.";
			link.l2.go = "Del_Folke_11b";
			Del_Ohrannik();
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			AddDialogExitQuestFunction("Del_Folke_DlgExit_2");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "Szüksége van egy tisztre, kapitány?";
    		Link.l1 = "Egy tiszt? És miben vagy jó?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "Nem, van teljes felszerelésem.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "Én vagyok a legjobb navigátor ezeken a vizeken. Még mindig tudok egy keveset az orvostudományról. És kész vagyok szívességet tenni neked, és alattad szolgálni.";
			Link.l1 = "És mennyit akarsz?";
			Link.l1.go = "Del_price";
			Link.l2 = "És miféle szakember vagy te?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "Sajnos, már van egy navigátorom.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "Azt hiszem, 4000 pezóban meg tudunk egyezni.";
			Link.l1 = "Nem túl sok ez egy kicsit?";
			Link.l1.go = "Del_trade";
			Link.l2 = "Egyetértek. Tekintsd magad a legénység tagjának.";
			Link.l2.go = "Del_hire";
			Link.l3 = "Nem éred meg ezt a pénzt.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "Meggondolta magát, kapitány? Úgy döntött, hogy egy új navigátor nem ártana?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Valami ilyesmi. Mennyit akarsz?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "És mire vagy képes?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "Van egy teljes készletem. Viszlát.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "Rendben... Azt hiszem, még 2500 pezóban is meg tudnék egyezni. Mit szólsz hozzá?";
				Link.l1 = "Így már jobb. Benne vagy.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "Sajnálom, kapitány, de pontosan annyit érek, amennyit kértem. Ha ez túl sok neked, akkor keress valaki mást.";
				Link.l1 = "Rendben, egyetértek. Elviszlek.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "Ezt fogom tenni. Viszontlátásra.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Köszönöm, kapitány. Nem fogja megbánni a döntését.";
					Link.l1 = "Remélem is.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "Látom, kevés a pénze, kapitány! Sajnálom, de én nem dolgozom hitelben.";
					Link.l1 = "Ó, az ördögbe!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Köszönöm, kapitány. Nem fogja megbánni a döntését.";
					Link.l1 = "Remélem is.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "Látom, kevés a pénze, kapitány! Sajnálom, de én nem dolgozom hitelben.";
					Link.l1 = "Ó, az ördögbe!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "Csak befejezem az italomat, kapitány, aztán megyek a hajóra. Ne aggódjon, idôben odaérek.";
			Link.l1 = "Rendben. Ha elkésel, akkor a fedélzetet fogod felmosni!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			DialogExit();
			AddDialogExitQuestFunction("Del_shturman_DlgExit");
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "Rendben, rendben! Megadom magam, a fenébe is!";
			link.l1 = "Mostantól a foglyom vagy, de hamarosan St. Pierre-ben találod magad az akasztófával szemben.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "Akkor ennyi volt... Honnan tudtad, hogy hol találsz meg?";
			link.l1 = "A kormányzó személyesen tájékoztatott a helyzetrôl.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "Micsoda barom! Biztosan tudomást szerzett a terveimrôl, és úgy döntött, hogy nyíltan megdug a barlangja elôtt, hogy példát mutasson a többi legénységnek!";
			link.l1 = "Még egy sértés Ôexcellenciájának, és az útja St. Pierre-be gyors és felejthetetlen lesz.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "Mi? Nem a méltóságodról beszélek, haver. Jacques-ról, a Goodmanrôl beszélek\nA fenébe, a pletykák igazak voltak! Barbazon rájött, hogy veszélyt jelentek, ezért átadott a kormányzónak, hogy ne álljak az útjába. Ezért volt meg a pontos tartózkodási helyem - és ezért kaptak el letolt gatyával, ha-ha!";
			link.l1 = "Maga téveszmés. Martinique kormányzója nem süllyedne le odáig, hogy egy kalózvezérrel üzleteljen!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "Igen, persze. Talán nem közvetlenül, de szerintem Barbazon-nal kötött egyezséget. Ez neki kényelmes: egy veszélyes kalózt felakasztanak, a jelentések szépen néznek ki, és a 'a katonai mûvelet' költségei indokoltak. Tudod, hogy szolgáltam? Szóval tudom, hogyan megy ez ott. És te? Ön a helyôrségben szolgál?";
			link.l1 = "Én a hazámat szolgálom, és ennek a beszélgetésnek vége. Isten hozta a fogdában.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Várj, haver. Nem vagyok kasztíliai, és nem azért voltam ma a tengeren, hogy fosztogassam a fench kereskedôket. Nekem elveim vannak, a fenébe is! Kössünk alkut, rendben?";
			link.l1 = "Csak az idôdet vesztegeted, kalóz. Be a hajóra veled együtt.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "El akarod kerülni a hurkot?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "Szilárd elônyöm volt itt, és ha elengedsz, beváglak. Az életem csak pár ezret ér ezüstben, de sokkal többet tudok neked keresni - és adómentesen.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "Ez egy csábító ajánlat... Bár a kalózkodás nem éppen az erôsségem.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "Nem vagyok kalóz!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "Rajtad áll, haver. Hogy szerencsés ember akarsz-e lenni, vagy egy nincstelen kapitány, akinek elvei vannak. Ha igazi pénzt és szabadságot akarsz, akkor mindenbôl kell egy kicsit belekóstolnod. Ragadj meg minden lehetôséget.";
			link.l1 = "Maga aztán tud bánni a szavakkal...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Ahem... Azt hiszem, elviszem St. Pierre-be. Ez tûnik a helyes megoldásnak.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "Akkor baszódj meg!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "Szóval, megegyeztünk?";
			link.l1 = "Igen. Mondja meg, ki a fônök, és szabadon távozhat.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "Van egy okostojás angol a Henryn, egy bárkán. Éppen befejezni készül a kis kereskedelmi útját, a francia ültetvényekrôl szállít árut Willemstadba, busás haszonért. Nemsokára elhagyja Martinique-ot és Curacao-ba megy. Könnyû dolga van - nincs kíséret, és a bárkát a védelmének rovására értéktárgyakkal rakják meg. Túl sokáig tart, ezért pletykák terjednek. A tanácsom, haver? Ne szégyenlôsködjön a kocsmában. Néhány ital a helyieknek, és ôk majd elárulnak néhány titkot.";
			link.l1 = "Miért nincs kíséret?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "Hogyan máshogy intézhetné egy angol csendben az üzleti ügyeit Curacaón? Anglia és Hollandia között nyílt háború dúl, és a kereskedelmi engedély megszerzése nehézkes és drága.";
			link.l1 = "De Franciaország és Anglia között nincs háború. Milyen következményekkel jár, ha megtámadok egy semleges hajót?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "Semmi, ha diszkrét vagy. A legénység biztosan dicsekedni fog a hôstetteiddel a legközelebbi kikötôben, de amíg nem rendszeresen angol vagy holland hajókat zsákmányolsz, addig minden rendben lesz. Közelítsd meg a Henry-t francia színekben. Töltsd meg az ágyúidat grapeshot-tal, közelítsd meg a távolságot, engedd fel a Blacket, lôj le néhány sortüzet, és szállj fel a szuka fedélzetére. Egyszerû, haver.";
			link.l1 = "Majd meglátjuk. Becsületszavamra elengedlek. Ne adj okot arra, hogy megbánjam.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "Nem fogom. Jó vadászatot, haver.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... Majd én elintézem a szerencsejáték ügyeit. Hé! Szedd össze magad, ember! Vagy összeszeded magad, vagy én magam rázom rád az eszed.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "Monsieur, elnézést kérek, de egy kicsit zavarja a dolgokat.";
			link.l1 = "Igen, persze. Kellemes napot, uraim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_DiegoInTaverna_3");
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "De Maure kapitány! Várjon, várjon!";
			link.l1 = "Igen, hadnagy úr?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "Alig tudtam lépést tartani önnel. Volt egy kis... csuklás, kapitány. Micsoda zûrzavar!";
			link.l1 = "Vegyen egy nagy levegôt és nyugodjon meg, kérem.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "Rendben, rendben. Figyeljen, miután megtöltöttük az ágyúkat, van még hely a raktérben?";
			link.l1 = "Még új vagyok ebben, úgyhogy nem vagyok benne teljesen biztos, de feltételezem, hogy van.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "Remek! A parancsnokság minden lehetséges módon támogatni akarja a Porto Bello-i mûveletet, ezért további kétszáz adag puskaport rendeltek a Warlike-nak. Lehet, hogy nem tûnik soknak, de néhány extra lövedék megfordíthatja a csata menetét!";
			link.l1 = "Rendben van, hadnagy úr. Készen állok rá, hogy kivegyem a részem. Töltse be a puskaport - egyáltalán nem bánom.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Köszönöm, kapitány. Azonnal értesítem a rakodó személyzetet. Szerencsére még nem végeztek a '" + PChar.Ship.Name + "' . Sok szerencsét a küldetéshez!";
			link.l1 = "Köszönöm, bár eddig elég kaotikus volt. Viszlát, hadnagy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "Jézusom, kapitány! Hála az égnek, hogy sértetlen!";
			link.l1 = "Mi a fasz történt?! Mi történt a hajómmal?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "Nem tudom, kapitány! Épp most búcsúztam el egy helyi nôtôl, akivel nemrég találkoztam... A francba! Eugenie!";
			link.l1 = "Meghalt, "+npchar.name+". Sajnálom, de koncentrálnunk kell, hogy lássuk, nem sérült-e meg valaki a legénységbôl.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "Alig ismertük egymást... Aaah! Bassza meg! Jelentem, kapitány: a legénység nagy része a parton volt, amikor a robbanás történt - szerencsére. A fiúk a következô nagy utazásunk elôtt egy kis szárazföldi szabadságot vettek ki. De a hajó ôrsége... Attól tartok, nincsenek túlélôk. Nézzenek csak körül! A törmelék még itt, ezen a mólón is megsebesített vagy megölt embereket! Csoda, hogy mi ketten sértetlenek maradtunk.";
			link.l1 = "Mi van a hajóval? Jól van?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "Jól van?! Elnézést kérek, kapitány. Nehéz biztosra mondani, de úgy tûnik, a robbanás a felsô fedélzeten történt, nem alul. Nem látok aktív tüzet, és úgy tûnik, megúsztuk a nagyobb károkat.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			
			VsD_AfterVzriv_1();
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_2");
		break;
		
		case "VsD_Komendant":
			dialog.text = "Mi az ördög folyik itt, kapitány?!";
			link.l1 = "Én is ezt kérdezem, ezredes!";
			link.l1.go = "VsD_Komendant_1";
			VsD_AfterVzriv_3();
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "Vigyázzon magára, de Maure! Elfogadta ezt a munkát a haditengerészettôl, nehéz ágyúkat vállalt - a korona tulajdonát, stratégiai fontosságúakat! Felfogja, hogy ezeknek az ágyúknak milyen jelentôsége van az egész hadmûvelet szempontjából?! Az ön hanyagsága miatt közel négyszáz ember és egy francia hadihajó került veszélybe! Árulás miatt bíróság elé áll!";
			link.l1 = "Nyugodjon meg, ezredes! Csodával határos módon, úgy tûnik, a hajóm túlélte, és az értékes rakománya nagyrészt sértetlen... nagyrészt.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "Hogy érti azt, hogy nagyrészt?!";
			link.l1 = "Nem tudom garantálni, hogy a kétszáz mérô puskapor, amit az utolsó pillanatban töltött be az egyik hadnagya, nem sérült meg. Ezeket kellett volna utoljára betölteni, és valószínûleg ezek robbantak fel.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "Mi ez az ostobaság, Charles? Milyen hadnagy? Milyen puskapor? Én nem adtam ki ilyen parancsot!";
			link.l1 = "Ez a hadnagy biztosan a helyôrségedbôl való volt. Nem érdeklôdtem a neve felôl, de úgy tûnt, hogy tudott a mûveletrôl.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "A francba! Úgy tûnik, a kasztíliaiak is hajlamosak a piszkos játékra... Majd én elintézem ezt a szerencsétlen helyzetet, kapitány. Önnek azonban még van egy feladata: biztos benne, hogy a hajója tengerálló?";
			link.l1 = "Úszóképes, de határozottan jelentôs javításokra van szüksége.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "Erre nincs idô, kapitány. Azonnal induljon el, és teljesítse a küldetést. A tét túl nagy a késlekedéshez.";
			link.l1 = "Nem kaphatnánk legalább egy napot, az ég szerelmére? A helyi hajógyár el tudná végezni a szükséges javításokat! És mi lesz a legénységemmel?! Biztos vannak áldozatok!";
			link.l1.go = "VsD_Komendant_6";
			VsD_AfterVzriv_4();
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "Ha nem vetted volna észre, a hajógyár lángokban áll. Még mindig vizsgáljuk, hogy szándékos volt-e, vagy a robbanás mellékhatása. Csak azt ígérhetem, hogy a sebesültjeik orvosi ellátást kapnak, és a Korona viseli a halottak eltemetésének költségeit.";
			link.l1 = "Ez most komoly? Ez a legjobb, amit fel tud ajánlani?";
			link.l1.go = "VsD_Komendant_7";
			VsD_AfterVzriv_5();
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Kapitány, Franciaországnak sürgôsen szüksége van a segítségére. Ellátom deszkákkal, és ha okosan játszik, a hajója majdnem teljesen megjavul, mire Jamaicára ér.";
			link.l1 = "Elnézést, de milyen deszkák? És miért Jamaica?";
			link.l1.go = "VsD_Komendant_8";
			VsD_AfterVzriv_6();
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "Az ön legénysége a tengeren a deszkákkal - egy elsôdleges javítóanyaggal - tud vészhelyzeti javításokat végezni. És Jamaica meglehetôsen közel van az egyik útvonalhoz, amelyen Porto Bellóba juthat. Ha nem vesztegeted az idôt, ott befejezheted a javításokat és toborozhatsz egy teljes legénységet.";
			link.l1 = "Rendben. Azonnal útnak indulok, ezredes.";
			link.l1.go = "VsD_Komendant_9";
			
			VsD_AfterVzriv_7();
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_8");
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "Minek ez a sietség, kedvesem?";
			link.l1 = "Drágám, erre most nincs idôm. Nem látod, mi történik?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "Ó, a jelenlegi bajok szörnyûek, de a kezedbôl látom, hogy még több is van a láthatáron.";
			link.l1 = "Ezt bárki láthatja anélkül is, hogy ránézne a kezemre, ami, hozzáteszem, kesztyûben van. Rendben, játszom: mi az ára annak, hogy manapság elkerüljük a katasztrófát?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "Nekem nincs meg ez a hatalmam, szépfiú. És még ha lenne is, nem tudnám elviselni. De még mindig segíthetek neked... a hajóddal. A lány szomorú állapotban van, kedvesem.";
			link.l1 = "Soha nem tudtam, hogy a cigányságodnak asztalos ambíciói lennének.";
			link.l1.go = "VsD_Tsyganka_3";
			
			VsD_Final_1();
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "Maga, kedvesem, maga is aligha ács. Azt hiszed, hogy a deszkák önmagukban megjavítják a hajót? Csak elnehezítenék a dolgot, hacsak nincs egy ácsmester...";
			link.l1 = "Vagy?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "Van egy erôs amulett, amit a helyiek tisztelnek. A fa meghajlik az akarata szerint, és még azok is, akik nem ismerik az ácsmesterséget, képzettnek találják magukat, ha viselik. Ezer pezóért a tiéd lehet, kedvesem.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Rendben, megegyeztünk. Minden segítségre szükségem van.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "Nincs idôm a varázslásodra. Menj békében, boszorkány, és ne avatkozz bele.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Net");
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Da");
			Log_info("Amulettet kaptál 'Teredo'");
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Figyeljen ide, én törvénytisztelô polgára vagyok ennek a városnak. Meg kell kérnem, hogy ne járkáljon úgy, mint egy rabló, a pengéjével.", "Uram, kérem, a törvény világosan kimondja, hogy a város falain belül nem szabad kivont fegyverrel járkálni.");
			link.l1 = LinkRandPhrase("Jól van, rendben.", "Rendben.", "Ahogy kívánod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
