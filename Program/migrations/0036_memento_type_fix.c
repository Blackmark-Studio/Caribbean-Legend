
void ApplyMigration(ref migrationState)
{
	ref refShip;
	int i;
	makeref(refShip,ShipsTypes[SHIP_MEMENTO]);
	refShip.Type.Merchant = false;

	// Сгенерированные корабли
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if (!CheckAttribute(&RealShips[i], "BaseType")) continue;

		if (sti(RealShips[i].BaseType) == SHIP_MEMENTO) // "Мементо"
		{
			RealShips[i].Type.Merchant = false;
		}
	}

	ReapplyPerksItems0036();
}

// Обновляем перки/дескрипторы
void ReapplyPerksItems0036()
{
	InitPerks();

	if(LoadSegment("items\modifiers\init\init.c"))
	{
		InitModifiers();
		UnloadSegment("items\modifiers\init\init.c");
	}

	object fellows = GetAllFellows(pchar, true);
	for (int i=0; i < GetAttributesNum(&fellows); i++)
	{
		int idx = sti(GetAttributeValue(GetAttributeN(&fellows, i)));
		ref chr = GetCharacter(idx);
		if (!CheckAttribute(chr, "perks.list")) continue;
		ReapplyAllPerks(chr);
	}
	trace("Применили фикс перков/предметов");
}
