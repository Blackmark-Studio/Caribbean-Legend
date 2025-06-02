// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai provato a farmi una domanda un po' di tempo fa...","Non ho mai incontrato persone con tanta curiosità nel mio cantiere navale o in qualsiasi altro luogo in questa città.","Cosa c'è con tutte queste domande? Il mio lavoro è costruire navi. Occupiamoci di questo.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Mh, beh...","Avanti...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dimmi, il nome Juan significa qualcosa per te?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Signore, c'era una fregata qui sotto il comando di Miguel Dichoso nell'aprile 1654. È scomparso subito dopo. Non ti ricordi nulla al riguardo? Forse Dichoso si è fermato per una riparazione, e forse ti ha detto qualcosa...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "No. Niente affatto.";
			link.l1 = "Bene. Scusa per il disturbo...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Mh. No. Non si è fermato per una riparazione e non mi ha detto nulla affatto. E se qualcosa del genere fosse accaduto, non me lo ricordo. Mi dispiace, non posso aiutarti, signore.";
			link.l1 = "Bene. Grazie amico...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
