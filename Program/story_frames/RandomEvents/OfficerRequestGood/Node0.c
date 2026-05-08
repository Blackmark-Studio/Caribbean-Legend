#include "story_frames\RandomEvents\helpers.c"
#include "story_frames\RandomEvents\OfficerRequestGood\condition.c"
ref officer, prisoner;

void OfficerRequestGood_Node0()
{
	PlaySound("interface\knock.wav");
	SF_InitModule("RandomEvents");
	storyObject.title = SF_Convert("title");
	storyObject.icon.group = "SEASONS_ICONS";
	storyObject.icon.picture = "stories";

	aref situation;
	makearef(situation, storyObject.situation);
	if (!SF_InitConditions(&context, &situation, true))
	{
		SF_ExitButton("The conditions of the story " + StoryObject.name + " are not fulfilled");
		return;
	}
	officer = CharacterFromIDSafe(context.officerId);
	if (CheckAttribute(context, "prisonerId")) prisoner = CharacterFromIDSafe(context.prisonerId);
	SF_ResolveSituation(&situation);

	switch (situation.a)
	{
		case "a":
			action = SF_AddAction("a_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, 25, "base");
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_FORTUNE)/2, SKILL_FORTUNE + "$" + officer.name);
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_SHOOTER), SF_CONDITION_HERO_TYPE, HERO_TYPE_SHOOTER);
			action = SF_AddAction("a_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("a_c", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_ATHLETE));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_ATHLETE), SF_CONDITION_HERO_TYPE, HERO_TYPE_ATHLETE);
		break;
		case "b":
			action = SF_AddAction("b_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, 10, "base");
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_F_HEAVY)/3, SKILL_F_HEAVY + "$" + officer.name);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_F_LIGHT)/3, SKILL_F_LIGHT + "$" + officer.name);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_FENCING)/3, SKILL_FENCING + "$" + officer.name);
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_GYMNAST), SF_CONDITION_HERO_TYPE, HERO_TYPE_GYMNAST);
			action = SF_AddAction("b_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("b_c", "", "", SF_Icon("story", "forward"));
		break;
		case "c":
			action = SF_AddAction("c_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("c_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("c_c", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_ACCOUNTANT));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_ACCOUNTANT), SF_CONDITION_HERO_TYPE, HERO_TYPE_ACCOUNTANT);
			action = SF_AddAction("c_d", "", "", SF_Icon("story", "forward"));
		break;
		case "d":
			action = SF_AddAction("d_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("d_b", "", "", SF_Icon("story", "forward"));
			SF_AddCondition(&action, int(pchar.money) >= 10000, SF_CONDITION_MONEY);
			action = SF_AddAction("d_c", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, 25, "base");
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP)/2, SKILL_LEADERSHIP);
			SF_SetChance(action, int(pchar.reputation.nobility), "Nobility");
			action = SF_AddAction("d_d", "", "", SF_Icon("story", "forward"));
			SF_AddCondition(&action, CheckAttribute(pchar, "questTemp.ShipCapellan.Yes"), SF_CONDITION_CAPELLAN);
		break;
	}

	RE_SetEventDelay(120);
}


void OfficerRequestGood_Node0_a_a_action()
{
	if (SF_PerformCheck())
	{
		SF_Triumph("a_a");
		SF_AddEffect(SF_E_MONEY, pchar, 2500);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_FORTUNE, 50.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 25);
		SF_AddEffect(SF_E_LOYALITY, officer, 2);
		return;
	}

	SF_AddEffect(SF_E_MONEY, pchar, -5000);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_FORTUNE, 40);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 20);
	SF_Fail("a_a");
}

void OfficerRequestGood_Node0_a_b_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, -1);
	SF_AddEffect(SF_E_MONEY, pchar, GetMoneyForOfficerFull(officer));
	SF_AddEffect(SF_E_MORALE, pchar, 10, true);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Sailors", 15);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Cannoners", 15);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Soldiers", 15);
	SF_Triumph("a_b");
}

void OfficerRequestGood_Node0_a_c_action()
{
	SF_AddEffect(SF_E_MORALE, pchar, -10, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 20.0);
	SF_AddEffect(SF_E_LOYALITY, officer, 3);
	SF_Triumph("a_c");
}

void OfficerRequestGood_Node0_b_a_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_LOYALITY, officer, 2);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_LIGHT, 50.0);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_FENCING, 50.0);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_HEAVY, 50.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 25.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, 25.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, 25.0);
		SF_Triumph("b_a");
		return;
	}

	SF_AddEffect(SF_E_LOYALITY, officer, -1);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_LIGHT, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_FENCING, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_HEAVY, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 15.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, 15.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, 15.0);
	SF_Fail("b_a");
}

void OfficerRequestGood_Node0_b_b_action()
{
	SF_AddEffect(SF_E_ITEMS_CABIN, context.bladeId, -1);
	SF_AddEffect(SF_E_LOYALITY, officer, 3);
	SF_AddEffect(SF_E_MORALE, pchar, 10, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 50.0);
	object fellows;
	AddAllFellows(&fellows, pchar, false);
	for (int i=0; i < GetAttributesNum(&fellows); i++)
	{
		ref chr = GetCharacter(sti(GetAttributeValue(GetAttributeN(&fellows, i))));
		SF_AddEffect(SF_E_SKILL_EXP, chr, SKILL_LEADERSHIP, 50.0);
	}
	SF_Triumph("b_b");
}

void OfficerRequestGood_Node0_b_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, -2);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Sailors", 15);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Cannoners", 15);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Soldiers", 15);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 30.0);
	SF_Triumph("b_c");
}

void OfficerRequestGood_Node0_c_a_action()
{
	RemovePassenger(pchar, prisoner);
	SF_AddEffect(SF_E_LOYALITY, officer, -3);
	SF_AddEffect(SF_E_MORALE, pchar, 30, true);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", -30);
	SF_AddEffect(SF_E_TEMP_MODIFIER, pchar, M_SQUADRON_POWER, 0.30, "OfficerRequestGood", 30);
	CT_UpdateCashTables(pchar);

	aref achievement = GetAref(&RandEventSystem, "achievments.a212", true);
	achievement.OfficerRequestGood_Node0_c_a_action = true;
	if (GetAttributesNum(achievement > 3)) Achievment_Set("ach_CL_212");
	SF_Triumph("c_a");
}

void OfficerRequestGood_Node0_c_b_action()
{
	LAi_KillCharacter(prisoner);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_LEADERSHIP, 50.0);
	SF_AddEffect(SF_E_LOYALITY, officer, 3);
	SF_Triumph("c_b");
}

void OfficerRequestGood_Node0_c_c_action()
{
	LAi_KillCharacter(prisoner);
	SF_AddEffect(SF_E_LOYALITY, officer, 1);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_COMMERCE, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 25.0);
	SF_AddEffect(SF_E_MONEY, pchar, GetMoneyForOfficerFull(officer));
	SF_Triumph("c_c");
}

void OfficerRequestGood_Node0_c_d_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, -1);
	SF_AddEffect(SF_E_MORALE, pchar, 10, true);
	SF_Triumph("c_d");
}

void OfficerRequestGood_Node0_d_a_action()
{
	SF_AddEffect(SF_E_ITEMS_CABIN, "mineral3", -1);
	SF_AddEffect(SF_E_ITEMS_CABIN, "mineral5", -1);
	SF_AddEffect(SF_E_LOYALITY, officer, 3);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", 5);
	SF_Triumph("d_a");
}

void OfficerRequestGood_Node0_d_b_action()
{
	SF_AddEffect(SF_E_MONEY, pchar, 10000);
	object fellows;
	AddAllFellows(&fellows, pchar, false);
	int fellowsQty = GetAttributesNum(&fellows);
	for (int i=0; i < fellowsQty; i++)
	{
		ref fellow = FindChar_VT(sti(GetAttributeValue(GetAttributeN(&fellows, i))), true);
		if (fellow == nullptr) continue;
		SF_AddEffect(SF_E_LOYALITY, fellow, 1);
	}
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", 10);
	SF_Triumph("d_b");
}

void OfficerRequestGood_Node0_d_c_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_LOYALITY, officer, 3);
		SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", 15);
		SF_Triumph("d_c");
		return;
	}

	SF_AddEffect(SF_E_LOYALITY, officer, -1);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", -5);
	SF_Fail("d_c");
}

void OfficerRequestGood_Node0_d_d_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, 3);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", 20);
	SF_AddEffect(SF_E_MORALE, pchar, 10, true);
	SF_Triumph("d_d");
}

void OfficerRequestGood_Node0_Triumph()
{
	storyObject.exit = true;
}

void OfficerRequestGood_Node0_Fail()
{
	storyObject.exit = true;
}
