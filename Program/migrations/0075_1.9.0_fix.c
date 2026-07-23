
void ApplyMigration(ref migrationState)
{
	for (int i = 36; i <= 39; i++)
	{
		string jewelry = "jewelry" + i;
        int q = GetCharacterItem(PChar, jewelry);
        if (q > 0) RemoveItems(PChar, jewelry, q);
	}
}
