// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Che tipo di domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Mi sono ricreduto.'","Non ho nulla da dire ora.");
		    link.l1.go = "exit";
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensi che lavori per il servizio segreto di "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Ebbene... no. Addio allora.";
			link.l1.go = "exit";
			link.l2 = "Altre domande, allora?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sembro forse l'ufficio investigativo? Non lo so, non so nulla.";

            link.l1 = "Sei un tale pasticcione! Vattene.";
			link.l1.go = "exit";
			link.l2 = "Hai altre domande, allora?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
