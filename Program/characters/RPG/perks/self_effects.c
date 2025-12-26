// Здесь функции личных перков, вызываемые в соответствующих местах кода
// В основном тут то, что нет смысла/не получилось/не успели, перевести на модификаторы и коллбэки

void Perk_Preaim(ref attacker, ref enemy, ref damageMtp)
{
	if (IsMainCharacter(attacker)) return;
	if (!HasPerk(attacker, "Preaim")) return;
	if (LAi_GetCharacterRelHP(enemy) == 1) return;

	damageMtp += PERK_VALUE2_PREAIM;
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

bool Perk_Sliding(ref attacker)
{
	if (!HasPerk(attacker, "sliding")) return false;
	if (!HasLightWeapon(attacker)) return false;

	return fPercentChance(PERK_VALUE_SLIDING);
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
		if (componentId == "alchemy_tool")       toolRequired = true;
		else if (componentId == "Tailor_Tool")   toolRequired = true;
		else if (componentId == "Mechanic_Tool") toolRequired = true;
	}

	if (!toolRequired) return;

	float value = PERK_VALUE_MASTER * qty;
	IncreaseChrModifier(pchar, FAST_STRIKE  + "_" + M_DAMAGE, value, "Perk_Master");
	IncreaseChrModifier(pchar, FORCE_STRIKE + "_" + M_DAMAGE, value, "Perk_Master");
	IncreaseChrModifier(pchar, ROUND_STRIKE + "_" + M_DAMAGE, value, "Perk_Master");
	IncreaseChrModifier(pchar, BREAK_STRIKE + "_" + M_DAMAGE, value, "Perk_Master");
	IncreaseChrModifier(pchar, SHOT_STRIKE  + "_" + M_DAMAGE, value, "Perk_Master");
	
	if(!CheckAttribute(pchar, "achievment.Perk_Master"))
		pchar.achievment.Perk_Master = 0;
	pchar.achievment.Perk_Master = sti(pchar.achievment.Perk_Master) + qty;
	if(sti(pchar.achievment.Perk_Master) >= 100) Achievment_Set("ach_CL_182");
	
    // belamour на случай стата в стиме
	/* int statSteam = GetStat("stat_CL_175");
	int statProfile = sti(pchar.achievment.Perk_Master) + qty;
	if(statProfile > statSteam)
	{
		Achievment_SetStat(175, statProfile - statSteam);
	} */
}

void Perk_Kern(ref attacker, ref damageMtp)
{	
	if (!HasPerk(attacker, "Kern")) return;
	int nChargeMax = GetAttributeInt(attacker, "chr_ai.gun.charge_max");
	int nChargeCur = GetattributeInt(attacker, "chr_ai.gun.charge") + 1;	// прибавляем единицу, потому что только что отстрелили один
	log_Testinfo("патроны " + nChargeCur + "/" + nChargeMax);
	if(nChargeMax > nChargeCur)
		damageMtp += PERK_VALUE_KERN * (nChargeMax - nChargeCur);
}

void Perk_MasterAlternate(ref chr)
{
	if (IsMainCharacter(chr) || !HasPerk(chr, "Master")) return;
	IncreaseLandModifier(chr, FAST_STRIKE  + "_" + M_DAMAGE, PERK_VALUE2_MASTER, "Perk_Master");
	IncreaseLandModifier(chr, FORCE_STRIKE + "_" + M_DAMAGE, PERK_VALUE2_MASTER, "Perk_Master");
	IncreaseLandModifier(chr, ROUND_STRIKE + "_" + M_DAMAGE, PERK_VALUE2_MASTER, "Perk_Master");
	IncreaseLandModifier(chr, BREAK_STRIKE + "_" + M_DAMAGE, PERK_VALUE2_MASTER, "Perk_Master");
	IncreaseLandModifier(chr, SHOT_STRIKE  + "_" + M_DAMAGE, PERK_VALUE2_MASTER, "Perk_Master");
}

string PerkMasterDescription(ref chr)
{
	string key = "perkMaster";
	if (!IsMainCharacter(chr)) key += "_alternate";
	string baseText = DLG_Convert(key, "AbilityDescribe.txt", &NullObject);

	float bonus = GetAttributeFloat(chr, "ct.static.fast_Damage.perk_master");
	if (bonus == 0) return baseText;

	return baseText + " " + DLG_Convert("perkMaster_currentBonus", "AbilityDescribe.txt", chr);
}