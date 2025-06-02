///////////////////////////////////////////////////////////////////////////////////////////////////////
///Jason--------------------------------------- Регата ----------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////
void PrepareToRegata(string qName)
{
	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	sld = GetCharacter(NPC_GenerateCharacter("RegataCureer", "off_eng_2", "man", "man", 20, ENGLAND, 1, false, "quest"));
    sld.Dialog.Filename = "Quest\Regata_dialog.c";
	sld.dialog.currentnode = "Regata_Cureer";
	LAi_SetImmortal(sld, true);
    FantomMakeCoolFighter(sld, 20, 20, 20, "blade_11", "pistol3", "grapeshot", 50);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.Regata.CureerCity+"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PrepareToRegataInPortroyal(string qName)//создаем распорядителя регаты
{
	sld = GetCharacter(NPC_GenerateCharacter("RegataHead", "off_eng_5", "man", "man", 20, ENGLAND, -1, false, "quest"));
    sld.Dialog.Filename = "Quest\Regata_dialog.c";
	sld.dialog.currentnode = "Regata_Head";
	sld.name = StringFromKey("Regatta_1");
	sld.lastname = StringFromKey("Regatta_2");
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
    FantomMakeCoolFighter(sld, 90, 90, 90, "blade_11", "pistol3", "grapeshot", 50);
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "Portroyal_Roomtownhall", "sit", "sit2");
}

void Regata_SetCitizen()//оптимизация - установка ситизенов и распорядителя
{
	//установим благодарных зрителей
	for (i=1; i <=9; i++)
	{
	sld = GetCharacter(NPC_GenerateCharacter("RegataCitPRMan_"+i, "citiz_"+(rand(9)+11), "man", "man", 10, ENGLAND, 1, false, "quest"));
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	ChangeCharacterAddressGroup(sld, "Portroyal_town", "quest", "quest1");
	LAi_SetStayType(sld);
	//LAi_ActorRunToLocator(sld, "quest", "quest1", "RegataCitPR_norm", -1);
		if (CheckAttribute(pchar, "questTemp.Regata.Prepare"))
		{
		LAi_SetLoginTime(sld, 9.0, 13.0);
		sld.dialog.currentnode = "Regata_CitMan";
		}
		else sld.dialog.currentnode = "Regata_CitMan_1";
	}
	for (i=1; i <=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("RegataCitPRWom_"+i, "women_"+(rand(9)+7), "woman", "towngirl", 5, ENGLAND, 1, false, "quest"));
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	ChangeCharacterAddressGroup(sld, "Portroyal_town", "quest", "quest1");
	LAi_SetStayType(sld);
	//LAi_ActorGoToLocator(sld, "quest", "quest1", "RegataCitPR_norm", -1);
		if (CheckAttribute(pchar, "questTemp.Regata.Prepare"))
		{
		LAi_SetLoginTime(sld, 9.0, 13.0);
		sld.dialog.currentnode = "Regata_CitWom";
		}
		else sld.dialog.currentnode = "Regata_CitWom_1";
	}
	for (i=1; i <=2; i++)
	{
	sld = GetCharacter(NPC_GenerateCharacter("RegataCitPRHor_"+i, "horse0"+(2+i), "woman", "towngirl", 5, ENGLAND, 1, false, "quest"));
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	ChangeCharacterAddressGroup(sld, "Portroyal_town", "quest", "quest1");
	LAi_SetStayType(sld);
	//LAi_ActorGoToLocator(sld, "goto", "goto27", "RegataCitPR_norm", -1);
		if (CheckAttribute(pchar, "questTemp.Regata.Prepare"))
		{
		LAi_SetLoginTime(sld, 9.0, 13.0);
		sld.dialog.currentnode = "Regata_CitHorse";
		}
		else sld.dialog.currentnode = "Regata_CitHorse_1";
	}
	//установим распорядителя регаты
	sld = characterFromId("RegataHead");
	LAi_SetStayType(sld);
	if (CheckAttribute(pchar, "questTemp.Regata.Prepare")) sld.dialog.currentnode = "Regata_Prepare_1";
	else sld.dialog.currentnode = "Regata_Finish";
	ChangeCharacterAddressGroup(sld, "Portroyal_town", "reload", "reload1");
}

void Regata_SetTime(string qName)//подготовка к запуску
{
	log_testinfo("ПРИГОТОВЛЕНИЯ К РЕГАТЕ ПОШЛИ!");
	LocatorReloadEnterDisable("Portroyal_town", "reload1_back", true);//закроем выход в море
	Regata_SetCitizen();//горожане и распорядитель
	//установим тела противников, для антуражу и индикации готовности, без возможности общения
	for (i=1; i<=5; i++)
	{
	sld = GetCharacter(NPC_GenerateCharacter("Regata_Cap_F"+i, "mercen_1"+i, "man", "man", 20, ENGLAND, 1, true, "quest"));
	ChangeCharacterAddressGroup(sld, "Portroyal_town", "reload", "reload1_back");
		LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload1_back", "RegataCapTurn", -1);
	LAi_SetLoginTime(sld, 12.0, 13.0);
	}
	//установим кораблики противников
	Group_FindOrCreateGroup("Regata");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	string sName, sShip;
	for (int i=1; i<=5; i++)
	{
		switch(i)
		{
			case 1:
				sName = pchar.questTemp.Regata.AdversaryName.a;
				sShip = pchar.questTemp.Regata.AdversaryShipName.a;
			break;
			case 2:
				sName = pchar.questTemp.Regata.AdversaryName.b;
				sShip = pchar.questTemp.Regata.AdversaryShipName.b;
			break;
			case 3:
				sName = pchar.questTemp.Regata.AdversaryName.c;
				sShip = pchar.questTemp.Regata.AdversaryShipName.c;
			break;
			case 4:
				sName = pchar.questTemp.Regata.AdversaryName.d;
				sShip = pchar.questTemp.Regata.AdversaryShipName.d;
			break;
			case 5:
				sName = pchar.questTemp.Regata.AdversaryName.e;
				sShip = pchar.questTemp.Regata.AdversaryShipName.e;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Regata_Cap"+i, "mercen_1"+i, "man", "man", iRank, ENGLAND, 1, true, "quest"));
		sld.name = sName;
		sld.lastname = "";
		FantomMakeCoolSailor(sld, SHIP_LUGGER, sShip, CANNON_TYPE_CANNON_LBS3, 90, 60, 60);
		FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_05", "pistol1", "bullet", 100);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetImmortal(sld, true);//иначе несколько точно утонут, теревшись друг о друга
		Group_AddCharacter("Regata", "Regata_Cap"+i);
   }
	Group_SetGroupCommander("Regata", "Regata_Cap1");
	Group_SetTaskRunAway("Regata", PLAYER_GROUP);
	Group_SetPursuitGroup("Regata", PLAYER_GROUP);
	Group_SetAddress("Regata", "Jamaica", "quest_ships", "quest_ship_1");
	Group_LockTask("Regata");
}

void Regata_Lost(string qName)//опоздал к старту
{
	pchar.quest.Regata_Start.over = "yes";//снять прерывание
	DeleteAttribute(pchar, "questTemp.Regata");
	log_info(StringFromKey("Regatta_3"));
	Group_DeleteGroup("Regata");
	LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
	sld = characterFromId("RegataHead");
	LAi_SetHuberType(sld);
	sld.dialog.currentnode = "Regata_Head";
	ChangeCharacterAddressGroup(sld, "Portroyal_Roomtownhall", "sit", "sit2");
	AddQuestRecord("Regata", "45");
	CloseQuestHeader("Regata");
}

void Regata_Start(string qName)//старт регаты
{
	log_testinfo("РЕГАТЕ-СТАРТ!!!");
	//стартовая точка отсчета времени
	pchar.quest.Regata_Lost.over = "yes";//снять прерывание
	pchar.questTemp.Regata.StartYear = GetDataYear();
	pchar.questTemp.Regata.StartMonth = GetDataMonth();
	pchar.questTemp.Regata.StartDay = GetDataDay();
	pchar.questTemp.Regata.StartTime = GetTime();
	for (i=1; i <=5; i++)
	{
		if (i==1) sTemp = "a";
		if (i==2) sTemp = "b";
		if (i==3) sTemp = "c";
		if (i==4) sTemp = "d";
		if (i==5) sTemp = "e";
		pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) = 216*stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp));//время 1 перехода в часах
		pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = 366*stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp));//время 1+2 переходов в часах
		pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = 576*stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp));//время 1+2+3 переходов в часах
		pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = 720*stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp));//время 1+2+3+4 переходов в часах
		pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = 1080*stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp));//время 1+2+3+4+5 переходов в часах
		log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
	}
	pchar.quest.Regata_Check.win_condition.l1 = "location";
	pchar.quest.Regata_Check.win_condition.l1.location = "Beliz";
	pchar.quest.Regata_Check.function = "RegataCheck";//проверка
	//распорядитель даёт отмашку
	sld = characterFromId("RegataHead");
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "Regata_Start";
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void ReturnJamaicaNorm(string qName)//вертаем остров в норму
{
	Island_SetReloadEnableGlobal("Jamaica", true);
	sld = characterFromId("RegataHead");
	LAi_SetHuberType(sld);
	sld.dialog.currentnode = "Regata_Head";
	ChangeCharacterAddressGroup(sld, "Portroyal_Roomtownhall", "sit", "sit2");
	DeleteAttribute(pchar, "questTemp.Regata.Prepare");
}

void RegataCheck(string qName)//проверку ставим в локации острова, чтобы не жульничал
{
	// belamour legendary edition допуск курьерского люггера -->
	bOk = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
	log_testinfo("ПРОВЕРКА ПРАВИЛЬНОСТИ!!!");
	if ((GetCompanionQuantity(pchar) > 1) || !bOk || pchar.Ship.Name != StringFromKey("Regatta_4")) pchar.questTemp.Regata.Breach = "true";
	// <-- legendary edition
}

void RegataPU_Open(string qName)//телепорт в ПУ, если ночь на дворе
{
	PlaySound("Interface\knock.wav");
	DoQuestReloadToLocation(pchar.questTemp.Regata.Town+"_portoffice", "reload", "reload1", "");
}

void RegataTH_Open(string qName) // belamour резиденция ночью
{
	PlaySound("Interface\knock.wav");
	DoQuestReloadToLocation("bridgetown_townhall", "reload", "reload1", "");
}

void RegataShipyarder(string qName)//верфист с парусами в Белизе
{
	bDisableFastReload = true;
	chrDisableReloadToLocation = true;
	sld = characterFromId("Beliz_shipyarder");
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
	sld.dialog.currentnode = "Regata_Shipyarder";
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, "Beliz_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Contra_Regata(string qName)//контрики с пушками в Порт Принсе
{
	for (i=1; i<=2; i++)
	{
	sld = GetCharacter(NPC_GenerateCharacter("RegataContra_"+i, "citiz_"+(46+i), "man", "man", 20, FRANCE, 1, false, "quest"));
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
	sld.dialog.currentnode = "Regata_Contra";
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	if (i == 2) LAi_CharacterDisableDialog(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, "Portpax_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Padre_Regata(string qName)//падре в Сент-Джонсе
{
	bDisableFastReload = true;
	chrDisableReloadToLocation = true;
	sld = characterFromId("SentJons_Priest");
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
	sld.dialog.currentnode = "Regata_Padre";
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void RegataSpyglassGirl(string qName)//девушка с подзорной трубой
{
	bDisableFastReload = true;
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("SpyglassGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, ENGLAND, 1, true, "quest"));
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
	sld.dialog.currentnode = "Regata_Spyglass";
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void RegataAttack_Hunter(string qName)//атака ДУ
{
	CoolTraderHunterOnMap();
}

void RegataAttack_Lugger(string qName)//засада из 2 люггеров
{
	Group_DeleteGroup("Lugger_Attack");
	Group_FindOrCreateGroup("Lugger_Attack");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 5*sti(pchar.rank);
	int iNation = sti(pchar.questTemp.Regata.AttackNation);
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Lugger_CapAttack_"+i, "mercen_"+(rand(27)+1), "man", "man", iRank, iNation, 5, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_LUGGER, "", CANNON_TYPE_CANNON_LBS6, 100, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_05", "pistol1", "bullet", 100);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		UpgradeShipParameter(sld, "SpeedRate");
		if (hrand(3) == i) UpgradeShipParameter(sld, "WindAgainstSpeed");
		Character_SetAbordageEnable(sld, false); //нельзя абордировать
		Group_AddCharacter("Lugger_Attack", "Lugger_CapAttack_"+i);
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.AnalizeShips = true;
    }
	Group_SetGroupCommander("Lugger_Attack", "Lugger_CapAttack_1");
	Group_SetTaskAttack("Lugger_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Lugger_Attack", PLAYER_GROUP);
	Group_SetAddress("Lugger_Attack", pchar.questTemp.Regata.AttackIsland, "", "");
	Group_LockTask("Lugger_Attack");
}

void RegataAttack_Corvette(string qName)//засада - корвет
{
	Group_DeleteGroup("Corvette_Attack");
	Group_FindOrCreateGroup("Corvette_Attack");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 7*sti(pchar.rank);
	int iNation = sti(pchar.questTemp.Regata.AttackNation);
		sld = GetCharacter(NPC_GenerateCharacter("Corvette_CapAttack_1", "mercen_"+(rand(27)+1), "man", "man", iRank, iNation, 5, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_CORVETTE, "", CANNON_TYPE_CANNON_LBS20, 100, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_10", "pistol1", "bullet", 100);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		UpgradeShipParameter(sld, "SpeedRate");
		if (hrand(3) == 0) UpgradeShipParameter(sld, "Capacity");
		Character_SetAbordageEnable(sld, false); //нельзя абордировать
		Group_AddCharacter("Corvette_Attack", "Corvette_CapAttack_1");
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.AnalizeShips = true;
	Group_SetGroupCommander("Corvette_Attack", "Corvette_CapAttack_1");
	Group_SetTaskAttack("Corvette_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Corvette_Attack", PLAYER_GROUP);
	Group_SetAddress("Corvette_Attack", pchar.questTemp.Regata.AttackIsland, "", "");
	Group_LockTask("Corvette_Attack");
}

void RegataAttack_Brigantine(string qName)//засада - бригантина
{
	Group_DeleteGroup("Brigantine_Attack");
	Group_FindOrCreateGroup("Brigantine_Attack");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 10*sti(pchar.rank);
	int iNation = sti(pchar.questTemp.Regata.AttackNation);
		sld = GetCharacter(NPC_GenerateCharacter("Brigantine_CapAttack_1", "mercen_"+(rand(27)+1), "man", "man", iRank, iNation, 5, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "", CANNON_TYPE_CANNON_LBS12, 100, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_10", "pistol1", "bullet", 100);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		UpgradeShipParameter(sld, "SpeedRate");
		if (hrand(1) == 0) UpgradeShipParameter(sld, "Capacity");
		else UpgradeShipParameter(sld, "WindAgainstSpeed");
		Character_SetAbordageEnable(sld, false); //нельзя абордировать
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.AnalizeShips = true;
		Group_AddCharacter("Brigantine_Attack", "Brigantine_CapAttack_1");
	Group_SetGroupCommander("Brigantine_Attack", "Brigantine_CapAttack_1");
	Group_SetTaskAttack("Brigantine_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Brigantine_Attack", PLAYER_GROUP);
	Group_SetAddress("Brigantine_Attack", pchar.questTemp.Regata.AttackIsland, "", "");
	Group_LockTask("Brigantine_Attack");
}

void RegataAttack_Brander(string qName)//люггер-брандер
{
	Island_SetReloadEnableGlobal("Antigua", false);//на остров нельзя			
	bQuestDisableMapEnter = true;//на глобалку тоже
	Group_DeleteGroup("Brander_Attack");
	Group_FindOrCreateGroup("Brander_Attack");
	sTemp = pchar.questTemp.Regata.BranderName;
	sld = GetCharacter(NPC_GenerateCharacter("Brander_CapAttack_1", "mercen_"+(rand(27)+1), "man", "man", 30, ENGLAND, 5, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LUGGER, sTemp, CANNON_TYPE_CANNON_LBS3, 100, 10, 10);
	SetShipSkill(sld, 30, 10, 10, 10, 100, 10, 10, 10, 10);//дополнительно
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	UpgradeShipParameter(sld, "SpeedRate");
	UpgradeShipParameter(sld, "Capacity");
	UpgradeShipParameter(sld, "WindAgainstSpeed");
	UpgradeShipParameter(sld, "TurnRate");
	Character_SetAbordageEnable(sld, false); //нельзя абордировать
	sld.DontDeskTalk = true; //шлюпку не выслать
	sld.Coastal_Captain = true;
	SetCharacterGoods(sld, GOOD_BALLS, 0);
	SetCharacterGoods(sld, GOOD_BOMBS, 0);
	SetCharacterGoods(sld, GOOD_SAILCLOTH, 0);
	SetCharacterGoods(sld, GOOD_PLANKS, 0);
	SetCharacterGoods(sld, GOOD_RUM, 0);
	SetCharacterGoods(sld, GOOD_POWDER, 250);
	Group_AddCharacter("Brander_Attack", "Brander_CapAttack_1");
	Group_SetGroupCommander("Brander_Attack", "Brander_CapAttack_1");
	Group_SetAddress("Brander_Attack", "Antigua", "IslandShips1", "ship_5");
	Ship_SetTaskMove(SECONDARY_TASK, sti(sld.Index), -1548.87, 559.55);
	DoQuestFunctionDelay("BranderGo", 5.0);
}

void BranderGo(string qName)//относится к функции выше - таск брандера не действует на дрейфующий корабль
{
	sld = characterFromId("Brander_CapAttack_1");
	Ship_SetTaskBrander(SECONDARY_TASK, sti(sld.Index), GetMainCharacterIndex());
	sld.ShipTaskLock = true;
	pchar.quest.Brander_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Brander_AfterBattle.win_condition.l1.group = "Brander_Attack";
	pchar.quest.Brander_AfterBattle.function = "BranderDestroyed";
}

void BranderDestroyed(string qName)//брандер капут
{
	Group_DeleteGroup("Brander_Attack");
	Island_SetReloadEnableGlobal("Antigua", true);		
	bQuestDisableMapEnter = false;
}

void RegataSiege(string qName)//создаем осаду ручками, ибо CreateSiege() тут не совсем годится
{
	Group_DeleteGroup("Siege_Attack");
	Group_FindOrCreateGroup("Siege_Attack");
	for (int i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Siege_CapAttack_"+i, "off_spa_"+(rand(1)+1), "man", "man", 40-(i*2), SPAIN, -1, true, "quest"));
		switch (i)
		{
			case 1: FantomMakeCoolSailor(sld, SHIP_LINESHIP, "", CANNON_TYPE_CANNON_LBS32, 100, 100, 100); break;
		case 2:
				FantomMakeCoolSailor(sld, SHIP_LINESHIP, "", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
		LAi_SetImmortal(sld, true);//защита от дурака
		Character_SetAbordageEnable(sld, false); //нельзя абордировать
		break;
			case 3: FantomMakeCoolSailor(sld, SHIP_GALEON_H, "", CANNON_TYPE_CANNON_LBS32, 100, 100, 100); break;
			case 4: FantomMakeCoolSailor(sld, SHIP_GALEON_H, "", CANNON_TYPE_CANNON_LBS24, 100, 100, 100); break;
			case 5: FantomMakeCoolSailor(sld, SHIP_GALEON_H, "", CANNON_TYPE_CANNON_LBS24, 100, 100, 100); break;
		}
		FantomMakeCoolFighter(sld, 40-(i*2), 100, 100, "blade_13", "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.AlwaysSandbankManeuver = true;
		Group_AddCharacter("Siege_Attack", "Siege_CapAttack_"+i);
    }
	Group_SetGroupCommander("Siege_Attack", "Siege_CapAttack_1");
	Group_SetAddress("Siege_Attack", "Barbados", "quest_ships", "quest_ship_5");
}

void RegataSiegeDelete(string qName)//удалить осаду
{
	Group_DeleteGroup("Siege_Attack");
	for (i=1; i <=5; i++)
	{
		if (GetCharacterIndex("Siege_CapAttack_"+i) != -1)
		{
		sld = characterFromId("Siege_CapAttack_"+i);
		sld.lifeday = 0;
		}
	}
}

void RegataSiegeOfficer(string qName)//офицер-вестовой
{
	bDisableFastReload = true;
	LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "reload3_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "gate_back", true);//чтобы не сбежал
	LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", true);//для логики событий
	sld = GetCharacter(NPC_GenerateCharacter("SiegeOfficer", "off_eng_1", "man", "man", 25, ENGLAND, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 60, 60, "blade_10", "pistol5", "bullet", 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.name = StringFromKey("Regatta_5");
    sld.lastname = StringFromKey("Regatta_6");
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
	sld.dialog.currentnode = "Regata_SiegeOfficer";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz)); 
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto8"); // belamour фикс махойни
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	//поставим горожанок
	for (i=1; i <=9; i++)
	{
	sld = GetCharacter(NPC_GenerateCharacter("RegataBridgWom_"+i, "women_"+(rand(9)+7), "woman", "towngirl", 5, ENGLAND, -1, false, "quest"));
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
	sld.dialog.currentnode = "Regata_BridgWom";
	LAi_SetImmortal(sld, true);//защита от дурака
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "patrol", "patrol17", "RegataBridgWom_norm", -1);
	}
}

void RegataSiegeEvacuation(string qName)//эвакуация на корабль
{
	sld = characterFromId("SiegeOfficer");
	sld.dialog.currentnode = "Regata_SiegeOfficer_4";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CreateSiegeSloop(string qName)//шлюп у мыса
{
	Group_DeleteGroup("Sloop_Attack");
	Group_FindOrCreateGroup("Sloop_Attack");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 5*sti(pchar.rank);
	sld = GetCharacter(NPC_GenerateCharacter("Sloop_CapAttack", "off_spa_"+(rand(1)+1), "man", "man", iRank, SPAIN, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_SLOOP, "", CANNON_TYPE_CANNON_LBS12, 100, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_10", "pistol1", "bullet", 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	UpgradeShipParameter(sld, "SpeedRate");
	UpgradeShipParameter(sld, "WindAgainstSpeed");
	Group_AddCharacter("Sloop_Attack", "Sloop_CapAttack");
	sld.AlwaysEnemy = true;
	sld.Coastal_Captain = true;
	sld.AnalizeShips = true;
	Group_SetGroupCommander("Sloop_Attack", "Sloop_CapAttack");
	Group_SetTaskAttack("Sloop_Attack", PLAYER_GROUP);
	Group_SetAddress("Sloop_Attack", "Barbados", "quest_ships", "quest_ship_9");
	Group_LockTask("Sloop_Attack");
}

void RegataSiegeShore(string qName)//бой в бухте
{
	chrDisableReloadToLocation = true;
	for (i=1; i <=9; i++)
	{
	sld = characterFromId("RegataBridgWom_"+i);
	ChangeCharacterAddressGroup(sld, "Shore4", "goto", "goto10");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto4", "RegataBridgWom_norm", -1);
	}
	sld = characterFromId("SiegeOfficer");
	sld.dialog.currentnode = "Regata_SiegeOfficer_6";
	LAi_SetWarriorType(sld);
	LAi_warrior_DialogEnable(sld, true);
	ChangeCharacterAddressGroup(sld, "Shore4", "goto", "goto8");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i <=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Spa_shore_sold_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 20, SPAIN, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 20, 60, 60, "blade_10", "pistol1", "bullet", 100);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, "Shore4", "goto", "goto"+(15+i));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = GetCharacter(NPC_GenerateCharacter("Spa_shore_off", "off_spa_"+(rand(1)+1), "man", "man", 25, SPAIN, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 60, 60, "blade_10", "pistol5", "bullet", 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	ChangeCharacterAddressGroup(sld, "Shore4", "goto", "goto19");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "RegataShoreAfterBattle");
}

void RegataBarbadosCave(string qName)//в пещере
{
	LocatorReloadEnterDisable("Barbados_cave", "reload1", true);
	if (GetCharacterIndex("SiegeOfficer") != -1)
	{
	sld = characterFromId("SiegeOfficer");
	sld.dialog.currentnode = "Regata_SiegeOfficer_8";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	ChangeCharacterAddressGroup(sld, "Barbados_cave", "monsters", "monster10");
	}
	else
	{
		sld = characterFromId("RegataBridgWom_1");
		sld.dialog.currentnode = "Regata_BridgWom_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		ChangeCharacterAddressGroup(sld, "Barbados_cave", "monsters", "monster10");
	}
	for (i=2; i <=9; i++)
	{
	sld = characterFromId("RegataBridgWom_"+i);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Barbados_cave", "monsters", "monster37");
	LAi_ActorRunToLocator(sld, "reload", "reload1", "", 30);
	}
}

void RegataSiegeSkiper()//Вудро в церкви
{
	sld = GetCharacter(NPC_GenerateCharacter("SiegeSkiper", "Doggerty", "man", "man", 30, ENGLAND, 2, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 10, 10, "blade_10", "pistol5", "bullet", 10);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	SetShipSkill(sld, 35, 15, 24, 30, 100, 35, 20, 60, 40);
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "SailingProfessional");
	sld.CompanionDisable = true;
	sld.name = StringFromKey("Regatta_7");
    sld.lastname = StringFromKey("Regatta_8");
	sld.Dialog.Filename = "Quest\Regata_dialog.c";
	sld.dialog.currentnode = "Regata_SiegeSkiper";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Bridgetown_church", "goto", "goto1");
	LAi_SetStayType(sld);
}

void SiegeSkiperOver(string qName)//время службы Вудро истекло
{
	if (IsEntity(&worldMap) || bSeaActive) 
	{
	pchar.quest.Remove_Vudro.win_condition.l1 = "Location_Type";
	pchar.quest.Remove_Vudro.win_condition.l1.location_type = "town";
	pchar.quest.Remove_Vudro.function = "RemoveSiegeSkiper";
	}
	else
	{
	Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
	sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
    DeleteAttribute(sld, "Payment");
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
	log_info(StringFromKey("Regatta_9"));
		PlaySound("interface\notebook.wav");
	}
}

void RemoveSiegeSkiper(string qName)//удалить Вудро
{
	Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
	sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
    DeleteAttribute(sld, "Payment");
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
	log_info(StringFromKey("Regatta_9"));
	PlaySound("interface\notebook.wav");
}

void RegataFinishSea(string qName)//здесь пересчитаем время для установки кораблей соперников
{
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	Group_FindOrCreateGroup("Regata");
	int n=0;
	pchar.questTemp.Regata.FifthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на всю регату
	for (i=1; i <=5; i++)
	{
		if (i==1) sTemp = "a";
		if (i==2) sTemp = "b";
		if (i==3) sTemp = "c";
		if (i==4) sTemp = "d";
		if (i==5) sTemp = "e";
		if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
	}
	if (n != 0)
	{
		for (int i=1; i <=n; i++)
		{
			if (i==1) sTemp = "a";
			if (i==2) sTemp = "b";
			if (i==3) sTemp = "c";
			if (i==4) sTemp = "d";
			if (i==5) sTemp = "e";
			sld = GetCharacter(NPC_GenerateCharacter("Regata_Cap"+i, "mercen_1"+i, "man", "man", 20, ENGLAND, 1, true, "quest"));
			sld.name = pchar.questTemp.Regata.AdversaryName.(sTemp);
			sld.lastname = "";
			FantomMakeCoolSailor(sld, SHIP_LUGGER, pchar.questTemp.Regata.AdversaryShipName.(sTemp), CANNON_TYPE_CANNON_LBS3, 90, 60, 60);
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_6", "pistol1", "bullet", 100);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetImmortal(sld, true);//иначе несколько точно утонут, теревшись друг о друга
			Group_AddCharacter("Regata", "Regata_Cap"+i);
		}
		Group_SetGroupCommander("Regata", "Regata_Cap1");
		Group_SetAddress("Regata", "Jamaica", "quest_ships", "quest_ship_1");
	}
	Log_TestInfo(FindRussianDaysString(n));
	Log_TestInfo(FindRussianDaysString(sti(pchar.questTemp.Regata.FifthTransitionTime)));
}

void RegataFinishTown(string qName)//финиш на суше
{
	Regata_SetCitizen();//горожане и распорядитель
}

void RegataFinal(string qName)//финальная часть регаты при победе
{
	sld = characterFromId("PortRoyal_Mayor");
	sld.dialog.currentnode = "Regata_Final";
	sld = characterFromId("RegataHead");
	LAi_SetHuberType(sld);
	sld.dialog.currentnode = "Give_advantage";
	ChangeCharacterAddressGroup(sld, "Portroyal_Roomtownhall", "sit", "sit2");
}

void RegataFinalOver(string qName)//зачистка всего связанного с регатой
{
	sld = characterFromId("PortRoyal_Mayor");
	sld.dialog.currentnode = "First time";
	sld = characterFromId("RegataHead");
	sld.dialog.currentnode = "Other_result_repeat";//для мотальщиков времени в локации
	sld.lifeday = 0;
	DeleteAttribute(pchar, "questTemp.Regata");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
///-----------------------------------------регата конец-----------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Regatta_QuestComplete(string sQuestName, string qname)
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////		
//Jason------------------------------------------------регата-------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld;
	int i, n; 
	
	bool condition = true;
	
	if (sQuestName == "RegataCitPR_norm")	
	{
		for (i=1; i <=9; i++)
		{
			sld = characterFromId("RegataCitPRMan_"+i);
			LAi_SetStayType(sld);
		}
		for (i=1; i <=5; i++)
		{
			sld = characterFromId("RegataCitPRWom_"+i);
			LAi_SetStayType(sld);
		}
		for (i=1; i <=2; i++)
		{
			sld = characterFromId("RegataCitPRHor_"+i);
			LAi_SetStayType(sld);
		}
	}
	else if (sQuestName == "RegataCapTurn")	
	{
		for (i=1; i <=5; i++)
		{
			sld = characterFromId("Regata_Cap_F"+i);
			LAi_ActorTurnToLocator(sld, "goto", "goto29");
		}
	}
	else if (sQuestName == "ReturnRegataSYNorm")	
	{
		sld = characterFromId("Beliz_shipyarder");
		LAi_SetLoginTime(sld, 6.0, 21.99);
		LAi_SetHuberType(sld);
		sld.Dialog.Filename = "Common_Shipyard.c";
		sld.dialog.currentnode = "First time";
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "ReturnRegataPadreNorm")	
	{
		sld = characterFromId("SentJons_Priest");
		LAi_SetLoginTime(sld, 6.0, 21.99);
		LAi_SetPriestType(sld);
		sld.Dialog.Filename = "Common_church.c";
		sld.dialog.currentnode = "First time";
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "RegataSiegeHover")
	{
		LocatorReloadEnterDisable("Bridgetown_town", "reload3_back", false);
		// belamour открыть резиденцию ночью
		pchar.quest.Regata_TH.win_condition.l1 = "locator";
		pchar.quest.Regata_TH.win_condition.l1.location = "Bridgetown_town";
		pchar.quest.Regata_TH.win_condition.l1.locator_group = "reload";
		pchar.quest.Regata_TH.win_condition.l1.locator = "reload3_back"; 
		pchar.quest.Regata_TH.win_condition.l2 = "Night";
		pchar.quest.Regata_TH.function = "RegataTH_Open";
		
		sld = characterFromId("Bridgetown_Mayor");
		sld.Dialog.Filename = "Quest\Regata_dialog.c";
		sld.dialog.currentnode = "Regata_Hovernor";
	}
	else if (sQuestName == "RegataBridgWom_norm")	
	{
		for (i=1; i <=9; i++)
		{
			sld = characterFromId("RegataBridgWom_"+i);
			LAi_SetStayType(sld);
		}
	}
	else if (sQuestName == "RegataSiegeOpen")
	{
		ref shTo;
		WaitDate("", 0, 0, 0, 2, 0);
		log_info(StringFromKey("Regatta_10"));
		log_info(StringFromKey("Regatta_11"));
		bDisableFastReload = false;
		LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
		LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
		bQuestDisableMapEnter = true;//глобу закрыть
		//установить радиус доплыть до на остров, чтобы ручками порулил корабликом
		n = FindIsland("Barbados");
		Islands[n].EffectRadius = 500;
		//запоминаем и снижаем скорость и манёвренность
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		pchar.questTemp.Regata.Shipspeed = shTo.SpeedRate;
		pchar.questTemp.Regata.Shipturnrate = shTo.TurnRate;
		shTo.SpeedRate = (stf(shTo.SpeedRate)/1.2);
		shTo.TurnRate = (stf(shTo.TurnRate)/1.2);
		pchar.quest.Regata_Siege1.win_condition.l1 = "location";
		pchar.quest.Regata_Siege1.win_condition.l1.location = "Shore4";
		pchar.quest.Regata_Siege1.function = "RegataSiegeShore";
		pchar.quest.Regata_Siege2.win_condition.l1 = "location";
		pchar.quest.Regata_Siege2.win_condition.l1.location = "Barbados";
		pchar.quest.Regata_Siege2.function = "CreateSiegeSloop";
	}
	else if (sQuestName == "RegataShoreAfterBattle")	
	{
		//вертаем корабль и остров в норму
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		shTo.SpeedRate = (stf(pchar.questTemp.Regata.Shipspeed));
		shTo.TurnRate = (stf(pchar.questTemp.Regata.Shipturnrate));
		n = FindIsland("Barbados");	
		DeleteAttribute(Islands[n], "EffectRadius");
		DeleteAttribute(Islands[n], "DontSetShipInPort");
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Shore4", "boat", true);
		sld = characterFromId("SiegeOfficer");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
		}
		else
		{
			sld = characterFromId("RegataBridgWom_1");
			sld.dialog.currentnode = "Regata_BridgWom_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	//<-- Регата конец
	else
	{
		condition = false;
	}
	
	return condition;
}