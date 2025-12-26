void StealthCheckNight_Node1()
{
	aref situation;
	makearef(situation, storyObject.situation);
	situation.a = 100;
	situation.b.a = 40;
	situation.b.b = 35;
	situation.b.c = 25;
	situation.c = 100;
	SF_ResolveSituation(&situation);

	switch (situation.b)
	{
		case "a":
			// ПРОВЕРКА. Шанс успеха 16+Выносливость*7. При успехе результат 1 и +22, при провале результат 2 и -15
			reaction = SF_AddReaction("b", "", "", SF_Icon("pirates", PIRATES_E));
			SF_SetChance(reaction, 16, "base");
			SF_SetChance(reaction, GetSpecialAfterPenalty(pchar, PIRATES_E) * 7, PIRATES_E);
			SF_SetResults(reaction, -15, 22);
		break;
		case "b":
			// ПРОВЕРКА. Шанс успеха 16+Восприятие*7. При успехе результат 1 и +23, при провале результат 2 и -16
			reaction = SF_AddReaction("b", "", "", SF_Icon("pirates", PIRATES_I));
			SF_SetChance(reaction, 16, "base");
			SF_SetChance(reaction, GetSpecialAfterPenalty(pchar, PIRATES_I) * 7, PIRATES_I);
			SF_SetResults(reaction, -16, 23);
		break;
		case "c":
			// ПРОВЕРКА. Шанс успеха 16+Реакция*7. При успехе результат 1 и +21, при провале результат 2 и -14
			reaction = SF_AddReaction("b", "", "", SF_Icon("pirates", PIRATES_R));
			SF_SetChance(reaction, 16, "base");
			SF_SetChance(reaction, GetSpecialAfterPenalty(pchar, PIRATES_R) * 7, PIRATES_R);
			SF_SetResults(reaction, -14, 21);
		break;
	}

	// Проскользнуть мимо
	action = SF_AddAction("a", "", "", SF_Icon("skill", SKILL_SNEAK));
	SF_SetChance(action, 15, "base");
	SF_SetChance(action, GetCharacterSkill(pchar, SKILL_SNEAK) / 2, SKILL_SNEAK);
	SF_SetChance(action, StealthCheckNight_ArmorFactor(), CIRASS_ITEM_TYPE);

	// Я умею двигаться абсолютно незаметно
	action = SF_AddAction("b", "", "", SF_Icon("perk", "Quiet"));
	if (!HasPerk(pchar, "Quiet")) action.disabled = true;
}

// Замереть и задержать дыхание
void StealthCheckNight_Node1_b_a_reaction()
{
	SF_DefaultReaction("a");
}

// Найти обходной путь
void StealthCheckNight_Node1_b_b_reaction()
{
	SF_DefaultReaction("a");
}

// Швырнуть камень и отвлечь убийцу
void StealthCheckNight_Node1_b_c_reaction()
{
	SF_DefaultReaction("a");
}

// Проскользнуть мимо
void StealthCheckNight_Node1_a_action()
{
	if (SF_PerformCheck())
	{
		SF_Triumph();
		AddCharacterExpToSkill(pchar, "Sneak", 7);
		return;
	}

	AddCharacterExpToSkill(pchar, "Sneak", 9);
	SF_SwitchNode("Node3");
}

// Я умею двигаться абсолютно незаметно
void StealthCheckNight_Node1_b_action()
{
	SF_Triumph();
}

// Триумф
void StealthCheckNight_Node1_Triumph()
{
	StealthCheck_EnterTown("tavern", STH_LEGAL);
}

// // =========================================
// // ============ Хелперы истории ============
// // =========================================

int StealthCheckNight_ArmorFactor()
{
	string cirassId = GetCharacterEquipByGroup(pchar, CIRASS_ITEM_TYPE);
	if (cirassId == "") return 25;

	ref cirass = ItemsFromID(cirassId);
	switch (GetAttributeInt(cirass, "modifiers." + HAS + M_ARMOR_TYPE))
	{
		case ARMOR_LIGHT: return 20; break;
		case ARMOR_MEDIUM: return -10; break;
		case ARMOR_HEAVY: return -25; break;
	}
}
