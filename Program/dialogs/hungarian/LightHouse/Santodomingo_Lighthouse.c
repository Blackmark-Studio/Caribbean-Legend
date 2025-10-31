// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz?", "Mit szeretnél tudni?"), "Mire van szüksége, " + GetAddress_Form(NPChar) + "?", "Már harmadszor próbálod megkérdezni...", "Elegem van belôled, tûnj el!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sajnálom, meggondoltam magam.", "Semmiség, elnézést."), "Elfelejtettem, elnézést kérek...",
                      "Harmadszorra sikerül, mi? Elnézést...", "Bocsánat, bocsánat! Akkor majd én kikísérem magam...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
