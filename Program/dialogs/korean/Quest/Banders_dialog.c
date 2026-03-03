void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
		
		case "fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "quest_fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DeliverToBander_Dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
			dialog.text = "너 대체 누구야?";
			link.l1 = "조용히 해, 진정해. 네가 말한 감옥에 갇힌 동료 이름은 "+pchar.questTemp.jailCanMove.Deliver.name+" 그가 나를 여기로 보냈어, 너 그 사람 알아?";
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Step_1":
			dialog.text = "네가 총독의 개들이 아니라는 증거라도 있나?";
			link.l1 = "그가 쪽지를 전해 달라고 했어. 여기 있어.";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		
		case "Step_2":
			dialog.text = "보자...(읽는 중). 젠장! 이런 때에 걸리다니... 제기랄, 이런 거래라니... 이봐, 선원, 네가 그렇다는 거지 "+GetSexPhrase("든든한 친구","능숙한 아가씨")+". 돈 좀 벌고 싶나? 우리 모두 이 거래로 이득을 볼 거야.";
			link.l1 = "나는 항상 그러고 싶지. 무슨 일이야?";
			link.l1.go = "Step_3";
		break;
			
		case "Step_3":
			dialog.text = "흥미로운 정보를 좀 나눠줄 수 있지. 나한텐 필요 없고, 우리 공통 친구 덕분에 시간도 없으니 말이야. 하지만 너한텐 쓸모가 있을지도 몰라. 물론 공짜는 아니야.";
			link.l1 = "얼마야?";
			if (hrand(2) == 0) link.l1.go = "Step_4";
			else link.l1.go = "Step_4d";
		break;
		
		case "Step_4":
			iTotalTemp = 0;
			dialog.text = "오만 페소.";
			if(makeint(Pchar.money) >= 50000)
			{
				link.l1 = "흠, 꽤 비싸군. 하지만 장사가 그만한 가치가 있다면 난 하겠어. 나도 끼겠어! 자세한 내용을 말해 줘.";
				link.l1.go = "Step_5";
			}
			link.l2 = "관심 없어.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_4d":
			iTotalTemp = 250+hrand(25)*10;
			dialog.text = ""+FindRussianDublonString(iTotalTemp)+". 한 푼도 깎아줄 수 없어!";
			if (PCharDublonsTotal() >= iTotalTemp)
			{
				link.l1 = "흠, 꽤 비싸군. 하지만 그만한 가치가 있다면 동의하지. 나도 끼겠어! 자세한 내용을 말해 줘.";
				link.l1.go = "Step_5";
			}
			link.l2 = "흥미 없어.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://попытка грабежа
					dialog.text = "그래, 그래, 뭐든지. "+GetSexPhrase("속았구나, 이 바보야","속았구나, 어리석은 계집애")+". 이제 돈 내, 선불이야!";
					link.l1 = "닻이나 처박아라... 네 친구가 자기 동료들은 인심이 후하다고 하더군!";
					link.l1.go = "Step_fight";
				break;
				
				case 1://кидалово
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveDublonsFromPCharTotal(iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					dialog.text = "좋아, 들어봐. 나는 이런 소식을 들었어, "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" 에서 멀지 않은 곳 "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" 두 개 있을 거야 "+pchar.questTemp.jailCanMove.Deliver.add1+" 무역선 - 그 "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" 그리고 "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" 화물창이 가득 찬 채로 "+pchar.questTemp.jailCanMove.Deliver.add+". 네가 그들을 잡아볼 수도 있겠지.";
					link.l1 = "훌륭하군! 너와 돈을 나눈 게 옳은 선택이었던 것 같아.";
					link.l1.go = "Step_lay";
				break;
				
				case 2://наведем на торговый корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveDublonsFromPCharTotal(iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					
					dialog.text = "좋아, 들어봐. 나는 이렇게 들었어, "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" 에서 멀지 않은 곳 "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" 두 명 있을 거야 "+pchar.questTemp.jailCanMove.Deliver.add1+" 무역선 - "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" 그리고 그 "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" 그들의 화물창이 가득 찬 채로 "+pchar.questTemp.jailCanMove.Deliver.add+". 그놈들을 잡아보는 것도 괜찮겠군.";
					link.l1 = "훌륭하군! 너와 돈을 나눈 게 옳은 선택이었던 것 같아.";
					link.l1.go = "Step_trader";
				break;
				
				case 3://наведем на курьерский корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveDublonsFromPCharTotal(iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "좋아, 들어봐. 나는 이렇게 들었어, "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" 에서 멀지 않은 곳 "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" 사환 루거선을 타고 항해하게 될 거야 "+pchar.questTemp.jailCanMove.Deliver.add2+" 이름이 붙은 "+pchar.questTemp.jailCanMove.Deliver.ShipName+". 그 배에는 보석이 많이 있어. 한번 잡아보는 것도 괜찮겠지.";
					link.l1 = "훌륭하군! 너에게 돈을 나눠준 게 옳은 선택이었던 것 같아.";
					link.l1.go = "Step_cureer";
				break;
			}
		break;
			
		case "Step_fight":
			dialog.text = "저 자식이 그렇게 멍청하지 않았다면 지금쯤 선술집에서 럼주나 마시고 있었겠지, 여기 포대 안에 앉아 있지는 않았을 거야. 그러니 불평할 거 있으면 다 저놈한테 해, 하하! 이제 돈 내놔. 안 그러면 여기서 살아나가지 못할 거다.";
			link.l1 = "그렇게 확신하나, 광대야?";
			link.l1.go = "quest_fight";
			link.l2 = "좋아, 돈 가져가라... 내가 수적으로 밀리잖아...";
			link.l2.go = "Step_takemoney";
		break;
		
		case "Step_takemoney":
			dialog.text = "잘했어, "+GetSexPhrase("친구","소녀")+". 우리 공통 친구가 죽고 나면 네게 돌려줄 거다, 하하... 이제 꺼져라. 조용히.";
			link.l1 = "저주받을 놈!";
			link.l1.go = "exit";
			if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
			else RemoveDublonsFromPCharTotal(300);
			AddQuestRecord("GivePrisonFree", "17");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;
		
		case "Step_lay":
			dialog.text = "그래... 뭐, 이제 조용히 꺼져.";
			link.l1 = "잘 가시오.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_lay";//придем - а там пусто
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_trader":
			dialog.text = "그래... 알겠으니, 이제 조용히 꺼져.";
			link.l1 = "안녕히 가시오.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_CreateTraderShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_cureer":
			dialog.text = "그래... 뭐, 이제 조용히 꺼져.";
			link.l1 = "잘 가라.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "14");
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sText", pchar.questTemp.jailCanMove.Deliver.add2);
			AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.function = "Deliver_CreateCureerShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_CureerShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_no":
			dialog.text = "그래, 됐다. 이제 가라, 더 이상 너랑 얘기할 건 없다.";
			link.l1 = "좋아, 잘 가라.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "16");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			AddQuestUserData("GivePrisonFree", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;

		case "Second time":
			dialog.text = "또 뭘 원해? 이미 꺼지라고 했잖아.";
			link.l1 = "좋아, 가고 있어...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Man_FackYou":
			dialog.text = "찌르고 싶어,  "+GetSexPhrase("멋쟁이","멍청한 계집애")+"?!";
			link.l1 = LinkRandPhrase("악마 놈!","카라암바!","젠장!");
			link.l1.go = "fight";
		break;
	}
}

void GetBandersTradeShore()//выберем остров для торгашей и курьера
{
	pchar.questTemp.jailCanMove.Deliver.Island = GetRandIslandId();
	pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
	while (pchar.questTemp.jailCanMove.Deliver.Island.Shore == "")
	{
		pchar.questTemp.jailCanMove.Deliver.Island = GetRandIslandId();
		pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
		if (!isLocationFreeForQuests(pchar.questTemp.jailCanMove.Deliver.Island)) pchar.questTemp.jailCanMove.Deliver.Island.Shore = "";
	} 
	pchar.questTemp.jailCanMove.Deliver.Island.Town = FindTownOnIsland(pchar.questTemp.jailCanMove.Deliver.Island);
	if (pchar.questTemp.jailCanMove.Deliver.Island.Town == "" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Caiman" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Terks" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Dominica")
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = GetIslandNameByID(pchar.questTemp.jailCanMove.Deliver.Island);
	}
	else
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = XI_ConvertString("Colony" + pchar.questTemp.jailCanMove.Deliver.Island.Town + "Gen");
	}
}

void GetBandersTradeGoods()//выберем товар для торгашей
{
	switch (rand(5))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_EBONY;
			pchar.questTemp.jailCanMove.Deliver.add = "ebony";
		break;
		
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_MAHOGANY;
			pchar.questTemp.jailCanMove.Deliver.add = "redwood";
		break;
		
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_CHOCOLATE;
			pchar.questTemp.jailCanMove.Deliver.add = "cacao";
		break;
		
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_COFFEE;
			pchar.questTemp.jailCanMove.Deliver.add = "coffee";
		break;
		
		case 4:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_CINNAMON;
			pchar.questTemp.jailCanMove.Deliver.add = "cinnamon";
		break;
		
		case 5:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_FOOD;
			pchar.questTemp.jailCanMove.Deliver.add = "provisions";
		break;
	}
}

void GetBandersTradeNation()//выберем нацию торгаша и курьера
{
	switch (rand(3))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Nation = SPAIN;
			pchar.questTemp.jailCanMove.Deliver.add1 = "Spanish";
			pchar.questTemp.jailCanMove.Deliver.add2 = "Spanish Treasury";
		break;
		
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Nation = FRANCE;
			pchar.questTemp.jailCanMove.Deliver.add1 = "French";
			pchar.questTemp.jailCanMove.Deliver.add2 = "French Treasury";
		break;
		
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Nation = HOLLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "Holland";
			pchar.questTemp.jailCanMove.Deliver.add2 = "Dutch West India Company";
		break;
		
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Nation = ENGLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "English";
			pchar.questTemp.jailCanMove.Deliver.add2 = "English Treasury";
			break;
	}
}
