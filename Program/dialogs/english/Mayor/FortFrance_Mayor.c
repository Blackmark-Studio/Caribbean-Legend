// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.","I am listening, what's the question?"),"It is the second time you are trying to ask...","It is the third time you are trying to ask again...","When is it going to end?! I am a busy man, working on the colony's matters and you are still trying to ask something!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...","Not now. Wrong place and time."),"True... But later, not now...","I'll ask... But a bit later...","I am sorry, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Monsieur, I have found a bandit's corpse in the jungle. He was killed by the Indians. There were earrings on his body; looks like they were brought here from Europe. Perhaps they belonged to one of the nobles in your town?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "Your Excellency, the deed is done! However, I regret to inform you that the criminal did not survive the engagement, and therefore will not face execution.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "Your Excellency, the task is complete! The prisoner awaits his fate in my brig.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "I have arrived by order of Governor General Philippe de Poincy to take command of your armed frigate.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "I'm ready to take the frigate into my squadron.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "I came at your invitation, Monsieur...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "That was unfortunate, Monsieur";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "Your Excellency, I've come into possession of intelligence regarding illicit commerce soon to transpire upon these shores. I venture to say this matter may prove worthy of your attention.";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "Your Excellency, I come seeking tidings of that smuggling vessel we discussed.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Let's see what you have... Incredible! It's just incredible, Charles! These are my wife's earrings. I gave them to her before I left Europe and came to the colonies. They disappeared a few months ago under mysterious circumstances. I knew they were stolen!\nCharles, I'm very glad that you came straight to me, and didn't sell the thing I hold so dear to the merchants. I'll repay you for your favour. As I heard, you are going to buy a ship? Since you've decided to take up seafaring, you'll undoubtedly need a map of our archipelago. Here, take it. I'm sure it will come in handy!";
			link.l1 = "Thank you, Your Grace!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "That's unfortunate, Charles, but we must make do with the situation at hand. Here is your reward: five thousand pesos, after taxes.";
			link.l1 = "I am pleased to serve St. Pierre and you personally. While the battle was difficult, I found some enjoyment in it.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "It was a challenging battle, your Excellency. My ship sustained significant damage. Would it be possible to compensate me for my losses?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "Bravo, Charles! I have no doubt you'll rise far in our ranks.";
			link.l1 = "Until we meet again, your Excellency.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "I must say, I'm a bit surprised by your request, Charles... Very well, consider another two thousand pesos from me personally as a gesture of goodwill. Farewell.";
			link.l1 = "Thank you, your Excellency.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "Excellent, Charles! You will be pleased to learn that your success will aid your Maltese friends in a delicate operation... Here is your reward: eight thousand pesos, after taxes.";
			link.l1 = "I'm pleased to serve St. Pierre, the Order, and you personally. Though the fight was challenging, I found some satisfaction in it.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "It was a tough battle, your Excellency. My ship suffered considerable damage. May I request compensation for my losses?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "Bravo, Charles! I'm confident you'll go far.";
			link.l1 = "Until we meet again, Your Excellency";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "I suppose you've earned it. Keep another two thousand from me personally as a gesture of goodwill. Thank you, my friend.";
			link.l1 = "Thank you, your Excellency.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "The ship is ready, but you don't have a free berth for it in your squadron. Captain, reduce your squadron and return, then I will immediately give you the frigate.";
				link.l1 = "Fine.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Yes, of course, the ship is ready to sail. Her captain is aware and will follow all of your orders.";
				link.l1 = "Then we're setting off. Goodbye, Your Grace.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excellent. Prepare to greet your new ship. Its captain is aware and will follow all your orders.";
			link.l1 = "Then we're setting off. Goodbye, Your Grace.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Captain Charles de Maure, at last! I've been waiting for you eagerly! Please, come in, join me.";
			link.l1 = "Good day to you too, Your Excellency. There is always a reason behind such politeness of yours. What is it this time? Pirates, Spaniards, Redskin cannibals?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "Don't get all ironic, Captain. It's not my fault that we always get into trouble, you and I. But please, don't worry, there will be no shooting this time... probably.";
			link.l1 = "You intrigue me, go on. How can I help?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Ever heard of Madame Botot's fine establishment? During the siege, our... brothel was burnt to ashes. One day, a certain lady volunteered to rebuild it.";
			link.l1 = "A fire in a brothel and without me? By the way, I got shot by the Spanish that day too.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "Damn it, Charles, what is wrong with you today? Your wit is inappropriate! Even though it is not a matter of State, it is still an important matter, for me, personally! I need your help! For God's sake, pull yourself together and hear me out!";
			link.l1 = "Forgive me, Your Excellency. I am feeling a huge relief, that's all. To be honest, I got tired of all this constant battling and fighting. I expected you to start dragging me into another circle of violence. Please go on. Never heard of this Madame Botot.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Right, so this honourable dame has elevated the establishment to a whole new level. It is now a place of high and noble society, not a rat hole as it used to be. A place of distinguished vices, expensive wine, and unlimited gambling. You will see everything for yourself!";
			link.l1 = "Your Excellency, I am not a prude and your description was very colourful, but why are you telling me this?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "Because you're on the list, why else?! Look, I feel guilty about the Marquise and promised to introduce you to her at one of her parties tomorrow. Juliana doesn't do this often, so please be kind enough to join us. No fighting, shooting, or chasing this time, I promise. Everything will be courteous and dignified: wine, beautiful women, cards, and other noble pleasures.";
			link.l1 = "Cards and whores. It's been a while, in another life. I still don't follow you though. Why me?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Are you deaf? Juliana Botot, she... collects bright and famous faces. They make her parties special and fresh. You have made quite a name for yourself, the Marquise has waited a long time to have you as her guest. My misstep gave her an opportunity, and I won't take it if she refuses to receive me again. This is all I am getting if I don't deliver you to her!";
			link.l1 = "Your Excellency, you are a handsome widower and a governor... Why do you even care about some courtesan's opinion? It is they who should seek your favour, not the other way around.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "Marquise Botot is under the protection of Count Henry de Levi-Vantadur - who, by His Majesty's grace, is the head of New France's states in North America. Trust me, Charles, no one here wants to cross him.";
			link.l1 = "You almost had me here - I thought this was only about lust and amour. Now I see it was politics all along. Trivial, but expected. Very well, I will help you out. It will be sweet to return to the days of my youth just for one night.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Captain, you are a seasoned man, no doubt, but don't try to pretend to be an old man. It's not only about politics. I value Juliana's presence and I am grateful for your help. It is important to me personally, truly. Come to Marquise Botot's place after dusk, tomorrow. I promise you that politics will not spoil the night.";
			link.l1 = "Wine, cards, women. Just like the good old times. Farewell, Your Excellency!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Charles, what happened, you look like hell!";
			link.l1 = "Angerran, damn Chievous, Excellency. He stole my frigate last night. Put my prize crew to death and set sail in the mist.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "It's an unpleasant turn of events, I understand, but trust me - such an outcome is quite satisfactory. You are not in dire need of ships and men, while de Levi Vantadour will pay a significant sum to conceal the truth behind a certain recent duel. Or he will remember our role in concealing it for free, which is also worth quite a lot. De Chievous did dishonest things twice, but he is far away now, while we still have decent cards to play against him.";
			link.l1 = "Thrice, your Excellency. Angerran admitted to cheating during our card game. But he won't pay me off with money, if that's what you mean. He crossed the line. There was a certain person on that ship this morning... she is very dear to me! I won't let the bastard do her any harm! You hear that, Jacques, I will not!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "I think I know who you're talking about - I remember seeing you with some... girl, dressed like a man and armed to the teeth like a pirate. Charles, don't be a fool! You got lucky, you avoided huge trouble and now what, you're trying to drag yourself into it again? Let it go. De Chievous is on the run - thank God! And as for your 'girlfriend in arms' - take your friend's advice - go see Julianna and forget about all this.";
			link.l1 = "Out of the question, your Excellency. Some things are just beyond your understanding, all right? Now tell me everything you know about the bastard. Where could he go from Saint Pierre? And don't try to dissuade me again - I've tangled with the Dutch Company, crossed pirate barons, governor-generals, even the Holy Inquisition! I am not an easy man to scare off. I will get her back, whatever the cost!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Charles, have you ever given any thought to the question of who appoints governor-generals? This is an entirely different world! You have barely scratched its surface; it is beyond your understanding, you are like a child in a gunpowder store. And you are asking me to hand you a lit candle. As for governor-generals: de Poincy himself never crosses the count, neither in matters of coin nor in matters of politics. Vice King, the term so popular among the commoners, would suit Henri de Lévis Ventadour just fine.";
			link.l1 = "And here I am, planning to skin his only male heir. I know what I'm risking here. Now, just tell me: is there anything useful you know that could help me?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "On any other day, I would take you reaching for your pistol as the end of our friendship, Charles. But I understand your current state of mind. That is why I am willing to let this go. I know nothing useful to you; the frigate sailed west early this morning. You should pay a visit to the Marquise... Wait, not like that! Julianna knows a great deal about your enemy, and she was personally... acquainted with his father for some time. Ask her. Unlike me, she won't try to stop you.";
			link.l1 = "That's the plan. See you, Excellency. Thank you for your time.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "Smuggled goods, you say? Hmm... most intriguing. Pray, enlighten me with the particulars of your discovery.";
			link.l1 = "Three days past, a vessel laden with contraband was to drop anchor in Le Marin Bay. The ship failed to make its rendezvous, but I have sound reason to believe she'll yet make port ere long. Perhaps your men might arrange a proper greeting for these brigands when they arrive, Your Excellency.";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Magor_2":
			dialog.text = "A nameless vessel carrying unnamed cargo... And you presume I should dispatch His Majesty's forces on such nebulous intelligence?";
			link.l1 = "Your Excellency, I grant the particulars are scarce. But pray, allow me to recount how this intelligence came into my possession. (Cutscene)";
			link.l1.go = "VPVL_Magor_3";
		break;

		case "VPVL_Magor_3":
			dialog.text = "Very well, we shall put your intelligence to the test. Should a vessel bearing contraband indeed weigh anchor off Le Marin's shores, you shall be handsomely rewarded for your service to the Crown. Return to me in three days' time. By then, the fog of uncertainty shall have lifted.";
			link.l1 = "Excellent. Then I'll see you in three days.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;

		case "VPVL_Magor_4":
			dialog.text = "Ah, Captain! A pleasure to receive you once more. Your intelligence proved most valuable indeed. My men intercepted the vessel precisely where you indicated. Here—one hundred and fifty Spanish doubloons, freshly struck and heavy in the purse. Take them with my gratitude.";
			link.l1 = "My humble thanks, Your Excellency. 'Tis good fortune that my morsel of intelligence served the Crown's interests. Should opportunity arise again, know that my sword arm and discerning eye remain at your disposal.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;

		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
