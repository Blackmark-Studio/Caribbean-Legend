void ApplyMigration(ref migrationState) {
	FixInjuredBoatswains();
}

void FixInjuredBoatswains()
{
	object fellows;
	AddAllFellows(&fellows, pchar, true);
	for (int i=0; i < GetAttributesNum(&fellows); i++)
	{
		int idx = int(GetAttributeValue(GetAttributeN(&fellows, i)));
		ref chr = GetCharacter(idx);
		if (!CheckAttribute(chr, "OfficerImmortal")) continue;
		chr.OfficerImmortal = true;
	}
}
