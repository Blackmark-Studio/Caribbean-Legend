// Вильям Патерсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Is there something you want?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "Hello, Monsieur. God damn it, so you're the one who stirred up all the military strife around here?!";
			link.l1 = TimeGreeting()+", sir. Yes, it was my ship that made the landing. What's the matter anyway? Who are you? An Englishman, I suppose?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "A Scotsman, Monsieur. Captain of the English Navy, William Paterson, and this is my first mate and right hand, Archibald Calhoun. The thing is, there is a Spanish fort in the jungle. My mission is to drive the cursed bastards out of the fort, which they have built dangerously close to English territory.\nRecently, we tried to storm it, but the bastards managed to hold out despite their losses. I left for reinforcements and...";
			link.l1 = "No need for that now. I've completed your unfinished business; the jungle fort is empty. The Spanish commander, Diego de Montoya, is dead, and his squadron has been wiped out as well.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "What kind of vigilantism is this? What's your motivation for stirring up such military action on English territory?";
			link.l1 = "I dare remind you, Captain Paterson, that this isn't Belize. What English possession? All this fuss started because of Don Diego de Montoya and his reckless decision to attack me and my ships.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "Ehem... and what reason did Don Diego have to attack you, eh captain?";
			link.l1 = "He and I have a longstanding feud... Ever since the day when the squadron he was leading attacked St. Pierre, and a little later was eliminated with my direct involvement.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "Blast it! I needed that venerable caballero alive! I was going to interrogate him about why he set up a military base in the jungle. It couldn't have been for no reason...";
			link.l1 = "I'm sorry, but he can't tell you anything now. Anyway, the fort may contain wounded soldiers from the garrison. Is there a chance they could talk?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "Soldiers... Oh, what's the use of some hard-headed ramrods!... Where's Don Diego's corpse? He could've had important documents on him!";
			link.l1 = "I left Don Diego on the grounds of the armoury fort. If you need him so badly, you can find him there. I don't think he can run off.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "Eh... and who asked you to butt into someone else's business... You've given me enough of a headache already...";
			link.l1 = "Captain, I don't understand why you reprimand me. I've done your work, put my own people into battle, risked my own life, and yet you're displeased. All you have to do now is inform Port Royal of your success in the mission and all your affairs. I won't claim any credit for your glory, I assure you.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "Claim credit? What do you mean by glory?! You don't get it at all... Eh, fine. Farewell, sir.";
			link.l1 = "All the best to you as well!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\English\sharlie\Willie Paterson.wav");
			dialog.text = "Man, the gossips weren't lying when they said you have nine lives like a cat! "+TimeGreeting()+", Monsieur de Maure. You don't look very well...";
			link.l1 = TimeGreeting()+", Mr Paterson. I must say, you and your friend Archibald played your parts and fooled me rather well. Damn you all! I didn't even see it coming...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "Hey, don't swear before the gates of the Holy Land. You didn't see it coming? I am flattered: I have fooled one of the most famous intriguers of the archipelago. The diary idea was brilliant, don't you think?\nI had to lure you to some obscure place; killing you in the open would be a scandal, you are a close friend of Philippe de Poincy, am I correct? Now you are going to disappear without a trace and no one will ever know how.";
			link.l1 = "So, everything Calhoun told me... was a lie?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "Not at all. I really did find poor Archibald at this place. He didn't write any memoirs, though; the diary you found in his room was written at my request, especially for you, Monsieur de Maure.\nI have been keeping an eye on you since we met at Cape Catoche. It was you who took the map of Two Appearances from Don Diego's corpse, wasn't it? Don't deny it, I know it was you.";
			link.l1 = "You know about the Guardian of Truth as well?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "That's a stupid question. Of course I do. And I know that you have the Chief's Claw on you too. And soon you will return those items, which do not belong to you.";
			link.l1 = "I'm glad you don't wobble like Don Diego. I appreciate honesty and directness. As I understand, you have the compass, the Arrow of the Way?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "Haw-haw! Well, we'll be honest right up until the end... Do you really believe, sir, that I'm such an idiot, like you and Don Diego, that I would carry such a precious object with me? The compass is in Jamaica, and not even in Port Royal, but in a place where no one would ever think to look, and under a secure lock. But you won't be needing that information.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "As I understand it, you've already buried me, Mr Paterson? I dare proclaim that the cat has one life left!.. Where are my officers?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "As I understand it, you've already buried me, Mr Paterson? I dare proclaim that the cat has one life left!..";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "Worried about your lady friend, captain? Your woman is lying over there in the bushes with a hole in her forehead. She's paved the way for you, and you'll soon be joining her. I must say, she was a pretty girl! I hope you bedded her more than once?";
				link.l1 = "C'est un fils de pute! You'll pay for that, you bastard?!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "Your officers have paved the way for you, Monsieur de Maure. They're lying over there in the bushes. Soon you'll join them.";
				link.l1 = "We'll see about that!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "We'll make sure it truly is your last.";
			link.l1 = "We'll see about that!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "You make me laugh. One against a whole troop! Anyway, enough chatting... Aim your muskets! Fire!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
