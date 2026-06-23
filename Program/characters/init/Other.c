int CreateOtherCharacters(int n)
{
	ref ch;

	////////////////////////////////////////////////////////////////////////////////////////
	/// персонаж для ВАНО
	/// делаем его неписем для корректного отображения флага ГГ на шлюпке
	////////////////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);		// boat character  // boal

	ch.name 	= GetCharacterName("Sailor");	// Моряк
	ch.lastname = GetCharacterName("Sailor");	// Моряк
	ch.id		= "BoatChar";
	ch.nation	= ENGLAND;
	ch.activity_begin = "0";
	ch.activity_end = "24";
	ch.experience = "0";
	ch.Ship.Name = "Boat";
	ch.Ship.Type = GenerateShip(SHIP_BOAT, true);
	ch.Ship.Stopped = true;
	n = n + 1;

	return n;
}