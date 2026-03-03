
void ApplyMigration(ref migrationState)
{
	InitPerks();
	if(LoadSegment("items\modifiers\init\init.c"))
	{
		InitModifiers();
		UnloadSegment("items\modifiers\init\init.c");
	}
}
