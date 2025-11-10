// Здесь таблица с эффектами экипировки персонажа
void CT_UpdateEquipTable(ref chr)
{
	if (!CheckAttribute(chr, "equip") && !CheckAttribute(chr, "equip_item")) return;
	DeleteAttribute(chr, "ct."+CT_EQUIP);

	aref table = CT_GetTable(chr, CT_EQUIP);
	aref equipment, item, itemAttr;
	string itemID;
	makearef(equipment, chr.equip);
	ApplyEquipModifiers(chr, &table, &equipment);
	makearef(equipment, chr.equip_item);
	ApplyEquipModifiers(chr, &table, &equipment);

	aref staticTable = CT_GetTable(chr, CT_STATIC);
	CT_MergeTables(&table, &staticTable); // подливаем статические модификаторы
	RunTableCallbacks(chr, CT_EQUIP, &table, &NullObject);
}

void ApplyEquipModifiers(ref chr, ref table, ref equipment)
{
	aref item;

	for (int i = 0; i < GetAttributesNum(equipment); i++)
	{
		string itemID = GetAttributeValue(GetAttributeN(equipment, i));
		if (itemID == "") continue;
		if (Items_FindItem(itemID, &item) < 0)
		{
			trace("ApplyEquipModifiers warning - can't find " + itemID + " item");
			continue;
		}
		string itemType = GetAttributeOrDefault(item, "groupId", "rest");
		ApplyItemModifiers(chr, &table, &item, itemType);
		ApplyItemDescriptors(chr, &table, &item, itemType);
	}
}

void ApplyItemDescriptors(ref chr, ref table, ref item, string itemType)
{
	if (!CheckAttribute(item, "descriptors")) return;
	aref descriptors, descriptor;
	makearef(descriptors, item.descriptors);
	for (int i = 0; i < GetAttributesNum(descriptors); i++)
	{
		descriptor = GetAttributeN(descriptors, i);
		string descriptorId = GetAttributeName(descriptor);
		table.descriptors.(descriptorId) = GetAttributeInt(table, "descriptors." + descriptorId) + 1;
		if (CheckAttribute(descriptor, "universal")) table.descriptors.(descriptorId).(itemType) = true;
	}
}

void ApplyItemModifiers(ref chr, ref table, ref item, string itemType)
{
	if (!CheckAttribute(item, "modifiers")) return;

	aref modifiers, modifier;
	makearef(modifiers, item.modifiers);
	for (int i = 0; i < GetAttributesNum(modifiers); i++)
	{
		modifier = GetAttributeN(modifiers, i);
		string modifierName = GetAttributeName(modifier);
		if (modifierName == "callbacks") MergeCallbacks(&table, &modifier);
		else if (modifierName == "has") MergeFlags(&table, &modifier);
		else MergeModifier(&table, &modifier, modifierName, itemType);
	}
}
