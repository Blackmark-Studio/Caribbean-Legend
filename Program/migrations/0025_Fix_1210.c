void ApplyMigration(ref migrationState) {
	FixInjuredBoatswains()
}

void FixInjuredBoatswains()
{
	object fellows = GetAllFellows(pchar, true);
	for (int i=0; i < GetAttributesNum(&fellows); i++)
	{
		int idx = sti(GetAttributeValue(GetAttributeN(&fellows, i)));
		ref chr = GetCharacter(idx);
		if (!CheckAttribute(chr, "OfficerImmortal")) continue;
		chr.OfficerImmortal = true;
	}
}
