void Perk_Preaim(ref attacker, ref enemy, float damageMtp)
{
	if (IsMainCharacter(attacker)) return;
	if (!HasPerk(attacker, "Preaim")) return;
	if (LAi_GetCharacterRelHP(enemy) == 1) return;

	damageMtp += PERK_VALUE2_PREAIM;
}

void Perk_Muscles(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_HEAVY) return;

	float lessEnergy = PERK_VALUE_MUSCLES;
	AddToAttributeFloat(table, BLADE_ITEM_TYPE + M_ACTION_SPEED, PERK_VALUE2_MUSCLES);
}

void Perk_PerfectBalance(ref chr, ref table, ref function, ref context)
{
	int weaponType = GetAttributeInt(table, HAS + M_WEAPON_TYPE);
	if (weaponType != WEAPON_MEDIUM) return;

	AddToAttributeFloat(table, M_REDUCE_DAMAGE, PERK_VALUE_PERFECT_BALANCE);
}

void Perk_Heartbreaker(ref chr, ref table, ref function, ref context)
{
	int curve = GetAttributeInt(table, HAS + M_WEAPON_CURVATURE);
	int length = GetAttributeInt(table, HAS + M_WEAPON_LENGTH);
	if (curve != WEAPON_STRAIGHT || length != WEAPON_LONG) return;

	AddToAttributeFloat(table, FORCE_STRIKE + "_" + M_DAMAGE, PERK_VALUE_HEARTBREAKER);
	AddToAttributeFloat(table, FORCE_STRIKE + "_" + M_ACTION_SPEED, PERK_VALUE2_HEARTBREAKER);
}

void Perk_BladeDancer(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_CURVATURE) != WEAPON_CURVE) return;

	AddToAttributeFloat(table, ROUND_STRIKE + "_" + M_DAMAGE, PERK_VALUE_BLADE_DANCER);
}


void Perk_OttomanGrip(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_CURVATURE) != WEAPON_CURVE) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_OTTOMAN_GRIP);
}

void Perk_Puncher(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_CURVATURE) != WEAPON_STRAIGHT) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_PUNCHER);
}

void Perk_Dragoon(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_MEDIUM) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_DRAGOON);
}

void Perk_Virtuosity(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_LIGHT) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_VIRTUOSITY);
}

void Perk_Inertia(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_HEAVY) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_INERTIA);
}

void Perk_MeatGrinder(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_LENGTH) != WEAPON_SHORT) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_MEAT_GRINDER);
}

void Perk_Reach(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_LENGTH) != WEAPON_LONG) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_REACH);
}

void Perk_Stabbing(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_LENGTH) != WEAPON_SHORT) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_STABBING);
}

void Perk_NeckStrike(ref chr, ref table, ref function, ref context)
{
	if (GetAttributeInt(table, HAS + M_WEAPON_LENGTH) != WEAPON_LONG) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_DAMAGE, PERK_VALUE_NECK_STRIKE);
}

void Perk_Conquest(ref chr, ref table, ref function, ref context)
{
	int curve = GetAttributeInt(table, HAS + WEAPON_CURVE);
	int length = GetAttributeInt(table, HAS + M_WEAPON_LENGTH);
	if (curve != WEAPON_STRAIGHT || length != WEAPON_LONG) return;

	AddToAttributeFloat(table, FAST_STRIKE  + "_" + M_DAMAGE, PERK_VALUE_CONQUEST);
	AddToAttributeFloat(table, BREAK_STRIKE + "_" + M_DAMAGE, PERK_VALUE_CONQUEST);
}

void Perk_SabreHurricane(ref chr, ref table, ref function, ref context)
{
	int curve = GetAttributeInt(table, HAS + WEAPON_CURVE);
	int type = GetAttributeInt(table, HAS + M_WEAPON_TYPE);
	if (curve != WEAPON_CURVE || type != WEAPON_MEDIUM) return;

	AddToAttributeFloat(table, FAST_STRIKE  + "_" + M_DAMAGE, PERK_VALUE_SABRE_HURRICANE);
	AddToAttributeFloat(table, FORCE_STRIKE + "_" + M_DAMAGE, PERK_VALUE_SABRE_HURRICANE);
}

void Perk_PalaceGuard(ref chr, ref table, ref function, ref context)
{
	int curve = GetAttributeInt(table, HAS + WEAPON_CURVE);
	int type = GetAttributeInt(table, HAS + M_WEAPON_TYPE);
	if (curve != WEAPON_CURVE || type != WEAPON_HEAVY) return;

	AddToAttributeFloat(table, FAST_STRIKE  + "_" + M_DAMAGE, PERK_VALUE_PALACE_GUARD);
	AddToAttributeFloat(table, FORCE_STRIKE + "_" + M_DAMAGE, PERK_VALUE_PALACE_GUARD);
	AddToAttributeFloat(table, BREAK_STRIKE + "_" + M_DAMAGE, PERK_VALUE_PALACE_GUARD);
	AddToAttributeFloat(table, ROUND_STRIKE + "_" + M_DAMAGE, PERK_VALUE2_PALACE_GUARD);
}

void Perk_LeadRain(ref attacker, int nEnemies, ref damageMtp)
{
	if (nEnemies < 2) return;
	if (!HasPerk(attacker, "LeadRain")) return;

	damageMtp += PERK_VALUE_LEAD_RAIN * nEnemies;
}

void Perk_Reaper(ref attacker, string strikeType, ref critChance)
{
	if (!HasPerk(attacker, "Reaper")) return;

	if (strikeType == FAST_STRIKE) critChance += PERK_VALUE2_REAPER;
}

void Perk_Bayonet(ref chr, ref table, ref function, ref context)
{
	if (!HasPerk(chr, "Bayonet")) return;
	float value = PERK_VALUE_BAYONET;
	if (HasDescriptor(table, "Baoynet")) value = PERK_VALUE2_BAYONET;

	AddToAttributeFloat(table, MUSKET_ITEM_TYPE + "_" + FAST_STRIKE  + "_" + M_DAMAGE, value);
	AddToAttributeFloat(table, MUSKET_ITEM_TYPE + "_" + FORCE_STRIKE + "_" + M_DAMAGE, value);
	AddToAttributeFloat(table, MUSKET_ITEM_TYPE + "_" + ROUND_STRIKE + "_" + M_DAMAGE, value);
	AddToAttributeFloat(table, MUSKET_ITEM_TYPE + "_" + BREAK_STRIKE + "_" + M_DAMAGE, value);
}

void Perk_DarkHorse(ref chr, ref table, ref function, ref context)
{
	if (!HasPerk(chr, "DarkHorse")) return;
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_HEAVY) return;

	int amuletsCount = GetAttributeInt(table, "descriptors." + M_AMULET_TYPE + "_" + AMULET_COMMON);
	float value = PERK_VALUE_DARK_HORSE * amuletsCount;
	//JOKERTODO макс энергия AddToAttributeFloat(table, M_ENERGY_MAX, value);

	AddToAttributeFloat(table, M_MTP_HP_MAX, value);
}

void Perk_HardHitter(ref chr, ref table, ref function, ref context)
{
	if (!HasPerk(chr, "HardHitter")) return;
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_HEAVY) return;

	AddToAttributeFloat(table, BREAK_STRIKE + "_" + M_DAMAGE, PERK_VALUE_HARD_HITTER);
}

void Perk_Flanking(ref chr, ref table, ref function, ref context)
{
	if (!HasPerk(chr, "Flanking")) return;
	if (GetAttributeInt(table, HAS + M_WEAPON_CURVATURE) != WEAPON_CURVE) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED, PERK_VALUE_FLANKING);
}

void Perk_CunningStrike(ref chr, ref table, ref function, ref context)
{
	if (!HasPerk(chr, "CunningStrike")) return;
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_LIGHT) return;

	AddToAttributeFloat(table, BLADE_ITEM_TYPE + "_" + M_CRIT_CHANCE, PERK_VALUE_CUNNING_STRIKE);
}

void Perk_PowderFeel(ref item, ref resultQuantity)
{
	if (!HasPerk(pchar, "PowderFeel")) return;
	if (item.groupID != AMMO_ITEM_TYPE) return;
	resultQuantity = makeint(resultQuantity * (1 + PERK_VALUE_POWDER_FEEL));
}

void Perk_Sniper(ref attacker, ref enemy, string sBullet, int nShots)
{
	if (!HasPerk(attacker, "Sniper")) return;

	int value = 0;
	if (IsBulletGrape(sBullet)) value = (rand(1) + 1) * nShots;
	else value = rand(20) + 20;

	Lai_CharacterChangeEnergy(enemy, -value)
}

void Perk_TannedLeather(ref chr, ref table, ref function, ref context)
{
	if (!HasPerk(chr, "TannedLeather")) return;
	if (GetAttributeInt(table, HAS + M_ARMOR_TYPE) != ARMOR_LIGHT) return;

	float allDefence = GetAttributeFloat(table, M_REDUCE_DAMAGE);
	float armorDefence = GetAttributeFloat(table, M_REDUCE_DAMAGE + "source.armor");
	float bonusArmor = armorDefence * PERK_VALUE_TANNED_LEATHER;
	SetAttribute(table, M_REDUCE_DAMAGE, allDefence + bonusArmor);
	SetAttribute(table, M_REDUCE_DAMAGE + "source.armor", armorDefence + bonusArmor);
}

void Perk_TieFit(ref chr, ref table, ref function, ref context)
{
	if (!HasPerk(chr, "TieFit")) return;
	if (IsMainCharacter(chr))
	{
		AddToAttributeInt(table, SKILL_TYPE + SKILL_LEADERSHIP, GetAttributeInt(table, "descriptors.Fancy") * PERK_VALUE_TIE_FIT);
		AddToAttributeInt(table, SKILL_TYPE + SKILL_SNEAK, GetAttributeInt(table, "descriptors.Unremarkable") * PERK_VALUE_TIE_FIT);
	}
}

void Perk_Gossip(ref chr, ref table, ref function, ref context)
{
	if (!HasPerk(chr, "Gossip")) return;
	int exoticQty = 0;
	if (IsMainCharacter(chr)) exoticQty = GetAttributeInt(table, "descriptors.Exotic");
	else if (IsCompanion(chr)) exoticQty = 1;
	else return;

	aref ptable = CT_GetTable(pchar, CT_EQUIP);
	AddToAttributeFloat(&ptable, M_SQUADRON_POWER, exoticQty * PERK_VALUE_GOSSIP);
}

bool Perk_Sliding(ref attacker)
{
	if (!HasPerk(attacker, "sliding")) return false;
	if (!HasLightWeapon(attacker)) return false;

	return PercentChance(PERK_VALUE_SLIDING);
}

void Perk_Practice(ref chr, ref table, ref function, ref context)
{
	int alchemyCount = GetAttributeInt(table, "descriptors.Alchemy");

	for (int i=1; i<15; i++)
	{
		string skillName = GetSkillNameByIdx(i);
		AddToAttributeInt(table, SKILL_TYPE + skillName, alchemyCount * PERK_VALUE_PRACTICE);
	}
}

void Perk_Master(ref item, int qty)
{
	if (!HasPerk(pchar, "Master")) return;

	bool toolRequired = false;
	aref components;
	makearef(components, item.component);

	for(int i = 0; i < GetAttributesNum(components); i++)
	{
		string sAttr = "t" + (i + 1);
		string componentId = item.component.(sAttr).id;
		if (componentId == "alchemy_tool") toolRequired = true;
	}

	if (!toolRequired) return;

	float value = 0.01 * qty;
	IncreaseChrModifier(pchar, FAST_STRIKE  + "_" + M_DAMAGE, value, "perkMaster");
	IncreaseChrModifier(pchar, FORCE_STRIKE + "_" + M_DAMAGE, value, "perkMaster");
	IncreaseChrModifier(pchar, ROUND_STRIKE + "_" + M_DAMAGE, value, "perkMaster");
	IncreaseChrModifier(pchar, BREAK_STRIKE + "_" + M_DAMAGE, value, "perkMaster");
	IncreaseChrModifier(pchar, FEINT_STRIKE + "_" + M_DAMAGE, value, "perkMaster");
	IncreaseChrModifier(pchar, SHOT_STRIKE  + "_" + M_DAMAGE, value, "perkMaster");
}

void Perk_Kern(ref attacker, ref damageMtp)
{	
	if (!HasPerk(attacker, "Kern")) return;
	int nChargeMax = sti(attacker.chr_ai.gun.charge_max);
	int nChargeCur = makeint(stf(attacker.chr_ai.gun.charge)) + 1;	// прибавляем единицу, потому что только что отстрелили один
	log_Testinfo("патроны " + nChargeCur + "/" + nChargeMax);
	if(nChargeMax > nChargeCur)
		damageMtp += PERK_VALUE_KERN * (nChargeMax - nChargeCur);
}