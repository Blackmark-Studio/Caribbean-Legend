// диалоги прочих НПС
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
			dialog.text = "A bug. Tell the devs.";
			link.l1 = "I will!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "What a stroke of luck! Captain, I happen to need an escort to Philipsburg very urgently...";
			link.l1 = "Are you Balthazar Ridderbock?";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "What the hell, I'm already more famous than the viceroy! Who are you? What do you want?";
			link.l1 = "I am Captain "+GetFullName(pchar)+". I was sent to you by Lucas Rodenburg. I am authorised to take you and your ship under my protection.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "Oh, mynheer Rodenburg must have heard my pleas for help! You see, there is a privateer...";
			link.l1 = "Let's skip the details of your story, I already know them.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "Of course! I've lost too much time already... I must reach Philipsburg within two weeks at the latest.";
			link.l1 = "Then go to your ship and prepare for sailing. We are setting sail right away!";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "Thank you for your help, Captain! Your protection could not have come at a better time. Please accept my gratitude and these 5,000 pesos.";
			link.l1 = "Hmm... This is not a very generous reward for saving a life...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "Besides, I will send a letter to mynheer Rodenburg when I have a chance – with the highest possible appraisal for your actions. I have to go now.";
			link.l1 = "Well, farewell then, Balthazar.";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "Señor! Wait... it looks like you've dropped something...";
			link.l1 = "What? Ah?!";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("You were knocked unconscious from behind", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "Sorry, my friend – I had to hit you lightly so you wouldn't cause any trouble. I realise your head is probably aching, but whatever, you'll survive. If there's time for that...";
			link.l1 = "Who are you, damn it, and what's going on here?";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "Easy, easy, my friend - otherwise I'll have to calm you down once again. We don't want those martinets bursting in, clanking their rusty swords, do we? We need to talk quietly.";
			link.l1 = "Give me back my sword, bastard, and we will have a nice talk, I swear!";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "You are a quick little man, aren't you? No need to use steel for now. Tell me what I want to know and, perhaps, you will leave this place in one piece. Am I clear? So let's chat a little.\nKeeping silent? Good, we have a deal then. What did you carry from Rodenburg to the banker?";
			link.l1 = "A letter.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "Clever. I know it wasn't a bouquet of daisies. What was in that letter, boy?";
			link.l1 = "How should I know? I don't make a habit of reading correspondence entrusted to me. Maybe it was a love letter. You know what they say about people in power...";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "...An honest captain is quite a rare thing to see in these miserable times. Well, that's bad news for you. What did this goddamn banker say when he received the package? What kind of business does he have with the Dutch?";
			link.l1 = "They're dealing in smuggled perfume from France... or Bavarian cow dung, I think.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "The question was about compensation for something. That is all I know.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "You are a brave fellow... And with a sense of humour, too. It would be a pity to kill you. Gaston would have liked you. Although... stay here for the time being. I should go and check something, and Miguel will be looking after you while I am away.";
			link.l1 = "I swear, 'my friend' – you will regret this! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "There goes the arrogance... When things are looking grim, our brave captain shows some reason. You could have done it much sooner and saved us time and trouble. Well, I have to go and check something, but then I'll come back and we'll talk, if there's still a need, that is. Stay here for the time being. Miguel will be looking after you while I'm away.";
			link.l1 = "I swear, 'my friend' – you will regret this! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "But of course. Keep quiet, 'hero' - perhaps all will yet be well.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "Stay here and hope that your flexibility proves worthwhile.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "What the hell?!";
			link.l1 = "Prepare to die, you rascal!";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "What a mess! I've been wondering what all this noise was about. My congratulations - you are a clever fellow!";
			link.l1 = "Smarter than you think... Let's see now what you can do against an armed adversary!";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "Mynheer Lucas Rodenburg wants to see you right away. Go to him at once.";
			link.l1 = "On my way.";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "What do you want from me?";
			link.l1 = "Your head!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Nothing, never mind.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "It's you again? What do you want from me?! Explain yourself!";
			link.l1 = "Your head!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Nothing, never mind.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "It's you again? Why are you snooping around here? I don't like it at all. Alright, I'll arrest you and send you to the commandant's office for questioning. Boys, seize this one!";
			link.l1 = "But I just wanted to...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "Who are you and what do you want? Explain yourself!";
			link.l1 = "I am sorry, sir, it seems I've come to the wrong house. I beg your pardon.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "I'd like to see Richard Fleetwood.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "That's right. You're talking to the wrong man. Be so kind as to leave at once!";
			link.l1 = "Yes. Sure.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "Really? Who told you he lived here? That sounds suspicious... Alright, I'll arrest you and send you to the commandant's office for questioning. Boys, seize this man!";
			link.l1 = "But I just wanted to see Richard...";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "Ah! Thieves? Spies? Hold on to your hat now!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "Ah! What is this guy doing here? Boys, we've got ourselves a spy here! To arms!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "Captain, we've questioned this scoundrel, as you instructed. We had to cauterize him a bit... He had this letter on him. Tried to eat it, but we didn't let him. Just as we thought, he was supposed to take some girl in Willemstad and bring her to his boss.";
			link.l1 = "A letter? Let's have a look at it. Then I will speak to him myself.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "What are your orders, Captain?";
			link.l1 = "Throw the corpse overboard. And prepare to go ashore!";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "Bury him at sea with full military honours. That old man fought bravely to the very last. He even loaded and aimed that cannon after it had been knocked from its carriage. A true pity. In another world we might have been comrades...";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "Aye, Captain!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			dialog.text = "Aye-aye, Captain!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "We have prepared the Chinese man for questioning, just as you ordered, Captain. He had nothing on him, no papers. A brazier has been set up, and we are heating the handcuffs and tongs until they are red-hot.";
			link.l1 = "Good work, Alonso. But before you start, I'd like to try to reason with him. Perhaps he'll decide to cooperate willingly?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "As you say, Captain.";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "Yes, Captain?";
			link.l1 = "Put him in manacles and keep your eye on him at all times until we reach Guadeloupe. You three must always be here. You will answer for him with your lives.";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "Aye-aye, Captain!";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "H-ic! Good evening, sir! What would you like? Perhaps you could buy an old drunk a drink? And I'd...";
			link.l1 = "Listen here, old drunkard... Are you Jack Harrison?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "Oh! Yes, that's me. Who else could it be? Why? Wh-a-t sha-a-ll we do-o with a-a dru-un-ken sai-lo-o-r...";
			link.l1 = "Oh my Lord, give me patience! What sailor? It's written all over your face that you're a landlubber... Do you want to make some money?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "I always want to make money. What should I do? But I won't kill anyone. Nor will I steal anything. And you are not my type.";
			link.l1 = "You won't have to kill anybody, and I doubt you are actually able to do that. You are too ham-handed. Now. Here is a letter. Take it and deliver it to the house to the left of the governor's residence. It is meant for Richard Fleetwood.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "For Richard Fleetwood? No... I'll be arrested on sight.";
			link.l1 = "Shut up and listen. Nobody is going to arrest you. You'll say that you've come from Charlie Knippel regarding Abigail. You will be let in. Repeat what I've said.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "Who is Abigail? I know Knippel...";
			link.l1 = "None of your business. The less you know, the longer you'll live. Well, I am waiting. Repeat.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "I've come from Charlie Knippel regarding your... Abigail. That's it. ";
			link.l1 = "Well done. You'll get 5,000 pesos for the job.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "5000 pesos? Oh... Only for delivering a letter?";
				link.l1 = "No. You'll be given another letter. Bring it to the tavern and take a seat here. I'll take it from you. Don't do anything foolish, and don't be afraid – I'll be watching you and staying close. Take this sum as an advance, so you can feel at ease.";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "Five thousand? Do you even have that much money?";
				link.l1 = "Ha! Of course I have. I'll bring it now.";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "Have you brought the five thousand?";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "Yes. Here you are. Don't worry.";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "No. Wait. I will be back soon.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "Hmm... Should I go now, sir?";
			link.l1 = "No, on Thursday morning... Of course, right now, you bonehead! Now finish your rum and go!";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//удалить время загрузки
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, here you are, sir... I wish I hadn't done this. Richard became enraged when he finished reading. I thought he would kill me.";
			link.l1 = "But here you are! Don't worry - he wouldn't dare do that - you were far too valuable to him at that moment, ha-ha! You can't even imagine just how much...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "I need a drink... Here's his reply to you.";
			link.l1 = "Give it to me! And keep your mouth shut!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "It will be difficult for me to speak in the next couple of days... Goodbye... I hope I never see you again.";
			link.l1 = "Take it easy, old drunkard, ha-ha-ha! Wh-a-t shall we-e do-o with a dru-un-ken sai-lor... Drink and relax - it's all over now!";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "Why the hell did you attack my ship? I have neither valuables nor money—just papers, which are of no use to you anyway!";
			link.l1 = "Shut up. You've lost, so now you will listen to me. I need neither your ship nor your papers. I need you to give this message to your boss, that dirty rat Lucas Rodenburg. Tell him that Captain Fleetwood sends his regards.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "Captain Fleetwood? But...";
			link.l1 = "Will you give this letter to your boss – or should I run you through? I can look for a different candidate for delivery too. I rob ships of your filthy Company every weekend out of sheer boredom, just so you know.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "Alright, Sir Fleetwood. I'll deliver it.";
			link.l1 = "That's great. Now we can say goodbye to each other, Mynheer. You can consider yourself very lucky today. And don't forget to visit a church upon arrival!";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("THE LETTER HAS BEEN DELIVERED!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "I was arrested illegally! I have no connection with the English! Those are all Rodenburg's intrigues. Never mind. Peter Stuyvesant will arrive soon - he will sort it all out!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "Mynheer Lucas Rodenburg does not wish to see anyone at this time. Please be so kind as to leave the residence at once.";
			link.l1 = "Hm. I see. I'll try to drop by in a week...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "We are going to the residence, Captain. I've already sent my people to the fort to get information about Matthias Beck. If he is actually in prison at the moment, he must have already been released and brought to the town. Follow me!";
			link.l1 = "Yes, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "Lucas! What is going on here? Where is Matthias Beck? Is it true that you've sent him to prison?";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "Hello, Mynheer Stuyvesant. I've got proof of his connection to British intelligence and directly to Captain Fleetwood. He tipped off the damned Brit to attack our courier brigantine and seize the Company's confidential correspondence.";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "Where did you get this information?";
			link.l1 = "";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "It was claimed by the captain of the courier brigantine. Richard Fleetwood boarded his ship and took away his papers; then the ship was set free. Nobody except me, you and Matthias Beck had any information about either the route or the schedule.";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "And that's why you have decided that Beck tipped off Fleetwood to attack the brigantine? What rubbish! Fleetwood is an ordinary pirate; he only attacks merchant ships. Why would he need the papers, which, by the way, only contained bookkeeping information?";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "Mynheer, the courier also transported other important Company documents - not just the usual reports. And now they are all in the hands of the British. That is why I decided to put Beck under arrest.";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "Damn it! This is a real usurpation of power! Have you actually realised what you have been doing, Lucas? Where is the captain of the courier brigantine?";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "He's gone to Philipsburg, Mynheer.";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "Fine, then. I've ordered Beck to be released. He'll be brought here and then the three of us will have a talk.";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "Alright, I don't mind. Three of us - fine. Let's talk.";
			link.l1 = "";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "You will pay for your lawlessness, Rodenburg! Your accusations are absurd. You didn't even let me see the captain of the brigantine! You haven't presented any evidence; all the accusations come from you personally.\nI swear to the Lord, I am innocent! I do not and did not have any contact with the Brits!";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "Oh, really? Then how did Fleetwood find out about our brigantine and that she had more than just the usual documents on board?";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "...";
			link.l1 = "Rodenburg is lying. Richard Fleetwood could not have attacked the courier brigantine.";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "And just who are you, Mynheer? On what grounds are you making such statements?";
			link.l1 = "My name is "+GetFullName(pchar)+". I personally eliminated Captain Fleetwood by luring him into a trap. His corpse is being eaten by seagulls on the shores of Turks. Officials failed to protect us, Dutch traders, from his aggression, so I finished him off myself. And it happened before the courier brigantine was plundered...";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "Fleetwood simply could not have done it, he was already dead. I have learnt from locals in the tavern that Mathias Beck was arrested, so I decided to investigate the matter, because I have always believed that mynheer Beck is a man of spotless reputation...";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "People in the port told me that you loaded your xebec with all kinds of criminals and mercenaries, while the Company's guardsmen were left ashore. I followed your ship and captured her, slaying every cutthroat you hired. I interrogated Captain Longway; in exchange for his freedom, he told me everything, Mynheer Rodenburg...";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "You were planning to seize power over Curacao and ordered Longway to sink mynheer Stuyvesant's galleon. Knowing your methods, I am sure that the poor captain of the brigantine is dead. You must have organised an attack on the courier vessel to create a precedent, am I right? And this act was carried out by your assassin, Jacob van Berg? Longway told me a lot about that man.";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "This ... this is a blatant lie! What are you talking about, Mynheer? Who the hell are you?";
			link.l1 = "I am an independent captain who wanted to rid the sea and land of that scoundrel Fleetwood and who became entangled in your political intrigues! I warned mynheer Stuyvesant about the danger he was in. And I am here to put an end to your depredations on Curacao - together with the legal authorities!";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "What insolence! You will answer for your words, Mynheer 'independent captain'! You...";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "Enough, Lucas. You will pay for your crimes! I have heard and seen enough. Lucas Rodenburg, I am arresting you for attempting to take the life of the Company's director, for attempting to seize power by force, and on suspicion of murdering the captain of the courier vessel.\nBesides, I am sure we will learn more about the interesting parts of your biography during the official investigation. You will be held in custody and delivered to Amsterdam, where you will be prosecuted. Take him away!";
			link.l1 = "";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "But...";
			link.l1 = "";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Captain "+GetFullName(pchar)+"! On behalf of the colony administration of Willemstad, I kindly ask you to accept our sincere gratitude for your actions, which helped us put that dangerous criminal under arrest. I would also like to thank you personally, as I am likely indebted to you for my life.";
			link.l1 = "I acted for the good of all the Dutch colonies, Mijnheer.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "Your modesty commands respect, my friend. Now I would like to settle some formalities: since you captured the Meifeng only for good purposes and in dire straits, there can be no claims. But this ship belongs to the Company and I kindly ask you to return her.";
			link.l1 = "Certainly, Mynheer.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "Please come to my residence tomorrow – you will be honoured on behalf of the Republic of Free Provinces for your deeds in its best interest. I kindly ask you not to leave town.";
			link.l1 = "Alright, Mynheer. I'll come by tomorrow.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "I would also like to thank you personally, Captain, for your spirit of enterprise and timely assistance. Don't forget to come here tomorrow, I will prepare a valuable gift for you.";
			link.l1 = "Thank you, Mynheer Beck. I will be there!";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = ""+GetFullName(pchar)+", on behalf of the Republic of the Free Provinces, you are hereby awarded a personal weapon and a sum of 100,000 pesos for your initiative in the elimination of the enemy of all Dutch people, the state criminal Richard Fleetwood. Congratulations!";
			link.l1 = "Thank you, Mynheer Stuyvesant!";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "Also, for your unprecedented courage, for uncovering a treacherous conspiracy within the Company, and for the daring capture of the former vice-president of the Company, you are being awarded 150,000 pesos. You will also be permitted to sign contracts with the Dutch West India Company\nI am sure that our new vice-director will find a well-paid position for such a brave captain as yourself.";
			link.l1 = "Thank you! I will keep that in mind.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Be aware that you can always count on my assistance in any dealings as long as you act on the side and in the interest of Holland. Now let's hear what the governor of Willemstad, Matthias Beck, has to say.";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "I express my sincere gratitude, Captain, for your courage and insight in uncovering a plot against the state. I would like to present you with this valuable navigational instrument, which is indispensable for any man-of-war's man.";
			link.l1 = "Thank you, Mynheer Beck";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "I would like you to know: you are my friend now, and this means a lot. You will always be a welcome guest in my residence. Come by at any time and for any reason - I will be happy to provide you with any help you might need.";
			link.l1 = "I am glad to hear that, Mynheer!";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "Holland is proud of you, Mynheer. Captains like you are the backbone of the Dutch Fleet in the Caribbean. Here you are, please accept your reward.";
			link.l1 = "Thank you, Mynheer. I am honoured to serve Holland!";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "I am glad to see you. How are you?";
			link.l1 = "I am fine. I just dropped by to see you.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Look who it is! It's "+GetFullName(pchar)+". We recently sent our headhunters to bring you here. And that service did cost a lot.";
				link.l1 = "Uhm... I should go...";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "Are you a captain in the French Navy? Good, I'm short on time, but I will listen to what you have to say. What brings you here?";
				link.l1 = "Mynheer Stuyvesant, I've come from Saint Christopher with a message from the Governor General of the French colonies, Chevalier de Poincy.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "Excuse me, Captain, but I'm extremely busy right now and can't spare enough time for you. Speak to mynheer Mathias Beck, let him hear what you have to say.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "From Chevalier de Poincy? I definitely didn't expect it would take so little... ahem... how is the Chevalier doing?";
			link.l1 = "Everything is fine, Mynheer. Monsieur de Poincy ordered me to deliver this letter to you. My other task was to escort "+sld.ship.name+"' with cargo for your company to Willemstad's port. The vessel is at the dock and the cargo is undamaged.";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "A fleet with cargo for our company? Intriguing... And the letter, Captain?";
			link.l1 = "Here. Please, take it.";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Hmmm... (reading). An inspection from the parent state... Ahem... Huh, well... that's interesting, heh-heh... By the way, Captain, I've heard that France is at war with Spain in the Caribbean? The siege and sacking of San Jose fort, the destruction of the Spanish war squadron off the eastern coast of Cuba...";
			link.l1 = "Off the western coast of Hispaniola by Port-au-Prince, Mynheer. And the only goal for the siege of San Jose was to get financial compensation from the Spaniards for their attack on Saint-Pierre. We have been on bad terms with Spain for quite some time... When should I return to collect the answer?";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "I won't hold you, Captain, you're a military man, you probably have a lot of affairs and I'm sure Chevalier is eagerly waiting for your return. Be so kind as to wait right here, in the living room, for two hours while I compose an answer to that letter. Take a seat and rest here, you will be served wine or rum, if you wish...";
			link.l1 = "My gratitude, Mynheer, but I'd prefer a glass of fine wine...";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "The answer for Monsieur de Poincy is ready. Here, please, take it... Good luck, Captain.";
			link.l1 = "Thank you, Mynheer. Farewell!";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Look who it is! It's "+GetFullName(pchar)+". We recently sent our headhunters to bring you here. And that service did cost a lot.";
				link.l1 = "Uhm... I should go...";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "You've come again with a message from Governor General Philippe de Poincy, haven't you?";
				link.l1 = "Yes, Mynheer Stuyvesant. On the banks of Sint Maarten there was an unfortunate misunderstanding - a ship carrying the inspector from Paris, Baron Noël Forget, was fired upon by the fort at Philipsburg, and...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "Excuse me, Captain, but I'm extremely busy right now and can't spare enough time for you. Speak to mynheer Mathias Beck, let him hear what you have to say.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "And that's why you're here, Captain. I will not engage in diplomatic discussions: tell the Chevalier that he is no longer in charge of Sint Maarten. Enough of him. And regarding the inspection from the parent state – let him come up with something. It was never difficult for de Poincy to turn everything upside down.";
				link.l1 = "Is that exactly what I should tell him?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "And that's why you're here, Captain. I will not go into diplomatic discussions: your liege has been far too greedy on Sint Maarten as of late, so it's time to temper his insatiable hunger. And I believe he understands that perfectly well. As for you, Captain Charles de Maure, we also have questions about recent events involving the British bandit by the name of Richard Fleetwood, so you will have to stay here for a while.\nSergeant! Take the captain's weapons and bring him to the commandant's office!";
				link.l1 = "Delaying a French officer on duty is unacceptable!";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "Couldn't have put it better myself, Captain. Your commander will understand everything, but you don't need to delve into it, that won't change anything. Wish you all the best. Sergeant, lead Monsieur Charles de Maure to the exit!";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "Unfortunately, I have a different opinion. Sergeant! If they resist, use force!";
			link.l1 = "You just don't know who you're dealing with yet, Mynheer ...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "It's a little strange to see you, Captain Charles de Maure, in this role ... I hope you can guarantee immunity to those who come to you for negotiations..";
			link.l1 = "You can be sure of it, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "So, could you give me a chance to read the agreement you've prepared? As I understand, it contains content from the letter?";
			link.l1 = "Precisely, Mynheer, only in an official form. From France's side – restoration of relations to neutral, rejection of any claim to the island of Sint Maarten. From England's side – the end of the trade war. The details are all described in here ... And, of course, financial compensation for the damage that we suffered because of the military actions you initiated.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "Please be so kind as to give me the document.";
			link.l1 = "Of course.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(reading)...";
			link.l1 = "...";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "Since you didn't leave me a choice, I'll sign this agreement. But for me, the protection of Willemstad and its inhabitants is of the highest importance";
			link.l1 = "Then we will validate all three copies with signatures. I am authorised by Governor General Philippe de Poincy to endorse the document for France's side, Colonel Doily will sign it for England.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(signing)...";
			link.l1 = "Perfect! Now we should sign this...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "So, I trust you'll call off the siege now?";
			link.l1 = "Without a doubt. I hope that all the terms of the agreement will be honoured by the Dutch side without violations.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "If there are no violations by England or France, then we will abide by the terms of the contract, so do not worry.";
			link.l1 = "It's always better to trade than to fight, Mynheer Stuyvesant. And now you can safely return to Willemstad. The siege will be lifted and our squadron will soon leave the waters of Curaçao.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "So, are you Baron Noel Forget? Huh, and you must be Monsieur Charles de Maure himself! Greetings, Vice Admiral! There is a reason why you are known as the most cunning schemer in the archipelago - one can never tell whose side you are on at any given moment...";
			link.l1 = "The Vice Admiral is on the King's side, and yours sincerely, as his entitled representative, at the moment.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "The King is far from here, and so is France, Baron, but Saint Christopher and Chevalier de Poincy are close. He is the true owner of the French colonies. De facto ... However, are you here to get anything that would compromise de Poincy in the eyes of the finance minister?";
			link.l1 = "Precisely, Mynheer.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "I have such documents. This is an entire ledger with my accounts and de Poincy's for the mine and some other matters. Inside, you'll also find a whole heap of papers related to this business, each bearing the personal signature of Philippe de Poincy. I assure you, the contents of these papers, in the hands of someone interested, will sink the Chevalier deeper than the bottom of the Caribbean Sea.";
			link.l1 = "What do you want for this ledger?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "I'm selling it for a song. Merely a million pesos in silver.";
			link.l1 = "A million pesos?!!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "That's right, Baron. This amount will at least partially cover the losses caused by the recent war. I will give you a piece of advice: turn to Monsieur Charles de Maure. During his service for de Poincy and ahem... other people, he probably made a huge fortune, and getting a million won't be a problem for him. I'm almost certain of it.\nI will give you a deadline - one month. After this time, if you do not bring the indicated amount, I will send a letter to the Chevalier, in which I will describe the details of your visit to me. You can guess what happens next.";
			link.l1 = "You're blackmailing me! You must understand that I couldn't possibly have a million in the colonies!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "Of course I understand. Therefore, I immediately pointed out to you the person who has this million. If Monsieur de Maure refuses, it's best for you, Baron, to sail away to Europe before the Chevalier receives my letter, otherwise you risk staying here forever. As for Monsieur de Maure... of course, he will lose his admiral's rank, but he'll get out... and maybe even get rid of de Poincy with his methods, which is perfectly fine with me.\nWell, gentlemen, you heard me. I will be waiting for you with the million in a month's time at my residence. Free entrance and exit guaranteed.";
			link.l1 = "...";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "I never doubted, Vice Admiral Charles de Maure, that you would bring me this money. Perhaps I even asked too little of you, but oh well... The Baron is just a pawn in your next game, isn't he? Rank and money are not enough for you; now you want to take de Poincy's place, am I right? You must admit, a million is a small sum for the post of Governor General of the French colonies! You'll get this money back in a matter of months, given your iron grip.";
				link.l1 = "Take your million, Mynheer. I'd like to receive my promised ledger.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "You'd better focus on collecting the million, Monsieur, instead of wasting your time on pointless visits.";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "Of course, Vice Admiral. And don't frown: when you become Governor General, you'll see that the Dutch West Indies Trading Company is a more profitable business partner than the greedy and warmongering British. Don't you know that if you give a Brit a finger, he'll take the whole hand? If not, you'll learn that the hard way. So I'm not saying goodbye to you yet. Keep your papers. I hope your baron is competent enough to defeat the Chevalier.";
			link.l1 = "My thanks. Farewell, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "Ha-ha-ha! Look at that! Jacob was right, as always - this fox came to the island for a good reason. It seems there's quite a pile of gold in the chest. Very careless of you to come here alone, fellow. But then again, it makes our job that much easier!";
			link.l1 = "Those scumbags have tracked me down! I didn't see it coming... But I won't be easy prey!";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "Are you looking for someone?";
			link.l1 = "Yes, I am. Where are Solomon and Abigail Shneur?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "They don't live here anymore. They simply couldn't afford the place. Abigail, poor girl, is working as one of the governor's servants. She works hard every day to provide for herself and her father. Solomon drinks in the tavern every day; he can't bear what happened to them. They are now living in a small hut not far from the sea...";
			link.l1 = "Oh... Alright, thank you for the information. I have to go.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "What else would you like to know, Mynheer?";
			link.l1 = "Nothing, never mind.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "Captain, you have misappropriated a ship belonging to the Dutch West India Company. I am authorised to confiscate it and use force should you resist. This is an order from Peter Stuyvesant.";
			link.l1 = "Well, if it is an order from Peter Stuyvesant himself... I will not go to war with Holland over a ship. Take it.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "Good of you to show reason.";
			link.l1 = "...";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "Of course it's time to leave, you'll even be escorted. Guards! Get him!";
		    link.l1 = "Make me!";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hey, listen up! As a citizen of this town, I kindly ask you not to walk around with an unsheathed blade.","You know, as a citizen of this town, I kindly ask you not to walk around with a drawn blade.");
			link.l1 = LinkRandPhrase("Fine.","Alright.","As you say...");
			link.l1.go = "exit";
		break;
	}
}
