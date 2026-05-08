#include "story_frames\StealthCheck\helpers.c"
#include "story_frames\StealthCheckHarbour\Node1.c"

void StealthCheckHarbour_Node0()
{
	SF_InitModule("StealthCheck");
	storyObject.title = SF_Convert("title");

	aref situation;
	makearef (situation, storyObject.situation);
	situation.a = 100;

	situation.b.a = 35;
	situation.b.b = 35;
	situation.b.c = 30;

	situation.c.a = 40;
	situation.c.b = 35;
	situation.c.c = 25;

	situation.d = 100;
	SF_ResolveSituation(&situation);

	switch (situation.b)
	{
		case "a":
			reaction = SF_AddReaction("b", "", "", SF_Icon(SKILL_TYPE, SKILL_COMMERCE));
			SF_SetResult(reaction, makeint(GetSkillAfterPenalty(pchar, SKILL_COMMERCE) / 2));
		break;
		case "b":
			reaction = SF_AddReaction("b", "", "", SF_Icon("perk", "Doctor1"));
			if (CheckOfficersPerkEnable("Doctor2")) bonus = 40;
			else if (CheckOfficersPerkEnable("Doctor1")) bonus = 25;
			else SF_AddCondition(&reaction, false, SF_CONDITION_PERK, "Doctor1");
			SF_SetResult(reaction, bonus);
		break;
		case "c":
			reaction = SF_AddReaction("b", "", "", SF_Icon("perk", "Trustworthy"));
			SF_SetResult(reaction, 15);
			SF_AddCondition(&reaction, HasPerk(pchar, "Trustworthy"), SF_CONDITION_PERK, "Trustworthy");
		break;
	}

	switch (situation.c)
	{
		case "a":
			// ПРОВЕРКА. Шанс успеха 35+Харизма/2. При успехе результат 1 и +30, при провале результат 2 и -10.
			reaction = SF_AddReaction("c", "", "", SF_Icon(SKILL_TYPE, SKILL_LEADERSHIP));
			SF_SetChance(reaction, 35, "base");
			SF_SetChance(reaction, makeint(GetCharacterSkill(pchar, SKILL_LEADERSHIP) / 2), SKILL_LEADERSHIP);
			SF_SetResults(reaction, -10, 30);
		break;
		case "b":
			storyObject.temp.bribeCost = 5000;
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "basicCommerce"));
			SF_AddCondition(&reaction, sti(pchar.money) > sti(storyObject.temp.bribeCost), SF_CONDITION_MONEY);
			if (CheckOfficersPerkEnable("professionalCommerce")) bonus = 15;
			else if (CheckOfficersPerkEnable("advancedCommerce")) bonus = 25;
			else if (CheckOfficersPerkEnable("basicCommerce")) bonus = 35;
			else SF_AddCondition(&reaction, false, SF_CONDITION_PERK, "basicCommerce");

			SF_SetResult(reaction, bonus);
		break;
		case "c":
			// ПРОВЕРКА. Шанс успеха 25+Восприятие*7. При успехе результат 1 и +30, при провале результат 2 и -10.
			reaction = SF_AddReaction("c", "", "", SF_Icon(PIRATES_TYPE, PIRATES_I));
			SF_SetChance(reaction, 25, "base");
			SF_SetChance(reaction, GetSpecialAfterPenalty(pchar, PIRATES_I) * 7, PIRATES_I);
			SF_SetResults(reaction, -10, 30);
		break;
	}

	action = SF_AddAction("a", "", "", SF_Icon(SKILL_TYPE, SKILL_SNEAK));
	SF_SetChance(action, -50, "base");
	SF_SetChance(action, GetCharacterSkill(pchar, SKILL_SNEAK) / 2, SKILL_SNEAK);
	SF_SetChance(action, GetCharacterShipClass(pchar) * 9, "ShipRank");
	SF_SetChance(action, (GetCompanionQuantity(pchar)-1) * -3, "ShipQty");
	SF_SetChance(action, GetSpecialAfterPenalty(pchar, SPECIAL_C) * 2, SPECIAL_C);
	SF_SetChance(action, ChangeCharacterNationReputation(pchar, StealthCheck_Nation(), 0), "relationship" + StealthCheck_Nation()); // отношения с нацией
	if (CheckAttributeEqualTo(pchar, "questTemp.Trial", "spy")) SF_SetChance(action, 50, "questZpq"); // +если "неизвестный гасконец" - квестовый тег для карибских нравов
	if (HasShipTrait(pchar, "trait05")) SF_SetChance(action, 15, "trait05"); // +если трейт Фальшивые документы
	SF_SetChance(action, makeint(SZN_GetModifierMtp(M_STEALTH_INCEPTION_BONUS, 0.0, -0.30, 0.30) * 100), "season");

	SF_AddAction("b", "", "", SF_Icon(SKILL_TYPE, SKILL_FENCING));
	StealthCheck_CheckVerifyPapers("c");
}

// Притвориться кораблем сопровождения и присоединиться к разгрузке
void StealthCheckHarbour_Node0_b_a_reaction()
{
	SF_DefaultReaction("a");
}

// Притвориться санитарным кораблем, который прислан ухаживать за ранеными
void StealthCheckHarbour_Node0_b_b_reaction()
{
	SF_DefaultReaction("a");
}

// Притвориться секретным курьерским кораблём с важным донесением
void StealthCheckHarbour_Node0_b_c_reaction()
{
	SF_DefaultReaction("a");
}

// Проявить сочувствие и предложить опустить формальности
void StealthCheckHarbour_Node0_c_a_reaction()
{
	SF_DefaultReaction("a");
}

// Показать готовность заплатить двойную пошлину.
void StealthCheckHarbour_Node0_c_b_reaction()
{
	SF_DefaultReaction("a");
	AddMoneyToCharacter(pchar, -sti(storyObject.temp.bribeCost));
}

void StealthCheckHarbour_Node0_c_c_reaction()
{
	SF_DefaultReaction("a");
}

// Попытаться пройти
void StealthCheckHarbour_Node0_a_action()
{
	if (SF_PerformCheck())
	{
		SF_Triumph();
		SF_AddEffect(SF_E_SKILL_EXP, pchar, "Sneak", 7);
		return;
	}

	SF_AddEffect(SF_E_SKILL_EXP, pchar, "Sneak", 9);
	SF_SwitchNode("Node1");
}

// Прорваться с боем
void StealthCheckHarbour_Node0_b_action()
{
	StealthCheck_EnterTown("port", STH_ENEMY);
}

// Показать торговую лицензию
void StealthCheckHarbour_Node0_c_action()
{
	StealthCheck_EnterTown("port", STH_LEGAL);
}

// Триумф
void StealthCheckHarbour_Node0_Triumph()
{
	StealthCheck_EnterTown("port", STH_LEGAL);
}