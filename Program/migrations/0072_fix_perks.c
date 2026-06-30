void ApplyMigration(ref migrationState)
{
	if(LoadSegment("items\modifiers\init\init.c"))
	{
		InitModifiers();
		UnloadSegment("items\modifiers\init\init.c");
	}

	InitPerks();

	for (int i = 0; i < TOTAL_CHARACTERS; i++)
	{
		ref chr = &Characters[i];
		if (!HasPerk(chr, "tireless")) continue;
		SetCharacterPerk(chr, "tireless");
	}
}
