bool SF_InitConditions(ref context, ref situation, bool fromStory = false)
{
	object officers;
	int randomOfficersIds[];
	int officersQty = RE_GetAllFellows(&officers);
	if (officersQty < 2) return false;
	if (!fromStory) return true; // уже точно знаем, что можно запускать

	int a,b;
	string randFunc = "SF_SetTwoRandomNums";
	call randFunc(officersQty-1, &a, &b);
	context.officerIdx_a = GetAttributeName(GetAttributeN(&officers, a));
	context.officerIdx_b = GetAttributeName(GetAttributeN(&officers, b));

	situation.a.a = 20;
	situation.a.b = 20;

	ref prisoner = _RE_GetRandomPrisoner();
	if (prisoner != nullptr)
	{
		context.prisonerId = prisoner.id;
		context.prisonerName = prisoner.name;
		situation.a.c = 20;
	}

	situation.a.d = 20;
	situation.a.e = 20;
	return true;
}


ref _RE_GetRandomPrisoner()
{
	int prisonerIds[] = {};
	FillAllPrisonersIndexes(&prisonerIds);
	int prisonersQty = GetArraySize(&prisonerIds);
	if (prisonersQty == 0) return nullptr;

	return GetCharacterSafe(prisonerIds[SF_Rand(prisonersQty-1)]);
}

