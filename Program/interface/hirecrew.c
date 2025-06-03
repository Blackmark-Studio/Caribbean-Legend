/// boal 30.07.06 найм матросов
/// Sith переделка
int	nCurScrollNum = 0;
ref refCharacter;
ref refTown;
ref refShipChar;
int iShipCapacity;
float fShipWeight;
int  BuyOrSell = 0; // 1-buy -1 sell
int  iPriceSailor;
int	 QtyMax = 0; 	 
int	 CrewQty = 0;

string CurTable, CurRow, CurCol;
int iSelected, iSelectedCol;

void InitInterface(string iniName)
{
 	StartAboveForm(true);
	LAi_SetActorType(pchar);
	refCharacter = pchar;
	GameInterface.title = "titleHireCrew";
	// город, где ГГ
	refTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
    FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"ShipName","",FONT_NORMAL,COLOR_MONEY, 960,175,SCRIPT_ALIGN_CENTER,1.5);

	SetDescription();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);

	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("OnTableRClick", "OnTableRClick", 0);
	
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("TransactionCancel", "TransactionCancel", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);
	
	SetNewGroupPicture("QTY_CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
	SetBackupQty();
	SetCurrentNode("SHIPS_SCROLL");
	GameInterface.qty_edit.str = 0;
	QtyMax = GetCargoFreeSpace(refCharacter);

	if(CheckAttribute(refTown, "AdditionalCrew"))
	{
		if(!IsEquipCharacterByArtefact(pchar, "totem_07"))
		{
			CrewQty = GetCrewQuantity(refTown) - sti(refTown.AdditionalCrew);
			if(CrewQty < 0) CrewQty = 0;
			SetCrewQuantity(refTown, CrewQty);
		}
	}
	else
	{
		if(IsEquipCharacterByArtefact(pchar, "totem_07"))
		{
			CrewQty = GetCrewQuantity(refTown);						
			refTown.AdditionalCrew = makeint(CrewQty * 0.35);			
			CrewQty += sti(refTown.AdditionalCrew);
			SetCrewQuantity(refTown, CrewQty);
		}
	}
	// belamour legendary edition Орден Святого Людовика -->
	if(CheckAttribute(refTown, "AddCrewTalisman9"))
	{
		if(!IsEquipTalisman9())
		{
			CrewQty = GetCrewQuantity(refTown) - sti(refTown.AddCrewTalisman9);
			if(CrewQty < 0) CrewQty = 0;
			SetCrewQuantity(refTown, CrewQty);
		}
	}
	else
	{
		if(IsEquipTalisman9() && refTown.nation == FRANCE)
		{
			CrewQty = GetCrewQuantity(refTown);						
			refTown.AddCrewTalisman9 = makeint(CrewQty * 0.4);			
			CrewQty += sti(refTown.AddCrewTalisman9);
			SetCrewQuantity(refTown, CrewQty);
		}
	}
	// <-- legendary edition
	SetNodeUsing("QTY_HIREFIRE_BUTTON", false);
	
	SetHireEffects();
}

void SetHireEffects()
{
	string sRow, sCol, sBonus, sArrow;
	int iRow, iCol, iBonus, nBonus, nPenalty;
	bool bBonus;

	nBonus = 0;
	nPenalty = 0;
	
	// харизма
	bBonus = true;
	iBonus = GetSummonSkillFromNameSimple(pchar, SKILL_LEADERSHIP);
	sBonus = "charisma";
	if(iBonus <= 16)
	{
		nPenalty++;
		sRow = "tr2";
		sCol = "td" + nPenalty;
		sArrow = "arrowdown1";
	}
	else
	{
		nBonus++;
		sRow = "tr1";
		sCol = "td" + nBonus;
		if(iBonus <= 44)		sArrow = "arrowup1";
		else if(iBonus <= 74)	sArrow = "arrowup2";
		else					sArrow = "arrowup3";
	}
	GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon1.image = sArrow;
	GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon2.image = sBonus;
	GameInterface.TABLE_EFFECTS.(sRow).(sCol).effectID = "charisma";
	
	// отношение нации
	iBonus = ChangeCharacterNationReputation(pchar, sti(refTown.nation), 0);
	sBonus = Nations[sti(refTown.nation)].name;
	if(sBonus == "pirate")
	{
		nBonus++;
		sRow = "tr1";
		sCol = "td" + nBonus;
		sArrow = "arrowup2";
	}
	else
	{
		if(iBonus < 0)
		{
			nPenalty++;
			sRow = "tr2";
			sCol = "td" + nPenalty;
			sArrow = "arrowdown1";
		}
		else if(iBonus > 20)
		{
			nBonus++;
			sRow = "tr1";
			sCol = "td" + nBonus;
			if(iBonus <= 50)		sArrow = "arrowup1";
			else if(iBonus <= 80)	sArrow = "arrowup2";
			else					sArrow = "arrowup3";
		}
		else
			bBonus = false;
	}
	if(bBonus)
	{
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon1.image = sArrow;
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon2.image = sBonus;
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).effectID = "nation";
	}
	
	// честь
	bBonus = true;
	iBonus = sti(pchar.reputation.nobility);
	string sRep = GetReputationComplexName(iBonus, "nobility");
	if(sRep != "REPUTATION_NOBILITY_5")
	{
		nBonus++;
		sRow = "tr1";
		sCol = "td" + nBonus;
		if(iBonus < COMPLEX_REPUTATION_NEUTRAL)
		{
			sBonus = "repdown";
			if(sRep == "REPUTATION_NOBILITY_1")
				sArrow = "arrowup3";
			else if(sRep == "REPUTATION_NOBILITY_2")
				sArrow = "arrowup2";
			else
				sArrow = "arrowup1";
		}
		else
		{
			sBonus = "repup";
			if(sRep == "REPUTATION_NOBILITY_9")
				sArrow = "arrowup3";
			else if(sRep == "REPUTATION_NOBILITY_8")
				sArrow = "arrowup2";
			else
				sArrow = "arrowup1";
		}
	}
	else
		bBonus = false;
	if(bBonus)
	{
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon1.image = sArrow;
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon2.image = sBonus;
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).effectID = "reputation";
	}
	
	// менестрель
	if(IsEquipCharacterByArtefact(pchar, "totem_07"))
	{
		nBonus++;
		sRow = "tr1";
		sCol = "td" + nBonus;
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon1.image = "arrowup1";
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon2.image = "minstrel";
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).effectID = "minstrel";
	}
	
	// крест
	if(IsEquipTalisman9() && refTown.nation == FRANCE)
	{
		nBonus++;
		sRow = "tr1";
		sCol = "td" + nBonus;
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon1.image = "arrowup2";
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon2.image = "louis";
		GameInterface.TABLE_EFFECTS.(sRow).(sCol).effectID = "louis";
	}

	int nCol;
	for(iRow = 1; iRow <= 2; iRow++)
	{
		sRow = "tr" + iRow;
		if(iRow == 1)
			nCol = nBonus;
		else
			nCol = nPenalty;
		for(iCol = 1; iCol <= nCol; iCol++)
		{
			sCol = "td" + iCol;
			
			GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon1.group = "HIRE_EFFECTS";
			GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon1.width = 15;
			GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon1.height = 50;
			GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon1.offset = "0, 5";
			
			GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon2.group = "HIRE_EFFECTS";
			GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon2.width = 50;
			GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon2.height = 50;
			GameInterface.TABLE_EFFECTS.(sRow).(sCol).icon2.offset = "14, 5";
		}
	}
	GameInterface.TABLE_EFFECTS.select = 0;
	Table_UpdateWindow("TABLE_EFFECTS");
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
	LAi_SetPlayerType(pchar);
	RecalculateCargoLoad(refCharacter);
    GetBackupQty(); // если неожиданно вышли
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("OnTableRClick", "OnTableRClick");
	
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("TransactionCancel", "TransactionCancel");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
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

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "QTY_HIREFIRE_BUTTON":
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
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void FillShipsScroll()
{
	nCurScrollNum = -1;
	FillScrollImageWithCompanionShips("SHIPS_SCROLL", 5);

	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}
}

void SetVariable()
{
	string sText, sTextSecond;
	int iColor;
	int nShipType = sti(refCharacter.ship.type);
	
	if (nShipType == SHIP_NOTUSED)
	{
        GameInterface.strings.shipname = "";
        GameInterface.strings.shipbasename = "";
		return;
	}
	
	QtyMax = GetCargoFreeSpace(refCharacter);
	
	ref refBaseShip = GetRealShip(nShipType);
	SetShipWeight();
	
	iShipCapacity = sti(refBaseShip.Capacity);
	sText  = iShipCapacity;
	sText  = makeint(fShipWeight) + " / " + sText;	
	SetFormatedText("CAPACITY", sText);	
	
	sText = MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER);
	SetFormatedText("QTY_OUR_GOLD", sText);

	if (CheckAttribute(refCharacter, "ship.name"))
	{
		GameInterface.strings.shipname = refCharacter.ship.name;
		GameInterface.strings.shipbasename = XI_ConvertString(refBaseShip.BaseName);
	}
	else
	{
	    GameInterface.strings.shipname = "";
	    GameInterface.strings.shipbasename = "";
	}
	SetCrewExpTable(refCharacter, "TABLE_CREW", "BAR_Sailors", "BAR_Cannoners", "BAR_Soldiers");
	
	SetFormatedText("QTY_CREW_QTY", ""+GetCrewQuantity(refCharacter));
	if (GetCrewQuantity(refCharacter) > GetOptCrewQuantity(refCharacter) || GetCrewQuantity(refCharacter) < GetMinCrewQuantity(refCharacter))
	{
		iColor = argb(255,255,64,64);
	}
	else
	{
		iColor = argb(255,255,255,255);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"QTY_CREW_QTY", 8,-1,iColor);
	SetFormatedText("QTY_CREW_CAPACITY", "" + GetOptCrewQuantity(refCharacter));
	SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(stf(refCharacter.ship.crew.morale)));
	SetFormatedText("CREW_MORALE_TEXT", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(refCharacter.Ship.crew.morale))));
		
	RecalculateCargoLoad(refCharacter);

	// на одном корабле
	SetFormatedText("MONEY_SHIP", FindRussianMoneyString(GetSalaryForShip(refCharacter)) + " " + XI_ConvertString("per month"));

	SetFoodShipInfoShort(refCharacter, "FOOD_SHIP");
	SetRumShipInfoShort(refCharacter,"RUM_SHIP");

	SetFormatedText("CREW_CAPACITY", GetCrewQuantity(refCharacter) + "/" + GetOptCrewQuantity(refCharacter));
	////  заполнялка города
	SetCrewExpTable(refTown, "TABLE_CREW2", "BAR_Sailors2", "BAR_Cannoners2", "BAR_Soldiers2");
	//BAR_CrewMoral
	GameInterface.StatusLine.BAR_CrewMoral.Max   = 100;
	GameInterface.StatusLine.BAR_CrewMoral.Min   = 0;
	GameInterface.StatusLine.BAR_CrewMoral.Value = sti(refCharacter.Ship.crew.morale);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_CrewMoral", 0);
	//BAR_CrewMoral2
	GameInterface.StatusLine.BAR_CrewMoral2.Max   = 100;
	GameInterface.StatusLine.BAR_CrewMoral2.Min   = 0;
	GameInterface.StatusLine.BAR_CrewMoral2.Value = sti(refTown.Ship.crew.morale);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_CrewMoral2", 0);

	SetFormatedText("QTY_CREW_QTY2", ""+GetCrewQuantity(refTown));
	if(PosEffects()) iColor = argb(255,128,255,128);
	else iColor = argb(255,255,128,128);
	if(GetCrewQuantity(refTown)==0) iColor = argb(255,255,255,255);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"QTY_CREW_QTY2", 8,-1,iColor);	
	SetNewGroupPicture("CREW_MORALE_PIC2", "MORALE_SMALL", GetMoraleGroupPicture(stf(refTown.ship.crew.morale)));
	SetFormatedText("CREW_MORALE_TEXT2", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(refTown.Ship.crew.morale))));
	
	iPriceSailor = GetCrewPriceForTavern(refTown.id);
	
	if(IsEquipCharacterByArtefact(pchar, "totem_07")) iPriceSailor = makeint(iPriceSailor/2);
	
	SetFormatedText("QTY_TAVERN_PRICE", XI_ConvertString("HirePrice1") + " " + FindRussianMoneyString(iPriceSailor));
}

void ProcessFrame()
{
	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		if(sti(GameInterface.SHIPS_SCROLL.current)!=nCurScrollNum)
		{
			GetBackupQty(); // если неожиданно вышли
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);
			SetDescription();
			GameInterface.qty_edit.str = 0;
		    SetFormatedText("QTY_Result", "");
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_HIREFIRE_BUTTON", 0, "");
			SetNodeUsing("QTY_HIREFIRE_BUTTON", false);
		}
	}
}

void SetDescription()
{
 	string sChrId;
 	 
	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		string attributeName = attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "SHIPS_SCROLL." + attributeName))
		{
			int iCharacter = GameInterface.SHIPS_SCROLL.(attributeName).companionIndex;
			sChrId = characters[iCharacter].id;
			refCharacter = characterFromID(sChrId);
			QtyMax = GetCargoFreeSpace(refCharacter);
			SetBackupQty();
		}
	}
	SetVariable();
}

void SetShipWeight()
{
    if (CheckAttribute(refCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(refCharacter.Ship.Cargo.RecalculateCargoLoad))
	{   // остатки с моря
		RecalculateCargoLoad(refCharacter);
		refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
	}
	fShipWeight  = makeint(GetCargoLoad(refCharacter)+ 0.4);
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;
	string sText;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	int iShip;
	ref refBaseShip;
	
	bool  bShowHint = true;
	switch (sCurrentNode)
	{
		case "SHIPS_SCROLL":
			// if (shipIndex != -1)
			if (iShip != SHIP_NOTUSED)
			{
			    sPicture = "interfaces\le\portraits\512\face_" + refCharacter.FaceId + ".tga"
				iShip = sti(refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText = XI_Convertstring("Captain") + " - " + GetFullName(refCharacter);
				sText1 = sText + "\n\n" + GetShipDescr(refBaseShip);
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat", "ShipsDescribe.txt");
			}
		break;
		case "TABLE_CREW":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break; 
		case "TABLE_CREW2":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break; 
		case "MONEY_SHIP":
			sHeader = XI_Convertstring("CostPerMonth");
			sText1 = GetRPGText("Partition_hint");
		break;
		case "FOOD_SHIP":
			sHeader = XI_Convertstring("FoodShipInfoShort");
			sText1 = GetConvertStr("Food_descr", "GoodsDescribe.txt");
		break;
		case "RUM_SHIP":
			sHeader = XI_Convertstring("RumShipInfoShort");
			sText1 = GetConvertStr("Rum_descr", "GoodsDescribe.txt");
		break;
		case "TABLE_EFFECTS":
			sHeader = XI_Convertstring("HireEffects");
			sText1 = XI_Convertstring("HireEffects_descr");
			if(CheckAttribute(GameInterface, CurTable + "." + CurRow + "." + CurCol + ".effectID"))
			{
				sText = "E" + GameInterface.(CurTable).(CurRow).(CurCol).effectID;
				sHeader = XI_Convertstring(sText);
				sText1 = XI_Convertstring(sText + "_descr");
			}
		break; 
	}
	if (bShowHint)
	{
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 160, 160);
	}
}

void HideInfoWindow()
{
	CloseTooltip();
}
// бакап значений, до применения
void SetBackupQty()
{
	aref    arTo, arFrom;
	NullCharacter.TavernBak.Hero = "";
	NullCharacter.TavernBak.Tavern = "";
	
	makearef(arTo,   NullCharacter.TavernBak.Hero);
	makearef(arFrom, refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
	
	makearef(arTo,   NullCharacter.TavernBak.Tavern);
	makearef(arFrom, refTown.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void GetBackupQty()
{
	aref    arTo, arFrom;
	
	makearef(arFrom,   NullCharacter.TavernBak.Hero);
	makearef(arTo, refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);
	
	makearef(arFrom,   NullCharacter.TavernBak.Tavern);
	makearef(arTo, refTown.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void TransactionCancel()
{
	if (sti(GameInterface.qty_edit.str) == 0)
	{   // выход
		ProcessCancelExit();	
	}
	else
	{
		CancelQty();	
    }
}

void CancelQty()
{
	GetBackupQty();	
	SetVariable();
	GameInterface.qty_edit.str = 0;
    SetFormatedText("QTY_Result", "");
	SetNodeUsing("QTY_HIREFIRE_BUTTON", false);
}
void TransactionOK()
{
	int nTradeQuantity, moneyback;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if (BuyOrSell == 0)
	{
	    CancelQty();
		return;
	}

    if (!GetRemovable(refCharacter)) return;
    
 	if (BuyOrSell == 1) // BUY  нанять
	{
		moneyback = makeint(iPriceSailor*stf(GameInterface.qty_edit.str));
		pchar.money = sti(pchar.money)  - moneyback;
		RecalculateCargoLoad(refCharacter);
		QtyMax = GetCargoFreeSpace(refCharacter);
		Statistic_AddValue(Pchar, "Money", moneyback);
	}
 	else
	{ // SELL
		RecalculateCargoLoad(refCharacter);
	}
	SetBackupQty(); // применим и согласимся
	CancelQty();
	SetVariable();
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_HIREFIRE_BUTTON");
}

void ChangeQTY_EDIT()
{
	float fQty;
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str); // приведение к целому
	GetBackupQty();	 // обновим как было до правок
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_Result", "");
		SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_HIREFIRE_BUTTON", 0, "");
		SetNodeUsing("QTY_HIREFIRE_BUTTON", false);
	    BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)
		{  // уволить
			if (BuyOrSell != -1)
			{
		    	GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
		    }
            BuyOrSell = -1;
		    // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > GetCrewQuantity(refCharacter))
		    {
		        GameInterface.qty_edit.str = GetCrewQuantity(refCharacter);
		    }
			if(refTown.id == "IslaMona")
			{
				if(sti(GameInterface.qty_edit.str) + GetCrewQuantity(refTown) > 300)
				{
					GameInterface.qty_edit.str = 300 - GetCrewQuantity(refTown);
				}
			}
		    // проверка на колво доступное <--
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_HIREFIRE_BUTTON", 0, "Fire");
			SetNodeUsing("QTY_HIREFIRE_BUTTON", true);
		    SetFormatedText("QTY_Result", "");
		}
		else
		{  // нанять
			BuyOrSell = 1;
         	// проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > GetCrewQuantity(refTown))
		    {
		        GameInterface.qty_edit.str = GetCrewQuantity(refTown);
		    }
		    if (sti(GameInterface.qty_edit.str) > (GetMaxCrewQuantity(refCharacter) -  GetCrewQuantity(refCharacter)))
		    {
		        GameInterface.qty_edit.str = (GetMaxCrewQuantity(refCharacter) -  GetCrewQuantity(refCharacter));
		    }
		    
		    if (makeint(iPriceSailor*stf(GameInterface.qty_edit.str)) > sti(pchar.money))
		    {
		        GameInterface.qty_edit.str = makeint(sti(pchar.money) / iPriceSailor);
		    }
			
			QtyMax = GetCargoFreeSpace(refCharacter);
			if(QtyMax > 0)
			{
				if(sti(GameInterface.qty_edit.str) >= QtyMax)
				{
					GameInterface.qty_edit.str = QtyMax;
				}
			}
			else GameInterface.qty_edit.str = 0;
						
		    // проверка на колво доступное <--

			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_HIREFIRE_BUTTON", 0, "Hire");
			SetNodeUsing("QTY_HIREFIRE_BUTTON", true);
			SetFormatedText("QTY_Result", "- " + FindRussianMoneyString(makeint(iPriceSailor*stf(GameInterface.qty_edit.str))));
		}
		// если получили ноль
		if (sti(GameInterface.qty_edit.str) == 0)
		{
		    SetFormatedText("QTY_Result", "");
		    BuyOrSell = 0;
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_HIREFIRE_BUTTON", 0, "");
			SetNodeUsing("QTY_HIREFIRE_BUTTON", false);
		}
	}
	if (sti(GameInterface.qty_edit.str) > 0)
	{ // применение кол-ва
		
		if (BuyOrSell == 1)
		{   // найм меняет опыт и мораль корабля
			fQty = stf(GetCrewQuantity(refCharacter) + sti(GameInterface.qty_edit.str));
			refCharacter.Ship.Crew.Exp.Sailors   = (stf(refCharacter.Ship.Crew.Exp.Sailors)*GetCrewQuantity(refCharacter) + 
			                                        stf(refTown.Ship.Crew.Exp.Sailors)*sti(GameInterface.qty_edit.str)) / fQty; 
			refCharacter.Ship.Crew.Exp.Cannoners   = (stf(refCharacter.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(refCharacter) + 
			                                        stf(refTown.Ship.Crew.Exp.Cannoners)*sti(GameInterface.qty_edit.str)) / fQty;
			refCharacter.Ship.Crew.Exp.Soldiers   = (stf(refCharacter.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(refCharacter) + 
			                                        stf(refTown.Ship.Crew.Exp.Soldiers)*sti(GameInterface.qty_edit.str)) / fQty;
			refCharacter.Ship.Crew.Morale   = (stf(refCharacter.Ship.Crew.Morale)*GetCrewQuantity(refCharacter) + 
			                                        stf(refTown.Ship.Crew.Morale)*sti(GameInterface.qty_edit.str)) / fQty;
		}
		else
		{ // увольнение меняет таверну
			fQty = stf(GetCrewQuantity(refTown) + sti(GameInterface.qty_edit.str));
			refTown.Ship.Crew.Exp.Sailors   = (stf(refTown.Ship.Crew.Exp.Sailors)*GetCrewQuantity(refTown) + 
			                                        stf(refCharacter.Ship.Crew.Exp.Sailors)*sti(GameInterface.qty_edit.str)) / fQty;
			refTown.Ship.Crew.Exp.Cannoners   = (stf(refTown.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(refTown) + 
			                                        stf(refCharacter.Ship.Crew.Exp.Cannoners)*sti(GameInterface.qty_edit.str)) / fQty;
			refTown.Ship.Crew.Exp.Soldiers   = (stf(refTown.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(refTown) + 
			                                        stf(refCharacter.Ship.Crew.Exp.Soldiers)*sti(GameInterface.qty_edit.str)) / fQty;
			refTown.Ship.Crew.Morale   = (stf(refTown.Ship.Crew.Morale)*GetCrewQuantity(refTown) + 
			                                        stf(refCharacter.Ship.Crew.Morale)*sti(GameInterface.qty_edit.str)) / fQty;
		}
		SetCrewQuantity(refCharacter, GetCrewQuantity(refCharacter) + BuyOrSell*sti(GameInterface.qty_edit.str));
		refTown.Ship.Crew.Quantity = sti(refTown.Ship.Crew.Quantity) - BuyOrSell*sti(GameInterface.qty_edit.str));	
	}
    SetVariable(); // обновим экран
}

void REMOVE_ALL_BUTTON()  // продать все (уволить)
{
	GetBackupQty();	// вернём все как было
	if (!GetRemovable(refCharacter)) return;
	GameInterface.qty_edit.str = -GetCrewQuantity(refCharacter);
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
	GetBackupQty();	// вернём все как было
	if (!GetRemovable(refCharacter)) return;
	GameInterface.qty_edit.str = GetCrewQuantity(refTown);
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
	if (!GetRemovable(refCharacter)) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = -1;
    }
    else
    {
		if (BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
	if (!GetRemovable(refCharacter)) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = 1;
    }
    else
    {
  		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - 1);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

bool PosEffects()
{
	float fResult = 0.0;
	float fKrank = 1.0 + (2.5 - 1.0) * (pow(stf(pchar.rank), 0.25) - 1.0) / (pow(40.0, 0.25) - 1.0);
	float fKrelation = GetNationRelationCoef(ChangeCharacterNationReputation(pchar, sti(refTown.nation), 0));
	float fKcharisma = 1.0 + (2.5 - 1.0) * (pow(stf(GetSummonSkillFromNameSimple(pchar, SKILL_LEADERSHIP)), 1.35) - 1.0) / (pow(100.0, 1.35) - 1.0);
	float fKrep = GetReputationCoef(abs(COMPLEX_REPUTATION_NEUTRAL - sti(pchar.reputation.nobility)));
	fResult = fKrank + fKrelation + fKcharisma + fKrep;
	// log_testinfo("fResult - " + fResult);
	if(fResult>0) return true;
	return false;
}