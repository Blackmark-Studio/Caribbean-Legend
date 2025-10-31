// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?","What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind.'","I've got nothing to say now.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Who are you interested in?","Who do you mean?","Well, who is it?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "I want to know more about Jan Svenson.";
				link.l1.go = "svenson";
			}
			link.l2 = "Let's change the subject...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Where do you want to go?","What are you looking for?","What exactly do you need?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Where is Jan Svenson's house?";
				link.l1.go = "svenson_house";
			}
			link.l2 = "Let's change the subject...";
			link.l2.go = "new question";
		break;
		
		case "svenson":
			dialog.text = RandPhraseSimple("Oh, our Jan Svenson is a very important person. In the past he was the most dashing pirate of the Western Main and even now he still hasn't begun to rust, ha! But those days are over, he isn't as active as he used to be. He owns a mansion and lives there with his young wife, and he is always a welcome guest at the governor's residence. A lot of guests come to Jan, pirates mostly.","Jan Svenson is a legend of the Western Main! Forest Devil, that's what the Spanish called him when he was driving them away from here. He used to be a famous corsair, but now he is a respected citizen of our colony.\nThough he still does some 'business' on the side, it's no longer by his own hand. He rarely leaves his house since he married a young beauty.");
			link.l1 = "My thanks.";
			link.l1.go = "exit";
		break;
		
		case "svenson_house":
			dialog.text = RandPhraseSimple("Go straight from the pier until you reach the square, the house on the right near the fountain is Svenson's mansion.","Go to the pier through the square from the governor's residence, the house on the left near the fountain is Svenson's mansion.");
			link.l1 = "My thanks.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
