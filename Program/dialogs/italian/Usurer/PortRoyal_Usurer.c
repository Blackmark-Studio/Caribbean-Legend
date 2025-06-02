// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai cercato di farmi quella domanda non molto tempo fa...","Sì, lascia che indovini... Ancora una volta stiamo girando in tondo?","Ascolta, io gestisco le finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uh, dove se n'è andata la mia memoria...","Hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				link.l1 = "Dimmi, il Colonnello ti ha fatto visita? Ha detto che hai preparato una ricompensa per me.";
				link.l1.go = "DTSG_depozit_1";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_depozit_1":
			dialog.text = "Che colonnello?";
			link.l1 = "Thomas Lynch.";
			link.l1.go = "DTSG_depozit_2";
		break;
		
		case "DTSG_depozit_2":
			dialog.text = "Parla piano! Conosco l'uomo. Sì, è passato di qui. La tua ricompensa ti aspetta, Capitano.";
			link.l1 = "E quanto c'è?";
			link.l1.go = "DTSG_depozit_3";
		break;
		
		case "DTSG_depozit_3":
			dialog.text = "Esattamente diecimila in oro. Non un singolo peso - tutto oro.";
			link.l1 = "Almeno non sono trenta monete d'argento...";
			link.l1.go = "DTSG_depozit_4";
			AddItems(pchar, "chest", 70);
			Log_Info("You have received 70 chests");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_depozit_4":
			dialog.text = "Cos'era quello?";
			link.l1 = "Oh, niente... Grazie. Addio.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.DTSG_depozit");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
