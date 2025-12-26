#include "story_frames\StealthCheck\helpers.c"
#include "story_frames\StealthCheckHarbour\Node1.c"

void StealthCheckHarbour_Node0()
{
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
			reaction = SF_AddReaction("b", "", "", SF_Icon("Skill", SKILL_COMMERCE));
			SF_SetResult(reaction, makeint(GetSkillAfterPenalty(pchar, SKILL_COMMERCE) / 2));
		break;
		case "b":
			reaction = SF_AddReaction("b", "", "", SF_Icon("perk", "Doctor1"));
			if (HasPerk(pchar, "Doctor2")) bonus = 40;
			else if (HasPerk(pchar, "Doctor1")) bonus = 25;
			SF_SetResult(reaction, bonus);
			if (!CheckOfficersPerkEnable("Doctor2") && !CheckOfficersPerkEnable("Doctor1")) reaction.disabled = true;
		break;
		case "c":
			reaction = SF_AddReaction("b", "", "", SF_Icon("perk", "Trustworthy"));
			SF_SetResult(reaction, 15);
			if (!HasPerk(pchar, "Trustworthy")) reaction.disabled = true;
		break;
	}

	switch (situation.c)
	{
		case "a":
			// ПРОВЕРКА. Шанс успеха 35+Харизма/2. При успехе результат 1 и +30, при провале результат 2 и -10.
			reaction = SF_AddReaction("c", "", "", SF_Icon("Skill", SKILL_LEADERSHIP));
			SF_SetChance(reaction, 35, "base");
			SF_SetChance(reaction, makeint(GetCharacterSkill(pchar, SKILL_LEADERSHIP) / 2), SKILL_LEADERSHIP);
			SF_SetResults(reaction, -10, 30);
		break;
		case "b":
			storyObject.temp.bribeCost = 5000;
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "basicCommerce"));
			if (sti(pchar.money) < sti(storyObject.temp.bribeCost)) reaction.disabled = true;
			if (CheckOfficersPerkEnable("professionalCommerce")) bonus = 15;
			else if (CheckOfficersPerkEnable("advancedCommerce")) bonus = 25;
			else if (CheckOfficersPerkEnable("basicCommerce")) bonus = 35;
			else reaction.disabled = true;

			SF_SetResult(reaction, bonus);
		break;
		case "c":
			// ПРОВЕРКА. Шанс успеха 25+Восприятие*7. При успехе результат 1 и +30, при провале результат 2 и -10.
			reaction = SF_AddReaction("c", "", "", SF_Icon("pirates", PIRATES_I));
			SF_SetChance(reaction, 25, "base");
			SF_SetChance(reaction, GetSpecialAfterPenalty(pchar, PIRATES_I) * 7, PIRATES_I);
			SF_SetResults(reaction, -10, 30);
		break;
	}

	action = SF_AddAction("a", "", "", SF_Icon("skill", SKILL_SNEAK));
	SF_SetChance(action, -50, "base");
	SF_SetChance(action, GetCharacterSkill(pchar, SKILL_SNEAK) / 2, SKILL_SNEAK);
	SF_SetChance(action, GetCharacterShipClass(pchar) * 9, "ShipRank");
	SF_SetChance(action, (GetCompanionQuantity(pchar)-1) * -3, "ShipQty");
	SF_SetChance(action, GetSpecialAfterPenalty(pchar, SPECIAL_C) * 2, SPECIAL_C);
	SF_SetChance(action, ChangeCharacterNationReputation(pchar, StealthCheck_Nation(), 0), "relationship" + StealthCheck_Nation()); // отношения с нацией

	SF_AddAction("b", "", "", SF_Icon("skill", SKILL_FENCING));
	action = SF_AddAction("c", "", "", SF_Icon("item", "HolTradeLicence"));
	if (!LICENSE_HasLicense()) action.disabled = true;
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
		AddCharacterExpToSkill(pchar, "Sneak", 7);
		return;
	}

	AddCharacterExpToSkill(pchar, "Sneak", 9);
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