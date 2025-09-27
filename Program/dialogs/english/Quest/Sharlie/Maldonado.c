// Алонсо де Мальдонадо
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
			dialog.text = "Is there something you need?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "Stop, Captain "+GetFullName(pchar)+"...";
			link.l1 = "Somehow I'm not even surprised by the Spanish soldiers' presence here... I suppose I've just got used to someone always being on my tail. What are you looking for on this godforsaken island, Castilian? Hoping for a quick way to kick up your heels?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "My name is Alonso de Maldonado. That might not mean anything to you, but Diego de Montoya might ring a few bells. He was my best friend. He saved my life, and now his blood is on your hands.";
			link.l1 = "I take it you've followed me here to seek revenge?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "I'm not just looking for revenge. As far as I understand, you have Kukulcán's mask?";
			link.l1 = "Well, I'll be damned! Another treasure hunter! Come for some unfinished business started by Don Diego?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "I'm not interested in treasures. I've seen the riches in Tayasal. Miguel Dichoso wasn't able to haul out much more than a morsel. The mask is what I want.";
			link.l1 = "You've been to Tayasal? That's hard to believe. As far as I recall, Dichoso was the one and only survivor of the expedition.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "I went to Tayasal twenty years before Dichoso ever arrived. The same time that mad sorcerer Kanek used that despicable human sacrifice ritual to hide the mask on this island.";
			link.l1 = "I can't believe what I'm hearing! You were part of the same band of conquistadors who were brought there to be sacrificed when the Guardian of Truth was created? You're all dead!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "Not all of us. I survived.";
			link.l1 = "Why did the Itza decide to spare you? What makes you so different?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "You wouldn't understand. Hell, I didn't understand it either. No one spared me. I remember it like it was yesterday... Right after that savage took a dagger and sliced a patch of skin from Casco's back before putting him to death and starting to howl like a maniac, I think I got sucked into the idol. I woke up far away from Tayasal twenty years later in what felt like a mere moment!";
			link.l1 = "A space-time funnel... God damn it, everything Ksatl Cha said was spot on! How did you find out about the mask? What do you need it for?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "I must stop the spawn of hell, summoned by a mad Indian sorcerer. This abomination seeks to turn our world into a bonfire!";
			link.l1 = "Hmm... You've spoken to Father Vincento, haven't you? The Inquisitor is running with the hare and hunting with the hounds. Surprise, surprise. Has he sent you to track me down for a battle royale? Well done! You've completed your mission, Don Alonso!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "The Lord strengthens my hand in battle against evil. I will return to Tayasal and use the mask to seal the gates forever. And no demon in human form will ever cross into our world.";
			link.l1 = "There's just one little problem with your plan, Don Alonso. The demon is ALREADY among us. All we need to do is not let him LEAVE through these gates. He won't be able to do that as long as you keep the mask away from him.  ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "It'll take more than that. Whoever of us is right, one thing is for sure: the gates must be closed forever. And there's only one way to do that: destroy the mask on the altar at Tayasal. By doing so, the demon will be stripped of all its power.";
			link.l1 = "Hm. I agree that it's our best bet... How are you planning to get to Tayasal? Do you know the way there?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "The easy path we used back then no longer exists. The roads are buried under stones and lost in the jungles. There is another way to the city, but it's long and dangerous. The path starts at the northernmost bay of Yucatan.\nWith the help of Father Vincento and Don Ramon de Mendoza, I will gather a squad of elite soldiers and we will fight our way through the selva, guarded by the Itza savages. It won't be easy, but God will grant us strength and courage for our fight in the name of our faith.";
			link.l1 = "Don Alonso, my aspirations happen to coincide with yours. Isn't it time we put our grudges aside for a moment and join forces? Together we will have a better chance of completing this crusade successfully.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "I am a Spanish soldier. I do not form alliances with heretics, nor do I make deals with Frenchmen. Besides, I've already declared my vendetta against you for Don Diego. A life for a life!";
			link.l1 = "You're as stubborn as an ox, Don Alonso! There you stand, preaching that the world is threatened by a great evil, and yet you refuse my help in succeeding at such an astronomical task!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "I make the decisions now, not Father Vincento! Say your prayers and prepare to die, French captain!..";
			link.l1 = "Oh, I've heard that so many times in the past few months! En garde, hard-headed caballero!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
