bool SF_InitConditions(ref context, ref situation, bool fromStory = false)
{
	string curLocation = GetCurLocationName();
	if (curLocation == xiStr("Open Sea")) return false;

	int crewQty = GetCrewQuantity(pchar);
	int enemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.nation));

	if (crewQty >= 50) situation.a.a = 20;

	int freeSpace = GetCargoFreeSpace(pchar);

	// вариант b
	if (crewQty >= 50) situation.a.b = 20;

	// вариант c
	if (crewQty >= 60 && enemyNation > -1) situation.a.c = 20;

	if (GetAttributesNum(situation) == 0) return false; // хотя бы 1 вариант

	context.islandName = worldMap.island;
	context.enemyNation = enemyNation;
	return true;
}