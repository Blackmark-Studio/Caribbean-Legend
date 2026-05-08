#include "story_frames\Seasons\helpers.c"

void NextReed_Node0()
{
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
	situation.b.c = 10;
	situation.b.d = 10;

	situation.c.a = 15;
	situation.c.b = 15;
	situation.c.c = 15;
	situation.c.d = 10;
	situation.c.e = 10;

	situation.d.a = 15;
	situation.d.b = 15;
	situation.d.c = 10;
	

	SF_ResolveSituation(&situation);
	SZN_IncreaseTempEffect(M_TRADE_LICENSE_COST, -0.35);

	switch (situation.b)
	{
		case "a":
			SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_STOCK, 0.80);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "TreasureHunter"));
			SZN_SetReactionEffect(&reaction, M_CARIBBEAN_GOODS_STOCK, 0.15);
			SF_AddCondition(&reaction, HasPerk(pchar, HERO_TYPE_ACCOUNTANT), SF_CONDITION_HERO_TYPE, HERO_TYPE_ACCOUNTANT);
		break;
		case "b":
			SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_STOCK, 1.20);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "Tiefit"));
			SZN_SetReactionEffect(&reaction, M_CARIBBEAN_GOODS_STOCK, 0.25);
			SF_AddCondition(&reaction, HasPerk(pchar, "Tiefit"), SF_CONDITION_PERK, "Tiefit");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_STOCK, -0.35);
			reaction = SF_AddReaction("b", "", "", SF_Icon(SKILL_TYPE, SKILL_LEADERSHIP));
			SZN_SetReactionEffect(&reaction, M_IMPORT_PRICE_MTP, 0.02);
			SF_AddCondition(&reaction, GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP) > 65, SF_CONDITION_SKILL, SKILL_LEADERSHIP);
		break;
		case "d":
			SZN_SetTempEffect(M_UNIQUE_GOODS_AVAILABLE, 1);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "TradeConnections"));
			SZN_SetReactionEffect(&reaction, M_UNIQUE_GOODS_STOCK, 0.5);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("TradeConnections"), SF_CONDITION_PERK, "TradeConnections");
		break;
	}

	switch (situation.c)
	{
		case "a":
			SZN_IncreaseTempEffect(M_EXPORT_PRICE_MTP, -0.06);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "BasicCommerce"))
			SZN_SetReactionEffect(&reaction, M_EXPORT_PRICE_MTP, -0.02);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("BasicCommerce"), SF_CONDITION_PERK, "BasicCommerce");
		break;
		case "b":
			SZN_IncreaseTempEffect(M_EXPORT_PRICE_MTP, -0.04);
			SZN_IncreaseTempEffect(M_IMPORT_PRICE_MTP, 0.06);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "ProfessionalCommerce"))
			SZN_SetReactionEffect(&reaction, M_EXPORT_PRICE_MTP, -0.03);
			SZN_SetReactionEffect(&reaction, M_IMPORT_PRICE_MTP, 0.02);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("ProfessionalCommerce"), SF_CONDITION_PERK, "ProfessionalCommerce");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_IMPORT_PRICE_MTP, 0.07);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "AdvancedCommerce"))
			SZN_SetReactionEffect(&reaction, M_IMPORT_PRICE_MTP, 0.02);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("AdvancedCommerce"), SF_CONDITION_PERK, "AdvancedCommerce");
		break;
		case "d":
			SZN_IncreaseTempEffect(M_DEBIT_RATE, 0.03);
			SZN_IncreaseTempEffect(M_DEPOSIT_SILVER_RATE, 0.01);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "Investor"))
			SZN_SetReactionEffect(&reaction, M_DEPOSIT_GOLD_RATE, 0.01);
			SF_AddCondition(&reaction, HasPerk(pchar, "Investor"), SF_CONDITION_PERK, "Investor");
		break;
		case "e":
			SZN_SetTempEffect(M_GOLDSILVER_GOODS_AVAILABLE, 1);
			SZN_SetTempEffect(M_LEGAL_CONTRABAND, 1);
			reaction = SF_AddReaction("c", "", "", SF_Icon(SKILL_TYPE, SKILL_COMMERCE));
			SZN_SetReactionEffect(&reaction, SET + M_SLAVES_GOODS_AVAILABLE, 1);
			SF_AddCondition(&reaction, GetSkillAfterPenalty(pchar, SKILL_COMMERCE) > 65, SF_CONDITION_SKILL, SKILL_COMMERCE);
		break;
	}

	switch (situation.d)
	{
		case "a":
			SZN_IncreaseTempEffect(M_FOOD_CONSUMPTION, -0.10);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "Doctor1"));
			SZN_SetReactionEffect(&reaction, M_MEDICAMENT_CONSUMPTION, -0.10);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("Doctor1"), SF_CONDITION_PERK, "Doctor1");
		break;
		case "b":
			SZN_IncreaseTempEffect(M_FOOD_CONSUMPTION, -0.15);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "Looting"));
			SZN_SetReactionEffect(&reaction, M_FOOD_CONSUMPTION, -0.10);
			SF_AddCondition(&reaction, HasPerk(pchar, "Looting"), SF_CONDITION_PERK, "Looting");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_CREW_HIRE_COST, 2.50);
			SZN_IncreaseTempEffect(M_CREW_MAINTENANCE_COST, 0.70);
			reaction = SF_AddReaction("d", "", "", SF_Icon(PIRATES_TYPE, PIRATES_A));
			SZN_SetReactionEffect(&reaction, M_CREW_MAINTENANCE_COST, -0.04 * GetPirates(pchar, PIRATES_A));
		break;
	}

	action = SF_AddAction("a", "", "", SF_Icon("season", StoryObject.context.seasonId));
	action.tooltipCallback = "ShowSeasonsModifiers";
}

void Nextreed_Node0_b_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_b_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_b_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_b_d_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_c_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_c_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_c_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_c_d_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_c_e_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_d_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_d_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_d_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextreed_Node0_a_action()
{
	SZN_SF_Ending();
}

void Nextreed_Node0_Triumph()
{
	SZN_ApplyEffectsToCurrentSeason();
	storyObject.exit = true;
}