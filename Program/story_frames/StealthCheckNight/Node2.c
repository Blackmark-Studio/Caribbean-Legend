void StealthCheckNight_Node2()
{
	aref situation;
	makearef(situation, storyObject.situation);
	situation.a = 100;
	situation.b.a = 30;
	situation.b.b = 40;
	situation.b.c = 30;
	situation.c = 100;
	SF_ResolveSituation(&situation);

	switch (situation.b)
	{
		case "a":
			// ПРОВЕРКА. Шанс успеха 17+Лидерство*7. При успехе результат 1 и +21, при провале результат 2 и -16
			reaction = SF_AddReaction("b", "", "", SF_Icon(PIRATES_TYPE, PIRATES_E));
			SF_SetChance(reaction, 17, "base");
			SF_SetChance(reaction, GetSpecialAfterPenalty(pchar, PIRATES_A) * 7, PIRATES_A);
			SF_SetResults(reaction, -16, 21);
		break;
		case "b":
			// "ПРОВЕРКА. Шанс успеха: Навигация/2 + 38. При успехе результат 1 и +22, при провале результат 2 и -14
			reaction = SF_AddReaction("b", "", "", SF_Icon(PIRATES_TYPE, PIRATES_I));
			SF_SetChance(reaction, 38, "base");
			SF_SetChance(reaction, MakeInt(GetCharacterSkill(pchar, SKILL_SAILING) / 2), SKILL_SAILING);
			SF_SetResults(reaction, -14, 22);
		break;
		case "c":
			// "ПРОВЕРКА. Шанс успеха 30+Удача*6. При успехе результат 1 и +17, при провале результат 2 и -11 Бутылка не тратится"
			reaction = SF_AddReaction("b", "", "", SF_Icon(PIRATES_TYPE, PIRATES_S));
			SF_SetChance(reaction, 30, "base");
			SF_SetChance(reaction, GetSpecialAfterPenalty(pchar, PIRATES_S) * 7, SF_Icon("item", "potionwine"));
			SF_SetResults(reaction, -11, 17);
			SF_AddCondition(&reaction, GetCharacterFreeItem(pchar, "potionwine") > 0, SF_CONDITION_ITEM, "potionwine");
		break;
	}

	// Попытаться пройти в таверну
	action = SF_AddAction("a", "", "", SF_Icon("story", "random"));
	SF_SetChance(action, 15, "base");
	SF_SetChance(action, GetCharacterSkill(pchar, SKILL_LEADERSHIP) / 2, SKILL_LEADERSHIP);
	SF_SetChance(action, StealthCheckNight_UniformFactor(), "Uniform");
	if (CheckAttributeEqualTo(pchar, "questTemp.Trial", "spy")) SF_SetChance(action, 70, "questZpq"); // если "неизвестный гасконец" - квестовый тег для карибских нравов
	if (IsCharacterEquippedArtefact(pchar, "indian_11")) SF_SetChance(action, 15, "itmname_indian_11"); // если маска нгомбо

	// Я отлично умею сойти за своего
	action = SF_AddAction("b", "", "", SF_Icon("perk", "tieFit"));
	SF_AddCondition(&action, HasPerk(pchar, "tieFit"), SF_CONDITION_PERK, "tieFit");

	// У меня есть торговая лицензия на случай неприятностей
	StealthCheck_CheckVerifyPapers("c");
}

// Спросить дорогу до таверны
void StealthCheckNight_Node2_b_a_reaction()
{
	SF_DefaultReaction("a");
}

// Спеть моряцкую песню
void StealthCheckNight_Node2_b_b_reaction()
{
	SF_DefaultReaction("a");
}

// Угостить дворянина вином
void StealthCheckNight_Node2_b_c_reaction()
{
	SF_DefaultReaction("a");
}

// Попытаться пройти в таверну
void StealthCheckNight_Node2_a_action()
{
	if (SF_PerformCheck())
	{
		SF_Triumph();
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 7);
		return;
	}

	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 9);
	SF_SwitchNode("Node3");
}

// Я умею двигаться абсолютно незаметно
void StealthCheckNight_Node2_b_action()
{
	SF_Triumph();
}

// У меня есть торговая лицензия на случай неприятностей
void StealthCheckNight_Node2_c_action()
{
	StealthCheck_EnterTown("tavern", STH_LEGAL);
}

// Триумф
void StealthCheckNight_Node2_Triumph()
{
	StealthCheck_EnterTown("tavern", STH_LEGAL);
}

// // =========================================
// // ============ Хелперы истории ============
// // =========================================

int StealthCheckNight_UniformFactor()
{
	string cirassId = GetCharacterEquipByGroup(pchar, CIRASS_ITEM_TYPE);
	if (cirassId == "suit1") return -20;
	if (cirassId == "suit2") return -20;
	if (cirassId == "suit3") return -20;
	if (cirassId == "suit5") return -20;
	return 0;
}