// Здесь коллбэки предметов, вызываемые через RunOnUseCallbacks

// Эффект зелья забвения
void RevokePerksPotionEffect(ref chr, ref item)
{
	PlaySound("Ambient\Horror\Fear_breath_01.wav");
	RemoveAllPerksNoCash(chr);
	Achievment_Set("ach_CL_173");
	object temp;
	GEN_SummPerkPoints(chr, &temp);

	SetAttribute(chr, "perks.FreePoints_self", int(temp.self));
	SetAttribute(chr, "perks.FreePoints_ship", int(temp.ship));
	SetAttribute(chr, "perks.FreePoints_self_exp", int(temp.self_left));
	SetAttribute(chr, "perks.FreePoints_ship_exp", int(temp.ship_left));
	if (IsMainCharacter(chr))
	{
		pchar.questTemp.PerksPotionEffect = true;
		SetCharacterPerkNoCash(chr, "FlagPir", false);
		SetCharacterPerkNoCash(chr, "Flag" + NationShortName(GetBaseHeroNation()), false);
	}
	else ForceHeroPerks(chr);

	RemoveItems(chr, item.id, 1);
	RemoveCharacterEquip(chr, MUSKET_ITEM_TYPE);
	RemoveCharacterEquip(chr, GUN_ITEM_TYPE);
	CT_UpdateCashTables(chr);
}