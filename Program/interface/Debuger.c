//  boal 14.02.06 меню дебугера
string totalInfo;
int idLngFile = -1;
int remInt = 0;

void InitInterface(string iniName)
{
    StartAboveForm(true);

    GameInterface.title = "titleBoal_Debug";
	bGameMenuStart = true; // меню запущено, скрываем landinterface
    SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

    CalculateInfoData();

    CalculateCheatsInfo(); // Warship. Статистика - сколько читов юзали

    SetFormatedText("INFO_TEXT", totalInfo); //"Информация отладчика");
    SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 5);

    SetEventHandler("InterfaceBreak", "ProcessBreakExit", 0);
    SetEventHandler("exitCancel", "ProcessCancelExit", 0);
    SetEventHandler("evntDoPostExit", "DoPostExit", 0);
    SetEventHandler("ievnt_command", "ProcCommand", 0);
    SetEventHandler("SetScrollerPos", "SetScrollerPos", 0);
    SetEventHandler("ScrollPosChange", "ProcScrollPosChange", 0);
    SetEventHandler("ScrollTopChange", "ProcScrollChange", 0);

    GameInterface.reload_edit.str = "Shore75, reload, reload1"; //"Pearl_town_1, reload, reload1";
                                                                         // Pirates_Shipyard, reload, reload1
                                                                         // boarding_cargohold, rld, loc0
	SetSelectable("B_BACK",false);
}

void ProcessBreakExit()
{
    IDoExit(RC_INTERFACE_QUICK_SAVE);
}

void ProcessCancelExit()
{
    bGameMenuStart = false; // выход из меню, показываем landinterface
	IDoExit(RC_INTERFACE_QUICK_SAVE);
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);

    //SetTimeScale(1.0);
    //locCameraSleep(false);

    DelEventHandler("InterfaceBreak", "ProcessBreakExit");
    DelEventHandler("exitCancel", "ProcessCancelExit");
    DelEventHandler("evntDoPostExit", "DoPostExit");
    DelEventHandler("ievnt_command", "ProcCommand");
    DelEventHandler("SetScrollerPos", "SetScrollerPos");
    DelEventHandler("ScrollPosChange", "ProcScrollPosChange");
    DelEventHandler("ScrollTopChange", "ProcScrollChange");

    if (bSeaActive)
    {
        RefreshBattleInterface();
    }

    interfaceResultCommand = exitCode;
    EndCancelInterface(true);
}

void DoPostExit()
{
    int exitCode = GetEventData();
    IDoExit(exitCode);
}

void CalculateInfoData()
{
    // тут высчитываем нужную информацию и выводим в totalInfo - Инициализация -->
    totalInfo = "Это отладчик. Позволяет выполнять заданные скриптологом функции. Кнопки: " + NewStr();
    totalInfo = totalInfo + "F1 - " + descF1 + NewStr() +
                "F2 - " + descF2 + NewStr() +
                "F3 - " + descF3 + NewStr() +
                "F4 - " + descF4 + NewStr() +
                "F5 - " + descF5 + NewStr() +
                "F6 - " + descF6 + NewStr() +
                "F7 - " + descF7 + NewStr() +
                "F8 - " + descF8 + NewStr() +
                "F9 - " + descF9 + NewStr() +
                "F10 - " + descF10 + NewStr() +
                "F11 - " + descF11 + NewStr() +
                "F12 - " + descF12 + NewStr() +
                "F13 - " + descF13 + NewStr() +
                "F14 - " + descF14 + NewStr() +
                "F15 - " + descF15 + NewStr() +
                "F16 - " + descF16 + NewStr() +
                "F17 - " + descF17 + NewStr() +
                "F18 - " + descF18 + NewStr() +
                "F19 - " + descF19 + NewStr() +
                "F20 - " + descF20 + NewStr() +
                "F21 - " + descF21 + NewStr() +
                "F22 - " + descF22 + NewStr() +
                "F23 - " + descF23 + NewStr() +
                "F24 - " + descF24 + NewStr() +
                "F25 - " + descF25 + NewStr() +
                "F26 - " + descF26 + NewStr() +
                "F27 - " + descF27 + NewStr() +
                "F28 - " + descF28 + NewStr() +
                "F29 - " + descF29 + NewStr() +
                "F30 - " + descF30 + NewStr() +
                "F31 - " + descF31 + NewStr() +
                "F32 - " + descF32 + NewStr() +
                "F33 - " + descF33;
    // перевод строки (по другому у меня не вышло) +LanguageConvertString(idLngFile,"new_string");
    // тут высчитываем нужную информацию и выводим в totalInfo <--
}

void ProcCommand()
{
    string comName = GetEventData();
    string nodName = GetEventData();
	

	if (comName == "activate" || comName == "click") {
		if (nodName != "B_RELOAD" && nodName != "B_BACK") {
			SetSelectable("B_BACK",true);
		}
	}

    switch (nodName)
    {
    case "B_F1":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF1();
			SetSelectable("B_BACK",true);
        }
        break;
    case "B_F2":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF2();
        }
        break;
    case "B_F3":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF3();
        }
        break;
    case "B_F4":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF4();
        }
        break;
    case "B_F5":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF5();
        }
        break;

    case "B_F6":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF6();
        }
        break;

    case "B_F7":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF7();
        }
        break;

    case "B_F8":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF8();
        }
        break;

    case "B_F9":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF9();
        }
        break;

    case "B_F10":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF10();
			// pchar.rank_exp = 20;
        }
        break;

    case "B_F11":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF11();
        }
        break;

    case "B_F12":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF12();
        }
        break;

    case "B_F13":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF13();
        }
        break;

    case "B_F14":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF14();
        }
        break;

    case "B_F15":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF15();
        }
        break;

    case "B_F16":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF16();
        }
        break;

    case "B_F17":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF17();
        }
        break;

    case "B_F18":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF18();
        }
        break;

    case "B_F19":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF19();
        }
        break;

    case "B_F20":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF20();
        }
        break;

    case "B_F21":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF21();
        }
        break;
    case "B_F22":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF22();
        }
        break;
    case "B_F23":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF23();
        }
        break;
    case "B_F24":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF24();
        }
        break;
    case "B_F25":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF25();
        }
        break;
    case "B_F26":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF26();
        }
        break;
    case "B_F27":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF27();
        }
        break;
    case "B_F28":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF28();
        }
        break;
    case "B_F29":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF29();
        }
        break;
    case "B_F30":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF30();
        }
        break;
    case "B_31":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF31();
        }
        break;
    case "B_32":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF32();
        }
        break;
    case "B_33":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF33();
        }
        break;
    case "B_BETA":
        if (comName == "activate" || comName == "click")
        {
            IDoExit(RC_INTERFACE_DO_BOAL_BETA);
        }
        break;
    case "B_RELOAD":
        if (comName == "activate" || comName == "click")
        {
            ReloadByStr();
        }
        break;
    case "B_BACK":
        if (comName == "activate" || comName == "click")
        {
			CalculateInfoData();
			SetFormatedText("INFO_TEXT", totalInfo); //"Информация отладчика");
			SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 5);
			SetSelectable("B_BACK",false);
        }
        break;
    }

    CalculateCheatsInfo(); // Статистика по читам
}
/*
float GetShipMaxNeededValue(int iShipType, string _param)
{
    float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
    switch (_param)
    {
        case "speedrate":
            NeededValue += ((0.77 + frandSmall(0.3)) * (NeededValue/10.0)); 
        break;
        case "turnrate":
            NeededValue += ((0.77 + frandSmall(0.3)) * (NeededValue/10.0)); 
        break;
        case "capacity":
            NeededValue += ((0.77 + frandSmall(0.3)) * (NeededValue/8.0)); 
        break;
    }
    return NeededValue;
}
*/

////////////////////////////////////////////////////////////////////////
string descF1 = "Песо + 500 000, дублоны + 100";

void CalculateInfoDataF1()
{
    // тут высчитываем нужную информацию и выводим в totalInfo - Инициализация -->
    totalInfo = descF1;
    Pchar.money = sti(Pchar.money) + 500000;
    AddItems(pchar, "gold_dublon", 100);

    //------- проверка ачивок ------------
    /*    
    Achievment_SetStat(pchar, 8, 1);
    CheckAchievments(pchar, 8);

    if(bSteamAchievements) StoreStats();
*/

    /*
    float MaxSpeed             = 0.0;
    float fWindAgainstSpeed = 1.2;
    float fWindDotShip         = 0.0; 
    float angY                = 0.0;
    for(int i = 0; i < 36; i++)
    {
        angY = (i * 5)/180.0 * 3.1415926;
        fWindDotShip = GetDotProduct( 0.0, angY);    
        MaxSpeed = GetMaxSpeedZ(fWindAgainstSpeed, fWindDotShip);
        trace("MaxSpeed " + MaxSpeed + " angY " + (i*5)); 
    }
*/
    //DumpAttributes(showWindow);

    totalInfo = totalInfo + GetAssembledString(" Денег у #sName#а теперь #dmoney#", Pchar);
    // тут высчитываем нужную информацию и выводим в totalInfo <--

    //totalInfo = totalInfo + NewStr() + NewStr() + GetBestGeneratedItem("blade_32");

    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F1", 1);
}
////////////////////////////////////////////////////////////////////////
string descF2 = "";

void CalculateInfoDataF2()
{
    // -->
    totalInfo = descF2;
	
	/*pchar.questTemp.BM_StartQuest = true;
	PChar.quest.BM_BarbadosKontrabandisty.win_condition.l1 = "location";
	PChar.quest.BM_BarbadosKontrabandisty.win_condition.l1.location = "Mayak2";
	PChar.quest.BM_BarbadosKontrabandisty.win_condition = "BM_BarbadosKontrabandisty";
	AddMapQuestMarkShore("Mayak2", true);
	AddGeometryToLocation("Mayak2", "smg");
	sld = &Locations[FindLocation("Mayak2")];
	sld.locators_radius.goto.goto31 = 50.0;
	locations[FindLocation("Mayak2")].DisableEncounters = true;
	LAi_LocationDisableOfficersGen("Mayak2", true);*/

    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F2", 1);
}
////////////////////////////////////////////////////////////////////////
string descF3 = "ID текущей локации +коорд     ";

void CalculateInfoDataF3()
{
    // -->
    totalInfo = descF3;
    ref mc;
    mc = GetMainCharacter();

    float locx, locy, locz;
    if (bSeaActive && !bAbordageStarted)
    {
        if (CheckAttribute(mc, "Ship.pos.x"))
        {
            totalInfo = totalInfo + NewStr() + mc.location + "     ship(x,z,y)= " + mc.Ship.pos.x + ", " + mc.Ship.pos.z + ", " + mc.Ship.Ang.y;
            totalInfo = totalInfo + NewStr() + " Sea_Coord.X " + Sea_GetRealCoordX(makefloat(mc.Ship.pos.x)) + " Sea_Coord.Z " + Sea_GetRealCoordZ(makefloat(mc.Ship.pos.z));

            if (false) //CheckAttribute(mc, "WMShip.Pos.x") && worldMap.island != "")
            {
                string sTemp = mc.curIslandId;
                float r1 = stf(worldMap.islands.(sTemp).GoMapRadius);

                r1 *= WDM_MAP_TO_SEA_SCALE;
                float d2 = GetDistance2D(stf(mc.Ship.Pos.x),
                                         stf(mc.Ship.Pos.z),
                                         stf(worldMap.islands.(sTemp).position.rx),
                                         stf(worldMap.islands.(sTemp).position.rz));

                totalInfo = totalInfo + "         Координаты для карты radius= " + r1 + "   GetDistance2D= " + d2 + "      ";
            }
        }
    }
    else
    {
        if (IsEntity(loadedLocation))
        {
            GetCharacterPos(GetMainCharacter(), &locx, &locy, &locz);
            totalInfo = totalInfo + "id = " + mc.location + " (x,y,z)= " + locx + ", " + locy + ", " + locz;
            totalInfo = totalInfo + NewStr() + "filespath.models = " + loadedLocation.filespath.models;
            totalInfo = totalInfo + NewStr() + "image = " + loadedLocation.image;
            totalInfo = totalInfo + NewStr() + "models.locators = " + loadedLocation.models.always.locators;
            int attrName = locations[reload_location_index].index;
            totalInfo = totalInfo + NewStr() + "locationIDX = " + attrName;

            if (CheckAttribute(LoadedLocation, "islandId"))
            {
                totalInfo = totalInfo + NewStr() + "islandId = " + LoadedLocation.islandId;
            }

            if (CheckAttribute(LoadedLocation, "townsack"))
            {
                totalInfo = totalInfo + NewStr() + "townsack = " + LoadedLocation.townsack;
            }
        }
    }
    /*    
    aref rootItems;
    makearef(rootItems, worldMap);  //Islands[0]
    DumpAttributes(rootItems);
*/
    totalInfo = totalInfo + NewStr() + " MapShipX " + worldMap.playerShipX + " MapShipZ " + worldMap.playerShipZ + " X " + worldMap.island.x + " Z " + worldMap.island.z;

    totalInfo = totalInfo + NewStr() + " Map_Coord.X " + Map_GetRealCoordX(makefloat(worldMap.playerShipX)) + " Map_Coord.Z " + Map_GetRealCoordZ(makefloat(worldMap.playerShipZ));

    totalInfo = totalInfo + NewStr() + " Zero_Point_X " + makefloat(worldMap.zeroX) + " Zero_Point_Z " + makefloat(worldMap.zeroZ);
    // <
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    GetRealCoordsObjects();

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F3", 1);
}
////////////////////////////////////////////////////////////////////////
string descF4 = "Опыт команды +10";

void CalculateInfoDataF4()
{
    // -->
    totalInfo = descF4;

    ChangeCrewExp(pchar, "Sailors", 10);
    ChangeCrewExp(pchar, "Cannoners", 10);
    ChangeCrewExp(pchar, "Soldiers", 10);
    /*
    int i;
    for(i = 0; i < 200; i++)
        UpdateStore(&Stores[Villemstad_STORE]);
        
    for(i = 0; i < 200; i++)
        UpdateStore(&Stores[Tortuga_STORE]);    
*/
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F4", 1);
}
////////////////////////////////////////////////////////////////////////
string descF5 = "Ранг +1 (35 скилов)";
int BOAL_debug_num = 1;
void CalculateInfoDataF5()
{
    idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF5;

    pchar.Skill.FreeSkill = sti(pchar.Skill.FreeSkill) + 35;
    pchar.perks.FreePoints_self = sti(pchar.perks.FreePoints_self) + 25;
    pchar.perks.FreePoints_ship = sti(pchar.perks.FreePoints_ship) + 25;
	sld.perks.FreePoints_self = sti(sld.perks.FreePoints_self) + 25;
	sld.perks.FreePoints_ship = sti(sld.perks.FreePoints_ship) + 25;	
    // pchar.Perks.FreePerks = sti(pchar.perks.FreePoints_ship) + 15;
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                "Команда отработала успешно!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F5", 1);
}
////////////////////////////////////////////////////////////////////////
string descF6 = "Добавить навык 'Вызывающий доверие' и прокачать Харизму до 100";

void CalculateInfoDataF6()
{
    SetCharacterPerk(pchar, "Trustworthy");
	AddCharacterSkillDontClearExp(pchar, "Leadership", 100);

    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";

    SetFormatedText("INFO_TEXT", totalInfo);

    //ProcessCancelExit();
    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F6", 1);
}
////////////////////////////////////////////////////////////////////////
string descF7 = "Убрать навык 'Вызывающий доверие'";

void CalculateInfoDataF7()
{
	DeleteAttribute(pchar,"perks.list.Trustworthy");

    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
	
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F7", 1);
}
////////////////////////////////////////////////////////////////////////
string descF8 = "Улучшить отношения с индейцами";

void CalculateInfoDataF8()
{
	ChangeIndianRelation(10.00);

    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
	
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F8", 1);
}
////////////////////////////////////////////////////////////////////////
string descF9 = "Ухудшить отношения с индейцами";

void CalculateInfoDataF9()
{
	ChangeIndianRelation(-10.00);

    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
	
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F9", 1);
}
////////////////////////////////////////////////////////////////////////
string descF10 = "Бессмертие вкл/выкл";

void CalculateInfoDataF10()
{
    idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF10;
    ref mc;
    mc = GetMainCharacter();
    if (LAi_IsImmortal(mc))
    {
        LAi_SetImmortal(mc, false);
        Log_SetStringToLog("God mode OFF");
    }
    else
    {
        LAi_SetImmortal(mc, true);
        Log_SetStringToLog("God mode ON");
    }
    // <--
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                "Команда отработала успешно!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F10", 1);
}
////////////////////////////////////////////////////////////////////////
string descF11 = "Увеличить уровень +5";

void CalculateInfoDataF11()
{
	pchar.rank = sti(pchar.rank) + 5;
    Event("PlayerLevelUp", "l", sti(pchar.rank));
	
	totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
	
	SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F11", 1);
}
////////////////////////////////////////////////////////////////////////
//string descF12 = "НЗГ у всех наций +50";
string descF12 = "Увеличить макс. здоровье +50";

void CalculateInfoDataF12()
{
	LAi_SetHP(pchar,LAi_GetCharacterMaxHP(pchar)+50,LAi_GetCharacterMaxHP(pchar)+50);
	
	totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
	
	SetFormatedText("INFO_TEXT", totalInfo);
	 
	// Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F12", 1);
}

/*string descF13 = "Worldmap encounters ON/OFF";

void CalculateInfoDataF13()
{
    idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF13;

    ref mc;
    mc = GetMainCharacter();
    if(CheckAttribute(mc,"worldmapencountersoff") == 0)
    {
        mc.worldmapencountersoff = "1";
        Log_SetStringToLog("Worldmap encounters OFF");
    }
    else
    {
        if(mc.worldmapencountersoff == "1")
        {
            mc.worldmapencountersoff = "0";
            Log_SetStringToLog("Worldmap encounters ON");
        }
        else
        {
            mc.worldmapencountersoff = "1";
            Log_SetStringToLog("Worldmap encounters OFF");
        }
    }
    // <--
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "Команда отработала успешно!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
    
    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F13", 1);
}*/

string descF13 = "";
void CalculateInfoDataF13()
{

    ProcessCancelExit();
}

string descF14 = "Добавить офицера: Элен";

void CalculateInfoDataF14()
{
    // Элен:
    pchar.questTemp.Saga.Helena_officer = "true";
    sld = characterFromId("Helena");
    sld.greeting = "helena_hire";
    sld.quest.OfficerPrice = sti(pchar.rank) * 500;
    sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
    sld.loyality = MAX_LOYALITY;
    AddPassenger(pchar, sld, false);
    SetCharacterRemovable(sld, true);
    sld.Payment = true;
    sld.DontClearDead = true;
    sld.dialog.currentnode = "Helena_officer";
    LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    SaveCurrentNpcQuestDateParam(sld, "HiredDate");
    sld.rank = 35;
    LAi_SetHP(sld, 400.0, 400.0);
    SetSelfSkill(sld, 100, 90, 100, 100, 90);
    SetShipSkill(sld, 100, 90, 90, 90, 90, 90, 90, 90, 90);
    SetCharacterPerk(sld, "HardHitter");
    SetCharacterPerk(sld, "ByWorker");
    SetCharacterPerk(sld, "ByWorker2");
    SetCharacterPerk(sld, "Grus");
    GiveItem2Character(sld, "blade_31");
    sld.equip.blade = "blade_31";
    GiveItem2Character(sld, "pistol4");
    sld.equip.gun = "pistol4";
    GiveItem2Character(sld, "cirass4");
    EquipCharacterbyItem(sld, "cirass4");
    AddItems(sld, "cartridge", 50);
    //LAi_SetCharacterUseBullet(sld, "cartridge");
    AddItems(sld, "potion2", 10);
    AddItems(sld, "potion4", 5);

    ProcessCancelExit();
}

string descF15 = "Добавить офицера: Мэри";
void CalculateInfoDataF15()
{
    // Мэри:
    pchar.questTemp.LSC.Mary_officer = "true";
    sld = characterFromId("Mary");
    sld.quest.OfficerPrice = sti(pchar.rank) * 500;
    sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
    sld.CompanionDisable = true;       //нельзя в компаньоны
    sld.loyality = MAX_LOYALITY;
    AddPassenger(pchar, sld, false);
    SetCharacterRemovable(sld, true);
    sld.Payment = true;
    sld.DontClearDead = true;
    sld.dialog.currentnode = "Mary_officer";
    LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    SaveCurrentNpcQuestDateParam(sld, "HiredDate");
    sld.rank = 35;
    LAi_SetHP(sld, 500.0, 500.0);
    SetSelfSkill(sld, 100, 90, 100, 100, 90);
    SetShipSkill(sld, 100, 40, 40, 40, 40, 40, 40, 40, 40);
    SetCharacterPerk(sld, "HardHitter");
    SetCharacterPerk(sld, "ByWorker");
    SetCharacterPerk(sld, "ByWorker2");
    SetCharacterPerk(sld, "Grus");
    GiveItem2Character(sld, "blade_31");
    sld.equip.blade = "blade_31";
    GiveItem2Character(sld, "pistol4");
    sld.equip.gun = "pistol4";
    GiveItem2Character(sld, "cirass4");
    EquipCharacterbyItem(sld, "cirass4");
    AddItems(sld, "cartridge", 50);
    //LAi_SetCharacterUseBullet(sld, "cartridge");
    AddItems(sld, "potion2", 10);
    AddItems(sld, "potion4", 5);
	
    ProcessCancelExit();
}

string descF16 = "Добавить офицера: Тичингиту";
void CalculateInfoDataF16() 
{
// Тичингиту
    sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
    sld.name = "Тичингиту";
    sld.lastname = "";
    sld.greeting = "Tichingitu";
    sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
    sld.dialog.currentnode = "Tichingitu";
    sld.rank = 30;
    LAi_SetHP(sld, 380.0, 380.0);
    SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
    SetSelfSkill(sld, 90, 90, 100, 100, 90);
    SetShipSkill(sld, 40, 40, 40, 40, 40, 40, 40, 40, 40);
    SetCharacterPerk(sld, "Energaiser");
    SetCharacterPerk(sld, "BasicDefense");
    SetCharacterPerk(sld, "AdvancedDefense");
    SetCharacterPerk(sld, "CriticalHit");
    SetCharacterPerk(sld, "Tireless");
    SetCharacterPerk(sld, "HardHitter");
    SetCharacterPerk(sld, "Gunman");
    SetCharacterPerk(sld, "GunProfessional");
    SetCharacterPerk(sld, "SwordplayProfessional");
    SetCharacterPerk(sld, "Sliding");
    SetCharacterPerk(sld, "ByWorker");
    SetCharacterPerk(sld, "ByWorker2");
    SetCharacterPerk(sld, "Grus");
    AddItems(sld, "mushket6", 1);
    sld.CanTakeMushket = true;
    GiveItem2Character(sld, "blade_21");
    sld.equip.blade = "blade_21";
    GiveItem2Character(sld, "pistol5");
    sld.equip.gun = "pistol5";
    GiveItem2Character(sld, "cirass1");
    EquipCharacterbyItem(sld, "cirass1");
    AddItems(sld, "cartridge", 30);
    AddItems(sld, "GunEchin", 30);
    AddItems(sld, "GunPowder", 30);
    sld.quest.OfficerPrice = sti(pchar.rank) * 20;
    sld.OfficerWantToGo.DontGo = true;
    sld.CompanionDisable = true;
    sld.loyality = MAX_LOYALITY;
    AddPassenger(pchar, sld, false);
    SetCharacterRemovable(sld, true);
    sld.Payment = true;
    LAi_SetOfficerType(sld);
    sld.dialog.currentnode = "Tichingitu_officer";
    LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    SaveCurrentNpcQuestDateParam(sld, "HiredDate");
    AddItems(sld, "potion2", 7);
    AddItems(sld, "potion4", 3);
	
    ProcessCancelExit();
}

string descF17 = "Добавить офицера: Тонзага";
void CalculateInfoDataF17()
{
    // Тонзаг
    sld = characterFromId("Tonzag");
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.Dialog.currentnode = "hired";
    sld.quest.OfficerPrice = sti(pchar.rank) * 20;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddPassenger(pchar, sld, false);
    SetCharacterRemovable(sld, true);
    sld.Payment = true;
    LAi_SetOfficerType(sld);
    LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    SaveCurrentNpcQuestDateParam(sld, "HiredDate");
    sld.rank = 35;
    LAi_SetHP(sld, 450.0, 450.0);
    SetSelfSkill(sld, 90, 90, 100, 100, 90);
    SetShipSkill(sld, 50, 80, 80, 80, 80, 80, 80, 80, 80);
    SetCharacterPerk(sld, "HardHitter");
    SetCharacterPerk(sld, "Sliding");
    SetCharacterPerk(sld, "BladeDancer");
    SetCharacterPerk(sld, "SwordplayProfessional");
    SetCharacterPerk(sld, "Gunman");
    SetCharacterPerk(sld, "GunProfessional");
    SetCharacterPerk(sld, "ByWorker");
    SetCharacterPerk(sld, "ByWorker2");
    SetCharacterPerk(sld, "Grus");
    GiveItem2Character(sld, "topor_06");
    sld.equip.blade = "topor_06";
    GiveItem2Character(sld, "pistol8");
    sld.equip.gun = "pistol8";
    GiveItem2Character(sld, "cirass2");
    EquipCharacterbyItem(sld, "cirass2");
    AddItems(sld, "GunEchin", 50);
    AddItems(sld, "GunPowder", 50);
    //LAi_SetCharacterUseBullet(sld, "GunEchin");
    AddItems(sld, "potion2", 15);
    AddItems(sld, "potion4", 10);
	
    ProcessCancelExit();
}

string descF18 = "Добавить офицера: Томми";

void CalculateInfoDataF18()
{
	// Томми
	sld = GetCharacter(NPC_GenerateCharacter("Irons", "Irons", "man", "Irons", 12, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("BlackMark_5");
	sld.lastname = StringFromKey("BlackMark_6");
	sld.rank = 12;
	sld.CanTakeMushket = true;
	sld.PriorityMode = 2;
	sld.MusketerDistance = 10;
	SetSPECIAL(sld, 6, 9, 6, 3, 7, 6, 9);
	SetSelfSkill(sld, 15, 15, 50, 60, 20);
	SetShipSkill(sld, 5, 1, 4, 6, 1, 1, 7, 1, 10);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Jager"); //Егерь
	SetCharacterPerk(sld, "Sniper"); //Снайпер
	GiveItem2Character(sld, "cirass10");
	EquipCharacterByItem(sld, "cirass10");
	GiveItem2Character(sld, "blade_42");
	EquipCharacterByItem(sld, "blade_42");
	GiveItem2Character(sld, "indian_2");
	GiveItem2Character(sld, "mushket1");
	EquipCharacterByItem(sld, "mushket1");
	AddItems(sld, "potionrum", 5);
	AddItems(sld, "GunPowder", 15);
	AddItems(sld, "bullet", 15);
	LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.quest.OfficerPrice = 15000;
	sld.OfficerWantToGo.DontGo = true;
	sld.CompanionDisable = true;
	sld.loyality = MAX_LOYALITY;
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, true);
	sld.Payment = true;
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0; 
	sld.Health.maxHP    = 60.0;
	SetCharacterPerk(sld, "ShipEscape");
	sld.CanTakeMushket = true;
	LAi_SetOfficerType(sld);
	sld.dialog.filename = "Quest\BlackMark.c";
	sld.Dialog.CurrentNode = "Irons_officer";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	SaveCurrentNpcQuestDateParam(sld, "HiredDate");
	LAi_SetHP(sld, 170.0, 170.0);
			
    ProcessCancelExit();
}

string descF19 = "Добавить офицера: Дюрана";
void CalculateInfoDataF19()
{
	sld = GetCharacter(NPC_GenerateCharacter("Duran", "Claude_Durand", "man", "man", 15, FRANCE, -1, false, "soldier"));
	sld.name = StringFromKey("FMQ_49");
	sld.lastname = StringFromKey("FMQ_50");
	sld.Dialog.Filename = "Enc_Officer_dialog.c";
	sld.Dialog.CurrentNode = "hired";
	sld.rank = 15;
	sld.reputation = 25;
	LAi_SetHP(sld, 180, 180);
	SetSelfSkill(sld, 45, 50, 45, 45, 35);
	SetShipSkill(sld, 25, 10, 20, 20, 20, 20, 20, 20, 30);
	SetSPECIAL(sld, 8, 5, 8, 4, 6, 8, 5);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Tireless");
	sld.SuperShooter = true;
	sld.quest.OfficerPrice = sti(pchar.rank) * 20;
	sld.OfficerWantToGo.DontGo = true;
	sld.loyality = MAX_LOYALITY;
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, true);
	sld.Payment = true;
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
	sld.greeting = "Duran_officer";
	LAi_SetOfficerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0; 
	sld.Health.maxHP    = 60.0;
	SetCharacterPerk(sld, "ShipEscape");
	
    ProcessCancelExit();
}

string descF20 = "Добавить офицера: Книппеля";
void CalculateInfoDataF20()
{
    //Чарли
	sld = GetCharacter(NPC_GenerateCharacter("Knippel", "Kneepel", "man", "man_B", 20, ENGLAND, -1, false, "quest"));
	sld.name = "Чарли";
	sld.lastname = "Книппель";
	sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
	sld.Dialog.CurrentNode = "Knippel_officer";
	sld.rank = 20;
	LAi_SetHP(sld, 120, 120);
	SetSelfSkill(sld, 10, 12, 10, 10, 70);
	SetShipSkill(sld, 50, 20, 75, 75, 45, 20, 20, 10, 15);
	SetSPECIAL(sld, 9, 10, 6, 5, 5, 5, 9);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "Ciras");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "AgileMan");
	SetCharacterPerk(sld, "BladeDancer");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "ByWorker2");
	GiveItem2Character(sld, "shamshir");
	sld.equip.blade = "shamshir";
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "pistol1");
	AddItems(sld, "cartridge", 50);
	TakeNItems(sld,"potion4", 20);
	//LAi_SetCharacterUseBullet(sld, "cartridge");
	sld.money = 1000;
	sld.quest.OfficerPrice = sti(pchar.rank)*200;
	sld.OfficerWantToGo.DontGo = true;
	sld.loyality = MAX_LOYALITY;
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0; 
	sld.Health.maxHP    = 60.0;
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, true);
	sld.Payment = true;
	LAi_SetOfficerType(sld);
	sld.greeting = "knippel_hire";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	
	ProcessCancelExit();
}

string descF21 = "Свободный полёт камеры";
void CalculateInfoDataF21()
{
    totalInfo = descF21;
    // -->
    //locCameraLockNearHero(-5.0, 2.0, -5.0, 200, true);
    SendMessage(&locCamera, "l", MSG_CAMERA_FREE);
    locCameraCurMode = LOCCAMERA_FREE;

    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F21", 1);
}

string descF22 = "Сделать доступными все возможные рецепты алхимии";
void CalculateInfoDataF22()
{
    pchar.alchemy.known = 1;
    SetCharacterPerk(pchar, "Alchemy");
    ref item;
    for (int n = 0; n < ITEMS_QUANTITY; n++)
    {
        item = &Items[n];
        if (CheckAttribute(item, "multiobject"))
        {
            string sGood = item.id;
            pchar.alchemy.(sGood).isKnown = true;
        }
    }

    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F22", 1);
}

string descF23 = "Дамп аттрибутов камеры";
void CalculateInfoDataF23()
{
    float xx, xy, xz, yx, yy, yz, zx, zy, zz;
    totalInfo = descF23;
    // -->
    DumpAttributes(&Camera);

    float sinAx = sin(stf(Camera.ang.x));
    float cosAx = cos(stf(Camera.ang.x));
    float sinAy = sin(stf(Camera.ang.y));
    float cosAy = cos(stf(Camera.ang.y));
    float sinAz = sin(stf(Camera.ang.z));
    float cosAz = cos(stf(Camera.ang.z));

    xx = cosAz * cosAy + sinAz * sinAx * sinAy;
    xy = sinAz * cosAx;
    xz = cosAz * (-sinAy) + sinAz * sinAx * cosAy;

    zx = cosAx * sinAy;
    zy = -sinAx;
    zz = cosAx * cosAy;

    yx = -sinAz * cosAy + cosAz * sinAx * sinAy;
    yy = cosAz * cosAx;
    yz = -sinAz * (-sinAy) + cosAz * sinAx * cosAy;

    totalInfo += "\n\nCamera.pos.x == " + Camera.pos.x +
                 "\nCamera.pos.y = " + Camera.pos.y +
                 "\nCamera.pos.z == " + Camera.pos.z +
                 "\n\nCamera.ang.z == " + Camera.ang.z +
                 "\nCamera.ang.y == " + Camera.ang.y +
                 "\nCamera.ang.x == " + Camera.ang.x +
                 "\n XX == " + xx +
                 "\n XY == " + xy +
                 "\n XZ == " + xz +
                 "\n YX == " + yx +
                 "\n YY == " + yy +
                 "\n YZ == " + yz +
                 "\n ZX == " + zx +
                 "\n ZX == " + zy +
                 "\n ZZ == " + zz +
                 "\n\n";
    // <--
    DoQuestFunctionDelay("Norman_ChangeUsualFace", 0.5);
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F23", 1);
}

string descF24 = "Выдать Аркебузу и включить возможность ее прокачки";
void CalculateInfoDataF24()
{
	totalInfo = descF24;
	ref itm;
	makeref(itm, items[FindItem("mushket9")]);
	itm.UpgradeStage = 1;
	GiveItem2Character(pchar, "mushket9");
	
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F24", 1);
}

string descF25 = "Выдать запчасть от Аркебузы";
void CalculateInfoDataF25()
{
	totalInfo = descF25;
	GiveItem2Character(pchar, "FirearmStockPart");
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    ProcessCancelExit();
    Statistic_AddValue(PChar, "Cheats.F25", 1);
}

string descF26 = "Дамп атрибутов ГГ";
void CalculateInfoDataF26()
{
    totalInfo = descF26;
    // -->
    ref characterRef = GetMainCharacter();
    float sdp = 0.0;

    if (shipType != SHIP_NOTUSED)
        sdp = GetAllSailsDamagePercent(characterRef);
    trace(" spd = " + sdp);
    trace(" sailpercent = " + GetSailPercent(characterRef));

    trace("==================== " + characterRef.ID + " ====================");
    DumpAttributes(characterRef);
    trace("========================================");

    ref realShip;
    int shipType = sti(characterRef.Ship.Type);

    if (shipType != SHIP_NOTUSED) // Есть ли корабль вообще
    {
        realShip = GetRealShip(shipType);
        DumpAttributes(realShip);
        trace("========================================");
    }

    string sGun = GetCharacterEquipByGroup(characterRef, GUN_ITEM_TYPE);
    if (sGun != "")
    {
        ref rItm = ItemsFromID(sGun);
        trace("==================== " + rItm.ID + " ====================");
        DumpAttributes(rItm);
        trace("========================================");
    }

    Log_Info("Дамп аттрибутов ГГ");
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.26", 1);
}

string descF27 = "Выдать Устав";
void CalculateInfoDataF27()
{
    totalInfo = descF27;
   
    GiveItem2Character(pchar, "talisman18");
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F27", 1);
}

string descF28 = "Прокачать Устав";
void CalculateInfoDataF28()
{
    totalInfo = descF28;
    
	addArticlesBonus();
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F28", 1);
}

string descF29 = "НЗГ у всех наций 50";
void CalculateInfoDataF29()
{
    totalInfo = descF29;
    // -->
    for (int j = 0; j < MAX_NATIONS; j++)
    {
        ChangeCharacterNationReputation(pchar, j, -50);
    }
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F29", 1);
}

string descF30 = "+20 дней";
void CalculateInfoDataF30()
{
    totalInfo = descF30;
    // -->
    LAi_Fade("", "");
    AddDataToCurrent(0, 0, 20);
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F30", 1);
}

string descF31 = "Супер корабль, полная прокачка ГГ, все перки, предметы";
void CalculateInfoDataF31()
{
    ref mc;
    string sEquipItem;
    totalInfo = descF31;
    mc = GetMainCharacter();
    SetRandSelfSkill(mc, 100, 100);
    SetRandShipSkill(mc, 100, 100);
    mc.rank = 20;
    Event("PlayerLevelUp", "l", sti(mc.rank));
    LAi_SetHP(mc, 250.0, 250.0);

    mc.Ship.Type = GenerateShipExt(SHIP_FRIGATE, true, mc);
//	mc.Ship.Type = GenerateShipExt(SHIP_LSHIP_SPA, true, mc);
    SetBaseShipData(mc);

    //    mc.Ship.Masts.mast1   = 1;
    //    mc.Ship.Masts.mast201 = 1;

    mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
    SetCrewQuantityFull(mc);
    AddCrewMorale(mc, 100);
    ChangeCrewExp(mc, "Sailors", 100);
    ChangeCrewExp(mc, "Cannoners", 100);
    ChangeCrewExp(mc, "Soldiers", 100);

    SetCharacterGoods(mc, GOOD_BALLS, 500);
    SetCharacterGoods(mc, GOOD_GRAPES, 500);
    SetCharacterGoods(mc, GOOD_KNIPPELS, 500);
    SetCharacterGoods(mc, GOOD_BOMBS, 500);
    SetCharacterGoods(mc, GOOD_FOOD, 500);
    SetCharacterGoods(mc, GOOD_POWDER, 1000);
    SetCharacterGoods(mc, GOOD_WEAPON, 500);

    sEquipItem = GetCharacterEquipByGroup(mc, BLADE_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);
    sEquipItem = GetCharacterEquipByGroup(mc, GUN_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);
    sEquipItem = GetCharacterEquipByGroup(mc, SPYGLASS_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);
    sEquipItem = GetCharacterEquipByGroup(mc, CIRASS_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);

    AddMoneyToCharacter(mc, 10000000);
	AddItems(pchar, "gold_dublon", 500);
    AddItems(mc, "spyglass5", 1);
    AddItems(mc, "pistol5", 1);
	GiveItem2Character(pchar, "talisman2");

    sEquipItem = GetGeneratedItem("blade_25");
    AddItems(mc, sEquipItem, 1);
    AddItems(mc, "cirass4", 1);

    EquipCharacterbyItem(mc, "spyglass5");
    EquipCharacterbyItem(mc, "pistol5");
    EquipCharacterbyItem(mc, sEquipItem);
    EquipCharacterbyItem(mc, "cirass4");
	EquipCharacterByItem(pchar, "talisman2");

    AddItems(mc, "cartridge", 50);
    AddItems(mc, "bullet", 50);
    AddItems(mc, "grapeshot", 20);
    AddItems(mc, "gunpowder", 50);

    AddItems(mc, "amulet_7", 1);
	
    //LAi_SetCharacterUseBullet(mc, "cartridge");

    SetAllPerksToChar(mc, false);
	AddCharacterGoodsSimple(pchar, GOOD_FOOD, 3000);
	AddCharacterGoodsSimple(pchar, GOOD_RUM, 300);
	//SetHalfPerksToChar(mc, false);
	
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F31", 1);
}

string descF32 = "Простой корабль, неполная прокачка ГГ";
void CalculateInfoDataF32()
{
    ref mc;
    string sEquipItem;
    totalInfo = descF32;
    mc = GetMainCharacter();
    SetRandSelfSkill(mc, 60, 85);
    SetRandShipSkill(mc, 60, 85);
    mc.rank = 22;
    Event("PlayerLevelUp", "l", sti(mc.rank));
    LAi_SetHP(mc, 250.0, 250.0);

    // mc.Ship.Type = GenerateShipExt(SHIP_CORVETTE_QUEST, true, mc);
    mc.Ship.Type = GenerateShipExt(SHIP_CORVETTE, true, mc);
    // mc.Ship.Type = GenerateShipExt(SHIP_ELCASADOR, true, mc);
    SetBaseShipData(mc);
    mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
    /*
    //mc.Ship.Type = GenerateShipHand(SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
    mc.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 700, 40, 610, 16000, 15.2, 58.8, 1.42);
    mc.Ship.name = "Сумрак";
    SetBaseShipData(mc);
    mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
    SetCrewQuantityFull(mc);
    mc.Ship.Crew.Morale = 80;
    mc.Ship.Crew.Exp.Sailors = 90;
    mc.Ship.Crew.Exp.Cannoners = 70;
    mc.Ship.Crew.Exp.Soldiers = 70;
    SetCharacterGoods(mc, GOOD_BALLS, 100);
    SetCharacterGoods(mc, GOOD_GRAPES, 100);
    SetCharacterGoods(mc, GOOD_KNIPPELS, 100);
    SetCharacterGoods(mc, GOOD_BOMBS, 100);
    SetCharacterGoods(mc, GOOD_FOOD, 100);
    SetCharacterGoods(mc, GOOD_POWDER, 300);
    SetCharacterGoods(mc, GOOD_WEAPON, 60);
    SetCharacterGoods(mc, GOOD_MEDICAMENT, 60); 
*/

    //mc.Ship.Type = GenerateShipExt(SHIP_XebekVML, true, mc);

    //    mc.Ship.Masts.mast2   = 1;
    //    mc.Ship.Masts.mast201 = 1;
       
//    mc.Ship.Masts.mast2   = 1;
//    mc.Ship.Masts.mast201 = 1;
/*
    mc.Ship.Masts.mast3   = 1;
    mc.Ship.Masts.mast301 = 1;
    mc.Ship.Masts.mast4   = 1;
    mc.Ship.Masts.mast401 = 1;
    mc.Ship.Masts.mast5   = 1;
*/
    //mc.ship.SP = CalculateShipSP(mc);

    //    trace("fail masts " + GetShipFallMastsQuantity(mc) + " ship.sp " + mc.ship.SP);
    //mc.ship.HP = sti(mc.ship.HP) - makeint(sti(mc.ship.HP) / 2);

    //    ShipRepair(mc);
//
    SetCrewQuantityFull(mc);
    AddCrewMorale(mc, 80);
    ChangeCrewExp(mc, "Sailors", 50);
    ChangeCrewExp(mc, "Cannoners", 50);
    ChangeCrewExp(mc, "Soldiers", 50);

    SetCharacterGoods(mc, GOOD_BALLS, 300);
    SetCharacterGoods(mc, GOOD_GRAPES, 300);
    SetCharacterGoods(mc, GOOD_KNIPPELS, 300);
    SetCharacterGoods(mc, GOOD_BOMBS, 300);
    SetCharacterGoods(mc, GOOD_FOOD, 300);
    SetCharacterGoods(mc, GOOD_POWDER, 700);
    SetCharacterGoods(mc, GOOD_WEAPON, 300);

    SetCharacterGoods(mc, GOOD_PLANKS, 10);
    SetCharacterGoods(mc, GOOD_SAILCLOTH, 10);

    // для отладки контрабаса
    //SetCharacterGoods(mc, GOOD_SLAVES, 50);
    /*    
    SetCharacterGoods(mc, GOOD_SHIPSILK, 30);
    SetCharacterGoods(mc, GOOD_ROPES, 30);
    SetCharacterGoods(mc, GOOD_SANDAL, 30);
    SetCharacterGoods(mc, GOOD_OIL, 30);
*/

    sEquipItem = GetCharacterEquipByGroup(mc, BLADE_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);
    sEquipItem = GetCharacterEquipByGroup(mc, GUN_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);
    sEquipItem = GetCharacterEquipByGroup(mc, SPYGLASS_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);
    sEquipItem = GetCharacterEquipByGroup(mc, CIRASS_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);

    AddMoneyToCharacter(mc, 300000);
	// AddItems(pchar, "gold_dublon", 500);
    AddItems(mc, "spyglass3", 1);
    AddItems(mc, "pistol5", 1);

    sEquipItem = GetGeneratedItem("blade_25");
    AddItems(mc, sEquipItem, 1);

    AddItems(mc, "cirass3", 1);

    EquipCharacterbyItem(mc, "spyglass3");
    EquipCharacterbyItem(mc, "pistol5");
    EquipCharacterbyItem(mc, sEquipItem);
    EquipCharacterbyItem(mc, "cirass3");

    AddItems(mc, "cartridge", 50);
    AddItems(mc, "bullet", 50);
    AddItems(mc, "gunpowder", 50);
    AddItems(mc, "grapeshot", 20);
    AddItems(mc, "talisman7", 1);
    AddItems(mc, "amulet_7", 2);

    //LAi_SetCharacterUseBullet(mc, "cartridge");

        SetHalfPerksToChar(mc, false);
    // SetAllPerksToChar(mc, false);

    ref realShip;
    int shipType = sti(mc.Ship.Type);

    if (shipType != SHIP_NOTUSED) // Есть ли корабль вообще
    {
        realShip = GetRealShip(shipType);
        //        realShip.HP = sti(realShip.HP) - makeint(sti(realShip.HP)/5);
    }

    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F32", 1);
}

string descF33 = "Апгрейд-тестирование";
void CalculateInfoDataF33()
{
    ref mc;
    string sEquipItem;
    totalInfo = descF33;
    mc = GetMainCharacter();
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";

    SetFormatedText("INFO_TEXT", totalInfo);

    /*SetRandSelfSkill(mc, 50, 85);
    SetRandShipSkill(mc, 50, 85);
    mc.rank = 15;
    Event("PlayerLevelUp", "l", sti(mc.rank));
    LAi_SetHP(mc, 250.0, 250.0);
    mc.Ship.Type = GenerateShipExt(SHIP_CORVETTE, true, mc);    
    SetBaseShipData(mc);
    mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
    
    SetCrewQuantityFull(mc);
    AddCrewMorale(mc, 100);    
    ChangeCrewExp(mc, "Sailors", 100);
    ChangeCrewExp(mc, "Cannoners", 100);
    ChangeCrewExp(mc, "Soldiers", 100);

    SetCharacterGoods(mc, GOOD_BALLS, 700);
    SetCharacterGoods(mc, GOOD_GRAPES, 700);
    SetCharacterGoods(mc, GOOD_KNIPPELS, 700);
    SetCharacterGoods(mc, GOOD_BOMBS, 700);
    SetCharacterGoods(mc, GOOD_FOOD, 500);
    SetCharacterGoods(mc, GOOD_POWDER, 2000);
    SetCharacterGoods(mc, GOOD_WEAPON, 500);
    
    sEquipItem = GetCharacterEquipByGroup(mc, BLADE_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);
    sEquipItem = GetCharacterEquipByGroup(mc, GUN_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);
    sEquipItem = GetCharacterEquipByGroup(mc, SPYGLASS_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);
    sEquipItem = GetCharacterEquipByGroup(mc, CIRASS_ITEM_TYPE);
    RemoveItems(mc, sEquipItem, 1);

    AddMoneyToCharacter(mc, 5000000);
    AddItems(mc, "spyglass3", 1);
    AddItems(mc, "pistol5", 1);
    
    sEquipItem = GetGeneratedItem("blade_25");
    AddItems(mc, sEquipItem, 1);
    
    AddItems(mc, "cirass3", 1);

    EquipCharacterbyItem(mc, "spyglass3");
    EquipCharacterbyItem(mc, "pistol5");
     EquipCharacterbyItem(mc, sEquipItem);
     EquipCharacterbyItem(mc, "cirass3");
     
    AddItems(mc, "cartridge", 50);
    AddItems(mc, "bullet", 50);
    AddItems(mc, "gunpowder", 50);
    AddItems(mc, "grapeshot", 20);
    LAi_SetCharacterUseBullet(mc, "cartridge");
    
    SetAllPerksToChar(mc, false);*/
    SetCharacterGoods(mc, GOOD_SHIPSILK, 1000);
    SetCharacterGoods(mc, GOOD_ROPES, 1000);
    SetCharacterGoods(mc, GOOD_SANDAL, 1000);
    SetCharacterGoods(mc, GOOD_OIL, 1000);

    AddItems(mc, "chest", 10);
    AddItems(mc, "icollection", 1);
    AddItems(mc, "jewelry1", 50);
    AddItems(mc, "jewelry2", 50);
    AddItems(mc, "jewelry3", 50);
    AddItems(mc, "jewelry4", 50);
    AddItems(mc, "jewelry5", 50);
    AddItems(mc, "jewelry6", 50);
    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F32", 1);
}

void ShipRepair(ref chr)
{
    int hp = MakeInt(GetHullPercent(chr));
    int sp = MakeInt(GetSailPercent(chr));
    trace("hp " + hp + " sp " + sp);

    // процент ремонта в день (при ремонте на глобальной карте)
    float sail_RPD = GetSailRPD(chr);
    float hull_RPD = GetHullRPD(chr);
    trace("hull_RPD " + hull_RPD + " sail_RPD " + sail_RPD);

    float timeHull, timeSail, timeMast;

    timeHull = 0.0;
    timeSail = 0.0;
    timeMast = 0.0;

    float SailDamagePercent = 100.0 - GetSailPercent(chr);
    float HullDamagePercent = 100.0 - GetHullPercent(chr);

    if (HullDamagePercent > 0.0)
    {
        timeHull = HullDamagePercent * (8 - GetCharacterShipClass(chr));
    }
    if (SailDamagePercent > 0.0)
    {
        timeSail = SailDamagePercent * (8 - GetCharacterShipClass(chr));
    }

    // кол-во материала на один процент ремонта
    float sail_SPP = GetSailSPP(chr);
    float hull_PPP = GetHullPPP(chr);
    trace("hull_PPP " + hull_PPP + " sail_SPP " + sail_SPP);

    float matQ;
    int shMastFall = GetShipFallMastsQuantity(chr);

    trace("timeHull " + timeHull + " timeSail " + timeSail + " time (hours) : " + makeint((timeHull / 4.0 + timeSail / 6.0)));

    if (shMastFall > 0)
    {
        matQ = 15.0 * GetHullPPP(chr);
    }
}

float GetMaxSpeedZ(float fWindAgainstSpeed, float fWindDotShip)
{
    float fMaxSpeedZ = 10.0;
    float BtWindR = 1.0 - fWindAgainstSpeed;
    float fkoeff = fWindAgainstSpeed;
    if (fkoeff < 1.0)
        fkoeff = 1.0;

    if (fWindDotShip < BtWindR) // по ветру
    {
        fMaxSpeedZ = fMaxSpeedZ * (1.0 + 0.974 * (fWindDotShip - BtWindR) / (1.0 + BtWindR));
    }
    else // против ветра
    {
        fMaxSpeedZ = fkoeff * fMaxSpeedZ * (1.0 - (fWindDotShip - BtWindR) / 2.0);
    }
    return fMaxSpeedZ;
}

void ReloadByStr()
{
    // разбор строки
    string loc = stripblank(GetSubStringByNum(GameInterface.reload_edit.str, 0));
    string grp = stripblank(GetSubStringByNum(GameInterface.reload_edit.str, 1));
    string ltr = stripblank(GetSubStringByNum(GameInterface.reload_edit.str, 2));

    int i = FindLocation(loc);
    if (i != -1)
    {
        if (CheckAttribute(&locations[i], "fastreload"))
        {
            if (GetCityFrom_Sea(locations[i].fastreload) != "")
            {
                setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
                setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
            }
        }
        else
        {
            if (locations[i].type == "seashore" || locations[i].type == "mayak")
            {
                setCharacterShipLocation(pchar, loc));
                setWDMPointXZ(loc);
            }
        }
        DoQuestReloadToLocation(loc, grp, ltr, "");
        Log_Info(loc);

        // Статистика по читам
        Statistic_AddValue(PChar, "Cheats.ReloadByStr", 1);
    }
    else
    {
        Log_Info("Нет локации");
    }
}

void XI_SetScroller(float pos)
{
    SendMessage(&GameInterface, "lsf", MSG_INTERFACE_SET_SCROLLER, "QUESTSCROLL", pos);
}

void SetScrollerPos()
{
    string nodName = GetEventData();
    float pos = GetEventData();
    XI_SetScroller(pos);
}

void ProcScrollPosChange()
{
    float newPos = GetEventData();
    SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 2, newPos);
}

void ProcScrollChange()
{
    int changeNum = GetEventData();
    if (changeNum == 0)
        return;
    string controlNode = "";
    if (GetSelectable("INFO_TEXT"))
        controlNode = "INFO_TEXT";

    if (controlNode != "")
    {
        if (changeNum > 0)
        {
            SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, controlNode, -1, 0, ACTION_DOWNSTEP);
        }
        else
        {
            SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, controlNode, -1, 0, ACTION_UPSTEP);
        }
    }
}

void GetRealCoordsObjects()
{
    trace("---------");
    trace("Barbados (island)                    : " + Map_GetRealCoordX(946.0062) + " " + Map_GetRealCoordZ(-486.9014));
    trace("Бриджтаун                             : " + Map_GetRealCoordX(903.6217) + " " + Map_GetRealCoordZ(-522.2799));
    trace("Mayak2 (маяк Барбадоса)                : " + Map_GetRealCoordX(918.619) + " " + Map_GetRealCoordZ(-506.827));
    trace("Shore4 (мыс Гаррисон)                : " + Map_GetRealCoordX(919.808) + " " + Map_GetRealCoordZ(-448.061));
    trace("Shore5 (мыс Раггед Пойнт)            : " + Map_GetRealCoordX(983.787) + " " + Map_GetRealCoordZ(-518.14));
    trace("---------");
    trace("Antigua (island)                        : " + Map_GetRealCoordX(903.9222) + " " + Map_GetRealCoordZ(109.0605));
    trace("Сент-Джонс                             : " + Map_GetRealCoordX(852.4083) + " " + Map_GetRealCoordZ(128.9092));
    trace("Shore1 (мыс Бун)                        : " + Map_GetRealCoordX(880.892) + " " + Map_GetRealCoordZ(148.897));
    trace("Shore2 (залив Уиллогби)                : " + Map_GetRealCoordX(931.028) + " " + Map_GetRealCoordZ(74.5353));
    trace("---------");
    trace("Curacao (island)                     : " + Map_GetRealCoordX(383.4142) + " " + Map_GetRealCoordZ(-691.11));
    trace("Виллемштадт                             : " + Map_GetRealCoordX(396.1) + " " + Map_GetRealCoordZ(-722.8));
    trace("Shore22 (Пальмовый берег)            : " + Map_GetRealCoordX(354.604) + " " + Map_GetRealCoordZ(-678.54));
    trace("Shore23 (Мыс Кальвинистов)            : " + Map_GetRealCoordX(347.313) + " " + Map_GetRealCoordZ(-705.112));
    trace("Shore24 (берег Приют Контрабандиста)    : " + Map_GetRealCoordX(455.427) + " " + Map_GetRealCoordZ(-740.655));
    trace("---------");
    trace("SentMartin (island)                    : " + Map_GetRealCoordX(921.559) + " " + Map_GetRealCoordZ(523.596));
    trace("Мариго                                 : " + Map_GetRealCoordX(900.0994) + " " + Map_GetRealCoordZ(501.6531));
    trace("Shore40 (берег Спасения)                : " + Map_GetRealCoordX(924.442) + " " + Map_GetRealCoordZ(554.385));
    trace("Shore41 (бухта Неистового ветра)        : " + Map_GetRealCoordX(898.877) + " " + Map_GetRealCoordZ(522.703));
    trace("---------");
    trace("Guadeloupe (island)                    : " + Map_GetRealCoordX(537.114) + " " + Map_GetRealCoordZ(-25.3853));
    trace("Бас-Тер                                 : " + Map_GetRealCoordX(462.2107) + " " + Map_GetRealCoordZ(-73.0837));
    trace("Mayak4 (маяк Гваделупы)                : " + Map_GetRealCoordX(465.076) + " " + Map_GetRealCoordZ(-38.9423));
    trace("Shore28 (бухта Морн л'О)                : " + Map_GetRealCoordX(536.636) + " " + Map_GetRealCoordZ(26.1279));
    trace("Shore29 (пляж Капстер)                : " + Map_GetRealCoordX(507.669) + " " + Map_GetRealCoordZ(-75.4176));
    trace("Shore30 (бухта Гран Бур)                : " + Map_GetRealCoordX(549.807) + " " + Map_GetRealCoordZ(-69.7107));
    trace("Shore31 (мыс Недоступный)            : " + Map_GetRealCoordX(589.889) + " " + Map_GetRealCoordZ(-65.0601));
    trace("---------");
    trace("Martinique (island)                     : " + Map_GetRealCoordX(538.524) + " " + Map_GetRealCoordZ(-385.567));
    trace("Сен-Пьер                             : " + Map_GetRealCoordX(513.51) + " " + Map_GetRealCoordZ(-397.645));
    trace("Ле-Франсуа                             : " + Map_GetRealCoordX(559.008) + " " + Map_GetRealCoordZ(-368.16));
    trace("Shore38 (пляж Ламантен)                : " + Map_GetRealCoordX(481.181) + " " + Map_GetRealCoordZ(-340.832));
    trace("Shore39 (бухта Ле Марен)                : " + Map_GetRealCoordX(557.181) + " " + Map_GetRealCoordZ(-422.987));
    trace("---------");
    trace("Bermudes (island)                    : " + Map_GetRealCoordX(920.738) + " " + Map_GetRealCoordZ(920.767));
    trace("Шарптаун                             : " + Map_GetRealCoordX(931.059) + " " + Map_GetRealCoordZ(928.281));
    trace("Shore3 (залив Руны)                    : " + Map_GetRealCoordX(915.745) + " " + Map_GetRealCoordZ(966.469));
    trace("Shore_ship1 (бухта Разбитого Корыта) : " + Map_GetRealCoordX(968.947) + " " + Map_GetRealCoordZ(923.636));
    trace("---------");
    trace("Maracaibo (areal)                     : " + Map_GetRealCoordX(178.51) + " " + Map_GetRealCoordZ(-870.37));
    trace("Маракайбо                             : " + Map_GetRealCoordX(134.82) + " " + Map_GetRealCoordZ(-939.65));
    trace("Shore37 (бухта Гуахира)                : " + Map_GetRealCoordX(140.753) + " " + Map_GetRealCoordZ(-828.99));
    trace("Shore_ship3 (мыс Несбывшихся Надежд)    : " + Map_GetRealCoordX(198.162) + " " + Map_GetRealCoordZ(-994.035));
    trace("---------");
    trace("Beliz (areal)                         : " + Map_GetRealCoordX(-896.084) + " " + Map_GetRealCoordZ(230.227));
    trace("Shore_ship2 (залив Гибели)            : " + Map_GetRealCoordX(-1022.94) + " " + Map_GetRealCoordZ(629.355));
    trace("Shore6 (мыс Каточе)                    : " + Map_GetRealCoordX(-909.655) + " " + Map_GetRealCoordZ(629.079));
    trace("Shore7 (залив Косумель)                : " + Map_GetRealCoordX(-915.581) + " " + Map_GetRealCoordZ(409.002));
    trace("Shore8 (бухта Четумаль)                : " + Map_GetRealCoordX(-963.489) + " " + Map_GetRealCoordZ(281.628));
    trace("Белиз                                 : " + Map_GetRealCoordX(-978.396) + " " + Map_GetRealCoordZ(158.751));
    trace("Shore9 (бухта Аматике)                : " + Map_GetRealCoordX(-1017.2) + " " + Map_GetRealCoordZ(-33.7293));
    trace("Shore10 (лагуна Каратаска)            : " + Map_GetRealCoordX(-818.198) + " " + Map_GetRealCoordZ(-177.208));
    trace("---------");
    trace("Jamaica (island)                        : " + Map_GetRealCoordX(-298.0) + " " + Map_GetRealCoordZ(-128.0));
    trace("Порт-Ройал                             : " + Map_GetRealCoordX(-250.157) + " " + Map_GetRealCoordZ(-150.839));
    trace("Shore35 (мыс Негрил)                    : " + Map_GetRealCoordX(-446.951) + " " + Map_GetRealCoordZ(-107.118));
    trace("Shore36 (бухта Портленд)                : " + Map_GetRealCoordX(-281.543) + " " + Map_GetRealCoordZ(-164.245));
    trace("Mayak3 (маяк Порт Рояля)                : " + Map_GetRealCoordX(-224.127) + " " + Map_GetRealCoordZ(-163.435));
    trace("---------");
    trace("PuertoRico (island)                     : " + Map_GetRealCoordX(506.489) + " " + Map_GetRealCoordZ(460.815));
    trace("Сан-Хуан                             : " + Map_GetRealCoordX(528.645) + " " + Map_GetRealCoordZ(484.18));
    trace("Shore44 (бухта Агуадилья)            : " + Map_GetRealCoordX(392.82) + " " + Map_GetRealCoordZ(501.808));
    trace("Shore45 (пляж Фахардо)                : " + Map_GetRealCoordX(602.049) + " " + Map_GetRealCoordZ(458.322));
    trace("---------");
    trace("Cuba1 (areal)                         : " + Map_GetRealCoordX(-358.027) + " " + Map_GetRealCoordZ(819.223));
    trace("Сантьяго                             : " + Map_GetRealCoordX(-339.796) + " " + Map_GetRealCoordZ(771.839));
    trace("Пуэрто-Принсипе                         : " + Map_GetRealCoordX(-282.032) + " " + Map_GetRealCoordZ(839.056));
    trace("Shore11 (мыс Камагуэй)                : " + Map_GetRealCoordX(-386.907) + " " + Map_GetRealCoordZ(883.044));
    trace("Shore12 (залив Анна Мария)            : " + Map_GetRealCoordX(-468.486) + " " + Map_GetRealCoordZ(838.497));
    trace("Mayak9 (маяк Сантьяго)                : " + Map_GetRealCoordX(-333.295) + " " + Map_GetRealCoordZ(723.486));
    trace("---------");
    trace("Cuba2 (areal)                         : " + Map_GetRealCoordX(-640.61) + " " + Map_GetRealCoordZ(870.058));
    trace("Гавана                                 : " + Map_GetRealCoordX(-663.685) + " " + Map_GetRealCoordZ(913.862));
    trace("Shore13 (залив Батабано)                : " + Map_GetRealCoordX(-613.56) + " " + Map_GetRealCoordZ(886.009));
    trace("Shore14 (бухта Хувентуд)                : " + Map_GetRealCoordX(-653.269) + " " + Map_GetRealCoordZ(871.013));
    trace("Shore15 (мыс Сан Антонио)            : " + Map_GetRealCoordX(-715.129) + " " + Map_GetRealCoordZ(797.212));
    trace("Mayak10 (маяк Гаваны)                : " + Map_GetRealCoordX(-647.18) + " " + Map_GetRealCoordZ(925.046));
    trace("---------");
    trace("Tortuga (island)                     : " + Map_GetRealCoordX(102.328) + " " + Map_GetRealCoordZ(852.912));
    trace("Тортуга                                 : " + Map_GetRealCoordX(116.875) + " " + Map_GetRealCoordZ(817.942));
    trace("Shore58 (пляж Глаз Рыбы)                : " + Map_GetRealCoordX(131.064) + " " + Map_GetRealCoordZ(849.44));
    trace("Mayak6 (маяк Тортуги)                : " + Map_GetRealCoordX(103.23) + " " + Map_GetRealCoordZ(812.356));
    trace("---------");
    trace("Trinidad (island)                    : " + Map_GetRealCoordX(889.76) + " " + Map_GetRealCoordZ(-774.746));
    trace("Порт-оф-Спейн                         : " + Map_GetRealCoordX(848.282) + " " + Map_GetRealCoordZ(-822.588));
    trace("Shore59 (бухта Скарборо)                : " + Map_GetRealCoordX(937.322) + " " + Map_GetRealCoordZ(-737.478));
    trace("Shore60 (мыс Галера)                    : " + Map_GetRealCoordX(906.25) + " " + Map_GetRealCoordZ(-757.928));
    trace("Mayak1 (маяк Тринидада и Тобаго)        : " + Map_GetRealCoordX(821.24) + " " + Map_GetRealCoordZ(-847.69));
    trace("---------");
    trace("Nevis (island)                        : " + Map_GetRealCoordX(681.595) + " " + Map_GetRealCoordZ(256.013));
    trace("Чарльзтаун                             : " + Map_GetRealCoordX(658.918) + " " + Map_GetRealCoordZ(241.972));
    trace("Shore42 (бухта Ньюкасл)                : " + Map_GetRealCoordX(690.047) + " " + Map_GetRealCoordZ(291.621));
    trace("Shore43 (пляж Бат)                    : " + Map_GetRealCoordX(684.026) + " " + Map_GetRealCoordZ(212.793));
    trace("Mayak5 (маяк Невиса)                    : " + Map_GetRealCoordX(663.418) + " " + Map_GetRealCoordZ(228.281));
    trace("---------");
    trace("Hispaniola1 (areal)                     : " + Map_GetRealCoordX(198.977) + " " + Map_GetRealCoordZ(588.696));
    trace("Санто-Доминго                         : " + Map_GetRealCoordX(198.683) + " " + Map_GetRealCoordZ(547.97));
    trace("Ла-Вега                                 : " + Map_GetRealCoordX(166.708) + " " + Map_GetRealCoordZ(662.952));
    trace("Shore32 (мыс Исабела)                : " + Map_GetRealCoordX(130.591) + " " + Map_GetRealCoordZ(682.362));
    trace("Shore33 (бухта Самана)                : " + Map_GetRealCoordX(229.081) + " " + Map_GetRealCoordZ(593.727));
    trace("Mayak8 (маяк Санто-Доминго)            : " + Map_GetRealCoordX(168.314) + " " + Map_GetRealCoordZ(520.218));
    trace("---------");
    trace("Hispaniola2 (areal)                     : " + Map_GetRealCoordX(-47.1762) + " " + Map_GetRealCoordZ(625.596));
    trace("Порт-о-Пренс                         : " + Map_GetRealCoordX(22.521) + " " + Map_GetRealCoordZ(592.233));
    trace("Shore34 (бухта Гонаив)                : " + Map_GetRealCoordX(0.999614) + " " + Map_GetRealCoordZ(643.122));
    trace("Mayak7 (маяк Порт-о-Пренса)            : " + Map_GetRealCoordX(-14.9756) + " " + Map_GetRealCoordZ(606.258));
    trace("---------");
    trace("Dominica                             : " + Map_GetRealCoordX(783.057) + " " + Map_GetRealCoordZ(-256.833));
    trace("Shore27 (мыс Скотс Хед)                : " + Map_GetRealCoordX(779.89) + " " + Map_GetRealCoordZ(-295.002));
    trace("Shore26 (пляж Касл Брус)                : " + Map_GetRealCoordX(803.577) + " " + Map_GetRealCoordZ(-252.617));
    trace("---------");
    trace("Теркс                                 : " + Map_GetRealCoordX(443.257) + " " + Map_GetRealCoordZ(939.102));
    trace("Shore57 (залив Южный)                : " + Map_GetRealCoordX(434.944) + " " + Map_GetRealCoordZ(923.524));
    trace("Shore56 (залив Северный)                : " + Map_GetRealCoordX(444.298) + " " + Map_GetRealCoordZ(954.975));
    trace("---------");
    trace("Кайман                                 : " + Map_GetRealCoordX(-489.6) + " " + Map_GetRealCoordZ(362.455));
    trace("Shore17 (залив Эсмеральды)            : " + Map_GetRealCoordX(-505.038) + " " + Map_GetRealCoordZ(348.115));
    trace("Shore16 (Пустынный пляж)                : " + Map_GetRealCoordX(-449.837) + " " + Map_GetRealCoordZ(366.308));
    trace("---------");
    trace("Panama (areal)                         : " + Map_GetRealCoordX(-395.198) + " " + Map_GetRealCoordZ(-972.801));
    trace("Панама                                 : " + Map_GetRealCoordX(-389.965) + " " + Map_GetRealCoordZ(-949.118));
    trace("Shore63 (залив Сан Мигель)             : " + Map_GetRealCoordX(-328.166) + " " + Map_GetRealCoordZ(-1023.72));
    trace("---------");
    trace("PortoBello (areal)                     : " + Map_GetRealCoordX(-435.73) + " " + Map_GetRealCoordZ(-895.763));
    trace("Порто-Белло                             : " + Map_GetRealCoordX(-427.183) + " " + Map_GetRealCoordZ(-907.277));
    trace("Shore46 (лагуна Чирики)                : " + Map_GetRealCoordX(-627.474) + " " + Map_GetRealCoordZ(-940.853));
    trace("Shore47 (залив Москитос)                : " + Map_GetRealCoordX(-486.49) + " " + Map_GetRealCoordZ(-976.966));
    trace("Shore48 (Дарьенский залив)            : " + Map_GetRealCoordX(-279.316) + " " + Map_GetRealCoordZ(-1005.49));
    trace("---------");
    trace("Cartahena (areal)                     : " + Map_GetRealCoordX(-51.2104) + " " + Map_GetRealCoordZ(-851.77));
    trace("Картахена                             : " + Map_GetRealCoordX(-26.7669) + " " + Map_GetRealCoordZ(-872.535));
    trace("Shore25 (бухта Ковеньяс)                : " + Map_GetRealCoordX(-115.589) + " " + Map_GetRealCoordZ(-937.387));
    trace("Mayak11 (маяк Картахены)                : " + Map_GetRealCoordX(-65.6347) + " " + Map_GetRealCoordZ(-842.072));
    trace("---------");
    trace("Caracas (areal)                         : " + Map_GetRealCoordX(435.126) + " " + Map_GetRealCoordZ(-936.197));
    trace("Каракас                                 : " + Map_GetRealCoordX(440.684) + " " + Map_GetRealCoordZ(-960.339));
    trace("Shore21 (мыс Аруба)                    : " + Map_GetRealCoordX(410.688) + " " + Map_GetRealCoordZ(-913.531));
    trace("---------");
    trace("Cumana (areal)                         : " + Map_GetRealCoordX(767.999) + " " + Map_GetRealCoordZ(-936.266));
    trace("Кумана                                 : " + Map_GetRealCoordX(691.343) + " " + Map_GetRealCoordZ(-896.619));
    trace("Shore20 (пляж Лос Текес)                : " + Map_GetRealCoordX(574.327) + " " + Map_GetRealCoordZ(-929.042));
    trace("Shore19 (бухта Карупано)                : " + Map_GetRealCoordX(768.622) + " " + Map_GetRealCoordZ(-914.469));
    trace("Shore18 (берег Бока де ла Сьерпе)    : " + Map_GetRealCoordX(924.423) + " " + Map_GetRealCoordZ(-969.921));
    trace("---------");
    trace("SantaCatalina (areal)                 : " + Map_GetRealCoordX(-742.269) + " " + Map_GetRealCoordZ(-563.205));
    trace("Санта-Каталина                         : " + Map_GetRealCoordX(-769.375) + " " + Map_GetRealCoordZ(-537.051));
    trace("Shore53 (Берег Москитов)                : " + Map_GetRealCoordX(-792.718) + " " + Map_GetRealCoordZ(-331.728));
    trace("Shore54 (мыс Перлас)                    : " + Map_GetRealCoordX(-760.343) + " " + Map_GetRealCoordZ(-484.106));
    trace("Shore55 (залив Сан Хуан дель Норте)    : " + Map_GetRealCoordX(-736.763) + " " + Map_GetRealCoordZ(-756.295));
    trace("---------");
    trace("ГПК                                    : " + Map_GetRealCoordX(-938.667) + " " + Map_GetRealCoordZ(938.654));
    trace("---------");
    trace("Teno (areal)                            : " + Map_GetRealCoordX(-966.062) + " " + Map_GetRealCoordZ(-294.232));
    trace("Теночтитлан                             : " + Map_GetRealCoordX(-969.194) + " " + Map_GetRealCoordZ(-305.237));
    trace("Shore61 (Тепейакак)                     : " + Map_GetRealCoordX(-955.553) + " " + Map_GetRealCoordZ(-281.197));
    trace("Shore62 (Истапалапу)                    : " + Map_GetRealCoordX(-935.811) + " " + Map_GetRealCoordZ(-316.162));
    trace("---------");
    trace("Ксочитэм                                : " + Map_GetRealCoordX(-597.3333) + " " + Map_GetRealCoordZ(85.3333));
    trace("---------");
    trace("RockIsland                            : " + Map_GetRealCoordX(-511.9965) + " " + Map_GetRealCoordZ(554.6586));
    trace("---------");
    trace("KhaelRoa                                : " + Map_GetRealCoordX(810.6678) + " " + Map_GetRealCoordZ(298.6671));
    trace("---------");
    trace("Providence                            : " + Map_GetRealCoordX(-512.0) + " " + Map_GetRealCoordZ(-426.6667));
    trace("---------");
    trace("SantaQuiteria                        : " + Map_GetRealCoordX(-213.3336) + " " + Map_GetRealCoordZ(-512.0));
    trace("---------");
    trace("IslaDeVieques                        : " + Map_GetRealCoordX(85.3334) + " " + Map_GetRealCoordZ(-70.6667));
    trace("---------");
    trace("IslaMona                                : " + Map_GetRealCoordX(0) + " " + Map_GetRealCoordZ(170.6669));
    trace("---------");
    trace("IslaDeCoche                            : " + Map_GetRealCoordX(640.0) + " " + Map_GetRealCoordZ(-640.0));
    trace("---------");
}