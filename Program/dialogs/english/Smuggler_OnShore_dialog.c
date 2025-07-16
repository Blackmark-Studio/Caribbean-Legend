void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;

				// поиск мин.  те старшего класса
				for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				}
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("Weren't you told not to come here on such noticeable ship! Why don't you bring a pair of man-of-wars? Get lost and come on a smaller ship.", 
						"Get out! Or we will give you away to the patrol by ourselves.", 
						"Go to your boat and get away.",
						"So tired of you...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Alright, alright I am going to change my vessel.", 
						"Calm yourself, I am on way.",
						"Damn, I thought that it will work...", 
						"Yes, I am really stubborn!", npchar, Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("Hey, what are doing here, "+ GetSexPhrase("pal","girl") +"?",
                                          RandSwear() + "What's your business here?!");
				Link.l1 = "Relax, mate, let's trade!";
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "I am here by the orders of the governor of " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "! Drop down your weapons and follow me, you're arrested!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("Ah, at last! We have been waiting for you. Let's move, it's time to sail off.", "Let's do it fast. There are patrols everywhere. We need to get away from here!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "I am here by the orders of the governor of " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "! Drop down your weapons and follow me, you're arrested!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "And who are you? We were talking about only one passenger!";
						Link.l1 = "Oops..";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Who are you? We have been waiting a passenger, not a captain.", "Get lost! Don't come back until you get rid of your ship.");
						Link.l1 = "Crap!";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "Shit, patrol! We don't know you and you don't know us.";
							Link.l1 = "Fine...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Thanks for your assistance. We won't forget that. Let's sail now.", "Well done! Good fighting. Let's move.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "I am on my way.";
					Link.l2.go = "Exit";
					//а это патруль... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//поместим Грея в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						
						SetLaunchFrameFormParam(".. " + sti(Pchar.GenQuest.contraTravel.destination.days) + " days passed." + NewStr() + "Smuggler's ship deck.",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
                    // если таможня уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+ "Patrol! We don't know you and you don't know us.";
						Link.l1 = "Fine!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "Get lost! We will rip your guts if you spoil our deal.";
						Link.l1 = RandPhraseSimple("You dare to threaten me mutt!?", "You will choke on your words!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "Don't worry, I know what business is. Bye.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "Are you carrying it on your backbone? Where is your ship?";
			Link.l1 = RandPhraseSimple("First, I'd like to see if there is any catch in it.", "Didn't want to risk the ship. I prefer seeing everything with my own eyes.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "The deal is over!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "We are honest men and we won't cheat on you. Bring your ship here, just don't make patrols follow you.";
			Link.l1 = "Fine. Wait me here.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "Over? You are probably kidding me!";
    			Link.l1 = "I am serious.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "Fine then. We've had good trades today anyway.";
    			Link.l1 = "Correct!";
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "You bastard! You can't fool us just like that! You'll pay for it with your own head!";
					Link.l1 = "Doubt it!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "You won't get away with it!";
					Link.l1 = "Go bark somewhere else, dogs!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "You'll regret that!";
				Link.l1 = "You talk too much.";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			//счетчик подстав по "метро"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = "You will answer for that!";
			Link.l1 = "Then you are all dead. I've got a clear order - to eliminate all of you if you will resist.";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("Heard the latest news? The local smugglers were rounded up by a patrol not long ago. And you know what? Captain who had a deal with them escaped!" +
				"He had dashing lads in his crew and the whole patrol was killed. And our local smugglers just vanished. There was nothing found on the shore. No goods, no stash and smugglers. See, how they do their business here!", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
            // таможня на суше
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 100);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// сама торговля -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "And what are you doing here? You have nothing to sell! Every good in your cargo can be sold in the town!";
				Link.l1 = "No luck this time.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "I see.. You know, we'll take your goods for free. I doubt that you'll be able to complain anyway.";
        				Link.l1 = "Try it, scum!";
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// море и солдаты на суше НЕЗАВИСИМЫ!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// при убегании от патруля на карту - корабли трем
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// установим окружение <--
				dialog.text = "Alright let's see what you've got.";										  
				Link.l1 = "Show us what you've got.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "I have changed my mind.";
    				Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			// belamour legendary edition опасный груз
			pchar.GenQuest.Smugglerzpq = npchar.id;
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
		// belamour legendary edition опасный груз -->
		case "SmugglerZPQ":
			dialog.text = "Good deal, captain! If there are any other interesting products - contact us!";										  
			Link.l1 = "I agree, I am also satisfied with our trade. Oh, if only I could buy all the goods at such a good price...";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "Why do we need to buy ordinary goods at such prices, if they can be legally purchased in a store? But do not be discouraged: in fact, any product can be sold, even ordinary gunpowder! You could sell at a sky-high price one just needs to know the place.";										  
			Link.l1 = "Come on. Who will buy gunpowder at a sky-high price?";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "Well, that's what I told you, hehe ... Although ... You know, there really is such an opportunity to sell gunpowder for a fortune, but this deal still doesn't shine for us, for it you need to have a fairly good reputation, and we, as you understand, are not nobles.";										  
			Link.l1 = "Well, maybe I can check it out. I can be good and kind when needed. Can you tell me about the deal?";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "Everything costs money in this world, captain, even information. I would even say, especially information. I propose this: I will give you this tip for a symbolic amount of ... let's say five thousand pesos. Will that suit you?";										  
			Link.l1 = "To pay five thousand pesos for dubious information about where you can sell gunpowder for a high price? No, I think I can somehow live without this tip.";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "I think I can make more than just five grand on this deal. Fine then, I agree.";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "It's up to you, captain. In any case, we had a good deal. Good luck... and don't run into a patrol!";										  
			Link.l1 = "You too. Goodbye.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Excellent, captain! You are an amazing customer you know. So listen. I was whispered in my ear that in some of the Spanish cities on the Maine there was a problem with gunpowder. Whether it's tropical showers, or something else - in general, in the fort that guards the colony, there are very few reserves. And the commandant of this fort is looking for someone who could help him in this difficult situation.\nThere are only two problems: first, this is a delicate matter, and the commandant will not talk about it with any crooks, and secondly, we are talking about a very large batch - not every ship will fit so much gunpowder, so you might need a fleet. Also not every captain will agree to turn his vessel into a floating bomb that can easily destroy an entire island if it's hit by a stray cannonball.";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "Sorry, but I already know about this deal. Anyway, the deal is worth more than money, so you deserve five thousand.";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "Valuable information, thank you. If I'm on Maine, I'll ask the local commandants of the forts about their misfortunes. And somehow I hope I will deal with these problems or abuse them he-he.";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "That's how it happens. In any case, we had a good deal. Good luck... and don't run into a patrol!";										  
			Link.l1 = "You too. Goodbye.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "That's how it happens. In any case, we had a good deal. Good luck... and don't run into a patrol!";										  
			Link.l1 = "You too. Goodbye.";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
