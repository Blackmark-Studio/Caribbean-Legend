// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?","What do you want, "+GetAddress_Form(NPChar)+"?"),"You've already tried to ask me a question "+GetAddress_Form(NPChar)+"...","You've brought up this question for the third time today...","Look, if you have nothing to tell me about the port's affairs then don't bother me with your questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.","I've got nothing to talk about."),"Never mind.","Indeed, the third time already...","Sorry, but I'm not interested in the port's affairs for now.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Good day to you. I'd like to learn about a corvette named '"+pchar.questTemp.Slavetrader.ShipName+"' under the command of François Gontier.";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Excuse me, has a man by the name of Joachim Merriman arrived at your port? A middle-aged señor, Portuguese, with a moustache, imperial beard and piercing eyes?";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "I am interested in a ship named 'Cantavro'. I am looking for its captain, Esberdo Cabanas, on a private matter. Could you help me?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Yes, he was here. But he has already left. Ask our tavern keeper about him, he has rented a room upstairs.","You have already asked about this and I've answered.","I told you, you've already asked about this Gontier..","I ask you not to bother me!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thanks. I'll do that.","Hm, well ...","Yes, I really have asked ...","Pardon, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Can't tell you anything about him. Even if he arrived, he never registered anywhere.";
			link.l1 = "I see. Such a pity... Alright, I'll continue my search...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "Let's see... the schooner 'Cantavro' set sail two days ago on patrol... however, the location is not listed. It is a military vessel, so the destination is known only to its captain and the fort commandant. I would suggest you speak with the commandant directly; you can find him at the fort if you wish to know more. Unfortunately, that is all I can do for you.";
			link.l1 = "I see. Well, thank you for your time...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
