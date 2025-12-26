string GetCharPerkInterfaceState(ref chr, ref perk)
{
	string reason = "";
	string perkName = GetAttributeName(perk);
	CanTakePerk(chr, perk, &reason);
	bool isPchar = IsMainCharacter(chr);

	if (reason == "alreadyHave") return "active";
	if (isPchar && GetOfficersPerkUsing(pchar, perkName)) return "officer";
	else if (HasPerk(chr, perkName)) return "officer";
	if (isPchar && strleft(perkName, 4) == "flag" && LicenseOrJokerFlagPerk(perkName)) return "officer";
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

// Нужно ли показать, что перк флага в интерфейсе есть из-за лицензии/джокера
bool LicenseOrJokerFlagPerk(string perkName)
{
	if (LICENSE_HasLicense()) return true;

	aref flags = _STH_GetFlags(_STH_GetNationByPerk(perkName));
	return (CheckAttribute(&flags, "joker"));
}