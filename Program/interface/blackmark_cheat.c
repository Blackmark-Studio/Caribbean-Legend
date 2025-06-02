//  09.04.2024 belamour Cheats Menu
string totalInfo;
int idLngFile = -1;
int remInt = 0;

void InitInterface(string iniName)
{
    StartAboveForm(true);

    GameInterface.title = "titleBoal_Debug";
	bGameMenuStart = true; // меню запущено, скрываем landinterface
    SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
	
	CalculateCheatsInfo(); // Warship. Статистика - сколько читов юзали
    CalculateInfoData();

    SetFormatedText("INFO_TEXT", totalInfo); //"Информация отладчика");
    SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 5);

    SetEventHandler("InterfaceBreak", "ProcessBreakExit", 0);
    SetEventHandler("exitCancel", "ProcessCancelExit", 0);
    SetEventHandler("evntDoPostExit", "DoPostExit", 0);
    SetEventHandler("ievnt_command", "ProcCommand", 0);
    SetEventHandler("SetScrollerPos", "SetScrollerPos", 0);
    SetEventHandler("ScrollPosChange", "ProcScrollPosChange", 0);
    SetEventHandler("ScrollTopChange", "ProcScrollChange", 0);
	
	idLngFile = LanguageOpenFile("blackmark_cheat.txt");

    /* GameInterface.reload_edit.str = "Shore75, reload, reload1"; //"Pearl_town_1, reload, reload1";
                                                                         // Pirates_Shipyard, reload, reload1
                                                                         // boarding_cargohold, rld, loc0 */
	//SetSelectable("B_BACK",false);
	
	// врменно закроем
	/* SetSelectable("B_BETA", false);
	SetSelectable("B_31", false);
	SetSelectable("B_32", false);
	SetSelectable("B_33", false); */
}

void ProcessBreakExit()
{
    IDoExit(RC_INTERFACE_QUICK_SAVE);
}

void ProcessCancelExit()
{
	LanguageCloseFile(idLngFile);
    bGameMenuStart = false; // выход из меню, показываем landinterface
	if(CheckAttribute(pchar,"systeminfo.photomod"))
	{
		PhotoModChangeInterface();
		DeleteAttribute(pchar,"systeminfo.photomod");
	}
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
	
	ChangeLanguage();

    // тут высчитываем нужную информацию и выводим в totalInfo - Инициализация -->
	if(LanguageGetLanguage() == "russian")
	{
		totalInfo = "Чит меню вер.1.3. Команды: " + NewStr();
		totalInfo = totalInfo + "****************************" + NewStr();
	}
	else
	{
		totalInfo = "Cheat menu ver.1.3. Commands: " + NewStr();
		totalInfo = totalInfo + "*****************************" + NewStr();
	}
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
                "F30 - " + descF30;// + NewStr() +
                /* "F31 - " + descF31 + NewStr() +
                "F32 - " + descF32 + NewStr() +
                "F33 - " + descF33; */
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
            //CalculateInfoDataF31();
			IDoExit(RC_INTERFACE_CHEAT_CHARACTER);
        }
        break;
    case "B_32":
        if (comName == "activate" || comName == "click")
        {
            //CalculateInfoDataF32();
			IDoExit(RC_INTERFACE_CHEAT_ITEMS);
        }
        break;
    case "B_33":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF33();
        }
    break;
	
	case "B_34":
        if (comName == "activate" || comName == "click")
        {
            CalculateInfoDataF33();
        }
    break;
	
    case "B_BETA":
        if (comName == "activate" || comName == "click")
        {
			CalculateInfoDataF33();
            //IDoExit(RC_INTERFACE_DO_BOAL_BETA);
        }
        break;
    case "B_RELOAD":
        if (comName == "activate" || comName == "click")
        {
            //ReloadByStr();
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

////////////////////////////////////////////////////////////////////////
string descF1 = "Песо + 500 000 ";

void CalculateInfoDataF1()
{
    // тут высчитываем нужную информацию и выводим в totalInfo - Инициализация -->
    totalInfo = descF1;
    Pchar.money = sti(Pchar.money) + 500000;
	
	if(LanguageGetLanguage() == "russian")
	{
		totalInfo = totalInfo + GetAssembledString(" Денег у #snameGen# теперь #dmoney#", Pchar);
	}
	else
	{
		totalInfo =  totalInfo + NewStr() + GetAssembledString(" #snameGen# has #dmoney# pesos", Pchar);
	}
    // тут высчитываем нужную информацию и выводим в totalInfo <--

    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F1", 1);
}
////////////////////////////////////////////////////////////////////////
string descF2 = "Получить лечебные зелья";

void CalculateInfoDataF2()
{
    // -->
    totalInfo = descF2;
	
	locCameraEnableFree = !locCameraEnableFree;
	pchar.systeminfo.photomod = true;
	
    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile, "Cheat_success");

    SetFormatedText("INFO_TEXT", totalInfo);

    ProcessCancelExit();

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F2", 1);
}
////////////////////////////////////////////////////////////////////////
string descF3 = "Аркадное плавание ВКЛ/ВЫКЛ ";

void CalculateInfoDataF3()
{
    // -->
    totalInfo = descF3;
	if(!CheckAttribute(pchar, "cheats.ArcadeSailing"))
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile, "StrF3_on") + NewStr();
		pchar.cheats.ArcadeSailing = true;
	}
	else
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile, "StrF3_off") + NewStr();
		DeleteAttribute(pchar, "cheats.ArcadeSailing");
	}
    
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);
	
	//ProcessCancelExit();
	
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
    
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F4", 1);
}
////////////////////////////////////////////////////////////////////////
string descF5 = "Главному герою +35 скилов";
int BOAL_debug_num = 1;
void CalculateInfoDataF5()
{
    //idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF5;

    pchar.Skill.FreeSkill = sti(pchar.Skill.FreeSkill) + 35;
    
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F5", 1);
}
////////////////////////////////////////////////////////////////////////
string descF6 = "Корабельные навыки +1 ";

void CalculateInfoDataF6()
{
	 totalInfo = descF6;
    pchar.perks.FreePoints_ship = sti(pchar.perks.FreePoints_ship) + 1;
	
    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile, "Cheat_success");

    SetFormatedText("INFO_TEXT", totalInfo);

    //ProcessCancelExit();
    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F6", 1);
}
////////////////////////////////////////////////////////////////////////
string descF7 = "Личные навыки +1 ";

void CalculateInfoDataF7()
{
    //idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF7;

   pchar.perks.FreePoints_self = sti(pchar.perks.FreePoints_self) + 1;

    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F7", 1);
}
////////////////////////////////////////////////////////////////////////
string descF8 = "Штурману +35 скилов";
void CalculateInfoDataF8()
{
	 totalInfo = descF8;
    // -->
    if (sti(pchar.Fellows.Passengers.navigator) != -1)
    {
        ref chr = GetCharacter(sti(pchar.Fellows.Passengers.navigator));

        chr.Skill.FreeSkill = sti(chr.Skill.FreeSkill) + 35;
    }
    else
    {
        totalInfo = "Нет офицера";
    }
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F8", 1);
}
////////////////////////////////////////////////////////////////////////
string descF9 = "Офицеры в таверне ";

void CalculateInfoDataF9()
{
	 totalInfo = descF9;
    // -->
    if(!CheckAttribute(pchar, "cheats.lai_officers"))
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile, "StrF9_on") + NewStr();
		pchar.cheats.lai_officers = true;
	}
	else
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile, "StrF9_off") + NewStr();
		DeleteAttribute(pchar, "cheats.lai_officers");
	}
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F9", 1);
}
////////////////////////////////////////////////////////////////////////
string descF10 = "Бессмертие вкл/выкл";

void CalculateInfoDataF10()
{
    //idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF10;
    ref mc;
    mc = GetMainCharacter();
    if (LAi_IsImmortal(mc))
    {
        LAi_SetImmortal(mc, false);
		totalInfo = totalInfo + NewStr() + " God mode OFF "+ NewStr();
    }
    else
    {
        LAi_SetImmortal(mc, true);
		totalInfo = totalInfo + NewStr() + " God mode ON "+ NewStr();
        
    }
    // <--
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F10", 1);
}
////////////////////////////////////////////////////////////////////////
string descF11 = "Лояльность офицерам +1";

void CalculateInfoDataF11()
{
    totalInfo = descF11;

	ChangeOfficersLoyality("good_all", 1);
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F11", 1);
}
////////////////////////////////////////////////////////////////////////

string descF12 = "Лояльность офицерам -1";

void CalculateInfoDataF12()
{
	totalInfo = descF12; 
    ChangeOfficersLoyality("bad_all", 1);
	
	totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F12", 1);
}

string descF13 = "Отношени у всех наций +10";
void CalculateInfoDataF13()
{
    //idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF13;
	
    for (int j=0; j< MAX_NATIONS; j++)
    {
        ChangeCharacterNationReputation(pchar, j, 10);
    }

    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);
    //ProcessCancelExit();

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F13", 1);
}

string descF14 = "Отношение у всех наций -10";
void CalculateInfoDataF14()
{
   // idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF14;
	
    for (int j=0; j< MAX_NATIONS; j++)
    {
        ChangeCharacterNationReputation(pchar, j, -10);
    }

    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);
    //ProcessCancelExit();

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F14", 1);
}

string descF15 = "Повысить репутацию ";

void CalculateInfoDataF15()
{
    //idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF15;

    ChangeCharacterComplexReputation(pchar,"nobility", 5);

    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);
    //ProcessCancelExit();

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F15", 1);
}

string descF16 = "Понизить репутацию ";

void CalculateInfoDataF16()
{
    //idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF16;

    ChangeCharacterComplexReputation(pchar,"nobility", -5);
    // <
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F16", 1);
}

string descF17 = "Повысить известность ";

void CalculateInfoDataF17()
{
    //idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF17;

   ChangeCharacterComplexReputation(pchar, "fame", 5);
   
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F17", 1);
}

string descF18 = "Понизить известность ";

void CalculateInfoDataF18()
{
    //idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    // -->
    totalInfo = descF18;

    ChangeCharacterComplexReputation(pchar, "fame", -5);
    // <
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
   //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F18", 1);
}

string descF19 = "Повысить авторитет ";
void CalculateInfoDataF19()
{
    totalInfo = descF19;
    
	if(!CheckAttribute(pchar, "cheats.dopgrus"))
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile, "Cheat_on") + NewStr();
		pchar.cheats.dopgrus = true;
	}
	else
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile, "Cheat_off") + NewStr();
		DeleteAttribute(pchar, "cheats.dopgrus");
	}
    
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F19", 1);
}

string descF20 = "+100 дублонов ";
void CalculateInfoDataF20()
{
    totalInfo = descF20;
	
    AddItems(pchar, "gold_dublon", 100);
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F20", 1);
}

string descF21 = "Ветер 14.5 ";
void CalculateInfoDataF21()
{
    totalInfo = descF21;
    // -->
    Weather.Wind.Speed = 14.5;
    pchar.wind.speed = Weather.Wind.Speed;
    fWeatherSpeed = stf(Weather.Wind.Speed);

    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F21", 1);
}

string descF22 = "Освятить корабль";
void CalculateInfoDataF22()
{
    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
	{
		totalInfo = descF22;
		Pchar.GenQuest.Shipshine = true;
		DoQuestCheckDelay("Monk_Shipshine", 0.01);
	}
	else
	{
		return;
	}

    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile, "Cheat_success");

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F22", 1);
}

string descF23 = "Восстановить корпус и паруса ";
void CalculateInfoDataF23()
{
    totalInfo = descF23;
    
	pchar.ship.hp = GetCharacterShipHP(pchar);
	if(CheckAttribute(pchar, "ship.hulls"))
		DeleteAttribute(pchar, "ship.hulls");
	if(CheckAttribute(pchar, "ship.blots"))
		DeleteAttribute(pchar, "ship.blots");
	
	pchar.ship.sp = GetCharacterShipSP(pchar);
	if(CheckAttribute(pchar, "ship.sails"))
		DeleteAttribute(pchar, "ship.sails");
	if(CheckAttribute(pchar, "ship.masts"))
		DeleteAttribute(pchar, "ship.masts");
	
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F23", 1);
}

string descF24 = "Стратегические товары +500";
void CalculateInfoDataF24()
{
    totalInfo = descF24;
    
	AddCharacterGoods(pchar, GOOD_SHIPSILK, 500);
	AddCharacterGoods(pchar, GOOD_ROPES, 500);
	AddCharacterGoods(pchar, GOOD_SANDAL, 500);
	AddCharacterGoods(pchar, GOOD_OIL, 500);
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F24", 1);
}

string descF25 = "Товары жизнеобеспечения +500 ";
void CalculateInfoDataF25()
{
    totalInfo = descF25;
	
    AddCharacterGoods(pchar, GOOD_BALLS, 500);
	AddCharacterGoods(pchar, GOOD_GRAPES, 500);
	AddCharacterGoods(pchar, GOOD_KNIPPELS, 500);
	AddCharacterGoods(pchar, GOOD_BOMBS, 500);
	AddCharacterGoods(pchar, GOOD_POWDER, 500);
	AddCharacterGoods(pchar, GOOD_WEAPON, 500);
	AddCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
	AddCharacterGoods(pchar, GOOD_RUM, 500);
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    //ProcessCancelExit();
    Statistic_AddValue(PChar, "Cheats.F25", 1);
}

string descF26 = "Улучшить здоровье ";
void CalculateInfoDataF26()
{
    totalInfo = descF26;
    // -->
	AddCharacterHealth(pchar, 10.0);
	AddCharacterMaxHealth(pchar, 4.0);
	PlaySound("Ambient\Horror\Fear_breath_01.wav");
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.26", 1);
}

string descF27 = "Противник на глобальной карте ВКЛ/ВЫКЛ ";
void CalculateInfoDataF27()
{
    totalInfo = descF27;
    // -->
     ref mc;
    mc = GetMainCharacter();
    if(CheckAttribute(mc,"worldmapencountersoff") == 0)
    {
        mc.worldmapencountersoff = "1";
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile,"StrF27_off") + NewStr();
        //Log_SetStringToLog("Worldmap encounters OFF");
    }
    else
    {
        if(mc.worldmapencountersoff == "1")
        {
            mc.worldmapencountersoff = "0";
			totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile,"StrF27_on") + NewStr();
            //Log_SetStringToLog("Worldmap encounters ON");
        }
        else
        {
            mc.worldmapencountersoff = "1";
			totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile,"StrF27_off")+ NewStr();
            //Log_SetStringToLog("Worldmap encounters OFF");
        }
    }
    // <--
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
    // <--

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F27", 1);
}

string descF28 = "Телепорт в море без ограничений ВКЛ/ВЫКЛ ";
void CalculateInfoDataF28()
{
    totalInfo = descF28;
	//-->
	if(!CheckAttribute(pchar, "Cheats.SeaTeleport"))
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile,"StrF28_on")+ NewStr();
		//log_info("Телепорт в море включен");
		pchar.Cheats.SeaTeleport = true;
	}
	else
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile,"StrF28_off")+ NewStr();
		//log_info("Телепорт в море выключен");
		DeleteAttribute(pchar, "Cheats.SeaTeleport");
	}
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F28", 1);
}

string descF29 = "Быстрый переход в локациях без ограничений ";
void CalculateInfoDataF29()
{
    totalInfo = descF29;
    // -->
    if(!CheckAttribute(pchar, "Cheats.LocTeleport"))
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile,"Cheat_on")+ NewStr();
		//log_info("Телепорт в локациях включен");
		pchar.Cheats.LocTeleport = true;
	}
	else
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile,"Cheat_off")+ NewStr();
		//log_info("Телепорт в локациях выключен");
		DeleteAttribute(pchar, "Cheats.LocTeleport");
	}
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F29", 1);
}

string descF30 = "Дополнительная команда в меню 'топить противников'  ";
void CalculateInfoDataF30()
{
    totalInfo = descF30;
    // -->
    if(!CheckAttribute(pchar, "Cheats.ImmediateDeath"))
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile,"Cheat_on")+ NewStr();
		//log_info("Телепорт в локациях включен");
		pchar.Cheats.ImmediateDeath = true;
	}
	else
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile,"Cheat_off")+ NewStr();
		//log_info("Телепорт в локациях выключен");
		DeleteAttribute(pchar, "Cheats.ImmediateDeath");
	}
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.F30", 1);
}

string descF31 = "";
void CalculateInfoDataF31()
{
    totalInfo = descF31;
	
    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile,"Cheat_Comming_soon");

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    //Statistic_AddValue(PChar, "Cheats.F31", 1);
}

string descF32 = "";
void CalculateInfoDataF32()
{
   totalInfo = descF32;
   

    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile,"Cheat_Comming_soon");

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    //Statistic_AddValue(PChar, "Cheats.F32", 1);
}

string descF33 = "";
void CalculateInfoDataF33()
{
   
    totalInfo = descF33;
    
    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile,"Cheat_Comming_soon");

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    //Statistic_AddValue(PChar, "Cheats.F33", 1);
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

void ChangeLanguage()
{
	int dockid = LanguageOpenFile("blackmark_cheat.txt");
	descF1 = LanguageConvertString(dockid,"f1");
	descF2 = LanguageConvertString(dockid,"f2");
	descF3 = LanguageConvertString(dockid,"f3");
	descF4 = LanguageConvertString(dockid,"f4");
	descF5 = LanguageConvertString(dockid,"f5");
	descF6 = LanguageConvertString(dockid,"f6");
	descF7 = LanguageConvertString(dockid,"f7");
	descF8 = LanguageConvertString(dockid,"f8");
	descF9 = LanguageConvertString(dockid,"f9");
	descF10 = LanguageConvertString(dockid,"f10");
	descF11 = LanguageConvertString(dockid,"f11");
	descF12 = LanguageConvertString(dockid,"f12");
	descF13 = LanguageConvertString(dockid,"f13");
	descF14 = LanguageConvertString(dockid,"f14");
	descF15 = LanguageConvertString(dockid,"f15");
	descF16 = LanguageConvertString(dockid,"f16");
	descF17 = LanguageConvertString(dockid,"f17");
	descF18 = LanguageConvertString(dockid,"f18");
	descF19 = LanguageConvertString(dockid,"f19");
	descF20 = LanguageConvertString(dockid,"f20");
	descF21 = LanguageConvertString(dockid,"f21");
	descF22 = LanguageConvertString(dockid,"f22");
	descF23 = LanguageConvertString(dockid,"f23");
	descF24 = LanguageConvertString(dockid,"f24");
	descF25 = LanguageConvertString(dockid,"f25");
	descF26 = LanguageConvertString(dockid,"f26");
	descF27 = LanguageConvertString(dockid,"f27");
	descF27 = LanguageConvertString(dockid,"f27");
	descF28 = LanguageConvertString(dockid,"f28");
	descF29 = LanguageConvertString(dockid,"f29");
	descF30 = LanguageConvertString(dockid,"f30");
	LanguageCloseFile(dockid);
}

void PhotoModChangeInterface()
{
	if(!locCameraEnableFree) 
	{
		if (bSeaActive && !bAbordageStarted)
		{
			if (!IsEntity(&BattleInterface))
			{
			}
			else DeleteBattleInterface();
			SeaCameras.Camera = "SeaShipCamera";
			SeaCameras_UpdateCamera();
		}
		else
		{
			if (!IsEntity(&worldMap)) 
			{
				if (!bLandInterfaceStart)// если батловый интерфейс не включен или главное меню
				{
				}
				else EndBattleLandInterface(); // выключаем 
				locCameraFollow();
			}
		}
		
		if(LanguageGetLanguage() == "russian") Log_info("Свободная камера выключена");
		if(LanguageGetLanguage() != "russian") Log_info("FreeCam Off");
	}
	else 
	{
		if (bSeaActive && !bAbordageStarted)
		{
			if (!IsEntity(&BattleInterface))
			{
				InitBattleInterface();
				StartBattleInterface();
				RefreshBattleInterface();
			}
			SeaCameras.Camera = "SeaFreeCamera";
			SeaCameras_UpdateCamera();
		}
		else
		{
			if (!IsEntity(&worldMap)) 
			{
				if (!bLandInterfaceStart)// если батловый интерфейс не включен или главное меню
				{
					StartBattleLandInterface(); // включаем 
				}
				locCameraFree();
			}
		}
		
		if(LanguageGetLanguage() == "russian") Log_info("Свободная камера включена");
		if(LanguageGetLanguage() != "russian")Log_info("FreeCam On");
	}
}