string GetHumanReadableReason(string sourceName, ref chr)
{
	bool replaceByEquipName = false;

	switch (sourceName)
	{
		case GUN_ITEM_TYPE: replaceByEquipName = true; break;
		case BLADE_ITEM_TYPE: replaceByEquipName = true; break;
		case SPYGLASS_ITEM_TYPE: replaceByEquipName = true; break;
		case PATENT_ITEM_TYPE: replaceByEquipName = true; break;
		case CIRASS_ITEM_TYPE: replaceByEquipName = true; break;
		case MAPS_ITEM_TYPE: replaceByEquipName = true; break;
		case TOOL_ITEM_TYPE: replaceByEquipName = true; break;
		case TALISMAN_ITEM_TYPE: replaceByEquipName = true; break;
		case SPECIAL_ITEM_TYPE: replaceByEquipName = true; break;
		case AMMO_ITEM_TYPE: replaceByEquipName = true; break;
		case LANTERN_ITEM_TYPE: replaceByEquipName = true; break;
		case HAT_ITEM_TYPE: replaceByEquipName = true; break;
		case MUSKET_ITEM_TYPE: replaceByEquipName = true; break;
		case ITEM_SLOT_TYPE: return xiStr("Items_Amulets"); break;
	}

	// источником является предмет экипировки
	if (replaceByEquipName)
	{
		string itemId = GetCharacterEquipByGroup(chr, sourceName);
		return GetItemName(itemId);
	}

	// источником является перк через модификаторы
	if (CheckAttribute(ChrPerksList, "list." + sourceName)) return GetPerkName(sourceName);

	// источником является коллбэк от перка
	if (HasSubStr(sourceName, "Perk_"))
	{
		DLG_ReplaceAllMatches(&sourceName, "Perk_", "", 0);
		return GetPerkName(sourceName);
	}

	// прочие источники
	return GetConvertStrB("Source"+sourceName, "RPGDescribe.txt");
}

string GetModifierName(string modifier)
{
	return GetConvertStrB(modifier, "Modifiers.txt");
}