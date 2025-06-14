void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Cap'n, the day is ours. The vanguard's finishing the sweep of the lower deck. No prisoners... Ha! I see you didn't hold back either.";
			link.l1 = "For some reason, I expected to make some grand speech. But he just charged in.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "Permission to speak freely?";
			link.l1 = "Granted.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "No, we're done here.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "Why did we attack them? That brig wasn't a threat, it wasn't hauling cargo. Sure, there were all sorts of rumors about Grim, but only slavers feared him. A lot of people died today — and for what?";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "Are you speaking for the crew now?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "And it's not the first time...";
			link.l1 = "Are you speaking for the crew now?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "Nope. Believe me, if the crew had questions like that, it would mean I'm bad at my job and you're already a dead man walking\n"+
			"Luckily for you, the lads made a nice profit off this bloody venture. Every sailor on this ship had their pockets stuffed with doubloons!\n"+
			"No valuable cargo though — just native trinkets and creepy talismans. Still, the crew made out like bandits. Seems Grim paid them well\n"+
			"I hope you're not planning to claim a share of that gold, cap'n?";
			link.l1 = "I'm not, Alonso. Thanks for keeping me informed.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "I am. Make sure my share gets delivered to my cabin.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;

		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Always on your side, cap'n. By the way, what do you plan to do with the Memento?";
			link.l1 = "Take it as a prize — what else?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Haven't decided"+GetSexPhrase(""," yet")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Always on your side, cap'n. By the way, what do you plan to do with the Memento?";
			link.l1 = "Take it as a prize — what else?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Haven't decided"+GetSexPhrase(""," yet")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "Better not. It's covered in some kind of native symbols. And there are bad rumors about it — they say it once survived a monstrous plague and the decks almost danced with corpses\n"+
			"As for the skeleton on the stern, I won't even go there: until some idiot dares to snatch the skull for fun, no one but me will dare keep watch there.";
			link.l1 = "Got it, Alonso. Back to work.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "Aye, cap'n.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Captain, sorry to disturb you at this hour.";
			link.l1 = "Report, Alonso.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "Captain? What are you doing here? Were you sleeping here?";
				link.l1 = "Doesn't matter.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "My cabin feels... unsettling.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "Things are bad. Crew morale is in the gutter! People are openly saying the ship is cursed. Complaining they’re seeing things at night.";
			link.l1 = "Seeing what exactly?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Nightmares, mostly. But the worst is that one of our men died of a fever. A young lad, strong as an ox, and he burned up in a few hours.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "That's for the doctor to decide. "+sld.name+" knows their business.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "That’s not normal. Keep the crew in line, Alonso. That’s your job.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "Aye aye!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "I understand. Many in the crew now sleep in groups — afraid to be alone. As if it's even possible to be alone on this ship...";
			link.l1 = "Doesn't seem like I managed it. What happened?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "A fight — José stabbed Marcel. Was shouting he 'carried the plague.'";
			link.l1 = "Is the situation getting worse?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = sld.name+" already reported this morning. We've lost eleven souls. What shall we do?";
			}
			else
			{
				dialog.text = "Another eleven souls lost. What shall we do?";
			}
			link.l1 = "I'll make the call.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "I hope so, Captain. What about José? Killing isn't a joke.";
			link.l1 = "Hang him after the bell. Show we're in control.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Thirty lashes. If he survives — then it's God's will.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "Aye aye!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "Aye aye!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "Cap'n! Alarm!! You must get to the gundeck immediately!";
			link.l1 = "What's going on?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "You'd better see for yourself. Come on, quickly!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "Good morning, cap'n!";
			link.l1 = "Huh?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Uh, you look awful. Rough night? Well, I've got good news. The epidemic's over. Turns out — there wasn't one.";
			link.l1 = "What do you mean?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "The crew got spooked, started believing those silly ghost ship stories. Power of suggestion — a scary thing, I tell you. Has sunk more than one ship.";
			link.l1 = "But people died!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Fighting, dirty wounds, spoiled salt meat — just regular sailor math. If we hadn’t all whipped ourselves up with tales of cursed ships, maybe we'd have lost a few less\n"+
			"That skeleton on the stern didn’t help. Good thing some… prankster stole its hat during the night\n"+
			"Since lightning didn’t strike us down for such blasphemy, the crew perked up and their sailor wits got busy cooking up mischief. Like, for example...";
			link.l1 = "No touching the skeleton!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Er... well, if you've grown fond of it, of course we won’t. Have a good day, cap'n\n"+
			"By the way, nice hat! Looks great on you. Clearly didn’t fit the previous owner.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Greetings, Captain. You should speak to Captain Grim.";
				link.l1 = "Sorry, sailor, but you stand out here.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Anything else, Captain?";
				link.l1 = "Nothing.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "I know what you mean, Captain. I served under a free captain — much like yourself. He hunted treasure, traded, took on freight. Then he decided to rob some merchants — didn’t work out. The survivors were sentenced to hang for piracy.";
			link.l1 = "And Captain Grim bought you?";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "Bought us all in one lot, like cargo. Every ship needs seasoned sailors, and Grim doesn’t recruit in taverns... But he feeds us and pays well. And we serve — and draw lots.";
			link.l1 = "The lots?";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "Sorry, we shouldn’t talk about that.";
			link.l1 = "Why not just leave?";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "Where to? At least here there’s a chance. Maybe luck will smile. Every ship has its own lot. Grim has his, you have yours. We’re not men, just numbers in the ship’s log.";
			link.l1 = "Things are different on my ship.";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "As you say, Captain. Good day to you.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "It's been a long time since we've had visitors on this fine vessel!";
				link.l1 = "Are you a sailor? You don't look the part.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Anything else, Captain?";
				link.l1 = "Nothing.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_2_1":
			dialog.text = "Ha! The cap’n bought me straight out of the cell. Was supposed to hang in Port Royal — stabbed some fop who kept reciting poetry. Deserved it, the bastard.";
			link.l1 = "So you got lucky, then?";
			link.l1.go = "Memento_Sailor_2_2";
		break;

		case "Memento_Sailor_2_2":
			dialog.text = "You bet! The captain's not stingy, though sometimes you have to play his... games.";
			link.l1 = "What kind of games?";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "Every week we draw sticks: the short one means a dangerous job, or sometimes you jump overboard. It's a laugh, really. Not for everyone, but the captain says it's how he weeds out the unworthy.";
			link.l1 = "Unworthy of what?";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "How should I know? The cap'n loves to talk, preaches like a priest: «Only by facing death can you truly live!»\n"+
			"(He spits.)";
			link.l1 = "Spitting on deck earns you the lash. You're acting like a brigand, not a sailor. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Greetings, Captain.";
				link.l1 = "How did you end up here?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Anything else, Captain?";
				link.l1 = "Nothing.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "Captain Grim took the slaver ship I was on. I was sick, dying in the hold ... I don't remember much. Next thing I knew, I woke up here, on the Memento.";
			link.l1 = "And what happened to the other slaves?";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "I don't know. Captain says he freed everyone, but I was the only one brought aboard. The rest must've scattered across the islands or died from their wounds. That day is a blur to me.";
			link.l1 = "At least you're free now.";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "Free? No one's free here. The captain gives gold, food, clothes, but in return he demands total loyalty — and makes us draw those cursed lots.";
			link.l1 = "The lots?";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "Every week, someone draws the short stick and gets a dangerous job — not all come back. Captain says it's how the living are separated from the dead.";
			link.l1 = "And you put up with that?";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "Everyone hopes luck will favor them. The captain knows what drives each man: fear of the noose, greed for gold, the urge to repay a debt for a saved life. None of that matters to me. I don't need money, and what debt can you owe for something you don't remember?";
			link.l1 = "Aren't you afraid to speak so openly?";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "What can they do to me? This is a ship of the dead, Captain, and I belong here. But you — you do not.";
			link.l1 = "If you say so. Farewell.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Welcome aboard the Memento, Captain.";
				link.l1 = "A Spanish soldier on a pirate ship? That's not something you see every day.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Anything else, Captain?";
				link.l1 = "Nothing.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		case "Memento_Sailor_4_1":
			dialog.text = "I'm a deserter. Captain Grim bought me right off the gallows in San Jose square. Paid a hefty price — a whole sack of doubloons for my sorry hide.";
			link.l1 = "What did they hang you for?";
			link.l1.go = "Memento_Sailor_4_2";
		break;

		case "Memento_Sailor_4_2":
			dialog.text = "Officer Saldo sent us to guard laborers in the jungle, where half die of fever in a week. I figured my life was worth more. Now I serve the man who put a price on it.";
			link.l1 = "No regrets?";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "A rope may twist for a long while... Captain's generous to those loyal to him. Though sometimes he sets us to strange trials — drawing lots. Not everyone gets lucky.";
			link.l1 = "Drawing lots?";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "You know. Some get sent aloft in a storm, some to the vanguard. Captain says it's how he tests if you're ready. Ready for what, I can't say, but I hope luck's on my side.";
			link.l1 = "Good luck... I suppose.";
			link.l1.go = "Memento_Sailor_4_5";
		break;

		case "Memento_Sailor_4_5":
			dialog.text = "Thank you, Captain. Death comes for us all, sooner or later.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Диалог 5";
				link.l1 = "Диалог 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Welcome aboard the Memento, colleague. Name's Mortimer Grim.";
				link.l1 = "Captain "+GetFullName(pchar)+". Thank you for having me...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "What else shall we talk about?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "That's a remarkable blade you have, Captain.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "Your spyglass looks great next to the skeleton.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "I must say, your crew is quite the motley lot.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Nothing... colleague. Fair winds to you.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "The Caribbean is generous to those who rush to the gallows, that much I know.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;
		
		case "Memento_MortimerGrim_3":
			dialog.text = "Yes? Was there something you wished to ask?";
			link.l1 = "You've got a skeleton hanging behind you.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Fine wind today, isn't it? And the weather's grand.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "What skeleton? Behind me there's only the blue Caribbean Sea.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "Agreed, colleague. Wouldn't mind every day being like this!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "Ha-ha-ha! That joke never gets old! Don't be alarmed: old Yorick, like this ship, is a keepsake from my former life. Quite literally, I assure you.";
			link.l1 = "'Literally?'";
			link.l1.go = "Memento_MortimerGrim_7";
		break;

		case "Memento_MortimerGrim_7":
			dialog.text = "Colleague, do you fear death? No threat, I'm genuinely curious.";
			link.l1 = "Of course. Anyone who says otherwise is a liar.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "No. We'll all end up there.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "And you?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "Oh! Death is the mother of all fears. Loneliness, darkness, punishment — they're all just her masks.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "Oh! Death is the mother of all fears. Loneliness, darkness, punishment — they're all just her masks.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "Oh! Death is the mother of all fears. Loneliness, darkness, punishment — they're all just her masks.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Memento_MortimerGrim_9":
			dialog.text = "No need to look far. Take old Yorick: a pile of bones with a lantern in his ribs — yet even a fearsome captain like you got rattled!";
			if (startHeroType == 4)
			{
				dialog.text = "No need to look far. Take old Yorick: a pile of bones with a lantern in his ribs — even fearless Ellen, daughter of the great Sean MacArthur, got spooked!";
			}
			link.l1 = "You speak well, but you haven't said what to do with all that.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;

		case "Memento_MortimerGrim_10":
			dialog.text = "I know what to do, but my cure doesn't suit everyone. You can always try it, but first, tell me what you think.";
			link.l1 = "The Bible says there is no death.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "If I start fearing, the ship is doomed.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "The answer drowned at the bottom of a bottle of rum.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "That's true. The only thing I agree with in that book.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_2":
			dialog.text = "Admirable. But you worry for nothing: there is no death.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "Yo-ho-ho! A cynic. But even without rum, I'll say: there is no death.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "It's simple: true life begins only when you conquer death. I've been there, beyond the veil, and believe me, I only truly started living after that.";
			link.l1 = "Come again?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "Never mind, colleague.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "Glad you noticed, colleague! I'm no show-off, but what kind of pirate would I be without a fearsome cutlass?";
			link.l1 = "Does that really matter?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "Exactly! The only time I notably lightened the ship's treasury for personal reasons was for this very blade. Two thousand gold doubloons, colleague! Hell, if I could rise from the grave a second time, I'd come back just for its price!\n"+
			"The weapon itself is excellent. But somehow... it feels like something’s missing.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "A gift from someone. A brilliant conversationalist, who understands death like no other — and with a wild imagination, as you can see.";
			link.l1 = "Looks grim.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, colleague.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "My crew has more in common with each other than yours, for example... All of them were freed by me from rope and chains. Each has felt death’s breath. That binds people better than blood or flag.";
			link.l1 = "So, you don’t hire people in taverns, I suppose?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "You’d be surprised how willingly former slaves and condemned men sign up: swap a slaver’s hold or the gallows for Memento’s deck? I’ve got 178 crew now — and each of them owes me.";
			link.l1 = "But you must still pay them and maintain the ship. Gratitude alone won’t cut it.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "I’m a successful pirate, colleague. A true hostis humanitatis. That’s what the real enemies of humanity — slavers and crowned heads — would call me. The only difference between them is the title.\n"+
			"Luckily, they’ve got plenty of gold. I use the coins from slaver chests to save those condemned by the crown. The rest goes to my crew — I need nothing. What use has a dead man for gold? They’ll figure it out soon enough...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "That's the shitty situation we're in, Cap'n.";
			link.l1 = "What is this?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "You're the only one left. The sickness got us all. You let us down.";
			link.l1 = "That can't be!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "You brought us aboard a cursed ship.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "You doomed us all!";
			link.l1 = "Alonso, what's wrong with you?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "Why'd you stop, colleague? Changed your mind? Then why attack in the first place?";
			link.l1 = "Grim? But you're dead!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "Ha! What is dead may never die. And besides, you're jumping ahead: maybe you won the boarding, but will you survive... well, let's find out!";
			link.l1 = "That fight ended weeks ago! You're dead!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Now it's done. Congratulations on your victory.";
			link.l1 = "Grim?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "You know, I'm glad. Truly glad you killed me. For real.";
			link.l1 = "What are you talking about?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "I'm a coward, colleague. Just a pitiful coward who was afraid of death — like thousands before him. When the crew died of the plague... and it was my fault, I went mad with fear. I drifted for a month alone on a ship of the dead.";
			link.l1 = "What really happened?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "I failed the trial of death. Instead of accepting it, surviving, and learning something, I became even more afraid. And to muffle that fear... I started forcing others to go through what I did.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;
		
		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Thank you, colleague. For freeing me from this... existence. Now I truly know there is no death. And I'm not afraid anymore. No one left to blame or enslave.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "Don't separate the Memento from its captain. Mortimer... Captain Mortimer was a good man. Find him on Dominica. And the ship... the ship will accept you.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, colleague. The dead teach the living. Farewell.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 