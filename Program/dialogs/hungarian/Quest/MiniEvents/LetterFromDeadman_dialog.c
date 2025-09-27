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
			dialog.text = "Mit akarsz?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		case "Sailor_1":
			dialog.text = "Mit akarsz, "+GetSexPhrase("barát","lány")+" ? Ha rumot kínálsz, nem fogok nemet mondani. Annyit köröztem már ebben az istenverte városban, hogy a lábaim mindjárt csomót kötnek magukra. És neked mi a neved?";
			link.l1 = "Kapitány "+GetFullName(pchar)+". Te nem az „Eagle”-ről vagy, ugye?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "És én - "+GetFullName(npchar)+". Igen, az 'Eagle'-ről vagyok. Tetszik a hajónk, kapitány?";
			}
			else
			{
				dialog.text = "Kapitány? Nos, nos... Khm... Antonio Velenta vagyok. És igen, az 'Eagle'-ről jöttem. Felkeltette a hajónk az érdeklődését, Kapitány?";
			}
			link.l1 = "Egy hajó az hajó. Jobban tennéd, ha felszállnál, ahelyett hogy a városban kószálsz—a kapitányod már most dühöng. Mindenáron ki akar futni, mielőtt apály lesz, és valami azt súgja, fiú, nem fog rád várni.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "A fenébe is... Tudom, tudom... De még van itt néhány befejezetlen ügyem ebben a városban. Nincs kedved keresni pár doblont, mi, Kapitány?";
			link.l1 = "A dublon sosem jön rosszkor. De megszerezni egy dolog, bajba keveredni megint más. Mi a meló? Mondd csak.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "Látod, miközben kipakoltam a rakteret, rábukkantam egy levélre. Nem tűnt úgy, mintha szándékosan rejtették volna el, csak ott hevert néhány régi hordó között. A mi fluytunkat már többször is átkutatták, szóval ki tudja, honnan került oda.";
			link.l1 = "Szóval megtaláltad a levelet, de aztán mi van?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "Egy bizonyos Marisa Calderának szól Porto Bellóból. Viaszpecséttel lezárva... érzem a zsigereimben – ez nem valami jelentéktelen ügy. Talán egy kapitánytól, talán egy kereskedőtől... de biztosan nem egy olyan egyszerű matróztól, mint én! Csak hát, nem lesz időm megkeresni a címzettet – a mi kapitányunk nem igazán szereti a tréfákat.  Nem akarod megvenni tőlem? Odaadom ezer pesóért. Te kapitány vagy, neked nem lesz nehéz megtalálni ezt a señoritat. És ki tudja, talán arannyal jutalmaz, vagy valamivel mással... érted, mire gondolok?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Nos, talán én megtalálom a te Marisádat.  Akárhogy is, nincs mit veszítenem. Ezer peso kivételével. Add ide a levelet.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				notification("Nincs elég pénz (1000)", "Money");
			}
			link.l2 = "Sajnálom, barátom, de mást kell keresned. Fontosabb dolgaim vannak annál, mint hogy leveleket kézbesítsek.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Tessék. Vigyázz magadra, "+GetSexPhrase("cimbora","lány")+", mennem kellene – nem szeretném, ha a holmijaim az 'Eagle'-lel hajóznának el.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "Ki vagy te? Mit akarsz?";
			link.l1 = "A nevem Kapitány "+GetFullName(pchar)+". Marisa Calderát keresem.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "Nem ismerek semmilyen Marisát. Rossz ajtón kopogtatsz. Tűnj el innen, mielőtt hívom az őröket – pillanatok alatt kiraknak.";
			link.l1 = "Apa "+sld.name+" azt mondta, hogy a barátja vagy. Van nála egy levél, amit neki címeztek. Az állapota alapján már nagyon régi lehet. Szeretném személyesen átadni.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ó, apám... Túl kedves mindenkivel, de ritkán téved az emberekben. Nálam hagyhatod a levelet. Gondoskodom róla, hogy eljusson hozzá.";
			link.l1 = "Bocsásson meg, señorita, de inkább személyesen adnám át. Talán lesznek kérdései arról, hogyan jutottam hozzá, és miért tartott ilyen sokáig, hogy megérkezzen.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "És azt várod, hogy csak úgy elhiggyem a jó szándékaidat? Láttam már elég gazfickót ártatlan arccal. Hagyd itt a levelet, vagy menj tovább.";
			link.l1 = "Szavamat adom kapitányként, hogy sem neked, sem Marisának nem ártok. Sőt, akár a strázsát vagy bárkit, aki ért a fegyverekhez, is meghívhatsz a találkozónkra. Nincs más szándékom, mint hogy ezt a levelet személyesen adjam át Marisának.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "Rendben. Gyere vissza holnap tizenegy óra után éjjel. Nem ígérhetem, hogy beleegyezik a találkozóba, de mindent átadok, amit mondtál.";
			link.l1 = "Ott leszek. Hamarosan találkozunk.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Szia, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". Engem kerestél, hát itt vagyok. Dolores azt mondta, hogy van egy leveled számomra?";
			link.l1 = "Jó napot, Caldera asszony. Úgy van, itt is van. Sajnos úgy tűnik, elég sokáig tartott, mire eljutott Önhöz.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Átadva: Levél Marisa Calderának", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Dolores... Ez az ő kézírása... Ramiro kézírása!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "De hogy lehetséges ez? Két év telt el!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Kapitány... Hogyan jutott hozzá? Hol találta meg? Mindent tudnom kell! Kérem, mondjon el mindent, amit csak tud.";
			link.l1 = "Ez a levél egy matróztól jutott el hozzám. A hajója sötét rakterében találta, és maga akarta átadni neked, de sietve vissza kellett térnie a fedélzetre. Ezért megkért, hogy keresselek meg, és hát itt vagyok. Ennél többet nem tudok...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Köszönöm, "+GetAddress_Form(NPChar)+"! Nagyon köszönöm! Kérlek, ne menj el. Szeretnék még beszélgetni veled, de előbb... el kell olvasnom ezt a levelet.";
			link.l1 = "Természetesen, Lady Caldera. Itt leszek.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Húsz perc telt el, Marisa elolvasta a levelet...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores... Ezt a levelet az utolsó útja előtt írta. El akarta mondani, hogy lehetősége nyílt egy nagyobb ébenfa-szállítmányt venni egy belize-i kereskedőtől, de nem volt elég pénze. Akkor vette fel ezt a kölcsönt... Kétszáz doblón... Emiatt most nem találok nyugalmat.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "Ez mindent megmagyaráz... De sajnos, ettől nem lesz könnyebb a terhed. Légy erős, Marisa. A sötétség nem tart örökké, és ez az adósság sem fog örökké kísérteni.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "Nem, Dolores, nem lesz! Ramiro azt írta, hogy van egy rejtekhelye... a mi helyünkön. Ha még érintetlen, talán ki tudom fizetni az adósságot, és végre megszabadulhatok ettől a rémálomtól.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "Az Úr kegyelmet adott neked! Meghallgatta imáinkat...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Kapitány, ismételten köszönöm, hogy elhozta nekem ezt a levelet. Nagyon sokat jelent nekem... De még egy szívességet kell kérnem Öntől. Tudja, a férjem, Ramiro volt számomra minden, sosem kerestem más férfi védelmét. Most, hogy ő nincs többé, senkim sem maradt, nincs saját családom\nEl kell jutnom a rejtekhelyére – a városon kívül van. De túlságosan félek egyedül menni, a néhai férjem hitelezői üldöznek. Ön becsületesen viselkedett, amikor felkeresett, hogy átadja a levelet... Kérem, segítsen nekem még egyszer.";
			link.l1 = "Természetesen, Marisa, elkísérlek. Mikor szeretnél indulni?";
			link.l1.go = "Marisa_16";
			link.l2 = "Sajnálom, señora, de a városukban töltött időm már így is túl hosszúra nyúlt. A vidéki séták nem szerepelnek a terveim között.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "Értem... Már így is többet tett értem, mint remélhettem volna. Köszönöm, Kapitány, és isten önnel.";
			link.l1 = "Viszlát.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Köszönöm, kapitány. Holnap hajnalban, hét óráig jöjjön el. Készen leszek.";
			link.l1 = "Akkor hát, amíg újra nem találkozunk, señora.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Caballero, ott vagy... Igazán becsületes ember vagy! Induljunk hát. Utunk a dzsungelen át vezet a barlanghoz, nem messze a Mosquitos-öböltől.";
				}
				else
				{
					dialog.text = "Kapitány, hát itt vagy... Tudtam, hogy eljössz. Tudod, ez az első alkalom, hogy olyan nővel találkozom, aki saját hajót vezet. És már most látom, hogy minden tekintetben felérsz bármely férfihoz—akár becsületben, akár nemességben!";
				}
				link.l1 = "Kiváló, señora. Akkor ne vesztegessük az időt. Maradjon közel, és egy pillanatra se távolodjon el.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Köszönöm, Marisa. Az apám kapitány volt és becsületes ember – gyerekkoromtól kezdve belém nevelte ugyanazokat az elveket.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Gyere hajnalban, hét órára. Készen leszek.";
				link.l1 = "Akkor találkozunk, señora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "Ő is? Ugyanaz lett a sorsa, mint Ramirómnak?";
			link.l1 = "Biztosan szívesebben halt volna meg karddal a kezében vagy egy vihar közepén. De a sors másként akarta – egy betegség vitte el, amiről soha senkinek nem beszélt.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "Sajnálom a veszteségedet, "+pchar.name+" Az Úr a legjobbakat veszi el közülünk... És bár nem mindig értjük, miért, ez az Ő akarata. Mindössze annyit tehetünk, hogy imádkozunk halhatatlan lelkük nyugalmáért.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Induljunk el. Az utunk a dzsungelen át vezet a barlanghoz, nem messze a Mosquitos-öböltől.";
			link.l1 = "Természetesen. Maradj közel, és egy pillanatra se kóborolj el.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "Itt vagyunk... Ramiróval egyszer itt húzódtunk meg az eső elől, amikor még fiatalok voltunk, mielőtt a férjem lett volna. Akkor mondta, hogy bármi áron elnyeri a szívemet.";
			link.l1 = "Sajnálom, hogy egyedül kellett idejönnie, a férje nélkül, señora. Az ilyen helyek sok emléket őriznek. Nézzünk körül – talán az emlékeken kívül mást is találunk, amit Ramiro a legnehezebb időkre tartogatott.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Señor "+pchar.lastname+"",""+pchar.name+"")+"... Találtál valamit? Ez az, amit Ramiro hátrahagyott? Nem is tudom, mitől félek jobban – attól, hogy üres, vagy attól, hogy nem lesz elég a tartozás kiegyenlítésére...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(mutatja) Tessék, ez minden, ami a ládában volt. Remélem, elég lesz, hogy jobb irányba fordítsa a sorsodat.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Még mindig átnézem a ládát.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "Ah, Kapitány! Természetesen! Ez bőven elég lesz! De nem hagyhatom, hogy a segítséged jutalom nélkül maradjon. Fogadj el száz dublont. Ha nem lennél, sosem tudtam volna erről a rejtekről, és még mindig Ramiro hitelezőjének emberei elől bujkálnék...";
			link.l1 = "Nagyon nagylelkű, señora, köszönöm. A mi szakmánkban az arany sosem vész kárba.";
			link.l1.go = "Marisa_34";
			link.l2 = "Nem, señora. Önnek sokkal nagyobb szüksége van erre a pénzre, mint nekem. Ami igazán számít, az az, hogy most már maga maga mögött hagyhatja a gondjait, és békében élhet. Nekem ez bőven elég.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Átadva: Amulett 'Cimaruta'", "None");
			notification("Átadva: Amulett 'Halász'", "None");
			notification("Átadva: Kovás muskéta", "None");
			notification("Átadva: Gyémánt (10)", "None");
			notification("Átadva: Rubin (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "Nos, hát akkor, "+GetSexPhrase("úr",""+pchar.name+"")+", indulnunk kellene. Ha észrevettek a városban, lehet, hogy követnek minket. Jobb, ha nem időzünk itt.";
			link.l1 = "Igazad van, Marisa. Menjünk.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Kapitány, kérem... a férjem ezt a fegyvert azért tartotta, hogy megvédje a családunkat, és biztos vagyok benne—az Ön kezében igaz ügyet fog szolgálni. Ramiro örülne, ha tudná, hogy ahhoz került, aki megmentett engem, amikor már minden remény elveszett.";
			link.l1 = "Rendben, Marisa, köszönöm. Kedves és becsületes asszony vagy, és őszintén sajnálom, hogy a sors ilyen kegyetlen volt hozzád.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "Előfordul, hogy az Úr nehéz napokat, vagy akár éveket is ránk mér, hogy próbára tegye a hitünket, de sosem hagyja el azokat, akik az igaz úton járnak. Téged is azért küldött hozzám, hogy segíts, és most már remélem, a legnagyobb bajom hamarosan mögöttem lesz.\nDe most ideje visszamennünk. Elég sokáig maradtunk itt, és ez veszélyes lehet, hiszen még mindig keresnek engem.";
			link.l1 = "Természetesen, señora, induljunk.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ha! Hát itt van az elveszettünk! Tényleg azt hitted, hogy elbújhatsz itt, ebben a lyukban, mint egy egér, és én nem találok rád? Már többször felforgattam az egész várost, és te végig itt voltál"+GetSexPhrase(", és ráadásul randiztál valami kis kölyökkel. Hol van a pénzem, te kis ringyó? Jobb lesz, ha most azonnal ideadod, különben ez a barlang lesz a sírod.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "Te...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "Szóval te vagy az, aki abból él, hogy nőktől hajt be adósságokat? Ahogy elnézem a választott mesterségedet, az eszed sosem volt az erősséged. Csoda, hogy egyáltalán idetaláltál magadtól, és nem csak követtél valakit, aki nálad okosabb... mondjuk a saját csizmádat, például.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Fogd be a szád, hős. A te időd is eljön, de előbb vele végzek. Ötszázhuszonöt dublont tartozik – ennyi az adóssága kamatostul. Vagy mindent kifizet, vagy örökre itt marad – a férgek táplálékának. De ha már ennyire igazságos vagy, kifizetheted helyette, és én eltűnök.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Azt hiszed, csak úgy besétálhatsz, megsérthetsz egy hölgyet, rám se hederítesz, és sértetlenül kisétálsz innen, ráadásul a doblonokkal? Úgy látom, nem vagy valami okos. De nem fogok verekedést kezdeni egy nő előtt. Szóval itt az ajánlatom: bocsánatot kérsz Caldera asszonytól, elviszed a doblonjaidat, és szépen eltakarodsz innen. Vagy végül tényleg megtanítalak egy kis jó modorra.";
					link.l1.go = "Naemnik_5";
					notification("Ellenőrzés sikeres (525)", "Dubloon");
				}
				else
				{
					notification("Nincs elég arany (525)", "Dubloon");
				}
			}
			else
			{
				dialog.text = "Fogd be a szád, és várj a sorodra. Veled később foglalkozom, miután elintéztem ezt a nyomorultat. Ötszázhuszonöt dublonnal tartozik – ennyi az adóssága kamatostul. Ha már ennyire igazságos vagy, kifizetheted helyette, és akkor én eltűnök.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Nos, hajlandó vagyok elnézni a nyers modorodat, sőt, még azt is, ahogy velem beszéltél. De ha tényleg szeretnéd megkapni a dublonjaidat és épségben távozni innen, bocsánatot kell kérned Lady Calderától. Különben majd meglátjuk, ki bánik jobban a fegyverrel. És hidd el, én nem csak dísznek hordom a sajátomat.";
					link.l1.go = "Naemnik_5";
					notification("Ellenőrzés sikeres (525)", "Dubloon");
				}
				else
				{
					notification("Nincs elég arany (525)", "Dubloon");
				}
			}
			link.l2 = "Nyilvánvaló, hogy nem vagy túl eszes, ha azt hitted, hogy majd szépen kivárom a sorom. És még kevésbé, ha azt gondoltad, hogy szemet hunyok mindazok felett a bajok felett, amiket te és a fajtád Lady Calderára zúdítottatok.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "Rendben, legyen úgy, ahogy akarod. Ha meg tudjuk szerezni a pénzt fölösleges kockázat nélkül, nem látom értelmét, hogy veszélybe sodorjam magam. Add ide a doblonokat – és tűnj el.";
			link.l1 = "Először is, kérj bocsánatot a hölgytől.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Bocsásson meg, señora. Az ördög vitt rá.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Boldog"+GetSexPhrase("","")+" Add ide a pénzt, aztán megyek is tovább. Rengeteg dolgom van, nincs időm itt ácsorogni és csevegni veled.";
			link.l1 = "Vedd a dublonjaidat, és tűnj el innen.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Kapitány, tényleg nem értem... Mit jelent ez?";
			link.l1 = "Ez azt jelenti, hogy most már semmivel sem tartozol. Szabad vagy.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "De... most nincs meg nálam a teljes összeg, hogy visszafizessem. Ha tudnál egy kicsit várni...";
			link.l1 = "Nem érted, Marisa. Nem tartozol nekem semmivel. Már senkinek sem tartozol semmivel. És a pénz, amit találtál, nagyon jól fog jönni neked. Térj vissza a régi életedhez – a templom vár rád.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "Én... én egyszerűen nem hiszem el. Ilyesmi nem történik meg, "+GetSexPhrase("caballero","senorita")+"! Egy vagyont fizettél értem... csak úgy? És most mindennek vége? Nincs adósság, nincs üldözés? Mondd, igaz ez?";
			link.l1 = "Igaz, señora. Mindennek vége. Már senkinek sem tartozik semmivel.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "Ó, Kapitány, annyira nemes vagy! Olyan, mintha maga az Isten küldött volna! De el sem tudom képzelni, hogyan hálálhatnám meg. Maga... teljesen megváltoztatta az életemet, és én... mit tehetnék önért?";
			link.l1 = "Nem kell semmit tenned, Marisa. Csak élj. Félelem nélkül, a múlt láncai nélkül. Térj vissza a régi életedhez, és találd meg benne a boldogságot – ez lesz a legszebb köszönet, amit adhatsz nekem. Gyere, elkísérlek a városba.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "Mit tettél, kapitány, megölted őt!";
			link.l1 = "Így van, señora. Meg kellett védenem önt és a becsületét...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "Ó, Kapitány, egy élet kioltása, még ha olyané is, mint az övé, borzalmas és súlyos bűn! Éjjel-nappal imádkoznod kell, hogy akár csak egy kicsit is lemoshass belőle a halhatatlan lelkedről. Isten a tanúm, egyszerűen odaadhattam volna neki mindent, amim csak volt, és elment volna... De most... most már az ő vére a te kezedhez tapad, és csak az égiek döntik el, hogy megbocsátanak-e neked!";
			link.l1 = "Talán az Úr akarata volt. De ne rágódjunk ezen. Inkább menjünk ki ebből a barlangból.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "Kapitány, engedje meg, hogy ismét megköszönjem! Imádkozni fogok az egészségéért és jólétéért, "+pchar.name+". Kérem, jöjjön el templomunkba – adjon az Úr bocsánatot minden bűnére, és áldja meg Önt.";
			link.l1 = "Lehet, hogy egyszer benézek. És ne feledd, Marisa, ha nem látom ott a vidám arcodat, nagyon csalódott leszek.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... Olyan kedves vagy hozzám. Igazán örülök majd, ha újra látlak a városunkban. De most bocsáss meg, alig várom, hogy rendbe tegyem az életem, és megosszam a jó hírt Doloressel.";
			link.l1 = "Természetesen, Marisa. Viszlát. Vigyázz magadra.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "Kapitány, engedje meg, hogy ismételten kifejezzem végtelen hálámat! Valóban lehetetlent tett értem! Jósága és nemessége miatt szeretném elmondani, hogyan sikerült elkerülnöm a zsoldosokat az elmúlt két évben. Talán ez a tudás egyszer még az ön hasznára is válhat.";
			link.l1 = "Köszönöm, señora. Ilyen ügyekben a tudás annyit ér, mint az arany. Figyelek.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "Így telt el ez a két évem. Egy olyan világban, ahol az erő mindennél többet számít, az, hogy tudod, miként maradj az árnyékban, olyan lehetőségeket nyit meg előtted, amikről mások csak álmodhatnak.";
			link.l1 = "Köszönöm, hogy megosztottad a történeted, Marisa. Sokat átéltél, és a tapasztalatod valóban felbecsülhetetlen.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "Őszintén örülök, ha újra látom Önt a városunkban. Kérem, látogasson el templomunkba—adja meg az Úr Önnek bocsánatát minden bűnére és áldását.";
			link.l1 = "Lehet, hogy egyszer benézek. És ne feledd, Marisa, ha nem látom ott a vidám arcodat, nagyon csalódott leszek.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ah, Kapitány... Olyan kedves vagy hozzám. De most bocsáss meg, alig várom, hogy rendbe tegyem az életem, és megosszam a jó hírt Dolores-szel.";
			link.l1 = "Természetesen, Marisa. Viszlát. Vigyázz magadra.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Hallották? "+GetFullName(pchar)+" kapitány a saját pénzéből fizette ki Calder özvegyének adósságát! Nem sokan lennének ilyen nagylelkűek egy idegenért. Még mindig vannak igazi caballerók Spanyolországban!", "Öröm látni, hogy Spanyolországban nemcsak tisztességes caballerók élnek, hanem olyan nők is, akik bátorságban és becsületben sem maradnak el a férfiaktól.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("Azt beszélik, egy kapitány a saját pénzét adta, hogy megszabadítsa Calder özvegyét a néhai férje adósságaitól! Nem mindenki tenne ilyen nemes gesztust. Igazi becsületes ember, nem igaz?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kapitány, olyan öröm újra látni! Reméltem, hogy benézel. Talán ma van egy kis időd, hogy maradj és imádkozzunk együtt?";
						link.l1 = "Örülök"+GetSexPhrase("","")+" találkozás, Marisa. De attól tartok, most nincs időm maradni. Emlékszem a kötelességemre az Úr előtt, de az imádság most várhat.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "Kapitány, ismét ön! Mindig öröm találkozni. Úgy tűnik, az Úr nem engedi, hogy elfelejtse az utat a templomhoz... Talán mégis jut majd ideje egy imára?";
						link.l1 = "Marisa, jó látni téged. De nem maradhatok – a dolgom nem várhat. Hiszem, hogy az Úr az imádság nélkül is ismeri a gondolataimat.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kapitány, micsoda öröm újra látni önt! Minden nap hálát adok az Úrnak a jóságáért. A világ is fényesebb lett, amikor segített nekem.";
						link.l1 = "Örülök"+GetSexPhrase("","")+"   Örülök, hogy jó egészségben látlak, Marisa. Remélem, az élet nem hozott neked újabb kellemetlen meglepetéseket. Sokkal boldogabbnak tűnsz.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "Kapitány, annyira örülök, hogy látom Önt! Valahányszor betér templomunkba, béke tölt el. Önnel együtt a jócselekedetek fénye is megérkezik.";
						link.l1 = "És én is örülök"+GetSexPhrase("","")+" Jó látni téged, Marisa. Hozzászoktál már a nyugodt élethez, vagy néha még visszagondolsz a régi időkre?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", ha mindenki halogatná az imát, a világ már rég sötétségbe borult volna. Tedd félre egy időre az aggodalmaidat – a bűnbánat erőt ad, hogy továbbmenj.";
			link.l1 = "Értem, Marisa, de most tényleg nem tudom megtenni. Hiszem, hogy az Úr szavak nélkül is meghallgat.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", meggondoltad magad? A bűnök nem tűnnek el maguktól, és minél tovább vársz, annál nehezebbé válnak.";
			link.l1 = "Sajnos mennem kell. De legközelebb ígérem, hogy imádkozni fogok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "De a hit nem csak tudás, hanem cselekvés is! Nem halogathatod örökké a megváltás útját. Nem akarod végre érezni, milyen megkönnyebbülés megszabadulni a bűn terhétől?";
			link.l1 = "Talán, de most még nem. Halljon meg az Úr, még ha az imádságnak várnia is kell.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Kapitány, nem gondolja, hogy a bűnbánat halogatása önmagában is bűn? Egy nap talán már túl késő lesz.";
			link.l1 = "Talán, de attól tartok, ma nincs időm. A hitem velem van, és az Úr látja a bűnbánatomat még ima nélkül is.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Igen, neked köszönhetően újra szabadon lélegezhetek. Az Úr vigyázzon rád és utadra. Talán imádkoznál velem?";
			link.l1 = "Úgy hiszem, az imáid már most is elég erősek. Ami igazán számít, hogy mostantól csak jóság vesz körül.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", mégis meggondoltad magad? Imádkozzunk a Teremtőnkhöz?";
			link.l1 = "Sajnos, Marisa, most mennem kell, dolgaim vannak.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "Csak előre próbálok nézni. Most már van jövőm, és mindezt neked köszönhetem. Talán együtt kellene hálát adnunk ezért az Úrnak?";
			link.l1 = "Azt hiszem, te jobban boldogulsz, mint én tenném. A legfontosabb, hogy az imáid békét hozzanak neked.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", talán rá tudlak venni, hogy legalább egy imát elmondj?";
			link.l1 = "Bocsáss meg, Marisa, de sajnos most nincs időm. Imádkozz értem is.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Kapitány, ez nem az a hely. A barlang, amit keresünk, a Mosquitos-öbölnél van.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}