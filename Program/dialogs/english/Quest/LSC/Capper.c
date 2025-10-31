// Чад Каппер - боцман Акулы и тюремщик
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "Well, well... So you are the mysterious thief? Hmm... you don't look like a common pilferer.";
			link.l1 = "Sir, you're mistaken. I am a newcomer here, so how could I know that the cargo hold where your people caught me was your property?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "Oh really? Nice try, pal... Where did you come here from, then?";
			link.l1 = "From the Spanish Main, through an Indian idol... I don't quite know how to explain...";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "Statue? Ha-ha! You're a funny lad, aren't you...? Let me take a crack at it: you swam through the hole in the ship's hull to sneak into our storehouse. But how come I don't recognize your face? I know all the Rivados...";
			link.l1 = "Rivados? I've no idea what you're talking about! Listen, I came here about an hour ago--";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "Don't shout, I'm not deaf. No, as fucking hilarious as you are, I think I'll leave you to stew for a bit. Maybe you'll change your tune after the rats chew your toes off.";
			link.l1 = "I know nothing of these Rivados! My name is Charles de Maure!";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "Hm... maybe you are telling the truth... the Rivados aren't in the habit of working with white men. Answer me plainly... are you one of them?";
			link.l1 = "I swear to you, I've never heard the name before! I'm not working with anyone!";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "Really? Fine. Prove it. Go downstairs, there's a Rivados sitting in a cage. He's a dangerous wizard. Kill him, and I'll be convinced.\nI'll also forget about your little trespass into our warehouse. So, what'll it be? Don't be scared, the wizard is unarmed and weak. Well... he might turn you to dust with a spell, he-he...";
			link.l1 = "If you'd seen what I've seen, you wouldn't be joking--";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "All right, enough! Are you doing this or not? If so, then take this machete and cut down the wizard. Otherwise you'll die in the depths of Tartarus. Understood?";
			link.l1 = "... give me the machete.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "Good boy. Now, go and kill the Negro voodoo man. His cage is unlocked. Don't try anything stupid now - we wont hesitate to finish you if you as much as think of escaping. Now go!";
			link.l1 = "Afraid I'll gut you lads with this rusty piece of crap?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "My patience is running out, pal. Head to the cargo hold and do as you're told!";
			link.l1 = "All right, all right, I'm going...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "You're trying my patience, jackass! You do not want to irritate me...";
			link.l1 = "F, fine, relax.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "Have you killed the Negro? Good... I'm glad. You've proven that you're not Rivados.";
			link.l1 = "Am I finally going to be released from this damn tub? I need to see Shark Dodson immediately.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "You'll see him... on the road to hell.";
			link.l1 = "... fuck.";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Ha! Look at this. What're you doing in my prison?";
			link.l1 = "Your name is Chad Kapper, right? I'm "+GetFullName(pchar)+", I'm here on behalf of Shark Dodson. He gave me the keys.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "The Admiral sent you? Hmph. Are you his new errand boy?";
			link.l1 = "Mind your tongue, sir... or you'll lose it. I'm no one's errand boy.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Ha-ha! I like you, pal. Forget I said anything... So, what's your business here?";
			link.l1 = "Shark's ordered Chimiset be freed.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "The Rivados voodoo man? Hm, that's strange... I'm really surprised to hear that...";
			link.l1 = "Shark wants to make peace with the Rivados.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "A-ah, I see... Fine. I'll send a man to Rivados; they can come and collect their wizard.";
			link.l1 = "Why can't you just release him?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Sure I could... if I wanted to get him killed. Chimiset's known around here. His life will be forfeit once he sets foot on the deck of the Esmeralda - the territory of his enemies, the Narwhals.\nThere's no other way to leave the Tartarus, and we can't make the old man swim around the island! And if anything happens to him, the Rivados will blame us - me, in particular!\nI don't want that kind of trouble, so I'll release him only if his own clan takes responsibility for his safety. You want to speak with Chimiset yourself? He's a colourful character...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "I've spoken with him already. He is indeed strange... Well, I have to go. Goodbye, Chad.";
			else link.l1 = "I intend to. I'll see him now.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "I'll send a courier to the Rivados and they'll come collect their voodoo man. Don't worry, pal, you can go.";
			link.l1 = "All right.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "... must've opened the barrel, already, I'm sure. It's his favorite whiskey: Bushmills. It'll all be over soon, I put enough arsenic in that cask to kill an elephant...";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "Hmm? Damn it, what are you doing here?! Fuck off!";
			link.l1 = "I'd been looking for you, poisoner. Odd, I don't see the Cyclops... You wanted to take Shark's position, right?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "Ha-ha, Shark's probably already dead! And you'll soon join him, spy!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_2":
			dialog.text = "... this is going to be a hell of a drink. Shark's been dreaming of this whiskey so long, he'll down it in a single draught. Where's the arsenic? We'll use two bottles, just to be sure... then our friend Fazio can deliver this barrel to the Admiral as a present from tje Narwhals, ha-ha!\nAm I right, dear Giuseppe? Chin up, lad; you do this right, and you've got nothing to worry abou-- Ah! We have company, boys! What do you want, jackass? This is a private get-together.";
			link.l1 = "Your plan has failed, Kapper. I know what you and your friend Marcello are going to do. Toss the arsenic! You'll not poison Shark!";
			link.l1.go = "Aeva_attack_3";
		break;
		
		case "Aeva_attack_3":
			dialog.text = "Ah, shit. All right... you die first, then Shark! To arms, lads!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
