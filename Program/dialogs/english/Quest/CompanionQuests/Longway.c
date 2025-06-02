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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "I apologize for intruding on your quarters, Senor Captain, but this is very important.";
			link.l1 = "I hope it is, Alonso. If every one of you starts barging in here like it's their own space, we'll have a problem. So, what's going on?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "We found your locker had been rummaged through.";
			link.l1 = "What?! Hold on... How did you figure that out? And what were you all doing in my cabin?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "We clean your quarters from time to time when you're out - either in town or resting on the bunks. You never noticed? Or did you just forget?";
			link.l1 = "Oh, that's right. Well, you can go now.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Captain Charles, look! Someone was digging through your big drawer.";
			link.l1 = "What? When did you notice this? Do you know who it was?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "Not long ago, when I was coming to see you. The spirits are silent about who it might be.";
			link.l1 = "That's a nice touch, Tichingitu. Now if you'll excuse me, I need to check if anything is missing.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "Hey, Captain, what are you looking at? Someone's been going through your stuff. Even I noticed.";
			link.l1 = "Wasn't it you? After all, I don't pay you as generously as Francois.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Heh, if I were the thief, I wouldn't tell you, would I? I'd take the valuables and clean up after myself. This mess isn't my style.";
			link.l1 = "I hate to admit it, but you're right. Well, Claude, save your barbs for later. I have to check what the thief took.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Captain, I noticed today that someone had rummaged through your locker. Didn't you notice?";
			link.l1 = "What? I'm not constantly checking the locker, Folke, and I'm not even in the cabin all the time. Tell me honestly - was it you? Did you mess up again and take out more bank loans the last time we were on land?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "Not at all, Captain. I don't have anything of yours in my pockets or my locker. And I never will.";
			link.l1 = "I certainly hope not. You can go - I'll check what's missing.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			
			if (npchar.id == "Tichingitu")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				npchar.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (npchar.id == "Duran" || npchar.id == "Folke")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Enc_Officer_dialog.c";
				npchar.Dialog.CurrentNode = "hired";
			}
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "loc2", "PZ_OsmatrivaemSunduk", -1);
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Charles de Maure, right?";
			link.l1 = "From the look on your face, I'd say you already know the answer. So, what do you want?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "Your head.";
			link.l1 = "Fascinating! I must say, I like how this conversation is starting. But before we go any further, could you at least tell me who I've wronged? Maybe we can negotiate.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "We're not amateurs, Monsieur de Maure. Even if we told you, it wouldn't help you - our employer has already left the Archipelago. You can't harm them or offer an apology. We've been paid, and now it's time to hold up our end of the bargain.";
			link.l1 = "If you've already been paid, why spill more blood?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "We're not amateurs. We value our reputation.";
			link.l1 = "I'm afraid you won't be able to live up to it this time.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "We'll see about that. Search his corpse when we're done! Burn anything you find!";
			link.l1 = "Burn what?..";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "What the masked man said... Could it be...?";
			link.l1 = "What is it, Longway? It's not the first time bounty hunters have come after me, but you seem unusually concerned.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Longway thinks he knows who sent these men after you, Lord Captain.";
			link.l1 = "Something I should be aware of?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "This is Lord Rodenburg's way - eliminating those who've helped him but know too much.";
			link.l1 = "Really... That masked man did say his employer recently left the Archipelago. That's exactly what Lucas was planning! Do you think we should expect more attacks?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "It's wise to be prepared for anything, Lord Captain.";
			link.l1 = "Wise words. We will be. But what was Lucas after? What did he think I had? Any ideas, Longway?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "Mm-mm, no, Longway has no idea what it might be.";
			link.l1 = "That's a shame. But alright, let's get out of here.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			Return_LongwayOfficer();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Lord Captain, Longway wishes to speak with you. It's of great importance.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "What is it, Longway? Are you worried Lucas's way of saying goodbye, or have you discovered something new?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "Sure! What's on your mind?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "Unfortunately, no.";
			link.l1 = "Then what is it, Longway?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Longway can't say. But... he wishes to ask for permission to leave.";
			link.l1 = "Leave? Like, for good? Why, Longway? As your captain, I have a right to know the reason.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "That's true, Lord Captain. But Longway is neither a laborer nor a servant. He came to help of his own free will, and he can leave the same way. It won't be forever - there is an important matter to attend to. Longway hopes to return once it is done.";
			link.l1 = "What is this matter? Tell me - if not as your captain, then as someone who has been through a lot with you.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "All Longway can say is that he made a vow - long ago. The time has come to fulfill it. Otherwise... there is no point in Longway's life.";
			link.l1 = "You're right, Longway - you're not a prisoner, and I'm not a jailer. You're free to go. Godspeed.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "You can go, but at least tell me where you're heading. I could help without asking too many questions.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "I have an important task as well - to save my brother. For that, I need every man, including you, Longway. We can't do it without you.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "Don't try to play on my pity or sense of duty. I understand perfectly. Have you ever taken a vow, Lord Captain?";
			link.l1 = "Of course I have. So tell me everything as it is, and my men and I will certainly help you.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Longway can't. Just... can't. It's a great mystery, and not even mine to share.";
			link.l1 = "That's too bad. I thought there was trust between us. You're not leaving the ship - I have all the officers on my side now.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "You're right, Longway - you're not a prisoner, and I'm not a jailer. You're free to go. Godspeed.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "You can't do that!";
			link.l1 = "Unfortunately, I can, Longway. Now get back to your duties.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "I didn't think you'd let me go so easily. Thank you, Lord Captain.";
			link.l1 = "Ah, it's nothing. But tell me - where can I find you once your business is finished?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Longway really can't say, no matter how much he wishes he could. But he appreciates the Lord Captain's willingness to help.";
			link.l1 = "So be it. Where should I look for you once you've fulfilled your vow?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "I expect to finish my business in a month. After that, Longway will wait for you for another week in the tavern in Basse-Terre.";
			link.l1 = "Well, whatever you say, my friend. It's not goodbye. See you in Basse-Terre.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "Well, hello, Captain.";
			link.l1 = "I don't like your smirk, sir.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "I am devastated. I came to tell you that you are finally free. But if you want to stay longer in this luxurious cabin, you're welcome to do so.";
			link.l1 = "Not at all. So, Longway's been found? Where is he? In one of the cells?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "In another world more like it - he wouldn't talk to any of us and went straight into battle.";
			link.l1 = "Damn it! You could have just captured him.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Some people are much easier to kill than to capture, don't you know? You should be glad we're not holding anything against you - your Chinaman caused another massacre, and we needed several more units with marksmen to deal with him.";
			link.l1 = "Yes, indeed. Thank you for that.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "Speaking of which, since he was your friend, we found some papers on him. We didn't understand what they were - you'd probably know better. There was some gibberish written on the parts not covered in blood.";
			link.l1 = "That's... Shit. Thank you for returning them. Goodbye, officer.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Come with us, the Commandant wishes to speak to you.";
			link.l1 = "I take it this has to do with my search for the Chinaman?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "You'll see for yourself, monsieur.";
			link.l1 = "Am I accused of anything?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "Not at all. No one is trying to arrest or detain you. For now. When I said the Commandant wishes to speak to you, I meant exactly that.";
			link.l1 = "Oh, well...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "Got any ideas? This yellow-skinned man is deadly dangerous. We're not the first squad sent here. Orders are orders, but I don't want to die stupidly by going in without a solid plan.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "He's all alone in there, and I'm with you. I'll handle him - you guys focus on covering me. We'll manage.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "I have one. You're all going to die-right here.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "Don't worry, we're just going to talk to him.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "I'm sorry, but you're all going to die today. And it won't be at the hands of a Chinese man.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "So you're not a bounty hunter... But even if you are, you're a friend of that damn Chinaman!";
				link.l1 = "That's right. I'd have to get rid of you anyway - no point in delaying the inevitable.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "What do you mean?! You promised to help!";
				link.l1 = "I think you wouldn't have given us a peaceful way out anyway. It's nothing personal.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "I'd like to believe that.";
				link.l1 = "I've faced worse. One Chinese man won't be the end of us. Let's go, boys!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "What if the conversation doesn't go as planned?";
				link.l1 = "I'd hate that, but then I'll have to defend myself. Let's go.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "Lord Captain?! Longway can't believe you're with them!";
			link.l1 = "No, Longway, I'm just here to talk! It's not what you think!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "Then you'd have come alone. You're trying to lower my guard so you can attack me with the help of these soldiers!";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "If I could, I would. I'm the only reason they haven't attacked you yet. Calm down, and let's talk, alright?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "Cut the crap! If I wanted to, I would have killed you already. Lay down your arms, and we'll talk. That's an order from your captain.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Aye. Longway trusts you, Lord Captain.";
			link.l1 = "There, that's better. Now, tell me...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Monsieur, what's going on? What is this... touching reunion? You were supposed to help us eliminate that Chinese savage, weren't you?";
				link.l1 = "I am. I'm taking him with me, and all this killing will stop. You'll tell the commandant we killed him together. Deal?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Well done, Captain! He laid down his weapons. It's good to have you with us. Now let's take him to the commandant.";
				link.l1 = "Why would I do that? I paid a fine in gold for Longway's actions - a generous one. Your fellow officers were witnesses - they'll confirm it. The commandant authorized me to take my man with me to the ship.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "Commandant might have enough of this blood gold, but not me. Some of the men he killed in that bloody cave were my friends. Besides, I doubt that he will care if we kill the Chinaman anyway.";
			link.l1 = "Sure you want to find out? And about your friends who got killed... ever heard about that brazen band of brigands? It must have been them.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Longway, you didn't kill as many soldiers as they claim, did you?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "That's right, Lord Captain. Longway saw that band. They hid deeper in the cave so they wouldn't notice him. And Longway heard the sounds of talking, swearing, and fighting between the bandits and the soldiers.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "See? It all fits. Longway may have a temper, but he's an honest man. We're leaving. If you touch us, you'll dishonor your uniform. Goodbye, gentlemen.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "No way, monsieur! He killed a whole bunch of our men, and now you're saying he'll get away with it?! Either you help us kill the bastard, or at least stay the hell out of our way!";
			link.l1 = "I'm afraid I have to interfere. I'm sorry, really.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "If you just wanted to talk, you wouldn't ask me to disarm. But a tiger is still a tiger, even with its claws retracted. You must have already decided to betray Longway long ago-no need to lie. Defend yourself, Captain!";
			link.l1 = "Fuck!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "I can't believe we got through with him! But tell me, why did he call you Captain?";
				link.l1 = "It's more complicated than it looks, mate. I needed to reassure your commandant. The important thing is the result, right? And the result is that Longway is dead, and I helped you with that.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Even your presence didn't help - he still jumped us. Damned savage...";
				link.l1 = "You shouldn't talk about him like that. He attacked us because he was upset and thought I was with you.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Maybe. In that case, goodbye, monsieur. We'll tell the commandant ourselves that the Chinese man is finally dead.";
				link.l1 = "Very well, thank you. Goodbye, boys.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Well, upset or not, savage or not, it doesn't change anything - he killed a lot of ours before, spilled blood first.";
				link.l1 = "Something must have driven him to that state. But let's not dwell on it. I'll be going, and you can return to the commandant when you see fit. So long.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "Lord Captain?";
			link.l1 = "Aye! I've been searching everywhere for you, Longway. You've caused quite a stir in town. We have a lot to discuss, so let's get back to the ship immediately.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "Over there!";
			link.l1 = "I see we've got company. Looks like we're going to be a little late.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "More coming!";
			link.l1 = "Stubborn bastards - I'll give them that. We're too exposed out here. Let's head to the cave - it'll be easier to defend ourselves.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "We can't stay here forever.";
			link.l1 = "And that's the first thing you want to say after everything that's happened, Longway? Don't you think it's time you explained what's going on?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Lord Captain, Longway...";
			link.l1 = "But you're right - we can't stay. Let's get moving before another squad shows up. We'll talk on the ship once we've set sail.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "The guile and malice of the white man knows no bounds.";
			link.l1 = "Hey, I'm a white man too! Besides, you killed their friends and fellow soldiers - they have the right to be angry.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "Do you absolve them, Lord Captain?";
			link.l1 = "I absolve you, Longway. And I urge you not to judge people by the color of their skin. You of all people should understand that. We were interrupted - where were we...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "Captain! Behind you!";
			link.l1 = "Oh, they're not going to let us have a proper conversation today...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "Clear, Lord Captain.";
			link.l1 = "That's good, but let's not linger here. You and I have a lot to talk about. Follow me - we're going back to the ship.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "Lord Captain, is it really you...?";
			link.l1 = "Aye, Longway. Are you all right?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Longway is fine. Thank you. But, Captain! Look!";
			link.l1 = "Run to the cave, hurry! It's a good defensive position!";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Longway will check if the soldiers are still coming.";
			link.l1 = "We'll go together - we can't hold our defense against the whole garrison.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Yes, Lord Captain?";
			link.l1 = "We have a lot to talk about. Now follow me - we need to raise the anchor immediately.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Thank you again for lending a hand, Lord Captain. I'm sure you have many questions.";
			link.l1 = "That's putting it mildly. Why did you kill those soldiers? You don't kill for pleasure-I know that.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "No, Longway does not. The soldiers tried to stop Longway, and prison was not an option. They wouldn't listen to a Chinaman-only a white man gets that courtesy.";
			link.l1 = "They don't always listen to other white people either, but I see your point. Still, slaughtering them like cattle in the city? What were you doing in Basse-Terre?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "Not only do white people often not listen to me; sometimes they won't even talk. And when they do, it's to call the guards. Longway didn't choose his skin or his eyes, but he's proud of who he is. When soldiers mock and threaten, Longway grows tired... and angry.";
			link.l1 = "From now on, let's work together. People talk to me instead of calling the guards... usually. But seriously, tell me about your mission. Let me help you.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Please, Lord Captain, understand Longway. He took an oath to do this alone. Don't push him. You owe Longway that much.";
			link.l1 = "I am truly grateful, but I could have handled van Merden myself back then. However, we were even from the start-you said I saved your face, and you saved my life. Now I've saved you again.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Hmm... you're right, Lord Captain. Longway believes you are his true friend among white men. Once, he thought so before, but he was bitterly mistaken. Do you remember John Murdock? Johan van Merden?";
			link.l1 = "How strange you should mention van Merden. Recently, someone tore a few pages out of his archive right under my nose. Was it connected to your case? Did you find the thief?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "I did. The thief was... Longway. He's very sorry, Lord Captain. Back then, he didn't know if he could fully trust you.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "You talk about friendship, but you steal from me behind my back? This is the first and last time, Longway. Do you understand?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(61))+")", "None");
			}
			else
			{
				link.l1 = "And how did you manage to pull it off, Longway?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				notification("Reputation Check Passed", "None");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Longway understands. He means it.";
			link.l1 = "I hope so. Now tell me how you came to this life - what promise you made, when, and to whom.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Yes, Lord Captain\nLongway seeks out the most important remaining living person to him-Chang Xing.";
			link.l1 = "Chang Xing-is he your best friend?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "Thanks to your kindness, the rest of the crew quickly got used to me and started trusting me.";
			link.l1 = "Well, I get it. Not one for praise, but good job, Longway... if you cleaned up the mess your intrusion left.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "Right. But there's no time for that.";
			link.l1 = "I guess not. But try not to do that again, alright? If you need anything, just ask. You can trust me. Now, tell me about your oath.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "Of course, Longway is happy to share his burden with you, Lord Captain.\nLongway seeks out the most important remaining living person to him-Chang Xing.";
			link.l1 = "Chang Xing-is he your best friend?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Chang Xing is my family, my sister. She went missing years ago. To find her, Longway seeks those who might know where she is.";
			link.l1 = "What does this have to do with van Merden's archive? Is it connected to your sister's disappearance?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "That's right. It's all connected. Longway and Johan met many years ago, in the land you call Formosa, long before I came to the Archipelago.";
			link.l1 = "You've known each other for so many years? And van Merden was involved? What a story! What was his connection to your sister's disappearance?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "He helped me in my search for very bad people-even by white men's standards. Oliveiro Fermentelos, Antoon van Diemen, and Joep van der Vink.";
			link.l1 = "Judging by their names, one is Portuguese, and the other two are Dutch.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Yes, that's correct. But the search didn't succeed. Longway waited patiently for Heaven's guidance. So when you obtained van Merden's archive, I decided to study it. When I found the first pages mentioning Oliveiro, I tore them out and fled from the cabin.";
			link.l1 = "Everything finally fits into the story.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "But the story itself is just beginning. Lord Captain, would you like to know about Longway's search from the very beginning? Are you ready to sit down and listen?";
			link.l1 = "That's exactly why I called you to the cabin. Go ahead.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "Chinamen are not allowed in here. This is a respectable establishment, for respectable people-not for the likes of you.";
			link.l1 = "I just have one question. Let me ask it, and I'll leave.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "Learn to speak properly first! I told you-your kind isn't welcome here.";
			link.l1 = "Where can I find Oliveiro Fermentelos? Tell me, and I'll be on my way.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "Are you deaf too? Don't test my patience, or this whole room will soon stink of yellow guts.";
			link.l1 = "My people have lived here for thousands of years. This is our island, and we can't even enter a simple tavern?";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "Oh, talking big, are you? You could be hanged for that. Get out!";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "I heard about your big problem, my little friend. You shouldn't have been so loud-wrong name, wrong place.";
			link.l1 = "Do you know something about this man?! Tell me!";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Calm down, mate.";
			link.l1 = "My apologies.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "I don't want your apology, but I do want your money. Maybe then I'll help you out. I'm Marcelo Schulte. And you? You got money, right?";
			link.l1 = "My name is Chang Tu. I have money. Is that enough?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(whistles) Escudos, pesos, guilders, doubloons... and even some of those weird coins you people have. This will do. Alright, Chung Chung, I'll see what I can find out about the man. Don't worry, I'm here almost every day, so your money's safe. Check back daily, and we'll definitely cross paths.";
			link.l1 = "I hope. I have no more money left...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "Ah, Chang-Chang! You're already here.";
			link.l1 = "It's Chang Tu.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "Doesn't matter, mate.";
			link.l1 = "Did you find out where Oliveiro is?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "Nope, not the slightest idea.";
			link.l1 = "My money!";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "Don't be so jumpy! Would I have dared to approach you again if I hadn't found out anything? I'm going to introduce you to someone who knows. And lucky you, he loves you Asian folks. He's even got servants to match-heck, even servant girls. Learning your filthy language too. Name's Johan van Merden. He'll be waiting for you in a two-story house near the residence.";
			link.l1 = "My thank you.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "You're Chang Chang, apparently? Come in, don't be shy.";
			link.l1 = "It's Chang Tu.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "Is that so? My apologies. That Marcelo and his parade of jokes... Shame that so few take an interest in your culture. And all this just because of a different language, and the cut of your eyes. But you're intelligent. Unlike the black folk, hehehe.";
			link.l1 = "(in Mandarin) So the smuggler wasn't lying-you truly are a man of culture. And you really speak our language?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "My thank you for the warm words about my culture. You must be Johan van Merden?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "Oh... I understood only a few words. I'm still learning, you see. Could you continue in Dutch?";
			link.l1 = "As you wish. You are Johan van Merden?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "Yes, Chung Tu, that's me. I hear you're looking for Oliveiro Fermentelos. I do know where to find him, but first tell me-why do you seek him? Your answer will determine mine.";
			link.l1 = "He... kidnapped my last and dearest family member-my sister, Chang Xing.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "Then I must disappoint you, Chang Tu. There's probably no hope for her now. She's likely been sold into slavery to a rich planter or to a brothel. Either way, you won't be able to save her.";
			link.l1 = "I believe Chang Xing is still alive. Oliveiro set his eyes on her. She proudly refused him. He stole her when I wasn't home. And... killed our parents.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "I... am so sorry. If that is the case, Chang Xing-right?-might still be alive. Here's what we'll do: give me some time to find out exactly where Oliveiro is right now. Let's say a week. I'll see you again then. Meet me outside the city gates-who knows what eyes are following you here. I don't want to get involved more than I am used to, hope you understand.";
			link.l1 = "I'm... I'm deeply grateful to you, Mynheer van Merden. I look forward to our next meeting.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Hello, Chung Tu. I see the fire in your eyes. I do have news, but it's not good.";
			link.l1 = "Any news is of utmost importance to me. Please, tell me, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "Aye... Fermentelos left for Batavia about a month ago. That's the only lead I got on him. The good news is he's planning to stay there for a while, so if you go now, you'll catch him. The bad news? He's a close friend of Governor-General Anthony van Diemen. You won't get near him.";
			link.l1 = "This news is enough. My humble thanks to you, Mynheer van Merden. I shall leave immediately.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Something told me you'd say that, so I decided to help even the odds for you and Chang Xing. I wrote a letter to an old friend of mine, Oliver Trust. He owns a shop in Batavia. He owes me a favor, so he'll help you out.";
			link.l1 = "Me... I don't know what to say...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "A simple “thank you” will do. If you can't find Oliveiro in the city, look for the Morning Star. You can always track him down through his ship. Good luck, my friend-you and your sister will need it.";
			link.l1 = "Thank you from the bottom of my heart, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "Who are you, and what are you doing here? I don't trade with your kind.";
			link.l1 = "I have a letter for you.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "Ah, the messenger! Though I wasn't expecting any letters today. Stay here! I'll have a look.";
			link.l1 = "Are you Oliver Trust? Van Merden sent me to you.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "I can read, you know. Normally, I'd send you away, but people like van Merden don't take no for an answer. Finally, it's time to settle the score with van Diemen.";
			link.l1 = "My target is Fermentelos. What about van Diemen?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "That's none of your business. You should be grateful I'm helping you at all. Now listen carefully, before I decide this is a bad idea. I know Fermentelos. He's been here for a while, but he's not here anymore. The Morning Star left a few weeks ago. God knows when it'll be back. So your target has changed, and it is a friend of Fermentelos...";
			link.l1 = "... van Diemen.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "Aye. You know about that too? I assume Johan told you? Oh, van Merden... you are a daring bastard. But since you already know about van Diemen, you know about his high position, don't you? What is your master plan to get to the Governor-General? Not by storming his residence, I am sure!";
			link.l1 = "Chang Tu is a skilled warrior.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "A skilled warrior, huh? You realize we're all tangled up now? And what happens to me if you're captured? I'll have to help you for your own safety and mine. Besides residing in his residence, Van Diemen pays regular visits to the plantation outside the city and his mistress Vette.";
			link.l1 = "You mentioned helping me.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "I believe everyone should have a passion, a hobby. As for me, I collect rare and expensive weapons. Sometimes they have history, sometimes not, but they're always deadly. My collection can be useful to your crusade. So, tell me, where do you plan to ambush van Diemen?";
			link.l1 = "(Residence) Since you have so many good weapons, I'll take the best blade. With it, Chang Tu will be unmatched among white men.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(Plantation) I'll ambush them on the plantation road - they'll have no place to run.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(Mistress) The mistress - there won't be many people there, so guards won't react in time.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "Good choice! I'm impressed. To make the most of it, you'll need a good firearm. Tell me, how far can you aim, Chang Tu?";
			link.l1 = "To be honest... not too far, I must ensure I don't miss."
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "I'll attack from afar - my enemy won't even realize where I hit him from.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification("Jager Unlocked", "Longway");
			SetCharacterPerk(pchar, "Jager");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "I see. In that case, take this! An antique Portuguese tower blunderbuss, firing a large-caliber cartridge. They don't make these anymore, even in the Old World.";
			link.l1 = "I saw one as a child...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "So, you know how to use it?";
			link.l1 = "No...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "Keep in mind, the interchangeable mechanism has gone rusty over time. No oil will fix it - it's broken for good. Charging it is hard, so let's do it now. Watch carefully - use a little force, like this. But not too hard, or you'll break it.";
			link.l1 = "Like this?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Exactly.";
			link.l1 = "Understood. Thank you very much!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "cartridge", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "cartridge");
			
			dialog.text = "A true jaeger! Be careful, this was a gift. It's one of those rare cases where a weapon is both ornate and deadly. A double-barreled hunting rifle! Heavy to hold, easy to use. Have you figured out how to shoot it yet?";
			link.l1 = "Understood. Thank you very much!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "You're right about the guards, but don't underestimate the danger. Van Diemen never goes anywhere in the city without his right-hand man, Joep van der Vink.";
			link.l1 = "So, they're together with Vette...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "What? Ha! You've got quite an imagination, Chinaman! Antoon is a coward, and van der Vink is there to protect him in case anyone disrupts their “private time.”/nJoep always wears heavy trench armor - impenetrable to most cold arms. That's why you'll need something special too. Take this rapier. It's long, stronger than most other swords, and weighs like a good blade.";
			link.l1 = "A rapier for fighting armored foes...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "Don't aim for the armor itself - it's not an estoc. Strike at the crevices and vulnerable spots, like the groin, armpits, and throat. Wear him down, dictate the terms. Joep also wields a heavy axe, so don't try to parry his blows - dodge instead/nJust in case you fail to find an opening, take this blunderbuss. It's usually loaded with buckshot, but I've prepared a set of steel arrows for you.";
			link.l1 = "Arrows for a musket...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "Unusual, right? A blend of old and new. It's designed to be fired with one hand, but if it's too heavy, use both. Many do/nAnd here, try this wicker armor. It's lighter than Joep's cuirass but still offers decent protection. Don't let his axe land a direct hit - even Milanese armor wouldn't hold up against a weapon like that. Do you understand?";
			link.l1 = "Yes, I understand. Thank you, Mr. Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "Overconfident, are you? Perhaps I told you about my collection too soon. But... you are committed already. Attacking a residence in broad daylight is a bold move, not to be expected. This blade should suit your needs. It's not the finest in the world, but it's perfect for stabbing, slashing, and chopping.";
			link.l1 = "Clewang! I recognize this blade. People from the neighboring islands often use one.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification("Duelist Unlocked", "Longway");
			SetCharacterPerk(pchar, "FencingMaster");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "Have you used one before? Good. You'll have little time and many enemies to face. Here, take this as well - a handgun with three barrels, beautifully inlaid. Load it now in front of me; you won't have time for that later. And wear this dueling waistcoat. It's light, it will give you the speed you'll need, and some protection.";
			link.l1 = "Thank you, Mynheer Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "Wait, we're not finished. It's in our mutual interest that you survive. Take this medicine to heal your wounds after the battle. \nAnd this elixir too. It tastes and smells awful, but it kills any poison in your body. Joep van der Vink, Van Diemen's bodyguard, smears his weapons with that shit. Cocky bastard, so you will be at an advantage.";
			link.l1 = "I don't know if I'll ever be able to thank you enough, Mynheer Trust...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "Your best thanks would be not to turn me in if you get caught. Although, most likely, they'll just kill you on the spot. But if you survive through this, tell Van Diemen he owes his death to me. Can you do that?";
			link.l1 = "No problem. Thank you again, Mynheer Trust. Goodbye!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "Halt! Where are you going, Chinaman?";
			link.l1 = "To the residence.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "That was a rhetorical question, genius. What makes you think anyone would let someone like you in there?";
			link.l1 = "I have business with Mynheer Van Diemen. Let me through, please.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "You know the governor-general's name? Well... tell me what your business is. I'll pass it on and get back to you with an answer.";
			link.l1 = "My conversation is only with Mynheer Van Diemen. He's waiting for me. Move aside, or you'll regret it.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "Well, well, don't crow, narrow-eyed. It's either my way or no way.";
			link.l1 = "My way then.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "Damn peasant! Who hired you? I'll pay you more than that!";
			link.l1 = "You white people only care about gold. May the dragons curse your kind. I came for information, but your people won't let me in.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "What do you want?!";
			link.l1 = "Fermentelos. Where is he now?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "Oliveiro? But why the hell do you want him? I'm not telling you anything!";
			link.l1 = "He killed my family and kidnapped my sister. My advice to you is to start talking. For your own good.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "What are you going to do to me? The whole garrison will be here soon.";
			link.l1 = "Have you heard of Lynchy? It's a punishment in my culture. It means 'Death by a Thousand Cuts.'";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "You won't have time to inflict so many cuts on me, you imbecile!";
			link.l1 = "It's a figure of speech. The executioner inflicts cuts, one by one. Or cuts off pieces of the body. We do as much as we have time for - unless you start talking.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "A-A-A!!! Stop! Stop, you filthy brute. I'll tell you, I'll tell you everything. Just stop. Joep! Finally! Where the fuck have you been all this time?!";
			link.l1 = "What bad timing...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Antoon? You need to see a doctor right away. I'll help you get there as soon as I'm done here. You! What the hell are you doing, you yellow butcher?!";
			link.l1 = "Yellow Butcher? I kind of like that. There's only one question I need answered, but no one seems willing to do it...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "What question?!";
			link.l1 = "Where is Oliveiro Fermentelos? Can't you tell just that?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "I don't give a damn about Fermentelos! Who gave you the money and information?!";
			link.l1 = "Oliver Trust. By the way, he wanted me to tell you that you owe him your death.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "Trust?! Ha-ha-ha-ha-ha-ha-ha! That miser, thinking he could take revenge just because we took his plantation? We'll soon take his shop and his life, once I'm done with you.";
			link.l1 = "You're wasting my time.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(in Mandarin) So, let's look for a good ambush spot.";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(in Mandarin) With this rusty thing, I'll need to get close. Quick volley - sharp and merciless. Fear and panic will do the rest.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(in Mandarin) Right here. They won't even see me at first. The best battles are the ones that don't start... or that end quickly with little bloodshed.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Nasty brute... Escaped slave aren't you? How did you get such a weapon? Did someone hire you...?";
				link.l1 = "No time! Tell me where Oliveiro Fermentelos is - now!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Hehehe, funny... There's no time - the blood is pouring out my belly. Burn in hell, pagan...";
			link.l1 = "(in Mandarin) No!!!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(in Mandarin) Why, why, why?! How am I supposed to find Fermentelos now?!";
			link.l1 = "But first, I need to hide - someone must have already reported this bloodbath...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "Hic! A Chinaman! I didn't expect someone like you to be invited here. Like to watch, eh? Hehe.";
			link.l1 = "Why are there so many people here...? And who are you?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "You don't recognize me by my clothes? And watch your tone when speaking to the Governor-General! Hic!";
			link.l1 = "So, you must be Mynheer Van Diemen. I apologize for my ignorance. Is this a carnival going on here?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "That's right, my good man, and no other way! A cross-dressing carnival! Ha-ha-ha! Not so bad, peasant! I'm sure Luthers would lo-o-o-ve to wear Vette's dress, ha ha ha!";
			link.l1 = "Luthers?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "Tha-a-at pitiful excuse for a husband, who loves peeking from the wardrobe while his dear wifey is being bedded. She doesn't mind!";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "Right, Vette, my dear? Heh-heh.";
			link.l1 = "(in Mandarin) What the hell is going on here...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "Hic! I don't know what you just said, but by the look in your eyes and your tone, you agree with me! Van Haan is a goddamn pervert. So, what are you anyway? A laborer? Did Vette invite you?";
			link.l1 = "I...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Inviting a laborer here is too much, even for Vette. He's obviously lost and in the wrong place. Hey, you. Get out of here and forget everything you've seen. Who's your master? We'll contact him, and you'll both be paid for your silence. You might even be allowed to return to your family on the continent. Answer me and leave.";
			link.l1 = "Actually, I'm here on business.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Heh, business. Only Mynheer van Diemen does “Business” here. My job is to keep him safe from people like you. And Luthers... is being Luthers. Or... did Vette really invite you here?";
			link.l1 = " No, I'm here to...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "Would my dearest Vette really invite a yellow-ass here?! Get out of here!!!";
			link.l1 = "The wretched cuckold...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "No one is talking to you. Shut your mouth. Don't pretend to have a cock or dignity.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "Cu-cu-cuckold?! No, I love her more than myself. Ha, a dumb Chinese like you wouldn't understand that!";
			link.l1 = "(in Mandarin) Sick bastard.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "Co-co-cock?! It's just fine! Yes! I just know that other men give my dear Vette more pleasure, that's all!";
			link.l1 = "As we say in my homeland, a man is still a man until he has only one finger left. If you were a man, you'd understand that.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "I didn't invite him, of course, but, you know, he's quite nice. He might stick around after you all leave. I've already tried it with our dog, but I've never done it with...";
			link.l1 = "Shut up, when men are talking, whore! You're the only animal here. I'm here on business. I look for Oliveiro Fermentelos. You must be his friends. Can you please tell me where he might be, Mynheer Van Diemen?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Antoon, he insulted me! Insulted me! You're not going to let it go, are you?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Hehe, sorry, mate, but the lady's pissed. I'm gonna have to give you a lesson of manners. Lesson one.";
			link.l1 = "But can you help me in my search of Oliveiro?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "It won't help a dead laborer.";
			link.l1 = "(in Mandarin) Damn you all...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(in Mandarin) Damn it! I didn't learn anything!";
			link.l1 = "(in Mandarin) I'll never forget this day... I have to get out of here before the guards arrive. Not that they'll care about the noises coming from this madhouse...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(in Mandarin) The gods have cursed this day! Van Diemen bleed to death while I was dealing with his lackey...!";
			link.l1 = "(in Mandarin) The guards are coming. I will have to fight my way out of here.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "Oh, it's Chang Chang! What do you need help with this time, my little friend?";
			link.l1 = "It's Chang Tu... what do you mean?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "You're oozing contempt for me, aren't you? You wouldn't come here unless you needed something.";
			link.l1 = "Do you know where van Merden is? Is he in town? He's not at home. I need to speak with him.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "A man can't be expected to stay at home all day, waiting for a single yellow-skinned man to show up. He's got business on the island. He'll be back in town tonight, so don't worry, Chang Chang!";
			link.l1 = "Thank you. Goodbye.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "Hey, narrow-eyed! What's the rush at this hour? All decent folks are asleep by now.";
			link.l1 = "Then what about you?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "Well said! We are on patrol! Word is, there's a little yellow fellow snooping around town, bothering God-fearing people.";
			link.l1 = "Who that might be, pray tell?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Enough talking - it's getting late and I am starting to get sleepy.";
			link.l1 = "Soon you sleep will be eternal.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Chang Tu, are you alright?";
			link.l1 = "Mynheer van Merden! I am, thanks to your intervention. Are you alright? That's the most important question.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "Always thinking of others, aren't you? We share that trait. I couldn't just stand by when I saw them attacking you, even though I knew you'd handle them. To answer your question, I'm fine, just a bit tired. My legs are a little shaky. Let's go inside, if you don't mind. We can talk there.";
			link.l1 = "Of course, Mynheer van Merden, it's your house after all.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Now, we can talk without hurry, in peace and quiet. Tell me, what brings you to me, Chang Tu?";
			link.l1 = "You're right, Mynheer van Merden. I've just returned from Batavia, and...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Wait. Is it poor Chang Xing...?";
			link.l1 = "No, not at all! I hope not. Heaven still keeps her fate a secret from me. And as for Fermentelos... he's not in Batavia. Van Diemen was of no help.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "He wouldn't be, for he and Oliveiro are old friends. As the English say, friends and partners in crime. I'd be surprised if he gave you anything useful.";
			link.l1 = "Yes, thanks to both you and Trust, I acquired mighty arms. I attacked Van Diemen to interrogate him and find out where Fermentelos was. But he died before I could learn anything...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Impressive. You've come to realize that people don't always want to share what they know. So there are other... methods of persuasion, shall we say. I thought you might have learned about your sister's death, and that's why you went on a rampage. But what brings you to me now? I told you I didn't know where Fermentelos goes, aside from his occasional visits to Batavia. With Van Diemen gone, that last lead is lost.";
			link.l1 = "But you know many things and many people. I thought you might help again, perhaps ask around about Fermentelos, like before. You were the first white man to treat me well. The first... white friend.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "That's... touching.";
			link.l1 = "Mynheer van Merden, why are you smiling...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "Huh? Oh, I'm sorry, Chang Tu. I'm getting old, sentimental, and melancholy with age. It's a sincere smile - I couldn't hide it. I'm glad you consider me a friend. Since we are friends, I also expect you to help me from time to time. In return, I'll definitely help you with Fermentelos. Don't worry - you're not walking into a trap.";
			link.l1 = "Hmm, help you how?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "Since we last met, I've deepened my study of your language and culture, especially medicine. I'd like you to find me certain relic plaques from time to time. I'll pay you generously for them, just like any other job. And I hope we can practice our conversations in Chinese occasionally. I'm ashamed to ask my servants, but a friend...";
			link.l1 = "Chang Tu will do his best, Lord van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Good. You and I have a long road ahead, my friend. A long road. Ha! I think it would be a good cover name for you. A useful practice of my trade. In Dutch, it's “Lange Afstand.” The English say “Long Way.” Which do you prefer?";
			link.l1 = "I like the English version better. Long. Way. Longway. It sounds quite fitting in my language. Thank you for listening, Lord van Merden. Longway will await your word and be ready to assist you and fulfill your requests.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "Speaking of the archive, Lord Captain, do you have it with you? It is all I need - I know the cipher by heart.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingL", 50);
				AddCharacterExpToSkill(npchar, "FencingS", 50);
				AddCharacterExpToSkill(npchar, "FencingH", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Yes, I kept it, thinking it might be useful one day.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "Unfortunately, no. Was it your last hope to find sister?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "Longway is very pleased that Mr. Captain is concerned. For now, there's still hope. I've found a new lead on Guadeloupe.";
			link.l1 = "All right, then. Tell me what happened to you there.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "That was a wise decision. Perhaps we'll find something in there that can help us in our search for Chang Xing.";
			link.l1 = "That would be ideal. Let's study it right now.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Yes, let's study it together. The year is... 1637. Antoon van Diemen sold... sold...";
			link.l1 = "Slaves, right?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Women from my people, sold to rich white men.";
			link.l1 = "That's terrible.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Lord Captain, you don't seem surprised. Doesn't it trouble you at all, the fate of those women?";
			link.l1 = "Longway, of course it sincerely troubles me. I've seen this filth from the inside. But I've always been an advocate for women... and a bit of a ladies' man, to be honest. It's good you killed van Diemen; he deserved it. Is there anything else?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Van Diemen only worked with those he trusted completely - Joep van der Vink, his right-hand man, and that damned Oliveiro Fermentelos. And... and...";
			link.l1 = "What is it? You've gone pale, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Johan van Merden...";
			link.l1 = "I'm so sorry. That's awful, but why are you so shocked? Earlier you said you tore out all the pages mentioning Fermentelos. Didn't you find mention of van Merden then?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "Longway was in a hurry and must have missed this important piece.";
			link.l1 = "I see. When you're ready, let's keep looking and find anything we can use right now.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "It's written that Fermentelos would send his people to capture women, swapping them out and destroying records. Merden would then send them to Batavia, where van der Vink and van Diemen sold our women to white men. If only I had learned this sooner...";
			link.l1 = "So, in the end, they all worked together. Don't blame yourself, Longway. You couldn't have known. The archive only came into your hands recently. Is there anything else?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Yes. They've been at it for nearly ten years. So many women lost their families, their honor, their hope... But then Fermentelos stopped working with van Merden. That's the only reason he helped me - all he ever wanted was to get rid of his former partner.";
			link.l1 = "What other details of their dirty deeds are recorded here?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "More of van Merden's dark thoughts. He found out that van Diemen was cheating him out of money. So, he sent me to Batavia, hoping I'd die there, but also hoping I'd take van Diemen with me.";
			link.l1 = "Cold. But also incredibly smart.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "It could have been even worse. It was van Merden who sent those thugs to his house to kill me. He stepped in to help only when he realized I might defeat them on my own.";
			link.l1 = "He had it all thought through, no doubt.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "After I returned alive, he must have thought I'd discovered his real agenda and come for revenge. When we talked, he had his gun aimed under the table. But then I called him my first white friend... he almost burst with laughter...";
			link.l1 = "That's awful, Longway. It's a bitter thing to realize that those we considered friends were laughing at us behind our backs all the time.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Longway learned something long ago, shortly before arriving in this archipelago. I was captured by the Portuguese and they wanted to hang me. Lord Rodenburg saved my life.";
			link.l1 = "Is that how you came into his service? Lucas was in Formosa too?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "Yes, that's right. And not just him - Van Berg, too. Van Merden told me it was he who advised Rodenburg to spare me. But some time later Longway learned from a shady source that it was actually Johan who sent the Portuguese after me. I didn't believe it then... but now I realize it might be true...";
			link.l1 = "Disgusting.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Still, doubts settled in my heart that day. So when I learned that Lord Captain and van Merden had confronted each other, Longway remembered your kindness and took your side.";
			link.l1 = "That was the right decision, Longway. Heh, it turns out that all this time, your first real white friend was me.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "It turns out so, Lord Captain. Now I understand. Van Merden told me I was his friend. But in reality, Longway was no more than another laborer to him - just more useful than most\nThat's all. The other pages concern accounting, as well as business details between Van Berg and Rodenburg.";
			link.l1 = "I see. And now it's high time you tell me about what you did on Guadeloupe.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "I was searching for the Morning Star. One of the torn-out archive pages said it was last seen near St. Christopher's.";
			link.l1 = "Why there? We agreed to meet on Guadeloupe, and I found you there.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Because St. Christopher's is the home of Georges Gravel, one of van Merden's informants. Georges believes I am still working for Johan. Moreover, Gravel once committed a grave offense against van Merden. And Longway helped cover it up.";
			link.l1 = "And what offense was that?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "That's not important. What's important is that Georges owed Longway a debt. So, I went to the church where Gravel works as an assistant priest. Is Lord Captain ready to listen further? You seem a little distracted.";
			link.l1 = "Sorry, I got distracted. Aye, sure, go ahead, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "Good, you're not too late. I wouldn't want to be here any longer than necessary, you know! What do you need this time, Longway?";
			link.l1 = "Change your tone, Gravel. The organization requires your services.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "I must confess, I haven't heard from them for a long time. Have they forgotten about me?";
			link.l1 = "I can remind them. Perhaps by telling Lord van Merden about what you did.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "All right, all right, no need to get so angry! What can I do for you?";
			link.l1 = "I need information about the Morning Star. Anything you can find. The more, the better.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "Sure, but it will take time! Two days! At the very least.";
			link.l1 = "Why so long?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Normally, It'll take money from the offering box to loosen the tongues of my informants. But we were robbed recently! The Father will announce a new сollection of donation money of course, but we still need to fix our roof - it is leaking! It's going to take a lot of donations to fix it.";
			link.l1 = "Two days. I can't stay here forever. I don't have that kind of time. Longway is not known for his patience. Lord van Merden even less so. Or shall I remind you of that, Gravel?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "I can't control what's beyond my reach! I'll do what I can. Although, I'd find out much quicker if you found those brigands and brought back our donations!";
			link.l1 = "I'll think about it. You start searching. Two days. No more. Meet at the same time and place.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A Day Later..."+ NewStr() +"In Search of the Church Robbers.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "Well, look at that! A narrow-eyed man on our island! Running from your masters, eh? Who're you hiding from, if you don't mind me asking?";
			link.l1 = "I'm a free man.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "Ha! Sure you are. But you look strong and smart, even if your eyes are a bit slanted. Want to join our gang? I don't think you've got anywhere else to go, anyway.";
			link.l1 = "Longway thinks you're more interested in robbing him than recruiting him.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Heh, consider yourself lucky. We recently robbed a church in town, can you believe that? Why? Because stealing from thieves ain't really stealing.";
			link.l1 = "I wasn't planning on hunting you down, but I'm glad I found you.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "Hunting us down? Ah, so you're a mercenary, not some runaway laborer. Bad for you then.";
			link.l1 = "Exactly.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Fuck... Why didn't you kill me right away? What do you want from me? Are you gonna drag me to prison?";
				link.l1 = "I have no interest in that. Just tell me where you hid the gold.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Heh... You yellow-skinned bastard...";
			link.l1 = "Longway's patience is wearing thin. I'll find out anyway. The only question is how long you'll suffer.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "Fine, alright... It's in a cave. Everything's there. The money is yours. Just... just don't kill me, all right?";
			link.l1 = "I didn't say there wouldn't be any suffering at all...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(in Mandarin) Here's the bandits' hideout.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(in Mandarin) It's a lot!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(in Mandarin) I hear footsteps...";
			link.l1 = "(in Mandarin) There's someone else here...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "What the hell are we doing here? There's no one left - we made sure all the robbers were gone.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "That's the point, idiot! They'll come back, and we'll give them a warm welcome.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "I'll take a look around, make sure no one's hiding. I'm bored anyway...";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(in Mandarin) Soldiers! How unfortunate... What am I supposed to do now?";
			link.l1 = "(in Mandarin) I need this money more than the white soldiers! I'm not leaving without it!";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "Ah, monsieur Longway, you've returned!";
			link.l1 = "Of course. Was there any doubt? Did you find anything about the Morning Star, Georges?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Yes, monsieur. It's a heavy galleon, captained by a Spaniard, or so they say...";
			link.l1 = "He's Portuguese. You white people can't even tell each other apart.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "Oh, right. My mistake. Anyway, I found out that he's heavily modified the galleon as a measure of trying to pass it off as a merchant ship, with small-caliber cannons and a smaller crew. But he expanded the hold, filling it to the brim - it's so heavy it can barely sail.";
			link.l1 = "So he's decided to start a new life. Good. Now, where can I find him?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "That's trickier. He moves constantly between our colonies and the English ones, but only among the Windward Islands. However, I've learned he's on his way to Basse-Terre with a large cargo of wine at the moment.";
			link.l1 = "I need to figure out how to get there quickly.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "That's your concern, monsieur Longway. I've got enough problems of my own... like fixing that damned roof.";
			link.l1 = "Speaking of concerns, I found those church robbers. Here's your donation money back. Fix the roof - it's not good for your God to be without one.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "Thank you so much, monsieur Longway! I never thought you'd be the one to do that.";
			link.l1 = "I didn't think so either. But I had to do something with those two days.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "So, you need to get to Guadeloupe? I'll find you a ship heading that way. Expect to hear from me soon!";
			link.l1 = "That would be helpful. Thank you, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("The Next Morning..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "You must be an acquaintance of Georges? He asked me to give you this.";
			link.l1 = "A note? My gratitude. How did you know it was for me?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "Seriously?";
			link.l1 = "Oh, right.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(Reads the Letter) Monsieur Longway, the ‘Provence' pinnace departs for Basse-Terre tomorrow morning. The captain, Mathieu Terugny, can be found in the tavern. Give my regards to monsieur van Merden. - Georges Gravel.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "We don't serve drinks to your kind here. And unless I want to hear complaints about fleas, I won't rent you a room either.";
			link.l1 = "I don't need a drink or a room. And... Longway doesn't have fleas.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "How the hell am I supposed to know? All right, spit it out. What do you want? Then get out.";
			link.l1 = "I will. I'm looking for Captain Mathieu Terugny. I can't seem to find him. Do you know where he is?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "He's busy getting his ship ready to sail in the local shop. That's far more important than chatting with a Chinaman like you, but you clearly don't get that.";
			link.l1 = "Actually, I used to be... Never mind. Not important right now.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "What do you want, Chinaman? Can't you see I'm busy? I need to get my ship ready.";
			link.l1 = "Captain Mathieu Terugny?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "Well, this just stopped being funny. How does someone like you know who I am? Did someone send you?";
			link.l1 = "No need to worry. I heard you're sailing to Basse-Terre. Can you take me as a passenger? I'll pay.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "This just keeps getting better. I'm heading to St. Pierre, not Basse-Terre, but it's a short detour. That's good, because I won't have to keep you on the ship any longer than necessary. Five thousand pesos. We leave in three hours. Pay at the pier. Even though I'm a merchant, there's no bargaining. Got it?";
			link.l1 = "Yes. Thank you. See you at the pier, Captain Terugny.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "You showed up after all, chink. I thought you wouldn't make it - no one ever gives real money to your kind voluntarily.";
			link.l1 = "Five thousand pesos, just as you asked. Are you ready to set sail?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "No, no! I should be the one asking you that. But I take it you're ready. Come on. You'll row the dinghy. And don't expect a proper cabin! You're the only reason we're making this detour.";
			link.l1 = "I don't need comfort. Just get me there.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...so Longway couldn't figure out exactly where the Morning Star is headed.";
			link.l1 = "Yeah, I can see how you ended up in all that mess.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "I saw a brig in Guadeloupe waters. Perhaps it was the Banten. I'll try to find out. Well, you can go now, Longway. Bring me " + sStr + ".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "My captain, is everything well? I came as soon as Longway said you needed me.";
				link.l1 = "I'm just trying to piece things together. Do you remember the name of that brig we saw off the island?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "You wanted to see me?";
				link.l1 = "Aye. Do you remember the brig we saw recently? Find out her location and name.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "I remember, but why the sudden interest in a brig? Finding out could take some time.";
			link.l1 = "Helen, just do it, please. And yes, I know it could take a while. I'll be waiting.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "No, I didn't check. Why? Is it important?";
			link.l1 = "Mm-hmm. Can you find out more? I need to know where they're anchored now, if they haven't left Guadeloupe waters already.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "By all means. Just a heads-up, it might take a while. I'll take a dinghy and a couple of guys to help, alright, Charles?";
			link.l1 = "Of course, Helen, thank you. I'll be waiting.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Senor Captain, you called?";
			link.l1 = "Yes, Alonso. We passed a brig in the waters off the island when we went back for Longway. Did you happen to catch her name?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "No, my job is to keep an eye on the new recruits and take part in the boarding vanguard. Besides, I don't own a spyglass, and we weren't that close.";
			link.l1 = "True. But I need to find out nonetheless. Get it done.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Aye, Captain. I think I can do it in half a day.";
			link.l1 = "Hurry up. I'll be waiting.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "I've learned everything. Was everything alright while I was gone, my captain?";
				link.l1 = "Yes, I'm fine, thank you, Helen. Tell me.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "Whew, I'm back. I found your brig.";
				link.l1 = "Welcome back. What's her location and name?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "The Banten. That name means something to you, doesn't it? She's at the lighthouse now, and a few of her crew have come ashore. Are we going to attack that ship?";
			link.l1 = "No, we need to find out exactly who went ashore. We'll head to the lighthouse by land. Considering we've already been delayed, it's high time we left the port. We should anchor somewhere remote. Capster Beach would be good. Let's hurry, Helen.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Well, the brig is called the Banten, and she's anchored at the lighthouse. Some of the crew have landed there. What are you going to do?";
			link.l1 = "To find out, we'll have to reach the lighthouse unnoticed, and we can only do that on foot. Our ship needs to anchor somewhere safe. How about Capster Beach?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "Good idea. Charles, do you want me to go to the lighthouse with you?";
			link.l1 = "I'll think about it while we move the ship - you're tired enough as it is.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "I came back as soon as I was done, Senor Captain.";
			link.l1 = "Very good. Report, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "The brig is still off the island - at the lighthouse, to be precise. The name on the stern is Banten. A few of their crew have gone ashore.";
			link.l1 = "Good work, Alonso. Get the crew ready to hoist anchor immediately.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "Prepare for boarding, too?";
			link.l1 = "Not yet. If their captain is headed for the lighthouse, he might hide in the city if we attack at sea. We'll head to Capster Beach to secure our ship, then approach the lighthouse on foot.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "Lord Captain, look! There's someone inside the lighthouse.";
			link.l1 = "Good, we're in time! Let's hurry and get them. Alonso will have a lot of work today.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "But what if they die in the process?";
			link.l1 = "What do you suggest?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "We sneak in quietly and overhear their conversation first.";
			link.l1 = "I doubt we can do that without being seen from the window. But let's give it a try.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "SkritoeBessmertie");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Think about what I said. Think hard. Money is not an issue - within certain limits, of course. But even that limit will seem like a mountain of gold to you - the Chinaman must die! I've sent men after him before, but to no avail. This time, however, if they team up with your men...";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "Look, we're being watched! It's him! Him and his damned captain!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "Damn you, filthy Asian... I had to endure so much because of you. And now, for all that, I'm about to die...";
				link.l1 = "We'll take you to our physician, Lord Commandant. Just tell us who you were talking to - it's very important.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "His name... is Joep van der Vink, he... kha...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "He's dead... Well, at least we know the name. Longway...?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "That absolutely can't be...";
			link.l1 = "You're looking a little pale, Longway.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Longway was quite sure he killed van der Vink ten years ago\nThey're getting away! Their ship is fast!";
			link.l1 = "Yes, a marvelous brig... unfortunately for us. Even if we reach our ship in time, they'll be gone by the time we hoist the sails and catch the wind.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "This could be the end...";
			link.l1 = "No, Longway. Listen to me. If they plan to stay in the Archipelago, we're bound to run into them sooner or later - it's a small world, and the Caribbean especially so. As soon as we pick up their trail again, I'll drop everything and go after them. I promise you that. You hear me?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Yes, Lord Captain. Thank you.";
			link.l1 = "Keep your head up, Longway. We need to hurry back to the ship - the Commandant's death will be big news very soon.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			Return_LongwayOfficer();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "Monsieur! A moment! Are you a captain?";
			link.l1 = "Maybe. How did you guess? And what do you want?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Well, there's nothing but mountains and thick jungle around here - no roads to the city. Yet, here you are. You're not just sightseeing, right?";
			link.l1 = "Good observation. But you still haven't told me what you want.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "Ah, right! Captain, our ship hit the rocks just off this cove. We're the only ones who made it...";
			link.l1 = "I'm sorry. You want me to take you somewhere, don't you?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Aye... We won't be any trouble, I swear. Just drop us off at Belize, and we'll manage from there.";
			link.l1 = "It's not far, is it? In that case, welcome aboard.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "I'm sorry, but I'm headed the other way.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "Thank you, Captain! Who knows how long we'd have been stuck without you.";
			link.l1 = "Indeed. Let's not waste any time!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "But Belize is so close! It wouldn't take long, surely?";
			link.l1 = "I'm in a hurry. Can't afford any detours.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "Not even a short one? Just to Belize? Please, Captain, don't leave us stranded!";
			link.l1 = "Alright, I hope I won't regret this. All aboard!";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "C'est la vie. Have a pleasant day, my friends.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "Thanks again, Captain! We're just simple sailors, so we don't have much to offer you.";
			link.l1 = "Well, at least we didn't have to go too far out of our way.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "We'll raise a glass to your health and light a candle for you in the church.";
			link.l1 = "That's better than nothing. Cheers, lads!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "Did you hear? They finally caught him! Our waters are safe at last!";
			link.l1 = "That's... good news? But who did they catch?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "Matthew Lutter, the Windbag himself!";
			link.l1 = "I'm not familiar - what did he do?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "You don't know?! Well, you're clearly not English, I can tell. He's a pirate who's been plundering us and the Spaniards for years on his ship, the Seagull.";
			link.l1 = "Plundering both the English and the Spaniards? That's unusual.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "Indeed. The coastal guard could never catch him, but in the end, he bit off more than he could chew - lost to some strange merchant ship, if you can believe it.";
			link.l1 = "That's amusing. What was so strange about the merchant?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "Well, it was just one huge, clumsy galleon with no escort! But thanks to her madman captain, Lutter will sing his last song today - he's about to be hanged. You should come see!";
			link.l1 = "I might, but for now, I have other matters to attend to.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "Lord Captain!";
			link.l1 = "A Spanish merchant defeating a daring pirate... You're thinking what Longway is thinking, right?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "The Morning Star...";
			link.l1 = "Most likely - there's no other merchant captain like him in the entire archipelago.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "We must find him immediately!";
			link.l1 = "Right. But I don't see any heavy galleon in port. Let's try to talk to the Windbag before he's hanged. Let's see if he's earned that nickname.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			Return_LongwayOfficer();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "Is he still alive? Can we talk to him?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "What? Oh, yes. He's alive - the execution hasn't happened yet. You can go talk to him - he's more talkative than ever. But lately, he's been spouting nonsense, mostly talking to himself. The Windbag's gone mad... I can't wait to hang him, before we all go mad from his endless chatter.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Thank you.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			Return_LongwayOfficer();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "He stole my treasure!";
			link.l1 = "Matthew Lutter?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "My treasure's bound to him now, you know, HIM! There's nothing we can do! What do you want?! Do you want to take something else from us? There's nothing left! She's going to die! Or worse!";
			link.l1 = "Who's going to die? What treasure? Never mind, it's your own fault - you attacked that galleon, not the other way around.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "No! It was the other way around! Damn that hidalgo! He's the reason we're in this mess! He came right at us and fired point-blank! Then he took her from us!";
			link.l1 = "Really? That's not surprising. What else can you tell us about him? And... what did he take? Who's 'she'?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "Ah-ah-ah!!! A-A-A-A!!!";
			link.l1 = "I see, I'm wasting my time...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Captain, with your permission... Lutter! Out! End of the line, pal.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "Captain, we need to find out more about Sotta and Lutter. Let's ask around.";
			link.l1 = "Good idea, Longway. We didn't get much from the yelling man anyway.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "But it's better to start with Sotta.";
			link.l1 = "Right, he's the one we're after. Let's go.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "They don't know anything!";
			link.l1 = "Obviously. But we've got enough to start thinking for ourselves. From what I've heard, Sotta will probably try to sell those strategic goods he was rewarded with, and soon.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "Exactly!";
			link.l1 = "We should intercept him on his way at Port Royal or Capsterville. The only question is where he's headed and where we should engage him. Or maybe we'll catch him in the open sea.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "No! Longway meant... Fermentelos is a seasoned captain. A fight in the open sea could go either way. We'd have better chances ambushing him in port.";
			link.l1 = "You're right, I suppose. No matter what really happened between Matt and him, Sotta is dangerous and can't be underestimated.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "We can't wait either!";
			link.l1 = "Right again, Longway. So let's raise the anchor immediately, and then we'll plan our next move.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Lord Captain, the Morning Star is in port!";
			link.l1 = "Yes, I've already noticed.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "What's your plan?";
			link.l1 = "I haven't decided yet. Trying to board them under the fort's guns would be suicide. And even if we capture their heavy galleon, we can't escape on it. Do you have any ideas, Longway?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Yes. We could anchor off a safe cove and approach the galleon by boat under the cover of night.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "What about Half Moon Bay, Longway?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "I think Portland Cove would be a good fit - close enough and relatively safe. What do you think?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Good choice.";
			link.l1 = "Great, that's settled. Did we miss anything?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "I don't think so, Lord Captain. We just need to be well-prepared.";
			link.l1 = "Absolutely.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "Who the fuck are you, what's going on? Mister Holmes!";
			link.l1 = "Mister Holmes doesn't work here anymore. And we have sealed all the hatches tight. So, we won't be disturbed for a while, Mynheer Fermentelos.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "What? Fermentelos? My name is Edgardo Sotta!";
			link.l1 = "Uh-huh, I've heard that one before. We know that's not your real name, Oliveiro.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "Fermentelos is dead!";
			link.l1 = "On second thought, you do look too young. You obviously couldn't have been the captain of the Morning Star ten years ago. So, what happened to Oliveiro?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "We got rid of him. He was just another problem we had to clean up - just like the one standing next to you.";
			link.l1 = "Well, since you're not Fermentelos, maybe you can still answer our questions. We're looking for someone he took from my friend.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "I'm not going to tell you anything! He'll never forgive me for this.";
			link.l1 = "Right now, you'd better worry about whether we forgive you...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "He's finally dead...";
			link.l1 = "That's right. And who are you, madam? Did he hold you against your will? I sympathize; you must have been through a terrible ordeal...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "I'm Annabel Lutter. And thank God, I didn't have to endure much, but I appreciate your concern, mister...?";
			link.l1 = "Captain Charles de Maure. Lutter, you say...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "Ah, you must have heard of Matt? Poor fool... I was his... consort.";
			link.l1 = "I'm sorry for your loss, Mrs. Lutter. You're a widow now. What was your maiden name, if it's not a secret?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "I didn't have one. Take a closer look at me. My poor mother was a dark-skinned slave girl to the pirates. Nobody knows who my father was, so they didn't bother giving me a proper name.";
			link.l1 = "Why didn't anyone touch you then? Don't get me wrong - I'm glad it didn't happen. But still, it's... unusual.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "You're right. But let's call things by their proper names. I'm not a pampered noblewoman; I'm the daughter of a slave. I won't faint from a heavy conversation.";
			link.l1 = "Ahem, I'm not one for pampering either. But go on, please. Why didn't the crew lay a finger on the slave girl's daughter? You don't know your father, and he didn't seem to care.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "I suppose not. Since you know about Matt, do you know he worked for Levasseur for a while?";
			link.l1 = "Yes, I heard about it while I was searching for the Morning Star. But what's that got to do with it? Tell me everything, please.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "You still don't understand, do you? Apparently, you haven't heard about Levasseur's... preferences?";
			link.l1 = "I haven't, but then again, what does that have to do with...?";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "Oh, I guess I'll have to tell you all about it. Sit down if you're too impressionable, sir. The thing is, he sleeps with a lot of women, and...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "His wife is not far from him, and she sleeps with almost anyone.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "Oh no.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " Well, you know what they say... like husband, like wife. But no, I'm sure he went much further than that.";
			link.l1 = "And how far?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "Your sarcasm is misplaced here, sir. You have no idea what we're talking about.";
			link.l1 = "All right, all right, I'm sorry. Go on, please.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "It's not just cheating on your spouse. He's taking women against their will. And it's not just a one-time abuse. He kidnaps girls and keeps them in one of the wine cellars he owns.";
			link.l1 = "So he's getting slave girls on a regular basis? And you were supposed to be one of them?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "You're right about the latter. But, alas, not the first. He doesn't need slaves. Levasseur is insane - in his own way, not like my Matt. Francois wants to own a woman completely, body and soul. And it wasn't about love, of course. He needed free women to break their will. He enjoyed watching the way their looks, behavior, and manner of speech changed over time...";
			link.l1 = "Disgusting...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "You're already feeling a little sick. Now imagine what it was like for those women. I heard about all this, and not only from Matt. Levasseur once had a Portuguese noblewoman...";
			link.l1 = "You looked away and kept quiet. Tell us everything. I've seen all sorts of things in the Old World and during my time in the Archipelago too. Nothing surprises me now.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Stop, I don't want to know what happened to her. I hope those women didn't suffer too long in his hands.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "But you've never heard of anything like this. And I hope you never see it. She was brought to him still proud and unbroken, even though, as Matt told me, Levasseur's men raped her all the way to Tortuga after taking over her husband's plantation near Campeche - he died from a hemorrhage after those monsters shot him in both knees...";
			link.l1 = "A strong woman... But you said Levasseur usually didn't touch the women he wanted for himself.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "The ones he specifically requested were left alone. But Senora Leontina was a gift. An unexpected and pleasant one for them all. So they indulged themselves...";
			link.l1 = "I see...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "I guess... Matt had become one of Francois' favorites. He was invited to one of Levasseur's secret soirées... During the feast, one of the pirates complained that there weren't enough women. Levasseur laughed and then...";
			link.l1 = "And then? What happened?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...then she was brought out. On a leash! Beaten, her back scratched, blindfolded and gagged. When they removed the gag, all she said was...";
			link.l1 = "Something horrible, I imagine. Did she curse him with everything she had?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "If only... Dona Leontina simply whispered, 'What does my master wish?'";
			link.l1 = "I think I'm going to be sick. Did Matt tell you what happened to her afterward?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Murdered, of course. But not at Levasseur's hands. He discarded her like a stray dog. One of his captains shot her. Before she died, she uttered only one word...";
			link.l1 = "A curse? A prayer?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "No. 'Thank you...'";
			link.l1 = "To be thankful for death after such torment... What she must have endured... and others like her in that monster's lair...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Levasseur particularly despised slaves and dark-skinned women - said there was nothing to break in them. They didn't last long with him, and neither did the Indians - except for a few particularly stubborn ones. But wildness and rebellion weren't the answer either - he killed those who tried to please him too soon and those who remained defiant for too long.";
			link.l1 = "That's horrific... Tell me, did Levasseur ever have Asian women?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "No, at least not that I've heard. As for me... I've already told you that he didn't like dark-skinned women. So when Matt was working for Francois, he would walk with me openly on the streets of Tortuga. He even took me to the residence once.";
			link.l1 = "But Levasseur wanted to make you one of his slaves anyway...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "Exactly... I don't know why he liked me so much... When Matt found out, he fled the island as soon as he was told. He never returned to Tortuga. He might have been a bit mad, but he loved me. He called me his treasure...";
			link.l1 = "So that's what he meant when he said Sotta took his treasure from him!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Heh, he did say that? Oh, Matt... But it seems we were never meant to grow old together. If Levasseur set his sights on a woman, he'd do anything to get her, no matter her background or the cost. Sotta was one of his captains, and he did what he was told.";
			link.l1 = "I see. And what do you intend to do now, Annabel?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Run. Somewhere Levasseur's men can't reach me. Change my name. Disguise myself...";
			link.l1 = "I hope you succeed. I wish you all the best, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "You'll need money to arrange a passage. Take this. There are ten thousand pesos here.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "You'll need more than just a little money. Not everyone is willing to help a dark-skinned girl, even a half-breed. Here, take a hundred doubloons - find a ship and hide.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "You too! Goodbye, Captain.";
			link.l1 = "Goodbye.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "I... I don't know what to say. No one but Matt has ever shown me such kindness.";
			link.l1 = "Maybe it's a sign. That you'll grow old happily somewhere after all. Farewell.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "You're right. Thank you so much for this. I'll remember you in my prayers for the rest of my life.";
			link.l1 = "Thank you. Goodspeed.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "That man... No, he's no longer a man. He's a beast. A monster. Torturing women like that...";
			link.l1 = "I know what you're thinking, Longway. But you heard - he's never had a yellow-skinned woman.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "But he knew the whole group! Van der Vink, Fermentelos, Sotta... We just read about it in his journal. What if that particular 'she' is... her?";
			link.l1 = "Who knows... A woman bent on revenge against Fermentelos - it's easy to see why you'd think that. But it could have been any woman whose life was shattered by Oliveiro. It doesn't have to be your sister. It doesn't even have to be a yellow-skinned woman.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "Are you... refusing to give this a go, Lord Captain? At the very last moment...?";
			link.l1 = "No, Longway. But how do you imagine it? It's unlikely Levasseur will answer any of our questions. And sniffing around Tortuga like this is too dangerous.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "So what do you suggest?";
			link.l1 = "Wait it out. We know Levasseur doesn't like women like your sister. So we can conserve our resources for now. Patience and strength. Francois is a tough nut to crack, not least because of his 'turtle.' But with Svenson's help, we can talk to him on our terms. I promised you I'd help you find your sister and intend to holp up to it. Do you believe me, Longway?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "Hmm... Aye aye, Lord Captain. But Longway has one more request for you.";
			link.l1 = "What is it? You're not planning to go off on your own again, are you? Last time it didn't end so well.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "Not at all, Lord Captain. I realize now that unfortunately, a man like me can't do anything on his own in a world run by white men. Longway asks you to dock at Capsterville and deliver a note to Georges Gravel, asking him to find out anything while you're getting ready.";
			link.l1 = "A sensible idea, Longway. We'll do that.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Lord Captain, there's something Longway needs to ask...";
			link.l1 = "Did you forget to write the letter? You can just talk to Gravel.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "No, the letter's ready. But Longway thought it best not to wander around town alone. Lord Captain... could you deliver the letter to Georges for me? Please?";
			link.l1 = "Do I look like a courier to you? Or are you the captain here?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Lord Captain...";
			link.l1 = "Ha ha ha, I'm just joking, Longway! Remind me where to find this Gravel of yours?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "He works at the church.";
			link.l1 = "Alright, I'll handle it.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Charles, my dear Charles, is something wrong? You look worried and... tired, alright.";
			link.l1 = "Oh, no, no, Mary, I'm fine. It's just... this Tortuga quest of mine. It seems to be at a dead end... again. And that Sharp's will definitely took its toll on me, for goodness' sake. But never mind.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "What? What quest? And what's that got to do with Sharp? I don't understand anything!";
			link.l1 = "Too many questions, Mary. This is no place for such talk. Shall we discuss it in the tavern room? Just the way you like it, out of sight and out of mind. I will fill you in what I have been doing for the past year.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "Alright! But be warned: if you're hiding something...";
			link.l1 = "Absolutely not! Let's go, we have time to kill anyway...";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "How strange, isn't it, Charles? I'm supposed to own this very island, but I don't feel like I own it at all.";
			link.l1 = "You think?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "Oh, that grin of yours... You do know how to treat a girl. But what's wrong with you? Your face is all wrong!";
			link.l1 = "Why? It is my usual face, very handsome too.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Charles, I can hear it in your voice - you've been down lately.";
			link.l1 = "I've got a lot on my plate, especially with Longway. I'm just exhausted. But it's too late to give up, especially since I made a promise to him and to my father.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "I don't understand... What does Longway have to do with it? And what promises did you make?";
			link.l1 = "If we're going to discuss it, let's do it in the tavern, rent a room. Away from other people.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "All right, let's go. There's nothing else to do anyway, so at least we can spend some time together.";
			link.l1 = "Lead the way, darling!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Look how sweetly they sleep in each other's arms! Lovely!";
				link.l1 = "Jealous?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Rise and shine! How did you sleep, lovebirds?";
				link.l1 = "Fine, thanks for asking. And how did you boys sleep?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "That's a silly question, don't you think?";
				link.l1 = "It is. And a stupid thing to do on your part. Do you want to know why?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "They say you've got a sharp tongue, Charles de Maure.";
				link.l1 = "And not just my tongue. Want to find out? But tell me, why didn't you attack while we slept?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "And why is that?";
				link.l1 = "You shouldn't make Mary angry in the morning. You'll find out why soon enough.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Simple! It's dark, you know, so we couldn't tell which of you was the girl.";
				link.l1 = "Bastard.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Unlike you, I'm not afraid of women. Speaking of which - boys, take her safe and sound, or the Huguenot will make us into women instead!";
				link.l1 = "Hu... who?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "At least I look like a man. Boys, take the blonde alive - the Huguenot is waiting for her.";
				link.l1 = "Hu... who?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Who was that, Charles? Who the hell is that Huguenot? Is it really...?";
				link.l1 = "There's only one, Mary. And we'd better...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Charles... what was that? A Huguenot? Is this the man I think it is?";
				link.l1 = "I'm afraid so, Helen. We need to...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Do you hear that? Someone's coming, alright. Friends of these dead men, probably.";
				link.l1 = "Then we'll see them join them. Get ready...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Do you hear that? Footsteps.";
				link.l1 = "Indeed I do. Stand behind me.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Lord Captain, lady " + sStr + ".";
			link.l1 = "Longway?! You think you can walk into our room just like that? What if we were...?";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Hm, beg your pardon, Lord Captain. I thought that you would have closed the door if you were busy like that. But Longway found it open.";
			link.l1 = "Broken, not open. But tell me, my friend, why are you so damn calm? There are dead bodies on the floor, we're armed, and you're...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "Well, I'm used to it.";
			link.l1 = "And you can't argue with that, can you? But really, you didn't hear the sounds of fighting on your way here? Didn't see these brutes walk into the tavern and up the stairs right in front of you? ";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "No, Lord Captain. I saw no strangers in the hall on my way up here.";
			link.l1 = "That's a ridiculous coincidence. So what do you want, Longway?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "I urgently need a ship and crew, Lord Captain.";
			link.l1 = "What? Why? Did you finally get on Chang Xing's trail? In that case, let's go for her right now, together.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "Not Chang Xing, alas. It's... Joep van der Vink. Georges Gravel sent a message and I got it while I was strolling about the village, while you... were resting with the lady.";
			link.l1 = "Aye, I've had a great rest, I can tell you that. But why should we separate now, Longway? We have a damn long list of important tasks to complete and dangerous people to kill.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Van der Vink is not as dangerous as Levasseur. Besides, I've already defeated him once. And I will defeat him again. This time, to make sure he is dead for good. I don't want all of us to waste precious time on him. You should go to Tortuga and ask the important people about anything we need. I'll capture van der Vink myself. Lord Captain, this is not worth wasting your time and I was a Captain once too. I will manage.";
			link.l1 = "Hmm, you have a point, Longway. Van der Vink may not be as dangerous, but the 'Banten' is one of the fastest ships in the Archipelago. Not every ship will do to catch her. And what about the crew? How do you plan to gather men so quickly and on your own?";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "I know the right place and I have the Compnay's standing there. Or at least I can pretend about that, as I did with Georges. The Company... Mynheer Rodenburg  used their services when he urgently needed fighting men, professional crews, who don't ask questions.";
			link.l1 = "A ship's crew for hire, then... Makes sense such a thing exists. And how much will it cost?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "Two and a half thousand. Right away and right now.";
			link.l1 = "That's it? It takes more than that to hire a full complement of regular sailors from a tavern, especially for a big ship. Apparently, Rodenburg and his agents have special prices in special places.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "I meant doubloons, Lord Captain.";
			link.l1 = "WHAT?!";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "You heard me right, Lord Captain. It's important. I wouldn't ask for such an amount for a trifle.";
			link.l1 = "Yes, I heard you, but I still can't believe it. Special prices indeed. Do they accept pesos?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Yes... from white people. Longway may have trouble with that, but... I think I'll be able to convince them if I ask hard enough. There's always a way.";
			link.l1 = "Well, that's something. And that's just for the crew... And you've got a ship to get to, too. Probably also in some 'special place'? I'm afraid to ask how much it will cost us...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "Not quite so, Lord Captain. The crew comes with its own ship.";
			link.l1 = "But?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "The 'Meifeng'. She may become a decisive factor - no ship in the Archipelago is faster than her. And she is... was mine, so I know her. Will you lend her to me, Lord Captain?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "Here. Two and a half thousand doubloons. As long as you bring me van der Vink's head on a platter of solid gold, ha ha ha ha!";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "I don't carry that many doubloons, Longway. And I doubt I'd even have that many on the ship - it's a pile of gold you are talking about. But pesos, sure. Three hundred thousand is just what you need.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "You know what, Longway... Are you really suggesting I pay money enough to arm a siege fleet just so you could fight a common thug?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Oh... Longway thanks you from the bottom of his heart, Lord Captain! But still, what about the 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "What about her? My friend, did you bang your head on the way here? She is in our fleet right now!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "I need to think about it, Longway.  How much time do we have to catch van der Vink?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Lord Captain, you made a slight mistake. It would be two hundred and fifty thousand pesos.";
			link.l1 = "I did not; it's Charles de Maure's special exchange rate when his friends need help, ha ha. I'm giving you extra so you'll have enough for everything.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Thank you very much, Lord. Captain... But, what about the 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "What about her? My friend, did you bang your head on the way here? She is in our fleet right now!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "I need to think about it, Longway.  How much time do we have to catch van der Vink?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "There is no other way, Lord Captain, please calm down...";
			link.l1 = "Oh, I haven't started yet. Here's the deal. Fifty thousand pesos. That's just enough to buy a brig from the shipyard, prepare it for battle, and even hire a crew.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "But, Lord Captain. It may be enough for a white captain! Not everyone will agree to deal with Longway. They will drive a hard bargain before they sell me anything!";
			link.l1 = "So, be persuasive! You're quite adept at haggling, judging by your initial... proposal. Are you still here? Take this money and go, since it's so urgent as you say!";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "Aye aye, Lord Captain...";
			link.l1 = "And don't look at me like that. I'll see you later on Tortuga. Good luck.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "Ahem, no, Lord Captain. Of course, I remember. Longway was just asking if you're ready to share her with me.";
			link.l1 = "I am. After all, van der Vink is as much involved in your sister's misfortunes as the other people on our list. So catching him is really important. I give you the command of the Meifeng.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "I can't believe it... Thank you, Lord Captain!";
			link.l1 = "Ah, it's nothing. She used to be your ship, I will always remember that. Well, go on. Kill the son of bitch. I'm off to Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			notification("Longway approves", "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "Time is short, Lord Captain. We shouldn't waste it - Chang Xing might need our help...";
			link.l1 = "I know that, Longway. Still, how long do we have exactly to catch van der Vink?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "A couple of months - he goes on regular route for about that long before disappearing for a while. Such is his way, as Gravel informed me in his letter.";
			link.l1 = "Alright. Let's go to the ship, then...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "I'm afraid my preparations must begin immediately, Lord Captain. So that we can start right away when I have the Meifeng. I need to negotiate with the men in advance. ";
			link.l1 = "So where do we meet?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Right here. But we can meet at the shipyard for your convenience.";
				link.l1 = "And why am I the only one who didn't know that you can hire a full crew of fighting men here for the right price?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "Those mercenaries used to have a place in Isla Tesoro, but were forced to move here.";
				link.l1 = "I can see why. So where do I look for you in La Vega?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Because very few know about it. And even fewer can afford it. Mynheer Rodenburg was their only client for a long time.";
			link.l1 = "I see. Alright, Longway. See you there.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "The tavern, Lord Captain. Where else would I be?";
			link.l1 = "That's right. See you later then, Longway! Take care of yourself.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Lord Captain, I am to inform you that the crew is ready. There's one last matter to deal with. What about the 'Meifeng'?";
			link.l1 = "So far, I haven't really picked a ship worthy of you, Longway.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'" + sStr + "' is yours.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "What about the 'Meifeng'? Did you think I let her to waste?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "I have a... special ship for you, Longway. A fast one. And even more deadly than Meifeng. It's war galleon, the 'Flying Heart'.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "You like xebecs, Longway. What about polacres? Especially this one, the, 'Torero'. Not built for regattas, of course, but she's pretty powerful.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "I must confess, I didn't think there would be a worthy use for this one day. What do you think of this galleon? The mighty 'El Casador'!";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "It's not the 'Meifeng', Lord Captain! What's happened with the Meifeng?";
			link.l1 = "Longway! " + sStr + " is in danger! And so is your sister! And you're being cranky about not having a ship like this?! Anybody would be happy with a ship like this! Take her under your command  and show van der Vink what your are capable of.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "Fine... I hope Heaven sends me good fortune. Just as I hope the same for you on Tortuga. Goodbye, Lord Captain.";
			link.l1 = "I'm sure of it. Goodbye, Longway.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Ahem, no, Lord Captain. Of course, I remember. Longway was just asking if you're ready to share her with me.";
			link.l1 = "I am. After all, van der Vink is as much involved in your sister's misfortunes as the other people on our list. So catching him is really important. I give you the command of the 'Meifeng'.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "I can't believe it... Thank you, Lord Captain!";
			link.l1 = "Ah, it's nothing. She used to be your ship, I will always remember that. Well, go on. Kill the son of bitch. I'm off to Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "I... I can't command THIS, Lord Captain. Longway still cares about his life, soul, and sanity.";
			link.l1 = "Ha ha ha, Longway! Come on, I didn't know you were so superstitious. But anyway, the curse has been lifted, so you have nothing to fear.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "Ah... but does van der Vink know that? He'll run like a frightened rabbit as soon as he sees that ship.";
			link.l1 = "You're right about that. Fine, we'll find something else for you.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Never sailed a polacre when captaining myself. She is interesting, but speed is the most important thing now, not power.";
			link.l1 = "That's true, but it's a polacre, after all. It may not be as fast as the 'Banten', but you can catch wind at angles they can't. Even more than the 'Meifeng' herself ever could. So take advantage of that.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Still... the 'Meifeng' was better... Too bad you let her waste, Lord Captain. Good luck on Tortuga.";
			link.l1 = "Same to you, Longway. Thank you.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "That it may be the most unusual galleon in the Archipelago, Lord Captain. I can handle it, but it is slower than the 'Banten'...";
			link.l1 = "Well, you're not competing with Joep in a regatta, are you?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Whatever you say. But the 'Meifeng' was better... Too bad you let her waste, Lord Captain. Good luck on Tortuga.";
			link.l1 = "Same to you, Longway. Thank you.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "I appreciate your concern, Lord Captain, but please hurry - we don't have much time.";
			link.l1 = "I know. But you don't want to go on a wild goose chase, do you? Alright, I'll find you a proper ship.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "We're almost there, Charles. Have you decided where to start? Maybe it makes sense for us to ask people on the streets...";
			link.l1 = "Maybe it does. But not for us - for me. You'll stay on board, Helen.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Charles, of course, I'm still uneasy about those scoundrels and what they have said, and it makes sense for me to stay under the protection of the crew... But you're heading into the beast's den alone doesn't make me feel any safer.";
			link.l1 = "I understand. But if things go wrong, it's much easier to flee alone, knowing you're safe. It's an order, Helen. Wait for me here and try not to worry too much.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "Here's Tortuga, Charles, alright. I can't wait to come knocking on some doors, asking what that fat donkey wanted from me...";
			link.l1 = "That's exactly why you're staying on board, my dear.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "No way! Do you think I'm going to let you go ashore alone?";
			link.l1 = "I think that if Levasseur decides to finish what his mercenaries failed to do, we'll have no chance of fighting back. I don't want to provoke him unnecessarily, especially since my target is not him but Joep van der Vink.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "So I'm locked up now, alright?";
			link.l1 = " I'm not ordering you, I'm asking you, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "What if something happens to you in some back alley of that shit island?";
			link.l1 = "Then I promise I won't play hero. And knowing you're safe will help me run faster. So wait for me on the ship, and for God's sake, don't go ashore, no matter what happens.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "Who are you? I doubt you walked across the beach just to chat.";
			link.l1 = "That's right. Charles de Maure. Rober Martene?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "The Charles de Maure? Shit, just don't get me involved in anything shady. Aye, that's me. So, what do you want?";
			link.l1 = "I was told you're friends with Joep van der Vink, and...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "Who told you that? I will spill their guts. Well, we know each other, that's all. I don't want any trouble because he crossed you.";
			link.l1 = "Heh, you're quick to give up on your friends...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "Don't think that. I'm not afraid of you. But why go to the trouble or even create it? I don't know Joep as intimately as you've been told. Are you looking for him?";
			link.l1 = "Yeah, sort of. I know he's already left Tortuga, but it wouldn't hurt to learn more about him - where he's been, who he's talked to. Can you help?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "It wouldn't help you anyway, so... why not? He was in a brothel. The brothel. I think you can afford it, so I'm telling you about it.";
			link.l1 = "A new brothel? Isn't one enough for you anymore?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "Well, not new, but not many people know about it. And only a few can afford it. I guess your time has come. But be warned - only doubloons are accepted. Slip silver, and you'll get a kick in the arse.";
			link.l1 = "I figured as much. And where did you say this brothel is?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "You know that building with the columns? That's the one. And what a hostess they have! Yellow-skinned, so good looking! Huh, I see you're already drooling, huh?";
			link.l1 = "Heh-heh, sort of. Thanks, Rober. No trouble today for you - you've been a great help to me.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "You're back at last, Charles! I couldn't find a place for myself, alright!";
			link.l1 = "I won't be long, Mary. I've got a little business to attend to... I won't keep you in suspense - it's Longway's business. I need to visit a local brothel.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "I knew I shouldn't have let you go ashore alone. Either you forgot to put your hat on, and your head got hot... Or you banged it, alright!";
			link.l1 = "Mary, listen to me. It's possible the owner of this establishment is Longway's sister. To be sure, I'd have to see her, but that's all I'll do. I can't do that without going inside. But I don't want you to think something you shouldn't.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "Are you sure you're not lying to me, Charles?";
			link.l1 = "Mary, look at it this way... Have you ever heard of a man warning his beloved about...?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Just stop right there, Charles, I don't even want to think about it. I believe and trust you. And I hope you won't stay there longer than you have to.";
			link.l1 = "Not a minute longer, darling, I promise. In and out, you'll see.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "Charles! You're back even faster than I expected. But what happened? You're not looking well... Did you find out anything about Joep van der Vink?";
			link.l1 = "Not yet. I've learned a few things, but to go further... I need to go to a... brothel. Not for what you might think, of course.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "A brothel? I didn't know these places offered anything other than the obvious.";
			link.l1 = "I need to chat with the owner, that's all. And it's not just any brothel. Rumor is - it's a very expensive establishment, for members of high society only...";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "Well, then it is just right for you, darling. Oh, I'm kidding. Still, I'm not thrilled you're going there. But...";
			link.l1 = "I promise I'm going strictly on Longway's business. It's quite possible the owner of that place is his sister. I won't be there long.";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "As you wish. You are not obliged to inform me about such things. I never promised you I wouldn't sleep with another man. And yet, I don't. Because it's something I take for granted.";
			link.l1 = "Under other circumstances, I would have taken you with me, but...";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;
		
		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "Thanks, but no thanks. Charles, don't worry. I'm not some stupid jealous girl. Well, maybe jealous, but not stupid. And I believe you. Stupid me!";
			link.l1 = "Thanks, Helen. I'll be right back.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "Oh, a new face in our establishment? Welcome, monsieur. Food, aged wine, a hot bath - all await you if you can afford to spend time with one of us.";
			link.l1 = "Thank you for your welcome, mademoiselle. But that's not why I'm here. I'm looking for someone...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "It is only with the heart that one can see rightly; what is essential is invisible to the eye.";
			link.l1 = "Beautiful. I've never heard those lines before.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "We're educated here, not just dolls. The hostess thinks it's essential to our establishment.";
			link.l1 = "The hostess! That's who I'm looking for. I heard she's yellow-skinned. Tell me, is it true? What's her name, by the way?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "It's true. But she's got better business acumen than many white women. Her name is Belle Etoile. But enough talk.";
			link.l1 = "Enough talk, you say? I'm here for the talk. I'll ask a few more questions and then leave.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "And what's the benefit in it to the establishment? They pay not for bodies here but for time. You want to talk? You're welcome. But money up front. And we'll whisper in the room, away from prying ears. I don't care what we do there - I don't care if we light candles and pray. A client once asked me to help him write a poem. Another to talk about his troubles, calling me his good friend. And a third - just to light candles, so that then...";
			link.l1 = "Well, I don't want to know - I've already heard something unpleasant recently. How much do I owe you?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "Two hundred and fifty doubloons. No bargaining. If we realize we're looking at a penniless poser, we throw him out with no regret. And if he's wealthy but greedy, we raise the price - he'll pay anyway.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "There you go, two hundred and fifty gold pieces.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "Whoa, this place is more expensive than that brothel in Jamaica. Can I come back later after I get the gold?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Good. Where shall we start? Dinner, with or without candles, bath, conversation?";
			link.l1 = "I don't have much time, so let's get straight to my questions. Lead the way.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Of course you can. Patience is one of the virtues of a courtesan. Throwing a beggar out is one thing. Letting a wealthy gentleman like you go and get his money, or even borrow it, is quite another.";
			link.l1 = "The virtues of a courtesan... Ironic. I'll be right back.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "Welcome back, monsieur! So, who are you? A wealthy gentleman or a poser?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Of course, I'm a wealthy gentleman, mademoiselle. Here is your gold - all two hundred and fifty doubloons. No need to count it.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "I'm still short, just bear with me.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "We don't count here. Hmm, some of the coins look bent and broken - the mistress won't like that much, but at least it's all real gold.";
			link.l1 = "What a... graceful person she is.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "That's right. Madam Etoile can be soft and caring, she can be strict, and she can be ruthless. That's why we don't count, by the way. The mistress isn't always paid immediately, but she always gets her due. If not in gold, then in blood. Any house of tolerance needs protectors and patrons. And ours match the establishment's status.";
			link.l1 = "I've paid, so lead the way.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "So, what questions do you have, monsieur? I'll try to satisfy your... curiosity.";
			link.l1 = "You know what interests me, mademoiselle - your mistress, Madame Etoile.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "What can I say about her? She remains a mystery, even to us. Although she cares about our well-being, health, and safety, she doesn't socialize or get close to any of us.";
			link.l1 = "Perhaps she doesn't like long conversations. Tell me, does she speak with an accent?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "No, what makes you think that? Just because she's yellow-skinned? She speaks pure French and several other languages. And she can hold an hour-long conversation on any topic with guests and potential stakeholders.";
			link.l1 = "You don't say. Interesting... Is she here now? If so, I'll just go in and see her and not waste any more of your truly... expensive time so you can get back to work.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "There isn't plenty to get back to - though our hostess' goal is to make this place the best in the Archipelago. An elitist place, where no merchant, nobleman, or just an educated person would be ashamed to come - because we offer much more than our bodies.";
			link.l1 = "But she's not very successful at it, is she?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "How to put it... She sees each of us not just as a commodity, as in simpler establishments, but as a project. Expensive clothes, medicine, education - she invests in each of us. And if we were in a big city in the Old World, she'd have succeeded! But here... Even a talented tradesman won't earn anything if the goods are so expensive that almost no one can buy them. Even if we lower prices, we are still destined to go broke someday.";
			link.l1 = "I am sorry to hear that. So where is your mistress now?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "We're having a good life here so far, I can tell you. Comes with a price of earning it and keeping up with her standards... As for the lady, she went to Espanola, to discuss the possibility of moving all of us to Port-au-Prince - after all, more trade routes converge there, and our trade won't stand idle and suffer almost constant losses there. ";
			link.l1 = "Is that so? Didn't Levasseur invest in this place to ensure its stability?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "Not too much. He came to us and said he'd only invest big if we went to his place from time to time. But the lady refused sharply. So much so that His Grace was taken off guard for a second. I've never seen her or him like that.";
			link.l1 = "Heh-heh, look at that. She seems to know... Brave, very brave of her.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "Know what? However, since we're talking so well, I'll tell you something else, but it's a big secret, so don't discuss it with anyone!";
			link.l1 = "Oh no, mademoiselle. I assure you, I'm not looking to harm your lady in any way. Please continue.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "I don't even know if you could harm her, because Belle Etoile practices fencing every day, and she has no worthy opponent in the whole city. In addition to Port-au-Prince, she's planning to offer Marcus Tyrex himself to invest! Or rather, to get a loan from him. Can you imagine?";
			link.l1 = "Yes, and I feel that today I'm going to have a very tough conversation with another woman who regularly practices fencing... Well, thank you for sharing, mademoiselle. Have a good day and generous clients.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Thank you. But what's your hurry? You've paid in full, and we haven't talked that long. Besides, there's something refined about you, monsieur. Something much more than the rare rich men who come to our house. Shall we enjoy each other's company for real?";
			link.l1 = "You know... what the hell? Why am I pretending and lying to myself like I don't want this? A chance with a woman like you is very rare.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Oh, I regret to say no, mademoiselle. I only came here to talk. Besides... I have someone waiting for me.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "As if that ever stopped anyone. In that case, you deserve respect, monsieur. I'm very happy for your 'someone'.";
			link.l1 = "Thank you again, mademoiselle. Goodbye.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Thank you. How about a hot bath together, for starters?";
			link.l1 = "Both hands in favor.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "That was a magical experience, monsieur. I didn't think a man could surprise me like that. You do know how to give pleasure to a woman...";
			link.l1 = "It depends on the woman.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "Do you regret it?";
			link.l1 = "Right now, definitely not. Goodbye, mademoiselle.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "Watch where you're going, poser!";
			link.l1 = "Watch your mouth!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "I was watching where I was going while you were counting crows.";
			link.l1 = "You could have gone around if you'd been looking, couldn't you?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "Why should I go around you?!";
			link.l1 = "I suggest we find out outside the city, who owes what and to whom.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "Mm-mm, no. I didn't know your Lordship was so disgusted by the unintentional touch of a mere man.";
			link.l1 = "Say again?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "Hmm, sorry. It was not my intention to push you.";
			link.l1 = "That's better.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "If you were half an hour late, Charles, I'd have our cannonballs smashing this filthy den to bits, alright! Did you find what you were looking for? Is that her, Longway's sister? Did you see her?";
			link.l1 = "Shh, Mary, don't talk like that. No, I didn't get to meet Chang Xing...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "Then what the hell took you so long?! What were you doing there?";
			link.l1 = "You have nothing to worry about. As soon as I found out everything I could, I left that place, just like I promised you.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "Just spit it out, alright!";
			link.l1 = "The owner isn't on Tortuga at the moment. The demand for her services is low here since she employs well-educated ladies in expensive clothes, and they only accept gold as payment...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "Did you pay them too?!";
			link.l1 = "They wouldn't have even talked to me otherwise. With that kind of approach, it's no wonder they don't get many customers. The madame has decided to move her trade to Port-au-Prince, hoping to attract a wealthier clientele. But she's obviously short on money since she's decided to approach Marcus Tyrex for a loan...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "Does he know her?";
			link.l1 = "We'll find out when we get to La Vega. And if we hurry up and stop wasting time with unnecessary chatter, we'll catch this Asian woman, whoever she is.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "It was unnecessary to go to that brothel, Charles. I'm sure we could have found all this out in the tavern or on the streets if we tried hard enough, alright.";
			link.l1 = "Next time I'll take you with me so you don't fill your pretty red head with rubbish, eh? Now, let's get down to business.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "Oh, I see I'm a little late, alright! Well, hold on, you scoundrel...";
			link.l1 = "Mary, what the hell are you doing here?! I told you to stay on the boat!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "So I wouldn't stop you from having fun with whores?! Don't even think about denying it, Charles! The crew saw you there, alright! How could you?!";
			link.l1 = "That's what I thought. I suppose I should have taken them with me, so they could see what I was doing - or rather, not doing - and not make a big deal out of it...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "You're accusing our boys of lying? After what you did yourself, you brute?";
			link.l1 = "I'm accusing them only of unparalleled stupidity. Without understanding the situation, you...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "Oh-oh, Charles, I don't think you and your whores would have liked how I understood the situation if I'd gotten to that hole in time. But you're lucky - I had row this fucking boat all by myself...";
			link.l1 = "They say hard physical labor clears your head of unnecessary thoughts. But you still have plenty of them, so you're rowing back too.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "I'm not moving, alright!";
			link.l1 = "Mary, I'm not going to have this conversation here in front of Levasseur's men. Calm down, take a look around, and make a judgment call. This is neither the time nor the place.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "To hell with you. I still have my things in the cabin... But don't think I'm going to work the oars again, alright! There must be something of a nobleman left in you!";
			link.l1 = "I'm a scoundrel and a brute, remember? I'll prove it on the ship, but I have to get there first. So your pleas are futile.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "You've got the whole crew laughing at you, alright!";
			link.l1 = "Well, maybe at you too. They haven't seen a spectacle like that in a long time. Now that your temper's cooled a bit, let me tell you what happened.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Charles, I've heard everything by now. I just have one question: was I not good enough for you? Is there something missing with me?";
			link.l1 = "It's impolite, but I'll answer with a question: have I ever given you any good reason not to trust me? Huh? I don't remember such a thing. So take a breath and hear me out. I couldn't find out much about Joep van der Vink except that he'd been to a brothel. Not the one near the 'Singing Crow', but another one near the pier. I didn't know about it before... unlike, apparently, our sailors, who got you up to speed. Although they wouldn't have been allowed to go there...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "What kind of brothel doesn't let sailors in, alright?";
			link.l1 = "A brothel where they employ silk-clad ladies who have more than just air in their heads. And their services are paid for exclusively in gold doubloons. It's not just anyone's whim, but the order of their mysterious mistress, Belle Etoile.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Mysterious, alright.";
			link.l1 = "It's not just that. She's Asian.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "Asian? The madam of the brothel on Tortuga?";
			link.l1 = "It could be Chang Xing. That's why I went there - I wanted to see her with my own eyes. That's all.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "What's she like?";
			link.l1 = "I have no idea. She wasn't there, so I had to chat with another... star.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "Was she Asian too, alright?";
			link.l1 = "No, she was white. She told me that Belle Etoile hasn't been doing so well lately, so she decided to move to Port-au-Prince. Makes sense, as the people there would be wealthier. The madam must be strapped for cash since she needs a loan to open a trade in Espanola, which she intends to take from Tyrex. So if we hurry to La Vega, we can intercept her before Marcus meets her.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "I don't give a damn about her or Marcus or anyone else, alright. Charles, just tell me one thing - have you been with any of the girls in her brothel?";
			link.l1 = "I don't need that, Mary. I've got you, the best girl in the world. I don't understand why you don't realize that.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "Actually, it's really easy to figure out the truth, alright, hee hee. If you haven't been with anyone, you must be full of energy right now. That's what we're going to check out now, alright!";
			link.l1 = "Mary, please..";
			link.l1.go = "exit";
			AddDialogExitQuest("cabin_sex_go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					notification("Excellent Health", "Medic");
					dialog.text = "(Excellent Health) Ugh... Looks like you weren't lying, Charles, alright...";
					link.l1 = "I have no need to deceive you, my dear...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					notification("Perk check failed", "Medic");
					dialog.text = "Charles, are you... are you serious?! What was that?";
					link.l1 = "Oh, that heat is doing me no good. Ahem.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Ugh... Looks like you weren't lying, Charles, alright...";
				link.l1 = "I have no need to deceive you, my dear...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "But that dinghy ride I won't forget for a long time!";
			link.l1 = "Ha!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "You've never complained about it before, have you?";
			link.l1 = "You try running around the bloody island...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "And the brothels, alright! Did you really...";
			link.l1 = "Mary, I'm sorry.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "What?! So you're...";
			link.l1 = "I'm not sorry for that. Shit. I mean, I wasn't with anyone but you, I told you. I just... couldn't ease my mind, that's all. It's hard to do that, you know, with the cannons of La Roche staring at you.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "That's a fine excuse, Charles. All right, I'll believe you. This time... But know that I'm still pissed at you, alright!";
			link.l1 = "I'll earn your forgiveness, I promise.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Well, lover boy, tell me what you found out. Was it worth risking my favor?";
			link.l1 = "I really can't tell if you're joking or being serious. It paid off - even though I didn't see the hostess with my own eyes. She is Asian and her name is Belle Etoile - a wonderful star. Not her real name, of course...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "And for that, you had to go to a brothel? You couldn't find that out at the inn?";
			link.l1 = "They don't really talk about this place in town. Why? It's a good question. You can ask Belle Etoile herself - she's gone to Espanola.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "Tortuga wasn't enough for her?";
			link.l1 = "The trade, apparently, isn't going well here. She doesn't employ ordinary harbor girls but richly dressed, educated ladies.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "And why would they do that?";
			link.l1 = "That's another good question. Anyway, our little bird has decided to fly to Port-au-Prince, de Mussac's fiefdom. But the loan for this endeavor was to be obtained from none other than Tyrex.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "I want this story to be over soon. Let's not waste any time and set a course for La Vega.";
			link.l1 = "That's what we'll do.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "You're a brave man, Charles, I'll give you that. Showing up so easily, with such a straight face, as if nothing happened.";
			link.l1 = "I suppose one of the crewmen blabbed? Without any context, of course. Because nothing really happened-at least not what you're thinking.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "I'm glad you didn't deny it, Charles.";
			link.l1 = "I was going to tell you everything, Helen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "Don't, Charles. The details don't interest me much. But the reasons do. Tell me, is there anything wrong with me?";
			link.l1 = "Let's start with the reasons. I found out there are two brothels on Tortuga. One is well-known. The other - people know about it, but few want to talk. It's owned by an Asian woman...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "Are you making this up as you go?";
			link.l1 = "Why the hell would I do that, Helen?! If you don't believe me, they'll confirm it at the place!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "First, you told me not to go ashore, so there's no way I can get there. Secondly, who the hell do you think I am?! I won't go near a place like that! Thirdly... just go on.";
			link.l1 = "Good. I decided to go there to see Madame Étoile with my own eyes. That was my only intention, damn it!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "I suppose. Did you meet her?";
			link.l1 = "No. She's gone to Espanola. Things aren't going well for her here, so she decided to try her luck in Port-au-Prince. There, the silk-clad, well-educated ladies who work in her establishment can bring her more profit than on Tortuga...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "Dressed up and educated? Whoa, what life can bring you. But you should like them just the way they are.";
			link.l1 = "Helen, stop it. I haven't done anything to earn your distrust.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "True. If you'd tried to deceive me, you wouldn't be so calm. But you should have warned me of your plans, Charles.";
			link.l1 = "You're right, darling. But I decided to save some time. My mistake.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "All right. What now, do we plan a course for Port-au-Prince?";
			link.l1 = "La Vega. Don't be surprised, Helen. Madame Belle Etoile isn't doing well. She needed a loan to move her trade to Port-au-Prince, so she decided to borrow it from Marcus. If we hurry, we can catch her there. So let's not waste a minute.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				Return_MaryOfficer();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				Return_HelenaOfficer();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "I can't believe that a prick like you and your rabble defeated us!";
			link.l1 = "You...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "Oh, you recognize me?";
			link.l1 = "Did we meet?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "What?! Are you fucking kidding me?!";
			link.l1 = "I can't remember all uncivilized scum I meet. You'd better tell us who sent you to kill us. Or maybe they just wanted to get rid of you?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "I won't say anything to someone like you. You think so bloody highly of yourself! Let's see if you can back that up again after our little respite here.";
			link.l1 = "Too bad. You're disgusting, but I could have just dropped you off on another island. Now all I can do is send you to the other side.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "Calling for me, Captain?";
			link.l1 = "Yes, mate. Report the damage.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "There's a violent storm. The ship is creaking and cracking; it's wobbling badly.";
			link.l1 = "Yes, I've noticed. Tichingitu, my friend. I and the " + sStr + " will go ashore. You stay in charge. Start the repairs immediately - until the storm dies down, it's no use going to the dockyard. Besides, we won't be here long.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "I'll make everything look better.";
			link.l1 = "Great, thanks. We're off to town without any worries then.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "Monsieur le Capitaine? It's an honor. But you usually call on Alonso at times like this. Is everything all right, if I may ask?";
			link.l1 = "Yes, everything's fine. But our Alonso is more about destruction, not fixing anything. In every sense of the word. How bad is the ship?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Alonso would tell you it's lousy, even if we're not going down. You mentioned repairs - shall we start them?";
			link.l1 = "Yes, do what you can. But don't plan on full-scale long-term work - we'll be pulling up anchor soon, right after I finish my business in town. Me and " + sStr + " won't be there, so in case of anything, make all decisions yourself. Listen to Alonso in everything.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "As you command, Monsieur le Capitaine.";
			link.l1 = "At ease.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "Greetings, monsieur! Welcome to Port-au-Prince.";
			link.l1 = "And good day to you, monsieur. Who are you, and to what do I owe this welcome? I wouldn't say I'm in the mood for a long conversation in this rain and after a storm.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "Oh, I shall not take up much of your time, Monsieur de Maure.";
			link.l1 = "Do I know you?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "Oh, no, but the whole archipelago knows who you are. Ah, where are my manners! Henri Thibaut, at your service. I am the messenger of His Lordship, Monsieur de Mussac. As soon as he spotted your ship, he ordered me to give you the warmest possible welcome, monsieur.";
			link.l1 = "Well, that explains a lot. Pleased to meet you, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "And the pleasure is mutual, Monsieur de Maure! Please follow me. It's not right for a man of your stature and his beautiful companion to be confined to this stinking tavern. His Lordship has assigned you a house in the city and has instructed me to assist you in every way. Please don't forget to convey his best wishes to His Excellency Poincy afterward.";
			link.l1 = "Actually, my errand is a discreet one. You know, Monsieur Thibaut, I think that...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. I rarely ask you for anything, much less interrupt you, but can we take advantage of their offer? I'm sick of getting wet in the rain. I'm also feeling nauseous and dizzy.";
			link.l1 = "Heh-heh, are you sure it's the rain?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "Bite your tongue, Charles! Anyway, I want to rest. On a big bed and with no waves.";
			link.l1 = "All right. We'll dry off, take a break, and then get right back to business.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "Can we take a break in this house? I don't feel well, and I'm also... tired, Charles. Alright.";
			link.l1 = "Mary, dear, I understand, but maybe we should go to the tavern. This whole thing smells bad, doesn't it?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "What could happen to me? This isn't even Tortuga.";
			link.l1 = "That's what scares me.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "Please? If anything, I'll set up a defense in the room-just like... back then, alright. You know me better than anyone, Charles, so you know I can handle it.";
			link.l1 = "All right, all right. Hopefully, this won't be like back then.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "I knew you'd change your mind, monsieur! Regarding your worries, I understand perfectly. But, you see, His Excellency Poincy and the governor are old friends, and therefore you are a welcome guest in our town, Monsieur de Maure!";
			link.l1 = "Oh, well... Well, then, take us to the house then.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "Certainly, monsieur! Follow me, please.";
			link.l1 = "Thank you.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Monsieur, the governor is waiting for you. He has asked you to go to him as soon as you can - he would like to speak to you in private.";
			link.l1 = "Does he already know that?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "Of course, he knows! That's why he's waiting for you. Let your beloved sleep sweetly while you go and see monsieur de Mussac. Some storm won't stop the famous Charles de Maure, will it? But His Lordship, as you realize, doesn't have much time to spare between appointments...";
			link.l1 = "Well, that's true, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "We'll show you the way, Captain.";
			link.l1 = "Oh, so I even have an honorary escort... Well then, lead the way.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "Lord Captain!";
			link.l1 = "Longway! To the ship! Now!";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "But I saw Chang Xing!";
			link.l1 = "What?! Where? When? Is she on your ship?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "No! Here in the city, Longway saw her from afar. No time to catch up - she's boarding a galleon that's just set sail!";
			link.l1 = "We'll catch up with the galleon! But tell me - have you seen " + sStr + " anywhere?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "No! Did something happen?";
			link.l1 = "Yes, something has happened! She's in danger! Have you seen Levasseur's nephew? Name's Henri Thibaut! Nasty, skinny, long-haired young man with a funny mustache!";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(in Mandarin) You don't need to talk about funny mustaches, Captain... (in broken French) I saw him! He and the mercenaries also boarded the same galleon.";
			link.l1 = "Let's give chase immediately!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Your ship is badly worn out, Lord Captain!";
			link.l1 = "I don't care! " + sStr + "'s life is at stake!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "My... 'Your Meifeng' will get us through!";
				link.l1 = "Oh, she will! Hurry!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "Don't throw us into a suicidal attack. Use the ship that's you provided me earlier!";
				link.l1 = "Good idea, Longway! Let's hurry!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			chrDisableReloadToLocation = false;
			Island_SetReloadEnableGlobal("Hispaniola2", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			pchar.GenQuest.AbordageInStorm = true;	//Разрешить абордаж во время шторма
			SetLocationCapturedState("PortPax_town", false);

			LAi_LoginInCaptureTown(npchar, false);
			AddPassenger(pchar, npchar, false);
			Return_LongwayOfficer();
			
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				AddPassenger(pchar, sld, false);
				Return_TichingituOfficer();
			}
			
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1 = "location";
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1.location = "Hispaniola2";
			PChar.quest.PZ_PoP_Pogonya.win_condition = "PZ_PoP_Pogonya";
			
			SeaAI_SwapShipsAttributes(pchar, CharacterFromID("PZ_ShipStasis"));
			AddCharacterGoodsSimple(pchar, GOOD_GRAPES, 300);
			AddCharacterGoodsSimple(pchar, GOOD_BOMBS, 200);
			AddCharacterGoodsSimple(pchar, GOOD_POWDER, 350);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 150);
			AddCharacterGoodsSimple(pchar, GOOD_RUM, 50);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 700);
			SetCrewQuantityFull(pchar);
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) / 2;
			AddCrewMorale(Pchar, 100);
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			
			//Вражина
			sld = characterFromId("PZ_RobertMartin");
			sld.nation = PIRATE;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				GiveItem2Character(sld, "blade_31");
				EquipCharacterByItem(sld, "blade_31");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				GiveItem2Character(sld, "pirate_cutlass");
				EquipCharacterByItem(sld, "pirate_cutlass");
			}
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			sld.ShipHideImmortal = 800;
			Group_FindOrCreateGroup("PZ_RM_Attack");
			Group_SetType("PZ_RM_Attack", "pirate");
			Group_AddCharacter("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetGroupCommander("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetTaskAttack("PZ_RM_Attack", PLAYER_GROUP);
			Group_SetAddress("PZ_RM_Attack", "Hispaniola2", "quest_ships", "Quest_ship_1");
			Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "You again... I knew I should have refused and let someone else take your girl.";
			link.l1 = "Where is she?! Tell me! No... Shut your mouth. You'll only talk in the hold, in shackles! You hear me?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "Her blade. If you don't start singing right now, I'll cut you to pieces with it.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "You... you're out of your goddamn mind!..";
			link.l1 = "Now you're about to see my unpleasant side...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "That's it?";
			link.l1 = "I ask you again! Where is " + sStr + "?! Where's the Chinese woman?! Where is Henri Thibaut?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(spits blood) You hit like a girl.";
			link.l1 = "You bitch! I'll beat every word out of you!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "Pathetic. Although... I'll say it. Why not, ha ha. They're all on the other ship, right on the way to Tortuga. You're too late.";
			link.l1 = "If even a hair falls off her head...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 1.00, 5.13, 7.23);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "And whose fault is that?! You killed Edgardo Sotta! For the first time in his life, Levasseur wanted a taste of a girl and he didn't get it right away! First time our crew failed his direct order! The man can be as scary as the devil...";
			link.l1 = "Then I'll be scarier than the devil himself and give you a little personal hell if you don't tell me what I want to know, do you hear me?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			else link.l1.go = "PZ_RobertMartin_Helena_1";
			//if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "I don't give a damn about your sorrows - I'm a dead man anyway, judging by those crazy eyes of yours. I'll give you some credit though, de Maure.";
			link.l1 = "What the hell are you talking about?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Levasseur favors blondes. But I've always liked redheads better, just like you, hehehe... What a spicy one you've got!";
			link.l1 = "You're right, you won't survive the day...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "I don't give a damn what you want. But let me tell you  what Levasseur wants - pretty blonde girls, ha ha ha ha ha ha ha ha ha! First, he has her...";
			link.l1 = "A-AH!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Squealing and beating up an unarmed man - pathetic. That's all you can do. You've lost, de Maure! Do you want to know when you truly lost, you pathetic cretin?";
			link.l1 = "Enlighten me. But if I'm not impressed, you'll lose a finger. Or an ear. Or those rotten teeth from your stinking mouth. Or maybe something else. The choice is yours...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "Heh-heh, I've got something you don't. Do you think Levasseur didn't know what that old fox Poincy was plotting against him? Francois knows everything, everything! Even the Brotherhood barons don't dare challenge him. And you, smartass, you did. But...";
			link.l1 = "But what?! Don't you fucking dare to drag this out!! Start talking, or I'll start breaking your fingers one by one!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "Ha-ha, brave Captain de Maure! But all right. Me, Henri, and the yellow-skinned woman decided it was best to destroy you here. And blame it on Tyrex, so the old fools in the Brotherhood would start another war among themselves! Or maybe de Mussac - he's been sticking his nose where it doesn't belong... You know, everyone laughed at me for sailing a galleon, but it weathered the storm with ease, unlike your piece of crap.";
			link.l1 = "Enough! Where does Levasseur keep his victims?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "So you know about his secret place, the dungeon? Oh yes, he is the real dungeon master, ha-ha-ha! But can you really challenge him? I doubt it. You want to defeat the beast? Then become the beast yourself. See if you can break me like Francois breaks those girls. Like he'll soon break yours...";
			/*if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Alo-o-on-s-o-o!!!";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}*/
			link.l1 = "Alo-o-on-s-o-o!!!";
			link.l1.go = "PZ_RobertMartin_23";
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "I told you not to bother, dammit!..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "Allow me, Lord Captain.";
			link.l1 = "Longway? Allow what?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "White men torment the body. My people know that one needs to torment a wretched soul first, drive mad by a little constant pain. You can't just take and torment without preparation. It always takes a special approach. Here you need... Lynchy.";
			link.l1 = "Lynchy?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Yes, Lord Captain. Death by a thousand cuts.";
			link.l1 = "Are you mad?! Cracked your head? What death are you blabbering about?! I need to make him talk first!";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "Longway knows, Lord Captain. He knows what to do. This bastard's going to tell me everything. Give me time...";
			link.l1 = "Time? Time?! All right... Do it. Just please, I beg you, get it all out of him, everything!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_LongwayKazn_4", 1.5);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Kill me, just kill me, please... What more do you want from me?!";
			link.l1 = "Nothing more. Shut your mouth and die.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Clean shot, Lord Captain. I told you it would work.";
			link.l1 = "Yeah. Good job. So, to the dungeon then. Hoist all sails! Set course for Tortuga. And God help this bloody city if a single hair falls from " + sStr + " head...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "39");
			
			LAi_SetPlayerType(pchar);
			npchar.greeting = "Longway";
			Return_LongwayOfficer();
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			pchar.questTemp.PZ_FlagMartinInfo = true;
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Dios mio... I've never seen or heard you... like that, senor Captain.";
			link.l1 = "He's all yours, Alonso! Go ahead, show me what the Holy Inquisition does to Huguenots and their minions... And I'll watch... Then you can do whatever you want with him.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Aye aye, senor Captain...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "It won't take long, senor Captain...";
			link.l1 = "Do it, for heaven's sake!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			//LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Get up, you piece of shit. Get up, I said!";
			link.l1 = "Is he dead? Dead?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "Looks like it, cap...";
			link.l1 = "What the hell did you do?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "Who knew this oaf would turn out to be such a weakling! He soiled his knickers too, the filthy scum! I'll be damned, the fire was unnecessary...";
			link.l1 = "You... Well, overboard him to the fish. Set course for Tortuga. If need be, I'll take her apart brick by brick - first La Roche, then... Then God help me if I don't find her alive...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "38");
			
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_Norman1":
			dialog.text = "Finally. This throne is mine now. On this rock I will build...";
			link.l1 = "What the fuck... Seriously?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "... my Church. I am now the Pope of Rome. Do not swear in the House of God!";
			link.l1 = "And here I thought... Well, Your Holiness, would you kindly tell your faithful where the "+ sTemp +" is now?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "He's off on a holy quest. A new crusade, if you will. He's going to take the money from the wicked and bring it to me.";
			link.l1 = "To you, right. Did he mention when he'd be back?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "In a month. Maybe a little later. I'm waiting for his return, along with the rest of our flock.";
			link.l1 = "So he really is at sea. I'd better leave before I catch whatever you've got.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "I will cleanse them all in the holy flames...";
			link.l1 = "Your head could use some cleansing...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "with Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "Charles! What can I do for you?";
					link.l1 = "Hello, Helen! I want to talk to "+ sTemp +". Is he upstairs? Or is he in the tavern?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "Charles! And... Ah, what a nice surprise. What can I do for you two?";
					link.l1 = "Hello, Helen. Where's "+ sTemp +"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting() + ", Charles. What brings you here?";
				link.l1 = TimeGreeting() + ", Helen. I'm looking for the "+ sTemp +". Do you know where he is?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "He's out, but I'm afraid he's away for a long time - out to sea, to be precise.";
			link.l1 = "Damn. Did something happen? Did he say when he'd be back?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "He didn't, but it's nothing serious - he's got a good lead, as usual. He generally returns in a month, two at most. I know how it is, sometimes I miss the ship's deck myself...";
			link.l1 = "You can always go to sea. It would be nice to do it together sometime - you on the 'Rainbow', me on the...";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "It would. But your... girlfriend might not appreciate it. And I don't want to be the third wheel.";
			link.l1 = "Ahem, sorry, Helen, I didn't mean to offend you. Thanks for the chat. See you later.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, you're back. Is there anything else I can help you with?";
			link.l1 = "No, thank you, Helen. Just wanted to check if "+ sTemp +" showed up.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "I'd be surprised if you came looking for me. As for "+ sTemp +", he's out at sea.";
			link.l1 = "Oh, really? Did he tell you when he'd be back?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "Apparently, he's tired of running this cesspool and have to remind himself he's still captain of a ship. Not the first time. He usually returns in a month, maybe a month and a half.";
			link.l1 = "Damn, so the barons don't always sit still like that? Thank you, Helen. Goodbye.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+ sTemp +"'s still not back, Charles";
			link.l1 = "I see, just checking.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "He's a free man, isn't he? He can go to sea whenever he wants.";
			link.l1 = "Of course he can. So, where is he?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "But Charles, if he's not on the island, he's gone to plunder the Spaniards then. And now, if you'll excuse me, I have much to do. Check in from time to time - usually, the "+ sTemp +" returns in about a month, sometimes a bit later.";
			link.l1 = "Fine, Helen, thank you. We'll keep busy.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "I'm not in the mood right now. Maybe come back some other time, Charles?";
			link.l1 = "Sure, Helen. Sorry to bother you. Take care.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "We're in position, Lord Captain. Do you remember the way?";
				link.l1 = "Of course, Longway. Let's just hope we don't lose it in that cursed dungeon...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "We're in position, Lord Captain. Do you have a plan?";
				link.l1 = "I'm still working on it... Why, do you have something in mind?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Well, I reckon if we rush to Chang Xing...";
			link.l1 = "Longway... I understand how much you want to see your sister, but " + sStr + " is in mortal danger right now, and that's not just a figure of speech! You need to understand that saving her is the first priority!";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Lord Captain, I doubt you truly understand, what I've been going through all these ten years. What I am going through right now.";
			link.l1 = "You know, in a way, I do. My brother is being held in prison. And although they haven't harmed him yet, at any moment they could do whatever they want to him.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "But where would you go if it was only lady " + sStr + " who needed rescuing?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "There is one place... one person... But don't trouble yourself with that, Longway - I have to handle it myself.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "In truth, I don't even know where to go. If I carelessly snoop around everywhere, I'll attract attention, and then " + sStr + " is definitely done for. So... I just don't know.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "What? Why?";
			link.l1 = "They won't just let you in there - it's high society, damn it. So, I'll go alone. In the meantime, you head to your sister. I'll join you as soon as I can. Good luck, Longway!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "Aye! Thank you, Lord Captain. And good luck to you too!";
			link.l1 = "Oh, thank you - I need it badly today. We all do.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Lord Captain...";
			link.l1 = "Never mind. Let's go to your sister, Longway. If we split up now - we are dead. Let's hurry to your sister and find out where Levasseur's lair is. Then we'll go together again - I need all the help I can get right now. I hope we're not too late.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "We won't be late, Lord Captain. Let's not delay any longer or waste time arguing. Let's go to Chang Xing!";
			link.l1 = "You're right, let's hurry.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "Where the hell are you going? Do you even know where that door leads?";
			link.l1 = "I know perfectly well. I'm going there on business, not out of idle curiosity or to steal.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "What business? Madame Levasseur isn't available at the moment. Besides, she's a married woman - it's not right for people to be hanging around her place.";
			link.l1 = "Married, alright. But she does have receptions from time to time, eh? Including private ones. This is one of those times. She's expecting me, and I'm in a hurry.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "She would have warned me if that were the case.";
			link.l1 = "I'm a special kind of guest - the kind that doesn't need announcements.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "Aye, the kind of guest that'll make His Lordship order me shot. Or the Lady herself will have me skinned.";
			link.l1 = "I've been a guest of Madame Marceline before. I assure you, nothing will happen to you afterwards, soldier.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "But of course, staying blind and letting everyone in - that's the job of the city guard.";
			link.l1 = "I don't have time for this, you stubborn mule...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "You...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "Oh yes, madam. Your knight is pleased to meet you again. I see you're surprised to see me. Is the joy of this meeting... not mutual?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "Yes, I did. I realize I may not be the most handsome or worthy man on this island, as you mentioned during our last meeting, but at least you know I'm an honest man. Hear me out, madam - I won't take up much of your... precious time.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "Hush for God's sake, stop with this screaming, madam. I'm not here to get even with you for deceiving your knight and running off with the dragon's treasure. And I assure you, if I wanted to kill you, I'd just shoot you and run for my life. This is Tortuga afterall! But I think you already know that would be beneath me.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "Oh, no! I just thought that... Well, it doesn't matter! You see, evil tongues are spreading dirty rumors about me - a poor woman who, even if she wanted to, could neither harm anyone nor defend herself against enemies. Besides, it's been so long... I thought you came to me in bad spirit, and not with good intentions. I'm glad to be wrong. It's hard to live when you're surrounded by ill-wishers.";
			link.l1 = "How could I? Even if I heard something like that, I wouldn't believe a word of it. But you're right - I didn't come here just to see you. Though I'm glad I did. I know this will sound unusual, but... this time your knight needs your help, madam.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "And you're much more sensitive than I thought you'd be. However, you're not without fault, Monsieur de Maure - I expected you to be more... refined. In fact... either you've always been this way, or the Archipelago has already corrupted you. You should re-learn how to speak to a lady. But you're right - you're an honest man, albeit... simple.";
			link.l1 = "And you are a proud and vindictive woman. Your eyes, words, and... actions reveal as much. So if anyone will understand me, it's you. Just as I once understood you. So let's not dwell on the past any longer. Can you help me, madam?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Oh... I admit I was unkind to you at the time. But only because I wasn't completely sure of you, nothing more! Would you have taken all the diamonds away from me? Or brought my husband there, saying you'd learned from our servants that I'd stolen from him, denying your part in it? After all, everyone is looking for his favor, not a poor woman like me... Now I realize I was wrong about you. Please accept my apologies... my knight.";
			link.l1 = "I don't know now whether they are sincere or not. But it doesn't matter. I need your help, Madame Marceline. It's a matter of life and death. Please don't refuse.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "My help...? I'm certainly not the last woman in town, but my influence isn't as great as you all think. I'm a queen who reigns, not rules. But I will listen to you. What can my humble persona do for you?";
			link.l1 = "I realize this is an unpleasant subject for you, but I'm looking for your husband, madam, and as soon as possible. The fact is...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "Is this a joke? He's not at the residence at the moment? Then he's away on business. I can't help you, Monsieur de Maure.";
			link.l1 = "You averted your eyes. You know. I know too. I just need to get there. Please don't pretend this is the first time you've heard of the dungeon - you're too smart not to know.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "Oh, I feel like this conversation is going to add another gray hair to my head. As if I don't have enough first wrinkles already. What on earth are you doing to us all, Francois...";
			link.l1 = "A gray lock will only add to your nobility and won't take away your beauty. But a good, innocent girl has fallen into your husband's hands. And now she risks losing her beauty, her health, and even her life!...! You know what happens to those who get trapped there. Please, madam. Marceline... Help your knight.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "Not really my knight anymore, right? Come on, I'm not stupid. But... I'll help you, de Maure. After all, it couldn't go on forever. And one day it would have gone public. What's important to me now is to get out in time and in the right way. And... I can't condemn you to eternal suffering caused by what my ‘husband' will do to your... acquaintance.";
			link.l1 = "I may no longer be your knight, madam. But neither have you been my lady from the beginning. However, I will be grateful to you for the rest of my life. So where is this place?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Well, I'll take you at your word, Charles. In the city dungeons. There is a large barrel in one of the cul-de-sacs, and next to it begins a passage that leads to the lair of this fiend. I didn't look inside. I only followed him once, a long time ago. And I was frightened when I heard the inhuman screams of those poor creatures.";
			link.l1 = "You have saved many lives today, madam. Not only my dear one, but all those who might have fallen to your husband in the future. Thank you.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "Ah, leave me with these empty words, monsieur. You have asked a great deal of me. And I took a great risk. Try now to make your new quest into the dragon's lair a success... my knight.";
			link.l1 = "I'll do my best. Goodbye, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "So, you're a bandit, monsieur...? We don't hire new girls like this; we all came here voluntarily. I'm going to have to ask you and your... accomplice to step out. And I'll make sure this girl gets treatment - otherwise, I'll report you to the authorities!";
				link.l1 = "We're not bandits. But this girl is a match for any of them. She doesn't carry a blade for show. She's just wounded. This man is a friend of mine and your mistress's brother too. So, let us see her.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "Nice to see you again, monsieur! But you know we don't accept guests... of low class here. Even if they're vouched for and paid for. Especially yellow-skinned laborers or negro slaves. I'm afraid your friend will have to leave.";
				link.l1 = "Don't say that in front of your mistress. She's yellow-skinned too. And this is not a laborer, but her brother. You wouldn't interfere with a family reunion, would you?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "It's getting worse by the hour. First the mad yellow laborer and now you. No, monsieur, we don't pay for the girls who are brought to us by force; they are all here of their own free will.";
				link.l1 = "I saved this girl, and she will never work in a place that is beneath her . A laborer, you say?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "Oh monsieur, what bad timing! We're not accepting any more guests today - you can see for yourself what has happened here.";
				link.l1 = "That's why I am here. It was a yellow-skinned man who organized all this, wasn't it?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "Yes, monsieur, a laborer! We could hardly understand what he was saying! This ragamuffin burst in and demanded to see the lady. He assured us he was her brother. We called for men, but...";
			link.l1 = "That's no obstacle for him. What happened then?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "As it turned out, he wasn't lying. The lady came out to us and recognized him. In fact, they are still talking in her luxurious place.";
			link.l1 = "Who knows what's in his head, though. We're going in there - we'll save her if we have to. Don't make a fuss - it'll destroy the reputation of the place.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "That's right, monsieur. He said he was the lady's brother.";
			link.l1 = "And you didn't let him in...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "Of course not! The lady is exquisitely dressed and speaks without an accent, unlike that laborer. We tried to chase him away, and he put down all the guards, can you imagine?!";
			link.l1 = "I can easily imagine. And where is he now?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "He and the lady are still talking about something, but we can't understand what it is - probably in their own language.";
			link.l1 = "I'll go to them. Perhaps your lady needs help. Don't call the guards - if it goes public, no one will ever come to your door again.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "A brother? The mistress is dignified, which is more than I can say for this ‘brother' of hers. No need to mess with her head or try to swindle her with this laborer. Take him away.";
			link.l1 = "I told you they lost each other a long time ago. He's just less fortunate. We'll pay the establishment ourselves for our time. Alert the mistress now.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "She has nothing to be alerted about with you. And I don't like your persistence. Boys! Throw that laborer out! And his misguided master, too!";
			link.l1 = "Damn it! So much arrogance for a courtesan!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "No way! To have the mistress alone with all this strange company of yours? Only if you go there alone, monsieur. And your... friends will be waiting outside - we have a decent establishment here.";
			link.l1 = "Why are worried about her? Everyone knows she's one of the best swordsmen in Tortuga. And my friends are more decent than most people in this town.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "Boys! There's a wounded bandit and a dirty laborer in here! They want something from our mistress! Deal with them!";
			link.l1 = "What dedication, damn it...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "I take it you're Charles de Maure? And this... Oh.";
				link.l1 = "And you must be Belle Etoile. Or should I say Chang Xing? And yes, this is your brother. He's been looking for you for over a decade. He and I have many, many questions for you. And not a lot of time.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "My goodness, you survived. You've got a pretty good defender, even if he was a little late. Better than the one who apparently considers me his protector and is now standing next to you. Heaven favors you, my dear girl.";
				link.l1 = "I can see that you know. That's even better - no need to explain. But tell me, what are you smiling at, Chang Xing? You enjoy watching other girls suffer, don't you? You sell them after all.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "Charles de Maure, right? I heard you wanted to see me. So, what troubles you? Didn't like the service at our establishment the last time you were here?";
				link.l1 = "I just came from another establishment of yours, Chang Xing. "+ sStr +", my lover, is dead. And I know you played a part in it too.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Chang Xing... It's been a long time since I've heard that name. It's been a long time. White people... you're always in a hurry. What about a leisurely family reunion? I don't care, though. I stopped relying on other people years ago. Why don't you say anything, my brother? Aren't you happy to see your own sister? You've been looking for me so relentlessly afterall.";
			link.l1 = "We have other urgent and more important business to attend to. Talk to your sister, Longway. But remember where we have yet to go. We need to hurry. And I have questions for her, too.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(In Mandarin) Longway, huh? Well, aside from the name, you haven't changed much... Chang Tu.";
			link.l1 = "(In Mandarin) But you have changed a lot, sister. What happened? Your gaze used to be as warm as the midday sun. Now it's cold and expresses nothing but contempt. And your voice? I used to love to make you laugh and listen to those silver bells ringing... Now it is colder than a Goango in winter. And you wear their clothes. And you sell the women yourself, though you were once kidnapped by Fermentelos.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "You come to lecture me, even though you once worked for Rodenburg, one of the archipelago's biggest scoundrels? You think I didn't know about you? I always knew. It's not for you to judge what I've become and why, my misguided older brother.";
			link.l1 = "So let me find out, Xing! And tell me. If you knew I was on the Archipelago, why didn't you want to meet me after all these years? I've devoted my entire life to searching for you...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Because neither you nor Heaven protected me from the most terrible of fates. Then I realized that no one in this world needs anyone else. We can only rely on ourselves. Well, I'll tell you if you want to know. But I'll speak in his language. I'm sure he'd like to hear it too. You understand French, don't you, Tu?";
			link.l1 = "(in broken French): Yes, I speak that language.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ha ha ha, oh, Heaven! Your accent is terrible. It's not your fault, though - French pronunciation and writing are indeed difficult.";
			link.l1 = "You laugh different now, sister...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			Return_LongwayOfficer();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "My dear brother wants to know what has happened to me over the years. I think it would be good for you to listen too - as you said, you have questions. So don't worry - I'll tell you all about it in French.";
			link.l1 = "Tell me only the gist of it - when Longway told me his life story, it took a good few hours. And I am now in a hurry.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "You'll be patient. I kept it all to myself for more than a year. And if you interrupt, I won't answer any of your questions.";
			link.l1 = "All right... Then go on.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "Where are your manners, Charles de Maure? I was told you were a man of excellent manners and a model ladies' man. Just rumors, but in reality... a flop? That's what I thought. And you're wrong - I hate all men and women equally. In fact, I don't trust anyone, I don't wonder, I don't expect anything. I'd gladly crush your testicles if I could get my hands on you. But hearing my real name after all these years was a little... refreshing.";
			link.l1 = "I'm a ladies' man for ladies, not witches like you. And anyway, what did you expect, considering you're involved in tormenting the person I care most about? I can barely contain myself from doing something to you, too. Not the least of which is for his sake. Longway is my friend. And you are his family. He's been looking for you for over a decade. And he deserves to talk to you.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "How sentimental. And how sad that I don't care. But you're not going to get away that easily now, are you, Tu? Not for killing you and all of you for being late once. But knowing... I guess you do deserve to know. You've known me when I wasn't like this, brother.";
			link.l1 = "No matter what happened to you... you always had a choice, Chang Xing.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "You're still young and don't know how the world works, Charles de Maure. There's only one real choice in life: live or die. I think it would be good for you to know everything, too. So I'll tell my story in French. You speak it, don't you, Tu?";
			link.l1 = "With an accent. But he understands it very well. You may begin.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "And where have you been all this time? Espanola's only a day or two away. Her death is your fault, too. And you. You're more than a decade late. Our saviors, our protectors. The sooner a woman learns to defend herself, the better. Some do it in time, some don't. And someone doesn't have enough brains to come to it.";
			link.l1 = "Be careful with every word you say next. I still haven't torn you to pieces just for my friend, your brother. You have no idea what he went through for you.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "I highly doubt he's been through anything remotely similar to what I've been through.";
			link.l1 = "So tell us.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "Well, what can I say, I was young, stupid, and naive back then. And intolerant. Did Tu already tell you about how I was kidnapped by Oliverio Fermentelos after he killed my parents and me?";
			link.l1 = "That's right.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "He courted me and confessed his feelings, but I rejected him. And that's when he slaughtered our family and stole me. And then...";
			link.l1 = "I can guess.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "I wish you could. Then he confessed his feelings to me again, hot and in tears, saying that it was the only way, because my family would never let me go with him.";
			link.l1 = "Madness...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Heh, a word to describe my whole life since that then. I rejected him again. And it went on like that for a while. But clearly, it couldn't last forever, because I was completely at his mercy.";
			link.l1 = "So it did happen?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Of course. He took me by force, roughly and mercilessly. Not that it ever bothers rapists, but hadn't he earlier tearfully confessed to me his great love? Pfft! The love was gone apparently. And all this went on and on every day like it was a routine. At first, I shouted and resisted, but then I stopped - what was the point anyway...?";
			link.l1 = "But Fermentelos got what he deserved, and you ended up here. How did that happen?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "Well, pretty soon he got fed up with me. It's funny, isn't it? He killed mine and Tu's parents, stole me, dishonored me regularly, only to discard me at the end. He came to this Archipelago and sold me to Levasseur as a slave.";
			link.l1 = "I wouldn't wish that on my enemy. So how did you survive? And end up free in the first place? From what I've heard, Levasseur never let women out of his hideout. He always got rid of them.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "That's the way it is now. Levasseur was different then. No, he was always an animal. But at first, he occasionally kidnapped local young colonists, raped them in his basement, and got rid of them almost immediately to avoid paying for their silence. Only rarely did he keep them longer than a few days in those years. With me, on the other hand, it was different from the beginning.";
			link.l1 = "Because you were a slave, right?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "Exactly. Levasseur's main desire wasn't just physical pleasure. And not even a momentary feeling of power over his victims - after all, he has it over the whole island. But...";
			link.l1 = "... the pleasure of watching them break - their will, their looks, their voice, their behavior.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Yes. I see you did your homework, Captain. But in that respect, I was no fun to him - Fermentelos brought me already broken. And Levasseur didn't consider me beautiful - he doesn't like Asian women. You know, for some reason this has affected me so much - I realize I'm attractive, but I don't think I'm truly beautiful. And I don't believe it when people tell me that. Even now, when I exercise, wear silks, and spritz myself with fine perfume. Not that I need my tormentor's approval, but...";
			link.l1 = "Well, then I'll repeat my question again - how did you survive? As soon as he gets bored with a woman, he gets rid of her. With you, he was bored from the start, as you say.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "I guess the fact that I bored him from the start had an effect. And the fact that I was a slave - I couldn't go anywhere or say anything. Slave girls have been treated like that for thousands of years. He started thinking about how to make the time he spent with me ‘fun' for him.";
			link.l1 = "I guess that's how his addictions were born, in their current form.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Exactly. At first, it was beatings, spitting, and other humiliations. And mockery - both of my personal appearance and my origin, my blood. And then came the first tortures - knives, tongs, a frying pan... That's why I wear such closed clothes - my whole body is scarred, burned, and mutilated. And that's why I never plan to undress in front of a man again. Ever again. Then I finally realized what I should have realized back when Fermentelos kidnapped me.";
			link.l1 = "What was that?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "That I should no longer be a helpless puppet. On the contrary, I should be in control of my life. With me, it was the case that a woman can only change her life in some way by controlling the men around her.";
			link.l1 = "I wouldn't say that Levasseur can be controlled.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "And you wouldn't be wrong. But it is possible to influence him carefully. Levasseur equally hates both complete obedience from the start and arguments or pleading. So does flattery - apparently realizing what a pig he really was. This I realized at once, at quite an agonizing cost. But, when he was satisfied with everything after another evening of torture and violence, it was possible to talk to him gently. I may not be of noble birth, but I'm not lacking in intelligence.";
			link.l1 = "And what did you talk about?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "I piqued his interest. Suggested ideas for torture, advised what torture devices are best not to use, and which ones are worth starting with. At first, he tried it all on me, of course. But then... he started to respect me, in his own twisted way. What's going on in his head? I tried to find out how he got like that, but he beat me half to death again. Then he brought in a personal physician.";
			link.l1 = "That's even more strange and disgusting than what I've already heard about him.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "He no longer demanded that I give myself to him. He called me a pupil. But he always said that as his project, I was a complete disappointment. I guess to keep me on my toes. So he started teaching me fencing and languages. Although he kept me in the basement, it was me, not his wife, who got all the expensive dresses.";
			link.l1 = "A project indeed. You can see a clear parallel with the way you run the place.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "I hadn't thought of that, hmmm. And I don't like your parallel, because I don't torture my female employees. And I don't let my clients do it. Even though I hate those sluts and envy their beauty. And I have nothing in common with that pig, remember that.";
			link.l1 = "So how did you get this brothel?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "From Levasseur, of course. For some time, he kept me at his place. From time to time, even asking for advice on how to break this girl or that. After all, I was special to him, even if he'd never admit it. I was the first. I saw everything.";
			link.l1 = "Who learned from whom, again?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "I'm not like that! I hate with all my soul anyone who had everything on a platter handed to them! It's not fair! This brothel was my idea! My workers are the daughters of merchants, officials, and noblemen who sometimes fell in with Levasseur. I asked him to give them to me. Torture and humiliation in a secret cellar is one thing. But the public activities of a courtesan for the likes of them are quite another!";
			link.l1 = "I wouldn't say that your female workers look so humiliated, miserable, and broken.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Because they know what Levasseur or even I will do to them if they even make a peep. But you're right in part, of course. The wine, the food, the silks, the lack of daily torture - many of them began to see me as a savior. Damn fools! Only a few of them are not happy to be here. Some of them he gave away with a heavy heart. And he'd chuckle, saying I could always return any of them to him in exchange for solving my place's money problems. But I always said no. At least that way they'd bring back the gold instead of dying in the cellar for nothing. Would be a way out too easy for them.";
			link.l1 = "What a pity that not everyone felt humiliated, changing the cloisters worse than the Holy Inquisition to a golden cage like your brothel is...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "You judge me? I wanted not just to survive but to build a successful trade. Albeit unknowingly, Levasseur was grateful to me. Even though I was no longer a slave, he couldn't let me go. I was still forced to work for him and help his henchmen. Especially his scrawny nephew, who drooled over me every time he saw me. But wouldn't dare attack me or speak to me in a bad manner. Disgusting. You know, even though he called me a disappointment, I was more useful than Thibaut and Martene put together. I accompanied them quite often on his orders, as I did then in Port-au-Prince.";
			link.l1 = "That all explains a great deal...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "That's right. Listen. I didn't torture your lover. Just as I have not tortured any girl with these hands, even if I sometimes gave advice to Levasseur. But while we're on the subject...";
			link.l1 = "What?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "As you may also know, Levasseur sometimes demands to bring him a certain girl who was glimpsed in Tortuga, and then she left the island. Or someone would surprise him and bring him a stranger to earn his favor, as was the case with me. Kidnapping your beloved was my idea.";
			link.l1 = "What did you just say...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "At first, we were considering capturing that blonde who used be so close to you. But since she is untouchable now, and because we have already promised him a girl, you redhead had to do.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "I heard rumors about your gorgeous companion who never leaves your side. Considering Levausser's love for blondes, I had very little trouble selling him this idea.";
			dialog.text = "Sotta, his mutt, was supposed to bring him the mulatto, Lutter's wife. But you killed Sotta, so - no mulatto for the big man. Levasseur was furious. Everybody got hammered - Thibaut, Martene, even me. I don't know who made me more angry: him, because he beat me up again, or you, who caused it... "+ sStr +"";
			link.l1 = "So it's not even because of him... You did this.";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "I don't even hope for your forgiveness, and, moreover, I don't need it. If you want blood, you'll get blood. And you will regret it very much. But I will not refuse understanding. I could use it for the first time in long ten years. All I ever did was just doing my best to get out of Tortuga one day. Do you have any questions for me, Charles de Maure?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "But you were involved in the kidnapping. And you know where Levasseur keeps his victims. Tell me where it is. And if the worst hasn't happened - I'll think hard about not retaliating against you.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "Well, that's all coming together finally...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "I do know because I was there. And if you have the impression that I am mutually and unhealthily attached to him - then you are sorely mistaken. I'd be happy to see someone put that pig on a spit.";
			link.l1 = "I don't have time, Chang Xing. Where is it?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "You know the local dungeon under the city streets? That's where you're going. In one of the dead ends is a large wine barrel, and next to it begins a secret passage to his pleasure room, as he sometimes calls it.";
			link.l1 = "Well, that's all coming together finally...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Good for you. Now get out. As much as I wanted to speak out after so many years, the realization that you know all my secrets, know what was done to me - it's disgusting. The sight of you only makes me angry now. Oh, and Tu stays with me.";
				link.l1 = "Why is that?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "Maybe because I'm his family? And because I see what he's like with you - a beaten-down, miserable mumbler who hasn't even had time to fully learn the language and start speaking properly. Yet he told me you two were friends. It's clear how you've influenced him. At least I'll make a man out of him.";
			link.l1 = "And are you truly happy with yourself? What will you turn him into? A cruel, bitter creature that trades in lives?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Lord Captain, please stop. I'm asking you to leave my sister in peace. And... I'll stay with her.";
				link.l1 = "You... what? Longway... but why? Can't you see what she's become?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "Are you any different? You've changed over time. For the worse. At first, you were polite and understanding. But then you became rude, even ruder than Rodenburg. And when I needed a good ship to catch Van der Vink, you gave me some trash!";
				link.l1 = "Longway...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Once I set out to sea and spent all these years just to find and save my sister. And now she's here and safe. My mission is complete. And... My name is Chang Tu. Longway is the name given to me by the traitor Van Merden, in case you've forgotten. But Chang Tu is a free man. Chang Tu's long journey is finally over.";
			link.l1 = "She'll make you into a servant like Rodenburg once did. She'll pressure you because you're family. And will you so easily side with the one who caused me and " + sStr + " so much pain?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Right now, it's you who's pressuring Chang Tu. Please, let me go. I'm very tired. You're a good man, Captain - Heaven can attest to that. But you're not family to me. She is. If I don't stay, then all these years will have been in vain. Now I will be her guiding star and rekindle her extinguished fire - warm and comforting, not burning everything it touches.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "Hmm, you're right. I might be pushing too hard right now. Well, I've always respected you. I wish you a long-awaited family reunion with your sister. But I warn you, you won't find peace with her.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "You can't leave me now! I still need to save " + sStr + " from Levasseur! Do you want me to go there alone? Help me, Longway. And then I'll let you go. I promise you.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "I can handle it. You needn't worry about me anymore. Thank you.";
				link.l1 = "It seems your sister is angry that we've decided to part peacefully.";
			}
			else
			{
				dialog.text = "You will figure it out, Lord Captain. You're the most intelligent man I've ever seen. You can easily handle that worm who's only used to tormenting women. I'm asking you, don't force me. My sister has so much to talk to me about! And... my name is Chang Tu.";
				link.l1 = "You realize that by leaving me now, you're betraying me?! Especially by staying with her - the woman who started all this!";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Fear not, Captain. Though she speaks of me disrespectfully,  I am the older brother and her last male kin. You can go. I won't let her kill you. Farewell.";
				link.l1 = "Farewell... Chang Tu.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "I've said all I have to say. Goodbye, Captain. And good luck to you. Chang Tu will always be a free man. Don't forget that.";
				link.l1 = "And this is what I get after I gave up everything and helped you in your search?! After what they're doing to " + sStr + " now?! You're a traitor, Chang Tu. And you will die as such, both of you, you fucking snakes!";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "My name is Chang Tu. Longway is dead. You killed him. You are no longer my Captain. And now you'll die. My family will finally find peace, and our star will shine brightly in the night sky.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(Trustworthy) (Leadership) Longway... Chang Tu. Stop. I know that I wasn't the perfect Captain for you. But do you really want to kill me so badly for this? After all we've been through? First Rodenburg, now the search for your sister.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				notification("Trustworthy", "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Longway, I'm your Captain. Not your family and not a babysitter. I give orders, not wondering if I've inadvertently insulted you. You're making demands as if we were old spouses, by God...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "Aye. I can see it now. You're just as much a rotten scum who cares only about oneself... Longway. Just like your sister. My family will survive the day. Yours - won't. Go to hell!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "If the choice is between you and my family - I still choose family, even if it's a hard choice.";
			link.l1 = "A family that didn't lift a finger while you were searching for her all these years? Oh, but then the right time just came in! As for me, I gave up everything to help you. You, standing right here, is the result of that. Hell, I'm more family to you than she is, my friend!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "You're right. As always, you're right. Will you forgive me, Lord Captain?";
			link.l1 = "There is nothing to forgive! You're right about one thing - I wasn't always the Captain you deserve. I guess that makes us even now. By the way, how would you like me to address you from now on? Longway? Or is it Chang Tu?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Let it be Longway. I'm already used to you addressing me that way.";
			link.l1 = "Then let's forget all disagreements, and welcome aboard again, Longway.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "Tu! What are you saying?! Why did you stop?! Kill him! You'll always be just a laborer to him! Your family is me and only me!";
			link.l1 = "She's so angry, isn't she, Longway? You are no longer his family, Xing. That ended when you learned of Longway's arrival in the Archipelago and chose to ignore it. We're leaving.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "I guess I never had a real chance of rooting out that slave mentality in him. I can't save him. Then I'll kill you both myself.";
			link.l1 = "You're the one here who can't be saved. You know, I was too understanding and forgiving of you. But this is even better. I think even Longway has realized what a snake you are. He won't mourn you too much.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "Jokes are inappropriate now! You hide your fear and failure behind them! Which only convinces me more. Defend yourself, de Maure! For Chang Tu has no intention of sparing you.";
			link.l1 = "I'm sorry it ended this way. But if that's the way you want it, so be it. In that case, you won't get any mercy from me either.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Charles, listen...";
				link.l1 = "Helen?";
			}
			else
			{
				dialog.text = "Charles, Longway, stop...";
				link.l1 = "Helen, you'd better get behind me now. I'd feel safer if you did, in case they attack us.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "I'm so tired; I can hardly stand. I just want to get out of here. We're not going to drag Longway back to the ship if he doesn't want to come, are we? I'll be your navigator and first mate, my Captain. Hopefully, your most trusted and beloved too. Besides, he's got a point - we're not his family. She is, for better or worse.";
				link.l1 = "But what about her? She's the reason you were tortured; it was all her idea. And she's the one who kidnapped you.";
			}
			else
			{
				dialog.text = "But they won't, right? Let's just leave now, that's all. If this is what he thinks of us after everything we've done for him, there's no point in trying to change his mind. Actions speak louder than words. If he wants to stay with his sister, let him.";
				link.l1 = "Helen, you've suffered so much because of her...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Leave that demoness alone with her demons. They'll consume her soul soon enough. And ours deserve a good rest. Let's go.";
				link.l1 = "Yeah. I guess we should. Let's get out of here, my angel. And you - Longway, or Chang Tu - goodbye.";
			}
			else
			{
				dialog.text = "But I didn't die. And the worst didn't happen. I'm here, with you, and that's what matters. And Levasseur is dead. Without him, she's nothing. Her place is losing money and will soon go under. And they'll go down with it. Let's go, my captain. There's nothing more for us to do here.";
				link.l1 = "I won't argue, Helen.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "Where are you going?";
			link.l1 = "What, surprised we're not eager to spill your and your sister's guts, Longway? That's the difference between us. And you still think I'm the bad guy... But alright, look. If you want to kill me, that means you're gonna have to kill Helen, too. She's wounded, injured. Do you really want to do that?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Mm-hmm.";
			link.l1 = "I can see the doubt in your eyes, even though you've got plenty of grudges against me. But let's both take a cue from Helen, shall we? No one in our crew is kinder or more forgiving than her. We're leaving. And if there's any goodness or sense left in you, you won't stand in our way.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Be that way. I apologize. But you are no longer my Captain.";
			link.l1 = "I'll get over it somehow. I wish you and your sister the best, despite what she's done. Goodbye, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "Come on, Charles, it's time to stomp out this mutiny.";
			link.l1 = "God knows I didn't want to do that... and I still don't want to.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "You don't?! Charles, listen to me. You've done so much for him, and what have you gotten in return? Betrayal and nasty words, alright! Are you really going to let that slide?";
			link.l1 = "I don't want to spill Longway's blood. I haven't forgotten that we were friends once.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "Screw friends like that - they're worse than enemies, alright! Charles, look at me. Look at what happened to me-because of his sister, who mocked, insulted, and humiliated me on the way to this bloody island!";
			link.l1 = "Mary, I understand - you're very, very angry right now...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "Oh no, Charles, I'm not just angry, no... I'm furious! And not just because of what that miserable little bastard said to you! Look at me again, Charles-and imagine how many more girls will go through this if we don't put an end to it. Here and now.";
			link.l1 = "They won't hurt anyone else. Levasseur is dead.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Charles, did you really listen to the heresy she was spouting? She's just as responsible for what went on in that cellar as that stinking hog. Now look at Longway - or whatever his name is now. See how quickly she managed to get him on her side, alright! Who knows what other sick ideas she'll put into that traitor's head? Do you think that demoness will have much trouble pushing him onto Levasseur's path? Don't think about what he is now, Charles. Think of what kind of monster he could become in a year... or even a month. You know I'm right, don't you?";
			link.l1 = "As much as I hate to admit it, I have nothing to contradict you, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "Ha-ha-ha! Fascinating, what a performance. I haven't laughed so heartily in a long time. And she's got guts, I'll give her that.";
			link.l1 = "Shut your mouth, you bitch.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "That's amusing, isn't it, de Maure? I'd love to see Tu take you down myself. And here your woman is just as bloodthirsty as I am. Very good. I won't stand idly by-I've trained with Levasseur and some of Tortuga's top dogs. Let's see whose duo comes out on top.";
			link.l1 = "You didn't have a very good teacher. And you've pissed Mary off. You're finished. Even if I wasn't here, your duo wouldn't stand a chance against her.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "Yes. Finally. May Longway speak with my sister again, Lord Captain? Not long.";
			link.l1 = "Of course. Just make it quick - we don't have much time.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "Longway make it quick.";
			link.l1 = "Good.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "And what was it you wanted to tell me, my brother?";
			link.l1 = "That Longway is very disappointed in you, Xing.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(In Mandarin) Why don't you speak our language since you wanted to talk again, Tu? Are you embarrassed of him? If I were you, I'd be more embarrassed about your accent.";
			link.l1 = "No. Longway has no secrets from Lord Captain. Not anymore.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(in French) First Rodenburg, now de Maure. You always need a ‘monsieur.' You've achieved nothing here in over a dozen years. You can't even learn any of their languages. And they're so much simpler than ours! If anyone is a disappointment, it's you.";
			link.l1 = "But I don't trade in women. I don't participate in their kidnapping and torture.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "Are you serious? Shall I list the things you've done for Rodenburg? What I've been doing would be child's play in comparison.";
			link.l1 = "I had a purpose - to find you. But you didn't even want to see me. And when I found you, I found a monster, not the warm guiding star that once shone on my path.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "A monster? Well, maybe you're right. I'm no longer the cheerful girl you knew. If I'd stayed that way, life would have chewed me up and spit me out. I had to grow my own teeth. My star has long since extinguished. But I'm still your sister, Tu.";
			link.l1 = "No. You're no longer my sister.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "Giving up on me so easily after all these years? Heh... And who knows, maybe I'd still be the same if you'd made it home in time to kill Fermentelos that day?";
			link.l1 = "You're right. It's partly my fault, too. It's my responsibility. And I'll end it. I'll put you out of your misery. End this miserable existence.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "Are you really going to kill your own sister, Chung Tu? Not that you'll succeed, but the fact is...";
			link.l1 = "You're no longer my sister. Xing died ten years ago. And today is the day Chung Tu finally dies. From now on and forever, my name is... Longway.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "First, we rescue Chang Xing.";
			link.l1 = "What?! You don't seem to get it, my friend. Your sister is not in immediate danger, but " + sStr + " is. And need I remind you that Chang Xing is as much to blame for this as Martene and Thibaut?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "That's not true! She's...";
			link.l1 = "Do you have any idea what Levasseur could be doing to " + sStr + " while we're here arguing?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "But Chang Xing is all I have left, Captain... Your family is still intact...";
			link.l1 = + sStr + " may not be my wife, but she's as dear to me as my own family.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing is my last guiding star, Captain. Besides, you owe me for getting that confession out of Robert Marten.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "We'll go after your sister, I promise. But Levasseur hasn't touched her all this time. " + sStr + " is in far greater danger than Chang Xing. Help me save her first, and I'll owe you a big one.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(Trustworthy) (Leadership) We'll go after your sister, I promise. But Levasseur hasn't touched her all this time. " + sStr + " is in far greater danger than Chang Xing. Help me save her first, and I'll owe you a big one.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						notification("Trustworthy", "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "Listen to me! Your sister is safe. But " + sStr + " is now in the hands of a pervert, who could be torturing her right now - or worse! Do you think Levasseur would let your sister own such a classy establishment if he treated her like other poor girls in his dungeon?!";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "I won't waste time on pointless arguments. We each have our own priorities. Let's split up again. May my God help me and yours help you.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "You're right. I owe you one. Fine, have it your way. Besides, without you, I might not be able to handle Levasseur and his men. But if something happens to " + sStr + " while we're dealing with your sister...";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Thank you for understanding, Lord Captain. Good luck to you!";
			link.l1 = "And to you, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Idle threats are empty threats, Lord Captain. We must hurry, so we'll make it in time for everything.";
			link.l1 = "I hope your God hears it. Let's go!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "'ll let that slide out of respect, Lord Captain. Just this once. Next time I will hit you. I'm going after my sister now, with or without your approval.";
			link.l1 = "I won't waste any more time arguing with you, Longway. In the end, we all have something we hold dearer than anything else.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "Mm-hmm, alright, Lord Captain. But then we must hurry.";
			link.l1 = "Right. Thank you, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Well, well, who the hell do we have here... Fuck. Charles de Maure and his slant-eyed mutt.";
				link.l1 = "There's only one mutt here. If you want to see it, look in the mirror, you Huguenot bastard. Or just take a look at your nephew. Though, he looks more like a mangy rat.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "I told you not to disturb me! Ah, Charles de Maure, hehehe. What a persistent little pest.";
				link.l1 = "That's just how I am. Now shut the fuck up and...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "You're not on your own ship, pup! There's only one man on this island, and that's me!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "How dare you, you scum!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "Calm down, nephew! Monsieur de Maure is about to get a lesson in good manners.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Did I give you permission to squeal?!";
			}
			else
			{
				dialog.text = "Where's all that fire gone, huh, pretty thing? Ah, I think I get it...";
			}
			link.l1 = "Leave her alone, you bastard!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Heh-heh-heh... You can shout and insult me all you want, but I can see you trembling like a leaf in the wind. I see the fear in your eyes. You and Henri have that in common. No offense, nephew.";
			link.l1 = "You're right, it's fear. But not of you, scum.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Of course, of course. I've heard it all before - that you fear no one, de Maure. She told me that. 'O-oh, Charles will come, Charles will save me... Charles this, Charles that...' Well, Charles is here. Charles has a front-row seat. Henri, make our guest comfortable.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "There's no need for that, Uncle. I'm afraid you've gone a bit too far this time...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Uncle, I'm going to need your help with this one...";
				}
				else
				{
					dialog.text = "Should I finish him off, Uncle, or let him watch first?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "It wasn't me, it was Monsieur White Knight over here who took too long to come for the rescue. Looks like the show's over, ha-ha-ha-ha!";
				link.l1 = "God, no...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "I thought so. How did you manage to live to this age? By the way, same question for you, de Maure.";
					link.l1 = "You have no idea how many questions I have for you, butcher!";
				}
				else
				{
					dialog.text = "I wish our little performance had an audience... But I don't think Monsieur Stubborn here will give us that pleasure.";
					link.l1 = "The only pleasure anyone gets is me - by gutting you, butcher!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "Come on, go ahead and pick her up! Ha-ha-ha!";
			link.l1 = "Fucking animals, I'll make you regret being born!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Butcher? I think of myself more as an artist, a painter - would you at least try to see it as art... Observe.\nDo you like my work? Truly one of my masterpieces. To be completely honest, I prefer blondes, but her... In the end, I forgave her for this ugly hair color. It wasn't just the hair - the girl's like fire! I almost burned myself. She fought, bit, snarled like a wild animal! Reminded me of a red-skinned savage, one I had a lot of fun with, even if not for long...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Butcher? I think of myself more as an artist, a painter - would you at least try to see it as art... Observe.\nSee, I'm not done with her yet - there's still a lot of empty space on this canvas. Not only is she beautiful, but she's as tough as a rock and as cold as ice. I even had to work up a bit of a sweat to get her to scream. She held out till the end, just so she wouldn't give me the pleasure of hearing her lovely voice.";
			}
			link.l1 = "Release her now, you degenerate.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "Where do you think are you going? This piece of meat is my property now. Just like everything around it - this town, this fortress... I am Tortuga. And you and Poincy, that stinking old turkey, can never change that.";
			link.l1 = "Levasseur, you...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "It's Signor de René de Buaduflé de Lettre for you.";
			link.l1 = "I don't give a damn. Draw your sword and show me what you're worth in a fight - with a man, not a defenseless girl.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "And what a man you are! But you're right, I'm tired of all this chatter myself. I want to get back to... my dame. But I'll ask you one last question. How did you get here? Who gave away the location of this place? Only a handful of people know about it.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Your mutual friend, Martene, sang like a nightingale. Actually, squealed more like a pig in a slaughterhouse though...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Maybe it's better to keep it a secret from you. I'm afraid it might hurt your ego, Signor de René... something.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "One of your victims, Levasseur.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "Liar, you scoundrel! Nobody leaves these walls!";
			link.l1 = "Use your memory, come on. There was one. Chang Xing.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "No way. Not her. Some of my ideas were spawned by that little devil. Oh-oh, we taught each other a lot, hehe. Has she decided to clear her conscience in the end? I doubt it. After all, I etched it all out of her a long time ago!";
			link.l1 = "Now I'm going to etch you dry. One drop at a time.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "And you call me a butcher, you miserable hypocrite! Heh-heh... But as long as he's burning in Hell, I have nothing to fear.";
			link.l1 = "He's waiting for you there. And your scoundrel of a nephew too. Let's not disappoint him.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "How about I hurt this toy a little more? Slit her belly or throat, and watch her bleed out while you're trying to get down to her...";
			link.l1 = "Whatever you say, Levasseur, whatever you say... Your wife sends her regards. And with it, a farewell bow.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "WHAT?! Kha-kha... Fucking Marceline... You miserable bitch, bitch, bitch, bitch!";
			link.l1 = "That she is. You're worthy of each other. She's a bit better with her head on straight though. At first glance at least.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "I'm gonna put her chicken head on a spike. But before that... oh-oh, many, many things will happen to that slut.... I'll even give my new toy to rest a bit. Wait! I have a better idea. I'll lend her to Henri. For a time, of course.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "Really? Thank you, Uncle!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Deserve it first - give me a hand with this one, eh?";
			link.l1 = "He is about to lose it.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Lord Captain... Longway offers his condolences. We did all we could.";
			link.l1 = "Not everything, not nearly enough.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Longway's going to find Chang Xing. Will you come with me?";
			link.l1 = "Aye, I'm going with you, Longway. But remember - your sister had a very active part in this bloody spectacle too. She's going to have to work very hard to convince me to spare her. And you won't help her. Now come on, it's time to end this.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			Return_LongwayOfficer();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, I knew it, alright! I knew you'd come! You always do, don't you?";
					link.l1 = "I wouldn't want to test that for a fourth time, Mary... Those scoundrels, they...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Oh, my Captain, you don't realize how timely you are. Those... those monsters...";
					link.l1 = "It's over now, Helen. It's alright, it's all over. Oh my God, what have they done to you...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, you're here! I knew it, I knew it, alright!";
					link.l1 = "I was flying full sail, running for my life, Mary. You... did they?..";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "My Captain... You're here... I had almost lost the hope...";
					link.l1 = "I came as fast as I could, Helen. I'm sorry it took so long.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "No, Charles, no. They tried, but I fought them off as best I could. That's why they beat me so badly... Please, Charles, let's get out of here... alright?";
					link.l1 = "Right away, my dear. One last thing to do.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "They didn't do it, Charles! They did not. The rest will heal. Please, take me away from here.";
					link.l1 = "Of course, my dear. There's just one thing left to do here.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "No, Charles, no. They tried, but you made it just in time. Like back then. How many times is that?";
					link.l1 = "I haven't kept count, Mary. And I never will.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "You got here... just in time. The worst didn't happen. Now, please, let's get out of here. Anywhere.";
					link.l1 = "Get on your feet, Helen. Go upstairs. I've got to deal with this rotter first.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "And I won't stop counting. Now let's leave this place, please.";
			link.l1 = "Of course, my dear. There's nothing more for us to do here. Except one thing.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "So what, kha-kha, you don't have the guts, snotlout? Ask your yellow-ass boar to lend you a hand...  Or do it yourself and then you'll have a reason to tell Poincy how brave you are.";
				link.l1 = "I'd rather tell everyone what a cowardly piece of shit you were instead.";
			}
			else
			{
				dialog.text = "What, do you really want to watch me bleed to death? You're enjoying it, eh? You'll tell your woman what a hero you are. See that skeleton up there on the wall? Santiago's banker's wife... Her man thought he was a hero too, but he turned out to be just a good screamer - when I spun him on that wheel...";
				link.l1 = "I could roll your carcass on it, scumbag, but I'm afraid it wouldn't support the weight of your ass.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Cowardly? Oh, kha-kha, come on...";
				link.l1 = "Cruelty isn't the opposite of cowardice. But someone like you wouldn't know the difference.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "That's very clever. Mark my words, de Maure: you'll die just like that bigwig, hoarse from your own screams and deaf from the cries of your...";
				link.l1 = "Burn in Hell, scum.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "Aye, I'm not much of a philosopher, I'll admit that. See that skeleton on the wall, de Maure? That's all that's left of Santiago's banker's wife. He liked to talk big too, but all that stopped when I started winding his body on that wheel. All that was left was screaming, which almost made me deaf...";
			link.l1 = "Let's get this over with.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Wait a minute, Lord Captain... Don't be so quick.";
			link.l1 = "What's the matter, Longway?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Don't kill him. Too simple. He deserves worse.";
			link.l1 = "You're angry about your sister, my friend. And I'm furious about what he did to " + sStr + "... and what he could have done to her. But I'm not an animal like him. I could burn him with coals from that brazier, break his bones on that wheel... I could shackle him and let him die from blood loss. But I can't risk one of his henchmen saving him. I can't take that chance.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "Wait, Lord Captain. That's not what I meant. I'm talking about Poincy.";
			link.l1 = "What about him?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Think about how he'd reward you if you brought him this animal alive. He'd shower you with doubloons. And that scum would rather die here than rot in a dungeon in Capsterville.";
			link.l1 = "You may be right, Longway. But I don't know what exactly happened between this scumbag and the Chevalier. Believe me, I know this crowd better than you do. If it's all about money, as they say, these two could make a deal. Poincy could let him go, and another room like this could appear on some other island or in one of the cities of the Old World.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "Not a bad idea, Longway. I doubt the Chevalier will be that generous though... It's not in his nature really. But for me, it's not about the money anyway. Get him up! And dress his wounds so he doesn't die before his time.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "But first, I'm coming for you. And your mate. I won't touch you, narrow-eyed man - you're not worth my time.";
			link.l1 = "You see, Longway? This all has to stop now. Here and now.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Wait a minute, Captain, wait a minute, kha-kha.";
			link.l1 = "What is it, Monsieur ex-governor?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "My key is in this room somewhere. It opens a chest in my office. There's two hundred thousand in silver and a fine blade. If that's not enough, in my wife's bedroom, in the chest of drawers, there's a collection of expensive gems.";
			link.l1 = "Hmm, and what do you want in return?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "A bullet. Finish me off. Here and now.";
			link.l1 = "What about the Chevalier de Poincy? I hear you're old friends... Don't you want to see him?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "To hell with Poincy! So, do you agree or not?";
			link.l1 = "Not really, Monsieur de... I don't want to list your full name.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "Isn't that enough for you? Fine, there's more...";
			link.l1 = "The screams of your victims must had made you deaf, Levasseur. I told you, it's not about the money. You are afraid of Poincy for a reason, ed? I don't even want to know what he'll do to you. But if it serves as a bit of retribution for your... artistry, so be it.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "So that's what you really are, kha-kha... No better than me.";
			link.l1 = "Enough. Longway - get him up!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) Return_LongwayOfficer();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Our ship... I never thought I'd be so glad to see her... alright. At last, this nightmare is over.";
				}
				else
				{
					dialog.text = "It's finally over. Where to now, Charles?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "I can't believe it's all over... What do we do now, my Captain?";
				}
				else
				{
					dialog.text = "Well, that's it, my Captain. What do we do now?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Alas, it's not over yet. Chang Xing... This story only truly ends once I get my answers from her.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Set course for Capsterville. It's time for Monsieur Levasseur to become part of history.";
				}
				else
				{
					link.l1 = "The Chevalier's mission is complete. I need to report it to him. I'll leave some of the details out of it though. I only hope he keeps his word and Michel is freed...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Me too, alright. So I'm going with you. And don't even try to argue with me, Charles.";
				link.l1 = "Mary, dear, you need to rest. You're this close to fainting...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "I'll come with you.";
				link.l1 = "Helen, you nearly died at the hands of that devil. You can barely stand on your feet...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "I need you, Charles. And you need me. And if anyone's going to faint tonight, it's Chang Xing. On the floor of her whorehouse, with a bullet between her eyes!";
				link.l1 = "Aye, Levasseur didn't beat the fighting spirit out of you. I'd send you back to the ship, but I know you'd follow me anyway...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "But I can still hold a blade. Charles, I have to be there. I need to understand what drove her to do it. Do you understand why this is so important to me?";
				link.l1 = "I understand that you need rest and healing. And a long one at that.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "You know me too well, Charles, alright. So let's forgo the chatter and finish this.";
				link.l1 = "Have it your way. But stay sharp. No one knows what surprises await us out there.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "It can wait. You came for me, and now I'm coming with you. Whether you want me to or not.";
				link.l1 = "I see you still have your nerve, Helen. Good. Stay behind me, and for God's sake, be careful.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Our ship... I can't believe I'll board her again, alright...";
					link.l1 = "She's waiting for you, Mary. A hearty meal and a soft bed too...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... I didn't think I'd make it to the boat on my own two feet.";
					link.l1 = "You're the most resilient person I've ever known, Helen. Now get inside and then to bed...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Our ship... I can't believe I'll board her again, alright...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... I didn't think I'd make it to the boat on my own two feet.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Set course for Capsterville. It's time for Monsieur Levasseur to become part of history.";
				}
				else
				{
					link.l1 = "The Chevalier's mission is complete. I need to report it to him. I'll leave some of the details out of it though. I only hope he keeps his word and Michel is freed...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "And you, Charles... Why is that look? You're up to something again, aren't you?";
				link.l1 = "Chang Xing. I must get to her too.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "And you? Where are you going?";
				link.l1 = "To see Chang Xing. She is the last chapter of this nightmare.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Then I'm coming with you! She owes me big time, alright!";
				link.l1 = "Mary, dear, you barely made it to the boat. And you can't hold a blade right now. I'll make her pay for she's done to you, I swear to God. But I'll feel much better if you stay on the ship, knowing you're safe.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "My Captain, I'd like to go with you so much... Please be careful. Who knows what else she's capable of? She held me down while that pup Thibaut...";
				link.l1 = "The worst is over, Helen. It'll all be over soon, I promise.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Well, at least Longway will have your back in my absence. But if anything happens to you, I'll put him and Chang Xing in the ground myself!";
					link.l1 = "It'll be fine. Now go rest. I'll be back before you know it.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Where's Longway gone, Charles?";
					link.l1 = "He went after Chang Xing without me. I couldn't stop him, but what could I do?";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Well, at least Longway's coming with you. That's some comfort, at least.";
					link.l1 = "See? There's no need to worry. I won't be long.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Where's Longway? I just realized he's not here.";
					link.l1 = "He went to his sister without me. I don't blame him. He's waited too long for this moment.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, I have a bad feeling about this...";
				link.l1 = "I know. This nightmare has gone on too long, and the end is near. The worst is over.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Who knows what's on his mind, Charles? Keep your eyes open, alright?";
				link.l1 = "I will. I'll be back soon, Helen."
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Promise me you'll be ready for anything.";
			link.l1 = "I am, and I will be. I'll be back soon, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "Longway  helped you, Captain. Now it's your word to keep.";
			link.l1 = "You heard everything, Longway. Let's go see your sister.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Lord Captain, Longway has one last request: let Chang Xing explain herself. Hear her out before you make any decisions.";
			link.l1 = "What happened to " + sStr + " is on her. But I'll give her a chance to explain first.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Longway trusts your word, your judgment, and your kindness.";
			link.l1 = "Mate, there's no room for reason or kindness in this bloody mess. And it's high time to end it.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Lord Captain...";
				link.l1 = + sStr + " is dead.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Captain, lady " + sStr + ", it's a pleasure to see you. This is... Chang Xing.";
					link.l1 = "I've guessed it, Longway. Stand back. You've had plenty of time to talk to your sister. Now she must answer to " + sStr + " for helping Levasseur's minions kidnap her.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "You've come... Where is lady " + sStr + "? Is she...?";
					link.l1 = "No, Longway. Thank God, no. I took her to the ship. Otherwise, I wouldn't even be having this conversation right now. However, it is still not going to be easy or pleasant.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing and I offer our condolences...";
			link.l1 = "Condolences from Chang Xing?! You might as well offer condolences on behalf of Levasseur, Longway! You know very well that she participated in the kidnapping of " + sStr + " along with the others his minions! And now she's gone...!";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "We.. I understand what you are feeling right now, Lord Captain.";
			link.l1 = "Oh, really?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "I lost my parents, as you remember. If you do remember. Besides, it wasn't Chang Xing who tortured and killed " + sStr + ". I understand your pain, your rage. But my sister's guilt isn't as much as yours to consider. Please, hear me out.";
			link.l1 = "I remember. I'll listen to your story. But make it quick! And know that I can't let something like this go unpunished!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "Then I'd better tell it all again, Monsieur de Maure. Our Tu's French is so bad, you nearly attacked him.";
			link.l1 = "You should have kept your mouth shut. I wasn't going to attack Longway, but you... You're the one responsible for her death.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "I'd argue with that, but I realize I'd rather not. Tu spoke of you as a person of respect and understanding. But is that really the case? Does it make sense for me to even start talking? Or have you already made up your mind?";
			link.l1 = "You know how to get inside someone's head, mademoiselle. It's really not worth arguing now. But if you want to try to justify yourself... Well, go ahead. For Longway's sake, I'll hear you out.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "She can explain everything, Lord Captain... It's not what you think... Not really...";
			link.l1 = "Then explain it. But not to me. " + sStr + ". Look into her eyes. Look at her bruises and wounds. And tell her it wasn't like that.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "My apology on behalf of Xing, Captain...";
			link.l1 = "Judging by her smirking face, you're doing it in vain. She doesn't deserve your apology.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "You're being too hard on him, Monsieur de Maure. Though you're probably used to treating him that way - like a typical yellow-skinned laborer.";
			link.l1 = "Are you trying to turn Longway against me? It won't work. I've always treated him with respect, and he knows it. That's all that matters. I realize that playing games is all you have left now.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "What do you want to do? Take poor Tu away from his family? When he finally found them again after ten years?";
			link.l1 = "Blood doesn't always make a family. But what do you suggest we do? Let what you did to " + sStr + " go unpunished? And have Longway occasionally visit a woman who trades in other girls without a second thought?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "Well, for starters, listen. Unlike him, I can retell what I just told him in perfect French. My story. Looking straight into your eyes, or even hers. And all that without the accent you're probably sick to death of by now. After all, what do we all have to lose?";
			link.l1 = "I'm used to Longway's accent; it's part of who he is to me. I'll listen to you, but only for the sake of my friend. Go on.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Why not, Lord Captain...?";
			link.l1 = "Do you really need to ask? She was involved in the kidnapping of " + sStr + ", wasn't she?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "I... sincerely apologize. It's my fault too, for not being able to save my sister ten years ago, to keep her safe from all this.";
			link.l1 = "You shouldn't apologize for those who don't have the slightest remorse, Longway. Are you done here? It's my turn to talk to her.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "Lord Captain, wait! Chang Xing isn't like Levasseur. Not entirely. She'll tell me about her life over these ten years. Let me tell you too.";
			link.l1 = "All right, Longway. I'm listening. A lot depends on what you will tell me.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "If it's you telling it, we'll all get a headache. Allow me, Tu. Charles de Maure, I presume?";
			link.l1 = "Right. And you're Belle Etoile, also known as Chang Xing. You played a part in kidnapping my love, along with Thibaut and Martene. And you smile when I mention it. Happy memories?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "It's stupid to deny it. But what of it now? Are you going to torture me in front of my brother? Or even ask him to help you torture me? Or will you just kill me? Would you really do that to him?";
			link.l1 = "Like I said, despite everything I'd like to do right now, I'm still talking to you. Don't push it. Tell me what you told him before. And then we'll see where we all go from there.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "I still can't believe Chang Xing would turn into... this.";
				link.l1 = "People change, Longway. Anyone can be broken or have the last drops of kindness and faith etched out of them.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "Longway still can't believe my sister turned into... this. Why... why? If only I had been home that day...";
				link.l1 = "Don't beat yourself up over what-ifs. Besides, you didn't sit idle all those years - you tried so damn hard to fix things.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eh... I guess that's just how it is, Lord Captain.";
			link.l1 = "Let's get out of here. We still have to clean up the mess she left behind and save the " + sStr + " as soon as possible.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "Aye. We need to hurry - it's already been delayed too long because of me.";
			link.l1 = "It's not your fault, Longway. Let's hurry!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "Right. Thank you for your support, Lord Captain.";
			link.l1 = "Don't mention it. She didn't deserve your dedication anyway - she wasn't the one who sought you out, even when she could have. Your star has long since extinguished, and she stopped being your family a long time ago. We're your family now, Longway.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "Aye... So you are. And I was too blind to see it all this time.";
			link.l1 = "Better late than never. Now let's go home - our ship is waiting for us.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "Alright. You have no idea how much I wanted this.";
			link.l1 = "I believe I do. How are you feeling, Mary? The reason I wanted to avoid bloodshed was because I wasn't sure if you could hold your blade as firmly as you always have - one of them could have gained the upper hand while I was busy with another.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "You underestimate me. Besides, anger is a hell of a medicine. I had no doubt you would rush to save me - just like you always do, alright. You know, Charles... Even though you call me your Red Talisman, what if you're mine too? Something amazing always happens when we're together.";
			link.l1 = "I'm your talisman? Why, I like that idea.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "There you go, you're already smiling! Now let's get out of this disgusting place - hurry up, chop-chop, alright.";
			link.l1 = "Eh-heh, this mess hit me hard. I wish it could have ended any other way.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "I don't. There was no saving her, Charles. And she dragged Longway down with her. He made his choice, and he left us no choice. Think of all the people we've helped today.";
			link.l1 = "Once again, I have nothing to contradict you, Mary. And this time, I don't even want to. Come, my Red Talisman...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "What happened there, monsieur? We heard swearing and shouting. But we didn't dare call for help until it was over.";
				link.l1 = "And rightly so. Your hostess is dead. You are free to go. If I were you, I'd collect the establishment's treasury, split it up, and flee the island as soon as possible. I know you are honorable ladies, not mere prostitutes, so you will have a future beyond this wretched place.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "Oh, it's you, monsieur. Do you know when the hostess's coming down?";
				link.l1 = "Not soon. And I would step away from the door if I were you. And never talk to her about this evening - she won't share anything, and nosy cats lose their lives all at once. It seems your madam doesn't like anyone prying into her secrets.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "Did you kill her?!";
			link.l1 = "I did. And if you linger or try calling the guards on me, that would be your greatest mistake. She was never a patron saint to you - no matter how much silk and education she gave you, you were imprisoned here, forced to give yourselves to any rabble she pointed at. I wish you all the best of luck in getting out of here. Goodbye, ladies.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "Is she really fine? Can we go in? Do we need to call the guards?";
			link.l1 = "She will never be fine. You can try asking her herself... at your own risk. She's still talking to her brother. And I don't think they'll be pleased to be disturbed.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "I see... Well, you come and see us again sometime, monsieur.";
			link.l1 = "Never. Farewell, ladies.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "Halt! Screaming and fighting were reported coming from Mademoiselle Etoile's place. The guard believes you had something to do with that. Relinquish your weapons and follow us, monsieur.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "True, but we didn't start the fight, we ended it. The hired thugs rebelled over late payments and attacked Madame Etoile to rob her. Trust the mercenaries, eh? We won the day, but unfortunately, she didn't survive.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "I lost the love of my life today, so let me pass, officer.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "You realize we can't just take your word for it, don't you? We have to detain you. And you'll need witnesses from among the female employees. Let's see what they have to say.";
			link.l1 = "My loved one is badly injured. I'm also dead tired. Can't you just let us go, please?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "We'll try to sort this out as soon as possible. Now follow us.";
			link.l1 = "Go to hell...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Condolences, monsieur. And I'm not an officer yet, but... anyway, never mind. Could you come with us and tell us what happened there?";
			link.l1 = "I'll tell you. The brothel was losing money, and there was no cash left to pay the mercenaries guarding it. They decided to take whatever was left, just as I happened to be there. Madame Etoile and I fought them off, but she died of her wounds. Now, let me pass at last.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "I'd love to, but there's a lot of paperwork to fill out. And I need to interview the ladies who work there. I'm afraid you'll have to stay in town for at least a day, even if you're telling the truth, monsieur.";
			link.l1 = "Go to hell...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "Longway has something for you, Mr. Captain.";
			link.l1 = "How beautiful and whimsical. I've never seen anything like it. What is it?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "It is my Homeland's Captain amulet. And, since Longway's not a Captain anymore, I give it to you.";
			link.l1 = "Thank you, Longway. With van der Vink's death, you got your revenge on everyone you wanted. I am glad it all worked out like that.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "If only I could convince Xing to be a good person again...";
			link.l1 = "She wouldn't want to listen to anyone anymore, even to her brother. You did the best you could. All of us did.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "Aye... Thank you very much, Lord Captain. Longway to be free, and to have a home and friends again.";
			link.l1 = "You're welcome, my friend. Now, why don't you come with me to visit my brother. Oh, the irony!";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			Return_LongwayOfficer();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Here we are again, François. I see life has taken its toll on you, hehe.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Poincy, you greedy bastard... Almost choked on the gold your coffers are full of, and you still can't get enough?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "I'll share some with you, François. You'll have enough, believe me.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "What... what do you mean?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Governor-General, are you going to...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, my friend, you've done your job and you've done it brilliantly! What will happen to this man should not concern you... However, it will be useful for you to know, Captain, just in case your bright head get some dumb ideas ome day. A bad case of indigestion awaits our mutual friend, so to speak. Gold is not good for the stomach, I heard... I hope I don't need to explain further.";
			link.l1 = "No, Governor-General.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "Unlike Monsieur François, you have a great future ahead of you, Charles. Boys, get that hog to jail!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "Hands off, you cunts! Are you satisfied, de Maure?! Fuck you! You'll both burn in Hell, in the same frying pan with me!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "Well, sir. I have inspected miss " + sStr + "...";
			link.l1 = "How bad is it, Raymond?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Nothing to worry about, Captain. Mary was hurt hard, of course, but, on the whole, everything will all right. She should remain in bed for a few days, and I expect she'll be back in action in a fortnight.";
					link.l1 = "I see. Thanks, Raymond. Dismissed.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mary took quite a beating, Captain. Bruises, cuts... and the shock of it all, of course - though she tries not to show it.";
					link.l1 = "She's keeping a tough face, as always. But I think she realises that she's better off on bed rest now. For how long though?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Even a professional soldier would struggle to survive what she went through, Captain. Sprains, strains, bruises - we're lucky those bastards didn't break her bones. Her tendons are damaged, though, so she won't be able to wield a blade for at least a month.";
					link.l1 = "To hell with the blade. When will she be able to stand on her feet?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Don't worry, Captain. Hellen is hurt, but not badly. She'll have to remain in bed for now, but I think she'll make a full recovery in a couple of weeks.";
					link.l1 = "I see. Thanks, Raymond. Dismissed.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "She took quite a beating, captain. And the physical injuries are only a part of the diagnosis... Being in that terrible place reminded her of the nightmare she experienced on the Arbutus.";
					link.l1 = "Of course... damn it! When will she be back on her feet?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Helen walked on a razor's edge, Captain. I'm surprised she survived after all she's been through. No internal lacerations or fractures, but plenty of sprains and strains.";
					link.l1 = "Poor thing. How long will her recovery take?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "At least a week, sir. If she follows my recommendations, she should be back in action in about a month.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Not before a fortnight, sir. After that, I'll allow her short walks on the quarterdeck. Full recovery will take at least two months.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Don't bother her for at least a week, I'll tell you that, sir. Full recovery will take around a month.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "She should stay in bed for a fortnight; after that, she may be able to walk around the deck. But don't expect to see her back in action for at least two months.";
				}
			}
			link.l1 = "I see. Thanks, Raymond. Dismissed.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "It's harder than I thought it would be to stand on my own after lying down for so long, alright!";
				link.l1 = "Maybe you shouldn't stop bed rest so abruptly, love.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Oh-h, my head...";
				link.l1 = "Helen! Aren't you up a little early? You can barely stand!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "I'd rather burn this bloody bed than lie in it again - at least until I've walked from bow to stern and back!";
				link.l1 = "It's a nice comfortable bed. And it's not a bad ship either. So I'm not going to stop you. But I'll be there to make sure you don't do anything foolish.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "I'm fine, Captain, though not completely. I'm not ready to swing a blade yet, but I hate this bed with all my soul.";
				link.l1 = "Well, a short walk on the deck probably won't hurt you. But don't even think about going near the cables!";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, don't you think you've forgotten all about me? Remind me when we bed last together, alright!";
				link.l1 = "Before... Let's not talk about that, shall we, Mary?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "My captain, have I ceased to interest you as a woman?";
				link.l1 = "That's unexpected, Helen. Usually, I'm the one to bring that up... but I wasn't sure you were ready after...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Then talk about me at least, alright. Or have I become unpleasant to you after those two bastards gave me a beating?";
				link.l1 = "That's the stupidest thing I've ever heard. I just didn't want to disturb you until you were ready. And since you are...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "It's alright, Charles, really. I just try not to think about it. And besides, you saved me from the worst of it. So let's stop talking and just... catch up.";
				link.l1 = "That's a damn good idea, Helen.";
				link.l1.go = "exit";
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Charles, I don't want it, I demand it, alright!";
				link.l1 = "I wouldn't dare refuse you...";
				link.l1.go = "exit";
				AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, we need to talk, alright.";
				link.l1 = "Is something wrong, Mary? You look rather anxious, and that usually doesn't bode well.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "My captain, there's something I need to tell you.";
				link.l1 = "Is that so, Helen? I'm listening.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "That's just it! Isn't it a good thing that I'm ready to return to my duties as an officer?";
				link.l1 = "So that's it. Well, if you feel strong enough, it's not just good, it's wonderful.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "I'm tired of the crew staring at me like I'm some feeble old woman. I want to get back at the helm and stretch my arms by practicing with a blade...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "If you feel up to it, I won't object, dear. I'll get your gear. And I'll gladly let you take the helm. But be careful in a fight, alright?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "You've been missed on the bridge, Helen. As for the blade, I think it's time you had it back.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Of course, My Captain, whatever you say.";
			link.l1 = "Good.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Wonderful, alright! I can't wait to practice with the blade...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Glad to hear it, Mary. But don't dive into the thick of things just yet... But who am I telling?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "I suppose you'll be happy to see that palash back in its scabbard...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "I... I don't know what to say, Charles. I've only just realized how much this cutlass means to me...";
				link.l1 = "I knew that a long time ago, which is why it's been waiting for you safe and sound.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "My narwhal, alright!!! Charles, you saved it! I'm not just happy, I'm thrilled! Thank you, thank you! I was so afraid it was left on Martin's ship...";
				link.l1 = "This blade belongs in your hand, my Red Talisman. I trust you won't lose it again... Well, I won't stand in the way of your reunion, ha-ha!";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Thank you, Charles. You know, that's probably why I love you...";
				link.l1 = "For bringing back lost things? Ha ha ha ha...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "You're laughing, but I'm serious.";
			link.l1 = "I know, Helen. I love you too, though I'm still not sure why.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Maybe because I haven't used this cutlass on you yet.";
			link.l1 = "I'll save myself from that by heading to the boats. I'll wait for you there, Helen.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 