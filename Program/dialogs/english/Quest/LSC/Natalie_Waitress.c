// официантка Наталия Бушелл
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! And they told me that you had drowned... Liars!";
				link.l1 = "Sure, they did! Ha! I'm fine!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Good day, "+GetAddress_Form(NPChar)+"! First time here? I haven't seen you before... I hope you'll visit us more often, Sancho offers an excellent variety of drinks. Yes, and my name is Nathalie and I help Sancho with the tavern's affairs.";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". Glad to meet you. You couldn't have seen me before. I only arrived here recently.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Got anything interesting to say?","Has anything new happened on the island?","Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to know how you're doing. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Recently? Has another ship crashed? I haven't heard anything... Or did you arrive here just like monsieur Turam, on the mast's wreckage? Oh, pardon my curiosity, it's the nature of women, you know.";
			link.l1 = "No, it's all right, Nathalie. I arrived here on a barque, but it sank. It was nice to meet you. See you around!";
			link.l1.go = "exit";
			link.l2 = "No, it's all right. Just wanted to ask you a few questions about the island.";
			link.l2.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am listening.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "You work in the tavern. What can you tell me about the owner?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "And how did you end up here?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "How many people live here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Are you never surprised to see new faces here?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. If you will excuse me...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Only good things,  "+GetAddress_Form(NPChar)+" Sancho always has a great variety of drinks - from old wines to simple ale and rum. Several years ago he found a huge stock of vintage wines. Sancho spent two months moving boxes of bottles to his store\nAnd now we are well supplied with wine only governors could afford back in the archipelago. Rum is not an issue either. Sancho can provide you not only with drinks, but also with fresh news, a good word of advice, and a warm bed for the night.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Oh, that's a sad story. Seven years ago I ran away with my suitor from my parents' home and we decided to move to Belize from Santiago. The navigator made a mistake near Main, so we sailed in the wrong direction to the north and were caught by a storm. Our ship sank not far from the outer ring\nMy suitor died that day, just like most of the others. The survivors and I started new lives here, on the Island.";
			link.l1 = "Sad story...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Quite a lot. The Rivados and Narwhal clans are strong in numbers; they've been living here for decades. There aren't many common folk, but the tavern is full every night. I barely manage to serve drinks.";
			link.l1 = "Really? Interesting.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "And why should we? There are a lot of new faces coming in very often. I don't even know how many of us live here. Sometimes I see a man for the first time and he tells me he's been living here for a year.";
			link.l1 = "Well...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, huh? Thief!","Just look at that! As soon as I got lost in contemplation, you decided to check my chest!","Decided to check my chests? You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to check my chests? You won't get away with it!";
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
			dialog.text = LinkRandPhrase("Listen, you'd better put your weapons away. They make me nervous.","You know, running around with a blade is not tolerated here. Put it away.","Listen, don't act like a medieval knight running around with a weapon. Put it away, it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.","Alright.","As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Listen, I am a citizen of this city and I'd ask you to sheathe your blade.","Listen, I am a citizen of this city and I'd ask you to sheathe your blade.");
				link.l1 = LinkRandPhrase("Fine.","Alright.","As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Be careful, pal, running around with a weapon. It makes me nervous...","I don't like it when people walk in front of me with their weapons drawn. It frightens me...");
				link.l1 = RandPhraseSimple("Got it.","I am taking it away.");
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
