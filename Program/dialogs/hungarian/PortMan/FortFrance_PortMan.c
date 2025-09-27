// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Már próbáltál kérdezni " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Nézze, ha nincs mondanivalója a kikötô ügyeirôl, akkor ne zavarjon a kérdéseivel.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam.", "Nincs mirôl beszélnem."), "Nevermind.", "Valóban, már harmadszor...", "Sajnálom, de egyelôre nem érdekelnek a kikötô ügyei.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "Uram, állást keresek. De nem hordárnak, hanem valami olyat, ami jobban megfelel a rangomnak. Küldetés, szolgálat, kényes ügyekkel... Bármilyen megbízást elvállalok.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "Azt mondták, hogy levelet hoztál nekem. A neve Charles de Maure kapitány.";
			link.l1.go = "LH_letter";
		}
		break;
		
		case "Sharlie":
			dialog.text = "Segítség? Hm. Jól vagyok, hála Istennek. De az egyik barátomnak nagyon nagy szüksége van segítségre, és sürgôs. Egyedül akar bemenni a dzsungelbe, hogy harcoljon az indiánokkal, ez teljes ôrület!\nPróbáltam jobb belátásra bírni, könyörögtem neki, de nem hallgatott rám! Túlságosan aggódik a lányáért, és kész az életét adni érte!";
			link.l1 = "Várj, kezdjük elölrôl: ki a barátod, hol találom meg, és milyen segítségre van szüksége?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Ah, bocsásson meg, csak túlságosan nyugtalan vagyok. A neve Prosper... Prosper Troubale. Biztosan meg fog halni! És én nem tudok segíteni rajta - nem vagyok katona. A lánya eltûnt, és úgy véli, hogy a helyi indiánok a felelôsek\nKépzelje el, egyedül akar a vademberek után menni! Darabokra fogják vágni ôt... Ebben a pillanatban éppen muskétát vásárol, és készülôdik, hogy kimegy a szelavába!";
			link.l1 = "Maga egy szerencsétlen mesélô, uram. Hol találom a barátodat... hogy is hívták... Prosper?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "Éppen most beszéltem vele, és próbáltam rávenni, hogy meggondolja magát. Nem messze a városkaputól, a kútnál van, a muskétáját és a lôszerét ellenôrzi. Menjetek oda hozzá, és tegyetek valamit! Ha egyedül megy a dzsungelbe, nem fog visszajönni, ebben biztos vagyok. A vörösbôrû ördögök darabokra fogják tépni...";
			link.l1 = "Hagyd abba a fecsegést, úgy beszélsz, mint egy vénasszony! Azonnal a barátodhoz megyek. Remélem, hogy tudok majd segíteni neki.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "Igen, igazad van - van egy boríték. Itt van, de elôbb ki kell fizetnie a küldeményt - tizenkétezer ezüstpezót.";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "Mindig is gyanítottam, hogy a kereskedésed eredetileg tolvaj' business volt, de valahogy lemaradtam a levélrôl, hm. Kérem, itt van a pénze.";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "Kicsit késôbb visszajövök, azt hiszem, a kocsmában hagytam az erszényemet.";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
