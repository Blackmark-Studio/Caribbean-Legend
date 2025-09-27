// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Mire van szükséged?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "Az ezredes úr jelenleg egy hadgyakorlaton van. Mit akar tôle, kapitány?";
				link.l1 = "Ezúttal, Ben, magára van szükségem. Rossz hírem van a húgodról, Mollyról. Az a gyönyörû lány, úgy tûnik, nagy bajban van. Tortuga kalózai fogságba ejtették. Segítségre van szüksége, és megkért, hogy figyelmeztessem magát. Az embert, aki vállalta, hogy átadja az üzenetet, megölték, de halála elôtt még sikerült beszélnie nekem a húgodról.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "Ha úton vagy Róka ezredes felé, akkor fordulj meg 360 fokban, és menj el. Nem fogad vendégeket.";
				link.l1 = "Rendben van.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Az ezredes nincs itt. Jöjjön be késôbb.";
				link.l1 = "Jól van...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "Ha! Te vagy a legelsô férfi, aki valaha is a húgomat 'szépnek'. nevezte, Isten gránátos testet és Jerikó szarvát adta neki hang helyett. A mi Mollynk tud harcolni magáért\nDe a mi Urunk kreativitása nem csak az álla alatt állt meg. Nem nem, a legszebb dolog, amit tett, hogy elhunyt apánk szôrös, pockos arcát a mellei fölé ragasztotta. És meg kell mondanom, uram, az én öregem arcától a lovak ájultan estek össze.";
			link.l1 = "Látom, nem vagy különösebben feldúlt...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "És miért bukkant fel Tortugán? Molly Catherine Fox, a mi bátor ezredesünk lányának a szolgálója. Catherine Európából érkezett, hogy meglátogassa az apját a születésnapján. De a hajóraj, amellyel a hajója indult volna, késik\nHa látni akarod az igazi Molly Jonest és a szeretôjét, aki egyébként nagyon szép, gyere ide egy hónap múlva. Egy nappal sem korábban.";
			link.l1 = "Kiderült, hogy az ön húga, Molly Jones a Fox kisasszonyt szolgálta, és jelenleg az Atlanti-óceán túlsó partján tartózkodik?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "Pontosan így van! A legutóbbi futár arról tájékoztatott minket, hogy a Cromwell lordprotektor által kiküldött hadihajónak csak egy hónapja kellett volna elhagynia Londont. A brigg 'Albatross' Katalinnal a fedélzetén elkísérte volna ôket. Hogy ez valóban így van-e, a következô postacsomaghajóról megtudjuk. Bár a hajók még nem érkeztek meg, és az ezredes szigorúan megtiltotta, hogy a 'Albatross' egyedül hajózzon\nTudta, hogy szeretett felesége francia korzír támadás során halt meg? Az ezredesnek nem volt könnyû dolga, és még mindig retteg a nyílt tengerek veszélyeitôl... Így nem tudok segíteni Molly Jones-szal, kapitány úr! Sok Molly nevû gyarmatosítólány van! Különben is, a Jones vezetéknév Nagy-Britanniában olyan jó, mintha egyáltalán nem lenne vezetékneve!\nAz Antiguán minden tengeri kutya ismer engem és a parancsnokomat. Nem meglepô, hogy egy bajba jutott szegény lány a segítségemet kéri. Szívesen segítenék, de nincs pénzem váltságdíjra. Az ezredes tartozik nekem háromhavi bérrel, a fizetésem a többiekkel együtt érkezik 'Albatross'.";
			link.l1 = "Úgy tûnik, akkor tévedtem. De azért köszönöm a felvilágosítást.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "Egyáltalán nem, kapitány.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "Mit akar? Nem akarok beszélni.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "Van egy kis dolgom magával, kapitány. Látom, hogy nincs valami vidám hangulatban, és talán az ajánlatom egy kicsit felvidítja.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "Nyugodjon meg, igyon egy kis rumot. Az én hibám, pajtás. Bocsánat.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "A hangja nagyon vonzó! Az arcod pedig olyan, mintha már láttam volna valahol... Csak nem emlékszem, hol láttalak. Mondd meg nekem!";
			link.l1 = "Tudok a Thibaut-val való üzletérôl... Nyugi, haver! Nem kell félned tôlem. Van egy ajánlatom a számodra.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "A pokolba vele! Baszd meg azt a részeg disznót!... Nem sikerült...";
			link.l1 = "Ebben igazad van. A matrózodnak nagy szája volt, de a pletykái nem jutottak túl rajtam. És azok a pletykák nem is jutnak tovább, hiszen te vagy az, aki gondoskodott róla, nem igaz?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "Caramba! Most már felismerlek! Te vagy az, aki feldúlta Doiley ezredest és elvitte az egész szigetét! Nagy üzletet kötöttél a Holland Nyugat-indiai Társasággal, és egy nyugat-maini báróval dörgölôdzöl..... A neve... "+GetFullName(pchar)+", igaz?";
			link.l1 = "Pontos információkkal rendelkezel. Igen, én vagyok. De le tudnál nyugodni egy pillanatra, Robert?";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "Argh! Nos, hogyan is nyugodhatnék meg, amikor a szigetvilág egyik leghíresebb tengeri kutyája érdeklôdik irántam, és nem csak ez, hanem az én üzletemrôl is tudomást szerzett! Mi a fene ütött belém, hogy megtámadtam ezt a brigget! Mit akarsz tôlem?";
			link.l1 = "Fogd be a szád és hallgass meg! Nekem úgy tûnik, mindketten Levasseur fejét akarjuk tálcán. Az a nagyképû hencegô túl nagyra nôtt a nadrágjához képest, és feldühített néhány komoly embert. Szándékomban áll megváltoztatni az erôviszonyokat a szigeten, és de Poincy-t a helyére tenni, de nem akarok felesleges vért ontani egyetlen hazámbeli emberbôl sem, fôleg nem valami mocskos tolvaj miatt. Ön segíthet nekem. Én pedig segíthetek neked és Thibaut-nak megtartani a kiváltságaitokat.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "Várj, várj! Nem hiszek a fülemnek! Fortuna ma rám mosolyog. Igazad van, közösek a céljaink. Veled sokkal érdekesebb lehet... Thibaut jó vívó, de ahhoz nem elég tökös, hogy elvágja a nagybátyja torkát... De egy olyan ravasz cápa, mint te, képes lenne rá. A hírneved közismert\nNincs szükségem a garanciáidra, de a lányért cserébe segítek neked. Szükségem van rá, mint túszra, amíg befejezem az üzletemet a Karib-tengeren. Hamarosan angol fregattok fognak üldözni. Mi az ördög ütött belém, hogy megtámadtam azt a brigget! Olyan könnyû prédának tûnt a hajórajtól elválasztva...";
			link.l1 = "Mi volt benne olyan különleges? A lány, akit Levasseur elôl rejtegetett?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "Igen. Meg kell gyôznie Thibaut-t, hogy váljon el a lánytól. Megkértem, hogy vigyázzon rá, amíg kiderítem, ki az ördög az a lány, de ez 'Miss Jones', vagy hogy is hívják, teljesen kiforgatta a fejét, és most Henry még elôlem is rejtegeti! Hozza el nekem azt a bûbájos szirént, és én megszervezek magának egy találkozót Levasseurrel a városon kívül. Ekkor lesz lehetôséged rajtaütni. A Halszem parton fogok várni.";
			link.l1 = "Megegyeztünk. Most pedig mondd el, hogyan kapjuk el Thibaut-t.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "A kocsmában az emberek megmutathatják az utat a házához. Henri eléggé figyelemre méltó. Fenyegesd meg a leleplezéssel, és vedd rá, hogy hozza el hozzám a lányt. Még aznap tudatom Levasseurrel, hogy az unokaöccse egy ritka szépséget rejteget a város tömlöcében\nA futárom megtalálja a kocsmában. Miután nem találja Henrit, a kormányzó egy kisebb osztaggal elmegy a tömlöcbe, és önnek lesz egy kellemes alkalma elbeszélgetni vele.";
			link.l1 = "Hová szállítsam a lányt?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "Mondd meg neki, hogy maga szállítsa ki a lányt a tengerpartra. Mondok neki egy-két dolgot, ha már ott vagyok...";
			link.l1 = "Jól van, rendben. Vegye úgy, hogy megegyeztünk. Találkozunk Tortugán!";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "Ha minden a terv szerint megy, soha többé nem találkozunk. Legalábbis remélem. Viszontlátásra!";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "Argh! Ezt nem láttam elôre... A lelkemért jöttél, nem igaz, pajtás? Mindent úgy csináltam, ahogy megbeszéltük! Mi a fene?!";
			link.l1 = "Egy ítéletet hoztak rád, Robert. Az ítéletet nekem kellett végrehajtanom. Így hát teljesítem a megbízatásomat.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "Te démon! Ez lehetetlen! Nem tudhatott meg mindent ilyen gyorsan! És egyáltalán hogyan jött rá?!";
			link.l1 = "Úgy érti, Fox? Nem. Nem ô küldött. Az ezredes még mindig nem tudja, hogy te vágtad le a lányát. A régi haverod, Henry Thibaut az, aki holtan akar látni. Ô bérelt fel engem.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "Az az istenverte katamita! Meg kellett volna etetnem a rákokkal, amíg a 'Voltigeur'.... Mennyit ígért neked az a szemétláda?";
			link.l1 = "Nem mindennap tudja meg az ember, hogy milyen vérdíjat tûztek ki a fejére, igaz, Robert? Thibaut negyedmillióra taksálta magát, de meggyôztem, hogy többe kerül. Háromszázezer ezüstpezót érsz, barátom. Nem örülsz?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "Várj egy kicsit... Kössünk üzletet! Többet fizetek neked!";
			link.l1 = "Milyen pénzzel, Robert? Teljesen biztos vagyok benne, hogy hazudik. Nincs annyi pénzed, amennyit Henry ígért nekem. És amúgy sem ez a lényeg. Ha nem lenne egy tény, visszautasítottam volna az ajánlatát, hogy levadásszalak, és véget vetek a Thibaut-val való piszkos ügyeidnek.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "Melyik tény az?";
			link.l1 = "Megölted Catherine Foxot. Annak a szegény lánynak a bûne nem volt több, minthogy Fox ezredes lányának született. Gyûlölöm az olyan megvetendô gyávákat, mint maga, akik védtelen nôket ölnek meg! Nem kötök magával semmilyen alkut. Még csak meg sem fontolom. Ne vesztegesse az idejét.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "Bassza meg! Mi mást tehettem volna?! Nem hagyhattam életben, és nem rejtegethettem végtelenül a hajón! És ki vagy te... te gazember, te fattyú, te orgyilkos, hogy kioktatsz az erkölcsrôl! Nézz magadra! A te 'módszereidre'! Te sem vagy jobb nálam!";
			link.l1 = "Elég volt. Martene, húzd elô a pengédet! Itt az ideje, hogy befejezzük ezt.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "Találkozunk a pokolban!";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Mit keresel az otthonomban, uram?";
			link.l1 = TimeGreeting()+", ...Monsieur Thibaut. Egy olyan ember nevében vagyok itt, akit ismer, Robert Martene kapitány.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "Hm. És? - Igen, uram. És?";
			link.l1 = "Martene kapitány szeretné, ha most a Fisheye Beach-en lenne a társasága. De nem egyedül. Molly Jones-t is szívesen látná az ön társaságában. Érti, mire gondolok?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "Sajnos, uram, nem értem. Soha nem hallottam semmilyen Molly Jonesról, és Robertnek soha nem volt szüksége arra, hogy egy olyan... meghatalmazottat küldjön hozzám, akit még soha nem láttam. Csak hogy tudja, uram, én vagyok a második ember ezen a szigeten a nagybátyám, a kormányzó után, így...";
			link.l1 = "Az élet egy kiszámíthatatlan állat, Henry... Jelenleg ön a sziget második embere, és néhány órán belül már a kazamatákban lehet bilincsben... Mindezt egy olyan ember életéért, aki egy pezót sem adna önnek. Megtagadta a nagybátyja parancsát, ugye, Thibaut úr? Mi a fontosabb önnek: egy buja lány vagy az élete?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "Miért... Hazudik! A kalapodon keresztül beszélsz!";
			link.l1 = "Ön, mint bárki másnak, tudnia kell, hogy a nagybátyja milyen heves vérmérsékletû tud lenni. Levasseur még napnyugta elôtt rájön, hogy rejtegeti a lányt. Ne kérdezd, honnan tudta meg Robert, csak hallgass rám: halálra van rémülve, és kész azonnal horgonyt vetni. Még csak be sem mert menni a városba, és fizetett nekem egy tetemes összeget, hogy helyette átadjam neked ezt az üzenetet.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "A fenébe... Ez nem lehet!";
			link.l1 = "Önön múlik, uram. Martene nem fog két óránál tovább várni önre. Nagyra értékeli a fejét a saját vállán. Csak a barátsága jeléül van az, hogy még mindig a Tortuga partján tartózkodik, és nem bujkál valahol a hollandoknál.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "Caramba! Honnan tudta ezt meg a nagybátyám?";
			link.l1 = "Nyelvek, Henry. Csóválja a nyelvét. Még én is tudom, hogy te és Robert elkaptátok a szépséget, aki a társad által lefoglalt angol briggrôl jött. Elrejtettétek Levasseur elôl...tsk tsk. Tényleg kételkedsz abban, hogy én vagyok az egyetlen, akit tájékoztattak errôl a történetrôl?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "Úgy tûnik, igazat mond, uram. Mondja meg Martene-nek...";
			link.l1 = "Nem hiszem, hogy érted, Henry. Martene nem fog rád várni. Az egyetlen reményed, hogy kijuttasd innen azt a lányt, aki miatt neked és Robertnek is hurok van a nyakatokban. Szaladj oda, ahol rejtegeted, fogd meg a csinos kis kezét, és vidd át a Voltigeurhöz. Találjátok meg gyorsan, és hozzátok még gyorsabban. A nagybátyád egy szót sem fog hallani rólam.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "Jól van, rendben. Akkor ezt fogjuk tenni. Köszönöm a jótékonyságát, uram!";
			link.l1 = "Nem kell megköszönnie, uram. A munkámért fizetnek... Csak azt akarom, hogy szálljon ki a levesbôl, mielôtt megfô.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Mit keres itt, uram? Nem én hívtam ide.";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. Egy olyan embertôl jöttem, akit ismer. A neve Robert Martene kapitány.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "Hm. És? - Igen, uram. És?";
			link.l1 = "Martene kapitány szeretné, ha most a Fisheye Beach-en lenne a társasága. De nem egyedül. Molly Jones-t is szívesen látná az ön társaságában. Érti, mire gondolok?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "Sajnos, uram, nem ismerem.";
			link.l1 = "Ezt vártam tôled. Persze kétlem, hogy korábban már bemutatták volna önnek Fox ezredes lányát, persze ön ismeri Fox ezredest, a hírhedt tengeri rókák parancsnokát... Anglia ellenségeinek rémét a Karib-tengeren? Ön és Robert olyan darázsfészket kavarnak fel, hogy csoda, hogy még nem csíptek meg benneteket! A lány, Molly Jones, akit az angol briggrôl fogtatok el, és akit Levasseur elôl rejtegettetek. Fox ezredes lánya, Catherine Fox!";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "M-mi?";
			link.l1 = "Eléggé elsápadt, uram. Most jól figyelj rám, Henry, és jól figyelj: te és a pajtásod, Robert nyakig ülsz a szarban. Napokon belül Cromwell hadihajója megérkezik a Karib-tengerre. Vadászni fognak rád. A zászlóshajója önmagában is képes arra, hogy a maga dicsôített La Roche-ját és legénységét néhány óra alatt szilánkká és darált hússá változtassa. Mit gondol? Megérte az angol brigg megtámadása és Fox lányának fogságba ejtése?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "De ez még nem minden. A terveit nem csak én ismertem meg. Kedves nagybátyád, a kormányzó is rájön, hogy megszegted szigorú parancsait, és elrejtettél elôle egy lányt, akit a vén kéjenc minden bizonnyal magának akart volna elvenni. Mit gondolsz, Henry? Mit fog veled tenni a nagybátyád? Biztosan tudod, mint senki más, hogy milyen heves vérmérsékletû...";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "Minden hazugság!";
			link.l1 = "Tényleg? Kedves Henrym, megkérdezheted a barátodat, Martene-t. Ô küldött engem. Levasseur még napnyugta elôtt rájön, hogy rejtegeted a lányt. Ne kérdezd, honnan tudta meg Robert, csak hallgass rám: halálra van rémülve, és készen áll arra, hogy azonnal felhúzza a horgonyt és elhajózzon. Még csak be sem mert jönni a városba. Ezért kért meg, hogy adjam át neked ezt az üzenetet.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "Martene nem fog két óránál tovább várni rád. Nagyra értékeli a fejét a saját vállán. Csak a barátságotok jeléül van az, hogy még mindig a Tortuga partján tartózkodik, és nem bujkál valahol a hollandoknál. Az a szegény Robert azonban még csak nem is sejti, hogy ki is az a Molly Jones valójában. Tudjátok, ti ketten tényleg lenyûgöztök azzal a hihetetlen tudatlanságotokkal a nôi divat és megjelenés terén! Még egy nemesasszonyt sem tudnátok megkülönböztetni a szolgálójától!";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "Mit szeretne?";
			link.l1 = "Végre néhány bölcs szó az ifjú újonctól! Jól van, Thibaut: menj oda, ahol most éppen rejtegeted, fogd meg gyengéden a liliomfehér kezét, és sétálj vele gyorsan le a Halászpartra, ahol Martene Voltigeurje van. Mondd meg neki, hogy megváltoztak a terveid...";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "Martene-nek teljesítenie kell a nekem tett ígéretét, meg se próbálja a lányt a saját hajójára vinni. A lány a parton marad és vár rám. Mondd meg Robertnek, hogy ha nem teljesíti a kötelezettségeit, vagy elviszi Katalint, vagy ha egy hajszál is leesik a csinos kis fejérôl, egész hátralévô életemet azzal fogom tölteni, hogy megtaláljam ôt. És ha megtalálom, átadom ôt Fox ezredesnek... élve. De ami titeket illet... darabokban hozlak vissza. Igen, egyébként ez rád is vonatkozik, Thibaut.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "Hogy ki vagyok és milyen lehetôségeim vannak, arról kérdezd meg Robertet. Ô jól tudja. Ha mindketten azt teszitek, amit mondtam, akkor mindannyian nyerünk. Robert folytathatja a kalózüzletét, te pedig megôrizheted minden kiváltságodat, és megkapod az örökséget a kedves öreg nagybátyádtól, amikor az utoljára elpatkol. Ami engem illet... Én sem fogok vesztesként távozni. Minden világos?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "Inkább égek az örök pokol tüzén, minthogy a parancsodat teljesítsem... "+GetFullName(pchar)+"! Hogyhogy nem ismertelek fel már az elején? Te mészáros! Nem tervezed, hogy életben hagysz engem vagy Robertet! A 'módszereid' széles körben ismertek! Kizárt dolog, hogy Mollyt... vagy Catherine-t átadjam az olyan mocskoknak, mint te! Nem hagyod el élve Tortugát, te rohadék!";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "Állj meg, gyáva!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "Nos, végre! Kapitány "+GetFullName(pchar)+", nagyon örülök, hogy eljött. Jöjjön be, foglaljon helyet. Kér valamit inni? Van egy nagyon jövedelmezô üzleti ajánlatom a számodra, barátom...";
			link.l1 = "Hát, nem a legudvariasabb hangulatban van ma, Monsieur Thibaut... Ne üldögéljünk itt. Térjünk a lényegre.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "Az ajánlat egykori barátomra és társamra vonatkozik, akit Robert Martene néven ismersz, a gálya egykori kapitányára 'Voltigeur'....";
			link.l1 = "Szóval, te és Robert már nem vagytok társak? Érdekes fejlemény.";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "Kapitány, kérem, hallgassa meg az indítékaimat, amiért a segítségét kérem, és minden világos lesz. Mint azt maga is tudja, Martene megragadott egy angol brigget, és foglyul ejtett egy angol nôt, egy Molly Jones nevû szolgát, aki az oka annak, hogy ez az egész balhé kirobbant.";
			link.l1 = "Persze, tudom. Ha jól értem, ön teljesítette az ajánlásaimat, és elvezette a lányt Martene hajójára?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "Igen, megtettem. De minden nap megbántam. Tudatom veled, hogy Molly nagyon bájos és gyönyörû lány, még soha nem találkoztam hozzá hasonlóval. Be kell vallanom, beleszerettem. Neki is tetszettem, ô maga mondta! Nem hagyhattam, hogy a nagybátyám elvigye\nAmikor elkísértem a 'Voltigeur' hoz, reméltem, hogy a nagybácsi megnyugszik, amint rájön, hogy senki sem rejteget lányokat elôle, a vén kéjenc. Aztán Robert visszavinné a lányt Tortugára, hogy biztonságosan átköltöztethessem magamhoz. Mindenesetre ez volt az alku, amit Martene-vel kötöttem. De másképp alakult\nAmikor megtudtam, hogy a nagybátyámat megölték, nem volt értelme Mollyt elrejteni, így türelmesen vártam 'Voltigeur' megérkezését Mollyval a fedélzeten.";
			link.l1 = "Megérkezett?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "Igen. Sajnos Molly nem volt a hajón. Robert megrázkódott, mintha magával Luciferrel ütközött volna össze. Rövid ideig tartó expedíciója során valahogy rájött egy szörnyû részletre: a lány, Molly, egyáltalán nem Molly Jones volt, hanem Catherine Fox! Maga Fox ezredes lánya, a Sea Foxes, az elit angol tengerészgyalogos ezred parancsnoka! Tudják, hogy ez mit jelent!";
			link.l1 = "A fenébe a szememmel, mit szólsz hozzá! Kétségtelen tehát, hogy Robertnek van mitôl tartania. De hogyan is alakulhatott így?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "Amikor Catherine-t fogságba ejtették, szándékosan elrejtette a személyazonosságát, úgy téve, mintha Molly Jones lenne, egy szolgálólány, aki a beszállás során meghalt. Attól félt, hogy Martene rájönne, ki is ô valójában. És sikerült is becsapnia ôt. De az utolsó út során Robert valahogy rájött, hogy ki is ô valójában. Azt mondta, hogy talált néhány levelet, vagy papírt...";
			link.l1 = "És hol van most a lány, ha nem indult el 'Voltigeur'?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "Meghalt. Martene megrémülve a Fox fenyegetô büntetésétôl, amiért megtámadta az angol brigget, úgy döntött, hogy a vízbe rejti az egyetlen megmaradt bizonyítékot. Ô volt az utolsó szemtanúja a támadásának a 'Albatross'.";
			link.l1 = "Akkor akár az összes matrózt is meggyilkolhatta volna... Mint Fernand Luc. Különben egy nap berúgnak, és túlságosan nagyra nyitják a szájukat a kocsmában...";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "Úgy érzi, hogy az egész legénysége véresküt tett neki. Talán részben igaza van. De én ismerem Róka ezredest! Ô élete végéig ásni fog, hogy kiderítse, ki rabolta el a lányát!";
			link.l1 = "Ebben nem kételkedem. Különösen azután, hogy egy francia kalóz megölte a feleségét. Most meg a lányát is... Egyébként teljesen biztos benne, uram, hogy Catherine tényleg meghalt? Lehet, hogy Robert valahol elrejtette ön elôl.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "Biztos vagyok benne. Beszéltem egy tengerésszel a 'Voltigeur'. én hittem neki. A saját szemével látta, ahogy elvágták a lány torkát, majd ágyúgolyót kötöttek a lábához, és kidobták a fedélzetre.";
			link.l1 = "Isten az égben! Az a szegény nô... mit akarsz tôlem, Henry?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "Azóta a nap óta nem tudok aludni éjszaka. Folyton Mollyt látom a szemem elôtt... Inkább Catherine-t. Én vezettem a halálba, "+GetFullName(pchar)+"! Ezt nem tudom megbocsátani magamnak. Ráadásul nem táplálok illúziókat Fox-szal kapcsolatban. Az az ember nem önelégült, és szerintem nem is alszik. Elôbb-utóbb Martene nyomába ered, szóra bír valakit, és amikor rájön, ki ölte meg a lányát, elszabadul a pokol. Keményen megvisel mindenkit, aki így vagy úgy, de kapcsolatban állt az egész történettel.";
			link.l1 = "Engem is beleértve.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "Igen, én is. Ezért akarom, hogy találd meg Martene-t, mielôtt Fox találja meg. Találd meg azt a szemetet és öld meg. És elôbb szenvedjen, ha tudsz. Szegény Catherine miatt. Ha ez megtörtént, vágd le azt a kövér gyûrût, amit a kezén visel, az ujjával együtt, és hozd el nekem bizonyítékként\nIsmerem jól a görbe ujját és azt a gyûrût. Ha ezt megteszed, negyedmillió ezüstöt fizetek neked.";
			link.l1 = "Úgy látszik, nagy örökséget kaptál a drága öreg bácsikádtól, aki békében nyugszik, mi? Mondja, Henry, miért döntött úgy, hogy engem kér meg, hogy segítsek ebben az ügyben?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "Mert rólad is megtudtam néhány dolgot, "+GetFullName(pchar)+". Könnyû volt, te egy híres ember vagy. Azt viszont nem tudni, hogy valójában kinek dolgozik, de Poincy-nak, vagy a hollandoknak, vagy az angoloknak, vagy Jan Svenson bárónak... Egy dolog azonban világos: ön kényes, diszkrét feladatokat vállal és elvégzi ôket. Aztán szépen megfizetnek érte. És ami a legjobb, önnek nincs köze a spanyolokhoz\nvégtére is részt vett azokban az eseményekben, amelyek után örököltem a nagybátyám vagyonát. Ne is tagadja... Negyedmillió az jó pénz. Megmondom, hol találja meg Martene-t. Csak el kell fognod a hajóját, és fel kell szállnod rá.";
			link.l1 = "Még százezer, és én gondoskodom Martene-rôl.";
			link.l1.go = "tibo_34";
			link.l2 = "Sajnos, Monsieur Thibaut, a Martene-vel és Fox ezredessel kapcsolatos problémáját az én közremûködésem nélkül kell megoldania. Én a magam részérôl megígérem önnek, hogy nem küldök semmilyen hírt az ezredesnek a lánya sorsáról és azokról, akik bûnösök a halálában. Minden jót, uram.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "Uram, féljen Istentôl... Nekem nincsenek kincsesládákban elraktározott millióim, higgye el nekem! Megértem, hogy az ön szolgálatai pénzbe kerülnek, ezért ajánlottam önnek rögtön kétszázötvenezret... Rendben... Rendben, mit szólna, ha adnék hozzá még ötvenezer aranyat. Nem tudok többet ajánlani!";
			link.l1 = "Rendben. Megegyeztünk. Hol láttad utoljára Martene-t?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "Délre hajózott, a spanyol fôvárosba, Caracasba, és sikerült meghallgatást kérnie Don Diego Francisco de Kerres kormányzójától. Úgy tûnik, hogy valahogy megvesztegette ôt, mert Don Diego megadta Robertnek a spanyol korona védelmét. Eladta a 'Voltigeur' és most ô a kapitánya aInfanta nehéz gályának 'Infanta'. Nagyon jó megtakarításai lehettek, hiszen megengedhette magának, hogy megvesztegesse a kormányzót, és hogy egy ilyen nagy katonai hajót vásároljon és felszereljen\nSzóval legközelebb Caracasból Santo Domingóba hajózik az új hajóján egy spanyol hajóraj tagjaként. Ennyit sikerült megtudnia az ügynökömnek. Az egyetlen lehetôség Martene elkapására, ha utolérik a spanyol hajóraj\nHa elérik Santo Domingót, vége. Fogalmam sincs, hogy Robert hova megy legközelebb. El fog tûnni, mint nyúl a föld alá, és soha nem találjuk meg.";
			link.l1 = "Megvan. Elkapom ôket.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "És ne feledkezzünk meg a gyûrûs ujjáról! Ez a megállapodásunk kötelezô feltétele! Teljesen biztos akarok lenni abban, hogy Robert halott!";
			link.l1 = "Rendben, rendben. Ne vesztegessük az idôt, azonnal indulok!";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "Martene még mindig bûzlik a Karib-térségben a jelenlétével, kapitány?";
			link.l1 = "Már nincs sok ideje!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "Martene még mindig bûzlik a Karib-térségben, kapitány?";
			link.l1 = "Már nem. Többé nem félhetsz Fox ezredestôl, és Catherine-ért bosszút álltunk. Itt a bizonyíték.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "Igen... Ez kétségtelenül Martene ujja. Ön mindig lenyûgöz, kapitány "+GetFullName(pchar)+"! Igazán megérdemli a hírnevet, amit kap.";
			link.l1 = "Térjünk rá a fizetségre, rendben, Thibaut?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("500 dublont kapott.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Minden készen áll. Tessék, vegye el a jutalmát.";
			link.l1 = "Hálámat fejezem ki. Örülök, hogy sikerült idôben elkészítenie. Nos, Henry, remélem, hogy nem kerülsz több ilyen szerencsétlenségbe, és jobb barátokat választasz a jövôben. Minden jót!";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "Köszönöm a segítségét, kapitány! Minden barátomnak ajánlani foglak. Sok szerencsét!";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "Igen, monsieur "+GetFullName(pchar)+"? Van valami dolga velem?";
			link.l1 = "Nem, Thibaut úr. Csak úgy döntöttem, hogy beugrom egy pillanatra. Viszontlátásra!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "Ah, "+GetFullName(pchar)+"...Gyerünk, mi tart ilyen sokáig! Ki a fene tudja, hol van Robert Martene?! Ha Fox ezredesnek sikerül mindent kiderítenie, azt hiszem, nagy bajban leszek...";
			link.l1 = "Értem, értem. Elkéstem. Elnézését kérem, Monsieur Thibaut, de nagyon sürgôs dolgok miatt késlekedtem. Nem fogom az idejét vesztegetni. Viszontlátásra.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "Mit akarsz, "+GetFullName(pchar)+"? Nincs idôm csevegni. Nagyobb dolgom is van. Meg kell találnom Martene-t, mielôtt Fox találja meg...";
			link.l1 = "Igen, igen. Már úton vagyok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "Te vagy a kapitány "+GetFullName(pchar)+"?";
			link.l1 = "A megfelelô emberhez jöttél, pajtás. Csupa fül vagyok.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "Az adósod megkért, hogy közöljem veled, hogy a tett megtörtént, és a hal kevesebb, mint egy órán belül a hálóba úszik. Úgyhogy siess.";
			link.l1 = "Megértem. Köszönöm!";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "Mi a fenéért mászkálsz itt? Ki maga? Válaszolj!";
			link.l1 = "Ki a fasz vagy te, és miért kérdezel ilyen hülyeségeket?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "Micsoda?! Te taknyos pisis! Ki vagyok én? Én vagyok a sziget kormányzója, Francois Levasseur, Senior de Renet de Boidouflet de Lettre! És ezen a szigeten minden az én hatáskörömbe tartozik! Ez téged is beleértve, amíg az én területemen vagy, kölyök!";
			link.l1 = "Nocsak, nocsak... Maga a nagy, rossz farkas, mi? Kicsit eltévedtél, Levasseur, Senior de Renet de akármi is volt az. Lejárt az idôd. Francois Longvillier de Poincy fôkormányzó parancsára eltávolítottak a posztjáról és azonnali halálra ítélték! Én vagyok a bírája és a hóhéra egyben! Utolsó szavak?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "Gondolom, nem fogod feladni, és kegyelmet kérni tôlem nem fogsz, úgyhogy gyerünk, húzd meg a ravaszt!";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "Baszd meg! Ez de Poincy ügynöke! Húzzátok ki a kardotokat! Öljétek meg!";
			link.l1 = "Táncoljunk.";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "Mi a faszt keresel itt? Kik vagytok ti? Válaszolj, most!";
			link.l1 = "Mit szólsz ehhez? Erre nem számítottam... Maga Monsieur Levasseur, gondolom?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "Igen, én vagyok a sziget kormányzója, Francois Levasseur, Senior de Renet de Boidouflet de Lettre! És ezen a szigeten minden az én hatáskörömbe tartozik! Önt is beleértve, amíg az én területemen járkál, maga gazember! Válaszolj a kérdésekre! Ôrmester, zárja be az ajtót! Ez az ember semmi jóra készül!";
			link.l1 = "Maga hihetetlenül éleslátó, Monsieur Levasseur, Senior de Renet de whatever. Az én jelenlétem itt nem fog önnek örömet okozni. Francois Longvillier de Poincy fôkormányzó parancsára önt eltávolították a posztjáról és azonnali halálra ítélték! Én vagyok a bírája és a hóhéra egyben!";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "Gondolom, nem fogod feladni, és kegyelmet kérni tôlem nem használ, úgyhogy gyerünk, húzd ki a vassal! Te vagy a munkám, semmi személyes. Csak a koronát szolgálom, ha! Ôrmester, nem tanácsolom, hogy avatkozzon közbe, míg én a fôkormányzó parancsát hajtom végre!";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "Ne hallgasson rá, ôrmester! Ô egy spanyol ügynök! Megölni! Ôrség, segítség! Spanyolok vannak itt!";
			link.l1 = "Igazából sosem voltam Spanyolországban, csak Narbonne-ban.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "Jaj! Segítség! Katonák!";
			link.l1 = "Csönd legyen, te bolond! Ha nem sikítasz, nem teszek veled semmit!";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "Ne öljetek meg!";
			link.l1 = "Ne légy hülye! Tíz perce futott erre egy férfi. Egy jól öltözött nemes. Hol bujkál? És eszedbe ne jusson azt mondani, hogy nem láttad!";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "Monsieur Thibaut?";
			link.l1 = "Hát akkor ismeri ôt! Hová menekült? Válaszolni fog, vagy rázzam meg a fejét, hogy mûködjön?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "Ó, ne, kérem, ne bántson! Monsieur Thibaut elfutott, arra, a tenger felé. És leugrott az emelôrôl, egyenesen a vízbe. Valószínûleg meghalt, olyan magasan van...";
			link.l1 = "Nem hiszem. Ô nem az a típus, aki öngyilkos lenne. Be kellene mennie. Veszélyes itt kint lenni ma este...";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "Aú! Aúúú! Ne lôjön!";
			link.l1 = "Micsoda?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "Ki vagy te? Azért jöttél, hogy megölj, vagy... rosszabb?";
			link.l1 = "Semmi ilyesmi, madame. Visszaviszem önt, Catherine Fox, az apjához St. John's-ba. Ha ezután megkorbácsolja magát, mert nem engedelmeskedik a parancsának, akkor az én bûnöm megismétlôdik. Remélem azonban, hogy az ezredes örülni fog, hogy életben látja a lányát, annak ellenére, hogy annyi gondot okozott neki.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "Hála Istennek! Biztosan álmodom! Hát nem tudja, hogy ki vagyok? Ön francia és katolikus, és mégis úgy döntött, hogy idejön, hogy megmentsen engem a saját honfitársaim kezétôl? Az életét kockáztatta Fox ezredes lányáért?";
			link.l1 = "Eredetileg egészen más volt az oka annak, hogy itt vagyok Tortugán. De én sem hagyhattam egy gyönyörû hölgyet egy tolvaj- és rablóbanda kezében.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "Ön egy nemes úriember! Mi a neve, uram?";
			link.l1 = ""+GetFullName(pchar)+". Kapitány "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "Mondja, kapitány úr, tényleg elvisz engem az apámhoz Szent Jánosba?";
			link.l1 = "Igen, bár nem kedveli a franciákat. Nos, majd emlékeztetem, hogy vannak angolok is, akik gazemberek, beleértve az angol tiszteket is! Legalább egynek tanúja voltam... Richard Fleetwood volt a neve.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "Ha eljutunk Antiguára, mindent megteszek, hogy meggyôzzem apámat, hogy a franciák között is vannak igazi lovagok.";
			link.l1 = "Ezt nagyra értékelném... Jól van, remélem, hogy ôrangyalaim figyelték a nyomomat a város háztetôin, és már várják a visszatérésünket.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "Eddig nem hittem el, hogy betartod az ígéretedet! Annyi szörnyû és undorító dolog történt velem az utóbbi idôben... Köszönöm, kapitány, hogy visszaadta az emberekbe és a lovagiasságba vetett hitemet. Látogasd meg apámat, amikor csak tudod!\nÔ tiszteli az olyan embereket, mint te. És nem számít, hogy francia vagy. Mindent meg fogok tenni, hogy meggyôzzem apámat, hogy gondolja át a nemzetedhez való hozzáállását.";
			link.l1 = "Köszönöm, Catherine. Talán élni fogok az udvarias ajánlatával.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "Remélem, kapitány. Hatalmas köszönet még egyszer azért, amit értem tett. Soha nem fogom elfelejteni.";
			link.l1 = "Gyerünk, siess az apádhoz. Nagyon fog örülni, hogy látja magát. Talán már visszatért a tereprôl. Nos, mindenesetre itt az ideje, hogy elmenjek. Viszontlátásra!";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "Hát itt vagy, sapka! Betegre aggódtuk magunkat! Egy ilyen száguldás a csempézett háztetôkön, és egy ilyen ugrás a bélfájdító magasságból, az egy látvány volt, amit látni lehetett! Isten a tanúnk, már attól féltünk, hogy nem fogod megcsinálni... Isten hozott a fedélzeten, kapitány, a hosszú csónak készen áll!";
			link.l1 = "Nagyszerû. Catherine, kövessen!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "Jó napot, uram. Ön a kapitány "+GetFullName(pchar)+"?";
			link.l1 = "Igen, én vagyok. Mi folyik itt?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "Hú, alig értem utol... Egy Henry Thibaut nevû úriember nevében jöttem önhöz.";
			link.l1 = "Henry? És mit akar? Megosztani az örömét, hogy néhai nagybátyja halála után váratlanul ráhullott az öröksége?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "Monsieur Thibaut sürgôsen kérte, hogy minél hamarabb látogassa meg ôt a Tortugán lévô kastélyában. Jól fizetô munkát ajánl önnek. Azt is mondta, hogy említsek meg önnek egy nevet: Robert Martene. Ez biztos felkeltette az érdeklôdését.";
			link.l1 = "Valóban? És mi adta Henrynek ezt az ötletet?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "És ha ez nem gyôzte volna meg önöket, hogy látogassák meg, akkor kérte, hogy a következôket is tegyem hozzá: 'Robert Martene-nek meg kell halnia'..";
			link.l1 = "Rendben, rendben... Most már kezd érdekes lenni. Két esküdt barát épp most keveredett vitába... Ahogy mondtad, megpróbálom meglátogatni Henryt, ha lesz rá lehetôségem.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "Monsieur Thibaut megkérte, hogy ne késlekedjen a látogatásával. 'A halak tíz napon belül kiúsznak a hálóból' ezek voltak a pontos szavai...";
			link.l1 = "Ô és Robert ugyanúgy beszélnek. Rendben, meglátogatom Henry-t.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
