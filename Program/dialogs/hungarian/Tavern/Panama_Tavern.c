// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("A "+ GetCityName(npchar.city) +" összes pletykája az Ön rendelkezésére áll. Mit szeretnél megtudni?",
                          "Éppen errôl beszéltünk. Biztos elfelejtette...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Ismétled ugyanazt, mint egy papagáj...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Igen...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "Úgy hallottam, hogy van egy Francois Gontier nevû kalóz a városodban. Nem tudod véletlenül, hol találom?";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ”ЊЉ-ѓваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "Nézze, egy Bertrand Pinette nevû embert keresek, hallott róla? Nemrég érkezett Panamába. Egy impozáns úriember parókában. Lehet, hogy itt járt...";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Igen, volt egy ilyen fickó a városban. Sötét helyeken ólálkodott... Aztán jöttek a haverjai, és meglátogatták, úgy nézett ki, mint egy csapat gyilkos. Velük hagyta el a várost.", "Errôl már kérdezett, és én már válaszoltam is.", "Mondtam, hogy már kérdeztél errôl Gontier.", "Figyelj, menj el, és ne zaklass engem! Teljesen elment az eszed?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("És hová ment, tudja?", "Hm, azt hiszem...", "Igen, persze, ezt már kérdeztem...", "Bocsánat, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "Nos, csak egy út van innen gyalog - Portobello. És ô elment. Szóval ott keressétek.";
			link.l1 = "Köszönöm, sokat segítettél!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("panama");
			dialog.text = "Bertrand Pinette? Francia? Sosem hallottam róla. Nem, haver, már egy ideje nem láttunk franciákat.";
			link.l1 = "Milyen kár... Biztos vagy benne? Egy Don Carlos de Milyar nevû fontos hidalgó barátja. Úgy volt, hogy együtt érkeznek ide.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Senor de Milyar? Az az úr egy éve járt Panamában. Valójában Don Carlos de Milyar Portobellóban él. A helyi kormányzó nagy barátja.";
			link.l1 = "Értem. Nem kellett volna idôt és levegôt vesztegetni a dzsungelben. Köszönöm, haver.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
			AddMapQuestMarkCity("PortoBello", true);
			AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
