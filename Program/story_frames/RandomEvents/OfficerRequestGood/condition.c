bool SF_InitConditions(ref context, ref situation, bool fromStory = false)
{
	// общее условие, есть хотя бы 1 неквестовый офицер на должности
	ref officer = fromStory ? _RE_GetRandomFellow("SF_Rand") : _RE_GetRandomFellow();
	if (officer == nullptr) return false;

	// вариант a
	if (int(pchar.money) >= 5000) situation.a.a = 20;

	// вариант b
	ref item = FindItemOnShip(true, "OfficerRequestGood_FindBlade");
	if (item != nullptr)
	{
		context.bladeId = item.id;
		context.bladeName = GetItemName(item);
		situation.a.b = 20;
	}

	// вариант c
	ref prisoner = fromStory ? _RE_GetRandomPrisoner("SF_Rand") : _RE_GetRandomPrisoner();
	if (prisoner != nullptr)
	{
		context.prisonerId = prisoner.id;
		context.prisonerName = prisoner.name;
		situation.a.c = 20;
	}

	// вариант d
	if (CheckItemMyCabin("Mineral3") > 0 && CheckItemMyCabin("Mineral5") > 0) situation.a.d = 20;

	if (GetAttributesNum(situation) == 0) return false; // хотя бы 1 вариант

	context.officerId = officer.id;
	context.officerName = officer.name;
	context.officerJob = GetJobsList(officer, "-");
	return true;
}

ref _RE_GetRandomPrisoner(string randMethod = "rand")
{
	int prisonerIds[] = {};
	FillAllPrisonersIndexes(&prisonerIds);
	int prisonersQty = GetArraySize(&prisonerIds);
	if (prisonersQty == 0) return nullptr;

	int randIdx = call randMethod(prisonersQty-1);
	return GetCharacterSafe(prisonerIds[randIdx]);
}

bool OfficerRequestGood_FindBlade(ref item)
{
	if (!CheckAttributeEqualTo(item, "groupId", BLADE_ITEM_TYPE)) return false;
	int quality = int(item.quality);
	if (quality > B_EXCELLENT) return false;
	if (quality < B_GOOD) return false;
	return true;
}

ref _RE_GetRandomFellow(string randMethod = "rand")
{
	object officerIds;
	int officersQty = RE_GetAllFellows(&officerIds);
	if (officersQty < 1) return nullptr; // не нашли офицера

	int randIdx = call randMethod(officersQty-1);
	return CharacterFromIDSafe(GetAttributeValue(GetattributeN(&officerIds, randIdx)));
}