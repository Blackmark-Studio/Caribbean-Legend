#include "story_frames\RandomEvents\helpers.c"
#include "story_frames\RandomEvents\SeaMeeting\condition.c"
ref storyPassenger;
int storyNation;

void SeaMeeting_Node0()
{
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvShip1.wav");
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

	storyNation = int(context.nation);
	context.enemyNation = FindEnemyNation2Nation(int(context.nation));
	context.shipname = generateRandomNameToShip(storyNation);
	storyPassenger = GetCharacterSafe(NPC_GeneratePhantomCharacter("citizen", storyNation, MAN, -1), true);
	ForceAutolevel(storyPassenger, GEN_TYPE_OFFICER, GEN_ELITE, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.5);
	context.cityA = GetQuestNationsCity(storyNation);
	ref cityB = GetColonyByIndex(FindNonEnemyColonyForAdventure(storyNation, context.cityA, true));
	context.cityB = cityB.id;
	context.passengerName = storyPassenger.name;

	SF_ResolveSituation(&situation);

	switch (situation.a)
	{
		case "a":
			action = SF_AddAction("a_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("a_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("a_c", "", "", SF_Icon("story", "forward"));
		break;
		case "b":
			action = SF_AddAction("b_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("b_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("b_c", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_ATHLETE));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_ATHLETE), SF_CONDITION_HERO_TYPE, HERO_TYPE_ATHLETE);
			action = SF_AddAction("b_d", "", "", SF_Icon("story", "forward"));
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
			action = SF_AddAction("d_b", "", "", SF_Icon("perk", "InstantRepair"));
			SF_AddCondition(&action, CheckOfficersPerkEnable("InstantRepair"), SF_CONDITION_PERK, "InstantRepair");
			action = SF_AddAction("d_c", "", "", SF_Icon("story", "forward"));
		break;
		case "e":
			action = SF_AddAction("e_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("e_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("e_c", "", "", SF_Icon("story", "forward"));
		break;
		case "f":
			action = SF_AddAction("f_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("f_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("f_c", "", "", SF_Icon("story", "forward"));
		break;
		case "g":
			action = SF_AddAction("g_a", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("g_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("g_c", "", "", SF_Icon("story", "forward"));
		break;
	}

	RE_SetEventDelay(120);
}


void SeaMeeting_Node0_a_a_action()
{
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_FOOD, -150);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 3);
	SF_AddEffect(SF_E_MORALE, pchar, 20);
	SF_Triumph("a_a");
}

void SeaMeeting_Node0_a_b_action()
{
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_FOOD, -150);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 1);
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_AddEffect(SF_E_MONEY, pchar, 5000);
	SF_Triumph("a_b");
}

void SeaMeeting_Node0_a_c_action()
{
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, -1);
	SF_AddEffect(SF_E_MORALE, pchar, -20);
	SF_Triumph("a_c");
}


void SeaMeeting_Node0_b_a_action()
{
	SF_AddEffect(SF_E_CREW_QTY, pchar, -(20+SF_Rand(10)));
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_MEDICAMENT, -200);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 4);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", 3.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 150.0);
	SF_AddEffect(SF_E_MORALE, pchar, -20);
	SF_Triumph("b_a");
}

void SeaMeeting_Node0_b_b_action()
{
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_MEDICAMENT, -50);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 1);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", 1.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 100.0);
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_Triumph("b_b");
}

void SeaMeeting_Node0_b_c_action()
{
	SF_AddEffect(SF_E_CREW_QTY, pchar, -(10+SF_Rand(5)));
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_MEDICAMENT, -150);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 3);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", 6.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 250.0);
	SF_AddEffect(SF_E_MORALE, pchar, 20);
	SF_Triumph("b_c");
}
void SeaMeeting_Node0_b_d_action()
{
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, -2);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", -3.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_DEFENCE, 100.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 100.0);
	SF_AddEffect(SF_E_MORALE, pchar, 10);
	SF_Triumph("b_d");
}

void SeaMeeting_Node0_c_a_action()
{
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_FOOD, -150);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_SLAVES, 50);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 1);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 50.0);
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_Triumph("c_a");
}

void SeaMeeting_Node0_c_b_action()
{
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_FOOD, -100);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 5);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 40.0);
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_Triumph("c_b");
}


void SeaMeeting_Node0_c_c_action()
{
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_FOOD, -250);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_SLAVES, 125);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 2);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 125.0);
	SF_AddEffect(SF_E_MORALE, pchar, -20);
	SF_Triumph("c_c");
}

void SeaMeeting_Node0_c_d_action()
{
	SF_AddEffect(SF_E_MORALE, pchar, 10);
	SF_AddEffect(SF_E_LOYALITY_ALL, 1);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 10.0);
	SF_Triumph("c_d");
}

void SeaMeeting_Node0_d_a_action()
{
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_SAILCLOTH, -50);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_EBONY, 50);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 3);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 40.0);
	SF_AddEffect(SF_E_MORALE, pchar, 10);
	SF_Triumph("d_a");
}

void SeaMeeting_Node0_d_b_action()
{
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_SAILCLOTH, -30);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_EBONY, 70);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 5);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_REPAIR, 40.0);
	SF_AddEffect(SF_E_MORALE, pchar, 20);
	SF_Triumph("d_b");
}

void SeaMeeting_Node0_d_c_action()
{
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_Triumph("d_c");
}

void SeaMeeting_Node0_e_a_action()
{
	SF_AddEffect(SF_E_ITEMS, pchar, "gold_dublon", 150);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 20.0);
	SF_Triumph("e_a");
}

void SeaMeeting_Node0_e_b_action()
{
	// Тут тоже пуфто...
	SF_Triumph("e_b");
}

void SeaMeeting_Node0_e_c_action()
{
	SF_AddEffect(SF_E_MORALE, pchar, -30);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", -10.0);
	SF_AddEffect(SF_E_TEMP_MODIFIER, pchar, M_SQUADRON_POWER, 0.80, "SeaMeeting", 30);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_ACCURACY, 30.0);
	SF_Triumph("e_c");
}

void SeaMeeting_Node0_f_a_action()
{

	SF_AddEffect(SF_E_MONEY, pchar, -10000);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_TOBACCO, 400);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 1);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 30.0);
	SF_Triumph("f_a");
}

void SeaMeeting_Node0_f_b_action()
{
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, -4);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 50.0);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_TOBACCO, 450);
	SF_AddEffect(SF_E_REPUTATION, pchar, "nobility", -3.0);
	SF_Triumph("f_b");
}

void SeaMeeting_Node0_f_c_action()
{
	// Тут тоже пуфто...
	SF_Triumph("f_c");
}

void SeaMeeting_Node0_g_a_action()
{
	SetCharToPrisoner(storyPassenger);
	SF_AddEffect(SF_E_CUSTOM, SF_Convert("PassengerImprisoned"), 1);
	SF_AddEffect(SF_E_ITEMS, pchar, "gold_dublon", 100);
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, 1);
	SF_Triumph("g_a");
}

void SeaMeeting_Node0_g_b_action()
{
	SF_AddEffect(SF_E_NATION_RELATION, pchar, storyNation, -1);
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_AddEffect(SF_E_TEMP_MODIFIER, pchar, M_SQUADRON_POWER, 0.20, "SeaMeeting", 30);
	aref achievement = GetAref(&RandEventSystem, "achievments.a212", true);
	achievement.SeaMeeting_Node0_g_b = true;
	if (GetAttributesNum(achievement > 3)) Achievment_Set("ach_CL_212");
	SF_Triumph("g_b");
}

void SeaMeeting_Node0_g_c_action()
{
	// Тут тоже пуфто...
	SF_Triumph("g_c");
}

void SeaMeeting_Node0_Triumph()
{
	storyObject.exit = true;
}

void SeaMeeting_Node0_Fail()
{
	storyObject.exit = true;
}
