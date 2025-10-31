void ApplyMigration(ref migrationState) {
	string herotype = pchar.heroparam.herotype;
	switch (herotype)
	{
		case "HeroType_1": 
		{
			SetCharacterPerk(pchar, "HT1");
			SetCharacterPerk(pchar, "TannedLeather");
		}
		break;
		case "HeroType_2":
		{
			SetCharacterPerk(pchar, "HT2");
			SetCharacterPerk(pchar, "RatsWolf");
			SetCharacterPerk(pchar, "Mimicry");
			SetCharacterPerk(pchar, "TreasureHunter");
		}
		break;
		case "HeroType_3":
		{
			SetCharacterPerk(pchar, "HT3");
			SetCharacterPerk(pchar, "Mule");
		}
		break;
		case "HeroType_4":
		{
			SetCharacterPerk(pchar, "HT4");
			SetCharacterPerk(pchar, "Bombardier");
			SetCharacterPerk(pchar, "Sniper");
		}
		break;
	}

}