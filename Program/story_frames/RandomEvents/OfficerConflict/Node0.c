#include "story_frames\RandomEvents\helpers.c"
#include "story_frames\RandomEvents\OfficerConflict\condition.c"
ref officer, officerA, officerB, prisoner;

void OfficerConflict_Node0()
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

	officerA = CharacterFromIDSafe(context.officerIdx_A);
	officerB = CharacterFromIDSafe(context.officerIdx_B);
	context.officerName_A = officerA.name;
	context.officerName_B = officerB.name;
	context.officerJob_A = GetMainJob(officerA);
	context.officerJob_B = GetMainJob(officerB);
	if (CheckAttribute(context, "prisonerId")) prisoner = CharacterFromIDSafe(context.prisonerId);
	Log_TestInfo("officerA: " + context.officerIdx_A);
	Log_TestInfo("officerB: " + context.officerIdx_B);
	if (CheckAttribute(context, "prisonerId")) Log_TestInfo("prisoner: " + context.prisonerName);

	SF_ResolveSituation(&situation);

	switch (situation.a)
	{
		case "a":
			action = SF_AddAction("a_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("a_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("a_c", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("a_d", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_ACCOUNTANT));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_ACCOUNTANT), SF_CONDITION_HERO_TYPE, HERO_TYPE_ACCOUNTANT);
		break;
		case "b":
			action = SF_AddAction("b_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("b_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("b_c", "", "", SF_Icon("story", "forward"));
		break;
		case "c":
			action = SF_AddAction("c_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("c_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("c_c", "", "", SF_Icon("story", "forward"));
		break;
		case "d":
			action = SF_AddAction("d_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("d_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("d_c", "", "", SF_Icon("story", "forward"));
		break;
		case "e":
			action = SF_AddAction("e_a", "", "", SF_Icon("story", "forward"));
			SF_AddCondition(&action, int(pchar.money) >= 5000, SF_CONDITION_MONEY);
			action = SF_AddAction("e_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("e_c", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("e_d", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("e_e", "", "", SF_Icon("story", "forward"));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_GYMNAST), SF_CONDITION_HERO_TYPE, HERO_TYPE_GYMNAST);
		break;
	}

	RE_SetEventDelay(120);
}


void OfficerConflict_Node0_a_a_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, 2);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 50.0);
	SF_Triumph("a_a");
}

void OfficerConflict_Node0_a_b_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, 2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 50.0);
	SF_Triumph("a_b");
}

void OfficerConflict_Node0_a_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 50.0);
	SF_Triumph("a_c");
}

void OfficerConflict_Node0_a_d_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_REPAIR, 125.0);
	SF_Triumph("a_d");
}

void OfficerConflict_Node0_b_a_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, 2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_LearnSkillsFromOfficer(officerA, 40.0);
	SF_Triumph("b_a");
}

void OfficerConflict_Node0_b_b_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, 2);
	SF_LearnSkillsFromOfficer(officerB, 40.0);
	SF_Triumph("b_b");
}

void OfficerConflict_Node0_b_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_LearnSkillsFromOfficer(officerA, 40.0);
	SF_LearnSkillsFromOfficer(officerB, 40.0);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Sailors", 10.0);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Cannoners", 10.0);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Soldiers", 10.0);
	SF_Triumph("b_c");
}

void OfficerConflict_Node0_c_a_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, 2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_LearnSkillsFromOfficer(officerA, 40.0);
	prisoner.bonusCost = SF_ChanceLock(50) ? 2.0 : 0.5;
	SF_Triumph("c_a");
}

void OfficerConflict_Node0_c_b_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, 2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_LearnSkillsFromOfficer(officerA, 40.0);
	prisoner.bonusCost = 1.25;
	SF_Triumph("c_b");
}


void OfficerConflict_Node0_c_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_LearnSkillsFromOfficer(officerA, 40.0);
	SF_LearnSkillsFromOfficer(officerB, 40.0);
	SF_AddEffect(SF_E_MORALE, pchar, 10, true);
	SF_AddEffect(SF_E_TEMP_MODIFIER, pchar, M_SQUADRON_POWER, 0.30, "OfficerConflict", 30);
	SF_Triumph("c_c");
	aref achievement = GetAref(&RandEventSystem, "achievments.a212", true);
	achievement.OfficerConflict_Node0_c_c_action = true;
	if (GetAttributesNum(achievement > 3)) Achievment_Set("ach_CL_212");
}

void OfficerConflict_Node0_d_a_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, 2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_LearnSkillsFromOfficer(officerA, 40.0);
	SF_AddEffect(SF_E_SKILL_EXP, officerA, SKILL_LEADERSHIP, 200.0);
	SF_Triumph("d_a");
}

void OfficerConflict_Node0_d_b_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, 2);
	SF_LearnSkillsFromOfficer(officerB, 40.0);
	SF_AddEffect(SF_E_SKILL_EXP, officerB, SKILL_LEADERSHIP, 200.0);
	SF_Triumph("d_b");
}

void OfficerConflict_Node0_d_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_AddEffect(SF_E_SKILL_EXP, officerB, SKILL_LEADERSHIP, 150.0);
	SF_LearnSkillsFromOfficer(officerA, 40.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 40.0);
	SF_Triumph("d_c");
}

void OfficerConflict_Node0_e_a_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, 2);
	SF_AddEffect(SF_E_LOYALITY, officerB, 2);
	SF_LearnSkillsFromOfficer(officerA, 40.0);
	SF_LearnSkillsFromOfficer(officerB, 40.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 50.0);
	SF_Triumph("e_a");
}

void OfficerConflict_Node0_e_b_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, 2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_LearnSkillsFromOfficer(officerA, 40.0);
	SF_Triumph("e_b");
}

void OfficerConflict_Node0_e_c_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, 2);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 40.0);
	SF_Triumph("e_c");
}

void OfficerConflict_Node0_e_d_action()
{
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_LOYALITY, officerB, -2);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 300.0);
	SF_AddEffect(SF_E_MORALE, pchar, 20, true);
	SF_AddEffect(SF_E_TEMP_MODIFIER, pchar, M_SQUADRON_POWER, 0.30, "OfficerConflict", 30);
	SF_Triumph("e_d");
}

void OfficerConflict_Node0_e_e_action()
{

	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_LOYALITY, officerA, 2);
		SF_AddEffect(SF_E_SKILL_EXP, officerA, SKILL_F_LIGHT, 50.0);
		SF_AddEffect(SF_E_SKILL_EXP, officerA, SKILL_FENCING, 50.0);
		SF_AddEffect(SF_E_SKILL_EXP, officerA, SKILL_F_HEAVY, 50.0);
		SF_AddEffect(SF_E_LOYALITY, officerB, -2);
		SF_AddEffect(SF_E_SKILL_EXP, officerB, SKILL_F_LIGHT, 30.0);
		SF_AddEffect(SF_E_SKILL_EXP, officerB, SKILL_FENCING, 30.0);
		SF_AddEffect(SF_E_SKILL_EXP, officerB, SKILL_F_HEAVY, 30.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 100.0);
		SF_Triumph("e_e");
		return;
	}

	SF_AddEffect(SF_E_LOYALITY, officerB, 2);
	SF_AddEffect(SF_E_SKILL_EXP, officerB, SKILL_F_LIGHT, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, officerB, SKILL_FENCING, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, officerB, SKILL_F_HEAVY, 50.0);
	SF_AddEffect(SF_E_LOYALITY, officerA, -2);
	SF_AddEffect(SF_E_SKILL_EXP, officerA, SKILL_F_LIGHT, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, officerA, SKILL_FENCING, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, officerA, SKILL_F_HEAVY, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 100.0);
	SF_Fail("e_e");
}

void OfficerConflict_Node0_Triumph()
{
	storyObject.exit = true;
}

void OfficerConflict_Node0_Fail()
{
	storyObject.exit = true;
}
