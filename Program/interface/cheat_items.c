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
	
	idLngFile = LanguageOpenFile("cheat_items.txt");

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
                "F21 - " + descF21;/* + NewStr() + */
                /* "F22 - " + descF22 + NewStr() +
                "F23 - " + descF23 + NewStr() +
                "F24 - " + descF24 + NewStr() +
                "F25 - " + descF25 + NewStr() +
                "F26 - " + descF26 + NewStr() +
                "F27 - " + descF27; */ /* + NewStr() + */
                /*"F28 - " + descF28 + NewStr() +
                "F29 - " + descF29 + NewStr() +
                "F30 - " + descF30; // + NewStr() +
                "F31 - " + descF31 + NewStr() +
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
			IDoExit(RC_INTERFACE_BLACKMARK_CHEAT);
            //CalculateInfoDataF31();
        }
        break;
    case "B_32":
        if (comName == "activate" || comName == "click")
        {
            //CalculateInfoDataF32();
			IDoExit(RC_INTERFACE_CHEAT_CHARACTER);
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
string descF1 = "Сделать доступными все рецепты алхимии";

void CalculateInfoDataF1()
{
    totalInfo = descF1;

	pchar.alchemy.known = 1;
    SetCharacterPerk(pchar, "Alchemy");
    ref item;
    for (int n = 0; n < ITEMS_QUANTITY; n++)
    {
        item = &Items[n];
        if (CheckAttribute(item, "multiobject"))
        {
            string sGood = item.id;
			if(!GetDLCenabled(DLC_APPID_2))
			{
				if(sGood == "bullet_double") continue;
				if(sGood == "grapeshot_double") continue;
			}
            pchar.alchemy.(sGood).isKnown = true;
        }
    }
    
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    //LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.IF1", 1);
}
////////////////////////////////////////////////////////////////////////
string descF2 = "Получить хлам ";

void CalculateInfoDataF2()
{
	totalInfo = descF2;
    // -->
	for (int i = 1; i <= 35; i++)
	{
		if(i == 28) continue;
		if(i == 29) continue;
		if(i == 32) continue;
		TakenItems(pchar, "mineral" + i, 1);
	}
	//<--
	
    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile, "Cheat_success");

    SetFormatedText("INFO_TEXT", totalInfo);
	
    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.IF2", 1);
}
////////////////////////////////////////////////////////////////////////
string descF3 = "Получить все травы ";

void CalculateInfoDataF3()
{
    totalInfo = descF3;

	for(int j = 1; j < 8; j++)
	{
		TakenItems(pchar, "cannabis"+j, 5);
	}

    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF3", 1);
}
////////////////////////////////////////////////////////////////////////
string descF4 = "Получить все камни и украшения";

void CalculateInfoDataF4()
{
    totalInfo = descF4;

    // -->
	for (int i = 1; i <= 23; i++)
	{
		TakenItems(pchar, "jewelry" + i, 1);
	}
	for ( i = 40; i <= 53; i++)
	{
		TakenItems(pchar, "jewelry" + i, 1);
	}
    // <--
    
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF4", 1);
}
////////////////////////////////////////////////////////////////////////
string descF5 = "Куриный бог +100";

void CalculateInfoDataF5()
{
    totalInfo = descF5;
    
	TakenItems(pchar, "talisman11", 100);
	
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF5", 1);
}
////////////////////////////////////////////////////////////////////////
string descF6 = "Боеприпасы +50";

void CalculateInfoDataF6()
{
	totalInfo = descF6;
	
    TakenItems(pchar, "bullet", 50);
    TakenItems(pchar, "GunCap_colt", 50);
    TakenItems(pchar, "shotgun_cartridge", 50);
    TakenItems(pchar, "grapeshot", 50);
    TakenItems(pchar, "cartridge", 50);
    TakenItems(pchar, "powder_pellet", 50);
    TakenItems(pchar, "grenade", 50);
    TakenItems(pchar, "harpoon", 50);
    TakenItems(pchar, "GunPowder", 150);
    TakenItems(pchar, "GunEchin", 50);
	
    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile, "Cheat_success");

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF6", 1);
}
////////////////////////////////////////////////////////////////////////
string descF7 = "Получить клинки";

void CalculateInfoDataF7()
{
    totalInfo = descF7;
	int i;
	string sBlade;
	for(i=1; i<=32; i++)
	{
		if(i < 10)
		{
			sBlade = GetBestGeneratedItem("blade_0"+i);
		}
		else
		{
			sBlade = GetBestGeneratedItem("blade_"+i);
		}
		GiveItem2Character(pchar, sBlade);
	}
	sBlade = GetBestGeneratedItem("shamshir");
	GiveItem2Character(pchar, sBlade);
	for(i=1; i<=5; i++)
	{
		sBlade = GetBestGeneratedItem("topor_0"+i);
		GiveItem2Character(pchar, sBlade);
	}
	ref sld = ItemsFromID("topor_06");
	sld.Balance = 2.0;
	sld.Weight = 3.5;
	sld.Attack = 88.0;
	GiveItem2Character(pchar, "topor_06");
	
	sBlade = GetBestGeneratedItem("blade_38");
	GiveItem2Character(pchar, sBlade);
	sBlade = GetBestGeneratedItem("blade_39");
	GiveItem2Character(pchar, sBlade);

    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
	
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF7", 1);
}
////////////////////////////////////////////////////////////////////////
string descF8 = "Получить пистолеты";
void CalculateInfoDataF8()
{
	totalInfo = descF8;
	
	int i;
	for(i=1; i<=9; i++)
	{
		GiveItem2Character(pchar, "pistol"+i);
	}
    GiveItem2Character(pchar, "pistol11");
    GiveItem2Character(pchar, "howdah");
    GiveItem2Character(pchar, "mortairgun");
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF8", 1);
}
////////////////////////////////////////////////////////////////////////
string descF9 = "Получить мушкеты";

void CalculateInfoDataF9()
{
	totalInfo = descF9;
	
    GiveItem2Character(pchar, "mushket1");
    GiveItem2Character(pchar, "mushket2");
    GiveItem2Character(pchar, "mushket3");
    GiveItem2Character(pchar, "mushket5");
    GiveItem2Character(pchar, "mushket6");
    GiveItem2Character(pchar, "mushket7");
    GiveItem2Character(pchar, "grape_mushket");
    GiveItem2Character(pchar, "mushket2x2");
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF9", 1);
}
////////////////////////////////////////////////////////////////////////
string descF10 = "Бессмертие вкл/выкл";

void CalculateInfoDataF10()
{
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
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF10", 1);
}
////////////////////////////////////////////////////////////////////////
string descF11 = "Полуить кирасы";

void CalculateInfoDataF11()
{
    totalInfo = descF11;

	int i;
	for(i=1; i<=9; i++)
	{
		GiveItem2Character(pchar, "cirass"+i);
	}
	GiveItem2Character(pchar, "underwater");
	GiveItem2Character(pchar, "suit4");
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF11", 1);
}
////////////////////////////////////////////////////////////////////////

string descF12 = "Получить талисманы";

void CalculateInfoDataF12()
{
	totalInfo = descF12; 
    
	int i;
	for(i=1; i<=13; i++)
	{
		if(i<10)
		{
			GiveItem2Character(pchar, "totem_0"+i);
		}
		else
		{
			GiveItem2Character(pchar, "totem_"+i);
		}
	}
	
	totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF12", 1);
}

string descF13 = "Получить амулеты";
void CalculateInfoDataF13()
{
    totalInfo = descF13;
	
    int i;
	for(i=1; i<=11; i++)
	{
		GiveItem2Character(pchar, "indian_"+i);
		GiveItem2Character(pchar, "amulet_"+i);
		GiveItem2Character(pchar, "obereg_"+i);
	}
	GiveItem2Character(pchar, "rat_poison");
	GiveItem2Character(pchar, "clock2");
	
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF13", 1);
}

string descF14 = "Получить обереги";
void CalculateInfoDataF14()
{
    totalInfo = descF14;
	
	int i;
	for(i=1; i<=11; i++)
	{
		if(i == 5) continue;
		GiveItem2Character(pchar, "talisman"+i);
	}

    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
	
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF14", 1);
}

string descF15 = "Получить зелья";

void CalculateInfoDataF15()
{
    totalInfo = descF15;

    int i;
	for(i=1; i<=7; i++)
	{
		TakenItems(pchar, "potion"+i, 5);
	}
	TakenItems(pchar, "potionrum", 5);
	TakenItems(pchar, "potionwine", 5);
	TakenItems(pchar, "Ultimate_potion", 5);
	TakenItems(pchar, "berserker_potion", 5);
	TakenItems(pchar, "mangarosapower", 5);
	TakenItems(pchar, "mangarosafast", 5);
	TakenItems(pchar, "mangarosatotal", 5);

    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF15", 1);
}

////////////////////////////////////////
string descF16 = "Получить подзорные трубы";

void CalculateInfoDataF16()
{
    totalInfo = descF16;

    int i;
	for(i=1; i<=5; i++)
	{
		TakenItems(pchar, "spyglass"+i, 1);
	}
    
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
	
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF16", 1);
}

string descF17 = "Получить фонарь";

void CalculateInfoDataF17()
{
    totalInfo = descF17;
	
	TakenItems(pchar, "lantern_belt", 1);
   
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF17", 1);
}

string descF18 = "Получить навигационные приборы";

void CalculateInfoDataF18()
{
    totalInfo = descF18;

    TakenItems(pchar, "sand_clock", 1);
    TakenItems(pchar, "astrolab", 1);
    TakenItems(pchar, "compass1", 1);
    TakenItems(pchar, "clock1", 1);
    TakenItems(pchar, "clock2", 1);
    TakenItems(pchar, "sextant1", 1);
    TakenItems(pchar, "bussol", 1);
    TakenItems(pchar, "clock3", 1);
    TakenItems(pchar, "sextant2", 1);
	
    totalInfo = totalInfo + LanguageConvertString(idLngFile, "new_string") + LanguageConvertString(idLngFile, "new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
	
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF18", 1);
}

string descF19 = "Получить инструменты";
void CalculateInfoDataF19()
{
    totalInfo = descF19;
    
	TakenItems(pchar, "tailor_tool", 1);
    TakenItems(pchar, "mechanic_tool", 1);
    TakenItems(pchar, "tigel", 1);
    TakenItems(pchar, "sextant2", 1);
    
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF19", 1);
}

string descF20 = "Получить обычные карты";
void CalculateInfoDataF20()
{
    totalInfo = descF20;
	
	int i;
	string Map;

	for (i = 0; i < ITEMS_QUANTITY; i++)
	{
		if (CheckAttribute(&Items[i], "Atlas") && sti(Items[i].Atlas) == 1)
		{
			Map = Items[i].id;
			TakenItems(pchar, Map, 1);
		}
	}

	TakenItems(pchar, "map_LSC", 1);

	TakenItems(pchar, "map_bad", 1);

	TakenItems(pchar, "map_normal", 1);

	TakenItems(pchar, "Map_Best", 1);
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF20", 1);
}

string descF21 = "Получить отличные карты";
void CalculateInfoDataF21()
{
    totalInfo = descF21;
    // -->
    if (CheckAttribute(pchar, "questTemp.AdmiralMap"))
	{
		int i = 0;
		while(CountAdmiralMapFromCharacter() < 24 && i < 50)
		{
			GiveAdmiralMapToCharacter(pchar, 0);
			i++;
		}
	}
	else
	{
		totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "descF21No");
		SetFormatedText("INFO_TEXT", totalInfo);
		return;
	}

    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF21", 1);
}

string descF22 = "Изучить перки предыстории 'Дуэлянт' ";
void CalculateInfoDataF22()
{
	totalInfo = descF22;
	
    SetCharacterPerk(pchar, "HT1");
	SetCharacterPerk(pchar, "FencingMaster");
	SetCharacterPerk(pchar, "TannedLeather");

    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile, "Cheat_success");

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF22", 1);
}

string descF23 = "Изучить перки предыстории 'Счетовод' ";
void CalculateInfoDataF23()
{
    totalInfo = descF23;
    // -->
	SetCharacterPerk(pchar, "HT2");
	SetCharacterPerk(pchar, "RatsWolf");
	SetCharacterPerk(pchar, "Mimicry");
	SetCharacterPerk(pchar, "TreasureHunter");
	//<--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF23", 1);
}

string descF24 = "Изучить перки предыстории 'Атлет' ";
void CalculateInfoDataF24()
{
    totalInfo = descF24;
	
	SetCharacterPerk(pchar, "HT3");
	SetCharacterPerk(pchar, "Dragoon");
	SetCharacterPerk(pchar, "SecondWind");
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF24", 1);
}

string descF25 = "Изучить перки предыстории 'Стрелок' ";
void CalculateInfoDataF25()
{
    totalInfo = descF25;
    // -->
	SetCharacterPerk(pchar, "HT4");
	SetCharacterPerk(pchar, "Jager");
	SetCharacterPerk(pchar, "Bombardier");
	SetCharacterPerk(pchar, "Sniper");
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    //ProcessCancelExit();
    Statistic_AddValue(PChar, "Cheats.CF25", 1);
}

string descF26 = "Не получать штрафы от навигации ВКЛ/ВЫКЛ";
void CalculateInfoDataF26()
{
    totalInfo = descF26;
    // -->
	 if(!CheckAttribute(pchar, "NoNavyPenalty"))
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile, "Cheat_on") + NewStr();
		pchar.NoNavyPenalty = true;
	}
	else
	{
		totalInfo = totalInfo + NewStr() + LanguageConvertString(idLngFile, "Cheat_off") + NewStr();
		DeleteAttribute(pchar, "NoNavyPenalty");
	}
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() +
                LanguageConvertString(idLngFile, "Cheat_success");
    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.26", 1);
}

string descF27 = "Отрезвить персонажа ";
void CalculateInfoDataF27()
{
    totalInfo = descF27;
    // -->
    if(CheckAttribute(pchar, "GenQuest.CamShuttle")) 
	{
		DeleteAttribute(pchar, "GenQuest.CamShuttle");
		SetPitch(1.0);
	}
    // <--
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                LanguageConvertString(idLngFile, "Cheat_success");
    LanguageCloseFile(idLngFile);
    SetFormatedText("INFO_TEXT",totalInfo);
    // <--

    // Статистика по читам
    Statistic_AddValue(PChar, "Cheats.CF27", 1);
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
    Statistic_AddValue(PChar, "Cheats.CF28", 1);
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
    Statistic_AddValue(PChar, "Cheats.CF29", 1);
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
    Statistic_AddValue(PChar, "Cheats.CF30", 1);
}

string descF31 = "";
void CalculateInfoDataF31()
{
    totalInfo = descF31;
	
    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile,"Cheat_Comming_soon");

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    //Statistic_AddValue(PChar, "Cheats.CF31", 1);
}

string descF32 = "";
void CalculateInfoDataF32()
{
   totalInfo = descF32;
   

    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile,"Cheat_Comming_soon");

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    //Statistic_AddValue(PChar, "Cheats.CF32", 1);
}

string descF33 = "";
void CalculateInfoDataF33()
{
   
    totalInfo = descF33;
    
    totalInfo = totalInfo + NewStr() + NewStr() + LanguageConvertString(idLngFile,"Cheat_Comming_soon");

    SetFormatedText("INFO_TEXT", totalInfo);

    // Статистика по читам
    //Statistic_AddValue(PChar, "Cheats.CF33", 1);
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
	int dockid = LanguageOpenFile("cheat_items.txt");
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