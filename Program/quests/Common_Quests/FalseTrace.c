////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--> Jason ----------------------------------Ложный след---------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FalseTrace_Prepare(string qName)//подготовка инициализации квестодателя
{
	pchar.questTemp.FalseTrace.StartCity = FindFriendCityToMC(true);//город, в котором квестодатель подойдет
	while (pchar.questTemp.FalseTrace.StartCity == "") pchar.questTemp.FalseTrace.StartCity = FindFriendCityToMC(true); // patch-9
	pchar.quest.False_Trace_1.win_condition.l1 = "location";
	pchar.quest.False_Trace_1.win_condition.l1.location = pchar.questTemp.FalseTrace.StartCity+"_tavern"; // Rebbebion, теперь в таверну
	pchar.quest.False_Trace_1.function = "FalseTrace_Begin";
	log_testinfo("Ложный след в колонии: "+pchar.questTemp.FalseTrace.StartCity);
	AddMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity, false);
	CheckPortugalHWIC(); // для квест марков
}

void CheckPortugalHWIC()
{
	if(SandBoxMode || pchar.questTemp.HWIC.Detector == "holl_win"|| pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
	{
		if(sti(pchar.rank) > 14) 
		{
			AddMapQuestMarkCity("marigo", false);
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		}
		if(!CheckAttribute(pchar, "questTemp.Consumption") && sti(pchar.rank) > 6)
		{
			AddMapQuestMarkCity("PortSpein", false);
			AddLandQuestMark(characterFromId("PortSpein_waitress"), "questmarkmain");
		}
	}
}

void FalseTrace_Begin(string qName)//инициализация квестодателя
{
	if (sti(pchar.rank) < 15)
	{
		DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
		DoQuestFunctionDelay("FalseTrace_Prepare", 2.0);
		return; // may-16
	}
	if(CheckAttribute(pchar,"questTemp.RedChieftain.StartCity") && pchar.questTemp.RedChieftain.StartCity == pchar.questTemp.FalseTrace.StartCity)
	{
		DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
		DoQuestFunctionDelay("FalseTrace_Prepare", 2.0);
		return; // may-16
	}
	sld = GetCharacter(NPC_GenerateCharacter("Mugger", "AdamRainer", "man", "man", 20, sti(pchar.nation), -1, false, "quest"));
	sld.name = StringFromKey("FalseTrace_1");
	sld.lastname = StringFromKey("FalseTrace_2");
    sld.Dialog.Filename = "Quest\LineMiniQuests\FalseTrace.c";
	sld.dialog.currentnode = "FalseTrace";
	sld.greeting = "town_pirate";
    sld.loyality = 25;
	sld.rank 	= 20;
    sld.reputation = 10;
	sld.alignment = "bad";
	LAi_SetHP(sld, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35);
	GiveItem2Character(sld, "blade_04");
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	sld.equip.blade = "blade_04";
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
	sld.cirassId = Items_FindItemIdx("cirass1"); // 280313
    sld.HoldEquip = true; // не отдавать саблю и пистоль
	SetSPECIAL(sld, 7, 4, 8, 4, 3, 10, 8);
	SetSelfSkill(sld, 75, 95, 75, 80, 75);
	SetShipSkill(sld, 50, 10, 8, 9, 12, 11, 15, 12, 90);
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
	sld.HalfImmortal = true;//полубессмертен
	sld.CompanionDisable = true;//не может быть компаньоном
	ChangeCharacterAddressGroup(sld, pchar.questTemp.FalseTrace.StartCity+"_tavern", "sit", LAi_FindNearestFreeLocator("sit", locx, locy, locz));
	LAi_SetSitType(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void FalseTraceGaleonOver(string qName)//просрочили или не нашли
{
	pchar.quest.False_Trace_AfterBattle.over = "yes";
	Group_DeleteGroup("Sea_FalseTrace1");
	if (IsEntity(&worldMap) || bSeaActive) 
	{
	pchar.quest.False_Trace_end.win_condition.l1 = "Location_Type";
	pchar.quest.False_Trace_end.win_condition.l1.location_type = "town";
	pchar.quest.False_Trace_end.function = "RemoveFalseTrace";
	sld = characterFromId("Mugger");
	DeleteAttribute(sld, "HalfImmortal");
	RemovePassenger(Pchar, sld);
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	}
	else
	{
	sld = CharacterFromID("Mugger");
	sld.lifeday = 0;
	sld.dialog.currentnode = "FalseTrace_Remove1";
	RemovePassenger(Pchar, sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	AddQuestRecord("FalseTrace", "2");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	ChangeOfficersLoyality("bad_all", 1);
}

void RemoveFalseTrace(string qName)//удалить Адама
{
	sld = CharacterFromID("Mugger");
	sld.lifeday = 0;
	sld.dialog.currentnode = "FalseTrace_Remove1";
	RemovePassenger(Pchar, sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CreateFalseTraceGaleonOnMap(string qName)//энкаунтер галеона на карте
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 10 + 2*sti(pchar.rank);
    string sGroup = "Sea_FalseTrace1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	// Captain Beltrop, 14.02.2021, правка нации капитана галеона - несовпадение атрибутов
	sld = GetCharacter(NPC_GenerateCharacter("FalseTraceCap", "q_eng_Cap_1", "man", "man", iRank, sti(pchar.questTemp.FalseTrace.Mation), sti(pchar.questTemp.FalseTrace.DayQty), true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_FLEUT, pchar.questTemp.FalseTrace.ShipName, CANNON_TYPE_CANNON_LBS8, 70, iScl, iScl, iScl, iScl);
	UpgradeShipParameter(sld, "Capacity");
	SetCaptanModelByEncType(sld, "war");
	SetRandomNameToCharacter(sld);
	LAi_SetHP(sld, 50+MOD_SKILL_ENEMY_RATE*30, 50+MOD_SKILL_ENEMY_RATE*30);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Coastal_Captain = true; //не ссорить нации
	sld.Ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*10-10;
	sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*10-10;
	sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*10-10;
	sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*10-10;
	if (MOD_SKILL_ENEMY_RATE > 4) TakeNItems(sld, "potion2", 2);
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipSpeedUp");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "quest_ship";
    sld.mapEnc.Name = StringFromKey("FalseTrace_3", pchar.questTemp.FalseTrace.ShipName);
    Group_AddCharacter(sGroup, "FalseTraceCap");
	Group_SetGroupCommander(sGroup, "FalseTraceCap");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader("Cartahena", pchar.questTemp.FalseTrace.TargetShore, "FalseTraceCap", sti(pchar.questTemp.FalseTrace.DayQty));//запуск энкаунтера
	
	pchar.quest.False_Trace_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.False_Trace_AfterBattle.win_condition.l1.group = sGroup;
	pchar.quest.False_Trace_AfterBattle.function = "FalseTrace_AfterBattle";
	
	// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
    pchar.GenQuest.SeaHunter2Pause = true;
    SeaHunter_Delete();
}

void FalseTrace_AfterBattle(string qName)//утопили галеон
{
	pchar.quest.FalseTraceGaleonOver.over = "yes";
	Group_DeleteGroup("Sea_FalseTrace1");
	Log_testInfo("ГАЛЕОН УТОНУЛ!");
	pchar.quest.False_Trace_end.win_condition.l1 = "Location_Type";
	pchar.quest.False_Trace_end.win_condition.l1.location_type = "town";
	pchar.quest.False_Trace_end.function = "RemoveFalseTrace";
	AddQuestRecord("FalseTrace", "3");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	ChangeOfficersLoyality("bad_all", 1);
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void SetCheckForSolly()//на золото Солли
{
	pchar.quest.False_Trace_3.win_condition.l1 = "location";
	pchar.quest.False_Trace_3.win_condition.l1.location = pchar.questTemp.FalseTrace.QuestCity+"_town";
	pchar.quest.False_Trace_3.function = "RemoveFalseTraceBoth";
	pchar.questTemp.FalseTrace.SollyBonanza = "true";
}

void SetCheckForKillAdam()//на тайник Адама
{
	pchar.quest.False_Trace_3.win_condition.l1 = "location";
	pchar.quest.False_Trace_3.win_condition.l1.location = pchar.questTemp.FalseTrace.QuestShore;
	pchar.quest.False_Trace_3.function = "RemoveFalseTraceBoth";
	pchar.questTemp.FalseTrace.KillAdam = "true";
	LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, true);//офицеров не пускать
	locations[FindLocation(pchar.questTemp.FalseTrace.QuestShore)].DisableEncounters = true; //энкаутеры закрыть
}

void SetCheckForGoldShip()//на корабль с золотом
{
	pchar.quest.False_Trace_3.win_condition.l1 = "location";
	pchar.quest.False_Trace_3.win_condition.l1.location = pchar.questTemp.FalseTrace.TargetShore;
	pchar.quest.False_Trace_3.function = "FalseTrace_GoldShip";
	pchar.questTemp.FalseTrace = "CatchAdam";
	locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = true; //энкаутеры закрыть
}

void FalseTraceSollyOver(string qName)//просрочили за наводкой на Солли
{
	pchar.quest.False_Trace_3.over = "yes"; //снять прерывание
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		if (CheckAttribute(pchar, "questTemp.FalseTrace.KillAdam")) 
		{
		AddQuestRecord("FalseTrace", "12");
		AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		sld = CharacterFromID("Mugger");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		sld = CharacterFromID("FalseTraceWife");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		log_info(StringFromKey("FalseTrace_4"));
			PlaySound("interface\notebook.wav");
		}
		else
		{
		pchar.quest.False_Trace_end.win_condition.l1 = "Location_Type";
		pchar.quest.False_Trace_end.win_condition.l1.location_type = "town";
		pchar.quest.False_Trace_end.function = "RemoveFalseTraceBoth";
		AddQuestRecord("FalseTrace", "13");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		}
	}
	else
	{
	AddQuestRecord("FalseTrace", "13");
		AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
	sld = CharacterFromID("Mugger");
	sld.lifeday = 0;
	sld.dialog.currentnode = "FalseTrace_Remove2";
	RemovePassenger(Pchar, sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	ref chr = CharacterFromID("FalseTraceWife");
	chr.lifeday = 0;
	RemovePassenger(Pchar, chr);
	LAi_SetActorType(chr);
	ChangeCharacterAddressGroup(chr, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorFollow(chr, sld, "", -1);
	}
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
}

void RemoveFalseTraceBoth(string qName)//удалить Адама и Катерину+наводка на сокровища Солли+убить Адама
{
	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	sld = CharacterFromID("Mugger");
	LAi_SetImmortal(sld, true);
	sld.lifeday = 0;
	if (CheckAttribute(pchar, "questTemp.FalseTrace.SollyBonanza")) sld.dialog.currentnode = "FalseTrace_23";
	else 
	{
		if (CheckAttribute(pchar, "questTemp.FalseTrace.KillAdam")) sld.dialog.currentnode = "FalseTrace_24";
		else sld.dialog.currentnode = "FalseTrace_Remove2";
	}
	RemovePassenger(Pchar, sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	ref chr = CharacterFromID("FalseTraceWife");
	LAi_SetImmortal(chr, true);
	RemovePassenger(Pchar, chr);
	LAi_SetActorType(chr);
	ChangeCharacterAddressGroup(chr, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorFollow(chr, sld, "", -1);
}

void FalseTraceBonanzaOver(string qName)//опоздали
{
	pchar.quest.False_Trace_4.over = "yes"; //снять прерывание
	AddQuestRecord("FalseTrace", "15");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	ChangeOfficersLoyality("bad_all", 1);
}

void FalseTrace_SollyBonanza(string qName)//высадка на берег за сокровищами
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретим драться
	pchar.quest.FalseTraceBonanzaOver.over = "yes"; //снять прерывание
	//заполним сундук
	pchar.GenQuestBox.Shore55 = true;
	pchar.GenQuestBox.Shore55.box2.items.jewelry5 = 2061;//золото
	pchar.GenQuestBox.Shore55.box2.items.jewelry6 = 889;//серебро
	pchar.GenQuestBox.Shore55.box2.items.jewelry10 = 25;//платина
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2;
	int iScl = 10 + 2*sti(pchar.rank);
	//ставим наших бойцов
	for (i=1; i<=10; i++)
	{
		if (i == 3)
		{
		sld = GetCharacter(NPC_GenerateCharacter("FTOur_crew_"+i, "mush_ctz_5", "man", "mushketer", iRank, sti(pchar.nation), 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
		sld = GetCharacter(NPC_GenerateCharacter("FTOur_crew_"+i, "citiz_"+(i+30), "man", "man", iRank, sti(pchar.nation), 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
		}
		ChangeCharacterAddressGroup(sld, "Shore55", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	//ставим бандитов Солли
	for (i=1; i<=6; i++)
	{
		if (i == 1)
		{
		sld = GetCharacter(NPC_GenerateCharacter("FTEnemy_crew_"+i, "mush_ctz_"+(rand(2)+7), "man", "mushketer", iRank, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
		sld = GetCharacter(NPC_GenerateCharacter("FTEnemy_crew_"+i, "citiz_"+(i+40), "man", "man", iRank, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
		}
		ChangeCharacterAddressGroup(sld, "Shore55", "goto", "goto4");
		LAi_SetActorType(sld);
		sld.Dialog.Filename = "Quest\LineMiniQuests\FalseTrace.c";
		if (i == 2) sld.dialog.currentnode = "FalseTrace_Solly";
		else LAi_CharacterDisableDialog(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
	}
}

void FalseTrace_SollyBonanzaAdd()//ещё выскочили из засады
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2;
	int iScl = 10 + 2*sti(pchar.rank);
	for (i=1; i<=8; i++)
	{
		if (i == 2)
		{
		sld = GetCharacter(NPC_GenerateCharacter("FTAEnemy_crew_"+i, "mush_ctz_"+(rand(2)+7), "man", "mushketer", iRank, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl+5, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
		sld = GetCharacter(NPC_GenerateCharacter("FTAEnemy_crew_"+i, "citiz_"+(i+40), "man", "man", iRank, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
		}
		ChangeCharacterAddressGroup(sld, "Shore55", "goto", "goto2");
		LAi_SetWarriorType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
}

void FalseTrace_SollyShip(string qName)//появился Солли
{
	Island_SetReloadEnableGlobal("SantaCatalina", false);//на остров нельзя
	Group_FindOrCreateGroup("Solly_brig");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 20 + 2*sti(pchar.rank);
	if (sti(pchar.rank < 15)) iTemp = SHIP_BRIG;
	else iTemp = SHIP_CORVETTE;
	sld = GetCharacter(NPC_GenerateCharacter("Solly", "mercen_20", "man", "man", iRank, PIRATE, 0, true, "quest"));
	sld.name = StringFromKey("FalseTrace_5");
	sld.lastname = StringFromKey("FalseTrace_6");
	FantomMakeSmallSailor(sld, iTemp, "", CANNON_TYPE_CULVERINE_LBS18, 100, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, 40, 40, "blade_04", "pistol1", "bullet", 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	Group_AddCharacter("Solly_brig", "Solly");
	sld.AlwaysEnemy = true;
	sld.AnalizeShips = true;
	Group_SetGroupCommander("Solly_brig", "Solly");
	Group_SetAddress("Solly_brig", "SantaCatalina", "quest_ships", "quest_ship_9");
	Group_SetTaskAttack("Solly_brig", PLAYER_GROUP);
	Group_LockTask("Solly_brig");
	pchar.quest.FalseTrace_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.FalseTrace_AfterBattle.win_condition.l1.group = "Solly_brig";
	pchar.quest.FalseTrace_AfterBattle.function = "SollyShip_AfterBattle";
	pchar.quest.FalseTrace_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.FalseTrace_DieHard.function = "SollyShip_DieHard";
}

void SollyShip_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.FalseTrace_DieHard.over = "yes";
	Group_DeleteGroup("Solly_brig");
	Island_SetReloadEnableGlobal("SantaCatalina", true);
	AddQuestRecord("FalseTrace", "17");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	SetFunctionTimerCondition("FalseTrace_DeleteBox", 0, 0, 1, false);
	AddComplexSeaExpToScill(200, 150, 150, 150, 200, 200, 0);
	ChangeOfficersLoyality("good_all", 1);
	if(SandBoxMode)
	{
		//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
		//{
			//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
			//{
				pchar.questTemp.SanBoxTarget.FalseTrace = true;
				ChangeCharacterComplexReputation(pchar, "fame", 25);
			//}
		//}
	}
}

void SollyShip_DieHard(string qName)//сбежали
{
	pchar.GenQuestBox.Shore55 = true;
	pchar.GenQuestBox.Shore55.box1.items.mineral18 = 10;
	pchar.GenQuestBox.Shore55.box2.items.mineral14 = 25;
	pchar.quest.FalseTrace_AfterBattle.over = "yes";
	Group_DeleteGroup("Solly_brig");
	Island_SetReloadEnableGlobal("SantaCatalina", true);
	AddQuestRecord("FalseTrace", "18");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	ChangeOfficersLoyality("bad_all", 1);
	SetFunctionTimerCondition("FalseTrace_DeleteBox", 0, 0, 1, false); // belamour gen через день удалить хлам из сундуков
}

void FalseTrace_DeleteBox(string qName)//в сундуки - хлам
{
	DeleteAttribute(pchar, "GenQuestBox.Shore55"); // belamour gen этот хлам остается навечно
}

void FalseTrace_GoldShip(string qName)//высадили в бухте Катерину, её кэпа и пленного Адама
{
	chrDisableReloadToLocation = true;
	sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
	sld.lifeday = 0;
	LAi_CharacterEnableDialog(sld);//разрешение диалога
	sld.Dialog.Filename = "Quest\LineMiniQuests\FalseTrace.c";
	sld.dialog.currentnode = "FalseTrace_GoldShip";
	sld.greeting = "town_pirate";
	RemovePassenger(Pchar, sld);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	ref chr = CharacterFromID("FalseTraceWife");
	chr.lifeday = 0;
	RemovePassenger(Pchar, chr);
	LAi_SetActorType(chr);
	ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");
	LAi_ActorFollow(chr, sld, "", -1);
	ref ch = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerAdamIDX)];
	ReleasePrisoner(ch); //освободили пленника
	ch.lifeday = 0;
	ChangeCharacterAddressGroup(ch, pchar.location, "goto", "goto2");
	LAi_SetActorType(ch);
	LAi_ActorFollow(ch, sld, "", -1);
}

void CreateFalseTraceGoldShipOnMap(string qName)//создаем корабль с золотом
{
	string sCapId = "FalseTraceGoldCap";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iNation = sti(pchar.questTemp.FalseTrace.ShipNation);
	int iScl = 20 + 2*sti(pchar.rank);
	if (iScl > 90) iScl = 90;
	for (int i = 1; i <= 2; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "citiz_41", "man", "man", 20, iNation, 20, true, "quest"));
		SetRandomNameToCharacter(sld);
		SetRandomNameToShip(sld);
		switch (i)
		{
			case 1: iTemp = SHIP_GALEON_H break;
			case 2: 
				if (sti(pchar.rank < 16)) iTemp = SHIP_CORVETTE;
				else iTemp = SHIP_FRIGATE;
			break;
		}
		sld.Ship.Type = GenerateShipExt(iTemp, 1, sld);
		SetBaseShipData(sld);
		SetCaptanModelByEncType(sld, "war");
		int hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantity(sld, hcrew);
		SetCrewQuantityFull(sld);
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.Coastal_Captain = true; //не ссорить нации
		sld.lifeDay = 15;
		sld.AnalizeShips = true;
		sld.skill.Sailing = iScl+10;
		sld.skill.Defence = iScl;
		sld.skill.Accuracy = iScl;
		sld.skill.Cannons = iScl+rand(10);
		sld.Ship.Crew.Morale = iScl;
		sld.Ship.Crew.Exp.Sailors = iScl;
		sld.Ship.Crew.Exp.Cannoners = iScl;
		sld.Ship.Crew.Exp.Soldiers = iScl;
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "SailsDamageUp");
		SetCharacterPerk(sld, "CrewDamageUp");
		SetCharacterPerk(sld, "CriticalShoot");
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "AdvancedBattleState");
		SetCharacterPerk(sld, "ShipDefenseProfessional");
		SetCharacterPerk(sld, "LongRangeShoot");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "ShipSpeedUp");
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		SetCharacterGoods(sld, GOOD_GRAPES, 700);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 500);
		SetCharacterGoods(sld, GOOD_BOMBS, 1000);
		SetCharacterGoods(sld, GOOD_POWDER, 2500);
		if (i == 1)
		{
			SetCharacterGoods(sld, GOOD_GOLD, 800); //положить в трюм золото
			SetCharacterGoods(sld, hrand(3, "1")+28, 200+hrand(100, "2")); //положить в трюм апгрейд-товар
		}
		sld.mapEnc.type = "war";
		sld.mapEnc.worldMapShip = "quest_ship";
        sld.mapEnc.Name = StringFromKey("FalseTrace_7");
        Group_AddCharacter(sGroup, sCapId + i);
	}
	Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader(pchar.questTemp.FalseTrace.ShipCity, "Shore3", sCapId + "1", 19);//запуск энкаунтера
	SetFunctionTimerCondition("FalseTraceGoldShipOver", 0, 0, 19, false); 
	//на абордаж
	pchar.quest.FalseTrace_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.FalseTrace_Abordage.win_condition.l1.character = "FalseTraceGoldCap1";
	pchar.quest.FalseTrace_Abordage.function = "FalseTraceGoldCap_Abordage";//взяли на абордаж
	//на потопление орудиями
	pchar.quest.FalseTrace_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.FalseTrace_Sink.win_condition.l1.character = "FalseTraceGoldCap1";
	pchar.quest.FalseTrace_Sink.function = "FalseTraceGoldCap_Sink";//потопили
	
	// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
    pchar.GenQuest.SeaHunter2Pause = true;
    SeaHunter_Delete();
}

void FalseTraceGoldCap_Abordage(string qName)//после абордажа
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.FalseTraceGoldShipOver.over = "yes"; //снять таймер
	pchar.quest.FalseTrace_Sink.over = "yes";
	AddQuestRecord("FalseTrace", "22");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	AddComplexSeaExpToScill(150, 150, 150, 200, 150, 150, 0);
	ChangeOfficersLoyality("good_all", 1);
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
	
	if(SandBoxMode)
	{
		//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
		//{
			//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
			//{
				pchar.questTemp.SanBoxTarget.FalseTrace = true;
				ChangeCharacterComplexReputation(pchar, "fame", 25);
			//}
		//}
	}
}

void FalseTraceGoldCap_Sink(string qName)//потопили
{
	pchar.quest.FalseTraceGoldShipOver.over = "yes"; //снять таймер
	pchar.quest.FalseTrace_Abordage.over = "yes";
	AddQuestRecord("FalseTrace", "21");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	AddComplexSeaExpToScill(20, 20, 20, 0, 20, 20, 0);
	ChangeOfficersLoyality("bad_all", 1);
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void FalseTraceGoldShipOver(string qName)//опоздали или не нашли галеон
{
	pchar.quest.FalseTrace_Abordage.over = "yes";
	pchar.quest.FalseTrace_Sink.over = "yes";
	AddQuestRecord("FalseTrace", "20");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	ChangeOfficersLoyality("bad_all", 1);
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void FalseTrace_AdamTreasure(string qName)//на маяке у нычки Адама
{
	//заполним сундук
	pchar.GenQuestBox.Mayak7 = true;
	pchar.GenQuestBox.Mayak7.box1.items.gold_dublon = 1109;//дублоны
	pchar.GenQuestBox.Mayak7.box1.items.icollection = 4;//коллекции
	pchar.GenQuestBox.Mayak7.box1.items.jewelry2 = 55;
	pchar.GenQuestBox.Mayak7.box1.items.jewelry3 = 28;
	pchar.GenQuestBox.Mayak7.box1.items.jewelry4 = 11;
	pchar.GenQuestBox.Mayak7.box1.items.jewelry40 = 20;
	pchar.GenQuestBox.Mayak7.box1.items.jewelry41 = 15;
	pchar.GenQuestBox.Mayak7.box1.items.jewelry42 = 21;
	pchar.GenQuestBox.Mayak7.box1.items.jewelry44 = 26;
	pchar.GenQuestBox.Mayak7.box1.items.jewelry47 = 19;
	pchar.GenQuestBox.Mayak7.box1.items.jewelry49 = 24;
	pchar.GenQuestBox.Mayak7.box1.items.jewelry51 = 13;
	//поставим прерывание на вход в локатор
	pchar.quest.False_Trace_8.win_condition.l1 = "locator";
	pchar.quest.False_Trace_8.win_condition.l1.location = "Mayak7";
	pchar.quest.False_Trace_8.win_condition.l1.locator_group = "box";
	pchar.quest.False_Trace_8.win_condition.l1.locator = "box1";
	pchar.quest.False_Trace_8.function = "FalseTrace_PrepereCreateBandits";
}

void FalseTrace_PrepereCreateBandits(string qName)//установим прерывание на выход
{
	chrDisableReloadToLocation = true;
	pchar.quest.False_Trace_9.win_condition.l1 = "locator";
	pchar.quest.False_Trace_9.win_condition.l1.location = "Mayak7";
	pchar.quest.False_Trace_9.win_condition.l1.locator_group = "reload";
	pchar.quest.False_Trace_9.win_condition.l1.locator = "boat";
	pchar.quest.False_Trace_9.function = "FalseTrace_CreateBandits";
}

void FalseTrace_CreateBandits(string qName)//установим бандитов
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретим драться
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2;
	int iScl = 10 + 2*sti(pchar.rank);
	if (sti(pchar.rank) < 16) sTemp = "pistol1";
	else sTemp = "pistol6";
	for (i=1; i<=4; i++)
	{
		if (i == 1)
		{
		sld = GetCharacter(NPC_GenerateCharacter("Adam_bandit_"+i, "mercen_24", "man", "man", iRank+3, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank+3, iScl+5, iScl+5, "blade_04", "pistol4", "bullet", iScl*2);
		}
		else
		{
		sld = GetCharacter(NPC_GenerateCharacter("Adam_bandit_"+i, "citiz_"+(i+40), "man", "man", iRank, PIRATE, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", sTemp, "bullet", iScl*2);
		}
		ChangeCharacterAddressGroup(sld, "Mayak7", "goto", "goto1");
		LAi_SetActorType(sld);
		sld.Dialog.Filename = "Quest\LineMiniQuests\FalseTrace.c";
		if (i == 1) sld.dialog.currentnode = "FalseTrace_Bandits";
		else LAi_CharacterDisableDialog(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
	}
	//установим Катерину
	sld = characterFromId("FalseTraceWife");
	ChangeCharacterAddressGroup(sld, "Mayak7", "goto", "goto3");
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
}

void FalseTrace_BanditsShip(string qName)//бандитский корабль
{
	Island_SetReloadEnableGlobal("Hispaniola2", false);//на остров нельзя
	Group_FindOrCreateGroup("Band_brig");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 10 + 2*sti(pchar.rank);
	iTemp = SHIP_CARAVEL;
	sld = GetCharacter(NPC_GenerateCharacter("BandCap", "mercen_2", "man", "man", iRank, FRANCE, 0, true, "quest"));
	FantomMakeSmallSailor(sld,iTemp, "", CANNON_TYPE_CANNON_LBS16, 70, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, 40, 40, "blade_04", "pistol1", "bullet", 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	Group_AddCharacter("Band_brig", "BandCap");
	sld.AlwaysEnemy = true;
	sld.AnalizeShips = true;
	sld.Coastal_Captain = true;
	sld.Ship.Mode = "pirate";
	Group_SetGroupCommander("Band_brig", "BandCap");
	Group_SetAddress("Band_brig", "Hispaniola2", "ships", "l2");
	Group_SetTaskAttack("Band_brig", PLAYER_GROUP);
	Group_LockTask("Band_brig");
	pchar.quest.FalseTrace_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.FalseTrace_AfterBattle.win_condition.l1.group = "Band_brig";
	pchar.quest.FalseTrace_AfterBattle.function = "BandShip_AfterBattle";
	pchar.quest.FalseTrace_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.FalseTrace_DieHard.function = "BandShip_DieHard";
}

void BandShip_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.FalseTrace_DieHard.over = "yes";
	Group_DeleteGroup("Band_brig");
	Island_SetReloadEnableGlobal("Hispaniola2", true);
	AddQuestRecord("FalseTrace", "26");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
	ChangeOfficersLoyality("good_all", 1);
	if(SandBoxMode)
	{
		//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
		//{
			//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
			//{
				pchar.questTemp.SanBoxTarget.FalseTrace = true;
				ChangeCharacterComplexReputation(pchar, "fame", 25);
			//}
		//}
	}
}

void BandShip_DieHard(string qName)//сбежали
{
	pchar.GenQuestBox.Mayak7 = true;
	pchar.GenQuestBox.Mayak7.box1.items.mineral18 = 25;
	pchar.quest.FalseTrace_AfterBattle.over = "yes";
	Group_DeleteGroup("Band_brig");
	Island_SetReloadEnableGlobal("Hispaniola2", true);
	AddQuestRecord("FalseTrace", "27");
	CloseQuestHeader("FalseTrace");
	DeleteAttribute(pchar, "questTemp.FalseTrace");
	ChangeOfficersLoyality("bad_all", 1);
}
//<-- Ложный след

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool FalseTrace_QuestComplete(string sQuestName, string qname)
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason--------------------------------------------------Ложный след----------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld, chr, rShip;
	int  iShipType;
    float locx, locy, locz;
	string sTemp;
	
	bool condition = true;
	
	if (sQuestName == "FalseTrace_AfterFight")
	{
		sld = GetCharacter(NPC_GenerateCharacter("FalseTraceWife", "CatRainer", "woman", "towngirl", 2, sti(pchar.questTemp.FalseTrace.Mation), -1, true, "quest"));
		sld.name = StringFromKey("FalseTrace_8");
		sld.lastname = StringFromKey("FalseTrace_9");
		sld.Dialog.Filename = "Quest\LineMiniQuests\FalseTrace.c";
		if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) 
			sld.dialog.currentnode = "FalseTrace_wife_4";
		else 
			sld.dialog.currentnode = "FalseTrace_wife";
		
		RemoveAllCharacterItems(sld, true);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddComplexSeaExpToScill(150, 130, 130, 170, 150, 150, 0);
		pchar.GenQuest.DontSetCabinOfficer = true; // не пускать офицеров в каюту ГГ
	}
	else if (sQuestName == "SetFalseTraceCharToCabin")
	{
		iShipType = GetCharacterShipType(pchar);
		rShip = GetRealShip(iShipType);
		sTemp = "My_" + rShip.CabinType;
		sld = characterFromId(pchar.questTemp.FalseTrace.CharID);
		ChangeCharacterAddressGroup(sld, sTemp, "reload", "reload1");
		LAi_SetStayType(sld);
	}
	else if (sQuestName == "FalseTraceWife_Remove")
	{
		sld = characterFromId("FalseTraceWife");
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
	}
	else if (sQuestName == "FalseTrace_capture")
	{
		sld = characterFromId("Mugger");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Afraid", "FalseTrace_afraid", 6.0);
	}
	else if (sQuestName == "FalseTrace_afraid")
	{
		LAi_SetActorType(pchar);
		sld = characterFromID("Mugger");        
		LAi_SetActorType(sld);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		LAi_ActorTurnToCharacter(sld, pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	}
	else if (sQuestName == "FalseTrace_SollyAfterFight")
	{
		chrDisableReloadToLocation = false;
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("FalseTrace", "16");
		pchar.quest.False_Trace_5.win_condition.l1 = "location";
		pchar.quest.False_Trace_5.win_condition.l1.location = "SantaCatalina";
		pchar.quest.False_Trace_5.function = "FalseTrace_SollyShip";
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "FalseTraceDouble_Remove")
	{
		sld = characterFromId("FalseTraceWife");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		chr = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerAdamIDX)];
		ChangeCharacterAddressGroup(chr, "none", "", "");
		chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "FalseTrace_AdamDead")
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("FalseTraceWife");
		sld.dialog.currentnode = "FalseTrace_wife_25";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		locations[FindLocation(pchar.questTemp.FalseTrace.QuestShore)].DisableEncounters = false; //энкаутеры открыть
	}
	else if (sQuestName == "FalseTrace_BanditsAfterFight")
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("FalseTraceWife");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "FalseTrace_wife_31";
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		pchar.quest.False_Trace_10.win_condition.l1 = "location";
		pchar.quest.False_Trace_10.win_condition.l1.location = "Hispaniola2";
		pchar.quest.False_Trace_10.function = "FalseTrace_BanditsShip";
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "FalseTrace_CaterinaKilled")
	{
		sld = characterFromID("FalseTraceWife"); 
		LAi_KillCharacter(sld);
		LAi_SetPlayerType(pchar);
		chrDisableReloadToLocation = false;
		LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
		locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
		AddQuestRecord("FalseTrace", "24");
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		OfficersReaction("bad");
		Achievment_SetStat(95, 1);
	}
	//<-- Ложный след конец
	else
	{
		condition = false;
	}
	
	return condition;
}