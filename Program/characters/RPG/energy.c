#define BASE_ENERGY 125.0
#define MAIN_ENERGY_BONUS	0.0
#define BASE_ENERGY_FOR_RANK 4

float GetCharacterBaseEnergy(ref chr)
{
	if (!CheckAttribute(chr, "equip.blade")) return BASE_ENERGY; // невооруженные пофигу

	float addValue = BASE_ENERGY_FOR_RANK * (GetAttributeInt(chr, "rank")-1);
	float result = BASE_ENERGY + addValue;
	NormalizeByPirates(&result, chr, SPECIAL_A, SPECIAL_I, 7, 3);
	return result;
}

//Получить максимальные хп персонажа
float GetCharacterMaxEnergyValue(ref chr)
{
	return GetAttributeFloatOrDefault(chr, "chr_ai.energy_max", BASE_ENERGY);
}

float GetCharacterMaxEnergyABSValue(ref _refCharacter)
{
	return GetCharacterMaxEnergyValue(_refCharacter);
}

void AddBonusEnergyToCharacter(ref _refCharacter, int iEnrg)
{
	IncreaseChrModifier(_refCharacter, M_ENERGY_MAX, iEnrg, "bonus");
	CT_UpdateLandTable(_refCharacter);
	SetEnergyToCharacter(_refCharacter);
}

void SetEnergyToCharacter(ref _refCharacter)
{
	_refCharacter.chr_ai.energyMax = GetCharacterMaxEnergyValue(_refCharacter);
	if (!CheckAttribute(_refCharacter, "chr_ai.energy"))
	{
		_refCharacter.chr_ai.energy    = _refCharacter.chr_ai.energyMax;
	}
	else
	{
	    if (sti(_refCharacter.chr_ai.energy) > sti(_refCharacter.chr_ai.energyMax))
	    {
	        _refCharacter.chr_ai.energy    = _refCharacter.chr_ai.energyMax;
	    }
	}
}

//Получить количество энергии у персонажа 0..100
float Lai_CharacterGetEnergy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		return stf(chr.chr_ai.energy);
	}
	return 0.0;
}

//Изменить количество энергии у персонажа 0..100
void Lai_CharacterChangeEnergy(aref chr, float dlt)
{
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		float cur = stf(chr.chr_ai.energy);
		cur = cur + dlt;
		if(cur < 0.0) cur = 0.0;
		if(cur > LAi_GetCharacterMaxEnergy(chr)) cur = LAi_GetCharacterMaxEnergy(chr); //boal
		chr.chr_ai.energy = cur;
	}else{
		if(dlt < 0.0) dlt = 0.0;
		if(dlt > LAi_GetCharacterMaxEnergy(chr)) dlt = LAi_GetCharacterMaxEnergy(chr);
		chr.chr_ai.energy = dlt;
	}
}


//Получить относительную энергию персонажа 0..1
float LAi_GetCharacterRelEnergy(aref chr)
{
	float energy = 0.0;
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		energy = stf(chr.chr_ai.energy);
		energy = energy / LAi_GetCharacterMaxEnergy(chr); // boal
	}
	return energy;
}


float LAi_GetCharacterMaxEnergy(aref chr)
{
	return GetAttributeFloatOrDefault(chr, "chr_ai.energyMax", LAI_DEFAULT_ENERGY_MAX)
}
