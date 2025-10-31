///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason --------------------------------Вождь краснокожих------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RedChieftain_Prepare(string qName)//подготовка инициализации квестодателя
{
	pchar.questTemp.RedChieftain.StartCity = FindFriendCityToMC(true);//город, в котором квестодатель подойдет
	while (pchar.questTemp.RedChieftain.StartCity == "") pchar.questTemp.RedChieftain.StartCity = FindFriendCityToMC(true); // patch-9
	pchar.quest.Red_Chieftain_1.win_condition.l1 = "location";
	pchar.quest.Red_Chieftain_1.win_condition.l1.location = pchar.questTemp.RedChieftain.StartCity+"_town";
	pchar.quest.Red_Chieftain_1.function = "RedChieftain_Begin";
	AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
	log_testinfo("Вождь краснокожих в колонии: "+pchar.questTemp.RedChieftain.StartCity);
}

void RedChieftain_Begin(string qName)//инициализация квестодателя
{
	//DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
	//chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("RedChieftain", "Canib", "man", "man", 20, sti(pchar.nation), -1, false, "native"));
	sld.name = StringFromKey("RedChieftain_1");
	sld.lastname = StringFromKey("RedChieftain_2");
    sld.Dialog.Filename = "Quest\LineMiniQuests\RedChieftain.c";
	sld.dialog.currentnode = "RedChieftain";
    FantomMakeCoolFighter(sld, 20, 50, 50, "blade_01", "", "", 50);
	LAi_SetImmortal(sld, true);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetCitizenType(sld);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.RedChieftain.StartCity+"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	AddLandQuestMark(sld, "questmarkmain");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
}

void RedChieftainDelete(string qName)//не пришли за 30 дней
{
	if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
	{
		DelMapQuestMarkShore("Shore19");	
	}
	if (CheckAttribute(pchar, "questTemp.RedChieftain.Eng"))
	{
		DelMapQuestMarkShore("Shore54");	
	}
	DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
	sld = CharacterFromID("RedChieftain");
	sld.lifeday = 0;
	DeleteAttribute(pchar, "questTemp.RedChieftain");
	ChangeIndianRelation(-1.0);
}

void RedChieftain_CreateShooner(string qName)//создание кораблей и лодок
{
	pchar.quest.RedChieftainOver.over = "yes";//снять таймер
	Group_FindOrCreateGroup("RedChieftain_Shooner");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 5 + 2*sti(pchar.rank);
	int iNation = sti(pchar.questTemp.RedChieftain.AttackNation);
	int iType = SHIP_SCHOONER_W;
	if (MOD_SKILL_ENEMY_RATE < 5) iType = SHIP_SCHOONER;
	for (int i=1; i<=2; i++)
	{
		if (i == 2 && MOD_SKILL_ENEMY_RATE < 9) iType = SHIP_SCHOONER;
		if (i == 2 && MOD_SKILL_ENEMY_RATE < 5 && sti(pchar.rank) < 12) continue;
		sld = GetCharacter(NPC_GenerateCharacter("ShoonerRC_Cap_"+i, "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank, iNation, 0, true, "quest"));
		FantomMakeSmallSailor(sld, iType, "", CANNON_TYPE_CANNON_LBS12, 50, iScl, iScl, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", 50);
		if(MOD_SKILL_ENEMY_RATE < 5) SetCrewQuantity(sld, sti(GetMaxCrewQuantity(sld))/2); // belamour legendary edition
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		Group_AddCharacter("RedChieftain_Shooner", "ShoonerRC_Cap_"+i);
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.AnalizeShips = true;
		sld.DontRansackCaptain = true;
    }
	Group_SetGroupCommander("RedChieftain_Shooner", "ShoonerRC_Cap_1");
	if (pchar.questTemp.RedChieftain.Island == "Cumana") Group_SetAddress("RedChieftain_Shooner", pchar.questTemp.RedChieftain.Island, "ships", "l1");
	else Group_SetAddress("RedChieftain_Shooner", pchar.questTemp.RedChieftain.Island, "quest_ships", "quest_ship_7");
	bool bOk = (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_TARTANE) || (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_WAR_TARTANE) || (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER) || (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER) || (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SLOOP) || (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_PINK);
	if(bOk && GetCompanionQuantity(pchar) < 2)
	{//все гуд - ставим тартаны
		AddQuestRecord("RedChieftain", "3");
		Island_SetReloadEnableGlobal(pchar.questTemp.RedChieftain.Island, false);
		Group_FindOrCreateGroup("RedChieftain_Tartane");
		for (i=1; i<=6; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("TartaneRC_Cap_"+i, "mercen_25", "man", "man", 5, PIRATE, 0, true, "native"));
			sld.name = StringFromKey("RedChieftain_3");
			sld.lastname = StringFromKey("RedChieftain_4");
			FantomMakeSmallSailor(sld, SHIP_TARTANE, "", CANNON_TYPE_NONECANNON, 30, 10, 10, 10, 10);
			SetCrewQuantityOverMax(sld, 12);
			Group_AddCharacter("RedChieftain_Tartane", "TartaneRC_Cap_"+i);
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.AnalizeShips = true;
		}
		Group_SetGroupCommander("RedChieftain_Tartane", "TartaneRC_Cap_1");
		Group_SetTaskAttack("RedChieftain_Shooner", "RedChieftain_Tartane");
		Group_SetTaskRunaway("RedChieftain_Tartane", "RedChieftain_Shooner");
		if (pchar.questTemp.RedChieftain.Island == "Cumana") Group_SetAddress("RedChieftain_Tartane", pchar.questTemp.RedChieftain.Island, "ships", "l1");
		else Group_SetAddress("RedChieftain_Tartane", pchar.questTemp.RedChieftain.Island, "quest_ships", "quest_ship_7");
		Group_LockTask("RedChieftain_Tartane");
		Group_LockTask("RedChieftain_Shooner");
		pchar.quest.Red_Chieftain_AfterBattle.win_condition.l1 = "Group_Death";
		pchar.quest.Red_Chieftain_AfterBattle.win_condition.l1.group = "RedChieftain_Shooner";
		pchar.quest.Red_Chieftain_AfterBattle.function = "RedChieftain_AfterBattle";
		pchar.quest.Red_Chieftain_DieHard.win_condition.l1 = "MapEnter";
		pchar.quest.Red_Chieftain_DieHard.function = "RedChieftain_DieHard";
		pchar.quest.Red_Chieftain_Fail.win_condition.l1 = "Group_Death";
		pchar.quest.Red_Chieftain_Fail.win_condition.l1.group = "RedChieftain_Tartane";
		pchar.quest.Red_Chieftain_Fail.function = "RedChieftain_Fail";
	}
	else
	{
		AddQuestRecord("RedChieftain", "4");
		CloseQuestHeader("RedChieftain");
		Group_SetTaskAttack("RedChieftain_Shooner", PLAYER_GROUP);
		Group_LockTask("RedChieftain_Shooner");
		pchar.quest.Red_Chieftain_end.win_condition.l1 = "Location_Type";
		pchar.quest.Red_Chieftain_end.win_condition.l1.location_type = "town";
		pchar.quest.Red_Chieftain_end.function = "RemoveRedChieftain";
		DeleteAttribute(pchar, "questTemp.RedChieftain");
	}
}

void RedChieftain_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Island_SetReloadEnableGlobal(pchar.questTemp.RedChieftain.Island, true);
	locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = true; //энкаутеры закрыть
	bQuestDisableMapEnter = true;//на карту нельзя
	pchar.quest.Red_Chieftain_Fail.over = "yes";
	pchar.quest.Red_Chieftain_DieHard.over = "yes";
	AddQuestRecord("RedChieftain", "5");
	pchar.quest.Red_Chieftain_3.win_condition.l1 = "location";
	pchar.quest.Red_Chieftain_3.win_condition.l1.location = pchar.questTemp.RedChieftain.Shore;
	pchar.quest.Red_Chieftain_3.function = "RedChieftain_Shore";
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
	AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
	AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
	ChangeOfficersLoyality("good_all", 1);
	ChangeCharacterComplexReputation(pchar, "authority", 3);
	//считаем не потопленные тартаны
	iTemp = 0;
    for (i=1; i<=6; i++)
    {
		sld = characterFromId("TartaneRC_Cap_"+i);
		if (LAi_GetCharacterHP(sld) > 0)
		{
			LAi_SetImmortal(sld, true);//защита от дурака
			iTemp++;
		}
    }
	pchar.questTemp.RedChieftain.Tartane = iTemp;
}

void RedChieftain_DieHard(string qName)//сбежали
{
	Island_SetReloadEnableGlobal(pchar.questTemp.RedChieftain.Island, true);
	pchar.quest.Red_Chieftain_AfterBattle.over = "yes";
	pchar.quest.Red_Chieftain_Fail.over = "yes";
	Group_DeleteGroup("RedChieftain_Shooner");
	Group_DeleteGroup("RedChieftain_Tartane");
	pchar.quest.Red_Chieftain_end.win_condition.l1 = "Location_Type";
	pchar.quest.Red_Chieftain_end.win_condition.l1.location_type = "town";
	pchar.quest.Red_Chieftain_end.function = "RemoveRedChieftain";
	AddQuestRecord("RedChieftain", "6");
	CloseQuestHeader("RedChieftain");
	DeleteAttribute(pchar, "questTemp.RedChieftain");
	ChangeOfficersLoyality("bad_all", 1);
	ChangeIndianRelation(-3.0);
}

void RedChieftain_Fail(string qName)//потеряли все тартаны
{	
	Island_SetReloadEnableGlobal(pchar.questTemp.RedChieftain.Island, true);
	pchar.quest.Red_Chieftain_AfterBattle.over = "yes";
	pchar.quest.Red_Chieftain_DieHard.over = "yes";
	pchar.quest.Red_Chieftain_end.win_condition.l1 = "Location_Type";
	pchar.quest.Red_Chieftain_end.win_condition.l1.location_type = "town";
	pchar.quest.Red_Chieftain_end.function = "RemoveRedChieftain";
	AddQuestRecord("RedChieftain", "7");
	CloseQuestHeader("RedChieftain");
	DeleteAttribute(pchar, "questTemp.RedChieftain");
	ChangeOfficersLoyality("bad_all", 1);
	ChangeIndianRelation(-5.0);
}

void RedChieftainOver(string qName)//просрочили
{
	pchar.quest.Red_Chieftain_2.over = "yes"; //снять прерывание
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		pchar.quest.Red_Chieftain_end.win_condition.l1 = "Location_Type";
		pchar.quest.Red_Chieftain_end.win_condition.l1.location_type = "town";
		pchar.quest.Red_Chieftain_end.function = "RemoveRedChieftain";
	}
	else
	{
		sld = CharacterFromID("RedChieftain");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		log_info(StringFromKey("RedChieftain_5"));
		PlaySound("interface\notebook.wav");
	}
	AddQuestRecord("RedChieftain", "2");
	CloseQuestHeader("RedChieftain");
	DeleteAttribute(pchar, "questTemp.RedChieftain");
	ChangeOfficersLoyality("bad_all", 1);
	ChangeIndianRelation(-2.0);
}

void RemoveRedChieftain(string qName)//удалить вождя
{
	sld = CharacterFromID("RedChieftain");
	RemovePassenger(Pchar, sld);
	sld.lifeday = 0;
	log_info(StringFromKey("RedChieftain_5"));
	PlaySound("interface\notebook.wav");
}

void RedChieftain_Shore(string qName)//высадка на сушу и бой
{
	bQuestDisableMapEnter = false;//на карту можно
	chrDisableReloadToLocation = true;//закрыть локацию
	int iCrew = GetCrewQuantity(pchar);//получим число команды
	int n = makeint(iCrew/10);
	if (n < 1) n = 1;
	pchar.questTemp.RedChieftain.OurCrew = n;//запомним
	int iRank = sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE/2);
	int iScl = 5 + 2*sti(pchar.rank);
	int iNation = sti(pchar.questTemp.RedChieftain.AttackNation);
	//ставим наших бойцов согласно числу команды
	for (i=1; i<=n; i++)
	{
		if (i == 3)
		{
		sld = GetCharacter(NPC_GenerateCharacter("RSOur_crew_"+i, "mush_ctz_5", "man", "mushketer", iRank, sti(pchar.nation), 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2);
		}
		else
		{
		sld = GetCharacter(NPC_GenerateCharacter("RSOur_crew_"+i, "citiz_"+(rand(9)+31), "man", "man", iRank, sti(pchar.nation), 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
		}
		ChangeCharacterAddressGroup(sld, pchar.questTemp.RedChieftain.Shore, "goto", "goto1");
		LAi_SetWarriorType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	//ставим вражеских солдат
	for (i=1; i<=6; i++)
	{
		if (i == 1 || i == 2)
		{
			sld = GetCharacter(NPC_GenerateCharacter("RSEnemy_crew_"+i, "mush_"+NationShortName(iNation)+"_" + i, "man", "mushketer", iRank+2, iNation, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank+2, iScl+5, iScl+5, "", "mushket1", "bullet", iScl*2);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("RSEnemy_crew_"+i, "sold_"+NationShortName(iNation)+"_"+(rand(1)+7), "man", "man", iRank, iNation, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
		}
		ChangeCharacterAddressGroup(sld, pchar.questTemp.RedChieftain.Shore, "reload", "reload1_back");
		LAi_SetWarriorType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	//ставим офицера
	sld = GetCharacter(NPC_GenerateCharacter("RSEnemy_off", "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank+5, iNation, 0, false, "soldier"));
	FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_10", "pistol3", "grapeshot", iScl*2);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.RedChieftain.Shore, "reload", "reload1_back");
	LAi_SetWarriorType(sld);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_group_MoveCharacter(sld, "EnemyFight");
	TakeNItems(sld, "jewelry52", rand(150)+50);
	TakeNItems(sld, "jewelry53", rand(175)+175);
	//стравливаем группы
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "RedChieftain_AfterFight");
	LAi_SetFightMode(pchar, true);
}
// <-- Вождь краснокожих

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool RedChieftain_QuestComplete(string sQuestName, string qname)
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//Jason---------------------------------------Вождь краснокожих-------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld;
	int iTemp, i, n;
    float locx, locy, locz;
	
	bool condition = true;
	
	if (sQuestName == "RedChieftainStay")
	{
		sld = CharacterFromID("RedChieftain");
		LAi_SetStayType(sld);
		sld.dialog.currentnode = "RedChieftain_wait_2";
		AddLandQuestMark(sld, "questmarkmain");
		AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
	}
	else if (sQuestName == "RedChieftain_AfterFight")
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		DoQuestCheckDelay("RedChieftain_EnterIndian", 20.0);//время на сбор жемчуга с трупа
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "RedChieftain_EnterIndian")
	{
		n = sti(pchar.questTemp.RedChieftain.OurCrew);
		//считаем живых солдат
		iTemp = 0;
		for (i=1; i<=n; i++)
		{
			sld = characterFromId("RSOur_crew_"+i);
			if (LAi_GetCharacterHP(sld) > 0) iTemp++;
		}
		if (iTemp != n)//если есть потери - пересчитаем команду на корабле
		{
			iTemp = (n-iTemp)*10;
			SetCrewQuantityOverMax(pchar, sti(PChar.Ship.Crew.Quantity)-iTemp); 
		}
		//ставим индейцев по числу живых тартан
		n = sti(pchar.questTemp.RedChieftain.Tartane);
		ChangeIndianRelation(n+4.0);
		for (i=1; i <=n; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("RC_Indian_"+i, "miskito_"+(rand(5)+1), "man", "man", 5, sti(pchar.nation), 0, true, "quest"));
			sld.name = StringFromKey("RedChieftain_6");
			sld.lastname = StringFromKey("RedChieftain_7");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.RedChieftain.Shore, "goto", "goto1");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
			LAi_SetImmortal(sld, true);
		}
		//ставим вождя
		sld = CharacterFromID("RedChieftain");
		LAi_SetActorType(sld);
		sld.dialog.currentnode = "RedChieftain_pearl";
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.questTemp.RedChieftain.Shore, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "RedChieftain_Pearl")
	{
		i = sti(pchar.questTemp.RedChieftain.Ind);
		if (i <= sti(pchar.questTemp.RedChieftain.Tartane))
		{
			sld = characterFromId("RC_Indian_"+i);    
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\LineMiniQuests\RedChieftain.c";
			sld.dialog.currentnode = "RedChieftain_pearl_give";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			sld = CharacterFromID("RedChieftain");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "RedChieftain_final";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	//<-- Вождь краснокожих конец
	else
	{
		condition = false;
	}
	
	return condition;
}