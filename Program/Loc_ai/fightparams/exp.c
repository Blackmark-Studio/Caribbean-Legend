
//Расчитать полученный опыт при ударе саблей
float LAi_CalcExperienceForBlade(aref attack, aref enemy, string attackType, bool isBlocked, float dmg)
{
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if(ra < 1.0) ra = 1.0;
	if(re < 1.0) re = 1.0;
	dmg = dmg*((1.0 + re*0.5)/(1.0 + ra*0.5));

	switch(attackType)
	{
		case "break":
			if(isBlocked)
			{
				dmg = dmg*1.1;
			}else{
				dmg = dmg*1.2;
			}
		break;
		case "feint":
			dmg = dmg*1.5;
		break;
		case "feintc":
			dmg = dmg*1.5;
		break;
	}
	if (stf(enemy.chr_ai.hp) < dmg)
	{
       dmg = stf(enemy.chr_ai.hp);
	}
	return dmg;
}

// Начисляем опыт за удар
void ApplyExpFromStrike(ref attack, ref enemy, bool isDead, string attackType, string weaponType, bool isBlocked, float dmg)
{
	float exp = LAi_CalcExperienceForBlade(attack, enemy, attackType, isBlocked, dmg);
	exp *= EXP_FOR_HIT;	// ИГРАЕМСЯ СКОРОСТЬЮ НАБОРА ОПЫТА ЗА УДАР

	if (weaponType == MUSKET_ITEM_TYPE)
	{
		if (CheckAttribute(enemy, "City")) AddCharacterExpToSkill(attack, SKILL_PISTOL, Makefloat(exp*0.02));
		else AddCharacterExpToSkill(attack, SKILL_PISTOL, Makefloat(exp*0.2));
	}
	else
	{
		if (CheckAttribute(enemy, "City")) AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), Makefloat(exp*0.02));
		else AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), Makefloat(exp*0.2));
	}

	if(!isDead) return;

	float ra = 1.0;
	float re = 1.0;
	if (CheckAttribute(attack, "rank")) ra = stf(attack.rank);
	if (CheckAttribute(enemy, "rank")) re = stf(enemy.rank);

	float kExpKill = EXP_FOR_KILL; // ИГРАЕМСЯ СКОРОСТЬЮ НАБОРА ОПЫТА ЗА УБИЙСТВО
	
	if (weaponType == MUSKET_ITEM_TYPE)
	{
		if (CheckAttribute(enemy, "City")) AddCharacterExpToSkill(attack, SKILL_PISTOL, makefloat((10.0 + ((1 + re) / (1+ra))*6.5)/20) * kExpKill);
		else AddCharacterExpToSkill(attack, SKILL_PISTOL, makefloat(10.0 + ((1 + re) / (1+ra))*6.5) * kExpKill);
	}
	else
	{
		if (CheckAttribute(enemy, "City")) AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), makefloat((10.0 + ((1 + re) / (1+ra))*6.5)/20) * kExpKill);
		else AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), makefloat(10.0 + ((1 + re) / (1+ra))*6.5) * kExpKill);	
	}

	AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
	AddCharacterExpToSkill(attack, SKILL_FORTUNE, 1);
	AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
}

// Начисляем опыт за выстрел
void ApplyExpFromShot(ref attack, ref enemy, bool isDead, bool isHeadShot, float damage)
{
	float exp = LAi_GunCalcDamageExperience(attack, enemy, damage, isHeadShot);
	AddCharacterExpToSkill(attack, SKILL_PISTOL, exp);
	if (!isDead) return;

	float expKill = LAi_GunCalcKillExperience(attack, enemy);
	AddCharacterExpToSkill(attack, SKILL_PISTOL, expKill);
	if (CheckAttribute(enemy, "City")) return;

	AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
	AddCharacterExpToSkill(attack, SKILL_FORTUNE, 2);
	AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
}