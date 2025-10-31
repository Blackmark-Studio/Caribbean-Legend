// Здесь функции предметов, вызываемые в соответствующих местах кода
// В основном тут то, что нет смысла/не получилось/не успели, перевести на модификаторы и коллбэки

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
	if (!IsEquipCharacterByArtefact(attacker, "totem_11")) return;

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

	float maxEnergy = stf(chr.chr_ai.energy_max);
	chr.chr_ai.energy = fClamp(1.0, maxEnergy, stf(chr.chr_ai.energy) + maxEnergy*0.25);
	notification(XI_ConvertString("Hat2 Hit"), "EnergyPlus");
}

// Восстанавливаем энергию за убийство
void TeresasHatSecondary(ref chr)
{
	if (GetCharacterEquipByGroup(chr, HAT_ITEM_TYPE) != "hat11") return;
	chr.chr_ai.energy = stf(chr.chr_ai.energy) + stf(chr.chr_ai.energy)*0.25;
	//notification(XI_ConvertString("Hat2 Hit"), "EnergyPlus");
}

// Наносим урон солдатской шляпе, чтобы она ломалась
void SoldiersHat(ref chr)
{
	if (GetCharacterEquipByGroup(chr, HAT_ITEM_TYPE) != "hat10") return;

	ref hat10 = ItemsFromID("hat10");
	if (!CheckAttribute(hat10, "durability")) return;

	int durability = sti(hat10.durability);
	if (durability < 2)
	{
		DeleteAttribute(hat10, "durability");
		RemoveCharacterEquip(chr, HAT_ITEM_TYPE);
		SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "UntieItem", 10);
		RemoveItems(chr, "hat10", 1);
		GiveItem2Character(chr, "hat10_part");
		CT_UpdateEquipTable(chr);
		CT_UpdateLandTable(chr);
		notification(StringFromKey("LAi_fightparams_2"), "ItemDestroy");
		return;
	}

	durability --;
	hat10.durability = durability;
}

// Вернем локализацию эффекта черепа Йорика в зависимости от того, в инвентаре он или нет
string GetYorickLoc(string prefix)
{
	object nullObj;
	string postfix = "InSlot";
	if (GetCharacterFreeItem(pchar, "talisman19")) postfix = "InInventory";
	return DLG_Convert("itm_stat" + prefix + "_talisman19_" + postfix, "ItemsStats.txt", &nullObj);
}