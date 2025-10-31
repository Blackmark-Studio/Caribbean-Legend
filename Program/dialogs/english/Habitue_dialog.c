#include "DIALOGS\%language%\Common_Duel.c" //navy
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle, sStr;
	int DonationSize;
    	
	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	int d1,d2,d3,d4;
	bool ok;
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150) npchar.money = 150;
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "Drunkard type selection (beta)";
			link.l1 = "Drunkard";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Cards gambler";
			link.l2.go = "Beta_test_card";
			link.l3 = "Dice gambler";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Drunkard selected";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Cards gambler (30% to resent immediately)";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Dice gambler (30% likely to resent immediately)";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("I might be drunk, but I'm not an idiot. If I drink with you now, the soldiers will get me the next day. No way!","I am no enemy to my own town. I will not drink with you!",""+GetSexPhrase("mate","lass")+", you'd better leave this place while you still can...");
				link.l1 = RandPhraseSimple("Well, as you wish...","Heh, you know, I don't need to get drunk that much. It's not the right time for it."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ha, miss"+GetSexPhrase("ter","s")+", surely, I've heard of you, he-he. People at the taverns say you're a troublemaker and a duelist. I say our folk are not easily frightened, but no one wants to die for a cup of rum. I find it unnerving to even sit close to you, so I'd better pass.";
				link.l1 = LinkRandPhrase("Good riddance, then!","Get lost, while I'm still in a good mood...","Go, go! Get lost, fish food!");
				link.l1.go = "exit";
				link.l2 = "Wait, I wanted to ask a question...";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Don't stand in my light, I can't see the flies in the mug!";
            link.l1 = "I am not standing...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "Hic! Oh, "+GetSexPhrase("mate, you surely look like a seasoned old salt","lass, you certainly look like a seasoned old salt")+"! Perhaps you could buy me a glass of rum?";
						link.l1 = "I might be an old salt, but that doesn't mean I'm buying booze for riffraff...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "I'd gladly join your company.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "And why is that?";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("A game of cards, perhaps? A most interesting game!","I suggest we play a game of cards. What do you say?");
										link.l1 = "And why not? Sure, let's play.";
										link.l1.go = "Cards_begin";
										link.l2 = "And what are the rules of your game?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Not now.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "No, I am not playing cards with you anymore.";
						    			link.l1 = "As you say.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("A game of dice, perhaps? A very interesting game!","I suggest we roll some dice. What do you say?");
										link.l1 = "And why not? Sure, let's play.";
										link.l1.go = "Dice_begin";
										link.l2 = "And what are the rules of your game?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Not now.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "No, I am not playing dice with you anymore.";
					    				link.l1 = "As you say.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear()+" You were cheating!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Get away from my table! Now!"," Oh? What? Who's that? Hic... Get lost!");
	                        link.l1 = RandPhraseSimple("Drinking dooms your sinful soul! Come to your senses!","Don't be rude to me.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Watch your tongue, you cur! Or I'll teach you some manners.","What if I hit you on the head now, I suppose that'll help you sober up.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "I am not telling you anything, miss"+GetSexPhrase("ter","s")+"! And I don't think that anyone else will be talking to you, since that always means trouble. But you know, people tend to have short memories, so in a month or two they might forget about your adventure, if you don't remind them again, of course, he-he! Farewell, mis"+GetSexPhrase("ter","s")+". ";
			link.l1 = "Alright...";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Well, let's begin, then...";
			link.l1.go = "Cards_begin";
			link.l3 = "No, it's not for me...";
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "Let's define the bet first then (enter bet).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "I suppose I have to go.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "You are a notorious cheat. I will not gamble with you.";
                link.l1 = "It's all lies! Well, whatever.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "I see you're skint, "+GetSexPhrase("friend","darling")+". Come back when you are rich.";
                link.l1 = "Fine.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "I have already lost everything I had. Today is not my lucky day.";
                link.l1 = "Fine.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Are you laughing at me or what?! Playing for "+iLa_Puesta+" pesos?! Let's play for reasonable stakes, or I'm out!";
				link.l1 = "Yeah, you're right. We need to raise the stakes a bit.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "I've changed my mind, I'm not playing.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Playing for such huge sums? No, I'll pass, unless we change the wager.";
				link.l1 = "Yeah, you're right. We need to lower the bet a bit.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Actually, I decided not to play at all.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Alright, let's play for "+iLa_Puesta+" coins.";
			link.l1 = "Deal the cards!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "So, what is the bet? (Enter bet)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "I think I will not play after all...";
			link.l2.go = "exit_sit";
		break;
							
		case "Cards_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Well, let's begin, then...";
			link.l1.go = "Dice_begin";
			link.l3 = "No, it's not for me...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";		    
			Dialog.text = "Let's set the bet (enter bet).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "I guess I have to go.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "You are a notorious cheat. I will not roll dice with you.";
                link.l1 = "It's all lies! Well, whatever.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "I see you're skint, "+GetSexPhrase("friend","darling")+". Come back when you are rich.";
                link.l1 = "Fine.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "I have already lost everything I had. Today is not my lucky day.";
                link.l1 = "Fine.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Are you laughing at me or what?! Playing for "+iLa_Puesta+" pesos per die?! Let's play for reasonable stakes, or I'm out!";
				link.l1 = "Yeah, you're right. We need to raise the stakes a bit.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "I've changed my mind, I'm not playing.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Playing dice for such a huge sum? No, I'll pass, unless we change the bet.";
				link.l1 = "Yeah, you're right. We need to lower the bet a bit.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Actually, I decided not to play at all.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Alright, let's play for "+iLa_Puesta+" coins per die.";
			link.l1 = "Let's roll!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "So what’s the bet? (Enter bet)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "I think I will not play after all...";
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // КОСТИ <--

		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "Well, h-hic! Things are good. Hic! You don't see it coming. Hi-ic! This rum is fine. Jamaican black rum. hic!\nHere, pour yourself a drink!";
			link.l1 = "Alright, why not.";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Sorry, friend, I have to go.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Mugs and faces come and go... Hic... Right up until I hit the floor. I'm drinking all the time... Hic! Where's the booze... And what's the rhyme...";
			link.l1 = "The booze is here and the girls are fine, all want a buccaneer, but only rum seems to be mine.";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "I have no time for this.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "When you're sad, don't try to think, come around, and let us drink! Everything will surely be fine, I'm your friend, and you are mine!";
			link.l1 = "To have a friend sure is great, when you are gone he will wait, with a friend there is no hate, but when rum is gone there is just a debate. So let us drink, mate, before I go and be late... ";
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase("Hic! Now that's better! That's much better! So? Will you buy me some rum or what?","Sit down, "+GetAddress_Form(npchar)+", let's knock back a cup of good old Jamaican rum. That's never bad for your health. And if you're interested in what's going on - you'll never find a better place than this tavern, I assure you. A bit of money, a couple of cups of decent rum - and you'll learn whatever you needed to know, and even more, trust an old patron...","Heh, please, have a seat, "+GetSexPhrase("my good friend","miss")+", let's have a drink... Why not enjoy a drink in good company? You can hear a lot of interesting things if you're patient and drink slowly, in small sips... There are captains boasting about their adventures, and many others blurting out important things when they've lost control... Many people spend their time there, and many have something to tell, trust me, "+GetSexPhrase("my good friend","Miss")+".");
			link.l1 = "And why not! Bartender! Rum for the two of us!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "Sure! Have you heard... bandits even plunder churches!";
				link.l1 = "Well, that sounds like pirates, who else...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "What pirates? Just your ordinary landlubbers, and surely the damn local ones... If they were visitors, they wouldn't have known when the church coffers were full. And they would hardly have got into that mess, anyway.";
				link.l1 = "Daring fellows, that's for sure. They so gallantly opened a flimsy door bar...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "A-ha. And clever ones, too. Who would expose themselves in such a way?";
				link.l1 = "True. The whole parish was saving money to donate to the church, and now these clever fellows have made their fortune from it? Surely they will be caught. Everyone will be looking for them now.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "Hardly. Who will be looking for them? They just robbed the church and left the town, gone with the wind. The jungle is large, very large, you'd be searching for them in there till doomsday. And after a couple of months people will just forget all about it, mark my words!";
				link.l1 = "I don't think so. Such things cannot be forgiven.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "A man's memory is like a leaking skiff. People will forget and forgive. But God?! He sees everything. That's whom you need to fear. I say, ten years ago something terrible happened to an old mate of mine. He, too, lacked respect for the Creator, and almost went straight to the sea devil...";
				link.l1 = "Sorry, friend, I have to go. We'll talk about that mate of yours another time. See you.";
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;
			
		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");			
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("The bandits who raided the church shall be in location - " + sGenLocation + " Time to search for them - 1 day");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "Oh Francois! Sure, I remember that guy... No, I don't know. But, you know, you can ask our waitress about him. For as long as he lived here, she spent every night with him. A bitch she is, that's for sure. Perhaps he blabbed something to her.";
				link.l1 = "Thanks for the advice, mate. I'll go talk to her.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Yeah, very weird things can happen on the open sea sometimes. On my last voyage I've seen something rea-lly...";
				link.l1 = "Go ahead, tell me, just don't exaggerate too much. I'll fetch you more rum in the meantime.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "I swear to God, noble"+GetSexPhrase("sir","lady")+" - I've seen it with my own eyes... A ship was sailing, but instead of sailors there were some giant apes... or macaques... monkeys, you know.";
				link.l1 = "What?! Tell me, friend, are you drinking on watch, too?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Strike me blind if I'm lying! Have you never heard about the monkey shrimp? Damn me, shrimp ha-ha! ... The monkey ship.";
				link.l1 = "What monkey ship?";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "Oh-ho, I tell you, I saw it with my own eyes. There was a storm. Couldn't see a thing, and then the ship appeared out of nowhere. Torn sails. Her foresail was broken, as well as the mainsail, and by God, everything was shattered! And yet she was charging upwind!\nAnd there were apes on her deck... a whole lot of them, like a seal rookery! And a real gorilla was standing at the wheel! Nine feet tall, red shirt, and shark teeth instead of a cross on its chest... Eyes blazing red, fangs gleaming, it saw us and shouted something...";
				link.l1 = "You're lying through your teeth, friend. You know, you see things when you're drunk. Next you'll tell me she was the Flying Dutchman.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "No, she was no Dutchman. I'm telling you the truth! It was a barque, and on the stern there was an inscription - "+pchar.questTemp.Slavetrader.ShipName+".";
				link.l1 = "Goddamn it! I think I know what 'monkeys' you were talking about. Indeed, rum can loosen tongues - one just has to listen...";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "See - I told you! And you didn't believe me!.. Alright, let's knock back one last cup, and I'm good to go.";
				link.l1 = "Alright, thanks for an interesting story. I have to go. Good luck to you, mate.";
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;
		
		//Голландский Гамбит, против всех
		case "Lucas_Tavern":
			DelMarkInTavernHWIC();
			dialog.text = "No, captain. A sailor's life is not for me. You know, I, too, once had a ship, but... I had a stroke of really bad luck.";
			link.l1 = "Listen - I've seen an unusual ship lying offshore - 'Meifeng' is her name. I've never seen a ship like that before. Who owns her? Perhaps she's up for sale? I'd like to take a look.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ha! Hardly, captain. I don't think that Chinese fellow will sell you or anyone else his ship.";
			link.l1 = "A Chinese? There are Chinese people on Curacao? And even a captain of his own ship?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "There is, as you can see. But this is not his ship, actually – it belongs to the Trade Company. They say mynheer Rodenburg, the vice director and now acting governor, owns it.";
			link.l1 = "So, Matthias Beck has retired?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ha! Mynheer, you really should visit the land more often – or at least keep up with the news. Matthias Beck was dismissed and put behind bars until all the circumstances are clarified.";
			link.l1 = "You don't say! Indeed, I am spending too much time at sea. And when did that happen?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "Actually, just a couple of days ago. A courier brigantine arrived in port. It was not in the best shape; clearly, it had participated in fierce combat. The captain went straight to mynheer Rodenburg with his report, and in just a few hours Matthias Beck was arrested by mynheer Rodenburg and the commandant on suspicion of collaborating with English intelligence.";
			link.l1 = "You are saying terrible things. How can the governor of Curacao be an English spy?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Frankly, I can hardly believe it myself. I heard that soon the director of the Company, Peter Stuyvesant himself, will arrive here. Apparently, he will personally conduct the investigation.";
			link.l1 = "Then you are right. It can be risky to bother Mynheer Rodenburg at this time.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "Good thinking, captain! All the more so since 'Meifeng' is currently being loaded. She has just returned from a voyage to the southern coast of the Main, and soon she will set sail again. And, I tell you, strange things are going on there. Dutch sailors and Company guardsmen have been relieved of duty, and another crew is being put together. And I swear by all the cups of rum I've drunk in my life, those new volunteers are something else entirely, all pirates, bandits, and cutthroats!";
			link.l1 = "A miracle, indeed! Well, it's a pity! Such a fine ship... Well, fate decreed otherwise... Thanks for an interesting story and for the news! It was a pleasure to talk to you!";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "Well, thanks for the company and the rum, captain! Drop by again sometime!";
			link.l1 = "Of course I will!";
			link.l1.go = "exit_sit";
			AddQuestRecord("Holl_Gambit", "3-44");
			pchar.questTemp.HWIC.Self = "AttackMeifeng";
			//ставим прерывание на выход в море Мейфенг
			pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // таймер
			pchar.quest.Meifeng_fail.over = "yes"; //снять прерывание
			Group_DelCharacter("Meifeng_Empty", "Longway");
			Group_DeleteGroup("Meifeng_Empty");//удалить Мейфенг из порта
		break;
		
			//Jason --> поиск дезертира
		case "FindFugitiveHb":
			npchar.quest.fugitive = "true";
			if (npchar.location == pchar.GenQuest.FindFugitive.City+"_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
			{
				pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
				dialog.text = "Ha! "+pchar.GenQuest.FindFugitive.Name+"? I know, I know... He's very unsociable, that colleague of yours. A lone wolf, so to speak. He sails his longboat along the island's coast all day until nightfall. People think he's a fisherman, but he's actually a pearl diver... Heh! I know it for damn sure!";
				link.l1 = "Heh! So... can you tell me where I can find him?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? No, I swear I've never heard of him... But you - Hic! You can ask our bartender - he must know for sure!";
				link.l1 = "Hmm... Alright, I'll ask around some more. Well, mate, thanks for the company. See you!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Of course, I can! Every morning he can be found on the shore, at "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+". Just come as early as possible, otherwise he will set sail and you will have to wait until the next morning.";
			link.l1 = "Thanks! You've helped me a lot, friend! See you!";
			link.l1.go = "exit_sit";
			pchar.GenQuest.FindFugitive.Chance = 3; // чтобы никто больше не говорил
			AddQuestRecord("MayorsQuestsList", "12-3");
			AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen"));
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_shore";
			LAi_SetLoginTime(sld, 4.0, 6.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
		//<-- поиск дезертира
		
		// Карибские нравы
		case "trial_spy":
			dialog.text = "He was hanging about in our shipyard, asking the shipwrights about this and that. And that's what played a mean trick on him. Some people alerted the commandant about suspicious people hanging around in the town, so he detained him, and then it was found out that he was no merchant at all.";
			link.l1 = "I take it he was planning to steal some secret project from your shipwright?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "Who knows? But I am quite sure that he was interested in the galleon 'Alacantara' in the first place! Hic! I can swear to it! This ship is being equipped by Señor Governor himself, so I bet that scoundrel tried to sniff out something about her.";
			link.l1 = "Ha! That's quite likely. Surely the governor will be loading her with something valuable...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "That goes without saying! That must be something truly worth attention, I tell you! Oh, and people were saying that the fishermen have seen a foreign military ship in these waters ... a frigate, most likely. Perhaps that's where that spy came from?";
			link.l1 = "Yeah, it can be... Alright, mate, thanks for the company, but I have to go!";
			link.l1.go = "exit_sit";
			Trial_Habitue_DlgExit();
		break;
		
		case "sit_2":
			Statistic_AddValue(pchar, "TavernDrink", 1);
			AddMoneyToCharacter(pchar, -2);
			//navy --> Alcohol - rum count;
			if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
			{
				if (CheckAttribute(pchar, "questTemp.Rum"))
				{
					pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
				}
				else pchar.questTemp.Rum = 1;
			}
			else 
			{
				if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
			}				
			//<-- navy
			if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 30);
			
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
			
			// Sinistra - Квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerAlkash") && npchar.city == "baster")
			{
				dialog.text = "To your health and to your generosity!";
				link.l1 = "Mate, have you seen a Chinese man around town?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("You're a "+GetSexPhrase("real friend","great lass")+"! Nice to meet you! Cheers!","Hic! That's great rum! Hic... Cheers!","To your health and to your generosity!");
			link.l1 = "Heh, that's strong rum indeed. Alright, I have to go. Enjoy yourself!";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "One more cup, do you mind?";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("Feels like I've spent an eternity at sea. Any news?","What do people say? Surely, I will buy you drinks.","Tell me, pal, what tales are popular in taverns these days?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "Oh! A splendid idea!";
					link.l1 = "Bartender! More rum!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "To you! Oh, hell! Who's that?";
					link.l1 = "Huh? What? Where? I must be seeing things.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Let's drink, then! Another one?";
					link.l1 = "Go ahead!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("Hey, you, "+GetAddress_Form(NPChar)+", you're surely thinking that everyone admires you, right? Well, if you ask me, you're just an ordinary brigand!.. And a murderer! 'Noble pirate'! Ha! A bandit is a bandit... Hic... Be it on land or at sea..","Hic! "+GetSexPhrase("Sco... Scoundrel","Fi... Filth")+"! You want me to drink until I pass out - hic - and then you'll steal all my money!");
						link.l1 = "I see you've already had enough to drink... Go sleep it off... And I have to go...";
						link.l1.go = "exit_sit";						
						link.l2 = "I don't like your tone, mate. Watch your tongue, alright?";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Who did you just call a bandit, you landlubber?! Let's see what you'll say with a hole in your belly!";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "Calm down! Did you forget? I'm your only true friend!";
					link.l4.go = "sit_case_2_friend";		
					}
					else
					{
						// Captain Beltrop, 27.06.21, новый вариант
						/* if (rand(1) == 0)
						{
							Diag.CurrentNode = Diag.TempNode;
							AddDialogExitQuestFunction("Tavern_SetBadHabitue");
							DialogExit();
						}
						else
						{ */
							dialog.text = RandPhraseSimple("Why are you staring at me? You'll wait until I pass out - hic - and then you'll steal all my money! Where did all this rabble come from?! Hic... No room for a decent person in this tavern?","Do you respect me?.. Yeah, you! Do you respect me?! You just watch yourself... I'm not one to be trifled with... One blow between the eyes... And you're as good as dead...");
							link.l1 = "Mate, you're drunk as a pig. Go home and sleep it off... And I have to go, too...";	
							link.l1.go = "exit_sit";
							link.l2 = "Hold your horses, mate. Mind whom you're talking to.";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "What did you just say?! I'll teach you a lesson!";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "Calm down! Have you forgotten me? I am your only true friend!";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "Listen! You're a good man! Perhaps you'll help me... with a certain matter?";
					link.l1 = "No, I think I have to go now.";
					link.l1.go = "exit_sit";
					link.l2 = "Sure! Hic! We're friends... aren't we? Hic!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) || CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						dialog.text = "...And then I c-caught his sabre by the b-blade...";
						link.l1 = "...and then she said...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...And then I c-caught his sabre by the b-blade...";
						link.l1 = "...hic! ...and then she said...";
						link.l1.go = "sit_case_4_exit";
					}
				break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "The p-point is t-that one of the s-soldiers insulted me. T-That’s it!";
			link.l1 = "A s-soldier? N-No, I think I'll pass.";
			link.l1.go = "exit_sit";
			link.l2 = "Calm down! Have you forgotten me? I am your only true friend!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "You? What kind of friend are you? N-no! You... you want to kill me! T-That's it!";
			link.l1 = "Well, certainly you've drunk enough already. Farewell.";
			link.l1.go = "exit_sit";
			link.l2 = "What? I'll prove to you that I'm n-not going to kill you! I... I'll cut your hand off!... Withouuu...t it you can't be killed!... Hic!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "Aaaah! Take "+GetSexPhrase("him","her")+" away from me!";
			link.l1 = "Calm down... hic... It's not going to hurt!... It's less painful than a shave!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Don't try to intimidate me! Hic! I am not so easily scared!.. And you - you should be hanging from the gallows... With all your kind - hic! You may puff out your feathers all you want - but you still reek of rotten fish! And I am not going to watch my tongue when - hic! - talking to your kind! You all disgust me!";
			link.l1 = "Argh, why am I talking to such a drunkard anyway... I suppose I'll go get a gasp of fresh air...";
			link.l1.go = "exit_sit1";
			link.l2 = "You're too bold, mate. I'll shove your words right back down your throat!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Wha-at?! I'll strangle you with my own hands! Hic... No one has escaped me - hic! - so far!";
			link.l1 = "Aren't you a drunken pig? To spoil such a nice evening... Alright, go catch your roaches - and I am out of here.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear()+"I see you're not going to keep quiet. Well, then a lesson in good manners is due.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Come closer, you rascal! You'll get what you deserve!",RandSwear()+"I will give you what you deserve!","Ha! Alright, sea dog - let's see how you fare on dry land!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("I swear you will regret it!","I will shorten your foul tongue for the ears!"),RandPhraseSimple("I'll gut you like a pig, from your arse to that shithole some call a mouth!","I swear I'll make you shut up!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hey, boys! Let's sweep this trash out of our town!";
				link.l1 = RandPhraseSimple(RandSwear()+"Say your prayers, bastards!","Oh, so you're not alone?! Well, good for you - you'll have company in hell!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Come closer, you rascal! You'll get what you deserve!",RandSwear()+"I will give you what you deserve!","Ha! Alright, sea dog - let's see how you fare on dry land!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("I swear you will regret it!","I will shorten your foul tongue by the ears!"),RandPhraseSimple("I'll gut you like a pig, from your arse to that shithole some call a mouth!","I swear I'll make you shut up!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hey, boys! Let's sweep this trash out of our town!";
				link.l1 = RandPhraseSimple(RandSwear()+"Say your prayers, bastards!","Oh, so you're not alone?! Well, good for you – you'll have company in hell!");
				link.l1.go = "fight_right_now_1";
			}
		break;		
		
		case "exit_sit":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterComplexReputationToNeutral(pchar,"nobility", 2.0);			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
				
		case "tavern_keeper":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
		
		// Captain Beltrop, 27.06.21, новый вариант
		case "bad_habitue":
			dialog.text = "Hey, I don't get it! As soon as I turned the corner, some new rookie took my spot. Get out of here!";
			link.l1 = "It's always the same: you sit down at the table, and it turns out it's already taken... Keep your seat, I was about to leave anyway.";
			link.l1.go = "bad_habitue1";
			link.l2 = "One more sentence like that from your filthy mouth and it will be the last thing you ever say, understand?";
			link.l2.go = "bad_habitue2";
			link.l3 = "I don't know if this was really your place, but I won't let you talk to me like that. Watch your words.";
			link.l3.go = "bad_habitue3";
		break;
		
		case "bad_habitue1":
			DialogExit();
			pchar.questTemp.BadHabitueSit = true; // атрибут усаживания
			AddDialogExitQuest("exit_sit");
		break;
		
		case "bad_habitue2":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Come on, rascals! You're about to get your fill!",RandSwear()+"Now I'll strip you properly!","Ha! Come on, sailor - let's see what you can do on land!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("I swear you'll regret this!","I'll cut your bloody tongue out!"),RandPhraseSimple("I'll gut you like a pig, from your arse to that shithole some call a mouth!","I swear I'll make you shut up!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Come on, guys! Let's get this scum out of our town!";
				link.l1 = RandPhraseSimple(RandSwear()+"Pray, you bastards!","Oh, you're not alone! Well, you'll have company in hell!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Come on, rascals! You're about to get your fill!",RandSwear()+"Now I'll strip you properly!","Ha! Come on, sailor - let's see what you can do on land!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("I swear you'll regret this!","I'll cut your bloody tongue out!"),RandPhraseSimple("I'll gut you like a pig, from your arse to that shithole some call a mouth!","I swear I'll make you shut up!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Come on, guys! Let's get this scum out of our town!";
				link.l1 = RandPhraseSimple(RandSwear()+"Pray, you bastards!","Oh, you're not alone! Well, you'll have company in hell!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "O-of course, we all know each other! Why do you ask?";
            link.l1 = "I wanted to visit the moneylender and found out he sold his old house. Do you know where he lives now?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "Why do you need him at this hour, hic? Just visit the bank in the morning!";
            link.l1 = "I need money urgently. Let the moneybags work for it for a change! Their kind always calls us freeloaders who only beg, complain and never return what we owe.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "Ha-ha-ha, hic, yes, let him work! Do you know where our glorious captain Fleetwood lived?";
            link.l1 = "Of course, who didn't know Richard. Now the banker lives there?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "You're right. When you get there, friend - tell him he's gotten too full of himself.";
            link.l1 = "Heh-heh, I'll be sure to do that. Farewell.";
            link.l1.go = "DTSG_NightIskat_5";
		break;
		
		case "DTSG_NightIskat_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_NightIskat");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_SluhSmertFleetWood";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//<-- Длинные тени старых грехов
		
		//--> Путеводная звезда
		case "PZ_BasTerAlkash_1":
			dialog.text = "Ha-ha-ha, have I seen a Chinaman? We've all seen him!";
			link.l1 = "What's so funny? I'm not talking about a travelling circus, if that's what you mean. I'm talking about a fighter, a naval officer.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "Ah, I see what you mean! Yes, I saw him. Even after sobering up, I couldn't stop seeing him...  I can't forget it!";
			link.l1 = "That's interesting. Go on. Let's have another drink - you're probably drinking now to forget it all. Tell me what you saw before you do.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "A travelling circus, my arse! He was jumping, spinning, and whirling that sabre around - I've never seen anyone so skilled and terrifying with a weapon.";
			link.l1 = "That sounds like him. Who was he fighting? Do you remember?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "The guards, mate! Narrowing his eyes at them too! Though, I think he always looks like that. What do you think?";
			link.l1 = "I don't know, mate. Keep going. Did they think he was a spy? Why did the guards attack him?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "Who knows? They were trying to figure out what he was doing in town...";
			link.l1 = "So, did they arrest him? Or...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "Ha, fat chance! They couldn't catch him. He cut down the guards in the city and fled into the jungle. They've sent several groups after him, but none have come back. Can you imagine? He's turned that cave into a real fortress!";
			link.l1 = "That's something. Get some rest and try to forget it. I think I'll be going now - my head's spinning.";
			link.l1.go = "PZ_BasTerAlkash_7";
		break;
		
		case "PZ_BasTerAlkash_7":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerAlkash2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			pchar.questTemp.PZ_BasTerTurma = true;
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			DelMapQuestMarkIsland("Guadeloupe");
			AddQuestRecord("PZ", "3");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			PChar.quest.PZ_BasTerPeshera.win_condition.l1 = "location";
			PChar.quest.PZ_BasTerPeshera.win_condition.l1.location = "Guadeloupe_CaveEntrance";
			PChar.quest.PZ_BasTerPeshera.win_condition = "PZ_BasTerPeshera";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		break;
		
		case "Sotta1":
			dialog.text = "Haven't seen him myself - he's been hanging around the governor's office, eh! But his crew had a big party here.";
			link.l1 = "Is that so?";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "Everyone says he's a merchant. But his crew didn't look like tavern trash, I tell you! They looked as if... as if... what's the word...?";
			link.l1 = "I get it. Thanks for the company, mate. Take care.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "I'm celebrating! And who says I'm alone? You're here, mate! And as for Matt, it was bound to happen sooner or later.";
			link.l1 = "What makes you say that? I've heard he was a remarkably lucky pirate, favoured by Fortune for years!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "Heh, it wasn't just Fortune, eh! He was a lone pirate, not a member of the Brotherhood! And those don't last long... Although, I heard folks gossip that he was once under Levasseur's wing.";
			link.l1 = "That's right, loners don't last long. Well, celebrate. I've got to go, mate.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "Eek, no, I-I’ve never seen him. Who is he?";
			link.l1 = "He's the captain of one of the fastest ships in the Archipelago, the brig 'Banten'. Heard of him?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "Er, no, I'm not interested in ships, mate, eek! Shall we have another cup?";
			link.l1 = "Not for me. I didn't get what I wanted here anyway.";
			link.l1.go = "exit_sit";
		break;
		//<-- Путеводная звезда
		
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
