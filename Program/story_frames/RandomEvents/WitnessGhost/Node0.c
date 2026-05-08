#include "story_frames\RandomEvents\helpers.c"
#include "story_frames\RandomEvents\WitnessGhost\condition.c"

void WitnessGhost_Node0()
{
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy0.wav");
	SF_InitModule("RandomEvents");
	storyObject.icon.group = "SEASONS_ICONS";
	storyObject.icon.picture = "stories";
	aref situation;
	makearef(situation, storyObject.situation);
	if (!SF_InitConditions(&context, &situation, true))
	{
		SF_ExitButton("The conditions of the story " + StoryObject.name + " are not fulfilled");
		return;
	}
	SF_ResolveSituation(&situation);

	switch (situation.a)
	{
		case "a":
			storyObject.title = SF_Convert("title_a");
			action = SF_AddAction("a_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("a_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("a_c", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("a_d", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_SHOOTER));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_SHOOTER), SF_CONDITION_HERO_TYPE, HERO_TYPE_SHOOTER);
		break;
		case "b":
			storyObject.title = SF_Convert("title_b");
			action = SF_AddAction("b_a", "", "", SF_Icon("item", "greenIdol"));
			action = SF_AddAction("b_b", "", "", SF_Icon("story", "forward"));
		break;
		case "c":
			storyObject.title = SF_Convert("title_c");
			action = SF_AddAction("c_a", "", "", SF_Icon("item", "hat12"));
			action = SF_AddAction("c_b", "", "", SF_Icon("story", "forward"));
		break;
		case "d":
			storyObject.title = SF_Convert("title_d");
			action = SF_AddAction("d_a", "", "", SF_Icon("item", "blade_34"));
			action = SF_AddAction("d_b", "", "", SF_Icon("story", "forward"));
		break;
	}

	RE_SetEventDelay(120);
}

void WitnessGhost_Node0_a_a_action()
{
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 100.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 80.0);
	SF_AddEffect(SF_E_MORALE, pchar, 30, true);
	SF_Triumph("a_a");
}

void WitnessGhost_Node0_a_b_action()
{
	SF_AddEffect(SF_E_CREW_QTY, pchar, -15);
	SF_AddEffect(SF_E_MORALE, pchar, -20, true);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 70.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_REPAIR, 70.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_SAILING, 70.0);
	SF_Triumph("a_b");
}

void WitnessGhost_Node0_a_c_action()
{
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_SAILING, 150.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 100.0);
	SF_AddEffect(SF_E_MORALE, pchar, 10, true);
	SF_Triumph("a_c");
}

void WitnessGhost_Node0_a_d_action()
{
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_CANNONS, 100.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_ACCURACY, 80.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 70.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 60.0);
	SF_AddEffect(SF_E_MORALE, pchar, 20, true);
	SF_Triumph("a_d");
}

void WitnessGhost_Node0_b_a_action()
{
	SF_Triumph("b_a");
	SF_AddEffect(SF_E_ITEMS, pchar, "greenIdol", 1);
	DeleteAttribute(&RandEventSystem, "greenIdolNotGiven");
	Achievment_Set("ach_CL_210");
}

void WitnessGhost_Node0_b_b_action()
{
	RE_SetEventDelay(365);
	SF_Triumph("b_b");
}

void WitnessGhost_Node0_c_a_action()
{
	SF_AddEffect(SF_E_ITEMS, pchar, "hat12", 1);
	DeleteAttribute(&RandEventSystem, "hat12NotGiven");
	Achievment_Set("ach_CL_208");
	SF_Triumph("c_a");
}

void WitnessGhost_Node0_c_b_action()
{
	RE_SetEventDelay(365);
	SF_Triumph("c_b");
}

void WitnessGhost_Node0_d_a_action()
{
	SF_AddEffect(SF_E_ITEMS, pchar, "blade_34", 1);
	DeleteAttribute(&RandEventSystem, "blade_34NotGiven");
	Achievment_Set("ach_CL_209");
	SF_Triumph("d_a");
}

void WitnessGhost_Node0_d_b_action()
{
	RE_SetEventDelay(365);
	SF_Triumph("d_b");
}

void WitnessGhost_Node0_Triumph()
{
	storyObject.exit = true;
}

void WitnessGhost_Node0_Fail()
{
	storyObject.exit = true;
}
