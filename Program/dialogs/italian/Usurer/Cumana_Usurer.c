// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarla?"),"Hai cercato di farmi quella domanda non molto tempo fa...","Sì, lascia che indovino... Ancora una volta girando in cerchio?","Ascolta, io gestisco le finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho niente di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
