// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me a question a little while ago...", "I have never met people with such curiosity in my shipyard or anywhere else in this town.",
                          "What's with all the questions? My job is to build ships. Let's take care about that.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Hm, well...", "Go ahead...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Listen, has a man named Joachim Merriman been here recently? A middle-aged senor, Portuguese, with moustache, imperial beard and piercing eyes? Perhaps, he wanted to buy a ship?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "No, Senor. Haven't seen such a client.";
			link.l1 = "I see. Pity. I will continue my search then...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
