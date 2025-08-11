// Альваро Гомец - капитан
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
				dialog.text = "Señor, I will say nothing to you! You attack peaceful people without cause. ¡Vete al cuerno!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, a new face! Greetings! And when did you get here? I don't remember any recent shipwreck.";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". And my ship went down quickly and quietly in the night. I alone, of all my crew, swam to the island...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
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
			dialog.text = "I see. Oh, I forgot to introduce myself. Pardon me, senor. My name is Alvaro Gomez and I was once captain of a brig. Eh, now my fine vessel is lying at the bottom just beyond the outer ring... Much water has flowed under the bridge since then. Ah, así es la vida. Glad to meet you!";
			link.l1 = "Glad to meet you too, Señor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Anything interesting to tell me?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "I am listening, señor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "You said that you were once a captain. How did you get to the island?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What can you tell me about life on the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Tell me, do the locals live peacefully with each other? Apart from the clans, of course.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "From where do the locals get provisions?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Just as anyone else did: the storms caught me. I lost my mast and rudder, then we were taken by the current and thrown onto the reefs. My ship didn't even reach the outer ring before it was destroyed. Only a few men survived, myself included.";
			link.l1 = "Sad story...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "What can I say? We have everything we need for living. Though sometimes it gets quite dull here, and that melancholy... the first year was truly difficult. But I got used to the island. I feel bad for my poor wife Sabrina - she must think me dead. I do hope she managed to marry again, and that she is happy.\nDon't be upset about your situation, mi amigo, you'll get used to it. Visit the tavern, the store, the church, meet everyone - but don't go to the Narwhals or Rivados unless you truly must! They are tricky bastards.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Peacefully enough. We have no written laws, but if you beat someone without a strong reason or, God forbid, commit murder, you will be isolated. You may even be thrown overboard in the night.\nThere were once a couple of clanless brawlers on the island - truly wicked hombres. The first disappeared, and the second died in the cells of Tartarus after a few months spent rotting inside.\Now, all this isn't to say you can't defend yourself from violent attack, but generally, the locals are quite peaceful. Abbot is swaggering, but not aggressive. Kassel is uno bastardo, but keeps his hands clean. Pratt is an ex-convict, but he is harmless.\nWe have two ex-navy officers here - Lauderdale and Solderra. They got here while having a sea battle near the island. Both of them survived and keep making bloodthirsty plans against each other.";
			link.l1 = "Fascinating...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "From the holds of wrecks, en efecto. All provisions used to be stored in the San Augustine and shared equally. Then the pirates came and took the San Augustine - now they squeeze the island for money to pay for the same provisions we used to own!\nWe have our own caches, so we don't starve. We also fish and shoot birds, but the best meat comes from giant crabs. They have a very tasty and nourishing meat - though, they rarely come closer the outer ring.\nDiving to hunt them is too risky. There was once a man brave enough to hunt them underwater, but his luck, eventually, ran out. No one has dived for crab meat since.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ladrón! Thief!", "You think you can just take what you want?! Face steel!", "How dare you steal my belongings! Meet my sword!");
			link.l1 = "Merde!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to ransack my chests? You won't get away with this!";
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
			dialog.text = LinkRandPhrase("Ay, caramba! Put your weapon away hombre!", "People here do not take kindly to those who run around with swords drawn.", "Listen, caballero, it is not safe to run around with your sword drawn. Put it away...");
			link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "As a citizen of this city, I ask you to put away your blade.", "As a citizen of this city, I ask you to put away your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Whatever then.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful, mi amigo, running aruond with a weapon like that. You make me nervous...", "Do not wave your weapon around in front of me like that. It scares me...");
				link.l1 = RandPhraseSimple("Understood.", "I'm putting it away.");
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
