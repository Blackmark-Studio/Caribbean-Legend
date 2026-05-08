#include "modifiers\modifiers.h"
#include "modifiers\descriptors.h"
#include "modifiers\descriptors.c"

string GetModifierName(string modifier)
{
	return GetConvertStrB(modifier, "Modifiers.txt");
}

// Добавить модификатор предмету/навыку с перезаписью значения
void SetModifier(ref rObject, string modifier, ref value)
{
	rObject.modifiers.(modifier) = value;
}

// Добавить модификатор напрямую с перезаписью значения
void SetModifierDirect(ref rObject, string modifier, ref value)
{
	rObject.(modifier) = value;
}

// Добавить модификатор предмету/навыку с перезаписью значения и указанием источника
void SetModifierFromSource(ref rObject, string modifier, ref value, string sourceName)
{
	aref modifiers;
	makearef(modifiers, rObject.modifiers);
	SetModifierFromSourceDirect(&modifiers, modifier, value, sourceName);
}

// Добавить модификатор на атрибут чего-либо с перезаписью значения, нужно только для инитки перков
void SetArefModifier(ref rObject, string attribute, string modifier, ref value)
{
	rObject.(attribute).modifiers.(modifier) = value;
}

// Добавить модификатор чему-либо напрямую, с перезаписью значения и указанием источника
void SetModifierFromSourceDirect(ref rObject, string modifier, ref value, string sourceName)
{
	// если уже есть мод, выпиливаем
	if (CheckAttribute(rObject, modifier + "." + sourceName)) 
	{
		float currentValue = GetAttributeFloat(rObject, modifier + "." + sourceName);
		AddToAttributeFloat(rObject, modifier, value-currentValue);
		SetAttribute(rObject, modifier + "." + sourceName, value);
	}
	else IncreaseModifierFromSourceDirect(rObject, modifier, value, sourceName);
}

// Добавить модификатор чему-либо напрямую со складыванием значения и указанием источника
void IncreaseModifierFromSourceDirect(ref rObject, string modifier, ref value, string sourceName)
{
	AddToAttributeFloat(rObject, modifier, value);
	AddToAttributeFloat(rObject, modifier + "." + sourceName, value);
}

// Добавить модификатор чему-либо напрямую со складыванием значения
void IncreaseModifierDirect(ref rObject, string modifier, ref value)
{
	AddToAttributeFloat(rObject, modifier, value);
}

// Добавить коллбэк на предмет/навык и получить его
aref AddCallback(ref rObject, string callerFunctionName, string callbackFunctionName)
{
	aref result;
	makearef(result, rObject.modifiers.callbacks.(callerFunctionName).(callbackFunctionName));
	return result;
}

// Добавить коллбэк на атрибут чего-либо и получить его, нужно только для нитки перков
aref AddArefCallback(ref rObject, string attribute, string callerFunctionName, string callbackFunctionName)
{
	aref result;
	makearef(result, rObject.(attribute).modifiers.callbacks.(callerFunctionName).(callbackFunctionName));
	return result;
}

string HumanModifierValue(ref args, ref rObject)
{
	string modifier = AttributesToString(args, "");
	if (CheckAttribute(rObject, "modifiers." +modifier)) return rObject.modifiers.(modifier);
	
	trace("Missing modifier " + modifier + " for object" + rObject.id);
	return "Missing modifier";
}

// Запустить коллбэки на кэш-таблице по названию таблицы
void RunTableCallbacks(ref chr, string callbackName, ref table, ref context)
{
	if (!CheckAttribute(table, "callbacks." + callbackName)) return;

	aref functionList;
	makearef(functionList, table.callbacks.(callbackName));

	int functionsQty = GetAttributesNum(functionList);
	for (int i = 0; i < functionsQty; i++)
	{
		aref rFunction = GetAttributeN(functionList, i);
		string sFunction = GetAttributeName(rFunction);
		call sFunction(chr, table, rFunction, context, sFunction);
	}
}

// Запустить на объекте коллбэки из его атрибута
void RunCallbacks(ref rObject, string attributeName)
{
	aref callbacksObject;
	makearef(callbacksObject, rObject.(attributeName));

	int modifiersQty = GetAttributesNum(callbacksObject);
	for (int i = 0; i < modifiersQty; i++)
	{
		aref functionObject = GetAttributeN(callbacksObject, i);
		string sFunction = GetAttributeName(functionObject);
		call sFunction(rObject, &functionObject);
	}
}

// Удалить личный коллбэк с персонажа, например, от перков
void RemoveChrCallback(ref chr, string callbackPath)
{
	DeleteAttribute(chr, "ct.static.callbacks." + callbackPath);
}

// Складываем значения модификаторов
void MergeModifier(ref rObject, ref modifier, string modifierName, string sourceName)
{
	string modifierValue = GetAttributeValue(modifier);
	rObject.(modifierName) = GetAttributeFloat(rObject, modifierName) + stf(modifierValue);
	rObject.(modifierName).(sourceName) = modifierValue;
}

// Коллбэки дописываем
void MergeCallbacks(ref rObject, ref modifier)
{
	aref callbacks;
	makearef(callbacks, rObject.callbacks);
	CopyAttributesSafe(callbacks, modifier);
}

// Флаги копируем
void MergeFlags(ref rObject, ref modifier)
{
	aref flags;
	makearef(flags, rObject.has);
	CopyAttributesSafe(flags, modifier);
}

// Тупа копируем единичный модификатор
void CopyModifier(ref rTo, ref rFrom, string modifier)
{
	if (!CheckAttribute(rFrom, modifier)) return;
	rTo.(modifier) = rFrom.(modifier);
}

// Получить значение модификатора на чём-либо как int
int GetModifierInt(ref rObject, string modifierName, int iDefault = 0)
{
	return GetAttributeIntOrDefault(rObject, "modifiers." + modifierName, iDefault);
}

// Получить значение модификатора на чём-либо как float
float GetModifierFloat(ref rObject, string modifierName, float iDefault = 0.0)
{
	return GetAttributeFloatOrDefault(rObject, "modifiers." + modifierName, iDefault);
}

/*
	Получить множитель модификатора на чём-либо, то есть база 1.0 + float-значение модификатора
	@param base базовый множитель, обычно единица, т. е. 100%
	@param min минимальный множитель, для цен используем 0.01 (1%), чтобы не получалось бесплатно
	@param max максимальный множитель, если нужен

	@return ножитель вида n.n
*/
float GetModifierMtp(ref rObject, string modifierName, float base = 1.0, float min = 0.0, float max = 10.0)
{
	return fClamp(min, max, base + GetModifierFloat(rObject, modifierName));
}

/*
	Получить значение модификатора состояния на чём-либо
	@param modifierName имя модификатора
	@param defaultState состояние по умолчанию

	@return состояние как число
*/
int GetModifierState(ref rObject, string modifierName, int defaultState = 0)
{
	return GetAttributeIntOrDefault(rObject, "modifiers." + HAS + modifierName, defaultState);
}

void RemoveModifiersFromSource(ref rObject, string sourceName)
{
	int modifiersQty = GetAttributesNum(rObject);

	for (int i = modifiersQty-1; i >= 0; i--)
	{
		aref modifier = GetAttributeN(rObject, i);
		if (!CheckAttribute(modifier, sourceName)) continue;

		string modifierName = GetAttributeName(modifier);
		float value = stf(modifier.(sourceName));
		rObject.(modifierName) = stf(GetAttributeValue(modifier)) - value; // вычитаем эффект
		DeleteAttribute(&modifier, sourceName);                            // убираем источник
	}
}

// Складываем бонусы от одного модификатора в другой
// в частности, используется для отображения бонусов к урону картечью/пулями в общем бонусе к урону огнестрела
void ApplyModifierAsAnother(ref rTo, ref rFrom, string modifierNameTo, string modifierNameFrom)
{
	if (!CheckAttribute(rFrom, modifierNameFrom)) return;

	aref modifierTo, modifierFrom;
	makearef(modifierTo, rTo.(modifierNameTo));
	makearef(modifierFrom, rFrom.(modifierNameFrom));
	CopyAttributesSafe(modifierTo, modifierFrom);
	AddToAttributeFloat(rTo, modifierNameTo, GetAttributeFloat(rFrom, modifierNameFrom));
}

// Удаляем временные модификаторы, распиханные по персонажам
void GlobalRemoveTempModifiers()
{
	aref modifiers = GetAref(&TEV, "tempModifiers", true);
	int now = TMSTD_Timestamp(0);
	int modifiersQty = GetAttributesNum(modifiers);

	for (int i = modifiersQty-1; i >= 0; i--)
	{
		aref modifier = GetAttributeN(modifiers, i);
		if (now < int(GetAttributeValue(modifier))) continue;

		ref chr = CharacterFromIDSafe(modifier.chrId, true);
		string sourceName = GetAttributeName(modifier);

		// персонажа нет, значит и модификатор не нужен
		if (chr == nullptr)
		{
			DeleteAttribute(&modifiers, sourceName);
			continue;
		}

		aref table = CT_GetTable(chr, modifier.table);
		RemoveModifiersFromSource(table, sourceName);
		CT_UpdateCashTables(chr);
		DeleteAttribute(&modifiers, sourceName);
	}
}

// Установить персонажу модификатор на n дней
void SetTempChrModifier(ref chr, string modifierName, ref value, string sourceName, int days)
{
	SetChrModifier(chr, modifierName, value, sourceName);
	TEV.tempModifiers.(sourceName) = TMSTD_Timestamp(days);
	TEV.tempModifiers.(sourceName).chrId = chr.id
	TEV.tempModifiers.(sourceName).table = CT_STATIC;
}