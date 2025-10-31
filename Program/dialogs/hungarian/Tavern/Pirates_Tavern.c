// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Nemrég próbáltál feltenni nekem néhány kérdést, " + GetAddress_Form(NPChar) + "...", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz...",
                          "További kérdések, gondolom?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Igen, ez tényleg a harmadik alkalom...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "Figyelj, "+npchar.name+", hallottál valamit egy Miguel Dichoso nevû emberrôl? Azt mondják, hogy a hajóját látták Isla Tesoro vizein belül...";
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Figyelj, "+npchar.name+", nem láttad mostanában Miguel Dichosót az Isla Tesorón?";
				link.l1.go = "tieyasal";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Igen, láttam. Az a spanyol don eladott Shark Dodson-nak egy figyelemre méltó hajót, egy fregattot, amikor még itt lakott. Á, az a hajó... Hihetetlenül jó volt...";
			link.l1 = "Hadd találjam ki: modern, elegáns vázzal rendelkezett, és tizenhat csomó elérésére volt képes? És a neve 'Santa Quitaria'?volt.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ami a keretet és a sebességet illeti, teljesen igazad van, de más neve volt: 'San Martin'. Shark egy rakás aranyat fizetett annak a gazembernek azért a hajóért.";
			link.l1 = "Biztos, hogy 'San Martin' és nem 'Santa Quiteria'? Mikor vette? És miért nevezte Dichosót gazembernek?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "A fenébe a szememmel, teljesen biztos vagyok benne, hogy ez 'San Martin', volt, mert személyesen láttam, ahogy Alexus munkásai tányért téptek le a tatról azzal a pápista hülyeséggel. Shark Dodson nevezte el 'Fortune', sokkal alkalmasabb név egy ilyen szépségnek. (spits) télen vásárolta '54, nem sokkal Blaze meggyilkolása elôtt\nMiért neveztem Don Miguelt gazembernek? Mert a Gondviselésbôl ellopta azt az átkozott hajót a spanyol haditengerészettôl! Dodson tûzzel és füsttel elôadást rendezett St. Juan erôdjének és helyôrségének, ahogy mindig mesélte, amikor részegen volt. Cápa feláldozott két sérült luggert, hogy a fregattal vívott harc valódi\nhogy az éjszaka beálltával titokban elhajózott 'San Martin' az Isla Tesoróra. A Cápa megszerezte a hajót, Dichoso pedig a pénzt. Ravasz fattyú késôbb azt mondta a feljebbvalóinak, hogy a fregatt elsüllyedt a kalózflottával vívott harc során, St. Juan erôdparancsnoka megerôsítette ezt.";
			link.l1 = "Ó, hogy azok a spanyol dónok hogyan tömik a zsebüket! Micsoda csaló! Mondja, biztos benne, hogy ez 1654 telén történt? Lehet, hogy tavasszal történt? És a fregatt nem mutatta a vihar okozta kopás jeleit?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Biztos vagyok benne, hogy télen volt... Ó, ki tudja. Talán tavasz volt. Nem emlékszem biztosan. Valószínûleg részeg voltam. A fregatt egyáltalán nem volt kopott, pedig vadonatúj volt.";
			link.l1 = "És hol van most az a gyönyörû fregatt?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Egy sötét történet, ez... Amikor Blaze-t meggyilkolták, mindenki Cápára gyanakodott, mert a nyakláncát, egy cápafogat találtak a holttesten. Ráadásul néhányan látták Sharkot Blaze lakásában azon az éjszakán\nShark megszökött Isla Tesoróból, mielôtt fekete jelet adtak volna neki. Meglátogatta Dark Pastort, és elcserélte a fregattját egy briggre. Fogalmam sincs, hol lehet most a férfi. Zachary késôbb eladta a fregattot William Patersonnak.";
			link.l1 = "Ki ez a Paterson?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Mi az, még sosem hallottál Willie Patersonról? Ô egy skót, aki most érkezett a Karib-tengerre. A királyi flotta kapitányának tartja magát, maga Fox ezredes kedvence! Mellesleg, most kezdett el Jackmannel is üzletelni. Pattersons flagship is 'Fortune' herself.";
			link.l1 = "Értem. Tudja, hol van most Dichoso?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Fogalmam sincs. A 'Fortune' val való bohóckodás után azóta nem láttam az Isla Tesorón, és nem hallottam róla semmit.";
			link.l1 = "Rendben, "+npchar.name+", köszönöm a részletes tájékoztatást! Kiváló kocsmáros vagy! Bárcsak több ilyen ember lenne, mint te... Viszlát!";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Sok sikert, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "Úgy tûnik, mintha mindketten egymást kergetnétek, haver. Igen, Dichoso pont itt volt, ahol most állsz. És pontosan úgy, ahogyan rólad kérdezôsködött, amikor legutóbb Sharptownban jártál.";
			link.l1 = "A francba! Ez a hír... És hol van most Miguel?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Fogalmam sincs. Elment a tengerre, ahol... mondott valamit Blueweldrôl. Valószínûleg csak téged keresett.";
			link.l1 = "Véletlenül nem te küldted ôt Blueweldbe?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Nem. Csak annyit mondtam neki, hogy már régóta nem láttam magát.";
			link.l1 = "Értem. Rendben, akkor. Kösz, haver!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
