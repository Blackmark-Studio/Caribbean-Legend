// Диего де Монтойя
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
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", Chief of the San Jose patrol. We've received a message concerning suspicious behaviour on the outskirts of this town. Would you be so kind as to explain to us who you are and what you're up to?";
			link.l1 = "Captain "+GetFullName(pchar)+", señor officer. I am here under the authority and direct instructions of Inquisitor Father Vincento. Here is a document confirming my authorisation.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "All right... Everything looks fine. It's filled out properly with the signature of the inquisitor. My apologies for my suspicions. What are you doing at the lighthouse?";
			link.l1 = "I'm not authorised to answer such questions. If you are genuinely interested in the purpose of my work for the inquisitor, I would recommend referring directly to him in Santiago for clarification. You are an officer; surely you have knowledge of military and service secrets. The only thing I can tell you is that I am investigating the circumstances of a wrecked Spanish ship.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "My apologies once again, Monsieur. I won't dare delay you any further... ah, one moment! Did I just see the blade of cold steel or was it just my imagination? What an interesting dagger you have! Can you show it to me?";
			link.l1 = "Make sure you don't forget to give it back. It's very important to me.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "Dios mio! I know this dagger, I saw it depicted in one of the library books! This is the dagger of Cortés himself! It's branded right here... Monsieur, please don't refuse. Let me have this dagger! I collect ancient and personalised weaponry and this is simply an incredible specimen. I'll pay well for it.";
			link.l1 = "Señor, this dagger is not for sale. I received it as a gift and I'm not inclined to sell it to anyone. Give it back, please.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "You wouldn't even be satisfied with five hundred gold doubloons? That's a fortune. You could buy a ship with that!";
			link.l1 = "No. I already have a ship, and the dagger is one of a kind. I will not sell it.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "Eh, that's too bad... All right, take your valuables. I won't dare disturb you any longer. Good luck!";
			link.l1 = "All the best, officer.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\English\Sharlie\Diego De Montoya.wav");
			dialog.text = "Enough! I want to have a word with him...";
			link.l1 = "So, I see Diego de Montoya himself right in front of me... But pardon me, señor. We've met before, haven't we? Oh yes, that's right. Trinidad, at the local lighthouse. But I am sure that you called yourself something else there...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "Your memory serves you well, sir. Well, you're not the only one capable of sparking intrigue and waging wars behind the scenes. I am well informed of your undying desire to see me. Well, it seems your wish has come true.";
			link.l1 = "This wasn't exactly the type of encounter I was hoping for, señor.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "Well, it is what it is. But I will give you a chance to get out of here alive if you give me your dagger.";
			link.l1 = "Has your passion for collecting rarities really sent you that far down the pipes, caballero, that you had to prepare such a well-thought-out trap for me?  Oh, I don't think so. Is the Guardian of Truth keeping you on your toes or am I far off?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "I have no idea what you're talking about. The dagger must return to where it belongs and that's all you need to know. You wouldn't give it up for gold, so now you'll give it up for your own life.";
			link.l1 = "Do you really think, señor, that I'm going to believe what you've just told me? You've already decided that I'm not leaving this bay, haven't you?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "And what if I give you my word?";
			link.l1 = "The word for a 'frog-eater'? Hm...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Monsieur, I'm giving you one last chance. Either you hand over the dagger I'm interested in, or I'll be looting your dead body in a few minutes. Resistance is futile; we've got an overwhelming advantage in numbers.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "You have surprised me, señor, that's for sure. Do you really think that I'm such a bullheaded imbecile that I would just put my head in the jaws of a shark without bothering to snag my harpoon? Guys, kill them!";
			else link.l1 = "Real power is not in numbers, but in skill, señor!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
