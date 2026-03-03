
void ApplyMigration(ref migrationState)
{
	int n = FindLocation("Charles_houseS3");
	locations[n].townsack = "Charles";
	locations[n].islandId = "Nevis";
	locations[n].fastreload = "Charles";

	n = FindLocation("Charles_houseH1");
	locations[n].fastreload = "Charles";

	n = FindLocation("Villemstad_houseH3");
	locations[n].fastreload = "Villemstad";

	n = FindLocation("Villemstad_houseH5");
	locations[n].fastreload = "Villemstad";

	n = FindLocation("Villemstad_Hut3");
	locations[n].fastreload = "Villemstad";

	n = FindLocation("Villemstad_houseH2");
	locations[n].fastreload = "Villemstad";

	n = FindLocation("Mine_residence");
	locations[n].islandId = "Mein";
	DeleteAttribute(&locations[n], "fastreload");
}
