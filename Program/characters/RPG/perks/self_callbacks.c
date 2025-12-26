// Здесь коллбэки предметов, вызываемые через RunTableCallbacks
// Все они имеют единую сигнатуру и работают с модификаторами

void Perk_Muscles(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_HEAVY) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED, PERK_VALUE2_MUSCLES, funcName);
}

void Perk_PerfectBalance(ref chr, ref table, ref function, ref context, string funcName)
{
	int weaponType = GetAttributeInt(table, HAS + M_WEAPON_TYPE);
	if (weaponType != WEAPON_MEDIUM) return;

	SetModifierFromSourceDirect(table, M_REDUCE_DAMAGE, PERK_VALUE_PERFECT_BALANCE, funcName);
}

void Perk_Heartbreaker(ref chr, ref table, ref function, ref context, string funcName)
{
	int curve = GetAttributeInt(table, HAS + M_WEAPON_CURVATURE);
	if (curve != WEAPON_STRAIGHT) return;

	SetModifierFromSourceDirect(table, FORCE_STRIKE + "_" + M_DAMAGE, PERK_VALUE_HEARTBREAKER, funcName);
	SetModifierFromSourceDirect(table, FORCE_STRIKE + "_" + M_ACTION_SPEED, PERK_VALUE2_HEARTBREAKER, funcName);
}

void Perk_BladeDancer(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_CURVATURE) != WEAPON_CURVE) return;

	SetModifierFromSourceDirect(table, ROUND_STRIKE + "_" + M_DAMAGE, PERK_VALUE_BLADE_DANCER, funcName);
}


void Perk_OttomanGrip(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_CURVATURE) != WEAPON_CURVE) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_OTTOMAN_GRIP, funcName);
}

void Perk_Puncher(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_CURVATURE) != WEAPON_STRAIGHT) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_PUNCHER, funcName);
}

void Perk_Dragoon(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_MEDIUM) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_DRAGOON, funcName);
}

void Perk_Virtuosity(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_LIGHT) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_VIRTUOSITY, funcName);
}

void Perk_Inertia(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_HEAVY) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_INERTIA, funcName);
}

void Perk_MeatGrinder(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_LENGTH) != WEAPON_SHORT) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_MEAT_GRINDER, funcName);
}

void Perk_Reach(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_LENGTH) != WEAPON_LONG) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_REACH, funcName);
}

void Perk_Stabbing(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_LENGTH) != WEAPON_SHORT) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_STABBING, funcName);
}

void Perk_NeckStrike(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_LENGTH) != WEAPON_LONG) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_NECK_STRIKE, funcName);
}

void Perk_Conquest(ref chr, ref table, ref function, ref context, string funcName)
{
	int length = GetAttributeInt(table, HAS + M_WEAPON_LENGTH);
	if (length != WEAPON_LONG) return;

	SetModifierFromSourceDirect(table, FAST_STRIKE  + "_" + M_DAMAGE, PERK_VALUE_CONQUEST, funcName);
	SetModifierFromSourceDirect(table, BREAK_STRIKE + "_" + M_DAMAGE, PERK_VALUE_CONQUEST, funcName);
}

void Perk_SabreHurricane(ref chr, ref table, ref function, ref context, string funcName)
{
	int curve = GetAttributeInt(table, HAS + M_WEAPON_CURVATURE);
	int type = GetAttributeInt(table, HAS + M_WEAPON_TYPE);
	if (curve != WEAPON_CURVE || type != WEAPON_MEDIUM) return;

	SetModifierFromSourceDirect(table, FAST_STRIKE  + "_" + M_DAMAGE, PERK_VALUE_SABRE_HURRICANE, funcName);
	SetModifierFromSourceDirect(table, FORCE_STRIKE + "_" + M_DAMAGE, PERK_VALUE_SABRE_HURRICANE, funcName);
	SetModifierFromSourceDirect(table, FAST_STRIKE  + "_" + M_STRIKE_ANGLE, PERK_VALUE2_SABRE_HURRICANE, funcName);
	SetModifierFromSourceDirect(table, FORCE_STRIKE + "_" + M_STRIKE_ANGLE, PERK_VALUE2_SABRE_HURRICANE, funcName);
}

void Perk_PalaceGuard(ref chr, ref table, ref function, ref context, string funcName)
{
	int curve = GetAttributeInt(table, HAS + M_WEAPON_CURVATURE);
	int type = GetAttributeInt(table, HAS + M_WEAPON_TYPE);
	if (curve != WEAPON_CURVE || type != WEAPON_HEAVY) return;

	SetModifierFromSourceDirect(table, FAST_STRIKE  + "_" + M_DAMAGE, PERK_VALUE_PALACE_GUARD, funcName);
	SetModifierFromSourceDirect(table, FORCE_STRIKE + "_" + M_DAMAGE, PERK_VALUE_PALACE_GUARD, funcName);
	SetModifierFromSourceDirect(table, BREAK_STRIKE + "_" + M_DAMAGE, PERK_VALUE_PALACE_GUARD, funcName);
	SetModifierFromSourceDirect(table, ROUND_STRIKE + "_" + M_DAMAGE, PERK_VALUE2_PALACE_GUARD, funcName);
}

void Perk_Bayonet(ref chr, ref table, ref function, ref context, string funcName)
{
	float value = PERK_VALUE_BAYONET;
	if (HasDescriptor(table, "Baoynet")) value = PERK_VALUE2_BAYONET;

	SetModifierFromSourceDirect(table, MUSKET_ITEM_TYPE + "_" + FAST_STRIKE  + "_" + M_DAMAGE, value, funcName);
	SetModifierFromSourceDirect(table, MUSKET_ITEM_TYPE + "_" + FORCE_STRIKE + "_" + M_DAMAGE, value, funcName);
	SetModifierFromSourceDirect(table, MUSKET_ITEM_TYPE + "_" + ROUND_STRIKE + "_" + M_DAMAGE, value, funcName);
	SetModifierFromSourceDirect(table, MUSKET_ITEM_TYPE + "_" + BREAK_STRIKE + "_" + M_DAMAGE, value, funcName);
}

void Perk_DarkHorse(ref chr, ref table, ref function, ref context, string funcName)
{
	int amuletsCount = GetAttributeInt(table, "descriptors." + M_AMULET_TYPE + "_" + AMULET_COMMON);
	float value = PERK_VALUE_DARK_HORSE * amuletsCount;

	SetModifierFromSourceDirect(table, M_MTP_HP_MAX, value, funcName);
	SetModifierFromSourceDirect(table, M_MTP_ENERGY_MAX, value, funcName);
}

void Perk_HardHitter(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_HEAVY) return;

	SetModifierFromSourceDirect(table, BREAK_STRIKE + "_" + M_DAMAGE, PERK_VALUE_HARD_HITTER, funcName);
}

void Perk_Flanking(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_CURVATURE) != WEAPON_CURVE) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED, PERK_VALUE_FLANKING, funcName);
}

void Perk_CunningStrike(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_LIGHT) return;

	SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_CRIT_CHANCE, PERK_VALUE_CUNNING_STRIKE, funcName);
}


void Perk_TannedLeather(ref chr, ref table, ref function, ref context, string funcName)
{
	if (!HasPerk(chr, "TannedLeather")) return;
	if (GetAttributeIntOrDefault(table, HAS + M_ARMOR_TYPE, -1) != ARMOR_LIGHT) return;

	float allDefence = GetAttributeFloat(table, M_REDUCE_DAMAGE);
	float armorDefence = GetAttributeFloat(table, M_REDUCE_DAMAGE + ".cirass");
	float bonusArmor = armorDefence * PERK_VALUE_TANNED_LEATHER;
	SetAttribute(table, M_REDUCE_DAMAGE, allDefence + bonusArmor);
	SetAttribute(table, M_REDUCE_DAMAGE + ".cirass", armorDefence + bonusArmor);
}

void Perk_TieFit(ref chr, ref table, ref function, ref context, string funcName)
{
	if (!HasPerk(chr, "TieFit")) return;
	if (IsMainCharacter(chr))
	{
		SetModifierFromSourceDirect(table, SKILL_TYPE + SKILL_LEADERSHIP, GetAttributeInt(table, "descriptors.Fancy") * PERK_VALUE_TIE_FIT, funcName);
		SetModifierFromSourceDirect(table, SKILL_TYPE + SKILL_SNEAK, GetAttributeInt(table, "descriptors.Unremarkable") * PERK_VALUE_TIE_FIT, funcName);
	}
}

void Perk_Gossip(ref chr, ref table, ref function, ref context, string funcName)
{
	if (!HasPerk(chr, "Gossip")) return;
	int exoticQty = 0;
	if (IsMainCharacter(chr)) exoticQty = GetAttributeInt(table, "descriptors.Exotic");
	else if (IsCompanion(chr)) exoticQty = 1;
	else return;

	aref ptable = CT_GetTable(pchar, CT_EQUIP);
	SetModifierFromSourceDirect(&ptable, M_SQUADRON_POWER, exoticQty * PERK_VALUE_GOSSIP, funcName);
}


void Perk_Practice(ref chr, ref table, ref function, ref context, string funcName)
{
	int alchemyCount = GetAttributeInt(table, "descriptors.Alchemy");

	for (int i=1; i<15; i++)
	{
		string skillName = GetSkillNameByIdx(i);
		SetModifierFromSourceDirect(table, SKILL_TYPE + skillName, alchemyCount * PERK_VALUE_PRACTICE, funcName);
	}
}

void Perk_Collection(ref chr, ref table, ref function, ref context, string funcName)
{
	if (IsMainCharacter(chr)) return;
	int exoticCount = GetAttributeInt(table, "descriptors.Exotic");
	float value = exoticCount * PERK_VALUE2_COLLECTION;

	SetModifierFromSourceDirect(table, FAST_STRIKE  + "_" + M_DAMAGE, value, funcName);
	SetModifierFromSourceDirect(table, FORCE_STRIKE + "_" + M_DAMAGE, value, funcName);
	SetModifierFromSourceDirect(table, ROUND_STRIKE + "_" + M_DAMAGE, value, funcName);
	SetModifierFromSourceDirect(table, BREAK_STRIKE + "_" + M_DAMAGE, value, funcName);
	SetModifierFromSourceDirect(table, SHOT_STRIKE  + "_" + M_DAMAGE, value, funcName);
}

void Perk_Mule(ref chr, ref table, ref function, ref context, string funcName)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) == WEAPON_HEAVY)
	{
		SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED, PERK_VALUE2_MULE * -WEAPON_HEAVY_ATTACK_SPEED_MTP, funcName);
	}

	if (GetAttributeInt(table, HAS + M_ARMOR_TYPE) == ARMOR_HEAVY)
	{
		SetModifierFromSourceDirect(table, M_MOVE_SPEED, PERK_VALUE2_MULE * -ARMOR_HEAVY_MOVE_SPEED_MTP, funcName);
	}
}

void Perk_TieFitAlternate(ref chr, ref table, ref function, ref context, string funcName)
{
	if (IsMainCharacter(chr)) return;

	float weaponSpeedBonus = 0.0;
	float armorSpeedBonus = 0.0;
	switch (GetAttributeInt(table, HAS + M_WEAPON_TYPE))
	{
		case WEAPON_MEDIUM: weaponSpeedBonus = -WEAPON_MEDIUM_ATTACK_SPEED_MTP * PERK_VALUE2_TIE_FIT; break;
		case WEAPON_HEAVY:  weaponSpeedBonus = -WEAPON_HEAVY_ATTACK_SPEED_MTP  * PERK_VALUE2_TIE_FIT; break;
	}

	switch (GetAttributeInt(table, HAS + M_ARMOR_TYPE))
	{
		case ARMOR_MEDIUM: armorSpeedBonus = -ARMOR_MEDIUM_MOVE_SPEED_MTP * PERK_VALUE2_TIE_FIT; break;
		case ARMOR_HEAVY:  armorSpeedBonus = -ARMOR_HEAVY_MOVE_SPEED_MTP  * PERK_VALUE2_TIE_FIT; break;
	}

	if (weaponSpeedBonus > 0.0) SetModifierFromSourceDirect(table, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED, weaponSpeedBonus, "Perk_TieFit");
	if (armorSpeedBonus > 0.0)  SetModifierFromSourceDirect(table, M_MOVE_SPEED, armorSpeedBonus, "Perk_TieFit");
}