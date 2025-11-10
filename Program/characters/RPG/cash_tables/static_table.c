// Здесь таблица со статичными модификаторами самого персонажа, типа перков или квестовых бонусов
// Она не обновляется с нуля, значения просто дописываются/удаляются по необходимости

// Выставляем модификатор персонажу с конкретным значением
void SetChrModifier(ref chr, string modifier, ref value, string sourceName)
{
	aref table = CT_GetTable(chr, CT_STATIC);
	SetModifierFromSourceDirect(&table, modifier, value, sourceName);
}

// Увеличиваем модификатор персонажа
void IncreaseChrModifier(ref chr, string modifier, ref value, string sourceName)
{
	aref table = CT_GetTable(chr, CT_STATIC);
	IncreaseModifierFromSourceDirect(&table, modifier, value, sourceName);
}

// Увеличиваем модификатор персонажа и таблицы суши, таким образом не нужно пересчитывать все таблички
void IncreaseLandModifier(ref chr, string modifier, ref value, string sourceName)
{
	aref staticTable = CT_GetTable(chr, CT_STATIC);
	aref equipTable = CT_GetTable(chr, CT_EQUIP);
	aref landTable = CT_GetTable(chr, CT_LAND);
	IncreaseModifierFromSourceDirect(&staticTable, modifier, value, sourceName);
	IncreaseModifierFromSourceDirect(&equipTable, modifier, value, sourceName);
	IncreaseModifierFromSourceDirect(&landTable, modifier, value, sourceName);
}

// Увеличиваем модификатор персонажа по скиллам/пиратес не пересчитывая все таблички
void IncreaseCommonModifier(ref chr, string modifier, ref value, string sourceName)
{
	aref staticTable = CT_GetTable(chr, CT_STATIC);
	aref equipTable = CT_GetTable(chr, CT_EQUIP);
	aref commonTable = CT_GetTable(chr, CT_COMMON);
	IncreaseModifierFromSourceDirect(&staticTable, modifier, value, sourceName);
	IncreaseModifierFromSourceDirect(&equipTable, modifier, value, sourceName);
	IncreaseModifierFromSourceDirect(&commonTable, modifier, value, sourceName);
}

// Удаляем модификаторы с персонажа по названию источника
void RemoveChrModifier(ref chr, string sourceName)
{
	aref table = CT_GetTable(chr, CT_STATIC);
	for (int i = 0; i < GetAttributesNum(table); i++)
	{
		aref modifier = GetAttributeN(table, i);
		if (!CheckAttribute(modifier, sourceName)) continue;

		string modifierName = GetAttributeName(modifier);
		float value = stf(modifier.(sourceName));
		table.(modifierName) = stf(GetAttributeValue(modifier)) - value; // вычитаем эффект
		DeleteAttribute(modifier, sourceName);                           // убираем источник
	}
}

// Удаляем модификаторы суши с персонажа по названию источника без обсчёта таблиц
void RemoveLandModifier(ref chr, string sourceName)
{
	aref staticTable = CT_GetTable(chr, CT_STATIC);
	aref landTable = CT_GetTable(chr, CT_LAND);
	aref equipTable = CT_GetTable(chr, CT_EQUIP);
	for (int i = 0; i < GetAttributesNum(staticTable); i++)
	{
		aref modifier = GetAttributeN(staticTable, i);
		if (!CheckAttribute(modifier, sourceName)) continue;

		string modifierName = GetAttributeName(modifier);
		float value = GetAttributeFloat(modifier, sourceName);
		DeleteSourceFromTable(&staticTable, modifierName, sourceName, value);
		DeleteSourceFromTable(&equipTable, modifierName, sourceName, value);
		DeleteSourceFromTable(&landTable, modifierName, sourceName, value);
	}
}

// Удаляем модификаторы скиллов с персонажа по названию источника без обсчёта таблиц
void RemoveCommonModifier(ref chr, string sourceName)
{
	aref staticTable = CT_GetTable(chr, CT_STATIC);
	aref commonTable = CT_GetTable(chr, CT_COMMON);
	aref equipTable = CT_GetTable(chr, CT_EQUIP);
	for (int i = 0; i < GetAttributesNum(staticTable); i++)
	{
		aref modifier = GetAttributeN(staticTable, i);
		if (!CheckAttribute(modifier, sourceName)) continue;

		string modifierName = GetAttributeName(modifier);
		float value = GetAttributeFloat(modifier, sourceName);
		DeleteSourceFromTable(&staticTable, modifierName, sourceName, value);
		DeleteSourceFromTable(&equipTable, modifierName, sourceName, value);
		DeleteSourceFromTable(&commonTable, modifierName, sourceName, value);
	}
}

void DeleteSourceFromTable(ref table, string modifierName, string sourceName, float value)
{
	AddToAttributeFloat(table, modifierName, -value);        // вычитаем источник
	DeleteAttribute(table, modifierName + "." + sourceName); // чистим следы
}

// Добавить статусный эффект, пока что это только тинктура
void ApplyStatusEffect(ref chr, string perkName)
{
	if (perkName != "Rush") return;

	IncreaseLandModifier(chr, M_REDUCE_DAMAGE, 0.50, perkName);
	IncreaseLandModifier(chr, FAST_STRIKE  + "_" + M_DAMAGE, 3.0, perkName);
	IncreaseLandModifier(chr, FORCE_STRIKE + "_" + M_DAMAGE, 3.0, perkName);
	IncreaseLandModifier(chr, ROUND_STRIKE + "_" + M_DAMAGE, 3.0, perkName);
	IncreaseLandModifier(chr, BREAK_STRIKE + "_" + M_DAMAGE, 3.0, perkName);
}

// Убрать статусный эффект, пока что это только тинктура
void RemoveStatusEffect(ref chr, string perkName)
{
	if (perkName != "Rush") return;

	RemoveLandModifier(chr, perkName);
}