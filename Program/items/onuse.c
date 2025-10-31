// Добавить вызов коллбэка при использовании предмета
aref AddOnUseCallback(ref item, string funcName)
{
	aref callback;
	makearef(callback, item.callbacks.onUse.(funcName));
	return callback;
}

// Добавить вызов коллбэка для проверки возможности использования предмета
aref AddCanBeUsedCallback(ref item, string funcName)
{
	aref callback;
	makearef(callback, item.callbacks.CanBeUsed.(funcName));
	return callback;
}

// Общее уведомление Использовано 'Имя предмета' для героя
void NotifyPlayerUse(ref chr, ref item)
{
	if (!IsMainCharacter(chr)) return;
	Log_Info(DLG_Convert("CommonUse", "", item));
}

// Запустить все onUse-коллбэки на предмете
void RunOnUseCallbacks(ref chr, ref item)
{
	if (!CheckAttribute(item, "callbacks.onUse")) return;

	aref callbacks;
	makearef(callbacks, item.callbacks.onUse);
	for (int i = 0; i < GetAttributesNum(callbacks); i++)
	{
		aref function = GetAttributeN(callbacks, i);
		string functionName = GetAttributeName(function);
		call functionName(chr, item);
	}
}

// Запустить все проверки возможности использования предмета персонажем в данный момент
// Для запуска функций с разными аргументами предусмотрены 3 варианта: персонаж+предмет, персонаж, предмет
// Если любой коллбэк вернет false -> предмет нельзя использовать
bool RunCanBeUsedCallbacks(ref chr, ref item)
{
	if (!CheckAttribute(item, "callbacks.CanBeUsed")) return true;

	aref callbacks;
	bool result = true;
	makearef(callbacks, item.callbacks.CanBeUsed);
	for (int i = 0; i < GetAttributesNum(callbacks); i++)
	{
		aref function = GetAttributeN(callbacks, i);
		string functionName = GetAttributeName(function);
		if (!CheckAttribute(function, "argumentsConfig")) result = call functionName(chr, item);
		else if (function.argumentsConfig == "chr")       result = call functionName(chr);
		else if (function.argumentsConfig == "item")      result = call functionName(item);

		if (!result) return false;
	}

	return result;
}