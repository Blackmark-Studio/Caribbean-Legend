void ShowSeasonsModifiers(ref rObject, ref sHeader, ref text, ref badText, ref goodText)
{
	StoryObject.tooltipConfig = "SZN_TooltipConfig";
	if (CheckAttributeEqualTo(rObject, "reaction", "1"))
	{
		SZN_ShowModifiers(rObject, sHeader, text, badText, goodText, DLG_Convert("additional_effects_title", "StoryFrames\Seasons\Common.txt")); // модификаторы на реакции в сторе смены сезона
		return;
	}

	aref tempEffects;
	makearef(tempEffects, storyObject.tempEffects);
	SZN_ShowModifiers(tempEffects, sHeader, text, badText, goodText, DLG_Convert("effects_title", "StoryFrames\Seasons\Common.txt"));
}

// временное хранилище модификаторов сезона, применяются к сезону при выходе из стори
aref SZN_tempEffects()
{
	aref tmp;
	makearef(tmp, storyObject.tempEffects.modifiers);
	return tmp;
}

void SZN_ApplyEffectsToCurrentSeason()
{
	DeleteAttribute(&SeasonSystem, "current");
	string newSeasonName = StoryObject.context.seasonId;
	SeasonSystem.current = newSeasonName;
	aref seasonEffects;
	makearef(seasonEffects, SeasonSystem.current.modifiers);
	CopyAttributes(&seasonEffects, SZN_tempEffects());
	SZN_ChangeEncounters(newSeasonName);
	SeasonSystem.lastChangeTimestamp = TMSTD_Timestamp(0);
}

void SZN_SetReactionEffect(ref reaction, string modifierName, ref value)
{
	SetModifier(reaction, modifierName, value);
	reaction.tooltipCallback = "ShowSeasonsModifiers";
}

void SZN_IncreaseTempEffect(string modifierName, ref value)
{
	IncreaseModifierFromSourceDirect(SZN_tempEffects(), modifierName, value, "season");
}

void SZN_SetTempEffect(string modifierName, ref value)
{
	SetModifierFromSourceDirect(SZN_tempEffects(), SET + modifierName, value, "season");
}

void SZN_DefaultReaction()
{
	aref reaction = SF_CurrentReaction();
	if (reaction == nullptr) return; // что-то пошло не так
	if (!CheckAttribute(&reaction, "modifiers")) return;

	aref effects = SZN_tempEffects();
	aref modifiers, modifier;
	makearef(modifiers, reaction.modifiers);
	int modifiersQty = GetAttributesNum(modifiers);
	for (int i = 0; i < modifiersQty; i++)
	{
		modifier = GetAttributeN(modifiers, i);
		string modifierName = GetAttributeName(modifier);
		if (modifierName == "callbacks") MergeCallbacks(&effects, &modifier);
		else if (modifierName == "has") MergeFlags(&effects, &modifier);
		else MergeModifier(&effects, &modifier, modifierName, "season");
	}

	SF_Log(SF_Convert("log"));
}

void SZN_SF_Ending()
{
	aref action = SF_Ending();
	action.tooltipCallback = "ShowSeasonsModifiers";
	action.iconGroup = "SEASONS_ICONS";
	action.iconName = StoryObject.context.seasonId;
}

// Трекаем реакции в сезонах для ачивок
void SZN_ButtonWasPressed()
{
	if (GetAttributeOrDefault(&StoryObject, "style", "") == "ending") return;

	aref links = GetAref(&StoryObject, "links", true);
	int linksQty = GetAttributesNum(links);
	bool atLeastOneReactionLeft = false;
	for (int i = 0; i < linksQty; i++)
	{
		aref link = GetAttributeN(links, i);
		if (!AttributeIsTrue(&link, "reaction")) continue;
		if (AttributeIsTrue(&link, "hidden")) continue;
		atLeastOneReactionLeft = true;
	}
	
	if (atLeastOneReactionLeft) return;

	if (StoryObject.context.seasonId == STORM_SEASON) Achievment_Set("ach_CL_206");
	else if (StoryObject.context.seasonId == SHADOW_SEASON) Achievment_Set("ach_CL_207");
}