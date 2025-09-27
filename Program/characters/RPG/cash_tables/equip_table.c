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
	RunCharacterCallbacks(chr, CT_EQUIP, &table, &NullCharacter);
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
		string itemType = GetItemEquipmentType(item);
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
		if (modifierName == "callbacks") MergeCallbacks(chr, &modifier);
		else MergeModifier(&table, &modifier, modifierName, itemType);
	}
}

string GetItemEquipmentType(ref item)
{
	if (CheckAttribute(item, "groupId")) return item.groupId;
	return "rest";
}

// Складываем значения модификаторов
void MergeModifier(ref rObject, ref modifier, string modifierName, string sourceName)
{
	string modifierValue = GetAttributeValue(modifier);
	rObject.(modifierName) = GetAttributeFloat(rObject, modifierName) + stf(modifierValue);

	if (strleft(modifierName, 4) != HAS) rObject.(modifierName).(sourceName) = modifierValue;
}

// Коллбэки дописываем
void MergeCallbacks(ref rObject, ref modifier)
{
	aref callbacks;
	makearef(callbacks, rObject.callbacks);
	CopyAttributesSafe(callbacks, modifier);
}