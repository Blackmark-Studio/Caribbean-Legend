// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai per un soldato?","Un soldato ha tutta la sua vita programmata - guardando, trafficando... Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Non dovresti infastidire un soldato con domande stupide, "+GetAddress_Form(NPChar)+"...","Questa è la terza volta oggi che provi a farmi una domanda...","La sorte di un soldato non è facile, e ora tu, feccia, mi stai facendo impazzire...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Capito...","Sì, hai ragione, è già la terza volta...","Mi dispiace...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dimmi, il nome Juan significa qualcosa per te?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "No. È tutto?";
			link.l1 = "Sì. Scusa per il disturbo, soldato...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
