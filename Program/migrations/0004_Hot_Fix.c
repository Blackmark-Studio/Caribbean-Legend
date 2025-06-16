void ApplyMigration(ref migrationState) {
	
	MementoCabinFix();
}

void MementoCabinFix()
{
	int n;
	
	n = FindLocation("Cabin_Memento");
	Locations[n].models.always.locators = "inside_cabin_4_locators";
	
	n = FindLocation("My_Cabin_Memento");
	Locations[n].models.always.locators = "inside_cabin_4_locators";
	
}