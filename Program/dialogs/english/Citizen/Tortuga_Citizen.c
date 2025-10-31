// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?","What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind.'","I've got nothing to say now.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "You wouldn't happen to know a certain Joep van der Vink, would you?";
				link.l1.go = "PZ_1";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Do you think I work for the secret service of "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well... no. Farewell then.";
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
		
		case "PZ_1":
			dialog.text = "Well, I don't know him personally, but I see him here from time to time. Why do you ask?";
			link.l1 = "I've been assigned to deliver a package to him personally. But no one wants to talk about him, and I don't know why. Do you? Is he a bad man? I'd appreciate your honest opinion.";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Again, we don't know each other personally, so I know almost nothing. But he has a close friend in town, and they're often seen together. Go to him – he'll decide whether to tell you more or not. His friend's name is Rober Martene.";
			link.l1 = "Rober Martene, you say... And who is he? Where can I find him?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Various places, but right now he's at our lighthouse - repairing his galleon after a terrible storm. It's called the 'Voltigeur'.";
			link.l1 = "Thank you so much! You have no idea how much you've helped me.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
