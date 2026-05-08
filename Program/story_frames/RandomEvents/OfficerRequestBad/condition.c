bool SF_InitConditions(ref context, ref situation, bool fromStory = false)
{
	// общее условие, есть хотя бы 1 неквестовый офицер на должности
	ref officer = fromStory ? _RE_GetRandomFellow("SF_Rand") : _RE_GetRandomFellow();
	if (officer == nullptr) return false;

	// вариант a
	situation.a.a = 20;

	// вариант b
	if (GetCrewQuantity(pchar) >= 15 && GetCharacterShipClass(pchar) < 7) situation.a.b = 20;

	// вариант c
	if (GetCrewQuantity(pchar) >= 15) situation.a.c = 20;

	// вариант d
	if (!IsFellowHasJob(officer, JOB_TREASURER)) situation.a.d = 20;

	// вариант e
	if (IsFellowHasJob(officer, JOB_TREASURER) || IsFellowHasJob(officer, JOB_BOATSWAIN)) situation.a.e = 35;

	if (GetAttributesNum(situation) == 0) return false; // хотя бы 1 вариант

	context.officerId = officer.id;
	context.officerName = officer.name;
	context.officerJob = GetJobsList(officer, "-_");
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

