// Модифицируем сгенерированных персонажей от сложности

void GEN_ApplyDifficulty(ref chr, int chrtype, int powerLvl)
{
	int difficultyLevel = GetNormalizedDifficultyLevel();
	int bonusHP = GEN_GetHPBonus(powerLvl, chrtype, difficultyLevel);
	if (bonusHP != 0) SetChrModifier(chr, M_HP_PER_RANK, bonusHP, "difficulty");
}

void GEN_ApplyPlayerDifficulty(ref chr)
{
	int difficultyLevel = GetNormalizedDifficultyLevel();
	object temp;
	SplitString(&temp, GEN_PLAYER_HP_BONUS, "|", 0);
	int bonusHP = GetAttributeValue(GetAttributeN(&temp, difficultyLevel));
	if (bonusHP != 0) SetChrModifier(chr, M_HP_PER_RANK, bonusHP, "difficulty");
}

// Размазываем флоат об сложность, для квестовых ситуёвин
// На классике вернем max, на лёгком min, на остальных линейное возрастание
float GetFloatModifiedByDifficulty(float value, float min, float max)
{
	int difficulty = GetNormalizedDifficultyLevel();
	float step = (max - min) * 0.25; // всего 4 шага
	return value * min + value * step * difficulty;
}

// 0 = лёгкий, 4 = классика
int GetNormalizedDifficultyLevel()
{
	return makeint((MOD_SKILL_ENEMY_RATE-1) * 0.5);
}

int GEN_GetHPBonus(int powerLvl, int chrtype, int difficultyLevel)
{
	string attrName = "generator.difficulty.hp.powerLvl_" + powerLvl + ".chrType_" + chrtype;

	// Проверяем, что конфиг не изменился
	if (!CheckAttributeEqualTo(&TEV, "generator.difficulty.checkSumm", GEN_CHECK_SUM))
	{
		DeleteAttribute(&TEV, "generator.difficulty");
		TEV.generator.difficulty.checkSumm = GEN_CHECK_SUM;
	}

	if (CheckAttribute(&TEV, attrName)) return sti(TEV.(attrName)); // уже считали

	object temp;
	switch (chrtype)
	{
		case GEN_TYPE_ENEMY:
		{
			switch (powerLvl)
			{
				case GEN_COMMONER: SplitString(&temp, GEN_ENEMY_COMMONER_HP_BONUS, "|", 0); break;
				case GEN_ELITE:    SplitString(&temp, GEN_ENEMY_ELITE_HP_BONUS,    "|", 0); break;
				case GEN_MINIBOSS: SplitString(&temp, GEN_ENEMY_MINIBOSS_HP_BONUS, "|", 0); break;
				case GEN_BOSS:     SplitString(&temp, GEN_ENEMY_BOSS_HP_BONUS,     "|", 0); break;
			}
		}
		break;
		case GEN_TYPE_OFFICER:
		{
			switch (powerLvl)
			{
				case GEN_COMMONER: SplitString(&temp, GEN_OFFICER_COMMONER_HP_BONUS, "|", 0); break;
				case GEN_ELITE:    SplitString(&temp, GEN_OFFICER_ELITE_HP_BONUS,    "|", 0); break;
				case GEN_MINIBOSS: SplitString(&temp, GEN_OFFICER_MINIBOSS_HP_BONUS, "|", 0); break;
				case GEN_BOSS:     SplitString(&temp, GEN_OFFICER_BOSS_HP_BONUS,     "|", 0); break;
			}
		}
		break;
	}

	TEV.(attrName) = GetAttributeValue(GetAttributeN(&temp, difficultyLevel));
	return sti(TEV.(attrName));
}
