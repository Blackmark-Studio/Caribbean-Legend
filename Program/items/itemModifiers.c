


#define MODIFIER_MELEE_CRIT_CHANCE "add_CritChanceMelee"
#define MODIFIER_CRIT_INCOMING_CHANCE "add_CritIncomingChance"
#define MODIFIER_INCOMING_DAMAGE "add_IncomingDamage"
//#define MODIFIER_MELEE_DAMAGE_UNDEAD "mul_DamageToUndeadMelee"
#define MODIFIER_MELEE_EXTRA_DAMAGE_TO_UNDEAD "bool_ExtraDamageToUndeadMelee"
#define MODIFIER_MELEE_DAMAGE_MISHELLE "mul_DamageToMishelleMelee"
#define MODIFIER_MELEE_DAMAGE_MODIFIER "mul_DamageMeleeModifier"
#define MODIFIER_MELEE_SP3_DAMAGE_BONUS "bool_SP3DamageBonusMelee"
#define MODIFIER_MELEE_CRIT_DAMAGE "add_CritDamageMelee"
#define MODIFIER_POISON_ATTACK "add_PoisonAttack"
#define MODIFIER_POISON_PROTECT "bool_PoisonProtect"

#define MODIFIER_KILL_ENERGY_UP "add_KillEnergyUp"
#define MODIFIER_ALLOW_ENEMY_FLAGSHIP "mul_AllowEnemyFlagship"


#define MODIFIER_RANGE_EXTRA_DAMAGE_TO_UNDEAD "bool_ExtraDamageToUndeadRange"
#define MODIFIER_RANGE_INSTA_SHOT "add_RangeInstaShot"
#define MODIFIER_RANGE_HIT_PROBABILITY "mul_RangeHitProbability"
#define MODIFIER_RANGE_HIT_ENEMY_PROBABILITY "mul_RangeHitEnemyProbability"
#define MODIFIER_RANGE_DAMAGE_MODIFIER "mul_RangeDamageModifier"
#define MODIFIER_RANGE_ENEMY_DAMAGE_MODIFIER "mul_RangeDamageEnemyModifier"


#define MODIFIER_RANGE_CRIT_CHANCE "add_CritChanceRange"
#define MODIFIER_RANGE_RELOAD_SPEED_BONUS "mul_RangeReloadSpeedBonus"


#define MODIFIER_PROTECT_RANGE_EXPLOSION "bool_ProtectRangeExplosion"
#define MODIFIER_PROTECT_RANGE_EXPLOSION_DOUBLE_BULLET "bool_ProtectRangeExplosionDoubleBullet"
#define MODIFIER_PROTECT_RANGE_EXPLOSION_MODIFIER "mul_ProtectRangeExplosionModifier"

#define MODIFIER_RANGE_EXPLODE_ON_SHOT "bool_RangeExplodeOnShot"

#define MODIFIER_HEAVY_ARMOR "bool_HeavyArmor"
#define MODIFIER_LIGHT_ARMOR "bool_LightArmor"

#define MODIFIER_SKILL_ACCURACY_SCALE "mul_SkillAccuracyScale"
#define MODIFIER_DISABLE_OVERLOAD_CHECK "bool_DisableOverloadCheck"
#define MODIFIER_OWN_STUN_CHANCE "mul_OwnStunChance"

void AddSkillModifierToItem(ref rItem, string sSkillName, int iValue)
{
	rItem.skills.(sSkillName) = iValue;
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

