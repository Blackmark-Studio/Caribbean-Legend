/// BOAL меню корабль
/// Sith новое меню
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню кнопками Q и E

int nCurScrollNum;
ref xi_refCharacter;
int shipIndex;
int currentCannonsMode = 0;
int curNationIdx;

string CurTable, CurRow;
int iSelected; // курсор в таблице

// для выкидывания
int iShipQty, iUnits, iCurGoodsIdx;

string sMessageMode;
void InitInterface_R(string iniName, ref _chr) // _chr нужно для читового просмотра НПС в море
{
    InterfaceStack.SelectMenu_node = "LaunchShipState"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleShip";
	// belamour корабль из журнала -->
	if(CheckAttribute(pchar,"SystemInfo.ShowShip"))
	{
		int chrIdx = sti(pchar.SystemInfo.ShowShip);
		xi_refCharacter = GetCharacter(chrIdx);
	}
	else
	{
		xi_refCharacter = _chr;
	}
	
	FillShipsScroll();
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	CreateString(true,"ShipName","",FONT_NORMAL,COLOR_MONEY, 435,355,SCRIPT_ALIGN_CENTER,1.6);
	CreateString(true,"ShipBaseName","",FONT_NORMAL,COLOR_NORMAL, 435,485,SCRIPT_ALIGN_CENTER,1.6);
	
	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
	SetEventHandler("FlagsPress","FlagsProcess",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("confirmShipChangeName","confirmShipChangeName",0);
    SetEventHandler("undoShipChangeName","undoShipChangeName",0);
	SetEventHandler("CheckForRename","CheckForRename",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("GoodsExitCancel", "GoodsExitCancel", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ShipChange", "ShipChange", 0);
	SetEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu", 0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("GoToShipChange", "GoToShipChange", 0);
	SetEventHandler("ExitCannonsMenu", "ExitCannonsMenu", 0);
	
	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);
	SetEventHandler("ExitPartitionWindow", "ExitPartitionWindow", 0);
    
    XI_RegistryExitKey("IExit_F2");

    SetNewGroupPicture("CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
	
	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("GoodsHold");
	GameInterface.TABLE_LIST.hr.td1.textoffset = "40,0";
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("QuantityHold");
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("WeightHold");
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("PackHold");
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("PackWeightHold");
	GameInterface.TABLE_LIST.hr.td5.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.select = 0;
	SetCurrentNode("SHIPS_SCROLL");
	OnShipScrollChange();
	sMessageMode = "";
	ref chref = GetMainCharacter();
	curNationIdx = sti(chref.nation);
    SetNewNation(0);
	SetAlertMarks(xi_refCharacter);
}

// гуляем по меню кнопками Q и E
void ProcessInterfaceControls() 
{
	string sCurNode = GetCurrentNode();
	string controlName = GetEventData();
	if(sCurNode != "EDIT_BOX")
	{
		if (controlName == "InterfaceGoLeft") {
			IDoExit(RC_INTERFACE_INVENTORY);
		}
		if (controlName == "InterfaceGoRight") {
			IDoExit(RC_INTERFACE_TO_QUESTBOOK);
		}
		if (controlName == "InterfaceInfoSwitch") {
			currentCannonsMode = (currentCannonsMode + 1) % 2;
			SetCannonsMode(currentCannonsMode + 1);
		}
	}
}

// показываем/скрываем управление орудиями
void SetCannonsMode(int nMode)
{
	switch (nMode)
	{
	    case 1: HideCannonsMenu(); break;// скрываем меню пушек
	    case 2: ShowCannonsMenu(); break;// показываем меню пушек
	}
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	UpdatePlayerSquadronPower(); // Обновим, если что-то менялось

	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
	DelEventHandler("FlagsPress","FlagsProcess");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("confirmShipChangeName","confirmShipChangeName");
    DelEventHandler("undoShipChangeName","undoShipChangeName");
	DelEventHandler("CheckForRename","CheckForRename");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("GoodsExitCancel", "GoodsExitCancel");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ShipChange", "ShipChange");
	DelEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("GoToShipChange", "GoToShipChange");
	DelEventHandler("ExitCannonsMenu", "ExitCannonsMenu");
	
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	DelEventHandler("ExitPartitionWindow", "ExitPartitionWindow");
	// belamour вернуться во вкладку журнала, если пришли оттуда -->
	if(CheckAttribute(pchar,"SystemInfo.ShowShip"))
	{
		interfaceResultCommand = RC_INTERFACE_TO_QUESTBOOK;
	} 
	else
	{
		interfaceResultCommand = exitCode;
	}
	// <-- belamour
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
	if(CheckAttribute(pchar, "questTemp.SantaMisericordia") && !GetAchievement("ach_CL_139"))
	{
		if(ach139condition()) Achievment_Set("ach_CL_139");
	}
}
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
        case "LEFTCHANGE_NATION":
    		if(comName=="activate" || comName=="click")
    		{
				if (!CheckAttribute(pchar, "DisableChangeFlagMode"))
				{
					SetNewNation(-1);
				}
    		}
    	break;

    	case "RIGHTCHANGE_NATION":
    		if(comName=="activate" || comName=="click")
    		{
                if (!CheckAttribute(pchar, "DisableChangeFlagMode"))
                {
					SetNewNation(1);
				}
    		}
    	break;
		/////  пушки -->
        case "CANNONS_OK":
			if(comName=="click")
			{
				HideCannonsMenu(); // применить уже сущ изменения
				OnShipScrollChange();
				Ship_ResearchCannons(xi_refCharacter);
			}
		break;
		
		case "CANNONS_REMOVE_ALL":
			if(comName=="click")
			{
			    CanonsRemoveAll();   
			}
		break;
		
		case "CANNONS_SET_ALL":
			if(comName=="click")
			{
			    CanonsSetAll(xi_refCharacter);
			}
		break;
		
		case "CANNONS_LEFT_F":
			if(comName=="click")
			{
				ChangeCannonNum("cannonf", -1);
			}
		break;
		case "CANNONS_RIGHT_F":
			if(comName=="click")
			{
				ChangeCannonNum("cannonf", 1);
			}
		break;
		
		case "CANNONS_LEFT_B":
			if(comName=="click")
			{
				ChangeCannonNum("cannonb", -1);
			}
		break;
		case "CANNONS_RIGHT_B":
			if(comName=="click")
			{
				ChangeCannonNum("cannonb", 1);
			}
		break;
		
		case "CANNONS_LEFT_R":
			if(comName=="click")
			{
				ChangeCannonNum("cannonr", -1);
			}
		break;
		case "CANNONS_RIGHT_R":
			if(comName=="click")
			{
				ChangeCannonNum("cannonr", 1);
			}
		break;
		
		case "CANNONS_LEFT_L":
			if(comName=="click")
			{
				ChangeCannonNum("cannonl", -1);
			}
		break;
		case "CANNONS_RIGHT_L":
			if(comName=="click")
			{
				ChangeCannonNum("cannonl", 1);
			}
		break;
		/////  пушки <--
		case "CREW_MORALE_BUTTON":
			if(comName=="click")
			{
			    ShowMoraleMessage();
			}
		break;
		
		case "PARTITION_OK":
			if(comName=="click")
			{
			    DoPartitionPay();
			}
		break;
		
		case "CREW_PARTITION":
			if(comName=="click")
			{
			    ShowPartitionWindow();
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
		// мины 07.07.07
		case "QTY_BOMB_BUTTON":
			if(comName=="click")
			{
			    SetMineFree(xi_refCharacter, 1);
			    iShipQty = GetCargoGoods(xi_refCharacter, GOOD_POWDER);
			    OnShipScrollChange();
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
			    nodName = "I_ABILITIES";
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
		// belamour если пришли из кораблей на приколе
		if(CheckAttribute(pchar,"SystemInfo.ShowShip")) DeleteAttribute(pchar,"SystemInfo.ShowShip"); 
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	// boal new menu 31.12.04 -->
}
///////////////////////////////////////////////////////////////////////////////////////////
void FillShipsScroll()
{
	nCurScrollNum = -1;
	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}

	string attributeName;
	string shipName;
	int iShipType, cn;
	GameInterface.SHIPS_SCROLL.ImagesGroup.t0 = "BLANK_SHIP";

	GameInterface.SHIPS_SCROLL.BadTex1 = 0;
	GameInterface.SHIPS_SCROLL.BadPic1 = "Not Used";
	int m = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(xi_refCharacter, i);
		if(cn != -1)
		{
			AddShipPictureToList("SHIPS_SCROLL.ImagesGroup", GetCharacter(cn));
			iShipType = sti(characters[cn].ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				ref realShip = GetRealShip(iShipType);
				attributeName = "pic" + (m+1);
				iShipType = sti(RealShips[iShipType].basetype);
				shipName = ShipsTypes[iShipType].Name;

				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#"+" "+ShipsTypes[iShipType].Class;
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "ship";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("SHIPS_SCROLL.ImagesGroup","SHIPS_"+shipName+"_"+realShip.ship.upgrades.hull);
				m++;
			}
			else
			{
				attributeName = "pic" + (m+1);
				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP";
				m++;
			}
		}
	}

	GameInterface.SHIPS_SCROLL.ListSize = m;
	GameInterface.SHIPS_SCROLL.NotUsed = 5 - m + 1;
}


void ProcessFrame()
{
	string attributeName;
	int iCharacter;

	string sNode = GetCurrentNode();
	if(sNode == "SHIPS_SCROLL")
	{
		if(sti(GameInterface.SHIPS_SCROLL.current)!= nCurScrollNum)
		{
			DeleteAttribute(&GameInterface, "TABLE_LIST.BackUp");
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			attributeName = "pic" + (nCurScrollNum+1);

			iCharacter = sti(GameInterface.SHIPS_SCROLL.(attributeName).character);

			if(iCharacter > 0)
			{
				string sChrId = characters[iCharacter].id;

				xi_refCharacter = characterFromID(sChrId);
				shipIndex= nCurScrollNum+ 1;
				if (shipIndex< 0)
				{
					shipIndex= 0;
				}
				if (sti(xi_refCharacter.ship.type) == SHIP_NOTUSED) 
				{
					shipIndex= -1;
				}
				// boal оптимизация скилов -->
			    DelBakSkillAttr(xi_refCharacter);
			    ClearCharacterExpRate(xi_refCharacter);
			    RefreshCharacterSkillExpRate(xi_refCharacter);
			    
			    SetEnergyToCharacter(xi_refCharacter);
			    // boal оптимизация скилов <--
				OnShipScrollChange();
			} 
			else 
			{
				shipIndex= -1;
			}
			return;
		}
	}
}

void OnShipScrollChange()
{
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
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\le\portraits\512\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_NAME", GetFullName(xi_refCharacter));
	SetFormatedText("HERO_RANK",xi_refCharacter.Rank);
	// нулим все формы, тк корабля может не быть
	SetFormatedText("SHIP_RANK","");
	SetFormatedText("CREW_QTY","");
	SetFormatedText("FOOD_SHIP", "");
	SetFormatedText("FOOD", "");
	SetFormatedText("RUM_SHIP", "");
	SetFormatedText("MONEY_SHIP", "");
	SetFormatedText("CREW_MORALE_TEXT", "");
	SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(1));
	SetSelectable("CREW_MORALE_BUTTON", false);
	Table_Clear("TABLE_LIST", false, true, false);
	Table_Clear("TABLE_OTHER", false, true, false);
	Table_Clear("TABLE_CREW", false, true, false);
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
	int iShip = sti(xi_refCharacter.ship.type);
	
	SetNodeUsing("CREW_PARTITION", false);
	SetNodeUsing("CREW_MORALE_BUTTON", false);
	SetNodeUsing("FLAGPIC", false);
	SetNodeUsing("FLAG_BTN", false);
	SetNodeUsing("LEFTCHANGE_NATION", false);
	SetNodeUsing("RIGHTCHANGE_NATION", false);
	SetNodeUsing("SUPPLY",false);
	SetNodeUsing("SUPPLY2",false);
	SetNodeUsing("SUPPLYGOLD",false);
		
	if (iShip != SHIP_NOTUSED)
	{
		// оптимизация скилов -->
	    DelBakSkillAttr(xi_refCharacter);
	    ClearCharacterExpRate(xi_refCharacter);
	    RefreshCharacterSkillExpRate(xi_refCharacter);
	    // оптимизация скилов <--
	    
		if (CheckAttribute(xi_refCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(xi_refCharacter.Ship.Cargo.RecalculateCargoLoad))
		{
			RecalculateCargoLoad(xi_refCharacter);
			xi_refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
		}
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName + refBaseShip.ship.upgrades.hull;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\le\ships\" + sShip + ".tga");
		GameInterface.strings.shipbasename = XI_ConvertString(refBaseShip.BaseName);
		GameInterface.strings.shipname = xi_refCharacter.ship.name;

		GameInterface.edit_box.str = xi_refCharacter.ship.name;	
		SetFormatedText("SHIP_RANK", refBaseShip.Class);
		FillGoodsTable();
		
		SetShipOTHERTable2("TABLE_OTHER", xi_refCharacter);
		// еда -->
		int iColor, iFood;
		string sText;
		// в эскадре
		if (GetCompanionQuantity(pchar) > 1) // больше 1 ГГ
		{
			iFood = CalculateFood();
			sText = sText + FindRussianDaysString(iFood);
			SetFormatedText("FOOD", sText);
			if(iFood >= 5)
			{
				iColor = argb(255,255,255,192);
			}
			if(iFood > 10)
			{
				iColor = argb(255,192,255,192);
			}
			if(iFood < 5)
			{
				iColor = argb(255,255,192,192);
			}
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FOOD", 8,-1,iColor);
			SetNodeUsing("SUPPLY2",true);
		}
		// еда -->
		// на одном корабле
		SetFoodShipInfoShort(xi_refCharacter, "FOOD_SHIP");
		SetRumShipInfoShort(xi_refCharacter,"RUM_SHIP");
		SetNodeUsing("SUPPLY",true);
		// еда <--
		SetFormatedText("MONEY_SHIP", FindRussianMoneyString(GetSalaryForShip(xi_refCharacter)) + " " + XI_ConvertString("per month"));
		SetNodeUsing("SUPPLYGOLD",true);
		SetFormatedText("CREW_QTY", ""+GetCrewQuantity(xi_refCharacter));
		if (GetCrewQuantity(xi_refCharacter) > GetOptCrewQuantity(xi_refCharacter) || GetCrewQuantity(xi_refCharacter) < GetMinCrewQuantity(xi_refCharacter))
		{
			iColor = argb(255,255,64,64);
		}
		else
		{
			iColor = argb(255,255,255,255);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREW_QTY", 8,-1,iColor);
		SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(stf(xi_refCharacter.ship.crew.morale)));
		SetFormatedText("CREW_MORALE_TEXT", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(xi_refCharacter.Ship.crew.morale))));
		if (sti(xi_refCharacter.Ship.crew.morale) < MORALE_MAX && GetCrewQuantity(xi_refCharacter) > 0)
		{
			SetSelectable("CREW_MORALE_BUTTON", true);
		}
		SetNodeUsing("BAR_Sailors", true);
		SetNodeUsing("BAR_Cannoners", true);
		SetNodeUsing("BAR_Soldiers", true);
		SetNodeUsing("BAR_CrewMoral", true);

		SetCrewExpTable(xi_refCharacter, "TABLE_CREW", "BAR_Sailors", "BAR_Cannoners", "BAR_Soldiers");
		//BAR_CrewMoral
		GameInterface.StatusLine.BAR_CrewMoral.Max   = 100;
    	GameInterface.StatusLine.BAR_CrewMoral.Min   = 0;
    	GameInterface.StatusLine.BAR_CrewMoral.Value = sti(xi_refCharacter.Ship.crew.morale);
    	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_CrewMoral", 0);
		
    	if (xi_refCharacter.id == pchar.id)
    	{
    		SetNodeUsing("CREW_PARTITION", true);
			SetNodeUsing("CREW_MORALE_BUTTON", true);
			SetNodeUsing("FLAGPIC", true);
			SetNodeUsing("LEFTCHANGE_NATION", true);
			SetNodeUsing("RIGHTCHANGE_NATION", true);
    	}
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\le\ships\empty_ship.tga");
		// GameInterface.edit_box.str = XI_Convertstring("NoneBoat");
		SetNodeUsing("BAR_Sailors", false);
		SetNodeUsing("BAR_Cannoners", false);
		SetNodeUsing("BAR_Soldiers", false);
		SetNodeUsing("BAR_CrewMoral", false);
	}
	SetShipPerks();
	Table_UpdateWindow("TABLE_LIST");
	Table_UpdateWindow("TABLE_OTHER");
	Table_UpdateWindow("TABLE_CREW");
}

void confirmShipChangeName()
{
	if (shipIndex== -1) return;
	xi_refcharacter.ship.name = GameInterface.edit_box.str;
	GameInterface.edit_box.str = xi_refcharacter.ship.name;
	SetCurrentNode("SHIPS_SCROLL");
	if (bSeaActive) RefreshBattleInterface();
}

void undoShipChangeName()
{
	if (shipIndex== -1) return;
	GameInterface.edit_box.str = xi_refcharacter.ship.name;
	xi_refcharacter.ship.name = GameInterface.edit_box.str;
	SetCurrentNode("SHIPS_SCROLL");
}

void CheckForRename()
{
	if (GetShipRemovable(xi_refCharacter) == true && shipIndex!= -1)
	{
		SetCurrentNode("EDIT_BOX");
	}
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int picW = 180;
	int picH = 180;
	int iItem;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	int iShip;
	ref refBaseShip;
	float fRepairPercent;
	
	bool  bShowHint = true;
	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
			if (shipIndex != -1)
			{
			    iShip = sti(xi_refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetShipDescr(refBaseShip);
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat", "ShipsDescribe.txt");
			}
		break; 
		
		case "SHIP_PERK1":
			string sPerkName1 = GetShipSpecDesc(xi_refCharacter);
			sGroup = "PERKS_SHIPS";
			sGroupPicture = sPerkName1;
			sHeader = GetConvertStr(sPerkName1, "ShipsPerksDescribe.txt");
			sText1 = GetConvertStr(sPerkName1 + "_desc", "ShipsPerksDescribe.txt");
			sText3 = GetConvertStr(sPerkName1 + "_desc2", "ShipsPerksDescribe.txt");
		break;

		case "SHIP_PERK2":
			string sPerkName2 = GetShipTraitDesc(xi_refCharacter);
			sGroup = "PERKS_SHIPS";
			sGroupPicture = sPerkName2;
			sHeader = GetConvertStr(sPerkName2, "ShipsPerksDescribe.txt");
			sText1 = GetConvertStr(sPerkName2 + "_desc", "ShipsPerksDescribe.txt");
			sText3 = GetConvertStr(sPerkName2 + "_desc2", "ShipsPerksDescribe.txt");
		break;

		case "FLAGPIC":
			sHeader = XI_ConvertString("Nation");
			sText1 = GetRPGText("Nation_hint");
		break;
		
		case "SHIPS_SCROLL":
			if (shipIndex != -1)
			{
			    iShip = sti(xi_refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetShipDescr(refBaseShip);
				sText2 = GetRPGText("shipChoose_hint");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat", "ShipsDescribe.txt");
			}
		break; 
		
		case "MAIN_CHARACTER_PICTURE":
			// отдельная форма
			bShowHint = false;
			ShowRPGHint();
		break;  
		
		case "TABLE_LIST":
			sHeader = XI_Convertstring("Goods");
			sText1  = GetRPGText("GoodsCargo_hint");	
		break; 
		
		case "TABLE_CREW":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break; 
		
		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(xi_refCharacter.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		    {
		    	ref Cannon = GetCannonByType(sti(xi_refCharacter.Ship.Cannons.Type));
		    	sText1 = sText1 + NewStr() + "***" + NewStr() + XI_ConvertString("Type") +": " + XI_ConvertString(GetCannonType(sti(xi_refCharacter.Ship.Cannons.Type)));
		    	sText1 = sText1 + NewStr() + XI_ConvertString("Caliber") + ": " + XI_ConvertString("caliber" + GetCannonCaliber(sti(xi_refCharacter.Ship.Cannons.Type)));
		    	sText1 = sText1 + NewStr() + XI_ConvertString("Fire range2") + ": "  + sti(Cannon.FireRange);
		    	sText1 = sText1 + NewStr() + XI_ConvertString("CannonsDamage") + ": x" + FloatToString(stf(Cannon.DamageMultiply), 1);
		    	sText1 = sText1 + NewStr() + XI_ConvertString("CannonsTime") + ": " + sti(GetCannonReloadTime(Cannon)) + " " + XI_ConvertString("sec.");
		    	sText1 = sText1 + NewStr() + XI_ConvertString("Weight") + ": " + sti(Cannon.Weight) + " " + XI_ConvertString("cwt") + NewStr() + "***";
		    	
		    	sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(xi_refCharacter.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(xi_refCharacter.Ship.Cannons.Type));
		    }
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText2 = XI_ConvertString("other_crew_descr");
				sText2 = sText2 + NewStr() + XI_ConvertString("other_crew_descr_max") + ": " + GetMaxCrewQuantity(xi_refCharacter);
			} 
			// процент ремонта
			if (sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull")
				{
					if (GetHullPercent(xi_refCharacter) < 100.0 )
					{
						sText2 = XI_ConvertString("RepairShipShort") + " " + FloatToString(GetHullRepairDay(xi_refCharacter, false),2) + XI_ConvertString("RepairShip_descr") + makeint(GetHullRepairDay(xi_refCharacter, true)) + XI_ConvertString("RepairShip_descr_planks");
					}
					sText3 = xiStr("Hull") + ": " + GetCurrentShipHP(xi_refCharacter) +  " / " + GetCharacterShipHP(xi_refCharacter) + " (" + GetCharacterShipBaseHP(xi_refCharacter) + ")";
				}
				if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails")
				{
					if (GetSailPercent(xi_refCharacter) < GetAllSailsDamagePercent(xi_refCharacter) )
					{
						sText2 = XI_ConvertString("RepairShipShort") + " " + FloatToString(GetSailRepairDay(xi_refCharacter, false),2) + XI_ConvertString("RepairShip_descr") + makeint(GetSailRepairDay(xi_refCharacter, true))+ XI_ConvertString("RepairShip_descr_canvas");
					}
					sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(xi_refCharacter), 1) + " %";
				}
			}
			// трюм
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText3 = XI_ConvertString("Used") + ": " + FloatToString((stf(GetCargoLoad(xi_refCharacter))  /  stf(GetCargoMaxSpace(xi_refCharacter))) * 100.0, 1)+ " %";
			}
		break; 
		
		case "CREW_PARTITION":
			sHeader = XI_Convertstring("PartitionCaption");
			sText1  = GetRPGText("Partition_hint");
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
		case "FOOD_SHIP":
			sHeader = XI_Convertstring("FoodShipInfoShort");
			sText1 = GetConvertStr("Food_descr", "GoodsDescribe.txt");
		break;
		case "RUM_SHIP":
			sHeader = XI_Convertstring("RumShipInfoShort");
			sText1 = GetConvertStr("Rum_descr", "GoodsDescribe.txt");
		break;
		case "MONEY_SHIP":
			sHeader = XI_Convertstring("CostPerMonth");
			sText1 = GetRPGText("Partition_hint");
		break;
		case "FOOD":
			sHeader = XI_Convertstring("FoodSquadronInfoShort");
			sText1 = GetConvertStr("Food_descr", "GoodsDescribe.txt");
		break;
	}
	if (bShowHint)
	{
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, picW, picH);
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    NullSelectTable("TABLE_LIST");
    NullSelectTable("TABLE_OTHER");
    NullSelectTable("TABLE_CREW");
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("OFFICER_INFO_WINDOW", false);
		XI_WindowDisable("OFFICER_INFO_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", false);
		sMessageMode = "";
	}
}

void ShowRPGHint()
{
	SetSPECIALMiniTable("TABLE_SMALLSKILL", xi_refCharacter);
    SetOTHERMiniTable("TABLE_SMALLOTHER", xi_refCharacter);
    SetFormatedText("OFFICER_NAME", GetFullName(xi_refCharacter));
	        
	XI_WindowShow("OFFICER_INFO_WINDOW", true);
	XI_WindowDisable("OFFICER_INFO_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";
}

void FillGoodsTable()
{
	int n, i, qty;
	string row;
	ref rShip;
	string sGood;
	aref refGoods;
	
	n = 1;
	if (!CheckAttribute(&GameInterface, "TABLE_LIST.BackUp"))
	{
		GameInterface.TABLE_LIST.select = 0;
		GameInterface.TABLE_LIST.top    = 0;
		GameInterface.TABLE_LIST.BackUp = true;
	}
    for (i = 0; i< GOODS_QUANTITY; i++)
	{
        row = "tr" + n;
		sGood = Goods[i].name;
		qty = GetCargoGoods(xi_refCharacter, i);
		if (qty <= 0) continue; // только не нули

		GameInterface.TABLE_LIST.(row).index = i;
		
		GameInterface.TABLE_LIST.(row).td2.str = qty;
		GameInterface.TABLE_LIST.(row).td3.str = GetGoodWeightByType(i, qty);
		GameInterface.TABLE_LIST.(row).td4.str = Goods[i].Units;
		GameInterface.TABLE_LIST.(row).td5.str = Goods[i].Weight;

        GameInterface.TABLE_LIST.(row).td1.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td1.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td1.icon.offset = "-5, -5";
		GameInterface.TABLE_LIST.(row).td1.icon.width = 50;
		GameInterface.TABLE_LIST.(row).td1.icon.height = 50;
		GameInterface.TABLE_LIST.(row).td1.textoffset = "40,0";
		GameInterface.TABLE_LIST.(row).td1.line_space_modifier = 0.8;
		GameInterface.TABLE_LIST.(row).td1.str = XI_ConvertString(sGood);
		n++;
	}
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void ShowItemInfo()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) // нет товара вообще
	{
	    ShowGoodsInfo(sti(GameInterface.(CurTable).(CurRow).index));
		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", true);
		SetCurrentNode("QTY_CANCEL_BUTTON");
		if (GetRemovable(xi_refCharacter))
		{
		    SetSelectable("QTY_OK_BUTTON", true);
		}
		else
		{
		    SetSelectable("QTY_OK_BUTTON", false);
		}
		// мины
	    if (sti(GameInterface.(CurTable).(CurRow).index) == GOOD_POWDER)
	    {
	        SetNodeUsing("QTY_BOMB_BUTTON", true);
	        if (bSeaActive && !bAbordageStarted && GetRemovable(xi_refCharacter))
	        {
	            SetSelectable("QTY_BOMB_BUTTON", true);
	        }
	        else
	        {
	            SetSelectable("QTY_BOMB_BUTTON", false);
	        }
		}
		else
		{
		    SetNodeUsing("QTY_BOMB_BUTTON", false);
		}
	}
}

void GoodsExitCancel()
{
	
	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode("TABLE_LIST");
	// пересчитаем новые пареметры от веса
	if (iShipQty != GetCargoGoods(xi_refCharacter, iCurGoodsIdx))
	{
		SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty); // вернём обратно
		OnShipScrollChange();
	}
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;

	int lngFileID = LanguageOpenFile("GoodsDescribe.txt");
	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
	string goodsDescr = GetAssembledString( LanguageConvertString(lngFileID,goodName+"_descr"), &Goods[iGoodIndex]);
    goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
	              ", " + XI_ConvertString("PackHolds") + " " + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits  = sti(Goods[iGoodIndex].Units);
	if(checkAttribute(pchar, "ship.cargo.goods." + GoodName + ".isquest"))
	{
		string sTradeQ = pchar.ship.cargo.goods.(GoodName).isquest.quantity;
		string sColony = pchar.ship.cargo.goods.(GoodName).isquest.colony;
		goodsDescr += NewStr() + XI_ConvertString("YouNeedToDelivery") + sTradeQ + XI_ConvertString("QuantityOfGoodsToColony") + XI_ConvertString("Colony"+sColony) + ".";
	}
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", goodsDescr);
	LanguageCloseFile(lngFileID);
	
	iShipQty = GetCargoGoods(xi_refCharacter, iGoodIndex);
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty))
    SetFormatedText("QTY_INFO_STORE_QTY", its(GetGoodWeightByType(iGoodIndex, iShipQty)));
}

void TransactionOK()
{
	int nTradeQuantity;
	confirmChangeQTY_EDIT();
	
	nTradeQuantity = sti(GameInterface.qty_edit.str);

    SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty);
    
    if (!GetRemovable(xi_refCharacter)) return;
	if (nTradeQuantity > 0)
	{
		DropGoodsToSeaFromInterface(iCurGoodsIdx, nTradeQuantity); // остаётся плавать в море
		iShipQty = GetCargoGoods(xi_refCharacter, iCurGoodsIdx);
	}
	GoodsExitCancel();
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	int  iWeight;
	GameInterface.qty_edit.str = abs(sti(GameInterface.qty_edit.str));  // приведение к числу
	
	string GoodName = goods[iCurGoodsIdx].name;
	
    // проверка на колво доступное -->
    if (sti(GameInterface.qty_edit.str) > iShipQty)
    {
        GameInterface.qty_edit.str = iShipQty;
    }
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty - sti(GameInterface.qty_edit.str)))
	SetFormatedText("QTY_INFO_STORE_QTY", its(GetGoodWeightByType(iCurGoodsIdx, (iShipQty - sti(GameInterface.qty_edit.str)))));
	// прикидываем место в трюме
	iWeight = sti(GameInterface.qty_edit.str);
	SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty);
	if (iWeight > 0)
	{
		RemoveCharacterGoods(xi_refCharacter, iCurGoodsIdx, iWeight);
	}
	OnShipScrollChange();
}

void REMOVE_ALL_BUTTON()  // продать все
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = iShipQty;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + iUnits);
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - iUnits);
	if (sti(GameInterface.qty_edit.str) < 0) GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void DropGoodsToSeaFromInterface(int iGoodIndex, int iQuantity)
{
	ref rGood;
	string sGood;

	sGood = Goods[iGoodIndex].name;

	if (CheckAttribute(xi_refCharacter, "Ship.Cargo.Goods."+sGood))
	{		
		RemoveCharacterGoods(xi_refCharacter, iGoodIndex, iQuantity);
		if (bSeaActive && !bAbordageStarted)  // море, но не каюта
		{
			iQuantity = iQuantity / sti(Goods[iGoodIndex].Units);
	
			int iSwimQuantity = makeint(iQuantity/3 + rand(makeint(iQuantity/3)) + rand(makeint(iQuantity/3)));
	
			if(iSwimQuantity < 1)
			{
				iSwimQuantity = 1;
			}
	
			RecalculateCargoLoad(xi_refCharacter);
	        xi_refCharacter.Tmp.SpeedRecall = 0; // чтоб пересчитались скорость и маневр
	        
			if (CheckAttribute(&Goods[iGoodIndex], "Swim")) 
			{ 
				float fTime = stf(Goods[iGoodIndex].Swim.Time);
				string sModel = Goods[iGoodIndex].Swim.Model;
	
				fTime = fTime + (frnd() - 0.5) * fTime / 2.0;
	
				AISeaGoods_AddGood(xi_refCharacter, sGood, sModel, fTime * 60.0, iSwimQuantity);
			}
			PlaySound("Ships\jakor_002.wav");
		}
	}
}

void ShipChange()
{
	if(CheckAttribute(pchar,"SystemInfo.ShowShip")) return;
	bool bOk;
	bool sOk = false;
	if (xi_refCharacter.id != pchar.id && sti(pchar.ship.type) != SHIP_NOTUSED)
	{
		SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChange1")); // Перейти в режим обмена между кораблями?
		bOk = !bSeaActive && LAi_grp_alarmactive;
		if (bDisableMapEnter || bOk || chrDisableReloadToLocation)
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChange2")); // Во время боя обмен с кораблями возможен только борт к борту
			sOk = true;
		}
		if (bSeaActive && GetShipEscape())
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChange3")); // Использование способности 'спасение на шлюпке' позволяет обмениваться с кораблями в бою. Продолжить?
			sOk = false;
		}
		if (!GetRemovable(xi_refCharacter))
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChange4")); // Обмен с кораблём этого компаньона невозможен
			sOk = true;
		}
		if (sti(pchar.ship.type) == SHIP_NOTUSED)
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChange5")); // Обмен невозможен. У героя нет корабля
			sOk = true;
		}
		sMessageMode = "ShipChange";
		ShowShipChangeMenu();
		if (sOk)
		{	
			SetNodeUsing("REMOVE_ACCEPT_OFFICER",false);
			SetNodeUsing("REMOVE_CANCEL_OFFICER",false);
			SetNodeUsing("REMOVE_OK_OFFICER",true);
			SetCurrentNode("REMOVE_OK_OFFICER");
		} else {
			SetNodeUsing("REMOVE_ACCEPT_OFFICER",true);
			SetNodeUsing("REMOVE_CANCEL_OFFICER",true);
			SetNodeUsing("REMOVE_OK_OFFICER",false);
			SetCurrentNode("REMOVE_ACCEPT_OFFICER");
		}
	}
}

void ExitShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void ShowShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	// SetCurrentNode("REMOVE_ACCEPT_OFFICER");
}

bool GetShipEscape()
{
    if (CheckCharacterPerk(PChar, "ShipEscape") && GetHullPercent(PChar) <= 15.0)
    {
        return true;
    }
    return false;
}

void ShowOtherClick()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".UserData.ID") && GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType")
	{
		ShowCannonsMenu();
	}
}

void GoToShipChange()
{
	if (sMessageMode == "MoraleMessage") // мораль
	{
		AddMoneyToCharacter(pchar, -GetCharacterRaiseCrewMoraleMoney(xi_refCharacter));
		Statistic_AddValue(pchar, "PartitionPay", GetCharacterRaiseCrewMoraleMoney(xi_refCharacter));
		AddCrewMorale(xi_refCharacter, 10);
		ChangeCharacterComplexReputation(pchar,"authority", 2);
		ExitShipChangeMenu();
		OnShipScrollChange();
	}
	if (sMessageMode == "ShipChange") // обмен с кораблём
	{
		pchar.SystemInfo.OurChar = true; // belamour выход обратно из меню обмена
		pchar.TransferChar = xi_refCharacter.index;
		InterfaceStates.ReloadMenuExit = true;
		IDoExit(RC_INTERFACE_ANY_EXIT);
		PostEvent("LaunchIAfterFrame",1,"sl", "TransferMain", 2);
	}
}

void ShowMoraleMessage()
{
	int  sum = GetCharacterRaiseCrewMoraleMoney(xi_refCharacter);
	SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("RaiseMorale"));
	SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("RaiseMoraleMoney") + FindRussianMoneyString(sum));
	
	if (sum <= sti(pchar.money))
	{
		SetSelectable("REMOVE_ACCEPT_OFFICER", true);
	}
	else
	{
		SetSelectable("REMOVE_ACCEPT_OFFICER", false);
	}
	sMessageMode = "MoraleMessage";
	ShowShipChangeMenu();
	SetNodeUsing("REMOVE_OK_OFFICER",false);
}

void ShowCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", true);
	XI_WindowDisable("CANNONS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("CANNONS_CANCEL");

    SetBackupCannons(); // запомнить, для отката
    
    bool bOk  = !bSeaActive && LAi_grp_alarmactive;
    bool bOk2 = bAbordageStarted && !bCabinStarted; // в абордаже не жать пушки
	bool bOk3 = bDisableMapEnter && !CheckAttribute(pchar, "GenQuest.MapClosedNoBattle") // Jason 020712
	if (bOk3 || bOk || bOk2)
    { // идёт бой, запрет смены орудий
    	SetSelectable("CANNONS_OK", false);
	}
	else
	{
		SetSelectable("CANNONS_OK", true);
	}
	if (!GetRemovable(xi_refCharacter))
	{
		SetSelectable("CANNONS_OK", false);
	}
    DeleteAttribute(&GameInterface, "CANNONS_TABLE.BackUp")
    CannonsMenuRefresh();
}
void CannonsMenuRefresh()
{
	int idx = GetCannonGoodsIdxByType(sti(xi_refCharacter.Ship.Cannons.Type));
	if (idx != -1)
	{
	    SetNewGroupPicture("CANNONS_PIC", "GOODS", Goods[idx].Name);
		SetFormatedText("CANNONS_TEXT", XI_ConvertString(Goods[idx].Name));
		SetFormatedText("CANNONS_QTY_F", its(GetBortCannonsQty(xi_refCharacter, "cannonf")));
		SetFormatedText("CANNONS_QTY_B", its(GetBortCannonsQty(xi_refCharacter, "cannonb")));
		SetFormatedText("CANNONS_QTY_R", its(GetBortCannonsQty(xi_refCharacter, "cannonr")));
		SetFormatedText("CANNONS_QTY_L", its(GetBortCannonsQty(xi_refCharacter, "cannonl")));
		/// всего GetCannonsNum(xi_refCharacter)
	}
	else
	{
		SetNewGroupPicture("CANNONS_PIC", "GOODS", "");
		SetFormatedText("CANNONS_TEXT", "");
		SetFormatedText("CANNONS_QTY_F", "0");
		SetFormatedText("CANNONS_QTY_B", "0");
		SetFormatedText("CANNONS_QTY_R", "0");
		SetFormatedText("CANNONS_QTY_L", "0");
	}
	FillCannonsTable();
}
void ExitCannonsMenu()
{
	HideCannonsMenu();
	
	GetBackupCannons(); // отмена
	OnShipScrollChange();
}

void HideCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", false);
	XI_WindowDisable("CANNONS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

/// установить орудия по борту (сперва расчитать дельту было стало - лишнее в запасы)
void SetCannonsToBort(ref chr, string sBort, int iQty)
{
	int     curQty = GetBortCannonsQty(chr, sBort);
	int     maxQty = GetBortCannonsQtyMax(chr, sBort);
	int     i, delta;
	string  attr;
	int     center, left, right; // счетчики орудий для распределения
	bool    bLeft; // направление хода
	float	ax = 0.0;
	float 	az = 0.0;
		
	if (iQty > maxQty) iQty = maxQty; 
	if (iQty < 0) iQty = 0;
	
	int idx = GetCannonGoodsIdxByType(sti(chr.Ship.Cannons.Type));
    delta = iQty - curQty;
    if (delta > 0)
    {
    	if (GetCargoGoods(chr, idx) < delta) iQty = curQty + GetCargoGoods(chr, idx);
    }
	if (iQty > curQty)
	{ // списать со склада
		RemoveCharacterGoodsSelf(chr, idx, (iQty - curQty));
	}
	else
	{
		if (iQty < curQty)
		{// лишние на склад
			SetCharacterGoods(chr, idx, GetCargoGoods(chr, idx) + (curQty - iQty)); // этот метод, тк перегруз может быть, а  AddCharacterGoodsSimple режет перегруз
		}
	}
	// нулим колво пушек на борту и распределяем заново от центра (как они на модели по номерам не знаю, допуск, что подряд)
	for (i = 0; i < maxQty; i++)
	{
		attr = "c" + i;
		chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0; // поломана на 100%, не палит, те нет её
	}
	// распределяем
	if (iQty > 0)		 
	{
		center = makeint(maxQty / 2); // целочисленное деление
		left   = center - 1;
		right  = center;
		i = 0; // сколько распределили уже
		bLeft = true;
		while (i < iQty)
		{
			if (bLeft)
			{
				if (left >= 0)
				{
					attr = "c" + left;
					left--;
				}
				else
				{
					attr = "c" + right;	
					right++;
				}
				if (right < maxQty) bLeft = false;
			}
			else
			{
				if (right < maxQty)
				{
					attr = "c" + right;	
					right++;
				}
				else
				{
					attr = "c" + left;
					left--;
				}
				if (left >= 0) bLeft = true;
			}				
			chr.Ship.Cannons.borts.(sBort).damages.(attr) = 0.0; // новая, не битая
			i++;
		}	
	}
	RecalculateCargoLoad(chr);  // пересчет, тк пушки снялись
/*	
	if(SetHeel_XZ(chr,  &ax, &az))
	{
		SendMessage(chr, "lff", MSG_SHIP_SET_HEEL_XZ, ax, az); 
	}	
*/	
}

void CanonsRemoveAll()
{
    SetCannonsToBort(xi_refCharacter, "cannonf", 0);
    SetCannonsToBort(xi_refCharacter, "cannonb", 0);
    SetCannonsToBort(xi_refCharacter, "cannonr", 0);
    SetCannonsToBort(xi_refCharacter, "cannonl", 0);

	OnShipScrollChange();
    CannonsMenuRefresh();
}

// бакап значений, до применения
void SetBackupCannons()
{
	aref    arTo, arFrom;
	NullCharacter.ShipBak.Cannons = "";
	NullCharacter.ShipBak.Cargo   = "";
	
	makearef(arTo,   NullCharacter.ShipBak.Cannons);
	makearef(arFrom, xi_refCharacter.Ship.Cannons);
	CopyAttributes(arTo, arFrom);
	
	makearef(arTo,   NullCharacter.ShipBak.Cargo);
	makearef(arFrom, xi_refCharacter.Ship.Cargo);
	CopyAttributes(arTo, arFrom);
}

void GetBackupCannons()
{
	aref    arTo, arFrom;
	
	makearef(arFrom,   NullCharacter.ShipBak.Cannons);
	makearef(arTo, xi_refCharacter.Ship.Cannons);
	CopyAttributes(arTo, arFrom);
	
	makearef(arFrom,   NullCharacter.ShipBak.Cargo);
	makearef(arTo, xi_refCharacter.Ship.Cargo);
	CopyAttributes(arTo, arFrom);
}

void CanonsSetAll(ref chr)
{
    if (GetCannonQuantity(chr) <= 0) return;
	// сначала все убрать
    if (GetCannonsNum(chr) > 0) 
    {
		SetCannonsToBort(chr, "cannonf", 0);
	    SetCannonsToBort(chr, "cannonb", 0);
	    SetCannonsToBort(chr, "cannonr", 0);
	    SetCannonsToBort(chr, "cannonl", 0);
    }
    //новый калибр назначить
    if (CurTable == "CANNONS_TABLE" && CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
    {
		chr.Ship.Cannons.Type = sti(Goods[sti(GameInterface.(CurTable).(CurRow).index)].CannonIdx);
	}
    // потом все выставить раскидав по бортам
    int idx = GetCannonGoodsIdxByType(sti(chr.Ship.Cannons.Type));
    int fb, lb, rb, bb;
    int qty;
    
    if (idx != -1)
    {
    	qty = GetCargoGoods(chr, idx);
    	
		rb = GetBortCannonsQtyMax(chr, "cannonr");    	
    	if (rb  > (qty / 2)) rb = qty / 2;
    	qty = qty - rb;
    	if (qty < 0) qty = 0;
    	   	
		lb = GetBortCannonsQtyMax(chr, "cannonl");
    	if (lb > qty) lb = qty;
    	qty = qty - lb;
    	if (qty < 0) qty = 0;
    	   	
		bb = GetBortCannonsQtyMax(chr, "cannonb");
    	if (bb > qty) bb = qty;
    	qty = qty - bb;
    	if (qty < 0) qty = 0;
    	
		fb = GetBortCannonsQtyMax(chr, "cannonf");	
    	if (fb > qty) fb = qty;
		SetCannonsToBort(chr, "cannonf", fb);
	    SetCannonsToBort(chr, "cannonb", bb);
	    SetCannonsToBort(chr, "cannonr", rb);
	    SetCannonsToBort(chr, "cannonl", lb);
    }
    // рефреш
    OnShipScrollChange();
    CannonsMenuRefresh();
}

void ChangeCannonNum(string sBort, int add)
{
    SetCannonsToBort(xi_refCharacter, sBort, GetBortCannonsQty(xi_refCharacter, sBort) + add);
    OnShipScrollChange();
	CannonsMenuRefresh();
}

void FillCannonsTable()
{
	int n, i, qty;
	string row;
	ref rShip;
	string sGood;
	aref refGoods;

	n = 1;
	Table_Clear("CANNONS_TABLE", false, true, false);
	GameInterface.CANNONS_TABLE.hr.td1.str = XI_ConvertString("CannonsHold");
	GameInterface.CANNONS_TABLE.hr.td2.str = XI_ConvertString("CannonsQty");
	GameInterface.CANNONS_TABLE.hr.td3.str = XI_ConvertString("CannonsDist");
	GameInterface.CANNONS_TABLE.hr.td4.str = XI_ConvertString("CannonsDamage");
	GameInterface.CANNONS_TABLE.hr.td5.str = XI_ConvertString("CannonsTime");
	
	if (!CheckAttribute(&GameInterface, "CANNONS_TABLE.BackUp"))
	{
		GameInterface.CANNONS_TABLE.select = 0;
		GameInterface.CANNONS_TABLE.top    = 0;
		GameInterface.CANNONS_TABLE.BackUp = true;
	}
	if (GetCannonQuantity(xi_refCharacter) > 0)
	{
	    for (i = 0; i< GOODS_QUANTITY; i++)
		{
	        row = "tr" + n;
			sGood = Goods[i].name;
			qty = GetCargoGoods(xi_refCharacter, i);
			if (qty <= 0) continue; // только не нули

	        if (!CheckAttribute(&Goods[i], "type")) continue;
	        if (sti(Goods[i].type) != T_TYPE_CANNONS) continue;

	        if (GetCannonCaliberNominal(sti(Goods[i].CannonIdx)) > GetMaximumCaliber(xi_refCharacter)) continue;
			GameInterface.CANNONS_TABLE.(row).index = i;

			GameInterface.CANNONS_TABLE.(row).td2.str = qty;
			GameInterface.CANNONS_TABLE.(row).td3.str = sti(Goods[i].FireRange);
			GameInterface.CANNONS_TABLE.(row).td4.str = "x"+FloatToString(stf(Goods[i].DamageMultiply), 1);
			GameInterface.CANNONS_TABLE.(row).td5.str = sti(Goods[i].ReloadTime);

	        GameInterface.CANNONS_TABLE.(row).td1.icon.group = "GOODS";
			GameInterface.CANNONS_TABLE.(row).td1.icon.image = sGood;
			GameInterface.CANNONS_TABLE.(row).td1.icon.offset = "0, 0";
			GameInterface.CANNONS_TABLE.(row).td1.icon.width = 40;
			GameInterface.CANNONS_TABLE.(row).td1.icon.height = 40;
			GameInterface.CANNONS_TABLE.(row).td1.textoffset = "40,0";
			GameInterface.CANNONS_TABLE.(row).td1.str = XI_ConvertString(sGood);
			n++;
		}
	}
	Table_UpdateWindow("CANNONS_TABLE");
}

void ShowPartitionWindow()
{
    string str;
	string sTitul = "";
	int	HowGower = 0;

	if (isMainCharacterPatented())
	{
		sTitul = GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur));
//		HowGower = Partition_GetSetting("Part_Gower") + (MOD_SKILL_ENEMY_RATE);
	}
	
	str = XI_ConvertString("CurDate") + GetDateString() + " " + GetTimeString() + NewStr();
	if(CheckAttribute(pchar, "paymentdate"))
	{
		str += XI_ConvertString("PrevPaymentDate") + pchar.paymentdate + NewStr();
	}	
	str += sTitul + " " + GetFullName(pchar) + NewStr() + XI_ConvertString("Rank") + ": " + sti(pchar.rank) + NewStr();
	str += XI_ConvertString("m_Complexity") + ": " + GetLevelComplexity(MOD_SKILL_ENEMY_RATE) + NewStr() +
			XI_ConvertString("OurMoney") + FindRussianMoneyString(sti(pchar.money)) + NewStr() + "*****" + NewStr();
    str += XI_ConvertString("CurMonthParts") + NewStr() + XI_ConvertString("CaptainPart") + GetPartitionAmount("Partition.MonthPart.Hero") + NewStr() +
		  XI_ConvertString("OfficersPart") + GetPartitionAmount("Partition.MonthPart.Officers") + NewStr() +
		  XI_ConvertString("SailorsPart") + GetPartitionAmount("Partition.MonthPart.Crew") + NewStr() + 		  
		   "*****" + NewStr() +
		  XI_ConvertString("CurMonthDebt") + GetPartitionAmount("Partition.MonthPart") + NewStr() +	
		  XI_ConvertString("StateDebt") + GetPartitionAmount("Partition.MonthPart.Gower") + NewStr();
	str += "*****" + NewStr() + XI_ConvertString("PrevMonthDebt") + GetPartitionAmount("CrewPayment");

	SetFormatedText("PARTITION_WINDOW_TEXT", str);
    SetSelectable("PARTITION_OK", false);
	if (GetPartitionAmount("Partition.MonthPart") > 0 || GetPartitionAmount("CrewPayment") > 0)
	{
		if (sti(Pchar.Money) > 0)
		{
			SetSelectable("PARTITION_OK", true);
		}
	}
	XI_WindowShow("PARTITION_WINDOW", true);
	XI_WindowDisable("PARTITION_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("PARTITION_CANCEL");
}

void ExitPartitionWindow()
{
	XI_WindowShow("PARTITION_WINDOW", false);
	XI_WindowDisable("PARTITION_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void DoPartitionPay()
{
	int sum = 0;
	int sum_gow = 0;
	if (GetPartitionAmount("Partition.MonthPart") > 0 || GetPartitionAmount("CrewPayment") > 0)
	if (GetPartitionAmount("CrewPayment") > 0)
	{
	    sum = GetPartitionAmount("CrewPayment");
	    if (sti(Pchar.Money) < sum) sum = sti(Pchar.Money);
        Pchar.CrewPayment = sti(Pchar.CrewPayment) - sum;
        if (sti(Pchar.CrewPayment) <= 0) DeleteAttribute(Pchar, "CrewPayment");
	}
	else
	{
		// долг перед командой
		if (GetPartitionAmount("Partition.MonthPart") > 0)
		{
		    sum = GetPartitionAmount("Partition.MonthPart");
		    if (sti(Pchar.Money) < sum) sum = sti(Pchar.Money);
	        Pchar.Partition.MonthPart = sti(Pchar.Partition.MonthPart) - sum;
	        AddCrewMorale(xi_refCharacter, 2);
			ChangeCharacterComplexReputation(pchar,"authority", 2); 
		}
		// долг перед государством
		if (GetPartitionAmount("Partition.MonthPart.Gower") > 0)
		{
		    sum_gow = GetPartitionAmount("Partition.MonthPart.Gower");
		    if (sti(Pchar.Money) < sum_gow) sum_gow = sti(Pchar.Money);
	        Pchar.Partition.MonthPart.Gower = sti(Pchar.Partition.MonthPart.Gower) - sum_gow;
		}
	}
	pchar.paymentdate = GetDateString() + " " + GetTimeString();
	AddMoneyToCharacter(Pchar, - (sum + sum_gow));
	Statistic_AddValue(pchar, "PartitionPay", sum + sum_gow);
	if(sum >= 3000) AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, makefloat(sum) / 3000.0);
	OnShipScrollChange();
	ExitPartitionWindow();
}

int GetPartitionAmount(string _param)
{
    if (!CheckAttribute(Pchar, _param)) return 0;
    return sti(Pchar.(_param));
}


// функция для table other из interface utils --->

void SetShipOTHERTable2(string _tabName, ref _chr)
{
    int     i;
	string  row;
	float   fTmp;

    int iShip = sti(_chr.ship.type);
	ref refBaseShip = GetRealShip(iShip);
		
    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=9; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 35;
    	GameInterface.(_tabName).(row).td1.icon.height = 35;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.textoffset = "2,0";
		GameInterface.(_tabName).(row).td3.align = "right";
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Hull";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Hull";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Hull");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.ship.hp) + " / " + sti(refBaseShip.hp);
    if (!CheckAttribute(&RealShips[iShip], "Tuning.HP")) 
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,255,255,255);
	}
	else 
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,128,255,255);
	}

	GameInterface.(_tabName).tr2.UserData.ID = "Sails";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Sails";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Sails");
	GameInterface.(_tabName).tr2.td3.str = sti(_chr.ship.sp) + " / " + sti(refBaseShip.sp);

    GameInterface.(_tabName).tr3.UserData.ID = "Speed";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "Speed";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Speed");
	if (IsCompanion(_chr))
	{
		GameInterface.(_tabName).tr3.td3.str = FloatToString(FindShipSpeed(_chr),2) + " / " + FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr3.td3.str = FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.SpeedRate")) 
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,128,255,255);
	}	
	

    GameInterface.(_tabName).tr4.UserData.ID = "Maneuver";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Maneuver";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Maneuver");
	if (IsCompanion(_chr))
	{
  		GameInterface.(_tabName).tr4.td3.str = FloatToString((stf(refBaseShip.turnrate) * FindShipTurnRate(_chr)), 2) + " / " + FloatToString(stf(refBaseShip.TurnRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr4.td3.str = FloatToString(stf(refBaseShip.TurnRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.TurnRate")) 
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,128,255,255);
	}

	GameInterface.(_tabName).tr5.UserData.ID = "AgainstWind";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "AgainstWind";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("AgainstWind");
	
	fTmp = acos(1.0 - FindShipWindAgainstSpeed(_chr)) * 180.0/PI;
	GameInterface.(_tabName).tr5.td3.str = makeint(180.0 - fTmp) + " / " + (makeint(fTmp));
	
	if (!CheckAttribute(&RealShips[iShip], "Tuning.WindAgainst")) 
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,128,255,255);
	}
	
	
	RecalculateCargoLoad(_chr);
	GameInterface.(_tabName).tr6.UserData.ID = "Capacity";
	GameInterface.(_tabName).tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr6.td1.icon.image = "Capacity";
	GameInterface.(_tabName).tr6.td2.str = XI_ConvertString("Capacity");
	GameInterface.(_tabName).tr6.td3.str = GetCargoLoad(_chr) + " / " + GetCargoMaxSpace(_chr);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.Capacity")) 
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,128,255,255);
	}
	
	GameInterface.(_tabName).tr7.UserData.ID = "Crew";
	GameInterface.(_tabName).tr7.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr7.td1.icon.image = "Crew";
	GameInterface.(_tabName).tr7.td2.str = XI_ConvertString("Crew");
	GameInterface.(_tabName).tr7.td3.str = GetCrewQuantity(_chr) + " : "+ sti(refBaseShip.MinCrew) +" / " + sti(refBaseShip.OptCrew);	
	if (!CheckAttribute(&RealShips[iShip], "Tuning.MaxCrew")) 
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,128,255,255);
	}
	
	GameInterface.(_tabName).tr8.UserData.ID = "sCannons";
	GameInterface.(_tabName).tr8.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr8.td1.icon.image = "Caliber";
	GameInterface.(_tabName).tr8.td2.str = XI_ConvertString("sCannons"); //XI_ConvertString("Caliber");
	GameInterface.(_tabName).tr8.td3.str = XI_ConvertString("caliber" + refBaseShip.MaxCaliber) + " / " + sti(refBaseShip.CannonsQuantity);
	
	if (!CheckAttribute(&RealShips[iShip], "Tuning.Cannon")) 
	{
		GameInterface.(_tabName).tr8.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr8.td3.color = argb(255,128,255,255);
	}
		
	GameInterface.(_tabName).tr9.UserData.ID = "CannonType";
	GameInterface.(_tabName).tr9.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr9.td1.icon.image = "Cannons";
	GameInterface.(_tabName).tr9.td2.str = XI_ConvertString(GetCannonType(sti(_chr.Ship.Cannons.Type)) + "s2");
	
	if (sti(_chr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
	{
		if(GetCannonsNum(_chr) > 0)
		{
		GameInterface.(_tabName).tr9.td3.str = XI_ConvertString("caliber" + GetCannonCaliber(sti(_chr.Ship.Cannons.Type))) + " / " + GetCannonsNum(_chr);
	}
	else
	{
			GameInterface.(_tabName).tr9.td3.str = GetCannonsNum(_chr);
		}	
	}
	else
	{
	    GameInterface.(_tabName).tr9.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}
// <---

void FlagsProcess()
{
	// boal 04.04.2004 -->
	bool bTmpBool = true;
	
	if (CheckAttribute(pchar, "DisableChangeFlagMode")) return; // нефиг менять файл за 3 секунды сразу
	
	if (!bBettaTestMode)
	{
    	// if(LAi_group_IsActivePlayerAlarm()) bTmpBool = false;
    	// if(!LAi_IsCharacterControl(GetMainCharacter())) bTmpBool = false;
		// if(GetCharacterShipType(pchar) == SHIP_NOTUSED) bTmpBool = false;
    	if (bLandInterfaceStart)  bTmpBool = false; // на суше нельзя в принципе
    	if (bSeaActive && !CheckEnemyCompanionDistance2GoAway(false)) bTmpBool = false; // компаньон под ударом
	}
	if (bDisableMapEnter || !bTmpBool)
	{
		if (!bBettaTestMode)
        {
            PlaySound("interface\knock.wav");
            return;
        }
	}
	// смена флага
	Sea_ClearCheckFlag(); // сбросить всем в море проверку смотрения на флаг.
	pchar.DisableChangeFlagMode = true; //закрываем Флаг
	DoQuestFunctionDelay("FreeChangeFlagMode", 5.0); // ролик + запас
	
	switch (curNationIdx)
	{
    	case ENGLAND:	EnglandProcess();	break;
    	case FRANCE:	FranceProcess();	break;
    	case SPAIN:		SpainProcess();		break;
    	case PIRATE:	PirateProcess();	break;
    	case HOLLAND:	HollandProcess();	break;
	}
}

void SetNewNation(int add)
{
    ref   mchar = GetMainCharacter();
    bool  ok, ok2, ok3;
    
    curNationIdx = curNationIdx + add;
    if (curNationIdx < 0) curNationIdx = 4;
    if (curNationIdx > 4) curNationIdx = 0;
    SetNewGroupPicture("FLAGPIC", "NATIONS", GetNationNameByType(curNationIdx));
    
    if (IsCharacterPerkOn(mchar,"FlagPir")  ||
	    IsCharacterPerkOn(mchar,"FlagEng")  ||
		IsCharacterPerkOn(mchar,"FlagFra")  ||
		IsCharacterPerkOn(mchar,"FlagSpa")  ||
		IsCharacterPerkOn(mchar,"FlagHol"))
    {
		SetNodeUsing("FLAG_BTN",true);
		if (!bBettaTestMode)
		{
			ok3 = bSeaActive && !CheckEnemyCompanionDistance2GoAway(false);
			if (bDisableMapEnter || bLandInterfaceStart || ok3) SetSelectable("FLAG_BTN",false);
		}
        ok  = !IsCharacterPerkOn(mchar,"Flag" + NationShortName(curNationIdx)) && (sti(mchar.nation) != curNationIdx);
        ok2 =  true;
        if (isMainCharacterPatented())
        {
            ok2 = (sti(Items[sti(mchar.EquipedPatentId)].Nation) != curNationIdx);
        }
        if (ok && ok2)
        {
            SetNewNation(add);
        }
        if (sti(mchar.nation) == curNationIdx)
        {
			SetNodeUsing("FLAG_BTN",false);
        }
    }
    else
    {
        SetNodeUsing("FLAG_BTN",false);
	    SetNodeUsing("RIGHTCHANGE_NATION",false);
	    SetNodeUsing("LEFTCHANGE_NATION",false);
    }
}
void PirateProcess()
{
    PChar.GenQuest.VideoAVI        = "Pirate";
    PChar.GenQuest.VideoAfterQuest = "pir_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
	ProcessExitCancel();
}

void EnglandProcess()
{
    PChar.GenQuest.VideoAVI        = "England";
    PChar.GenQuest.VideoAfterQuest = "eng_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
    ProcessExitCancel();
}

void FranceProcess()
{
    PChar.GenQuest.VideoAVI        = "France";
    PChar.GenQuest.VideoAfterQuest = "fra_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
	ProcessExitCancel();
}

void SpainProcess()
{
    PChar.GenQuest.VideoAVI        = "Spain";
    PChar.GenQuest.VideoAfterQuest = "spa_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
    ProcessExitCancel();
}

void HollandProcess()
{
    PChar.GenQuest.VideoAVI        = "Holland";
    PChar.GenQuest.VideoAfterQuest = "hol_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
	ProcessExitCancel();
}

void SetShipPerks()
{
	string pictureGroup = "PERKS_SHIPS";
	string perkName1, perkName2;
	SetNodeUsing("SHIP_PERK1",false);
	SetNodeUsing("SHIP_PERK2",false);

	int iShip = sti(xi_refCharacter.ship.type);
	if(iShip != SHIP_NOTUSED) 
	{
		perkName1 = GetShipSpecDesc(xi_refCharacter);
		perkName2 = GetShipTraitDesc(xi_refCharacter);
		SetNewGroupPicture("SHIP_PERK1", pictureGroup, perkName1);
		SetNewGroupPicture("SHIP_PERK2", pictureGroup, perkName2);
		if(perkName1 != "") SetNodeUsing("SHIP_PERK1",true);
		if(perkName2 != "") SetNodeUsing("SHIP_PERK2",true);
	}
}