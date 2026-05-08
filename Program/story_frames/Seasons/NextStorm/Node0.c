#include "story_frames\Seasons\helpers.c"
int StoryButtonsPressed = 0; // каунтер кнопок для ачивок

void NextStorm_Node0()
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
	situation.b.c = 10;
	situation.b.d = 10;

	situation.c.a = 15;
	situation.c.b = 15;
	situation.c.c = 10;

	situation.d.a = 15;
	situation.d.b = 15;
	situation.d.c = 10;
	situation.d.d = 10;

	SF_ResolveSituation(&situation);
	SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_COST, 0.80);
	SZN_IncreaseTempEffect(M_EUROPEAN_GOODS_STOCK, -0.55);
	SZN_IncreaseTempEffect(M_REPAIR_COST, 1.20);
	SZN_IncreaseTempEffect(M_WORLD_SHIPS_CREW_MTP, -0.30);
	SZN_IncreaseTempEffect(M_WORLD_SHIPS_HULL_MTP, -0.15);

	switch (situation.b)
	{
		case "a":
			SZN_IncreaseTempEffect(M_STORM_DAMAGE_MTP, 0.15);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "SailingProfessional"));
			SZN_SetReactionEffect(&reaction, M_GLOBAL_SPEED, 0.08);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("SailingProfessional"), SF_CONDITION_PERK, "SailingProfessional");
		break;
		case "b":
			SZN_IncreaseTempEffect(M_STORM_DAMAGE_MTP, 0.25);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "Thrift"));
			SZN_SetReactionEffect(reaction, M_STORM_DAMAGE_MTP, -0.07);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("Thrift"), SF_CONDITION_PERK, "Thrift");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_STORM_DAMAGE_MTP, -0.15);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "WindCatcher"));
			SZN_SetReactionEffect(&reaction, M_SHIP_SPEED_DYNAMIC, 0.12);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("WindCatcher"), SF_CONDITION_PERK, "WindCatcher");
		break;
		case "d":
			SZN_IncreaseTempEffect(M_STORM_DAMAGE_MTP, -0.05);
			SZN_IncreaseTempEffect(M_AMMO_GOODS_STOCK, -0.70);
			SZN_IncreaseTempEffect(M_CONVENIENCE_GOODS_STOCK, -0.40);
			reaction = SF_AddReaction("b", "", "", SF_Icon("Perk", "Collection"));
			SZN_SetReactionEffect(&reaction, M_CREW_MORALE_DEBUFF_MTP, 0.70);
			SF_AddCondition(&reaction, HasPerk(pchar, "Collection"), SF_CONDITION_PERK, "Collection");
		break;
	}

	switch (situation.c)
	{
		case "a":
			SZN_IncreaseTempEffect(M_RECRUITS_MTP, -0.55);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "Gossip"))
			SZN_SetReactionEffect(&reaction, M_RECRUITS_MTP, 0.20);
			SF_AddCondition(&reaction, HasPerk(pchar, "Gossip"), SF_CONDITION_PERK, "Gossip");
		break;
		case "b":
			SZN_IncreaseTempEffect(M_RECRUITS_MTP, -0.75);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "BoardingPrepare"))
			SZN_SetReactionEffect(&reaction, M_RECRUITS_MTP, 0.15);
			SF_AddCondition(&reaction, CheckOfficersPerkEnable("BoardingPrepare"), SF_CONDITION_PERK, "BoardingPrepare");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_RECRUITS_MTP, 0.10);
			SZN_IncreaseTempEffect(M_CREW_HIRE_MORALE_MTP, 0.30);
			reaction = SF_AddReaction("c", "", "", SF_Icon("perk", "Looting"))
			SZN_SetReactionEffect(&reaction, M_RECRUITS_MTP, 0.20);
			SZN_SetReactionEffect(&reaction, M_CREW_HIRE_MORALE_MTP, 0.20);
			SF_AddCondition(&reaction, HasPerk(pchar, "Looting"), SF_CONDITION_PERK, "Looting");
		break;
	}

	// Дальше
	switch (situation.d)
	{
		case "a":
			SZN_IncreaseTempEffect(M_MEDICAMENT_CONSUMPTION, 0.35);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "Mule"));
			SZN_SetReactionEffect(&reaction, M_MEDICAMENT_CONSUMPTION, -0.20);
			SF_AddCondition(&reaction, HasPerk(pchar, HERO_TYPE_ATHLETE), SF_CONDITION_HERO_TYPE, HERO_TYPE_ATHLETE);
		break;
		case "b":
			SZN_IncreaseTempEffect(M_MEDICAMENT_CONSUMPTION, 0.65);
			SZN_IncreaseTempEffect(M_MEDICAMENT_COST, 2.00);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "Master"));
			SZN_SetReactionEffect(&reaction, M_MEDICAMENT_CONSUMPTION, -0.20);
			SZN_SetReactionEffect(&reaction, M_MEDICAMENT_COST, -1.00);
			SF_AddCondition(&reaction, HasPerk(pchar, "Master"), SF_CONDITION_PERK, "Master");
		break;
		case "c":
			SZN_IncreaseTempEffect(M_MEDICAMENT_CONSUMPTION, 0.20);
			SZN_IncreaseTempEffect(M_CREW_MORALE_MTP, 0.30);
			SZN_IncreaseTempEffect(M_CREW_EXP_MTP, -0.40);
			reaction = SF_AddReaction("d", "", "", SF_Icon("perk", "HPPlus"));
			SZN_SetReactionEffect(&reaction, M_CREW_EXP_MTP, 0.20);
			SF_AddCondition(&reaction, HasPerk(pchar, "HPPlus"), SF_CONDITION_PERK, "HPPlus");
		break;
		case "d":
			SZN_IncreaseTempEffect(M_MEDICAMENT_COST, 5.00);
			SZN_IncreaseTempEffect(M_CONVENIENCE_GOODS_STOCK, 7.00);
			SZN_IncreaseTempEffect(M_CONVENIENCE_GOODS_COST, -0.50);
			reaction = SF_AddReaction("d", "", "", SF_Icon(PIRATES_TYPE, PIRATES_A));
			SZN_SetReactionEffect(&reaction, M_CONVENIENCE_GOODS_STOCK, 0.02 * GetPirates(pchar, PIRATES_A));
		break;
	}

	action = SF_AddAction("a", "", "", SF_Icon("season", StoryObject.context.seasonId));
	action.tooltipCallback = "ShowSeasonsModifiers";
}

void Nextstorm_Node0_b_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_b_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_b_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_b_d_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_c_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_c_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_c_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_c_d_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_d_a_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_d_b_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_d_c_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_d_d_reaction()
{
	SZN_DefaultReaction();
}

void Nextstorm_Node0_a_action()
{
	SZN_SF_Ending();
}

void Nextstorm_Node0_Triumph()
{
	SZN_ApplyEffectsToCurrentSeason();

	DelEventHandler("SF_ButtonWasPressed", "SZN_ButtonWasPressed");
	storyObject.exit = true;
}