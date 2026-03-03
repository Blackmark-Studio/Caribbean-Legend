
void ApplyMigration(ref migrationState)
{
	for (int i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if (!CheckAttribute(&RealShips[i], "BaseType")) continue;

		if (sti(RealShips[i].BaseType) == SHIP_AMSTERDAM)
		{
			float value = GetAttributeFloat(RealShips[i], "tuning.modifiers." + M_SHIP_RELOAD_SPEED + ".trait_SP4");
			if (value == 0) return;
			aref modifiers;
			makearef(modifiers, RealShips[i].tuning.modifiers);
			SetModifierFromSourceDirect(modifiers, M_GLOBAL_SPEED, value, "trait_SP4");
			SetModifierFromSourceDirect(modifiers, M_SHIP_SPEED, 0.0, "trait_SP4");
		}
	}
}