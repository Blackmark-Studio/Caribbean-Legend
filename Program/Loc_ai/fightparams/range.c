float LAi_GunCalcDamage(ref attacker, ref enemy, string sBullet, string sType, int nShots)
{
	float min = 10.0;
	float max = 10.0;

	if(!IsBulletGrape(sBullet))
	{
		if(sBullet == "powder_pellet") LaunchBlastPellet(enemy);
		if(sBullet == "grenade") LaunchBlastGrenade(enemy);
		
		min = stf(attacker.chr_ai.(sType).DmgMin);
		max = stf(attacker.chr_ai.(sType).DmgMax);
	}

	float aSkill = DamageSkillMtp(attacker, "range"); //Учитываем скилы

	float shotDamage;
	if(IsBulletGrape(sBullet))
	{
		shotDamage = stf(attacker.chr_ai.(sType).basedmg) * nShots;
		shotDamage *= Bring2Range(0.75, 1.5, 0.0, 1.0, aSkill);
	}
	else
		shotDamage = min + (max - min)*frandSmall(aSkill);

	return shotDamage;
}

//Расчитать полученный опыт при попадании из пистолета - evganat - переделал
float LAi_GunCalcDamageExperience(ref attack, ref enemy, float dmg, bool isHeadShot)
{
	float hp = stf(enemy.chr_ai.hp);
	if(dmg > hp)
		dmg = hp;
	float exp = dmg * 0.08;
	if(isHeadShot)
		exp *= 1.5;
	return LAi_GunCalcExperience(attack, enemy, exp);
}

float LAi_GunCalcKillExperience(ref attack, ref enemy)
{
	return LAi_GunCalcExperience(attack, enemy, 20.0);
}

float LAi_GunCalcExperience(ref attack, ref enemy, float exp)
{
	int attackRank = sti(attack.rank);
	int enemyRank = sti(enemy.rank);
	float kRank = 1.0 + (enemyRank - attackRank) * 0.1;
	if(kRank > 1.6)
		kRank = 1.6;
	else
	{
		if(kRank < 0.4)
			kRank = 0.4;
	}
	exp *= kRank;
	
	if(CheckAttribute(enemy, "City"))
		exp *= 0.1;
	return exp;
}

//Расчитаем текущую скорость перезарядки пистолета
float LAi_GunReloadSpeed(ref chr, string sType)
{
	float charge_dlt = LAI_DEFAULT_DLTCHRG;
	if (CheckAttribute(chr, "chr_ai." + sType + ".charge_dlt"))
	{
		charge_dlt = stf(chr.chr_ai.(sType).charge_dlt);
	}

	aref landTable = CT_GetTable(chr, CT_LAND);
	charge_dlt *= GetReloadSpeed(landTable, sType);
	return charge_dlt;
}

//Начисление повреждений при попадании
void LAi_ApplyCharacterFireDamage(ref attacker, ref enemy, int nEnemies, float fAimingTime, bool isHeadShot, int nShots)
{
	if (LAi_IsImmortal(enemy)) return; // Если неубиваемый, то нетрогаем его
	if (GrimHatSecondary(enemy)) return;
	if (TalismanMaria(enemy)) return;
	string weaponType;
	aref aTable = InitTableForFight(attacker);
	aref eTable = InitTableForFight(enemy);

	ref rItm = LAi_GetCurrentWeapon(attacker, &weaponType, "range");
	string sBullet = LAi_GetCharacterBulletType(attacker, weaponType);              // получаем боеприпас
	ref rAmmo = ItemsFromId(sBullet);
	float damage = LAi_GunCalcDamage(attacker, enemy, sBullet, weaponType, nShots);  // базовый урон

	//Аттака своей группы
	if (!LAi_IsGroupDamagableEnemy(attacker, enemy)) return; // проверка ударов по своим

	if (stf(attacker.chr_ai.(weaponType).EnergyP) > 0.0)
	{
		if (sBullet != "powder_pellet") Lai_CharacterChangeEnergy(enemy, -stf(attacker.chr_ai.(weaponType).EnergyP));
		else Lai_CharacterChangeEnergy(enemy, -stf(attacker.chr_ai.(weaponType).EnergyP));
	}

	float damageMtp = 1 + GetDamageMtp(&aTable, SHOT_STRIKE, weaponType); // множитель урона

	GunpowderTester(attacker, &damageMtp, rAmmo);
	ModifyGunDamageByPerks(attacker, enemy, &damageMtp, nEnemies);                    // перки, не вынесенные в модификаторы
	ModifyGunDamageByAiming(fAimingTime, &damageMtp);                                   // прицеливание
	ModifyGunDamageByQuestSituations(attacker, enemy, &damageMtp);                    // особые ситуации
	bool isCrit = false;
	ModifyDamageMtpByCrit(attacker, enemy, &aTable, &eTable, weaponType, SHOT_STRIKE, &damageMtp, &isCrit); // крит попадание
	if (isHeadShot) ModifyDamageMtpByHeadshot(attacker, &aTable, enemy, weaponType, &damageMtp); // хедшот

	if (!HasDescriptor(rAmmo, "PiercingAmmo")) damageMtp -= GetDamageReduction(&eTable); // вражеское снижение урона
	damageMtp -= GetRangeDamageReduction(&eTable);                                      // вражеское снижение урона от огнестрела
	int resultDamage = MakeInt(damage * func_fmax(0, damageMtp) + 0.5);                 // итого базовый урон * мультипликатор
	if (resultDamage <= 0.0) return;

	LAi_ApplyCharacterDamage(enemy, resultDamage, "fire", isCrit);
	LAi_Achievments_ExtraDamage(attacker, resultDamage);

	if (CheckAttributeEqualTo(enemy,"model.animation", "man")) enemy.DamageFromShot = attacker.chr_ai.(weaponType).bullet;

	LAi_CheckKillCharacter(enemy); //Проверим на смерть
	// яд таино // Addon 2016-1 Jason Пиратская линейка
	if (IsCharacterEquippedArtefact(attacker, "indian_poison")) MakeIndianPoisonAttack(enemy, attacker);
	if (CheckAttribute(attacker, "cheats.indian_poison")) MakeIndianPoisonAttack(enemy, attacker);

	bool isSetBlade = CheckAttribute(enemy, "equip.blade");
	Perk_Sniper(attacker, enemy, sBullet, nShots);
	SoldiersHat(enemy);
	bool isDead = LAi_IsDead(enemy);
	if (isSetBlade) ApplyExpFromShot(attacker, enemy, isDead, isHeadShot, damage); // расчёт опыта за урон
	if (!isDead) return;

	Statistic_KillChar(attacker, enemy, "_g");
	Achievment_SetStat(27, 1);
	LAi_SetResultOfDeath(attacker, enemy, isSetBlade);
	if (fAimingTime >= 0.0)	pchar.chr_ai.kill_timer = BLI_KILL_MARKER_TIMER; // после убийства на короткое время меняем прицел
}

void ModifyGunDamageByPerks(ref attacker, ref enemy, ref damageMtp, int nEnemies)
{
	Perk_Preaim(attacker, enemy, &damageMtp);
	Perk_LeadRain(attacker, nEnemies, &damageMtp);
	Perk_Kern(attacker, &damageMtp);
}

// Это можно было бы сделать модификаторами персонажей, но нужны уведомления
// С появлением событий-на-персонаже можно будет убрать туда
void ModifyGunDamageByQuestSituations(ref attacker, ref enemy, ref damageMtp)
{
	// калеуче
	if (IsCharacterEquippedArtefact(enemy, "kaleuche_amulet3"))
	{
		damageMtp -= 0.25;
	}

	if (enemy.chr_ai.group == "KSOCHITAM_MONSTERS")
	{
		damageMtp = 0.16;
	}
	if (CheckAttribute(enemy, "GuardMask"))
	{
		damageMtp = 0;
		if (attacker.id == "Blaze") log_info(XI_ConvertString("Bullets1"));
	}
	// калеуче
	bool bTutt = (IsCharacterEquippedArtefact(pchar, "kaleuche_amulet2")) || (IsCharacterEquippedArtefact(pchar, "kaleuche_amulet3"));
	if (CheckAttribute(enemy, "KhaelRoaMonster") && !bTutt)
	{
		damageMtp = 0.0;
		if (attacker.id == "Blaze") log_info(XI_ConvertString("Bullets2"));
	}
	if (CheckAttribute(attacker, "KhaelRoaMonster") && !bTutt) 
	{
		damageMtp += 4;
	}
}

void ModifyDamageMtpByHeadshot(ref attacker, ref attackerTable, ref enemy, string weaponType, ref damageMtp)
{
	if (IsMainCharacter(enemy)) return; // ГГ не получает хедшотов

	damageMtp += GetHeadshotDamageMtp(attackerTable);
	if (CheckAttribute(enemy, "chr_ai.getheadshot")) return;

	enemy.chr_ai.getheadshot = 0.1;
	if (ShowCharString()) Log_Chr(enemy, XI_ConvertString("HeadShot"));
	else if(IsMainCharacter(attacker)) log_info(XI_ConvertString("HeadShot"));
}

void ModifyGunDamageByAiming(float aimingTime, ref damageMtp)
{
	if (aimingTime < 0.0) return;
	float fMaxTime = MAX_AIMING_TIME;
	float fBonus = 0.0;
	if(IsCharacterEquippedArtefact(pchar, "talisman20"))
	{
		fMaxTime *= 0.85;
		fBonus = 0.2;
	}
	damageMtp += Bring2Range(-0.25, 0.5 + fBonus, 0.0, fMaxTime, aimingTime);
}