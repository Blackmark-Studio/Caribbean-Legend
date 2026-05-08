
void ApplyMigration(ref migrationState)
{
	if (LoadSegment("ships\sails_init.c"))
	{
		InitSailsParams();
		InitSpeedPoints();
		InitAdvancedSpeedPoints();
		UnloadSegment("ships\sails_init.c");
	}

	InitGunWithAmmoParams("mushket_indian", "t1", "cartridge", "",       127.0, 167.0, 0.0,  0, 0,  29, 0);
	InitGunWithAmmoParams("mushket_indian", "t3", "bullet_double", "",   220.0, 290.0, 0.0,  0, 0,  19, 0);

	if(LoadSegment("items\modifiers\init\init.c"))
	{
		InitModifiers();
		UnloadSegment("items\modifiers\init\init.c");
	}

	ref refShip;
	makeref(refShip,ShipsTypes[SHIP_EASTINDIAMAN]);
	refShip.Cannon = CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber = 24;

	makeref(refShip,ShipsTypes[SHIP_NAVIO]);
	refShip.Cannon = CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber = 20;
}
