// Сесил Галард - бабулька
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
				dialog.text = "I don't want to talk to you. You attack peaceful civilians for no reason and provoke them to fight. Get lost!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Want something, young man?";
				link.l1 = TimeGreeting()+". Let me introduce myself - "+GetFullName(pchar)+". I am a newcomer.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! What can I do for you?";
				link.l1 = LinkRandPhrase("Hello, Cecille. Heard any juicy gossip lately?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to know how you're doing. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "A-ah, so you're getting to know our island and its inhabitants?";
			link.l1 = "Exactly, Madame?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Halard. Cecille Halard.";
			link.l1 = "Nice to meet you, Madame Halard! It's my pleasure.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Mine as well... And how did you get here, young man? I don't remember any recent shipwreck...";
			link.l1 = "I sailed from the Spanish Main on a barque and a storm drove me here... my ship sank not far from the island.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "In that case, you are really very lucky to have made it to the island in one piece. Storms rarely touch the island itself, but in the waters surrounding it, they can appear without warning and thrash even the most well-founded ships!\nSo consider yourself lucky and get used to the place. I don't want upset you, but while getting here is easy, leaving the island is almost impossible. No one has managed to do so - and survive - for the last ten years.";
			link.l1 = "Forgive me, but I won't give in to despair so easily. Glad to have met you, Madame Halard, 'til next time!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Yes, young man?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "And how did you get here, madame?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "You've been living here a long time, haven't you?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "What can you tell me about the locals?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Who are the most interesting people who live here?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "It was so long ago, I barely remember how it happened. I know I was shipwrecked, but as for the details... (shrug)";
			link.l1 = "Huh.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Since I was a little girl. Sometimes I almost believe that I was born here... but that's not true, of course. However, I will certainly die here.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "There's not much I can say, young man... Justice Island takes all kinds: white folk, Negroes, Indians, escaped slaves, nobles, state convicts, sailors... and there were even more of them before. Everybody has their story and their habits. One person is happy to be here, another dreams constantly of leaving.\nThen you have the clans - Narwhals and Rivados - and they are balanced out by the pirates. You see a mix of people here that exist nowhere else in the world, and in relative peace and harmony, too...";
			link.l1 = "Fascinating...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Herr Schmidt, the Narwhal mechanic-inventor... Sancho Carpentero, the local bartender... And now we also have Admiral Shark Dodson with his friend, Layton Dexter.\nBut really, you should go and meet some of these people for yourself. You have no idea how many interesting stories we Justice Islanders have.";
			link.l1 = "I will consider that...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ah, thief! Stop right there!", "Robbing an old women when her back is turned? How dare you!", "Decided to ransack my chests? You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Robbing an old women when her back is turned? How dare you!!";
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
			dialog.text = LinkRandPhrase("Put your weapon away, young man. It makes me nervous.", "You know, bad things happen to people who wave their weapons around on this island. Put it away.", "Young man, sheathe your sword. You'll frighten an old woman to death!");
			link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Put your weapon away, young man. It makes me nervous.", "You know, bad things happen to people who wave their weapons around on this island. Put it away.");
				link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Put your weapon away, young man. It makes me nervous.", "Young man, sheathe your sword. You'll frighten an old woman to death!");
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
