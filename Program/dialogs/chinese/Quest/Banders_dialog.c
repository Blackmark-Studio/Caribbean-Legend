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
			dialog.text = "你到底是谁? ";
			link.l1 = "安静点, 冷静一下。 你那位被监禁的同伴, 名叫" + pchar.questTemp.jailCanMove.Deliver.name + ", 派我来的, 你认识他吗? ";
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Step_1":
			dialog.text = "有什么证据证明你不是总督的走狗? ";
			link.l1 = "他让我给你带封信, 给你。 ";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		
		case "Step_2":
			dialog.text = "让我看看... (阅读中)。 该死! 被抓的时机真糟... 靠, 这么个交易... 听着, 水手, 看你是个" + GetSexPhrase("强壮的伙计","熟练的姑娘") + "。 想赚点钱吗? 我们都能从这交易中获利。 ";
			link.l1 = "我总是想赚钱。 什么交易? ";
			link.l1.go = "Step_3";
		break;
			
		case "Step_3":
			dialog.text = "我可以告诉你一些有趣的消息。 我不需要它, 反正我也没时间了, 多亏了我们共同的朋友, 但你可能会觉得有用。 不是免费的。 ";
			link.l1 = "多少钱? ";
			if (hrand(2) == 0) link.l1.go = "Step_4";
			else link.l1.go = "Step_4d";
		break;
		
		case "Step_4":
			iTotalTemp = 0;
			dialog.text = "五万比索。 ";
			if(makeint(Pchar.money) >= 50000)
			{
				link.l1 = "嗯, 相当贵。 但如果这生意值得, 我就同意。 我加入! 告诉我细节。 ";
				link.l1.go = "Step_5";
			}
			link.l2 = "没兴趣。 ";
			link.l2.go = "Step_no";
		break;
		
		case "Step_4d":
			iTotalTemp = 250+hrand(25)*10;
			dialog.text = ""+FindRussianDublonString(iTotalTemp)+"。 一分都不能少! ";
			if (GetCharacterItem(pchar, "gold_dublon") >= iTotalTemp)
			{
				link.l1 = "嗯, 相当贵。 但如果这生意值得, 我就同意。 我加入! 告诉我细节。 ";
				link.l1.go = "Step_5";
			}
			link.l2 = "没兴趣。 ";
			link.l2.go = "Step_no";
		break;
		
		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://抢劫企图
					dialog.text = "好吧好吧, 不管怎样, "+ GetSexPhrase("你被耍了, 蠢货","你被耍了, 傻姑娘") +"。 现在付钱, 一手交钱! ";
					link.l1 = "你去用锚自慰吧... 你朋友说他的伙伴们很大方! ";
					link.l1.go = "Step_fight";
				break;
				
				case 1://诈骗
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					dialog.text = "好的, 听着。 我得到消息, 在" + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + "内, 在" + pchar.questTemp.jailCanMove.Deliver.Island.Areal + "附近会有两艘" + pchar.questTemp.jailCanMove.Deliver.add1 + "商船 - " + pchar.questTemp.jailCanMove.Deliver.ShipName1 + "号和" + pchar.questTemp.jailCanMove.Deliver.ShipName2 + "号, 货舱里装满了" + pchar.questTemp.jailCanMove.Deliver.add + "。 你可以试试截住它们。 ";
					link.l1 = "太棒了! 看来我跟你分钱是对的。 ";
					link.l1.go = "Step_lay";
				break;
				
				case 2://指引商船
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					
					dialog.text = "好的, 听着。 我得到消息, 在" + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + "内, 在" + pchar.questTemp.jailCanMove.Deliver.Island.Areal + "附近会有两艘" + pchar.questTemp.jailCanMove.Deliver.add1 + "商船 - " + pchar.questTemp.jailCanMove.Deliver.ShipName1 + "号和" + pchar.questTemp.jailCanMove.Deliver.ShipName2 + "号, 货舱里装满了" + pchar.questTemp.jailCanMove.Deliver.add + "。 你可以试试截住它们。 ";
					link.l1 = "太棒了! 看来我跟你分钱是对的。 ";
					link.l1.go = "Step_trader";
				break;
				
				case 3://指引信使船
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "好的, 听着。 我得到消息, 在" + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + "内, 在" + pchar.questTemp.jailCanMove.Deliver.Island.Areal + "附近会航行着一艘名为" + pchar.questTemp.jailCanMove.Deliver.ShipName + "的" + pchar.questTemp.jailCanMove.Deliver.add2 + "信使小帆船。 船上有很多珠宝。 你可以试试截住她。 ";
					link.l1 = "太棒了! 看来我跟你分钱是对的。 ";
					link.l1.go = "Step_cureer";
				break;
			}
		break;
			
		case "Step_fight":
			dialog.text = "如果他没那么蠢, 现在应该在酒馆喝朗姆酒, 而不是坐在牢里。 所以要抱怨就找他吧, 哈哈哈! 现在把钱给我, 否则你别想活着离开这里。 ";
			link.l1 = "你这么确定吗, 小丑? ";
			link.l1.go = "quest_fight";
			link.l2 = "好吧, 拿钱... 我寡不敌众... ";
			link.l2.go = "Step_takemoney";
		break;
		
		case "Step_takemoney":
			dialog.text = "做得好, "+ GetSexPhrase("伙计","姑娘") +"。 我们共同的朋友会把钱还给你的, 哈哈哈... 等他死了之后。 滚吧, 安静点。 ";
			link.l1 = "诅咒你! ";
			link.l1.go = "exit";
			if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
			else RemoveItems(pchar, "gold_dublon", 300);
			AddQuestRecord("GivePrisonFree", "17");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;
		
		case "Step_lay":
			dialog.text = "当然... 不管怎样, 现在离开, 安静点。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//送往该地点
			pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_lay";//到达后发现为空
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//计时器
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_trader":
			dialog.text = "当然... 不管怎样, 现在离开, 安静点。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//送往该地点
			pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_CreateTraderShips";//创建船只
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//计时器
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_cureer":
			dialog.text = "当然... 不管怎样, 现在离开, 安静点。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "14");
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sText", pchar.questTemp.jailCanMove.Deliver.add2);
			AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1 = "location";
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//送往该地点
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.function = "Deliver_CreateCureerShips";//创建船只
			SetFunctionTimerCondition("Deliver_CureerShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//计时器
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_no":
			dialog.text = "那随便吧。 现在走吧, 我们没什么好谈的了。 ";
			link.l1 = "好吧, 再见。 ";
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
			dialog.text = "你还想干什么? 我已经告诉你滚了。 ";
			link.l1 = "好吧, 我这就走... ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Man_FackYou":
			dialog.text = "你想被捅吗, " + GetSexPhrase("花花公子","愚蠢的姑娘") + "?!";
			link.l1 = LinkRandPhrase("魔鬼! ", "卡兰巴! ", "该死的! ");
			link.l1.go = "fight";
		break;
	}
}

void GetBandersTradeShore()//为商人和信使选择岛屿
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
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = GetConvertStr(pchar.questTemp.jailCanMove.Deliver.Island, "LocLables.txt") + "");
	}
	else
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = XI_ConvertString("Colony" + pchar.questTemp.jailCanMove.Deliver.Island.Town + "Gen");
	}
}

void GetBandersTradeGoods()//为商人选择货物
{
	switch (rand(6))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_EBONY;
			pchar.questTemp.jailCanMove.Deliver.add = "乌木";
		break;
		
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_MAHOGANY;
			pchar.questTemp.jailCanMove.Deliver.add = "红木";
		break;
		
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_CHOCOLATE;
			pchar.questTemp.jailCanMove.Deliver.add = "可可";
		break;
		
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_COFFEE;
			pchar.questTemp.jailCanMove.Deliver.add = "咖啡";
		break;
		
		case 4:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_CINNAMON;
			pchar.questTemp.jailCanMove.Deliver.add = "肉桂";
		break;
		
		case 5:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_FOOD;
			pchar.questTemp.jailCanMove.Deliver.add = "补给品";
		break;
		
		case 6:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_WEAPON;
			pchar.questTemp.jailCanMove.Deliver.add = "武器";
		break;
	}
}

void GetBandersTradeNation()//为商人和信使选择国家
{
	switch (rand(3))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Nation = SPAIN;
			pchar.questTemp.jailCanMove.Deliver.add1 = "西班牙人";
			pchar.questTemp.jailCanMove.Deliver.add2 = "西班牙财政部";
		break;
		
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Nation = FRANCE;
			pchar.questTemp.jailCanMove.Deliver.add1 = "法国人";
			pchar.questTemp.jailCanMove.Deliver.add2 = "法国财政部";
		break;
		
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Nation = HOLLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "荷兰人";
			pchar.questTemp.jailCanMove.Deliver.add2 = "荷兰西印度公司";
		break;
		
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Nation = ENGLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "英国人";
			pchar.questTemp.jailCanMove.Deliver.add2 = "英国财政部";
			break;
	}
}