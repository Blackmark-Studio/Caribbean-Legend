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
			dialog.text = "Chi diavolo sei tu?";
			link.l1 = "Silenzio, calmati. Il tuo compagno incarcerato di nome "+pchar.questTemp.jailCanMove.Deliver.name+" mi ha mandato qui, lo conosci?";
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Step_1":
			dialog.text = "Hai forse qualche prova che non sei uno dei segugi del governatore?";
			link.l1 = "Mi ha chiesto di consegnare un messaggio. Ecco qui.";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		
		case "Step_2":
			dialog.text = "Vediamo un po'...(leggendo). Maledizione! Che momentaccio per farsi beccare... Dannazione, che razza d'affare... Senti, marinaio, suppongo che tu sia "+GetSexPhrase("vecchio lupo","ragazza abile")+" Vuoi guadagnare qualche moneta? Tutti ci guadagneremo da questo affare.";
			link.l1 = "Lo voglio sempre, dannazione. Qual è il gioco stavolta?";
			link.l1.go = "Step_3";
		break;
			
		case "Step_3":
			dialog.text = "Posso raccontarti qualcosa di interessante. A me non serve, non arriverò mai in tempo grazie al nostro amico comune, ma potrebbe tornarti utile. Però non è gratis.";
			link.l1 = "Quanto vuoi?";
			if (hrand(2) == 0) link.l1.go = "Step_4";
			else link.l1.go = "Step_4d";
		break;
		
		case "Step_4":
			iTotalTemp = 0;
			dialog.text = "Cinquanta mila pesos.";
			if(makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Hm, piuttosto salato il prezzo. Ma dico di sì, se l'affare ne vale la pena. Ci sto! Dammi i dettagli.";
				link.l1.go = "Step_5";
			}
			link.l2 = "Non m’interessa.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_4d":
			iTotalTemp = 250+hrand(25)*10;
			dialog.text = ""+FindRussianDublonString(iTotalTemp)+". Non un solo doblone di meno!";
			if (GetCharacterItem(pchar, "gold_dublon") >= iTotalTemp)
			{
				link.l1 = "Hm, piuttosto salato. Ma se l'affare ne vale la pena, ci sto! Dammi i dettagli.";
				link.l1.go = "Step_5";
			}
			link.l2 = "Non mi interessa.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://попытка грабежа
					dialog.text = "Ebbene, ebbene, poco importa, "+GetSexPhrase("ti hanno gabbato, stolto","sei stata ingannata, stupida ragazza")+". Ora paga, subito e in contanti!";
					link.l1 = "Vaffanculo con un'ancora... Il tuo compare mi ha detto che i suoi amici sono generosi!";
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
					dialog.text = "D'accordo, ascolta. Mi hanno riferito che in "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" non lontano da "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" ce ne saranno due "+pchar.questTemp.jailCanMove.Deliver.add1+" navi mercantili - le "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" e il "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" con le stive cariche di "+pchar.questTemp.jailCanMove.Deliver.add+". Puoi provare ad acchiapparli.";
					link.l1 = "Splendido! Pare proprio che non mi sia sbagliato a spartire il bottino con te.";
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
					
					dialog.text = "Va bene, ascolta. Mi hanno detto che a "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" non lontano da "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" ce ne saranno due "+pchar.questTemp.jailCanMove.Deliver.add1+" navi mercantili - le "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" e il "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" con le stive colme di "+pchar.questTemp.jailCanMove.Deliver.add+". Puoi provare ad acciuffarli.";
					link.l1 = "Splendido! Pare proprio che ci abbia visto giusto a spartire il bottino con te.";
					link.l1.go = "Step_trader";
				break;
				
				case 3://наведем на курьерский корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "Bene, ascolta. Mi hanno informato che a "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" non lontano da "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" navigherà su una lugger corriera "+pchar.questTemp.jailCanMove.Deliver.add2+" chiamato "+pchar.questTemp.jailCanMove.Deliver.ShipName+". Ci sono molti gioielli lì sopra. Puoi provare a catturarla.";
					link.l1 = "Splendido! Pare proprio che ho fatto bene a spartire le monete con te.";
					link.l1.go = "Step_cureer";
				break;
			}
		break;
			
		case "Step_fight":
			dialog.text = "Se non fosse stato così sciocco, a quest’ora starebbe tracannando il suo rum in una taverna, invece di marcire nei sotterranei! Quindi tutte le lamentele a lui, ah-ah! Ora dammi il tuo bottino, oppure di qui non te ne vai vivo.";
			link.l1 = "Ne sei così sicuro, buffone?";
			link.l1.go = "quest_fight";
			link.l2 = "Va bene, prendi le tue monete... Siete in troppi per me...";
			link.l2.go = "Step_takemoney";
		break;
		
		case "Step_takemoney":
			dialog.text = "Ben fatto, "+GetSexPhrase("compare","fanciulla")+". Il nostro comune compare te li restituirà, ah-ah... quando sarà morto. Sparisci. In silenzio.";
			link.l1 = "Maledetto tu sia!";
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
			dialog.text = "Certo... Come vuoi, adesso sparisci in silenzio.";
			link.l1 = "Addio.";
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
			dialog.text = "Certo... Va' pure, ma senza far rumore.";
			link.l1 = "Addio.";
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
			dialog.text = "Certo... Va bene, adesso sparisci, in silenzio.";
			link.l1 = "Addio.";
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
			dialog.text = "Come vuoi. Ora vattene, non abbiamo altro da dirti.";
			link.l1 = "Va bene, addio.";
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
			dialog.text = "Cos'altro vuoi? Ti ho già detto di sparire.";
			link.l1 = "Va bene, sto andando...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Man_FackYou":
			dialog.text = "Vuoi buscarti una coltellata, "+GetSexPhrase(" damerino ","ragazza stupida")+"?! ";
			link.l1 = LinkRandPhrase("Diavolo!","Carramba!","Maledizione!");
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
