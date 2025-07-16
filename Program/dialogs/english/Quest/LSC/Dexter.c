// старпом Акулы - Лейтон Декстер
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "What do you want, boy? Talk to Shark, he is in charge here.";
				link.l1 = "Can I at least say hello to you or is that against the rules?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "Layton, Shark told me that you have a map of the Island. Are you selling it?";
					link.l2.go = "map";
				}
				dialog.text = "A-ah, "+GetFullName(pchar)+"! Do you have business with me or do you just want to talk again? If so, bring a bottle of rum next time, ha-ha!";
				link.l1 = "No, I have no particular business for you. I will bring rum next time, just for you.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ha! You are a joker, aren't you boy? Fine... My name is Layton Dexter, I am Shark's second in command and nowadays I am his deputy on this damned City of Abandoned Ships. In the meantime I sell provisions and try to get money out of that idler Fazio.";
			link.l1 = "And my name is "+GetFullName(pchar)+". Pleased to meet you!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "I suppose you already heard that Steven is dead. The Narwhals did it.";
			link.l1 = "You are right, I know that... So what, you're the admiral now?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "Exactly. Chad defected to the Narwhals, Steven is dead and thus - me being the second in command, naturally, I am the admiral now. Objections?";
			link.l1 = "No. No objections.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "Good. Let's hear your questions.";
			link.l1 = "Are you going to exact revenge on the Narwhals for Steven's death?";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "You mean, will I declare a war on then? No. There are better ways to make them pay. First I will triple the price they pay for provisions\nIf they attack the 'San Augustine' we will give them hell. Then, I am going to negotiate with the Rivados. Of course, we can't trust those dirty niggers and they hold a grudge against us for the death of their wizard, but any problem can be smoothed over with rum and food.";
			link.l1 = "I see. Fine, Layton, I have to go...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "Wait. Steven told me that you are trying to leave the City of Abandoned Ships somehow and to come back here on a ship?";
			link.l1 = "That's the plan.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "Take these sailing directions. Using them you can get back here by sea in one piece. Meaning: you won't founder on the reefs, you won't be carried away by the current, and your ship won't get dashed onto the other wrecks on the outer rim\nWithout them you will either fail to find a passage or your ship will join her sisters here. Remember that you must use a small vessel with a shallow draft in order to pass the shoals. Lugger, schooner, brigantine, brig... nothing bigger than a fourth class. Got it?";
			link.l1 = "Aye I do. Thanks! That is exactly what I need.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Don't forget to fill your cargo hold with provisions. I will sell them to you for a good price. Don't show this document to anyone, our base must remain secret. I am giving you this document only because Steven himself was going to give it to you, and you are a friend of Jan Svenson.";
			link.l1 = "Don't worry about that. Thank you again and see you around!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = "Do you have any progress in escaping the City of Abandoned Ships, "+pchar.name+"?";
			link.l1 = "No progress yet, Layton. I am working on it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "Here you are, "+pchar.name+". I have a few things to discuss with you.";
			link.l1 = "As far as I understood, you have taken Steven's position after his death. So are you the admiral now?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "Exactly. Being the second in command, I'm the admiral now. Objections?";
			link.l1 = "No objections. You have every right to keep this position.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "I am glad that we understand each other. Let me know if you need anything.";
			link.l1 = "Are you going to exact revenge upon the Narwhals for Steven's death?";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "You mean, will I declare war on then? No. There are better ways to make them pay. I will triple the price they pay for provisions\nIf they attack 'San Augustine', we will give them hell. Besides, we have good relationships with the Rivados now, so Narwhals won't risk anything to act stupidly.";
			link.l1 = "I see. Do you want to tell me anything else? Or can I go now?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "I do. I can see only one way we can get the Narwhals. It's not perfect, but I don't see any alternative. We will attack them from two directions. A group of bold cutthroats on longboats will board the 'Ceres Smithy', while a second group along with the Rivados will storm the 'Esmeralda'. This will either eliminate them completely, or will make them flee to the 'San Gabriel. Second scenario is the most probable, San Gabriel is a highly fortified position and besieging her take a long time. But either way, we will win.";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // ноду Акуле
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "We are waiting for the results of your conversation with Donald Greenspen. It is a very important matter, so don't waste any time.";
			link.l1 = "I am on my way!";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "Yes, I have got the map. Would you like to buy it? You are welcome, if you would. It will be yours for just two hundred doubloons.";
			link.l1 = "How about pesos?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "No. I want gold. No haggling will do.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "Fine. Take your gold, I agree.";
				link.l1.go = "map_2";
			}
			link.l2 = "I don't have that much gold. Perhaps later...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveItems(pchar, "gold_dublon", 200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "Nice deal, lad! Take your map. It's worth the price - I crawled around the City for a whole week to draw it so I've sold it to you quite cheaply, actually.";
			link.l1 = "Cheaply?! Sure. Well, thank you anyway.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "Stop right there, matey! Yes, Shark was right, this guy has gone mad. So many men are dead because of him... Chain him up boys and throw him in the hold!";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "Steven made me admiral of the City instead of him - I take it that you and he are going back to the Caribbean together. I will stay here and carry on business, me and Steven are loathe to lose such a great base. And I want to tell you that you will always be a welcome guest here.";
			link.l1 = "Thanks, Layton. I think I will be returning to your Island quite often.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "Ah, my old friend "+GetFullName(pchar)+"! You have managed to find the City of Abandoned Ships using Steven's sailing directions, right? I am very, very glad to see you. You are always a welcome guest here.";
			link.l1 = "Thanks, Layton. I think I will be returning to your City quite often.";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "Very well. Do you have any food for sale? I am ready to buy it from you for double the usual rate.";
			if (iTrade > 0)
			{
				link.l1 = "Yes, I can sell you some provisions.";
				link.l1.go = "trade";
			}
			link.l2 = "Unfortunately, I have nothing to sell you right now.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "Pity. Don't forget to bring it next time - I will pay well.";
			link.l1 = "Fine. I will try not to forget about it...";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "How much?";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "Damn, you are stone drunk, mate! I'm impressed! Go and have some sleep, we will trade later.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "I won't even lift my ass from the chair for such a petty amount. Bring me more!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "And how are you going to sail without any provision on your ship, mate? You want your boys to starve? Keep at least "+FindRussianQtyString(GetCrewQuantity(pchar))+" for yourself.";
				link.l1 = "Hm, you are right.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "Wow, pal, that's too much for us! We won't be able to eat it before it rots. Right now I can't take more than "+iTemp+".";
			 link.l1 = "Whatever you say.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"? Fine. I will pay you "+FindRussianMoneyString(iMoney)+". Deal?";
			link.l1 = "Sure! Nice doing business with you!";
			link.l1.go = "trade_2";
			link.l2 = "Hm. No, I have changed my mind.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Deal. I'll pay you "+FindRussianMoneyString(iMoney)+" for the goods. Is it enough?";
			link.l1 = "Sure! Nice trading!";
			link.l1.go = "trade_4";
			link.l2 = "Hm. No, I have changed my mind.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Damn my eyes! My storehouse is full! I won't need to buy provision for the next half a year.";
				link.l1 = "Good. Then I will bring the next load of provision to you in six months.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Great! Bring me more next time.";
				link.l1 = "Sure!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Nice! My storehouse is full now. I won't need to buy victuals for the next half a year.";
				link.l1 = "Good. Then I will bring the next load of provisions to you in six months.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Great! Bring me more next time.";
				link.l1 = "Sure!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "A-ah, "+GetFullName(pchar)+"! Glad to see you! What do you want?";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "Want to buy some provisions from me?";
				link.l1.go = "trade";
			}
			link.l2 = "It's nothing, just wanted to know how you were doing.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
