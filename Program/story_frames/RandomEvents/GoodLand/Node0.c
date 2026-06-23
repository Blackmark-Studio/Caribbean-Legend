#include "story_frames\RandomEvents\helpers.c"
#include "story_frames\RandomEvents\GoodLand\condition.c"

void GoodLand_Node0()
{
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvLand1.wav");
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
	SF_ResolveSituation(&situation);

	switch (situation.a)
	{
		case "a":
			action = SF_AddAction("a_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, 20, "base");
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_SAILING)/2, SKILL_SAILING);
			SF_SetChance(action, 8-GetCharacterShipClass(pchar)*7, "shipRank");
			action = SF_AddAction("a_b", "", "", SF_Icon("perk", "CoordinatedBoarding"));
			SF_AddCondition(&action, HasPerk(pchar, "CoordinatedBoarding"), SF_CONDITION_PERK, "CoordinatedBoarding");
			action = SF_AddAction("a_c", "", "", SF_Icon("story", "forward"));
		break;
		case "b":
			action = SF_AddAction("b_a", "", "", SF_Icon("story", "random"));
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_GRAPPLING)/3, SKILL_GRAPPLING);
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_FORTUNE)/2, SKILL_FORTUNE);
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_SNEAK)/2, SKILL_SNEAK);
			action = SF_AddAction("b_b", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_SHOOTER));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_SHOOTER), SF_CONDITION_HERO_TYPE, HERO_TYPE_SHOOTER);
			action = SF_AddAction("b_c", "", "", SF_Icon("story", "forward"));
		break;
		case "c":
			action = SF_AddAction("c_a", "", "", SF_Icon("money"));
			SF_AddCondition(&action, int(pchar.money) >= 3000, SF_CONDITION_MONEY);
			action = SF_AddAction("c_b", "", "", SF_Icon("story", "forward"));
			action = SF_AddAction("c_c", "", "", SF_Icon("story", "forward"));
		break;
		case "d":
			action = SF_AddAction("d_a", "", "", SF_Icon("story", "random"));
			SF_AddCondition(&action, GoodLandHasTreasures(action), SF_CONDITION_CUSTOM, SF_Convert("MissingTreasures"));
			SF_SetChance(action, int(pchar.questTemp.Indian.relation)-50, "relationshipIndians");
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_COMMERCE)/3, SKILL_COMMERCE);
			SF_SetChance(action, GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP)/2, SKILL_LEADERSHIP);

			action = SF_AddAction("d_b", "", "", SF_Icon(HERO_TYPE, HERO_TYPE_SHOOTER));
			SF_AddCondition(&action, HasPerk(pchar, HERO_TYPE_SHOOTER), SF_CONDITION_HERO_TYPE, HERO_TYPE_SHOOTER);
			action = SF_AddAction("d_c", "", "", SF_Icon("story", "forward"));
		break;
	}

	RE_SetEventDelay(120);
}

void GoodLand_Node0_a_a_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_MONEY, pchar, 5000+SF_Rand(5000));
		SF_AddEffect(SF_E_ITEMS, pchar, "gold_dublon", 100+SF_Rand(100));
		SF_AddEffect(SF_E_ITEMS, pchar, "jewelry2", 20+SF_Rand(30));
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_SAILING, 30.0);
		SF_Triumph("a_a");
		return;
	}

	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_SAILING, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_REPAIR, 70.0);
	SF_Fail("a_a");
}

void GoodLand_Node0_a_b_action()
{
	SF_AddEffect(SF_E_MONEY, pchar, 10000+SF_Rand(5000));
	SF_AddEffect(SF_E_ITEMS, pchar, "gold_dublon", 150+SF_Rand(100));
	SF_AddEffect(SF_E_ITEMS, pchar, "jewelry2", 20+SF_Rand(30));
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_SAILING, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 40.0);
	SF_Triumph("a_b");
}

void GoodLand_Node0_a_c_action()
{
	// Тут тоже пуфто
	SF_Triumph("a_c");
}

void GoodLand_Node0_b_a_action()
{
	if (SF_PerformCheck())
	{
		SF_AddEffect(SF_E_GOODS, pchar, GOOD_COFFEE, 70);
		SF_AddEffect(SF_E_GOODS, pchar, GOOD_TOBACCO, 50);
		SF_AddEffect(SF_E_GOODS, pchar, GOOD_SHIPSILK, 40);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 30.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_SNEAK, 30.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 30.0);
		SF_Triumph("b_a");
		return;
	}

	SF_AddEffect(SF_E_CREW_QTY, pchar, -(10 + SF_Rand(5)));
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_SHIPSILK, 15);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_SNEAK, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FORTUNE, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 40.0);
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_Fail("b_a");
}

void GoodLand_Node0_b_b_action()
{
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_COFFEE, 100);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_TOBACCO, 100);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_SHIPSILK, 50);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_CANNONS, 30.0);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Cannoners", 10.0);
	SF_AddEffect(SF_E_MORALE, pchar, 10);
	SF_Triumph("b_b");
}

void GoodLand_Node0_b_c_action()
{
	// Тут тоже пуфто
	SF_Triumph("b_c");
}

void GoodLand_Node0_c_a_action()
{
	SF_AddEffect(SF_E_MONEY, pchar, -3000);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_FOOD, 300);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 30.0);
	SF_AddEffect(SF_E_MORALE, pchar, 10);
	SF_Triumph("c_a");
}

void GoodLand_Node0_c_b_action()
{
	SF_AddEffect(SF_E_MORALE, pchar, 20);
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_FOOD, 500);
	SF_Triumph("c_b");
}

void GoodLand_Node0_c_c_action()
{
	// Тут тоже пуфто
	SF_Triumph("c_c");
}

void GoodLand_Node0_d_a_action()
{
	if (SF_PerformCheck())
	{
		SF_Triumph("d_a");
		GoodLand_TakeTreasures();
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 30.0);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 20.0);
		SF_AddEffect(SF_E_FRACTION_RELATION, "Indian", 5);
		SF_AddEffect(SF_E_GOODS, pchar, GOOD_SANDAL, 20);
		return;
	}

	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_LEADERSHIP, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_COMMERCE, 10.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 40.0);
	SF_AddEffect(SF_E_FRACTION_RELATION, "Indian", -3);
	SF_AddEffect(SF_E_MORALE, pchar, -10);
	SF_Fail("d_a");
}

void GoodLand_Node0_d_b_action()
{
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_GRAPPLING, 50.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, 20.0);
	SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_CANNONS, 10.0);
	SF_AddEffect(SF_E_CREW_EXP, pchar, "Soldiers", 20.0);
	SF_AddEffect(SF_E_CREW_QTY, pchar, -(15 + SF_Rand(15)));
	SF_AddEffect(SF_E_GOODS, pchar, GOOD_SANDAL, 60);
	SF_Triumph("d_b");
}

void GoodLand_Node0_d_c_action()
{
	// Тут тоже пуфто
	SF_Triumph("d_c");
}

void GoodLand_Node0_Triumph()
{
	storyObject.exit = true;
}

void GoodLand_Node0_Fail()
{
	storyObject.exit = true;
}

void GoodLand_TakeTreasures()
{
	aref itemTreasures = GetAref(&StoryObject, "itemTreasures", true);
	int treasuresQty = GetAttributesNum(itemTreasures);
	for (int i = 0; i < treasuresQty; i++)
	{
		aref item = GetAttributeN(itemTreasures, i);
		SF_AddEffect(SF_E_ITEMS_CABIN, GetAttributeName(item), -int(GetAttributeValue(item)));
	}
}

bool GoodLandHasTreasures(aref link)
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