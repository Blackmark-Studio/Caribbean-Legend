// Здесь общие хелперы стори-фреймов, подгружаемые в интерфейс в момент открытия стори-фрейма

// Добавить в узел кнопку Решения
aref SF_AddAction(string nodeName, string forceText, string tooltipCallback, string iconData)
{
	nodeName += "_action";
	aref link = _SF_Addlink(nodeName, forceText);
	if (tooltipCallback != "") link.tooltipCallback = tooltipCallback;
	if (HasSubStr(iconData, "|")) {
		link.iconGroup = FindStringBeforeChar(iconData, "|");
		link.iconName = FindStringAfterChar(iconData, "|");
	}
	else link.iconGroup = "";
	return link;
}

// Добавить в узел кнопку Реакции
aref SF_AddReaction(string nodeName, string forceText, string tooltipCallback, string iconData)
{
	nodeName = nodeName + "_" + storyObject.situation.(nodename) + "_reaction";
	aref link = _SF_Addlink(nodeName, forceText);
	link.reaction = true;
	if (tooltipCallback != "") link.tooltipCallback = tooltipCallback;

	if (HasSubStr(iconData, "|")) {
		link.iconGroup = FindStringBeforeChar(iconData, "|");
		link.iconName = FindStringAfterChar(iconData, "|");
	}
	else link.iconGroup = "";
	return link;
}

// Получить текущий шанс успеха внутри действия или реакции, где есть проверка
int SF_GetCurrentChance()
{
	string funcName = storyObject.currentFrame;
	aref link = _SF_FindLink(funcName);
	if (link != nullptr) return iClamp(1, 99, GetAttributeInt(&link, "check")); // всегда есть 1% хаоса

	trace("Error: Missing current chance on the link with funcName: " + funcName);
	return 0;
}

// Сколько процентов бонуса даёт реакция
void SF_SetResult(aref reaction, int points)
{
	reaction.points = points;
}

// Сколько процентов бонуса даёт реакция в случае провала и успеха
void SF_SetResults(aref reaction, int failPoints, int winPoints)
{
	reaction.winPoints = winPoints;
	reaction.failPoints = failPoints;
}

// Получить последнюю нажатую реакцию
aref SF_CurrentReaction()
{
	return _SF_FindLink(storyObject.currentFrame);
}

// Бросок рандома, режим зависит от мода истории в целом
// при зафиксированном режиме выдаст одинаковый результат броска для каждой проверки
int SF_Rand(int value)
{
	int randomMode = GetAttributeIntOrDefault(&StoryObject, "random.mode", RAND_TAG);
	if (randomMode == RAND_NORMAL) return rand(value);
	return DateRandom(value, storyObject.name + storyObject.currentFrame);
}

// Добавить фактор сложности проверке узла
void SF_SetChance(aref link, ref value, string sourceName)
{
	IncreaseModifierFromSourceDirect(&link, "check", value, sourceName);
}

// Увеличить шанс пройти проверку (или уменьшить, если < 0)
void SF_IncreaseChance(aref action, int value)
{
	SF_SetChance(action, value, storyObject.currentFrame + "_factor");
}

// Здесь разбираемся, какие варианты ситуации по факту произошли
void SF_ResolveSituation(ref situation)
{
	storyObject.random.tag = storyObject.currentFrame;
	VRNTR_PickVariants(&storyObject, "situation");
	SF_CompleteSituation(situation);
}

// Здесь пишем срандомившиеся части ситуации в лог
void SF_CompleteSituation(aref situation)
{
	int partNums = GetAttributesNum(situation);
	string tempText = "";
	for (int i = 0; i < partNums; i++)
	{
		aref part = GetAttributeN(situation, i);
		string varName = GetAttributeName(part);
		string value = GetAttributeValue(part);
		if (GetAttributesNum(part) > 0) tempText = tempText + SF_Convert(varName + "_" + value);
		else tempText = tempText + SF_Convert(varName);
		if (i+1 != partNums) tempText = tempText + "<br>";
		tempText = tempText + "~~~~~~~~";
	}

	_SF_Log(tempText, false);
}

// Перейти в другой узел
void SF_SwitchNode(string nodeName)
{
	_SF_Log("<br>", false);
	storyObject.currentNode = nodeName;
	storyObject.currentFrame = nodeName;
	DeleteAttribute(&storyObject, "situation");
	DeleteAttribute(&storyObject, "action");
	DeleteAttribute(&storyObject, "links");
	_SF_NextFrame(nodeName);
}

// Бросаем d100 кубик с общим локом
bool SF_ChanceLock(int percent)
{
	int seed = SF_Rand(99);
	bool result = percent > seed;
	if (result) Log_TestInfo("Выпало " + seed + " < " + percent + " – успех");
	else Log_TestInfo("Выпало " + seed + " > " + percent + " – провал");
	return result;
}

// Обрезаем текст кнопки в сторях
string SF_Truncate(string text)
{
	return Truncate(text, 44, "...");
}

// Добавить строчку в лог истории
void SF_Log(string text)
{
	_SF_Log(text, true);
}

// Локализовать ключ, либо вставить конкретный текст
string SF_ForceOrConvert(string forceText, string key)
{
	if (forceText == "none") return "none";
	else if (forceText == "") return SF_Convert(key);
	else return forceText;
}

// Ищем ключ в общем файле стори-фреймов, затем в файле конкретной стори
string SF_Convert(string key)
{
	string temp = "";
	temp = DLG_ConvertE(key, "StoryFrames\Common.txt", &storyObject);
	if (temp != "") return temp; // нашли в общих ключах сторей

	return DLG_Convert(storyObject.currentFrame + "_" + key, "StoryFrames\" + storyObject.name + ".txt", &storyObject);
}

// Получить действие из текущего узла по буквенному индексу
aref SF_GetAction(string letterIndex)
{
	return _SF_FindLink(storyObject.currentNode + "_" + letterIndex + "_action");
}

// Общее поведение стандартных реакций. Это реакция cо встроенной проверкой и двумя вариантами влияния на действие
void SF_ReactionWithRandomCheck(string actionName, bool autoLog)
{
	aref reaction = SF_CurrentReaction();
	if (reaction == nullptr) return; // что-то пошло не так

	bool success = SF_PerformCheck();
	bonus = sti(reaction.failPoints);
	if (success) bonus = sti(reaction.winPoints);

	if (autoLog) SF_Log(SF_Convert("log_" + !success));
	aref action = SF_GetAction(actionName);
	if (action == nullptr) return; // что-то пошло не так

	SF_IncreaseChance(action, bonus);
}

// Общее поведение стандартных реакций. Это реакция с фиксированным бонусом
void SF_ReactionWithFixedBonus(string actionName, bool autoLog)
{
	aref reaction = SF_CurrentReaction();
	if (reaction == nullptr) return; // что-то пошло не так

	aref action = SF_GetAction(actionName);
	if (action == nullptr) return; // что-то пошло не так

	SF_IncreaseChance(action, GetAttributeInt(&reaction, "points"));
	if (autoLog) SF_Log(SF_Convert("log"));
}

// Общее поведение стандартных реакций. Отдельное для тех, где есть проверка с факторами, и для фиксированных
void SF_DefaultReaction(string actionName)
{
	aref reaction = SF_CurrentReaction();
	if (reaction == nullptr) return; // что-то пошло не так

	int bonus;
	if (CheckAttribute(&reaction, "check")) SF_ReactionWithRandomCheck(actionName, true);
	else SF_ReactionWithFixedBonus(actionName, true);
}

// Триумф
void SF_Triumph()
{
	DeleteAttribute(&storyObject, "situation");
	DeleteAttribute(&storyObject, "action");
	DeleteAttribute(&storyObject, "links");
	DeleteAttribute(&storyObject, "logs");
	storyObject.currentFrame = storyObject.currentNode;
	storyObject.style = "triumph";
	_SF_Log(SF_Convert("success"), false);
	action = SF_AddAction("success", "", "", SF_Icon("story", "triumph"));
	action.func = storyObject.currentNode + "_Triumph";
}

// Крах
void SF_Fail()
{
	DeleteAttribute(&storyObject, "situation");
	DeleteAttribute(&storyObject, "action");
	DeleteAttribute(&storyObject, "links");
	DeleteAttribute(&storyObject, "logs");
	storyObject.currentFrame = storyObject.currentNode;
	storyObject.style = "fail";
	_SF_Log(SF_Convert("fail"), false);
	action = SF_AddAction("fail", "", "", SF_Icon("story", "fail"));
	action.func = storyObject.currentNode + "_Fail";
}

// Подбор иконки для кнопки стори-фреймов
string SF_Icon(string type, string name)
{
	switch (type)
	{
		case "skill": return "EQUIP_ICONS|" + name + " skill icon"; break;
		case "perk": return "PERKS_ENABLE|" + name; break;
		case "item": return GetItemTextureName(name) + "|" + GetItemPictureName(name); break;
		case "pirates": return "EQUIP_ICONS|" + name; break;
		case "honor": return "HIRE_EFFECTS|" + name; break;
		case "story":
			if (name == "triumph") return "EQUIP_ICONS|Rank";
			else return "EQUIP_ICONS|critDamage";
		break;
		case "fractions": return "message_icons|" + name; break;
	}

	trace("Error: Missing Icon " + type + " | " + name + " in SF_Icon");
	return "";
}

// Пройти проверку в текущей реакции или решении
bool SF_PerformCheck()
{
	return SF_ChanceLock(SF_GetCurrentChance());
}