#include "story_frames\StealthCheck\helpers.c"
#include "story_frames\StealthCheckNight\Node1.c"
#include "story_frames\StealthCheckNight\Node2.c"
#include "story_frames\StealthCheckNight\Node3.c"

void StealthCheckNight_Node0()
{
	storyObject.title = SF_Convert("title");

	aref situation;
	makearef(situation, storyObject.situation);

	// вход через порт или через ворота
	if (context.entryPoint == "Port") situation.a.a = 100;
	else situation.a.b = 100;

	situation.b.a = 50;
	situation.b.b = 50;
	situation.c.a = 50;
	situation.c.b = 50;
	situation.d = 100;
	SF_ResolveSituation(&situation);

	// Пройти переулками
	action = SF_AddAction("a", "", "", SF_Icon("skill", SKILL_SNEAK));

	// Пройти крупными улицами
	action = SF_AddAction("b", "", "", SF_Icon("skill", SKILL_LEADERSHIP));

	// Вернуться, пока не поздно
	action = SF_AddAction("c", "", "", SF_Icon("story", "fail"));
}

// Пройти переулками
void StealthCheckNight_Node0_a_action()
{
	SF_SwitchNode("Node1");
}

// Пройти крупными улицами
void StealthCheckNight_Node0_b_action()
{
	SF_SwitchNode("Node2");
}

// Вернуться, пока не поздно
void StealthCheckNight_Node0_c_action()
{
	storyObject.exit = true;
	STH_SetColonyEnemy(storyObject.context.colonyId, 1);
}
