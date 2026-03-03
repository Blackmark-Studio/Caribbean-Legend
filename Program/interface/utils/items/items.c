// Общие для инвентаря/торговли/обмена/лута функции представления предметов в интерфейсе, подсветки, метки и т. п.

void AddRecipeKnownMarker(ref item, ref description)
{
	if (findsubstr(item.id, "recipe_" , 0) == -1) return;
	if (!isMultiObjectKnown(item.result)) return;

	description += GetConvertStr("newLine", "AbilityDescribe.txt") + xiStr("KnownRecipe") + ".";
}

void AddMapKnownMarker(ref item, ref description)
{
	if (!CheckAttribute(&item, "GroupID") || item.groupID != MAPS_ITEM_TYPE) return;
	if (!CheckMapForEquipped(&pchar, item.id)) return;

	description += GetConvertStr("newLine", "AbilityDescribe.txt") + xiStr("KnownMap") + ".";
}

bool IsItemForChar(ref item, ref chr)
{
	if (CheckAttribute(item, "groupid") && item.groupid == MUSKET_ITEM_TYPE && CheckAttribute(&chr, "CanTakeMushket")) return true; // заплатка для мушкетеров

	object jobs;
	FillFellowJobs(chr, &jobs);
	for (int i = 0; i < GetAttributesNum(&jobs); i++)
	{
		aref job = GetAttributeN(&jobs, i);
		if (CheckAttribute(&item, "descriptors." + GetAttributeName(job))) return true;
	}

	return false;
}

string GetItemName(ref ref_Id_Idx)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);

	if (!CheckAttribute(refItem, "name")) return refItem.id;
	return GetConvertStr(refItem.name, "ItemsDescribe.txt");
}

string GetSimpleItemKey(string sKey)
{
    return GetConvertStr(sKey, "ItemsDescribe.txt");
}

string GetItemDescr(ref ref_Id_Idx)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);
	return DLG_Convert(refItem.describe, "ItemsDescribe.txt", refItem);
}

string GetItemUpgradeStage(ref ref_Id_Idx)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);

	string sKeyFile = "ItemsDescribe.txt";

	return GetConvertStr("UpgradeStageInfo_" + refItem.id + "_" + sti(refItem.UpgradeStage), sKeyFile);
}


string GetItemStat(ref ref_Id_Idx, string sStatName, bool bAllowEmpty)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);
	string sKeyFile = "ItemsStats.txt";

	if (sStatName == "mainEffect")
	{
		sStatName = refItem.id;
	}
	else if (sStatName == "secondaryEffect")
	{
		sStatName = "secondary_" + refItem.id;
	}

	if (bAllowEmpty)
	{
		return GetConvertStr("itm_stat_" + sStatName, sKeyFile);
	}
	else
	{
		return GetConvertStrB("itm_stat_" + sStatName, sKeyFile);
	}
}

string GetItemStatDescr(ref ref_Id_Idx, string sStatName)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);

	string sKeyFile = "ItemsStats.txt";

	if (sStatName == "mainEffect")
	{
		sStatName = refItem.id;
	}
	else if (sStatName == "secondaryEffect")
	{
		sStatName = "secondary_" + refItem.id;
	}

	return DLG_Convert("itm_stat_descr_" + sStatName, sKeyFile, refItem);
}


string GetSimpleItemStatKey(string sKey)
{
	return GetConvertStrB(sKey, "ItemsStats.txt");
}

string GetItemType(ref ref_Id_Idx)
{
	ref item = FindItem_VT(&ref_Id_Idx);
	if (HasDescriptor(item, "healPotion" )) return xiStr("items_Potions");
	if (!CheckAttribute(item, "groupID")) return xiStr("items_Other");
	return GetConvertStr("itmtype_" + item.groupID, "ItemsDescribe.txt");
}

// Усредняем урон от всех типов ударов для какого-то общего числа в интерфейсе
void WeaponSetVisualDamages(ref weapon, ref min, ref max)
{
	aref damages;
	makearef(damages, weapon.attack);
	min += GetAttributeInt(damages, FAST_STRIKE + ".min");
	min += GetAttributeInt(damages, FORCE_STRIKE + ".min");
	min += GetAttributeInt(damages, ROUND_STRIKE + ".min");
	min += GetAttributeInt(damages, BREAK_STRIKE + ".min");
	min = makeint(min*0.25);

	max += GetAttributeInt(damages, FAST_STRIKE + ".max");
	max += GetAttributeInt(damages, FORCE_STRIKE + ".max");
	max += GetAttributeInt(damages, ROUND_STRIKE + ".max");
	max += GetAttributeInt(damages, BREAK_STRIKE + ".max");
	max = makeint(max*0.25);
}
