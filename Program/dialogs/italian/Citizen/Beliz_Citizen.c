// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Qual tipo di domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Mi sono ricreduto.'","Non ho nulla da dire ora.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "Hai per caso incrociato il Capitano Edgardo Sotta? Puoi dirci qualcosa su di lui? Sembra un uomo degno di nota.";
					link.l1.go = "Sotta1";
					link.l2 = "Non andrai a vedere l'esecuzione del Chiacchierone?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "Dimmi, hai visto l'eroe del giorno, Capitano Edgardo Sotta? Purtroppo l'ho perso. Com'è? Non posso credere che un mercante abbia catturato il famigerato Windbag Matt!";
					link.l1.go = "Sotta1_1";
					link.l2 = "Vedo che tutta la città sta festeggiando la cattura di Lutter, persino quelli che non vanno mai in mare."link.l2.go ="Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensi che io lavori per il servizio segreto di "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Beh... no. Addio allora.";
			link.l1.go = "exit";
			link.l2 = "Hai qualche altra domanda?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sembro forse l'ufficio investigativo? Non lo so, non ne so nulla.";

            link.l1 = "Sei un tale pasticcio! Sparisci.";
			link.l1.go = "exit";
			link.l2 = "Qualche altra domanda, allora?";
			link.l2.go = "new question";
		break;
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "Non ho avuto l'opportunità di parlare con lui, ma ho visto la sua nave - una pesante galeone. È pericoloso navigare da soli in queste acque, ma Sotta lo fa senza una scorta.";
			link.l1 = "Probabilmente insegue ogni moneta d'oro e taglia i costi ovunque può. Beh, non ti tratterrò. Buona giornata.";
			link.l1.go = "Exit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "Certo, è difficile da credere! Ma non fidarti di tutto ciò che senti, signore. L'ho visto, chiaro come ti vedo ora. È un bene che abbia catturato Lutter, ma perché tutta questa farsa da mercante? Si comporta come un soldato. Posso sempre dirlo - un mio parente ha servito per anni.";
			link.l1 = "Interessante. Beh, ognuno ha i suoi segreti. Meglio che me ne vada. Grazie per il consiglio.";
			link.l1.go = "Exit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Ho già visto l'uomo. È difficile credere che questo sia lo stesso pirata che ha terrorizzato i nostri mercanti per anni. Come ha fatto a ottenere il suo proprio comando in primo luogo? Ho visto i soldati che lo scortavano - urlando, piangendo, ridendo. Un pazzo.";
			link.l1 = "Forse la sconfitta e la realtà della sua morte imminente erano troppo per lui. Ma non importa. Addio!";
			link.l1.go = "Exit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Sì, e anche io sto festeggiando - un buon numero dei miei compatrioti è morto per mano sua. I più sfortunati hanno perso un padre, un fratello, un figlio - capisci il quadro. Quella barbarie è durata troppo a lungo! Matt deve essere stato uno dei pirati più fortunati degli ultimi anni, se mi chiedi.";
			link.l1 = "La fortuna finisce sempre prima o poi. Ci vediamo in giro.";
			link.l1.go = "Exit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
