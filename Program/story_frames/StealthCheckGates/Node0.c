#include "story_frames\StealthCheck\helpers.c"
#include "story_frames\StealthCheckGates\Node1.c"

void StealthCheckGates_Node0()
{
	storyObject.localization.iNation = StealthCheck_Nation(); // инфа для локализации
	storyObject.title = SF_Convert("title");

	aref situation;
	makearef(situation, storyObject.situation);
	situation.a = 100;

	situation.b.a = 15;
	situation.b.b = 25;
	situation.b.c = 35;
	situation.b.d = 25;

	situation.c.a = 30;
	situation.c.b = 35;
	situation.c.c = 35;

	situation.d = 100;
	SF_ResolveSituation(&situation);

	switch (situation.b)
	{
		case "a":
			reaction = SF_AddReaction("b", "", "", SF_Icon("Skill", SKILL_FENCING));
			SF_SetResult(reaction, 30);
			if (!HasPerk(pchar, "HT1")) reaction.disabled = true;
		break;
		case "b":
			reaction = SF_AddReaction("b", "", "", SF_Icon("Skill", SKILL_COMMERCE));
			SF_SetChance(reaction, 25, "base");
			SF_SetChance(reaction, GetCharacterSkill(pchar, SKILL_COMMERCE) / 2, SKILL_COMMERCE);
			SF_SetResults(reaction, -10, 25);
		break;
		case "c": 
			reaction = SF_AddReaction("b", "", "", SF_Icon("Skill", SKILL_LEADERSHIP));
			SF_SetResult(reaction, GetSpecialAfterPenalty(pchar, SPECIAL_C) * 4);
		break;
		case "d":
			storyObject.temp.prisonerCost = 1000;
			reaction = SF_AddReaction("b", "", "", SF_Icon("perk", "Investor"));
			if (sti(pchar.money) < sti(storyObject.temp.prisonerCost)) reaction.disabled = true;
			SF_SetResult(reaction, 25);
			if (!HasPerk(pchar, "Investor")) reaction.disabled = true;
		break;
	}

	switch (situation.c)
	{
		case "a": 
			reaction = SF_AddReaction("c", "", "", SF_Icon("honor", "repup"))
			if (sti(pchar.reputation.nobility) < (COMPLEX_REPUTATION_NEUTRAL-10)) reaction.disabled = true;
			SF_SetResult(reaction, 25);
		break;
		case "b":
			//ПРОВЕРКА. Шанс успеха 35+огнестрел/2. При успехе результат 1 и +20, при провале результат 2 и +5.
			reaction = SF_AddReaction("c", "", "", SF_Icon("skill", SKILL_PISTOL));
			SF_SetChance(reaction, 35, "base");
			SF_SetChance(reaction, GetCharacterSkill(pchar, SKILL_PISTOL) / 2, SKILL_PISTOL);
			SF_SetResults(reaction, 5, 20);
		break;
		case "c":
			//ПРОВЕРКА. Шанс успеха 16+Восприятие*8. При успехе результат 1 и +22, при провале результат 2. (и ничего)
			reaction = SF_AddReaction("c", "", "", SF_Icon("pirates", PIRATES_I));
			SF_SetChance(reaction, 16, "base");
			SF_SetChance(reaction, GetSpecialAfterPenalty(pchar, PIRATES_I) * 8, PIRATES_I);
			SF_SetResults(reaction, 0, 22);
		break;
	}

	action = SF_AddAction("a", "", "", SF_Icon("skill", SKILL_SNEAK));
	SF_SetChance(action, -40, "base");
	SF_SetChance(action, GetCharacterSkill(pchar, SKILL_SNEAK) / 2, SKILL_SNEAK);
	SF_SetChance(action, GetCharacterSkill(pchar, SKILL_LEADERSHIP) / 2, SKILL_LEADERSHIP);
	SF_SetChance(action, ChangeCharacterNationReputation(pchar, StealthCheck_Nation(), 0), "relationship" + StealthCheck_Nation()); // отношения с нацией
	
	SF_AddAction("b", "", "", SF_Icon("skill", SKILL_FENCING));
	action = SF_AddAction("c", "", "", SF_Icon("item", "HolTradeLicence"));
	if (!LICENSE_HasLicense()) action.disabled = true;
}

// Сказать, что вы столкнулись с агрессивными индейцами в джунглях
void StealthCheckGates_Node0_b_a_reaction()
{
	SF_DefaultReaction("a");
}

// Предложить рассудить спор
void StealthCheckGates_Node0_b_b_reaction()
{
	SF_DefaultReaction("a");
}

// Рассказать историю
void StealthCheckGates_Node0_b_c_reaction()
{
	SF_DefaultReaction("a");
}

// Предложить выкупить пленника.
void StealthCheckGates_Node0_b_d_reaction()
{
	SF_DefaultReaction("a");
	AddMoneyToCharacter(pchar, -sti(storyObject.temp.prisonerCost));
}

// Предложить помощь
void StealthCheckGates_Node0_c_a_reaction()
{
	SF_DefaultReaction("a");
}

// Сказать, что вы хотите поступить на службу
void StealthCheckGates_Node0_c_b_reaction()
{
	SF_DefaultReaction("a");
}

// Осмотреть место
void StealthCheckGates_Node0_c_c_reaction()
{
	SF_DefaultReaction("a");
}

// Попытаться пройти
void StealthCheckGates_Node0_a_action()
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
void StealthCheckGates_Node0_b_action()
{
	StealthCheck_EnterTown("gates", STH_ENEMY);
}

// Показать торговую лицензию
void StealthCheckGates_Node0_c_action()
{
	StealthCheck_EnterTown("gates", STH_LEGAL);
}

// Триумф
void StealthCheckGates_Node0_Triumph()
{
	StealthCheck_EnterTown("gates", STH_LEGAL);
}