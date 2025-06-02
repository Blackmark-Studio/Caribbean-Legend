void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "What do you need?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;

		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! What brings you to my home?";
			link.l1 = "My name is Captain "+GetFullName(pchar)+". I'm here at the gypsy woman's request. She wants to know why you rejected her help. Are you really in a position to refuse any chance, however small, to heal your daughter?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_1":
			dialog.text = "Oh, Captain... Please understand, I had to refuse, but not of my own will. Believe me, I would give anything for Esther to recover.";
			link.l1 = "What could have made you reject the help you so desperately need?";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "You see, our family has always been devout. After the death of my wife, Olivia, I've been holding on by faith alone. When the gypsy offered her help, I agreed - anything to save my daughter. But... our priest found out about it.";
			link.l1 = "Let me guess: he opposes such services?";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "Exactly so. He convinced me that only prayer and the Lord's will can heal my daughter. And in case I stray from this path - by using the help of a 'witch' - he threatened me with excommunication from the church. Do you understand? Excommunication!";
			link.l1 = "So Esther's health depends solely on the priest's word?";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "My daughter and I live by the church. Faith is everything to us. If the gypsy fails, I'll lose not only my daughter but also what remains of my place in this world. People will turn away, the church will reject us. Esther and I will be completely alone.";
			link.l1 = "And if the priest gave his consent? Would you then allow the gypsy to try?";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "Yes. If the church blessed her actions... Then I would trust her. I'm ready to try anything that might help.";
			link.l1 = "I see. Very well, Thomas, I'll help you. I'll speak with your priest. Perhaps I can convince him.";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "You... you're really willing to help us? Captain, I will pray for your success. But keep in mind... our priest is stubborn and principled, convincing him won't be easy.";
			link.l1 = "Principles can be overcome with persuasive arguments. Wait for me, I'll return soon.";
			link.l1.go = "Tomas_7";
		break;

		case "Tomas_7":
			DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("DWH", "3");
			pchar.questTemp.DWH_pastor = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "Thomas, I managed to convince the priest.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "Really? Incredible! Then let us invite the gypsy as soon as possible.";
			link.l1 = "We certainly will, but there’s one detail. The priest hopes this won’t shake your faith and expects sincere repentance and good deeds. One such deed could be purchasing a new bell for the parish.";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "Oh, Captain... A bell costs a good sum. I may have to part with something from my late wife's jewelry. But for Esther, I’m ready to give everything I have—and more. Of course, I will beg the Lord for forgiveness. I’ll go to the blacksmith, place the order, and find the gypsy.\nPlease, tell the priest the bell will be ready soon. I’ll get it even from beneath the earth, if I must.";
			link.l1 = "Very well, Thomas.";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			
			LAi_SetActorType(npchar);
			pchar.questTemp.DWH_pastor_PrinesDengi = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "I've told the priest what you said. He won't stand in your way anymore, so you may begin.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "Thank you, Captain, for your involvement! Please take these fifty doubloons. It's the least I can do for you, and all I have at the moment...";
			link.l1 = "Nonsense! I didn't help you for money. So, everything is ready for... hmm... the treatment?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Well, if you insist... Is there anything else I can do?";
			link.l2.go = "Tomas_16_2";
		break;

		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "To prepare the remedy that will restore the girl's health, I need mangarosa - a rare plant that grows in places seldom touched by man. I know a cave outside the town, often crawled by... lowlifes. They burn the mangarosa for smoking, unaware of its power. Help me out, "+GetSexPhrase("falconet","dovey")+", get me some mangarosa, nothing will work without it.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "Mangarosa? I'm familiar with that plant.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "What does it look like?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "It’s a rather tall plant with split leaves and a pleasant, dizzying smell. You won’t mistake it for anything else.";
			link.l1 = "Alright, I’ll find this mangarosa.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "You mix it with your tobacco too?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "No, not at all! There's a healer named Amelia. She uses it to brew potions that could quite literally turn your mind inside out.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "No, but I’ve handled mangarosa a couple of times.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "So you know Amelia? Well, "+GetSexPhrase("falconet","dovey")+", soon you’ll be giving me some real competition. But now is not the time for that. Go fetch the mangarosa, and I’ll prepare everything.";
			link.l1 = "On my way.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "I see, you're not an ordinary one, "+GetSexPhrase("falconet","dovey")+". Your knowledge is vast, your mind sharp as a blade! You're not afraid to venture into the unknown, eager to grasp what others shy away from. Thomas is lucky to have your help. Now go, bring me the mangarosa, and I’ll heal the girl.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			
			AddQuestRecord("DWH", "5");
			
			// поход за мангаросой
			LAi_LocationDisableOfficersGen("Antigua_Grot", true);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = true;
			PChar.quest.DWH_Grot.win_condition.l1 = "location";
			PChar.quest.DWH_Grot.win_condition.l1.location = "Antigua_Grot";
			PChar.quest.DWH_Grot.function = "DWH_Grot";
		break;
		
		case "Bandit_1":
			dialog.text = "Ha-ha. I'm telling you, Mark, he's a fool. He doesn't even lock his house.";
			link.l1 = "Are you sure his hen won’t be sitting at home?";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestFunctionDelay("DWH_Grot_2", 4.0);
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Well, well, fresh fish swims into our net! Come on, don’t just stand there. Turn out your pockets, quick, before we lose our good mood.";
			link.l1 = "Easy now, bandits. I'm here on business. "+sld.name+" sent me. I need mangarosa.";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "You say "+sld.name+" sent you? Alright, we have mangarosa. Give us ten gold and it's yours.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Here you go.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "Money? What for? I don’t hand out charity. But I can hand you two pounds of steel instead!";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "Alright, here's your mangarosa. And remember, you never saw us.";
			link.l1 = "Heh. Didn't need the warning.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_LocationDisableOfficersGen("Antigua_Grot", false);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = false;
			
			if (CheckAttribute(pchar, "questTemp.DWH_GoodChoice")) SetFunctionLocatorCondition("DWH_VorovstvoSunduk", "Antigua_Grot", "box", "box1", false)
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_3";
			AddLandQuestMark(sld, "questmarkmain");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DWH_Podkreplenie");
			}
		break;
		
		case "Bandit_7":
			DialogExit();
			
			chrDisableReloadToLocation = true;
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			GiveItem2Character(NPChar, "cannabis7");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=3; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_"+i, "citiz_48", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
				if (i==4) sld.model = "citiz_49";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Antigua_Grot", "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "DWH_Grot_4");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "Take a look, "+npchar.name+", is this the plant you need?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Have you brought what I asked for?";
				link.l1 = "Not yet, I'm working on it.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "Yes, this is it. Now I have everything I need, and I can begin.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "Let's go quickly, we must not waste any time.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "Captain, if you don't mind, we'll speak later. We now face the most crucial part... the treatment.";
			link.l1 = "Of course, Thomas. I hope your daughter recovers soon.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+", Thomas didn't turn you away of his own will. The priest threatened him with excommunication if he accepted your help.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "I knew right away, "+GetSexPhrase("darling","beauty")+", that he gave me that refusal with a heavy heart.";
			link.l1 = "Is there a way to help him without the church taking offense?";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "Oh, "+GetSexPhrase("darling","beauty")+", it’s no easy matter, but the paths are known to me, I know what to do. Only, I can’t manage without your help, you understand.";
			link.l1 = "Of course, you can count on me.";
			link.l1.go = "gypsy_10";
			link.l2 = "I'm sorry, dark-brow, but I have absolutely no time for this. I've done everything in my power. Now I must attend to my own affairs.";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "Then here's what I need: an item that belongs to the girl, two stems of datura, one stem of ipecac, and one of verbena. If you bring me all of this, I can prepare a healing potion for her.";
			link.l1 = "Very well, I'll get everything needed.";
			link.l1.go = "gypsy_11";
		break;

		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Thomas, unfortunately, the priest didn't heed my words. But the gypsy and I can help you. I need...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "Are you suggesting that I go against the church?";
			link.l1 = "We'll do everything quietly, no one will know. Soon your daughter will be able to enjoy life again and freely walk around the town, as befits a young lady.";
			link.l1.go = "Tomas_23";
			link.l2 = "Damn it, Thomas Morrison, do you want your daughter to recover, or are you just hiding behind pretty words?";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "Fine, I agree. But please, act carefully. I don't want unnecessary rumors and trouble.";
			link.l1 = "Absolutely. So, I need a personal item of your daughter's. Something she's attached to.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "Fine, I agree. But please, act carefully. I don't want unnecessary rumors and trouble.";
			link.l1 = "Absolutely. So, I need a personal item of your daughter's. Something she's attached to.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "Hmm... Yes! I know what will work. Wait for me here, I'll be right back.";
			link.l1 = "I'll wait...";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("A few minutes later...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "Here. These are jade beads. Esther never took them off, they are very dear to her.";
			link.l1 = "Excellent. Now, all you have to do is wait. See you soon, Thomas.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "gypsy_21":
			dialog.text = "Have you managed to get everything needed?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "I've managed to get everything needed.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Remind me what I need to bring.";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "Then here's what I need: an item that belongs to the girl, two stems of datura, two stems of ipecac, and one of verbena. If you bring me all of this, I can prepare an herbal brew for her.";
			link.l1 = "Very well, I'll get everything needed.";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "Excellent. Now I can prepare a healing potion for the girl. It will be ready no earlier than tomorrow morning. You can find me as usual, on the streets of the town.";
			link.l1 = "Very well, see you then.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "Well, "+npchar.name+", is your potion ready?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "There it is, "+GetSexPhrase("darling","beauty")+". Let the girl put on these beads and drink the contents of the vial to the bottom. In no more than a month, she will be completely healthy.";
			link.l1 = "I'll take this to Thomas immediately. Farewell, dark-brow.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "Thomas, everything is ready. Esther should put on these beads and drain the vial of potion in one go.";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "Thank you, "+pchar.name+"! Please forgive me, I don't want to waste a minute...";
			link.l1 = "Of course, of course.";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "Greetings, "+pchar.name+"! My Esther has recovered! She is completely healthy and is now in church, giving thanks to our Lord God for sending you and the gypsy to us!";
			link.l1 = "Thomas, I'm delighted everything worked out! Take care of the girl, she has a long and happy life ahead of her now.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "Take these three hundred doubloons. Unfortunately, I cannot offer more, as I had to go into debt to gather this sum. But know that no words and no gold can express the gratitude I feel toward you, Captain. You've not only freed me from fear for her life but also given our family hope for the future. I will always be in your debt!";
			link.l1 = "Thank you! Three hundred doubloons is quite generous, so rest easy - you've thanked me more than enough!";
			link.l1.go = "Tomas_43";
			link.l2 = "I won't take your money, Thomas. Don't even think of insisting! Better buy young Esther a beautiful dress, she deserves it.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", visit us anytime. You will always be welcome in our home. And also, talk to the gypsy woman, she wanted to see you.";
			link.l1 = "I'll consider it an honor! Now I must take my leave - the tides wait for no captain.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "Of course, of course. May God be with you, "+GetFullName(pchar)+"!";
			link.l1 = "Goodbye.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "You are a most noble person, "+GetFullName(pchar)+"! May the Virgin Mary be with you! Visit us, you are always a welcome guest in our home. And also, "+pchar.name+", talk to the gypsy, she wanted to see you.";
			link.l1 = "Most assuredly! Now I must away - the sea beckons.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("Have you heard? "+GetFullName(pchar)+" procured a remedy for Thomas Morrison's daughter that miraculously restored the poor girl's health!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison lights a candle in the parish daily for the health of "+GetFullName(pchar)+". They say thanks to his (her) efforts, Thomas's daughter was freed from a prolonged illness.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison has blossomed before our eyes. As if she had never been ill. No one can really explain what made the illness retreat.", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_41":
			dialog.text = "And there you are, "+GetSexPhrase("falconet","dovey")+"! I knew you would return. Thanks to your efforts, the girl has recovered and now moves about like a dove. The whole town speaks of her with wonder.";
			link.l1 = "Well, dark-brow, it wasn't just my doing – don't give me too much credit. It was your brew that restored her health, so don't diminish your part in this.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "You have a kind heart, "+GetSexPhrase("falconet","dovey")+", and a sharp mind! You're destined for greatness – that's my prophecy.";
			link.l1 = "Heh... well, thank you, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "And there you are, "+GetSexPhrase("falconet","dovey")+"! I knew you would appear here again. Thanks to your efforts, the girl has recovered and now flutters like a dove. The whole town admires her.";
			link.l1 = "Now, now, you saved the girl yourself, and you want me to take all the credit? That won't do! You prepared the potion, you put her back on her feet, you should take the glory.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "You have a kind heart, "+GetSexPhrase("falconet","dovey")+", and a noble soul. I have a gift for you – one that any captain would appreciate. Here. Now the rats on your ship will have neither happiness nor peace!";
			link.l1 = "A gift for me? By the stars, most unexpected!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "Your soul is pure, I see that you won't burn mangarosa for momentary pleasure. If you need her urgently, come to me, "+GetSexPhrase("falconet","dovey")+". Five stems will cost you two hundred doubloons\nThis herb is capricious, not everyone can find it. So don't rush me – don't ask more often than once a month, I won't be able to obtain it anyway.";
			}
			else
			{
				dialog.text = "Your soul is bright, I see you're not foolish, you understand herbs no worse than some healers. You can find many things, though luck won't always smile. There is a rare plant that not everyone can find. It's called mangarosa. If you ever need it, come to me, "+GetSexPhrase("falconet","dovey")+". I'll get five stems, but I won't give them for free – two hundred doubloons I'll take\nBut this herb is willful, so don't rush me. Don't ask more often than once a month – even if you lay out all the cards of fate, I won't get it sooner.";
			}
			link.l1 = "Well, thank you, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "Captain, I keep thinking – it must have been the Lord Himself who directed you here at the right time! You saved my daughter, and I will never forget that.";
			link.l1 = "Perhaps, Thomas. The Lord's ways are inscrutable.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "Would you like some wine, Captain? I have something special for dear guests.";
			link.l1 = "Thank you, Thomas, but unfortunately, I must go.";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "What do you need, my falcon?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Tell me, dark-brow, would you have mangarosa for me?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Just stopped by to say hello. Time for me to go!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "Who else but me, "+GetSexPhrase("darling","beauty")+", would get you such a rarity? Two hundred doubloons – and it's yours, five stems, no more, no less.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Your price is fair. The gold is yours.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "Blast it all! My purse runs too light. I'll return when fortune smiles upon me.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "That's better. Take it. And mind you don't waste it needlessly, you know – mangarosa is no ordinary herb, power is hidden in it that not everyone can handle.";
			link.l1 = "Don't worry, dark-brow, I'll find a worthy use for its power.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 5);
			RemoveDublonsFromPCharTotal(300);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}