/// BOAL меню торговли
string CurTable, CurRow;
bool bSortCityDisable, bSortByDate, bSortByABC, bClockwiseSort; // belamour значения не присваиваю, дабы сохранялись до перезагрузки

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchTradeBook"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleTradeBook";
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("TableSelectChange", "TableSelectChange", 0);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
    SetEventHandler("MouseRClickUp","HideInfoWindow",0);
    
    XI_RegistryExitKey("IExit_F2");

	SetBySort(); // belamour установить параметры чекбоксам
	GetBySort(); // сортировка от значения
}

void SetBySort() 
{
	if(!bSortCityDisable) 
	{
		CheckButton_SetState("CHECK_SortTradeBook", 1, true); // нация
		CheckButton_SetState("CHECK_SortTradeBookDate", 1, false); 
		CheckButton_SetState("CHECK_SortTradeBookABC", 1, false);
		CheckButton_SetState("CHECK_SortTradeBookClockwise", 1, false);
	}  
	if(bSortByDate) 
	{
		CheckButton_SetState("CHECK_SortTradeBookDate", 1, true); // дата
		CheckButton_SetState("CHECK_SortTradeBook", 1, false); 
		CheckButton_SetState("CHECK_SortTradeBookABC", 1, false);
		CheckButton_SetState("CHECK_SortTradeBookClockwise", 1, false);
	}   
	if(bSortByABC) 
	{
		CheckButton_SetState("CHECK_SortTradeBookABC", 1, true); // алфавит
		CheckButton_SetState("CHECK_SortTradeBookDate", 1, false);  
		CheckButton_SetState("CHECK_SortTradeBook", 1, false); 
		CheckButton_SetState("CHECK_SortTradeBookClockwise", 1, false);
	}
	if(bClockwiseSort) 
	{
		CheckButton_SetState("CHECK_SortTradeBookClockwise", 1, true); // по часовой
		CheckButton_SetState("CHECK_SortTradeBookABC", 1, false); 
		CheckButton_SetState("CHECK_SortTradeBookDate", 1, false);  
		CheckButton_SetState("CHECK_SortTradeBook", 1, false); 
	}
	if(bSortCityDisable && !bSortByDate && !bSortByABC && !bClockwiseSort) // классика
	{
		CheckButton_SetState("CHECK_SortTradeBookDate", 1, false); 
		CheckButton_SetState("CHECK_SortTradeBook", 1, false);
		CheckButton_SetState("CHECK_SortTradeBookABC", 1, false);
		CheckButton_SetState("CHECK_SortTradeBookClockwise", 1, false);
	} 
}

void GetBySort()
{
	if(!bSortCityDisable || bSortByABC) FillPriceListTownSorted("TABLE_CITY"); // по нациям или алфавиту 
	if(bSortByDate) FillPriceListTownSortedByDate("TABLE_CITY"); // по актуальности		
	if(bClockwiseSort) FillPriceListClockwiseSort("TABLE_CITY"); // по часовой стрелке
	if(bSortCityDisable && !bSortByDate && !bSortByABC && !bClockwiseSort) FillPriceListTown("TABLE_CITY"); // классика
}
	
void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("TableSelectChange", "TableSelectChange");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
    DelEventHandler("MouseRClickUp","HideInfoWindow");
    
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
	// belamour
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_SortTradeBook", 3, 1))
	{
		bSortCityDisable = false;
	}
	else
	{
		bSortCityDisable = true;
	}
	
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_SortTradeBookDate", 3, 1))
	{
		bSortByDate = true;
	}
	else
	{
		bSortByDate = false;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_SortTradeBookABC", 3, 1))
	{
		bSortByABC = true;
	}
	else
	{
		bSortByABC = false;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_SortTradeBookClockwise", 3, 1))
	{
		bClockwiseSort = true;
	}
	else
	{
		bClockwiseSort = false;
	}
	
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
		case "I_CHARACTER_2":
			if(comName=="click")
			{
			    nodName = "I_CHARACTER";
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
		case "I_TRADEBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_TRADEBOOK";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
		
		case "CHECK_SortTradeBook": 
			if(comName=="click")
			{
				bSortByDate = false;
				bSortByABC = false;
				bClockwiseSort = false;
				SetBySort();  // belamour для обновления сортировки
				GetBySort();
			}
		break;
		
		case "CHECK_SortTradeBookDate": 
			if(comName=="click")
			{
				bSortCityDisable = true;
				bSortByABC = false;
				bClockwiseSort = false;
				SetBySort(); 
				GetBySort();
			}
		break;
		
		case "CHECK_SortTradeBookABC": 
			if(comName=="click")
			{
				bSortCityDisable = true;
				bSortByDate = false;
				bClockwiseSort = false;
				SetBySort(); 
				GetBySort();
			}
		break;
		
		case "CHECK_SortTradeBookClockwise": 
			if(comName=="click")
			{
				bSortCityDisable = true;
				bSortByDate = false;
				bSortByABC = false;
				SetBySort(); 
				GetBySort();
			}
		break;
	}
	
	// boal new menu 31.12.04 -->
	if (nodName == "I_CHARACTER" || nodName == "I_SHIP" ||
	    nodName == "I_QUESTBOOK" || nodName == "I_TRADEBOOK" ||
		nodName == "I_NATIONS" || nodName == "I_ITEMS")
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
//  таблица: город, местоположение, актуальность
void FillPriceListTown(string _tabName)
{
	string  cityId, attr2, firstId;
    int     i, cn, n;
    ref     nulChr;
    string  row;
    aref    rootItems;
    aref    curItem;
    ref     rCity;
    
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = "Нация";
    GameInterface.(_tabName).hr.td1.scale = 0.77
	GameInterface.(_tabName).hr.td2.str = "Город";
	GameInterface.(_tabName).hr.td2.scale = 0.8;
	GameInterface.(_tabName).hr.td3.str = "Местоположение";
	GameInterface.(_tabName).hr.td3.scale = 0.7;
	GameInterface.(_tabName).hr.td4.str = "Актуальность";
	GameInterface.(_tabName).hr.td4.scale = 0.7;
    // <--
    nulChr = &NullCharacter;
    makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
    n = 1;
    firstId = "";
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
        row = "tr" + n;
		curItem = GetAttributeN(rootItems, i);
		cityId = GetAttributeName(curItem);
        row = "tr" + n;	
		cn = FindColony(cityId);
		if (cn != -1)
		{
			rCity = GetColonyByIndex(cn);
			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).UserData.CityID  = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 26;
		    GameInterface.(_tabName).(row).td1.icon.height = 26;
		    GameInterface.(_tabName).(row).td1.icon.offset = "0, 3";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(cityId + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			GameInterface.(_tabName).(row).td3.scale = 0.8;
			GameInterface.(_tabName).(row).td4.scale = 0.75;
			if (CheckAttribute(nulChr, "PriceList." + cityId + ".AltDate"))
		    {
		        GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(cityId).AltDate;
		    }
		    else
		    {
		        GameInterface.(_tabName).(row).td4.str = "??.??.????";
		    }
			n++;
		}
	}
	//if (n > 1) GameInterface.(_tabName).select = 1;
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}

// LDH 06Jul17 
#define MAX_OURCOLONIES 42
void FillPriceListTownSorted(string _tabName)
{
	string  cityId, attr2, firstId;
    int     i, cn, n, z;
    ref     nulChr;
    string  row;
    aref    rootItems;
    aref    curItem;
    ref     rCity;
	
	// LDH 06Jul17 -->
	// belamour немного переделал метод для алфавитного порядка
    string AlphaColonies[MAX_OURCOLONIES];
    z = 0;
	AlphaColonies[z] = "BasTer";          z = z + 1;
	AlphaColonies[z] = "Beliz";           z = z + 1;
	AlphaColonies[z] = "SantaCatalina";   z = z + 1;  // Blueweld
	AlphaColonies[z] = "Bridgetown";      z = z + 1;
	AlphaColonies[z] = "Villemstad";      z = z + 1;
    AlphaColonies[z] = "Havana";          z = z + 1;
	AlphaColonies[z] = "Charles";         z = z + 1; 
	AlphaColonies[z] = "Caracas";         z = z + 1;
	AlphaColonies[z] = "Cartahena";       z = z + 1;
	AlphaColonies[z] = "Cumana";          z = z + 1;
	AlphaColonies[z] = "LaVega";          z = z + 1;
	AlphaColonies[z] = "LeFransua";		  z = z + 1;
	AlphaColonies[z] = "Maracaibo";       z = z + 1;
	AlphaColonies[z] = "FortOrange";      z = z + 1;
    AlphaColonies[z] = "Panama";          z = z + 1;
	AlphaColonies[z] = "PortoBello";      z = z + 1;
	AlphaColonies[z] = "PortPax";         z = z + 1;
	AlphaColonies[z] = "PortRoyal";       z = z + 1;
	AlphaColonies[z] = "PuertoPrincipe";  z = z + 1;
	AlphaColonies[z] = "SanAndres";	      z = z + 1;
    AlphaColonies[z] = "SantoDomingo";    z = z + 1;
	AlphaColonies[z] = "Santiago";        z = z + 1;
	AlphaColonies[z] = "PortSpein";       z = z + 1;
	AlphaColonies[z] = "SanJuan";         z = z + 1;
	AlphaColonies[z] = "FortFrance";      z = z + 1;
	AlphaColonies[z] = "SentJons";        z = z + 1;
	AlphaColonies[z] = "Tortuga";         z = z + 1;
	AlphaColonies[z] = "Marigo";          z = z + 1;
    AlphaColonies[z] = "Pirates";         z = z + 1;
	
	AlphaColonies[z] = "LosTeques";       z = z + 1;
	AlphaColonies[z] = "Terks";           z = z + 1;
    AlphaColonies[z] = "Dominica";        z = z + 1;
    AlphaColonies[z] = "Pearl";           z = z + 1;
    AlphaColonies[z] = "Caiman";          z = z + 1;
    AlphaColonies[z] = "Tenotchitlan";    z = z + 1;
    AlphaColonies[z] = "LostShipsCity";   z = z + 1;
    AlphaColonies[z] = "KhaelRoa";        z = z + 1;
    AlphaColonies[z] = "Ksochitam";       z = z + 1;
    AlphaColonies[z] = "RockIsland";      z = z + 1;
    AlphaColonies[z] = "SantaQuiteria";   z = z + 1;
    AlphaColonies[z] = "IslaDeVieques";   z = z + 1;
    AlphaColonies[z] = "Is";              
   
	// belamour сортировка Трейдбука по нациям -->
	string OurColonies[MAX_OURCOLONIES];
	ref rCitySort;
	int  m;
	i = 0;
	if(!bSortByABC) 
	{
		string sHeroNation = GetBaseHeroNation(); // belamour задел на будущее 
		switch (sHeroNation) 
		{
			case "1": // Шарль де Мор
			
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "FRANCE") {OurColonies[i] = AlphaColonies[z]; i++;}
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "HOLLAND") {OurColonies[i] = AlphaColonies[z]; i++;}	
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "ENGLAND") {OurColonies[i] = AlphaColonies[z]; i++;}		
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "SPAIN") {OurColonies[i] = AlphaColonies[z]; i++;}		
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "PIRATE") {OurColonies[i] = AlphaColonies[z]; i++;}
				}
			break;
		
			case "2": // Диего де Монтойя

				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "SPAIN") {OurColonies[i] = AlphaColonies[z]; i++;}		
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "HOLLAND") {OurColonies[i] = AlphaColonies[z]; i++;}	
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "FRANCE") {OurColonies[i] = AlphaColonies[z]; i++;}
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "ENGLAND") {OurColonies[i] = AlphaColonies[z]; i++;}		
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "PIRATE") {OurColonies[i] = AlphaColonies[z]; i++;}
				}
			break;
		
			case "0": // малыш Вилли, если будет
			
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "ENGLAND") {OurColonies[i] = AlphaColonies[z]; i++;}		
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "FRANCE") {OurColonies[i] = AlphaColonies[z]; i++;}
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "HOLLAND") {OurColonies[i] = AlphaColonies[z]; i++;}	
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "SPAIN") {OurColonies[i] = AlphaColonies[z]; i++;}		
				}
				for (z=0; z<MAX_OURCOLONIES; z++)
				{
					m = FindColony(AlphaColonies[z]); rCitySort = GetColonyByIndex(m);
					if(Nations[sti(rCitySort.nation)].Name == "PIRATE") {OurColonies[i] = AlphaColonies[z]; i++;}
				}
			break;
		}
	}
	else // по алфавиту
	{
		for (z=0; z<MAX_OURCOLONIES; z++)
		{
			OurColonies[i] = AlphaColonies[z]; 
			i++;
		}
	}
	// <-- belamour
	
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = "Нация";
    GameInterface.(_tabName).hr.td1.scale = 0.77
	GameInterface.(_tabName).hr.td2.str = "Город";
	GameInterface.(_tabName).hr.td2.scale = 0.8;
	GameInterface.(_tabName).hr.td3.str = "Местоположение";
	GameInterface.(_tabName).hr.td3.scale = 0.7;
	GameInterface.(_tabName).hr.td4.str = "Актуальность";
	GameInterface.(_tabName).hr.td4.scale = 0.7;
    // <--
    nulChr = &NullCharacter;
    makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
    n = 1;
    firstId = "";
// LDH 06Jul17 -->
    for (i=0; i<MAX_OURCOLONIES; i++)   
    {
		bool bFound = false;
		for (int j=0; j<GetAttributesNum(rootItems); j++)
		{
			curItem = GetAttributeN(rootItems, j);
			cityId = GetAttributeName(curItem);
			
			if(cityId == OurColonies[i])
			{
				bFound = true;
				break;
			}
		}
		
		if(!bFound)
			continue;
// LDH 06Jul17 <--

        row = "tr" + n;	
		cn = FindColony(cityId);
		if (cn != -1)
		{
			rCity = GetColonyByIndex(cn);
			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).UserData.CityID  = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 26;
		    GameInterface.(_tabName).(row).td1.icon.height = 26;
		    GameInterface.(_tabName).(row).td1.icon.offset = "0, 3";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(cityId + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			GameInterface.(_tabName).(row).td3.scale = 0.8;
			GameInterface.(_tabName).(row).td4.scale = 0.75;
			if (CheckAttribute(nulChr, "PriceList." + cityId + ".AltDate"))
		    {
		        GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(cityId).AltDate;
		    }
		    else
		    {
		        GameInterface.(_tabName).(row).td4.str = "??.??.????";
		    }
			n++;
		}
	}
	//if (n > 1) GameInterface.(_tabName).select = 1;
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}

// --> mitrokosta сортировка по дате
int DateStringToInt(string dateString) {
	int pos;
	string time, date;
	int totalTime = 0;
	
	// резка строки по пробелу
	pos = findSubStr(&dateString, " ", 0);
	if (pos < 0) return -1;
	
	time = strcut(&dateString, 0, pos - 1);
	date = strcut(&dateString, pos + 1, strlen(&dateString) - 1);
	
	// парсинг и приведение дат к числам
	totalTime += sti(strcut(&date, 6, 9));
	totalTime *= 365;
	
	totalTime += sti(strcut(&date, 3, 4));
	totalTime *= 31;
	
	totalTime += sti(strcut(&date, 0, 1));
	totalTime *= 24;
	
	totalTime += sti(strcut(&time, 0, 1));
	totalTime *= 60;
	
	totalTime += sti(strcut(&time, 3, 4));
	
	return totalTime;
}

void FillPriceListTownSortedByDate(string _tabName) {
	string	cityId, attr2, firstId;
	int		i, j, tmp, cn, n, totalEntries;
	ref		nulChr;
	string	row, left, right, lAttr, rAttr;
	aref	rootItems;
	aref	curItem;
	ref		rCity;

	// шапка -->
	GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "Нация";
	GameInterface.(_tabName).hr.td1.scale = 0.77;
	GameInterface.(_tabName).hr.td2.str = "Город";
	GameInterface.(_tabName).hr.td2.scale = 0.8;
	GameInterface.(_tabName).hr.td3.str = "Местоположение";
	GameInterface.(_tabName).hr.td3.scale = 0.7;
	GameInterface.(_tabName).hr.td4.str = "Актуальность";
	GameInterface.(_tabName).hr.td4.scale = 0.7;
	// <--

	nulChr = &NullCharacter;
	makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
	n = 1;
	firstId = "";
	totalEntries = GetAttributesNum(rootItems);

	int entryIndices[2];
	
	if (totalEntries > 2) {
		SetArraySize(&entryIndices, totalEntries);
	}
	
	for (i = 0; i < totalEntries; i++) {
		entryIndices[i] = i;
	}

	// Собственно сама сортировка (выбором)
	for (i = 0; i < totalEntries - 1; i++) {
		for (j = i + 1; j < totalEntries; j++) {
			lAttr = "PriceList." + GetAttributeName(GetAttributeN(rootItems, entryIndices[j])) + ".AltDate";
			rAttr = "PriceList." + GetAttributeName(GetAttributeN(rootItems, entryIndices[i])) + ".AltDate";
			
			if (CheckAttribute(nulChr, lAttr) && CheckAttribute(nulChr, rAttr)) {
				if (DateStringToInt(nulChr.(lAttr)) > DateStringToInt(nulChr.(rAttr))) {
					tmp = entryIndices[i];
					entryIndices[i] = entryIndices[j];
					entryIndices[j] = tmp;
				}
			}
		}
	}

	for (i = 0; i < totalEntries; i++)
	{
		row = "tr" + n;
		curItem = GetAttributeN(rootItems, entryIndices[i]); // учёт сортировки
		cityId = GetAttributeName(curItem);
		row = "tr" + n;	
		cn = FindColony(cityId);
		if (cn != -1)
		{
			rCity = GetColonyByIndex(cn);
			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).UserData.CityID  = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 26;
			GameInterface.(_tabName).(row).td1.icon.height = 26;
			GameInterface.(_tabName).(row).td1.icon.offset = "0, 3";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(cityId + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			GameInterface.(_tabName).(row).td3.scale = 0.8;
			GameInterface.(_tabName).(row).td4.scale = 0.75;
			if (CheckAttribute(nulChr, "PriceList." + cityId + ".AltDate"))
			{
				GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(cityId).AltDate;
			}
			else
			{
				GameInterface.(_tabName).(row).td4.str = "??.??.????";
			}
			n++;
		}
	}
	//if (n > 1) GameInterface.(_tabName).select = 1;
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}
// <-- mitrokosta

// belamour плюс метод сортировки по часовой стрелке от LDH -->

void FillPriceListClockwiseSort(string _tabName)
{
	string  cityId, attr2, firstId;
    int     i, cn, n;
    ref     nulChr;
    string  row;
    aref    rootItems;
    aref    curItem;
    ref     rCity;

// LDH 06Jul17 -->
    string OurColonies[MAX_OURCOLONIES];
    i = 0;
    OurColonies[i] = "Havana";          i = i + 1;
    OurColonies[i] = "Santiago";        i = i + 1;
    OurColonies[i] = "PuertoPrincipe";  i = i + 1;
    OurColonies[i] = "PortRoyal";       i = i + 1;
    OurColonies[i] = "FortOrange";      i = i + 1;
    OurColonies[i] = "Tortuga";         i = i + 1;
    OurColonies[i] = "PortPax";         i = i + 1;
    OurColonies[i] = "SantoDomingo";    i = i + 1;
    OurColonies[i] = "LaVega";          i = i + 1;
    OurColonies[i] = "Terks";           i = i + 1;
    OurColonies[i] = "SanJuan";         i = i + 1;
    OurColonies[i] = "Pirates";         i = i + 1;
    OurColonies[i] = "Marigo";          i = i + 1;
    OurColonies[i] = "Charles";         i = i + 1;
    OurColonies[i] = "SentJons";        i = i + 1;
    OurColonies[i] = "BasTer";          i = i + 1;
    OurColonies[i] = "Dominica";        i = i + 1;
    OurColonies[i] = "FortFrance";      i = i + 1;
    OurColonies[i] = "LeFransua";       i = i + 1;
    OurColonies[i] = "Bridgetown";      i = i + 1;
    OurColonies[i] = "Villemstad";      i = i + 1;
    OurColonies[i] = "PortSpein";       i = i + 1;
    OurColonies[i] = "Cumana";          i = i + 1;
    OurColonies[i] = "Caracas";         i = i + 1;
    OurColonies[i] = "Maracaibo";       i = i + 1;
    OurColonies[i] = "Cartahena";       i = i + 1;
    OurColonies[i] = "PortoBello";      i = i + 1;
    OurColonies[i] = "Panama";          i = i + 1;
    OurColonies[i] = "Pearl";           i = i + 1;
    OurColonies[i] = "SantaCatalina";   i = i + 1;  // Blueweld
    OurColonies[i] = "Beliz";           i = i + 1;
    OurColonies[i] = "Caiman";          i = i + 1;
    
    OurColonies[i] = "Tenotchitlan";    i = i + 1;
    OurColonies[i] = "LosTeques";       i = i + 1;
    OurColonies[i] = "LostShipsCity";   i = i + 1;
    OurColonies[i] = "KhaelRoa";        i = i + 1;
    OurColonies[i] = "Ksochitam";       i = i + 1;
    OurColonies[i] = "RockIsland";      i = i + 1;
    OurColonies[i] = "SantaQuiteria";   i = i + 1;
    OurColonies[i] = "IslaDeVieques";   i = i + 1;
    OurColonies[i] = "Is";              i = i + 1;
    OurColonies[i] = "SanAndres";

// LDH 06Jul17 <--
    
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = "Нация";
    GameInterface.(_tabName).hr.td1.scale = 0.77
	GameInterface.(_tabName).hr.td2.str = "Город";
	GameInterface.(_tabName).hr.td2.scale = 0.8;
	GameInterface.(_tabName).hr.td3.str = "Местоположение";
	GameInterface.(_tabName).hr.td3.scale = 0.7;
	GameInterface.(_tabName).hr.td4.str = "Актуальность";
	GameInterface.(_tabName).hr.td4.scale = 0.7;
    // <--
    nulChr = &NullCharacter;
    makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
    n = 1;
    firstId = "";
// LDH 06Jul17 -->
    for (i=0; i<MAX_OURCOLONIES; i++)   
    {
		bool bFound = false;
		for (int j=0; j<GetAttributesNum(rootItems); j++)
		{
			curItem = GetAttributeN(rootItems, j);
			cityId = GetAttributeName(curItem);
			
			if(cityId == OurColonies[i])
			{
				bFound = true;
				break;
			}
		}
		
		if(!bFound)
			continue;
// LDH 06Jul17 <--

        row = "tr" + n;	
		cn = FindColony(cityId);
		if (cn != -1)
		{
			rCity = GetColonyByIndex(cn);
			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).UserData.CityID  = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 26;
		    GameInterface.(_tabName).(row).td1.icon.height = 26;
		    GameInterface.(_tabName).(row).td1.icon.offset = "0, 3";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(cityId + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			GameInterface.(_tabName).(row).td3.scale = 0.8;
			GameInterface.(_tabName).(row).td4.scale = 0.75;
			if (CheckAttribute(nulChr, "PriceList." + cityId + ".AltDate"))
		    {
		        GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(cityId).AltDate;
		    }
		    else
		    {
		        GameInterface.(_tabName).(row).td4.str = "??.??.????";
		    }
			n++;
		}
	}
	//if (n > 1) GameInterface.(_tabName).select = 1;
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}
// <-- ClockwiseSort

//  таблица
// картинка, название, картинка экспорта, продажа, покупка, колво, пачка, вес пачки
void FillPriceList(string _tabName, string  attr1)
{
    string  sGoods;
    int     i, n;
    ref     nulChr;
    string  row;
    nulChr = &NullCharacter;
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Good name");
    GameInterface.(_tabName).hr.td1.scale = 0.8;
    GameInterface.(_tabName).hr.td2.str = "Тип";
    GameInterface.(_tabName).hr.td2.scale = 0.85;
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.(_tabName).hr.td3.scale = 0.8;
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Price buy");
	GameInterface.(_tabName).hr.td4.scale = 0.8;
	GameInterface.(_tabName).hr.td5.str = XI_ConvertString("In the store");
	GameInterface.(_tabName).hr.td5.scale = 0.8;
	GameInterface.(_tabName).hr.td6.str = "Пачка";
	GameInterface.(_tabName).hr.td6.scale = 0.8;
	GameInterface.(_tabName).hr.td7.str = "Вес пачки";
	GameInterface.(_tabName).hr.td7.scale = 0.8;
	if (attr1 != "")
	{
	    // <--
	    n = 1;
	    for (i = 0; i < GetArraySize(&Goods); i++)
	    {
	        row = "tr" + n;
	        sGoods = "Gidx" + i;			
	        if (sti(nulChr.PriceList.(attr1).(sGoods).TradeType) == T_TYPE_CANNONS && !bBettaTestMode) continue; // не пушки
	        
            GameInterface.(_tabName).(row).UserData.ID = Goods[i].name;
            GameInterface.(_tabName).(row).UserData.IDX = i;
            
	        GameInterface.(_tabName).(row).td1.icon.group = "GOODS";
			GameInterface.(_tabName).(row).td1.icon.image = Goods[i].name;
			GameInterface.(_tabName).(row).td1.icon.offset = "1, 0";
			GameInterface.(_tabName).(row).td1.icon.width = 32;
			GameInterface.(_tabName).(row).td1.icon.height = 32;
			GameInterface.(_tabName).(row).td1.textoffset = "30,0";
			GameInterface.(_tabName).(row).td1.str = XI_ConvertString(Goods[i].name);
			GameInterface.(_tabName).(row).td1.scale = 0.85;

	        GameInterface.(_tabName).(row).td2.icon.group = "TRADE_TYPE";
			GameInterface.(_tabName).(row).td2.icon.image = "ico_" + nulChr.PriceList.(attr1).(sGoods).TradeType;
			GameInterface.(_tabName).(row).td2.icon.offset = "0, 1";
			GameInterface.(_tabName).(row).td2.icon.width = 16;
			GameInterface.(_tabName).(row).td2.icon.height = 28;

	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Buy"))
	        {
	            GameInterface.(_tabName).(row).td3.str = nulChr.PriceList.(attr1).(sGoods).Buy;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td3.str = "???";
	        }
	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Sell"))
	        {
	            GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(attr1).(sGoods).Sell;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td4.str = "???";
	        }
	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Qty"))
	        {
	            GameInterface.(_tabName).(row).td5.str = nulChr.PriceList.(attr1).(sGoods).Qty;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td5.str = "????";
	        }
	        GameInterface.(_tabName).(row).td6.str = Goods[i].Units;
			GameInterface.(_tabName).(row).td7.str = Goods[i].Weight;
	        n++;
	    }
    }
    Table_UpdateWindow(_tabName);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
 	//NullSelectTable("TABLE_CITY");
    NullSelectTable("TABLE_GOODS");
    // перерисуем "прайс"
    if (CurTable == "TABLE_CITY")
    {
    	FillPriceList("TABLE_GOODS", GameInterface.(CurTable).(CurRow).UserData.CityID);
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

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "TABLE_GOODS":
		    sGroup = "GOODS";
		    sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
		    sText1  = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem]);
			sText2 = "Цвета указателя типа товара :" + newStr() + 
				 "- зелёный : колониальные товары" + newStr() + 
				 "- синий : импортные товары" + newStr() + 
				 "- красный : контрабандные товары" + newStr() + 
				 "- персиковый : товары агрессивного спроса";
		break;
		// belammour описание -->
		case "CHECK_SortTradeBook":
			sHeader = XI_ConvertString("CHECK_SortTradeBook Mode");
		    sText1 = XI_ConvertString("CHECK_SortTradeBook Mode_descr");
		break;
		
		case "CHECK_SortTradeBookABC":
			sHeader = XI_ConvertString("CHECK_SortTradeBook Mode");
		    sText1 = XI_ConvertString("CHECK_SortTradeBookABC Mode_descr");
		break;
		
		case "CHECK_SortTradeBookDate":
			sHeader = XI_ConvertString("CHECK_SortTradeBook Mode");
		    sText1 = XI_ConvertString("CHECK_SortTradeBookDate Mode_descr");
		break;
		
		case "CHECK_SortTradeBookClockwise":
			sHeader = XI_ConvertString("CHECK_SortTradeBook Mode");
		    sText1 = XI_ConvertString("CHECK_SortTradeBookClockwise Mode_descr");
		break;
		// <--
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);

}
void HideInfoWindow()
{
	CloseTooltip();
}