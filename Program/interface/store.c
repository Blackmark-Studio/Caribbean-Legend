////    boal 31/03/06 STORE
string totalInfo = "";
int  TableSelect = 0;
int	nCurScrollNum = 0;
int iShipCapacity;
int iTotalSpace;
float fShipWeight, fStoreWeight;
int iMaxGoodsStore = 50000;
int sortedGoodIndex = 0;
int sortedRow = 0;

bool bShowChangeWin = true;
int  BuyOrSell = 0; // 1-buy -1 sell
string sChrId;
ref refStore, refCharacter, refShipChar;
int iShipQty, iStoreQty, iShipPrice, iStorePrice, iUnits;
float fWeight;
int  iCurGoodsIdx;
bool ok; // for if

void InitInterface_R(string iniName, ref pStore)
{
 	StartAboveForm(true);
	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetActorType(pchar);
	}
    refStore = pStore;
	refCharacter = pchar;
	SetQuestGoodsToStore(refStore); // установка квестовых товаров и цен
	if(CheckAttribute(pchar, "shiptrade.character"))
	{
		refShipChar = CharacterFromID(pchar.shiptrade.character);
	}
	//GameInterface.TABLE_LIST.hr.height = 36;
	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("In the hold");
	GameInterface.TABLE_LIST.hr.td1.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("WeightHold");
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Price buy");
	GameInterface.TABLE_LIST.hr.td3.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("Good name");
	GameInterface.TABLE_LIST.hr.td4.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("Price sell");
	GameInterface.TABLE_LIST.hr.td5.line_space_modifier = 0.8;
	if(refStore.Colony == "none")
	{
	    GameInterface.TABLE_LIST.hr.td6.str = XI_ConvertString("In the hold");
		GameInterface.TABLE_LIST.hr.td6.line_space_modifier = 0.8;
	}
	else
	{
		GameInterface.TABLE_LIST.hr.td7.str = XI_ConvertString("In the store");
		GameInterface.TABLE_LIST.hr.td7.line_space_modifier = 0.8;
	}
	GameInterface.TABLE_LIST.hr.td6.str = XI_ConvertString("WeightHold");
	GameInterface.TABLE_LIST.hr.td6.line_space_modifier = 0.8;

    FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"Money_1","",FONT_NORMAL,COLOR_MONEY, 550,215,SCRIPT_ALIGN_LEFT,  1.5);
	CreateString(true,"Money_2","",FONT_NORMAL,COLOR_MONEY, 1380,215,SCRIPT_ALIGN_RIGHT, 1.5);
		
	CreateString(true,"ShipName","",FONT_NORMAL,COLOR_MONEY, 960,250,SCRIPT_ALIGN_CENTER,1.5);

    SetShipWeight();
	SetDescription();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);

	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
	SetEventHandler("MouseRClickUP","EndTooltip",0);
	SetEventHandler("ShowHelpHint", "ShowHelpHint", 0);
	SetEventHandler("ShowInfoWindow", "ShowHelpHint", 0);
	SetEventHandler("HideInfoWindow", "HideInfoWindow", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);

	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);

	SetEventHandler("SellGoods", "SellGoods", 0);
	SetEventHandler("SellAll", "SellAll", 0);

	SetEventHandler("frame","ProcessFrame",1);

	if(refStore.Colony == "none")
	{
		SetFormatedText("STORECAPTION", XI_ConvertString("Ship") + ": '" + refShipChar.ship.name + "'");
	}
	else
	{
		SetFormatedText("STORECAPTION", XI_ConvertString("Colony" + refStore.Colony) + ":" + XI_ConvertString("titleStore"));
	}

 	if (refStore.Colony == "none")
	{
		SetNewPicture("OTHER_PICTURE", "interfaces\le\portraits\256\face_" + its(refShipChar.FaceId) + ".tga");
	}
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
	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetPlayerType(pchar);
	}
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");
	DelEventHandler("MouseRClickUP","EndTooltip");
	DelEventHandler("ShowHelpHint", "ShowHelpHint");
	DelEventHandler("ShowInfoWindow", "ShowHelpHint");
	DelEventHandler("HideInfoWindow", "HideInfoWindow");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	DelEventHandler("SellGoods", "SellGoods");
	DelEventHandler("SellAll", "SellAll");

	//DelEventHandler("RefreshTable","RefreshTable");
    // boal 27.02.05 -->
    if (CheckAttribute(pchar, "PriceList.StoreManIdx"))
    {
    	SetPriceListByStoreMan(&Colonies[sti(pchar.PriceList.StoreManIdx)]);
    	DeleteAttribute(pchar, "PriceList.StoreManIdx");
    }
    // boal 27.02.05 <--

	if(refStore.Colony == "none") Partition_GetCargoCostCoeff("before"); // Эти товары были получены в море честно

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "QTY_BUYSELL_BUTTON":
			if(comName=="leftstep")
			{
	            AddOrRemove(1);	//ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            AddOrRemove(-1);	//REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
			if(comName == "ctrlleft")
				AddOrRemove(10);
			if(comName == "ctrlright")
				AddOrRemove(-10);
		break;

		case "TABLE_LIST":
			if(comName=="leftstep")
			{
	            AddOrRemove(1);	//ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            AddOrRemove(-1);	//REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
			if(comName == "ctrlleft")
				AddOrRemove(10);
			if(comName == "ctrlright")
				AddOrRemove(-10);
		break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
    AddToTable();
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
	int n, i, iPrice;
	string row, sShipGroup;
	ref rShip;
	string sGood;
	string sBuy, sSell, sShipQ, sStoreQ, sStoreWeight;
	int tradeType, iColor;
	aref refGoods;
	n = 1;
	Table_Clear("TABLE_LIST", false, true, false);
    for (i = 0; i< GetArraySize(&Goods); i++)
	{
        row = "tr" + n;
		sGood = Goods[i].name;
		makearef(refGoods,refStore.Goods.(sGood));
        tradeType = MakeInt(refGoods.TradeType);
        if (tradeType == T_TYPE_CANNONS) continue; // не пушки
        
		sShipQ = GetCargoGoods(refCharacter, i);

		if(refStore.Colony != "none")
		{
			sStoreQ = GetStoreGoodsQuantity(refStore, i);
		}
		else
		{
			sStoreQ = GetCargoGoods(refShipChar, i);
		}

		if(sti(sStoreQ) < 0)
		{
			sStoreQ = 0;
			refGoods.quantity = 0;
		}
		if (sStoreQ == 0 && sShipQ == 0) continue; // только не нули

		GameInterface.TABLE_LIST.(row).td1.str = sShipQ;
		GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, sti(sShipQ));
		GameInterface.TABLE_LIST.(row).td6.str = GetGoodWeightByType(i, sti(sStoreQ));
		GameInterface.TABLE_LIST.(row).td7.str = sStoreQ;

		switch(tradeType)
		{
			case T_TYPE_NORMAL:
				iColor = ARGB_Color("white");
			break;
			case T_TYPE_EXPORT:
				iColor = argb(255,196,255,196);
			break;
			case T_TYPE_IMPORT:
				iColor = argb(255,196,196,255);
			break;
			case T_TYPE_AGGRESSIVE:	
				iColor = argb(255,255,196,98);
			break;
			case T_TYPE_CONTRABAND:
				iColor = argb(255,255,196,196);
			break;
			case T_TYPE_AMMUNITION:
			    if (refStore.Colony == "none")
				{
					iColor = ARGB_Color("offGrey");
				}
				else
				{
					iColor = ARGB_Color("white");
				}
			break;
		}
		if(checkAttribute(refCharacter, "ship.cargo.goods." + sGood + ".isquest"))
		{
			iColor = argb(255,255,192,255);
		}

        GameInterface.TABLE_LIST.(row).td4.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td4.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td4.icon.offset = "0, 0";
		GameInterface.TABLE_LIST.(row).td4.icon.width = 40;
		GameInterface.TABLE_LIST.(row).td4.icon.height = 40;
		GameInterface.TABLE_LIST.(row).td4.textoffset = "30,0";
		GameInterface.TABLE_LIST.(row).td4.str = XI_ConvertString(sGood);
		GameInterface.TABLE_LIST.(row).index = i;
		GameInterface.TABLE_LIST.(row).td4.color = iColor;

        // Продаёт магазин (PRICE_TYPE_BUY)
		if ((tradeType == T_TYPE_AMMUNITION) && (refStore.Colony == "none"))
		    GameInterface.TABLE_LIST.(row).td3.str = "-"; // нельзя купить в море
		else
			GameInterface.TABLE_LIST.(row).td3.str = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY, pchar, 1);

        // Продаёт игрок (PRICE_TYPE_SELL)
		if (tradeType == T_TYPE_CONTRABAND)
			GameInterface.TABLE_LIST.(row).td5.str = "-";
		else
		{
            iPrice = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);
            // В море продавать невыгодно
			if (refStore.Colony == "none")
			{
			    iPrice /= 2;
			    if (iPrice < 1) iPrice = 1;
			}
            GameInterface.TABLE_LIST.(row).td5.str = iPrice;
		}

		n++;
	}
	RestoreTableSorting("TABLE_LIST");
	if (sortedGoodIndex != 0) ShowGoodsInfo(sortedGoodIndex);
	RestoreAllSelectionsAfterSort("TABLE_LIST", sortedGoodIndex, sortedRow);
	NextFrameRefreshTable();
}

void NextFrameRefreshTable()
{
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
    Table_UpdateWindow(sControl);
	XI_WindowDisable("QTY_WINDOW",false);
	XI_WindowShow("QTY_WINDOW", true);
	bShowChangeWin = true;
	SetNodeUsing("QTY_BUYSELL_BUTTON", false);	
}

void ChangePosTable()
{
}

void ShowHelpHint()
{
	string sCurrentNode = GetEventData();
    string sHeader;
	string sText1, sText2, sText3, sText4, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	sHeader = XI_ConvertString("GoodsColor_Descr");

	sText1 = XI_ConvertString("GoodsColor1") + NewStr() +
			 XI_ConvertString("GoodsColor2") + NewStr() +
			 XI_ConvertString("GoodsColor3") + NewStr() +
			 XI_ConvertString("GoodsColor4");
	// sText2 = XI_ConvertString("GoodsColor2");
	// sText3 = XI_ConvertString("GoodsColor3");
	// sText4 = XI_ConvertString("GoodsColor4");
		
	CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, sText4, sPicture, sGroup, sGroupPicture, 64, 64, false);
}

void HideInfoWindow()
{
	CloseTooltipNew();
}

void EndTooltip()
{
	CloseTooltipNew(); // всегда убирать, если был
    GameInterface.qty_edit.str = 0;
	SetShipWeight();
	SetVariable();
	SetCurrentNode("TABLE_LIST");
 	XI_WindowDisable("QTY_WINDOW", false);
	XI_WindowShow("QTY_WINDOW", true);
	bShowChangeWin = true;
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "");	
 	SetNodeUsing("QTY_BUYSELL_BUTTON", false);
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

void ShowItemInfo()
{
	if (bShowChangeWin) // жмем окей, когда курсор на таблице
	{
	    TransactionOK();
	}
	else
	{
		GameInterface.qty_edit.str = "0";
		BuyOrSell = 0;
		ChangeQTY_EDIT();

		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		bShowChangeWin = true;
		if (GetRemovable(refCharacter))
		{
			SetSelectable("QTY_BUYSELL_BUTTON",true);
		}
		else
		{
			SetSelectable("QTY_BUYSELL_BUTTON",false);
		}
	}
}

void RefreshTable()
{
    PostEvent("RefreshTable", 100);
    if (TableSelect != sti(GameInterface.TABLE_LIST.select))
    {
        TableSelect = sti(GameInterface.TABLE_LIST.select);
        ChangePosTable();
    }
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    TableSelect = iSelected;
    string sRow = "tr" + (iSelected);
	SetShipWeight();
	SetVariable();
	sortedGoodIndex = sti(GameInterface.TABLE_LIST.(sRow).index);
	ShowGoodsInfo(sortedGoodIndex);
}

void FillShipsScroll()
{
	nCurScrollNum = -1;
	FillScrollImageWithCompanionShips("SHIPS_SCROLL", COMPANION_MAX);

	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}
}

void SetVariable()
{
	string sText, sTextSecond;

	int nShipType = sti(refCharacter.ship.type);
	ref refBaseShip = GetRealShip(nShipType);

	iShipCapacity = sti(refBaseShip.Capacity);
	sText  = iShipCapacity;

	sText  = makeint(fShipWeight) + " / " + sText;
	sText = sText;
	SetFormatedText("CAPACITY", sText);

	iTotalSpace = iMaxGoodsStore;
	string sStoreName, sMaxGoodsStore;
	if(refStore.Colony == "none")
	{
		iTotalSpace = sti(RealShips[sti(refShipChar.ship.type)].capacity);
		sStoreName = GetFullName(refShipChar);
		sMaxGoodsStore = makeint(fStoreWeight) + " / " + iTotalSpace;
	}
	else
	{
	    sStoreName = XI_ConvertString("store");
		sMaxGoodsStore = "";
	}
	SetFormatedText("STORE_NAME", sStoreName);
	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);
	
	if(refStore.Colony == "none")
	{
		sText = MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER);
		GameInterface.strings.Money_1 = sText;
		sText = MakeMoneyShow(sti(refShipChar.Money), MONEY_SIGN,MONEY_DELIVER);
		GameInterface.strings.Money_2 = sText;
		SetFormatedText("CHARACTER_NAME", GetFullName(refCharacter));
		SetNodeUsing("WEIGHTMONEY2", true);
	}
	else
	{
		sText = MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER);		
		SetFormatedText("OUR_GOLD", sText);
		SetFormatedText("CHARACTER_NAME", GetFullName(refCharacter));
		SetNodeUsing("WEIGHTMONEY2", false);
	}

	if (CheckAttribute(refCharacter, "ship.name"))
	{
		GameInterface.strings.shipname = refCharacter.ship.name;
	}
	else
	{
	    GameInterface.strings.shipname = "";
	}
}

void ProcessFrame()
{
	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		if(sti(GameInterface.SHIPS_SCROLL.current)!=nCurScrollNum)
		{
            XI_WindowDisable("QTY_WINDOW", false);
			XI_WindowShow("QTY_WINDOW", true);
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			SetDescription();
   			GameInterface.TABLE_LIST.select = 1;
			GameInterface.TABLE_LIST.top = 0;
			SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST",0);
		}
	}
}

void SetDescription()
{
 	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		string attributeName = attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "SHIPS_SCROLL." + attributeName))
		{
			int iCharacter = GameInterface.SHIPS_SCROLL.(attributeName).companionIndex;
			sChrId = characters[iCharacter].id;
			refCharacter = characterFromID(sChrId);
			SetShipWeight();
		}
	}
    CalculateInfoData();
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\le\portraits\256\face_" + its(refCharacter.FaceId) + ".tga");
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

    if(refStore.Colony == "none")
	{
		fStoreWeight = makeint(GetCargoLoad(refShipChar)+ 0.4);
	}
	else
	{
	    fStoreWeight = 0;
	}
}
void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;

	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
    string goodsDescr = "";
    if (bBettaTestMode)
	{
		goodsDescr += NewStr() + "BaseNorm " + goods[iGoodIndex].Norm + " BaseCost " + goods[iGoodIndex].Cost + " StoreNorm " + refStore.Goods.(GoodName).Norm;
		goodsDescr += NewStr() + "NormPrMod " + FloatToString(stf(refStore.Goods.(GoodName).NormPriceModify), 4) + " CurPrMod " +
		                         FloatToString(stf(refStore.Goods.(GoodName).RndPriceModify), 4) + " Delta " +
								 FloatToString(stf(stf(refStore.Goods.(GoodName).Quantity) / stf(refStore.Goods.(GoodName).Norm)), 3);
		goodsDescr += NewStr();
	}
	goodsDescr += GetAssembledString( GetGoodDescr(&Goods[iGoodIndex]), &Goods[iGoodIndex]);
    goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
	              ", " + XI_ConvertString("PackHold") + " "  + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits  = sti(Goods[iGoodIndex].Units);
	fWeight = stf(Goods[iGoodIndex].weight);
	if(checkAttribute(pchar, "ship.cargo.goods." + GoodName + ".isquest"))
	{
		string sTradeQ = pchar.ship.cargo.goods.(GoodName).isquest.quantity;
		string sColony = pchar.ship.cargo.goods.(GoodName).isquest.colony;
		goodsDescr += NewStr() + XI_ConvertString("YouNeedToDelivery") + sTradeQ + XI_ConvertString("QuantityOfGoodsToColony") + XI_ConvertString("Colony"+sColony) + ".";
	}

    BuyOrSell = 0;
    SetFormatedText("QTY_TypeOperation", "");
    SetFormatedText("QTY_Result", "");
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "");	
 	SetNodeUsing("QTY_BUYSELL_BUTTON", false);
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);	
	SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", goodsDescr);

	iShipQty = GetCargoGoods(refCharacter, iGoodIndex);

	if(refStore.Colony != "none")
	{
		iStoreQty = GetStoreGoodsQuantity(refStore, iGoodIndex);
	}
	else
	{
		iStoreQty = GetCargoGoods(refShipChar, iGoodIndex);
	}

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty));
	BuyOrSell = 0;

    // Продаёт игрок (PRICE_TYPE_SELL)
	if (MakeInt(refStore.Goods.(GoodName).TradeType) == T_TYPE_CONTRABAND)
	{
	    iStorePrice = 0;
	    SetFormatedText("QTY_INFO_STORE_PRICE", XI_ConvertString("Price sell") + NewStr() + "-");
	}
	else
	{
		iStorePrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_SELL, pchar, 1);
		// В море продавать невыгодно
	 	if(refStore.Colony == "none")
		{
		    iStorePrice /= 2;
		    if (iStorePrice < 1) iStorePrice = 1;
		}
        SetFormatedText("QTY_INFO_STORE_PRICE", XI_ConvertString("Price sell") + NewStr() + its(iStorePrice));
	}

    // Продаёт магазин (PRICE_TYPE_BUY)
	if ((MakeInt(refStore.Goods.(GoodName).TradeType) == T_TYPE_AMMUNITION) && (refStore.Colony == "none"))
	{
	    iShipPrice = 0;
	    SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price buy") + NewStr() + "-");
	}
	else
	{
		iShipPrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_BUY, pchar, 1);
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price buy") + NewStr() + its(iShipPrice));
	}

	ShowFoodInfo();
}

void ShowFoodInfo()
{
	if(iCurGoodsIdx == GOOD_FOOD)
	{
		// чтоб прикинуть как оно будет, скинем на время колво на продажное
		SetCharacterGoods(refCharacter, GOOD_FOOD, iShipQty + BuyOrSell*sti(GameInterface.qty_edit.str));
		SetFoodShipInfo(refCharacter, "FOOD_SHIP");
		SetCharacterGoods(refCharacter, GOOD_FOOD, iShipQty);
	}
	else
	{
		if(iCurGoodsIdx == GOOD_RUM) // Warship 11.07.09 На сколько хватит рому
		{
			// чтоб прикинуть как оно будет, скинем на время колво на продажное
			SetCharacterGoods(refCharacter, GOOD_RUM, iShipQty + BuyOrSell*sti(GameInterface.qty_edit.str));
			SetRumShipInfo(refCharacter, "FOOD_SHIP");
			SetCharacterGoods(refCharacter, GOOD_RUM, iShipQty);
		}
		else
		{
			SetFormatedText("FOOD_SHIP", "");
		}
	}
}
void TransactionOK()
{
	int nTradeQuantity, moneyback;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if (BuyOrSell == 0)
	{
	    EndTooltip();
	    return;
	}
    if (!GetRemovable(refCharacter)) return;
    
 	if (BuyOrSell == 1) // BUY
	{
        if(refStore.Colony != "none")
		{
   			SetStoreGoods(refStore, iCurGoodsIdx, iStoreQty - nTradeQuantity);
		}
		else
		{
   			RemoveCharacterGoods(refShipChar, iCurGoodsIdx, nTradeQuantity);
		}

		AddCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iShipPrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5);
		pchar.money = sti(pchar.money)  - moneyback;		
		if(refStore.Colony == "none" && CheckAttribute(refShipChar,"money"))
		{			
			refShipChar.money = sti(refShipChar.money) + moneyback;			
		}		
		Statistic_AddValue(Pchar, "Money_spend", moneyback);
		// boal  check skill -->
        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 800.0);
    	WaitDate("",0,0,0, 0, 15);
        // boal <--
	}
 	else
	{ // SELL
        if(refStore.Colony != "none")
		{
      		SetStoreGoods(refStore, iCurGoodsIdx, iStoreQty + nTradeQuantity);
		}
		else
		{
   			AddCharacterGoods(refShipChar, iCurGoodsIdx, nTradeQuantity);
		}

		RemoveCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iStorePrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5);
  		pchar.money = sti(pchar.money)  + moneyback;
		if(refStore.Colony == "none" && CheckAttribute(refShipChar,"money"))
		{			
			refShipChar.money = sti(refShipChar.money) - moneyback;			
		}
		else if(HasShipTrait(pchar, "trait03") && moneyback >= 50000)
		{
			ref rColony = GetColonyRefByID(refStore.Colony);
			ChangeCharacterNationReputation(pchar, sti(rColony.nation), moneyback/50000);
		}
		Statistic_AddValue(Pchar, "Money_get", moneyback);
		Achievment_SetStat(39, moneyback);
		if(iCurGoodsIdx == GOOD_SLAVES) Achievment_SetStat(43, nTradeQuantity);
		// boal  check skill -->
        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 1600.0);
    	WaitDate("",0,0,0, 0, 15);
        // boal <--
	}
	AddToTable();
	EndTooltip();
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_BUYSELL_BUTTON");
}

void ChangeQTY_EDIT()
{
	int  iWeight;
	SetShipWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	
	string GoodName = goods[iCurGoodsIdx].name;
	
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
		SetNodeUsing("QTY_BUYSELL_BUTTON", false);
		SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "");
	    BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)
		{
			if (BuyOrSell != -1)
			{
		    	GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
		    }
            BuyOrSell = -1;
            if (MakeInt(refStore.Goods.(GoodName).TradeType) == T_TYPE_CONTRABAND)
            {  // контрабанду нельзя продать
                GameInterface.qty_edit.str = 0;
            }
		    // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iShipQty)
		    {
		        GameInterface.qty_edit.str = iShipQty;
		    }
		    iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		    if ((fStoreWeight + iWeight) > iTotalSpace)
		    {
		        iWeight = iTotalSpace - fStoreWeight - fWeight;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits );
		        iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits ); // округдение
		    }
			if(refStore.Colony == "none" && CheckAttribute(refShipChar,"money"))
			{			
				if (makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(refShipChar.money))
				{
					GameInterface.qty_edit.str = makeint(sti(refShipChar.money) / iStorePrice);
					iWeight = fWeight * sti(GameInterface.qty_edit.str);
				}			
			}	
		    // проверка на колво доступное <--
		    SetFormatedText("QTY_TypeOperation", XI_ConvertString("SELL"));
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "SELL");
			SetNodeUsing("QTY_BUYSELL_BUTTON", true);
		    SetFormatedText("QTY_Result", XI_ConvertString("Money") + " " + makeint(iStorePrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5) +
			                ", " + XI_ConvertString("weight") + " " + iWeight + " " + XI_ConvertString("cwt"));
		}
		else
		{
            // не нужно у кэпов в море пукупать порох и ядра, а то потом они беззащитны
			if ((MakeInt(refStore.Goods.(GoodName).TradeType) == T_TYPE_AMMUNITION) && (refStore.Colony == "none"))
            {
                GameInterface.qty_edit.str = 0;
            }
			BuyOrSell = 1;
         	// проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
		    iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		    if ((fShipWeight + iWeight) > iShipCapacity)
		    {
		        iWeight = iShipCapacity - fShipWeight - fWeight;
				if (iWeight < 0) iWeight = 0;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits );
		        iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits ); // округление
		    }
		    if (makeint(iShipPrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5) > sti(pchar.money))
		    {
		        GameInterface.qty_edit.str = makeint(sti(pchar.money)*iUnits / iShipPrice);
		        iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		    }
		    // проверка на колво доступное <--
			SetFormatedText("QTY_TypeOperation", XI_ConvertString("BUY"));
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "BUY");
			SetNodeUsing("QTY_BUYSELL_BUTTON", true);
			SetFormatedText("QTY_Result", XI_ConvertString("Money") + " " + makeint(iShipPrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5) +
			                ", " + XI_ConvertString("weight") + " " + iWeight + " " + XI_ConvertString("cwt"));
		}
	}
	// если получили ноль Jason: или особо хитрожопые ввели минус
	if (sti(GameInterface.qty_edit.str) <= 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
		SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "");
		SetNodeUsing("QTY_BUYSELL_BUTTON", false);
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetShipWeight();
    fShipWeight  = fShipWeight  + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
    SetVariable();
    ShowFoodInfo();
}

void REMOVE_ALL_BUTTON()  // продать все
{
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iShipQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
	if(XI_IsKeyPressed("shift"))
		REMOVE_ALL_BUTTON();
	int n = -1;
	if(XI_IsKeyPressed("control"))
		n = -10;
	AddOrRemove(n);
}

void ADD_BUTTON()  // купить
{
	if(XI_IsKeyPressed("shift"))
		ADD_ALL_BUTTON();
	int n = 1;
	if(XI_IsKeyPressed("control"))
		n = 10;
	AddOrRemove(n);
}

void AddOrRemove(int n)	// > 0 - Add, < 0 - Remove
{
	if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
        GameInterface.qty_edit.str = n * iUnits;
    else
    {
  		if (BuyOrSell == 1)
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + n * iUnits);
		else
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - n * iUnits);
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void OnHeaderClick()
{
	string sControl = GetEventData();
	int iColumn = GetEventData();
	// trace("sControl: " + sControl  + " iColumn "  + iColumn);

	if (sControl == "TABLE_LIST") SortStoreGoods(iColumn, false, sControl);
}

void SortStoreGoods(int column, bool preserveState, string tableName)
{
  string datatype = "integer";
	switch (column)
	{
		case 4: datatype = "index"; break; 
	}
	
  QoLSortTable(tableName, column, datatype, preserveState, 0);
}

void SellGoods()
{
	BulkSale(false);
}

void SellAll()
{
	BulkSale(true);
}

// Продать всё в магазине
void BulkSale(bool isSellAll)
{
  if (!GetRemovable(&refCharacter)) return; // не можем продавать с корабля

	int i, tradeType;
	int resultSumm = 0;
	aref refGoods;
	int tradeSumm, storeCargoQty, shipCargoQty, goodPrice;

	for (i=0; i < GetArraySize(&Goods); i++)
	{
		string sGood = Goods[i].name;
		makearef(refGoods, refStore.Goods.(sGood));
		tradeType = sti(refGoods.TradeType);
		if (tradeType == T_TYPE_CANNONS) continue;                             // не пушки
		if (tradeType == T_TYPE_CONTRABAND) continue;                          // не контрабанда

		// не продаём патроны, ром и медицину
		if (!isSellAll)
		{
			if (sti(refGoods.Type) == T_TYPE_AMMUNITION) continue;
			if (i == GOOD_RUM) continue;
			if (i == GOOD_WEAPON) continue;
			if (i == GOOD_POWDER) continue;
			if (i == GOOD_FOOD) continue;
			if (i == GOOD_MEDICAMENT) continue;
			if (i == GOOD_SAILCLOTH) continue;
			if (i == GOOD_PLANKS) continue;
		}

		shipCargoQty = GetCargoGoods(&refCharacter, i);
		if (shipCargoQty <= 0) continue;                                          // нет товара на корабле

		goodPrice = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);
		tradeSumm = makeint(makefloat(goodPrice*shipCargoQty) / sti(Goods[i].Units) + 0.5);
		storeCargoQty = GetStoreGoodsQuantity(refStore, i);

		if (i == GOOD_SLAVES) Achievment_SetStat(43, shipCargoQty);
		SetStoreGoods(refStore, i, storeCargoQty + shipCargoQty);
		RemoveCharacterGoods(refCharacter, i, shipCargoQty);
		resultSumm += tradeSumm;
	}

	pchar.money = sti(pchar.money) + resultSumm;
	Statistic_AddValue(Pchar, "Money_get", resultSumm);
	Achievment_SetStat(39, resultSumm);
	AddCharacterExpToSkill(pchar, "Commerce", resultSumm / 1600.0);
	WaitDate("",0,0,0,0,15);

	AddToTable();
	EndTooltip();
}
