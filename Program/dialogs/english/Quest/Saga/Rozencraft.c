// Михаэль Розенкрафт - голландский капитан, квестовый покупатель бакаута
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
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Hm... And where is Molligan? Didn't he want to see me himself?";
				link.l1 = "Our poor Paul has a fever. He is not in the mood to trade. I am here in his place.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "What do you want, sir?";
				link.l1 = "I take it you are waiting to buy some ironwood?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Who told you that nonsense, Mister? I am not waiting for anyone or anything. My vessel is patrolling the local area by order of the governor of Willemstad. So, would you be so kind as to leave my ship, you must be mistaken.";
			link.l1 = "Hm... I see. I am sorry for troubling you.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "Haven't we had this talk already, Mister?";
			link.l1 = "Yes, yes. I am leaving and boarding my ship already.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "And who are you?";
			link.l1 = "Don't you care who you trade with? I've brought ironwood to sell. How much?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "According to the agreement - forty doubloons per piece.";
			link.l1 = "Hm...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Pal, we had a deal with Molligan. This is a good price, you won't find a better one. So don't act like a farmer at the market. How much ironwood have you got?";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Splendid. That's more than I expected. Here, take the gold. If you get more ironwood, go to the tavern in Saint Martin and talk to... you know who. He will arrange a meeting for us. I see that you are a much better partner than that idiot Molligan.";
				link.l1 = "Fine. It's a deal.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Good. Here, take the gold. If you get more ironwood, go to the tavern in Philipsburg and talk to... you know who. He will get in touch with me. I see that we can do business with you just as well as with that fool Molligan.";
				link.l1 = "Fine. It's a deal.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Hm... I was expecting more. Fine. Here, take the gold. And tell Molligan that next time he must bring a batch no smaller than one hundred pieces.";
				link.l1 = "Fine. I will tell him.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Are you kidding me? We had a deal with Molligan, the batch must not be smaller than fifty pieces! Get lost and don't return until you have enough.";
			link.l1 = "Fine, fine, calm down.";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = makeint((iTemp*40-2000)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // доля Яна
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "In addition, if I get ironwood, I will be able to sell it to Michael Rosencraft by having a meeting arranged with his man at the tavern in Philipsburg.");
				pchar.questTemp.Saga = "removebakaut";
				// корабль Розенкрафта сохраняем, в АИ на него будет стоять проверка на попадание
				pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; //снять прерывание
				pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; //снять прерывание
				// ставим новое прерывание на потопление Розенкрафта
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
				pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
				pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
				pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
			}
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
	// ------------------------------------генератор сбыта бакаута-----------------------------------------------
		case "bakaut":
			dialog.text = "Oh, my old friend! Got some ironwood to sell?";
			link.l1 = "Exactly, Michael. Let's trade.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "How much have you got? I need a batch no smaller than "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "I know that. I have got "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SANDAL))+"  of ironwood that you are so eager to get.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Unfortunately, I haven't got that much.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "Damn it, didn't they warn you? Or have the rats eaten the wood? I need "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" and not a single piece less. Next time, bring me as much wood as my agent instructs you. I do hope you won't disappoint me again, or I shall have to decline your services.";
				link.l1 = "Fine, Mynheer, I will be more attentive in the future.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "You are screwing me for the second time. I don't like it. Know that this is the last warning, next time I will decline your services.";
					link.l1 = "Damn rats have damaged my goods! I promise you, Michael, this will be the last time.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "And now my patience has run out! I don't want to do business with you any longer. Get lost and forget about me.";
					link.l1 = "But Mynheer...";
					link.l1.go = "bakaut_no_2";
				}
			}
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
		break;
		
		case "bakaut_no_1":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			if (!CheckAttribute(npchar, "quest.bakaut_angry")) npchar.quest.bakaut_angry = 1;
			else npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry)+1;
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			AddQuestRecord("Bakaut", "3");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_no_2":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
			AddQuestRecord("Bakaut", "4");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_1":
			iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
			if (iTemp > sti(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "Shiver me timbers! I'm sorry, friend, but I can only buy "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+", I don't have enough money for all your cargo. I was expecting a batch of "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" pieces at forty doubloons each...";
				link.l1 = "Fine. Take "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" now, and I will sell you the rest next time.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Very well. The price is as usual, forty doubloons for each piece.";
				link.l1 = "Works for me. Take your batch.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "Pleasure doing business with you. Come and see me again if you want to sell more ironwood.";
			link.l1 = "See you again, Mister. Our collaboration has been very profitable for me. Goodbye!";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = sti(npchar.quest.bakaut);
			TakeNItems(pchar, "gold_dublon", iTemp*40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			AddQuestRecord("Bakaut", "2");
			AddQuestUserData("Bakaut", "sQty", iTemp);
			AddQuestUserData("Bakaut", "sDublon", iTemp*40);
			AddQuestUserData("Bakaut", "sDublon1", iTemp*40-iTemp*30);
			CloseQuestHeader("Bakaut");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
