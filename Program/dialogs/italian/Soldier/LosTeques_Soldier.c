// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai per un soldato?","Un soldato ha tutta la sua vita pianificata - fare la guardia, trafficare... Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Non dovresti infastidire un soldato con domande stupide, "+GetAddress_Form(NPChar)+"...","Questa è la terza volta oggi che hai cercato di farmi una domanda...","La sorte di un soldato non è facile, e ora tu, feccia, mi stai facendo impazzire...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Capito...","Sì, hai ragione, è già la terza volta...","Mi dispiace...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
