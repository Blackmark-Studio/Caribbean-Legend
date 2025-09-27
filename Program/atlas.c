
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
	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	aref areas;
	makearef(areas, Atlas.areas);

	if (CheckAttributeHasValue(map, "area")) {
		string area = map.area;
		string atlasType = map.atlasType;
		areas.(area).(atlasType) = mapId;
	}
	else if (map.ImageType == "cabin_map") Atlas.region.(mapId) = true;
	else Atlas.rest.(mapId) = true;
	notification(StringFromKey("characterUtilite_12", LanguageConvertString(idLngFile, map.name)), "MapsAtlas");
	LanguageCloseFile(idLngFile);

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
		string map[MAPS_IN_ATLAS];
		map[0] = "map_jam";
		map[1] = "map_cayman";
		map[2] = "map_barbados";
		map[3] = "map_trinidad";
		map[4] = "map_Curacao";
		map[5] = "map_martiniqua";
		map[6] = "map_dominica";
		map[7] = "map_puerto";
		map[8] = "map_cuba";
		map[9] = "map_hisp";
		map[10] = "map_nevis";
		map[11] = "map_guad";
		map[12] = "map_antigua";
		map[13] = "map_TORTUGA";
		map[14] = "map_terks";
		map[15] = "map_sm";
		map[16] = "map_bermudas";
		map[17] = "map_beliz";
		map[18] = "map_santa";
		map[19] = "map_maine_1";
		map[20] = "map_maine_2";
		map[21] = "map_panama";
		map[22] = "map_cumana";

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
	string leftMaps[2];
	int n = 1;
	int mapQty = FillAdmiralMaps(map);

	for (int i = 0; i < mapQty; i++) {
		mapId = map[i];
		if (CheckMapForEquipped(pchar, mapId)) continue;
		SetArraySize(&leftMaps, n);
		leftMaps[n-1] = mapId;
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
	mapIds[0] = "A_map_bermudas";
	mapIds[1] = "A_map_jam";
	mapIds[2] = "A_map_cayman";
	mapIds[3] = "A_map_barbados";
	mapIds[4] = "A_map_tortuga";
	mapIds[5] = "A_map_curacao";
	mapIds[6] = "A_map_martiniqua";
	mapIds[7] = "A_map_dominica";
	mapIds[8] = "A_map_trinidad";
	mapIds[9] = "A_map_puerto";
	mapIds[10] = "A_map_cuba";
	mapIds[11] = "A_map_hisp";
	mapIds[12] = "A_map_nevis";
	mapIds[13] = "A_map_beliz";
	mapIds[14] = "A_map_guad";
	mapIds[15] = "A_map_santa";
	mapIds[16] = "A_map_antigua";
	mapIds[17] = "A_map_terks";
	mapIds[18] = "A_map_sm";
	mapIds[19] = "A_map_maine_1";
	mapIds[20] = "A_map_maine_2";
	mapIds[21] = "A_map_panama";
	mapIds[22] = "A_map_cumana";
	mapIds[23] = "A_map_perl";
	return 24;
}

void RemoveAllAdmiralMap()
{
	string mapId = "";
	string map[24];
	int n = 1;
	int mapQty = FillAdmiralMaps(map);
	for (int i = 0; i < mapQty; i++) {
		mapId = map[i];
		if (!CheckMapForEquipped(pchar, mapId)) continue;
		RemoveItems(pchar, mapId, 1);
	}
}

// Для совместимости
bool IsEquipCharacterByMap(ref chref, string itemID)
{
	return false;
}

// Для совместимости
int FindRealItem(string itemID, string handler) {
	return 0;
}

// Для совместимости
void CheckAdmiralMaps(ref chref) {
	return;
}

// Для совместимости
string IdentifyAdmiralMapLast()
{
	return "";
}

// Для совместимости
void PrepareAdmiralMaps() {
	return;
}

// Для совместимости
void GiveAdmiralAtlasToCharacter(ref chr)
{
	return;
}

// Для совместимости
bool CheckMainHeroMap(string itemName)
{
	return false;
}

void StoreEquippedMaps(ref refCh)
{
	return;
}

void RestoreEquippedMaps(ref refCh)
{
	return;
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
