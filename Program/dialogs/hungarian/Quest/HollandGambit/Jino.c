// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "Jó napot, uram. Hogy került ide?";
				link.l1 = "Jó napot, Gino. Ismerkedjünk meg egymással. A nevem "+GetFullName(pchar)+" kapitány, és John engedélyével vagyok itt. Tisztázni fogom - szükségem van a segítségedre, de én is tudok segíteni neked.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ó! Jó napot, uram. Hogy került ide? És hol van John?";
				link.l1 = "Nocsak, nocsak... És ez az, aki mindig is a zárt ajtó mögött bujkált! Érdekes... Johnnal kapcsolatban... Elment. És ez a ház most már az enyém. De ne aggódj. Ismerkedjünk meg egymással, ki vagy te és mit keresel itt?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "Hello, " + pchar.name + ". Az arcod elárulja, hogy valami fontosat találtál. Megtaláltad az Igazság Ôrének minden összetevôjét?";
					link.l1 = "Pontosan! Mindhárom elem nálam van: a tôr, a térkép és az iránytû!";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "Hello, " + pchar.name + ". Mi történt? Furcsa az arckifejezésed...";
					link.l1 = "Beszélnünk kell valamirôl, Gino. Nagy dologról van szó.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Igen, emlékszem, két nap telt el, és az Igazság Ôrzôjérôl akarsz tudni, igazam van?";
					link.l1 = "Igen, így van! Sikerült elôásnod valamit?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "Hoztál 5000 pesót, " + pchar.name + "?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "Persze. Tessék, fogd a pénzt és vegyél meg mindent, amire szükséged van.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "Sajnos jelenleg nincs nálam a pénz.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "Sajnos, " + pchar.name + ", nagyon sajnálom - a beteg meghalt. Hirtelen rosszabbodott az állapota és nagyon gyorsan elhunyt.";
					link.l1 = "Kár... Isten irgalmazzon a lelkének!";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "Hello, " + pchar.name + ". Történt valami? Nagyon aggódónak tûnsz...";
					link.l1 = "Gino, van egy szokatlan kérésem a számodra! Van egy magas lázas ember a hajónkon. Félrebeszél és eszméletlen... tudsz rajta segíteni?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = "" + pchar.name + ", Várom a beteget. Siess, minél hamarabb idehozod, annál nagyobb az esély, hogy meg tudom menteni.";
					link.l1 = "Igen, igen, azonnal ide fogjuk szállítani.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "Épp idôben hoztad el, " + pchar.name + ". Kritikus állapotban van, de még mindig van esély.\nKapitány, kifogyok a hozzávalókból, és nincs idônk összegyûjteni ôket a dzsungelben. Meg kell vennem az összeset a helyi gyógynövénykereskedôktôl 5 000 pesóért. Meg tudná adni az összeget?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "Persze. Tessék, fogd a pénzt és vegyél meg mindent, amire szükséged van.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "Sajnos most nincs rá pénzem.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "Most nincs mit mondanom, " + pchar.name + ". A beteg életéért küzdök. Még van némi remény. Jöjjön el hozzám késôbb, gondolom, hamarosan tudok majd valami konkrétabbat mondani.";
					link.l1 = "Rendben, Gino, késôbb visszajövök.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "Híreim vannak," + pchar.name + ". Nem mondom, hogy az embere jól van, de él. A betegség visszahúzódik, és van fejlôdés látható. Hogy ôszinte legyek, nem számítottam rá, hogy a fôzeteim ennyire segíteni fognak rajta.";
					link.l1 = "Ez nagyszerû hír, Gino, de mondd meg, mikor tudom elvinni? Hosszú út áll elôttünk, és az óra ketyeg.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "Jó napot, kapitány. Örülök, hogy látom.";
					link.l1 = "Hogy van a betegünk, Gino?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "Jó napot, kapitány. Hogy van? Szüksége van a segítségemre?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "Hogy van a betegünk, Gino? Gino, úgy veszem észre, hogy ön egy mûvelt ember, és talán még latinul is tud...";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "Nekem valami más van. Egy kis ajándék neked. Tessék, nézze meg ezt a könyvet.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "Igen, Gino. Szeretném megmutatni ezt a pisztolyt. Látott már valaha ilyet?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "Hoztam neked egy példát a pisztolyom töltetérôl.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "Mi a helyzet a pisztoly tölteteivel? Van már valami nyom?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "Gino Megtaláltam a számomra ismeretlen szót 'gord' egy kapitányi naplóban. Tudod, hogy mit jelent?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "Jó napot, Gino. Jól vagyok, nincs szükségem segítségre. Csak be akartam nézni hozzád és beszélgetni egy kicsit.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "A nevem Gino. Gino Gvineili. Tudós vagyok. Az a munkám, hogy porokat, keverékeket és egyéb gyógyszereket készítsek Murdock úrnak. De mióta ô elment...";
			link.l1 = "Nos, én vagyok "+GetFullName(pchar)+". A saját hajóm kapitánya. Szóval akkor alkimista vagy?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Nemcsak alkimista, hanem orvos is. Elég nagy orvosi tudással rendelkezem. Sok mindent tudok a gyógyító gyógynövényekrôl, és képes vagyok keverékeket és fôzeteket fôzni belôlük. De a kémia a hivatásom, sokat kísérletezem, és néhány találmányom talán segíthet a hozzád hasonló embereken.\nTudok latinul, franciául, angolul és olaszul. A segítségem nélkülözhetetlen lesz, ha egy olyan gyógyszertárat tervezel vezetni, mint Mister Murdock...";
			link.l1 = "Oho! Nem mindennap találkozik az ember ilyen mûvelt emberrel. A gyógyszertári szakma biztosan jó, de én tengerész vagyok... hm, ez még nekem is furcsán hangzik... mindenesetre biztos vagyok benne, hogy barátok leszünk, Gino. Továbbra is itt élhetsz, és csinálhatod a tudományos dolgaidat...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "És ha valaha is szükségem lesz egy alkimista, egy gyógyító vagy egy tudós segítségére - tudni fogom, kitôl kérhetem... Mondd csak, miért élsz mindig bent? Nem mész ki néha?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Én akkor megyek ki, amikor a kísérleteimhez kell néhány hozzávalót vagy gyógynövényt vásárolnom. Szeretek egyedül élni, ez az én módszerem. Az életemet a tudománynak szenteltem, és nem érdekel a hétköznapi élet. Könyvek, írások, kémcsövek, retorták...\nMister Murdock adott nekem ilyen lehetôséget, cserébe azért, hogy segítsek neki drogokat elôállítani.";
			link.l1 = "Most még több idôd lesz, Gino. De le kell mondanod a kísérleted idejébôl, ha szükségem lenne a segítségedre, megegyeztünk?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Persze, kapitány. Kapitánynak fogom szólítani, "+GetAddress_Form(NPChar)+", ha nem bánja? Itt hagyom az összes kutatásomat, ha esetleg szüksége lenne a gyakorlati képességeimre vagy az elméleti tudásomra.";
			link.l1 = "Nagyszerû. Örülök, hogy ilyen gyorsan megértettük egymást. Ne aggódjon a költségei miatt, én vagy a tárcám idôrôl idôre ésszerû összegeket hagyunk magának.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Köszönöm, kapitány. Nincs szükségem sok mindenre... Kapitány, van egy ötletem... miért nem tanulsz meg egy kis alkímiát? Az nagyon hasznos lehet önnek.";
			link.l1 = "Hm. Ahogy a bátyám mondta nekem egyszer - ne légy finnyás, ha saját kezûleg kell megtanulni dolgokat csinálni. Szóval persze, miért ne. Mit tudsz nekem mutatni?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Nos, természetesen nem fogod tudni a vasat arannyá változtatni, az lehetetlen... egyelôre, de megtanulhatod, hogyan keverj össze összetevôket az utasítások szerint, hogy bájitalokat vagy más hasznos tárgyakat kapj az eredményül. Tessék, fogd ezt a zsákot. Minden benne van, amire a kezdô alkimistának szüksége lehet. Próbakövek, lombikok, retorták, lepárlók, spatulák, üvegcsövek, égô és így tovább...";
			link.l1 = "Lenyûgözô!";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("Kaptál egy alkimista készletet");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Egy bájital vagy tárgy elkészítéséhez ismerned kell egy receptet. A recepteket a kereskedôktôl lehet megvásárolni, vagy bárhol megtalálhatók. Miután tanulmányoztál egy receptet, össze kell gyûjtened minden szükséges hozzávalót, és pontosan azt kell tenned, ami oda van írva.\n Használd az alkímia eszközeidet, keress vagy vegyél mozsarat és mozsárt, keress tégelyt, sajnos nincs nálam egy extra, amit adhatnék. Gyógynövények, szeszek, bájitalok, ásványok, szemét - minden megteszi, feltéve, ha van megfelelô recepted és szerszámod.";
			link.l1 = "Látom. Megpróbálok valamit keverni a szabadidômben. Köszönöm, Gino! Tudsz adni valami egyszerû receptet? Valamit, amivel elkezdhetem? ";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "Nekem nincsenek egyszerû receptjeim... de itt van ez az ellenszer receptje. Feltételezem, hogy képes vagy megbirkózni ezzel a feladattal. Vedd el.";
			link.l1 = "Köszönöm! Megtanulom. Viszlát, Gino! Figyeld a házamat, attól tartok, hogy nem fogok ide gyakran ellátogatni, úgyhogy szívesen látlak nemcsak a szobádban, hanem az épület többi részében is.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("Kaptál egy ellenszer receptet");
			PlaySound("interface\notebook.wav");
			Log_Info("A bájitalok, amulettek és tárgyak készítéséhez az alkímia készségre van szükséged!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "Igen, kapitány úr, ismerem az ókori rómaiak nyelvét. Minden tudósnak, különösen egy gyógyítónak vagy alkimistának tudnia kell latinul. Szüksége van a latin tudásomra?";
			link.l1 = "Igen, uram. Gino, ne tartson bolondnak, de... nos, hogy is mondjam...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "Beszéljen úgy, ahogy van, kapitány. Ne szégyenlôsködjön.";
			link.l1 = "Jól van. Tudnál nekem egy listát készíteni a latin aforizmákról? Tudod, van... egy ember, aki szeret dicsekedni a 'erudíciójával' és néha ezeket a latin kifejezéseket használja, hogy megmutassa nekem, milyen tudatlan vagyok hozzá képest. Something like... 'pasem-bellum'...";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "'Si vis pacem, para bellum', úgy érti?";
			link.l1 = "Igen, igen. Meg akarom tanulni ôket, hogy legyôzzem az arrogáns br... barátomat.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "Nincs semmi furcsa vagy szégyenletes a kérésében, kapitány. Ha ismeri az ókoriak aforizmáit, akik beírták magukat a történelembe, az mûvelt emberré teszi. Tessék, fogd ezt a szöveget. Ez az, amit kért.";
			link.l1 = "Köszönöm, Gino! Nagyra értékelem! El fogom olvasni a szabadidômben...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("Lavoisier kémia tankönyvét adtad oda.");
			dialog.text = "Mutasd meg... (olvasás) Lehetetlen! Azt mondod, egy 'kis ajándék'?  Ez a könyv felbecsülhetetlen értékû! Honnan szerezted? Ez... egy igazi kincs!";
			link.l1 = "Örülök, hogy tetszik.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(Olvasás) Hihetetlen! Errôl még csak nem is hallottam... és ez? Itt semmit nem értek... de majd fogok, a fenébe is! Ó, hamarosan forrni fog a munka a laboromban! "+pchar.name+", fel sem fogod, hogy MI mindent adtál nekem...";
			link.l1 = "Miért nem tudom? Én tudom. Egy tudományos könyv egy tudósnak...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "De ki a szerzôje ennek a csodának? Antoine-Laurent de Lavoisier, Franciaország... Soha nem hallottam róla. De várjon! Hogy lehetséges ez? A nyomtatás éve 1789? De hogyan...";
			link.l1 = "Én sem tudom, miért van ráírva az az évszám. Hát, talán én tudom. De azt tanácsolom, hogy ne gondolkodjatok ezen túl sokat. A könyv hasznos, és csak ez számít.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "Mérhetetlenül ígéretes, és az az évszám biztosan valamilyen nyomdai hiba... Mindegy. Köszönöm szépen, kapitány úr!";
			link.l1 = "Szívesen, Gino. Ez mind a tiéd.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "Ez még nem minden, Gino. Szeretném megmutatni ezt a pisztolyt. Láttál már valaha ilyet?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "Nem vagyok fegyverkovács, de megnézem... nem, még sosem láttam ilyet. Miért kérdezed?";
			link.l1 = "Ez a pisztoly erôs és pusztító, de a használatához különleges töltetekre van szükség. Semmi más nem mûködne. És fogalmam sincs, hogyan lehetne több töltényt készíteni hozzá. Ezért jöttem ide, hogy tanácsot kérjek.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "Van legalább egy tölténye, amit megmutathatna nekem példaként? Ha nincs, akkor attól tartok, nem tudok segíteni.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "De van. A töltet két részbôl áll: maga a töltény a golyóval és ez a dolog, ami felrobbantja a lôport.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "Micsoda hiba! Micsoda szégyen! Rendben, talán találok még, és elhozom önnek.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("Egy revolver töltényét adtad oda.");
			Log_Info("Kapszulát adtál");
			PlaySound("interface\important_item.wav");
			dialog.text = "Érdekes! Ez egyszerûnek tûnik, van benne lôpor, a golyó felülrôl megy be, de egy kicsit furcsán néz ki. És ez 'dolog'.... hm. A lôpor nem robban fel anélkül, nem? Kíváncsi vagyok... Nézze, kapitány, hagyja ezt az egészet rám: a pisztolyt és a tölteteket. Jöjjön el hozzám egy hónap múlva, idôre van szükségem, hogy kitaláljam.";
			link.l1 = "Remek! Próbálja megérteni, hogyan mûködik, én tényleg lôni akarok ezzel a pisztollyal.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "A fô probléma az, hogy kiderítsük, mibôl készül ez az anyag, ami felrobbantja a puskaport. Ez a könyv jól fog jönni. Megpróbálok mögé kerülni.";
			link.l1 = "Rendben. Viszlát, Gino!";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "Igen, rájöttem, mibôl készül a pisztoly töltete. Köszönöm a könyvet, amit kaptam tôled. Nélküle nem mûködött volna. De figyelmeztetnem kell, kapitány, nem lesz könnyû elkészíteni a töltényeket és a kapszulákat ehhez a fegyverhez.";
			link.l1 = "Kapszulák?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "A kapszula az 'thing' az, ahogy mondta, felrobbantja a port. De kezdjük a tetejérôl. Készen állsz?";
			link.l1 = "Igen! Nagyon figyelek rád.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "Szóval, elôször is, egy különleges golyót kell készítened. A közönséges golyók nem fognak mûködni. Valami különleges kúp alakúnak kell lennie. Találnod kell egy formát az ilyen golyókhoz, a golyóformát, ahogy én neveztem. Vegyetek közönséges ólomgolyókat, olvasztjátok meg ôket egy tégelyben, és öntsétek az olvadt ólmot a golyóformába. Fagyassza le ezt az öntvényt, és vegye ki belôle a kész golyót.";
			link.l1 = "És hol találok ilyen golyóformát?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "Nem tudom, kapitány úr. Alkimista vagyok, nem kovács. Vegye példának ezt a golyót, talán rájön, mit kell tennie.";
			link.l1 = "Rendben. Menjen csak...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "Akkor készítsen egy edényt a pornak. Oda fecskendezed a golyót. Írtam neked egy szép útmutatót. Olvasd el figyelmesen és próbáld ki.";
			link.l1 = "Jó...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "Most már csak a kapszulákat kell megszereznünk. Szükséged lesz egy nagyon vékony rézlemezre - készítsd el magad egy rézrögbôl. Vésd bele a körökkel megegyezô méretû köröket. Ezután viasz segítségével tegyél beléjük ezüstöt.";
			link.l1 = "Fumináló ezüst? Az meg mi?";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "Magam sem tudtam róla, a könyvébôl tanultam meg a titkot. Ez egy fehér por, amit ezüstbôl, szeszbôl és salétromsavból lehet készíteni. Dörzsöléstôl vagy rázástól könnyen felrobban, ezért jól szolgál a pisztolyod lôporának elsütésére. Kellemetlen dolog, kétszer is felrobbant a kísérleteim során, amíg ki nem találtam a receptet.";
			link.l1 = "Szerencsém volt, hogy nálam volt ez a könyv!";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "Legyetek erôsen óvatosak, ez a cucc pokolian robbanékony! Én magam is tudnék készíteni belôle némi mennyiséget, de a fulmináló ezüst tárolása túl veszélyes, létfontosságú, hogy a készítése után azonnal a kapszulákba tegyétek. Rézkapszulákat nem tudok készíteni, nem vagyok kovács, mint már mondtam.";
			link.l1 = "Rendben. Add meg a receptet, megtanulom magam is.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "Szívesen. Pontosan kövesse a receptet, és ügyeljen a folyamat sorrendjére, különben az egekbe repíti a lombikjait.";
			link.l1 = "Óvatos leszek.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "Fogd ezt a két lombikot is. Ebben salétromsav van, ebben pedig szesz. Elég fulmináló ezüstöt fogsz tudni készíteni, hogy körülbelül 20 kapszulát tölts meg.";
			link.l1 = "Köszönöm, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("Kaptál egy flaskányi salétromsavat");
			Log_Info("Kaptál egy flaska szeszes italt");
			PlaySound("interface\important_item.wav");
			dialog.text = "Fogd a pisztolyodat és a példatöltetet is. Sok szerencsét, kapitány, a töltetek elkészítéséhez. Remélem, hogy életben maradsz és egyben maradsz.";
			link.l1 = "Megteszem, amit tudok, hogy megvédjem magam. És, Gino, mondtam már, hogy zseniális vagy?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "Elpirulok magától, kapitány, komolyan mondom...";
			link.l1 = "Hát persze. Viszlát, Gino! Te vagy a legjobb alkimistám!";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "Gord, Gord... Mesélnél még a kapitányról? Honnan jött?";
			link.l1 = "Fogalmam sincs, bár valahol északon született, néha vikingnek hívták.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Egy viking! Igen-igen, emlékszem, olvastam róla egy történelemkönyvben. Gord egy szabad jarl megerôsített települése.";
			link.l1 = "Egy szabad jarl? Ki lehet az?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Az északiak egyik hercege. A szabad jarlok a hadicsapataikkal évszázadokkal ezelôtt a hajóikon, a Drakkarokon portyáztak és fosztogattak Európában. Nevezhetnénk ôket kalózoknak is, gondolom. A gordok voltak a bázisaik és otthonaik, helyek, ahol megpihenhettek, gazdálkodhattak és lakomázhattak.";
			link.l1 = "Értem már. Akkor ez a gord lehet a kalózok búvóhelye... Köszönöm, Gino!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "Láz és téveszmék, azt mondod, ez érdekes. Azonnal hozzátok ide! Meglátom, mit tehetek. De nem ígérhetek semmit, ha az állapota túl rossz... Ô a maga tisztje?";
			link.l1 = "Nem, hála Istennek, nem az. Gino, figyelj, ne kérdezd meg, hogy ki ô, csak tedd meg, amit tudsz, ez nagyon fontos nekem!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Rendben, hozd be a házba, a szobádba. Készítek néhány keveréket... talán ez a gyökér...";
			link.l1 = "Azonnal ide fogom szállítani!";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "Akkor próbáld meg minél hamarabb megtalálni, gyógyszerek nélkül nem fogom tudni meggyógyítani, és lehet, hogy már késô lesz, ha nem sietsz.";
			link.l1 = "Rendben, megkeresem a pénzt.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Nagyszerû, kapitány. Most pedig foglalkozom néhány keverék elkészítésével, és javaslom, hogy hagyja el a betegemet. Jöjjön vissza holnap.";
			link.l1 = "Rendben, Gino. Bízom a keverékeidben és a zsenialitásodban.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "Nos, azt hiszem, két hét múlva rendbe fog jönni. Azt nem ígérhetem, hogy képes lesz táncolni, de az biztos, hogy legalább saját lábára fog állni.";
			link.l1 = "A fenébe is, nekem nincs meg ez a két hét! Muszáj... minél hamarabb kihajózni!";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Kapitány, én nem vagyok mágus, és biztosíthatom, hogy a férfi egyelôre túl gyenge. Nem vagyok benne biztos, hogy túlél néhány napot a hajón, nem mozdíthatja meg!";
			link.l1 = "Jó-rossz, de két hét, nem, még egy hét is túl sok!";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Három nap... igen, azt hiszem, három nap múlva megpróbálhat hajózni, de szüksége lesz ellátásra és gyógyszerekre, és meg kell majd állnia.";
			link.l1 = "Van egy orvosom, ô majd gondoskodik róla. Három nap múlva visszajövök, és elvisszük ôt, ez a legtöbb, amit megengedhetek magamnak. Mennünk kell, még ha megállunk is... igen, és még valami - Gino, te egy zseni vagy!";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "Köszönöm, kapitány. Jöjjön vissza a barátjáért három nap múlva, de addig ne zavarja. Teljes pihenésre van szüksége.";
			link.l1 = "Rendben, értem. Három nap múlva elviszem.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "Jól van, de lassan halad. Még nem lehet elvinni.";
			link.l1 = "Igen - igen, Gino, emlékszem. Három nap...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "Nem romlott, de nem is javult igazán. Még mindig eszméletlen, nem érti, hol van, és miért van itt, bár úgy tûnik, ez nem nagyon foglalkoztatja. Még mindig lázas, úgyhogy nem vagyok benne biztos, hogy jó ötlet lenne most a fedélzetre vinni.";
			link.l1 = "Nem tudok tovább várni, már túl régóta vagyunk itt. Csomagolja be a keverékeket, amelyek segíteni fognak neki az úton, és indulunk. Remélem, hogy ez a fattyú elég erôs ahhoz, hogy túlélje a halálos ítéletét...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "Várjon, kapitány! Én kezeltem a halálraítélteket? Mi a fene? Hatalmas munkát végeztek itt, van fogalmad róla, milyen nehéz a száraz por elôállítása...";
			link.l1 = "Gino, ezt nem kellett volna tudnod. Ne aggódj túlságosan, ô egy kalóz, és az egyik legszörnyûbb a maga nemében. A lehetô leghamarabb el kell vinnem Curacaóba, hogy találkozzon a Társaság hatóságaival. Idôpont.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "Rendben, te jobban tudod. Akkor kalóz... Curacao. Mindegy, de figyelj rám, az idô nagy részében aludni fog, de a hajó sodrása és a fülledt hôség hátráltathatja az egész folyamatot. Javaslom, hogy néhány nap hajózás után álljon meg, és hagyja, hogy a... foglya a szárazföldön pihenjen. Ellenkezô esetben fennáll a veszélye, hogy Curacaón fel kell akasztaniuk egy holttestet... ";
			link.l1 = "Rendben, akkor megteszem. Martinique jó lesz, majdnem félúton van Curacao felé. Remélem, hogy a szél jó lesz. Most fogom ôt, és elindulunk. Még egyszer köszönöm, Gino.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "Szívesen, kapitány. Ne feledje, hogy négy napja van, vagyis öt, de nem több. És még egy utolsó dolog... tudod, én általában nem azért gyógyítom az embereket, mert azt akarom, hogy a kezelésem után felakasszák ôket. Az orvos felelôs a betegeiért, nem számít, hogy kik azok. És nagyon rosszul érzem magam...";
			link.l1 = "Sajnálom, hogy belerángattalak ebbe az egészbe, de nélküled nem volt esélyünk. Azonnal el kell indulnunk, különben a portugál legényeknek sikerül az ajtónk elôtt összegyûlniük, hogy találkozzanak a fônökükkel.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "Érdekes... És miben tudsz segíteni nekem? Nincs szükségem segítségre, és nem is kértem...";
			link.l1 = "De szükséged lesz rá. Elôbb hallgass meg, aztán döntsd el.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "Csupa fül vagyok.";
			link.l1 = "Nemrég jártam Santiagóban... Vincento atyát látogattam meg. Az eltûnt titkárnôjét kereste... Jézusom, miért vagy ilyen sápadt, Gino?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Te... láttad az inkvizítort? Ô...";
			link.l1 = "Ne aggódj, Gino. Nincs rá esély, hogy átadjalak neki, bár ez volt a parancsa: megtalálni téged és elvinni hozzá. Szükségem van néhány információra az Itza nép egyik indiánjáról. Mesélj nekem Tayasalról, a kincseirôl és a 'evil' ról.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Látom, hogy jól informált vagy. Vincento atya mondta ezt neked?";
			link.l1 = "Néhány információt tôle kaptam, néhányat pedig más emberektôl. De szeretném meghallgatni téged. Egykor a titkára voltál, így bizonyára te készítetted a kihallgatási protokollt, igazam van?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "El sem tudja képzelni, mit tett azzal a szegény indiánnal... A hideg futkos a hátamon, valahányszor eszembe jut az a kihallgatás.";
			link.l1 = "Mégis, beszéljünk róla. Ki volt az az indián? Hogy került Vincento atya kezébe?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Az Itza nép indiánjai között volt, akik Tayasalból a Kukulcan maszk - az ôsi maja isten, Kukulcan ereklyéje - keresésére indultak. Azok az indiánok egy csapat fehér kalandorral kerültek szembe, akiket Archibald Calhoun - egy skót kincsvadász - vezetett. Csak egy indián maradt életben, az ô neve Ksatl Cha volt. Három érdekes tárgy volt nála, ezekrôl majd késôbb mesélek.\Calhoun megpróbálta kényszeríteni a foglyot, hogy meséljen neki a kincsekrôl, de az hallgatott. Ezért a skót átadta ôt Santiagóba, Vincento atyának, cserébe azért, hogy egy évig engedélyt kapjon a spanyol városok látogatására. Tudta, hogy az inkvizítort nagyon érdekli mindenféle helyi rejtély és legenda. Vincento szóra bírta az indiánt. Sokat kezdett beszélni, mindent elmondott, amit tudott, és az információk, amelyeket kiszedtünk belôle, magát az inkvizítort is megdöbbentették.";
			link.l1 = "Nem mondod? És mitôl remeghetett meg Ôkegyelmessége?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Mindent el fogok mondani nektek sorban. Yucatán dzsungelének mélyén van egy ôsi maja város, Tayasal. A maják utódai, az Itza nép lakja. Ôk igyekeznek az ôseik szabályai és hagyományai szerint élni az életüket. Bizonyára nem tetszik nekik a modern világ állapota - mármint a fehér ember uralma.\nA régi szép idôkrôl álmodoznak. És itt jön a legérdekesebb rész. Egy csapat fehér kalandor véletlenül Tayasal közelébe jutott, és elrabolta az Itza nép legfôbb fônökének lányát. Ez majdnem negyedszázaddal ezelôtt történt.\nEz volt az utolsó csepp a pohárban, és Kanek, a fônök feldühödött. Elhatározta, hogy elvégzi a maják legveszélyesebb és legtitkosabb rituáléját: megidéz egy indián istent, hogy a fehér hódítók minden utódját eltörölje...";
			link.l1 = "Hm... Ez lehet az a démon, akirôl Vincento atya beszélt. De hogyan kellene ennek az indián istennek bánnia a fehér gyarmatosítókkal? Megjelenjen sárkány alakjában és égesse el ôket?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Ó, "+pchar.name+", hagyd meg ezeket a tûzszörnyes meséket az öreg nagyiknak! Igazából nem is tévedsz annyira, de a mi esetünk nehezebb és súlyosabb. Még az özönvíz sem fogja tudni megakadályozni Európa terjeszkedését az Újvilágban. Tíz újabb fog jönni egy halott helyett. Kaneknek magának az európai gyarmatosítás lehetôségét kellett elpusztítania.";
			link.l1 = "Nos, ez már megtörtént.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Jó irányban gondolkodik, kapitány... Kanek rítusának célja nem csak a magas lény megidézése volt, hanem egy tér-idôbeli lyuk létrehozása is.";
			link.l1 = "Micsoda?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "A maják ôsei elég nagy tudással rendelkeztek, kapitány. Kanek megtalálta egy rítus leírását, amely lehetôvé teszi az idô irányítását.";
			link.l1 = "Hûha! Hihetetlen!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Hallgassa meg. A rituálé végsô célja a múlt megváltoztatása, hogy lehetetlenné tegye a fehér ember megjelenését az Újvilágban. Hogy ezt megtehessék, elküldenek valakit a múltba, valakit, akinek hatalma, hatalma és képessége van arra, hogy megváltoztassa az emberek sorsát. De ami a legfontosabb, egy ilyen személynek rendelkeznie kell modern tudással.\nGondoljunk csak bele, "+pchar.name+", mi történt volna Kolumbusszal, ha karavelláival egy modern ágyúkkal felfegyverzett indián fregattokból és gályákból álló flotta találkozik? És mi lett volna, ha a fehér katonák hekkjei nem íjakkal és lándzsákkal, hanem mozsárágyúkkal és muskétákkal szálltak volna szembe?";
			link.l1 = "Feltételezem, hogy Amerikát egyáltalán nem fedezték volna fel.....";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Pontosan! És talán egy indián 'Kolumbusz' felfedezte volna Európát...";
			link.l1 = "Érdekes, és kit küld Kanek a múltba? Az egyik meztelen harcosát? Kétlem, hogy képes lenne tanítani az ôseinek...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Ne nevessen, kapitány. Kanek nem pazarolt éveket a maja templomokban az írásaik olvasására. Egy indián istent kell a múltba küldeni emberi alakban...";
			link.l1 = "Gino, miféle ostobaságról beszélsz? Te vagy az....";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Még a mi Urunk Fia, Jézus Krisztus is emberi alakban jött a földünkre, és egy emberi nôtôl, a Szent Szûz Máriától született...";
			link.l1 = "Jézusom, Gino... komolyan beszélsz?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Persze, hogy komolyan. Ksatl Cha nagyon meggyôzô volt...";
			link.l1 = "De melyik Istent választotta Kanek egy ilyen 'nemes' küldetésre?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "A rítus csak egy Magaslényt volt hivatott megidézni. A tollas kígyó, Quetzalcoatl, Kukulcan...";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "Kukulcan?! Már voltam olyan vakmerô, hogy találkoztam az ô 'szellemével' amely szobrokban él. Most már értem... folytasd!";
			else link.l1 = "Hm. Érdekes. Már hallottam ezt a nevet Vincento atyától... folytasd!";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Kanek úgy döntött, hogy megidézi Kukulkant, mivel az Itzának már volt egy ôsi ereklyéje errôl az istenrôl - Kukulcan maszkja. Akinél a maszk van, az képes átmenni a portálon, és csak ôt fogadják el az ôsi maják élô istennek.\nA pap elvégezte a rituálét, megidézte Kukulkant, hogy testet öltsön egy halandó testében. Emellett létrehozott egy idôlyukat, amely több véletlenszerû embert a jövôbôl a mi idônkbe vonzott.\nA kivonulás célja az volt, hogy Kukulcan inkarnációja ne csak a mi korunk, hanem a jövô tudását is átadja. De valami rosszul sült el, és ezek az emberek mind máshová érkeztek, nem pedig Tayasalba. Soha nem találkoztam egyikükkel sem.\nA szigetcsoporton belül több portált is létrehoztak, ezek a jövô tudásának birtokosait és az Itza ügynökeit hivatottak voltak az egész területre és Tayasalba szállítani. De ezek a portálok nem teljesítették a céljukat, az elmúlt 25 évben senkit sem szállítottak Tayasalba...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "Persze... Mert ezek a portálok a foglyul ejtett embereket csak egymáshoz szállítják. Hihetetlen!";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "Érdekes...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "Láttad azokat a portálokat? Mondd el!";
			link.l1 = "Talán késôbb, Gino... Jelenleg jobban érdekel a te történeted. Folytasd csak!";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Vincento atya tisztában van mindazzal, amit elmondtam. Ez persze aggodalommal töltötte el. Ha Kukulcan, emberi alakban megtestesülve, eljut a portálhoz a Maszkkal és az összes összegyûjtött tudással együtt... Az idôk végezetéig. Apokalipszis.\nHa a múlt megváltozik - a jövô ugyanezt teszi. A valóságunk megváltozik, eltûnik, feloldódik. Te és én talán soha nem születünk meg. Vagy mások leszünk. Ha Kukulcan egyszer eléri a múltat - mi megragadjuk a létezést.";
			link.l1 = "És ki Kukulcan megtestesülése?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Ki tudja. Lehet, hogy bárkiben benne van, aki negyedszázaddal ezelôtt született, amikor a szertartást végezték. Például benned... csak vicceltem. De még mindig van esélyünk. Elôször is, Kukulcan megtestesülése csak egy halandó ember, megfulladhat, leszúrhatják, lelôhetik vagy belehalhat a lázba. És ilyen esetben nem fog bekövetkezni az apokalipszis.\nMásodik, a maszk nélkül lehetetlen eljutni a múltba, Kanek nagyon jól elrejtette, talán túl jól is úgy tûnik. Lehet, hogy még a megtestesült Kukulcan sem fogja megtalálni.";
			link.l1 = "Mesélj még.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "A szertartás után egy idôvel a spanyol hódítók egy csoportja majdnem elérte Tayasalt, és majdnem eljutott a kincstárig. Az Itzának sikerült mindannyiukat megölnie, kivéve egyet - egy erôs, két méter magas óriást.\nKanek aggódott, hogy a Maszkot bármelyik idegen ellophatja, ezért úgy döntött, hogy megvédi az ereklyét. Kitalálta a saját rituáléját, felhasználva az ôsi maják tudását. Három tárgyat vett magához, amelyekrôl úgy vélte, hogy a fehér ember erejét hordozzák. Egy tôrt, amely egykor maga Cortezé volt, és egy iránytût. Ezt a tôrt arra is használta, hogy a harmadik tárgyként egy darab bôrt faragjon ki az elfogott spanyol óriás hátából. Magát a férfit Kukulcan oltárán áldozták fel. A rituáléhoz három tárgyat használtak fel.\nEzzel a rituáléval egy új sziget született, a nyílt tengeren, nem messze Yucatántól. Senki sem tudja a helyét, de a Maszk ott van elrejtve. Ahhoz, hogy megtaláljuk, a tôrt, az iránytût és a bôrdarabot kell használni. Emellett a kincstár minden tárgya el van átkozva, egyetlen egy sem hagyhatja el a szigetcsoportot.\nAz erre tett kísérlet viharral jár, amely a hajót egyenesen a sziget szikláihoz viszi, ahol a maszk el van rejtve. A szigetet Ksocheatemnek hívják. Okos, nem igaz?";
			link.l1 = "Talán túlságosan is. Ezen nem vitatkozunk. De hogy a fenébe volt Ksatl Cha ilyen jól informált? Kétlem, hogy Kanek megosztotta volna ezt a tudást a közönséges harcosokkal...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "A helyzet az, hogy az Itza jelenlegi fônöke, Urakan, Kanek fia, mindent elmondott ennek a harcosnak. Elküldte Ksatl Cha-t egy csapat harcossal, hogy találják meg a titkos szigetet és Kukulcan maszkját. Ehhez az Igazság Ôrzôjét adta neki, ez a neve a három tárgynak együtt - a tôrnek, az iránytûnek és az emberi bôrbôl készült térképnek.";
			link.l1 = "A térképet? És miért volt szüksége Urakannak a Maszkra? Úgy döntött, hogy ô maga változtatja meg a múltat?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "A bôrön rajta vannak a szigetvilág körvonalai, ezért nevezik térképnek. Urakan nagyon egyszerû okból akarta a Maszkot - nem akarja elpusztítani a létezô valóságot, és nem akarja feláldozni az életét és a népe életét az ôsök dicsôségéért.\nEzért akarta mindenáron elpusztítani a Maszkot. De Ksatl Cha-t elfogta Calhoun, és... nos, a történet többi részét ismeritek. Sosem érte el Ksocheatemet.";
			link.l1 = "Tehát lehetséges megakadályozni az idôk végét a Maszk megtalálásával és elpusztításával? És hol van az a... Az Igazság Ôrzôje?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "A tôr 'Chiefs Claw' és az iránytû 'Az Út Nyila' a Calhounra maradt, a bôrtérkép 'Két megjelenés' pedig még mindig valahol az inkvizícióban van. Calhoun szájzárként használta, hogy befogja a fogoly száját. Fogalma sem volt, mire valók ezek a tárgyak.";
			link.l1 = "Mit mondtál? 'Chief's Claw'? Francba, ez a tôr most is rajtam van! Fadey adta nekem a bátyámmal szembeni adósságának törlesztéseként! Nézd meg!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "Hihetetlen... Tényleg az. Emlékszem rá.";
			link.l1 = "Gino, mondd csak, pontosan mit tud Vincento atya a történetedrôl?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "Mindent, kivéve az Igazság Ôrével kapcsolatos információkat, és azt, hogyan lehet elérni, hogy megmutassa a titkos sziget helyét, ahol Kukulcan maszkja el van rejtve. Ksatl Cha mesélt errôl, amikor kettesben voltunk, közvetlenül azelôtt, hogy beadtam neki a méregkeveréket, hogy véget vessen a szenvedésének. Mosollyal az arcán halt meg.\nAzt követôen, amit tettem, nem maradhattam Santiagóban. Komoly gyanúm volt, hogy fontos és veszélyes tanúja lettem az inkvizítornak. Vincento atya mindig megkapja, amit akar, bármi áron. Ksatl Cha mesélt neki a Tayasalban lévô kincstárról.";
			link.l1 = "Ezeket a kincseket már megtalálta egy Miguel Dichoso nevû kalandor. Hallottál már róla?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "Nem. És hol van most a kincseivel?";
			link.l1 = "Magam is szeretném megismerni. Ezért jöttem hozzád, mert azt az indiai aranyat keresem. Dichoso elvitte a kincseket Európába, és eltûnt velük.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "Megmondom, hol vannak a kincsek és maga Dichoso.";
			link.l1 = "Gino, te meglepsz engem. Honnan tudod ezt?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "Ezt maga is ki tudja találni a történetembôl, kapitány. A Tayasal kincseit elátkozták - egyetlen darabot sem lehet elvinni a szigetcsoportról. Bármelyik hajó...";
			link.l1 = "...elkapja a vihar, és a szigetre dobja, ahol Kukulcan maszkja van elrejtve! Vak voltam, de most már látok. Úgy tûnik, eleget tudok ahhoz, hogy megtaláljam Ksocheatemet, a kincseket és magát a Maszkot!";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "Meg akarod menteni a világot, kapitány?";
			link.l1 = "Meg akarom találni a tékozló testvéremet... Gino, hogyan érhetem el, hogy az Igazság Ôre megmutassa a sziget helyét? Azt mondtad, hogy tudod, hogyan!";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "Ismerem a módszert, de a részleteket nem tudom. Nem tudok segíteni neked, amíg nem rendelkezem az Ôrzô összes alkatrészével.";
			link.l1 = "Hm. A tôr már megvan. Már csak az iránytû és a térkép van hátra. Calhounnál van az iránytû, Vincento atyánál pedig a térkép...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "Visszatérsz az inkvizítorhoz? De hogyan fogsz jelentést tenni...";
			link.l1 = "Meg kell gyôznöm Vincento atyát, hogy meghaltál, Gino. Csak akkor hagyja abba a keresést. Tegyük fel, hogy hirtelen agyvérzést kaptál, amikor megláttál engem. Adnod kell egy tárgyat, amit bizonyítékként használhatok a halálodra.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "Vincento nem fog hinni a szívrohamos verzióban, de hinni fog neked, ha azt mondod neki, hogy öngyilkos lettem, mert valami mandulaillatú mérget ittam. Add oda neki az almanachomat, tudja, hogy sosem válok meg tôle.";
			link.l1 = "Rendben. Mert szükségem van arra a kapcsolatra az inkvizítorral. Valószínûleg sokat tud az üzletünkrôl.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "Légy óvatos Vincento atyával. Veszélyes, mint egy tigris, és a saját játékát ûzi. Nem osztja meg veled sem a kincseket, sem a hírnevét.";
			link.l1 = "Ezt megértem. Rendben, Gino, add ide az almanachodat, és próbálj meg emlékezni arra, amit az indián mondott neked az Igazság Ôrzôjérôl, mert össze akarom rakni. Meg kell találnom Ksocheatemet, biztos vagyok benne, hogy ott nemcsak a maszkot és a kincseket találom meg, hanem a drága testvéremet is.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "Fogd meg. Sok szerencsét, kapitány!";
			link.l1 = "Nem búcsúzom el tôled, Gino...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("Kaptál egy almanachot");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "Nehéz volt, kapitány?";
			link.l1 = "Ne beszéljünk róla... Túl sokan haltak meg azért, hogy megszerezzék ezeket a tárgyakat. Túl sokan. Úgy tûnik, nem én vagyok az egyetlen, aki alig várja, hogy megtalálja a titokzatos Ksocheatemet. ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "El tudom képzelni... Egyébként, hogy van Vincento atya? Rendszeresen kommunikálsz vele?";
			link.l1 = "Eddig igen, de azt hiszem, erre már nincs szükség. Az Igazság Ôrének minden alkotóeleme az enyém, ami azt jelenti, hogy birtokomban van a kulcs Ksocheatem helyéhez. Valamiért nem szívesen jelentem a sikeremet Ôkegyelmességének.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "Légy óvatos, "+pchar.name+". Vincento atyának több száz szeme és keze van. Nagyon hosszú kezei...";
			link.l1 = "Sok mindenen mentem keresztül az elmúlt hónapokban, és most már biztosan nem félek, sem Vincento atyától, sem a szemeitôl és a kezeitôl. Mindegy. Itt az ideje, hogy megtaláljuk Ksocheatemet az Ôrzô összetevôinek segítségével. Tudod, hogyan kell ezt végrehajtani? ";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "Nem igazán. Ksatl Cha elég homályosan fogalmazott. Azt hiszem, az indián nem igazán tudta, hogyan kell az Ôrzôt mûködésre bírni. Bízza rám az alkatrészeket, és megpróbálom kitalálni. Jöjjön el hozzám két nap múlva, és talán megoldom ezt a rejtélyt.";
			link.l1 = "Rendben, Gino. Számítok rád. Tessék, fogd ôket.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "Biztos lehetsz benne, hogy biztonságban és egyben maradnak nálam.";
			link.l1 = "Ebben nem kételkedem. Nos, egyelôre nem zavarlak, Gino. Sok sikert a kutatáshoz!";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "Részben. Úgy értem, van valamim, de nem tudom, hogyan lehet az egészet valósággá tenni. Próbáljuk meg együtt megoldani ezt a rejtvényt.";
			link.l1 = "Próbáljuk meg! Mondd el az ötleteidet!";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Ksatl Cha valami ilyesmit mondott: 'A fônök karma feltárja a térképet. Az Út nyila megmutatja a megjelenések irányát.";
			link.l1 = "És mit sikerült elérned?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Kitaláltam, hogyan lehet a térképet 'feltárni'. Megnézted már a Két megjelenés térképét?";
			link.l1 = "Hm. És volt valami különleges? A szigetvilág néhány homályos körvonala...";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "Vegye el, és nézze meg újra. Légy figyelmes.";
			link.l1 = "Nos, tegyük meg, ha ragaszkodik hozzá.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "Nem nézted meg a térképet, "+pchar.name+"...";
			link.l1 = "Igen-igen, most már megteszem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "Megnéztem. Nem láttam semmi újat. Csak néhány homályos szigetet és a fôfolyót. Mit kellene ott látnom?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Várj egy pillanatot. Most már el kell érned, hogy ez a térkép felfedje magát. Fogd a tôrt, és simítsd meg a térképet az élével. Ne nyomd, el kell kerülnünk minden sérülést. Fogd a tôrt. És vigyázz rá alaposan!";
			link.l1 = "Érdekes! Lássuk csak...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "Nos, látsz már különbséget?";
			link.l1 = "Igen. Amikor megérinted a térképet a tôrrel, két koponya jel jelenik meg, és mindig ugyanazon a helyen vannak...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Ugyanazon a KÉT helyen, "+pchar.name+"! Ezért nevezték el a Két Megjelenés Térképének!";
			link.l1 = "És mit jelent ez?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Azt hiszem, sokat... De még több rejtvény következik. Gondolom, ezek a koponyák azok a megjelenések, amelyekrôl Ksatl Cha beszélt. Tehát az iránytûnek kell megmutatnia a helyes irányt Ksocheatem felé tôlük. Láttad már az iránytût, "+pchar.name+"?";
			link.l1 = "Igen. Úgy néz ki, mint egy közönséges tengeri iránytû, de furcsán viselkedik, a nyila különbözô irányokba rángatózik, vagy vad sebességgel kezd el forogni.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Arra gondoltam, hogy az iránytût a koponyákra helyezve megállítja a nyilát, és valami világos irányt fog mutatni a térképen. Ehhez az egyik koponyára, majd a másikra ültettem, miközben a tôrrel megérintettem a térképet.";
			link.l1 = "És?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "Gyümölcstelenül. Az iránytû nem változtatta meg a viselkedését. A nyíl még mindig vadul forog. Úgy tûnik, hogy valamit rosszul csinálok. Vagy nem jól értettem Ksatl Cha szavait.";
			link.l1 = "Tehát a tôr és a térkép mûködik, az iránytû viszont nem?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "Az Út Nyilának biztosan mûködôképesnek kell lennie, csak még nem tudjuk, hogyan kell mûködtetni. "+pchar.name+", te jobban ismered a szigetvilág földrajzát, mint én... Mondd csak, milyen helyeket mutat a két megjelenés térképe?";
			link.l1 = "Egy pillanat! (megnézi)... Nos, nos... A bal oldali megjelenés a nyugati fôút. A jobb oldali úgy néz ki, mint Dominika szigete. Valami ilyesmi.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "És mondd csak: van... valami figyelemre méltó azokon a helyeken?";
			link.l1 = "Hogy érti ezt?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "Magam sem vagyok benne biztos... Nos, valami különleges?";
			link.l1 = "Gino, ne beszélj talányokat. Magyarázd el egyszerûen.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "Csak azt tudom feltételezni, hogy ezek a koponyák valódi helyeket mutatnak nekünk. Az Út Nyila nem mûködik, amíg a térkép megjelenéseire van ültetve. Talán a térkép által felfedett valódi földrajzi helyek közelében fog mûködni?";
			link.l1 = "Gino, te egy zseni vagy! Western Main, Dominika? A koponyák túl nagyok, hogy megmutassák a pontos helyeket.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+", tegyük a következôket: Hozz nekem egy papírtérképet a szigetvilágról, kombináld a Két Megjelenés térképével, és jelöld meg a megjelenéseket keresztekkel. Talán ez ad néhány feltételezést?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Nálam van a szigetvilágnak ez a régi térképe.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Megvan a szigetvilágnak ez a szép térképe.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Van ez a kiváló térképem a szigetvilágról.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Megegyeztünk. Hozok egy térképet, és folytatjuk...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "Ugyan már, "+pchar.name+"! Ez a Kolumbusz idejébôl származó pergamen nem sokkal jobb, mint a bôrtérkép. Biztos vagyok benne, hogy van ennél a szemétnél jobb is a világon. Hozzatok egy másik térképet, egy fiatalabbat!";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "Pompás! Most pedig jelöld be rajta a megjelenések helyét. Ez megkönnyíti a feltételezések felállítását.";
			link.l1 = "Egy pillanat, Gino!";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "Kizárt, hogy egy ilyen csodálatos térképet tönkretegyünk a jelzéseinkkel. Magának is szüksége lesz rá, "+pchar.name+". Hozzatok egy másik térképet, egy kicsit szerényebbet!";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "Hoztál nekem egy térképet a szigetvilágról, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Nálam van a szigetvilágnak ez a régi térképe.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Megvan a szigetvilágnak ez a szép térképe.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Van ez a kiváló térképem a szigetvilágról.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Még nem, de már megrendeltem. Hamarosan megkapom, és folytatjuk...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "Kész... A jelöléseket elkészítettem, de ez még mindig pontatlan információ. Az elsô hely valahol Blueweldtôl északnyugatra van. A második a Dominika sziget közepén van.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "Valami ötlet?";
			link.l1 = "Nincs. De szerintem oda kellene vinnünk az Út Nyilát, és megfigyelni a viselkedését. Persze ez olyan, mint tût keresni a szénakazalban, de jobb ötletünk amúgy sincs.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "Egyetértek veled, "+pchar.name+". Megengeded, hogy veled hajózzak?";
			link.l1 = "Nem akarod ellenôrizni a feltételezéseidet? Megtiszteltetés lenne, ha a hajóm fedélzetén lennél, Gino. Pakolj össze!";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "Nem tart sokáig. Néhány órán belül készen leszek. Tessék, fogd az Út Nyilát.";
			link.l1 = "Üdvözöllek a fedélzeten!";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "Igen-igen, "+pchar.name+", készülök. Hamarosan készen állok.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "Akkor mi van, "+pchar.name+", szerencsések vagyunk a keresésben?";
			link.l1 = "Igazunk volt. Ez az. Az indiai bálvány az egyik megjelenés.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "Ó! Ez biztos az egyik olyan bálvány, ami állítólag teleportálja az embereket Tayasalba! Meséltem neked róluk, emlékszel? Szóval, hová mutat az Út Nyila?";
			link.l1 = "Északnyugatra mutat. Bejelöltem az irányt a térképen. Bár a meghúzott vonal majdnem az egész Karib-tengeren áthalad. Meg kell találnunk egy másik megjelenést Dominikán, hogy megtaláljuk Ksocheatemet.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "Biztos vagyok benne, hogy ott találunk egy másik bálványt... egyetértesz a hipotézisemmel, "+pchar.name+"?";
			link.l1 = "Igen, Gino. Most pedig ne vesztegessük az idôt, és kezdjük el a keresést.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "Na és, "+pchar.name+", találtál valami érdekeset?";
			link.l1 = "Igazunk volt. Ez az. Az indiai bálvány az egyik megjelenés.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "Ó! Ez biztos az egyik olyan bálvány, ami állítólag teleportálja az embereket Tayasalba! Meséltem neked róluk, emlékszel? Szóval, hová mutat az Út Nyila?";
			link.l1 = "Északnyugatra. Bejelöltem az irányt a térképen. Bár a meghúzott vonal majdnem az egész Karib-tengeren áthalad. Egy másik megjelenést kell találnunk a Fônél, hogy megtaláljuk Ksocheatemet.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "Na és, "+pchar.name+", megtaláltad a második bálványt?";
			link.l1 = "Igen. Megrajzoltam az irányt, amit az Út Nyila mutatott. Most már tudjuk Ksocheatem helyét, nem a pontos helyet, de tudjuk, hol kell keresnünk! Átkutatom az egész területet, ahol a vonalak keresztezik egymást, és megtalálom azt az átkozott szigetet!";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "Örülök, hogy ennyi lelkesedést hallok a hangjában. De jól fel kell készülnünk a közelgô expedícióra, nem tudni, mivel fogunk ott találkozni. Kétlem, hogy ott szívélyes fogadtatásban lesz részünk...";
			link.l1 = "Valami konkrét dolog miatt aggódsz, vagy csak aggodalmadat fejezed ki?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "Gondolj bele, "+pchar.name+".. Ksocheatem a Kanek által végzett maja mágia által jött létre. Ez nem egy természetes képzôdmény, és gonosz és pusztító erôk vannak rajta. Nem tudni mi vár ott ránk, kétlem, hogy napsütést, békés tengert, kurvákat és szélcsendet találunk ott.";
			link.l1 = "Rendben, Gino. Megfontolom a szavaidat és felkészülök az expedícióra. Elôkészítem a hajómat, gondoskodom a bájitalokról és a lôszerrôl...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "Nagyon bölcs döntés. Nos, visszatérhetünk a hajóra?";
			link.l1 = "Persze, menjünk vissza a hajóra. Menjünk!";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "Megérkeztünk, "+pchar.name+"! Uh, a szél üvölt!";
			link.l1 = "Igen, Gino, igazad volt, nincs napsütés, hogy üdvözöljön minket... És kurvákat sem látok. Igazából nem tudni, hogy egyáltalán mi vár ránk itt.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "Hát, rossz helyet választott a leszálláshoz, kapitány! Csak sziklák és sziklák mindenütt! És hogy akarnak innen a sziget belsejébe jutni?";
			link.l1 = "Nem láttam más alkalmas öblöt, ahol leszállhatnánk ezen a szigeten, mert ez az átkozott vihar! Mindegy, ez is jobb, mint a semmi. Megtalálom az utat ezeken a sziklákon belül, volt már rosszabb is. Ne ess pánikba, barátom!";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "Nem szeretem ezt a szigetet, "+pchar.name+"! Hátborzongató. És ez a vihar biztosan a szigethez kötôdik. Ez a hely halálra van ítélve, az biztos!";
			link.l1 = "Nekem sem tetszik ez a hely, Gino! De ez a sziget létezik, ami azt jelenti, hogy Kukulcan története igaz. Mindannyian veszélyben leszünk, ha sikerül eljutnia Tayasalba a Maszkkal...";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "Próbálja megtalálni a Maszkot, kapitány! Ez fontosabb, mint a világ összes kincse! Valahol itt kell lennie! Ha egyszer nálunk lesz, elpusztítjuk Kukulcan terveit, és nem hagyjuk, hogy megváltoztassa a múltat!";
			link.l1 = "És hogy néz ki ez a maszk, tudod, hogy néz ki?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "Fogalmam sincs! De szerintem fel fogod ismerni, ez egy ôsi indián lelet, nehéz összekeverni bármi mással!";
			link.l1 = "Értem. Nyitva fogom tartani a szemem! Rendben, Gino, menj vissza a hajóra! Nem kell a szigetet körbejárnod, a fejed túl értékes ahhoz, hogy kockáztass!";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "Nem fogok hazudni, kapitány, pocsék harcos vagyok, és nem érzem jól magam ezen a helyen. Szeretnél tanácsot hallani? Az Ôrzô minden eleme kapcsolódik a sziget mágiájához. Ksatl Cha említette, hogy a tôrnek hatalma van a helyi lakosok felett, bár nem tudom, mire gondolt.\nA fedélzeten maradok. Találkozzunk ott, ha szükségetek van a segítségemre.";
			link.l1 = "Jól van. És most kívánj szerencsét, Gino!";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "Sok sikert, "+pchar.name+"! Isten kegyelmezzen és tartson meg benneteket!";
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "Hogy vagy, "+pchar.name+"? Szüksége van egy tanácsra?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "Ez a kibaszott sziget hemzseg az élôhalottaktól, és azok a rohadt csontvázak meglepôen kemények. Fogalmam sincs, hogyan harcoljak ellenük.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "Ha balra mész az elágazástól, végül eljutsz a barlanghoz. De merre menjek tovább? Attól tartok, hogy a barlang zsákutca...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "Megtaláltam az utat a nedves barlang belsejébe, lemerülhetsz a víz alatti részébe. De nem látok onnan kijáratot...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "Ha az elágazástól balra mész, akkor eljutsz a barlangba. De merre menjek tovább? Attól tartok, hogy a barlang zsákutca...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "A nagy barlangban van egy hely, ahol be lehet merülni az elárasztott részbe. De úgy tûnik, hogy onnan nincs kiút...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "Eddig minden rendben van, Gino, jól vagyok.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "Ksatl Cha említette a Fônök karmait. Próbáld meg használni a csontvázak ellen, az indián azt mondta, hogy ennek a tôrnek hatalma van Ksocheatem lakói felett.";
			link.l1 = "Biztosan megpróbálom!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "És hogy néz ki ez a barlang?";
			link.l1 = "Nos, van egy kis barlang a sziklában, vizes, és a víz úgy ringatózik az alján, mint a hullámzás...";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "Ha a víz ringatózik, akkor a barlangnak van valami kapcsolata a tengerrel, és nem lehet holtág. Keressetek egy átjárót, ott kell lennie.";
			link.l1 = "Útközben...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "Ha a fôbarlangból van út az elárasztott barlangba, és ha a víz úgy ringatózik, mint a fôbarlangban a hullámzás, akkor az elárasztott barlangban van a második átjáró. Kutassátok át jobban, de legyetek óvatosak, különben megfulladtok.";
			link.l1 = "Megyek és lemerülök...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "És hogy néz ki ez a barlang?";
			link.l1 = "Hát elég nagy, néhány barlanggal, vizes és van egy kis lyuk, ahol áll a víz...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "Ha a víz áll, akkor a barlangnak nincs kapcsolata a tengerrel és lehet, hogy zsákutca.";
			link.l1 = "Én is erre gondoltam. Sokáig kerestem ott, és csak egy bejárat van, ami egyben kijárat is...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "Ha a víz még mindig a barlangban van, akkor talán igazad van. Kutass még egy kicsit, de ne szomorkodj, ha nem találsz semmit. Valószínû, hogy ez egy zsákutca.";
			link.l1 = "Értem...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", a spanyol hajók a nyomunkban vannak! Ez nem a legjobb idôpont a beszélgetésre!";
			link.l1 = "Igen, persze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "Boldog szemed azt mondja, hogy megtaláltad, amit kerestél.";
			link.l1 = "Igen. Miguel Dichoso kincsei és Kukulcan maszkja. Most már a megtestesülése soha nem lesz képes megváltoztatni a jövôt!";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "Hihetetlen! Ön egy hôs, "+pchar.name+"...";
			link.l1 = "Gino, biztos vagy benne, hogy ez elég ahhoz, hogy megállítsuk Kukulcant?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "Ksatl Cha szerint igen. És ô Urakant idézte. Az apja, Kanek volt az, aki ezt az egészet elkezdte. Kétségek?";
			link.l1 = "Az öbölben találkoztam egy vendéggel a múltból - Alonso de Maldonado. Tayasalban volt, amikor Kanek elvégezte a rituálét az Igazság Ôrének létrehozására. Belerángatták a tér-idô lyukba, mégis életben maradt... Egészen a mai napig.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "Azt mondta, hogy le kell zárnom magát a portált, hogy végleg megvédjem a világunkat. Ehhez el kell pusztítanom a maszkot egy oltáron Tayasalban.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "És te Tayasalba mész? Ez ôrület! "+pchar.name+", nálad van a maszk és Kukulcan inkarnációja nem fog tudni mit csinálni! És ebben maga Kanek is biztos! Ezért küldte Urakan Ksatl Cha-t, hogy megtalálja Ksocheatemet - hogy megszerezze a maszkot és elpusztítsa.";
			link.l1 = "És mi van, ha ez az Urakan azt tervezte, hogy elpusztítja a maszkot Tayasalban?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+", eddig csak egy embernek sikerült élve elmenekülnie Tayasalból, és az Miguel Dichoso volt. Maldonado is, de ô kivétel volt. Még ha Kukulcan megtestesülése el is jut a múltba, az ôsi maják meg fogják ölni!";
			link.l1 = "Mi van, ha nem ölik meg, hanem felismerik?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "Szóval terveztek egy expedíciót Tayasalba?";
			link.l1 = "Nem tudom, Gino. Tényleg nem tudom...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "Akkor gondolkodj el rajta, miért tennéd ezt? Hallottad a véleményemet. Most már csak rajtad múlik..."+pchar.name+", elviszel a Szent Jánosba?";
			link.l1 = "Persze, Gino. Induljunk minél hamarabb. Elegem van ebbôl a szörnyû szigetbôl.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "Hamarosan hazaérünk, "+pchar.name+"? Nagyon hiányoznak a lombikjaim és a csöveim...";
			link.l1 = "Igen-igen, Gino, hamarosan Antiguán leszünk.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "Örülök, hogy végre itthon vagyunk! El sem tudom képzelni, hogy ti, tengerészek, hogy tudtok ennyi idôt eltölteni a hajóitokon...";
			link.l1 = "Ez szokás kérdése, Gino.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "Nagy örömmel fekszem majd az ágyamon, szilárd talajon állva... Remélem, "+pchar.name+", hogy megkímélte a fejét a Tayasal meglátogatásának gondolatától?";
			link.l1 = "Még nem tudom, Gino. Hogy ôszinte legyek, még mindig nem vagyok benne biztos.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "Pusztítsd el Kukulcan maszkját és élj gondtalanul, kapitány. Ha akarod, feloldjuk a maszkot a legerôsebb savban, amim csak van. Nem fogok haragudni egy ilyen ügy miatt.";
			link.l1 = "Tudod, én még várok egy kicsit. Mindig lesz idônk elpusztítani.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "A te döntésed. Ha úgy döntesz, hogy megkíméled ezt a világot ettôl a leletektôl - gyere hozzám. Köszönöm a csodálatos utazást, kapitány!";
			link.l1 = "Bármikor, Gino. Viszlát!";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Maga egy "+ GetSexPhrase("tolvaj, uram! Ôrök, vigyétek","tolvajt, lány! Ôrök, vigyétek ") +"!!!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat! Vigyétek a tolvajt!!!", "Ôrség! Rablás! Elkapni a tolvajt!!!");
			link.l1 = "A francba!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
