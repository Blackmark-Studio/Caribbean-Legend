bool SF_InitConditions(ref context, ref situation, bool fromStory = false)
{
	string curLocation = GetCurLocationName();
	if (curLocation == xiStr("Open Sea")) return false;

	int crewQty = GetCrewQuantity(pchar);
	if (crewQty >= 30) situation.a.a = 20;

	int freeSpace = GetCargoFreeSpace(pchar);

	// вариант b
	if (freeSpace > GetGoodWeightByType(GOOD_COFFEE, 100)+ GetGoodWeightByType(GOOD_TOBACCO, 100) + GetGoodWeightByType(GOOD_SHIPSILK, 30) && crewQty >= 30) situation.a.b = 20;

	// вариант c
	if (freeSpace > GetGoodWeightByType(GOOD_FOOD, 500)) situation.a.c = 20;

	// вариант d
	if (freeSpace > GetGoodWeightByType(GOOD_SANDAL, 100) && crewQty >= 50) situation.a.d = 20;

	if (GetAttributesNum(situation) == 0) return false; // хотя бы 1 вариант

	context.islandName = worldMap.island;
	return true;
}