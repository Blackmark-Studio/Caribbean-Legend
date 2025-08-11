// Антонио Бетанкур - потомок Франциско Бетанкура
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
				dialog.text = "Out of my sight! I'll have no truck with brigands who wantonly attack innocent people. Begone!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Greetings! What can I do for you, friend?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". I wanted to introduce myself. You see, I am newly arrived, and I'm just getting to know the city and her people.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! What can I do for you?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, they say that you know the island's history well. I've a question for you...";
					link.l4.go = "dolly";
				}
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("What news, Antonio?", "Has anything new happened on the island?", "Can you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're getting along. Farewell, sir!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Splendid. Welcome to our island! You'll be fine, because we are all one big, happy family - well, except for the Narwhals and those filthy Rivados, of course.\nMy name is Antonio, Antonio de Betancourt. I am the grandson of Francisco de Betancourt, if that name means anything to you.";
			link.l1 = "Francisco de Betancourt? I've heard that name before... Ah, sure! Jose Dios told me about him, and I read about him in Ignacio Alvarado's notes!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "I know not this 'Jose Dios' of yours, but Captain Alvarado visited us long ago - saw him myself when I was a kid. He sailed away from the island and wrote about it in his chronicle. And my grandfather, Francisco, was a Spanish admiral, commanding his own squadron.\nHe's part of the history of this place due to the fact that the Rivados are descended from the black slaves of Tartarus, the flagship of the squadron. The Narwhals are the children of the first white settlers: the crew of Tartarus, San Augustine, and San Geronimo.";
			link.l1 = "Incredible! So you were born here?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Exactly. I am the grandson of the man who colonized the island.";
			link.l1 = "I see. Glad to meet you, Antonio. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Sure, friend, ask away. I'll answer your questions if I can.";
			link.l1 = "Tell me, do you remember a galleon called San Geronimo?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Sure I do. She was a very special ship. There was a curious Indian idol aboard to which the filthy pagan Rivados performed sacrifices.";
			link.l1 = "What kind of sacrifices? Were they cutting people's hearts out and chopping their heads off like the Maya?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "No. When a victim was brought to the idol, it dragged them into itself and they disappeared forever. Devil's work! Thank God above the idol sank with the ship and will do none harm any longer.\nThe sacrifices were always made in the morning; the idol used to turn to gold in the  rising sun's rays, so that was when the savages brought their victims - mostly Narwhals they'd captured.";
			link.l1 = "Fascinating! Has anybody ever tried to reach the idol?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Of course not! Firstly, the Rivados never let anyone except their own come near the San Geronimo, and secondly, an honest Catholic must keep a distance from the Devil's devices.";
			link.l1 = "I see... I take it that you don't like the Rivados much at all.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Good Lord, I hate those dirty pagans! As I said, my grandfather - God rest his soul - was captain of the ship upon which the negroes revolted, led by their leader, Rivados. Giving that black bastard a slow death was the only right and just response such actions.\nI had a gorgeous key to the St. Anna's treasury. No one knows where the treasury now lies - probably at the bottom of the sea with crabs picking over it - but the key was a sweet memento to me, and it was stolen!\nI am certain the blacks did it - trying to find the treasury! I doubt they'll succeed; it has been too long, ha-ha! Scum...";
			link.l1 = "Yes... ahem, anyway, thanks for your interesting story!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "You are welcome! Drop by anytime!";
			link.l1 = "Farewell!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I'm listening, friend.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "So, you've never left the island?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "You were born here... yet you aren't a member of the Narwhal clan? I thought all native white people were Narwhals.";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "And what do you do on the island?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Tell me, have you ever wanted to leave the island, see the world?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Not once. But don't think that I am an idiot or narrow-minded. I inherited a fine library from my grandfather, and my father gave me an excellent education. I know history, geography, astronomy. I speak English, French, Spanish, Latin. Though I've never seen anything except rotting ship wrecks, in my mind I have visited Europe, China, India...\nIndeed, I'd say I know far more than most sailors who've been around the world.";
			link.l1 = "Maybe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Not all, but most. But I am not a Narwhal and I don't want to become one of them. Why should I? To stand guard for hours in the hot sun or be disembowelled in a fight with Rivados? God, spare me from that! I'm an intellectual. I prefer to live independently and read books.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Father left me a goodly inheritance and I spend it wisely, so I don't need to crawl through old ship wrecks in search of baubles to trade for food, or chase treasure that may or may not exist.\nThe only treasure I know of for certain is the St. Anna's treasury. It's in a big iron chest, but no one has yet found it.\nOne day, I'm going to write a detailed chronicle of the island based on local oral histories - what do you think of that?";
			link.l1 = "A worthy pursuit! I know at least one man in the Caribbean who'd would pay well for such book...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Sometimes. If a ship came which could navigate the currents and the storms, perhaps I'd take the risk. I do long to see thye things which are so meticulously described in my books! But for now, these are merely dreams...";
			link.l1 = "Sometimes dreams come true... if you make them.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ahh, heeelp! Thief!!", "You rapscallion, trying to rob me when my back is turned!", "Take your hands off that! That is my chest! Somebody, heeelp!");
			link.l1 = "Oh shit!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What do you think you're doing, opening my chests? You won't get away with this!";
			link.l1 = "Blazes!";
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
			dialog.text = LinkRandPhrase("Sheathe your sword, sir! You make me nervous.", "Unwise to be running around with a blade here, my friend. Sheathe it.", "Oh, don't go running around with your sword like a child, put it away.");
			link.l1 = LinkRandPhrase("Fine.", "As you wish...", "I apologize...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "As a citizen of this city I demand you put away your sword, sir!", "Put away your sword sir! You're making a scene.");
				link.l1 = LinkRandPhrase("Fine.", "As you wish...", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Friend, please, put away your sword. It makes me nervous...", "I don't like men waving their weapons in front of me. It scares me...");
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
