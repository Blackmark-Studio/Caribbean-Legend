/////////////////////////////////////////////////////////////////////////////////////////////////////////
///------------------------------------------Макроквесты------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////

///----------------------------Голландский Гамбит, часть 1 - за Голландию-------------------------------

//--------------------------------------------1 задание-----------------------------------------------
void HWICofficerTalk(string qName)//говорилка офицера
{
	sld = characterFromId("HWIC_officer");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void HWICofficerTalkReturn(string qName)//возврат говорилки
{
	pchar.quest.HWIC_officer.win_condition.l1 = "location";
	pchar.quest.HWIC_officer.win_condition.l1.location = "GVIK"; // belamour legendary edition
	pchar.quest.HWIC_officer.function = "HWICofficerTalk";
}

void Create_Baltazar()//создание торговца
{
	AddQuestRecord("Holl_Gambit", "1-1");
	ReOpenQuestHeader("Holl_Gambit"); // лесник чтобы вышел из архива																					  
	SetFunctionTimerCondition("Create_BaltazarOver", 0, 0, 2, false); //таймер
	sld = GetCharacter(NPC_GenerateCharacter("Baltazar", "trader_2", "man", "man", 5, HOLLAND, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_FLEUT, "", CANNON_TYPE_CANNON_LBS8, 10+rand(5), 10+rand(5), 10+rand(5), 10+rand(5), 15+rand(5));
    SetFantomParamFromRank(sld, 5, true); 
	sld.name = StringFromKey("HollandGambit_1");
	sld.lastname = StringFromKey("HollandGambit_2");
	sld.greeting = "captain_trader";
	sld.AnalizeShips = true;
	SetCharacterGoods(sld, GOOD_FOOD, 222);
	SetCharacterGoods(sld, GOOD_SUGAR, 1600);
	LAi_SetCitizenType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_portoffice", "goto", "goto1");
	sld.dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Baltazar";
	AddLandQuestMark(sld, "questmarkmain");
}

void Create_BaltazarOver(string qName)//не пошли на стрелку - ждать никто не будет
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Create_BaltazarOver.over"))
		DeleteAttribute(pchar,"quest.Create_BaltazarOver.over");
		NewGameTip(StringFromKey("HollandGambit_3"));
		SetFunctionTimerCondition("Create_BaltazarOver", 0, 0, 2, false);
		return;
	}
	AddQuestRecord("Holl_Gambit", "1-2");
	CloseQuestHeader("Holl_Gambit");
	sld = characterFromId("Baltazar");
	LAi_CharacterDisableDialog(sld); // 170712
	sld.lifeday = 0;
	DeleteAttribute(pchar, "questTemp.HWIC.Holl");//ещё можно взять иные варианты
	pchar.questTemp.HWIC.Fail1 = "true";
}

void Baltazar_ConvoyOver(string qName)//опоздали
{
	pchar.quest.BaltazarConvoy_fail.over = "yes";//снять прерывание
	AddQuestRecord("Holl_Gambit", "1-4");
	CloseQuestHeader("Holl_Gambit");
	sld = characterFromId("Baltazar");
	RemoveCharacterCompanion(Pchar, characterFromID("Baltazar"));
	sld.lifeday = 0;
	DeleteAttribute(pchar, "questTemp.HWIC.Holl");//ещё можно взять иные варианты
	pchar.questTemp.HWIC.Fail1 = "true";
	DelMapQuestMarkCity("Marigo");
}

void Baltazar_fail(string qName)//утонул Бальтазар
{
	pchar.quest.Baltazar_ConvoyOver.over = "yes";//снять прерывание
	if (CheckAttribute(pchar, "questTemp.HWIC.Holl.BaltazarAttack")) pchar.quest.BaltazarConvoy_Attack.over = "yes";//снять прерывание, если не было атаки
	AddQuestRecord("Holl_Gambit", "1-5");
	CloseQuestHeader("Holl_Gambit");
	ChangeCharacterComplexReputation(pchar,"nobility", -2); 
	ChangeCharacterNationReputation(pchar, HOLLAND, -2);
	ChangeOfficersLoyality("bad_all", 1);
	DeleteAttribute(pchar, "questTemp.HWIC.Holl");//ещё можно взять иные варианты
	pchar.questTemp.HWIC.Fail1 = "true";
	DelMapQuestMarkCity("Marigo");
}

void Baltazar_complete(string qName)//прибыли в порт
{
	pchar.quest.Baltazar_ConvoyOver.over = "yes";//снять прерывание
	pchar.quest.BaltazarConvoy_fail.over = "yes";//снять прерывание
	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	RemoveCharacterCompanion(Pchar, characterFromID("Baltazar"));
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = characterFromId("Baltazar");
	sld.lifeday = 0;
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Marigo_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	sld.dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Baltazar_5";
	sld.greeting = "captain_complete_1";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 0);
	AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
}

void BaltazarPirateGlobalCreate()//на глобальной карте
{
    ref sld;
    string sCapId = "FollowerHWIC0"; // patch
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	SelectLevelWarShipParameter();//автолевеллинг
    for (int i = 1; i <= 2; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "mercen_"+(rand(27)+1), "man", "man", sti(PChar.rank)+MOD_SKILL_ENEMY_RATE/2, PIRATE, 10, true, "hunter"));
		SetRandomNameToCharacter(sld);
		SetRandomNameToShip(sld);
		if (i == 1)
		{
			sld.name = "" + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + "";
			sld.lastname = "";
		}
		sld.Ship.Type = GenerateShipExt(iGlobalTemp, 1, sld);
		SetBaseShipData(sld);
		int hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantity(sld, hcrew);
		SetCrewQuantityFull(sld);
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
        sld.mapEnc.type = "war";
		sld.mapEnc.worldMapShip = "quest_ship";
        sld.mapEnc.Name = "" + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + "";
        Group_AddCharacter(sGroup, sCapId + i);
    }
    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateCoolWarrior("", sCapId + "1", 10);
}

void BaltazarPirateSeaCreate(string qName)//на боевой карте
{
	ref sld;
	DeleteAttribute(pchar, "questTemp.HWIC.Holl.BaltazarAttack");
	Island_SetReloadEnableGlobal("SentMartin", false);//на остров нельзя
	bQuestDisableMapEnter = true;//и на карту тоже нельзя
	Group_FindOrCreateGroup("Baltazar_Attack");
	SelectLevelWarShipParameter();//автолевеллинг
    for (int i = 1; i <= 2; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("BaltPirate_"+i, "mercen_"+(rand(27)+1), "man", "man", sti(PChar.rank)+MOD_SKILL_ENEMY_RATE/2, PIRATE, 10, true, "hunter"));
		FantomMakeSmallSailor(sld, iGlobalTemp, "", iTotalTemp, 10+rand(5), 10+rand(5), 10+rand(5), 10+rand(5), 15+rand(5));
		FantomMakeCoolFighter(sld, sti(PChar.rank)+MOD_SKILL_ENEMY_RATE/2, 30, 30, sTotalTemp, "pistol2", "grapeshot", 30);
		if (i == 1)
		{
			sld.name = "" + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + "";
			sld.lastname = "";
		}
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
        Group_AddCharacter("Baltazar_Attack", "BaltPirate_"+i);
    }
    Group_SetGroupCommander("Baltazar_Attack", "BaltPirate_1");
	Group_SetTaskAttack("Baltazar_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Baltazar_Attack", PLAYER_GROUP);
	Group_SetAddress("Baltazar_Attack", "SentMartin", "", "");
	Group_LockTask("Baltazar_Attack");
    
    pchar.quest.BaltazarAttack_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.BaltazarAttack_AfterBattle.win_condition.l1.group = "Baltazar_Attack";
	pchar.quest.BaltazarAttack_AfterBattle.function = "Baltazar_Attack_AfterBattle";
}

void Baltazar_Attack_AfterBattle(string qName)//после боя
{
	Island_SetReloadEnableGlobal("SentMartin", true);
	bQuestDisableMapEnter = false;
	DoQuestCheckDelay("sea_victory", 1.5);
}

//------------------------------------------1а задание---------------------------------------------
void SantiagoTripOver(string qName)//просрочили - значит, присвоили сундуки, примерно накажем
{
	AddQuestRecord("Holl_Gambit", "1-47");
	CloseQuestHeader("Holl_Gambit");
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterHunterScore(PChar, "holhunter", 100); //начислить НЗГ
	ChangeCharacterHunterScore(PChar, "spahunter", 100); //начислить НЗГ
	DeleteAttribute(pchar, "questTemp.HWIC.Holl");//ещё можно взять иные варианты
	pchar.questTemp.HWIC.Fail1 = "true";
	DelMapQuestMarkCity("Santiago");
	DelLandQuestMark(characterFromId("Santiago_usurer"));
}

void SantiagoTrip_Attack(string qName)//подкраулили
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	LAi_LocationFightDisable(&Locations[FindLocation("Santiago_town")], true); // Addon 2016-1 Jason пиратская линейка
	int iRank = 12+MOD_SKILL_ENEMY_RATE/2;
	int iScl = 20+MOD_SKILL_ENEMY_RATE*2;
	sld = GetCharacter(NPC_GenerateCharacter("SantiagoEnemy1", "mercen_10", "man", "man", iRank, SPAIN, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_06", "pistol1", "bullet", iScl);
	sld.dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Santiago_Trip";
	sld.greeting = "hambit_other_1";
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void SantiagoTripInHouse(string qName)//телепорт
{
	LAi_LocationFightDisable(&Locations[FindLocation("Santiago_town")], false); // Addon 2016-1 Jason пиратская линейка
	bDisableFastReload = false;
	pchar.GenQuestBox.Santiago_HouseSp2_Room = true;
	pchar.GenQuestBox.Santiago_HouseSp2_Room.box1.items.slave_01 = 1;
	pchar.GenQuestBox.Santiago_HouseSp2_Room.box1.items.potion1 = 2;
	DoQuestReloadToLocation("Santiago_HouseSp2_Room", "barmen", "bar2", "SantiagoTripTalkToMC");
	LocatorReloadEnterDisable("Santiago_HouseSp2_Room", "reload1", true);//закрыть выход
	//обчистим карманы ГГ
	//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
	ref location = &Locations[FindLocation("Santiago_HouseSp2")];
	aref arItems, boxItems;
	ref rItem, sld;
	string sName;
	makearef(arItems, PChar.items);
	makearef(boxItems, location.box1.items);
	int iItemsNum = GetAttributesNum(arItems);
	for(int i=0; i<iItemsNum; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sName);
		if (rItem.ItemType != "QUESTITEMS")
		{
			boxItems.(sName) = PChar.items.(sName);
		}
	}
	location.box1.money = sti(PChar.money);	
	location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	RemoveAllCharacterItems(PChar, true);
}

void SantiagoTrip_wait(string qName)//
{
	DoQuestFunctionDelay("SantiagoTrip_Migel", 10.0);
	InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
}

void SantiagoTrip_Migel(string qName)//создаем Мигеля
{
	sld = GetCharacter(NPC_GenerateCharacter("SantiagoEnemy2", "mercen_17", "man", "man", 8, SPAIN, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 8, 10, 10, "blade_05", "", "bullet", 0);
	if (MOD_SKILL_ENEMY_RATE < 7) LAi_SetHP(sld, 35.0, 35.0);
	sld.name = StringFromKey("HollandGambit_4");
	sld.lastname = StringFromKey("HollandGambit_5");
	sld.dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Santiago_Trip_12";
	sld.greeting = "hambit_other_3";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	ChangeCharacterAddressGroup(sld, "Santiago_HouseSp2_Room", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void SantiagoTripSecondTalk(string qName)//драка внизу
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	chrDisableReloadToLocation = true;
	sld = characterFromId("SantiagoEnemy1");
	sld.dialog.currentnode = "Santiago_Trip_14";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

//-----------------------------------------2 задание-----------------------------------------------
void GollandGambit_2_ZadanieStart(string qName)//Квестовая марка
{
	pchar.questTemp.HWIC.Holl = "SantiagoTripComplete";
	AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
	AddMapQuestMarkCity("Villemstad", true);
}

void Create_Longway(string qName)//создаем Лонгвэя
{
	sld = characterFromId("Longway");
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	GetMeifengToCharacter(pchar);//сажаем на Мейфенг
}

void JacobOnMainOver(string qName)//просрочили на стрелку
{
	if (pchar.questTemp.HWIC.Holl == "JacobInRoom")
	{
		sld = characterFromId("JacobBerg");
		sld.lifeday = 0;
		pchar.quest.MirageAttack_DieHard.win_condition.l1 = "MapEnter";
	    pchar.quest.MirageAttack_DieHard.function = "MC_GoAway";
	}
	if(IsEntity(&worldMap)) DoQuestFunctionDelay("MC_GoAway", 0.1);
	else
	{
		pchar.quest.MirageAttack_DieHard.win_condition.l1 = "MapEnter";
	    pchar.quest.MirageAttack_DieHard.function = "MC_GoAway";
	}
}

void Create_JacobVanBerg()//создаем Якоба ван Берга
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2;
	sld = characterFromId("JacobBerg");
	sld.rank = iRank;
    FantomMakeCoolFighter(sld, iRank, 20, 20, "blade_14", "pistol1", "bullet", 50);
    sld.DontClearDead = true;
	sld.SaveItemsForDead = true;
	GiveItem2Character(sld, "JacobJournal");
	GiveItem2Character(sld, "clock1");
	GiveItem2Character(sld, "recipe_totem_13");
	GiveItem2Character(sld, "totem_13");
	LAi_SetCitizenType(sld);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.HWIC.Holl.JacobCity+"_tavern_upstairs", "goto", "goto1");
	AddLandQuestMark(sld, "questmarkmain");
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern_upstairs")], true);
}

void Jacob_Journal(string qName)//журнал Якоба ван Берга - все записи отражаем в документах
{
	chrDisableReloadToLocation = false;
	AddQuestRecordInfo("JacobVanBerg_Journal", "1");
	AddQuestRecord("Holl_Gambit", "1-11");
	pchar.quest.Jacob_Island.win_condition.l1 = "location";
	pchar.quest.Jacob_Island.win_condition.l1.location = "Cumana";
	pchar.quest.Jacob_Island.function = "Create_Mirage";
	pchar.questTemp.HWIC.Holl.Width = "true";// нашли широту острова
	AddMapQuestMarkShore("Shore18", false);
}

void Create_Mirage(string qName)//создаем 'Мираж'
{
	AddQuestRecord("Holl_Gambit", "1-12");
	ref sld;
	int iRank = 13+MOD_SKILL_ENEMY_RATE/2;
	Island_SetReloadEnableGlobal(pchar.questTemp.HWIC.Holl.JacobIsland, false);//на остров нельзя
	Group_FindOrCreateGroup("Mirage");
	Group_SetType("Mirage", "pirate");
	sld = GetCharacter(NPC_GenerateCharacter("MirageCap", "mercen_"+(rand(10)+1), "man", "man", iRank, PIRATE, -1, false, "quest"));
	FantomMakeSmallSailor(sld, SHIP_MIRAGE, StringFromKey("HollandGambit_6"), CANNON_TYPE_CANNON_LBS18, 40+rand(10), 30+rand(20), 30+rand(20), 30+rand(15), 25+rand(25));
	// belamour для легких уровней команду в опт -->
	if(MOD_SKILL_ENEMY_RATE < 7) SetCrewQuantity(sld,GetOptCrewQuantity(sld));
	// <-- legendary edition
	FantomMakeCoolFighter(sld, iRank, 20, 20, "blade_10", "pistol2", "grapeshot", 30);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true;
	sld.AlwaysFriend = true;
	// belamour для легких уровней без МЗ -->
	if(MOD_SKILL_ENEMY_RATE > 7) SetCharacterPerk(sld, "MusketsShoot");
	// <-- legendary edition
	sld.AnalizeShips = true;
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 3;//замшелый корпус
	SetShipSailsFromFile(sld, "ships/parus_torn.tga");
	SetSailsColor(sld, 8);//черный рваный парус
    Group_AddCharacter("Mirage", "MirageCap");
	Group_SetGroupCommander("Mirage", "MirageCap");
	Group_SetTaskNone("Mirage");//нет задачи
	Group_SetAddress("Mirage", "Cumana", "quest_ships", "Quest_ship_6");
	DelMapQuestMarkShore("Shore18");
    
    pchar.quest.MirageAttack_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.MirageAttack_Abordage.win_condition.l1.character = "MirageCap";
	pchar.quest.MirageAttack_Abordage.function = "Mirage_Attack_Win";//взяли на абордаж
	pchar.quest.MirageAttack_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.MirageAttack_Sink.win_condition.l1.character = "MirageCap";
	pchar.quest.MirageAttack_Sink.function = "Mirage_Attack_Fail";//потопили, а нельзя было
}

void Mirage_Attack_Fail(string qName)//потопили Мираж - провал
{
	Island_SetReloadEnableGlobal(pchar.questTemp.HWIC.Holl.JacobIsland, true);
	pchar.quest.MirageAttack_Abordage.over = "yes";
	AddQuestRecord("Holl_Gambit", "1-13");
	pchar.quest.MirageAttack_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.MirageAttack_DieHard.function = "MC_GoAway";
	pchar.questTemp.HWIC.Holl = "MirageFail";
}

void Mirage_Attack_Win(string qName)//после боя - проверяем корабли
{
	pchar.GenQuest.DontPartition = true; // отключить дележ
	Island_SetReloadEnableGlobal(pchar.questTemp.HWIC.Holl.JacobIsland, true);
	pchar.quest.MirageAttack_Sink.over = "yes";
	int iNum = 0;
	for(i = 0; i < COMPANION_MAX; i++)
	{
		int iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			sld = GetCharacter(iTemp);
			if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE || sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iNum++;
		}
	}
	if (iNum != 2)
	{
		pchar.quest.MirageAttack_DieHard.win_condition.l1 = "MapEnter";
	    pchar.quest.MirageAttack_DieHard.function = "MC_GoAway";
		pchar.questTemp.HWIC.Holl = "MirageFail";//потеряли один из кораблей - провал
	}
	else
	{
		AddQuestRecord("Holl_Gambit", "1-14");
		pchar.questTemp.HWIC.Holl = "MirageTake";
		AddComplexSeaExpToScill(80, 50, 50, 130, 80, 80, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		if(bImCasual)
		{
			NewGameTip(StringFromKey("HollandGambit_7"));
			SetFunctionTimerCondition("MirageConvoyOver", 0, 0, 30, false);
		}
		else SetFunctionTimerCondition("MirageConvoyOver", 0, 0, 15, false);
	}
	DoQuestCheckDelay("sea_victory", 1.5);
	AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
	AddMapQuestMarkCity("Villemstad", true);
}

void MirageConvoyOver(string qName)//не пошёл в Виллемстад с Миражом - значит, провалил
{
	pchar.questTemp.HWIC.Holl = "lateVillemstad";
	DelMapQuestMarkCity("Villemstad");
	DelLandQuestMark(characterFromId("Lucas"));
	if(IsEntity(&worldMap)) DoQuestFunctionDelay("MC_GoAway", 0.1);
	else
	{
		pchar.quest.MirageAttack_DieHard.win_condition.l1 = "MapEnter";
	    pchar.quest.MirageAttack_DieHard.function = "MC_GoAway";
	}
}

void MC_GoAway(string qName)//провалил задание - в лодку и в плавание
{
	aref arOldMapPos;
	makearef(arOldMapPos, worldMap.old);
	
	if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
	{
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
		DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
	}
	if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
	{
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
		DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
	}
	sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
	RemoveCharacterCompanion(pchar, sld);
	LAi_SetCitizenType(sld);
    DeleteAttribute(sld, "Payment");
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
	WdmPrepareMapForAbordage(arOldMapPos);
	MakeCloneShipDeck(pchar, true);//клон палубы
	LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], true);
	DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto1");
	LAi_LockFightMode(pchar, true);
	ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto2");
	LAi_SetActorType(sld);
	if (CheckAttribute(pchar, "questTemp.HWIC.Holl")) sld.dialog.Filename = "Quest\HollandGambit\Longway.c";
	if (CheckAttribute(pchar, "questTemp.HWIC.Eng")) sld.dialog.Filename = "Quest\HollandGambit\Knippel.c";
	sld.dialog.currentnode = "MC_GoAway";
	sld.greeting = ""; // озвучка напрямую
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	pchar.quest.Munity = "";//чтобы не выскочил без разговора
	DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
}

void Jacob_RemoveShip()//удаление корабля
{
	if(sti(RealShips[sti(pchar.ship.type)].basetype) == sti(pchar.questTemp.HWIC.Holl.ShipType))
	{
		pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
		pchar.Ship.name = "Лодка";
		SetBaseShipData(pchar);
		SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
	}
	else
	{
		for(i = 1; i < COMPANION_MAX; i++)
		{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
			{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.questTemp.HWIC.Holl.ShipType))
				{
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
					RemoveCharacterCompanion(PChar, sld);
					AddPassenger(PChar, sld, false);
				}
			}
		}
    }
	Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
	sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
	RemoveCharacterCompanion(pchar, sld);
    DeleteAttribute(sld, "Payment");
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
}

//---------------------------------------3 задание--------------------------------------------------------
void ToAntiguaOver(string qName)//потеряли слишком много времени
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.ToAntiguaOver.over"))
		DeleteAttribute(pchar,"quest.ToAntiguaOver.over");
		NewGameTip(StringFromKey("HollandGambit_3"));
		SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false);
		return;
	}
	DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
	pchar.questTemp.HWIC.Holl = "end";
	pchar.questTemp.HWIC.Detector = "holl_fail";
	AddQuestRecord("Holl_Gambit", "1-15_1");
	CloseQuestHeader("Holl_Gambit");
	ChangeCharacterHunterScore(PChar, "holhunter", 100); //начислить НЗГ
	DelMapQuestMarkShore("Shore1");
	DelMapQuestMarkShore("Shore2");
}

void PrepareToFleetwoodAttack(string qName)//пришли на Доминику, а подлого китайца нет
{
	if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.Repeat")) AddQuestRecord("Holl_Gambit", "1-18");
	if (sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_MIRAGE || GetCompanionQuantity(pchar) > 1)
	{//пришли не на том, или с эскадрой - фигвам, а не Флитвуд, круговое прерывание, пока не выполним условия
		pchar.quest.Fleetwood_Return.win_condition.l1 = "MapEnter";
		pchar.quest.Fleetwood_Return.function = "ReturnFleetwoodBreak";
	}
	else
	{
		Island_SetReloadEnableGlobal("Dominica", false);//на остров нельзя			
		bQuestDisableMapEnter = true;
		DoQuestFunctionDelay("CreateFleetwoodOnMap", 15.0);
	}
}

void ReturnFleetwoodBreak(string qName)//второй раз, третий, четвертый... пока не дойдет
{
	pchar.quest.toDominica.win_condition.l1 = "location";
	pchar.quest.toDominica.win_condition.l1.location = "Dominica";
	pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
	pchar.questTemp.HWIC.Holl.Repeat = "true";
}

void CreateFleetwoodOnMap(string qName)//подгружаем в море энкаунтер Флитвуда
{
	DeleteAttribute(pchar, "questTemp.HWIC.Holl.Repeat");
	int iRank = 15+MOD_SKILL_ENEMY_RATE/2;
	Group_FindOrCreateGroup("Fleetwood_Attack");
	sld = characterFromId("Fleetwood");
	// belamour для легких уровней Флитвуд хуже стреляет -->
	if(MOD_SKILL_ENEMY_RATE < 7) FantomMakeSmallSailor(sld, SHIP_VALCIRIA, StringFromKey("HollandGambit_8"), CANNON_TYPE_CANNON_LBS16, 40+rand(10), 35+rand(20), 35+rand(20), 20+rand(14), 25+rand(20));
	else FantomMakeSmallSailor(sld, SHIP_VALCIRIA, StringFromKey("HollandGambit_8"), CANNON_TYPE_CANNON_LBS16, 40+rand(10), 35+rand(20), 35+rand(20), 30+rand(15), 35+rand(25));
	// <-- legendary edition
	FantomMakeCoolFighter(sld, iRank, 30, 30, "blade_14", "pistol3", "grapeshot", 50);
	GiveItem2Character(sld, "FleetwoodJournal");
	GiveItem2Character(sld, "sand_clock");
	sld.DontClearDead = true;
	sld.SaveItemsForDead = true;
	GiveItem2Character(sld, "spyglass3");
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.Coastal_Captain = true; //не ссорить нации
	sld.AnalizeShips = true;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Fleetwood_Attack", "Fleetwood");
    Group_SetGroupCommander("Fleetwood_Attack", "Fleetwood");
	Group_SetTaskAttack("Fleetwood_Attack", PLAYER_GROUP);
	Group_SetAddress("Pirate_Attack", "Dominica", "", "");
    Group_LockTask("Fleetwood_Attack");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Sea_LoginGroupCurrentSea("Fleetwood_Attack");
	log_info(StringFromKey("HollandGambit_9"));
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy1.wav");;
	AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
	AddMapQuestMarkCity("Villemstad", true);
	
	pchar.quest.FleetwoodAttack_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.FleetwoodAttack_AfterBattle.win_condition.l1.group = "Fleetwood_Attack";
	pchar.quest.FleetwoodAttack_AfterBattle.function = "Fleetwood_AfterBattle";
	//прерывание на Мейфенг у Кюрасао ставим тут
	pchar.quest.Fleetwood_Complete.win_condition.l1 = "location";
	pchar.quest.Fleetwood_Complete.win_condition.l1.location = "Curacao";
	pchar.quest.Fleetwood_Complete.function = "CreateEmptyMeifeng";
}

void Fleetwood_AfterBattle(string qName)//потопили Флитвуда - острова теперь не найти
{
	DeleteAttribute(pchar, "questmaplock");
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal("Dominica", true);//на остров можно	
	if (pchar.questTemp.HWIC.Holl != "FleetwoodCapture")
	{
		Group_DeleteGroup("Fleetwood_Attack");
		AddQuestRecord("Holl_Gambit", "1-19");
		pchar.questTemp.HWIC.Holl = "FleetwoodSink";
	}
	DoQuestCheckDelay("sea_victory", 1.5);
}

void FleetwoodJournalFind(string qName)//журнал Флитвуда
{
	pchar.GenQuest.DontPartition = true; // отключить дележ
	pchar.quest.FleetwoodAttack_AfterBattle.over = "yes";
	pchar.quest.FleetwoodAttack_DieHard.over = "yes";
	Group_DeleteGroup("Fleetwood_Attack");
	if(CheckCharacterItem(pchar, "FleetwoodJournal"))
	{
		AddQuestRecord("Holl_Gambit", "1-20");
		AddQuestRecordInfo("Fleetwood_Journal", "1");
		pchar.questTemp.HWIC.Holl.Longitude = "true";//нашли долготу острова
	}
	else AddQuestRecord("Holl_Gambit", "1-21");//не нашли журнал - олухи
	AddComplexSeaExpToScill(100, 60, 60, 150, 100, 100, 0);
	AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
}

void CreateEmptyMeifeng(string qName)//Мейфенг без китайца в порту Виллемстада
{
	Island_SetReloadEnableGlobal("Dominica", true);//patch-7
	Group_FindOrCreateGroup("Meifeng_Empty");
	sld = GetCharacter(NPC_GenerateCharacter("MeifengCap", "off_hol_2", "man", "man", 40, HOLLAND, -1, true, "quest"));
	sld.name = StringFromKey("HollandGambit_10");
	sld.lastname = StringFromKey("HollandGambit_11");
	FantomMakeSmallSailor(sld, SHIP_MAYFANG, StringFromKey("HollandGambit_12"), CANNON_TYPE_CANNON_LBS16, 90+rand(10), 80+rand(20), 80+rand(20), 80+rand(15), 75+rand(25));
	SetFantomParamFromRank(sld, 40, true); 
	Character_SetAbordageEnable(sld, false);//нельзя абордировать
	sld.AnalizeShips = true;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Meifeng_Empty", "MeifengCap");
	Group_SetGroupCommander("Meifeng_Empty", "MeifengCap");
	Group_SetAddress("Meifeng_Empty", "Curacao", "Islandships1", "ship_2");
	AddQuestRecord("Holl_Gambit", "1-22");
	pchar.quest.Meifeng_fail.win_condition.l1 = "NPC_Death";
	pchar.quest.Meifeng_fail.win_condition.l1.character = "MeifengCap";
	pchar.quest.Meifeng_fail.function = "HollGambit_failed";//для особо умных
}

void HollGambit_failed(string qName)//если у кого-то хватит наглости
{
	Group_DeleteGroup("Meifeng_Empty");
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterHunterScore(PChar, "holhunter", 100); //начислить НЗГ
	AddQuestRecord("Holl_Gambit", "1-23");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Holl = "end";
	pchar.questTemp.HWIC.Detector = "holl_fail";
}

void Lucas_ExangeShip()//обмен корабля
{
	if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MIRAGE)
	{
		GetMeifengToCharacter(pchar);//даем Мейфенг навсегда - ну неужели эти корабельные обмены окончены? 
	}
	else
	{
		for(i = 1; i < COMPANION_MAX; i++)
		{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
			{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
				{
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
					GetMeifengToCharacter(sld);//сажаем на Мейфенг
				}
			}
		}
	}
}

void GetMeifengToCharacter(ref rChar)//сажаем на Мейфенг
{
	rChar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, rChar);
	rChar.Ship.name = StringFromKey("HollandGambit_12");
	SetBaseShipData(rChar);
	rChar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
	SetCrewQuantityFull(rChar);
	AddCrewMorale(rChar, 50);
	ChangeCrewExp(rChar, "Sailors", 30);
	ChangeCrewExp(rChar, "Cannoners", 30);
	ChangeCrewExp(rChar, "Soldiers", 30);
	SetCharacterGoods(rChar, GOOD_BALLS, 200);
	SetCharacterGoods(rChar, GOOD_GRAPES, 300);
	SetCharacterGoods(rChar, GOOD_KNIPPELS, 300);
	SetCharacterGoods(rChar, GOOD_BOMBS, 500);
	SetCharacterGoods(rChar, GOOD_FOOD, 500);
	SetCharacterGoods(rChar, GOOD_POWDER, 800);
	SetCharacterGoods(rChar, GOOD_WEAPON, 300);
	SetCharacterGoods(rChar, GOOD_MEDICAMENT, 150);
}

void AwardFromFromLucas(string qName)//церемония награждения
{
	bDisableFastReload = true;
	sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "governor1");
	sld = characterFromId("Lucas");
	sld.dialog.currentnode = "LucasAward";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto3");
	for (i=1; i<=3; i++)
	{
		ref chr = GetCharacter(NPC_GenerateCharacter("LucasGuard_"+i, "sold_hol_1"+i, "man", "man", 35, HOLLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(chr, 35, 90, 90, "blade_10", "pistol3", "grapeshot", 200);//группа альфа
		LAi_SetActorType(chr);
		if (i == 3) ChangeCharacterAddressGroup(chr, "Villemstad_townhall", "goto", "goto1");
		else ChangeCharacterAddressGroup(chr, "Villemstad_townhall", "goto", "goto"+(i+3));
		LAi_ActorTurnToCharacter(chr, pchar);
	}
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	LAi_ActorTurnToCharacter(sld, pchar);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
}

//-------------------------------------------4 задание--------------------------------------------------------
void GollandGambit_4_ZadanieStart(string qName)//Квестовая марка
{
	pchar.questTemp.HWIC.Holl = "Abby_prepare";
	AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
	AddMapQuestMarkCity("Villemstad", true);
}

void Create_Joakim(string qName)//создаем Жоакима
{
	sld = characterFromId("Joakim");
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	//хозяйка дома
	sld = GetCharacter(NPC_GenerateCharacter("Landlady", "women_7", "woman", "towngirl", 5, HOLLAND, -1, false, "quest"));
	LAi_SetOwnerType(sld);
	sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
	sld.dialog.currentnode = "Landlady";
	ChangeCharacterAddressGroup(sld, "Villemstad_houseSp1", "goto", "goto1");
}

void JoakimTalk(string qName)//Жоаким в комнате
{
	sld = characterFromId("Joakim");
	sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
	if (CheckAttribute(pchar, "questTemp.HWIC.Holl")) sld.dialog.currentnode = "JoakimSeekSkull_3";
	else sld.dialog.currentnode = "JoakimSeekSkull_8";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CheckIslandCoordinates()//проверка наличия координат острова у ГГ
{
	if (CheckAttribute(pchar, "questTemp.HWIC.Holl.Width") && CheckAttribute(pchar, "questTemp.HWIC.Holl.Longitude"))
	{
		AddQuestRecord("Holl_Gambit", "1-28");
		pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
	}
	else
	{
		pchar.questTemp.HWIC.Holl = "NotFindAbbyIsland";
		AddQuestRecord("Holl_Gambit", "1-29");
		AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
	}
}

void PrepareSearchingFor()//подготовка-сценка
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_SetBarmanType(pchar);
	DoQuestCheckDelay("TalkSelf_Quest", 15.0);
}

void SearchingForIslandOnMap()//подготовим остров к посещению
{
	pchar.questTemp.HWIC.Isladecoche = "true"; // Addon 2016-1 Jason Пиратская линейка; флаг - Исла де Коче найден
	DeleteAttribute(pchar, "questTemp.HWIC_FindIsland"); // 021012
	chrDisableReloadToLocation = false;//открыть локацию
	AddQuestRecord("Holl_Gambit", "3-60");
	AddMapQuestMarkIsland("IslaDeCoche", false);
	i = FindIsland("IslaDeCoche");
	Islands[i].visible = true;
	Islands[i].reload_enable = true;
	if (CheckAttribute(pchar, "questTemp.HWIC.Holl") || CheckAttribute(pchar, "questTemp.HWIC.Self"))
	{
		pchar.GenQuestBox.IslaDeCoche_Grot = true;
		pchar.GenQuestBox.IslaDeCoche_Grot.box1.money = 200000;
		pchar.GenQuestBox.IslaDeCoche_Grot.box1.items.jewelry5 = 100;
		pchar.GenQuestBox.IslaDeCoche_Grot.box1.items.SkullAztec = 1;
	}
	if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
	{
		pchar.GenQuestBox.IslaDeCoche_Grot = true;
		pchar.GenQuestBox.IslaDeCoche_Grot.box1.items.GastonHead = 1;//бошка бармена
	}
	LAi_SetPlayerType(pchar);
	pchar.quest.Abby_IslandSea.win_condition.l1 = "location";
	pchar.quest.Abby_IslandSea.win_condition.l1.location = "IslaDeCoche";
	pchar.quest.Abby_IslandSea.function = "IslaDeCocheInSea";//на выход в локацию острова
	pchar.quest.Abby_IslandGrot.win_condition.l1 = "location";
	pchar.quest.Abby_IslandGrot.win_condition.l1.location = "IslaDeCoche_Grot";
	pchar.quest.Abby_IslandGrot.function = "IslaDeCocheInGrot";//на посещение грота
	if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
	{
		pchar.quest.Abby_IslandSkullAztec.win_condition.l1 = "item";
		pchar.quest.Abby_IslandSkullAztec.win_condition.l1.item = "SkullAztec";
		pchar.quest.Abby_IslandSkullAztec.function = "SkullAztec_Find";//на нахождение черепа
	}
	if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
	{
		pchar.quest.Abby_IslandFight.win_condition.l1 = "locator";
		pchar.quest.Abby_IslandFight.win_condition.l1.location = "IslaDeCoche_Grot";
		pchar.quest.Abby_IslandFight.win_condition.l1.locator_group = "box";
		pchar.quest.Abby_IslandFight.win_condition.l1.locator = "box1";
		pchar.quest.Abby_IslandFight.function = "BoomInGrot";//на взрыв и создание монстра
	}
	if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
	{
		pchar.quest.Abby_IslandBattle.win_condition.l1 = "item";
		pchar.quest.Abby_IslandBattle.win_condition.l1.item = "SkullAztec";
		pchar.quest.Abby_IslandBattle.function = "BattleInGrot";//на бойцов ван Берга
	}
	
	// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
    pchar.GenQuest.SeaHunter2Pause = true;
    SeaHunter_Delete();
}

void IslaDeCocheInSea(string qName)//вышли у острова
{
	AddQuestRecord("Holl_Gambit", "1-30");
	LAi_LocationDisableOfficersGen("IslaDeCoche_Grot", true);//офицеров в грот не пускать
	LAi_LocationDisableMonGenTimer("IslaDeCoche_Grot", 3); //монстров не генерить
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void IslaDeCocheInGrot(string qName)//вошли в грот
{
	PlaySound("interface\notebook.wav");
	Log_info(StringFromKey("HollandGambit_13"));
}

void SkullAztec_Find(string qName)//нашли схрон и череп
{
	AddQuestRecord("Holl_Gambit", "1-31");
	pchar.questTemp.HWIC.Holl = "AbbyFindScull";//а теперь к Соломону
	LAi_LocationDisableOfficersGen("IslaDeCoche_Grot", false);//офицеров пускать
	DelMapQuestMarkIsland("IslaDeCoche");
	AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
	AddLandQuestMark(characterFromId("Joakim"), "questmarkmain");
	AddMapQuestMarkCity("Villemstad", false);
}

void DeleteJoakimFromRoom(string qName)//закрыть комнату Жоакима и пусть там сидит
{
	sld = characterFromId("Landlady");
	sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
	sld.dialog.currentnode = "Landlady_1";
	sld = characterFromId("Joakim");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

//-------------------------------------------5 задание-----------------------------------------------------
void GollandGambit_5_ZadanieStart(string qName)//Квестовая марка
{
	AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
	AddMapQuestMarkCity("Villemstad", false);
}

void GiveTaskMerdok(string qName)//посыльный на последнее задание
{
	LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
	bDisableFastReload = true;
	sld = GetCharacter(NPC_GenerateCharacter("HollQuestOff", "off_hol_2", "man", "man", 20, HOLLAND, 0, false, "quest"));
    sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "HollQuest_Officer";
    FantomMakeCoolFighter(sld, 20, 20, 20, "blade_12", "pistol3", "grapeshot", 50);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void MerdokInUndergroundCave(string qName)//установим Мердока и Тонзага в подземелье
{
	sld = characterFromId("Bridgetown_tavernkeeper");
	sld.model = "barmen_3";
	sld.name = StringFromKey("HollandGambit_14");
	sld.lastname = StringFromKey("HollandGambit_15");//перерисуем бармена Бриджтауна
	sld.greeting = "barmen_1";
	LAi_group_Delete("EnemyFight");
	LAi_LocationDisableMonGenTimer("SentJons_TownCave", 3); //монстров не генерить
	LocatorReloadEnterDisable("SentJons_TownCave", "reload2", true);//выход сразу закроем
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретим драться
	sld = characterFromId("Merdok");
	sld.greeting = "merdok_6";
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_27", "pistol6", "bullet", 100); // приз - саксенфедер 090912
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "Drugstore_keys");//ключи
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "item", "berglar1");
	//помощник Мердока - Тонзаг
	sld = characterFromId("Tonzag");	
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_07", "pistol6", "bullet", 150);
	LAi_SetStayType(sld);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "reload", "reload1_back");
	pchar.quest.Merdok_Fight.win_condition.l1 = "locator";
	pchar.quest.Merdok_Fight.win_condition.l1.location = "SentJons_TownCave";
	pchar.quest.Merdok_Fight.win_condition.l1.locator_group = "item";
	pchar.quest.Merdok_Fight.win_condition.l1.locator = "berglar1";
	pchar.quest.Merdok_Fight.function = "MerdokPrepareFight";
	pchar.GenQuestBox.SentJons_HouseF3 = true;
	pchar.GenQuestBox.SentJons_HouseF3.box1.money = 25000;
	pchar.GenQuestBox.SentJons_HouseF3.box1.items.MerdokArchive = 1;//архив
}

void MerdokPrepareFight(string qName)//подготовка к бою
{
	sld = characterFromId("Merdok");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void FindMerdokKey(string qName)//теперь у нас есть ключ
{
	LocatorReloadEnterDisable("SentJons_TownCave", "reload2", false);//выход откроем // patch-9
	if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
	{
		AddQuestRecord("Holl_Gambit", "2-27");
		CloseQuestHeader("Holl_Gambit");
		pchar.questTemp.HWIC.Detector = "eng_win";
		Achievment_Set("ach_10");
		CheckPortugalHWIC();
		AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		AddMapQuestMarkCity("FortFrance", false);
	}
	pchar.quest.Merdok_Door.win_condition.l1 = "locator";
	pchar.quest.Merdok_Door.win_condition.l1.location = "SentJons_TownCave";
	pchar.quest.Merdok_Door.win_condition.l1.locator_group = "reload";
	pchar.quest.Merdok_Door.win_condition.l1.locator = "reload1_back";
	pchar.quest.Merdok_Door.function = "OpenDungeDoor";//на локатор входа в дом
	pchar.quest.Jino_Door.win_condition.l1 = "locator";
	pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
	pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
	pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
	pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
	DelMapQuestMarkIsland("Caiman");
}

void OpenDungeDoor(string qName)//вошли в локатор двери дома
{
	PlaySound("interface\key.wav");//щелк!
	LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем дверь в дом
	LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем дверь в подвал из дома
	LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//аптеку откроем
}

void OpenRoomDoor(string qName)//вошли в локатор комнаты дома
{
	PlaySound("interface\key.wav");//щелк!
	LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем дверь в комнату
}

void FindMerdokBook(string qName)//нашли архив
{
	PlaySound("interface\important_item.wav");
	if (CheckAttribute(pchar, "questTemp.HWIC.Holl")) AddQuestRecord("Holl_Gambit", "1-39");
	if (CheckAttribute(pchar, "questTemp.HWIC.Eng")) AddQuestRecord("Holl_Gambit", "2-24");
	pchar.GenQuestBox.SentJons_TownCave = true;
	pchar.GenQuestBox.SentJons_TownCave.box2.items.Cipher = 1;//а шифр генерим только счас
	pchar.quest.Merdok_Cipher.win_condition.l1 = "item";
	pchar.quest.Merdok_Cipher.win_condition.l1.item = "Cipher";
	pchar.quest.Merdok_Cipher.function = "FindMerdokCipher";//и сразу прерывание на него
	Box_OnLoadLocation(loadedLocation); // belamour patch 1.2 обновить сундуки в локации
}

void FindMerdokCipher(string qName)//нашли шифр
{
	AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
	AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
	if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
	{
		AddQuestRecord("Holl_Gambit", "1-40");
		AddQuestRecordInfo("Merdok_Archive", "1");
		Achievment_Set("ach_10");
	}
	if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
	{
		AddQuestRecord("Holl_Gambit", "2-26");
		AddQuestRecordInfo("Merdok_Archive", "2");
	}
}

void LucasQuit(string qName)//уберем Лукаса
{
	if (GetCharacterIndex("Lucas") != -1) // 021012
	{
		sld = characterFromId("Lucas");
		sld.lifeday = 0;
	}
	sld = GetCharacter(NPC_GenerateCharacter("HWICBoss", "off_hol_3", "man", "man", 35, HOLLAND, -1, false, "quest"));
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade_17", "pistol5", "bullet", 200);
	sld.Dialog.Filename = "Quest\HollandGambit\HWIC_Office.c"; // 021012
	sld.dialog.currentnode = "HWIC_Boss";
	sld.standUp = true;
	LAi_SetHuberType(sld);
	LAi_SetImmortal(sld, true);
	// belamour legendary edition сменим прописку
	ChangeCharacterAddressGroup(sld, "GVIK_residence", "sit", "sit1");
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");//заменим главу ГВИК
}

///----------------------------Голландский Гамбит, часть 2 - за Англию-------------------------------

//--------------------------------------------1 задание-----------------------------------------------

void HWICSilverConvoyInWorld()//создаем серебряный конвой
{
	string sCapId = "SilverCap";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	pchar.questTemp.HWIC.Eng.SlvQty = 1800 + rand(500);
	int iRank = 13+MOD_SKILL_ENEMY_RATE;
	int iScl = MOD_SKILL_ENEMY_RATE*2+30;
	for (int i = 1; i <= 3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "citiz_41", "man", "man", iRank, HOLLAND, 15, true, "soldier"));
		SetRandomNameToCharacter(sld);
		SetRandomNameToShip(sld);
		switch (i)
		{
			case 1: iTemp = SHIP_LUGGER; break;
			case 2: iTemp = SHIP_GALEON_L; break;
			case 3: iTemp = SHIP_SLOOP; break;
		}
		sld.Ship.Type = GenerateShipExt(iTemp, 1, sld);
		SetBaseShipData(sld);
		SetCaptanModelByEncType(sld, "war");
		int hcrew = GetMaxCrewQuantity(sld);
		// belamour поблажка для легких уровней -->
		if(MOD_SKILL_ENEMY_RATE < 7 && sld.id == "SilverCap2") SetCrewQuantity(sld, hcrew/2);
		else SetCrewQuantityFull(sld);
		// <-- legendary edition
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.Coastal_Captain = true; //не ссорить нации
		sld.lifeDay = 15;
		sld.AnalizeShips = true;
		sld.WatchFort = true; //видеть форты
		sld.skill.Sailing = iScl+rand(10);
		sld.skill.Defence = iScl+rand(10);
		sld.skill.Accuracy = iScl+rand(10);
		sld.skill.Cannons = iScl+rand(10);
		sld.Ship.Crew.Morale = iScl+10;
		sld.Ship.Crew.Exp.Sailors = iScl;
		sld.Ship.Crew.Exp.Cannoners = iScl;
		sld.Ship.Crew.Exp.Soldiers = iScl;
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "SailsDamageUp");
		SetCharacterPerk(sld, "CrewDamageUp");
		SetCharacterPerk(sld, "CriticalShoot");
		if (MOD_SKILL_ENEMY_RATE > 6) SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "AdvancedBattleState");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "ShipSpeedUp");
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		if (i == 2) SetCharacterGoods(sld, GOOD_SILVER, sti(pchar.questTemp.HWIC.Eng.SlvQty));//положить в трюм серебро
		sld.mapEnc.type = "war";
		sld.mapEnc.worldMapShip = "quest_ship";
        sld.mapEnc.Name = StringFromKey("HollandGambit_16");
        Group_AddCharacter(sGroup, sCapId + i);
	}
	Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader("Shore22", "Shore41", sCapId + "1", 15);//запуск энкаунтера
	
	pchar.quest.SilverConvoy_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.SilverConvoy_Abordage.win_condition.l1.character = "SilverCap2";
	pchar.quest.SilverConvoy_Abordage.function = "SilverConvoy_AfterBattle";//взяли на абордаж
	pchar.quest.SilverConvoy_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.SilverConvoy_Sink.win_condition.l1.character = "SilverCap2";
	pchar.quest.SilverConvoy_Sink.function = "SilverConvoy_AfterBattle";//потопили
}

void SilverConvoy_AfterBattle(string qName)//после боя
{
	pchar.GenQuest.DontPartition = true; // отключить дележ
	pchar.quest.HollConvoy_Over.over = "yes";
	pchar.questTemp.HWIC.Eng = "TakeHollConvoy";
	AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
	DoQuestCheckDelay("sea_victory", 1.5);
	ChangeCharacterComplexReputation(pchar, "fame", 1);
	AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
	AddMapQuestMarkCity("SentJons", false);
}

void HollConvoy_Over(string qName)//опоздали или не нашли конвой
{
	pchar.quest.SilverConvoy_Abordage.over = "yes";
	pchar.quest.SilverConvoy_Sink.over = "yes";
	AddQuestRecord("Holl_Gambit", "2-2");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Fail2 = "true";
	DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
}

void HollConvoy_Remove()//удаляем товар и корабль
{
	RemoveCharacterGoods(pchar, GOOD_SILVER, sti(pchar.questTemp.HWIC.Eng.SlvQty));
	//удаляем ост-индца
	if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_GALEON_L)
	{
		pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
		pchar.Ship.name = StringFromKey("HollandGambit_17");
		SetBaseShipData(pchar);
		SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
	}
	else
	{
		for(i = 1; i < COMPANION_MAX; i++)
		{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
			{
				ref chr = GetCharacter(iTemp);
				if(sti(RealShips[sti(chr.ship.type)].basetype) == SHIP_GALEON_L)
				{
					pchar.questTemp.HWIC.Eng.CompanionIndex = chr.Index;
					sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
				}
			}
		}
		RemoveCharacterCompanion(PChar, sld);
		AddPassenger(PChar, sld, false);//удалим тока 1 последний в списке ОИ - пусть будет хоть так
	}
}

//--------------------------------------------2 задание-----------------------------------------------
void EnglandGambit_2_ZadanieStart(string qName)//Квестовая марка
{
	pchar.questTemp.HWIC.Eng = "Start_main";
	AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
	AddMapQuestMarkCity("SentJons", false);
}

void Knippel_GoTown(string qName)//шагаем по городу
{
	sld = characterFromId("Knippel");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "houseSP3", "SentJons_houseSP3", "goto", "goto1", "OpenFleetwoodDoor", -1);
	pchar.quest.Knippel_Inside.win_condition.l1 = "location";
	pchar.quest.Knippel_Inside.win_condition.l1.location = "SentJons_houseSP3";
	pchar.quest.Knippel_Inside.function = "Knippel_InHouse";
}

void Knippel_InHouse(string qName)//заходим в дом
{
	sld = characterFromId("Knippel");
	sld.dialog.currentnode = "InFleetwoodHouse";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GetValckiriaToCharacter(ref rChar)//сажаем на Валькирию
{
	rChar.Ship.Type = GenerateShipExt(SHIP_VALCIRIA, true, rChar);
	rChar.Ship.name = StringFromKey("HollandGambit_8");
	SetBaseShipData(rChar);
	rChar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
	SetCrewQuantityFull(rChar);
	AddCrewMorale(rChar, 100);
	ChangeCrewExp(rChar, "Sailors", 100);
	ChangeCrewExp(rChar, "Cannoners", 100);
	ChangeCrewExp(rChar, "Soldiers", 100);
	SetCharacterGoods(rChar, GOOD_BALLS, 200);
	SetCharacterGoods(rChar, GOOD_GRAPES, 300);
	SetCharacterGoods(rChar, GOOD_KNIPPELS, 300);
	SetCharacterGoods(rChar, GOOD_BOMBS, 500);
	SetCharacterGoods(rChar, GOOD_FOOD, 500);
	SetCharacterGoods(rChar, GOOD_POWDER, 1000);
	SetCharacterGoods(rChar, GOOD_WEAPON, 300);
	SetCharacterGoods(rChar, GOOD_MEDICAMENT, 180);
}

void KnippelToOfficer(string qName)//Книппель идёт офицером
{
	sld = characterFromId("Knippel");
	sld.dialog.currentnode = "Knippel_ToOfficer";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GotoBridgetownOver(string qName)//просрочили выполнить задание
{
	if (pchar.questTemp.HWIC.Eng == "SeekVanBerg")
	{
		sld = characterFromId("JacobBerg");
		sld.lifeday = 0;
		Group_DeleteGroup("Sea_1");
	}
	if(IsEntity(&worldMap)) DoQuestFunctionDelay("MC_GoAway", 0.1);
	else
	{
		pchar.quest.MirageAttack_DieHard.win_condition.l1 = "MapEnter";
	    pchar.quest.MirageAttack_DieHard.function = "MC_GoAway";
	}
	DelMapQuestMarkCity("SentJons");
	DelMapQuestMarkCity("Bridgetown");
	DelLandQuestMark(characterFromId("Fleetwood"));
	DelLandQuestMark(characterFromId("Bridgetown_trader"));
	DelLandQuestMark(characterFromId("Bridgetown_shipyarder"));
	DelLandQuestMark(characterFromId("Bridgetown_Mayor"));
	DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
	DelLandQuestMark(characterFromId("Bridgetown_usurer"));
	DelLandQuestMark(characterFromId("Bridgetown_PortMan"));
	DelLandQuestMark(characterFromId("Bridgetown_Hostess"));
}

void VanBergAttackCheck(string qName)//проверка соблюдения условий
{
	if (sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) FailVanBergInWorld();
	else CreateVanBergInWorld();
}

void FailVanBergInWorld()//не создаем ван Берга, если сильно умные
{
	log_testinfo("ВАН БЕРГ ПОТЕРЯН!!!");
	pchar.questTemp.HWIC.Eng = "VanBergFailInWorld";
	DoQuestFunctionDelay("GotoBridgetownOver", 5.0);
}

void CreateVanBergInWorld()//запускаем Ван Берга на карте
{
	int iRank = 15+MOD_SKILL_ENEMY_RATE;
    string sCapId = "JacobBerg";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	sld = characterFromId("JacobBerg");
	FantomMakeCoolSailor(sld, SHIP_MIRAGE,  StringFromKey("HollandGambit_6"), CANNON_TYPE_CANNON_LBS18, 60, 60, 60);
	// belamour для легких уровней команду в опт -->
	if(MOD_SKILL_ENEMY_RATE < 7) SetCrewQuantity(sld,GetOptCrewQuantity(sld));
	// <-- legendary edition
	FantomMakeCoolFighter(sld, iRank, 60, 60, "blade_14", "pistol1", "bullet", 100);
	GiveItem2Character(sld, "JacobJournal");
	GiveItem2Character(sld, "sand_clock");
	GiveItem2Character(sld, "recipe_totem_13");
	GiveItem2Character(sld, "totem_13");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true; //видеть форты
	sld.Ship.Mode = "pirate";
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 3;//замшелый корпус
	SetShipSailsFromFile(sld, "ships/parus_torn.tga");
	SetSailsColor(sld, 8);//черный рваный парус
	sld.AnalizeShips = true;
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = StringFromKey("HollandGambit_6");
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter(sGroup, sCapId);
    Group_SetGroupCommander(sGroup, sCapId);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateCoolWarrior("Shore37", sCapId, -1);
	
	pchar.quest.JacobAttack_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.JacobAttack_Abordage.win_condition.l1.character = sCapId;
	pchar.quest.JacobAttack_Abordage.function = "Jacob_Attack_Win";//взяли на абордаж
	pchar.quest.JacobAttack_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.JacobAttack_Sink.win_condition.l1.character = sCapId;
	pchar.quest.JacobAttack_Sink.function = "Jacob_Attack_Fail";//потопили, а нельзя было
	pchar.quest.Jacob_Journal.win_condition.l1 = "item";
	pchar.quest.Jacob_Journal.win_condition.l1.item = "JacobJournal";
	pchar.quest.Jacob_Journal.function = "JacobJournalFind";//на журнал Ван Берга
}

void Jacob_Attack_Fail(string qName)//потопили Мираж - провал
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Log_Testinfo("Ван Берг утонул!");
	pchar.quest.JacobAttack_Abordage.over = "yes";
	AddQuestRecord("Holl_Gambit", "2-14");
	pchar.quest.MirageAttack_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.MirageAttack_DieHard.function = "MC_GoAway";
	pchar.questTemp.HWIC.Eng = "MirageFail";
}

void Jacob_Attack_Win(string qName)//после боя - проверяем корабли
{
	DoQuestCheckDelay("sea_victory", 1.5);
	ChangeCharacterComplexReputation(pchar, "fame", 1);
	Log_Testinfo("Ван Берг абордирован!");
	pchar.quest.JacobAttack_Sink.over = "yes";
	int iNum = 0;
	for(i = 0; i < COMPANION_MAX; i++)
	{
		int iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			sld = GetCharacter(iTemp);
			if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE || sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iNum++;
		}
	}
	if (iNum != 2)
	{
		pchar.quest.MirageAttack_DieHard.win_condition.l1 = "MapEnter";
	    pchar.quest.MirageAttack_DieHard.function = "MC_GoAway";
		pchar.questTemp.HWIC.Eng = "MirageFail";//потеряли один из кораблей - провал
	}
	else
	{
		pchar.questTemp.HWIC.Eng = "MirageTake";
		SetFunctionTimerCondition("ToAntiguaMirageOver", 0, 0, 15, false); //ставим таймер
		AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		AddMapQuestMarkCity("SentJons", false);
	}
}

void JacobJournalFind(string qName)//нашли журнал
{
	AddQuestRecord("Holl_Gambit", "2-15");
	AddQuestRecordInfo("JacobVanBerg_Journal", "2");
	AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
}

void ToAntiguaMirageOver(string qName)//если не пошёл на Антигуа с Миражом
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.ToAntiguaMirageOver.over"))
		DeleteAttribute(pchar,"quest.ToAntiguaMirageOver.over");
		NewGameTip(StringFromKey("HollandGambit_3"));
		SetFunctionTimerCondition("ToAntiguaMirageOver", 0, 0, 15, false);
		return;
	}
	DoQuestFunctionDelay("GotoBridgetownOver", 1.0);
}

void Fleetwood_RemoveShip()//удаление корабля
{
	if(sti(RealShips[sti(pchar.ship.type)].basetype) == sti(pchar.questTemp.HWIC.Eng.ShipType))
	{
		pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
		pchar.Ship.name = StringFromKey("HollandGambit_17");
		SetBaseShipData(pchar);
		SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
	}
	else
	{
		for(i = 1; i < COMPANION_MAX; i++)
		{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
			{
				ref sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.questTemp.HWIC.Eng.ShipType))
				{
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
					RemoveCharacterCompanion(PChar, sld);
					AddPassenger(PChar, sld, false);
				}
			}
		}
	}
	Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
	sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
	RemoveCharacterCompanion(pchar, sld);
    DeleteAttribute(sld, "Payment");
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем Книппеля из офицеров
	sld = characterFromId("Knippel");
	ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
}

//--------------------------------------------3 задание-----------------------------------------------

void BoomInGrot(string qName)//взрыв
{
	//if (CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false); // patch-5
	chrDisableReloadToLocation = true;
	CreateLocationParticles("ShipExplode", "box", "box1", 1.0, 0, 0, "boom");
	CreateLocationParticles("blast_inv", "box", "box1", 1.0, 0, 0, "");
	CreateLocationParticles("blast_dirt", "box", "box1", 1.0, 0, 0, "");
	CreateFireParticles("box", "box1");
	LAi_SetActorType(Pchar);
	LAi_ActorAnimation(Pchar, "jump", "SitInGrot", 1.0);
	ChangeCharacterAddressGroup(Pchar, "IslaDeCoche_Grot", "monsters", "monster2");
	Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/3;
	PlaySound("People fight\Death_NPC_08.wav");
}

void StandUpInGrot(string qName)//поднимаемся на ноги
{
	LAi_SetActorType(Pchar);
	LAi_ActorAnimation(Pchar, "Ground_StandUp", "", 3.5);
	CreateLocationParticles("large_smoke", "monsters", "monster1", 1.15, 0, 0, "");
	DoQuestFunctionDelay("CreateChavinavyMonster", 3.5);
}

void CreateChavinavyMonster(string qName)//драка с монстром
{
	LAi_group_Delete("EnemyFight");
	PlaySound("ambient\horror\horror2.wav");
	LAi_SetStayType(Pchar);
	sld = GetCharacter(NPC_GenerateCharacter("Chavinavi", "Chavinavi_1", "man", "skeleton", 20+MOD_SKILL_ENEMY_RATE*3, PIRATE, -1, false, "quest"));
	FantomMakeCoolFighter(sld, 20+MOD_SKILL_ENEMY_RATE*3, 70, 70, "topor_01", "pistol6", "bullet", MOD_SKILL_ENEMY_RATE*60);
	sld.name = StringFromKey("HollandGambit_44");
	sld.lastname = StringFromKey("HollandGambit_45");
	sld.greeting = "";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.monster = true; // признак нежити
	sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/20; // мультифайтер
	ChangeCharacterAddressGroup(sld, "IslaDeCoche_Grot", "monsters", "monster1");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "Ground_sitting", "MonsterStandUp", 1.0);
}

void HeadBarmen_Find(string qName)//нашли бошку, теперь можно выходить
{
	chrDisableReloadToLocation = false;
	AddQuestRecord("Holl_Gambit", "2-19");
	pchar.questTemp.HWIC.Eng = "toAntigua";//назад к Флитвуду
	LAi_LocationDisableOfficersGen("IslaDeCoche_Grot", false);//офицеров пускать
	SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 120, false); // таймер на Калеуче
	DelMapQuestMarkIsland("IslaDeCoche");
	AddMapQuestMarkCity("SentJons", false);
	AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
}

//--------------------------------------------4 задание-----------------------------------------------
void HWICEng_toBarbadosOver(string qName)//опоздали до Барбадоса или Кюрасао
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.HWICEng_toBarbadosOver.over"))
		DeleteAttribute(pchar,"quest.HWICEng_toBarbadosOver.over");
		NewGameTip(StringFromKey("HollandGambit_3"));
		SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);
		return;
	}
	LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
	LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
	LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
	pchar.quest.Knippel_Shore.over = "yes";//снять прерывание
	sld = characterFromId("Knippel");
	sld.lifeday = 0;
	AddQuestRecord("Holl_Gambit", "2-20");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Eng = "end";
	pchar.questTemp.HWIC.Detector = "eng_fail";
	DelMapQuestMarkCity("Bridgetown");
	DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
	DelMapQuestMarkShore("Shore24");
}

void KnippelOnCuracao(string qName)//Книппель на Кюрасао
{
	sld = characterFromId("Knippel");
	ChangeCharacterAddressGroup(sld, "Shore24", "goto", "goto1");
	sld.dialog.currentnode = "OnCuracao";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CreateHollandShorePatrol(string qName)//патруль, драться необязательно
{
	Group_FindOrCreateGroup("HollPatrol_Attack");
	if (Whr_IsDay()) iTemp = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
	else iTemp = GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
    for (int i = 1; i <= 3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("PatrolCap_"+i, "off_hol_"+(rand(5)+1), "man", "man", 20, HOLLAND, 3, true, "hunter"));
		FantomMakeSmallSailor(sld, iTemp, "", CANNON_TYPE_CANNON_LBS16, 40+rand(10), 40+rand(15), 40+rand(15), 50+rand(15), 45+rand(15));
		FantomMakeCoolFighter(sld, 20, 50, 50, "blade_10", "pistol1", "bullet", 70);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
        Group_AddCharacter("HollPatrol_Attack", "PatrolCap_"+i);
    }
    Group_SetGroupCommander("HollPatrol_Attack", "PatrolCap_1");
	Group_SetTaskAttack("HollPatrol_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("HollPatrol_Attack", PLAYER_GROUP);
	Group_SetAddress("HollPatrol_Attack", "Curacao", "", "");
	Group_LockTask("HollPatrol_Attack");
	
	pchar.quest.Merdok_inCave.win_condition.l1 = "location";
	pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
	pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCaveEng";
	LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
	AddMapQuestMarkCity("SentJons", false);
	DelMapQuestMarkShore("Shore24");
}

//---------------------------------------------4 задание---------------------------------------------------
void MerdokInUndergroundCaveEng(string qName)//установим Мердока в подземелье
{
	LAi_group_Delete("EnemyFight");
	LAi_LocationDisableMonGenTimer("SentJons_TownCave", 3); //монстров не генерить
	LocatorReloadEnterDisable("SentJons_TownCave", "reload2", true);//выход сразу закроем
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретим драться
	sld = characterFromId("Merdok");
	sld.greeting = "merdok_3";
	FantomMakeCoolFighter(sld, 20, 60, 60, "blade_14", "pistol3", "bullet", 100);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "MerdokArchive");//архив
	GiveItem2Character(sld, "MC_Letter");//письмо
	ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter3");
	GiveItem2Character(sld, "NPC_Letter");//конверт с картой клада
	ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter3");
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
	ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "item", "berglar1");
	pchar.quest.Merdok_Fight.win_condition.l1 = "locator";
	pchar.quest.Merdok_Fight.win_condition.l1.location = "SentJons_TownCave";
	pchar.quest.Merdok_Fight.win_condition.l1.locator_group = "item";
	pchar.quest.Merdok_Fight.win_condition.l1.locator = "berglar1";
	pchar.quest.Merdok_Fight.function = "MerdokPrepareFight";
	sld = ItemsFromID("MerdokArchive");
	sld.price = 100;
}

void CreateLucasBonanza(string qName)//создадим клад Лукаса и поставим прерывание
{
	chrDisableReloadToLocation = false;//открыть локацию
	DeleteAttribute(pchar, "GenQuest.NoDelBody");
	AddQuestRecordInfo("LetterToMerdok", "1");
	pchar.GenQuestBox.Caiman_Grot = true;
	pchar.GenQuestBox.Caiman_Grot.box1.money = 200000;
	pchar.GenQuestBox.Caiman_Grot.box1.items.Drugstore_keys = 1;//ключ
	pchar.quest.Lucas_Attack.win_condition.l1 = "location";
	pchar.quest.Lucas_Attack.win_condition.l1.location = "Caiman";
	pchar.quest.Lucas_Attack.function = "CreateLucasOnMeifeng";
	pchar.quest.Merdok_Key.win_condition.l1 = "item";
	pchar.quest.Merdok_Key.win_condition.l1.item = "Drugstore_keys";
	pchar.quest.Merdok_Key.function = "FindMerdokKey";//прерывание на ключ
	AddMapQuestMarkIsland("Caiman", false);
	DelMapQuestMarkCity("SentJons");
}

//--------------------------------------5 задание----------------------------------------------------
void CreateLucasOnMeifeng(string qName)//создадим Лукаса на Мейфенг
{
	Island_SetReloadEnableGlobal("Caiman", false);//на остров нельзя
	bQuestDisableMapEnter = true; // patch-4
	Group_FindOrCreateGroup("Lucas_Attack");
	sld = characterFromId("Lucas");
	FantomMakeSmallSailor(sld, SHIP_MAYFANG, StringFromKey("HollandGambit_12"), CANNON_TYPE_CANNON_LBS16, 100, 70, 70, 90, 70);
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade_30", "pistol5", "bullet", 100); // приз - офицерский катлас
    sld.AlwaysEnemy = true;
    sld.DontRansackCaptain = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "spyglass3"); // 160912
	sld.AnalizeShips = true;
	if (GetCompanionQuantity(pchar) > 1) sld.Abordage.Enable = false;//теперь попробуй взять компаньоном
	SetCharacterPerk(sld, "MusketsShoot");
	sld.ship.Crew.Morale = 100;
	sld.Ship.Crew.Exp.Sailors = 100;
	sld.Ship.Crew.Exp.Cannoners = 100;
	sld.Ship.Crew.Exp.Soldiers = 100;
	Group_AddCharacter("Lucas_Attack", "Lucas");
	Group_SetGroupCommander("Lucas_Attack", "Lucas");
	Group_SetTaskAttack("Lucas_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Lucas_Attack", PLAYER_GROUP);
	Group_SetAddress("Lucas_Attack", "Caiman", "", "");
	Group_LockTask("Lucas_Attack");
	pchar.quest.LucasAttack_Abordage.win_condition.l1 = "Group_Death";
	pchar.quest.LucasAttack_Abordage.win_condition.l1.group = "Lucas_Attack";
	pchar.quest.LucasAttack_Abordage.function = "Lucas_Attack_Win";
}

void Lucas_Attack_Win(string qName)//победа
{
	DoQuestCheckDelay("sea_victory", 1.5);
	bQuestDisableMapEnter = false; // patch-4
	Group_DeleteGroup("Lucas_Attack");
	AddQuestRecord("Holl_Gambit", "2-25");
	Island_SetReloadEnableGlobal("Caiman", true);
	RemoveItems(PChar, "NPC_Letter", 1);
	RemoveItems(PChar, "MC_Letter", 1);//подчистим предметы
	AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
	SetFunctionTimerCondition("LucasQuit", 0, 0, 10, false); // 021012
	ChangeCharacterComplexReputation(pchar, "fame", 5);
}

///----------------------------Голландский Гамбит, часть 3 - против всех-------------------------------

//--------------------------------------------1 задание-----------------------------------------------
/*void CreateMapMarksTonzag(string qName)
{
	string sAttr, mQuest;
	
	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			sAttr = colonies[n].id+"_town";
			if(CheckAttribute(&worldMap,"labels."+sAttr+".icon1"))
			{		
				worldMap.labels.(sAttr).icon2 = 6;
				mQuest = "TQM"+sAttr;
				pchar.quest.(mQuest).win_condition.l1           = "location";
				pchar.quest.(mQuest).win_condition.l1.location  = sAttr;
				pchar.quest.(mQuest).function                   = "DelMapTonzagQM";
			}
			else 
			{
				worldMap.labels.(sAttr).majorQM = true;
				worldMap.labels.(sAttr).icon1 = 6;
				mQuest = "TQM"+sAttr;
				pchar.quest.(mQuest).win_condition.l1           = "location";
				pchar.quest.(mQuest).win_condition.l1.location  = sAttr;
				pchar.quest.(mQuest).function                   = "DelMapTonzagQM";
			}
		}
	}
}

void DelMapTonzagQM(string qName) // удалить квестмарк при заходе в локацию
{
	string dCity = strcut(qName, 3 , strlen(qName)-1);
	string sAttr = dCity;
	pchar.quest.(dCity).over = "yes";
	if(CheckAttribute(worldMap,"labels."+sAttr+".icon2"))
	{
		DeleteAttribute(&worldMap,"labels."+sAttr+".icon2");
	}
	else
	{
		if(CheckAttribute(worldMap,"labels."+sAttr+".icon1"))
			DeleteAttribute(&worldMap,"labels."+sAttr+".icon1");
		if(CheckAttribute(worldMap,"labels."+sAttr+".majorQM"))
			DeleteAttribute(&worldMap,"labels."+sAttr+".majorQM");
	}
}

void DelMapTonzagAllQM() // удалить остатки квестмаркеров
{
	string sAttr, mQuest;
	
	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			sAttr = colonies[n].id+"_town";
			mQuest = "TQM"+sAttr;
			if(CheckAttribute(pchar, "quest."+mQuest+".function"))
			{
				if(CheckAttribute(&worldMap,"labels."+sAttr+".icon2"))
				{		
					DeleteAttribute(&worldMap,"labels."+sAttr+".icon2");
					pchar.quest.(mQuest).over = "yes";
				}
				else
				{
					if(CheckAttribute(worldMap,"labels."+sAttr+".icon1"))
						DeleteAttribute(&worldMap,"labels."+sAttr+".icon1");
					if(CheckAttribute(worldMap,"labels."+sAttr+".majorQM"))
						DeleteAttribute(&worldMap,"labels."+sAttr+".majorQM");
					pchar.quest.(mQuest).over = "yes";
				}
			}
		}
	}
	DelLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"));
}*/

void CreateFernandoOnLand(string qName)//испанец в городе
{
	pchar.questTemp.HWIC.Self = "FernandoCreated";
	sld = GetCharacter(NPC_GenerateCharacter("HWICFernando", "Rodriges", "man", "man", 20, SPAIN, 1, false, "quest"));
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_09", "pistol1", "bullet", 50);
	sld.name = StringFromKey("HollandGambit_18");
	sld.lastname = StringFromKey("HollandGambit_19");
	sld.greeting = "hambit_other_5";
	sld.dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Fernando";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "Finger");//палец
	GiveItem2Character(sld, "jewelry7");//голубой янтарь
	GiveItem2Character(sld, "totem_05");//железный пуп
	GiveItem2Character(sld, "amulet_1"); //щит Нгомбо
	sld.money = 18250;
	LAi_SetCitizenType(sld);
	LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Fernando_FightInPort");//сработает на атаку
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	ChangeCharacterAddressGroup(sld, pchar.questTemp.HWIC.Self.SpainCity +"_town", "patrol", "patrol1");
}

void CreateFernandoOnSea(string qName)//испанец на море
{
	pchar.questTemp.HWIC.Self = "FernandoCreated";
	Island_SetReloadEnableGlobal(pchar.questTemp.HWIC.Self.FernandoIslandID, false);//на остров нельзя
	Group_FindOrCreateGroup("Fernando_Attack");
	Group_SetType("Fernando_Attack", "war");
	if(MOD_SKILL_ENEMY_RATE > 8)
	{
		sld = GetCharacter(NPC_GenerateCharacter("HWICFernando", "Rodriges", "man", "man", 20, SPAIN, -1, false, "quest"));
		FantomMakeSmallSailor(sld, SHIP_BRIGANTINE, "", CANNON_TYPE_CANNON_LBS12, 45, 40, 40, 50, 50);
		FantomMakeCoolFighter(sld, 20, 50, 50, "blade_09", "pistol1", "bullet", 150);
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("HWICFernando", "Rodriges", "man", "man", 17, SPAIN, -1, false, "quest"));
		FantomMakeSmallSailor(sld, SHIP_BRIGANTINE, "", CANNON_TYPE_CANNON_LBS12, 38, 34, 34, 43, 43);
		FantomMakeCoolFighter(sld, 17, 43, 43, "blade_09", "pistol1", "bullet", 130);
		SetCrewQuantity(sld,GetOptCrewQuantity(sld));
	}
	sld.name = StringFromKey("HollandGambit_18");
	sld.lastname = StringFromKey("HollandGambit_19");
	sld.greeting = "hambit_other_5";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "Finger");//палец
	GiveItem2Character(sld, "jewelry7");//голубой янтарь
	GiveItem2Character(sld, "totem_05");//железный пуп
	GiveItem2Character(sld, "amulet_1"); //щит Нгомбо
	sld.DontRansackCaptain = true; 
	sld.AnalizeShips = true;
	sld.money = 18250;
	Group_AddCharacter("Fernando_Attack", "HWICFernando");

	Group_SetGroupCommander("Fernando_Attack", "HWICFernando");
	Group_SetTaskRunaway("Fernando_Attack", PLAYER_GROUP);//пусть погоняется
	Group_SetAddress("Fernando_Attack", pchar.questTemp.HWIC.Self.FernandoIslandID, "quest_ships", "Quest_ship_6");
	Group_LockTask("Fernando_Attack");
	
    pchar.quest.HWICFernando_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.HWICFernando_AfterBattle.win_condition.l1.group = "Fernando_Attack";
	pchar.quest.HWICFernando_AfterBattle.function = "Fernando_AfterBattle";
	pchar.quest.HWICFernando_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.HWICFernando_DieHard.function = "Fernando_DieHard";
}

void Fernando_AfterBattle(string qName)//победа
{
	AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
	AddMapQuestMarkCity("bridgetown", false);
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.TargetFernandoOver.over = "yes";
	pchar.quest.HWICFernando_DieHard.over = "yes";
	Island_SetReloadEnableGlobal(pchar.questTemp.HWIC.Self.FernandoIslandID, true);
	Group_DeleteGroup("Fernando_Attack");
	pchar.questTemp.HWIC.Self = "FernandoDie";
	AddQuestRecord("Holl_Gambit", "3-6");
	AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
}

void Fernando_DieHard(string qName)//ушли или не догнали
{
	if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
	{
		AddMapQuestMarkCity("Villemstad", false);
		AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
	}
	if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
	{
		AddMapQuestMarkCity("SentJons", false);
		AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
	}
	pchar.quest.TargetFernandoOver.over = "yes";
	pchar.quest.HWICFernando_AfterBattle.over = "yes";
	Island_SetReloadEnableGlobal(pchar.questTemp.HWIC.Self.FernandoIslandID, true);
	Group_DeleteGroup("Fernando_Attack");
	sld = characterFromId("HWICFernando");
	sld.lifeday = 0;
	AddQuestRecord("Holl_Gambit", "3-7");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Fail3 = "true";
	DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к иному варианту
}

void Fernando_died(string qName)//клиент готов
{
	chrDisableReloadToLocation = false;
	pchar.questTemp.HWIC.Self = "FernandoDie";
	pchar.quest.TargetFernandoOver.over = "yes";
	AddQuestRecord("Holl_Gambit", "3-5");
	AddComplexSelfExpToScill(50, 50, 50, 50);
}

void TargetFernandoOver(string qName)//опоздали
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.TargetFernandoOver.over"))
		DeleteAttribute(pchar,"quest.TargetFernandoOver.over");
		NewGameTip(StringFromKey("HollandGambit_3"));
		SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false);
		return;
	}
	//DelMapTonzagAllQM();
	if (pchar.questTemp.HWIC.Self == "KillFernando") pchar.quest.HWIC_Fernando.over = "yes";
	if (pchar.questTemp.HWIC.Self == "FernandoCreated")
	{
		sld = characterFromId("HWICFernando");
		LAi_SetImmortal(sld, true);
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
	}
	AddQuestRecord("Holl_Gambit", "3-4");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Fail3 = "true";
	DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к иному варианту
	if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
	{
		AddMapQuestMarkCity("Villemstad", false);
		AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
	}
	if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
	{
		AddMapQuestMarkCity("SentJons", false);
		AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
	}
}

//--------------------------------------------2 задание----------------------------------------------
void CreateFleetwoodSoldiers()//солдаты в доме Флитвуда
{
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Fleetwood_sold_"+i, "sold_eng_"+i, "man", "man", 35, ENGLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 35, 80, 80, "blade_11", "pistol6", "bullet", 150);//подразделение альфа
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		TakeNItems(sld, "potion2", 2);
		LAi_SetWarriorType(sld);
		if (i == 1)
		{
			LAi_SetHP(sld, 500, 500);
			LAi_warrior_DialogEnable(sld, true);
			sld.greeting = "soldier";
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Fleetwood_soldier";
		}
		ChangeCharacterAddressGroup(sld, "SentJons_houseSP3", "goto", "goto"+i);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	}
}

void Fleetwood_Soldier(string qName)//get out!
{
	sld = characterFromId("Fleetwood_sold_1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void FleetwoodJournalOver(string qName)//провалили по срокам
{
	pchar.quest.Fleetwood_Journal.over = "yes";//снять прерывание на ключ, а вот солдат в доме оставлю
	RemoveItems(PChar, "key3", 1);
	AddQuestRecord("Holl_Gambit", "3-11");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Detector = "self_fail";
	DelMapQuestMarkCity("SentJons");
	AddMapQuestMarkCity("FortFrance", false);
	AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
}

void FleetwoodHouseEnter(string qName)//открываем дверь
{
	LAi_LocationFightDisable(&Locations[FindLocation("SentJons_houseSP3")], false);//можно драться
	pchar.quest.Fleetwood_Soldier.over = "yes";
	PlaySound("interface\key.wav");//щелк!
	pchar.questTemp.HWIC.Self.Theft = "true";//атрибут вторжения
	for (i=2; i<=4; i++)
	{
		sld = characterFromId("Fleetwood_sold_"+i);
		sld.lifeday = 0;//уберем лишних солдеров
	}
	sld = characterFromId("Fleetwood_sold_1");
	LAi_SetStayType(sld);
	LAi_SetHP(sld, 10, 500);
	sld.dialog.currentnode = "Theft_soldier";
	GiveItem2Character(sld, "key2");
	ChangeCharacterAddressGroup(sld, "SentJons_houseSP3", "barmen", "bar2");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	RemoveItems(PChar, "key3", 1);
	DoQuestReloadToLocation("SentJons_houseSP3", "reload", "reload1", "");
	pchar.quest.Fleetwood_Room.win_condition.l1 = "item";
	pchar.quest.Fleetwood_Room.win_condition.l1.item = "key2";
	pchar.quest.Fleetwood_Room.win_condition.l2 = "locator";
	pchar.quest.Fleetwood_Room.win_condition.l2.location = "SentJons_houseSP3";
	pchar.quest.Fleetwood_Room.win_condition.l2.locator_group = "reload";
	pchar.quest.Fleetwood_Room.win_condition.l2.locator = "reload2";
	pchar.quest.Fleetwood_Room.function = "FindRoomKey";
}

void FindRoomKey(string qName)//открываем дверь
{
	PlaySound("interface\key.wav");//щелк!
	LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", false);//комнату откроем
	pchar.quest.Fleetwood_Book.win_condition.l1 = "item";
	pchar.quest.Fleetwood_Book.win_condition.l1.item = "FleetwoodJournal";
	pchar.quest.Fleetwood_Book.win_condition.l2 = "location";
	pchar.quest.Fleetwood_Book.win_condition.l2.location = "SentJons_houseSP3";
	pchar.quest.Fleetwood_Book.function = "FirstFloorFight";
}

void FirstFloorFight(string qName)//драка в доме
{
	pchar.quest.FleetwoodJournalOver.over = "yes"; //снять таймер
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запрет драки до разговора
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Attack_sold_"+i, "sold_eng_"+i, "man", "man", 20, ENGLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 20, 50, 50, "blade_10", "pistol6", "bullet", 50);//подразделение альфа
		LAi_SetWarriorType(sld);
		if (i == 4)
		{
			LAi_warrior_DialogEnable(sld, true);
			sld.greeting = "soldier_arest";
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Attack_soldier";
		}
		ChangeCharacterAddressGroup(sld, "SentJons_houseSP3", "goto", "goto"+i);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	}
	sld = characterFromId("Attack_sold_4");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void SJ_StreetFight(string qName)//драка на улице - Тонзаг в помощь
{
	chrDisableReloadToLocation = true;
	pchar.GenQuest.Notsearchbody = true;//запрет обыска трупов
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Attack2_sold_"+i, "sold_eng_"+i, "man", "man", 20, ENGLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 20, 60, 60, "blade_19", "pistol4", "bullet", 60);//подразделение альфа
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = characterFromId("Tonzag");
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "SentJons_town", "patrol", "patrol10");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "MC_deafenning");
}

void InMerdokHouse(string qName)//телепорт в аптеку
{
	DoQuestReloadToLocation("SentJons_HouseF3_Room2", "barmen", "bar1", "MerdokTalkToMC");
	RemoveItems(PChar, "key2", 1);
	RemoveItems(PChar, "FleetwoodJournal", 1);
	DeleteAttribute(pchar, "GenQuest.Notsearchbody");//снять запрет обыска трупов
	sld = characterFromId("Merdok");
	sld.greeting = "";
}

void TonzagMeeting(string qName)//встреча друзей
{
	sld = characterFromId("Tonzag");
	sld.Dialog.Filename = "Quest\HollandGambit\Tonzag.c";
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "SentJons_town", "patrol", "patrol14");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

//-----------------------------------------3 задание----------------------------------------------------
void Wait_FleetwoodQM(string qName)
{
	AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
	AddMapQuestMarkCity("SentJons", false);
}

void Wait_FleetwoodOver(string qName)//не пришел за 12 дней, хотя срок был - неделя
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Wait_FleetwoodOver.over"))
			DeleteAttribute(pchar,"quest.Wait_FleetwoodOver.over");
		NewGameTip(StringFromKey("HollandGambit_3"));
		SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);
		return;
	}
	pchar.questTemp.HWIC.Self = "HWICSelf_fail";
	pchar.quest.Wait_FleetwoodQM.over = "yes";
}

void HuntKnippelOver(string qName)//опоздал за Чарли
{
	pchar.quest.Hunt_Knippel.over = "yes"; //снять прерывание
	AddQuestRecord("Holl_Gambit", "3-17");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
	DelMapQuestMarkIsland("Curacao");
}

void CreateKnippelShip(string qName)//создаем бригантину Чарли
{
	pchar.quest.HuntKnippelOver.over = "yes";//снять таймер
	Island_SetReloadEnableGlobal("Curacao", false);//на остров нельзя
	Group_FindOrCreateGroup("Knippel_Attack");
	Group_SetType("Knippel_Attack", "war");
	sld = characterFromId("Knippel");
	sld.nation = HOLLAND;
	FantomMakeSmallSailor(sld, SHIP_BRIGANTINE, StringFromKey("HollandGambit_20"), CANNON_TYPE_CULVERINE_LBS8, 45, 90, 85, 30, 80);
	// belamour для легких уровней половина команды -->
	if(MOD_SKILL_ENEMY_RATE < 7) SetCrewQuantity(sld, sti(GetMaxCrewQuantity(sld))/2);
	// <-- legendary edition		 
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.DontRansackCaptain = true; 
	sld.AnalizeShips = true;
	sld.Alwaysenemy = true;
	sld.Coastal_Captain = true;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Knippel_Attack", "Knippel");
	Group_SetGroupCommander("Knippel_Attack", "Knippel");
	Group_SetTaskRunaway("Knippel_Attack", PLAYER_GROUP);//пусть погоняется
	Group_SetAddress("Knippel_Attack", "Curacao", "", "");
	Group_SetPursuitGroup("Knippel_Attack", PLAYER_GROUP);
	Group_LockTask("Knippel_Attack");
	
    pchar.quest.Knippel_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Knippel_AfterBattle.win_condition.l1.group = "Knippel_Attack";
	pchar.quest.Knippel_AfterBattle.function = "Knippel_AfterBattle";
	pchar.quest.Knippel_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.Knippel_DieHard.function = "Knippel_DieHard";
}

void Knippel_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Island_SetReloadEnableGlobal("Curacao", true);
	if(pchar.questTemp.HWIC.Self != "KnippelPrisoner")
	{
	    pchar.quest.Knippel_DieHard.over = "yes";
		Group_DeleteGroup("Knippel_Attack");
		AddQuestRecord("Holl_Gambit", "3-18");
		CloseQuestHeader("Holl_Gambit");
		pchar.questTemp.HWIC.Self = "end";
		pchar.questTemp.HWIC.Detector = "self_fail";
		Log_TestInfo("КНИППЕЛЬ УТОНУЛ!");
	}
	else
	{
		Log_TestInfo("КНИППЕЛЬ В ТРЮМЕ!");
		AddComplexSeaExpToScill(100, 100, 100, 200, 100, 100, 0);
		AddComplexSelfExpToScill(60, 60, 60, 60);
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ref chr = GetCharacter(NPC_GenerateCharacter("KnippelClone", "Kneepel", "man", "man_B", 25, ENGLAND, -1, false, "quest"));
		chr.name = StringFromKey("HollandGambit_21");
		chr.lastname = StringFromKey("HollandGambit_22");
		LAi_SetGroundSitType(chr);
		ChangeCharacterAddressGroup(chr, "My_Deck", "rld", "aloc3");
		chr.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		chr.Dialog.CurrentNode = "Knippel_prisoner";
		for (i=1; i<=2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Sailor_"+i, "citiz_"+(30+i), "man", "man", 25, pchar.nation, -1, false, "soldier"));
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			if (i == 1) ChangeCharacterAddressGroup(sld, "My_Deck", "rld", "aloc2");
			else ChangeCharacterAddressGroup(sld, "My_Deck", "rld", "loc3");
		}
		sld = GetCharacter(NPC_GenerateCharacter("Sailor_3", "citiz_36", "man", "man", 25, pchar.nation, -1, false, "soldier"));
		sld.name 	= StringFromKey("HollandGambit_23");
		sld.lastname = StringFromKey("HollandGambit_24");
		sld.greeting = "hambit_other_4";
		sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
		sld.dialog.currentnode = "Sailor_deck";
		ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Knippel_DieHard(string qName)//ушёл на карту
{
	Island_SetReloadEnableGlobal("Curacao", true);
	pchar.quest.Knippel_AfterBattle.over = "yes"; //снять прерывание
	Group_DeleteGroup("Knippel_Attack");
	AddQuestRecord("Holl_Gambit", "3-19");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
	sld = characterFromId("Knippel");	
	sld.lifeday = 0; 
}

void AbigileGoToShipOver(string qName)//просрочили забрать Аби
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.AbigileGoToShipOver.over"))
			DeleteAttribute(pchar,"quest.AbigileGoToShipOver.over");
		NewGameTip(StringFromKey("HollandGambit_3"));
		SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);
		return;
	}
	pchar.quest.Abigile_Kidnap.over = "yes"; //снять прерывание
	pchar.questTemp.HWIC.Self = "AbigileNextDayOver";
	sld = characterFromId("Abigile");
	sld.lifeday = 0;
}

void AbigileGoToShip(string qName)//забираем Аби
{
	pchar.questTemp.HWIC.Self = "AbigileNextDay";
	sld = characterFromId("Abigile");
	ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

//удаление Книппеля, Лонгвэя и Абигайль, если геймер затянул прохождение
void RemoveAbigileOver(string qName)//удаление Абигайль
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.RemoveAbigileOver.over"))
			DeleteAttribute(pchar,"quest.RemoveAbigileOver.over");
		NewGameTip(StringFromKey("HollandGambit_3"));
		SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);
		return;
	}
	pchar.quest.Abigile_died.over = "yes";//снять прерывание на убийство Аби
	sld = characterFromId("Abigile");
	RemovePassenger(Pchar, sld);
	sld.lifeday = 0;
	AddQuestRecord("Holl_Gambit", "3-67");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
	Log_Info(StringFromKey("HollandGambit_25"));
	DelLandQuestMark(characterFromId("merdok"));
	DelMapQuestMarkCity("SentJons");
}

void RemoveKnippelOver(string qName)//удаление Книппеля (клона в трюме)
{
	sld = characterFromId("KnippelClone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0;
	for (i=1; i<=3; i++)//уберем охрану
	{
		sld = characterFromId("Sailor_"+i);
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	AddQuestRecord("Holl_Gambit", "3-68");
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
	Log_Info(StringFromKey("HollandGambit_26"));
}

void RemoveLongwayOver(string qName)//удаление Лонгвэя (клона в трюме)
{
	sld = characterFromId("LongwayClone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0;
	for (i=1; i<=3; i++)//уберем охрану
	{
		sld = characterFromId("Sailor_"+i);
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	if (pchar.questTemp.HWIC.Self == "GotoGuadeloupe")
	{
		AddQuestRecord("Holl_Gambit", "3-71");
		Log_Info(StringFromKey("HollandGambit_27"));
		DelMapQuestMarkShore("Shore31");
	}
	else
	{
		AddQuestRecord("Holl_Gambit", "3-70");
		Log_Info(StringFromKey("HollandGambit_28"));
	}
	if (CheckShipTypeInSquadron(SHIP_MAYFANG) > 0)//если есть шебека - отберем
	{
		pchar.quest.Remove_Meifeng.win_condition.l1 = "Location_Type";
		pchar.quest.Remove_Meifeng.win_condition.l1.location_type = "town";
		pchar.quest.Remove_Meifeng.function = "RemoveMeifeng";
	}
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
}

void AbigileDied(string qName)//для отморозков, решивших пострелять по Аби
{
	sld = characterFromId("Abigile");
	sld.lifeday = 0;
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
	ChangeCharacterComplexReputation(pchar, "nobility", -30);
	ChangeCharacterHunterScore(PChar, "holhunter", 50);
	DelLandQuestMark(characterFromId("merdok"));
	DelMapQuestMarkCity("SentJons");
}

//-------------------------------------------4 задание------------------------------------------------
void MC_writeLetterGo(string qName)//пишем письмо
{
	SetLaunchFrameFormParam(StringFromKey("HollandGambit_29"), "MC_writeLetterDone", 0, 5);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 1, 10); //крутим время
	RecalculateJumpTable();
}

void CreateDrunckardInTavern()//создаем пьянтоса
{
	pchar.questTemp.HWIC.Self = "LetterToDrunkard";
	FreeSitLocator("Sentjons_tavern", "sit_front1");
	sld = GetCharacter(NPC_GenerateCharacter("Drunkard", "panhandler_6", "man", "man", 10, ENGLAND, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 10, 10, "topor_1", "pistol3", "bullet", 50);
	RemoveAllCharacterItems(sld, true);
	sld.name = StringFromKey("HollandGambit_30");
	sld.lastname = StringFromKey("HollandGambit_31");
	sld.dialog.FileName = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Drunkard";
	sld.greeting = "poorman_male";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);
	LAi_SetLoginTime(sld, 16.0, 21.0);
	ChangeCharacterAddressGroup(sld, "Sentjons_tavern", "sit", "sit_front1");
	AddLandQuestMark(sld, "questmarkmain");
}

void DrunkardReturnToTavern(string qName)//пьянтос идёт назад в таверну
{
	sld = characterFromId("Drunkard");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "SentJons_town", "reload", "houseSP3");
	LAi_ActorGoToLocation(sld, "reload", "reload4_back", "SentJons_tavern", "reload", "reload1", "DrunkardSitInTavern", -1);	
}

void Fleetwood_meetingOver(string qName)//не пришли на встречу вовремя
{
	pchar.quest.Fleetwood_meetingShore.over = "yes";
	pchar.quest.Abigile_died.over = "yes";//снять прерывание на убийство Аби
	AddQuestRecord("Holl_Gambit", "3-29");
	sld = characterFromId("Abigile");
	sld.lifeday = 0;//убираем Аби
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
	CloseQuestHeader("Holl_Gambit");
	DelMapQuestMarkShore("Shore57");
}

void InTerksShore(string qName)//пришли на Теркс в бухту
{
	if (pchar.location.from_sea == "Shore57")
	{
		DelMapQuestMarkShore("Shore57");
		pchar.quest.Fleetwood_meetingOver.over = "yes";//снять таймер
		SetFunctionTimerCondition("Fleetwood_ShoreOver", 0, 0, 5, false);//новый таймер, чтобы не занимался ерундой
		AddQuestRecord("Holl_Gambit", "3-33");
		for (i=1; i<=7; i++)//организуем засаду
		{
			sld = GetCharacter(NPC_GenerateCharacter("OwrSailor_"+i, "citiz_"+(30+i), "man", "man", 20, sti(pchar.nation), -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 20, 40, 40, "blade_14", "pistol1", "bullet", 70);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			if (i == 1 || i == 2 || i == 3) ChangeCharacterAddressGroup(sld, "Shore56", "smugglers", "smuggler0"+i);
			if (i == 4 || i == 5) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto"+(8+i));
			if (i == 6 || i == 7) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto"+(13-i));
		}
		pchar.quest.Fleetwood_Login.win_condition.l1 = "Timer";
		pchar.quest.Fleetwood_Login.win_condition.l1.date.hour  = sti(GetTime()+rand(6));
		pchar.quest.Fleetwood_Login.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
		pchar.quest.Fleetwood_Login.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Fleetwood_Login.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
		pchar.quest.Fleetwood_Login.win_condition.l2 = "location";
		pchar.quest.Fleetwood_Login.win_condition.l2.location = "Shore56";
		pchar.quest.Fleetwood_Login.function = "CreateFleetwoodInShore";
	}
	else
	{
		pchar.questTemp.HWICMC = "Fleetwood";
		DoQuestCheckDelay("TalkSelf_Quest", 1.0);
	}
}

void Fleetwood_repeatShore(string qName)//если пришли не туда или тупые сильно
{
	pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
	pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
	pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";//дубль два(три, четыре...)
}

void Fleetwood_ShoreOver(string qName)//если страдали фигней, а не делом занимались, для особо упоротых
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Fleetwood_ShoreOver.over"))
			DeleteAttribute(pchar,"quest.Fleetwood_ShoreOver.over");
		NewGameTip(StringFromKey("HollandGambit_3"));
		SetFunctionTimerCondition("Fleetwood_ShoreOver", 0, 0, 15, false);
		return;
	}
	pchar.quest.Fleetwood_Login.over = "yes";
	pchar.quest.Abigile_died.over = "yes";//снять прерывание на убийство Аби
	AddQuestRecord("Holl_Gambit", "3-30");
	sld = characterFromId("Abigile");
	sld.lifeday = 0;//убираем Аби
	for (i=1; i<=7; i++)
	{
		sld = characterFromId("OwrSailor_"+i);
		sld.lifeday = 0;//убираем засаду
	}
	pchar.questTemp.HWIC.Self = "end";
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Detector = "self_fail";
}

void CreateFleetwoodInShore(string qName)//явился Флитвуд
{
	if (pchar.location.from_sea == "Shore57")
	{
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретим драться
		chrDisableReloadToLocation = true;//закрыть локацию
		ref chr = characterFromId("Fleetwood");
		FantomMakeCoolFighter(chr, 25, 70, 70, "blade_14", "pistol3", "bullet", 100);//крутой парень
		chr.SaveItemsForDead = true;
		chr.DontClearDead = true;
		chr.dialog.currentnode = "InTerksShore";
		chr.greeting = "fleetwood_3";
		LAi_SetStayType(chr);
		ChangeCharacterAddressGroup(chr, "Shore56", "goto", "goto10");
		AddLandQuestMark(chr, "questmarkmain");
		for (i=1; i<=3; i++)//офицеры
		{
			sld = GetCharacter(NPC_GenerateCharacter("FlOfficer_"+i, "sold_eng_"+i, "man", "man", 20, ENGLAND, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, 20, 40, 40, "blade_13", "pistol3", "bullet", 70);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Shore56", "officers", "sea_"+i);
		}
	}
}

void CreateValkiriaBrig(string qName)//создаем Валькирию без Флитвуда
{
	Island_SetReloadEnableGlobal("Terks", false);//на остров нельзя
	bQuestDisableMapEnter = true;//на карту тоже
	Group_FindOrCreateGroup("Val_Attack");
	Group_SetType("Val_Attack", "war");
	sld = GetCharacter(NPC_GenerateCharacter("ValCap", "off_eng_4", "man", "man", 25, ENGLAND, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_VALCIRIA, StringFromKey("HollandGambit_8"), CANNON_TYPE_CANNON_LBS16, 50, 60, 60, 60, 60);
	sld.DontRansackCaptain = true; 
	sld.AnalizeShips = true;
	sld.Alwaysenemy = true;
	sld.Coastal_Captain = true;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Val_Attack", "ValCap");
	Group_SetGroupCommander("Val_Attack", "ValCap");
	Group_SetTaskAttack("Val_Attack", PLAYER_GROUP);
	Group_SetAddress("Val_Attack", "Terks", "quest_ships", "quest_ship_1");
	Group_LockTask("Val_Attack");
	
    pchar.quest.Val_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Val_AfterBattle.win_condition.l1.group = "Val_Attack";
	pchar.quest.Val_AfterBattle.function = "Valkiria_AfterBattle";
}

void Valkiria_AfterBattle(string qName)//после боя - неважно, потопил или взял
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Val_Attack");
	Island_SetReloadEnableGlobal("Terks", true);
	bQuestDisableMapEnter = false;
	AddQuestRecord("Holl_Gambit", "3-32");
	pchar.questTemp.HWIC.Self = "FleetwoodDied";
	AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
	AddMapQuestMarkCity("SentJons", false);
}

void TonzagMeetingInDange(string qName)//Тонзаг в подземелье
{
	sld = characterFromId("Tonzag");
	ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "item", "berglar1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

//----------------------------------------------5 задание---------------------------------------------------
void HWICCureerOnMapOver(string qName)//не перехватили курьера
{
	pchar.quest.HWICCureer_AfterBattle.over = "yes"; //снять прерывание
	pchar.quest.Abigile_died.over = "yes";//снять прерывание на убийство Аби
	Group_DeleteGroup("Sea_CureerCap1");
	AddQuestRecord("Holl_Gambit", "3-37");
	sld = characterFromId("Abigile");
	sld.lifeday = 0;//убираем Аби
	RemoveItems(PChar, "MC_Letter", 1);
	pchar.questTemp.HWIC.Self = "end";
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Detector = "self_fail";
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void CreateHWICCureerOnMap(string qName)//энкаунтер курьера на карте
{
    string sGroup = "Sea_CureerCap1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	sld = GetCharacter(NPC_GenerateCharacter("CureerCap", "citiz_41", "man", "man", 20, HOLLAND, 15, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_BRIGANTINE, StringFromKey("HollandGambit_33"), CANNON_TYPE_CANNON_LBS12, 50, 45, 45, 50, 60);
	// belamour для легких уровней команду в опт -->
	if(MOD_SKILL_ENEMY_RATE < 7) SetCrewQuantity(sld,GetOptCrewQuantity(sld));
	// <-- legendary edition			 
	SetCaptanModelByEncType(sld, "war");
	SetRandomNameToCharacter(sld);
	LAi_SetHP(sld, 100+MOD_SKILL_ENEMY_RATE*30, 100+MOD_SKILL_ENEMY_RATE*30);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Coastal_Captain = true; //не ссорить нации
	sld.Ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*10;
	sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*10;
	sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*10;
	sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*10;
	UpgradeShipParameter(sld, "SpeedRate");
	UpgradeShipParameter(sld, "Capacity");
	UpgradeShipParameter(sld, "WindAgainstSpeed");
	UpgradeShipParameter(sld, "TurnRate");
	if (MOD_SKILL_ENEMY_RATE > 4) TakeNItems(sld, "potion2", 3);
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
	sld.mapEnc.Name = StringFromKey("HollandGambit_32");
	Group_AddCharacter(sGroup, "CureerCap");
	Group_SetGroupCommander(sGroup, "CureerCap");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Map_CreateTrader("Shore41", "Shore39", "CureerCap", 16);//запуск энкаунтера - до Мартиники, до Кюрасао нельзя
	pchar.quest.HWICCureer_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.HWICCureer_AfterBattle.win_condition.l1.group = sGroup;
	pchar.quest.HWICCureer_AfterBattle.function = "HWICCureer_AfterBattle";
	
	// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
    pchar.GenQuest.SeaHunter2Pause = true;
    SeaHunter_Delete();
}

void HWICCureer_AfterBattle(string qName)//утопили курьера
{
	pchar.quest.HWICCureerOnMapOver.over = "yes";
	pchar.quest.Abigile_died.over = "yes";//снять прерывание на убийство Аби
	Group_DeleteGroup("Sea_CureerCap1");
	Log_testInfo("КУРЬЕР УТОНУЛ!");
	AddQuestRecord("Holl_Gambit", "3-38");
	sld = characterFromId("Abigile");
	sld.lifeday = 0;//убираем Аби
	RemoveItems(PChar, "MC_Letter", 1);
	pchar.questTemp.HWIC.Self = "end";
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Detector = "self_fail";
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void CuracaoExploring(string qName)//на Кюрасао
{
	//Мейфенг с китайцем в порту
	AddQuestRecord("Holl_Gambit", "3-40");
	Group_FindOrCreateGroup("Meifeng_Empty");
	Group_SetType("Meifeng_Empty", "pirate");//тип группы
	sld = characterFromId("Longway");
	FantomMakeSmallSailor(sld, SHIP_MAYFANG, StringFromKey("HollandGambit_12"), CANNON_TYPE_CANNON_LBS16, 50, 65, 65, 50, 90);
	Character_SetAbordageEnable(sld, false);//нельзя абордировать
	sld.AnalizeShips = true;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Meifeng_Empty", "Longway");
	Group_SetGroupCommander("Meifeng_Empty", "Longway");
	Group_SetAddress("Meifeng_Empty", "Curacao", "Islandships1", "ship_2");
	pchar.quest.Meifeng_fail.win_condition.l1 = "NPC_Death";
	pchar.quest.Meifeng_fail.win_condition.l1.character = "Longway";
	pchar.quest.Meifeng_fail.function = "HollGambitSelf_failed";//для особо умных
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
	CreatMarkInTavernHWIC();
	//подготовим Виллемстад к посещению ГГ
	LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
	LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
	sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
	LAi_SetStayType(sld);
	sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "MatiasBek";
	ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");//Бека - в тюрьму
	sld = characterFromId("Lucas");
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");//Лукаса - на место губера
	sld = &characters[GetCharacterbyLocation("Villemstad_town", "soldiers", "soldier1")];
    sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "QuestGuard";
    sld.protector = true;
    sld.protector.CheckAlways = 1;//всегда проверять
    LAi_RemoveLoginTime(sld);
    LoginCharacter(sld, "Villemstad_town");//квестовый стражник
}

void CreatMarkInTavernHWIC()
{
	SetFunctionLocationCondition("CreatMarkInTavernHWIC_Next", "Villemstad_tavern", false);
}
void CreatMarkInTavernHWIC_Next(string qName)
{
	DoQuestFunctionDelay("CreatMarkInTavernHWIC_Delay", 1.0);
}

void CreatMarkInTavernHWIC_Delay(string qName)
{
	for(int n=0; n<MAX_CHARACTERS; n++) 
	{
		sld = GetCharacter(n);
		if(CheckAttribute(sld, "dialog.filename"))
		{
			if(sld.dialog.filename == "Habitue_dialog.c")
			{
				if(CheckAttribute(sld, "greeting") && sld.greeting == "habitue")
				{
					if(CheckAttribute(sld, "Default.ToLocator"))
					{
						AddLandQuestMark(sld, "questmarkmain");
						//Log_testinfo("Добавили маркер ");
					}
				}
			}
		}
	}
}

void DelMarkInTavernHWIC()
{
	for(int n=0; n<MAX_CHARACTERS; n++) 
	{
		sld = GetCharacter(n);
		if(CheckAttribute(sld, "dialog.filename"))
		{
			if(sld.dialog.filename == "Habitue_dialog.c")
			{
				if(CheckAttribute(sld, "greeting") && sld.greeting == "habitue")
				{
					if(CheckAttribute(sld, "Default.ToLocator"))
					{
						DelLandQuestMark(sld);
					}
				}
			}
		}
	}
}

void HollGambitSelf_failed(string qName)//если у кого-то хватит наглости
{
	if (pchar.questTemp.HWIC.Self == "LetterToLucasSent")
	{
		Group_DeleteGroup("Meifeng_Empty");
		AddQuestRecord("Holl_Gambit", "3-41");
		ChangeCharacterHunterScore(PChar, "holhunter", 100); //начислить НЗГ
	}
	if (pchar.questTemp.HWIC.Self == "MeetingStivesant")
	{
		Group_DeleteGroup("Stivesant_Halleon");
		AddQuestRecord("Holl_Gambit", "3-42");
		ChangeCharacterHunterScore(PChar, "holhunter", 100); //начислить НЗГ
	}
	if (pchar.questTemp.HWIC.Self == "WayWithStivesant")
	{
		Group_DeleteGroup("Stivesant_Halleon");
		AddQuestRecord("Holl_Gambit", "3-43");
	}
	pchar.quest.Abigile_died.over = "yes";//снять прерывание на убийство Аби
	pchar.quest.CreatMarkInTavernHWIC_Next.over = "yes";
	sld = characterFromId("Abigile");
	sld.lifeday = 0;//убираем Аби
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
}

void CreateMeifengOnMap(string qName)//энкаунтер Мейфенг на карте
{
    string sGroup = "Sea_Meifeng1";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "pirate");//тип группы
	sld = characterFromId("Longway");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Alwaysenemy = true; // 260912
	sld.Coastal_Captain = true;
	sld.Ship.Mode = "pirate";
	Character_SetAbordageEnable(sld, true);//можно абордировать
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "'"+StringFromKey("HollandGambit_12")+"'";
	Group_AddCharacter(sGroup, "Longway");
	
	Group_SetGroupCommander(sGroup, "Longway");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader("Shore22", "Shore39", "Longway", 10);//запуск энкаунтера - до Мартиники
	
	pchar.quest.Meifeng_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Meifeng_AfterBattle.win_condition.l1.group = sGroup;
	pchar.quest.Meifeng_AfterBattle.function = "Meifeng_AfterBattle";
}

void Meifeng_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
	if (CheckShipTypeInSquadron(SHIP_MAYFANG) > 0) pchar.questTemp.HWIC.TakeQuestShip = "true";
	if(pchar.questTemp.HWIC.Self != "LongwayPrisoner")
	{
		Group_DeleteGroup("Sea_Meifeng1");
		AddQuestRecord("Holl_Gambit", "3-46");
		CloseQuestHeader("Holl_Gambit");
		pchar.quest.Abigile_died.over = "yes";//снять прерывание на убийство Аби
		sld = characterFromId("Abigile");
		sld.lifeday = 0;
		sld = characterFromId("Longway");
		sld.lifeday = 0;
		pchar.questTemp.HWIC.Self = "end";
		pchar.questTemp.HWIC.Detector = "self_fail";
		Log_TestInfo("ЛОНГВЭЙ УТОНУЛ!");
		//проверим на захват компаньоном
		if (CheckShipTypeInSquadron(SHIP_MAYFANG) > 0)
		{
			pchar.quest.Remove_Meifeng.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Meifeng.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Meifeng.function = "RemoveMeifeng";
		}
	}
	else
	{
		pchar.GenQuest.DontPartition = true; // отключить дележ
		Log_TestInfo("ЛОНГВЭЙ В ТРЮМЕ!");
		AddComplexSeaExpToScill(150, 150, 150, 200, 150, 150, 0);
		AddComplexSelfExpToScill(60, 60, 60, 60);
		ref chr = GetCharacter(NPC_GenerateCharacter("LongwayClone", "Longway", "man", "man", 20, HOLLAND, -1, false, "quest"));
		chr.name = StringFromKey("HollandGambit_34");
		chr.lastname = StringFromKey("HollandGambit_35");
		LAi_SetStayType(chr);
		ChangeCharacterAddressGroup(chr, "My_Deck", "rld", "aloc3");
		chr.Dialog.Filename = "Quest\HollandGambit\Longway.c";
		chr.Dialog.CurrentNode = "Longway_prisoner";
		AddLandQuestMark(chr, "questmarkmain");
		for (i=1; i<=2; i++)
		{
			sld = characterFromId("Sailor_"+i);	
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			if (i == 1) ChangeCharacterAddressGroup(sld, "My_Deck", "rld", "aloc2");
			else ChangeCharacterAddressGroup(sld, "My_Deck", "rld", "loc3");
		}
		sld = characterFromId("Sailor_3");
		sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
		sld.dialog.currentnode = "Sailor_deck_5";
		ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void LongwayInShore(string qName)//Лонгвэй в бухте
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("LongwayClone");
	sld.dialog.currentnode = "Longway_prisoner_10";
	ChangeCharacterAddressGroup(sld, "Shore31", "goto", "goto8");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (i=1; i<=3; i++)//уберем охрану китайца
	{
		sld = characterFromId("Sailor_"+i);
		sld.lifeday = 0;
	}
	LAi_LocationFightDisable(&Locations[FindLocation("Shore31")], true);//запрет драки
	locations[FindLocation("Shore31")].DisableEncounters = true; //энкаутеры закрыть
}

void CreatePiterHalleon(string qName)//галеон Стайвесанта
{
	Group_FindOrCreateGroup("Stivesant_Halleon");
	sld = GetCharacter(NPC_GenerateCharacter("Stivesant", "huber_1", "man", "man_B", 35, HOLLAND, 9, false, "quest"));
	FantomMakeSmallSailor(sld, SHIP_GALEON_H, StringFromKey("HollandGambit_38"), CANNON_TYPE_CANNON_LBS24, 100, 100, 100, 100, 100);
	FantomMakeCoolFighter(sld, 35, 90, 90, "blade_15", "pistol5", "bullet", 250);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.name = StringFromKey("HollandGambit_36");
	sld.lastname = StringFromKey("HollandGambit_37");
	sld.greeting = "Stivesant"; 
	Character_SetAbordageEnable(sld, false);//нельзя абордировать
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	SetCharacterPerk(sld, "MusketsShoot");
	AddLandQuestMark(sld, "questmarkmain");
	//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_MAYFANG || GetCompanionQuantity(pchar) > 2) sld.AlwaysEnemy = true;
	if(CheckShipTypeInSquadron(SHIP_MAYFANG) < 1)) sld.AlwaysEnemy = true;
	Group_AddCharacter("Stivesant_Halleon", "Stivesant");
	Group_SetGroupCommander("Stivesant_Halleon", "Stivesant");
	Group_SetAddress("Stivesant_Halleon", "Nevis", "quest_ships", "quest_ship_1");
	pchar.quest.Piter_fail.win_condition.l1 = "NPC_Death";
	pchar.quest.Piter_fail.win_condition.l1.character = "Stivesant";
	pchar.quest.Piter_fail.function = "HollGambitSelf_failed";//для особо умных
}

void QuestShipsTerms_Over(string qName)//провал по срокам - вертаем Виллемстад в норму и зачищаем неписей
{
	if (pchar.questTemp.HWIC.Self == "AttackMeifeng")//упустили Мейфенг
	{
		pchar.quest.Meifeng_AfterBattle.over = "yes";
		Group_DeleteGroup("Sea_Meifeng1");
		AddQuestRecord("Holl_Gambit", "3-47");
		sld = characterFromId("Longway");
		sld.lifeday = 0;
	}
	if (pchar.questTemp.HWIC.Self == "MeetingStivesant")//упустили галеон Стайвесанта
	{
		pchar.quest.Seek_Piter.over = "yes"; //снять прерывание
		pchar.quest.Piter_fail.over = "yes"; //снять прерывание
		AddQuestRecord("Holl_Gambit", "3-50");
		if (CheckShipTypeInSquadron(SHIP_MAYFANG) > 0)//если есть шебека - отберем
		{
			pchar.quest.Remove_Meifeng.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Meifeng.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Meifeng.function = "RemoveMeifeng";
		}
		DelMapQuestMarkIsland("Nevis");
	}
	if (pchar.questTemp.HWIC.Self == "WayWithStivesant")//не пошли как нормальные люди на Кюрасао
	{
		pchar.quest.Piter_fail.over = "yes"; //снять прерывание
		RemoveCharacterCompanion(pchar, characterFromID("Stivesant"));
		AddQuestRecord("Holl_Gambit", "3-51");
		sld = characterFromId("Stivesant");
		sld.lifeday = 0;
		pchar.quest.Remove_Meifeng.win_condition.l1 = "Location_Type";
		pchar.quest.Remove_Meifeng.win_condition.l1.location_type = "town";
		pchar.quest.Remove_Meifeng.function = "RemoveMeifeng";
		DelMapQuestMarkCity("Villemstad");
	}
	CloseQuestHeader("Holl_Gambit");
	pchar.quest.Abigile_died.over = "yes";//снять прерывание на убийство Аби
	sld = characterFromId("Abigile");
	sld.lifeday = 0;
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
	LocatorReloadEnterDisable("Villemstad_town", "reload3_back", false);//открыть вход в резиденцию
	LocatorReloadEnterDisable("Villemstad_town", "reloadR2", false);//открыть боковой вход в резиденцию
	sld = characterFromId("Lucas");
	sld.lifeday = 0;
	sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.dialog.currentnode = "First time";
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
}
	
void RemoveMeifeng(string qName)//удалить Мейфенг, если провалил квест
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("TempOffGuard", "off_hol_4", "man", "man", 35, HOLLAND, 0, false, "soldier"));
	FantomMakeCoolFighter(sld, 35, 90, 90, "blade_14", "pistol3", "grapeshot", 200);//группа альфа
	sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "TempOffGuard";
	LAi_SetImmortal(sld, true);//защита от дурака
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (i=1; i<=3; i++)
	{
		ref chr = GetCharacter(NPC_GenerateCharacter("TempGuard_"+i, "sold_hol_1"+i, "man", "man", 35, HOLLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(chr, 35, 90, 90, "blade_14", "pistol3", "grapeshot", 200);//группа альфа
		LAi_SetImmortal(chr, true);//защита от дурака
		ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto1");
		LAi_CharacterDisableDialog(chr);//запрет диалога
		LAi_SetActorType(chr);
		LAi_ActorFollow(chr, sld, "", -1);
	}
}
	
void StivesantOnStreet(string qName)//прибыли в Виллемстад
{
	bDisableFastReload = true;
	LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload5_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload10_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);//чтобы не сбежал
	pchar.quest.Piter_fail.over = "yes"; //снять прерывание
	pchar.quest.Terms_Over.over = "yes"; //снять таймер
	RemoveCharacterCompanion(pchar, characterFromID("Stivesant"));
	sld = characterFromId("Stivesant");
	sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Stivesant";
	LAi_SetImmortal(sld, true);//защита от дурака
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (i=1; i<=5; i++)
	{
		ref chr = GetCharacter(NPC_GenerateCharacter("StivesantGuard_"+i, "sold_hol_1"+i, "man", "man", 35, HOLLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(chr, 35, 90, 90, "blade_14", "pistol3", "grapeshot", 200);//группа альфа
		LAi_SetImmortal(chr, true);//защита от дурака
		ChangeCharacterAddressGroup(chr, "Villemstad_town", "patrol", "patrol20");
		LAi_SetActorType(chr);
		LAi_ActorFollow(chr, sld, "", -1);
	}
}
	
void InVillemstadResidense(string qName)//вошли в резиденцию
{
	sld = characterFromId("Stivesant");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto3", "", -1.0);
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto4", "PiterTalkWithLucas", -1.0);
}

void SecondDayInVillemstad(string qName)//увели Лукаса в тюрьму
{
	sld = characterFromId("Stivesant");
	sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Stivesant_10";
	LAi_SetActorType(sld);
	LAi_SetPlayerType(PChar);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	locCameraFollow();
	EndQuestMovie();
	LAi_LocationDisableOfficersGen("Villemstad_townhall", false);
}

void OpenResidenceDoor(string qName)//откроем двери
{
	LocatorReloadEnterDisable("Villemstad_town", "reload3_back", false);//открыть вход в резиденцию
	LocatorReloadEnterDisable("Villemstad_town", "reloadR2", false);//открыть боковой вход в резиденцию
	pchar.quest.Award_Give.win_condition.l1 = "location";
	pchar.quest.Award_Give.win_condition.l1.location = "Villemstad_townhall";
	pchar.quest.Award_Give.function = "AwardFromPiterAndBek";
}
	
void AwardFromPiterAndBek(string qName)//церемония награждения
{
	sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "governor1");
	sld = characterFromId("Stivesant");
	sld.dialog.currentnode = "Stivesant_14";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto3");
	for (i=1; i<=3; i++)
	{
		ref chr = characterFromId("StivesantGuard_"+i);
		LAi_SetActorType(chr);
		if (i == 3) ChangeCharacterAddressGroup(chr, "Villemstad_townhall", "goto", "goto1");
		else ChangeCharacterAddressGroup(chr, "Villemstad_townhall", "goto", "goto"+(i+3));
		LAi_ActorTurnToCharacter(chr, pchar);
	}
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	LAi_ActorTurnToCharacter(sld, pchar);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
}
	
void PiterStivesantRemove(string qName)//чистим Стайвесанта
{
	sld = characterFromId("Stivesant");
	sld.location	= "none";
	sld.lifeday = 0;
	sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
}

//----------------------------------------------6 задание--------------------------------------------------
void AbiGoInVillemstad(string qName)//провожаем Аби домой	
{
	sld = characterFromId("Abigile");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "quest", "quest1");
	LAi_ActorFollowEverywhere(sld, "", -1);
	pchar.quest.AbiReturn_InHome.win_condition.l1 = "location";
	pchar.quest.AbiReturn_InHome.win_condition.l1.location = "Villemstad_houseSp2";
	pchar.quest.AbiReturn_InHome.function = "AbiInHouse";
	RemovePassenger(Pchar, sld);
}
	
void AbiInHouse(string qName)//Аби дома
{
	sld = characterFromId("Abigile");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, characterFromID("Solomon"));
	ChangeCharacterAddressGroup(sld, "Villemstad_houseSp2", "goto", "goto2");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	pchar.quest.Abigile_died.over = "yes";//снять прерывание на убийство Аби
}
	
void CreateTradeFleut(string qName)//флейт Тоффа Келлера
{
	Group_FindOrCreateGroup("Keller_Fleut");
	Group_SetType("Keller_Fleut", "trade");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("Keller", "trader_2", "man", "man", 20, HOLLAND, 5, false, "quest"));
	FantomMakeSmallSailor(sld, SHIP_FLEUT, StringFromKey("HollandGambit_39"), CANNON_TYPE_CANNON_LBS8, 50, 40, 40, 60, 60);
	FantomMakeCoolFighter(sld, 20, 30, 30, "blade_08", "pistol3", "grapeshot", 50);
	sld.name = StringFromKey("HollandGambit_40");
	sld.lastname = StringFromKey("HollandGambit_41");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	Character_SetAbordageEnable(sld, false);//нельзя абордировать
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "trade";
	SetCharacterPerk(sld, "MusketsShoot");
	AddLandQuestMark(sld, "questmarkmain");
	Group_AddCharacter("Keller_Fleut", "Keller");
	Group_SetGroupCommander("Keller_Fleut", "Keller");
	Group_SetAddress("Keller_Fleut", "Trinidad", "quest_ships", "quest_ship_6");
	pchar.quest.Keller_fail.win_condition.l1 = "NPC_Death";
	pchar.quest.Keller_fail.win_condition.l1.character = "Keller";
	pchar.quest.Keller_fail.function = "AbiIsland_failed";//для особо тупых
}	
	
void AbiIsland_failed(string qName)//если у кого-то нет моска
{
	Group_DeleteGroup("Keller_Fleut");
	AddQuestRecord("Holl_Gambit", "");
	ChangeCharacterHunterScore(PChar, "holhunter", 30); //начислить НЗГ
	CloseQuestHeader("Holl_Gambit");
	pchar.questTemp.HWIC.Self = "end";
	pchar.questTemp.HWIC.Detector = "self_fail";
}
	
void BattleInGrot(string qName)//напали ванберговцы в пещере
{
	DelMapQuestMarkIsland("IslaDeCoche");
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться 300912
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("vanberg_sold_"+i, "citiz_"+(40+i), "man", "man", 15, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 15, 40, 40, "blade_04", "pistol3", "bullet", 70);
		if (i == 1) 
		{
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "vanberg_sold";
			sld.greeting = "hunter";
			ChangeCharacterAddressGroup(sld, "IslaDeCoche_Grot", "reload", "reload1");
		}
		else
		{
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "IslaDeCoche_Grot", "monsters", "monster1");
		}
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}
	
void CreateVanbergSailors(string qName)//напали ванберговцы в бухте
{
	chrDisableReloadToLocation = true;
	for (i=1; i<=5; i++)//5 солдат
	{
		sld = GetCharacter(NPC_GenerateCharacter("vanberg_sailor_"+i, "citiz_"+(i+43), "man", "man", 15, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 15, 40, 40, "blade_10", "pistol6", "bullet", 50);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, pchar.location.from_sea, "goto", "goto"+(i+3));
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	for (i=1; i<=3; i++)//3 мушкетера
	{
		sld = GetCharacter(NPC_GenerateCharacter("vanberg_mushketer_"+i, "mush_ctz_"+(6+i), "man", "mushketer", 20, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 20, 50, 50, "", "mushket1", "cartridge", 50);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, pchar.location.from_sea, "goto", "goto"+i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "PrepareVanbergInSea");
}
	
void CreateVanbergInSea(string qName)//Якоб ван Берг у острова
{
	Island_SetReloadEnableGlobal("IslaDeCoche", false);//на остров нельзя
	bQuestDisableMapEnter = true;//на карту тоже
	Group_FindOrCreateGroup("Mirage");
	Group_SetType("Mirage", "pirate");//тип группы
	sld = characterFromId("JacobBerg");
	FantomMakeCoolSailor(sld, SHIP_MIRAGE, StringFromKey("HollandGambit_6"), CANNON_TYPE_CANNON_LBS18, 70, 70, 70);
	// belamour для легких уровней команду в опт -->
	if(MOD_SKILL_ENEMY_RATE < 7) SetCrewQuantity(sld,GetOptCrewQuantity(sld));
	// <-- legendary edition			 
	FantomMakeCoolFighter(sld, 30, 80, 80, "topor_04", "pistol5", "bullet", 150); // приз - секира 090912
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "spyglass3");
	GiveItem2Character(sld, "recipe_totem_13");
	GiveItem2Character(sld, "totem_13");
	sld.Ship.Mode = "pirate";
	if (GetCompanionQuantity(pchar) > 1) sld.Abordage.Enable = false;//теперь попробуй взять компаньоном
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 3;//замшелый корпус
	SetShipSailsFromFile(sld, "ships/parus_torn.tga");
	SetSailsColor(sld, 8);//черный рваный парус
	sld.ship.Crew.Morale = 100;
	sld.Ship.Crew.Exp.Sailors = 100;
	sld.Ship.Crew.Exp.Cannoners = 100;
	sld.Ship.Crew.Exp.Soldiers = 100;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Mirage", "JacobBerg");
	Group_SetGroupCommander("Mirage", "JacobBerg");
	Group_SetTaskAttack("Mirage", PLAYER_GROUP);
	Group_SetPursuitGroup("Mirage", PLAYER_GROUP);
	Group_SetAddress("Mirage", "IslaDeCoche", "", "");
	Group_LockTask("Mirage");
	
	pchar.quest.Mirage_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Mirage_AfterBattle.win_condition.l1.group = "Mirage";
	pchar.quest.Mirage_AfterBattle.function = "Mirage_AfterBattle";
}	
	
void Mirage_AfterBattle(string qName)//после боя
{
	AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
	AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
	AddLandQuestMark(characterFromId("Joakim"), "questmarkmain");
	AddMapQuestMarkCity("SentJons", false);
	AddMapQuestMarkCity("Villemstad", false);
	DoQuestCheckDelay("sea_victory", 1.5);
	Island_SetReloadEnableGlobal("IslaDeCoche", true);
	bQuestDisableMapEnter = false;
	Group_DeleteGroup("Mirage");
	AddQuestRecord("Holl_Gambit", "3-63");
	pchar.questTemp.HWIC.Self = "VanbergDestroyed";
	AddComplexSeaExpToScill(200, 200, 200, 200, 200, 200, 0);
	SetFunctionTimerCondition("MakeAbiPoor", 0, 0, 30, false); //даем месяц сроку, чтобы вернул деньги Аби
}
	
//-----------------------------------------эпилог-----------------------------------------------
void GoFromAbiRoom(string qName)//телепорт из комнаты Аби
{
	DoQuestReloadToLocation("Villemstad_houseSp2", "reload", "reload2", "");
	LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", true);
	pchar.quest.Solomon_talk.win_condition.l1 = "locator";
	pchar.quest.Solomon_talk.win_condition.l1.location = "Villemstad_houseSp2";
	pchar.quest.Solomon_talk.win_condition.l1.locator_group = "reload";
	pchar.quest.Solomon_talk.win_condition.l1.locator = "reload1";
	pchar.quest.Solomon_talk.function = "SolomonTalk";
	
	EndQuestMovie();
	bDisableCharacterMenu = false;
	locCameraTarget(PChar);
	locCameraFollow();
	LAi_SetPlayerType(pchar);
	
	sld = characterFromId("Abigile");
	LAi_SetOwnerType(sld);
	sld.model.animation = "woman_A2";
	Characters_RefreshModel(sld);
}	
	
void SolomonTalk(string qName)//благодарности Соломона
{
	sld = characterFromId("Solomon");
	sld.dialog.currentnode = "Solomon_thanks";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
	
void MakeAbiPoor(string qName)//Аби и Соломон остались без гроша
{
	//DelMapQuestMarkCity("Villemstad");
	sld = characterFromId("Solomon");
	sld.dialog.currentnode = "Solomon_poor";
	FreeSitLocator("Villemstad_tavern", "sit_front1");
	LAi_SetSitType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "sit", "sit_front1");
	sld = characterFromId("Abigile");
	DelLandQuestMark(sld);
	sld.dialog.currentnode = "Abigile_Poor";
	LAi_SetOwnerType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhallRoom", "goto", "goto1");
	sld = GetCharacter(NPC_GenerateCharacter("Abihouselady", "women_8", "woman", "towngirl", 5, HOLLAND, -1, false, "quest"));
	LAi_SetOwnerType(sld);
	sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Abihouselady";
	ChangeCharacterAddressGroup(sld, "Villemstad_houseSp2", "goto", "goto1");
	log_info(StringFromKey("HollandGambit_43"));
	ChangeCharacterComplexReputation(pchar, "nobility", -20);
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool HollandGambit_QuestComplete(string sQuestName, string qname)
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///  Jason  								Голландский гамбит
//////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld, chr;
	aref arOldMapPos, arAll, arPass;
	int  iTemp, i, n; // нужно для вычислений любых целых (нации)
	string sTemp; // любые строки для вычислений
//-------------------------------------общие функции-----------------------------------------------
	bool condition = true;

	if (sQuestName == "ReturnTalkerToOfficer")
	{
		chrDisableReloadToLocation = false;
		pchar.quest.HWIC_ReturnOfficer.win_condition.l1 = "location";
		pchar.quest.HWIC_ReturnOfficer.win_condition.l1.location = "Villemstad_town";
		pchar.quest.HWIC_ReturnOfficer.function = "HWICofficerTalkReturn";
	}
	else if (sQuestName == "PrepareToBoom")
	{
		pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4; // ба-бах!
		pchar.GenQuest.ShipSituation.Explosion.CapId = "Fleetwood";
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "PrepareToBoom1")
	{
		pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4; // ба-бах!
		pchar.GenQuest.ShipSituation.Explosion.CapId = "Lucas";
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "PrepareToBoom2")
	{
		pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4; // ба-бах!
		pchar.GenQuest.ShipSituation.Explosion.CapId = "JacobBerg";
		AddComplexSelfExpToScill(200, 200, 200, 200);
	}
	else if (sQuestName == "JoakimInRoom")
	{
		pchar.quest.Joakim_InRoom.win_condition.l1 = "location";
		pchar.quest.Joakim_InRoom.win_condition.l1.location = "Villemstad_houseSp1_room";
		pchar.quest.Joakim_InRoom.function = "JoakimTalk";
	}
	else if (sQuestName == "SantiagoTripTalkToMC")
	{
		sld = characterFromId("SantiagoEnemy1");
		sld.dialog.currentnode = "Santiago_Trip_2";
		sld.greeting = "hambit_other_2";
		ChangeCharacterAddressGroup(sld, "Santiago_HouseSp2_Room", "barmen", "stay");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 2.0);
		AddCharacterExpToSkill(pchar, "Fortune", 50); // везение
	}
	else if (sQuestName == "SantiagoTripExitFromRoom")
	{
		LocatorReloadEnterDisable("Santiago_HouseSp2_Room", "reload1", false); // открыть выход
		LAi_LocationFightDisable(&Locations[FindLocation("Santiago_HouseSp2")], true); // запретить драться // patch-2
		pchar.quest.Santiago_Trip2.win_condition.l1 = "locator";
		pchar.quest.Santiago_Trip2.win_condition.l1.location = "Santiago_HouseSp2";
		pchar.quest.Santiago_Trip2.win_condition.l1.locator_group = "reload";
		pchar.quest.Santiago_Trip2.win_condition.l1.locator = "reload3";
		pchar.quest.Santiago_Trip2.function = "SantiagoTripSecondTalk";
	}
	else if (sQuestName == "SantiagoTripExitHouse")
	{
		InterfaceStates.Buttons.Save.enable = true; // разрешить сохраняться
		chrDisableReloadToLocation = false;
		AddQuestRecord("Holl_Gambit", "1-45");
		pchar.questTemp.HWIC.Holl = "SantiagoTripReturn";
		AddComplexSelfExpToScill(80, 80, 80, 80);
		AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
	}
	else if (sQuestName == "HollJacob_dead")
	{
		DoQuestCheckDelay("hide_weapon", 1.0);
		pchar.quest.Holl_Jacob.win_condition.l1 = "item";
		pchar.quest.Holl_Jacob.win_condition.l1.item = "JacobJournal";
		pchar.quest.Holl_Jacob.function = "Jacob_Journal";
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Fortune", 100); // везение
	}
	else if (sQuestName == "BekSitDown")
	{
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		sld.Dialog.Filename = "Common_Governor.c";
		sld.dialog.currentnode = "First time";
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
	}
	else if (sQuestName == "LucasReturnInCabinet")
	{
		sld = characterFromId("Lucas");
		sld.Dialog.Filename = "Quest\HollandGambit\LucasRodenburg.c";
		sld.dialog.currentnode = "Second_time";
		LAi_SetHuberType(sld);
		// belamour legendary edition меняем прописку
		ChangeCharacterAddressGroup(sld, "GVIK_residence", "sit", "sit1");
		LAi_SetPlayerType(pchar);
		bDisableFastReload = false;
	}
	else if (sQuestName == "Merdok_AfterBattle")
	{
		LAi_LocationDisableOfficersGen("SentJons_TownCave", false); // офицеров пускать
		pchar.quest.Merdok_Book.win_condition.l1 = "item";
		pchar.quest.Merdok_Book.win_condition.l1.item = "MerdokArchive";
		pchar.quest.Merdok_Book.function = "FindMerdokBook"; // прерывание на архив
		pchar.quest.Merdok_Key.win_condition.l1 = "item";
		pchar.quest.Merdok_Key.win_condition.l1.item = "Drugstore_keys";
		pchar.quest.Merdok_Key.function = "FindMerdokKey"; // прерывание на ключ
		pchar.questTemp.HWIC.Holl = "MerdokDie";
		// а теперь проверим китайца
		sld = characterFromId("Longway");
		sld.greeting = "";
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend") && GetCharacterIndex("Longway") != -1)
		{
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		AddMapQuestMarkCity("Villemstad", false);
		DelMapQuestMarkCity("SentJons");
	}
	else if (sQuestName == "OpenFleetwoodDoor")
	{
		LocatorReloadEnterDisable("SentJons_town", "houseSP3", false);
	}
	else if (sQuestName == "SitInGrot")
	{
		LAi_SetActorType(Pchar);
		LAi_ActorAnimation(Pchar, "Ground_sitting", "", 2.5);
		DoQuestFunctionDelay("StandUpInGrot", 2.5);
	}
	else if (sQuestName == "MonsterStandUp")
	{
		sld = characterFromId("Chavinavi");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Ground_StandUp", "MonsterFight", 3.5);
		PlaySound("VOICE\Russian\hambit\Chavinavy.wav");
	}
	else if (sQuestName == "MonsterFight")
	{
		PlaySound("ambient\horror\horror2.wav");
		PlaySound("types\skel.wav");
		LAi_SetPlayerType(Pchar);
		sld = characterFromId("Chavinavi");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "GrotAfterBattle");
	}
	else if (sQuestName == "GrotAfterBattle")
	{
		pchar.quest.Abby_IslandHeadBarmen.win_condition.l1 = "item";
		pchar.quest.Abby_IslandHeadBarmen.win_condition.l1.item = "GastonHead";
		pchar.quest.Abby_IslandHeadBarmen.function = "HeadBarmen_Find"; // на нахождение бошки бармена
		AddComplexSelfExpToScill(200, 200, 200, 200);
	}
	else if (sQuestName == "Merdok_AfterBattleEng")
	{
		LocatorReloadEnterDisable("SentJons_TownCave", "reload2", false); // выход откроем
		LAi_LocationDisableOfficersGen("SentJons_TownCave", false); // офицеров пускать
		pchar.quest.Merdok_Book.win_condition.l1 = "item";
		pchar.quest.Merdok_Book.win_condition.l1.item = "MerdokArchive";
		pchar.quest.Merdok_Book.function = "FindMerdokBook"; // прерывание на архив
		pchar.quest.Merdok_Map.win_condition.l1 = "item";
		pchar.quest.Merdok_Map.win_condition.l1.item = "NPC_Letter";
		pchar.quest.Merdok_Map.function = "CreateLucasBonanza"; // прерывание на карту клада
		pchar.questTemp.HWIC.Eng = "MerdokDie";
		chrDisableReloadToLocation = true; // закрыть локацию
		pchar.GenQuest.NoDelBody = true;
	}
	else if (sQuestName == "Fernando_FightInPort")
	{
		chrDisableReloadToLocation = true; // выходы закроем
		iTemp = GetCharacterIndex("HWICFernando");
		if (iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_group_Attack(sld, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		}
		pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
		pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
		pchar.quest.HWIC_Fernando.function = "Fernando_died";
	}
	else if (sQuestName == "PrepareToStreetFight")
	{
		chrDisableReloadToLocation = false;
		pchar.quest.Fleetwood_deafenning.win_condition.l1 = "location";
		pchar.quest.Fleetwood_deafenning.win_condition.l1.location = "SentJons_town";
		pchar.quest.Fleetwood_deafenning.function = "SJ_StreetFight";
	}
	else if (sQuestName == "MC_deafenning")
	{
		chrDisableReloadToLocation = false;
		DoQuestCheckDelay("hide_weapon", 1.0);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "death_citizen_1", "Without_consciousness", 5.0);
	}
	else if (sQuestName == "Without_consciousness")
	{
		SetLaunchFrameFormParam(StringFromKey("HollandGambit_42"), "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 5, 9, 10); // крутим время
		RecalculateJumpTable();
		DoQuestFunctionDelay("InMerdokHouse", 5.0);
		// if (2-sti(RealShips[sti(pchar.ship.type)].basetype) < 0) pchar.Ship.Type = SHIP_NOTUSED;
		LocatorReloadEnterDisable("SentJons_town", "houseSP3", true); // дом Флитвуда закроем
	}
	else if (sQuestName == "MerdokTalkToMC")
	{
		chrDisableReloadToLocation = true; // закрыть локацию
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Merdok");
		sld.dialog.currentnode = "MC_InHouse";
		ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "barmen", "bar3");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld = characterFromId("Tonzag");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Fortune", 100); // везение
	}
	else if (sQuestName == "Kill_Knippel")
	{
		LAi_SetActorType(pchar);
		//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
		if (!CheckAttribute(pchar, "equip." + GUN_ITEM_TYPE) || !CheckAttribute(pchar, "equip." + MUSKET_ITEM_TYPE))
		{
			GiveItem2Character(pchar, "pistol1");
			EquipCharacterbyItem(pchar, "pistol1");
		}
		// <-- legendary edition
		LAi_ActorAnimation(pchar, "Shot", "Knippel_die", 1.0);
	}
	else if (sQuestName == "Knippel_die")
	{
		sld = characterFromId("KnippelClone");
		LAi_KillCharacter(sld);
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Sailor_3");
		sld.dialog.currentnode = "Sailor_deck_2";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		Achievment_SetStat(95, 1);
	}
	else if (sQuestName == "ReturnMCPlayer")
	{
		LAi_SetPlayerType(pchar);
		chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "Abigile_Stay")
	{
		sld = characterFromId("Abigile");
		LAi_SetOwnerType(sld);
		LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", false); // откроем комнату Аби
	}
	else if (sQuestName == "SetAbigileToCabin")
	{
		int iShipType = GetCharacterShipType(pchar);
		ref rShip = GetRealShip(iShipType);
		sTemp = "My_" + rShip.CabinType;
		sld = characterFromId("Abigile");
		ChangeCharacterAddressGroup(sld, sTemp, "rld", "aloc0");
		LAi_SetCitizenType(sld);
		chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "ContinueWithMerdok")
	{
		sld = characterFromId("Merdok");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "MC_writeLetter")
	{
		LAi_FadeLong("MC_writeLetter2", "");
	}
	else if (sQuestName == "MC_writeLetter2")
	{
		LAi_SetActorType(pchar);
		LAi_SetSitType(pchar);
		TeleportCharacterToPosAy(pchar, -1.70, 0.00, 1.00, -0.00);
		locCameraFromToPos(-0.40, 1.17, -0.77, true, -1.64, -0.78, 2.49);
		DoQuestFunctionDelay("MC_writeLetterGo", 4.0);
	}
	else if (sQuestName == "MC_writeLetterDone") // написали письмо
	{
		LAi_FadeLong("MC_writeLetterDone2", "");
	}
	else if (sQuestName == "MC_writeLetterDone2") // написали письмо
	{
		EndQuestMovie();
		locCameraTarget(PChar);
		locCameraFollow();
		GiveItem2Character(pchar, "MC_Letter");
		AddQuestRecordInfo("LetterToFleetwood", "1");
		pchar.questTemp.HWIC.Self = "LetterToFleetwood";
		LAi_SetPlayerType(pchar);
		ChangeCharacterAddressGroup(pchar, "SentJons_HouseF3", "goto", "goto4");
		sld = characterFromId("Merdok");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		// уберем табурет
		sld = ItemsFromID("lcheer");
		sld.shown = false;
		sld.startLocation = "none";
		sld.startLocator = "";
	}
	else if (sQuestName == "MC_TakeCloves")
	{
		chrDisableReloadToLocation = false;
		sld = characterFromId("Merdok");
		LAi_SetOwnerType(sld);
	}
	else if (sQuestName == "DrunkardGoTown")
	{
		chrDisableReloadToLocation = false; // открыть локацию
		sld = characterFromId("Drunkard");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "houseSP3", "SentJons_houseSP3", "reload", "reload1", "DrunkardInHouse", -1);
		bDisableFastReload = true; // закроем быстрый переход
		pchar.GenQuest.CannotWait = true; // не мотать время
	}
	else if (sQuestName == "DrunkardInHouse")
	{
		DoQuestFunctionDelay("DrunkardReturnToTavern", 120.0);
	}
	else if (sQuestName == "DrunkardSitInTavern")
	{
		sld = characterFromId("Drunkard");
		sld.dialog.currentnode = "Drunkard_9";
		LAi_SetSitType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		ChangeCharacterAddressGroup(sld, "Sentjons_tavern", "sit", "sit_front1");
		bDisableFastReload = false;
		LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
		LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
		LocatorReloadEnterDisable("SentJons_town", "gate_back", false);
		bDisableFastReload = false; // открыть переход
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		SetFunctionTimerCondition("Fleetwood_meetingOver", 0, 0, 15, false); // таймер сюда поставим
	}
	else if (sQuestName == "FleetwoodDiedInShore")
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("Holl_Gambit", "3-31");
		pchar.quest.Login_Val.win_condition.l1 = "location";
		pchar.quest.Login_Val.win_condition.l1.location = "Terks";
		pchar.quest.Login_Val.function = "CreateValkiriaBrig";
		AddComplexSelfExpToScill(100, 100, 100, 100);
		for (i = 1; i <= 7; i++)
		{
			// log_info("чистим матросов"); // лесник удалил матросов после боя с флитвудом.
			sld = characterFromId("OwrSailor_" + i);
			sld.lifeday = 0; // убираем засаду
		}
	}
	else if (sQuestName == "ReturnShoreToNormal")
	{
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation("Shore31")], false);
		locations[FindLocation("Shore31")].DisableEncounters = false; // локацию в норму
	}
	else if (sQuestName == "OpenVillemstadResidence")
	{
		LocatorReloadEnterDisable("Villemstad_town", "reload3_back", false); // открыть вход в резиденцию
		LocatorReloadEnterDisable("Villemstad_town", "reloadR2", false); // открыть боковой вход в резиденцию
		for (i = 1; i <= 5; i++)
		{
			chr = characterFromId("StivesantGuard_" + i);
			ChangeCharacterAddressGroup(chr, "Villemstad_townhall", "goto", "goto5");
		}
		sld = characterFromId("Stivesant");
		DelLandQuestMark(sld);
		LAi_ActorFollow(chr, sld, "", -1);
		pchar.quest.Piter_Go.win_condition.l1 = "location";
		pchar.quest.Piter_Go.win_condition.l1.location = "Villemstad_townhall";
		pchar.quest.Piter_Go.function = "InVillemstadResidense";
		LAi_LocationDisableOfficersGen("Villemstad_townhall", true);
	}
	else if (sQuestName == "PiterTalkWithLucas")
	{
		StartQuestMovie(true, true, true);
		LAi_SetPlayerType(PChar);
		sld = characterFromId("Lucas");
		sld.greeting = "";
		LAi_SetActorType(sld);
		sld = characterFromId("Stivesant");
		sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
		sld.dialog.currentnode = "ArestLucas_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	else if (sQuestName == "PiterTalkWithLucas_2")
	{
		locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, -3.50);
	}
	else if (sQuestName == "DoubleTalkWithLucas")
	{
		locCameraFollow();
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
		sld.dialog.currentnode = "ArestLucas_40";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	else if (sQuestName == "LucasGoToPrison")
	{
		sld = characterFromId("Lucas");
		sld.greeting = ""; // озвучка напрямую
		ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
		sld = characterFromId("Merdok");
		sld.greeting = "merdok_5";
	}
	else if (sQuestName == "TalkWithLucasPrisoner")
	{
		sld = characterFromId("Lucas");
		GiveItem2Character(sld, "unarmed");
		EquipCharacterbyItem(sld, "unarmed");
		sld.Dialog.Filename = "Quest\HollandGambit\LucasRodenburg.c";
		sld.dialog.currentnode = "LucasPrisoner";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 3, 0);
	}
	else if (sQuestName == "StivesantSitDown")
	{
		sld = characterFromId("Stivesant");
		sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
		sld.dialog.currentnode = "Stivesant_18";
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
		pchar.quest.Piter_Remove.win_condition.l1 = "Timer";
		pchar.quest.Piter_Remove.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Piter_Remove.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
		pchar.quest.Piter_Remove.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
		pchar.quest.Piter_Remove.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
		pchar.quest.Piter_Remove.function = "PiterStivesantRemove";
	}
	else if (sQuestName == "ReturnAbiNormal")
	{
		sld = characterFromId("Solomon");
		LAi_SetOwnerType(sld);
		sld = characterFromId("Abigile");
		LAi_SetOwnerType(sld);
	}
	else if (sQuestName == "PrepareMassakraInShore")
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("Holl_Gambit", "3-61");
		pchar.quest.vanberg_ShoreBattle.win_condition.l1 = "location";
		pchar.quest.vanberg_ShoreBattle.win_condition.l1.location = pchar.location.from_sea;
		pchar.quest.vanberg_ShoreBattle.function = "CreateVanbergSailors";
	}
	else if (sQuestName == "PrepareVanbergInSea")
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("Holl_Gambit", "3-62");
		pchar.quest.vanberg_SeaBattle.win_condition.l1 = "location";
		pchar.quest.vanberg_SeaBattle.win_condition.l1.location = "IslaDeCoche";
		pchar.quest.vanberg_SeaBattle.function = "CreateVanbergInSea";
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Fortune", 100); // везение
	}
	else if(sQuestName == "AbiKiss")
	{
		TeleportCharacterToPosAy(pchar, 0.30, 0.00, -2.20, 3.00);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 4.5);
		sld = characterFromId("Abigile");
		TeleportCharacterToPosAy(sld, 0.30, 0.00, -2.80, 0.00);
		LAi_SetActorType(sld);
		sld.model.animation = "woman";
		Characters_RefreshModel(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 4.5);
		locCameraFromToPos(1.41, 1.76, -1.06, true, -0.91, -0.40, -3.93);
		DoQuestFunctionDelay("GoFromAbiRoom", 4.5);
	}
	else
	{
		condition = false;
	}
	// <-- Голландский Гамбит конец
	
	return condition;
}