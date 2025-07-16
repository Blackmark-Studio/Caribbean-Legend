// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind.'", "I've got nothing to say now.");
		    link.l1.go = "exit";
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Do you think I work for the secret service of "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well... no. Farewell then.";
			link.l1.go = "exit";
			link.l2 = "Any other question, then?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Do I look like the investigation bureau? I don't know, don't know a thing.";

            link.l1 = "You're such a muddle-head! Begone.";
			link.l1.go = "exit";
			link.l2 = "Any other question, then?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
