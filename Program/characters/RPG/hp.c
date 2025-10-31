#define BASE_HP 160.0
#define BASE_HP_FOR_RANK 11
#define MAIN_HP_BONUS		0.0

float GetCharacterBaseHPValue(ref chr)
{
	float addValue = BASE_HP_FOR_RANK * (GetAttributeInt(chr, "rank")-1);
	float result = BASE_HP + addValue;
	NormalizeByPirates(&result, chr, SPECIAL_S, SPECIAL_E, 4, 6);
	return result;
}

//Получить хп персонажа
float LAi_GetCharacterHP(aref chr)
{
	float curHp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp"))
	{
		curHp = stf(chr.chr_ai.hp);
	}
	float maxHp = LAi_GetCharacterMaxHP(chr);
	if(curHp > maxHp) curHp = maxHp;
	chr.chr_ai.hp = curHp;
	chr.chr_ai.hp_max = maxHp;
	return curHp;
}

//Получить максимальные хп персонажа
float LAi_GetCharacterMaxHP(ref chr)
{
	return GetAttributeFloatOrDefault(chr, "chr_ai.hp_max", BASE_HP)
}

//Получить относительные хп персонажа 0..1
float LAi_GetCharacterRelHP(aref chr)
{
	float hp = LAi_GetCharacterHP(chr);
	float maxhp = LAi_GetCharacterMaxHP(chr);
	if(maxhp <= 0.0) return 0.0;
	if(maxhp > 0.0)
	{
		return hp/maxhp;
	}
	return 0.0;
}
