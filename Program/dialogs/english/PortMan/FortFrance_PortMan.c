// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?","What do you want, "+GetAddress_Form(NPChar)+"?"),"You've already tried to ask me a question "+GetAddress_Form(NPChar)+"...","You've brought up that question for the third time today...","Look, if you have nothing to tell me about the port's affairs then don't bother me with your questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.","I've got nothing to talk about."),"Never mind.","Indeed, the third time already...","Sorry, but I'm not interested in the port's affairs for now.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "Sir, I am looking for a job. But not as a porter, something more befitting my rank. A mission, a service, something involving delicate matters... I will take any assignment you have.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "I was told you had a letter for me. The name is Captain Charles de Maure.";
			link.l1.go = "LH_letter";
		}
		break;
		
		case "Sharlie":
			dialog.text = "Help? Hm. I am doing fine, thanks be to God. But one of my friends is really in need of help and it's urgent. He's going to enter the jungle alone to fight the Indians, this is absolute madness!\nI tried to reason with him, was begging him, but he didn't listen! He worries too much about his daughter and is ready to give his life for her!";
			link.l1 = "Hang on, let's start again: who is your friend, where can I find him, and what kind of help does he need?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Ah, pardon me, I am just too anxious. His name is Prosper... Prosper Troubale. He is going to die for sure! And I can't help him - I am not a soldier. His daughter is missing and he believes that the local Indians are responsible.\nImagine that, he plans to go after the wild savages on his own! They will cut him to pieces... At this moment he is buying a musket and getting ready to go out to the selva!";
			link.l1 = "You are a miserable storyteller, sirrah. Where can I find your friend... what was his name... Prosper?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "I just spoke with him and tried to make him change his mind. He's not far from the city gates, by the well, checking his musket and ammunition. Go to him and do something! If he goes into the jungle alone, he won't come back, I'm sure of it. The red-skinned devils will tear him apart...";
			link.l1 = "Stop rambling, you sound like an old woman! I'm heading to your friend right away. I hope I'll be able to help him.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "Yes, you're right - there is an envelope. Here it is, but first, you need to pay for the delivery - twelve thousand silver pesos.";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "I always suspected that your trade was originally a thief's business, but somehow I missed the mark, hm. Please, here is your money.";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "I'll come back a bit later, I think I left my coin purse at the tavern.";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
