// Общие для инвентаря/торговли/обмена/лута функции представления предметов в интерфейсе, подсветки, метки и т. п.

void AddRecipeKnownMarker(ref item, string description)
{
	if (findsubstr(item.id, "recipe_" , 0) == -1) return;
	if (!isMultiObjectKnown(item.result)) return;

	description += GetConvertStr("newLine", "AbilityDescribe.txt") + xiStr("KnownMap") + ".";
}

void AddMapKnownMarker(ref item, string description)
{
	if (!CheckAttribute(&item, "GroupID") || item.groupID != MAPS_ITEM_TYPE) return;
	if (!CheckMapForEquipped(&pchar, item.id)) return;

	description += GetConvertStr("newLine", "AbilityDescribe.txt") + xiStr("KnownRecipe") + ".";
}

bool IsItemForChar(ref item, ref rchar)
{
	if (CheckAttribute(&item, "groupid") && item.groupid == MUSKET_ITEM_TYPE && CheckAttribute(&rchar, "CanTakeMushket")) return true; // заплатка для мушкетеров

	if (!CheckAttribute(&item, "descriptors.recommendFor")) return false;
	if (!CheckAttribute(&rchar, item.descriptors.recommendFor)) return false;
	return true;
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
		return GetConvertStr(refItem.describe, "mods\"+refItem.modname+"\ItemsDescribe.txt");
	}
	return GetConvertStr(refItem.describe, "ItemsDescribe.txt");
}

string GetItemDescribe(int iGoodIndex)
{
	return GetItemDescr(&iGoodIndex);
}

string GetItemType(ref ref_Id_Idx)
{
	ref item = FindItem_VT(&ref_Id_Idx);
	if (!CheckAttribute(item, "groupID")) return "";
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
