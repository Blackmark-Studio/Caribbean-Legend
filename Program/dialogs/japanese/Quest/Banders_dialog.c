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
			dialog.text = "てめえ、何者だ？";
			link.l1 = "静かに、落ち着け。お前の投獄された仲間の名前は "+pchar.questTemp.jailCanMove.Deliver.name+" ここに俺を寄越したんだが、あいつのこと知ってるか？";
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Step_1":
			dialog.text = "お前が総督の犬じゃねえって証拠はあるのか？";
			link.l1 = "手紙を届けてくれと頼まれたんだ。これだ。";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		
		case "Step_2":
			dialog.text = "さてと…（読みながら）。くそっ！捕まるには最悪のタイミングだ…ちくしょう、こんな取引なんて…おい、水夫、あんたは "+GetSexPhrase("頼もしい仲間","腕の立つ娘")+"。小遣いを稼ぎたいか？この取引はみんなに得があるぜ。";
			link.l1 = "俺はいつだってやりたいぜ。どういう話だ？";
			link.l1.go = "Step_3";
		break;
			
		case "Step_3":
			dialog.text = "面白い情報を教えてやってもいいぜ。俺にはもう必要ねえし、共通の知り合いのおかげで間に合わなかったが、 お前には役立つかもしれねえ。ただし、タダじゃねえぞ。";
			link.l1 = "いくらだ？";
			if (hrand(2) == 0) link.l1.go = "Step_4";
			else link.l1.go = "Step_4d";
		break;
		
		case "Step_4":
			iTotalTemp = 0;
			dialog.text = "「五万ペソ。」";
			if(makeint(Pchar.money) >= 50000)
			{
				link.l1 = "ふむ、ずいぶん高いな。だが、商売になるなら俺は乗るぜ！詳しい話を聞かせてくれ。";
				link.l1.go = "Step_5";
			}
			link.l2 = "興味ねえな。";
			link.l2.go = "Step_no";
		break;
		
		case "Step_4d":
			iTotalTemp = 250+hrand(25)*10;
			dialog.text = ""+FindRussianDublonString(iTotalTemp)+"。1枚たりともまけねえぞ！";
			if (PCharDublonsTotal() >= iTotalTemp)
			{
				link.l1 = "ふむ、ずいぶん高いな。しかし、商売の価値があるなら同意するぜ。乗った！詳しい話を聞かせてくれ。";
				link.l1.go = "Step_5";
			}
			link.l2 = "興味ねえな。";
			link.l2.go = "Step_no";
		break;
		
		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://попытка грабежа
					dialog.text = "「まあまあ、どうでもいいさ。」 "+GetSexPhrase("騙されたな、この間抜けめ","騙されたな、おろかな娘よ")+"。さあ、今すぐ払え、先払いだぜ！";
					link.l1 = "錨で自分をぶっ刺してこいよ……お前の仲間は気前がいいって友達が言ってたぜ！";
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
					dialog.text = "いいか、聞け。俺が聞いた話だが、 "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" 「～からそう遠くない」 "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" 二つになる "+pchar.questTemp.jailCanMove.Deliver.add1+" 交易船－ "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" そして "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" 積荷室にいっぱい詰め込まれた "+pchar.questTemp.jailCanMove.Deliver.add+"。奴らを捕まえてみてもいいんじゃねえか。";
					link.l1 = "素晴らしい！俺があんたに金を分けて正解だったようだな。";
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
					
					dialog.text = "いいか、聞け。俺が聞いた話だが、 "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" 「～からそう遠くない」 "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" 「二つになる」 "+pchar.questTemp.jailCanMove.Deliver.add1+" 交易船― "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" そして "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" 積荷室にいっぱい詰め込まれた "+pchar.questTemp.jailCanMove.Deliver.add+"。奴らを捕まえてみてもいいぜ。";
					link.l1 = "素晴らしい！お前に金貨を分けて正解だったようだな。";
					link.l1.go = "Step_trader";
				break;
				
				case 3://наведем на курьерский корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveDublonsFromPCharTotal(iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "いいか、聞け。俺が聞いた話だが、 "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" 「～からそう遠くない」 "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" 通報用ラガー船で航海することになる "+pchar.questTemp.jailCanMove.Deliver.add2+" 「名付けられた」 "+pchar.questTemp.jailCanMove.Deliver.ShipName+"。宝石がたくさん乗っているぜ。お前もあの船を追ってみたらどうだ。";
					link.l1 = "素晴らしい！お前に金貨を分けて正解だったようだな。";
					link.l1.go = "Step_cureer";
				break;
			}
		break;
			
		case "Step_fight":
			dialog.text = "あいつがもう少し賢けりゃ、今ごろ酒場でラムを飲んでたはずだぜ、こんな地下牢に座ってるんじゃなくてな。 だから文句があるなら全部あいつに言えよ、ははっ！さあ、金を出せ。じゃねえと生きてここを出られねえぞ。";
			link.l1 = "それほど自信があるのかよ、この道化野郎？";
			link.l1.go = "quest_fight";
			link.l2 = "わかった、金貨を持っていけ……俺は数で負けてるんだ……";
			link.l2.go = "Step_takemoney";
		break;
		
		case "Step_takemoney":
			dialog.text = "「よくやった」 "+GetSexPhrase("相棒","娘")+"。俺たちの共通の友人は、お前にそれを返すさ、はは……奴が死んだらな。失せろ。静かにな。";
			link.l1 = "呪われちまえ！";
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
			dialog.text = "ああ……どうでもいいさ、さっさと静かに立ち去れ。";
			link.l1 = "さらば。";
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
			dialog.text = "ああ……どうでもいいさ、さっさと静かに出ていけ。";
			link.l1 = "さらば。";
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
			dialog.text = "ああ…どうでもいいさ、さっさと静かに出ていけ。";
			link.l1 = "さらば。";
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
			dialog.text = "どうでもいいさ。さあ行け、俺たちはお前と話すことなんてねえんだ。";
			link.l1 = "ああ、じゃあな。";
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
			dialog.text = "他に何が欲しいんだ？もうとっとと失せろって言っただろ。";
			link.l1 = "よし、今行くぜ……";
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Man_FackYou":
			dialog.text = "刺されたいのか "+GetSexPhrase("伊達男","「馬鹿な娘」")+"?!";
			link.l1 = LinkRandPhrase("「悪魔め！」","「カランバ！」","くそっ！");
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
