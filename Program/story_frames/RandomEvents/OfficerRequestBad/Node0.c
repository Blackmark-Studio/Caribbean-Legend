#include "story_frames\RandomEvents\helpers.c"
#include "story_frames\RandomEvents\OfficerRequestBad\condition.c"
ref officer, prisoner;

void OfficerRequestBad_Node0()
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
	SF_ResolveSituation(&situation);

	switch (situation.a)
	{
		case "a":
			action = SF_AddAction("a_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, 10, "base");
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_F_HEAVY)/3, SKILL_F_HEAVY + "$" + officer.name);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_F_LIGHT)/3, SKILL_F_LIGHT + "$" + officer.name);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_FENCING)/3, SKILL_FENCING + "$" + officer.name);
			action = SF_AddAction("a_b", "", "", SF_Icon("story", "forward"));
			SF_AddCondition(&action, int(pchar.money) >= 10000, SF_CONDITION_MONEY);
			action = SF_AddAction("a_c", "", "", SF_Icon("story", "forward"));
		break;
		case "b":
			action = SF_AddAction("b_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP)/2, SKILL_LEADERSHIP);
			SF_SetChance(action, -GetSkillAfterPenalty(officer, SKILL_LEADERSHIP)/2, SKILL_LEADERSHIP + "$" + officer.name);
			SF_SetChance(action, (8-GetCharacterShipClass(pchar))*5, "shipRank");
			action = SF_AddAction("b_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("b_c", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("b_d", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_GYMNAST));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_GYMNAST), SF_CONDITION_HERO_TYPE, HERO_TYPE_GYMNAST);
		break;
		case "c":
			action = SF_AddAction("c_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, int(officer.reputation.nobility), "Nobility" + "$" + officer.name);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_LEADERSHIP)/2, SKILL_LEADERSHIP);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_GRAPPLING)/2, SKILL_GRAPPLING);
			SF_SetChance(action, -GetSkillAfterPenalty(officer, SKILL_PISTOL)/2, SKILL_PISTOL);
			action = SF_AddAction("c_b", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_SHOOTER));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_SHOOTER), SF_CONDITION_HERO_TYPE, HERO_TYPE_SHOOTER);
			action = SF_AddAction("c_c", "", "", SF_Icon("story", "forward"));
		break;
		case "d":
			action = SF_AddAction("d_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_LEADERSHIP)/2, SKILL_LEADERSHIP + "$" + officer.name);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_GRAPPLING)/2, SKILL_GRAPPLING + "$" + officer.name);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_F_LIGHT)/3, SKILL_F_LIGHT + "$" + officer.name);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_FENCING)/3, SKILL_FENCING + "$" + officer.name);
			SF_SetChance(action, GetSkillAfterPenalty(officer, SKILL_F_HEAVY)/3, SKILL_F_HEAVY + "$" + officer.name);
			action = SF_AddAction("d_b", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_ACCOUNTANT));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_ACCOUNTANT), SF_CONDITION_HERO_TYPE, HERO_TYPE_ACCOUNTANT);
			action = SF_AddAction("d_c", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("d_c", "", "", SF_Icon("story", "forward"));
		break;
		case "e":
			action = SF_AddAction("e_a", "", "", SF_Icon("story", "forward"));
			SF_AddCondition(&action, int(pchar.money) >= 5000, SF_CONDITION_MONEY);
			action = SF_AddAction("e_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("e_c", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("e_d", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_ACCOUNTANT));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_ACCOUNTANT), SF_CONDITION_HERO_TYPE, HERO_TYPE_ACCOUNTANT);
		break;
	}

	RE_SetEventDelay(120);
}

void OfficerRequestBad_Node0_a_a_action()
{
	if (SF_PerformCheck())
	{
		SF_Triumph("a_a");
		SF_AddEffect(SF_E_LOYALITY, officer, 2);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_GRAPPLING, 60.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 30.0);
		SF_AddEffect(SF_E_MORALE, pchar, 10, true);
		return;
	}

	SF_AddEffect(SF_E_LOYALITY, officer, -2);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_GRAPPLING, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 15.0);
	SF_AddEffect(SF_E_MORALE, pchar, -10, true);
	SF_Fail("a_a");
}

void OfficerRequestBad_Node0_a_b_action()
{
	string jobName = GetMainJob(officer);
	if (jobName == JOB_FIGHTER)
	{
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, 20.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, 20.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 20.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, 20.0);
	}
	else
	{
		string skillname = GetSkillNameByJob(jobName);
		if (jobName == JOB_CANNONER)
		{
			SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_CANNONS, 50.0);
			SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_ACCURACY, 50.0);
		}
		else SF_AddEffect(SF_E_SKILL_EXP, pchar, skillname, 100.0);
	}

	SF_AddEffect(SF_E_MONEY, pchar, -10000);
	SF_AddEffect(SF_E_LOYALITY, officer, 2);
	SF_Triumph("a_b");
}

void OfficerRequestBad_Node0_a_c_action()
{
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", -15);
	SF_AddEffect(SF_E_LOYALITY, officer, -2);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 50);
	SF_AddEffect(SF_E_MORALE, pchar, 20, true);
	SF_AddEffect(SF_E_TEMP_MODIFIER, pchar, M_SQUADRON_POWER, 0.20, "OfficerRequestBad", 30);
	CT_UpdateCashTables(pchar);

	aref achievement = GetAref(&RandEventSystem, "achievments.a212", true);
	achievement.OfficerRequestBad_Node0_a_c_action = true;
	if (GetAttributesNum(achievement > 3)) Achievment_Set("ach_CL_212");
	SF_Triumph("a_c");
}

void OfficerRequestBad_Node0_b_a_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_LOYALITY, officer, -1);
		SF_AddEffect(SF_E_MORALE, pchar, 30, true);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 30);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 30);
		SF_Triumph("b_a");
		return;
	}

	SF_AddEffect(SF_E_LOYALITY, officer, -1);
	SF_AddEffect(SF_E_MORALE, pchar, -20, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 15);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 15);
	SF_Fail("b_a");
}

void OfficerRequestBad_Node0_b_b_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, 3);
	SF_AddEffect(SF_E_MORALE, pchar, -30, true);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_GRAPPLING, 60.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_DEFENCE, 60.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_CANNONS, 60.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_CANNONS, 30.0);
	SF_Triumph("b_b");
}

void OfficerRequestBad_Node0_b_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, -3);
	SF_AddEffect(SF_E_MORALE, pchar, 30, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 100.0);

	SF_Triumph("b_c");
}

void OfficerRequestBad_Node0_b_d_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, -3);
	SF_AddEffect(SF_E_MORALE, pchar, 40, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 150.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_HEAVY, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_FENCING, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_LIGHT, 50.0);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Soldiers", 20);
	SF_Triumph("b_d");
}

void OfficerRequestBad_Node0_c_a_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_LOYALITY, officer, 2);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_LEADERSHIP, 100.0);
		SF_AddEffect(SF_E_MORALE, pchar, 10, true);
		SF_Triumph("c_a");
		return;
	}

	SF_AddEffect(SF_E_LOYALITY, officer, -2);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_LEADERSHIP, 50.0);
	SF_AddEffect(SF_E_MORALE, pchar, -10, true);
	SF_Fail("c_a");
}

void OfficerRequestBad_Node0_c_b_action()
{
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 40.0);
	SF_AddEffect(SF_E_MORALE, pchar, 20, true);
	SF_AddEffect(SF_E_LOYALITY, officer, 2);
	SF_Triumph("c_b");
}

void OfficerRequestBad_Node0_c_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, 1);
	SF_AddEffect(SF_E_MORALE, pchar, 10, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 40.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_GRAPPLING, 50.0);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Soldiers", 40);
	SF_Triumph("c_c");
}


void OfficerRequestBad_Node0_d_a_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_LOYALITY, officer, 1);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 80.0);
		SF_AddEffect(SF_E_CREW_EXP, pchar, "Soldiers", 10);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_GRAPPLING, 45.0);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_LEADERSHIP, 45.0);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_LIGHT, 10.0);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_FENCING, 10.0);
		SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_HEAVY, 10.0);
		SF_Triumph("d_a");
		return;
	}
	
	SF_AddEffect(SF_E_LOYALITY, officer, -1);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_GRAPPLING, 15.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_LEADERSHIP, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_LIGHT, 5.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_FENCING, 5.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_HEAVY, 5.0);
	SF_Fail("d_a");
}

void OfficerRequestBad_Node0_d_b_action()
{
	SF_AddEffect(SF_E_ITEMS, pchar, "gold_dublon", 200);
	SF_AddEffect(SF_E_LOYALITY, officer, 1);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_COMMERCE, 25.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_LEADERSHIP, 25.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_GRAPPLING, 25.0);
	SF_Triumph("d_b");
}

void OfficerRequestBad_Node0_d_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, 2);
	SF_AddEffect(SF_E_MORALE, pchar, -10, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 20.0);
	SF_Triumph("d_c");
}

void OfficerRequestBad_Node0_d_d_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, -2);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_LIGHT, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_FENCING, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_F_HEAVY, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, officer, SKILL_GRAPPLING, 100.0);
	SF_AddEffect(SF_E_MORALE, pchar, 10, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 50.0);
	SF_Triumph("d_d");
}

void OfficerRequestBad_Node0_e_a_action()
{
	SF_AddEffect(SF_E_MONEY, pchar, -5000);
	SF_AddEffect(SF_E_LOYALITY, officer, 2);
	SF_AddEffect(SF_E_MORALE, pchar, 10, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 30.0);
	SF_Triumph("e_a");
}

void OfficerRequestBad_Node0_e_b_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, 3);
	SF_AddEffect(SF_E_MORALE, pchar, -10, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 30.0);
	SF_Triumph("e_b");
}

void OfficerRequestBad_Node0_e_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officer, -1);
	SF_AddEffect(SF_E_MORALE, pchar, 20, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 20.0);
	SF_Triumph("e_c");
}

void OfficerRequestBad_Node0_e_d_action()
{
	SF_AddEffect(SF_E_MONEY, pchar, 5000);
	SF_AddEffect(SF_E_LOYALITY, officer, -1);
	SF_AddEffect(SF_E_MORALE, pchar, -10, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 10.0);
	SF_Triumph("e_d");
}

void OfficerRequestBad_Node0_Triumph()
{
	storyObject.exit = true;
}

void OfficerRequestBad_Node0_Fail()
{
	storyObject.exit = true;
}
