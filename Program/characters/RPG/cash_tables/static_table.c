// Здесь таблица со статичными модификаторами самого персонажа, типа перков или квестовых бонусов
// Она не обновляется с нуля, значения просто дописываются/удаляются по необходимости

// Добавляем модификатор персонажу
void SetChrModifier(ref chr, string modifier, ref value, string sourceName)
{
	aref table = CT_GetTable(chr, CT_STATIC);
	SetModifierFromSourceDirect(table, modifier, value, sourceName);
}

// Увеличиваем модификатор персонажа
void IncreaseChrModifier(ref chr, string modifier, ref value, string sourceName)
{
	aref table = CT_GetTable(chr, CT_STATIC);
	IncreaseModifierFromSourceDirect(table, modifier, value, sourceName);
}

// Увеличиваем модификатор персонажа и таблицы суши, таким образом не нужно пересчитывать все таблички
void IncreaseLandModifier(ref chr, string modifier, ref value, string sourceName)
{
	IncreaseChrModifier(chr, modifier, value, sourceName);
	aref table = CT_GetTable(chr, CT_LAND);
	IncreaseModifierDirect(table, modifier, value);
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

// Удаляем модификаторы с персонажа по названию источника
// JOKERTODO мб вернуть, если будем хранить источники в таблице суши
// void RemoveLandModifier(ref chr, string sourceName)
// {
// 	aref table = CT_GetTable(chr, CT_LAND);
// 	for (int i = 0; i < GetAttributesNum(table); i++)
// 	{
// 		aref modifier = GetAttributeN(table, i);
// 		if (!CheckAttribute(modifier, sourceName)) continue;

// 		string modifierName = GetAttributeName(modifier);
// 		float value = stf(modifier.(sourceName));
// 		table.(modifierName) = stf(GetAttributeValue(modifier)) - value; // вычитаем эффект
// 		DeleteAttribute(modifier, sourceName);                           // убираем источник
// 	}
// }



// Добавить статусный эффект пока что это только тинктура
void ApplyStatusEffect(ref chr, string perkName)
{
	if (perkName != "Rush") return;

	IncreaseLandModifier(chr, M_REDUCE_DAMAGE, 0.50, perkName);
	IncreaseLandModifier(chr, FAST_STRIKE  + "_" + M_DAMAGE, 3.0, perkName);
	IncreaseLandModifier(chr, FORCE_STRIKE + "_" + M_DAMAGE, 3.0, perkName);
	IncreaseLandModifier(chr, ROUND_STRIKE + "_" + M_DAMAGE, 3.0, perkName);
	IncreaseLandModifier(chr, BREAK_STRIKE + "_" + M_DAMAGE, 3.0, perkName);
}

// Убрать статусный эффект пока что это только тинктура
void RemoveStatusEffect(ref chr, string perkName)
{
	if (perkName != "Rush") return;

	RemoveChrModifier(chr, perkName);
	CT_UpdateCashTables(chr);
}