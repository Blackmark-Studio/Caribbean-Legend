// Джаспер Пратт - каторжник
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
				dialog.text = "Leave me alone, mister. I don't talk to them what hurt th'innocent! You're more a criminal than me!";
				link.l1 = "Am I...?";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "G'day, mister. Need somewhat?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". I'm new here. May I ask your name?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Hello, Jasper. Heard any news lately?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you are. Another time, Jasper!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Me? I'm Jasper Pratt. You may've 'eard people call me the state convict - s'why they all look askance at me. Ah, the 'ell with them. I am what I am...";
			link.l1 = "I don't care about who you were, I care about who you are.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Shame not everyone thinks like you, mister.";
			link.l1 = "Well, I am known for my liberal attitude...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Good on you. Don't worry. Despite m'past, I'm no threat to th'purses 'n chests o' th'Island's 'habitants. I'm glad I can live in peace at last.";
			link.l1 = "Good to meet you, Jasper. 'Til next time!"
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hello Jasper. Heard any news lately?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I'll answer you if'n I can. Ask.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you come to the island?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Do you like this place?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "You mentioned that people look at you askance. Is that because of your past?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "This island is quite interesting, don't you think?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Run away from a Cuban plantation. There were five of us 'n we decided dyin' were preferable to breakin' ours backs or bein' beat daily. We managed to trick th'guards an' disappear into the jungles. When we reached the shore we built a raft.\nTried to reach Tortuga but none of us knew how to navigate, so we got lost. Then th'water run out... I don't want to think about that. Anyroad, I was th'only one who to reach the island and survive.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "You know, I like it here. After all I went through on the plantation, this place feels like Heaven on Earth. I don't need much... bit o' food, water, glass o' rum in th'evening - and nobody wants to tan my hide with a whip here. All that's reason 'nuff to stay. I'll be glad to die here when my time comes.";
			link.l1 = "I suppose so...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Thing is, th'island's been a playground for a thief. He comes in the night, locks don't stop 'im. Mostly he plunders 'round th'Admiral's chambers, where the pirates live, everybody's 'ad their chests turnt inside-out at one time or another.\nNobody knows who the thief is, so they suspect people with... erm... criminal pasts.\nThief's is a bit strange though: he only takes spirit bottles and certain trinkets - nothing truly valuable. Funny, innit?";
			link.l1 = "Yeah, funny...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "'Tis. Swam a lot 'round the inner ships o' th'island. Not many exits from the water: San Augustine, on the canted deck either side o' the rope bridge; Gloria, up the fallen mast...\nIf'n you swim close to the Phoenix and then 'round the Ceres you can reach Mary Casper's cabin through the ship's bow.\nThe hole in Tartarus's belly will lead you to the prison. There's a hole in the San Augustine's bow what opens into th'Admiral's storage room, but don't go in there - the guards'll cut you down; remember, the lowest door of Tartarus is locked for a reason.\nAn' o' course you can get aboard the Fernanda, the lone fluyt. They say no one lives there but I've often seen lights inside the cabin, and sometimes I can hear drinking songs... and a man cryin' out, in pain or grief.";
			link.l1 = "Interesting... so much to explore.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ah! There's the thief! He's right there!", "And they say I'm a criminal?! Hands off, mister!", "I've found the thief! He's here! He's here!");
			link.l1 = "Wait, no!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Take your fingers out my chest! Heeelp!";
			link.l1 = "Fuck!";
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
			dialog.text = LinkRandPhrase("Mister, for the love o' God, put your blade away! You're scarin' folks.", "You best not let anyone see you wavin' that around... you'll wind up in Tartarus.", "There's no need to be wavin' a blade 'round here. You're among friends.");
			link.l1 = LinkRandPhrase("Fine.", "Sorry.", "All right...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, mister, put that away. No need for a sword 'round here.", "This is my home, an' it's safe 'cause folks don't go 'round wavin' swords. Put that away.");
				link.l1 = LinkRandPhrase("Fine.", "All right, then.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Mister, for the love o' God, put your blade away! You're scarin' folks.", "This is my home, an' it's safe 'cause folks don't go 'round wavin' swords. Put that away.");
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
