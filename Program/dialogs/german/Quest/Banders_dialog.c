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
			dialog.text = "Wer zur Hölle bist du?";
			link.l1 = "Ruhig, beruhige dich. Dein inhaftierter Genosse namens "+pchar.questTemp.jailCanMove.Deliver.name+" hat mich hierher geschickt, kennen Sie ihn?";
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Step_1":
			dialog.text = "Hast du irgendeinen Beweis, dass du nicht einer der Hunde des Gouverneurs bist?";
			link.l1 = "Er hat mich gebeten, einen Zettel zu überbringen. Hier ist er.";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		
		case "Step_2":
			dialog.text = "Lass uns sehen... (liest). Verdammt! Ein schlechter Zeitpunkt, um erwischt zu werden... Scheiße, was für ein Deal... Hör zu, Matrose, ich nehme an, dass du bist "+GetSexPhrase("starker Kumpel","geschicktes Mädchen")+". Möchtest du einige Münzen verdienen? Wir werden alle von dem Geschäft profitieren.";
			link.l1 = "Ich will immer. Was ist der Deal?";
			link.l1.go = "Step_3";
		break;
			
		case "Step_3":
			dialog.text = "Ich kann einige interessante Informationen mit dir teilen. Ich brauche es nicht, ich werde es nicht rechtzeitig schaffen, dank unseres gemeinsamen Freundes, aber du könntest es nützlich finden. Nicht umsonst.";
			link.l1 = "Wie viel?";
			if (hrand(2) == 0) link.l1.go = "Step_4";
			else link.l1.go = "Step_4d";
		break;
		
		case "Step_4":
			iTotalTemp = 0;
			dialog.text = "Fünfzigtausend Pesos.";
			if(makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Hm, ziemlich teuer. Aber ich stimme zu, wenn das Geschäft es wert ist. Ich bin dabei! Gib mir die Details.";
				link.l1.go = "Step_5";
			}
			link.l2 = "Nicht interessiert.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_4d":
			iTotalTemp = 250+hrand(25)*10;
			dialog.text = ""+FindRussianDublonString(iTotalTemp)+". Keinen einzigen Taler weniger!";
			if (GetCharacterItem(pchar, "gold_dublon") >= iTotalTemp)
			{
				link.l1 = "Hm, ziemlich teuer. Aber ich stimme zu, wenn das Geschäft es wert ist. Ich bin dabei! Gib mir die Details.";
				link.l1.go = "Step_5";
			}
			link.l2 = "Nicht interessiert.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://попытка грабежа
					dialog.text = "Nun-nun, was auch immer, "+GetSexPhrase("du wurdest getäuscht, du Trottel","du wurdest getäuscht, du dummes Mädchen")+". Jetzt zahlen, bar auf die Hand!";
					link.l1 = "Verpiss dich zum Teufel mit einem Anker... Dein Freund hat mir gesagt, dass seine Kumpels großzügig sind!";
					link.l1.go = "Step_fight";
				break;
				
				case 1://кидалово
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					dialog.text = "Gut, hör zu. Mir wurde mitgeteilt, dass in "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" nicht weit von "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" es wird zwei geben "+pchar.questTemp.jailCanMove.Deliver.add1+" Handelsschiffe - die "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" und der "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" mit ihren Frachträumen voll von "+pchar.questTemp.jailCanMove.Deliver.add+". Du kannst versuchen, sie zu fangen.";
					link.l1 = "Prächtig! Es sieht so aus, als hätte ich recht gehabt, Münzen mit dir zu teilen.";
					link.l1.go = "Step_lay";
				break;
				
				case 2://наведем на торговый корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					
					dialog.text = "Gut, hör zu. Mir wurde mitgeteilt, dass in "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" nicht weit von "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" es wird zwei geben "+pchar.questTemp.jailCanMove.Deliver.add1+" Handelsschiffe - die "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" und der "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" mit ihren Laderäumen voll mit "+pchar.questTemp.jailCanMove.Deliver.add+". Du kannst versuchen, sie zu fangen.";
					link.l1 = "Prächtig! Es sieht so aus, als hätte ich recht gehabt, Münzen mit dir zu teilen.";
					link.l1.go = "Step_trader";
				break;
				
				case 3://наведем на курьерский корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "Gut, hör zu. Mir wurde mitgeteilt, dass in "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" nicht weit von "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" wird ein Kurier-Lugger segeln "+pchar.questTemp.jailCanMove.Deliver.add2+" genannt "+pchar.questTemp.jailCanMove.Deliver.ShipName+". Es gibt viele Juwelen darauf. Du kannst versuchen, sie zu fangen.";
					link.l1 = "Prächtig! Es scheint, dass ich recht hatte, Münzen mit dir zu teilen.";
					link.l1.go = "Step_cureer";
				break;
			}
		break;
			
		case "Step_fight":
			dialog.text = "Wenn er nicht so dumm gewesen wäre, würde er jetzt seinen Rum in einer Kneipe trinken und nicht in den Kasematten sitzen. Also alle Beschwerden gehen an ihn, ha-ha! Jetzt gib mir dein Geld oder du kommst hier nicht lebend weg.";
			link.l1 = "Bist du dir da so sicher, Narr?";
			link.l1.go = "quest_fight";
			link.l2 = "Gut, nimm deine Münzen... Ich bin in der Unterzahl...";
			link.l2.go = "Step_takemoney";
		break;
		
		case "Step_takemoney":
			dialog.text = "Gut gemacht, "+GetSexPhrase("Kumpel","Mädchen")+". Unser gemeinsamer Freund wird sie dir zurückgeben, ha-ha... sobald er tot ist. Verschwinde. Leise.";
			link.l1 = "Verfluche dich!";
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
			dialog.text = "Sicher... Was auch immer, jetzt geh, leise.";
			link.l1 = "Auf Wiedersehen.";
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
			dialog.text = "Sicher... Was auch immer, jetzt geh, leise.";
			link.l1 = "Auf Wiedersehen.";
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
			dialog.text = "Sicher... Was auch immer, jetzt geh, leise.";
			link.l1 = "Auf Wiedersehen.";
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
			dialog.text = "Was auch immer. Geh jetzt, wir haben nichts mit dir zu besprechen.";
			link.l1 = "Gut, lebe wohl.";
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
			dialog.text = "Was willst du noch? Ich habe dir schon gesagt, dass du verschwinden sollst.";
			link.l1 = "Gut, ich bin auf dem Weg...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Man_FackYou":
			dialog.text = "Willst du erstochen werden, "+GetSexPhrase("Tölpel","dummes Mädchen")+"Was?!";
			link.l1 = LinkRandPhrase("Teufel!","Verdammt!","Verdammt!");
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
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = GetConvertStr(pchar.questTemp.jailCanMove.Deliver.Island, "LocLables.txt") + "");
	}
	else
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = XI_ConvertString("Colony" + pchar.questTemp.jailCanMove.Deliver.Island.Town + "Gen");
	}
}

void GetBandersTradeGoods()//выберем товар для торгашей
{
	switch (rand(6))
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
		
		case 6:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_WEAPON;
			pchar.questTemp.jailCanMove.Deliver.add = "weapons";
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
