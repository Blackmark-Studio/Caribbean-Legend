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
			dialog.text = "뭐 원하는 거 있어?";
			link.l1 = "아니, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "흠... 그런데 몰리건은 어디 있지? 직접 나를 만나고 싶다더니?";
				link.l1 = "우리 불쌍한 폴이 열이 있어. 지금은 거래할 기분이 아니야. 내가 대신 왔어.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "무슨 일이십니까, 나리?";
				link.l1 = "철목을 사려고 기다리고 있는 거요?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "그런 헛소리는 누가 했소, 나리? 나는 아무도, 아무것도 기다리지 않소. 내 배는 윌렘스타트 총독의 명령으로 이 지역을 순찰 중이오. 그러니, 실례지만 내 배에서 내려주시오. 분명 착각하신 게요.";
			link.l1 = "흠... 알겠소. 폐를 끼쳐 미안하오.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "우리 이미 이 얘기 하지 않았나, 나리?";
			link.l1 = "그래, 그래. 나는 이제 떠나서 내 배에 타고 있네.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "너는 누구냐?";
			link.l1 = "누구랑 거래하는지 신경도 안 쓰나? 내가 철목을 팔려고 가져왔어. 얼마 줄 건데?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "약속대로라면 한 개당 40두블론이오.";
			link.l1 = "흠...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "이봐, 우리 몰리건이랑 약속했잖아. 이건 좋은 값이야, 이보다 나은 가격 못 구해. 그러니까 시장 바닥 촌놈처럼 굴지 마. 철목 얼마나 가져왔어?";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "훌륭하군. 기대했던 것보다 더 많아. 자, 금화를 가져가라. 철목을 더 구하면 생마르탱의 선술집에 가서... 누군지 알지? 그에게 말해라. 그가 우리 만남을 주선할 거다. 너, 그 멍청이 몰리건보다 훨씬 나은 동료로구나.";
				link.l1 = "좋아. 거래하자.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "좋아. 자, 금을 가져가라. 철목을 더 구하게 되면 필립스버그의 선술집에 가서... 누군지 알지? 그에게 말을 걸어라. 그가 나와 연락할 거다. 너와도 그 바보 몰리건만큼이나 장사를 할 수 있겠군.";
				link.l1 = "좋아. 거래지.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "흠... 기대보다 적군. 좋아. 여기, 금을 가져가라. 그리고 몰리건에게 다음에는 최소한 백 개 이상은 가져와야 한다고 전해라.";
				link.l1 = "좋소. 내가 그에게 말하겠소.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "장난해? 우리 몰리건이랑 약속했잖아, 최소한 오십 개는 가져와야 한다고! 꺼져, 수량 맞출 때까지 다시 오지 마.";
			link.l1 = "좋아, 좋아, 진정해.";
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
			dialog.text = "오, 내 오랜 친구! 철목 좀 팔러 왔나?";
			link.l1 = "정확히 그렇소, Michael. 거래를 합시다.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "얼마나 가지고 있지? 나는 최소한 그만큼은 필요해\n "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "그건 알고 있소. 나는 가졌소 "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SANDAL))+"  네가 그토록 얻고 싶어 하는 철목으로 만든 것이지.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "흠. 유감이지만, 그만한 돈은 없어.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "젠장, 경고 안 받았어? 아니면 쥐들이 나무라도 갉아먹은 거야? 나한텐 필요해\n "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" 한 조각도 덜어서는 안 된다. 다음번에는 내 대리인이 지시한 만큼의 목재를 가져오게. 다시는 나를 실망시키지 않길 바라오, 그렇지 않으면 자네의 서비스를 거절할 수밖에 없을 것이네.";
				link.l1 = "좋소, 마인헤르. 앞으로는 더 주의하겠소.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "너 나한테 두 번째로 사기 치는 거야. 마음에 안 들어. 이번이 마지막 경고라는 걸 알아둬. 다음번엔 네 도움 따윈 거절할 거다.";
					link.l1 = "빌어먹을 쥐들이 내 물건을 망가뜨렸어! 맹세코, 미셸, 이번이 마지막일 거야.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "이제 내 인내심도 바닥났어! 더 이상 너랑 거래하고 싶지 않다. 썩 꺼져, 그리고 나를 잊어버려라.";
					link.l1 = "하지만 마인헤르...";
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
				dialog.text = "이런 젠장! 미안하다, 친구야, 하지만 나는 살 수 있는 게 이것뿐이야 "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+", 네 화물 전부를 살 만큼 돈이 부족하네. 나는 한 차례 물건만 기대하고 있었어\n "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" 한 조각에 40두블론씩...";
				link.l1 = "좋아. 가져가라 "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" 지금은 여기까지 팔고, 나머지는 다음에 팔아주지.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "좋소. 가격은 늘 그렇듯이, 한 점당 40두블룬이오.";
				link.l1 = "나야 상관없지. 네 몫 가져가.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "거래하게 되어 기쁩니다. 철목을 더 팔고 싶으면 또 찾아오시오.";
			link.l1 = "또 봅시다, 나리. 당신과의 협력이 내게 아주 큰 이익이 되었소. 안녕히 가시오!";
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
