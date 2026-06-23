
void ApplyMigration(ref migrationState)
{
	int n = FindLocation("Boarding_fortyard");
	Locations[n].id.label = "Fort inside";

	n = FindLocation("Boarding_bastion1");
	Locations[n].id.label = "Fort inside";

	n = FindLocation("Boarding_bastion2");
	Locations[n].id.label = "Fort inside";

}
