// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "I don't want to talk to you. You attack peaceful civilians for no reason and provoke them into fights. Au revoir!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Good day, monsieur. You are new here, aren't you?";
				link.l1 = TimeGreeting()+". Yes, I suppose I am. My name is "+GetFullName(pchar)+". And you are?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, bonjour "+GetFullName(pchar)+"! "+TimeGreeting()+"! How can I help you today?";
				link.l1 = LinkRandPhrase("Bonjour, Monsieur Turam! Tell me the latest news.", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're doing. Au revoir!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Jacques Turam. Two years ago I was a respectable and wealthy merchant, owner and captain of my own fluyt. Alas, now I am as poor as a church mouse with no hope that my situation will change.\nSome people get lucky here; they find gold, jewels, ships filled with treasure, but I am not one of them. I found only a single chest of doubloons and few trinkets.\nAt least it's enough to buy food, so I don't starve... Pleasure to meet you, sir, I don't mind chatting.";
			link.l1 = "I'm glad to meet you too, Jacques. Au revoir!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Bonjour, Monsieur Turam! Tell me the latest news.", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am all ears.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What do you do here?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Tell me... I see that there are ladies on the island...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Do you want to go back, to the wide world?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "It's nothing.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "You want to hear my story? Fine. As you already know, I was a merchant. One day I sailed from Tortuga to Belize on my good old fluyt. My holds were filled with ebony and cacao - I spent all my money on the cargo.\nI'd arranged a very profitable deal with a man who wanted to buy my cargo for an extremely high price. I would've made a fortune. All was going well, not a single cloud in the sky, my ship as swift as a bird. Then trouble came.\nI was sailing near Cuba, avoiding Spanish patrols, when suddenly we were attacked by a pirate galleon. What were they doing there, in the middle of Spanish territory? We tried to flee, but the galleon was surprisingly fast.\nThe pirates caught us up and attacked. Their couleuvrines were loaded with grape shot - the first salvo took out half my crew demoralized the rest. I wanted to put up a good fight, but my crew and officers stopped me. We surrendered.\nThe pirates took our cargo and threw away our cannons. I hoped it was not the end for me; losing the cargo was a heavy blow, but I could still make money on freight contracts and until I got back on my feet.\nBut fate had other plans. The pirate bastards opened fire on my defenseless fluyt - we were a sitting duck without our guns. I can still hear the pirates' laughter...\nThe galleon sailed away and we clung to the wreck of our ship. Then a strong gale came and a wave carried me overboard. I managed to lash myself to a broken spar and stay afloat.\nI'll spare you the details about my brush with sharks. After an eternity the currents brought me to this island. That's how I survived.";
			link.l1 = "Yes, that is truly a sad story.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "I live like the rest of locals: I search for valuables on the outer ring and exchange them for food. I dream about finding an Indian chief's treasures, or a galleon filled with Spanish gold...\nI dream about eating something other than corned beef and fish - there was a man here who hunted those giant crabs. I used to pay him five doubloons a claw and dine on it for several days.\nPity he died... though I can't say anyone was surprised - hunting those crabs is a dangerous activity.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I see what you're implying. Yes, love and intrigue exist here - and why wouldn't they? Man is made for woman as woman is made for man. That's nature. You may try Gillian and Tanneke; they are young, pretty and open to courting.\nI myself have already found a woman: Natalia. She is a waitress in Sancho's tavern. A great girl, I tell you. I believe she is the only reason I didn't lose my mind during those first months living here. She has helped me a lot and now we are together.";
			link.l1 = "Ah, romantic!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Good question. I'd like that, of course. But to think about it... I am broke. I invested everything in my cargo and now both it and my ship are sunk. I have nothing left. The only way I can think to earn money now is to work for Dutch West India Company - if they hired me, of course.\nIf only I had enough money to buy a schooner and some supplies... but I don't, so I'd better stay on the island. At least here I don't have to work from dawn to dusk for a piece of bread.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Who is - ah, thief!", "Take your hands off my things, you devil!", "That's my chest! Get away from it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "How dare you riffle through my drawers!";
			link.l1 = "Quiet!";
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
			dialog.text = LinkRandPhrase("Monsieur, I beg you, put your weapon away. You are frightening me.", "You know, you are likely to injure yourself, running around with your weapon drawn.", "Don't try to impress the girls, playing the chevalier. Put it away...");
			link.l1 = LinkRandPhrase("Fine.", "Fine.", "Er, right...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Monsieur, as a citizen of this island, I ask you to put away your blade.", "It's dangerous to go around with a weapon drawn, monsieur. Please put it away.");
				link.l1 = LinkRandPhrase("Fine.", "Very well, then.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Monsieur, I beg you, put your weapon away. You are frightening me.", "I don't like when men act like pirates, walking around with their weapon ready.");
				link.l1 = RandPhraseSimple("Je suis desole, I'm putting it away.", "I am putting it away.");
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
