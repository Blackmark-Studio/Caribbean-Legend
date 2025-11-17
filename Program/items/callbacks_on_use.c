// Здесь коллбэки предметов, вызываемые через RunOnUseCallbacks

// Эффект зелья забвения
void RevokePerksPotionEffect(ref chr, ref item)
{
	PlaySound("Ambient\Horror\Fear_breath_01.wav");
	RemoveAllPerksNoCash(chr);
	Achievment_Set("ach_CL_173");
	object temp;
	GEN_SummPerkPoints(chr, &temp);

	SetAttribute(chr, "perks.FreePoints_self", sti(temp.self));
	SetAttribute(chr, "perks.FreePoints_ship", sti(temp.ship));
	SetAttribute(chr, "perks.FreePoints_self_exp", sti(temp.self_left));
	SetAttribute(chr, "perks.FreePoints_ship_exp", sti(temp.ship_left));
	if (IsMainCharacter(chr))
	{
		pchar.questTemp.PerksPotionEffect = true;
		SetCharacterPerkNoCash(chr, "FlagPir", false);
		SetCharacterPerkNoCash(chr, "Flag" + NationShortName(GetBaseHeroNation()), false);
	}
	else ForceHeroPerks(chr);

	RemoveItems(chr, item.id, 1);
	CT_UpdateCashTables(chr);
}