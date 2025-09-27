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
			link.l1 = "I want to know more about Fadey the Muscovite.";
			link.l1.go = "fadey";
			link.l2 = "No one, never mind that.";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Where do you want to go?","What are you looking for?","What exactly do you need?");
            link.l1 = "Where is Fadey's house?";
			link.l1.go = "fadey_house";
			link.l2 = "Let's talk about something else...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("Ah, an important man. He owns the local factory and is close with the high society of Basse-Terre. He has a strong accent and he really likes drinking... but he never gets drunk.","He is a big shot and a friend of the governor. Fadey owns a local factory. He came from a northern country, far, far away from here... I don't even know the name of it. He has strong hands and can drink a whole barrel of rum without getting drunk.");
			link.l1 = "My thanks.";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("Go straight from the pier until you reach the square, the house on the left is Fadey's mansion.","Go to the pier through the square from the governor's residence, the house on the right is Fadey's mansion.");
			link.l1 = "My thanks.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
