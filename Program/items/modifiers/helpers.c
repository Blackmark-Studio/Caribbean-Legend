bool HasLightWeapon(ref chr)
{
	return HasWeaponType(chr, WEAPON_LIGHT);
}

bool HasMediumWeapon(ref chr)
{
	return HasWeaponType(chr, WEAPON_MEDIUM);
}

bool HasHeavyWeapon(ref chr)
{
	return HasWeaponType(chr, WEAPON_HEAVY);
}

bool HasWeaponType(ref chr, int weaponType)
{
	aref descriptors;
	descriptors = GetEquipDescriptors(chr);
	return CheckAttribute(descriptors, HAS + M_WEAPON_TYPE + "_" + weaponType);
}
