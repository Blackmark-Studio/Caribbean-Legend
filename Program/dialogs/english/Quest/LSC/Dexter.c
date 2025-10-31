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
				dialog.text = "Don't bother me, boy. Talk to Shark, he's in charge here.";
				link.l1 = "May I at least say hello to you or is that against the rules?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "Layton, Shark told me you have a map of the island. Could I buy it off you?";
					link.l2.go = "map";
				}
				dialog.text = "Ah, "+GetFullName(pchar)+"! Do you have business with me or do you just want to talk? Either way, bring a bottle of rum next time, ha-ha!";
				link.l1 = "No, I just wanted to say hello. I will bring rum next time, just for you.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ha! A joker! All right... My name is Layton Dexter. I was Shark's mate prior to washing up here, and nowadays I'm his deputy on this 'City of Abandoned Ships.' (spits)\nSpend my days selling provisions to the citizens and trying to squeez money out of that idler, Fazio.";
			link.l1 = "I'm "+GetFullName(pchar)+". Pleasure to meet you... I think.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "Suppose you already heard Steve's dead. The Narwhals did it.";
			link.l1 = "I heard... So, you're the new Admiral?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "I am. Chad defected to the Narwhals, Steve's dead, so... I'm the Admiral. Objections?";
			link.l1 = "No... no objections.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "Good.";
			link.l1 = "Are you going to take revenge on the Narwhals for Shark's death?";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "You mean, will I declare war on then? No. There are better ways to make them pay.\nFirst I'll triple the price they pay for provisions. If they don't like that, and try to attack the San Augustine, I'll make them pay in blood.\nNext, I'm going to negotiate a truce with the Rivados. Of course, we can hardly trust those filthy Negroes, especially after the death of their wizard Chimiset, but food and rum can smooth over any number of sins.";
			link.l1 = "I see. Well... goodbye, Layton...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "Wait. Steve told me you wanted to leave the island and return with a ship. Is that still your plan?";
			link.l1 = "It is.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "Take these rutters. They contain sailing directions that'll lead you back here in one piece - meaning, you won't founder on the reefs, you won't be carried away by the current, and you won't collide with the wrecks on the outer rim.\nWithout these, you'll either miss the island entirely... or wind up another wreck.\nRemember that you must use a small vessel with a shallow draught in order to navigate the reefs. Tartane, lugger, schooner, sloop... nothing bigger. Got it?";
			link.l1 = "Aye, I do. Thank you.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Don't forget to fill your cargo hold with provisions - I'll buy them from you for a good price. And never show this document to anyone; our base must remain secret. I'm only giving it to you because Steve himself was going to, and because you're a friend of Jan Svenson.";
			link.l1 = "I promise to let no one else see these. Thank you again, Layton.";
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
			dialog.text = "Made any progress in planning your escape, "+pchar.name+"?";
			link.l1 = "Not yet, Layton, I'm working on it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "There you are. We need to talk.";
			link.l1 = "So, you're the Admiral now?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "Aye, I'm the Admiral. I was Steve's mate in everything, so I take charge upon his death. Objections?";
			link.l1 = "No... no objections. You have every right.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "Glad that we understand each other. Let me know if you need anything.";
			link.l1 = "Are you going to take revenge on the Narwhals for Shark's death?";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "You mean, will I declare war on then? No. There are better ways to make them pay.\nFirst I'll triple the price they pay for provisions. If they don't like that, and try to attack the San Augustine, I'll make them pay in blood.\nBesides, we have a good relationship with the Rivados now, so the Narwhals will hesitate to make a play against us again.";
			link.l1 = "I see. Anything else, or can I go?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "Yes. I see only one way we can get to the Narwhals. It's not perfect, but I don't see any alternative.\nWe will attack them from two directions. A group of cutthroats on longboats will board the Ceres while a second group, joined by the Rivados, will storm the Esmeralda.\nThis will either eliminate them completely, or prompt them to flee to the San Gabriel.\nThe second scenario is more likely; the San Gabriel is a very defensible position and besieging her would take a long time. Either way, we win.";
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
			dialog.text = "I'm waiting for the report of your conversation with Donald Greenspan. This is crucial, so don't waste any time.";
			link.l1 = "I'm on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "Yes, I have a map. If you want it, it can be yours for just two hundred doubloons.";
			link.l1 = "How about pesos?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "No, I take gold - and haggling will get you nowhere; I know exactly what this map is worth, and that's two hundred doubloons.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Fine, I agree. Here's your gold.";
				link.l1.go = "map_2";
			}
			link.l2 = "I don't have that much gold. Perhaps later...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveDublonsFromPCharTotal(200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "Take your map. It's worth the price - I crawled around the city for a whole week to draw it. If anything, I think I sold it to you cheaply.";
			link.l1 = "Cheaply?! Ha! Well... thank you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "Stop right there, mate! Yes, Shark was right, this bastard's gone mad. So many men dead because of him... Chain him up and throw him in the hold!";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "Steve made me Admiral in his stead - I take it you and he are going back to the Caribbean together.\nI'll stay here and carry on business; me and Steve are loathe to lose such a great base. And you, of course, will always be a welcome guest, here.";
			link.l1 = "Thanks, Layton. Keep a weather eye on that horizon, I'll be back someday.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "A-ha, "+GetFullName(pchar)+"! You did it! You found Justice Island using Steve's sailing directions, right? You mad bastard... welcome back!";
			link.l1 = "Thanks, Layton. Told you I'd be back someday, ha-ha!";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "All right. Do you have any food for sale? I'm prepared to buy at double the market rate.";
			if (iTrade > 0)
			{
				link.l1 = "Yes, I have provisions to sell.";
				link.l1.go = "trade";
			}
			link.l2 = "Unfortunately, I have nothing to sell you right now.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "Pity. Don't forget to bring some next time - I'll pay well.";
			link.l1 = "I'll try not to forget.";
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
				dialog.text = "What, are you drunk, mate? Come back when you're ready to talk seriously.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "That's a pittance! Not worth my time - bring me more!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "And how are you going to sail without any provisions for yourself, mate? You want your boys to starve? Keep at least "+FindRussianQtyString(GetCrewQuantity(pchar))+".";
				link.l1 = "Uh, you're right.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "Jesus Christ, that's too much for us! We'd never be able to eat it before it rotted. Right now I can't take more than "+iTemp+".";
			 link.l1 = "Whatever you say.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"? All right, I'll pay you "+FindRussianMoneyString(iMoney)+". Deal?";
			link.l1 = "Deal! Nice doing business with you!";
			link.l1.go = "trade_2";
			link.l2 = "Hm... no, I've changed my mind.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Deal. I'll pay you "+FindRussianMoneyString(iMoney)+" for the goods. Fair?";
			link.l1 = "Fair! Nice doing business with you!";
			link.l1.go = "trade_4";
			link.l2 = "Hm... no, I've changed my mind.";
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
				dialog.text = "Damn my eyes! My storehouse is full! I won't need to buy provisions for the next half-year.";
				link.l1 = "Good. Then I'll bring the next load of provision to you in six months.";
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
				dialog.text = "Excellent! My storehouse is full, now. I won't need to buy victuals for the next half-year.";
				link.l1 = "Good. Then I'll bring the next load of provisions in six months.";
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
			link.l2 = "It's nothing, just wanted to see how you're doing.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
