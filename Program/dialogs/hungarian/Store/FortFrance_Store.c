// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Gyerünk, mit akarsz?",
                          "Épp errôl beszéltünk. Biztos elfelejtetted...", "Ma már harmadszor beszélsz valami kérdésrôl...",
                          "Figyelj, ez egy bolt. Az emberek itt vásárolnak. Ne zavarjon!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Hm, nem fogom...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Figyeljen, uram, munkát keresek. Nem fôállású munkát vagy zsákos rakományt cipelô munkát, hanem inkább úgymond megbízásokat teljesítek. Szüksége van véletlenül segítségre?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "Elvégeztem a küldetését. Megtaláltam Gralam Lavoie-t.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Bemutatom az új asszisztensét, monsieur.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "Megint én vagyok, uram. A jutalmamért jöttem.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Nézze meg ezeket a fülbevalókat, uram. Egy bandita testén találtam, akit a dzsungelben öltek meg. Ez egyértelmûen egy olyan ékszerész munkája, aki biztos vagyok benne, hogy nem idevalósi. Tud valamit mondani ezekrôl a fülbevalókról?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "Elnézést, uram, de hol van a kardja? Nem biztonságos elhagyni a várost pengés fegyver nélkül. Sosem tudhatod, mi történhet a dzsungelben!";
				link.l1 = "A fenébe, teljesen elfelejtettem! Mindent elvittek!";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "Munkát? Hm. Azt hiszem, van egy munkám, amit talán szeretnél. Az asszisztensem eltûnt, a raktáramban dolgozott. Már egy hete eltûnt, és ez rohadtul bosszantó, mert kénytelen vagyok elvégezni a feladatait, és nincs idôm\nKérem, keresse meg ezt az idiótát, és derítse ki, mi a fenéért hagyta ott a munkáját. Vagy még jobb - hozzátok vissza hozzám. Fizetek neked ezer darab pesot.";
			link.l1 = "Rendben, benne vagyok. Mondd meg a nevét és írd le a kinézetét. Van valami ötleted, hogy hol keressük?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Keressek egy embert Isten tudja hol egy vacak ezresért? Ez csak vicc lehet!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hé, monsieur. Ki keres munkát, maga vagy én? Ha nem akarja, nem kényszerítem. Szép napot!";
			link.l1 = "Hm... Azt hiszem, megnézem a kikötôi hatóságot; talán ott valami komolyabbat tudnak ajánlani.";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "A nevem Gralam Lavois. A külseje? Harmincöt éves, szakáll és bajusz, hosszú barna kabát, fehér ing. Ó, és mindig azt a hülye, kakasos kalapot viseli, admirálisnak tetteti magát, horgonnyal a seggében\nNincs St. Pierre-ben, az egész várost ellenôriztem. Biztos a dzsungelben van, vagy Les Francois-ban bujkál a kalózok között, akik ott ólálkodnak.\nAztán megint csak valószínû, hogy Le Francois kalóztelepülésén van, ami a szigetünk keleti részén van. Talán éppen az ottani kalózokkal beszélget, vagy a tavernában tölti az idejét, esetleg a helyi kereskedôvel vitatkozik a boltban.\nHogyan juthatunk el Le Francoisba? Menj ki a városkapun át a dzsungelbe, a keresztezôdésnél menj balra az ösvényen, majd kövesd az utat, amíg jobbra nem fordulsz, majd a sziklák között balra az átjárón, és máris megtalálod Le Francois-t. Nem hiszem, hogy el fogsz tévedni.";
			link.l1 = "Rendben. Majd én megkeresem. Amint kiderül valami, azonnal értesítelek.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "Tényleg? És hol van?";
			link.l1 = "Megtaláltam Le Francois-ban. Nem fog többé neked dolgozni. Ráadásul egy csomó eléggé sós dolgot mondott rólad... Szeretné hallani?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "Nem. Kíméljen meg a részletektôl... Milyen kár! Mit fogok most csinálni asszisztens nélkül?";
			link.l1 = "Béreljen fel valaki mást. Vagy ez tényleg olyan nagy probléma, mint ahogy Gralam mondta?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Szerencsétlenség, valóban. És mit mondott az a csavargó?";
			link.l1 = "Nos, elôször is, nyilvánvalóan nem vesztegeti az idejét, he-he. Azt mondta, hogy egész Saint Pierre-ben senki sem jelentkezne önöknél szolgálatra, mert... nem fizetnek eleget a munkásaiknak. Igen, egyébként, "+npchar.name+", tartozik ezer pezóval, ahogy ígérte.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Kérem, vegye el a pénzét. Ha! Ne fizessetek eleget! Persze, senki sem akar nekem dolgozni. A fattyú mindent megtett, hogy mocskos beszédeket terjesszen. Mit tehetnék? Nem tudok mindent egyedül csinálni!\nNem tudok elaludni, amíg meg nem számolok minden rakományt, mert azok az átkozott munkások mindig ellopnak valamennyit. A legutóbbi rakodás után öt hordó rum hiányzik. Biztos vagyok benne, hogy a munkások 'tévedésbôl' rabolták el...";
			link.l1 = "Hát, nem tudom, mit tanácsoljak. Rendben, minden jót. Ideje mennem.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Várj! Azt hiszem, tudsz nekem segíteni. Ha képes voltál megkeresni azt a szemetet, akkor talán te is képes lennél...";
			link.l1 = "És vajon mit tudnék tenni, ha ebben a városban senki sem hisz neked? Új vagyok itt és...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Hadd fejezzem be, uram. Ön Le Francois-ban volt. Szeretném, ha újra odamennél, és megpróbálnál találni nekem egy alkalmazottat. Talán Gralam nem tette teljesen tönkre a hírnevemet ebben a kalózbarlangban\nA munka egyszerû - számolja meg a rakományt, és vigyázzon a kikötôi munkásokra, hogy megakadályozza a lopást. Néha elvégzik helyettem a munkát itt, amíg távol vagyok, persze külön díjért\nmondja meg nekik, hogy egy szobát kínálok a boltban lakhatásra és heti ötszáz darab pesot. Monsieur, bôvíteni akartam az üzletemet, és végre jól mennek a dolgok, szükségem van egy segédre!\nApropó, a legjobb, ha a helyi kocsmárostól, Cesare Craigtôl kér segítséget a munkáskeresésben. Ez a gazember biztosan segít nektek, ha nem is ingyen, hogy olyan személyeket találjatok, akiket érdekelne, hogy nekem dolgozzanak.";
			link.l1 = "Hm. Megpróbálhatom, bár nem vagyok benne biztos... Mennyit fizetne nekem a munkáért?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "Ez attól függ, hogy milyen munkást tud felvenni. Minél jobbnak bizonyul, annál többet fizetek az erôfeszítéseidért. Ez igazságos, nem?";
			link.l1 = "Nem gondolja, hogy arra kényszerít, hogy vakon lovagoljak? Honnan tudjam, hogyan fogod értékelni a munkást? Bárkit besorolhatsz rossznak vagy...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Monsieur! Talán helyes, ha egy kicsit fukarnak neveznek, de tisztességtelennek senki sem nevezhet! Ha azt mondom, hogy a munkájáért fizetek, attól függôen, hogy mi lesz a vége, akkor komolyan gondolom. Nézze az én szemszögembôl is. Lehet, hogy csak úgy idehozol nekem valami lusta cigányt, aki nemhogy lógna és nem csinálna semmit, de még esetleg éjjel ki is rabolna!";
			link.l1 = "Rendben. Egyetértek. Elhiszem a szavát, "+npchar.name+". Biztos leszek benne, hogy nem hozok vissza cigányokat.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Vissza Le Francois-hoz...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "Találtál nekem egy munkást? Csodálatos. Engedje meg, hogy beszéljek vele, és egy óra múlva jöjjön vissza a jutalmáért.";
			link.l1 = "Rendben. Egy óra múlva visszajövök.";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("Egy óra telt el...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "Elégedett vagyok a munkással, akit találtál nekem, bár többet beszél, mint amennyit jár, de ne aggódj, egy idô után ki fogom verni belôle a fecsegést. A jutalmad nyolcezer darab. Tessék, tessék.";
					link.l1 = "Köszönöm szépen! Mondja, uram, nem tudja, hogy a városban van-e még valakinek szüksége segítségre valami fontos ügyben?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "Sikerült egy igazán értékes munkást találnia! Még annál a gazember Gralamnál is jobb. Nagyon, nagyon örülök, uram. Tessék, itt a jutalmad - nyolcezer darab.";
					link.l1 = "Köszönöm szépen! Mondja, uram, nem tudja, hogy a városban van-e még valakinek szüksége segítségre valami fontos ügyben?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "Találtál egy jó munkást. És bár nem ismeri a szakma minden csínját-bínját, biztos vagyok benne, hogy minden gond nélkül elsajátítja. Elégedett vagyok magával, uram. Tessék, vegye el a jutalmát - négyezer nyolcezret.";
					link.l1 = "Köszönöm szépen! Mondja, uram, nem tudja, hogy a városban van-e még valakinek szüksége segítségre valami fontos ügyben?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hmm... Nemrég láttam a kikötômestert, aki szemmel láthatóan feldúltan a kikötôi hatóság felé tartott. Nézzen utána, ki tudja, mi történhetett.";
			link.l1 = "Majd én megteszem. Köszönöm, uram.";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Nos, mit is mondhatnék, csodálatos fülbevaló. Adhatok érte... lássuk csak... négyezer nyolcezret. Kétlem, hogy bárki is többet ajánlana. Megegyeztünk?";
			link.l1 = "Áll az alku! A magáé.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Nem. Azt hiszem, inkább magamra hagyom ezeket az ékszereket.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("Odaadtad a fülbevalót");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "Az nem fog menni. Azt javaslom, forduljon a kormányzóhoz, és kérje a segítségét.";
			link.l1 = "Köszönöm a tanácsot. Ezt fogom tenni.";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}
