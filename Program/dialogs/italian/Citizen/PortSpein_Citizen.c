// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Quali domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Ho cambiato idea.'","Non ho nulla da dire ora.");
		    link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dimmi, il nome 'Juan' ti suona familiare?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Ascolta compagno, una fregata sotto il comando di Miguel Dichoso attraccò qui, nel porto, nell'aprile 1654. È sparito in quel giorno. Ti ricordi qualcosa al riguardo?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensi che io lavori per i servizi segreti di "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Beh... no. Addio allora.";
			link.l1.go = "exit";
			link.l2 = "Hai altre domande, allora?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sembro forse l'ufficio investigativo? Non lo so, non so niente.";

            link.l1 = "Sei un vero pasticcione! Vattene.";
			link.l1.go = "exit";
			link.l2 = "Hai altre domande, allora?";
			link.l2.go = "new question";
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Stai scherzando? Ci sono almeno una dozzina di Juan in ogni colonia!";
			link.l1 = "Capisco. Scusami per il disturbo...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Avanti, capitano! Pensi davvero che mi ricordi di queste cose?","Perdonami Signore, non posso aiutarti con questo.","Signore, pensi davvero che ricordi tali sciocchezze? Ho già abbastanza problemi.");
			link.l1 = LinkRandPhrase("Capisco. Mi scuso per il disturbo...","Che peccato, Addio.","Bene, addio...");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
