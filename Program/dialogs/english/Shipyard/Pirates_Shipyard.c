// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Phew... What a dreadful climate... My name is "+GetFullName(npchar)+", and may God damn me if I'm not the best shipwright in these God-forsaken islands. But this humidity is just knocking me down...";
				Link.l1 = pcharrepphrase("A thousand sharks, just what I needed—an old man's muttering. My name is "+GetFullName(pchar)+", I believe you've heard of me.","It's not the humidity, it's old age, sir. My name is "+GetFullName(pchar)+", I believe you've heard of me.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "Oh, you again, always going on about your problems... (coughing).";
				link.l1 = pcharrepphrase("You're right, it's me again. But let's talk business while you still haven't given your soul to God yet.","Your memory serves you well, and now, if you allow, let's get down to some more specific questions.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("I've grown tired of your muttering. Farewell.","It's time for me to go. Sorry to bother you");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "Aha, Captain "+GetFullName(pchar)+"! How nice that you've stopped by!";
				Link.l1 = "It looks like you need me for something, don't you? Usually you aren't quite as courteous.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "I see you've returned to me empty-handed, captain! What happened to the...guests?";
				Link.l1 = "They've gone. I asked them, and they have gone.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "Oh, you again, always going on about your problems... (coughing)";
			link.l1 = pcharrepphrase("You're right, it's me again. But let's talk business while you still haven't given your soul to God yet.","Your memory serves you well, and now, if you allow, let's get down to some more specific questions.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("I've grown tired of your muttering. Farewell.","It's time for me to go. Sorry to bother you.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "Young people these days... You never show any respect. Hot heads, hard hands, what do you want?";
			link.l1 = pcharrepphrase("That's right. But sooner or later, everything comes to an end, and it looks like your time is near...","Something tells me that during your younger years, you didn't necessarily have much respect for your elders either. Am I correct?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Don't argue with your elders, pup.";
			link.l1 = pcharrepphrase("Easy, now. Calm down. Don't overexert yourself, otherwise you might have a heart attack. I don't want to be accused of causing the death of the best shipwright in the Caribbean. Let's get down to business.","I forgive you for your rudeness, only out of respect for your age. And now, if you're finished, let's get down to business.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("All right, that's enough lecturing from me! Farewell!","I see we're not going to see eye to eye. Farewell.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(coughing)... People won't let an old man be. What do you want from me this time, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = pcharrepphrase("I need to use the services of the shipyard.","I want to use the services of the shipyard.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "I have a question.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "I'd like to talk about finances.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("Shit, I have a couple of urgent matters to attend to. Goodbye.","It's time for me to go. Sorry.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			dialog.Text = "Come on, what do you want? Don't bother an old man...";
			link.l2 = "I just want to use the shipyard's services.";
			link.l2.go = "shipyard";
			link.l3 = "I need weapons for the ship.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "I want to change the look of my sails.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_cabin"))
			{
					link.l50 = "My ship is quite... special. I'd like to make a few changes.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_cabin") && npchar.quest.FDM_cabin == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "I have more chests for the cabin's reconstruction.";
					link.l50.go = "FDM_cabin_pay";
			}
			// Xenon -->
			/*if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "I'm here about the ship's reconstruction.";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "I'm here about the ship's reconstruction.";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon*/
			link.l9 = pcharrepphrase("Shit, I have a couple of urgent matters to attend to, goodbye.","It's time for me to go. Sorry.");
			Link.l9.go = "ship_tunning_not_now";
		break;	
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you?"),"You tried to ask me a question a little while ago...","I have never met people with such curiosity in my shipyard or anywhere else in this town.","What's with all the questions? My job is to build ships. Let's take care of that.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","Hm, well...","Fine, let us...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Listen, I'd like to pass through, but that door is locked...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "I'd like to propose a deal.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "I'm here about the materials for the frigate.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Listen, "+npchar.name+", have you seen Miguel Dichoso on Isla Tesoro lately?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "State your terms.";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "True royal generosity! Of course I agree!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "No, I don't think so.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "That's right. If you want to pass through this door, you have to pay me 20,000 pesos. If you don't pay, I won't open it. This isn't a soup kitchen. And I don't advise you to go there anyway. It would be better for you if you didn't...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Here's your money. Open up.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "I don't have that much money.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "No way! I'd never pay for a door.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "Go in. The door is open. Don't worry about thanking me!";
			link.l1 = "No, why not. Thank you. "+npchar.name+"...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "Well, when you have it, come back. Otherwise, don't try to convince me. It's useless...";
			link.l1 = "Argh, I'm completely speechless!";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "Come on, don't be so strict with an old man... I really need your help, captain.";
			link.l1 = "Tell me, master. What happened to you?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "Our new leader of the Brethren of the Coast, "+sTotalTemp+", has ordered a new ship, a frigate. He also set quite difficult tasks: a reinforced hull, high speed and good manoeuvrability, plus cannons of the largest possible calibre\nI understand that the ship of an admiral—sorry, the leader of the brethren—must be something special, but that means I need special materials to build it. You must have heard of them. Ironwood, resin, ship silk and ropes...";
			link.l1 = "So tell this to the leader of the Brethren. Or are you wary that "+sTotalTemp+" will cut off your head for it?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "I told him... The thing is, our new leader has neither the time nor the opportunity to find and bring these materials. You have to know what a rarity they are. And there's no way I'll be able to build a frigate with the said characteristics without them.";
			link.l1 = "And I suppose you want me to find the materials for the ship?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "Well, yes. You are a good friend of our leader. "+sTotalTemp+" says himself that he owes you a great deal and insists that you deserve every respect... So I thought: since you're his friend, perhaps you wouldn't mind helping him? And at the same time, you do understand what an awkward position I'm in? All materials will be paid for, "+sTotalTemp+" isn't tight with his gold.";
			link.l1 = "I'm quite sorry, master, but I'm no less busy than "+sTotalTemp+". I'm afraid that collecting materials may take an eternity. So, you'd better ask someone else.";
			link.l1.go = "clock_exit";
			link.l2 = "Well, if "+sTotalTemp+" ordered a ship from you - then of course I'll try to help. We really are friends, and friends have to help each other. How many materials do you need?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "That's too bad. That's really too bad. I was counting on you. Well, as they say, no means no...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "I'm missing 100 units of ironwood, 150 containers of resin, 110 rolls of ship silk, and 90 coils of hemp rope. What do you think? Could you find all of that for me within four months? I don't think I have any more time.";
			link.l1 = "I can at least try. And as for the payment?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "Here are my rates: ironwood at 4000 pesos per piece, resins at 1400 pesos per container, silk at 2500 pesos per roll, and ropes at 1500 pesos per coil. And if you bring all of that to me, you'll receive a very nice gift from me.";
			link.l1 = "What is it, I wonder?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "Bring me the materials first. But I assure you: it'll come in handy for you, and the thing is unique. There isn't another in the Caribbean, or in the whole world as of yet. I hope that little spark of curiosity has ignited your interest in gathering the materials for me.";
			link.l1 = "Well, you're as slick as a leprechaun, master! All right, you've got yourself a deal.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "I'm very happy. I'll be looking forward to your return.";
			link.l1 = "I hope it won't take too long...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "Excellent! What have you brought me today?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Ironwood, in the amount of "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Resins, in the amount of "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Ship silk, in the amount of "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Hemp ropes, in the amount of "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "Nothing at the moment. I just wanted to make sure that we still have an agreement.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "Wonderful! I've got all the materials I need. Thanks a million for your help, captain. You've helped me out big time.";
				link.l1 = "Yes, any time, master. I'm quite pleased as well: I helped a friend out and made some good money. And now, let's get back to our conversation about your mysterious item that you promised me.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "Any more surprises for me, captain?";
				link.l1 = "Alas, that's all for now. Just keep waiting.";
				link.l1.go = "exit";
				link.l2 = "Yes, I've got one more thing...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "Fine, alright. I'm going to need "+FindRussianQtyString(amount)+" of ironwood. You've brought me "+FindRussianQtyString(iSan)+". . So, what you have left to bring me is "+FindRussianQtyString(iTemp)+". All right, at the rate of 4000 pesos per piece, your reward totals "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you! You'll have the rest soon.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "Fine, alright. I'll also need "+FindRussianQtyString(amount)+"  of ironwood. You've brought me "+FindRussianQtyString(iSan)+". So, we've taken care of the ironwood now! All right, at the rate of 4000 pesos per piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "Fine, alright. I'll also need "+FindRussianQtyString(amount)+" resins. You've brought me "+FindRussianQtyString(iOil)+". So, what's left for you to bring me is "+FindRussianQtyString(iTemp)+". All right, at the rate of 1400 pesos per container, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you! You'll have the rest soon.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "Fine, alright. I'll also need "+FindRussianQtyString(amount)+" resins. You've brought me "+FindRussianQtyString(iOil)+". So, we've taken care of the resins now! All right, at the rate of 1400 pesos per container, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "Fine, alright. I'll also need "+FindRussianQtyString(amount)+" silk. You've brought me "+FindRussianQtyString(iSil)+". So, what's left for you to bring me is "+FindRussianQtyString(iTemp)+". All right, at the rate of 2600 pesos per piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you! You'll have the rest soon.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "Fine, alright. I'll also need "+FindRussianQtyString(amount)+" silk. You've brought me "+FindRussianQtyString(iSil)+". So, we've taken care of the silk now! So, at the rate of 2600 pesos per piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "Fine, alright. I'll also need "+FindRussianQtyString(amount)+" ropes. You've brought me "+FindRussianQtyString(iRop)+". So, what you still need to bring me is "+FindRussianQtyString(iTemp)+". So, at the rate of 1500 pesos per piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you! You'll have the rest soon.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "Fine, alright. I'm going to need "+FindRussianQtyString(amount)+" ropes. You've brought me "+FindRussianQtyString(iRop)+". So, we've taken care of the ropes already. All right, at the rate of 1500 pesos per piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "Yes, yes... about my thing, of course. M-m-mmm... Hmmm... where did I... ahhh...";
			link.l1 = "What is it, master? You look quite worried. Is something wrong? Some kind of trouble?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "Precisely. Problems. Recent ones. Damn those treasure hunters...";
			link.l1 = "Calm down, calm down. It's not good at your age to be worrying like that. God forbid, you could be just one beat away. Who would build the frigate for the head of the Brethren then? Calm down and explain to me, who are these treasure hunters?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "Over there by my table is a door. It leads directly into an old vault. In this vault, in one of the treasure chests, I keep my metal box with the objects that were with me when I was pulled through that damn funnel twenty years ago, and I ended up here...";
			link.l1 = "What funnel? What are you talking about?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "Ah, forgive my ramblings. Growing old is not easy, young man. Pardon me. But that's beside the point. What matters is that a box with a gift for you is in the chest lying in the dungeon, currently occupied by some scoundrels. They're not our men, nor from Isla Tesoro.\nTreasure hunters—someone must have told them this place is full of riches. They wouldn't dare show themselves here, but I'm too afraid to visit them, you see? Their faces are...";
			link.l1 = "I see. Open your door. I'll drive out your uninvited guests.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "Just like that? You'll drive them out? Alone? Aren't you afraid? We have an entire settlement that will fight for you if you only ask...";
			link.l1 = "Less talk, more action, master. Open this door and leave the rest to me. Which chest are you keeping your things in?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "Right down the hallway is a whole collection of empty wooden barrels. Behind them, on the floor in a secluded spot, is a small chest. I've hammered a lock onto it, so I doubt those intruders would manage to get their filthy hands inside, even if they found it. Here, take the key.";
			link.l1 = "I'm glad you think ahead. Wait here and don't go anywhere.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "They just listened to you and left?";
			link.l1 = "That's right. They turned out to be rather polite fellows. I explained to them that their presence was frightening the old, renowned shipwright, and out of respect for your age, they left the premises. You can go down there without a worry.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "Ah-ha, you're mocking an old man! All right. Give me my box and I'll open it up and give you the device you've earned fair and square.";
			link.l1 = "Please, take it...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "Thank you! Let's open it. Here, take this. An automatic mechanical timer—no one makes such devices here, and no one will for the next three hundred years... ah, apologies, please forgive an old man. All I'm saying is that this thing is unique.\nIt does all the work itself, you won't need those foolish sand clocks and so on. No errors! Just keep it safe from direct blows and water, or you'll lose it. Even an ape could use this timer.";
			link.l1 = "Get a load of this! I've never seen anything so miraculous in my life! Thank you, master.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "You're welcome. Now you'll always know for sure what time it is. Don't ask me where I got it. I won't tell you.";
			link.l1 = "Everyone has their secrets, don't they, master? Fine... keep your secrets and I won't pry into your business. Thanks for the gift!";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "And thank you for your help, Captain. Visit me sometime. Don't forget an old shipwright.";
			link.l1 = "Like I could forget you... Anyway, I'll definitely do that, Alexus the Master. Goodbye!";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "Aha, Miguel! My old acquaintance. I remember him. He asked me about every little detail over and over. But how was I going to explain to him how a radio was constructed inside when he hadn't even seen a simple telegraph?";
			link.l1 = "What?.. What are you talking about, master?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Oh, sorry, young man. Don't pay much attention to my talking... Our curious Michel satisfied his curiosity and disappeared. Only three days ago we had a chat.";
			link.l1 = "Where's Miguel right now, if you don't mind my asking?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Who knows. Maybe he's tending to his business in Sharptown, or perhaps he's already departed from Isla Tesoro.";
			link.l1 = "I see. Thank you, master!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "Again with your 'ghost ship'... Know this - I'm only working with it in the hope that it will turn into something decent. Otherwise, I wouldn't even touch it. I think everyone at sea shares a similar opinion. What do you want to do with it this time?";
			else	
				dialog.text = "Ah, the 'ghost ship'! Mothers use your galleon to scare naughty children. And you decided to keep that damned vessel instead of sinking it! Sailors tremble when they see your ship on the horizon... So, what do you want to do with it?";
			if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "I like the idea of little cowards who are scared witless. But the interior makes me sad. Have you seen the cabin? It feels like a coffin. All that mould and dust. I want to fix it. Can you do that, master?";
				link.l1.go = "FDM_cabin";
			}
			/* if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "I am fed up with these torn black rags. I admit, they catch the wind as well as normal sails, but the view... Disgusting. I want ordinary snow-white sails. Are you in, master?";
				link.l2.go = "FDM_sails";
			}
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "Well, I think it's time to turn it into something decent. The ship is good, the crew is used to it, but it's just not dignified for a respectable captain to sail on a vessel that can scare the crap out of adults, never mind children. I want to completely rebuild it so that other captains envy it when they see my ship, instead of crossing themselves. And who else should I turn to with this but the best shipwright in the archipelago?";
				link.l3.go = "FDM_hull";
			} */
		break;
		
		case "FDM_cabin":
			dialog.text = "Why not? My hands are still steady.";
			link.l1 = "...";
			link.l1.go = "FDM_cabin_s";
			//link.l2 = "No point in excessive luxuries. Keep the standard.";
			//link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "Fine. Ten chests of doubloons and it will be done in five days.";
			link.l1 = "Deal!";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "Ten chests? A thousand and a half doubloons? Hm, I need time to consider such expenses...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "Seven chests of doubloons and it will be done in five days.";
			link.l1 = "Deal!";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "Seven chests? More than a thousand doubloons? Hm, I need time to consider such an expense...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "Good, I will be waiting for the payment.";
			if (iTemp > 0)
			{
				link.l1 = "I have chests with me. Let's see. Here, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "I have to go and put coins in the chests.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin.chest = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "Good, I will be waiting for the payment.";
			if (iTemp > 0)
			{
				link.l1 = "I have chests with me. Let's see. Here, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "I have to go and put coins in the chests.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin.chest)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin.chest));
				dialog.text = "So, you had to bring me "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" chests, you have brought "+FindRussianQtyString(iTemp)+". I have the payment. Now it's my turn. Go and walk around. Don't worry, I'll do my best.";
				link.l1 = "Good...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "So, you had to bring me "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" chests, you have brought "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" chests left.";
				link.l1 = "Very well, master.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin.chest = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
			npchar.quest.FDM_cabin = "done";
		break;
		
		case "FDM_sails":
			dialog.text = "Sure, I can do that! Well, well... This means we have to throw away every dirty old rag and put up new, clean sails made of cotton. There's a lot of work to be done here. One hundred thousand pesos for labour and materials. Deal?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "Sure, I'm fine with that. Deal!";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "Hm. I suppose I need to think about it...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Good. I have the coins, time to do my job. Walk around until it's done and don't worry.";
			link.l1 = "Good...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "Well, glad to finally hear that. And true enough - you seem to be a fine fellow, yet you're sailing on heaven knows what. But let me warn you upfront, this job is not just for a few hours, and it will cost you a pretty penny. ";
			link.l1 = "Alright, could you be a bit more specific?";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "Alright, let's calculate... For a complete overhaul of the ship's hull, I'll need 150 units of ironwood, 130 coils of rope, 170 rolls of ship silk, and 200 barrels of resin. I'll take 250 thousand pesos for all this. And don't look at me like that – most of that money will go to labour anyway! After all, we're not rebuilding a tartane.";
			link.l1 = "I think not. I'm not up for hauling such a huge amount of materials, along with paying a quarter million for the job. Guess I'll keep sailing on it the way it is.";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "Eh, what won't we do for our ship... Fine, it's a deal.";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "Fine, less conversation, more action. I'll be waiting for the money from you so that I can start buying everything I need. Once I have the money, you can start bringing me the materials. And I'll get to work on your vessel.";
			if(sti(pchar.money) >= 250000)
			{
    			link.l1 = "Well, money is not a problem. I've got it on me. Here you go, master.";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "At the moment, I don't have that kind of money. Wait a little, I'll bring it to you.";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			addMoneyToCharacter(pchar, -250000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "Not afraid to walk around a pirate settlement with such a tidy sum, hehe? Fine, I'm kidding, these are all honest people, in their own way. Now I'm waiting for the materials. As a reminder, you'll need to bring a total of 150 ironwood, 130 coils of rope, 170 rolls of ship silk, and 200 barrels of resin.";
			link.l1 = "Hang in there, I'll bring you your materials.";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "Very good! What have you brought me today?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Ironwood in the amount of "+FindRussianQtyString(iSan)+".";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 200)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Resin in the amount of "+FindRussianQtyString(iOil)+".";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 170)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Ship silk in the amount of "+FindRussianQtyString(iSil)+".";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 130)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Ropes in the amount of "+FindRussianQtyString(iRop)+".";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "Nothing yet. Just wanted to make sure the deal is still on.";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 199 && sti(npchar.quest.FDMshipsilk) > 169 && sti(npchar.quest.FDMropes) > 129)
			{
				dialog.text = "Wonderful! All the materials are accounted for. Now, let me take that monster off your hands. At last, it will have a proper look.";
				link.l1 = "Alright, enough grumbling, master. I'm eagerly awaiting the result.";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "Got anything else to brighten my day, Captain?";
				link.l1 = "Alas, that's all for now.";
				link.l1.go = "exit";
				link.l2 = "Yes, I have something else for you...";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "Let's see... I require "+FindRussianQtyString(amount)+" of ironwood. You brought "+FindRussianQtyString(iSan)+". of ironwood. Therefore, you still need to bring me "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Thanks! I'll get you the rest soon.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Let's see... I still need "+FindRussianQtyString(amount)+" of ironwood. You brought me  "+FindRussianQtyString(iSan)+". Therefore, we're done with ironwood!";
				link.l1 = "Thanks!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 200 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "Let's see... I require "+FindRussianQtyString(amount)+" of resin. You brought "+FindRussianQtyString(iOil)+". Therefore, you still need to bring me "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Thanks! I'll get you the rest soon.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Let's see... I still need "+FindRussianQtyString(amount)+" of resin. You brought me "+FindRussianQtyString(iOil)+". Therefore, we're done with resin!";
				link.l1 = "Thanks!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 170 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "Let's see... I require "+FindRussianQtyString(amount)+" of ship silk. You brought "+FindRussianQtyString(iSil)+". Therefore, you still need to bring me "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Thanks! I'll get you the rest soon";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Let's see... I still need "+FindRussianQtyString(amount)+" of ship silk. Therefore, you still need to bring me "+FindRussianQtyString(iSil)+". Therefore, we're done with ship silk";
				link.l1 = "Thanks!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 170 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "Let's see... I require "+FindRussianQtyString(amount)+" of ropes. You brought "+FindRussianQtyString(iRop)+". Therefore, you still need to bring me "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Thanks! I'll get you the rest soon";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Let's see... I require  "+FindRussianQtyString(amount)+" of ropes. You brought "+FindRussianQtyString(iRop)+". Therefore, we're done with ropes!";
				link.l1 = "Thanks!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "Well, did you bring the money";
			if(sti(pchar.money) >= 250000)
			{
    			link.l2 = "Yes, I did. 250,000 pesos, as agreed.";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Not yet, hold on, master.";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Five days passed..."+ NewStr() +"Master Alexus completed the job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			RealShips[sti(Pchar.Ship.Type)].BaseType = SHIP_RENOVATED_FDM;
			RealShips[sti(Pchar.Ship.Type)].Name = "NewFlyingdutchman1";
			RealShips[sti(Pchar.Ship.Type)].BaseName = "NewFlyingdutchman";
			/* RealShips[sti(Pchar.Ship.Type)].CannonsQuantity = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMin = 58;
			RealShips[sti(Pchar.Ship.Type)].rcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].lcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].fcannon = 6;
			RealShips[sti(Pchar.Ship.Type)].bcannon = 4; */
			if(Get_My_Cabin() == "My_Cabin") RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin";	
			else RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin_Huge";
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			pchar.ship.hp = GetCharacterShipMaxHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
