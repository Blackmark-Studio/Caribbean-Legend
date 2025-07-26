// Куранай - индеец
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
				dialog.text = "Paleface dog hurt white brothers and sisters. I not talk with you. Go.";
				link.l1 = "Oh...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "What white brother want?";
				link.l1 = TimeGreeting()+". 'White brother'? Tell me, why do you Indians, call us either white brothers or paleface dogs, hmm?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Hail, Curanai. What has been happening on the island lately?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Show me what you were able to find, I might buy something...";
					link.l3.go = "trade";
				}
				link.l5 = "Just wanted to see how you're doing. Goodbye!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "We all live in peace here, white brother. I not call white brother paleface dog. Not all paleface are dogs, I call a lot Indians 'redskin dog.'";
			link.l1 = "You sound like a philosopher.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "I not understand you, white brother. What means 'philosopher'?";
			link.l1 = "It doesn't matter, redskin brother. I just like the way you think. My name is "+GetFullName(pchar)+". What's yours?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Curanai be my name. I glad to know white brother's name.";
			link.l1 = "Curanai... Well, see you around!";
			link.l1.go = "exit";
			link.l3 = "I want to ask you a few questions about the island, Curanai.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ask, white brother. I answer.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What do you do on the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Do you want to go home?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Do you live peacefully on the island? Do fights or quarrels happen here?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I and seven warriors of my tribe decide to sail to little island not far from our island, visible in clear day. We make a raft of bamboo and sail. But storm take us suddenly and carry us into open sea. We not realize how fast our land and island disappeared.\nWe sail the sea many, many nights and days. All my brothers die from thirst and hunger. I alone am left - spirits take pity on I and bring raft to this island.";
			link.l1 = "I see... sad story.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "I fish; hit fish with harpoon. Rarely, rarely hit big crab. Then I happy; crab is tasty, very tasty. One crab enough for few days. And I also dive to bottom in one place, where no big crabs are. Pick yellow stone, blue stone, black stone, and pearl. Big and small. Then I sell them to white brother, white sister.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I want to go home. But where is home? I don't know where village is or how to sail there.";
			link.l1 = "Hmm, I'm so sorry...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Narwhal and Rivados tribes fight often, one against another. There are two chieftains; one hates the other. Someday, one kill the other. I see this. Rest of us live in peace and don't hurt anyone. Sometimes white brothers drink fire water and swear... but no killing. ";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Stop, paleface dog! No take what you not own!", "Paleface dog take when I not look?! No!", "That mine, paleface dog! I not let you take what isn't yours!");
			link.l1 = "Shit!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to ransack my chests? You won't get away with it!";
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
			dialog.text = LinkRandPhrase("I not like seeing white brother's naked steel. Put back.", "White brothers and sisters not like seeing you run with steel. Stop, brother.", "Don't play hero, white brother. Put steel away.");
			link.l1 = LinkRandPhrase("Fine.", "Sure.", "Sorry...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "I live here in peace. It wrong to go with steel in hand.", "Hold, white brother. Put steel away, it frighten I.");
				link.l1 = LinkRandPhrase("Fine.", "Whatever then.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "White brother, put steel away. It make me nervous...", "White man only hold steel if plan to use. Put away...");
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
