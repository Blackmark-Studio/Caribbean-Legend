#include "interface\utils\popup_confirmation.c"
#include "interface\utils\ship_perks.c"
#include "interface\utils\ship_common.c"
#include "interface\utils\modifiers.c"
#include "interface\utils\universal_input.c"
#include "interface\utils\cannons_health.c"

#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню кнопками Q и E

/// BOAL 01.08.06 форма обмена-грабежа корабля
/// Sith переделка
#define FOOD_BY_ENEMY_CREW 			10
#define RUM_BY_ENEMY_CREW 			20
#define MEDICAMENT_BY_ENEMY_CREW 	30
#define WEAPON_BY_ENEMY_CREW		10
#define HP_BY_ENEMY_CREW			50
#define HP_PER_BOAT					25  

int nCurScrollOfficerNum;
ref xi_refCharacter, refEnemyCharacter;
ref refCharacter;

string CurTable, CurRow, CurCol;
int iSelected, iSelectedCol;

// для выкидывания
int iShipQty, iUnits, iCurGoodsIdx;

float fSpeeds[SHIP_SPEEDPOINT_QUANTITY];
float fCompareSpeeds[SHIP_SPEEDPOINT_QUANTITY];

int	iCrewQty = 0;
int iBackCrew = 0;
int iGetHired = 0;
int goodsMode = 0;

string sMessageMode;
bool  bTransferMode;
bool  bSwap;
// pchar - ГГ, xi_refCharacter - враг или наш компаньон, гг всегда слева  
void InitInterface_RS(string iniName, ref _chr, string _type)
{
    bQuestCheckProcessFreeze = true;
    
	xi_refCharacter   = _chr;
	refEnemyCharacter = _chr; // изначальный кэп
	refCharacter = pchar;
	
	if(refEnemyCharacter.id == "ShipWreck_BadPirate") 
	{
		xi_refCharacter = CharacterFromID("ShipWreck_0");
		refEnemyCharacter = xi_refCharacter;
	}	
	
	if (CheckAttribute(xi_refCharacter, "Ship.Cargo.RecalculateCargoLoad") && int(xi_refCharacter.Ship.Cargo.RecalculateCargoLoad))
	{
		RecalculateCargoLoad(xi_refCharacter);
		xi_refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
	}
	if (CheckAttribute(pchar, "Ship.Cargo.RecalculateCargoLoad") && int(pchar.Ship.Cargo.RecalculateCargoLoad))
	{
		RecalculateCargoLoad(pchar);
		pchar.Ship.Cargo.RecalculateCargoLoad = 0;
	}
	if (_type == "Transfer")
    {
		GameInterface.title = "titleTransfer";
		bTransferMode = true;
	}
	else
	{
		DeleteAttribute(pchar, "abordage_active"); // от к3, хотя трется до этой формы
		GameInterface.title = "titleRansack";
		bTransferMode = false;
		
		if(GetCargoGoods(xi_refCharacter, GOOD_SLAVES) > 0)
		{
			pchar.GoodsExp.Slaves = GetSquadronGoods(pchar, GOOD_SLAVES);
		}
		if(GetCargoGoods(xi_refCharacter, GOOD_GOLD) > 0)
		{
			pchar.GoodsExp.Gold = GetSquadronGoods(pchar, GOOD_GOLD);
		}
		if(GetCargoGoods(xi_refCharacter, GOOD_SILVER) > 0)
		{
			pchar.GoodsExp.S = GetSquadronGoods(pchar, GOOD_SILVER);
		}
		
		if (_type == "") // дошли до логического конца абордажа, кэп помер
		{
			if(xi_refCharacter.Id != "PiratesOnUninhabited_BadPirate" && !CheckAttribute(refCharacter,"GenQuest.ShipSituation.Explosion"))
			{
				LAi_SetCurHP(xi_refCharacter, 0.0); // умер, чтоб на форме обмена не жил
			}
		}
		
		SetShipRemovable(xi_refCharacter, true);
		SetCharacterRemovable(xi_refCharacter, true);
		
		DeleteParticles();
		CreateParticleEntity();
	}
	
	SetWindRosePoints();
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("HideInfoWindow","HideInfoWindow",0);
	SetEventHandler("ShowRPGHint1","ShowRPGHint",0);
	SetEventHandler("ShowRPGHint2","ShowRPGHint2",0);
	SetEventHandler("MouseRClickUp","ExitRPGHint",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("OnTableRClick", "OnTableRClick", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("GoodsExitCancel", "GoodsExitCancel", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu", 0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("GoToShipChange", "GoToShipChange", 0);
	SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("ExitCrewWindow","ExitCrewWindow",0);
	SetEventHandler("ExitCaptureWindow","ExitCaptureWindow",0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
	
	SetEventHandler("HireTransactionOK", "HireTransactionOK", 0);
	SetEventHandler("HireTransactionCancel", "HireTransactionCancel", 0);
	
	SetEventHandler("Event_GetWindRosePoints", "GetWindRosePoints", 0);
	SetEventHandler("Event_GetWindRoseComparePoints", "GetWindRoseComparePoints", 0);
	SetEventHandler("Event_GetGradientRingColor", "GetSpeedColor", 0);
	
    //////////////////
    SetNewGroupPicture("CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
	SetNewGroupPicture("CREW_PICTURE2", "SHIP_STATE_ICONS", "Crew");
	
	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("QuantityHold");
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("WeightHold");
	GameInterface.TABLE_LIST.hr.td3.str = "";
	GameInterface.TABLE_LIST.hr.td3.textoffset = "30,0";
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("QuantityHold");
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("WeightHold");
	GameInterface.TABLE_LIST.select = 0;
	XI_InitUniversalInput();
	XI_SetArrowsInputHandler("TABLE_LIST", &TakeGoods, &GiveGoods);
	XI_SetArrowsInputHandler("TABLE_LIST_CANNONS", &TakeGoods, &GiveGoods);
	XI_SetClickInputHandler("B_LEFT", "B_RIGHT", &TakeGoods, &GiveGoods);
	XI_SetArrowsInputHandler("CREW_TRANSFER", &TakeCrew, &GiveCrew);
	XI_SetClickInputHandler("CREW_LEFT", "CREW_RIGHT", &TakeCrew, &GiveCrew);
	
	// Выкидывание товаров
	XI_SetClickInputHandler("QTY_ADD_BUTTON", "QTY_REMOVE_BUTTON", &ADD_BUTTON, &REMOVE_BUTTON);
	XI_SetArrowsInputHandler("QTY_EDIT", &ADD_BUTTON, &REMOVE_BUTTON);
	XI_SetArrowsInputHandler("QTY_OK_BUTTON", &ADD_BUTTON, &REMOVE_BUTTON);
	XI_SetArrowsInputHandler("QTY_CANCEL_BUTTON", &ADD_BUTTON, &REMOVE_BUTTON);
	XI_SetUniversalInputTooltip("QTY_EDIT", "QTY_WINDOW");

	// Передача сдавшейся команды
	XI_SetClickInputHandler("HIRE_QTY_ADD_BUTTON", "HIRE_QTY_REMOVE_BUTTON", &HIRE_ADD_BUTTON, &HIRE_REMOVE_BUTTON);
	XI_SetArrowsInputHandler("HIRE_QTY_OK_BUTTON", &HIRE_ADD_BUTTON, &HIRE_REMOVE_BUTTON);
	XI_SetArrowsInputHandler("HIRE_QTY_CANCEL_BUTTON", &HIRE_ADD_BUTTON, &HIRE_REMOVE_BUTTON);
	XI_SetArrowsInputHandler("HIRE_QTY_EDIT_BOX", &HIRE_ADD_BUTTON, &HIRE_REMOVE_BUTTON);
	XI_SetUniversalInputTooltip("HIRE_QTY_EDIT_BOX", "HIRE_CREW_WINDOW");

	GameInterface.TABLE_LIST_CANNONS.hr.td1.str = XI_ConvertString("QuantityHold");
	GameInterface.TABLE_LIST_CANNONS.hr.td2.str = XI_ConvertString("WeightHold");
	GameInterface.TABLE_LIST_CANNONS.hr.td3.str = "";
	GameInterface.TABLE_LIST_CANNONS.hr.td3.textoffset = "30,0";
	GameInterface.TABLE_LIST_CANNONS.hr.td4.str = XI_ConvertString("QuantityHold");
	GameInterface.TABLE_LIST_CANNONS.hr.td5.str = XI_ConvertString("WeightHold");
	SetControlsTabMode(0);

	GameInterface.TABLE_LIST_CANNONS.select = 0;
	OnShipScrollChange();
	sMessageMode = "";
	SetGoodsArrows();
	// сообщение о захвате

	if(!bTransferMode && !LAi_IsDead(xi_refCharacter) && _type != "MaryCelesteTransfer" && xi_refCharacter.Id != "ShipWreck_0" &&
		xi_refCharacter.Id != "PiratesOnUninhabited_BadPirate" && !CheckAttribute(refCharacter,"GenQuest.ShipSituation")) //пленный
	{
		SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Surrendered_caption_1"));
		iGetHired = GetEnemyHiredCrew();
		if(iGetHired > 0)
		{
			xi_refCharacter.Ship.Crew.Hire = iGetHired;
			SetBackupQty();	
			SetBackupExp();		
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_" + _type)+" "+XI_ConvertString("Surrendered_wishes"));
		}
		else
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_" + _type)); 
		}
		SetCurrentNode("REMOVE_WINDOW_TEXT");
		sMessageMode = "Surrendered_Ok";
		ShowOkMessage();	
	}

	bSwap = false;
	SetNodeUsing("DROP_GOODS",false);
	CreateString(true, "CharJob", "", FONT_NORMAL, COLOR_NORMAL, 960, 290, SCRIPT_ALIGN_CENTER, 1.4);
	GameInterface.strings.CharJob = "";

	if (!bTransferMode) STH_StealShipFlag(int(refEnemyCharacter.nation), GetCharacterShipClass(refEnemyCharacter));
	InitLootCabinButton(refEnemyCharacter, _type);
}

// кнопка обыска каюты
void InitLootCabinButton(ref chr, string situation)
{
	if (bTransferMode)
	{
		SetNodeUsing("LOOT_CABIN_BUTTON", false);
		AutoLayoutCenter("OFF_CANNONS_BUTTON|LOOT_CABIN_BUTTON", 1); // перемещаем кнопку, если вместо двух одна
		return;
	}

	bool canLoot = situation != "";
	if (BRD_IsCrewGiveUpCaptain(chr, GetCrewQuantity(chr))) canLoot = false;

	SetSelectable("LOOT_CABIN_BUTTON", canLoot);
}

void ProcessExitCancel()
{
	ref realShip;
	
	if(CheckAttribute(pchar, "GoodsExp"))
	{
		notification(XI_ConvertString("GoodsExp"), "Grappling");
		if(CheckAttribute(pchar, "GoodsExp.Slaves") && int(pchar.GoodsExp.Slaves) < GetSquadronGoods(pchar, GOOD_SLAVES))
		{
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 5.0);
		}
		if(CheckAttribute(pchar, "GoodsExp.Gold") && int(pchar.GoodsExp.Gold) < GetSquadronGoods(pchar, GOOD_GOLD))
		{
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 5.0);
		}
		if(CheckAttribute(pchar, "GoodsExp.Silver") && int(pchar.GoodsExp.Silver) < GetSquadronGoods(pchar, GOOD_SILVER))
		{
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 5.0);
		}
		DeleteAttribute(pchar, "GoodsExp");
	}

	// Warship 09.07.09 Мэри Селест
	if(xi_refCharacter.id == "MaryCelesteCapitan")
	{
		realShip = GetRealShip(GetCharacterShipType(xi_refCharacter));
		realShip.TurnRate = 1; // Понижаем манёвренность, чтобы не крутилась сильно
		IDoExit(-1);
		return;
	}

	// Warship 20.08.09 Генер "Пираты на необитайке"
	if(xi_refCharacter.Id == "PiratesOnUninhabited_BadPirate")
	{
		sMessageMode = "ShipGoFreeAsk";
		GoToShipChange(); // Выход там
		return;
	}
	
	if(xi_refCharacter.Id == "ShipWreck_0")
	{
		sMessageMode = "ShipGoFreeAsk";
		GoToShipChange(); // Выход там	
		return;
	}
	
	// Ugeen - ситуация "Взрыв на вражеском корабле"
	if(CheckAttribute(refCharacter,"GenQuest.ShipSituation.Explosion") || CheckAttribute(refCharacter,"GenQuest.ShipSituation.Epidemy"))
	{
		sMessageMode = "ShipGoFreeAsk";
		GoToShipChange(); // Выход там
		return;		
	}

	 if(xi_refCharacter.Id == "CureerCap")//Jason, Голландский гамбит
	{
		sMessageMode = "ShipGoFreeAsk";
		GoToShipChange(); // Выход там	
		return;
	}

	if(xi_refCharacter.Id == "Jackman")//Jason, Сага
	{
		sMessageMode = "ShipGoFreeAsk";
		GoToShipChange(); // Выход там	
		return;
	}
	
	if(xi_refCharacter.Id == "DTSG_Kortni")//Sinistra, Длинные тени старых грехов
	{
		if (!CheckAttribute(pchar, "questTemp.DTSG_Kech"))
		{
			sMessageMode = "ShipGoFreeAsk";
			GoToShipChange(); // Выход там	
			return;
		}
	}
	
	if(xi_refCharacter.Id == "Map_Garpiya")//Гарпия
	{
		if (CheckAttribute(pchar, "questTemp.Caleuche_ReleasedHarpy"))
		{
			sMessageMode = "ShipGoFreeAsk";
			GoToShipChange(); // Выход там	
			return;
		}
	}

	if (sMessageMode == "CREW_WINDOW")
	{
		ExitCrewWindow();
		return;
	}
		
	if (!isCompanion(xi_refCharacter))
	{ // не наш корабль, соотв топим, но сперва спросим
		if (LAi_IsDead(xi_refCharacter))
		{
			string crewLeftNotification = "";
			if (GetCrewQuantity(xi_refCharacter) > 0) crewLeftNotification = NewStr() + XI_ConvertString("CrewFromSunkenShipWillSaved");
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Capture Ship"));
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_exit_1") + crewLeftNotification); // Корабль остался без капитана. Потопить его?
			SetSelectable("REMOVE_ACCEPT_OFFICER", true);
			SetCurrentNode("REMOVE_WINDOW_CAPTION");
			sMessageMode = "ShipDeadAsk";
			ShowShipChangeMenu();
		}
		else
		{//пленный кэп, живой ещё
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Surrendered_caption_2"));
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_exit_2")); // Закончить грабеж и отпустить сдавшегося капитана и его экипаж? 
			SetCurrentNode("REMOVE_WINDOW_CAPTION");
			SetSelectable("REMOVE_ACCEPT_OFFICER", true);
			sMessageMode = "ShipGoFreeAsk";
			ShowShipChangeMenu();
		}
	}
	else
	{  // наш компаньон, корабль наш, все ок
	    if (bSwap) SeaAI_SwapShipAfterAbordage(pchar, refEnemyCharacter);
	    if (xi_refCharacter.id != refEnemyCharacter.id) // новый назначенец
	    {
			SeaAI_SetOfficer2ShipAfterAbordage(xi_refCharacter, refEnemyCharacter); // to_do делать один раз на закрытии могут быть баги со множественой сменой в море
			//DeleteAttribute(xi_refCharacter, "ship"); // трем корабль
			//refEnemyCharacter.ship.type = SHIP_NOTUSED;  // если это был фантом, то он сам подохнет позже
			
			// сам стотрется, тк НР == 0 будет, а это нельзя, иначе наш офф потрется refEnemyCharacter.LifeDay = 0; // стереть при выходе, если был кэп по захвату корабля
		    refEnemyCharacter.location = "none"; 
		    
			if (bSeaActive)
			{
				if (!bTransferMode)
				{
					PostEvent("evntQuestsCheck", 400);
					ShipTaken(int(refEnemyCharacter.index), KILL_BY_ABORDAGE, int(pchar.index));
					UpdateRelations();
					RefreshBattleInterface();
				}
			}
			//DeleteAttribute(refEnemyCharacter,"ship");
			//refEnemyCharacter.ship.type = SHIP_NOTUSED;
			ClearShipTypeForPassenger();
		}
		if (bTransferMode)
		{
			IDoExit(RC_INTERFACE_ANY_EXIT);
		}
		else
		{
			if(GetMaxAutoSaves("AfterBoarding") != 0)
			{
				DeleteAfterSaveFunction();
				PostEvent("Event_NewAutoSave", 1000, "s", "AfterBoarding");
			}
			IDoExit(RC_INTERFACE_RANSACK_MAIN_EXIT);
		}
	}
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("HideInfoWindow","HideInfoWindow");
	DelEventHandler("ShowRPGHint1","ShowRPGHint");
	DelEventHandler("ShowRPGHint2","ShowRPGHint2");
	DelEventHandler("MouseRClickUp","ExitRPGHint");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("OnTableRClick", "OnTableRClick");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("GoodsExitCancel", "GoodsExitCancel");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("GoToShipChange", "GoToShipChange");
	DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitCrewWindow","ExitCrewWindow");
	DelEventHandler("ExitCaptureWindow","ExitCaptureWindow");
	DelEventHandler("eTabControlPress","procTabChange");
	XI_ExitUniversalInput();
	
	DelEventHandler("HireTransactionOK", "HireTransactionOK");
	DelEventHandler("HireTransactionCancel", "HireTransactionCancel");
	
	DelEventHandler("Event_GetWindRosePoints", "GetWindRosePoints");
	DelEventHandler("Event_GetWindRoseComparePoints", "GetWindRoseComparePoints");
	DelEventHandler("Event_GetGradientRingColor", "GetSpeedColor");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");
	
	UpdateRelations();
	
	if(bSeaActive)
	{
		RefreshBattleInterface();
	}
	if(IsEntity(&worldMap))
    {
        BI_UpdateWmInterface();
    }
	DoQuestCheckDelay("NationUpdate", 1.5);
	DoQuestCheckDelay("update_sea_after_cabin", 0.1);
	PostEvent("StopQuestCheckProcessFreeze", 100);
	if(NavyPenalty(pchar)) notification(""+XI_ConvertString("Sailing note")+NavyPenalty(pchar)+XI_ConvertString("Sailing2 note")+"","Sailing");
	// belamour обратно в меню корабля
	if(CheckAttribute(pchar, "SystemInfo.OurChar"))
	{
		DeleteAttribute(pchar, "SystemInfo.OurChar");
		interfaceResultCommand = RC_INTERFACE_TO_SHIP;
	}
	else
	{
		interfaceResultCommand = exitCode;
	}
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

// Переместить вещи из каюты капитана в трюм игрока
void LootCabin()
{
	ref cabin =	FindLocationById(GetShipCabinID(xi_refCharacter));
	if (cabin == nullptr)
	{
		trace("Error: can't loot cabin for captain: " + xi_refCharacter.id + ". Can't found cabin location.");
		return;
	}

	FillAboardCabinBox(cabin, xi_refCharacter);
	for (int i = 1; i < 5; i++)
	{
		aref box = GetAref(cabin, "box" + i);
		aref itemsList = GetAref(&box, "items");
		if (itemsList == nullptr) continue;

		int itemsListLength = GetAttributesNum(itemsList);
		PutItemToShip(SHIP_LOC_HOLD, "money", GetAttributeInt(&box, "money"));

		for (int x = 0; x < itemsListLength; x++)
		{
			aref boxItem = GetAttributeN(itemsList, x);
			string itemId = GetAttributeName(boxItem);
			if (itemId == "kaleuche_amulet1") continue;

			PutItemToShip(SHIP_LOC_HOLD, itemId, int(GetAttributeValue(boxItem)));
			Log_TestInfo("Закинули в трюм: " + itemId + " " + int(GetAttributeValue(boxItem)));
		}
	}

	SetSelectable("LOOT_CABIN_BUTTON", false);
	SetCurrentNode(CurrentGoodsTableName());
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	switch(nodName)
	{
		case "LOOT_CABIN_BUTTON":
				if (comName=="click" || comName=="activate") CallWithConfirmation(XiStr("LootPopupText"), "LootCabin", true);
		break;
		case "REMOVE_OK":
			if(comName=="click" || comName=="activate")
			{
				if(sMessageMode == "Surrendered_Ok") { ShowCrewCaptureHire(); }
			}
		break;
	
		case "CAPTURE_CAPTAIN_PRISON":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyToPrisoner();
			}
		break;
		
		case "CAPTURE_CAPTAIN_KILL":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyToKilled();
			}
		break;
		
		case "CAPTURE_CREW_PRISON":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyCrewToPrisoner();
			}
		break;
		
		case "CAPTURE_CREW_KILL":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyCrewToKilled();
			}
		break;

		case "CAPTURE_CREW_FREE":
			if(comName=="click" || comName=="activate")
			{
			    SetEnemyCrewToFree();
			}
		break;
		
		case "EXIT_BTN":
			if (comName=="click")
			{
				ExitCrewWindow();
			}
		break;
		
		case "TABLE_OTHER":
			if(comName=="click")
			{
				ShowShipFoodInfo(pchar);
				ShowShipFoodInfo(xi_refCharacter);
			}
		break;
		
		case "SWAP_BUTTON":
			if(comName=="click" || comName=="activate")
			{
			    SwapProcess();
			}
		break;
		
		case "CAPTAN_BUTTON":
			if(comName=="click" || comName=="activate")
			{
				ExitCrewWindow(); // для профилактики
				ShipChangeCaptan();
			}
		break;
		
		case "TAKE_GOODS":
			if(comName=="click" || comName=="activate")
			{
				ExitCrewWindow(); // для профилактики
				TakeAllGoods();
			}
		break;

		case "OFF_CANNONS_BUTTON":
			if(comName=="click" || comName=="activate")
			{
				ExitCrewWindow(); // для профилактики
				CallWithConfirmation(xiStr("Take Cannons Off Confirm"), "TakeCannonsOff", IsInBattle());
			}
		break;

		case "CREW_BUTTON":
			if(comName=="click" || comName=="activate")
			{
				ShowCrewWindow();
			}
		break;

		case "CREW_BACK":
			if(comName=="click" || comName=="activate")
			{
				ShowCrewWindow();
			}
		break;
	}
}

void ProcessFrame()
{
	string attributeName;
	int iCharacter;

	string sNode = GetCurrentNode();
	if (sNode == "PASSENGERSLIST" && int(GameInterface.PASSENGERSLIST.current)!= nCurScrollOfficerNum)
	{
		nCurScrollOfficerNum = int(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
	}
	if (sNode != CurrentGoodsTableName())
	{
		SetNodeUsing("B_RIGHT",  false);
		SetNodeUsing("B_LEFT", false);	
	}
}
void OnShipScrollChange()
{
	ShowShipInfo(pchar, "");
	ShowShipInfo(xi_refCharacter, "2");
	ShowShipFoodInfo(pchar);
	FillStockTable();
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(int(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
	if (isCompanion(xi_refCharacter))
	{ // наш товарищ
	
		// SetNodeUsing("MAIN_CHARACTER_PICTURE2", true);
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"CAPTAN_BUTTON",0, "#"+XI_ConvertString("Remove Captain"));
		if (GetRemovable(xi_refCharacter))
		{ // обмен с квестовыми
		    if (GetShipRemovable(xi_refCharacter))
		    {
				SetSelectable("CAPTAN_BUTTON", true);
				SetSelectable("SWAP_BUTTON", true);
			}
			else
			{
			    SetSelectable("CAPTAN_BUTTON", false);
				SetSelectable("SWAP_BUTTON", false);
				SetSelectable("OFF_CANNONS_BUTTON", false);
			}
			SetSelectable("CREW_BUTTON", true);
			SetSelectable("TAKE_GOODS", true);
		}
		else
		{
			SetSelectable("CAPTAN_BUTTON", false);
			SetSelectable("SWAP_BUTTON", false);
			SetSelectable("OFF_CANNONS_BUTTON", false);
			SetSelectable("CREW_BUTTON", false);
			SetSelectable("TAKE_GOODS", false);
		}
	}
	else
	{  // не наш, значит убит или сдался
		// Warship 09.07.09 Мэри Селест и (20.08.09) генер "Пираты на необитайке"
		// ugeen Ситуация на захваченном корабле
		//Jason Голландский гамбит
		if(xi_refCharacter.id == "MaryCelesteCapitan" || xi_refCharacter.Id == "PiratesOnUninhabited_BadPirate" || CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion") || xi_refCharacter.Id == "ShipWreck_0" || xi_refCharacter.id == "CureerCap" || xi_refCharacter.id == "Cap_Utreht" || CheckAttribute(pchar,"GenQuest.CannotTakeShip"))
		{
			SetSelectable("CAPTAN_BUTTON", false);
			SetSelectable("SWAP_BUTTON", false);
			SetSelectable("CREW_BUTTON", false);
		}
		else
		{
			if (LAi_IsDead(xi_refCharacter))
			{
				// SetNodeUsing("MAIN_CHARACTER_PICTURE2", false); // убитый кэп
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"CAPTAN_BUTTON",0, "#"+XI_ConvertString("Set Captain"));
				SetSelectable("SWAP_BUTTON", true);
				SetSelectable("OFF_CANNONS_BUTTON", true);
			}
			else
			{
				// SetNodeUsing("MAIN_CHARACTER_PICTURE2", true); // живой враг
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"CAPTAN_BUTTON",0, "#"+XI_ConvertString("Remove Captain"));
				SetSelectable("SWAP_BUTTON", false);
				SetSelectable("OFF_CANNONS_BUTTON", false);
			}
		}
	}
}

void ShowShipInfo(ref chr, string sAdd)
{
	if (LAi_IsDead(chr)) SetNewPicture("MAIN_CHARACTER_PICTURE" + sAdd, "interfaces\le\portraits\empty\empty_face.tga");
	else SetNewPicture("MAIN_CHARACTER_PICTURE" + sAdd, "interfaces\le\portraits\512\face_" + chr.FaceId + ".tga");
	
	SetShipPerks(chr, sAdd);
	int iShip = int(chr.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName + refBaseShip.ship.upgrades.hull;
		SetNewPicture("SHIP_BIG_PICTURE" + sAdd, "interfaces\le\ships\" + sShip + ".tga");
		SendMessage(&GameInterface,"lslffff",MSG_INTERFACE_MSG_TO_NODE,"SHIP_BIG_PICTURE", 1, 1.0, 0.0, 0.0, 1.0 );//отзеркаливание картинки по горизонтали

		SetFormatedText("SHIP_NAME" + sAdd, chr.ship.name);	
		SetFormatedText("SHIP_TYPE" + sAdd, XI_ConvertString(refBaseShip.BaseName));
		SetFormatedText("SHIP_RANK" + sAdd, refBaseShip.Class);
		SetShipsOTHERTable("TABLE_OTHER", pchar, chr);
	}
}

void SetShipsOTHERTable(string _tabName, ref chrLeft, ref chrRight)
{
	ref refBaseShip1 = GetRealShip(int(chrLeft.ship.type));
	ref refBaseShip2 = GetRealShip(int(chrRight.ship.type));

	SetShipOTHERTable2(_tabName, chrLeft, "td1", "td1", "td2", ".left");
	SetShipOTHERTable2(_tabName, chrRight, "", "", "td3", ".right");

	for (int i=1; i<=10; i++)
	{
		string row = "tr" + i;

		GameInterface.(_tabName).(row).td1.icon.width = 28;
		GameInterface.(_tabName).(row).td1.icon.height = 28;
		GameInterface.(_tabName).(row).td1.icon.offset = "354, 0";
		GameInterface.(_tabName).(row).td1.align = "left";
		GameInterface.(_tabName).(row).td1.textoffset = "0,2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.textoffset = "0,2";
		GameInterface.(_tabName).(row).td3.align = "right";
		GameInterface.(_tabName).(row).td3.textoffset = "20,2";

		GameInterface.(_tabName).(row).td2.icon.width = 16;
		GameInterface.(_tabName).(row).td2.icon.height = 28;
		GameInterface.(_tabName).(row).td2.icon.group = "HIRE_EFFECTS";
	}

	// сравниваем по максимально достижимым статам, учитываем только апгрейды самого корабля
	XIShip_GetCompareArrow(_tabName, "tr1", int(refBaseShip1.hp), int(refBaseShip2.hp), "Hull");
	XIShip_GetCompareArrow(_tabName, "tr2", int(refBaseShip1.MaxCrew), int(refBaseShip2.MaxCrew), "MaxCrew");
	XIShip_GetCompareArrow(_tabName, "tr4", GetCargoMaxSpace(chrLeft), GetCargoMaxSpace(chrRight), "Capacity");
	XIShip_GetCompareArrow(_tabName, "tr5", FindShipSpeedMax(chrLeft), FindShipSpeedMax(chrRight), "Speed");
	XIShip_GetCompareArrow(_tabName, "tr7", FindShipTurnrateMax(chrLeft), FindShipTurnrateMax(chrRight), "Maneuver");
	XIShip_GetCompareArrow(_tabName, "tr8", int(refBaseShip1.MaxCaliber), int(refBaseShip2.MaxCaliber), "cannonsCaliber");
	XIShip_GetCompareArrow(_tabName, "tr9", int(refBaseShip1.CannonsQuantity), int(refBaseShip2.CannonsQuantity), "cannonsQty");
	Table_UpdateWindow(_tabName);
}

void ShowShipFoodInfo(ref chr)
{

	SetFoodShipInfoShort(refCharacter, "FOOD_SHIP");
	SetFoodShipInfoShort(xi_refCharacter, "FOOD_SHIP2");
	SetRumShipInfoShort(refCharacter, "RUM_SHIP");
	SetRumShipInfoShort(xi_refCharacter, "RUM_SHIP2");
	SetMedicamentShipInfo(refCharacter, "MEDICAMENT_SHIP", "short");
	SetMedicamentShipInfo(xi_refCharacter, "MEDICAMENT_SHIP2", "short");

	SetFormatedText("MONEY_SHIP", "");
	SetFormatedText("MONEY_SHIP2", "");
	
	if (GetRemovable(chr) && isCompanion(chr)) // считаем только своих, а то всяких сопровождаемых кормить!!!
	{
		SetFormatedText("MONEY_SHIP", FindRussianMoneyString(GetSalaryForShip(refCharacter)));
		SetFormatedText("MONEY_SHIP2", FindRussianMoneyString(GetSalaryForShip(xi_refCharacter)));
	}
}
void ShowInfoWindow()
{
	string sCurrentNode = GetEventData();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int picW = 180;
	int picH = 180;
	int iItem, iCharacter, iGoodIndex;
	string sPerkName1,sPerkName2;
	string sRow, sCol;
	sPicture = "-1";
	string sAttributeName, sCharacter;
	int nChooseNum = -1;
	int nChooseCol = -1;
	int iShip;
	ref refBaseShip;
	ref chr;
	aref arShipBonus;
	
	bool bWindRose = false;
	if (XI_ShowUniversalInputTooltip(sCurrentNode)) return;

	switch (sCurrentNode)
	{
		case "SHIP_TYPE":
		    iShip = int(pchar.ship.type);
		    refBaseShip = GetRealShip(iShip);
			sHeader = XI_ConvertString(refBaseShip.BaseName);
			sText1 = GetShipDescr(refBaseShip);
		break; 
		
		case "SHIP_TYPE2":
		    iShip = int(xi_refCharacter.ship.type);
		    refBaseShip = GetRealShip(iShip);
			sHeader = XI_ConvertString(refBaseShip.BaseName);
			sText1 = GetShipDescr(refBaseShip);
		break;

		case "TABLE_LIST":
			CloseTooltipNew();
			nChooseNum = SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, CurrentGoodsTableName(), 1);
			sRow = "tr" + nChooseNum;
			if (CheckAttribute(&GameInterface, "TABLE_LIST." + sRow + ".index")) {
				iItem = sti(GameInterface.TABLE_LIST.(sRow).index)
				sHeader = XI_ConvertString(goods[iItem].name);
				sGroup = "GOODS";
				sGroupPicture = goods[iItem].name;
				sText1 = GetAssembledString(GetGoodDescr(&Goods[iItem]), &Goods[iItem]);
			} else {
				sHeader = XI_Convertstring("Goods");
				sText1  = GetRPGText("GoodsCargo_hint");
				sText2  = GetConvertStr("TakeAllGoods_hint", "ShipsDescribe.txt");	
				sText3  = GetConvertStr("GoodsKeys_hint", "ShipsDescribe.txt");
			}
		break;		
		case "TABLE_LIST_CANNONS":
			CloseTooltipNew();
			nChooseNum = SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, CurrentGoodsTableName(), 1);
			sRow = "tr" + nChooseNum;
			if (CheckAttribute(&GameInterface, "TABLE_LIST_CANNONS." + sRow + ".index")) {
				iItem = sti(GameInterface.TABLE_LIST_CANNONS.(sRow).index)
				sHeader = XI_ConvertString(goods[iItem].name);
				sGroup = "GOODS";
				sGroupPicture = goods[iItem].name;
				sText1 = GetGoodDescr(&Goods[iItem]);
				aref userdata = GameInterface.TABLE_LIST_CANNONS.(sRow).userdata$aref;
				int cannonType = int(Goods[iItem].cannonIdx);
				sText1 += XI_HumanCannonAdditionalStats(&Cannon[cannonType], cannonType);
				if (userdata.qty1$int(0) > 0) 
				{
					userdata.shipName = pchar.ship.name;
					userdata.health = XI_HumanCannonsHealth(CAN_GetCannonsStockHealth(pchar, goods[iItem].name));
					sText3 += DLG_Convert("Cannon_health_on_ship", "ShipsDescribe.txt", &userdata);
				}
				if (userdata.qty2$int(0) > 0) 
				{
					userdata.shipName = xi_refCharacter.ship.name;
					userdata.health = XI_HumanCannonsHealth(CAN_GetCannonsStockHealth(xi_refCharacter, goods[iItem].name));
					sText2 += DLG_Convert("Cannon_health_on_ship", "ShipsDescribe.txt", &userdata);
				}
			} else {
				sHeader = XI_Convertstring("Cannons");
				sText1  = GetRPGText("GoodsCannons_hint");
				sText2  = GetConvertStr("TakeAllGoods_hint", "ShipsDescribe.txt");	
				sText3  = GetConvertStr("GoodsKeys_hint", "ShipsDescribe.txt");
			}
		break;
		
		case "TABLE_OTHER":
			CloseTooltipNew();
			nChooseCol = int(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_OTHER", 3));
			refBaseShip = nChooseCol < 2 ? GetRealShip(int(pchar.ship.type)) : GetRealShip(int(xi_refCharacter.ship.type));
			ref secondChr = nChooseCol < 2 ? xi_refCharacter : pchar;
			XI_ShipTableTooltip(nChooseCol < 2 ? pchar : xi_refCharacter, refBaseShip, "TABLE_OTHER", &sHeader, &sText1, &sText2, &sText3, &sGroup, &sGroupPicture, &bWindRose, secondChr, nChooseCol < 2 ? ".left" : ".right");
		break;
		
		case "CREW_TRANSFER":	
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break; 

		case "PASSENGERSLIST":
			nChooseNum = int(SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"PASSENGERSLIST", 2 ));
			sAttributeName = "pic" + (nChooseNum+1);
			if(CheckAttribute(&GameInterface, "PASSENGERSLIST." + sAttributeName))
			{
				if(CheckAttribute(&GameInterface, "PASSENGERSLIST." + sAttributeName + ".character"))
				{
					sCharacter = GameInterface.PASSENGERSLIST.(sAttributeName).character;
					sHeader = XI_ConvertString("OfficerJob");
					sText1 = GetJobsList(sCharacter, " / ");
				}
			}
		break;
		case "MONEY_SHIP":
			sHeader = XI_Convertstring("CostPerMonth");
			sText1 = GetRPGText("Partition_hint");
		break;
		case "FOOD_SHIP":
			sHeader = XI_Convertstring("FoodShipInfoShort");
			sText1 = GetGoodDescr("Food");
		break;
		case "RUM_SHIP":
			sHeader = XI_Convertstring("RumShipInfoShort");
			sText1 = GetGoodDescr("Rum");
		break;
		case "MONEY_SHIP2":
			sHeader = XI_Convertstring("CostPerMonth");
			sText1 = GetRPGText("Partition_hint");
		break;
		case "FOOD_SHIP2":
			sHeader = XI_Convertstring("FoodShipInfoShort");
			sText1 = GetGoodDescr("Food");
		break;
		case "RUM_SHIP2":
			sHeader = XI_Convertstring("RumShipInfoShort");
			sText1 = GetGoodDescr("Rum");
		break;
		case "MEDICAMENT_SHIP":
			sHeader = XI_Convertstring("MedicamentShipInfoShort");
			sText1 = GetGoodDescr("Medicament");
		break;
		case "MEDICAMENT_SHIP2":
			sHeader = XI_Convertstring("MedicamentShipInfoShort");
			sText1 = GetGoodDescr("Medicament");
		break;
	}

	if (sCurrentNode == "SHIP_PERK1" || sCurrentNode == "SHIP_PERK2") chr = pchar;
	else chr = xi_refCharacter;

	if (XI_CrewQualityTooltip(sCurrentNode, &sHeader, &sText1, &sText2, &sText3)) return;
	SetShipPerksTooltip(chr, &sCurrentNode, &sHeader, &sText1, &sText2, &sText3, &sPicture, &sGroup, &sGroupPicture);
	if (sHeader != "") CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, picW, picH, bWindRose, false);
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
    NullSelectTable(CurrentGoodsTableName());
    NullSelectTable("TABLE_OTHER");
    NullSelectTable("TABLE_CREW");
    SetGoodsArrows();
	SetNodeUsing("DROP_GOODS",true);
}

void OnTableRClick()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
	iSelectedCol = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
	CurCol   =  "td" + (iSelectedCol);
	Table_UpdateWindow(sControl);
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", false);
		sMessageMode = "";
	}
}

void ShowRPGHint()
{
	SetSPECIALMiniTable("TABLE_SMALLSKILL2", pchar);
    SetOTHERMiniTable("TABLE_SMALLOTHER2", pchar);
    SetFormatedText("RPG_NAME", GetFullName(pchar));
	        
	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";
}

void ShowRPGHint2()
{
	if(xi_refCharacter.id == "DeadShipCap")
		return;
	SetSPECIALMiniTable("TABLE_SMALLSKILL2", xi_refCharacter);
    SetOTHERMiniTable("TABLE_SMALLOTHER2", xi_refCharacter);
    SetFormatedText("RPG_NAME", GetFullName(xi_refCharacter));
	        
	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";	
}

void FillStockTableWithCannons()
{
	int n, i, qty2, qty1;
	string row;
	ref rShip;
	string sGood;
	ref good;
	
	Table_Clear("TABLE_LIST_CANNONS", false, true, false);
	n = 1;
	if (!CheckAttribute(&GameInterface, "TABLE_LIST_CANNONS.BackUp"))
	{
		GameInterface.TABLE_LIST_CANNONS.select = 0;
		GameInterface.TABLE_LIST_CANNONS.top    = 0;
		GameInterface.TABLE_LIST_CANNONS.BackUp = true;
	}
	for (i = 0; i< GetArraySize(&Goods); i++)
	{
		row = "tr" + n;
		good = &Goods[i];
		sGood = good.name;
		qty1 = GetCargoGoods(pchar, i);
		qty2 = GetCargoGoods(xi_refCharacter, i);
		if (qty2 <= 0 && qty1 <= 0) continue; // только не нули
		if (!CheckAttribute(good, "CannonIdx")) continue;
		
		aref userdata = touchattr(GameInterface.TABLE_LIST_CANNONS.(row).userdata);
		userdata.qty1 = qty1;
		userdata.qty2 = qty2;
		GameInterface.TABLE_LIST_CANNONS.(row).index = i;
		
		GameInterface.TABLE_LIST_CANNONS.(row).td1.str = qty1;
		if (qty1 > 0)
		{
			GameInterface.TABLE_LIST_CANNONS.(row).td1.icon.group = "CANNONS_MANAGEMENT";
			GameInterface.TABLE_LIST_CANNONS.(row).td1.icon.image = XI_GetCannonsHealthIconForStock(pchar, good);
			GameInterface.TABLE_LIST_CANNONS.(row).td1.icon.offset = "54, 2";
			GameInterface.TABLE_LIST_CANNONS.(row).td1.icon.width = 35;
			GameInterface.TABLE_LIST_CANNONS.(row).td1.icon.height = 35;
		}
		GameInterface.TABLE_LIST_CANNONS.(row).td2.str = GetGoodWeightByType(i, qty1);
		GameInterface.TABLE_LIST_CANNONS.(row).td4.str = qty2;
		if (qty2 > 0)
		{
			GameInterface.TABLE_LIST_CANNONS.(row).td4.icon.group = "CANNONS_MANAGEMENT";
			GameInterface.TABLE_LIST_CANNONS.(row).td4.icon.image = XI_GetCannonsHealthIconForStock(xi_refCharacter, good);
			GameInterface.TABLE_LIST_CANNONS.(row).td4.icon.offset = "54, 2";
			GameInterface.TABLE_LIST_CANNONS.(row).td4.icon.width = 35;
			GameInterface.TABLE_LIST_CANNONS.(row).td4.icon.height = 35;
		}
		GameInterface.TABLE_LIST_CANNONS.(row).td5.str = GetGoodWeightByType(i, qty2);
		GameInterface.TABLE_LIST_CANNONS.(row).td3.icon.group = "GOODS";
		GameInterface.TABLE_LIST_CANNONS.(row).td3.icon.image = sGood;
		GameInterface.TABLE_LIST_CANNONS.(row).td3.icon.offset = "-8, 0";
		GameInterface.TABLE_LIST_CANNONS.(row).td3.icon.width = 40;
		GameInterface.TABLE_LIST_CANNONS.(row).td3.icon.height = 40;
		GameInterface.TABLE_LIST_CANNONS.(row).td3.textoffset = "58,0";
		GameInterface.TABLE_LIST_CANNONS.(row).td3.align = "left";
		GameInterface.TABLE_LIST_CANNONS.(row).td3.str = XI_ConvertString(sGood +"_s");
		n++;
	}
	RestoreTableSorting("TABLE_LIST_CANNONS");
	Table_UpdateWindow("TABLE_LIST_CANNONS");
}

void FillGoodsTable()
{
	int n, i, qty2, qty1;
	string row;
	ref rShip;
	string sGood;
	ref good;
	
	Table_Clear("TABLE_LIST", false, true, false);
	n = 1;
	if (!CheckAttribute(&GameInterface, "TABLE_LIST.BackUp"))
	{
		GameInterface.TABLE_LIST.select = 0;
		GameInterface.TABLE_LIST.top    = 0;
		GameInterface.TABLE_LIST.BackUp = true;
	}
	for (i = 0; i< GetArraySize(&Goods); i++)
	{
		row = "tr" + n;
		good = &Goods[i];
		sGood = good.name;
		qty1 = GetCargoGoods(pchar, i);
		qty2 = GetCargoGoods(xi_refCharacter, i);
		if (qty2 <= 0 && qty1 <= 0) continue; // только не нули
		if (CheckAttribute(good, "CannonIdx")) continue;

		GameInterface.TABLE_LIST.(row).index = i;
		
		GameInterface.TABLE_LIST.(row).td1.str = qty1;
		GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, qty1);
		GameInterface.TABLE_LIST.(row).td4.str = qty2;
		GameInterface.TABLE_LIST.(row).td5.str = GetGoodWeightByType(i, qty2);
		GameInterface.TABLE_LIST.(row).td6.str = good.Units + " / " + good.Weight;

		GameInterface.TABLE_LIST.(row).td3.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td3.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td3.icon.offset = "-5, 0";
		GameInterface.TABLE_LIST.(row).td3.icon.width = 40;
		GameInterface.TABLE_LIST.(row).td3.icon.height = 40;
		GameInterface.TABLE_LIST.(row).td3.textoffset = "30,0";
		GameInterface.TABLE_LIST.(row).td3.str = XI_ConvertString(sGood);
		n++;
	}
	RestoreTableSorting("TABLE_LIST");
	Table_UpdateWindow("TABLE_LIST");
}

void FillStockTable()
{
	bool isCannonsMode = goodsMode == 1;
	SetNodeUsing("TABLE_LIST_CANNONS", isCannonsMode);
	SetNodeUsing("SCROLL_LIST_CANNONS", isCannonsMode);
	SetNodeUsing("TABLE_LIST", !isCannonsMode);
	SetNodeUsing("SCROLL_LIST", !isCannonsMode);
	if (goodsMode == 1) FillStockTableWithCannons();
	else FillGoodsTable();
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
		XI_WindowDisable("GOODS_WINDOW", true);
		SetCurrentNode("QTY_CANCEL_BUTTON");
	}
}

void GoodsExitCancel()
{
	
	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowDisable("GOODS_WINDOW", false);

	// пересчитаем новые пареметры от веса
	if (iShipQty != GetCargoGoods(pchar, iCurGoodsIdx))
	{
		SetCharacterGoods(pchar, iCurGoodsIdx, iShipQty); // вернём обратно
		CAN_UpdateDamageInStock(pchar, &Goods[iCurGoodsIdx]);
		OnShipScrollChange();
	}
	SetCurrentNode(CurrentGoodsTableName());
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;

	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
	string goodsDescr = GetAssembledString(GetGoodDescr(&Goods[iGoodIndex]), &Goods[iGoodIndex]);
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
	
	iShipQty = GetCargoGoods(pchar, iGoodIndex);
	SetFormatedText("QTY_INFO_SHIP_QTY", string(iShipQty));
	SetFormatedText("QTY_INFO_STORE_QTY", string(GetGoodWeightByType(iGoodIndex, iShipQty)));
}

void TransactionOK()
{
	int nTradeQuantity;
	confirmChangeQTY_EDIT();
	nTradeQuantity = int(GameInterface.qty_edit.str);

    SetCharacterGoods(pchar, iCurGoodsIdx, iShipQty);
	if (nTradeQuantity > 0)
	{
		DropGoodsToSeaFromInterface(iCurGoodsIdx, nTradeQuantity); // остаётся плавать в море
		iShipQty = GetCargoGoods(pchar, iCurGoodsIdx);
		CAN_UpdateDamageInStock(pchar, &Goods[iCurGoodsIdx]);
		FillStockTable();
	}
	ShipSituation_SetQuestSituation(ShipSituation_1);
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
	SetCharacterGoods(pchar, iCurGoodsIdx, iShipQty);
	if (iWeight > 0)
	{
		RemoveCharacterGoods(pchar, iCurGoodsIdx, iWeight);
	}
	OnShipScrollChange();
}

void REMOVE_BUTTON(int value)  // продать
{
	GameInterface.qty_edit.str = (int(GameInterface.qty_edit.str) + iUnits*value);
	ChangeQTY_EDIT();
}

void ADD_BUTTON(int value)  // купить
{
	GameInterface.qty_edit.str = (int(GameInterface.qty_edit.str) - iUnits*value);
	if (int(GameInterface.qty_edit.str) < 0) GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void DropGoodsToSeaFromInterface(int iGoodIndex, int iQuantity)
{
	ref rGood;
	string sGood;

	sGood = Goods[iGoodIndex].name;

	if (CheckAttribute(pchar, "Ship.Cargo.Goods."+sGood))
	{		
		RemoveCharacterGoods(pchar, iGoodIndex, iQuantity);
		if (bSeaActive && !bAbordageStarted)  // море, но не каюта
		{
			iQuantity = iQuantity / int(Goods[iGoodIndex].Units);
	
			int iSwimQuantity = rand(iQuantity/4) + rand(iQuantity/4) + rand(iQuantity/4) + rand(iQuantity/4);
	
			if(iSwimQuantity < 1)
			{
				iSwimQuantity = 1;
			}
	
			RecalculateCargoLoad(pchar);
	
			if (CheckAttribute(&Goods[iGoodIndex], "Swim")) 
			{ 
				float fTime = float(Goods[iGoodIndex].Swim.Time);
				string sModel = Goods[iGoodIndex].Swim.Model;
	
				fTime = fTime + (frnd() - 0.5) * fTime / 2.0;
	
				AISeaGoods_AddGood(pchar, sGood, sModel, fTime * 60.0, iSwimQuantity);
			}
		}
	}
}

void ShipChangeCaptan()
{
	if (isCompanion(xi_refCharacter))
	{ // наш товарищ
		if (!CheckAttribute(xi_refCharacter, "Tasks.Clone")) //zagolski. баг с двойниками в каюте
		{
		SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Captain"));
		SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChangeCaptan1")); // Сместить капитана?
		SetSelectable("REMOVE_ACCEPT_OFFICER", true);
		sMessageMode = "ShipChangeCaptanRemove";
		ShowShipChangeMenu();
	}
	else
	{
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Captain"));
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChangeCaptan2")); // В данный момент этот капитан не может быть смещен
			sMessageMode = "ShipChangeCaptanMessage";
			ShowOkMessage();
		}
	}
	else
	{
		// если пленный
		if (!LAi_IsDead(xi_refCharacter))
		{
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Surrendered_caption_2"));
			if (!CheckAttribute(xi_refCharacter, "Tasks.Clone")) SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_text_2"));
			else SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChangeCaptan3")); // Этот капитан в данный момент не может быть снят
			SetSelectable("REMOVE_ACCEPT_OFFICER", true);
			sMessageMode = "SurrenderedCaptanRemove";
			ShowShipChangeMenu();
		}
		else
		{
			/// проверка на доступных капитанов
			if (!bPassengersAccess())
			{
				SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Capture Ship"));
				SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChangeCaptan5")); // У вас нет доступных офицеров.\n Назначение капитана невозможно
				sMessageMode = "ShipChangeCaptanMessage";
				ShowOkMessage();
			}
			else
			{
				// проверка на 5 кораблей
				if (GetCompanionQuantity(PChar) < COMPANION_MAX)
				{
					FillScrollWithCharacters(&NullCharacter, "PASSENGERSLIST", "IsFellowAbleToBeCompanionOnBoarding", false, &nCurScrollOfficerNum, -1);
				    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
				    SetCurrentNode("PASSENGERSLIST");
					ProcessFrame();
					SetOfficersSkills();

					XI_WindowShow("OFFICERS_WINDOW", true);
					XI_WindowDisable("OFFICERS_WINDOW", false);
					XI_WindowDisable("MAIN_WINDOW", true);
					XI_WindowDisable("GOODS_WINDOW", true);
					XI_WindowShow("GOODS_WINDOW", false);
				}
				else
				{
				    SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Capture Ship"));
					SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChangeCaptan6")); // В эскадре героя может быть только пять кораблей
					sMessageMode = "ShipChangeCaptanMessage";
					ShowOkMessage();
				}
			}
		}
	}
}

void ExitShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowDisable("GOODS_WINDOW", false);
	XI_WindowShow("GOODS_WINDOW", true);
	sMessageMode = "";
	SetCurrentNode(CurrentGoodsTableName());
}

void GoToShipChange() // нажатие ОК на табличке ок-отмена
{
	ref     sld;
	aref    arTo, arFrom;
	
	switch (sMessageMode)
	{
		case "SurrenderedCaptanRemove":  // убрать сдавшегося капитана
			ExitShipChangeMenu();
			// первый проход - кэп ещё жив
			SetFormatedText("CAPTURE_TEXT", XI_ConvertString("Surrendered_captain_capture"));
			SetNewPicture("CAPTURE_PICTURE", "interfaces\le\portraits\512\face_" + xi_refCharacter.FaceId + ".tga");
			ShowCaptureWindow();
			SetCurrentNode("CAPTURE_CANCEL");
		break;
		
		case "ShipChangeCaptanRemove":  // снять кэпа
			sld = GetCharacter(NPC_GenerateCharacter("DeadShipCap", "off_hol_2", "man", "man", 60, int(pchar.nation), 0, true, "citizen")); // фантом, на время
			sld.faceId = 666;
			sld.name = "";
			sld.lastname = "";
			DeleteAttribute(sld,"ship");
			sld.ship = "";
			LAi_SetCurHP(sld, 0.0); // умер
			 
			makearef(arTo,   sld.ship);
			makearef(arFrom, xi_refCharacter.Ship);
			CopyAttributes(arTo, arFrom);

			//SeaAI_SetOfficer2ShipAfterAbordage(sld, xi_refCharacter); // to_do делать один раз на закрытии могут быть баги со множественой сменой в море
			// убить на выходе
			//DeleteAttribute(xi_refCharacter,"ship"); // трем корабль
			//xi_refCharacter.ship.type = SHIP_NOTUSED;
			// снимем компаньона в офы -->
			RemoveCharacterCompanion(pchar, xi_refCharacter);
			AddPassenger(pchar, xi_refCharacter, false);
			DelBakSkill();
			// снимем компаньона в офы <--
			xi_refCharacter = sld;
			ExitShipChangeMenu();
			CheckQuestAboardCabinSituation(xi_refCharacter);
			OnShipScrollChange();
		break;
		
		case "ShipDeadAsk": // выход с убиением корабля

			if(CheckAttribute(pchar, "SystemInfo.OurChar")) // belamour если решили потопить, то трем атрибут
			{
				DeleteAttribute(pchar, "SystemInfo.OurChar");
			}
            if (bSwap) {
				ShipSituation_SetQuestSituation(ShipSituation_3);
				SeaAI_SwapShipAfterAbordage(pchar, refEnemyCharacter);
			}	
			if (xi_refCharacter.id != refEnemyCharacter.id) // новый назначенец
			{
				ShipSituation_SetQuestSituation(ShipSituation_2);
				SeaAI_SetOfficer2ShipAfterAbordage(xi_refCharacter, refEnemyCharacter); // to_do делать один раз на закрытии могут быть баги со множественой сменой в море
			}
			// убить на выходе
			if (bSeaActive)
			{
				SaveCrewFromSunkenShip(xi_refCharacter);
				if (bTransferMode)
				{
					ShipDead(int(xi_refCharacter.index), KILL_BY_SELF, int(pchar.index));  // сами же и топим
				}
				else
				{
					ShipDead(int(xi_refCharacter.index), KILL_BY_ABORDAGE, int(pchar.index));
				}
			}
			CheckQuestAboardCabinSituation(xi_refCharacter);
			//DeleteAttribute(refEnemyCharacter,"ship");
			//refEnemyCharacter.ship.type = SHIP_NOTUSED;
			ClearShipTypeForPassenger();
			if (bTransferMode)
			{
				IDoExit(RC_INTERFACE_ANY_EXIT);
			}
			else
			{
				if(GetMaxAutoSaves("AfterBoarding") != 0)
				{
					DeleteAfterSaveFunction();
					PostEvent("Event_NewAutoSave", 1000, "s", "AfterBoarding");
				}
				IDoExit(RC_INTERFACE_RANSACK_MAIN_EXIT);
			}
		break;
		
		case "ShipGoEscape":
		
		break;
		
		// отпустить кэпа
		case "ShipGoFreeAsk":
			sld = GetCharacter(NPC_GenerateCharacter(refEnemyCharacter.id + "_free", "off_hol_2", "man", "man", 60, int(refEnemyCharacter.nation), 0, true, "citizen")); // фантом, на время
			ChangeAttributesFromCharacter(sld, refEnemyCharacter, false);
			DeleteAttribute(sld, "ship");
			sld.ship = "";
			 
			makearef(arTo,   sld.ship);
			makearef(arFrom, refEnemyCharacter.Ship);
			CopyAttributes(arTo, arFrom);
			
			if(CheckAttribute(refCharacter,"GenQuest.ShipSituation.Explosion")){ LAi_SetCurHP(refEnemyCharacter, 0.0); }

			sld.AlwaysFriend = true;
			sld.Abordage.Enable    = false; // запрет абордажа
			// Jason: идёт квест Саги, возврат фрегата Даниэль
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "after_boarding")
			{
				sld.name = GetCharacterName("Danielle");
				sld.lastname = GetCharacterName("Hawk");
				sld.DontDeskTalk = true;
				sld.FaceId = 253;
				sld.ShipEnemyDisable  = true;
				LAi_SetImmortal(sld, true);
			}
			// Голлндский гамбит, против всех, курьерская бригантина 260912
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent")
			{
				sld.DontDeskTalk = true;
				sld.ShipEnemyDisable  = true;
				LAi_SetImmortal(sld, true);
			}
			// на случай диалдога на палубе потом
			if(xi_refCharacter.Id == "PiratesOnUninhabited_BadPirate")
			{
				sld.Dialog.Filename = "GenQuests_Dialog.c";
				sld.greeting        = "Gr_MiddPirate";
				sld.DeckDialogNode  = "PiratesOnUninhabited_50_Deck1";
			}
			else
			{
				sld.Dialog.Filename = "Capitans_dialog.c";
                // нет такого звука
				// sld.greeting        = "Gr_Commander";
				sld.DeckDialogNode  = "Go_away";
			}
		    
			xi_refCharacter = sld;
			// обмена кораблями тут нет
			//SeaAI_SetOfficer2ShipAfterAbordage(xi_refCharacter, refEnemyCharacter);
			SeaAI_SetCaptainFree(xi_refCharacter, refEnemyCharacter);
		    refEnemyCharacter.location = "none"; 
		    
			if (bSeaActive)
			{
				if (!bTransferMode)
				{
					PostEvent("evntQuestsCheck", 400);
					ShipTakenFree(int(refEnemyCharacter.index), KILL_BY_ABORDAGE, int(pchar.index)); // тут умер реальный кэп, апдайтим ещё
					SetCharacterRelationBoth(int(xi_refCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
					UpdateRelations();
					RefreshBattleInterface();
					CheckQuestAboardCabinSituation(xi_refCharacter);
					DoQuestCheckDelay("NationUpdate", 1.5);
				}
			}
			ClearShipTypeForPassenger();
			if (bTransferMode)
			{
				IDoExit(RC_INTERFACE_ANY_EXIT);
			}
			else
			{
				if(GetMaxAutoSaves("AfterBoarding") != 0)
				{
					DeleteAfterSaveFunction();
					PostEvent("Event_NewAutoSave", 1000, "s", "AfterBoarding");
				}
				IDoExit(RC_INTERFACE_RANSACK_MAIN_EXIT);
			}
		break;
	}
}

void ShowShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowDisable("GOODS_WINDOW", true);
    SetNodeUsing("REMOVE_OK", false);
	SetNodeUsing("REMOVE_ACCEPT_OFFICER", true);
	SetNodeUsing("REMOVE_CANCEL_OFFICER", true);
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_WINDOW_TEXT", 5 );
	SetCurrentNode("REMOVE_CANCEL_OFFICER");
}

void ShowOkMessage()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowDisable("GOODS_WINDOW", true);

    SetNodeUsing("REMOVE_OK", true);
	SetNodeUsing("REMOVE_ACCEPT_OFFICER", false);
	SetNodeUsing("REMOVE_CANCEL_OFFICER", false);
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"REMOVE_WINDOW_TEXT", 5 );
	SetCurrentNode("REMOVE_OK");
}

void ShowOtherClick()
{
	// test не работает  :( CreateMessageBox("sCaptionID", "sMessageID", "", "", "", "");
}

void SwapProcess()
{
	SeaAI_SwapShipsAttributes(pchar, xi_refCharacter);
	if (xi_refCharacter.id == refEnemyCharacter.id)
	{
	//	SeaAI_SwapShipAfterAbordage(pchar, xi_refCharacter);
	}
    bSwap = !bSwap;
    // оптимизация скилов -->
    DelBakSkill();
    // оптимизация скилов <--
	Event(EVENT_CT_UPDATE, "a", xi_refCharacter);
	Event(EVENT_CT_UPDATE, "a", pchar);
	OnShipScrollChange();
	ExitCrewWindow(); // для профигактики
}

//////////////
void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowDisable("GOODS_WINDOW", false);
	XI_WindowShow("GOODS_WINDOW", true);
	GameInterface.strings.CharJob = "";
	SetCurrentNode(CurrentGoodsTableName());
}

void AcceptAddOfficer()
{
	string  attributeName2 = "pic"+(nCurScrollOfficerNum+1);
    ref     sld;
	aref    arTo, arFrom;
    if (checkAttribute(&GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
    {
		int iChar = int(GameInterface.PASSENGERSLIST.(attributeName2).character);
        // назначение нового кэпа, возможно, если там уже не наш, те или враг или снят
        sld = GetCharacter(iChar);
		DeleteAttribute(sld,"ship");
		sld.ship = "";
		
		makearef(arTo,   sld.ship);
		makearef(arFrom, xi_refCharacter.Ship);
		CopyAttributes(arTo, arFrom);
		// снимем пассажира -->
		CheckForReleaseOfficer(iChar); 
		RemovePassenger(pchar, sld);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
			
		xi_refCharacter = sld;
		DelBakSkill();
	}
	ExitOfficerMenu();
	// оптимизация скилов -->
    DelBakSkill();
    // оптимизация скилов <--
	OnShipScrollChange();
}

void SetOfficersSkills()
{
	string sCharacter = "pic"+(int(GameInterface.PASSENGERSLIST.current)+1);
	if (checkAttribute(&GameInterface, "PASSENGERSLIST."+sCharacter))
	{
		if (checkAttribute(&GameInterface, "PASSENGERSLIST."+sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[int(sCharacter)];
	        SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
	        SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
	        SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
			GameInterface.strings.CharJob = GetJobsList(otherchr, " / ");
	        SetSelectable("ACCEPT_ADD_OFFICER", true);
	        return;
        }
	}
    Table_Clear("TABLE_SMALLSKILL", false, true, true);
    Table_Clear("TABLE_SMALLOTHER", false, true, true);
    SetFormatedText("OFFICER_NAME", "");
	GameInterface.strings.CharJob = "";
	SetSelectable("ACCEPT_ADD_OFFICER", false);
}

void DelBakSkill()
{
	DelBakSkillAttr(xi_refCharacter);
    ClearCharacterExpRate(xi_refCharacter);
    RefreshCharacterSkillExpRate(xi_refCharacter);
    SetEnergyToCharacter(xi_refCharacter);
    DeleteAttribute(xi_refCharacter, "TmpSkillRecall");
    
    DelBakSkillAttr(pchar);
    ClearCharacterExpRate(pchar);
    RefreshCharacterSkillExpRate(pchar);
    SetEnergyToCharacter(pchar);
    DeleteAttribute(pchar, "TmpSkillRecall");
}

void ClearShipTypeForPassenger()
{
	int iPassenger;
	
	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			characters[iPassenger].ship.type = SHIP_NOTUSED; //пассажиры по определению не могут иметь корабли
		}
	}
}

void TakeAllGoods()
{
	int i, j, idx, qty;
	float fMaxCost;
	
	for (j = 0; j< GetArraySize(&Goods); j++)
	{
		fMaxCost = 0;
		idx = -1; 
		for (i = 0; i< GetArraySize(&Goods); i++)
		{
			if (GetCargoGoods(xi_refCharacter, i) > 0)
			{
				if (fMaxCost < float(Goods[i].Cost)/float(Goods[i].Weight)) // поиск ликвидного товара
				{
					fMaxCost = float(Goods[i].Cost)/float(Goods[i].Weight);
					idx = i;
				} 
			}
		}
		if (fMaxCost > 0)
		{
			qty = AddCharacterGoodsSimple(pchar, idx, GetCargoGoods(xi_refCharacter, idx));
			if (qty > 0)
			{
				RemoveCharacterGoodsSelf(xi_refCharacter, idx, qty);
			}
			else
			{   // нет места
				OnShipScrollChange();
				ShipSituation_SetQuestSituation(ShipSituation_1);
				return;
			}
		}
	}
	OnShipScrollChange();
	ShipSituation_SetQuestSituation(ShipSituation_1);
	ExitCrewWindow(); // для профилактики
}

void SetGoodsArrows()
{
    int  idx;
    int  iLine;
	if (CurTable == CurrentGoodsTableName())
	{
		int offset = CurTable == "TABLE_LIST_CANNONS" ? 18 : 0;
	    if (GetRemovable(xi_refCharacter) && CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) // с купцами нельзя
	    {
			idx = int(GameInterface.(CurTable).(CurRow).index);
		    iLine = iSelected - 1 - int(GameInterface.(CurTable).top);
			if  (GetCargoGoods(pchar, idx) > 0 && GetGoodQuantityByWeight(idx, GetCargoFreeSpace(xi_refCharacter)) > 0)
	        {
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_RIGHT",0, 1030+offset*2,552 + 40*iLine,1055+offset*2,552 + 40 + 40*iLine, 0);
				SetNodeUsing("B_RIGHT", true);
	        }
	        else
	        {
	        	SetNodeUsing("B_RIGHT",  false);
	        }
	        if (GetCargoGoods(xi_refCharacter, idx) > 0 && GetGoodQuantityByWeight(idx, GetCargoFreeSpace(pchar)) > 0)
	        {
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_LEFT",0, 880-offset,552 + 40*iLine,905-offset,552 + 40 + 40*iLine, 0);

	            SetNodeUsing("B_LEFT", true);
	        }
	        else
	        {
	        	SetNodeUsing("B_LEFT", false);	
	        }
	        return;
        }
	}
	SetNodeUsing("B_RIGHT",  false);
	SetNodeUsing("B_LEFT", false);	
}

void TakeGoods(int inc)
{  // лево
	int  idx;
	int  qty; 
	
	if (!GetRemovable(xi_refCharacter)) return; // с купцами нельзя
	
	if (CurTable == CurrentGoodsTableName())
	{
		idx = int(GameInterface.(CurTable).(CurRow).index);
		inc = int(Goods[idx].Units) * inc;
		if (inc > GetCargoGoods(xi_refCharacter, idx)) inc = GetCargoGoods(xi_refCharacter, idx);
		if (inc > 0)
		{
			qty = AddCharacterGoodsSimple(pchar, idx, inc);
			if (qty > 0)
			{
				CAN_TransferCannons(xi_refCharacter, pchar, &Goods[idx], qty);
				RemoveCharacterGoodsSelf(xi_refCharacter, idx, qty);
			}
			OnShipScrollChange();
			SetGoodsArrows();
			ShipSituation_SetQuestSituation(ShipSituation_1);
		}
	}	
}

void GiveGoods(int inc)
{  // право
	int  idx;
	int  qty; 
	
	if (!GetRemovable(xi_refCharacter)) return; // с купцами нельзя
	
	if (CurTable == CurrentGoodsTableName())
	{
		idx = int(GameInterface.(CurTable).(CurRow).index);
		inc = int(Goods[idx].Units) * inc;
		if (inc > GetCargoGoods(pchar, idx)) inc = GetCargoGoods(pchar, idx);
		if (inc > 0)
		{
			qty = AddCharacterGoodsSimple(xi_refCharacter, idx, inc);
			if (qty > 0)
			{
				CAN_TransferCannons(pchar, xi_refCharacter, &Goods[idx], qty);
				RemoveCharacterGoodsSelf(pchar, idx, qty);
			}
			OnShipScrollChange();
			SetGoodsArrows();
			ShipSituation_SetQuestSituation(ShipSituation_1);
		}
	}	
}
////////////////////////////// crew ///////////////
void ShowCrewWindow()
{
	if (sMessageMode == "CREW_WINDOW")
	{
		ExitCrewWindow();
	}
	else
	{
		if (!isCompanion(xi_refCharacter) && !LAi_IsDead(xi_refCharacter))// пленный кэп
		{
			SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("Surrendered_caption_1"));
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("Surrendered_text_1")); // Невозможно перемещать экипаж между не своими кораблями. ...
			sMessageMode = "SurrenderedCrewOkMessage";
			ShowOkMessage();
		}
		else
		{
			SetCrewVariable();
			
			XI_WindowShow("CREW_WINDOW", true);
			XI_WindowDisable("CREW_WINDOW", false);
			SetNodeUsing(CurrentGoodsTableName(),false);
			SetNodeUsing("SCROLL_LIST",false);
			SetNodeUsing("DROP_GOODS",false);
			SetNodeUsing("DROP_GOODS",false);
			SetNodeUsing("CREW_BUTTON",false);
			SetNodeUsing("CREW_BACK",true);
			XI_WindowShow("GOODS_WINDOW", false);
			XI_WindowDisable("GOODS_WINDOW", true);
		
			SetCurrentNode("CREW_TRANSFER");
			sMessageMode = "CREW_WINDOW";
		}
	}
}
void SetCrewVariable()
{
	string sText, sTextSecond;
	int iColor;

	SetFormatedText("CREW_QTY", ""+GetCrewQuantity(pchar));
	if (GetCrewQuantity(pchar) > GetOptCrewQuantity(pchar) || GetCrewQuantity(pchar) < GetMinCrewQuantity(pchar))
	{
		iColor = argb(255,255,64,64);
	}
	else
	{
		iColor = argb(255,255,255,255);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREW_QTY", 8,-1,iColor);
	SetFormatedText("CREW_QTY2", ""+GetCrewQuantity(xi_refCharacter));
	if (GetCrewQuantity(xi_refCharacter) > GetOptCrewQuantity(xi_refCharacter) || GetCrewQuantity(xi_refCharacter) < GetMinCrewQuantity(xi_refCharacter))
	{
		iColor = argb(255,255,64,64);
	}
	else
	{
		iColor = argb(255,255,255,255);
	}

	XI_SetCrewQualityStates(pchar);
	XI_SetCrewQualityStates(xi_refCharacter, "2");

	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREW_QTY2", 8,-1,iColor);
}

void ExitCrewWindow()
{
	XI_WindowShow("CREW_WINDOW", false);
	XI_WindowDisable("CREW_WINDOW", true);
	XI_WindowShow("GOODS_WINDOW", true);
	XI_WindowDisable("GOODS_WINDOW", false);
	SetNodeUsing("SCROLL_LIST",true);
	SetNodeUsing("DROP_GOODS",true);
	SetNodeUsing("CREW_BUTTON",true);
	SetNodeUsing("CREW_BACK",false);
	sMessageMode = "";
	FillStockTable();
	SetCurrentNode(CurrentGoodsTableName());
}

void TakeCrew(int inc)
{
	XI_TransferCrew(xi_refCharacter, pchar, inc);
}

void GiveCrew(int inc)
{
	XI_TransferCrew(pchar, xi_refCharacter, inc);
}

void XI_TransferCrew(ref fromChr, ref toChr, int amount)
{
	int toMaxCommand = GetMaxCrewQuantity(toChr);
	int fromCurrentCommand = GetCrewQuantity(fromChr);
	int toCurrentCommand = GetCrewQuantity(toChr);
	int freeSpace = GetCargoFreeSpace(toChr);
	amount = func_min(amount, fromCurrentCommand);
	if ((toCurrentCommand + amount) > toMaxCommand) amount = toMaxCommand - toCurrentCommand; 
	if (amount > freeSpace) amount = freeSpace;
	if (amount < 1) return;

	float fTemp =  float(toCurrentCommand + amount);
	toChr.Ship.Crew.Exp = (GetCrewExp(toChr)*toCurrentCommand + GetCrewExp(fromChr)*amount) / fTemp;
	toChr.Ship.Crew.morale = (GetCharacterCrewMorale(toChr)*toCurrentCommand + GetCharacterCrewMorale(fromChr)*amount) / fTemp;

	SetCrewQuantity(toChr, toCurrentCommand + amount);
	SetCrewQuantity(fromChr, fromCurrentCommand - amount);
	ShowShipInfo(pchar, "");
	ShowShipInfo(IsMainCharacter(fromChr) ? toChr : fromChr, "2");
	SetCrewVariable();
}

/////////////////////////////// capture_window
void ExitCaptureWindow()
{
	XI_WindowShow("CAPTURE_WINDOW", false);
	XI_WindowDisable("CAPTURE_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowShow("GOODS_WINDOW", true);
	XI_WindowDisable("GOODS_WINDOW", false);

	sMessageMode = "";
	SetCurrentNode(CurrentGoodsTableName());
}

void ShowCaptureWindow()
{
	XI_WindowShow("CAPTURE_WINDOW", true);
	XI_WindowDisable("CAPTURE_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowShow("GOODS_WINDOW", false);
	XI_WindowDisable("GOODS_WINDOW", true);
	sMessageMode = "CAPTURE_WINDOW";
}

void ExitCaptureCrewWindow()
{
	XI_WindowShow("CAPTURE_CREW_WINDOW", false);
	XI_WindowDisable("CAPTURE_CREW_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowShow("GOODS_WINDOW", true);
	XI_WindowDisable("GOODS_WINDOW", false);

	sMessageMode = "";
	SetCurrentNode(CurrentGoodsTableName());
}

void ShowCaptureCrewWindow()
{
	XI_WindowShow("CAPTURE_CREW_WINDOW", true);
	XI_WindowDisable("CAPTURE_CREW_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowShow("GOODS_WINDOW", false);
	XI_WindowDisable("GOODS_WINDOW", true);
	sMessageMode = "";
}

void ShowHireCrewWindow()
{
	XI_WindowShow("HIRE_CREW_WINDOW", true);
	XI_WindowDisable("HIRE_CREW_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowShow("GOODS_WINDOW", false);
	XI_WindowDisable("GOODS_WINDOW", true);

	SetSelectable("CAPTAN_BUTTON", false);
	SetSelectable("SWAP_BUTTON", false);
	SetSelectable("CREW_BUTTON", false);
	SetSelectable("TAKE_GOODS", false);
	SetSelectable("DROP_GOODS", false);
	sMessageMode = "";
	SetEventHandler("delayedDisableMainWindow", "delayedDisableMainWindow", 1);
	PostEvent("delayedDisableMainWindow", 10);
}

void delayedDisableMainWindow()
{
	DelEventHandler("delayedDisableMainWindow", "delayedDisableMainWindow");
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowShow("GOODS_WINDOW", false);
	XI_WindowDisable("GOODS_WINDOW", true);
	SetCurrentNode("HIRE_QTY_EDIT_BOX");
}

void ExitHireCrewWindow()
{
	XI_WindowShow("HIRE_CREW_WINDOW", false);
	XI_WindowDisable("HIRE_CREW_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowShow("GOODS_WINDOW", true);
	XI_WindowDisable("GOODS_WINDOW", false);

	SetSelectable("CAPTAN_BUTTON", true);
	SetSelectable("SWAP_BUTTON", false);
	SetSelectable("CREW_BUTTON", true);
	SetSelectable("TAKE_GOODS", true);
	SetSelectable("DROP_GOODS", true);
	sMessageMode = "";	

	OnShipScrollChange();
	SetCurrentNode(CurrentGoodsTableName());
}

void SetEnemyToPrisoner()
{
	ExitCaptureWindow();
	SetCharToPrisoner(xi_refCharacter); 
	LAi_SetCurHP(xi_refCharacter, 0.0); // умер
	// нет изменений репы - будет при судьбе пленного
	OnShipScrollChange();
	// второй проход - судьба команды
	ShowCrewCaptureAsk();
}

void SetEnemyToKilled()
{
	ExitCaptureWindow();
	LAi_SetCurHP(xi_refCharacter, 0.0); // умер
	ChangeCharacterComplexReputation(pchar,"nobility", -2); // плохое дело
	OfficersReaction("bad");
	OnShipScrollChange();
	// второй проход - судьба команды
	ShowCrewCaptureAsk();
}

void ShowCrewCaptureHire()
{
	if (GetCrewQuantity(xi_refCharacter) > 0 && iGetHired > 0) 		
	{
		InitVariable();
		SetVariable();		
		ShowHireCrewWindow();
	}
}

void ShowCrewCaptureAsk()
{
	if (GetCrewQuantity(xi_refCharacter) > 0)
	{
		// второй проход - Команда
		SetFormatedText("CAPTURE_TEXT_CREW", XI_ConvertString("Surrendered_crew_capture"));
		SetNewGroupPicture("CAPTURE_CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
		ShowCaptureCrewWindow();
		
		int iMode = CheckEnemyShipHPFree();
		switch (iMode)
		{
			case 0:
				SetSelectable("CAPTURE_CREW_FREE", false);
				SetCurrentNode("CAPTURE_CREW_PRISON");
			break;
			case 1:
				SetCurrentNode("CAPTURE_CREW_FREE");
			break;
			case 2:
				SetCurrentNode("CAPTURE_CREW_FREE");
			break;
		}
	}
}

void SetEnemyCrewToPrisoner()
{
	ExitCaptureCrewWindow();
	ChangeCharacterComplexReputation(pchar,"nobility", -1); // плохое дело
	ChangeCharacterComplexReputation(pchar,"authority", 0.5); // но команде это вряд ли понравится
	OfficersReaction("bad");
	SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + int(xi_refCharacter.Ship.Crew.Quantity))); // в перегруз, потом сам выкинет
	xi_refCharacter.Ship.Crew.Quantity = 0;
	OnShipScrollChange();
}

void SetEnemyCrewToKilled()
{
	ExitCaptureCrewWindow();
	ChangeCharacterComplexReputation(pchar,"nobility", -3); // плохое дело
	ChangeCharacterComplexReputation(pchar,"authority", -0.5); // но команде это вряд ли понравится
	OfficersReaction("bad");
	xi_refCharacter.Ship.Crew.Quantity = 0;
	OnShipScrollChange();
}

void SetEnemyCrewToFree()
{
	ExitCaptureCrewWindow();
	if(SetEnemyCrewGoods() == true)
	{
		ChangeCharacterComplexReputation(pchar,"nobility", 1); // хорошее дело
		ChangeCharacterComplexReputation(pchar,"authority", -0.5); // но команде это вряд ли понравится
		OfficersReaction("good");
	}
	RemoveEnemyShipHPFree();	
	xi_refCharacter.Ship.Crew.Quantity = 0;
	OnShipScrollChange();
}

// ugeen --> снабжение сдавшихся врагов, отпущенных  на шлюпках
bool SetEnemyCrewGoodOne(int iGood, int iGoodRateEat)
{
	int iQty, iGoodQty;
	int iCrewQty = GetCrewQuantity(xi_refCharacter);
	
	iGoodQty = int(iCrewQty/iGoodRateEat + 1);
	iQty = GetCargoGoods(xi_refCharacter, iGood);
	if(iQty >= iGoodQty) 
	{
		iQty = RemoveCharacterGoodsSelf(xi_refCharacter,iGood,iGoodQty); // сначала на корабле противника
		return iQty;
	}
	else
	{	
		iQty = GetCargoGoods(pchar, iGood);
		if(iQty >= iGoodQty)	
		{
			iQty = RemoveCharacterGoodsSelf(pchar,iGood,iGoodQty); // если нет у врага - спишем  с флагмана ГГ
			return iQty;
		}
	}	
	return false;
}

int CheckEnemyShipHPFree()
{
	int iHP = int(GetCrewQuantity(xi_refCharacter)/HP_BY_ENEMY_CREW + 1) * HP_PER_BOAT;
	if(float(xi_refCharacter.ship.hp) > iHP + 100)
	{   // списываем HP у абордируемого
		return 1;
	}
	else 
	{
		// cписываем HP у абордирующего
		if(float(pchar.ship.hp) > iHP + 200)
		{
			return 2;
		}		
	}
	return 0; // блокируем кнопку 
}

void RemoveEnemyShipHPFree()
{
	int iCrewQty = GetCrewQuantity(xi_refCharacter)/HP_BY_ENEMY_CREW;
	int iHP = int(iCrewQty + 1) * HP_PER_BOAT;
	if(float(xi_refCharacter.ship.hp) > iHP + 100)
	{
		xi_refCharacter.ship.hp = float(xi_refCharacter.ship.hp) - iHP;
	}
	else
	{
		pchar.ship.hp = float(pchar.ship.hp) - iHP;
	}
}

bool SetEnemyCrewGoods() // снабдим отпущенных всем необходимым 
{
	bool bOk;
	
	bOk = SetEnemyCrewGoodOne(GOOD_FOOD, FOOD_BY_ENEMY_CREW);
	bOk = bOk && SetEnemyCrewGoodOne(GOOD_RUM, RUM_BY_ENEMY_CREW);
	bOk = bOk && SetEnemyCrewGoodOne(GOOD_MEDICAMENT, MEDICAMENT_BY_ENEMY_CREW);
	SetEnemyCrewGoodOne(GOOD_WEAPON, WEAPON_BY_ENEMY_CREW);
		
	return bOk;
}
// ugeen <--

int GetEnemyHiredCrew()
{
	int iEnemyHiredCrew = 0;

	if(CheckAttribute(refCharacter,"GenQuest.ShipExplode")) return iEnemyHiredCrew;
	
	if (CheckAttribute(xi_refCharacter, "Ship.Mode") && xi_refCharacter.Ship.Mode == "War") 
	{
		iEnemyHiredCrew = int(GetCrewQuantity(xi_refCharacter) * rand( int(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)*0.2))/100.0 + GetCrewQuantity(xi_refCharacter) * rand( int(GetSummonSkillFromName(pchar, SKILL_FORTUNE)*0.2))/100.0 );
	}
	else // все остальные
	{
		iEnemyHiredCrew = int(GetCrewQuantity(xi_refCharacter) * rand(int(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)*0.7))/100.0);
	}
	int iDiffCrew = GetMaxCrewQuantity(refCharacter) - GetCrewQuantity(refCharacter);
	// учёт веса экипажа -- если нет места на корабле, то в команду не пойдут :(
	if(iDiffCrew > GetCargoFreeSpace(refCharacter))
	{
		iDiffCrew = GetCargoFreeSpace(refCharacter);
	}
		
	if(iEnemyHiredCrew > iDiffCrew) 
	{
		iEnemyHiredCrew = iDiffCrew;
	}		
	return iEnemyHiredCrew;
}

void SetShipInfoPic(ref chr, string sAdd)
{	
	int iShip = int(chr.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName + refBaseShip.ship.upgrades.hull;
		SetNewPicture("MAIN_SHIP_PICTURE" + sAdd, "interfaces\le\ships\" + sShip + ".tga");	
		SendMessage(&GameInterface,"lslffff",MSG_INTERFACE_MSG_TO_NODE,"MAIN_SHIP_PICTURE1", 1, 1.0, 0.0, 0.0, 1.0 );//отзеркаливание картинки по горизонтали
	}
}

void InitVariable()
{
	int nShipType = int(refCharacter.ship.type);
		
	ref refBaseShip = GetRealShip(nShipType);
	
	SetShipInfoPic(refCharacter, "1");
	SetShipInfoPic(xi_refCharacter, "2");
	
	if (CheckAttribute(refCharacter, "ship.name"))
	{
		SetFormatedText("CAPACITY", refCharacter.ship.name);
	}
	else
	{
		SetFormatedText("CAPACITY", "");
	}	
	if (CheckAttribute(xi_refCharacter, "ship.name"))
	{
		SetFormatedText("HIRE_CAPACITY", xi_refCharacter.ship.name);
	}
	else
	{
		SetFormatedText("HIRE_CAPACITY", "");
	}	

	SetNewPicture("MAIN_HERO_PICTURE", "interfaces\le\portraits\256\face_" + string(refCharacter.FaceId) + ".tga");
	SetFormatedText("MAIN_HERO_NAME", GetFullName(refCharacter));
	
	SetNewGroupPicture("HIRE_CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
	SetNewGroupPicture("HIRE_CREW_PICTURE2", "SHIP_STATE_ICONS", "Crew");
	
	// SetFormatedText("HIRE_CREW_CAPACITY", "Команда:\nмин. "+GetMinCrewQuantity(refCharacter) + ", опт. " + GetOptCrewQuantity(refCharacter) + ", макс. " + GetMaxCrewQuantity(refCharacter));
	SetFormatedText("HIRE_CREW_CAPACITY", XI_ConvertString("CrewTransferMin") + GetMinCrewQuantity(refCharacter) + XI_ConvertString("CrewTransferMax") + GetMaxCrewQuantity(refCharacter));
	SetFormatedText("HIRE_QTY_TypeOperation", XI_ConvertString("CrewTransfer"));	// Желающих перейти к нам в команду
}

void SetVariable()
{
	int iColor;
	string sText;
	
	SetFormatedText("HIRE_CREW_QTY", ""+GetCrewQuantity(pchar));
	if (GetCrewQuantity(pchar) < GetMinCrewQuantity(pchar)) iColor = argb(255,255,64,64);
	else iColor = argb(255,255,255,255);

	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"HIRE_CREW_QTY", 8,-1,iColor);

	SetFoodShipInfo(pchar, "HIRE_FOOD_SHIP");
	SetRumShipInfo(pchar, "HIRE_RUM_SHIP");	

	SetFormatedText("HIRE_CREW_QTY2", ""+GetCrewQuantity(xi_refCharacter));
	SetFormatedText("HIRED_CREW", ""+int(xi_refCharacter.Ship.Crew.Hire));
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"HIRED_CREW", 5 );

	XI_SetCrewQualityStates(pchar, "", "HIRE_");
	XI_SetCrewQualityStates(xi_refCharacter, "2", "HIRE_");
}

// бакап значений, до применения
void SetBackupQty()
{
	aref    arTo, arFrom;
	NullCharacter.CrewBak.Hero = "";
	NullCharacter.CrewBak.ECrew = "";
	
	makearef(arTo, NullCharacter.CrewBak.Hero);
	makearef(arFrom, refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
	
	makearef(arTo, NullCharacter.CrewBak.ECrew);
	makearef(arFrom, xi_refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void GetBackupQty()
{
	aref    arTo, arFrom;
	
	makearef(arFrom, NullCharacter.CrewBak.Hero);
	makearef(arTo, refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
	
	makearef(arFrom, NullCharacter.CrewBak.ECrew);
	makearef(arTo, xi_refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void SetBackupExp()
{
	aref    arTo, arFrom;
	NullCharacter.CrewBak.Exp = "";
	NullCharacter.CrewBak.Morale = "";
	
	makearef(arTo, NullCharacter.CrewBak.Exp);
	makearef(arFrom, refCharacter.Ship.Crew.Exp);
	CopyAttributes(arTo, arFrom);
	
	makearef(arTo, NullCharacter.CrewBak.Morale);
	makearef(arFrom, refCharacter.Ship.Crew.Morale);
	CopyAttributes(arTo, arFrom);
}

void GetBackupExp()
{
	aref    arTo, arFrom;
	
	makearef(arFrom, NullCharacter.CrewBak.Exp);
	makearef(arTo, refCharacter.Ship.Crew.Exp);
	CopyAttributes(arTo, arFrom);
	
	makearef(arFrom, NullCharacter.CrewBak.Morale);
	makearef(arTo, xi_refCharacter.Ship.Crew.Morale);
	CopyAttributes(arTo, arFrom);
}

void HireTransactionCancel()
{
	GetBackupQty();
	DeleteAttribute(xi_refCharacter, "Ship.Crew.Hire");
	ExitHireCrewWindow();
}

void HireTransactionOK()
{
	DeleteAttribute(xi_refCharacter, "Ship.Crew.Hire");
	ExitHireCrewWindow();
}

void HIRE_ChangeQTY_EDIT()
{
	GetBackupExp();
	float fQty = float(GetCrewQuantity(pchar) + iCrewQty);

	pchar.Ship.Crew.Exp = (GetCrewExp(pchar)*GetCrewQuantity(pchar) + GetCrewExp(xi_refCharacter)*iCrewQty) / fQty;
	refCharacter.Ship.Crew.Morale = (GetCharacterCrewMorale(pchar)*GetCrewQuantity(pchar) + GetCharacterCrewMorale(xi_refCharacter)*iCrewQty) / fQty;

	SetCrewQuantity(pchar, GetCrewQuantity(pchar) + iCrewQty - iBackCrew);
	SetCrewQuantity(xi_refCharacter, GetCrewQuantity(xi_refCharacter) - iCrewQty + iBackCrew);

	iBackCrew = iCrewQty;
	SetVariable();	
}

void HIRE_REMOVE_ALL_BUTTON()
{
	if(iCrewQty > 0)
	{
		xi_refCharacter.Ship.Crew.Hire = int(xi_refCharacter.Ship.Crew.Hire) + iCrewQty;
		iCrewQty = 0;
		HIRE_ChangeQTY_EDIT();
	}	
}

void HIRE_ADD_ALL_BUTTON()
{
	if(int(xi_refCharacter.Ship.Crew.Hire) > 0)
	{
		iCrewQty = iCrewQty + int(xi_refCharacter.Ship.Crew.Hire);
		xi_refCharacter.Ship.Crew.Hire = 0;
		HIRE_ChangeQTY_EDIT();
	}
}

void HIRE_REMOVE_BUTTON(int value)  
{
	if(iCrewQty > 0)
	{
		value = func_min(iCrewQty, value);
		iCrewQty = iCrewQty - value;
		xi_refCharacter.Ship.Crew.Hire = int(xi_refCharacter.Ship.Crew.Hire) + value;
		HIRE_ChangeQTY_EDIT();
	}	
}

void HIRE_ADD_BUTTON(int value)  
{
	if(int(xi_refCharacter.Ship.Crew.Hire) > 0)
	{
		value = func_min(int(xi_refCharacter.Ship.Crew.Hire), value);
		iCrewQty = iCrewQty + value;
		xi_refCharacter.Ship.Crew.Hire = int(xi_refCharacter.Ship.Crew.Hire) - value;
		HIRE_ChangeQTY_EDIT();
	}
}

void XIShip_GetCompareArrow(string _tabName, string rowId, ref valueA, ref valueB, string mode)
{
	string icon = "";
	// сравнение калибров по ступени калибра
	if (mode == "cannonsCaliber")
	{
		int calibers[12] = {3, 6, 8, 12, 16, 18, 20, 24, 32, 36, 42, 48};
		valueA = FindIndexOf(&calibers, valueA);
		valueB = FindIndexOf(&calibers, valueB);

		if (valueB == valueA) icon = "";
		else if (valueB >= valueA + 2) icon = "arrowup2";
		else if (valueB > valueA) icon = "arrowup1";
		else if (valueB + 2 <= valueA ) icon = "arrowdown2";
		else if (valueB < valueA) icon = "arrowdown1";
	} // остальное сравниваем приблизительно
	else if (valueB == valueA) icon = "";
	else if (valueB >= valueA * 1.35) icon = "arrowup2";
	else if (valueB > valueA) icon = "arrowup1";
	else if (valueB * 1.35 <= valueA ) icon = "arrowdown2";
	else if (valueB <= valueA) icon = "arrowdown1";

	if (icon != "" && strright(icon, 1) == "1") GameInterface.(_tabName).(rowId).td2.icon.offset = "198,-10";
	else GameInterface.(_tabName).(rowId).td2.icon.offset = "198,-7";
	GameInterface.(_tabName).(rowId).td2.icon.image = icon;
}


//проверка доступных офицеров
bool bPassengersAccess() {
    int qty = GetPassengersQuantity(pchar);
    for(int i = 0; i < qty; i++) {
        int idx = GetPassenger(pchar, i);
        if (idx != -1) {
            bool ok = CheckAttribute(&characters[idx], "prisoned") && int(characters[idx].prisoned) == true;
            bool ob = CheckAttribute(&characters[idx], "CompanionDisable") && int(characters[idx].CompanionDisable) == true;
            if (!ok && !ob && GetRemovable(&characters[idx])) return true;
        }
    }
    
    return false;
}

void TakeCannonsOff()
{
	SetCannonsToBort(xi_refCharacter, "cannonf", 0);
	SetCannonsToBort(xi_refCharacter, "cannonb", 0);
	SetCannonsToBort(xi_refCharacter, "cannonr", 0);
	SetCannonsToBort(xi_refCharacter, "cannonl", 0);
	FillStockTable();
	ShowShipInfo(xi_refCharacter, "2");
}

// Если на корабле осталась команда, не топим её
void SaveCrewFromSunkenShip(ref captain)
{
	AddCharacterCrew(pchar, GetCrewQuantity(captain));
}

void SetWindRosePoints()
{
	int iShipType1 = int(RealShips[int(refCharacter.ship.type)].basetype);
	int iShipType2 = int(RealShips[int(xi_refCharacter.ship.type)].basetype);
	float fAngle;
	for(int i = 0; i <= SHIP_SPEEDPOINT_QUANTITY / 2; i++)
	{
		fAngle = i * PIm2 / SHIP_SPEEDPOINT_QUANTITY;
		fSpeeds[i] = Ship_SimulateSpeed_Init(iShipType1, fAngle) * GetCurSpeedFromPoint(refCharacter, fAngle);
		fCompareSpeeds[i] = Ship_SimulateSpeed_Init(iShipType2, fAngle) * GetCurSpeedFromPoint(xi_refCharacter, fAngle);
		if(i > 0 && i <  SHIP_SPEEDPOINT_QUANTITY / 2)
		{
			fSpeeds[SHIP_SPEEDPOINT_QUANTITY - i] = fSpeeds[i];
			fCompareSpeeds[SHIP_SPEEDPOINT_QUANTITY - i] = fCompareSpeeds[i];
		}
	}
}

ref GetWindRosePoints()
{
	string sNode = GetEventData();
	return &fSpeeds;
}

ref GetWindRoseComparePoints()
{
	string sNode = GetEventData();
	return &fCompareSpeeds;
}

string CurrentGoodsTableName()
{
	return goodsMode == 0 ? "TABLE_LIST" : "TABLE_LIST_CANNONS";
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode(CurrentGoodsTableName());

	if(sNodName == "TABBTN_1")
	{
		SetControlsTabMode(0);
		XI_TransferSelectGoodsTable("TABLE_LIST");
		return;
	}
	if(sNodName == "TABBTN_2")
	{
		SetControlsTabMode(1);
		XI_TransferSelectGoodsTable("TABLE_LIST_CANNONS");
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

void ProcessInterfaceControls()
{
	string sCurNode = GetCurrentNode();
	string controlName = GetEventData();
	bool IsMainWindowEnabled = XI_IsWindowEnable("MAIN_WINDOW");
	if (controlName == "InterfaceTabSwitch")
	{
		if (!XI_IsWindowEnable("GOODS_WINDOW")) return;
		goodsMode = !goodsMode;
		SetControlsTabMode(goodsMode);
		XI_TransferSelectGoodsTable(goodsMode == 0 ? "TABLE_LIST" : "TABLE_LIST_CANNONS");
	}
}

void OnHeaderClick()
{
	string sControl = GetEventData();
	int iColumn = GetEventData();
	if (sControl == "TABLE_LIST") XI_SortTransferGoods(iColumn, false, sControl);
	if (sControl == "TABLE_LIST_CANNONS") XI_SortTransferGoods(iColumn, false, sControl);
}

void XI_SortTransferGoods(int column, bool preserveState, string tableName)
{
  string datatype = "integer";
	switch (column)
	{
		case 3: datatype = "index"; break;
	}
	
  QoLSortTable(tableName, column, datatype, preserveState, 0);
}

void XI_TransferSelectGoodsTable(string tableName)
{
	EI_DeleteTriggerFrame();
	CloseTooltipNew();
	CurTable = tableName;
	NullSelectTable(CurTable);
	SetCurrentNode(CurTable);
	GameInterface.(CurTable).select = 1;
	GameInterface.(CurTable).top = 0;
	FillStockTable();
	SetNodeUsing("B_RIGHT", false);
	SetNodeUsing("B_LEFT", false);
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER, tableName == "TABLE_LIST" ? "SCROLL_LIST" : "SCROLL_LIST_CANNONS",0);
}