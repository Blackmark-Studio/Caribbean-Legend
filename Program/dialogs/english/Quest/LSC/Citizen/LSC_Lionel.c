// Лайонел Маскетт - мещанин
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
				dialog.text = "I don't want to talk to you. You attack peaceful people for no reason and provoke them to fight. Go away!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Greetings, "+GetAddress_Form(NPChar)+". Are you a newcomer here?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+" - and yes, I am.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+", "+TimeGreeting()+". Want something?";
				link.l1 = LinkRandPhrase("Got anything interesting to tell me?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're doing. Goodbye.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "My name is Lionell. Nice to meet you. How did you get here?";
			link.l1 = "On a barque... I heard that there was a smugglers' cove out here and decided to look for it... Well, my barque is sunk and here I am.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Do people really think the island is a smugglers' cove?";
			link.l1 = "Not officially. Most people don't even believe in your existence.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "And why should they? We're not on any map. You can't leave this place. The locals say that the island once traded with Cuba, but I don't remember that and I've been living here almost eight years.";
			link.l1 = "I see. It was a pleasure to talk with you. Goodbye.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Got anything interesting to tell me?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am listening.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Would you like to leave and go to the Main?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "What do people do here, on the island?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Where do you get things here? Food, clothing, drinks?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "That is an odd story. This island is the only place I've known in the Caribbean. I had a run of hard luck in England so I booked passage on a merchantman to the New World. I was going to find a job in Belize - maybe as a clerk for the harbourmaster. But we never made it to Belize.\nI'm no sailor, so I don't know the details, but a storm cropped up and wrecked us on the reefs. I'll never forget that terrible blow... the screaming...\nSomeone shouted, 'She's holed!' and people started jumping overboard. Me... I can't swim, so I stayed. Ironically, that saved my life: the ship survived and the storm broke at dawn.\nBefore I left the ship I took some food, built a raft, and paddled over a tranquil sea to the outer ring. That's how I survived; the only one out of the whole crew.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "That was my dream for the first two years here, but now... Is the island really worse than any other place? There are no green fields or trees, but there is a magnificent sea and a night sky filled with stars. I am well fed, I wear decent clothing - better than I could afford while living in England. I have a lot of friends...\nNo, sir, I don't want to leave this place. What's out there for me? A desk job under a cantankerous boss for three hundred pesos a week? No sir! I found everything I was looking for right here. I need nothing else.";
			link.l1 = "I see. I'm glad for you!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Whatever they like. The Narwhals and Rivados make war. The pirates sell provisions. Axel Yost buys and sells salvage. Sancho Carpentero serves drinks and entertains people. Brother Julian prays, says Mass and sells medicines. Lauderdale and Solderra intrigue against each other. Abbot likes to strut in the sun. Jillian and Tanneke dream about true love...";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "From the wrecks, my friend, from the wrecks. Salvaging the broken ships on the outer ring is many an islander's favourite pastime. You can find everything there: weapons, medicines, spices and rum. A lot of the wrecks are still unexplored - the currents bring new victims all the time...";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Get your hands off my things, thief!", "Turn my back for one minute and you try to rob me?! I'll show you!", "Ransacking my chests?! You won't get away with this!");
			link.l1 = "Shut your mouth!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "How dare you touch my things without permission! Someone, help! Thief!";
			link.l1 = "Shut your mouth!";
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
			dialog.text = LinkRandPhrase("Put your weapon away, friend. It makes me nervous.", "You know, running around with a blade is not tolerated here. Put it away.", "Listen, don't play the white knight, running around with a sword. It doesn't suit you, put it away...");
			link.l1 = LinkRandPhrase("Fine.", "All right.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am a citizen of this island and I'd ask you to put down your blade.", "Listen, I am a citizen of this island and I'd ask you to put down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Alright.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful, friend. Running around with a weapon... makes me nervous.", "I don't like men walking around with their weapon out. It scares me.");
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
