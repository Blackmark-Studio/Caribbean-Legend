// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?","What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind.'","I've got nothing to say now.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "Have you, by any chance, crossed paths with Captain Edgardo Sotta? Can you tell us anything about him? He sounds like a man worth knowing.";
					link.l1.go = "Sotta1";
					link.l2 = "Aren't you going to see the execution of the Windbag?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "Tell me, have you seen the hero of the day, Captain Edgardo Sotta? I missed him, unfortunately. What's he like? I can't believe a merchant caught the infamous Windbag Matt!";
					link.l1.go = "Sotta1_1";
					link.l2 = "I see the whole town is celebrating Lutter's capture, even those who never go to sea."link.l2.go ="Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "About a month and a half ago a certain Jerome Sauvernier arrived in Belize. He was wounded in a brawl at the 'Glass Eye', but survived. Could you tell me where I might find him?";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "A month and a half ago, give or take, a gentleman appeared in Belize. His name was Jerome Sauvernier. He was searching for another man – so he must have spoken with townsfolk. Later he was injured in a tavern brawl, but fortunately survived. Can you tell me where I might find him?";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "I am trying to find a man who arrived in Belize about two months ago. His name is Jerome Sauvernier. He was looking for a certain gentleman, and I suppose he spoke with the townsfolk about it...";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Do you think I work for the secret service of "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well... no. Farewell, then.";
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
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "I didn't get to talk to him, but I saw his ship - a heavy galleon. It's dangerous to sail alone in these waters, but Sotta manages without an escort.";
			link.l1 = "Probably chasing every gold coin and cutting costs wherever he can. Well, I won't keep you. Good day.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "Aye, it's hard to believe! But don't trust everything you hear, sir. I've seen him, as clear as I see you now. It's good he caught Lutter, but why all this merchant charade? He carries himself like a soldier. I can always tell – a relative of mine served for years.";
			link.l1 = "Interesting. Well, everyone has their secrets. I'd better be going. Thanks for the insight.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "I've already seen the man. It's hard to believe this is the same pirate who terrorised our merchants for years. How did he even get his own command in the first place? I saw the soldiers escorting him - shouting, crying, laughing. A madman.";
			link.l1 = "Maybe the defeat and the reality of his imminent death were too much for him. But it doesn't matter. Goodbye!";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Yes, and I'm celebrating too - a good number of my compatriots died at his hands. The unlucky ones lost a father, a brother, a son - you get the picture. That barbarity went on for far too long! Matt must have been one of the luckiest pirates in recent years, if you ask me.";
			link.l1 = "Luck always runs out sooner or later. See you around.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
		
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "I don’t know such a man, sir. Brawls in the tavern are near daily business, and remembering every fellow who got hurt is a thankless task.";
    		link.l1 = "I see, thank you. All the best.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "Sauvernier? A Frenchman... Yes, there was such a one. He came to me for help, but there was nothing I could do for him. I have not seen him since, forgive me.";
    		link.l1 = "Thank you. Well then, I shall continue asking around.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_3":
			dialog.text = "Mister Jerome! Of course, of course, I remember him. He was wounded in a tavern brawl. Since then he hardly leaves his house, tending to the wound on his leg.";
			link.l1 = "And where is this house?";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;
		
		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "It’s right here, quite nearby, next to the port authority. The house with the red roof. That’s where you’ll find him.";
    		link.l1 = "Thank you, you’ve been a great help! All the very best to you!";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
