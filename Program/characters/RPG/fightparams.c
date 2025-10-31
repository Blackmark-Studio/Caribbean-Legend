
// Защита от урона
float GetDamageReduction(ref table)
{
	return GetAttributeFloat(table, M_REDUCE_DAMAGE);
}

// Защита от урона огнестрелом
float GetRangeDamageReduction(ref table)
{
	return GetAttributeFloat(table, RANGE + M_REDUCE_DAMAGE);
}

// Защита от критического урона
float GetCritDefence(ref table)
{
	return GetAttributeFloat(table, M_REDUCE_CRIT_DAMAGE);
}

// Крит шанс
float GetCritChance(ref table, string type)
{
	return GetAttributeFloat(table, type + "_" + M_CRIT_CHANCE)
}

// Крит урон
float GetCritDamageMtp(ref table, string type)
{
	return GetAttributeFloat(table, type + "_" + M_CRIT_DAMAGE)
}

// Скорость перезарядки пистолета/мушкета
float GetReloadSpeed(ref table, string type)
{
	return GetAttributeFloat(table, type + "_" + M_RELOAD_SPEED);
}

// Множитель урона
float GetDamageMtp(ref table, string strike, string weaponType)
{
	string modifier = strike + "_" + M_DAMAGE;
	float res = GetAttributeFloat(table, modifier);
	if (strike == SHOT_STRIKE) return res;

	modifier = weaponType + "_" + modifier;
	res += GetAttributeFloat(table, modifier);
	return res;
}

float GetHeadshotDamageMtp(ref table)
{
	return GetAttributeFloat(table, M_HEADSHOT_DAMAGE);
}

float GetPoisonChance(ref chr, ref table)
{
	if (chr.sex == "skeleton" || chr.sex == "crab" || CheckAttribute(chr, "viper")) return 15.0;
	return GetAttributeFloat(chr, "ct." + CT_LAND + "." + M_POISON_CHANCE);
}

float GetStabMtp(ref chr)
{
	float result = 0;
	if (HasPerk(chr, "CunningStrike")) result += PERK_VALUE2_CUNNING_STRIKE;
	if (!IsMainCharacter(chr) && HasPerk(chr, "Quiet ")) result += PERK_VALUE_QUIET;
	return result;
}