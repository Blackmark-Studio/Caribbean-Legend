


#define MODIFIER_MELEE_CRIT_CHANCE "add_CritChanceMelee"
#define MODIFIER_CRIT_INCOMING_CHANCE "add_CritIncomingChance"
#define MODIFIER_INCOMING_DAMAGE "add_IncomingDamage"
//#define MODIFIER_MELEE_DAMAGE_UNDEAD "mul_DamageToUndeadMelee"
#define MODIFIER_MELEE_EXTRA_DAMAGE_TO_UNDEAD "bool_ExtraDamageToUndeadMelee"
#define MODIFIER_MELEE_DAMAGE_MISHELLE "mul_DamageToMishelleMelee"
#define MODIFIER_MELEE_DAMAGE "mul_DamageMeleeModifier"

#define MODIFIER_MELEE_BREAK_ATTACK_BONUS "mul_BreakAttackBonusMelee"
#define MODIFIER_MELEE_BREAK_ATTACK_BONUS_ENEMY "mul_BreakAttackEnemyBonusMelee"

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
#define MODIFIER_RANGE_ENEMY_DAMAGE "mul_RangeDamageEnemyModifier"
#define MODIFIER_RANGE_EXTRA_DAMAGE_GRAPE "mul_ExtraDamageGrape"

#define MODIFIER_RANGE_CRIT_CHANCE "add_CritChanceRange"
#define MODIFIER_RANGE_RELOAD_SPEED_BONUS "mul_RangeReloadSpeedBonus"


#define MODIFIER_PROTECT_RANGE_EXPLOSION "bool_ProtectRangeExplosion"
#define MODIFIER_PROTECT_RANGE_EXPLOSION_DOUBLE_BULLET "bool_ProtectRangeExplosionDoubleBullet"
#define MODIFIER_PROTECT_RANGE_EXPLOSION_MODIFIER "mul_ProtectRangeExplosionModifier"

#define MODIFIER_RANGE_EXPLODE_ON_SHOT "bool_RangeExplodeOnShot"

#define MODIFIER_HEAVY_ARMOR "bool_HeavyArmor"
#define MODIFIER_LIGHT_ARMOR "bool_LightArmor"

#define MODIFIER_SKILL_ACCURACY_SCALE "mul_SkillAccuracyScale"

#define MODIFIER_SKILL_SNEAK_SCALE "mul_SkillSneakScale"
#define MODIFIER_SKILL_FORTUNE_SCALE "mul_SkillFortuneScale"

#define MODIFIER_DISABLE_OVERLOAD_CHECK "bool_DisableOverloadCheck"
#define MODIFIER_OWN_STUN_CHANCE "mul_OwnStunChance"
#define MODIFIER_ENERGY_DRAIN "add_EnergyDrain"
#define MODIFIER_SHOT_AVOID_CHANCE "add_ShotAvoidChance"


void SetSkillModifierToItem(ref rItem, string sSkillName, int iValue)
{
	rItem.skills.(sSkillName) = iValue;
}

void SetPassiveSkillModifierToItem(ref rItem, string sSkillName, int iValue)
{
	rItem.passive_skills.(sSkillName) = iValue;
}

void SetSkillCallbackModifierToItem(ref rItem, string sSkillName, string callback)
{
	DeleteAttribute(rItem, "skills."+sSkillName);
	rItem.skills.(sSkillName).callback = callback;
}

void SetPassiveSkillCallbackModifierToItem(ref rItem, string sSkillName, string callback)
{
	DeleteAttribute(rItem, "passive_skills."+sSkillName);
	rItem.passive_skills.(sSkillName).callback = callback;
}

void SetBoolModifierToItem(ref rItem, string sModifierName, bool bValue)
{
	rItem.modifiers.(sModifierName) = bValue;
}

void SetPassiveBoolModifierToItem(ref rItem, string sModifierName, bool bValue)
{
	rItem.passive_modifiers.(sModifierName) = bValue;
}

void SetFloatModifierToItem(ref rItem, string sModifierName, float fValue)
{
	rItem.modifiers.(sModifierName) = fValue;
}

void SetPassiveFloatModifierToItem(ref rItem, string sModifierName, float fValue)
{
	rItem.passive_modifiers.(sModifierName) = fValue;
}

void SetCallbackModifierToItem(ref rItem, string sModifierName, string callback)
{
	DeleteAttribute(rItem, "modifiers."+sModifierName);
	rItem.modifiers.(sModifierName).callback = callback;
}

void SetPassiveCallbackModifierToItem(ref rItem, string sModifierName, string callback)
{
	DeleteAttribute(rItem, "passive_modifiers."+sModifierName);
	rItem.passive_modifiers.(sModifierName).callback = callback;
}

int GetCharacterSkillModifier(ref rChar, string sSkillName)
{
	return GetCharacterSkillModifierWithObject(rChar, sSkillName, rChar);
}

int GetCharacterSkillModifierWithObject(ref rChar, string sSkillName, ref rObject)
{
	if (!CheckAttribute(rChar, "modifiers.skills."+sSkillName))
	{
		return 0;
	}
	int result = sti(rChar.modifiers.skills.(sSkillName));
	
	aref modifierAttr;
	makearef(modifierAttr, rChar.modifiers.skills.(sSkillName));
	int callbackNum = GetAttributesNum(modifierAttr);
	for (int i = 0; i < callbackNum; i++)
	{
		string callback = GetAttributeValue(GetAttributeN(modifierAttr, i));
		result += call callback(rObject);
	}
	return result;
}

bool GetCharacterBoolModifier(ref rChar, string sSkillName)
{
	return GetCharacterBoolModifierWithObject(rChar, sSkillName, rChar);
}

bool GetCharacterBoolModifierWithObject(ref rChar, string sSkillName, ref rObject)
{
	if (!CheckAttribute(rChar, "modifiers.modifiers."+sSkillName))
	{
		return false;
	}
	bool result = sti(rChar.modifiers.modifiers.(sSkillName));

	aref modifierAttr;
	makearef(modifierAttr, rChar.modifiers.modifiers.(sSkillName));
	int callbackNum = GetAttributesNum(modifierAttr);
	for (int i = 0; i < callbackNum; i++)
	{
		string callback = GetAttributeValue(GetAttributeN(modifierAttr, i));
		bool val = call callback(rObject);
		result = result || val;
	}
	
	return result;
}

float GetCharacterFloatModifier(ref rChar, string sSkillName)
{
	return GetCharacterFloatModifierWithObject(rChar, sSkillName, rChar);
}

float GetCharacterFloatModifierWithObject(ref rChar, string sSkillName, ref rObject)
{
	string modifierType;
	if (!CheckAttribute(rChar, "modifiers.modifiers."+sSkillName))
	{
		modifierType = FindStringBeforeChar(sSkillName, "_");
		if (modifierType == "mul")
		{
			return 1.0;
		}
		return 0.0;
	}
	
	float result = stf(rChar.modifiers.modifiers.(sSkillName));
	aref modifierAttr;
	makearef(modifierAttr, rChar.modifiers.modifiers.(sSkillName));
	int callbackNum = GetAttributesNum(modifierAttr);
	
	if (callbackNum > 0)
	{
		modifierType = FindStringBeforeChar(sSkillName, "_");
		bool needMul = false;
		if (modifierType == "mul")
		{
			needMul = true;
		}

		for (int i = 0; i < callbackNum; i++)
		{
			string callback = GetAttributeValue(GetAttributeN(modifierAttr, i));
			float val = call callback(rObject);
			if (needMul)
			{
				result *= val;
			}
			else
			{
				result += val;
			}
		}
	}
	return result;
}

