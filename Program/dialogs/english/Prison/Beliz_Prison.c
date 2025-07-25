// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I am listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "I heard about a gang of thieves and robbers operating in the vicinity of Belize and in the town itself.";
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "I can give you information about the gang.";
				link.l1.go = "caleuche_3";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "What news about the gang? Have you seized them at the cave?";
				link.l1.go = "caleuche_7";
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "The whole town seems to be celebrating the capture of a pirate. Can you tell me more about it?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "Gladly! This isn't just any pirate - it's that scoundrel, Matthew Lutter.";
			link.l1 = "Everyone's luck runs out eventually.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "You're not English, and you don't look like a merchant, so I can see why you're not as excited. Lutter has terrorized these waters for years, attacking both us and the Dons, but more often us. He always managed to evade our coastal patrols, sailing his corvette, the Seagull, which was once the fastest ship in the Archipelago. How he came to command a warship like that, only God knows.";
			link.l1 = "So it's true he lost to a merchant? On a corvette? Sounds unbelievable.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "As strange as it sounds, it's true. A merchant, and a Spaniard at that! Our navy could learn a thing or two from him. Captain Sotta, realizing there was no escape, prepared for battle...";
			link.l1 = "Quite the unusual character, this Sotta.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "Perhaps. He had his ship refitted to carry as much cargo as possible, which made escape impossible. Knowing the pirates were after his cargo, he pretended to be adrift. And then...";
			link.l1 = "...he raised the sails at the right moment?";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "Ha! No, he fired a broadside of grapeshot at point-blank range as Lutter approached, and then boarded the pirate himself! When he found out who Lutter was, he handed him over to us. A true hero, a man of honor!";
			link.l1 = "It wasn't just honor driving him - there must have been a reward for catching the Windbag.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "Sometimes profit aligns with good intentions. But yes, he was handsomely rewarded. His Grace loaded him up with expensive goods as a token of our city's gratitude before he sailed.";
			link.l1 = "I wish I'd met him - I'd like to shake his hand. Tell me...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "Your source was telling the truth. These bandits have become a real pain in the ass for us. Do you want to tell us anything about them?";
			link.l1 = "Beside that they've stolen one important thing from me - nothing really. I hoped that you would be able to tell me something about them. Maybe, one of them was caught and he is now ready to testify...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Sorry to disappoint you, captain, but I have no information about them. I only know that they are hiding somewhere in the jungle, and they have accomplices in the town, that's all. Now, if you learn anything new about them, please tell me immediately.";
			link.l1 = "Alright, officer. I'll do that.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "in three days";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "on the day after tomorrow";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "tomorrow";
			dialog.text = "Are you serious, captain? Speak, I am all ears.";
			link.l1 = "I have found one of their informers in the town. He told me that their gang is preparing to attack a ship, which is supposed to arrive to the cove of Chetumal. The villains are gathering "+sTime+" at night near a cave not far from Belize. To get there, just need to take the left path at the fork in the jungle.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "At the cave? Excellent news. I will order to prepare an ambush for these villains. If you got it right and your informer was telling the truth, we will catch these bastards, and then I'll solicit before the governor to reward you.";
			link.l1 = "Thanks! I'll come to see you, when it's over.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Alright. That's fine.";
			link.l1 = "See you soon, officer.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddQuestRecord("Caleuche", "15");
			pchar.questTemp.Caleuche.Bandos = "comendant";
			pchar.questTemp.Caleuche.BelizChance = hrand(3);
			SetFunctionTimerCondition("Caleuche_BelizRegard", 0, 0, 3, false); // таймер
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "We prepared a warm welcome for the scoundrels, ha-ha-ha! If only you could have seen their faces! We took everyone, including the ringleader! Some attempted to resist, but they were eliminated by our brave soldiers.";
				link.l1 = "Excellent news, officer! Now the citizens of Belize can finally sleep calmly.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "Hmm... My soldiers had been waiting for them at the cave for the whole night, but no one ever showed up. The sergeant was really furious. It's good that he still didn't catch you.";
				link.l1 = "Goddammit! That just can't be! At which cave had you set the ambush? There are two of them!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "Where you told me. At the one to the right at the fork...";
			link.l1 = "IT IS THE ONE ON THE LEFT! To the left of the fork you imbeciles!";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "But I perfectly remember that you said 'to the right'.";
			link.l1 = "Oh my Lord! To the left! I said, TO! THE! LEFT! You let them slip away, and it was your fault!";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "Then you must have mumbled something under your nose. I can hear quite well, you know.";
			link.l1 = "Alright, officer, I am not going to argue. I wanted to help you, but one can't help those that cannot help themselves. Farewell.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "I reported to the governor of your role in the elimination of the gang. He valued your contribution very highly and authorized me to present you with a reward: a monetary premium and a trophy arquebus.";
			link.l1 = "Thank you!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received an arquebus");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "Thanks for the service, captain! If only all our citizens were as conscientious as you, we'd have defeated the crime once and for all long ago! Best of luck to you!";
			link.l1 = "Goodbye, officer! Best of luck to you in your service!";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
