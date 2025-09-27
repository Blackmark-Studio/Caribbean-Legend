// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hogyan segíthetek Önnek?", "Mit tehetek önért?"), "Mondja el, mi bántja, " + GetAddress_Form(NPChar) + "?", "Harmadszorra, " + GetAddress_Form(NPChar) + ", mire van szüksége?", "Elegem van belôled. Takarodj innen!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam, elnézést kérek.", "Semmiség, elnézést."), "Bocsáss meg, ez semmiség.",
                      "Igazad van, ez már a harmadik alkalom. Bocsáss meg...", "Apologies.", npchar, Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Figyeljen, látott vagy találkozott egy Joachim Merriman nevû férfival, itt Havannában vagy a környékén? Ô egy középkorú senor, portugál, bajusszal, császári szakállal és szúrós szemekkel. Talán egy öbölben vagy a dzsungelben? Ôt keresem.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Nem, tengerész, biztosan nem. Ritkán kapok látogatókat idelent, tudja... és én... Nem láttam még senkit, aki olyan lenne, mint az a férfi, akit leírt, szóval...";
			link.l1 = "Tényleg? Akkor miért dadog és miért rejtegeti a szemét? Ne hazudjon nekem, tudja az igazat. Jobb, ha megismétli - látta azt a férfit?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Én-én mondom önnek, Senor, nem láttam senkit! Gyerekkorom óta dadogok...";
			link.l1 = "Hazugság, csupa hazugság. Látom a szemében. Hol van, hol van Merriman?! Mondja meg, MOST!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Nem ismerek semmilyen Merrimant! Ezt a nevet sem hallottam még soha! És ne próbálj bántani, vagy a parancsnok felakaszt az erôdben! Szóval óvatosan, fiú!";
			link.l1 = "Ó, azt hiszi? Jól van, rendben. Most pedig jól figyeljen rám: Joachim Merriman egy boszorkánymester. A Szent Inkvizíció keresi ôt. Sok évvel ezelôtt Európában máglyahalálra ítélték sírásásért, halottgyalázásért és boszorkányságért. És biztosan tudom, hogy most valahol itt bujkál, Havanna külvárosában...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "...nemrég megtisztítottam a közeli barlangot a zombiktól, és tudom, ki a felelôs! Bizonyára Merriman hova máshova menne, ha nem a temetôbe! Tudod, hogy hol van. De legyen, ahogy akarod, én egy ujjal sem nyúlok hozzád, de meglátogatom a santiagói inkvizítorokat. Vincento atya nagyon érdekesnek fogja találni, hogy Joachim Merriman a havannai temetôben bujkál a cinkosával, a helyi ôrrel...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "...Máris elszállt a szín az arcodról? Egy nemesember szavát adom: Egy nappal azután, hogy jelentem az eredményeimet, az egész sziget hemzsegni fog a spanyol katonáktól. Téged pedig addig fognak kínpadra feszíteni, könyörögve és sírva, amíg el nem árulod, hol rejtôzik az a varázsló. Legkésôbb máglyán égetnek el, mint a bûntársát, miközben én az autodaféra vigyázok. Hogy tetszene ez neked?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Kérem, senor! Esküszöm, hogy nem veszek részt ebben az egészben! I... Én csak nem tehettem semmit... Hogy állhattam volna ellene?! Ô egy szörnyû ember, képes... fogalma sincs, mire képes! Kegyelem, könyörgöm!";
			link.l1 = "Bízz bennem, tudom, mire képes. A saját szememmel láttam. És? Hol van? Mondja el, és ígérem, hogy nem keverem bele magát ebbe az ügybe.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Ô... Egy barlangban rejtôzik a temetô alatt. Oda csak a kápolna ajtaján keresztül lehet bejutni. Amikor kimegy, én elbújok a házamban, és ott ülök. Fogalmad sincs, mennyire szeretnék megszabadulni ettôl a borzalomtól!\nDe még csak megközelíteni sem merem. I... Láttam, ahogy friss sírt ásott, és aztán... aztán a halott feltámadt, és a holdfényben sétálgatott a temetôben! Akkor majdnem elvesztettem a józan eszemet! De Merriman megtiltotta, hogy elmenjek. Megfenyegetett, hogy ha az engedélye nélkül akár csak egy fél napra is elhagyom a házamat, megtalálja és átváltoztat engem abba a förtelembe... egy két lábon járó csontvázzá!";
			link.l1 = "Milyen gyakran hagyja el a barlangját?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Nos, ételt és gyógyító italt hozok neki a városból, és... bármi mást, amit kér. Havonta egyszer vagy kétszer megy el... amikor telihold van. Hagy egy üzenetet az ajtón, megírja, hogy mire van szüksége... Én elhozom, és kiteszem az ajtó elé, ô pedig elviszi, ha visszatért.";
			link.l1 = "Értem. Az az ajtó a búvóhelyéhez - be van zárva valahogyan?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "Igen. Mindig zárva van. Nagyon erôs, a zár pedig masszív és bonyolult.";
			link.l1 = "Hm... Merriman nem bolond, biztosan van egy másik kijárata is a búvóhelyérôl, mint az európai háza. Ha feltörnénk az ajtót, elszökne, és soha többé nem találnánk meg. Hmmm...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Senor, megesküszik, hogy nem ad fel az inkvizíciónak?";
			link.l1 = "A szavamat adtam, és egy nemes szava szent. Esküszöm, hogy nem adom fel.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Ó, áldja meg, Senor! Tudom, hogy jutok el a barlanghoz. Van egy kulcs, egy második kulcs... Nálam van. Merriman nem tudja, hogy két kulcs van ahhoz a zárhoz. Én soha nem mernék bemenni, de maga...";
			link.l1 = "Add ide a kulcsot, és megszabadítalak ettôl a rémálomtól.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Tessék, Senor. Komolyan bemegy a búvóhelyére?";
			link.l1 = "Igen. Zárkózzon be a házába, és várjon ott, amikor bemegyek. Ha nem térek vissza, hagyjon ott mindent, és fusson, amilyen gyorsan csak tud.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "De legyen óvatos, Senor. Ijesztô hangokat hallottam a barlangjából, és még belegondolni is félek, hogy ki lakhat benne. De Merriman nincs egyedül - ez biztos.";
			link.l1 = "Minden tôlem telhetôt megteszek. Viszontlátásra.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
