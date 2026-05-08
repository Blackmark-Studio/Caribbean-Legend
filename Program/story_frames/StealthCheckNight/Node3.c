void StealthCheckNight_Node3()
{
	aref situation;
	makearef(situation, storyObject.situation);
	situation.a = 100;
	situation.b.a = 30;
	situation.b.b = 40;
	situation.b.c = 30;
	situation.c.a = 30;
	situation.c.b = 40;
	situation.c.c = 30;
	situation.d = 100;
	SF_ResolveSituation(&situation);

	switch (situation.b)
	{
		case "a":
			reaction = SF_AddReaction("b", "", "", SF_Icon("perk", "Trustworthy"));
			SF_SetResult(reaction, 15);
			SF_AddCondition(&reaction, HasPerk(pchar, "Trustworthy"), SF_CONDITION_PERK, "Trustworthy");
		break;
		case "b":
			SF_SetResult(SF_AddReaction("b", "", "", SF_Icon(PIRATES_TYPE, PIRATES_T)), GetCharacterSpecial(pchar, PIRATES_T) * 4);
		break;
		case "c":
			SF_SetResult(SF_AddReaction("b", "", "", SF_Icon(PIRATES_TYPE, PIRATES_A)), GetCharacterSpecial(pchar, PIRATES_A) * 3);
		break;
	}

	switch (situation.c)
	{
		case "a":
			// ПРОВЕРКА. Шанс успеха: 20+отношения с контрабандистами При успехе результат 1 и +16, при провале результат 2 и -9"
			reaction = SF_AddReaction("c", "", "", SF_Icon("fractions", "smugglers"));
			SF_SetChance(reaction, 20, "base");
			SF_SetChance(reaction, sti(pchar.questTemp.Contraband.relation), "relationshipSmugglers");
			SF_SetResults(reaction, -9, 16);
		break;
		case "b":
			reaction = SF_AddReaction("c", "", "", SF_Icon(SKILL_TYPE, SKILL_COMMERCE));
			SF_SetResult(reaction, 25);
			SF_AddCondition(&reaction, HasPerk(pchar, HERO_TYPE_ACCOUNTANT), SF_CONDITION_HERO_TYPE, HERO_TYPE_ACCOUNTANT);
		break;
		case "c":
			reaction = SF_AddReaction("c", "", "", SF_Icon(SKILL_TYPE, SKILL_F_LIGHT));
			SF_SetResult(reaction, 30);
			SF_AddCondition(&reaction, HasPerk(pchar, HERO_TYPE_GYMNAST), SF_CONDITION_HERO_TYPE, HERO_TYPE_GYMNAST);
		break;
	}

	// Попытаться сгладить ситуацию
	action = SF_AddAction("a", "", "", SF_Icon("story", "random"));
	SF_SetChance(action, -50.0, "base");
	SF_SetChance(action, GetCharacterSkill(pchar, SKILL_LEADERSHIP) / 2, SKILL_LEADERSHIP);
	SF_SetChance(action, GetCharacterSpecial(pchar, SPECIAL_L) * 2, SPECIAL_L);

	// Сказать сержанту, что произошла чудовищная ошибка
	StealthCheck_CheckVerifyPapers("b");
}

// Укрепить авторитет сержанта
void StealthCheckNight_Node3_b_a_reaction()
{
	SF_DefaultReaction("a");
}

// Воспользоваться усталостью
void StealthCheckNight_Node3_b_b_reaction()
{
	SF_DefaultReaction("a");
}

// Сослаться на закон
void StealthCheckNight_Node3_b_c_reaction()
{
	SF_DefaultReaction("a");
}

// Окликнуть контрабандистов
void StealthCheckNight_Node3_c_a_reaction()
{
	SF_DefaultReaction("a");
}

// Переключить внимание на таверну
void StealthCheckNight_Node3_c_b_reaction()
{
	SF_DefaultReaction("a");
}

// Призвать к порядку
void StealthCheckNight_Node3_c_c_reaction()
{
	SF_DefaultReaction("a");
}

// Попытаться сгладить ситуацию
void StealthCheckNight_Node3_a_action()
{
	if (SF_PerformCheck())
	{
		SF_Triumph();
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 7);
		return;
	}

	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 9);
	if (bSeaLoaded) SF_Fail("b");
	else SF_Fail("a");
}

// Сказать сержанту, что произошла чудовищная ошибка
void StealthCheckNight_Node3_b_action()
{
	StealthCheck_EnterTown("tavern", STH_LEGAL);
}

// Триумф
void StealthCheckNight_Node3_Triumph()
{
	StealthCheck_EnterTown("tavern", STH_LEGAL);
}

// Крах
void StealthCheckNight_Node3_Fail()
{
	if (!bSeaLoaded)
	{
		StealthCheck_EnterTown("gates", STH_ENEMY); // JOKERTODO: Тут должен быть телепорт к таверне и файт
		return;
	}

	storyObject.exit = true;
	pchar.MoorName = " ";
	notification(XI_ConvertString("FriendFailNotif"), "SneakFail");
	DoQuestCheckDelay(NationShortName(GetBaseHeroNation()) + "_flag_rise", 0.1);
	STH_DelayFort(storyObject.context.colonyId, 45);
	UpdateRelations();
	STH_SetColonyEnemy(storyObject.context.colonyId, 1);
}
