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
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Greetings, Father. Father Superior "+sld.name+" of the church of Willemstad sent me. You told him about strange sightings in a cave in Cuba.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "I have visited the cave in the jungle, father.";
				link.l1.go = "caleuche_4";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "caleuche":
			dialog.text = "Thank God he paid heed to it! Once the gossip about the living dead reached my ears, I immediately notified His Reverence Father Vincento, the inquisitor of Santiago. He promised to look into it, but so far no action has been taken! I'm afraid His Reverence has more important matters to attend to...";
			link.l1 = "I'll look into it myself. Besides, all these rumours are nothing but the ramblings of drunken hunters - that's why the Inquisition hasn't taken them seriously. I'll head into the jungle to see it with my own eyes.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "I assure you, my son, it is crucial. The man who told me about the walking dead, I trust him with my life.";
			link.l1 = "Very well then, I will prepare for battle. If the unholy creatures have indeed taken root in the cavern, I will purge them from this world.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Go with the Lord's blessing, my son! Here, take this sanctified amulet. It will help you in your task. Go now, destroy the spawn of evil!";
			link.l1 = "Until then, Father "+npchar.name+". Once I'm finished, I'll return to you immediately.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("You have received a church amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				AddLandQuestMark(sld, "questmarkmain");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "What have you seen, my son? Were our fears unfounded?";
			link.l1 = "I'm afraid not, Father "+npchar.name+". The cave was crawling with the undead, but with God's help I emerged victorious. They will not trouble anyone anymore.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Praise the Lord! You are indeed His chastising sword, my son! Please allow me to express my deepest gratitude on behalf of the entire parish of Havana. Please, accept these sanctified amulets as a token of gratitude. You will surely find them useful on your perilous journeys.";
			link.l1 = "Thank you, Father "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "Additionally, I'll make sure both commoners and noblemen know about your heroic deed, and I will pray tirelessly for you day and night.";
			link.l1 = "Thank you, Father. I also have one more question to ask.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Ask, my child.";
			link.l1 = "Tell me, Father "+npchar.name+", did a man by the name of Joachim Merriman arrive in your town recently? Middle-aged señor, a Portuguese with a moustache, imperial beard and piercing eyes?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Neither the name nor the description rings a bell, I am sorry. Who is this man?";
			link.l1 = "Merriman is a warlock. The Inquisition has been hunting him for a very long time. Father "+sld.name+" and I suspect that the emergence of the living dead in Cuba is his doing. Not long ago, he had been living in Willemstad, then he suddenly disappeared. Shortly after, the woman who was accommodating him was turned into a walking skeleton.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "What a nightmare! I will immediately inform the inquisitors, Father Vincento himself! He must know what's happening here! Tell me, my son, do you think the people who have gone missing in the jungle...?";
			link.l1 = "Indeed, I'm almost certain that those living dead in the cavern were your former citizens. I want to seek out this Portuguese on Cuba and bring him to heel! That scoundrel managed to get hold of an old heathen relic - a jade skull of Yum Cimil. I'm afraid that with the artifact and Indian witchery, Merriman will cause even more trouble if nobody stops him anytime soon.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Do you believe the undead will rise again?";
			link.l1 = "Almost certainly. I am not sure what drives him, but surely his aspirations are far from virtuous.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "May the Almighty have mercy on us! Seek him out, my son! I permit you to take any measures against him in the name of our Holy Church! I will immediately dispatch a messenger to Santiago with a report for Father Vincento.";
			link.l1 = "You do that. Farewell, Father "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddLandQuestMark(characterFromId("Havana_CemeteryMan"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
