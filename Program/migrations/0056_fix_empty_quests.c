
void ApplyMigration(ref migrationState)
{
	aref questInfo = GetAref(pchar, "QuestInfo");
	int questQty = GetAttributesNum(questInfo);
	for (int i = questQty-1; i > 0; i--)
	{
		aref quest = GetAttributeN(questInfo, i);
		string questName = GetAttributeName(quest);
		aref text = GetAref(quest, "text");
		if (text != nullptr && GetAttributesNum(text) > 0) continue;

		DeleteAttribute(&questInfo, questName);
	}
}
