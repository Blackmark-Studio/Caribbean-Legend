

void RecalculateCharacterModifiers(ref rChar)
{
	
	trace("Recalculate modifiers for "+rChar.name);
	
	DeleteAttribute(rChar, "modifiers");
	aref arItm;
	int  i = 0;
	int num = 0;
	string itemType;
	string itemID;
	if (!CheckAttribute(rChar, "equip"))
	{
		return;
	}
	
	aref charEquip;
	makearef(charEquip, rChar.equip);

	num = GetAttributesNum(charEquip);
	for (i = 0; i < num; i++)
	{
		aref itemAttr = GetAttributeN(charEquip, i);
		itemID = GetAttributeValue(itemAttr);
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
			trace("RecalculateCharacterModifiers warning - can't find " + itemID + " item");
			continue;
		}
		
		ApplyItemModifiers(rChar, arItm, itemID, false);
	}
	
	if (CheckAttribute(rChar, "equip_item"))
	{

        makearef(charEquip, rChar.equip_item);
        num = GetAttributesNum(charEquip);

        for (i=0; i < num; i++)
        {
            itemID = GetAttributeValue(GetAttributeN(charEquip, i));
            if(itemID == "")
			{
				continue;
			}
            if(Items_FindItem(itemID, &arItm) < 0)
			{
				trace("RecalculateCharacterModifiers warning - can't find " + itemID + " item");
				continue;
			}

            ApplyItemModifiers(rChar, arItm, itemID, false);
        }
	}

	if (CheckAttribute(rChar, "bullets"))
	{
		aref charBullets;
		makearef(charBullets, rChar.bullets);
		num = GetAttributesNum(charBullets);
		for (i = 0; i < num; i++)
		{
			aref bulletAttr = GetAttributeN(charBullets, i);
			itemID = GetAttributeValue(bulletAttr);
			itemType = GetAttributeName(bulletAttr);


			if (itemType == MUSKET_ITEM_TYPE && !CharUseMusket(rChar))
			{
				continue;
			}
			 
			if (itemType == GUN_ITEM_TYPE && CharUseMusket(rChar))
			{
				continue;
			}

			if(Items_FindItem(itemID, &arItm) < 0)
			{
				trace("RecalculateCharacterModifiers warning - can't find " + itemID + " item");
				continue;
			}
			
			ApplyItemModifiers(rChar, arItm, itemID, false);
		}
	}
	
	// Для возможности добавлять личные модификаторы, например для возможности дать персонажу доп. процент крита. Или наоборот убрать у него процент.
	if (CheckAttribute(rChar, "personalModifiers"))
	{
		aref personalModifiers;
		makearef(personalModifiers, rChar.personalModifiers);
		ApplyItemModifiers(rChar, personalModifiers, "Character_"+rChar.id, false);
	}
	
	
	// Пассивные скиллы для предметов просто в инвентаре
	if (CheckAttribute(rChar, "items"))
	{
        makearef(charEquip, rChar.items);
        num = GetAttributesNum(charEquip);

        for (i=0; i < num; i++)
        {
            itemID = GetAttributeName(GetAttributeN(charEquip, i));
            if(itemID == "")
			{
				continue;
			}
            if(Items_FindItem(itemID, &arItm) < 0)
			{
				trace("RecalculateCharacterModifiers warning - can't find " + itemID + " item");
				continue;
			}

            ApplyItemModifiers(rChar, arItm, itemID, true);
        }
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

void ApplyItemModifiers(ref rChar, aref rItem, string itemID, bool bPassive)
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
	
	string prefix = "";
	if (bPassive)
	{
		prefix = "passive_";
	}
	
	string skillsAttr = prefix+"skills";
	string modifiersAttr = prefix+"modifiers";
	if (CheckAttribute(rItem, skillsAttr))
	{
		aref itemSkills;
		makearef(itemSkills, rItem.(skillsAttr));
		skillNum = GetAttributesNum(itemSkills);
		for (i = 0; i < skillNum; i++)
		{
			skillAttr = GetAttributeN(itemSkills, i);
			skillValue = GetAttributeValue(skillAttr);
			skillName = GetAttributeName(skillAttr);
			if (CheckAttribute(skillAttr, "callback"))
			{
				rChar.modifiers.skills.(skillName).(itemID) = skillAttr.callback;
				continue;
			}

			skillIntCharValue = 0;
			
			if (CheckAttribute(rChar, "modifiers.skills."+skillName))
			{
				skillIntCharValue = sti(rChar.modifiers.skills.(skillName));
			}
			
			skillIntCharValue += sti(skillValue);
			rChar.modifiers.skills.(skillName) = skillIntCharValue;
		}
	}
	
	if (CheckAttribute(rItem, modifiersAttr))
	{
		aref itemModifiers;
		makearef(itemModifiers, rItem.(modifiersAttr));
		skillNum = GetAttributesNum(itemModifiers);
		for (i = 0; i < skillNum; i++)
		{
			skillAttr = GetAttributeN(itemModifiers, i);
			skillValue = GetAttributeValue(skillAttr);
			skillName = GetAttributeName(skillAttr);
			if (CheckAttribute(skillAttr, "callback"))
			{
				rChar.modifiers.modifiers.(skillName).(itemID) = skillAttr.callback;
				continue;
			}
			
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
					rChar.modifiers.modifiers.(skillName) = skillBoolCharValue;
					break;
					
				case "mul":
					skillFloatCharValue = 1.0;
					if (CheckAttribute(rChar, "modifiers.modifiers."+skillName))
					{
						skillFloatCharValue = stf(rChar.modifiers.modifiers.(skillName));
					}
					skillFloatCharValue *= stf(skillValue);
					rChar.modifiers.modifiers.(skillName) = skillFloatCharValue;
					break;
					
				case "add":
					skillFloatCharValue = 0.0;
					if (CheckAttribute(rChar, "modifiers.modifiers."+skillName))
					{
						skillFloatCharValue = stf(rChar.modifiers.modifiers.(skillName));
					}
					skillFloatCharValue += stf(skillValue);
					rChar.modifiers.modifiers.(skillName) = skillFloatCharValue;
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