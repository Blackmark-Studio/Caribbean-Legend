// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Che tipo di domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Ho cambiato idea.","Non ho nulla da dire ora.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "Dimmi, "+GetAddress_FormToNPC(NPChar)+", la galeone 'Santa Margarita' è stata qui da poco? Come una nave preda di un corsaro forse?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensi che io lavori per il servizio segreto di "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Ebbene... no. Addio allora.";
			link.l1.go = "exit";
			link.l2 = "Hai qualche altra domanda, allora?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sembro l'ufficio investigativo? Non lo so, non so nulla.";

            link.l1 = "Sei un tale confuso! Sparisci.";
			link.l1.go = "exit";
			link.l2 = "Hai qualche altra domanda?";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, non ricordo nessun galeone con questo nome. Raramente vediamo navi così grandi qui.","Cosa? Un galeone? Qui? Non ne ho idea.","No signore, quella nave non ha attraccato qui di recente, almeno non ricordo che sia successo.");
			link.l1 = LinkRandPhrase("Bene...","Molto bene...","Capisco, peccato...");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
