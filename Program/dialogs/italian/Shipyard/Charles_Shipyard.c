// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai provato a farmi una domanda un po' di tempo fa...","Non ho mai incontrato persone con tanta curiosità nel mio cantiere navale o in qualsiasi altro posto in questa città.","Che cosa sono tutte queste domande? Il mio lavoro è costruire navi. Occupiamoci di questo.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Mm, beh...","Vai avanti...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "Ascolta, maestro, qui costruisci navi, giusto?.. E cambi anche le vele... hai mai pensato a... un tessuto per vele migliore?";
                link.l1.go = "mtraxx";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Parlate in enigmi, signore... Parlate chiaramente, cosa vi ha portato qui? Non c'è nulla di cui preoccuparsi, non sono qualche tipo di impiegato e questo non è un dogana.";
			link.l1 = "Ah, sono contento che siamo sulla stessa lunghezza d'onda! Tela di seta per le vele, signore. Da quanto ne capisco, non c'è materiale migliore per le vele se la velocità è la tua preoccupazione.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Non solo velocità, ma anche la sua capacità di navigare controvento. Stai offrendo seta navale per l'acquisto? È davvero un carico prezioso. Ma c'è un ostacolo: semplicemente non so come utilizzarlo nella produzione. Mi segui? Un materiale come questo richiede un set molto speciale di abilità e competenze che mi mancano. Ad essere onesti, il mio cantiere ha una specializzazione molto diversa, se mi avessi offerto delle corde dallo Zarato di Russia, le avrei comprate tutte a prescindere dal prezzo. Abbiamo un bisogno costante di corde, invece la seta navale qui non è richiesta, mi dispiace!";
			link.l1 = "Mh. Capisco. Grazie per il tuo tempo, maestro. Buona fortuna!";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
