void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bug. Let us know.";
			link.l1 = "Sure!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "Good afternoon, captain... ehm... kha-hahrm! Bloody mines... Let me introduce myself. Adam Rayner. I am a simple man and do not like long forewords, so I'll spit it out right away. Do you want to make good money? I offer you a small business, which neither of us can handle alone.";
			link.l1 = "Heh! Good money? Interesting. I'm listening, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "You know, I'm sorry, but you don't seem trustworthy. So I won't do any business with you.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Trustworthy? Ha-ha! One shouldn't judge a man by his face. Well, never mind. You've just missed a good opportunity to make easy money quickly. I will find someone more cooperative...";
			link.l1 = "Our conversation is over, sir. Goodbye!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Kha! Pleasure doing business with such a quick-thinker as yourself, Captain. So, the job is simple: there is a fluyt filled with a decent amount of silver and she will soon set sail from one of the local ports. A single vessel, no escort. Silly, right? K-kha\n Easy as pie. I tell you where and when, you take the prize and I get my cut.";
			link.l1 = "And of course, you want to receive it in cash right now?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Do I look like a pathetic crook, captain? No way. I will join you in this raid and we shall do it together. I won't stay in the hold during the fight, quite the opposite - I ask you to put me in the boarding party as your officer, temporarily, of course\nI know my job, I know how to stab and shoot folk. So I will risk my neck just like you... khe... kha! You will pay me my share after we capture the fluyt.";
			link.l1 = "What share of the loot do you claim for yourself?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "I am not a greedy man, captain. My share is only as much as can be loaded in the hold of my old longboat, and that is about 200 packs of silver. According to my information, there will be no less than 2,000 packs of silver on the fluyt, so I will take a tenth. That's fair, don't you think?";
			link.l1 = "Tenth of the loot just for information? I buy such information from drunkards for a glass of rum at the local tavern. No, we are not going the same way, friend!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. I suppose I agree. I accept your offer, Adam. Welcome aboard. Now, about your information: where from, where to, time, name of the ship?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "What a miser you are, Captain! In that case, you'll get nothing! See ya!";
			link.l1 = "Good luck! Find another simpleton for your shady undertaking!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "The name of the fluyt is the "+pchar.questTemp.FalseTrace.ShipName+", she departs from Cartagena and sets sail "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". We don't have much time, though. Two weeks, three at most. If we don't find her in three weeks, it's over.";
			link.l1 = "Let's not waste time, then! Adventure calls!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Did you want anything, captain?";
			link.l1 = "Nothing, never mind.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Did you want to see me, Captain?";
			link.l1 = "I think you saw this coming... Where is the silver, damn it? Where is it? I am talking to you! The captain of the fluyt told me that it was a foraging vessel! You lied to me!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Calm down, Captain. I'll try to explain everything.";
			link.l1 = "Of course you will! I have already calmed down! The only reason you are not hanging from the yardarm right now is because I still cannot understand your motives. You pursued this fluyt with me, knowing all along there was no silver. So please, explain yourself.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Yes, I really fooled you, Captain. But that was the only way to persuade you to do what I needed, to capture... khe kha! To capture this damn fluyt\nBut I promise I will repay my debt to you. Now let me tell you why I did it. Did you find a woman on the fluyt? I saw crewmen taking her onto your vessel...";
			link.l1 = "Hm... So, you needed the girl? And that's why you forced me to start a sea battle and kill so many people!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "It's my wife. Katerine Rayner. She ran away from me three months ago with this pathetic captain. I made every effort to find them, and I did. They were both going to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". I couldn't imagine a better way to bring Katerine back and deal with that wife-stealer\nIf I told you the truth, you would have walked away. So I had to tell you a juicy story about a fluyt filled with silver.";
			link.l1 = "Hmpf... Your wife left you, didn't she? Very interesting!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "This is my lawful wife, I love her and no one else has the right to be with her! That scoundrel told her beautiful lies about romance and all that nonsense when I was... away. Don't you know women? She believed that rubbish, silly girl, and ran off with him.";
			link.l1 = "Alright, listen, I don't really care about your family life, so sort it out with your wife. But you mentioned compensating my costs, didn't you? Did I hear you right?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Yes, you heard me right, captain. A favour for a favour. I do not have money right now, but if you bring Katerine and me to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", I will give you completely reliable information about where you can fetch some gold without any effort.";
			link.l1 = "Very interesting. And why can't you tell me this completely reliable information right now?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Because, I don't have this information yet. Let me explain in detail. One gentleman of fortune named Squint-eyed Solly - have you ever heard of him? - is going to plunder some gold mines not far from Blueweld\nBecause of certain events, he will have to leave all his gold in a hidden place and post a few guards to protect it. The man himself will go on foot to Belize or to Blueweld in order to get a ship\nI have an agent among Solly's crew, he will be waiting for me in "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". Once we drop anchor there, he will tell me where Solly hides his goodies\nYou will go there, eliminate the guards and take all the gold for yourself. I was going to do it myself, but considering the current situation, I'll leave everything to you. No charge.";
			link.l1 = "Your story sounds much like your previous fable about a fluyt loaded with silver. You have already deceived me once. How can you guarantee that you are not lying this time?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "I give you my word. I don't have any other guarantees. But it's true, I swear khe... kha...  damn mines!";
			link.l1 = "Alright. Now go, and I will think about what you've said.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "Don't think too long. Squint-eyed Solly will return for his treasures, as you should realise. According to my calculations, you have only two weeks to get to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "I will keep that in mind. And now go to the crew's quarters and join the sailors. I think you'd better be separated from your wife until our arrival. You can go now.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Did you call for me, captain?";
			link.l1 = "Yes. Adam Rayner, I will arrest you and lock you up. You have cheated me, and I don't have any other choice but to isolate you and turn you over to the authorities.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Really? I expected you to do so, Captain. Especially after you came to the hold and shared a talk with that filthy snatcher of other men's wives. You decided that you're on his side, did you not, Captain?";
			link.l1 = "None of your business. You used me, you have crossed me, and now you're trying to deceive me again with absurd tales of treasures! Bosun, take him away!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Kha, not so fast, Captain... The bosun and the rest of your crew won't be able to come in here anytime soon. Haven't you noticed that I've locked the door? Now we're alone here - just you and me. So show me, Captain, what you're made of!";
			link.l1 = "Really? Do you truly believe you stand a chance?! You'll regret this, bastard!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "That's better... Lay down your arms, scoundrel! Bosun! Put this rascal in irons and throw him in the hold!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Thank you, Captain, for helping to bring back my wife! Adam Rayner is in your debt, he won't forget it, ha-ha, I swear to... kha! Damn mines! Now, about Squint-eyed Solly. My man has already given me all the details. Solly left all his loot in a grotto in San Juan del Norte bay. The man himself is in Blueweld now\nYou should hurry, you have only five days, according to my pal. Take your men with you, Solly's bandits are tough, they'll give you some trouble\nTime to say farewell. Thank you again, Captain, Godspeed!";
			link.l1 = "Good luck to you, Adam. Don't offend your wife!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Ha! Why on earth, Captain, have we come ashore in this bay? I told you that my man was waiting for me in the port of "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"! Are you planning to go there on foot through the jungle?";
			link.l1 = "Bad guess, Adam. Did you really think that I would believe your nonsense once again? Do you think I am a complete fool? This time I've made a deal with your wife.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "What?! Ha! What kind of deal with my wife? What are you talking about, you rotten fish?!";
			link.l1 = "Because of your false information, I captured an empty fluyt and killed her captain. I regret having done that, though it is too late for regrets. Your wife was in love with that sailor, as I understand. That's why she asked me to kill you. That's why we are here in this bay now.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "I can't believe it! Katerine ... what a bitch! Well, you'll get what you deserve yet... So, how did she promise to pay you, fool? She hasn't got a penny, she even sold all her jewellery to run off with that captain!";
			link.l1 = "That's none of your business, scoundrel. But it is time to finish our conversation. I'll send you to hell, where you should have been for quite some time already!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Let's see what you can do, rotten herring!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Ah! Why on earth did you attack my ship, you scum? I cannot understand...";
			link.l1 = "Don't pretend to be a lamb, captain. I know what kind of cargo you're transporting. I need it.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Cargo? Ha-ha! What kind of cargo did you expect to see here? My holds are empty!";
			link.l1 = "What did you say, scoundrel! Say that again!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "I repeat - I don't have any cargo on board. This fluyt is a foraging vessel heading to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" to take a cargo of cannonballs and provisions for the troops.";
			link.l1 = "You're pulling the wool over my eyes. Your holds must be full of silver. And I am going to check them, after we have finished this conversation...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "I don't know who told you about the silver. But this is absolute nonsense... I lost to you, so I am giving up. Here is my sword. Now you can go and check the holds. They are empty.";
			link.l1 = "Giving up? No! I don't need any witnesses. Take your sword and fight, or I'll gut you like a sheep.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Good for you that you've shown reason. I think I'll be able to get a ransom for you... Hey, guys - throw the captain into the hold!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "You killed him, you rascal! Scoundrel! Poor "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "What's this? Where did you come from, dear?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "You will burn in hell for all you've done. Damn you!";
			link.l1 = "Calm down, young lady! Don't push your luck by cursing me – or I'll send you after your captain!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "You ... you wouldn't dare raise your hand against a woman!";
			link.l1 = "I won't even need to. I can shoot you. Or I'll just throw you overboard, and the sharks will do the rest... Now, what are you waiting for? Go to my ship. Don't be afraid - I won't let anyone hurt you, and I won't touch you myself if you stay quiet...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "What... what are you going to do to him?";
			link.l1 = "What's this? Where did you come from, dear?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Poor "+pchar.questTemp.FalseTrace.CapName+"! Tell me - are you going to kill him? Don't...";
			link.l1 = "Listen now, lady - if I wanted to kill him, I would have done it already. He'll be staying in the hold, and then I'll either let him go or ransom him... the latter is more likely. And now, please be a good girl and come aboard my ship. Don't be afraid - I won't let anyone hurt you, and I won't touch you myself if you keep quiet...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "What do you want from me? Throw me to the sharks, as you said you would? You ruined my life and I...";
				link.l1 = "Come on, dear. Nobody is going to throw you anywhere. I just want to clarify the situation, since I attacked this fluyt because of you and not for any other reason.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "What do you want from me? Where is "+pchar.questTemp.FalseTrace.CapName+"? Ransom? Do you need a ransom?";
				link.l1 = "Alright, lady, let's put an end to this stream of pointless questions. I didn't call you here for that. One fact has been clarified, and I think you'll find it interesting.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "Because of me? Are you saying it's my fault that you attacked our ship and killed my beloved? Poor "+pchar.questTemp.FalseTrace.CapName+", what did he do to you? You will answer to the Lord for all you've done...";
			link.l1 = "The same old stew! Shall we return to our shark talk?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Quiet now? Great. Now listen to me! I attacked the ship because I had information that she was carrying a decent load of silver. And I got this information from Adam Rayner.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ah! What?! Adam? Where is he? Is he here?";
			link.l1 = "I see you know the name... Katerine. And, as you can see, I already know everything about you. I take it Adam Rayner is your husband, isn't he?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Yes. I am this monster's wife. I was under the illusion that this nightmare was finally over... Did he hire you to catch me?";
			link.l1 = "Generally, that's how it turned out. Adam lied to me about the silver, so that I would capture the fluyt '"+pchar.questTemp.FalseTrace.ShipName+"'. Definitely, he was determined to bring you back. A quarter of an hour ago he explained to me all his actions.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "And... what does he want? What did he tell you?";
			link.l1 = "He wants his lawful wife to return to him. He will provide me with information about Squint-eyed Solly's gold as compensation for deceiving me. And I am going to take you both to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "No... (crying) I do not want to go back to that rascal! I made a huge effort to run away from him and cover my tracks, but he has found me anyway... Scoundrel! Bandit! Bloody thief!";
			link.l1 = "Calm down, Katerine... Watch your language. He is your husband, after all. And he said he loves you.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(weepingly) My husband? Do you know who my husband is? He is an ex-prisoner, a convict, and now the most cruel bandit of "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"! He is a low, filthy beast, and to him I am nothing but a hole between my legs to fuck!";
			link.l1 = "Hadn't you seen it all before you married him?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "At first, he was different... And his past seemed so romantic to me... But eventually, everything changed. And I don't even want to see him, let alone live with him, can't you understand that? I don't want to! Especially after this attack on the fluyt, which he arranged!";
			link.l1 = "Hm... What should I do with you, then, sweet lady?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "What to do? I know what to do. You are a tool of sin, thanks to my husband's deeds. You have killed an innocent man, the only man who ever treated me well. Atone for your sins, captain. Slay Adam. Right in front of my eyes. I want to see this scum die, I want to spit on his corpse\nWhen he is dead, I will tell you where he hides his treasures. The drunken idiot told me about his stash once, ha-ha, he doesn't even remember it!";
				link.l1 = "Heh! You are a cruel woman, Katherine, as I can see!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... The fluyt's captain. You locked him up. Talk to him, I beg you! He will offer you something for our lives and freedom! He will come up with an idea! I... I don't want to go back to Adam, from now on "+pchar.questTemp.FalseTrace.CapName+" is my husband! I beg you – don't take me back to Adam, to that monster!";
				link.l1 = "Hm. Interesting. And what could my prisoner possibly offer me? I can get a ransom for him from the authorities, and I will get Squint-eyed Solly's gold as well...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Look who's talking about cruelty. Sail to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", do what Adam told you, just land not at the port but at the nearest bay. Three of us will go there and you will kill the bastard\nOnce it's done, I will tell you about the stash. I swear, I'm not lying. I believe you trust my word more than Adam's—he fooled you once, didn't he? What do you say, captain?";
			link.l1 = "Yeah... They say for a reason that husband and wife are indeed of the same breed. I look at you, Katerine, and I see that you are the best match for Adam... If you want him dead so much, you might as well stab him in his drunken sleep... Bosun! Take her away!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "I hate rascals who try to cheat me and use me for their own purposes. Alright, Katherine, I agree to your offer, since it is clear to me that Adam cannot be trusted. But if you deceive me too, I swear I will find you even in Europe, and I will put a bullet through your head. Now get lost. Bosun! Take her away!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "You will regret this... I swear, I ...";
			link.l1 = "Boatswain! Guard her and keep an eye on her at all times until we arrive at "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "What fact? What are you going to do with us? Why have you captured our ship?";
			link.l1 = "Will you let me speak a word or should I order my boatswain to shut you up with a gag?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "Solly's gold? Do you really trust this scoundrel? He'll fool you again, that's just his way! Talk to your prisoner!\n"+pchar.questTemp.FalseTrace.CapName+" is a true gentleman, he will not break his word and he will not lie to you!";
			link.l1 = "You did not persuade me, lady. I have nothing to discuss with your captain. I will get a ransom for him, and I'll get Solly's gold from Adam. If Adam deceives me again, I will find him even at the ends of the earth, and he will curse the day he was born... Bosun! Take her away!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "To tell you the truth, I do not trust Adam... I hate being manipulated. Alright, I will talk to your captain and see what he can tell me. You can go now... Bosun! Take her away!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "You are a cruel and heartless man! I swear I...";
			link.l1 = "Boatswain! Guard her and keep an eye on her the entire time until we arrive at "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "It's over now... Poor "+pchar.questTemp.FalseTrace.CapName+" is avenged, and I can now breathe freely and call myself a widow...";
			link.l1 = "I have fulfilled my part of the deal, Katerine. Now it is your turn.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Of course, captain. My husband—thank God, now ex-husband—was a bandit, as you already know. Fearing possible searches, he did not keep pillaged loot at home. He organised a cache—but he once let slip about it. Still, he hid it in a very clever way—there is no access to that place from the shore.";
			link.l1 = "Very interesting... And where is it?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "On a small island near Hispaniola. In the lighthouse.";
			link.l1 = "Port-au-Prince lighthouse! It's located on the island!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Probably so. You'll be able to find the loot there. You'll see. That's all. Goodbye, Captain.";
			link.l1 = "Wait... Forgive me, Katerine, if you can. I hope that the death of the one responsible for all your misfortunes will bring you some relief, at least. I am truly sorry...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "I don't need your regrets, Captain. You did what I asked you to do - and I told you everything you wanted to know. Farewell now, and leave me alone with my grief...";
			link.l1 = "Bye, Katherine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Filthy scoundrel! He managed to kill all four! Unbelievable!";
			link.l1 = "Didn't expect such a turn, Katerine? I'm hard to kill. You play double games rather well, I must say!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "You have murdered my man. Do you really think I would let you keep breathing?! Did you think Adam's death would satisfy me? No! You won't leave this place. There is a ship not far from this island, she will sink your old tub along with you!\nNow, do what you want with me.";
			link.l1 = "Didn't I tell you, dear, that you'd lose your head if you deceived me? A crafty devil! You'll be far less dangerous dead. This pretty head is getting a bullet right now...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "I feel sorry for you, Katerine. Your craving for revenge did you no good in the end. I am going to leave you to your fate - you will stay on this island. I think the local fishermen will find you soon and take you to Hispaniola. And may the Lord judge us for all our deeds...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "It is you who should pray, monster! Murderer! Help! Fuck y...";
			link.l1 = "I have heard enough.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "May you drown! May your ship be dashed against the rocks! May you...";
			link.l1 = "Bye, Katherine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "A-ah, here is Adam's murderer! Katherine was right, this bastard came to rob the stash!";
			link.l1 = "What? Katherine? Who are you?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Who are we? We are friends of Adam Rayner, who was murdered by you. He was the head of our brotherhood. Now I am the head, my name is "+GetFullName(npchar)+", and I will punish you for killing my boss and for the violence you committed against his wife.";
			link.l1 = "Violence? What the hell are you talking about?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "You stabbed Adam in the back, you filthy traitor. You forced his wife to tell you where Adam kept his gold, and then you left the poor woman to die on a deserted shore.\nBut she survived. She asked us to help her, to right a wrong. We've been waiting several days for you. And here you are, you bastard!";
			link.l1 = "Ha-ha! Definitely Katerine's style... Now listen, I did kill Adam, that's true, but I did it because his wife actually asked me to kill him. It was revenge for the death of her lover. She told me where to find the stash as payment...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Don't slander the poor widow, scum! Why would she come to us then? She offered to let us take all the gold for ourselves in exchange for your life. She doesn't want coins, she wants your death! A righteous death for the death of her husband!\nBut I swear, she won't die in poverty, this is as true as my name's "+GetFullName(npchar)+", and that this is the time for you to die, coward!";
			link.l1 = "Holy hell, what a glorious speech. Oh, there she is, eager to watch this comedy in person... Gentlemen?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "You are such a muddler, captain! To lose a fluyt filled with silver... I made a mistake by counting on you. Farewell!";
			link.l1 = "Farewell, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "I warned you, captain, we only had two weeks! By now, Squint-eyed Solly must have already taken all the booty. It's not my fault you're such a muddler. Farewell!";
			link.l1 = "Yeah, my fault. Farewell, I hope we won't meet again, you're just bad luck for me.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Heh! Finally! We're tired of waiting, and these damn mosquitoes... Wait... Where's Solly? I don't get it...";
			link.l1 = "Solly won't come here. I act on his behalf... So either you give me the gold or you're as good as dead.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Argh! We'll see! To me, lads! To arms!";
			link.l1 = "Such a foolish way to die, come then, scavengers!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "You have fulfilled your part of the bargain, captain. Thank you for trusting me. Don't worry about Adam, I will deliver him to the right place. He will get what he deserves.";
			link.l1 = "I don't care about Adam. What about your promise concerning some ship?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Yes, yes, sure. Let's see, counting from today... Yes... In 12-14 days from "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" a heavy galleon loaded with gold ore will set sail for Europe. She will be protected by a single frigate or corvette\nSo prepare yourself, it is a rich prize, but it has teeth. Still, I am sure you will succeed, you did crush my resistance rather easily... You must reach "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" in two weeks and prepare an ambush\nRemember that your target is a heavy galleon with a single convoy ship. That's it, I suppose. The rest is in your hands.";
			link.l1 = "I see... Well, "+pchar.questTemp.FalseTrace.CapName+", farewell. Perhaps I should wish you luck and a happy life with Katerine? I hope that you two will be all right. It's a pity that we have met under such sad circumstances.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Thank you, captain. As I've said before, you have a certain nobility. I hope you will come to realise that honest actions bring more profit than dishonourable ones. Devote yourself to serving your nation, and you will become a great naval officer.";
			link.l1 = "I will think about your words. Well, farewell for now!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
