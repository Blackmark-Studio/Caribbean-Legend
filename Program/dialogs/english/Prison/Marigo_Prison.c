// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I am listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "You have Simon Morelle under arrest here. He is a smuggler whose schooner was sunk by a patrol not long ago. May I see him?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Officer, I was sent here by the mynheer governor of Philipsburg. He asked me to raid the island and its waters in search of English spies. His Excellency also told me that you could provide me with useful information.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Officer, I've found the missing patrol. I've also found the British spies. They are here on the island.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "Me again, officer. Did you detain the spies?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "And why do you need him, sir?";
			link.l1 = "I want to tell him that he is a damn bastard and a scoundrel. I hope it will help him when he stands on the gallows.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "Ha-ha! You've got a sense of humour, sir... Well, two thousand pesos and you can move along.";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "Take it, officer. Thank you!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... You know, I've changed my mind. I'd rather waste my money in the tavern.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "You're welcome... Move along!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "As you wish, you won't get such an offer next time.";
			link.l1 = "I don't need it anyway. See you, officer!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Useful? Ha! On second thought, wait. I do have something useful to tell you. One of our patrols has gone missing in the jungle. They were supposed to be back in their barracks by now, but it seems they prefer the company of parrots instead. Or perhaps something really has happened. If you find them during your searches, please tell them to come up with a decent excuse for their delay, or else they won't like the consequences... The patrol's commander is called Jannes Hoffman.";
			link.l1 = "Is that all, officer?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Yes, damn it. I'm sorry, but I have nothing else to tell you. Good luck, captain.";
			link.l1 = "Thank you...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "What?! I hope you're not joking. Give me a report!";
			link.l1 = "I met a patrol near a cave in the jungle. They stopped me and asked where I was heading and why, then let me go. Damn me, if those weren't the Brits disguised in Dutch uniforms! I also saw something curious in the jungle which looked exactly like a bunch of naked men hidden in bushes. I assume the British raiding party had disarmed your patrol and taken their uniforms.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "As you understand, I didn't risk fighting a squad of trained redcoats, so I rushed to you with a report instead.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "Well, well... A cave, you say? How many did you count?";
			link.l1 = "Five men. And yes, I think they went into that cave.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "I am sending a squad to the cave immediately! Captain, if the men you met are really British spies, you will receive a well-deserved reward. You are free to join the squad if you wish to assist the authorities in detaining those bastards and receive an extra reward; these are the governor's orders, after all. So, are you coming along?";
			link.l1 = "No, officer, chasing spies is your job. Make sure you send a well-armed squad, these scum are too dangerous...";
			link.l1.go = "FMQN_7";
			link.l2 = "I think I can do that. Your men will find the spies faster with my help.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "Your choice, captain, I'll take your advice into account. Come see me tomorrow to hear about the results of our operation.";
			link.l1 = "See you tomorrow.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "Your information was correct, captain. We found those bastards inside the cave. They showed no intention of surrendering and engaged in a fight. As a result, we eliminated all of them. We've also found the missing patrol. They are alive and well, although a bit beaten... Thank you, captain, on behalf of all good citizens of Philipsburg. Your vigilance will be rewarded as promised. Please, take it.";
			link.l1 = "Thank you!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "You are always a welcome guest on Sint Maarten. Now, please excuse me, I have other matters to attend to.";
			link.l1 = "Me too. Farewell.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Very well. Your help is greatly appreciated. Go to the city gates, the punitive squad will be assembled there in an hour.";
			link.l1 = "A small piece of advice, you should send the best soldiers you have for this mission. Those spies are dangerous.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "Don't worry. I am sending our most experienced soldiers under the command of Officer Hans Shulte - the master swordsman of Philipsburg.";
			link.l1 = "Great! Let's not waste any time then.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
