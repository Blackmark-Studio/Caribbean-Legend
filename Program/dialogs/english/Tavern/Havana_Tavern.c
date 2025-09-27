// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the rumours of "+GetCityName(npchar.city)+" at your service. What would you like to know?","We were just talking about that. You must have forgotten...","This is the third time today you've brought up this question...","You're repeating yourself like a parrot...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, "+NPChar.name+", maybe next time.","Right, I've forgotten for some reason...","Yes, it really is the third time...","Yup...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Has Francois Gontier happened to stop by your town by any chance? He has a corvette '"+pchar.questTemp.Slavetrader.ShipName+"', just in case... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "Tell me, mate, where can I find Don Diego de Montoya? Am I late? Has he already departed for the Main?";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Listen, has a man by the name of Joachim Merriman stopped by here? A middle-aged doctor, Portuguese, with a moustache, imperial beard, and piercing eyes? Perhaps he wanted to rent a room?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "Aha, that gloomy fellow? Yes, he's stopped by my place. I'll tell you something: he had an appointment with Oregon-and-Haskon. He applied for a patent. But it didn't work out for him and he left.";
			Link.l1 = "And where did he sail off to, do you know? I've been chasing after him since Porto Bello and I just can't find him.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "What do you need from him? He's afraid of outsiders, always hiding from everyone; as soon as he sees an armed stranger, he grabs his sword. He only walks around surrounded by four guards. Are you, by any chance, the one he's so wary of?";
			Link.l1 = "Lord, people keep saying that again and again! What, do I look like a killer? He's an old friend of mine, I'm just in a hurry to pass on some news to him. He'll be quite overjoyed to know there's no need for him to hide any longer—nobody's looking for him.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "No need for him to hide? Ha-ha-ha! Just one day before his departure from Havana, a whole pack of hoodlums tried to kill him in the jungle... Of course, he had his own men, and they turned them into mincemeat in a second. And here you are saying...";
			Link.l1 = "Oh, come on. It was probably just some local bandits trying to get his wallet. You know yourself how many scoundrels are wandering around the jungle. So where did he go?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "Well, after he was sent far away and for a long time from the residence, he kept harping on that he'd turn himself in to the frog-eaters, to his countrymen. He has set off to Tortuga, to some d'Ogeron... He also muttered something about his lover, but I couldn't quite understand him.";
			Link.l1 = "So, Tortuga? Excellent! I hope I'll catch him there. Thank you, "+npchar.name+", you've been a great help. Bye.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "Hm... And why would a Frenchman be interested in Don Diego, huh?";
			link.l1 = "The fact that I'm French is irrelevant. What matters is this document signed by the Inquisitor. Have a look... do you see now? I have an urgent message for Diego.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "A-ha, so you work for His Reverence, Father Vincento? This changes things. Don Diego de Montoya left two days ago with his squadron, but soon returned on his courier lugger. One of his ships foundered on the reefs south of Cuba, so he has been buying repair materials just today\nCheck the bay to the south, you will find a ship there and the man himself. I doubt they've already managed to fix the holes.";
			link.l1 = "Thanks, mate! You've been a great help!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Not at all, any time. I'm always happy to help a Jesuit brother.";
			link.l1 = "Aye, pax vobiscum and all that.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "The Devil knows, pal. He might have arrived, but I don't know about it. Sorry.";
			link.l1 = "I see. Pity. I will continue my search...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
