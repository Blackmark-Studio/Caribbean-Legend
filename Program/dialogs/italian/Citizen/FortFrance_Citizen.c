// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("Che tipo di domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Ho cambiato idea.","Non ho nulla da dire ora.");
			link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "Scusami, "+GetAddress_FormToNPC(NPChar)+"potresti dirmi dove posso trovare Michel de Monper? Ho sentito dire che è in questa città.";
				link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "Ascolta, "+GetAddress_FormToNPC(NPChar)+", Voglio chiederti qualcosa... Sto cercando un navigatore per servire sulla mia nave, ne conosci qualcuno?";
				link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensi che io lavori per il servizio segreto di "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Beh... no. Addio allora.";
			link.l1.go = "exit";
			link.l2 = "Hai altre domande, allora?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sembro l'ufficio investigativo? Non lo so, non so nulla.";

            link.l1 = "Sei un tale pasticcione! Sparisci.";
			link.l1.go = "exit";
			link.l2 = "Altre domande, poi?";
			link.l2.go = "new question";
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "Hmm... Sospetto che tu sia arrivato qui di recente, visto che fai domande così audaci... Ti consiglio di smettere se non vuoi problemi. Parla con l'Abate, potrebbe aiutarti a 'ritornare in te'. Puoi trovarlo alla chiesa.";
				link.l1 = "Capisco...";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
			else
			{
				dialog.text = LinkRandPhrase("No, non ne ho sentito parlare.","Non posso aiutarti, ho lavoro da fare.","Chi? Non mi suona familiare, no. Proseguirò per la mia strada.");
				link.l1 = "Capisco... Allora proseguirò la mia strada.";
				link.l1.go = "exit";
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("No, non conosco nessun navigatore.","Ho lavoro da sbrigare e no, chiedi a qualcun altro...","Sfortunatamente non posso aiutarti, non conosco nessuno.");
			link.l1 = "Capisco. Allora chiederò altrove.";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
