// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Go ahead, what do you want?","We were just talking about that. You must have forgotten...","This is the third time today you've brought up some question...","Listen, this is a store. People buy things here. Don't disturb me!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, "+NPChar.name+", maybe next time.","Right, I've forgotten for some reason...","Yes, it really is the third time...","Hm, I won't...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Listen, has a man by the name of Joachim Merriman ever come here to your store? A middle-aged señor, Portuguese, with a moustache, imperial beard, and piercing eyes? Perhaps he bought something?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "No, none of my customers look like the person you described. Also, I've never heard that name before. Sorry, I can't help you any further.";
			link.l1 = "I see. Pity. Well, I'll continue my search...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
