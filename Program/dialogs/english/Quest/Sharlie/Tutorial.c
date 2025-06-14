void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{	case "First time":
			dialog.text = "Do you want something?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "A fair sight, eh?";
			link.l1 = "This cursed sea's been trying to kill me for two months now. Hasn't succeeded yet.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "Quite so. Sometimes the ocean reminds you how small we really are.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "I've learned there are only two states at sea: boredom or terror. This... is different.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "StartSailor_1_fencing":
			dialog.text = "Ha! First time at sea, monsieur? When it's calm like this, anyone can play captain. Better enjoy it while it lasts.";
			link.l1 = ""+GetFullName(pchar)+". A nobleman, I'll have you know. Don't 'monsieur' me.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "Ha! First time at sea, monsieur? When it's calm like this, anyone can play captain. Better enjoy it while it lasts.";
			link.l1 = ""+GetFullName(pchar)+". A nobleman, I'll have you know. Don't 'monsieur' me.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_1_fortune":
			dialog.text = "Ha! First time at sea, monsieur? When it's calm like this, anyone can play captain. Better enjoy it while it lasts.";
			link.l1 = ""+GetFullName(pchar)+". A nobleman, I'll have you know. Don't 'monsieur' me.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_2":
			dialog.text = "As you wish, my lord. So then, first voyage for you, my lord "+pchar.lastname+"?";
			link.l1 = "Is it so obvious? Aye, my first. And I was not born for cramped quarters and moldering ship's food.";
			link.l1.go = "StartSailor_3";
		break;
		
		case "StartSailor_3":
			dialog.text = "Plain as day you're a landlubber, my lord.";
			link.l1 = "Mind your tongue! To a man of honor I would cast down my glove and demand satisfaction. But to a peasant like you - I'll simply cut off your ears.";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "Maybe in Paris. But out here, words like that can get a man fed to the fishes. I wouldn't go waving that blade around, my lord - and don't make the captain regret letting you walk his deck armed. Last troublemaker got sent to the hold on moldy hardtack and bilge water even the rats wouldn't touch. And you know what? The poor bastard still had to pay extra when we reached port.";
			link.l1 = "What can you expect... Fine, let's forget this misunderstanding. I keep having to remind myself this tub is nowhere near the Louvre.";
			link.l1.go = "StartSailor_5";
		break;
		
				case "StartSailor_5":
			dialog.text = "Eh? The Louvre? What's that supposed to be?";
			link.l1 = "Ha! The Louvre is a palace for the chosen few. Balls, receptions, intrigues...";
			link.l1.go = "StartSailor_6";
		break;
		
		case "StartSailor_6":
			dialog.text = "Ah... a brothel then. We've got those aplenty. Can't say they're for the chosen few - pay your coin and all's yours.";
			link.l1 = "Ha! You're not far from the mark, sailor.";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "Name's Alonso, by the way. And what brings you to the ends of the earth, my lord? I doubt you crossed the Atlantic just to argue with a sailor.";
			link.l1 = "My father is ill and cannot leave our estate in Gascony. I was tasked with finding my... elder brother. He came here on business, and we've heard nothing from him since.";
			link.l1.go = "StartSailor_8";
		break;
		
		case "StartSailor_8":
			dialog.text = "Why not just send a trusted man, instead of enduring the hardships of the sea yourself?";
			link.l1 = "Family comes first. I cannot entrust its fate to the first man I meet.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "I would have liked to - but my father insists it must be me. I have no idea why.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "And what is your brother's name?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "StartSailor_9_nobilityminus":
			dialog.text = "And what is your brother's name?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "De Monper? And you're "+pchar.lastname+"? How come?";
			link.l1 = "Don't look at me like that. I'm the legitimate son. Just took my mother's name.";
			link.l1.go = "StartSailor_11";
		break;
		
		case "StartSailor_11":
			dialog.text = "Nothing to be ashamed of. You'll fit right in - in the New World, everyone has some story. Me, for example...";
			link.l1 = "I'm not ashamed of anything! Just tell me about Martinique. Is it a big city? Like Toulouse?";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "A city? Ha! Martinique is an island. One of the largest in France's Caribbean holdings. They grow fiery coffee, mine hellish sulfur, and birth the most beautiful women in the world. A fine mix, if you ask me.";
			link.l1 = "I'm not interested in coffee or sulfur. But wait... an island? How am I supposed to find my brother on a whole island?";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "Don't fret. Saint-Pierre is a small town — not the Louvre, sure, but not the jungle either. Now Le François, God forbid — a decent man has no business there.";
			link.l1 = "If I must, I'll go to the bandits. Michel always pulled me out of trouble. Now it's my turn.";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "Not bad... for a landlubber.";
			link.l1 = "There you go again. How long till we reach this damn Martinique?";
			link.l1.go = "StartSailor_15";
		break;
		
		case "StartSailor_15":
			dialog.text = "Five days.";
			link.l1 = "Five?!";
			link.l1.go = "StartSailor_16";
		break;
		
		case "StartSailor_16":
			dialog.text = "At least. And if pirates show up — we might not make it at all. The Lesser Antilles are dangerous waters, even without valuable cargo.";
			link.l1 = "Aside from the passengers!";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "Ha-ha! Don't worry. Worst comes to worst, I'll hide you in the hold myself — no pirate would think to look for a Gascon nobleman among rum barrels! We’re not idiots, after all — mixing a live Gascon with rum. That’d blow up worse than gunpowder, ha-ha!";
			link.l1 = "Ha! Good thing the rum ran out a month ago!";
			link.l1.go = "StartSailor_18";
		break;
		
		case "StartSailor_18":
			dialog.text = "Er... better not say things like that out loud. Folks might think you're the reason we ran out of rum.";
			link.l1 = "Alright, Alonso, I won’t. I wouldn’t drink that swill anyway. As for your brilliant plan to stash me in the hold before battle — not happening.";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "Why not?";
			link.l1 = "I'm a nobleman, I handle a sword well, and I'm not hiding in the hold.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "If it comes to it — I’ll defend the ship and fight with the rest. What else?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "I’ll decide for myself when to fight and when to run. We’ll see how it goes.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "Ha. Maybe there's something to you after all. But watch out — the Caribbean loves to flay those who walk in with their noses high. You won't survive your first run-in with the pirate vanguard. Hell, some ragged thug outside Saint-Pierre will gut you before you know it.";
			link.l1 = "You don't know me at all.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "Ha. Maybe there's something to you after all. But watch out — the Caribbean loves to flay those who walk in with their noses high. You won't survive your first run-in with the pirate vanguard. Hell, some ragged thug outside Saint-Pierre will gut you before you know it.";
			link.l1 = "You don't know me at all.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_21_fortune":
			dialog.text = "Ha. Maybe there's something to you after all. But watch out — the Caribbean loves to flay those who walk in with their noses high. You won't survive your first run-in with the pirate vanguard. Hell, some ragged thug outside Saint-Pierre will gut you before you know it.";
			link.l1 = "You don't know me at all.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_22":
			dialog.text = "But I know the New World and its folk. If you're not planning to wither behind account books or serve in the governor's house — you'll need to learn everything from scratch.";
			link.l1 = "Good thing I don’t plan on sticking around.";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "That's what you think. We don't take passengers back to Europe often. Some die — from fever, a rope, or a bullet. Others stay — forever. I've seen feeble aristocrats become captains, ruthless bandits become respected planters. And brilliant officers — turn into penniless drifters.";
			link.l1 = "Tempting as hell, but I’ll be going back to France. I’ve people waiting for me.";
			link.l1.go = "StartSailor_24";
		break;
		
		case "StartSailor_24":
			dialog.text = "Ah yes, that's right. A sick father?";
			link.l1 = "Let's just say... there's a certain lady whose husband really doesn’t want me in Paris. But a few months — and the passions will cool.";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "Ha-ha-ha! Then you've definitely come to the right place. The Caribbean is a paradise for those fleeing jealous husbands. And time flies here. Give it a while — you might end up a sailor yet!";
			link.l1 = "More likely a captain. I’m no good as a common sailor, I fear. Manual labor isn’t my thing.";
			link.l1.go = "StartSailor_26";
		break;
		
		case "StartSailor_26":
			dialog.text = "In France, people rule by birthright. But aboard ship — the captain is king, judge, and God. No one knows what trials he faced to earn that hat. Here, everyone gets what they deserve. As we say on deck — to each their own.";
			link.l1 = "Nonsense. Speaking of captains — I need to talk to yours, especially since he’s been looking for me. Farewell, Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "Did you want to ask something?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "I'm from Monsieur Pinchon.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Nothing.";
			link.l2.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_2":
			dialog.text = "Ha! That four-eyes got you in on this too?";
			link.l1 = "Four-eyes?";
			link.l1.go = "AlonsoGold_3";
		break;
		
		case "AlonsoGold_3":
			dialog.text = "Have you seen his spectacles? Exactly! But don’t get me wrong — the crew respects Monsieur Pinchon. Good doctors are always valued on a ship. And he’s a decent purser, too.";
			link.l1 = "What business do you have with him?";
			link.l1.go = "AlonsoGold_4";
		break;
		
		case "AlonsoGold_4":
			dialog.text = "Uhh... Sorry, but that’s our own business. Don’t worry though — we’re not breaking any ship laws.";
			link.l1 = "What about regular laws?";
			link.l1.go = "AlonsoGold_5";
		break;
		
		case "AlonsoGold_5":
			dialog.text = "Regular laws don’t concern us. So, how much did they tally up for me?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 doubloons.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 doubloons.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 doubloons.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "I need to double-check everything. I'll come back later.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "There’s the gold. Saint-Pierre, here I come! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "There’s the gold. Saint-Pierre, here I come! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "There’s the gold. Saint-Pierre, here I come! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "Ah, Charles. Not exactly in a hurry, were you? When a ship's captain wants a word, you’re to report at once. Having trouble following orders?";
			link.l1 = "I'm not used to taking orders, Captain.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Apologies, Captain, I was delayed.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "It’s been made very clear that your ship — your rules.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (skip tutorial and start game on Martinique)";
				link.l9.go = "BetaTest_StartGame";
			}
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "I won't have my authority questioned. You’ve no idea how often misfortune befalls passengers at sea. You’re very lucky I’m interested in seeing you safely to Saint-Pierre.";
			link.l1 = "What are you talking about?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Captain_2_leadership":
			dialog.text = "Apology accepted. Enjoy the moment. You won't get sunsets like this often.";
			link.l1 = "What are you talking about?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Captain_2_sailing":
			dialog.text = "Good to see you've learned something this voyage. The captain's word is law — and sometimes it applies even ashore, far from the ship.";
			link.l1 = "What are you talking about?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "Captain. Kindly address me in accordance with maritime protocol.";
			link.l1 = "What are you talking about, Captain?";
			link.l1.go = "Captain_4";
		break;
		
		case "Captain_4":
			dialog.text = "I wanted to inform you that we’ve dropped sail and are adrift. Unfortunately, your arrival in Martinique will be delayed by a couple of days.";
			link.l1 = "But why, Captain?";
			link.l1.go = "Captain_5";
		break;
		
		case "Captain_5":
			dialog.text = "Because I decided so.";
			link.l1 = "Is this somehow related to yesterday’s encounter with the merchant convoy heading to that... what’s it called...";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "Capsterville. Listen, "+pchar.name+": we need to have a serious talk. I’m inviting you to dine in my cabin. The bell will strike soon — then we’ll have the time to talk like civilized men, finishing the ship’s last bottle of wine.";
			link.l1 = "Thank you for the invitation. I’d be honored, Captain.";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Let me know when you're ready. We still have some time, so you're free to walk around the ship — just don’t distract my crew from their work.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "Any other questions?";
			link.l1 = "(Wrap things up) I’m ready, Captain. With you — I’ll even drink Burgundy!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "What are you observing so intently through that scope... Captain?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Captain, I had the pleasure of speaking with a certain Alonso. What’s his position aboard?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Captain, tell me about your ship. A pinnace, isn’t it?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "Until next time, Captain.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Nothing in particular, just scanning the horizon. A ship adrift is easy prey.";
			link.l1 = "Looking for pirates?";
			link.l1.go = "Captain_7_question_1_2";
		break;
		
		case "Captain_7_question_1_2":
			dialog.text = "Or Spaniards. We’re sailing under the French flag without an escort, and the Lesser Antilles are a real crossroads — and Jacques Barbazon’s domain.";
			link.l1 = "Who’s that? A governor?";
			link.l1.go = "Captain_7_question_1_3";
		break;
		
		case "Captain_7_question_1_3":
			dialog.text = "Worse — one of the pirate barons. These gallows birds formed something like an organization and call themselves the Brotherhood of the Coast. They divided the Caribbean into six parts and placed a baron in each, so they wouldn’t tear each other apart.";
			link.l1 = "Why don’t the authorities do something about it?";
			link.l1.go = "Captain_7_question_1_4";
		break;
		
		case "Captain_7_question_1_4":
			dialog.text = "You’re naïve, "+pchar.name+". Piracy exists only because local authorities let them repair and resupply in selected ports in exchange for a cut of the loot. I don’t like to admit it, but the only ones actually doing anything about this black plague are the Spaniards. If not for them, we’d have to outfit our ship with pricey cannons — and hire an escort too.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Captain_7_question_2_1":
			dialog.text = "Senior sailor. I don’t know much about him, but I can tell you this: if every man has a skeleton in the closet, Alonso’s got a whole cemetery.";
			link.l1 = "Sounds like you don’t trust him.";
			link.l1.go = "Captain_7_question_2_2";
		break;
		
				case "Captain_7_question_2_2":
			dialog.text = "Not at all. Do you think it’s easy to find such experienced men for the crew? It takes at least a year and an excellent boatswain to make a gang of tavern drunks look even remotely like a crew. Besides, Alonso is also the crew’s voice. A captain doesn’t bother with talking to the lower ranks, but it’s stupid — and deadly — to forget that common sailors have interests too. Alonso represents them when needed.";
			link.l1 = "And what happens if the crew is unhappy?";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "They’ll hang me, and you’ll just get stabbed. Don’t look so pale. As long as the crew gets paid, fed, drunk, and patched up — the contract between the captain and crew is fulfilled. I don’t gamble with their lives, I don’t punish on a whim, I share the spoils, and sometimes I spoil them with free drinks and shore leave. That’s how we maintain a fragile balance — and why the ship always gets where it’s going.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "You’ve touched a nerve, "+pchar.name+"! I could talk about my beauty forever. Third-rate, twenty guns, great speed — don’t let the ‘merchant’ part fool you!";
			link.l1 = "I got the part about guns and speed. But ‘rate’? ‘Merchant’?";
			link.l1.go = "Captain_7_question_3_2";
		break;
		
		case "Captain_7_question_3_2":
			dialog.text = "Rates are a loose classification by number of guns. Seventh rate is barely a boat, while first rate is nearly a fortress. But don’t go repeating that in Europe — especially around naval officers.";
			link.l1 = "Why not? Is this some kind of sailor joke?";
			link.l1.go = "Captain_7_question_3_3";
		break;
		
		case "Captain_7_question_3_3":
			dialog.text = "They’ll take you for a complete fool and mock you. Truth is, on any serious navy, the ranking system is different and applies only to warships. But here in the Caribbean, things are done our own way, as usual.";
			link.l1 = "And what did you mean by calling your ship a ‘merchant’?";
			link.l1.go = "Captain_7_question_3_4";
		break;
		
		case "Captain_7_question_3_4":
			dialog.text = "Another loose term. Warships — tougher and shoot better. Raiders — rob and run. Merchants — can carry lots of cargo, crew, or guns, but must compromise, or else their speed becomes laughable. There are also multipurpose ships, but not much to say about them except that they adapt to their owner’s needs.";
			link.l1 = "You’re getting excited, Captain.";
			link.l1.go = "Captain_7_question_3_5";
		break;
		
		case "Captain_7_question_3_5":
			dialog.text = "I love my ship, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;
			
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "Well, lucky you — Burgundy’s all I’ve got left... Hold on, "+pchar.name+". Where did you get my old hat?!\nWait. Hey, in the tops! What’s going on up there?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "Well, lucky you — Burgundy’s all I’ve got left\nWait. Hey, in the tops! What’s going on up there?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "Forgive me, monsieur de More, but you are not allowed in there.";
			link.l1 = "I’ve been to the captain’s cabin before. You should remember that by now.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Alas, my cunning plan has failed. Farewell, sailor.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;
		
		case "OhrannikCabin_1":
			dialog.text = "Forgive me, monsieur, but the circumstances have changed.";
			link.l1 = "And what exactly has happened?";
			link.l1.go = "OhrannikCabin_2";
		break;
		
		case "OhrannikCabin_2":
			dialog.text = "There’s hardly any voyage left, and the captain would rather not have anyone cleaning out his valuables and vanishing into the bandit haven of Le Francois.";
			link.l1 = "I doubt the captain had me in mind when he gave such an order.";
			link.l1.go = "OhrannikCabin_3";
		break;
		
		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Well... you’ve got a point. And you’ve dined in the captain’s cabin more than once already. Go ahead, monsieur de More.";
					link.l1 = "That’s more like it!";
					link.l1.go = "OhrannikCabin_4";
					notification("Check passed", SKILL_Leadership);
				}
				else
				{
					dialog.text = "Insi... insinu-what? I didn’t mean anything like that, monsieur de More!";
					link.l1 = "Then you must let me through.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Monsieur, surely you understand the captain’s cabin isn’t a public thoroughfare. Orders are orders.";
					link.l1 = "Damn it, I can’t wait to get back on land. This is humiliating!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Monsieur, we’ve already discussed this. I can’t let you through.";
					link.l1 = "Stubborn as ever, sailor. Farewell.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				notification("Insufficient skill (15)", SKILL_Leadership);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "Eh... fine. I suppose no great harm will come of it.";
			link.l1 = "That’s more like it!";
			link.l1.go = "OhrannikCabin_4";
			notification("Check passed", SKILL_Leadership);
		break;
		
		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;
		
		case "OhrannikCabin_again":
			dialog.text = "Something else, monsieur? I can’t let you in — the captain is concerned about his valuables.";
			link.l1 = "Are you implying theft, sailor? Careful with your words. That’s pure insinuation!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Nothing, sailor.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "Hey, you noble oaf! What are you doing, trying to stuff the devil into the windlass?!\nYou kicked the stopper with your royal foot! Planning to send us all to the bottom, huh?!\nDo us a favor — don’t touch anything unless it’s a French runny nose!";
			link.l1 = "What is this, exactly?";
			link.l1.go = "SailorWithWindlass_2";
		break;
		
		case "SailorWithWindlass_2":
			dialog.text = "It’s the windlass, you dolt. It lifts the anchor. And if it’s not locked down — it’ll rip the ship to pieces or wrap someone up like a herring in a barrel!";
			link.l1 = "Ha... And if you turn it the other way — it lowers the anchor, right?";
			link.l1.go = "SailorWithWindlass_3";
		break;
		
		case "SailorWithWindlass_3":
			dialog.text = "No, genius, it turns back time. Too bad for you — you’re already born!";
			link.l1 = "Well, no one got hurt, right? Ships really are complex machines. I’ll be more careful.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "You're staring at the long barrel of that cannon with the same awe you had for the sunset earlier.";
			link.l1 = "I see you enjoy watching me, Alonso. Better tell me about this marvel of military engineering.";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "That’s a sixteen-pounder. Not every warship has one of those.";
			link.l1 = "Is it easy to hit something with it?";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "At point-blank range — we’ll blow anything apart. A hundred yards and we’re in the game. Beyond that — mostly noise and flame, but better than nothing.";
			link.l1 = "A hundred yards — and the enemy can do the same.";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "True. But it all comes down to the crew’s teamwork and the сannoneer’s skill. Too bad ours is asleep — he’d give you a whole lesson and then load you into the cannon himself, ha!";
			link.l1 = "The сannoneer is an officer, right?";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "Usually. Without at least a semi-competent сannoneer, it’s better to avoid fights — might as well throw the cannons overboard and run.\nMerchant captains rarely carry anything bigger than six-pounders — they count on escorts or luck.\nThat’s fair enough: with no heavy cannons or munitions, a ship sails better and has more room for cargo to sell.\nIf our captain hadn’t splurged on these beauties, we might still have some rum left. Sigh.";
			link.l1 = "Doesn’t the captain direct the gunfire personally?";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "With a good сannoneer and crew, he doesn’t need to. But let me tell you: when a captain sights the guns himself instead of barking 'Fire!' from the quarterdeck — the enemy ships end up with more holes.";
			link.l1 = "Can I fire one?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Thanks for the fascinating lecture, Alonso. You’re a real treasure trove of naval wisdom.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "Sure! But still, don't mess with the cannon and don't make the crew nervous.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "Firing it? Unlikely. To fire a shot — you'd need the captain's permission. I'll ask him now!";
			link.l1 = "No need!";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "Caa-ap'n!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;
		
		case "CaptainWithCannon_1":
			dialog.text = "What is it here, Alonso?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "Mister Charles suggests firing the cannon — strictly for training purposes.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "I thought you looked out for the crew's interests, Alonso. Yet here you are, proposing we wake the next watch and rouse everyone in the most barbaric way possible?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_7":
			dialog.text = "Seems to me it'd be wise to stir their blood and ready them. I don't like how we're drifting in plain sight. Something might happen.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "Don't jinx it!.. Fine. One shot. Blank.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "Enjoy yourselves, "+pchar.name+". We'll rouse the crew... at your expense, ha-ha!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "Spare a minute, monsieur?";
			link.l1 = "Speak, sailor.";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "A pleasure to meet you, monsieur. My name is Henry. Interested in earning a little cash?";
			link.l1 = "How much is 'a little'?";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "Five hundred pesos.";
			link.l1 = "How much?! What do you want me to do for that kind of money? Stage a mutiny?";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "Good heavens, monsieur! No need to shout!";
			link.l1 = "That's a lot of money, sailor. You could live well in Paris on that.";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "Ah, I won’t take advantage of your ignorance. Here in the Caribbean, 500 pesos is nothing. Captains and traders bring so many goods that the prices for anything remotely useful are through the roof. Sometimes a rare blade costs as much as a small ship.";
			link.l1 = "That’s insane.";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "What can I say? We’re all waiting for things to stabilize and prices to normalize. So, are you interested in earning 500 pesos?";
			link.l1 = "First, I want to know what the job is.";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "You’re surely aware of the unfortunate rum situation on the ship. But I’m convinced there are still a few bottles left somewhere. Rum in bottles isn’t the same as barrel swill. Great taste, prevents poisoning, strengthens your arm and health — a real treasure. Especially at the end of a voyage, when the horizon starts to drive you mad.";
			link.l1 = "And what would you do with it? Why not search yourself?";
			link.l1.go = "SailorWantRum_7";
		break;

		case "SailorWantRum_7":
			dialog.text = "When would I have the time? We’re short-handed, so I work for three. As for the rum, I’ll resell it — I’ll find a buyer.";
			link.l1 = "Well, I respect honesty in a man.";
			link.l1.go = "SailorWantRum_8";
		break;
		
		case "SailorWantRum_8":
			dialog.text = "So, will you take the job? I need three bottles.";
			link.l1 = "I'll try, but no promises.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "I'd rather decline. This sort of work is beneath me.";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "Pity, but I won’t hold a grudge. Have a good evening, sir.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;

		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "Yes, monsieur "+pchar.lastname+"";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "Here are your three bottles of rum.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Henry, I have something for you from Monsieur Pinchon.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Nothing.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "Always happy to be of service to him! How much am I owed this time?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 doubloons.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 doubloons.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 doubloons.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "I need to double-check everything. I’ll be back.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;

		case "RumGold_DatDeneg_gold28":
			dialog.text = "Thank you, monsieur "+pchar.lastname+". Give my regards to the treasurer.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "Thank you, monsieur "+pchar.lastname+". Give my regards to the treasurer.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold42":
			dialog.text = "Thank you, monsieur "+pchar.lastname+". Give my regards to the treasurer.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold42":
			dialog.text = "Thank you, monsieur "+pchar.lastname+". Give my regards to the treasurer.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Thank you, monsieur "+pchar.lastname+". That was slick work!";
			link.l1 = "I hope I’ll get my payment just as slick.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "Would you consider non-monetary payment?";
			link.l1 = "You're not as honest as you claim, it seems.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "No, no! If you want money, you'll get money! But I can also share some knowledge.";
			link.l1 = "What kind of knowledge?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "I can tell you a lot about seamanship you won’t find in your scholarly books.";
			link.l1 = "Alright then, give me the most expensive lesson of my life.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "Five hundred tips won’t replace five hundred coins. I’ll take the money.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Here you are, monsieur "+pchar.lastname+". And thanks again!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "I sincerely hope, monsieur "+pchar.name+", that my lesson proves useful. Do you know what navigation is?";
			link.l1 = "You’d be surprised, but I do. I can even read. Navigation is determining position in space and plotting a course, for example, of a ship.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;

		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "Ah. You mean stars and charts. No, I don’t know that stuff. That’s for the navigator or the captain. Around here, navigation means the ability to steer and command a ship.";
			link.l1 = "Who’s 'around here'?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "In the Caribbean. That’s just how it is, don’t ask me why. So, the better your navigation, the more speed and maneuverability you can squeeze out of a ship. Your crew also handles sails faster. But that’s not the most important thing.";
			link.l1 = "You sure know how to build suspense.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "The better your navigation, the larger the ship you can command! If you take a ship that’s too advanced, you’ll lose focus, energy, and even your health!";
			link.l1 = "Sounds dangerous. Strange I survived this long without knowing.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "Luckily, you don’t have to be an expert in everything. You can always hire a good navigator to cover your shortcomings. Just make sure they’re paid and loyal. Losing a navigator on a ship that’s beyond your skill — not fun.";
			link.l1 = "Thanks for the lecture, Henry. Not sure I’ll need it, but I guess you can never have too much knowledge.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "You're welcome, monsieur "+pchar.lastname+". And thank you again!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(sings) C’est la mère Michel qui a perdu son chat... Qui crie par la fenêtre à qui le lui rendra...";
			link.l1 = "What are you doing here, sailor??";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;
		
		case "OldSailor_1":
			dialog.text = "So now I'm like madame Michelle — looking for the cat. Only I don't shout — she doesn't like shouting.";
			link.l1 = "I saw her this morning — clawing at my boots again.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "That's nothing. The captain's boots had it worse. Do you like cats?";
			link.l1 = "Of course I do.";
			link.l1.go = "OldSailor_3";
			link.l2 = "Not really.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "Makes sense. Otherwise how would we deal with those damn rats?";
			link.l1 = "But you can't rely on cats forever, can you? They're quite wilful creatures.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "Pity. Cats are loved and valued aboard. Otherwise how would we deal with those damn rats?";
			link.l1 = "But you can't rely on cats forever, can you? They're quite wilful creatures.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "That's true. So we rely on arsenic. Only good luck finding that in the Caribbean. So we lose cargo — rats foul the rum, ruin the hardtack, and gnaw everything else\nAnd our purser says: 'Relax, it's like a trade tax'\nBut we know the truth: he's just lazy. If not for our dear Chantal, the captain would've had him living in the hold and catching rats himself long ago, ha-ha!";
			link.l1 = "Good luck with the cat. I must go.";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "Hold on, monsieur. A common sailor usually only sees noble passengers topside, yet here you are — all the way down in the hold!";
			link.l1 = "Curiosity killed the cat, ha-ha!";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "Taking an interest in seamanship, are you?";
			link.l1 = "Seems like every crew member is determined to make me a true sailor before landfall.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "Not surprising. Though the sea's brought many of us only sorrow, we love our work. And a sailor's always glad when someone new shows genuine interest.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;
		
		case "OldSailor_9":
			dialog.text = "Now tell me: what's the most important skill for a captain?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Navigation. It determines the size of the ship he can command.";
				link.l1.go = "OldSailor_10";
				notification("Check passed", SKILL_Sailing);
			}
			else
			{
				link.l1 = "I won't lie — I don't know.";
				link.l1.go = "OldSailor_9_1";
				notification("Insufficient skill level (6)", SKILL_Sailing);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "Don't be upset, monsieur. Talk to the crew, explore the ship. If you find the answer — I'll share something truly fascinating with you. As if you were one of us.";
			link.l1 = "I'll keep that in mind. Farewell!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "Correct! Now here's a trickier one: square sails or fore-and-aft — which are better?";
			link.l1 = "Hard to say, but I sense a trick. I’d say each has its merits.";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "Right again! Square sails are great if you've got the wind at your back. But a fore-and-aft rig can tack and catch even a crosswind. It's good to see you haven’t been wasting your time, monsieur.";
			link.l1 = "Not sure this knowledge will ever be useful... Unless I want to impress high society ladies by posing as a true sailor, ha-ha!";
			link.l1.go = "OldSailor_12";
		break;
		
		case "OldSailor_12":
			dialog.text = "Oh, I don’t know, monsieur "+pchar.name+". A noble you may be — but you treat us decently. We value that. The captain’s up to something. A black cat’s crossed your path.";
			link.l1 = "Nonsense. What are you on about, sailor?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "Word is, he sent a letter to Capsterville just days ago with a passing ship\nAnd went adrift — right at the voyage’s end, when everyone's howling for landfall.";
			link.l1 = "I don’t care for rumors. Why bother? I can just ask him. He wouldn’t deny a nobleman a straight answer.";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "You don’t know him, monsieur "+pchar.name+". He would — and how. And he’s angry now — lost his key.";
			link.l1 = "Key?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "To his chest, in the cabin. I reckon it’s lying around somewhere.";
			link.l1 = "Find the key? Me?";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "That’s up to you\nBy the way, monsieur "+pchar.name+", any rum left? Surely you didn’t give all of it to Henry, ha-ha!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "I do. Here you go.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "Afraid not. It was a miracle I even found those three bottles.";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "True enough. Good luck to you, monsieur "+pchar.name+". I’ll keep searching for that striped scoundrel.";
			link.l1 = "Good luck to you too, sailor.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "You’ve done the crew a good turn, monsieur "+pchar.name+". Here’s a little charm for luck!";
			link.l1 = "A stone with a hole? How sweet.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "Laugh all you like. Out at sea, talismans don’t hurt.";
			link.l1 = "You sailors are a superstitious bunch. Good luck to you.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "Already found the answer? What's the most important skill for a captain?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Navigation. It determines the size of the ship he can command.";
				link.l1.go = "OldSailor_10";
				notification("Check passed", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Not yet.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				notification("Insufficient skill level (6)", SKILL_Sailing);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "Hey there, sonny!";
			link.l1 = "You don't look like my father. Thank God for that.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "Ha! I'd be proud to have such a tall, noble son. But I can only father salt of the earth like myself.";
			link.l1 = "Alright, I'll take the compliment. What's the trouble?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "Need a helping hand, lad. Been ordered to stack shot by the guns — case we run into trouble in these dangerous waters. Spent half the watch hauling these iron bastards up from the hold, and my back's given out on the last crate.";
			link.l1 = "Why not just ask your mates? I thought you sailors help each other out.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "One thing our brotherhood definitely hates is hauling heavy loads without good reason. Drew the short straw today — dragging shot crates from the hold. Lousy work, beneath a sailor of my caliber. But what can you do?";
			link.l1 = "Stop your whining. I'll help. At least I'll get a look at this hold everyone keeps threatening me with.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Athlete) See this broadsword on my belt? It weighs more than you. I'll fetch your shot — no trouble at all.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "I don't do manual labor, sailor. Haul your own crates.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "Thanks, lad. Just don't throw your back out!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ожидание выстрела
			dialog.text = "How's it going, lad?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "Here's your shot. Thought they'd be bigger.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "Your name's Paul, right?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "Farewell.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "Er... y-yes.";
			link.l1 = "Your name's on the list monsieur Pinchon gave me.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "Phew, thought for a moment... Yes, Paul - that's me alright. How much have you got there for me?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 doubloons.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 doubloons.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 doubloons.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "I need to double-check everything. I'll be back later.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Thanks, lad.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Thanks, lad.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Thanks, lad.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "Any bigger and it'd be a gift to the enemy! If it hits the hull — well, maybe just splinters someone. But if it strikes the stern, it'll bounce all over the deck like a ball!";
			link.l1 = "Seen that happen before?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;
		
		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "Seen it myself, lad. Man’s real good at inventing killing machines. Take grapeshot — short range, won’t breach a hull, but it can send a dozen men straight to the next world. Or chain shot — hits the sails and turns them to ribbons! As for bombs — I’ll say nothing, never seen one, and thank God! Devil’s tools, and expensive to boot.";
			link.l1 = "I’ve already seen how deadly cannonballs are — just ask your poor back.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "Well, you've done me a real favor. And I’ll return it. Here — a nearly full bottle of prime rum, ha-ha!";
			link.l1 = "Where’d you get it? I keep hearing the rum ran out ages ago. With that kind of goods, you could’ve made anyone haul not just one, but all the crates from the hold.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "Just happened that way, lad. Thanks and farewell.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "Ah, monsieur "+pchar.lastname+". If you're planning to sleep — you're out of luck. Our cannoneer's claimed your bed. As you know, waking him is rather tricky.";
			link.l1 = "I must say, when he needs to — he hears everything perfectly well!";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "Нет.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;
		
		case "OfficerTorgovets_1":
			dialog.text = "That’s nothing. Heard Sharp’s crew once had a blind cannoneer. Said he aimed by the sound of the guns.";
			link.l1 = "You’re remarkably talkative today, monsieur boatswain.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "There’s a reason for that! We’ll be ashore soon — time to turn the leftover goods into clinking pesos. Brothels in Saint-Pierre are always happy to see those, ha-ha!";
			link.l1 = "Strange it’s you, not the purser, handling petty trade aboard.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "The purser can’t talk to people! That’s what a boatswain’s for — good with words and work, ha-ha! The purser’s got a scheme of his own, of course — but I’m not dipping into those murky waters.";
			link.l1 = "And what’s on offer today?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Last bottle of rum on the ship, a few lucky charms... and voilà! A full treasure map.";
				link.l1 = "You should be a merchant, not a boatswain! Let’s see what you’ve got.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "Anything else?";
				link.l1 = "Let’s see what you’ve got.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Charms? Like the one hanging on your chest?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Sorry... did you say a treasure map?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Maybe another time.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;

		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "Ah, sharp eyes, monsieur. Yes, the 'Coral Head' — a fine thing. Especially for me. If I have to lead a boarding party — it helps me rally the men.";
			link.l1 = "You actually believe that?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "I don’t have to believe. That’s just how the Caribbean works, and the seaman’s lot. Charms are handy things. So if you’re sticking with us, I recommend carrying a few — for different occasions.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "Oh yes. It’s not uncommon in the Caribbean. Some get lucky — hit it big. Then they either pay taxes, live quietly and long... or stash the gold in a cave. And what’s left is a grave, treasure... and a scrap of paper.";
			link.l1 = "Just like that?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "Not quite. Maps are pricey, and they attract other hunters like you. And sometimes the loot barely covers the trouble. Even the great Albert Blackwood had it rough at first. Make treasure hunting your trade — the more you find, the greater the rewards. And if you’ve got a lucky charm — all the better!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+"! Just a moment.";
			link.l1 = "Again with the lectures, monsieur Pinchon? I didn’t touch your precious ink!";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "Then what are you scribbling into your little book with? Holy water? There was no ink in the passenger inventory. Anyway, you've got bigger problems right now.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "And two hundred more — for the broken windlass. The anchor cable snapped.";
			dialog.text = "You still owe thirty pesos to the ship’s treasury — for the rain barrel you ruined. Your hilarious attempt to wash your shirt would’ve cost even more if it hadn’t rained again just then. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Just what I needed — debts right off the ship. Here you go.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Just what I needed — debts right off the ship. Here you go.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "That’s it? This isn’t a gambling debt. I’m a bit busy — you’ll have to wait until we make port.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "Pity. Right then — to business. I have a task for you.";
			link.l1 = "You’re not exactly a people person, are you?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_4":
			dialog.text = "One moment, let me count.";
			link.l1 = "Don’t forget to count the breadcrumbs I left on the table after supper.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "Congratulations. The ship’s treasury has no more questions for you. For now.\nStraight to the point — I’ve got a task for you.";
			link.l1 = "You’re not exactly a people person, are you?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "People? Not really. But I’m good with numbers.\nWhat about you, monsieur "+pchar.lastname+" — do you know how to count?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Accountant) I’m no stranger to ledgers or bills of exchange. I even know what zero means.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "Enough to stretch my father’s meager allowance through the season.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "Ooooh! Shame you didn’t tell me sooner - this voyage could’ve been far more interesting.";
			link.l1 = "You mentioned a task?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "For your own sake, I hope you never become a shipowner. You’d bankrupt yourself — and everyone else aboard.";
			link.l1 = "You mentioned a task?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Yes. Not sure if you’re aware, but the purser and the doctor — are second only to the captain.\n" +
			"Setting sail without either is a risk to your money. And without money, a ship is just a very expensive piece of wood.\n" +
			"Even a small sloop can bankrupt its captain without a purser. And the first battle without a doctor could wipe out the entire crew — triggering the long and costly process of hiring and training replacements.\n" +
			"Luckily for both of us, I serve as both. That gives me the ability to conduct personal trade and request minor services from the crew.\n" +
			"Of course, I pay generously — and now’s a good time for that.\n" +
			"I want you to take this list, this chest of doubloons — and pay the crew.\n" +
			"Exactly as listed! That’s why I asked if you could count.";
			link.l1 = "Why don’t you do it yourself? If they’re expecting pay — let them come to you.";
			link.l1.go = "OfficerKaznachey_10";
		break;
		
		case "OfficerKaznachey_10":
			dialog.text = "Too much to do right now. Just days left in the voyage — and soon, there’ll be a line of a hundred sailors demanding their pay.";
			link.l1 = "You mentioned doubloons...";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "Spanish gold coin. Hard currency. The true measure of wealth. Only the rarest, most valuable services go for these.\nThey’re stored in chests like this for convenience.";
			link.l1 = "And what do I get out of it?";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(Accountant) 150 pesos, and 5 extra doubloons — for being practically my colleague. And you’ll get a fair exchange rate between pesos and doubloons.";
			}
			else
			{
				dialog.text = "150 pesos, and the ability to exchange pesos for doubloons. It’s not much, but the job is simple.";
			}
			link.l1 = "Fine. Hand over the list and the chest.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "I’m afraid this sort of work isn’t for me. Farewell, monsieur Pinchon.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;
		
		case "OfficerKaznachey_11_otkaz":
			dialog.text = "Your choice. Just stay out of my way, monsieur "+pchar.lastname+"";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Here you go. For the love of God — don’t forget to take the doubloons from the chest, follow the list exactly, and don’t pocket any extra. I expect the empty chest back too.\nDon’t strain yourself, monsieur. Why are you carrying so much junk? I recommend stashing some things in a chest.";
			}
			else
			{
				dialog.text = "Here you go. For the love of God — don’t forget to take the doubloons from the chest, follow the list exactly, and don’t pocket any extra. I expect the empty chest back too.";
			}
			link.l1 = "As you wish. See you soon, monsieur Pinchon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
				
		case "OfficerKaznachey_12_Wait":
			dialog.text = "How did it go? Did you pay them all? Got the leftover doubloons and the empty chest?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && GetCharacterItem(pchar, "gold_dublon") >= 18)
			{
				link.l1 = "All done.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Not yet, monsieur Pinchon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "Let’s see...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "And you claimed you could count. You returned fewer doubloons than expected. That means extra work for me, not less — and that means no pay for you.";
				link.l1 = "But will you still exchange doubloons?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "And you claimed you could count. You brought back more than you should have. That means extra work for me, not less — and that means no pay for you.";
				link.l1 = "How about the exchange?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "All correct. Good to see the younger generation can still count. Thank you, monsieur "+pchar.lastname+". Here’s your pay — and a little bonus, from one professional to another.";
					link.l1 = "And the exchange?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "All correct. Glad to see young people treat money responsibly. Thank you, monsieur "+pchar.lastname+". Here’s your pay.";
					link.l1 = "Still doing exchanges?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "Why not. 115 pesos per doubloon. Come to me if you’re interested.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Of course. 105 pesos per doubloon. Come to me if you’re interested.\nLet me give you some advice: if fate ever puts you in charge of a ship, hire a treasurer first thing. Even a poor one will save you a fortune.";
			link.l1 = "Thank you, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "Of course! 100 pesos per doubloon — a fair rate. Caribbean banks would charge you more.\nLet me give you some advice: if fate ever puts you in charge of a ship, hire a treasurer first thing. Even a poor one will save you a fortune.";
			link.l1 = "Thank you, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;
		
		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "Loafing around, monsieur "+pchar.lastname+"?";
			link.l1 = "You got assigned to the hold too?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;
		
		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "I’m the ship’s doctor, "+pchar.lastname+"! Soon the wardroom will be full of wounded, and I’ll see more blood than any fighter. And even if I were just the treasurer, I’d still take my place in the line of fire. No, the only one who was sent to rest in the cozy hold is you.";
			link.l1 = "Then what are you doing down here?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "The battle won't start for a couple hours, so it's the perfect time to close the daily accounts. You have my chest of doubloons, de Maure. Kindly return it.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "Take it. And don't show your face down here again.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "I left your junk somewhere else.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			dialog.text = "I had no intention of it. I'm not a landlubber - my place isn't in the hold. Farewell.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "Somewhere else... We'll discuss this after the battle - in the captain's presence. Until then.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;
		
		case "TreasurerTrade":
			dialog.text = "Interested in doubloons, monsieur "+pchar.lastname+"?";
			link.l1 = "Let’s make a deal.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Not right now.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;
		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "Cap’n, alarm! Pirates on the horizon!";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "Alonso, please escort Monsieur "+pchar.lastname+" to the hold. And make sure Monsieur Drussac is awake and has the gunners ready.";
			link.l1 = "Captain, I’m ready to fight! A nobleman can’t...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "If I can help in any way...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "Wait, does that mean no burgundy?..";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "Alonso, get him out of here. Move it, you slackers! Raise the sails!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "Alonso, get him out of here. Move it, you slackers! Raise the sails!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "Alonso, get him out of here. Move it, you slackers! Raise the sails!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
				// <-- Матрос сообщает о приближающихся кораблях
				
				// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "Devil take it! Stubborn devils!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\Spanish\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "And what are you doing here?! Abandoned your crew and hiding from the fight, you bilge rat?! I’ll gut you right now!";
			link.l1 = "Bad move crawling into my hold. I’ll gut you myself.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "You're barely standing, and most of that blood on you isn’t even yours.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Duelist) Two months. Two months I had to keep my sword sheathed. Let’s dance!";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "Heh-heh. Go on then, dandy.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "Heh-heh. Then I’ve got nothing to lose.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "What are you babbling about?!";
			link.l1 = "Two months. Two months I had to keep my sword sheathed. Let’s dance!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "At least you're alive... I'm done for. Took a hard knock to the tiller...";
			link.l1 = "What happened?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "We were boarded. Ar-r-gh! Stubborn devils!\nListen carefully: we held the gun deck, but the fun’s just beginning upstairs. I swear, they’ll be down here any minute. Take the scattergun! Devil, careful! It’s loaded!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Sharpshooter) Don’t worry about me. I’ll punch holes in anyone who tries.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "There’s grapeshot in it. Do it right, and you can take down two or three at once.\nI believe in you, "+pchar.name+". Once you fight them off, check the bodies. Maybe you’ll find a drink for me... otherwise I’m no help.";
			link.l1 = "Hang in there, Alonso. Here come the guests!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "Alright... Good job, "+pchar.name+". Did you find anything for me?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Think this is it. Though it looks a bit suspicious.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "Still looking!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;

		case "SailorAlive_12":
			dialog.text = "Not bad at all, ha-ha! Thanks, "+pchar.name+". And those three — you took them out nicely. Since you're truly a nobleman, take command. Together, we can hold this deck. And if the boys upstairs manage too — the day is ours!";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "Much better. Did you load the scattergun?";
				link.l1 = "Just doing that... Why did it go so quiet all of a sudden?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Since you're truly a nobleman, take command.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "Much better. Did you load the scattergun?";
			link.l1 = "Just doing that... Why did it go so quiet all of a sudden?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "Just for added drama. It's about to begin.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "Here we are finishing where we started. Thanks for saving my hide, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "I guess we’re even. I don’t even remember how you dragged me out of there.";
			}
			else
			{
				link.l1 = "I guess we’re even. If it weren’t for you and the boys, I’d still be there.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "You could’ve stayed in the hold like you were told. Shame the captain didn’t live to give you a proper scolding.";
			link.l1 = "We had to dig him out from under a pile of bodies. How many scoundrels did he take down?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "Some saw him drop three. Others say it was a dozen. I figure only the devil kept count.";
			link.l1 = "You still haven’t told me how it all turned out this way.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "What’s there to tell? Our sixteen-pounders didn’t save us from a single pirate brig.\n" +
			"It was on us in a flash, hit us with grapeshot while we were turning, and boarded right away. You should’ve seen the deck — nothing left for the surgeon to do.\n" +
			"Worst part of fighting pirates — no profit. Just paupers. We couldn’t even take their brig.";
			link.l1 = "So what happens next?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "The ship's afloat, and we’ve enough crew left to get you to Saint-Pierre on schedule, where I’ll look for a new captain, and you’ll find your brother and tell him all about your adventures. What comes next — only God knows.\n" +
			"But one thing’s for sure - you’ll fit in fine with us. Not bad for a land rat, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "Ha! You're about to start turning inside out. Don’t be shy. That’s just the fear leaving your body. Welcome to the Caribbean!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}