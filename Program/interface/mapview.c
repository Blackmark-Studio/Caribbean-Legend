// Ugeen && Warship --> интерфейс картографического атласа
// Sith отличная карта интегрирована в атлас
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню кнопками Q и E
/// bestmap ===>
//settings file
#include "activemap_settings.h"
//changing this requires frame resizing
#define TRADEASSISTANT_MAXGOODS 5

string CurRow, CurTable;
ref xi_refCharacter; 
int iSelected = 1;
int colonyindex = -1;
int  iGoodIndex;
///espkk. utils -->
//cuz the game doesn't use built-in language mechanism
#define LANG_FILE "activemap"
string GetLangStr(string sParam)
{
	string sFile = LANG_FILE + "_";
	if(findSubStr(VERSION_NUMBER2, "ENG", 0) != -1)
		sFile += "en";
	else
		sfile += "ru";
	sFile+=".txt";
	
	return GetConvertStr(sParam, sFile);
}

//float to str conversion with one decimal place
string FloatToStr(float value)
{
	if(value == makeint(value))
		return "" + makeint(value);
	return "" + makefloat(makeint((value+0.5)*10))/10;
}

void AddImageToImageList(string sImgName, string sPicGroup, string sPic, float X, float Y, int Width, int Height)
{
	GameInterface.MAP.imagelist.(sImgName).group = sPicGroup;
	GameInterface.MAP.imagelist.(sImgName).pic = sPic;
	GameInterface.MAP.imagelist.(sImgName).x = X;
	GameInterface.MAP.imagelist.(sImgName).y = Y;
	GameInterface.MAP.imagelist.(sImgName).width = Width;
	GameInterface.MAP.imagelist.(sImgName).height = Height;
}

//Whether on worldmap or not. Supports Hook's mod position fix
void GetCorrectShipCoords(ref X, ref Y)
{
	if(IsEntity(&worldMap))
	{
		X = sti(worldMap.playerShipX);
		Y = -sti(worldMap.playerShipZ);
	}
		else
	{
		if (!bSeaActive && CheckAttribute(pchar, "shipx"))
		{
			X = GetSeaShipX(stf(pchar.shipx));
			Y = -GetSeaShipZ(stf(pchar.shipz));
		}
		else
		{
			X = GetSeaShipX(stf(pchar.Ship.Pos.X));
			Y = -GetSeaShipZ(stf(pchar.Ship.Pos.Z));
		}
	}
	
	X+=1000;
	Y+=1000;
}

//Correct version of GetDistanceToColony2D
int _GetDistanceToColony2D(string _sColony)
{
	ref rColony = GetColonyRefByID(_sColony);
	string sColonyIslandID = rColony.Island;
	string sColonyTown = _sColony + "_town";

	if(_sColony == "FortOrange") sColonyTown = "Shore36";
	if(_sColony == "LaVega") sColonyTown = "LaVega_town";

	float X1, Z1;
	GetCorrectShipCoords(&X1, &Z1)
	float X2 = makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.x)+1000;
	float Z2 = -makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.z)+1000;
	
	return makeint(GetDistance2D(X1, Z1, X2, Z2));
}
///espkk. utils <--
/// bestmap <===

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchMapViewScreen"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleMapView";
	
	xi_refCharacter = pchar;
	
	ShowBestMapWindow();
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);	
	SetEventHandler("SelectRColony","SelectRColony",0);
	SetEventHandler("HideRColony","HideRColony",0);
	SetEventHandler("FillTable","FillTable",0);
	SetEventHandler("HideTable","HideTable",0);
	SetEventHandler("DoTP","DoTP",0);
	
    XI_RegistryExitKey("IExit_F2");
	FillMapsTable();
	
	if(CheckCharacterItem(pchar, "MapsAtlas")) // проверяем наличие атласа в инвентаре
	{
		XI_WindowShow("MAIN_WINDOW", true);
		SetNodeUsing("STR_NOMAP", false);
	}
	else
	{
		XI_WindowShow("MAIN_WINDOW", false);
		SetNodeUsing("STR_NOMAP", true);
	}
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
	//Show boundaries
	if(SHOW_BOUNDARIES == 1)
	{
		if(LanguageGetLanguage() != "Russian"){
			SetNewPicture("BOUNDARIES", "interfaces\maps\english\" + "map_good_boundaries.tga");
		} else {
			SetNewPicture("BOUNDARIES", "interfaces\maps\russian\" + "map_good_boundaries.tga");
		}
		SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "BOUNDARIES", 4,
			argb(makeint(255/(makefloat(100)/BOUNDARIES_OPACITY)), BOUNDARIES_R, BOUNDARIES_G, BOUNDARIES_B));
	}
	SetAlertMarks(xi_refCharacter);
}

// гуляем по меню кнопками Q и E
void ProcessInterfaceControls() 
{
    string controlName = GetEventData();
 
	if (controlName == "InterfaceGoLeft") {
        IDoExit(RC_INTERFACE_TO_QUESTBOOK);
    }
	if (controlName == "InterfaceGoRight") {
        IDoExit(RC_INTERFACE_ABILITIES);
    }
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("SelectRColony","SelectRColony");
	DelEventHandler("HideRColony","HideRColony");
	DelEventHandler("FillTable","FillTable");
	DelEventHandler("HideTable","HideTable");
	DelEventHandler("DoTP","DoTP");	

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
		case "TABLE_MAPS":
			if(comName == "click")
			{
				nodName = "TABLE_MAPS";
			}
		break;
		case "MAPS":
			if (CheckAttribute(GameInterface, "TABLE_MAPS." + CurRow + ".index")){
				iGoodIndex = sti(GameInterface.TABLE_MAPS.(CurRow).index);
			}
			ref itmRef = &Items[iGoodIndex];
			if(CheckAttribute(itmRef,"ID") && itmRef.ID == "map_best")
			{
				if(comName == "click")
				{
					SelectRColony();
				}
				if(comName == "rclick")
				{
					if (bBettaTestMode) FillTable();
				}
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_INVENTORY" || nodName == "I_SHIP" || nodName == "I_QUESTBOOK" ||
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
	// boal new menu 31.12.04 -->
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void FillMapsTable() 
{
	int n, i;
	string row;
	string sGood, selectedId = "";
	int  idLngFile;
	bool ok = true;
	aref rootItems, arItem;
	aref  curItem;
		
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");	
	if(CheckAttribute(pchar, "showlastmap")) { selectedId = pchar.showlastmap; }
	// belamour cle выбираем карту  в зависимости от местоположения
	if(IsEntity(&worldMap))
	{
		IsEquipCharacterByMap(xi_refCharacter, "map_bad")) selectedId = "map_bad";
		IsEquipCharacterByMap(xi_refCharacter, "map_normal")) selectedId = "map_normal";
		IsEquipCharacterByMap(xi_refCharacter, "Map_Best")) selectedId = "Map_Best";
	}
	else
	{
		if(FindAtlasMap(&selectedId)) {}
		else
		{
			if(CheckAttribute(pchar, "showlastmap")) { selectedId = pchar.showlastmap; }
		}
	}
	
	// GameInterface.TABLE_MAPS.hr.td1.str = "";
	GameInterface.TABLE_MAPS.hr.td1.str = XI_ConvertString("Select map");
	Table_UpdateWindow("TABLE_MAPS");

	// Заполним картами
	makearef(rootItems, xi_refCharacter.Items);
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);
		if (Items_FindItem(GetAttributeName(curItem), &arItem)>=0 )
		{
			row = "tr" + n;
			// Index = FindItem("Map_Best");
			sGood = arItem.id;			
			if(CheckAttribute(arItem,"mapType") && IsEquipCharacterByMap(xi_refCharacter, arItem.id))
			{
                ok = true;
			}
            else ok = false;
			if (arItem.ItemType != "MAP" || !ok) continue;			

			if (selectedId == sGood) { iSelected = n; }			
			if (GetCharacterItem(xi_refCharacter, sGood) > 0)
			{					
				GameInterface.TABLE_MAPS.(row).index = GetItemIndex(arItem.id);				
				GameInterface.TABLE_MAPS.(row).td1.textoffset = "0,0";
				GameInterface.TABLE_MAPS.(row).td1.str = LanguageConvertString(idLngFile, arItem.name);
				n++;							
			}
		}
    }		
	GameInterface.TABLE_MAPS.select = iSelected;
	CurRow   =  "tr" + (iSelected);    
	SetNewMapPicture();
		
	Table_UpdateWindow("TABLE_MAPS");
	LanguageCloseFile(idLngFile);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
	CurTable = sControl;
    CurRow   =  "tr" + (iSelected);    
    if (CurTable != "TABLE_LOCS") SetNewMapPicture();
}

void SetNewMapPicture()
{
	if (CheckAttribute(GameInterface, "TABLE_MAPS." + CurRow + ".index")){
		iGoodIndex = sti(GameInterface.TABLE_MAPS.(CurRow).index);
	}
	ref itmRef = &Items[iGoodIndex];
	
	if (CheckAttribute(itmRef, "groupID"))
	{
		string itmGroup = itmRef.groupID;
		if (itmGroup == MAPS_ITEM_TYPE)
		{
			if (itmRef.id != "Map_Best")
			{
				if(LanguageGetLanguage() != "Russian"){
					SetNewPicture("MAPS", "interfaces\Maps\english\" + itmRef.imageTga + ".tga");
				} else {
					SetNewPicture("MAPS", "interfaces\Maps\russian\" + itmRef.imageTga + ".tga");
				}
				XI_WindowShow("MAINBESTMAP_WINDOW", false);
			}
			else
			{
				SetNewPicture("MAPS", "");
				XI_WindowShow("MAINBESTMAP_WINDOW", true);
				if(LanguageGetLanguage() != "Russian"){
					SetNewPicture("MAIN_MAP", "interfaces\Maps\english\" + "map_good.tga");
				} else {
					SetNewPicture("MAIN_MAP", "interfaces\Maps\russian\" + "map_good.tga");
				}
			}
			pchar.showlastmap = itmRef.id;							
		}
	}
}

void ShowInfoWindow()
{
	if (CheckAttribute(GameInterface, "TABLE_MAPS." + CurRow + ".index")){
		iGoodIndex = sti(GameInterface.TABLE_MAPS.(CurRow).index);
	}
	ref  itmRef = &Items[iGoodIndex];
	int  idLngFile;

	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sAttributeName;
	sPicture = "-1";

	idLngFile = LanguageOpenFile("ItemsDescribe.txt");	
	switch (sCurrentNode)
	{
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
		case "TABLE_MAPS":
			sGroup = itmRef.picTexture; 
			sGroupPicture = "itm" + itmRef.picIndex
			sHeader = LanguageConvertString(idLngFile, itmRef.name);
			sText1  = GetItemDescribe(iGoodIndex); 
		break;
		case "MAP_INFO":
			if (itmRef.id != "Map_Best")
			{
				sHeader = XI_ConvertString("Atlas");
				sText1 = XI_ConvertString("Atlas_Descr");
			}
			else
			{
				sHeader = XI_ConvertString("BestMap");
				sText1 = XI_ConvertString("BestMap_Descr");
			}
		break;
		// <--- sith
	}
	LanguageCloseFile(idLngFile);
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 128, 128);
}

void HideInfoWindow()
{
	CloseTooltip();
	HideRColony();
}

/// bestmap section ===>
void ShowBestMapWindow()
{
	string sColony, sPic, sPicGroup, sSiegeCol;
	int Width, Height;
	float X, Y;
	ref rColony;

	for(int i=0; i<MAX_COLONIES; i++)
	{
		rColony = &colonies[i];
		sColony = rColony.id;
		
		string sColonyIslandID = rColony.Island;
		string sColonyTown = sColony + "_town";
		
		if(sColony == "Pearl") continue;
		if(sColony == "Tenotchitlan") continue;
		if(sColony == "Dominica") continue;
		if(sColony == "Terks") continue;
		if(sColony == "Caiman") continue;
		if(sColony == "LostShipsCity") continue;
		if(sColony == "KhaelRoa") continue;
		if(sColony == "LosTeques") continue;
		if(sColony == "Ksochitam") continue;
		if(sColony == "RockIsland") continue;
		if(sColony == "SantaQuiteria") continue;
		if(sColony == "IslaDeVieques") continue;
		if(sColony == "SanAndres") continue;
		if(sColony == "Is") continue;
		if(sColony == "IslaMona" && !CheckAttribute(CharacterFromID("Islamona_carpenter"), "Storage.Activate")) continue;

		if(sColony == "IslaMona")
			sPic = "Smuggler";
		else
			sPic = GetNationNameByType(sti(rColony.nation));
			
		if(sColony != "FortOrange" && sColony != "LaVega" && sColony != "IslaMona")
		{
			X = makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.x)+1000;
			Y = -makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.z)+1000;
		}
		
		if(sColony == "FortOrange")
		{
			X = 600;
			Y = 1080;
		}
		
		if(sColony == "LaVega")
		{
			X = 1150;
			Y = 350;
		}

		if(sColony == "IslaMona")
		{
			X = 1000;
			Y = 829;
		}
	
		//Draw colony on the map
		AddImageToImageList(sColony, "NATIONS_SMALL", sPic, X, Y, 24, 24);

		ref chref;
		for (int iChar=1; iChar<MAX_CHARACTERS; iChar++)
		{
			makeref(chref, Characters[iChar]);
			
			//Draw packhouses
			if (CheckAttribute(chref, "Storage.Activate"))
			{
				if (sColony == chref.city)
				{
					AddImageToImageList(sColony + "_storage", "ICONS", "ship capacity icon", X, Y + 50, 24, 24);
				}
			}
			
			//Draw ships
    		if (CheckAttribute(chref, "ShipInStockMan"))
    		{
				bool bIslaMonaShip = (sColony == "IslaMona") && (chref.ShipInStockMan == "Islamona_carpenter"); //stupid compiler >:|
                if (chref.ShipInStockMan == (sColony + "_PortMan") || bIslaMonaShip)
				{
					AddImageToImageList(sColony + "_shipinstock", "ICONS", "ship stored icon", X - 35, Y, 24, 24);
				}
			}
		}
		
		//Draw our moneylenders
		aref quests;
		int  nQuestsNum, n;
		string sQuestName, sType;
		for(int iType=0; iType<2; iType++)
		{
			if(iType)
				sType = "Quest.Loans";
			else
				sType = "Quest.Deposits";

			if (CheckAttribute(pchar, sType))
			{
				makearef(quests, pchar.(sType));
				nQuestsNum = GetAttributesNum(quests);

				for(n = 0; n < nQuestsNum; n++)
				{
					sQuestName = GetAttributeName(GetAttributeN(quests,n));
					if (sColony == sQuestName)
					{
						AddImageToImageList(sColony + "_money", "ICONS", "commerce skill icon", X, Y - 55, 24, 24);

						iType = 2; //stop for
						break;
					}
				}
			}
		}
		
		//Draw sieges
		if(CheckAttribute(rColony, "siege") && sti(rColony.siege) != -1)
		{
			sSiegeCol = "SiegeOn" + sColony;
			AddImageToImageList(sSiegeCol, "ICONS_SPEC", "weapon button", X + 35, Y - 3, 24, 24);
			
			if(CheckAttribute(&NullCharacter, "siege.nation"))
			{
				string sSiegeNation = GetNationNameByType(sti(NullCharacter.Siege.nation));
				sSiegeCol = sSiegeCol + "NationPic" + sSiegeNation;
				AddImageToImageList(sSiegeCol, "NATIONS_SMALL", sSiegeNation, X + 70, Y, 24, 24);
			}
		}
	}
	
	//Draw our ship
	GetCorrectShipCoords(&X, &Y);
	AddImageToImageList("PShip", "ICONS", "ship class icon", X, Y, 32, 32);
}
void DoTP()
{
	string ID = GameInterface.TABLE_LOCS.(CurRow).td1.str;
	setCharacterShipLocation(pchar, ID);
	setWDMPointXZ(ID);
	DoQuestReloadToLocation(ID, "reload", "reload1", "");
}

void HideTable()
{
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowDisable("MAINBESTMAP_WINDOW", true);
	XI_WindowDisable("TP_WINDOW", true);
	XI_WindowShow("TP_WINDOW", false);
}

void FillTable()
{
	if (!bBettaTestMode) return;
	float fMouseX = stf(GameInterface.mousepos.x)-480;
	float fMouseY = stf(GameInterface.mousepos.y)-120;
	
	//Getting correct image offsets
	float fOffsetX, fOffsetY;
	GetXYWindowOffset(&fOffsetX, &fOffsetY);

	fMouseX = (fMouseX - fOffsetX) * stf(GameInterface.MAP.scale.x);
	fMouseY = (fMouseY - fOffsetY) * stf(GameInterface.MAP.scale.y);


	//Check if clicked on colony
	string sColony = "";
	string ssColony = "";
	for(int i = 0; i < MAX_COLONIES; i++)
	{
		sColony = colonies[i].id;
		if(CheckAttribute(&GameInterface, "MAP.imagelist." + sColony))
		{
			// LDH 21Mar17 enlarge click spot by 10 each direction
			if(fMouseX >= stf(GameInterface.MAP.imagelist.(sColony).x) + 30)	// 30
			{
				if(fMouseX <= stf(GameInterface.MAP.imagelist.(sColony).x) + 60.0)	// 50
				{
					if(fMouseY >= stf(GameInterface.MAP.imagelist.(sColony).y))	// 0
					{
						if(fMouseY <= stf(GameInterface.MAP.imagelist.(sColony).y) + 60.0)	// 50
						{
							if(sColony != "Panama" && sColony != "IslaMona" && sColony != "KhaelRoa" && sColony != "Caiman")
							{
								colonyindex = i;
								XI_WindowShow("TP_WINDOW", true);
								XI_WindowDisable("TP_WINDOW", false);
								SetFormatedText("LOCS_CAPTION", "Локации колонии");
								Table_Clear("TABLE_LOCS",false,true,false);
								GameInterface.TABLE_LOCS.select = 0;
								GameInterface.TABLE_LOCS.top = 0;
								int nFile = LanguageOpenFile("LocLables.txt");
								ref rColony = &colonies[i];
								string island = rColony.island;
								string row = "";
								int n = 1;
								GameInterface.TABLE_LOCS.hr.td1.str = "ID";
								GameInterface.TABLE_LOCS.hr.td2.str = "Label";
								for(int z=0; z<MAX_LOCATIONS; z++)
								{
									if (GiveArealByLocation(&locations[z]) == island)
									{
										row = "tr" + n;
										GameInterface.TABLE_LOCS.(row).td1.str = locations[z].id;
										GameInterface.TABLE_LOCS.(row).td2.str = LanguageConvertString(nFile, locations[z].id.label);
										if (HasSubStr(locations[z].id.label,"upstairs")) GameInterface.TABLE_LOCS.(row).td2.str = "Комната наверху таверны";
										n++;
									}
								}
								Table_UpdateWindow("TABLE_LOCS");
								break;
							}
						}
					}
				}
			}
		}
	}
	if (colonyindex != i)
	{
		if (fMouseX >= 69.0 && fMouseX <= 155.0 && fMouseY >= 1275.0 && fMouseY <= 1380.0)
		{
			setCharacterShipLocation(pchar, "Shore53");
			setWDMPointXZ("Shore53");
			ssColony = "Tenotchitlan";
		}
		if (fMouseX >= 1775.0 && fMouseX <= 1853.0 && fMouseY >= 1240.0 && fMouseY <= 1352.0)
		{
			setCharacterShipLocation(pchar, "Shore27");
			setWDMPointXZ("Shore27");
			ssColony = "Dominica";
		}
		if (fMouseX >= 1436.0 && fMouseX <= 1534.0 && fMouseY >= 50.0 && fMouseY <= 143.0)
		{
			setCharacterShipLocation(pchar, "Shore56");
			setWDMPointXZ("Shore56");
			ssColony = "Terks";
		}
		if (fMouseX >= 2.0 && fMouseX <= 77.0 && fMouseY >= 1051.0 && fMouseY <= 1194.0)
		{
			setCharacterShipLocation(pchar, "Shore9");
			setWDMPointXZ("Shore9");
			ssColony = "Pearl";
		}
		if (fMouseX >= 215.0 && fMouseX <= 351.0 && fMouseY >= 1765.0 && fMouseY <= 1912.0)
		{
			setCharacterShipLocation(pchar, "Shore55");
			setWDMPointXZ("Shore55");
			ssColony = "Pearl";
		}
		if (fMouseX >= 515.0 && fMouseX <= 617.0 && fMouseY >= 610.0 && fMouseY <= 722.0)
		{
			setCharacterShipLocation(pchar, "Shore17");
			setWDMPointXZ("Shore17");
			ssColony = "Caiman";
		}
		if (fMouseX >= 648.0 && fMouseX <= 694.0 && fMouseY >= 1955.0 && fMouseY <= 2028.0)
		{
			setCharacterShipLocation(pchar, "PortoBello_town");
			setWDMPointXZ("PortoBello_town");
			ssColony = "Panama";
		}
		if (fMouseX >= 973.0 && fMouseX <= 1031.0 && fMouseY >= 908.0 && fMouseY <= 966.0)
		{
			setCharacterShipLocation(pchar, "MountainPath");
			setWDMPointXZ("MountainPath");
			ssColony = "Reefs";
		}
		if (fMouseX >= 1079.0 && fMouseX <= 1135.0 && fMouseY >= 792.0 && fMouseY <= 861.0)
		{
			setCharacterShipLocation(pchar, "DeckWithReefs");
			setWDMPointXZ("DeckWithReefs");
			ssColony = "Reefs";
		}
		if (fMouseX >= 1811.0 && fMouseX <= 1883.0 && fMouseY >= 714.0 && fMouseY <= 780.0)
		{
			setCharacterShipLocation(pchar, "KhaelRoa_port");
			setWDMPointXZ("KhaelRoa_port");
			ssColony = "KhaelRoa";
		}
		if (fMouseX >= 47.0 && fMouseX <= 207.0 && fMouseY >= 19.0 && fMouseY <= 197.0)
		{
			setCharacterShipLocation(pchar, "LostShipsCity_town");
			setWDMPointXZ("LostShipsCity_town");
			ssColony = "LostShipsCity";
		}
		if (fMouseX >= 1568.0 && fMouseX <= 1642.0 && fMouseY >= 1074.0 && fMouseY <= 1170.0)
		{
			setCharacterShipLocation(pchar, "Shore31");
			setWDMPointXZ("Shore31");
			ssColony = "MarieGalante";
		}
		if (fMouseX >= 1916.0 && fMouseX <= 1996.0 && fMouseY >= 1715.0 && fMouseY <= 1812.0)
		{
			setCharacterShipLocation(pchar, "Shore59");
			setWDMPointXZ("Shore59");
			ssColony = "Tobago";
		}
		if (fMouseX >= 1627.0 && fMouseX <= 1669.0 && fMouseY >= 1941.0 && fMouseY <= 1986.0)
		{
			setCharacterShipLocation(pchar, "Shore20");
			setWDMPointXZ("Shore20");
			ssColony = "LosTeques";
		}
		if (fMouseX >= 1023.0 && fMouseX <= 1052.0 && fMouseY >= 840.0 && fMouseY <= 901.0)
		{
			setCharacterShipLocation(pchar, "Shore75");
			setWDMPointXZ("Shore75");
			ssColony = "IslaMona";
		}
		if (fMouseX >= 414.0 && fMouseX <= 485.0 && fMouseY >= 906.0 && fMouseY <= 995.0)
		{
			setCharacterShipLocation(pchar, "Shore65");
			setWDMPointXZ("Shore65");
			ssColony = "Ksochitam";
		}
		if (fMouseX >= 1097.0 && fMouseX <= 1180.0 && fMouseY >= 1143.0 && fMouseY <= 1254.0)
		{
			setCharacterShipLocation(pchar, "Shore74");
			setWDMPointXZ("Shore74");
			ssColony = "IslaDeVieques";
		}
		if (ssColony == "") return;
		XI_WindowShow("TP_WINDOW", true);
		XI_WindowDisable("TP_WINDOW", false);
		SetFormatedText("LOCS_CAPTION", "Локации колонии");
		Table_Clear("TABLE_LOCS",false,true,false);
		GameInterface.TABLE_LOCS.select = 0;
		GameInterface.TABLE_LOCS.top = 0;
		int nFile1 = LanguageOpenFile("LocLables.txt");
		string row1 = "";
		int x = 1;
		GameInterface.TABLE_LOCS.hr.td1.str = "ID";
		GameInterface.TABLE_LOCS.hr.td2.str = "Label";
		for(int y=0; y<MAX_LOCATIONS; y++)
		{
			if (GiveArealByLocation(&locations[y]) == ssColony || CheckForIslandID(&locations[y]) == ssColony)
			{
				row1 = "tr" + x;
				GameInterface.TABLE_LOCS.(row1).td1.str = locations[y].id;
				GameInterface.TABLE_LOCS.(row1).td2.str = LanguageConvertString(nFile1, locations[y].id.label);
				if (HasSubStr(locations[y].id.label,"upstairs")) GameInterface.TABLE_LOCS.(row1).td2.str = "Комната наверху таверны";
				x++;
			}
		}
		Table_UpdateWindow("TABLE_LOCS");
	}
	SetCurrentNode("TABLE_LOCS");
}

string CheckForIslandID(ref location)
{
	if (CheckAttribute(location,"islandid")) return location.islandid;
	return "none";
}

void SelectRColony()
{
	float fMouseX = stf(GameInterface.mousepos.x)-480;
	float fMouseY = stf(GameInterface.mousepos.y)-120;	
	//Getting correct image offsets
	float fOffsetX, fOffsetY;
	GetXYWindowOffset(&fOffsetX, &fOffsetY);

	fMouseX = (fMouseX - fOffsetX) * stf(GameInterface.MAP.scale.x);
	fMouseY = (fMouseY - fOffsetY) * stf(GameInterface.MAP.scale.y);


	//Check if clicked on colony
	string sColony;
	for(int i = 0; i < MAX_COLONIES; i++)
	{
		sColony = colonies[i].id;
		if(CheckAttribute(&GameInterface, "MAP.imagelist." + sColony))
		{
			// LDH 21Mar17 enlarge click spot by 10 each direction
			if(fMouseX >= stf(GameInterface.MAP.imagelist.(sColony).x) + 30)	// 30
			{
				if(fMouseX <= stf(GameInterface.MAP.imagelist.(sColony).x) + 60.0)	// 50
				{
					if(fMouseY >= stf(GameInterface.MAP.imagelist.(sColony).y))	// 0
					{
						if(fMouseY <= stf(GameInterface.MAP.imagelist.(sColony).y) + 60.0)	// 50
						{
							if(sColony != "Panama" && sColony != "IslaMona")
							{
								XI_WindowDisable("MAINBESTMAP_WINDOW", true);
								XI_WindowDisable("INFO_WINDOW", false);
								XI_WindowShow("INFO_WINDOW", true);
								colonyindex = i;
								ShowColonyInfo(i);
							}
						}
					}
				}
			}
		}
	}
	Log_TestInfo(fMouseX+"/"+fMouseY);
	if (bBettaTestMode)
	{
		if (fMouseX >= 69.0 && fMouseX <= 155.0 && fMouseY >= 1275.0 && fMouseY <= 1380.0)
		{
			setCharacterShipLocation(pchar, "Shore53");
			setWDMPointXZ("Shore53");
			DoQuestReloadToLocation("Tenochtitlan", "reload", "reload1", "");
		}
		if (fMouseX >= 1775.0 && fMouseX <= 1853.0 && fMouseY >= 1240.0 && fMouseY <= 1352.0)
		{
			setCharacterShipLocation(pchar, "Shore27");
			setWDMPointXZ("Shore27");
			DoQuestReloadToLocation("Shore27", "reload", "reload1", "");
		}
		if (fMouseX >= 1436.0 && fMouseX <= 1534.0 && fMouseY >= 50.0 && fMouseY <= 143.0)
		{
			setCharacterShipLocation(pchar, "Shore56");
			setWDMPointXZ("Shore56");
			DoQuestReloadToLocation("Shore56", "reload", "reload1", "");
		}
		if (fMouseX >= 2.0 && fMouseX <= 77.0 && fMouseY >= 1051.0 && fMouseY <= 1194.0)
		{
			setCharacterShipLocation(pchar, "Shore9");
			setWDMPointXZ("Shore9");
			DoQuestReloadToLocation("Pearl_town_1", "reload", "reload1", "");
		}
		if (fMouseX >= 215.0 && fMouseX <= 351.0 && fMouseY >= 1765.0 && fMouseY <= 1912.0)
		{
			setCharacterShipLocation(pchar, "Shore55");
			setWDMPointXZ("Shore55");
			DoQuestReloadToLocation("Pearl_town_2", "reload", "reload1", "");
		}
		if (fMouseX >= 515.0 && fMouseX <= 617.0 && fMouseY >= 610.0 && fMouseY <= 722.0)
		{
			setCharacterShipLocation(pchar, "Shore17");
			setWDMPointXZ("Shore17");
			DoQuestReloadToLocation("Shore17", "reload", "reload1", "");
		}
		if (fMouseX >= 648.0 && fMouseX <= 694.0 && fMouseY >= 1955.0 && fMouseY <= 2028.0)
		{
			setCharacterShipLocation(pchar, "PortoBello_town");
			setWDMPointXZ("PortoBello_town");
			DoQuestReloadToLocation("Panama_town", "reload", "reload1", "");
		}
		if (fMouseX >= 973.0 && fMouseX <= 1031.0 && fMouseY >= 908.0 && fMouseY <= 966.0)
		{
			setCharacterShipLocation(pchar, "MountainPath");
			setWDMPointXZ("MountainPath");
			DoQuestReloadToLocation("MountainPath", "reload", "reload1", "");
		}
		if (fMouseX >= 1079.0 && fMouseX <= 1135.0 && fMouseY >= 792.0 && fMouseY <= 861.0)
		{
			setCharacterShipLocation(pchar, "DeckWithReefs");
			setWDMPointXZ("DeckWithReefs");
			DoQuestReloadToLocation("DeckWithReefs", "reload", "reload1", "");
		}
		if (fMouseX >= 1811.0 && fMouseX <= 1883.0 && fMouseY >= 714.0 && fMouseY <= 780.0)
		{
			setCharacterShipLocation(pchar, "KhaelRoa_port");
			setWDMPointXZ("KhaelRoa_port");
			DoQuestReloadToLocation("KhaelRoa_port", "reload", "reload1", "");
		}
		if (fMouseX >= 47.0 && fMouseX <= 207.0 && fMouseY >= 19.0 && fMouseY <= 197.0)
		{
			setCharacterShipLocation(pchar, "LostShipsCity_town");
			setWDMPointXZ("LostShipsCity_town");
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload1", "");
		}
		if (fMouseX >= 1568.0 && fMouseX <= 1642.0 && fMouseY >= 1074.0 && fMouseY <= 1170.0)
		{
			setCharacterShipLocation(pchar, "Shore31");
			setWDMPointXZ("Shore31");
			DoQuestReloadToLocation("Shore31", "reload", "reload1", "");
		}
		if (fMouseX >= 1916.0 && fMouseX <= 1996.0 && fMouseY >= 1715.0 && fMouseY <= 1812.0)
		{
			setCharacterShipLocation(pchar, "Shore59");
			setWDMPointXZ("Shore59");
			DoQuestReloadToLocation("Shore59", "reload", "reload1", "");
		}
		if (fMouseX >= 1627.0 && fMouseX <= 1669.0 && fMouseY >= 1941.0 && fMouseY <= 1986.0)
		{
			setCharacterShipLocation(pchar, "Shore20");
			setWDMPointXZ("Shore20");
			DoQuestReloadToLocation("Shore20", "reload", "reload1", "");
		}
		if (fMouseX >= 1023.0 && fMouseX <= 1052.0 && fMouseY >= 840.0 && fMouseY <= 901.0)
		{
			setCharacterShipLocation(pchar, "Shore75");
			setWDMPointXZ("Shore75");
			DoQuestReloadToLocation("Shore75", "reload", "reload1", "");
		}
		if (fMouseX >= 414.0 && fMouseX <= 485.0 && fMouseY >= 906.0 && fMouseY <= 995.0)
		{
			setCharacterShipLocation(pchar, "Shore65");
			setWDMPointXZ("Shore65");
			DoQuestReloadToLocation("Shore65", "reload", "reload1", "");
		}
		if (fMouseX >= 1097.0 && fMouseX <= 1180.0 && fMouseY >= 1143.0 && fMouseY <= 1254.0)
		{
			setCharacterShipLocation(pchar, "Shore74");
			setWDMPointXZ("Shore74");
			DoQuestReloadToLocation("Shore74", "reload", "reload1", "");
		}
	}
}

void HideRColony()
{
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowDisable("MAINBESTMAP_WINDOW", true);
	XI_WindowDisable("INFO_WINDOW", true);
	XI_WindowShow("INFO_WINDOW", false);
	// телепорт на правую кнопку
	// if (bBettaTestMode && colonyindex != -1)
	// {
		// setCharacterShipLocation(pchar, colonies[colonyindex].from_sea));
		// setWDMPointXZ(colonies[colonyindex].from_sea);
		// DoQuestReloadToLocation(colonies[colonyindex].from_sea, "reload", "reload1", "");
	// }
}

void ShowColonyInfo(int iColony)
{
	string sText;
	ref sld, rColony;
	rColony = &colonies[iColony];
	string sColony = colonies[iColony].id;
	int iColor;

	//Clean up -->
	sText = XI_ConvertString("Colony" + sColony);
	SetFormatedText("INFO_CAPTION", sText);

	sText = GetNationNameByType(sti(rColony.nation));
	SetNewGroupPicture("INFO_NATION_PICTURE", "NATIONS", sText);

	SetFormatedText("EXPORT_CAPTION", GetLangStr("EXPORT"));
	SetFormatedText("IMPORT_CAPTION", GetLangStr("IMPORT"));
	SetFormatedText("CONTRABAND_CAPTION", GetLangStr("CONTRABAND"));
	SetFormatedText("AGGRESSIVE_CAPTION", "");
	SetFormatedText("COLONY_INFO", "");
	SetFormatedText("COLONY_INFO_TEXT", "");
	SetFormatedText("COLONY_INFO_TEXT2", "");
	SetFormatedText("COLONY_INFO_SIEGE", "");
	SetFormatedText("TRADEASSISTANT_CAPTION", "");
	SetFormatedText("TRADEASSISTANT_TO", "");
	SetFormatedText("TRADEASSISTANT_FROM", "");
	SetFormatedText("TRADEASSISTANT_PRICES1", "");
	SetFormatedText("TRADEASSISTANT_PRICES2", "");
	SetFormatedText("TRADEASSISTANT_SPECIAL", "");

	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 2 );
	//Clean up <--
	
	//Time to travel
	//Thanks to LDH
	sText = XI_ConvertString("ColonyDistance") + " - ";
	
	if(TRAVELTIME_MODE == 0)
	{
		int iDays1 = makeint(_GetDistanceToColony2D(sColony)/300 + 0.5); //min - sailing on deck
		int iDays2 = makeint(_GetDistanceToColony2D(sColony)/100 + 0.5); //max - worldmap

		if (iDays1 < 1)	iDays1 = 1;
		if (iDays2 < 1) iDays2 = 1;
		
		if (iDays1 == iDays2)
			sText += iDays1 + " " + GetLangStr("day");
		else
		{
			sText += GetLangStr("TRAVEL_from") + " " + iDays1 + " " + GetLangStr("TRAVEL_to") + " " + iDays2 + " ";
			
			if(iDays2%10 == 1)
				sText += GetLangStr("day2");
			else
				sText += GetLangStr("days");
		}
		sText+=".";
	}
	else
	{
		int iDistance;
		
		if(TRAVELTIME_MODE == 1)
		{
			iDistance = makeint(_GetDistanceToColony2D(sColony)/6.5 + 0.5)
			
			sText = GetLangStr("Distance") + " = " + iDistance + " ";
			if (iDistance == 1)
			{
				sText += GetLangStr("nautical_mile");
			}
			else
			{
				if(iDistance%10 == 1)
				{
					sText += GetLangStr("nautical_mile2");
				}
				else
				{
					bool lc1 = iDistance%100 < 10 || iDistance%100 > 20;
					if(lc1 && iDistance%10 > 1 && iDistance%10 < 5)
						sText += GetLangStr("nautical_miles2");
					else
						sText += GetLangStr("nautical_miles");
				}
			}
            // LDH 12Jul17 - add direction
            sText += " " + GetMapDir16(_GetDirToColony(sColony));
            sText += " (" + GetMapDir32(_GetDirToColony(sColony)) + ")";
			sText += ".";
		}
		else
		{
			float AverageSpeed = TRAVELTIME_AVERAGE_SPEED;
			if (iArcadeSails == 0) AverageSpeed *= 0.7;
			iDistance = makeint(_GetDistanceToColony2D(sColony)/(TRAVELTIME_AVERAGE_SPEED * 6.5) + 0.5)
			
			sText += iDistance + " ";
			if (iDistance == 1)
			{
				sText += GetLangStr("hour");
			}
			else
			{
				if (iDistance%10 == 1)
				{
					sText += GetLangStr("hour");
				}
				else
				{
					bool lc2 = iDistance%100 < 10 || iDistance%100 > 20;
					if(lc2 && iDistance%10 > 1 && iDistance%10 < 5)
						sText += GetLangStr("hours2");
					else
						sText += GetLangStr("hours");
				}
			}
			sText += ".";
		}
	}
	SetFormatedText("COLONY_TRAVEL_INFO", sText);
	
	//Colony info
	sText = XI_ConvertString("ColonyInfo");
	AddLineToFormatedText("COLONY_INFO_LABEL", sText);
	sText = XI_ConvertString("SalaryQuantity");
	AddLineToFormatedText("COLONY_INFO_TEXT", sText);
	sText = sti(colonies[iColony].ship.crew.quantity);
	AddLineToFormatedText("COLONY_INFO_TEXT2", sText);
	sText = XI_ConvertString("Fort");
	AddLineToFormatedText("COLONY_INFO_TEXT", sText);
	if(!CheckAttribute(rColony, "HasNoFort"))
	{
		sText = XI_ConvertString("FortYes");
		AddLineToFormatedText("COLONY_INFO_TEXT2", sText);

		sld = CharacterFromID(sColony + " Fort Commander");
		sText = XI_ConvertString("CrewQuantity");
		AddLineToFormatedText("COLONY_INFO_TEXT", sText);
		sText = sti(sld.ship.crew.quantity);
		AddLineToFormatedText("COLONY_INFO_TEXT2", sText);

		sText = XI_ConvertString("Quantity_info");
		AddLineToFormatedText("COLONY_INFO_TEXT", sText);
		sText = GetMaxFortCannons(sld.id);
		AddLineToFormatedText("COLONY_INFO_TEXT2", sText);
	}
	else
	{
		sText = XI_ConvertString("FortNo");
		AddLineToFormatedText("COLONY_INFO_TEXT2", sText);
	}
	if(CheckAttribute(rColony, "siege"))
	{
		sText = XI_ConvertString("ThisColonySiege");
		AddLineToFormatedText("COLONY_INFO_TEXT", sText);
		SetFormattedTextLastLineColor("COLONY_INFO_TEXT", argb(255,255,168,168));
	}
	
	///Draw categorized goods
	int iGood = -1;
	string sGood = "";
	int iIsland = FindIsland(rColony.Island);
	
	int i, iType;
	int iGoods_x, iGoods_x1, iGoods_x2, iGoods_x3, iGoods_x4, iGoods_y, iGoods_y1, iGoods_y2, iGoods_y3, iGoods_y4;
	string sGoodNum, sType;
	iGoods_x1 = 1050; iGoods_x2 = 1050; iGoods_x3 = 1050; iGoods_x4 = 1050;
	iGoods_y1 = 530; iGoods_y2 = 615; iGoods_y3 = 700; iGoods_y4 = 785;
	
	bool bFound = true;
	aref rootItems;
	makearef(rootItems, NullCharacter.PriceList);
	bFound = CheckAttribute(rootItems, sColony);

	ref refStore, refStore2;
	aref arefStore2, refGoods;
	for(i = 0; i < STORE_QUANTITY; i++)
	{
		makeref(refStore, Stores[i]);
		if (refStore.colony == sColony)
			break;
	}
	
	for(iType=0; iType<GOODS_QUANTITY; iType++)
	{
		if(iType > 34 && iType < 51) continue;
		
		sGood = goods[iType].name;
		if(!bFound)
		{
			SendMessage( &GameInterface,"lslslllll",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 0,sGood, argb(0, 128, 128, 128), 0,0,0,0);
			break;
		}		
		int i1, i2, i3, i4;
		switch(sti(refStore.Goods.(sGood).TradeType))
		{
		case 3:
			i1++;
			if(i1%8)
			{
				iGoods_x1 += 28;
			}
			else
			{
				iGoods_y1+=28;
				iGoods_x1 = 1078;
			}
			SendMessage( &GameInterface,"lslslllll",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 0,sGood, argb(255, 128, 128, 128), iGoods_x1,iGoods_y1,iGoods_x1+28,iGoods_y1+28 );
			break;
		case 4:
			i2++;
			if(i2%6)
			{
				iGoods_x2+=28;
			}
			else
			{
				iGoods_y2+=28;
				iGoods_x2 = 1078;
			}
			SendMessage( &GameInterface,"lslslllll",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 0,sGood, argb(255, 128, 128, 128), iGoods_x2,iGoods_y2,iGoods_x2+28,iGoods_y2+28 );
			break;
		case 7:
			i3++;
			if(i3%6)
			{
				iGoods_x3+=28;
			}
			else
			{
				iGoods_y3+=28;
				iGoods_x3 = 1078;
			}
			SendMessage( &GameInterface,"lslslllll",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 0,sGood, argb(255, 128, 128, 128), iGoods_x3,iGoods_y3,iGoods_x3+28,iGoods_y3+28 );
			break;
		case 8:
			i4++;
			if(i4%6)
			{
				iGoods_x4+=28;
			}
			else
			{
				iGoods_y4+=28;
				iGoods_x4 = 1078;
			}
			SendMessage( &GameInterface,"lslslllll",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 0,sGood, argb(255, 128, 128, 128), iGoods_x4,iGoods_y4,iGoods_x4+28,iGoods_y4+28 );
			break;
		}
		if(sti(refStore.Goods.(sGood).TradeType) == 8 && i4 > 0)
		SetFormatedText("AGGRESSIVE_CAPTION", GetLangStr("AGGRESSIVE"));
		sText = XI_ConvertString("GoodsRelevance");
		AddLineToFormatedText("COLONY_INFO_TEXT", sText);
		sText =  NullCharacter.PriceList.(sColony).AltDate;
		AddLineToFormatedText("COLONY_INFO_TEXT2", sText);
	}
	
	///Trade assistant
	string sTown = GetCurrentTown();
	
	if(sTown == "" || sTown == sColony)
	return;
	
	SetFormatedText("TRADEASSISTANT_CAPTION", GetLangStr("Trade_assistant"));
	
	//Find town in trade book
	bFound = true;
	if(TRADEASSISTANT_MODE == 0)
	{
		rootItems;
		makearef(rootItems, NullCharacter.PriceList);
		bFound = CheckAttribute(rootItems, sColony);
	}
	
	if(!bFound)
	{
		SetFormatedText("TRADEASSISTANT_SPECIAL", GetLangStr("No_price"));
		return;
	}
		
	//Find our store
	for(i = 0; i < STORE_QUANTITY; i++)
	{
		makeref(refStore, Stores[i]);
		if (refStore.colony == sTown)
			break;
	}
	//Find target store
	if(TRADEASSISTANT_MODE == 0)
	{
		makearef(arefStore2, NullCharacter.PriceList.(sColony));
	}
	else
	{
		for(i = 0; i < STORE_QUANTITY; i++)
		{
			makeref(refStore2, Stores[i]);
			if (refStore2.colony == sColony)
					break;
		}
	}
	
	float a_fMax[TRADEASSISTANT_MAXGOODS];
	int a_iMax[TRADEASSISTANT_MAXGOODS];
	float fTemp;
	int nSell, nBuy;
	
	bFound = false; //at least one good displayed
	
	//Calculate profit
	for(iType=0; iType<2; iType++)
	{
		if(iType)
		{
			iGoods_x = 920;
			iColor = argb(255,196,255,196);
		}
		else
		{
			iGoods_x = 820;
			iColor = argb(255,196,196,255);
		}
		
		for(i=0; i<TRADEASSISTANT_MAXGOODS-1; i++)
			a_fMax[i] = 0.;

		for (i = 10; i < 35; i++)
		{
			sGood = Goods[i].name;
			if(refStore.Goods.(sGood).TradeType == 3)
				continue;
			
			if(TRADEASSISTANT_MODE == 1)
			{
				if(refStore2.Goods.(sGood).TradeType == 3)
					continue;
			}
			else
			{
				sGood = "Gidx" + i;
				
				if(arefStore2.(sGood).TradeType == 3)
					continue;
			}
			
			if(iType == 0)
			{
				nBuy = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY, pchar, 1);
				if(TRADEASSISTANT_MODE == 0)
					nSell = arefStore2.(sGood).Sell;
				else
					nSell = GetStoreGoodsPrice(refStore2, i, PRICE_TYPE_SELL, pchar, 1);
			}
			else
			{
				nSell = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);
				if(TRADEASSISTANT_MODE == 0)
					nBuy = arefStore2.(sGood).Buy;
				else
					nBuy = GetStoreGoodsPrice(refStore2, i, PRICE_TYPE_BUY, pchar, 1);
			}
			
			fTemp = (nSell - nBuy) / stf(Goods[i].weight); //price per pound
			
			//Sort
			for(int k=0; k<TRADEASSISTANT_MAXGOODS; k++)
			{
				if(fTemp > a_fMax[k])
				{
					for( int j=TRADEASSISTANT_MAXGOODS-1; j>k; j--)
					{
						a_fMax[j] = a_fMax[j-1];
						a_iMax[j] = a_iMax[j-1];
					}
					a_fMax[k] = fTemp;
					a_iMax[k] = i;
					break;
				}
			}
		}
		
		//Draw goods
		iGoods_y = 710;
		for(i=0; i<TRADEASSISTANT_MAXGOODS; i++)
		{
			if(!a_fMax[i])
				break;
			
			AddLineToFormatedText("TRADEASSISTANT_PRICES" + (iType+1), FloatToStr(a_fMax[i]));
			SetFormattedTextLastLineColor("TRADEASSISTANT_PRICES" + (iType+1), iColor);
			
			SendMessage( &GameInterface,"lslslllll",MSG_INTERFACE_MSG_TO_NODE,"GOODS_PICTURES", 0,
				Goods[a_iMax[i]].name, argb(255, 128, 128, 128), iGoods_x,iGoods_y,iGoods_x+28,iGoods_y+28 );
			iGoods_y+=28;
			
			bFound = true;
		}
	}
	
	if(bFound)
	{
		SetFormatedText("TRADEASSISTANT_TO", GetLangStr("To"));
		SetFormatedText("TRADEASSISTANT_FROM", GetLangStr("From"));
	}
	else
	{
		SetFormatedText("TRADEASSISTANT_SPECIAL", GetLangStr("No_profit"));
	}
}

int GetMaxFortCannons(string _FortCommander)
{
	int _iCannons = 0;
	switch(_FortCommander)
	{
		case "Bridgetown Fort Commander": _iCannons = 39; break;
			
		case "SentJons Fort Commander": _iCannons = 103; break;
			
		case "SanJuan Fort Commander": _iCannons = 45; break;
			
		case "Charles Fort Commander": _iCannons = 157; break;
			
		case "Marigo Fort Commander": _iCannons = 161; break;
			
		case "BasTer Fort Commander": _iCannons = 82; break;
			
		case "FortFrance Fort Commander": _iCannons = 92; break;
			
		case "Villemstad Fort Commander": _iCannons = 76; break;
			
		case "PortSpein Fort Commander": _iCannons = 83; break;
			
		case "Cumana Fort Commander": _iCannons = 80; break;
			
		case "Caracas Fort Commander": _iCannons = 164; break;
			
		case "Maracaibo Fort Commander": _iCannons = 70; break;
			
		case "Cartahena Fort Commander": _iCannons = 85; break;
			
		case "PortoBello Fort Commander": _iCannons = 82; break;
			
		case "SantaCatalina Fort Commander": _iCannons = 164; break;
			
		case "Beliz Fort Commander": _iCannons = 80; break;
			
		case "PortRoyal Fort Commander": _iCannons = 204; break;
			
		case "PortPax Fort Commander": _iCannons = 179; break;
			
		case "SantoDomingo Fort Commander": _iCannons = 128; break;
			
		case "Santiago Fort Commander": _iCannons = 128; break;
			
		case "Tortuga Fort Commander": _iCannons = 28; break;
			
		case "Havana Fort Commander": _iCannons = 80; break;
	}
	
	return _iCannons;
}
// LDH 12Jul17 compass directions -->
string GetMapDir16(float dir)      // N, NNE, NE
{
	dir = Normalize360(Radian2Degree(dir));
	int index = makeint((dir / 22.5) + 0.5);   // round to nearest compass16 point
	if (index >= 16) index = 0;

	switch (index)
	{
	    case  0: return "N"; break;
	    case  1: return "NNE"; break;
	    case  2: return "NE"; break;
	    case  3: return "ENE"; break;
	    case  4: return "E"; break;
	    case  5: return "ESE"; break;
	    case  6: return "SE"; break;
	    case  7: return "SSE"; break;
	    case  8: return "S"; break;
	    case  9: return "SSW"; break;
	    case 10: return "SW"; break;
	    case 11: return "WSW"; break;
	    case 12: return "W"; break;
	    case 13: return "WNW"; break;
	    case 14: return "NW"; break;
	    case 15: return "NNW"; break;
	}
}

string GetMapDir32(float dir)      // N, NbE, NNE
{
	dir = Normalize360(Radian2Degree(dir));
	int index = makeint((dir / 11.25) + 0.5);   // round to nearest compass32 point
	if (index >= 32) index = 0;

	switch (index)
	{
	    case  0: return "N"; break;
	    case  1: return "NbE"; break;
	    case  2: return "NNE"; break;
	    case  3: return "NEbN"; break;
	    case  4: return "NE"; break;
	    case  5: return "NEbE"; break;
	    case  6: return "ENE"; break;
	    case  7: return "EbN"; break;
	    case  8: return "E"; break;
	    case  9: return "EbS"; break;
	    case 10: return "ESE"; break;
	    case 11: return "SEbE"; break;
	    case 12: return "SE"; break;
	    case 13: return "SEbS"; break;
	    case 14: return "SSE"; break;
	    case 15: return "SbE"; break;
	    case 16: return "S"; break;
	    case 17: return "SbW"; break;
	    case 18: return "SSW"; break;
	    case 19: return "SWbS"; break;
	    case 20: return "SW"; break;
	    case 21: return "SWbW"; break;
	    case 22: return "WSW"; break;
	    case 23: return "WbS"; break;
	    case 24: return "W"; break;
	    case 25: return "WbN"; break;
	    case 26: return "WNW"; break;
	    case 27: return "NWbW"; break;
	    case 28: return "NW"; break;
	    case 29: return "NWbN"; break;
	    case 30: return "NNW"; break;
	    case 31: return "NbW"; break;
	}
}

float _GetDirToColony(string _sColony)
{
	ref rColony = GetColonyRefByID(_sColony);
	string sColonyIslandID = rColony.Island;
	string sColonyTown = _sColony + "_town";

	if(_sColony == "FortOrange") sColonyTown = "Shore36";
	if(_sColony == "LaVega") sColonyTown = "LaVega_town";

	float X1, Z1;
	GetCorrectShipCoords(&X1, &Z1)
	float X2 = makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.x)+1000;
	float Z2 = -makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.z)+1000;
    
    if (Z2 > Z1)
        return PI + atan((X1-X2)/(Z2-Z1));
    else
        return atan((X1-X2)/(Z2-Z1));

}

float Normalize360(float dir)
{
    if (dir < 0.0) dir += 360.0;
    if (dir > 360.0) dir -= 360.0;
    return dir;
}
// LDH 12Jul17 <-