// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind.'", "I've got nothing to say now.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "Tell me, "+GetAddress_FormToNPC(NPChar)+", was the galleon 'Santa Margarita' here not long ago? As a prize ship of a privateer maybe?";
                link.l1.go = "guardoftruth";
			}
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
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, I don't remember any galleon with this name. We rarely see ships that large here.","What? A galleon? Here? I have no idea.","No Sir, that ship hasn't moored here lately, at least I don't remember it happening.");
			link.l1 = LinkRandPhrase("Alright...","Very well...","I see, pity...");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
