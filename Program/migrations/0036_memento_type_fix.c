
void ApplyMigration(ref migrationState)
{
	ref refShip;
	int i;
	makeref(refShip,ShipsTypes[SHIP_MEMENTO]);
	refShip.Type.Merchant = false;
	refship.icons.FirstIconPos = 10+5*16;
	refship.icons.SecondIconPos = 10+5*16 + 1;

	// Сгенерированные корабли
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if (!CheckAttribute(&RealShips[i], "BaseType")) continue;

		if (sti(RealShips[i].BaseType) == SHIP_MEMENTO) // "Мементо"
		{
			RealShips[i].Type.Merchant = false;
		}
	}
}
