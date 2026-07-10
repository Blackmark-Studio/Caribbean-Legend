void ApplyMigration(ref migrationState)
{
	if ("Quest.Deposits" !in Pchar)
	{
		return;
	}

	for (aref arDepType: &Pchar.Quest.Deposits)
	{
		if ("Result" in arDepType)
		{
			arDepType.Result = int(float(arDepType.Result));
		}
	}
}
