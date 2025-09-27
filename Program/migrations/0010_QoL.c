void ApplyMigration(ref migrationState) {
	ref item;
	aref descriptors;

	// Раскидываем дескриптор для подсветки амулетов/оберегов/талисманов/тотемов в торговле и сундуках
	// Раскидываем акватории по картам
	for (int i = 0; i < ITEMS_QUANTITY; i++)
	{
		makeref(item, Items[i]);
		if (CheckAttribute(&item, "itemtype") && item.itemtype == "MAP")
		{
			switch (item.id)
			{
				case "map_antigua":    item.area = "Antigua";       break;
				case "map_barbados":   item.area = "Barbados";      break;
				case "map_beliz":      item.area = "Beliz";         break;
				case "map_bermudas":   item.area = "Bermudes";      break;
				case "map_cayman":     item.area = "Caiman";        break;
				case "map_maine_2":    item.area = "Caracas";       break;
				case "map_maine_1":    item.area = "Cartahena";     break;
				case "map_cumana":     item.area = "Cumana";        break;
				case "map_curacao":    item.area = "Curacao";       break;
				case "map_dominica":   item.area = "Dominica";      break;
				case "map_guad":       item.area = "Guadeloupe";    break;
				case "map_cuba":       item.area = "Cuba";          break;
				case "map_jam":        item.area = "Jamaica";       break;
				case "map_hisp":       item.area = "Hispaniola";    break;
				case "map_LSC":        item.area = "LostShipsCity"; break;
				case "map_maine_1":    item.area = "Maracaibo";     break;
				case "map_martiniqua": item.area = "Martinique";    break;
				case "map_nevis":      item.area = "Nevis";         break;
				case "map_panama":     item.area = "PortoBello";    break;
				case "map_perl":       item.area = "Providence";    break;
				case "map_puerto":     item.area = "PuertoRico";    break;
				case "map_santa":      item.area = "SantaCatalina"; break;
				case "map_sm":         item.area = "SentMartin";    break;
				case "map_terks":      item.area = "Terks";         break;
				case "map_tortuga":    item.area = "Tortuga";       break;
				case "map_trinidad":   item.area = "Trinidad";      break;
				case "a_map_antigua":    item.area = "Antigua";       break;
				case "a_map_barbados":   item.area = "Barbados";      break;
				case "a_map_beliz":      item.area = "Beliz";         break;
				case "a_map_bermudas":   item.area = "Bermudes";      break;
				case "a_map_cayman":     item.area = "Caiman";        break;
				case "a_map_maine_2":    item.area = "Caracas";       break;
				case "a_map_maine_1":    item.area = "Cartahena";     break;
				case "a_map_cumana":     item.area = "Cumana";        break;
				case "a_map_curacao":    item.area = "Curacao";       break;
				case "a_map_dominica":   item.area = "Dominica";      break;
				case "a_map_guad":       item.area = "Guadeloupe";    break;
				case "a_map_cuba":       item.area = "Cuba";          break;
				case "a_map_jam":        item.area = "Jamaica";       break;
				case "a_map_hisp":       item.area = "Hispaniola";    break;
				case "a_map_maine_1":    item.area = "Maracaibo";     break;
				case "a_map_martiniqua": item.area = "Martinique";    break;
				case "a_map_nevis":      item.area = "Nevis";         break;
				case "a_map_panama":     item.area = "PortoBello";    break;
				case "a_map_perl":       item.area = "Providence";    break;
				case "a_map_puerto":     item.area = "PuertoRico";    break;
				case "a_map_santa":      item.area = "SantaCatalina"; break;
				case "a_map_sm":         item.area = "SentMartin";    break;
				case "a_map_terks":      item.area = "Terks";         break;
				case "a_map_tortuga":    item.area = "Tortuga";       break;
				case "a_map_trinidad":   item.area = "Trinidad";      break;
			}

			if (findsubstr(item.id, "a_map_", 0) != -1) item.atlasType = "admiral";
			else if (CheckAttribute(&item, "area")) item.atlasType = "common";
			else if (CheckAttribute(&item, "ImageType") && item.ImageType == "cabin_map") item.atlasType = "region";
			else item.atlasType = "none";
		}

		if (!CheckAttribute(&item, "type")) continue;
		int itemType = item.Type;
		if (itemType != ITEM_INDIAN && itemType != ITEM_AMULET && itemType != ITEM_OBEREG && itemType != ITEM_TOTEM) continue;
	}

	// Выдаём карты в новый атлас
	aref arEquips, arEquip;
	string groupID = MAPS_ITEM_TYPE;
	
	makearef(arEquips, pchar.equip.(groupID));

	for(int j=0; j < GetAttributesNum(arEquips); j++)
	{
		arEquip = GetAttributeN(arEquips, j);
		string mapId = GetAttributeName(arEquip);
		ref map = ItemsFromID(mapId);

		if (CheckAttribute(&map, "area"))
		{
			string atlastype = map.atlastype;
			string area = map.area;
			Atlas.areas.(area).(atlastype) = map.id;
		}
		else if (map.ImageType == "cabin_map") Atlas.region.(mapId) = true;
		else if (sti(map.Atlas) != 0) Atlas.rest.(mapId) = true;
	}

	DeleteAttribute(pchar, "equip.maps");
	DeleteAttribute(pchar, "items.MapsAtlas");

	// Удаляем следы мода, если он был
	if (CheckAttribute(&objControlsState, "keygroups.primaryland.QoL_TakeAll"))
	{
		aref controls;
		makearef(controls, objControlsState.keygroups.primaryLand);
		DeleteAttribute(&controls, "QoL_TakeAll");
		DeleteAttribute(&controls, "QoL_Favorites");
	}

	// Вырезаем совместителя-универсала, ограничиваем по рангу совместителя
	aref perks;
	makearef(perks, ChrPerksList.list);
	DeleteAttribute(&perks, "ByWorker2");
	perks.ByWorker.rank = 15;
}
