// Сглаживаем значения по рангу ГГ, чтобы рандомные разбросы были адекватны
int GEN_SmoothBonusByRank(int bonus, float playerRank)
{
	if (bonus == 0) return 0;

	float mdf = Bring2Range(0.4, 1.2, 3.0, 26.0, playerRank);
	return makeint(makefloat(bonus) * mdf + 0.5);
}

// Суммируем очки умений, чтобы выдать нужное число очков навыков
void GEN_SummPerkPoints(ref chr, ref points)
{
	int self = GEN_SELF_PERKS_PENALTY;
	int ship = GEN_SHIP_PERKS_PENALTY;
	int selfRate = GetFreePoints_SelfRate(chr);
	int shipRate = GetFreePoints_ShipRate(chr);
	string skillName;

	for (int i = 1; i <= 7; i++)
	{
		skillName = GetSkillNameByTRIdx("SelfType", i);
		self += sti(chr.skill.(skillName));

		skillName = GetSkillNameByTRIdx("ShipType", i);
		ship += sti(chr.skill.(skillName));
	}

	points.self = makeint(self / selfRate);
	points.ship = makeint(ship / shipRate);
	points.self_left = self % selfRate;
	points.ship_left = ship % shipRate;
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

int GEN_GetPowerLevelRankOffset(int powerLevel)
{
	switch (powerLevel)
	{
	case GEN_COMMONER:
		return GEN_COMMONER_RANK_OFFSET;
		break;
	case GEN_ELITE:
		return GEN_ELITE_RANK_OFFSET;
		break;
	case GEN_MINIBOSS:
		return GEN_MINIBOSS_RANK_OFFSET;
		break;
	case GEN_BOSS:
		return GEN_BOSS_RANK_OFFSET;
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
	case GEN_ARCHETYPE_FREE:
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

bool SetAutolevel(ref chr, int chrtype, int powerLvl, string mainArchetype, string secondaryArchetype, bool randomPirates, float selfToShip)
{
	SetAttribute(&TEV, "QCharAutolevel." +  chr.id, true);
	DeleteAttribute(chr, "personality.adaptiveRank");
	chr.personality.chrtype = chrtype;
	chr.personality.powerLvl = powerLvl;
	chr.personality.mainArchetype = mainArchetype;
	chr.personality.secondaryArchetype = secondaryArchetype;
	chr.personality.randomPirates = randomPirates;
	chr.personality.selfToShip = selfToShip;
	return true;
}

void ForceAutolevel(ref chr, int chrtype, int powerLvl, string mainArchetype, string secondaryArchetype, bool randomPirates, float selfToShip)
{
	if (!CheckAttribute(pchar, "personalseed")) return;

	SetAutolevel(chr, chrtype, powerLvl, mainArchetype, secondaryArchetype, randomPirates, selfToShip);
	InitChrRebalance(chr);
}

void ForceAdaptivelevel(ref chr, int rank, int chrtype, int powerLvl, string mainArchetype, string secondaryArchetype, bool randomPirates, float selfToShip)
{
	if (!CheckAttribute(pchar, "personalseed")) return;

	SetAdaptivelevel(chr, rank, chrtype, powerLvl, mainArchetype, secondaryArchetype, randomPirates, selfToShip);
	InitChrRebalance(chr);
}

bool SetAdaptivelevel(ref chr, int rank, int chrtype, int powerLvl, string mainArchetype, string secondaryArchetype, bool randomPirates, float selfToShip)
{
	SetAttribute(&TEV, "QCharAutolevel." +  chr.id, true);
	chr.personality.adaptiveRankMin = rank;
	chr.personality.chrtype = chrtype;
	chr.personality.powerLvl = powerLvl;
	chr.personality.mainArchetype = mainArchetype;
	chr.personality.secondaryArchetype = secondaryArchetype;
	chr.personality.randomPirates = randomPirates;
	chr.personality.selfToShip = selfToShip;
	return true;
}

void ForceHeroAutolevel(ref chr)
{
	SetHeroAutolevel(chr);
	chr.personality.fixedRandom = true;
	InitChrRebalance(chr);
	ForceHeroPerks(chr);
}

void CheckAutolevel(ref chr)
{
	if (IsMainCharacter(chr)) return;
	if (!CheckAttribute(&TEV, "QCharAutolevel." +  chr.id)) return;
	
	InitChrRebalance(chr);
}

// Костыль для ребаланса старых персонажей из старых функций
void ForceOldGenerateToNew(ref chr, int rank)
{
	if (!CheckAttribute(pchar, "personalseed")) return;

	chr.personality.adaptiveRank = rank;
	chr.personality.chrtype = GEN_TYPE_ENEMY;
	chr.personality.powerLvl = GEN_BY_RANK
	chr.personality.mainArchetype = GEN_ARCHETYPE_RANDOM;
	chr.personality.secondaryArchetype = GEN_ARCHETYPE_RANDOM;
	chr.personality.selfToShip = 0.6;
	InitChrRebalance(chr);
}

// Сглаживаем фиксированный ранг противника об ранг игрока для последующего автолевелинга
int GEN_GetTargetRankFromFixed(int rank)
{
	float pcharRank = GetAttributeFloatOrDefault(pchar, "rank", 1.0);
	return makeint(rank * pow((pcharRank / rank), 0.4));
}

// По сглаженному рангу получаем разряд персонажа
int GEN_GetPowerLvlByRank(int rank)
{
	int pcharRank = sti(pchar.rank);
	int chrtype = GEN_COMMONER;
	if (rank - pcharRank >= GEN_BOSS_RANK_OFFSET) chrtype = GEN_BOSS;
	else if (rank - pcharRank >= GEN_MINIBOSS_RANK_OFFSET) chrtype = GEN_MINIBOSS;
	else if (rank - pcharRank >= GEN_ELITE_RANK_OFFSET) chrtype = GEN_ELITE;
	return chrtype;
}

void GEN_SetNavyFromShip(ref chr)
{
	int shipClass = GetCharacterShipClass(chr);
	if (shipClass > 6) return;
	int needSkill = GetShipClassNavySkill(shipClass);

	int currentValue = sti(chr.skill.sailing);
	if (currentValue < needSkill) chr.skill.sailing = needSkill + rand(5);
}

int GEN_RandLock(ref chr, int n, string tag)
{
	if (CheckAttribute(chr, "personality.fixedRandom")) return TagRandom(n, chr.id + tag);
	return rand(n);
}