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
	return CheckAttribute(descriptors, M_WEAPON_TYPE + "_" + weaponType);
}

void SetWeaponDamageByStrikes(ref item, int type, float dmgMin, float dmgMax)
{
	float weightMtp = GetWeightMtp(type, stf(item.weight));
	aref attack;
	makearef(attack, item.attack);
	float baseAttack = stf(item.attack);
	item.attack.min = makeInt(baseAttack * dmgMin + 0.5);
	item.attack.max = makeInt(baseAttack * dmgMax + 0.5);
	float mtp = baseAttack * weightMtp;
	switch (type)
	{
		case WEAPON_LIGHT:
		{
			SetWeaponStrikeDamage(attack, FAST_STRIKE , mtp * WEAPON_LIGHT_FAST_STRIKE_MTP , dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FORCE_STRIKE, mtp * WEAPON_LIGHT_FORCE_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, ROUND_STRIKE, mtp * WEAPON_LIGHT_ROUND_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, BREAK_STRIKE, mtp * WEAPON_LIGHT_BREAK_STRIKE_MTP, dmgMin, dmgMax);
		}
		break;
		case WEAPON_MEDIUM:
		{
			SetWeaponStrikeDamage(attack, FAST_STRIKE , mtp * WEAPON_MEDIUM_FAST_STRIKE_MTP , dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FORCE_STRIKE, mtp * WEAPON_MEDIUM_FORCE_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, ROUND_STRIKE, mtp * WEAPON_MEDIUM_ROUND_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, BREAK_STRIKE, mtp * WEAPON_MEDIUM_BREAK_STRIKE_MTP, dmgMin, dmgMax);
		}
		break;
		case WEAPON_HEAVY:
		{
			SetWeaponStrikeDamage(attack, FAST_STRIKE , mtp * WEAPON_HEAVY_FAST_STRIKE_MTP , dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FORCE_STRIKE, mtp * WEAPON_HEAVY_FORCE_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, ROUND_STRIKE, mtp * WEAPON_HEAVY_ROUND_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, BREAK_STRIKE, mtp * WEAPON_HEAVY_BREAK_STRIKE_MTP, dmgMin, dmgMax);
		}
		break;
		case MUSKET_ITEM_TYPE:
		{
			SetWeaponStrikeDamage(attack, FAST_STRIKE , mtp * MUSKET_FAST_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FORCE_STRIKE, mtp * MUSKET_FORCE_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, ROUND_STRIKE, mtp * MUSKET_ROUND_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, BREAK_STRIKE, mtp * MUSKET_BREAK_STRIKE_MTP, dmgMin, dmgMax);
		}
		break;
	}
}

void SetWeaponStrikeDamage(ref attack, string strike, float mtp, float dmgMin, float dmgMax)
{
	SetAttribute(attack, strike + ".min", makeInt(mtp * dmgMin + 0.5));
	SetAttribute(attack, strike + ".max", makeInt(mtp * dmgMax + 0.5));
}

void SetWeaponDescriptors(ref item, int type, int length, int curvature, float dmgMin, float dmgMax)
{
	AddDescriptor(item, M_WEAPON_TYPE, type);
	AddDescriptor(item, M_WEAPON_LENGTH, length);
	AddDescriptor(item, M_WEAPON_CURVATURE, curvature);

	switch (type)
	{
		case WEAPON_LIGHT:  item.FencingType = SKILL_F_LIGHT; break;
		case WEAPON_MEDIUM: item.FencingType = SKILL_FENCING; break;
		case WEAPON_HEAVY:  item.FencingType = SKILL_F_HEAVY; break;
	}

	SetWeaponDamageByStrikes(item, type, dmgMin, dmgMax);
}

void SetArmorDescriptors(ref item, int type, int material)
{
	AddDescriptor(item, M_ARMOR_TYPE, type);
	AddDescriptor(item, M_ARMOR_MATERIAL, material);
}