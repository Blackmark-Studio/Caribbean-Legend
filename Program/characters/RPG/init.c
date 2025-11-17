
void initNewMainCharacter()//инициализация главного героя
{
	ref ch = GetMainCharacter();
	// Установим начальный дневной рандом
	UpdateSeeds();
	ch.PersonalSeed = rand(1000000); // уникальное число для рандома с хэшем
	string sTemp;
	int    iTmp, i;

    CCS_SetNewMainCharacter(ch, startHeroType);
    // контроль версий -->
    InitMigrations();
    // контроль версий <--

    // ROSARAK WEIGHT RANDOM (ВАЖНО ТУТ)
    InitWeightParameters();

    MOD_EXP_RATE =  makeint(MOD_EXP_RATE + MOD_SKILL_ENEMY_RATE * MOD_EXP_RATE / 1.666666666); // разные уровни для всех
    if (MOD_EXP_RATE < 10) MOD_EXP_RATE = 10; // иначе будет развал целостности данных, порог релиховой версии бля всех сложностей.

	// куда плывем	
	switch (sti(ch.nation))
	{
		case ENGLAND : 
			if(startHeroType == 4) ch.HeroParam.ToCityId = "SantaCatalina";
			else ch.HeroParam.ToCityId = "PortRoyal";
		break;
		case FRANCE  : 
			if(SandBoxMode) ch.HeroParam.ToCityId = "BasTer";
			else ch.HeroParam.ToCityId = "Charles";
		break;
		case SPAIN :   ch.HeroParam.ToCityId = "Santiago"; break;
		case HOLLAND : FindAlliedColonyForNation(sti(ch.nation), true); break;
		case PIRATE :  ch.HeroParam.ToCityId = "Pirates"; break;
	}

	// откуда плывем
    ch.HeroParam.FromCityId  = Colonies[FindNonEnemyColonyForAdventure(sti(ch.nation), ch.HeroParam.ToCityId, true)].id;

	// где появимся	
	ch.HeroParam.Location = ch.HeroParam.ToCityId + "_town";
	ch.HeroParam.Group    = "reload";
	ch.HeroParam.Locator  = "reload1";
	
	setCharacterShipLocation(ch, ch.HeroParam.Location);
    setWDMPointXZ(ch.HeroParam.Location);  // коорд на карте
    
	// а надо ли нам это ?
	SetTimerCondition("Move_Govenour", 0, 0, 25 + rand(10), true); // to_do перенести в один метод инициации
	
	//Запускаем проверку на падение здоровья раз в 5 дней
    SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
    
    SetTimerCondition("Nation_Legend", 0, 0, 25 + rand(10), true);

	// Jason: новая усадка генерал-губернаторов. На постоянке - Пуанси, Виндзор, Фокс, де Кордова
	SetGovenoursToResidence();

	ReloadProgressUpdate();

 	SetNationRelations();
 	// от кого драпаем
	ch.HeroParam.EnemyNation  = FindEnemyNation2Nation(sti(ch.nation));

    // boal вешаем прерывание на охотников навечно (для моря и земли) -->
    SetFunctionTimerCondition("SeaHunterCheck_eng", 0, 0, 6, true);
    SetFunctionTimerCondition("SeaHunterCheck_fra", 0, 0, 6, true);
    SetFunctionTimerCondition("SeaHunterCheck_spa", 0, 0, 6, true);
    SetFunctionTimerCondition("SeaHunterCheck_hol", 0, 0, 6, true);

    SetFunctionTimerCondition("FireBrigade_spa", 0, 0, 5, true);
    if(SandBoxMode)
    {
        SetFunctionTimerCondition("FireBrigade_eng", 0, 0, 5, true);
        SetFunctionTimerCondition("FireBrigade_fra", 0, 0, 5, true);
        SetFunctionTimerCondition("FireBrigade_hol", 0, 0, 5, true);
    }

    SaveCurrentQuestDateParam("Land_HunterTimerEng");
    SaveCurrentQuestDateParam("Land_HunterTimerFra");
    SaveCurrentQuestDateParam("Land_HunterTimerSpa");
    SaveCurrentQuestDateParam("Land_HunterTimerHol");
    // boal вешаем прерывание на охотников навечно (для моря и земли) <--

    LAi_SetHP(ch, LAI_DEFAULT_HP, LAI_DEFAULT_HP);

    ch.HeroParam.HeroType = NullCharacter.HeroParam.HeroType;

	SetSPECIAL(ch, 4,4,4,4,4,4,4);
	switch (ch.HeroParam.HeroType)
	{        
		case "HeroType_1":	//Дуэлянт
			SetSPECIAL(ch, 5, 7, 6, 5, 6, 9, 5);
			SetSelfSkill(ch, 8, 1, 1, 3, 1);
			SetShipSkill(ch, 5, 1, 1, 3, 1, 1, 8, 5, 1);
			SetCharacterPerk(ch, "HT1");
			SetCharacterPerk(ch, "TannedLeather");
			ch.StartShip = SHIP_SLOOP;
		break;
		
		case "HeroType_2":	//Счетовод
			SetSPECIAL(ch,  6, 5, 6, 9, 6, 4, 7);
			SetSelfSkill(ch, 1, 3, 1, 1, 1);
			SetShipSkill(ch, 8, 8, 1, 1, 1, 3, 1, 5, 5);
			SetCharacterPerk(ch, "HT2");
			SetCharacterPerk(ch, "RatsWolf");
			SetCharacterPerk(ch, "Mimicry");
			SetCharacterPerk(ch, "TreasureHunter");
			ch.StartShip = SHIP_BARKENTINE;
		break;
		
		case "HeroType_3":	//Атлет
			SetSPECIAL(ch, 9, 5, 8, 4, 5, 6, 6);
			SetSelfSkill(ch, 1, 5, 8, 1, 3);
			SetShipSkill(ch, 1, 1, 1, 1, 1, 5, 3, 8, 1);
			SetCharacterPerk(ch, "HT3");
			SetCharacterPerk(ch, "Mule");
			ch.StartShip = SHIP_LUGGER;
		break;
		
		case "HeroType_4":	//Стрелок
			SetSPECIAL(ch, 4, 8, 7, 4, 5, 6, 9);
			SetSelfSkill(ch, 3, 1, 1, 8, 5);
			SetShipSkill(ch, 1, 1, 8, 5, 1, 3, 1, 1, 1);
			SetCharacterPerk(ch, "HT4");
			SetCharacterPerk(ch, "Bombardier");
			SetCharacterPerk(ch, "Sniper");
			ch.StartShip = SHIP_CAREERLUGGER;
		break;
	}
	
	ch.skill.freeskill   = 0;
	ch.Skill.FreeSPECIAL = 0;
	sGlobalTemp   = "Flag" + NationShortName(sti(ch.nation));
	SetCharacterPerk(ch, sGlobalTemp); // перк флага нации
	SetCharacterPerk(ch, "FlagPir");
	SetCharacterPerk(ch, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
	SetCharacterPerk(ch, "Rush");
    SetBonusPush(ch, true); // Rosarak - Коллизии
	// начальные скилы задать
    //InitStartParam(ch); // Jason - fix
	LAi_SetHP(ch, GetCharacterBaseHPValue(ch), GetCharacterBaseHPValue(ch));
    SetEnergyToCharacter(ch);
    TreasureTiersInit(); // Инитим сокровища ДО выдачи карты
    if (!SandBoxMode) initMainCharacterItem(); // Сюжет
    else initMainFreePlayCharacterItem();
    GEN_ApplyPlayerDifficulty(ch);
    CT_UpdateCashTables(ch);
    CT_UpdateLandTable(ch);

	ReloadProgressUpdate();	
    DeleteAttribute(ch, "Ship");

	if (!SandBoxMode)	// Сюжет
	{
		ch.Ship.Type = SHIP_NOTUSED;
		/*Ch.GenQuest.VideoAVI = "intro_Sharle";
		Ch.GenQuest.VideoAfterQuest = "SharlieTutorial_StartGame";
		DoQuestCheckDelay("PostVideo_Start", 0.2);*/
		loadedLocation = &Locations[0];
		pchar.systeminfo.LockFader = "loading\Start_Loading.tga";
		pchar.systeminfo.BLIoff = true;
		QuestToSeaLogin_Prepare(0.0, 0.0, "");
		QuestToSeaLogin_Launch();
		
		bQuestDisableMapEnter = true;
		pchar.GenQuest.CabinLock = true;
		bDisableCharacterMenu = true;
		InterfaceStates.Buttons.Save.enable = false;
		bCannonsRangeShow = false;
		//SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, argb(0,255,255,255), argb(0,255,255,255), argb(0,255,0,0), argb(0,255,0,0), 0.002, 0.002, 0);
		//DoQuestFunctionDelay("ChangeInterface", 1.1);
		DoQuestFunctionDelay("SharlieTutorial_Music", 1.1);
		DoQuestFunctionDelay("SharlieTutorial_PogodaRefresh", 0.1);
		DoQuestFunctionDelay("SharlieTutorial_RadiusCannonsOff", 1.5);
		
		pchar.Ship.Type = GenerateShipExt(SHIP_PINNACE, true, pchar);
		pchar.Ship.name = StringFromKey("SharlieTutorial_6");
		SetBaseShipData(pchar);
		RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull = 2;
		SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
		realships[sti(pchar.ship.type)].WaterLine = 1.3;
		realships[sti(pchar.ship.type)].Capacity = 6500;
		realships[sti(pchar.ship.type)].SpeedRate = 11.65;
		realships[sti(pchar.ship.type)].TurnRate = 78.65;
		realships[sti(pchar.ship.type)].WindAgainstSpeed = 1.75;
		pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
		SetCrewQuantityFull(pchar);
		pchar.ship.Crew.Morale = 100;
		ChangeCrewExp(pchar, "Sailors", 100);
		ChangeCrewExp(pchar, "Cannoners", 100);
		ChangeCrewExp(pchar, "Soldiers", 100);
		SetCharacterGoods(pchar, GOOD_BALLS, 0);
		SetCharacterGoods(pchar, GOOD_GRAPES, 0);
		SetCharacterGoods(pchar, GOOD_KNIPPELS, 0);
		SetCharacterGoods(pchar, GOOD_BOMBS, 0);
		SetCharacterGoods(pchar, GOOD_POWDER, 0);
		SetCharacterGoods(pchar, GOOD_WEAPON, 0);
		DeleteAttribute(pchar, "StartShip");
		
		SetCurrentTime(19, 00);
		WeatherParams.Rain 			= false;
		WeatherParams.Rain.ThisDay 	= false;
		pchar.questTemp.TimeLock = true;
		CreateSky(3);
		
		SeaCameras_SetShipCameraAy(115.0);
		
		DoQuestCheckDelay("SharlieTutorial_StartGame", 4.0);
	}
	else
	{
		if(startHeroType == 4) ch.Ship.Type = GenerateShipExt(SHIP_SCHOONER_W, 0, ch);//элен
		else ch.Ship.Type = GenerateShipExt(sti(ch.StartShip), 0, ch);//остальные
		SetBaseShipData(ch);
		DeleteAttribute(ch, "StartShip");
		ch.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
		if(startHeroType == 4)
		{
			RealShips[sti(ch.Ship.Type)].MaxCaliber = 18;
			//RealShips[sti(ch.Ship.Type)].CannonsQuantity = 10;
			RealShips[sti(ch.Ship.Type)].MinCrew = 13;
			RealShips[sti(ch.Ship.Type)].OptCrew = 96;
			RealShips[sti(ch.Ship.Type)].MaxCrew = 120;
			RealShips[sti(ch.Ship.Type)].SpeedRate = 15.00;
			RealShips[sti(ch.Ship.Type)].TurnRate = 60.00;
			RealShips[sti(ch.Ship.Type)].Capacity = 1500;
			RealShips[sti(ch.Ship.Type)].HP = 1600;
			SetCrewQuantity(ch, GetMaxCrewQuantity(ch));
		}
		if(startHeroType == 4) ch.Ship.Name = StringFromKey("RPGUtilite_22");
		else ch.Ship.Name = StringFromKey("RPGUtilite_23");
		/* RealShips[sti(ch.Ship.Type)].MinCrew = 3;
		RealShips[sti(ch.Ship.Type)].OptCrew = 12;
		RealShips[sti(ch.Ship.Type)].MaxCrew = 15;
		RealShips[sti(ch.Ship.Type)].SpeedRate = 11.50;
		RealShips[sti(ch.Ship.Type)].TurnRate = 74.00;
		RealShips[sti(ch.Ship.Type)].HP = 400; */
		/* UpgradeShipParameter(ch, "SpeedRate");
		UpgradeShipParameter(ch, "TurnRate");
		UpgradeShipParameter(ch, "WindAgainstSpeed");
		UpgradeShipParameter(ch, "HP");
		UpgradeShipParameter(ch, "MaxCrew"); */
		//if(startHeroType != 4) UpgradeShipFull(ch);
		/* if(CheckAttribute(&RealShips[sti(ch.Ship.Type)], "Tuning.Capacity"))
		{
			DegradeShipParameter(ch, "Capacity");
			DeleteAttribute(&RealShips[sti(ch.Ship.Type)],"DontTuning.Capacity");
			DeleteAttribute(&RealShips[sti(ch.Ship.Type)],"Tuning.Capacity");
		}
		RealShips[sti(ch.Ship.Type)].Capacity = 334;
		UpgradeShipParameter(ch, "Capacity"); */
		SetCrewQuantity(ch, GetMinCrewQuantity(ch));
		SetCharacterGoods(ch, GOOD_BALLS, 50);
		SetCharacterGoods(ch, GOOD_GRAPES, 50);
		SetCharacterGoods(ch, GOOD_KNIPPELS, 50);
		SetCharacterGoods(ch, GOOD_BOMBS, 0);
		SetCharacterGoods(ch, GOOD_FOOD, 150);
		SetCharacterGoods(ch, GOOD_POWDER, 150);
		SetCharacterGoods(ch, GOOD_WEAPON, 30);
		SetCharacterGoods(ch, GOOD_MEDICAMENT, 50);
		SetCharacterGoods(ch, GOOD_RUM, 100);
		if(startHeroType == 4) SetCharacterGoods(ch, GOOD_SANDAL, 50);
		/* if(startHeroType == 4) ch.Skill.Sailing = 45;
		else ch.Skill.Sailing = 1; */
		bWorldAlivePause = false;
		// коцаем корабль
		// ch.ship.SP = sti(ch.ship.SP) - 10; <-- этот код не имеет смысла
		//ch.ship.HP = sti(ch.ship.HP) - makeint(sti(ch.ship.HP)/2);
		//Tutorial - НАЧАЛО ИГРЫ
	    ch.quest.Tut_start.win_condition.l1          = "location";
	    ch.quest.Tut_start.win_condition.l1.location = "Ship_deck_Low";
	    ch.quest.Tut_start.function                  = "Tut_StartGame";
		ch.questTemp.StatusCity = ch.HeroParam.ToCityId;
		ch.systeminfo.tutorial.firstfight1_SandBox = true;
		ch.systeminfo.tutorial.firstSea_SandBox = true;
		ch.systeminfo.tutorial.firstSeaBattle_SandBox = true;
		ch.systeminfo.tutorial.navigator = true;
		ch.quest.Tut_WorldMap.win_condition.l1          = "MapEnter";
	    ch.quest.Tut_WorldMap.function                  = "Tutorial_WorldMap";
		SetFunctionTimerCondition("Tutorial_Salary", 0, 0, 28, true);
		ch.quest.Tutorial_Dubloons.win_condition.l1 = "item";
		ch.quest.Tutorial_Dubloons.win_condition.l1.item = "gold_dublon";
		ch.quest.Tutorial_Dubloons.function = "Tutorial_Dubloons";
		ch.quest.Tutorial_Mushket.win_condition.l1 = "ItemGroup";
		ch.quest.Tutorial_Mushket.win_condition.l1.group = MUSKET_ITEM_TYPE;
		ch.quest.Tutorial_Mushket.function = "Tutorial_Mushket";
		ch.quest.Tutorial_Box.win_condition.l1 = "My_Cabine";
		ch.quest.Tutorial_Box.function = "Tutorial_Box";
		ch.systeminfo.tutorial.health = true;
		ch.systeminfo.tutorial.Amulet = true;
		ch.systeminfo.tutorial.Perk = true;
		ch.systeminfo.tutorial.Fighter = true;
		if(startHeroType == 4)
		{
			SetItemInLocation("pirate_cutlass", "Pirates_townhall_upstairs", "item1");
			locations[FindLocation("Pirates_townhall_upstairs")].locators_radius.item.item1 = 1.0;
			DeleteAttribute(&locations[FindLocation("Pirates_town")],"reload.l3.disable"); //открыть резиденцию на ИТ
			DeleteAttribute(&locations[FindLocation("SantaCatalina_houseSp3_bedroom")],"box1.QuestClosed"); //открыть резиденцию на ИТ
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.obereg_7 = 1;
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.obereg_9 = 1;
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.obereg_10 = 1;
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.obereg_11 = 1;
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.amulet_5 = 1;
		}
		
		// SetCurrentTime(11,30); // вытавим время и отменим дождь
		WeatherParams.Rain 			= false;
		WeatherParams.Rain.ThisDay 	= false;
	}	
	// Warship Для разных квестов
	// Важно: функция MaryCelesteInit() должна быть тут, а не в initStartState2Character()
	// т.к. в ней идёт выборка колоний, которые в функции initStartState2Character() ещё не инитились
	OtherQuestCharactersInit(); // Инициализация прочих квестов
	MaryCelesteInit(); // Warship 07.07.09 Пасхалка "Мэри Селест"
	ChickenGod_PreInit();
}

void initMainCharacterItem()
{
    ref ch = GetMainCharacter();
	String itemID;
	
	ch.systeminfo.NoNotifications = true;
	switch (ch.HeroParam.HeroType)
	{
		case "HeroType_1":
			itemID = GetGeneratedItem("blade_09");	// карцолетта
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
			TakenItems(ch, "jewelry3", 1);
			TakenItems(ch, "jewelry42", 1);
			TakenItems(ch, "jewelry43", 2);
			TakenItems(ch, "jewelry46", 3);
         	ch.money = 500;		
		break;
		
		case "HeroType_2":
			itemID = GetGeneratedItem("blade_12");	// полусабля
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
			TakenItems(ch, "jewelry3", 2);
			TakenItems(ch, "jewelry42", 2);
			TakenItems(ch, "jewelry43", 4);
			TakenItems(ch, "jewelry46", 6);
         	ch.money = 500;
		break;
		
		case "HeroType_3":
			itemID = GetGeneratedItem("blade_14");	// валлонская шпага
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
			TakenItems(ch, "jewelry3", 1);
			TakenItems(ch, "jewelry42", 1);
			TakenItems(ch, "jewelry43", 2);
			TakenItems(ch, "jewelry46", 3);
         	ch.money = 500;				
		break;
		
		case "HeroType_4":
			itemID = GetGeneratedItem("blade_08");	// бильбо
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);			
			AddItems(ch, "pistol3", 1);
			EquipCharacterbyItem(ch, "pistol3");			
			AddItems(ch, "grapeshot", 5);
			AddItems(ch, "gunpowder", 5);
			LAi_SetCharacterUseBullet(ch, GUN_ITEM_TYPE, "grapeshot");
			TakenItems(ch, "jewelry3", 1);
			TakenItems(ch, "jewelry42", 1);
			TakenItems(ch, "jewelry43", 2);
			TakenItems(ch, "jewelry46", 3);
         	ch.money = 500;
		break;
	}
	if(GetDLCenabled(DLC_APPID_1) && startHeroType == 1)
	{
		AddItems(ch, "knife_03", 1);
	}
	DeleteAttribute(ch,"systeminfo.NoNotifications");
}

void initMainFreePlayCharacterItem()
{
    ref ch = GetMainCharacter();
	String itemID;
	ch.systeminfo.NoNotifications = true;
	switch (ch.HeroParam.HeroType)
	{
		case "HeroType_1":
			itemID = GetGeneratedItem("blade_08");	// бильбо
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
			AddItems(ch, "potion5", 3);
			AddItems(ch, "potionrum", 2);
			AddItems(ch, "potion1", 1);
			AddItems(ch, "potion2", 1);
         	ch.money = 3500;		
		break;
		
		case "HeroType_2":
			itemID = GetGeneratedItem("slave_02");	// мачете
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
			AddItems(ch, "potionrum", 2);
			AddItems(ch, "potion1", 3);
			AddItems(ch, "potion2", 1);
         	ch.money = 5000;
		break;
		
		case "HeroType_3":
			itemID = GetGeneratedItem("topor_05");	// томагавк
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
			AddItems(ch, "potion5", 4);
			AddItems(ch, "potionrum", 1);
			AddItems(ch, "potionwine", 1);
         	ch.money = 2500;				
		break;
		
		case "HeroType_4":
			itemID = GetGeneratedItem("slave_01");	// гарпун
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);			
			AddItems(ch, "pistol3", 1);
			EquipCharacterbyItem(ch, "pistol3");
			AddItems(ch, "pistol1", 1);			
			AddItems(ch, "grapeshot", 5);
			AddItems(ch, "bullet", 5);
			AddItems(ch, "gunpowder", 10);
			AddItems(ch, "ArmoryPaper", 2);
			LAi_SetCharacterUseBullet(ch, GUN_ITEM_TYPE, "grapeshot");
			AddItems(ch, "potion5", 3);
			AddItems(ch, "potionrum", 3);
			AddItems(ch, "potion1", 1);
         	ch.money = 2000;				
		break;
	}
	aref item;
	Items_FindItem("map_full", &item);
	FillMapForTreasure(item, "");
	GiveItem2Character(ch, "map_full");
	AddMapToPlayerAtlas("map_normal");
	//AddItems(ch, "obereg_8", 1);
	//AddItems(ch, "amulet_7", 1);
	//AddItems(ch, "obereg_4", 1);
	//AddItems(ch, "talisman2", 1);
	//AddItems(ch, "gold_dublon", 20);
	//AddItems(ch, "alchemy_tool", 1);
	AddItems(ch, "Tailor_Tool", 1);
	AddItems(ch, "Mechanic_Tool", 1);
	AddItems(ch, "spyglass1", 1);
	
	SetCharacterPerk(ch, "FlagHol");
	//GiveNationLicence(HOLLAND, 180);
	ch.alchemy.known = 1;
	AddQuestRecordInfo_Silent("Recipe", "cartridge");
	SetAlchemyRecipeKnown_Silent("cartridge");
    AddQuestRecordInfo_Silent("Recipe", "clock2");
	SetAlchemyRecipeKnown_Silent("clock2");
	if(GetDLCenabled(DLC_APPID_1) && startHeroType == 1)
	{
		AddItems(ch, "knife_03", 1);
	}
	DeleteAttribute(ch,"systeminfo.NoNotifications");
}

int GetNewMainCharacterFace()
{
    return sti(GetNewMainCharacterParam("heroFace_" + startHeroType));
}

string GetNewMainCharacterName()
{
    return GetHeroName(startHeroType);
}

string GetMainCharacterNameGen()  // ==> eddy. родительный падеж полного имени ГГ
{
    return GetHeroNameGen(startHeroType);
}

string GetMainCharacterNameDat()  // ==> eddy. дательный падеж полного имени ГГ
{
    return GetHeroNameDat(startHeroType);
}

string GetHeroName(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroName_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastname_" + _n);

    return totalInfo;
}

string GetHeroNameGen(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameGen_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameGen_" + _n);

    return totalInfo;
}

string GetHeroNameDat(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameDat_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameDat_" + _n);

    return totalInfo;
}

int GetNewMainCharacterNation(int _startHeroType)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, "heroNation_" + _startHeroType);
    LanguageCloseFile(idLngFile);

    switch(totalInfo)
	{
		case "Англия":
            return ENGLAND;
		break;
		case "Франция":
            return FRANCE;
		break;
		case "Испания":
            return SPAIN;
		break;
		case "Голландия":
			return HOLLAND;
		break;
		case "Береговое братство":
			return PIRATE;
		break;

		case "ENGLAND":
            return ENGLAND;
		break;
		case "FRANCE":
            return FRANCE;
		break;
		case "SPAIN":
            return SPAIN;
		break;
		case "HOLLAND":
			return HOLLAND;
		break;
		case "PIRATE":
			return PIRATE;
		break;
	}
	return PIRATE;
}

string GetNewMainCharacterParam(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}


void CCS_SetNewMainCharacter(ref ch, int num)
{
	if(num < 1) num = 1;
	switch (num)
	{
		case 1: //Шарль де Мор
			ch.FaceId 				= 201;
			ch.HeroModel 			= "Sharle_1,Sharle_2,Sharle_3,Sharle_4,Sharle_5,protocusto,Sharle_6,Sharle_8,Sharle_7,Sharle_9,Sharle_1,Sharle_11,Sharle_12,Sharle_13,Sharle_14,Sharle_15";
			ch.name 				= GetNewMainCharacterParam("heroName_1");
			ch.lastname				= GetNewMainCharacterParam("heroLastname_1");
			ch.nameGen				= GetNewMainCharacterParam("heroNameGen_1");
			ch.lastnameGen			= GetNewMainCharacterParam("heroLastnameGen_1");
			ch.nameDat				= GetNewMainCharacterParam("heroNameDat_1");
			ch.lastnameDat			= GetNewMainCharacterParam("heroLastNameDat_1");
			ch.sex					= "man";
			ch.model.animation 		= "Sharle_1";
			ch.HeroParam.HeroType 	= "HeroType_1";
			ch.nation				= FRANCE;
			ch.BaseNation			= FRANCE;
			ch.info					= GetNewMainCharacterParam("hero_1");
		break;
		case 2: // Диего  де Монтойя
//			return;			
			
			ch.FaceId 				= 203;
			ch.HeroModel 			= "Diego_1,Diego_2,Diego_3,Diego_4,Diego_5,protocusto,Diego_6,Diego_8,Diego_1,Diego_9,Diego_1,Diego_11,Diego_12,Diego_13,Diego_14,Diego_15";
			ch.name 				= GetNewMainCharacterParam("heroName_2");
			ch.lastname				= GetNewMainCharacterParam("heroLastname_2");
			ch.nameGen				= GetNewMainCharacterParam("heroNameGen_2");
			ch.lastnameGen			= GetNewMainCharacterParam("heroLastnameGen_2");
			ch.nameDat				= GetNewMainCharacterParam("heroNameDat_2");
			ch.lastnameDat			= GetNewMainCharacterParam("heroLastNameDat_2");
			ch.sex					= "man";
			ch.model.animation 		= "Diego_1";
			ch.HeroParam.HeroType 	= "HeroType_3";
			ch.nation				= SPAIN;
			ch.BaseNation			= SPAIN;
			ch.info					= GetNewMainCharacterParam("hero_2");
		break;		
		case 3: // Паттерсон
//			return;
			
			ch.FaceId 				= 202;
			ch.HeroModel 			= "Willy_1,Willy_2,Willy_3,Willy_4,Willy_5,protocusto,Willy_6,Willy_8,Willy_1,Willy_9,Willy_1,Willy_11,Willy_12,Willy_13,Willy_14,Willy_15";
			ch.name 				= GetNewMainCharacterParam("heroName_3");
			ch.lastname				= GetNewMainCharacterParam("heroLastname_3");
			ch.nameGen				= GetNewMainCharacterParam("heroNameGen_3");
			ch.lastnameGen			= GetNewMainCharacterParam("heroLastnameGen_3");
			ch.nameDat				= GetNewMainCharacterParam("heroNameDat_3");
			ch.lastnameDat			= GetNewMainCharacterParam("heroLastNameDat_3");
			ch.sex					= "man";
			ch.model.animation 		= "Willy_1";
			ch.HeroParam.HeroType 	= "HeroType_2";
			ch.nation				= ENGLAND;
			ch.BaseNation			= ENGLAND;
			ch.info 				= GetNewMainCharacterParam("hero_3");
		break;
		case 4: // Элен
//			return;
			
			ch.FaceId 				= 250;
			ch.HeroModel 			= "Rumba";
			ch.name 				= GetNewMainCharacterParam("heroName_4");
			ch.lastname				= GetNewMainCharacterParam("heroLastname_4");
			ch.nameGen				= GetNewMainCharacterParam("heroNameGen_4");
			ch.lastnameGen			= GetNewMainCharacterParam("heroLastnameGen_4");
			ch.nameDat				= GetNewMainCharacterParam("heroNameDat_4");
			ch.lastnameDat			= GetNewMainCharacterParam("heroLastNameDat_4");
			ch.sex					= "woman";
			ch.model.animation 		= "rumba";
			ch.HeroParam.HeroType 	= "HeroType_1";
			ch.nation				= ENGLAND;
			ch.BaseNation			= ENGLAND;
			ch.info 				= GetNewMainCharacterParam("hero_4");
		break;
	}	
	
	ch.model = GetSubStringByNum(ch.HeroModel, 0);
	ch.cirassIDX = 0;
	
	if(ch.sex == "woman")
	{
		ch.model.height = 1.75;
	}
    else
    {
		ch.model.height = 1.8;
	}
}

int CCS_GetNewMainCharacterFace(ref ch)
{
    return sti(ch.FaceId);
}

// boal 091004 много героев  -->
// boal 23.01.2004 выбор персонажа-->
void setNewMainCharacter(ref ch, int num)
{
	string heroModel, heroFaceId;
	int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    totalInfo = LanguageConvertString(idLngFile, "heroFace_" + num);
    heroFaceId  = sti(totalInfo);
    ch.FaceId   = heroFaceId;

    totalInfo = LanguageConvertString(idLngFile, "heroModel_" + num);
    ch.HeroModel = totalInfo;
    ch.model	= GetSubStringByNum(ch.HeroModel, 0);
    ch.headModel = "h_" + ch.model;

    totalInfo = LanguageConvertString(idLngFile, "heroName_" + num);
    ch.name 	=  totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "heroLastname_" + num);
    ch.lastname = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "sex_" + num);
    ch.sex = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "animation_" + num);
    ch.model.animation = totalInfo;

    if(ch.sex == "woman")
	{
		ch.model.height = 1.75;
	}
    else
    {
		ch.model.height = 1.8;
	}

    LanguageCloseFile(idLngFile);
    // для НПС
    ch.HeroParam.HeroType = GetNewMainCharacterType(num);
    ch.nation             = GetNewMainCharacterNation(num);
}

string GetNewMainCharacterType(int _startHeroType)
{
	string ret;
    switch (_startHeroType) 
	{
        case 1:
    	    ret = "HeroType_1";
	    break;
        case 2:
    	    ret = "HeroType_2";
	    break;
        case 3:
    	    ret = "HeroType_3";
	    break;
        case 4:
    	    ret = "HeroType_4";
	    break;	    
	}
	return ret;
}

void InitRPGType()
{
    NullCharacter.SPECIALType.Strength = true;
    NullCharacter.SPECIALType.Perception = true;
    NullCharacter.SPECIALType.Endurance = true;
    NullCharacter.SPECIALType.Charisma = true;
    NullCharacter.SPECIALType.Intellect = true;
    NullCharacter.SPECIALType.Agility = true;
    NullCharacter.SPECIALType.Luck = true;
    
    NullCharacter.SelfType.Leadership = true;
	NullCharacter.SelfType.FencingL = true;
    NullCharacter.SelfType.FencingS = true;
    NullCharacter.SelfType.FencingH = true;
    NullCharacter.SelfType.Pistol = true;
    NullCharacter.SelfType.Fortune = true;
    NullCharacter.SelfType.Sneak = true;
    // остальные корабельные
    NullCharacter.ShipType.Commerce = true;
    NullCharacter.ShipType.Accuracy = true;
    NullCharacter.ShipType.Cannons = true;
    NullCharacter.ShipType.Sailing = true;
    NullCharacter.ShipType.Repair = true;
    NullCharacter.ShipType.Grappling = true;
    NullCharacter.ShipType.Defence = true;

}

// по специал распередить скилы
void InitStartParam(ref _chref)
{
    int i;
    string  skillName;
    
    ClearCharacterExpRate(_chref);
    
    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        _chref.skill.(skillName) = makeint(MOD_EXP_RATE / GetCharacterExpRate(_chref, skillName) + 0.5);
    }
    LAi_SetHP(_chref, GetCharacterBaseHPValue(_chref), GetCharacterBaseHPValue(_chref));
}

int GetHPIncrease(ref chr) {
	// --> убрать влияние кирас
	int Ers = GetCharacterSPECIALSimple(chr, SPECIAL_E);
	if (GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "underwater") Ers = Ers+2;
	if (GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "cirass1") Ers = Ers+1;
	if (GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "cirass2") Ers = Ers+1;
	if (GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "cirass4") Ers = Ers+1;
	// <-- убрать влияние кирас

	int ret = makeint(2 + Ers * 0.55 + 0.5);
	
	return ret * (sti(chr.rank) - 1);
}