// Здесь оставлены старые названия методов, чтобы пока не заменять их во всех использующих скиллы местах

float GetCharacterSkillToOld(ref _refCharacter, string skillName)
{
	return makefloat(GetCharacterSkill(_refCharacter, &skillName) / SKILL_TO_OLD);
}

int GetCharacterSkill(ref chr, string skillName)
{
	return GetSkillAfterPenalty(chr, &skillName);
}

int GetCharacterSkillSimple(ref chr, string skillName)
{
	return GetSkillWithEffects(chr, &skillName);
}

float GetSummonSkillFromNameToOld(ref chr, string skillName)
{
	return (GetSummonSkillFromName(chr, &skillName) / SKILL_TO_OLD);
}

int GetSummonSkillFromName(ref chr, string skillName)
{
	return GetSkillAfterPenalty(chr, &skillName);
}

int GetSummonSkillFromNameSimple(ref chr, string skillName)
{
	return GetSkillWithOfficer(chr, &skillName);
}

// по имени скила вернуть значение
int GetSkillValue(ref chr, string type, string skillName)
{
	if (CheckAttribute(chr, type + "." + skillName))
	{
		return sti(chr.(type).(skillName));
	}
	return 0;
}

int GetCharacterSPECIAL(ref chr, string skillName)
{
	return GetSpecialAfterPenalty(chr, &skillName);
}

int GetCharacterSPECIALSimple(ref chr, string skillName)
{
	return GetSpecialWithEffects(chr, &skillName);
}