
void ApplyMigration(ref migrationState)
{
	aref aData;
	makearef(aData, NullCharacter.Siege);
	if (CheckAttribute(&aData, "nation") && CheckAttribute(&aData, "win"))
	{
		if (CheckAttribute(pchar, "quest.siegeresult")) return;
		if (CheckAttribute(pchar, "quest.EndOfTheSiege")) return;
		if (!CheckAttributeEqualTo(&aData, "issiege", "1")) return;

		trace("Закончили осаду принудительно");
		EndOfTheSiege("End");
	}
}
