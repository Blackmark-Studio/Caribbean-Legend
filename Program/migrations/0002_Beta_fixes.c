
void ApplyMigration(ref migrationState)
{
    ref sld;
    int iChar, i;

    // Фикс фортов
    for (i=0; i<MAX_COLONIES; i++)
	{
		if(Colonies[i].nation == "none") continue;
		if(CheckAttribute(&Colonies[i], "HasNoFort")) continue;
        if(!CheckAttribute(&Colonies[i], "Commander")) continue;

		iChar = GetCharacterIndex(Colonies[i].Commander);
        if(iChar == -1) continue;
        sld = &Characters[iChar];
        sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS48;
	}

    // Китаец
    if(CharacterIsAlive("Longway_FP"))
    {
        sld = CharacterFromId("Longway_FP");
        sld.CanTakeMushket = true;
    }
}
