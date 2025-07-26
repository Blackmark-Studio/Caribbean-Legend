// Дугал Эббот - дворянин
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
				dialog.text = "I won't speak to you, sir. You attack peaceful people unprovoked. Out of my sight!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Greeting, sir. Let me introduce myself: Dougall Abbot. It is good to see a nobleman here. These peasants are tiresome. I never imagined I would have to live the rest of my life amongst such lowly persons.";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". It's good to meet you. And why don't you like the locals?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! What can I do for you?";
				link.l1 = LinkRandPhrase("Dougall! What news of the island?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're doing. Farewell!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Wait 'til you get to know them. Have you just arrived? I don't recall hearing of a new shipwreck...";
			link.l1 = "I came here on a small barque. She went down suddenly, middle of the night.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Yes, it happens - ships sink and only a few survivors haul themselves ashore. Sometimes people live here for months and you never meet them.";
			link.l1 = "I see. It was good to meet you, Mr. Abbot. Goodbye!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Greetings, Dougall! What's new?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I'm listening.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What can you tell me about the locals?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "What can you tell me about the clans?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "How's the weather? Do you get a lot of storms here?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "It was five years ago, but I still remember it as if it were yesterday. I'd set sail from Port Royal for Belize on a fluyt stuffed with high-value cargo.\nThe next day, things started to go wrong: first, my boatswain got drunk and fell overboard; then we almost hit a reef; then my navigator made a mistake and sent us north instead of south.\nA Spanish brig and galleon happened upon us. We fled and they gave chase. The galleon we left behind but the brig caught up to us.\nSince the galleon was too far back to support her smaller companion, I ordered that we come about and board the brig at once. The Spanish dogs weren't expecting that, he-he! (sigh) We won, but at the cost of most of my crew.\nMere hours later, a storm got up, and we couldn't weather it with so few crew, and now you see the result: my fluyt is wrecked somewhere on the outer ring, and me and  three other survivors live here now. Fuh!";
			link.l1 = "Quite a story.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Scum. All of them! Ptah! (spits) Low lifes of all kind. Richard Shambon is a criminal - it's written all over his face. Kassel? Killing people for him is as natural as breathing. Jasper Pratt is a convict. Musket is a drunkard. Should I even continue?\nJoseph Lauderdale is the only decent man here - except you, of course. He's an English naval officer. There are two nobles here: Antonio de Betancourt and Lorenzo Solderra - blasted Spanish scum! I won't even sit at the same table as them.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "A bunch of bastards and scum. They don't harm us, though; they're far more interested in killing each other. And they've never stopped - can't live without violence.\nI don't like pirates either but I must admit the island has grown more peaceful since their arrival; they balance out the Narwhals and Rivados.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Never. Storms often happen around the island but the island itself is always tranquil. Maybe it's God's will or some magic spell, I don't know. Sometimes we get strong wind and rain, but nothing so bad as to cause damage.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("A-ha! I knew you were just a common brigand, the moment I laid eyes on you!", "Hands off my property, scum!", "Take your filthy fingers out of my chest! I'll skewer you for this!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Don't you dare pilfer my things, you rapscallion! Away with you!";
			link.l1 = "Calm down, woman!";
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
			dialog.text = LinkRandPhrase("Sir, put your weapon away. You're making me nervous.", "Put your weapon away, you're making a scene.", "You could hurt someone, going around so armed. Put it away, sir.");
			link.l1 = LinkRandPhrase("Fine.", "Fine.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "As a gentleman of this city I demand you put your weapon away!", "I should think a gentleman like you would have no need to wave a weapon around.");
				link.l1 = LinkRandPhrase("Fine.", "All right then.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Sir, put your weapon away. You're making me nervous.", "I beg you to put away your weapon, sir. You unnerve me.");
				link.l1 = RandPhraseSimple("Very well.", "I am putting it away.");
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
