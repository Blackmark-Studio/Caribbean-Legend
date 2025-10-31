// Общие для инвентаря/торговли/обмена/лута функции представления предметов в интерфейсе, подсветки, метки и т. п.

void AddRecipeKnownMarker(ref item, string description)
{
	if (findsubstr(item.id, "recipe_" , 0) == -1) return;
	if (!isMultiObjectKnown(item.result)) return;

	description += GetConvertStr("newLine", "AbilityDescribe.txt") + xiStr("KnownRecipe") + ".";
}

void AddMapKnownMarker(ref item, string description)
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

	if (CheckAttribute(refItem, "modname"))
	{
		return GetConvertStr(refItem.name, "mods\"+refItem.modname+"\ItemsDescribe.txt");
	}
	return GetConvertStr(refItem.name, "ItemsDescribe.txt");
}

string GetItemDescr(ref ref_Id_Idx)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);

	if (CheckAttribute(refItem, "modname"))
	{
		return DLG_Convert(refItem.describe, "mods\"+refItem.modname+"\ItemsDescribe.txt", refItem);
	}
	return DLG_Convert(refItem.describe, "ItemsDescribe.txt", refItem);
}

string GetItemDescribe(int iGoodIndex)
{
	return GetItemDescr(&iGoodIndex);
}

string GetItemType(ref ref_Id_Idx)
{
	ref item = FindItem_VT(&ref_Id_Idx);
	if (HasDescriptor(item, "healPotion" )) return xiStr("items_Potions");
	if (!CheckAttribute(item, "groupID")) return xiStr("items_Other");
	return GetConvertStr("itmtype_" + item.groupID, "ItemsDescribe.txt");
}

string GetItemNameBatch(ref ref_Id_Idx, ref files)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);

	if (!CheckAttribute(refItem, "name")) return refItem.id;

	string filename = "ItemsDescribe.txt";

	if (CheckAttribute(refItem, "modname"))
	{
		filename = "mods\"+refItem.modname+"\ItemsDescribe.txt";
	}

	int idLngFile = -1;

	if (CheckAttribute(files, filename))
	{
		idLngFile = sti(files.(filename));
	}
	else
	{
		idLngFile = LanguageOpenFile(filename);
		files.(filename) = idLngFile;
	}
	return LanguageConvertString(idLngFile, refItem.name);
}

string GetItemDescrBatch(ref ref_Id_Idx, ref files)
{
	ref refItem = FindItem_VT(&ref_Id_Idx);

	if (!CheckAttribute(refItem, "name"))
	{
		return refItem.id;
	}

	string filename = "ItemsDescribe.txt";

	if (CheckAttribute(refItem, "modname"))
	{
		filename = "mods\"+refItem.modname+"\ItemsDescribe.txt";
	}


	int    idLngFile = -1;

	if (CheckAttribute(files, filename))
	{
		idLngFile = sti(files.(filename));
	}
	else
	{
		idLngFile = LanguageOpenFile(filename);
		files.(filename) = idLngFile;
	}
	return LanguageConvertString(idLngFile, refItem.describe);
}

void CloseLanguageFilesBatch(ref files)
{
	int filesNum = GetAttributesNum(files);
	for (int i = 0; i < filesNum; i++) 
	{
		aref file = GetAttributeN(files, i);
		int idLngFile = sti(GetAttributeValue(file));
		LanguageCloseFile(idLngFile);
	}
	DeleteAttribute(files, "");
}

// Усредняем урон от всех типов ударов для какого-то общего числа в интерфейсе
void WeaponSetVisualDamages(ref weapon, int min, int max)
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
