/// boal 07/06/06 переделка СЖ под нужны ВМЛ
// Sith в сж добавлен журнал торговли
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню кнопками Q и E
ref xi_refCharacter;
int curQuestTop;
string CurTable, CurRow;
int iMaxGoodsStore = 50000;
int currentTab = 0;

void InitInterface(string iniName)
{
	xi_refCharacter = pchar;
	InterfaceStack.SelectMenu_node = "LaunchQuestBook"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleQuestBook";

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	SetFontType();
	
	selectJournal(1); // первый режим журнала, только активные
	
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);

    SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("SetScrollerPos","SetScrollerPos",0);
	SetEventHandler("ScrollPosChange","ProcScrollPosChange",0);
	SetEventHandler("ScrollTopChange","ProcScrollChange",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("QuestTopChange","QuestTopChange",0);
	SetEventHandler("BackToTitle","BackToTitle",0);
	SetEventHandler("QuestActivate","XI_QuestActivate",0);
	SetEventHandler("QuestDeActivate","QuestDeActivate",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0); // belamour окно инфы на пкм

	XI_RegistryExitKey("IExit_F2");
	
	string sDate = " ";
	sDate = GetDateString();
	string sTime; 
	sTime = GetTimeString();
    SetFormatedText("CURRENT_DATE_CAPTION", sDate + " "+ sTime);

	// belamour для выхода из меню корабля или персонажа -->
	if(CheckAttribute(pchar,"SystemInfo.ShowShip"))
		{
			SetControlsTabModeManual(5);
			DeleteAttribute(pchar, "SystemInfo.ShowShip");
		} 
		else
		{
			SetControlsTabModeManual(1); // первый режим журнала, только активные
		}
	// <--
	InitTableHeader();
	// доп инфа в шапку --->
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
	SetFormatedText("Difficulty", XI_ConvertString("m_Complexity") + ": " + GetLevelComplexity(MOD_SKILL_ENEMY_RATE));
	
	string herotype = " ";
	if (NullCharacter.HeroParam.HeroType == "HeroType_1") herotype = XI_ConvertString("Gymnast");
	if (NullCharacter.HeroParam.HeroType == "HeroType_2") herotype = XI_ConvertString("Accountant");
	if (NullCharacter.HeroParam.HeroType == "HeroType_3") herotype = XI_ConvertString("Athlete");
	if (NullCharacter.HeroParam.HeroType == "HeroType_4") herotype = XI_ConvertString("Shooter");
	SetFormatedText("Herotype", XI_ConvertString("Archetype") + ": " + herotype);
}

// гуляем по меню кнопками Q и E, TAB переключает вкладки таблицы
void ProcessInterfaceControls() 
{
	string controlName = GetEventData();
 
	if (controlName == "InterfaceGoLeft") {
        IDoExit(RC_INTERFACE_TO_SHIP);
    }
	if (controlName == "InterfaceGoRight") {
        IDoExit(RC_INTERFACE_MAPVIEW);
    }
	if (controlName == "InterfaceTabSwitch") {
		currentTab = (currentTab + 1) % 8;
		SetControlsTabMode(currentTab + 1);
	}
}
// метод на TAB переключает вкладки таблицы
void SetControlsTabModeManual(int mode) 
{
    currentTab = mode - 1;
    SetControlsTabMode(mode);
}

void XI_SetQuestData(bool qtitle)
{
	aref arefTmp;
	makearef(arefTmp,pchar.TmpQuestInfo);

	XI_SetQuestTitles("QUEST_TITLE",arefTmp,0);
	curQuestTop = 0;

	SetNodeUsing("QUEST_TITLE",qtitle);
	SetNodeUsing("QUEST_TEXT",!qtitle);
	SetNodeUsing("QUESTSCROLL_TITLE",qtitle);
	SetNodeUsing("QUESTSCROLL_TEXT",!qtitle);
	
	if(qtitle == true)
	{
		SetCurrentNode("QUEST_TITLE");
		SetNodeUsing("QUESTSCROLL_TITLE",true);
		if(currentTab > 2) HideQuests();
	}
	else
	{
		SetCurrentNode("QUEST_TITLE");
		SetNodeUsing("QUEST_TITLE",true);
		SetNodeUsing("QUESTSCROLL_TEXT",true);	
	}
	SetAlertMarks(xi_refCharacter);
}

void HideQuests()
{
	SetNodeUsing("QUEST_TITLE",false);
	SetNodeUsing("QUEST_TEXT",false);
	SetNodeUsing("QUESTSCROLL_TITLE",false);
	SetNodeUsing("QUESTSCROLL_TEXT",false);
}

void HideCashBook()
{
	SetNodeUsing("SCROLL_DEBIT",false);
	SetNodeUsing("TABLE_DEBIT",false);
	SetNodeUsing("SCROLL_CREDIT",false);
	SetNodeUsing("TABLE_CREDIT",false);
}

void HideShipPlace()
{
	SetNodeUsing("TABLE_SHIP_PLACE",false);
	SetNodeUsing("SCROLL_SHIP_PLACE",false);
}

void HideStoreBook()
{
	SetNodeUsing("TABLE_CITY",false);
	SetNodeUsing("SCROLL_CITY",false);
	SetNodeUsing("TABLE_GOODS",false);
	SetNodeUsing("SCROLL_GOODS",false);
}

// tradebook --->
void HideTradeBook()
{
	SetNodeUsing("TRADEBOOK_TABLE_CITY",false);
	SetNodeUsing("TRADEBOOK_SCROLL_CITY",false);
	SetNodeUsing("TRADEBOOK_TABLE_GOODS",false);
	SetNodeUsing("TRADEBOOK_SCROLL_GOODS",false);
}
// <---
void HideStatistic()
{
	SetNodeUsing("TABLE_SHIPCLASS",false);
	SetNodeUsing("TABLE_HUMAN",false);
	SetNodeUsing("TABLE_NATION",false);
	SetNodeUsing("TABLE_OTHER",false);
	SetNodeUsing("DIFFICULTY",false);
	SetNodeUsing("HEROTYPE",false);
	// CreateString(true, "LevelComplexity", "", "INTERFACE_ULTRASMALL", COLOR_NORMAL, 0, 0, SCRIPT_ALIGN_RIGHT, 1);
}

void ProcessCancelExit()
{
	// if( GetSelectable("QUEST_TEXT") )
	// {
		// XI_SetQuestData(true);
		// return;
	// }
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void QuestTopChange()
{
	if( GetSelectable("QUEST_TITLE") )
	{
		int newTop = curQuestTop+GetEventData();

		aref arefTmp;
		makearef(arefTmp,pchar.TmpQuestInfo);
		int maxVal = GetAttributesNum(arefTmp);
		if(newTop>=maxVal)
		{
			newTop=maxVal-1;
		}
		if(newTop<0)
		{
			newTop=0;
		}

		if(newTop!=curQuestTop)
		{
			curQuestTop=newTop;
			XI_SetQuestTitles("QUEST_TITLE",arefTmp,curQuestTop);
			XI_SetScroller(MakeFloat(newTop)/MakeFloat(maxVal));
		}
	}
}

void SetQTextShow(aref pA,int qnum)
{
	// boal Покраска, выбрали 22.06.07 -->
	aref arTopic = GetAttributeN(pA, qnum);
	string sTopic = GetAttributeName(arTopic);
	DeleteQuestHeaderColor(sTopic);	
	// boal <--
	
	if(sTopic == "SharlieTutorial_ListOfSailors" && TW_IsActive() && CheckAttribute(&objTask, "land_craft") && objTask.land_craft == "1_Inventory" && CheckAttribute(&TEV, "Tutor.Document"))
	{
		TW_ColorWeak(TW_GetTextARef("Inventory_document"));
		DeleteAttribute(&TEV, "Tutor.Document");
		if(!CheckAttribute(&TEV, "Tutor.Alchemy"))
			TW_FinishLand_Craft_1_Inventory();
	}
	
	SendMessage(&GameInterface,"lsal",MSG_INTERFACE_INIT_QTEXT_SHOW,"QUEST_TEXT",pA,qnum);
	SetCurrentNode("QUEST_TEXT");
}

void BackToTitle()
{
	// XI_SetQuestData(true);
	selectJournal(currentTab+1);
}

void XI_QuestActivate()
{
	int aq = curQuestTop+GetEventData();
	aref pA;
	makearef(pA,pchar.TmpQuestInfo);
	if (GetAttributesNum(pA) == 0) return;
	XI_SetQuestData(false);
	SetQTextShow(pA,aq);
	SetCurrentNode("QUEST_TEXT");
}

void XI_SetScroller(float pos)
{
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"QUESTSCROLL_TITLE",pos);
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"QUESTSCROLL_TEXT",pos);
}

void SetScrollerPos()
{
	string nodName = GetEventData();
	float pos = GetEventData();
	XI_SetScroller(pos);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("QuestTopChange","QuestTopChange");
	DelEventHandler("BackToTitle","BackToTitle");
	DelEventHandler("QuestActivate","XI_QuestActivate");
	DelEventHandler("SetScrollerPos","SetScrollerPos");
	DelEventHandler("ScrollPosChange","ProcScrollPosChange");
	DelEventHandler("ScrollTopChange","ProcScrollChange");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
 	DelEventHandler("QuestDeActivate","QuestDeActivate");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow"); // belamour окно инфы

    interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}
void QuestDeActivate()
{
	XI_SetQuestData(true);
}

void ProcScrollPosChange()
{
	float newPos = GetEventData();
	string scrollName = GetEventData();
	if(scrollName == "QUESTSCROLL_TITLE")
	{
		aref arefTmp;
		makearef(arefTmp,pchar.TmpQuestInfo);
		int maxVal = GetAttributesNum(arefTmp);
		int newTop = makeint(newPos*maxVal);

		if(newTop!=curQuestTop)
		{
			curQuestTop=newTop;
			XI_SetQuestTitles("QUEST_TITLE",arefTmp,curQuestTop);
		}
	}
	else
	{
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TEXT", 1,newPos);
	}
}

void ProcScrollChange()
{
	int changeNum = GetEventData();
	if(changeNum==0) return;
	string controlNode = "";
	if( GetSelectable("QUEST_TITLE") ) controlNode = "QUEST_TITLE";
	if( GetSelectable("QUEST_TEXT") ) controlNode = "QUEST_TEXT";

	if(controlNode!="")
	{
		if(changeNum>0) {
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,controlNode,-1, 0,ACTION_DOWNSTEP);
		} else {
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,controlNode,-1, 0,ACTION_UPSTEP);
		}
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	aref arCurRow;

	switch(nodName)
	{
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
		case "I_LOGBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_LOGBOOK";
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
			    nodName = "I_ABILITIES";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
		// belamour клик по кораблику
		case "TABLE_SHIP_PLACE": 
			if(comName=="click")
			{
				// --> mitrokosta fix если не было кораблей, открывалось пустое меню
				makearef(arCurRow, GameInterface.(CurTable).(CurRow));
				if (!CheckAttribute(arCurRow, "UserData.IDX")) {
					break;
				}
				// mitrokosta <--
				int chrIdx = sti(arCurRow.UserData.IDX);
				pchar.SystemInfo.ShowShip = chrIdx;
				// if(XI_IsKeyPressed("control")) IDoExit(RC_INTERFACE_TO_CHAR);
				if(XI_IsKeyPressed("shift")) IDoExit(RC_INTERFACE_TO_SHIP);
			}
		break;

	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_INVENTORY" || nodName == "I_SHIP" || nodName == "I_LOGBOOK" ||
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
}

void selectJournal(int iMode)
{
    // HideQuests();
	SetFontType();
	HideCashBook();
    HideShipPlace();
	HideStoreBook();
	HideTradeBook();
	HideStatistic();
	// подменим квестовую ветку, зависимо от типа режима: журнал, архив, инфа
	aref arQuestInfo, arTmp;
	int  i;
	string attributeName;
	bool   ok; // копировать ли?
	aref   newAttr;
	makearef(arQuestInfo, pchar.QuestInfo);
	DeleteAttribute(pchar, "TmpQuestInfo");
	pchar.TmpQuestInfo = "";
	for(i=0; i<GetAttributesNum(arQuestInfo); i++)
    {
        arTmp = GetAttributeN(arQuestInfo, i);
        attributeName = GetAttributeName(arTmp);
        ok = false;
		switch (iMode)
        {
            case 1:
                if (!CheckAttribute(pchar, "QuestInfo." + attributeName + ".InfoType") && sti(pchar.QuestInfo.(attributeName).Complete) == false)
                {
                    ok = true;
                }
            break;
            
            case 2:
                if (!CheckAttribute(pchar, "QuestInfo." + attributeName + ".InfoType") && sti(pchar.QuestInfo.(attributeName).Complete) == true)
                {
                    ok = true;
                }
            break;
            
            case 3:
                if (CheckAttribute(pchar, "QuestInfo." + attributeName + ".InfoType"))
                {
                    ok = true;
                }
            break;
        }
        if (ok)
        { // копируем
            pchar.TmpQuestInfo.(attributeName) = "";
            makearef(newAttr, pchar.TmpQuestInfo.(attributeName));
			CopyAttributes(newAttr, arTmp);
        }
    }
	XI_SetQuestData(true);
}

void selectCashBook()
{
    SetNodeUsing("SCROLL_DEBIT",true);
	SetNodeUsing("TABLE_DEBIT",true);
	SetNodeUsing("SCROLL_CREDIT",true);
	SetNodeUsing("TABLE_CREDIT",true);
	HideQuests();
	HideShipPlace();
	HideStoreBook();
	HideTradeBook();
	HideStatistic();
}

void selectShipPlace()
{
    SetNodeUsing("TABLE_SHIP_PLACE",true);
    SetNodeUsing("SCROLL_SHIP_PLACE",true);
	HideQuests();
	HideCashBook();
	HideStoreBook();
	HideTradeBook();
	HideStatistic();
}

void selectStoreBook()
{
	SetNodeUsing("TABLE_CITY",true);
	SetNodeUsing("SCROLL_CITY",true);
	SetNodeUsing("TABLE_GOODS",true);
	SetNodeUsing("SCROLL_GOODS",true);
	HideQuests();
	HideCashBook();
	HideShipPlace();
	HideTradeBook();
	HideStatistic();
}
// tradebook --->
void selectTradeBook()
{
	SetNodeUsing("TRADEBOOK_TABLE_CITY",true);
	SetNodeUsing("TRADEBOOK_SCROLL_CITY",true);
	SetNodeUsing("TRADEBOOK_TABLE_GOODS",true);
	SetNodeUsing("TRADEBOOK_SCROLL_GOODS",true);
	HideQuests();
	HideCashBook();
	HideShipPlace();
	HideStoreBook();
	HideStatistic();	
}
// <---
void selectStatistic()
{
    SetNodeUsing("TABLE_SHIPCLASS",true);
    SetNodeUsing("TABLE_HUMAN",true);
    SetNodeUsing("TABLE_NATION",true);
    SetNodeUsing("TABLE_OTHER",true);
	SetNodeUsing("DIFFICULTY",true);
	SetNodeUsing("HEROTYPE",true);
	HideQuests();
    HideCashBook();
	HideShipPlace();
	HideStoreBook();
	HideTradeBook();
}

void HideInfoWindow() 
{
	CloseTooltip();
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;
	sPicture = "-1";
	int picW, picH;
	// string sAttributeName;
	// int nChooseNum = -1;
	aref arCurRow;
	makearef(arCurRow, GameInterface.(CurTable).(CurRow));
	sGroupPicture = "";
	switch (sCurrentNode)
	{
		case "TABBTN_QUEST":
			sHeader = XI_ConvertString("QuestsBook");
			sText1 = XI_ConvertString("QuestsBook_Descr");
		break;
		case "TABBTN_QUESTARJ":
			sHeader = XI_ConvertString("QuestsLogBook");
			sText1 = XI_ConvertString("QuestsLogBook_Descr");
		break;
		case "TABBTN_INFO":
			sHeader = XI_ConvertString("DocsBook");
			sText1 = XI_ConvertString("DocsBook_Descr");
		break;
		case "TABBTN_CASHBOOK":
			sHeader = XI_ConvertString("CashBook");
			sText1 = XI_ConvertString("CashBook_Descr1");
			sText2 = XI_ConvertString("CashBook_Descr2");
		break;
		case "TABBTN_SHIP_PLACE":
			sHeader = XI_ConvertString("ShipsPlaceBook");
			sText1 = XI_ConvertString("ShipsPlaceBook_Descr1");
		break;
		case "TABBTN_STOREBOOK":
			sHeader = XI_ConvertString("StorageBook");
			sText1 = XI_ConvertString("StorageBook_Descr");
		break;
		case "TABBTN_TRADEBOOK":
			sHeader = XI_ConvertString("TradeBook");
			sText1 = XI_ConvertString("TradeBook_Descr1");
		break;
		case "TABBTN_STATISTIC":
			sHeader = XI_ConvertString("StatisticsBook");
			sText1 = XI_ConvertString("StatisticsBook_Descr");
		break;
		case "QUEST_TEXT":
			if (currentTab == 0)
			{
				sHeader = XI_ConvertString("QuestsBook");
				sText1 = XI_ConvertString("QuestsBook_Descr");
			}
			if (currentTab == 1)
			{
				sHeader = XI_ConvertString("QuestsLogBook");
				sText1 = XI_ConvertString("QuestsLogBook_Descr");
			}
			if (currentTab == 2)
			{
				sHeader = XI_ConvertString("DocsBook");
				sText1 = XI_ConvertString("DocsBook_Descr");
			}
		break;
		case "TABLE_CITY":
				sHeader = XI_ConvertString("StorageBook");
				sText1 = XI_ConvertString("StorageBook_Descr");
		break;
		case "TABLE_GOODS":
			sGroup = "GOODS";
			if (!CheckAttribute(arCurRow, "UserData.IDX")) {
				sHeader = XI_ConvertString("StorageBook");
				sText1 = XI_ConvertString("StorageBook_Descr");
			} else {
				iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
				sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
				sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
				picW = 128;
				picH = 128;
				sText1  = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem]);
			}
		break;
		case "TABLE_SHIP_PLACE":
			if (!CheckAttribute(arCurRow, "UserData.IDX")) {
				sHeader = XI_ConvertString("ShipsPlaceBook");
				sText1 = XI_ConvertString("ShipsPlaceBook_Descr1");
			} else {
				int chrIdx = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
				ref chref = GetCharacter(chrIdx);
				int iShip = sti(chref.ship.type);
				ref refBaseShip = GetRealShip(iShip);
				string sShip = refBaseShip.BaseName + refBaseShip.ship.upgrades.hull;
				sPicture = "interfaces\le\ships\" + sShip + ".tga";
				picW = 512;
				picH = 512;
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetShipDescr(refBaseShip);
				sText2 = XI_ConvertString("ShipsPlaceBook_Descr2");
				sText3 = " ";
			}
		break;
		case "TRADEBOOK_TABLE_CITY":
				sHeader = XI_ConvertString("TradeBook");
				sText1 = XI_ConvertString("TradeBook_Descr1");
		break;
		case "TRADEBOOK_TABLE_GOODS":
		    sGroup = "GOODS";
			sGroupPicture = "";
			if (!CheckAttribute(arCurRow, "UserData.IDX")) {
				sHeader = XI_ConvertString("TradeBook");
				sText1  = XI_ConvertString("TradeBook_Descr1");
				sText2  = XI_ConvertString("TradeBook_Descr2");
			} else {
		    iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
			sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem]);
			sText2 = XI_ConvertString("TradeBook_Descr3");
			picW = 128;
			picH = 128;
			}
		break;
		// sith --->
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
		//<--- sith
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, picW, picH);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	switch (sNodName)
	{
		case "TABBTN_QUEST":
			SetControlsTabModeManual(1);
		break;
		case "TABBTN_QUESTARJ":
			SetControlsTabModeManual(2);
		break;
		case "TABBTN_INFO":
			SetControlsTabModeManual(3);
		break;
		case "TABBTN_CASHBOOK":
			SetControlsTabModeManual(4);
		break;
		case "TABBTN_SHIP_PLACE":
			SetControlsTabModeManual(5);
		break;
		case "TABBTN_STOREBOOK":
			SetControlsTabModeManual(6);
		break;
		case "TABBTN_TRADEBOOK":
			SetControlsTabModeManual(7);
		break;
		case "TABBTN_STATISTIC":
			SetControlsTabModeManual(8);
		break;
	}
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(155,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;
	int nColor5 = nColor1;
	int nColor6 = nColor1;
	int nColor7 = nColor1;
	int nColor8 = nColor1;

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;
	string sPic5 = sPic1;
	string sPic6 = sPic1;
	string sPic7 = sPic1;
	string sPic8 = sPic1;

	switch (nMode)
	{
		case 1: //
			sPic1 = "TabSelected1";
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabSelected2";
			nColor2 = argb(255,255,255,255);
		break;
		case 3:
			sPic3 = "TabSelected3";
			nColor3 = argb(255,255,255,255);
		break;
		case 4:
			sPic4 = "TabSelected4";
			nColor4 = argb(255,255,255,255);
		break;
		case 5:
			sPic5 = "TabSelected5";
			nColor5 = argb(255,255,255,255);
		break;
		case 6:
			sPic6 = "TabSelected6";
			nColor6 = argb(255,255,255,255);
		break;
		case 7:
			sPic7 = "TabSelected7";
			nColor7 = argb(255,255,255,255);
		break;		
		case 8:
			sPic8 = "TabSelected8";
			nColor8 = argb(255,255,255,255);
		break;	
	}

	SetNewGroupPicture("TABBTN_QUEST", "QUESTBOOK", sPic1);
	SetNewGroupPicture("TABBTN_QUESTARJ", "QUESTBOOK", sPic2);
	SetNewGroupPicture("TABBTN_INFO", "QUESTBOOK", sPic3);
	SetNewGroupPicture("TABBTN_CASHBOOK", "QUESTBOOK", sPic4);
	SetNewGroupPicture("TABBTN_SHIP_PLACE", "QUESTBOOK", sPic5);
	SetNewGroupPicture("TABBTN_STOREBOOK", "QUESTBOOK", sPic6);
	SetNewGroupPicture("TABBTN_TRADEBOOK", "QUESTBOOK", sPic7);
	SetNewGroupPicture("TABBTN_STATISTIC", "QUESTBOOK", sPic8);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_QUEST", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_QUESTARJ", 8,0,nColor2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_INFO", 8,0,nColor3);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_CASHBOOK", 8,0,nColor4);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SHIP_PLACE", 8,0,nColor5);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_STOREBOOK", 8,0,nColor6);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_TRADEBOOK", 8,0,nColor7);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_STATISTIC", 8,0,nColor8);	
	
	currentTab = nMode-1;
	FillControlsList(nMode);
	if(currentTab > 2) XI_SetQuestData(true);
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: selectJournal(1); break;	// первый режим журнала, только активные
	    case 2: selectJournal(2); break;	// только закрытые
	    case 3: selectJournal(3); break;	// только инфа
	    case 4: selectCashBook(); break;	// кассовая книга
	    case 5: selectShipPlace(); break;	// корабли на приколе
		case 6: selectStoreBook(); break;	// складская книга
		case 7: selectTradeBook(); break;	// журнал торговли
	    case 8: selectStatistic(); break;	// статистика
	}
}

void InitTableHeader()
{
	int    i;
	string row;
	
	GameInterface.TABLE_SHIPCLASS.hr.td1.str = XI_ConvertString("StatShips");
	GameInterface.TABLE_SHIPCLASS.hr.td1.line_space_modifier = 0.8;
	// GameInterface.TABLE_SHIPCLASS.hr.td1.scale = 0.9;
	GameInterface.TABLE_SHIPCLASS.hr.td2.str = XI_ConvertString("StatSunkByGuns");
	GameInterface.TABLE_SHIPCLASS.hr.td2.line_space_modifier = 0.8;
	// GameInterface.TABLE_SHIPCLASS.hr.td2.scale = 0.7;
	GameInterface.TABLE_SHIPCLASS.hr.td3.str = XI_ConvertString("StatSunkByBoarding");
	GameInterface.TABLE_SHIPCLASS.hr.td3.line_space_modifier = 0.8;
	// GameInterface.TABLE_SHIPCLASS.hr.td3.scale = 0.7;
	GameInterface.TABLE_SHIPCLASS.hr.td4.str = XI_ConvertString("StatCapturedByBoarding");
	GameInterface.TABLE_SHIPCLASS.hr.td4.line_space_modifier = 0.8;
	// GameInterface.TABLE_SHIPCLASS.hr.td4.scale = 0.7;
	
    for (i = 1; i< 7; i++)
	{
        row = "tr" + i;
        GameInterface.TABLE_SHIPCLASS.(row).td1.str = XI_ConvertString("StatClass") + i;
		GameInterface.TABLE_SHIPCLASS.(row).td2.str = Statistic_AddValue(pchar, "KillShip_" + i, 0);
		GameInterface.TABLE_SHIPCLASS.(row).td3.str = Statistic_AddValue(pchar, "KillAbordShip_" + i, 0);
		GameInterface.TABLE_SHIPCLASS.(row).td4.str = Statistic_AddValue(pchar, "AbordShip_" + i, 0);
	}

	GameInterface.TABLE_HUMAN.hr.td1.str = XI_ConvertString("StatKilled");
	// GameInterface.TABLE_HUMAN.hr.td1.scale = 0.9;
	GameInterface.TABLE_HUMAN.hr.td2.str = XI_ConvertString("StatByBlades");
	// GameInterface.TABLE_HUMAN.hr.td2.scale = 0.7;
	GameInterface.TABLE_HUMAN.hr.td3.str = XI_ConvertString("StatByFirearms");
	// GameInterface.TABLE_HUMAN.hr.td3.scale = 0.7;
	
	GameInterface.TABLE_HUMAN.tr1.td1.str = XI_ConvertString("StatSoldiers");
	GameInterface.TABLE_HUMAN.tr1.td2.str = Statistic_AddValue(pchar, "Solder_s", 0);
	GameInterface.TABLE_HUMAN.tr1.td3.str = Statistic_AddValue(pchar, "Solder_g", 0);
	
	GameInterface.TABLE_HUMAN.tr2.td1.str = XI_ConvertString("StatCitizens");
	GameInterface.TABLE_HUMAN.tr2.td2.str = Statistic_AddValue(pchar, "Citizen_s", 0);
	GameInterface.TABLE_HUMAN.tr2.td3.str = Statistic_AddValue(pchar, "Citizen_g", 0);
	
	GameInterface.TABLE_HUMAN.tr3.td1.str = XI_ConvertString("StatScum");
	GameInterface.TABLE_HUMAN.tr3.td2.str = Statistic_AddValue(pchar, "Monster_s", 0);
	GameInterface.TABLE_HUMAN.tr3.td3.str = Statistic_AddValue(pchar, "Monster_g", 0);
	
	GameInterface.TABLE_HUMAN.tr4.td1.str = XI_ConvertString("StatOther");
	GameInterface.TABLE_HUMAN.tr4.td2.str = Statistic_AddValue(pchar, "Warrior_s", 0);
	GameInterface.TABLE_HUMAN.tr4.td3.str = Statistic_AddValue(pchar, "Warrior_g", 0);
	
	GameInterface.TABLE_HUMAN.tr5.td1.str = XI_ConvertString("StatTotal");
	GameInterface.TABLE_HUMAN.tr5.td2.str = Statistic_AddValue(pchar, "Solder_s", 0) + Statistic_AddValue(pchar, "Citizen_s", 0) + Statistic_AddValue(pchar, "Monster_s", 0) + Statistic_AddValue(pchar, "Warrior_s", 0);
	GameInterface.TABLE_HUMAN.tr5.td3.str = Statistic_AddValue(pchar, "Solder_g", 0) + Statistic_AddValue(pchar, "Citizen_g", 0) + Statistic_AddValue(pchar, "Monster_g", 0) + Statistic_AddValue(pchar, "Warrior_g", 0);
	
	GameInterface.TABLE_OTHER.hr.td1.str = XI_ConvertString("StatEvents");
	GameInterface.TABLE_OTHER.hr.td2.str = XI_ConvertString("StatValue");
	
	GameInterface.TABLE_OTHER.tr1.td1.str = XI_ConvertString("StatShipsSold");
	GameInterface.TABLE_OTHER.tr1.td2.str = Statistic_AddValue(PChar, "SellShip", 0);
	
	GameInterface.TABLE_OTHER.tr2.td1.str = XI_ConvertString("StatShipsPurchased");
	GameInterface.TABLE_OTHER.tr2.td2.str = Statistic_AddValue(PChar, "BuyShip", 0);
	
	GameInterface.TABLE_OTHER.tr3.td1.str = XI_ConvertString("StatShipMutiny");
	GameInterface.TABLE_OTHER.tr3.td2.str = Statistic_AddValue(PChar, "ShipMunity", 0);
	
	GameInterface.TABLE_OTHER.tr4.td1.str = XI_ConvertString("StatSlavesMutiny");
	GameInterface.TABLE_OTHER.tr4.td2.str = Statistic_AddValue(PChar, "SlavesMunity", 0);
	
	GameInterface.TABLE_OTHER.tr5.td1.str = XI_ConvertString("StatAbordShipFree");
	GameInterface.TABLE_OTHER.tr5.td2.str = Statistic_AddValue(PChar, "AbordShipFree", 0);
	
	GameInterface.TABLE_OTHER.tr6.td1.str = XI_ConvertString("StatRatsEatGoods");
	GameInterface.TABLE_OTHER.tr6.td2.str = Statistic_AddValue(PChar, "RatsEatGoods", 0);
	
	GameInterface.TABLE_OTHER.tr7.td1.str = XI_ConvertString("StatSaveLoad");
	GameInterface.TABLE_OTHER.tr7.td2.str = pchar.SystemInfo.SaveCount +" / " + pchar.SystemInfo.LoadCount;
	
	GameInterface.TABLE_OTHER.tr8.td1.str = XI_ConvertString("StatHealthTotalDmg");
	GameInterface.TABLE_OTHER.tr8.td2.str = sti(pchar.Health.TotalDamg);
	
	GameInterface.TABLE_OTHER.tr9.td1.str = XI_ConvertString("StatSailorsDead");
	GameInterface.TABLE_OTHER.tr9.td2.str = Statistic_AddValue(PChar, "Sailors_dead", 0);
	
	GameInterface.TABLE_OTHER.tr10.td1.str = XI_ConvertString("StatTreasuresFound");
	GameInterface.TABLE_OTHER.tr10.td2.str = Statistic_AddValue(PChar, "Treasure", 0);
	
	GameInterface.TABLE_OTHER.tr11.td1.str = XI_ConvertString("StatExpenses");
	GameInterface.TABLE_OTHER.tr11.td2.str = Statistic_AddValue(PChar, "Money_spend", 0);
	
	GameInterface.TABLE_OTHER.tr12.td1.str = XI_ConvertString("StatCrewPayments");
	GameInterface.TABLE_OTHER.tr12.td2.str = Statistic_AddValue(PChar, "PartitionPay", 0);
	
	GameInterface.TABLE_NATION.hr.td1.str = XI_ConvertString("StatEvents");
 	GameInterface.TABLE_NATION.hr.td2.icon.group = "NATIONSQ"
	GameInterface.TABLE_NATION.hr.td2.icon.image      = Nations[0].Name;
	GameInterface.TABLE_NATION.hr.td2.icon.width = 55;
    GameInterface.TABLE_NATION.hr.td2.icon.height = 55;
    GameInterface.TABLE_NATION.hr.td2.icon.offset = "3, 0";
 	GameInterface.TABLE_NATION.hr.td3.icon.group = "NATIONSQ"
	GameInterface.TABLE_NATION.hr.td3.icon.image      = Nations[1].Name;
	GameInterface.TABLE_NATION.hr.td3.icon.width = 55;
    GameInterface.TABLE_NATION.hr.td3.icon.height = 55;
    GameInterface.TABLE_NATION.hr.td3.icon.offset = "3, 0";
 	GameInterface.TABLE_NATION.hr.td4.icon.group = "NATIONSQ"
	GameInterface.TABLE_NATION.hr.td4.icon.image      = Nations[2].Name;
	GameInterface.TABLE_NATION.hr.td4.icon.width = 55;
    GameInterface.TABLE_NATION.hr.td4.icon.height = 55;
    GameInterface.TABLE_NATION.hr.td4.icon.offset = "3, 0";
 	GameInterface.TABLE_NATION.hr.td5.icon.group = "NATIONSQ"
	GameInterface.TABLE_NATION.hr.td5.icon.image      = Nations[3].Name;
	GameInterface.TABLE_NATION.hr.td5.icon.width = 55;
    GameInterface.TABLE_NATION.hr.td5.icon.height = 55;
    GameInterface.TABLE_NATION.hr.td5.icon.offset = "3, 0";
 	GameInterface.TABLE_NATION.hr.td6.icon.group = "NATIONSQ"
	GameInterface.TABLE_NATION.hr.td6.icon.image      = Nations[4].Name;
	GameInterface.TABLE_NATION.hr.td6.icon.width = 55;
    GameInterface.TABLE_NATION.hr.td6.icon.height = 55;
    GameInterface.TABLE_NATION.hr.td6.icon.offset = "3, 0";
	GameInterface.TABLE_NATION.hr.td7.str = XI_ConvertString("StatTotal");
	
	GameInterface.TABLE_NATION.tr1.td1.str = XI_ConvertString("StatFortsDestroyed");
	GameInterface.TABLE_NATION.tr1.td2.str = Statistic_AddValue(PChar, "eng_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td3.str = Statistic_AddValue(PChar, "fra_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td4.str = Statistic_AddValue(PChar, "spa_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td5.str = Statistic_AddValue(PChar, "hol_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td6.str = Statistic_AddValue(PChar, "pir_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td7.str = (Statistic_AddValue(PChar, "pir_KillFort", 0) +
             Statistic_AddValue(PChar, "eng_KillFort", 0) +
             Statistic_AddValue(PChar, "fra_KillFort", 0) +
             Statistic_AddValue(PChar, "spa_KillFort", 0) +
             Statistic_AddValue(PChar, "hol_KillFort", 0));
             
    GameInterface.TABLE_NATION.tr2.td1.str = XI_ConvertString("StatCitiesCaptured");
	GameInterface.TABLE_NATION.tr2.td2.str = Statistic_AddValue(PChar, "eng_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td3.str = Statistic_AddValue(PChar, "fra_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td4.str = Statistic_AddValue(PChar, "spa_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td5.str = Statistic_AddValue(PChar, "hol_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td6.str = Statistic_AddValue(PChar, "pir_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td7.str = (Statistic_AddValue(PChar, "pir_TakeTown", 0) +
             Statistic_AddValue(PChar, "eng_TakeTown", 0) +
             Statistic_AddValue(PChar, "fra_TakeTown", 0) +
             Statistic_AddValue(PChar, "spa_TakeTown", 0) +
             Statistic_AddValue(PChar, "hol_TakeTown", 0));
             
    GameInterface.TABLE_NATION.tr3.td1.str = XI_ConvertString("StatCitiesPlundered");
	GameInterface.TABLE_NATION.tr3.td2.str = Statistic_AddValue(PChar, "eng_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td3.str = Statistic_AddValue(PChar, "fra_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td4.str = Statistic_AddValue(PChar, "spa_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td5.str = Statistic_AddValue(PChar, "hol_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td6.str = Statistic_AddValue(PChar, "pir_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td7.str = (Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
             Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
             Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
             Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
             Statistic_AddValue(PChar, "hol_GrabbingTown", 0));
             
    GameInterface.TABLE_NATION.tr4.td1.str = XI_ConvertString("StatShipsCaptured");
	GameInterface.TABLE_NATION.tr4.td2.str = Statistic_AddValue(PChar, "eng_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td3.str = Statistic_AddValue(PChar, "fra_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td4.str = Statistic_AddValue(PChar, "spa_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td5.str = Statistic_AddValue(PChar, "hol_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td6.str = Statistic_AddValue(PChar, "pir_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td7.str = (Statistic_AddValue(PChar, "pir_AbordShip", 0) +
             Statistic_AddValue(PChar, "eng_AbordShip", 0) +
             Statistic_AddValue(PChar, "fra_AbordShip", 0) +
             Statistic_AddValue(PChar, "spa_AbordShip", 0) +
             Statistic_AddValue(PChar, "hol_AbordShip", 0));
             
    GameInterface.TABLE_NATION.tr5.td1.str = XI_ConvertString("StatShipsSunk");
	GameInterface.TABLE_NATION.tr5.td2.str = Statistic_AddValue(PChar, "eng_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td3.str = Statistic_AddValue(PChar, "fra_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td4.str = Statistic_AddValue(PChar, "spa_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td5.str = Statistic_AddValue(PChar, "hol_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td6.str = Statistic_AddValue(PChar, "pir_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td7.str = (Statistic_AddValue(PChar, "pir_KillShip", 0) +
             Statistic_AddValue(PChar, "eng_KillShip", 0) +
             Statistic_AddValue(PChar, "fra_KillShip", 0) +
             Statistic_AddValue(PChar, "spa_KillShip", 0) +
             Statistic_AddValue(PChar, "hol_KillShip", 0));

    Table_UpdateWindow("TABLE_SHIPCLASS");
    Table_UpdateWindow("TABLE_HUMAN");
    Table_UpdateWindow("TABLE_OTHER");
    Table_UpdateWindow("TABLE_NATION");
	
    //  ростовщики
    GameInterface.TABLE_CREDIT.hr.td1.str = XI_ConvertString("CreditCity");
	GameInterface.TABLE_CREDIT.hr.td2.str = XI_ConvertString("CreditSum");
	GameInterface.TABLE_CREDIT.hr.td3.str = XI_ConvertString("CreditDate");
	GameInterface.TABLE_CREDIT.hr.td4.str = XI_ConvertString("CreditTerm");
	GameInterface.TABLE_CREDIT.hr.td5.str = XI_ConvertString("CreditPercent");
	GameInterface.TABLE_CREDIT.select = 0;
	
    aref quests;
	aref quest;
	int  nQuestsNum;
	int  n;
	string sQuestName;
	i = 1;
    if (CheckAttribute(pchar, "Quest.Loans"))
    {
    	makearef(quests, pchar.Quest.Loans);

    	nQuestsNum = GetAttributesNum(quests);

    	for(n = 0; n < nQuestsNum; n++)
    	{
    		quest = GetAttributeN(quests,n);

    		sQuestName = GetAttributeName(quest);
    		row = "tr" + i;
    		i++;
    		GameInterface.TABLE_CREDIT.(row).td1.str = GetCityName(sQuestName);
			GameInterface.TABLE_CREDIT.(row).td2.str = MakeMoneyShow(sti(Pchar.Quest.Loans.(sQuestName).Sum), MONEY_SIGN,MONEY_DELIVER);
			GameInterface.TABLE_CREDIT.(row).td3.str = GetBookData(sti(Pchar.Quest.Loans.(sQuestName).StartDay),
                               sti(Pchar.Quest.Loans.(sQuestName).StartMonth),
                               sti(Pchar.Quest.Loans.(sQuestName).StartYear));
			GameInterface.TABLE_CREDIT.(row).td4.str = Pchar.Quest.Loans.(sQuestName).Period;
			GameInterface.TABLE_CREDIT.(row).td5.str = Pchar.Quest.Loans.(sQuestName).Interest;
        }
    }
	Table_UpdateWindow("TABLE_CREDIT");
	
	GameInterface.TABLE_DEBIT.hr.td1.str = XI_ConvertString("DepCity");
	GameInterface.TABLE_DEBIT.hr.td2.str = XI_ConvertString("DepSum");
	GameInterface.TABLE_DEBIT.hr.td3.str = XI_ConvertString("DepDate");
	GameInterface.TABLE_DEBIT.hr.td4.str = XI_ConvertString("DepPercent");
	GameInterface.TABLE_DEBIT.hr.td5.str = XI_ConvertString("DepType");
	GameInterface.TABLE_DEBIT.select = 0;
	i = 1;
    if (CheckAttribute(pchar, "Quest.Deposits")) // не треться при возврате
    {
    	makearef(quests,Characters[GetMainCharacterIndex()].Quest.Deposits);

    	nQuestsNum = GetAttributesNum(quests);

    	for(n = 0; n < nQuestsNum; n++)
    	{
    		quest = GetAttributeN(quests,n);

    		sQuestName = GetAttributeName(quest);
						
    		if (CheckAttribute(Pchar, "Quest.Deposits."+sQuestName+".Sum"))
    		{
                row = "tr" + i;
    			i++;
				GameInterface.TABLE_DEBIT.(row).td1.str = GetCityName(Pchar.Quest.Deposits.(sQuestName).City);
				GameInterface.TABLE_DEBIT.(row).td2.str = MakeMoneyShow(sti(Pchar.Quest.Deposits.(sQuestName).Sum), MONEY_SIGN,MONEY_DELIVER);
				GameInterface.TABLE_DEBIT.(row).td3.str = GetBookData(sti(Pchar.Quest.Deposits.(sQuestName).StartDay),
	                               sti(Pchar.Quest.Deposits.(sQuestName).StartMonth),
	                               sti(Pchar.Quest.Deposits.(sQuestName).StartYear));
				GameInterface.TABLE_DEBIT.(row).td4.str = Pchar.Quest.Deposits.(sQuestName).Interest;
				if(HasSubStr(sQuestName, "_type1"))
				{
					GameInterface.TABLE_DEBIT.(row).td5.str = XI_ConvertString("DebitType1");
				}
				else
				{
					GameInterface.TABLE_DEBIT.(row).td5.str = XI_ConvertString("DebitType2");
				}
			}			
        }
    }
	Table_UpdateWindow("TABLE_DEBIT");
	
	FillShipPlaceTable("TABLE_SHIP_PLACE"); // 1.2.3
	
	FillPriceListTown("TABLE_CITY");
	// tradebook --->
	TradebookFillPriceListTown("TRADEBOOK_TABLE_CITY");
	// <---
	
}

void FillShipPlaceTable(string _tabName)
{
    int     i, cn, n;
    string  row;
    ref     rCity, chref;

    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = "N";
    GameInterface.(_tabName).hr.td2.str = XI_ConvertString("Ship");
	GameInterface.(_tabName).hr.td2.textoffset = "40, 0";
    GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Rank");
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("City");
	GameInterface.(_tabName).hr.td5.str = XI_ConvertString("Location");
	GameInterface.(_tabName).hr.td6.str = XI_ConvertString("MoorDate");
	GameInterface.(_tabName).hr.td7.str = XI_ConvertString("CostPerMonth");
	GameInterface.(_tabName).hr.td7.line_space_modifier = 0.8;
    // <--
    cn = 1;
    for (n=0; n<MAX_COLONIES; n++)
	{
		rCity = &Colonies[n];
		for (i=1; i<MAX_CHARACTERS; i++)
    	{
    		makeref(chref, Characters[i]);
    		if (CheckAttribute(chref, "ShipInStockMan"))
    		{
                if (chref.ShipInStockMan == (rCity.id + "_PortMan"))
		        {
                    row = "tr" + cn;
					int iShip = sti(chref.ship.type);
					ref refBaseShip = GetRealShip(iShip);
					string sShip = refBaseShip.BaseName + refBaseShip.ship.upgrades.hull;
					GameInterface.(_tabName).(row).UserData.IDX = i; // belamour запомнить в кого тыкать будем
                    GameInterface.(_tabName).(row).td1.str = cn;
					
	                GameInterface.(_tabName).(row).td2.icon.texture = "interfaces\le\ships\" + sShip + ".tga";
	                GameInterface.(_tabName).(row).td2.icon.uv = "0,0,1,1";
	                GameInterface.(_tabName).(row).td2.icon.offset = "-2, 0";
	                GameInterface.(_tabName).(row).td2.icon.width  = 40;
				    GameInterface.(_tabName).(row).td2.icon.height = 40;
				    GameInterface.(_tabName).(row).td2.str = XI_ConvertString(refBaseShip.BaseName) + " '" + chref.Ship.Name + "'";
					GameInterface.(_tabName).(row).td2.line_space_modifier = 0.8;	
				    GameInterface.(_tabName).(row).td2.textoffset = "40, 0";
					
					GameInterface.(_tabName).(row).td3.str = sti(refBaseShip.Class) + "";
					
					GameInterface.(_tabName).(row).td4.icon.group  = "NATIONSQ";
					GameInterface.(_tabName).(row).td4.icon.image  = Nations[sti(rCity.nation)].Name;
					GameInterface.(_tabName).(row).td4.icon.width  = 40;
				    GameInterface.(_tabName).(row).td4.icon.height = 40;
				    GameInterface.(_tabName).(row).td4.icon.offset = "-2, 0";
					GameInterface.(_tabName).(row).td4.str = GetConvertStr(rCity.id + " Town", "LocLables.txt");
					GameInterface.(_tabName).(row).td4.line_space_modifier = 0.8;	
					GameInterface.(_tabName).(row).td4.textoffset = "40, 0";
					
					GameInterface.(_tabName).(row).td5.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
					
					GameInterface.(_tabName).(row).td6.str = chref.ShipInStockMan.AltDate;
					
					GameInterface.(_tabName).(row).td7.str = chref.ShipInStockMan.MoneyForShip;
    		        cn++;
		        }
    		}
        }
	}
	// Addon 2016-1 Jason Пиратская линейка. Стоянка Исла-Моны.
	for (i=1; i<MAX_CHARACTERS; i++)
	{
		makeref(chref, Characters[i]);
		if (CheckAttribute(chref, "ShipInStockMan"))
		{
			if (chref.ShipInStockMan == "Islamona_carpenter")
			{
				row = "tr" + cn;
				GameInterface.(_tabName).(row).UserData.IDX = i; // belamour запомнить в кого тыкать будем
				GameInterface.(_tabName).(row).td1.str = cn;
				GameInterface.(_tabName).(row).td2.icon.texture = "interfaces\le\ships\" + sShip + ".tga";
	            GameInterface.(_tabName).(row).td2.icon.uv = "0,0,1,1";
	            GameInterface.(_tabName).(row).td2.icon.offset = "-2, 0";
	            GameInterface.(_tabName).(row).td2.icon.width  = 40;
				GameInterface.(_tabName).(row).td2.icon.height = 40;
				GameInterface.(_tabName).(row).td2.str = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'";
				
				GameInterface.(_tabName).(row).td3.str = sti(RealShips[sti(chref.Ship.Type)].Class) + "";
				
				GameInterface.(_tabName).(row).td4.icon.group  = "NATIONSQ";
				GameInterface.(_tabName).(row).td4.icon.image  = Nations[PIRATE].Name;
				GameInterface.(_tabName).(row).td4.icon.width  = 40;
				GameInterface.(_tabName).(row).td4.icon.height = 40;
				GameInterface.(_tabName).(row).td4.icon.offset = "-2, 0";
		
				GameInterface.(_tabName).(row).td4.str = XI_ConvertString("IslaMona");
				GameInterface.(_tabName).(row).td4.textoffset = "40, 0";
				
				GameInterface.(_tabName).(row).td5.str = XI_ConvertString("IslaMona");
				
				GameInterface.(_tabName).(row).td6.str = chref.ShipInStockMan.AltDate;

				GameInterface.(_tabName).(row).td7.str = chref.ShipInStockMan.MoneyForShip;
				cn++;
			}
		}
	}
	Table_UpdateWindow(_tabName);
}

void FillPriceListTown(string _tabName)
{
    int     i, cn, n, StoreNum;
    ref     chref;
    string  row, firstId, CityId;
    aref    curItem;
    ref     rCity;
	ref		refStorage;
    
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Nation");
	GameInterface.(_tabName).hr.td2.str = XI_ConvertString("City");
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Location");
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Fullness");
	GameInterface.(_tabName).hr.td5.str = XI_ConvertString("Rent");

	cn = 1;
	for (i=1; i<MAX_CHARACTERS; i++)
	{
		makeref(chref, Characters[i]);
		if (CheckAttribute(chref, "Storage.Activate"))
		{
			row = "tr" + cn;
			CityId = chref.city;
			rCity = GetColonyByIndex(FindColony(CityId));
			StoreNum = GetStorage(CityId);
			refStorage = &stores[StoreNum];
			if (n == 0) firstId = rCity.id;
			if (chref.id == "Islamona_carpenter") // Addon 2016-1 Jason пиратская линейка
			{
				rCity.id = "IslaMona";
				firstId = "IslaMona";
				StoreNum = 29;
				refStorage = &stores[StoreNum];
			}
			GameInterface.(_tabName).(row).UserData.CityID  = rCity.id;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONSQ";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 40;
			GameInterface.(_tabName).(row).td1.icon.height = 40;
			GameInterface.(_tabName).(row).td1.icon.offset = "10, 0";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(rCity.id + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			GameInterface.(_tabName).(row).td4.str = GetStorageUsedWeight(refStorage) + " / " + iMaxGoodsStore;
			GameInterface.(_tabName).(row).td5.str = GetNpcQuestPastMonthParam(chref, "Storage.Date") * sti(chref.MoneyForStorage);
			cn++;
		}
	}
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}

void TableSelectChange()
{
	// Log_TestInfo("Click!");
	string sControl = GetEventData();
	int iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    NullSelectTable("TABLE_GOODS");
    if (CurTable == "TABLE_CITY")
    {
    	FillPriceList("TABLE_GOODS", GameInterface.(CurTable).(CurRow).UserData.CityID);
    }
	// tradebook --->
	NullSelectTable("TRADEBOOK_TABLE_GOODS");
    if (CurTable == "TRADEBOOK_TABLE_CITY")
    {
    	TradebookFillPriceList("TRADEBOOK_TABLE_GOODS", GameInterface.(CurTable).(CurRow).UserData.CityID);
    }
	// <---
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void FillPriceList(string _tabName, string  attr1)
{
    string  sGoods;
	int		StoreNum, iStoreQ;
    int     i, n;
    ref     nulChr;
    string  row;
	ref 	chref;
    ref		refStorage;
	
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Good name");
	GameInterface.(_tabName).hr.td2.str = XI_ConvertString("In the storage");
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("PackHold");
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("WeightHold");
	
	Table_Clear("TABLE_GOODS", false, true, false);
	
	n = 1;
	if (attr1 != "")
	{
		StoreNum = GetStorage(attr1);
		if(StoreNum > 0)
		{
			refStorage = &stores[StoreNum];
			for (i = 0; i < GetArraySize(&Goods); i++) 
			{
				row = "tr" + n;
				sGoods = "Gidx" + i;	
				iStoreQ = GetStorageGoodsQuantity(refStorage, i); 	
				if(iStoreQ == 0) continue;
				GameInterface.(_tabName).(row).UserData.ID = Goods[i].name;
				GameInterface.(_tabName).(row).UserData.IDX = i;
				GameInterface.(_tabName).(row).td1.icon.group = "GOODS";
				GameInterface.(_tabName).(row).td1.icon.image = Goods[i].name;
				GameInterface.(_tabName).(row).td1.icon.offset = "20, 0";
				GameInterface.(_tabName).(row).td1.icon.width = 40;
				GameInterface.(_tabName).(row).td1.icon.height = 40;
				GameInterface.(_tabName).(row).td1.textoffset = "40,0";
				GameInterface.(_tabName).(row).td1.str = XI_ConvertString(Goods[i].name);
				GameInterface.(_tabName).(row).td2.str = iStoreQ;
				GameInterface.(_tabName).(row).td3.str = Goods[i].Units;
				GameInterface.(_tabName).(row).td4.str = GetGoodWeightByType(i, iStoreQ);
				n++;
			}	
		}
	}
    Table_UpdateWindow(_tabName);
}

// tradebook --->

//  таблица: город, местоположение, актуальность
void TradebookFillPriceListTown(string _tabName)
{
	string  cityId, attr2, firstId;
    int     i, cn, n;
    ref     nulChr;
    string  row;
    aref    rootItems;
    aref    curItem;
    ref     rCity;
    
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Nation");
	GameInterface.(_tabName).hr.td2.str = XI_ConvertString("City");
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Location");
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Relevance");
    // <--
    nulChr = &NullCharacter;
    makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
    n = 1;
    firstId = "";
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
        row = "tr" + n;
		curItem = GetAttributeN(rootItems, i);
		cityId = GetAttributeName(curItem);
        // row = "tr" + n;	
		cn = FindColony(cityId);
		if (cn != -1)
		{
			rCity = GetColonyByIndex(cn);
			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).UserData.CityID  = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONSQ";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 35;
		    GameInterface.(_tabName).(row).td1.icon.height = 35;
		    GameInterface.(_tabName).(row).td1.icon.offset = "13, 2";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(cityId + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			if (CheckAttribute(nulChr, "PriceList." + cityId + ".AltDate"))
		    {
		        GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(cityId).AltDate;
		    }
		    else
		    {
		        GameInterface.(_tabName).(row).td4.str = "??.??.????";
		    }
			n++;
		}
	}
	Table_UpdateWindow(_tabName);
	TradebookFillPriceList("TRADEBOOK_TABLE_GOODS", firstId);
}

//  таблица: картинка, название, картинка экспорта, продажа, покупка, колво, пачка, вес пачки
void TradebookFillPriceList(string _tabName, string  attr1)
{
    string  sGoods;
    int     i, n;
    ref     nulChr;
    string  row;
    nulChr = &NullCharacter;
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Good name");
 	GameInterface.(_tabName).hr.td1.line_space_modifier = 0.8;
    GameInterface.(_tabName).hr.td2.str = XI_ConvertString("Type");
 	GameInterface.(_tabName).hr.td2.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.(_tabName).hr.td3.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Price buy");
	GameInterface.(_tabName).hr.td4.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td5.str = XI_ConvertString("In the store");
	GameInterface.(_tabName).hr.td5.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td6.str = XI_ConvertString("PackHold");
	GameInterface.(_tabName).hr.td6.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td7.str = XI_ConvertString("PackWeightHold");
	GameInterface.(_tabName).hr.td7.line_space_modifier = 0.8;
	if (attr1 != "")
	{
	    // <--
	    n = 1;
	    for (i = 0; i < GetArraySize(&Goods); i++)
	    {
	        row = "tr" + n;
	        sGoods = "Gidx" + i;			
	        if (sti(nulChr.PriceList.(attr1).(sGoods).TradeType) == T_TYPE_CANNONS && !bBettaTestMode) continue; // не пушки
	        
            GameInterface.(_tabName).(row).UserData.ID = Goods[i].name;
            GameInterface.(_tabName).(row).UserData.IDX = i;
            
	        GameInterface.(_tabName).(row).td1.icon.group = "GOODS";
			GameInterface.(_tabName).(row).td1.icon.image = Goods[i].name;
			GameInterface.(_tabName).(row).td1.icon.offset = "5, 0";
			GameInterface.(_tabName).(row).td1.icon.width = 40;
			GameInterface.(_tabName).(row).td1.icon.height = 40;
			GameInterface.(_tabName).(row).td1.textoffset = "40,0";
			GameInterface.(_tabName).(row).td1.str = XI_ConvertString(Goods[i].name);

	        GameInterface.(_tabName).(row).td2.icon.group = "TRADE_TYPE";
			GameInterface.(_tabName).(row).td2.icon.image = "ico_" + nulChr.PriceList.(attr1).(sGoods).TradeType;
			GameInterface.(_tabName).(row).td2.icon.offset = "5,2";
			GameInterface.(_tabName).(row).td2.icon.width = 24;
			GameInterface.(_tabName).(row).td2.icon.height = 34;

	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Buy"))
	        {
	            GameInterface.(_tabName).(row).td3.str = nulChr.PriceList.(attr1).(sGoods).Buy;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td3.str = "???";
	        }
	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Sell"))
	        {
	            GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(attr1).(sGoods).Sell;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td4.str = "???";
	        }
	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Qty"))
	        {
	            GameInterface.(_tabName).(row).td5.str = nulChr.PriceList.(attr1).(sGoods).Qty;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td5.str = "????";
	        }
	        GameInterface.(_tabName).(row).td6.str = Goods[i].Units;
			GameInterface.(_tabName).(row).td7.str = Goods[i].Weight;
	        n++;
	    }
    }
    Table_UpdateWindow(_tabName);
}
// <---
void SetFontType()
{
	if(CheckAttribute(&InterfaceStates,"FontType"))
	{
		switch (sti(InterfaceStates.FontType))
		{
			case 0:
				SetTabsFontType(1);
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TITLE", 0,"interface_quest_titleh");
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TEXT", 2,"interface_quest_texth");
			break;

			case 1:
				SetTabsFontType(2);
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TITLE", 0,"interface_quest_titlen");
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TEXT", 2,"interface_quest_textn");
			break;
			
			case 2:
				SetTabsFontType(2);
				if (currentTab == 2){
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TITLE", 0,"interface_quest_titlen");
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TEXT", 2,"interface_quest_texth");
				} else {
					SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TITLE", 0,"interface_quest_titlen");
					SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QUEST_TEXT", 2,"interface_quest_textn");
				}
			break;
		}
	}
}

void SetTabsFontType(int fontType)
{
	SetNodeUsing("TABSTR_QUEST", false);
	SetNodeUsing("TABSTR_QUESTN", false);
	SetNodeUsing("TABSTR_QUESTARJ", false);
	SetNodeUsing("TABSTR_QUESTARJN", false);
	SetNodeUsing("TABSTR_INFO", false);
	SetNodeUsing("TABSTR_INFON", false);
	SetNodeUsing("TABSTR_CASHBOOK", false);
	SetNodeUsing("TABSTR_CASHBOOKN", false);
	SetNodeUsing("TABSTR_SHIP_PLACE", false);
	SetNodeUsing("TABSTR_SHIP_PLACEN", false);
	SetNodeUsing("TABSTR_STOREBOOK", false);
	SetNodeUsing("TABSTR_STOREBOOKN", false);
	SetNodeUsing("TABSTR_TRADEBOOK", false);
	SetNodeUsing("TABSTR_TRADEBOOKN", false);
	SetNodeUsing("TABSTR_STATISTIC", false);
	SetNodeUsing("TABSTR_STATISTICN", false);
	switch (fontType)
	{
		case 1:
			SetNodeUsing("TABSTR_QUEST", true);
			SetNodeUsing("TABSTR_QUESTARJ", true);
			SetNodeUsing("TABSTR_INFO", true);
			SetNodeUsing("TABSTR_CASHBOOK", true);
			SetNodeUsing("TABSTR_SHIP_PLACE", true);
			SetNodeUsing("TABSTR_STOREBOOK", true);
			SetNodeUsing("TABSTR_TRADEBOOK", true);
			SetNodeUsing("TABSTR_STATISTIC", true);
		break;

		case 2:
			SetNodeUsing("TABSTR_QUESTN", true);
			SetNodeUsing("TABSTR_QUESTARJN", true);
			SetNodeUsing("TABSTR_INFON", true);
			SetNodeUsing("TABSTR_CASHBOOKN", true);
			SetNodeUsing("TABSTR_SHIP_PLACEN", true);
			SetNodeUsing("TABSTR_STOREBOOKN", true);
			SetNodeUsing("TABSTR_TRADEBOOKN", true);
			SetNodeUsing("TABSTR_STATISTICN", true);
		break;
	}
}