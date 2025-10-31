// Абрахам Норман
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
		case "First time":
			dialog.text = "Szükséged van valamire?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Mire van szükséged, haver? Menj az utadon, intézd a dolgaidat. Csak hagyj békén.","Hé, hé, haver. Sétálni mész? Hát, csak sétálj tovább, és hagyd békén Mr. Abraham-et. Ô is sétálni megy. Friss tengeri levegôt szív.","Helló, barátom. Akarsz beszélgetni? Csak egy baj van: nincs kedvem beszélgetni. Úgyhogy keress valaki mást, akit zavarhatsz. Menj, dôlj hátra a kocsmában. Igyál egy kis rumot...");
				link.l1 = "Figyelj, Abraham, nem futottál össze egy Miguel Dichoso nevû férfival Isla Tesoro-n mostanában? Eléggé ismert errefelé.";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("Mire van szükséged, haver? Menj az utadon, intézd a dolgaidat. Csak hagyj békén.","Hé, hé, haver. Sétálni mész? Hát, csak sétálj tovább, és hagyd békén Mr. Abrahamot. Ô is sétálni megy. Friss tengeri levegôt szív.","Helló, haver. Akarsz beszélgetni? Csak egy baj van: nincs kedvem beszélgetni. Úgyhogy menj és zavard valaki mást. Menj, dôlj hátra a kocsmában. Igyál egy kis rumot..."), LinkRandPhrase("Hé, Sailor. Mi van, keményfejû vagy, vagy mi? Azt hittem, elég világos voltam.","Haver, menj, pihenj egy kicsit. Úgy látom, egy kicsit nagyothalló vagy.","Hé haver, mi van, hülye vagy, vagy mi? Én már eléggé kibetûztem neked."), "Haver, ne idegesíts fel. Annyi szárazföldi barmot mészároltam már le, hogy egyel több vagy kevesebb nem igazán számít.", "Rendben, felbosszantottál. Most vagy vedd elô a rozsdás kardodat, vagy fuss, amilyen gyorsan csak tudsz. Én a második lehetôséget ajánlom...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Rendben, barátom. Nem foglak zavarni.", "Rendben, rendben. Értem...", "Hú, hát úgy nézel ki, mintha te lennél a tengerek mennydörgése! Rendben, én leléptem.", "Mi?!", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Mire van szükséged, haver? Menj az utadon, intézd a dolgaidat. Csak hagyj békén.","Hé, hé, haver. Sétálni mész? Hát, csak sétálj tovább, és hagyd békén Mr. Abraham-et. Ô is sétálni megy. Friss tengeri levegôt szív.","Helló, haver. Akarsz beszélgetni? Csak egy baj van: nincs kedvem beszélgetni. Úgyhogy menj és zavard valaki mást. Menj, dôlj hátra a kocsmában. Igyál egy kis rumot...");
				link.l1 = "Figyelj, Abraham, nem futottál össze egy Miguel Dichoso nevû férfival Isla Tesoro-n mostanában? Eléggé ismert errefelé.";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "Ne mozdulj! Én vagyok a sziget kormányzója. Mi az, nem hiszel nekem?!";
					link.l1 = "Persze, hogy akarok! Ki ne ismerné Isla Tesoro kormányzóját...";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "Ha, nevezd magad admirálisnak, ha már itt vagy, azt biztosan beveszem!";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "Vigyázz! Íme - Barbarigo admirális! Nem ismered fel a híres lovassági kardomat?";
					link.l1 = "Elnézést kérek, admirális úr! Mostantól jobban fogok figyelni.";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "A lovassági kardja széles körben ismert. Kár, hogy egy bolond kezében van.";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "Amint látja, számûzetésben vagyok itt. Várom a Monk tábornok további értesítését. Kérem, hogy ne terjesszétek elrejtett királyi személyazonosságomat. Cromwell hírszerzésének hosszú füle van.";
					link.l1 = "De természetesen, felséged. Senki sem fogja megtudni, hogy II. Károly Nyugat-Indiában bujkál.";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "Nos, akkor én vagyok Innocent X pápa.";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "Mi történt veled, Blaze? Már két napja kereslek. Teljesen elfelejtetted az apádat, Nicolas-t!";
					link.l1 = "Nincs idôm rád, apám! El vagyok havazva.";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "Téved, uram. A nevem "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "Pszt... Davy Jones vagyok. Mondd, félsz a haláltól?";
					link.l1 = "Persze, hogy félek, Mr. Jones. Különösen másnaposság után.";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "Egy halál tragédia, ezer halál csak statisztika.";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "Sietek, hogy befejezzem az új darabomat. Segítened kell befejezni a mondatot 'Lenni vagy nem lenni'?!";
					link.l1 = "Ez a kérdés! Elviseljük a sértést és továbblépünk...";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "Egy ital, az biztos. De nem lepôdnék meg, ha egy bordélyházban kapnék el valami betegséget!";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "Mi a fenérôl beszélsz? 'Tesoro'?! Akár a Bermudáknak is hívhatnád! Ezt a szigetet Norman szigetnek hívják utánam és ezt ne felejtsd el! Meg kell tanítanom téged földrajzra...";
			link.l1 = "Huh! Hogy érted ezt?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "Igazad van, Sailor. Tényleg Barbarigo admirális vagyok, de ez szigorúan köztünk marad. Készüljetek a menetelésre. Hamarosan indulunk. Ez jól fog jönni neked.";
			link.l1 = "Nagyon hálás vagyok!";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("Kaptál egy háromcsövû puskát");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("Kaptál egy gyufaszáras muskétát.");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("Kaptál egy papírpatront");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "Majd meglátjuk, hogy ki a bolond most azonnal. Ôrség!";
			link.l1 = "Ez most komoly?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "Mit mondtam neked! Tessék, igyál az egészségemre.";
			link.l1 = "Fenékig, admirális!";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("Kaptál egy aranydublont");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("Kaptál egy láda dublont.");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "Kértem, hogy ne terjessze a nevemet! Most pedig el kell tüntetnem magát, mint veszélyes tanút...";
			link.l1 = "Ó, erre vártam!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "Bocsásson meg, kegyelmes uram! Nem ismertem meg ebben a ruhában. Kérem, fogadja el ezt a szerény ajándékot egy igaz katolikustól.";
			link.l1 = "Az ôrület dudorászik...";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("Megkaptad a Csodamûvész amulettet.");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("Megkaptad a Cinkos talizmánját.");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("Kaptál egy viaszgyertyát");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "Mindenki rám támad! Elkaptam egy kémet, aki pont úgy néz ki, mint a fiam! Biztos vagyok benne, hogy Tamás küldte, hogy verje ki a második szememet!";
			link.l1 = "Húzz el, te idióta!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "Fáradt vagy, és nem nézel ki túl jól, fiacskám. Menj, és kezeltesd magad.";
			link.l1 = "Köszönjük!";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("Kaptál egy bájitalt");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("Megkaptad a Skorpió amulettet.");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("Kaptál gyógyító esszenciát")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "Ne félj, haver. Látod, a halál egyáltalán nem ijesztô...";
			link.l1 = "Úgy tûnik, nem viccelsz!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "Úgy tûnik, nem félsz. Tudtam. Ez bátorság!";
			link.l1 = "Vicces egy öregember vagy...";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("Kaptál egy tûznyelô mellényt.");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("Kaptál egy parádés mellvértet.");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("Kaptál egy kis dohányt");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "Szar költô vagy, tengerész. Lehet, hogy a pengéd fürgébb, mint a nyelved?";
			link.l1 = "Caramba! Az a lovassági kardod egyáltalán nem csalóka!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "A fenébe! Elég simán mentek a dolgok neked! Hogy is van ez a képzelôerôddel!";
			link.l1 = "Gyere vissza.";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("Kaptál egy üveg rumot.");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("Kaptál egy öntöttvas torkot.");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("Kaptál egy üveglombikot");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "Aha, felismerlek! Ha-ha!";
			link.l1 = "Ismétlem...";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "Rendben, haver, megbeszéltük a dolgot. Most már menjetek.";
			link.l1 = "Ahogy mondod...";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "Dichoso? Mi szükséged van rá, mi?";
			link.l1 = "Nos, szükségem van rá. Csak szükségem van rá. Szóval, láttad ôt?";
			link.l1.go = "tieyasal_1";
			link.l2 = "Hogy érted, hogy mire van rá szükségem? Miguel a régi cimborám, mondhatni egy barátom. Neki kellene...";
			link.l2.go = "tieyasal_2";
			link.l3 = "Azt akarom, hogy vontasson nekem egy új hajót, ahogy egyszer már megtette Shark Dodson-nak.";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "Miguel Dichoso megölt egy embert. Ezért keresem ôt.";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "Csak ô kell neked... Csak ô kell neked! Csak Miguel Dichoso kell neked! Nem, nem láttam ôt. Már régóta nem láttam. Semmiben nem tudok segíteni, Sailor.";
			link.l1 = "Hm... Rendben, viszlát.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "Egy barát, azt mondod... Úgy tûnik, egy egész rakás barátja van. Egy barátjával kevesebb lesz...";
			link.l1 = "Hé, öregem. Mi bajod van?";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "Igen, Dichoso egy mestere az ilyen mesterségeknek, akárhogy is nézzük. De nem tudom, hol van. Megfordult, de aztán megint elment. Szóval menj át Alexushoz, Sailor. Ô majd összefûrészel neked egy csodálatos kádat.";
			link.l1 = "Hm... Kösz a tippet, haver.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "Szóval kit tett el láb alól Dichoso, hogy te is a nyomába eredtél, haver?";
			link.l1 = "Blaze Sharp";
			link.l1.go = "tieyasal_5_1";
			link.l2 = "Nicolas Sharp";
			link.l2.go = "tieyasal_5";
			link.l3 = "Alonso de Maldonado";
			link.l3.go = "tieyasal_5";
			link.l4 = "A Pápát";
			link.l4.go = "tieyasal_5_bud_joke";
		break;

		case "tieyasal_5_1":
			dialog.text = "Pszt... (körbenéz) Szóval te is azt hiszed, hogy Dichoso ölte meg Blaze Sharpot?";
			link.l1 = "Igen. Nem csak gyanúm van, hanem bizonyítékom is. Bejegyzések a hajónaplóban...";
			link.l1.go = "tieyasal_6"
		break;

		case "tieyasal_5_bud_joke":
			dialog.text = "Szóval viccelődni van kedved? Semmi tisztelet! Na gyere csak közelebb...";
			link.l1 = "Na azt már nem.";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_5":
			dialog.text = "Ah... Nos. Ô ölte meg, és ez minden. Tudod, hány gyilkos szaladgál itt? Minden második ember! Nem, Sailor. Régóta nem láttam Dichosót. Nem tudok segíteni neked semmiben.";
			link.l1 = "Kár...";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "Nyugodj meg, pajtás. Mi a neved, mi? Valahogy kiment a fejembôl...";
			link.l1 = "Kapitány "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Figyelj, "+pchar.name+". Dichoso megölte szegény Blaze-t. A saját szememmel láttam, igen-igen. De nem hisznek nekem. Látod, azt hiszik, hogy ôrült vagyok. A sajátjuk, de ôrült. Pedig én voltam a legjobb fedélzeti tiszt magának Nicolas Sharpnak a legénységében! Szép idôk! De végül elvesztettem a karmaimat, a patámat és a lencsémet, és szobafogságba kerültem.\nMi? Á, igen! Mindenki azt hitte, hogy Shark a hibás, de nem ô volt a hibás. Nem, nem, nem. Volt ott egy cápafog, Dodson talizmánja, de Dichoso volt az, aki oda tette.\nÔ biztos ellopta Cápától, amikor együtt hajózgattak a Fortune nevû fregatton. Aznap nem aludtam jól, és kimentem sétálni. Láttam, hogy Dichoso belopózott Sharp rezidenciájába, hallottam, hogy valaki sikoltozik, majd nyögdécsel. Nem sokkal késôbb Dichoso elhagyta a rezidenciát, és a keze véres volt.\nNem hittek nekem, nem-nem. Mert aznap nem volt Dichoso a szigeten, de Shark igen. És megtalálták a fogát. De én láttam Dichosót, ebben biztos vagyok. Senki sem tudta, hogy aznap ott volt. 'A Szerencsés' egy nagyon ravasz és félelmetes ember...";
			link.l1 = "Nem te vagy az elsô, aki Dichosót 'a szerencsésnek'. hívja. Miért? Ez a beceneve?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Nem tudsz spanyolul, srác? 'Dichoso' jelent 'lucky' a pápista nyelven. Szerencsés Miguel, Miguel a szerencsés. Ez a neve.";
			link.l1 = "Miguel a szerencsés? Hm. Errôl eszembe jut valami. Hm. Ez a mondat olyan ismerôsen hangzik...";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Nos, bár a vezetékneve Dichoso, mégsem hiszem, hogy spanyol. Nem, nem, nem... Nem spanyol. Bár úgy néz ki, mint egy spanyol.";
			link.l1 = "Akkor mi lehet? Angol, francia?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Nem errôl beszélek, Sailor... Ó, bocsásson meg, kapitány. Igen, Dichoso mesésen fecseg franciául, nem rosszabbul, mint maga. És angolul is. De az ereiben indián vér folyik. Sok ilyen embert láttam már életemben. Nem látszik tisztán, de ô egy félvér. Garantálom neked.";
			link.l1 = "Beszéli az indiánt?";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "Ó, a pokol tudja. Talán tényleg az. Bár, várj csak. De igen! Állandóan furcsa mondatokat mondott valami bizarr nyelven, és ijesztô bölcs arcot vágott, és fújta az arcát, miközben kiejtette ôket. Például valami olyasmit mondott, hogy: cogito ergo sum! Aztán forgatta a szemét, és várta a matrózok reakcióját. Vagy így kiáltott fel: aut Caesar, aut nihil! Egy csomó más dolgot is elpufogtatott. Nem emlékszem mindenre, amit mondott.";
			link.l1 = "Ez nem indiai nyelv. Ez latin. Latin... Latin?! Szent szar!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Miért vagy ilyen ideges, srác? Miért kiabálsz? Megharapott egy kígyó, vagy mi? Hova tûnt?";
			link.l1 = "Miért nem láttam az elején! Minden a szemembe nézett! Latin! Miguel... Miguel a szerencsés!!!";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "Hé, haver. Abbahagynád már a kiabálást? Az emberek bámulnak minket. Mi a bajod, matróz... bocsánat, kapitány?";
			link.l1 = "Tudom, ki Miguel Dichoso valójában. Nem spanyol. Ô francia! Ó, annyira vak voltam!";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "Nah-uh, buta. Nem francia. Ô egy félig-meddig. A fehér apja egy kis indiánlánnyal kavargatott, valamelyik arawakkal vagy miskitóval a Karib-tengerrôl, vagy akár egy itzával, és így jött Szent Miguel Dichoso erre a Földre. Te ezt nem látod, de én igen. A szemébe van írva...";
			link.l1 = "Hagyjuk egy pillanatra félre a származásának kérdését. Hol van, Ábrahám?! Itt volt?!";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "Sh-sh... Igen, itt volt. De elment. Már nincs Isla Tesoro-n.";
			link.l1 = "Miért jött ide? Milyen hajója van?";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "A hajója egy gálya. Egy nagy harci gálya. Amiért idejött... Hát, körbeszaglászott és kérdezôsködött. De én hallottam a beszélgetéseit, igen, igen! Valami Charles de Maure-t keresett. Igen, ez az. Charles de Maure. Várj, ez te vagy, Charles de Maure! Téged keresett, haver.";
			link.l1 = "Tudod, hogy miért?";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "Hát biztosan nem azért, hogy meglátogassa a kocsmát és elkortyoljon veled egy kis rumot. Azért, hogy elfogjon téged. Igen, igen! Elfogni téged! Nagy szarban vagy, kapitány!";
			link.l1 = "Nem kételkedem benne...";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "És téged? Miért keresed ôt? Ó, értem, értem: hogy megölje ôt! Öljétek meg, öljétek meg a rohadékot! Bosszuljátok meg Blaze Sharpot! Blaze remek fickó volt. Emlékszem rá, már gyerekként is olyan volt, mint Nicholas.";
			link.l1 = "Hová tûnt Dichoso?";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "Úton volt Blueweldbe. Azt mondta, hogy Charles de Maure-t az Erdei Ördög szárnyai alatt kell keresni. De itt hagyta az embereit... Várj, azt hiszem, már észrevették!";
			link.l1 = "Ki vett észre engem?";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "Dichoso emberei. Megparancsolta, hogy ôrizzék magát. Ó, tudom, tudom! Legyen résen, kapitány: Isla Tesoro zátonyait hajók veszik körül, és ott várják a fejét. A kapitány ravasz, mint a róka. Ne hagyd magad becsapni.";
			link.l1 = "Megpróbálom...";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "És még valami: tessék, fogd a lovassági kardomat. Vedd el, vedd el. Szükséged lesz rá. Ez maga Barbarigo kapitány kardja. Kitûnô penge. A legjobb a szigetvilágban. Ne szégyenlôsködj, vedd el. Blaze Sharp megbosszulja magát!";
			link.l1 = "Köszönöm, Abraham.";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("Barbarigo kardját kaptad.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Most menj. Menj, figyelnek téged. Legyen úgy, mintha okos lennél. Vagy hülyének. Nem számít. Csak légy óvatos!";
			link.l1 = "Kösz, haver. Nem is tudod, mennyit segítettél nekem. Sok szerencsét!";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
