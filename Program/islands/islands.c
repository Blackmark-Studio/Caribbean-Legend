#include "islands\islands_loader.c"

extern void InitIslands();
int iNumIslands = 0;

void IslandsInit()
{
	if(LoadSegment("islands\islands_init.c"))
	{
		InitIslands();
		UnloadSegment("islands\islands_init.c");
	}
}

ref GetIslandByIndex(int iIslandIndex) 
{ 
	return &Islands[iIslandIndex]; 
}

ref GetIslandByID(string sIslandID) 
{
	for (int i=0;i<MAX_ISLANDS;i++)
	{
		if (Islands[i].id == sIslandID) return &Islands[i];
	}
	//Trace("Invalid island ID: " + sIslandID);
	return &Islands[0];
}

aref FindIslandReloadLocator(string sIslandID, string sLocatorName)
{
	aref	arReload, arLocator;

	int		iIsland = FindIsland(sIslandID);
	if (iIsland < 0)
	{
		Trace("Can't find island sIslandID = " + sIslandID );
		return arLocator;
	}
	ref		rIsland = GetIslandByIndex(iIsland);
	makearef(arReload, rIsland.reload);
	int		iNumReload = GetAttributesNum(arReload);
	for (int i=0;i<iNumReload;i++)
	{
		arLocator = GetAttributeN(arReload, i);
		if (CheckAttribute(arLocator,"Name") && arLocator.Name == sLocatorName)
		{
			return arLocator;
		}
	}
	Trace("Can't find locator = " + sLocatorName + " on island sIslandID = " + sIslandID );
	return arLocator;
}

int FindIsland(string id)
{
	if (id=="") return -1;
	for(int n = 0; n<MAX_ISLANDS; n++)
	{
		if(Islands[n].id == id) return n;
	}
	return -1;
}

void Island_SetReloadEnableGlobal(string sIslandID, bool bEnable)
{
	ref rIsland = GetIslandByID(sIslandID);
	rIsland.reload_enable = bEnable;
}

void Island_SetReloadEnableLocal(string sIslandID, string sLocatorID, bool bEnable)
{
	aref arIslandReloadLocator = FindIslandReloadLocator(sIslandID, sLocatorID);
	arIslandReloadLocator.enable = bEnable;
}

bool Island_isReloadEnableGlobal(string sIslandID)
{
	ref rIsland = GetIslandByID(sIslandID);
	return sti(rIsland.reload_enable);
}

bool Island_isReloadFort(string sIslandID, string sLocatorID)
{
	aref arIslandReloadLocator = FindIslandReloadLocator(sIslandID, sLocatorID);
	if (CheckAttribute(arIslandReloadLocator,"fort")) return true;
	return false;
}

bool Island_isReloadEnableLocal(string sIslandID, string sLocatorID)
{
	aref arIslandReloadLocator = FindIslandReloadLocator(sIslandID, sLocatorID);
	if (!CheckAttribute(arIslandReloadLocator,"enable")) return true;
	return sti(arIslandReloadLocator.enable);
}

void Island_SetGotoEnableLocal(string sIslandID, string sLocatorID, bool bEnable)
{
	aref arIslandReloadLocator = FindIslandReloadLocator(sIslandID, sLocatorID);
	arIslandReloadLocator.goto_enable = bEnable;
}

bool Island_isGotoEnableLocal(string sIslandID, string sLocatorID)
{
	aref arIslandReloadLocator = FindIslandReloadLocator(sIslandID, sLocatorID);
	if (!CheckAttribute(arIslandReloadLocator,"goto_enable")) return true;
	return sti(arIslandReloadLocator.goto_enable);
}

void Island_SetEncountersEnable(string sIslandID, bool bEnable)
{
	ref rIsland = GetIslandByID(sIslandID);
	rIsland.Enc_enable = bEnable;
}

bool Island_IsEncountersEnable(string sIslandID)
{
	ref rIsland = GetIslandByID(sIslandID);
	if (!CheckAttribute(rIsland, "Enc_enable")) return true;
	return sti(rIsland.Enc_enable);
}

int FindIslandBySeaLocation(string locID)
{
	int n,m;
	aref arroot,arreload;
	for(n=0; n<MAX_ISLANDS; n++)
	{
		makearef(arroot,Islands[n].reload);
		for(m=0; m<GetAttributesNum(arroot); m++)
		{
			arreload = GetAttributeN(arroot,m);
			if(arreload.go == locID) return n;
		}
	}
	return -1;
}
// boal -->
////////////
bool FindIslandLocatorXYZ(string _islandId, string _locator, ref float_x, ref float_y, ref float_z)
{
    int   i;
	ref   rIsl;
	aref  rl, at;

	i = FindIsland(_islandId);
	if (i != -1)
	{
        rIsl = GetIslandByIndex(i);
		makearef(rl, rIsl.reload);

		int num = GetAttributesNum(rl);
		int disableVal = 0;
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(rl, i);
			if(at.name == _locator)
			{
				if (CheckAttribute(at, "x"))
				{
					float_x = stf(at.x); float_y = stf(at.y); float_z = stf(at.z);
				}
				else
				{
				    trace("!!!!!! FindIslandLocatorXYZ  нет локатора " + _locator + " остров " + _islandId);
				}
				return true;
			}
		}
	}
	return false;
}
// boal <--

// Warship, 17.05.11.
// Функция вернет локатор перехода, который используется для перехода ИЗ МОРЯ указанного острова в указанную локацию.
string Island_GetLocationReloadLocator(string _island, string _location)
{
	int i, reloadsCount;
	ref island;
	aref reloadNode, reloadLocator;
	
	i = FindIsland(_island);
	
	if(i == -1) return "";
	
	island = &Islands[i];
	
	makearef(reloadNode, island.reload);
	
	reloadsCount = GetAttributesNum(reloadNode);
	
	for(i = 0; i < reloadsCount; i++)
	{
		reloadLocator = GetAttributeN(reloadNode, i);
		
		if(reloadLocator.go == _location)
		{
			return reloadLocator.name;
		}
	}
	
	return "";
}

// belamour новый метод поиска рандомного острова
string GetRandIslandId()
{
	int n;
    int islandsArray[2];
	SetArraySize(&islandsArray, MAX_ISLANDS);
	int iNum = 0;
	
	for (n=0;n<MAX_ISLANDS;n++)
	{
		if(Islands[n].id == "LostShipsCity") continue;
		if(Islands[n].id == "KhaelRoa") continue;
		if(Islands[n].id == "Ksochitam") continue;
		if(Islands[n].id == "RockIsland") continue;
		if(Islands[n].id == "Providence") continue;
		if(Islands[n].id == "SantaQuiteria") continue;
		if(Islands[n].id == "IslaDeVieques") continue;
		if(Islands[n].id == "IslaMona") continue;
		if(Islands[n].id == "IslaDeCoche") continue;
		if(Islands[n].id == "") continue;
		
		islandsArray[iNum] = n;
		iNum++;
	}
	if (iNum == 0) return "none";
	n = islandsArray[rand(iNum-1)];
	trace("Остров с индексом " + n + " имеет айди " + Islands[n].id);
	return Islands[n].id;
}

// Warship, 25.05.11
// Метод возвращает идентификатор локации маяка, которая расположена на острове с указанной колонией.
/*string Island_GetLighthouseId(string _islandId)
{
	int i, reloadsCount;
	ref island = GetIslandByID(_islandId);
	aref reloadNode, reloadLocator;
	
	makearef(reloadNode, island.reload);
	
	reloadsCount = GetAttributesNum(reloadNode);
	
	for(i = 0; i < reloadsCount; i++)
	{
		reloadLocator = GetAttributeN(reloadNode, i);
		
		if(HasSubStr(reloadLocator.go, "mayak"))
		{
			return reloadLocator.go;
		}
	}
	
	return "";
}*/ // Jason: функция работает некорректно, сделал более надежным способом через иниты. Функция в colonies.c