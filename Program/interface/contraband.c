////    контрабанда
string 	totalInfo = "";
int  	TableSelect = 0;
int		nCurScrollNum = 0;
int 	iShipCapacity;
int 	iTotalSpace;
float 	fShipWeight, fStoreWeight;
int 	iMaxGoodsStore = 50000;

bool 	bShowChangeWin = true;
int  	BuyOrSell = 0; // 1-buy -1 sell
string 	sChrId;
ref 	refStore, refCharacter, refShipChar, refContraChar;
int 	iShipQty, iStoreQty, iShipPrice, iStorePrice, iUnits;
float 	fWeight;
int  	iCurGoodsIdx;
bool 	ok; // for if

void InitInterface_RR(string iniName, ref ContraTrader , ref pStore)
{
 	StartAboveForm(true);

    refStore 		= pStore;
	refCharacter 	= pchar;
	refContraChar	= ContraTrader;

	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("In the hold");
	GameInterface.TABLE_LIST.hr.td1.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("WeightHold");
	GameInterface.TABLE_LIST.hr.td2.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.TABLE_LIST.hr.td3.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("Good name");
	GameInterface.TABLE_LIST.hr.td4.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("Price buy");
	GameInterface.TABLE_LIST.hr.td5.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td6.str = XI_ConvertString("In the contra");
	GameInterface.TABLE_LIST.hr.td6.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td7.str = XI_ConvertString("PackHold");
	GameInterface.TABLE_LIST.hr.td7.line_space_modifier = 0.8;
	GameInterface.TABLE_LIST.hr.td8.str = XI_ConvertString("PackWeightHold");
	GameInterface.TABLE_LIST.hr.td8.line_space_modifier = 0.8;

    FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

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
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);

	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);

	SetEventHandler("frame","ProcessFrame",1);

	SetFormatedText("STORECAPTION", XI_ConvertString("Colony" + refStore.Colony) + ": " + XI_ConvertString("titleContraband"));
	SetNodeUsing("QTY_BUYSELL_BUTTON", false);
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_CONTRATRADE );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_CONTRATRADE );
}

void IDoExit(int exitCode)
{
	if(GetSummonSkillFromName(GetMainCharacter(), "Sneak") * GetFloatByCondition(HasShipTrait(pchar, "trait05"), 1.0, 1.5) < Rand(120) && !CheckAttribute(pchar, "questTemp.BlockContrabandPatrol"))
	{
		DoQuestCheckDelay("Rand_ContrabandInterruption", 0.1);
		for (int i=1; i<=3; i++)
		{
			characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
		}
	}
	AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 100);
	
	if (sti(Pchar.quest.Contraband.Counter) > 0) Achievment_SetStat(31, 1);
					
	ChangeContrabandRelation(GetMainCharacter(), 15);
    OfficersReaction("bad");
    ChangeCharacterComplexReputation(GetMainCharacter(), "nobility", -1);
            
    CloseQuestHeader("Gen_Contraband");
            
	DeleteAttribute(Pchar, "quest.Contraband.active");
	DeleteAttribute(Pchar, "quest.Contraband.counter");
	
	Pchar.quest.Rand_Smuggling.over = "yes";
	RemoveSmugglersFromShore();
	RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));

    EndAboveForm(true);

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");
	DelEventHandler("MouseRClickUP","EndTooltip");
	DelEventHandler("ShowHelpHint", "ShowHelpHint");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");

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

		case "TABLE_LIST":
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

void CalculateInfoData()
{
    AddToTable();
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
	int n, i;
	string row, sShipGroup;
	ref rShip;
	string sGood;
	string sBuy, sSell, sShipQ, sStoreQ, sStoreWeight;
	int iColor;
	aref refGoods;
	n = 1;
	Table_Clear("TABLE_LIST", false, true, false);

    for (i = 0; i< GOODS_QUANTITY; i++)
	{
        row = "tr" + n;
		sGood = Goods[i].name;
		
		if(GetContrabandGoods(refStore, i) == 0) continue;
		
		makearef(refGoods,refContraChar.Goods.(sGood));
		    
		sShipQ 		= GetCargoGoods(refCharacter, i);
		sStoreQ 	= GetContraGoodsQuantity(refContraChar, i);

		if(sti(sStoreQ) < 0)
		{
			sStoreQ = 0; refGoods.quantity = 0;
		}
		if (sStoreQ == 0 && sShipQ == 0) continue; // только не нули

		GameInterface.TABLE_LIST.(row).td1.str = sShipQ;
		GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, sti(sShipQ));
		GameInterface.TABLE_LIST.(row).td7.str = Goods[i].Units;
		GameInterface.TABLE_LIST.(row).td8.str = Goods[i].Weight;

		GameInterface.TABLE_LIST.(row).td6.str = sStoreQ;
		iColor = argb(255,255,255,255);
		if(GetContrabandGoods(refStore, i) == 1)
		{
			iColor = argb(255,196,196,255);
		}
		else
		{
			iColor = argb(255,196,255,196);
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

		GameInterface.TABLE_LIST.(row).td5.str = GetContrabandGoodsPrice(refStore, i, PRICE_TYPE_BUY, pchar, 1);
		GameInterface.TABLE_LIST.(row).td3.str = GetContrabandGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);
		n++;
	}
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
	int iRow		= GetEventData();
	int iColumn 	= GetEventData();

	string sRow = "tr" + (iRow + 1);
    Table_UpdateWindow(sControl);
	XI_WindowDisable("QTY_WINDOW",false);
	XI_WindowShow("QTY_WINDOW", true);
	bShowChangeWin = true;
	SetNodeUsing("QTY_BUYSELL_BUTTON", false);
}

void OnHeaderClick()
{
	string sNode = GetEventData();
	int iCol = GetEventData();
}

void ChangePosTable()
{
}

void ShowHelpHint()
{

}

void EndTooltip()
{
	CloseTooltip(); // всегда убирать, если был
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
    ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sRow).index));
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

	int nShipType = sti(refCharacter.ship.type);
	ref refBaseShip = GetRealShip(nShipType);

	iShipCapacity = sti(refBaseShip.Capacity);
	sText  = iShipCapacity;

	sText  = makeint(fShipWeight) + " / " + sText;
	sText = sText;
	SetFormatedText("CAPACITY", sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;

	sMaxGoodsStore = XI_ConvertString("contraband");

	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);

	sText = MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER);
	SetFormatedText("OUR_GOLD", sText);
	SetFormatedText("CHARACTER_NAME", GetFullName(refCharacter));

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
    fStoreWeight = 0;	
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;

	int lngFileID = LanguageOpenFile("GoodsDescribe.txt");
	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
    string goodsDescr = "";
    if (bBettaTestMode)
	{
		goodsDescr += NewStr() + "BaseNorm " + goods[iGoodIndex].Norm + " BaseCost " + goods[iGoodIndex].Cost + " StoreNorm " + refStore.Goods.(GoodName).Norm;
		goodsDescr += NewStr() + "NormPrMod " + FloatToString(stf(refStore.Goods.(GoodName).NormPriceModify), 4) + " CurPrMod " +
		                        FloatToString(stf(refStore.Goods.(GoodName).RndPriceModify), 4); 
		goodsDescr += NewStr();
	}
	goodsDescr += GetAssembledString( LanguageConvertString(lngFileID,goodName+"_descr"), &Goods[iGoodIndex]);
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
	LanguageCloseFile(lngFileID);

	iShipQty = GetCargoGoods(refCharacter, iGoodIndex);
	iStoreQty = GetContraGoodsQuantity(refContraChar, iGoodIndex);
	
	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty));
	BuyOrSell = 0;
	
	iStorePrice = GetContrabandGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_SELL, pchar, 1);
    SetFormatedText("QTY_INFO_STORE_PRICE",XI_ConvertString("Price sell") + NewStr() + its(iStorePrice));

	iShipPrice = GetContrabandGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_BUY, pchar, 1);
	SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price buy") + NewStr() + its(iShipPrice));
	
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
		SetContraGoods(refContraChar, iCurGoodsIdx, iStoreQty - nTradeQuantity);
		AddCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iShipPrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5);
		pchar.money = sti(pchar.money)  - moneyback;
		Statistic_AddValue(Pchar, "Money_spend", moneyback);
        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 800.0);
    	WaitDate("",0,0,0, 0, 15);
		Pchar.quest.Contraband.Counter = 1;
	}
 	else
	{ // SELL
        SetContraGoods(refContraChar, iCurGoodsIdx, iStoreQty + nTradeQuantity);
		RemoveCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iStorePrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5);
  		pchar.money = sti(pchar.money)  + moneyback;
		Statistic_AddValue(Pchar, "Money_get", moneyback);
		Achievment_SetStat(39, moneyback);
        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 1600.0);
		
		if(iCurGoodsIdx == GOOD_SLAVES) Achievment_SetStat(43, nTradeQuantity);
		
    	WaitDate("",0,0,0, 0, 15);
		Pchar.quest.Contraband.Counter = 1;
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
		    // проверка на колво доступное <--
		    SetFormatedText("QTY_TypeOperation", XI_ConvertString("SELL"));
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "SELL");
			SetNodeUsing("QTY_BUYSELL_BUTTON", true);
		    SetFormatedText("QTY_Result", XI_ConvertString("Money") + " " + makeint(iStorePrice*stf(GameInterface.qty_edit.str) / iUnits + 0.5) +
			                ", " + XI_ConvertString("weight") + " " + iWeight + " " + XI_ConvertString("cwt"));
		}
		else
		{
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

			// SetFormatedText("QTY_TypeOperation", "Купить");
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
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = -iUnits;
    }
    else
    {
		if (BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + iUnits);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - iUnits);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
    if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = iUnits;
    }
    else
    {
  		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + iUnits);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - iUnits);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}