// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Di nuovo domande, "+GetAddress_Form(NPChar)+"...","Domande, domande... Che ne dici di fare un po' di commercio, "+GetAddress_Form(NPChar)+"eh?","Ascolta, quanto tempo pensi di parlare?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Nessuna domanda per ora...","Mi dispiace, non ho nulla da dire ora..."),"Ancora una volta, mi dispiace...","Forse è davvero il momento di commerciare...","Mi dispiace, facciamo affari...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
