string GetCharPerkInterfaceState(ref chr, ref perk)
{
	string reason = "";
	string perkName = GetAttributeName(perk);
	CanTakePerk(chr, perk, &reason);

	if (reason == "alreadyHave") return "active";
	if (IsMainCharacter(chr) && GetOfficersPerkUsing(pchar, perkName)) return "officer";
	else if (HasPerk(chr, perkName)) return "officer";
	if (reason == "disabled") return "disabled";
	if (reason == "") return "available";
	return "locked";
}

string PERKPICTURE(bool enable)
{
	if (enable) return "PERKS_ENABLE";
	return "PERKS_DISABLE";
}

string PERKPICTURE_BASE(bool enable, ref perk)
{
	if (enable) return "base_" + perk.BaseType;
	return "base";
}
