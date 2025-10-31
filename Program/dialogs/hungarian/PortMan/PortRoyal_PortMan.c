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
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Jó napot! Francois Gontier kapitány regisztrált itt? Porto Bellóból hajózott a '" + pchar.questTemp.Slavetrader.ShipName + "'nevû korvettjén.";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("Nem, nem tette. És a Corvette '" + pchar.questTemp.Slavetrader.ShipName + "' nem látták Kikötô-Royalban.", "Errôl már kérdeztél, és én válaszoltam.", "Mondom, hogy már kérdezett errôl a Gontier fickóról.", "Kérem, ne vonja el a figyelmemet a munkámról!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Köszönöm. Tovább keresgélek.", "Hm, nos...", "Igen, tényleg megkérdeztem ...", "Pardon, " + npchar.name + "...", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
