
void ApplyMigration(ref migrationState)
{
	int n = Items_FindItemIdx("amulet_7");
	SetModifier(&Items[n], M_HP_RECOVERY_MLT, 2.0);

	n = Items_FindItemIdx("blade_WR");
	SetModifier(&Items[n], M_HP_RECOVERY_MLT, 5.0);



	aref perks;
	makearef(perks, ChrPerksList.list);

	SetArefModifier(perks, "Energaiser", M_ENERGY_RECOVERY_MLT, 1.5);
	SetArefModifier(perks, "Tireless", M_ENERGY_RECOVERY_MLT, 1 + PERK_VALUE_TIRELESS);
	SetArefModifier(perks, "HT3", M_ENERGY_RECOVERY_MLT, 1.15);
	SetArefModifier(perks, "Medic", M_HP_RECOVERY_MLT, 2.0);
}
