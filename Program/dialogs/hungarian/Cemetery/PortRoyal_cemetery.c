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
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
