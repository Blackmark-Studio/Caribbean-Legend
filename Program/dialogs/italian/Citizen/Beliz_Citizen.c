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
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
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
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Circa un mese e mezzo fa è arrivato a Belize un certo Jerome Sauvernier. È rimasto ferito in una rissa alla taverna 'Glass Eye', ma è sopravvissuto. Potreste dirmi dove potrei trovarlo?";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Un mese e mezzo fa, più o meno, è comparso un gentiluomo a Belize. Si chiamava Jerome Sauvernier. Stava cercando un altro uomo — quindi deve aver parlato con qualche abitante. Più tardi è rimasto ferito in una rissa in taverna, ma per fortuna è sopravvissuto. Potreste dirmi dove si trova adesso?";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Sto cercando un uomo arrivato a Belize circa due mesi fa. Si chiama Jerome Sauvernier. Era sulle tracce di un certo gentiluomo, e suppongo abbia chiesto in giro agli abitanti...";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
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
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "Certo, è difficile da credere! Ma non fidarti di tutto ciò che senti, signore. L'ho visto, chiaro come ti vedo ora. È un bene che abbia catturato Lutter, ma perché tutta questa farsa da mercante? Si comporta come un soldato. Posso sempre dirlo - un mio parente ha servito per anni.";
			link.l1 = "Interessante. Beh, ognuno ha i suoi segreti. Meglio che me ne vada. Grazie per il consiglio.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Ho già visto l'uomo. È difficile credere che questo sia lo stesso pirata che ha terrorizzato i nostri mercanti per anni. Come ha fatto a ottenere il suo proprio comando in primo luogo? Ho visto i soldati che lo scortavano - urlando, piangendo, ridendo. Un pazzo.";
			link.l1 = "Forse la sconfitta e la realtà della sua morte imminente erano troppo per lui. Ma non importa. Addio!";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Sì, e anche io sto festeggiando - un buon numero dei miei compatrioti è morto per mano sua. I più sfortunati hanno perso un padre, un fratello, un figlio - capisci il quadro. Quella barbarie è durata troppo a lungo! Matt deve essere stato uno dei pirati più fortunati degli ultimi anni, se mi chiedi.";
			link.l1 = "La fortuna finisce sempre prima o poi. Ci vediamo in giro.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
		
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "Non lo conosco, signore. Le risse in taverna sono quasi quotidiane, e ricordare tutti quelli che restano feriti è un compito ingrato.";
    		link.l1 = "Capisco, grazie. Buona giornata.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "Sovernie? Francese... Sì, c’era un tale. È venuto da me, ma non potevo essergli d’aiuto. Non l’ho più visto, mi scuso.";
    		link.l1 = "Grazie. Allora continuerò a chiedere in giro.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_3":
			dialog.text = "Signor Jerome! Certo, certo, ricordo bene. È rimasto ferito in una rissa in taverna. Dopo di allora esce quasi mai di casa, sta curando la ferita alla gamba.";
			link.l1 = "E dove si trova questa casa?";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;
		
		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "È qui vicino, proprio accanto all’amministrazione portuale. Una casa con il tetto rosso. Lì lo troverai.";
    		link.l1 = "Grazie, mi avete davvero aiutato! Tutto il meglio per voi!";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
