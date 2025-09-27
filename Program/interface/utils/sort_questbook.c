// тупа разворачиваем порядок для архива
void SortQuests(ref sortedIdxs, ref original)
{
	int questNum = GetAttributesNum(original);
	SetArraySize(&sortedIdxs, questNum);
	int i, j, x;

	// сохраняем пары январь=1, февраль=2...
	object monthNameToIndex;
	for (i = 1; i < 13; i++)
	{
		string temp = "target_month_" + i;
		string locName = xiStr(temp);
		monthNameToIndex.(locName) = i;
	}

	// заполняем массивчик квестов, докидывая lastUpdate в каждый
	for(x=0; x<questNum; x++)
	{
		aref quest = GetAttributeN(original, x);
		AddLastUpdateToQuest(&quest, &monthNameToIndex);
		sortedIdxs[x] = GetAttributeName(quest);
	}

	// сортируем по lastUpdate
	for (i=0; i < questNum - 1; i++) {
		for (j=0; j < questNum - 1 - i; j++) {

			aref lQuest, rQuest;
			string lQuestName = sortedIdxs[j];
			string rQuestName = sortedIdxs[j+1];

			makearef(lQuest, original.(lQuestName));
			makearef(rQuest, original.(rQuestName));

			if (sti(lQuest.lastUpdate) > sti(rQuest.lastUpdate)) continue;

			string q = sortedIdxs[j];
			sortedIdxs[j] = "" + sortedIdxs[j+1];
			sortedIdxs[j+1] = q;
		}
	}
}

// Добавляем в запись журнала аттрибут lastUpdate с timestampом от самой поздней записи
void AddLastUpdateToQuest(ref quest, ref monthNameToIndex)
{
	quest.lastUpdate = 0;
	aref text;
	makearef(text, quest.text);
	int num = GetAttributesNum(text);
	string tempStr = "l"+(num-1);
	tempStr = text.(tempStr);
	if (!HasSubStr(tempStr, ":")) return; // нет времени в записи, убираем в конец

	quest.lastUpdate = ParseHumandate(FindStringAfterChar(strcut(tempStr, 1, strlen(tempStr)-1), "@"), &monthNameToIndex);
}

// 21 июля 1655 → timestamp
int ParseHumandate(string date, ref monthNameToIndex)
{
	object split;
	SplitString(&split, date, " ", 0);

	string monthName = split.p1;
	if (CheckAttribute(&monthNameToIndex, monthName)) split.p1 = monthNameToIndex.(monthName);
	else return 0;

	if (sti(split.p0) < 10) split.p0 = "0" + split.p0;
	if (sti(split.p1) < 10) split.p1 = "0" + split.p1;

	string dateString = strleft(split.p3, 5) + " " + split.p0 + "." + split.p1 + "." + split.p2;
	return DateStringToInt(dateString);
}