// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Go ahead, what do you want?","We were just talking about that. You must have forgotten...","This is the third time today you've brought up some question...","Listen, this is a store. People buy things here. Don't disturb me!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, "+NPChar.name+", maybe next time.","Right, I've forgotten for some reason...","Yes, it really is the third time...","Hm, I won't...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Listen, monsieur, I'm looking for a job. Not a full-time position or hauling cargo, but more like running errands, so to speak. Do you happen to need any assistance?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "I've completed your errand. I found Gralam Lavoie.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Meet your new assistant, monsieur.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "It's me again, monsieur. I've come for my reward.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Take a look at these earrings, monsieur. I found them on the body of a bandit who was killed in the jungle. This is clearly the work of a fine jeweller which, I'm sure, is not from around here. Is there anything you can say about these earrings?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "Excuse me, sir, but where is your sword? It is not safe to leave town without a blade. You never know what might happen in the jungle!";
				link.l1 = "Damn, I completely forgot! Everything has been taken away!";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "A job? Hm. I suppose I've got a job you might want. My assistant is missing; he used to work in my warehouse. He has been missing for a week already and this is damn annoying, because I am forced to do his duties and I don't have time.\nPlease, find this idiot and find out why the hell he abandoned his work. Or even better – bring him back to me. I'll pay you a thousand pieces of eight.";
			link.l1 = "Fine, I'm in. Tell me his name and describe his appearance. Do you have any idea where to look for him?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Search for a man God knows where for a measly thousand? You've got to be joking!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hey, monsieur. Who's looking for a job, you or me? If you don't want to, I'm not forcing you. Have a nice day.";
			link.l1 = "Hm... Think I'll go check the port authority; perhaps they'll offer something more substantial there.";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "Name's Gralam Lavois. His looks? Thirty-five years old, beard and moustache, long brown coat, white shirt. Oh, and he always wears that silly cocked hat, pretends to be an admiral with an anchor up his arse\nHe's not in St. Pierre, I have checked the whole town. He must be in the jungles or at Les Francois hiding with the pirates who lurk about there.\nThen again, he is likely in the pirate settlement of Le Francois, which is in the eastern part of our island. Maybe he's chatting with the pirates there, or spending time in the tavern, or having an argument with the local merchant at the shop.\nHow to get to Le Francois? Leave through the city gates into the jungle, at the crossroads, take the left path, then follow the road until you turn right, and then take the left passage between the rocks, and you'll find Le Francois. I don't think you'll get lost.";
			link.l1 = "Fine. I'll start searching. As soon as something comes up, I'll inform you right away.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "Oh yeah? And where is he?";
			link.l1 = "I've found him in Le Francois. He won't be working for you anymore. He also had quite a few rather salty things to say about you... Would you care to hear them?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "No. Spare me the details... What a pity! What am I to do now without an assistant?";
			link.l1 = "Hire someone else. Or is it really as big a problem as Gralam said it was?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Rotten luck, indeed. And what did that loafer say?";
			link.l1 = "Well, for starters, he's obviously not idling his time, he-he. He said that no one in all of Saint Pierre would sign up for service with you because... you don't pay your workers enough. Yes, by the way, "+npchar.name+", you owe one thousand pesos, as promised.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Please, take your money. Ha! It's never enough! Of course, nobody wants to work for me. The bastard did his best to spread filthy rumours. What can I do? I can't do everything alone!\nI can't go to sleep until I've counted every piece of cargo, because those damn workers always steal something. After the last loading, I'm missing five barrels of rum. I'm sure the workers 'accidentally' took them...";
			link.l1 = "Well, I don't know what to advise. All right, all the best. It's time for me to go.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Wait! I think you can help me. If you were able to track down that bastard, then you might well be able to...";
			link.l1 = "And what could I possibly do, I wonder, if nobody in this town believes you? I'm new here and...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Let me finish, sir. You have been to Le Francois. I would like you to go there again and try to find an employee for me. Perhaps Gralam didn't completely ruin my reputation in that pirate den\nThe job is easy - count cargo and watch over the port workers to prevent stealing. Sometimes, do my job here instead of me while I am gone, for an extra fee of course\nTell them that I offer a room in the store to live in and five hundred pieces of eight per week. Monsieur, I am planning to expand my business and things are finally going well, I need an assistant!\nBy the way, it's best to seek help in finding a worker from the local tavern keeper, Cesare Craig. That scoundrel will surely help you, though not for free, to find individuals who'd be interested in working for me.";
			link.l1 = "Hm. I can try, although I'm not sure... How much will you pay me for the job?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "That will depend on what worker you're able to hire. The better he turns out to be, the more I'll pay you for your efforts. That's fair, isn't it?";
			link.l1 = "Don't you think you're forcing me to ride blind? How am I supposed to know how you'll evaluate a worker? You could label anyone as bad or...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Monsieur! It may very well be correct to call me a little stingy, but no one could call me dishonest! If I tell you I'll pay for your efforts depending on how it turns out, then I mean it. See it from my point of view as well. You might just bring me some lazy gypsy who would not only loaf about and do nothing, but might even rob me at night!";
			link.l1 = "All right. I agree. I'll take your word for it, "+npchar.name+". I'll be sure not to bring back any gypsies.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Back to Le Francois...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "Have you found a worker for me? Wonderful. Allow me to have a word with him, come back in an hour for your reward.";
			link.l1 = "All right. I'll come back in an hour.";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "I am quite happy with the worker you've found for me, although he talks the talk more than he walks the walk, but don't worry, I'll beat the chattering out of him in time. Your reward is three thousand pieces of eight. Here you go.";
					link.l1 = "Thank you! Tell me, Monsieur, do you know if anyone else in town might need help with some important matter?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "You've managed to find a truly valuable worker! He's even better than that scoundrel Gralam. I'm very, very pleased, sir. Here, take your reward - five thousand pieces of eight.";
					link.l1 = "Thank you! Tell me, Monsieur, do you know if anyone else in town might need help with some important matter?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "You've found a good worker. And although he doesn't know all the tricks of the trade, I'm sure he'll get a handle on it without much trouble. I'm pleased with you, sir. Here, take your reward - four thousand pieces of eight.";
					link.l1 = "Thank you! Tell me, Monsieur, do you know if anyone else in town might need help with some important matter?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hmm... Just recently, I saw the port master, clearly upset, heading to the port authority. Check with him; who knows what might have happened.";
			link.l1 = "I'll do just that. Thank you, Monsieur.";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Well, what am I supposed to say, magnificent earrings. I can give you... let's see... four thousand pieces of eight for them. I doubt anyone will offer you more. Do we have a deal?";
			link.l1 = "Deal! They are yours.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "No. I think I'll keep these jewels for myself.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "That will not do. I suggest you approach our governor and ask for his assistance.";
			link.l1 = "Thanks for the advice. That is what I plan to do.";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}
