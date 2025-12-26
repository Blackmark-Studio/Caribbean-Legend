
// Есть ли карта в Атласе игрока
bool CheckMapForEquipped(ref _refCh, string itemID)
{
	ref item = ItemsFromID(itemID);

	if (CheckAttributeHasValue(item, "area")) {
		string area = item.area;
		string atlasType = item.atlasType;
		if (CheckAttribute(&Atlas, "areas." + area + "." + atlasType)) return true;
	}
	else if (CheckAttribute(&Atlas, "region." + itemID)) return true;
	else if (CheckAttribute(&Atlas, "rest." + itemID)) return true;

	return false;
}

// Получить ключ локализации для показа карты в интерфейсе атласа
string GetMapShownKey(ref map)
{
	if (map.id == "MAP_LSC") return "LostShipsCity";
	if (map.atlasType == "region") return "archipelago";
	if (CheckAttributeHasValue(map, "area")) return map.area;
	return map.name;
}

// Получить обычную по адмиральской и наоборот. Если обратной нет, вернём ту же. Карты региона перебираем от лучшей к худшей и по кругу
ref GetMapSwitch(ref mapEntity)
{
	aref region;
	makearef(region, Atlas.region);
	ref map = FindItem_VT(&mapEntity);
	if (map.atlasType == "region")
	{
		int regionMapsQty = GetAttributesNum(region);
		for (int i=0; i< GetAttributesNum(region); i++)
		{
			aref regionMap = GetAttributeN(region, i);
			string regionMapId = GetAttributeName(regionMap);
			if (regionMapId != map.id) continue; 
			if (i-1 < 0) return ItemsFromID(GetAttributeName(GetAttributeN(region, regionMapsQty-1)));
			return ItemsFromID(GetAttributeName(GetAttributeN(region, i-1)));
		}
	}

	if (!CheckAttributeHasValue(map, "area")) return map;
	string area = map.area;
	string newType = "admiral";
	if (map.atlasType == "admiral") newType = "common";

	if (CheckAttribute(&Atlas, "areas." + area + "." + newType)) return ItemsFromID(Atlas.areas.(area).(newType));
	return map;
}

// В атласе есть что показать игроку
bool IsAtlasNotEmpty()
{
	aref maps;
	makearef(maps, Atlas.region);
	if (GetAttributesNum(maps) > 0) return true;

	makearef(maps, Atlas.areas);
	if (GetAttributesNum(maps) > 0) return true;

	makearef(maps, Atlas.rest);
	return GetAttributesNum(maps) > 0;
}

// Лучшая карта региона
string GetBestRegionMap()
{
	if (CheckAttribute(&Atlas, "region.map_best")) return "map_best";
	if (CheckAttribute(&Atlas, "region.map_normal")) return "map_normal";
	if (CheckAttribute(&Atlas, "region.map_bad")) return "map_bad";
	return "";
}

// belamour имеется ли релевантная карта (местоположение)
string FindAtlasMap(ref mapId)
{
	mapId = MapFromCurPos();
	if (mapId == "") return "";
	
	ref map = ItemsFromID(mapId);
	return GetBestMapByArea(map.area);
}

string GetBestMapByArea(string area)
{
	if (CheckAttribute(&Atlas, "areas." + area + ".common")) return Atlas.areas.(area).common;
	if (CheckAttribute(&Atlas, "areas." + area + ".admiral")) return Atlas.areas.(area).admiral;
	return "";
}

int FillAreaMapsIds(ref mapsIds)
{
	aref areas, area;
	int n = 1;
	makearef(areas, Atlas.areas);

	int maxIndex = GetAttributesNum(areas);
	if (maxIndex < 1) return 0;
	SetArraySize(mapsIds, maxIndex);

	for(int i = 0; i < maxIndex; i++) 
	{
		area = GetAttributeN(areas, i);
		if (CheckAttribute(area, "admiral")) mapsIds[i] = area.admiral;
		else mapsIds[i] = area.common;
		n++;
	}

	return n-1;
}

bool IsAtlasMap(ref map)
{
	return CheckAttribute(map, "atlasType") && map.atlasType != "none";
}

bool IsTreasureMap(ref map)
{
	return map.maptype == "full" || map.maptype == "part"
}

// проверка - есть ли новые карты для включения в атлас
void RefreshEquippedMaps(ref chref)
{
	aref arItems;
	ref item;
	makearef(arItems, chref.items);

	for (int a = 0; a < GetAttributesNum(arItems); a++)
	{
		string itemID = GetAttributeName(GetAttributeN(arItems, a));
		item = ItemsFromID(itemID);
		if (!CheckAttribute(item, "GroupID") || item.groupID != MAPS_ITEM_TYPE) continue;
		if (CheckMapForEquipped(chref, itemID)) continue;
		if (IsTreasureMap(item)) continue;
		AddMapToPlayerAtlas(item);
	}
}

string GetMapArea(ref mapEntity)
{
	ref map = FindItem_VT(&mapEntity);
	if (CheckAttribute(map, "area")) return map.area;
	return "";
}

// Добавить в атлас игрока карту по ref или id или index
void AddMapToPlayerAtlas(ref mapEntity)
{
	ref map = FindItem_VT(&mapEntity);
	string mapId = map.id;
	aref areas;
	makearef(areas, Atlas.areas);
	bool notify = false;

	if (CheckAttributeHasValue(map, "area")) {
		notify = true;
		string area = map.area;
		string atlasType = map.atlasType;
		areas.(area).(atlasType) = mapId;
	}
	else if (map.ImageType == "cabin_map") 
	{
		Atlas.region.(mapId) = true;
		notify = true;
	}
	else Atlas.rest.(mapId) = true;
	if (notify) Notification(StringFromKey("characterUtilite_12", GetItemName(map)), "MapsAtlas");

	pchar.MapsAtlasCount = CountAreasMapFromCharacter();
	// даем скрытый перк если собрали все карты островов
	if (sti(pchar.MapsAtlasCount) == MAPS_IN_ATLAS && !CheckCharacterPerk(pchar, "MapMaker"))
	{
		SetCharacterPerk(pchar, "MapMaker");
	}
}

// Выбор обычной неповторяющейся карты
string SelectUsualMaps(ref item, ref qMiss)
{
		string map[MAPS_IN_ATLAS] = {"map_jam", "map_cayman", "map_barbados", "map_trinidad", "map_Curacao", "map_martiniqua", "map_dominica", "map_puerto", "map_cuba", "map_hisp", "map_nevis", "map_guad", "map_antigua", "map_TORTUGA", "map_terks", "map_sm", "map_bermudas", "map_beliz", "map_santa", "map_maine_1", "map_maine_2", "map_panama", "map_cumana"};

		string storeArray[MAPS_IN_ATLAS];
		int howStore = 0;
		string sTemp;

		if(qMiss > 0)
		{
			for (int i = 0; i < MAPS_IN_ATLAS; i++)
			{
					sTemp = map[i];
					if (!CheckMapForEquipped(pchar, sTemp) && !CheckAttribute(item, "BoxTreasure." + sTemp))
					{
							storeArray[howStore] = sTemp;
							howStore++;
					}
			}
			qMiss--;
		}
		else howStore = MAPS_IN_ATLAS; // У игрока на пару с текущим кладом имеются все карты, теперь можно рандомить любую

		if (bTrHash)
		{
			sTrSubTag += "µ";
			return storeArray[hrand(howStore - 1, sTrTag + sTrSubTag)];
		}

		return storeArray[rand(howStore - 1)];
}

// Выбор случайной карты из ещё не найденных, либо просто случайной, если найдены все
string SelectAdmiralMaps() 
{
	string mapId = "";
	string map[24];
	string leftMaps[];
	int n = 1;
	int mapQty = FillAdmiralMaps(&map);

	for (int i = 0; i < mapQty; i++) {
		mapId = map[i];
		if (CheckMapForEquipped(pchar, mapId)) continue;
		leftMaps += mapId;
		n++;
	}

	if (n == 1) return map[rand(mapQty-1)];
	return leftMaps[rand(n - 2)];
}

// Дать случайную с рандомом как предмет, записать в Атлас, если ещё не
void GiveAdmiralMapToCharacter(ref chr, int abl) 
{
	if (!CheckAttribute(pchar, "questTemp.AdmiralMap")) return;
	if (hrand(abl, chr.id + chr.name) == 0)
	{
		string amap = SelectAdmiralMaps();
		GiveItem2Character(chr, amap);
		if (IsMainCharacter(chr)) AddMapToPlayerAtlas(amap);
	}
}

// Дать конкретную карту, записать в Атлас, если ещё не
void TargetAdmiralMapToCharacter(ref chr, string amap) 
{
	if (!CheckAttribute(pchar, "questTemp.AdmiralMap")) return;
	GiveItem2Character(chr, amap);
	if (IsMainCharacter(chr)) AddMapToPlayerAtlas(amap);
}

// сосчитать адмиральские
int CountAdmiralMapFromCharacter() 
{
	aref areas, area;
	makearef(areas, Atlas.areas);
	int n = 0;

	for (int i=0; i < GetattributesNum(areas);i++)
	{
		area = GetAttributeN(areas, i);
		if (CheckAttribute(area, "admiral")) n++;
	}

	return n;
}

bool HasAllMaps(string type)
{
	if (type == "admiral") return CountAdmiralMapFromCharacter() == MAPS_IN_ATLAS;
	return CountAreasMapFromCharacter() == MAPS_IN_ATLAS;
}

// Сосчитать карты акваторий
int CountAreasMapFromCharacter() 
{
	aref areas, area;
	makearef(areas, Atlas.areas);
	int n = 0;

	for (int i=0; i < GetattributesNum(areas);i++)
	{
		area = GetAttributeN(areas, i);
		if (CheckAttribute(area, "common")) n++;
	}

	return n;
}

int FillAdmiralMaps(ref mapIds)
{
    mapIds = {"A_map_bermudas", "A_map_jam", "A_map_cayman", "A_map_barbados", "A_map_tortuga", "A_map_curacao", "A_map_martiniqua", "A_map_dominica", "A_map_trinidad", "A_map_puerto", "A_map_cuba", "A_map_hisp", "A_map_nevis", "A_map_beliz", "A_map_guad", "A_map_santa", "A_map_antigua", "A_map_terks", "A_map_sm", "A_map_maine_1", "A_map_maine_2", "A_map_panama", "A_map_cumana", "A_map_perl"};
    return GetArraySize(mapIds);
}

void RemoveAllAdmiralMap()
{
	string mapId = "";
	string map[24];
	int n = 1;
	int mapQty = FillAdmiralMaps(&map);
	for (int i = 0; i < mapQty; i++) {
		mapId = map[i];
		if (!CheckMapForEquipped(pchar, mapId)) continue;
		RemoveItems(pchar, mapId, 1);
	}
}

// Для совместимости
bool CheckMainHeroMap(string itemName)
{
	return false;
}

string GetMapByArea(string areaName)
{
	if(areaName == "" || areaName == "none" ) return "";
	switch (areaName)
	{
		case "Antigua":       return "map_antigua";    break;
		case "Barbados":      return "map_barbados";   break;
		case "Beliz":         return "map_beliz";      break;
		case "Bermudes":      return "map_bermudas";   break;
		case "Caiman":        return "map_cayman";     break;
		case "Caracas":       return "map_maine_2";    break;
		case "Cartahena":     return "map_maine_1";    break;
		case "Cumana":        return "map_cumana";     break;
		case "Curacao":       return "map_curacao";    break;
		case "Dominica":      return "map_dominica";   break;
		case "Guadeloupe":    return "map_guad";       break;
		case "Cuba1":         return "map_cuba";       break;
		case "Cuba2":         return "map_cuba";       break;
		case "Jamaica":       return "map_jam";        break;
		case "Hispaniola1":   return "map_hisp";       break;
		case "Hispaniola2":   return "map_hisp";       break;
		case "LostShipsCity": return "map_LSC";        break;
		case "Maracaibo":     return "map_maine_1";    break;
		case "Martinique":    return "map_martiniqua"; break;
		case "Nevis":         return "map_nevis";      break;
		case "Panama":        return "map_panama";     break;
		case "PortoBello":    return "map_panama";     break;
		//case "Providence":    return "map_perl";       break;
		case "PuertoRico":    return "map_puerto";     break;
		case "SantaCatalina": return "map_santa";      break;
		case "SentMartin":    return "map_sm";         break;
		case "Terks":         return "map_terks";      break;
		case "Tortuga":       return "map_tortuga";    break;
		case "Trinidad":      return "map_trinidad";   break;
	}

 return "";
}

// belamour карта острова от положения игрока
string MapFromCurPos()
{
	string curLocId = pchar.location;
	string mapLoc = "";
	string mapId = "";

	if(curLocId == "") return "";
	if(IsEntity(&worldMap)) return ""; // Для интерфейсных методов (?), а так можно worldMap.island брать

	if(bSeaActive)
	{
		if(!bAbordageStarted) mapLoc = curLocId;
		else mapLoc = boarding_adr[0].location;
	}
	else
	{
		ref loc = &locations[FindLocation(pchar.location)];
		mapLoc = GiveArealByLocation(loc);
	}
	return GetMapByArea(mapLoc);
}
