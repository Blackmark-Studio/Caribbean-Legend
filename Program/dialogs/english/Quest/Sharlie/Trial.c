// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "Good afternoon. You must be "+GetFullName(pchar)+"?";
			link.l1 = "You're correct, Monsieur LeCroix. Captain "+GetFullName(pchar)+" at your service. Fadey the Muscovite recommended you to me...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Yes, yes. My dear friend Fadey described you and your situation in detail. I knew it was you as soon as I saw you in the doorway. Tell me captain, what kind of ship do you have?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Ah...I don't have a ship at the moment , monsieur...";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "I have a "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+", her name is "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ha! Well what kind of a captain are you then if you don't have a ship? I'm sorry, monsieur, but in that case I don't have any work to offer you. All the best, give Fadey my regards!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "Well that simply won't do. That's not a ship sir, that's a boat! Alas, monsieur, you do not fit the role. Say hello to Fadey for me, good day!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "My ship wasn't big enough for him";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "You and I have discussed everything already, monsieur. Haven't we?";
			link.l1 = "Oui, Monsieur LeCroix... I'm on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Excellent. In that case you're a good fit for me. Are you ready to set out to sea right away?";
			link.l1 = "Yes, monsieur, I'm ready. What do I have to do?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "You must deliver a small batch of gunpowder and bombs to Port-au-Prince, on French Hispaniola. The commandant has been waiting for it for a while, so don't lose any time, you have about ten days left\nRespected "+GetFullName(sld)+" will take care of delivering and loading it onto your vessel. The commandant will pay you five thousand pieces of eight for the job.";
			link.l1 = "And that's the whole job?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "Oh by no means, monsieur. The commandant will explain the real job to you when you bring the munitions. This freight is just a small aperitif of the work you have ahead. But don't be afraid, if you do the job well, you'll make some serious money.";
			link.l1 = "You have my undivided attention, monsieur. My ship is ready to take the cargo on board.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "Let's not waste any time then, captain! Make your way to your ship and prepare to cast off.";
			link.l1 = "I'm going!";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Exploration mode: timer is disabled.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "What can I help you with, sir?";
			link.l1 = "Good afternoon, captain. You're Florian Shoke, I presume?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "I am. And you are the packet ship from Port-au-Prince, if I'm not mistaken?";
			link.l1 = "Aye, I have fifteen cannons for you. The deadline was a near-run thing, I barely made it...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Hm. Strange sense of humor you have, sir! For some reason I don't see fifteen cannons being unloaded from your ship...";
				link.l1 = "Well you see, we had a leak and had to throw some of the cargo overboard...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Glad to see you, captain?..";
				link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Nice to meet you. Let's not waste time and get these cannons aboard. This isn't going be easy, so I'll need your men to help.";
			link.l1 = "We'll manage. You there, get the block and tackle set up on the yardarm!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "You Goddamn idiot! If you can't even handle this simple task, you're sure to sink in the next storm. Make your way back to your ship, captain, and do something you're better at like delivering flowers to noble ladies. Better yet, sail back to Europe and leave the New World to real men. Good day sir!";
			link.l1 = "But...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "Whew, that was some thirsty work! I thank you for the service, captain! Take your reward, two hundred doubloons.";
			link.l1 = "Thank you!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You've received 200 doubloons.");
			PlaySound("interface\important_item.wav");
			dialog.text = "But that's not all, captain. Would you like to make another two hundred fifty golden double escudos?";
			link.l1 = "That sounds promising, but it depends on what you're going to ask me to do for it, sir.";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "I won't lie, it's dangerous. As you may already know, I lying in wait for a Spanish heavy galleon with a valuable cargo. The ship was put in the docks for a repair. According to my sources, she was supposed to set sail yesterday but it didn't happen\nBesides, my agent in Portobello didn't get to the rendezvous point to deliver the updates I've been awaiting. I suspect that the Spanish arrested him. I'll pay you to sneak into Portobello and find out two things: why the galleon is still there and what happened to my agent. Are you in?";
			link.l1 = "I'm afraid I lack of the proper training for such an operation. I'm a gentleman, not a spy. I might get into trouble myself and I won't be able to help you.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "Sounds dangerous, but profitable. I'll risk it. What's your man's name and what is the name of the galleon?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Well, aren't you entitled? I understand you. Goodbye then, captain, thanks again for your help!";
			link.l1 = "All the best, Monsieur Shoke.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "Aye, listen well then. My man's name is Sylvan Laforet, but in Portobello he goes by Jaime Silicio, a merchant. The galleon is named 'Alacantara'. I advise you to pass through the city gates at nighttime, through the jungle. The Portobello guards are very suspicious nowadays, not to mention that Sylvan's disappearance doesn't bode well for him being alive and well. You have two days until I have to get out of here before Spanish patrols find us. Good luck, monsieur!";
			link.l1 = "See you soon, Monsieur Shoke...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Exploration mode: timer is disabled.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Guards are less suspicious when you walk at slow pace!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "We've discussed everything captain, haven't we?";
			link.l1 = "Yes. I'm on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "How are things coming along, captain? What have you managed to find out?";
			link.l1 = "Things are going poorly, Monsieur Shoke. I'm not much of a spy, they found me out very quickly. I had to escape the city after fighting some guards. The only thing I managed to discover is that your man Sylvan Laforet has been arrested and is being held in jail.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "God damn it! That's not good... Did you find out anything about the galleon?";
			link.l1 = "No, I didn't.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "Damn. I really need some information on it. But this prize to too fat to give up! Anyway, I'll try sending another scout over there... Captain, I ask you not to leave me for now. I might need your help. Will you wait till another day while I'm sniffing out information about the Alacantara?";
			link.l1 = "Of course, I'll wait! I would like to make up for that failure.";
			link.l1.go = "florian_9";
			link.l2 = "I don't think so. Apparently I'm too bad at these games. I'm heading homeward.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Well, that's your choice. All the best, captain.";
			link.l1 = "Farewell, Monsieur Shoke.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "How are things coming along, captain? What have you managed to find out?";
			link.l1 = "Things are going poorly, Monsieur Shoke. I'm not much of a spy, they found me out very quickly. The only thing I managed to discover was that your man, Sylvan Laforet has been arrested and is being held somewhere.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "Then make your way to your ship, captain. Tomorrow at about the same time, or a little later, you'll have to visit me. Maybe by that time I'll have found something out. Don't set foot on shore, wait for me on your ship!";
			link.l1 = "All right. Will do.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "And captain, take this purse. Your efforts weren't completely in vain after all. At least we know what happened to poor old Sylvan...";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Captain, I don't have any news at the moment. We're still waiting...";
			link.l1 = "All right...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "How are things coming along, captain? What have you managed to find out?";
			link.l1 = "It's done. Your man, Sylvan Laforet, was arrested and is being held in jail. It is over for him.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "God damn it! That's dreadful... Did you find out anything about the galleon?";
			link.l1 = "Yes. She is being prepared to embark for a while now, but the governor of Portobello is intending on holding her at the dock. Right now he's waiting for a barkentine named the 'Puebla' to arrive from Cartagena with a cargo of gunpowder for the 'Alcantara'. According to a sailor from the galleon they don`t have enough of it and the governor fears pirates.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "How interesting!";
			link.l1 = "But if Puebla doesn't arrive within three days then the Alacantara will stop waiting and set sail.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Excellent work, Captain "+GetFullName(pchar)+"! I'm very pleased! Here, take your reward. You've totally earned it!";
			link.l1 = "Thank you! Do you have any other assignments for me?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 250);
			Log_Info("You've received 250 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "You are reading my mind, "+GetFullName(pchar)+"! Yes, damn it! Since Alacantara is low on gunpowder I can let her sail into the open sea and then force her to engage in a protracted naval fight, in which their powder will run off before ours, haha!\nYou should make sure that supply barkentine Puebla never reaches Portobello. I can't sail close to the shore, patrols will notice my frigate easily and run me off before I can intercept Alacantara\nYou can deal with Puebla on your own. Find her and get rid of her. Sink her or take her as a prize, I don't care. Just prevent her from getting here!\nIf you succeed, than go to Guadeloupe and see Gerard LeCroix, I believe that you already know him, don't you? He will pay you the coin you deserve.";
			link.l1 = "Deal! I'll be on my way to cut off the Puebla!";
			link.l1.go = "florian_19";
			link.l2 = "Wait a little, Monsieur Choquet. The fact is that I'm still ... Let's just say, not particularly accustomed to naval battles. And you are the captain of a frigate, you obviously have more than one naval battle behind you. If it's not difficult for you, you could... How should I put it...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "Glad you're here, captain. I've just received information from my spy and I have an important mission for you.";
			link.l1 = "I'm all ears.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "The Alacantara is ready to set sail, but the galleon's captain is waiting for the barkentine 'Puebla' to arrive from Cartagena loaded with ammunition. Apparently the Alacantara doesn't have enough gunpowder, so the Spanish are not ready to set sail yet. But the captain's patience has its limits and if Puebla won't come in three days then the galleon will leave Portobello without her\nThe Alacantara is low on gunpowder, I can let her sail into the open sea and then force her to engage in a protracted naval fight, in which their powder will run off before ours. Your objective is to intercept the Puebla and to destroy her. Sink her or take her a prize, I don't care. Just prevent that resupply barkentine from getting here!\nIf you succeed than go to Guadeloupe and see Gerard LeCroix, I believe that you already know him, don't you? He will pay you the coin you deserve.";
			link.l1 = "Deal! I'll be on my way to cut off the Puebla!";
			link.l1.go = "florian_19";
			link.l2 = "Wait a little, Monsieur Choquet. The fact is that I'm still ... Let's just say, not particularly accustomed to naval battles. And you are the captain of a frigate, you obviously have more than one naval battle behind you. If it's not difficult for you, you could... How should I put it...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "You would like me to you a lesson on the tactics of naval combat? With pleasure, captain! Especially since it's in my own interest: I want to be sure that you will successfully intercept the 'Puebla'.";
			link.l1 = "No, I didn't mean it. Fine, forget it: I'm sure that I won't have any problems intercepting a barkentine.";
			link.l1.go = "florian_19";
			link.l2 = "Yes, that's exactly what I meant. I am sure that new knowledge will not hurt me.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "So the first thing you need to remember is that half the battle is won or lost before it even starts. A lot depends on how ready you and your ship are for it.";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "First, make sure your ship is repaired. If you have holes in the hull then it will not be difficult for the enemy to send you to the bottom. And if you have rags hanging instead of sails, then this very significantly limits your mobility. The enemy can easily get away from you if the balance of forces is not in his favor or worse, catch up with you and impose an unprofitable battle on you - or even immediately board you. In addition, with torn sails, you'll struggle to gain the weather gage, that is, get upwind of your opponent where you want to be.";
			link.l1 = "Weather gage, got it. Anything else?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "Make sure you have enough men. Even the most powerful ship with 42-pound cannons becomes useless if you have one gunner running to reload three cannons and there is simply no one to control the sails. In general, I would just immediately board such a ship and seize her.";
			link.l1 = "Enough men, got it.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "Also, watch your cannons: they will wear out and explode over time. Over time, the condition of the barrels deteriorate, and if your cannons start to explode in the midst of a battle it can end very badly for you. I was not lucky at all: the batch of cannons I sailed with turned out to have several casting defects. If you had not brought a replacement in time, I would have simply abandoned the operation, since the Militant would be much inferior to the Alcantara in firepower. Tools need to be changed in time.";
			link.l1 = "Now I understand why it was so important!";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "In addition to cannons, also keep an eye on the amount of ammunition. Alcantara will fall to me because of this. If she has low stocks of gunpowder, she will not be able to fight a long battle - she needs to immediately go into close combat. And I will play on this: my frigate is faster, a heavy galleon will not be able to get away from it. But I also don't need to come close: I will impose an artillery duel at long range and then, when the gunpowder on the Alcantara runs out I will close, rake her with grapeshot, and board her.";
			link.l1 = "Desperate situation...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "Exactly. Keep an eye on your gunpowder and ammunition. If you run out of solid shot - and you will most likely not be able to sink an enemy ship. If you run out of grape shot, you can not hope for a boarding if you're outnumbered. If you have no chainshot or knipples, you will not be able to catch up with the enemy or get away from him if he is faster. All types of ammo are important.";
			link.l1 = "Instructive, thanks.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "And finally, depending on the type and size of your ship and the enemy ship, use the appropriate tactics. There is a tradeoff at sea between firepower and speed. On a large and slow ship, there is no point in chasing a brig or a corvette to board - you still won't catch up without softening her up first with chainshot. In such cases, it's wiser to blast her apart from range and pick through the wreckage. If you still need to board such a ship, it is preferable to use a fast and maneuverable ship.";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "At the same time, don't go toe-to-toe with a ship of the line with a brig. One broadside from a monster like that will shatter smaller ships' hulls into splinters. Use your advantage in speed and maneuverability, rip down her masts and rigging then close and rake her decks with grapeshot if you still need to board. If you need to sink her... it won't be an easy task, but it's possible. You can board her and then fire her powder magazine, but it's never shameful to flee. A good captain will save his ship and crew from certain death instead of excessive heroism. Remember, discretion and prudence are often the better part of valor.";
			link.l1 = "Thank you very much, Monsieur Choquet!";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "Glad to help captain. I hope this knowledge will help you in the future.";
			link.l1 = "I'm sure it will help. We're off to intercept the 'Puebla!'";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "That's an unusual accent you have there, senor. Or should I say 'monsieur'? Would you like to see Jaime Silicio? Perhaps you can share the same cell. Take him, boys!";
			link.l1 = "Well, if you don't like my accent perhaps I can introduce you to French swordplay!";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
