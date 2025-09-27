// Здесь таблица со статичными модификаторами самого персонажа, типа перков или квестовых бонусов
// Она не обновляется с нуля, значения просто дописываются/удаляются по необходимости

// Добавляем модификатор персонажу
void SetChrModifier(ref chr, string modifier, ref value, string source)
{
	aref table = CT_GetTable(chr, CT_STATIC);
	SetAttribute(table, modifier, value);
	SetAttribute(table, modifier + "." + source, value);
}

// Увеличиваем модификатор персонажа
void IncreaseChrModifier(ref chr, string modifier, ref value, string source)
{
	aref table = CT_GetTable(chr, CT_STATIC);
	AddToAttributeFloat(table, modifier, value);
	AddToAttributeFloat(table, modifier + "." + source, value);
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