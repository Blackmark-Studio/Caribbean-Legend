// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai per un soldato?","Un soldato ha tutta la sua vita programmata - guardia, fatica... Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Non dovresti disturbare un soldato con domande stupide, "+GetAddress_Form(NPChar)+"...","È la terza volta oggi che provi a farmi una domanda...","Il destino di un soldato non è facile, e ora tu, feccia, mi stai facendo impazzire...","blocca",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Capito...","Sì, hai ragione, già la terza volta...","Scusa...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
