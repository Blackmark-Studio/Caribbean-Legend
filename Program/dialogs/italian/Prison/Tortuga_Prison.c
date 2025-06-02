// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parla, sto ascoltando";
			link.l1 = "Mi sono sbagliato. Addio.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "Qual è lo scopo della tua visita a Tortuga, Capitano?";
			link.l1 = "Ti prego! Aiuta il mio compagno, e risponderò a tutte le tue domande!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "Sei una persona così importante, e sei venuto qui senza alcuna guardia, proprio dopo che tutta la prigione ha sentito uno sparo?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "Mentre ritardi la tua risposta, lui sta sanguinando a morte. Ripeto la domanda.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "So abbastanza su cosa è successo. Ripeto la domanda.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Ultima chance, Capitano.";
			link.l1 = "Sto eseguendo l'incarico dato a me dal governatore generale!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "Sai molto bene che sono il Capitano della mia nave e lavoro su contratto. E visito la tua bella isola un paio di volte all'anno!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "Avevo i miei sospetti, ma non ero del tutto sicuro. Sei fortunato che solo pochi giorni fa si è tenuto un incontro importante a Capsterville. Alcune persone molto influenti sono riuscite a trovare un accordo. Quindi, non sei più il mio nemico.";
			link.l1 = "Ci aiuterai?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "Ti libererò immediatamente. Il tuo compagno sarà trasferito sulla nave e riceverà le cure necessarie.";
			link.l1 = "Grazie...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "Hai quasi fatto naufragio, Charles! Vattene e non tornare a Tortuga per almeno un mese. Lascia che la polvere si depositi e le teste si raffreddino.";
			link.l1 = "Lo farò. Addio!";
			link.l1.go = "exit";
			link.l2 = "Non spiegherai nulla affatto? Neanche un po'? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "Qualcuno ti ha denunciato. A quanto pare, sei un fanatico cattolico arrivato sulla nostra bellissima isola per uccidere maliziosamente il suo onorevole governatore.";
			link.l1 = "Non sono un fanatico!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "È scritto abilmente, credimi. Sono bravo in queste cose - le migliori calunnie sono quelle che contengono almeno un granello di verità.";
			link.l1 = "Chi ha scritto il rapporto?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "Chi ha lasciato entrare l'assassino in prigione?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Qualcuno che voleva che tu fossi rinchiuso in prigione per qualche giorno, invece di mandarti immediatamente al tavolo di tortura degli Ugonotti nel seminterrato di La Roche.\nBasta, Charles. Vattene. Occupati prima di ciò che hai di fronte, e dopo... beh, mi capisci!";
			link.l1 = "Sì. Lo farò. Addio, Comandante.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "L'ho fatto.";
			link.l1 = "È meglio che tu mandi a chiamare un altro prima che me ne vada da qui.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "Sono tutto orecchie, comandante.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Non sono obbligato a spiegarti nulla, Charles. Sii grato che sei finito nelle mie mani e non in quelle del mio superiore diretto. E sii grato che sarà il tuo capo a compensarmi per tutti questi disturbi, e non tu.";
				link.l1 = "Certo, certo... Non conosci il mio capo come lo conosco io. Arrivederci, comandante.";
				link.l1.go = "exit";
				
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Sai cosa? Credo che te lo dirò. È stata fatta una generosa donazione, esente da tasse, al fondo pensione speciale della guarnigione. Come gesto di gratitudine, al donatore è stato permesso di contribuire all'esecuzione rapida e legale di un noto criminale!";
				link.l1 = "Il mio ufficiale?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Amico mio?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Non sono obbligato a spiegarti nulla, Charles. Sii grato di essere finito nelle mie mani e non in quelle del mio superiore diretto. E sii grato che sarà il tuo capo a risarcirmi per tutti questi disturbi, e non tu.";
				link.l1 = "Certo... Non conosci il mio capo come lo conosco io. Addio, comandante.";
				link.l1.go = "exit";
				
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Sai cosa? Credo che te lo dirò. Una generosa donazione, esente da tasse, è stata fatta al fondo pensione speciale della guarnigione. Come gesto di gratitudine, al donatore è stato permesso di contribuire all'esecuzione rapida e legale di un noto criminale!";
				link.l1 = "Il mio ufficiale?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Amico mio?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Vattene, Charles. E porta via questa feccia con te. La tua scelta di compagni... è deludente.";
			link.l1 = "Almeno dimmi dove trovare il tuo... benefattore?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "Sulla terraferma. Addio, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "È stato presentato un rapporto contro di te. Un rapporto molto brutto. Capitano, è chiaro che ti hanno incastrato, ma... sono pienamente nel mio diritto di tenerti qui per altre due settimane e lasciare che il tuo amico muoia. A meno che...";
			link.l1 = "Quanto costa?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "Chi mi ha incastrato? Hai lasciato entrare l'assassino in prigione?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Per favore, deposita cinquecento dobloni nel fondo pensione della guarnigione di Tortuga presso il prestanome locale.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+"E aggiungiamo un altro centinaio di dobloni per i vecchi guai che hai causato coinvolgendoti con una signora di alto rango su quest'isola.";
			}
			link.l1 = "Apri questa maledetta porta subito!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Hai già preso troppo del mio tempo. Vai al prestanome e deposita cinquecento dobloni nel fondo pensione della guarnigione di Tortuga.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+"E aggiungiamo un altro centinaio di dobloni per i vecchi problemi che hai causato coinvolgendoti con una dama di alto rango su quest'isola.";
			}
			link.l1 = "Apri questa maledetta porta subito!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "I fondi sono depositati. Dov'è Hercule?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "Gli abbiamo fornito il primo soccorso e lo abbiamo mandato sulla tua nave. Il mascalzone è duro, molto probabilmente se la caverà. Addio, Capitano, e non farti vedere sulla nostra isola per un po'!";
			link.l1 = "Ebbene, dopo un'accoglienza del genere, starò alla larga da qui! Addio, comandante.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
