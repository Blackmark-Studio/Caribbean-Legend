// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple("What kind of questions?","What would you like?");
				link.l1 = "I know that the Dutch West India Company has set a good price on the head of the famous pirate Bartolomeo the Portuguese. I managed to capture him. He is currently in my ship's hold, and I am ready to hand him over to the authorities.";
				link.l1.go = "Portugal";
				break;
			}
            dialog.text = RandPhraseSimple("What kind of questions?","What is it you need?");
			link.l1 = RandPhraseSimple("Nothing of importance, Sir.","I've nothing to say, apologies.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Unfortunately, I can't consider you for a job. You're not someone I wish to work with at the moment. Farewell.";
                link.l1 = "You can't be serious... but very well.";
                link.l1.go = "exit";
				break;
			}                   
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Bart the Portuguese?! Do you have him? Alive?";
			link.l1 = "I know you don't need him dead. He's alive. I had to make a great effort to keep him that way!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Most excellent! Now he will tell us everything... Mynheer, prepare the prisoner for transfer. We will send a military barque to your ship immediately. ";
			link.l1 = "I'd like to talk about my reward first, Mynheer... If you don't mind.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Don't worry about your reward, captain. You will get it. We have set a price on Bartolomeo the Portuguese's head - one thousand five hundred doubloons. Lieutenant! Bring the captain his reward!";
			link.l1 = "Hm... Seems that Hugo lied to me about two thousand doubloons... Fine then.";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "And now, captain, would you be so kind as to transfer the Portuguese to the Company. We just can't wait to have a talk with him.";
			link.l1 = "Sure, mynheer, send the barque to my ship.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
