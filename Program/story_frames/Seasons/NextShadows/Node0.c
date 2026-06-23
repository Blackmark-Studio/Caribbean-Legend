#include "story_frames\Seasons\helpers.c"

void NextShadows_Node0()
{
	SetEventHandler("SF_ButtonWasPressed", "SZN_ButtonWasPressed", 1);
	if (bBettaTestMode) Log_Clear();
	SF_InitModule("Seasons");
	storyObject.title = SF_Convert("title");
	storyObject.icon.group = "SEASONS_ICONS";
	storyObject.icon.picture = StoryObject.context.seasonId;
	aref situation;
	makearef(situation, storyObject.situation);
	situation.a = 100;

	situation.b.a = 15;
	situation.b.b = 15;
	situation.b.c = 15;
	situation.b.d = 10;

	situation.c.a = 15;
	situation.c.b = 15;
	situation.c.c = 10;

	situation.d.a = 15;
	situation.d.b = 15;
	situation.d.c = 10;
	situation.d.d = 15;

	SF_ResolveSituation(&situation);

	SZN_IncreaseTempEffect(M_RECRUITS_MTP, -0.35);
	SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_COST, 0.80);
	SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_STOCK, -0.50);

	switch (situation.b)
	{
		case "a":
			SZN_IncreaseTempEffect(M_MEDICAMENT_CONSUMPTION, -0.15);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "Moonshiner"));
			SZN_SetReactionEffect(&reaction, M_MEDICAMENT_CONSUMPTION, -0.05);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("Moonshiner"), SF_CONDITION_PERK, "Moonshiner");
		break;
		case "b":
			SZN_IncreaseTempEffect(M_MEDICAMENT_CONSUMPTION, -0.25);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "Practice"));
			SZN_SetReactionEffect(&reaction, M_MEDICAMENT_CONSUMPTION, -0.05);
			SF_AddCondition(&reaction, HasPerk(pchar, "Practice"), SF_CONDITION_PERK, "Practice");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_RECRUITS_MTP, 0.10);
			SZN_IncreaseTempEffect(M_CREW_MORALE_MTP, 0.50);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "Gossip"));
			SZN_SetReactionEffect(&reaction, M_RECRUITS_MTP, 0.10);
			SF_AddCondition(&reaction, HasPerk(pchar, "Gossip"), SF_CONDITION_PERK, "Gossip");
		break;
		case "d":
			SZN_IncreaseTempEffect(M_RECRUITS_MTP, 0.15);
			SZN_IncreaseTempEffect(M_MEDICAMENT_CONSUMPTION, 0.25);
			reaction = SF_AddReaction("b", "", "", SF_Icon("perk", "HPPLUS"));
			SZN_SetReactionEffect(&reaction, M_MEDICAMENT_CONSUMPTION, -0.10);
			SF_AddCondition(&reaction, HasPerk(pchar, "HPPLUS"), SF_CONDITION_PERK, "HPPLUS");
		break;
	}

	switch (situation.c)
	{
		case "a":
			SZN_IncreaseTempEffect(M_REPAIR_COST, 0.60);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "Builder"))
			SZN_SetReactionEffect(&reaction, M_REPAIR_COST, -0.15);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("Builder"), SF_CONDITION_PERK, "Builder");
		break;
		case "b":
			SZN_IncreaseTempEffect(M_REPAIR_COST, 0.90);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "CriticalShoot"))
			SZN_SetReactionEffect(&reaction, M_REPAIR_COST, -0.15);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("CriticalShoot"), SF_CONDITION_PERK, "CriticalShoot");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_REPAIR_COST, 0.40);
			SZN_IncreaseTempEffect(M_SHIPYARD_CANNONS_STOCK, 0.25);
			SZN_SetTempEffect(M_BIG_CANNONS_AVAILABLE, true);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "Looting"));
			SZN_SetReactionEffect(&reaction, M_REPAIR_COST, -0.15);
			SF_AddCondition(&reaction, HasPerk(pchar, "Looting"), SF_CONDITION_PERK, "Looting");
		break;
	}

	switch (situation.d)
	{
		case "a":
			SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_COST, 1.50);
			SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_STOCK, -0.75);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "TradeConnections"));
			SZN_SetReactionEffect(&reaction, M_EUROPEAN_GOODS_COST, -0.75);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("TradeConnections"), SF_CONDITION_PERK, "TradeConnections");
		break;
		case "b":
			SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_COST, 2.50);
			SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_STOCK, -0.95);
			reaction = SF_AddReaction("d", "", "", SF_Icon("fractions", "smugglers"));
			SZN_SetReactionEffect(&reaction, M_EUROPEAN_GOODS_STOCK, 0.15);
			SF_AddCondition(&reaction, int(pchar.questTemp.Contraband.relation) > 70, SF_CONDITION_RELATIONS, "Smuggler");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_COST, 1.20);
			SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_STOCK, -0.45);
			SZN_IncreaseTempEffect(M_STOLEN_GOODS_MTP, -0.08);
			reaction = SF_AddReaction("d", "", "", SF_Icon(SKILL_TYPE, SKILL_COMMERCE));
			SZN_SetReactionEffect(&reaction, M_STOLEN_GOODS_MTP, -0.04);
			SF_AddCondition(&reaction, GetSkillAfterPenalty(pchar, SKILL_COMMERCE) > 65, SF_CONDITION_SKILL, SKILL_COMMERCE);
		break;
		case "d":
			SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_COST, 0.95);
			SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_STOCK, -0.55);
			SZN_SetTempEffect(M_CONTRABAND_TRADE_STATUS, 1);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "Quiet"));
			SZN_SetReactionEffect(&reaction, SET + M_CONTRABAND_TRADE_STATUS, 2);
			SF_AddCondition(&reaction, HasPerk(pchar, "Quiet"), SF_CONDITION_PERK, "Quiet");
		break;
	}

	action = SF_AddAction("a", "", "", SF_Icon("season", StoryObject.context.seasonId));
	action.tooltipCallback = "ShowSeasonsModifiers";
}

void Nextshadows_Node0_b_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_b_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_b_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_b_d_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_c_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_c_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_c_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_d_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_d_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_d_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_d_d_reaction()
{
	SZN_DefaultReaction();
}

void Nextshadows_Node0_a_action()
{
	SZN_SF_Ending();
}

void Nextshadows_Node0_Triumph()
{
	SZN_ApplyEffectsToCurrentSeason();
	DelEventHandler("SF_ButtonWasPressed", "SZN_ButtonWasPressed");
	storyObject.exit = true;
}