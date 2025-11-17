#include "modifiers\modifiers.h"
#include "modifiers\descriptors.h"
#include "modifiers\descriptors.c"

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
	for (int i = 0; i < GetAttributesNum(functionList); i++)
	{
		aref rFunction = GetAttributeN(functionList, i);
		string sFunction = GetAttributeName(rFunction);
		call sFunction(chr, table, rFunction, context, sFunction);
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

// Складываем бонусы от одного модификатора в другой
void MergeModifiers(ref rTo, ref rFrom, string modifierNameTo, string modifierNameFrom)
{
	if (!CheckAttribute(rFrom, modifierNameFrom)) return;

	aref modifierTo, modifierFrom;
	makearef(modifierTo, rTo.(modifierNameTo));
	makearef(modifierFrom, rFrom.(modifierNameFrom));
	CopyAttributesSafe(modifierTo, modifierFrom);
	AddToAttributeFloat(rTo, modifierNameTo, GetAttributeFloat(rFrom, modifierNameFrom));
}