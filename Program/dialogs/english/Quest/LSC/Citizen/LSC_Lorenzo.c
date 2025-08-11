// Лоренцо Сольдерра - испанский военный офицер
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

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
				dialog.text = "I have nothing to say to a brigand like you. Begone.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hm, you are French? I don't think we have anything to talk about.";
				link.l1 = "Interesting, and why not? I don't think international animosity serves much purpose on this island...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("At least tell me the latest news?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're doing. Goodbye, Lorenzo.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "I don't think so. I am an officer and a gentleman; I don't fraternize with enemies of El Escorial - neither in Europe, nor the Caribbean, nor this island, nor anywhere else. Go your way, señor!";
			link.l1 = "Hu-h. As you wish...";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
		case "meeting_no":
			dialog.text = "I thought I made myself clear: I don't fraternize with my country's enemies!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am listening.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¡Ladrón francés! I'll teach you a lesson!", "¡Hijo de puta! Grabbing my things when my back is turned? I'll kill you!", "Trying to steal my things? Good. I was hoping for some sword practice, francés odioso!");
			link.l1 = "Pompous don! En garde!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Trying to ransack my chests? You won't get away with it!";
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
			dialog.text = LinkRandPhrase("Francés, you'd better put your weapon away, or I might make you use it...", "You may test me with that weapon, if you feel brave... otherwise, put it away.", "Having a sword makes you neither noble nor handsome, francés. Put it away.");
			link.l1 = LinkRandPhrase("Fine.", "Alright.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Francés, you'd better put your weapon away, or I might make you use it...", "You may test me with that weapon, if you feel brave... otherwise, put it away.");
				link.l1 = LinkRandPhrase("Fine.", "No need for that... I'm putting it away.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Francés, you'd better put your weapon away, or I might make you use it...", "You may test me with that weapon, if you feel brave... otherwise, put it away.");
				link.l1 = RandPhraseSimple("No need for that, I'm putting it away.", "I am putting it away.");
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
