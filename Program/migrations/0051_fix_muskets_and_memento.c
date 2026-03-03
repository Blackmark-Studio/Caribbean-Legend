
void ApplyMigration(ref migrationState)
{
	int i, j;
	ref refShip;
	
	makeref(refShip,ShipsTypes[SHIP_MEMENTO]);
	refShip.rcannon = 8;
	refShip.rcannon = 8;
	refShip.cannonl = 8;
	refShip.cannonr = 8;
	refShip.CannonsQuantity = 20;
	refShip.CannonsQuantityMin = 20;

	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
		if(sti(RealShips[i].BaseType) != SHIP_MEMENTO) continue;
		ref realShip = &RealShips[i];

		realShip.CannonsQuantity = 20;
		realShip.CannonsQuantityMin = 20;
		realShip.CannonsQuantityMax = 20;
		realShip.rcannon = 8;
		realShip.cannonr = 8;
		realShip.lcannon = 8;
		realShip.cannonl = 8;
		realShip.cannons = 20;
	}
	
	for(j = 0; j < MAX_CHARACTERS; j++)
	{
		if (!CheckAttribute(&characters[j],"Ship.Cannons.borts")) continue;
		if (!CheckAttribute(&characters[j],"Ship.Type")) continue;
		if (sti(characters[j].Ship.Type) == SHIP_NOTUSED) continue;
		if (RealShips[sti(characters[j].Ship.Type)].BaseType != SHIP_MEMENTO) continue;
		DeleteAttribute(&characters[j], "Ship.Cannons.borts.cannonr.damages.c8");
		DeleteAttribute(&characters[j], "Ship.Cannons.borts.cannonl.damages.c8");
	}
}
