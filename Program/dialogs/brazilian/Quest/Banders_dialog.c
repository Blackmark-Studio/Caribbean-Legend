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
			dialog.text = "Quem diabos é você?";
			link.l1 = "Calma, fique tranquilo. Seu companheiro preso chamado "+pchar.questTemp.jailCanMove.Deliver.name+" me enviou aqui, você o conhece?";
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Step_1":
			dialog.text = "Tem alguma prova de que você não é um dos cães do governador?";
			link.l1 = "Ele me pediu para entregar um bilhete. Aqui está.";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		
		case "Step_2":
			dialog.text = "Vamos ver...(lendo). Droga! Péssima hora pra ser pego... Maldição, que situação... Escuta, marinheiro, imagino que você seja "+GetSexPhrase("amigo forte","garota habilidosa")+". Quer ganhar umas moedas? Todos nós vamos sair ganhando com esse acordo.";
			link.l1 = "Eu sempre quero. Qual é o lance?";
			link.l1.go = "Step_3";
		break;
			
		case "Step_3":
			dialog.text = "Posso compartilhar algumas informações interessantes com você. Eu não preciso delas, não vou conseguir usá-las a tempo, graças ao nosso amigo em comum, mas talvez você ache útil. Não é de graça.";
			link.l1 = "Quanto?";
			if (hrand(2) == 0) link.l1.go = "Step_4";
			else link.l1.go = "Step_4d";
		break;
		
		case "Step_4":
			iTotalTemp = 0;
			dialog.text = "Cinquenta mil pesos.";
			if(makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Hm, bem caro. Mas eu topo, se o negócio valer a pena. Tô dentro! Me conte os detalhes.";
				link.l1.go = "Step_5";
			}
			link.l2 = "Não estou interessado.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_4d":
			iTotalTemp = 250+hrand(25)*10;
			dialog.text = ""+FindRussianDublonString(iTotalTemp)+". Nem uma moeda a menos!";
			if (PCharDublonsTotal() >= iTotalTemp)
			{
				link.l1 = "Hm, bem caro. Mas concordo, se o negócio valer a pena. Estou dentro! Me conte os detalhes.";
				link.l1.go = "Step_5";
			}
			link.l2 = "Não estou interessado.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://попытка грабежа
					dialog.text = "Bom, bom, tanto faz, "+GetSexPhrase("você foi enganado, seu tolo","você foi enganada, sua tola")+". Agora pague, dinheiro na frente!";
					link.l1 = "Vai se ferrar com uma âncora... Seu amigo me disse que os parceiros dele são generosos!";
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
					dialog.text = "Certo, escute. Fiquei sabendo que em "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" não muito longe de "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" haverá dois "+pchar.questTemp.jailCanMove.Deliver.add1+" navios mercantes - os "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" e o "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" com seus porões de carga cheios de "+pchar.questTemp.jailCanMove.Deliver.add+". Você poderia tentar pegá-los.";
					link.l1 = "Excelente! Parece que fiz bem em dividir as moedas com você.";
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
					
					dialog.text = "Certo, escute. Fiquei sabendo que em "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" não muito longe de "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" haverá dois "+pchar.questTemp.jailCanMove.Deliver.add1+" navios mercantes - os "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" e o "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" com seus porões de carga cheios de "+pchar.questTemp.jailCanMove.Deliver.add+". Você poderia tentar pegá-los.";
					link.l1 = "Excelente! Parece que fiz bem em dividir moedas com você.";
					link.l1.go = "Step_trader";
				break;
				
				case 3://наведем на курьерский корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveDublonsFromPCharTotal(iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "Certo, escute. Fiquei sabendo que em "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" não muito longe de "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" vou navegar em uma escuna de correio "+pchar.questTemp.jailCanMove.Deliver.add2+" chamado "+pchar.questTemp.jailCanMove.Deliver.ShipName+". Tem muitas joias nela. Você pode tentar pegá-la.";
					link.l1 = "Excelente! Parece que fiz bem em dividir as moedas com você.";
					link.l1.go = "Step_cureer";
				break;
			}
		break;
			
		case "Step_fight":
			dialog.text = "Se ele não fosse tão tolo, já estaria bebendo seu rum numa taverna, não sentado nas casamatas. Então, reclame com ele, ha-ha! Agora me dê seu dinheiro ou você não sai daqui vivo.";
			link.l1 = "Tem tanta certeza disso, palhaço?";
			link.l1.go = "quest_fight";
			link.l2 = "Tá bom, pega suas moedas... Estou em desvantagem...";
			link.l2.go = "Step_takemoney";
		break;
		
		case "Step_takemoney":
			dialog.text = "Muito bem, "+GetSexPhrase("amigo","garota")+". Nosso amigo em comum vai devolvê-los pra você, ha-ha... assim que ele estiver morto. Cai fora. Em silêncio.";
			link.l1 = "Maldito seja!";
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
			dialog.text = "Certo... Tanto faz, agora vá embora em silêncio.";
			link.l1 = "Adeus.";
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
			dialog.text = "Certo... Tanto faz, agora vá embora em silêncio.";
			link.l1 = "Adeus.";
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
			dialog.text = "Certo... Tanto faz, agora vá embora em silêncio.";
			link.l1 = "Adeus.";
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
			dialog.text = "Tanto faz então. Agora vá, não temos mais nada para conversar com você.";
			link.l1 = "Tudo bem, até logo.";
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
			dialog.text = "O que mais você quer? Já te disse pra cair fora.";
			link.l1 = "Tudo bem, estou indo...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Man_FackYou":
			dialog.text = "Quer levar uma facada, "+GetSexPhrase("fop","garota estúpida")+"?!";
			link.l1 = LinkRandPhrase("Demônio!","Caramba!","Droga!");
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
