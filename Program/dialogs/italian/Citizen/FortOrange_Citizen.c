// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Qual tipo di domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Mi sono ricreduto.","Non ho nulla da dire ora.");
		    link.l1.go = "exit";
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensi che io lavori per il servizio segreto di "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Ebbene... no. Allora addio.";
			link.l1.go = "exit";
			link.l2 = "Hai qualche altra domanda, allora?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sembro l'ufficio delle indagini? Non lo so, non so nulla.";

            link.l1 = "Sei talmente confuso! Sparisci.";
			link.l1.go = "exit";
			link.l2 = "Hai altre domande, allora?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
