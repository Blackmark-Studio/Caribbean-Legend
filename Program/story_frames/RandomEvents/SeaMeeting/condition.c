bool SF_InitConditions(ref context, ref situation, bool fromStory = false)
{
	if (int(pchar.nation) == PIRATE) return false;

	int nation = FindNonEnemyNation2Nation(int(pchar.nation));
	if (nation < 0) return false; // чебурашка, у которого нет друзей

	int foodQty = GetCargoGoods(pchar, GOOD_FOOD);
	int freeSpace = GetCargoFreeSpace(pchar);
	string curLocation = GetCurLocationName();

	// вариант a
	if (foodQty >= 300) situation.a.a = 20;

	// вариант b
	if (foodQty >= 300 && GetCargoGoods(pchar, GOOD_MEDICAMENT) >= 300 && GetCrewQuantity(pchar) >= 40) situation.a.b = 20;

	// вариант c
	if (foodQty >= 300 && freeSpace >= 150) situation.a.c = 20;

	// вариант d
	if (GetCargoGoods(pchar, GOOD_SAILCLOTH) >= 100 && freeSpace >= GetGoodWeightByType(GOOD_EBONY, 100)) situation.a.d = 20;

	// вариант e
	if (curLocation != xiStr("Open Sea") && curLocation != GetIslandNameByID("Mein"))
	{
		context.islandName = worldMap.island;
		situation.a.e = 20;
	}

	// вариант f
	if (freeSpace >= GetGoodWeightByType(GOOD_TOBACCO, 500)) situation.a.f = 15;

	// вариант g
	situation.a.g = 20;

	if (GetAttributesNum(situation) < 1) return false;
	if (!fromStory) return true;

	context.nation = nation;
	return true;
}

