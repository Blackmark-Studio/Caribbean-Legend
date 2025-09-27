// Здесь таблица с эффектами персонажа для суши
void CT_UpdateLandTable(ref chr)
{
	trace("Recalculate land modifiers for "+chr.name);

	DeleteAttribute(chr, "ct."+CT_LAND);
	aref landTable = CT_GetTable(chr, CT_LAND);
	aref equipTable = CT_GetTable(chr, CT_EQUIP);
	string bladeId = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
	if (bladeId == "") return;
	ref blade = ItemsFromID(bladeId);

	bool hasMusket = IsMusketer(chr);
	landTable.hasMusket = hasMusket;

	CT_SetWeaponDamageCoeff(&landTable, &equipTable, chr, blade);
	if (hasMusket) CT_SetMusketDamageCoeff(&landTable, &equipTable, chr);

	CT_SetAllCritChance(&landTable, &equipTable, chr, hasMusket);
	CT_SetAllCritDamage(&landTable, &equipTable, chr, hasMusket);
	CT_SetAllHeadshotDamage(&landTable, &equipTable, chr, hasMusket);
	CT_SetDefence(&landTable, &equipTable, chr);
	CT_SetCritDefence(&landTable, &equipTable, chr);
	CT_SetAllAttackSpeed(&landTable, &equipTable, chr, blade);
	CT_SetAllMoveSpeed(&landTable, &equipTable, chr);
	CT_SetAllReloadSpeed(&landTable, &equipTable, chr);
	CT_SetPoisonAttack(&landTable, &equipTable, chr);
	CT_SetMaxHealth(&landTable, &equipTable, chr);
	CT_SetStaggerSpeed(&landTable, &equipTable, chr, hasMusket);

	// мультифайтер
	if (CheckAttribute(chr, "MultiFighter")) AddToAttributeFloat(landTable, BLADE_ITEM_TYPE + "" + M_DAMAGE, stf(chr.MultiFighter));
}

void CT_SetMaxHealth(ref landTable, ref equipTable, ref chr)
{
	float baseHp = GetCharacterBaseHPValue(chr) + (stf(chr.rank)-1) * GetCharacterAddHPValue(chr);
	float bonusHp = GetAttributeFloat(equipTable, M_HP_MAX);
	float bonusMtp = GetAttributeFloat(equipTable, M_MTP_HP_MAX);

	chr.chr_ai.hp_max = (baseHp + bonusHp) * (1 + bonusMtp);
	SetAttribute(landTable, M_HP_MAX, bonusHp);
	SetAttribute(landTable, M_MTP_HP_MAX, bonusMtp);
}

void CT_SetAllMoveSpeed(ref landTable, ref equipTable, ref chr)
{
	float moveSpeed = GetAttributeFloatOrDefault(chr, "baseMoveSpeed", 1.0);
	float mtp = 1.0 + (GetAttributeFloat(equipTable, M_MOVE_SPEED));
	CT_SetMoveSpeed(landTable, equipTable, chr, moveSpeed, mtp, RUN_MOVE);
	CT_SetMoveSpeed(landTable, equipTable, chr, moveSpeed, mtp, WALK_MOVE);
	CT_SetMoveSpeed(landTable, equipTable, chr, moveSpeed, mtp, MUSKET_RUN_MOVE);
	CT_SetMoveSpeed(landTable, equipTable, chr, moveSpeed, mtp, AIMING_WALK_MOVE);
	CT_SetMoveSpeed(landTable, equipTable, chr, moveSpeed, mtp, SPRINT_MOVE);
}

void CT_SetMoveSpeed(ref landTable, ref equipTable, ref chr, float baseSpeed, float mtp, string animation)
{
	baseSpeed *= (mtp + GetAttributeFloat(equipTable, animation + "_" + M_ACTION_SPEED));
	SetCharacterActionSpeed(chr, animation, baseSpeed);
	SetAttribute(landTable, animation + "_" + M_ACTION_SPEED, baseSpeed);
}

void CT_SetAllHeadshotDamage(ref landTable, ref equipTable, ref chr, bool hasMusket)
{
	float mtp = HEADSHOT_MTP;
	mtp += GetAttributeFloat(equipTable, M_HEADSHOT_DAMAGE);
	if(IsCharacterEquippedArtefact(chr, "talisman20")) mtp += 0.2;
	SetAttribute(landTable, M_HEADSHOT_DAMAGE, mtp);
}

void CT_SetPoisonAttack(ref landTable, ref equipTable, ref chr)
{
	SetAttribute(landTable, M_POISON_CHANCE, GetAttributeFloat(equipTable, M_POISON_CHANCE));
}

void CT_SetAllReloadSpeed(ref landTable, ref equipTable, ref chr)
{
	float mtp;
	
	string modifier = GUN_ITEM_TYPE + "_" + M_RELOAD_SPEED;
	mtp = 1 + GetAttributeFloat(equipTable, modifier);
	if (CheckAttribute(chr, "MultiShooter")) mtp += 2.00;
	if(IsMainCharacter(chr) && IsCharacterEquippedArtefact(chr, "talisman20")) mtp += 0.1;
	SetAttribute(landTable, modifier, mtp);
	if (landTable.hasMusket != "1") return;

	mtp = 1 + GetAttributeFloat(equipTable, modifier);
	modifier = MUSKET_ITEM_TYPE + "_" + M_RELOAD_SPEED;
	SetAttribute(landTable, modifier, mtp);
}

void CT_SetAllAttackSpeed(ref landTable, ref equipTable, ref chr, ref blade)
{
	float baseSpeed =  GetAttributeFloatOrDefault(chr, "baseAttackSpeed", 1.0);

	float mtp = 1.0 + (GetAttributeFloat(equipTable, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED));
	mtp += GetAttributeFloat(equipTable, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED);
	if(GetCharacterEquipByGroup(chr, HAT_ITEM_TYPE) == "hat11")
	{
		if(CheckAttribute(chr, "hat11_bonus")) mtp += 0.05;
	}
	CT_SetAttackSpeed(landTable, equipTable, chr, baseSpeed, mtp, FORCE_STRIKE);
	CT_SetAttackSpeed(landTable, equipTable, chr, baseSpeed, mtp, FAST_STRIKE);
	CT_SetAttackSpeed(landTable, equipTable, chr, baseSpeed, mtp, ROUND_STRIKE);
	CT_SetAttackSpeed(landTable, equipTable, chr, baseSpeed, mtp, BREAK_STRIKE);
	CT_SetAttackSpeed(landTable, equipTable, chr, baseSpeed, mtp, FEINT_STRIKE);
}

void CT_SetAttackSpeed(ref landTable, ref equipTable, ref chr, float baseSpeed, float mtp, string type)
{
	string modifier = type + "_" + M_ACTION_SPEED;
	float value = baseSpeed * (mtp + (GetAttributeFloat(equipTable, modifier)));
	SetAttribute(landTable, modifier, value);
	SetCharacterActionSpeed(chr, type, value);
}

void CT_SetAllCritChance(ref landTable, ref equipTable, ref chr, bool hasMusket)
{
	float chance = BASE_CRIT_CHANCE;
	float skillBonus = (GetCharacterSkill(chr, SPECIAL_L) + GetCharacterSkill(chr, SPECIAL_P)) * 0.005;
	chance += skillBonus;
	CT_SetCritModifier(chance, BLADE_ITEM_TYPE,  M_CRIT_CHANCE, &landTable, &equipTable, chr);
	CT_SetCritModifier(chance, GUN_ITEM_TYPE,    M_CRIT_CHANCE, &landTable, &equipTable, chr);
	if (!hasMusket) return;
	CT_SetCritModifier(chance, MUSKET_ITEM_TYPE, M_CRIT_CHANCE, &landTable, &equipTable, chr);
}

void CT_SetAllCritDamage(ref landTable, ref equipTable, ref chr, bool hasMusket)
{
	float multipler = CRIT_MTP;
	CT_SetCritModifier(multipler, BLADE_ITEM_TYPE,  M_CRIT_DAMAGE, &landTable, &equipTable, chr);
	CT_SetCritModifier(multipler, GUN_ITEM_TYPE,    M_CRIT_DAMAGE, &landTable, &equipTable, chr);
	if (!hasMusket) return;
	CT_SetCritModifier(multipler, MUSKET_ITEM_TYPE, M_CRIT_DAMAGE, &landTable, &equipTable, chr);
}

void CT_SetCritModifier(float value, string weapon, string modifier, ref landTable, ref equipTable, ref chr)
{
	value += GetAttributeFloat(equipTable, weapon + "_" + modifier);
	SetAttribute(landTable, weapon + "_" + modifier, value);
}

void CT_SetDefence(ref landTable, ref equipTable, ref chr)
{
	float damageReduction = GetAttributeFloat(equipTable, M_REDUCE_DAMAGE);
	if (CheckAttribute(chr,"ReducedDamage")) damageReduction += 1.0-makefloat(chr.ReducedDamage); // квестовое снижение урона

	if (damageReduction > 0) SetAttribute(landTable, M_REDUCE_DAMAGE, damageReduction);

	damageReduction = GetAttributeFloat(equipTable, RANGE + M_REDUCE_DAMAGE);
	if (damageReduction > 0) SetAttribute(landTable, RANGE + M_REDUCE_DAMAGE, damageReduction);
}

void CT_SetCritDefence(ref landTable, ref equipTable, ref chr)
{
	float critDamageReduction = GetAttributeFloat(equipTable, M_REDUCE_CRIT_DAMAGE);
	if (critDamageReduction > 0) SetAttribute(landTable, M_REDUCE_CRIT_DAMAGE, critDamageReduction);
}

// Устанавливаем коэффициент повреждений от типов удара с учётом типа оружия
void CT_SetWeaponDamageCoeff(ref landTable, ref equipTable, ref chr, ref blade)
{
	int weaponType = GetAttributeInt(equipTable, HAS + M_WEAPON_TYPE);
	float commonBonus =  GetAttributeFloat(equipTable, BLADE_ITEM_TYPE + "_" + M_DAMAGE);

	// Бонусы по типам удара
	float fastBonus  = commonBonus;
	float forceBonus = commonBonus;
	float roundBonus = commonBonus;
	float breakBonus = commonBonus;
	float shotBonus = commonBonus;

	CT_AddEquipCoeffBonuses(equipTable, "", &fastBonus, &forceBonus, &roundBonus, &breakBonus, &shotBonus);
	CT_AddEquipCoeffBonuses(equipTable, weaponType, &fastBonus, &forceBonus, &roundBonus, &breakBonus, &shotBonus);

	if (fastBonus  > 0) SetAttribute(landTable, FAST_STRIKE  + "_" + M_DAMAGE, fastBonus);
	if (forceBonus > 0) SetAttribute(landTable, FORCE_STRIKE + "_" + M_DAMAGE, forceBonus);
	if (roundBonus > 0) SetAttribute(landTable, ROUND_STRIKE + "_" + M_DAMAGE, roundBonus);
	if (breakBonus > 0) SetAttribute(landTable, BREAK_STRIKE + "_" + M_DAMAGE, breakBonus);
	if (shotBonus > 0)  SetAttribute(landTable, SHOT_STRIKE  + "_" + M_DAMAGE, shotBonus);
}

void CT_SetMusketDamageCoeff(ref table, ref equipTable, ref chr)
{
	float commonBonus = GetAttributeFloat(equipTable, BLADE_ITEM_TYPE + "_" + M_DAMAGE);
	float fastBonus  = commonBonus;
	float forceBonus = commonBonus;
	float roundBonus = commonBonus;
	float breakBonus = commonBonus;
	float shotBonus = commonBonus;
	
	if(CheckAttribute(chr, "VodkaEffect"))
	{
		fastBonus  += 0.4;
		forceBonus += 0.2;
		roundBonus += 0.2;
		breakBonus += 0.2;
	}

	CT_AddEquipCoeffBonuses(equipTable, MUSKET_ITEM_TYPE, &fastBonus, &forceBonus, &roundBonus, &breakBonus, &shotBonus);

	if (fastBonus  > 0) SetAttribute(table, MUSKET_ITEM_TYPE + "_" + FAST_STRIKE  + "_" + M_DAMAGE, fastBonus);
	if (forceBonus > 0) SetAttribute(table, MUSKET_ITEM_TYPE + "_" + FORCE_STRIKE + "_" + M_DAMAGE, forceBonus);
	if (roundBonus > 0) SetAttribute(table, MUSKET_ITEM_TYPE + "_" + ROUND_STRIKE + "_" + M_DAMAGE, roundBonus);
	if (breakBonus > 0) SetAttribute(table, MUSKET_ITEM_TYPE + "_" + BREAK_STRIKE + "_" + M_DAMAGE, breakBonus);
	if (shotBonus > 0)  SetAttribute(table, MUSKET_ITEM_TYPE + "_" + SHOT_STRIKE  + "_" + M_DAMAGE, shotBonus);
}

void CT_AddEquipCoeffBonuses(ref equipTable, string weaponType, float fastBonus, float forceBonus, float roundBonus, float breakBonus, float shotBonus)
{
	if (weaponType != "") weaponType += "_";
	fastBonus  += GetAttributeFloat(equipTable, weaponType + FAST_STRIKE  + "_" + M_DAMAGE);
	forceBonus += GetAttributeFloat(equipTable, weaponType + FORCE_STRIKE + "_" + M_DAMAGE);
	roundBonus += GetAttributeFloat(equipTable, weaponType + ROUND_STRIKE + "_" + M_DAMAGE);
	breakBonus += GetAttributeFloat(equipTable, weaponType + BREAK_STRIKE + "_" + M_DAMAGE);
	shotBonus  += GetAttributeFloat(equipTable, weaponType + SHOT_STRIKE  + "_" + M_DAMAGE);
}

void CT_SetStaggerSpeed(ref landTable, ref equipTable, ref chr, bool hasMusket)
{
	float mtp = 1.0;
	
	if(hasMusket && IsMainCharacter(chr) && CheckAttribute(chr, "VodkaEffect"))
		mtp += 0.33;
	SetAttribute(landTable, M_STAGGER_SPEED, mtp);
	SetCharacterActionSpeed(chr, "hit", mtp);
}