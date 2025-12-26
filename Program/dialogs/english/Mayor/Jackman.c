// Якоб Джекман
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play the butcher? All the pirates are angry with you, boy, you'd better leave this place...","It seems you've gone mad, boy. Wanted to stretch your arms a bit? No offence, but you have no business here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation...","Help me solve this problem...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", I'd like" + GetSexPhrase(""," to") + " discuss my safety at sea. The lads from the Brotherhood of the Coast are showing way too much interest in my humble person. Could you rein them in a bit?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat("Do you have anything to tell me? No? Then get out of here!",
						"I think I made myself clear, stop annoying me.","Although I've made myself clear, you keep annoying me!",
						"Right, I am getting tired of this rudeness.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I am leaving already.",
						"Sure, "+npchar.name+"...",
						"Sorry, "+npchar.name+"...",
						"Ouch...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "Where can I find Jimmy Higgins?";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "Me again, Jackman. They say you're looking for some missing people...";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "It's about your prisoner.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Hello, Jackman. About your mission...";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "It's about your prisoner.";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Did you want to play the butcher? All the pirates are angry with you, boy, you'd better leave this place...");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation...","Help me solve this problem...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", I'd like" + GetSexPhrase(""," to") + " discuss my safety at sea. The lads from the Brotherhood of the Coast are showing way too much interest in my humble person. Could you rein them in a bit?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat("Do you have anything to tell me? No? Then get out of here!",
						"I think I made myself clear, stop annoying me.","Although I've made myself clear, you keep annoying me!",
						"Right, I am getting tired of this rudeness.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I am leaving already.",
						"Sure, "+npchar.name+"...",
						"Sorry, "+npchar.name+"...",
						"Ouch...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "It's about your prisoner.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "Really! Someone needs this lazy bum! He's been drinking rum alone in his shack for several days now. I wouldn't advise you to visit him. He's not the finest man, even when he's sober...";
			link.l1 = "It's alright, I'm not a saint either. Where is his shack?";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "It's right in front of the tavern. He picked a good spot for quick runs to get a drink.";
			link.l1 = "Thanks!";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "And who told you that? That drunkard Higgins? Have you found out anything about Gladys Chandler or Henry the Hangman?";
			link.l1 = "Nothing special, really, but I want to know something specific about that hangman.";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "There's nothing much to know. A few remember him now, but twenty years ago Henry was very popular among the whores from Bridgetown to Tortuga. You bet! A boatswain of the 'Neptune', under the command of Captain Butcher himself! He must be really old now, if he's still alive, of course.\nChances are slim, but you know, nothing is impossible. I will pay twenty thousand pesos for any information about him, double if you bring him here alive.";
			link.l1 = "How much will you pay for Gladys and her daughter?";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "Oh, she is not her daughter. If you bring that girl back alive, I'll pay you a pile of doubloons. I'm not interested in Gladys. Questions?";
			link.l1 = "I wish I knew the reason for this fuss, but I won't ask. It looks like it might shorten my biography.";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "Perhaps... Those secrets are none of your concern. The less you know, the longer you'll live. Don't ask me such questions again, because I'm starting to suspect there's something off about you. Get lost before I change my mind.";
			link.l1 = "See you, Baron!";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "To Antigua now. The corvette must be boarded.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "Ha! We meet again, Captain "+GetFullName(pchar)+". I admit, you are a worthy opponent, despite your attempts to portray yourself as a simpleton in Maroon-Town. I have found out something about you, your intrigues with the Dutch West India Company have been uncovered... I understand now what sort you are.";
			link.l1 = "I know your type too, Jacob. So let's not delude ourselves.";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "And how you tricked me with 'Marlin'! I suppose my poor brother is dead...";
			link.l1 = "I take it you want revenge for him? But I have a long bill for you as well. For the cornered Nathaniel, his wife, his frigate, the slandered Shark, Blaze Sharp...";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "Blaze? I didn't kill him.";
			link.l1 = "Even if it's true, the rest of my list is enough. I am sick of your name. Enough words, Jackman! Our blades will speak!";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "Such a vehement fool... Damn you! Now you'd better hold on! Jacob Jackman has never been defeated! Carpacho, you are just in time! Come here!";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "Ha-ha. Do you think I have only one prisoner here? Name him.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". Is he here?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "He was. I sold him to that plantation owner from Barbados – Colonel Bishop, when he was here a week ago.";
				link.l1 = "Damn...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, at last. I was thinking of selling him to that plantation owner from Barbados, he will be here in a week or two... Do you have a ransom?";
				link.l1 = "Look, there's a slight problem... Actually, I don't have that much money. But I'm willing to work.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "It's good that you haven't sold him. Here are your coins - 150,000 pesos. Where can I find him?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "You were too slow... And why do you care about him? I have only been negotiating with his relatives.";
			link.l1 = "They have asked me to come here.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Well, you're late. I can do nothing.";
			link.l1 = "Listen, how much did you sell him for, if it's not a secret?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, it's not. But I won't tell you... You'll laugh if I do. Ha-ha-ha-ha! Farewell.";
			link.l1 = "See you...";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Well, well... I've got some business... Don't even know how to start. I need to sink a pirate who crossed the line.";
				link.l1 = "Can't he simply be killed in the jungle?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Well, "+pchar.name+", you know, it doesn't work like that. Come back with the money and you'll get your weakling, ha-ha.";
				link.l1 = "Fine. See you.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "It's not how business works, you know... I don't need him dead, I just need to teach some people to stay away from taking my share of the loot. But if he ends up feeding the sharks, I won't be upset.";
			link.l1 = "Why don't you send your own people after him?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hm... Well, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" has convinced some pirates that their share of the loot is kept in our stash not far from "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Their two ships '"+pchar.GenQuest.CaptainComission.ShipName1+"' and '"+pchar.GenQuest.CaptainComission.ShipName2+"' raised anchor not long ago and sailed to "+sLoc+". Now you see why I can't trust my men to do this job?";
			link.l1 = "I do. How much time do I have?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 to 15 days, no more, I suppose. I don't want them to reach the stash, or it would be pointless to sink them with valuable cargo. In that case, it would be better if they brought it here...";
			link.l1 = "Fine, I'm in. I'll try to catch them.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Don't worry. My men will deliver him to your ship. And why do you care about him?";
			link.l1 = "I don't. His relatives asked me to deliver him.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, that's fine. I was almost sorry for offering such a low price for your man. Ha-ha-ha-ha. Farewell.";
			link.l1 = "See you.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "So, , "+GetFullName(pchar)+", did you sink my mate? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "No. I failed to catch them. And I didn't meet them on the way back.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "I did. I've sent them to feed the sharks.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Damn! Whether I met them or not, it doesn't matter now! And what will be your next suggestion?";
			link.l1 = "Maybe you've got an easier job for me?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Listen, Jackman, lower the price for the prisoner...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "No.";
			link.l1 = "Farewell then...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Bring down the price? I've just lost my stash because of your incompetence! And now I can raise the price! You can take him for 200,000 pesos if you want, or you can get the hell out of here.";
			link.l1 = "It's too expensive... Farewell...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Damn it, take your coins.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Fine, you can take this weakling...";
			link.l1 = "Farewell.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Well done! Take your weakling and good luck.";
			link.l1 = "Thank you. Farewell.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "Have you brought the money, Charles? I wasn't joking about selling the man to the plantation.";			
			link.l1 = "Listen, "+NPChar.name+", there is a problem... I don't have that much money. But I am willing to work.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "It's good that you haven't sold him. Here are your coins - 150,000 pesos. Where can I find him?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery! That is unacceptable! Prepare yourself, "+GetSexPhrase("boy","girl")+"...","Hey, what the hell are you doing there?! Thought you could rob me? You're finished...","Wait, what the hell? Take your hands off! Turns out you are a thief! End of the line, bastard...");
			link.l1 = LinkRandPhrase("Shit!","Caramba!!","Damn it!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Get away from here!","Get out of my home!");
			link.l1 = "Oops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Don't bother me with your cheap talk. Next time you won't like the result...";
        			link.l1 = "I got it.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "It's over, no talking.""I don't want to talk to you anymore so you'd better not bother me.";
			link.l1 = RandPhraseSimple("As you wish...","Fine then...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "I hope that you will show more respect and stop being rude. Otherwise, I would have to kill you. That would be most unpleasant.";
        			link.l1 = "You can be sure, Jackman, I will.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Solve the problem? Do you understand what you've done? Anyway, bring me a million pesos and I will persuade the lads to forget your 'feats'. If you don't like the idea then you may go to hell.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Fine, I am ready to pay.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Got it. I am leaving.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Good! Consider yourself clean again. But I hope you won't do such disgusting things again.";
			link.l1 = "I won't. Far too expensive for me. Farewell...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("We've already discussed this today.",
				                                      "Was I not clear enough?",
				                                      "You're starting to push your luck.",
				                                      "I've had just about enough. Get out of here!",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Maybe some other time...",
				                                   "Of course, "+npchar.name+"...",
				                                   "Sorry, "+npchar.name+"...",
				                                   "Ouch...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "Ha! Getting heat from our brotherhood, huh, " + GetSexPhrase("mate", "lass") + "? Sure, I can keep them in line for a while. But it'll cost you a fair bit. " + FindRussianDublonString(iBarbazonTotalTemp) + " on the barrel and it's a deal.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "Sure, here's your money.";
					else link.l0 = "Looks like I have no choice. Here's your money.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "I'll come back another time...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "Are you insane" + GetSexPhrase("", " girl") + "? Our guys steer clear of you like you’ve got the plague. So beat it and stop wasting my time.";
				else
					dialog.text = "What are you talking about, " + GetSexPhrase("mate", "lass") + "? You’re a real pain in the neck — even the dogs sense it. No one wants to deal with you.";
				link.l1 = "Got it...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}
