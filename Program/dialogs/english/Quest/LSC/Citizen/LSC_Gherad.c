// Гхерад Смиитс - матрос
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
				dialog.text = "Bugger off, mate. I don't gab with them that strike innocent civvies!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "G'day, mate, ha-ha! What are you doing here?";
				link.l1 = TimeGreeting()+". Good day! I don't believe I've met you yet.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Hey-ho, "+GetFullName(pchar)+"! "+TimeGreeting()+"! What can I do for ye?";
				link.l1 = LinkRandPhrase("Hey-ho! Any news?", "Has anything new happened on the island?", "Will you tell me the latest gossips?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to know how you're doing. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Sure, you haven't, but now you have! Name's Gerard Smeets, sailor - a seaman from Rotterdam. And you look like a quartermaster if I'm not mistaken...?";
			link.l1 = "Something like that. My name is "+GetFullName(pchar)+". Pleasure to meet you.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Actually, you look more like a ship owner or a paymaster... You're a well educated man, no doubt. Glad to meet ye! How did you get here?";
			link.l1 = "I decided to explore the Gulf of Mexico. Buccaneers from Cuba told me that there was an uncharted island in this area and I wanted to see if they were correct.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Are you the only survivor? Where'd your ship sink, the outer ring?";
			link.l1 = "I'm indeed the only one. And my barque is at the bottom of the sea south of here; it didn't even reach the outer ring.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ah. Well, since you're stuck here, visit Sancho to get some rum. Drinking away your sorrow is a good start to your stay, he-he.";
			link.l1 = "Thanks... 'bye for now!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hey-ho Smeets, any news?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sure, mate. Fire away!.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Tell me, how did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Do you want to leave the island and return to your old life?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Do the clans bother you?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "How did this island form? Any idea?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I got here with that puffed up peacock Abbot. I served on his ship. You know, people like him ought never set foot on a ship's deck - they bring bad luck. The devil must've put him on our tub.\nWe set sail on a voyage from Jamaica to Belize; easy as pie. But ill fate chased us: our boatswain fell overboard, our navigator steered us wrong, the bloody Spanish fell upon us, and a storm battered us to pieces. And here we are.";
			link.l1 = "Goodness!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "I used to, but... tell ye the truth, mate, I don't know. Life is fine here; plenty of rum and wine, good food - not a lot, but  better than weevilly ship's biscuits.\nThere are good blokes here, plenty of drink and gabbin'. I like it here. So I'm not sure... No, I reckon I don't want to leave. I used to live angry and hungry - look at my belly now, ha-ha!";
			link.l1 = "Great! I'm glad for you.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "No, they don't. Just don't trespass against 'em, they don't abide that. The Narwhals are good lads - most of 'em were born here and they know no other life. Many of 'em are very skilled. Jurgen Schmidt for example; he's a god of blacksmithing, Hephaestus in the flesh!";
			link.l1 = "Good to know.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Storms and reefs, mate. The outer ring is made of ships top to bottom; ships get caught by a storm and thrown onto the reefs or the outer ring itself. That's how the island grows!\nThough I've no idea why the inner ships stay above the water. Probably there's a shoal beneath our feet, holding us up.";
			link.l1 = "Fascinating!";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Hey-ho, thief! Thought you could rob me blind, eh?", "Turn my back, look what happens! A filthy thief comes crawlin'!", "Oi! Hands off my sea chest, mate!");
			link.l1 = "Oh, fuck it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ransacking my chests?! How dare you!";
			link.l1 = "Damn...";
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
			dialog.text = LinkRandPhrase("Mate, put your blade away, will ye? You're makin' me nervous.", "Don't let anyone see you runnin' around with a blade out. Put that away.", "Don't go playin' a knight with you're sword out, you look a proper arse. Put it away...");
			link.l1 = LinkRandPhrase("Fine.", "As you wish...", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, we don't tolerate fools runnin' around with their weapons out. Put it away.", "I don't like a man bein' so free with his blade. Put it away.");
				link.l1 = LinkRandPhrase("Fine.", "Whatever then.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Mate, put your blade away, will ye? You're makin' me nervous.", "I don't like a man bein' so free with his blade. It scares me...");
				link.l1 = RandPhraseSimple("Got it.", "I am taking it away.");
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
