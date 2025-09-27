// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("The town is on alert. Seems like it's time for me to take up arms too...","Aren't you being chased by all the town's guards? To me, soldiers!","You won't find shelter here. But you will find a few inches of cold steel under your ribs!"),LinkRandPhrase("What do you want, scoundrel?! The city guard is already on your trail, you won't get far, "+GetSexPhrase("dirty pirate!","scoundrel")+"!","Stop! "+GetSexPhrase("Dirty killer! Guard!!!","I am not afraid of you! Soon you will be hanged in our fort, there's no place to hide...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Seems like you're tired of living...","And why don't you want to live in peace, citizens..."+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Go to hell!","There are only a few seconds left for you in this world..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "A-a-ah! Ah, it's you... Who are you? What brings you to the cemetery?";
				link.l1 = "My name is "+GetFullName(pchar)+". And who are you, and what are you doing here? And why are you so frightened?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "So, how was it? Did you check? Do you believe me now?";
				link.l1 = "No, I haven't gone down to the crypt yet. Wait a bit longer, I'll check everything.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "So? Did you take a look? Did you see it?";
				link.l1 = "Yes, I did! You were right!";
				link.l1.go = "Lantern_10";
				link.l2 = "It wasn't quite what you thought.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Hello, sailor! My name is "+GetFullName(npchar)+", and I am the only living soul here. Actually, we're all still going to die, ha-ha-ha! Why did you come?","Hello! I haven't seen a living man in a long time... Allow me to introduce myself - "+GetFullName(npchar)+", and this cemetery is my last refuge. Apparently, I will be buried here. How can I help you?");
				link.l1 = "Hello, "+npchar.name+"! My name is "+GetFullName(pchar)+", and I am a captain. I walked through the jungle and came here. Thought I'd take a look inside this comfortable house, to see who is bold enough to live here...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, my old friend, Captain "+GetFullName(pchar)+"! Come in, come in!";
				link.l1 = "Welcome, friend! Very glad to see you. Do you ever see dancing skeletons at night and dead people with copper coins on their eyes in your dreams?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "And why should I be afraid, captain? It's the living we must fear, not the dead — they don't bite. Eh! Once, I had quite a different life, and now I'm the watchman of this cemetery. I look after the graves. And sometimes I trade in odd bits as well...";
			link.l1 = "And what goods do you trade in, tell me, please?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "What brings you to me this time?";
			link.l1 = "Show me what you have for sale today.";
			link.l1.go = "trade";
			link.l2 = "I want to ask you a question...";
			link.l2.go = "quests";
			link.l3 = "Nothing serious. I just came to greet you.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "I have a lot of free time, so I like walking in the jungle to collect useful plants and interesting stones. Then I sell them in town. They don't fetch much, but it's better than nothing. And I get all sorts of things from my friends...";
			link.l1 = "Friends? You mean, you resell what others bring you?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... No, they give me everything free of charge. Who could be friends with a cemetery watchman, if not the dead?";
			link.l1 = "Wha... Do you rob dead bodies?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "I don't rob; I just take things off those who don't need them anymore. Many different people are buried here-some unknown and not from our lands. The commandant brings a dead body from the town and says: 'This is for you, "+npchar.name+", send him on his final journey.' Homeless, hanged pirates, bandits killed by guardians-all are buried here. And old "+npchar.name+" buries their bodies on a Christian custom.";
			link.l1 = "I see. Well, money is money, show me what you have.";
			link.l1.go = "trade";
			link.l2 = "Understood. I must go. It was a pleasure meeting you.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("And you, "+GetFullName(pchar)+", you are a thief! Guards!!!","What the hell! I looked away for a moment and you're already trying to steal what belongs to me! Hold the thief!!!","Guard! Robbery!!! Grab the thief!!!");
			link.l1 = "Oh hell!!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "Phew, so you're just a traveller... My name is "+GetFullName(npchar)+", I am the caretaker of this godforsaken place.";
			link.l1 = "Why do you feel that way about the cemetery? On the contrary, it is from here that our Lord takes the righteous after their burial.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "But the unrighteous, apparently, remain here after burial! For the last couple of nights, there's been some noise coming from the crypt. And the moans are so chilling they give me shivers... It seems a lost soul can't find peace! Now I only sleep during the day - at night, I can't leave my post or get any shuteye...";
			link.l1 = "Noises? Moans? But there's no one there except the dead.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "That's what I'm saying, you know? You'd better get out of here before the ghost senses you... Otherwise, you won't be able to sleep, just like me.";
			link.l1 = "Hm, yes, I think I'd better leave this place.";
			link.l1.go = "Lantern_04";
			link.l2 = "Maybe I can help you? Let me look into those strange noises tonight.";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "Are you out of your mind?! I see you have a weapon, but how do you plan to fight the undead with it? And if you end up kicking the bucket there, what then? The ghost will roam free, and it might even raise you as its servant!";
			link.l1 = "Well, that's just superstition...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "What superstition? This is not the pious land of Europe, damn it... The natives, those red-skinned folk, they can conjure up anything - and now we have to live here!";
			link.l1 = "Still, let me try. I'll wait until nightfall and then go down to the crypt.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "Fine, do as you wish. But if you don't return by sunrise, I'll lock everything up, barricade it, and get out of here on my own! Whether it's swabbing the deck as a sailor or hauling boxes as a dockworker - I won't come back here anyway!";
			link.l1 = "Just calm down... Everything will be fine.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "Wait... Take this lantern. I have a spare one. You'll need it there. It's pitch dark!";
			link.l1 = "Thanks, a lantern will indeed come in handy in a place like that.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern' received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "Right? What was there? Tell me!";
			link.l1 = "There was the restless spirit of a woman! Luckily, I had the local priest bless my blade to smite the wicked, so everything worked out. That spirit won't bother you anymore.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "Oh Lord, save our sinful souls! I warned you! And you didn't believe me!";
			link.l1 = "Yes, and I sincerely regret that. But now everything is fine – I sprinkled this place with holy water, and no spirit will dare rise from the grave. You can sleep peacefully.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "Thank you so much! You have no idea what this means to me! Here, please take this. It's not much, but I can't let you leave without a reward.";
			link.l1 = "Thank you, I can't refuse. Good luck to you!";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "No? Then what the devil... I mean, what in God's name, happened there?";
			link.l1 = "There was no ghost at all. A young couple chose this crypt as a place for their meetings. Their parents are against this union, so they were looking for a place to be alone.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "Alone?.. Why, those youngsters! Let them try coming here again! I'll either chase them both away with a whip or lock them up in the crypt so they stay there!!!";
			link.l1 = "They won't come back here anymore. I told them that their little escapades really scared the local guard. They meant to do that. And by the way, the lock on the door is broken anyway.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "No problem, I'll replace it. But if I ever catch them...";
			link.l1 = "Don't be so angry. We've all been that age. They didn't come here because this was the best place for courting.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "Fair enough... Oh well, Lord be with them. Thank you for not leaving an old man in trouble. Here, please take this. It's not much, but I can't let you go without a reward.";
			link.l1 = "Thank you, I can't refuse. Good luck to you!";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}
