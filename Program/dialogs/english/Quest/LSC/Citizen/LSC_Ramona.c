// Рамона Лоцано - горячая испанская сеньорита
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
				dialog.text = "Go away, señor. You attack ordinary people trying to go about their business.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Well, well! You're either new here or you've been hiding in one of the cargo holds, since this is the first time I've seen your face around.";
				link.l1 = TimeGreeting()+". Hiding in cargo holds is not my style. I prefer the captain's cabin... But yes, I am new here.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! "+TimeGreeting()+"! I am glad to see you! What say you?";
				link.l1 = LinkRandPhrase("Dear Ramona! How are things on the island?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see your beautiful face. 'Til next time, Ramona!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Let's get to know each other then... Captain. I am Ramona Lozano - and don't even try to call me 'Señora' Lozano. I hate it. What is your name?";
			link.l1 = ""+GetFullName(pchar)+". Delighted to meet you, Ramona.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Are you truly delighted or just being polite, "+GetFullName(pchar)+"? Tell me, are you really a captain or were you joking?";
			link.l1 = "O-ho, so many questions! May I answer them in order? First, I am truly delighted; I don't meet such pretty girls every day. Second, I am indeed a captain, but my ship is anchored on the coast of the Spanish Main right now.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Funny! And how is it, captain, that you are here, but your ship is on the coast of the Main? Aren't you afraid that your crew will scatter and your vessel will be taken from you?";
			link.l1 = "I sailed here on a barque to... to explore this part of the sea. I didn't want to risk my ship - she is my pride and joy. But at night, the barque struck some reef or wreck in the darkness, overturned, et voilà! Here I am.\nMy ship will wait for me as long as she must. Dannie Hawk will keep the lads together.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Dannie Hawk? As in... Danielle Hawk? Do you mean to tell me you sail with her?";
			link.l1 = "My hand to God, Ramona, I tell no lie; Dannie serves as my officer. I left her in command while I set out in my barque... How do you know her?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ha! Everyone in the Spanish colonies knows the pirate Danielle Hawk and her husband, Nathaniel. Yes, you, señor "+GetFullName(pchar)+", must be a tough man... Are you a pirate then? Don't worry, I get along just fine with your kind. I like tough men.";
			link.l1 = "Well, I'm not really a pirate... at the moment I'm working for Jan Svenson - trying to help Dannie find her missing husband.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "And you say you're not a pirate? You work for the Forest Devil, your first mate is Danielle Hawk, and you're searching for Nathaniel... and I am sure that you have come here for the Admiral. Right?";
			link.l1 = "Ramona, you may call me a pirate if you want. You may even call me an anchor - so long as you don't use me as one!";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "It seems you are indeed one of those really tough men, "+pchar.name+". Well, I have to go. I hope I see you around the island, I have a feeling that we might be friends... close friends.";
			link.l1 = "Why not? Good day!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Oh, really? Well, ask. I will answer if I can...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Surely you've tried to leave the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "How do you live here?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "What do you do here? I take it that food is not free, right?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "That's a long story... My stepfather is the one to blame.\nFour years ago I was living happily in Havana. My mother died and I was the sole heir to her fortune. We were not rich, but we had money - more than enough to live comfortably.\nMy stepfather didn't like that and decided to get rid of me. Of course, I only found out after two hired thugs attacked me by the city gates. Those fools told me themselves who hired them to kill me and why.\nFortunately, they were not professionals, otherwise I'd be lying in the bushes with my throat cut. The idiots decided to have some fun first.\nFate saved me: a captain like yourself happened to be passing by. He saw what was happening and killed the scum immediately - they never stood a chance. I told him about my situation, cried a bit... He knew that I had nowhere to go, so he took me aboard his ship to save me from my stepfather - first temporarily, but then...\nI believe I would have stayed with him, but two months later he ran into a patrol, lost a mast, got caught by a strong gale, and found peace at the bottom of the outer ring. I survived despite everything and joined the community of Justice Island.";
			link.l1 = "Sad story, I have no words.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Of course not, because it's impossible. I saw a man who tried to leave this place on a longboat... he returned two days later. He'd tied himself to a wrecked mast to save himself from drowning, but he was blue and stone dead.\nAnd tell me, "+pchar.name+", what am I supposed to do even if I manage to escape? Havana is too dangerous for me - my stepfather will surely try to kill me again. I have no house, no money. Where would I go? A brothel?";
			link.l1 = "Still, do you want to get back to the Caribbean?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "What do you think? Sure, I do. But it is impossible and I've just told you why. If someone could deal with my stepfather - either with cold steel or a bullet - then there would be some hope that I could go back to my old life. But who would dare do that, knowing my stepfather is a dear friend of Havana's governor? So what are we talking about? There is no way out of here...";
			link.l1 = "We'll see. Maybe the time will come...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "I simply live. There is no other option. My friends are mostly men because our two marriageable beauties - Gillian and Tanneke - don't like me. Natalie was a nice girl until she has started to spend a lot of time with those two idiots. Stupidity is contagious.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "I work like the other girls, mostly helping the men. There's a lot of work for women on the island so I keep busy. And I often get gifts - it's a usual thing here. But don't think I am some wench; I was well educated and come from a good family. I just don't play the saint... like some women...";
			link.l1 = "I wasn't thinking ill of you at all...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing - ah! Thief!", "Just look at that! As soon as I turn my back, you decide to ransack my chest!", "Ransacking my chests?! You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¡Hijo de puta! Breaking into my chest when my back is turned?!";
			link.l1 = "Be quiet!";
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
			dialog.text = LinkRandPhrase("Señor, put your weapon away. It makes me nervous.", "We don't like it when idiots run around with their swords out. Put it away.", "You look like an idiot running around with your sword out. Put it away...");
			link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, put away your blade. You're upsetting people.", "We don't like it when idiots run around with their swords out. Put it away.");
				link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Señor, put your weapon away. It makes me nervous.", "You look like an idiot running around with your sword out. Put it away...");
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
