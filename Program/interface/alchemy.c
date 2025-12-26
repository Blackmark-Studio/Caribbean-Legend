// Ugeen 26.08.10 - интерфейс мультиобъектов (на базе интерфейса обыска) 

int 	nCurScrollNum = 0;
ref 	refCharacter, rItem, nulChr;
aref    alchemy;
string  sCurItem;

bool 	bShowChangeWin = true;
int  	BuyOrSell = 0;
int  	iCharQty, iStoreQty, iCurGoodsIdx;

int 	iTableAddBtnX = 665;
int 	iTableAddBtnY = 380;
int 	iTableRemoveBtnX = 915;
int 	iTableRemoveBtnY = 380;

int 	iTableAddAllBtnX = 630;
int 	iTableAddAllBtnY = 380;
int 	iTableRemoveAllBtnX = 945;
int 	iTableRemoveAllBtnY = 380;
int 	iCurrentTabMode = 1; // belamour первым идёт главный герой																					 

int iLinesCount = 0;

void InitInterface(string iniName)
{
	refCharacter = GetMainCharacter();
	nulChr = &NullCharacter;

	GameInterface.title = "titleAlchemy";	
	if(CheckAttribute(nulChr,"alchemy.items")) DeleteAttribute(nulChr,"alchemy.items");
	makearef(alchemy, nulChr.alchemy);
	
	StartAboveForm(true);
	
	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("ItemsCount");
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("ItemsFunc");
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("ItemsName");
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("ItemsNeed");
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("ItemsCount");
	
	FillItemsScroll();
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	CreateString(true, "ItemName", "", FONT_NORMAL, COLOR_MONEY, 960, 240, SCRIPT_ALIGN_CENTER, 1.5);
	
	sCurItem = SetItemsName();
	AddToTable(ItemsFromId(sCurItem));
	

	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.tr1.index);
	ShowGoodsInfo(GetItemIndex(sCurItem));
	
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON", 0, iTableAddBtnX, iTableAddBtnY, iTableAddBtnX + 30, iTableAddBtnY + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON", 0, iTableRemoveBtnX, iTableRemoveBtnY, iTableRemoveBtnX + 30, iTableRemoveBtnY + 45, 0);
	
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 35, iTableAddAllBtnY + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 35, iTableRemoveAllBtnY + 45, 0);
	
	SetNodeUsing("GETALL_BUTTON", true);
	SetSelectable("GETALL_BUTTON", false);
	XI_WindowShow("QTY_WINDOW", false);
	
	// belamour показывать TAB будем только в каюте -->
	int chestCount = CountChestsInCabin(Get_My_Cabin());
	if(chestCount < 1)
	{
		SetSelectable("TABSTR_1", false);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,argb(255,128,128,128));
	}
	// залочим несуществующие сундуки
	for(int j = 2; j <= 5; j++)
	{
		if(j > chestCount + 1)
		{
			SetSelectable("TABSTR_"+j, false);
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_"+j, 8,0,argb(255,128,128,128));
		}
	}
	// <-- belamour
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
	SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("eTabControlPress", "procTabChange", 0);
	SetEventHandler("ChooseTable", "ChooseTable", 0);
	
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\le\portraits\128\face_" + refCharacter.FaceId + ".tga");	
	SetNodeUsing("QTY_TAKEGIVE_BUTTON", false);	
	SetControlsTabMode(1);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_ALCHEMY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_ALCHEMY_EXIT);		
}

void IDoExit(int exitCode)
{		
	aref rootItems, curItem, arItem;
	int iItemsQty;

	makearef(rootItems, alchemy.Items);
    for(int j = 0; j < GetAttributesNum(rootItems); j++)
    {
		curItem = GetAttributeN(rootItems,j);
		if( Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 )
		{
			iItemsQty = sti(GetAttributeValue(curItem));
			if(iItemsQty == 0) 	continue;
			AddItems(refCharacter, arItem.id, iItemsQty);
			//PutItemMyBox("box1", arItem.id, iItemsQty); 
		}
	}

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
	DelEventHandler("ShowInfoWindow", "ShowHelpHint");
	DelEventHandler("HideInfoWindow", "HideInfoWindow");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	DelEventHandler("eTabControlPress", "procTabChange");
	DelEventHandler("ChooseTable", "ChooseTable");
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ChooseTable()
{
	SetCurrentNode("TABLE_LIST");
	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.tr1.index);
	ShowGoodsInfo(iCurGoodsIdx);
	XI_WindowShow("QTY_WINDOW", true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{	
		
		case "TABLE_ADD_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onTableAddAllBtnClick();
			}
		break;
		
		case "TABLE_REMOVE_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onTableRemoveAllBtnClick();
			}
		break;

		case "TABLE_ADD_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onTableAddBtnClick();
			}
		break;
		
		case "TABLE_REMOVE_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onTableRemoveBtnClick();
			}
		break;
		
		case "QTY_TAKEGIVE_BUTTON":
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
				onTableAddBtnClick();
			}
			if(comName=="rightstep")
			{
				onTableRemoveBtnClick();
			}
			if(comName=="speedleft")
			{
				onTableAddAllBtnClick();
			}
			if(comName=="speedright")
			{
				onTableRemoveAllBtnClick();
			}
		break;
		
		case "GETALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onGetAllBtnClick();
			}
		break;
	}	
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void ShowHelpHint()
{
	string sCurrentNode = GetEventData();
	string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	if(sCurrentNode == "ITEMS_SCROLL")
	{
		ref    arItm = ItemsFromID(sCurItem);
		sHeader = GetItemName(arItm);
		sText1 =  GetItemDescr(arItm);
		CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, 64, 64, false);
	}
	else
	{
		sHeader = XI_ConvertString("titleAlchemy");
		sText1 = XI_ConvertString("Alchemy_Descr1");
		sText2 = XI_ConvertString("Alchemy_Descr2");
		CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, 64, 64, false);
	}	
}

void HideInfoWindow()
{
	CloseTooltipNew();
}

int GetMultiObjectQty()
{
	int Qty = 0;
	for(int n = 0; n < TOTAL_ITEMS; n++)
	{
		if( CheckAttribute(&Items[n],"multiobject") )
		{
			Qty++;
		}
	}
	return Qty;
}

void FillItemsScroll()
{
	int 	i, iNum;
	string 	attributeName, sAttr, sItemId, sItmId;
	ref     itm; 
	aref 	arImgGrp, rType;
	
	DeleteAttribute(&GameInterface, "ITEMS_SCROLL");

	nCurScrollNum = 0;
	GameInterface.ITEMS_SCROLL.current = 0;
	
	int nListSize = GetMultiObjectQty();
	
	GameInterface.ITEMS_SCROLL.NotUsed = 6;
	GameInterface.ITEMS_SCROLL.ListSize = nListSize + 2;

	GameInterface.ITEMS_SCROLL.ImagesGroup.t0 = "ITEMS_EMPTY";
	
	makearef(arImgGrp, GameInterface.ITEMS_SCROLL.ImagesGroup);
	FillImagesGroupForItems(arImgGrp);

	GameInterface.ITEMS_SCROLL.BadTex1 = 0;
	GameInterface.ITEMS_SCROLL.BadPic1 = "empty";
		
	int m = 0;
	for(int n = 0; n < TOTAL_ITEMS; n++)
	{
		makeref(itm, Items[n]); 
				
		if(CheckAttribute(itm, "id") && CheckAttribute(itm, "multiobject") && CheckAttribute(itm, "multiobject.alchemy") && isMultiObjectKnown(itm.id))
		{
			//if(itm.multiobject.alchemy == true && !CheckCharacterPerk(refCharacter, "Alchemy")) continue;
		
			attributeName = "pic" + (m + 1);
			GameInterface.ITEMS_SCROLL.(attributeName).itemId = itm.id;
			GameInterface.ITEMS_SCROLL.(attributeName).img1 = GetItemPictureName(itm.id);
			GameInterface.ITEMS_SCROLL.(attributeName).tex1 = GetItemPictureTexture("ITEMS_SCROLL.ImagesGroup",itm.id);
			
			sItemId = itm.id;
			alchemy.items.(sItemId) = 0;
			
			makearef(rType, itm.component);
			iNum = GetAttributesNum(rType);
			
			for(i = 0; i < iNum; i++)
			{
				sAttr = "t" + (i + 1);
				sItmId = itm.component.(sAttr).id;
				alchemy.items.(sItmId) = 0;
			}
			m++;
		}
	}
}

string SetItemsName()
{	
	string sAttr = "pic" + (nCurScrollNum + 1);
	string itemId = GameInterface.ITEMS_SCROLL.(sAttr).itemId;	
	ref rItem = ItemsFromID(itemId);	
	string sItemName = GetItemName(rItem);
	GameInterface.strings.ItemName = sItemName;
	
	return itemId;
}

void ProcessFrame()
{	
	if(sti(GameInterface.ITEMS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "ITEMS_SCROLL")
	{

		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.ITEMS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		string sItemId = GameInterface.ITEMS_SCROLL.(sAttr).itemId;
		
		rItem = ItemsFromId(sItemId);

		AddToTable(rItem);
		iCurGoodsIdx = sti(GameInterface.TABLE_LIST.tr1.index);
		ShowGoodsInfo(sti(rItem.index));
		sCurItem = sItemId;
		
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;

		SetItemsName();
		
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST",0);
		// Стрелочки на первую позицию
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON", 0, iTableAddBtnX, iTableAddBtnY, iTableAddBtnX + 30, iTableAddBtnY + 45, 0);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON", 0, iTableRemoveBtnX, iTableRemoveBtnY, iTableRemoveBtnX + 30, iTableRemoveBtnY + 45, 0);
		
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 35, iTableAddAllBtnY + 45, 0);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 35, iTableRemoveAllBtnY + 45, 0);
	}
	
}

void ChangePosTable()
{
}

void AddToTable(ref rItem)
{
	string 	sItemId, sItmId, sAttr, sList, sItmUse, sItmReq;
	int 	n, i, iNum, iLeftQty, iRightQty;
	aref    rType;
	ref     itm;
	
	
	n = 1;	
	iLinesCount = 1;
	Table_Clear("TABLE_LIST", false, true, false);
	
	sItemId = rItem.id;

	makearef(rType, rItem.component);
	iNum = GetAttributesNum(rType);
	
	for(i = 0; i < iNum; i++) // кол-во компонентов и прочего
	{	
		sAttr 		= GetAttributeName(GetAttributeN(rType, i));
		sItmId 		= rItem.component.(sAttr).id;
		sItmUse 	= rItem.component.(sAttr).use;
		sItmReq     = rItem.component.(sAttr).qty;
		
		if(CheckCharacterPerk(refCharacter, "Alchemy"))
		{
			if(rItem.component.(sAttr).id == "alchemy_tool") continue;
			if(rItem.component.(sAttr).id == "Mechanic_Tool") continue;
			if(rItem.component.(sAttr).id == "tailor_tool") continue;
		}
		itm = ItemsFromId(sItmId);
		trace("sItemId :" +sItemId +" sItmId : " + sItmId);	
		
		sList = "tr" + n;
		// belamour заполнить имеющимся количеством
		if(iCurrentTabMode == 1) iLeftQty  = GetCharacterFreeItem(refCharacter, sItmId);
		else iLeftQty = CheckItemMyBox("box"+sti(iCurrentTabMode-1), sItmId); 
		if(CheckAttribute(alchemy, "items."+(sItmId))) iRightQty = sti(alchemy.items.(sItmId));
		else iRightQty = 0;
		
		GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
		GameInterface.TABLE_LIST.(sList).td2.str = XI_ConvertString(sItmUse);
		GameInterface.TABLE_LIST.(sList).td3.icon.group = itm.picTexture;
		GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + itm.picIndex;
		GameInterface.TABLE_LIST.(sList).td3.icon.offset = "0, 0";
		GameInterface.TABLE_LIST.(sList).td3.icon.width = 55;
		GameInterface.TABLE_LIST.(sList).td3.icon.height = 55;
		GameInterface.TABLE_LIST.(sList).td3.textoffset = "60, 0";
		GameInterface.TABLE_LIST.(sList).td3.str = GetItemName(itm);
		GameInterface.TABLE_LIST.(sList).index = itm.index;
		GameInterface.TABLE_LIST.(sList).td4.str = sItmReq;
		GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;
		
		n++;			
		iLinesCount++;
	}

	Table_UpdateWindow("TABLE_LIST");
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
}

void CS_TableSelectChange()
{
	String sControl = GetEventData();
	int iSelected = GetEventData();
	int iCol = GetEventData();
	
	// Warship 26.04.09 fix - при прокрутке могло вылазить за экран, неправильно определялась текущая линия
	int iSelLine = iSelected;
	
	if(CheckAttribute(&GameInterface, "TABLE_LIST.top"))
	{
		iSelLine = iSelected - sti(GameInterface.TABLE_LIST.top);
	}
	
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON", 0, iTableAddBtnX, iTableAddBtnY + 55 * (iSelLine - 1), iTableAddBtnX + 30, iTableAddBtnY + 55 * (iSelLine - 1) + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON", 0, iTableRemoveBtnX, iTableRemoveBtnY + 55 * (iSelLine - 1), iTableRemoveBtnX + 30, iTableRemoveBtnY + 55 * (iSelLine - 1) + 45, 0);	

	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY + 55 * (iSelLine - 1), iTableAddAllBtnX + 35, iTableAddAllBtnY + 55 * (iSelLine - 1) + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY + 55 * (iSelLine - 1), iTableRemoveAllBtnX + 35, iTableRemoveAllBtnY + 55 * (iSelLine - 1) + 45, 0);
	
	String sList = "tr" + iSelected;
	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sList).index);
	ShowGoodsInfo(iCurGoodsIdx);
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
	SetNodeUsing("QTY_TAKEGIVE_BUTTON", false);
}

void OnHeaderClick()
{
	string sNode = GetEventData();
	int iCol = GetEventData();
}

void EndTooltip()
{
	CloseTooltipNew(); // всегда убирать, если был
	GameInterface.qty_edit.str = 0;
	SetCurrentNode("TABLE_LIST");
 	XI_WindowDisable("QTY_WINDOW", false);
	XI_WindowShow("QTY_WINDOW", true);
	bShowChangeWin = true;
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_TAKEGIVE_BUTTON", 0, "");
	SetNodeUsing("QTY_TAKEGIVE_BUTTON", false);
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

void ShowItemInfo()
{
	if(bShowChangeWin) // жмем окей, когда курсор на таблице
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
	}
}

int CheckAlchemy(string sItemID)
{
	ref 	rItem;
	aref 	rType;
	int 	Qty = 0;
	int 	iNum, itmReq, itmQty;
	string  sAttr, sItmId, sItmUse;
	bool	bOk = false;
	
	rItem = ItemsFromId(sItemId);
	makearef(rType, rItem.component);
	iNum = GetAttributesNum(rType);
	
	for(int i = 0; i < iNum; i++) // кол-во компонентов и прочего
	{	
		sAttr 		= GetAttributeName(GetAttributeN(rType, i));
		sItmId 		= rItem.component.(sAttr).id;
		itmReq      = sti(rItem.component.(sAttr).qty);
		sItmUse 	= rItem.component.(sAttr).use;
		
		if(CheckCharacterPerk(refCharacter, "Alchemy"))
		{
			if(rItem.component.(sAttr).id == "alchemy_tool") continue;
			if(rItem.component.(sAttr).id == "Mechanic_Tool") continue;
			if(rItem.component.(sAttr).id == "tailor_tool") continue;
		}
		
		if(sItmUse == "component")
		{
			itmQty 		= makeint(GetCharacterFreeItem(alchemy, sItmId)/itmReq);
			if(itmQty > 0)
			{
				if(itmQty < Qty && Qty != 0) 	Qty = itmQty;
				else
				{	
					if(Qty == 0) 				Qty = itmQty;
				}
				bOk = true;	
			}
			else
			{	
				Qty = 0; bOk = false; break;	
			}	
		}		
		else
		{
			if(GetCharacterFreeItem(alchemy, sItmId) >= itmReq) bOk = true;
			else 
			{												
				bOk = false;
				break;
			}	
		}	
	}		
	
	if(!bOk) return 0;
	return Qty;
}

// Жмакнули по кнопке "взять все"
void onGetAllBtnClick()
{
	aref 	rType;
	int 	iNum, itmReq;
	string  sAttr, sItmId, sItmUse;

	ref rItem 	= ItemsFromId(sCurItem);
	int Qty 	= CheckAlchemy(sCurItem);
	
	makearef(rType, rItem.component);
	iNum = GetAttributesNum(rType);
	
	for(int i = 0; i < iNum; i++) // кол-во компонентов и прочего
	{
		sAttr 		= GetAttributeName(GetAttributeN(rType, i));
		sItmId 		= rItem.component.(sAttr).id;
		itmReq      = sti(rItem.component.(sAttr).qty);		
		sItmUse 	= rItem.component.(sAttr).use;
		
		if(sItmUse == "component")
		{
			RemoveItems(alchemy, sItmId, Qty * itmReq);
		}
		if(sItmUse == "catalizator")
		{
			RemoveItems(alchemy, sItmId, 1);
		}	
		if(sItmUse == "additional")
		{
			AddItems(alchemy, sItmId, Qty);
		}	
	}

	int resultQty = Qty * sti(rItem.multiobject.qty);
	Perk_PowderFeel(rItem, &resultQty);
	Perk_Master(rItem, resultQty);

	AddItems(refCharacter, sCurItem, resultQty);
	WaitDate("", 0, 0, 0, 0, 15 + (5 * (Qty - 1)));
	Statistic_AddValue(refCharacter, "Alchemy", Qty);
	Achievment_SetStat(7, Qty);
	
	// ugeen 2016
	if(rItem.id == "mangarosapower")
	{
		if (!CheckAttribute(refCharacter, "Mangarosa.Alchemy.MP"))
		{
			refCharacter.Mangarosa.Alchemy.MP = true;
		}	
	}
	if(rItem.id == "mangarosafast")
	{
		if (!CheckAttribute(refCharacter, "Mangarosa.Alchemy.MF"))
		{
			refCharacter.Mangarosa.Alchemy.MF = true;
		}	
	}
	if(rItem.id == "mangarosatotal")
	{
		if (!CheckAttribute(refCharacter, "Mangarosa.Alchemy.MT"))
		{
			refCharacter.Mangarosa.Alchemy.MT = true;
		}		
	}
	
	AddToTable(ItemsFromId(sCurItem)); // Рефрешь таблицы
	
	if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
	else							SetSelectable("GETALL_BUTTON", false);
	
	GameInterface.TABLE_LIST.select = 1;
	GameInterface.TABLE_LIST.top = 0;
	
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST",0);
	// Рефреш позиции стрелочек
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON", 0, iTableAddBtnX, iTableAddBtnY, iTableAddBtnX + 30, iTableAddBtnY + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON", 0, iTableRemoveBtnX, iTableRemoveBtnY, iTableRemoveBtnX + 30, iTableRemoveBtnY + 45, 0);
	
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 35, iTableAddAllBtnY + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 35, iTableRemoveAllBtnY + 45, 0);
	// <-- Warship fix 10.06.09	
	SetCurrentNode("TABLE_LIST");
	EndTooltip();
	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.tr1.index);
	ShowGoodsInfo(iCurGoodsIdx);
}

// Нажали на табличной стрелочке "взять все предметы одного типа"
void onTableAddAllBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(alchemy, item);

	if(iItemsQty > 0) // fix
	{
		RemoveItems(alchemy, item, iItemsQty);
		// belamour
		if(iCurrentTabMode == 1) AddItems(refCharacter, item, iItemsQty);
		else PutItemMyBox("box"+sti(iCurrentTabMode-1), item, iItemsQty); 
		
		AddToTable(ItemsFromId(sCurItem));
		if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
		else							SetSelectable("GETALL_BUTTON", false);
		// belamour	
		if(iCurrentTabMode == 1) iCharQty = GetCharacterFreeItem(refCharacter, item);
		else iCharQty = CheckItemMyBox("box"+sti(iCurrentTabMode-1), item);
		iStoreQty = GetCharacterFreeItem(alchemy, item);	
	}
}

// Нажали на табличной стрелочке "отдать все предметы одного типа"
void onTableRemoveAllBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	
	int iItemsQty = 0;
	// belamour
	if(iCurrentTabMode == 1)  iItemsQty = GetCharacterFreeItem(refCharacter, item);
	else  iItemsQty = CheckItemMyBox("box"+sti(iCurrentTabMode-1), item);      
						
	if(iItemsQty > 0) 
	{
		// belamour
		if(iCurrentTabMode == 1) RemoveItems(refCharacter, item, iItemsQty);
		else GetItemMyBox("box"+sti(iCurrentTabMode-1), item, iItemsQty);
		
		AddItems(alchemy, item, iItemsQty);
		
		AddToTable(ItemsFromId(sCurItem));
		if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
		else							SetSelectable("GETALL_BUTTON", false);
		// belamour				
		if(iCurrentTabMode == 1) iCharQty = GetCharacterFreeItem(refCharacter, item);
		else iCharQty =  CheckItemMyBox("box"+sti(iCurrentTabMode-1), item); 
		iStoreQty = GetCharacterFreeItem(alchemy, item);	
	}		
}

// Нажали на табличной стрелочке "взять 1 ед. предмета одного типа"
void onTableAddBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(alchemy, item);
	if (iItemsQty > 1) iItemsQty = 1;// лок на 1 ед.
	if(iItemsQty > 0) // fix
	{
		RemoveItems(alchemy, item, iItemsQty);
		// belamour
		if(iCurrentTabMode == 1) AddItems(refCharacter, item, iItemsQty);
		else PutItemMyBox("box"+sti(iCurrentTabMode-1), item, iItemsQty); 
		
		AddToTable(ItemsFromId(sCurItem));
		if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
		else							SetSelectable("GETALL_BUTTON", false);
		// belamour	
		if(iCurrentTabMode == 1) iCharQty = GetCharacterFreeItem(refCharacter, item);
		else iCharQty = CheckItemMyBox("box"+sti(iCurrentTabMode-1), item);
		iStoreQty = GetCharacterFreeItem(alchemy, item);	
	}
}

// Нажали на табличной стрелочке "отдать 1 ед. предмета одного типа"
void onTableRemoveBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	
	int iItemsQty = 0;
	// belamour
	if(iCurrentTabMode == 1)  iItemsQty = GetCharacterFreeItem(refCharacter, item);
	else  iItemsQty = CheckItemMyBox("box"+sti(iCurrentTabMode-1), item);      
	if (iItemsQty > 1) iItemsQty = 1;// лок на 1 ед.
	if(iItemsQty > 0) 
	{
		// belamour
		if(iCurrentTabMode == 1) RemoveItems(refCharacter, item, iItemsQty);
		else GetItemMyBox("box"+sti(iCurrentTabMode-1), item, iItemsQty);
		
		AddItems(alchemy, item, iItemsQty);
		
		AddToTable(ItemsFromId(sCurItem));
		if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
		else							SetSelectable("GETALL_BUTTON", false);
		// belamour				
		if(iCurrentTabMode == 1) iCharQty = GetCharacterFreeItem(refCharacter, item);
		else iCharQty =  CheckItemMyBox("box"+sti(iCurrentTabMode-1), item); 
		iStoreQty = GetCharacterFreeItem(alchemy, item);	
	}		
}

// инфа о предмете
void ShowGoodsInfo(int iGoodIndex)
{
	ref    arItm = &Items[iGoodIndex];
	string sHeader = GetItemName(arItm);

	string describeStr = "";

	if(bBettaTestMode)
	{
		describeStr += "id = " + Items[iGoodIndex].id + NewStr();
	}
	describeStr += GetItemDescr(arItm);

	BuyOrSell = 0;
	SetFormatedText("QTY_TypeOperation", "");
	SetFormatedText("QTY_Result", "");
	GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", Items[iGoodIndex].picTexture, "itm" + Items[iGoodIndex].picIndex);
	SetFormatedText("QTY_CAPTION", sHeader);
	SetFormatedText("QTY_GOODS_INFO", describeStr);
	// belamour
	if(iCurrentTabMode == 1)iCharQty = GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id);
	else iCharQty = CheckItemMyBox("box"+sti(iCurrentTabMode-1), Items[iGoodIndex].id); 
	iStoreQty = GetCharacterFreeItem(alchemy, Items[iGoodIndex].id);
		
	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;	
}

void TransactionOK()
{
	int nTradeQuantity;
	String list;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if(BuyOrSell == 0)
	{
	    EndTooltip();
	    return;
	}

 	if(BuyOrSell == 1) // Забираем
	{
		RemoveItems(alchemy, Items[iCurGoodsIdx].id, nTradeQuantity);
		// belamour
		if(iCurrentTabMode == 1) AddItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
		else  PutItemMyBox("box"+sti(iCurrentTabMode-1), Items[iCurGoodsIdx].id,  nTradeQuantity);
		
	}
 	else // Отдаем
	{
		AddItems(alchemy, Items[iCurGoodsIdx].id, nTradeQuantity);
		// belamour
		if(iCurrentTabMode == 1)RemoveItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
		else GetItemMyBox("box"+sti(iCurrentTabMode-1), Items[iCurGoodsIdx].id, nTradeQuantity); 
	}
	
	AddToTable(ItemsFromId(sCurItem));
	if(CheckAlchemy(sCurItem) > 0) 	SetSelectable("GETALL_BUTTON", true);
	else							SetSelectable("GETALL_BUTTON", false);
	EndTooltip();
	
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния	
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
	SetCurrentNode("QTY_TAKEGIVE_BUTTON");	
}

void ChangeQTY_EDIT()
{
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	if(sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
		SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_TAKEGIVE_BUTTON", 0, "");
		SetNodeUsing("QTY_TAKEGIVE_BUTTON", false);
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

		    // SetFormatedText("QTY_TypeOperation", "Отдать");
			SetFormatedText("QTY_TypeOperation", XI_ConvertString("Give goods"));
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_TAKEGIVE_BUTTON", 0, "Give goods");
			SetNodeUsing("QTY_TAKEGIVE_BUTTON", true);
		}
		else
		{
			BuyOrSell = 1;
			
	        // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
			// SetFormatedText("QTY_TypeOperation", "Забрать");
			SetFormatedText("QTY_TypeOperation", XI_ConvertString("Take goods"));
			SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_TAKEGIVE_BUTTON", 0, "Take goods");
			SetNodeUsing("QTY_TAKEGIVE_BUTTON", true);
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
		SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"QTY_TAKEGIVE_BUTTON", 0, "");
		SetNodeUsing("QTY_TAKEGIVE_BUTTON", false);
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
}

void REMOVE_ALL_BUTTON()  
{
	if(!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iCharQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();	
}

void ADD_ALL_BUTTON()  
{
	if(!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();	
}

void REMOVE_BUTTON()  
{
	if(!bShowChangeWin) return;
	
	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = -1;
	}
	else
	{
		if(BuyOrSell == -1)
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

void ADD_BUTTON()  
{
	if(!bShowChangeWin) return;
	
	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = 1;
	}
	else
	{
		if(BuyOrSell == 1)
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

// belamour компоненты из сундуков -->
void procTabChange()
{
	int comIndex = GetEventData();
	String nodName = GetEventData();
	SetCurrentNode("TABLE_LIST");
	
	switch(nodName)
	{
		case "TABSTR_1":
			SetControlsTabMode(1);
		break;
		
		case "TABSTR_2":
			SetControlsTabMode(2);
		break;
		
		case "TABSTR_3":
			SetControlsTabMode(3);
		break;
		
		case "TABSTR_4":
			SetControlsTabMode(4);
		break;
		
		case "TABSTR_5":
			SetControlsTabMode(5);
		break;
	}
}

void SetControlsTabMode(int _mode)
{
	int nColorMain = argb(255,196,196,196);
	int nColorNone = argb(255,128,128,128);
	int nColorSelected = argb(255,255,255,255);
	
	int colorArray[5];
	colorArray[0] = nColorMain;
	
	int chestCount = CountChestsInCabin(Get_My_Cabin());
	for (int i = 1; i < 5; i++)
	{
		if (i <= chestCount)
			colorArray[i] = nColorMain;
		else
			colorArray[i] = nColorNone;
	}

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
	
	if(_mode > -1)
		colorArray[_mode - 1] = nColorSelected;

	switch (_mode)
	{
		case 1:
			sPic1 = "TabSelected";
			sPic6 = "TabSelectedMark";
		break;
		case 2:
			sPic2 = "TabSelected";
			sPic7 = "TabSelectedMark";
		break;
		case 3:
			sPic3 = "TabSelected";
			sPic8 = "TabSelectedMark";
		break;
		case 4:
			sPic4 = "TabSelected";
			sPic9 = "TabSelectedMark";
		break;
		case 5:
			sPic5 = "TabSelected";
			sPic10 = "TabSelectedMark";
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
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,colorArray[0]);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,colorArray[1]);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_3", 8,0,colorArray[2]);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_4", 8,0,colorArray[3]);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_5", 8,0,colorArray[4]);
	
	iCurrentTabMode = _mode;
	
	AddToTable(ItemsFromID(sCurItem));
}

// количество сундуков в каюте
int CountChestsInCabin(string cabinType)
{
	if(PChar.location != Get_My_Cabin()) return 0;
	
	aref al;
	int num = 0;
	for(int i = 1; i < 5; i++)
	{
		if(FindLocator(cabinType, "box"+i, &al, true)) num++;
	}
	return num;
}
// <-- belamour