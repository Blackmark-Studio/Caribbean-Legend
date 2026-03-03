
void ApplyMigration(ref migrationState)
{
	ref blade;
	for (int i = 0; i < TOTAL_ITEMS; i++)
	{
		makeref(blade, Items[i]);
		if (!CheckAttribute(blade, "attack")) continue;

		float oldValue = blade.attack;
		ReinitBladeDamage(blade);
	}
}
