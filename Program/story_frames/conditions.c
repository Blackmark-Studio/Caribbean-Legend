// Модуль проверки возможности использования реакций/решения
#define SF_CONDITION_PERK "perk"
#define SF_CONDITION_SKILL "skill"
#define SF_CONDITION_PIRATES "pirates"
#define SF_CONDITION_HERO_TYPE "heroType"
#define SF_CONDITION_ITEM "item"
#define SF_CONDITION_MONEY "money"
#define SF_CONDITION_REPUTATION "reputation"
#define SF_CONDITION_LICENSE "license"
#define SF_CONDITION_RELATIONS "relations"
#define SF_CONDITION_CAPELLAN "capellan"

#define SF_CONDITION_CUSTOM "custom"

/*
	Добавить реакции/решениюу условие доступности
	@param check сама проверка условия
	@param conditionType тип условия для вывода в тултипе
	@param conditionValue значение условия для вывода в тултипе
	
	Не укладывающиеся в схему проверки добавляем через `SF_CONDITION_CUSTOM` с собственным текстом для тултипа.
	Например, проверки типа `SF_CONDITION_PERK` подразумевают, что перк должен быть прокачен.
	Если нужна проверка, при которой перк НЕ должен быть прокачен и это одноразовый случай → кастом.
*/
void SF_AddCondition(ref link, bool check, string conditionType, string conditionValue = "")
{
	if (check || DEBUG_SF_ALL_CONDITIONS_ARE_TRUE) return;

	// $+value дорисовываем для уникальности ключей, на случай нескольких требуемых перков и т. п.
	string attributeName = conditionValue == "" ? conditionType : conditionType + "$" + conditionValue;
	switch (conditionType)
	{
		case SF_CONDITION_PERK:
			SetAttribute(link, "disabled." + attributeName, GetPerkName(conditionValue));
		break;
		case SF_CONDITION_SKILL:
			SetAttribute(link, "disabled." + attributeName, xiStr(conditionValue));
		break;
		case SF_CONDITION_HERO_TYPE:
			SetAttribute(link, "disabled." + attributeName, xiStr("HeroType_" +strright(conditionValue, 1)));
		break;
		case SF_CONDITION_ITEM:
			SetAttribute(link, "disabled." + attributeName, GetItemName(conditionValue));
		break;
		case SF_CONDITION_PIRATES:
			SetAttribute(link, "disabled." + attributeName, xiStr(conditionValue));
		break;
		case SF_CONDITION_RELATIONS:
			SetAttribute(link, "disabled." + attributeName, conditionValue);
		break;
		case SF_CONDITION_REPUTATION:
			SetAttribute(link, "disabled." + attributeName, "");
		break;
		case SF_CONDITION_LICENSE:
			SetAttribute(link, "disabled." + attributeName, "");
		break;
		case SF_CONDITION_CAPELLAN:
			SetAttribute(link, "disabled." + attributeName, "");
		break;
		case SF_CONDITION_MONEY:
			SetAttribute(link, "disabled." + attributeName, "");
		break;
		case SF_CONDITION_CUSTOM:
			SetAttribute(link, "disabled." + attributeName, conditionValue);
		break;
	}
}