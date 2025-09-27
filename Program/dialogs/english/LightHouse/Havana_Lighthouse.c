// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want?","What would you like to know?"),"What is it you need, "+GetAddress_Form(NPChar)+"?","That's the third time you've tried to ask me...","I've had enough of you, get lost!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sorry, I've changed my mind.","It's nothing, my apologies."),"I forgot, my apologies...","Third time's the charm, eh? Excuse me...","Sorry, sorry! I'll see myself out then...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Listen - has a man by the name of Joachim Merriman been here? He's a middle-aged Portuguese señor, with a moustache, an imperial beard and piercing eyes. Perhaps he disembarked in a cove or near the lighthouse? Have you seen anyone like him?";
				link.l1.go = "merriman";
			}
		break;
		
		// калеуче
		case "merriman":
			dialog.text = "Nay, I haven't seen anyone like him. I'd have noticed, aye.";
			link.l1 = "I see, what a pity. Thank you for your time, I'll continue my search then.";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
