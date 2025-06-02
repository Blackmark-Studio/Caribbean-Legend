// Sith меню снаряжение/инвентарь
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню кнопками Q, E и TAB
#include "interface\character_all.h"
int currentTab = 0;
int currentScrollTab = 1;
int sMode;
bool validLineClicked = false; // клик ПКМ на существующей строке таблицы, false - строка не выбрана
int nCurScrollOfficerNum;
int iCharQty, iGoodIndex;
bool bQuestItem;
bool isMusketLoadPress = false;
bool bShowTabOfficers = true;

void InitInterface(string iniName)
{
    xi_refCharacter = pchar;
	InterfaceStack.SelectMenu_node = "LaunchInventory"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleCharacter";
	if (CheckAttribute(&InterfaceStates, "nCurScrollTab") && sti(InterfaceStates.nCurScrollTab) == 2)
	{
		bShowTabOfficers = false;
		currentScrollTab = 2;
	}
	FillCharactersScrollEx(bShowTabOfficers);
	FillPassengerScroll();
 	if (CheckAttribute(&InterfaceStates, "CurCharacter")) 
	{
		GameInterface.CHARACTERS_SCROLL.current = InterfaceStates.CurCharacter;
		ProcessFrame();
	}

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("eScrollTabControlPress","procScrollTabChange",0);
	SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("OfficerChange","OfficerChange",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("ExitRemoveOfficerMenu","ExitRemoveOfficerMenu",0);
	SetEventHandler("AcceptRemoveOfficer","AcceptRemoveOfficer",0);
	SetEventHandler("ExitMapWindow","ExitMapWindow",0);	
	SetEventHandler("EquipItem","EquipItem",0);
	SetEventHandler("RemoveItem","RemoveItem",0);
	SetEventHandler("RemoveSlotItemOk","RemoveSlotItemOk",0);
	SetEventHandler("RemoveItemCancel","RemoveItemMsgExit",0);
	SetEventHandler("WarningHide","WarningHide",0);
	// выбросить предмет
	SetEventHandler("ShowBoxMove", "ShowBoxMove", 0);
	SetEventHandler("GoodsExitCancel", "GoodsExitCancel", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);	
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);
	//
	XI_RegistryExitKey("IExit_F2");
	
	SetVariable();
    SetNodeUsing("CHARACTERS_SCROLL",true);
    SetCurrentNode("CHARACTERS_SCROLL");
	
	GameInterface.StatusLine.LOYALITY.Max = 1;
    GameInterface.StatusLine.LOYALITY.Min = 0;
    GameInterface.StatusLine.LOYALITY.Value = 0;
	
	if (IsMainCharacter(xi_refCharacter))
	{
		SetFormatedText("LOYALITY_STR", XI_ConvertString("Authority"));
	}
	else
	{
		SetFormatedText("LOYALITY_STR", XI_ConvertString("Loyality"));
	}
	GameInterface.TABLE_ITEMS.select = -1;
	Table_UpdateWindow("TABLE_ITEMS");
	SetControlsTabMode(1);
	if (CheckAttribute(&InterfaceStates, "nCurScrollTab") && CheckAttribute(&InterfaceStates, "CurCharacter")) 
		SetControlsScrollTabMode(currentScrollTab);
	else SetControlsScrollTabMode(1);
	CreateString(true, "CharJob", "", FONT_NORMAL, COLOR_NORMAL, 960, 290, SCRIPT_ALIGN_CENTER, 1.4);
	GameInterface.strings.CharJob = "";
}

// гуляем по меню кнопками Q и E, TAB переключает вкладки таблицы
void ProcessInterfaceControls() 
{
    string controlName = GetEventData();
	if (controlName == "InterfaceGoLeft") {
        IDoExit(RC_INTERFACE_NATIONRELATION);
    }
    if (controlName == "InterfaceGoRight") {
		IDoExit(RC_INTERFACE_TO_SHIP);
    }
	if (controlName == "InterfaceTabSwitch") {
		currentTab = (currentTab + 1) % 5;
		SetControlsTabMode(currentTab + 1);
	}
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	int i, iOfficer;
	
	if(!GetAchievement("ach_CL_132"))
	{
		iOfficer = -1;
		int totalMush = 0;
		for(i = 1; i < 4; i++)
		{		
			iOfficer = GetOfficersIndex(pchar, i); 
			if(iOfficer != -1)
			{
				if(CheckAttribute(&characters[iOfficer], "isMushketer")) totalMush++;
			}
		}
		if(totalMush > 2) Achievment_Set("ach_CL_132");
	}
	if(bGlobalTutor)
	{
		for(i = 1; i < 4; i++)
		{		
			iOfficer = GetOfficersIndex(pchar, i); 
			if(iOfficer != -1)
			{
				DoQuestFunctionDelay("SharlieTutorial_AlonsoHired", 1.0);
			}
		}
	}
	if(CheckAttribute(pchar, "questTemp.SantaMisericordia") && !GetAchievement("ach_CL_139"))
	{
		if(ach139condition()) Achievment_Set("ach_CL_139");
	}
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("eScrollTabControlPress","procScrollTabChange");
	DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("OfficerChange","OfficerChange");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitRemoveOfficerMenu","ExitRemoveOfficerMenu");
	DelEventHandler("AcceptRemoveOfficer","AcceptRemoveOfficer");
	DelEventHandler("ExitMapWindow","ExitMapWindow");
	DelEventHandler("EquipItem","EquipItem");
	DelEventHandler("RemoveItem","RemoveItem");
	DelEventHandler("RemoveSlotItemOk","RemoveSlotItemOk");
	DelEventHandler("RemoveItemCancel","RemoveItemMsgExit");
	DelEventHandler("WarningHide","WarningHide");
	// выбросить предмет
	DelEventHandler("ShowBoxMove", "ShowBoxMove");
	DelEventHandler("GoodsExitCancel", "GoodsExitCancel");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	//
	
	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		DeleteAttribute(&InterfaceStates, "CurCharacter");
		DeleteAttribute(&InterfaceStates, "nCurScrollTab");
		EndCancelInterface(true);
	}
	LAi_SetPlayerType(PChar); // Возвращаем тип игрока
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
    switch(nodName)
	{
		case "EQUIP_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				EquipPress();
				SetCurrentNode("TABLE_ITEMS");
			}
		break;
		case "OPENMAP_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				EquipPress();
				SetCurrentNode("TABLE_ITEMS");
			}
		break;
		case "ATLASADD_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				AtlasAddPress();
				SetCurrentNode("TABLE_ITEMS");
			}
		break;
		case "LOADGUN_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				EquipPress();
				SetCurrentNode("TABLE_ITEMS");
			}
		break;
		case "LOADMUSKET_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				isMusketLoadPress = true;
				EquipPress();
				isMusketLoadPress = false;
				SetCurrentNode("TABLE_ITEMS");
			}
		break;
		case "TABLE_ITEMS":
			if(comName=="click")
			{
				validLineClicked = false;
				if(XI_IsKeyPressed("control")) ShowBoxMove();
			}
		break;
		case "QTY_OK_BUTTON":
			if(comName=="leftstep")
			{
				ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
				REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;
		case "QTY_CANCEL_BUTTON":
			if(comName=="leftstep")
			{
				ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
				REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;
		/////////////////////// menu ///////////////
		case "I_INVENTORY_2":
			if(comName=="click")
			{
			    nodName = "I_INVENTORY";
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
			}
		break;
		case "I_ATLAS_2":
			if(comName=="click")
			{
			    nodName = "I_ATLAS";
			}
		break;
		case "I_ABILITIES_2":
			if(comName=="click")
			{
				// nodName = "I_ABILITIES";
				string attributeName = "pic" + (nCurScrollNum+1);
				if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
				{
					InterfaceStates.CurCharacter = GameInterface.CHARACTERS_SCROLL.current;
				}
				else DeleteAttribute(&InterfaceStates, "CurCharacter");
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ABILITIES);
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_INVENTORY" || nodName == "I_SHIP" || nodName == "I_QUESTBOOK" ||
		nodName == "I_ATLAS" || nodName == "I_ABILITIES" || nodName == "I_NATIONS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	if (nodName == "BTN_ITEM_1" || nodName == "BTN_ITEM_2" || nodName == "BTN_ITEM_3" ||
		nodName == "BTN_ITEM_4" || nodName == "BTN_ITEM_5" || nodName == "BTN_ITEM_6" ||
		nodName == "BTN_ITEM_7" || nodName == "BTN_ITEM_8" || nodName == "BTN_ITEM_9" || 
		nodName == "BTN_ITEM_10"|| nodName == "BTN_ITEM_11")
	{
		if(comName=="deactivate")
		{
			ProcessExitCancel();
		}
	}
	// boal new menu 31.12.04 -->
}

void RemoveItem()
{
	string rComName = GetEventData();
	string rNodName = GetEventData();
	string rItem;
	string equip;
	int index;
	ref arItm;
	int x1 = 1497;
	int y1 = 340;
	int x2 = 1647;
	int y2 = 420;
	int offx = 0;
	int offy = 0;
	
    switch(rNodName)
	{
		case "TABBTNSLOT_1":
			rItem = BLADE_ITEM_TYPE; // сабли
			sMode = 6;
			offx = 137;
		break;
		case "TABBTNSLOT_2":
			rItem = GUN_ITEM_TYPE;
			sMode = 7;
			offx = -137;
		break;
		case "TABBTNSLOT_3":
			rItem = SPYGLASS_ITEM_TYPE; // трубы
			sMode = 8;
			offx = -137;
			offy = 137;
		break;
		case "TABBTNSLOT_4":
			rItem = CIRASS_ITEM_TYPE; // кирасы
			sMode = 9;
		break;
		case "TABBTNSLOT_5":
			rItem = MUSKET_ITEM_TYPE;
			sMode = 10;
			offx = 137;
			offy = -137;
		break;
		case "TABBTNSLOT_6":
			rItem = TALISMAN_ITEM_TYPE; // талисманы/обереги
			sMode = 11;
			offx = -137;
			offy = -137;
		break;
		case "TABBTNSLOT_7":
			rItem = TOOL_ITEM_TYPE; // инструменты
			sMode = 12;
			offx = 137;
			offy = 137;
		break;
		case "TABBTNSLOT_8":
			rItem = "slot1"; // амулеты
			sMode = 13;
			offx = -137;
			offy = 274;
		break;
		case "TABBTNSLOT_9":
			rItem = "slot2"; // амулеты
			sMode = 13;
			offy = 274;
		break;
		case "TABBTNSLOT_10":
			rItem = "slot3"; // амулеты
			sMode = 13;
			offx = 137;
			offy = 274;
		break;
		case "TABBTNSLOT_4L":
			rItem = LANTERN_ITEM_TYPE; // фонарь
			sMode = 17;
		break;
		case "TABBTNSLOT_11":
			rItem = HAT_ITEM_TYPE; // шляпы
			sMode = 18;
		break;
	}
	if (rNodName == "TABBTNSLOT_1" || rNodName == "TABBTNSLOT_2" || rNodName == "TABBTNSLOT_3" ||
		rNodName == "TABBTNSLOT_4" || rNodName == "TABBTNSLOT_5" || rNodName == "TABBTNSLOT_6" ||
		rNodName == "TABBTNSLOT_7" || rNodName == "TABBTNSLOT_8" || rNodName == "TABBTNSLOT_9" || 
		rNodName == "TABBTNSLOT_10"|| rNodName == "TABBTNSLOT_4L"|| rNodName == "TABBTNSLOT_11")
	{
		if (rNodName == "TABBTNSLOT_8" || rNodName == "TABBTNSLOT_9" || rNodName == "TABBTNSLOT_10")
		equip = GetCharacterEquipBySlot(xi_refCharacter, rItem);
		else equip = GetCharacterEquipByGroup(xi_refCharacter, rItem);
		if (equip == "") {
			SetFormatedText("REMOVE_WARNING_TEXT", XI_ConvertString("Not Used"));
			SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_WARNING_TEXT", -1, 4, x1 + offx,y1 + offy,x2 + offx,y2 + offy);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_WARNING_TEXT", 5);
			PostEvent("WarningHide",1000);
			return;
		}
		index = GetItemIndex(equip);
		arItm = &Items[index];
		if (index < 0) {
			return;
		}
		if(ThisItemCanBeEquip(arItm)) {
			SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_ITEM_FRAME", -1, 4, x1 + offx,y1 + offy,x2 + offx,y2 + offy);
			SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_ITEM_TEXT", -1, 4, x1 + 3 + offx,y1 + 14 + offy,x2 - 3 + offx,y2 - 36 + offy);
			SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_ACCEPT_ITEM", -1, 4, x1 + 30 + offx,y1 + 40 + offy,x2 - 30 + offx,y2 - 15 + offy);
			RemoveItemMsgShow();
		} 
		else 
		{
			SetFormatedText("REMOVE_WARNING_TEXT", XI_ConvertString("RemoveError"));
			SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_ITEM_FRAME", -1, 4, x1 + offx,y1 + offy,x2 + offx,y2 + offy);
			SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_WARNING_TEXT", -1, 4, x1 + offx,y1 + offy,x2 + offx,y2 + offy);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_WARNING_TEXT", 5);
			SetNodeUsing("REMOVE_ITEM_FRAME",true);
			PostEvent("WarningHide",1000);
		}
	}
}

void EquipItem()
{
	iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref arItm = &Items[iGoodIndex];
	if(ThisItemCanBeEquip(arItm)) EquipPress();
}

void RemoveItemMsgShow()
{
	XI_WindowShow("REMOVE_ITEM_WINDOW", true);
	XI_WindowDisable("REMOVE_ITEM_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	SetCurrentNode("REMOVE_ACCEPT_ITEM");
}

void RemoveItemMsgExit()
{
	XI_WindowShow("REMOVE_ITEM_WINDOW", false);
	XI_WindowDisable("REMOVE_ITEM_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
}

void RemoveSlotItemOk()
{
	EquipPress();
	SetVariable();
	RemoveItemMsgExit();
	SetControlsTabMode(sMode);
	HideItemSelect();
	UpdateItemInfo();
}

void WarningHide()
{
	SetFormatedText("REMOVE_WARNING_TEXT", "");
	SetNodeUsing("REMOVE_ITEM_FRAME",false);
	SetFormatedText("DROP_WARNING_TEXT", "");
	SetNodeUsing("DROP_ITEM_FRAME",false);
}

void ProcessFrame()
{
	if (sti(GameInterface.CHARACTERS_SCROLL.current)!=nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		SetButtonsState();
		return;
	}
	if (sti(GameInterface.PASSENGERSLIST.current)!= nCurScrollOfficerNum && GetCurrentNode() == "PASSENGERSLIST")
	{
		nCurScrollOfficerNum = sti(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
		return;
	}
}

void SetButtonsState()
{
	string attributeName = "pic" + (nCurScrollNum+1);
	if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		xi_refCharacter = &characters[iCharacter];
		SetControlsTabModeManual(1);
		SetVariable();
	}
	else
	{
        xi_refCharacter = pchar;
		SetControlsTabModeManual(1);
		SetVariable();
	}
}

void SetVariable()
{
	// доп инфа в шапку --->
	SetAlertMarks(xi_refCharacter);
	SetFormatedText("Weight", FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / " + GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("Money", FindRussianMoneyString(sti(xi_refCharacter.money)));
	SetFormatedText("Dublon", FindRussianDublonString(sti(xi_refCharacter.dublon)));
	SetFormatedText("Rank", xi_refCharacter.rank);
	SetFormatedText("Rank_progress", GetCharacterRankRateCur(xi_refCharacter) + " / " + GetCharacterRankRate(xi_refCharacter));
	// порог уровня
	GameInterface.StatusLine.BAR_RANK.Max   = GetCharacterRankRate(xi_refCharacter);
	GameInterface.StatusLine.BAR_RANK.Min   = 0;
	GameInterface.StatusLine.BAR_RANK.Value = GetCharacterRankRateCur(xi_refCharacter);	
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"BAR_RANK",0);
	// <--- 
	// items --->
	SetFormatedText("SETUP_FRAME_CAPTION", XI_ConvertString("Equipment"));	
	SortItems(xi_refCharacter); //сортировка
	FillItemsTable(currentTab+1); // fix
	HideItemSelect();
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	// <----
	FillTableOther();
	SetHatSlot(xi_refCharacter);
	SetNewPicture("CHARACTER_BIG_PICTURE", "interfaces\le\portraits\512\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_NAME", GetFullName(xi_refCharacter));
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"HERO_NAME",5);

	//navy --> alcohol
	if (xi_refCharacter.id == pchar.id && CheckAttribute(xi_refCharacter, "chr_ai.drunk"))
	{
		SetNewGroupPicture("CHARACTER_DRUNK_PICTURE", "ITEMS_19", "itm7");
		SetNodeUsing("CHARACTER_DRUNK_PICTURE", true);
	}
	else
	{
		SetNodeUsing("CHARACTER_DRUNK_PICTURE", false);
	}
	//navy <--
	bool bShowNations = true;
	if(CheckCharacterPerk(xi_refCharacter, "ByWorker"))
	{
		SetNewGroupPicture("CHARACTER_NATION_PICTURE", "PERKS_ENABLE", "ByWorker");
		if(CheckCharacterPerk(xi_refCharacter, "ByWorker2")) SetNewGroupPicture("CHARACTER_NATION_PICTURE", "PERKS_ENABLE", "ByWorker2");
	}
	else
	{
		bShowNations = false;
		if(xi_refCharacter.id == pchar.id) 
		{
			SetNewGroupPicture("CHARACTER_NATION_PICTURE", "NATIONS", GetNationNameByType(GetBaseHeroNation()));
			bShowNations = true;
		}
	}
	SetNodeUsing("CHARACTER_NATION_PICTURE", bShowNations);
	
	if (bBettaTestMode)
    {
        CreateString(true,"healthCur1",
                     "pchar MaxHP = "    + FloatToString(stf(pchar.Health.maxHP), 1) +
                     " CurHP = "   + FloatToString(stf(pchar.Health.HP), 1) +
                     " WeekDmg = " + FloatToString(stf(pchar.Health.weekDamg), 1) +
                     " DayDmg = "  + FloatToString(stf(pchar.Health.Damg), 1),
                     "INTERFACE_ULTRASMALL",COLOR_NORMAL,10,1070, SCRIPT_ALIGN_LEFT,1.0);
    }
    
    // теперь это Лояльность		
	if (xi_refCharacter.id == pchar.id)
	{
		GameInterface.StatusLine.LOYALITY.Max   = COMPLEX_REPUTATION_MAX;
		GameInterface.StatusLine.LOYALITY.Min   = COMPLEX_REPUTATION_MIN;
		GameInterface.StatusLine.LOYALITY.Value = sti(xi_refCharacter.reputation.authority);
		
		SetFormatedText("REPUTATION_STR", GetFullReputationComplexName(xi_refCharacter));
	}
	else
	{
		GameInterface.StatusLine.LOYALITY.Max   = MAX_LOYALITY;
		GameInterface.StatusLine.LOYALITY.Min   = 0;
		GameInterface.StatusLine.LOYALITY.Value = GetCharacterLoyality(xi_refCharacter);
		
		SetFormatedText("REPUTATION_STR", XI_ConvertString(GetReputationName(sti(xi_refCharacter.reputation))));
	}	
    if (xi_refCharacter.id == pchar.id)
    {
	    GameInterface.StatusLine.BAR_HEALTH.Max   = 60;
	    GameInterface.StatusLine.BAR_HEALTH.Min   = 1;
	    GameInterface.StatusLine.BAR_HEALTH.Value = makeint(pchar.Health.HP);
	    if (sti(pchar.Health.HP) > 60 )
	    {
	        GameInterface.StatusLine.BAR_HEALTH.Value = 60;
	    }
    }
    else
    {
		// belamour legendary edition бар для бессмертного офицера -->
		if(CheckAttribute(xi_refCharacter, "OfficerImmortal"))
		{
			GameInterface.StatusLine.BAR_HEALTH.Max   = 60;
			GameInterface.StatusLine.BAR_HEALTH.Min   = 1;
			GameInterface.StatusLine.BAR_HEALTH.Value = makeint(xi_refCharacter.Health.HP);
			if (sti(xi_refCharacter.Health.HP) > 60 )
			{
				GameInterface.StatusLine.BAR_HEALTH.Value = 60;
			}
		}
		else
		{
			GameInterface.StatusLine.BAR_HEALTH.Max = 1;
			GameInterface.StatusLine.BAR_HEALTH.Min = 0;
			GameInterface.StatusLine.BAR_HEALTH.Value = 0;
		}
		//<-- legendary edition			 
    }

    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"LOYALITY",0);
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"BAR_HEALTH",0);
    
	if ( IsMainCharacter(xi_refCharacter) )
	{
		SetFormatedText("LOYALITY_STR", XI_ConvertString("Authority"));
	}
	else
	{
		SetFormatedText("LOYALITY_STR", XI_ConvertString("Loyality"));
	}	
	RefreshSetupBigPicture();
}

void RefreshSetupBigPicture()
{
	switch (xi_refCharacter.id)
	{
		case "Blaze":
			if (HasSubStr(xi_refCharacter.model, "Sharle")) SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Sharle.tga");
			else 
			{
				if(startHeroType == 4) SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Helena.tga");
				else SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Man.tga");
			}
		break;
		case "Tichingitu":
		SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Tichingitu.tga");
		break;
		case "Longway":
		SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Longway.tga");
		break;
		case "Knippel":
		SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Knippel.tga");
		break;
		case "Folke":
		SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Folke.tga");
		break;
		case "Duran":
		SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Claude.tga");
		break;
		case "Tonzag":
		SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Tonzag.tga");
		break;
		case "Mary":
		SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Mary.tga");
		break;
		case "Helena":
		SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Helena.tga");
		break;
        if (xi_refCharacter.sex == "man")
        SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Man.tga");
        else
        SetNewPicture("SETUP_BIG_PICTURE", "interfaces\le\equipment\CharacterEquipment_Helena.tga");		
	}
}
	
void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;
	ref arItm = &Items[iGoodIndex];
	ref rItem = ItemsFromID(arItm.id);
	int lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	int	picW = 128;
	int	picH = 128;

	sPicture = "-1";
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "CHARACTERS_SCROLL":
			picW = 256;
			picH = 256;
			nChooseNum = SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"CHARACTERS_SCROLL", 2 );
			string attributeName = "pic" + (nChooseNum+1);
			int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
            sHeader = XI_ConvertString("passengership");
			sText1 = "";
			sText2 = "";

			if(currentScrollTab == 1)
			{
				switch(nChooseNum)
				{
					case 0:
						sHeader = GetCharacterFullName(pchar.id);
						sText1 = "";
						sText2 = XI_ConvertString("It's you");
						sText3 = "";
					break;

					case 1:
						sHeader = XI_ConvertString("navigator");
						sText1 = XI_ConvertString("Navigator_Descr");
						sText2 = XI_ConvertString("Navigator_Up");
					break;

					case 2:
						sHeader = XI_ConvertString("boatswain");
						sText1 = XI_ConvertString("Boatswain_Descr");
						sText2 = XI_ConvertString("Boatswain_Up");
					break;

					case 3:
						sHeader = XI_ConvertString("cannoner");
						sText1 = XI_ConvertString("Cannoner_Descr");
						sText2 = XI_ConvertString("Cannoner_Up");
					break;

					case 4:
						sHeader = XI_ConvertString("doctor");
						sText1 = XI_ConvertString("Doctor_Descr");
						sText2 = XI_ConvertString("Doctor_Up");
					break;

					case 5:
						sHeader = XI_ConvertString("treasurer");
						sText1 = XI_ConvertString("Treasurer_Descr");
						sText2 = XI_ConvertString("Treasurer_Up");
					break;

					case 6:
						sHeader = XI_ConvertString("carpenter");
						sText1 = XI_ConvertString("Carpenter_Descr");
						sText2 = XI_ConvertString("Carpenter_Up");
					break;

					case 7:
						sHeader = XI_ConvertString("fighter");
						sText1 = XI_ConvertString("Officer_Descr");
						sText2 = XI_ConvertString("Officer_Up");
					break;

					case 8:
						sHeader = XI_ConvertString("fighter");
						sText1 = XI_ConvertString("Officer_Descr");
						sText2 = XI_ConvertString("Officer_Up");
					break;

					case 9:
						sHeader = XI_ConvertString("fighter");
						sText1 = XI_ConvertString("Officer_Descr");
						sText2 = XI_ConvertString("Officer_Up");
					break;
				}

				if(iCharacter != 0)
				{
					ref rchr = &Characters[iCharacter];
					iItem = GetMoneyForOfficerFull(rchr);
					if (iItem > 0)
					{
						sText2 = XI_ConvertString("HirePrice") + " " + FindRussianMoneyString(iItem) + " " + XI_ConvertString("per month");
					}
					if(FindFellowtravellers(pchar,rchr) != FELLOWTRAVEL_COMPANION)
					{
						sText3 = XI_ConvertString("AddRemoveOfficerScroll");
					}
					else
					{
						if(CheckAttribute(rchr, "quest.convoyquest.money"))
						{
							sText3 = "";//SelectEscortQuestInfo(rchr);
						}
						sText1 = GetCharacterFullName(Characters[iCharacter].id);
						sHeader = XI_ConvertString("companionship");
					}
					sPicture = "interfaces\le\portraits\512\face_" + rchr.FaceId + ".tga"
					if(CheckCharacterPerk(xi_refCharacter, "ByWorker")) 
					{
						if(CheckCharacterPerk(xi_refCharacter, "ByWorker2")) sText2 = sText2 + NewStr() + GetConvertStr("perkByWorker2Short", "AbilityDescribe.txt"));
						else sText2 = sText2 + NewStr() + GetConvertStr("perkByWorkerShort", "AbilityDescribe.txt"));
					}
				}
			}
			else
			{
				if(nChooseNum == 0)
				{
					sHeader = XI_ConvertString("captain");
					sText1 = "";
					sText2 = XI_ConvertString("It's you");
					sText3 = "";
				}
				if(iCharacter != 0)
				{
					ref rchar = &Characters[iCharacter];
					if(FindFellowtravellers(pchar,rchar) != FELLOWTRAVEL_COMPANION)
					{
						sText1 = GetCharacterFullName(Characters[iCharacter].id);
						if (CheckAttribute(&Characters[iCharacter], "prisoned") && Characters[iCharacter].prisoned == true)
						{
							sHeader = GetRPGText("Prisoner");
							sText2 = GetRPGText("Prisoner_desc");
						}
					}
					sPicture = "interfaces\le\portraits\512\face_" + rchar.FaceId + ".tga"
					if(CheckCharacterPerk(rchar, "ByWorker")) 
					{
						if(CheckCharacterPerk(rchar, "ByWorker2")) sText2 = sText2 + NewStr() + GetConvertStr("perkByWorker2Short", "AbilityDescribe.txt"));
						else sText2 = sText2 + NewStr() + GetConvertStr("perkByWorkerShort", "AbilityDescribe.txt"));
					}
				}
				else return;
			}
			if(sPicture == "-1")
			{
				sPicture = "interfaces\le\portraits\512\" + sHeader + ".tga";
			}
			if (bBettaTestMode)
			{
				if(iCharacter != 0) sText3 += "   " +  Characters[iCharacter].id;
			}
		break;
		
		case "LOYALITY_STR":
			if ( IsMainCharacter(xi_refCharacter) )		
			{
				sHeader = XI_ConvertString("Authority");
				sText1  = GetRPGText("Authority");
			}
			else
			{
				sHeader = XI_ConvertString("Loyality");
				sText1  = GetRPGText("Loyality");
			}	
		break;
		case "REPUTATION_STR":
		    sHeader = XI_ConvertString("Reputation");
		    sText1  = GetRPGText("Reputation");
		break;

		case "TABLE_OTHER":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;

		case "TABLE_ITEMS":
			if(CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
			{
				sHeader = LanguageConvertString(lngFileID, rItem.name);
				sText1  = GetAssembledString(LanguageConvertString(lngFileID, arItm.describe), rItem);
				sGroup = rItem.picTexture;
				sGroupPicture = "itm" + rItem.picIndex;
			}
			else
			{
				sHeader = XI_ConvertString("Items");
				sText1  = XI_ConvertString("ItemsDescribe1");
			}
			sText2  = XI_ConvertString("ItemsDescribe2");
			sText3  = XI_ConvertString("ItemsDescribe3");
		break;
		
		case "CHARACTER_NATION_PICTURE":
		    sHeader = XI_ConvertString("Nation");
			sText1 = GetRPGText("Nation_hint");
			if(CheckCharacterPerk(xi_refCharacter, "ByWorker")) 
			{
				sHeader = GetConvertStr("ByWorker", "AbilityDescribe.txt"));
				sText1 = GetConvertStr("perkByWorkerShort", "AbilityDescribe.txt"));
			}
			if(CheckCharacterPerk(xi_refCharacter, "ByWorker2")) 
			{
				sHeader = GetConvertStr("ByWorker2", "AbilityDescribe.txt"));
				sText1 = GetConvertStr("perkByWorker2Short", "AbilityDescribe.txt"));
			}			
		break;
		//navy-->
		case "CHARACTER_DRUNK_PICTURE":
		    sHeader = XI_ConvertString("Alcohol");
			sText1 = GetRPGText("Drunk_hint");
		break;
		//<--navy
		case "WEIGHT":
		    sHeader = XI_ConvertString("Weight");
			sText1 = GetRPGText("Weight");
		break;
		case "MONEY":
		    sHeader = XI_ConvertString("Money");
			sText1 = GetRPGText("Money");
		break;		
		case "RANK":
		    sHeader = XI_ConvertString("Rank");
			sText1 = GetRPGText("Rank");
		break;
		case "TABBTNSLOT_1":
		    sHeader = XI_ConvertString("ItemSlot_1");
			sText1 = XI_ConvertString("ItemSlot_1_d");
			sText2 = XI_ConvertString("ItemSlot_Info_d1");
			sText3 = XI_ConvertString("ItemSlot_Info_d2");
		break;
		case "TABBTNSLOT_2":
		    sHeader = XI_ConvertString("ItemSlot_2");
			sText1 = XI_ConvertString("ItemSlot_2_d");
			sText2 = XI_ConvertString("ItemSlot_Info_d1");
			sText3 = XI_ConvertString("ItemSlot_Info_d2");
		break;
		case "TABBTNSLOT_3":
		    sHeader = XI_ConvertString("ItemSlot_3");
			sText1 = XI_ConvertString("ItemSlot_3_d");
			sText2 = XI_ConvertString("ItemSlot_Info_d1");
			sText3 = XI_ConvertString("ItemSlot_Info_d2");
		break;
		case "TABBTNSLOT_4":
		    sHeader = XI_ConvertString("ItemSlot_4");
			sText1 = XI_ConvertString("ItemSlot_4_d");
			sText2 = XI_ConvertString("ItemSlot_Info_d1");
			sText3 = XI_ConvertString("ItemSlot_Info_d2");
		break;
		case "TABBTNSLOT_5":
		    sHeader = XI_ConvertString("ItemSlot_5");
			sText1 = XI_ConvertString("ItemSlot_5_d");
			sText2 = XI_ConvertString("ItemSlot_Info_d1");
			sText3 = XI_ConvertString("ItemSlot_Info_d2");
		break;
		case "TABBTNSLOT_6":
		    sHeader = XI_ConvertString("ItemSlot_6");
			sText1 = XI_ConvertString("ItemSlot_6_d");
			sText2 = XI_ConvertString("ItemSlot_Info_d1");
			sText3 = XI_ConvertString("ItemSlot_Info_d2");
			if(IsEquipCharacterByArtefact(xi_refCharacter, "talisman17"))
			{
				rItem = ItemsFromID("talisman17");
				sHeader = LanguageConvertString(lngFileID, "itmname_talisman17");
				sText1 = LanguageConvertString(lngFileID, "itmdescr_talisman17");
				if(CheckAttribute(rItem,"QBonus"))
				{
					sText2 = GetAssembledString(LanguageConvertString(lngFileID,"talisman17_quests"), rItem);
				}
				else
				{
					sText2 = LanguageConvertString(lngFileID, "talisman17_questsNoBonus");
				}
				sGroup = rItem.picTexture;
				sGroupPicture = "itm" + rItem.picIndex;
			}
		break;
		case "TABBTNSLOT_7":
		    sHeader = XI_ConvertString("ItemSlot_7");
			sText1 = XI_ConvertString("ItemSlot_7_d");
			sText2 = XI_ConvertString("ItemSlot_Info_d1");
			sText3 = XI_ConvertString("ItemSlot_Info_d2");
		break;
		case "TABBTNSLOT_8":
		    sHeader = XI_ConvertString("ItemSlot_8-10");
			sText1 = XI_ConvertString("ItemSlot_8-10_d");
			sText2 = XI_ConvertString("ItemSlot_8-10!_d");
			sText3 = XI_ConvertString("ItemSlot_Info_d1");
		break;
		case "TABBTNSLOT_9":
		    sHeader = XI_ConvertString("ItemSlot_8-10");
			sText1 = XI_ConvertString("ItemSlot_8-10_d");
			sText2 = XI_ConvertString("ItemSlot_8-10!_d");
			sText3 = XI_ConvertString("ItemSlot_Info_d1");
		break;
		case "TABBTNSLOT_10":
		    sHeader = XI_ConvertString("ItemSlot_8-10");
			sText1 = XI_ConvertString("ItemSlot_8-10_d");
			sText2 = XI_ConvertString("ItemSlot_8-10!_d");
			sText3 = XI_ConvertString("ItemSlot_Info_d1");
		break;
		case "TABBTNSLOT_11":
		    sHeader = "Шляпа";
			sText1 = "Шляпа";
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,255,192), sText3, argb(255,255,192,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, picW, picH);
	LanguageCloseFile(lngFileID);
}

void HideInfoWindow()
{
	CloseTooltip();
	RemoveItemMsgExit();
}

void FillTableOther()
{
	int     i;
	string  row, skillName;
    int     diff, skillVal;

    // boal оптимизация скилов -->
    DelBakSkillAttr(xi_refCharacter);
    ClearCharacterExpRate(xi_refCharacter);
    RefreshCharacterSkillExpRate(xi_refCharacter);
    SetEnergyToCharacter(xi_refCharacter);
    // boal оптимизация скилов <--

	////  остальное
	GameInterface.TABLE_OTHER.select = 0;
	GameInterface.TABLE_OTHER.hr.td1.str = "";
	for (i=1; i<=8; i++)
	{
	    row = "tr" + i;

	    GameInterface.TABLE_OTHER.(row).td1.icon.width = 40;
    	GameInterface.TABLE_OTHER.(row).td1.icon.height = 40;
    	GameInterface.TABLE_OTHER.(row).td1.icon.offset = "0, 0";
		GameInterface.TABLE_OTHER.(row).td2.align = "left";
		// GameInterface.TABLE_OTHER.(row).td2.scale = 0.85;
		GameInterface.TABLE_OTHER.(row).td2.textoffset = "10,0";
		GameInterface.TABLE_OTHER.(row).td3.align = "right";
	}

	
	GameInterface.TABLE_OTHER.tr1.UserData.ID = "Life";
	GameInterface.TABLE_OTHER.tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr1.td1.icon.image = "Life";
	GameInterface.TABLE_OTHER.tr1.td2.str = XI_ConvertString("Life");
	GameInterface.TABLE_OTHER.tr1.td3.str = MakeInt(LAi_GetCharacterHP(xi_refCharacter)) + " / " + MakeInt(LAi_GetCharacterMaxHP(xi_refCharacter));

    GameInterface.TABLE_OTHER.tr2.UserData.ID = "Energy";
	GameInterface.TABLE_OTHER.tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr2.td1.icon.image = "Energy";
	GameInterface.TABLE_OTHER.tr2.td2.str = XI_ConvertString("Energy");
	GameInterface.TABLE_OTHER.tr2.td3.str = sti(Lai_CharacterGetEnergy(xi_refCharacter)) + " / " + sti(LAi_GetCharacterMaxEnergy(xi_refCharacter));
	diff = sti(LAi_GetCharacterMaxEnergy(xi_refCharacter) - GetCharacterMaxEnergyABSValue(xi_refCharacter));
	if (diff != 0)
	{
	   if (diff > 0)
	   {
          GameInterface.TABLE_OTHER.tr2.td3.color = argb(255,196,255,196);
       }
       else
       {
          GameInterface.TABLE_OTHER.tr2.td3.color = argb(255,255,196,196);
       }
	}
	else
	{
		DeleteAttribute(&GameInterface, "TABLE_OTHER.tr3.td3.color");
	}

    GameInterface.TABLE_OTHER.tr3.UserData.ID = "Health";
	GameInterface.TABLE_OTHER.tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr3.td1.icon.image = "Health";
	GameInterface.TABLE_OTHER.tr3.td2.str = XI_ConvertString("Health");
	GameInterface.TABLE_OTHER.tr3.td3.str = GetHealthName(xi_refCharacter);
	GameInterface.TABLE_OTHER.tr3.td3.scale = 1.3;
	
	if (GetHealthNum(xi_refCharacter) >= GetHealthMaxNum(xi_refCharacter))
    {
        GameInterface.TABLE_OTHER.tr3.td3.color = SetAlphaIntoColor(COLOR_MONEY, GetAlphaFromSkill(10));
    }
    else
    {
        GameInterface.TABLE_OTHER.tr3.td3.color = SetAlphaIntoColor(COLOR_NORMAL, GetAlphaFromSkill(makeint(GetHealthNum(xi_refCharacter)* 1.9)));
    }
    
	GameInterface.TABLE_OTHER.tr4.UserData.ID = "Crit";
	GameInterface.TABLE_OTHER.tr4.td1.icon.group = "PERKS_ENABLE";
    GameInterface.TABLE_OTHER.tr4.td1.icon.image = "CriticalHit";
	GameInterface.TABLE_OTHER.tr4.td2.str = XI_ConvertString("Crit");
	GameInterface.TABLE_OTHER.tr4.td3.str = GetAttackCritical(xi_refCharacter)+"%/"+GetShotCritical(xi_refCharacter)+"%";

	GameInterface.TABLE_OTHER.tr5.UserData.ID = "CharDefence";
	GameInterface.TABLE_OTHER.tr5.td1.icon.group = "PERKS_ENABLE";
    GameInterface.TABLE_OTHER.tr5.td1.icon.image = "AdvancedDefense";
	GameInterface.TABLE_OTHER.tr5.td2.str = XI_ConvertString("CharDefence");
	GameInterface.TABLE_OTHER.tr5.td3.str = GetDefenceBlade(xi_refCharacter) + " / "+GetDefenceGun(xi_refCharacter)+ " / "+GetDefenceCritical(xi_refCharacter);
	
    GameInterface.TABLE_OTHER.tr6.UserData.ID = "Title";
	GameInterface.TABLE_OTHER.tr6.td1.icon.group = "ICONS_CHAR";
	GameInterface.TABLE_OTHER.tr6.td1.icon.image = "Title";
	
	DeleteAttribute(&GameInterface, "TABLE_OTHER.tr6.td2");
	GameInterface.TABLE_OTHER.tr6.td2.str = XI_ConvertString("Title");
	GameInterface.TABLE_OTHER.tr6.td2.align = "left";
	// GameInterface.TABLE_OTHER.tr6.td2.scale = 0.85;
	GameInterface.TABLE_OTHER.tr6.td2.textoffset = "10,0";

    DeleteAttribute(&GameInterface, "TABLE_OTHER.tr6.td3");
    GameInterface.TABLE_OTHER.tr6.td3.str = "";
	// GameInterface.TABLE_OTHER.tr6.td3.scale = 0.9;
	
	if (xi_refCharacter.id == pchar.id && isMainCharacterPatented())
    {
        GameInterface.TABLE_OTHER.tr6.td3.str = GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur));
		GameInterface.TABLE_OTHER.tr6.td3.align = "right";
		// GameInterface.TABLE_OTHER.tr6.td3.scale = 1.4;
        GameInterface.TABLE_OTHER.tr6.td2.icon.group = "NATIONS";
		GameInterface.TABLE_OTHER.tr6.td2.icon.image = GetNationNameByType(sti(Items[sti(pchar.EquipedPatentId)].Nation));
		GameInterface.TABLE_OTHER.tr6.td2.icon.offset = "80, 5";
		GameInterface.TABLE_OTHER.tr6.td2.icon.width = 30;
		GameInterface.TABLE_OTHER.tr6.td2.icon.height = 30;
    }
    else
    {
        GameInterface.TABLE_OTHER.tr6.td3.str = XI_ConvertString("NoTitle");
		GameInterface.TABLE_OTHER.tr6.td3.align = "right";
    }

	GameInterface.TABLE_OTHER.tr7.UserData.ID = "Rank";
	GameInterface.TABLE_OTHER.tr7.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr7.td1.icon.image = "Rank";
	GameInterface.TABLE_OTHER.tr7.td2.str = XI_ConvertString("Rank");
	GameInterface.TABLE_OTHER.tr7.td3.str = sti(xi_refCharacter.rank);
	
	GameInterface.TABLE_OTHER.tr8.UserData.ID = "NextExp";
	GameInterface.TABLE_OTHER.tr8.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr8.td1.icon.image = "NextExp";
	GameInterface.TABLE_OTHER.tr8.td2.str = XI_ConvertString("NextExp");
	GameInterface.TABLE_OTHER.tr8.td3.str = "";
	
	// прорисовка
    Table_UpdateWindow("TABLE_OTHER");
}	

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index)
    NullSelectTable("TABLE_OTHER");
    // перерисует "порог опыта"
    GameInterface.TABLE_OTHER.tr8.td3.str = "";
    if (CurTable == "TABLE_OTHER" && CurRow == "tr1")
    {
    	GameInterface.TABLE_OTHER.tr8.td3.str = GetCharacterRankRateCur(xi_refCharacter) + "/" + GetCharacterRankRate(xi_refCharacter);
    }
	Table_UpdateWindow("TABLE_OTHER");
	validLineClicked = true;
	// отрисовка инфы
    if (CurTable == "TABLE_ITEMS") UpdateItemInfo();
	GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_ITEMS");
	HideItemSelect();
	if(sNodName == "TABBTN_1")
	{
		SetControlsTabModeManual(1);
		return;
	}
	if(sNodName == "TABBTN_2")
	{
		SetControlsTabModeManual(2);
		return;
	}
	if(sNodName == "TABBTN_3")
	{
		SetControlsTabModeManual(3);
		return;
	}
	if(sNodName == "TABBTN_4")
	{
		SetControlsTabModeManual(4);
		return;
	}
	if(sNodName == "TABBTN_5")
	{
		SetControlsTabModeManual(5);
		return;
	}
	if(sNodName == "TABBTNSLOT_1")
	{
		SetControlsTabModeManual(6);
		SetNodeUsing("ITEM_SELECT_1",true);
		SelectItemByType(BLADE_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_2")
	{
		SetControlsTabModeManual(7);
		SetNodeUsing("ITEM_SELECT_2",true);
		SelectItemByType(GUN_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_3")
	{
		SetControlsTabModeManual(8);
		SetNodeUsing("ITEM_SELECT_3",true);
		SelectItemByType(SPYGLASS_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_4")
	{
		SetControlsTabModeManual(9);
		SetNodeUsing("ITEM_SELECT_4",true);
		SelectItemByType(CIRASS_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_5")
	{
		SetControlsTabModeManual(10);
		SetNodeUsing("ITEM_SELECT_5",true);
		SelectItemByType(MUSKET_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_6")
	{
		SetControlsTabModeManual(11);
		SetNodeUsing("ITEM_SELECT_6",true);
		SelectItemByType(TALISMAN_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_7")
	{
		SetControlsTabModeManual(12);
		SetNodeUsing("ITEM_SELECT_7",true);
		SelectItemByType(TOOL_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_8")
	{
		SetControlsTabModeManual(13);
		SetNodeUsing("ITEM_SELECT_8",true);
		SetNodeUsing("ITEM_SELECT_9",true);
		SetNodeUsing("ITEM_SELECT_10",true);
		SelectAmulet("slot1");
		return;
	}
	if(sNodName == "TABBTNSLOT_9")
	{
		SetControlsTabModeManual(13);
		SetNodeUsing("ITEM_SELECT_8",true);
		SetNodeUsing("ITEM_SELECT_9",true);
		SetNodeUsing("ITEM_SELECT_10",true);
		SelectAmulet("slot2");						
		return;
	}
	if(sNodName == "TABBTNSLOT_10")
	{
		SetControlsTabModeManual(13);
		SetNodeUsing("ITEM_SELECT_8",true);
		SetNodeUsing("ITEM_SELECT_9",true);
		SetNodeUsing("ITEM_SELECT_10",true);
		SelectAmulet("slot3");						
		return;
	}
	if(sNodName == "TABBTNSLOT_2B")
	{
		SetControlsTabModeManual(16);
		SelectAmmoType(GUN_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_5B")
	{
		SetControlsTabModeManual(16);
		SelectAmmoType(MUSKET_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_4L")
	{
		SetControlsTabModeManual(17);
		SelectItemByType(LANTERN_ITEM_TYPE);
		return;
	}
	if(sNodName == "TABBTNSLOT_11")
	{
		SetControlsTabModeManual(18);
		SetNodeUsing("ITEM_SELECT_11",true);
		SelectItemByType(HAT_ITEM_TYPE);
		return;
	}
}

// метод на TAB переключает вкладки таблицы
void SetControlsTabModeManual(int mode) 
{
    currentTab = mode - 1;
    SetControlsTabMode(mode);
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;
	int nColor5 = nColor1;

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;
	string sPic5 = sPic1;

	string sPic6 = sPic1;
	string sPic7 = sPic1;
	string sPic8 = sPic1;
	string sPic9 = sPic1;
	string sPic10 = sPic1;

	string sPic11 = "Empty";
	string sPic12 = sPic11;
	string sPic13 = sPic11;
	string sPic14 = sPic11;
	string sPic15 = sPic11;
	string sPic16 = sPic11;
	string sPic17 = sPic11;
	string sPic18 = sPic11;
	string sPic19 = sPic11;
	string sPic20 = sPic11;

	string sPic21 = "Empty";
	string sPic22 = sPic11;
	string sPic23 = sPic11;
	string sPic24 = sPic11;
	string sPic25 = sPic11;
	string sPic26 = sPic11;
	string sPic27 = sPic11;
	string sPic28 = sPic11;
	string sPic29 = sPic11;
	string sPic30 = sPic11;
	
	string sPic31 = sPic11;
	string sPic32 = sPic11;

	switch (nMode)
	{
		case 1:
			sPic1 = "TabSelected";
			sPic6 = "TabSelectedMark";
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabSelected";
			sPic7 = "TabSelectedMark";
			nColor2 = argb(255,255,255,255);
		break;
		case 3:
			sPic3 = "TabSelected";
			sPic8 = "TabSelectedMark";
			nColor3 = argb(255,255,255,255);
		break;
		case 4:
			sPic4 = "TabSelected";
			sPic9 = "TabSelectedMark";
			nColor4 = argb(255,255,255,255);
		break;
		case 5:
			sPic5 = "TabSelected";
			sPic10 = "TabSelectedMark";
			nColor5 = argb(255,255,255,255);
		break;
		case 6:
			sPic11 = "glow";
			sPic21 = "slotframe";
		break;
		case 7:
			sPic12 = "glow";
			sPic22 = "slotframe";
		break;
		case 8:
			sPic13 = "glow";
			sPic23 = "slotframe";
		break;
		case 9:
			sPic14 = "glow";
			sPic24 = "slotframe";
		break;
		case 10:
			sPic15 = "glow";
			sPic25 = "slotframe";
		break;
		case 11:
			sPic16 = "glow";
			sPic26 = "slotframe";
		break;
		case 12:
			sPic17 = "glow";
			sPic27 = "slotframe";
		break;
		case 13:
			sPic18 = "glow";
			sPic28 = "slotframe";
		break;
		case 14:
			sPic19 = "glow";
			sPic29 = "slotframe";
		break;
		case 15:
			sPic20 = "glow";
			sPic30 = "slotframe";
		break;
		case 18:
			sPic31 = "glow";
			sPic32 = "slotframe";
		break;
	}
    
	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS", sPic4);
	SetNewGroupPicture("TABBTN_5", "TABS", sPic5);
	SetNewGroupPicture("TABBTN_1_MARK", "TABS", sPic6);
	SetNewGroupPicture("TABBTN_2_MARK", "TABS", sPic7);
	SetNewGroupPicture("TABBTN_3_MARK", "TABS", sPic8);
	SetNewGroupPicture("TABBTN_4_MARK", "TABS", sPic9);
	SetNewGroupPicture("TABBTN_5_MARK", "TABS", sPic10);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,nColor2);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_3", 8,0,nColor3);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_4", 8,0,nColor4);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_5", 8,0,nColor5);

	// items slots
	SetNewGroupPicture("TABBTNSLOT_1", "ITEMS_GLOW", sPic11);
	SetNewGroupPicture("TABBTNSLOT_2", "ITEMS_GLOW", sPic12);
	SetNewGroupPicture("TABBTNSLOT_3", "ITEMS_GLOW", sPic13);
	SetNewGroupPicture("TABBTNSLOT_4", "ITEMS_GLOW", sPic14);
	SetNewGroupPicture("TABBTNSLOT_5", "ITEMS_GLOW", sPic15);
	SetNewGroupPicture("TABBTNSLOT_6", "ITEMS_GLOW", sPic16);
	SetNewGroupPicture("TABBTNSLOT_7", "ITEMS_GLOW", sPic17);
	SetNewGroupPicture("TABBTNSLOT_8", "ITEMS_GLOW", sPic18);
	SetNewGroupPicture("TABBTNSLOT_9", "ITEMS_GLOW", sPic18);
	SetNewGroupPicture("TABBTNSLOT_10", "ITEMS_GLOW", sPic18);
	SetNewGroupPicture("TABBTNSLOT_11", "ITEMS_GLOW", sPic31);
	
	// Выставим таблицу в начало
	GameInterface.TABLE_ITEMS.select = 1;
	GameInterface.TABLE_ITEMS.top = 0;
	FillControlsList(nMode);
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_ITEMS",0);
	validLineClicked = false;
	if(CheckAttribute(GameInterface, "TABLE_ITEMS.tr1.index"))
	{
		SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ITEMS", 2, 0); // ставим принудительно первую строку
		iGoodIndex = sti(GameInterface.TABLE_ITEMS.tr1.index)
		SetItemInfo(iGoodIndex);
	}
	else HideItemInfo();
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: FillItemsTable(1); break;  // все
	    case 2: FillItemsTable(2); break;  // снаряжение
	    case 3: FillItemsTable(3); break;  // эликсиры
	    case 4: FillItemsTable(4); break;  // амулеты
	    case 5: FillItemsTable(5); break;  // прочее

	    case 6: FillItemsTable(6); break;  // сабли
	    case 7: FillItemsTable(7); break;  // пистолеты
	    case 8: FillItemsTable(8); break;  // трубы
	    case 9: FillItemsTable(9); break;  // кирасы
	    case 10: FillItemsTable(10); break;  // мушкеты
	    case 11: FillItemsTable(11); break;  // талисманы
	    case 12: FillItemsTable(12); break;  // инструменты
	    case 13: FillItemsTable(13); break;  // амулеты1
	    case 14: FillItemsTable(14); break;  // амулеты2
	    case 15: FillItemsTable(15); break;  // амулеты3	
	    case 16: FillItemsTable(16); break;  // боеприпасы
	    case 17: FillItemsTable(17); break;  // фонарь
	    case 18: FillItemsTable(18); break;  // шляпы
	}
}

void SetOfficersSkills()
{
	string sCharacter = "pic"+(sti(GameInterface.PASSENGERSLIST.current)+1);
	if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter))
	{
		if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[sti(sCharacter)];
	        SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
	        SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
	        SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
			GameInterface.strings.CharJob = GetOfficerPosition(sCharacter);
	        SetSelectable("ACCEPT_ADD_OFFICER", true);
        }
        else
        {
            Table_Clear("TABLE_SMALLSKILL", false, true, true);
            Table_Clear("TABLE_SMALLOTHER", false, true, true);
            SetFormatedText("OFFICER_NAME", "");
			GameInterface.strings.CharJob = "";
            SetSelectable("ACCEPT_ADD_OFFICER", false);
        }
	}
	else
    {
        Table_Clear("TABLE_SMALLSKILL", false, true, true);
        Table_Clear("TABLE_SMALLOTHER", false, true, true);
        SetFormatedText("OFFICER_NAME", "");
		GameInterface.strings.CharJob = "";
        SetSelectable("ACCEPT_ADD_OFFICER", false);
    }
}

void FillPassengerScroll()
{
	int i, howWork;
	string faceName;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2;
	bool  ok;
	
	DeleteAttribute(&GameInterface, "PASSENGERSLIST");

	nCurScrollOfficerNum = -1;
	GameInterface.PASSENGERSLIST.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetFreePassengersQuantity(pchar);

	GameInterface.PASSENGERSLIST.NotUsed = 6;
	GameInterface.PASSENGERSLIST.ListSize = nListSizeFree + 2;

	GameInterface.PASSENGERSLIST.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("PASSENGERSLIST.ImagesGroup", pchar, 2); // passengers

	GameInterface.PASSENGERSLIST.BadTex1 = 0;
	GameInterface.PASSENGERSLIST.BadPic1 = "emptyface";

	int m = 0;
	for(i=0; i<nListSize; i++)
	{
		attributeName = "pic" + (m+1);
		PsgAttrName = "id"+(i+1);
		makearef(pRef2,GameInterface.PASSENGERSLIST.(attributeName));

		_curCharIdx = sti(pRef.(PsgAttrName));

		if (_curCharIdx!=-1)
		{
			ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
			if (!ok && GetRemovable(&characters[_curCharIdx]))
			{
                // совместители должностей -->
                howWork = 1;
                if (CheckCharacterPerk(&characters[_curCharIdx], "ByWorker"))
                {
                    howWork = 2;
                }
                if (CheckCharacterPerk(&characters[_curCharIdx], "ByWorker2"))
                {
                    howWork = 3;
                }
                ok = !CheckAttribute(&characters[_curCharIdx], "isbusy") || sti(characters[_curCharIdx].isbusy) < howWork;
                PsgAttrName = GetOfficerTypeByNum(nCurScrollNum);
				// совместители должностей <--
				if (ok && !CheckAttribute(&characters[_curCharIdx], PsgAttrName))
				{
					GameInterface.PASSENGERSLIST.(attributeName).character = _curCharIdx;
					GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
					GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
					m++;
				}
			}
		}
	}
	GameInterface.PASSENGERSLIST.ListSize = m + 2; // не знаю зачем, но для совместимости с "было"
}

void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	GameInterface.strings.CharJob = "";
	SetCurrentNode("CHARACTERS_SCROLL");
}

void OfficerChange()
{
    string attributeName = "pic" + (nCurScrollNum+1);
	
	if(bGlobalTutor && nCurScrollNum < 7) return;

	if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		xi_refCharacter = &characters[iCharacter];
		if (isOfficerInShip(xi_refCharacter, true) && xi_refCharacter.id != pchar.id)
		{
			XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
			XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
			XI_WindowDisable("MAIN_WINDOW", true);

			SetCurrentNode("REMOVE_CANCEL_OFFICER");
		}
	}
	else
	{
	    if (nCurScrollNum <= 9 && nCurScrollNum != 0)
		{
			FillPassengerScroll();
		    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
		    SetCurrentNode("PASSENGERSLIST");
			ProcessFrame();
			SetOfficersSkills();

			XI_WindowShow("OFFICERS_WINDOW", true);
			XI_WindowDisable("OFFICERS_WINDOW", false);
			XI_WindowDisable("MAIN_WINDOW", true);
		}
	}
}

void AcceptAddOfficer()
{
	int iCurrentNode = nCurScrollNum;
	bool bNeedFollow = false;
	bool bOk;
	ref rChar;
	
	string attributeName2 = "pic"+(nCurScrollOfficerNum+1);

    if (checkAttribute(GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
    {
		int iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);

		if (!CheckAttribute(&characters[iChar], "isbusy"))
		{
			characters[iChar].isbusy = 1;
		}
		else
		{
		    characters[iChar].isbusy = sti(characters[iChar].isbusy) + 1; // совместители
		}
		bOk = (Characters[iChar].location != pchar.location);  // ниже локация перебивается на ГГ
		switch (nCurScrollNum)
		{
			case 1:
				pchar.Fellows.Passengers.navigator = iChar;
			break;

			case 2:
				pchar.Fellows.Passengers.boatswain = iChar;
			break;

			case 3:
				pchar.Fellows.Passengers.cannoner = iChar;
			break;

			case 4:
				pchar.Fellows.Passengers.doctor = iChar;
			break;

			case 5:
				pchar.Fellows.Passengers.treasurer = iChar;
			break;

			case 6:
				pchar.Fellows.Passengers.carpenter = iChar;
			break;

			case 7:
				SetOfficersIndex(pchar, 1, iChar);
				bNeedFollow = true;
			break;

			case 8:
				SetOfficersIndex(pchar, 2, iChar);
				bNeedFollow = true;
			break;

			case 9:
				SetOfficersIndex(pchar, 3, iChar);
				bNeedFollow = true;
			break;
		}
        attributeName2 = GetOfficerTypeByNum(nCurScrollNum);
    	characters[iChar].(attributeName2) = true; // совместитель дожности
    	//SetCharacterTask_FollowCharacter(&Characters[iChar], PChar);
    	if (!IsEntity(&worldMap) && !bSeaActive && bNeedFollow) // только для офов
    	{
	    	if (IsEntity(&loadedLocation) && loadedLocation.type == "tavern")
	    	{   //  пусть всегда будут появляться
	    	    PlaceCharacter(&Characters[iChar], "goto", "random_must_be_near");
	    	}
			else // запрет обмена с офами, где их нет
			{
				ref loc = &Locations[FindLocation(pchar.location)];
				aref grp;
				makearef(grp, loc.locators.officers);
				int num = GetAttributesNum(grp);
				if (num < 1 || CheckAttribute(loc, "DisableOfficers")) ChangeCharacterAddressGroup(&Characters[iChar], "none", "", "");
			}
	    	LAi_tmpl_SetFollow(&Characters[iChar], GetMainCharacter(), -1.0);
    	}
		FillCharactersScrollEx(true);
		GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
		
		rChar = &characters[iChar];
		Event("eSwitchPerks", "l", sti(rChar.index));
	}
	ExitOfficerMenu();
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	ProcessFrame();
	SetVariable();
	SetControlsTabMode(currentTab+1);
}

void ExitRemoveOfficerMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("CHARACTERS_SCROLL");
}

void AcceptRemoveOfficer()
{
    int iCurrentNode = nCurScrollNum;
	string attributeName2 = "pic"+(nCurScrollNum+1);

	int iChar = sti(GameInterface.CHARACTERS_SCROLL.(attributeName2).character);

    characters[iChar].isbusy = sti(characters[iChar].isbusy) - 1; // совместители
	if (sti(characters[iChar].isbusy) <= 0)
	{
		DeleteAttribute(&characters[iChar], "isbusy");
	}

	switch (nCurScrollNum)
	{
		case 1:
			pchar.Fellows.Passengers.navigator = -1;
		break;

		case 2:
			pchar.Fellows.Passengers.boatswain = -1;
		break;

		case 3:
			pchar.Fellows.Passengers.cannoner = -1;
		break;

		case 4:
			pchar.Fellows.Passengers.doctor = -1;
		break;

		case 5:
			pchar.Fellows.Passengers.treasurer = -1;
		break;

		case 6:
			pchar.Fellows.Passengers.carpenter = -1;
		break;

		case 7:
			RemoveOfficersIndex(pchar, GetOfficersIndex(pchar, 1));
		break;

		case 8:
			RemoveOfficersIndex(pchar, GetOfficersIndex(pchar, 2));
		break;

		case 9:
			RemoveOfficersIndex(pchar, GetOfficersIndex(pchar, 3));
		break;
	}
    attributeName2 = GetOfficerTypeByNum(nCurScrollNum);
    DeleteAttribute(&characters[iChar], attributeName2); // совместитель дожности
    
	FillCharactersScrollEx(true);
	GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
	ExitRemoveOfficerMenu();
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	SetVariable();
	SetControlsTabMode(currentTab+1);
}

// items --->
void FillItemsTable(int _mode) // 1 - все 2 - снаряжение 3 - эликсиры 4 - амулеты 5 - прочее
{
	int n, i;
	string row;
	string sGood;
	string groupID;
	string itemType;
	int  idLngFile;
	bool ok, ok0, ok1, ok2, ok3, ok4, ok5;
	bool slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8;
	aref rootItems, arItem;
	aref  curItem;

	GameInterface.TABLE_ITEMS.hr.td1.str = XI_ConvertString("ItemsName");
	GameInterface.TABLE_ITEMS.hr.td1.textoffset = "40,0";
	GameInterface.TABLE_ITEMS.hr.td2.str = XI_ConvertString("ItemsWeight");
	GameInterface.TABLE_ITEMS.hr.td2.line_space_modifier = 0.60;
	GameInterface.TABLE_ITEMS.hr.td3.str = XI_ConvertString("ItemsQty");
	GameInterface.TABLE_ITEMS.hr.td4.str = XI_ConvertString("ItemsWeightAll");
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_ITEMS", false, true, false);
	
	// Заполним вещами от нас
	makearef(rootItems, xi_refCharacter.Items);
    int num = GetAttributesNum(rootItems);
    for (i=0; i<num; i++)
    {
		curItem = GetAttributeN(rootItems, i);
		groupID = "";
		itemType = "";

		if (Items_FindItem(GetAttributeName(curItem), &arItem) >= 0)
		{
			row = "tr" + n;
			sGood = arItem.id;
			if(CheckAttribute(arItem,"groupID")) 	groupID 	= arItem.groupID;
			if(CheckAttribute(arItem,"itemType")) 	itemType	= arItem.itemType;

			ok = (groupID == BLADE_ITEM_TYPE) || 	// холодное оружие
				 (groupID == GUN_ITEM_TYPE)	||		// огнестрел
				 (groupID == MUSKET_ITEM_TYPE)	||		// мушкет
                 (groupID == SPYGLASS_ITEM_TYPE) || // трубы
				 (groupID == CIRASS_ITEM_TYPE) ||   // костюмы и доспехи
				 (groupID == TOOL_ITEM_TYPE) ||     // навигационные приборы котороые можно экипировать в спецслот
				 (groupID == LANTERN_ITEM_TYPE) ||  // фонарь
				 (groupID == HAT_ITEM_TYPE) ||  	// шляпы
				 (groupID == AMMO_ITEM_TYPE);		// расходники для огнестрела
			
			ok1 = (groupID == PATENT_ITEM_TYPE)	||	// патенты
                  (groupID == MAPS_ITEM_TYPE) ||	// карты
                  (groupID == SPECIAL_ITEM_TYPE) || // спецпредметы
				  (itemType == "QUESTITEMS"); 	    // квестовые предметы			  
			
			ok2	= (groupID == ITEM_SLOT_TYPE) && (itemType == "ARTEFACT"); // артефакты
			
			ok3 = (groupID == TALISMAN_ITEM_TYPE) || ok2; // талисманы
			
			ok4 = (groupID == MAPS_ITEM_TYPE);	// карты
				
			ok5 = (sGood == "map_sharp_full") || // особенные карты
				(sGood == "map_half_blaze") || 
				(sGood == "map_half_beatriss") || 
				(sGood == "skinmap") || 
				(sGood == "mark_map") || 
				(sGood == "Map_Best") ||
				(sGood == "mapQuest") ||
				(sGood == "mapEnrico") ||
				(sGood == "LadyBeth_Map") ||
				(sGood == "map_full") ||
				(sGood == "map_part1") ||
				(sGood == "map_part2");

			slot1 = (groupID == BLADE_ITEM_TYPE); // сабли
			slot2 = (groupID == GUN_ITEM_TYPE); // пистолеты
			slot3 = (groupID == SPYGLASS_ITEM_TYPE); // трубы
			slot4 = (groupID == CIRASS_ITEM_TYPE); // кирасы
			slot5 = (groupID == MUSKET_ITEM_TYPE); // мушкеты
			slot6 = (groupID == TALISMAN_ITEM_TYPE); // талисманы
			slot7 = (groupID == TOOL_ITEM_TYPE); // инструменты
			slot8 = (groupID == ITEM_SLOT_TYPE); // только амулеты
                 
			if(_mode == 1 && groupID == MAPS_ITEM_TYPE)	continue;
			if(_mode == 2 && !ok)  continue;	 
			if(_mode == 3)
			{
				if(!HasSubStr(sGood, "potion"))  continue;
			}
			if(_mode == 4 && !ok3) continue;	
			if(_mode == 5) 
			{
				if(!ok1 && !ok5) continue;
				if(GetCharacterFreeItem(xi_refCharacter, arItem.id) < 1 && arItem.id != "MapsAtlas") continue;
				if(HasSubStr(sGood, "potion"))  continue;
			}			
			if(_mode == 6 && !slot1) continue;//сабли
			if(_mode == 7)//пистолеты
			{
				if(!slot2) continue;
				if(HasSubStr(sGood, "mushket"))  continue;
			}
			if(_mode == 8 && !slot3) continue;//трубы
			if(_mode == 9 && !slot4) continue;//кирасы
			if(_mode == 10)//мушкеты
			{
				if(!slot5) continue;
				if(HasSubStr(sGood, "pistol"))  continue;
				if(HasSubStr(sGood, "howdah"))  continue;
			}
			if(_mode == 11 && !slot6) continue;//талисманы
			if(_mode == 12 && !slot7) continue;//инструменты
			if(_mode == 13 && !slot8) continue;//слоты амулетов	
			if(_mode == 14 && !slot8) continue;//слоты амулетов
			if(_mode == 15 && !slot8) continue;//слоты амулетов
			if(_mode == 16 && groupID != AMMO_ITEM_TYPE) continue;//боеприпасы
			if(_mode == 17 && groupID != LANTERN_ITEM_TYPE) continue;//фонарь
			if(_mode == 18 && groupID != HAT_ITEM_TYPE) continue;//шляпы
			if (GetCharacterItem(xi_refCharacter, sGood) > 0)
			{		
				GameInterface.TABLE_ITEMS.(row).index = GetItemIndex(arItem.id);
				
				GameInterface.TABLE_ITEMS.(row).td1.icon.group = arItem.picTexture;
				GameInterface.TABLE_ITEMS.(row).td1.icon.image = "itm" + arItem.picIndex;
				GameInterface.TABLE_ITEMS.(row).td1.icon.offset = "0, 0";
				GameInterface.TABLE_ITEMS.(row).td1.icon.width = 50;
				GameInterface.TABLE_ITEMS.(row).td1.icon.height = 50;
				GameInterface.TABLE_ITEMS.(row).td1.textoffset = "40,0";
				GameInterface.TABLE_ITEMS.(row).td1.line_space_modifier = 0.7;
				GameInterface.TABLE_ITEMS.(row).td1.str = LanguageConvertString(idLngFile, arItem.name);
				
				GameInterface.TABLE_ITEMS.(row).td2.str   = FloatToString(stf(arItem.Weight), 1);
				if(groupID == MAPS_ITEM_TYPE)
					GameInterface.TABLE_ITEMS.(row).td3.str   = GetCharacterFreeItem(xi_refCharacter, sGood);
				else
					GameInterface.TABLE_ITEMS.(row).td3.str   = GetCharacterItem(xi_refCharacter, sGood);
				GameInterface.TABLE_ITEMS.(row).td4.str   = FloatToString(stf(arItem.Weight) * sti(GameInterface.TABLE_ITEMS.(row).td3.str), 1);
				n++;
			}
		}
    }
    
	Table_UpdateWindow("TABLE_ITEMS");
	LanguageCloseFile(idLngFile);
	if (_mode == 1)
	{
		FillItemsSelected();
	}
}

void FillItemsSelected() 
{
    aref arEquip, curItem;
	string sItem, sSlot, remainTime;
    int i, picIndex, num, idx;
	ref rAmmoGunItem;
	int nColor1 = argb(155,128,128,128);
	int nColor2 = argb(0,128,128,128);
	int sColor1 = nColor1;
	int sColor2 = nColor1;
	int sColor3 = nColor1;
	int sColor4 = nColor1;
	int sColor5 = nColor1;
	int sColor6 = nColor1;
	int sColor7 = nColor1;
	int sColor8 = nColor1;
	int sColor9 = nColor1;
	int sColor10 = nColor1;
	
	// Скроем по умолчанию
	SetNodeUsing("EMPTY_ITEMS", true);
	SetNodeUsing("ITEM_1", false);
	SetNodeUsing("ITEM_2", false);
	SetNodeUsing("ITEM_3", false);
	SetNodeUsing("ITEM_4", false);
	SetNodeUsing("ITEM_5", false);
	SetNodeUsing("ITEM_6", false);
	SetNodeUsing("ITEM_7", false);
	SetNodeUsing("ITEM_2B", false);
	SetNodeUsing("ITEM_5B", false);
	SetNodeUsing("ITEM_4L", false);
	SetNodeUsing("ITEM_11", false);
	SetNodeUsing("TABBTNSLOT_2B", false);
	SetNodeUsing("TABBTNSLOT_5B", false);
	SetNodeUsing("TABBTNSLOT_4L", false);
	
	SetNodeUsing("SLOT_ITEM_1", false);
	SetNodeUsing("SLOT_ITEM_2", false);
	SetNodeUsing("SLOT_ITEM_3", false);
	
	SetNodeUsing("SLOT1_TEXT", false);
	SetNodeUsing("SLOT2_TEXT", false);
	SetNodeUsing("SLOT3_TEXT", false);
	SetNodeUsing("SLOT6_TEXT", false);
	
	SetNodeUsing("SLOT_PIC_1", false);
	SetNodeUsing("SLOT_PIC_2", false);
	SetNodeUsing("SLOT_PIC_3", false);
	SetNodeUsing("SLOT_PIC_6", false);

    makearef(arEquip, xi_refCharacter.equip);
    num = GetAttributesNum(arEquip);
    for (i=0; i<num; i++)
	{
		sItem = GetAttributeValue(GetAttributeN(arEquip,i));
        if(sItem == "") continue;
        idx = FindItem(sItem);
        if (idx >= 0) makearef(curItem, Items[idx]);
        else continue;

        switch (curItem.groupID) 
        {
            case BLADE_ITEM_TYPE:
                SetNewGroupPicture("ITEM_1", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("ITEM_1" , true);
                sColor1 = nColor2;
            break;
            case GUN_ITEM_TYPE:
                if (CheckAttribute(xi_refCharacter,"chr_ai.gun.bullet"))
                {
                    rAmmoGunItem = ItemsFromID(xi_refCharacter.chr_ai.gun.bullet);
                    SetNewGroupPicture("ITEM_2B", rAmmoGunItem.picTexture, "itm" + rAmmoGunItem.picIndex);
                    if (rAmmoGunItem.id != GetAmmoPortrait(GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE)))
                    {
                        SetNodeUsing("TABBTNSLOT_2B", true);
                        SetNodeUsing("ITEM_2B", true);
                    }
                }
                
                SetNewGroupPicture("ITEM_2", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("TABBTNSLOT_2B", true);
                SetNodeUsing("ITEM_2", true);
                sColor2 = nColor2;
            break;
            case MUSKET_ITEM_TYPE:
                if (CheckAttribute(xi_refCharacter,"chr_ai.musket.bullet"))
                {
                    rAmmogunItem = ItemsFromID(xi_refCharacter.chr_ai.musket.bullet);
                    SetNewGroupPicture("ITEM_5B", rAmmogunItem.picTexture, "itm" + rAmmogunItem.picIndex);
                    if (rAmmoGunItem.id != GetAmmoPortrait(GetCharacterEquipByGroup(xi_refCharacter, MUSKET_ITEM_TYPE)))
                    {
                        SetNodeUsing("TABBTNSLOT_5B", true);
                        SetNodeUsing("ITEM_5B", true);
                    }
                }
                SetNewGroupPicture("ITEM_5", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("TABBTNSLOT_5B", true);
                SetNodeUsing("ITEM_5", true);
                sColor5 = nColor2;
            break;
            case SPYGLASS_ITEM_TYPE:
                SetNewGroupPicture("ITEM_3", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("ITEM_3" , true);
                sColor3 = nColor2;
            break;
            case CIRASS_ITEM_TYPE:
                SetNewGroupPicture("ITEM_4", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("ITEM_4" , true);
                sColor4 = nColor2;
            break;
            case TALISMAN_ITEM_TYPE:
                SetNewGroupPicture("ITEM_6", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("ITEM_6" , true);
                sColor6 = nColor2;
                if (IsEquipCharacterByArtefact(xi_refCharacter, "talisman17"))
                {
                    ref Liber = ItemsFromID("talisman17");
                    int iQBonus = 0;
                    if(CheckAttribute(Liber, "QBonus"))
                    {
                        iQBonus = sti(Liber.QBonus);
                    }
                    picIndex = iQBonus*2; // у картинки 10 делений
                    SetNewGroupPicture("SLOT_PIC_6", "ITEMS_USE10", "items_use" + picIndex);
                    SetNodeUsing("SLOT_PIC_6", true);
                    SetFormatedText("SLOT6_TEXT", iQBonus +"/5");
                    SetNodeUsing("SLOT6_TEXT", true);
                }
                //TODO переписать в один метод (расставить предметам QBonus в квестах)
                if (IsEquipCharacterByArtefact(xi_refCharacter, "talisman18"))
                {
                    ref Articles = ItemsFromID("talisman18");
                    int QBonus = 0;
                    if(CheckAttribute(Articles, "QBonus"))
                    {
                        QBonus = sti(Articles.QBonus);
                    }
                    picIndex = QBonus;
                    SetNewGroupPicture("SLOT_PIC_6", "ITEMS_USE10", "items_use" + picIndex);
                    SetNodeUsing("SLOT_PIC_6", true);
                    SetFormatedText("SLOT6_TEXT", QBonus +"/10");
                    SetNodeUsing("SLOT6_TEXT", true);
                }
            break;
            case TOOL_ITEM_TYPE:
                SetNewGroupPicture("ITEM_7", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("ITEM_7" , true);
                sColor7 = nColor2;
            break;
            case LANTERN_ITEM_TYPE:
                SetNewGroupPicture("ITEM_4L", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("ITEM_4L", true);
                SetNodeUsing("TABBTNSLOT_4L", true);
            break;
            case HAT_ITEM_TYPE:
                SetNewGroupPicture("ITEM_11", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("ITEM_11", true);
                SetNodeUsing("TABBTNSLOT_11", true);
            break;
        }
	}

    makearef(arEquip, xi_refCharacter.equip_item);
    num = GetAttributesNum(arEquip);
    for (i=0; i<num; i++)
	{
		sItem = GetAttributeValue(GetAttributeN(arEquip,i));
        if(sItem == "") continue;
        idx = FindItem(sItem);
        if (idx >= 0) makearef(curItem, Items[idx]);
        else continue;

        sSlot = GetCharacterEquipSlot(xi_refCharacter, sItem);
        switch (sSlot)
        {
            case ITEM_SLOT1_TYPE:
                SetNewGroupPicture("SLOT_ITEM_1", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("SLOT_ITEM_1" , true);
                sColor8 = nColor2;
                remainTime = GetCharacterSlotRemainTime(xi_refCharacter, ITEM_SLOT1_TYPE);
                if(CheckAttribute(curItem,"time") && curItem.time > -1 && remainTime != "")
                {
                    SetFormatedText("SLOT1_TEXT", remainTime + "/" + curItem.time);
                    SetNodeUsing("SLOT1_TEXT", true);	
                    SetVAligmentFormatedText("SLOT1_TEXT");	
                }	

                picIndex = GetCharacterEquipSlotUsedPicture(xi_refCharacter, ITEM_SLOT1_TYPE);
                if(picIndex > 0) 
                {
                    SetNewGroupPicture("SLOT_PIC_1", "ITEMS_USE", "items_use" + picIndex);
                    SetNodeUsing("SLOT_PIC_1", true);
                }
            break;
            case ITEM_SLOT2_TYPE:
                SetNewGroupPicture("SLOT_ITEM_2", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("SLOT_ITEM_2" , true);
                sColor9 = nColor2;
                remainTime = GetCharacterSlotRemainTime(xi_refCharacter, ITEM_SLOT2_TYPE);
                if(CheckAttribute(curItem,"time") && curItem.time > -1 && remainTime != "")
                {
                    SetFormatedText("SLOT2_TEXT", remainTime + "/" + curItem.time);
                    SetNodeUsing("SLOT2_TEXT", true);	
                    SetVAligmentFormatedText("SLOT2_TEXT");		
                }	
                
                picIndex = GetCharacterEquipSlotUsedPicture(xi_refCharacter, ITEM_SLOT2_TYPE);
                if(picIndex > 0) 
                {
                    SetNewGroupPicture("SLOT_PIC_2", "ITEMS_USE", "items_use" + picIndex);
                    SetNodeUsing("SLOT_PIC_2", true);	
                }
            break;
            case ITEM_SLOT3_TYPE:
                SetNewGroupPicture("SLOT_ITEM_3", curItem.picTexture, "itm" + curItem.picIndex);
                SetNodeUsing("SLOT_ITEM_3" , true);
                sColor10 = nColor2;
                remainTime = GetCharacterSlotRemainTime(xi_refCharacter, ITEM_SLOT3_TYPE);
                if(CheckAttribute(curItem,"time") && curItem.time > -1 && remainTime != "")
                {
                    SetFormatedText("SLOT3_TEXT", remainTime + "/" + curItem.time);
                    SetNodeUsing("SLOT3_TEXT", true);	
                    SetVAligmentFormatedText("SLOT3_TEXT");		
                }	
                
                picIndex = GetCharacterEquipSlotUsedPicture(xi_refCharacter, ITEM_SLOT3_TYPE);
                if(picIndex > 0) 
                {
                    SetNewGroupPicture("SLOT_PIC_3", "ITEMS_USE", "items_use" + picIndex);
                    SetNodeUsing("SLOT_PIC_3", true);	
                }
            break;
        }
	}

    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 0, sColor1);
    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 1, sColor2);
    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 2, sColor3);
    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 3, sColor4);
    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 4, sColor5);
    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 5, sColor6);
    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 6, sColor7);
    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 7, sColor8);
    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 8, sColor9);
    SendMessage( &GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EMPTY_ITEMS", 3, 9, sColor10);
}

void ShowBoxMove()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) // фильтр пустых строк
	{
		if(iCharQty ==0 || bQuestItem) // нельзя выкинуть недоступные предметы
		{
			if(iCharQty ==0) SetFormatedText("DROP_WARNING_TEXT", XI_ConvertString("DropErrore")); // надетые
			if(bQuestItem) SetFormatedText("DROP_WARNING_TEXT", XI_ConvertString("DropErrorq")); // квестовые
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"DROP_WARNING_TEXT", 5);
			SetNodeUsing("DROP_ITEM_FRAME",true);
			PostEvent("WarningHide",1000);
			return;
		}
		if(iCharQty <2)
		{
			XI_WindowDisable("QTY_WINDOW_S", false);
			XI_WindowShow("QTY_WINDOW_S", true);
			XI_WindowDisable("MAIN_WINDOW", true);
			SetCurrentNode("QTY_CANCEL_BUTTON_S");
			GameInterface.qty_edit.str = 1;
			ChangeQTY_EDIT();
		}
		else
		{

			XI_WindowDisable("QTY_WINDOW", false);
			XI_WindowShow("QTY_WINDOW", true);
			XI_WindowDisable("MAIN_WINDOW", true);
			SetCurrentNode("QTY_CANCEL_BUTTON");
			GameInterface.qty_edit.str = 0;
			ChangeQTY_EDIT();
		}
	}
}

void GoodsExitCancel()
{
	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	XI_WindowDisable("QTY_WINDOW_S", true);
	XI_WindowShow("QTY_WINDOW_S", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode("TABLE_ITEMS");
	// вернём старые значения веса
	SetFormatedText("Weight", FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / " + GetMaxItemsWeight(xi_refCharacter));
	Table_UpdateWindow("TABLE_OTHER");
}

void TransactionOK()
{
	ref arItm = &Items[iGoodIndex];
	int iDropQuantity;
	iDropQuantity = sti(GameInterface.qty_edit.str);
	if(iDropQuantity <= 0) return;
	if(iDropQuantity > 0) 
	{
		RemoveItems(xi_refCharacter, arItm.id, iDropQuantity);
		// WaitDate("", 0, 0, 0, 0, 1);
	}
	GoodsExitCancel();
	FillItemsTable(currentTab+1);
	UpdateItemInfo();
	Log_Info(XI_ConvertString("DropItemLog") + GetConvertStr(arItm.name, "ItemsDescribe.txt") + " " + iDropQuantity + " " +  XI_ConvertString("units"));
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	SetSelectable("QTY_OK_BUTTON", true);
	float fCurWeight, fItemsWeight;
	ref arItm = &Items[iGoodIndex];
	ref rItem = ItemsFromID(arItm.id);
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	
	if (sti(GameInterface.qty_edit.str) <= 0)
	{
		GameInterface.qty_edit.str = 0;
		SetSelectable("QTY_OK_BUTTON", false);
	}	
	if (sti(GameInterface.qty_edit.str) == 1)
	{
		GameInterface.qty_edit.str = 1;
	}	
	// проверка на доступное кол-во -->
    if (sti(GameInterface.qty_edit.str) > iCharQty)
    {
        GameInterface.qty_edit.str = iCharQty;
    }
	fItemsWeight = sti(GameInterface.qty_edit.str)*stf(rItem.Weight);
	fCurWeight = GetItemsWeight(xi_refCharacter) - fItemsWeight;
	string sText = FloatToString(fCurWeight, 1) + " / " + GetMaxItemsWeight(xi_refCharacter);
	SetFormatedText("WEIGHT", sText);
	Table_UpdateWindow("TABLE_OTHER");
}

void ADD_ALL_BUTTON()  // сбросить
{
	GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // вернуть
{
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);

	if(sti(GameInterface.qty_edit.str) < 0)
	{
		GameInterface.qty_edit.str = 0;
	}
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // выкинуть
{
	if(iCharQty >= 1)
	{
		GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
	}
	if(sti(GameInterface.qty_edit.str) > iCharQty)
	{
		GameInterface.qty_edit.str = iCharQty;
	}
	ChangeQTY_EDIT();
}

void REMOVE_ALL_BUTTON()  // выкинуть все
{
	GameInterface.qty_edit.str = iCharQty;
	ChangeQTY_EDIT();
}

void SetItemInfo(int iGoodIndex)
{
	ref arItm = &Items[iGoodIndex];
	string describeStr;
	iCharQty = GetCharacterFreeItem(xi_refCharacter, arItm.id);
	bQuestItem = IsQuestUsedItem(arItm.id);// квестовый
	SetNodeUsing("EQUIP_BUTTON", true);
	SetNodeUsing("OPENMAP_BUTTON", false);
	SetNodeUsing("ATLASADD_BUTTON", false);
	SetNodeUsing("LOADGUN_BUTTON", false);
	SetNodeUsing("LOADMUSKET_BUTTON", false);
		
	aref attr, arGrape;
	string sBullet;
	string sAttr;
	int i, n;
	int lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	if(CheckAttribute(arItm,"groupID") && arItm.groupID == GUN_ITEM_TYPE && IsEquipCharacterByItem(xi_refCharacter, arItm.id))
	{
		sBullet = LAi_GetCharacterBulletType(xi_refCharacter, "gun");
		if(IsBulletGrape(sBullet))
		{
			makearef(attr, arItm.type);
			n = GetAttributesNum(attr);
			for(i = 0; i < n; i++)
			{
				arGrape = GetAttributeN(attr, i);
				if(arGrape.bullet == sBullet)
					break;
			}
			describeStr += GetAssembledString( LanguageConvertString(lngFileID,"weapon grape parameters equipped"), arGrape) + newStr();
		}
		else
			describeStr = GetAssembledString(LanguageConvertString(lngFileID,"weapon gun parameters equipped"), arItm) + newStr();
		
		describeStr = describeStr + GetAssembledString(LanguageConvertString(lngFileID, Items[iGoodIndex].describe), arItm);
		SetFormatedText("INFO_TEXT", describeStr);

		LanguageCloseFile(lngFileID);
	}
	else
	{
		if(CheckAttribute(arItm,"groupID") && arItm.groupID == MUSKET_ITEM_TYPE && IsEquipCharacterByItem(xi_refCharacter, arItm.id))
		{
			sBullet = LAi_GetCharacterBulletType(xi_refCharacter, "musket");
			if(IsBulletGrape(sBullet))
			{
				makearef(attr, arItm.type);
				n = GetAttributesNum(attr);
				for(i = 0; i < n; i++)
				{
					arGrape = GetAttributeN(attr, i);
					if(arGrape.bullet == sBullet)
						break;
				}
				describeStr += GetAssembledString( LanguageConvertString(lngFileID,"weapon grape parameters equipped"), arGrape) + newStr();
			}
			else
				describeStr = GetAssembledString(LanguageConvertString(lngFileID,"mushket parameters equipped"), arItm) + newStr();		
			
			describeStr = describeStr + GetAssembledString(LanguageConvertString(lngFileID, Items[iGoodIndex].describe), arItm);
			if(CheckAttribute(arItm, "UpgradeStage"))
			{
				describeStr += newStr() + LanguageConvertString(lngFileID,"UpgradeStageInfo_" + arItm.id + "_" + sti(arItm.UpgradeStage));
			}
			SetFormatedText("INFO_TEXT", describeStr);

			LanguageCloseFile(lngFileID);
		}
		else
			SetFormatedText("INFO_TEXT", GetItemDescribe(iGoodIndex));
	}
	
	SetNewGroupPicture("INFO_PIC", Items[iGoodIndex].picTexture, "itm" + Items[iGoodIndex].picIndex);
	SetNodeUsing("INFO_TEXT", true);
	SetNodeUsing("INFO_PIC", true);
	
	if(arItm.ID == "map_bad" || arItm.ID == "map_normal" || arItm.ID == "map_best")
	{
		if(IsMainCharacter(xi_refCharacter))
		{
			SetNodeUsing("EQUIP_BUTTON", false);
			SetNodeUsing("OPENMAP_BUTTON", true);
			SetNodeUsing("ATLASADD_BUTTON", true);
			SetSelectable("ATLASADD_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
		}
		else
		{
			SetNodeUsing("EQUIP_BUTTON", true);
			SetNodeUsing("OPENMAP_BUTTON", false);
			SetNodeUsing("ATLASADD_BUTTON", false);
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
			SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
		}
	}
	else
	{
		if(CheckAttribute(arItm,"groupID") && arItm.groupID == AMMO_ITEM_TYPE)
		{
			SetNodeUsing("EQUIP_BUTTON", true);
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("LoadAnyGun"));
			if(arItm.groupID == AMMO_ITEM_TYPE
				&& arItm.ID != "GunPowder"
				&& GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE) !="" 
				&& GetCharacterEquipByGroup(xi_refCharacter, MUSKET_ITEM_TYPE) !="")
			{
				SetNodeUsing("EQUIP_BUTTON", false);
				SetNodeUsing("LOADGUN_BUTTON", true);
				SetNodeUsing("LOADMUSKET_BUTTON", true);
				SetSelectable("LOADGUN_BUTTON",true);
				SetSelectable("LOADMUSKET_BUTTON",true);
				if(!LAi_CanCharacterUseBullet(xi_refCharacter, GUN_ITEM_TYPE, arItm.ID)) SetSelectable("LOADGUN_BUTTON",false);
				if(!LAi_CanCharacterUseBullet(xi_refCharacter, MUSKET_ITEM_TYPE, arItm.ID)) SetSelectable("LOADMUSKET_BUTTON",false);
			}
		}
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
		SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
	}
	SetVAligmentFormatedText("INFO_TEXT");
}

void HideItemInfo()
{
	SetNodeUsing("INFO_TEXT", false);
	SetNodeUsing("INFO_PIC", false);
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetNodeUsing("EQUIP_BUTTON", false);
	SetNodeUsing("OPENMAP_BUTTON", false);
	SetNodeUsing("ATLASADD_BUTTON", false);
}

void UpdateItemInfo();
{
	if(CheckAttribute(GameInterface, "TABLE_ITEMS." + CurRow + ".index"))
	{
		iGoodIndex = sti(GameInterface.TABLE_ITEMS.(CurRow).index)
		SetItemInfo(iGoodIndex);
	}
	else HideItemInfo();
}

void HideItemSelect()
{
	SetNodeUsing("ITEM_SELECT_1", false);
	SetNodeUsing("ITEM_SELECT_2", false);
	SetNodeUsing("ITEM_SELECT_3", false);
	SetNodeUsing("ITEM_SELECT_4", false);
	SetNodeUsing("ITEM_SELECT_5", false);
	SetNodeUsing("ITEM_SELECT_6", false);
	SetNodeUsing("ITEM_SELECT_7", false);
	SetNodeUsing("ITEM_SELECT_8", false);
	SetNodeUsing("ITEM_SELECT_9", false);
	SetNodeUsing("ITEM_SELECT_10", false);
	SetNodeUsing("ITEM_SELECT_11", false);
	SetNewPicture("TABBTNSLOT_1", "");
	SetNewPicture("TABBTNSLOT_2", "");
	SetNewPicture("TABBTNSLOT_3", "");
	SetNewPicture("TABBTNSLOT_4", "");
	SetNewPicture("TABBTNSLOT_5", "");
	SetNewPicture("TABBTNSLOT_6", "");
	SetNewPicture("TABBTNSLOT_7", "");
	SetNewPicture("TABBTNSLOT_8", "");
	SetNewPicture("TABBTNSLOT_9", "");
	SetNewPicture("TABBTNSLOT_10", "");
	SetNewPicture("TABBTNSLOT_11", "");
}

bool ThisItemCanBeEquip(aref arItem)
{
	if( !CheckAttribute(arItem,"groupID") )
	{
		if(IsMainCharacter(xi_refCharacter) && LAi_GetCharacterHP(xi_refCharacter)<LAi_GetCharacterMaxHP(xi_refCharacter)) // неполное здоровье
		{
			if(arItem.id == "potion1" || arItem.id == "potion2" || arItem.id == "potion3" || arItem.id == "potion4" || 
			   arItem.id == "potion5" || arItem.id == "potion6" || arItem.id == "potionrum" || arItem.id == "potionwine") return true; // лечилки
		}
		return false;
	}
	if(!IsCanEquiping(xi_refCharacter, arItem.groupID))
	{
		return false;
	}	
	
	if(arItem.id == "MapsAtlas" && sti(xi_refCharacter.index) == sti(pchar.index)) 
	{
		if(IsMainCharacter(xi_refCharacter)) return true;
		return false;
	}

	// дешевая, обычная и отличная карты для ГГ
	if(arItem.ID == "map_bad" || arItem.ID == "map_normal" || arItem.ID == "map_best")
	{
		if(IsEquipCharacterByMap(xi_refCharacter, arItem.ID)) return false;
	}

    // нельзя собрать новую карту сокровищ, если текущий клад не найден
	if(arItem.ID == "map_part1" || arItem.ID == "map_part2")
	{
		if(GetCharacterItem(PChar, "map_full") > 0 && GetCharacterItem(PChar, "map_part1") > 0 && GetCharacterItem(PChar, "map_part2") > 0) return false;
	}

	// спецпредметы только для ГГ
	if (arItem.groupID == SPECIAL_ITEM_TYPE && !IsMainCharacter(xi_refCharacter)) 
	{
		return false;
	}
	if(HasSubStr(arItem.id, "FirearmStockPart") && !CanUpgradeMusketSP(xi_refCharacter, arItem))
	{
		return false;
	}
	if (arItem.groupID == AMMO_ITEM_TYPE) 
	{
		if (arItem.ID == "GunPowder") return false;
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("LoadAnyGun"));
		if(GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE) != "" && !LAi_CanCharacterUseBullet(xi_refCharacter, GUN_ITEM_TYPE, arItem.ID)) return false;
		if(GetCharacterEquipByGroup(xi_refCharacter, MUSKET_ITEM_TYPE) != "" && !LAi_CanCharacterUseBullet(xi_refCharacter, MUSKET_ITEM_TYPE, arItem.ID)) return false;
	}
	// фонарь только для ГГ
	if (arItem.groupID == LANTERN_ITEM_TYPE && !IsMainCharacter(xi_refCharacter)) 
	{
		return false;
	}
	// шляпы только для персонажей с локатором hat
	if(arItem.groupID == HAT_ITEM_TYPE)
	{
		if (!HasHatLocator(xi_refCharacter) && !CanEquipHatDirectly(xi_refCharacter)) return false;
	}

	/* if (xi_refCharacter.id == "Mary" && arItem.groupID == BLADE_ITEM_TYPE)
	{
		return false; // чтобы нарвал не отбирали
	}
	if (xi_refCharacter.id == "Helena" && IsEquipCharacterByItem(xi_refCharacter, "pirate_cutlass") && arItem.groupID == BLADE_ITEM_TYPE)
	{
		return false;
	}
	if (xi_refCharacter.id == "Danielle" && arItem.groupID == BLADE_ITEM_TYPE)
	{
		return false; // чтобы саблю не отбирали лесник - пусть сама рашает что ей лучше то и выбирает. как Мери. 	
	} */
	if (xi_refCharacter.id == "Irons" && IsEquipCharacterByItem(xi_refCharacter, "blade_42") && arItem.groupID == BLADE_ITEM_TYPE && CheckAttribute(pchar, "questTemp.IronsItemsBlock"))
	{
		return false;
	}
	if (xi_refCharacter.id == "Irons" && IsEquipCharacterByItem(xi_refCharacter, "cirass10") && arItem.groupID == CIRASS_ITEM_TYPE && CheckAttribute(pchar, "questTemp.IronsItemsBlock"))
	{
		return false;
	}
	
	if (arItem.groupID == GUN_ITEM_TYPE) 
	{
		if (!CheckAttribute(arItem,"chargeQ") )
		{
			return false;
		}
		int chrgQ = sti(arItem.chargeQ);

		if (chrgQ >= 2 && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional") )
		{
			if(arItem.id == "pistol9" || arItem.id == "pistol6") return true;
			return false;
		}
		
		// Нельзя экипировать мушкет в непредназначенных для этого локациях (Таверна)
		if(HasSubStr(arItem.id, "mushket") && !CanEquipMushketOnLocation(PChar.Location))
		{
			if(!HasSubStr(xi_refCharacter.model, "Irons")) return false;
		}
	}
	
	if (arItem.groupID == MUSKET_ITEM_TYPE) 
	{
		bool bCanMush = IsMainCharacter(xi_refCharacter) || CheckAttribute(xi_refCharacter, "CanTakeMushket");
		if (HasSubStr(arItem.id, "mushket") && !bCanMush) 
		{
			return false;
		}	
		if (!CheckAttribute(arItem,"chargeQ") )
		{
			return false;
		}
		int chrgQm = sti(arItem.chargeQ);

		if (chrgQm >= 2 && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional") )
		{
			if(arItem.id == "pistol9" || arItem.id == "pistol6") return true;
			return false;
		}
				
		// Для мушкетов нужен соответствующий перк
		if(HasSubStr(arItem.id, "mushket") && !IsCharacterPerkOn(xi_refCharacter,"Gunman"))
		{
			return false;
		}
		
		// Нельзя экипировать мушкет в непредназначенных для этого локациях (Таверна)
		if(HasSubStr(arItem.id, "mushket") && !CanEquipMushketOnLocation(PChar.Location))
		{
			if(!HasSubStr(xi_refCharacter.model, "Irons")) return false;
		}
	}
    
	if (arItem.groupID == ITEM_SLOT_TYPE)
	{
		if (IsEquipCharacterByArtefact(xi_refCharacter, arItem.id))
		{
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
			return true;
		}
		else
		{
			if(GetCharacterFreeSlot(xi_refCharacter) != SLOT_NOT_USED && IsCanArtefactBeEquipped(xi_refCharacter, arItem.id))
			{
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
				return true;
			}
			return false;
		}
	}	
	
    if (IsEquipCharacterByItem(xi_refCharacter, arItem.id))
	{		
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
		// if(arItem.groupID == BLADE_ITEM_TYPE || arItem.groupID == SPYGLASS_ITEM_TYPE || arItem.groupID == PATENT_ITEM_TYPE)
		if(arItem.groupID == BLADE_ITEM_TYPE || arItem.groupID == PATENT_ITEM_TYPE)
		{
			return false; // не запрещаем снимать трубу
		}		
		//Jason: под водой ничего нельзя снимать
		if (xi_refCharacter.location == "underwater")
		{
		    return false;
	    }
		//Jason: запрет снятия кирасы
		if (arItem.groupID == CIRASS_ITEM_TYPE && CheckAttribute(xi_refCharacter, "GenQuest.CirassExchangeDisable"))
	    {
		    return false;
	    }
	}
	else
	{ // Jason: убираем влияние перка кирасы - кирасу носим без перка
		/*if (arItem.groupID == CIRASS_ITEM_TYPE && !IsCharacterPerkOn(xi_refCharacter,"Ciras") && arItem.Clothes == false)
	    {	
		    return false;
	    }*/
		//Jason: под водой ничего нельзя одевать
		if (xi_refCharacter.location == "underwater")
	    {
		    return false;
	    }
		//Jason: запрет одевания кирасы
		if (arItem.groupID == CIRASS_ITEM_TYPE && CheckAttribute(xi_refCharacter, "GenQuest.CirassExchangeDisable"))
	    {
		    return false;
	    }
		if (arItem.groupID == AMMO_ITEM_TYPE) SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("LoadAnyGun"));
		else SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	}
	
	if (IsMainCharacter(xi_refCharacter) || CheckAttribute(xi_refCharacter, "CanTakeMushket"))
	{
		if(arItem.ID == "underwater" && IsMusketer(xi_refCharacter))
		{
			return false;
		}
	}
	
	/*if (CheckAttribute(xi_refCharacter, "CanTakeMushket"))
	{
		if(CheckAttribute(xi_refCharacter, "IsMushketer"))
		{
			if(arItem.ID == xi_refCharacter.IsMushketer.MushketID)
			{
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
				return true;
			}
			if(arItem.groupID == BLADE_ITEM_TYPE || arItem.groupID == SPYGLASS_ITEM_TYPE || arItem.groupID == GUN_ITEM_TYPE || arItem.groupID == CIRASS_ITEM_TYPE)
			{
				return false;
			}
		}
	}*/
	
	return true;
}

void AtlasAddPress()
{
	iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	string totalInfo;
	int  i;

	if (CheckAttribute(itmRef, "ID"))
	{
		if(itmRef.ID == "map_bad" || itmRef.ID == "map_normal" || itmRef.ID == "map_best")
		{
			CheckMapForEquipped(pchar,itmRef.ID);
		}
	}
	SetItemInfo(iGoodIndex);
	FillItemsTable(currentTab+1);
}

void EquipPress()
{
	iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	string totalInfo;
	int  i;
	
	if (CheckAttribute(itmRef, "groupID"))
	{
		string itmGroup = itmRef.groupID;
		if (itmGroup == MAPS_ITEM_TYPE)
		{

			// Warship. Отличная карта, у неё отдельный интерфейс
			// if(itmRef.ID == "Map_Best")
			// {
				// PChar.ShowBestMap = true; // Флаг, что смотрим из интерфейса придметов
				// IDoExit(RC_INTERFACE_BEST_MAP);
				// return;
			// }
			// Ugeen --> интерфейс атласа карт
			if(itmRef.ID == "MapsAtlas") // взяли атлас карт
			{
				PChar.ShowMapsAtlas = true; // Флаг, что смотрим из интерфейса предметов
				IDoExit(RC_INTERFACE_MAPVIEW);
				return;
			}
			// Ugeen --> специальная квестовая карта
			if(itmRef.id == "mapQuest")
			{
				totalInfo = GenQuest_GetQuestTreasureMapDescription(itmRef);
				SetNewPicture("MAP_PICTURE", "interfaces\maps\treasure map.tga");
				SetFormatedText("MAP_TEXT", totalInfo);
				SetVAligmentFormatedText("MAP_TEXT");
				ShowMapWindow();
				return;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if(itmRef.id == "mapEnrico")
			{
				totalInfo = XI_ConvertString("mapEnrico");
				SetNewPicture("MAP_PICTURE", "interfaces\maps\treasure map.tga");
				SetFormatedText("MAP_TEXT", totalInfo);
				SetVAligmentFormatedText("MAP_TEXT");
				ShowMapWindow();
				return;
			}
			if(itmRef.id == "LadyBeth_Map")
			{
					if(!CheckAttribute(itmRef, "Plantation"))
					{
						// начинается этап Барбадос
						SetFunctionLocationCondition("LadyBeth_Barbados_Elizabeth_1", "Bridgetown_Plantation_Sp1", false);
						itmRef.Plantation = true;
					}
					totalInfo = XI_ConvertString("LadyBeth_Map");
					SetNewPicture("MAP_PICTURE", "interfaces\maps\treasure map.tga");
					SetFormatedText("MAP_TEXT", totalInfo);
					SetVAligmentFormatedText("MAP_TEXT");
					ShowMapWindow();
				return;
			}
            if (itmRef.id == "map_full" || itmRef.id == "map_part1" || itmRef.id == "map_part2")
            {// клады
            	SetNewPicture("MAP_PICTURE", "interfaces\maps\treasure map2.tga");
            	if (itmRef.id != "map_full" && GetCharacterItem(pchar, "map_part1") > 0 && GetCharacterItem(pchar, "map_part2") > 0)
			    {
                    // Тут применяем логику двух кусков, из них одна карта
			        TakeNItems(xi_refCharacter, "map_part1", -1);
			        TakeNItems(xi_refCharacter, "map_part2", -1);
			        TakeNItems(pchar, "map_full",   1);
			        itmRef = &Items[FindItem("map_full")];
			        pchar.GenQuest.TreasureBuild = true;
			        FillMapForTreasure(itmRef);
			        SetVariable();
			    }
			    if (itmRef.mapType == "Full")
			    {
		            if (CheckAttribute(itmRef, "MapTypeIdx") && (sti(itmRef.MapTypeIdx) == -1))
				    {
                        SetFormatedText("MAP_TEXT", GetConvertStr("type_fake", "MapDescribe.txt"));
					    DeleteAttribute(itmRef, "MapIslId");
					    TakeNItems(GetMainCharacter(), "map_full", -1);
				    }
				    else
				    {
				        if (!CheckAttribute(itmRef, "MapIslId"))
				        {
				            FillMapForTreasure(itmRef); //заполним если смотрим карту из сундука
				        }
                        //totalInfo = GetConvertStr(itmRef.MapIslId, "LocLables.txt");
                        i = FindLocation(itmRef.MapLocId);  // ищем ареал
						if (i != -1 && locations[i].islandId != "Mein")
                        {
                            totalInfo = GetConvertStr(locations[i].islandId, "LocLables.txt");
                            totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_isl", "MapDescribe.txt") + " " + totalInfo;
                        }
                        else
                        {
                            totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_mein", "MapDescribe.txt");
                        }
						itmRef.MapIslName = totalInfo;
						totalInfo = GetConvertStr(itmRef.MapLocId, "MapDescribe.txt") + ", " + GetConvertStr(itmRef.MapLocId + "_" + itmRef.MapBoxId, "MapDescribe.txt");
				        itmRef.MaplocName = totalInfo;

				        totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx, "MapDescribe.txt");
				        totalInfo = GetAssembledString(totalInfo, itmRef);
				        SetFormatedText("MAP_TEXT", totalInfo);
				    }
			    }
			    else
			    {
           			SetFormatedText("MAP_TEXT", GetConvertStr("type_part", "MapDescribe.txt"));
				}
            	SetVAligmentFormatedText("MAP_TEXT");
            }
            else
            {
            	SetNewPicture("MAP_PICTURE", "interfaces\maps\" + LanguageGetLanguage() + "\" + itmRef.imageTga + ".tga");
            	SetFormatedText("MAP_TEXT", "");
            }
            ShowMapWindow();
		}
		else
		{ 
			if (itmGroup == SPECIAL_ITEM_TYPE) // Jason, спецпредметы
			{
				if (itmRef.id == "Ultimate_potion") UltimatePotionEffect(); // зелье команчей
				if (itmRef.id == "berserker_potion") // зелье берсеркера
				{
					if (GetCharacterPerkUsing(pchar, "Rush"))
					{
						ActivateCharacterPerk(pchar, "Rush");
						PerkBerserkerReaction();
					}
					else PlaySound("interface\knock.wav");
				}
				if (itmRef.id == "potion7") // слёзы Иш-Чель
				{
					Log_Info(XI_ConvertString("IndianPotionUsed"));
					//PlaySound("Ambient\Tavern\glotok_001.wav");
					PlaySound("Ambient\Horror\Fear_breath_01.wav");
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 4);
					RemoveItems(pchar, "potion7", 1);
				}
				// мангароса
				if (itmRef.id == "mangarosapower") 	MangarosaEffect("power"); 	// зелье силы
				if (itmRef.id == "mangarosafast") 	MangarosaEffect("fast"); 	// зелье реакции
				if (itmRef.id == "mangarosatotal") 	MangarosaEffect("total"); 	// комплексное зелье
				// калеуче
				if (findsubstr(itmRef.id, "kaleuche_amulet", 0) != -1)
				{
					Log_Info(XI_ConvertString("PowerfulPotionUsed"));
					//PlaySound("Ambient\Tavern\glotok_001.wav");
					PlaySound("Ambient\Horror\Fear_breath_01.wav");
					AddCharacterHealth(pchar, 5);
					RemoveItems(pchar, itmRef.id, 1);
					Caleuche_MangarosaPotionEffect(itmRef.id); 	
				}
				// калеуче - ящик Мерримана
				if (itmRef.id == "MerrimanBook") Caleuche_MerrimanBoxOpen();
				if (findsubstr(itmRef.id, "recipe_" , 0) != -1) // рецепты
				{
					if (isMultiObjectKnown(itmRef.result))
					{
						PlaySound("interface\knock.wav");
						Log_Info(XI_ConvertString("KnownRecipe"));
					}
					else
					{
						RemoveItems(pchar, itmRef.id, 1);
						AddQuestRecordInfo("Recipe", itmRef.result);
						SetAlchemyRecipeKnown(itmRef.result);
					}
				}
				if (findsubstr(itmRef.id, "purse" , 0) != -1) // кошельки
				{
					RemoveItems(pchar, itmRef.id, 1);
					TakeNItems(pchar, itmRef.result, sti(itmRef.result.qty));
					PlaySound("Ambient\Tavern\monetki_taverna_001.wav");
					Log_info(XI_ConvertString("Acquired")+sti(itmRef.result.qty)+XI_ConvertString("dublon4")+"");
				}
				if (itmRef.id == "RingCapBook") // СЖ пинаса 'Санта-Люсия' и дневник Колхауна
				{
					RemoveItems(pchar, itmRef.id, 1);
					AddQuestRecordInfo("RingCapBook", "1");
					pchar.questTemp.LSC.Ring.ReadCapBook = "true";
				}
				if (itmRef.id == "ArchyBook") // // Jason 070712 дневник Колхауна
				{
					RemoveItems(pchar, itmRef.id, 1); 
					GuardOT_ReadArchyBook(); // Jason 050712
				}
				if (itmRef.id == "specialletter") // спецписьмо
				{
					RemoveItems(pchar, itmRef.id, 1);
					AddQuestRecordInfo(itmRef.text, "1");
					pchar.GenQuest.specialletter.read = itmRef.text;
					if (pchar.GenQuest.specialletter.read == "Letter_Vincento") GuardOT_VinsentoLetterRead();
					if (pchar.GenQuest.specialletter.read == "Letter_Vincento_next") GuardOT_VinsentoNextLetterRead();
					if (pchar.GenQuest.specialletter.read == "Letter_Vincento_last") Ksochitam_VinsentoLastLetterRead();
					if (pchar.GenQuest.specialletter.read == "Letter_Dichoso") Tieyasal_DichosoLetterRead();
				}
				if (itmRef.id == "skinmap") // // Jason 120712 карта двух появлений
				{
					int mark = sti(itmRef.mark);
					SetNewPicture("MAP_PICTURE", "interfaces\maps\" + "skinmap_"+mark+".tga");
					ShowMapWindow();
					if (CheckAttribute(pchar, "questTemp.Ksochitam"))
					{
						if (pchar.questTemp.Ksochitam == "skinmap_1") Ksochitam_LookSkinmapFirstTime();
						if (pchar.questTemp.Ksochitam == "skinmap_2") Ksochitam_LookSkinmapSecondTime();
					}
					return;
				}
				if (itmRef.id == "mark_map") // // Jason 130712 карта с пометками
				{
					mark = sti(itmRef.mark);
					if(LanguageGetLanguage() != "Russian")
						SetNewPicture("MAP_PICTURE", "interfaces\maps\english\" + "map_TM_"+mark+".tga");
					else 
						SetNewPicture("MAP_PICTURE", "interfaces\maps\russian\" + "map_TM_"+mark+".tga");
					ShowMapWindow();
					return;
				}
				if (itmRef.id == "SQCapBook") // // Jason 240712 СЖ капитана Санта-Квитерии
				{
					RemoveItems(pchar, itmRef.id, 1); 
					AddQuestRecordInfo("SQCapBook", "1");
					pchar.questTemp.Ksochitam.SQCapBookRead = "true";
				}
				if (itmRef.id == "wolfreeks_book") Mtraxx_WolfreekReadLogbook(); // // Addon 2016-1 Jason Пиратская линейка журнал Вульфрика
				if (itmRef.id == "treasure_note") // Записки из кладов
				{
                    aref aReadSequence;
                    makearef(aReadSequence, PChar.Treasure_Stories_Read);
                    totalInfo = GetAttributeValue(GetAttributeN(aReadSequence, 0)); // Берём хронологически первый номер
					RemoveItems(pchar, "treasure_note", 1);
					AddQuestRecordInfo("StoriesTreasures", totalInfo);
					Treasure_Stories(totalInfo);
				}
				if(HasSubStr(itmRef.id, "FirearmStockPart") && CanUpgradeMusketSP(xi_refCharacter, itmRef))
				{
					UpgradeMusketSP(xi_refCharacter);
					FillItemsSelected();
					FillTableOther();
				}
				SetVariable();
				UpdateItemInfo();
				return;
			}
			else
			{
				bool bCanmakeMushketer = (CheckAttribute(xi_refCharacter, "CanTakeMushket"))
				if(HasSubStr(itmRef.id, "Mushket") && bCanmakeMushketer)
				{
					/* if (IsMainCharacter(xi_refCharacter)) // ГГ
					{
						if(!CheckAttribute(PChar, "IsMushketer")) // Не мушкетер. Делаем мушкетером
						{
							SetMainCharacterToMushketer(itmRef.id, true);
						}
						else // Мушкетер. Делаем обычным фехтовальщиком
						{
							SetMainCharacterToMushketer("", false);
						}
					}
					else
					{ */
						if(!CheckAttribute(xi_refCharacter, "IsMushketer")) // Не мушкетер. Делаем мушкетером
						{
							SetOfficerToMushketer(xi_refCharacter, itmRef.id, true);
							SetVariable();
							UpdateItemInfo();
								FillItemsSelected();
								FillTableOther();
							return;
						}
						else // Мушкетер. Делаем обычным фехтовальщиком
						{
							SetOfficerToMushketer(xi_refCharacter, itmRef.id, false);
							SetVariable();
							UpdateItemInfo();
								FillItemsSelected();
								FillTableOther();
							return;
						}
					//}
				} 
				else
				{
					if (itmGroup == ITEM_SLOT_TYPE)
					{
						if(IsEquipCharacterByArtefact(xi_refCharacter, itmRef.id))
						{
							RemoveCharacterArtefactEquip(xi_refCharacter, GetCharacterEquipSlot(xi_refCharacter, itmRef.id));
							SetVariable();
							FillItemsSelected();
							UpdateItemInfo();
							return;
						}
						else
						{
							EquipCharacterByArtefact(xi_refCharacter, itmRef.id);
							if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
							{
								DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
								ProcessExitCancel();
								return;
							}
						}
						if (itmRef.id == "indian_poison") // ugeen 2016
						{
							Achievment_Set("ach_71");
						}
					}
					else
					{
						if (itmRef.groupID == AMMO_ITEM_TYPE) // боеприпасы для пистолей и мушкетов
						{
							if(isMusketLoadPress || and(GetCharacterEquipByGroup(xi_refCharacter, MUSKET_ITEM_TYPE) != "", GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE) == ""))
							{
								if(!LAi_SetCharacterUseBullet(xi_refCharacter, MUSKET_ITEM_TYPE, itmRef.ID)) 
								{
									if(HasSubStr(itmRef.ID, "_double")) notification(XI_ConvertString("AmmoNotSelectNotif"), "AmmoNotSelect");
									PlaySound("interface\knock.wav");
									return;
								}
								LAi_GunSetUnload(xi_refCharacter, MUSKET_ITEM_TYPE);
								
								SetNewGroupPicture("ITEM_5B", itmRef.picTexture, "itm" + itmRef.picIndex);
								if (itmRef.id != GetAmmoPortrait(GetCharacterEquipByGroup(xi_refCharacter, MUSKET_ITEM_TYPE)))
								{
									SetNodeUsing("TABBTNSLOT_5B", true);
									SetNodeUsing("ITEM_5B", true);
								} else {
									SetNodeUsing("ITEM_5B", false);
								}
							}
							else
							{
								if(!LAi_SetCharacterUseBullet(xi_refCharacter, GUN_ITEM_TYPE, itmRef.ID)) 
								{
									if(HasSubStr(itmRef.ID, "_double")) notification(XI_ConvertString("AmmoNotSelectNotif"), "AmmoNotSelect");
									PlaySound("interface\knock.wav");
									log_info("gun load");
									return;
								}
								LAi_GunSetUnload(xi_refCharacter, GUN_ITEM_TYPE);
								
								SetNewGroupPicture("ITEM_2B", itmRef.picTexture, "itm" + itmRef.picIndex);
								if (itmRef.id != GetAmmoPortrait(GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE)))
								{
									SetNodeUsing("TABBTNSLOT_2B", true);
									SetNodeUsing("ITEM_2B", true);
								} else {
									SetNodeUsing("ITEM_2B", false);
								}
							}
							//Log_info(XI_ConvertString("AmmoSelect")+GetConvertStr(itmRef.name, "ItemsDescribe.txt")+"");
							notification(GetFullName(xi_refCharacter)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(itmRef.name, "ItemsDescribe.txt")+"", "AmmoSelect");
							PlaySound("People Fight\reload1.wav");
							SetVariable();
							SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("LoadAnyGun"));
							return;
						}
						else
						{
							if (itmRef.groupID == LANTERN_ITEM_TYPE)
							{
								if(IsEquipCharacterByItem(xi_refCharacter, itmRef.id))
								{
									RemoveCharacterEquip(xi_refCharacter, itmGroup);
									DeleteAttribute(pchar, "LanternOnChar");
									DeleteAttribute(pchar, "HandLight");
									SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "UntieItem", 9);
									SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "HandLightOff");
									Log_Info(XI_ConvertString("LanternOff"));
								} else {
									EquipCharacterByItem(xi_refCharacter, itmRef.id);
									pchar.LanternOnChar = true; // фонарь надет
									SendMessage(pchar, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", 9, "lantern_beltoff", "Lantern_belt",1);
									Log_Info(XI_ConvertString("LanternOn"));
								}
							}
							else
							{
								if(IsEquipCharacterByItem(xi_refCharacter, itmRef.id))
								{
									// belamour legendary edition орден святого Людовика -->
									if(itmRef.id == "talisman9" && CheckAttribute(xi_refCharacter, "reputation.fame.talisman9"))
									{
										xi_refCharacter.reputation.fame = COMPLEX_REPUTATION_MAX - sti(xi_refCharacter.reputation.fame.talisman9);
										DeleteAttribute(xi_refCharacter, "reputation.fame.talisman9");
										SetVariable();
									}
									if(itmRef.id == "suit5" && CheckAttribute(xi_refCharacter, "reputation.fame.talisman9"))
									{
										xi_refCharacter.reputation.fame = COMPLEX_REPUTATION_MAX - sti(xi_refCharacter.reputation.fame.talisman9);
										DeleteAttribute(xi_refCharacter, "reputation.fame.talisman9");
										SetVariable();
									}
									RemoveCharacterEquip(xi_refCharacter, itmGroup);
								}
								else 
								{
									if(sti(xi_refCharacter.index) == GetMainCharacterIndex() && itmRef.id == "talisman9")
									{
										xi_refCharacter.reputation.fame.talisman9 = COMPLEX_REPUTATION_MAX - sti(xi_refCharacter.reputation.fame);
										xi_refCharacter.reputation.fame = COMPLEX_REPUTATION_MAX;
										SetVariable();
									}
									if(sti(xi_refCharacter.index) == GetMainCharacterIndex() && itmRef.id == "suit5")
									{
										xi_refCharacter.reputation.fame.talisman9 = COMPLEX_REPUTATION_MAX - sti(xi_refCharacter.reputation.fame);
										xi_refCharacter.reputation.fame = COMPLEX_REPUTATION_MAX;
										SetVariable();
									}
									// <-- legendary edition
									// belamour cle Цзань -->
									if(itmRef.id == "blade_41")
									{
										SetBlade_FgtLvl(xi_refCharacter, itmRef);
									}
									// <-- Цзань
									EquipCharacterByItem(xi_refCharacter, itmRef.id);
								}
							}
						}
					}
				}
			}
			FillItemsSelected();
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
			SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(itmRef));
			SetItemInfo(iGoodIndex);
			SetVariable(); // еще раз обновим
		}
	}
	else
	{
		if(HasSubStr(itmRef.id, "potion")) // лечилки
		{
			SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(itmRef));
			DoCharacterUsedItem(xi_refCharacter, itmRef.id);
			SetVariable();
			FillItemsSelected();
			UpdateItemInfo();
		}
	}
	FillTableOther();
}

void ExitMapWindow()
{
	XI_WindowShow("MAP_WINDOW", false);
	XI_WindowDisable("MAP_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetFormatedText("MAP_TEXT", "");
	SetCurrentNode("TABLE_ITEMS");
}

void ShowMapWindow()
{
	XI_WindowShow("MAP_WINDOW", true);
	XI_WindowDisable("MAP_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	
	SetCurrentNode("MAP_TEXT");
}

void SelectItemByType(string itemType) {
	string equip = GetCharacterEquipByGroup(xi_refCharacter, itemType);
	if (equip == "") {
		return;
	}
	
	int index = GetItemIndex(equip);
	if (index < 0) {
		return;
	}
	
	aref tableItems;
	makearef(tableItems, GameInterface.TABLE_ITEMS);
	int n = 1;
	while (true) {
		string row = "tr" + n;
		if (!CheckAttribute(tableItems, row)) {
			break;
		}
		
		if (tableItems.(row).index == index) {
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ITEMS", 2, n - 1);
			return;
		}
		
		n += 1;
	}
}

void SelectAmulet(string slot) {
	string equip = GetCharacterEquipBySlot(xi_refCharacter, slot);
	if (equip == SLOT_NOT_USED) {
		return;
	}
	
	int index = GetItemIndex(equip);
	if (index < 0) {
		return;
	}
	
	aref tableItems;
	makearef(tableItems, GameInterface.TABLE_ITEMS);
	int n = 1;
	while (true) {
		string row = "tr" + n;
		if (!CheckAttribute(tableItems, row)) {
			break;
		}
		
		if (tableItems.(row).index == index) {
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ITEMS", 2, n - 1);
			return;
		}
		
		n += 1;
	}
}

void SelectAmmoType(string itemType) {
	string equip = LAi_GetCharacterBulletType(xi_refCharacter, itemType);
	if (equip == SLOT_NOT_USED) {
		return;
	}
	
	int index = GetItemIndex(equip);
	if (index < 0) {
		return;
	}
	
	aref tableItems;
	makearef(tableItems, GameInterface.TABLE_ITEMS);
	int n = 1;
	while (true) {
		string row = "tr" + n;
		if (!CheckAttribute(tableItems, row)) {
			break;
		}
		
		if (tableItems.(row).index == index) {
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ITEMS", 2, n - 1);
			return;
		}
		
		n += 1;
	}
}

string GetAmmoPortrait(string weapon) 
{
	if(weapon == "pistol8") return "harpoon";
	
	string defBullet = LAi_GetCharacterDefaultBulletType(weapon);
	
	if(defBullet != "") return defBullet;
	
	return "bullet";
}

void SetHatSlot(ref xi_refCharacter)
{
	bool bState = false;
	if(HasHatLocator(xi_refCharacter)) bState = true;
	if(CanEquipHatDirectly(xi_refCharacter)) bState = true;
	SetNodeUsing("HATS_BACK", bState);
	SetNodeUsing("TABBTNSLOT_11", bState);
	SetNodeUsing("EMPTY_HATS", bState);
	SetNodeUsing("ITEM_11", bState);
	SetNodeUsing("BTN_ITEM_11", bState);
}

void procScrollTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	if(sNodName == "TABBTN_SCROLL_1")
	{
		SetControlsScrollTabMode(1);
		return;
	}
	if(sNodName == "TABBTN_SCROLL_2")
	{
		if(GetFreePassengersQuantity(pchar) == 0) return;
		SetControlsScrollTabMode(2);
		return;
	}
}

void SetControlsScrollTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	if(GetFreePassengersQuantity(pchar) == 0) nColor2 = argb(255,128,128,128);

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;

	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch (nMode)
	{
		case 1:
			sPic1 = "TabSelected";
			sPic3 = "TabSelectedMark";
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabSelected";
			sPic4 = "TabSelectedMark";
			nColor2 = argb(255,255,255,255);
		break;
	}
    
	SetNewGroupPicture("TABBTN_SCROLL_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_SCROLL_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_SCROLL_1_MARK", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_SCROLL_2_MARK", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SCROLL_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SCROLL_2", 8,0,nColor2);

	FillScrollControlsList(nMode);
}

void FillScrollControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: 
			FillCharactersScrollEx(true);
			currentScrollTab = 1;
		break;  // офицеры
	    case 2: 
			FillCharactersScrollEx(false);
			currentScrollTab = 2;
		break;  // пассажиры
	}
	if (CheckAttribute(&InterfaceStates, "CurCharacter")) 
	{
		GameInterface.CHARACTERS_SCROLL.current = InterfaceStates.CurCharacter;
		SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
		DeleteAttribute(&InterfaceStates, "CurCharacter");
	}
	else
	{
		GameInterface.CHARACTERS_SCROLL.current = 0;
		SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	}
}