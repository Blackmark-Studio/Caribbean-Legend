#include "story_frames\RandomEvents\helpers.c"
#include "story_frames\RandomEvents\Lover\condition.c"

void Lover_Node0()
{
	SF_InitModule("RandomEvents");
	PlaySound("interface\key.wav");
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
	SF_ResolveSituation(&situation);

	switch (situation.a)
	{
		case "a":
			action = SF_AddAction("a_a", "", "", SF_Icon("character", "life"));
			action = SF_AddAction("a_b", "", "", SF_Icon("character", "life"));
			action = SF_AddAction("a_c", "", "", SF_Icon("character", "life"));
			action = SF_AddAction("a_d", "", "", SF_Icon("character", "life"));
			action = SF_AddAction("a_e", "", "", SF_Icon("story", "forward"));
		break;
		case "b":
			action = SF_AddAction("b_a", "", "", SF_Icon("character", "life"));
			action = SF_AddAction("b_b", "", "", SF_Icon("character", "life"));
			action = SF_AddAction("b_c", "", "", SF_Icon("character", "life"));
			action = SF_AddAction("b_d", "", "", SF_Icon("story", "forward"));
		break;
	}

	RE_SetEventDelay(120);
}

void Lover_Node0_a_a_action()
{
	Lover_Cabin();
}

void Lover_Node0_a_b_action()
{
	Lover_Cabin();
}

void Lover_Node0_a_c_action()
{
	Lover_Cabin();
}

void Lover_Node0_a_d_action()
{
	Lover_Cabin();
}

void Lover_Node0_a_e_action()
{
	AddCharacterHealth(pchar, -15);
	storyObject.exit = true;
}

void Lover_Node0_b_a_action()
{
	Lover_Cabin();
}

void Lover_Node0_b_b_action()
{
	Lover_Cabin();
}

void Lover_Node0_b_c_action()
{
	Lover_Cabin();
}

void Lover_Node0_b_d_action()
{
	AddCharacterHealth(pchar, -15);
	storyObject.exit = true;
}

void Lover_Node0_Triumph()
{
	storyObject.exit = true;
}

void Lover_Node0_Fail()
{
	storyObject.exit = true;
}

void Lover_Cabin()
{
	storyObject.exit = true;
	storyObject.onClose.Lover_Cabin2 = true;
}