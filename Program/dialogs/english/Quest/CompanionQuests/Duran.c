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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Greetings in my home, gentlemen. What can I do for you?";
			link.l1 = "Levasseur sends his regards, monsieur.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "So that's how it is... Alicia! Leave us, please. These gentlemen have business with me.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "But...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "I love you, darling. Go on then!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
			sld = CharacterFromID("SKD_Anri");
			CharacterTurnByLoc(sld, "barmen", "stay");
			
			sld = CharacterFromID("SKD_Alisia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
			sld.location = "None";
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "Wondrous works, O Lord! It was worth losing everything to find the love of your life at the end of the world! Gentlemen, I'm all yours. I don't suppose we'll be able to make a deal?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "No, and don't try to ask for mercy either.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "It is not fitting for a Knight of the Order to ask for mercy.";
			link.l1 = "A former knight, though.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "The bureaucrats wouldn't have all the ink in the world to take that title away from me.";
			link.l1 = "In that case, prove it.  But, first, satisfy my curiosity: Are you a traitor to the Crown? Otherwise, I don't understand why Levasseur wanted your life so badly.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "I am faithful to my oath, monsieur, so do not begrudge me that. I will only say that a traitor to the Crown has sent me to eliminate another traitor. And he'll do it again and again until a Brother more capable than me succeeds. Enough talk. Gentlemen, to battle!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			EndQuestMovie();
			
			sld = CharacterFromID("Duran");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "Ah-ah! Oh, thank you, Cap. Tough devil he was. There's no way I could have beaten him myself.";
			link.l1 = "Somehow I don't feel very happy about this victory. I suppose we're done here?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Not quite, first we have to clean up and eliminate the girl who ran away so quickly to the second floor.";
			link.l1 = "What?! Stand down! Have you lost your mind, Claude? I'm not a butcher!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "You don't have to do anything, Cap. Besides, it's all your fault: you shouldn't have mentioned Levasseur to her.";
			link.l1 = "That's nonsense and you know it. And if you dare to give me another inarticulate rebuke, you won't get away with it.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "Heh! My bad, Captain. True, Levasseur's orders clearly stated to take out not only the knight but all his companions. All of them, you understand? These people are not to be trifled with and their demands must be taken seriously. Don't stop me from doing my job, Cap. One last dirty job and then I'm with you to the end, I swear!";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Trustworthy) (Honor) You once said I was destined to fly high, and you were happy to contribute to that.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("Perk Check Failed", "Trustworthy");
			}
			link.l2 = "To hell with you! Do your dirty work. I accept your oath, and you'd better take it deadly seriously. Do we understand each other?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "Not at this price, Claude. I won't let you kill that girl.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "Heh! I guess we were destined to kill each other, eh, Cap?";
			link.l1 = "I guess so. Let's pick up where we left off at Tortuga, shall we?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			
			RemovePassenger(pchar, npchar);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "Aye aye, Captain!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			sld = CharacterFromID("Duran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortRoyal_town", true);
			
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "It's done, Cap. She did surprise me...";
			link.l1 = "I don't want to hear about it. I kept my word. Now it's your turn.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "Gold is one thing, but putting your own skin on the line for a simple mercenary is worth much more. I'm with you to the end, Captain.";
			link.l1 = "In that case, we're done here.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Aye aye.";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_LocationDisableOfficersGen("PortRoyal_town", false);
			chrDisableReloadToLocation = false;
			AddQuestRecord("TheFormerKnight", "3");
			CloseQuestHeader("TheFormerKnight");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			pchar.questTemp.SKD_DevushkaUbita = true;
			sld.reputation = sti(sld.reputation) - 15;
			OfficersFollow();
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "I did. What's your point, Cap?";
			link.l1 = "Prove to me that those words were not idle chatter. You want to earn a place on my team? A share in future spoils? Follow my orders. Don't touch the girl. Why? Because if you don't, you'll be a butcher forever, and I don't have room for people like that.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "This is the second time you and I are about to fight to the death, Cap\nAnd once again, you win thanks to your gift for scratching your tongue! Ha ha! You said it! Well, to hell with the girl. I'm an animal after all. Permission to join the crew?";
			link.l1 = "Welcome, Claude. For real this time.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "Aye, aye, Captain!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddQuestRecord("TheFormerKnight", "2");
			CloseQuestHeader("TheFormerKnight");
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			sld.reputation = 60;
			OfficersFollow();
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "Something came up, Cap.";
			Link.l1 = "Let me guess: you're going to threaten to resign and demand a raise again?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "Heh! Not this time... Don't worry, Captain, as long as you pay, I'm all yours... within reason, of course. It's the only way our brother mercenaries survive. And even the best of us are paid a pittance.";
			link.l1 = "Why don't we just get right down to business?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "Remember that bitch from Tortuga?";
			link.l1 = "Marceline? The governor's wife? You don't forget a woman like that.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "I didn't come to Levasseur's house by accident. I had dealings with that scoundrel and heretic.";
			link.l1 = "It's rather strange of you to speak so disparagingly of the powerful, Claude.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "Huh? Heh! Levasseur is the devil! He's far worse than even the pirates who feed off him!";
			link.l1 = "You yourself just said you did business with him. Isn't that a little hypocritical of you?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "I'm no angel, Cap, and I make my living by killing whoever I'm told to. That's why you value me so much, isn't it? But even men like me get chills hearing rumors about what they do to women on Tortuga in Levasseur's lairs!";
			link.l1 = "Rumors don't interest me. This man is a nobleman and a servant of the King, and he deserves respect.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "So you robbed this King's servant and screwed his wife? Heh! Suit yourself, Cap. Let's cut to the chase. His Excellency ordered me to find and kill a man. A fairly routine assignment, even if it doesn't often come from such a high person, and even in person.";
			link.l1 = "And what do you want? To release you so you could keep your word and kill this man?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "I want you to help me do it, Cap. When things got bad for me on Tortuga, I agreed to join your service, but I won't rest until I get the job done. Levasseur would kill me if he found out. Besides, it's unprofessional to leave a job unfinished.";
			link.l1 = "Is it professional to have affairs with a client's wife? It is very strange to hear such a request from you, especially if we remember the beginning of our conversation, where you quite accurately described the essence of our relationship. Blood for gold, eh?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "If you help me, you won't just get my sword, you'll get my loyalty. I can see at once that you're destined to fly high, Cap. I'd be happy to help make that happen.";
			link.l1 = "I admit, I'd rather have a man of your abilities watching my back. Where can we find this target of yours?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "Your saber will suffice for now. I'm not an assassin. At ease, officer!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Aye, aye, Cap. It was worth asking anyway.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 10;
			Return_DurandOfficer();
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "Heh! That's the problem, Cap. All I know is he's a former knight of the Order of Malta on the run somewhere in English territory. A man of noble birth, so he won't be living in a hovel.";
			link.l1 = "Knight of the Order?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "A former knight. Yeah, and I've already regretted taking this job a thousand times. Knights fight like devils, so I guarantee you a serious test of your swording skills.";
			link.l1 = "I don't like it, but let's give it a try. So: not a poor man, a nobleman and hiding with the English? Levasseur didn't say why he should be dealt with?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "Of course he won't! But it's obviously political, otherwise he'd have sent soldiers.";
			link.l1 = "I'll try, but I can't promise anything.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Thanks, Cap.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			SetQuestHeader("TheFormerKnight");
			AddQuestRecord("TheFormerKnight", "1");
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 15;
			Return_DurandOfficer();
			PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
			PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
			pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
		break;
		
	}
} 
