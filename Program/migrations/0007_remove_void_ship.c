
void ApplyMigration(ref migrationState)
{
    int shipCount = GetArraySize(&ShipsTypes);
	shipCount -= 1;
	SetArraySize(&ShipsTypes, shipCount);
}
