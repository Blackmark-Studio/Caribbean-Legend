// Оеларт Котеел - канонир
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
				dialog.text = "Out of my sight, mynheer. I have nothing to say to men who attack innocent people.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Good day, mynheer! What do you think of this weather?";
				link.l1 = TimeGreeting()+". I like any weather except storms in the open sea...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Good day, mynheer. What's the latest news?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're doing. Good day, mynheer!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha-ha! I feel the same. I have never seen you before... my name is Oelart Koteel. I was a gun captain on a Dutch man-o'-war.";
			link.l1 = ""+GetFullName(pchar)+". I am a newcomer here, just arrived.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "I am new too, been here for less than a year - and I really hope I don't have to stay here much longer, though everybody tries to convince me otherwise. Good to meet you!";
			link.l1 = "Good to meet you too, "+npchar.name+"...";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Good day, mynheer. What's the latest news?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
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
				link.l2 = "Do you want to leave the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Have you any idea how the island formed?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Have you ever visited the clans' ships?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "It's quite banal. We fought an English schooner and almost won the action. They fled, we chased. A day passed, we were close to catching them but they shot off our mainmast and managed to escape.\nLater, we were almost sunk by a strong gale, then we were caught in a current, and in the end our ship was thrown onto a reef close to the outer ring. Very few managed to survive...";
			link.l1 = "Sad...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "That is my dream. You can't imagine how bored I am of this place. But how do I leave? I have no idea.\nThere are no ships afloat here and no opportunity to built a new one - and it would be a suicide to try to sail out on a longboat. The storms would crush anything so small.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "The oldest wreck I've seen on the island is about a hundred years old, but there is every possibility that the island is much older, because of the outer ring. It's made of ships from top to the bottom - there could be some truly ancient vessels deep underwater, a few fathoms out of sight.\nAs for the island's formation... I believe the currents and storms bring drifting ships here, so an artificial shoal was made. The outer ring was built upon that.\nThe inner ships we live on... either they were the very first or they somehow managed to slip through the outer ring. It's quite possible, the Admiral and his pirates reached us on their brig after all.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "I have visited the Protector and Velasco, in Rivados territory. Black Eddy once needed a consultation about ship's guns - don't ask me why, he never told me. So one of the blacks found me and gave me the password.\nThe guards are tough so don't even try to get past them without a password.";
			link.l1 = "I'll keep that in mind.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mynheer, what are you... Ah! You're robbing me! Stop!", "Just when I turn my back, you try to rob me?! How dare you!", "Take your hands off my sea chest, thief!");
			link.l1 = "Shit...";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to ransack my chest? You won't get away with this!";
			link.l1 = "Bitch!";
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
			dialog.text = LinkRandPhrase("Mynheer, please put your weapon away. You're making me nervous.", "Don't go running around with a blade, you might hurt yourself.", "Running around innocent people with a sword is not so gallant as you think, mynheer. Put it away.");
			link.l1 = LinkRandPhrase("Fine.", "All right.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Mynheer, please put your weapon away. You're making me nervous.", "Don't go running around with a blade, you might hurt yourself.");
				link.l1 = LinkRandPhrase("Fine.", "All right.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Mynheer, please put your weapon away. You're making me nervous.", "Don't go running around with a blade, you might hurt yourself.");
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
