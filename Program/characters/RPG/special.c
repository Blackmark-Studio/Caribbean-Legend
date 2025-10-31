
// Получить базовый уровень характеристики без бонусов
int GetSpecialBase(ref chr, string specialName)
{
	return GetAttributeInt(chr, SPECIAL_TYPE + "." + specialName);
}

// Получить уровень характеристики со всеми эффектами и штрафом от навигации
int GetSpecialAfterPenalty(ref chr, string specialName)
{
	int specialValue = GetSpecialWithEffects(chr, specialName);
	specialValue -= GetAttributeInt(chr, "ct.com.navyPenaltySpecial");
	return iClamp(1, SPECIAL_MAX, specialValue);
}

// Получить уровень характеристики со всеми эффектами, но без штрафа от навигации
int GetSpecialWithEffects(ref chr, string specialName)
{
	if (!LAi_IsArmed(chr)) return GetSpecialBase(chr, &specialName);

	if (!CheckAttribute(chr, "ct." + CT_COMMON + "." + specialName)) CT_UpdateCommonTable(chr);
	int specialValue = CT_GetInt(chr, CT_COMMON, &specialName);
	return iClamp(1, SPECIAL_MAX, specialValue);
}

int AddSPECIALValue(ref _refCharacter, string _skillName, int _add)
{
    string _type = SPECIAL_TYPE;
    
    if (CheckAttribute(_refCharacter, _type + "." + _skillName))
    {
        _refCharacter.(_type).(_skillName) = sti(_refCharacter.(_type).(_skillName)) + _add;
    }
    else
    {
        _refCharacter.(_type).(_skillName) = _add;
    }
    if (sti(_refCharacter.(_type).(_skillName)) < 1) {_refCharacter.(_type).(_skillName) = 1;}
    if (sti(_refCharacter.(_type).(_skillName)) > SPECIAL_MAX) {_refCharacter.(_type).(_skillName) = SPECIAL_MAX;}
    
    return sti(_refCharacter.(_type).(_skillName));
}

void SetSPECIAL(ref _refCharacter, int _s, int _p, int _e, int _c, int _i, int _a, int _l)
{
    _refCharacter.SPECIAL.Strength   = _s;
    _refCharacter.SPECIAL.Perception = _p;
    _refCharacter.SPECIAL.Endurance  = _e;
    _refCharacter.SPECIAL.Charisma   = _c;
    _refCharacter.SPECIAL.Intellect  = _i;
    _refCharacter.SPECIAL.Agility    = _a;
    _refCharacter.SPECIAL.Luck       = _l;
}

void SetRandSPECIAL(ref _refCharacter)
{
    SetSPECIAL(_refCharacter,
               (3 + rand(7)),
               (3 + rand(7)),
               (3 + rand(7)),
               (2 + rand(8)),
               (4 + rand(6)),
               (4 + rand(6)),
               (2 + rand(8)));
}

// Jason: спец.атрибут
int ApplySPECIALQuestPenalty(ref rChar, String sSkillName)
{
	int iValue = 0;
	int iPenalty = sti(rChar.GenQuest.EnergyPenalty);
	
	if(sSkillName == SPECIAL_A) iValue = -iPenalty;
	
	return iValue;
}
