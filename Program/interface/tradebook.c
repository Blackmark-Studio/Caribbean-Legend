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
			GameInterface.(_tabName).(row).td2.str = GetCityName(cityId);
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetIslandName(rCity);
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
    string AlphaColonies[MAX_OURCOLONIES] = {"BasTer", "Beliz", "SantaCatalina", "Bridgetown", "Villemstad", "Havana", "Charles", "Caracas", "Cartahena", "Cumana", "LaVega", "LeFransua", "Maracaibo", "FortOrange", "Panama", "PortoBello", "PortPax", "PortRoyal", "PuertoPrincipe", "SanAndres", "SantoDomingo", "Santiago", "PortSpein", "SanJuan", "FortFrance", "SentJons", "Tortuga", "Marigo", "Pirates", "LosTeques", "Terks", "Dominica", "Pearl", "Caiman", "Tenotchitlan", "LostShipsCity", "KhaelRoa", "Ksochitam", "RockIsland", "SantaQuiteria", "IslaDeVieques", "Is"};

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
			GameInterface.(_tabName).(row).td2.str = GetCityName(cityId);
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetIslandName(rCity);
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
/*
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
*/

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
	int entryIndices[totalEntries];

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
			GameInterface.(_tabName).(row).td2.str = GetCityName(cityId);
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetIslandName(rCity);
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

// LDH 06Jul17
    string OurColonies[MAX_OURCOLONIES] = {"Havana", "Santiago", "PuertoPrincipe", "PortRoyal", "FortOrange", "Tortuga", "PortPax", "SantoDomingo", "LaVega", "Terks", "SanJuan", "Pirates", "Marigo", "Charles", "SentJons", "BasTer", "Dominica", "FortFrance", "LeFransua", "Bridgetown", "Villemstad", "PortSpein", "Cumana", "Caracas", "Maracaibo", "Cartahena", "PortoBello", "Panama", "Pearl", "SantaCatalina", "Beliz", "Caiman", "Tenotchitlan", "LosTeques", "LostShipsCity", "KhaelRoa", "Ksochitam", "RockIsland", "SantaQuiteria", "IslaDeVieques", "Is", "SanAndres"};

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
			GameInterface.(_tabName).(row).td2.str = GetCityName(cityId);
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = GetIslandName(rCity);
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
		    sText1  = GetAssembledString(GetGoodDescr(GameInterface.(CurTable).(CurRow).UserData.ID), &Goods[iItem]);
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
	//CreateTooltip(sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, 64, 64); // не компилится

}
void HideInfoWindow()
{
	CloseTooltip();
}