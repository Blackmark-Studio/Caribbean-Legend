// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Bugger off, pal! I don't chin waggle with scum who attack innocent people.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "Pal, you're just in time... I want to talk to you about some business... important business.";
				link.l1 = "Really? Why Leonard... I do believe you're sober! What a rare sight!";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A-a... hic! Hello, pal...";
				link.l1 = TimeGreeting()+". It looks like you had enough already, 'pal.'";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Hic! What do you want?";
				link.l1 = LinkRandPhrase("What's new, Leonard?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to know check you're doing. 'Bye!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Yeah! Enough? Nope! Not nearly enough, h-hic! Yes, Leonard Musket is drunk and that is how it should be!";
			link.l1 = "Fond of drinks, huh? Yes, my name is "+GetFullName(pchar)+". Nice to er... meet you.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "If you say so. We're all - hic! - met, now, so... now what?";
			link.l1 = "Fine, if you're too uh... busy to talk... Another time, then!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("What's new around here?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "A-haha, fuck you! Yes, pal, I am - almost - sober. And that's because I've got an opportunity for us...";
			link.l1 = "What sort of opportunity? Speak, and don't waste my time!";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "Pal... do you want to make some money? Silver pesos, gold doubloons? I'll tell you how. But you will have to share with me - we'll work together.";
			link.l1 = "I'm always game to make money. But it all depends on your proposal: how profitable and how... legal... it is.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "The business is not really legal, sure, but it is profitable... and we'll be able to punish a miser for his greed. He won't end up poor; he has too much money.\nBesides, everyone shares with him, so it's his turn to return the favour. Tell me, can you hold your liquor? How much rum are you able to drink before going under table?";
			link.l1 = "It depends. I don't really have a habit for excessive drinking... Are you going to tell me details finally?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "Fine. I'll be specific. There is a fat ugly bastard on the island, Giuseppe Fazio. (spits) He skins the Narwhals, Rivados and the locals. I've been watching him for a while and I learned something...\nThere are two chests in his cabin on the Caroline: one contains papers, the other gold and silver. Both are locked with different keys. The fat bastard always keeps the keys in his pocket.";
			link.l1 = "So, you plan to rob Fazio? Sorry pal, I won't participate. And be glad I won't tell anyone about it. Find another partner.";
			link.l1.go = "facio_exit";
			link.l2 = "Ha! Interesting! Go on...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "Too bad, too bad... there's plenty of gold for both of us... Fine, then. See you around.";
			link.l1 = "Farewell.";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "Two doors lead into his cabin. One of them is always locked, but the key that opens the gold chest also opens the door. I've seen him do it. You only need the one key to open the cabin and get the gold. But how to acquire the key?\nI have a plan, an excellent plan. If it goes smoothly, Fazio will never know what happened, or who to blame. He'll think it was the mysterious rum-and-jewellery thief. Problem is, I need a partner with a head of iron in order to get it done. You follow?";
			link.l1 = "I do. Go on.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "Fazio loves to sit at Sancho's and have a good drink - and he can hold his liquor better than anyone I've ever seen! He knows it, too; he came up with a drinking game: a game where people try to drink him under the table.\nIf you ask him to play this game, I promise you he'll agree. And then comes the fun part.\nYou make a bet with him, go to the tavern, grab a bottle of rum, and drink until one of you kisses the table. If you pass out first then the whole plan is ruined; I won't be able to do it alone.\nThat's why I asked about your head. All you have to do is make sure he drops first. I'll be nearby, waiting. When he's down, I'll take his keys.\nThen we move the fat man to a bed upstairs and sneak into his cabin while he's asleep. I'll return the key right after we loot his chest - he won't even realize he's been robbed 'til he opens the chest, ha-ha!\nOnce we've got the key, you sneak into his cabin and take what you can. I'll stay on guard outside. We split the chest's contents, half-and-half, and go our separate ways. So, are you in?";
			link.l1 = "A devious plan! Sure, I'm in.";
			link.l1.go = "facio_6";
			link.l2 = "No, pal. I'll pass. I fear I can't hold my liquor that well. Find another partner, one a bit more robust than me.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "Glad I was right about you. Now, go to Fazio and arrange a meeting at the tavern in the evening after nine o'clock. I hope you beat the pig at his own game! Good luck, see you in the evening!";
			link.l1 = "I'll do my best... 'bye!";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "Pal, I'm counting on you. Drink that fat miser under the table...";
			link.l1 = "Sure.";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "It's done, the pig is asleep upstairs. I've got the key. You're doing well; you seem to be sober enough!";
			link.l1 = "R-really? It's been - hic! - a long time since I got that... that drunk. Feeling a bit dizzy... Hic! Shall we go?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "It's done, that fat pig is asleep upstairs. I have the key. You're doing good; you really managed to over drink that piggy...";
			link.l1 = "I have, but it's - hic! - been a long time since I got this drunk. My head is awhirl... let's go before I keel over.";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "Eh, pal, you failed to out-drink the fat man... Too bad. Well, at least we tried...";
			link.l1 = "D-damn me, he is like some... bot-t-tomless barrel. Argh, I need to r-rest... It's over, g-get lost! Hic!..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "Yes. Let's go! Follow me to the Caroline! And don't wander off, we don't have much time!";
			link.l1 = "Yes, l-let's!";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "Here. Take the key. The chest you need is left of the entrance. Take as much as you can as quickly as you can. Don't forget to lock it again! If I see something I'll knock on the door three times. Run away through the rear gallery.";
			link.l1 = "Fine. Be on your guard!";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = PCharDublonsTotal()-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable haul... Why'd we even bother? Eh... fine, let's split what we've got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there'd be much more... Hardly worth the risk. Eh... fine, let's split what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought there'd be more. All right, let's split it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We've done well, partner! This is a lot of coin! Let's split it!";
						else
						{
							sTotalTemp = "Damn me! I never imagined the fat man's stash was so huge. Well done, partner! Let's split the loot!";
						}
					}
				}
			}
			dialog.text = "At last! What did you managed to take from that miser? Show me!";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "There was nothing at all. Just a few scraps - amulets and such.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "I found "+sPeso+" and "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "No! It seems it was all for nothing... Maybe that bastard put his stash in another chest. Eh! Fine, give me the key and I'll return it. Farewell, pal... damn...";
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "Let's share.";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((PCharDublonsTotal()-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "All right, give me the key and I'll return it. Farewell, pal.";
			link.l1 = "Good luck, pal.";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone cleaned out his chest. It seems the mysterious thief did it.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Haven't you heard? Fazio was robbed! He was robbed while lying dead drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your feet! That's something.", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Really?... hic! I'm listening...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you end up here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Do you always drink? And where do you find coin for drink?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "What can you tell me about the locals?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Would you like to leave this place and go to the Spanish Main?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Eh! You know, I don't remember. It's true, I don't! It was a long time ago. I was sailing somewhere... somehow... anyway, I finally ended up here. Hic!";
			link.l1 = "Hm... All right...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Yes, I drink. I am a drunkard... Drinking... damn it, because I have nothing left to do! You see, pal, I'm done. This bottle of rum is the only thing I want in life. So I'll keep drinking! And money... he-he, rum doesn't cost much.\nAnyway, I don't even have to pay for it. There's a place filled with rum, but you need to swim if you want to get there. That's why I only buy rum when I'm too drunk to swim... hic! Jizjezezejizeze... no, I won't tell you where to swim, he-he, don't even ask...";
			link.l1 = "Delightful.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "What can I say - hic! - about them? Good people to talk and drink with. Giuseppe Fazio is an important man, a bigwig. His chests are bursting with gold... pfuh! Miser... but he respects old Leonard, buys him drinks at the tavern.\nThough, sometimes he also asks something in return, but it's nothing - hic!\nHeh, you know how many doubloons Fazio owns? Aha-ha-ha! Enough to spend the rest of your life in the best tavern in the Caribbean, not working, drinking the best rum in the world. But he stays here, on the island. Still never enough money for him it seems...";
			link.l1 = "Got it...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "Leave? Hic! Why? No, I don't want to go to the Main, nor to Europe, nor any poor fucking island in the world. Is there any free rum out there? No! There is no... not any free rum - hic! Which means that there's nothing for me there... Pal, I'm fine here. Hey, hey - hic! - ask people if they want to leave this place. No one does, except two or three - hic!";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Hey, pig, get your hands off my - hic! - stash!", "Think you can rob poor Leonard 'cause he drinks, huh? Huh?! I'll show you!", "Get away from my chests! Who sent you, that fat pig Fazio?!");
			link.l1 = "You fucking drunkard!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Leave my chest alone, you felon!";
			link.l1 = "Foolish girl!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Say pal, put your - hic! - sword away. You're going to hurt someone.", "You're not drunk... drunk enough to be holding a sword. Put it away and come have a drink.", "You look like a real arsehole waving your sword around like that. Put - hic! - put it away.");
			link.l1 = LinkRandPhrase("Fine.", "All right.", "Arsehole... fine.");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, you can't - hic! - can't be waving your sword around like that. Knock it off.", "You're not drunk... drunk enough to be holding a sword. Put it away and come have a drink.");
				link.l1 = LinkRandPhrase("Fine.", "Alright.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Say pal, put your - hic! - sword away. You're going to hurt someone.", "You look like a real arsehole waving your sword around like that. Put - hic! - put it away.");
				link.l1 = RandPhraseSimple("Sorry.", "I am putting it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
