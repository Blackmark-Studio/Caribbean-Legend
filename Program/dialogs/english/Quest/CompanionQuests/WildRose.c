void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+"Hey, look over here!";
			link.l1 = "Quiet, "+npchar.name+", we might not be alone here.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"? Did you follow me all the way here?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "And it seems I was right to, alright! What happened here?";
			link.l1 = "If I had known, "+npchar.name+", if only I’d known...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "My God...";
			link.l1 = "Yes, it seems the poor thing suffered before dying. No one deserves such an end...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "And is that her husband over there? What the hell were they doing in the jungle?! Didn’t they hear about the runaway slaves?";
			link.l1 = "I'm afraid they won't be able to answer that question anymore...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "Do you think the one who did this is still somewhere nearby?";
			link.l1 = "Quite possible. So, we’d better keep it down – we need to spot them before they spot us.";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "Too late, "+pchar.name+". Looks like we've already been spotted. Look over there.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Well, well, boys, just look at this. It’s like a lovers’ hollow, isn’t it, heh-heh. No sooner have two lovebirds given up the ghost, than another couple shows up to take their place...";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "Very clever. But don’t you know how to count? Unlike those poor souls, we're not alone here.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "Well, dealing with us will be a bit more complicated, you can trust me on that...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "I’d like to say you’re smarter than they are – but that would be a godless lie. Even with your numbers, you wouldn’t have beaten those bastards. And your pretty girl would’ve ended up just like the one lying at your feet...";
			link.l1 = "Are you talking about the runaway slaves? Is this one of them? So, you’re Bishop’s people?";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "Yes to all your questions. For more than two days, we chased them all over the island with the soldiers. Then the bastards split up. Some retreated towards the cave, followed by the guards, and the rest bolted to the bay. They ambushed us about half a mile west of here, and we lost a few men. While we were regrouping and getting our bearings, they... had their way with that foolish girl...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		
		case "Naemnik_4":
			dialog.text = "Keep your toothpick to yourself, dandy—don’t get on my nerves or the lads’. I’d like to see how much good it’d do you if you were surrounded by a dozen of those bastards we took down in the bay. Only one of them got lucky—but not for long... As soon as that bastard ends up in Bishop’s hands...";
			link.l1 = "So you’re his mercenaries?";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "Well, clearly not the garrison soldiers. If it weren't for those layabouts, we'd have caught the scoundrels yesterday—and that fool and his wife would still be alive...";
			link.l1 = "So, this isn’t your handiwork...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Who do you take us for, huh? Sure, we’re no angels, but if we feel like it, we go to a brothel, not...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "He's lying, lying through his teeth – the filthy scoundrel! Don't listen to him, "+GetAddress_Form(NPChar)+"! We didn’t lay a finger on those poor souls!";
			link.l1 = "Oh, really? And why should we believe you and not him?";
			link.l1.go = "Naemnik_8";
			link.l2 = "Alright? Or maybe it’s you who’s lying, after all? You don’t really look like a saint to me.";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "Well, just think for yourself, for God’s sake! We were running from that beast Bishop, two days wandering through the jungle, covering our tracks – and for what? So we could now violate a poor lady and let those bloodsuckers catch up with us?! My friends barely dragged their feet onto that beach, "+GetAddress_Form(NPChar)+"! We didn’t even have the strength to fire our muskets, otherwise we’d never have let those scoundrels do their dirty work... It was all them, we saw it!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "Well, just think for yourself, for God's sake! We were running from that beast Bishop, spent two days in the jungle, covering our tracks – for what? So we could now disgrace a poor lady and let those bloodsuckers catch up with us?! My friends barely dragged their feet onto that beach, "+GetAddress_Form(NPChar)+"! We didn’t even have the strength to fire our muskets, otherwise we’d never have let those scoundrels do their dirty work... It was all them, we saw it!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "Shut up, Casper, you mangy mutt!";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "What did you say?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "Are you deaf, lady? I told him to shut his trap. Our Jerry can spin tall tales for hours – he’s got a real talent for it! Bishop wanted to cut out his tongue and make him eat it, but then he took pity. Damn shame, if you ask me!";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "But... You called him Casper, alright...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "Listen, buddy, explain to your sweetheart that people, even scum like this runt, have more than just a first name. I’ve heard that pretty women can be dumb as corks, but I’ll be damned...";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "Oh you will pay for those words, alright!";
			link.l1 = "Mary, wait! I'll handle this myself. Put your weapon away. Right now.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "Oh, so we have a real gentleman here. Well, your manners are certainly more fitting than the squealing of that little worm. He was screaming louder than his poor wife – loud enough to hear even from behind that hill. Honestly, he even helped us out a bit – that’s how we tracked down those bastards...";
			link.l1 = "Here in the Caribbean, nobility is a rare thing. Now, let's all take a breath—there's nothing noble about meeting your maker right here and now.";
			link.l1.go = "Naemnik_17";
			link.l2 = "The only scoundrels here are you lot. Apologize to Mary right now, and maybe we can avoid any bloodshed.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "Hard to argue with that. But first, calm your...";
			link.l1 = "Her name is Mary Casper. I think that explains a lot.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "Casper? Is she his daughter or something, ha-ha?";
			link.l1 = "I highly doubt that. But I hope that now you understand and will take your words back.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "Back? Or what? You’ll challenge me to a duel? Go ahead... If you’re not afraid to leave your precious one all alone in the middle of the jungle, heh-heh. The boys and I would be ve-e-ery happy with that turn of events.";
			link.l1 = "There you go, showing your true colors. The facade didn’t last long.";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "You, mister, are quite the contradiction – so peaceful, and yet such a boor. And why, pray tell, would I be begging forgiveness from this redheaded lunatic?";
			link.l1 = "Her name is Mary Casper, and...";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "Casper? Well, I'll be damned! Jerry, is that your little girl by any chance, huh? Ha-ha-ha-ha! I can't believe my ears! Who would've thought!";
			link.l1 = "Laugh it up while you can. Men like you - all bark and no breeding - treat women like dirt and think it's a sport. Born in a barn, raised by jackals - that’d explain your manners. But I suppose when your head’s stuffed with straw, there’s not much room left for decency.";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "Well, well... What a cheeky little worm. Tell me, mate, is your girl any good in a hammock?  Then again, I have my doubts... but I’d be glad to find out for myself.";
			link.l1 = "There you go, showing your true colors. The facade didn’t last long.";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "You really gave them a beating, "+GetAddress_Form(NPChar)+", - those scoundrels. May they burn in hell! Shame I couldn't help you in time. The musket I spotted on my way here was too far off. Looks like one of ours dropped it when we were running for our lives. I wish I could've shot that bastard Primer myself.";
			link.l1 = "Looks like Primer was really giving you a hard time if you decided to come back.";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "That's putting it mildly. That cur was the reason I have scars all over my back. The worst part was that he could deny us water whenever he pleased.";
			link.l1 = "Too bad not a single one of those bastards survived. We could've handed him over to the soldiers, who, I'm sure, will be here soon.";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "I'm not quite sure why, uh, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Well, you see... The commandant would have forced a confession out of him, clearing your name—and the names of your fallen friends.";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "Uh-huh, sure, ha-ha. And then William Bishop would clear me of my own skin. Heard all about it from a black fella on the plantation... Bishop doesn’t care if you’re black or white - he’s quick to deal with runaways all the same. ";
			link.l1 = "I'm afraid you'll have to go back to the plantation one way or another...";
			link.l1.go = "Djerry_5";
			link.l2 = "So you won’t go back to the plantation?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "You're quite the joker – has anyone ever told you that, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "No jokes, "+npchar.name+". You think I ended up here by chance? I went into the jungle to track down your little band, drag you all back to the plantation, and earn myself a bit of gold. But you’re the only one left. You’re not worth much on your own, so maybe I’ll let you go. But tell me, what were you thinking? You’re alone. The rest are dead. What are you hoping to do, damn you? Keep hiding in the hills and bushes until a bullet finds you, or you drop dead from fever, or get eaten by a jaguar?";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "You're quite the joker – has anyone ever told you that, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "No jokes, "+npchar.name+". You think I ended up here by chance? I went into the jungle to track down your little band, drag you all back to the plantation, and earn myself a bit of gold. But you’re the only one left. You’re not worth much on your own, so maybe I’ll let you go. But tell me, what were you thinking? You’re alone. The rest are dead. What are you hoping to do, damn you? Keep hiding in the hills and bushes until a bullet finds you, or you drop dead from fever, or get eaten by a jaguar?";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "Better this way, God knows, "+GetAddress_Form(NPChar)+" - If you ask me, that's a far better fate than dying from whatever tortures Bishop had in store for me. But honestly, it's not all that bad – there's a boat with a sail stashed near Ragged Point.";
			link.l1 = "The nearest lands to Barbados are Dominica, with its natives, and Tobago, with the Spaniards. I can't even say which is worse for you...";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "I think I’ll take my chances with the dons – smugglers and pirates often drop anchor at Tobago. Oh, I see that disapproving look, "+GetAddress_Form(NPChar)+". But I served my country faithfully. What was I supposed to do when it threw me into the quarries?";
			link.l1 = "I'm not judging, "+npchar.name+". Everyone has their own path. Now take more powder and bullets, and go. Before the soldiers show up.";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "Thank you, "+GetAddress_Form(NPChar)+". And you, young lady, uh, Mary. (bows). Of course, we’re not related, but to meet someone with the same surname in such an, uh, situation... is quite unexpected and...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "I suppose so, alright. And now, farewell, Jerry.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", is something bothering you? You said goodbye to your namesake awfully quickly.";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "I just wanted to get rid of that man's company as soon as possible... His story is full of holes, alright.";
			link.l1 = "What are you talking about, darling?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "After what we heard from Bishop’s lackey, I have no doubt those poor souls died by his hand. But before that... Casper – were you paying attention to what he was saying?";
			link.l1 = "And what didn’t sit right with you, darling?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "He claims there's a boat hidden on the beach. But over twenty people escaped from the plantation. So the boat must be pretty big, right? Jerry's a navy deserter, he knows full well it's not easy to handle a big vessel all by himself, alright...";
			link.l1 = "All he’ll have to do is set the sail and hold the course – the wind will do the rest. Sure, he’s taking a real risk, but maybe a death at sea truly is better than at the hands of a planter’s executioner.";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "Perhaps. But now I realize there’s something else that doesn’t add up... According to him, he and his friends watched from afar as the mercenaries abused that poor girl...";
			link.l1 = "Instead of running like hell to their boat... Yes, I see where you’re going with this, "+npchar.name+". Perhaps we should ask Mr. Casper a couple more questions...";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " Hey, "+npchar.name+", old friend! Hold on a minute...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " Damn it!!! Mary, watch out!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "Vile scoundrel! We saved his life, and he! So what does that mean, "+pchar.name+"? So it turns out...";
			link.l1 = "Alas, "+npchar.name+", there’s no one left alive who knows the truth about what happened here...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "We should get out of here, "+pchar.name+". If the soldiers find us here, we're in for trouble.";
			link.l1 = "You're right, Mary. Let's go...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "You know, "+pchar.name+", after all that, I could really use a good drink, alright.";
			link.l1 = "No argument there, darling. I could use a drink myself. Let’s stop by the ‘Irish Cuckold’.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "Sorry for waking you, Captain...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Well, at least you knocked, so that’s something. Now out with it—what do you want from me?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "Good thing you thought to knock, mate. If you’d just barged in, you’d be tumbling down the stairs now.\nWhat are you staring at? Out with it—why’d you drag yourself in here?";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "One of the townsfolk wishes to see you – Lewis Gernon. He says he has something important to discuss with you.";
			link.l1 = "Never heard that name before. I hope he really does have something important, to pull me away from... work like this. Let him in...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "Hello, mister "+pchar.lastname+". Miss... Casper.";
			link.l1 = ""+TimeGreeting()+", mister "+npchar.lastname+". I don't recall us meeting before. So how do you know us?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "Don't recall? Ah, I see... My face was smeared with blood and dust, I was horrified myself when I saw my reflection in the mirror just a few hours ago...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "You... you’re that man, alright, we found you and...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "And my Susan. My poor Suzie...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "We thought you were dead. And... She was your wife, alright?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "Yes, ma'am. She was my wife, and I was paralyzed with fear... and I couldn't do anything. My God, my God...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(sobbing) They beat me and made me watch...";
			link.l1 = "Stand up, "+GetAddress_Form(NPChar)+". You're not to blame. No one could have stood alone against so many cutthroats.";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "There were so many of them, so many... But still, I...";
			link.l1 = "But still, you survived, and your wife's killers are burning in hell. It's a small comfort, but it's something, Mister "+npchar.lastname+". However, there’s something I wanted to ask you about...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "Alright, mister "+pchar.lastname+"?";
			link.l1 = "Who were they? Bishop’s mercenaries or runaway slaves?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "It was Jeremy Casper and the other fugitives. You were wrong about Bruce Primer and his men.";
			link.l1 = "Bishop’s mercenaries?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "Yes. Bruce was certainly a scoundrel and did a lot of dirty work for Bishop, but he was no rapist";
			link.l1 = "That’s not how it seemed to me at the moment. But I won’t argue with you, "+npchar.name+". However, since you were conscious and saw everything, you could have stood up and...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "Forgive me, "+GetAddress_Form(NPChar)+". You can call me a miserable coward – but I just couldn’t move, I was so terrified. When those scoundrels blocked the way for Suzie and me, at first I just screamed at the top of my lungs, hoping someone would come to help.";
			link.l1 = "And they beat you up.";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "Jerry smashed me with the butt of his musket, then said he'd cut me to pieces right in front of Susan. I... I'm ashamed to admit it, but I think I even blacked out for a couple of seconds from sheer terror. And while that was happening...";
			link.l1 = "I understand you, mister "+npchar.lastname+". There is nothing shameful in your actions. Not everyone could have endured what you did. It's a pity you didn't step in – but what's done is done. Still, I'm glad we managed to send at least one of your wife's killers to the next world – even if he nearly managed to fool us.";
			link.l1.go = "Lewis_14";
			link.l2 = "So we almost got killed fighting Bishop’s mercenaries – just because you were scared, is that it? What a lovely excuse, "+npchar.name+". It's good that we managed to figure things out in the end, even if it was a bit late...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "Yes, "+GetAddress_Form(NPChar)+". I came to thank you for that. Even if at first you believed him...";
			link.l1 = "Bruce Primer did everything he could to make that happen, damn him. If only he’d watched his mouth...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "Yes, "+GetAddress_Form(NPChar)+". I came to thank you for that. Even if at first you believed him...";
			link.l1 = "Bruce Primer did everything he could to make that happen, damn him. If only he’d watched his mouth...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "Alas, we all made mistakes that day... Susan and I shouldn’t have gone for a walk in Ragged Point, Bruce should’ve held his tongue... And you shouldn’t have trusted Jeremy. But thanks to Miss Casper, justice was restored.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "I think I know what you want to ask me, mister "+sld.lastname+". But I have nothing to do with that man.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "I know, miss. I realized it the moment I walked into this room. There’s not the slightest resemblance between you and him. And yet, Susan... she was sure that nothing in this world happens by chance.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "Your wife was right. I’ve seen it for myself more than once, alright. And so has "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "All too true. However, I don't think this is the time for philosophical talk. Doubt it'll help you, "+npchar.name+". Only time can help with something like that.";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "Maybe you’re right, mister "+pchar.lastname+". Well, thank you once again, and farewell. I will pray for you and Miss Casper.";
			link.l1 = "Take care, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "I know, darling, I almost let that bastard walk free...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "A bastard named Jerry Casper.";
			link.l1 = "That's right... Wait... you don't mean to say, you think he...";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "I know it sounds very foolish...";
			link.l1 = "Absolutely! And what if your last name was Smith or Jones? There are countless people with those names walking the streets – and some of them are bound to do something wicked... And that Jerry, may he burn in hellfire – maybe he’s not even a Casper at all...";
			link.l1.go = "Mary_34";
			link.l2 = "That’s right, darling. For all we know, he wasn’t even Jerry - he easily could have used a fake name.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "And still... I know you don't understand me, but just imagine what you would think if he had your last name "+pchar.lastname+".";
			link.l1 = "It's not the same thing, Mary. "+pchar.lastname+" – is a noble family name, and...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "And yet... I know you don't understand me, but just imagine what you would think if he had your last name "+pchar.lastname+".";
			link.l1 = "It's not the same thing, Mary. "+pchar.lastname+" - a noble family name, and...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "And Caspers, well, we're just people with no name, no family, right? I suppose I should be giving thanks to our Lord every day that you even noticed me, and not some puffed-up...";
			link.l1 = ""+npchar.name+", that’s not what I meant at all – you do understand that. Members of a noble family are bound by blood – and that’s nothing like just sharing a surname with someone. Which, as I’ve said, someone could have simply taken for themselves...";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "It's not just about that, "+pchar.name+"...";
			link.l1 = "Sweetheart, we've had a long, hard day. We trekked for miles through the jungle, we could've died... and then we barely got any sleep at all. It's no wonder you've got all sorts of strange thoughts in your head. We both just need a good night's rest.";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "I don’t think it’s strange at all, but alright... let’s talk tomorrow.";
			link.l1 = "With a clear head, we'll sort everything out much faster. Lie down, darling, we need to leave this day behind.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "Are you alright, "+GetAddress_Form(NPChar)+"? You look strange, as if you've seen a ghost. Maybe you'd like some rum? Or wine? We've got an excellent selection, and you could use a little relaxation.";
			link.l1 = "To hell with the drink. I'm looking for a girl...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "Then you’ve come to the wrong place, Captain. This is a tavern, not a brothel. Step outside, and you’ll see it right across the street...";
			link.l1 = "Listen, I’m not in the mood for jokes. I’m looking for a red-haired girl in a red doublet, she’s armed. Her name is Mary Casper.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "Well, if we're not joking around, then I have nothing to tell you. My shift started an hour ago, and I haven't seen any redhead in a red coat here.";
			link.l1 = "So she left in the night... But where could she have gone?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "Good morning, my love! You slept for quite a while...";
			link.l2 = "You really made me worry there, "+npchar.name+". Don't disappear like that again, without warning...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "I didn’t want to wake you. And besides, you sometimes just disappear like that too, without saying a word...";
			link.l1 = "And you decided to pay me back in kind?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "Honestly, I just needed some time alone with my thoughts, alright. I didn’t want you to worry.";
			link.l1 = "Is something bothering you?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "Our conversation yesterday. About surnames, blood ties...";
			link.l1 = "So, you really are upset with me after all...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "Not at all, darling, that's not what I meant. It's just that I suddenly realized I know nothing about my own family. You, for example – you're the son of a noble house. The lads on the ship, every now and then, will share a story or two about their families. But me – I've got nothing to tell. I never knew my parents. Hell, I don't even know where I was born...";
			link.l1 = "Wasn't it on the Isle of Justice?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "Eric, the man who raised me, always said so. But if that’s true, why has no one on the Island ever spoken of my parents? Not a word, not even a passing mention. I once asked Donald Greenspen about it, but he couldn’t give me a clear answer.";
			link.l1 = "Or maybe did not want to.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "Exactly! I thought the same thing, alright. You know, I used to just live my life without really thinking about it. But yesterday, when we ran into that bastard Jerry... I asked myself—who was my father? My mother? Why did no one ever tell me about them, as if they never even existed? What if my father was just as much a scoundrel as that Jerry?";
			link.l1 = "It doesn't matter at all, "+npchar.name+". You were raised by other people – and they did a great job.";
			link.l1.go = "Mary_50";
			link.l1 = "I doubt that's the case. And I can hardly see why it matters, considering you never seemed to care about it before.";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "But it matters to me, "+pchar.name+", alright. I want to, I have the right to know who my parents were. Don't you agree?";
			link.l1 = "Of course I agree, without a doubt. But if we are to find out anything about your father and mother, it’ll have to be on the Justice Island. After all, you don’t even know their names, do you?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "But it matters to me, "+pchar.name+"Yeah, alright. I want to know, I have the right to know who my parents were. Don’t you agree?";
			link.l1 = "Of course, I agree, without a doubt. But if we’re to find out anything about your father and mother, it’ll have to be on the Justice Island. After all, you don’t even know their names, do you?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "I do not, dear. I can’t recall ever hearing their names, alright.";
			link.l1 = "Then it’s too early to go to the colonial archives. First, we’ll have to return to that ship graveyard and try to find some traces of your ancestry there.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "I'm glad you understand me, "+pchar.name+". Thank you.";
			link.l1 = ""+npchar.name+", you truly surprise me, you know. This is the least I can do for you, my love.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "Somehow I managed to live almost twenty years without knowing anything about them...";
			// dialog.text = "After all, it did not bother me for over twenty years...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "So, I can wait a little longer.";
			link.l1 = "I see that this is important to you, "+npchar.name+". So, I’ll try not to keep you waiting, darling. Now let’s go, we need to return to the ship. I’ll feel better knowing you’re there, at least.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "Home shores... You know, "+pchar.name+", I feel like if we came back here in ten years, everything would look exactly the same as it does now, alright.";
			link.l1 = "Maybe, "+npchar.name+", maybe. The ships of the inner ring will stay afloat, but the people living here will be different.";
			link.l1.go = "Mary_62";
			link.l2 = "I highly doubt it. Everything here is already hanging by a thread. Thanks to the genius of one mechanic.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "And I can barely remember those who lived on these shipwrecks ten or fifteen years ago. Only the people closest to me—Alan, Eric...";
			link.l1 = "I suppose that's just how it is. You can't remember everything and everyone. Names and faces fade from my memory too – from my Paris days, let alone Gascony. And here I thought that only happened to old folks.";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "And I can barely remember those who lived on these wrecks ten or fifteen years ago. Only the ones dearest to me – Alan, Eric...";
			link.l1 = "I suppose that's just how it is. You can't remember everything and everyone. Even I forget names and faces from my days in Paris—let alone Gascony. And here I thought that only happened to old folks.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "But this place... It's like another world, isn’t it? Can you imagine, some of those who arrived here not so long ago claim that time here flows almost three times faster than on the Mainland...";
			link.l1 = "Ha-ha, so how old does that make you then?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "I was being serious, "+pchar.name+", alright!";
			link.l1 = "Well, if we’re being serious, it’s time to get down to business. Is there anyone among the Narwhals older than Greenspen?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "Mmm, no, I don't think so. But I already told you he didn't say anything when I asked him about it.";
			link.l1 = "Nevertheless, I have no other ideas about who could help us make sense of what happened twenty years ago. At least, not for now. So, we're setting course for the 'Esmeralda'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "Ah, "+pchar.name+" and Mary, what a surprise! Glad to see you both... alive and well, heh-heh. Two or three ships wrecked on the outer ring just this past month - the sea’s been damn restless lately. And hey, don’t go barging into locked doors - you’ll break the bloody lock, and then I’ll be the one fixing it. You’re here to see Donald, right?";
			link.l1 = "And a good day to you, friend. We’re here to see him in person. But judging by the locked door, he’s either moved to another ship or doesn’t want to see old friends.";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "Neither, haha. Greenspen is on the outer ring right now, training.";
			link.l1 = "Drills? Really? Is he getting ready for a new war with the Rivados?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "The war never really ended, "+pchar.name+". There just haven't been as many brawls lately as there used to be. But still, in Sancho's tavern, someone ends up getting punched in the face every now and then... and sometimes a knife gets drawn, too.";
			link.l1 = "Hmm, it seems clan members didn’t use to show up at the tavern before.";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "Well, a few things have changed since you left the Island. Donald and Eddie are managing to keep the people in check. For now. But who knows what tomorrow will bring? That’s why old Donny started all this...";
			link.l1 = "I went through all that trouble to stop a massacre on the Island, just so you could play soldiers here again? And how long has he been hanging around the outer ring?";
			link.l1.go = "Schmidt_5";
			link.l2 = "Drills are all well and good, but won’t they put the already shaky truce at risk? And how long has Greenspen been drilling the lads already?";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "It's been three days. He’s supposed to be back by noon tomorrow. With the way they’re scrubbing those muskets over there, they’ll have nothing left to shoot by morning! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "It's been three days. He should be back by noon tomorrow. With the way they're scrubbing those muskets over there, they won't have anything left to shoot with by tomorrow! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "Is my cabin on the 'Ceres Smithy' still free? Or has someone already moved in?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "It's all just the same as it was the last time you were there. We haven't even unlocked the door. To be honest, we haven't cleaned or oiled the lock all this time either. So, if you need to break it, just say the word.";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "Of course. Thank you, Jurgen.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "And truly, everything is just as it was. All my things are right where I left them – as if I never left at all... This is where you and I first met, "+pchar.name+". Remember?";
			link.l1 = "Of course! You handled those two so well, You handled those two so well, I was worried I’d get chopped up too.";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "It wasn’t like that at all, alright! You literally snatched me from the jaws of death!";
			link.l1 = "It feels like fate led me here, to you.";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "Do you really think so, darling?";
			link.l1 = "Of course, my love. And ever since then, I thank it every day for bringing me straight to the 'Ceres Smithy'.";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... Tell me, what did you think when you saw me for the first time?";
			link.l1 = "Well... All I remember is that when it happened, it felt like my heart was about to burst out of my chest. You were so...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "What?";
			link.l1 = "Unlike anyone I’ve ever known before. Your grace, your voice... and that red doublet. I never stood a chance against you. You know, I’ve always wondered: why a red doublet, not a dress or a corset?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "I found it when I was nine, out on the outer ring. Back then, I loved wandering there—exploring everything new, finding things you couldn't get on the island, especially books. I was dying to try it on, but at the time, it would've just swallowed me whole. So I hid it where I kept all my other treasures—in one of the crow's nests sticking out of the water.";
			link.l1 = "And once you grew into it, you went and retrieved it?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "A few years ago, I found a book about a bold sea captain in a red coat. He wasn’t afraid of anything - faced down hundreds of enemies for the love of his life. That’s when I tried the doublet on for the first time. It makes me feel brave.";
			link.l1 = "And that irresistible charm, darling! But you know what? Right now, there’s only one thing I want... to take it off you...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "So what are you waiting for, my brave captain?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "Good morning, darling. The Narwhals have just returned to the 'Esmeralda' and the 'San Gabriel', and Donald is with them. I saw him in one of the boats, alright.";
			link.l1 = "Good morning, good morning... To be honest, after a night like that I’d sleep till noon, but you’re already up and about, fluttering around.";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "Yesterday we talked about the doublet and the crow’s nest, where I used to hide it... And suddenly I was overwhelmed by longing for those days, when I would hide up there from everyone, just to read books about the wide world in peace... I couldn’t help myself and sailed there. I used to spend hours up there, but today... I just watched the sunrise. And I realized: more than anything in the world, I want to be by your side.";
			link.l1 = "And I by yours, "+npchar.name+". Well, shall we go to Donald? We’ll have plenty to talk about.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", Mary, glad to see you! I’ve already been told about your visit yesterday. I was thinking of stopping by ‘Ceres Smithy’ myself, but you beat this old man to it. Ah, if only I were your age...";
			link.l1 = "Well, you've got plenty of energy of your own, as we've seen. How did the drills go?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "Better than I expected. We practiced boarding enemy ships, storming the cabins... All in all, we did a fine job. Sure, I pushed the lads pretty hard, but it was good for them. They haven't stretched their legs in ages, oh, it's been a while, ha-ha.";
			link.l1 = "And what, may I ask, inspired you to such feats? The Island got too quiet for your taste?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "Hmm, I can hear a note of disapproval in your voice, "+pchar.name+". I suppose you have every right to be...";
			link.l1 = "Really, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "You had to run around these rotten shipwrecks quite a bit so we wouldn’t end up cutting each other’s throats – I haven’t forgotten that. No one has.";
			link.l1 = "And this is how you repay my efforts? I guess it is true what they say - a true warrior is burdened by peace.";
			link.l1.go = "Grinspy_5";
			link.l2 = "And I have to say, I was counting on your good sense far more than on that of the pirates or the Rivados.";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "Let me finish. Yes, we managed to preserve the peace, but our differences haven’t gone anywhere. At least not with the black-skinned heathens. Just last week, one of the Narwhals was killed in a tavern brawl. But we made sure to return the favor...";
			link.l1 = "Yes, yes - that’s how it always begins.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = " Let me finish. Yes, we managed to preserve the peace, but our differences haven’t gone anywhere. At least not with the black-skinned heathens. Just last week, one of the Narwhals was killed in a tavern brawl. But we made sure to return the favor...";
			link.l1 = "Alright, that's exactly how it always begins.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "You're wrong about two things, "+pchar.name+". First of all, it isn't starting, it's continuing. If you naively thought you'd put an end to it, you were wrong. And secondly, I'm no saint to turn the other cheek. The blacks have gotten out of hand again, and I don't like it. Neither does Dexter, by the way, but he's decided he's some great politician and prefers to stay above the fray. So, after some thought, I've chosen what I think is the most... painless way to keep a fragile peace.";
			link.l1 = " You decided to scare the Rivados with your little drills?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "A couple of weeks ago, an English galleon with a military cargo washed up at the outer ring – you wouldn’t believe what was on board... But the main thing was fifty brand new muskets and some fine gunpowder. And the boats, too... The paint on them hadn’t even dried yet! The old ones were falling apart, and after the storms, there aren’t that many boats left in one piece, let me tell you...";
			link.l1 = "And all of that became the property of the Narwhals?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "Maybe I would’ve shared it with the Admiral, but since he thinks he’s the cleverest one around, I don’t want to look like a fool either. And for what it’s worth, my plan worked.";
			link.l1 = "Did Black Eddie send you a letter promising he’d stop gutting your men?";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "Black Eddie ordered his black boys to keep quiet. I was worried that in my absence, they'd get even bolder—but it turned out to be the exact opposite: the Rivados are sitting tight and keeping their distance, both from my crew and from the townsfolk they used to hassle from time to time. Negroes are negroes—they only understand strength. That's what Alan used to say, and may this ship sink to the bottom this very instant if he was wrong!";
			link.l1 = "And if after a while they start acting up again, will you rain down lead from your new muskets on the Fury and the Protector, just to scare them straight?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "The idea is bold and reckless, but I don't think it'll come to that. Maybe we'll just pretend we're planning a raid on their ships – and then Layton will finally muster his courage and step in. He's gotten a bit full of himself, sure, but the man isn't blind. Destroying either our clan or the blacks isn't in his interest – three roughly equal centers of power keep things at least somewhat balanced. If one of them falls, everything goes straight to hell. I'm sure he gets that – but for some reason, it's me who has to do his job for him.";
			link.l1 = "I might drop by to see him while we’re here—unless, of course, he decides to start one of his drills in return, ha-ha.";
			link.l1.go = "Grinspy_12";
			link.l2 = "I’ll try to drop by and talk to him about it when I get the chance. Who knows, maybe he’ll listen.";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "If anyone can convince him to keep the blacks in check, it's you, "+pchar.name+". But judging by your faces, you’re not here to chat about politics. So, out with it, what do you want?";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "My parents, Donald.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "I don't quite understand what you want from me, Mary.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "Tell me about them, please. You knew them! I asked you about them once before, and you wouldn’t answer me...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "And that's why you decided to drag Charles here, ha-ha-ha! You're something else, girl, strike me down if I'm lying! If I never spoke to you about your father and mother, it's only because I never knew them, that's all!";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "But you’re the oldest member of our clan, alright! You’ve been here for as long as I can remember...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "I arrived on the Island just under twenty years ago, already after you were born. You were just a little thing, running and crawling under tables and stools, giving poor Eric Udette no peace at all... Of course, I asked him where such a restless creature had come from – and he told me you were born on the Island a few years back. He never said a word about your father or your mother. And if he did – well, I either didn’t pay attention, or just plain forgot...";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = " It’s been so many years... I understand, Donald, I do.";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = " It’s a pity Eric’s no longer with us - he came to this place long before I did. By the way, when he used to talk about your latest escapades, he often mentioned Orelie Bertine. That old woman adored you, that much I remember clearly... Now that I think about it, I’d say she was already living on the Island when you were born. Maybe she can help you?";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = " Maybe. It’s a reason to visit her. I haven’t seen her in a long while. How inconsiderate of me, alright!";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "I don't think she's upset with you. But don't push her too hard – I heard she's unwell. Wouldn't want anything worse to happen...";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "Hush, Donald, you'll bring trouble on us! Orelie will outlive us all, alright.";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "Let's go, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "Farewell, "+npchar.name+". See you soon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "Merciful Lord, my heart nearly jumped out of my chest. You can't just go around scaring people like that.";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "Jillian! Didn’t expect to see you here, alright. What are you doing here? And where’s Orelie?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "And hello to you too, Mary. And to you, "+pchar.name+". Orelie is ill, didn’t you know? I’m looking after her at Brother Julian’s request. He sends me potions, and I give them to her, but... it doesn’t seem like they’re helping much. Right now she’s in the cabin, at the stern, sleeping. I took her there so I could tidy up here.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "We only found out today, alright. Donald told us. How is she?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "Not good. She complains of weakness, barely gets out of bed. Sometimes she mumbles something incoherent, some nonsense... I've heard so many stories about days long gone that I've lost count.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "Hmm, that's exactly the kind of story we've come for. I hope she won't refuse to talk to us...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "Is this really necessary, Mary? I don't think we should bother her when she's like this.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "This is about my parents. Orelie might have known them. It's really important to me, Jillian, alright.";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "Is there no medicine on the island that could help her get better?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "Brother Julian makes her tinctures. But they only help for a little while. And even then, she refuses to drink them, and I have to practically pour them down her throat by force. Sometimes I’m afraid she might just choke on them – I even have to make her swallow everything...";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "Poor Orelie! Is there really no one on the Island who can help her?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = " You know as well as I do that there’s no proper physician here. And what could be done anyway? Old age spares no one... ";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", maybe we could bring someone from our ship?";
			link.l1 = "I'm afraid, "+npchar.name+", what we need here isn’t a ship’s surgeon, but a skilled physician.";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "I'm ready to believe in magic right now if it helps, alright.";
			link.l1 = "Hmm... Magic? Maybe I should talk to Chimiset...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "Chimiset? The black sorcerer? "+pchar.name+", are you serious?";
			link.l1 = "More than ever. Whether he’s black or white is the last thing that concerns me right now. I don’t know who else might help Orelie, and I doubt you do either. So stand aside, and don’t you dare get in my way.";
			link.l1.go = "Jillian_16";
			link.l2 = "Absolutely. Medicine has failed her. So have Brother Julian’s prayers. Chimiset is our last hope.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "I can't believe my ears! But he is... a godless man!";
			link.l1 = "And she’s a dying woman - one breath away from forgetting her own name. Yes, he’s a sorcerer, but I’ve heard they’re capable of many things. Incredible things. And if he can restore her mind, does it really matter what god he worships?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "I can't believe my ears! But he is... a godless man!";
			link.l1 = " And she’s a dying woman - one breath away from forgetting her own name. Yes, he’s a sorcerer, but I’ve heard they’re capable of many things. Incredible things. And if he can restore her mind, does it really matter what god he worships?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", listen, I care about Orelie too... God is my witness – I’m doing everything I can to ease her suffering! But are you really going to let that black heretic perform his ritual in this cabin? What if he sets the ship on fire, or decides to sacrifice someone during it?";
			link.l1 = "We won't let that happen, "+npchar.name+", I assure you.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "And I assure you both, if anyone finds out about this... Do you have any idea what will happen here? The other townsfolk won't like it, the Narwhals especially!";
			link.l1 = "You're right about that. We shouldn't bring Chimiset here, we should take Orelie to him.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "You haven’t seen her – the old woman can barely stand on her feet. It’ll be a miracle if she doesn’t fall overboard!";
			link.l1 = "Well, sometimes all we can do is hope for a miracle. And, Jillian...";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "What else?";
			link.l1 = "I hope you'll keep this to yourself. You're a smart woman, and you've judged everything right... The unrest on the Island could easily turn into bloodshed, and nobody wants that, do we?";
			link.l1.go = "Jillian_22";
			link.l2 = "Not a word to anyone. Understood? We’ve placed our trust in you - don’t make us regret it. I believe you know as well as I do that if word of this gets out, the Island will see a massacre the likes of which it’s never known.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "Alright. But then make sure no one sees you dragging her onto the 'Protector'... Otherwise I'll have to answer some awkward questions.";
			link.l1 = "We’ll spare you the trouble of giving awkward answers. We’ll do it tonight.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "Alright. But then make sure no one sees you dragging her onto the 'Protector'... Otherwise I'll have to answer some awkward questions.";
			link.l1 = "We won't let that happen. We'll do it at night.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "Come after midnight. She’ll be here. And for God’s sake, be careful.";
			link.l1 = "You don't have to worry, "+npchar.name+", I promise we will be.";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "Come after midnight. She’ll be here...";
				link.l1 = "Alright.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "Orelie is ready. You can take her.";
				link.l1 = "Alright. Then let's go.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "Young people, where... where are we going?! This is a Rivados ship! Where is Eric?!";
			link.l1 = "Eric made friends with Eddie Black, didn’t you know?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "What are you saying, boy! Eric can't stand black folks!";
			link.l1 = "Well, what do you know! Alright, then let's go and ask him what the devil he's doing here!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "Well, look who’s come to see us! "+GetFullName(pchar)+" In the flesh! Glad to see my white brother, ha-ha! So, what brings you here?";
			link.l1 = "And hello to you, "+npchar.name+" . I wish I could just stop by for a mug of rum, but I’m afraid I have urgent business with you—or rather, with Chimiset.";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "We are forever in your debt, my friend. We'll do everything we can to help.";
			link.l1 = "That’s good to hear. Because I have no one else left to turn to.";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "Which of these ladies do you need help with, "+pchar.name+"?";
			link.l1 = "I can't tell if you're being serious or just joking, "+npchar.name+", but I’m not in the mood for jokes. It’s Orelie who needs help, of course.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "Eric! ERIC! Show yourself, you old layabout! What’s this nonsense?! Get your scrawny ass over here right now!";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "So it’s true, then... My people told me that this wreck’s got a screw loose. Now I see they weren’t lying. But I still don’t quite get what you want from the Rivados...";
			link.l1 = "Let me talk to Chimiset, and you’ll understand everything...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "Speak, my dear friend. I'm ready to listen to you carefully.";
			link.l1 = "I’ll be brief, Chimiset. Orelie has the information Mary and I need. But due to her condition, which, if I understand correctly, is simply a matter of age, we... can’t get this knowledge from her, nor can we be sure it would be accurate. I’ve heard of the wonders both Indian and African shamans are capable of – that’s why I’ve come to ask for your help, Chimiset.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "I hear you, my friend. Shamans possess mysterious and mystical powers, often beyond the understanding of outsiders, even their own kin, let alone the whites. Some call it sorcery, others – a miracle. We truly are capable of many things – but no one can make a river flow backwards... Nor can anyone stop it, either.";
			link.l1 = "What do you mean, Chimiset?";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "I'm talking about the river of time, my friend. Or the river of life—whichever you prefer. You see, you're absolutely right—the root of this poor soul's illness lies in her years, and nothing else.";
			link.l1 = "I've heard a little about that. All I know is, it's not such a rare problem.";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "You're right. People her age are often carried away to valleys of dreams, and sometimes of nightmares. They come back, only to leave again—not so much by their own will, but because of mysterious forces pulling them in. As time goes on, the illness grows stronger—until a person no longer remembers themselves or their friends.";
			link.l1 = "So, there’s nothing you can do about it?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "To drive out the sickness – no. That’s beyond me. But there’s something else I can do...";
			link.l1 = "What exactly?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "The moment this woman comes to, I'll perform a quick ritual, for which I will prepare beforehand.";
			link.l1 = "Will it at least slow the disease down, if not stop it altogether?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "Not exactly. It will force her to summon every ounce of her strength just to keep her sanity for as long as possible.";
			link.l1 = "How long is ‘as long as possible’, exactly?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "It doesn’t depend on the ritual, but on the person. Some can hold on for a week, others for a month... I heard of a man who kept his sanity and memory for almost a year, maybe even longer... And just when everyone thought he’d been cured, the sickness returned—and took him that very night.";
			link.l1 = "An hour will be enough to learn what we need. When can you perform the ritual, Chimiset?";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "I'll take the woman right now, bring her down to the hold—there's a sanctuary set up there... just for things like this. After that, it all depends on when she comes back to her senses... But I think we'll be done by morning.";
			link.l1 = "Then I won’t get in your way. And may your... God, Chimiset, help you.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "Zikomo! Help me take the white woman to the hold.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "It worked out, white brother. We managed to...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "Oh, "+GetFullName(pchar)+"! I had no idea you and Mary were back on the Island! What a wonderful surprise!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Chimiset, thank you! I don’t even know how to thank you...";
			link.l1.go = "Chimset_14";
			link.l2 = "Well, would you look at that, Chimiset pulled it off! I never doubted you for a second...";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "All the Rivados are forever in your debt, my friend! The doors of the 'Protector' are always open to you.";
			link.l1 = "I hope I won’t have to trouble you any further... Mary, Orelie, we need to get back to the 'Pluto'.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "All the Rivados are forever in your debt, my friend! The doors of the 'Protector' are always open to you.";
			link.l1 = "I hope I won’t have to trouble you any further... Mary, Orelie, we need to get back to the 'Pluto'.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "I can't even remember how I left my cabin... Ah, this old age – my memory's just gone to hell. ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "Well, well, young lady, what brings you to my cabin?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "Orelie, I...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "Orelie, I asked her to tidy up here while you were away. No need for you to strain your back with those bad knees...";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "Clean up?! You...";
			link.l1 = "Jillian, thank you for your work. (whispering) We did it. Chimiset pulled it off.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "It can't be...";
			link.l1 = "As you can see. Now, please, let us talk.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "Well, young people, thank you for escorting an old lady. I'm afraid soon I won't be able to go outside at all. My poor legs, my legs...";
			link.l1 = "If you don’t mind, "+npchar.name+", we’ll stay with you for just a little while. Mary and I have some very important business with you.";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "If I don’t have to drag myself onto another ship again, I’ll help however I can. I’m listening.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "Orelie, I want you to tell me about my parents. And about the day I was born. It happened here, on the Island, right? Donald says it did, but he wasn’t even here back then, so he can’t really know for sure. But you’ve lived here much longer than he has, alright! For more than twenty years, haven’t you?";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "Easy, easy, girl, don’t talk so fast, please! I can’t keep up with you...";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "Alright, I get it. Okay, let's go over it one more time...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "Don’t worry, Mary, I’m not that old just yet, ha-ha... I heard what you said. But since I really have lived on the Island longer than anyone, I hope you’ll treat my age with a bit of respect and understanding...";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "Of course, Orelie! How could you ever think otherwise?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "Ah, it’s just that when I look at young folks these days... no, no, we weren’t like that with our elders. But you’re not like that either, of course. I only meant to say that it’ll be easier for us if I answer your questions one at a time, not all in a jumble...";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "I understand, Orelie. Whatever’s easier for you, alright. So, you were on the Island when I was born? That is, if I was born here...";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "I came to the Island in 1633, and sometimes that day still haunts my nightmares. The storm, our 'Reprisal'—the flute my husband and I were sailing to Florida on—was tossed about by the waves, ready to capsize at any moment, and we were reciting every prayer we knew and making up new ones... And then, a crack and...";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "So you ended up here five years before I was even born, alright.";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "More or less. Things were different back then. San Jeronimo was still afloat, the outer ring of ships was half the size it is now, maybe even less... And that’s not even counting the ones that didn’t last! I’ll tell you this, youngsters - on a clear day, if you look down into the water, it’s a fright how many wrecks you can see down there...";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "We're interested in the ship my parents arrived here on. With me... or without me?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "With you, girl, with you.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "So, I was born on the Mainland after all?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "No, I meant 'with you' in a slightly different way. You were in your mother's belly and were born a week later.";
			link.l1 = "Do you find this funny, Orelie?";
			link.l1.go = "Oreli_32";
			link.l2 = "And you haven't lost your sense of humor over the years, Orelie.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "Well, I laugh at myself much more often than at others. Sorry, Mary, I didn’t mean to hurt your feelings.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "Well, I laugh at myself much more often than at others. Sorry, Mary, I didn't mean to hurt your feelings.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "It's alright, Orelie. Please – go on. What happened to my parents after I was born?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "Afterwards? Oh, my dear, the fact that both of them even survived until then is nothing short of a miracle! What a terrible storm raged that June night! When, come morning, the boat brought your mother to the inner ring, hardly anyone could believe their eyes at first—that a woman about to give birth had survived such a dreadful shipwreck. Poor Teresa, I remember it like it was yesterday...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "Teresa? Was that her name?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "Yes, that's how she introduced herself – and that was almost all she ever said. By the end of the day, she slipped into a fever and stayed that way right up until the birth. No one was sure she'd survive it, and even more so, everyone doubted the child would be born alive – after all she'd been through. But Teresa made it. She made it – and then she passed away. May God rest her soul...";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "Mother died, and I was left with my father? But then why did everyone say I was raised by Eric Udette? And...";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Mary, darling, I asked you... Don’t overwhelm me with so many questions...";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "Sorry, Orelie, I got carried away, alright. My father, he survived a shipwreck too, didn't he?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "Your father... You know, there’s not much I can say about your father—except that I wouldn’t wish a dad like him on anyone. Just a few days after you were born, he vanished, leaving you to fend for yourself. You were lucky Eric had such a kind and gentle heart—soft as a biscuit soaked in a mug of grog...";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "At least tell me his name!";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "Oh... Was it Jeffrey or John, if only I could remember...";
			link.l1 = "So, you don’t really remember, do you, "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "Are you doubting my words, young man?!";
			link.l1 = "Quiet, "+npchar.name+", easy now. I didn’t mean to offend you. It just seemed to me that you remember those days rather well, that’s all.";
			link.l1.go = "Oreli_45";
			link.l2 = "I have no doubts, "+npchar.name+". I'm just trying to remember all the details correctly - that's all. But all this confusion does make things a bit more complicated.";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "Memory is a fickle lady, "+pchar.name+", quite selective. Especially after all these years. Teresa is hard to forget – I watched her suffering all week! Oh, how sorry I felt for her!";
			link.l1 = "And her husband, wasn’t he with her?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "Memory is a fickle lady, "+pchar.name+", quite selective. Especially after all these years. It's hard to forget Teresa – I watched her suffering all week! Oh, how sorry I felt for her!";
			link.l1 = "And her husband, wasn’t he with her?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "Very rarely. He was gone most of the week – searching for medicines and potions, which were in short supply on the Island back then...";
			link.l1 = "So, he must have been a good husband - if he tried to help his wife.";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "He might have been a good husband. I never said otherwise, mind you. Don’t try to confuse me, young man!";
			link.l1 = "And I never even thought of such a thing, I swear, "+npchar.name+". It's just obvious you don't think very highly of him. And the fact that you don't even remember his name...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "I caught a glimpse of that man, almost just a shadow, in the darkness of the 'Ceres Smithy' cabin—where Herr Jürgen lives now. He only came at night, and I barely remember his face. As for his name—no one ever called him by his first name, only by his last. Casper this, Casper that...";
			link.l1 = "I understand you, "+npchar.name+". So Mary was born, and a few days later he vanished without a trace. Was he killed?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "That's a tricky question, young man. You see, it's rather hard to keep anything secret in this place—everyone's always watching. Whenever there's another quarrel—even inside the ships—the whole Island knows about it by the next day.";
			link.l1 = "No wonder.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "The bodies of the killed aren’t always found - experienced crooks sink the corpses, tying hands and feet with the chain-shots, or attaching weights like cannonballs or stones. And crabs at the bottom finish the job. But personal belongings of the dead eventually resurface.";
			link.l1 = "From the bottom?!";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "Of course not! I meant that they just catch your eye—a ring, a pistol with an engraving, a ceremonial saber... People rarely ask questions about those. You can't bring the person back, and no one wants any more trouble than they've already got.";
			link.l1 = "Did Geoffrey or John Casper have any distinctive belongings?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+" bless your soul – I can’t even remember his name, and you’re asking me questions like that! If anything did happen, I never heard talk of that thing ending up with anyone else on the Island. Back then I was working as a tavern maid, and hardly any gossip slipped past me. But that doesn’t mean I knew absolutely everything.";
			link.l1 = "When people say someone disappears without a trace, they usually mean they've been killed. But in Mr. Casper's case, you clearly aren't so sure about that...";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "I'm just saying that 'disappeared' doesn't necessarily mean 'dead'. Especially in those days, when tartanes full of smugglers and fences sailed regularly between the Island and Cuba... You know, I can't remember his face, but his eyes... That was the look of a man who'd never get lost anywhere. Or at least, he truly believed that himself.";
			link.l1 = "Tartanes, tartanes... Nothing impossible about that. If we knew his name, we could check colonial archives from those years. But it would be much easier if we had the type and name of the ship he served on.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "And why are you looking at me, young man? Do you think I’ll remember that?";
			link.l1 = "We hope so, "+npchar.name+" - considering how much you've already told us.";
			link.l1.go = "Oreli_56";
			link.l2 = "Hmm... I have serious doubts about that.";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "Maybe you want to ask how many cannons she had and what caliber they were? My dear, do you have any idea how many ships have perished here over the years? And you think I remember them all? Besides, only a handful of people survived from that ship – she barely lasted a day on the surface, you know...";
			link.l1 = "I see... Well, that makes sense, it’s been twenty years. Thank you for at least remembering what we were told.";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "Maybe you want to ask how many guns she had and what caliber they were? My dear, do you have any idea how many ships have perished here over the years? And you think I remember them all? Besides, only a handful survived from that ship – it barely lasted a day afloat, if that...";
			link.l1 = "I see... Well, it makes sense, it's been twenty years. Thank you for at least remembering what we were told.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "I hope you’re not joking and not trying to make fun of an old woman whose memory is full of holes.";
			link.l1 = "Not at all, "+npchar.name+". You really did help us a lot. Get well soon. Well, we'll be on our way.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "So, Teresa... That was her name. My poor mother, alright...";
			link.l1 = "Well, at least now we know where you get all that strength and stubbornness from. A pregnant woman on a sinking ship... Just thinking about it gives me chills.";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "But what was she doing in that state on this ship, "+pchar.name+"?! You’d have to be mad to even think of doing something like that!";
			link.l1 = "Only your father can answer that question – John, Jack, Jacob, Jasper, Jordan...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "Are you trying to remember every English name that starts with ‘J’? Orelie only mentioned Geoffrey and John, alright.";
			link.l1 = "Maybe she just didn’t remember the rest, like I did? You know, age and all that...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", you think...";
			link.l1 = "I wouldn’t trust her memory entirely right now. But even so, we’ll have to dig up not just the colonial, but the Navy archives from 1638, and that’s much harder: those records are classified, especially when it comes to officers. And I highly doubt any ordinary sailor would be allowed to sneak his wife aboard.";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "On the other hand, it’s much easier to find information about an officer than about an ordinary sailor.";
			link.l1 = "If you know the name of the ship. Or its full name. And not just 'Geoffrey or John or, at worst, Jack...'. That’s if we’re lucky and the ship was a navy vessel. Merchants keep their crew lists in far worse shape.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "But what should we do then, "+pchar.name+"? Talk to Orelie again? We’ve already gotten everything we could out of her, don’t you think?";
			link.l1 = "Not with Orelie. With Donald.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "And how is he supposed to help us? He said himself that in 1638 he was nowhere near the Justice Island, alright.";
			link.l1 = "But there were other Narwhals here, weren’t they?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "I don’t really understand what you’re getting at.";
			link.l1 = "You’ll see, darling, you’ll see. There’s still one more thread we can pull. Let’s go.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "Oh, it's you again! So, how are your searches going?";
			link.l1 = "Hello, "+npchar.name+". Things could be better. Right now we’re wandering as if in some cave of mysteries and riddles. But we feel the exit is close.";
			link.l1.go = "Grinspy_32";
			link.l2 = "And hello to you, "+npchar.name+"Better than I could have imagined at the very start. The situation... isn't quite so hopeless after all.";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "I'm glad to hear that. Honestly. But you both need something from me again, don't you? What have you managed to find out?";
			link.l1 = "Mary was born here, on the Island, in June 1638. Her mother, Teresa, died right after giving birth. Her father—a man by the name of Casper—vanished without a trace just days after Mary was born. All we know about him is that his name starts with a 'J.' Some say he didn’t end up as crab food in the local shallows, but left the Island on one of the smugglers’ tartans...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "Glad to hear it. Honestly. But you both need something from me again, alright? So, what have you found out?";
			link.l1 = "Mary was born here, on the Island, in June 1638. Her mother, Teresa, died right after giving birth. Her father—a man by the name of Casper—vanished without a trace just a few days after Mary was born. We know nothing about him, except that his name starts with a 'J.' Some say he didn’t end up crab food in the local shallows, but left the Island on one of the smugglers’ tartans...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "And left his daughter behind? That's a strange thing to do.";
			link.l1 = "It sure is. But no one except this very Mr. J. can explain it.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "And you think he's still alive? Is that why you're looking for him?";
			link.l1 = "Not just for that. We want to know who he was, how he lived. It's very important to Mary.";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "Hmm, I see. And I’m sorry I can’t really help you with anything...";
			link.l1 = "Actually, you can. Tell me, the Narwhals do keep some sort of record of the ships lost at the Island, don’t they?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "I'm not quite sure what you mean, "+pchar.name+".";
			link.l1 = "Greenspen, Greenspen... Don't forget you're still warming that chair only because of me. So do me a favor – don't test my patience.";
			link.l1.go = "Grinspy_38";
			link.l2 = "I'm sure you understand, Donald. And for the sake of our friendship, you won't try to dodge the question.";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "Hmm...";
			link.l1 = "Ships get washed up on the outer ring from time to time. Some sink right away, others stay afloat for a while—they get searched and stripped of anything valuable. I don't know about the Rivados, but I doubt the Narwhals fight over every trinket they find on board—most likely, everything goes into a common pool, then there's a tally of all the loot, and only after that do they divide the spoils.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "Hmm...";
			link.l1 = "Ships occasionally wash up on the outer ring. Some sink right away, others stay afloat for a while—they get searched, and everything valuable is stripped from them. I don’t know about the Rivados, but I doubt the Narwhals fight over every trinket they find on board—most likely, everything goes into a common pool, then they make a full inventory, and only after that do they divide the loot.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "You’re no fool, +pchar.name+. Unlike many around here. Yes, that’s more or less how it works. Personally, I find all that paperwork tiresome, but it’s been that way since the time of Alan Milroe and those who led the Narwhal clan before him. We keep such records - and more than that: we even log ships that were reached first by the Rivados or pirates. In those cases, of course, we don’t know who or what was on board...";
			link.l1 = "Judging by the fact that Mary’s parents were brought to the Ceres Smithy after the shipwreck, it was the Narwhals who found their ship. Which means there should be a record of it.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "That may be. I can’t say for sure. And I won’t be able to.";
			link.l1 = "Now I don't understand what you mean, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "The shipwreck logs. When Leighton Dexter became Admiral after Dodson left, he took those documents from us.";
			link.l1 = "Just like that - he took them? And you didn’t object?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "Well, first of all, he was polite enough. Second, he promised to return them soon. And third... why the hell would I care about those papers?";
			link.l1 = "Not exactly useless records, though.";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "Like I said, it’s just a tradition, mainly to keep our clan from tearing each other's throats out over loot from the ships. A vessel washes up, we strip it of everything we can, make a list, split some of it, stash the rest in our holds – that's all there is to it. Why clutter up the drawer? Now there's a bit more space in them – I suppose I should even thank the Admiral for that.";
			link.l1 = "Alright, understood. Then we're setting course for 'San Augustin'. But we might drop by to see you again, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "Ah, "+pchar.name+"Come in, come in. Are you here on business, my friend, or just dropping by to say hello?";
            link.l1 = "This time, it’s business. Let’s just say, it’s personal.";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "And clearly important to you, judging by how worked up you look.";
            link.l1 = "Really? More like tired, if you ask me. I’ve had to wander your domain quite a bit these past few days. My joints are starting to complain—and here I was, foolish enough to think that only old men like you had to deal with that.";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "Just a bit winded, that’s all. You see, I don’t just sit in a chair all day. Unlike you, apparently – looks like your legs have completely given up on you, ha-ha-ha!";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "And did you ever wonder why I’m glued to this chair, heh? You know, your whole outlook can change once you realize you can’t buy your health, not even with all the riches on this Island.";
            link.l1 = "Funny thing – that’s exactly what I came here to talk about.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "And did you ever wonder why I’m glued to this chair, heh? You know, your whole outlook can change when you realize you can’t buy your health, not even for all the riches on this Island.";
            link.l1 = "Funny, that’s exactly what I came here to talk about.";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "About my health?";
            link.l1 = "No, about the riches of the Island. Or to be a bit more precise, about their inventory. And to be completely precise, about the ledgers that contain those inventories.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "Uh... mind dumbing it down a little, "+pchar.name+"?";
            link.l1 = "Not so long ago you took the logs of ships stranded on the Island from the Narwhals...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "So, that fool Greenspen actually sent you after them? What a nerve.";
            link.l1 = "Not at all, "+npchar.name+", Donald has nothing to do with it. I came to him with this question, and he sent me to you. But your reaction, I must admit, amused me. Care to share why you needed the Narwhal records?";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "Why not? As you can probably guess, I couldn’t care less about the ships themselves. And the valuables stuffed in their holds? Same there. There's enough for everyone here, if people don’t get too greedy. At least, that’s how I see it. What I truly care about is weapons: muskets, sabres... cannons, even. Yes, those smartasses sometimes salvage those too. The brainless black bastards couldn’t manage it, but the Narwhals...";
            link.l1 = "And you decided to see just how ready the people of Greenspen are for a new round of conflict?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "And send a message that me and my lads are keeping our eyes wide open. It’s a pretty transparent signal, but considering the little circus Donald pulled with those drills, I wouldn’t be surprised if he thought I was after his money.";
            link.l1 = "Yeah, I can see things aren’t exactly going the way you hoped. And what about the Rivados? Is Black Eddie causing any trouble?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Rivados, Eddie... Vile blacks – no wonder Shark hated them so much.";
            link.l1 = "So he IS causing trouble.";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "That's just it, no, curse me if I lie! The black bastards have gone quiet, holed up on their ships...";
            link.l1 = "So what the hell is bothering you, then? "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "How do I even explain this to you, "+pchar.name+"... You see, it's like the wind on the open sea. Sometimes it's gentle, sometimes it's strong, and sometimes it turns into a real storm. But one way or another, the wind moves the ship forward, and a good captain knows how to harness it.";
            link.l1 = "A gentle breeze is always better than a raging storm.";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "Right. But sometimes, there’s just no wind at all. Dead calm – and there’s nothing any skipper can do about it. You just sit on the quarterdeck, stare at the water, and wonder what the hell is going to happen next. It’s the same with Eddie and his pal Chimiset – they’re up to something, I can feel it in my bones, and it’s no good, I swear by thunder!";
            link.l1 = "Maybe you should get off your arse and have a face-to-face talk with Edward. Or better yet, get the three of you together, bring Donald along too, and have an honest conversation. That’s a far better idea than drowning the Island in blood all over again. But alright... Let’s get back to why I came here.";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "So you’re interested in the narwhals’ treasures, am I right? What are you hoping to find there?";
            link.l1 = "I'm interested in the lists of ships lost here. Specifically, for the year 1638. The thing is, we're trying to find information about Mary's parents. Her mother is more or less accounted for, but the same can't be said about her father. The details about him are quite vague—we don't even know his name, and the only clue we have is the name of the ship that wrecked on the outer ring in June of 1638...";
            link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "A noble. I once tormented myself over who my own father was. But I’m afraid I can’t help you.";
            link.l1 = "And why is that, if you don't mind me asking?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "No secrets from you, "+npchar.name+". It’s not me, it’s Donald. He only handed over papers starting from the year 1651. I asked about older records, at least the previous decade, but he said that was all he’d inherited from Alan Milroe. That’s what he told me.";
            link.l1 = "I don't think he had any reason to lie.";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "I don’t either, friend. Considering he handed me the new records without a single question. In fact, it seemed to me he was even somewhat glad to get rid of that junk... Who knows, maybe Milroew just got rid of papers from decades past... Burned them, or maybe...";
            link.l1 = "No, that can't be.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "No, that can't be. Alan would never do something like that.";
            link.l1 = "Why are you so sure about that, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "I thought he was more of a knife-and-hatchet type than into all this paperwork. Surprised he could even read.";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "He treated every record about the Island with great care. He saw them as part of its story. And history— not just of this place— was Alan’s true passion, alright. He studied every historical document and book he could get his hands on... Sometimes I thought he’d have made a far better scholar than a fighter— I even told him so once.";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
            dialog.text = "He treated every record about the Island with great care. He saw them as part of its history. And history—not just of this place—was Alan’s true passion, alright. He studied every historical document and book he could get his hands on... Sometimes I thought he’d make a much better scholar than a fighter—once, I even told him so.";
            link.l1 = "Maybe he really should have chosen glasses, paper, and a quill over a sword and pistol—who knows, he might still be pacing the rotten decks of these ships. But if Milroe was such a lover of archives, then where did he put those records? Let's say he could have spilled ink on one sheet by accident—but there were dozens, if not hundreds of them, right?";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_18":
            dialog.text = "I only know that he guarded those papers more carefully than his own life. Maybe someone stole them, or perhaps he gave them to someone himself...";
            link.l1 = "Stolen? Who would need information about ships that were gutted from quarterdeck to keel ages ago? Gave it away—that’s much more likely, but to whom, and for what?";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "To some other history buff, ha-ha-ha! I agree with Charles – I have no idea who else could possibly want those ancient scribbles.";
            link.l1 = "Someone needed them, though. I’ll have to give it some thought. Alright, "+npchar.name+", we won't keep you any longer. We'll meet again.";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", glad to see you again. How are things with Mary?";
			link.l1 = "And we're glad to see you, "+npchar.name+". But how things turn out for us – that will depend on you.";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "An intriguing way to start a conversation, I must admit. And a little unsettling, judging by the looks on your faces.";
			link.l1 = "No need to be alarmed, "+npchar.name+", it’s not your fault. We’re just a bit winded from running all over these creaky shipwrecks without a break. And the air’s thick today, wouldn’t you agree?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "We’ve been running around the Island looking for you, so we could use your help. Phew, this heat is something else...";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "Ahem, yes, a light breeze would be more than welcome right now. But I take it it’s not just the weather that’s worn you down. So, what can I do for you?";
			link.l1 = "You see, Mary and I started an investigation to shed some light on what happened twenty years ago.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "Ahem, yes, a light breeze would be more than welcome right now. But I take it it’s not just the weather that’s worn you down. So, what can I do for you?";
			link.l1 = "You see, Mary and I started an investigation to shed some light on what happened twenty years ago.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "Sounds intriguing. And what is it about, exactly?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "My parents, Antonio. Charles and I are trying to find out who they were. And what happened to them. My mother died in childbirth, we've already figured that out. But things with my father aren't so simple...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "What year were you born, remind me...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "In 1638. In June.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "I was only twelve back then, Mary. I don’t really remember those days all that well. Some memories do flash through my mind now, of course, but honestly, it’s a bit hard to piece them all together. I’m sorry, but I doubt I can help you...";
			link.l1 = "We don't quite need that from you, Antonio. But if you remember anything about the day Mary was born, we'd be very grateful.";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "Then how can I help you, "+pchar.name+"?";
			link.l1 = "You told me you were interested in history. Not just world history, but the Island’s in particular.";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "It's true. I read every book I could find, studied every manuscript I could get my hands on...";
			link.l1 = "It's the manuscripts we're talking about. Besides you, there was only one other person on the Island who was just as passionate about history as you are...";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Alan Milroe. Alright, we talked about it back when he wasn’t busy drawing up plans to wipe out the Rivados, and later the pirates too. He was a clever guy, with some remarkable talents.";
			link.l1 = "No doubt about it – the lad was something else. He had something that might help us. And it’s of no practical use to anyone on Justice Island, except for the two of you. Ship logs from vessels wrecked near the Island, with descriptions of the cargo and valuables salvaged from them, and maybe even the names of the passengers...";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "That's right.";
			link.l1 = "So, you saw them?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "Not only did I see them – I copied the information they contained into my own notes. During one of our conversations, he happened to mention the existence of these journals, and I asked him for them to study – I'm trying to put together something like the Chronicles of Justice Island, and those records were a great help to me.\nAlan was thrilled with my idea – to write the history of this place. True, he didn't give me all the records, keeping the ones from the 1650s for himself, but at the time, the rest was enough for me.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = " Those records... they include the year 1638, don’t they? Please, say they do!";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "I've got a whole stack of those logs – starting all the way back in 1620. That's when, according to Alan, they first started keeping these records. And yes, 1638 is there too, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "Will you let us take a look at them?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			if (PChar.location == "PlutoStoreSmall") StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
			else StartInstantDialog("LSC_Betancur", "WildRose_Betancur_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "Doesn’t look like I have a choice, ha-ha-ha! Hold on. They’re all here, in the bottom drawer of this cabinet.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = " Please, make yourselves comfortable, research to your hearts’ content...";
			link.l1 = "That's exactly what we'll do.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "Here, "+pchar.name+", look! Joshua and Teresa Casper! I can't believe it – we did it, we really did, alright! And the ship's name is 'Wrangler'! Now we can find out everything about my father – who he was, how he ended up here...";
			link.l1 = "I'm afraid, "+npchar.name+", you’re rushing things... It might not be as simple as it seems. His Majesty’s ship... We’ll have to think about who could help us get information from the Royal Navy archives...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "Let's think! Let's think and we'll get it, "+pchar.name+"! The hardest part is already behind us, alright!";
			link.l1 = "Maybe it also makes sense to talk to Mister Young and Mister Friddick. However, I don't recall anyone by those names on the Island.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Because they're not here, "+pchar.name+". Those two died the very next night after they were rescued along with the Caspers.";
			link.l1 = "Curious. The pregnant woman lived for another week, while two sailors from the Royal Navy died suddenly...";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = " They weren’t well to begin with, as I recall. Now it comes back to me, "+pchar.name+" – I was near the Ceres Smithy when they were brought aboard... Yes, I was on the Esmeralda with Orelie Bertine, I believe. And there was also Chimiset, that shaman of the black heathens, who came to the store for some reason. At first, I thought the two sailors were already dead, but they passed only a day later...";
			link.l1 = "Well, nothing we can do about it. But we've already learned quite a lot. Thank you for your help, Antonio.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = " No thanks needed, "+pchar.name+". It was all thanks to Alan – hardly any of those cuirassiers could’ve grasped the true worth of those records. But it’s through documents like these that history is restored!";
			link.l1 = "I hope that one day Mary and I will read your Chronicles, mate. Here’s your journal—don’t lose it. Well, it’s time for us to go. Maybe we’ll meet again, my friend.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Because they're not here, "+pchar.name+". Those two died the very next night after they were rescued along with the Caspers.";
			link.l1 = "Curious. The pregnant woman survived another week, but two sailors from the Royal Navy died suddenly...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "Good to see you again, my friend. What brings you here?";
			link.l1 = " A request, +npchar.name+... Or rather, a question.";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "Ask your question. Or make your request. I'll do everything I can to help you.";
			link.l1 = "Alright. How long have you been living on the Island?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "Decades and decades, my friend. I ended up here as a child, but already sharp-witted – aboard a slave ship. My story isn’t much different from many others you’ve heard here. A squall, a shipwreck... The English galleon I was locked in didn’t even make it to the outer ring, splitting in two after crashing against one of the reefs the waves threw her onto.";
			link.l1 = "How did you survive? The reefs are quite far from the outer ring, and making it here through stormy waves is, let's be honest, no easy feat...";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "The gods were on my side that night. I managed to break free from my shackles, then grabbed hold of a piece of what used to be a boat. I had a tribesman with me, Asana – together we fought the waves until we passed out from exhaustion.";
			link.l1 = "You washed up on one of the ships?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "Yes, we crawled into a hole in the hold... That’s where I passed out again, I was so weak. I came to when Asana started screaming – he was being torn apart by a giant crab that had climbed onto the same ship we’d washed up on. And I just stood there watching, knowing I’d be next – frozen with fear and helplessness, I couldn’t move an inch.";
			link.l1 = "You could have tried to help your friend. But then we wouldn't be talking right now, would we? So how did you get away?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "You're lucky he didn't start with you, "+npchar.name+". So how did you escape – did you jump back into the water and swim away?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "Asana’s screams were heard by a few Rivados, who had come out to scavenge the holds of ships after the latest hurricane. They surrounded the beast and killed it. There was nothing anyone could do for Asana, but I was much luckier. That’s how I ended up here. But now it’s your turn, my friend – why did you want to know all this?";
			link.l1 = "Actually, "+npchar.name+", I was going to ask not how you ended up here, but when it happened.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "The screams of Asana were heard by several Rivados, who had gone out hunting for ship cargo after the latest hurricane. They surrounded the beast and killed it. There was nothing more to be done for Asana, but I was much luckier. That’s how I ended up here. But now it’s your turn to answer, my friend – why did you want to know all this?";
			link.l1 = "Actually, "+npchar.name+", I was going to ask not how you ended up here, but when it happened.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "Hmm, by your calendar it was the year 1623, late summer – I can’t be any more precise than that...";
			link.l1 = "That’s not necessary. So, in 1638, you’d already been on the Island for fifteen years.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "Looks like it, my friend.";
			link.l1 = "In June of that year, the hurricane drove the brig 'Wrangler' onto the outer ring — a ship of His Majesty King Charles I’s fleet. Only four of the crew survived — among them Mary’s parents: Joshua and Teresa Casper.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "Alright, I remember that, my friend. Vaguely, as if through a fog, but I do remember...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "You really remember? Tell me, then!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "I can’t say much. Four people: an officer, his wife, and two sailors. The woman was pregnant, and those who rescued them thought she wouldn’t live till morning – but she turned out to be strong as a lioness, while the two sailors left this world in less than a day... I saw them: they were weak, but still had enough life left in them...";
			link.l1 = "Are you suggesting they were killed?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "If that’s so, then there were no witnesses to it, nor any wounds on their bodies, my friend...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "You said 'officer', alright... Was my father really an officer?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "He was wearing an officer’s uniform – that’s probably the only thing I remember when I try to recall what he looked like.";
			link.l1 = "If he was an officer, then he couldn’t have worn anything else – I doubt his wardrobe was all that varied... Maybe you remember any other details, "+npchar.name+"? Any distinguishing features... Say, a scar on his face, or maybe some other injury...";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "I don't remember much, my friend. His face has almost faded from my memory – it's been twenty years... But his gaze – that I remember all too well. I spoke with this man only once, but the look in his grey eyes – just like Mary's – I'll never forget. There was despair in them, fear like a cornered antelope, and at the same time – a fury and resolve worthy of a lion...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "You talked to him, alright? About what?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "It happened a few hours before you were born. He came here, to the 'Protector', and demanded to see me. The leader of the Rivados, Mogedi, was stunned by his audacity – but I suddenly found myself intrigued by this man. When he stood before me, he fell to his knees and begged me to save his wife... Someone, in the short time they were here, had managed to tell him about me. I agreed, even though Mogedi objected...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = " Then that means I owe you my life?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "There’s no point in lying – we managed to reach your mother, but it was too late: the Narwhals refused to let me onto the ‘Ceres Smithy’. Your father managed to... persuade them, but I saw poor Teresa only as she was drawing her last breath. She gave birth to you, and if I’d arrived sooner, maybe I could have saved her, but...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "Mother died.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "Alas. She looked at you and drew her last breath, but before that, as if gathering her strength, she called out for someone named Rupert. She shouted his name at the top of her lungs, as if calling for help – and then she died.";
			link.l1 = "Rupert? Not Joshua?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "While I was telling you this, my friend, it felt like I was reliving that moment all over again. I will never forget it – neither her dying scream, nor her face twisted in pain. And yes, the last thing that escaped her lips was 'Rupert'.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "Was she beautiful, my mother? Can you describe what she looked like, Chimiset?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = " There’s no need to, Mary. Just look in the mirror - you are the spitting image of her. Only that piercing gaze you inherited from your father.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "And what about him, what happened to him? We managed to find out that just a few days after I was born, he vanished without a trace, alright! But he wasn’t killed, was he?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "As soon as he was told that Teresa was dying, Joshua flew into a real rage – I swear, even lions in the savannah never attacked their prey with the fury your father showed when he went after those narwhals who wouldn’t let me on the flute... It took half a dozen men to restrain him – and that was after he’d thrown two clan fighters into the water, armor and all.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "And what did they do to him - tell me, come on!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "They threw him into one of the cells on the 'Tartarus'. No one dared to judge him—they wanted the story to die down first... Almost everyone felt sorry for him, but few wished to live side by side with such a man. Joshua disappeared a few days later—around the same time, several smugglers' boats left the Island. No one saw him in the boats, and that's what started the rumors of his death.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "So you believe he’s alive, alright?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "I'll just say what others will surely tell you as well – no one ever found his body. Maybe he did hide at the bottom of one of the boats, or maybe they slit his throat in that cell and fed him to the crabs...";
			link.l1 = "The fact that he vanished at the same time those traders set sail points more to the first option – there are no such coincidences. And maybe he let something slip about his plans to someone? If he ran, then he ran, leaving his newborn daughter here, which, in its own way, makes sense – an infant might not have survived the journey to Cuba in a flimsy boat... But he surely meant to come back for her.";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "I wouldn't know, my friend. If Joshua Casper spoke to anyone in those days, it could only have been his jailers – but they've all long since left this sinful world. Oh, and yes, one day Padre Domingo came to see him – he was the priest for the whites before Brother Julian...";
			link.l1 = "Was he planning to confess or something? Guess he was afraid he’d die during the escape.";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "I can't shed light on what I don't know, my friend. And Domingo won't be telling you anything either – he's been dead for about fifteen years now, alright. Maybe someone hit him on the head, maybe he just drank himself to death – he was quite fond of that...";
			link.l1 = "But maybe Domingo kept a journal... or told his brother Julian about that conversation with Joshua?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "We need to talk to him, "+pchar.name+", alright. And the sooner, the better. I don't even want to think about going back to the ship until we've dealt with this.";
			link.l1 = "If there’s anything left to figure out. Julian might not even know about it – but we’ll get to the bottom of it. Thank you, Chimiset.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "I'm always at your service, my friend. But let me give you both a piece of advice.";
			link.l1 = " And what’s that?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "When you're out hunting, don't wander too deep into the thickets — you might never find your way out.";
			link.l1 = "We’ll remember that, shaman. And now – farewell.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "Welcome under the shelter of God's house, my children. Have you come to confess, or do you simply wish to pray?";
			link.l1 = "Greetings, Brother Julian. I’m afraid listing our sins would take too much time, which we unfortunately don't have. But rest assured, as good Catholics, we attend church at every port.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "Greetings, Brother Julian. As devout Catholics, we start our day with prayer to our Lord and end it the same way.";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = " Good Catholics living together out of wedlock under one roof... That borders on blasphemy, my son. And that, I remind you, is a mortal sin!";
			link.l1 = "And doesn’t the Scripture say that love covers all sins?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = " Good Catholics living together out of wedlock under one roof... That borders on blasphemy, my son. And that, I remind you, is a mortal sin!";
			link.l1 = "And doesn’t the Scripture say that love covers all sins?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "Love is about living by His commandments – do I need to remind you of them, my son?";
			link.l1 = "Some other time. We're here on different business.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "It’s never too late for lost souls to find their way back to the righteous path... But I am listening to you, my children.";
			link.l1 = "We really have gotten a bit lost, Brother Julian. Lost in the thickets of the past. And we hope you can help us find our way back to the light.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "Very witty, my son. You should remember that it is not man who leads to the light, but the Lord – and as you follow Him, remember that His ways are mysterious.";
			link.l1 = "I'll be brief, Brother Julian. We're trying to find out everything we can about Mary's parents. As for her mother, Teresa, things are more or less clear—she arrived on the Island with her husband and died in childbirth a week later. But her father... He disappeared a few days after Mary was born, escaping from the 'Tartarus.' Rumor has it, the last person he spoke to here was Padre Domingo—your predecessor.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "Then you’re more than fifteen years too late, my children.";
			link.l1 = "Yes, we know that the padre died quite some time ago. And back then, Brother Julian, you were still too young to have arrived on the Island in the proper rank, isn’t that right?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "I ended up here a few years after his death. It took a lot of effort to put everything in order here, on this ship, but with God's help I managed, my son.";
			link.l1 = "While you were sorting things out here, did you happen to come across any of Father Domingo’s records?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "Do you mean something specific, my son?";
			link.l1 = "We're looking for diaries or some kind of logbooks... There's little hope for a miracle, but the padre might have recorded the contents of that conversation in one of his notes. We believe Mary's father left the island on one of the smugglers' boats—maybe he hinted to the padre where he was headed and when he'd come back for his daughter?";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "I never found any diaries or anything of the sort, that's for sure, but there were all kinds of records... When it came to church matters, he was quite meticulous— not every servant of the Lord is blessed with such pedantry. But his papers contain only dry numbers and names— nothing more.";
			link.l1 = "As far as we could find out, Joshua Casper – that was his name – in a fit of rage after his wife’s death, killed two members of the Narwhal clan who refused to let the rivados sorcerer Chimiseta see Mary’s mother...";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "They acted like true children of the Church! The dungeons of the Inquisition are just waiting for this servant of the Devil!";
			link.l1 = "God, I think He’d be horrified to know how many people have been tortured in His name. Casper was luckier – they just threw him into a cell on the ‘Tartarus’, but he never made it to trial.";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "Yes, yes, no doubt about it. Casper was thrown into one of the cells in 'Tartarus', but there was no sentence passed – not everyone condemned the actions of a husband who had lost his wife.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "What happened next – did that heretic escape?";
			link.l1 = "Less than a week later, Joshua disappeared. And the night before that, Padre Domingo paid him a visit. So the question is—why? It's unlikely that a Protestant, which Casper surely was, would confess to a Catholic priest—don't you think?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "What happened next – did that heretic escape?";
			link.l1 = "Less than a week later, Joshua disappeared. And the night before, Padre Domingo came to see him. So the question is – why? It’s unlikely that a Protestant, which Casper surely was, would confess to a Catholic priest – what do you think?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "It's never too late to turn to the true faith, my son. But your reasoning is sound. If he didn't need confession, then perhaps he was discussing his wife's funeral service with the padre—if, of course, she was Catholic. Or perhaps the baptism of his daughter, or rather, the refusal of it, since Protestants don't baptize infants, believing that a person must make the decision to be baptized independently and consciously.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "But I was baptized, Brother Julian. Eric Udette told me about it.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "Those are only my assumptions, my child. The truth is unknown to me. The Lord opens our eyes only to what is truly important and necessary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "And that's exactly how it is for me, alright. Maybe there's still something left on the pages of Padre Domingo's records that you didn't notice, Brother Julian? After all, you were just flipping through them, weren't you?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "I had no business there, my child. I can see you've been working on this for a long time, and with great care – the Lord is guiding you down this thorny path. If you are meant to find what you seek, then it is His will, and it is not for me to stand in its way. I can give you Domingo's records from the year you were born; perhaps you'll find something useful in them.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "That would be very generous of you, Brother Julian. Do you still have the records from 1638?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "Well, well... (blows off the dust). Looks like this is it. The ledger for the year 1638 Anno Domini.";
			link.l1 = "Allow me, Brother Julian...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "Look, "+pchar.name+": August 3rd. That’s the day Fabian and I were baptized. I was born on June 22nd. But not a word about my father, alright.";
			link.l1 = "Just as Brother Julian said – nothing but dry numbers and names. What's interesting is that Padre Domingo was so zealous in his duties, he even performed last rites for Protestants – I doubt van Ekkus, Young, and Friddicks were Catholics.";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "They could well have turned to the true faith on the very threshold of entering the Kingdom of Heaven, my son.";
			link.l1 = "Of course, Brother Julian—what else would they do? Especially if they died like Soren and Rojas—I suppose those are the very Narwhals that blocked Chimiset’s way.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "It would be better if Padre Domingo wrote out the middle names in full, alright. What do those ‘V.’ and ‘J.’ after my mother’s name and mine even mean?";
			link.l1 = "And who is this Fabian, the one who was baptized on the same day as you?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "Cecille Halard's son. Oh, I just remembered! She raised me, though she was never particularly warm. Probably because I survived and Fabian didn’t. He died a few months after he was born, alright.";
			link.l1 = "Maybe we should talk to her, since we’ve barely learned anything useful from this little book—unless, of course, you count the dates of your birth and baptism.";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "She’s not much younger than Orelie, "+pchar.name+". All we can do is hope that at least she's got her head on straight. But what are you planning to ask her?";
			link.l1 = "Well, since she was your nursemaid, she might have known some details from Padre Domingo about his talk with Joshua. Who else would he have told, if not her? Maybe Orelie or Eric too. But I think we’ve squeezed everything we could out of the first, and the second won’t be telling anyone anything anymore.";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "This good woman is a devoted parishioner of this house of God. She never misses a single mass and goes to confession regularly. I believe she truly can help you, my children.";
			link.l1 = "Thank you, Father. Farewell.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" and Mary Casper. What a pleasant surprise!";
			link.l1 = "Likewise, "+npchar.name+". Actually, we came to see you. There’s something we’d like to discuss with you.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "Oh, really? Well, you have my full attention.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "This is about my parents, Cecille. We’ve already learned everything we could about my mother... She died right after I was born. But my father... he vanished without a trace just a few days later. We tend to think he didn’t die, alright.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = " Indeed, it would’ve taken quite an effort to send a man like him to the other world...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "Did you see him?! Did you talk to him?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "My girl, I saw him take down two Narwhals with his bare hands, almost...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "Sorreno and Rojas?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "I had my hands full back then, no time to remember the names of those scoundrels – and now I can’t recall them at all.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "Alright, it doesn't matter. Please, go on, Cecille.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "And what’s there to continue? He threw those two overboard, they sank like stones, and then they tied him up and dragged him off to the 'Tartarus'. And they did the right thing – who knows who else that cutthroat might have decided to drown...";
			link.l1 = "Cutthroat? That’s a bit harsh, don’t you think, Mrs. Halard? We’re talking about a man here, an officer who’s just lost his wife...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "I see you don't think too highly of him – not every officer gets talked about like that.";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "Officer, well, well. His uniform was quite something, I remember it clearly. Practically brand new. But I’ve seen plenty of officers in my time, young man. And every single one of them behaved far more decently than that... gentleman.";
			link.l1 = "Did he do anything else? Besides killing those two?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "Officer, well, well. His uniform was quite something, I remember it clearly. Almost brand new, straight off the tailor’s hands. But I’ve seen plenty of officers in my time, young man. And all of them behaved far more decently than this... gentleman.";
			link.l1 = "Did he do anything else? Besides killing those two?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "He demanded to see a priest in his cell – Padre De la Cruz...";
			link.l1 = "Well, would you look at that! That's exactly what we wanted to talk to you about. Do you know the details of that conversation?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "Of course, young man! That scoundrel of a Protestant demanded that the padre not baptize his daughter—even though her mother was Irish, and therefore Catholic.";
			link.l1 = "That's almost the first time I've heard an Englishwoman speak like that about a Protestant... Ahem, forgive me for interrupting, Mrs. "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "I used to be a Protestant myself, no point hiding it. But Brother Julian managed to set me on the right path.";
			link.l1 = "So that's how it is... Truly a devoted servant of the Lord. But we've strayed from the point. So, Casper wanted his daughter to be raised in the Protestant faith.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "That's exactly what he told our padre De la Cruz. And he also ordered them to name the girl Julia...";
			link.l1 = "So that's what the 'J.' stands for. Mary Julia Casper... But then why did they call her Mary?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "Because that's what her mother wanted, that's why. When the girl was taken from her womb, she whispered a name – Mary. I wasn't there to witness it, but Orelie Bertine was present at the birth. You can ask her if you want...";
			link.l1 = "So you went with your mother’s wishes, then.";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = " And how could it be otherwise, when the deadbeat father disappeared as if into thin air?";
			link.l1 = "Given... Padre De la Cruz’s talents, I doubt the father’s opinion would have mattered, even if he’d stayed put on the Tartarus. Domingo didn’t tell you—he wasn’t aware of Casper’s plans to escape and maybe come back for the girl?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "Perhaps you’re right. But going back to Father Domingo’s conversation with Mr. Casper — did the priest mention if Joshua talked to him about escaping, or when he might come back for his daughter?";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = " He didn’t mention anything like that. And think about it, "+npchar.name+", if you were planning to escape from prison, would you go telling every passerby? That guy definitely wouldn’t, that I can tell you.";
			link.l1 = "So, this thread led us nowhere as well. Well, thank you for your time, Mrs. "+npchar.lastname+". See you around.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = " He didn’t mention anything like that. And think about it, "+npchar.name+", if you were planning to escape from prison, would you go telling every passerby? That guy definitely wouldn’t, that I can tell you.";
			link.l1 = "So, this lead turned out to be a dead end. Well, thank you for your time, Mrs. "+npchar.lastname+". See you around.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "We’ve found out quite a few interesting things, "+pchar.name+". But we’ve hardly made any progress, alright.";
			link.l1 = "And we even got a bit tangled up. Who, I wonder, is this Rupert your mother was calling out to before she died?";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "Maybe a brother, or... a close friend?";
			link.l1 = "Friend, you say, huh... I wonder if Joshua knew about him...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "What are you getting at, "+pchar.name+"?";
			link.l1 = "That we need to think all this through properly. Luckily, we’ll have plenty of time for that while we look for someone who can help us with our search. We’ve done a lot already. But we’re not quite finished yet. We can’t get into the Royal Navy office ourselves, and it’s all the way across the ocean in London... Any ideas who might be able to help us with this?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "What about Serge Benoit, Charles?";
			link.l1 = "Abbot? He’s well-connected, that’s true, but I doubt he’ll be able to get into the Royal Navy archives.";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "If he can't do it himself, maybe he'll put us in touch with someone who can, alright.";
			link.l1 = "I suppose so. So, we're heading for Saint-Pierre.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "Well, now all we can do is wait, alright.";
			link.l1 = "I'm sure he'll find out everything, "+npchar.name+". Time will fly by, you won’t even notice. And for now – we’ve got things to do.";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "Are you hinting at something specific, darling?";
			link.l1 = "We've got plenty to do, but why don't we head back to the ship, lock the door, and spend some time together? What do you say?";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "And I knew you’d suggest that, alright! Here’s what I say: let’s not waste any time!";
			link.l1 = "Come on, my darling.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "Oh, "+pchar.name+", you have no idea, you just have no idea what a weight has just been lifted off my soul, alright!";
			link.l1 = "I can imagine, darling – you’re practically glowing, ha-ha! As you can see, it was all worth it.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "My father was a celebrated officer, can you imagine! But it’s such a pity we never got to meet. And we never even found out if he made it to the mainland, alright...";
			link.l1 = "If that had happened, he surely would have returned to service, and someone, somewhere, would have heard something about him, alright. A man like that could never just sit still – otherwise, where would you have gotten it from?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "Do you really think he’s dead? That he ended up in the hands of the Spanish in Cuba, or was killed on the Justice Island?";
			link.l1 = "I try to look at things realistically, "+npchar.name+". Back then, there was still some traffic with the Island. Smugglers sailed their tartanes there regularly. If he’d managed to leave, I have no doubt he would’ve returned for you in time.";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "To get me out of there. But then we wouldn’t have met, alright.";
			link.l1 = "That's life, darling. You never know where you'll find something, or where you'll lose it. I hope you don't regret being here with me, right now.";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "I've never heard anything more ridiculous in my life, alright! "+pchar.name+", you’re the best, you’re wonderful! Thank you for putting in so much effort to help me figure all this out. It means so much to me, alright! But let’s take a look at the documents—maybe we’ll find something in there our friend didn’t tell us...";
			link.l1 = "Good idea. Let's get started right now.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "Well, "+pchar.name+", did you notice anything interesting?";
			link.l1 = "Alright, "+npchar.name+". There is something...";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "You look like you've seen a ghost, alright.";
			link.l1 = "It mentions some Rupert Northwood.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "Rupert Northwood?! Is it really him?";
			link.l1 = "Quiet, "+npchar.name+" - don't shout like that. Hmm... I think so, yes – that's the person Chimiset was talking about. It can't be otherwise – there are no such coincidences.";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "And what do you think about all this, "+pchar.name+"?";
			link.l1 = "This story is getting more and more tangled. So... the 'Cornwall' set sail from Plymouth, the 'Cornwall' also arrived at Antigua, but it was the 'Wrangler' that wrecked on the reefs of Justice Island – with the same Joshua Casper at the helm, who somehow managed to secretly marry a woman behind the Admiralty's back, a woman who, in her dying agony, was calling out to someone named Rupert.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "I don’t understand any of this. I don’t even know who else could shed any light on it. The more we try to find out about my father, the deeper we sink into this swamp of secrets and mysteries, alright.";
			link.l1 = "If anyone can shed any light on this, it's either Joshua Casper or Rupert Northwood.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "Northwood? But he’s dead, alright. You don’t really think the report filed when the 'Cornwall' arrived in St. John’s was falsified?";
			link.l1 = "Oh, that naivety of yours, "+npchar.name+"... I'm starting to think this whole story is steeped in lies. Think about it: Joshua Casper was a model officer – plenty of awards and not a single reprimand. That just doesn't fit with what we learned about him on the Justice Island, where he sent two men to their graves without a second thought, don't you think?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "He fought for the life of his wife, my mother, "+pchar.name+"!";
			link.l1 = "Of course, but then where did she even come from? And more importantly, why did he hide the marriage from the Admiralty? A career man through and through, loyal to duty and regulation, otherwise his record wouldn't be so spotless, and suddenly he pulls something like this.";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "And what if there's some beautiful, romantic story behind it all? It does happen, even if rarely, alright.";
			link.l1 = "Don't get me wrong, Mary, but this doesn't sound like a love story at all. It's more like some sort of performance, and I still can't figure out what it was all for. Why rename the ship on the way to Providence? It's a warship—such antics could land you in front of a tribunal.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "Agreed – good question.";
			link.l1 = "And something's definitely fishy with this Rupert Northwood. Nearly half the crew died in that battle, yet oddly, not a single officer except for him. And why did Teresa call out to Rupert on her deathbed, and not her husband Joshua?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "So, you’re really sure the first mate didn’t die fighting the Spanish, huh? And I’m not Joshua Casper’s daughter at all, but Rupert Northwood’s – is that what you’re getting at?";
			link.l1 = "As I said before – only one person knows the truth. Either Joshua Casper, who for some reason called Teresa his wife, or Rupert Northwood, who, for reasons just as unclear, took on his captain’s name.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "What a devilish mess, alright! So what do we do now, "+pchar.name+"? Now I want to get to the truth even more, but we've already squeezed everything we could out of everyone.";
			link.l1 = "If the answers lie anywhere, it's on the Justice Island - there's no one else left, at least not on this side of the ocean, who knew your parents, even briefly. I think we should speak with Orelie Bertine one more time - she might recall something we missed.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "But what do you want to find out from her? Seems like she’s already told us everything she knew.";
			link.l1 = "She told us what we asked her, and she could easily have missed something important. Maybe your father had a scar on his face, or was missing a finger on his hand... I doubt that someone who came up with all those tricks—changing the ship’s name and maybe even his own—would just die ingloriously on some island or in a Castilian dungeon.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "Maybe you're right...";
			link.l1 = "And if we decide to keep searching – not on the dusty shelves of the Admiralty, but here, in the Archipelago – we’ll need more than just a name, and a false one at that.";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "You know, all this gives me goosebumps, alright. Maybe it’s because it’s all so... thrilling, or maybe it’s the thought that my father might not have been so different than that bastard from Bishop’s plantation.";
			link.l1 = "Either way, I promise we’ll do everything we can to get to the bottom of this. So let’s not waste any time. Let’s go!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "Let's go, "+pchar.name+", let's not waste any more time, alright.";
			link.l1 = "I hope Orelie is in her cabin, and we won't have to search the whole Island looking for her...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "Looks like we’re out of luck again, alright. Where could she have gone this time?";
			link.l1 = "I hope the sickness hasn’t taken hold of her mind again...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "Oh, you're here again. Well, hello... What is it, do you need Orelie again?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "Can’t deny you’re quick-witted, Jillian. You wouldn’t happen to know where she is, would you?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "At the church, she was about to confess. If you hurry, you'll find her there.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "Well, if she's confessing, then she's definitely of sound mind and memory, alright.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "Hard to say... For the last three days, she hasn't been herself, can't seem to settle down. You know, for some reason she got terribly agitated when she saw the masts of your ship beyond the outer ring.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "I wonder what brought that on?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "Well, I suppose the thought of being questioned by you again makes her uneasy. But since when have you ever cared about other people's troubles?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "Don't you dare speak to me like that, Jillian. I'll forgive you this time, but just try saying something like that again...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "Such a temperamental woman - always on edge if something’s not to her liking, isn’t she?";
			link.l1 = "Best not to rile her up without a reason, "+npchar.name+". You know she doesn’t wear that blade just for show.";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "And you would have let that happen, "+pchar.name+"?";
			link.l1 = "You’ve simply never seen Mary in battle, "+npchar.name+". Otherwise, you’d have no illusions - nothing and no one can stop her. Be seeing you.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "You probably want to ask me something, "+pchar.name+", alright...";
			link.l1 = "Honestly, I don’t really care what came between you two, though I have a guess that it was a specific person. Do you really want to talk about it?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "Did you and Jillian have a falling out over something? Or should I say, over someone?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "Hmm, not really, no.";
			link.l1 = "Whatever you say. Now let's go find Orelie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "That little leech will never forgive that Alan chose me over her. Though she could have, considering he’s gone now... To be honest, "+pchar.name+", I’d rather not talk about it, alright.";
			link.l1 = "As you say, darling. Then let's go look for Orelie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", Mary! You're back on the Island, what a joy!";
			link.l1 = "Glad to see you in good health, "+npchar.name+". Actually, we came to the Island just to talk to you again. But don’t worry, it won’t take long.";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "Oh-oh, young people, you really have no pity for an old lady. But I felt that you would come. This is about your parents again, isn’t it, Mary?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "Please, Orelie. I know it's hard for you to remember after all this time, but try just once more for me, alright.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "I’ve already told you everything I remember. I have no idea what else you want to squeeze out of me.";
			link.l1 = "We have a couple of questions for you, "+npchar.name+". Please, try to remember something—any details or anything at all. We won’t pressure you...";
			link.l1.go = "WildRose_Oreli_65";
		break;

		case "WildRose_Oreli_65":
			dialog.text = "And isn’t that exactly what you’re doing right now?";
			link.l1 = "You've already done so much for us, "+npchar.name+"... We only hope that somewhere in the labyrinths of your memory, there’s something else that will help us a great deal.";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "We've come a long way, "+npchar.name+". You can't even imagine how much effort and time it cost us. But we lost our way, and only you and your memory can lead us back to the path of truth.";
			link.l2.go = "WildRose_Oreli_66_2";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "Memories... What’s left of them, really. Some mornings I can’t even remember my own name, and you want details from me—about things that happened twenty years ago. But alright, go ahead and ask.";
			link.l1 = "We're interested in Mr. Casper, Mary's father. Can you recall anything distinctive about his appearance? Maybe he had a scar on his face, or walked with a heavy limp...";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "Memories... What’s left of them, really. Some mornings I can’t even remember how to find the privy, and you want details from me—about what happened on these wrecks twenty years ago. But alright, fine, go ahead and ask.";
			link.l1 = "We’re interested in Mr. Casper, Mary’s father. Can you recall anything distinctive about his appearance? Maybe he had a scar on his face, or walked with a heavy limp...";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "Oh... I think I already mentioned I only saw him in pitch darkness, in the hold of the 'Ceres Smitty', where they made a bed for poor Teresa. He definitely wasn’t limping—on the contrary, he was quite a spry man.";
			link.l1 = "And his age? Was he young or already getting on in years?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "I wouldn’t call him an old man, alright... But I didn’t really pay much attention to him – I was more worried about Teresa. He looked pretty rough, like some kind of ghost. But keep in mind, he barely slept all week while his wife was about to give birth... He was running all over the Island, never stopping.";
			link.l1 = "So, he must have loved his wife very much. And you spent a lot of time with her, right? Did she ever mention her husband?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "Teresa kept asking about him. She slept a lot, sometimes she was delirious, but whenever she came to her senses, the first thing she did was ask where he was. And the poor thing waited for him so, so much. But at the most important moment – he never came.";
			link.l1 = "I see. Clearly, their love was mutual... Well, thank you, Orelie. You’ve been a great help to us.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "And that's it? I thought our conversation would last at least an hour or two.";
			link.l1 = "We did promise not to trouble you for long. Take care of yourself, "+npchar.name+". All the best.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "Wait, young people! I have something else for you... Or rather, for you, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			NPCsLookEachOther("LSC_Oreli", "Mary");
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "Here you go, my girl, take it... As soon as I saw the sails of your ship, I took this hat with me so I wouldn't forget it. But to walk down to the pier... I just couldn't bring myself to do it.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "What is it, Orelie? A hat?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "Your mother’s hat, Teresa’s. She had it with her when the survivors of the shipwreck were brought to the ‘Ceres Smithy’. When Teresa passed away, I picked up that hat from the floor by her bed—alright, and then I just forgot about it... Only remembered it today, during our conversation.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "Orelie... You kept it all these years! And... and you didn’t throw it away, didn’t sell it... Thank you, thank you! You have no idea how much this means to me, alright!";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "Sorry, Mary — I should have given it to you ages ago... But my memory’s like an old sieve these days — that’s why...";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "There's no better moment, Orelie! I'll try it on right now, alright!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "Well, darling, how do you like me?..";
			link.l1 = "You're beautiful. And the hat... it hasn't gone out of style yet, so it looks wonderful too.";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "Really? I’m so glad you like it!";
			link.l1 = "Could it be any other way?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "Thank you once again, Orelie – you made this day a little brighter! All the best, have a good rest.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "So it really was Rupert. Rupert Northwood, alright.";
			link.l1 = "Obviously, yes, darling. He did everything he could to save his wife... or his beloved, I don't know. It doesn't really matter, honestly. The important thing is, now we know who we're looking for.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "But what happened to the real Joshua Casper, captain of the 'Cornwall'?";
			link.l1 = "Good question, but not the main one right now. Why didn’t Rupert come back for you if he loved Teresa so much – now that’s far more interesting. And that’s the first thing we’ll ask him. If he’s still alive, and if we find him. One thing’s for sure – he never returned to the fleet. He had no reason to take such a risk.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "What could have made him take the name Joshua Casper? What happened aboard the 'Cornwall', which became the 'Wrangler'? Could my father really be a criminal, "+pchar.name+"?";
			link.l1 = "I'm afraid we can't rule out that possibility either, "+npchar.name+". We should be ready for absolutely anything.";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "I don't even want to think about that...";
			link.l1 = "For now, we need to think about something else – where to look for him. He could have joined the pirates or smugglers. Or maybe he settled down in some town and is keeping his head down. Anything’s possible.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "And what do you suggest we do? How are we supposed to find him? Go into every colony, say his name, and hope someone’s heard of Rupert Northwood?";
			link.l1 = "Or Joshua Casper. He could very well have gone on living under the identity of his former captain—most likely dead. But that carried certain risks, since someone might start looking for the missing brig. Especially since there was a chest of silver on board, meant for the Providence garrison.";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "You're right, alright.";
			link.l1 = "And yet, Rupert Northwood, supposedly lost near the Azores, would hardly be of any interest to anyone. Still, there’s definitely something here worth thinking about.";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "How much more time are we going to have to spend on this, "+pchar.name+"?! He could be anywhere, in any colony, alright!";
			link.l1 = "If he survived, of course. But I disagree. It’s unlikely he spoke fluent Spanish, so that rules out Cuba and Hispaniola. If he knew some French, he might’ve gone to Tortuga or one of the Lesser Antilles. Or he could’ve ended up on the Western Main, under the wing of fellow Englishmen. We might spend months tracking him down, and still come up empty.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "But I don't want to give up, "+pchar.name+". Just not now, when we've already learned so much, alright!";
			link.l1 = "I’m not suggesting we give up, "+npchar.name+". But we don’t have to search for him ourselves - we can turn to someone with the right connections. It worked once before. Why not try again?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "Are you suggesting we ask the abbot for help again? I thought he made it clear we shouldn’t count on any more support from him in this matter, alright.";
			link.l1 = "That would be a bit too brazen towards the old man, you’re right.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "But then who should we turn to? Who has the money and connections for something like this?";
			link.l1 = "Well, we’ll definitely have to fund the search ourselves. As for connections... I suppose Fadey Moskovit could help us out. He must know some capable folks we could send around the colonies. Or maybe he’ll point us to someone who can.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "So, we're heading to Basse-Terre?";
			link.l1 = "Yes, let’s pay our friend a visit. This doesn’t seem like too difficult a task for him, if you ask me.";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "Let's weigh anchor tomorrow, what do you say? I'd like to spend the rest of today and the night with you, just the two of us, on the 'Ceres Smitty'.";
			link.l1 = "No one turns down an offer like that, darling. We’ve definitely earned ourselves a little rest.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "What, leaving the Island already? Not even staying for the funeral?";
			link.l1 = "Funeral?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "Oh, so you haven't heard. I see... Orelie Bertine passed away last night.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "What?! That can't be – we just spoke with her yesterday, and she was perfectly fine. Or did someone...";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "No, Mary. Orelie died in her sleep. I went to see her today, to bring her some ointments for her joints, made by Brother Julian – and that's when I found her. She was lying on her bed, with a strange smile on her face. But she was already pale and cold.\nThis past week, the old woman wasn't herself, I even thought that the illness the black sorcerer had driven out had returned. But her mind was clear enough, and it seemed she wasn't delirious.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "At least she didn’t suffer, alright.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "So, will you stay for the funeral? It will be held tomorrow, on the farthest reef – it's deep enough there, and the crabs don't wander that far.";
			link.l1 = "We'll stay, Jillian. Orelie has done so much for Mary, we simply can't do otherwise. If no one objects, we'll hold the procession on our ship. We'll bury her at sea, with all due honors.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "No one’s going to argue. It’s more convenient, and in the end, safer than climbing over the wreckage.";
			link.l1 = "Then take care of the funeral arrangements – Mary will help you. As for me, I need to have a word with someone...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "And here you are again, my dear friend! What can I do for you this time?";
			link.l1 = "Hello, "+npchar.name+". Have you heard what happened last night?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "Are you talking about Orelie’s death? I can see that you are. Of course I’ve heard. She lived on the ‘Pluto’, and that’s practically Rivados turf. And people on all the other ships can’t talk about anything else.";
			link.l1 = "We saw her as recently as yesterday, and she was in good health—except, of course, she'd been anxious about something all week. And when she spotted our ship, she got even more agitated.";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "A person can feel when the river of their life is running dry. Some show it to everyone around them, some keep it hidden inside, but everyone senses it, one way or another—especially those who know how to listen to their heart.";
			link.l1 = "It seemed to me she was healthy, almost like a young doe, "+npchar.name+". And something here just doesn’t add up...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "And yet, she was clearly not on her last legs, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "My friend, the mind and the body are things of entirely different orders. The mind governs the body, and sometimes the body tries to take control of the mind. They are closely connected, but they are not truly one and the same. A person may look perfectly healthy on the outside, yet their soul may already be walking the path of death.";
			link.l1 = "You're clever, my friend, very clever. If you sense the truth is close, you'll chase after it like a lion after a zebra – and you won't stop until you've caught it. I saw that right away, the very moment I met you.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "My friend, mind and body are things of completely different orders. The mind rules the body, and sometimes the body tries to take control of the mind. They're closely connected, but they're not truly one and the same. A person may look perfectly healthy on the outside, but their soul may already be walking the path of death.";
			link.l1 = "You know, it occurred to me that Orelie seemed to be waiting for us, like she knew we’d come to her. The old woman could have died a day earlier or later, but it happened almost right after she told us something important about Mary’s father."link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "You're clever, my friend, very clever. If you sense the truth is close, you'll chase after it like a lion after a zebra – and you won't stop until you've caught it. I realized that the very moment I first saw you.";
			link.l1 = "I didn't... Wait a second. That ritual you performed in the hold of the 'Protector'... it didn't slow down Orelie's illness, did it? So what did you actually do?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "You can fill a river with stones, but that won't stop its flow. I knew you needed something important from Orelie – and that you wouldn't reach it right away. But how long your journey would take, I couldn't tell. So I built a dam, calling on all her life force to hold back the sickness until she fulfilled her purpose. And the moment that happened, the barrier collapsed...";
			link.l1 = " So then, Orelie... at the moment of her death, she wasn't herself at all, not unaware, like we thought? ";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "She spent all her strength just to keep her mind clear and her memory sharp, and when she no longer needed to, the illness crashed over her like a great wave, carrying her into the valley of death. Whether her passing was gentle, or whether she went to your God tormented by ghosts of the past and terrible nightmares—I cannot say, for I do not know.";
			link.l1 = "You knew exactly where this would lead, alright? Why the hell didn’t you warn me about the consequences?! Well, speak!";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "You knew exactly what you were doing, "+npchar.name+". Why didn't you warn me what this could lead to?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "Because I decided to help you, my friend, to learn what you needed, and to let her fulfill her destiny. If I had told you what awaited her, you might not have gone through with it—and Orelie would have taken her secrets with her to the grave. What good would that have done? She would have died for nothing. Like an antelope brought down by a lion, but left uneaten and abandoned to the vultures instead.";
			link.l1 = "Purpose, usefulness... You're quite the master of destinies, "+npchar.name+". God in human form.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "Because I decided to help you, my friend, to learn what you needed, and to let her fulfill her destiny. If I had told you what awaited her, you might not have gone through with it—and Orelie would have taken her secrets with her to the grave. What good would that have done? She would have died for nothing. Like an antelope brought down by a lion, but left uneaten and abandoned to the vultures instead.";
			link.l1 = "Purpose, usefulness... You're quite the master of destinies, "+npchar.name+". God in human form.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "I hear a note of discontent in your voice, my friend. But no, I don't consider myself a god at all—and believe me, even he is not all-powerful. Neither the one you believe in, nor those we worship. Gods cannot grant a person greater strength than what they were given at birth. We shamans can only guide that strength in one direction or another—nothing more.";
			link.l1 = "And you set them on a course that doomed her to death...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "I only set Orelie on a path, and by following it, she helped Mary — someone she’d been closely connected to since the day Mary was born. After all, your companion came into this world right before her eyes. Please, don’t look at me as if I’ve lost my mind. Surely you wouldn’t say you saw in me a kindly sorcerer, able to turn back the river of time with a wave of his hand?";
			link.l1 = "I don't know what to say to you, "+npchar.name+". Maybe it really wasn’t all for nothing. But it shouldn’t have happened this way. You should have told me, and I should have made the choice. Still, what’s done is done. Well then, farewell, my friend.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "Ah, this isn’t how I imagined our last meeting, my friend...";
			link.l1 = "What makes you think she's the last one?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "Some rivers flow into others, becoming part of them, others dry up, and some—like ours—meet their end in a great waterfall...";
			link.l1 = "More riddles, Chimiset? I think I’ve had enough for today. I’m sure we’ll meet again.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "I figured I'd find you here, alright. What did you want from Chimiset, "+pchar.name+"? What did he tell you?";
			link.l1 = "Not exactly what I expected—or wanted—to hear. But something I had a vague suspicion about.";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "You’ll tell me, won’t you?";
			link.l1 = "No, "+npchar.name+". Not this time. Everything said in the Protector’s cabin stays there, between me and Chimiset.";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "I haven't heard such determination in your voice for a long time, "+pchar.name+". But alright, we've got other things to worry about. The funeral will be held tomorrow, at sunset, at seven o'clock.";
			link.l1 = "Come on, let me help you get everything ready.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "Looks like everyone who wanted to come is here, alright.";
			link.l1 = "I thought there’d be more people. At least some peaceful ones.";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "Well, nobody invited Kurana or Rivados. Abbott, that pompous, disgusting turkey, said he had more important things to do than bury a Catholic woman, and Lauderdale and Musket mumbled something similar. Cassel, that brute, just said he wouldn’t come. But everyone else is here.";
			link.l1 = "Some things will always be beyond my understanding. Well, let God be their judge. And here comes Brother Julian... Now it all begins.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "Though our hearts are heavy with sorrow, let us thank God for all the blessings He bestowed upon the departed Orelie, and proclaim: We thank You, God, our Father\n"+"For all the years and days Orelie spent  with us\n"+"For the great gift of holy baptism, by which Orelie became Your daughter\n"+"For the gifts and knowledge You have bestowed upon her\n"+"For her service to the good of her family and others\n"+"For her patience with our mistakes\n"+"Let us pray to God, that He may welcome our departed sister Orelie into His glory, and let us call out: We ask You, Lord\n"+"May Orelie’s good deeds bear abundant fruit\n"+"Let what she started be carried on\n"+"Forgive her the sins she has committed\n"+"Let her memory live on in our hearts\n"+"Let us pray to God to strengthen the faith and hope of those who suffer, and let us call upon Him: Lord, increase our faith\n"+"Through Your Son, who became man\n"+"Through Your Son, Jesus Christ, who has loved us beyond all measure\n"+"Through Your Son, who accepted death for our sins and rose again for our salvation\n"+"Through Your Son, who opened the way to heaven for us\n"+"Together with all the faithful who have gone before us to the heavenly abode, let us pray as the Savior taught us.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "Almighty God, hear our prayers, offered in faith in Your Risen Son, and strengthen our hope that, together with Your departed servant, we too may be granted resurrection. Through our Lord Jesus Christ, Your Son, who lives and reigns with You in the unity of the Holy Spirit, God forever and ever. Amen.";
			link.l1 = "God, Almighty Father, the mystery of the cross is our strength, and the Resurrection of Your Son is the foundation of our hope; free Your departed handmaid from the bonds of death and join her to the company of the saved. Through Christ our Lord. Amen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", let's go to the cabin quickly, alright. I'm about to burst into tears... I don't want anyone to see me like this.";
			link.l1 = "Of course, "+npchar.name+". Let's go.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "You only truly start to appreciate someone after they're gone – have you ever heard that, "+pchar.name+"?";
			link.l1 = "Yes, more than once. .";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "Eric used to say that a lot. I think he meant his family. I never asked him about them—I always thought there’d be time for that. And then he died, alright. Now Orelie is gone too—and only now do I realize how little time and attention I gave her. Far less than she deserved.";
			link.l1 = "You're not to blame for anything. We can never know when the Lord will call our loved ones to Him. And no time with them is ever enough. Never.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "Maybe so, alright. And Eric often said – and Orelie agreed with him – that any place is, first and foremost, its people. Not the houses, the trees, the roads – but the people. When you think of some spot on the map, the first thing you remember is the people who live there. Or who once did.";
			link.l1 = "I never really thought about it. But maybe Eric was right—after all, what’s a home worth if, once you step inside, you’ll never see your father or brother again?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = " I’d argue otherwise. When I think of, say, Paris, what comes to mind are the sights of the streets, the smells... Only a handful of people stick in my memory - the rest have almost faded away, even though it’s been just a few years. ";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "I think Eric and Orelie talked about the Island, alright. And about the people who used to live here—a long, long time ago. I was just a child and didn’t understand any of it, but now—I see it all clearly. After all, Antonio, Cecille... and a few Rivados like Chimiset have been here longer than I have—but I was never close to any of them. As for the rest: Eric, Orelie, Alan, and so many others—they’re all dead.";
			link.l1 = "I see. The world’s become... just a bit smaller, hasn’t it?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "I think Eric and Orelie talked about the Island, alright. And about the people who used to live here—long, long ago. I was just a child and didn’t understand any of it, but now I see it all so clearly. After all, Antonio, Cecille... and some of the Rivados, like Chimiset, have been here longer than I have—but I was never close to any of them. As for the rest: Eric, Orelie, Alan, and so many others—they’re all gone.";
			link.l1 = "I see. The world’s grown... just a little smaller, alright?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "More like it’s emptied out. This world—inside the outer ring. It’s empty now, alright. And soon—it might just vanish altogether.";
			link.l1 = "What are you talking about, Mary?.";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "Didn’t you feel it, "+pchar.name+"? Just now, when we were standing by Orelie's grave.";
			link.l1 = "What exactly?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "I don’t know how to explain it. You know how the air smells before a storm? Remember—when you first arrived here, there was this tension everywhere... Everyone was ready to tear each other’s throats out, many thought they could smell gunpowder and blood. After you killed Chad, everything changed—it felt like it was easier to breathe... But now—that feeling is back again.";
			link.l1 = "I suppose, I felt something like that too. But maybe it’s just the mood? I mean, it is a funeral after all...";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "You're exhausted, "+npchar.name+". Get some rest – it’ll feel easier. And really, can anyone feel any different at a funeral?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "When we gave Eric and so many others from the Island to the sea, it wasn’t like this, I’m telling you. There was a kind of... unity. But today—some were eyeing each other like wolves, even though we were all saying the same prayer.";
			link.l1 = "You mean Leighton and Donald?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "When we gave Eric and so many others from the Island to the sea, it wasn’t like this, I’m telling you. There was a kind of... unity. But today—some of them were eyeing each other like wolves, even though they were all reciting the same prayer.";
			link.l1 = "You mean Leighton and Donald?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "So, you noticed it too, alright.";
			link.l1 = "Dexter gets nervous whenever Greenspen tries to meddle with the drills – and who can blame him?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "This won't end well, alright.";
			link.l1 = "If that's the case, then today wasn't just the funeral of Orelie Bertine, but of this... City of Abandoned Ships as well.";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "Cities of Abandoned Ships?";
			link.l1 = "Forgive me, Mary, but I just can’t bring myself to call this place the Justice Island.";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "Now that I've seen the world and realized just how vast it is, this place feels like... a prison, alright. Hard to believe I grew up here.";
			link.l1 = "And I can hardly believe that among all these broken ships, such a wild and beautiful rose could bloom as you did.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "I want to say goodbye to this place, "+pchar.name+"... I guess we’ll never come back here again, alright. I don’t want to. I don’t want to see with my own eyes what might happen here.";
			link.l1 = "I'll talk to Eddie and Donald. Maybe I can cool them down a bit.";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "You don't understand... This will only delay the inevitable, so it's not worth your effort. The day will come when we return – and here\nIt's for the best, "+pchar.name+", alright... There's nothing keeping me here anymore.";
			link.l1 = "As you say, darling. We'll finish what we have to do – and then we'll leave this place for good.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "Rupert Casper? Joshua Northwood?";
			link.l1 = "I've been thinking about it the whole way, "+npchar.name+". And I came to the conclusion that your father wouldn’t have hidden under a name and surname he’d already used. At the same time, he might not have dared to give up his real name or surname: what if, at the wrong moment, he failed to respond to a false one?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "He could have called himself anything, alright.";
			link.l1 = "He could have, of course. And maybe he did just that. If he survived on Cuba, where he arrived on a smuggler tartane. If he made it there, and didn’t end up as food for the crabs of Justice Island. Now all we can do is wait – at least not as long as last time. I think we can manage a month easily enough.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "My father is alive, "+pchar.name+". I always knew it, alright!";
			link.l1 = "Just like me, darling. Well, it's time to go see this Jerome – and the sooner, the better.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "Finally made it, alright. So, what now, "+pchar.name+"?";
			link.l1 = "We need to find Jerome. He’s either lounging around in a room at the tavern or renting a house – I’m sure he’s got enough money for that.";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "Considering how much Fadey paid him... I think he definitely went with the second option.";
			link.l1 = "Agreed. We can ask the owner of the 'Glass Eye' about him, or just ask around among the townsfolk. Let's go, time is precious.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "Well, well, well... Here are our lovebirds. Alright, boys, let's get this done and report back to him.";
			link.l1 = "Jerome Souvernier? What the hell is going on here?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "Ah, you bastards, kh-kh. Well, that's alright...";
				link.l1 = "I'd watch your tongue if you value your own skin... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "That too. Now spill it: what the devil made you attack us – and together with Souvernier, no less...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "Your Souvernier is a greedy, cowardly bastard. All it took was for Casper to give him a good thrashing, then promise him some coin – and right away, he scribbled that letter like a good little boy, ahem...";
			link.l1 = "So he really did find it.";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "Found you, found you. So you’ll be dead soon. Same goes for your little girlfriend. Casper will cut you both to ribbons, heh-heh. I’m as good as dead already, but I’ll help you meet your end. Pity I won’t get to hear you beg for mercy when he gets his hands on you...";
			link.l1 = "Alright, I’m not long for this world, that’s true. So speak quickly, before I breathe my last.";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "If you want to meet him, head to Chetumal Bay, that's where he lives. You won't have to look for him, he'll find you himself.";
			link.l1 = " Wonderful. Feel free to take your time dying. We are done here.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "I hope so. Now go to hell.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "Oh God, "+pchar.name+"... I can't believe it, I just can't, alright! My father did this?!";
			link.l1 = "Looks like it, alright. "+npchar.name+". I have no idea what drove him or who the hell he is, alright... But I doubt it's some other Rupert Casper. Coincidences like that just don't happen.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "And what are we supposed to do now? What am I supposed to say when I look him in the eye?";
			link.l1 = "First, we need to reach him. Most likely, he’s made himself an outlaw, since searching for him caused... such a nervous reaction. But, whatever the case, he’s still your father. And we’ve spent a fortune of effort, time, and money trying to find him.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "But what if he won't even talk to us? Why did he order us killed?";
			link.l1 = "At the very least, he might not have known exactly who was after him. Fadey could have just given your name and left out the details about you. Otherwise, I doubt we'd have to stain our blades with blood right now.";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "And what now? Are we heading to Chetumal Bay? But if he set a trap for us here... who knows what’s waiting for us there?";
			link.l1 = "We have the advantage of time before he finds out what happened here. Let's use it. We'll sail to the bay, and send a squad overland led by one of the officers to support us.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "Sounds reasonable, alright. But who will lead it?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Tichingitu. He’s a veteran of land battles. No one could handle it better than him.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Claude. He won't be thrilled, of course, but he'll get over it.";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Hercule. He knows exactly how these things are done.";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Tommy. Even if something goes wrong, that guy will find a way out, trust me.";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Longway. It's not his first time tracking an enemy through the jungle.";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Alonso. He’s quick with a blade, and he’s no fool.";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Tichingitu listens carefully, captain "+pchar.name+".";
			link.l1 = "My friend, you have an important task ahead of you. A gang of cutthroats is hiding out in Chetumal Bay. You need to track them down and wipe them out. We’ll approach by sea on our ship.";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "You’ll be leading a squad of our men through the jungle to get behind those bastards. Do you have any questions for me?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "The Indian has no questions. Tomorrow at noon the group will be in place and wait there in ambush.";
			link.l1 = "Very well, Tichingitu. Good luck to you.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = " Called, Cap’n? ";
			link.l1 = "I've got a job for you, Claude.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "We need to gather a squad of fighters and lead them through the jungle to Chetumal Bay. There, a gang led by some Rupert Casper is lying in wait for us. They’ve prepared a nasty surprise for us. But we will be the ones surprising them - or rather, you will. Attack them on my signal. Any questions? ";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "Hate trudging through the jungle. But, as they say, orders are orders. See you there - I think around noon tomorrow. ";
			link.l1 = "Good luck, Claude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = " Listening, Cap. ";
			link.l1 = "Hercule, there's a job for you.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "Need someone to put a couple of bullets in some thick-headed fool? That’s me, always ready, you know that.";
			link.l1 = "You guessed it. You need to lead a squad of fighters from our ship through the jungle to Chetumal Bay. There, you’ll set an ambush for the gang that, I believe, will be waiting for us.";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "I thought you had something challenging in mind, Cap. But this is a tavern trip for me. Count on us being there by noon tomorrow.";
			link.l1 = "I'll see you there. Good luck, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = " Ha, Captain, why so serious? Heading to a funeral or something? ";
			link.l1 = "Always the funny guy, eh Tommy? I got one for you too – you won’t get paid this month. Or the next one either. Why so tense?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "Can’t even joke...";
			link.l1 = "There’s a time for everything, Tommy. You’ve still got a lot to learn. Now listen carefully: gather your squad and move through the jungle to Chetumal Bay. Once you arrive, wait for my signal.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "Trekking through the jungle? We won’t get there before noon tomorrow at the earliest.";
			link.l1 = "So, we’ll meet there tomorrow at noon. Don’t engage without orders and don’t leave your positions. Got it? I see you do. Now, get to it.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Longway listening, Captain.";
			link.l1 = "Hey there, I've got a job for you.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "You’ll lead a squad of our men through the jungle to Chetumal Bay. There might be an encounter with the enemy there, so make sure your people are ready.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Longway understand everything, no need to worry, Captain. We’ll arrive at our destination around noon tomorrow.";
			link.l1 = "Go on, and be careful.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "Did you call for me, Captain?";
			link.l1 = "Alright. Listen closely, Alonso.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "You’ll lead a squad of fighters through the jungle and make your way to Chetumal Bay. There’s a good chance a gang of scoundrels will be waiting there. You’ll need to take up positions and attack them from behind when I give the signal.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "Piece of cake, Captain. But don’t land in the bay before noon tomorrow – my crew and I won’t get there any sooner.";
			link.l1 = "Get ready, Alonso. And may God help us.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Charles, did you see that?";
			link.l1 = "Looks like they're already waiting for us. I'm sure they're lying in wait just around that bend.";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "Yet we are still on our feet. They are not even trying to shoot us, alright. ";
			link.l1 = "Maybe he’s still willing to talk to us first. Let’s not provoke him – we’ll go there ourselves, our crew will have our backs. Come on, let’s put an end to all this.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "Stop right there! Not another step! Boys, if that dandy so much as twitches – fill him with holes. Don’t touch the girl.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "Dad?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			sld = CharacterFromID("Mary");
			if (CheckCharacterItem(sld, "hat11")) // У Мэри есть своя шляпа
			{
				dialog.text = " Weeell... I’ve seen much in my long and hard life. Just when I think nothing can surprise me anymore, life proves me wrong. So, you actually survived... And even kept Theresa’s hat. I never thought I’d see it again. ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = " Weeell... I’ve seen much in my long and hard life. Just when I think nothing can surprise me anymore, life proves me wrong. So, you actually survived, Julia... ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "Orelie gave it to me before her... passing.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "How touching... I'm about to cry. And here I thought they'd buried Teresa along with it. She never parted with it for a second since I gave it to her. Your mother, even though she was just a serving girl, had so much adventure in her that it was practically pouring out of her ears. When I found it during the capture of the Fleur-de-Lys, I knew at once Teresa would be crazy about it. She looked funny in that hat, but she didn't care: she only took it off to sleep. But you, Julia, it really suits you.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "Julia? No, you’re mistaken, my name is Mary...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "Hmm, is that so. So those bastards ignored my words and took matters into their own hands. Well, you couldn't expect anything else from those Catholic dogs.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "You... You... Are you really my father?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "Well, if that weren’t the case, you and your pal would already be lying on the ground, full of lead. I haven’t believed in God or the Devil for a long time, but maybe they do exist after all. The first one for sure—since He gave you Teresa’s looks. And that just saved your life right now. How does that saying go... The Lord works in mysterious ways, alright? Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "Dad... I... I don't understand, alright...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = " Of course you don’t. How could you...";
			link.l1 = "You don’t exactly look thrilled to see your daughter, Mister Casper. Especially after you just admitted she’s yours.";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "You're not lacking in wit, dandy... What's your name again?";
			link.l1 = ""+GetFullName(pchar)+". While we were searching for you, we kept wondering how you’d been living all this time. If you’d survived at all. But I see you’ve settled in quite well here, Mister... Northwood.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "Ah, so you even dug that up. Well, my respects, monsieur Frog-eater, what else can I say – considering I made sure to tie up every loose end.";
			link.l1 = "There is more. We know about the 'Cornwall', and its cargo, and about Joshua Casper, whose name you borrowed for a while, and his surname—seems you’ve kept that one for good.";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "Bravo (applauds). I'm impressed. Did you figure it all out by yourself, or did my precious child help you too?";
			link.l1 = "I couldn't have done it without Mary. She was determined to learn everything about her parents. It wasn't hard to figure out what happened to Theresa, but tracking you down took us quite a while...";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "This is all so touching, it almost brings tears to my eyes. Well, daughter, are you satisfied? Happy now? Want to give daddy a hug?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "I don't understand, Father... Why are you tormenting me? What for?! (shouts) You were the one who left me there—on those shipwrecks! And then you never even thought to come back, alright! Why? Who are you, anyway, and who are those people standing behind you?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "Tell me, "+pchar.lastname+", does she always throw such tantrums? She gets it from her mother. Teresa was a wonderful girl, the best I’ve ever met But boy could she scream up a storm when she got angry... What can I say... Irish.";
			link.l1 = "Don't you dare insult her! Mary isn't to blame for your misfortunes, and she certainly doesn't deserve to be treated like this.";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "Trying to shut me up, pup?!";
			link.l1 = "On the contrary. I want you to tell us your story. It's very important for Mary to know it. But I won't let you insult her. So keep yourself in check.";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "You think I’m dying to pour my heart out to you? My life turned out the way it did, and, as you papists like to say—God is my witness—I regret nothing. Except losing Teresa back then—because of her. Do I hate you, my girl? Maybe once I did, but now I couldn’t care less about you.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "You’re blaming me for Mama’s death?! How does that make any sense? What did I do - get born? Is that my crime? Fine, Father. +pchar.name+ is right - just tell us everything. After that, we’ll leave. You’ll never see my face again... if that’s what you want... (begins sobbing)";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "Ahhh, just like Theresa. It’s like I’m back twenty years ago, ha! Oh what the hell, have it your way. I’m not going to enjoy relieving all those memories... So if, by the end of this little story, I feel like putting a bullet in your skull, darling - well, blame yourself.";
			link.l1 = "Then you'll catch a bullet too, Rupert. And I don't think that's part of your plan – you look like someone who values his own life.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_20": //
			dialog.text = "I know what my life is worth, boy. That’s not the same as valuing it. But what would you know about that? Fine, let’s get to it. You want the full story? Here it is. I was born on a farm near Eastbourne - little town on the Channel coast - back in 1611. Give or take a year, who knows - my mother never could keep dates straight, not surprising given how much booze she gobbled.";
			link.l1 = "Tough childhood? I see.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "If you asked for it, then listen and keep your mouth shut, don’t get smart. I never had a father, and I didn’t even know why—but unlike you, little girl, I didn’t care about that. The surname I got from him suited me just fine. When I was thirteen, one night Dunkirk privateers landed on the coast. Alright, people don’t like to remember that now, but it wasn’t just the Dutch who suffered from them, but us too—those of us living on the old lady England’s eastern shore.";
			link.l1 = "I’ve heard about that. Those guys didn’t spare a soul. How did you make it out alive?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "I know the kind of horrors they left behind. They didn’t spare anyone - not the old, not the young. Makes it all the more remarkable that you survived.";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "That night, those papist swine burned down several farms, including ours. I managed to get out, but my mum, who’d stuffed herself with cider so much she couldn’t haul her fat arse off the bed, burned right there in it. It was her own fault, of course – but still, she was my mother.";
			link.l1 = "And that’s when you started hating all the papists?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "That night, those papist swine burned down several farms, ours included. I managed to get out, but my mum, who’d stuffed herself with cider so much she couldn’t drag her fat arse out of bed, burned right there in it. Her own fault, of course – but she was still my mother.";
			link.l1 = "And that’s when you started hating all papists?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "That's when I learned to hate hunger, smartass. I bet you’ve never really known what that’s like, but I sure did—felt it in my own skin. I went north, to the capital, and signed up for the navy—there, they served out lashes more often than food, but a couple dozen was enough to set me straight. After that, I got used to it—and I came to love life at sea. Especially since there was never a dull moment...";
			link.l1 = "I can believe that. The reputation of the Royal Navy speaks for itself.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "In 1633, I passed the lieutenant’s exam and was assigned to the brig Cornwall.";
			link.l1 = "Under the command of Joshua Casper.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "Oh, yes... Joshua Casper... You couldn't find a bigger bastard on the whole damn fleet. It's been so many years, and that pig still haunts my dreams.";
			link.l1 = "What did he do, then? Did he put you on extra watch for being too eager? Or was he secretly a papist?";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "That cruel bastard drilled the crew so hard, people would drop overboard from sheer exhaustion. Since you know his name and that he was the commander of the 'Cornwall', you must have seen his papers—shining like a cat’s licked rear.   Our heroic Joshua had a whole box full of medals. Plenty of naive lads like yourself wanted to serve under him—say what you will, but he cut down you frog-eaters like a sharp sickle through wet grass after rain, alright—but once they found themselves on the 'Cornwall', they realized their mistake real quick.   We were dead tired of putting up with it, "+pchar.lastname+". Some even wrote petitions for transfers – but they vanished on the shelves of the Admiralty, or in its furnaces. Still, life gave us a chance – they didn’t transfer us off the 'Cornwall', but someone else onto it. John Lawson – Cromwell’s favorite, you must have heard of him.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "He already knew how to kiss ass back then — and maybe he and Casper would’ve hit it off, but I didn’t let that happen. I set little Johnny up, and Joshua, not knowing the whole story, beat him with his cane in a fit of rage.";
			link.l1 = "A real humiliation for an officer. And Lawson told his father everything?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "Of course he did – that was my plan. But, you see, the system can't devour itself. The whole thing was hushed up – Lawson was offered an early promotion, and Joshua and the 'Cornwall' were pushed into the shadows – we were transferred from London to Plymouth, down south in England. We could have kept terrorizing you, frog-eaters, but the 'Cornwall' was turned into a supply ship, hauling military cargo to Dundalk, a small Irish town.";
			link.l1 = "And that's where you met Teresa?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "First time we docked there. Theresa O’Fatt - she was a barmaid at a local tavern. Took us three days to realize we were made for each other. I think you understand what I mean, too, "+pchar.lastname+", don’t you?";
			link.l1 = "I suppose so.";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "Looking at you now, one wouldn't think you know the meaning of the word 'love'.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "I've never met anyone more wonderful – not before, nor in all the twenty years since. For the first time in my life, I felt truly happy, and so did she – or so she claimed.";
			link.l1 = "And you asked her to leave with you?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "I've never met anyone more wonderful – not before, nor in all the twenty years since. For the first time in my life, I truly felt happy, and so did she – or so she claimed.";
			link.l1 = "And you asked her to leave with you?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "Of course not – that was impossible, since the 'Cornwall' was still a warship with a bastard for a captain. After a week that felt like an eternity, our brig set sail back to Plymouth. We returned to Dundalk two months later – and Teresa stunned me with the news: she was pregnant.";
			link.l1 = "Yeah, that tends to happen when you sleep with a girl.";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "Don’t get clever, you brat. Teresa was sobbing on my shoulder, and I was trying to figure out what to do. I wanted to stay with her, I really did – but even then, I felt like nothing good would come of that child.\nI tried to convince Teresa to get rid of it while it was still not too late – but instead, I got an even fiercer fit of hysteria. We couldn’t think of what to do then – so we decided to wait another two months, until the next time the ‘Cornwall’ returned to Dundalk, since at that point the Admiralty still hadn’t turned its wrath on Casper into mercy\nAfter our return I didn’t find her immediately — Theresa’s pregnancy had grown obvious, and, as the owner of the tavern where she worked told me, her bastard of a father beat her and locked her up in the house. Needless to say, I dealt with that old man so severely that he nearly vomited his own guts. Obviously, there was no question of her continuing to live in that house.";
			link.l1 = "And you brought her onto the 'Cornwall'?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "I had to make a quick decision. I knew Casper wouldn’t tolerate a woman on board, so I planned to steal a boat the night after we set sail and make my way to Dublin, which would be just off our starboard side.";
			link.l1 = "And what happened? Did they catch you?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "Exactly. Casper had already poured himself a good dose of whiskey, so he was deaf to any pleas, simply ordering the girl thrown overboard. No matter how I begged, he just laughed himself breathless—damn it, I’m telling you this and I can still hear his laughter in my head...";
			link.l1 = "And that’s when you decided to start a mutiny?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "I had no other choice. Snatching a pistol from the belt of a nearby watchman, I put a hole in that bastard’s forehead. A massacre broke out on board right away — no one liked the captain, but the fear of the tribunal was stronger. It cost nearly a third of the crew their lives — by the time we finally came to our senses, the whole deck of the 'Cornwall' was awash with blood and strewn with the bodies of our dead comrades.";
			link.l1 = " After that, I guess going back to England was off the table. You’d all be facing the noose there.";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "I was certain I would be able to steer the ‘Cornwell’ across the ocean. Here our faces were unknown to anyone, and that gave us a chance to start a new life. Convincing the other officers took little effort — it was less my authority than the contents of a couple of chests, of which the ordinary sailors had no knowledge. The crew decided — Joshua Casper was to be kept alive. We, the officers from the highlands, resolved to buy ourselves some time, sacrifice one of the chests and put into Antigua, where I would assume his name. After that, we intended to set course for Providence.\n That’s exactly what happened: no one suspected the substitution, but when we were only a couple of days from Providence, some bastard blabbed about the second chest — and that caused a split among the crew.";
			link.l1 = "So now they mutinied against you?";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "No, but the number of men willing to keep serving our glorious king dropped fast. And there weren’t that many eager to turn pirate either. So we settled on a middle ground - we’d anchor at a French port, sell the ship, split the money from the sale and the chest, then go our separate ways.";
			link.l1 = "And you didn’t care that you’d have to live among those Catholics you despise so much?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "At that point, I didn’t care where we landed. Teresa - she put on a brave face, but after three months of constant rolling, she was just like any pregnant woman would be. And just like three months earlier, I didn’t give a damn if I was surrounded by Catholics, as long as I was with her.";
			link.l1 = "But there are no French settlements in the northwest of the Caribbean Sea, and there never were.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "By the time things on board the 'Cornwall' reached a boiling point, we had already made it halfway with a favorable wind, which by then wouldn’t let us change course for St. Christopher...";
			link.l1 = "And you chose Tortuga as your destination?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "Back then, it was just a simple village. To delay any possible pursuit from the authorities, we swapped out the nameplate on the stern—so 'Cornwall' became 'Wrangler'.";
			link.l1 = "But for some reason, you never made it to Turtle Island. You couldn't have gotten so far off course that you ended up west of Cuba instead of Tortuga, could you?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "Just so you know, I'm an experienced navigator—better than most. There was no mistake, we were holding a steady course due north. But as soon as we entered the Windward Passage, a terrible squall hit us. I still wonder how on earth we weren’t smashed against the Cuban shore, but were dragged along it instead...";
			link.l1 = "A real miracle, nothing less.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "Holding sobbing Teresa close, I prayed to the Lord with all my heart, begging Him to send us salvation. And He truly did help us.";
			link.l1 = "You were washed ashore on the Isle of Justice.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "Justice – oh yes! When the 'Wrangler' struck the reef, she split in two, but somehow managed to stay afloat – just enough to be carried to where those other wrecks were piled up. The storm raged on for almost two more days, and when it finally calmed – the people from that poor little island saved us.";
			link.l1 = "You, Teresa, and two more sailors. We have a general idea of what happened next. Better tell us how you got out of prison and left the island.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "I wish they'd just shot me back then... If only I'd known what was waiting for me, I'd have chained myself to those bars and never moved an inch.";
			link.l1 = "Was it really less comfortable on the tartane than on the brig, alright? "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "Just don’t tell me you got caught in a storm on a tartane too.";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "Tartane? Ha-ha-ha... Yes, that was my plan. I thought I'd gotten lucky. The head of the prison guard turned out to be a former officer of the English Navy, and he took pity on me. He told me all about the Cuban smugglers' tartanes, and that they were planning to have me executed. I suppose you could call him a man of honor—he was the one who offered to let me go, so I could leave my fate to chance.";
			link.l1 = "I don't understand... If not on tartanes, then how did you leave the island?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "Tartane? Ha-ha-ha... Yes, that was my plan. I thought I got lucky. The head of the prison guard turned out to be a former officer of the English Navy, and he took pity on my misfortune. He was the one who told me about the Cuban smugglers’ tartanes, and that they were planning to execute me. Maybe you could call him a man of honor—he offered to let me go himself, so I could leave my fate to chance.";
			link.l1 = "I don't understand... If not on tartanes, then how did you leave the island?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "If you just shut up and listen, you'll understand. I was swimming towards the tartanes, swimming for a long time—until I saw a light beyond the wall of rain. It was something absolutely unbelievable, damn it. It shone like the sun on the deck of one of the half-sunken galleons, and I headed straight for it. Not knowing yet that I was making the worst mistake of my life. I climbed out of the water using the boarding ladder—and found myself face to face with the light. It sparkled above a golden statue and...";
			link.l1 = "The idol of Kukulkan. That’s right, back then 'San Jeronimo' hadn’t sunk yet...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "So, you saw him too, "+pchar.lastname+"?";
			link.l1 = "Not just saw it. I traveled through space with its help, and more than once, alright.";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "You're lying! Several times, you say?! Then how can you be standing here, looking so full of life?!";
			link.l1 = "After I was moved, I drank an Indian potion, and that's what helped me stay alive and regain my strength.";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "Ah, so that's how it is. Do you have any idea how long it took me to get my strength back? Do you?!";
			link.l1 = "I suppose I can guess. You touched the idol, and it sent you to Dominica – to the Indian village, where they sacrificed you to the statue, and then you ended up on the Main, right?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "Exactly. I’ve never felt pain like I did then, lying by that statue. I don’t even know what to compare it to. Maybe if a stone house collapsed on you—even then, you wouldn’t suffer like that. As soon as I came to, I saw a crowd of natives coming at me again. If I’d spoken their language—swear to God, I would’ve begged them to kill me right there.";
			link.l1 = "Were those Miskito Indians from the nearby village?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "That's them. They dragged me into one of the huts, where some strange native—didn't look like the others—poured something right into my mouth. The pain eased a bit, but didn't go away completely. By evening, they hauled me out to the fire, and that painted bastard started performing some kind of ritual. Pathetic bastard.";
			link.l1 = "Snake Eye... You should've been grateful to him for saving your hide.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "Rescue?.. Three years, "+pchar.lastname+". For three years I lay almost motionless, soiling and wetting myself, waking up in my own vomit – because I just couldn’t stand all those foul-smelling brews and tinctures they kept forcing down my throat! And then I spent almost another year learning to walk again.";
			link.l1 = "A heartbreaking story. But honestly, I almost feel sorry for you.";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "Shove your pity up your Pope’s fat Catholic arse. I don’t need anyone’s sympathy. Should I go on, or do you need a moment to cry, little peacock?";
			link.l1 = "This journey certainly hasn't improved your manners. But alright, for Mary's sake, I'll put up with it. Although I suppose we've already learned the main thing—still, let's hear you out to the end.";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "Somehow managing to get back on my feet, I left that cursed village and made my way to the coast, to Amatique Bay. There, I met some smugglers whose ship was anchored nearby and joined them, calling myself Rupert Casper — I didn't want to give up my first name, but I also kept the surname of one of those who'd ruined my life. Just so I’d never forget why I ended up here.";
			link.l1 = " Everyone’s to blame, as far as you are concerned, Northwood... except for yourself. Still, I can see why — years of humiliation and hardship, and now you’re stuck in these woods. Who wouldn’t lose their mind? ";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "You've been through a lot, Northwood – no doubt about it. And now, look where you are... In the woods, at the edge of civilization. You won't lose your mind out here...";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "I am the master of these woods, "+pchar.lastname+". In over fifteen years, I went from a miserable sailor on a smuggler ship to their leader. Not just the captain of some little boat, but the master of the entire coast, from Amatique Bay to the Bay of Doom.";
			link.l1 = "Well, that's quite a comeback, I admit.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "I am the master of these woods, "+pchar.lastname+". In over fifteen years, I went from a miserable sailor on a smuggler’s ship to their leader. Not just the captain of some little boat, but the master of the entire coast, from Amatique Bay to the Bay of Doom.";
			link.l1 = "Well, that's quite a comeback, I admit.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "Some say this is the domain of the Forest Devil... What a brazen lie – these are my lands. And Svensson knows it, ha-ha-ha. He’s sent his men here more than once, tried to find out who I am – and not one of them ever made it back to him. Alive, heh-heh. You could count on one hand those who know the name I started my smuggling career under, or where in these woods I live.";
			link.l1 = "So, you go by a different name now. No wonder you panicked when you heard someone was looking for Rupert Casper.";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "Panicking? Are you serious, boy? The only one panicking here is you – on my turf, surrounded by my people, completely at my mercy! I can do whatever I want with you. And with her too – just for being the reason I had to go through all that torment!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "You're mad, just plain mad, alright. I don't know of any cure or doctor who could fix you, Rupert Northwood! You've been through hell, but... how can you blame it all on me?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "I already told you – if it weren’t for you, none of this would have happened. Just admit it, alright?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "Leave him, "+npchar.name+". We've heard enough. Some roads really aren't meant to be followed to the very end. I had a bad feeling when we decided to get involved in all this. But I didn't listen to it. Pity.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "Yeah, then neither of you would have ended up here, trapped and powerless to do anything. Now feel for yourself, daughter, what I went through!";
			link.l1 = "And who told you we're powerless to do anything? Tro-o-o-op, to arms!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "What's the matter, rookie? Lost someone? Ha-ha-ha... Ha-ha-ha. HA-HA-HA-HA-HA-HA!!! Oh, you should see your face right now, you fool! Hey, Mason, bring over my gift for our guests.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "Bastard! Where are my people?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "You mean that handful of fools who thought they could ambush me? My friend the innkeeper warned me in time about your arrival in town, so I gave them the welcome they deserved... A few managed to slip away. But don’t worry – I caught one of them alive. So you can see for yourself what fate awaits you today.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "Scoundrel! You’ll pay for this! (cries) I swear, alright!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "Alonso! I'm so glad to see you!";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "And I’m just as glad to see you, Cap! Someone tipped that scoundrel off that you were after him — and we were met with a hail of grapeshot halfway there. I managed to pull back with a handful of men, and we ran straight to the port to warn you. Luckily, the watchman on duty saw me on the barque I’d hastily bought in town and figured out what was going on right away. He quickly gathered the men — and we set off here to help.";
			link.l1 = "Thank you, my friend. You saved us from certain death.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "That's nothing. What do we do next, Cap?";
			link.l1 = "Gather the crew and head to the ship. Mary and I need some time alone.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "My God, "+pchar.name+"... I still can't, I just can't believe it. My father... He's a monster... Why would he do this to me? Has he really lost his mind?";
			link.l1 = "He had to endure terrible suffering. The mutiny on the 'Cornwall', the escape across the Atlantic, the storm, and your mother's death. I can't imagine how he survived the journey through those idols' portals without the Comanche potion – but that's what destroyed his mind.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "And what if he was always like that? Or maybe he was just as much of a scoundrel, only a bit softer, but truly loved my mother? What if all this just set free what was already inside him? And if that's the case... what if there's something of him in me too? That could happen, "+pchar.name+", alright?";
			link.l1 = "You've definitely picked up something from him, "+npchar.name+". In today's fight I noticed – you fight with the same determination, the same fire in your eyes, and that very same fury as he did. But you don't have his madness. You're something else entirely. Alive, open, with your heart on your sleeve. That's exactly why I fell in love with you. And it seems Northwood was right: you've got your mother's spirit through and through.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "Do you really think so, darling?";
			link.l1 = "Of course, my love. If I’d met him just like that, without knowing who he was, I’d never have guessed you were related.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "You know, there’s not much entertainment on the Isle of Justice. Since I was a kid, I’ve loved fencing—at first I fought the boys with wooden sticks, then with grown men, real blades, alright. I always wanted to be their equal... but somehow I always felt weaker, even when I came out on top.   So I’d just go home and practice some more. I’d train for hours, until my hands started to shake, alright. Is that the fire you mean? That rage you’re talking about?";
			link.l1 = "In a way – yes. I think that fire gives you much more strength than you see in yourself. And whether you like it or not, it’s a gift from your father. Even if he never meant to give you anything.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "Do you think we did the right thing by digging up the past?";
			link.l1 = "Now that we know everything... it doesn't seem like such a good idea anymore. But if you want to know the truth, you have to be ready for the fact that you might not like it.";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "You're right, "+pchar.name+", alright... Let's stay here a little longer. I don't feel like going back to the ship just yet. I just want to... sit here, in the quiet.";
			link.l1 = "Of course, my love. I was just about to suggest the same.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
		
		// Тичингиту
		case "WildRose_Tichingitu_Final_1":  
			dialog.text = npchar.name + ", came right on time, Captain " + pchar.name + ".";
			link.l1 = "I knew I could count on you, my friend. Thank you — no one could've done it better.";
			link.l1.go = "WildRose_Tichingitu_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tichingitu_Final_2":
			dialog.text = "The jungle is " + npchar.name + "'s home. " + npchar.name + " glad to fight in jungle. Jungle give strength to " + npchar.name + ".";
			link.l1 = "That's exactly why I put you in charge of the squad. And it paid off — as you can see, they welcomed us with open arms.";
			link.l1.go = "WildRose_Tichingitu_Final_3";
		break;

		case "WildRose_Tichingitu_Final_3":
			dialog.text = "What Captain " + pchar.name + " planning to do next?";
			link.l1 = "Mary and I need some time alone. Gather the wounded and take them to the ship. Bring the dead too — we’ll bury them at sea. And, " + npchar.name + "... tell Alonso that Mary’s father should be buried here, in proper Protestant fashion. Only he and you must know this. No one else — not even Mary. She doesn’t need to suffer more than she already has.";
			link.l1.go = "WildRose_Tichingitu_Final_4";
		break;

		case "WildRose_Tichingitu_Final_4":
			dialog.text = npchar.name + " understand, Captain " + pchar.name + ". Tichingitu will do everything.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Дюран
		case "WildRose_Duran_Final_1":   
			dialog.text = "Tough bastards... But we outsmarted them, ha-ha! Let 'em rot here and think twice before messing with us again.";
			link.l1 = "Thanks, " + npchar.name + ", you did a great job. I shudder to think what might’ve happened to Mary... or to me... if I hadn’t sent you to cover our backs...";
			link.l1.go = "WildRose_Duran_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Duran_Final_2":
			dialog.text = "Ha, Cap’n, you’d have found a way — I know you. Did you see that big blade their leader had? I couldn’t take my eyes off it. If you don’t like it, I won’t be offended if you gift it to me.";
			link.l1 = "Hm... We’ll see, mate, we’ll see. For now, gather the survivors and head to the ship. Bring the fallen aboard — we’ll give them to the sea. And... that leader — he was Mary’s father. Take Alonso and bury him properly, in Protestant tradition, somewhere here. No one is to know where the grave is. Especially not Mary. She doesn’t need that kind of pain.";
			link.l1.go = "WildRose_Duran_Final_3";
		break;

		case "WildRose_Duran_Final_3":
			dialog.text = "Will do, Cap’n. Wait... On second thought... never mind. I’ll go.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Тонзаг
		case "WildRose_Tonzag_Final_1": 
			dialog.text = "Pretty damn hot out here, Cap’n. Those bastards got what they deserved. Did you see that little runt’s face twist when we showed up?";
			link.l1 = "He clearly didn’t see that coming. Just like Mary and I didn’t expect him to be such a scumbag. Still, my gut didn’t fail me when I chose to cover our rear.";
			link.l1.go = "WildRose_Tonzag_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tonzag_Final_2":
			dialog.text = "You ain’t new to the Caribbean, Cap’n. You must’ve gotten used to the kind of scum crawling around here, and learned to smell trouble from miles away. What now? We heading back to the ship?";
			link.l1 = "Gather the wounded, collect the dead, and get everyone on board. Those we lost — we’ll give them to the sea, like true sons of the ocean. Mary and I will stay behind for a while — we need some time alone. One more thing: bury Mary’s father in the Protestant way. Take Alonso with you if needed. Just make sure no one knows the burial spot. Especially Mary. I don’t want her haunted by memories.";
			link.l1.go = "WildRose_Tonzag_Final_3";
		break;

		case "WildRose_Tonzag_Final_3":
			dialog.text = "You’re right. No point in her coming back here just to shed tears. Don’t worry — we’ll do it properly, and no living soul will hear a word of it.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Айронс
		case "WildRose_Irons_Final_1":
			dialog.text = "Captain, sir, reporting in: ambush successful, scum eliminated, captain secured.";
			link.l1 = "This really isn’t the time for sarcasm, and if you’re trying to be funny — bad idea. You don’t want to be scrubbing the deck in front of the crew, do you? Oh, they’d love that... I suggest you don’t test my patience. Not today.";
			link.l1.go = "WildRose_Irons_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Irons_Final_2":
			dialog.text = "Uh... well, I *am* an officer, and...";
			link.l1 = "For now. Today an officer — tomorrow a deckhand, and the day after — a beggar.";
			link.l1.go = "WildRose_Irons_Final_3";
		break;

		case "WildRose_Irons_Final_3":
			dialog.text = "Understood: " + GetFullName(pchar) + " is Captain Serious. No more jokes. Orders, sir?";
			link.l1 = "Gather the wounded and get them aboard. Tell Alonso to take a crew and recover the bodies of our men — we’ll give them to the sea. Also, have him bury Mary’s father according to Protestant traditions. Only he and whoever helps him should know the burial place. Mary doesn’t need to know. I don’t want her tormented by memories.";
			link.l1.go = "WildRose_Irons_Final_4";
		break;

		case "WildRose_Irons_Final_4":
			dialog.text = "Alright, alright... Consider it done. And don’t worry — I know how to keep my mouth shut.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Лонгвэй
		case "WildRose_Longway_Final_1":
			dialog.text = "Captain, sir, we did it. Not a single dog got away.";
			link.l1 = "Good job, " + npchar.name + ", thank you. I knew I could count on you. Gather all survivors and head back to the ship. Mary and I will stay ashore a little longer.";
			link.l1.go = "WildRose_Longway_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Longway_Final_2":
			dialog.text = "What should we do with the bodies of the dead?";
			link.l1 = "We’ll give them to the sea. Tell Alonso to handle the preparations. And one more thing: tell him to bury Mary’s father according to Protestant customs, somewhere here in the jungle, far from prying eyes. No one must know where the grave is — especially Mary. Knowing her, she’ll want to come back here, and that won’t do her any good.";
			link.l1.go = "WildRose_Longway_Final_3";
		break;

		case "WildRose_Longway_Final_3":
			dialog.text = "Understood. Anything else, sir?";
			link.l1 = "That’s all, my friend. Go rest and take care of your wounds.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Алонсо
		case "WildRose_Alonso_Final_1":
			dialog.text = "Hell of a bloodbath... You alright, Cap’n?";
			link.l1 = "I’m fine... except for the fact that Mary and I just had to kill her father...";
			link.l1.go = "WildRose_Alonso_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_Final_2":
			dialog.text = "From the looks of it, he was a real bastard...";
			link.l1 = "You got that right, " + npchar.name + ". Still, he deserves a proper burial — Protestant rites. I want you to handle it personally. No one must know where the grave is. Especially Mary.";
			link.l1.go = "WildRose_Alonso_Final_3";
		break;

		case "WildRose_Alonso_Final_3":
			dialog.text = "You want to spare her the bad memories?";
			link.l1 = "And needless torment. Send everyone else to the ship to recover. Bring the fallen aboard — we’ll bury them at sea once Mary and I return. For now, we need to be alone.";
			link.l1.go = "WildRose_Alonso_Final_4";
		break;

		case "WildRose_Alonso_Final_4":
			dialog.text = "I’ll tell the boys to leave you be.";
			link.l1 = "Thanks, " + npchar.name + ".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
	}
}
