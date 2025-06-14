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
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "Oh, what a heat today. You might as well tie a chain shot around your leg and jump into the sea, just to get rid of this stuffiness!";
			link.l1 = "Ha-ha, Charlie!.. Those are some extreme measures, if you ask me. But I wouldn't mind wetting my whistle - it really is too hot today. Are you in?";
			link.l1.go = "DTSG_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "Have a drink or two with you, Captain? Always!";
			link.l1 = "That's what I like to hear. Let's go!";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "", "", "", "DTSG_BasTerTavern", -1);
			FreeSitLocator("BasTer_tavern", "sit_base2");
			FreeSitLocator("BasTer_tavern", "sit_front2");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "Hey, sailor, you look like you've seen it all! Let's have a drink and swap some tales? My treat!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "Uh, no thanks, mate. I came here with my Captain. Find someone else.";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "Ha, a ragamuffin like you has such high opinions, only drinking with captains?";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "High opinions?! I've served for decades in the Royal Navy! And I fought not for the lords, but for regular folk like you and me, to ensure law and order everywhere!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "You talk big, but only drink with captains and nobles! Looks like the Navy did  teach you how to polish the cannons properly, ha!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "I'll shove a chain shot down your throat, whelp!";
			link.l1 = "Charlie, don't freak out like that, it's not worth it.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "Let me handle this, Captain. The honor of the Navy is at stake, I must defend it myself and not hide behind anyone...";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_FadeLong("DTSG_BasTerTavern_7", "");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "Thank you for waiting, Captain. I hope I didn't take too long.";
			link.l1 = "Don't worry about it. You're not hurt? That scoundrel was quite good.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "Don't trouble yourself, Captain. The important thing is he got what he deserved. I picked up some kind of key from his body...";
			link.l1 = "...";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "I picked up some kind of key from his body... I wonder what it could be for?";
			link.l1 = "Elementary, Charlie... For a door or a chest, ha-ha. We should talk to the innkeeper about this scoundrel, it might be useful.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie gave you the key.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.location = "None";
			pchar.questTemp.DTSG_BasTerTavern = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "Unbelievable...";
			link.l1 = "Are you thinking what I'm thinking, Charlie?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "I don't know about you, sir, but I'm surprised at how much money is here - he looked like an ordinary man, not a merchant or a noble.";
			link.l1 = "It's not that much, really, but you're right. What surprises me is this strange burnt letter.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "Yeah, that wasn't very smart of him - it's like firing chain shot at a sturdy hull. He should have destroyed the letter completely.";
			link.l1 = "True. But it doesn't help us - we don't know who he was or who he was corresponding with. Let's go, Charlie, there's nothing more for us here.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			Return_KnippelOfficer();

			AddQuestRecord("DTSG", "2");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.DTSG_Nastoroje1 = true;
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "So much for your vaunted Royal Navy, pfft!";
			link.l1 = "Charlie was a good, decent man. And he was a cannoneer, not a marine.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "A cannoneer?! So, it's exactly as I said, ha-ha-ha! And don't glare - you should have known who you were taking into your crew.";
			link.l1 = "You should have known who you were messing with.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "You're still alive only because you won fairly, so hold your rotten tongue and get out of here.";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "Well, I thought I would have to fight you next. It's nice to hear that honor means something to you.";
			link.l1 = "It wasn't just empty words for Charlie either. But as for you, I have my doubts. Anyway, it doesn't matter now.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			ChangeCharacterComplexReputation(pchar, "fame", -3);	
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "And who did I mess with, a pampered weakling?! Have you even seen your own thin mustache?..";
			link.l1 = "You sure know how to push buttons... It'll be all the more satisfying to take out my anger on you.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("DTSG_Ohotnik");
			DeleteAttribute(sld, "CantLoot");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Ohotnik_Agressia_3");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "Wait, Captain. I see you are a worthy and noble man, can you help me with something? It's a matter of honor.";
			link.l1 = "Maybe I can, but what is the matter? And why did you come to me? There are many noble people around here. Who do I have the honor of speaking with, by the way?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "Peter. Peter Adams. I can see that you're not a typical pampered descendant of an old family, but a reliable man with a steady hand.";
			link.l1 = "Oh, you should have seen me when I first arrived in the Caribbean, sir. But go ahead, what do you need help with?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "Could you... duel on my behalf, sir? A local troublemaker, Ralph Faggle, insulted my wife. And he harassed her, publicly. Right in front of me. Can you imagine that?";
			link.l1 = "There's not much honor in challenging a duel and then hiding behind someone else. Especially when it's not just your personal honor at stake, but that of a woman, your wife no less. Don't you think so, Adams? Why can't you fight for your woman yourself?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "And you're right, absolutely right. But I recently suffered from a severe fever, and I can barely stand on my feet\nAdmittedly, it's not easy for me to ask you for something like this. If he insulted me, I would have endured it. But not when my wife's honor is at stake! I'm not a coward, sir. I once served in the Royal Navy and sailed on the same ship with Robert Blake himself!";
			link.l1 = "I...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "We'll help you.";
			link.l1 = "Charlie?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "He's a worthy man, Captain. And may I be damned to eternity by cannonballs if it's not true! Great people served with Admiral Blake. They fought together so that no one would oppress the common people\nAnd thanks to him, Jamaica was freed from the tyranny of the Spaniards!";
			link.l1 = "Even if that's the case, I won't allow my crewmen to interrupt me or make decisions for me. Is that clear?";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "I understand, really. However, I haven't even had a chance to respond. Try not to be so hasty and interrupt me in the future, alright?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "I'll tell you this, Captain - if you don't help this man, old Charlie will drop everything and duel for him himself, may I be damned on the spot!";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Quiet now, I didn't say that I refuse to help. Right, Mr. Adams?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "Honestly, Charlie, you're making me look like a coward. And I've never been one. You should know that.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "Uh, sorry, Captain, I got carried away.";
			link.l1 = "It's fine. But keep yourself in check, alright?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "I'll duel for you, Mr. Adams.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "Thank you, sir! God bless you!";
			link.l1 = "And bless the Lord Protector as well, right, Mr. Adams? Don't worry, Charles de Maure never leaves an honest man in trouble.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "We appreciate it, Mr. de Maure, sir! Would you like to come over and have dinner with Jane and me?";
			link.l1 = "Well, I...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "I insist!";
			link.l1 = "Well, only if you insist. Thank you, Peter. Lead the way.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "Of course, it's true, sir! Would you like to come over with Jane and rest after your journey?";
			link.l1 = "Thank you, but is it right to take advantage of your hospitality?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "Oh, on the contrary, Captain, we would be offended if you didn't come over.";
			link.l1 = "How could I refuse then? After you, Peter!";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "houseF1", "DTSG_PiterAdams_VDom", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "That's us! Please, come in.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Thank you. May I speak with Jane? Ask her how it happened - I need all the details.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "I deeply apologize, but after a second thought, I must decline. I have got a duel to prepare for ahead. By the way, where and when is it scheduled?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "Well, of course, sir. We will both gladly talk to you and answer all your questions. Please follow me.";
			link.l1 = "Thank you, Peter.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "What a pity! But you are right, you should prepare thoroughly, of course. Two hours. Jjust outside the city gates.";
			link.l1 = "Understood, thank you. I will gladly come over once it's over. See you then!";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			npchar.location = "None";
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1 = "Timer";
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.hour = sti(GetTime() + 2);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition = "DTSG_PoP_DuelTime";
			
			PChar.quest.DTSG_PoP_Duel.win_condition.l1 = "location";
			PChar.quest.DTSG_PoP_Duel.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.DTSG_PoP_Duel.win_condition = "DTSG_PoP_Duel";
			
			AddQuestRecord("DTSG", "3");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "Welcome! Dear, you didn't tell me you were bringing guests - I would have prepared properly.";
			link.l1 = "Thank you, madam, we won't be long. Charles de Maure, at your service. I agreed to hear your story with your husband. Tell me how it happened.";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "Oh, it was horrible! Ralph was completely drunk. He started harassing me in front of the neighbors, even in front of Peter, saying obscene things...";
			link.l1 = "What exactly did he say to you?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "I'm too embarrassed to talk about it. Then he sobered up, and...";
			link.l1 = "Apologized and asked to cancel the duel, perhaps?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "Not once.";
			link.l1 = "I'm sorry for you. I would like to know one more thing, if you allow, madam.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "And what is that, sir?";
			link.l1 = "What life circumstances and trials forced you and your husband to live here? In any English city, given your husband's merits, you would have already put Ralph in his place.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "I beg your pardon, sir, but how dare you?! If you weren't my captain, I'd grab a chain shot and give you a good thrashing!\nNot only do you distrust such a worthy man as Mr. Adams, but you also mock a lady in distress...";
			link.l1 = "Did you hear me mock a lady? No? Then don't slander me. Our people could have helped them, that's why I asked.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "Calm down, Charlie! How could you... I just wanted to know more about Jane and Peter's hardships and sympathize with them. In English colonies, they would surely have been helped by now.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "Life can turn out in many ways... The shipwreck. Or someone's slander, which can sometimes force even such honest people to hide in disgrace\nIf you're so distrustful and suspicious - you can talk to the neighbors. I'm sure they will confirm every word. But old Charlie wouldn't stoop to discussing people's grief behind their backs!";
			link.l1 = "Didn't you hear me? I said I would help these people.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "Life can turn out in many ways... The shipwreck. Or someone's slander, which can sometimes force even such honest people to hide in disgrace\nIf you're so distrustful and suspicious - you can talk to the neighbors. I'm sure they will confirm every word. But old Charlie wouldn't stoop to discussing people's grief behind their backs!";
			link.l1 = "Didn't you hear me? I said I would help these people.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "Thank you from the bottom of our hearts. We will remember you in our prayers.";
			link.l1 = "That's good. By the way, about our matter. Where and when did you arrange the duel, Mr. Adams?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "Outside the city gates, sir. In two hours.";
			link.l1 = "I'll make it. Expect me with good news. And don't think of lighting a candle for my repose ahead of time!";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "Is something bothering you, Captain? You look very thoughtful.";
			link.l1 = "You know, yes. Something about Adams' story doesn't add up, and...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "How long will this go on, sir?! Do you react this way every time someone needs help?";
			link.l1 = "For God's sake, speak quietly. You would shout it to the whole street. I said I would go to the duel. Isn't that enough for you? Now listen to me carefully.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "Hmm, alright, Captain. Sorry for my outburst - I care about the fate of those who served in the Royal Navy. Many of us were decent guys, deserving a better fate than most got.";
			link.l1 = "I understand you, Charlie. Now remember what needs to be done. I want you to send some of the crew to the city gates. As the time for the duel approaches, let them gather quietly and be ready for my signal.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "Do you intend to turn an honest duel into a murder?";
			link.l1 = "I suspect it won't be entirely honest. I'll signal only if necessary. If everything is truly above board, I'll be happy to be wrong. Do you understand now? Do you remember what happened a month ago?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "Understood, sir. Frankly, I'm not too happy about it, but I'll do what's necessary. Don't worry.";
			link.l1 = "That's what I wanted to hear.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.location = "None";
			AddDialogExitQuestFunction("DTSG_Knippel_36");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "So, de Maure. You're early. And we're still in the city. Though it doesn't matter. Too bad you didn't bring that old fool with you. But no worries, we'll get to him eventually.";
			link.l1 = "At your service any time. Mercenaries, are you? Who did I cross?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "That's just it, no one. We're after that old fart, Charlie, and it's easier to find him through you, as we learned he's now on your ship. This isn't the jungle, so we'll have to act quickly to avoid drawing a crowd. But here, at least, you won't get away.";
			link.l1 = "I suppose this whole duel thing was a trap?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "A bit late to realize that, friend. We would have fought anyway - I'm Ralph Faggle, at your service.";
			link.l1 = "Actually, I suspected as much, so I decided to talk to the neighbors. By the way, is Adams involved in this too? And what about Jane? Could she be...";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "Curiosity killed the cat, haven't you heard? You were told to show up for the duel, not to snoop around. You could have a chance to live through this mess\nOf course. Provoke the old serviceman and force his commanding officer to duel - a perfect plan we came up with Peter, I think. And Jane did her part well too.";
			link.l1 = "Tell me, who wanted to get rid of Charlie?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "Ha, as if I'd tell you? Defend yourself.";
			link.l1 = "Pity. Then I'll ask Peter later.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "Oh, I see you took my story to heart and already punished Ralph, Captain.";
			link.l1 = "Of course, since as you noted, I'm a worthy and noble man. And now I'll have to punish you as for this treacherous trap.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "You're welcome to try, Captain - surely you're already exhausted and wounded.";
			link.l1 = "Then let's take a break. In the meantime, tell me, who do you work for?";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "Sorry, but my patron wouldn't like that, even if I successfully dealt with you afterwards. Which, by the way, will happen now.";
			link.l1 = "Damn it!..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "I can't believe these... these scoundrels not only deceived us but lied about the Royal Navy! How dare they! If they weren't dead, I'd make them swallow a couple of chain shots for such treachery!..";
			link.l1 = "People lie about all sorts of things, Charlie. I thought you knew that well. But what you surely know is who sent them. This isn't the first trap set for you recently. They had a letter with a detailed description of you. Who did you anger so much?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "Well, I... Maybe we'll find something else in the Adams' house, sir?";
			link.l1 = "Dodging the question? But you're right, I planned to search it thoroughly anyway. Let's go.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "Holy cannonballs, so much gold!";
			link.l1 = "Too bad there's nothing else here. 'Jane' is nowhere to be found either. Do you think she's still alive?";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "I don't know, sir, such scoundrels are capable of anything...";
			link.l1 = "That's true, but it seems to me you know more than you're saying. This isn't the first time they've hunted you. And each time we find a heap of money on them.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "I'm not sure, Captain, but maybe it was a moneylender from St. John's.";
			link.l1 = "How did you cross him?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "Well... some time ago, I borrowed money from him to pay off all my other debts. Richard promised to pay for it, but...";
			link.l1 = "Do you think he didn't?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "I wouldn't have believed it before, but after what he did to you and hurriedly left the Caribbean with Abi... Maybe he forgot about the debt. Or he didn't but left anyway... Richard acted like a real dick, sir. I wouldn't be surprised but still disappointed if it turns out to be true again.";
			link.l1 = "Don't be so categorical prematurely, Charlie. So, St. John's it is.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "Ah, here you are, sir - it seems everyone decided to come early. Judging by your appearance, you seem quite light-hearted, are you so confident in your abilities?";
				link.l1 = "Naturally, this is far from my first duel.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "I was afraid you wouldn't come, sir. The others are already here.";
				link.l1 = "A true nobleman can only be late for his death.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "Wonderful words, sir! Meet our opponent, Ralph Faggle. And this is our second, Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "Meet...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "Our opponent, Ralph Faggle.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "And this is our second, Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "So this is Ralph? He doesn't look like a typical drunk neighbor.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "You never know who your neighbor might be, have you thought about that, Mr. de Maure? Heh-heh-heh.";
			link.l1 = "So, this is a trap... I see you've even stopped shaking. Tired of playing the fever-stricken?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "The only thing I could shake from now is laughter at your naivety.";
			link.l1 = "Well, well. I only regret that Charlie tagged along - it would have been easier and quieter to deal with you all alone...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "Well, that's wonderful!";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "Allow me to introduce...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "Mr. Stokes, our second.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "And this is Ralph Faggle.";
			link.l1 = "So that's Ralph? I must admit, I imagined him differently. But no matter, I've dealt with worse.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "Hmm, I wonder, are you naive, not understanding anything? Or so overconfident?";
			link.l1 = "And what don't I understand, Mr. Adams? Come on, surprise me.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "Usually, people behave surprised or scared in such situations, but you seem to be a different type. It'll be all the more pleasant to wipe that smug grin off your face, Mr. de Maure.";
			link.l1 = "What threats! Aren't we on the same side, Peter?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "Don't tell me you hope to defeat all of us with that old man. You are outnumbered, my dear sir.";
			link.l1 = "As I said, it's YOU who doesn't understand. Charlie grumbled a bit, but I still told him to bring the guys here just in case. As it turns out, not in vain. GUYS, GET HERE!!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "What?..";
			link.l1 = "Surprised and scared, Mr. Adams? Good to know.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "That's how you should deal with such lying scoundrels. I still can't believe they had the nerve to lie about the Royal Navy! I'd strangle them with a chain shot!..";
			link.l1 = "By now, you should know that some people have no scruples, Charlie. I said I'd take care of it, you could have stayed on the ship. Did you want to make sure I'd help these 'worthy people'? And who was right again, that it wasn't as straightforward as you thought?";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "You, sir...";
			link.l1 = "Exactly. But tell me, why would anyone want to hunt you? It's not the first time.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "I don't know, Captain. Old Charlie is just a simple cannoneer.";
			link.l1 = "Hmm, well, well. Alright, since our poor duelists had nothing useful with them... No, let's go see if we can find anything in Adams' house.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "So, this woman has disappeared too... Maybe they were preparing to flee the city right after that 'duel'? And in a hurry - so much gold here!";
			link.l1 = "You're right, because gold isn't the only thing they left behind. Another letter. They were in such a rush they forgot to burn it. Look, you'll like its content.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(reads) Well, I'd argue about 'old'.";
			link.l1 = "That's not the point now. This is the second time they've sent mercenaries after you and provided them with money and information. And they want you specifically. Tell me, you simple cannoneer, who could you have angered so much?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "I have one guess, sir, just one, and I really don't want it to be true.";
			link.l1 = "So, it's most likely to be true. Speak up.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "I once had debts to various people in St. John's, and...";
			link.l1 = "... and now you think they're hunting you? How many can afford mercenaries and such sums?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "You're thinking correctly, sir. In the end, I paid off almost all my debts by borrowing from a moneylender. He can afford all this, of course. But...";
			link.l1 = "But what? We'll pay your debt, and that's it. What worries you?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "You see, Captain, Richard promised me he'd pay it off for me.";
			link.l1 = "You think he didn't?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "I don't know what to think anymore, sir. All the time we knew each other, I knew him as a model gentleman. But after he left you and fled with Abigail... I wouldn't be surprised. That's why I said I wouldn't want it to be true.";
			link.l1 = "Guesses need to be checked first, then you can be upset, Charlie. Let's go, you'll revisit St. John's.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "Captain!!!";
			link.l1 = "What is it, Charlie, what happened?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "Happened?! Don't tell me you forgot about the duel, sir! Adams might already be hacked to pieces while you're lounging here!";
			link.l1 = "Right!.. I'll head out of town immediately.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "Captain Charles de Maure? Is that Charlie Knippel with you?";
			link.l1 = "No, this...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "Don't deny it, sir - everyone in this colony knows Charlie.";
			link.l1 = "Then why ask? How can I help?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "You can't. Please don't resist - Charlie is wanted here. We have to take him into custody.";
			link.l1 = "May I know what charges are brought against my man? Is it because of his debt? I can pay it for him. Let's go to the banker right now, in your presence.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "A debt? First time I'm hearing about it. I don't know the details, but please, don't complicate things - I'm just following orders.";
			link.l1 = "Oh, that's just great...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "Captain...";
			link.l1 = "Charlie, if we run now, the bounty on our heads will be even higher. And we can't fight our way out? I'll try to get you out, just don't do anything stupid!";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "Stop making noise and threatening this man immediately, sir. Surrender your arms and follow me this instant!";
			link.l1 = "I didn't threaten anyone, there's been a mistake. This is a business matter, not an attempted murder.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "Doesn't look like it to me. You'll have to answer to the law.";
			link.l1 = "What if I apologize and leave?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "So you can sneak back in and finish what I interrupted? Do you think I'm stupid?";
			link.l1 = "You must be if you don't want to settle this peacefully. God knows, I didn't want it to come to this...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "You killed him!..";
			link.l1 = "Consider it done by your own hands, sir. You could have just answered my questions instead of being hysterical. I swear, one more scream and I'll blow your brains out.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "Yes, I killed him. He forced me to. But you're not as brainless as him and won't follow his example, right?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "What do you want?!";
			link.l1 = "Some time ago, Charlie Knippel borrowed money from you. His friend promised to pay off his debt but apparently didn't. I demand that you stop sending mercenaries after us immediately. I'm ready to pay Charlie's debt right now if I can afford it.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "What do you want?!";
			link.l1 = "Some time ago, Charlie Knippel borrowed money from you. His friend promised to pay off his debt but apparently didn't. I demand that you stop sending mercenaries after us immediately. I'm ready to pay Charlie's debt right now if I can afford it.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "Charlie?! I would never do that to him; he's a good, honest man. Besides, his debt has long been paid off. Mr. Fleetwood, the captain of the Valkyrie, settled it to the last peso.";
			link.l1 = "Really? I know who he is. You should have said that right away. Sorry for the trouble, goodbye.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "Just like that?! You threatened me! And killed a man!..";
			link.l1 = "Did you forget what I said? One more scream and you'll join him. Goodbye.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "Still here and not hanging yet? Well, best regards from the Sussex, Charlie.";
			link.l1 = "Greetings to you, whoever you are.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "Ah, Charles de Maure. Good of you to visit poor Charlie. We were counting on that.";
			link.l1 = "Who are we?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "Doesn't matter. You've cost us significant time and money, Mr. de Maure. I think they won't mind if I deal with both Charlie and you right here.";
			link.l1 = "Well, since we are both dead anyway, might you tell us out of the goodness of your heart who we angered so much? We promise not to do it again. And who is Sussex?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "Can't do. Duty calls and, unlike you, I'm a man of action, not words.";
			link.l1 = "For fuck's sake, will anyone ever explain to me what's going on?!";
			link.l1.go = "DTSG_Killer_5";
		break;
		
		case "DTSG_Killer_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			
			for (i=1; i<=12; i++)
			{
				if (GetCharacterIndex("SentJonsPrisoner_"+i) != -1)
				{
					sld = CharacterFromID("SentJonsPrisoner_"+i);
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = GetCharacter(i);
				if (sld.city == "sentjons" && sld.location == "SentJons_prison")
				{
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			sld = CharacterFromID("SentJonsJailOff");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_SentJonsJailOff", "off_eng_1", "man", "man", 30, PIRATE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto18");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto22");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			for (i=4; i<=7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			/*sld = CharacterFromID("SentJons_Mayor");
			LAi_group_Attack(sld, Pchar);*/
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_TurmaDayPobeda");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "Well, I'll be damned, Captain, what a massacre you've made here!";
			link.l1 = "Do you object? Would you prefer the gallows? Or perhaps to rot here indefinitely?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "No, sir. Thank you for rescuing me. To be honest, I'm surprised you came, considering how easily you let them take me. And surprised how easily you dealt with the guard - he was a Sea Fox. A marine.";
			link.l1 = "I told you I'd get you out, you shouldn't have doubted. Now get out of this cell before the whole garrison gets here.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "Aye aye, Captain.";
			link.l1 = "...";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "Shit, sir, I can hardly believe it...";
			link.l1 = "By the way, tell me, what did they charge you with? And who is Sussex?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "I don't know, sir. I have no idea who they meant by that...";
			link.l1 = "Alright, we'll find out later. Now we need to get out of here.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "What are your next steps, sir? Beating the sense out of that bloodsucker in broad daylight is risky business.";
			link.l1 = "You just gave me an idea. Why beat sense out of him in daylight when we can do it now, under cover of night?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "Damn me, that's a brilliant idea, Captain!";
			link.l1 = "Exactly. Tell me, Charlie, you lived here for a while. Do you know where the moneylender lives?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "I used to know, sir, but last time I was here, he was selling his house. No idea where the new one is.";
			link.l1 = "Well, that's a problem...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "I'm sure you'll figure something out, Captain, after all, you defeated the big scary Lucas Rodenburg!";
			link.l2 = "Alright, I'll handle it. Though, if you knew where the moneylender's house was, it would be better!";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "That I did. But morning is wiser than evening, Charlie. Let's rest from the journey and go in the daytime - we're not here to murder the man afterall.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "Are you sure about that, sir? We'll lose the element of surprise.";
			link.l1 = "I'm sure and I'm tired. Besides, I just want to talk. Scare him a bit if necessary.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "What I don't know - I don't know, sorry, sir.";
			link.l1 = "Ah, never mind, let's look for him.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "Are you thinking what I'm thinking, sir?";
			link.l1 = "I'm afraid so, Charlie. There's no other famous captain with that name in the Caribbean. And Richard did go to London. So, it's unlikely to be a coincidence.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "Terrible... Though I said many harsh words about him, I never wished him something like this! And poor Abi!.. She was expecting a child. I hope she's alive...";
			link.l1 = "Indeed, wouldn't wish it to anyone. Let's hope Abi is alright. Any idea who could do this to Dick? Any powerful enemies he ever mentioned?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "You must be joking, Captain. I don't know about Europe, but here every Dutchman wanted Richard dead.";
			link.l1 = "True. Maybe someone here spent big and sent assassins after him to the Old World. Could it be that it's not this petty moneylender who is behind the attacks on you, but some Richard's mysterious enemy?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "I don't know, sir. Anything is possible at this point. But that would complicate things for all of us...";
			link.l1 = "Yes, you're right, I don't like this possibility either.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "What, who... WHAT?! What's going on?.. Who are you?!..";
			link.l1 = "Oh, come on. If I wanted to kill you, I'd do it in your sleep. So let's not complicate or shorten our lives. Nod if you understand.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "Mm-hmm...";
			link.l1 = "Very good. Calm down - I'm not here to rob, kidnap, or harm you.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "Then... why are you here? Why couldn't you come in the morning?";
			link.l1 = "Because some wealthy, influential person is hunting my friend. We have reason to believe it's you, so it's likely unsafe for him to walk these streets in broad daylight.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "But I truly don't understand what you're talking about, sir...";
			link.l1 = "Charlie Knippel. Everyone in town knows him. Think hard. He owes you money.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "Our old Charlie?? That's true, but his debt was paid long ago, though not by him personally.";
			link.l1 = "And who was this benefactor?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "His captain, lord Richard Fleetwood. If you don't believe me, I can show you my records.";
			link.l1 = "Fleetwood, you say? Then I believe you. So, you didn't send mercenaries after Charlie?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "Of course not, why would I?? And tell me, what sense would it make?";
			link.l1 = "Indeed. Well, sorry for the late visit. Good night.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "What, Charlie, hoped to hide out with your former patron tonight? He's not there. But you'll meet him soon enough. Best regards from the Sussex.";
			link.l1 = "We knew that already. And who is Sussex? And who are you?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "That's none of your concern, Mr. de Maure. Shame that you've gotten involved into this mess more than we'd like. You're an annoyance.";
			link.l1 = "An annoyance to whom? Please don't tell me I slept with the wife of a very influential and very angry Englishman.";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "Very funny. Found time to jest. Apparently, what I've heard about you is true\nWhat do we want? Charlie's head would suffice. But considering how much trouble you've caused us, this time it concerns you too - you keep poking your nose where it doesn't belong.";
			link.l1 = "I suppose we're under arrest?";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "Arrest? No, dear sir, the time for half-measures is over. This is an execution, Captain de Maure.";
			link.l1 = "Agreed. The only question is, whose.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "I didn't think Sea Foxes would be involved...";
			link.l1 = "Well, there's a first time for everything. Tell me, Charlie, who is Sussex?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "I...";
			link.l1 = "Can't you see how far this has gone? And it seems we're in the same boat, Charlie. So I have a right to know the details.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "Of course, Captain. But not here, right? Let's get off the island and talk on the ship.";
			link.l1 = "You're right. Alright, let's hurry.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "You called, Captain?";
			link.l1 = "Yes, Charlie. We need to talk. I think you already guessed what it's about.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "Aye, sir...";
			link.l1 = "Good. Tell me why your compatriots, including elite forces, are hunting you when you're not a criminal or anything.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "I really don't know, sir...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "This is not a joke, Charlie. Whoever is hunting you can give orders to the sea foxes. He's probably also behind Richard's murder. So if you have any thoughts, share them. What kind of greetings from Sussex, who is it?";
			}
			else
			{
				link.l1 = "Stop looking away, Charlie. I see you know something. As your captain, I order you to tell me everything. Who is Sussex?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "Alright, Captain. Sussex isn't a person. It's... a ship.";
			link.l1 = "Greetings from a ship? That's nonsense.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "Let me explain. May I sit down, sir? The story is long and not very pleasant.";
			link.l1 = "Of course, Charlie. Go ahead.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
			LaunchFrameForm();
			//DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "Hey, Charlie, I'm from Captain Fleetwood. He wants to see you.";
			link.l1 = "Thanks, mate. Did something happen? Usually, he sends everything through you right away.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "I don't know. He says he wants to discuss this with you directly. It's your business, sort it out yourselves.";
			link.l1 = "Oh, I have a bad feeling about this...";
			link.l1.go = "DTSG_Kurier_3";
		break;
		
		case "DTSG_Kurier_3":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "DTSG_KD1", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			/*PChar.quest.DTSG_KD1.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD1.win_condition.l1.location = "SentJons_houseH1";
			PChar.quest.DTSG_KD1.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD1.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_KD1.win_condition = "DTSG_KD1";
			
			PChar.quest.DTSG_KD2.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD2.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_KD2.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD2.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_KD2.win_condition = "DTSG_KD2";*/
			
			pchar.questTemp.Knippel.Soldiers_1 = true;
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "Good night, sir!";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "Good night. Let me pass.";
			link.l1 = "Of course, go ahead, I apologize, sir.";
			link.l1.go = "DTSG_Cortny_3";
		break;
		
		case "DTSG_Cortny_3":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			/*PChar.quest.DTSG_KD4.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD4.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_KD4.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD4.win_condition.l1.locator = "reload2";
			PChar.quest.DTSG_KD4.win_condition = "DTSG_KD4";*/
			DoQuestCheckDelay("DTSG_KD3_2", 3.0);
			locCameraSleep(true);
			
			sld = CharacterFromID("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Fleetwood";
			sld.greeting = "";
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "Ah, it's you, Charlie. Come in, come in. Close the door behind you.";
			link.l1 = "Good night, Captain. What's going on? And who was that man? A pompous peacock...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "That, I can't say. Nor can I allow anyone to overhear our conversation. Don't tell anyone about this, understood?";
			link.l1 = "Yes, sir. Did something happen? You look unusually worried, that's not like you.";
			link.l1.go = "DTSG_Fleetwood_3";
			//locCameraFromToPos(0.77, 1.87, -0.42, true, -1.34, -0.10, -1.35);
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "It seems that way to you. You don't look your best either - it's night, after all. But I'm afraid your sleep is over for tonight, my friend - we have an urgent and classified mission.";
			link.l1 = "And what will it entail, Captain?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "Eliminating a traitor. From our own. Soon, a diplomatic ship from the Old World will appear off the coast of Dominica - the frigate 'Sussex'. Officially, they are to negotiate a good deal with the Dutch. But in reality...";
			link.l1 = "... are they going to pass information to our enemies, sir?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "Even worse. Fully defect to their side. And though they will be exhausted after crossing the Atlantic, in the end, it's a good frigate that will surely try to escape if we attack with a heavy ship\nSo we need to act quickly and decisively. We can only rely on the 'Valkyrie' - she's the only one capable of such a mission.";
			link.l1 = "Will the old 'Valkyrie' handle a frigate?..";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "Ha-ha, Charlie, do you doubt your captain? Besides, as I said, they'll be exhausted. If we attack suddenly, all the advantages are ours.";
			link.l1 = "I would never! But I hope you know what you're doing, sir...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "I'm sure of it. And one more thing. This defector holds a high position in Parliament itself, understand? He may have eyes and ears everywhere - not just at home, but already here, in the Caribbean. So don't mention the Sussex or any details of our mission in town.";
			link.l1 = "You didn't have to tell me, sir. You can always count on old Charlie.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "I know. Just the stakes are higher than ever this time. Gather your things and prepare - we set sail at dawn.";
			link.l1 = "Aye, sir. Good night, sir.";
			link.l1.go = "DTSG_Fleetwood_9";
		break;
		
		case "DTSG_Fleetwood_9":
			DeleteAttribute(pchar,"questTemp.TimeLock");
			SetCurrentTime(11, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("SentJons_houseH1", "reload", "reload1", "DTSG_KD6");
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "I've never seen Richard like this... He was so worried or even... scared?";
			link.l1 = "But why? He didn't even share it with me. Well, no matter. He's a great captain, so we'll surely handle this frigate and her tired crew.";
			link.l1.go = "DTSG_Knippel_SamSoboi_2";
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Knippel_SamSoboi_2":
			DialogExit();
			SetLaunchFrameFormParam("August 17th, 1654"+ NewStr() +", SE of Dominica", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Ship_deck_Big", "reload", "reload1", "DTSG_ProshloeDominika_2");
			LaunchFrameForm();
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "The 'Sussex' is on the horizon, Charlie, get ready.";
			link.l1 = "Always ready, Captain.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "Very good. I count on you and your chain shot. Try to shred their sails as quickly as possible, or better yet, take down a mast. Engaging in a risky fight to sink them makes no sense, so I'll try to board them\nBesides, we need to make sure the traitor is dead - if we sink them, we'll still have to get close and make sure no one survives.";
			link.l1 = "And kill so many compatriots for one traitor...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "Sadly. It pains me too, Charlie. But orders are orders. At least we're not doing this for fun. So let's get this over with quickly.";
			link.l1 = "Yes, sir...";
			link.l1.go = "DTSG_Fleetwood_13";
		break;
		
		case "DTSG_Fleetwood_13":
			DialogExit();
			EndQuestMovie();
			AddItems(pchar, "potion4", 10);
			AddItems(pchar, "bullet", 10);
			AddItems(pchar, "GunPowder", 10);
			AddItems(pchar, "grapeshot", 10);
			AddItems(pchar, "cartridge", 10);
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
			PlaySound("interface\MusketFire1.wav");
			PlaySound("interface\MusketFire1.wav");
			
			SetLaunchFrameFormParam("2 hours later..."+ NewStr() +"Boarding the 'Sussex'", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Location_reserve_06", "rld", "aloc14", "DTSG_ProshloeDominika_12");
			LaunchFrameForm();
			
			n = Findlocation("Location_reserve_06");
			DeleteAttribute(&locations[n], "IslandId");
			DeleteAttribute(&locations[n], "type");
			DeleteAttribute(&locations[n], "models");
			DeleteAttribute(&locations[n], "environment");
			DeleteAttribute(&locations[n], "Box1");
			DeleteAttribute(&locations[n], "Box2");
			DeleteAttribute(&locations[n], "Box3");
			Locations[n].id.label = "Orlop deck";
			Locations[n].filespath.models = "locations\decks\oldeck";
			Locations[n].image = "loading\Boarding_B" + rand(3) + ".tga";
			//Sound
			locations[n].type = "deck_fight";
			//Models
			//Always
			Locations[n].models.always.ODeck = "oldeck";
			Locations[n].models.always.locators = "oldeck_locators";

			//Day
			Locations[n].models.day.charactersPatch = "oldeck_patch";
			Locations[n].models.day.fonar = "oldeck_fday";
			//Night
			Locations[n].models.night.charactersPatch = "oldeck_patch";
			Locations[n].models.night.fonar = "oldeck_fnight";
			//Environment
			Locations[n].environment.sea = "true";
			Locations[n].environment.weather = "true";
		break;
		
		case "DTSG_Graf_Sheffild_1":
			//StartQuestMovie(true, false, true);
			dialog.text = "Enough! I'm ready to surrender my sword and discuss your demands. But first, introduce yourself! Who are you and how dare you attack us?! This is treason!";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "Captain Richard Fleetwood. And you must be Earl Sheffield? And you're absolutely right, this is treason.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "You know who I am? Damn it! I knew something like this would happen, rats everywhere, so I asked, even begged for a warship...";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "It wouldn't have saved you, just prolonged the inevitable, as I'd find another approach. And yes, by treason, I mean yours, Earl Sheffield.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "Then you know nothing about me, sir! Everyone knows there's no more loyal man to England than I am! You'll regret this mistake, mark my words.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "I have nothing to regret, as I'm not the one defecting to the Dutch.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "What?! What nonsense are you spouting?! You've been misled, and you've followed a false trail like a mad hound\nAhem, it's true, I am heading for negotiations with the Dutch West India Company. But in the interest of our England, Captain. This is a terrible mistake, but we can still correct it.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "I'm afraid it's not up to me. And certainly not up to you. You've chosen the wrong side, gentlemen. Goodbye.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "We're done here. I thought that fat man would never stop squealing. Oh, these earls, right, Charlie?";
			link.l1 = "I just wonder, sir, what if the colonel was wrong? Or, God forbid, lied to us to get rid of the Earl?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "Listen to me, my friend. And listen carefully. Our service is very dangerous and difficult, in every sense. Anything can happen - a sad mistake, a ridiculous coincidence, or a treacherous betrayal\nServing the country isn't just loading cannons with cannonballs, Charlie. For powers that be it's making tough decisions. And for soldiers like us - executing those decisions.";
			link.l1 = "But what if we shed innocent blood one day, Captain? That will be on our hands, our conscience.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "Then the blood will be on their hands as much as ours, if not more. Let that comfort you. The main thing is our intentions were pure - to eliminate the enemy of the homeland\nNow help me, Charlie, we still need to make it look like a Dutch attack.";
			link.l1 = "Yes, sir...";
			link.l1.go = "DTSG_Graf_Sheffild_25";
		break;
		
		case "DTSG_Graf_Sheffild_25":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Kortni", "off_eng_5", "man", "man", 40, ENGLAND, -1, false, "quest"));
			sld.name = "Thomas";
			sld.lastname = "Lynch";
			sld.rank = 40;
			GiveItem2Character(sld, "blade_16");
			EquipCharacterByItem(sld, "blade_16");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterByItem(sld, "pistol6");
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			LAi_SetHP(sld, 400.0, 400.0);
			FantomMakeCoolSailor(sld, SHIP_HIMERA, "Сhimera", CANNON_TYPE_CANNON_LBS20, 70, 70, 70);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			sld.Ship.Mode = "war";
			sld.alwaysEnemy = true;
			sld.Coastal_Captain = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("DTSG_KortniAttack");
			Group_SetType("DTSG_KortniAttack", "pirate");
			Group_AddCharacter("DTSG_KortniAttack", "DTSG_Kortni");

			Group_SetGroupCommander("DTSG_KortniAttack", "DTSG_Kortni");
			Group_SetTaskAttack("DTSG_KortniAttack", PLAYER_GROUP);
			Group_SetAddress("DTSG_KortniAttack", "Antigua", "Quest_Ships", "Quest_Ship_10");
			Group_LockTask("DTSG_KortniAttack");
			
			SetLaunchFrameFormParam("Present time", "DTSG_SegodnyaVremya", 0, 4.0);
			LaunchFrameForm();
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "So, we left false evidence to make it seem like the Dutch did it. Richard and I never discussed that day again.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Well, a lot makes sense now. I think a relative or a supporter of the Earl is behind Richard's death. But why target you? You're just a cannoneer and didn't make any decisions that sad day.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Indeed. This is bad business and it stinks. Maybe someone found out and decided to avenge the Earl. But is one cannoneer worth such expenses? Money, mercenaries, employing Sea Foxes... No way, Charlie.";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "Maybe this person is hunting down everyone from Richard's former crew. What do you think, sir?";
			link.l1 = "I think we should distance ourselves from Antigua, and the sooner, the better.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "I've asked myself that question too, Captain, but I haven't found an answer.";
			link.l1 = "Fuck. Someone's coming. I asked not to be disturbed!";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Helena_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Tichingitu_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
				sld.name 	= "Alonso";
				sld.lastname = "";
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Alonso_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.location = "None";
			}
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Charles!..";
				link.l1 = "What's wrong, Helen??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "Charles, I remember you asked me not to let anyone in and not to disturb you and Charlie, but...";
				link.l1 = "... you decided to come yourself. Alright, it's alright, Helen.";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "An English warship! She was spotted some time ago. At first, I didn't pay attention, but she will reach us any minute now! I've never seen such a fast ship.";
				link.l1 = "Then thank you for telling me. I hope we have time to prepare before she closes by. Helen, Charlie, battlestations!";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... you can continue your secret meeting later. An English warship is heading our way. I thought it was important.";
				link.l1 = "Well, I'll go take a look. Thanks, Helen.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "Captain, a fast ship is coming towards us. Very fast. The spirits whisper to me that their intentions are evil.";
			link.l1 = "Thank you and the spirits for the warning. Prepare for battle just in case. And pass this message to the others from me.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "Excuse me, for the interruption, Captain, but it's urgent.";
			link.l1 = "Oh, I hope it's really important, Alonso. Report.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "An English ship is approaching. It's... the 'Mirage', Captain.";
			link.l1 = "What? Are you absolutely sure? Been drinking again, eh?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "I'm sure, Captain - there's no other ship like it in the Caribbean, you know that.";
			link.l1 = "Indeed. I'll go take a look myself - let's see if this 'Mirage' is real.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "Oh... But it's not over yet! Brian, there you are! Where the hell have you been?";
			link.l1 = "This will only delay the inevitable.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "Charles de Maure. To think how far you've come. Pity. I hoped to catch you off guard on this ship.";
			link.l1 = "You know who I am? So, it's you behind our recent troubles - you look like a high-flying bird forced to leave its cozy nest and come out personally instead of sending another vulture.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "Correct, on both counts. I suppose a nobleman can recognize another from afar. Colonel Thomas Lynch. It seems it's time to talk like gentlemen, rather than try to destroy each other. Perhaps we can reach a mutually beneficial agreement.";
			link.l1 = "I can't promise anything, but I give you my word as a nobleman that at least we'll talk like civilized people, Colonel.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "Very well. I couldn't have had such a conversation with Fleetwood. Still, we found leverage on him, and he won't trouble us anymore. It's a shame it didn't work out with you, but never mind.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "The entire Caribbean is talking about Richard's death. So, it was you! And I assume the leverage you mentioned was Abigail? What happened to her, by the way?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Not a threat, you say?.. So, you killed him? Are you a supporter of the earl?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Abigail? Ah, the young Jewess, his fiancée. Once again, you have proved to be a quite perceptive individual. She is alive and well - we promised and delivered on that in exchange for Fleetwood's cooperation.";
				link.l1 = "Quite the cooperation, I must say. But why did you do it? Are you a supporter of the Earl?";
			}
			else
			{
				dialog.text = "Supporter? Oh, quite the opposite. But you see, some cards can no longer be played as they become a burden for the player. Unfortunately, Richard became one of them.";
				link.l1 = "I see. You eliminate all witnesses. What happened to Abigail? Did you kill her too?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Not at all. Quite the opposite. But Richard knew too much, and by returning to the Old World, he became dangerous. He should have stayed here, and we wouldn't have taken his life.";
				link.l1 = "Do you eliminate everyone who has ever worked for you, Colonel?";
			}
			else
			{
				dialog.text = "Who? Ah, his fiancée, I suppose. She was the leverage. His life for hers. She's fine, I swear on my honor.";
				link.l1 = "I doubt you know what honor is, considering what you've done, Colonel.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "I won't answer that provocation, sir.";
				link.l1 = "Then answer this - how did you get this ship? Is it... the 'Mirage'?";
			}
			else
			{
				dialog.text = "I'll overlook this insult because it's coming from someone who has never had to wield power and influence the order of things.";
				link.l1 = "Speaking of things, where did you get the 'Mirage'? Is this her?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "Not exactly. A magnificent ship, eh? Too bad it didn't fulfill her purpose against you. Do you know the history of this ship, Captain de Maure?";
			link.l1 = "You mean the ghost ship and the hunt for English merchants?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "That? Oh, no. I'm not talking about well-known things. I mean things that are hidden from sight. This ketch was designed by Johan van Merden and Lucas Rodenburg\nThat sweet couple created a chain of schemes, and the ship was eventually launched from the shipyard in Havana. We were lucky to get our hands on the original blueprints. And in the end, we recreated the Mirage in all her glory and even improved her, correcting some flaws in her design.";
			link.l1 = "Too bad, as you noted yourself, it didn't help you much, Colonel.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "Are you in a laughing mood? Don't be. I admit, you surpassed me both as a captain and a fighter. But I still hold the upper hand here.";
			link.l1 = "Is that a dying bluff? Or just the usual overconfidence of people like you? What lies behind these words?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "Excellent question. It seems to me you're more than a whoring rake and duelist, as my research suggested. I took measures for all outcomes of this meeting. Even the one where I die by your blade, bullet, or stray cannonball. If I die today, you and Charlie will regret not joining Fleetwood.";
			link.l1 = "More bounty hunters? Please. It was unpleasant and tedious, but not deadly. We fought them off then - we'll fight them off again.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "I have no doubt. Now I see the carefree duelist speaking again. Not just bounty hunters. The full force of Sea Foxes and the English naval intelligence will crash on your head like a storm wave on a fisherman's boat.";
			link.l1 = "What do you want from me? You don't expect me to surrender?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "Of course not. We've studied you well over all this time. I want to offer you a mutually beneficial deal. One that it would be unwise to refuse. And as two noblemen, I hope we can come to an agreement.";
			link.l1 = "Then I repeat the question, Colonel, what do you want? I assume Charlie?.. And you think you can offer me something in return? I won't betray for a few gold coins.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "Correct again. It's not just about a few gold coins, as you put it, but a whole mountain - 10,000 doubloons. The deposit will be waiting for you at the banker in Port Royal if we come to an agreement\nBut the most important thing I offer is your life, Captain de Maure. You heard me. We will cease all pursuit if we all lay down our arms now, and you hand over Charlie to us\nHave you heard the expression 'man against society'? In your case, if you refuse, it will be 'man against the state'. Decide, Charles. Here and now.";
			link.l1 = "You can easily use your title and influence to intimidate a fool or two. But I'm no fool. And I sense desperation a mile away. Get out. And be glad I didn't kill you - you more than deserve it.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "You don't really need Charlie, Colonel. You need his silence.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "I agree to this for the safety of myself and my men, not out of greed for your money, just so you know.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "You've made one of the worst decisions of your life, Captain de Maure. I don't envy you. Honestly. You'll have yourself to blame - no one will make you similar offers again. Especially not me. Goodbye.";
			link.l1 = "Wait, Colonel.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "What, have you changed your mind? My words finally had an effect?";
			link.l1 = "Right, just the opposite.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "What do you mean? Explain yourself.";
			link.l1 = "Your words only strengthened my resolve against you. Don't look like that - I won't kill you. And as I said, I'll even let you go. But I think you'll manage without a boat.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "I don't need it, as I have a ship.";
			link.l1 = "You're right. But only about not needing it. You may be an influential man. But you lack a sense of measure. And tact. I'll do what you are used to doing - be the master of the situation.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "You are not, Captain de Maure. Don't deceive yourself.";
			link.l1 = "Fully? Maybe not. But neither are you - your life is now in my hands, Colonel. It doesn't matter what happens to me later - now I can do whatever I want. And I... take this ship. You're free. The shore is not far.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "You wouldn't dare. But judging by your look... Enjoy your little victory. You've made...";
			link.l1 = "Yes, yes, one of the worst decisions of my life. I've heard it already. Off this ship. My ship. Will you jump yourself, or should we throw you overboard?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto4", "", "", "", "DTSG_Kortni_Vyprygnul", 7);
			npchar.lifeday = 0;
			npchar.location = "None";
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "I never thought I'd see him like this - humiliated, jumping out the window, and swimming to shore on all fours.";
			link.l1 = "Got a glimpse? Satisfied? Wonderful. You're next.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "What are you saying, sir? We're not enemies; I was just following orders!.. Can I at least ask for a boat? You'll never see me again!";
			link.l1 = "You wouldn't spare me if I was in your shoes and just a lost a battle to you. So be glad I didn't kill you. Out the window. Now. Maybe you'll catch up to your patron.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "I'd rather die than face such humiliation, monsieur!";
			link.l1 = "As you wish.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "That was the Colonel, right, Captain?";
			link.l1 = "Right. Look out the window, Charlie, you won't regret it.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto4", "DTSG_Kortni_Vyprygnul_5", 6);
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "The Colonel?.. I'd never have thought I'd see something like this, sir. That someone would dare throw a man with such a title overboard like a common sailor! Richard would never do that - respecting rank was a core part of him.";
			link.l1 = "It was beaten into him over years of drill. He's a military man, with the corresponding mindset. I'm not, and I think broader, without such... restrictions.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "And we won't get in trouble for doing this to him?";
			link.l1 = "Heh, you blame Richard, but think like him. We dared to resist, so we'll be hunted for a while. But sooner or later, even the English navy will give up on us. And for Lynch, it will become a personal matter. But we made sure he won't get state resources behind him next time.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "You know, Captain, from this day, I respect you even more. I'll never regret not leaving with Dick on the Valkyrie and deciding to join you.";
			link.l1 = "Thank you, my friend! Be ready - the storm is gathering upon us. But you know what? Something tells me we'll come out victorious again. Let's go, it's time to get back to the deck.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "That's not entirely true, although personally, I don't care about Charlie if he keep his mouth from now own. But my colleagues would like to see his body. And they know what he looks like\nThis is a read life, Charles, not a child's fairy tale or a knightly poem read to us by nannies in childhood, and I don't see a solution that pleases everyone.";
			link.l1 = "But I do. You can always find a similar body. And buy similar clothes. Grease some wheels. And I'll talk to Charlie. And I give you my word as a guarantee.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				dialog.text = "It's... a big risk. And it's not just about whether I can trust your word. But whether my colleagues will believe me when they see a body resembling Charlie's. And I won't take that risk... just like that.";
				link.l1 = "How much?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				dialog.text = "The word of a man with your reputation? You're joking. Noble birth alone isn't enough for trust.";
				link.l1 = "Hearing this from another man with similar birth and actions, forgive me, Colonel.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "You're right, of course. But in this case, it's about my trust, not anyone else's. And you as a guarantor don't suit me\nI tell you one last time. Give me Charlie. If, of course, you don't want to share Fleetwood's fate.";
			link.l1 = "You can easily use your title and influence to intimidate a fool or two. But I'm no fool. And I sense desperation a mile away. Get out. And be glad I didn't kill you - you more than deserve it.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "Finally, straight to the point. A million pesos. Final offer.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "I'll pay you the money. Don't think I'm poor or don't value my men's lives. Neither is true. Take it.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = " You have a good appetite, though I didn't expect less. But right now, I don't have that much, and...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "No silver - no deal. Did you think I'd show mercy? Do I look like a saint, sir?";
			link.l1 = "But maybe you could wait a bit? Where and when would be convenient for you to meet again? I could borrow the doubloons from a moneylender.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "Then you think I'm even more naive than I thought\nI'm not a country girl ready to wait forever for someone who once had his way with her\nNo money? I didn't ask for it anyway. I only want Charlie. You are of no use to me despite all the trouble you've caused.";
			link.l1 = "You can easily use your title and influence to intimidate a fool or two. But I'm no fool. And I sense desperation a mile away. Get out. And be glad I didn't kill you - you more than deserve it.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "Are you really that attached to poor Charlie? In any case, your nobility deserves respect. Make sure your cannoneer is as silent as the grave. Or you'll both end up there.";
			link.l1 = "I promise. And you keep your word and stop all pursuit.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "I promise too. And one more thing. Despite your honest victory, I'll take my ship with me. It's a custom-made piece, you know. And very expensive.";
			link.l1 = "What about the victor's right? But I won't push my luck. This time.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_Fade("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "I'm almost sorry to say this, Brian, but I'm afraid our cooperation ends here.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "I... am free, Colonel? Will you lift the bounty on my head, and I can start anew as if I'm a law-abiding man?";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "I'd say you have seen too much - just like late Fleetwood. I've essentially received a bribe right in front of you just now.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "I... I won't tell anyone anything, I swear to God!";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "Of course, you won't.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "No!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "Don't look at me like that, Charles. If I constantly worry about whether Brian will spill the beans, I won't be able to sleep at all.";
			link.l1 = "I don't even know if I should be surprised by what I've seen or not.";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "You shouldn't. I am committed. All I require from you two is to keep your mouths shut about what happened. I'll try to find a similar body, fix its face properly, make a good use of the money and persuade my colleagues.";
			link.l1 = "Thank you, Colonel.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "There's nothing to thank me for yet. There's always a risk they won't believe me, and then the hunt will reopen. For now, goodbye, Captain de Maure. I'm sailing off on my ship. No objections here - I've already done you and Charlie a great favor.";
			link.l1 = "Well, farewell then.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_26";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "Do you even know who you were talking to, Captain? A colonel! Was he the one who orchestrated all this mess?";
			link.l1 = "I know, he introduced himself. And you're right - he was.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "It's strange, sir, because I once knew him as Richard's superior. How is this possible? And why is he leaving as if nothing happened? What did he want, anyway?";
			link.l1 = "Actually, there's nothing strange about it. Those who carry out shady orders often risk their lives not so much because of enemies, but because of their superiors. And he wanted your head, Charlie.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "I don't understand, Captain. Why is he leaving then? Did he accept defeat?";
			link.l1 = "That's not like him at all. I had to give him gold weighing roughly as much as your head. Maybe a bit more than that. A million pesos, to be exact.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "And you... paid him that enormous amount? For me?..";
			link.l1 = "Well, not just for you. For myself as well. And for all the boys, too. But yes, Charlie, primarily for you. If we had killed him, we would have faced punitive expeditions for eternity afterward.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "I... can't believe this, sir. Just... thank you. I didn't think Fleetwood would do that in your place.";
			link.l1 = "You're too biased against him after his escape. Richard just wanted a quiet and peaceful life with Abigail. I'm sorry it didn't work out for him. Plus, he kept his word and paid your debt. Heh, I, Fleetwood - you sure do get lucky with captains, huh, Charlie?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "No kidding, Captain. So, is everything over now?";
			link.l1 = "Yes, my very expensive friend. At least for now. The fight is over - you can tell the boys to stow their weapons. And let them prepare to hoist the sails.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "I couldn't care less why you agree - whether out of greed, fear, or duty to your men. The main thing is you agree. I'll send my man to Port Royal with instructions for the banker.";
			link.l1 = "Fine. I can't believe this is finally over.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "You know what, to hell with the money. One can always find more. There's something else I want from you in exchange for Charlie, Colonel.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "Oh? I must admit, you surprise me, Captain de Maure. And what, in your opinion, would be equivalent to the old cannoneer's bald head if a mountain of gold doesn't suit you?";
			link.l1 = "You said it yourself - a magnificent vessel, with design flaws corrected. I'm eager to try her myself. You still have the blueprints. But there's only one Charlie. Plus, it's in your interest to keep me satisfied.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "You're a tough negotiator. Do you have any idea how much it cost us to build just one of these?";
				link.l1 = "(Trustworthy) (Honor) I know perfectly well, that's why I ask. Your hand is in my jaws up to the elbow. You can try to shoot this wolf. But you'll lose the hand. And not just it.";
			}
			else
			{
				dialog.text = "I'm afraid building one of these costs far more than the gold we prepared for you. But you amused me, Charles. In a good way.";
				link.l1 = "It was worth a try.";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "I see you know what you want and pursue your goals in life\nWell, alright. The ketch is yours. But forget about the money - the moneylender will tell you he knows nothing.";
				link.l1 = "That suits me.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "Definitely. My life has been a story of seizing opportunities and securing myself from risks\nSo bring Charlie here, and we'll part in peace. After that, you can even take the deposit. But I'm leaving on this ship.";
				link.l1 = "Then let's settle it.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "I can't say I'm fully satisfied. But I want to end this quickly. Now give me what I want.";
			link.l1 = "Not 'what', but 'who'. But as you wish.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "Nor can I. I'm starting to believe it's not just about what a man is but who he surrounds himself with - a simple job of catching an old cannoneer turned into a headache because of his captain, that is, you, Charles\nCall Charlie here. This mess will end for good - we'll weigh anchor, and our ships will part.";
			link.l1 = "Part, you say?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "You look surprised? You must have thought the ketch was your rightful prize? We're not pirates, Captain de Maure. Civilized people live by different, much more complex rules. The ship stays with me.";
			link.l1 = "Well then...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "Are you alright, sir? Is that... the colonel?";
			link.l1 = "Yes, Charlie, it's the colonel. You came just in time - I was about to go fetch you myself.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "Fetch me, Captain?.. Right now? Why have you been talking to this... man for so long? I thought you were in trouble, so I came here myself.";
			link.l1 = "Correct. We're still in trouble despite the victory. And we would continue to be if the colonel and I hadn't found a solution.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "Did you manage to convince him to leave us alone, sir?";
			link.l1 = "Unfortunately, just me. Not us. You... will go with him, Charlie.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "What?.. But why?.. We won!";
			link.l1 = "Don't you understand? We can't keep on winning constantly - they won't stop until they get your head.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "I can't believe you're doing this to old Charlie, Captain. You're just like Dick. Both of you once told me you were my friends. And both abandoned me and everyone close to them.";
			link.l1 = "That's the burden of a captain, his responsibility. I see you can't understand that because all you had to do was load cannons with cannonballs.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "Can't understand?.. Maybe I'm just not a traitor like you? You know where you should go?";
			link.l1 = "To Hell? Maybe you're right. We all deserve it.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "Up yours, sir.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "Hilarious. I almost laughed. Did you hear that, Brian?\nSometimes hearing simple peasants talk feels like a breeze and not irritating at all. You've made the right decision, Charles. I understand how hard it is for you. But take comfort in knowing that neither you nor anyone else of your men will suffer now.";
			link.l1 = "I hope you keep this promise, Colonel.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "I'm a man of my word. Abigail's fate is a proof of that. Look at Brian too. A French pirate, but he made the right call when it was time to join the right side. And no one touches him as long as he serves us faithfully. Like him, you're moving in the right direction, Captain de Maure.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "Speaking of moving. I want to get out of here as soon as possible. On this, undoubtedly, fast ship that you promised me, Colonel.";
			}
			else
			{
				link.l1 = "I'm not a pirate. And I don't plan to join the English fleet just yet. But I do intend to claim the promised reward.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "I won't hide it - it feels like tearing her from my heart. I'll have to spend on a new one, but perhaps it's worth it - too long have I been troubled by the thought that Charlie might spill the beans\nIf you don't talk or commit serious crimes against England, consider that we're no longer enemies. Enjoy the new ship; she's indeed beautiful. Goodbye, Charles. Brian - prepare a boat for us. Charlie - follow me as you have no say in the matter.";
				link.l1 = "Goodbye. All of you.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "A pity, we always need capable people, regardless of their nationality. But of course, you still deserve the reward. You can safely go to Port Royal - I'll get there before any other ship on this ketch.";
				link.l1 = "I hope so. And I hope there won't be an armed escort waiting for me in Port Royal.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "Doubting my word again? Shame on you. You've earned the gratitude of the entire English navy. If you ever need anything, or decide to join us, reach me out, Captain de Maure.";
			link.l1 = "Once, I tried to gain support and connections with English intelligence. It didn't work out. So goodbye, Colonel.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 
