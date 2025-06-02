// Addon-2016 Jason, французские миниквесты (ФМК)
void FMQ_SetConditions(string qName) // установка параметров старта
{
	if (CheckAttribute(pchar, "questTemp.Trial"))
	{
		if(CheckAttribute(pchar,"quest.FMQ_SetConditions.over"))
			DeleteAttribute(pchar,"quest.FMQ_SetConditions.over");
			SetFunctionTimerCondition("FMQ_SetConditions", 0, 0, 1, false);
		return;
	}
	if (CheckAttribute(pchar, "questTemp.FMQ.Success")) return;
	// Гваделупа
	pchar.quest.FMQG_start.win_condition.l1 = "location";
	pchar.quest.FMQG_start.win_condition.l1.location = "Baster_town";
	pchar.quest.FMQG_start.win_condition.l2 = "Ship_location";
	pchar.quest.FMQG_start.win_condition.l2.location = "Baster_town";
	pchar.quest.FMQG_start.win_condition.l3 = "Hour";
	pchar.quest.FMQG_start.win_condition.l3.start.hour = 8.00;
	pchar.quest.FMQG_start.win_condition.l3.finish.hour = 15.00;
	pchar.quest.FMQG_start.function = "FMQG_Activation";
	// Мартиника
	pchar.quest.FMQM_start.win_condition.l1 = "location";
	pchar.quest.FMQM_start.win_condition.l1.location = "Fortfrance_town";
	pchar.quest.FMQM_start.win_condition.l2 = "Ship_location";
	pchar.quest.FMQM_start.win_condition.l2.location = "Fortfrance_town";
	pchar.quest.FMQM_start.win_condition.l3 = "Hour";
	pchar.quest.FMQM_start.win_condition.l3.start.hour = 8.00;
	pchar.quest.FMQM_start.win_condition.l3.finish.hour = 20.00;
	pchar.quest.FMQM_start.function = "FMQM_Activation";
	// Сент-Кристофер
	pchar.quest.FMQN_start.win_condition.l1 = "location";
	pchar.quest.FMQN_start.win_condition.l1.location = "Charles_town";
	pchar.quest.FMQN_start.win_condition.l2 = "Ship_location";
	pchar.quest.FMQN_start.win_condition.l2.location = "Charles_town";
	pchar.quest.FMQN_start.win_condition.l3 = "Hour";
	pchar.quest.FMQN_start.win_condition.l3.start.hour = 8.00;
	pchar.quest.FMQN_start.win_condition.l3.finish.hour = 21.00;
	pchar.quest.FMQN_start.function = "FMQN_Activation";
	// Тортуга
	pchar.quest.FMQT_start.win_condition.l1 = "location";
	pchar.quest.FMQT_start.win_condition.l1.location = "Tortuga_town";
	pchar.quest.FMQT_start.win_condition.l2 = "Ship_location";
	pchar.quest.FMQT_start.win_condition.l2.location = "Tortuga_town";
	pchar.quest.FMQT_start.win_condition.l3 = "Hour";
	pchar.quest.FMQT_start.win_condition.l3.start.hour = 10.00;
	pchar.quest.FMQT_start.win_condition.l3.finish.hour = 16.00;
	pchar.quest.FMQT_start.function = "FMQT_Activation";
	// Порт-о-Пренс
	pchar.quest.FMQP_start.win_condition.l1 = "location";
	pchar.quest.FMQP_start.win_condition.l1.location = "Portpax_town";
	pchar.quest.FMQP_start.win_condition.l2 = "Ship_location";
	pchar.quest.FMQP_start.win_condition.l2.location = "Portpax_town";
	pchar.quest.FMQP_start.win_condition.l3 = "Hour";
	pchar.quest.FMQP_start.win_condition.l3.start.hour = 8.00;
	pchar.quest.FMQP_start.win_condition.l3.finish.hour = 22.00;
	pchar.quest.FMQP_start.function = "FMQP_Activation";
	AddMapQuestMarkCity("Baster", false);
	AddMapQuestMarkCity("Fortfrance", false);
	AddMapQuestMarkCity("Charles", false);
	AddMapQuestMarkCity("Tortuga", false);
	AddMapQuestMarkCity("Portpax", false);
	// флаг, он же счетчик
	pchar.questTemp.FMQ.Success = 0;
}

void FMQ_Count() // подсчет успешно выполненных
{
	pchar.questTemp.FMQ.Success = sti(pchar.questTemp.FMQ.Success)+1;
	if (sti(pchar.questTemp.FMQ.Success) == 5) 
	{
		FMQL_Start(); // запуск последнего квеста
		AddMapQuestMarkCity("Fortfrance", false);
	}
}

// --> ФМК-Гваделупа
void FMQG_Activation(string qName) // 
{
	// belamour legendary edition -->
	if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED) return;
	// <-- legendary edition
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	sld = GetCharacter(NPC_GenerateCharacter("FMQG_pass_1", "q_citizen_1", "man", "man", 10, FRANCE, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 10, true);
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Guadeloupe.c";
	sld.Dialog.currentnode = "citizen";
	sld.name = StringFromKey("FMQ_1");
	sld.lastname = StringFromKey("FMQ_2");
	sld.greeting = "Pinett_predlozhenie";
	LAi_SetImmortal(sld, true);
	RemoveAllCharacterItems(sld, true);
	ChangeCharacterAddressGroup(sld, "Baster_town", "quest", "quest1");
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	LAi_SetLoginTime(sld, 8.0, 14.99);
	AddLandQuestMark(sld, "questmarkmain"); // Rebbebion, марка
}

void FMQG_StartLate(string qName) // опоздание
{
	pchar.quest.FMQG_Capster.over = "yes"; //снять прерывание
	pchar.questTemp.FMQG = "fail";
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	AddQuestRecord("FMQ_Guadeloupe", "2");
	CloseQuestHeader("FMQ_Guadeloupe");
}

void FMQG_CapsterBeach(string qName) // на пляже
{
	pchar.quest.FMQG_StartLate.over = "yes"; //снять таймер
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	// горожанин
	sld = characterFromId("FMQG_pass_1");
	sld.Dialog.currentnode = "citizen_9";
	GiveItem2Character(sld, "blade_04");
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "blade_04");
	EquipCharacterbyItem(sld, "pistol1");
	TakeNItems(sld, "bullet", 20);
	TakeNItems(sld, "potion1", 5);
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
	ChangeCharacterAddressGroup(sld, "Shore29", "smugglers", "smuggler01");
	// Rebbebion, теперь будет подбегать
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	AddLandQuestMark(sld, "questmarkmain");
	// испанец
	sld = GetCharacter(NPC_GenerateCharacter("FMQG_pass_2", "off_spa_6", "man", "man", 30, SPAIN, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 30, true);
	sld.name = StringFromKey("FMQ_3");
	sld.lastname = StringFromKey("FMQ_4");
	ChangeCharacterAddressGroup(sld, "Shore29", "smugglers", "smuggler02");
	LAi_SetActorType(sld);
	TakeNItems(sld, "potion2", 2);
	// француз
	sld = GetCharacter(NPC_GenerateCharacter("FMQG_pass_3", "quest_off_franc", "man", "man", 20, FRANCE, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 20, true);
	sld.name = StringFromKey("FMQ_5");
	sld.lastname = StringFromKey("FMQ_6");
	ChangeCharacterAddressGroup(sld, "Shore29", "smugglers", "smuggler03");
	LAi_SetActorType(sld);
	TakeNItems(sld, "potion2", 2);
}

void FMQG_SailingStart(string qName) // вышли в море
{
	LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false);
	AddQuestRecord("FMQ_Guadeloupe", "3");
	pchar.quest.FMQG_SailFinish.win_condition.l1 = "location";
	pchar.quest.FMQG_SailFinish.win_condition.l1.location = "Shore47";
	pchar.quest.FMQG_SailFinish.win_condition.l2 = "Ship_location";
	pchar.quest.FMQG_SailFinish.win_condition.l2.location = "Shore47";
	pchar.quest.FMQG_SailFinish.function = "FMQG_SailingFinish";
	AddMapQuestMarkShore("Shore47", true);
}

void FMQG_SailingLate(string qName) // опоздали к Москитос
{
	AddQuestRecord("FMQ_Guadeloupe", "4");
	pchar.questTemp.FMQG = "late";
}

void FMQG_MutiniActivate(string qName) // закладка бунта
{
	if (IsEntity(&worldMap)) DoQuestFunctionDelay("FMQG_MutiniOnShip", 0.5);
	else
	{
		pchar.quest.FMQG_Mutiny.win_condition.l1 = "MapEnter";
		pchar.quest.FMQG_Mutiny.function = "FMQG_MutiniOnShip";
	}
}

void FMQG_MutiniOnShip(string qName) // бунт
{
	pchar.quest.FMQG_SailFinish.over = "yes";
	pchar.questTemp.FMQG = "mutiny";
	MunityOnShip("ShipMunity");
	DelMapQuestMarkShore("shore47");
}

void FMQG_SailingFinish(string qName) // прибыли в Москитос
{
	float locx, locy, locz;
	pchar.quest.FMQG_SailingLate.over = "yes";
	pchar.quest.FMQG_MutiniActivate.over = "yes";
	pchar.quest.FMQG_Mutiny.over = "yes";
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	for (i=1; i<=3; i++)
	{
		sld = characterFromId("FMQG_pass_"+i);
		RemovePassenger(pchar, sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		if (i == 1)
		{
			sld.Dialog.currentnode = "citizen_12";
			sld.greeting = "Pinett_oplata";
			if (pchar.questTemp.FMQG == "late") sld.Dialog.currentnode = "citizen_12a";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
}

void FMQG_Block(string qName) // блокировка продолжения, если истекли 3 месяца, или 8 ранг
{
	
}

void FMQG_BasterContinue(string qName) // продолжение
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	sld = GetCharacter(NPC_GenerateCharacter("FMQG_cureer", "citiz_12", "man", "man", 10, FRANCE, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 10, true);
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Guadeloupe.c";
	sld.Dialog.currentnode = "cureer";
	RemoveAllCharacterItems(sld, true);
	ChangeCharacterAddressGroup(sld, "Baster_town", "quest", "quest1");
	LAi_SetImmortal(sld, true);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	AddLandQuestMark(sld, "questmarkmain");
}

void FMQG_CreateJuanship(string qName) // ставим корабль дона Хуана
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE-2; // Addon 2016-1 Jason пиратская линейка
	int iScl = 10 + 2*sti(pchar.rank);
	int iCannon = CANNON_TYPE_CANNON_LBS8;
	if (MOD_SKILL_ENEMY_RATE < 4) iCannon = CANNON_TYPE_CANNON_LBS6;
	if (MOD_SKILL_ENEMY_RATE > 6) iCannon = CANNON_TYPE_CANNON_LBS12;
	AddQuestRecord("FMQ_Guadeloupe", "11");
	Group_FindOrCreateGroup("FMQG_shipgroup");
	sld = GetCharacter(NPC_GenerateCharacter("FMQG_Juan", "quest_off_spain", "man", "man", iRank, SPAIN, -1, false, "soldier"));
	FantomMakeSmallSailor(sld, SHIP_SLOOP, StringFromKey("FMQ_7"), iCannon, iScl, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank-5, iScl, iScl, "blade_13", "pistol1", "bullet", iScl*2);
	SetMaxShipStats(sld);
	UpgradeShipParameter(sld, "MaxCrew");
	sld.name = StringFromKey("FMQ_8");
	sld.lastname = StringFromKey("FMQ_9");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.DontHitInStorm = true; // не ломается в шторм
	sld.Ship.Mode = "war";
	Character_SetAbordageEnable(sld, false);
	sld.DontDeskTalk = true;
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	SetSailsColor(sld, 3);
	sld.ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*8+20;
	sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*8+20;
	sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*8+20;
	sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*8+20;
	if (MOD_SKILL_ENEMY_RATE > 6) SetCharacterPerk(sld, "MusketsShoot");
	if(MOD_SKILL_ENEMY_RATE < 9) SetCrewQuantity(sld, GetOptCrewQuantity(sld));
	Group_AddCharacter("FMQG_shipgroup", "FMQG_Juan");
	Group_SetGroupCommander("FMQG_shipgroup", "FMQG_Juan");
	Group_SetTaskNone("FMQG_shipgroup");
	Group_SetAddress("FMQG_shipgroup", "PortoBello", "Islandships1", "ship_2");
	Group_LockTask("FMQG_shipgroup");
	// Rebbebion, теперь можно сразу нападать (правда, удачи сделать это под орудиями форта, лол)
	pchar.quest.FMQG_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.FMQG_AfterBattle.win_condition.l1.group = "FMQG_shipgroup";
	pchar.quest.FMQG_AfterBattle.function = "FMQG_JuanAfterBattle";
	// на отправление в путь
	int i = rand(1)+1;
	pchar.quest.FMQG_Juansail.win_condition.l1 = "Timer";
	pchar.quest.FMQG_Juansail.win_condition.l1.date.hour  = sti(GetTime() + rand(6));
	pchar.quest.FMQG_Juansail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, i);
	pchar.quest.FMQG_Juansail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, i);
	pchar.quest.FMQG_Juansail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, i);
	pchar.quest.FMQG_Juansail.function = "FMQG_ShipJuanSail";
}

void FMQG_ShipJuanFail(string qName) // напал в порту и прибил
{
	pchar.quest.FMQG_Juansail.over = "yes";
	pchar.questTemp.FMQG = "fail";
	AddQuestRecord("FMQ_Guadeloupe", "13");
	CloseQuestHeader("FMQ_Guadeloupe");
}

void FMQG_ShipJuanSail(string qName) // 
{
	if (bSeaActive)
	{
		pchar.quest.FMQG_Juansail1.win_condition.l1 = "ExitFromSea";
		pchar.quest.FMQG_Juansail1.function = "FMQG_ShipJuanToMap";
	}
	else DoQuestFunctionDelay("FMQG_ShipJuanToMap", 1.5);
}

void FMQG_ShipJuanToMap(string qName) // шхуна на карте
{
	pchar.quest.FMQG_Juanfail.over = "yes";
	Group_DelCharacter("FMQG_shipgroup", "FMQG_Juan");
	Group_DeleteGroup("FMQG_shipgroup");
	AddQuestRecord("FMQ_Guadeloupe", "12");
	string sGroup = "Sea_FMQGgroup1";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "war");
	sld = characterFromId("FMQG_Juan");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Alwaysenemy = true;
	sld.Coastal_Captain = true;
	sld.Ship.Mode = "war";
	Character_SetAbordageEnable(sld, true);//можно абордировать
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = StringFromKey("FMQ_10");
	Group_AddCharacter(sGroup, "FMQG_Juan");
	
	Group_SetGroupCommander(sGroup, "FMQG_Juan");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	if(!bImCasual) Map_CreateTrader("Portobello", "Cartahena", "FMQG_Juan", 7);
	else Map_CreateTrader("Portobello", "Cartahena", "FMQG_Juan", 8);
	if(!bImCasual) SetFunctionTimerCondition("FMQG_JuanLost", 0, 0, 10, false);
	else SetFunctionTimerCondition("FMQG_JuanLost", 0, 0, 11, false);
	pchar.quest.FMQG_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.FMQG_AfterBattle.win_condition.l1.group = sGroup;
	pchar.quest.FMQG_AfterBattle.function = "FMQG_JuanAfterBattle";
}

void FMQG_JuanAfterBattle(string qName) // 
{
	pchar.quest.FMQG_JuanLost.over = "yes";
	Group_DeleteGroup("FMQG_shipgroup");
	if (pchar.questTemp.FMQG == "fail") return;
	if (pchar.questTemp.FMQG == "juan_capture")
	{
		Group_DeleteGroup("Sea_FMQGgroup1");
		PlaySound("MUSIC\Victory.mp3");
		AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		bDisableMapEnter = true; // Rebbebion, нет выходу на глобалку
	}
	else
	{
		Group_DeleteGroup("Sea_FMQGgroup1");
		pchar.questTemp.FMQG = "fail";
		AddQuestRecord("FMQ_Guadeloupe", "15");
		CloseQuestHeader("FMQ_Guadeloupe");
	}
}

void FMQG_JuanLost(string qName) // 
{
	pchar.quest.FMQG_AfterBattle.over = "yes";
	Group_DeleteGroup("Sea_FMQGgroup1");
	pchar.questTemp.FMQG = "fail";
	AddQuestRecord("FMQ_Guadeloupe", "15");
	CloseQuestHeader("FMQ_Guadeloupe");
}

void FMQG_ArriveMoskitos(string qName) // 
{
	if (pchar.questTemp.FMQG == "fail") return;
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	sld = GetCharacter(sti(Pchar.questTemp.FMQG.PrisonerIDX));
	ReleasePrisoner(sld);
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Guadeloupe.c";
	sld.Dialog.currentnode = "Juan_2";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void FMQG_PlantationGuards(string qName) // 
{
	int n = 1;
	if (MOD_SKILL_ENEMY_RATE > 4) n = 2;
	int iRank = MOD_SKILL_ENEMY_RATE+7;
	for (int i=1; i<=n; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQG_plant_guard_"+i, "sold_eng_"+i, "man", "man", iRank, ENGLAND, -1, false, "soldier"));
		SetFantomParamFromRank(sld, iRank, true);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
	ChangeCharacterNationReputation(pchar, ENGLAND, -3);
}

void FMQG_Lighthouse(string qName) // на маяке
{
	AddQuestRecord("FMQ_Guadeloupe", "20");
	int i = 1+rand(1);
	SetFunctionTimerCondition("FMQG_KidnappingPrepare", 0, 0, i, false);
	/*int n = FindLocation("Bridgetown_Plantation");
	locations[n].locators_radius.quest.detector2 = 3.5;
	pchar.quest.FMQG_KidnappingInfo.win_condition.l1 = "locator";
	pchar.quest.FMQG_KidnappingInfo.win_condition.l1.location = "Bridgetown_Plantation";
	pchar.quest.FMQG_KidnappingInfo.win_condition.l1.locator_group = "quest";
	pchar.quest.FMQG_KidnappingInfo.win_condition.l1.locator = "detector2";
	pchar.quest.FMQG_KidnappingInfo.function = "FMQG_KidnappingInfo";
	pchar.questTemp.FMQG.Info = "true";*/
}

void FMQG_KidnappingPrepare(string qName) // на маяке
{
	if (pchar.questTemp.FMQG == "fail") return;
	//int iTime = 18+rand(3);
	pchar.quest.FMQG_Kidnapping.win_condition.l1 = "Ship_location";
	pchar.quest.FMQG_Kidnapping.win_condition.l1.location = "Mayak2";
	//pchar.quest.FMQG_Kidnapping.win_condition.l2 = "locator";
	//pchar.quest.FMQG_Kidnapping.win_condition.l2.location = "Bridgetown_Plantation";
	//pchar.quest.FMQG_Kidnapping.win_condition.l2.locator_group = "quest";
	//pchar.quest.FMQG_Kidnapping.win_condition.l2.locator = "detector2";
	pchar.quest.FMQG_Kidnapping.win_condition.l2 = "location";
	pchar.quest.FMQG_Kidnapping.win_condition.l2.location = "Bridgetown_Plantation";
	//pchar.quest.FMQG_Kidnapping.win_condition.l3 = "HardHour";
	//pchar.quest.FMQG_Kidnapping.win_condition.l3.hour = iTime;
	pchar.quest.FMQG_Kidnapping.function = "FMQG_KidnappingPinett";
}

/*void FMQG_KidnappingInfo(string qName) // 
{
	DoQuestCheckDelay("TalkSelf_Quest", 0.1);
	PlaySound("interface\notebook.wav");
}*/

void FMQG_KidnappingPinett(string qName)
{
	chrDisableReloadToLocation = true;
	pchar.GenQuest.BlockTalkSelf = true;
	pchar.GenQuest.CannotWait = true;
	DoQuestFunctionDelay("FMQG_KidnappingPinett_2", 4.0);
}

void FMQG_KidnappingPinett_2(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("FMQG_KidnappingPinett_3", 1.0);
}

void FMQG_KidnappingPinett_3(string qName) // Пинетт вышел
{
	//PlaySound("interface\notebook.wav");
	StartQuestMovie(true, false, true);
	locCameraFromToPos(0.95, 3.19, 41.52, true, 0.80, 1.00, 51.12);
	LAi_SetActorType(pchar);
	iTotalTemp = MOD_SKILL_ENEMY_RATE/2;
	if (iTotalTemp < 2) iTotalTemp = 2;
	int iRank = MOD_SKILL_ENEMY_RATE+3;
	int iScl = 10 + 2*sti(pchar.rank);
	LAi_group_Delete("TmpEnemy");
	LAi_group_Delete("EnemyFight");
	//chrDisableReloadToLocation = true;
	sld = characterFromId("FMQG_pass_1");
	sld.LSC_clan = true;
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "detector3");
	LAi_SetActorType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "FMQG_KidnappingAttack");
	LAi_ActorGoToLocator(sld, "reload", "reload1_back", "FMQG_KidnappingFail", -1);
	AddLandQuestMark(sld, "questmarkmain");
	for (int i=1; i<=iTotalTemp; i++)
	{
		ref chr = GetCharacter(NPC_GenerateCharacter("FMQG_pinett_guard_"+i, "citiz_2"+i, "man", "man", iRank, ENGLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(chr, iRank, iScl, iScl, LinkRandPhrase("blade_10","blade_04","blade_06"), "pistol1", "bullet", iScl*2);
		chr.LSC_clan = true;
		ChangeCharacterAddressGroup(chr, pchar.location, "quest", "detector3");
		LAi_SetActorType(chr);
		LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "FMQG_KidnappingAttack");
		LAi_ActorFollow(chr, sld, "", -1);
	}
	DoQuestFunctionDelay("FMQG_KidnappingPinett_4", 5.0);
}

void FMQG_KidnappingPinett_4(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("FMQG_KidnappingPinett_5", 1.0);
}

void FMQG_KidnappingPinett_5(string qName)
{
	EndQuestMovie();
	locCameraTarget(PChar);
	locCameraFollow();
	LAi_SetPlayerType(pchar);
	DeleteAttribute(pchar, "GenQuest.BlockTalkSelf");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
}

void FMQG_KidnappingSucsess(string qName) // Пинетт на корабле
{
	LocatorReloadEnterDisable("Mayak2", "reload1_back", false);
	AddQuestRecord("FMQ_Guadeloupe", "22");
	sld = characterFromId("FMQG_pass_1");
	LAi_SetActorType(sld);
	sld.location = "none";
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	pchar.questTemp.FMQG = "sucsess";
	AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
	AddMapQuestMarkCity("Baster", false);
}

void FMQG_InCave(string qName) // в пещере Гваделупы
{
	pchar.quest.FMQG_cave1.win_condition.l1 = "location";
	pchar.quest.FMQG_cave1.win_condition.l1.location = "Guadeloupe_CaveEntrance";
	pchar.quest.FMQG_cave1.function = "FMQG_Killers";
}

void FMQG_Killers(string qName) // привет от ростовщика
{
	int n = 2;// Addon 2016-1 Jason пиратская линейка
	if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
	if (MOD_SKILL_ENEMY_RATE < 4) n = 1;
	int iRank = MOD_SKILL_ENEMY_RATE+5;
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // правки релиза
	for (int i=1; i<=n; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQG_killer_"+i, RandPhraseSimple("Killer_1","Killer_5"), "man", "man", iRank, PIRATE, -1, false, "soldier")); // may-16
		FantomMakeCoolFighter(sld, iRank, 30, 30, RandPhraseSimple("blade_04","blade_06"), "pistol1", "bullet", 80);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2_back");
		LAi_SetActorType(sld);
		if (i == 1)
		{
			sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Guadeloupe.c";
			sld.Dialog.currentnode = "killer";
		}
		else LAi_CharacterDisableDialog(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void FMQG_UsurerTimeOut(string qName) // таймер опоздания 61 день
{
	AddQuestRecord("FMQ_Guadeloupe", "28");
	CloseQuestHeader("FMQ_Guadeloupe");
	ChangeCharacterHunterScore(pchar, "frahunter", 50);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeOfficersLoyality("bad_all", 5);
	AddCrewMorale(pchar, -20);
	pchar.quest.FMQG_Juanship.over = "yes";
	if (pchar.questTemp.FMQG == "headhunter_panama")
	{
		DelMapQuestMarkCity("panama");
		DelLandQuestMark(characterFromId("Panama_tavernkeeper"));
	}
	if (pchar.questTemp.FMQG == "headhunter_portobello")
	{
		DelMapQuestMarkCity("PortoBello");
		DelLandQuestMark(characterFromId("PortoBello_tavernkeeper"));
	}
	if (GetCharacterIndex("FMQG_Juan") != -1) // стоит в порту
	{
		sld = characterFromId("FMQG_Juan");
		sld.lifeday = 0;
		Group_DeleteGroup("Sea_FMQGgroup1"); // плывет по карте
	}
	pchar.quest.FMQG_Juanfail.over = "yes";
	pchar.quest.FMQG_Juansail.over = "yes";
	pchar.quest.FMQG_Juansail1.over = "yes";
	pchar.quest.FMQG_JuanToMap.over = "yes";
	if (pchar.questTemp.FMQG == "to_moskitos") // пленник в трюме - в обычные пленники
	{
		pchar.quest.FMQG_SailMoskitos.over = "yes";
		sld = characterFromId(pchar.questTemp.FMQG.PrisonerID);
		sld.Dialog.currentnode = "First time";
		LAi_CharacterEnableDialog(sld);
		DelMapQuestMarkShore("Shore47");
	}
	if (pchar.questTemp.FMQG == "headhunter_pinett") // идёт охота на Пинетта
	{
		sld = characterFromId("FMQG_pass_1");
		sld.lifeday = 0;
		pchar.quest.FMQG_Mayak.over = "yes";
		pchar.quest.FMQG_Kidnapping.over = "yes";
		DelMapQuestMarkCity("bridgetown");
	}
	if (pchar.questTemp.FMQG == "sucsess") // Пинетт захвачен
	{
		sld = characterFromId("FMQG_pass_1");
		RemovePassenger(pchar, sld);
		sld.lifeday = 0;
		AddQuestUserData("FMQ_Guadeloupe", "sAdd", StringFromKey("FMQ_11"));
		DelMapQuestMarkCity("baster");
		DelLandQuestMark(characterFromId("baster_usurer"));
	}
	if (pchar.questTemp.FMQG == "letter") // письмо Пинетта
	{
		ReOpenQuestHeader("FMQ_Guadeloupe");
		AddQuestUserData("FMQ_Guadeloupe", "sAdd1", StringFromKey("FMQ_12"));
		pchar.questTemp.FMQG.Letter = "true";
	}
	pchar.questTemp.FMQG = "fail";
}

void FMQG_RemoveHunterScore(string qName) // снятие НЗГ
{
	int n = ChangeCharacterHunterScore(Pchar, "frahunter", 0);
	if (n >= 50) ChangeCharacterNationReputation(pchar, FRANCE, 50);
	else ChangeCharacterNationReputation(pchar, FRANCE, n);
	ChangeCharacterComplexReputation(pchar, "nobility", 10);
	ChangeOfficersLoyality("good_all", 5);
	AddCrewMorale(pchar, 20);
}

void FMQG_ClearBox(string qName) // 
{
	DeleteAttribute(pchar, "GenQuestBox.Guadeloupe_Cave");
}
// <-- ФМК-Гваделупа

// --> ФМК-Мартиника
void FMQM_Activation(string qName) // старт
{
	// belamour legendary edition -->
	if (CheckAttribute(pchar, "questTemp.HWIC") || CheckAttribute(pchar, "questTemp.GuideDeath") || pchar.Ship.Type == SHIP_NOTUSED) return;
	//Sinistra Квест "Смолённый Пёс" не доступен, если убили Валинье
	// <-- legendary edition
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	sld = GetCharacter(NPC_GenerateCharacter("FMQM_carpenter", "citiz_25", "man", "man", 10, FRANCE, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 10, true);
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Martinique.c";
	sld.Dialog.currentnode = "carpenter";
	RemoveAllCharacterItems(sld, true);
	ChangeCharacterAddressGroup(sld, "Fortfrance_town", "quest", "quest1");
	LAi_SetImmortal(sld, true);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	LAi_SetLoginTime(sld, 8.0, 19.99);
	AddLandQuestMark(sld, "questmarkmain");
}

void FMQM_Denial(string qName) // просрочка
{
	pchar.questTemp.FMQM = "fail";
	AddQuestRecord("FMQ_Martinique", "2");
	CloseQuestHeader("FMQ_Martinique");
	DelLandQuestMark(characterFromId("FortFrance_shipyarder"));
}

void FMQM_ConvoyStart(string qName) // конвой со смолой
{
	string sCapId = "OilCap";// Addon 2016-1 Jason пиратская линейка
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE-2;
	int iScl = 10 + 2*sti(pchar.rank);
	int iShip, iTemp, iSpace;
	if (sti(pchar.rank) < 8)
	{
		if (MOD_SKILL_ENEMY_RATE < 7) iShip = SHIP_TARTANE;
		if (MOD_SKILL_ENEMY_RATE == 8) iShip = SHIP_SLOOP;
		if (MOD_SKILL_ENEMY_RATE > 9) iShip = SHIP_SCHOONER_W;
	}
	else
	{
		if (MOD_SKILL_ENEMY_RATE < 7) iShip = SHIP_SLOOP;
		if (MOD_SKILL_ENEMY_RATE == 8) iShip = SHIP_BARKENTINE;
		if (MOD_SKILL_ENEMY_RATE > 9) iShip = SHIP_BRIG;
	}
	for (int i = 1; i <= 3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "citiz_41", "man", "man", iRank, SPAIN, 25, true, "soldier"));
		SetRandomNameToCharacter(sld);
		SetRandomNameToShip(sld);
		switch (i)
		{
			case 1: iTemp = iShip; break;
			case 2: 
				if (MOD_SKILL_ENEMY_RATE > 7) iTemp = SHIP_BARQUE;
				else iTemp = SHIP_BARKENTINE; 
			break;
			case 3:
				if (MOD_SKILL_ENEMY_RATE < 7) iShip = SHIP_TARTANE;
				if (MOD_SKILL_ENEMY_RATE == 8) iShip = SHIP_LUGGER;
				if (MOD_SKILL_ENEMY_RATE > 9) iShip = SHIP_SCHOONER;
			break;
		}
		sld.Ship.Type = GenerateShipExt(iTemp, 1, sld);
		SetBaseShipData(sld);
		if (i > 1) 
		{
			SetCaptanModelByEncType(sld, "trade");
			sld.Ship.Mode = "trade";
		}
		else 
		{
			SetCaptanModelByEncType(sld, "war");
			sld.Ship.Mode = "war";
		}
		int hcrew = GetMaxCrewQuantity(sld);
		if(MOD_SKILL_ENEMY_RATE < 8) hcrew = GetOptCrewQuantity(sld);
		SetCrewQuantity(sld, hcrew);
		SetCrewQuantityFull(sld);
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.lifeDay = 25;
		sld.AnalizeShips = true;
		sld.WatchFort = true; //видеть форты
		sld.skill.Sailing = iScl+rand(5);
		sld.skill.Defence = iScl+rand(5);
		sld.skill.Accuracy = iScl+rand(5);
		sld.skill.Cannons = iScl+rand(5);
		sld.Ship.Crew.Morale = iScl+10;
		sld.Ship.Crew.Exp.Sailors = iScl+10;
		sld.Ship.Crew.Exp.Cannoners = iScl+10;
		sld.Ship.Crew.Exp.Soldiers = iScl+10;
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "SailsDamageUp");
		SetCharacterPerk(sld, "CrewDamageUp");
		if (MOD_SKILL_ENEMY_RATE > 6 && i == 1) SetCharacterPerk(sld, "CriticalShoot");
		if (MOD_SKILL_ENEMY_RATE > 6) SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "AdvancedBattleState");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "ShipSpeedUp");
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		AddCharacterGoods(sld, GOOD_BALLS, 300);
		if(MOD_SKILL_ENEMY_RATE > 6)
		{
			AddCharacterGoods(sld, GOOD_GRAPES, 300);
			AddCharacterGoods(sld, GOOD_KNIPPELS, 200);
			AddCharacterGoods(sld, GOOD_BOMBS, 200);
		}
		AddCharacterGoods(sld, GOOD_POWDER, 800);
		iSpace = GetCharacterFreeSpace(sld, GOOD_SUGAR);
		iSpace = makeint(iSpace/2 + hrand(iSpace/2));
		Fantom_SetCharacterGoods(sld, GOOD_SUGAR, iSpace, 1);
		if (i == 2) 
		{
			sld.Ship.Name = StringFromKey("FMQ_13");
			SetCharacterGoods(sld, GOOD_OIL, 100+hrand(10));//положить в трюм смолу
			if (MOD_SKILL_ENEMY_RATE > 8) SetCrewQuantityOverMax(sld, hcrew+4*MOD_SKILL_ENEMY_RATE); // увеличенная команда // may-16
		}
		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
        sld.mapEnc.Name = StringFromKey("FMQ_14");
        Group_AddCharacter(sGroup, sCapId + i);
	}
	Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader("PortSpein", "SanJuan", sCapId + "1", 25);//запуск энкаунтера
	SetFunctionTimerCondition("FMQM_ConvoyDelete", 0, 0, 26, false);
	pchar.quest.FMQM_Convoy_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.FMQM_Convoy_Abordage.win_condition.l1.character = "OilCap2";
	pchar.quest.FMQM_Convoy_Abordage.function = "FMQM_ConvoyBoarding";//взяли на абордаж
	pchar.quest.FMQM_Convoy_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.FMQM_Convoy_Sink.win_condition.l1.character = "OilCap2";
	pchar.quest.FMQM_Convoy_Sink.function = "FMQM_ConvoySink";//потопили
}

void FMQM_ConvoyBoarding(string qName) // 
{
	pchar.quest.FMQM_ConvoyDelete.over = "yes";
	pchar.quest.FMQM_Convoy_Sink.over = "yes";
	AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
	if (GetSquadronGoods(pchar, GOOD_OIL) >= 50)
	{
		pchar.questTemp.FMQM = "oil";
		AddQuestRecord("FMQ_Martinique", "8");
		SetFunctionTimerCondition("FMQM_Late", 0, 0, 30, false);
		AddMapQuestMarkCity("FortFrance", true);
		AddLandQuestMark(characterFromId("FortFrance_shipyarder"), "questmarkmain");
	}
	else
	{
		pchar.questTemp.FMQM = "fail";
		AddQuestRecord("FMQ_Martinique", "7");
		CloseQuestHeader("FMQ_Martinique");
	}
}

void FMQM_ConvoySink(string qName) // 
{
	pchar.quest.FMQM_ConvoyDelete.over = "yes";
	pchar.quest.FMQM_Convoy_Abordage.over = "yes";
	pchar.questTemp.FMQM = "fail";
	AddQuestRecord("FMQ_Martinique", "5");
	CloseQuestHeader("FMQ_Martinique");
}

void FMQM_ConvoyDelete(string qName) // 
{
	pchar.quest.FMQM_Convoy_Sink.over = "yes";
	pchar.quest.FMQM_Convoy_Abordage.over = "yes";
	pchar.questTemp.FMQM = "fail";
	AddQuestRecord("FMQ_Martinique", "6");
	CloseQuestHeader("FMQ_Martinique");
}

void FMQM_Late(string qName) // просрочка на месяц
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.FMQM_Late.over"))
			DeleteAttribute(pchar,"quest.FMQM_Late.over");
		NewGameTip(StringFromKey("FMQ_15"));
		SetFunctionTimerCondition("FMQM_Late", 0, 0, 30, false);
		return;
	}
	pchar.questTemp.FMQM = "fail";
	AddQuestRecord("FMQ_Martinique", "9");
	CloseQuestHeader("FMQ_Martinique");
	DelMapQuestMarkCity("FortFrance");
	DelLandQuestMark(characterFromId("FortFrance_shipyarder"));
}

void FMQM_WaitTime(string qName) // 
{
	// ориентируем на вечер
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime;
	if (iTime < 7) iAddTime = 21 - iTime;
	if (iTime >= 7 && iTime < 21) iAddTime = 21 - iTime;
	SetLaunchFrameFormParam(StringFromKey("FMQ_16", NewStr()), "", 0, 5);
	LaunchFrameForm();
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	DoQuestFunctionDelay("FMQM_OilTalking", 5.0);
}

void FMQM_OilTalking(string qName) // 
{
	sld = characterFromId("FortFrance_shipyarder");
	ChangeCharacterAddressGroup(sld, "FortFrance_Shipyard", "goto", "goto3");
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
	DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
}

void FMQM_ShipyardOpen(string qName) // 
{
	LocatorReloadEnterDisable("FortFrance_town", "reload5_back", false);
	sld = characterFromId("FortFrance_shipyarder");
	ChangeCharacterAddressGroup(sld, "FortFrance_Shipyard", "sit", "sit1");
	sld.Dialog.Filename = "Common_Shipyard.c";
	sld.Dialog.currentnode = "First time";
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	AddLandQuestMark(sld, "questmarkmain");
	AddQuestRecord("FMQ_Martinique", "11");
}

void FMQM_GuideAdvice(string qName) // 
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Guide_x");
	sld.dialog.currentnode = "greguar_18";
	ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto29");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void FMQM_HurryLate(string qName) // 
{
	pchar.worldmapencountersoff = "0"; // включить энкаунтеры
	pchar.quest.FMQM_hurry.over = "yes";
	pchar.questTemp.FMQM = "fail";
	AddQuestRecord("FMQ_Martinique", "14");
	CloseQuestHeader("FMQ_Martinique");
	DelMapQuestMarkIsland("Guadeloupe");
}

void FMQM_ArriveGuadeloupe(string qName) // 
{
	pchar.worldmapencountersoff = "0"; // включить энкаунтеры
	pchar.quest.FMQM_HurryLate.over = "yes";
	AddQuestRecord("FMQ_Martinique", "15");
	Island_SetReloadEnableGlobal("Guadeloupe", false);
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	pchar.GenQuest.SmugglersBlock = "baster_tavern";
	Group_SetAddress(PLAYER_GROUP, "Guadeloupe", "quest_ships", "quest_ship_10");
	// ставим тартану
	Group_FindOrCreateGroup("FMQM_Tartane");
	Group_SetType("FMQM_Tartane", "pirate");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("FMQM_Tartane_Cap", "mercen_7", "man", "man", 15, FRANCE, 5, true, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_WAR_TARTANE, StringFromKey("FMQ_17"), CANNON_TYPE_CANNON_LBS3, 30, 30, 30);// Addon 2016-1 Jason пиратская линейка
	FantomMakeCoolFighter(sld, 15, 30, 30, "blade_06", "pistol1", "bullet", 50);
	realships[sti(sld.ship.type)].SpeedRate = 35.0;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	LAi_SetImmortal(sld, true);
	sld.ShipEnemyDisable = true;
	Group_AddCharacter("FMQM_Tartane", "FMQM_Tartane_Cap");
	Group_SetGroupCommander("FMQM_Tartane", "FMQM_Tartane_Cap");
	Group_SetTaskNone("FMQM_Tartane");
	Group_SetAddress("FMQM_Tartane", "Guadeloupe", "ships", "l5");
	Group_LockTask("FMQM_Tartane");
	// таймер
	pchar.quest.FMQM_Tartane.win_condition.l1 = "Timer";
	pchar.quest.FMQM_Tartane.win_condition.l1.date.hour  = sti(GetTime() + 1);
	pchar.quest.FMQM_Tartane.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
	pchar.quest.FMQM_Tartane.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.FMQM_Tartane.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
	pchar.quest.FMQM_Tartane.function = "FMQM_TartaneSail";
}

void FMQM_TartanaAlarm() // 
{
	log_info(StringFromKey("FMQ_18"));
	pchar.quest.FMQM_Tartane.over = "yes";
	Island_SetReloadEnableGlobal("Guadeloupe", true);
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	sld = characterFromId("FMQM_Tartane_Cap");
	sld.quest.seaattack = "true";
	LAi_SetImmortal(sld, false);
	DeleteAttribute(sld, "ShipEnemyDisable");
	Ship_SetTaskRunAway(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	RefreshBattleInterface();
	UpdateRelations();
	pchar.questTemp.FMQM = "fail";
	AddQuestRecord("FMQ_Martinique", "16");
	CloseQuestHeader("FMQ_Martinique");
}

void FMQM_TartaneSail(string qName) // 
{
	sld = characterFromId("FMQM_Tartane_Cap");
	sld.quest.seaattack = "true";
	pchar.GenQuest.CabinLock = true; // закрыть каюту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	Ship_SetTaskRunAway(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
	AddQuestRecord("FMQ_Martinique", "17");
	// таймер
	pchar.quest.FMQM_Tartane1.win_condition.l1 = "Timer";
	pchar.quest.FMQM_Tartane1.win_condition.l1.date.hour  = sti(GetTime() + 1);
	pchar.quest.FMQM_Tartane1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
	pchar.quest.FMQM_Tartane1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.FMQM_Tartane1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
	pchar.quest.FMQM_Tartane1.function = "FMQM_AbandonGuadeloupe";
}

void FMQM_AbandonGuadeloupe(string qName) // 
{
	log_info(StringFromKey("FMQ_19"));
	PlaySound("interface\notebook.wav");
	SetTimeScale(1.0);
	Island_SetReloadEnableGlobal("Guadeloupe", true);
	DeleteAttribute(pchar, "GenQuest.CabinLock");
	pchar.GenQuest.MapClosedNoBattle = true;
	pchar.quest.FMQM_Abandon.win_condition.l1 = "location";
	pchar.quest.FMQM_Abandon.win_condition.l1.location = "Shore28";
	pchar.quest.FMQM_Abandon.win_condition.l2 = "Ship_location";
	pchar.quest.FMQM_Abandon.win_condition.l2.location = "Shore28";
	pchar.quest.FMQM_Abandon.function = "FMQM_AbandonCoast";
	AddGeometryToLocation("Shore28", "smg");
	// таймер
	pchar.quest.FMQM_Tartane2.win_condition.l1 = "Timer";
	pchar.quest.FMQM_Tartane2.win_condition.l1.date.hour  = sti(GetTime() + 3);
	pchar.quest.FMQM_Tartane2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
	pchar.quest.FMQM_Tartane2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.FMQM_Tartane2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
	pchar.quest.FMQM_Tartane2.function = "FMQM_AbandonGuadeloupeLate";
}

void FMQM_AbandonGuadeloupeLate(string qName) // 
{
	if(bImCasual)
	{
		NewGameTip(StringFromKey("FMQ_20"));
		pchar.quest.FMQM_Tartane2.over = "yes";
		return;
	}
	pchar.quest.FMQM_Abandon.over = "yes";
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	RemoveGeometryFromLocation("Shore28", "smg");
	pchar.questTemp.FMQM = "fail";
	AddQuestRecord("FMQ_Martinique", "22");
	CloseQuestHeader("FMQ_Martinique");
}

void FMQM_AbandonCoast(string qName) // в бухте Морн л'О
{
	pchar.quest.FMQM_Tartane2.over = "yes";
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	int iRank = MOD_SKILL_ENEMY_RATE+5;
	int iScl = 20 + 2*sti(pchar.rank);
	int i, n;
	n = makeint(MOD_SKILL_ENEMY_RATE/3 + 6);
	pchar.GenQuest.Hunter2Pause = true;
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], true);//запретить драться
	//ставим наших бойцов
	for (i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQM_Our_crew_"+i, "citiz_"+(i+30), "man", "man", iRank, sti(pchar.nation), 0, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_12","blade_09","blade_14"), "pistol1", "bullet", iScl*2);
		ChangeCharacterAddressGroup(sld, "Shore28", "goto", "goto12");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// ставим противника
	for (i=1; i<=n; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQM_Enemy_crew_"+i, "mush_ctz_9", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			sld.MusketerDistance = 0;
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQM_Enemy_crew_"+i, "citiz_"+(40+i), "man", "man", iRank, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_03","blade_05","blade_07"), "pistol1", "bullet", iScl*2);
		}
		if (i < 4) ChangeCharacterAddressGroup(sld, "Shore28", "smugglers", "smuggler0"+i);
		else 
		{
			ChangeCharacterAddressGroup(sld, "Shore28", "goto", "goto"+i);
			LAi_CharacterDisableDialog(sld);
		}
		if (MOD_SKILL_ENEMY_RATE > 8)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQM_Enemy_crew_plus", "mush_ctz_8", "man", "mushketer", iRank+3, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank+3, iScl+5, iScl+5, "", "mushket1", "cartridge", iScl*3);
			sld.MusketerDistance = 0;
			ChangeCharacterAddressGroup(sld, "Shore28", "smugglers", "smugglerload");
		}
		if (i == 2) AddLandQuestMark(sld, "questmarkmain");
		LAi_SetStayType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.dialog.FileName = "Quest\LineMiniQuests\FMQ_Martinique.c";
		sld.dialog.currentnode = "pirate";
		sld.greeting = "marginal";
	}
}

void FMQM_ShoreFight(string qName) // 
{
	LAi_group_Delete("EnemyFight");
	LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], false);
	int i, n;
	n = makeint(MOD_SKILL_ENEMY_RATE/3 + 6);
	for (i=1; i<=5; i++)
	{
		sld = characterFromId("FMQM_Our_crew_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i=1; i<=n; i++)
	{
		sld = characterFromId("FMQM_Enemy_crew_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	if (MOD_SKILL_ENEMY_RATE > 8)
	{
		sld = characterFromId("FMQM_Enemy_crew_plus");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "FMQM_ShoreAfterFight");
	LAi_SetFightMode(pchar, true);
}

void FMQ_CheckEnemyDistance() // расчет дистанции
{
	float fdist;
	if (pchar.location == "Shore28")
	{
		if (GetCharacterDistByLoc(pchar, "reload", "sea", &fdist))
		{
			if (fdist < 5.0) FMQM_OfficerTalkBegin();
		}
	}
}

void FMQM_OfficerTalkBegin()
{
	DeleteAttribute(pchar, "questTemp.FMQ.Attack");
	sld = characterFromId("FMQM_officer");
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void FMQM_PeaceExit(string qName) // 
{
	Group_DeleteGroup("FMQM_Tartane");
	sld = characterFromId("FMQM_officer");
	LAi_SetWarriorType(sld);
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
	chrDisableReloadToLocation = false;
	RemoveGeometryFromLocation("Shore28", "smg");
	pchar.quest.FMQM_final.win_condition.l1 = "ExitFromLocation";
	pchar.quest.FMQM_final.win_condition.l1.location = pchar.location;
	pchar.quest.FMQM_final.function = "FMQM_PeaceFinal";
}

void FMQM_PeaceFinal(string qName) // 
{
	LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], false);
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	int i = makeint(sti(pchar.questTemp.FMQM.Qty)/2);
	SetCharacterGoods(pchar, GOOD_OIL, GetCargoGoods(pchar, GOOD_OIL) + i);
	DeleteAttribute(pchar, "questTemp.FMQM.Qty");
	pchar.questTemp.FMQM = "end";
	FMQ_Count();
	AddQuestRecord("FMQ_Martinique", "19");
	CloseQuestHeader("FMQ_Martinique");
	ChangeCharacterComplexReputation(pchar, "authority", 1);
	AddComplexSelfExpToScill(50, 50, 50, 50);
	AddCharacterExpToSkill(pchar, "Leadership", 100);
	AddCharacterExpToSkill(pchar, "Fortune", 100);
	AddCharacterExpToSkill(pchar, "Sneak", 100);
}

void FMQM_BattleExit(string qName) // 
{
	LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], false);
	sld = characterFromId("FMQM_officer");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (i=1; i<=5; i++)
	{
		sld = characterFromId("FMQM_mercenary_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "FMQM_AfterBattleExit");
	LAi_SetFightMode(pchar, true);
}

void FMQM_SeaBattleTartane(string qName) // 
{
	RemoveGeometryFromLocation("Shore28", "smg");
	int i = makeint(sti(pchar.questTemp.FMQM.Qty)/2);
	SetCharacterGoods(pchar, GOOD_OIL, GetCargoGoods(pchar, GOOD_OIL) + i);
	SetCharacterGoods(pchar, GOOD_ROPES, GetCargoGoods(pchar, GOOD_ROPES) + 50);
	SetCharacterGoods(pchar, GOOD_SHIPSILK, GetCargoGoods(pchar, GOOD_SHIPSILK) + 30);
	SetCharacterGoods(pchar, GOOD_SANDAL, GetCargoGoods(pchar, GOOD_SANDAL) + 25);
	DeleteAttribute(pchar, "questTemp.FMQM.Qty");
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	Group_SetAddress("FMQM_Tartane", "Guadeloupe", "", "");
	Group_SetPursuitGroup("FMQM_Tartane", PLAYER_GROUP);
	sld = characterFromId("FMQM_Tartane_Cap");
	LAi_SetImmortal(sld, false);
	DeleteAttribute(sld, "ShipEnemyDisable");
	sld.Coastal_Captain = true;
	sld.AlwaysEnemy = true;
	Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	realships[sti(sld.ship.type)].SpeedRate = 12.5;
	RefreshBattleInterface();
	UpdateRelations();
	Group_LockTask("FMQM_Tartane");
	pchar.quest.Mirage_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Mirage_AfterBattle.win_condition.l1.group = "FMQM_Tartane";
	pchar.quest.Mirage_AfterBattle.function = "FMQM_BattleFinal";
}

void FMQM_BattleFinal(string qName) // 
{
	PlaySound("MUSIC\Victory.mp3");// Addon 2016-1 Jason пиратская линейка
	Group_DeleteGroup("FMQM_Tartane");
	bQuestDisableMapEnter = false;//открыть карту
	pchar.questTemp.FMQM = "end";
	FMQ_Count();
	AddQuestRecord("FMQ_Martinique", "21");
	CloseQuestHeader("FMQ_Martinique");
	ChangeCharacterComplexReputation(pchar, "authority", 3);
	AddCrewMorale(pchar, 5);
	ChangeOfficersLoyality("good_all", 1);
	AddComplexSelfExpToScill(80, 80, 80, 80);
	AddCharacterExpToSkill(pchar, "Leadership", 100);
	AddCharacterExpToSkill(pchar, "Fortune", 100);
	AddCharacterExpToSkill(pchar, "Sneak", 100);
	AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 50);
}

// --> ФМК-Сент-Кристофер
void FMQN_Activation(string qName) // 
{
	// belamour legendary edition -->
	if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED) return;
	// <-- legendary edition
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 30 + 3*sti(pchar.rank);
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	sld = GetCharacter(NPC_GenerateCharacter("FMQN_seafox_1", "quest_off_eng", "man", "man", iRank+5, ENGLAND, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_15", "pistol5", "bullet", iScl*3);
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Nevis.c";
	sld.Dialog.currentnode = "seafox";
	sld.name = StringFromKey("FMQ_21");
	sld.lastname = StringFromKey("FMQ_22");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	ChangeCharacterAddressGroup(sld, "Charles_town", "quest", "quest1");
	LAi_SetImmortal(sld, true);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	LAi_SetLoginTime(sld, 8.0, 20.99);
	AddLandQuestMark(sld, "questmarkmain");
	for (i=2; i<=5; i++)
	{
		if (i == 5)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQN_seafox_"+i, "mush_eng_6", "man", "mushketer", iRank, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQN_seafox_"+i, "sold_eng_1"+i, "man", "man", iRank, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_12","blade_09","blade_14"), "pistol1", "bullet", iScl*2);
		}
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
	}
}

void FMQN_SailingLate(string qName) // закладка бунта
{
	if (IsEntity(&worldMap)) DoQuestFunctionDelay("FMQN_MutiniOnShip", 0.5);
	else
	{
		pchar.quest.FMQN_Mutiny.win_condition.l1 = "MapEnter";
		pchar.quest.FMQN_Mutiny.function = "FMQN_MutiniOnShip";
	}
	DelMapQuestMarkShore("Shore40");
}

void FMQN_MutiniOnShip(string qName) // бунт
{
	if (pchar.questTemp.FMQN != "begin") return;
	pchar.quest.FMQN_sailing.over = "yes";
	pchar.questTemp.FMQN = "mutiny";
	MunityOnShip("ShipMunity");
	for(i = 0; i < MAX_LOCATIONS; i++)
	{	
		sld = &Locations[i];
		if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
		{
			sld.DisableEncounters = false;	
		}
	}
	sld = &Locations[FindLocation("Shore40")];
	DeleteAttribute(sld, "QuestlockWeather");
}

void FMQN_ArriveMaarten(string qName) // прибыли на Синт-Марртен
{
	// ориентируем на ночь
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + 1;
	if (iTime < 7) iAddTime = iTime + 13;
	if (iTime >= 7 && iTime < 21) iAddTime = 24 - iTime + 1;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	pchar.quest.FMQN_SailingLate.over = "yes";
	chrDisableReloadToLocation = true;
	pchar.GenQuest.Hunter2Pause = true;
	for (int i=1; i<=5; i++)
	{
		sld = characterFromId("FMQN_seafox_"+i);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Shore40", "goto", "goto"+i);
		if (i == 1)
		{
			sld.Dialog.currentnode = "seafox_6";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	pchar.questTemp.FMQN = "maarten";
	sld = &Locations[FindLocation("Shore40")];
	DeleteAttribute(sld, "QuestlockWeather");
}

void FMQN_EnglishmanGo() // англичане убегают
{
	for (int i=1; i<=5; i++)
	{
		sld = characterFromId("FMQN_seafox_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
		if (i == 1) RemovePassenger(pchar, sld);	
	}
	pchar.questTemp.FMQN.Choose = "true";
	DoQuestCheckDelay("TalkSelf_Quest", 11.0);
	InterfaceStates.Buttons.Save.enable = false;
	bDisableCharacterMenu = true;
}

void FMQN_ChooseExit(string qName) // отказ от продолжения
{
	chrDisableReloadToLocation = false;
	InterfaceStates.Buttons.Save.enable = true;
	bDisableCharacterMenu = false;
	DeleteAttribute(pchar, "questTemp.FMQN.Choose");
	for(i = 0; i < MAX_LOCATIONS; i++)
	{	
		sld = &Locations[i];
		if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
		{
			sld.DisableEncounters = false;	
		}
	}
	for (int i=1; i<=5; i++)
	{
		sld = characterFromId("FMQN_seafox_"+i);
		sld.lifeday = 0;
	}
	pchar.questTemp.FMQN = "fail";
	AddQuestRecord("FMQ_Nevis", "3");
	CloseQuestHeader("FMQ_Nevis");
}

void FMQN_ChooseContinue() // продолжаем квест 
{
	chrDisableReloadToLocation = false;
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	InterfaceStates.Buttons.Save.enable = true;
	bDisableCharacterMenu = false;
	pchar.GenQuest.SmugglersBlock = "marigo_tavern"; 
	DeleteAttribute(pchar, "questTemp.FMQN.Choose");
	AddQuestRecord("FMQ_Nevis", "4");
	pchar.quest.FMQN_to_port.win_condition.l1 = "location";
	pchar.quest.FMQN_to_port.win_condition.l1.location = "Marigo_town";
	pchar.quest.FMQN_to_port.win_condition.l2 = "Ship_location";
	pchar.quest.FMQN_to_port.win_condition.l2.location = "Marigo_town";
	pchar.quest.FMQN_to_port.function = "FMQN_ArriveToPort";
	SetFunctionTimerCondition("FMQN_WaitOver", 0, 0, 3, false);
	// поставим корвет Зеепард
	Group_FindOrCreateGroup("FMQN_shipgroup");
	sld = GetCharacter(NPC_GenerateCharacter("FMQN_Cap_Zeepard", "off_hol_4", "man", "man", 25, HOLLAND, -1, false, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_CORVETTE, StringFromKey("FMQ_23"), CANNON_TYPE_CULVERINE_LBS18, 65, 65, 65);
	FantomMakeCoolFighter(sld, 25, 65, 65, "blade_13", "pistol1", "bullet", 150);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.DontHitInStorm = true; // не ломается в шторм
	LAi_SetImmortal(sld, true);
	sld.ShipEnemyDisable  = true;
	sld.Ship.Mode = "war";
	sld.ship.Crew.Morale = 90;
	sld.Ship.Crew.Exp.Sailors = 90;
	sld.Ship.Crew.Exp.Cannoners = 90;
	sld.Ship.Crew.Exp.Soldiers = 90;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("FMQN_shipgroup", "FMQN_Cap_Zeepard");
	Group_SetGroupCommander("FMQN_shipgroup", "FMQN_Cap_Zeepard");
	Group_SetTaskNone("FMQN_shipgroup");
	Group_SetAddress("FMQN_shipgroup", "SentMartin", "quest_ships", "quest_ship_1");
	Group_LockTask("FMQN_shipgroup");
}

void FMQN_ArriveToPort(string qName) // прибыли в Филипсбург 
{
	AddLandQuestMark(characterFromId("marigo_tavernkeeper"), "questmarkmain");
	pchar.questTemp.FMQN = "town";
	bDisableFastReload = true;
}

void FMQN_WaitOver(string qName) // прошли три дня
{
	pchar.quest.FMQN_to_port.over = "yes";
	if (pchar.location == "Shore40") DoQuestFunctionDelay("FMQN_ThreeDaysOver", 1.0);
	else
	{
		pchar.questTemp.FMQN = "late";
		AddQuestRecord("FMQ_Nevis", "5");
		pchar.quest.FMQN_fail_town.win_condition.l1 = "location";
		pchar.quest.FMQN_fail_town.win_condition.l1.location = "Shore40";
		pchar.quest.FMQN_fail_town.function = "FMQN_ThreeDaysOver";
	}
	DelLandQuestMarkToPhantom();
}

void FMQN_ThreeDaysOver(string qName) // прошли три дня
{
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	bDisableFastReload = false;//открыть переход
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	for(i = 0; i < MAX_LOCATIONS; i++)
	{	
		sld = &Locations[i];
		if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
		{
			sld.DisableEncounters = false;	
		}	
	}
	sld = characterFromId("FMQN_Cap_Zeepard");
	sld.lifeday = 0;
	pchar.questTemp.FMQN = "fail";
	AddQuestRecord("FMQ_Nevis", "6");
	CloseQuestHeader("FMQ_Nevis");
	AddSimpleRumourCity(StringFromKey("FMQ_24"), "Marigo", 20, 2, "");
	AddSimpleRumourCity(StringFromKey("FMQ_25"), "Marigo", 20, 2, "");
}

void FMQN_ToGovernor(string qName) // посланец к губеру
{
	int iTime, iAddTime;
	iTime = sti(environment.time);
	chrDisableReloadToLocation = true;
	pchar.GenQuest.Hunter2Pause = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Marigo_town")], true);
	sld = GetCharacter(NPC_GenerateCharacter("FMQN_hov_sold", "sold_hol_1", "man", "man", 15, HOLLAND, 0, false, "soldier"));
	SetFantomParamFromRank(sld, 15, true);
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Nevis.c";
	sld.Dialog.currentnode = "soldier";
	ChangeCharacterAddressGroup(sld, "Marigo_town", "goto", LAi_FindNearestLocator2Pchar("goto"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void FMQN_ReloadToGovernor() // релоад к губеру
{
	LAi_LocationFightDisable(&Locations[FindLocation("Marigo_town")], false);
	if (stf(environment.time) < 10.0) WaitDate("",0,0,0,4,5);
	DoQuestReloadToLocation("Marigo_townhall", "reload", "reload1", "");
	DoQuestCheckDelay("OpenTheDoors", 10.0); // Addon 2016-1 Jason пиратская линейка
}

void FMQN_SetSoldiersInCave() // англичан в пещеру
{
	pchar.quest.FMQN_WaitOver.over = "yes";
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	LAi_LocationFightDisable(&Locations[FindLocation("Marigo_Cave")], true);
	LAi_LocationDisableOfficersGen("Marigo_Cave", true);
	sld = CharacterFromID("FMQN_seafox_1");
	sld.Dialog.currentnode = "seafox_9";
	sld.model = "quest_off_holl";
	Characters_RefreshModel(sld);
	sld.talker = 9;
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Marigo_Cave", "goto", "goto3");
	AddLandQuestMark(sld, "questmarkmain");
	for (int i=2; i<=5; i++)
	{
		sld = CharacterFromID("FMQN_seafox_"+i);
		if (i == 5)
		{
			sld.model = "mush_hol_2";
		}
		else
		{
			sld.model = "sold_hol_"+(i-1);
		}
		ChangeCharacterAddressGroup(sld, "Marigo_Cave", "goto", "ass"+(i-1));
		LAi_SetActorType(sld);
	}
}

void FMQN_ToChurch() // в церковь к Филипу Якобсену
{
	sld = CharacterFromID("FMQN_seafox_1");
	LAi_CharacterDisableDialog(sld);
	if (pchar.questTemp.FMQN == "way_div_1")
	{
		AddQuestRecord("FMQ_Nevis", "11");
		pchar.questTemp.FMQN = "way_div_2";
		AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
	}
	else 
	{
		AddQuestRecord("FMQ_Nevis", "12");
		pchar.questTemp.FMQN = "way_eng_2";
	}
	// ставим монаха
	sld = GetCharacter(NPC_GenerateCharacter("FMQN_monk", "monk_5", "man", "man_B", 10, HOLLAND, -1, true, "quest"));
	SetFantomParamFromRank(sld, 10, true);
	RemoveAllCharacterItems(sld, true);
	sld.name = StringFromKey("FMQ_26");
	sld.lastname = StringFromKey("FMQ_27");
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Nevis.c";
	sld.dialog.currentnode = "monk";
	sld.greeting = "monk";
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	LAi_SetLoginTime(sld, 6.00, 10.00);
	ChangeCharacterAddressGroup(sld, "Marigo_church", "reload", "reload2_back");
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	AddLandQuestMark(sld, "questmarkmain");
}

void FMQN_HollandPeace() // за голландцев, мир
{
	sld = CharacterFromID("FMQN_monk");
	sld.lifeday = 0;
	for (int i=1; i<=5; i++)
	{
		sld = CharacterFromID("FMQN_seafox_"+i);
		sld.lifeday = 0;
	}
	LocatorReloadEnterDisable("Marigo_town", "reload1_back", true);
	LocatorReloadEnterDisable("Marigo_town", "reload2_back", true);
	LocatorReloadEnterDisable("Marigo_town", "gate_back", true);//закрыть выходы из города
	pchar.questTemp.FMQN = "hol_peace";
	AddQuestRecord("FMQ_Nevis", "13");
	SetFunctionTimerCondition("FMQN_HollandPeaceReward", 0, 0, 1, false);
}

void FMQN_HollandPeaceReward(string qName) // за голландцев, мир, награда
{
	pchar.questTemp.FMQN = "hol_peace_rew";
	AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
	AddSimpleRumourCity(StringFromKey("FMQ_28"), "Marigo", 20, 2, "");
	AddSimpleRumourCity(StringFromKey("FMQ_29"), "Marigo", 20, 2, "");
}

void FMQN_HollandPeaceComplete() // за голландцев, мир, завершение
{
	LocatorReloadEnterDisable("Marigo_town", "reload1_back", false);
	LocatorReloadEnterDisable("Marigo_town", "reload2_back", false);
	LocatorReloadEnterDisable("Marigo_town", "gate_back", false);
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	bDisableFastReload = false;//открыть переход
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	LAi_LocationFightDisable(&Locations[FindLocation("Marigo_Cave")], false);
	LAi_LocationDisableOfficersGen("Marigo_Cave", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	for(i = 0; i < MAX_LOCATIONS; i++)
	{	
		sld = &Locations[i];
		if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
		{
			sld.DisableEncounters = false;	
		}	
	}
	Group_DeleteGroup("FMQN_shipgroup");
	pchar.questTemp.FMQN = "end";
	FMQ_Count();
	AddQuestRecord("FMQ_Nevis", "14");
	CloseQuestHeader("FMQ_Nevis");
	ChangeCharacterNationReputation(pchar, HOLLAND, 5);
	AddCharacterExpToSkill(pchar, "Sneak", 200);
	AddCharacterExpToSkill(pchar, "Leadership", 100);
}

void FMQN_HollandBattle() // за голландцев, боевой
{
	sld = CharacterFromID("FMQN_monk");
	sld.lifeday = 0;
	AddLandQuestMark(CharacterFromID("FMQN_seafox_1"), "questmarkmain");
	pchar.questTemp.FMQN = "hol_battle";
	AddQuestRecord("FMQ_Nevis", "15");
	LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", true);
	LocatorReloadEnterDisable("Marigo_ExitTown", "reload2_back", true);
	LocatorReloadEnterDisable("Marigo_jungle_01", "reload1_back", true);
	LocatorReloadEnterDisable("Marigo_jungle_01", "reload2_back", true);
	LocatorReloadEnterDisable("Marigo_jungle_01", "reload3_back", true);
	DoQuestReloadToLocation("Marigo_ExitTown", "reload", "reload3", "FMQN_HollandBattleRun");
}

void FMQN_HollandBattlePlan(string qName) // за голландцев, военный совет
{
	sld = CharacterFromID("FMQN_holland_0");
	sld.Dialog.currentnode = "hol_officer_2";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void FMQN_HollandBattleGovernor(string qName) // к губернатору
{
	AddLandQuestMark(characterFromId("marigo_mayor"), "questmarkmain");
	pchar.questTemp.FMQN = "hol_battle_complete";
}

void FMQN_HollandBattleAdding(string qName) // солдаты спускаются по 1 с интервалом 10 сек
{
	sld = CharacterFromID("FMQN_holland_"+iTotalTemp);
	ChangeCharacterAddressGroup(sld, "Marigo_Cave", "reload", "reload2");
	iTotalTemp++;
	FMQN_HollandBattleAdding1();
}

void FMQN_HollandBattleAdding1() // китайская рекурсия
{
	if (iTotalTemp > 5) return;
	DoQuestCheckDelay("FMQN_HollandBattleAdding2", 10.0);
}

void FMQN_HollandBattleComplete() // за голландцев, боевой, завершение
{
	LocatorReloadEnterDisable("Marigo_town", "reload1_back", false);
	LocatorReloadEnterDisable("Marigo_town", "reload2_back", false);
	LocatorReloadEnterDisable("Marigo_town", "gate_back", false);
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	bDisableFastReload = false;//открыть переход
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	LAi_LocationDisableOfficersGen("Marigo_Cave", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	for(i = 0; i < MAX_LOCATIONS; i++)
	{	
		sld = &Locations[i];
		if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
		{
			sld.DisableEncounters = false;	
		}	
	}
	Group_DeleteGroup("FMQN_shipgroup");
	pchar.questTemp.FMQN = "end";
	FMQ_Count();
	AddQuestRecord("FMQ_Nevis", "17");
	CloseQuestHeader("FMQ_Nevis");
	AddMoneyToCharacter(pchar, 10000); 
	SetCharacterGoods(pchar, GOOD_SHIPSILK, GetCargoGoods(pchar, GOOD_SHIPSILK)+200);
	notification(StringFromKey("FMQ_30"), "SHIPSILK");
	GiveNationLicence(HOLLAND, 1095);
	ChangeCharacterNationReputation(pchar, HOLLAND, 15);
	ChangeCharacterNationReputation(pchar, ENGLAND, -15);
	ChangeCharacterComplexReputation(pchar, "fame", 2);
	AddCharacterExpToSkill(pchar, "Sneak", 200);
	AddCharacterExpToSkill(pchar, "Leadership", 200);
	AddCharacterExpToSkill(pchar, "Fortune", 200);
	AddComplexSelfExpToScill(50, 50, 50, 50);
	AddSimpleRumourCity(StringFromKey("FMQ_31"), "Marigo", 20, 3, "");
	AddSimpleRumourCity(StringFromKey("FMQ_32"), "Marigo", 20, 3, "");
	SetFunctionTimerCondition("FMQN_HollandSetHunters", 0, 0, 5, false);
}

void FMQN_HollandSetHunters(string qName) // перехватчик
{
	Map_NationQuestHunter(ENGLAND);
}

void FMQN_EnglandFail(string qName) // провал английского варианта
{
	for (int i=1; i<=5; i++)
	{
		sld = CharacterFromID("FMQN_seafox_"+i);
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
	}
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	bDisableFastReload = false;//открыть переход
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	LAi_LocationFightDisable(&Locations[FindLocation("Marigo_Cave")], false);
	LAi_LocationDisableOfficersGen("Marigo_Cave", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	for(i = 0; i < MAX_LOCATIONS; i++)
	{	
		sld = &Locations[i];
		if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
		{
			sld.DisableEncounters = false;	
		}
	}
	sld = characterFromId("FMQN_Cap_Zeepard");
	sld.lifeday = 0;
	if (pchar.questTemp.FMQN == "way_eng_3") // провалил у попа
	{
		sld = CharacterFromID("FMQN_monk");
		sld.lifeday = 0;
		AddQuestRecord("FMQ_Nevis", "19");
	}
	if (pchar.questTemp.FMQN == "way_eng_4") // не дошел до пещеры к 20 часам
	{
		AddQuestRecord("FMQ_Nevis", "22");
	}
	if (pchar.questTemp.FMQN == "way_eng_5") // не встретил у ворот в 23 часа
	{
		AddQuestRecord("FMQ_Nevis", "23");
		pchar.quest.FMQN_to_prison.over = "yes";
	}
	CloseQuestHeader("FMQ_Nevis");
	pchar.questTemp.FMQN = "fail";
	AddSimpleRumourCity(StringFromKey("FMQ_33"), "Marigo", 20, 2, "");
	AddSimpleRumourCity(StringFromKey("FMQ_34"), "Marigo", 20, 2, "");
}

void FMQN_EnglandBattleFail(string qName) // тревога
{
	Log_Info(StringFromKey("FMQ_35"));
	PlaySound("VOICE\Russian\EvilPirates01.wav");
	LAi_group_SetHearRadius("HOLLAND_CITIZENS", 200);
	for (int i=1; i<=5; i++)
	{
		sld = CharacterFromID("FMQN_seafox_"+i);
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_SetImmortal(sld, false);
	}
	if (pchar.questTemp.FMQN == "way_eng_7") // после захода в тюрьму
	{
		for (i=5; i<=6; i++)
		{
			sld = CharacterFromID("FMQN_prisoner_"+i);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, false);
		}
	}
	pchar.quest.FMQN_jail.over = "yes";
	pchar.quest.FMQN_jail1.over = "yes";
	pchar.quest.FMQN_Alarm.over = "yes";
	pchar.quest.FMQN_fail3.over = "yes";
	chrDisableReloadToLocation = false;
	pchar.quest.FMQN_fail_exit.win_condition.l1 = "ExitFromLocation";
	pchar.quest.FMQN_fail_exit.win_condition.l1.location = pchar.location;
	pchar.quest.FMQN_fail_exit.function = "FMQN_EnglandBattleFailExit";
}

void FMQN_EnglandBattleFailExit(string qName) // провал после тревоги
{
	LAi_group_SetHearRadius("HOLLAND_CITIZENS", LAI_GROUP_GRD_HEAR);
	LAi_LocationDisableOfficersGen("Marigo_Town", false);
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	bDisableFastReload = false;//открыть переход
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	LAi_LocationFightDisable(&Locations[FindLocation("Marigo_Cave")], false);
	LAi_LocationDisableOfficersGen("Marigo_Cave", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	for(i = 0; i < MAX_LOCATIONS; i++)
	{	
		sld = &Locations[i];
		if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
		{
			sld.DisableEncounters = false;	
		}
	}
	Group_DeleteGroup("FMQN_shipgroup");
	AddQuestRecord("FMQ_Nevis", "24");
	CloseQuestHeader("FMQ_Nevis");
	pchar.questTemp.FMQN = "fail";
	AddSimpleRumourCity(StringFromKey("FMQ_36"), "Marigo", 20, 2, "");
	AddSimpleRumourCity(StringFromKey("FMQ_37"), "Marigo", 20, 2, "");
}

void FMQN_EnglandMonkPlan(string qName) // монах все сделал
{
	sld = CharacterFromID("FMQN_monk");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.currentnode = "monk_6";
	AddLandQuestMark(sld, "questmarkmain");
}

void FMQN_EnglandPrepare() // готовимся к операции Ы
{
	AddQuestRecord("FMQ_Nevis", "21");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	pchar.quest.FMQN_to_prison.win_condition.l1 = "HardHour";
	pchar.quest.FMQN_to_prison.win_condition.l1.hour = 23.00;
	pchar.quest.FMQN_to_prison.win_condition.l2 = "location";
	pchar.quest.FMQN_to_prison.win_condition.l2.location = "Marigo_ExitTown";
	pchar.quest.FMQN_to_prison.function = "FMQN_EnglandGotoPrison";
	pchar.quest.FMQN_fail2.win_condition.l1 = "Timer";
	pchar.quest.FMQN_fail2.win_condition.l1.date.hour  = 0.0;
	pchar.quest.FMQN_fail2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.FMQN_fail2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.FMQN_fail2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.FMQN_fail2.function = "FMQN_EnglandFail";
	pchar.questTemp.FMQN = "way_eng_5";
}

void FMQN_EnglandGotoPrison(string qName) // пришли англичане к воротам
{
	pchar.quest.FMQN_fail2.over = "yes";
	chrDisableReloadToLocation = true;
	for (int i=1; i<=5; i++)
	{
		sld = CharacterFromID("FMQN_seafox_"+i);
		ChangeCharacterAddressGroup(sld, "Marigo_ExitTown", "reload", "reload1_back");
		LAi_CharacterDisableDialog(sld);
		if (i == 1)
		{
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "seafox_31";
		}
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void FMQN_EnglandReload(string qName) // релоад в город
{
	LAi_LocationDisableOfficersGen("Marigo_Town", true);
	DoQuestReloadToLocation("Marigo_town", "reload", "gate_back", "FMQN_EnglandSnake");
}

void FMQN_EnglandJail(string qName) // англичане - в тюрьму
{
	PlaySound("interface\notebook.wav");
	for (int i=1; i<=5; i++)
	{
		sld = CharacterFromID("FMQN_seafox_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload_jail", "none", "", "", "FMQN_EnglandInJail", 7.0);
	}
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto21", "FMQN_EnglandJailTurn", -1);
}

void FMQN_EnglandReloadJungle(string qName) // релоад в джунгли
{
	DoQuestReloadToLocation("Marigo_exittown", "reload", "reload3", "FMQN_EnglandEscape");
	LAi_LocationDisableOfficersGen("Marigo_Town", false);
}

void FMQN_EnglandInShoreAttack(string qName) // рубилово в бухте
{
	bool bOk;
	if (pchar.location.from_sea == "shore40") bOk;
	else 
	{
		Log_Info(StringFromKey("FMQ_38"));
		PlaySound("interface\notebook.wav");
	}
	PlaySound("interface\abordage_wining.wav");
	chrDisableReloadToLocation = true;
	for (int i=5; i<=6; i++) // пленные бегут
	{
		sld = CharacterFromID("FMQN_prisoner_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "quest", "quest1", "", 20);
	}
	// активируем наших
	for (i=1; i<=5; i++)
	{
		sld = CharacterFromID("FMQN_seafox_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// ставим отряд голландцев
	int iRank = sti(pchar.rank)/2+MOD_SKILL_ENEMY_RATE;
	int iScl = 20 + sti(pchar.rank);
	LAi_group_Delete("EnemyFight");
	sld = GetCharacter(NPC_GenerateCharacter("FMQN_holland_0", "off_hol_5", "man", "man", iRank+5, HOLLAND, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_15", "pistol5", "bullet", iScl*4);
	sld.name = StringFromKey("FMQ_39");
	sld.lastname = StringFromKey("FMQ_40");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	ChangeCharacterAddressGroup(sld, "shore40", "goto", "goto10");
	for (i=1; i<=9; i++)
	{
		if (i > 7)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQN_holland_"+i, "mush_hol_"+(i-4), "man", "mushketer", iRank, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*3);
			sld.MusketerDistance = 0;
			ChangeCharacterAddressGroup(sld, "shore40", "goto", "goto"+(i+3));
		}
		else
		{
			if (i == 6 || i == 7)
			{
				if (MOD_SKILL_ENEMY_RATE < 9) continue;
			}
			sld = GetCharacter(NPC_GenerateCharacter("FMQN_holland_"+i, "sold_hol_1"+i, "man", "man", iRank, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_12","blade_09","blade_14"), "pistol1", "bullet", iScl*2);
			ChangeCharacterAddressGroup(sld, "shore40", "goto", "goto"+i);
		}
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
	}
	for (i=0; i<=9; i++)
	{
		if (i == 6 || i == 7)
		{
			if (MOD_SKILL_ENEMY_RATE < 9) continue;
		}
		sld = CharacterFromID("FMQN_holland_"+i);
		if (!bOk) LAi_SetCheckMinHP(sld, 10, true, "");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "FMQN_AfterShoreAttack");	
	LAi_SetFightMode(pchar, true);
}

void FMQN_EnglandSeaAttack(string qName) // атака в море
{
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// Addon 2016-1 Jason пиратская линейка
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE-2;
	int iScl = 15 + 2*sti(pchar.rank);
	int iShipType = SHIP_SHNYAVA;
	int iCannon = CANNON_TYPE_CULVERINE_LBS8;
	if(sti(RealShips[sti(pchar.ship.type)].Class) == 5) iShipType = SHIP_SCHOONER_W;
	Island_SetReloadEnableGlobal("SentMartin", false);//на остров нельзя
	Group_FindOrCreateGroup("FMQN_shoregroup");
	sld = GetCharacter(NPC_GenerateCharacter("FMQN_shorecap", "off_hol_4", "man", "man", iRank, HOLLAND, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_14", "pistol1", "bullet", iScl*2);
	FantomMakeSmallSailor(sld, iShipType, "", iCannon, iScl, iScl, iScl, iScl, iScl);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "war";
	sld.AlwaysEnemy = true;
	sld.Coastal_Captain = true;
	sld.ship.Crew.Morale = 30+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Sailors = 30+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Cannoners = 30+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Soldiers = 30+MOD_SKILL_ENEMY_RATE*6;
	if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_PINK)
	{
		AddCharacterGoods(sld, GOOD_SHIPSILK, 30);
	}
	if (MOD_SKILL_ENEMY_RATE > 8) SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("FMQN_shoregroup", "FMQN_shorecap");
	Group_SetGroupCommander("FMQN_shoregroup", "FMQN_shorecap");
	Group_SetAddress("FMQN_shoregroup", "SentMartin", "quest_ships", "quest_ship_7");
	Group_SetTaskAttack("FMQN_shoregroup", PLAYER_GROUP);
	Group_LockTask("FMQN_shoregroup");
	pchar.quest.FMQN_AfterSeaBattle.win_condition.l1 = "Group_Death";
	pchar.quest.FMQN_AfterSeaBattle.win_condition.l1.group = "FMQN_shoregroup";
	pchar.quest.FMQN_AfterSeaBattle.function = "FMQN_EnglandAfterSeaBattle";
	for (i=5; i<=6; i++)
	{
		sld = CharacterFromID("FMQN_prisoner_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
}

void FMQN_EnglandAfterSeaBattle(string qName) // после морского боя
{
	Group_DeleteGroup("FMQN_shoregroup");
	bQuestDisableMapEnter = false;//открыть карту
	bDisableFastReload = false;//открыть переход
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	LAi_LocationFightDisable(&Locations[FindLocation("Marigo_Cave")], false);
	LAi_LocationDisableOfficersGen("Marigo_Cave", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	for(i = 0; i < MAX_LOCATIONS; i++)
	{	
		sld = &Locations[i];
		if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
		{
			sld.DisableEncounters = false;	
		}	
	}
	LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false);
	LocatorReloadEnterDisable("Marigo_ExitTown", "reload2_back", false);
	LocatorReloadEnterDisable("Marigo_jungle_01", "reload1_back", false);
	LocatorReloadEnterDisable("Marigo_jungle_01", "reload3_back", false);
	LocatorReloadEnterDisable("Marigo_jungle_02", "reload1_back", false);
	LocatorReloadEnterDisable("Marigo_jungle_02", "reload3_back", false);
	LocatorReloadEnterDisable("Marigo_jungle_02", "reloadW_back", false);
	LocatorReloadEnterDisable("shore40", "reload1_back", false);
	// подгружаем Зеепард
	Group_FindOrCreateGroup("FMQN_shipgroup");
	sld = characterFromId("FMQN_Cap_Zeepard");
	DeleteAttribute(sld, "ShipEnemyDisable");
	LAi_SetImmortal(sld, false);
	sld.AlwaysEnemy = true;
	Group_AddCharacter("FMQN_shipgroup", "FMQN_Cap_Zeepard");
	Group_SetGroupCommander("FMQN_shipgroup", "FMQN_Cap_Zeepard");
	Group_SetAddress("FMQN_shipgroup", "SentMartin", "", "");
	Group_SetTaskAttack("FMQN_shipgroup", PLAYER_GROUP);
	Sea_LoginGroupCurrentSea("FMQN_shipgroup");
	Log_Info(StringFromKey("FMQ_41"));
	// через 3 дня откроем остров
	SetFunctionTimerCondition("FMQN_EnglandOpenSintMaarten", 0, 0, 3, false);
	// НЗГ
	ChangeCharacterHunterScore(pchar, "holhunter", 15);
	pchar.quest.FMQN_eng_complete.win_condition.l1 = "location";
	pchar.quest.FMQN_eng_complete.win_condition.l1.location = "SentJons_town";
	pchar.quest.FMQN_eng_complete.function = "FMQN_EnglandOnAntigua";
	AddQuestRecord("FMQ_Nevis", "27");
	SetFunctionTimerCondition("FMQN_EnglandAntiguaLate", 0, 0, 20, false);
	AddSimpleRumourCity(StringFromKey("FMQ_42"), "Marigo", 20, 2, "");
	AddSimpleRumourCity(StringFromKey("FMQ_43"), "Marigo", 20, 2, "");
}

void FMQN_EnglandOpenSintMaarten(string qName) // открываем Синт-Маартен
{
	Group_DeleteGroup("FMQN_shipgroup");
	if (GetCharacterIndex("FMQN_Cap_Zeepard") != -1) 
	{
		sld = CharacterFromID("FMQN_Cap_Zeepard");
		sld.lifeday = 0;
	}
	Island_SetReloadEnableGlobal("SentMartin", true);
}

void FMQN_EnglandAntiguaLate(string qName) // вез-вез и не довез
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.FMQN_EnglandAntiguaLate.over"))
			DeleteAttribute(pchar,"quest.FMQN_EnglandAntiguaLate.over");
		NewGameTip(StringFromKey("FMQ_44"));
		SetFunctionTimerCondition("FMQN_EnglandAntiguaLate", 0, 0, 20, false);
		return;
	}
	pchar.quest.FMQN_LateFinal.win_condition.l1 = "Location_Type";
	pchar.quest.FMQN_LateFinal.win_condition.l1.location_type = "town";
	pchar.quest.FMQN_LateFinal.function = "FMQN_EnglandAntiguaLateFinal";
}

void FMQN_EnglandAntiguaLateFinal(string qName) // вез-вез и не довез за 20 дней
{
	if (pchar.location == "SentJons_town") return;
	pchar.quest.FMQN_eng_complete.over = "yes";
	for (int i=5; i<=6; i++)
	{
		sld = CharacterFromID("FMQN_prisoner_"+i);
		LAi_SetStayType(sld);
		RemovePassenger(pchar, sld);
		sld.lifeday = 0;
	}
	if (pchar.questTemp.FMQN == "caspar_alive")
	{
		sld = CharacterFromID("FMQN_seafox_1");
		RemovePassenger(pchar, sld);
		sld.lifeday = 0;
	}
	pchar.questTemp.FMQN = "fail";
	AddQuestRecord("FMQ_Nevis", "30");
	CloseQuestHeader("FMQ_Nevis");
}

void FMQN_EnglandOnAntigua(string qName) // на Антигуа
{
	pchar.quest.FMQN_EnglandAntiguaLate.over = "yes";
	pchar.quest.FMQN_LateFinal.over = "yes";
	pchar.GenQuest.Hunter2Pause = true; 
	LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
	LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
	LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//закрыть выходы из города
	pchar.GenQuest.CannotWait = true;
	for (int i=5; i<=6; i++)
	{
		sld = CharacterFromID("FMQN_prisoner_"+i);
		LAi_SetStayType(sld);
		RemovePassenger(pchar, sld);
		sld.lifeday = 0;
	}
	if (pchar.questTemp.FMQN == "caspar_alive")
	{
		sld = CharacterFromID("FMQN_seafox_1");
		RemovePassenger(pchar, sld);
		sld.dialog.currentnode = "seafox_35";
		sld.model = "quest_off_eng";
		Characters_RefreshModel(sld);
		LAi_CharacterEnableDialog(sld);
		ChangeCharacterAddressGroup(sld, "SentJons_town", "quest", "quest1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		sld = CharacterFromID("FMQN_prisoner_5");
		sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Nevis.c";
		sld.dialog.currentnode = "seafox_35x";
		LAi_CharacterEnableDialog(sld);
		ChangeCharacterAddressGroup(sld, "SentJons_town", "quest", "quest1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void FMQN_EnglandReward(string qName) // Фокс ждёт
{
	pchar.questTemp.FMQN = "eng_reward";
	AddLandQuestMark(characterFromId("Fox"), "questmarkmain");
}

void FMQN_EnglandComplete() // за Англию завершение
{
	// награда оружием
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1": 
			GiveItem2Character(pchar, "blade_15");
			//Log_Info("Вы получили клинок 'Маринера'");
		break;
		
		case "HeroType_2":
			GiveItem2Character(pchar, "blade_10");
			//Log_Info("Вы получили клинок 'Корд'");
		break;
		
		case "HeroType_3":
			GiveItem2Character(pchar, "blade_13");
			//Log_Info("Вы получили клинок 'Офицерский палаш'");
		break;
		
		case "HeroType_4":
			GiveItem2Character(pchar, "blade_15");
			//Log_Info("Вы получили клинок 'Маринера'");
		break;
	}
	LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
	LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
	LocatorReloadEnterDisable("SentJons_town", "gate_back", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	pchar.questTemp.FMQN = "end";
	FMQ_Count();
	AddQuestRecord("FMQ_Nevis", "29");
	CloseQuestHeader("FMQ_Nevis");
	AddMoneyToCharacter(pchar, 30000); 
	GiveItem2Character(pchar, "mushket3");
	//Log_Info("Вы получили аркебузу");
	PlaySound("interface\important_item.wav");
	ChangeCharacterNationReputation(pchar, ENGLAND, 20);
	ChangeCharacterComplexReputation(pchar, "nobility", 5);
	ChangeCharacterComplexReputation(pchar, "authority", 3);
	ChangeCharacterComplexReputation(pchar, "fame", 3);
	ChangeOfficersLoyality("good_all", 1);
	AddCharacterExpToSkill(pchar, "Sneak", 200);
	AddCharacterExpToSkill(pchar, "Leadership", 200);
	AddCharacterExpToSkill(pchar, "Fortune", 200);
	AddComplexSelfExpToScill(50, 50, 50, 50);
	AddSimpleRumourCity(StringFromKey("FMQ_45"), "SentJons", 20, 3, "");
	AddSimpleRumourCity(StringFromKey("FMQ_46"), "SentJons", 20, 3, "");
}

// --> ФМК-Тортуга
void FMQT_Activation(string qName) // 
{
	// belamour legendary edition -->
	if (CheckAttribute(pchar, "questTemp.HWIC")) return;
	// <-- legendary edition
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	sld = GetCharacter(NPC_GenerateCharacter("FMQT_girl", "women_11", "woman", "towngirl", 5, FRANCE, -1, false, "quest"));
	SetFantomParamFromRank(sld, 5, true);
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Tortuga.c";
	if (sti(pchar.reputation.nobility) > 41) sld.Dialog.currentnode = "girl";
	else sld.Dialog.currentnode = "girl_5";
	RemoveAllCharacterItems(sld, true);
	ChangeCharacterAddressGroup(sld, "Tortuga_town", "quest", "quest1");
	LAi_SetImmortal(sld, true);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	LAi_SetLoginTime(sld, 10.0, 15.99);
	AddLandQuestMark(sld, "questmarkmain");
}

void FMQT_FillChest()
{
	// запираем сундук Левассера и заполним его
	ref rLoc = &Locations[FindLocation("Tortuga_townhallRoom")];
	rLoc.private2.key = "crowbar";
	rLoc.private2.key.delItem = true;
	rLoc.private2.money = 10000;
	rLoc.private2.items.jewelry2 = 200;
	rLoc.private2.items.cannabis7 = 1;
	rLoc.private2.items.indian_7 = 1;
	rLoc.private2.items.indian_8 = 1;
	rLoc.private2.items.amulet_6 = 1;
	rLoc.private2.items.amulet_10 = 1;
	rLoc.private2.items.obereg_9 = 1;
}

void FMQT_ClearChest() // 
{
	ref rLoc = &Locations[FindLocation("Tortuga_townhallRoom")];
	DeleteAttribute(rLoc, "private2.key");
	DeleteAttribute(rLoc, "private2.key.delItem");
	DeleteAttribute(rLoc, "private2.money");
	DeleteAttribute(rLoc, "private2.items");
	DeleteAttribute(pchar, "questTemp.FMQT.Open");
	DeleteAttribute(pchar, "questTemp.FMQT.Common");
}

void FMQT_Begin() // 
{
	chrDisableReloadToLocation = false;
	string sLoc = "CommonBedroom";
	if (pchar.questTemp.FMQT == "begin_serveroom") sLoc = "CommonResidence_4";
	else sLoc = "Tortuga_townhallBedroom"; // Rebbebion, если плохая репутация, будет ждать сразу в будуаре
	pchar.quest.FMQT_start.win_condition.l1 = "location";
	pchar.quest.FMQT_start.win_condition.l1.location = sLoc;
	pchar.quest.FMQT_start.win_condition.l2 = "HardHour";
	pchar.quest.FMQT_start.win_condition.l2.hour = 18.00;
	pchar.quest.FMQT_start.function = "FMQT_WifeMeeting";
	pchar.quest.FMQT_late.win_condition.l1 = "Timer";
	pchar.quest.FMQT_late.win_condition.l1.date.hour  = 20.0;
	pchar.quest.FMQT_late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
	pchar.quest.FMQT_late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.FMQT_late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
	pchar.quest.FMQT_late.function = "FMQT_Late";
	pchar.questTemp.FMQT.Common = "true";
}

void FMQT_Late(string qName) // 
{
	pchar.quest.FMQT_start.over = "yes";
	pchar.questTemp.FMQT = "fail";
	AddQuestRecord("FMQ_Tortuga", "3");
	CloseQuestHeader("FMQ_Tortuga");
	FMQT_ClearChest();
}

void FMQT_WifeMeeting(string qName) // 
{
	pchar.quest.FMQT_late.over = "yes";
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("FMQT_wife", "Levaser_Wife", "woman", "towngirl", 5, FRANCE, -1, false, "quest"));
	SetFantomParamFromRank(sld, 5, true);
	sld.name = StringFromKey("FMQ_47");
	sld.lastname = StringFromKey("FMQ_48");
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Tortuga.c";
	if (pchar.questTemp.FMQT == "begin_serveroom") sld.Dialog.currentnode = "wife";
	else sld.Dialog.currentnode = "wife_8";
	RemoveAllCharacterItems(sld, true);
	LAi_SetImmortal(sld, true);
	LAi_SetLoginTime(sld, 6.0, 20.0);
	ChangeCharacterAddressGroup(sld, pchar.location, "barmen", "stay");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	AddLandQuestMark(sld, "questmarkmain");
}

void FMQT_HuberTime(string qName) // 
{
	pchar.questTemp.FMQT = "fail";
	AddQuestRecord("FMQ_Tortuga", "5");
	CloseQuestHeader("FMQ_Tortuga");
	FMQT_ClearChest();
}

void FMQT_TavernTime(string qName) // 
{
	pchar.questTemp.FMQT = "fail";
	AddQuestRecord("FMQ_Tortuga", "8");
	CloseQuestHeader("FMQ_Tortuga");
	FMQT_ClearChest();
}

void FMQT_KeyTime(string qName) // 
{
	ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
	sld = CharacterFromID("FMQT_wife");
	sld.lifeday = 0;
	if (CheckCharacterItem(pchar, "kaleuche_key")) // не вскрывал сундук
	{
		RemoveItems(pchar, "kaleuche_key", 1);
		AddQuestRecord("FMQ_Tortuga", "12");
		pchar.questTemp.FMQT = "fail";
	}
	else 
	{
		AddQuestRecord("FMQ_Tortuga", "13");
		ChangeCharacterHunterScore(PChar, "frahunter", 30);
		pchar.questTemp.FMQT = "end";
		FMQ_Count();
	}
	CloseQuestHeader("FMQ_Tortuga");
	FMQT_ClearChest();
}

void FMQT_KeyNextDay() // 
{
	pchar.quest.FMQT_next_day.win_condition.l1 = "Timer";
	pchar.quest.FMQT_next_day.win_condition.l1.date.hour  = 6.0;
	pchar.quest.FMQT_next_day.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.FMQT_next_day.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.FMQT_next_day.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.FMQT_next_day.function = "FMQT_PlaceWife";
	pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
	pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
	pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
}

void FMQT_PlaceWife(string qName) // ставим жену Левассера в будуар 
{
	sld = CharacterFromID("FMQT_wife");
	LAi_CharacterEnableDialog(sld);
	sld.Dialog.currentnode = "wife_15";
	AddLandQuestMark(sld, "questmarkmain");
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Tortuga_townhallBedroom", "barmen", "stay");
}

void FMQT_Deceive() // 
{
	sld = CharacterFromID("FMQT_wife");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5.0);
	chrDisableReloadToLocation = false;
	pchar.quest.FMQT_deceive_fin.win_condition.l1 = "Timer";
	pchar.quest.FMQT_deceive_fin.win_condition.l1.date.hour  = 18.0;
	pchar.quest.FMQT_deceive_fin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.FMQT_deceive_fin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.FMQT_deceive_fin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.FMQT_deceive_fin.function = "FMQT_DeceiveFinal";
	AddQuestRecord("FMQ_Tortuga", "16");
	FMQT_ClearChest();
}

void FMQT_DeceiveFinal(string qName) // провальный финал - прогоняют
{
	sld = CharacterFromID("FMQT_wife");
	LAi_CharacterEnableDialog(sld);
	sld.Dialog.currentnode = "wife_27";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Tortuga_townhallBedroom", "barmen", "stay");
}

void FMQT_MercenEnter(string qName) // входит наемник 
{
	pchar.questTemp.FMQT = "chest_open";
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
	LAi_group_Delete("EnemyFight");
	sld = GetCharacter(NPC_GenerateCharacter("Duran", "Claude_Durand", "man", "man", 1, FRANCE, -1, false, "soldier"));
	sld.name = StringFromKey("FMQ_49");
	sld.lastname = StringFromKey("FMQ_50");
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Tortuga.c";
	sld.Dialog.currentnode = "mercen";
	sld.rank = 15;
	sld.reputation = 25;
	sld.alignment = "bad";
	LAi_SetHP(sld, 180, 180);
	SetSelfSkill(sld, 45, 50, 45, 45, 35);
	SetShipSkill(sld, 25, 10, 20, 20, 20, 20, 20, 20, 30);
	SetSPECIAL(sld, 8, 5, 8, 4, 6, 8, 5);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	if (MOD_SKILL_ENEMY_RATE > 4)
	{
		SetCharacterPerk(sld, "Sliding");
		sld.cirassId = Items_FindItemIdx("cirass1");
		sld.MultiFighter = 1.5;
		sld.MultiShooter = 2.0;
	}
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Tireless");
	sld.SuperShooter = true;
	EquipCharacterByArtefact(sld, "indian_1");
	EquipCharacterByArtefact(sld, "indian_7");
	EquipCharacterByArtefact(sld, "indian_4");
	GiveItem2Character(sld, "blade_12");
	sld.equip.blade = "blade_12";
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "pistol1");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 20);
	AddItems(sld, "gunpowder", 20);
	int i = makeint(MOD_SKILL_ENEMY_RATE/3);
	int n = 1+i;
	TakeNItems(sld, "potion1", n);
	TakeNItems(sld, "potion2", i);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	ChangeCharacterAddressGroup(sld, "Tortuga_townhallRoom", "reload", "reload1");
	LAi_SetCheckMinHP(sld, 20, true, "FMQT_MercenTalk");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	// таймер сутки на отдачу
	SetFunctionTimerCondition("FMQT_GemsTimeOver", 0, 0, 1, false);
}

void FMQT_GemsTimeOver(string qName) // не отдал камни
{
	sld = CharacterFromID("FMQT_wife");
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "none", "", "");
	AddQuestRecord("FMQ_Tortuga", "13");
	ChangeCharacterHunterScore(PChar, "frahunter", 30);
	pchar.questTemp.FMQT = "end";
	FMQ_Count();
	CloseQuestHeader("FMQ_Tortuga");
	FMQT_ClearChest();
}

void FMQT_WifeFinalTalk() // 
{
	sld = CharacterFromID("FMQT_wife");
	AddLandQuestMark(sld, "questmarkmain");
	LAi_CharacterEnableDialog(sld);
	if (CheckAttribute(pchar, "questTemp.FMQT.Roomfight")) sld.Dialog.currentnode = "wife_21";
	else sld.Dialog.currentnode = "wife_21x";
}

void FMQT_MercenAttackRoom(string qName) // 
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
	LAi_group_Delete("EnemyFight");
	sld = CharacterFromID("Duran");
	LAi_SetImmortal(sld, false);
	ChangeCharacterAddressGroup(sld, "Tortuga_townhallBedroom", "reload", "reload1");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "FMQT_MercenDieInRoom");
	sld = CharacterFromID("FMQT_wife");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 5.0);
}

void FMQT_FinalNoJewelry() // 
{
	sld = CharacterFromID("FMQT_wife");
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
	chrDisableReloadToLocation = false;
	pchar.questTemp.FMQT = "end";
	FMQ_Count();
	AddQuestRecord("FMQ_Tortuga", "20");
	CloseQuestHeader("FMQ_Tortuga");
	FMQT_ClearChest();
	ChangeCharacterHunterScore(PChar, "frahunter", 10);
}

void FMQT_FinalNoSex() // 
{
	sld = CharacterFromID("FMQT_wife");
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
	chrDisableReloadToLocation = false;
	pchar.questTemp.FMQT = "end";
	FMQ_Count();
	AddQuestRecord("FMQ_Tortuga", "21");
	CloseQuestHeader("FMQ_Tortuga");
	FMQT_ClearChest();
	AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
	AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
	AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
}

void FMQT_FinalWithSex() // 
{
	WaitDate("", 0, 0, 0, 2, 10); //крутим время
	RecalculateJumpTable();
	sld = CharacterFromID("FMQT_wife");
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
	if (CheckAttribute(pchar, "questTemp.FMQT.Caution")) // заполним сундук бабы
	{
		AddQuestRecord("FMQ_Tortuga", "24");
		DeleteAttribute(pchar, "questTemp.FMQT.Caution");
		pchar.GenQuestBox.Tortuga_townhallBedroom = true;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.money = 5000;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.gold_dublon = 50;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.totem_03 = 1;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.potionwine = 3;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.jewelry42 = 1;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.jewelry43 = 1;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.jewelry41 = 2;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.jewelry40 = 1;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.jewelry45 = 1;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.jewelry46 = 2;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.amulet_7 = 1;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.amulet_2 = 1;
		pchar.GenQuestBox.Tortuga_townhallBedroom.box1.items.amulet_3 = 1;
		SetFunctionTimerCondition("FMQT_ClearWifeChest", 0, 0, 1, false);
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
		
		PChar.quest.FMQT_ObchistilSunduk.win_condition.l1 = "locator";
		PChar.quest.FMQT_ObchistilSunduk.win_condition.l1.location = "Tortuga_townhallBedroom";
		PChar.quest.FMQT_ObchistilSunduk.win_condition.l1.locator_group = "box";
		PChar.quest.FMQT_ObchistilSunduk.win_condition.l1.locator = "box1";
		PChar.quest.FMQT_ObchistilSunduk.function = "FMQT_ObchistilSunduk";
		
		PChar.quest.FMQT_Ushel.win_condition.l1 = "ExitFromLocation";
		PChar.quest.FMQT_Ushel.win_condition.l1.location = PChar.location;
		PChar.quest.FMQT_Ushel.function = "FMQT_ClearWifeChest";
	}
	else
	{
		// шарим по карманам ГГ
		if (sti(Pchar.money) >= 50000) Pchar.money = sti(Pchar.money)-25000;
		else Pchar.money = sti(Pchar.money)/2;
		AddQuestRecord("FMQ_Tortuga", "22");
	}
	chrDisableReloadToLocation = false;
	pchar.questTemp.FMQT = "end";
	FMQ_Count();
	CloseQuestHeader("FMQ_Tortuga");
	FMQT_ClearChest();
	AddCharacterExpToSkill(pchar, "Leadership", 400);//авторитет
	AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
	AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
}

void FMQT_ClearWifeChest(string qName) // 
{
	DeleteAttribute(pchar, "GenQuestBox.Tortuga_townhallBedroom");
	DeleteQuestCondition("FMQT_ObchistilSunduk");
	DeleteQuestCondition("FMQT_ClearWifeChest");
}

void FMQT_ObchistilSunduk(string qName)
{
	Box_OnLoadLocation(loadedLocation);
	pchar.questTemp.FMQT_ObchistilSunduk = true;
}

// --> ФМК-Порт Пренс
void FMQP_Activation(string qName) // 
{
	// belamour legendary edition -->
	if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED) return;
	// <-- legendary edition
	pchar.quest.FMQP_begin.win_condition.l1 = "location";
	pchar.quest.FMQP_begin.win_condition.l1.location = "PortPax_tavern";
	pchar.quest.FMQP_begin.win_condition.l2 = "Hour";
	pchar.quest.FMQP_begin.win_condition.l2.start.hour = 8.00;
	pchar.quest.FMQP_begin.win_condition.l2.finish.hour = 20.00;
	pchar.quest.FMQP_begin.function = "FMQP_Begin";
}

void FMQP_Begin(string qName) // 
{
	pchar.questTemp.FMQP = "begin";
	sld = CharacterFromID("PortPax_waitress");
	AddLandQuestMark(sld, "questmarkmain");
	// приведем в порядок плантацию Порто-Белло без НИ
	ref loc = &Locations[FindLocation("PortoBello_Plantation")];
	loc.reload.l1.name = "reload2_back";
	loc.reload.l1.go = "PortoBello_ExitTown";
	loc.reload.l1.emerge = "reload2";
	loc.reload.l1.autoreload = "1";
	loc.reload.l1.label = "ExitTown";
	loc.locators_radius.reload.reload2_back = 2.5;
	loc = &Locations[FindLocation("PortoBello_ExitTown")];
	loc.reload.l2.emerge = "reload2";
	loc.reload.l2.autoreload = "1";
}

void FMQP_Remove(string qName) // 
{
	DeleteAttribute(pchar, "questTemp.FMQP");
	sld = CharacterFromID("PortPax_waitress");
	LAi_SetWaitressType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	LocatorReloadEnterDisable("Portpax_town", "reload4_back", false);
}

void FMQP_InRoom(string qName) // 
{
	DoQuestReloadToLocation("Portpax_tavern_upstairs", "quest", "quest4", "FMQP_InRoom");
}

void FMQP_SantoDomingoOver(string qName) // 
{
	pchar.quest.FMQP_sdm.over = "yes";
	pchar.questTemp.FMQP = "fail";
	AddQuestRecord("FMQ_Portpax", "2");
	CloseQuestHeader("FMQ_Portpax");
	LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
	DeleteAttribute(pchar, "GenQuestRandItem.CommonPirateHouse");
	ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
	DelMapQuestMarkCity("Santodomingo");
}

void FMQP_InSantoDomingo(string qName) // 
{
	LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", false);
	pchar.questTemp.FMQP = "sdm";
	// ставим засаду в коммон
	int iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank)/2-2;// Addon 2016-1 Jason пиратская линейка
	int iScl = 15 + sti(pchar.rank);
	sld = GetCharacter(NPC_GenerateCharacter("FMQP_Ugo", "citiz_19", "man", "man", iRank, PIRATE, 2, false, "soldier"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_05","blade_07"), "pistol1", "bullet", iScl*2);
	sld.name = StringFromKey("FMQ_51");
	sld.lastname = StringFromKey("FMQ_52");
	ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto", "goto6");
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_PortPax.c";
	sld.Dialog.currentnode = "ugo";
	LAi_SetImmortal(sld, true);
	LAi_SetStayType(sld);
	sld.talker = 9;
	// записку
	sld = ItemsFromID("letter_parol");
	ChangeItemDescribe("letter_parol", "itmdescr_letter_parol_FMQP");
	sld.model = "letter";
	pchar.GenQuestRandItem.CommonPirateHouse = true;
	pchar.GenQuestRandItem.CommonPirateHouse.randitem2 = "letter_parol";
}

void FMQP_SantoDomingoFight(string qName) // 
{
	chrDisableReloadToLocation = true;
	int iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank)/2-2;// Addon 2016-1 Jason пиратская линейка
	int iScl = 10 + sti(pchar.rank);
	LAi_group_Delete("EnemyFight");
	sld = CharacterFromID("FMQP_Ugo");
	LAi_SetImmortal(sld, false);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (int i=3; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQP_bandos_"+i, "citiz_2"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_05","blade_07"), "pistol1", "bullet", iScl);
		ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "FMQP_SantoDomingoAfterFight");
	LAi_SetFightMode(pchar, true);
	// кладем настоящего Уго
	sld = GetCharacter(NPC_GenerateCharacter("FMQP_Ugo_x", "citiz_19", "man", "man", 5, PIRATE, 1, false, "soldier"));
	SetFantomParamFromRank(sld, 5, true);
	RemoveAllCharacterItems(sld, true);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	AddLandQuestMark(sld, "questmarkmain");
	ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "sit", "sit1");
	LAi_SetSitType(sld);
	LAi_KillCharacter(sld);
}

void FMQP_FindLetter(string qName) // 
{
	AddQuestRecord("FMQ_Portpax", "4");
	DoQuestFunctionDelay("FMQP_DomingoEnter", 5.0);
}

void FMQP_DomingoEnter(string qName) // 
{
	sld = CharacterFromID("FMQP_noble");
	sld.Dialog.currentnode = "noble_5";
	sld.greeting = "Domingo_1"
	ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void FMQP_OnBoard(string qName) // 
{
	DoQuestReloadToLocation("Santodomingo_tavern", "tables", "stay1", "FMQP_OnBoard");
}

void FMQP_SetRaiders(string qName) // 
{
	if(bImCasual) return;
	int iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);// Addon 2016-1 Jason пиратская линейка
	int iScl = 10 + 2*sti(pchar.rank);
	int iShipType = GetRandomShipType(GetClassFlag(sti(RealShips[sti(pchar.ship.type)].Class)), FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY);
	string sGroup = "FMQP_SeaGroup";
	Group_FindOrCreateGroup(sGroup);
	sld = GetCharacter(NPC_GenerateCharacter("FMQP_Follower", "mercen_23", "man", "man", iRank, SPAIN, 30, true, "quest"));
	FantomMakeSmallSailor(sld, iShipType, "", -1, iScl, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_06", "pistol1", "bullet", 150);
	sld.Ship.Mode = "pirate";	
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;
	sld.Coastal_Captain = true;
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "HardHitter");
	sld.ship.Crew.Morale = 20+5*MOD_SKILL_ENEMY_RATE;
	ChangeCrewExp(sld, "Sailors", 20+5*MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Cannoners", 20+5*MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Soldiers", 20+5*MOD_SKILL_ENEMY_RATE);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "Galleon_red";
    sld.mapEnc.Name = StringFromKey("FMQ_53");
	Map_CreateCoolWarrior("", sld.id, 50);
}

void FMQP_PortobelloTimeOver(string qName) // 
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.FMQP_PortobelloTimeOver.over"))
			DeleteAttribute(pchar,"quest.FMQP_PortobelloTimeOver.over");
		NewGameTip(StringFromKey("FMQ_15"));
		SetFunctionTimerCondition("FMQP_PortobelloTimeOver", 0, 0, 20, false);
		return;
	}
	pchar.questTemp.FMQP = "time_over";
	SetFunctionTimerCondition("FMQP_PortobelloFail", 0, 0, 10, false);
	DelMapQuestMarkCity("Portobello");
}

void FMQP_PortobelloFail(string qName) // 
{
	pchar.quest.FMQP_Plantation.over = "yes"; 
	pchar.quest.FMQP_Portobello_Fail.win_condition.l1 = "Location_Type";
	pchar.quest.FMQP_Portobello_Fail.win_condition.l1.location_type = "town";
	pchar.quest.FMQP_Portobello_Fail.function = "FMQP_PortobelloClear";
}

void FMQP_PortobelloClear(string qName) // 
{
	sld = CharacterFromID("FMQP_noble");
	RemovePassenger(pchar, sld);
	pchar.questTemp.FMQP = "fail";
	AddQuestRecord("FMQ_Portpax", "6");
	CloseQuestHeader("FMQ_Portpax");
	Log_Info(StringFromKey("FMQ_54"));
}

void FMQP_OnPlantation(string qName) // 
{
	chrDisableReloadToLocation = true;
	pchar.quest.FMQP_PortobelloTimeOver.over = "yes"; 
	pchar.quest.FMQP_PortobelloFail.over = "yes"; 
	LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", true);
	sld = CharacterFromID("FMQP_noble");
	RemovePassenger(pchar, sld);
	sld.Dialog.currentnode = "noble_23";
	ChangeCharacterAddressGroup(sld, "PortoBello_Plantation", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	if (pchar.questTemp.FMQP == "time_over")
	{
		pchar.quest.FMQP_plantation_late.win_condition.l1 = "location";
		pchar.quest.FMQP_plantation_late.win_condition.l1.location = "PortoBello_Plantation_Sp1";
		pchar.quest.FMQP_plantation_late.function = "FMQP_NoBook";
	}
	else
	{
		ChangeItemDescribe("Almanac", "itmdescr_Almanac_FMQP");
		sld = ItemsFromID("Almanac");
		sld.model = "open_book";
		pchar.GenQuestRandItem.PortoBello_Plantation_Sp1 = true;
		pchar.GenQuestRandItem.PortoBello_Plantation_Sp1.randitem1 = "Almanac";
		pchar.quest.FMQP_Book.win_condition.l1 = "item";
		pchar.quest.FMQP_Book.win_condition.l1.item = "Almanac";
		pchar.quest.FMQP_Book.function = "FMQP_FindBook";
	}
}

void FMQP_FindBook(string qName) // 
{
	Log_Info(StringFromKey("FMQ_55"));
	sld = CharacterFromID("FMQP_noble");
	sld.Dialog.currentnode = "noble_27";
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	LAi_ActorTurnToCharacter(sld, pchar);
	SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	pchar.questTemp.FMQP = "book";
}

void FMQP_PrepareUncle(string qName) // 
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("FMQP_noble");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	AddQuestRecord("FMQ_Portpax", "8");
	pchar.quest.FMQP_uncle.win_condition.l1 = "location";
	pchar.quest.FMQP_uncle.win_condition.l1.location = "PortoBello_Plantation";
	pchar.quest.FMQP_uncle.function = "FMQP_CreateUncleLuis";
}

void FMQP_CreateUncleLuis(string qName) // 
{
	LAi_LocationFightDisable(&Locations[FindLocation("PortoBello_Plantation")], true);
	// дядюшка
	int iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank)-2;// Addon 2016-1 Jason пиратская линейка
	int iScl = 15 + 2*sti(pchar.rank); // may-16
	string sBlade = "blade_04";
	if (MOD_SKILL_ENEMY_RATE < 6) sBlade = "blade_12";
	if (MOD_SKILL_ENEMY_RATE > 8) sBlade = "topor_04";
	string sPistol = "pistol6";
	if (MOD_SKILL_ENEMY_RATE > 8) sPistol = "pistol4";
	ref chr = GetCharacter(NPC_GenerateCharacter("FMQP_Uncle", "citiz_1", "man", "man", iRank, SPAIN, -1, false, "soldier"));
	FantomMakeCoolFighter(chr, iRank, iScl, iScl, "blade_15", "pistol5", "bullet", iScl*2);
	chr.name = StringFromKey("FMQ_56");
	chr.lastname = StringFromKey("FMQ_57");
	chr.Dialog.Filename = "Quest\LineMiniQuests\FMQ_PortPax.c";
	chr.Dialog.currentnode = "uncle";
	DeleteAttribute(chr, "SaveItemsForDead");
	DeleteAttribute(chr, "DontClearDead");
	ChangeCharacterAddressGroup(chr, "PortoBello_Plantation", "goto", "goto21");
	LAi_SetActorType(chr);
	LAi_ActorDialog(chr, pchar, "", -1, 0);
	// гарды
	for (int i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQP_guard_"+i, "citiz_5"+i, "man", "man", iRank, SPAIN, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, sBlade, sPistol, "bullet", iScl*2);
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		if (MOD_SKILL_ENEMY_RATE > 6)
		{
			SetCharacterPerk(sld, "SwordplayProfessional");
			sld.cirassId = Items_FindItemIdx("cirass2");
		}
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, "PortoBello_Plantation", "goto", "goto22");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, chr, "", -1);
	}
}

void FMQP_UncleExit(string qName) // 
{
	DoQuestReloadToLocation("Portobello_exittown", "reload", "reload2", "FMQP_UncleExit");
}

void FMQP_OpenPlantation(string qName) // 
{
	LocatorReloadEnterDisable("Portobello_exittown", "reload2_back", false);
}

void FMQP_PlantatonPause(string qName) // 
{
	LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
	chrDisableReloadToLocation = false;
	bQuestDisableMapEnter = true;
	sld = CharacterFromID("FMQP_noble");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "houseSp1", "none", "", "", "", 20.0);
	pchar.questTemp.FMQP = "reward";
	AddQuestRecord("FMQ_Portpax", "11");
	pchar.quest.FMQP_Pause.win_condition.l1 = "Timer";
	pchar.quest.FMQP_Pause.win_condition.l1.date.hour  = 8.0;
	pchar.quest.FMQP_Pause.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.FMQP_Pause.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.FMQP_Pause.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.FMQP_Pause.function = "FMQP_PlantatonReward";
	ref rloc = &Locations[FindLocation("PortoBello_Plantation")];
	rloc.soldiers = true;
}

void FMQP_PlantatonReward(string qName) // 
{
	sld = CharacterFromID("FMQP_noble");
	sld.Dialog.currentnode = "noble_39";
	AddLandQuestMark(sld, "questmarkmain");
	ChangeCharacterAddressGroup(sld, "PortoBello_Plantation_Sp1", "goto", "goto1");
	LAi_SetStayType(sld);
	sld.talker = 9;
}

void FMQP_ReceiveReward(string qName) // 
{
	bQuestDisableMapEnter = false;// Addon 2016-1 Jason пиратская линейка
	sld = CharacterFromID("FMQP_noble");
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 4.0);
	pchar.questTemp.FMQP = "end";
	FMQ_Count();
	AddQuestRecord("FMQ_Portpax", "12");
	CloseQuestHeader("FMQ_Portpax");
	GiveItem2Character(pchar, "indian_6"); 
	GiveItem2Character(pchar, "amulet_10"); 
	GiveItem2Character(pchar, "obereg_10"); 
	GiveItem2Character(pchar, "spyglass3"); 
	GiveItem2Character(pchar, "blade_16"); 
	AddCharacterGoods(pchar, GOOD_COFFEE, 200);
	ChangeCharacterComplexReputation(pchar, "authority", 3);
	ChangeCharacterComplexReputation(pchar, "fame", 2);
	AddComplexSelfExpToScill(50, 50, 50, 50);
	AddCharacterExpToSkill(pchar, "Leadership", 200);
	AddCharacterExpToSkill(pchar, "Fortune", 100);
}

void FMQP_NoBook(string qName) // 
{
	pchar.quest.FMQP_no_book.win_condition.l1 = "ExitFromLocation";
	pchar.quest.FMQP_no_book.win_condition.l1.location = pchar.location;
	pchar.quest.FMQP_no_book.function = "FMQP_LateFinal";
}

void FMQP_LateFinal(string qName) // 
{
	sld = CharacterFromID("FMQP_noble");
	sld.Dialog.currentnode = "noble_46";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

// --> ФМК-Последний урок
void FMQL_Start() // накручиваем гида и выдаем ему шняву
{
	// belamour legendary edition -->
	if (CheckAttribute(pchar, "questTemp.HWIC")) return;
	// <-- legendary edition
	sld = GetCharacter(NPC_GenerateCharacter("Guide_y", "Guide_1", "man", "man", 10, FRANCE, -1, true, "officer"));
	FantomMakeSmallSailor(sld, SHIP_SHNYAVA, StringFromKey("FMQ_58"), CANNON_TYPE_CANNON_LBS16, 45, 45, 45, 45, 45);
	sld.name = StringFromKey("FMQ_59");
	sld.lastname = StringFromKey("FMQ_60");
	sld.dialog.FileName = "Quest\LineMiniQuests\FMQ_Lesson.c";
	sld.dialog.currentnode = "greguar";
	//sld.talker = 9;
	sld.rank = 25;
	int iHp = MOD_SKILL_ENEMY_RATE*10+300;
	LAi_SetHP(sld, iHp, iHp);
	SetSelfSkill(sld, 80, 80, 80, 80, 50);
	SetShipSkill(sld, 50, 80, 35, 30, 50, 20, 30, 20, 80);
	SetSPECIAL(sld, 9, 5, 8, 6, 5, 10, 8);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "BladeDancer");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	GiveItem2Character(sld, "blade_30");
	EquipCharacterbyItem(sld, "blade_30");
	GiveItem2Character(sld, "pistol6");
	EquipCharacterbyItem(sld, "pistol6");
	sld.cirassId = Items_FindItemIdx("cirass4");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 30);
	AddItems(sld, "gunpowder", 30);
	TakeNItems(sld, "potion2", 5);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	SetCrewQuantityOverMax(sld, 100);
	UpgradeShipParameter(sld, "Capacity");
	sld.ship.Crew.Morale = 90;
	sld.Ship.Crew.Exp.Sailors = 90;
	sld.Ship.Crew.Exp.Cannoners = 60;
	sld.Ship.Crew.Exp.Soldiers = 60;
	NullCharacterGoods(sld);
	AddCharacterGoods(sld, GOOD_BALLS, 200);
	AddCharacterGoods(sld, GOOD_GRAPES, 200);
	AddCharacterGoods(sld, GOOD_KNIPPELS, 200);
	AddCharacterGoods(sld, GOOD_BOMBS, 200);
	AddCharacterGoods(sld, GOOD_FOOD, 400);
	AddCharacterGoods(sld, GOOD_POWDER, 500);
	AddCharacterGoods(sld, GOOD_WEAPON, 150);
	AddCharacterGoods(sld, GOOD_MEDICAMENT, 100);
	ChangeCharacterAddressGroup(sld, "Fortfrance_town", "quest", "quest1");
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
}

void FMQL_DeleteGuide(string qName) // удаляем гида на 15 ранге
{
	sld = CharacterFromID("Guide_y");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0;
}

void FMQL_Begin() // 
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Guide_y");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	pchar.quest.FMQL_shipfail.win_condition.l1 = "NPC_Death";//прерывание на потопление 
	pchar.quest.FMQL_shipfail.win_condition.l1.character = "Guide_y";
	pchar.quest.FMQL_shipfail.function = "FMQL_ShipFail";
	SetFunctionTimerCondition("FMQL_TimeOver", 0, 0, 7, false);
	pchar.quest.FMQL_cumana.win_condition.l1 = "location";
	pchar.quest.FMQL_cumana.win_condition.l1.location = "Cumana";
	pchar.quest.FMQL_cumana.function = "FMQL_ArriveCumana";
	AddQuestRecord("FMQ_Lesson", "1");
	AddMapQuestMarkShore("Shore18", true);
	pchar.questTemp.FMQL = "toShore18";
	// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
	pchar.GenQuest.SeaHunter2Pause = true;
	SeaHunter_Delete();
}

void FMQL_ShipFail(string qName) // 
{
	pchar.quest.FMQL_cumana.over = "yes";
	pchar.quest.FMQL_TimeOver.over = "yes";
	ChangeCharacterHunterScore(PChar, "frahunter", 10);
	ChangeCharacterComplexReputation(pchar, "nobility", -5);
	AddQuestRecord("FMQ_Lesson", "11");
	CloseQuestHeader("FMQ_Lesson");
	pchar.questTemp.FMQL = "fail";
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void FMQL_TimeOver(string qName) // 
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.FMQL_TimeOver.over"))
			DeleteAttribute(pchar,"quest.FMQL_TimeOver.over");
		NewGameTip(StringFromKey("FMQ_15"));
		SetFunctionTimerCondition("FMQL_TimeOver", 0, 0, 7, false);
		return;
	}
	pchar.quest.FMQL_cumana.over = "yes";
	pchar.quest.FMQL_shipfail.over = "yes";
	sld = CharacterFromID("Guide_y");
	sld.lifeday = 0;
	RemoveCharacterCompanion(pchar, sld);
	AddQuestRecord("FMQ_Lesson", "4");
	CloseQuestHeader("FMQ_Lesson");
	pchar.questTemp.FMQL = "fail";
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
	DelMapQuestMarkShore("Shore18");
}

void FMQL_ArriveCumana(string qName) // у Куманы - ставим англов и голландцев
{
	pchar.quest.FMQL_TimeOver.over = "yes";
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	pchar.GenQuest.CannotWait = true;
	Group_FindOrCreateGroup("FMQL_Enggroup");
	Group_FindOrCreateGroup("FMQL_Holgroup");
	int iShip;
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_EngCap_"+i, "off_eng_"+i, "man", "man", 25, ENGLAND, 5, true, "officer"));
		if (i == 1) iShip = SHIP_FRIGATE;
		else iShip = SHIP_CORVETTE;
		FantomMakeCoolSailor(sld, iShip, "", CANNON_TYPE_CULVERINE_LBS18, 60, 60, 60);
		FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol1", "bullet", 150);
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		Character_SetAbordageEnable(sld, false);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.Ship.Mode = "war";
		SetCharacterPerk(sld, "MusketsShoot");
		Group_AddCharacter("FMQL_Enggroup", "FMQL_EngCap_"+i);
	}
	Group_SetGroupCommander("FMQL_Enggroup", "FMQL_EngCap_1");
	Group_SetAddress("FMQL_Enggroup", "Cumana", "quest_ships", "quest_ship_8");
	Group_SetTaskAttack("FMQL_Enggroup", "FMQL_Holgroup");
	Group_LockTask("FMQL_Enggroup");
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_HolCap_"+i, "off_hol_"+i, "man", "man", 25, HOLLAND, 5, true, "officer"));
		if (i == 1) iShip = SHIP_GALEON_H;
		else iShip = SHIP_XebekVML;
		FantomMakeCoolSailor(sld, iShip, "", CANNON_TYPE_CULVERINE_LBS18, 60, 60, 60);
		FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol1", "bullet", 150);
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		Character_SetAbordageEnable(sld, false);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.Ship.Mode = "war";
		SetCharacterPerk(sld, "MusketsShoot");
		Group_AddCharacter("FMQL_Holgroup", "FMQL_HolCap_"+i);
	}
	Group_SetGroupCommander("FMQL_Holgroup", "FMQL_HolCap_1");
	Group_SetAddress("FMQL_Holgroup", "Cumana", "quest_ships", "quest_ship_7");
	Group_SetTaskAttack("FMQL_Holgroup", "FMQL_Enggroup");
	Group_LockTask("FMQL_Holgroup");
	// прерывание на высадку
	pchar.quest.FMQL_bdls.win_condition.l1 = "location";
	pchar.quest.FMQL_bdls.win_condition.l1.location = "shore18";
	pchar.quest.FMQL_bdls.function = "FMQL_AbandonBdlS";
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void FMQL_AbandonBdlS(string qName) // 
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
	pchar.quest.FMQL_shipfail.over = "yes";
	pchar.questTemp.FMQL = "shore";
	chrDisableReloadToLocation = true;
	int oRank = sti(pchar.rank)+5;
	int eRank = sti(pchar.rank);
	int oScl = 20 + 2*sti(pchar.rank);
	int eScl = 10 + 2*sti(pchar.rank);// Addon 2016-1 Jason пиратская линейка
	// ставим наших
	sld = CharacterFromID("Guide_y");
	RemoveCharacterCompanion(pchar, sld);
	ChangeCharacterAddressGroup(sld, "Shore18", "goto", "goto8");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=5; i++)
	{
		if (i == 5)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQL_sailor_"+i, "mush_ctz_5", "man", "mushketer", oRank, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, oRank, oScl, oScl, "", "mushket3", "grapeshot", oScl*3);
			TakeNItems(pchar, "grapeshot", 40);
			TakeNItems(pchar, "gunpowder", 40);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
			ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto8");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQL_sailor_"+i, "citiz_3"+i, "man", "man", oRank, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, oRank, oScl, oScl, LinkRandPhrase("blade_08","blade_11","blade_14"), "pistol1", "bullet", oScl*2);
		}
		ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto7");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// первая группа индеев
	PlaySound("interface\abordage_wining.wav");
	LAi_group_Delete("EnemyFight");
	for (i=1; i<=10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_indian_"+i, "miskito_"+(rand(5)+1), "man", "man", eRank, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, eRank, eScl, eScl, RandPhraseSimple("topor_05","slave_02"), "", "", eScl*2);
		ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto3");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "FMQL_FirstBattleEnd");
	LAi_SetFightMode(pchar, true);
}

void FMQL_SecondCoastBattle() // 
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;// Addon 2016-1 Jason пиратская линейка
	int iScl = 25 + 2*sti(pchar.rank);
	// вторая группа индеев
	PlaySound("interface\abordage_wining.wav");
	for (int i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_indian_add_"+i, "miskito_"+(rand(5)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_01","blade_02"), "", "", iScl*2);
		ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto3");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = CharacterFromID("Guide_y");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "FMQL_SecondBattleEnd");
	LAi_SetFightMode(pchar, true);
}

void FMQL_GoToJungle() // 
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("shore18", "boat", true);
	sld = CharacterFromID("Guide_y");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	for (int i=1; i<=5; i++)
	{
		sld = CharacterFromID("FMQL_sailor_"+i);
		if (LAi_GetCharacterHP(sld) > 0)
		{
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
	}
	pchar.quest.FMQL_jungle.win_condition.l1 = "location";
	pchar.quest.FMQL_jungle.win_condition.l1.location = "Common_jungle_01";
	pchar.quest.FMQL_jungle.function = "FMQL_InJungle";
	pchar.questTemp.BlackMark.IronsBlock = true;
}

void FMQL_InJungle(string qName) // в джунглях
{
	chrDisableReloadToLocation = true;
	int iRank = sti(pchar.rank)+8-makeint(MOD_SKILL_ENEMY_RATE/2);
	int iScl = 25 + 2*sti(pchar.rank);
	if (CheckAttribute(pchar, "questTemp.Prosper_fmql"))
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_Prosper", "Prospero_mush", "man", "mushketer", iRank, FRANCE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, 110, "", "mushket1", "cartridge", iScl*3);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
		sld.name = StringFromKey("FMQ_61");
		sld.lastname = StringFromKey("FMQ_62");
		sld.dialog.FileName = "Quest\LineMiniQuests\FMQ_Lesson.c";
		sld.dialog.currentnode = "prosper";
		sld.greeting = "prosper_vovremya";
		sld.cirassId = Items_FindItemIdx("cirass1");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_mercen", "mush_ctz_12", "man", "mushketer", iRank, FRANCE, -1, false, "soldier"));
		sld.dialog.FileName = "Quest\LineMiniQuests\FMQ_Lesson.c";
		sld.dialog.currentnode = "mercen";
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*3);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
	}
	ChangeCharacterAddressGroup(sld, "Common_jungle_01", "rld", "aloc0");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0); 
	for (int i=6; i<=10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_sailor_"+i, "citiz_"+(20+i), "man", "man", iRank, FRANCE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_03","blade_04","blade_06"), "pistol1", "bullet", iScl*2);
		ChangeCharacterAddressGroup(sld, "Common_jungle_01", "rld", "aloc4");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", 5.0);
	}
}

void FMQL_FailInShore() // 
{
	for (int i=1; i<=5; i++)
	{
		sld = CharacterFromID("FMQL_sailor_"+i);
		sld.lifeday = 0;
	}
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("shore18", "boat", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	AddQuestRecord("FMQ_Lesson", "2");
	CloseQuestHeader("FMQ_Lesson");
	pchar.questTemp.FMQL = "fail";
}

void FMQL_PrepareAttack() // стадо баранов
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "quest", "quest1");
	FMQL_OurWarriorsActivate();
	DoQuestFunctionDelay("FMQL_CreateCaribMushketer", 3.0);
}

void FMQL_OurWarriorsActivate() // 
{
	sld = CharacterFromID("Guide_y");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	if (GetCharacterIndex("FMQL_Prosper") != -1)
	{
		sld = CharacterFromID("FMQL_Prosper");
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	if (GetCharacterIndex("FMQL_mercen") != -1)
	{
		sld = CharacterFromID("FMQL_mercen");
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (int i=1; i<=10; i++)
	{
		if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
		{
			sld = CharacterFromID("FMQL_sailor_"+i);
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
}

void FMQL_PrepareSneakAttack() // засада
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "quest", "quest1");
	sld = CharacterFromID("Guide_y");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "rld", "aloc0", "", 5.0);
	if (GetCharacterIndex("FMQL_Prosper") != -1)
	{
		sld = CharacterFromID("FMQL_Prosper");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "rld", "aloc11", "", 5.0);
	}
	if (GetCharacterIndex("FMQL_mercen") != -1)
	{
		sld = CharacterFromID("FMQL_mercen");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "rld", "aloc11", "", 5.0);
	}
	for (int i=1; i<=10; i++)
	{
		if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
		{
			sld = CharacterFromID("FMQL_sailor_"+i);
			if (i == 5) sld.MusketerDistance = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "rld", "aloc"+i, "", 5.0);
		}
	}
	DoQuestFunctionDelay("FMQL_CreateCaribMushketer", 7.0);
}

void FMQL_CreateCaribMushketer(string qName) // вышли из леса крутые карибы с пушками
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;// Addon 2016-1 Jason пиратская линейка
	int iScl = 30 + 2*sti(pchar.rank);
	// третья группа индеев - мушкетеры
	for (int i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_canib_mush_"+i, "mush_cnb_"+(rand(2)+1), "man", "mushketer", iRank, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
		sld.name = GetIndianName(MAN);
		sld.lastname = "";
		ChangeCharacterAddressGroup(sld, "Common_jungle_01", "quest", "quest1");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "rld", "loc"+i, "", 5.0);
	}
	DoQuestFunctionDelay("FMQL_CreateCaribWarrior", 3.0);
}

void FMQL_CreateCaribWarrior(string qName) // вождь с командой
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 35 + 3*sti(pchar.rank);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	// вождь
	sld = GetCharacter(NPC_GenerateCharacter("FMQL_canib_chief", "canib_boss", "man", "man", iRank+5, PIRATE, -1, false, "native"));
	FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "topor_01", "pistol5", "bullet", iScl*3+50);
	ChangeCharacterAddressGroup(sld, "Common_jungle_01", "quest", "quest1");
	LAi_SetCheckMinHP(sld, 10, true, "FMQL_CanibBossAmulet");
	LAi_SetWarriorType(sld);
	// третья группа индеев - воины
	for (int i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_canib_"+i, "canib_"+i, "man", "man", iRank, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_04", "pistol1", "bullet", iScl*3);
		ChangeCharacterAddressGroup(sld, "Common_jungle_01", "quest", "quest1");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetWarriorType(sld);
	}
	if (pchar.questTemp.FMQL == "sneak") DoQuestFunctionDelay("FMQL_CreateCaribGo", 0.1);
	else DoQuestFunctionDelay("FMQL_CaribAttack", 0.5);
}

void FMQL_CaribAttack(string qName) // схватились с карибами
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("FMQL_canib_chief");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (int i=1; i<=4; i++)
	{
		sld = CharacterFromID("FMQL_canib_mush_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	for (i=1; i<=6; i++)
	{
		sld = CharacterFromID("FMQL_canib_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "FMQL_AfterCaribAttack");
	LAi_SetFightMode(pchar, true);
}

void FMQL_CreateCaribGo(string qName) // идут, пока не подозревают
{
	sld = CharacterFromID("FMQL_canib_chief");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "quest", "quest2", "", 5.0);
	for (int i=1; i<=6; i++)
	{
		sld = CharacterFromID("FMQL_canib_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "quest", "quest2", "", 5.0);
	}
	DoQuestFunctionDelay("FMQL_CaribShot", 5.0);
}

void FMQL_CaribShot(string qName) // залп из засады
{
	if (GetCharacterIndex("FMQL_Prosper") != -1)
	{
		sld = CharacterFromID("FMQL_Prosper");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "shot", "", 1.0);
	}
	if (GetCharacterIndex("FMQL_mercen") != -1)
	{
		sld = CharacterFromID("FMQL_mercen");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "shot", "", 1.0);
	}
	for (int i=5; i<=10; i++)
	{
		if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
		{
			if (i > 5 && i < 9) continue;
			sld = CharacterFromID("FMQL_sailor_"+i);
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "shot", "", 1.0);
		}
	}
	DoQuestFunctionDelay("FMQL_CaribDie", 1.3);
}

void FMQL_CaribDie(string qName) // 
{
	for (int i=3; i<=4; i++)
	{
		sld = CharacterFromID("FMQL_canib_mush_"+i);
		LAi_KillCharacter(sld);
	}
	sld = CharacterFromID("FMQL_canib_6");
	LAi_KillCharacter(sld);
	if (GetCharacterIndex("FMQL_sailor_5") != -1) 
	{
		sld = CharacterFromID("FMQL_canib_5");
		LAi_KillCharacter(sld);
	}
	FMQL_OurWarriorsActivate();
	DoQuestFunctionDelay("FMQL_CaribAttack", 1.0);
}

void FMQL_ClearAllCharacters() // тотальная чистка чаров
{
	if (GetCharacterIndex("Guide_y") != -1)
	{
		sld = CharacterFromID("Guide_y");
		sld.lifeday = 0;
	}
	if (GetCharacterIndex("FMQL_Prosper") != -1)
	{
		sld = CharacterFromID("FMQL_Prosper");
		sld.lifeday = 0;
	}
	if (GetCharacterIndex("FMQL_mercen") != -1)
	{
		sld = CharacterFromID("FMQL_mercen");
		sld.lifeday = 0;
	}
	for (int i=1; i<=10; i++)
	{
		if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
		{
			sld = CharacterFromID("FMQL_sailor_"+i);
			sld.lifeday = 0;
		}
	}
}

void FMQL_ReturnMartinique(string qName) // прибыли домой
{
	pchar.quest.FMQL_ReturnTimeOver.over = "yes";
	pchar.quest.FMQL_shipfail_1.over = "yes";
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	pchar.GenQuest.SmugglersBlock = "fortfrance_tavern";
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Guide_y");
	sld.Dialog.currentnode = "greguar_15";
	RemoveCharacterCompanion(pchar, sld);
	LAi_SetCurHPMax(sld);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	ChangeCharacterAddressGroup(sld, "Fortfrance_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	if (GetCharacterIndex("FMQL_Prosper") != -1)
	{
		sld = CharacterFromID("FMQL_Prosper");
		RemovePassenger(pchar, sld);
		sld.Dialog.currentnode = "prosper_9x";
		sld.greeting = "prosper_ostorozhnee";
		LAi_SetCurHPMax(sld);
		TakeNItems(sld, "potion2", 3);
		ChangeCharacterAddressGroup(sld, "Fortfrance_town", "reload", "reload4_back");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void FMQL_MeetingOnLamanten(string qName) // встреча на пляже Ламантен
{
	// ставим шняву
	sld = CharacterFromID("Guide_y");
	DeleteAttribute(sld, "chr_ai.poison"); // патч 17/1
	LAi_SetCurHPMax(sld);
	Group_AddCharacter("FMQL_GuideGroup", "Guide_y");
	Group_SetGroupCommander("FMQL_GuideGroup", "Guide_y");
	Group_SetAddress("FMQL_GuideGroup", "Martinique", "quest_ships", "quest_ship_10");
	Group_SetTaskNone("FMQL_GuideGroup");
	AddGeometryToLocation("Shore38", "smg");
	pchar.quest.FMQL_goods_over.win_condition.l1 			= "Timer";		// ugeen fix, плодил ошибки в compile.log
	pchar.quest.FMQL_goods_over.win_condition.l1.date.hour  = 2.0;
	pchar.quest.FMQL_goods_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
	pchar.quest.FMQL_goods_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.FMQL_goods_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
	pchar.quest.FMQL_goods_over.function = "FMQL_GoodsTimeOver";
	pchar.quest.FMQL_beach.win_condition.l1 = "Hour";
	pchar.quest.FMQL_beach.win_condition.l1.start.hour = 0.00;
	pchar.quest.FMQL_beach.win_condition.l1.finish.hour = 2.00;
	pchar.quest.FMQL_beach.win_condition.l2 = "location";
	pchar.quest.FMQL_beach.win_condition.l2.location = "Shore38";
	pchar.quest.FMQL_beach.win_condition.l3 = "Ship_location";
	pchar.quest.FMQL_beach.win_condition.l3.location = "Shore38";
	pchar.quest.FMQL_beach.function = "FMQL_OnLamantenBeach";
}

void FMQL_ShipFailReturn(string qName) // 
{
	pchar.quest.FMQL_return.over = "yes";
	pchar.quest.FMQL_ReturnTimeOver.over = "yes";
	ChangeCharacterHunterScore(PChar, "frahunter", 40);
	ChangeCharacterComplexReputation(pchar, "nobility", -20);
	AddQuestRecord("FMQ_Lesson", "12");
	CloseQuestHeader("FMQ_Lesson");
	pchar.questTemp.FMQL = "fail";
}

void FMQL_ReturnTimeOver(string qName) // 
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.FMQL_ReturnTimeOver.over"))
			DeleteAttribute(pchar,"quest.FMQL_ReturnTimeOver.over");
		NewGameTip(StringFromKey("FMQ_15"));
		SetFunctionTimerCondition("FMQL_ReturnTimeOver", 0, 0, 10, false);
		return;
	}
	pchar.quest.FMQL_return.over = "yes";
	pchar.quest.FMQL_shipfail_1.over = "yes";
	sld = CharacterFromID("Guide_y");
	sld.lifeday = 0;
	RemoveCharacterCompanion(pchar, sld);
	AddQuestRecord("FMQ_Lesson", "13");
	CloseQuestHeader("FMQ_Lesson");
	pchar.questTemp.FMQL = "fail";
	DelMapQuestMarkCity("FortFrance");
}

void FMQL_GoodsTimeOver(string qName) // 
{
	pchar.quest.FMQL_beach.over = "yes";
	LAi_LocationDisableOfficersGen("Shore38", false);
	LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], false);
	locations[FindLocation("Shore38")].DisableEncounters = false; // may-16
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	RemoveGeometryFromLocation("Shore38", "smg");
	sld = CharacterFromID("Guide_y");
	sld.lifeday = 0;
	AddQuestRecord("FMQ_Lesson", "14");
	CloseQuestHeader("FMQ_Lesson");
	pchar.questTemp.FMQL = "fail";
}

void FMQL_OnLamantenBeach(string qName) // на самом пляже
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;
	pchar.GenQuest.CannotWait = true;
	DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
	LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
	// контра
	for (int i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_contra_"+i, "citiz_2"+(i+6), "man", "man", 25, PIRATE, -1, false, "marginal"));
		SetFantomParamFromRank(sld, 25, true);
		sld.dialog.FileName = "Quest\LineMiniQuests\FMQ_Lesson.c";
		sld.Dialog.currentnode = "contra";
		sld.greeting = "smuggler";
		ChangeCharacterAddressGroup(sld, "Shore38", "smugglers", "smuggler0"+i);
		LAi_SetStayType(sld);
		sld.talker = 9;
		LAi_CharacterDisableDialog(sld);
	}
	// гид
	sld = CharacterFromID("Guide_y");
	sld.Dialog.currentnode = "greguar_17";
	LAi_SetCurHPMax(sld); // патч 17/1
	sld.LSC_clan = true; // may-16
	TakeNItems(sld, "potion2", makeint(MOD_SKILL_ENEMY_RATE/2)); // may-16
	sld.SaveItemsForDead = true; 
	sld.DontClearDead = true;
	ChangeCharacterAddressGroup(sld, "Shore38", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void FMQL_CreateGuidesWarriors() // ставим кодлу гида
{
	int iRank = 5;
	int iScl = 5; // may-16
	// индей со склопеттой
	sld = GetCharacter(NPC_GenerateCharacter("FMQL_Johnny", "mush_cnb_1", "man", "mushketer", iRank, PIRATE, -1, false, "native"));
	FantomMakeCoolFighter(sld, iRank, iScl, 50, "", "grape_mushket", "grenade", 0);
	sld.name = StringFromKey("FMQ_63");
	sld.lastname = StringFromKey("FMQ_64");
	SetSPECIAL(sld, 10, 10, 5, 3, 5, 10, 10);
	TakeNItems(sld, "grenade", 70); // may-16
	LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grenade");
	TakeNItems(sld, "potion2", makeint(MOD_SKILL_ENEMY_RATE/2)); // may-16
	//sld.cirassId = Items_FindItemIdx("cirass1");
	sld.LSC_clan = true; // may-16
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	ChangeCharacterAddressGroup(sld, "Shore38", "box", "box1");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, characterFromID("FMQL_contra_2"));
	// гарды
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_guard_"+i, "killer_"+(rand(4)+1), "man", "man", iRank, PIRATE, -1, false, "soldier")); // may-16
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_04", "", "", 0); // mitrokosta ослабление гардов
		ChangeCharacterAddressGroup(sld, "Shore38", "goto", "goto"+(i+1));
		//if (MOD_SKILL_ENEMY_RATE > 8) sld.MultiFighter = 4.0; // мультифайтер may-16 belamour legendary edition
		TakeNItems(sld, "potion2", makeint(MOD_SKILL_ENEMY_RATE/3)); // may-16
		//sld.cirassId = Items_FindItemIdx("cirass4");
		sld.LSC_clan = true; // may-16
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetActorType(sld);
	}
}
// Addon 2016-1 Jason пиратская линейка - это отключаю
void FMQL_MoneyForSelina(string qName) // 
{
	AddMoneyToCharacter(pchar, -20000);
	PlaySound("interface\notebook.wav");
	Log_Info(StringFromKey("FMQ_65"));
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool FMQ_QuestComplete(string sQuestName, string qname)
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Addon-2016 Jason, французские миниквесты (ФМК)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld, chr, rloc;
	int i, idx, iRank, iScl;
	
	bool condition = true;
	
	// ФМК-Гваделупа
	if (sQuestName == "FMQG_OnBoard") // 
	{
		sld = characterFromId("FMQG_pass_1");
		AddPassenger(pchar, sld, false);//добавить пассажира
		SetCharacterRemovable(sld, false);
		for (i=2; i<=3; i++)
		{
			sld = characterFromId("FMQG_pass_"+i);
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
		}
		chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "FMQG_KidnappingAttack") // атака на Пинетта
	{
		sld = characterFromId("FMQG_pass_1");
		sld.greeting = "Pinett_vstrecha";
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "TmpEnemy");
		LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
		for (i=1; i<=iTotalTemp; i++)
		{
			sld = characterFromId("FMQG_pinett_guard_"+i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "FMQG_KidnappingAfterFight");
		SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
	}
	else if (sQuestName == "FMQG_KidnappingAfterFight") // после боя
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("FMQG_pass_1");
		sld.Dialog.currentnode = "citizen_23";
		LAi_CharacterEnableDialog(sld);
		LAi_SetActorType(sld);
		if (pchar.questTemp.FMQG == "fail") LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
		else LAi_ActorDialog(sld, pchar, "", -1, 0);
		LAi_group_Delete("TmpEnemy");
		AddComplexSelfExpToScill(30, 30, 30, 30);
	}
	else if (sQuestName == "FMQG_KidnappingFail") // упустил
	{
		chrDisableReloadToLocation = false;
		sld = characterFromId("FMQG_pass_1");
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
		for (i=1; i<=iTotalTemp; i++)
		{
			sld = characterFromId("FMQG_pinett_guard_"+i);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		pchar.questTemp.FMQG = "fail";
		AddQuestRecord("FMQ_Guadeloupe", "21");
		CloseQuestHeader("FMQ_Guadeloupe");
		SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
		ChangeCharacterNationReputation(pchar, ENGLAND, -5);
	}
	else if (sQuestName == "FMQG_OnLighthouse") // на маяке
	{
		LocatorReloadEnterDisable("Mayak2", "reload1_back", true);
		sld = characterFromId("FMQG_pass_1");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Mayak2", "goto", "goto2");
		LAi_ActorFollow(sld, pchar, "", -1);
		pchar.quest.FMQG_Mayak1.win_condition.l1 = "location";
		pchar.quest.FMQG_Mayak1.win_condition.l1.location = "Barbados";
		pchar.quest.FMQG_Mayak1.function = "FMQG_KidnappingSucsess";
	}
	else if (sQuestName == "FMQG_KillersDestroy") // прибил наймитов
	{
		chrDisableReloadToLocation = false;
		pchar.questTemp.FMQG = "killers";
		AddQuestRecord("FMQ_Guadeloupe", "26");
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	
	// ФМК-Мартиника
	
	else if (sQuestName == "FMQM_Looking") // ковыряется в ящике
	{
		sld = characterFromId("FortFrance_shipyarder");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Barman_idle", "FMQM_Arest", 5.0);
	}
	else if (sQuestName == "FMQM_Arest") // якобы арест
	{
		iRank = MOD_SKILL_ENEMY_RATE+7;// Addon 2016-1 Jason пиратская линейка
		iScl = 25 + 2*sti(pchar.rank);
		LAi_SetPlayerType(pchar);
		sld = GetCharacter(NPC_GenerateCharacter("FMQM_officer", "off_fra_2", "man", "man", iRank, FRANCE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol1", "bullet", iScl*3);
		sld.name = StringFromKey("FMQ_66");
		sld.lastname = StringFromKey("FMQ_67");
		sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Martinique.c";
		sld.Dialog.currentnode = "officer";
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		if (MOD_SKILL_ENEMY_RATE < 7)
		{
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
		}
		else
		{
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			sld.cirassId = Items_FindItemIdx("cirass2");
		}
		ChangeCharacterAddressGroup(sld, "FortFrance_Shipyard", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "FMQM_ArestContinue") // 
	{
		sld = characterFromId("FMQM_officer");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_1", "FMQM_ArestReload", 5);
		InterfaceStates.Buttons.Save.enable = false;
	}
	else if (sQuestName == "FMQM_ArestReload") // в город
	{
		LAi_SetPlayerType(pchar);
		DoQuestReloadToLocation("FortFrance_town", "reload", "reload5", "FMQM_ArestFinal");
	}
	else if (sQuestName == "FMQM_ArestFinal") // Грегуар Валинье подходит
	{
		sld = characterFromId("FMQM_officer");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload_jail", "none", "", "", "", 10);
		sld = characterFromId("FortFrance_shipyarder");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload_jail", "none", "", "", "", 10);
		LocatorReloadEnterDisable("FortFrance_town", "reload5_back", true); // запираем верфь
		LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_Shipyard")], false);
		// гид
		sld = GetCharacter(NPC_GenerateCharacter("Guide_x", "Guide_1", "man", "man", 10, FRANCE, -1, true, "officer"));
		SetFantomParamFromRank(sld, 10, true);
		RemoveAllCharacterItems(sld, true);
		GiveItem2Character(sld, "blade_12");
		EquipCharacterbyItem(sld, "blade_12");
		sld.name = StringFromKey("FMQ_59");
		sld.lastname = StringFromKey("FMQ_60");
		sld.dialog.FileName = "Quest\LineMiniQuests\FMQ_Martinique.c";
		sld.dialog.currentnode = "greguar";
		sld.greeting = "";
		sld.rank = 25;
		LAi_SetHP(sld, 350, 350);
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto13");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "FMQM_InTavern") // в таверне
	{
		/* if(CheckAttribute(pchar, "IsMushketer"))
		{
			SetMainCharacterToMushketer("", false);
		} */
		FreeSitLocator("Fortfrance_tavern", "sit_base4");
		DoQuestReloadToLocation("Fortfrance_tavern", "sit", "sit_base4", "");			
		sld = characterFromID("Guide_x");
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	else if (sQuestName == "FMQM_OutTavern")
	{
		chrDisableReloadToLocation = false;
		LAI_SetPlayerType(pchar);           
		DoQuestReloadToLocation("Fortfrance_tavern", "tables", "stay4", "");
		sld = CharacterFromID("Guide_x");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		AddQuestRecord("FMQ_Martinique", "10");
		InterfaceStates.Buttons.Save.enable = true;
		pchar.quest.FMQM_ShipyardOpen.win_condition.l1 = "Timer";
		pchar.quest.FMQM_ShipyardOpen.win_condition.l1.date.hour  = 6.0;
		pchar.quest.FMQM_ShipyardOpen.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
		pchar.quest.FMQM_ShipyardOpen.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
		pchar.quest.FMQM_ShipyardOpen.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
		pchar.quest.FMQM_ShipyardOpen.function = "FMQM_ShipyardOpen";
		LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
		LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
		LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
		WaitDate("",0,0,0,2,5);
		RecalculateJumpTable();
		InterfaceStates.Buttons.Save.enable = true;
	}
	else if (sQuestName == "FMQM_HurryToSea") // торопимся в море
	{
		chrDisableReloadToLocation = false;
		sld = CharacterFromID("Guide_x");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload4_back", "none", "", "", "", 10.0);
		AddQuestRecord("FMQ_Martinique", "13");
		LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
		LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
		LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
		pchar.quest.FMQM_hurry.win_condition.l1 = "location";
		pchar.quest.FMQM_hurry.win_condition.l1.location = "Guadeloupe";
		pchar.quest.FMQM_hurry.function = "FMQM_ArriveGuadeloupe";
		AddMapQuestMarkIsland("Guadeloupe", true);
		if(bImCasual)
		{
			NewGameTip(StringFromKey("FMQ_68"));
			SetFunctionTimerCondition("FMQM_HurryLate", 0, 0, 10, false);
		}
		else SetFunctionTimerCondition("FMQM_HurryLate", 0, 0, 5, false);
		pchar.worldmapencountersoff = "1"; // отключить энкаунтеры
	}
	else if (sQuestName == "FMQM_ShoreAfterFight") // прибили контру
	{
		LAi_group_Delete("EnemyFight");
		LAi_SetFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], true);//запретить драться
		DoQuestCheckDelay("FMQM_ShoreSetOfficer", 8.0);
	}
	else if (sQuestName == "FMQM_ShoreSetOfficer") // явился француз
	{
		pchar.questTemp.FMQ.Attack = true;// Addon 2016-1 Jason пиратская линейка
		iRank = MOD_SKILL_ENEMY_RATE+6;
		iScl = 25 + 2*sti(pchar.rank);
		string sModel, sModel_m, sPistol, sGroup, sLocator;
		if (MOD_SKILL_ENEMY_RATE < 7)
		{
			sModel = "citiz_2";
			sModel_m = "mush_ctz_"+(rand(2)+1);
			sPistol = "pistol6";
		}
		else
		{
			sModel = "citiz_5";
			sModel_m = "mush_ctz_"+(rand(2)+10);
			sPistol = "pistol4";
		}
		LAi_Fade("", "");
		AddQuestRecord("FMQ_Martinique", "18");
		sld = characterFromId("FMQM_officer");
		LAi_SetActorType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.dialog.currentnode = "officer_7";
		ChangeCharacterAddressGroup(sld, "Shore28", "reload", "sea");
		AddLandQuestMark(sld, "questmarkmain");
		for (i=1; i<=5; i++)
		{
			if (i > 3)
			{
				sld = GetCharacter(NPC_GenerateCharacter("FMQM_mercenary_"+i, sModel_m, "man", "mushketer", iRank, PIRATE, 0, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
				sld.MusketerDistance = 0;
				sGroup = "goto";
				sLocator = "goto"+(i+7);
				SetCharacterPerk(sld, "Gunman");
				SetCharacterPerk(sld, "GunProfessional");
				if (MOD_SKILL_ENEMY_RATE > 6) sld.cirassId = Items_FindItemIdx("cirass1");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("FMQM_mercenary_"+i, sModel+i, "man", "man", iRank, PIRATE, 0, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_04","blade_06","blade_10"), sPistol, "bullet", iScl*2);
				sGroup = "officers";
				sLocator = "sea_"+i;
				SetCharacterPerk(sld, "GunProfessional");
				EquipCharacterbyItem(sld, sPistol);
				if (MOD_SKILL_ENEMY_RATE > 6) sld.cirassId = Items_FindItemIdx("cirass2");
			}
			ChangeCharacterAddressGroup(sld, "Shore28", "reload", "sea");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, sGroup, sLocator, "", 7);
		}
	}
	else if (sQuestName == "FMQM_AfterBattleExit") // прибили кодлу француза
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		AddQuestRecord("FMQ_Martinique", "20");
		pchar.quest.FMQM_seabattle.win_condition.l1 = "location";
		pchar.quest.FMQM_seabattle.win_condition.l1.location = "Guadeloupe";
		pchar.quest.FMQM_seabattle.function = "FMQM_SeaBattleTartane";
	}
	
	// ФМК-Сент-Кристофер
	else if (sQuestName == "FMQN_HollandBattleRun") // ставим голландский отряд за городом
	{
		iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
		iScl = 30 + 2*sti(pchar.rank);
		sld = GetCharacter(NPC_GenerateCharacter("FMQN_holland_0", "off_hol_5", "man", "man", iRank+5, HOLLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank+7, iScl+7, iScl+7, "blade_15", "pistol5", "bullet", iScl*3+50);
		sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Nevis.c";
		sld.Dialog.currentnode = "hol_officer";
		sld.name = StringFromKey("FMQ_70");
		sld.lastname = StringFromKey("FMQ_71");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetImmortal(sld, true);
		LAi_SetCheckMinHP(sld, 10, true, "");
		ChangeCharacterAddressGroup(sld, "Marigo_ExitTown", "reload", "reload2_back");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		for (i=1; i<=7; i++)
		{
			if (i > 6)
			{
				sld = GetCharacter(NPC_GenerateCharacter("FMQN_holland_"+i, "mush_hol_4", "man", "mushketer", iRank, HOLLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*3);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("FMQN_holland_"+i, "sold_hol_1"+i, "man", "man", iRank, HOLLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_12","blade_09","blade_14"), "pistol1", "bullet", iScl*2);
			}
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetImmortal(sld, true);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Marigo_ExitTown", "reload", "reload2_back");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "goto6", "", 15);
		}
	}
	else if (sQuestName == "FMQN_HollandBattleMarch") // 
	{
		for (i=0; i<=7; i++)
		{
			sld = CharacterFromID("FMQN_holland_"+i);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
		pchar.quest.FMQN_holl_cave.win_condition.l1 = "locator";
		pchar.quest.FMQN_holl_cave.win_condition.l1.location = "Marigo_jungle_01";
		pchar.quest.FMQN_holl_cave.win_condition.l1.locator_group = "reload";
		pchar.quest.FMQN_holl_cave.win_condition.l1.locator = "reload3_back";
		pchar.quest.FMQN_holl_cave.function = "FMQN_HollandBattlePlan";
	}
	else if (sQuestName == "FMQN_HollandBattlePosition") // голландцы - к колодцу
	{
		for (i=0; i<=7; i++)
		{
			sld = CharacterFromID("FMQN_holland_"+i);
			if (i == 6 || i == 7) 
			{
				sld.MusketerDistance = 0;
				LAi_SetStayType(sld);
				LAi_SetActorType(sld);
			}
			else
			{
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "FMQN_HollandBattleToCave", 20.0);
			}
		}
	}
	else if (sQuestName == "FMQN_HollandBattleToCave") // в пещеру
	{
		LocatorReloadEnterDisable("Marigo_jungle_01", "reload3_back", false);
		sld = CharacterFromID("FMQN_seafox_1");
		sld.Dialog.currentnode = "seafox_20";
		LAi_CharacterEnableDialog(sld);
		sld.talker = 9;
	}
	else if (sQuestName == "FMQN_HollandBattleFight") // бой в пещере - начало
	{
		bDisableCharacterMenu = true;
		pchar.GenQuest.FrameLockEsc = true;
		LAi_LocationFightDisable(&Locations[FindLocation("Marigo_Cave")], false);
		chrDisableReloadToLocation = true;
		LAi_group_Delete("EnemyFight");
		for (i=1; i<=5; i++)
		{
			sld = CharacterFromID("FMQN_seafox_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "FMQN_HollandBattleAfterFight");
		LAi_SetFightMode(pchar, true);
		DoQuestCheckDelay("FMQN_HollandBattleFightAdd", 30.0);
	}
	else if (sQuestName == "FMQN_HollandBattleFightAdd") // голландцы спешат на помощь
	{
		bDisableCharacterMenu = false;
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		for (i=0; i<=7; i++)
		{
			sld = CharacterFromID("FMQN_holland_"+i);
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			if (i == 6 || i == 7) ChangeCharacterAddressGroup(sld, "Marigo_Cave", "reload", "reload1");
			else Log_TestInfo(i+"-й солдат ждёт");
		}
		DoQuestFunctionDelay("FMQN_HollandBattleAdding", 1.5);
		iTotalTemp = 0;
	}
	else if (sQuestName == "FMQN_HollandBattleAdding2") // китайская рекурсия
	{
		sld = CharacterFromID("FMQN_holland_"+iTotalTemp);
		ChangeCharacterAddressGroup(sld, "Marigo_Cave", "reload", "reload2");
		iTotalTemp++;
		if (iTotalTemp > 5) 
		{
		}
		else 
		{
			DoQuestFunctionDelay("FMQN_HollandBattleAdding", 10.0);
		}
	}
	else if (sQuestName == "FMQN_HollandBattleAfterFight") // после боя
	{
		LAi_group_Delete("EnemyFight");
		sld = CharacterFromID("FMQN_holland_0");
		sld.Dialog.currentnode = "hol_officer_5";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "FMQN_HollandBattleRest") // в город возвращаемся
	{
		chrDisableReloadToLocation = false;
		sld = CharacterFromID("FMQN_holland_0");
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		for (i=0; i<=7; i++)
		{
			if (GetCharacterIndex("FMQN_holland_"+i) != -1)
			{
				sld = CharacterFromID("FMQN_holland_"+i);
				sld.lifeday = 0; // Addon 2016-1 Jason пиратская линейка
			}
		}
		pchar.quest.FMQN_hol_complete.win_condition.l1 = "Timer";
		pchar.quest.FMQN_hol_complete.win_condition.l1.date.hour  = 6.0;
		pchar.quest.FMQN_hol_complete.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQN_hol_complete.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQN_hol_complete.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQN_hol_complete.function = "FMQN_HollandBattleGovernor";
		LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false);
		LocatorReloadEnterDisable("Marigo_ExitTown", "reload2_back", false);
		LocatorReloadEnterDisable("Marigo_jungle_01", "reload1_back", false);
		LocatorReloadEnterDisable("Marigo_jungle_01", "reload2_back", false);
		AddQuestRecord("FMQ_Nevis", "16");
	}
	else if (sQuestName == "FMQN_GetRumoursDay") // узнали днём
	{
		AddQuestRecord("FMQ_Nevis", "7");
	}
	else if (sQuestName == "FMQN_GetRumoursNight") // узнали ночью
	{
		DoQuestCheckDelay("sleep_in_tavern", 1.0);
		TavernWaitDate("wait_day");
		AddQuestRecord("FMQ_Nevis", "7");
	}
	else if (sQuestName == "FMQN_EnglandSnake") // скрытное проникновение
	{
		SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
		chrDisableReloadToLocation = true;
		pchar.GenQuest.CannotWait = true;
		for (i=1; i<=5; i++)
		{
			sld = CharacterFromID("FMQN_seafox_"+i);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Marigo_Town", "reload", "gate_back");
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		pchar.quest.FMQN_fail3.win_condition.l1 = "Timer";
		pchar.quest.FMQN_fail3.win_condition.l1.date.hour  = 4.0;
		pchar.quest.FMQN_fail3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQN_fail3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQN_fail3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQN_fail3.function = "FMQN_EnglandBattleFail"; // 4 часа на ходьбу к тюрьме и назад
		pchar.quest.FMQN_jail.win_condition.l1 = "locator";
		pchar.quest.FMQN_jail.win_condition.l1.location = "Marigo_town";
		pchar.quest.FMQN_jail.win_condition.l1.locator_group = "reload";
		pchar.quest.FMQN_jail.win_condition.l1.locator = "reload_jail";
		pchar.quest.FMQN_jail.function = "FMQN_EnglandJail";
		pchar.quest.FMQN_Alarm.win_condition.l1 = "Alarm";
		pchar.quest.FMQN_Alarm.win_condition.l1.value = 0;
		pchar.quest.FMQN_Alarm.win_condition.l1.operation = ">";
		pchar.quest.FMQN_Alarm.function = "FMQN_EnglandBattleFail";
		pchar.questTemp.FMQN = "way_eng_6";
	}
	else if (sQuestName == "FMQN_EnglandInJail") // зашли в тюрьму
	{
		SetNationRelation2MainCharacter(HOLLAND, RELATION_NEUTRAL);
		DoQuestCheckDelay("FMQN_EnglandOutJail", 45.0);
	}
	else if (sQuestName == "FMQN_EnglandJailTurn") // поворот ГГ
	{
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload_jail");
	}
	else if (sQuestName == "FMQN_EnglandOutJail") // вышли из тюрьмы
	{
		LAi_SetPlayerType(pchar);
		for (i=1; i<=5; i++)
		{
			sld = CharacterFromID("FMQN_seafox_"+i);
			LAi_SetActorType(sld);
			if (i == 1) 
			{
				sld.dialog.currentnode = "seafox_33";
				LAi_ActorDialogDelay(sld, pchar, "", 2.0);
			}
			ChangeCharacterAddressGroup(sld, "Marigo_Town", "reload", "reload_jail");
		}
		for (i=5; i<=6; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQN_prisoner_"+i, "off_eng_"+i, "man", "man", 30, ENGLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 30, true);
			RemoveAllCharacterItems(sld, true);
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_Town", "reload", "reload_jail");
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		pchar.questTemp.FMQN = "way_eng_7";
	}
	else if (sQuestName == "FMQN_EnglandRunToJungle") // уходим в джунгли
	{
		SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
		for (i=1; i<=5; i++)
		{
			sld = CharacterFromID("FMQN_seafox_"+i);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		pchar.quest.FMQN_jail1.win_condition.l1 = "locator";
		pchar.quest.FMQN_jail1.win_condition.l1.location = "Marigo_town";
		pchar.quest.FMQN_jail1.win_condition.l1.locator_group = "reload";
		pchar.quest.FMQN_jail1.win_condition.l1.locator = "gate_back";
		pchar.quest.FMQN_jail1.function = "FMQN_EnglandReloadJungle";
	}
	else if (sQuestName == "FMQN_EnglandEscape") // за воротами
	{
		pchar.quest.FMQN_fail3.over = "yes";
		pchar.quest.FMQN_Alarm.over = "yes";
		SetNationRelation2MainCharacter(HOLLAND, RELATION_NEUTRAL);
		for (i=1; i<=5; i++)
		{
			sld = CharacterFromID("FMQN_seafox_"+i);
			ChangeCharacterAddressGroup(sld, "Marigo_exitTown", "goto", "goto6");
			if (i == 1)
			{
				LAi_CharacterEnableDialog(sld);
				sld.dialog.currentnode = "seafox_34";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		for (i=5; i<=6; i++)
		{
			sld = CharacterFromID("FMQN_prisoner_"+i);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Marigo_exitTown", "rld", "loc0");
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
		pchar.questTemp.FMQN = "way_eng_8";
	}
	else if (sQuestName == "FMQN_EnglandRunToShore") // идем к бухте
	{
		for (i=1; i<=5; i++)
		{
			sld = CharacterFromID("FMQN_seafox_"+i);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", true);
		LocatorReloadEnterDisable("Marigo_ExitTown", "reload2_back", true);
		LocatorReloadEnterDisable("Marigo_jungle_01", "reload1_back", true);
		LocatorReloadEnterDisable("Marigo_jungle_01", "reload3_back", true);
		LocatorReloadEnterDisable("Marigo_jungle_02", "reload1_back", true);
		LocatorReloadEnterDisable("Marigo_jungle_02", "reload3_back", true);
		LocatorReloadEnterDisable("Marigo_jungle_02", "reloadW_back", true);
		pchar.quest.FMQN_ShoreAttack.win_condition.l1 = "location";
		pchar.quest.FMQN_ShoreAttack.win_condition.l1.location = "shore40";
		pchar.quest.FMQN_ShoreAttack.function = "FMQN_EnglandInShoreAttack";
		AddQuestRecord("FMQ_Nevis", "25");
		Group_DeleteGroup("FMQN_shipgroup"); // удаляем Зеепард
	}
	else if (sQuestName == "FMQN_AfterShoreAttack") // после боя в бухте
	{
		AddQuestRecord("FMQ_Nevis", "26");
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("shore40", "reload1_back", true);
		for (i=5; i<=6; i++)
		{
			sld = CharacterFromID("FMQN_prisoner_"+i);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
		}
		sld = CharacterFromID("FMQN_seafox_1");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			pchar.questTemp.FMQN = "caspar_alive";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
		}
		else pchar.questTemp.FMQN = "caspar_dead";
		for (i=2; i<=5; i++)
		{
			sld = CharacterFromID("FMQN_seafox_"+i);
			sld.lifeday = 0;
		}
		pchar.quest.FMQN_sea_attack.win_condition.l1 = "location";
		pchar.quest.FMQN_sea_attack.win_condition.l1.location = "SentMartin";
		pchar.quest.FMQN_sea_attack.function = "FMQN_EnglandSeaAttack";
	}
	
	// --> ФМК-Тортуга
	
	else if (sQuestName == "FMQT_PirateInTavern") // пирата с ключом - в таверну
	{
		chrDisableReloadToLocation = false;
		iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
		iScl = 15 + 2*sti(pchar.rank);// Addon 2016-1 Jason пиратская линейка
		sld = GetCharacter(NPC_GenerateCharacter("FMQT_pirate", "quest_pirat_2", "man", "man", iRank, FRANCE, 1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
		sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Tortuga.c";
		sld.Dialog.currentnode = "pirate";
		sld.name = StringFromKey("FMQ_72");
		sld.lastname = StringFromKey("FMQ_73");
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		AddMoneyToCharacter(sld, 5000);
		GiveItem2Character(sld, "totem_03");
		GiveItem2Character(sld, "potionwine");
		FreeSitLocator("Tortuga_tavern", "sit_front2");
		FreeSitLocator("Tortuga_tavern", "sit_base2");
		ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit_front2");
		LAi_SetSitType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		DoQuestCheckDelay("FMQT_freeSit", 1.0);
	}
	else if (sQuestName == "FMQT_freeSit")
	{
		FreeSitLocator("Tortuga_tavern", "sit_base2");
	}
	else if (sQuestName == "FMQT_MercenTalk") // 
	{
		DoQuestCheckDelay("hide_weapon", 1.0);
		sld = CharacterFromID("Duran");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "FMQT_MercenHire") // 
	{
		chrDisableReloadToLocation = false;
		sld = CharacterFromID("Duran");
		LAi_SetImmortal(sld, false);
		sld.quest.OfficerPrice = sti(pchar.rank)*2000;
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
		sld.loyality = 30;
		sld.Dialog.Filename = "Enc_Officer_dialog.c";
		sld.cirassId = Items_FindItemIdx("cirass8");
		DeleteAttribute(sld, "MultiFighter");
		DeleteAttribute(sld, "MultiShooter");
		LandEnc_OfficerHired();
		sld.greeting = "Duran_officer";
		FMQT_WifeFinalTalk();
		
		//Событие Клода "Последний рыцарь"
		SetTimerCondition("SKD_DuranTavern", 0, 6, 0, false);
	}
	else if (sQuestName == "FMQT_MercenDie") // 
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		AddQuestRecord("FMQ_Tortuga", "19");
		FMQT_WifeFinalTalk();
	}
	else if (sQuestName == "FMQT_MercenDieInRoom") // 
	{
		LAi_group_Delete("EnemyFight");
		sld = CharacterFromID("FMQT_wife");
		sld.Dialog.currentnode = "wife_22";
		ChangeCharacterAddressGroup(sld, "Tortuga_townhallBedroom", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		DeleteAttribute(pchar, "questTemp.FMQT.Roomfight");
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	}
	else if (sQuestName == "FMQT_FinalFail") // 
	{
		sld = CharacterFromID("FMQT_wife");
		LAi_CharacterDisableDialog(sld);
		sld.lifeday = 0;
		pchar.questTemp.FMQT = "fail";
		AddQuestRecord("FMQ_Tortuga", "23");
		CloseQuestHeader("FMQ_Tortuga");
	}
	
	// --> ФМК-Порт Пренс
	
	else if (sQuestName == "FMQP_InRoom") // ставим дворянчика и двух балбесов
	{
		iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank)-2;// Addon 2016-1 Jason пиратская линейка
		iScl = 20 + 2*sti(pchar.rank);
		LAi_group_Delete("EnemyFight");
		sld = GetCharacter(NPC_GenerateCharacter("FMQP_noble", "Spain_Major", "man", "man", 15, SPAIN, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 15, 50, 50, "blade_16", "pistol5", "bullet", 120); // may-16
		sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_PortPax.c";
		sld.Dialog.currentnode = "noble";
		sld.name = StringFromKey("FMQ_74");
		sld.lastname = StringFromKey("FMQ_75");
		sld.rank = 15;
		LAi_SetHP(sld, 200, 200);
		SetSelfSkill(sld, 90, 50, 30, 90, 50);
		SetShipSkill(sld, 60, 5, 5, 5, 5, 5, 5, 5, 50);
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "Gunman");
		GiveItem2Character(sld, "cirass7");
		EquipCharacterbyItem(sld, "cirass7");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, "Portpax_tavern_upstairs", "reload", "reload_window");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		for (i=1; i<=2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQP_marginal_"+i, "citiz_4"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_05","blade_07"), "pistol1", "bullet", iScl*2);
			ChangeCharacterAddressGroup(sld, "Portpax_tavern_upstairs", "goto", "goto"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "FMQP_AfterFightInRoom");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "FMQP_AfterFightInRoom") // 
	{
		LAi_group_Delete("EnemyFight");
		LAi_SetFightMode(pchar, false);
		chr = CharacterFromID("FMQP_noble");
		sld = GetCharacter(NPC_GenerateCharacter("FMQP_off", "off_fra_1", "man", "man", 15, FRANCE, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 15, 40, 40, "blade_13", "pistol1", "bullet", 120);
		sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_PortPax.c";
		if (LAi_GetCharacterHP(chr) > 0) sld.Dialog.currentnode = "officer";
		else sld.Dialog.currentnode = "officer_5";
		ChangeCharacterAddressGroup(sld, "Portpax_tavern_upstairs", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "FMQP_AfterFightInTown") // 
	{
		sld = CharacterFromID("FMQP_noble");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		LAi_SetImmortal(sld, true);
		chrDisableReloadToLocation = false;
		sld = CharacterFromID("PortPax_waitress");
		LAi_SetWaitressType(sld);
		ChangeCharacterAddressGroup(sld, "Portpax_tavern", "waitress", "barmen");
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		pchar.questTemp.FMQP = "guest";
		AddQuestRecord("FMQ_Portpax", "1");
		pchar.quest.FMQP_sdm.win_condition.l1 = "location";
		pchar.quest.FMQP_sdm.win_condition.l1.location = "SantoDomingo_town";
		pchar.quest.FMQP_sdm.function = "FMQP_InSantoDomingo";
		if(bImCasual)
		{
			NewGameTip(StringFromKey("FMQ_69"));
		}
		else SetFunctionTimerCondition("FMQP_SantoDomingoOver", 0, 0, 3, false);
	}
	else if (sQuestName == "FMQP_SantoDomingoAfterFight") // 
	{
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("FMQ_Portpax", "3");
		pchar.quest.FMQP_letter.win_condition.l1 = "item";
		pchar.quest.FMQP_letter.win_condition.l1.item = "letter_parol";
		pchar.quest.FMQP_letter.function = "FMQP_FindLetter";
	}
	else if (sQuestName == "FMQP_InSantoDomingoTavern") // 
	{
		/* if(CheckAttribute(pchar, "IsMushketer"))
		{
			SetMainCharacterToMushketer("", false);
		} */
		FreeSitLocator("Santodomingo_tavern", "sit_front3");
		FreeSitLocator("Santodomingo_tavern", "sit_base3");
		sld = CharacterFromID("FMQP_noble");
		sld.Dialog.currentnode = "noble_12";
		ChangeCharacterAddressGroup(sld, "Santodomingo_tavern", "sit", "sit_front2");
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "FMQP_OnBoard") // 
	{
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("FMQP_noble");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		AddPassenger(pchar, sld, false);//добавить пассажира
		SetCharacterRemovable(sld, false);
		SetFunctionTimerCondition("FMQP_PortobelloTimeOver", 0, 0, 20, false); 
		pchar.questTemp.FMQP = "sail";
		AddQuestRecord("FMQ_Portpax", "5");
		SetFunctionTimerCondition("FMQP_SetRaiders", 0, 0, 3, false);
		pchar.quest.FMQP_plantation.win_condition.l1 = "location";
		pchar.quest.FMQP_plantation.win_condition.l1.location = "PortoBello_Plantation";
		pchar.quest.FMQP_plantation.function = "FMQP_OnPlantation";
		rloc = &Locations[FindLocation("PortoBello_Plantation")];
		DeleteAttribute(rloc, "soldiers");
	}
	else if (sQuestName == "FMQP_UncleExit") // 
	{
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
		LAi_LocationFightDisable(&Locations[FindLocation("PortoBello_Plantation")], false);
		LocatorReloadEnterDisable("Portobello_exittown", "reload2_back", true);
		sld = CharacterFromID("FMQP_noble");
		sld.lifeday = 0;
		sld = CharacterFromID("FMQP_Uncle");
		sld.lifeday = 0;
		for (i=1; i<=4; i++)
		{
			sld = CharacterFromID("FMQP_guard_"+i);
			sld.lifeday = 0;
		}
		pchar.questTemp.FMQP = "end";
		FMQ_Count();
		AddQuestRecord("FMQ_Portpax", "9");
		CloseQuestHeader("FMQ_Portpax");
		SetFunctionTimerCondition("FMQP_OpenPlantation", 0, 0, 10, false); 
		rloc = &Locations[FindLocation("PortoBello_Plantation")];
		rloc.soldiers = true;
	}
	else if (sQuestName == "FMQP_UncleFight") // 
	{
		LAi_LocationFightDisable(&Locations[FindLocation("PortoBello_Plantation")], false);
		sld = CharacterFromID("FMQP_noble");
		LAi_SetImmortal(sld, false);
		if(bImCasual) sld.ReducedDamage = 0.3; // belamour LE
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_group_Delete("EnemyFight");
		sld = CharacterFromID("FMQP_Uncle");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		for (i=1; i<=4; i++)
		{
			sld = CharacterFromID("FMQP_guard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "FMQP_UncleAfterFight");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "FMQP_UncleAfterFight") // 
	{
		LAi_group_Delete("EnemyFight");
		sld = CharacterFromID("FMQP_noble");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			sld.Dialog.currentnode = "noble_36";
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.greeting = "";
		}
		else
		{
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "10");
			CloseQuestHeader("FMQ_Portpax");
			rloc = &Locations[FindLocation("PortoBello_Plantation")];
			rloc.soldiers = true;
		}
	}
	else if (sQuestName == "FMQP_SDMFail") // 
	{
		sld = CharacterFromID("FMQP_noble");
		sld.lifeday = 0;
		pchar.questTemp.FMQP = "fail";
		AddQuestRecord("FMQ_Portpax", "14");
		CloseQuestHeader("FMQ_Portpax");
	}
	
	// --> ФМК-Последний урок
	else if (sQuestName == "FMQL_FirstBattleEnd") // перебили 1 партию индеев
	{
		sld = CharacterFromID("Guide_y"); // Addon 2016-1 Jason пиратская линейка
		if (LAi_GetCharacterHP(sld) <= 0)
		{
			FMQL_FailInShore();
		}
		else
		{
			sld.dialog.currentnode = "greguar_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	else if (sQuestName == "FMQL_SecondBattleEnd") // перебили 2 партию индеев
	{
		InterfaceStates.Buttons.Save.enable = true; // Addon 2016-1 Jason пиратская линейка
		sld = CharacterFromID("Guide_y");
		if (LAi_GetCharacterHP(sld) <= 0)
		{
			FMQL_FailInShore();
		}
		else
		{
			sld.dialog.currentnode = "greguar_4";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	else if (sQuestName == "FMQL_JungleExit") // 
	{
		if(CheckAttribute(pchar,"questTemp.BlackMark.IronsBlock")) DeleteAttribute(pchar,"questTemp.BlackMark.IronsBlock");
		FMQL_ClearAllCharacters();
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("shore18", "boat", false);
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		if (pchar.questTemp.FMQL == "shore") AddQuestRecord("FMQ_Lesson", "3");
		else 
		{
			if (pchar.questTemp.FMQL == "poor") AddQuestRecord("FMQ_Lesson", "6");
			else AddQuestRecord("FMQ_Lesson", "2");
		}
		CloseQuestHeader("FMQ_Lesson");
		pchar.questTemp.FMQL = "fail";
	}
	else if (sQuestName == "FMQL_AfterCaribAttack") // после боя в джунглях
	{
		LAi_group_Delete("EnemyFight");
		sld = CharacterFromID("Guide_y");
		if (LAi_GetCharacterHP(sld) <= 0) // гид дал дуба
		{
			DoQuestCheckDelay("FMQL_JungleExit", 0.5);
		}
		else
		{
			// считаем выживших вояк
			iTotalTemp = 0;
			for (i=1; i<=10; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
				{
					sld = CharacterFromID("FMQL_sailor_"+i);
					if (LAi_GetCharacterHP(sld) > 0) iTotalTemp++;
				}
			}
			sld = CharacterFromID("Guide_y");
			if (iTotalTemp < 3)
			{
				sld.dialog.currentnode = "greguar_11"; // проиграли
				pchar.questTemp.FMQL = "poor";
			}
			else sld.dialog.currentnode = "greguar_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	else if (sQuestName == "FMQL_RunToGrabbing") // бегут типа в деревню
	{
		sld = CharacterFromID("Guide_y");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "quest", "quest1", "none", "", "", "", 5.0);
		if (GetCharacterIndex("FMQL_Prosper") != -1)
		{
			sld = CharacterFromID("FMQL_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "quest", "quest1", "none", "", "", "", 5.0);
		}
		if (GetCharacterIndex("FMQL_mercen") != -1)
		{
			sld = CharacterFromID("FMQL_mercen");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "quest", "quest1", "none", "", "", "", 5.0);
		}
		for (i=1; i<=10; i++)
		{
			if (GetCharacterIndex("FMQL_sailor_"+i) != -1)
			{
				sld = CharacterFromID("FMQL_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest1", "none", "", "", "", 7.0);
			}
		}
		pchar.quest.FMQL_goto_grabbing.win_condition.l1 = "locator";
		pchar.quest.FMQL_goto_grabbing.win_condition.l1.location = "Common_jungle_01";
		pchar.quest.FMQL_goto_grabbing.win_condition.l1.locator_group = "quest";
		pchar.quest.FMQL_goto_grabbing.win_condition.l1.locator = "quest1";
		pchar.quest.FMQL_goto_grabbing.win_condition = "FMQL_Grabbing";
	}
	else if (sQuestName == "FMQL_Grabbing") // 
	{
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam(StringFromKey("FMQ_76", NewStr()), "FMQL_GrabbingFinish", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 5, 10); // крутим время
		RecalculateJumpTable();
	}
	else if (sQuestName == "FMQL_GrabbingFinish") // 
	{
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		DoQuestReloadToLocation("shore18", "reload", "reload1", "FMQL_BattleAgainstNations");
		// укладываем товары
		int iSanl, iSilk, iRope, iOil;
		iSanl = iTotalTemp * (4 + hrand(MOD_SKILL_ENEMY_RATE)); // Addon 2016-1 Jason пиратская линейка
		iSilk = iTotalTemp * (5 + hrand(MOD_SKILL_ENEMY_RATE));
		iRope = iTotalTemp * (6 + hrand(MOD_SKILL_ENEMY_RATE));
		iOil = iTotalTemp * (7  + hrand(MOD_SKILL_ENEMY_RATE));
		sld = CharacterFromID("Guide_y");
		sld.ShipHideImmortal = 500; // непотопляемый корабль // правки прогона 3
		SetCharacterGoods(sld, GOOD_SANDAL, GetCargoGoods(sld, GOOD_SANDAL) + iSanl);
		pchar.questTemp.FMQL.Sanl = iSanl;
		SetCharacterGoods(sld, GOOD_SHIPSILK, GetCargoGoods(sld, GOOD_SHIPSILK) + iSilk);
		pchar.questTemp.FMQL.Silk = iSilk;
		SetCharacterGoods(sld, GOOD_ROPES, GetCargoGoods(sld, GOOD_ROPES) + iRope);
		pchar.questTemp.FMQL.Rope = iRope;
		SetCharacterGoods(sld, GOOD_OIL, GetCargoGoods(sld, GOOD_OIL) + iOil);
		pchar.questTemp.FMQL.Oil = iOil;
		pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	}
	else if (sQuestName == "FMQL_BattleAgainstNations") // между англами и голландцами
	{
		iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 2; // Addon 2016-1 Jason пиратская линейка
		iScl = 30 + 2 * sti(pchar.rank);
		// наши
		sld = CharacterFromID("Guide_y");
		ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto1");
		LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		if (GetCharacterIndex("FMQL_Prosper") != -1)
		{
			sld = CharacterFromID("FMQL_Prosper");
			ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		if (GetCharacterIndex("FMQL_mercen") != -1)
		{
			sld = CharacterFromID("FMQL_mercen");
			ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		for (i = 1; i <= 10; i++)
		{
			if (GetCharacterIndex("FMQL_sailor_" + i) != -1)
			{
				sld = CharacterFromID("FMQL_sailor_" + i);
				ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto3");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
		// англы
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_england_6", "off_eng_1", "man", "man", iRank + 3, ENGLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank + 3, iScl + 5, iScl + 5, "blade_13", "pistol1", "bullet", iScl * 2);
		ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto8");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "TmpEnemy");
		for (i = 1; i <= 5; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQL_england_" + i, "sold_eng_" + i, "man", "man", iRank, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08", "blade_12", "blade_14"), "pistol1", "bullet", iScl * 2);
			ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto8");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "TmpEnemy");
		}
		// голландцы
		sld = GetCharacter(NPC_GenerateCharacter("FMQL_holland_6", "off_hol_1", "man", "man", iRank + 3, ENGLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank + 3, iScl + 5, iScl + 5, "blade_10", "pistol1", "bullet", iScl * 2);
		ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto7");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		for (i = 1; i <= 5; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FMQL_holland_" + i, "sold_hol_" + i, "man", "man", iRank, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_09", "blade_11", "blade_14"), "pistol1", "bullet", iScl * 2);
			ChangeCharacterAddressGroup(sld, "shore18", "goto", "goto7");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
		LAi_group_SetRelation("TmpEnemy", "EnemyFight", LAI_GROUP_ENEMY);
		LAi_group_FightGroups("TmpEnemy", "EnemyFight", true);
		LAi_group_SetCheck("TmpEnemy", "FMQL_EngDestroy");
		LAi_group_SetCheck("EnemyFight", "FMQL_HolDestroy");
		if (CheckAttribute(pchar, "questTemp.BlackMark.IronsBlock")) DeleteAttribute(pchar, "questTemp.BlackMark.IronsBlock");
	}
	else if (sQuestName == "FMQL_EngDestroy") // 
	{
		pchar.questTemp.FMQL.EngDestroy = "true";
		if (CheckAttribute(pchar, "questTemp.FMQL.HolDestroy")) DoQuestCheckDelay("FMQL_CoastClear", 1.0);
	}
	else if (sQuestName == "FMQL_HolDestroy") // 
	{
		pchar.questTemp.FMQL.HolDestroy = "true";
		if (CheckAttribute(pchar, "questTemp.FMQL.EngDestroy")) DoQuestCheckDelay("FMQL_CoastClear", 1.0);
	}
	else if (sQuestName == "FMQL_CoastClear") // всех перебили
	{
		// --> mitrokosta чистим своих
		for (i = 1; i <= 10; i++)
		{
			if (GetCharacterIndex("FMQL_sailor_" + i) != -1)
			{
				sld = CharacterFromID("FMQL_sailor_" + i);
				sld.lifeday = 0;
			}
		}
		// <--
		LAi_group_Delete("EnemyFight");
		LAi_group_Delete("TmpEnemy");
		chrDisableReloadToLocation = false;
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		LocatorReloadEnterDisable("shore18", "boat", false);
		sld = CharacterFromID("Guide_y");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; // всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		pchar.quest.FMQL_shipfail_1.win_condition.l1 = "NPC_Death"; // прерывание на потопление 
		pchar.quest.FMQL_shipfail_1.win_condition.l1.character = "Guide_y";
		pchar.quest.FMQL_shipfail_1.function = "FMQL_ShipFailReturn";
		if (GetCharacterIndex("FMQL_Prosper") != -1)
		{
			sld = CharacterFromID("FMQL_Prosper");
			AddPassenger(pchar, sld, false); // добавить пассажира
			SetCharacterRemovable(sld, false);
		}
		for (i = 1; i <= 2; i++)
		{
			sld = CharacterFromID("FMQL_EngCap_" + i);
			sld.AlwaysEnemy = true;
		}
		Group_SetTaskAttack("FMQL_Enggroup", PLAYER_GROUP);
		Group_LockTask("FMQL_Enggroup");
		for (i = 1; i <= 2; i++)
		{
			sld = CharacterFromID("FMQL_HolCap_" + i);
			sld.AlwaysEnemy = true;
		}
		Group_SetTaskAttack("FMQL_Holgroup", PLAYER_GROUP);
		Group_LockTask("FMQL_Holgroup");
		AddQuestRecord("FMQ_Lesson", "5");
		AddQuestUserData("FMQ_Lesson", "sSanl", FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl)));
		AddQuestUserData("FMQ_Lesson", "sSilk", FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk)));
		AddQuestUserData("FMQ_Lesson", "sRope", FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope)));
		AddQuestUserData("FMQ_Lesson", "sOil", FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil)));
		pchar.quest.FMQL_return.win_condition.l1 = "location";
		pchar.quest.FMQL_return.win_condition.l1.location = "Fortfrance_town";
		pchar.quest.FMQL_return.function = "FMQL_ReturnMartinique";
		AddMapQuestMarkCity("FortFrance", true);
		SetFunctionTimerCondition("FMQL_ReturnTimeOver", 0, 0, 10, false);
		AddComplexSelfExpToScill(60, 60, 60, 60);
		AddCharacterExpToSkill(pchar, "Leadership", 200); // Addon 2016-1 Jason пиратская линейка
		AddCharacterExpToSkill(pchar, "Fortune", 150);
	}
	else if (sQuestName == "FMQL_LookOnGuards") // смотрим на гарда
	{
		LAi_SetActorType(pchar);
		LAi_ActorTurnToCharacter(pchar, characterFromID("FMQL_guard_1"));
		DoQuestCheckDelay("FMQL_LookOnJohnny", 2.0);
	}
	else if (sQuestName == "FMQL_LookOnJohnny") // смотрим на Джонни
	{
		LAi_SetActorType(pchar);
		LAi_ActorTurnToCharacter(pchar, characterFromID("FMQL_Johnny"));
		DoQuestCheckDelay("FMQL_JohnnyFire", 2.0);
	}
	else if (sQuestName == "FMQL_JohnnyFire") // Джонни стреляет в контру
	{
		sld = CharacterFromID("FMQL_Johnny");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "shot", "FMQL_KillSmugglers", 1.0);
		LAi_SetPlayerType(pchar);
	}
	else if (sQuestName == "FMQL_KillSmugglers") // прибили контриков
	{
		sld = CharacterFromID("FMQL_contra_2");
		LaunchBlastGrenade(sld);
		for (i = 1; i <= 3; i++)
		{
			sld = CharacterFromID("FMQL_contra_" + i);
			LAi_KillCharacter(sld);
		}
		sld = CharacterFromID("Guide_y");
		sld.dialog.currentnode = "greguar_20";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 2.0);
	}
	else if (sQuestName == "FMQL_PeaceFinal") // разошлись миром
	{
		sld = CharacterFromID("Guide_y");
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 10.0);
		sld = CharacterFromID("FMQL_Johnny");
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 10.0);
		for (i = 1; i <= 2; i++)
		{
			sld = CharacterFromID("FMQL_guard_" + i);
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 10.0);
		}
		i = makeint(iTotalTemp / 4);
		AddMoneyToCharacter(pchar, i);
		DoQuestCheckDelay("FMQL_ClearBeach", 11.0);
	}
	else if (sQuestName == "FMQL_ClearBeach") // чистка квеста
	{
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], false);
		LAi_LocationDisableOfficersGen("Shore38", false);
		locations[FindLocation("Shore38")].DisableEncounters = false; // may-16
		RemoveGeometryFromLocation("Shore38", "smg"); // mitrokosta фикс опечатки
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		AddQuestRecord("FMQ_Lesson", "8");
		CloseQuestHeader("FMQ_Lesson");
		pchar.questTemp.FMQL = "end";
		Achievment_Set("ach_51");
		AddCharacterExpToSkill(pchar, "Leadership", 100);
		AddCharacterExpToSkill(pchar, "Fortune", 300);
	}
	else if (sQuestName == "FMQL_BattleOnBeach") // решили повоевать
	{
		DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		InterfaceStates.Buttons.Save.enable = false; // запретить сохраняться
		LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], false);
		LAi_group_Delete("EnemyFight");
		sld = CharacterFromID("Guide_y");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		sld = CharacterFromID("FMQL_Johnny");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "rld", "loc8", "FMQL_JohnnyPosition", -1);
		for (i = 1; i <= 2; i++)
		{
			sld = CharacterFromID("FMQL_guard_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "FMQL_AfterBattleOnBeach");
		LAi_SetFightMode(pchar, true);
		if (GetCharacterIndex("FMQL_Prosper") != -1 && GetCharacterIndex("Duran") != -1) 
		{
			// belamour legendary edition 
			if (MOD_SKILL_ENEMY_RATE < 9) DoQuestCheckDelay("FMQL_BattleOnBeachHelp", 40.0);
			else DoQuestCheckDelay("FMQL_BattleOnBeachHelp", 120.0); // may-16
			pchar.GenQuest.FrameLockEsc = true;
			pchar.questTemp.FMQL.Cpy = "true";
		}
	}
	else if (sQuestName == "FMQL_JohnnyPosition") // 
	{
		sld = CharacterFromID("FMQL_Johnny");
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		DoQuestCheckDelay("FMQL_JohnnyChangePosition", 15.0); // may-16
	}
	else if (sQuestName == "FMQL_JohnnyChangePosition") // may-16
	{
		if (pchar.questTemp.FMQL == "end") return true; // патч 17/1
		sld = CharacterFromID("FMQL_Johnny");
		sld.MusketerDistance = 20;
		DoQuestCheckDelay("FMQL_JohnnyChangePosition1", 3.0);
	}
	else if (sQuestName == "FMQL_JohnnyChangePosition1") // may-16
	{
		sld = CharacterFromID("FMQL_Johnny");
		sld.MusketerDistance = 0;
		DoQuestCheckDelay("FMQL_JohnnyChangePosition", 25.0);
	}
	else if (sQuestName == "FMQL_BattleOnBeachHelp") // прибежали Проспер и пиратус
	{
		sld = CharacterFromID("FMQL_Prosper");
		sld.Dialog.currentnode = "prosper_11";
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Shore38", "reload", "reload1");
		LAi_ActorRunToLocator(sld, "goto", "goto8", "FMQL_BattleOnBeachMushketer", -1);
		pchar.quest.FMQL_prosper_dead.win_condition.l1 = "NPC_Death"; // прерывание на смерть 
		pchar.quest.FMQL_prosper_dead.win_condition.l1.character = "FMQL_Prosper";
		pchar.quest.FMQL_prosper_dead.win_condition = "FMQL_ProsperDead";
		if (CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
		{
			sld = CharacterFromID("Duran");
			ChangeCharacterAddressGroup(sld, "Shore38", "reload", "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			/*pchar.quest.FMQL_pirate_dead.win_condition.l1 = "NPC_Death";
			pchar.quest.FMQL_pirate_dead.win_condition.l1.character = "Duran";
			pchar.quest.FMQL_pirate_dead.win_condition = "FMQL_PirateDead";*/
		}
	}
	else if (sQuestName == "FMQL_ProsperDead") // 
	{
		sld = CharacterFromID("FMQL_Prosper");
		LAi_KillCharacter(sld);
		Log_TestInfo("Проспер убит");
		pchar.questTemp.FMQL.ProsperDead = "true";
	}
	else if (sQuestName == "FMQL_BattleOnBeachMushketer") // 
	{
		sld = CharacterFromID("FMQL_Prosper");
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	else if (sQuestName == "FMQL_AfterBattleOnBeach") // закончили бой с кодлой Валинье
	{
		InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
		RemoveGeometryFromLocation("Shore38", "smg");
		LAi_group_Delete("EnemyFight");
		SetCharacterGoods(pchar, GOOD_SANDAL, GetCargoGoods(sld, GOOD_SANDAL) + sti(pchar.questTemp.FMQL.Sanl));
		SetCharacterGoods(pchar, GOOD_SHIPSILK, GetCargoGoods(sld, GOOD_SHIPSILK) + sti(pchar.questTemp.FMQL.Silk));
		SetCharacterGoods(pchar, GOOD_ROPES, GetCargoGoods(sld, GOOD_ROPES) + sti(pchar.questTemp.FMQL.Rope));
		SetCharacterGoods(pchar, GOOD_OIL, GetCargoGoods(sld, GOOD_OIL) + sti(pchar.questTemp.FMQL.Oil));
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		LAi_LocationDisableOfficersGen("Shore38", false);
		locations[FindLocation("Shore38")].DisableEncounters = false;
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		if (CheckAttribute(pchar, "questTemp.FMQL.Cpy"))
		{
			DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
			DeleteAttribute(pchar, "questTemp.FMQL.Cpy");
			if (CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				if (!CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) // пират жив
				{
					sld = CharacterFromID("Duran");
					sld.dialog.FileName = "Quest\LineMiniQuests\FMQ_Lesson.c";
					sld.Dialog.currentnode = "FMQL_beach";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0); 
				}
				else
				{
					if (!CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) // Проспер жив
					{
						sld = CharacterFromID("FMQL_Prosper");
						sld.Dialog.currentnode = "prosper_11";
						sld.MusketerDistance = 20;
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0); 
					}
					else // никого не осталось
					{
						if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
						else
						{
							pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
							pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
							pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
							pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
						}
						chrDisableReloadToLocation = false;
						AddQuestRecord("FMQ_Lesson", "10");
						CloseQuestHeader("FMQ_Lesson");
						pchar.questTemp.FMQL = "end";
					}
				}
			}
		}
		else
		{
			chrDisableReloadToLocation = false;
			AddQuestRecord("FMQ_Lesson", "9");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		}
		Achievment_Set("ach_51");
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 500);
		AddCharacterExpToSkill(pchar, "Fortune", 200);
		ChangeCharacterComplexReputation(pchar, "authority", 7);
	}
	else if (sQuestName == "FMQL_PirateNormal") // 
	{
		sld = CharacterFromID("Duran");
		LAi_SetOfficerType(sld);
		sld.dialog.FileName = "Enc_Officer_dialog.c";
		sld.Dialog.currentnode = "hired";
	}
	else if (sQuestName == "FMQL_CanibBossAmulet") // 
	{
		sld = CharacterFromID("FMQL_canib_chief");
		RemoveAllCharacterItems(sld, true);
		sld.SaveItemsForDead = true; 
		sld.DontClearDead = true;
		GiveItem2Character(sld, "indian_1");
		GiveItem2Character(sld, "indian_7");
		GiveItem2Character(sld, "obereg_5");
		GiveItem2Character(sld, "obereg_6");
		GiveItem2Character(sld, "obereg_3");
		LAi_KillCharacter(sld);
	}
	else
	{
		condition = false;
	}
	
	return condition;
}