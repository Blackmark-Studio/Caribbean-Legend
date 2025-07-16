void ApplyMigration(ref migrationState) {
	
	Memento_BookDelete();
	Memento_modelPath();
}

void Memento_BookDelete()
{
	if (CheckCharacterItem(PChar, "Memento_Book")) TakeItemFromCharacter(pchar, "Memento_Book");
}

void Memento_modelPath()
{
	int n = FindLocation("Cabin_Memento");
	Locations[n].filespath.models = "locations\decks\inside_cabin_4"; // каюта 
	
	n = FindLocation("My_Cabin_Memento");
	Locations[n].filespath.models = "locations\decks\inside_cabin_4"; // каюта 
}