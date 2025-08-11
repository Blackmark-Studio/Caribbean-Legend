// Джиллиан Стайнер - просто девушка
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
				dialog.text = "Get away from me! I don't talk to men who start fights in the street.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh... hello! You scared me. I didn't hear you coming... Can I help you?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". I am a newcomer to this island. I'm getting to know the locals and I couldn't resist meeting such a pretty lady. What is your name?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Can I help?";
				link.l1 = LinkRandPhrase("Jillian! How are you? What's new?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're doing, madame. Farewell!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "You make me blush, sir, but it is my pleasure. Thank you for the compliment. My name is Jillian, Jillian Steiner.";
			link.l1 = "A pleasure indeed, Jillian.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "You say you are new here? Tell me, how did you get here? Have you survived a shipwreck?";
			link.l1 = "Well... something like that. I sailed here on a barque and almost got through the reefs, but unfortunately I struck the outer ring and my ship sank. I alone, out of all my crew, managed to swim here.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Oh! So you sought out the island? Incredible!";
			link.l1 = "Yes, I was a little mad. I decided to find the legendary Island of Justice, and now I have. Though... I'm not sure how I'll leave.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "You are either very brave or very reckless. To sail here voluntarily... now you're stuck here with us; nobody has managed to leave this place in years.";
			link.l1 = "I still have hope. All righ, Jillian, thank you, I'll let you get on with your day. Goodbye for now, madame!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Yes, sure, "+pchar.name+". I'm listening.";
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
				link.l3 = "And how do you spend your days?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "You say you are not married... Hasn't such a pretty girl got admirers?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I sailed from England with my parents. We were poor and wanted to start a new life, in the New World, and... well, my parents died when our ship was caught by a storm. I barely survived. I reached a wreck on the outer ring and lay there unconscious for a day until someone found me.\nI've started a new life, but perhaps not the one my parents dreamed of.";
			link.l1 = "I'm sorry...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "And go where? Who would take me in? I have no home, no husband, and no money. I've never known anyplace but London's slums... and this island. If it's my fate to live here, so be it - it's not the worst thing that could've happened to a girl.";
			link.l1 = "Fair enough, I suppose.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I mostly help Brother Julian in the church. I also do some odd jobs in Axel's shop - that's how I make coin; I can't clamber around the shipwrecks at the outer ring.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tee-hee... admirers, yes, but none who are worth a damn. I don't like any of them and I don't want to live with a man I don't like. The men I do like take no notice of me at all. I am just a common poor girl...";
			link.l1 = "I am certain you will find someone, and you have so much life ahead of you...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ah, thief!", "Take your filthy hands off that, that's mine!", "I did not give you permission to open my chest!");
			link.l1 = "Shit!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Take your hands off my chest, thief!";
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
			dialog.text = LinkRandPhrase("Sir, please, put your weapon away. You're scaring me.", "People on this island don't like it when you run around with a sword.", "Men running around with swords don't impress me. Put it away.");
			link.l1 = LinkRandPhrase("Fine.", "Fine.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "People on this island don't like it when you run around with a sword.", "Please put your sword away, sir. Armed men running around makes us nervous.");
				link.l1 = LinkRandPhrase("Fine.", "I beg your pardon...", "Sorry, madame...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Sir, please, put your weapon away. You're scaring me.", "Men running around with swords don't impress me. Put it away.");
				link.l1 = RandPhraseSimple("Sorry...", "I am putting it away.");
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
