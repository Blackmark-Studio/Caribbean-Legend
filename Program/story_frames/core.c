// Здесь внутренние функции стори-фреймов, подгружаемые в интерфейс в момент открытия стори-фрейма

aref reaction;
aref action;
int bonus;

// Добавить в узел кнопку
aref _SF_Addlink(string nodeName, string forceText)
{
	aref links, link;
	makearef(links, storyObject.links);
	int linkIndex = GetAttributesNum(links) + 1;
	string slinkIndex = "link" + linkIndex;
	DeleteAttribute(&links, slinkIndex);
	makearef(link, links.(slinkIndex));

	string fullText = SF_ForceOrConvert(forceText, nodeName);
	string truncatedText = SF_Truncate(fullText);
	link.text = truncatedText;
	link.func = storyObject.currentFrame + "_" + nodeName;
	if (truncatedText != fullText) link.fullText = fullText;

	return link;
}

// Найти в узле реакцию или действие по буквенному индексу
aref _SF_FindLink(string funcName)
{
	aref links, link;
	makearef(links, storyObject.links);
	int linksNum = GetAttributesNum(links);

	for (int i = 0; i < linksNum; i++)
	{
		link = GetAttributeN(links, i);
		if (link.func == funcName) return link;
	}

	trace("Error: Missing link with funcname: " + funcName + " in _SF_FindLink");
	return nullptr;
}

// Внутренняя функция для разруливания абзацев по необходимости
void _SF_Log(string text, bool addNewLine)
{
	if (addNewLine) _SF_Log("<br>", false);

	aref logs;
	makearef(logs, storyObject.logs);
	string logAttributeName = storyObject.currentFrame;

	// Нужно, если несколько раз в одной реакции/действии пишем в лог
	if (CheckAttribute(&logs, logAttributeName))
	{
		logAttributeName = storyObject.currentFrame + "/" + GetAttributesNum(&logs);
	}

	logs.(logAttributeName).value = "~~~~~~~~" + text; // с отступом слева
}