float LAi_CalcMeleeDamage(ref attacker, ref weapon, string attackType)
{
	float dmgMin = stf(weapon.Attack.(attackType).min);
	float dmgMax = stf(weapon.Attack.(attackType).max);
	float strikeDamage = dmgMin + (dmgMax - dmgMin)*frandSmall(1.0); // урон оружия для типа удара
	float skillMtp = DamageSkillMtp(attacker, "melee");              // влияние умения фехтования

	return strikeDamage * skillMtp;
}

//Энергия, необходимая для запуска действия
float LAi_CalcUseEnergyForBlade(aref character, string actionType)
{
	float energy = 0.0;
	
	switch(actionType)
	{
		case "fast":
			energy = 10.0;
		break;
		case "force":
			energy = 7.0;
		break;
		case "round":
			energy = 18.0;
		break;
		case "break":
			energy = 14.0;
		break;
		case "hit_parry":  // boal fix эту энергию тратит не атакующий, а атакуемый в анимации fgt_hit_parry
			energy = 20.0;
			if (HasPerk(&character, "Exhaustion") && HasLightWeapon(&character)) energy *= (1+PERK_VALUE_EXHAUSTION);
			else if (CheckAttribute(character, "animal")) energy = 0.0;
		break;
		case "feintc":
			energy = 7.0; // расход при успехе финта
		break;
	}
	
	if(energy > 0)  // оптимизация
	{
		float fSkill = LAi_GetCharacterFightLevel(character);  
		fSkill = 1.0 - (0.3 * fSkill);
		float fWeapon = 1.0;
		if(CharUseMusket(character))
		{
			ref rItm = ItemsFromID(GetCharacterEquipByGroup(character, MUSKET_ITEM_TYPE));
			if(IsCharacterPerkOn(character, "HT4"))
				fWeapon = stf(rItm.weight) * 0.1;
			else
				fWeapon = stf(rItm.weight) * 0.1 + 0.4;
		}
		else	
			fWeapon = LAi_GetBladeEnergyType(character);

		energy = energy * fSkill * fWeapon;
	}
	
	return energy;
}

void LAi_ApplyCharacterAttackDamage(ref attacker, ref enemy, string strikeType, bool isBlocked, bool isBackstab, bool isMiniStrike)
{
	if (LAi_IsImmortal(enemy)) return;                            // неубиваемый, то нетрогаем его
	if (isBlocked && !CheckAttribute(attacker, "animal")) return; // удар заблокирован

	aref aTable = InitTableForFight(attacker);
	aref eTable = InitTableForFight(enemy);
	string weaponType;
	ref weapon = LAi_GetCurrentWeapon(attacker, &weaponType, "melee");                // получили оружие: клинок или мушкет
	float damage = LAi_CalcMeleeDamage(attacker, weapon, &strikeType);                // урон оружия для типа удара в наших руках
	float damageMtp = 1 + GetDamageMtp(&aTable, &strikeType, weaponType);             // мультипликатор урона по умолчанию 1
	if (isBackstab) damageMtp += GetStabMtp(attacker);                                // мультипликатор удара в спину
	if (!LAi_IsGroupDamagableEnemy(attacker, enemy)) return;                          // проверка ударов по своим
	bool isCrit = false;
	ModifyDamageMtpByCrit(attacker, enemy, &aTable, &eTable, weaponType, strikeType, &damageMtp, &isCrit); // крит попадание
	ModifyBladeDamageByQuestSituations(attacker, enemy, &damageMtp);                  // особые ситуации
	damageMtp -= GetDamageReduction(&eTable);                                         // вражеское снижение урона
	if (isMiniStrike) damageMtp -= 0.7;                                               // если пробили ложным ударом фехтовальщика, а блока и не было

	float resultDamage = damage * func_fmax(0.0, damageMtp);                          // итого базовый урон * мультипликатор
	
	if(isBackstab && sti(attacker.index) == GetMainCharacterIndex())
		Achievment_SetStat(187, 1);

	if (IsDummy(attacker) || IsDummy(enemy))
	{
		if(bDrawBars)
			SendMessage(enemy, "lfff", MSG_CHARACTER_VIEWDAMAGE, resultDamage, stf(enemy.chr_ai.hp), stf(enemy.chr_ai.hp_max));
		return;
	}
	LAi_ApplyCharacterDamage(enemy, MakeInt(resultDamage + 0.5), "fight", isCrit);
	MakePoisonAttackCheckSex(attacker, enemy, &aTable, &eTable);
	LAi_CheckKillCharacter(enemy);

	Ghoul(attacker, enemy);
	SoldiersHat(enemy);
	if (weaponType == MUSKET_ITEM_TYPE) VodkaEnergy(attacker, enemy);
	// яд таино // Addon 2016-1 Jason Пиратская линейка
	if (IsCharacterEquippedArtefact(attacker, "indian_poison")) MakeIndianPoisonAttack(enemy, attacker);
	if (CheckAttribute(attacker, "cheats.indian_poison")) MakeIndianPoisonAttack(enemy, attacker);

	bool isSetBlade = LAi_IsArmed(enemy); //Есть ли оружие у цели
	bool isDead = LAi_IsDead(enemy);

	if (isSetBlade) ApplyExpFromStrike(attacker, enemy, isDead, strikeType, weaponType, isBlocked, resultDamage);
	if (!isDead) return;

	if (GetCharacterEquipByGroup(attacker, BLADE_ITEM_TYPE) == "khopesh1") ChickenGod_KhopeshKill(attacker);
	CavaliersHatSecondary(attacker);
	TeresasHatSecondary(attacker);
	Statistic_KillChar(attacker, enemy, "_s");
	LAi_SetResultOfDeath(attacker, enemy, isSetBlade);
}

// Это можно было бы сделать модификаторами персонажей, но нужны уведомления
// С появлением событий-на-персонаже можно будет убрать туда
void ModifyBladeDamageByQuestSituations(ref attacker, ref enemy, ref damageMtp)
{
	// Jason: трехкратный урон дагой Коготь Вождя для нежити. Ставить атрибут .monster нужным НПС, если группа не monsters
	bool bMonster = (CheckAttribute(enemy, "monster")) || (enemy.chr_ai.group == LAI_GROUP_MONSTERS);
	if (IsEquipCharacterByArtefact(attacker, "knife_01") && bMonster)
	{
		damageMtp += 2;
	}
	// группа монстров Ксочитэма - плохо бьются простым оружием, хорошо - Когтем вождя 210712
	if (enemy.chr_ai.group == "KSOCHITAM_MONSTERS")
	{
		if (IsEquipCharacterByArtefact(attacker, "knife_01")) damageMtp += 3;
		else damageMtp = 0.25;
	}
	if (CheckAttribute(attacker, "cheats.bladedamage")) damageMtp += 9;
	if (CheckAttribute(enemy, "GuardMask") && !IsEquipCharacterByArtefact(attacker, "knife_01"))
	{
		damageMtp = 0;
		if (IsMainCharacter(attacker)) log_info(XI_ConvertString("Gun1"));
	}
	// калеуче
	bool bTutt = (IsCharacterEquippedArtefact(attacker, "kaleuche_amulet2")) || (IsCharacterEquippedArtefact(attacker, "kaleuche_amulet3"));
	if (CheckAttribute(enemy, "KhaelRoaMonster") && !bTutt)
	{
		damageMtp = 0;
		if (IsMainCharacter(attacker)) log_info(XI_ConvertString("Gun2"));
	}
	if (CheckAttribute(attacker, "KhaelRoaMonster") && !bTutt) 
	{
		damageMtp += 4;
	}
	if(enemy.id == "Mishelle")
	{
		if(GetCharacterEquipByGroup(attacker, BLADE_ITEM_TYPE) == "khopesh1") damageMtp += 0.2;
		if(GetCharacterEquipByGroup(attacker, BLADE_ITEM_TYPE) == "khopesh2") damageMtp += 1.0;
		if(GetCharacterEquipByGroup(attacker, BLADE_ITEM_TYPE) == "khopesh3") damageMtp += 0.4;
	}
}