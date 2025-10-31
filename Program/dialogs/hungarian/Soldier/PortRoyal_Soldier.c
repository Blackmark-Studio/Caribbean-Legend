// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak egy katonához?", "Katona az egész életét eltervezte - ôrködik, sürög... Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Egy katonát nem szabad hülye kérdésekkel zaklatni, " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor próbálsz kérdezni...",
                          "Egy katona sorsa nem könnyû, és most te, söpredék, az ôrületbe kergetsz...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Megvan...",
                      "Igen, igazad van, már harmadszor...", "Bocsánat...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
