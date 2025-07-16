// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Che tipo di domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Ho cambiato idea.","Non ho nulla da dire adesso.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "Non sapresti per caso un certo Joep van der Vink, vero?";
				link.l1.go = "PZ1";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensi che io lavori per il servizio segreto di "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Beh... no. Addio allora.";
			link.l1.go = "exit";
			link.l2 = "Altre domande, quindi?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sembro l'ufficio delle indagini? Non lo so, non so niente.";

            link.l1 = "Sei un tale pasticcione! Sparisci.";
			link.l1.go = "exit";
			link.l2 = "Hai qualche altra domanda, allora?";
			link.l2.go = "new question";
		break;
		
		case "PZ1":
			dialog.text = "Beh, non lo conosco personalmente, ma lo vedo qui di tanto in tanto. Perché chiedi?";
			link.l1 = "Mi è stato assegnato di consegnare un pacco a lui personalmente. Ma nessuno vuole parlare di lui, e non so perché. Lo sai tu? È un uomo cattivo? Apprezzerei la tua onesta opinione.";
			link.l1.go = "PZ2";
		break;
		
		case "PZ2":
			dialog.text = "Di nuovo, non ci conosciamo personalmente, quindi so quasi niente. Ma lui ha un amico stretto in città, e spesso sono visti insieme. Vai da lui - deciderà se dirti di più o no. Il nome del suo amico è Rober Martene.";
			link.l1 = "Dici Rober Martene... E chi è lui? Dove posso trovarlo?";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Diversi posti, ma adesso si trova al nostro faro - sta riparando il suo galeone dopo una terribile tempesta. Si chiama 'Voltigeur'.";
			link.l1 = "Grazie mille! Non hai idea di quanto mi hai aiutato.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
