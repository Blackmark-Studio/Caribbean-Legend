void ApplyMigration(ref migrationState)
{
	JungleEncountersInit();

	for (int i = 0; i < TOTAL_CHARACTERS; i++)
	{
		ref chr = &Characters[i];

        if ("Merchant.Type" in chr && chr.CityType$string("") == "Citizen"
            && chr.LifeDay == 180)
        {
            chr.LifeDay = 2;
        }

		if ("Ship.Crew.Exp" !in chr) continue;

		float exp = 0.0;
		exp += chr.Ship.crew.exp.sailors$float(0.0);
		exp += chr.Ship.crew.exp.cannoners$float(0.0);
		exp += chr.Ship.crew.exp.soldiers$float(0.0);
		DeleteAttribute(chr, "Ship.crew.exp");
		chr.Ship.crew.exp = exp * 0.3;
	}

	if(LoadSegment("items\modifiers\init\init.c"))
	{
		InitModifiers();
		UnloadSegment("items\modifiers\init\init.c");
	}
}
