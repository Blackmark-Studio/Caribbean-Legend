

void RecalculateCharacterModifiers(ref rChar)
{
	
	trace("Recalculate modifiers for "+rChar.name);
	
	DeleteAttribute(rChar, "modifiers");
	aref arItm;
	int  i = 0;
	string itemType;
	if (!CheckAttribute(rChar, "equip"))
	{
		return;
	}
	
	aref charEquip;
	makearef(charEquip, rChar.equip);

	int equipmentNum = GetAttributesNum(charEquip);
	for (i = 0; i < equipmentNum; i++)
	{
		aref itemAttr = GetAttributeN(charEquip, i);
		string itemID = GetAttributeValue(itemAttr);
		if (itemID == "")
			continue;
		itemType = GetAttributeName(itemAttr);

		if (itemType == MUSKET_ITEM_TYPE && !CharUseMusket(rChar))
		{
			continue;
		}
		
		if (itemType == GUN_ITEM_TYPE || itemType == BLADE_ITEM_TYPE)
		{
			if (CharUseMusket(rChar)) // вложенные скобки почему-то не воспринимает движок
			{
				continue;
			}
		}

		if(Items_FindItem(itemID, &arItm) < 0)
		{
			trace("TakeNItems warning - can't find " + itemID + " item");
			continue;
		}
		
		ApplyItemModifiers(rChar, arItm);
	}
	
	if (CheckAttribute(rChar, "bullets"))
	{
		aref charBullets;
		makearef(charBullets, rChar.bullets);
		int bulletsNum = GetAttributesNum(charBullets);
		for (i = 0; i < bulletsNum; i++)
		{
			aref bulletAttr = GetAttributeN(charBullets, i);
			string bulletID = GetAttributeValue(bulletAttr);
			itemType = GetAttributeName(bulletAttr);


			if (itemType == MUSKET_ITEM_TYPE && !CharUseMusket(rChar))
			{
				continue;
			}
			 
			if (itemType == GUN_ITEM_TYPE && CharUseMusket(rChar))
			{
				continue;
			}

			if(Items_FindItem(bulletID, &arItm) < 0)
			{
				trace("TakeNItems warning - can't find " + bulletID + " item");
				continue;
			}
			
			ApplyItemModifiers(rChar, arItm);
		}
	}
	
	// Для возможности добавлять личные модификаторы, например для возможности дать персонажу доп. процент крита. Или наоборот убрать у него процент.
	if (CheckAttribute(rChar, "personalModifiers"))
	{
		aref personalModifiers;
		makearef(personalModifiers, rChar.personalModifiers);
		ApplyItemModifiers(rChar, personalModifiers);
	}
	
	
	trace("done recalculate modifiers for "+rChar.name);
	if (CheckAttribute(rChar, "modifiers"))
	{
		trace("with applied modifiers "+rChar.name);
		aref modifiers;
		makearef(modifiers, rChar.modifiers);
		DumpAttributes(modifiers);
	}
	else
	{
		trace("without applied modifiers "+rChar.name);
	}
	 
	
}

void ApplyItemModifiers(ref rChar, aref rItem)
{
	int i = 0;
	int skillIntCharValue = 0;
	float skillFloatCharValue = 0.0;
	bool skillBoolCharValue = false;
	int skillNum = 0;
	aref skillAttr;
	string skillValue;
	string skillName;
	string modifierType;
	
	if (CheckAttribute(rItem, "skills"))
	{
		aref itemSkills;
		makearef(itemSkills, rItem.skills);
		skillNum = GetAttributesNum(itemSkills);
		for (i = 0; i < skillNum; i++)
		{
			skillAttr = GetAttributeN(itemSkills, i);
			skillValue = GetAttributeValue(skillAttr);
			skillName = GetAttributeName(skillAttr);

			skillIntCharValue = 0;
			
			if (CheckAttribute(rChar, "modifiers.skills."+skillName))
			{
				skillIntCharValue = sti(rChar.modifiers.skills.(skillName));
			}
			
			skillIntCharValue += sti(skillValue);
			rChar.modifiers.skills.(skillName) = skillIntCharValue;
		}
	}
	
	if (CheckAttribute(rItem, "modifiers"))
	{
		aref itemModifiers;
		makearef(itemModifiers, rItem.modifiers);
		skillNum = GetAttributesNum(itemModifiers);
		for (i = 0; i < skillNum; i++)
		{
			skillAttr = GetAttributeN(itemModifiers, i);
			skillValue = GetAttributeValue(skillAttr);
			skillName = GetAttributeName(skillAttr);

			modifierType = FindStringBeforeChar(skillName, "_");
			
			switch (modifierType)
			{
				case "bool":
					skillBoolCharValue = false;
					if (CheckAttribute(rChar, "modifiers.modifiers."+skillName))
					{
						skillBoolCharValue = sti(rChar.modifiers.modifiers.(skillName));
					}
					skillBoolCharValue = skillBoolCharValue || sti(skillValue);
					rChar.modifiers.skills.(skillName) = skillBoolCharValue;
					break;
					
				case "mul":
					skillFloatCharValue = 1.0;
					if (CheckAttribute(rChar, "modifiers.modifiers."+skillName))
					{
						skillFloatCharValue = stf(rChar.modifiers.modifiers.(skillName));
					}
					skillFloatCharValue *= stf(skillValue);
					rChar.modifiers.skills.(skillName) = skillFloatCharValue;
					break;
					
				case "add":
					skillFloatCharValue = 0.0;
					if (CheckAttribute(rChar, "modifiers.modifiers."+skillName))
					{
						skillFloatCharValue = stf(rChar.modifiers.modifiers.(skillName));
					}
					skillFloatCharValue += stf(skillValue);
					rChar.modifiers.skills.(skillName) = skillFloatCharValue;
					break;
				
			}
		}
	}
}


void RecalculateModifiersForAllCharacters()
{
	for (int i = 0; i < GetArraySize(&Characters); i++)
	{
		ref rChar = &Characters[i];
		if (CharacterIsDead(rChar))
		{
			continue;
		}
		RecalculateCharacterModifiers(rChar);
	}
}