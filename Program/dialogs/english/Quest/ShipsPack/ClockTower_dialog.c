int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
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
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "Hold it, mynheer captain. No passage beyond this point.";
			link.l1 = "Why not?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "See that tower? Dutch West India Company office. Ship registry department and archive. Entry by appointment only.";
			link.l1 = "And how does one get an appointment?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "Those who need to know, know. The mynheer director doesn't work with just anyone.";
			link.l1 = "'Mynheer director'? Who's that?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "Director van Doorn. Maybe he's not exactly a director, but that's what everyone calls him. Been working here ten years — brought order to everything. Now every ship in the Caribbean goes through his office.";
			link.l1 = "Every ship? Even warships?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "Only the finest ships and the wealthiest captains. Being a client of our office is a great honor!";
			link.l1 = "What kind of services do you provide?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "I'm not privy to the details — I just guard the entrance. But I hear people leave satisfied.";
			link.l1 = "Impressive.";
			link.l1.go = "ClockTower_Johan_7";
		break;
		
		case "ClockTower_Johan_7":
			dialog.text = "And I'll tell you something else. See that clock? A European marvel — you won't find anything like it in our backwater. The mynheer director personally maintains it.";
			link.l1 = "Perhaps we could come to an arrangement?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "Surely there's something I can do to get inside?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "I don't take bribes!";
			link.l1 = "My apologies. You're a good man. What's your name?";
			link.l1.go = "ClockTower_Johan_9";
		break;
		
		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"... Look... I understand you're not from around here. But we have order here. The mynheer director always says: show weakness once, and our tower comes crashing down. Want to get inside? Help the city — and you'll be noticed.";
			link.l1 = "I see. Stay sharp, soldier.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "Well, I don't know. The mynheer director rewards friends of Willemstad. Help the city — and you'll be noticed. I understand you're not from around here. But we have order here. The mynheer director always says: show weakness once, and our tower comes crashing down.";
			link.l1 = "I see. And what's your name?";
			link.l1.go = "ClockTower_Johan_10";
		break;
		
		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar, true)+".";
			link.l1 = "And I'm "+GetTitle(NPChar, false)+" "+GetFullName(pchar)+". Stay sharp, soldier.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "Has something happened?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+". Я могу вам чем-нибудь помочь?";
				link.l1 = "No, "+npchar.name+". Carry on.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "Has something happened?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "Congratulations. You have an appointment scheduled.";
			link.l1 = "An appointment? With whom?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "With the mynheer director's deputy. He heard about your help to the city and ordered me to invite you.";
			link.l1 = "What about the director himself?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "Uh... I'm not authorized to tell you anything about that. Good luck in there, "+GetTitle(NPChar, true)+".";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "Welcome to the DWIC ship registry department. Captain...?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+",\n" +
							"Maarten Visser, deputy director.\n" +
							"I hear you've been quite helpful to Willemstad. Perhaps our office can be of service to you as well.";
			link.l1 = "That's why I'm here.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "I'm glad I could be of service to the capital of Curaçao.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "Any captain — French, Spanish, Dutch — can commission a ship audit from us. We inspect the rigging, cannons, tackle. Find weak points, provide recommendations";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "Any captain — French, Spanish, Dutch — can commission a ship audit from us. We inspect the rigging, cannons, tackle. Find weak points, provide recommendations";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "And if one audit isn't enough, we can also procure new ship documents. In other words, our office's work will improve your vessel — without spending precious mahogany and silk.";
			link.l1 = "How is that possible?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = "Captain, you have no idea how powerful a place you've entered, and how much a simple stroke of the pen can accomplish.";
			link.l1 = "For doubloons, I presume?";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "Naturally. Our services aren't cheap and depend on the size of your ship. But they always pay for themselves. A captain who's been through our doors rarely fails\n" +
						"However, we don't just take your gold — we also give you opportunities to earn it. Pirates have multiplied so much that even in the Lesser Antilles, captains must outfit squadrons to drive off these pests. Bring proof of elimination — and you'll receive payment in those same doubloons.";
			link.l1 = "What kind of proof?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "Ship's logs. Even that rabble must keep some semblance of documentation — otherwise you can't properly command even a lugger. Besides being absolute proof of villainy, logs always find a place in our archives. Useful for insurance disputes\n" +
						"If you're interested in our services, a spot has opened in our client roster — one of our captains recently concluded his partnership. Complete the work — and the spot is yours.";
			link.l1 = "Why the complications? Aren't my doubloons enough?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+", we operate on quality, not quantity. Every client of our office receives the finest service and the personal attention of the mynheer director himself. And the latter, believe me, costs considerable money even for our far from impoverished company. Since there are only thirty days in a month, we can only afford thirty clients.";
			link.l1 = "What needs to be done?";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "Bring five pirate ship's logs — that will prove your effectiveness. The reward depends on how dangerous their owners were.";
			link.l1 = "Very well. I'll do it.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "I need to think about it.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "Where's the director himself?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "Excellent. I await results and look forward to our partnership.";
			link.l1 = Goodbye(true) + ".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "As you wish. The offer stands. But your spot might be taken faster than you think.";
			link.l1 = Goodbye(true) + ".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "At sea. Mynheer van Doorn combines managing the office with commanding the flagship.";
			link.l1 = "How does he manage that?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "He works eighteen hours a day. Sleeps here, in the office upstairs. Says sleep is a waste of time. Four hours is enough for him.";
			link.l1 = "What about the racket from those massive clock mechanisms? How can anyone sleep here at all?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "You'll be able to ask him yourself and perhaps learn something. He's always happy to speak with clients. Do we understand each other?";
			link.l1 = "Perfectly.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "Not quite...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "Good day to you, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;
		
		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Do you have the logs with you?";
			link.l1 = "I see you're well informed, "+npchar.name+".";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "Ha! This isn't the pier or the city gates, and I'm not just some guard on duty, but a company employee.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Do you have the logs with you?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "I brought the logs. Will you let me through?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "Another time.";
			link.l2.go = "ClockTower_Johan_34";
		break;
		
		case "ClockTower_Johan_33":
			dialog.text = "Glad it worked out! Go ahead, they're expecting you.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;
		
		case "ClockTower_Johan_34":
			dialog.text = "Have a good day, mynheer captain, "+GetTitle(NPChar, true)+".";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "Captain! You're back. Did you bring the logs?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Yes. All five.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Another time.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
			// link.l1.go = "ClockTower_Visser_36";	
			
		break;

		case "ClockTower_Visser_22":
			dialog.text = "Excellent. Let me see them.\n"+
							"Yes, everything's in order. These are genuine pirate vessels. Quality work. You're owed " + SellJournals() + " doubloons\nPlease, take them. And sign here as well, please.";
			link.l1 = "So I'm on the roster?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromKPTotal("ClockTower_PirateJournal", 5);	// 
		break;

		case "ClockTower_Visser_23":
			dialog.text = "Almost. First we need to process the paperwork. It'll take a few minutes\n"+
							"Full name?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "Nationality?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "Your ship's name?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Type of vessel?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "Number of guns?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "Crew size?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "Good. Now sign here. And here. And here too.";
			link.l1 = "That's it?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "Almost. All that's left is to enter you in the registry. Of course, the mynheer director should meet you personally first... But it's a formality — I'm authorized to accept new clients\n"+
			"...But I'm getting sidetracked again. Now regarding repeatable services...\n"+
			"Insurance. Expensive, but no naval squadron will touch ships insured by the company. You'll be able to keep as many ships in port storage as you like without fear of losing them during a colony siege\n"+
			"Ship audit — slightly increases all characteristics without spending strategic goods. We'll inspect everything: rigging, hold, crew quarters. Provide recommendations. Price depends on ship size\n"+
			"Registration in our records. Increases vessel safety in the Caribbean region, so bounty hunters, pirates, and military will think twice before attacking you\n"+
			"Audit and registration can only be performed once for a specific ship. So if you've spent the money, take care of your vessel. You have no idea how much it irritates my superiors when captains treat their ships carelessly and change them like gloves!\n"+
			"But I'm getting sidetracked again. Now concerning repeatable services...\n"+
			"Document replacement. You know that ships can have different specializations. But you don't even suspect that it depends primarily on how the ship is documented. If you don't like that your warship is documented for fort sieges, you know who to turn to\n"+
			"Well, you've already heard about rewards for turning in pirate ship's logs... The more dangerous the pirate, the more we'll pay for his log.";
			link.l1 = "Impressive. I must say, mynheer Visser, your office truly...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "The Amsterdam's in the harbor! The mynheer director has returned!";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "What?! Already?! But he wasn't supposed to return for three more days!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "The mynheer director has already come ashore! He's heading straight here!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "Good Lord... If he sees you...";
			link.l1 = "What's the problem? You just said yourself you have authority to accept new clients.";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "I do! But he doesn't like it when... Never mind. Captain, wait outside. By the entrance. The mynheer director will want to speak with you.";
			link.l1 = "With me?";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "He personally vets every new client. Always. Go, quickly!";
			link.l1 = "I'm not giving back the doubloons for the logs!";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "Shame, I'd have stayed to listen.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;

		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;

		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "What was that, Johan?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "The mynheer director has returned.";
			link.l1 = "What's so terrible about that?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "Nothing terrible! It's just... The mynheer director doesn't like surprises. Everything must go according to plan. And here's a new client he hasn't vetted yet.";
			link.l1 = "Maarten said he had the authority to enter me in the registry.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "No, that's not the point. The mynheer director simply... well, he wants to control everything himself. Every little detail. Says otherwise everything will fall apart. You'll see, now he'll start worrying about his clock again.";
			link.l1 = "What?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "Mynheer van Doorn, when he gets irritated, stops the clock and starts tinkering with it. Sometimes the city goes without time for half a day. And it happens...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "Oh... Hear that? It's started.";
			link.l1 = "The boss is back. Business as usual.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "I can hear it alright. They're tearing Maarten a new one.";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "Unfortunately, it's become usual.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "That's harsh of you. It's not fair, if you ask me.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "Seems to have quieted down. They'll invite you in soon.";
			link.l1 = "Am I in trouble?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "Don't worry. You didn't do anything wrong.";
			link.l1 = "That's reassuring.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "Come on now! The mynheer director can be overly strict sometimes... But he's generous and polite... Oh, see?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "Ah, I told you!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "The mynheer director is waiting for you inside.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Your ship — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" guns and "+GetMaxCrewQuantity(pchar)+" crew.";
			link.l1 = "All correct.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "It's unfair that I know everything about you, while you know nothing about me except Johan's gossip. Hendrik van Doorn. Director of the Dutch West India Company's registry department in the Caribbean. Commander of the frigate Amsterdam. "+shipType+". "+GetCannonQuantity(npchar)+" guns and "+GetMaxCrewQuantity(npchar)+" crew.";
			link.l1 = "Pleased to meet you.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "You obtained five pirate ship's logs. My deputy held you in high regard, entered you in the client registry, and familiarized you with my office's services\n"+
						"But the final decision on admission is always mine. Personally. After an interview. Maarten could propose a candidate — nothing more.";
			link.l1 = "Let's begin.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "I need captains who effectively combat pirates while being commercially successful enough to afford our services. Do you meet these criteria?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "I destroyed Mortimer Grimm. Captain of the brig Memento.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "I think your company highly valued my victory over Albert Blackwood. The snow Lady Beth was a formidable opponent.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida wasn't a pirate, but...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "I defeated the terror of all who sail. You must know.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "You just entered my ship in the registry. Do you think an incompetent captain could maintain it?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "I'm managing just fine, and money grows on trees in the Caribbean.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Mynheer Visser has already verified my competence. Isn't your own deputy's assessment sufficient?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "Grimm? Our organization never had any complaints about Grimm, quite the opposite. But the one who took his place... I know who he was and what purpose originally brought him to the Caribbean. Such villainy has no statute of limitations, and I'm glad you punished the criminal and true enemy of my country.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "If I recall the report on the Cayman incident correctly, you didn't have a chance to verify that claim. In my opinion, the situation isn't entirely clear-cut, but your victory was undoubtedly competent.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "But could have become something far worse, yes indeed. A worthy enemy, although he lost not to you but to his ungrateful superiors. I'm Dutch, so I know what I'm talking about when it comes to war with Castile.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("Flying Heart")+"'. I'm still amazed that honest folk don't scatter at the sight of that monstrosity entering port. Much about this story surprises me, captain. But one day it will find its place in our books and lose all its mystique. As for you... you've immortalized yourself.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "You'd be surprised. But in your case, there's no room for doubt, that's true.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "And therefore worth nothing. Unless they're doubloons, of course.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\nYou're approved for the office's services. Welcome to the esteemed Dutch West India Company's Naval Registry.";
			link.l1 = "Thank you.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "This is a mutually beneficial cooperation. You gain access to the finest services in the Caribbean. We gain a reliable partner.";
			link.l1 = "Good.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "Wait! Do you hear that?";
			link.l1 = "I don't hear anything.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "Exactly the point! All it took was leaving for a week...";
			link.l1 = "Something wrong?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "With the clock. Need to check the mechanism. My apologies. This... is important.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "Seems fine now. My apologies again. Do you have questions?";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "More questions?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "Your deputy explained the office's services in detail. How is any of this even possible?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "How do you combine two positions? Captain and director?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "How do you work in such conditions? The racket from the clock mechanisms, the darkness, and the windows covered with heavy curtains.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "No, thank you for your time. What about the office's services?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "There's no sorcery here, captain. Pen and ink rule the world. The Church records a person's birth, baptism, marriage, and death. Change even one line — and their fate changes. A ship is slightly more complex, but even in its case a stroke of the pen changes much. I won't hide it, I'm proud of what I've achieved. And yet I still know it could be better. What if we entered not just ships and people in the ledgers, but an entire world?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "Because someone must. The previous captain of the Amsterdam died in battle against a group from Antigua. The company found no worthy replacement. I offered myself. Underwent training. Passed exams. Obtained a commission\n"+
			"Yes, I'm a poor captain. Far worse than you — that's certain. But a good manager can lead anything, not just a ship. It's hard to learn to command three people. Once you master that, you can command three thousand. Office, ship, town, or even a huge company — there's no limit, as long as you find talented people and trust them to substitute for you... That last part is the hardest. True curse.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "And there's barely any air to breathe. Captain, a person forms their own environment. Here nothing and nobody distracts me, everything's within reach and subjected only to me and time. If I could, I'd communicate with the outside world exclusively via paper. Unfortunately, that's impossible. Don't take it personally, captain. Better to be alone, but not lonely. If you understand what I mean.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "We only see clients by appointment. You're scheduled for... "+pchar.quest.ClockTower.date+" "+month+". If you don't come on the appointed day, no matter. Contact Johan, and he'll inform you of the next available appointment.";
			link.l1 = "Why such complications?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Our work is expensive because we perform true miracles and bring great benefit to our clients. Conflicts of interest are impossible, and thus we allocate an entire working day to serve a particular individual. Your next available date: "+pchar.quest.ClockTower.date+" "+month+"\n"+
			"If you see Visser... Maarten acted correctly in proposing your candidacy. Please convey that message. He's a good deputy. May he not doubt it.";
			link.l1 = "Good.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "Good day, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "How did it go?";
			link.l1 = "It was a long day, but van Doorn confirmed your decision.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "Thank God. So I did everything right.";
			link.l1 = "He told me to tell you that you're a good deputy.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "Really? He... said that?";
			link.l1 = "Aye. He did say that.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "Damn. He shouldn't have said that. Now I'll feel like an ungrateful bastard. Or maybe he foresaw this and planned everything?";
			link.l1 = "Mynheer deputy, you've suddenly stopped being yourself.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Captain, I'm a businessman, and so are you, so let's cut to the chase.\n"+
						 "The mynheer director hasn't been working for us for a long time.";
			link.l1 = "What, pardon?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "He came here under contract with one goal — to set up the ship registry department. He succeeded brilliantly, trained his successor, promoted me... and that's it.";
			link.l1 = "What, that's it?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "His contract ended long ago. We don't know exactly when, but we're completely certain this man no longer has the right to hold his position.";
			link.l1 = "I see. Fat cats in the central wing of this building get all nervous.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "I see. You're tired of waiting for him to vacate his chair for you.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "Exactly! And they can't do anything about it!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "I'll be frank. I'm really tired. Damn it, van Doorn promoted me specifically so I could replace him when the contract expires!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "Still, I would never shake this damned chair beneath him just because I feel deceived! God knows, I'm grateful and admire this man!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "No, mynheer. Van Doorn wants to drive out our mutual superiors. The very ones sitting behind the tower wall — in the central wing of this very building! But even they can't find a way to control him!";
			link.l1 = "What's so difficult about that? Van Doorn is hardly more important than Stuyvesant.";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "This isn't a ship or a royal court, captain. Our company is a completely new type of organization. You can't just point a finger and dismiss such a valuable person.\n"+
						 "First, no one knows where the original of van Doorn's contract is. Ergo, there are no grounds for dismissal. If we tried, he'd send a pack of lawyers, and we'd end up owing him.\n"+
						 "Second, management made a mistake when they gave van Doorn commission for the Amsterdam. He may be a weak captain, but he assembled a crew — the best in the entire region. Give the order — and the Company's elite soldiers will occupy this building without blinking.\n"+
						 "Third, his wife absolutely adores him. Never mind that he hasn't seen her in several years. De Witt's own daughter is capable of much for her beloved husband. And the Council of Seventeen is forced to accept it.\n"+
						 "You witnessed today's outburst, captain. I'll reveal a secret: this happens more and more often. The directors fear that one day he'll throw them out. And they won't be able to do anything, because the Amsterdam's in the harbor, van Doorn has a valuable client in his office, and at home — support from his father-in-law, Grand Pensionary of the Republic of the Seven United Provinces!\n"+
						 "In other words, the directorate will pay very generously for your help. And preserve your privileges at the ship registry office.";
			link.l1 = "Impressive. You truly are a businessman, Maarten. You're selling me betrayal with the same professionalism you recently used to sell your office's services.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "It's not difficult when van Doorn himself taught you the art of negotiation and you genuinely believe what you're saying.";
			link.l1 = "So what do you want from me?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "Something only an outsider can do. Break into the office at night and find van Doorn's original contract there. I'll make sure the doors are unlocked.";
			link.l1 = "Why won't you do it yourself? And what's stopping me from going right now to tell your superior everything?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "Because van Doorn has a habit of receiving anyone at night except company employees. No one will be surprised to see you leaving this tower at an irregular hour.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "As for your threat... You won't get to the director now, you have a different day scheduled. "+pchar.quest.ClockTower.date+" "+month+", correct? By then the urgency of the news will have diminished somewhat. And besides, the director never rewards informants. And always protects his employees.";
			link.l1 = "Convenient for you.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "This isn't betrayal, captain. We simply want to uphold the contract and safeguard the company. And Willemstad, which you've helped so much, by the way.";
			link.l1 = "I'll think about it. But I promise nothing.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "I ask no more from you, captain. Above all, you're our client. However it turns out, I'm very proud that I was the one who found you and entered you in the office's registry.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "You can always find me in the central wing. Good day.";
			link.l1 = "Until we meet again.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "Hello, "+GetTitle(NPChar, false)+". Any news?";
			link.l1 = "Nothing yet.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", today's your day. Please, go ahead.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "Good day, "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", you're expected on another day. We'll be glad to see you: "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "Good day, "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "Thank you, Johan.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", you're rather late. The office is closed.";
					link.l1 = "Hello, "+npchar.name+". I heard it operates even at night.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "That's true. All sorts of people come by. Even priests sometimes visit, heh-heh. But they all must go through me first. And I've received no instructions regarding you.";
			link.l1 = "Wait, you stand guard here round the clock? How is that possible?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "Yeah. The mynheer director just ordered it. How he manages it, I don't know, but I still have enough time for both rest and duty. And they raised my pay — can't complain!";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "Something else?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "You should let me through. I work for the company's senior management.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(Kill him)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "Carry on, soldier.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;
		
		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;
		
		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;
		
		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "Uh. What do you want from me, mynheer captain? I'm just a simple soldier, I don't know anything.";
				link.l1 = "You do know everything, Johan. Don't be so modest. The gentlemen in the high offices may not report to you, but you've certainly heard about the bad blood between them.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "I'm a small man, but I won't go over my direct superior's head. My apologies, "+GetTitle(NPChar, true)+".";
				link.l1 = "We'll return to this conversation.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;
		
		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "That's true, "+GetTitle(NPChar, true)+". The mynheer director has overstayed. A storm is brewing.";
			link.l1 = "What have you heard exactly?";
			link.l1.go = "ClockTower_Johan_56";
		break;
		
		case "ClockTower_Johan_56":
			dialog.text = "Everyone fears that if not today, then tomorrow he'll seize power. He's too big a man for our backwater. He's strangling everyone with his inspections, pushes every signature to go through him\nI'll tell you honestly, and you saw it yourself: every time the Amsterdam enters port — bad tension immediately rises.";
			link.l1 = "I can resolve this, but for that you must let me through.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "Go ahead, "+GetTitle(NPChar, true)+". Only I beg you, don't ruin me: if the mynheer director finds out, I'll lose my head, and I've got a family to feed.";
			link.l1 = "I'll do my best.";
			// if (sti(pchar.reputation.nobility) >= 71) link.l1.go = "ClockTower_Johan_58_hint";
			// else link.l1.go = "ClockTower_Johan_NightSuccess";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "You're a good man, "+GetTitle(NPChar, true)+". Perhaps I can help you: I know that in one of the books the mynheer director keeps a key. What it's for — I don't know, but perhaps it'll be useful.";
			link.l1 = "Thank you, Johan.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
			// if (sti(pchar.reputation.nobility) >= 71) Notification_Reputation(true, 71, "low");
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "Halt. You're on Dutch West India Company property. Naval registry department and archive. Entry by appointment only.";
			link.l1 = "I'm "+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "You have an appointment? Go ahead.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Your appointment is scheduled for another day: "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "Hello, "+GetTitle(NPChar, false)+". Any news?";
			link.l1 = "Yes. Here's the contract.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "Incredible... It expired seven years ago!";
			link.l1 = "So this is what you needed?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "Exactly! With this document the company can recall him legally. No loopholes. No excuses. Time's up — period.";
			link.l1 = "What next?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "I'll send the contract to Amsterdam. The Council of Seventeen will make a decision. Doorn will be ordered to return. He won't be able to refuse.";
			link.l1 = "What if he does refuse?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "He can't. His wife may be the daughter of a shareholder, the Grand Pensionary, but even her father won't go against the Council. And Catharina herself... She's been waiting ten years. If she finds out he can return but refuses — it will kill her.";
			link.l1 = "Cruel.";
			link.l1.go = "ClockTower_Visser_76";
		break;
		
		case "ClockTower_Visser_76":
			dialog.text = "Yes. But it's the only way. Thank you, captain. You've done important work.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;
		
		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "Your reward — five hundred doubloons. And I give you my word: in two to three months, when I take the director's chair, you'll be granted unlimited access to the office's services. No queues. No appointments. Any time.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "And you killed Johan. I've already betrayed a man I admire and owe everything to. Now this too\n"+
				"Perhaps on your ship people are like kindling, but the company values its employees. And I'm disgusted to be complicit in murder\n"+
				"Your doubloons will go to Johan's family, but I'll fulfill the second part of the deal\n"+
				"I give you my word: in two to three months, when I take the director's chair, you'll be granted unlimited access to the office's services.";
			}
			link.l1 = "I'm counting on your word. Good day.";
			link.l1.go = "ClockTower_Visser_78";
		break;
		
		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;
		
		case "ClockTower_Visser_79":
			dialog.text = "Hello, "+GetTitle(NPChar, false)+". No news yet. Don't worry, I remember our agreement.";
			link.l1 = "I hope so.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;
		
		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"! Come in, come in. Glad to see you.";
			link.l1 = "Congratulations on your appointment.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "Thank you. The Council of Seventeen made their decision faster than I expected. The contract proved sufficient evidence. Mynheer van Doorn was removed from managing the office.";
			link.l1 = "How did he take it?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "He knows how to lose. Just gathered his personal belongings from the office and left. Though did he really lose?\n"+
			"They kept his command of the Amsterdam. On that count, the company certainly made a mistake. They shouldn't have given him that ship back then.\n"+
			"We underestimated him. I hope things don't turn out worse in the end\n"+
			"And that's not all.";
			link.l1 = "How could it be worse?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "Mynheer van Doorn knows who retrieved the contract from his office.";
			link.l1 = "How?!";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "Don't look at me like that! I didn't tell him anything. He figured it out himself.";
			link.l1 = "What now?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "Now he considers you an enemy. But as long as you pose no threat to the Republic of the Seven United Provinces — he won't touch you\n"+
			"Van Doorn always knew how to separate personal from professional. The question is, can you?";
			link.l1 = "What if I can't?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "Then he'll find you. And do his job. Don't give him a reason.";
			link.l1 = "I'll try.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "Good day to you, "+GetTitle(NPChar, false)+". Feel free to use the services of our... my office at any time.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", you're expected. Mynheer Visser ordered all clients be allowed in freely. Says the old rules were too strict.";
			link.l1 = "Thank you, Johan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "Go ahead during any business hours. Appointments have been abolished.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "Do you have a minute?";
			link.l1 = "For you — always.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "Ah, if only, my captain. You have other passions in life. Right now, for instance, your handsome head is occupied by someone other than me, correct?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "That's what I thought. I know my man well. And a sailor's excitement — I'm even more familiar with that. So tell me straight, darling\n"+
			"What will it cost us to capture the flagship of the esteemed Dutch West India Trading Company?";
			link.l1 = "For van Doorn to come for us himself, I'll have to become an enemy of Willemstad.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "Oh, my captain... So that's how it will be. Not the first time, is it?";
			link.l1 = "As if you don't approve.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "I fell in love with you as you are. And I'll always be on your side. Just remember the burden of responsibility that we... that is, you bear before your people.";
			link.l1 = "Though that's what we have our Alonso for. He'll remind you.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "As soon as we set sail, my captain.";
			link.l1 = "Let's not delay then, love.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "Charles? I want to ask something.";
			link.l1 = "Of course, Mary. What's happened?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "I... I'm worried about you, alright. I know that look. You're thinking about something bad.";
			link.l1 = "Nonsense. I don't even remember what I was just thinking about. How would you know?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "I just know! I saw that Amsterdam, alright. Beautiful ship. Very beautiful. But\n"+
			"You've already decided everything... Like before, alright?";
			link.l1 = "Van Doorn will come for us himself, but for that I'll have to become an enemy of Willemstad.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "Is it worth it, Charles?";
			link.l1 = "I don't know, Mary.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "I want you to be happy, alright. But still I'll ask Alonso to try and talk you out of this, alright!";
			link.l1 = "That sounds like him. Let's go, love.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Cap, we need to talk.";
			link.l1 = "I'm listening.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "Not now, Alonso.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "Here's the thing, cap, but you'll have to hear me out. It's, uh, what's the word\n"+
			"An urgent matter — that's it!\n"+
			"So, a little bird told me you personally kicked one of the company's directors from his cushy seat, and he's nursing a grudge and now hunting us in his fine frigate.";
			link.l1 = "That's a gross exaggeration.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "You know how people love to wag their tongues, cap. Let a rumor brew for a week — and you'll hear that van Doorn was seduced by a planter's daughter, that the Amsterdam has a crew of living dead, and treasure from Cortés himself in the hold\n"+
			"But I'm more interested in the real state of affairs. So, cap, will there be a fight or not?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;
		
		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;
		
		case "ClockTower_Alonso_4_2":
			dialog.text = "Which, by the way, would be bloody fun, I won't argue! Dutch flagship! Ha! I can picture those cheese-eaters' faces when we...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;
		
		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;
		
		case "ClockTower_Alonso_4_4":
			dialog.text = "Tommy, shut up.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;
		
		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "If there's to be a fight, it won't be soon. Van Doorn won't seek revenge, he's not that kind of man. First we'll have to seriously anger the Dutch.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "ClockTower_Alonso_4_6":
			dialog.text = "Thanks, cap, that'll reassure the crew.";
			link.l1 = "And you?";
			link.l1.go = "ClockTower_Alonso_5";
		break;
		
		case "ClockTower_Alonso_5":
			dialog.text = "My concern is protecting the crew. From themselves and... from you, if I can. You'll do what you've planned anyway.";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "Carry on, Alonso.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;
		
		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;
		
		case "ClockTower_Alonso_6":
			dialog.text = "Stubborn as a Spanish mule!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;
		
		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;
		
		case "ClockTower_Alonso_7":
			dialog.text = "Lord, why me.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;
		
		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "You're overcomplicating everything! Cap wants a pretty ship — we'll get him a pretty ship! We're one crew!";
			link.l1 = "Carry on, Alonso. Tommy, get out.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Your ship — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" guns and "+GetMaxCrewQuantity(pchar)+" crew.";
			link.l1 = "You're as precise as ever, mynheer director.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "That title no longer belongs to me — thanks to your efforts. But don't even think I attacked you out of petty revenge. I was doing my job.\n"+
			"And obviously failed at it. Nor could I have succeeded: I told you once that you're a far better captain than I am.";
			link.l1 = "You took on this burden yourself! Your contract expired seven years ago. What stopped you from simply going home?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "What stops you from doing the same? You know the answer, captain. You have a dream. You have no other life. And if you let go of control — everything collapses.\n"+
			"I could have brought order to this region. Stopped the endless cycle of violence. If I hadn't loosened my grip. If I'd crushed my fear and done what I should have done long ago.\n"+
			"But enough pathos. I'm as poor a fighter as I am a captain, but I know how to choose my men. You made yourself my final task, captain. Today the office's registry will have two captains less!";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "You were saying something about fear. So read this letter."; // Доступно, если игрок принёс письмо
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "Just one. To battle!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "From Catharina?! How dare you mix personal with business?!";
			link.l1 = "As you see, the letter is still sealed. I'm waiting.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...she can't wait anymore... will go to another... if I don't return?!";
			link.l1 = "You've already lost the office. Your crew is dying right now. Are you ready to lose your family as well?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "Not like this. Captain, do you accept my surrender?";
			link.l1 = "Aye. Get the hell off my ship."; // Отпускает, повышает честь
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "No. That was the last courtesy for the condemned. To battle!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "Then congratulations on your victory, Captain "+GetFullName(pchar)+". Today the registry will have only one captain less.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE); // нужно два раза, чтобы сработало...
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+". I didn't expect you'd dare come here.";
			link.l1 = "Why not? I'm still your client, and I need the office's services.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "Services? SERVICES?! After what you've done? You're an enemy of the esteemed Dutch West India Company! Another captain will take your client spot!";
			link.l1 = "Unlikely. Look what I found in van Doorn's papers.";
			link.l1.go = "ClockTower_Visser_103";
		break;
		
		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "Your predecessor considered it beneath his dignity to use this document — even when his chair began to wobble.";
			link.l1.go = "ClockTower_Visser_104";
			// отдаём Ключ к Маартену Виссеру
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;
		
		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "You're lucky you had such a superior. For such shenanigans you'd face trial — at best.";
			link.l1.go = "ClockTower_Visser_105";
		break;
		
		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "You're a businessman. You know where I'm going with this.";
			link.l1.go = "ClockTower_Visser_106";
		break;
		
		case "ClockTower_Visser_106":
			dialog.text = "You... Your place in the registry is restored.";
			link.l1 = "Ah, Maarten. You wanted to take the director's place, though he gave you everything. He saved you from trial and didn't even think it necessary to inform you.";
			link.l1.go = "ClockTower_Visser_107";
		break;
		
		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "This little sin will never let you rise higher and will leave you living in constant fear.";
			link.l1.go = "ClockTower_Visser_108";
		break;
		
		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "Now it's your turn to be chained to this place. But you certainly won't have a deputy like van Doorn had.";
			link.l1.go = "ClockTower_Visser_109";
		break;
		
		case "ClockTower_Visser_109":
			dialog.text = "Enough. Do you want to finish me off completely?!";
			link.l1 = "Not quite. I want you to enter my new ship in the registry. I don't want any misunderstandings.";
			link.l1.go = "ClockTower_Visser_110";
		break;
		
		case "ClockTower_Visser_110":
			dialog.text = "Your ship is the '"+GetShipName("Amsterdam")+"'. DWIC flagship. It can't just be... re-registered.";
			link.l1 = "Why not? Paper endures everything. Isn't that how your system works?";
			link.l1.go = "ClockTower_Visser_111";
		break;
		
		case "ClockTower_Visser_111":
			dialog.text = "Good Lord, but everything has limits!";
			link.l1 = "I believe in the power of this place. You should too.";
			link.l1.go = "ClockTower_Visser_112";
		break;
		
		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;
		
		case "ClockTower_Visser_113":
			dialog.text = "Full name?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;
		
		case "ClockTower_Visser_114":
			dialog.text = "Подданство?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "Your ship's name?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Type of vessel?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "Number of guns?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "Crew size?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "Good. Now sign here. And here. And here too.";
			link.l1 = "That's it?";
			link.l1.go = "ClockTower_Visser_120";
		break;
		
		case "ClockTower_Visser_120":
			dialog.text = "That's it.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;
		
		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "You forgot to say something.";
			link.l1.go = "ClockTower_Visser_122";
		break;
		
		case "ClockTower_Visser_122":
			dialog.text = "\n"+
			"Welcome to the esteemed Dutch West India Company's Naval Registry.";
			link.l1 = "Until we meet again, mynheer director.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+". How may my office and I help you today?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "Glad to see you, "+GetTitle(NPChar, false)+"! Always at your service. What interests you today?";
				}
				else
				{
					dialog.text = "Well? What interests you today?";
				}
			}
			link.l1 = "Will you conduct an audit of my vessel? I want to improve its characteristics.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "I'm not satisfied with my ship's specialization. Will you procure new documents?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "Will you enter my ship in the company registry? Let pirates and hunters think twice.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "I want to insure my ships in port storage. Current and future ones.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "You accept pirate captains' ship logs, don't you?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "Perhaps not today. Good day.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// --> Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "The cost depends on the ship's size. Which vessel are we talking about?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}
 
			if (n == 0)
			{
				dialog.text = "Unfortunately, audit is a one-time service for each individual ship. Anything else?";
				link.l1 = "Let's do it another time.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "Let's see... This will cost " + n + " doubloons.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proceed.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "Though... let's do it another time.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "I’m afraid I must refuse. According to the registry, your ship went to the sea devil many years ago, and such a ghost of time cannot be undone by a stroke of the pen. Before we can cooperate, you will need to restore it. They say there is a master on Isla Tesoro who would take on such work.";
				link.l1 = "Okay, thanks.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Корабль уже улучшен";
				link.l1 = "Thank you.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "Done.";
			link.l1 = "Thank you.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Аудит

		// --> Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "The cost depends on the ship's size. Which vessel are we talking about?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Unfortunately, registry entry is a one-time service for each individual ship. Anything else?";
				link.l1 = "Let's do it another time.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "Let's see... This will cost " + n + " doubloons.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proceed.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "Though... let's do it another time.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "I’m afraid I must refuse. According to the registry, your ship went to the sea devil many years ago, and such a ghost of time cannot be undone by a stroke of the pen. Before we can cooperate, you will need to restore it. They say there is a master on Isla Tesoro who would take on such work.";
				link.l1 = "Okay, thanks.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Корабль уже улучшен";
				link.l1 = "Thank you.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "Done.";
			link.l1 = "Thank you.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Улучшение специализации

		// --> Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "The cost depends on the ship's size. Which vessel are we talking about?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Hm. I don't see any of your ships in port.";
				link.l1 = "Let's do it another time.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "Let's see... This will cost " + n + " doubloons.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proceed.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "Though... let's do it another time.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "Unfortunately, this is not possible. Your ship is a unique piece, steeped in legends. The stroke of a pen is powerless in such cases.";
				link.l1 = "Okay, thanks.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "What kind of specialization are you talking about? Your ship is universal, it has no distinctive features.";
				link.l1 = "Nice to know, thanks.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			// тут можно обработать другие причины отказа, но на данный момент таковых не будет
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;
		// <-- Смена трейта корабля

		// --> Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "Let's see... This will cost " + n + " doubloons.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "Proceed.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "Though... let's do it another time.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "Done.";
			link.l1 = "Thank you.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;
		// <-- Страховка
		
		// Награда за пиратов (раз в сутки) -->
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "Absolutely correct. The reward depends on the number of logs and the relative danger of their owners.\n" + 
						  "How many logs have you brought?"
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;
		
		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "The company thanks you for your work. You're owed " + JournalsCost() + " doubloons. Please, receive them and sign here"
			link.l1 = "Thank you.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;
		// <-- Награда за пиратов

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "I don't see your ship in port.";
	link.l1 = "Let's do it another time.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
