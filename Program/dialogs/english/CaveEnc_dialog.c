// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Do you want anything?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Whoa-ho, look who's here! Well, today is your lucky day, mate. We're good people, see, just cooking some food and such... I'm not inviting you to our dinner, but you'd best get lost while you still can.","Get lost now and don't bother us. Come back tomorrow – and don't forget to bring your purse with you, ha-ha-ha!","Don't make me angry, sailor! Do you still remember where the entrance to the cave is? You should go there now, very, very quickly...","Well, now you've crossed the line, mate! Guess I'll have to tear myself away from my affairs and deal with you, bastard!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("So very kind of you, mate...","I see you're quite the joker...","Alright, keep frying your flat cakes, then...","Now we're talking, ha-ha!",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Whoa, good heavens! No need to go hunting for prey - it's already here... Hey, guys - let's shake down this fop, shall we?","No one invited you here, mate... But it's so good that you're here, anyway. Let's see now, just how heavy your purse is!","No one dragged you here by force, heh-heh... But since you're already here, I suppose we'll tickle you a bit to see what falls out of your pockets...");
				link.l1 = LinkRandPhrase("Now I'll make your tongue a bit shorter...","I hope your skills with a sword match your wits, flapjaw!","Well, seems it's time to make a couple more holes in your perishable body...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Whoa, good heavens! No need to go hunting for prey - it's already here... Hey, guys - let's shake down this fop, shall we?","No one invited you here, mate... But it's good that you're here, anyway. Let's see now, just how heavy your purse is!","No one dragged you here by force, he-he... But since you're already here, I suppose we'll tickle you a bit to see what falls out of your pockets...");
			link.l1 = LinkRandPhrase("Now I'll make your tongue a bit shorter...","I hope your skills with a sword match your wits, flapjaw!","Well, seems like it's time to make a couple more holes in your perishable body...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Get lost, mate. There's nothing for you to do here!","Hey, I'm asking you nicely: get lost. You never know what might happen...","Last warning: if you don't get lost right now, you'll regret ever coming here.","That's it, mate, you asked for trouble.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Don't tell me what to do, alright?","And what's so special down there? Just a cave, nothing more...","Oh, come on now...","Ha! Well, let's see who's better, maggot!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Paleface, go away. He will be happy that "+npchar.name+"  kind. The gods take pity on you today.","Get out of my cave before my brothers and I get angry!","Get out, pale-faced dog!","Your luck and life are over, white dog!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Well, thank you, mate, that's very kind of you...","This cave is not yours, and I go where I please.","Take it down a notch, swamp spawn.","Now I'm going to shove those words right back down your throat, animal...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Cursed paleface has come to our campfire! Whoopee! You're done!","Silly paleface, you've come to the jaguar's lair. I'll fry your liver!","Insolent paleface dares to come to my cave? Then he'll never make it out alive!");
				link.l1 = LinkRandPhrase("Now I will tear out your tongue...","Now the world will have a few less cannibals...","Well, seems it's time to make a couple more holes in your perishable body, you red-faced ape.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Foul paleface has come to our cave! Whe-hee! I will cut out your tongue and fry it!","Stupid paleface has come to the jaguar's lair. Brothers, cut down this cursed white cur!","Insolent paleface dares to come to my cave? Then he'll never make it out alive!");
			link.l1 = LinkRandPhrase("I will cut off your bloody head...","Now the world will have a few less cannibals...","Well, prepare to meet your ancestors, redskin. To hell with you!");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
