// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdés, "+ GetSexPhrase("fiatalember","fiatal hölgy") +"?", "Mire van szükséged, "+ GetSexPhrase("jóképû","csinos") +"? Kérdezz csak!"), "Már megint kérdés?", "Tee-hee, ha neked mindegy - kérdések...",
                          ""+ GetSexPhrase("Hm, miért nem választasz magadnak egy szépséget? Kezdek gyanakodni rád...","Hm, miért nem választasz magadnak egy szépséget? Attól tartok, itt nincsenek fiúk, te-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam, elnézést.", "Igazából, nem számít..."), "Én... elnézést, egyelôre nincs kérdésem.",
                      "Igazad van, már harmadszorra. Bocsásson meg.", "Talán legközelebb, asszonyom.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
