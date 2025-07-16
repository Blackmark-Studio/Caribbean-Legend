// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Avanti, cosa vuoi?","Stavamo proprio parlando di questo. Devi aver dimenticato...","È la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. Le persone comprano roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, ho dimenticato per qualche motivo...","Sì, è davvero la terza volta...","Mh, non lo farò...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dimmi, il nome Juan significa qualcosa per te?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Nell'aprile 1654 una fregata attraccò nel vostro porto sotto il comando del Capitano Miguel Dichoso, dopo di che sparì. Il suo nome vi dice qualcosa? Possibilmente, avrebbe potuto acquistare della merce da voi o detto qualcosa...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Oh, smettila, capitano! Ho avuto due Juans nel mio negozio oggi, e un altro ieri. Cosa, dovrei ricordare ciascuno?";
			link.l1 = "Bene. Scusa per il disturbo...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Oh, capitano, ho avuto così tante fregate e galeoni che entravano ed uscivano da qui in quel tempo, Miguels e Carloses...";
			link.l1 = "Capisco. Quindi, non puoi essere d'aiuto...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
