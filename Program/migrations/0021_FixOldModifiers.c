void ApplyMigration(ref migrationState) {

	object fellows;
	AddAllFellows(&fellows, pchar, true);
	for (int i=0; i < GetAttributesNum(&fellows); i++)
	{
		int idx = int(GetAttributeValue(GetAttributeN(&fellows, i)));
		ref chr = GetCharacter(idx);
		DeleteAttribute(chr, "callbacks.equip");
	}
}
