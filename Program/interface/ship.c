#include "interface\utils\common_header.c"
#include "interface\utils\ship_perks.c"
#include "interface\utils\modifiers.c"
#include "interface\utils\cannons_health.c"
#include "interface\utils\cannons_stats.c"
#include "interface\utils\cannons_grid.c"
#include "interface\utils\ship_common.c"
#include "interface\utils\popup_error.c"
#include "interface\utils\popup_confirmation.c"
#include "interface\utils\universal_input.c"

#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню кнопками Q и E

int nCurScrollNum;
int nCurScrollCaptainNum;
ref xi_refCharacter;
int shipIndex;
int currentCannonsMode = 0;
int goodsMode = 0;
bool holdRaisedEstimationState = false; // для бара повышения морали/опыта
int currentCannonGoodIdx = -1;

string CurTable, CurRow;
int iSelected; // курсор в таблице

// для выкидывания
int iShipQty, iUnits, iCurGoodsIdx;

float fSpeeds[SHIP_SPEEDPOINT_QUANTITY];

string sMessageMode;
void InitInterface_R(string iniName, ref _chr) // _chr нужно для читового просмотра НПС в море
{
	InterfaceStack.SelectMenu_node = "LaunchShipState"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleShip";
	// belamour корабль из журнала -->
	if(CheckAttribute(pchar,"SystemInfo.ShowShip"))
	{
		int chrIdx = int(pchar.SystemInfo.ShowShip);
		xi_refCharacter = GetCharacter(chrIdx);
	}
	else
	{
		xi_refCharacter = _chr;
	}
	SetWindRosePoints();
	
	FillShipsScroll();
	
	SetEventHandler("Event_GetWindRosePoints", "GetWindRosePoints", 0);
	SetEventHandler("Event_GetGradientRingColor", "GetSpeedColor", 0);
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("confirmShipChangeName","confirmShipChangeName",0);
	SetEventHandler("undoShipChangeName","undoShipChangeName",0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
	SetEventHandler("CheckForRename","CheckForRename",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("ShowRPGHint","ShowRPGHint",0);
	SetEventHandler("MouseRClickUp","ExitRPGHint",0);
	SetEventHandler("HideInfoWindow","HideInfoWindow",0);
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
	
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("ExitPartitionWindow", "ExitPartitionWindow", 0);
	SetEventHandler("XI_ShipChangeCaptainClose", "XI_ShipChangeCaptainClose", 0);
	SetEventHandler("XI_ShipChangeCaptainConfirm", "XI_ShipChangeCaptainConfirm", 0);
	SetEventHandler("Event_NodeMouseEffect", "MouseEffect", 0);
	XI_RegistryExitKey("IExit_F2");

	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("GoodsHold");
	GameInterface.TABLE_LIST.hr.td1.icon = XI_ConvertString("GoodsHold");
	GameInterface.TABLE_LIST.hr.td1.icon.group = "HELP_ICONS";
	GameInterface.TABLE_LIST.hr.td1.icon.image = "HelpLight";
	GameInterface.TABLE_LIST.hr.td1.icon.offset = "2,6";
	GameInterface.TABLE_LIST.hr.td1.icon.width = 35;
	GameInterface.TABLE_LIST.hr.td1.icon.height = 35;
	GameInterface.TABLE_LIST.hr.td1.textoffset = "40,0";
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("QuantityHold");
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("WeightHold");
	GameInterface.TABLE_LIST.select = 0;
	SetCurrentNode("SHIPS_SCROLL");
	OnShipScrollChange();
	sMessageMode = "";
	SetControlsTabMode(0);

	XI_InitUniversalInput();
	XI_SetArrowsInputHandler("QTY_OK_BUTTON", &ADD_BUTTON, &REMOVE_BUTTON);
	XI_SetArrowsInputHandler("QTY_CANCEL_BUTTON", &ADD_BUTTON, &REMOVE_BUTTON);
	XI_SetClickInputHandler("QTY_REMOVE_BUTTON", "QTY_ADD_BUTTON", &REMOVE_BUTTON, &ADD_BUTTON);

	XI_SetClickHandler("SET_CANNONS_F", &SetCannons);
	XI_SetClickHandler("SET_CANNONS_B", &SetCannons);
	XI_SetClickHandler("SET_CANNONS_RL", &SetCannons);
	XI_SetClickHandler("REMOVE_CANNONS_F", &RemoveCannons);
	XI_SetClickHandler("REMOVE_CANNONS_B", &RemoveCannons);
	XI_SetClickHandler("REMOVE_CANNONS_RL", &RemoveCannons);

	XI_SetUniversalInputTooltip("QTY_EDIT_BOX", "QTY_WINDOW");
}

void RemoveCannons(string bortName = "")
{
	if (bortName == "")
	{
		bortName = "cannonl";
		if (XI_UniversalInputCurrentNode == "REMOVE_CANNONS_F") bortName = "cannonf";
		else if (XI_UniversalInputCurrentNode == "REMOVE_CANNONS_B") bortName = "cannonB";
	}

	if (bortName == "cannonl")
	{
		SetCannonsToBort(xi_refCharacter, "cannonl", 0);
		SetCannonsToBort(xi_refCharacter, "cannonr", 0);
	}
	else SetCannonsToBort(xi_refCharacter, bortName, 0);
	CannonsMenuRefresh();
}

void SetCannons()
{
	string bortName = "cannonl";
	if (XI_UniversalInputCurrentNode == "SET_CANNONS_F") bortName = "cannonf";
	else if (XI_UniversalInputCurrentNode == "SET_CANNONS_B") bortName = "cannonB";

	ref selectedGood = &Goods[currentCannonGoodIdx];
	int inStock = GetCargoGoods(xi_refCharacter, currentCannonGoodIdx);
	int beforeInstalled = inStock;
	int installedNow = 0;
	bool caliberChanged = false;
	int defaultCaliber = xi_refCharacter.Ship.Cannons.Type$int(CANNON_TYPE_NONECANNON);

	if (bortName == "cannonl")
	{
		caliberChanged = xi_refCharacter.Ship.Cannons.cannonl.Type$int(defaultCaliber) != int(selectedGood.CannonIdx);
		installedNow = GetBortCannonsQty(xi_refCharacter, "cannonl") + GetBortCannonsQty(xi_refCharacter, "cannonr");
		int maxCannons = GetBortCannonsQtyMax(xi_refCharacter, "cannonl") + GetBortCannonsQtyMax(xi_refCharacter, "cannonr");
		if (installedNow == maxCannons && !caliberChanged)
		{
			RemoveCannons("cannonl");
			return;
		}

		SetCannonsToBort(xi_refCharacter, "cannonl", 0);
		SetCannonsToBort(xi_refCharacter, "cannonr", 0);
		inStock = GetCargoGoods(xi_refCharacter, currentCannonGoodIdx);
		if (int(inStock * 0.5) > int(installedNow * 0.5) || caliberChanged)
		{
			xi_refCharacter.Ship.Cannons.cannonl.Type = selectedGood.CannonIdx;
			xi_refCharacter.Ship.Cannons.cannonr.Type = selectedGood.CannonIdx;
			SetCannonsToBort(xi_refCharacter, "cannonl", int(inStock * 0.5));
			SetCannonsToBort(xi_refCharacter, "cannonr", int(inStock * 0.5));
			xi_refCharacter.Ship.Cannons.Type = selectedGood.CannonIdx; // для совместимости со старым кодом ставим и общий калибр
			PlaySoundEvent(XI_ShipCannonInstallSoundEffect(inStock));
		}
	}
	else
	{
		installedNow = GetBortCannonsQty(xi_refCharacter, bortName);
		caliberChanged = xi_refCharacter.Ship.Cannons.(bortName).Type$int(defaultCaliber) != int(selectedGood.CannonIdx);
		
		if (installedNow == GetBortCannonsQtyMax(xi_refCharacter, bortName) && !caliberChanged)
		{
			RemoveCannons(bortName);
			return;
		}
		SetCannonsToBort(xi_refCharacter, bortName, 0);
		xi_refCharacter.Ship.Cannons.(bortName).Type = selectedGood.CannonIdx;
		inStock = GetCargoGoods(xi_refCharacter, currentCannonGoodIdx);
		if (inStock == installedNow && !caliberChanged)
		{
			RemoveCannons(bortName);
			return;
		}
		SetCannonsToBort(xi_refCharacter, bortName, inStock);
		PlaySoundEvent(XI_ShipCannonInstallSoundEffect(inStock));
	}

	CannonsMenuRefresh(bortName);
}

string XI_ShipCannonInstallSoundEffect(int qty)
{
	if (qty < 6) return "interface/installing_cannon_1";
	if (qty > 12) return "interface/installing_cannon_3";
	return "interface/installing_cannon_2";
}

// гуляем по меню кнопками Q и E
void ProcessInterfaceControls() 
{
	string sCurNode = GetCurrentNode();
	string controlName = GetEventData();
	bool IsMainWindowEnabled = XI_IsWindowEnable("MAIN_WINDOW");
	
	if(sCurNode != "EDIT_BOX")
	{
		if (IsMainWindowEnabled)
		{
			if (controlName == "IAction" || controlName == "ILeft" || controlName == "IRight") SetCurrentNode("SHIPS_SCROLL");
		}
		if (controlName == "InterfaceGoLeft") {
			IDoExit(RC_INTERFACE_INVENTORY);
		}
		if (controlName == "RaiseMorale" && IsMainWindowEnabled) {
			if (XI_CanRaiseForChr(xi_refCharacter, "morale")) XI_ShowRaiseMoralePopup();
			else PlaySound("interface/knock.wav");
		}
		if (controlName == "RaiseExp" && IsMainWindowEnabled) {
			if (XI_CanRaiseForChr(xi_refCharacter, "exp")) XI_ShowRaiseExpPopup();
			else PlaySound("interface/knock.wav");
		}
		if (controlName == "InterfaceGoLeft") {
			IDoExit(RC_INTERFACE_INVENTORY);
		}
		if (controlName == "InterfaceGoRight") {
			IDoExit(RC_INTERFACE_TO_QUESTBOOK);
		}
		if (controlName == "InterfaceInfoSwitch") {
			if (!IsMainWindowEnabled && currentCannonsMode == 0) return;
			currentCannonsMode = (currentCannonsMode + 1) % 2;
			SetCannonsMode(currentCannonsMode + 1);
		}
		if (controlName == "InterfaceTabSwitch")
		{
			if (!IsMainWindowEnabled) return;
			goodsMode = !goodsMode;
			SetControlsTabMode(goodsMode);
			FillSuppliesTable(goodsMode, xi_refCharacter);
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
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("confirmShipChangeName","confirmShipChangeName");
	DelEventHandler("undoShipChangeName","undoShipChangeName");
	DelEventHandler("CheckForRename","CheckForRename");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("ShowRPGHint","ShowRPGHint");
	DelEventHandler("MouseRClickUp","ExitRPGHint");
	DelEventHandler("HideInfoWindow","HideInfoWindow");
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
	DelEventHandler("eTabControlPress","procTabChange");
	
	DelEventHandler("ExitPartitionWindow", "ExitPartitionWindow");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");
	DelEventHandler("XI_ShipChangeCaptainClose", "XI_ShipChangeCaptainClose");
	DelEventHandler("XI_ShipChangeCaptainConfirm", "XI_ShipChangeCaptainConfirm");
	
	DelEventHandler("Event_GetWindRosePoints", "GetWindRosePoints");
	DelEventHandler("Event_GetGradientRingColor", "GetSpeedColor");
	DelEventHandler("Event_NodeMouseEffect", "MouseEffect");
	XI_ExitUniversalInput();
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

	CAN_CashCannonsHealth(pchar, true);
	if (bSeaActive) BI_SetCannonHealth();
}

void MouseEffect()
{
	string sNode = GetEventData();
	int isEffect = GetEventData();

	if (sNode == "CANNONS_ZONE_1") XI_ChangeNodeUsing("REMOVE_CANNONS_F", isEffect && GetBortCannonsQty(xi_refCharacter, "cannonf") > 0, "CANNONS_TABLE");
	else if (sNode == "CANNONS_ZONE_2") XI_ChangeNodeUsing("REMOVE_CANNONS_RL", isEffect && GetBortCannonsQty(xi_refCharacter, "cannonr") + GetBortCannonsQty(xi_refCharacter, "cannonl") > 0, "CANNONS_TABLE");
	else if (sNode == "CANNONS_ZONE_3") XI_ChangeNodeUsing("REMOVE_CANNONS_B", isEffect && GetBortCannonsQty(xi_refCharacter, "cannonb") > 0, "CANNONS_TABLE");

	if (!GetSelectable(sNode)) return;
	if (sNode != "CREW_MORALE_BUTTON" && sNode != "CREW_EXP_BUTTON") return;

	string type = sNode == "CREW_MORALE_BUTTON" ? "morale" : "exp";
	if (isEffect) _XI_ShowRaiseEstimation(type, false);
	else XI_HideRaiseEstimation();
}

void _XI_ShowRaiseEstimation(string type, bool hold = false)
{
	if (hold) holdRaisedEstimationState = true;
	if (type == "morale")
	{
		int morale = GetCharacterCrewMorale(xi_refCharacter);
		int up = XI_GetRaiseAmount(morale, "morale");
		XI_FillBar("BAR_CrewMorale_UP", 0, MORALE_MAX, morale+up);
		return;
	}

	int exp = GetCrewExp(xi_refCharacter);
	int up = XI_GetRaiseAmount(exp, "exp");
	XI_FillBar("BAR_CrewExp_UP", 0, EXP_MAX, exp+up);
}

void XI_HideRaiseEstimation()
{
	if (holdRaisedEstimationState) return;

	XI_FillBar("BAR_CrewMorale_UP", 0, MORALE_MAX, 0);
	XI_FillBar("BAR_CrewExp_UP", 0, MORALE_MAX, 0);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
		case "MAIN_CHARACTER_PICTURE":
			if(comName=="activate" || comName=="click") XI_ShipChangeCaptainShow();
		break;
		case "CANNONS_BUTTON":
			if(comName=="activate" || comName=="click") ShowCannonsMenu();
		break;
        case "CANNONS_OK":
			if(comName=="click")
			{
				HideCannonsMenu(); // применить уже сущ изменения
				OnShipScrollChange();	
				Ship_ResearchCannons(xi_refCharacter);
			}
		break;

		case "CREW_MORALE_BUTTON": if(comName=="click") XI_ShowRaiseMoralePopup(); break;
		case "CREW_EXP_BUTTON": if(comName=="click") XI_ShowRaiseExpPopup(); break;
		
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
			iShipType = int(characters[cn].ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				ref realShip = GetRealShip(iShipType);
				attributeName = "pic" + (m+1);
				iShipType = int(RealShips[iShipType].basetype);
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
		if(int(GameInterface.SHIPS_SCROLL.current)!= nCurScrollNum)
		{
			DeleteAttribute(&GameInterface, "TABLE_LIST.BackUp");
			nCurScrollNum = int(GameInterface.SHIPS_SCROLL.current);

			attributeName = "pic" + (nCurScrollNum+1);

			iCharacter = int(GameInterface.SHIPS_SCROLL.(attributeName).character);

			if(iCharacter > 0)
			{
				string sChrId = characters[iCharacter].id;

				xi_refCharacter = characterFromID(sChrId);
				shipIndex= nCurScrollNum+ 1;
				if (shipIndex< 0)
				{
					shipIndex= 0;
				}
				if (int(xi_refCharacter.ship.type) == SHIP_NOTUSED)
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
				
				SetWindRosePoints();
			} 
			else 
			{
				shipIndex= -1;
			}
			return;
		}
	}

	if (sNode == "PASSENGERSLIST" && int(GameInterface.PASSENGERSLIST.current) != nCurScrollCaptainNum)
	{
		nCurScrollCaptainNum = int(GameInterface.PASSENGERSLIST.current);
		SetCaptainsSkills();
		return;
	}
}

void OnShipScrollChange()
{
	SetCommonHeaderInfo();
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\le\portraits\512\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_RANK",xi_refCharacter.Rank);
	// нулим все формы, тк корабля может не быть
	SetFormatedText("SHIP_RANK","");
	SetFormatedText("CREW_QTY","");
	SetFormatedText("FOOD_SHIP", "");
	SetFormatedText("MEDICAMENT_SHIP", "");
	SetFormatedText("RUM_SHIP", "");
	SetFormatedText("TEXT_MONEY_SHIP", "");
	SetFormatedText("CREW_MORALE_TEXT", "");
	SetSelectable("CREW_MORALE_BUTTON", false);
	SetSelectable("CREW_EXP_BUTTON", false);
	SetSelectable("CANNONS_BUTTON", false);
	Table_Clear("TABLE_LIST", false, true, false);
	Table_Clear("TABLE_OTHER", false, true, false);
	SetExchangeTip()
	string bannerType = "banner";

	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(int(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
	int iShip = int(xi_refCharacter.ship.type);
	
	SetNodeUsing("CREW_PARTITION", false);
		
	if (iShip != SHIP_NOTUSED)
	{
		SetNodeUsing("BAR_CrewExp", true);
		SetNodeUsing("BAR_CrewMorale", true);
		SetSelectable("CANNONS_BUTTON", true);
		// оптимизация скилов -->
	    DelBakSkillAttr(xi_refCharacter);
	    ClearCharacterExpRate(xi_refCharacter);
	    RefreshCharacterSkillExpRate(xi_refCharacter);
	    // оптимизация скилов <--
	    
		if (CheckAttribute(xi_refCharacter, "Ship.Cargo.RecalculateCargoLoad") && int(xi_refCharacter.Ship.Cargo.RecalculateCargoLoad))
		{
			RecalculateCargoLoad(xi_refCharacter);
			xi_refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
		}
		ref refBaseShip = GetRealShip(iShip);
		if ("QuestShip" in refBaseShip) bannerType = "bannerUnique";
		string sShip = refBaseShip.BaseName + refBaseShip.ship.upgrades.hull;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\le\ships\" + sShip + ".tga");
		SetFormatedText("SHIP_NAME", xi_refCharacter.ship.name);
		SetFormatedText("SHIP_BASE_NAME", XI_ConvertString(refBaseShip.BaseName));

		GameInterface.edit_box.str = xi_refCharacter.ship.name;	
		SetFormatedText("SHIP_RANK", refBaseShip.Class);
		FillSuppliesTable(goodsMode, xi_refCharacter);
		
		SetShipOTHERTable2("TABLE_OTHER", xi_refCharacter);
		int iColor, iFood;
		string sText;
		SetFoodShipInfoShort(xi_refCharacter, "FOOD_SHIP");
		SetRumShipInfoShort(xi_refCharacter,"RUM_SHIP");
		SetMedicamentShipInfo(xi_refCharacter,"MEDICAMENT_SHIP", "short");

		int salary = GetSalaryForShip(xi_refCharacter);
		SetFormatedText("TEXT_MONEY_SHIP", xiStr("ShipUpkeep") + "\n" + (salary == 0 ? xiStr("No") :FindRussianMoneyString(salary)));
		SetFormatedText("TEXT_SHIP_POWER",  xiStr("ShipPower") + "\n" + int(GetRealShipPower(xi_refCharacter)) + " / " + int(GetModifiedBaseShipPower(xi_refCharacter, int(refBaseShip.BaseType))));
		SetNodeUsing("SUPPLYGOLD",true);
		int crewQty = GetCrewQuantity(xi_refCharacter);
		SetFormatedText("CREW_QTY", ""+crewQty);
		if (crewQty < GetMinCrewQuantity(xi_refCharacter)) iColor = argb(255,255,64,64);
		else iColor = ARGB_Color("white");

		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREW_QTY", 8,-1,iColor);
		SetSelectable("CREW_MORALE_BUTTON", XI_CanRaiseForChr(xi_refCharacter, "morale"));
		SetSelectable("CREW_EXP_BUTTON", XI_CanRaiseForChr(xi_refCharacter, "exp"));
		XI_SetCrewQualityStates(xi_refCharacter);
		XI_FillBar("BAR_CrewMorale_UP", 0, MORALE_MAX, 0);
		XI_FillBar("BAR_CrewExp_UP", 0, MORALE_MAX, 0);
		
		if (IsMainCharacter(xi_refCharacter))
		{
			SetNodeUsing("CREW_PARTITION", true);
			XI_SetClickHandler("TEXT_MONEY_SHIP", &ShowPartitionWindow);
		}
		else XI_UniversalClearElement("TEXT_MONEY_SHIP");
		SetAlertPictures(refBaseShip, crewQty);
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\le\ships\empty_ship.tga");
		SetNodeUsing("BAR_CrewExp", false);
		SetNodeUsing("BAR_CrewMorale", false);
		SetNodeUsing("BAR_CrewExp_UP", false);
		SetNodeUsing("BAR_CrewMorale_UP", false);
		SetNodeUsing("SHIP_ALERT_PICTURE", false);
		SetNodeUsing("SHIP_ALERT_PICTURE2", false);
		SetUseTrigger("TABLE_LIST", false);
		SetUseTrigger("TABLE_SUPPLIES", false);
		SetUseTrigger("TABLE_OTHER", false);
		SetUseTrigger("TABLE_CREW", false);
		SetNodeUsing("BAR_HP", false);
		SetNodeUsing("BAR_SP", false);
		SetNodeUsing("BAR_CAPACITY", false);
		SetNodeUsing("BAR_CREW", false);
		SetNodeUsing("SHIP_ALERT_PICTURE_BG", false);
		SetNodeUsing("SHIP_ALERT_PICTURE_BG2", false);
		SetNodeUsing("SHIP_ALERT_PICTURE_MARK", false);
		SetNodeUsing("SHIP_ALERT_PICTURE_MARK2", false);
	}
	SetShipPerks(xi_refCharacter, "");
	Table_UpdateWindow("TABLE_LIST");
	Table_UpdateWindow("TABLE_OTHER");

	SetNewGroupPicture("SHIP_NAME_BANNER", "SHIP_BANNER", bannerType);
	currentCannonGoodIdx = GetCannonGoodIdxByBort(xi_refCharacter, "cannonl");
}

bool XI_SetShipAlert(bool check, string type, string groupName, string picName, bool useBG, bool useMark, int size = 62, fref onClick = fref(nullptr))
{
	if (check) return false;
	if ("SHIP_ALERT_PICTURE_BG2.userdata" in &GameInterface) return true; // уже есть оба алерта

	string postfix = "";
	if ("SHIP_ALERT_PICTURE_BG.userdata" in &GameInterface) postfix = "2"; // уже есть первый алерт

	string mainEl = "SHIP_ALERT_PICTURE" + postfix;
	GameInterface.("SHIP_ALERT_PICTURE_BG" + postfix).userdata.alertType = type;
	SetNodeUsing(mainEl, true);
	SetNewGroupPicture("SHIP_ALERT_PICTURE_BG" + postfix, "PERKS_ENABLE", useBG ? "base_self" : "");
	SetNodeUsing("SHIP_ALERT_PICTURE_BG" + postfix, true);
	SetNodeUsing("SHIP_ALERT_PICTURE_MARK" + postfix, useMark);

	// привязываемся к фиксированной координате из-за странной работы разрешений
	int initY;
	if ("MAIN_CHARACTER_PICTURE_Y" !in &GameInterface)
	{
		GetNodePosition("MAIN_CHARACTER_PICTURE",0,&initY,0,0);
		GameInterface.MAIN_CHARACTER_PICTURE_Y = initY;
	}
	else initY = int(GameInterface.MAIN_CHARACTER_PICTURE_Y);

	if (size < 0) size = 62;
	int x1,y1,x2,y2;
	x1 = 596;
	x2 = 658;
	y1 = postfix == "2" ? initY+82 : initY;
	y2 = postfix == "2" ? initY+146 : initY+64;
	int diff = int((62 - size) * 0.5);
	SetNodePosition(mainEl, x1+diff, y1+diff, x2-diff, y2-diff);
	SetNewGroupPicture(mainEl, groupName, picName);
	if (onClick != fref(nullptr)) XI_SetClickHandler("SHIP_ALERT_PICTURE_BG" + postfix, onClick);
	return true;
}	

void SetAlertLocationPicture()
{
	if (!IsMainCharacter(xi_refCharacter)) return;

	string picName = "mooring";
	string groupName = "LAND_TARGET";
	if (IsEntity(&worldMap) || bSeaActive)
	{
		GameInterface.SHIP_ALERT_PICTURE_BG.userdata.alertType = "where_is_my_ship_sea";
		groupName = "LAND_COMMANDS";
		picName = "sea";
	}
	else
	{
		GameInterface.SHIP_ALERT_PICTURE_BG.userdata.alertType = "where_is_my_ship";
		ref location = FindLocationById(pchar.location.from_sea);
		string name = GetLocationNameByRef(location);
		GameInterface.SHIP_ALERT_PICTURE_BG.userdata.value = name != "" ? name : GetLocationLabelByRef(location);
		switch (location.type)
		{
			case "town":
			{
				ref town = &Colonies[FindColony(location.fastreload)];
				picName = int(town.nation) == PIRATE && bool(town.HasNoFort) ? "pirateTown" : "town";
			}
			break;
			case "seashore": picName = "seashore"; break;
		}
	}

	SetNodeUsing("SHIP_ALERT_PICTURE_BG", true);
	SetNewGroupPicture("SHIP_ALERT_PICTURE", groupName, picName);
	SetNodeUsing("SHIP_ALERT_PICTURE", true);
}

void SetAlertPictures(ref ship, int crewQty)
{
	SetNodeUsing("SHIP_ALERT_PICTURE_BG", false);
	SetNodeUsing("SHIP_ALERT_PICTURE_MARK", false);
	SetNodeUsing("SHIP_ALERT_PICTURE", false);
	SetNodeUsing("SHIP_ALERT_PICTURE_BG2", false);
	SetNodeUsing("SHIP_ALERT_PICTURE_MARK2", false);
	SetNodeUsing("SHIP_ALERT_PICTURE2", false);
	DeleteAttribute(&GameInterface, "SHIP_ALERT_PICTURE_BG.userdata");
	DeleteAttribute(&GameInterface, "SHIP_ALERT_PICTURE_BG2.userdata");

	SetAlertLocationPicture();
	// квестовый, больше ничего не показываем
	if (XI_SetShipAlert(GetRemovable(xi_refCharacter), "quest_companion", "MARKERS", "exclamation", false, false)) return;
	
	bool hasCrew = crewQty > 0;
	string cannonPic = Goods[GetCannonGoodIdxByBort(xi_refCharacter, "cannonl")].name;
	aref shipUserdata = GameInterface.TABLE_OTHER.userdata$aref;
	// бунт
	XI_SetShipAlert(GetCharacterCrewMorale(xi_refCharacter) > MORALE_MIN + 5, "low_morale", "MORALE", "medium morale", true, true, -1, IsMainCharacter(xi_refCharacter) ? &ShowPartitionWindow : &XI_ShowRaiseMoralePopup);
	// есть долг перед командой
	if (IsMainCharacter(xi_refCharacter)) XI_SetShipAlert(GetPartitionAmount("CrewPayment") <= 0, "salary_debt", "LAND_TARGET2", "usurer", true, true, 56, &ShowPartitionWindow);
	// мало еды
	XI_SetShipAlert(CalculateShipFood(xi_refCharacter) > 5 || !hasCrew, "low_food", "GOODS", "food", true, true);
	// мало медикаментов
	XI_SetShipAlert(CalculateShipMedicament(xi_refCharacter) > 5 || !hasCrew, "low_medicament", "GOODS", "medicament", true, true);
	// сломанные пушки
	XI_SetShipAlert(CAN_GetMostDamagedBortHealth(xi_refCharacter) > CAN_DEBUFF_LEVEL || int(ship.CannonsQuantity) < 1, "cannons_broken", "GOODS", cannonPic, true, true, -1, &ShowCannonsMenu);
	// нет капитанского навыка
	XI_SetShipAlert(CanBeCaptain(xi_refCharacter), "bad_captain", "PERKS_ENABLE", "captain", true, true, -1, &XI_ShipChangeCaptainShow);
	// корабль перегружен
	XI_SetShipAlert(!bool(shipUserdata.overload), "overload", "EQUIP_ICONS", "capacity", true, true, 48, &XI_ShipForceGoodsTab);
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
	string sCurrentNode = GetEventData();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int picW = 180;
	int picH = 180;
	int iItem;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	string sRow;
	int iShip;
	ref refBaseShip;
	float fRepairPercent;
	iShip = int(xi_refCharacter.ship.type);
	refBaseShip = GetRealShip(iShip);

	bool bWindRose = false;

	if (XI_ShowUniversalInputTooltip(sCurrentNode)) return;
	switch (sCurrentNode)
	{
		case "SHIPS_SCROLL":
			if (shipIndex != -1)
			{
			    iShip = int(xi_refCharacter.ship.type);
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
		
		case "HELP":
			sHeader = XI_Convertstring("Goods");
			sText1  = GetRPGText("GoodsCargo_hint");	
		break; 
		
		case "TABLE_OTHER":
			CloseTooltipNew();
			XI_ShipTableTooltip(xi_refCharacter, refBaseShip, "TABLE_OTHER", &sHeader, &sText1, &sText2, &sText3, &sGroup, &sGroupPicture, &bWindRose);
		break; 

		case "TEXT_SHIP_POWER":
			sHeader = xiStr("ShipPower");
			sText1  = DLG_Convert("ShipPower", "ShipsDescribe.txt");
		break;

		case "TEXT_MONEY_SHIP":
			sHeader = XI_Convertstring("CostPerMonth");
			sText1 = GetRPGText("Partition_hint");
		break;
		case "CANNONS_HELP":
			sHeader = XI_Convertstring("cannons_managment");
			sText1 = GetRPGText("cannons_managment_hint");
		break;
	}

	if (XI_CannonStatsTooltip(xi_refCharacter, sCurrentNode, &sHeader, &sText1, &sText2, &sText3)) return;
	if (XI_ShipAlertTooltip(xi_refCharacter, sCurrentNode, &sHeader, &sText1, &sText2, &sText3)) return;
	if (XI_CrewQualityTooltip(sCurrentNode, &sHeader, &sText1, &sText2, &sText3)) return;
	if (XI_ShipSuppliesTooltip(xi_refCharacter, sCurrentNode, &sHeader, &sText1, &sText2, &sText3, &sPicture, &sGroup, &sGroupPicture)) return;
	if (XI_CannonsHealthTooltip(xi_refCharacter, sCurrentNode, &sHeader, &sText1, &sText2, &sText3)) return;
	if (CommonHeaderTooltip(sCurrentNode, &sHeader, &sText1, &sText2, &sText3)) return;
	SetShipPerksTooltip(xi_refCharacter, &sCurrentNode, &sHeader, &sText1, &sText2, &sText3, &sPicture, &sGroup, &sGroupPicture);
	CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, picW, picH, bWindRose, false);
}	

bool XI_ShipAlertTooltip(ref chr, string currentNode, ref header, ref text, ref goodText, ref badText)
{
	if (currentNode != "SHIP_ALERT_PICTURE_BG" && currentNode != "SHIP_ALERT_PICTURE_BG2") return false;

	aref userdata = GameInterface.(currentNode).userdata$aref;
	header = DLG_Convert(userdata.alerttype + "_header", "ShipAlert.txt");
	text = DLG_Convert(userdata.alerttype + "_text", "ShipAlert.txt", &userdata);
	CreateTooltipNew(currentNode, header, text, badText, goodText, "", "", "", "", 0, 0, false, false);
	return true;
}

void HideInfoWindow()
{
	CloseTooltipNew();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    NullSelectTable("TABLE_LIST");
    NullSelectTable("TABLE_OTHER");

	if (curTable == "CANNONS_TABLE" && CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
	{
		currentCannonGoodIdx = int(GameInterface.(CurTable).(CurRow).index);
		ShowCurrentCannon();
	} 
}

void ShowCurrentCannon()
{
	ref cannonGood = &Goods[currentCannonGoodIdx];
	SetFormatedText("CANNON_NAME", xiStr(cannonGood.name));
	SetFormatedText("CANNON_TEXT", GetGoodDescr(cannonGood));
	SetNewGroupPicture("CANNON_PIC", "GOODS", cannonGood.name);
	ref cannonItem = &Cannon[int(cannonGood.cannonIdx)];
	FillUpCannonStats(cannonItem, xi_refCharacter);
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
	    ShowGoodsInfo(int(GameInterface.(CurTable).(CurRow).index));
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
	    if (int(GameInterface.(CurTable).(CurRow).index) == GOOD_POWDER)
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

	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
	string goodsDescr = GetAssembledString( GetGoodDescr(&Goods[iGoodIndex]), &Goods[iGoodIndex]);
    goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
	              ", " + XI_ConvertString("PackHolds") + " " + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits  = int(Goods[iGoodIndex].Units);
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
	
	iShipQty = GetCargoGoods(xi_refCharacter, iGoodIndex);
    SetFormatedText("QTY_INFO_SHIP_QTY", string(iShipQty));
    SetFormatedText("QTY_INFO_STORE_QTY", string(GetGoodWeightByType(iGoodIndex, iShipQty)));
}

void TransactionOK()
{
	int nTradeQuantity;
	confirmChangeQTY_EDIT();
	
	nTradeQuantity = int(GameInterface.qty_edit.str);

    SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty);
    
    if (!GetRemovable(xi_refCharacter)) return;
	if (nTradeQuantity > 0)
	{
		DropGoodsToSeaFromInterface(iCurGoodsIdx, nTradeQuantity); // остаётся плавать в море
		CAN_UpdateDamageInStock(xi_refCharacter, &Goods[iCurGoodsIdx]);
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
	GameInterface.qty_edit.str = abs(int(GameInterface.qty_edit.str));  // приведение к числу
	
	string GoodName = goods[iCurGoodsIdx].name;
	
    // проверка на колво доступное -->
    if (int(GameInterface.qty_edit.str) > iShipQty)
    {
        GameInterface.qty_edit.str = iShipQty;
    }
    SetFormatedText("QTY_INFO_SHIP_QTY", string(iShipQty - int(GameInterface.qty_edit.str)));
	SetFormatedText("QTY_INFO_STORE_QTY", string(GetGoodWeightByType(iCurGoodsIdx, (iShipQty - int(GameInterface.qty_edit.str)))));
	// прикидываем место в трюме
	iWeight = int(GameInterface.qty_edit.str);
	SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty);
	if (iWeight > 0)
	{
		RemoveCharacterGoods(xi_refCharacter, iCurGoodsIdx, iWeight);
	}
	OnShipScrollChange();
}


void REMOVE_BUTTON(int value)
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = (int(GameInterface.qty_edit.str) + value * iUnits);
	ChangeQTY_EDIT();
}

void ADD_BUTTON(int value)
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = (int(GameInterface.qty_edit.str) - value * iUnits);
	if (int(GameInterface.qty_edit.str) < 0) GameInterface.qty_edit.str = 0;
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
			iQuantity = iQuantity / int(Goods[iGoodIndex].Units);
	
			int iSwimQuantity = int(iQuantity/3 + rand(int(iQuantity/3)) + rand(int(iQuantity/3)));
	
			if(iSwimQuantity < 1)
			{
				iSwimQuantity = 1;
			}
	
			RecalculateCargoLoad(xi_refCharacter);
	        xi_refCharacter.Tmp.SpeedRecall = 0; // чтоб пересчитались скорость и маневр
	        
			if (CheckAttribute(&Goods[iGoodIndex], "Swim")) 
			{ 
				float fTime = float(Goods[iGoodIndex].Swim.Time);
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
	if (xi_refCharacter.id != pchar.id && int(pchar.ship.type) != SHIP_NOTUSED)
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
		if (int(pchar.ship.type) == SHIP_NOTUSED)
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
	if (sMessageMode == "ShipChange") // обмен с кораблём
	{
		pchar.SystemInfo.OurChar = true; // belamour выход обратно из меню обмена
		pchar.TransferChar = xi_refCharacter.index;
		InterfaceStates.ReloadMenuExit = true;
		IDoExit(RC_INTERFACE_ANY_EXIT);
		PostEvent("LaunchIAfterFrame",1,"sl", "TransferMain", 2);
	}
}

void XI_ShowRaiseExpPopup()
{
	_XI_ShowRaiseEstimation("exp", true);
	touchattr(GameInterface.CREW_EXP_BUTTON.userdata);
	aref userdata = GameInterface.CREW_EXP_BUTTON.userdata$aref;
	int crewQty = GetCrewQuantity(xi_refCharacter);
	userdata.good1_Idx = GOOD_WEAPON;
	userdata.good1 = Goods[GOOD_WEAPON].Name;
	userdata.qty1 = ceil(float(crewQty) / 6);
	userdata.good2_Idx = GOOD_BALLS;
	userdata.good2 = Goods[GOOD_BALLS].Name;
	userdata.qty2 = ceil(float(crewQty) * 0.25);
	userdata.good3_Idx = GOOD_POWDER;
	userdata.good3 = Goods[GOOD_POWDER].Name;
	userdata.good4_Idx = GOOD_PLANKS;
	userdata.good4 = Goods[GOOD_PLANKS].Name;
	userdata.qty3 = ceil(float(crewQty) * 0.10);
	userdata.good5_Idx = GOOD_SAILCLOTH;
	userdata.good5 = Goods[GOOD_SAILCLOTH].Name;
	string reason = "";
	if (GetCargoGoods(xi_refCharacter, GOOD_WEAPON) < int(userdata.qty1)) reason = "goods";
	else if (GetCargoGoods(xi_refCharacter, GOOD_BALLS) < int(userdata.qty2)) reason = "goods";
	else if (GetCargoGoods(xi_refCharacter, GOOD_POWDER) < int(userdata.qty2)) reason = "goods";
	else if (GetCargoGoods(xi_refCharacter, GOOD_PLANKS) < int(userdata.qty3)) reason = "goods";
	else if (GetCargoGoods(xi_refCharacter, GOOD_SAILCLOTH) < int(userdata.qty3)) reason = "goods";

	if (TMSTD_Timestamp(0) < TEV.actions.raiseExp.AvailableAt$int(0)) reason = "cooldown";

	CallWithConfirmationDynamic(&XI_RaiseExp, &XI_HideRaiseEstimationForce, reason == "", DLG_Convert("raiseExpText", "supplies.txt", &userdata), xiStr("RaiseExpTitle"), "", DLG_ConvertE(reason, "supplies.txt", &userdata));
}

void XI_HideRaiseEstimationForce()
{
	holdRaisedEstimationState = false;
	XI_HideRaiseEstimation();
}

bool XI_CanRaiseForChr(ref chr, string mode)
{
	int chrShipType = chr.ship.type$int(SHIP_NOTUSED);
	if (chrShipType == SHIP_NOTUSED) return false;
	if (GetCrewQuantity(xi_refCharacter) < 1) return false;
	if (mode == "exp" && XI_GetRaiseAmount(int(GetCrewExp(xi_refCharacter)), "exp") < 1) return false;
	else if (mode == "morale" && XI_GetRaiseAmount(GetCharacterCrewMorale(xi_refCharacter, true), "morale") < 1) return false;
	return GetRemovable(xi_refCharacter);
}

void XI_RaiseMorale()
{
	touchattr(GameInterface.CREW_MORALE_BUTTON.userdata);
	aref userdata = GameInterface.CREW_MORALE_BUTTON.userdata$aref;
	AddMoneyToCharacter(pchar, -int(userdata.money));
	RemoveCharacterGoodsSelf(xi_refCharacter, int(userdata.good1_Idx), int(userdata.qty1));
	RemoveCharacterGoodsSelf(xi_refCharacter, int(userdata.good2_Idx), int(userdata.qty2));
	AddCrewMorale(xi_refCharacter, XI_GetRaiseAmount(GetCharacterCrewMorale(xi_refCharacter, true), "morale"));
	Statistic_AddValue(pchar, "PartitionPay", int(userdata.money));
	OnShipScrollChange();
	SetCurrentNode("TABLE_CREW");
	TEV.actions.raiseMorale.AvailableAt = TMSTD_Timestamp(1);
}

void XI_RaiseExp()
{
	touchattr(GameInterface.CREW_EXP_BUTTON.userdata);
	aref userdata = GameInterface.CREW_EXP_BUTTON.userdata$aref;
	RemoveCharacterGoodsSelf(xi_refCharacter, int(userdata.good1_Idx), int(userdata.qty1));
	RemoveCharacterGoodsSelf(xi_refCharacter, int(userdata.good2_Idx), int(userdata.qty2));
	RemoveCharacterGoodsSelf(xi_refCharacter, int(userdata.good3_Idx), int(userdata.qty2));
	RemoveCharacterGoodsSelf(xi_refCharacter, int(userdata.good4_Idx), int(userdata.qty3));
	RemoveCharacterGoodsSelf(xi_refCharacter, int(userdata.good5_Idx), int(userdata.qty3));
	ChangeCrewExp(xi_refCharacter, "sailors", float(XI_GetRaiseAmount(GetCrewExp(xi_refCharacter), "exp")));
	OnShipScrollChange();
	SetCurrentNode("TABLE_CREW");
	TEV.actions.raiseExp.AvailableAt = TMSTD_Timestamp(1);
}

int XI_GetRaiseAmount(int currentValue, string mode)
{
	if (currentValue == 0) currentValue = 2;
	if (mode == "exp") return int((EXP_MAX - currentValue) * 0.25);
	else return int((MORALE_MAX - currentValue) * 0.3);
}

void XI_ShowRaiseMoralePopup()
{
	_XI_ShowRaiseEstimation("morale", true);
	touchattr(GameInterface.CREW_MORALE_BUTTON.userdata);
	aref userdata = GameInterface.CREW_MORALE_BUTTON.userdata$aref;

	int crewQty = GetCrewQuantity(xi_refCharacter);
	userdata.money = int(GetSalaryForShip(xi_refCharacter) * 0.25);
	userdata.HumanMoney = FindRussianMoneyString(int(userdata.money));
	userdata.good1_Idx = GOOD_FOOD;
	userdata.good1 = Goods[GOOD_FOOD].Name;
	userdata.qty1 = ceil(crewQty * 0.1);
	int rumNeeded = ceil(crewQty * 0.05);
	int aleNeeded = ceil(crewQty * 0.033);
	userdata.good2 = Goods[GOOD_RUM].Name;
	userdata.qty2 = aleNeeded;
	userdata.good2_Idx = GOOD_RUM;
	string reason = int(pchar.money) >= int(userdata.money) ? "" : "money";
	if (GetCargoGoods(xi_refCharacter, GOOD_RUM) >= rumNeeded) userdata.qty2 = rumNeeded;
	else if (GetCargoGoods(xi_refCharacter, GOOD_ALE) >= aleNeeded)
	{
		userdata.good2_Idx = GOOD_ALE;
		userdata.good2 = Goods[GOOD_ALE].Name;
	}
	else if (GetCargoGoods(xi_refCharacter, GOOD_WINE) >= aleNeeded)
	{
		userdata.good2_Idx = GOOD_WINE;
		userdata.good2 = Goods[GOOD_WINE].Name;
	}
	else reason = "goods";

	if (TMSTD_Timestamp(0) < TEV.actions.raiseMorale.AvailableAt$int(0)) reason = "cooldown";

	userdata.reason = reason;
	CallWithConfirmationDynamic(&XI_RaiseMorale, &XI_HideRaiseEstimationForce, reason == "", DLG_Convert("raiseMoraleText", "supplies.txt", &userdata), xiStr("RaiseMoraleTitle"), "", DLG_ConvertE(reason, "supplies.txt", &userdata));
}

void ShowCannonsMenu()
{
	int chrShipType = xi_refCharacter.ship.type$int(SHIP_NOTUSED);
	if (chrShipType == SHIP_NOTUSED) return;

	XI_WindowShow("CANNONS_WINDOW", true);
	XI_WindowDisable("CANNONS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("CANNONS_TABLE");

	bool canManage = GetRemovable(xi_refCharacter);
	SetSelectable("SET_CANNONS_F", canManage);
	SetSelectable("SET_CANNONS_B", canManage);
	SetSelectable("SET_CANNONS_RL", canManage);
	SetSelectable("REMOVE_CANNONS_F", canManage);
	SetSelectable("REMOVE_CANNONS_B", canManage);
	SetSelectable("REMOVE_CANNONS_RL", canManage);
	SetNodeUsing("REMOVE_CANNONS_F", false);
	SetNodeUsing("REMOVE_CANNONS_RL", false);
	SetNodeUsing("REMOVE_CANNONS_B", false);
	DeleteAttribute(&GameInterface, "CANNONS_TABLE.BackUp")
	CannonsMenuRefresh();
	currentCannonsMode = 1;
	
	ShowCurrentCannon();
}


void CannonsMenuRefresh(string bortName = "all")
{
	for (string nodeName, aref oldElement: GameInterface.tempCannons$aref) { XI_DeleteNode(nodeName); }
	DeleteAttribute(&GameInterface, "tempCannons");
	object cannonsHealthInfo = CAN_GetFullInfo(xi_refCharacter);

	XI_DrawCannonToBort("BORT_LAYOUT_R", "cannonr");
	XI_DrawCannonToBort("BORT_LAYOUT_L", "cannonl");
	XI_DrawCannonToBort("BORT_LAYOUT_F", "cannonf");
	XI_DrawCannonToBort("BORT_LAYOUT_B", "cannonb");

	int installedWeight = GetInstalledCannonsWeight(xi_refCharacter);
	SetFormatedText("CANNONS_WEIGHT_VALUE", installedWeight);
	int capacity = GetCargoMaxSpace(xi_refCharacter);
	int currentLoad = GetCargoLoad(xi_refCharacter);
	cannonsHealthInfo.weightPercent = ceil(installedWeight * 100 / float(capacity)) * 0.01;
	SetFormatedText("CANNONS_WEIGHT_VALUE2", DLG_Convert("Cannon_weight_in_stock", "ShipsDescribe.txt", &cannonsHealthInfo));
	XI_FillBar("BAR_CANNONS_WEIGHT", 0, capacity, currentLoad - installedWeight);
	XI_FillBar("BAR_CANNONS_WEIGHT2", 0, capacity, currentLoad);

	int idx =  GetCannonGoodIdxByBort(xi_refCharacter, "cannonl");
	if (idx != -1)
	{
		bool hasCannons = int(cannonsHealthInfo.l.goodcannons) + int(cannonsHealthInfo.r.goodcannons) > 0;
		SetFormatedText("CANNONS_TEXT_L", xiStr("cannonl") + "\n" + (hasCannons ? XI_ConvertString(Goods[idx].Name + "_s") + "\n" + XI_HumanCannonsHealth(float(cannonsHealthInfo.l.averageHealth)) : ""));
		SetFormatedText("CANNONS_TEXT_R", xiStr("cannonr") + "\n" + (hasCannons ? XI_ConvertString(Goods[idx].Name + "_s") + "\n" + XI_HumanCannonsHealth(float(cannonsHealthInfo.r.averageHealth)) : ""));
		SetVAligmentFormatedText("CANNONS_TEXT_L");
		SetVAligmentFormatedText("CANNONS_TEXT_R");
		SetNewGroupPicture("CANNONS_PIC_L", "GOODS", hasCannons ? Goods[idx].Name : "");
		SetNewGroupPicture("CANNONS_PIC_R", "GOODS", hasCannons ? Goods[idx].Name : "");
		idx = GetCannonGoodIdxByBort(xi_refCharacter, "cannonf");
		hasCannons = int(cannonsHealthInfo.f.goodcannons) > 0;
		SetFormatedText("CANNONS_TEXT_F", hasCannons ? XI_ConvertString(Goods[idx].Name + "_s") + "\n" + XI_HumanCannonsHealth(float(cannonsHealthInfo.f.averageHealth)) : "");
		SetNewGroupPicture("CANNONS_PIC_F", "GOODS", hasCannons ? Goods[idx].Name : "");
		idx = GetCannonGoodIdxByBort(xi_refCharacter, "cannonb");
		hasCannons = int(cannonsHealthInfo.b.goodcannons) > 0;
		SetFormatedText("CANNONS_TEXT_B", hasCannons ? XI_ConvertString(Goods[idx].Name + "_s") + "\n" + XI_HumanCannonsHealth(float(cannonsHealthInfo.b.averageHealth)) : "");
		SetNewGroupPicture("CANNONS_PIC_B", "GOODS", hasCannons ? Goods[idx].Name : "");
		SetFormatedText("CANNONS_QTY_R", string(GetBortCannonsQty(xi_refCharacter, "cannonr")));
		SetFormatedText("CANNONS_QTY_L", string(GetBortCannonsQty(xi_refCharacter, "cannonl")));
		
		
		SetNewGroupPicture("CANNONS_PIC_F_HEALTH", "CANNONS_MANAGEMENT", float(cannonsHealthInfo.f.averageHealth));
		SetNewGroupPicture("CANNONS_PIC_L_HEALTH", "CANNONS_MANAGEMENT", float(cannonsHealthInfo.l.averageHealth));
		SetNewGroupPicture("CANNONS_PIC_R_HEALTH", "CANNONS_MANAGEMENT", float(cannonsHealthInfo.r.averageHealth));
		SetNewGroupPicture("CANNONS_PIC_B_HEALTH", "CANNONS_MANAGEMENT", float(cannonsHealthInfo.b.averageHealth));

	
		SetFormatedText("CANNONS_HEALTH_F", XI_HumanCannonsHealth(float(cannonsHealthInfo.f.averageHealth)));
		SetFormatedText("CANNONS_HEALTH_B", XI_HumanCannonsHealth(float(cannonsHealthInfo.b.averageHealth)));
		SetFormatedText("CANNONS_HEALTH_R", XI_HumanCannonsHealth(float(cannonsHealthInfo.r.averageHealth)));
		SetFormatedText("CANNONS_HEALTH_L", XI_HumanCannonsHealth(float(cannonsHealthInfo.l.averageHealth)));
	}
	else
	{
		SetNewGroupPicture("CANNONS_PIC_L", "GOODS", "");
		SetNewGroupPicture("CANNONS_PIC_F", "GOODS", "");
		SetNewGroupPicture("CANNONS_PIC_B", "GOODS", "");
		SetFormatedText("CANNONS_TEXT_L", "");
		SetFormatedText("CANNONS_TEXT_F", "");
		SetFormatedText("CANNONS_TEXT_B", "");
		SetFormatedText("CANNONS_QTY_F", "0");
		SetFormatedText("CANNONS_QTY_B", "0");
		SetFormatedText("CANNONS_QTY_R", "0");
		SetFormatedText("CANNONS_QTY_L", "0");
	}

	SetNodeUsing("CANNONS_HEALTH_F", float(cannonsHealthInfo.f.averageHealth) > 0.0);
	SetNodeUsing("CANNONS_HEALTH_B", float(cannonsHealthInfo.b.averageHealth) > 0.0);
	SetNodeUsing("CANNONS_HEALTH_R", float(cannonsHealthInfo.r.averageHealth) > 0.0);
	SetNodeUsing("CANNONS_HEALTH_L", float(cannonsHealthInfo.l.averageHealth) > 0.0);
	FillCannonsTable();
}
void ExitCannonsMenu()
{
	HideCannonsMenu();
	OnShipScrollChange();
}

void HideCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", false);
	XI_WindowDisable("CANNONS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	for (string nodeName, aref _el: GameInterface.tempCannons$aref) { XI_DeleteNode(nodeName); }

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
	currentCannonsMode = 0;
	Ship_ResearchCannons(xi_refCharacter);
}

void FillCannonsTable()
{
	int n, qty;
	string row;
	ref rShip;
	string sGood;
	aref refGoods;

	n = 1;
	Table_Clear("CANNONS_TABLE", false, true, false);
	GameInterface.CANNONS_TABLE.hr.td1.str = XI_ConvertString("CannonsHold");
	GameInterface.CANNONS_TABLE.hr.td2.str = XI_ConvertString("CannonsQty");

	if (!CheckAttribute(&GameInterface, "CANNONS_TABLE.BackUp"))
	{
		GameInterface.CANNONS_TABLE.select = 0;
		GameInterface.CANNONS_TABLE.top    = 0;
		GameInterface.CANNONS_TABLE.BackUp = true;
	}

	int maxCaliber = GetMaximumCaliber(xi_refCharacter);
	for (int i, ref good: &Goods)
	{
		row = "tr" + n;
		sGood = good.name;
		qty = GetCargoGoods(xi_refCharacter, i);
		if (qty <= 0) continue; // только не нули
		if (good.type$int(-1) != T_TYPE_CANNONS) continue;
		if (GetCannonCaliber(int(good.CannonIdx)) > maxCaliber) continue;

		GameInterface.CANNONS_TABLE.(row).index = i;
		GameInterface.CANNONS_TABLE.(row).td1.icon.group = "GOODS";
		GameInterface.CANNONS_TABLE.(row).td1.icon.image = sGood;
		GameInterface.CANNONS_TABLE.(row).td1.icon.offset = "-10, 0";
		GameInterface.CANNONS_TABLE.(row).td1.icon.width = 40;
		GameInterface.CANNONS_TABLE.(row).td1.icon.height = 40;
		GameInterface.CANNONS_TABLE.(row).td1.textoffset = "40,0";
		GameInterface.CANNONS_TABLE.(row).td1.str = XI_ConvertString(sGood);
		GameInterface.CANNONS_TABLE.(row).td2.str = qty;
		GameInterface.CANNONS_TABLE.(row).td2.icon.group = "CANNONS_MANAGEMENT";
		GameInterface.CANNONS_TABLE.(row).td2.icon.image = XI_GetCannonsHealthIconForStock(xi_refCharacter, good);
		GameInterface.CANNONS_TABLE.(row).td2.icon.offset = "36, 4";
		GameInterface.CANNONS_TABLE.(row).td2.icon.width = 35;
		GameInterface.CANNONS_TABLE.(row).td2.icon.height = 35;
		n++;
	}

	RestoreTableSorting("CANNONS_TABLE");
	Table_UpdateWindow("CANNONS_TABLE");
}

void ShowPartitionWindow()
{
    string str;
	string sTitul = "";
	int	HowGower = 0;

	if (isMainCharacterPatented())
	{
		sTitul = GetAddress_FormTitle(int(Items[int(pchar.EquipedPatentId)].Nation), int(Items[int(pchar.EquipedPatentId)].TitulCur));
	}
	
	str = XI_ConvertString("CurDate") + GetDateString() + " " + GetTimeString() + NewStr();
	if(CheckAttribute(pchar, "paymentdate"))
	{
		str += XI_ConvertString("PrevPaymentDate") + pchar.paymentdate + NewStr();
	}	
	str += sTitul + " " + GetFullName(pchar) + NewStr() + XI_ConvertString("Rank") + ": " + int(pchar.rank) + NewStr();
	str += XI_ConvertString("m_Complexity") + ": " + GetLevelComplexity(MOD_SKILL_ENEMY_RATE) + NewStr() +
			XI_ConvertString("OurMoney") + FindRussianMoneyString(int(pchar.money)) + NewStr() + "*****" + NewStr();
    str += XI_ConvertString("CurMonthParts") + NewStr() + XI_ConvertString("CaptainPart") + GetPartitionAmount("Partition.MonthPart.Hero") + NewStr() +
		  XI_ConvertString("OfficersPart") + GetPartitionAmount("Partition.MonthPart.Officers") + NewStr() +
		  XI_ConvertString("SailorsPart") + GetPartitionAmount("Partition.MonthPart.Crew") + NewStr() + 		  
		   "*****" + NewStr() +
		  XI_ConvertString("CurMonthDebt") + GetPartitionAmount("Partition.MonthPart") + NewStr() +	
		  XI_ConvertString("StateDebt") + GetPartitionAmount("Partition.MonthPart.Gower") + NewStr();
	str += "*****" + NewStr() + XI_ConvertString("PrevMonthDebt") + GetPartitionAmount("CrewPayment");

	bool selectable = GetPartitionAmount("Partition.MonthPart") + GetPartitionAmount("CrewPayment") > 0;
	if (int(Pchar.Money) < 1) selectable = false;
	CallWithConfirmationDynamic(&DoPartitionPay, fref(nullptr), selectable, str, xiStr("PartitionCaption"));
	SetFormatedTextButton("OK_BUTTON_CONFIRMATION_POPUP", "PartitionOK");
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
	    if (int(Pchar.Money) < sum) sum = int(Pchar.Money);
        Pchar.CrewPayment = int(Pchar.CrewPayment) - sum;
        if (int(Pchar.CrewPayment) <= 0) DeleteAttribute(Pchar, "CrewPayment");
	}
	else
	{
		// долг перед командой
		if (GetPartitionAmount("Partition.MonthPart") > 0)
		{
		    sum = GetPartitionAmount("Partition.MonthPart");
		    if (int(Pchar.Money) < sum) sum = int(Pchar.Money);
	        Pchar.Partition.MonthPart = int(Pchar.Partition.MonthPart) - sum;
	        AddCrewMorale(xi_refCharacter, 2);
			ChangeCharacterComplexReputation(pchar,"authority", 2); 
		}
		// долг перед государством
		if (GetPartitionAmount("Partition.MonthPart.Gower") > 0)
		{
		    sum_gow = GetPartitionAmount("Partition.MonthPart.Gower");
		    if (int(Pchar.Money) < sum_gow) sum_gow = int(Pchar.Money);
	        Pchar.Partition.MonthPart.Gower = int(Pchar.Partition.MonthPart.Gower) - sum_gow;
		}
	}
	pchar.paymentdate = GetDateString() + " " + GetTimeString();
	AddMoneyToCharacter(Pchar, - (sum + sum_gow));
	Statistic_AddValue(pchar, "PartitionPay", sum + sum_gow);
	if(sum >= 3000) AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, float(sum) / 3000.0);
	OnShipScrollChange();
	ExitPartitionWindow();
}

int GetPartitionAmount(string _param)
{
    if (!CheckAttribute(Pchar, _param)) return 0;
    return int(Pchar.(_param));
}

void OnHeaderClick()
{
	string sControl = GetEventData();
	int column = GetEventData();
	
	string datatype = "integer";
	if (sControl == "TABLE_LIST") 
	{
		switch (column)
		{
			case 1: datatype = "index"; break; 
		}
	}
	else if (sControl == "CANNONS_TABLE")
	{
		switch (column)
		{
			case 1: datatype = "index"; break; 
		}	
	}

	QoLSortTable(sControl, column, datatype, false, 0);
}

void SetWindRosePoints()
{
	int chrShipType = xi_refCharacter.ship.type$int(SHIP_NOTUSED);
	if (chrShipType == SHIP_NOTUSED) return;
	int iShipType = int(RealShips[chrShipType].basetype);

	float fAngle;
	for(int i = 0; i <= SHIP_SPEEDPOINT_QUANTITY / 2; i++)
	{
		fAngle = i * PIm2 / SHIP_SPEEDPOINT_QUANTITY;
		fSpeeds[i] = Ship_SimulateSpeed_Init(iShipType, fAngle) * GetCurSpeedFromPoint(xi_refCharacter, fAngle);
		if(i > 0 && i <  SHIP_SPEEDPOINT_QUANTITY / 2)
			fSpeeds[SHIP_SPEEDPOINT_QUANTITY - i] = fSpeeds[i];
	}
}

ref GetWindRosePoints()
{
	string sNode = GetEventData();
	return &fSpeeds;
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode(CurrentGoodsTableName(goodsMode));

	if(sNodName == "TABBTN_1")
	{
		SetControlsTabMode(0);
		FillSuppliesTable(0, xi_refCharacter);
		return;
	}
	if(sNodName == "TABBTN_2")
	{
		SetControlsTabMode(1);
		FillSuppliesTable(1, xi_refCharacter);
		return;
	}
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,255,255,255);
	int nColor2 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	goodsMode = nMode;
	switch (nMode)
	{
		case 1:
			sPic1 = "TabDeSelected";
			nColor1 = argb(255,196,196,196);
		break;
		case 0:
			sPic2 = "TabDeSelected";
			nColor2 = argb(255,196,196,196);
		break;
	}

	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_SCROLL_1_MARK", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_SCROLL_2_MARK", "TABS", sPic2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,nColor2);
}

string CurrentGoodsTableName(int goodsMode)
{
	return goodsMode == 0 ? "TABLE_LIST" : "TABLE_SUPPLIES";
}

// Скрываем подсказку обмена для корабля гг
void SetExchangeTip()
{
	if (IsMainCharacter(xi_refCharacter))
	{
		StringCollection_SetText("KEY_STRS", 2, "# ");
		ImageCollection_ChangePicture("KEY_BTNS", 3, "");
		return;
	}

	StringCollection_SetText("KEY_STRS", 2, "for_quick_action_Reload_Sea");
	ImageCollection_ChangePicture("KEY_BTNS", 3, "Space");
}

void XI_ShipChangeCaptainShow()
{
	string attributeName = "pic" + (nCurScrollCaptainNum+1);

	if (IsMainCharacter(xi_refCharacter) || !GetRemovable(xi_refCharacter) || !IsCompanion(xi_refCharacter)) 
	{
		PlaySound("interface\knock.wav");
		return;
	}
	else if (!IsShipSafeReachableNow())
	{
		ShowError(xiStr("CantChangCaptainNow"));
		return;
	}

	FillScrollWithCharactersFref("PASSENGERSLIST", &IsFellowAbleToBeCompanion, false, &nCurScrollCaptainNum, 1);

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
	SetCurrentNode("PASSENGERSLIST");
	ProcessFrame();
	SetCaptainsSkills();

	XI_WindowShow("CHANGE_CAPTAIN_WINDOW", true);
	XI_WindowDisable("CHANGE_CAPTAIN_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	SetCurrentNode("PASSENGERSLIST");

	Event("PopupIsShown");
}

void XI_ShipChangeCaptainClose()
{
	XI_WindowShow("CHANGE_CAPTAIN_WINDOW", false);
	XI_WindowDisable("CHANGE_CAPTAIN_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	GameInterface.strings.CharJob = "";
	SetCurrentNode("SHIPS_SCROLL");
	Event("PopupIsClosed");
}

void SetCaptainsSkills()
{
	string sCharacter = "pic" + (int(GameInterface.PASSENGERSLIST.current) + 1);
	if (checkAttribute(&GameInterface, "PASSENGERSLIST." + sCharacter))
	{
		if (checkAttribute(&GameInterface, "PASSENGERSLIST." + sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[int(sCharacter)];
			SetSPECIALMiniTable("TABLE_SMALLSKILL2", otherchr);
			SetOTHERMiniTable("TABLE_SMALLOTHER2", otherchr);
			SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
			SetFormatedText("OFFICER_JOB", GetJobsList(otherchr, " / "));
			SetSelectable("ACCEPT_ADD_OFFICER", true);
		}
		else
		{
			Table_Clear("TABLE_SMALLSKILL2", false, true, true);
			Table_Clear("TABLE_SMALLOTHER2", false, true, true);
			SetFormatedText("OFFICER_NAME", "");
			SetFormatedText("OFFICER_JOB", "");
			SetSelectable("ACCEPT_ADD_OFFICER", false);
		}
	}
	else
	{
		Table_Clear("TABLE_SMALLSKILL", false, true, true);
		Table_Clear("TABLE_SMALLOTHER", false, true, true);
		SetFormatedText("OFFICER_NAME", "");
		SetFormatedText("OFFICER_JOB", "");
		SetSelectable("ACCEPT_ADD_OFFICER", false);
	}
}

void XI_ShipChangeCaptainConfirm()
{
	string  attributeName = "pic"+(nCurScrollCaptainNum+1);
	int newCapIdx = int(GameInterface.PASSENGERSLIST.(attributeName).character);
	ref newCap = GetCharacter(newCapIdx);
	ref oldCap = xi_refCharacter;

	string currentShipAttribute = "pic" + (nCurScrollNum+1);
	GameInterface.SHIPS_SCROLL.(currentShipAttribute).character = newCap.index;

	int companionNumber = GetCompanionNumber(pchar, int(oldCap.index));
	aref arTo = newCap.ship$aref;
	aref arFrom = oldCap.ship$aref;
	CopyAttributes(arTo, arFrom);
	RemoveCharacterCompanion(pchar, oldCap);
	AddPassenger(pchar, oldCap, false);

	CheckForReleaseOfficer(newCapIdx);
	RemovePassenger(pchar, newCap);
	SetCompanionIndex(pchar, companionNumber, newCapIdx);

	xi_refCharacter = newCap;
	OnShipScrollChange();
	XI_ShipChangeCaptainClose();

	SeaAI_SetOfficer2ShipAfterAbordage(newCap, oldCap);
	if (IsEntity(&worldMap)) BI_UpdateWmInterface();
}

void XI_ShipForceGoodsTab()
{
	goodsMode = 1;
	SetControlsTabMode(goodsMode);
	FillSuppliesTable(goodsMode, xi_refCharacter);
}
