// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
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
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "Talk to our captain. I've got nothing to tell you.";
			Link.l1 = "Fine.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Talk to our captain. I've got nothing to tell you.";
			Link.l1 = "Fine.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Sir, are you looking for someone?";
					Link.l1 = "Yes, mate. Can I see the captain?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "If you are looking for our captain, he has recently landed.";
					Link.l1 = "Fine";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Oh, you've come here alone. Ha! In that case, go to our captain. Tell him about your sorry deeds...","Shiver me timbers, it seems you're insane, friend. Go to our captain and he'll talk to you.");
				Link.l1 = "Too bad...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "You'd better look for him at the port.";
			Link.l1 = "Thank you, my friend.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Well, that was a serious mess, cap! We were in the tavern, drinking as we usually do, when we heard screaming. We ran out of the tavern and saw that they were trying to arrest you. Damn them! So we decided to leave this unfriendly harbour.";
			link.l1 = "Yeah, certainly some people have a rather strange perception of justice.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Captain! Don't fret like that! It was clear there was no way to escape quietly, so we decided to visit the local banker to check his chests. Here is your share - "+sti(pchar.questTemp.ReasonToFast.p9)+" pesos...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Captain! Don't fret like that! It was clear there was no way to escape quietly, so we decided to visit the local banker and check his chests. There was also a fine sword in the pawn box. Here is your share - "+sti(pchar.questTemp.ReasonToFast.p9)+" pesos and a sword...";
			}		
			link.l1 = "Well done, boys! Well done! I am proud of you.";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Captain, your friend has escaped.";
			link.l1 = "What friend?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Well, the friend whom you have taken from the dungeons.";
			link.l1 = "How the hell did you manage to lose him?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "It wasn't our fault, Cap. He jumped out through the latrine into the sea... We tried to shoot him, but it was too dark in there...";
			link.l1 = "Damn it! You really have got out of hand! All of you will be put ashore and sent to work in the sugarcane fields! To lose such a valuable bigwig! Unbelievable!";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Captain, forgive us, it was our fault – the prisoner has escaped.";
			link.l1 = "What prisoner? Who has escaped?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Well, oh, I've forgotten his name, "+pchar.GenQuest.Hold_GenQuest.CapName+", right?";
			link.l1 = "Damn it! Where were you looking?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "He got out of the cargo hold and jumped over the bulwark. We didn't shoot him to avoid any noise, and while we were preparing a longboat, he was saved by those bloody fishermen.";
			link.l1 = "And why do I pay you! Flog the head of the watch and deprive him of rum for a week. Stand to! We are weighing anchor...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Greetings, captain. There were no accidents during your...";
			link.l1 = "Fine, fine, I get it.... There is a prisoner in our cargo hold. His name is "+pchar.GenQuest.Hold_GenQuest.CapName+". Take a few men and escort him to the port. He is free now.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "Is he really free? Are we to deliver him on a longboat?";
			link.l1 = "No, on a fucking turtle... I thought I was clear enough. And hurry up! We need to weigh anchor by the start of the ebb.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Captain, there isn't a soul aboard the ship! Something is very wrong here... Tommy said he saw a cat in the cockpit, and it was the only living creature...";
			Link.l1 = "Idiot, cats don't have souls. It looks like he hasn't visited a church for a long time already, or perhaps he's never been there at all. Have you been to the captain's cabin? I need the logbook.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "No, they do have souls. There was no logbook and not a single navigational instrument. Not even a single longboat...";
			Link.l1 = "They don't. Was it driven off by a storm?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "They do, Cap. Cats have souls. Captain, the longboat was cut away and we have found a sword on the floor of the cockpit. It is rusty and bloody. Here, take a look...";
			Link.l1 = "Stop giving me this crap, throw it away, and stop talking about cats, damn it! Let's check the hold and leave... Oh, something is very wrong here and I don't bloody like it...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "Captain, I've got a bad feeling about this place... Perhaps it's time for us to leave?";
					Link.l1 = "Yes... Go to the ship's boat.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Captain, I will not stay on this strange ship if you intend to take it to port. I'd sooner throw myself into the sea.";
					Link.l1 = "I am not willing to do that... I am also a little frightened...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Perhaps we should sink it, Captain?";
					Link.l1 = "To let the souls of the dead sailors who dwell here visit us in our nightmares?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Good God, no! Captain... why are you saying that?";
			Link.l1 = "Don't go pale, I was joking... Go to the ship's boat. And I suppose you are right after all, perhaps cats really do have souls...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Talk to the boss. I've got nothing to say to you.","I am at my post. All questions should be directed to the commandant of the fort.");
			Link.l1 = "Fine.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("I am really busy right now. Leave me alone.","Don't distract me from my work. There is nothing to talk about.");
			Link.l1 = "Pity...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Morgan wanted to tell you 'a thing or two'... He is somewhere here, on the deck.","Heh, find Morgan. Bad news is waiting for you...");
			Link.l1 = "Fine.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
