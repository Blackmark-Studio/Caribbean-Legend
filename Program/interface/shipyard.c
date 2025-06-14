/// BOAL Верфь
/// Sith, mitrokosta Переделка меню верфи для LE

int nCurScrollNum;
ref refCharacter;
ref refNPCShipyard;
int shipIndex;
string sChrId;
bool FirstTime = true;
int CompanionIdx[COMPANION_MAX];
int nCurScrollOfficerNum;

string CurTable, CurRow;
string NPCCity;
int iSelected; // курсор в таблице

string sMessageMode, sFrom_sea, sShipId;

float shipCostRate;
bool  bShipyardOnTop, bEmptySlot;

int RepairHull, RepairSail;
int timeHull, timeRig;

void InitInterface_R(string iniName, ref _shipyarder)
{
 	StartAboveForm(true);
	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetActorType(pchar);
	}
	GameInterface.title = "titleShipyard";
	bGameMenuStart = true; // меню запущено, скрываем landinterface
	refCharacter = pchar;

    refNPCShipyard  = _shipyarder;
	NPCCity = refNPCShipyard.City;
    SetShipyardStore(refNPCShipyard);

    shipCostRate = stf(refNPCShipyard.ShipCostRate);

    int iTest = FindColony(refNPCShipyard.City); // город магазина
    ref rColony;
    sFrom_sea = "";
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea; // ветка верфи, в сухопутных верфи нет, значит везде правильная
	}

	FillShipsScroll();
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	CreateString(true,"ShipName","",FONT_NORMAL,COLOR_MONEY, 960,250,SCRIPT_ALIGN_CENTER,1.5);
	// CreateString(true,"ShipClass","",FONT_NORMAL,COLOR_NORMAL, 960,275,SCRIPT_ALIGN_CENTER,1.5);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("confirmShipChangeName","confirmShipChangeName",0);
	SetEventHandler("CheckForRename","CheckForRename",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
	SetEventHandler("ExitRepairMenu", "ExitRepairMenu", 0);
	SetEventHandler("ExitShipPaintMenu", "ExitShipPaintMenu",0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("ExitCannonsMenu", "ExitCannonsMenu", 0);
    SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("BuyShipEvent","BuyShipEvent",0);
    //////////////////
    SetNewGroupPicture("REPAIR_Money_PIC", "ICONS_CHAR", "Money");
    
    SetNewGroupPicture("REPAIR_Hull_PIC", "SHIP_STATE_ICONS", "Hull");
    SetNewGroupPicture("REPAIR_Sails_PIC", "SHIP_STATE_ICONS", "Sails");

    FillShipyardTable();
	
	SetCurrentNode("SHIPS_SCROLL");
	bShipyardOnTop = false;
	SetDescription();
	bEmptySlot = false;
	sMessageMode = "";
	SetButtonsAccess();
	timeHull = 0;
	timeRig = 0;
	
	SetFormatedText("STORECAPTION", XI_ConvertString("Colony" + refNPCShipyard.City) + ": " + XI_ConvertString("titleShipyard"));
}

void ProcessExitCancel()
{
    bGameMenuStart = false; // выход из меню, показываем landinterface
	// boal время на ремонт -->
    if (timeRig > 0 || timeHull > 0)
    {
        LAi_Fade("", "");
        bQuestCheckProcessFreeze = true;
    	WaitDate("",0,0,0, 0, makeint( (timeHull/4.0 + timeRig/6.0) * 60.0));
    	RecalculateJumpTable();
    	bQuestCheckProcessFreeze = false;
    	RefreshLandTime();
	}
	if (sti(pchar.ship.type) == SHIP_NOTUSED) PChar.nation = GetBaseHeroNation();
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetPlayerType(pchar);
	}
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("confirmShipChangeName","confirmShipChangeName");
	DelEventHandler("CheckForRename","CheckForRename");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("ExitCannonsMenu", "ExitCannonsMenu");
    DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitRepairMenu", "ExitRepairMenu");
	DelEventHandler("ExitShipPaintMenu", "ExitShipPaintMenu");
	DelEventHandler("BuyShipEvent","BuyShipEvent");
	
	if(NavyPenalty(pchar)) notification(""+XI_ConvertString("Sailing note")+NavyPenalty(pchar)+XI_ConvertString("Sailing2 note")+"","Sailing");
	
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
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

    switch(nodName)
	{
        case "SHIPS_SCROLL":
			if (comName=="click" || comName=="activate")
			{
				CurTable = "";
				NullSelectTable("TABLE_SHIPYARD"); // убрать скрол
				bShipyardOnTop = false;
				SetDescription();
				SetButtonsAccess();
			}
		break;
 
        case "BUY_CANNONS":
			if (comName=="click" || comName=="activate")
			{
				IDoExit(RC_INTERFACE_TO_CANNONS);
			}
		break;
 
		case "BUTTON_SELL":
			if (comName=="click" || comName=="activate")
			{
			    ShowMessageInfo();
			}
		break;

		case "BUTTON_BUY":
			if (comName=="click" || comName=="activate")
			{
			    ShowMessageInfo();
			}
		break;

		case "MSG_OK":
			if (comName=="click" || comName=="activate")
			{
			    MessageOk();
			}
		break;
		
		case "BUTTON_REPAIR":
			if (comName=="click" || comName=="activate")
			{
			    ShowRepairMenu();
			}
		break;
		
		case "REPAIR_LEFT_H":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("hull", -1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("hull", -5);
			}
		break;
		
		case "REPAIR_RIGHT_H":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("hull", 1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("hull", 5);
			}
		break;
		
		case "REPAIR_LEFT_S":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("sail", -1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("sail", -5);
			}
		break;
		
		case "REPAIR_RIGHT_S":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("sail", 1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("sail", 5);
			}
		break;
		
		case "REPAIR_OK":
			if (comName=="click" || comName=="activate")
			{
			    RepairOk();
			}
		break;
		
		case "REPAIR_ALL":
			if (comName=="click" || comName=="activate")
			{
			    RepairAll();
			}
		break;

		case "BUTTON_PAINT":
			if (comName=="click" || comName=="activate")
			{
			    ShowShipPaintMenu();
			}
		break;
		
		case "PAINT_LEFT":
			if(comName=="click")
			{
				ChangeHull(-1);	
			}
		break;
		
		case "PAINT_RIGHT":
			if(comName=="click")
			{
				ChangeHull(1);
			}
		break;
		
		case "PAINT_OK":
			if(comName=="click")
			{
				SetNewHullToCharacterShip();	
			}
		break;
		case "PAINT_OK2":
			if(comName=="click")
			{
				SetNewHullToCharacterShip();	
			}
		break;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void FillShipsScroll()
{
    DeleteAttribute(&GameInterface, "SHIPS_SCROLL");
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
		cn = GetCompanionIndex(pchar, i);
		if (FirstTime)
		{
			cn = GetCompanionIndex(pchar, i);
			CompanionIdx[i] = cn;
		} else {
			cn = CompanionIdx[i];
		}
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
	if (FirstTime) FirstTime = false;
	
	for (i = m; i < COMPANION_MAX; i++) {
		attributeName = "pic" + (i+1);
		GameInterface.SHIPS_SCROLL.(attributeName).character = -1;
		GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used";
		GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP";
	}

	GameInterface.SHIPS_SCROLL.ListSize = COMPANION_MAX;
	GameInterface.SHIPS_SCROLL.NotUsed = 0;
}

void ProcessFrame()
{
	string attributeName;
	int iCharacter;
    if (GetCurrentNode() == "PASSENGERSLIST" && sti(GameInterface.PASSENGERSLIST.current)!= nCurScrollOfficerNum)
	{
		nCurScrollOfficerNum = sti(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
	}
	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		if (sti(GameInterface.SHIPS_SCROLL.current)!= nCurScrollNum)	
		{
            CurTable = "";
			NullSelectTable("TABLE_SHIPYARD"); // убрать скрол
			bShipyardOnTop = false;
			
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			attributeName = "pic" + (nCurScrollNum+1);
			iCharacter = sti(GameInterface.SHIPS_SCROLL.(attributeName).character);
			
			if(iCharacter > 0)
			{
				bEmptySlot = false;
				shipIndex= nCurScrollNum+ 1;
				if (shipIndex< 0)
				{
					shipIndex= 0;
				}
				if (sti(refCharacter.ship.type) == SHIP_NOTUSED)
				{
					shipIndex= -1;
					trace("shipIndex= -1");
				}
				// boal оптимизация скилов -->
			    DelBakSkillAttr(refCharacter);
			    ClearCharacterExpRate(refCharacter);
			    RefreshCharacterSkillExpRate(refCharacter);
			    SetEnergyToCharacter(refCharacter);
			    // boal оптимизация скилов <--
			}
			else
			{
				iCharacter = GetMainCharacterIndex();
				shipIndex= -1;
				bEmptySlot = true;
				
			}
			sChrId = characters[iCharacter].id;
			refCharacter = characterFromID(sChrId);
			SetDescription();
			SetButtonsAccess();
		}
	}
}			

void SetDescription()
{
	int iShip = sti(refCharacter.ship.type);
	ref refBaseShip = GetRealShip(iShip);
	// нулим все формы, тк корабля может не быть
	SetFormatedText("SHIP_RANK","");
	Table_Clear("TABLE_OTHER", false, true, false);

	FillShipParam(refCharacter);
	// под кораблём имя и класс
	if (iShip != SHIP_NOTUSED && !bEmptySlot)
	{
		GameInterface.strings.shipname = refCharacter.ship.name;
		GameInterface.strings.shipclass = XI_ConvertString("ShipClass")+ " " + refBaseShip.Class;
	} else {
		GameInterface.strings.shipname = "";
		GameInterface.strings.shipclass = "";
	}
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\le\portraits\256\face_" + refCharacter.FaceId + ".tga");
	SetFormatedText("CHARACTER_NAME", GetFullName(refCharacter));
	string sText = MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER);
	SetFormatedText("OUR_GOLD", sText);
	SetFormatedText("STORE_CAPACITY", XI_ConvertString("Shipyard"));
}

void FillShipParam(ref _chr)
{
	int iMoney;
	int iShip = sti(_chr.ship.type);
	bool bShipExists = (!bEmptySlot) || (bShipyardOnTop);
	if (iShip != SHIP_NOTUSED && bShipExists)
	{
        if (CheckAttribute(_chr, "Ship.Cargo.RecalculateCargoLoad") && sti(_chr.Ship.Cargo.RecalculateCargoLoad))
		{
			RecalculateCargoLoad(_chr);
			_chr.Ship.Cargo.RecalculateCargoLoad = 0;
		}
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName + refBaseShip.ship.upgrades.hull;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\le\ships\" + sShip + ".tga");

		GameInterface.edit_box.str = _chr.ship.name;
		
		SetFormatedText("SHIP_RANK", refBaseShip.Class);

		SetShipOTHERTable2("TABLE_OTHER", _chr);
		string sShipName = refBaseShip.BaseName;
		SetFormatedText("INFO_CAPTION", XI_ConvertString(sShipName));
		string descr = GetShipDescr(refBaseShip);
		SetFormatedText("INFO_TEXT", descr);
		int nStrings = GetNumberOfStringsInFormatedText("INFO_TEXT", descr); // считаем сколько строк в форме
		SetNodeUsing("SCROLL_TEXT",true);
		SendMessage( &GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 13, 0 ); //1 - запрет, 0 - нет
		if(nStrings <11)// Запрет на скроллинг
		{
			SetNodeUsing("SCROLL_TEXT",false);
			SendMessage( &GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 13, 1 ); //1 - запрет, 0 - нет
		}
		if (bShipyardOnTop)
		{
			if (bEmptySlot)// проверка на пустой слот
			{
				iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard);
				SetFormatedText("BUYSELL_PRICE", XI_ConvertString("BuyCost") + " " + iMoney);
			} else {
				iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) - GetShipSellPrice(refCharacter, refNPCShipyard);
				SetFormatedText("BUYSELL_PRICE", XI_ConvertString("BuyCostTradeIn") + " " + iMoney);
			}
		} else {
			SetFormatedText("BUYSELL_PRICE", XI_ConvertString("SellCost") + " " + GetShipSellPrice(refCharacter, refNPCShipyard));
		}
		SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"BUYSELL_PRICE",5);
		SetNodeUsing("TABLE_OTHER", true);
		SetNodeUsing("SHIP_BIG_PICTURE", true);
		SetNodeUsing("SHIP_PERK1", true);
		SetNodeUsing("SHIP_PERK2", true);
		ShowCannonsMenu();
		SetShipPerks(_chr);
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\le\ships\empty_ship.tga");
		SetNodeUsing("SHIP_BIG_PICTURE", false);
		SetNodeUsing("SHIP_PERK1", false);
		SetNodeUsing("SHIP_PERK2", false);
		SetFormatedText("INFO_CAPTION","");
		SetFormatedText("INFO_TEXT","");
		SetFormatedText("BUYSELL_PRICE","");
		SetNodeUsing("TABLE_OTHER", false);
		HideCannonsMenu();
	}
	Table_UpdateWindow("TABLE_OTHER");
}

void confirmShipChangeName()
{
	/*
	if (shipIndex== -1) return;
	refCharacter.ship.name = GameInterface.edit_box.str;
	GameInterface.edit_box.str = refCharacter.ship.name;
	SetCurrentNode("SHIP_INFO_TEXT");   */
}

void CheckForRename()
{
	/*if (GetShipRemovable(refCharacter) == true && shipIndex!= -1)
	{
		SetCurrentNode("EDIT_BOX");
	}    */
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

	bool  bShowHint = true;

	ref rChr;
	if (bShipyardOnTop)
	{
	    rChr = refNPCShipyard;
	}
	else
	{
		rChr = refCharacter;
	}
	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
			if (shipIndex != -1 || bShipyardOnTop)
			{
			    iShip = sti(rChr.ship.type);
			    refBaseShip = GetRealShip(iShip);
				string sShipPic = refBaseShip.BaseName + refBaseShip.ship.upgrades.hull;
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sPicture = "interfaces\le\ships\" + sShipPic + ".tga";
				SetNewPicture("SHIP_BIG_PICTURE_ZOOM", "interfaces\le\ships\" + sShipPic + ".tga");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat2", "ShipsDescribe.txt");
				SetNewPicture("SHIP_BIG_PICTURE_ZOOM", "interfaces\le\ships\empty_ship.tga");
			}
		break;

		case "SHIP_PERK1":
			string sPerkName1 = GetShipSpecDesc(rChr);
			sGroup = "PERKS_SHIPS";
			sGroupPicture = sPerkName1;
			sHeader = GetConvertStr(sPerkName1, "ShipsPerksDescribe.txt");
			sText1 = GetConvertStr(sPerkName1 + "_desc", "ShipsPerksDescribe.txt");
			sText3 = GetConvertStr(sPerkName1 + "_desc2", "ShipsPerksDescribe.txt");
		break;

		case "SHIP_PERK2":
			string sPerkName2 = GetShipTraitDesc(rChr);
			sGroup = "PERKS_SHIPS";
			sGroupPicture = sPerkName2;
			sHeader = GetConvertStr(sPerkName2, "ShipsPerksDescribe.txt");
			sText1 = GetConvertStr(sPerkName2 + "_desc", "ShipsPerksDescribe.txt");
			sText3 = GetConvertStr(sPerkName2 + "_desc2", "ShipsPerksDescribe.txt");
			iShip = sti(rChr.ship.type);
			refBaseShip = GetRealShip(iShip);
			if(CheckAttribute(refBaseShip, "DeadSailors"))
			{
				aref arShipBonus;
				makearef(arShipBonus, refBaseShip.DeadSailors);
				sText3 += newStr() + GetAssembledString(GetConvertStr("sp3_SailorsBoardingBonus_desc","ShipsPerksDescribe.txt"), arShipBonus)
									 + GetAssembledString(GetConvertStr("sp3_SailorsBoardingBonus1_desc","ShipsPerksDescribe.txt"), refBaseShip);
				sText3 += newStr() + GetAssembledString(GetConvertStr("sp3_SurrenderChanceBonus_desc","ShipsPerksDescribe.txt"), arShipBonus)
								   + GetAssembledString(GetConvertStr("sp3_SurrenderChanceBonus1_desc","ShipsPerksDescribe.txt"), refBaseShip);
			}
		break;

		case "SHIPS_SCROLL":
			if (shipIndex != -1)
			{
			    iShip = sti(refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetShipDescr(refBaseShip);
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat2", "ShipsDescribe.txt");
			}
		break;

		case "MAIN_CHARACTER_PICTURE":
			// отдельная форма
			bShowHint = false;
			ShowRPGHint();
		break;

		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(rChr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		    {
		    	ref Cannon = GetCannonByType(sti(rChr.Ship.Cannons.Type));
		    	sText2 = XI_ConvertString("Type") +": " + XI_ConvertString(GetCannonType(sti(rChr.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + XI_ConvertString("Caliber") + ": " + XI_ConvertString("caliber" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + XI_ConvertString("Fire range2") + ": "  + sti(Cannon.FireRange);
		    	sText2 = sText2 + NewStr() + XI_ConvertString("CannonsDamage") + ": x" + FloatToString(stf(Cannon.DamageMultiply), 1);
		    	sText2 = sText2 + NewStr() + XI_ConvertString("CannonsTime") + ": " + sti(GetCannonReloadTime(Cannon)) + " " + XI_ConvertString("sec.");
		    	sText2 = sText2 + NewStr() + XI_ConvertString("Weight") + ": " + sti(Cannon.Weight) + " " + XI_ConvertString("cwt");

		    	sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(rChr.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type));
		    }
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText2 = XI_ConvertString("other_crew_descr");
				sText2 = sText2 + NewStr() + XI_ConvertString("other_crew_descr_max") + ": " + GetMaxCrewQuantity(rChr);
			}
			// процент ремонта
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(rChr), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(rChr), 1) + " %";
			}
			// трюм
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = XI_ConvertString("Used") + ": " + FloatToString((stf(GetCargoLoad(rChr))  /  stf(GetCargoMaxSpace(rChr))) * 100.0, 1)+ " %";
			}
		break;
		case "TABLE_SHIPYARD" :
		    sHeader = XI_Convertstring("Shipyard");
			sText1  = GetConvertStr("Shipyard_hint", "ShipsDescribe.txt");
		break;
	}
	if (bShowHint)
	{
		if(sCurrentNode == "SHIP_BIG_PICTURE")
		{
			XI_WindowShow("SHIP_ZOOM_WINDOW", true);
		} else {
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, picW, picH);
		}
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
	XI_WindowShow("SHIP_ZOOM_WINDOW", false);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    NullSelectTable("TABLE_OTHER");
 // не тереть скрол на верфи

    // заполнялка
    if (CurTable == "TABLE_SHIPYARD")
	{
        FillShipyardShip(refNPCShipyard, GameInterface.(CurTable).(CurRow).sShipId);
		FillShipParam(refNPCShipyard);
		bShipyardOnTop = true;
		SetButtonsAccess();
	}
}

void OnTableClick()
{
	FillShipParam(refNPCShipyard);
	bShipyardOnTop = true;
	SetButtonsAccess();
}

void OnHeaderClick()
{
	string sNode = GetEventData();
	int iCol = GetEventData();
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
	SetSPECIALMiniTable("RPG_TABLE_SMALLSKILL", refCharacter);
    SetOTHERMiniTable("RPG_TABLE_SMALLOTHER", refCharacter);
    SetFormatedText("RPG_OFFICER_NAME", GetFullName(refCharacter));

	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
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

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void ShowMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MSG_CANCEL");
}

void ShowOtherClick()
{
	if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType")
	{
		ShowCannonsMenu();
	}
}

void ShowCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", true);
	XI_WindowDisable("CANNONS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);

	// SetCurrentNode("CANNONS_CANCEL");

    DeleteAttribute(&GameInterface, "CANNONS_TABLE.BackUp")
    CannonsMenuRefresh();
}
void CannonsMenuRefresh()
{
	ref rChr;
	if (bShipyardOnTop)
	{
	    rChr = refNPCShipyard;
	}
	else
	{
		rChr = refCharacter;
	}
	int idx = GetCannonGoodsIdxByType(sti(rChr.Ship.Cannons.Type));
	if (idx != -1)
	{
	    SetNewGroupPicture("CANNONS_PIC", "GOODS", Goods[idx].Name);
		SetFormatedText("CANNONS_TEXT", XI_ConvertString(Goods[idx].Name));
		if (bShipyardOnTop)
		{
			SetFormatedText("CANNONS_QTY_F", its(GetBortCannonsQtyMax(rChr, "cannonf")));
			SetFormatedText("CANNONS_QTY_B", its(GetBortCannonsQtyMax(rChr, "cannonb")));
			SetFormatedText("CANNONS_QTY_R", its(GetBortCannonsQtyMax(rChr, "cannonr")));
			SetFormatedText("CANNONS_QTY_L", its(GetBortCannonsQtyMax(rChr, "cannonl")));
			SetNewGroupPicture("CANNONS_PIC", "GOODS", "");
			SetFormatedText("CANNONS_TEXT", "");
		} else {
			if (!bEmptySlot)
			{
				if (GetBortCannonsQty(rChr, "cannonf")+GetBortCannonsQty(rChr, "cannonb")+GetBortCannonsQty(rChr, "cannonr")+GetBortCannonsQty(rChr, "cannonl")>0)
				{
					SetFormatedText("CANNONS_QTY_F", its(GetBortCannonsQty(rChr, "cannonf")));
					SetFormatedText("CANNONS_QTY_B", its(GetBortCannonsQty(rChr, "cannonb")));
					SetFormatedText("CANNONS_QTY_R", its(GetBortCannonsQty(rChr, "cannonr")));
					SetFormatedText("CANNONS_QTY_L", its(GetBortCannonsQty(rChr, "cannonl")));
				} else { 
					SetNewGroupPicture("CANNONS_PIC", "GOODS", "");
					SetFormatedText("CANNONS_TEXT", "");
					SetFormatedText("CANNONS_QTY_F", "0");
					SetFormatedText("CANNONS_QTY_B", "0");
					SetFormatedText("CANNONS_QTY_R", "0");
					SetFormatedText("CANNONS_QTY_L", "0");
				}
			} else {
				SetNewGroupPicture("CANNONS_PIC", "GOODS", "");
				SetFormatedText("CANNONS_TEXT", "");
				SetFormatedText("CANNONS_QTY_F", "0");
				SetFormatedText("CANNONS_QTY_B", "0");
				SetFormatedText("CANNONS_QTY_R", "0");
				SetFormatedText("CANNONS_QTY_L", "0");
			}
		}
		/// всего GetCannonsNum(refCharacter)
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
}
void ExitCannonsMenu()
{
	HideCannonsMenu();
}

void HideCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", false);
	XI_WindowDisable("CANNONS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

////////////// ценообразование

void FillShipyardTable()
{
    Table_Clear("TABLE_SHIPYARD", false, true, false);

	GameInterface.TABLE_SHIPYARD.hr.td1.str = XI_ConvertString("Ship");
	GameInterface.TABLE_SHIPYARD.hr.td2.str = XI_ConvertString("ShipClass");
	GameInterface.TABLE_SHIPYARD.hr.td3.str = XI_ConvertString("Cannons");
	GameInterface.TABLE_SHIPYARD.hr.td4.str = XI_ConvertString("Capacity");
	GameInterface.TABLE_SHIPYARD.hr.td5.str = XI_ConvertString("Cost");
	GameInterface.TABLE_SHIPYARD.select = 0;
	GameInterface.TABLE_SHIPYARD.top = 0;

	aref   arDest, arImt;
	string sAttr;
	int    iNum, i, iShip;
	ref    refBaseShip;
	string sShip, sShipPic;
	string row;

	makearef(arDest, refNPCShipyard.shipyard);
	iNum = GetAttributesNum(arDest);
	for (i = 0; i < iNum; i++)
	{
        row = "tr" + (i+1);

		arImt = GetAttributeN(arDest, i);
		//Log_Info(GetAttributeName(arImt));
		sAttr = GetAttributeName(arImt);
    	FillShipyardShip(refNPCShipyard, sAttr); // скинуть в стандарт корабль из ШипХХ

    	iShip = sti(refNPCShipyard.Ship.Type);
    	refBaseShip = GetRealShip(iShip);
		
		sShip = refBaseShip.BaseName;
		sShipPic = refBaseShip.BaseName + refBaseShip.ship.upgrades.hull;
		//
		GameInterface.TABLE_SHIPYARD.(row).sShipId = sAttr;
        GameInterface.TABLE_SHIPYARD.(row).td1.icon.texture = "interfaces\le\ships\" + sShipPic + ".tga";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.uv = "0,0,1,1";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.width = 60;
    	GameInterface.TABLE_SHIPYARD.(row).td1.icon.height = 60;
    	GameInterface.TABLE_SHIPYARD.(row).td1.icon.offset = "248, 0";
    	GameInterface.TABLE_SHIPYARD.(row).td1.textoffset = "0,0";
		GameInterface.TABLE_SHIPYARD.(row).td1.str = XI_Convertstring(sShip) + "\n"+refNPCShipyard.ship.name;
		GameInterface.TABLE_SHIPYARD.(row).td1.align = "left";
		GameInterface.TABLE_SHIPYARD.(row).td2.str = refBaseShip.Class;
		GameInterface.TABLE_SHIPYARD.(row).td3.str = sti(refBaseShip.CannonsQuantity);
		GameInterface.TABLE_SHIPYARD.(row).td4.str = GetCargoMaxSpace(refNPCShipyard);
		GameInterface.TABLE_SHIPYARD.(row).td5.str = GetShipBuyPrice(iShip, refNPCShipyard);
		GameInterface.TABLE_SHIPYARD.(row).td5.color = argb(255,255,228,80);
    }

	Table_UpdateWindow("TABLE_SHIPYARD");
}

void SetButtonsAccess()
{
	// Jason --> для мультиквеста
	bool bMef = false;
	bool bMir = false;
	bool bVal = false;
	
	ref mc = GetMainCharacter();
	
	if(CheckAttribute(refCharacter,"ship.type") && (sti(refCharacter.ship.type) != SHIP_NOTUSED) && CheckAttribute(mc, "questTemp.HWIC.TakeQuestShip")) // тк корабля может не быть совсем !!
	{		
		bMef = sti(RealShips[sti(refCharacter.ship.type)].basetype) == SHIP_MAYFANG;
		bMir = sti(RealShips[sti(refCharacter.ship.type)].basetype) == SHIP_MIRAGE;
		bVal = sti(RealShips[sti(refCharacter.ship.type)].basetype) == SHIP_VALCIRIA;
	}
	// <-- для мультиквеста

	if(!bEmptySlot && CheckAttribute(refCharacter,"ship.type") && (sti(refCharacter.ship.type) != SHIP_NOTUSED))
	{
		SetNodeUsing("BUTTON_SELL", true);
		SetSelectable("BUTTON_SELL", true);
		SetNodeUsing("BUTTON_BUY", false);
		SetSelectable("BUTTON_REPAIR", false);
		SetNodeUsing("BUTTON_REPAIR", true);
		SetNodeUsing("BUTTON_PAINT", true);
	} else {
		SetNodeUsing("BUTTON_SELL", false);
		SetNodeUsing("BUTTON_BUY", false);
		SetNodeUsing("BUTTON_REPAIR", false);
		SetNodeUsing("BUTTON_PAINT", false);
	}	

    if (bShipyardOnTop)
    {
		SetNodeUsing("BUTTON_REPAIR", false);
		SetNodeUsing("BUTTON_PAINT", false);
		SetSelectable("BUTTON_SELL", false);
		SetNodeUsing("BUTTON_SELL", false);
		SetSelectable("BUTTON_BUY", true);
		SetNodeUsing("BUTTON_BUY", true);
		
    	if (shipIndex == -1)// проверка на цену
    	{
			trace("ship index = -1");
    	    if (GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) > sti(pchar.Money) )
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
			if (!bPassengersAccess() && sti(pchar.ship.type) != SHIP_NOTUSED)
			{// нельзя купить корабль компаньону, если нет компаньонов
				SetSelectable("BUTTON_BUY", false);
			}
    	}
    	else
    	{
    	    if (GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) > (GetShipSellPrice(refCharacter, refNPCShipyard) + sti(pchar.Money)) )
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
    	    if (!GetRemovable(refCharacter) || !GetShipRemovable(refCharacter))
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
			if (bMef || bMir || bVal)
    	    {//временный квестовый корабль нельзя купить-продать на верфи
				SetSelectable("BUTTON_BUY", false);
    	    }
    	}
    }
    else
    {
        SetSelectable("BUTTON_BUY", false);

        if (GetHullPercent(refCharacter) < 100 || GetSailPercent(refCharacter) < 100)
        {
            SetSelectable("BUTTON_REPAIR", true);
        }
        if (shipIndex == -1)
        {
            SetSelectable("BUTTON_SELL", false);
            SetSelectable("BUTTON_REPAIR", false);
        }
        else
        {
            if (!GetRemovable(refCharacter) || !GetShipRemovable(refCharacter))
    	    {
    	        SetSelectable("BUTTON_SELL", false);
    	    }
			if (bMef || bMir || bVal)
    	    {//временный квестовый корабль нельзя купить-продать на верфи
    	        SetSelectable("BUTTON_SELL", false);
    	    }
    	    if (refCharacter.id == pchar.id && GetCompanionQuantity(pchar) > 1)
    	    { // нельзя продать корабль ГГ, если есть ещё компаньоны
    	        SetSelectable("BUTTON_SELL", false);
    	    }
		}
    }
}

//////////////// назначение капитана  //////////////////////////////////////////////////////////////////////
void ShipChangeCaptan()
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

void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
}

void AcceptAddOfficer()
{
	string  attributeName2 = "pic"+(nCurScrollOfficerNum+1);
    ref     sld;

    if (checkAttribute(GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
    {
		int iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);
        // назначение нового кэпа, возможно, если там уже не наш, те или враг или снят
        sld = GetCharacter(iChar);
		DeleteAttribute(sld, "ship");
		sld.ship.Type = SHIP_NOTUSED;

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);
		RemovePassenger(pchar, sld);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);

		refCharacter = sld;
		DoBuyShip();
		ProcessFrame();
		InterfaceStates.Shipyard.FreePaint = true;
		ShowShipPaintMenu();
	}
	ExitOfficerMenu();
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
			SetFormatedText("OFFICER_JOB", GetOfficerPosition(sCharacter));
	        SetSelectable("ACCEPT_ADD_OFFICER", true);
	        return;
        }
	}
    Table_Clear("TABLE_SMALLSKILL", false, true, true);
    Table_Clear("TABLE_SMALLOTHER", false, true, true);
    SetFormatedText("OFFICER_NAME", "");
	SetFormatedText("OFFICER_JOB", "");
    SetSelectable("ACCEPT_ADD_OFFICER", false);
}

void FillPassengerScroll()
{
	int i, howWork;
	string faceName;
	string attributeName;
	int _curCharIdx;
	ref _refCurChar;
	bool  ok;

	DeleteAttribute(&GameInterface, "PASSENGERSLIST");

	nCurScrollOfficerNum = -1;
	GameInterface.PASSENGERSLIST.current = 0;

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = nListSize;

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
		_curCharIdx = GetPassenger(pchar,i);

		if (_curCharIdx!=-1)
		{
			ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
			bool ob = CheckAttribute(&characters[_curCharIdx], "CompanionDisable") && sti(characters[_curCharIdx].CompanionDisable) == true;
			if (!ok && !ob && GetRemovable(&characters[_curCharIdx]))
			{
				GameInterface.PASSENGERSLIST.(attributeName).character = _curCharIdx;
				GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup", "FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
	GameInterface.PASSENGERSLIST.ListSize = m + 2; // не знаю зачем, но для совместимости с "было"
}
// рефреш скилов офа и ГГ, если офа сняли для компаньона
void DelBakSkill()
{
	DelBakSkillAttr(refCharacter);
    ClearCharacterExpRate(refCharacter);
    RefreshCharacterSkillExpRate(refCharacter);
    SetEnergyToCharacter(refCharacter);

    DelBakSkillAttr(pchar);
    ClearCharacterExpRate(pchar);
    RefreshCharacterSkillExpRate(pchar);
    SetEnergyToCharacter(pchar);
}

void ShowMessageInfo()
{
	bool   bBuy;
	int    iMoney;
	string add = "";

	if (bShipyardOnTop) // на стороне верфи (купить)
    {
        bBuy = true;
		// if (shipIndex == -1)// проверка на цену
		if (bEmptySlot)// проверка на пустой слот
    	{
    	    iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard);
    	}
    	else
    	{
            iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) - GetShipSellPrice(refCharacter, refNPCShipyard);
    	}
    }
    else  // продать
    {
        bBuy = false;
        iMoney = GetShipSellPrice(refCharacter, refNPCShipyard);
    }
	SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("Ship"));

	if (bBuy)
	{
		if (iMoney < 0) add = "-";
		SetFormatedText("MSG_WINDOW_TEXT",  XI_ConvertString("BuyShipFor") + add + FindRussianMoneyString(abs(iMoney)) + "?");
		SetSelectable("MSG_OK", true);
		sMessageMode = "ShipBuy";
	}
	else
	{
	    SetFormatedText("MSG_WINDOW_TEXT", XI_ConvertString("SellShipFor") + add + FindRussianMoneyString(abs(iMoney)) + "?");
		SetSelectable("MSG_OK", true);
		sMessageMode = "ShipSell";
	}
	ShowMsgMenu();
}

void MessageOk()
{
	switch (sMessageMode)
	{
	    case "ShipSell" :
	        DoSellShip(true);
	        ExitMsgMenu();
	    break;

	    case "ShipBuy" :
	        DoBuyShipMain();
	    break;
	}
}

bool DoSellShip(bool _refresh)
{
	ref chref = refCharacter;
	if (shipIndex != -1 && sti(chref.ship.type) != SHIP_NOTUSED)
	{
    	int sellPrice = GetShipSellPrice(chref, refNPCShipyard);

    	AddMoneyToCharacter(pchar, sellPrice);
        AddCharacterExpToSkill(pchar, "Commerce", sellPrice / 1600.0);
        WaitDate("",0,0,0, 0, 30);
        Statistic_AddValue(pchar, "SellShip", 1);

    	DeleteAttribute(chref,"ship.sails");
    	DeleteAttribute(chref,"ship.blots");
        DeleteAttribute(chref,"ship.masts");
		DeleteAttribute(chref,"ship.hulls");
		
        // в списке на покупку. -->
        AddShip2Shipyard(chref);
        // в списке на покупку. <--
    	chref.ship.type = SHIP_NOTUSED;
    	// снять кэпа -->
    	if (_refresh)
		{
	    	if (sti(chref.index) != GetMainCharacterIndex())
	    	{
	            RemoveCharacterCompanion(pchar, chref);
				AddPassenger(pchar, chref, false);
				DelBakSkill();
				//navy --> Фигвам, а не халява :)
				if (CheckAttribute(chref, "PGGAi") && CheckAttribute(chref, "PGGAi.OwnShip")) //за корабли данные ГГ, деньги ГГ.
				{
					chref.Payment = true;
					DeleteAttribute(chref, "PGGAi.OwnShip")
					Log_Info(XI_ConvertString("CompanionMoney"));
					AddMoneyToCharacter(pchar, -(sellPrice));
				}
				//navy <--
	    	}
	    	else
	    	{
          		pchar.location.from_sea = ""; // нет корабля в порту
	    	}
			CompanionIdx[sti(GameInterface.SHIPS_SCROLL.current)] = -1;
			for (i=sti(GameInterface.SHIPS_SCROLL.current); i<COMPANION_MAX-1; i++)
				CompanionIdx[i] = CompanionIdx[i+1];
			CompanionIdx[COMPANION_MAX-1] = -1;
    		RefreshShipLists();
			GameInterface.SHIPS_SCROLL.current = GetCompanionQuantity(pchar) - 1;
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
    	}
		
		return true;
	}
	
	return false;
}

void RefreshShipLists()
{
    refCharacter = pchar;
	FillShipsScroll();
   	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
    SetCurrentNode("SHIPS_SCROLL");
	ProcessFrame();
	FillShipyardTable();
	bShipyardOnTop = false;
	SetDescription();
}

void AddShip2Shipyard(ref _chr)
{
    aref    arTo, arFrom;

	aref   arDest, arImt;
	string sAttr;
	int    iNum, i, iShip;
	ref    refBaseShip;
	string sShip;
	string row;

    iShip = sti(_chr.ship.type);
    RealShips[iShip].StoreShip = true;  // кораль на верфи, трется отдельным методом
    RealShips[iShip].Stolen = 0; // уже не ворованный
	makearef(arDest, refNPCShipyard.shipyard);
	iNum = GetAttributesNum(arDest);
	if (iNum == 0)
	{
	    sAttr = "ship1";
	}
	else
	{
	    arImt = GetAttributeN(arDest, iNum - 1);
	    sAttr = GetAttributeName(arImt) + "2";
	}
	makearef(arTo,   refNPCShipyard.ship);
	makearef(arFrom, _chr.Ship);
	CopyAttributes(arTo, arFrom);
	// нулим экипаж и трюм
	SetCrewQuantity(refNPCShipyard, 0);
	DeleteAttribute(refNPCShipyard, "Ship.Cargo");  //пустой трюм
	SetGoodsInitNull(refNPCShipyard);
    RecalculateCargoLoad(refNPCShipyard);

	FillShipyardShipBack(refNPCShipyard, sAttr);
	// бакапим атрибуты груза и матросов
	DeleteAttribute(refNPCShipyard, "BakCargo");
 	DeleteAttribute(refNPCShipyard, "BakCrew");
 	refNPCShipyard.BakCargo = "";
	makearef(arTo,   refNPCShipyard.BakCargo);
	makearef(arFrom, _chr.Ship.Cargo);
	CopyAttributes(arTo, arFrom);

	refNPCShipyard.BakCrew = "";
	makearef(arTo,   refNPCShipyard.BakCrew);
	makearef(arFrom, _chr.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void DoBuyShip()
{
    aref    arTo, arFrom;
	int     iBuyMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard);

 	DeleteAttribute(refNPCShipyard, "BakCargo");
 	DeleteAttribute(refNPCShipyard, "BakCrew");
	bool sold = DoSellShip(false);
	AddMoneyToCharacter(pchar, -iBuyMoney);

    AddCharacterExpToSkill(pchar, "Commerce", iBuyMoney / 700.0);
    WaitDate("",0,0,0, 0, 30);
    Statistic_AddValue(pchar, "BuyShip", 1);

    FillShipyardShip(refNPCShipyard, sShipId); // то, что покупаем

    makearef(arTo,   refCharacter.ship);
	makearef(arFrom, refNPCShipyard.Ship);
	CopyAttributes(arTo, arFrom);

	DeleteAttribute(refNPCShipyard, "shipyard." + sShipId);

    int iShip = sti(refCharacter.ship.type);
    DeleteAttribute(&RealShips[iShip], "StoreShip"); // можно тереть

	if (CheckAttribute(refNPCShipyard, "BakCargo")) // есть бакап корабля
	{
        DeleteAttribute(refCharacter, "Ship.Cargo");
		DeleteAttribute(refCharacter, "Ship.Crew");

		refCharacter.Ship.Cargo = "";
		makearef(arTo,   refCharacter.Ship.Cargo);
		makearef(arFrom, refNPCShipyard.BakCargo);
		CopyAttributes(arTo, arFrom);

        refCharacter.Ship.Crew = "";
		makearef(arTo,   refCharacter.Ship.Crew);
		makearef(arFrom, refNPCShipyard.BakCrew);
		CopyAttributes(arTo, arFrom);

		AddCharacterCrew(refCharacter, 0); // обрезать перегруз
	    RecalculateCargoLoad(refCharacter);
	}
	if (sti(refCharacter.index) == GetMainCharacterIndex())
	{
  		pchar.location.from_sea = sFrom_sea; // корабль в порту
	}
	DelBakSkill();
	
	CompanionIdx[sti(GameInterface.SHIPS_SCROLL.current)] = sti(refCharacter.index);
	int slotIndex = 0;
	if (sold) {
		slotIndex = sti(GameInterface.SHIPS_SCROLL.current);
	} else {
		slotIndex = GetCompanionQuantity(pchar) - 1;
	}

	RefreshShipLists();
	GameInterface.SHIPS_SCROLL.current = slotIndex;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
	ProcessFrame();
}

void DoBuyShipMain()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".sShipId"))
	{
	    sShipId = GameInterface.(CurTable).(CurRow).sShipId;

		if (!bEmptySlot || pchar.ship.type == SHIP_NOTUSED) // был коарбль или ГГ без корабля
		{
		    DoBuyShip();
		    ExitMsgMenu();
			InterfaceStates.Shipyard.FreePaint = true;
			ShowShipPaintMenu();
		}
		else
		{
		    ExitMsgMenu();
		    ShipChangeCaptan();
		}
	}
}

//////////////////// ремонт ///////////////
void ExitRepairMenu()
{
	XI_WindowShow("REPAIR_WINDOW", false);
	XI_WindowDisable("REPAIR_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowShow("CANNONS_WINDOW", true);
	SetNodeUsing("BUTTON_SELL",true);
	SetNodeUsing("BUTTON_REPAIR",true);
	SetNodeUsing("BUTTON_PAINT",true);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void ShowRepairMenu()
{
	XI_WindowShow("REPAIR_WINDOW", true);
	XI_WindowDisable("REPAIR_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowShow("CANNONS_WINDOW", false);
	SetNodeUsing("BUTTON_SELL",false);
	SetNodeUsing("BUTTON_REPAIR",false);
	SetNodeUsing("BUTTON_PAINT",false);

    SetRepairData();
	SetCurrentNode("REPAIR_CANCEL");
}

void SetRepairData()
{
	RepairSail = 0;
	RepairHull = 0;
 	RepairStatShow();
}

void RepairMoneyShow()
{
    int st = GetCharacterShipType(refCharacter);
    
	SetFormatedText("REPAIR_MONEY_TEXT", its(GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard)));
}

void RepairStatShow()
{
    int hp = MakeInt(GetHullPercent(refCharacter));
	int sp = MakeInt(GetSailPercent(refCharacter));
	
	SetFormatedText("REPAIR_QTY_H", (hp+RepairHull) + "%");
	SetFormatedText("REPAIR_QTY_S", (sp+RepairSail) + "%");
	RepairMoneyShow();
}

void ClickRepairArror(string _type, int add)
{
    int st = GetCharacterShipType(refCharacter);
    int i;
    int hp = MakeInt(GetHullPercent(refCharacter));
	int sp = MakeInt(GetSailPercent(refCharacter));
	
	if (_type == "hull")
	{
		if (add > 0)
		{
			if (sti(pchar.Money) >= (GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull + add, refNPCShipyard)))
		    {
		        RepairHull = RepairHull + add;
		    }
		    else
		    {
		        i = sti(pchar.Money) - (GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard));
		        i = i / GetHullRepairCost(st, 1, refNPCShipyard); // на сколько хватит
		        RepairHull = RepairHull + i;
		    }
		    if ((RepairHull + hp) > 100)  RepairHull = 100 - hp;
	    }
	    else
	    {
            RepairHull = RepairHull + add;
			if (RepairHull < 0)  RepairHull = 0;
	    }
	}
	else
	{
	    if (add > 0)
		{
			if (sti(pchar.Money) >= (GetSailRepairCost(st, RepairSail+ add, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard)))
		    {
		        RepairSail = RepairSail + add;
		    }
		    else
		    {
		        i = sti(pchar.Money) - (GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard));
		        i = i / GetSailRepairCost(st, 1, refNPCShipyard); // на сколько хватит
		        RepairSail = RepairSail + i;
		    }
		    if ((RepairSail+sp) > 100)  RepairSail = 100 - sp;
	    }
	    else
	    {
            RepairSail = RepairSail + add;
			if (RepairSail < 0)  RepairSail = 0;
	    }
	}
	RepairStatShow();
}

void RepairOk()
{
    int st = GetCharacterShipType(refCharacter);
    int hp = MakeInt(GetHullPercent(refCharacter));
	int sp = MakeInt(GetSailPercent(refCharacter));
	float ret;
	
	if (RepairHull > 0)
	{
		timeHull = timeHull + RepairHull * (9-GetCharacterShipClass(refCharacter));
	    AddCharacterExpToSkill(pchar, "Repair", (RepairHull * (8-GetCharacterShipClass(refCharacter)) / 10.0));
		AddMoneyToCharacter(pchar, -GetHullRepairCost(st, RepairHull, refNPCShipyard));

		ret = ProcessHullRepair(refCharacter, stf(RepairHull));
	}
	if (RepairSail > 0)
	{
	  	timeRig = timeRig + RepairSail * (9-GetCharacterShipClass(refCharacter));
	    AddCharacterExpToSkill(pchar, "Repair", (RepairSail * (8-GetCharacterShipClass(refCharacter)) / 14.0));
		AddMoneyToCharacter(pchar,-GetSailRepairCost(st, RepairSail, refNPCShipyard));

		ret = ProcessSailRepair(refCharacter, stf(RepairSail));
	}
	if ((hp + RepairHull) >= 100)
	{
        refCharacter.ship.hp = GetCharacterShipHP(refCharacter);
		DeleteAttribute(refCharacter, "ship.hulls");
		DeleteAttribute(refCharacter, "ship.blots");		
	}
	if ((sp+RepairSail) >= 100)
	{
		refCharacter.ship.sp = GetCharacterShipSP(refCharacter);
		DeleteAttribute(refCharacter, "ship.sails");
		DeleteAttribute(refCharacter, "ship.masts");
	}
	///
	ExitRepairMenu();
	st = sti(GameInterface.SHIPS_SCROLL.current);
	FillShipsScroll();
	GameInterface.SHIPS_SCROLL.current = st;
	nCurScrollNum = st;
   	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
	SetDescription();
	SetButtonsAccess();
	
	if(!CheckAttribute(pchar, "questTemp.ShipyardVisit."+(NPCCity) )) 
	{
		pchar.questTemp.ShipyardVisit.(NPCCity) = true;
		pchar.questTemp.ShipyardVisit.counter = sti(pchar.questTemp.ShipyardVisit.counter) + 1;
	}	
}

void RepairAll()
{
    ClickRepairArror("sail", 100);
    ClickRepairArror("hull", 100);
}

void BuyShipEvent()
{
	if (GetSelectable("BUTTON_BUY"))
	{
	    ShowMessageInfo();
	}
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

void ExitShipPaintMenu() {
	XI_WindowShow("PAINT_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowDisable("PAINT_WINDOW", true);
	XI_WindowDisable("INFO_WINDOW", false);
	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
	SetDescription();
}

void ShowShipPaintMenu() {
	// проверка что корабль есть? и свой
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowDisable("PAINT_WINDOW", false);
	XI_WindowShow("PAINT_WINDOW", true);
	XI_WindowDisable("INFO_WINDOW", true);
	SetCurrentNode("PAINT_CANCEL");
	
	ref realShip = GetRealShip(sti(refCharacter.ship.type));
	InterfaceStates.Shipyard.SelectedHull = sti(realShip.ship.upgrades.hull);
	SetShipPaintInfo(realShip.BaseName, sti(realShip.ship.upgrades.hull), sti(InterfaceStates.Shipyard.SelectedHull), GetShipHullCount(realShip));
}

int GetShipHullCount(ref realShip) {
	if (CheckAttribute(realShip,"maxHulls")) {
		return sti(realShip.maxHulls);
	}
	return 1;
}

void SetShipPaintInfo(string shipName, int current, int selected, int max) {
	SetNodeUsing("PAINT_OK", true);
	SetNodeUsing("PAINT_CANCEL", true);
	SetNodeUsing("PAINT_OK2", false);
	SetNewPicture("PAINT_SHIP_PICTURE", "interfaces\le\ships\" + shipName + selected + ".tga");
	SetFormatedText("PAINT_CAPTION", XI_ConvertString("HullPaint") + " (" + selected + "/" + max + ")");
	
	int cost = GetHullTuningPrice(refCharacter, refNPCShipyard);
	if (CheckAttribute(&InterfaceStates, "Shipyard.FreePaint")) {
		cost = 0;
		SetFormatedText("PAINT_MONEY", XI_ConvertString("HullChoose"));
		SetNodeUsing("PAINT_OK2", true);
		SetNodeUsing("PAINT_OK", false);
		SetNodeUsing("PAINT_CANCEL", false);
	} else {
		SetFormatedText("PAINT_MONEY", XI_ConvertString("HullPaintCost") + cost);
		SetSelectable("PAINT_OK", (sti(pchar.money) >= cost) && (current != selected));
	} 
	
}

void ChangeHull(int delta) {
	ref realShip = GetRealShip(sti(refCharacter.ship.type));
	
	int max = GetShipHullCount(realShip);
	if (max < 2) return;
	
	InterfaceStates.Shipyard.SelectedHull = ((sti(InterfaceStates.Shipyard.SelectedHull) - 1 + max + delta) % max) + 1;
	
	SetShipPaintInfo(realShip.BaseName, sti(realShip.ship.upgrades.hull), sti(InterfaceStates.Shipyard.SelectedHull), max);
}

void SetNewHullToCharacterShip() {
	ref realShip = GetRealShip(sti(refCharacter.ship.type));
	if (!CheckAttribute(&InterfaceStates, "Shipyard.FreePaint")){
		int cost = GetHullTuningPrice(refCharacter, refNPCShipyard);
		AddMoneyToCharacter(pchar, -cost);
	}
	realShip.ship.upgrades.hull = sti(InterfaceStates.Shipyard.SelectedHull);
	
	ExitShipPaintMenu();
	
	int currentSlot = sti(GameInterface.SHIPS_SCROLL.current);
	RefreshShipLists();
	GameInterface.SHIPS_SCROLL.current = currentSlot;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
	DeleteAttribute(&InterfaceStates, "Shipyard.FreePaint");
}

//проверка доступных офицеров
bool bPassengersAccess() {
    int qty = GetPassengersQuantity(pchar);
    for(int i = 0; i < qty; i++) {
        int idx = GetPassenger(pchar, i);
        if (idx != -1) {
            bool ok = CheckAttribute(&characters[idx], "prisoned") && sti(characters[idx ].prisoned) == true;
            bool ob = CheckAttribute(&characters[idx], "CompanionDisable") && sti(characters[idx].CompanionDisable) == true;
            if (!ok && !ob && GetRemovable(&characters[idx])) return true;
        }
    } 
    return false;
}

void SetShipPerks(ref chr)
{
	string pictureGroup = "PERKS_SHIPS";
	string perkName1, perkName2;
	SetNodeUsing("SHIP_PERK1",false);
	SetNodeUsing("SHIP_PERK2",false);

	int iShip = sti(chr.ship.type);
	if(iShip != SHIP_NOTUSED) 
	{
		perkName1 = GetShipSpecDesc(chr);
		perkName2 = GetShipTraitDesc(chr);
		SetNewGroupPicture("SHIP_PERK1", pictureGroup, perkName1);
		SetNewGroupPicture("SHIP_PERK2", pictureGroup, perkName2);
		if(perkName1 != "") SetNodeUsing("SHIP_PERK1",true);
		if(perkName2 != "") SetNodeUsing("SHIP_PERK2",true);
	}
}
