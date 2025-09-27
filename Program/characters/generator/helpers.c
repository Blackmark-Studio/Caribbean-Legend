// Сглаживаем значения по рангу ГГ, чтобы рандомные разбросы были адекватны
int GEN_SmoothBonusByRank(int bonus)
{
	if (bonus == 0)
		return 0;

	float mdf = fClamp(0.3, 1.0, stf(pchar.rank) / 11);
	return makeint(makefloat(bonus) * mdf + 0.5);
}

// Суммируем очки умений, чтобы выдать нужное число очков навыков
void GEN_SummPerkPoints(ref chr, ref points)
{
	int self = GEN_SELF_PERKS_PENALTY;
	int ship = GEN_SHIP_PERKS_PENALTY;
	for (int i = 1; i < 15; i++)
	{
		string skillName = GetSkillNameByIdx(i);
		if (i < 7)
			self += sti(chr.skill.(skillName));
		else
			ship += sti(chr.skill.(skillName));
	}
	points.self = makeint(self) / GetFreePoints_SelfRate(chr);
	points.ship = makeint(ship) / GetFreePoints_ShipRate(chr);
}

// 0 основной, 1 вторичный
string GEN_GetArchetype(ref chr, int order)
{
	string attr = "personality.mainArchetype";
	if (order == 1)
		attr = "personality.secondaryArchetype";
	if (!CheckAttribute(chr, attr))
		return "None";
	return chr.(attr);
}

int GEN_GetPowerLevelSkillBonus(int powerLevel)
{
	switch (powerLevel)
	{
	case GEN_COMMONER:
		return GEN_COMMONER_SKILL_BONUS;
		break;
	case GEN_ELITE:
		return GEN_ELITE_SKILL_BONUS;
		break;
	case GEN_MINIBOSS:
		return GEN_MINIBOSS_SKILL_BONUS;
		break;
	case GEN_BOSS:
		return GEN_BOSS_SKILL_BONUS;
		break;
	}
}

void GEN_GetPowerLevelPirates(int powerLevel, int base, int random)
{
	switch (powerLevel)
	{
	case GEN_COMMONER:
	{
		base = GEN_COMMONER_PIRATES_BONUS;
		random = GEN_COMMONER_PIRATES_BONUS_RANDOM;
	}
	break;
	case GEN_ELITE:
	{
		base = GEN_ELITE_PIRATES_BONUS;
		random = GEN_ELITE_PIRATES_BONUS_RANDOM;
	}
	break;
	case GEN_MINIBOSS:
	{
		base = GEN_MINIBOSS_PIRATES_BONUS;
		random = GEN_MINIBOSS_PIRATES_BONUS_RANDOM;
	}
	break;
	case GEN_BOSS:
	{
		base = GEN_BOSS_PIRATES_BONUS;
		random = GEN_BOSS_PIRATES_BONUS_RANDOM;
	}
	break;
	}
}

void GEN_GetArchetypePirates(ref chr, ref _p, ref _i, ref _r, ref _a, ref _t, ref _e, ref _s)
{
	string archetype = chr.personality.mainArchetype;
	int bigBonus = 2 + rand(1);
	int smallBonus = 1 + rand(1);
	switch (archetype)
	{
	case GEN_ARCHETYPE_DUELIST:
	{
		if (PercentChance(50))
		{
			_i += smallBonus;
			_r += bigBonus;
		}
		else
		{
			_i += bigBonus;
			_r += smallBonus;
		}
	}
	break;
	case GEN_ARCHETYPE_PIRATE:
	{
		if (PercentChance(50))
		{
			_p += smallBonus;
			_r += bigBonus;
		}
		else
		{
			_p += bigBonus;
			_r += smallBonus;
		}
	}
	break;
	case GEN_ARCHETYPE_GUNMAN:
	{
		if (PercentChance(50))
		{
			_s += smallBonus;
			_r += bigBonus;
		}
		else
		{
			_s += bigBonus;
			_r += smallBonus;
		}
	}
	break;
	case GEN_ARCHETYPE_SOLDIER:
	{
		if (PercentChance(50))
		{
			_p += smallBonus;
			_e += bigBonus;
		}
		else
		{
			_p += bigBonus;
			_e += smallBonus;
		}
	}
	break;
	case GEN_ARCHETYPE_PEASANT:
	{
		_p += rand(1);
		_e += rand(2);
	}
	break;
	case GEN_ARCHETYPE_TREASURER:
	{
		if (PercentChance(50))
		{
			_t += smallBonus;
			_a += bigBonus;
		}
		else
		{
			_t += bigBonus;
			_a += smallBonus;
		}
	}
	break;
	case GEN_ARCHETYPE_CARPENTER:
	{
		if (PercentChance(50))
		{
			_e += smallBonus;
			_a += bigBonus;
		}
		else
		{
			_e += bigBonus;
			_a += smallBonus;
		}
	}
	break;
	case GEN_ARCHETYPE_BOATSWAIN:
	{
		if (PercentChance(50))
		{
			_t += smallBonus;
			_r += bigBonus;
		}
		else
		{
			_t += bigBonus;
			_r += smallBonus;
		}
	}
	break;
	case GEN_ARCHETYPE_CANNONER:
	{
		if (PercentChance(50))
		{
			_i += bigBonus;
			_s += smallBonus;
		}
		else
		{
			_t += smallBonus;
			_p += bigBonus;
		}
	}
	break;
	case GEN_ARCHETYPE_NAVIGATOR:
	{
		if (PercentChance(50))
		{
			_i += smallBonus;
			_t += bigBonus;
		}
		else
		{
			_i += bigBonus;
			_t += smallBonus;
		}
	}
	break;
	case GEN_ARCHETYPE_DOCTOR:
	{
		if (PercentChance(50))
		{
			_e += smallBonus;
			_a += bigBonus;
		}
		else
		{
			_e += bigBonus;
			_a += smallBonus;
		}
	}
	break;
	}
}

void GEN_SetCharHiredOfficers(ref chr, bool upNavy)
{
	int score = makeint(GetSkillSum(chr) / 11 + 0.5);
	int needSkill = GetShipClassNavySkill(GetCharacterShipClass(chr));
	for (int i=1; i<8; i++)
	{
		string skillName = GetSkillNameByTRIdx("ShipType", i);
		int currentValue = sti(chr.skill.(skillName));
		int tempScore = score + rand(GEN_CHAOS_VALUE) - rand(GEN_CHAOS_VALUE) - rand(GEN_CHAOS_VALUE) * 2;
		if (upNavy && skillName == SKILL_SAILING) tempScore = func_max(score, needSkill + rand(GEN_CHAOS_VALUE));
		if (currentValue < tempScore) SetChrModifier(chr, SKILL_TYPE + skillName, tempScore-currentValue, "officer");
	}
}