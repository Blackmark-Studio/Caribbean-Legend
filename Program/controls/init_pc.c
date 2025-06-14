
void ExternControlsInit(bool bFirst, bool bClassic)
{
	//Trace("ExternControlsInit");
    ExternInitKeyCodes();

	if(bFirst)
	{
		CI_CreateAndSetControls("", "ICancel", CI_GetKeyCode("VK_ESCAPE"), 0, false);
		CI_CreateAndSetControls("", "IAction", CI_GetKeyCode("VK_SPACE"),  0, false);
		return;
	}

	if(bClassic) CI_CreateAndSetControls("", "Map_Best", CI_GetKeyCode("KEY_N"), 0, true); // Отличная карта
	else if (MOD_BETTATESTMODE == "On") CI_CreateAndSetControls("", "Map_Best", CI_GetKeyCode("KEY_N"), 0, true); // Отличная карта

	CI_CreateAndSetControls("", "BOAL_Control", CI_GetKeyCode("VK_F11"), 0, false);
    CI_CreateAndSetControls("", "BOAL_Control2", CI_GetKeyCode("VK_F12"), 0, false);
    CI_CreateAndSetControls("", "BOAL_SetCamera", CI_GetKeyCode("VK_F10"), 0, false); // Здесь можно прописать команды дебагера для быстрого выполнения в реальном времени
    CI_CreateAndSetControls("", "BOAL_ControF7", CI_GetKeyCode("VK_F7"), 0, false); // убить ближайшего персонажа
    CI_CreateAndSetControls("", "BOAL_ControlDebug", CI_GetKeyCode("VK_INSERT"), 0, false);
    
    CI_CreateAndSetControls("", "TimeScaleFaster", CI_GetKeyCode("VK_ADD"), 0, false);
    CI_CreateAndSetControls("", "TimeScaleSlower", CI_GetKeyCode("VK_SUBTRACT"), 0, false);
	CI_CreateAndSetControls("", "VK_PAUSETimePause", CI_GetKeyCode("VK_PAUSE"), 0, false);
	
	CI_CreateAndSetControls("", "ChangeShowInterface", CI_GetKeyCode("VK_DIVIDE"), 0, true);
	// для тестовых нужд - пока не убирать !!
	CI_CreateAndSetControls("", "TestShipCurrentSea", CI_GetKeyCode("VK_DECIMAL"), 0, true);
	
	if (MOD_BETTATESTMODE == "On")
	{
		CI_CreateAndSetControls("", "BOAL_ControF5", CI_GetKeyCode("VK_F5"), 0, false); //Дамп аттрибутов ближайшего персонажа
		// weather
		CI_CreateAndSetControls("", "WhrPrevWeather", CI_GetKeyCode("VK_L_BREAKE"), 0, false);
		CI_CreateAndSetControls("", "WhrNextWeather", CI_GetKeyCode("VK_R_BREAKE"), 0, false);
		CI_CreateAndSetControls("", "WhrUpdateWeather", CI_GetKeyCode("VK_A_QUOTE"), 0, false);
		//CI_CreateAndSetControls("", "Tele", CI_GetKeyCode("VK_A_POINT"), 0, false);

		//wind
		CI_CreateAndSetControls("", "WindIncrease", CI_GetKeyCode("VK_NUMPAD8"), 0, true );
		CI_CreateAndSetControls("", "WindDecrease", CI_GetKeyCode("VK_NUMPAD5"), 0, true );
		CI_CreateAndSetControls("", "WindAngleIncrease", CI_GetKeyCode("VK_NUMPAD4"), 0, true );
		CI_CreateAndSetControls("", "WindAngleDecrease", CI_GetKeyCode("VK_NUMPAD6"), 0, true );

		CI_CreateAndSetControls("", "CoastFoamLB", CI_GetKeyCode("VK_LBUTTON"), 0, true);
		CI_CreateAndSetControls("", "CoastFoamRB", CI_GetKeyCode("VK_RBUTTON"), 0, true);
		CI_CreateAndSetControls("", "CoastFoamINS", CI_GetKeyCode("VK_INSERT"), 0, true);
		CI_CreateAndSetControls("", "CoastFoamDEL", CI_GetKeyCode("VK_DELETE"), 0, true);
		CI_CreateAndSetControls("", "CoastFoamCopy", CI_GetKeyCode("KEY_C"), 0, true);
		CI_CreateAndSetControls("", "FreeCam", CI_GetKeyCode("KEY_0"), 0, true);
	}

// Character ===================================================================
	CI_CreateAndSetControls("", "ChrTurnH", 256, 0, false);
	CI_CreateAndSetControls("PrimaryLand", "ChrForward", CI_GetKeyCode("KEY_W"), 0, true);
	CI_CreateAndSetControls("PrimaryLand", "ChrForward2", CI_GetKeyCode("VK_RBUTTON"), 0, true); // вторая команда
	//CI_CreateAndSetControls("PrimaryLand", "ChrJump", CI_GetKeyCode("KEY_T"), 0, true);
	AddControlToGroups("ChrForward", "FightModeControls", "BattleInterfaceControls", "", "");
	CI_CreateAndSetControls("PrimaryLand", "ChrBackward", CI_GetKeyCode("KEY_S"), 0, true);
	AddControlToGroups("ChrBackward", "FightModeControls", "BattleInterfaceControls", "", "");
	CI_CreateAndSetControls("PrimaryLand", "ChrStrafeLeft", CI_GetKeyCode("KEY_A"), 0, true);
	AddControlToGroups("ChrStrafeLeft", "FightModeControls", "BattleInterfaceControls", "", "");
	CI_CreateAndSetControls("PrimaryLand", "ChrStrafeRight", CI_GetKeyCode("KEY_D"), 0, true);
	AddControlToGroups("ChrStrafeRight", "FightModeControls", "BattleInterfaceControls", "", "");

    /* CI_CreateAndSetControls( "PrimaryLand", "ChrTurnHL", CI_GetKeyCode("KEY_A"), 0, true );
	AddControlToGroups("ChrTurnHL", "FightModeControls", "BattleInterfaceControls", "", "");
	CI_CreateAndSetControls( "PrimaryLand", "ChrTurnHR", CI_GetKeyCode("KEY_D"), 0, true );
	AddControlToGroups("ChrTurnHR", "FightModeControls", "BattleInterfaceControls", "", ""); */

    //CI_CreateAndSetControls("PrimaryLand", "ChrRun", CI_GetKeyCode("VK_SHIFT"), USE_AXIS_AS_BUTTON, true);
	//AddControlToGroups("ChrRun", "FightModeControls", "BattleInterfaceControls", "", "");
	CI_CreateAndSetControls("PrimaryLand", "ChrSwitchWalk", CI_GetKeyCode("VK_CONTROL"), 0, true); // evganat - переключатель бега
	MapControlToGroup("ChrSwitchWalk","FightModeControls");
	MapControlToGroup("ChrSwitchWalk","BattleInterfaceControls");
	CI_CreateAndSetControls("PrimaryLand", "ChrSprint", CI_GetKeyCode("VK_SHIFT"), 0, true);
	MapControlToGroup("ChrSprint","FightModeControls");
	MapControlToGroup("ChrSprint","BattleInterfaceControls");

	CI_CreateAndSetControls("PrimaryLand", "ChrFightMode", CI_GetKeyCode("KEY_E"), 0, true);
	// evganat - мушкеты
    CI_CreateAndSetControls( "PrimaryLand", "ChrSwitchFightMode", CI_GetKeyCode("KEY_2"), 0, true );
	MapControlToGroup("ChrSwitchFightMode", "FightModeControls");
	
	// evganat - ПРИЦЕЛИВАНИЕ
	CI_CreateAndSetControls("FightModeControls", "ChrAiming", CI_GetKeyCode("KEY_Q"), 0, true);
    CI_CreateAndSetControls("FightModeControls", "ChrFire", CI_GetKeyCode("KEY_Q"), 0, true);
	CI_CreateAndSetControls("FightModeControls", "ChrAimingShot", CI_GetKeyCode("VK_LBUTTON"), 0, true);
    MapControlToGroup("ChrFire","BattleInterfaceControls");

	// evganat - камера
	CI_CreateAndSetControls("PrimaryLand", "SwitchCameraOffset", CI_GetKeyCode("VK_TAB"), 0, true);
	MapControlToGroup("SwitchCameraOffset", "FightModeControls");

	CI_CreateAndSetControls("PrimaryLand", "CharacterCamera_Forward", CI_GetKeyCode("VK_MWHEEL_UP"), 0, true);
	MapControlToGroup("CharacterCamera_Forward", "FightModeControls");
	CI_CreateAndSetControls("PrimaryLand", "CharacterCamera_Backward", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, true);
	MapControlToGroup("CharacterCamera_Backward", "FightModeControls")

	// CI_CreateAndSetControls( "PrimaryLand", "ChrCamNormalize", CI_GetKeyCode("KEY_Y"), 0, true );
	// fight
	CI_CreateAndSetControls("FightModeControls", "ChrAltAttackBase", CI_GetKeyCode("VK_LBUTTON"), 0, true);   //2
	CI_CreateAndSetControls("FightModeControls", "ChrAttackBreakBase", CI_GetKeyCode("VK_MBUTTON"), 0, true); 
	CI_CreateAndSetControls("FightModeControls", "ChrAttackBase", CI_GetKeyCode("VK_RBUTTON"), 0, true);   //1
	CI_CreateAndSetControls("FightModeControls", "ChrAttackChoseBase", CI_GetKeyCode("VK_SHIFT"), 0, true);
	CI_CreateAndSetControls("FightModeControls", "ChrBlock", CI_GetKeyCode("VK_SPACE"), 0, true);
	//belamour альтернативные клавиши --->
	CI_CreateAndSetControls("FightModeControls", "ChrAttackFient", CI_GetKeyCode("KEY_Z"), 0, true);// финт
	CI_CreateAndSetControls("FightModeControls", "ChrParry", CI_GetKeyCode("KEY_C"), 0, true); //парирование
    //<--- belamour
	CI_CreateAndSetControls("FightModeControls", "ChrFightMode", CI_GetKeyCode("KEY_E"), 0, true);
	MapControlToGroup("ChrFightMode","BattleInterfaceControls");

    // boal -->
	CI_CreateAndSetControls("PrimaryLand", "BOAL_UsePotion", CI_GetKeyCode("KEY_X"), 0, true); // Warship 13.06.09 Дефолтом перевесил на "C" // belamour всё же на X
	MapControlToGroup("BOAL_UsePotion","FightModeControls");
	// боеприпасы и лечебные зелья
	CI_CreateAndSetControls("PrimaryLand", "BulletChanger", CI_GetKeyCode("KEY_B"), 0, true);
	MapControlToGroup("BulletChanger", "FightModeControls");
	CI_CreateAndSetControls("PrimaryLand", "PotionChanger", CI_GetKeyCode("KEY_X"), 0, true);
	MapControlToGroup("PotionChanger", "FightModeControls");
	MapControlToGroup("PotionChanger", "AltPressedGroup");
	
	// Warship 13.06.09 Выпить противоядие
	CI_CreateAndSetControls("PrimaryLand", "UseAntidote", CI_GetKeyCode("KEY_V"), 0, true);
	MapControlToGroup("UseAntidote", "FightModeControls");
	 // выпить зелье команчей
	if(bClassic) CI_CreateAndSetControls("PrimaryLand", "Ultimate_potion", CI_GetKeyCode("KEY_U"), 0, true);
	else CI_CreateAndSetControls("PrimaryLand", "Ultimate_potion", CI_GetKeyCode("KEY_3"), 0, true);
	MapControlToGroup("Ultimate_potion","BattleInterfaceControls");

    if(bClassic) CI_CreateAndSetControls("PrimaryLand", "BOAL_DeadSearch", CI_GetKeyCode("KEY_1"), 0, true);
    else CI_CreateAndSetControls("PrimaryLand", "BOAL_DeadSearch", CI_GetKeyCode("KEY_F"), 0, true);
	MapControlToGroup("BOAL_DeadSearch","FightModeControls");
	
	// мушкет и клинки
	/* if(bClassic) {
		CI_CreateAndSetControls("PrimaryLand", "HK_Musket",   CI_GetKeyCode("KEY_2"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "HK_FencingL", CI_GetKeyCode("KEY_3"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "HK_FencingS", CI_GetKeyCode("KEY_4"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "HK_FencingH", CI_GetKeyCode("KEY_5"), 0, true);
	} else {
		CI_CreateAndSetControls("PrimaryLand", "HK_Musket",   CI_GetKeyCode("KEY_3"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "HK_FencingL", CI_GetKeyCode("KEY_4"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "HK_FencingS", CI_GetKeyCode("KEY_5"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "HK_FencingH", CI_GetKeyCode("KEY_6"), 0, true);
	}	 */
	// <-- belamour		
	
	if(bClassic) CI_CreateAndSetControls("FightModeControls", "BOAL_ActivateRush", CI_GetKeyCode("KEY_F"), 0, true); // boal ярость на суше
	else CI_CreateAndSetControls("FightModeControls", "BOAL_ActivateRush", CI_GetKeyCode("KEY_1"), 0, true);
	// boal <--
	
	//Jonathan A 2009-08-19 -->
	if(bClassic) CI_CreateAndSetControls("PrimaryLand", "OfficersCharge", CI_GetKeyCode("KEY_J"), 0, true);
	else CI_CreateAndSetControls("PrimaryLand", "OfficersCharge", CI_GetKeyCode("KEY_7"), 0, true);
	MapControlToGroup("OfficersCharge","FightModeControls");
	MapControlToGroup("OfficersCharge","BattleInterfaceControls");

	if(bClassic) CI_CreateAndSetControls("PrimaryLand", "OfficersHold", CI_GetKeyCode("KEY_H"), 0, true);
	else CI_CreateAndSetControls("PrimaryLand", "OfficersHold", CI_GetKeyCode("KEY_8"), 0, true);
	MapControlToGroup("OfficersHold","FightModeControls");
	MapControlToGroup("OfficersHold","BattleInterfaceControls");

	if(bClassic) CI_CreateAndSetControls("PrimaryLand", "OfficersFollow", CI_GetKeyCode("KEY_G"), 0, true);
	else CI_CreateAndSetControls("PrimaryLand", "OfficersFollow", CI_GetKeyCode("KEY_9"), 0, true);
	MapControlToGroup("OfficersFollow","FightModeControls");
	MapControlToGroup("OfficersFollow","BattleInterfaceControls");
	// <-- JA
	CI_CreateAndSetControls("", "LanternOnOff", CI_GetKeyCode("KEY_L"), 0, true); // включить/выключить фонарь
	
	CI_CreateAndSetControls("PrimaryLand", "Dolly", CI_GetKeyCode("KEY_T"), 0, true); // активировать телепортацию
	MapControlToGroup("Dolly","BattleInterfaceControls");
	
	//CI_CreateContainer("", "ChrTurnH1", 15.0);
	//MapControlToGroup("ChrTurnH1","FightModeControls");
	//MapControlToGroup("ChrTurnH1","BattleInterfaceControls");
	//AddToContainer("PrimaryLand", "ChrTurnH1", "TmpChrTurn1", CI_GetKeyCode("KEY_D"), 0, false);
	//MapControlToGroup("TmpChrTurn1","FightModeControls");
	//AddToContainer("PrimaryLand", "ChrTurnH1", "TmpChrTurn2", CI_GetKeyCode("KEY_A"), 0, true);
	//MapControlToGroup("TmpChrTurn2","FightModeControls");

	MapControlToGroup("ChrBlock","BattleInterfaceControls");
	

// Ship ========================================================================
	CI_CreateAndSetControls("Sailing3Pers", "Ship_SailUp", CI_GetKeyCode("KEY_W"), 0, true);
	AddControlToGroups("Ship_SailUp", "Sailing1Pers", "WorldMapControls", "SailingFire", "");
	CI_CreateAndSetControls("Sailing3Pers", "Ship_SailDown", CI_GetKeyCode("KEY_S"), 0, true);
	AddControlToGroups("Ship_SailDown", "Sailing1Pers", "WorldMapControls", "SailingFire", "");
	CI_CreateAndSetControls("Sailing3Pers", "Ship_TurnLeft", CI_GetKeyCode("KEY_A"), 0, true);
	AddControlToGroups("Ship_TurnLeft", "Sailing1Pers", "WorldMapControls", "SailingFire", "");
	CI_CreateAndSetControls("Sailing3Pers", "Ship_TurnRight", CI_GetKeyCode("KEY_D"), 0, true);
	AddControlToGroups("Ship_TurnRight", "Sailing1Pers", "WorldMapControls", "SailingFire", "");
	CI_CreateAndSetControls("Sailing3Pers", "Ship_Fire", CI_GetKeyCode("VK_LBUTTON"), 0, true);
	//MapControlToGroup("Ship_Fire","Sailing1Pers");
    MapControlToGroup("Ship_Fire","SailingFire");
	// belamour дополнительные кнопки для перков и перехода в каюту -->
	// переход в каюту
	CI_CreateAndSetControls("Sailing3Pers","hk_Cabin", CI_GetKeyCode("KEY_C"), 0, true);
	AddControlToGroups("hk_Cabin", "Sailing1Pers", "BattleInterfaceControls", "PrimaryLand", "SailingFire");
	// рендж пушек
	CI_CreateAndSetControls("Sailing3Pers", "CannonsRange", CI_GetKeyCode("KEY_Q"), 0, true);
    AddControlToGroups("CannonsRange", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// ремонт в бою 
	CI_CreateAndSetControls("Sailing3Pers","hk_InstantRepair", CI_GetKeyCode("KEY_Z"), 0, true);
    AddControlToGroups("hk_InstantRepair", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// неотложный ремонт (10% корпуса)
	CI_CreateAndSetControls("Sailing3Pers","hk_LightRepair", CI_GetKeyCode("KEY_X"), 0, true);
    AddControlToGroups("hk_LightRepair", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// манёвренный разворот
	CI_CreateAndSetControls("Sailing3Pers","hk_Turn180", CI_GetKeyCode("KEY_V"), 0, true);
    AddControlToGroups("hk_Turn180", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// предварительная перезарядка
	CI_CreateAndSetControls("Sailing3Pers","hk_ImmediateReload", CI_GetKeyCode("KEY_B"), 0, true);
    AddControlToGroups("hk_ImmediateReload", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// hot keys for cannon charge reload
		// Balls
	CI_CreateAndSetControls("Sailing3Pers","hk_charge1", CI_GetKeyCode("KEY_1"), 0, true);
    AddControlToGroups("hk_charge1", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
		// Grapes
	CI_CreateAndSetControls("Sailing3Pers","hk_charge2", CI_GetKeyCode("KEY_2"), 0, true);
    AddControlToGroups("hk_charge2", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
		// Knippels
	CI_CreateAndSetControls("Sailing3Pers","hk_charge3", CI_GetKeyCode("KEY_3"), 0, true);
    AddControlToGroups("hk_charge3", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
		// Bombs
	CI_CreateAndSetControls("Sailing3Pers","hk_charge4", CI_GetKeyCode("KEY_4"), 0, true);
    AddControlToGroups("hk_charge4", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// Эскадре - зарядить ядрами
	CI_CreateAndSetControls("Sailing3Pers", "FLT_LoadBalls", CI_GetKeyCode("KEY_5"), 0, true);
    AddControlToGroups("FLT_LoadBalls", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// Эскадре - зарядить картечью
	CI_CreateAndSetControls("Sailing3Pers", "FLT_LoadGrapes", CI_GetKeyCode("KEY_6"), 0, true);
    AddControlToGroups("FLT_LoadGrapes", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// Эскадре - зарядить книпелями
	CI_CreateAndSetControls("Sailing3Pers", "FLT_LoadChain", CI_GetKeyCode("KEY_7"), 0, true);
    AddControlToGroups("FLT_LoadChain", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// Эскадре - зарядить бомбами
	CI_CreateAndSetControls("Sailing3Pers", "FLT_LoadBombs", CI_GetKeyCode("KEY_8"), 0, true);
    AddControlToGroups("FLT_LoadBombs", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// Эскадре - свалить
	CI_CreateAndSetControls("Sailing3Pers", "FLT_SailAway", CI_GetKeyCode("KEY_O"), 0, true);
    AddControlToGroups("FLT_SailAway", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// Эскадре - паруса в боевое
	CI_CreateAndSetControls("Sailing3Pers", "FLT_LowerSails", CI_GetKeyCode("KEY_L"), 0, true);
    AddControlToGroups("FLT_LowerSails", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	// Всем - защита флагмана
	CI_CreateAndSetControls("Sailing3Pers", "FLT_ProtFlagship", CI_GetKeyCode("KEY_P"), 0, true);
    AddControlToGroups("FLT_ProtFlagship", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");

	CI_CreateAndSetControls("Sailing3Pers", "MiniMapZoomIn", CI_GetKeyCode("KEY_E"), 0, true);
    AddControlToGroups("MiniMapZoomIn", "Sailing1Pers", "SailingFire", "", "");

	if(bClassic) CI_CreateAndSetControls("Sailing3Pers", "MiniMapZoomOut", CI_GetKeyCode("KEY_F"), 0, true);
	else CI_CreateAndSetControls("Sailing3Pers", "MiniMapZoomOut", CI_GetKeyCode("KEY_T"), 0, true);
    AddControlToGroups("MiniMapZoomOut", "Sailing1Pers", "SailingFire", "", "");

	if(!bClassic)
    {
		CI_CreateAndSetControls("Sailing3Pers", "BI_MapEnter", CI_GetKeyCode("VK_SPACE"), 0, true);
		MapControlToGroup("BI_MapEnter","Sailing1Pers");
	}

	CI_CreateAndSetControls("Sailing3Pers", "Sea_CameraSwitch", CI_GetKeyCode("VK_TAB"), 0, true);
    AddControlToGroups("Sea_CameraSwitch", "Sailing1Pers", "SailingFire", "", "");

    // Rosarak Зум подзорки
	CI_CreateAndSetControls("Sailing1Pers", "TelescopeMode",    CI_GetKeyCode("VK_CONTROL"),     0, true);
	CI_CreateAndSetControls("Sailing1Pers", "TelescopeZoomIn",  CI_GetKeyCode("VK_MWHEEL_UP"),   0, true);
	CI_CreateAndSetControls("Sailing1Pers", "TelescopeZoomOut", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, true);
    MapControlToGroup("TelescopeMode",   "SailingFire");
    MapControlToGroup("TelescopeZoomIn", "SailingFire");
    MapControlToGroup("TelescopeZoomOut","SailingFire");
/*
	if (MOD_BETTATESTMODE == "On")
	{
		CI_CreateAndSetControls("Sailing3Pers", "Ship_SetRTime", CI_GetKeyCode("KEY_R"), 0, true);
	}
*/	
	// if (MOD_BETTATESTMODE == "On")
	// {
		// CI_CreateAndSetControls("", "Test_MastFall", CI_GetKeyCode("KEY_Y"), 0, true);
	// }
/*
	CI_CreateAndSetControls("Sailing3Pers", "Ship_GetPosition", CI_GetKeyCode("KEY_V"), 0, true);
	MapControlToGroup("Ship_GetPosition","Sailing1Pers");
*/
// World map ===================================================================
	CI_CreateAndSetControls("", "WMapTurnH", 256, 0, false);
	CI_CreateAndSetControls("", "WMapTurnV", 257, INVERSE_CONTROL, false);
	//SetControlForInverting("WMapTurnV",true);
	CI_CreateAndSetControls("WorldMapControls", "WMapCameraRotate", CI_GetKeyCode("VK_CONTROL"), 0, true);
	//CI_CreateAndSetControls("WorldMapControls", "WMapForward", CI_GetKeyCode("VK_LBUTTON"), 0, true);
	CI_CreateAndSetControls("WorldMapControls", "WMapForward", CI_GetKeyCode("VK_MWHEEL_UP"), 0, true);
	//CI_CreateAndSetControls("WorldMapControls", "WMapBackward", CI_GetKeyCode("VK_RBUTTON"), 0, true);
	CI_CreateAndSetControls("WorldMapControls", "WMapBackward", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, true);
	CI_CreateAndSetControls("WorldMapControls", "WMapCameraSwitch", CI_GetKeyCode("VK_TAB"), 0, true);
	//CI_CreateAndSetControls("WorldMapControls", "WMapPauseSwitch", CI_GetKeyCode("VK_PAUSE"), 0, true);
	
	// CI_CreateAndSetControls("WorldMapControls", "WMapShipSailUp", CI_GetKeyCode("KEY_W"), 0, true);
	// CI_CreateAndSetControls("WorldMapControls", "WMapShipSailDown", CI_GetKeyCode("KEY_S"), 0, true);
	// CI_CreateAndSetControls("WorldMapControls", "WMapShipTurnLeft", CI_GetKeyCode("KEY_A"), 0, true);
	// CI_CreateAndSetControls("WorldMapControls", "WMapShipTurnRight", CI_GetKeyCode("KEY_D"), 0, true);

	if(bClassic) CI_CreateAndSetControls("WorldMapControls", "WMapCancel", CI_GetKeyCode("VK_SPACE"), 0, true);
	else CI_CreateAndSetControls("WorldMapControls", "WMapCancel", CI_GetKeyCode("KEY_F"), 0, true);
	// CI_CreateAndSetControls("WorldMapControls", "WMapSkipEncounter", CI_GetKeyCode("VK_RETURN"), 0, true);
	// CI_CreateAndSetControls("WorldMapControls", "WMapGetCoords", CI_GetKeyCode("KEY_C"), 0, true);


// Interface ===================================================================
	// Main interface
	CI_CreateAndSetControls("", "ITurnH", 256, 0, false);
	CI_CreateAndSetControls("", "ITurnV", 257, INVERSE_CONTROL, false);
	CI_CreateAndSetControls("", "ILClick", CI_GetKeyCode("VK_LBUTTON"), 0, false);
	CI_CreateAndSetControls("", "IRClick", CI_GetKeyCode("VK_RBUTTON"), 0, false);
	if(!bClassic)
    {
        CI_CreateAndSetControls("PrimaryLand", "Interface", CI_GetKeyCode("VK_F2"), 0, false);
        AddControlToGroups("Interface", "Sailing3Pers", "Sailing1Pers", "WorldMapControls", "SailingFire");
	}
	CI_CreateAndSetControls("Sailing1Pers", "MainMenu", CI_GetKeyCode("VK_ESCAPE"), 0, false);
	AddControlToGroups("MainMenu", "Sailing3Pers", "PrimaryLand", "WorldMapControls", "FightModeControls");
    MapControlToGroup("MainMenu","SailingFire");
	CI_CreateAndSetControls("", "QuickSave", CI_GetKeyCode("VK_F6"), 0, false);
	CI_CreateAndSetControls("", "QuickLoad", CI_GetKeyCode("VK_F9"), 0, false);
	CI_CreateAndSetControls("", "IStartButton", CI_GetKeyCode("VK_RETURN"), 0, false);
	//CI_CreateAndSetControls("", "IAllCancel", CI_GetKeyCode("VK_BACK"), 0, false);
	CI_CreateAndSetControls("", "ICancel", CI_GetKeyCode("VK_ESCAPE"), 0, false);
	CI_CreateAndSetControls("", "IAction", CI_GetKeyCode("VK_SPACE"), 0, false);
	CI_CreateAndSetControls("", "ILeftShift", CI_GetKeyCode("VK_SHIFT"), 0, false);
	CI_CreateAndSetControls("", "IRightShift", CI_GetKeyCode("VK_SHIFT"), 0, false);
	CI_CreateAndSetControls("", "ShiftUp", CI_GetKeyCode("VK_SHIFT"), INVERSE_CONTROL, false);
	CI_CreateAndSetControls("", "IUp", CI_GetKeyCode("VK_UP"), 0, false);
	CI_CreateAndSetControls("", "IDown", CI_GetKeyCode("VK_DOWN"), 0, false);
	CI_CreateAndSetControls("", "IRight", CI_GetKeyCode("VK_RIGHT"), 0, false);
	CI_CreateAndSetControls("", "ILeft", CI_GetKeyCode("VK_LEFT"), 0, false);
	//CI_CreateAndSetControls("", "IContextHelp", CI_GetKeyCode("VK_CONTROL"), 0, false);
	CI_CreateAndSetControls("MainInterface", "InterfaceGoLeft", CI_GetKeyCode("KEY_Q"), 0, false);
	CI_CreateAndSetControls("MainInterface", "InterfaceGoRight", CI_GetKeyCode("KEY_E"), 0, false);
	CI_CreateAndSetControls("MainInterface", "InterfaceTabSwitch", CI_GetKeyCode("VK_TAB"), 0, false);
	CI_CreateAndSetControls("MainInterface", "InterfaceInfoSwitch", CI_GetKeyCode("KEY_S"), 0, false);

	// controls for instant exit from interface (used by function XI_RegistryExitKey() )
	CI_CreateAndSetControls("", "IExit_F2", CI_GetKeyCode("VK_F2"), 0, false);
	CI_CreateAndSetControls("", "IExit_Escape", CI_GetKeyCode("VK_ESCAPE"), 0, false);
	CI_CreateAndSetControls("", "IExit_F1", CI_GetKeyCode("VK_F1"), 0, false);

    // Взаимодействия
    CI_CreateAndSetControls("PrimaryLand", "ChrAction", CI_GetKeyCode("VK_LBUTTON"), 0, true);
	if(bClassic) 
		CI_CreateAndSetControls("BattleInterfaceControls", "BIFastCommand", CI_GetKeyCode("VK_SPACE"), 0, true);
	else 
		CI_CreateAndSetControls("BattleInterfaceControls", "BIFastCommand", CI_GetKeyCode("KEY_F"), 0, true);
	AddControlToGroups("BIFastCommand", "PrimaryLand", "FightModeControls", "Sailing3Pers", "Sailing1Pers");
    MapControlToGroup("BIFastCommand","SailingFire");

// Interface open controls for alternative layout =======================================
	CI_CreateAndSetControls("PrimaryLand", "Alchemy", CI_GetKeyCode("KEY_K"), 0, true); // Алхимия
	MapControlToGroup("Alchemy","BattleInterfaceControls");
	CI_CreateAndSetControls("PrimaryLand", "MapView", CI_GetKeyCode("KEY_M"), 0, true); // Атлас
	MapControlToGroup("MapView","Sailing3Pers");
	MapControlToGroup("MapView","WorldMapControls");

	// sith вкладки меню персонажа --->
	if(bClassic)
    {
		CI_CreateAndSetControls("PrimaryLand", "Inventory", CI_GetKeyCode("VK_F1"), 0, true); // Инвентарь
		CI_CreateAndSetControls("PrimaryLand", "ShipState", CI_GetKeyCode("VK_F2"), 0, true); // Корабли
		CI_CreateAndSetControls("PrimaryLand", "QuestBook", CI_GetKeyCode("VK_F3"), 0, true); // Журнал
		CI_CreateAndSetControls("PrimaryLand", "Abilities", CI_GetKeyCode("VK_F4"), 0, true); // Навыки
		CI_CreateAndSetControls("PrimaryLand", "Nations",   CI_GetKeyCode("VK_F5"), 0, true); // Нации
	}
    else
    {
		CI_CreateAndSetControls("PrimaryLand", "Inventory", CI_GetKeyCode("KEY_I"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "ShipState", CI_GetKeyCode("KEY_H"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "QuestBook", CI_GetKeyCode("KEY_J"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "Abilities", CI_GetKeyCode("KEY_U"), 0, true);
		CI_CreateAndSetControls("PrimaryLand", "Nations",   CI_GetKeyCode("KEY_N"), 0, true);
	}
	AddControlToGroups("Inventory", "Sailing3Pers", "Sailing1Pers", "WorldMapControls", "SailingFire");
	AddControlToGroups("ShipState", "Sailing3Pers", "Sailing1Pers", "WorldMapControls", "SailingFire");
	AddControlToGroups("QuestBook", "Sailing3Pers", "Sailing1Pers", "WorldMapControls", "SailingFire");
	AddControlToGroups("Abilities", "Sailing3Pers", "Sailing1Pers", "WorldMapControls", "SailingFire");
	AddControlToGroups("Nations",   "Sailing3Pers", "Sailing1Pers", "WorldMapControls", "SailingFire");
	// <--- sith

	// быстрый переход по заведениям
	CI_CreateAndSetControls("PrimaryLand", "Fast_port", CI_GetKeyCode("VK_NUMPAD1"), 0, true); // VK_BACK
	CI_CreateAndSetControls("PrimaryLand", "Fast_store", CI_GetKeyCode("VK_NUMPAD2"), 0, true);
	CI_CreateAndSetControls("PrimaryLand", "Fast_shipyard", CI_GetKeyCode("VK_NUMPAD3"), 0, true);
	CI_CreateAndSetControls("PrimaryLand", "Fast_tavern", CI_GetKeyCode("VK_NUMPAD4"), 0, true);
	CI_CreateAndSetControls("PrimaryLand", "Fast_townhall", CI_GetKeyCode("VK_NUMPAD5"), 0, true);
	CI_CreateAndSetControls("PrimaryLand", "Fast_bank", CI_GetKeyCode("VK_NUMPAD6"), 0, true);
	CI_CreateAndSetControls("PrimaryLand", "Fast_church", CI_GetKeyCode("VK_NUMPAD7"), 0, true);
	CI_CreateAndSetControls("PrimaryLand", "Fast_brothel", CI_GetKeyCode("VK_NUMPAD8"), 0, true);
	CI_CreateAndSetControls("PrimaryLand", "Fast_portoffice", CI_GetKeyCode("VK_NUMPAD9"), 0, true);
	CI_CreateAndSetControls("PrimaryLand", "Fast_prison", CI_GetKeyCode("VK_NUMPAD0"), 0, true);

	// Cameras =====================================================================
		// character camera
	CI_CreateAndSetControls("", "ChrCamTurnV", 257, 0, false);
	SetControlForInverting("ChrCamTurnV",false);
	CI_CreateAndSetControls("", "ChrCamTurnH", 256, 0, false);
	CI_CreateAndSetControls("", "ChrCamSpecMode", CI_GetKeyCode("VK_CONTROL"), 0, false);
	CI_CreateAndSetControls("", "Turn V", 257, INVERSE_CONTROL, false);
	SetControlForInverting("Turn V",true);
	CI_CreateAndSetControls("", "Turn H", 256, 0, false);
	if (MOD_BETTATESTMODE == "On") CI_CreateAndSetControls("PrimaryLand", "ChrCamCameraSwitch", CI_GetKeyCode("VK_A_TILDA"), 0, false);
	//CI_CreateAndSetControls("PrimaryLand", "ChrCamCameraRadius", CI_GetKeyCode("VK_MWHEEL_UP"), 0, false);
    //MapControlToGroup("ChrCamCameraSwitch","FightModeControls"); // evganat - добавляем таб в бой

		// ship follow camera
	CI_CreateAndSetControls("Sailing3Pers", "ShipCamera_Forward", CI_GetKeyCode("VK_MWHEEL_UP"), 0, true);
	CI_CreateAndSetControls("Sailing3Pers", "ShipCamera_Backward", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, true);
	CI_CreateAndSetControls("Sailing3Pers", "ShipCamera_Turn_V", 257, INVERSE_CONTROL, false);
	MapControlToGroup("ShipCamera_Turn_V", "BattleInterfaceControls");
	DoControlInvisible("Sailing3Pers", "ShipCamera_Turn_V");
	DoControlInvisible("BattleInterfaceControls", "ShipCamera_Turn_V");	
	SetControlForInverting("ShipCamera_Turn_V",true);
	CI_CreateAndSetControls("Sailing3Pers", "ShipCamera_Turn_H", 256, 0, false);
	MapControlToGroup("ShipCamera_Turn_H", "BattleInterfaceControls");
	DoControlInvisible("Sailing3Pers", "ShipCamera_Turn_H");
	DoControlInvisible("BattleInterfaceControls", "ShipCamera_Turn_H");
	CI_CreateAndSetControls("Sailing3Pers", "FireCamera_Set", CI_GetKeyCode("VK_RBUTTON"), 0, true);
    AddControlToGroups("FireCamera_Set", "Sailing1Pers", "SailingFire", "", "");

		// deck camera
	//Trace("DeckCamera_Turn_V");
	CI_CreateAndSetControls("Sailing1Pers", "DeckCamera_Forward", CI_GetKeyCode("VK_LBUTTON"), 0, true);
	CI_CreateAndSetControls("Sailing1Pers", "DeckCamera_Backward", CI_GetKeyCode("VK_MBUTTON"), 0, true);
	CI_CreateAndSetControls("Sailing1Pers", "DeckCamera_Turn_V", 257, 0, false);
	SetControlForInverting("DeckCamera_Turn_V",false);
	DoControlInvisible("Sailing1Pers", "DeckCamera_Turn_V");
	CI_CreateAndSetControls("Sailing1Pers", "DeckCamera_Turn_H", 256, 0, false);
	DoControlInvisible("Sailing1Pers", "DeckCamera_Turn_H");
	
        // fire camera
	CI_CreateAndSetControls("SailingFire", "FireCamera_Turn_V", 257, 0, false);
	SetControlForInverting("FireCamera_Turn_V",false);
	DoControlInvisible("SailingFire", "FireCamera_Turn_V");
	CI_CreateAndSetControls("SailingFire", "FireCamera_Turn_H", 256, 0, false);
	DoControlInvisible("SailingFire", "FireCamera_Turn_H");

		// free camera
	CI_CreateAndSetControls("", "FreeCamera_Turn_V", 257, INVERSE_CONTROL, false);
	SetControlForInverting("FreeCamera_Turn_V",true);
	CI_CreateAndSetControls("", "FreeCamera_Turn_H", 256, 0, false);
	CI_CreateAndSetControls("", "FreeCamera_Forward", CI_GetKeyCode("VK_LBUTTON"), 0, false);  //VK_LBUTTON
	CI_CreateAndSetControls("", "FreeCamera_Backward", CI_GetKeyCode("VK_RBUTTON"), 0, false);   //VK_RBUTTON

// Dialog =====================================================================
	CI_CreateAndSetControls("DialogControls", "DlgAction", CI_GetKeyCode("VK_SPACE"), 0, false);
	CI_CreateAndSetControls("DialogControls", "DlgAction1", CI_GetKeyCode("VK_LBUTTON"), 0, false);   // boal new engine
	CI_CreateAndSetControls("DialogControls", "DlgAction2", CI_GetKeyCode("VK_RETURN"), 0, false);
	CI_CreateAndSetControls("", "DlgCancel", CI_GetKeyCode("VK_ESCAPE"), 0, false);
	CI_CreateAndSetControls("DialogControls", "DlgUp", CI_GetKeyCode("VK_UP"), 0, false);
	CI_CreateAndSetControls("DialogControls", "DlgDown", CI_GetKeyCode("VK_DOWN"), 0, false);
	CI_CreateAndSetControls("DialogControls", "DlgUp2", CI_GetKeyCode("VK_MWHEEL_UP"), 0, false);
	CI_CreateAndSetControls("DialogControls", "DlgDown2", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, false);
	CI_CreateAndSetControls("DialogControls", "DlgUp3", CI_GetKeyCode("KEY_W"), 0, false);
	CI_CreateAndSetControls("DialogControls", "DlgDown3", CI_GetKeyCode("KEY_S"), 0, false);
	CI_CreateAndSetControls("DialogControls", "DlgScrollUp", CI_GetKeyCode("VK_PRIOR"), 0, false);
	CI_CreateAndSetControls("DialogControls", "DlgScrollDown", CI_GetKeyCode("VK_NEXT"), 0, false);

	for (int i = 1; i <= 9; i++) {
		CI_CreateAndSetControls("DialogControls", "DlgActionSel" + i, CI_GetKeyCode("KEY_" + i), 0, false);
	}

    // Net Controls -->
	CI_CreateAndSetControls("NetShipControls", "Net_Menu", CI_GetKeyCode("VK_ESCAPE"), 0, true);
	CI_CreateAndSetControls("NetShipControls", "Say", CI_GetKeyCode("KEY_Y"), 0, true);
	CI_CreateAndSetControls("NetShipControls", "Team_Say", CI_GetKeyCode("KEY_O"), 0, true);
	CI_CreateAndSetControls("NetShipControls", "Person_Say", CI_GetKeyCode("KEY_T"), 0, true);
	CI_CreateAndSetControls("", "gamestat", CI_GetKeyCode("VK_F1"), 0, true);
	CI_CreateAndSetControls("", "toplist", CI_GetKeyCode("VK_F2"), 0, true);
	//CI_CreateAndSetControls("", "gamechat", CI_GetKeyCode("VK_F3"), 0, true);

	MapControlToGroup("ShipCamera_Turn_H", "NetShipControls");
	MapControlToGroup("ShipCamera_Turn_V", "NetShipControls");

	MapControlToGroup("DeckCamera_Turn_H", "NetShipControls");
	MapControlToGroup("DeckCamera_Turn_V", "NetShipControls");

	MapControlToGroup("BICommandsActivate", "NetShipControls");
	
	// temporary control
	CI_CreateAndSetControls("NetShipControls", "Ship_StartRepair", CI_GetKeyCode("KEY_L"), 0, true);
	
	MapControlToGroup("Ship_TurnLeft", "NetShipControls");
	MapControlToGroup("Ship_TurnRight", "NetShipControls");
	MapControlToGroup("Ship_SailUp", "NetShipControls");
	MapControlToGroup("Ship_SailDown", "NetShipControls");
	MapControlToGroup("Ship_Fire", "NetShipControls");

	MapControlToGroup("Sea_CameraSwitch", "NetShipControls");
	MapControlToGroup("TelescopeIn", "NetShipControls"); //Без зума (TO_DO)

	MapControlToGroup("hk_charge1", "NetShipControls");
	MapControlToGroup("hk_charge2", "NetShipControls");
	MapControlToGroup("hk_charge3", "NetShipControls");
	MapControlToGroup("hk_charge4", "NetShipControls");

	MapControlToGroup("ShipCamera_Forward", "NetShipControls");
	MapControlToGroup("ShipCamera_Backward", "NetShipControls");
	MapControlToGroup("DeckCamera_Forward", "NetShipControls");
	MapControlToGroup("DeckCamera_Backward", "NetShipControls");
    // <-- Net Controls

	// TimeScale (кроме NumPad)
    CI_CreateAndSetControls("BattleInterfaceControls", "TimeScale", CI_GetKeyCode("KEY_R"), 0, true);
    AddControlToSettingsGroups("TimeScale");
	CI_CreateAndSetControls("BattleInterfaceControls", "TimeScaleFasterBA", CI_GetKeyCode("VK_A_PLUS"), 0, true);
    AddControlToSettingsGroups("TimeScaleFasterBA");
	CI_CreateAndSetControls("BattleInterfaceControls", "TimeScaleSlowerBA", CI_GetKeyCode("VK_A_MINUS"), 0, true);
    AddControlToSettingsGroups("TimeScaleSlowerBA");
    MapControlToGroup("TimeScale",         "SailingFire");
    MapControlToGroup("TimeScaleFasterBA", "SailingFire");
    MapControlToGroup("TimeScaleSlowerBA", "SailingFire");

    // Battle interface
    // Вызов панели
	CI_CreateAndSetControls("PrimaryLand", "LICommandsActivate", CI_GetKeyCode("VK_RETURN"), 0, true);
	MapControlToGroup("LICommandsActivate","FightModeControls");
	CI_CreateAndSetControls("Sailing3Pers", "BICommandsActivate", CI_GetKeyCode("VK_RETURN"), 0, true);
    AddControlToGroups("BICommandsActivate", "Sailing1Pers", "WorldMapControls", "SailingFire", "");
    // Действия на панели
    CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsConfirm", CI_GetKeyCode("VK_RETURN"), 0, true);
    AddControlToSettingsGroups("BICommandsConfirm");
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsCancel",  CI_GetKeyCode("VK_ESCAPE"), 0, false);
    AddControlToSettingsGroups("BICommandsCancel");
    // Навигация по панели
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsUp", CI_GetKeyCode("VK_UP"), 0, true);
    AddControlToSettingsGroups("BICommandsUp");
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsDown", CI_GetKeyCode("VK_DOWN"), 0, true);
    AddControlToSettingsGroups("BICommandsDown");
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsLeft", CI_GetKeyCode("VK_LEFT"), 0, true);
    AddControlToSettingsGroups("BICommandsLeft");
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsRight", CI_GetKeyCode("VK_RIGHT"), 0, true);
    AddControlToSettingsGroups("BICommandsRight");
    // Вешаем флаг принудительного обновления во всех группах
    // По факту используется лишь функционал BattleInterfaceControls, а остальные группы нужны лишь для интерфейса
    BI_ControlsSyncLock();

    // Рас/Синхронизация клавиш
    SetKeySyncParametres();
}

void ExternInitKeyCodes()
{
    // DIGITS
	objControlsState.key_codes.KEY_0 = 48;
	objControlsState.key_codes.KEY_0.img = "⓪";
	objControlsState.key_codes.KEY_1 = 49;
	objControlsState.key_codes.KEY_1.img = "①";
	objControlsState.key_codes.KEY_2 = 50;
	objControlsState.key_codes.KEY_2.img = "②";
	objControlsState.key_codes.KEY_3 = 51;
	objControlsState.key_codes.KEY_3.img = "③";
	objControlsState.key_codes.KEY_4 = 52;
	objControlsState.key_codes.KEY_4.img = "④";
	objControlsState.key_codes.KEY_5 = 53;
	objControlsState.key_codes.KEY_5.img = "⑤";
	objControlsState.key_codes.KEY_6 = 54;
	objControlsState.key_codes.KEY_6.img = "⑥";
	objControlsState.key_codes.KEY_7 = 55;
	objControlsState.key_codes.KEY_7.img = "⑦";
	objControlsState.key_codes.KEY_8 = 56;
	objControlsState.key_codes.KEY_8.img = "⑧";
	objControlsState.key_codes.KEY_9 = 57;
	objControlsState.key_codes.KEY_9.img = "⑨";

    // LETTERS
	objControlsState.key_codes.KEY_A = 65;
	objControlsState.key_codes.KEY_A.img = "Ⓐ";
	objControlsState.key_codes.KEY_B = 66;
	objControlsState.key_codes.KEY_B.img = "Ⓑ";
	objControlsState.key_codes.KEY_C = 67;
	objControlsState.key_codes.KEY_C.img = "Ⓒ";
	objControlsState.key_codes.KEY_D = 68;
	objControlsState.key_codes.KEY_D.img = "Ⓓ";
	objControlsState.key_codes.KEY_E = 69;
	objControlsState.key_codes.KEY_E.img = "Ⓔ";
	objControlsState.key_codes.KEY_F = 70;
	objControlsState.key_codes.KEY_F.img = "Ⓕ";
	objControlsState.key_codes.KEY_G = 71;
	objControlsState.key_codes.KEY_G.img = "Ⓖ";
	objControlsState.key_codes.KEY_H = 72;
	objControlsState.key_codes.KEY_H.img = "Ⓗ";
	objControlsState.key_codes.KEY_I = 73;
	objControlsState.key_codes.KEY_I.img = "Ⓘ";
	objControlsState.key_codes.KEY_J = 74;
	objControlsState.key_codes.KEY_J.img = "Ⓙ";
	objControlsState.key_codes.KEY_K = 75;
	objControlsState.key_codes.KEY_K.img = "Ⓚ";
	objControlsState.key_codes.KEY_L = 76;
	objControlsState.key_codes.KEY_L.img = "Ⓛ";
	objControlsState.key_codes.KEY_M = 77;
	objControlsState.key_codes.KEY_M.img = "Ⓜ";
	objControlsState.key_codes.KEY_N = 78;
	objControlsState.key_codes.KEY_N.img = "Ⓝ";
	objControlsState.key_codes.KEY_O = 79;
	objControlsState.key_codes.KEY_O.img = "Ⓞ";
	objControlsState.key_codes.KEY_P = 80;
	objControlsState.key_codes.KEY_P.img = "Ⓟ";
	objControlsState.key_codes.KEY_Q = 81;
	objControlsState.key_codes.KEY_Q.img = "Ⓠ";
	objControlsState.key_codes.KEY_R = 82;
	objControlsState.key_codes.KEY_R.img = "Ⓡ";
	objControlsState.key_codes.KEY_S = 83;
	objControlsState.key_codes.KEY_S.img = "Ⓢ";
	objControlsState.key_codes.KEY_T = 84;
	objControlsState.key_codes.KEY_T.img = "Ⓣ";
	objControlsState.key_codes.KEY_U = 85;
	objControlsState.key_codes.KEY_U.img = "Ⓤ";
	objControlsState.key_codes.KEY_V = 86;
	objControlsState.key_codes.KEY_V.img = "Ⓥ";
	objControlsState.key_codes.KEY_W = 87;
	objControlsState.key_codes.KEY_W.img = "Ⓦ";
	objControlsState.key_codes.KEY_X = 88;
	objControlsState.key_codes.KEY_X.img = "Ⓧ";
	objControlsState.key_codes.KEY_Y = 89;
	objControlsState.key_codes.KEY_Y.img = "Ⓨ";
	objControlsState.key_codes.KEY_Z = 90;
	objControlsState.key_codes.KEY_Z.img = "Ⓩ";

    // MOUSE
	objControlsState.key_codes.VK_LBUTTON	= 1;
	objControlsState.key_codes.VK_LBUTTON.img = "ᐼ";
	objControlsState.key_codes.VK_RBUTTON	= 2;
	objControlsState.key_codes.VK_RBUTTON.img = "ᐽ";
	objControlsState.key_codes.VK_MBUTTON	= 4;
	objControlsState.key_codes.VK_MBUTTON.img = "ᐲ";
	objControlsState.key_codes.VK_XBUTTON1	= 5;
	objControlsState.key_codes.VK_XBUTTON1.img = "ᐲ"; //TO_DO
	objControlsState.key_codes.VK_XBUTTON2	= 6;
	objControlsState.key_codes.VK_XBUTTON2.img = "ᐲ"; //TO_DO
    // MOUSE ADDITIONAL (TO_DO)
	objControlsState.key_codes.VK_TURN_H	= 256; //CE_MOUSE_X_AXIS
	objControlsState.key_codes.VK_TURN_H.img = "ᐲ";
	objControlsState.key_codes.VK_TURN_V	= 257; //CE_MOUSE_Y_AXIS
	objControlsState.key_codes.VK_TURN_V.img = "ᐲ";
	objControlsState.key_codes.VK_MWHEEL_UP		= 258; //CE_MOUSE_WHEEL_UP
	objControlsState.key_codes.VK_MWHEEL_UP.img = "ᐲ";
	objControlsState.key_codes.VK_MWHEEL_DOWN	= 259; //CE_MOUSE_WHEEL_DOWN
	objControlsState.key_codes.VK_MWHEEL_DOWN.img = "ᐲ";

    // NUMPAD
	objControlsState.key_codes.VK_NUMPAD0     = 96;
	objControlsState.key_codes.VK_NUMPAD0.img = "⓿";
	objControlsState.key_codes.VK_NUMPAD1     = 97;
	objControlsState.key_codes.VK_NUMPAD1.img = "⓵";
	objControlsState.key_codes.VK_NUMPAD2     = 98;
	objControlsState.key_codes.VK_NUMPAD2.img = "⓶";
	objControlsState.key_codes.VK_NUMPAD3     = 99;
	objControlsState.key_codes.VK_NUMPAD3.img = "⓷";
	objControlsState.key_codes.VK_NUMPAD4     = 100;
	objControlsState.key_codes.VK_NUMPAD4.img = "⓸";
	objControlsState.key_codes.VK_NUMPAD5     = 101;
	objControlsState.key_codes.VK_NUMPAD5.img = "⓹";
	objControlsState.key_codes.VK_NUMPAD6     = 102;
	objControlsState.key_codes.VK_NUMPAD6.img = "⓺";
	objControlsState.key_codes.VK_NUMPAD7     = 103;
	objControlsState.key_codes.VK_NUMPAD7.img = "⓻";
	objControlsState.key_codes.VK_NUMPAD8     = 104;
	objControlsState.key_codes.VK_NUMPAD8.img = "⓼";
	objControlsState.key_codes.VK_NUMPAD9     = 105;
	objControlsState.key_codes.VK_NUMPAD9.img = "⓽";
	objControlsState.key_codes.VK_MULTIPLY    = 106;
	objControlsState.key_codes.VK_MULTIPLY.img = "⊗";
	objControlsState.key_codes.VK_ADD     = 107;
	objControlsState.key_codes.VK_ADD.img = "⊕"; //TO_DO
	objControlsState.key_codes.VK_SEPARATOR	= 108;
	objControlsState.key_codes.VK_SEPARATOR.img = "⊙"; //TO_DO
	objControlsState.key_codes.VK_SUBTRACT	= 109;
	objControlsState.key_codes.VK_SUBTRACT.img = "⊖";
	objControlsState.key_codes.VK_DECIMAL	= 110;
	objControlsState.key_codes.VK_DECIMAL.img = "⊚";
	objControlsState.key_codes.VK_DIVIDE	= 111;
	objControlsState.key_codes.VK_DIVIDE.img = "⊘";

    // FUNCTION KEYS (F1 to F5; TO_DO ОСТАЛЬНЫЕ)
	objControlsState.key_codes.VK_F1     = 112;
	objControlsState.key_codes.VK_F1.img = "⑴";
	objControlsState.key_codes.VK_F2     = 113;
	objControlsState.key_codes.VK_F2.img = "⑵";
	objControlsState.key_codes.VK_F3     = 114;
	objControlsState.key_codes.VK_F3.img = "⑶";
	objControlsState.key_codes.VK_F4     = 115;
	objControlsState.key_codes.VK_F4.img = "⑷";
	objControlsState.key_codes.VK_F5     = 116;
	objControlsState.key_codes.VK_F5.img = "⑸";
	objControlsState.key_codes.VK_F6     = 117;
	objControlsState.key_codes.VK_F6.img = "⌴";
	objControlsState.key_codes.VK_F7     = 118;
	objControlsState.key_codes.VK_F7.img = "⌴";
	objControlsState.key_codes.VK_F8     = 119;
	objControlsState.key_codes.VK_F8.img = "⌴";
	objControlsState.key_codes.VK_F9     = 120;
	objControlsState.key_codes.VK_F9.img = "⌴";
	objControlsState.key_codes.VK_F10     = 121;
	objControlsState.key_codes.VK_F10.img = "⌴";
    objControlsState.key_codes.VK_F11     = 122;
	objControlsState.key_codes.VK_F11.img = "⌴";
    objControlsState.key_codes.VK_F12     = 123;
	objControlsState.key_codes.VK_F12.img = "⌴";

    // OTHER (TO_DO: ПЕРЕВЕРИТЬ)
	objControlsState.key_codes.VK_BACK     = 8;
	objControlsState.key_codes.VK_BACK.img = "↰";
	objControlsState.key_codes.VK_TAB      = 9;
	objControlsState.key_codes.VK_TAB.img  = "⇄";
	objControlsState.key_codes.VK_RETURN   = 13;
	objControlsState.key_codes.VK_RETURN.img = "↲";
	objControlsState.key_codes.VK_SHIFT     = 16;
	objControlsState.key_codes.VK_SHIFT.img = "⇪";
	objControlsState.key_codes.VK_CONTROL   = 17;
	objControlsState.key_codes.VK_CONTROL.img = "∁";

	objControlsState.key_codes.VK_ESCAPE	= 27;
	objControlsState.key_codes.VK_ESCAPE.img = "↺";
	objControlsState.key_codes.VK_SPACE		= 32;
	objControlsState.key_codes.VK_SPACE.img = "⌴";
	objControlsState.key_codes.VK_PRIOR		= 33;
	objControlsState.key_codes.VK_PRIOR.img = "⊼";
	objControlsState.key_codes.VK_NEXT		= 34;
	objControlsState.key_codes.VK_NEXT.img  = "⊻";
	objControlsState.key_codes.VK_CAPSLOCK  = 20;
	objControlsState.key_codes.VK_CAPSLOCK.img = "⇵";

	objControlsState.key_codes.VK_LEFT		= 37;
	objControlsState.key_codes.VK_LEFT.img  = "←";
	objControlsState.key_codes.VK_UP		= 38;
	objControlsState.key_codes.VK_UP.img    = "↑";
	objControlsState.key_codes.VK_RIGHT		= 39;
	objControlsState.key_codes.VK_RIGHT.img = "→";
	objControlsState.key_codes.VK_DOWN		= 40;
	objControlsState.key_codes.VK_DOWN.img  = "↓";

    // TO_DO ПЕРЕВЕРИТЬ (ИКОНОК НЕТ)
	objControlsState.key_codes.VK_MENU      = 18;
	objControlsState.key_codes.VK_MENU.img  = "ₐ";
	objControlsState.key_codes.VK_PAUSE	    = 19;
	objControlsState.key_codes.VK_PAUSE.img = "⌴"; //TO_DO
	objControlsState.key_codes.VK_INSERT	  = 45;
	objControlsState.key_codes.VK_INSERT.img  = "⌴";
	objControlsState.key_codes.VK_DELETE	  = 46;
	objControlsState.key_codes.VK_DELETE.img  = "⌴";
	objControlsState.key_codes.VK_A_POINT     = 186;    //; :
	objControlsState.key_codes.VK_A_POINT.img = "⌴";
	objControlsState.key_codes.VK_A_PLUS      = 187;    //= +
	objControlsState.key_codes.VK_A_PLUS.img  = "⊞";
	objControlsState.key_codes.VK_A_SMALL     = 188;    //, <
	objControlsState.key_codes.VK_A_SMALL.img = "⌴";
	objControlsState.key_codes.VK_A_MINUS     = 189;    //- _
	objControlsState.key_codes.VK_A_MINUS.img = "⊟";
	objControlsState.key_codes.VK_A_BIG		  = 190;    //. >
	objControlsState.key_codes.VK_A_BIG.img   = "⌴";
	objControlsState.key_codes.VK_A_QWS	      = 191;    //?/
	objControlsState.key_codes.VK_A_QWS.img   = "⌴";
	objControlsState.key_codes.VK_A_TILDA     = 192;    // ` ~
	objControlsState.key_codes.VK_A_TILDA.img  = "⌴";
	objControlsState.key_codes.VK_L_BREAKE     = 219;   //[ {
	objControlsState.key_codes.VK_L_BREAKE.img = "⌴";
	objControlsState.key_codes.VK_A_SLUSH	   = 220;   // \ |
	objControlsState.key_codes.VK_A_SLUSH.img  = "⌴";
	objControlsState.key_codes.VK_R_BREAKE	   = 221;   //[ {
	objControlsState.key_codes.VK_R_BREAKE.img = "⌴";
	objControlsState.key_codes.VK_A_QUOTE      = 222;   //' "
	objControlsState.key_codes.VK_A_QUOTE.img  = "⌴";

    // Порядок учитывается в поиске бинда для остальных групп
    objControlsState.keygroups.FightModeControls = "";
	objControlsState.keygroups.PrimaryLand  = "";
	objControlsState.keygroups.Sailing3Pers = "";
	objControlsState.keygroups.Sailing1Pers = "";
	objControlsState.keygroups.WorldMapControls = "";

	// Группы для сохранения в опции
	objControlsState.grouplist.FightModeControls = true;
	objControlsState.grouplist.PrimaryLand  = true;
	objControlsState.grouplist.Sailing3Pers = true;
	objControlsState.grouplist.Sailing1Pers = true;
	objControlsState.grouplist.WorldMapControls = true;
	objControlsState.grouplist.AltPressedGroup  = true;
    objControlsState.grouplist.BattleInterfaceControls = true;
    objControlsState.grouplist.SailingFire = true;
    // DialogControls, VideoPlayer, MainInterface
}

void SetKeySyncParametres()
{
    // В указанных парах можно менять кнопки, когда на второй уже стоит такой же бинд
    // Распространяется сразу на все группы (запрещать в одной, но разрешать в другой — пока нечего)

    // Прицеливание и стрельба
    SameBindingAllowed("ChrAiming", "ChrFire", 1);
    // Спринт и модификатор атаки
    SameBindingAllowed("ChrSprint", "ChrAttackChoseBase", 0);
    // Блок и быстрое действие
    SameBindingAllowed("ChrBlock", "BIFastCommand", 0);
    // Командное меню и движение
    SameBindingAllowed("ChrForward",     "BICommandsUp",    2);
    SameBindingAllowed("ChrBackward",    "BICommandsDown",  2);
    SameBindingAllowed("ChrStrafeLeft",  "BICommandsLeft",  2);
    SameBindingAllowed("ChrStrafeRight", "BICommandsRight", 2);
    // Командное меню и управление кораблём в море и на глобалке
    SameBindingAllowed("Ship_SailUp",    "BICommandsUp",    3);
    SameBindingAllowed("Ship_SailDown",  "BICommandsDown",  3);
    SameBindingAllowed("Ship_TurnLeft",  "BICommandsLeft",  3);
    SameBindingAllowed("Ship_TurnRight", "BICommandsRight", 3);
}

void BI_ControlsSyncLock()
{
    ControlSyncLock("BICommandsConfirm");
    ControlSyncLock("BICommandsCancel");
    ControlSyncLock("BICommandsUp");
    ControlSyncLock("BICommandsDown");
    ControlSyncLock("BICommandsLeft");
    ControlSyncLock("BICommandsRight");
}
