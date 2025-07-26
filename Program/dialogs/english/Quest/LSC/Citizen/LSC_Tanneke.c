// Таннеке Эверс - просто девушка
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
				dialog.text = "Leave me alone, mynheer. I don't want to talk to a man who assaults peaceful people!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Good day! Do I know you? I don't think I've seen you before...";
				link.l1 = TimeGreeting()+". I am new, it's true. My name is Captain "+GetFullName(pchar)+"";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Hello, Tanneke. What's new on the island?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're doing. Good day!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Former captain. (chuckle)";
			link.l1 = "What do you...? A-ha, I understand. No, I'm still a captain; my ship is moored off the shores of the Spanish Main. I reached this place on a barque - or, almost reached it; the barque was hold and sunk two miles offshore.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "And how did you manage to survive the storms?";
			link.l1 = "What storms? I don't remember any storms...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "How can you not? There are always storms around the island. Everybody says so.";
			link.l1 = "Well... I suppose I was lucky enough to bypass it. The sea was absolutely calm... excuse me, may I know the name of such a pretty lady?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Oh! I'm sorry, I forgot to introduce myself... My name is Tanneke. Nice to meet you.";
			link.l1 = "Nice to meet you too, Tanneke... Charmed, truly.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "And why did you trade your ship for a barque?";
			link.l1 = "I heard rumours about the Island of Justice, and decided to see it with my own eyes. I was unwilling to risk my ship, so I moored her in Blueweld and purchased a barque to explore this region...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Now I see. You are just like Adolf Barbier: read too much of Captain Alvarado and decided to look for Admiral de Betancourt's gold. Alas, captain, if such a cunning rogue as Barbier can't find it, I doubt you will.\nAnd I don't even think that there is any admiral's gold. I think Antonio made it up to make his grandfather seem important.\nWell, you'll stay with us then! Getting here was easy, but leaving is impossible - in one piece, I mean.";
			link.l1 = "Gold? Admiral de Betancourt? This is the first I'm hearing of it... Anyway, I do plan to leave the island - in one piece. It was a pleasure talking with you, Tanneke. Goodbye!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ask away, Captain...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Have you ever tried to leave the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "How is your life here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Do er... ladies need to buy food from the Admiral, or do they get it for free?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I am Dutch by birth, but I lived in Santiago. My parents sent me to work there as a servant girl for the Geraldi banking family. Have you heard of them? Three years ago one of them sailed to New Spain on a courier lugger. I was told to accompany him.\nOn the second day of our voyage, we were caught by a brigantine under the Spanish flag. Their officer came aboard our ship and had a talk with our captain - about what, I don't know. The captain became enraged and drove the officer off the lugger. As the officer returned to his ship, they fired upon us.\nWe tried to flee, but they managed to board us. I think they were after my master, Geraldi, because they rushed into his cabin, clapped him in irons, and took him away. Me and the crew were taken to the hold and locked in.\nI thought they planned to sink us, but they just sailed away. The sailors managed to escape the hold. We found the captain dead on the deck. None of us knew how to navigate properly.\nWe sailed blindly until a strong gale took us. A few hours later our lugger was thrown onto the outer ring. It's still there. At dawn, me and the few other survivors climbed into the lugger's longboat and rowed to the island.";
			link.l1 = "What a story!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "No. How would I? There are no seaworthy ships, and trying to get out on a longboat is suicide. As I said, the island is surrounded by storms.\nFive locals once tried to escape in this very manner. They built a decent longboat with strong timbers and good sails salvaged from a wrecked Indiaman. They fought the current for nine hours and finally broke into open water. A few days later, one of them returned to the outer ring, tied to the wreck of their mast... stone dead.\nNot many people were eager to leave after that.";
			link.l1 = "Horrifying...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "It's all right. It's no worse than being a servant of that puffed-up usurer's family. You just need to get used to this place, and once you do, you may even love it. Many feel that way. And the clans, they don't bother me.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Of course we buy. There is enough work for a girl: cleaning, cooking, helping others... we're not idle but neither do we break our backs. Pirates sell food cheaply to the common citizens, as opposed to the clans, whom they gouge remorselessly. So we don't starve.\nI help Gillian and Natalie and they help me, if I need. We are friends. There is another girl on the island, a Spaniard: Ramona. But she mostly keeps to herself and we are not really eager to be friends with her.";
			link.l1 = "And why is that?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Well... let's say that we've got different points of view on life. Talk to her and you'll understand.";
			link.l1 = "All right...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Who is... oh my God, thief! Help!", "Turn my back for one minute and you try to rob me?! Help!", "Decided to ransack my chests? You won't get away with this!");
			link.l1 = "Crap!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "How dare you touch my things! Somebody, help!";
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
			dialog.text = LinkRandPhrase("Please put your weapon away, mynheer. You're making me nervous.", "You know, running around with a blade is not tolerated here. Put it away.", "Mynheer, I know you are gallant. You need not prove it by waving a sword...");
			link.l1 = LinkRandPhrase("Fine.", "As you wish...", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Please put your weapon away, mynheer. You're making me nervous.", "You know, running around with a blade is not tolerated here. Put it away.");
				link.l1 = LinkRandPhrase("Fine.", "As you wish...", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Please put your weapon away, mynheer. You're making me nervous.", "Mynheer, I know you are gallant. You need not prove it by waving a sword...");
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
