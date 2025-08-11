// Виктор Кассель - бандит
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
				dialog.text = "Bugger off, pal. I don't want to talk to blokes who provoke innocent people to fight. Get lost!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hm... What do you want, pal? If you're hoping to talk, I have to disappoint you...";
				link.l1 = "Too bad... I did want to talk. I am a newcomer here and I'm just getting to know people...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! What do you want?";
				link.l1 = LinkRandPhrase("Victor! Got any news for me?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're doing. 'Bye.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "A newcomer? Hm... Fine then. I'm Victor Cassel, and you'd better avoid making me angry while I'm in a bad mood. And while I'm in a good mood, too. I don't waste time on chatting - when people get pushy, I push back. Hard. ";
			link.l1 = "I am "+GetFullName(pchar)+", and I can push hard, too, but I hope there won't be any need for it. If you won't be sociable, I won't bother you. 'Bye.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Victor! Got any news for me?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Make it quick.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What does life look like, here?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Who is the most important person here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Where can I make coin on the island?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Why do you care? I don't want to talk about it, especially with a man I don't know.";
			link.l1 = "Jesus... sorry.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "It looks like a bore. A tiresome, dull, senseless bore. I'm going to join Shark's pirates - at least those lads have a dustup now and then. I'm sure they'll find a way off the island too, someday. That day comes, I want to be with 'em.";
			link.l1 = "Really...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "The Admiral for sure! He's got the Narwhals and Rivados in his fist and they can't do nothin' about it. But second to him would be the leaders of the clans: Donald Greenspy of the Narwhals and Black Eddy of the Rivados. Then next would come Axel Yost, a Narwhal merchant. Then the tavern keeper, Sancho Carpentero - can't get by without a strong drink, heh!";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Chests, of course, but you have to beat the locks, first; people don't trust each other here, so all chests have locks. And let me tell you, pal, the best trinkets are kept inside the ships under the watch of their owners.\nYou can also explore the outer ring, but take care not to fall through the rotten decks. Or you can hunt giant crabs; you can get a good price for the meat on their pincers.";
			link.l1 = "Got it...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Hey, fucker! I told you not to get pushy with me. Take your hands off my chest!", "I knew you were the pushy type. I'll teach you to rob me!", "Oh good, I was lookin' for an excuse to get pushy with you!");
			link.l1 = "Argh!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to ransack my chests? You won't get away with this!";
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
			dialog.text = LinkRandPhrase("Pal, put that sword away. You look ridiculous.", "You know, pal, Shark'll throw you into Tartarus, you don't put that away...", "Fuck off with that sword, you look like an idiot.");
			link.l1 = LinkRandPhrase("Fine.", "Fine.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Pal, put that sword away. You look ridiculous.", "ou know, pal, Shark'll throw you into Tartarus, you don't put that away...");
				link.l1 = LinkRandPhrase("Fine.", "Fine.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Pal, put that sword away. You look ridiculous.", "Fuck off with that sword, you look like an idiot.");
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
