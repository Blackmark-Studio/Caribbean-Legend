// Модуль результатов истории, здесь все обычные плюшки типа опыта/денег, просто с форматированием под и сторию

#define SF_E_SKILL_EXP "SkillExp"
#define SF_E_MORALE "CrewMorale"
#define SF_E_GOODS "Goods"
#define SF_E_MONEY "Money"
#define SF_E_NATION_RELATION "NationRelation"
#define SF_E_FRACTION_RELATION "FractionRelation"
#define SF_E_REPUTATION "Reputation"
#define SF_E_LOYALITY "Loyality"
#define SF_E_LOYALITY_ALL "LoyalityAll"
#define SF_E_CREW_QTY "CrewQty"
#define SF_E_CREW_EXP "CrewExp"
#define SF_E_ITEMS "Items"
#define SF_E_ITEMS_CABIN "ItemsCabin"
#define SF_E_TEMP_MODIFIER "TempModifier"
#define SF_E_CUSTOM "Custom"

// Добавляем эффект через натитвные функции + записываем всё в контекст истории
void SF_AddEffect(string effectType, ...)
{
	int valueArgumentIndex = -1;
	int secondValueArgumentIndex = -1;
	string secondValueName;
	string attributeName = "";
	object ctx;

	switch (effectType)
	{
		case SF_E_SKILL_EXP:
			AddCharacterExpToSkill(GetArg(1), GetArg(2), GetArg(3));
			valueArgumentIndex = 3;
		break;
		case SF_E_MORALE:
			AddCrewMorale(GetArg(1), GetArg(2));
			valueArgumentIndex = 2;
		break;
		case SF_E_GOODS:
			if (GetArg(3) > 0) AddCharacterGoods(GetArg(1), GetArg(2), GetArg(3));
			else RemoveCharacterGoods(GetArg(1), GetArg(2), GetArg(3));
			valueArgumentIndex = 3;
		break;
		case SF_E_MONEY:
			AddMoneyToCharacter(GetArg(1), GetArg(2));
			valueArgumentIndex = 2;
		break;
		case SF_E_REPUTATION:
			ChangeCharacterComplexReputation(GetArg(1), GetArg(2), GetArg(3));
			valueArgumentIndex = 3;
		break;
		case SF_E_NATION_RELATION:
			ChangeCharacterNationReputation(GetArg(1), GetArg(2), GetArg(3));
			valueArgumentIndex = 3;
		break;
		case SF_E_FRACTION_RELATION:
			if (GetArg(1) == "Indian") ChangeIndianRelation(float(GetArg(2)));
			else if (GetArg(1) == "Smugglers") ChangeContrabandRelation(pchar, int(GetArg(2)));
			valueArgumentIndex = 2;
		break;
		case SF_E_LOYALITY:
			ChangeOfficerLoyality(GetArg(1), GetArg(2));
			valueArgumentIndex = 2;
		break;
		case SF_E_LOYALITY_ALL:
			RE_AddLoyalityToAllOfficers(GetArg(1));
			valueArgumentIndex = 1;
		break;
		case SF_E_CREW_EXP:
			ChangeCrewExp(GetArg(1), GetArg(2), GetArg(3));
			valueArgumentIndex = 3;
		break;
		case SF_E_ITEMS:
			TakeNItems(GetArg(1), GetArg(2), GetArg(3));
			valueArgumentIndex = 3;
		break;
		case SF_E_ITEMS_CABIN:
			if (GetArg(2) < 0) RemoveItemsFromPCharTotal(GetArg(1), -GetArg(2));
			else PutItemToShip(Get_My_Cabin(), GetArg(1), GetArg(2));
			valueArgumentIndex = 2;
		break;
		case SF_E_TEMP_MODIFIER:
			SetTempChrModifier(GetArg(1), GetArg(2), GetArg(3), GetArg(4), GetArg(5));
			valueArgumentIndex = 3;
			secondValueArgumentIndex = 5;
			secondValueName = "duration";
		break;
		case SF_E_CREW_QTY:
			if (GetArg(2) > 0) AddCharacterCrew(GetArg(1), GetArg(2));
			else RemoveCharacterCrew(GetArg(1), -GetArg(2));
			valueArgumentIndex = 2;
		break;
		case SF_E_CUSTOM:
			aref effects = GetAref(&StoryObject, "effects", true);
			string valueType = Vartype(GetArg(1));
			attributeName = GetArg(0) + "" + GetAttributesNum(effects);
			if (valueType == VAR_STRING) SetAttribute(&effects, attributeName, GetArg(1));
			else if (valueType == VAR_FLOAT) AddToAttributeFloat(&effects, attributeName, GetArg(1));

			SetAttribute(effects, attributeName + ".type", GetArg(2)); // хороший или плохой?
			return;
		break;
	}

	int argsQty = GetArgCount();
	if (valueArgumentIndex < 0) return;

	float value = float(GetArg(valueArgumentIndex));

	for (int i = 1; i < argsQty; i++)
	{
		if (i == valueArgumentIndex || i == secondValueArgumentIndex) continue;

		ref arg = GetArg(i);
		attributeName += "$" + _SF_EffectArgToString(arg);
	}

	AddToAttributeFloat(&StoryObject, "effects." + effectType + attributeName, value);
	if (secondValueArgumentIndex >= 0)
	{
		AddToAttributeFloat(&StoryObject, "effects." + effectType + attributeName + "." + secondValueName, float(GetArg(secondValueArgumentIndex)));
	}
}

// Строкое представление для аргументов в эффектах историй
string _SF_EffectArgToString(ref argument)
{
	switch (VarType(argument))
	{
		case VAR_FLOAT: return FloatToString(argument, 4); break;
		case VAR_INTEGER: return its(argument); break;
		case VAR_STRING: return argument; break;
		case VAR_REFERENCE: return IsMainCharacter(argument) ? "pchar" : argument.name; break;
		case VAR_AREFERENCE: return IsMainCharacter(argument) ? "pchar" : argument.name; break;
		case VAR_OBJECT: return IsMainCharacter(argument) ? "pchar" : argument.name; break;
	}

	assert(false, "_SF_EffectArgToString error, wrong argument: " + VarType(argument));
	return "Error";
}

// Всем офицерам лояльность, такой эффект есть только в историях
void RE_AddLoyalityToAllOfficers(int value)
{
	object fellows;
	AddAllFellows(&fellows, pchar, false);
	int fellowsQty = GetAttributesNum(&fellows);
	for (int i=0; i < fellowsQty; i++)
	{
		ref fellow = FindChar_VT(sti(GetAttributeValue(GetAttributeN(&fellows, i))), true);
		if (fellow == nullptr) continue;
		ChangeOfficerLoyality(fellow, value);
	}
}
