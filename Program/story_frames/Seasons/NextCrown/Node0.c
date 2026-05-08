#include "story_frames\Seasons\helpers.c"

void NextCrown_Node0()
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
	situation.b.c = 15;

	situation.c.a = 15;
	situation.c.b = 15;
	situation.c.c = 15;

	situation.d.a = 15;
	situation.d.b = 15;
	situation.d.c = 15;
	situation.d.d = 15;
	situation.d.e = 12;
	situation.d.f = 11;

	SF_ResolveSituation(&situation);

	SZN_IncreaseTempEffect(M_RECRUITS_MTP, 0.5);
	SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_COST, -0.40);
	SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_STOCK, 0.75);
	
	switch (situation.b)
	{
		case "a":
			SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_COST, 1.30);
			SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_STOCK, -0.80);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "TreasureHunter"));
			SZN_SetReactionEffect(&reaction, M_CARIBBEAN_GOODS_STOCK, 0.2);
			SF_AddCondition(reaction, HasPerk(pchar, HERO_TYPE_ACCOUNTANT), SF_CONDITION_HERO_TYPE, HERO_TYPE_ACCOUNTANT);
		break;
		case "b":
			SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_COST, 1.90);
			SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_STOCK, -0.95);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "Looting"));
			SZN_SetReactionEffect(&reaction, M_CARIBBEAN_GOODS_STOCK, 0.35);
			SF_AddCondition(&reaction, HasPerk(pchar, "Looting"), SF_CONDITION_PERK, "Looting");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_COST, 1.40);
			SZN_IncreaseTempEffect(M_CARIBBEAN_GOODS_STOCK, -0.85);
			SZN_IncreaseTempEffect(M_EXPORT_PRICE_MTP, 0.05);
			SZN_IncreaseTempEffect(M_IMPORT_PRICE_MTP, -0.05);
			reaction = SF_AddReaction("b", "", "", SF_Icon(SKILL_TYPE, SKILL_COMMERCE));
			SZN_SetReactionEffect(&reaction, M_IMPORT_PRICE_MTP, 0.02);
			SF_AddCondition(&reaction, GetSkillAfterPenalty(pchar, SKILL_COMMERCE) > 70, SF_CONDITION_SKILL, SKILL_COMMERCE);
		break;
	}


	switch (situation.c)
	{
		case "a":
			SZN_IncreaseTempEffect(M_REPAIR_COST, -0.30);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "Builder"))
			SZN_SetReactionEffect(&reaction, M_SEA_REPAIR_EFFICENCY, 0.15);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("Builder"), SF_CONDITION_PERK, "Builder");
		break;
		case "b":
			SZN_IncreaseTempEffect(M_REPAIR_COST, -0.45);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "Sniper"))
			SZN_SetReactionEffect(&reaction, M_ENEMY_HULL_DAMAGE_MTP, 0.07);
			SF_AddCondition(&reaction, HasPerk(pchar, HERO_TYPE_SHOOTER), SF_CONDITION_HERO_TYPE, HERO_TYPE_SHOOTER);
		break;
		case "c":
			SZN_IncreaseTempEffect(M_REPAIR_COST, 0.20);
			reaction = SF_AddReaction("c", "", "", SF_Icon(SKILL_TYPE, SKILL_ACCURACY));
			SZN_SetReactionEffect(&reaction, M_REPAIR_COST, -0.30);
			SF_AddCondition(&reaction, GetSkillAfterPenalty(pchar, SKILL_ACCURACY) > 60, SF_CONDITION_SKILL, SKILL_ACCURACY);
		break;
	}

	switch (situation.d)
	{
		case "a":
			SZN_IncreaseTempEffect(M_NATIONS_REPUTATION_MTP, 1.0);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "Gossip"));
			SZN_SetReactionEffect(&reaction, M_NATIONS_REPUTATION_MTP, 1.0);
			SF_AddCondition(&reaction, HasPerk(pchar, "Gossip"), SF_CONDITION_PERK, "Gossip");
		break;
		case "b":
			SZN_IncreaseTempEffect(M_CREW_HIRING_EXP_MTP, 0.30);
			SZN_IncreaseTempEffect(M_CREW_EXP_MTP, 0.25);
			reaction = SF_AddReaction("d", "", "", SF_Icon(PIRATES_TYPE, PIRATES_I));
			SZN_SetReactionEffect(&reaction, M_CREW_HIRING_EXP_MTP, 0.02 * makefloat(GetPirates(pchar, PIRATES_I)) + 0.3);
		break;
		case "c":
			SZN_IncreaseTempEffect(M_STEALTH_INCEPTION_BONUS, 0.15);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "Trustworthy"));
			SZN_SetReactionEffect(&reaction, M_STEALTH_INCEPTION_BONUS, 0.07);
			SF_AddCondition(&reaction, HasPerk(pchar, "Trustworthy"), SF_CONDITION_PERK, "Trustworthy");
		break;
		case "d":
			SZN_IncreaseTempEffect(M_STEALTH_INCEPTION_BONUS, -0.15);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "Quiet"));
			SZN_SetReactionEffect(&reaction, M_STEALTH_INCEPTION_BONUS, 0.06);
			SF_AddCondition(&reaction, HasPerk(pchar, "Quiet"), SF_CONDITION_PERK, "Quiet");
		break;
		case "e":
			SZN_IncreaseTempEffect(M_RECRUITS_MTP, -0.7);
			SZN_IncreaseTempEffect(M_CREW_HIRING_EXP_MTP, -0.4);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "Drill"));
			SZN_SetReactionEffect(&reaction, M_CREW_EXP_MTP, 0.15);
			SF_AddCondition(&reaction, HasPerk(pchar, "Drill"), SF_CONDITION_PERK, "Drill");
		break;
		case "f":
			SZN_IncreaseTempEffect(M_NATIONS_REPUTATION_MTP, 0.5);
			SZN_IncreaseTempEffect(M_SHIPYARD_CANNONS_STOCK, -0.45);
			reaction = SF_AddReaction("d", "", "", SF_Icon(SKILL_TYPE, SKILL_CANNONS));
			SZN_SetReactionEffect(&reaction, M_MIN_FORT_CANNONS_MTP, -0.12);
			SF_AddCondition(&reaction, GetSkillAfterPenalty(pchar, SKILL_CANNONS) > 65, SF_CONDITION_SKILL, SKILL_CANNONS);
		break;
	}

	action = SF_AddAction("a", "", "", SF_Icon("season", StoryObject.context.seasonId));
	action.tooltipCallback = "ShowSeasonsModifiers";
}

void Nextcrown_Node0_b_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_b_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_b_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_b_d_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_c_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_c_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_c_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_d_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_d_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_d_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_d_d_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_d_e_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_d_f_reaction()
{
	SZN_DefaultReaction();
}

void Nextcrown_Node0_a_action()
{
	SZN_SF_Ending();
}

void Nextcrown_Node0_Triumph()
{
	SZN_ApplyEffectsToCurrentSeason();
	storyObject.exit = true;
}