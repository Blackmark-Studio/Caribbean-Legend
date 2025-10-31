// Здесь работа Статусов, это, как правило, быстротечные эффекты, применяющиеся поверх всех расчётов и неподвластные множителям экипировки и навыков
// Должны применяться только к личным умениям
int GetStatusIntValue(ref chr, string skillName)
{
	object null;
	return GetStatusIntWithInfo(chr, skillName, &null, false);
}

int GetStatusIntWithInfo(ref chr, string skillName, ref infoObject, bool IsNededInfo)
{
	int skillValue = 0;
	if (!isSelfTypeSkill(skillName)) return 0;

	// Алкоголь
	int alcoN = GetAttributeInt(chr, "chr_ai.drunk.skill." +skillName);
	skillValue += alcoN;
	if (IsNededInfo) infoObject.alco = alcoN;

	// Перегруз, здесь проверяется флаг, а не вычисляется вес всех вещей
	int weightN = GetWeightSkillImpact(chr);
	skillValue += weightN;
	if (IsNededInfo) infoObject.overload = weightN;

	return skillValue;
}
