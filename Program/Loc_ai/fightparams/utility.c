float DamageSkillMtp(ref chr, string type)
{
	float level;
	if (type == "range") level = LAi_GetCharacterGunLevel(chr);
	else level = LAi_GetCharacterFightLevel(chr);

	return pow(level, SKILL_MTP_POWER);
}
