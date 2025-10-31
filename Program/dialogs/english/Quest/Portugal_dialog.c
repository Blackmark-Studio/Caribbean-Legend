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
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "Bug. Tell the devs.";
		link.l1 = "Sure.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Oh, another brave sailor! I know your kind, my God-damned eye is trained on you, ha! Ask me why?";
			link.l1 = "I will ask you about a different matter, it is about your debt which you owe to the mistress of the local... umm, establishment. She has asked me to remind you about your debt, I suggest you do something about it, otherwise she will have to ask the guards to do the same tomorrow.";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "Local est... oh, fuck! Johanna, she can't do this to me! Are you sure? Did she really say she would send me to the casemates for a few goddamned coins?";
			link.l1 = "Absolutely. That is what she said. I suppose my mission is over, farewell, mynheer Avendell.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Wait! Please, wait! You look like an experienced captain. Surely, you've got some coins, I am broke, only the good old bartender fills my cup on credit for the sake of our old friendship. Listen to my pro... proposal! You pay my debt and I will cut you a slice\nThere is a business... a very profitable business, damn me and my arse! I swear on my bloody anchor, just trust me, captain - whatever your name is!\nJust redeem one small debt, ten thousand pesos and you'll have a chance to make enough coins to buy all the brothels in the New-bloody-World! What do you say? You give me, I give you, as honest folk do...";
			link.l1 = "A ragged fellow who promises treasures. Spare me that nonsense, I don't do charity for people like you. Find the money or you'll be living in the fort's casemates quite soon. Farewell!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "A slice? And why should I trust the word of a drunken idiot? Because of imaginary promises?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Listen to me, captain! Hic, shoot me dead if I am lying! But I am telling the truth! Think about it, if you catch me lying, then you can cut out my guts with that beauty you carry on your belt! Damn, her hilt costs five times more than my miserable debt! So what do you say? You've got nothing to lose!";
			link.l1 = "I have had enough of your speeches. Farewell.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Fine, Hugo... I will risk believing in that nonsense you speak. But remember, you will have to persuade me and make sure that my money wasn't wasted when I return, otherwise it's your neck on the line.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "No threats needed, I understand. I give you my word, captain! We will be rich! Come back when this damn debt is repaid and we'll t... talk! Yes, we will! You won't be left aside!";
			link.l1 = "Fine, I will wipe away your debt, but you'd better pray, Hugo Avendell, that your 'proposal' will satisfy me.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "Captain, come back as quickly as you can - this business might slip away.";
			link.l1 = "Yes, yes, I will repay your debt soon.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "You are back, captain! By the storm and God damn thunder, I am so glad to see you! What about my debt?";
			link.l1 = "I've dealt with it, now it's your turn, Hugo. Tell me your story and try to make it just slightly believable!";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "Don't worry, captain! Did you know that I am a bounty hunter? Or... I used to be. I suppose I wasn't lucky enough. Perhaps even the Devil himself, with all his deeds, wasn't as much of a loser as I was. I lost everything on my last job... The crew deserted me and I had to sell my ship because of my debts...";
			link.l1 = "I am already informed about your heroic past. Straight to business, Hugo, don't test my patience.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Yes, yes, captain..."+GetFullName(pchar)+", am I right? I know something about you too. But damn me if it's important. Have you heard the name Bartolomeo the Portuguese?";
			link.l1 = "Bart the Portuguese? Of course I've heard of him. Everyone has. He's a pirate, a butcher, and scum as far as I'm aware. And what part does he play in your story?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "He is playing a bloody major part in it! I have been tracking him down for the past year and a half. The Dutch Company has put a hefty price on his head. But I have failed, and I have lost everything. And the Company has recently tripled the reward for him—alive, and alive only, damn him!";
			link.l1 = "For good reason, it's no easy task to capture him alive. Anyway, why should I care about that, Hugo? It looks like you're trying to cheat me!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "I wasn't even going to, captain! You know, the local doctor, Peter Van Stal, a very nice man, gave me a potion to cure my headaches! So, the doctor wasn't in his house for almost three days and...";
			link.l1 = "Hugo, my patience is almost gone! I promised the lady I wouldn't stab you with my blade, but my fists will do just fine! I swear that no potion will be able to cure your head tomorrow!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Wait, captain! Please! Listen to me, I saw a few men near the doctor's house and I recognised them. They're from the 'Albatross', a frigate of the damned Portuguese! And one of them was talking about their captain's health! Look now, "+pchar.name+", Bartolomeo is here, in this city! Right under our noses, he is either wounded or ill, which is why they need a blasted physician!\nI doubt the Portuguese has brought his whole crew here, but I can't start this mess alone! Surely, you know damn well how to handle your cursed sword! Take a few tough men with you and we'll find the rat! Then we capture him and deliver him to the authorities!\nAnd two thousand good gold doubloons will be in our pockets!";
			link.l1 = "No, Hugo, I've had enough of your talk. I won't take part in this mess, even if you are right. Farewell.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Hmm, interesting. Do you know where he is hiding? If it works out we can discuss shares, but if what you are telling me is the truth then we must hurry now!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "No, I do not know where he is, captain. I was too scared to track down those lads. If the One-eyed had seen me... fuh! But together, with your lads, we will be able to comb this entire town, call your men and let's get started! Damn, the Dutch doubloons are waiting for us! Such a God damn chance happens only once in a lifetime, bite me a herring!";
			link.l1 = "A commendable enthusiasm... I hope you can manage to leave the table, 'great' bounty hunter. I'm going to start searching right away, and you can follow me if you wish—just don't get in my way too much.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Yes, yes, captain, just let me finish my drink and I will join you... Where shall we start?";
			link.l1 = "Where?!... I'm going, with or without you.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Wrong house, pal. Get lost, now!";
			link.l1 = "Hm. And I think this is the right house...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Well, I did warn you...";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Full and by, flying high, sons of... prepare the cannons!... ah-ha-ha... oh, my beauty...";
			link.l1 = "Hmm, he's lucky to be alive...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "Oh God, who are you? Please put down your weapon! There is a sick man here!";
			link.l1 = "This 'ill man' of yours has killed more people than you've seen in your life, doctor. Get away!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "He is my patient and he is barely able to stand! Can't you see that? Please, put your blade down! I beg you!";
			link.l1 = "And what is wrong with him, damn it!?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "I suppose it is all because of his wound, a blow dealt by a poisoned Carib weapon... and the men who brought him here said that if he dies, I'll die! But I am doing all I can, tell them that!";
			link.l1 = "Don't worry about those men, doctor. My lads will keep an eye on your house and I have to go see the governor. I suppose he'll piss himself with joy. Don't leave this place until I return, doc.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "I won't leave, don't worry about that. Let's just hand him over to the authorities already and end this nightmare.";
			link.l1 = "Of course, I am on my way.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "We did it, captain! We've found him and soon we'll be rich, just as I told you! What's our plan?";
			link.l1 = "I hope so, Hugo. Anyway, it is not over yet. I suppose I have to go to the governor and discuss our reward?";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "No-no, no captain! Don't go to that damned Thomas! Trust me, this scoundrel will take away our prisoner and, if we're lucky, he'll treat us to a cup of coffee! His Excellency is a slippery sort, so if you want to get the full reward, you have to sail to Curaçao! Otherwise, the Portuguese will be taken from us to the fort and we'll be driven away like beggars!";
			link.l1 = "Well, if you are really sure about that...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "I am, captain, damn sure I am! But remember that Bartolomeo's men must be somewhere in the town and we don't want to attract the garrison's attention either, that's for damn sure! We have to decide how to get the Portuguese to your ship and how to do it in an unnoticeable way.";
			link.l1 = "Fine... I don't want to fight his frigate on the way to Willemstad. Got any ideas?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Yes, I have one. We need to find a more noble suit for him first, then we drag him through the rear entrance as a drunken officer! No one will suspect that he's a damn pirate, trust me!";
			link.l1 = "Hmm, I'm not sure about this, but we don't have a better plan yet anyway. I'll try to get some fine cloth for our passenger. You stay here and watch over Bart and the doc.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Don't worry, captain. The Portuguese is under my reliable guard, he-he...";
			link.l1 = "I would like to believe that...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "I don't see the soldiers, "+GetAddress_Form(NPChar)+". Where are they? You said he would be arrested as soon as you told them about the situation. So why are the soldiers not here?";
			link.l1 = "There won't be any soldiers, mynheer Van Stal. I am going to do the job myself and I have to take your patient to Curaçao as soon as possible.";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Captain, listen, I can't handle his wound, all I can do is lower the fever a bit. He is mostly unconscious and delirious, there is no doubt that he will die even without any interference, and the rolling of the sea will kill him in a few days. I will give you some mixtures that will help...";
			link.l1 = "No, doc, you're sailing with us. First, I'm hopeless at medicine, and second, I doubt you want to stay here and explain to the Portuguese men where their captain has gone?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "...Yes, I suppose you are right. But know that this pirate is very resilient. I have seen people with only minor wounds from Indian weapons, and all of them died in less than three days. And according to his 'friends', he has been in this state for a week already! Nevertheless, I maintain that he will survive only a short while on a ship in the open sea. Three days, no longer!\nThat's all the time we have.";
			link.l1 = "Even a bird couldn't reach Curacao in three days. But I think I know what I can do! There's this... friend of mine, he lives in St. John's, Antigua. He knows how to heal people from fatal wounds. He's the only person who can help us now. Our goal is simple - to get there before the Portuguese dies. Pack your things, doc, we set sail immediately and your patient will be transferred next!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "What a pity, captain. We've lost, and we won't see that damn gold. Farewell.";
			link.l1 = "Farewell, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Doc, get your patient ready for landing. The longboat is ready. Hurry up!";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "I am on my way, "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "This house stinks of bloody mixtures! It would be a real surprise if the Portuguese died here; even breathing this smell could cure any disease!\nAnd the man's crew could easily find us thanks to the stench!";
			link.l1 = "Hugo, spare me your jokes. I have left a few men on the streets to watch over the house, but one more guard won't be unnecessary for our guest. Keep an eye on him and try to stop the swearing, or Gino will make you drink some mixture of his; I am sure he can cure that.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "Don't worry, captain! I will watch over our money most vigilantly; he wouldn't escape even if he were healthy! And I beg you, please, no more mixtures!";
			link.l1 = "See, you can be nice when you want. Stay alert, I have to go.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Leaving already, captain? Good! It's time! I saw a few suspi... suspicious lads on the street. They don't look like Portuguese men, though they were searching for something. We have to be careful, captain!";
			link.l1 = "Fine, thank you for your warning, Hugo. Let's go to the ship.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Captain, we have been waiting for this meeting for far too long! And who is that with you? Bartolomeo the Portuguese himself, ha, it seems the Bold Pierre was right - it is him! Stay back, captain, we are taking him with us and no one will get hurt.";
			link.l1 = "I'm sorry, sir, but who the hell are you? Get out of my way or none of you will see tomorrow!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Oh, such a menacing fellow, just look at him, lads! Ha-ha-ha! Listen here, pup, don't stand between Leo Cord and his money! We've been tracking down the Portuguese for almost half a year, and now we've finally got him. So put down that toothpick of yours and get lost while you're still breathing! We're not that greedy; a dead man will do just fine, ha-ha!";
			link.l1 = "Enough. Let's dance, gentlemen!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "I knew something was wrong here! Well done, captain! But it's time to go, that damn Leo Cord has a lot of bandits around here and a fine ship! We have to get away from this island!";
				link.l1 = "Good point, Hugo, and I am very glad that no bullet was fired at the hole where you were hiding.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "What a pity, captain. We've lost and we won't see that damn gold. Farewell.";
				link.l1 = "Farewell, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "I... I was securing our rear, captain! You were doing just fine without me, but what if someone had attacked us from the other side of the street? You wouldn't have had time to run to the ship.";
			link.l1 = "Perhaps that's why you didn't succeed in your line of work? Whatever, enough talking, we have to get to the ship! Time is running out!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Captain, the Portuguese is feeling really unwell, we need to stop!";
			link.l1 = "That is why we are here, mynheer van Stal, our journey is almost over. I will rent a room in the tavern and our prisoner will stay there for a few days.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Mynheer captain, I will look after the Portuguese, he needs complete rest.";
			link.l1 = "I got it, doc, it's alright. Damn it, how long am I supposed to take care of this pirate? This is bad for him, it's not what he needs! It seems I was hired as a babysitter and... agh, pardon me, doctor, it's just too much... I'll see you later.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Monsieur, are you the captain "+GetFullName(pchar)+", whose ship has just arrived in our harbour today?";
			link.l1 = "You are correct, how may I help you?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "His Excellency Jacques Dille du Parquet, the governor of our colony, is waiting for you. The matter is urgent!";
			link.l1 = "Fine, monsieur, I will visit His Excellency today.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "We have reached Martinique, captain! Our money is not far now...";
			link.l1 = "Only if the Portuguese survive until we reach Willemstad. Hugo, I have to go to the ship, so you will have to watch over the doc and his patient.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "To go to the ship? Why? Will you lend me a few of your men to help me out? What if something happens while you are away?";
			link.l1 = "I am sorry, but no. I doubt that anything can threaten you here. The garrison is on alert and there are more soldiers on the streets than usual, so if something goes wrong, call them. They have seen a large ship not far from this island, a pirate one, perhaps. And His Excellency the Governor has asked me to fortify the island by patrolling with my ship.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "A ship? A pirate one? It could be the Albatross! Or perhaps a colleague of our old friend Leo Cord!";
			link.l1 = "Or perhaps it is just an ordinary pirate ship. Nevertheless, Hugo, if this vessel is here for our heads, then I'd better face her with the local patrol by my side and for the governor's gold. It is much better than watching our rear for the rest of the trip. If this alarm is false, however, then it will simply spare me from sitting on my arse in the tavern for a few days.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Think about it, captain, is it wise to leave the dam... the Portuguese unprotected while his frigate could be cruising around? You are risking our reward by accepting the governor's fee!";
			link.l1 = "Enough talking, Hugo Avendell! I am the captain here and the final decision is mine! So do as I command you. Go to the tavern and keep an eye on the doctor and the Portuguese until I'm back.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "You are back, captain, at last! I'm afraid I have bad news for you – the Portuguese is gone, and so is the doc!";
			link.l1 = "How?! And what were you doing then, you blockhead?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "I can bet that ship was the 'Albatross'. I saw the Portuguese men, they entered the tavern and I... I ran away. I'm sorry, but meeting the One-eyed Dog was too much, even for that much money!";
			link.l1 = "Bloody hell! At least tell me what happened in the tavern?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "I told you I saw nothing. I ran through the kitchen as soon as I saw Franz Garcke and his men... It was too close! It happened yesterday evening and I didn't know how to let you know...";
			link.l1 = "Yes, you are a very brave and resourceful man... Fine, let's give you one more chance, we are going to find them. I have been saving this scoundrel for too long and now I consider him my property. We still have some time to catch them, so let's start from the tavern; perhaps someone has seen more than your fleeing heels. Go, prepare yourself!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Have you heard him, captain, he was talking about the One-eyed Dog, I told you about him recently. And the lisping Castilian is Hernando Vasquez, the bloody Don - the butcher of Vera Cruz, I didn't see him!";
			link.l1 = "Relax, Hugo. I am sure that Bartholomeo is still on the island; he might be feeling better, but he is still too weak. And I think I know where to find him! We will get them, I won't walk away from my reward. If you are no coward, then follow me – it is not over yet.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "You ask too many questions, captain... Wait, aren't you that sneaky fellow from Philipsburg? You've been running from us for too long and now look - here you are...";
			link.l1 = "Too bad for you, scum!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... you miserable crab's shit, you'll tell us everything, you can trust me on that, you bloody rat! Then you'll be hanged from the yardarm instead of the topsail... And who the hell are you? Damn, those apes can't be trusted! Always have to do everything myself...";
			link.l1 = "Am I bothering you, gentlemen?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "I like your timing... I suppose I ought to thank you for keeping me alive until today?";
			link.l1 = "You are correct. My name is "+GetFullName(pchar)+" and you, Portuguese, are still my prisoner. So don't ask me questions, we have to go.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Wait, captain... There are a lot of Vasquez's men in the town, they won't let us go just like that. Give me a sword and we'll have much better chances.";
			link.l1 = "You are not on good terms with your partners, huh? Fine, an extra blade is always welcome. Take the corpse's weapon and stay close to me!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Don't even think that I would give you a weapon so you could strike me the moment I turn my back! Just stay close to me.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Don't worry, captain, I'd rather die than fall into Vasquez's hands again.";
			link.l1 = "Well, the thing is, I don't want you dead yet. Let's go, time is running out!";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Too bad, I would have helped the One-eyed if I wanted you dead...";
			link.l1 = "But you didn't help me either, so shut up and move!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Damn! That's them! Kill them all!";
			link.l1 = "Here we go again... Come on then, you mongrels!";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Splendid! You have killed the One-eyed Dog, that's what I call a masterpiece! How many of his men did you send to burn in hell?";
				link.l1 = "I was fighting, not counting. And where have you been, Hugo?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "What a pity, captain. We've lost and we won't see that damn gold. Farewell.";
				link.l1 = "Farewell, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "I... was ensuring a safe withdrawal... protecting our rear, so to speak.";
			link.l1 = "Well, that's it, Hugo Avendell, your cowardice has surpassed all my expectations. Have you any idea how tough that fight was for us? We barely made it!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Calm down, captain... I admit I was hiding. But I have found this opportunity for you! Remember, it was I who led you to the Portuguese! Well... considering your fair indignation, I agree to only a third of the reward.";
			link.l1 = "That's just glorious! Are you bargaining now? No, my friend, your part in this business is over! You lost your money in the tavern in Saint-Pierre. You left it there and ran away, so it's over for you now.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Captain, you are clearly exaggerating... Fine, I agree to a quarter... to a fifth! Ten percent!";
			link.l1 = "Do not test my patience! Get lost! I don't need cowards in my crew, especially now, with the clock ticking!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", don't you think it's a bit unfair?";
			link.l1 = "Cause and effect, Hugo... You have made your choice, so farewell. Draw your own conclusions and don't plunge into adventures like that; this is clearly not for you.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "Dropping the ballast, captain? So true, ha... Vasquez is still free and there are a lot of men and guns on the Albatross. I’d wager my fine trousers against an old kerchief that Hernando won’t let us escape.";
			link.l1 = "Well, it seems that we have to go and greet him ourselves. Go, monsieur Portuguese, and try to keep your mouth shut. We are going to weigh anchor as soon as possible.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "What are you waiting for, damn it?!";
			link.l1 = "Where is Hernando Vasquez? Speak and I will spare your life.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Go to hell with your bloody questions!";
			link.l1 = "After you...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "And here you are, my brave friend, we can finally have a proper conversation! Congratulations, captain - killing the One-eyed Dog and destroying the 'Albatross' was no easy feat! Truly, you have done so much to save my life... Perhaps I should even thank you?";
				link.l1 = "You will thank me when you are dancing on the gallows, or whatever they have prepared for you in Willemstad.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "And here you are, my brave friend, we can finally have a talk at last! Congratulations, captain – killing the One-eyed Dog is worthy of an honourable song! Truly, you have done so much to save my life... Perhaps I should even thank you?";
				link.l1 = "You will thank me when you are dancing on the gallows, or whatever they have prepared for you in Willemstad.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "Incredible! You have been saving my life for the past two weeks, you have brought me to your home and protected me in fights... and now you are going to send me to my death? I can hardly believe it... Actually, I almost consider you my friend now, ha-ha.";
			link.l1 = "A pirate appealing to honour? Portuguese, are you kidding me? I was saving you for only one purpose - to let the murderer and scoundrel face the court of justice!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Friend of mine... sounds like mockery. But nevertheless, you are right. It would be strange of me to do that, Portuguese...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Oh, that's enough, captain. I bet you did all that just to get the money the Company promised for the pleasure of seeing me alive! Don't try to be more honest than you really are, sir, it doesn't suit you.";
			link.l1 = "Only I can judge myself. So let's end this conversation. It's time to sail to Willemstad.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "It seems that there is still some honesty to be found in people these days... Too bad that money always gets in the way - eh, captain?";
			link.l1 = "Strange to hear that from a gallows-bird pirate, Portuguese. I'll let you go... don't ask me why, just get the hell away at the very first port. And remember, I won't be so kind if we ever meet again.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Really? I would like that, captain! Won't you order some rum to be brought here? You know, just to celebrate your knightly qualities, our relationship, and the deferment of my sentence?";
			link.l1 = "Don't make wicked jokes, you're still my prisoner until we reach the first shore. Farewell.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "I see... so it's the gallows then. That was to be expected. Now listen to what I have to say, captain. You were so eager to keep me alive just to execute me properly later, and I appreciate that. I suppose it would be foolish of me to ask you to change your mind just like that, right? And what would you say if I offered you something in exchange? A deal, so to speak, hmm?";
			link.l1 = "I won't say anything, Portuguese. You are a pirate and a bastard. You will answer for your crimes in Willemstad.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "A deal? What can you offer?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "I don't need your deal, just get lost at the very first port. It's your lucky day.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "You know, such persistent saving of my life, despite the unpleasant reasons behind it, still deserves some gratitude. And Bartolomeo the Portuguese knows something about being grateful. Now listen, a month before you and I met, we captured a ship of the Company. They fought like devils to the last man. But their holds had only cannonballs and rats\nMy crew didn't like it, yet I found a very interesting chest and some papers inside the captain's cabin. She was a courier ship, delivering samples from mines somewhere in Amazonia. Pure diamonds and rubies, a real fortune!";
			link.l1 = "An interesting prize... Now I see why the Company is so interested in you, but what is the point of your story?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "My first mates Vazquez and Franz Garcke had been keeping the crew in order, so I decided to take my chances. I hid the stones from them and burnt the papers. The Dutch had badly damaged our rigging during the boarding, and we had to take the 'Albatross' into a small bay of a small island in the north. I went deeper into the jungle alone while the whole crew were repairing the frigate\nI buried the stones; keeping them aboard was too risky considering the circumstances. My plan was to escape from my beloved crew at the very first port, buy or steal a small boat and sail to the island, collect my prize, and then... farewells to my old life! Europe, a decent mansion, a beautiful wife, you know the rest...";
			link.l1 = "Let me guess, something went wrong.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "Everything went wrong! The damn island turned out to be home to a horde of local cannibals. They attacked us as soon as I returned to shore. We had to sail away as quickly as possible, it was then that I got hit. I thought it was only a scratch.\nA few days later I was lying half-dead with fever and apparently said something about the stones. Franz and Vazquez realised that I had hidden something on the island, yet they didn't know the exact location. They didn't like the idea of wandering there and being constantly shot at by the Indians. So the bastards dragged me to the nearest port, since our physician had been killed during our fight with the Dutch, they needed a new one.\nThat's how I ended up at that doctor's place, they wanted to bring me back to consciousness just long enough to torture me and find out the location of the stones. I believe that afterwards they would cut me up and feed my juicy meat to the crabs.";
			link.l1 = "I can't say that I judge them - you were trying to cheat your men. So I ask again, why are you telling me about that?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "These dogs were not people, trust me, they are all now in their rightful place - in hell, ha-ha! As payment for my freedom and my life, I can tell you the exact location of the Dutch treasures.";
			link.l1 = "No, Bart, your betrayal has completely convinced me of your wickedness. Willemstad and lawful retribution await you. No deal.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "And am I supposed to believe that those gems actually exist? Whatever, I won't lose anything anyway... The deal was the start of this story and the deal will be its end. I accept your terms, Portuguese.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Consider this my modest gratitude. Eh, I wish I knew how much Bartolomeo the Portuguese's hide is worth in shiny pesos, ha! I understand your goals were strictly practical, but still, thank you, captain, for everything, ha-ha\nIt's Turks, the jungles not far from its shores. Find a dry, crooked tree—there is only one such tree there. I buried the chest close to it. So don't forget to take a shovel. Happy hunting...";
			link.l1 = "Fine, I will remember that, and you can take a longboat right now and get off my ship. Farewell.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "One last thing, captain. I suppose there are still a lot of savages, but it's not only them you should worry about. Vasquez wasn't on the 'Albatross', right? The Bloody Don is too clever... watch your back until you see him hanged or with a bullet in his head.";
			link.l1 = "Thank you for your warning, Portuguese. Now, would you kindly leave my ship already... don't test my patience.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "Oh, and who is this! Captain "+pchar.name+" himself! Want a drink?";
			link.l1 = "You know, I am actually happy to see you again. But perhaps I was too harsh with you on Martinique.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Whatever, captain! What happened, happened... But truth be told, I really did give you a reason to send me away... But hey, you won't believe who is a guest in Phillipsburg today!";
			link.l1 = "Don't tell me that it is...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "No, no, captain, it is not the Portuguese. And it is not some wounded bastard again. It is much better! It is Hernando Vasquez... The Bloody Don himself! He has been a guest of the local governor for the past few days.";
			link.l1 = "Vasquez? The guest of the governor? I see now. Hugo, tell me more about this, what the hell is going on here?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Well, I know a lot... but thanks to our voyage, I am bankrupt again. Perhaps your need for this information is worth a few pesos?";
			link.l1 = "Hugo, you are still an extortioner and a scoundrel! Say what you have to say, take 5000 pesos just for the sake of our old friendship.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "Somehow, I am not surprised. Here, take 10,000 pesos, and you had better hope that your information is worth that much!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "I have a better proposal for you. How about joining my crew? I gather you have a talent for making and finding profitable deals, so if you are tired of pretending to be a brave fighter - you are more than welcome to take the position of my purser.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "No, captain, it is not going to work like that! You have snatched a large sum with that damned Portuguese, I am sure. So consider that to be my share, don't be so greedy. 15,000 coins and not a single peso less!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "Ah, to hell with you, take them!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Well, they say greed is good... Isn't that a bit much for you, huh?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "Now that's the prize for me! ... Listen, Vasquez was sailing with me on the same ship, yet while I was cleaning the decks to pay for my passage, he was resting in a cabin, so thank God we rarely saw each other and he didn't recognise me. But I started following this devil straight away... An interesting story happened to him.";
			link.l1 = "Go on! What is he doing in the governor's palace?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "I don't know much, but the garrison has been on alert for a few days since his arrival, and the huge warship suddenly weighed anchor and left in a great hurry. It sailed northwest, I believe. The whole town was lost in speculation and gossip...";
			link.l1 = "So that was the ship I encountered! Intriguing... Don't stray from the topic, Hugo, please continue your story.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Well, as I said, the ship was gone and Vasquez had become some sort of guest of our governor, Martin Thomas. I see him sometimes in town, he is always in the company of a few soldiers. I don't know if it is his escort or a convoy, ha-ha. But only people in the residence could tell you more regarding the Don.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Perhaps you are right. But we had a deal, remember? Don't play the hero, go to my ship and wait for my return. I will try to speak with our hospitable governor.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Well, that was interesting. You have really helped me, Hugo. Drink your rum, the rest is none of your concern.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Are you serious, captain? What is wrong with you? You drove me away by pointing a gun at my face, and now you come to me with such proposals?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Forget about that, I haven't been myself and I'm sorry, greed consumed me I suppose. Here, take 10,000 pesos and tell me what you know about Vasquez, I'm in a hurry.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Perhaps I should apologise for that matter. You are a pathetic fighter, but you do well with coins. I repeat my proposal, what do you say?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "What can I say... I'll agree, but only after I get my share, captain. Ten percent, remember? You received two thousand for that scoundrel, so if you're asking me to join your crew, you'd better start by settling your debts. Ten percent, and no arguments!";
			link.l1 = "You are such a swindler, Hugo. I don't have that much on me right now, but I will be back soon. Stay here.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "I hope that you will live up to my expectations with that business acumen of yours, ha! Take your cut!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "It is your call, captain. I will stay here for a while. Come back if you change your mind.";
			link.l1 = "Fine, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "Have you changed your mind, captain? I'll wait for my money then.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Take your coins, you scoundrel, ha-ha!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "I don't have such a sum yet.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 25;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "Good day, captain. Do you want something?";
			link.l1 = "No, no, I am just waiting. When will mynheer Thomas be free? I am waiting for an audience... yes. Tell me, does His Excellency really consider the famous pirate Hernando Vasquez his friend?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Worry not, mynheer, he should be free at any moment now, and of course not, mynheer! This bandit has surrendered to the authorities, but somehow he wasn't hanged. Perhaps he bought his life by betraying his old partners in crime... I am not sure. He has been imprisoned for several days here... That was a nightmare, mynheer! That beast in human form was living in our mansion!";
			link.l1 = "A nightmare it is! What could that beast have told mynheer Thomas to avoid the gallows? I can't even imagine!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "I don't know either, but I can secretly tell you that all the servants were glad when his Excellency got rid of such a guest...";
			link.l1 = "Got rid of him? Did he finally get what he deserved?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Not quite so. Yet. A few days ago, he was taken to a military brig which sailed to Willemstad. You see, mynheer Thomas had lost interest in the scoundrel; it seems he tried to deceive him.\nAlso, they say that his former captain was caught - Bartolomeo the Portuguese! Just think of it! Looks like the Company wants to hang them together. Word is the trial will be in a month, but why wait so long?";
			link.l1 = "The Portuguese?! Hm... thank you for keeping me company, friend... it seems that mynheer Thomas is free now, I shall take my leave.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Now you are dead... both of you!";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Now this is someone I didn't expect to see, captain! But it doesn't look like a friendly visit, all this blood, noise, and gunfire, or is it some kind of celebration with fireworks, eh?";
				link.l1 = "Stop cracking your wicked jokes, Portuguese. I just don't like how you have used your freedom which you bought from me. I have put too much effort into saving your pathetic arse to let you be so stupidly caught right after our parting!";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "Well, I was bored! So I came here to visit you. Are you comfortable here, friend!";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "Be careful, friend! Ah, too bad I can't help you!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "So, nobility is sometimes not swayed by coins, eh? Hah... WATCH OUT, RIGHT BEHIND YOU!";
			link.l1 = "Agh, not this bloody mess again!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "So, nobility is sometimes unaffected by coins, huh? Hah... WATCH OUT, RIGHT BEHIND YOU!";
			link.l1 = "Agh, not this bloody mess again!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "And I warned you that this guy was trouble!";
			link.l1 = "He almost managed to shoot me in the back! How did he get through?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "I saw that he had a lockpick, it seems that someone had given it to him... he always had connections in the lower strata. Well, captain, I believe we should leave this place, don't you agree?";
			link.l1 = "You don't say! Fine, let's hurry before the whole garrison arrives. I'll break your lock in a second...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "You know, captain, this fresh air... you only start to appreciate it after spending a few weeks in a dungeon, right after your ship's boat was found by the local patrol. I suppose I still owe you for my rescue.";
			link.l1 = "No need, Portuguese. I am not an honourable knight, I just... I do what I think is right and what needs to be done.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ha, and that is a perfect quality! But I insist, here, take it... this is the only thing I managed to hide in prison... Yes, you got it right. This is my talisman. It always brought me luck at sea. You are a fine sailor, and you or your navigator will be able to use it, I am sure of it.";
			link.l1 = "Yes, and you were lucky enough to fall straight into the hands of the Dutch with that talisman.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "Hey! I am still alive, aren't I? And just so you know, I am no longer in prison. Take it, captain, it is time for the talisman to serve you. And I thank you again!";
			link.l1 = "Farewell then, Portuguese. And, please, try to stay away from the gallows! Just for the sake of my hard work, ha-ha!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("You have received the talisman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
