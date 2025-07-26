// Адольф Барбье - авантюрист
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
				dialog.text = "I want nothing with you. You attack peaceful civilians for no reason and provoke them into fights. Get lost!";
				link.l1 = "Um...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hello, hello... I haven't seen you before. New?";
				link.l1 = "You mean new on the island? Yes, you're right. My name is "+GetFullName(pchar)+", sailor and adventurer.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Need something?";
				link.l1 = LinkRandPhrase("Anything interesting to tell me?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see how you're doing. Goodbye!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha, just like me. I'm not a sailor, but my passion for adventures did lead me here. Now I'm going to rot in this cemetery of ships just like the others. By the way, the name's Adolf Barbier.";
			link.l1 = "It was good to meet you, Adolf. Farewell.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Anything interesting to tell me?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "Why the hell have you come into my home without permission?!";
			link.l1 = "You're being inhospitable to your guest, Adolf. I have business with you.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "I don't do business with people I don't know! Get out!";
			link.l1 = "Just like that? So you'll do business with the Narwhals, but not with me? Shame...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "What are you talking about, jester? What business with the Narwhals? This is your last chance to leave before I throw you out!";
			link.l1 = "You don't have the balls... Listen to me now! Where is the stutzen you're going to use to shoot the Admiral? Will you tell me voluntarily or must I become more persuasive?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "What? Are you mad, pal? I sold my stutzen - I don't have it anymore! And it's not your business whom I sold it to; I don't give a fuck what they do with it. And I'm not going to shoot anyone - admirals, generals, no one!. Do you understand me, fucker?";
			link.l1 = "I understand that you are a liar and a murderer, Adolf. I know that you didn't sell it but redeemed it. I also know that you've received a huge sum to repay your debts and buy this cabin--";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "This is my money! I've earned it! And I've sold my stutzen!";
			link.l1 = "You're lying, Adolf. You were hired by the Narwhals to shoot the Admiral. They gave you money to redeem your stutzen. They also paid for this place. You know better than me that the bowsprit behind this door is the only place on the island to shoot the rear balcony of Shark's residence.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "You're insane, pal! You ought to be committed! I've been waiting for Sessile to leave this cabin for half a year--";
			link.l1 = "Enough! I will search you and your cabin, I will find the stutzen - and more evidence besides! - I'm sure of it. And then we will go together to see Shark. He will look you in the eye and see the truth.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "Ah, you sick bastard! I'd rather die, than permit some mad scum touch my belongings!";
			link.l1 = "Fine, then. If you're dead, I won't need your permission.";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "Well, let's have a talk. What do you want to know?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What can you tell me about the local clans?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Have you explored the outer ring of ships?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Does the island have any connections with Cuba or Main?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I found the chronicle of a Spanish sailor, Ignacio Alvarado. He described the island in great detail, mentioning a few particular ships - San Augustine, San Geronimo, and Tartarus. All of them were part of de Betancourt's squadron, vanished over fifty years ago.\nI researched the expedition. It turned out there were a forth ship named St. Anna which was carrying the squadron's treasury: a pile of doubloons! What's more, the ships had gold ore in their holds. I decided to find the island.\nI made a deal with a captain I knew and we set sail on his schooner. You can guess how the story ends: we found the island, de Betancourt's ships, even his grandson: Antonio de Betancourt. I've been here ever since.\nThe schooner broke up on the reefs, my companion died, and I along with the rest of the survivors managed to swim here. The worst part is I never found what I was looking for - neither the St. Anna's treasury, nor any gold ore.";
			link.l1 = "Intriguing story. I've also read Alvarado's chronicle.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "The Rivados are damned pagan scum. They're the offspring of negro slaves, brought here by de Betancourt from Africa. Even though they've learned how to use blades and muskets from us white folk, they're still savages.\nThe Narwhals are good people; smart, and decent fighters. They have outstanding craftsmen among them. I know a lot of them. Perhaps one day I'll join their clan.\nThe pirates are a pain in the arse - damn them! When they arrived, they captured our supplies and now dare to sell us our own food! Bastards, eh? Pity we don't have the numbers or skill to drive them away; we're stuck with the bloody lot of them.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sure. A man has to make coin. Damn pirates demand gold, pesos or other valuables for the food. They sell it more cheaply to locals like me than to the clans, but it's no charity. Thank God there are plenty of ships on the outer ring to loot; a lot of them still remain untapped since their wreckage.\nAn interesting activity, but dangerous; you may fall into a flooded hold, break bones, get tangled in ropes, smashed by wooden beams or eaten by giant crabs - they often roam the wrecks out there.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Alas, it doesn't. They say that buccaneers and smugglers from Cuba once regularly visited this place, exchanging provisions for gold and salvage, and the Narwhals sometimes departed to visit the colonies. But that's all over, now. These days, no one wants to risk sailing on small, fragile boats past the outer ring - the storms would thrash them, and we don't have better vessels here.";
			link.l1 = "A shame...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, ah? Thief!", "Just look at that! As soon as I turn my back, you decide to ransack my chest!", "Decided to ransack my chests, eh? You won't get away with it!");
			link.l1 = "Shit!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to ransack my chests? You won't get away with it!";
			link.l1 = "Damnable girl!";
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
			dialog.text = LinkRandPhrase("Listen, you'd better put your weapon away. It makes me nervous.", "You know, running around with a blade is not tolerated here. Put it away.", "Listen, don't play a knight running around with a sword, it doesn't suit you. Put it away...");
			link.l1 = LinkRandPhrase("Fine.", "Fine.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am a citizen of the city and I ask you to lower your blade.", "Listen, I am a citizen of the city and I ask you to lower your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Fine.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful, pal, running around with a weapon like that. Makes me nervous...", "I don't like men waving their weapons in my face. It scares me...");
				link.l1 = RandPhraseSimple("Got it.", "I'm putting it away.");
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
