// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?","What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind.'","I've got nothing to say now.");
		    link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Tell me, does the name 'Juan' ring any bells?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Listen, mate, a frigate under the command of Miguel Dichoso moored in port here in April 1654. He disappeared that day. Do you remember anything about it?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Do you think I work for the secret service of "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well... no. Farewell, then.";
			link.l1.go = "exit";
			link.l2 = "Any other questions, then?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Do I look like the investigation bureau? I don't know, I don't know a thing.";

            link.l1 = "You're such a muddlehead! Begone.";
			link.l1.go = "exit";
			link.l2 = "Any other questions, then?";
			link.l2.go = "new question";
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Are you kidding me? There are two dozen Juans in every colony!";
			link.l1 = "I see. Apologies for troubling you...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Come on, captain! Do you think I remember such things?","Forgive me Señor, I can't help you with that.","Señor, do you really think I remember such rubbish? I've got enough problems already.");
			link.l1 = LinkRandPhrase("I see. Apologies for troubling you...","What a pity. Farewell.","Alright, farewell...");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
