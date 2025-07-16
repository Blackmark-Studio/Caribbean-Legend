///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason----------------------------------------Работорговец------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void Slavetrader_GetRandomShore()//выбор бухты
{	
	switch (rand(3))
	{
		case 0:
			pchar.questTemp.Slavetrader.Island = "Terks";
			break;
		case 1:
			pchar.questTemp.Slavetrader.Island = "Caiman";
			break;
		case 2:
			pchar.questTemp.Slavetrader.Island = "Dominica";
			break;
		case 3:
			pchar.questTemp.Slavetrader.Island = "Bermudes";
			break;
	}
	pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
	while(pchar.questTemp.Slavetrader.Island.Shore == "")
	{
		pchar.questTemp.Slavetrader.Island = GetRandIslandId();
		pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
		if (!isLocationFreeForQuests(pchar.questTemp.Slavetrader.Island)) pchar.questTemp.Slavetrader.Island.Shore = "";
	} 
}

void Slavetrader_SlaveShipsOver(string qName)//просроченный таймер
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Slavetrader_SlaveShipsOver.over"))
			DeleteAttribute(pchar,"quest.Slavetrader_SlaveShipsOver.over");
		NewGameTip(StringFromKey("Slavetrader_1"));
		SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);
		return;
	}
	pchar.quest.Slavetrader_ShipsAttack.over = "yes";
	AddQuestRecord("Slavetrader", "7");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_2"),StringFromKey("Slavetrader_3")));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "goaway";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_ShoreShipsOver(string qName)//просроченный таймер пинаса
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Slavetrader_ShoreShipsOver.over"))
			DeleteAttribute(pchar,"quest.Slavetrader_ShoreShipsOver.over");
		NewGameTip(StringFromKey("Slavetrader_1"));
		SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);
		return;
	}
	pchar.quest.Slavetrader_ShoreAttack.over = "yes";
	AddQuestRecord("Slavetrader", "7_1");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_2"),StringFromKey("Slavetrader_3")));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "goaway_pinas";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_CreateSlaveShips(string qName)//создание кораблей в бухте
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	ref sld;
	string Blade, sTemp;
			
	sTemp = pchar.questTemp.Slavetrader.ShipName;
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, false);
    Group_FindOrCreateGroup("Slave_Attack");
	Group_SetType("Slave_Attack", "war");
	for (i=1; i<=2; i++)
	{
		Rank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
		if(makeint(pchar.rank) >= 20) { iShipRank = 4; }
		if(makeint(pchar.rank) >= 13 && makeint(pchar.rank) < 20) { iShipRank = rand(1)+2; }	
		if(makeint(pchar.rank) >= 7 && makeint(pchar.rank) < 13) { iShipRank = rand(1); }	
		if(makeint(pchar.rank) < 7) { iShipRank = 0; }
		switch (iShipRank)
		{
			case 0:  
				ShipType = SHIP_SLOOP;     					
				Rank = 12 + rand(5);
                Blade = "blade_11";
				iCannonType = CANNON_TYPE_CANNON_LBS12;
			break; 		
			case 1:  
				ShipType = SHIP_SHNYAVA;			
				Rank = 15 + rand(5);
                Blade = "blade_12";
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 
			case 2: 
				ShipType = SHIP_CORVETTE; 				
				Rank = 20 + rand(5);
                Blade = "blade_13";
				iCannonType = CANNON_TYPE_CANNON_LBS20;
			break; 
			case 3: 
				ShipType = SHIP_FRIGATE;         			
				Rank = 25 + rand(5);
                Blade = "blade_15";
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break; 
			case 4: 
				ShipType = SHIP_GALEON_H; 						
				Rank = 30 + rand(5);
                Blade = "blade_20";
				iCannonType = CANNON_TYPE_CANNON_LBS36;
			break;  				
		}
		sld = GetCharacter(NPC_GenerateCharacter("CaptainSlaveAttack_"+i, "mercen_"+(rand(14)+14), "man", "man", Rank, PIRATE, 3, true, "quest"));//создание кэпа
		if (i == 1)
		{
			FantomMakeCoolSailor(sld, ShipType, "", iCannonType, 70, 50, 50);
			FantomMakeCoolFighter(sld, Rank, 40, 40, Blade, "pistol1", "bullet", 30);
		}
		if (i == 2)
		{
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, sTemp, CANNON_TYPE_CANNON_LBS16, 70, 50, 50);
			FantomMakeCoolFighter(sld, Rank, 40, 40, "blade_13", "pistol1", "bullet", 30);
		}
		
		Group_AddCharacter("Slave_Attack", "CaptainSlaveAttack_"+i);
		sld.SuperShooter  = true;
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterGoods(sld, GOOD_SLAVES, 700 + rand(100));//положить в трюм рабов
		
		sld.ship.Crew.Morale = 50;
		ChangeCrewExp(sld, "Sailors", 40);
		ChangeCrewExp(sld, "Cannoners", 40);
		ChangeCrewExp(sld, "Soldiers", 30);
    }
	Group_SetGroupCommander("Slave_Attack", "CaptainSlaveAttack_1");
	Group_SetTaskAttack("Slave_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Slave_Attack", PLAYER_GROUP);
	Group_SetAddress("Slave_Attack", pchar.questTemp.Slavetrader.Island, "", "");
	Group_LockTask("Slave_Attack");
			
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Slave_Attack";
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_SlaveAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_SlaveAttack_DieHard";//это слинял
	
	AddQuestRecord("Slavetrader", "3_1");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_2"),StringFromKey("Slavetrader_3")));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
}

void Slavetrader_SlaveAttack_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Slave_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	pchar.quest.Slavetrader_SlaveShipsOver.over = "yes";
	AddQuestRecord("Slavetrader", "4");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "died";
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
}

void Slavetrader_SlaveAttack_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Slave_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	pchar.quest.Slavetrader_SlaveShipsOver.over = "yes";
	AddQuestRecord("Slavetrader", "5");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "goaway";
	ChangeOfficersLoyality("bad_all",1);
}

void Slavetrader_CreateShoreShips(string qName)//создание пинаса в бухте
{
	int hcrew, iNation;
	ref sld;
	string sTemp;
	
	iNation = sti(pchar.questTemp.Slavetrader.Nation);
	sTemp = pchar.questTemp.Slavetrader.ShipName;
	pchar.questTemp.Slavetrader = "TakeShoreCap";
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, false);
    Group_FindOrCreateGroup("Shore_Attack");
	Group_SetType("Shore_Attack", "war");
	sld = GetCharacter(NPC_GenerateCharacter("Slaveshorecap", "trader_"+(rand(13)+1), "man", "man", 25, iNation, 3, true, "quest"));
	sld.DontRansackCaptain = true; 
	FantomMakeCoolSailor(sld, SHIP_PINNACE, sTemp, CANNON_TYPE_CANNON_LBS16, 100, 70, 70);
	sld.Ship.Mode = "trade";
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_21", "pistol5", "bullet", 250);
	Group_AddCharacter("Shore_Attack", "Slaveshorecap");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "MusketsShoot");
	hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, 1.5*hcrew);
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 70);
	ChangeCrewExp(sld, "Cannoners", 70);
	ChangeCrewExp(sld, "Soldiers", 100);
    
	Group_SetGroupCommander("Shore_Attack", "Slaveshorecap");
	Group_SetTaskAttack("Shore_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Shore_Attack", PLAYER_GROUP);
	Group_SetAddress("Shore_Attack", pchar.questTemp.Slavetrader.Island, "", "");
	Group_LockTask("Shore_Attack");
			
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Shore_Attack";
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_ShoreAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_ShoreAttack_DieHard";//это слинял
	pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
}

void Slavetrader_ShoreAttack_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Shore_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	AddQuestRecord("Slavetrader", "11");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_4"),StringFromKey("Slavetrader_5")));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "End_quest";
	CloseQuestHeader("Slavetrader");
	ChangeOfficersLoyality("bad_all",1);
}

void Slavetrader_ShoreAttack_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
	{
		Group_DeleteGroup("Shore_Attack");
		Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
	    pchar.quest.Slavetrader_DieHard.over = "yes";
		AddQuestRecord("Slavetrader", "12");
		AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
		CloseQuestHeader("Slavetrader");
		pchar.questTemp.Slavetrader = "End_quest";
	}
	else
	{
		characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "Slaveshorecap"; //полная победа, если захватил
		AddComplexSeaExpToScill(100, 100, 100, 200, 100, 100, 0);
	}
}

void Slavetrader_BrigOver(string qName)//реакция на просроченный таймер
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Slavetrader_BrigOver.over"))
			DeleteAttribute(pchar,"quest.Slavetrader_BrigOver.over");
		NewGameTip(StringFromKey("Slavetrader_1"));
		SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);
		return;
	}
	pchar.questTemp.Slavetrader_BrigAttack.over = "yes";//ликвидация бригантины
	AddQuestRecord("Slavetrader", "15");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_4"),StringFromKey("Slavetrader_5")));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
	CloseQuestHeader("Slavetrader");
	ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 50);
	pchar.questTemp.Slavetrader = "goodbye";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_CreateBrig(string qName)//создание бригантины
{
	int iNation = sti(pchar.questTemp.Slavetrader.Nation);
	ref sld;
	string sTemp;
			
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetraderbrig.Island, false);
    Group_FindOrCreateGroup("Brig_Attack");
	Group_SetType("Brig_Attack", "war");
	sTemp = pchar.questTemp.Slavetraderbrig.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("CapBrigAttack", "off_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", 35, iNation, 3, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, sTemp, CANNON_TYPE_CANNON_LBS12, 100, 70, 70);
	FantomMakeCoolFighter(sld, 35, 90, 90, "blade_16", "pistol3", "grapeshot", 100);
	Group_AddCharacter("Brig_Attack", "CapBrigAttack");
	sld.AlwaysEnemy = true;
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	sld.ship.Crew.Morale = 80;
	ChangeCrewExp(sld, "Sailors", 80);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
 
	Group_SetGroupCommander("Brig_Attack", "CapBrigAttack");
	Group_SetTaskAttack("Brig_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Brig_Attack", PLAYER_GROUP);
	Group_SetAddress("Brig_Attack", pchar.questTemp.Slavetraderbrig.Island, "", "");
	Group_LockTask("Brig_Attack");
			
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Brig_Attack";
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_BrigAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_BrigAttack_DieHard";//это слинял
}

void Slavetrader_BrigAttack_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Brig_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Slavetraderbrig.Island, true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	pchar.quest.Slavetrader_BrigOver.over = "yes";
	if (CheckCharacterItem(pchar, "letter_1"))
	{
		AddQuestRecord("Slavetrader", "16");
		AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
		pchar.questTemp.Slavetrader = "winbrig";
		AddComplexSeaExpToScill(100, 100, 100, 150, 100, 100, 0);
	}
	else
	{
		AddQuestRecord("Slavetrader", "17");
		AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_6"),StringFromKey("Slavetrader_7")));
		AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
		pchar.questTemp.Slavetrader = "goodbye_1";
	}
}

void Slavetrader_BrigAttack_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Brig_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetraderbrig.Island, true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	pchar.quest.Slavetrader_BrigShipsOver.over = "yes";
	AddQuestRecord("Slavetrader", "15");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_4"),StringFromKey("Slavetrader_5")));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
	CloseQuestHeader("Slavetrader");
	ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 50);
	pchar.questTemp.Slavetrader = "goodbye";
	ChangeOfficersLoyality("bad_all",1);
}

void Slavetrader_enterSoldiers() //арестовывающие солдеры
{	
	LAi_SetPlayerType(pchar);
	LAi_group_Delete("EnemyFight"); 
	pchar.questTemp.Slavetrader = "After_enterSoldiers";
	iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
	int iNation = sti(pchar.questTemp.Slavetrader.Nation);
	for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SLSold"+i, "sold_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", iTemp, iNation, 0, true, "soldier"));
		SetFantomParamFromRank(sld, iTemp, true);         
		LAi_SetWarriorType(sld); 
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
    }
    sld = GetCharacter(NPC_GenerateCharacter("SLOfficer", "off_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", iTemp, iNation, 0, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
	sld.Dialog.Filename = "Quest\Other_Quests_NPC.c";
	sld.dialog.currentnode = "Slave_arest";
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void Slavetrader_Bonanza(string qName)//cоздание индейцев 
{
	chrDisableReloadToLocation = true;
    for (i=1; i<=8; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("STIndian"+i, "canib_"+(rand(5)+1), "man", "man", 25, PIRATE, 0, true, "quest"));                    
        FantomMakeCoolFighter(sld, 25, 65, 65, "blade_02", "", "", 150);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        GetCharacterPos(pchar, &locx, &locy, &locz);
		sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
		if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
		ChangeCharacterAddressGroup(sld, "Shore18", "goto", sTemp);
    }
	sld = GetCharacter(NPC_GenerateCharacter("Nabuki", "Canib_Boss", "man", "man", 35, PIRATE, 0, true, "quest"));
    sld.name 	= StringFromKey("Slavetrader_8");
    sld.lastname = StringFromKey("Slavetrader_9");
	FantomMakeCoolFighter(sld, 35, 80, 80, "topor_01", "pistol4", "bullet", 150);
	TakeNItems(sld, "jewelry2", 120+rand(80));
	TakeNItems(sld, "jewelry3", 120+rand(60));
	TakeNItems(sld, "jewelry4", 140+rand(50));
	TakeNItems(sld, "jewelry6", rand(50));
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true;
	sld.cirassId = Items_FindItemIdx("cirass1"); 
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
	if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
	ChangeCharacterAddressGroup(sld, "Shore18", "goto", sTemp);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
}

void Slavetrader_GetHispanShore()//определение бухты, из которой галеон выйдет
{
	pchar.questTemp.Slavetrader.Island = "Caracas";
	pchar.questTemp.Slavetrader.Island.Shore = "Shore21";
	pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_10");
	while(pchar.questTemp.Slavetrader.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
	{
		pchar.questTemp.Slavetrader.Island = "Cumana";
		pchar.questTemp.Slavetrader.Island.Shore = "Shore19";
		pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_11");
	}
}

void Slavetrader_SlaveHalleon_AfterBattle(string qName)//реакция на победу
{
	Group_DeleteGroup("SlaveGalleon");
	pchar.quest.Slavetrader_SlaveGalleonOver.over = "yes";
	AddQuestRecord("Slavetrader", "19");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	ChangeCharacterComplexReputation(pchar,"nobility", -5);
	pchar.questTemp.Slavetrader = "wingalleon";
}

void Slavetrader_SlaveGalleonOver(string qName)//просроченный таймер
{
	Group_DeleteGroup("SlaveGalleon");
	pchar.quest.Slavetrader_SlaveGalleon.over = "yes";
	pchar.quest.SlaveHalleon_AfterBattle.over = "yes";
	AddQuestRecord("Slavetrader", "7_2");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "lostgalleon";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_RatCorvette(string qName)//создание корвета крысы
{
	ref sld;
	string sTemp;
    Island_SetReloadEnableGlobal("Tortuga", false);
    Group_FindOrCreateGroup("Rat_Attack");
	Group_SetType("Rat_Attack", "war");
	sTemp = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("RatCap", "Gontier", "man", "man", 35, FRANCE, 3, true, "quest"));
	sld.name = StringFromKey("Slavetrader_12");
	sld.lastname = StringFromKey("Slavetrader_13");
	FantomMakeCoolSailor(sld, SHIP_CORVETTE, sTemp, CANNON_TYPE_CANNON_LBS20, 100, 70, 70);
	FantomMakeCoolFighter(sld, 35, 80, 80, "blade_18", "pistol5", "bullet", 200);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Ship.Mode = "pirate";
	Group_AddCharacter("Rat_Attack", "RatCap");
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	Group_SetGroupCommander("Rat_Attack", "RatCap");
	Group_SetTaskAttack("Rat_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Rat_Attack", PLAYER_GROUP);
	Group_SetAddress("Rat_Attack", "Tortuga", "", "");
	Group_LockTask("Rat_Attack");	
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Rat_Attack";
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_RatAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_RatAttack_DieHard";//это слинял
	pchar.quest.Slavetrader_RatCorvetteOver.over = "yes";
}

void Slavetrader_RatAttack_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Rat_Attack");
	Island_SetReloadEnableGlobal("Tortuga", true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	AddQuestRecord("Slavetrader", "21_12");
	pchar.questTemp.Slavetrader = "wincorvette";
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
}

void Slavetrader_RatAttack_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Rat_Attack");
    Island_SetReloadEnableGlobal("Tortuga", true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	AddQuestRecord("Slavetrader", "21_11");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_14"),StringFromKey("Slavetrader_15")));
	pchar.questTemp.Slavetrader = "lostcorvette";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_RatCorvetteOver(string qName)//просроченный таймер корвета
{
	pchar.quest.Slavetrader_RatAttack.over = "yes";
	AddQuestRecord("Slavetrader", "21_10");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_2"),StringFromKey("Slavetrader_3")));
	pchar.questTemp.Slavetrader = "lostcorvette";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_GetEscapeShore()//выбираем маяк, куда беглых рабов запхнем
{
	switch (rand(9))
	{
		case 0:
			pchar.questTemp.Slavetrader.EsIsland = "Barbados";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak2";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_16");
			break;
		case 1:
			pchar.questTemp.Slavetrader.EsIsland = "Guadeloupe";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak4";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_17");
			break;
		case 2:
			pchar.questTemp.Slavetrader.EsIsland = "Cuba1";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak9";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_18");
			break;
		case 3:
			pchar.questTemp.Slavetrader.EsIsland = "Cuba2";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak10";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_19");
			break;
		case 4:
			pchar.questTemp.Slavetrader.EsIsland = "Tortuga";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak6";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_20");
			break;
		case 5:
			pchar.questTemp.Slavetrader.EsIsland = "Trinidad";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak1";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_21");
			break;
		case 6:
			pchar.questTemp.Slavetrader.EsIsland = "Nevis";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak5";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_22");
			break;
		case 7:
			pchar.questTemp.Slavetrader.EsIsland = "Hispaniola1";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak8";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_23");
			break;
		case 8:
			pchar.questTemp.Slavetrader.EsIsland = "Hispaniola2";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak7";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_24");
			break;
		case 9:
			pchar.questTemp.Slavetrader.EsIsland = "Cartahena";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak11";
			pchar.questTemp.SlavetraderAreal.add = StringFromKey("Slavetrader_25");
			break;
	}
}

void Slavetrader_EscapeSlaveInShore(string qName)
{
	string sShore = pchar.questTemp.Slavetrader.Island.Shore;
    LAi_group_Delete("EnemyFight"); 
	chrDisableReloadToLocation = true; //закроем локацию
	GetCharacterPos(pchar, &locx, &locy, &locz);
	//наши
    for (i=1; i<=3; i++)
    {
        iTemp = 10+rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("OwnCrew_"+i, "citiz_"+(rand(8)+42), "man", "man", iTemp, sti(pchar.nation), 0, true, "soldier"));
		SetFantomParamFromRank(sld, iTemp, true);
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
		if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
        ChangeCharacterAddressGroup(sld, sShore, "goto", sTemp);
    }
	//враги
	for (i=21; i<=27; i++)
    {
		iTemp = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
		sld = GetCharacter(NPC_GenerateCharacter("EscapeSlave_"+i, "prizon_"+(rand(3)+1), "man", "man_B", iTemp, PIRATE, -1, true, "marginal"));
		SetFantomParamFromRank(sld, iTemp, true);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        GetCharacterPos(pchar, &locx, &locy, &locz);
        ChangeCharacterAddressGroup(sld, sShore, "goto", "goto"+i);
    }
	sld = GetCharacter(NPC_GenerateCharacter("Jimmy", "Tamango", "man", "man", 30, PIRATE, 0, true, "quest"));
	sld.name 	= StringFromKey("Slavetrader_26");
	sld.lastname = StringFromKey("Slavetrader_27");
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade_06", "pistol1", "bullet", 100);
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.cirassId = Items_FindItemIdx("cirass1");
	sld.DontClearDead = true;
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "EnemyFight");
    GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, sShore, "goto", "goto30");
	LAi_LocationDisableOfficersGen(sShore, false);
	LAi_LocationFightDisable(loadedLocation, false);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Slavetrader_EscapeSlaves_Win");
}

void Slavetrader_Slavewoman()
{
	sld = characterFromId("Slavewoman");	
	LAi_SetPlayerType(pchar);
	SetCharacterRemovable(sld, false);
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "goto", "goto2", "none", "", "", "", 15.0);
	sld.lifeday = 0;
	for (i=10; i<=25; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SlaveShor_"+i, "prizon_"+(rand(3)+1), "man", "man_B", 10, PIRATE, 0, true, "quest"));
		FantomMakeCoolFighter(sld, 25, 100, 100, "", "","", 80);
		ChangeCharacterAddressGroup(sld, pchar.questTemp.Slavetrader.Island.Shore, "goto",  "goto"+i);
		sld = characterFromID("SlaveShor_"+i);
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		LAi_SetCitizenTypeNoGroup(sld);
		LAi_CharacterDisableDialog(sld);
	}
	SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES) + 1000 + rand(100));
	sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
	AddQuestRecord("Slavetrader", "22");
	AddQuestUserData("Slavetrader", "sQty", sTemp);
	pchar.questTemp.Slavetrader = "escapeslave_win";
	ChangeCharacterComplexReputation(pchar, "nobility", -1);
	OfficersReaction("bad");
}

void Slavetrader_CreateLineShips(string qName)//создание линейных кораблей
{
	int i;
	ref sld;
	string sTemp;

	Island_SetReloadEnableGlobal("Cuba2", false);
    Group_FindOrCreateGroup("Havana_Attack");
	Group_SetType("Havana_Attack", "war");
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);//ссорим ГГ и испанцев
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("HavanaAttack_"+i, "off_spa_"+i, "man", "man", 35, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_LINESHIP, "", CANNON_TYPE_CANNON_LBS36, 100, 100, 100);
		FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
		Group_AddCharacter("Havana_Attack", "HavanaAttack_"+i);
		sld.AlwaysEnemy = true;
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);
    }
	Group_SetGroupCommander("Havana_Attack", "HavanaAttack_1");
	Group_SetTaskAttack("Havana_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Havana_Attack", PLAYER_GROUP);
	Group_SetAddress("Havana_Attack", "Cuba2", "", "");
	Group_LockTask("Havana_Attack");
	bQuestDisableMapEnter = true; //запрещаем выход на глобу, чтоб не взяли форт до потопления	
   
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Havana_Attack";
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_HavanaAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHardHavana.win_condition.l1 = "MapEnter";//не лезь на карту
    pchar.quest.Slavetrader_DieHardHavana.function = "Slavetrader_HavanaAttack_DieHard";//теперь пеняй на себя
	AddQuestRecord("Slavetrader", "25");
}

void Slavetrader_HavanaAttack_AfterBattle(string qName)//реакция на победу
{
	bQuestDisableMapEnter = false;
	Group_DeleteGroup("Havana_Attack");
	Island_SetReloadEnableGlobal("Cuba2", true);
	AddQuestRecord("Slavetrader", "26");
}

void Slavetrader_HavanaAttack_DieHard(string qName)//если надумал починиться
{
	pchar.quest.Slavetrader_HavanaOver.over = "yes";//снимем таймер
	characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "CAPTURE_Main";//снимем ноду губеру
	AddQuestRecord("Slavetrader", "26_1");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_2"),StringFromKey("Slavetrader_3")));
	CloseQuestHeader("Slavetrader");
	pchar.questTemp.Slavetrader = "End_quest";
}

void Slavetrader_HavanaOver(string qName)//просроченный таймер
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Slavetrader_HavanaOver.over"))
			DeleteAttribute(pchar,"quest.Slavetrader_HavanaOver.over");
		NewGameTip(StringFromKey("Slavetrader_1"));
		SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);
		return;
	}
	pchar.quest.Slavetrader_HavanaAttack.over = "yes";
	AddQuestRecord("Slavetrader", "28");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_4"),StringFromKey("Slavetrader_5")));
	ChangeOfficersLoyality("bad_all", 1);
	CloseQuestHeader("Slavetrader");
	characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "CAPTURE_Main";
	pchar.questTemp.Slavetrader = "End_quest";
}

void Slavetrader_FiveTSlavesOver(string qName)//просроченный таймер
{
	ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 90);
	AddQuestRecord("Slavetrader", "30");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_2"),StringFromKey("Slavetrader_3")));
	CloseQuestHeader("Slavetrader");
	pchar.questTemp.Slavetrader = "End_quest";
}

void Slavetrader_HavanaSeekOver(string qName)//просроченный таймер
{
	ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 90);
	AddQuestRecord("Slavetrader", "31");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("Slavetrader_2"),StringFromKey("Slavetrader_3")));
	CloseQuestHeader("Slavetrader");
	pchar.questTemp.Slavetrader = "End_quest";
}

void Slavetrader_UsurerEscape(string qName)//меняем модель ростовщика
{
	sld = characterFromId(pchar.questTemp.Slavetrader.UsurerId);
	sld.name = StringFromKey("Slavetrader_28");
	sld.lastname = StringFromKey("Slavetrader_29");
	sld.model = "trader_8";
	LocatorReloadEnterDisable(pchar.questTemp.Slavetrader.Cityname, "reload8_back", false);
}
//<-- Работорговец конец


//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Slavetrader_QuestComplete(string sQuestName, string qname)
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason----------------------------------------------работорговец---------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld;
	
	bool condition = true;
	
	if (sQuestName == "Slavetrader_findTortugaRat") // охрана Гонтьера
	{
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			sld = GetCharacter(NPC_GenerateCharacter("Ratlover", "women_14", "woman", "towngirl", 10, FRANCE, -1, false, "citizen"));
			ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "barmen",  "bar2");
			sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_lover"; // диалоговый узел
			sld.name 	= StringFromKey("Slavetrader_30");
			sld.lastname 	= StringFromKey("Slavetrader_31");            
			LAi_SetImmortal(sld, true);
			LAi_SetStayTypeNoGroup(sld);
			
			sld = GetCharacter(NPC_GenerateCharacter("SLBanditHead", "citiz_50", "man", "man", 25, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 45, 100, 100, "blade_06", "pistol6", "bullet", 80);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_SetStayType(sld);
			sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_bandos";
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto",  "goto1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.3);
	}
	else if (sQuestName == "Slavetrader_findTortugaRat1") // охрана Гонтьера
	{
			for (i=3; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SVBandit"+i, "citiz_"+(40+i), "man", "man", 25, PIRATE, 0, true, "quest"));
				FantomMakeCoolFighter(sld, 35, 100, 100, "blade_10", "pistol6", "bullet", 80);
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto",  "goto"+i);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat2");
	}
	else if (sQuestName == "Slavetrader_findTortugaRat2")
	{
			chrDisableReloadToLocation = false;
			LAi_SetActorType(pchar);
			sld = characterFromID("Ratlover");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	}
	else if (sQuestName == "Slavetrader_EscapeSlaves_Win")
	{
			chrDisableReloadToLocation = false;
			sld = GetCharacter(NPC_GenerateCharacter("Slavewoman", "Izaura", "woman", "towngirl", 10, PIRATE, -1, false, "citizen"));
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Slavetrader.Island.Shore, "goto",  "goto31");
			sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Slave_woman"; 
			sld.name 	= StringFromKey("Slavetrader_32");
			sld.lastname 	= StringFromKey("Slavetrader_33");            
			LAi_SetImmortal(sld, true);
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetActorType(pchar);
			sld = characterFromID("Slavewoman");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	}
	//<-- работорговец конец
	else
	{
		condition = false;
	}
	
	return condition;
}