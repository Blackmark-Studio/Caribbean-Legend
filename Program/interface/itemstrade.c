// boal 26/04/06 форма торговли предметами
// Sith переделка меню
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по вкладкам на TAB
int	nCurScrollNum = 0;
int iCharCapacity;
int iTotalSpace;
float fCharWeight, fStoreWeight;
int iMaxGoodsStore = 50000;
string CurTable, CurRow;
int  TradeMode; // 0 - песо, 1 - дублоны
int  BuyOrSell = 0; // 1-buy -1 sell
string sChrId;
ref refCharacter, refStoreChar; // текущий ГГ (оф) и торгаш
int iCharQty, iStoreQty, iCharPrice, iStorePrice;
float fWeight;
int  iCurGoodsIdx;
int currentTab = 0;
int selectedRow = 0;
//----------------------------------------------------------------------------------------------------------------
void InitInterface_RI(string iniName, ref pTrader, int mode)
{
    StartAboveForm(true);
	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetActorType(pchar);
	}
	refCharacter = pchar;
	refStoreChar = pTrader;
	TradeMode = mode;

	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("ItemsName");
	GameInterface.TABLE_LIST.hr.td1.textoffset = "50,0";
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("ItemsQty");
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Weight");
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("Cost");
	
	GameInterface.TABLE_LIST2.hr.td1.str = XI_ConvertString("ItemsName");
	GameInterface.TABLE_LIST2.hr.td1.textoffset = "50,0";
	GameInterface.TABLE_LIST2.hr.td2.str = XI_ConvertString("ItemsQty");
	GameInterface.TABLE_LIST2.hr.td3.str = XI_ConvertString("Weight");
	GameInterface.TABLE_LIST2.hr.td4.str = XI_ConvertString("Cost");	


	FillCharactersScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetCharWeight();

	SetDescription();
	FillCharacterInfo();
	
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
	SetEventHandler("eTabControlPress", "procTabChange",0);	
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);

	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);

	SetEventHandler("frame","ProcessFrame",1);

	SetFormatedText("STORECAPTION", XI_ConvertString("titleItemsTrade"));

	SetNewPicture("OTHER_PICTURE", "interfaces\le\portraits\256\face_" + its(refStoreChar.FaceId) + ".tga");
	SetNodeUsing("QTY_BUYSELL_BUTTON", false);
	SetControlsTabModeManual(1); // ставим дефолтную вкладку все
}

// метод на TAB переключает вкладки таблицы
void ProcessInterfaceControls() 
{
    string controlName = GetEventData();
	if (controlName == "InterfaceTabSwitch") {
		currentTab = currentTab % 5;
		SetControlsTabMode(currentTab + 1);
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
    // boal проверка на перегруз 21.01.2004 -->
	CheckAndSetOverloadMode(GetMainCharacter());
	RefreshEquippedMaps(GetMainCharacter()); // рефрешим карты, если купили	
	// boal 21.01.2004 <--
	// раздайте патроны, порутчик Голицын -->
	int i, cn;
    for(i=1;i<4;i++)
	{
		cn = GetOfficersIndex(pchar, i);
		if (cn!=-1)
		{
			refCharacter = GetCharacter(cn);
            CheckAndSetOverloadMode(refCharacter);
			if (CheckAttribute(refCharacter, "skill.FencingS")) //boal fix иначе не берут саблю при перегрузе
			{
	            EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,BLADE_ITEM_TYPE));
	            EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,CIRASS_ITEM_TYPE)); // boal 08.10.04 броню офицерам
	        }
			if (CheckAttribute(refCharacter, "skill.Pistol") && GetCharacterSkill(refCharacter,"Pistol") > 0.1 )
			{
				EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,GUN_ITEM_TYPE));
			}
		}
	}
	// раздайте патроны, порутчик Голицын <--
	
	//CheckTraderItems(refStoreChar);
	
	EndAboveForm(true);
	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetPlayerType(pchar);
	}
	if(CheckAttribute(refStoreChar, "tutorial.trading"))
	{
		DeleteAttribute(refStoreChar, "tutorial.trading");
		DoQuestFunctionDelay("Tutorial_Trading", 1.0);
	}
	
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
	DelEventHandler("eTabControlPress", "procTabChange");
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

		case "TABLE_LIST2":
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

bool FilterItems(ref Item)
{
	bool items1, items2, items3, items4, items5;
	string groupID, itemType, sItem, TradeType;
	sItem = Item.id;
	
	if(!CheckAttribute(Item, "ID")) return false;

	if(CheckAttribute(Item,"groupID")) 	groupID = Item.groupID;
	if(CheckAttribute(Item,"itemType")) itemType = Item.itemType;
	if(CheckAttribute(Item,"TradeType")) TradeType = Item.TradeType;
	// проверка на экипировку, их не продаем
		
	items2 = (groupID == BLADE_ITEM_TYPE) || 	// холодное оружие
			 (groupID == GUN_ITEM_TYPE)	||		// огнестрел
			 (groupID == MUSKET_ITEM_TYPE)	||	// мушкеты
			 (groupID == SPYGLASS_ITEM_TYPE) || // трубы
			 (groupID == CIRASS_ITEM_TYPE) ||   // костюмы и доспехи
			 (groupID == TOOL_ITEM_TYPE) ||     // навигационные приборы котороые можно экипировать в спецслот
			 (groupID == LANTERN_ITEM_TYPE) ||  // фонарь
			 (groupID == HAT_ITEM_TYPE) ||  	// шляпы
			 (groupID == AMMO_ITEM_TYPE);		// расходники для огнестрела

	items4 = (groupID == ITEM_SLOT_TYPE) 	|| 	// амулеты
			 (groupID == TALISMAN_ITEM_TYPE)|| 	// талисманы
			 (itemType == "ARTEFACT");			// артефакты
	
	items5 = (groupID == PATENT_ITEM_TYPE)	||	// патенты
			 (groupID == MAPS_ITEM_TYPE) ||		// карты
			 (groupID == SPECIAL_ITEM_TYPE) || 	// спецпредметы
			 (itemType == "QUESTITEMS"); 	    // квестовые предметы			  

	if(CheckAttribute(refStoreChar, "Merchant.type"))
	{
		if(refStoreChar.Merchant.type == "jeweller" || refStoreChar.Merchant.type == "GasparGold")
		{
			if(!CheckAttribute(Item,"TradeType")) return false;
			if(Item.TradeType != ITEM_TRADE_JEWELRY && !items2) return false;
			if(items4) return false;
			if(items5) return false;
		}
	}
	
	if(currentTab == 2)
	{
		if (!items2) return false;
		if (HasSubStr(sItem, "potion"))  return false;
		if (HasSubStr(sItem, "mineral"))  return false;
	}
	if(currentTab == 3 && !HasSubStr(sItem, "potion"))  return false;
	if(currentTab == 4)
	{
		if (!items4) return false;
		if (HasSubStr(sItem, "chest"))  return false;
		if (HasSubStr(sItem, "jewelry"))  return false;
		if (HasSubStr(sItem, "dublon"))  return false;
		if (HasSubStr(sItem, "gold"))  return false;
		if (HasSubStr(sItem, "collect"))  return false;
		if (CheckAttribute(Item,"Price") && sti(Item.price) == 0) return false;
	}
	if(currentTab == 5)
	{
		if (!items5) return false;
		if (HasSubStr(sItem, "potion"))  return false;
		if (HasSubStr(sItem, "cannabis"))  return false;
	}
	return true;
}

void AddToTable()
{
	int n, i, j, leftQty, rightQty;
	int  idLngFile;
	string row, row2, sItem; 
	ref rItem;
	string sList;

	n = 1;
	j = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_LIST", false, true, false);
	Table_Clear("TABLE_LIST2", false, true, false);	
	HideItemInfo(); // прячем по умолчанию инфу по предметам

	// Сначала уникальные предметы
	for (i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		row = "tr" + n;
		row2 = "tr" + j;
		rItem = &Items[i];
		sItem = rItem.id;

		if(TradeMode == 1) continue; // рандомящиеся предметы за дублоны не продаем
		// проверка на экипировку, их не продаем
		if(!FilterItems(rItem)) continue;
		if(CheckAttribute(refStoreChar, "Merchant.type") && refStoreChar.Merchant.type == "GasparGold")
		{
			if(GetCharacterFreeItem(refCharacter, sItem) > 0)
			{
				leftQty  = GetCharacterFreeItem(refCharacter, sItem);
			}
			else
			{
				leftQty  = CheckItemMyCabin(sItem);
			}
		}
		else 
		{
			leftQty  = GetCharacterFreeItem(refCharacter, sItem);
		}
		rightQty = GetCharacterFreeItem(refStoreChar, sItem);

		// предметы героя
		if (leftQty > 0)
		{
			GameInterface.TABLE_LIST.(row).td1.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST.(row).td1.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST.(row).td1.icon.offset = "0, 0";
			GameInterface.TABLE_LIST.(row).td1.icon.width = 50;
			GameInterface.TABLE_LIST.(row).td1.icon.height = 50;
			GameInterface.TABLE_LIST.(row).td1.textoffset = "50,0";
			GameInterface.TABLE_LIST.(row).td1.str = LanguageConvertString(idLngFile, rItem.name);
			GameInterface.TABLE_LIST.(row).td1.line_space_modifier = 0.9;
			GameInterface.TABLE_LIST.(row).td2.str = leftQty;
			GameInterface.TABLE_LIST.(row).td3.str = FloatToString(stf(rItem.Weight) * leftQty, 1);
			GameInterface.TABLE_LIST.(row).td4.str = GetTradeItemPrice(i, PRICE_TYPE_SELL, refStoreChar);
			GameInterface.TABLE_LIST.(row).index = i;
			ShowItemInfo();	
			sList = "tr" + sti(GameInterface.TABLE_LIST.select);
			if(CheckAttribute(GameInterface, "TABLE_LIST." + sList + ".index"))
			{
				iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sList).index);
				ShowGoodsInfo(iCurGoodsIdx);
			}
			n++;
		} 
		
		// предметы торговца
		if (rightQty > 0)
		{
			GameInterface.TABLE_LIST2.(row2).td1.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST2.(row2).td1.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST2.(row2).td1.icon.offset = "0, 0";
			GameInterface.TABLE_LIST2.(row2).td1.icon.width = 50;
			GameInterface.TABLE_LIST2.(row2).td1.icon.height = 50;
			GameInterface.TABLE_LIST2.(row2).td1.textoffset = "50,0";
			GameInterface.TABLE_LIST2.(row2).td1.line_space_modifier = 0.9;
			GameInterface.TABLE_LIST2.(row2).td1.str = LanguageConvertString(idLngFile, rItem.name);            
			GameInterface.TABLE_LIST2.(row2).td2.str = rightQty;
			GameInterface.TABLE_LIST2.(row2).td3.str = FloatToString(stf(rItem.Weight), 1);
			GameInterface.TABLE_LIST2.(row2).td4.str = GetTradeItemPrice(i, PRICE_TYPE_BUY, refStoreChar);
			GameInterface.TABLE_LIST2.(row2).index = i;
			ShowItemInfo();	
			sList = "tr" + sti(GameInterface.TABLE_LIST2.select);
			if(CheckAttribute(GameInterface, "TABLE_LIST2." + sList + ".index"))
			{
				iCurGoodsIdx = sti(GameInterface.TABLE_LIST2.(sList).index);
				ShowGoodsInfo(iCurGoodsIdx);
			}
			j++;
		} 
	}
	
    for (i = 0; i < ITEMS_QUANTITY; i++)
	{
		row = "tr" + n;
		row2 = "tr" + j;
		rItem = &Items[i];
		sItem = rItem.id;

		if(TradeMode == 1) // тока за дублоны
		{
			if(!CheckAttribute(rItem,"PriceDublon")) continue;
		}
		else
		{	
			if(!bBettaTestMode)
			{
				if(CheckAttribute(rItem,"Price") && sti(rItem.price) == 0) continue;
			}
		}
		if(!FilterItems(rItem)) continue;
		// проверка на экипировку, их не продаем
		if(CheckAttribute(refStoreChar, "Merchant.type") && refStoreChar.Merchant.type == "GasparGold")
		{
			if(GetCharacterFreeItem(refCharacter, sItem) > 0)
			{
				leftQty  = GetCharacterFreeItem(refCharacter, sItem);
			}
			else
			{
				leftQty  = CheckItemMyCabin(sItem);
			}	
		}
		else 
		{
			leftQty  = GetCharacterFreeItem(refCharacter, sItem);
		}
		rightQty = GetCharacterFreeItem(refStoreChar, sItem);

		// предметы героя
		if(leftQty > 0)
		{			
			GameInterface.TABLE_LIST.(row).td1.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST.(row).td1.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST.(row).td1.icon.offset = "0, 0";
			GameInterface.TABLE_LIST.(row).td1.icon.width = 50;
			GameInterface.TABLE_LIST.(row).td1.icon.height = 50;
			GameInterface.TABLE_LIST.(row).td1.textoffset = "50,0";
			GameInterface.TABLE_LIST.(row).td1.str = LanguageConvertString(idLngFile, rItem.name);
			GameInterface.TABLE_LIST.(row).td1.line_space_modifier = 0.9;
			GameInterface.TABLE_LIST.(row).td2.str = leftQty;
			GameInterface.TABLE_LIST.(row).td3.str = FloatToString(stf(rItem.Weight) * leftQty, 1);
			GameInterface.TABLE_LIST.(row).td4.str = GetTradeItemPrice(i, PRICE_TYPE_SELL, refStoreChar);
			GameInterface.TABLE_LIST.(row).index = i;
			if(TradeMode == 0)
			{
				GameInterface.TABLE_LIST.(row).td4.str = GetTradeItemPrice(i, PRICE_TYPE_SELL, refStoreChar);
			}
			else
			{
				GameInterface.TABLE_LIST.(row).td4.str = GetTradeItemPriceDublon(i, PRICE_TYPE_SELL, refStoreChar);
			}			
			ShowItemInfo();	
			sList = "tr" + sti(GameInterface.TABLE_LIST.select);
			if(CheckAttribute(GameInterface, "TABLE_LIST." + sList + ".index"))
			{
				iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sList).index);
				ShowGoodsInfo(iCurGoodsIdx);
			}
			n++;
		} 
		
		// предметы торговца
		if(rightQty > 0)
		{
			GameInterface.TABLE_LIST2.(row2).td1.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST2.(row2).td1.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST2.(row2).td1.icon.offset = "0, 0";
			GameInterface.TABLE_LIST2.(row2).td1.icon.width = 50;
			GameInterface.TABLE_LIST2.(row2).td1.icon.height = 50;
			GameInterface.TABLE_LIST2.(row2).td1.textoffset = "50,0";
			GameInterface.TABLE_LIST2.(row2).td1.line_space_modifier = 0.9;
			GameInterface.TABLE_LIST2.(row2).td1.str = LanguageConvertString(idLngFile, rItem.name);            
			GameInterface.TABLE_LIST2.(row2).td2.str = rightQty;
			GameInterface.TABLE_LIST2.(row2).td3.str = FloatToString(stf(rItem.Weight), 1);
			GameInterface.TABLE_LIST2.(row2).td4.str = GetTradeItemPrice(i, PRICE_TYPE_BUY, refStoreChar);
			GameInterface.TABLE_LIST2.(row2).index = i;
			if(TradeMode == 0)
			{
				GameInterface.TABLE_LIST2.(row2).td4.str = GetTradeItemPrice(i, PRICE_TYPE_BUY, refStoreChar);
			}
			else
			{
				GameInterface.TABLE_LIST2.(row2).td4.str = GetTradeItemPriceDublon(i, PRICE_TYPE_BUY, refStoreChar);
			}
			ShowItemInfo();	
			sList = "tr" + sti(GameInterface.TABLE_LIST2.select);
			if(CheckAttribute(GameInterface, "TABLE_LIST2." + sList + ".index"))
			{
				iCurGoodsIdx = sti(GameInterface.TABLE_LIST2.(sList).index);
				ShowGoodsInfo(iCurGoodsIdx);
			}
			j++;
		}
	}
	
	NextFrameRefreshTable();
	LanguageCloseFile(idLngFile);
}

void NextFrameRefreshTable()
{
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST2", 0 );
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
    Table_UpdateWindow(sControl);
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
    string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	sHeader = XI_ConvertString("titleItemsTrade");
	sText1 = XI_ConvertString("ItemsTrade_d1");
	sText3 = XI_ConvertString("ItemsTrade_d2");

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,192,192), sText3, argb(255,255,192,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void EndTooltip()
{
	CloseTooltip(); // всегда убирать, если был
    GameInterface.qty_edit.str = 0;
	SetCharWeight();
	SetVariable();
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "");	
 	SetNodeUsing("QTY_BUYSELL_BUTTON", false);
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
	SetCurrentNode(Curtable);
}

void ShowItemInfo()
{
	XI_WindowDisable("QTY_WINDOW", false);
	XI_WindowShow("QTY_WINDOW", true);
	SetNodeUsing("QTY_BUYSELL_BUTTON", false);
	// GameInterface.qty_edit.str = "0";
	// BuyOrSell = 0;
	// ChangeQTY_EDIT();
	if (GetRemovable(refCharacter)) SetSelectable("QTY_BUYSELL_BUTTON",true);
	else SetSelectable("QTY_BUYSELL_BUTTON",false);		
	// }
}

void HideItemInfo()
{
	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
    selectedRow = GetEventData();
    CurTable = sControl;
    string sRow = "tr" + (selectedRow);
	NullSelectTable("TABLE_LIST");
    NullSelectTable("TABLE_LIST2");
	SetCharWeight();
	SetVariable();
	ShowItemInfo();
	if (CurTable == "TABLE_LIST") ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sRow).index));
    else ShowGoodsInfo(sti(GameInterface.TABLE_LIST2.(sRow).index));
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	if( sNodName == "TABBTN_1" )
	{
		SetControlsTabModeManual( 1 );
		return;
	}
	if( sNodName == "TABBTN_2" )
	{
		SetControlsTabModeManual( 2 );
		return;
	}
	if( sNodName == "TABBTN_3" )
	{
		SetControlsTabModeManual( 3 );
		return;
	}
	if( sNodName == "TABBTN_4" )
	{
		SetControlsTabModeManual( 4 );
		return;
	}
	if( sNodName == "TABBTN_5" )
	{
		SetControlsTabModeManual( 5 );
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
	
	currentTab = nMode;
	// Выставим таблицы в начало
	GameInterface.TABLE_LIST.select = 1;
	GameInterface.TABLE_LIST.top = 0;
	GameInterface.TABLE_LIST2.select = 1;
	GameInterface.TABLE_LIST2.top = 0;
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST",0);
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST2",0);
	SetDescription();
}

void FillCharactersScroll()
{
	int i;
	string faceName;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2;
	bool bOk;
	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");

	nCurScrollNum = -1;
	GameInterface.CHARACTERS_SCROLL.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetNotQuestPassengersQuantity(pchar);

	GameInterface.CHARACTERS_SCROLL.NotUsed = 6;
	GameInterface.CHARACTERS_SCROLL.ListSize = nListSizeFree + 2;

	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 2); // passengers

	GameInterface.CHARACTERS_SCROLL.BadTex1 = 0;
	GameInterface.CHARACTERS_SCROLL.BadPic1 = "emptyface";

	int m = 0;
	attributeName = "pic" + (m + 1);
	GameInterface.CHARACTERS_SCROLL.(attributeName).character = nMainCharacterIndex;
	GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(pchar);
	GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + pchar.FaceID);
	m++;

	for(i = 0; i < nListSize; i++)
	{
		_curCharIdx = GetPassenger(pchar, i);

        bOk = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
		if(_curCharIdx != -1  && !CheckAttribute(&characters[_curCharIdx], "isquest") && !bOk)
		{
			if (IsOfficer(&characters[_curCharIdx]) && PChar.location == Characters[_curCharIdx].location)  // boal
			// Jason: фикс - офицеры только в одной с ГГ локации
			{
				attributeName = "pic" + (m + 1);
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText  = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	SetFormatedText("CAPACITY", sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
    sMaxGoodsStore = GetFullName(refStoreChar) + NewStr() + XI_ConvertString("Merchant");
	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);

	if(!CheckAttribute(refStoreChar,"Merchant.type"))
	{
		if(TradeMode == 0)
		{
			sText = MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER);
		}
		else
		{
			sText = FindRussianDublonString(sti(pchar.dublon));
		}	
		SetFormatedText("OUR_GOLD", sText);
	}
	else
	{
		if(TradeMode == 0) sText = MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER);
		else			   sText = MakeMoneyShow(sti(pchar.Dublon), MONEY_SIGN,MONEY_DELIVER);
		GameInterface.strings.Money_1 = sText;
		SetFormatedText("OUR_GOLD", sText);
		
		if(TradeMode == 0) sText = MakeMoneyShow(sti(refStoreChar.Money), MONEY_SIGN,MONEY_DELIVER);
		else               sText = MakeMoneyShow(sti(refStoreChar.Dublon), MONEY_SIGN,MONEY_DELIVER);
		GameInterface.strings.Money_2 = sText;
		SetFormatedText("STORE_GOLD", sText);
	}
}

void ProcessFrame()
{
	if(sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		// XI_WindowDisable("QTY_WINDOW", false);
		// XI_WindowShow("QTY_WINDOW", true);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		refCharacter = &characters[sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character)];
		SetDescription();
 		FillCharacterInfo();
		// Выставим таблицы в начало
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
		GameInterface.TABLE_LIST2.select = 1;
		GameInterface.TABLE_LIST2.top = 0;
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST",0);
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST2",0);
	}
}
void FillCharacterInfo()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\le\portraits\256\face_" + refCharacter.FaceId + ".tga");
	GameInterface.strings.CharName = GetFullName(refCharacter);
	SetFormatedText("CHARACTER_NAME", GetFullName(refCharacter));
}
void SetDescription()
{
 	if(GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		string attributeName = attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "CHARACTERS_SCROLL." + attributeName))
		{
			SetCharWeight();
		}
	}
    CalculateInfoData();
	SetVariable();
}

void CalculateInfoData()
{
	AddToTable();
}

void SetCharWeight()
{
    fCharWeight  = GetItemsWeight(refCharacter);

    fStoreWeight = 0;
}
// инфа о предмете
void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = Items[iGoodIndex].name;
	ref    arItm = &Items[iGoodIndex];
	int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sHeader = LanguageConvertString(lngFileID, GoodName);

    iCurGoodsIdx = iGoodIndex;

    string describeStr = "";

	if(bBettaTestMode)
	{
	    describeStr += " id = " + Items[iGoodIndex].id + NewStr();
	    
	    if(CheckAttribute(arItm, "dmg_min.old") && CheckAttribute(arItm, "dmg_max.old"))
	    {
	    	describeStr += "OldDmgMin = " + sti(arItm.dmg_min.old) + ", OldDmgMax = "+sti(arItm.dmg_max.old) + newStr();
	    }
	}
	describeStr += GetItemDescribe(iGoodIndex);

	fWeight = stf(Items[iGoodIndex].weight);

    BuyOrSell = 0;
    SetFormatedText("QTY_TypeOperation", "");
    SetFormatedText("QTY_Result", "");
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", Items[iCurGoodsIdx].picTexture, "itm" + Items[iCurGoodsIdx].picIndex);
    SetFormatedText("QTY_CAPTION", sHeader);
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"QTY_CAPTION", 5 );
    SetFormatedText("QTY_GOODS_INFO", describeStr);
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"QTY_GOODS_INFO", 5 );
	LanguageCloseFile(lngFileID);

	if(CheckAttribute(refStoreChar, "Merchant.type") && refStoreChar.Merchant.type == "GasparGold")
	{
		if(GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id) > 0)
		{
			iCharQty  = GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id);
		}
		else
		{
			iCharQty  = CheckItemMyCabin(Items[iGoodIndex].id);
		}	
	}
	else 
	{
		iCharQty  = GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id);
	}

	//iCharQty = GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id);

	iStoreQty = GetCharacterFreeItem(refStoreChar, Items[iGoodIndex].id);

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;

	if(TradeMode == 0) iStorePrice = GetTradeItemPrice(iGoodIndex, PRICE_TYPE_SELL, refStoreChar);
	else 			   iStorePrice = GetTradeItemPriceDublon(iGoodIndex, PRICE_TYPE_SELL, refStoreChar);
    SetFormatedText("QTY_INFO_STORE_PRICE",XI_ConvertString("Price sell") + NewStr() + its(iStorePrice));

	if(TradeMode == 0) iCharPrice = GetTradeItemPrice(iGoodIndex, PRICE_TYPE_BUY, refStoreChar);
	else 			   iCharPrice = GetTradeItemPriceDublon(iGoodIndex, PRICE_TYPE_BUY, refStoreChar);
	SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price buy") + NewStr() + its(iCharPrice));
}

// Returns false if no correct good can be shown.
bool ShowCorrectLastGood()
{
    int leftovers = -1;
    bool correctInfo = true;
	bool isLastLine = false;
	bool valid = false;
	string stringRow;

    if (BuyOrSell == 1) leftovers = GetCharacterFreeItem(refStoreChar, Items[iCurGoodsIdx].id);
    else 				leftovers = GetCharacterFreeItem(refCharacter, Items[iCurGoodsIdx].id);

    if (leftovers == 0)
    {
		stringRow = "tr" + (selectedRow + 1);
		if (BuyOrSell == -1) {
            if (!CheckAttribute(GameInterface, "TABLE_LIST." + stringRow + ".index")) isLastLine = true;
        } else {
            if (!CheckAttribute(GameInterface, "TABLE_LIST2." + stringRow + ".index")) isLastLine = true;
        }
        if (isLastLine)
        {
            selectedRow -= 1;
            stringRow = "tr" + selectedRow;
            if (selectedRow >= 1)
            {
                if (BuyOrSell == -1) {
                    if (CheckAttribute(GameInterface, "TABLE_LIST." + stringRow + ".index")) {
                        iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(stringRow).index);
                    }
                } else {
                    if (CheckAttribute(GameInterface, "TABLE_LIST2." + stringRow + ".index")) {
                        iCurGoodsIdx = sti(GameInterface.TABLE_LIST2.(stringRow).index);
                    }
                }
            }
            else
            {
                selectedRow = 1;
                stringRow = "tr" + selectedRow;
                if (BuyOrSell == -1) {
                    if (CheckAttribute(GameInterface, "TABLE_LIST2." + stringRow + ".index"))
                    {
                        iCurGoodsIdx = sti(GameInterface.TABLE_LIST2.(stringRow).index);
                        GameInterface.TABLE_LIST2.select = selectedRow;
                        valid = true;
                    }
                } else {
                    if (CheckAttribute(GameInterface, "TABLE_LIST." + stringRow + ".index"))
                    {
                        iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(stringRow).index);
                        GameInterface.TABLE_LIST.select = selectedRow;
                        valid = true;
                    }
                }
                if (!valid) correctInfo = false;
            }
        }
    }

    return correctInfo;
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

 	if (BuyOrSell == 1) // BUY
	{
		TakeNItems(refStoreChar, Items[iCurGoodsIdx].id, -nTradeQuantity);
		TakeNItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);				
		moneyback = makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5);
		
		if(TradeMode == 0)
		{
			pchar.money = sti(pchar.money)  - moneyback;
			if(CheckAttribute(refStoreChar,"money") && CheckAttribute(refStoreChar,"Merchant.type"))
			{
				refStoreChar.money = sti(refStoreChar.money) + moneyback;
			}
			Statistic_AddValue(Pchar, "Money_spend", moneyback);
			// boal  check skill -->
	        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 700.0);
		}
		else
		{
			TakeNItems(refStoreChar, "gold_dublon", moneyback);
			TakeNItems(pchar, "gold_dublon", -moneyback);
			AddCharacterExpToSkill(pchar, "Commerce", moneyback / 70.0);	
		}
		
    	if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 5);
        // boal <--
	}
 	else
	{ // SELL
	    TakeNItems(refStoreChar, Items[iCurGoodsIdx].id, nTradeQuantity);
		if(CheckAttribute(refStoreChar, "Merchant.type") && refStoreChar.Merchant.type == "GasparGold")
		{
			if(GetCharacterFreeItem(refCharacter, Items[iCurGoodsIdx].id) > 0)
			{
				TakeNItems(refCharacter, Items[iCurGoodsIdx].id, -nTradeQuantity);	
			}
			else
			{
				if(CheckItemMyCabin(Items[iCurGoodsIdx].id) > 0)
				GetItemMyCabin(Items[iCurGoodsIdx].id, nTradeQuantity);
			}	
		}
		else 
		{
			TakeNItems(refCharacter, Items[iCurGoodsIdx].id, -nTradeQuantity);		
		}
		//TakeNItems(refCharacter, Items[iCurGoodsIdx].id, -nTradeQuantity);
		moneyback = makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5);
		
		if(TradeMode == 0)
		{
	  		pchar.money = sti(pchar.money)  + moneyback;
			if(CheckAttribute(refStoreChar,"money") && CheckAttribute(refStoreChar,"Merchant.type"))
			{
				refStoreChar.money = sti(refStoreChar.money) - moneyback;
			}
			Statistic_AddValue(Pchar, "Money_get", moneyback);
			Achievment_SetStat(39, moneyback);
			// boal  check skill -->
	        AddCharacterExpToSkill(pchar, "Commerce", moneyback / 1000.0);
		}
		else
		{
			TakeNItems(refStoreChar, "gold_dublon", -moneyback);
			TakeNItems(pchar, "gold_dublon", moneyback);
			AddCharacterExpToSkill(pchar, "Commerce", moneyback / 100.0);
		}
		
		
    	if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 5);
        // boal <--
	}

    bool correctInfo = ShowCorrectLastGood();
    CalculateInfoData();
    EndTooltip();
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
    if (!correctInfo)
    {
        HideItemInfo();
    }
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_BUYSELL_BUTTON");
}

void ChangeQTY_EDIT()
{
	float  iWeight;
	SetCharWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
		SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "");
		SetNodeUsing("QTY_BUYSELL_BUTTON", false);
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
		    if (sti(GameInterface.qty_edit.str) > iCharQty)
		    {
		        GameInterface.qty_edit.str = iCharQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fStoreWeight + iWeight) > iTotalSpace)
		    {
		        iWeight = iTotalSpace - fStoreWeight - 0.01; // чуть меньше
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округление
		    }
			if(CheckAttribute(refStoreChar,"Merchant.type"))
			{
				if(TradeMode == 0)
				{
					if (makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(refStoreChar.money))
					{
						GameInterface.qty_edit.str = makeint(sti(refStoreChar.money) / iStorePrice);
						iWeight = fWeight * sti(GameInterface.qty_edit.str);
					}
				}
				else
				{
					if (makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(refStoreChar.dublon))
					{
						GameInterface.qty_edit.str = makeint(sti(refStoreChar.dublon) / iStorePrice);
						iWeight = fWeight * sti(GameInterface.qty_edit.str);
					}				
				}	
			}	
		    // проверка на колво доступное <--
		    // квестовые не продать -->
		    if (IsQuestUsedItem(Items[iCurGoodsIdx].id))
		    {
		        GameInterface.qty_edit.str = 0;
		    }
		    // квестовые не продать <--
		    SetFormatedText("QTY_TypeOperation", XI_ConvertString("SELL"));
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "SELL");
			SetNodeUsing("QTY_BUYSELL_BUTTON", true);
		    SetFormatedText("QTY_Result", XI_ConvertString("Money") + " " + makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) +
			                ", " + XI_ConvertString("weight") + " " + FloatToString(iWeight, 1) );
		}
		else
		{
			BuyOrSell = 1;
	        // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fCharWeight + iWeight) > iCharCapacity)
		    {
		        iWeight = iCharCapacity - fCharWeight - 0.01; // чуть меньше
				if (iWeight < 0) iWeight = 0;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округдение
		    }
			if(TradeMode == 0)
			{
				if (makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(pchar.money))
				{
					GameInterface.qty_edit.str = makeint(sti(pchar.money) / iCharPrice);
					iWeight = fWeight * sti(GameInterface.qty_edit.str);
				}
			}	
			else
			{
				if (makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(pchar.dublon))
				{
					GameInterface.qty_edit.str = makeint(sti(pchar.dublon) / iCharPrice);
					iWeight = fWeight * sti(GameInterface.qty_edit.str);
				}
			}	
		    // проверка на колво доступное <--
			SetFormatedText("QTY_TypeOperation", XI_ConvertString("BUY"));
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "BUY");
			SetNodeUsing("QTY_BUYSELL_BUTTON", true);
			SetFormatedText("QTY_Result", XI_ConvertString("Money") + " " + makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) +
			                ", " + XI_ConvertString("weight") + " " + FloatToString(iWeight, 1) );
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
		SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_BUYSELL_BUTTON", 0, "");
		SetNodeUsing("QTY_BUYSELL_BUTTON", false);
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetCharWeight();
    fCharWeight  = fCharWeight  + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
    SetVariable();
}

void REMOVE_ALL_BUTTON()  // продать все
{
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iCharQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
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

int GetTradeItemPrice(int itmIdx, int tradeType, ref chr)
{
	int itmprice 		= 0;
	int itmtype 		= ITEM_TRADE_NORMAL;
	int FinalItmPrice 	= 0;
	float priceModify 	= 1.0;
	string sItemid;
	
	if(itmIdx<0 || itmIdx>TOTAL_ITEMS) return 0;

	if(CheckAttribute(&Items[itmIdx],"price"))
	{
		itmprice = sti(Items[itmIdx].price);
	}
	if(CheckAttribute(&Items[itmIdx],"TradeType"))
	{
		itmtype = sti(Items[itmIdx].TradeType);
	}
	if(CheckAttribute(&Items[itmIdx],"id"))
	{
		sItemid = Items[itmIdx].id;
	}

	float skillDelta = GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE);
	float skillModify;
	if(tradeType == PRICE_TYPE_BUY)	// покупка предметов героем
	{
		skillModify = 1.325 - skillDelta * 0.005; 		
		if(CheckAttribute(chr, "Merchant.type"))//Jason
		{
			if(chr.Merchant.type == "lightman")
			{
				if(itmtype == ITEM_TRADE_ARTEFACT || sItemid == "potionrum") skillModify *= 30.0;
				if(sItemid == "jewelry8") skillModify *= 10.0;
			}	
			if(chr.Merchant.type == "jeweller")
			{
				if(sItemid == "gold_dublon") 
				{
					FinalItmPrice = makeint(itmprice * 1.05);
					return FinalItmPrice;
				}	
			}
			if(bGlobalTutor && chr.Merchant.type == "SharlieTurorial")
			{
				switch(sItemid)
				{
					case "obereg_3": itmprice = 114; break; //150
					case "obereg_5": itmprice = 114; break; //150
					case "obereg_6": itmprice = 61; break; //80
					case "obereg_8": itmprice = 76; break; //100
					case "potionrum": itmprice = 151; break; //200
					case "map_full": itmprice = 4537; break; //6000
					//case "potion1": return 100; break;
				}
			}
			if(bGlobalTutor && chr.Merchant.type == "SharlieTurorialK")
			{
				switch(sItemid)
				{
					case "gold_dublon": return sti(chr.questTemp.GoldPrice); break;
				}
			}
		}
		if(CheckCharacterPerk(pchar,"HT2")) // belamour legendary edition скидка 15%
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{ skillModify -= 0.30; }
			else
			{
				if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.25; }
				else {skillModify -= 0.15;}
			}						
		}
		else
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{ skillModify -= 0.15; }
			else
			{
				if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.10; }
			}				
		}		
		if(skillModify < 1.01) skillModify = 1.01;
		FinalItmPrice = makeint(makefloat(itmprice)*skillModify);
	}
	else // продажа предметов героем
	{
		if(CheckAttribute(&Items[itmIdx],"fixedprice")) return itmprice;
		
		skillModify = 0.675 + skillDelta * 0.005; 
		if(CheckCharacterPerk(chr,"HT2")) // belamour legendary edition надбавка 15%
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{skillModify += 0.30;}
			else
			{
				if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify += 0.25; }
				else {skillModify += 0.15;}
			}				
		}
		else
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{skillModify += 0.15;}
			else
			{
				if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify += 0.10; }
			}		
		}			
		if(skillModify > 0.99) skillModify = 0.99;		
		priceModify = GetPriceModify(itmIdx, itmtype, chr);		
		FinalItmPrice = makeint(makefloat(itmprice)*skillModify * priceModify);
	}	

	return FinalItmPrice;
}

int GetTradeItemPriceDublon(int itmIdx, int tradeType, ref chr)
{
	int itmprice = 0;
	
	if(itmIdx < 0 || itmIdx > TOTAL_ITEMS) return 0;

	if(CheckAttribute(&Items[itmIdx],"PriceDublon"))
	{
		itmprice = sti(Items[itmIdx].PriceDublon);
	}

	float skillDelta = GetSummonSkillFromNameToOld(chr, SKILL_COMMERCE);
	float skillModify;
	if(tradeType == PRICE_TYPE_BUY)
	{
		skillModify = 1.325 - skillDelta * 0.005; 		
		if(CheckCharacterPerk(pchar,"HT2"))
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{ skillModify -= 0.20; }
			else
			{
				if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.15; }
				else skillModify -= 0.05;
			}						
		}
		else
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	{ skillModify -= 0.15; }
			else
			{
				if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.10; }
			}				
		}	
		if(skillModify < 1.01) skillModify = 1.01;
	}
	else
	{
		skillModify = 0.675 + skillDelta * 0.005; 
		if(CheckCharacterPerk(chr,"HT2"))
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	skillModify += 0.20;
			else
			{
				if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify += 0.15; }
				else skillModify += 0.05;
			}				
		}
		else
		{
			if(CheckOfficersPerk(pchar,"ProfessionalCommerce"))	skillModify += 0.15;
			else
			{
				if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify += 0.10; }
			}		
		}
		if(skillModify > 0.99) skillModify = 0.99;
	}
	return makeint(makefloat(itmprice)*skillModify);
}


float GetPriceModify(int itmIdx, int itmTradeType, ref _chr)
{
	aref arItem;
	string 	sMerchantType, sItemType, sItemid;
	float fModify = 1.0;
	
	if(itmIdx<0 || itmIdx>TOTAL_ITEMS) return 0;

	if(CheckAttribute(&Items[itmIdx],"id"))
	{
		sItemid = Items[itmIdx].id;
	}
	
	if(CheckAttribute(_chr, "Merchant.type"))
	{
		sMerchantType = _chr.Merchant.type;
		switch(sMerchantType)
		{
			case "potion"	:
				if(itmTradeType != ITEM_TRADE_NORMAL && itmTradeType != ITEM_TRADE_POTION) 
				{
					 fModify = 0.7;
				}
			break;
			case "veteran"	:
				if(itmTradeType != ITEM_TRADE_NORMAL) 
				{
					fModify = 0.7;
				}								
			break;
			case "armourer"	:
				if(itmTradeType != ITEM_TRADE_AMMUNITION) 
				{
					fModify = 0.7;
				}				
			break;
			case "monk"		:
				if(itmTradeType != ITEM_TRADE_ARTEFACT && itmTradeType != ITEM_TRADE_MAP) 
				{
					fModify = 0.7;
				}
			break;
			case "indian"	:
				if(itmTradeType != ITEM_TRADE_NORMAL && itmTradeType != ITEM_TRADE_ARTEFACT) 
				{
					fModify = 0.7;
				}
			break;
			case "jeweller"	:
				if(itmTradeType != ITEM_TRADE_JEWELRY) 
				{
					fModify = 0.7;
				}
			break;
			case "lightman"	://Jason
					if(sItemid == "potionrum") fModify = 10.0;
					else fModify = 0.5;
			break;
			case "LSC_indian"	://Jason 230912
					fModify = 0.3;
			break;
			case "company"	://Jason 230912
					fModify = 0.1;
			break;

			case "GasparGold":
				fModify = 0.7;
			break;
		}						
	}
	return fModify;
}

void CheckTraderItems(ref chr)
{
	string 	sMerchantType, sItemType;
	aref 	rootItems, curItem, arItem;
	
	if(CheckAttribute(chr, "Merchant.type")) // уличный торговец или ювелир
	{
		sMerchantType = chr.Merchant.type;
		makearef(rootItems, chr.Items);
		for(int j = 0; j < GetAttributesNum(rootItems); j++)
		{
			curItem = GetAttributeN(rootItems, j);
			if( Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 )
			{
				if(CheckAttribute(arItem, "TradeType")) 
				{
					sItemType = arItem.TradeType;
					switch(sMerchantType)
					{
						case "potion"	:
							if(sItemType != ITEM_TRADE_NORMAL 
								&& sItemType != ITEM_TRADE_POTION) DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "veteran"	:
							if(sItemType != ITEM_TRADE_NORMAL) 
								DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "armourer"	:
							if(sItemType != ITEM_TRADE_AMMUNITION) 
								DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "monk"		:
							if(sItemType != ITEM_TRADE_ARTEFACT 
								&& sItemType != ITEM_TRADE_MAP) DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "indian"	:
							if(sItemType != ITEM_TRADE_NORMAL 
								&& sItemType != ITEM_TRADE_ARTEFACT) DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "jeweller"	:
							if(sItemType != ITEM_TRADE_JEWELRY && arItem.id != "cirass3") 
								DeleteAttribute(chr, "items." + arItem.id); 
						break;
						case "GasparGold":
							if(sItemType != ITEM_TRADE_JEWELRY) 
								DeleteAttribute(chr, "items." + arItem.id); 
						break;
					}
				}	
			}
		}
	}
}
