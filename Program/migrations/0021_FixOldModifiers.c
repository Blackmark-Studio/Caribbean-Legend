void ApplyMigration(ref migrationState) {

	object fellows = GetAllFellows(pchar, true);
	for (int i=0; i < GetAttributesNum(&fellows); i++)
	{
		int idx = sti(GetAttributeValue(GetAttributeN(&fellows, i)));
		ref chr = GetCharacter(idx);
		DeleteAttribute(chr, "callbacks.equip");
	}
}
