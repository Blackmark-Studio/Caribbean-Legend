// Здесь коллбэки предметов, вызываемые через RunTableCallbacks
// Все они имеют единую сигнатуру и работают с модификаторами

// Ускоряем выпады прямым или удары кривым оружием
void CondottieresHat(ref chr, ref table, ref function, ref context, string funcName)
{
	float value = stf(function.arg0);
	int weaponCurvature = GetAttributeInt(table, HAS + M_WEAPON_CURVATURE);

	string attackType;
	if (weaponCurvature == WEAPON_STRAIGHT) attackType = FORCE_STRIKE;
	else if (weaponCurvature == WEAPON_CURVE) attackType = FAST_STRIKE;
	else return;

	SetModifierFromSourceDirect(table, attackType + "_" + M_DAMAGE, value, HAT_ITEM_TYPE);
}

// Ускоряем выпады прямым или удары кривым оружием
void Battleaxe(ref chr, ref table, ref function, ref context, string funcName)
{
	float value = stf(function.arg0);
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_HEAVY) return;

	IncreaseModifierFromSourceDirect(table, BREAK_STRIKE + "_" + M_DAMAGE, value, ITEM_SLOT_TYPE);
}

// Ускоряем круговые удары коротким и пробивающие удары длинным
void CavaliersHat(ref chr, ref table, ref function, ref context, string funcName)
{
	float value = stf(function.arg0);
	int weaponLength = GetAttributeInt(table, HAS + M_WEAPON_LENGTH);

	string attackType;
	if (weaponLength == WEAPON_SHORT) attackType = ROUND_STRIKE;
	else if (weaponLength == WEAPON_LONG) attackType = BREAK_STRIKE;
	else return;

	SetModifierFromSourceDirect(table, attackType + "_" + M_ACTION_SPEED, value, HAT_ITEM_TYPE);
}

//  Эль Трозо увеличивает скорость атаки по количеству шмоток с дескриптором "языческий"
void ElTrozo(ref chr, ref table, ref function, ref context, string funcName)
{
	string modifierName = BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED;
	int amuletsCount = GetAttributeInt(table, "descriptors." + M_AMULET_TYPE + "_" + AMULET_PAGAN);
	float value = stf(function.arg0) * amuletsCount;
	IncreaseModifierFromSourceDirect(table, modifierName, value, ITEM_SLOT_TYPE);
}

// Молитвослов снижает входящий урон огнестрела от церковных шмоток
void Euchologion(ref chr, ref table, ref function, ref context, string funcName)
{
	string modifierName = RANGE + M_REDUCE_DAMAGE;
	int amuletsCount = GetAttributeInt(table, "descriptors." + M_AMULET_TYPE + "_" + AMULET_CHURCH);
	float value = stf(function.arg0) * amuletsCount;
	if (ShipBonus2Artefact(chr, SHIP_GALEON_SM)) value *= 2;
	IncreaseModifierFromSourceDirect(table, modifierName, value, ITEM_SLOT_TYPE);
}

// Нательный крест уменьшает урон от критов
void Crucifix(ref chr, ref table, ref function, ref context, string funcName)
{
	float value = stf(function.arg0);
	if (ShipBonus2Artefact(chr, SHIP_GALEON_SM)) value = 0.20;
	IncreaseModifierFromSourceDirect(table, M_REDUCE_CRIT_DAMAGE, value, ITEM_SLOT_TYPE);
}

// Святая вода даёт макс хп
void HolyWater(ref chr, ref table, ref function, ref context, string funcName)
{
	float value = stf(function.arg0);
	if (ShipBonus2Artefact(chr, SHIP_GALEON_SM)) value = 0.25;
	IncreaseModifierFromSourceDirect(table, M_MTP_HP_MAX, value, ITEM_SLOT_TYPE);
}

// Экзотическое оружие наносит больше урона
void GoldenKnife(ref chr, ref table, ref function, ref context, string funcName)
{
	if (!CheckAttribute(table, "descriptors.exotic.blade")) return;
	string modifierName = BLADE_ITEM_TYPE + "_" + M_DAMAGE;
	SetModifierFromSourceDirect(table, modifierName, stf(function.arg0), TALISMAN_ITEM_TYPE);
}

// Легкое оружие наносит больше урона выпадами
void JaguarSon(ref chr, ref table, ref function, ref context, string funcName)
{
	float value = stf(function.arg0);
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_LIGHT) return;

	SetModifierFromSourceDirect(table, FORCE_STRIKE + "_" + M_DAMAGE, value, TALISMAN_ITEM_TYPE);
}

// Среднее оружие наносит больше урона круговыми ударами
void TasmanianDevil(ref chr, ref table, ref function, ref context, string funcName)
{
	float value = stf(function.arg0);
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_MEDIUM) return;

	SetModifierFromSourceDirect(table, ROUND_STRIKE + "_" + M_DAMAGE, value, TALISMAN_ITEM_TYPE);
}

// Увеличиваем защиту ткани/кожи, улучшаем защиту сердца
void NgomboShield(ref chr, ref table, ref function, ref context, string funcName)
{
	int armorMaterial = GetAttributeInt(table, HAS + M_ARMOR_MATERIAL);
	if (armorMaterial == ARMOR_FABRIC || armorMaterial == ARMOR_LEATHER)
	{
		float allDefence = GetAttributeFloat(table, M_REDUCE_DAMAGE);
		float armorDefence = GetAttributeFloat(table, M_REDUCE_DAMAGE + ".cirass");
		float bonusArmor = armorDefence * stf(function.arg0);
		SetAttribute(table, M_REDUCE_DAMAGE, allDefence + bonusArmor);
		SetAttribute(table, M_REDUCE_DAMAGE + ".cirass", armorDefence + bonusArmor);
	}

	if (HasDescriptor(table, "HeartDefence")) IncreaseModifierFromSourceDirect(table, M_REDUCE_CRIT_DAMAGE, stf(function.arg1), CIRASS_ITEM_TYPE);
}

// Книжка Аламиды увеличивает защиту и защиту от урона
void LiberMisericordiae(ref chr, ref table, ref function, ref context, string funcName)
{
	float reduceDamageValue = 0.05;
	int skillDefenceValue = 10;
	SetModifierFromSourceDirect(table, M_REDUCE_DAMAGE, reduceDamageValue, TALISMAN_ITEM_TYPE);

	// если книжка у ГГ
	if (IsMainCharacter(chr) && ShipBonus2Artefact(chr, SHIP_GALEON_SM))
	{
		SetModifierFromSourceDirect(table, SKILL_TYPE + SKILL_DEFENCE, skillDefenceValue, TALISMAN_ITEM_TYPE);
	}
	// если книжка у врача
	else if (pchar.Fellows.Passengers.doctor == chr.index && ShipBonus2Artefact(pchar, SHIP_GALEON_SM))
	{
		SetModifierFromSourceDirect(table, SKILL_TYPE + SKILL_DEFENCE, skillDefenceValue, TALISMAN_ITEM_TYPE);
	}
	// если книжка у компаньона
	else if (IsCompanion(chr))
	{
		if (GetCharacterShipType(chr) == SHIP_NOTUSED) return;
		if (!(sti(RealShips[sti(chr.Ship.Type)].BaseType) == SHIP_GALEON_SM)) return;
		SetModifierFromSourceDirect(table, SKILL_TYPE + SKILL_DEFENCE, skillDefenceValue, TALISMAN_ITEM_TYPE);
	}
}

void Jian(ref chr, ref table, ref function, ref context, string funcName)
{
	int l = GetCharacterSkill(chr, "FencingL");
	int s = GetCharacterSkill(chr, "FencingS");
	int h = GetCharacterSkill(chr, "FencingH");
	if (l > s && l > h) chr.chr_ai.FencingType = "FencingL";
	else if (h > l && h > s) chr.chr_ai.FencingType = "FencingH";
	else 	chr.chr_ai.FencingType = "FencingS";
}

void KaleucheAmuletAttack(ref chr, ref table, ref function, ref context, string funcName)
{
	int bonus;
	int base;
	float mtp = stf(function.arg0);
	base = sti(context.fencingl.base);
	bonus = makeint(base * mtp);
	context.fencingl = base + bonus;
	context.fencingl.talisman = bonus;

	base = sti(context.fencings.base);
	bonus = makeint(base * mtp);
	context.fencings = base + bonus;
	context.fencings.talisman = bonus;

	base = sti(context.fencingh.base);
	bonus = makeint(base * mtp);
	context.fencingh = base + bonus;
	context.fencingh.talisman = bonus;
}

void BlackwoodsCharter(ref chr, ref table, ref function, ref context, string funcName)
{
	float value = ArticlesBonus(chr) * 2;
	SetModifierFromSourceDirect(table, GRAPESHOT + "_" + M_DAMAGE, value, TALISMAN_ITEM_TYPE);
}