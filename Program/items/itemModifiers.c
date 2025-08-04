


#define MODIFIER_MELEE_CRIT_CHANCE "add_CritChanceMelee"
#define MODIFIER_MELEE_DAMAGE_UNDEAD "mul_DamageToUndeadMelee"
#define MODIFIER_MELEE_EXTRA_DAMAGE_TO_UNDEAD "bool_ExtraDamageToUndeadMelee"
#define MODIFIER_MELEE_DAMAGE_MISHELLE "mul_DamageToMishelleMelee"
#define MODIFIER_MELEE_DAMAGE_MODIFIER "mul_DamageMeleeModifier"
#define MODIFIER_MELEE_SP3_DAMAGE_BONUS "bool_SP3DamageBonusMelee"
#define MODIFIER_MELEE_CRIT_DAMAGE "add_CritDamageMelee"
#define MODIFIER_MELEE_POISON "add_MeleePoison"

#define MODIFIER_KILL_ENERGY_UP "add_KillEnergyUp"
#define MODIFIER_ALLOW_ENEMY_FLAGSHIP "mul_AllowEnemyFlagship"



#define MODIFIER_RANGE_INSTA_SHOT "add_RangeInstaShot"
#define MODIFIER_RANGE_HIT_PROBABILITY "mul_RangeHitProbability"
#define MODIFIER_RANGE_DAMAGE_MODIFIER "mul_RangeDamageModifier"
#define MODIFIER_RANGE_CRIT_CHANCE "add_CritChanceRange"
#define MODIFIER_RANGE_RELOAD_SPEED_BONUS "mul_RangeReloadSpeedBonus"


#define MODIFIER_PROTECT_RANGE_EXLOSION_PC "bool_ProtectRangeExlosionPC"
#define MODIFIER_PROTECT_RANGE_EXLOSION_NPC "bool_ProtectRangeExlosionNPC"
#define MODIFIER_PROTECT_RANGE_EXLOSION_MODIFIER "mul_ProtectRangeExlosionModifier"

#define MODIFIER_RANGE_EXLOSION_MODIFIER "mul_RangeExlosionModifier"

#define MODIFIER_HEAVY_ARMOR "bool_HeavyArmor"
#define MODIFIER_LIGHT_ARMOR "bool_LightArmor"

void AddSkillModifierToItem(ref rItem, string sSkillName, int iValue)
{
	rItem.skills.(sSkillName) = iValue;
}

int GetSkillModifierToItem(ref rItem, string sSkillName)
{
	if (!CheckAttribute(rItem, "skills."+sSkillName))
	{
		return 0;
	}
	return sti(rItem.skills.(sSkillName));
}

void AddBoolModifierToItem(ref rItem, string sModifierName, bool bValue)
{
	rItem.modifiers.(sModifierName) = bValue;
}

void AddFloatModifierToItem(ref rItem, string sModifierName, float fValue)
{
	rItem.modifiers.(sModifierName) = fValue;
}


int GetCharacterSkillModifier(ref rChar, string sSkillName)
{
	if (!CheckAttribute(rChar, "modifiers.skills."+sSkillName))
	{
		return 0;
	}
	return sti(rChar.modifiers.skills.(sSkillName));
}

bool GetCharacterBoolModifier(ref rChar, string sSkillName)
{
	if (!CheckAttribute(rChar, "modifiers.modifiers."+sSkillName))
	{
		return false;
	}
	return sti(rChar.modifiers.modifiers.(sSkillName));
}

float GetCharacterFloatModifier(ref rChar, string sSkillName)
{
	if (!CheckAttribute(rChar, "modifiers.modifiers."+sSkillName))
	{
		string modifierType = FindStringBeforeChar(sSkillName, "_");
		if (modifierType == "mul")
		{
			return 1.0;
		}
		return 0.0;
	}
	return stf(rChar.modifiers.modifiers.(sSkillName));
}

