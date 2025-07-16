// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande avete?","Come posso aiutarti?"),"Hai provato a farmi quella domanda non molto tempo fa...","Sì, lascia che indovini... Ancora una volta stai girando in tondo?","Ascolta, io gestisco le finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Uhm, dove se n'è andata la mia memoria...","L'hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// Реакция ростовщика Панамы на репутацию ГГ или на разграбление Картахены по сюжету
		case "Panama_Deposit_NoReputation":
			dialog.text = "Esatto... Un uomo d'onore amato dai sudditi del Re non sarà mai rifiutato dalla mia banca, indipendentemente dalla sua nazionalità.";
			link.l1 = "Capisco. Arrivederci.";
			link.l1.go = "exit";
		break;
		
		case "Panama_Deposit_Cartahena":
			dialog.text = "Ma mia figlia e mio suocero l'hanno avuto, sfortunatamente. Vivevano a Cartagena. Vattene, "+GetAddress_Form(NPChar)+". Non sei il benvenuto qui.";
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "Perdonami. Addio.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "La tua perdita. Addio.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
		
		case "Panama_Deposit_SgorelVklad":
			dialog.text = "I fondi sono stati sequestrati dalla Corona per aiutare le vittime del saccheggio della città di Cartagena. Non posso aiutarti. Ti chiedo di lasciare immediatamente la mia banca prima che chiami le guardie!";
			link.l1 = "Te ne pentirai...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
