// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Kérdések ismét, " + GetAddress_Form(NPChar) + "...", "Kérdések, kérdések... Mi lenne, ha cserélnénk, " + GetAddress_Form(NPChar) + "huh?",
                          "Figyelj, meddig akarsz még beszélgetni?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Egyelôre nincsenek kérdések...", "Sajnálom, most nincs mit mondanom..."), "Még egyszer, sajnálom...",
                      "Talán tényleg itt az ideje kereskedni...", "Sajnálom, cseréljünk...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
