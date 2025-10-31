string GetHumanCharacterArchetype(ref chr, string type)
{
	string key = GetCharacterArchetype(chr, type);
	if (key == "") return "";
	if (key == GEN_ARCHETYPE_RANDOM) return "";
	if (key == GEN_ARCHETYPE_FREE) return "";
	if (key == GEN_ARCHETYPE_PEASANT) return "";
	return DLG_Convert(key, "personality.txt", chr);
}

string GetHumanCharacterArchetypeFull(ref chr)
{
	string mainArchetype = GetHumanCharacterArchetype(chr, "main");
	string secondaryArcheType = GetHumanCharacterArchetype(chr, "secondary");
	if (mainArchetype == "") return "";
	if (secondaryArcheType == "") return mainArchetype;
	return mainArchetype + " / " + secondaryArcheType;
}