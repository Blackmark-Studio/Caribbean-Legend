void ApplyMigration(ref migrationState) {

	ChangeSmugglersNames();
	CabinsLocators();
}

void ChangeSmugglersNames()
{
	for(int n = 0; n < TOTAL_CHARACTERS; n++)
	{
		if(HasSubStr(Characters[n].id, "_smuggler"))
		{
			if(Characters[n].id == "JusticeOnSale_Smuggler") continue;
			if(Characters[n].id == "PZ_Formosa_smuggler") continue;
			Characters[n].name = GetCharacterName("Smuggler_" + rand(6));
		}
	}
}

void CabinsLocators()
{
	int n;
	
	n = FindLocation("My_Cabin_Medium2");
	
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
	
	n = FindLocation("Cabin_Medium2");
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
	
	n = FindLocation("Cabin");
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
	
	n = FindLocation("My_Cabin");
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
}