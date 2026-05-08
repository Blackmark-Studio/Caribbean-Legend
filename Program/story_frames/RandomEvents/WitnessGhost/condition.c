bool SF_InitConditions(ref context, ref situation, bool fromStory = false)
{
	int crewQty = GetCrewQuantity(pchar);
	if (CheckAttribute(&RandEventSystem, "witnessGhostNotGiven") && crewQty >= 30) situation.a.a = 15;
	if (CheckAttribute(&RandEventSystem, "greenIdolNotGiven")) situation.a.b = 100;
	if (CheckAttribute(&RandEventSystem, "hat12NotGiven")) situation.a.c = 100;
	if (CheckAttribute(&RandEventSystem, "blade_34NotGiven")) situation.a.d = 100;

	if (GetAttributesNum(situation) == 0) return false; // хотя бы 1 вариант

	return true;
}