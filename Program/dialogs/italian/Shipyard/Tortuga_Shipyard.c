// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai provato a farmi una domanda un po' di tempo fa...","Mai ho incontrato persone con tanta curiosità nel mio cantiere navale o in qualsiasi altro luogo in questa città.","Che succede con tutte queste domande? Il mio lavoro è costruire navi. Occupiamoci di questo.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Uff, dove se n'è andata la mia memoria...","Mh, beh...","Prosegui...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "Cerco un Gaius Marchais. L'ultima cosa che ho sentito di lui è che ha attraccato la sua galea 'Santa Margarita' affinché tu la riparassi...";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "La sua propria galeone? Ho-ho, questa è una buona battuta, capitano. Gaius Marchais possedeva solo un sloop mezzo morto... ha catturato una galeone come premio dopo aver deciso di diventare un corsaro. Diavolo fortunato, prima incursione e un tale trofeo\nHo offerto buoni soldi per lei, ma lui ha rifiutato, immagina un po'! Invece ha venduto il suo patetico sloop per una piccola somma e l'ha utilizzata per riparare la galeone! Nuove vele, nuovi colori e un nuovo nome, che di solito non è un buon segno\nCerto, il nome era troppo papista, ma mia figlia si chiama anche Margarita, quindi suppongo che alla fine andasse bene... Ha detto che ne aveva abbastanza della violenza, quindi sarebbe diventato un commerciante. E ha avuto la buona fortuna...";
			link.l1 = "Suppongo che il commercio sarebbe riposante, ma le galeoni papali non vengono di solito catturate dalle golette. E qual è il nuovo nome della sua nave ora?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "'Ammirevole'... Non c'è da stupirsi! Correva intorno alla sua nuova galea come se stesse inseguendo una sposa, semplicemente non riusciva a smettere di ammirarla.";
			link.l1 = "Capisco. Gaius è a Tortuga adesso?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "No. Ha salpato sulla sua nuova nave e non è ancora tornato a Tortuga. Non so dove stava andando, quindi non posso aiutarti in questo.";
			link.l1 = "Che fastidio... Ho davvero bisogno di lui. Dovremmo anche fare un brindisi per la sua 'ammirevole' nave. Comunque, grazie per l'informazione.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Oh, nessun problema. Passa di nuovo, capitano. E non dimenticare che c'è sempre uno spazio libero per la tua nave qui, se sono necessarie riparazioni!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
