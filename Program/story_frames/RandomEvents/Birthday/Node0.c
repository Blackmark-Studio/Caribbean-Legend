#include "story_frames\RandomEvents\helpers.c"
#include "story_frames\RandomEvents\Birthday\condition.c"

void Birthday_Node0()
{
	SF_InitModule("RandomEvents");
	PlayStereoSound("interface\new_level.wav");
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
			action = SF_AddAction("a_b", "", "", SF_Icon("story", "random"));
			action = SF_AddAction("a_c", "", "", SF_Icon("story", "random"));
		break;
		case "b":
			action = SF_AddAction("b_a", "", "", SF_Icon("story", "random"));
			action = SF_AddAction("b_b", "", "", SF_Icon("story", "random"));
			action = SF_AddAction("b_c", "", "", SF_Icon("story", "random"));
		break;
		case "c":
			action = SF_AddAction("c_a", "", "", SF_Icon("story", "random"));
			action = SF_AddAction("c_b", "", "", SF_Icon("story", "random"));
			action = SF_AddAction("c_c", "", "", SF_Icon("story", "random"));
		break;
	}

	storyObject.onClose._Birthday_TeleportToDeck = true;
	RE_SetEventDelay(340);
}

void Birthday_Node0_a_a_action()
{
	string itemRoll[] = {"jewelry1", "jewelry2", "jewelry3", "jewelry4", "jewelry14", "jewelry15", "jewelry17", "jewelry18", "jewelry19", "jewelry20", "jewelry21", "jewelry22", "jewelry23"};
	context.ItemA = itemRoll[SF_Rand(GetArraySize(&itemRoll)-1)];
	context.ItemB = "cannabis7";
	SF_AddEffect(SF_E_ITEMS, pchar, context.ItemA, 25);
	SF_AddEffect(SF_E_ITEMS, pchar, context.ItemB, 2+SF_Rand(2));
	SF_Triumph("a_a");
}

void Birthday_Node0_a_b_action()
{
	string itemRoll[] = {"totem_01", "totem_02", "totem_03", "totem_04", "totem_06", "totem_05", "totem_07", "totem_08", "totem_09", "totem_10", "totem_11", "totem_12", "totem_13"};
	context.ItemA = itemRoll[SF_Rand(GetArraySize(&itemRoll)-1)];
	
	// карта сокровищ → половинка → отличная карта → обычная карта
	if (GetCharacterFreeItem(pchar, "map_full") == 0)
	{
		context.ItemB = "map_full";
		ref map = ItemsFromID("map_full");
		FillMapForTreasure(map, GetTresuareMapSeed(), false);
	}
	else if (GetCharacterFreeItem(pchar, "map_part1") + GetCharacterFreeItem(pchar, "map_part2") > 1) // есть 2 половинки
	{
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) context.ItemB = SelectAdmiralMaps();
		else
		{
			string maps[] = {"map_jam", "map_cayman", "map_barbados", "map_trinidad", "map_Curacao", "map_martiniqua", "map_dominica", "map_puerto", "map_cuba", "map_hisp", "map_nevis", "map_guad", "map_antigua", "map_TORTUGA", "map_terks", "map_sm", "map_bermudas", "map_beliz", "map_santa", "map_maine_1", "map_maine_2", "map_panama", "map_cumana"};
			context.ItemB = maps[SF_Rand(SF_Rand(GetArraySize(&maps)-1))];
		}
	}
	else context.ItemB = "map_part1";

	context.ItemC = "berserker_potion";
	SF_AddEffect(SF_E_ITEMS, pchar, context.ItemA, 1);
	SF_AddEffect(SF_E_ITEMS, pchar, context.ItemB, 1);
	SF_AddEffect(SF_E_ITEMS, pchar, context.ItemC, 2+SF_Rand(2));
	SF_Triumph("a_b");
}

void Birthday_Node0_a_c_action()
{
	string itemRoll[3] = {"spyglass3", "hat2", "pistol5"};
	int blades[];
	FindBlades(&blades, ITEM_BLADE_TYPE_FLAG_ALL, B_GOOD, ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_OFFICER);
	context.ItemA = itemRoll[SF_Rand(2)];
	SF_AddEffect(SF_E_ITEMS, pchar, context.ItemA, 1);

	context.ItemB = Items[blades[SF_Rand(GetArraySize(&blades)-1)]].id;
	SF_AddEffect(SF_E_ITEMS, pchar, context.ItemB, 1);
	SF_Triumph("a_c");
}

void Birthday_Node0_Triumph()
{
	storyObject.exit = true;
}

