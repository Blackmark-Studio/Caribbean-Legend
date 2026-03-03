
void ApplyMigration(ref migrationState)
{
	int i, j;
	ref refShip;
	
	makeref(refShip,ShipsTypes[SHIP_FRIGATE]);
	refShip.CannonsQuantity				= 38;
	refShip.CannonsQuantityMin			= 32;
	
	// Сгенерированные корабли
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
		
        if(sti(RealShips[i].BaseType) == SHIP_FRIGATE)
        {
			if(sti(RealShips[i].CannonsQuantityMin) > 38) continue;
			RealShips[i].CannonsQuantity = sti(RealShips[i].CannonsQuantity) - 4;
			RealShips[i].CannonsQuantityMin	= sti(RealShips[i].CannonsQuantityMin) - 4;
			RealShips[i].CannonsQuantityMax	= sti(RealShips[i].CannonsQuantityMax) - 4;
        }
	}
	
	for(j = 0; j < MAX_CHARACTERS; j++)
	{
		if(!CheckAttribute(&characters[j],"Ship.Cannons.borts")) continue;
		if(!CheckAttribute(&characters[j],"Ship.Type")) continue;
		if(sti(characters[j].Ship.Type) > 899) continue;
		if(RealShips[sti(characters[j].Ship.Type)].BaseType != SHIP_FRIGATE) continue;
		if(sti(RealShips[sti(characters[j].Ship.Type)].CannonsQuantityMin) > 38) continue;
		
		for (i = 0; i < sti(RealShips[sti(characters[j].Ship.Type)].cannonr) + 4; i++)
		{
			string attr2 = "c" + i;
			characters[j].Ship.Cannons.borts.cannonr.damages.(attr2) = 1.0;
			characters[j].Ship.Cannons.borts.cannonl.damages.(attr2) = 1.0; 
		}
		for (i = 0; i < sti(RealShips[sti(characters[j].Ship.Type)].cannonr); i++)
		{
			string attr1 = "c" + i;
			characters[j].Ship.Cannons.borts.cannonr.damages.(attr1) = 0.0;
			characters[j].Ship.Cannons.borts.cannonl.damages.(attr1) = 0.0;
			
		}
	} 
}
