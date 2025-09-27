void ApplyMigration(ref migrationState) {
	InitPerks();
	if (HasPerk(pchar, "HT3"))
	{
		SetCharacterPerk(pchar, "Mule");
	}

	ref item = ItemsFromID("talisman11");
	AddModifier(item, SKILL_TYPE + SKILL_FORTUNE, 2);
	AddModifier(item, SKILL_TYPE + SKILL_F_LIGHT, 2);
	AddModifier(item, SKILL_TYPE + SKILL_FENCING, 2);
	AddModifier(item, SKILL_TYPE + SKILL_F_HEAVY, 2);
	AddModifier(item, SKILL_TYPE + SKILL_PISTOL, 2);
	AddModifier(item, SKILL_TYPE + SKILL_FORTUNE, 2);
	AddModifier(item, SKILL_TYPE + SKILL_LEADERSHIP, 2);
	AddModifier(item, SKILL_TYPE + SKILL_COMMERCE, 2);
	AddModifier(item, SKILL_TYPE + SKILL_ACCURACY, 2);
	AddModifier(item, SKILL_TYPE + SKILL_CANNONS, 2);
	AddModifier(item, SKILL_TYPE + SKILL_SAILING, 2);
	AddModifier(item, SKILL_TYPE + SKILL_REPAIR, 2);
	AddModifier(item, SKILL_TYPE + SKILL_GRAPPLING, 2);
	AddModifier(item, SKILL_TYPE + SKILL_DEFENCE, 2);
	AddModifier(item, SKILL_TYPE + SKILL_SNEAK, 2);
}