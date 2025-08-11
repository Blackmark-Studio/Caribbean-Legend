// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "Begone, sir! You assault the innocent and brawl like a common brigand! Out of my sight!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Good day, sir. I am glad to meet a nobleman here.";
				link.l1 = TimeGreeting()+". Actually I've been so long amongst the common folk during my time in the Caribbean that I've started to forget I am noble.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! Good to see you! What do you say?";
				link.l1 = LinkRandPhrase("Good day, Joseph! What's new on the island?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to give you my regards. Goodbye!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Oh, and a modest nobleman at that! A true gentleman! I think that you and I will be friends - you are not like that pompous Abbot... Let me introduce myself: Captain Joseph Lauderdale of the Commonwealth Navy.";
			link.l1 = "Well met, Captain. "+GetFullName(pchar)+" at your service!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Life is quite boring here, so visit the tavern in the evening and we can have a glass of wine and talk like gentlemen.";
			link.l1 = "I will keep that in mind, sir. Goodbye for now!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Good day, Joseph. How are things?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "It would be my pleasure to answer your questions, sir.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What kind of services can be found on the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Being a navy man, what's your opinion about the pirates' dominance here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "I've seen a lot of locked chests around the island. People don't trust each other, do they?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "By doing my duty. I was fighting a Spanish sloop-of-war, a vessel we believed responsible for plundering several English traders. The action lasted hours. We almost got them, but a sudden storm ruined the game: both our ships were wrecked near the outer ring.\nFortune has a sense of humor, for both I and my Spanish counterpart survived. Perhaps you've already met him - his name is Lorenzo Solderra, a rare Papist bastard. Be wary of him.";
			link.l1 = "Thank you for your tale, I'll consider your warning...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "If you need to rest, visit Sancho's tavern. He'll always provide you with food, drink, and a bed. If you need powder, shot, cold steel and the like, go to Axel Yost; he owns the local shop. Brother Julian offers medicines and sells holy amulets in his church.\nThe Narwhals have a very talented blacksmith, name of Jurgen Schmidt. They say that he crafts the most exquisite blades. There's another talented craftsman among the Narwhals, but I never learned anything about him.\nIf you run afoul of the pirates or the other clans, see Giuseppe Fazio; he functions as a sort of local diplomat between the clans.";
			link.l1 = "Thanks for the information!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I can't say I like it, but there's nothing I can do about it - and even I must admit they established peace on the island in record time. Before the pirates arrived, the clans fought each other almost daily with no regard for the innocents caught in the middle.\nMoreover, the pirates sell food at a fair rate; citizens get good nutrition cheaply. But the pirates gouge the clans as revenge for attacking them when they first arrived.\nI know a very smart man among the pirates: Layton Dexter. He's in charge of all their trade. I had a talk with him once. I wonder how such a talented and educated man - who knows tactics, cartography and economics - wound up joining a band of pirates.\nYou know it only took him a few days to make a map of this whole island? I saw it, it has almost everything. I believe he made it in anticipation of a war between the clans...";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "It's prudence, my friend, prudence. They say that long ago, thievery was common on the island - at least until new locks were installed on all the chests.\nAnd yet... there is still someone who can get the chests open. Though he only steals rum and cheap jewelry, never gold or money.\nEvery lock is unique, no duplicate keys exist - Jurgen Schmidt made sure of that. He crafts not only blades but also locks and keys. I was told that outdoor chests don't contain valuables, that serious items are always held within the ships.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("I thought you were a nobleman, but you're just a common thief!", "Try to rob me, eh? I'll show you how we deal with thieves in the Commonwealth Navy!", "Take your hands off my sea chest, thief!!");
			link.l1 = "Oh, fuck!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Thief! Someone stop that thief!";
			link.l1 = "Shut your mouth!";
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
			dialog.text = LinkRandPhrase("Good sir, please put your blade away. You're making a scene.", "Sheathe your sword, before someone decides to make you sheathe it.", "While I appreciate valour in a man, perhaps now is not the time to be waving a sword around...?");
			link.l1 = LinkRandPhrase("Fine.", "As you wish...", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Quit your antics, sir. Put your sword away.", "Good sir, please put your blade away. You're making a scene.");
				link.l1 = LinkRandPhrase("Fine.", "As you wish...", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Good sir, please put your blade away. You're making a scene.", "While I appreciate valour in a man, perhaps now is not the time to be waving a sword around...");
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
