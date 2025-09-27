#include "items\modifiers\modifiers.h"
#include "items\modifiers\descriptors.h"
#include "items\modifiers\descriptors.c"
#include "items\modifiers\callbacks.c"

void AddModifier(ref rObject, string modifier, ref value)
{
	rObject.modifiers.(modifier) = value;
}

void AddArefModifier(ref rObject, string path, string modifier, ref value)
{
	rObject.(path).modifiers.(modifier) = value;
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
			SetWeaponStrikeDamage(attack, FEINT_STRIKE, mtp * WEAPON_LIGHT_FEINT_STRIKE_MTP, dmgMin, dmgMax);
		}
		break;
		case WEAPON_MEDIUM:
		{
			SetWeaponStrikeDamage(attack, FAST_STRIKE , mtp * WEAPON_MEDIUM_FAST_STRIKE_MTP , dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FORCE_STRIKE, mtp * WEAPON_MEDIUM_FORCE_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, ROUND_STRIKE, mtp * WEAPON_MEDIUM_ROUND_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, BREAK_STRIKE, mtp * WEAPON_MEDIUM_BREAK_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FEINT_STRIKE, mtp * WEAPON_MEDIUM_FEINT_STRIKE_MTP, dmgMin, dmgMax);
		}
		break;
		case WEAPON_HEAVY:
		{
			SetWeaponStrikeDamage(attack, FAST_STRIKE , mtp * WEAPON_HEAVY_FAST_STRIKE_MTP , dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FORCE_STRIKE, mtp * WEAPON_HEAVY_FORCE_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, ROUND_STRIKE, mtp * WEAPON_HEAVY_ROUND_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, BREAK_STRIKE, mtp * WEAPON_HEAVY_BREAK_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FEINT_STRIKE, mtp * WEAPON_HEAVY_FEINT_STRIKE_MTP, dmgMin, dmgMax);
		}
		break;
		case MUSKET_ITEM_TYPE:
		{
			SetWeaponStrikeDamage(attack, FAST_STRIKE , mtp * MUSKET_FAST_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FORCE_STRIKE, mtp * MUSKET_FORCE_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, ROUND_STRIKE, mtp * MUSKET_ROUND_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, BREAK_STRIKE, mtp * MUSKET_BREAK_STRIKE_MTP, dmgMin, dmgMax);
			SetWeaponStrikeDamage(attack, FEINT_STRIKE, mtp * MUSKET_FEINT_STRIKE_MTP, dmgMin, dmgMax);
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

aref AddCallback(ref rObject, string callerFunctionName, string callbackFunctionName)
{
	aref result;
	makearef(result, rObject.modifiers.callbacks.(callerFunctionName).(callbackFunctionName));
	return result;
}

aref AddArefCallback(ref rObject, string path, string callerFunctionName, string callbackFunctionName)
{
	aref result;
	makearef(result, rObject.(path).modifiers.callbacks.(callerFunctionName).(callbackFunctionName));
	return result;
}

string HumanModifierValue(ref args, ref rObject)
{
	string modifier = AttributesToString(args, "");
	return rObject.modifiers.(modifier);
}
