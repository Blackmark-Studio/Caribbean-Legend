void ApplyMigration(ref migrationState) {
	
	fixCabinLights();
}

void fixCabinLights()
{
	int n;
	
	n = FindLocation("Cabin_Medium");
	SetDefaultLightingModels(n);
	
	n = FindLocation("My_Cabin_Medium");
	SetDefaultLightingModels(n);
	
	n = FindLocation("My_Cabin_Medium2");
	SetDefaultLightingModels(n);
	
	n = FindLocation("Cabin_Medium2");
	SetDefaultLightingModels(n);
	
	n = FindLocation("Cabin_Small");
	SetDefaultLightingModels(n);
	
	n = FindLocation("My_Cabin_Small");
	SetDefaultLightingModels(n);
	
	n = FindLocation("Cabin");
	SetDefaultLightingModels(n);
	
	n = FindLocation("My_Cabin");
	SetDefaultLightingModels(n);
}