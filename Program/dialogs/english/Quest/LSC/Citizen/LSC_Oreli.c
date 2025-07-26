// Орели Бертин - просто жительница
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
				dialog.text = "Leave me be, sir. You hurt someone! Go away!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Good day, sir.";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+", I am a newcomer here so I am getting to know the locals.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Good day, Madame Bertine. What's new on the island?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to know how you're doing. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "I see. My name is Orelie Bertine. How did you get here?";
			link.l1 = "Let's just say that I wanted to see the legendary Island of Justice.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "So you must be one of those madmen who come here of their own free will... Well, now you'll have ample time to see the island and experience plenty of its 'justice.'";
			link.l1 = "Based on your sarcasm, do you see any problems with its brand of justice?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "No, everything is fine - but for some reason we have to pay pirates for food, which used to be free for all, not long ago. And when the clans bring their fights to our part of the Island, we're supposed to sit inside our ships to avoid being shot or stabbed.\nI mean that they are allowed to do whatever they want on our territory but we can't do the same on theirs. But it's all right, I have no problems... none at all...";
			link.l1 = "I see... Well, I am glad to have meet you. Goodbye for now, Madame Bertine!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Speak up, now.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Have you been living here a long time?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Is there anything interesting on the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "How do you feel about the clans?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Do the pirates bother you?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "A very long time. I lost count of the years... it must be seventeen... no, perhaps, eighteen... or is it twenty? What's the current date?";
			link.l1 = "So you're an old-timer?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Put it this way: I still remember when the buccaneers from Cuba traded with us, and the cleverest, most reckless Narwhals sailed to the mainland to get food in exchange for salvaged goods from ships' cargo holds.\nBut there are a lot of people now who've never known anyplace but the island, because they were born here. They are not just old-timers, but natives.";
			link.l1 = "Interesting!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sure. The island's an interesting place. Walk around and see for yourself, swim around the wrecks, visit the tavern, the shop and the church. But I promise you the novelty will fade in a week.";
			link.l1 = "All right...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "What do you want me to say? I try to avoid them. At least the Narwhals do some good to the island - they have very talented craftsmen among them - but the Rivados are just savages and pagans.\nThey live by their African laws, just as their ancestors did hundreds of years ago. Animals. The only thing they learned is to use firearms. Some people say that the Rivados commit ritual acts of cannibalism!";
			link.l1 = "What a nightmare...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "The part where they sell us our own food bothers me, but they never harm us citizens. On the contrary, they brought the clans to heel and put a stop to the constant wars.\nAnd once, there was a citizen who made trouble for people - liked waving his sword around. He wounded two locals. The pirates locked him in Tartarus for a few weeks, and now the man is quite peaceful. We don't see him often - the outer ring is his new home...";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What do you think you're doing, thief?!", "The minute I turn my back you ransack my chest?!", "Ransacking my chest, eh? You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "You thief! You'll rot in Tartarus for this!";
			link.l1 = "Shut up!";
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
			dialog.text = LinkRandPhrase("Please put your weapon away, sir. It makes me nervous.", "You know, running around with blade in hand is not tolerated here. Put it away.", "I'm sure the pirates wouldn't be happy to see you running around with a sword in hand. Neither am I, for that matter...");
			link.l1 = LinkRandPhrase("Fine.", "Fine.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Please put your weapon away, sir. It makes me nervous.", "You know, running around with blade in hand is not tolerated here. Put it away.");
				link.l1 = LinkRandPhrase("Fine.", "Fine.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Please put your weapon away, sir. It makes me nervous.", "I'm sure the pirates wouldn't be happy to see you running around with a sword in hand. Neither am I, for that matter...");
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
