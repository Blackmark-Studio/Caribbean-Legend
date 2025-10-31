void ApplyMigration(ref migrationState) {
    EncWeightBase[ENCOUNTER_TYPE_PIRATE] = 10;
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_SMALL] = 25;
    if (!CheckAttribute(&TEV, "FireBrigade_fra"))
    {
    	TEV.FireBrigade_fra.name = GetRandSubString(sFrManNames[rand(GetArraySize(&sFrManNames) - 2)]);
        TEV.FireBrigade_fra.lastname = GetRandSubString(sFrFamilies[rand(GetArraySize(&sFrFamilies) - 2)]);
	}
    if (!SandBoxMode && !CheckAttribute(&TEV, "FireBrigade_spa"))
	{
		TEV.FireBrigade_spa.name = GetRandSubString(sSpManNames[rand(GetArraySize(&sSpManNames) - 2)]);
		TEV.FireBrigade_spa.lastname = GetRandSubString(sSpFamilies[rand(GetArraySize(&sSpFamilies) - 2)]);
	}
	ReapplyUpgradeHolyMercyBlade0024();
}

void ReapplyUpgradeHolyMercyBlade0024()
{
	ref Blade = ItemsFromID("lacrima_patris");
	if (!CheckAttribute(Blade, "KillerBonus")) return;
	if (sti(Blade.KillerBonus.Attack) < 1) return;
	
	int currentDifference = sti(Blade.Attack) - sti(Blade.KillerBonus.DefAttack);
	int addValue = currentDifference - GetAttributeInt(Blade, "KillerBonus.appliedBonus");
	if (addValue == 0) return;

	AddToAttributeInt(Blade, "KillerBonus.appliedBonus", addValue);
	AddToAttributeInt(Blade, "attack.min", addValue);
	AddToAttributeInt(Blade, "attack.max", addValue);
	AddToAttributeInt(Blade, "attack.force.min", addValue);
	AddToAttributeInt(Blade, "attack.force.max", addValue);
	AddToAttributeInt(Blade, "attack.fast.min", addValue);
	AddToAttributeInt(Blade, "attack.fast.max", addValue); 
	AddToAttributeInt(Blade, "attack.round.min", addValue);
	AddToAttributeInt(Blade, "attack.round.max", addValue);
	AddToAttributeInt(Blade, "attack.break.min", addValue);
	AddToAttributeInt(Blade, "attack.break.max", addValue);
	AddToAttributeInt(Blade, "attack.shot.min", addValue);
	AddToAttributeInt(Blade, "attack.shot.max", addValue);
}
