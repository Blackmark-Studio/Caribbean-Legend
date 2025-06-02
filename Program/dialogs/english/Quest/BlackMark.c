void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

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
		
		case "BM_Contra_1":
			dialog.text = "Who are you, and what the hell are you doing hanging around here?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Easy, mate. I'm just passing by. I'm not going to interfere with your... whatever this is.";
			}
			else
			{
				link.l1 = "Eh? Is this lighthouse yours? Next time, put a sign with your name on one of the palm trees or build a bloody fence.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Get out of here! If you mess up the deal by scaring off a client, I...";
			}
			else
			{
				dialog.text = "Listen, kid, don't make me and my boys call you out to see if your blade is as sharp as your tongue. Just disappear and...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "Well, Frankie, which one is it?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "No... I'll be damned, but I don't recognize any of those mugs.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "What?! Are you sure?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "Do you think I'm blind?! I'm telling you, wha...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "What the hell?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "Who fired?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "Do you take us for fools, scum? Put your guns on the ground, all of you! And you too!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Just hold your temper, officer. It's not us, can't you see? Our guns are right where they were. And don't you touch yours!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "You're giving me orders, you bastard?! Arrest all of them, now!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "Screw you! That's not gonna happen. Boys, to arms!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "Hey, hey, watch it! Someone might get killed if you keep waving that iron around so wildly.";
			link.l1 = "Ha, who?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Me, of course.";
			link.l1 = "What the...? Who the hell are you?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "That's exactly what I'm trying to do. Shall we?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			npchar.MusketerDistance = 10;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "I'm Tommy! Tommy Irons. I guess. Who are you? You're a brave woman, I tell you, walking around like that, hehehe.";
				link.l1 = "Brave, indeed. And I'm not afraid to shut your mouth if I must. It's a hot place, so I dress lightly -not to please you or your kind. The name's Helen MacArthur. My friends might call me Rumba, but you're certainly not one of them. And what that 'I guess' was about?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "I'm Tommy! Tommy Irons. I guess. And you?";
				link.l1 = ""+GetFullName(pchar)+". And what does that 'I guess' mean exactly?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "That means exactly what it means. I lost my memory - got beaten up pretty badly in battle. You know, sometimes you lose it all. I'm lucky, though. I only forgot my name. Lucky for me, I've got this pendant around my neck that says 'Thomas'. But I prefer Tommy. And Irons. I fought in the Ironsides for Cromwell, remember that. But ‘Ironsides' is too bulky. Irons is much better.";
			link.l1 = "I see what's wrong with you, Tommy. So, tell me - what was it? Were you aiming at someone in particular? Did you hit your mark? Or were you just shooting for fun? I wouldn't be surprised.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "I hit it, and I hit it hard! In every way. Remember those fancy pants? He followed my trail and brought soldiers with him. A whole squad, just because I slept with his wife.";
			link.l1 = "You did hit it indeed, heh. I suppose he caught you two in the act?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "Ha! You wouldn't believe it - no. The wench confessed later. Guilty conscience, or maybe she didn't enjoy it as much as I did, hehe. Who knows what goes on in women's heads? I don't really care, ha-ha-ha!";
			link.l1 = ""+GetSexPhrase("Hmm, she's an odd one.","Men... One minute you're trying to figure out what's in our heads, the next you're saying you don't care. But you're right about one thing - what she did was strange. She should've just left and forgotten it like a bad dream. That's exactly what I would do if it came to that.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "Exactly! People say there's something wrong with me. I feel sorry for the soldiers who died. I know it is, I was just a grunt myself once. Didn't I tell you?";
			link.l1 = "Yes, you did. From the Ironsides. Cromwell.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "Oh, yeah? I don't remember if I did or not. Do you know how I ended up in the New World? Shall I tell you?";
			link.l1 = "No, and it wouldn't interest me, Tommy.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "It would, it would. I'll tell you.";
			link.l1 = "All right, to hell with it, just shoot. I mean, go ahead.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "Don't interrupt me, then! Where was I? Right, so I was wounded, see? Got my official resignation because I was on the winning side. But you should've seen the looks on those desk rats' faces! They thought I was faking it, pretending to lose my memory. They kept asking about my family.";
			link.l1 = "Well, what did you tell them?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "What did I tell them? I told them I didn't remember. And I wasn't lying - I never knew them my folks. I was raised by the streets, by laborers and servants in the slums. I joined the Revolution for their sake. Though the ingratitude of people is astonishing - if I'd lost an arm or a leg, they would've been forced to give a hero like me an immediate retirement. And by the way, I almost lost my head, literally!";
			link.l1 = "Well, how did you get to the New World, war hero?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "Do you doubt it? Fighting for the common people - what's not heroic about that? I hope one day sissies like you will know what real freedom is!";
			link.l1 = "Although freedom is a good thing, somehow you made it sound like a threat. Alright, Tommy, go on.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "Aye. I got my resignation after the Revolution was won, and then I realized I couldn't do anything but shoot and punch people in the face. And you can't rejoin the army - they'd laugh at you, especially after I fought so hard for my resignation. Heh, it seems to me that even if I'd really lost an arm or a leg, the desk rats would still have thought I was hiding them somewhere to sew them back on later once I got my exit papers, ha-ha-ha!";
			link.l1 = "That's funny. But you still haven't told me how you ended up here.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Oh, you're such a bore. Didn't they teach you patience, " + GetSexPhrase("youngster","my girl") + "? I had nothing to do back home but shoot ducks and deer, so I went to the New World. I sailed with pirates for some time for fun, and when I got tired of the lawlessness, I became a mercenary.";
			link.l1 = "Not a very original story.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "Maybe you have a better one? You don't need a bodyguard, by any chance? Because you look... weak. I'm worried you won't make it far, hehe. Remember, it's the entourage that makes kings. And a bad retinue can bring them down.";
			link.l1 = "And what kind of " + GetSexPhrase("king","queen") + " would I be with a retinue like you? " + GetSexPhrase("King","Queen") + " of the dung heap?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "No, no! I'm making you a genuine offer, and you...";
			link.l1 = "I haven't received any offer yet. How much are you asking for your services, Tommy?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "Two hundred and fifty doubloons upfront! To make sure I know you're serious and not just a flop. And a monthly fee after that. I think we can make a deal.";
			link.l1 = "And you don't...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... think you've got the nerve? Heh, I won't even argue with you - did you see how I shot that cuckold from the lighthouse? First shot! No bargaining either, if that's what you're thinking. You need to show you can afford a professional like me.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Yes, I can! Two hundred and fifty gold pieces. Here you go.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "You got lucky with that shot. And now you're trying to pad your value with bragging. I can do without a professional like you. It's too much honor and too much money.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "I can't afford it right now, since I don't carry that much in my pockets. Stay here and don't go anywhere - I'll get the gold from the ship and return.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(250);
			
			dialog.text = "You're not as bad as I thought! But you better make sure I don't get bored. It'd be a waste of my talent, wouldn't it? Tommy and " + pchar.name + "! Let's shake up the Caribbean!";
			link.l1 = "Learn to respect the chain of command, Tommy. And secondly, I'm captain to you. Understand?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Heh, I do, Captain Boring, " + GetSexPhrase("sir","miss") + ".";
			link.l1 = "Oh, I'm already starting to regret this...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = 15000;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			pchar.questTemp.IronsItemsBlock = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_SetHP(npchar, 170.0, 170.0);
			
			// Костыли, нужно украсить интерфейс офицера ==>
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			//TakeItemFromCharacter(npchar, "unarmed");
			//GiveItem2Character(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "mushket1");
			//EquipCharacterByItem(npchar, "indian_2");
			// <== Костыли, нужно украсить интерфейс офицера
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
			
			// Продолжение через месяц в джунглях
			SetTimerCondition("BM_FirstJungle_Time", 0, 0, 14, false);
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Well, you're an idiot, young " + GetSexPhrase("man","woman") + "! And completely lacking judgment. I suggest you fix that or you won't last long. Especially on the Archipelago.";
			link.l1 = "I'll manage without you, Tommy. Goodbye.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "Are you serious? A bunch of soldiers just died here, genius! They'll probably send another squad soon. No, I could lock the lighthouse door and organize a defense, but do I want to? Nope.";
			link.l1 = "So what do you suggest?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Meet me at a cave in the jungle. I'll give you a couple of days to earn enough to pay for my services - you know how to hold a blade, maybe you'll manage it.";
			link.l1 = "Are you serious? You'll be like a cornered rat there.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Only if they search for me specifically, with a large detachment. So I think I'll be fine. And now I must go - they'll be here soon. See you later.";
			link.l1 = "Yeah, I've got to go too, just in case.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "Aye, there you are! I was beginning to think you didn't have it in you to make money. Sometimes I think people like you are born with it. And if they're not, they die in poverty without working a day like honest people.";
			link.l1 = "Well, well, Tommy. If you don't want to join my crew, then don't. I see you like nesting in this hole.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "You obviously haven't hidden in pits during the rainy season in Ireland, " + GetSexPhrase("youngster","my girl") + "! But going with you is better than hiding here. Now, about that gold...";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Here's your gold.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "I haven't got it yet. I thought I'd check if you'd run off somewhere else.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(250);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "Now we are talking! What do we do next... Captain?";
			link.l1 = "First of all, let's get out of this damp place, or I'll start sneezing.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Oh, you should try war. I feel almost at home in places like this.";
			link.l1 = "I see, so you got your resignation and forgot about respect and subordination, eh, Tommy? Don't worry, I won't hesitate to teach you again if I have to. Now let's go.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Heh, Tommy Irons never runs away! He keeps his word. Will you keep yours?";
			link.l1 = "Working on it.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "Did you bring the gold?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Here's your gold.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "I haven't got it yet. I thought I'd check if you'd run off somewhere else.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			GiveItem2Character(sld, "blade_42");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			//LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			AddQuestRecord("BlackMark", "5");
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Listen, Captain...";
			link.l1 = "What is it, Tommy?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "Wouldn't you have an extra round of ammo on you? Not just a bullet, but a full-fledged, paper-wrapped cartridge.";
			link.l1 = "Is this another one of your  jokes? I give you bullets and cartridges on a regular basis, whatever you need. And why exactly one cartridge, not a handful?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Why are you taking my request so badly? I ain't asking for bloody pearls, just a cartridge. I even waited until we were out in the jungle so as not to distract you from business in the city. So, got a round?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Yes, I got a round. Here you go. Just don't play a stupid joke on me with that bullet. Understand, Tommy?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "Not at the moment, I don't. It's not like I carry a single cartridge in my pocket, wondering what if Tommy asks for it...?";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Well, that's a good point, and you're quick on the uptake, hehe. But I'm afraid that's where we part ways, then.";
			link.l1 = "Are you serious? You're offended over a bullet? Come on, let's go to the ship and get one there. If you need it so urgently, I'll get you one, ten, whatever you need.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "No. There's nothing special about you, after all. A good captain can always supply his crew with everything they need. So I'll go.";
			link.l1 = "And if we were at sea, ran out of rum, and you wanted more? Would you untie the skiff and sail away? Or jump into the water?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "Ha-ha-ha! I laughed, but at this sad moment even a good joke won't help. Goodbye, Captain Boring.";
			link.l1 = "Well, the hell with you, Tommy. Goodbye.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "Can't promise anything, heh-heh. A good joke keeps things light. But thanks, of course.";
			link.l1 = "All right, let's go, you joker.";
			link.l1.go = "BM_IronsFirstJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_SecondJungle_Time", 0, 0, 14, false);
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "Hey, Captain!";
			link.l1 = "Yeah, Tommy?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "Got another paper cartridge?";
			link.l1 = "What happened to the last one? And what was that joke about the cartridge? I've been waiting two weeks for some stupid joke from you, but nothing.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "Oh, it's gonna be a killer joke, trust me. You'll love it, hehe. Just haven't put it all together yet. So what about the cartridge?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Here you go. I hope I really enjoy your upcoming prank. And where did you put the last round? I give you plenty of those. Or do you keep ammunition for fighting in one place and jokes in another?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "I don't carry ammunition for your stupid jokes, Tommy! You could've asked for a whole batch instead of just one cartridge two weeks ago!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "I did! I thought that whoever claims to be my captain always keeps what his crew needs.";
			link.l1 = "I'm not pretending to be anything, Tommy. I chose to be myself a long time ago. Whoever's comfortable with me, fine. If not, also fine.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Heh, you and I are alike in that respect. But I have certain requirements for my captain. And you no longer fulfill them, young man. That's where we part ways.";
			link.l1 = "Are you serious? Because I didn't have a damn paper cartridge?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "That's out of the question. I usually advise people to do what they like and take what they want out of life. I'd advise you to think more about your people in the future. Goodbye.";
			link.l1 = "And I'd advise you to take care of your head - they've done more damage to it than you realize. Goodbye, Tommy.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "You'll find out. All in good time, hehe.";
			link.l1 = "Oh, I've got a bad feeling about this, Tommy...";
			link.l1.go = "BM_IronsSecondJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_ThirdJungle_Time", 0, 0, 14, false);
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "I've got a question for you, Captain.";
			link.l1 = "Aye, Tommy, what is it?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "You didn't guess? Guessing is a useful skill, hehe. You, me, the jungle... About two weeks ago, we had this conversation. I need another paper cartridge.";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "This is becoming a funny tradition, isn't it? It's been two weeks - Tommy asks for a cartridge. Here you go. How many more do you need for that joke of yours?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "How much longer, Tommy?! How long is this going to go on? Do you Ironsides only get one cartridge before every battle?! I don't have to keep a round on me at all times for your quirks, you know that!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "Actually, as my captain, it's your duty to provide me with everything I need for battles and more.";
			link.l1 = "You're confused, Tommy. It's your duty to obey your captain's orders. I always supply you all with everything - medicine, ammunition, rum. The fact that you don't take what you need on time and then act like a beggar is your fault alone!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "You're so smart - why haven't you achieved anything of notice here so far? I'll tell you why. Because you don't think ahead, and you're never ready for anything. You don't know what you're doing, you bore. I won't recognize such a person as my commander, so goodbye.";
			link.l1 = "And you don't use your head at all! Good riddance, you damned buffoon!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "This one will do, hehe.";
			link.l1 = "You've finally got it together, then? But for what?";
			link.l1.go = "BM_IronsThirdJungle_6";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "I was just playing a joke on you, seeing if you'd turn back into your grumpy self. Hehe. But thanks for the cartridge.";
			link.l1 = "Your jokes are strange, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "That was a joke too. I wasn't collecting them; I was selecting them. Needed a cartridge that was close to perfect. This one will do. Yeah, with this round, the bullet will go far and true. Just like when I blew old Reasley's head off, ha-ha-ha!";
			link.l1 = "Old Reasley, you said... Frankie the Cuckold, wasn't it? The one you shot at the lighthouse? So, you've known each other a long time, then?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "What? Oh, hell, I let that slip. But I don't care - I've never been good at lying or keeping secrets.";
			link.l1 = "I take it the second bullet was meant for someone specific, wasn't it, Tommy?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Right, genius. Well, I know myself and my goals, and I'm not ashamed. That's why I don't care what you think - I'll tell you the whole story, why the hell not.";
			link.l1 = "Well, tell me then. It won't hurt to know what you're up to.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "Well, don't interrupt me, as you usually do. There were two bastards in the company with me - Francis Reasley and Gabriel Callow. Real rats! Even worse than those desk rats who wouldn't give me my resignation, which, you know, wasn't easy to get.";
			link.l1 = "And what did they do? Especially the second one, Callow. Did you sleep with his wife too? And he also sent soldiers after you?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Keep your mouth shut, wouldn't you? Although... I wouldn't mind, hehe. But no. The Royalists attacked us that day. Cavalry, too. There were a lot more of them. Gabe and Frankie ran like scared rabbits. But I stayed with the boys. I was the only one who survived. I've forgotten a lot from my childhood and youth, but not that.";
			link.l1 = "And you want revenge because they ran? Not everyone fights for an idea. Everyone wants to survive. Or almost everyone. Even if someone fights for the Revolution, they might have joined by accident and regretted it.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ha, if I hunted every coward, I'd have to shoot the whole world. Cowards, to hell with them. But they betrayed me. They told everyone I betrayed the Revolution and slaughtered our whole company on the orders of the King's supporters. I lied to you about something, Captain.";
			link.l1 = "What is it? Besides the fact that you lied about Frankie only hunting for you because of what you did with his wife?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "No, no! I didn't lie to you, I just didn't tell you everything. There's a difference. What I lied about was the resignation. There was no resignation. There was a tribunal. And lucky old Tommy - they decided not to hang him but to send him to the quarries in the southern colonies. Barbados, to be exact.";
			link.l1 = "Yeah, that was lucky. How many years did you work there?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "None. Since the earthly tribunal sentenced me because of those rats, the heavenly one upstairs decided to save me. As soon as we crossed into the Archipelago, we felt its atmosphere - our ship was boarded by pirates.";
			link.l1 = "So instead of the quarries and plantations of Barbados, you were sold by pirates into slavery? But you said you never worked in the quarries.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "That's what I said - someone upstairs decided to rescue me. What a rescue it was, hehe! You got it right - the pirates won over those who like to abuse bound and chained men. But it was still a hot fight, as hot as the sun here. And our saviors suffered some casualties. So they offered everyone who wished to join them.";
			link.l1 = "And did you join them? You said you sailed with pirates.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "Hell yeah! Best years of my life. Jack Mills was a captain with a capital C - I hope you'll be like him one day. I sailed on his 'Crane' for about two years until...";
			link.l1 = "... until you got tired of lawlessness, like you said? Why do you say those were the best years of your life?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "Eh... until I heard about those two traitors ending up in the Archipelago too. Aye, I know, I told you I was fed up with high seas piracy and all that. And I have already told you I don't care what you think. That's still true, but I didn't know you well when we first met. Didn't know how you'd react. That's why I said different things.";
			link.l1 = "You're a liar, Tommy! But fine, why did you leave the 'Crane'?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Because Jack was a real leader, so he said he wouldn't make a detour for one man, wait for him, play revenge, and mess with prominent officers of British Navy instead of attacking fat merchant ships.";
			link.l1 = "Prominent officers? Frank was a civilian, I think.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "Eh, he wasn't always one. He was always kind of, you know, murky. And when he tried to set someone up, he was kicked out in disgrace. He tried to sail on a trader, but honest work wasn't his thing. He ended up settling here.";
			link.l1 = "Still wouldn't call him a prominent officer.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "Don't forget about Gabe. He made lieutenant back home. And he got his commission here in Port Royal as captain of the ship, the 'Principio'.";
			link.l1 = "Doesn't sound very English.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "Good point! The ship changed hands like a harbor maiden, so it saw all sorts of things. But she's still seaworthy. And Gabe's a skilled captain, damn him.";
			link.l1 = "And Jack was afraid to deal with him? Is he as good as you say he is?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "Fine, fine! More like he didn't want to waste time on my behalf. Speaking of Jack, I liked a couple of traditions I first saw from him - the planking and handing out black marks. That gave me a funny idea back then.";
			link.l1 = "Black... marks? You mean a black spot, right? And what was it, Tommy? I don't think he would know what to do if you'd handed him a black spot. Is that what happened? You wanted to hand it over, and he attacked you as soon as he saw you, so you ran to the lighthouse, and he took a squad of soldiers with him, telling them you were a pirate?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "I prefer calling it a black mark. It just rings better. A simple black mark wouldn't have made him realize anything. But a black mark made from our silk handkerchief, which was a distinctive feature of our company - that, he'd understand. I slipped it discreetly into his pocket. Then I made sure he saw me heading to the lighthouse. You know the rest.";
			link.l1 = "And the smugglers?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "Wrong place, wrong time. I even felt a little sorry for them. But only a little, hehe.";
			link.l1 = "And for Frankie?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "Who cares now? We've got bigger fish to fry. That leaves Gabe. That's going to be tricky. We need to...";
			link.l1 = "We?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "Well, it's one thing to learn an interesting story, and another to create one yourself! So here's the plan. We'll need to leave Gabe another special black mark - I've got one made already. Then we'll follow his trail to Portland Cove, where we'll deal with him without leaving a trace.";
			link.l1 = "And where are we going to plant it?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ha ha ha, that's what I meant when I said I wished you were more like Jack, Captain. Come on, don't be a bore, I can see your eyes burning!";
			link.l1 = "Rather, I was actually somewhat interested in your story.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "At his house, of course! What kind of question is that? He's settled in Port Royal. So you and I will dock in the cove, so we can leave the island if anything goes wrong.";
			link.l1 = "Do you know where his house is?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "Nope. But it's not hard to find out. We'll ask the drunkards - they'd sell their mother if you bought them a drink or two. Well, what do you think of my plan?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "If he's the captain of a ship bound for Jamaica, he's on patrol all the time in the island's waters. Attacking under a false flag is better than trying anything in the city.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "It's not without flaws, and you're leaving a lot to luck. But overall, it's doable. I'm with you, Tommy. You got rid of one, you can't let the other go, can you?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "I'm not getting involved in your revenge and risking my relationship with England for this adventure where so much depends on chance, Tommy.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "You're a risky one, Captain! I'm starting to like you. But Gabe on the old 'Principio' isn't easy prey - he's much more dangerous than other captains on a ship like that.";
			link.l1 = "What do you think I am, a coward, Tommy? We'll board him ourselves, and you can have a heart-to-heart with him. Give him the black spot just before he's deposed.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Heh, you might not be a coward, but he is, though he's a smart one. He won't attack a soldier or even a pirate bigger than his ship. If he sees anything like that on the horizon, he'll hide under the fort's wing.";
			link.l1 = "Hmm, what about merchant ships?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "Yes, that could work! But again, nothing bigger than a barque or barquentine! Gabe isn't just a coward - he's never been greedy enough to let that outweigh his caution.";
			link.l1 = "Let's hope it works, Tommy. So, a fifth-rate barque or barquentine flying Spanish or Dutch colors. Get ready to meet your old war mate!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "I knew I could count on you! You might even be a better captain than Jack one day. And as for my luck... It got me so far, so I'll rely on it again. Shall we go, then?";
			link.l1 = "Yeah, let's not drag this out too long. The sooner it's over, the better.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Heh, I hoped otherwise, but I expected this - you don't have the guts for this sort of thing, " + GetSexPhrase("youngster","my girl") + ". Any real captain has had at least a few instances like that where he's discreetly dealt with rats. Sometimes even their own rats.";
			link.l1 = "I suppose I'm meant to fall for that provocation and say I've changed my mind and will prove I'm a real captain, eh, Tommy? But I understand your desire for revenge. I'm not going to force you to leave the crew like Jack did. How much time do you need for that? I'll get to Jamaica by then.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ha ha ha, you're growing up. I almost respect you for not falling for it. But you don't have to wait and pick me up afterward - I'll finish this myself. After all, all I ever wanted is someone willing to do something for me as my captain. So goodbye. Take care of England, ha-ha.";
			link.l1 = "You're really strange. But as you wish. Goodbye! And good luck with your revenge, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			AddQuestRecord("BlackMark", "6");
			AddQuestUserData("BlackMark", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("к","чка"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Great, we can retreat quickly from here if the need arises. Take this - give Gabe the note and a black mark once you find out where he lives and when he's home.";
			link.l1 = "Oh, so now you're calling the shots, Tommy. But remember, I'm still your captain. What are you planning to do while I'm in town?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Heh, how could I forget that, Captain Boring? If Gabe spots me on the streets, he'll either raise the alarm or slip off the island, that bloody coward. Don't worry, I'll set up an ambush right here, hehehe.";
			link.l1 = "An ambush, you say. All right, Tommy. Let's give your old war comrade a proper reunion, ha ha ha ha!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "Hic! That's great rum! Hic... Cheers!";
				link.l1 = "Listen, mate, what's the word in town about Captain Gabriel Callow?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "Old Gabe?! Only good things! Why, hic, what's that?";
			link.l1 = "Oh, really? Glad to hear it. Well, there's trouble with a pirate. The Commandant mostly handles land affairs, and I don't want to trouble His Lordship.";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "Then go straight to Gabe, I tell ya! There's not a more honest or brave captain in town than Gabe. Even Colonel Doyley holds him in high regard. He sails a ship that once belonged to Nicolas Sharp himself, can you believe it?";
			link.l1 = " I'm not drunk enough to believe that just yet, mate.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "A-Aye, but you are! It's the Principio! Ring a bell, eh?";
			link.l1 = "A Spanish trophy ship, is it? Why?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "АWhen's the last time you saw a pink with your own eyes, eh? I know what I'm saying, eek!";
			link.l1 = "Well, I don't know if the ship's design is that unusual.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "But it is! No one would command such junk now, with all the new designs around! They stopped building them in shipyards almost t-thirty years ago! Nic sailed her himself, I tell ya.";
			link.l1 = "All right, I'll buy it. So, she is the ship. How hasn't this wreck fallen apart yet?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "Well, she's not as fast as she was in her best years - like me after another drink, ha-ha-ha! But a good captain can still get something out of this old lady. Gabe tries not to put her in the line of fire either.";
			link.l1 = "So why hasn't the ship been renamed? His Majesty's Ship Thrashing, perhaps, under " + sStr + " old regime?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Trad... Trad-trad-tradition, eek! Nic himself never renamed her after fleeing from a Spanish plantation in Cuba. He never wanted to forget the experience - and neither did the Spaniards! Let me tell ya, that battle near the coast of Tendales...";
			if (startHeroType == 4)
			{
				link.l1 = "Tendales, right? Huh, the last time I heard that name was when I was a kid. I didn't think that anyone still knows and remembers about these now abandoned rocks.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "Tendales? Where is that?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "Or was it, eek, Highrock? N-no, definitely not there... Anyway, it doesn't matter! Nic fought and won in that pink, an unbelievable victory against the brig Cuttlefish, sent after him by Desmond Ray Beltrop, Pirate Baron. They spoiled each other's blood for a long time until Nic cut down Desmond himself.";
			if (startHeroType == 4)
			{
				link.l1 = "Wow, that's impressive! Although, you wouldn't expect anything else from Nicholas. Eh, the Sharps and the Beltrops are always together, then apart - apparently, history really repeats itself from time to time.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Impressive. So, how did Sharp part with the ship? Sold her at the shipyard?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "Nah. After that boarding, she started leaking, so Nic abandoned her. Then with the big tide, the pink was brought ashore, right near the town.";
			link.l1 = "Like anyone was interested in that wreck.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "Oh, but the Navy was interested! Practical chaps. They saw a ship under the English flag but with a Spanish name and got interested. Nic died a few years later, but his ship kept going, changing hands, always in a bloody way.";
			link.l1 = "This is just another ghost ship story, while Gabe's captaincy is very real. So, I think I'll go see him. Do you know where he lives?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "Ha-ha! Of course, hic, I know! Everyone knows! Old Gabe lives by the old windmill. Just go around the tavern and look up... hic!";
			link.l1 = "When's he home? Sounds like he's a busy man.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "That's right, mate! He's got a lot to do. He's home only in the evenings, from ten o'clock. And he gets up at six sharp, every day, by himself. Iron discipline!";
			link.l1 = "Thank you very much! I've had enough of these pirate tales for now.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "Are you really... Rumba? I've heard of you... but you've never turned against your own before!";
				link.l1 = "And I haven't. My quarrel isn't with my country. It's with you, Gabe.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "You're not a merchant...";
				link.l1 = "Surprise, Gabe! I was told you were cautious and even cowardly. Greed has clouded your judgment, hasn't it? No merchant would seek out boarding like I did.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "With me? What's the issue? We could have a proper discussion at my place, or even at yours. Like captains, and... What are YOU doing here?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "Indeed. So who are you? No, to hell with you, though. Who is that...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "Thomas, is that you...?";
			link.l1 = "Oh yes, Gabe. And I've come to punish you for what you did to me that day.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "Punish me?! Watch your mouth, Thomas! If any of us deserves punishment, it's you! You said you'd bring reinforcements! And we waited, dying under the bullets and swords of the King's cavalry!";
			link.l1 = "I ran damn hard to bring aid! But I was overtaken by another fucking force! Charles' bloody supporters were everywhere! They had me pinned down, I almost died! Good thing they thought I was dead. But you know what I saw, Gabe?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "What is it, Tom? You willing to make up any story you can to keep this man believing you?!";
			link.l1 = "Heh, that man won't betray me anyway. He's not a rat like some people.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "He has no choice! To attack a ship of the English navy!";
			link.l1 = "Oh, he had a choice from the start. And he chose to help me. You and Frankie had a choice too. You chose to run away so you wouldn't die. And then you came back and found me, half dead. And you told your vile lies at the tribunal. You knew no one would listen to me because I'd been hit on the head and lost my memory!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "No one would have listened to you anyway. You've always been a... banged-up, Thomas.";
			link.l1 = "Oh, so you're not hiding what you did that day. I've got something for you, Gabe. A black mark. But what's the point of giving it to you now that the ship's been commandeered and we're about to spill your guts, hee hee hee hee hee hee...";
			link.l1.go = "BM_IronsClone6"; // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			locCameraTarget(PChar);
			locCameraFollow();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			
			sld = CharacterFromID("IronsClone");
			LAi_SetCheckMinHP(sld, 1, true, "");
			LAi_SetCurHPMax(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "BM_IronsCloneMushket", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "BM_CabinDialog4");
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Well, Gabe's deposed, hehehe. Been meaning to say that for a long time. Too bad you can't hear it anymore, mate. Oh wait! You might - from Hell.";
			link.l1 = "Come on, Tommy. Even if he didn't hear it, he saw and knew that this was exactly your scheme and revenge. And there was nothing he could do about it.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Heh, you're right! Damn right! Thanks for helping me out on this one. You know, I thought you were just some spoiled girl in a flashy outfit who got a ship for a joyride. But you're a damn good captain! I bet you'd give Jack a run for his money.";
			}
			else
			{
				dialog.text = "Heh, you're right! Damn right! Thanks for helping me out on this one. You know, I think you're as good a captain as Jack. Or even better!";
			}
			link.l1 = "Oh, now you're flattering me. Thank you. I guess.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "Not at all. No flattery whatsoever. As you may have noticed, I rarely praise anyone like that. So shut the hell up and be glad I think so highly of you";
			link.l1 = "I wouldn't say I like the way you're presenting it, even though I'm glad you generally think of me as a good captain. But... the chain of command, Tommy, the chain of command.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "Oh, come on! I feel like everything we've been through has brought us closer, Ellie. We could be more than just captain and officer. Admit it - even if only to yourself  you feel it too.";
				link.l1 = "Only in your wildest dreams, Tommy. And it's Helen, not Ellie. But I suppose you can call me Rumba now.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "Oh, come on, you bore! It seems to me that we're no longer just a captain and his officer, but the truest of friends. Don't you think so?!";
				link.l1 = "Heh. Maybe. It's better to be your friend than your enemy. And since etiquette clearly isn't your thing, I guess I'll just have to get used to it.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "I have a... present for you, Captain.";
			link.l1 = "Whoa, look at that! A black spot? You want me to be deposed too, huh, Tommy? You want to be captain yourself? Ha-ha-ha-ha! I thought you said we were mates.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "It's a black MARK, you dickhead. You know, I'm starting to think that as soon as I embroidered the skull and bones on this scarf, it started bringing me luck. I can't explain it. Take it. Also... if you want, you can always borrow my trusty sword and armor... what's left of it, ha-ha! It'll come in handy! You'll go far. And I want to witness it. I don't want you getting killed by a stray bullet.";
			link.l1 = "Thanks, mate! I'll do my best. And you - watch and admire, ha-ha-ha!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Admire, sure, ha-ha-ha. Aye. So, what have you decided to do with this ship? On one hand, it's not much use anymore. On the other hand, there aren't any more like it. I don't think there ever will be again.";
			if (startHeroType == 4) 
			{
				link.l1 = "I haven't decided yet... You know, Tommy, I feel a sort of connection to this ship. I can't explain it. So, let's get this stinking corpse out of here first. If there are no leaks in the hold, I'll probably take this girl for myself.";
			}
			else
			{
				link.l1 = "I don't know, Tommy. I haven't decided yet. In the meantime, let's get rid of Gabe's body. Just in case we do keep the ship.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "Well, you did a pretty good job on that ancient vessel, Captain! And though I wanted to finish Gabe off with my own hands, I will not anger the Creator by belittling this victory.";
			link.l1 = "That would be unnecessary, Tommy. I hope your soul is at peace now.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "I feel like everything we've been through has brought us closer, Ellie. We could be more than just captain and officer. Admit it - even if only to yourself you feel it too.";
				link.l1 = "Only in your wildest dreams, Tommy. And it's Helen, not Ellie. But I suppose you can call me Rumba now if you stop with this flattery.";
			}
			else
			{
				dialog.text = "I've never been so happy in my life! Thanks for helping me through this. You know, I think you're just as good as Jack as a captain. Or even better!";
				link.l1 = "Oh, you flatter me. Thank you for the comparison, too, I guess.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "Not at all. No flattery whatsoever. As you may have noticed by now, I rarely praise anyone like that. So shut up and be glad I think so highly of you.";
				link.l1 = "I wouldn't say I like the way you put it, but I'm glad you generally think of me as a good captain. But... the chain of command, Tommy, the chain of command.";
			}
			else
			{
				dialog.text = "Not at all. No flattery whatsoever. As you may have noticed by now, I rarely praise anyone like that. So shut up and be glad I think so highly of you.";
				link.l1 = "I wouldn't say I like the way you put it, but I'm glad you generally think of me as a good captain. But... the chain of command, Tommy, the chain of command.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "Oh, come on, you bore! It seems to me that you and I are no longer just a captain and his officer, but the truest of friends. Don't you think so?!";
				link.l1 = "Heh. Maybe. It's better to be your friend than your enemy. And since etiquette clearly isn't your thing, I guess I'll just have to get used to it.";
			}
			else
			{
				dialog.text = "Oh, come on, you bore! It seems to me that you and I are no longer just a captain and his officer, but the truest of friends. Don't you think so?!";
				link.l1 = "Heh. Maybe. It's better to be your friend than your enemy. And since etiquette clearly isn't your thing, I guess I'll just have to get used to it.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "I have a... present for you, Captain.";
			}
			else
			{
				dialog.text = "I have a... present for you, Captain.";
			}
			link.l1 = "Whoa, look at that! A black spot? You want me to be deposed too, huh, Tommy? You want to be captain yourself? Ha-ha-ha-ha! I thought you said we were mates.";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "It's a black MARK, you dickhead. You know, I'm starting to think that as soon as I embroidered the skull and bones on this scarf, it started bringing me luck. I can't explain it. Take it. Also... if you want, you can always borrow my trusty sword and armor... what's left of it, ha-ha! It'll come in handy! You'll go far. And I want to witness it. I don't want you getting killed by a stray bullet.";
			link.l1 = "Thanks, mate! I'll do my best. And you - watch and admire, ha-ha-ha!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			notification("Reputation Check Passed", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Who needs to believe in such a thing... I'm sorry, miss. " + TimeGreeting() + ". How can I help you? You look very worried.";
			}
			else
			{
				dialog.text = "What? Who comes by at this late hour? You look rather concerned, sir. What can I do for you?";
			}
			link.l1 = "I apologize for disturbing your rest, Captain Callow. My name is " + GetFullName(pchar) + ", and I come on behalf of one of your old war comrades.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "Which comrade? I had many, both in the Old World and the New.";
			link.l1 = "At first, I only intended to leave something in one of your trunks. Or perhaps on the table, so you'd notice it sooner. It concerns a man from your past. Here, take a look and read it for yourself.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "A black spot? I don't recall any pirates among my comrades. Or did some of the lads fall into that life? Black silk? Really... Oh, Thomas. I'm surprised a man like you has dealings with that scoundrel.";
			link.l1 = "I apologize, but it's not for you to call him a scoundrel. You fled the battlefield and slandered Tom. Perhaps you later repented and became an exemplary officer here in the Archipelago, but that doesn't change the past.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "He told you that? No surprise - he always knew how to find the right man to spin his tales. Thomas had a silver tongue. You don't know him or the real story, or what you're getting into. I can tell you - since I won't sleep now anyway.";
			link.l1 = "It's never a bad idea to listen. Go on, Captain Callow.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "So, Thomas claims I ran and then slandered him? Well, you should know it was the opposite! When the King's cavalry approached, Tom said he was going for reinforcements. So we didn't retreat - we waited. Our whole company was killed! If we hadn't waited for the reinforcements he promised, we could have withdrawn and survived! In the end, it was just me, Frankie, and damn Thomas who lived.";
			link.l1 = "So what you're saying is...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "I'm saying the blood of our boys is on Tom's hands as much as on the Royalists'. He's lucky he was sentenced to penal servitude and not hanging! And now he has the nerve to hold a grudge and challenge me to a duel! He's not worthy of it!";
			link.l1 = "So you won't go? You realize what that means. The laws of honor are written for everyone.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "I do, of course. And that's why I'll go. We need to finish what our republican court couldn't because of Tom's past military honors. And you... you seem like a decent sort. I'd advise you to choose your acquaintances more wisely. Don't get involved with Tom and his kind.";
			link.l1 = "But Thomas is my subordinate now, an officer on my ship. "+GetSexPhrase("I'll keep an eye on him and won't let him dishonor himself further if he survives his encounter with you.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "And what would you do in my place, Captain Callow?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "Eh, if Tom could convince you of his tale, he'll have no trouble doing it again.";
			link.l1 = ""+GetSexPhrase("But by the laws of honor, I can't betray him. I'm","I'm")+" responsible for my men.. I will not be like him. And I'll be more careful and critical of him from now on if he survives.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "It's a tough decision. But I won't try changing your mind. Well, goodbye, "+GetSexPhrase("sir","miss")+" - I still have to prepare to meet Tom.";
			link.l1 = "Goodbye, Captain Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "Let justice be done! Help me bring down Thomas, "+pchar.lastname+". He's a rare scoundrel and a coward, but a great marksman - it won't be easy. But together...";
			link.l1 = "Hmm, help you defeat Thomas? Is there much honor in such a duel? You can settle it yourselves, and I'll stay out of the way.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Knowing him, I doubt I'll get a fair duel. By staying neutral, you're only condoning injustice. Am I right?";
			link.l1 = "It seems you know Tom better than I do, and what he's truly like. You're right - he's already setting up an ambush in Portland Bay, and he's counting on my help - just as you are now.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "Then it's not a duel, but a brawl. But I'm not suggesting we kill Thomas ourselves. We'll arrest him! I'll bring soldiers, and we'll finish what we couldn't in the Old World. If they try to exonerate him again, I'll write to the Colonel or even bring him here for the trial. If Thomas won't lay down his arms, it's his own fault.";
			link.l1 = "That sounds much better.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "Glad to hear it, "+pchar.lastname+"! I realize it may not be easy for you to make such a decision, but I assure you, you've made the right choice. And to ensure it, I'm going to help you with something else.";
			link.l1 = "What is it, Captain Callow?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Here, take this. Not a gift, but a loan - Thomas, as I said, is a very good fighter, and it's better to face him with a proper weapon, not a rusty piece of iron. Colonel Doyley himself gave me this beauty, but for a real fight, I'd always choose a broadsword.";
			link.l1 = "Indeed, it's a splendid rapier. Thank you.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "Don't thank me - I'm lending it to you, not gifting it, remember? Now head to the cove and play your part with our dear Tom, while I gather reinforcements. See you there.";
			link.l1 = "See you there, Captain Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Who are you, miss? You must have the wrong address. I, uh, didn't order any overnight services.";
				link.l1 = "Helen MacArthur. And keep your desires in check, Mr. Callow. I'm a decent girl. Our climate makes me feel hot, even at night. Weren't you ashamed to say that to a strange girl? I've been told about you as an exemplary officer.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "Who are you, and what do you want? I don't like your smirk, sir.";
				link.l1 = "" + GetFullName(pchar) + ". And you're not very hospitable, Mr. Callow.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "Do you greet strangers at this hour differently?";
			link.l1 = "I was told you're not home at other times.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Of course I'm not - I have service, duty, and honest labor, words that seem unknown to you, judging by your appearance.";
			link.l1 = "Such self-confidence! But then, you wouldn't have convinced Colonel Doyley and the others of your honesty otherwise. I don't need anything from you, Gabe, but an old acquaintance of yours does. Here you go.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "Convinced? Gabe? I say! A black spot? So you're a pirate? Wait a minute... black silk... could this be... Oh, I see. Thomas, you bloody bastard, still angry at me and Frank for reporting you, ha ha ha ha!";
			link.l1 = "I say! Tom is an officer on my ship and deserves respect. He's one of the Archipelago's finest marksmen.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "I didn't say he was a bad shot. But you don't know Thomas very well, I see. He's the one who betrayed us all. But I see there's no point arguing with you - you're clearly perfect for each other.";
			link.l1 = "I don't care. Keep your tales for Doyley and all those naive simpletons. If you're as brave and honorable as they say, you'll accept the challenge and come now. So, do you accept it?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "I do, I do. Now get out of my house before I call the guards.";
			link.l1 = "It will be my pleasure, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "Why are you so jumpy? Are you scared, or what?";
				link.l1 = "Anyone would be nervous when they see a man with a musket running at them - I didn't recognize you at first. What are you doing here, Tommy?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "How'd it go? Hey, hey, why are you looking at me like that? You scared me, hehehe.";
				link.l1 = "Who's scaring who! Who's running out like that?! We agreed to meet the guests in the cove!";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Heh, well, maybe. I got tired of waiting - for our dear guests and for you. And I decided this place was better suited for a good ambush. After all, I'm a hunter, not a duelist.";
			link.l1 = "I see.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Aye. So, did you leave my gift at Gabe's house? Took you long enough. I'd be a lot faster if I could get into town. What's got your eyes running, Captain? What's wrong?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Trustworthy) I'm nervous. Gabe's a coward, but he's not stupid. What if a whole platoon of soldiers comes here instead of him? Or they make an approach to the cove and sink our ship first?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				notification("Trustworthy", "Trustworthy");
			}
			else
			{
				link.l2 = "Gabe saw me. I had to run.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				notification("Perk Check Failed", "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Heh, I get it - I'm not entirely sure it'll work myself. This is the first time something this big has ever happened for you, huh? It's alright, it happens. I've got it all worked out. If the soldiers come without Gabe, we just leave. If they come with Gabe, I'll put a bullet between his eyes, and again, we just leave. And if a ship comes to the bay, we run to Maroon Town - they won't dare go there, and then we decide what to do next.";
			link.l1 = "I see you've really thought of everything, Tommy.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Of course I have. Now let's wait for our guest...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ha ha, you're as good a thief as I am a royalist. But why won't you look me in the eye... Captain? You were talking to Gabe, weren't you?";
			link.l1 = "No, what are you talking about? Why would I even talk to him?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Because you're all big talkers. All you do is talk. So, what did our dear Gabe tell you?";
			link.l1 = "Does it matter, Tommy?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Frankly, no. It does if you don't stab me in the back. But it looks like you already have. He talked you into taking his side, didn't he?";
			link.l1 = "No. Not exactly. Put the gun down, Tommy. I promise you, nothing irreparable has to happen. You might work in the quarries, maybe. I'll ask Gabe to show mercy. I'll even ask Colonel Doyley if I have to.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "What a good Samaritan you are. Showing mercy so I can cough up my lungs after years in the quarry? I'm not going back to the prison ships. Never again. And you... I should have known you were just another rat. There's something about the way you look. I'll deal with you first, so Gabe will be easier later.";
			link.l1 = "You leave us no choice!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Well, I see you've already done it, "+GetSexPhrase("sir","miss")+". And I was gathering a squad, thinking the numerical advantage would make Tom think twice and lay down his arms.";
			link.l1 = "And you took your time, Captain Callow.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "I told you, I was gathering men. The best of our garrison. Tom's a veteran soldier after all. But who am I telling this to? Well done, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+". "+GetSexPhrase("I'm proud of you, young man","I must admit, you possess equal parts beauty, intelligence, and skill, young lady")+". As I told you when we first met, you made the right decision. Now justice has been served.";
			link.l1 = "It worked out so well for you. Feeling proud?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Well, I'm not a veteran soldier, but I can fight, as you may have just noticed. But thank you, sir. Justice is not an empty word to me.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "And that is commendable, "+GetSexPhrase("young man","young miss")+". However, there is still one more thing left to do to complete this fine day.";
			link.l1 = "Hmm, and what's that? Tom is already defeated, after all.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "You have something that belongs to me. Give me back my beautiful Italian rapier please. It's not just a toothpick, after all, but a memento - a gift from Colonel Doyley himself.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "Eh... Here's the thing, Captain Callow... the rapier is gone. I lost it. I'm sorry.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "Ah, of course. Please. I didn't intend to steal it. Won't lie though - I'd like to keep it. But here you are, Captain Callow.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "I have a better offer for you, Captain.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "But you just called it a toothpick. Besides, you said you don't even like rapiers. I, on the other hand, deserve a reward.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "Anybody would have wanted to keep this beauty! Thank you for returning her to me. A lot of people would have been stubborn in your place.";
			link.l1 = "It's yours. I suppose we're done here?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "I'm not interested. Just return the rapier, and we'll leave on a good note, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+".";
			link.l1 = "I take it this rapier is dear to you because you like weapons with history, am I right? I have one just like it, and this one is what you'd like to carry instead of keeping in a drawer.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "Is that so? Well, I can't promise we'll come to an agreement, but I'm listening. I'm indeed interested in weapons with history. But this rapier was a gift from the Colonel. That's why it's so precious to me.";
			link.l1 = "You mentioned that you like broadswords. Here. It belonged to our dear Tommy. Imagine what this weapon has been through over the years. And what it will continue to go through with you.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "You're very persuasive, young man! Wielding Thomas's sword... how ironic. Ah, well, take the rapier. I'm not parting with it lightly, mind you.";
			link.l1 = "I'm glad we could come to an agreement. I think that's a goodbye, Captain Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "WHAT?! How could you... How could you lose a whole fucking rapier?! You're an idiot!";
			link.l1 = "Calm down! It's just a rapier. You'd never use it anyway. Tom is dead - isn't that the the only thing that matters now?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "Just a rapier?! It was my treasure! A gift from Colonel Doyley himself! I don't care if I didn't use it!";
			link.l1 = "Then you shouldn't have given it to me, should you?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "You should keep your mouth shut now, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+". We could have parted ways peacefully. But now... now I'd like to teach you a lesson, "+GetSexPhrase("young man","young miss")+".";
			link.l1 = "Cemeteries are filled with teachers like you.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "You do, of course. But you can't just take an officer's personal weapon because you lent him a hand, can you?";
			link.l1 = "I would agree, but you don't use it anyway. It'll just hang on a nail in your room. While with me, it'll find a worthy use. Colonel Doyley isn't going to check if you've misplaced it, is he?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "This is not up for discussion, young man. I told you from the start, it's not a gift. Give me the rapier. Now.";
			link.l1 = ""+GetSexPhrase("I'm not one of your toy soldiers","I am not one of your harbor whores")+", to take orders from you. I'm a ship's captain, just like you. The rapier stays with me, whether you like it or not.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "Looks like Thomas has had quite an effect on you. Then die for it, if you want it so badly.";
			link.l1 = "My thoughts exactly!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Here, take this. I don't need it at all. It will be your memento of the day. Try to be a little less gullible from now on. And don't let any scoundrels like Thomas get you involved in their dirty business.";
			link.l1 = "Heh, are you giving me a black spot, Captain Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "Well, neither of us are pirates, are we, "+pchar.name+"? Let it be a reminder. Take care, the Archipelago needs men like you. "+GetSexPhrase("Perhaps I'd suggest joining the Navy and write a recommendation to Colonel Doyley...","")+"";
			link.l1 = "I regret I cannot accept your offer, Captain.";
			if (startHeroType == 3)
			{
				link.l1 = "Hm. I will give give it a thought. A really good one.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Farewell, sir.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Suit yourself. Well, goodbye, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+". You deserve to carry what's left of the Ironsides. Farewell.";
			link.l1 = "Farewell, sir.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "I don't like your tone, "+GetSexPhrase("mister","miss")+". What's your point?";
			link.l1 = "You've been stalling deliberately, gathering your 'best men'. What for? To apprehend a single man? You should've grabbed a few soldiers patrolling the city and come to my aid at once!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "Bringing cannon fodder?! Tom wasn't just a city guard like them. He had completely different training and experience - he's a bloody Ironclad, just like me! How do you not realize that?";
			link.l1 = "Oh, on the contrary, I do realize it. That's why you and I were here - to cross blades with Tom, allowing the boys to capture him alive. Besides, you're Ironclad, too. Same company even. Were you so afraid to fight him in person?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "How dare you accuse me of cowardice, young "+GetSexPhrase("man","miss")+"! Ask anyone, and they'll tell you in detail what feats I've done for this city.";
			link.l1 = "I'm not finished yet. I'm beginning to wonder if these ‘feats' were done by your own hands. You wanted Tom and me to kill each other so you could take all the glory. You've done that before, haven't you?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "I've had enough of your accusations, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+". You want conflict? You'll get it. Right now.";
			link.l1 = "Truth hurts, doesn't it, Gabe?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "Gabe! It's been so long, so many bleak midwinters! And look at you - still have that same smug look, damn you!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "Thomas! I should be pleased, for today I will finally finish with my own hands what our justice system failed to do for years. And since I'm in good spirits, I allow you to lay down your arms and follow us. You may even be sent back to penal servitude. In that case, I will personally take you there.";
			link.l1 = "Heh, make me! You think a couple of blokes next to you will stop me!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "Who says they're the only ones with me? I'm talking about the person standing next to you right now.";
			link.l1 = "What?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Thomas, Thomas, Thomas... you are, as always, alone in this world. I almost feel sorry for you!";
			link.l1 = "Bloody rats! Bastards!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "What does that mean?! What did he mean by that?!";
			link.l1 = "Tommy, listen...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "That's exactly what I'm doing! Tell me he's lying!";
			link.l1 = "Unfortunately, he's right. Lay down your weapons. And nobody has to die today. I'll put in a good word for you myself so that you won't be hanged. You can even return to an honest life someday.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "That's not for you to decide! And certainly not you! Who needs enemies with a commander like that! Another fucking rat.";
			link.l1 = "Come on, Tommy. There are no clean getaways for people like you.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " A place in your crew, on your ship would be a start, if only you were willing to stand up for your men! But that doesn't matter anymore. Damn you, all of you! I'll gut your cowardly guts out, you little rat. And you, Gabe, I'll try to take you with me...";
			link.l1 = "Wait, Tommy, no!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Congratulations, "+GetSexPhrase("young man","young miss")+"! I'm impressed that you managed to make Thomas feel like everything was going according to his plan - he had a nose for treachery.";
			link.l1 = "Ah, thank you, of course, Captain Callow.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "Is something troubling you, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+"?";
			link.l1 = "Tom... he wasn't just angry that I was on your side. There was genuine despair and incomprehension in his voice, as if...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...as if he was the injured party here. It was to be expected. Remember, Charles, a monster can feel pain. But it doesn't stop being a monster. Many criminals are often sincerely convinced of their rightness and innocence.";
			link.l1 = "I'll try to keep that in mind. I think we're done here, don't you, Captain?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "In general, yes, but there is still one more thing left to do to complete this fine day.";
			link.l1 = "Oh? What is it?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "It took you long enough. So I thought I'd recon a bit. Anyway, I think it's better to ambush them here instead of playing fancy duelists on the beach. I hope you were able to find Gabe's house and leave everything in plain sight?";
			link.l1 = "Of course I did, what do you take me for, an idiot? I'm actually your captain, Tommy. What would that make of you if you served an idiot?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ha-ha-ha-ha, you wouldn't believe how often I've had to deal with crap like that in the service! But in our case, fortunately, that's not the case. All right, then. We're expecting company. Ready?";
			link.l1 = "Well, unless the entire fleet or the garrison of Port Royal shows up here, I'm ready.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "Thomas? It really is you after all...";
			link.l1 = "Of course it is really me, or you were expecting someone else, Gabe? Heh, you look pale, like you've seen a ghost. You're also fatter than you were in Old England.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Now I'm finally convinced it's really you. Rude as always. But that's all right, I'll soon shut your filthy mouth for good, you bastard.";
			link.l1 = "Ha-ha-ha, now we're talking! You know, you've actually disappointed me, Gabe. Again! You clearly needed to bring more men with you even to handle me alone. And there is the two of us! Or was it all they could spare you, you coward?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "Enough! I don't see the point of us talking anymore.";
			link.l1 = "I agree with you on that! " + pchar.name + "! To battle, Captain!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Heh, there you go! Rest in peace, you bastard.";
			link.l1 = "Well, are you satisfied, Tommy? You know, a lot of people only get worse after they get their revenge.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ha, did you read that up somewhere? I never understood such sissies. Bah! Am I satisfied? I am so happy I am about to piss myself! Those bastards were the roots of my biggest misfortunes!";
			link.l1 = "I am happy for you. Is there no one else you need to get revenge on? Am I to expect more paper cartridge jokes from you?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Calm down, Gabe was the last. And about the jokes - don't worry, there won't be any more, at least not as far as you're concerned.";
			link.l1 = "Shall we go back to the ship then?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "We'd be back on her anyway, whether I still have someone to get revenge on or not. Wait a minute, though...";
			link.l1 = "Oh, so it's not over yet...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "It is, it is. There's something I want to tell you. It's something I say to very few people. And I won't say it again. If you laugh at me, I'll be very angry with you.";
			link.l1 = "I promise not to laugh. Anyway, I find your jokes more tense than funny.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Good. So. I'm very grateful that you decided to help me instead of doing what Jack did. You're a true friend, Captain. Thank you. Also... if you want, you can borrow my trusty sword, and my armor... What's left of it, ha-ha!";
			link.l1 = "Well, thank you for saying that. It's not every day you hear something like that from your officers. Come on, mate.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "Aaaaye-aye, Captain?";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "So, Rumba, on whose bones shall we dance tonight?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Yes, Ellie?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "I`m all ears, captain.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Tommy, I'd like to ask you something very serious. There's one... a stone idol of the Redskins. And I'm going to need help. I can only ask my closest friends for it, like you. Newbies or those I don't trust too much yet won't do.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tommy, quit counting the seagulls. Have you tallied all the cargo? Give me a full report with a forecast.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, starting today, I need you to purchase certain goods at the ports.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Tommy, could you please report everything on the ship?";
					Link.l12 = "Tommy, I'm getting quite weary. Could you stock up on certain goods at each port?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Prepare me a report on the condition of the ship and everything on it, Tommy.";
					Link.l12 = "Could you stock up on certain goods during our port calls?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Count everything I have on the ship and report on its overall condition.";
					Link.l12 = "I need you to buy these goods during our calls at each port.";
				}
			}
			//////
			Link.l1 = "Listen carefully to my order!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Someone's for sure. But for now, listen to my orders.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Listen to my order... Tommy. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "That's good, because I have a new order for you, Tommy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Listen to my order, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Nothing, Tommy. At ease.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "We'll see how it goes, Tommy.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "No, Tom, nothing.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "No, nothing.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Nothing, everything's fine.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "I haven't even started on the inventory. You should be grateful I'm counting our profits and losses at all, let alone haggling with those greedy merchants. Inventory's not my business, never had to do it in the army, and I'm not starting now.";
			Link.l1 = "This ain't the army, Tommy. But fine, I get it, I won't force you.";
			if (startHeroType == 4)
			{
				dialog.Text = "I'm no scribe, Ellie. I once knew a fellow, Daniel Crimson, who always claimed to be a scribe, but he'd barely seen the battlefield. Yet, the man was a beast in a fight. That's not me, though, and I won't lie about it. Inventory's just not my thing. I'm already doing our accounts for your sake. Don't push it.";
				Link.l1 = "Alright, Tommy, I won't.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Look, I'm not a scribe. No one has ever required this of common soldiers like me, even in the army. Let's not change that rule.";
				Link.l1 = "Okay, let's not.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "The only thing I can count is how many of our enemies I've shot, ha-ha-ha. And even then I'll lose count. I'm a simple soldier, you know. Who the hell knows about the ship - I've been a landlubber most of my life.";
				Link.l1 = "Looks like I'll have to do it myself.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "What do you take me for, some back-alley quartermaster? We had nothing but contempt for those soft-dicked cowards back home. I may not be nobility, but I've still got my pride.";
			link.l1 = "Alright, alright, if you won't, then you won't.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Listen, I was a simple, honest soldier, not a supply officer, my girl. I don't know much about it and don't want to start learning. It's like asking you to assemble and disassemble a musket on time.";
				Link.l1 = "Well, I could name every part of the standing and running rigging on this ship by heart. But as you wish, Tom. The matter's closed.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "No, I couldn't. Perhaps you forgot or don't know this at all, so I'll explain. For you, this would be a routine task, but in our army, we don't treat supply and rear services very well. Please don't count me among them.";
				Link.l1 = "Ha-ha, good, good.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Look, I respect you, of course, but I'm not going to step over myself and do something I can't do and can't stand. I barely learned to count back then, and you want me to be a true supplier. By the way, we didn't like them - they save on ammunition, water, food and its freshness.";
				Link.l1 = "Hm, okay, let's forget about it.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Oh, an order, huh? You like the drill and all that army things, don't you? I'd rather you just tell me what needs to be done.","You're like a sergeant or something. It doesn't suit you - you're too beautiful for that. You wouldn't have survived a day in the army. But I'm listening.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Apparently, you really are a big fan of uniforms, drills, and all that. But okay, go on.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Which one?";
			}
			
            Link.l1 = ""+GetSexPhrase("Don't go anywhere and don't do anything - just observe, understand? I know you.","Stay right where you are, understand me?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Just stand here, don't go anywhere, and don't touch anything.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Stay here and don't let anyone pass.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Follow me and don't get distracted by anything - stray wives or suddenly appearing old war comrades included.","Stay close, alright? I'd like to have my back covered.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Follow me. I can see you're lost in thought.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Follow me, otherwise you've stopped for some reason.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "I need you to shoot something different this time.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "I need you to fire different ammo in the upcoming fight.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "You'll be using different ammo in the next battle.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Change the type of ammo for your musket.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Change your priority weapon for combat.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "I'd like you to keep a certain distance between you and your enemies.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "I would like you to keep a certain distance from the enemy, Tommy.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Keep a certain distance between yourself and the enemy, Tommy.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("What kind of projectiles? I hope you've carefully crafted each one because who knows where they'll land, hehe.","I'll shoot anything for you. Whatever it is, but never blanks, hehe. ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "I sense something interesting is brewing! Okay, what kind?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "ighting in again... Okay, what kind?";
			}
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "Select ammunition type:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "At the beginning of the fight you will use:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("Even if you get beaten up there, hehe? Got it, I'll just watch.","Trying to turn me into a guard? What if you get beaten up or something?")+"";
            Link.l1 = ""+GetSexPhrase("Hey, watch it! We'll figure something out if it comes to that.","Well, you're not just going to watch, are you? If you think your captain is as wonderful as you say, you'll do something about it.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Even to hit the head? Okay, okay, don't look at me like that, I get it.";
				Link.l1 = "I hope so.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Don't be afraid, no one will pass.";
				Link.l1 = "If you don't miss anyone, of course. But good.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Very funny. But I get your point.","Oh, don't you worry, your back is always under my watchful eye, hehe.")+"";
            Link.l1 = ""+GetSexPhrase("Good.","God, you're insufferable, Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Well, I'm trying to remember something very important. And then I realize that I don't even know what it is, since I lost my memory back then, so nothing will come of it. Okay, let's go.";
				Link.l1 = "Witty, I must say.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Well, I'm standing here because you ordered me to do so yourself earlier. Coming, coming.";
				Link.l1 = "Hm-m, okay, okay.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("What kind of distance? Keep in mind that beyond twenty yards, I won't be able to aim accurately. Unless, of course, you don't need me to actually hit anything, hehe.","As if I'd want to get close to stinking men after being around you. So, what's the distance? But remember, I can't really aim my fire, beyond twenty yards, No one can.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Okay, what distance? But let me remind you that I won't be able to fire accurately and slowly more than twenty meters in the heat of battle.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Okay. What? Remember that further than... well, we're not little anymore, you and I know that.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("You shouldn't try humor.","You still have a lot to learn from me about humor, my girl. But you're making progress!")+"";
				link.l1 = ""+GetSexPhrase("That's odd; I've always been told the opposite.","Very funny, Tommy.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Not your worst joke. Maybe one day you'll even stop being a sourpuss, heh-heh.";
					Link.l1 = "Oh well.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ha-ha-ha, good joke.";
					Link.l1 = "Actually, I just... okay.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Well, then I'll just stand still and hold my ground. If you fight them from too far away, that's your ass on the line, hehe.";
				link.l1 = "Don't be sarcastic; holding your ground is exactly what I want you to do from now.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Heh, you could have just told me to hold the line, and not talk about distances and numbers.";
					Link.l1 = "Well, the main thing is that you understood me.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Got it, I'll hold the line here. Then bring them closer to me so I can shoot.";
					Link.l1 = "Certainly.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Look, I know you'd like every shot I make to be like the one at the lighthouse, but that's not gonna happen. It was a good position there. Calm and steady. You can't replicate that in the heat of battle.";
				link.l1 = "Hmm. Then keep twenty yards away.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "I know you'd like that, all the guys would like that, but like that time, at the lighthouse, it won't work anymore. I'll need a good point, and for no one to get to me, otherwise my nerves will give out.";
					Link.l1 = "Hm-m, okay.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "I've certainly honed my skills since then, but the impossible will remain impossible - in the heat of battle, I could never repeat that shot from the lighthouse. Even with a wheel lock rifle.";
					Link.l1 = "And the impossible is possible, Tommy. But okay, no means no.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Very good. I'll maintain that distance exactly, but if we're fighting inside a tavern or cave, I'll get outside to keep it, hehe.", "I'll try. But decks and confined spaces might dictate their own terms.");
			link.l1 = ""+GetSexPhrase("Not funny, Tommy. Act according to the situation, but no jokes or your stupid pranks.","I know that, Thomas, I'm not dumb.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "I'll try to remember.";
				Link.l1 = "Okay, I'm counting on you.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Yes, captain.";
				Link.l1 = "At ease, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Help with what, steal it? But why? I'm flattered, of course, but you could have said everything a long time ago. Go ahead, spit.";
			link.l1 = "Watch your mouth, huh? Well, damn it - I don't really care how you express yourself, as long as you're on my side. So, that idol. Through it, you can... magically get to another place. Don't look at me like that - I know how it sounds. But I've been through this before and seen it all with my own eyes. It's... safe if you drink one elixir.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "I see you've had a few drinks already. Although no, you seem sober. And they say about me that I always talk nonsense...";
			link.l1 = "Are you coming with me or not? The idol is supposed to take us to an ancient Mayan city, and who knows what awaits us there? You are one of those I believe I can rely on in a difficult moment. And now such a moment has just come.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "I have a bad feeling about all this. If you weren't my captain, I'd say you belong in a mental institution. Next you`ll be telling me God exists.";
			link.l1 = "He does, Tommy. And, as I discovered to my surprise on this Archipelago, not just ours. You could see all the devilry going on here yourself. And you've probably noticed the influence of blessed or cursed trinkets.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Devilry exists at home, too. And it's always had a normal explanation. Sorry, captain, but I won't dance around stone idols with you. Shooting enemies - you`re welcome. I may have lost my memory, but I haven't lost my mind. At least, I think so.";
			link.l1 = "Well, I can't force you. So... as you wish, Tommy.";
			link.l1.go = "tieyasal_5";
			link.l2 = "I doubt you'll have the balls to shoot them, you bold, if you're afraid to go near the idol.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Oh well-well, don't pout. Okay, if you come back after dancing around that idol, then I'll think about it next time.";
			link.l1 = "There may not be a next time. Go back to the ship, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "I'm not afraid, don't get me wrong. But I'm used to listening to my gut feeling, it has never let me down over the years. And now it's telling me that nothing good will come of this. And anyway... Oh well, you'll get offended.";
			link.l1 = "Go ahead and tell me.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Well, if that's the case! I agreed to fight side by side with you. But what if, let's imagine, this thing really works? What if it's cursed? I'm not going to die for anyone, I'm sorry.";
			link.l1 = "Now you've proven yourself, Tommy. I needed the most loyal people now. And now I see that you're not one of them. I'm going there. And you... do whatever you want.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Look at him. He's offended after all.";
			link.l1 = "Shut your mouth. If you find us so disgusting, you don't have to come back to the ship.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Wow! Are you serious? Well, maybe it's for the best. I don't want to be with wet blankets who don't even understand jokes. In that case... farewell, Your Excellency.";
			link.l1 = "Farewell, Tommy. And go to hell.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			RemovePassenger(pchar, npchar);
			DeleteAttribute(npchar, "OfficerImmortal");
			npchar.lifeday = 0;
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
	}
} 