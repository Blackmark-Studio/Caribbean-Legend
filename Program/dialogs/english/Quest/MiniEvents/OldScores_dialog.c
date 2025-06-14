void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "They say there was a brawl in the tavern last night... But who was fighting — damned if I know. My face's still intact. I think.";
				link.l1 = "Looks like there was quite the booze fest here?";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "Oi, "+GetSexPhrase("mate","lass")+", seen my boot anywhere? Some scurvy thief made off with it while I was passed out under the tavern table.";
						link.l1 = "Keep a sharper eye out, or the other one will follow suit.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Word is there was a brawl in the tavern yesterday... Though who was fighting is anyone's guess. My face seems intact. I think.";
						link.l1 = "Perhaps they reckoned your face had seen enough damage already.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "By all the devils in the deep, I had a purse full of gold yesterday! Where in blazes is it now?!";
						link.l1 = "For a true pirate, gold isn't the prize that matters most. Freedom holds far greater value.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "Oh, definitely! The innkeeper had his hands full... hic... And on top of that... someone stole his gin! Not just a bottle, but an entire barrel! And not just any barrel — one you won't find anywhere else in the Caribbean! They say it was brought all the way from Europe. He won't say who it was for, but one thing is clear: if that thing isn’t found soon, the poor guy's in for a hell of a storm!";
			link.l1 = "That's amusing. Well then, take care, you old drunk.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "What else do you want? Can't you see my skull's about to split open? Fuck off.";
					link.l1 = "Perhaps drink less and you might pass for a proper man rather than a sodden wreck.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Leave me be... My head's about to explode!";
					link.l1 = "Remarkable it's still attached to your shoulders at all.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "Curse you to the depths... Leave me in peace, can't you see I'm in no state for conversation!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "Back off! Can't you see I'm at my limit? My fists are itching to connect with someone's jaw.";
			link.l1 = "Settle down, sailor. I'm only looking to hear what transpired in the tavern yesterday.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "Blast and damnation! Are you "+GetSexPhrase("another of that mad serving wench's lovers","a relative")+"? What do you want, may you be swept overboard in a squall? Challenging me to a duel, are you? Or will you draw steel right here and now?";
			if (pchar.sex == "woman")
			{
				link.l1 = "A relative? Hardly that. But you, fellow, don't seem to hold her in particularly high regard?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "A lover? Hardly that. The wench seems to favor quantity over quality in her conquests, wouldn't you say?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "Her affairs concern me not. Just tell me what happened, and I'll leave you be. It was you who drove her to such fury, wasn't it?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;
		
		case "OS_Matros_3_scrit":
			dialog.text = "That hellcat's about as discerning as a starving sailor after months at sea - grab what's closest and sort it out later! She'd been making eyes at me all evening, flirting like a tavern cat prowling for scraps. But the moment I tried to drop anchor in her harbor - she shrieked so loud it sent the fish in the bay diving for the depths!";
			link.l1 = "Perhaps you'd had too much rum and were overly forward in your approach?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "That hellcat's about as discerning as a starving sailor after months at sea - grab what's closest and sort it out later! She'd been making eyes at me all evening, flirting like a tavern cat prowling for scraps. But the moment I tried to drop anchor in her harbor - she shrieked so loud it sent the fish in the bay diving for the depths!";
			link.l1 = "Perhaps you'd had too much rum and were overly forward in your approach?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "I might have been in my cups, but I recall clear as a calm sea what happened there. It wasn't me hunting her - she was circling me like a shark smelling blood. She'd been hovering around me the whole blasted day!";
			if (pchar.sex == "woman")
			{
				link.l1 = "And for such a trifling matter you're ready to brawl with the first person you meet? Or did something else happen that evening?";
			}
			else
			{
				link.l1 = "Listen here, you said 'another lover.' Do you know something about her dalliances?";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "After her screams died down, my shipmates told me I was wasting my time trying to cast lines in her waters. Said she's got some suitor in town who's thick as thieves with our captain.";
			link.l1 = "Intriguing. Did you notice anything else unusual? Perhaps someone approaching the bar counter during the commotion?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "Devil take it all... My head's splitting like a hull on a reef, and here you are with your infernal questions. I didn't see or hear a blasted thing. You'd do better to spare a few pesos than torment a seasoned sailor with this interrogation.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Here's a hundred pesos. Mind you don't drink yourself senseless and fall under that serving girl's spell again, eh?";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "You'll weather without my coin. Otherwise, you'll just get soused and go pestering that waitress again.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hey, Jack! You've got a dockside strumpet in your quarters! Ha-ha! Just feast your eyes on her - quite the fetching little devil! I wonder, has she searched all our chests, or did we interrupt her at the most interesting part?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "Hey, Jack! Look what we've got here - a thieving rat! Ha-ha! Would you look at this scoundrel! Already been rummaging through our sea chests, has he, the sneaking cur?";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\\MiniEvents\\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "A daring little hen. Breaking into Jack Veils' den - not many would have the nerve. So what brings you here, sweetheart? Thought you might entertain us, did you?";
				link.l1 = "Entertain you? Ha! You're quite the dreamers, gentlemen. I'm here to retrieve what you stole. Did you honestly believe your pathetic little performance would escape notice?";
			}
			else
			{
				dialog.text = "A bold worm indeed. Breaking into Jack Veils' house isn't something many would dare attempt. Well now, what business do you have here?";
				link.l1 = "Let's just say I'm recovering stolen property. Or did you gentlemen truly believe your pitiful little charade would go undetected?";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "Pathetic performance?! May the devil roast me, I'll flay you alive and use your skin for sails! Ha-ha! Though perhaps first we might... amuse ourselves with you a bit?";
				link.l1 = "I see you're eager to meet your maker? Very well, I won't keep you waiting - have at you, you filthy bastards!";
			}
			else
			{
				dialog.text = "Pitiful charade? May the devil take me, I'll strip the hide from your back and use it for sail cloth! Enough talk - your time has come, you miserable dog!";
				link.l1 = "If that's how you want it, then have at you, villains!";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", where's my gin?! If you don't have it, I'll personally send you to feed the fishes at the bottom of the harbor!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "I've just delivered it myself. Here it is.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("You gave the barrel of gin", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Good to see my faith in you wasn't misplaced, "+sld.name+". Come by my quarters tomorrow for your doubloons.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "Zaharia_4":
			DialogExit();
			
			//ChangeShowIntarface();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;
		
		case "Tavern_1":
			dialog.text = "Captain, about that plaque...";
			link.l1 = "What plaque? Ah, that one... I daresay I've no need for such honors. Don't trouble yourself on my account.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "I can offer something far better! From this day forward, you'll always have free lodging and drinks on the house in my tavern! A person of your caliber most certainly deserves as much!";
			link.l1 = "Now that's more to my liking! Such privileges I can heartily appreciate! Until our paths cross again, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}