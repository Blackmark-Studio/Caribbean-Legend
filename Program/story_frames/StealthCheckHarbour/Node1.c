void StealthCheckHarbour_Node1()
{
	aref situation;
	makearef(situation, storyObject.situation);
	situation.a = 100;

	situation.b.a = 40;
	situation.b.b = 25;
	situation.b.c = 35;

	situation.c.a = 10;
	situation.c.b = 60;
	situation.c.c = 30;

	situation.d = 100;

	SF_ResolveSituation(&situation);

	switch (situation.b)
	{
		case "a":
			reaction = SF_AddReaction("b", "", "", SF_Icon(SKILL_TYPE, SKILL_COMMERCE));
			SF_SetResult(reaction, 40);
			SF_AddCondition(&reaction, HasPerk(pchar, HERO_TYPE_ACCOUNTANT), SF_CONDITION_HERO_TYPE, HERO_TYPE_ACCOUNTANT);
		break;
		case "b":
			reaction = SF_AddReaction("b", "", "", SF_Icon(SKILL_TYPE, SKILL_COMMERCE));
			SF_AddCondition(&reaction, HasPerk(pchar, HERO_TYPE_ATHLETE), SF_CONDITION_HERO_TYPE, HERO_TYPE_ATHLETE);
			SF_SetResult(reaction, GetCharacterSpecial(pchar, SPECIAL_E) * 4 + GetCharacterSpecial(pchar, SPECIAL_S) * 4);
		break;
		case "c":
			reaction = SF_AddReaction("b", "", "", SF_Icon(PIRATES_TYPE, PIRATES_A));
			SF_SetResult(reaction, GetCharacterSpecial(pchar, SPECIAL_C) * 3);
		break;
	}

	switch (situation.c)
	{
		case "a": SF_SetResult(SF_AddReaction("c", "", "", SF_Icon(PIRATES_TYPE, PIRATES_S)), -4+SF_Rand(10)); break;
		case "b": 
			// Если честь нейтральная или положительная, то результат 1 и +30, если отрицательная - то результат 2 и +10
			reaction = SF_AddReaction("c", "", "", SF_Icon(PIRATES_TYPE, PIRATES_A));
			storyObject.temp.c_b_state = sti(pchar.reputation.nobility) > (COMPLEX_REPUTATION_NEUTRAL-10);
			if (AttributeIsTrue(storyObject, "temp.c_b_state")) bonus = 30;
			else bonus = 10;
			SF_SetResult(reaction, bonus);
		break;
		case "c":
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "Collection"));
			SF_SetResult(reaction, 30);
			SF_AddCondition(&reaction, HasPerk(pchar, "Collection"), SF_CONDITION_PERK, "Collection");
		break;
	}

	action = SF_AddAction("a", "", "", SF_Icon(SKILL_TYPE, SKILL_LEADERSHIP));
	SF_SetChance(action, -50.0, "base");
	SF_SetChance(action, GetCharacterSkill(pchar, SKILL_LEADERSHIP) / 2, SKILL_LEADERSHIP);
	SF_SetChance(action, GetCharacterSpecial(pchar, SPECIAL_L) * 2, SPECIAL_L);
	if (HasShipTrait(pchar, "trait05")) SF_SetChance(action, 15, "trait05"); // +если трейт Фальшивые документы
	SF_SetChance(action, makeint(SZN_GetModifierMtp(M_STEALTH_INCEPTION_BONUS, 0.0, -0.30, 0.30) * 100), "season");

	SF_AddAction("b", "", "", SF_Icon("story", "fail"));
}

// Убедить моряков, что в море нет наций и флагов, только суровый быт и тяжелый физический труд
void StealthCheckHarbour_Node1_b_a_reaction()
{
	SF_DefaultReaction("a");
}

// Прибавляет Сила*4 и Выносливость*4 к проверке
void StealthCheckHarbour_Node1_b_b_reaction()
{
	SF_DefaultReaction("a");
}

// Сослаться на морские законы, прямо запрещающие случайные необоснованные досмотры кораблей в порту
void StealthCheckHarbour_Node1_b_c_reaction()
{
	SF_DefaultReaction("a");
}

// Попытаться угадать причину траура и сказать, что вы прибыли по этому поводу.
void StealthCheckHarbour_Node1_c_a_reaction()
{
	SF_DefaultReaction("a");
}

// Сказать, что за вас может поручиться знакомый капитан.
void StealthCheckHarbour_Node1_c_b_reaction()
{
	SF_ReactionWithFixedBonus("a", false);
	SF_Log(SF_Convert("log_" + storyObject.temp.c_b_state));
}

// Сказать, что вы везёте церковные реликвии специально для праздника и уже опаздываете.
void StealthCheckHarbour_Node1_c_c_reaction()
{
	SF_DefaultReaction("a");
}

// Попытаться сгладить ситуацию
void StealthCheckHarbour_Node1_a_action()
{
	if (SF_PerformCheck())
	{
		SF_Triumph();
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 7);
		return;
	}

	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 9);
	SF_Fail();
}

void StealthCheckHarbour_Node1_Triumph()
{
	StealthCheck_EnterTown("port", STH_LEGAL);
}

void StealthCheckHarbour_Node1_Fail()
{
	storyObject.exit = true;
	pchar.MoorName = " ";
	notification(XI_ConvertString("FriendFailNotif"), "SneakFail");
	DoQuestCheckDelay(NationShortName(GetBaseHeroNation()) + "_flag_rise", 0.1);
	STH_DelayFort(storyObject.context.colonyId, 45);
	UpdateRelations();
	STH_SetColonyEnemy(storyObject.context.colonyId, 1);
}

// Сняться с якоря и сбежать
void StealthCheckHarbour_Node1_b_action()
{
	storyObject.exit = true;
	pchar.MoorName = " ";
	notification(XI_ConvertString("FriendFailNotif"), "SneakFail");
	DoQuestCheckDelay(NationShortName(GetBaseHeroNation()) + "_flag_rise", 0.1);

	STH_DelayFort(storyObject.context.colonyId, 90);
	UpdateRelations();
	STH_SetColonyEnemy(storyObject.context.colonyId, 1);
}
