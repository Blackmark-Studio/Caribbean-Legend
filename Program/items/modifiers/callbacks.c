void RunCharacterCallbacks(ref chr, string callbackName, ref table, ref context)
{
	if (!CheckAttribute(chr, "callbacks." + callbackName)) return;

	aref functionList;
	makearef(functionList, chr.callbacks.(callbackName));
	for (int i = 0; i < GetAttributesNum(functionList); i++)
	{
		aref rFunction = GetAttributeN(functionList, i);
		string sFunction = GetAttributeName(rFunction);
		call sFunction(chr, table, rFunction, context);
	}
}

// Ускоряем выпады прямым или удары кривым оружием
void CondottieresHat(ref chr, ref table, ref function, ref context)
{
	float value = stf(function.arg0);
	int weaponCurvature = GetAttributeInt(table, HAS + M_WEAPON_CURVATURE);

	string attackType;
	if (weaponCurvature == WEAPON_STRAIGHT) attackType = FAST_STRIKE;
	else if (weaponCurvature == WEAPON_CURVE) attackType = FORCE_STRIKE;
	else return;

	AddToAttributeFloat(table, attackType + "_" + M_ACTION_SPEED, value);
}

// Ускоряем выпады прямым или удары кривым оружием
void Battleaxe(ref chr, ref table, ref function, ref context)
{
	float value = stf(function.arg0);
	if (GetAttributeInt(table, HAS + M_WEAPON_TYPE) != WEAPON_HEAVY) return;

	AddToAttributeFloat(table, BREAK_STRIKE + "_" + M_DAMAGE, value);
}

// Ускоряем круговые удары коротким и пробивающие удары длинным
void CavaliersHat(ref chr, ref table, ref function, ref context)
{
	float value = stf(function.arg0);
	int weaponLength = GetAttributeInt(table, HAS + M_WEAPON_LENGTH);

	string attackType;
	if (weaponLength == WEAPON_SHORT) attackType = ROUND_STRIKE;
	else if (weaponLength == WEAPON_LONG) attackType = BREAK_STRIKE;
	else return;

	AddToAttributeFloat(table, attackType + "_" + M_ACTION_SPEED, value);
}

// Шляпа Грима
bool GrimHatSecondary(ref chr)
{
	if (GetCharacterEquipByGroup(chr, HAT_ITEM_TYPE) != "hat9") return false;
	if (!PercentChance(10)) return false;

	notification(StringFromKey("LAi_fightparams_1"), "Hat9");
	return true;
}

// Оберег Мария
bool TalismanMaria(ref chr)
{
	if (!IsCharacterEquippedArtefact(chr, "knife_02")) return false;
	if (!PercentChance(12)) return false;

	notification(StringFromKey("LAi_fightparams_1"), "None");
	return true;
}

// Пороховой тестер увеличивает урон пуль/картечи 
void GunpowderTester(ref chr, ref damageMtp, ref ammo)
{
	if (!IsCharacterEquippedArtefact(chr, "indian_2")) return;
	if (HasDescriptor(ammo, "GrapeAmmo") || HasDescriptor(ammo, "BulletAmmo")) damageMtp += 0.1;
	if (HasDescriptor(ammo, "EmpoweredAmmo") || HasDescriptor(ammo, "PiercingAmmo")) damageMtp += 0.05;
}

// Упырь ворует энергию
void Ghoul(ref attacker, ref enemy)
{
	if(!IsEquipCharacterByArtefact(attacker, "totem_11")) return;

	// CheckCharacterPerk(enemy, "HT1"))
	float fEnergyDrain = stf(enemy.chr_ai.energy) * 0.1;
	Lai_CharacterChangeEnergy(enemy, -fEnergyDrain);
	Lai_CharacterChangeEnergy(attacker, fEnergyDrain);
}

void VodkaEnergy(ref attacker, ref enemy)
{
	if(CheckAttribute(attacker, "VodkaEffect")) Lai_CharacterChangeEnergy(enemy, -0.1 * stf(enemy.chr_ai.energy));
}

// Восстанавливаем энергию за убийство
void CavaliersHatSecondary(ref chr)
{
	if (GetCharacterEquipByGroup(chr, HAT_ITEM_TYPE) != "hat2") return;

	chr.chr_ai.energy = stf(chr.chr_ai.energy) + stf(chr.chr_ai.energy)*0.25;
	notification(XI_ConvertString("Hat2 Hit"), "EnergyPlus");
}

// Восстанавливаем энергию за убийство
void TeresasHatSecondary(ref chr)
{
	if (GetCharacterEquipByGroup(chr, HAT_ITEM_TYPE) != "hat11") return;
	chr.chr_ai.energy = stf(chr.chr_ai.energy) + stf(chr.chr_ai.energy)*0.25;
	//notification(XI_ConvertString("Hat2 Hit"), "EnergyPlus");
}

//  Эль Трозо увеличивает скорость атаки по количеству шмоток с дескриптором "языческий"
void ElTrozo(ref chr, ref table, ref function, ref context)
{
	string modifierName = BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED;
	int amuletsCount = GetAttributeInt(table, "descriptors." + M_AMULET_TYPE + "_" + AMULET_PAGAN);
	float value = stf(function.arg0) * amuletsCount;
	AddToAttributeFloat(table, modifierName, value);
}

// Молитвослов снижает входящий урон огнестрела от церковных шмоток
void Euchologion(ref chr, ref table, ref function, ref context)
{
	string modifierName = RANGE + M_REDUCE_DAMAGE;
	int amuletsCount = GetAttributeInt(table, "descriptors." + M_AMULET_TYPE + "_" + AMULET_CHURCH);
	float value = stf(function.arg0) * amuletsCount;
	AddToAttributeFloat(table, modifierName, value);
}

// Экзотическое оружие наносит больше урона
void GoldenKnife(ref chr, ref table, ref function, ref context)
{
	if (!CheckAttribute(table, "descriptors.exotic.blade")) return;
	string modifierName = BLADE_ITEM_TYPE + "_" + M_DAMAGE;
	AddToAttributeFloat(table, modifierName, stf(function.arg0));
}

// Увеличиваем защиту ткани/кожи, улучшаем защиту сердца
void NgomboShield(ref chr, ref table, ref function, ref context)
{
	int armorMaterial = GetAttributeInt(table, HAS + M_ARMOR_MATERIAL);
	if (armorMaterial == ARMOR_FABRIC || armorMaterial == ARMOR_LEATHER)
	{
		float allDefence = GetAttributeFloat(table, M_REDUCE_DAMAGE);
		float armorDefence = GetAttributeFloat(table, M_REDUCE_DAMAGE + "source.armor");
		float bonusArmor = armorDefence * stf(function.arg0);
		SetAttribute(table, M_REDUCE_DAMAGE, allDefence + bonusArmor);
		SetAttribute(table, M_REDUCE_DAMAGE + "source.armor", armorDefence + bonusArmor);
	}

	if (HasDescriptor(table, "HeartDefence")) AddToAttributeFloat(table, M_REDUCE_CRIT_DAMAGE, stf(function.arg1));
}

void Jian(ref chr, ref table, ref function, ref context)
{
	int l = GetCharacterSkill(chr, "FencingL");
	int s = GetCharacterSkill(chr, "FencingS");
	int h = GetCharacterSkill(chr, "FencingH");
	if (l > s && l > h) chr.chr_ai.FencingType = "FencingL";
	else if (h > l && h > s) chr.chr_ai.FencingType = "FencingH";
	else 	chr.chr_ai.FencingType = "FencingS";
}

