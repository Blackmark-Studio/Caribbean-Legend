#include "story_frames\RandomEvents\helpers.c"
#include "story_frames\RandomEvents\BadLand\condition.c"
int enemyNation;

void BadLand_Node0()
{
	PlaySound("interface\" + LanguageGetLanguage() + "\_GTTown2.wav");
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
	enemyNation = int(context.enemyNation);
	SF_ResolveSituation(&situation);

	switch (situation.a)
	{
		case "a":
			action = SF_AddAction("a_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP)/2, SKILL_LEADERSHIP);
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_FORTUNE)/2, SKILL_FORTUNE);
			SF_SetChance(action, sti(pchar.questTemp.Indian.relation)-50, "relationshipIndians");
			action = SF_AddAction("a_b", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, -(sti(pchar.questTemp.Indian.relation)-50), "relationshipIndians");
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_GRAPPLING)/2, SKILL_GRAPPLING);
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_PISTOL)/2, SKILL_PISTOL);
			action = SF_AddAction("a_c", "", "", SF_Icon("story", "forward"));
			SF_AddCondition(&action, BadLandHasTreasures(action), SF_CONDITION_CUSTOM, SF_Convert("MissingTreasures"));
		break;
		case "b":
			action = SF_AddAction("b_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_GRAPPLING)/2, SKILL_GRAPPLING);
			if (CheckOfficersPerkEnable("MusketsShoot")) SF_SetChance(action, 20, "MusketsShoot");
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP)*3, SKILL_LEADERSHIP);
			action = SF_AddAction("b_b", "", "", SF_Icon("money"));
			SF_AddCondition(&action, int(pchar.money) >= 20000, SF_CONDITION_MONEY);
			action = SF_AddAction("b_c", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_GYMNAST));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_GYMNAST), SF_CONDITION_HERO_TYPE, HERO_TYPE_GYMNAST);
		break;
		case "c":
			action = SF_AddAction("c_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP)/2, SKILL_LEADERSHIP);
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_FORTUNE)/2, SKILL_FORTUNE);
			SF_SetChance(action, ChangeCharacterNationReputation(pchar, enemyNation, 0), "relationship" + enemyNation); // отношения с нацией
			action = SF_AddAction("c_b", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_SHOOTER));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_SHOOTER), SF_CONDITION_HERO_TYPE, HERO_TYPE_SHOOTER);
			action = SF_AddAction("c_c", "", "", SF_Icon("story", "forward"));
			break;
	}

	RE_SetEventDelay(120);
}

void BadLand_Node0_a_a_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 60.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 30.0);
		SF_AddEffect(SF_E_MORALE, pchar, 30);
		SF_AddEffect(SF_E_FRACTION_RELATION, "Indian", 10);
		SF_Triumph("a_a");
		return;
	}

	SF_AddEffect(SF_E_CREW_QTY, pchar, -(20+SF_Rand(10)));
	SF_AddEffect(SF_E_MORALE, pchar, -20);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 40.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 30.0);
	SF_AddEffect(SF_E_FRACTION_RELATION, "Indian", -5);
	SF_Fail("a_a");
}


void BadLand_Node0_a_b_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 200.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, 100.0);
		SF_AddEffect(SF_E_MORALE, pchar, 30);
		SF_AddEffect(SF_E_FRACTION_RELATION, "Indian", -10);
		SF_Triumph("a_b");
		return;
	}

	SF_AddEffect(SF_E_CREW_QTY, pchar, -(25+SF_Rand(15)));
	SF_AddEffect(SF_E_MORALE, pchar, -20);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 150.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, 80.0);
	SF_AddEffect(SF_E_FRACTION_RELATION, "Indian", -5);
	SF_Fail("a_b");
}

void BadLand_Node0_a_c_action()
{
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 200.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 100.0);
	SF_AddEffect(SF_E_MORALE, pchar, 30);
	SF_AddEffect(SF_E_FRACTION_RELATION, "Indian", 15);
	BadLandTakeTreasures();
	SF_Triumph("a_c");
}


void BadLand_Node0_b_a_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_CREW_QTY, pchar, -(10+SF_Rand(10)));
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 30.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 15.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, 15.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, 15.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, 15.0);
		SF_AddEffect(SF_E_MORALE, pchar, 10);
		SF_Triumph("b_a");
		return;
	}

	SF_AddEffect(SF_E_CREW_QTY, pchar, -(20+SF_Rand(15)));
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 15.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, 20.0);
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_Fail("b_a");
}

void BadLand_Node0_b_b_action()
{
	SF_AddEffect(SF_E_MONEY, pchar, -20000);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 15.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 20.0);
	SF_AddEffect(SF_E_MORALE, pchar, -20);
	SF_Triumph("b_b");
}

void BadLand_Node0_b_c_action()
{
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, 30.0);
	SF_AddEffect(SF_E_MORALE, pchar, 20);
	SF_Triumph("b_c");
}

void BadLand_Node0_c_a_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 15.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_REPAIR, 70.0);
		SF_AddEffect(SF_E_MORALE, pchar, 10);
		SF_AddEffect(SF_E_NATION_RELATION, pchar, enemyNation, 3);
		SF_Triumph("c_a");
		return;
	}

	SF_AddEffect(SF_E_CREW_QTY, pchar, -(10+SF_Rand(10)));
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_CANNONS, 15.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_SAILING, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_REPAIR, 50.0);
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_Fail("c_a");
}

void BadLand_Node0_c_b_action()
{
	SF_AddEffect(SF_E_CREW_QTY, pchar, -(20+SF_Rand(15)));
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 30.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_CANNONS, 15.0);
	SF_AddEffect(SF_E_MORALE, pchar, 20);
	SF_Triumph("c_b");
}

void BadLand_Node0_c_c_action()
{
	SF_AddEffect(SF_E_CREW_QTY, pchar, -(30+SF_Rand(15)));
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 15.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_REPAIR, 45.0);
	SF_AddEffect(SF_E_MORALE, pchar, -20);
	SF_Triumph("c_c");
}

void BadLand_Node0_Triumph()
{
	storyObject.exit = true;
}

void BadLand_Node0_Fail()
{
	storyObject.exit = true;
}

void BadLandTakeTreasures()
{
	aref itemTreasures = GetAref(&StoryObject, "itemTreasures", true);
	int treasuresQty = GetAttributesNum(itemTreasures);
	for (int i = 0; i < treasuresQty; i++)
	{
		aref item = GetAttributeN(itemTreasures, i);
		SF_AddEffect(SF_E_ITEMS_CABIN, GetAttributeName(item), -int(GetAttributeValue(item)));
	}
}

bool BadLandHasTreasures(aref link)
{
	bool res = false;
	aref itemTreasures = GetAref(&StoryObject, "itemTreasures", true);

	string goodsIds[16] = {"Mineral6", "jewelry24", "jewelry25", "jewelry26", "jewelry27", "jewelry28", "jewelry29", "jewelry40", "jewelry41", "jewelry42", "jewelry43", "jewelry44", "jewelry45", "jewelry46", "jewelry47", "jewelry48", "jewelry49"};

	int qtyToTake = 10;

	for (int i = 0; i < 16; i++)
	{
		string itemId = goodsIds[i];
		int qty = func_min(qtyToTake, PCharItemsTotal(itemId));
		qtyToTake -= qty;
		itemTreasures.(itemId) = qty;
		if (qtyToTake != 0) continue;
		res = true; // набрали
		break;
	}

	aref linkAttribute = GetAref(&link, "itemTreasures", true);
	CopyAttributes(&linkAttribute, &itemTreasures); // для дебага
	return res;
}