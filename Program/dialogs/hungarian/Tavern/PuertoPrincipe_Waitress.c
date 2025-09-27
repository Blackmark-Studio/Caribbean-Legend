// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Kérdések, " + GetAddress_Form(NPChar) + "?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hm, mi a nagy ötlet, " + GetAddress_Form(NPChar) + "? ","Már megint a furcsa kérdések? Toots, menj, igyál egy kis rumot vagy valamit...") +"", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz..."+ GetSexPhrase(" Ezek a figyelem jelei?","") +"",
                          "További kérdések, gondolom, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam", "Jelenleg nincs mirôl beszélnem."), "Nem, nem szép...",
                      "Szó sem lehet róla, kedvesem...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "Fel kell tennem néhány kérdést. A kocsmában dolgozott aznap, amikor a gines hordó eltûnt, ugye? Mit tud nekem mondani az aznapi eseményekrôl?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "I... Nem tudom, mit mondjak. Minden normális volt, semmi szokatlan.";
			link.l1 = "Valóban? Semmi különös? Mi a helyzet azzal a tengerésszel a 'Sea Beast' , aki zaklatott téged? Úgy tûnt, meg volt gyôzôdve róla, hogy szívesen látná a társaságát az éjszakára.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "Ó, ô! Ô... csak egy cseppet túl sokat ivott, ez minden. Tudja, ez elég gyakran megtörténik itt. Nem bátorítottam, de elkezdett közeledni. Így hát a helyére tettem.";
			link.l1 = "Nem bátorítottad? Ô másképp mesél. Most miért keltett ekkora felhajtást, de máskor miért nem?";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "I... Nem tudom, mit mondhatnék még! Tényleg nem tudok semmit! Én csak... Egész este szem elôtt voltam! Nem láttam semmit, nem hallottam semmit! És a hordóról... Nem tudom, mi történt vele! Miért ez a kihallgatás? Én csak... csak a munkámat végeztem, mint mindig!";
			link.l1 = "Gyanítom, hogy visszatartja magát. Egy éjszaka a hajó rakterében fény és étel nélkül csodákat mûvel az ember memóriájával. Kíváncsi rá? Vagy beszélgessünk inkább rendesen?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "Azt hiszem, sokkal többet tud, mint amennyit elárul. Ritka lehetôséged van most - mondj el mindent, és én megtartom magamnak a szerepedet ebben a kis színdarabban. De ha hallgatsz, az még rosszabb lesz neked. A segítségeddel vagy nélküled is kiderítem az igazságot.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "I... I... Mindent elmondok neked! Az egész az én... udvarlóm volt, Jack. Jack Veils! Ô gyôzködött, hogy csábítsak el bármelyik tengerészt a 'Sea Beast'. És amikor ô közeledne, nekem kellett jelenetet rendeznem, hogy elôcsalogassam a kocsmárost a pult mögül. Ahogy a felfordulás kezdett lecsendesedni, két matróz verekedésbe kezdett volna, hogy lefoglalja ôt a nagyteremben. Pontosan ez történt\nAz idô alatt a 'Sea Beast' kapitányának sikerült ellopnia a hordót. Ez... ez minden, amit tudok, "+GetSexPhrase("uram","asszonyom")+"! Kérem, ne adjon fel! Én csak... Én csak... Én csak... azt akartam, hogy Jack végre tisztelettel bánjon velem! Végül is segítettem neki...";
			link.l1 = "Segítettél egy embernek, miközben egy másikat habozás nélkül a farkasok elé dobtál?! Mindazonáltal, tartom a szavam - nem fogom felfedni a szerepedet ebben. De együtt kell élned azzal, amit tettél! A te ostobaságod komoly veszélybe sodorhatta volna a fogadósokat. Hol találom ezt a te Jackedet? És ne feledd: ha hazudsz nekem, visszajövök. Hidd el, nem fogod élvezni a viszontlátogatást.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "I... I... Mindent elmondok neked! Az egész az én... udvarlóm volt, Jack. Jack Veils! Ô gyôzködött, hogy csábítsak el bármelyik tengerészt a 'Sea Beast'. És amikor ô közeledne, nekem kellett jelenetet rendeznem, hogy elôcsalogassam a kocsmárost a pult mögül. Ahogy a felfordulás kezdett lecsendesedni, két matróz verekedésbe kezdett volna, hogy lefoglalja ôt a nagyteremben. Pontosan ez történt\nAz idô alatt a 'Sea Beast' kapitányának sikerült ellopnia a hordót. Ez... ez minden, amit tudok, "+GetSexPhrase("uram","asszonyom")+"! Kérem, ne adjon fel! Én csak... Én csak... Én csak... azt akartam, hogy Jack végre tisztelettel bánjon velem! Végül is segítettem neki...";
			link.l1 = "Segítettél egy embernek, miközben egy másikat habozás nélkül a farkasok elé dobtál?! Mindazonáltal, tartom a szavam - nem fogom felfedni a szerepedet ebben. De együtt kell élned azzal, amit tettél! A te ostobaságod komoly veszélybe sodorhatta volna a fogadósokat. Hol találom ezt a te Jackedet? És ne feledd: ha hazudsz nekem, visszajövök. Hidd el, nem fogod élvezni a viszontlátogatást.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "Nem tudtam, hogy ez ilyen komoly! Végül is ez csak egy hordó... Jack az utca túloldalán lakik. Ô bérli a házat, én... Nem tudok többet! Kérem, bocsásson meg nekem! Kapitány, esküszöm, hogy soha többé nem teszek ilyet!";
			link.l1 = "Menjen vissza a dolgára, és ne merjen sírni - a kocsmárosnak nem szabad gyanút fognia.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
