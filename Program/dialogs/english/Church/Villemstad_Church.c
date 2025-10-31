// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+GetSexPhrase("my son","my daughter")+"?","Ask away, I'm listening..."),"I am listening, speak now. "+GetSexPhrase("my son","my daughter")+"...","For the third time, "+GetSexPhrase("my son","my daughter")+", ask for what you need.","A clergyman has a lot of work and you are distracting me, "+GetSexPhrase("my son","my daughter")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","Not at this time, padre..."),"I have nothing to say, my apologies.","I'll ask, but later. Forgive me, father.","Pardon me, holy father...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "Excuse me, Father, one of the clergymen from your parish asked me to investigate the house where Joachim Merriman was renting a room...";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "So? Have you been there, my son?";
			link.l1 = "I have. But honestly, it would've been better if I hadn't. I was attacked by a skeleton with an enormous axe in the upper room. I managed to come out victorious, although it certainly wasn't easy.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "My Lord, have mercy on our souls! My worst fears have come true!";
			link.l1 = "That's not all, father. When I finally put it down, it screeched and sounded like a woman. When I looked through the bones I found some jewellery, so it's safe to assume it was the landlady gone missing.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "(crosses himself)... Poor servant of God, may the Lord grant her soul rest...";
			link.l1 = "It seems Merriman truly is a warlock. I have no idea how anyone could turn a living man into such an abomination.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Joachim Merriman is a very fearsome warlock, my son. I knew him in Europe, but at the time he wasn't capable of anything like that. Here, in the Caribbean, he managed to get his hands on something which gave him supernatural powers.";
			link.l1 = "You knew Merriman, Father?";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "That I did. Back then I was just a humble priest in one of Lisbon's parishes. Joachim Merriman was a wealthy nobleman, and at some point he became interested in old manuscripts and scrolls brought by sailors from distant lands. He also began to study alchemy, but after some time he went into seclusion.\nPeople saw flashes of light in his house; sometimes they could also smell something strange. Then they saw him in the cemetery at nights. Once they saw him digging out a fresh corpse and bringing it to his home. And when patience ran out, local father superior contacted the Inquisition.\nWhen the guards breached the door of Merriman's house, Joachim was not there - he had escaped through a secret passage. They found a lab in the basement, and even the seasoned soldiers were shocked and sickened by what they saw. Whole rotting and dismembered bodies, human and animal skeletons, strange things... Fear and hatred for Merriman was so significant that his house was demolished in an instant.\nMerriman disappeared without a trace. The Inquisition began to search for him, sentencing him in his absence to burn at a stake as a dangerous warlock. But they never found him. And now, after all these years, I saw him again on the streets of Willemstad.";
			link.l1 = "Why didn't you tell the inquisitors?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "My son, don't you know that our church is at odds with the Inquisition? I'd prefer to steer clear of Father Vincento and his ruffians.";
			link.l1 = "I understand. Father, I think I know where Merriman drew his power from. He's gotten hold of an ancient artifact, a jade skull of Yum Cimil, an ancient god of death worshipped by the Indians of the Chavin tribe.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Hm, Merriman was known for performing sorcerous rituals and experiments on corpses, so it very well might be true. I thank God that this terrible man has left Willemstad and that you have destroyed the devilish seeds he attempted to plant here. We are deeply indebted to you, my son. Please accept these sanctified items as your reward.";
			link.l1 = "Thank you, Father";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "But that was not the end of our troubles, my son. Recently, I received a letter from "+sld.name+", father superior of the church in Havana. He brings terrible news. In a cave in the Cuban jungle, hunters have seen terrifying abominations, the walking dead. And it's all the more troubling considering that recently, people have gone missing after venturing into the jungle.";
			link.l1 = "Hmm... are you implying that this is Merriman's work, too?";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "I don't know what to think, my son. But if that black witcher has become so powerful, all the inhabitants of the archipelago are in grave danger. Only God knows what this servant of the devil could have in mind\nI do hope that Father "+sld.name+" was wrong, but anyway - please go to Havana and talk to him. I have prepared a trading license for you, which is valid for a month. With it, you'll be able to enter the port of Havana without any difficulties.";
			link.l1 = "Alright, Father. I'll head to Havana.";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "I don't know what to think, my son. But if that black witcher has become so powerful, all the inhabitants of the archipelago are in grave danger. Only God knows what this servant of devils might have in mind.\nI do hope that Father "+sld.name+" was wrong, but no matter – I ask you to travel to Havana and speak with him.";
			link.l1 = "Of course, Father. I'll head to Havana right away.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "I am glad that you're a true son of the Church. I will pray for your health and well-being day and night. Go with my blessing. May the Lord strengthen you in your struggle against these unholy powers.";
			link.l1 = "Thank you, and farewell, Father.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
			AddLandQuestMark(characterFromId("Havana_Priest"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
