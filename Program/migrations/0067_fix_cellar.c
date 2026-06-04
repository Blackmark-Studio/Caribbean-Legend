
void ApplyMigration(ref migrationState)
{
	ref loc = FindLocationById("Villemstad_ClockCellar");
	loc.reload.l1.emerge = "reload1";
}
