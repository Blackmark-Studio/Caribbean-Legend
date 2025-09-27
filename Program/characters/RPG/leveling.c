// Эффективность по talent
float GetTalentEfficiency(int talent)
{
    float norm = makefloat(talent) / 10.0;   // нормализуем 1..10 → 0.1..1.0
    return 0.7 + 0.3 * sqrt(norm);           // формула эффективности
}

// порог ранга
int GetCharacterRankRate(ref _refCharacter)
{
    int talent = GetCharacterSPECIALSimple(_refCharacter, SPECIAL_I);
    float eff = GetTalentEfficiency(talent);

    if(CheckCharacterPerk(_refCharacter, "SharedExperience"))
    {
        return makeint(40.0 / eff);
    }
    return makeint(41.0 / eff);
}
int GetCharacterRankRateCur(ref _refCharacter)
{
    if(!CheckAttribute(_refCharacter, "rank_exp"))
	{
		_refCharacter.rank_exp = 0;
	}
    return sti(_refCharacter.rank_exp);
}

// сброс всех порогов (буфер расчета, пересчитывается от вещей +1)
void ClearCharacterExpRate(ref _chref)
{
    int    i;
    string name;

    for (i=1; i<15; i++)
    {
        name = GetSkillNameByIdx(i);
        DeleteAttribute(_chref, "skill." + name + "_rate");
    }
}

// когда меняется порог кача, нужно сбросить очки, иначе будет по 120%
void RefreshCharacterSkillExpRate(ref _chref)
{
    int    i;
    string name;

    // --> Оптимизация для интерфейсов. Тут цикл, где на каждом шагу:
    // Посмотреть порог -> посмотреть спешиал -> проверить пенальти -> посмотреть Навигацию 
    AddCharacterExpToSkill(_chref, SKILL_SAILING, 0.0);
    ApplayNewSkill(_chref, SKILL_SAILING, 0);
    _chref.TempSailing = GetSummonSkillFromNameSimple(_chref, SKILL_SAILING); // бэкапим её
    // <-- Оптимизация (and its really works!)

    for (i=1; i<15; i++)
    {
        if(i == 10) continue; // SKILL_SAILING
        name = GetSkillNameByIdx(i);
        AddCharacterExpToSkill(_chref, name, 0.0);
        ApplayNewSkill(_chref, name, 0); // иначе перки  будут 23/22
    }

    DeleteAttribute(_chref, "TempSailing"); // убираем бэкап
}

void AddCharacterExpToSkillSquadron(ref _refCharacter, string _skill, float _addValue)
{
    int cn,i;
	ref chref;

	for(i=0; i<4; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{    // и квестовым тоже
			AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue);
		}
	}
}

void AddCharacterExpToSkill(ref _chref, string _skill, float _addValue)
// _chref - character _skill - name ex -"Fencing"  _skill_exp = "Fencing_exp"   _addValue = 100
{
	if (CheckAttribute(pchar, "GenQuest.NoExp")) return;
    string  _skill_exp = _skill + "_exp";
    if (!CheckAttribute(_chref, "skill." + _skill_exp))
    {
        _chref.skill.(_skill_exp) = 0;
    }

    // boal 300804 падение экспы
    if (_addValue < 0)
    {
        _chref.skill.(_skill_exp) = sti(_chref.skill.(_skill_exp)) + _addValue;
        if (sti(_chref.skill.(_skill_exp)) < 0)
        {
            _chref.skill.(_skill_exp) = 0;
        }
        return;
    }

    if(_addValue > 0)
    {
        // Шапки
        switch (GetCharacterEquipByGroup(_chref, HAT_ITEM_TYPE))
        {
            case "hat1":
                if(_skill == SKILL_F_LIGHT || _skill == SKILL_FENCING || _skill == SKILL_F_HEAVY)
                    _addValue *= 1.1;
                break;
            case "hat3":
                if(_skill == SKILL_SAILING || _skill == SKILL_ACCURACY || _skill == SKILL_REPAIR)
                    _addValue *= 1.1;
                break;
            case "hat4":
                if(_skill == SKILL_SAILING || _skill == SKILL_ACCURACY || _skill == SKILL_CANNONS || _skill == SKILL_REPAIR || _skill == SKILL_GRAPPLING || _skill == SKILL_DEFENCE || _skill == SKILL_COMMERCE)
                    _addValue *= 1.15;
                break;
        }
        // Лог
        if (bExpLogShow && IsOfficer(_chref))
        {
           Log_Info(_chref.id + " take " + FloatToString(_addValue, 2) + " exp to " + _skill);
        }
    }

    if (CheckAttribute(_chref, "skill." + _skill) && sti(_chref.skill.(_skill)) < SKILL_MAX)// && sti(_chref.skill.(_skill)) > 0)
    { // if skill = 0 then it is great loser
        _chref.skill.(_skill_exp) = stf(_chref.skill.(_skill_exp)) + _addValue;
        float fExpRate = GetCharacterExpRate(_chref, _skill);
        while ( makeint(sti(_chref.skill.(_skill)) * fExpRate) <= stf(_chref.skill.(_skill_exp)) && sti(_chref.skill.(_skill)) < SKILL_MAX )
        {
            _chref.skill.(_skill_exp) = stf(_chref.skill.(_skill_exp)) - makeint(sti(_chref.skill.(_skill)) * fExpRate);
            AddCharacterSkillDontClearExp(_chref, _skill, 1);
            fExpRate = GetCharacterExpRate(_chref, _skill); // Обновим на случай повышения fRateReg
            // оптимизация скилов
            DeleteAttribute(_chref, "BakSkill." + _skill);
            DeleteAttribute(_chref, "BakSkillCount." + _skill);
        }
    }

    // Officers
    if (_addValue > 0 && sti(_chref.index) == GetMainCharacterIndex()) // Только для ГГ
    {
        if(ShowExpNotifications()) notification(StringFromKey("RPGUtilite_1"), _skill);

        float div;
        bool  bShare = CheckCharacterPerk(_chref, "SharedExperience");
		int cn, i, iPas;
		iPas = GetPassengersQuantity(_chref);
        for(i=0; i<iPas; i++)
        {
            cn = GetPassenger(_chref,i);
            if(cn!=-1)
            {
               if (isOfficerInShip(GetCharacter(cn), true))
               {
                   if(bShare) div = 2.0;
                   else div = 4.0;
               }
               else
               {
                   if(bShare) div = 10.0;
                   else div = 20.0;
               }
               AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / div);
            }
        }
        for(i=1; i<COMPANION_MAX; i++)
        {
            cn = GetCompanionIndex(_chref,i);
            if(cn!=-1)
            {
               if(bShare) div = 3.0;
               else div = 6.0;
               AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / div);
            }
        }
    }
}


int AddCharacterExp(ref _refCharacter,int _exp)
{
	int retVal = false;
	return retVal;
}

int CalculateExperienceFromRank(int _Rank)
{
	if(_Rank<2) return 0;
	int retVal = 100;
	return retVal;
}
// личные перки
int GetFreePoints_SelfRate(ref _chref)
{
    int talent = GetCharacterSPECIALSimple(_chref, SPECIAL_I);
    float eff = GetTalentEfficiency(talent);

    if (CheckCharacterPerk(_chref, "SharedExperience"))
    {
        return makeint(11.0 / eff);
    }
    return makeint(12.0 / eff);
}
// корабельные перки 
int GetFreePoints_ShipRate(ref _chref)
{
    int talent = GetCharacterSPECIALSimple(_chref, SPECIAL_I);
    float eff = GetTalentEfficiency(talent);

    if (CheckCharacterPerk(_chref, "SharedExperience"))
    {
        return makeint(15.0 / eff);
    }
    return makeint(16.0 / eff);
}

// порог следующего скила (множитель)
float GetCharacterExpRate(ref _chref, string _skill)
{
    string  skill_rate = _skill + "_rate";

    if (!CheckAttribute(_chref, "skill." + skill_rate))
    {
        float  divBy = 1.0;
		float  fRateReg = 0.85;

        switch (_skill)
        {
            case SKILL_F_LIGHT:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.9 + GetCharacterSPECIAL(_chref, SPECIAL_P)*0.1;
            break;
            case SKILL_FENCING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_S)*0.6 + GetCharacterSPECIAL(_chref, SPECIAL_A)*0.4;
            break;
            case SKILL_F_HEAVY:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_S)*0.9 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.1;
            break;
            case SKILL_PISTOL:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.4 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.6;
            break;
            case SKILL_FORTUNE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_L);
            break;
            
            case SKILL_LEADERSHIP:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.2 + GetCharacterSPECIAL(_chref, SPECIAL_C)*0.8;
            break;
            case SKILL_COMMERCE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.8 + GetCharacterSPECIAL(_chref, SPECIAL_C)*0.2;
            break;
            case SKILL_ACCURACY:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.8 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.2;
            break;
            case SKILL_CANNONS:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.6 + GetCharacterSPECIAL(_chref, SPECIAL_S)*0.4;
            break;
            case SKILL_SAILING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.2 + GetCharacterSPECIAL(_chref, SPECIAL_I)*0.8;
            break;
            case SKILL_REPAIR:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.2 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.8;
            break;
            case SKILL_GRAPPLING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.7 + GetCharacterSPECIAL(_chref, SPECIAL_I)*0.3;
            break;
            case SKILL_DEFENCE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_C)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.5;
            break;
            case SKILL_SNEAK:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.5;
            break;
        }
		
		int Skill_Val = GetSkillValue(_chref, SKILL_TYPE, _skill);
		if(Skill_Val > 20 && Skill_Val < 36 ) fRateReg = 0.95;
		else if(Skill_Val > 35 && Skill_Val < 51 ) fRateReg = 1.10;
		else if(Skill_Val > 50 && Skill_Val < 66 ) fRateReg = 1.30;
		else if(Skill_Val > 65 && Skill_Val < 76 ) fRateReg = 1.60;
		else if(Skill_Val > 75 && Skill_Val < 86 ) fRateReg = 1.80;
		else if(Skill_Val > 85 && Skill_Val < 95 ) fRateReg = 2.10;
		else if(Skill_Val > 94 && Skill_Val < 99 ) fRateReg = 2.40;
		else if(Skill_Val > 98) fRateReg = 10.00;
		
        _chref.skill.(skill_rate) = makefloat(MOD_EXP_RATE / divBy)*fRateReg;
    }
    return  stf(_chref.skill.(skill_rate));
}


void ApplayNewSkill(ref _chref, string _skill, int _addValue)
{
    // трем кэш
    DeleteAttribute(_chref, "BakSkill." + _skill);
    
	// boal 05.05.04 разделение по группам -->
    if (isSelfTypeSkill(_skill))
    {
       if(CheckAttribute(_chref,"perks.FreePoints_self_exp"))
       {
           _chref.perks.FreePoints_self_exp = sti(_chref.perks.FreePoints_self_exp) + _addValue;
       }
       else
       {	_chref.perks.FreePoints_self_exp = _addValue;
       }
       if (sti(_chref.perks.FreePoints_self_exp) >= GetFreePoints_SelfRate(_chref))
       {
           _chref.perks.FreePoints_self_exp = 0;
           if(CheckAttribute(_chref,"perks.FreePoints_self"))
           {
               _chref.perks.FreePoints_self = sti(_chref.perks.FreePoints_self) + 1;
           }
           else
           {	_chref.perks.FreePoints_self = 1;
           }
           if (sti(_chref.index) == GetMainCharacterIndex())
           {
			   notification(XI_ConvertString("Personal abilities Note"), "Personal abilities");
			   if(CheckAttribute(_chref,"systeminfo.tutorial.Perk"))
			   {
				   Tutorial_Perk("");
				   DeleteAttribute(_chref,"systeminfo.tutorial.Perk");
			   }
           }
       }
    }
    else
    {
       if(CheckAttribute(_chref,"perks.FreePoints_ship_exp"))
       {
           _chref.perks.FreePoints_ship_exp = sti(_chref.perks.FreePoints_ship_exp) + _addValue;
       }
       else
       {	_chref.perks.FreePoints_ship_exp = _addValue;
       }
       if (sti(_chref.perks.FreePoints_ship_exp) >= GetFreePoints_ShipRate(_chref))
       {
           _chref.perks.FreePoints_ship_exp = 0;
           if(CheckAttribute(_chref,"perks.FreePoints_ship"))
           {
               _chref.perks.FreePoints_ship = sti(_chref.perks.FreePoints_ship) + 1;
           }
           else
           {	_chref.perks.FreePoints_ship = 1;
           }
           if (sti(_chref.index) == GetMainCharacterIndex())
           {
               notification(XI_ConvertString("Ship abilities Note"), "Ship abilities");
			   if(CheckAttribute(_chref,"systeminfo.tutorial.Perk"))
			   {
				    Tutorial_Perk("");
				    DeleteAttribute(_chref,"systeminfo.tutorial.Perk");
			   }
           }
       }
    }
    // boal 05.05.04 разделение по группам <--


    if(!CheckAttribute(_chref, "rank_exp"))
    {
      _chref.rank_exp = 0;
    }
    _chref.rank_exp = sti(_chref.rank_exp) + _addValue;

    if (sti(_chref.rank_exp) >= GetCharacterRankRate(_chref)) // use classic mode - 2 skill = 1 rank
    {
        _chref.rank_exp = 0;
        _chref.rank = sti(_chref.rank) + 1;
        float mhp = LAi_GetCharacterMaxHP(_chref) + GetCharacterAddHPValue(_chref);
        LAi_SetHP(_chref,mhp,mhp);

        if (CheckCharacterPerk(_chref, "EnergyPlus"))
		{
		    if (!CheckAttribute(_chref, "PerkValue.EnergyPlus"))
			{
		  		_chref.PerkValue.EnergyPlus = 0;
			}
			// belamour legendary edition новый бонус к энергии 
			_chref.PerkValue.EnergyPlus = sti(_chref.rank);
			SetEnergyToCharacter(_chref);
		}

        // сообщение в лог
        //if(IsOfficer(_chref) || IsCompanion(_chref))

		if(sti(_chref.index) == GetMainCharacterIndex())
        {
            AddMsgToCharacter(_chref, MSGICON_LEVELUP);
            LA_LevelUp(XI_ConvertString("Level Up"), ""+sti(_chref.rank)+"");
            Event("PlayerLevelUp");
            //QuestsCheck();
        }
    }
    if (_addValue > 0 ) Event(EVENT_CT_UPDATE_FELLOW, "a", _chref);
}


int AddCharacterSkill(ref _chref, string _skill, int _addValue)
{
    string  _skill_exp = _skill + "_exp";

    if (_addValue > 0)
	{
	    if ((sti(_chref.skill.(_skill)) + _addValue) > SKILL_MAX)
	    {
	        _addValue = SKILL_MAX - sti(_chref.skill.(_skill));
	    }
	}
    _chref.skill.(_skill) = sti(_chref.skill.(_skill)) + _addValue;

	if (sti(_chref.skill.(_skill)) < 1)
	{
        _chref.skill.(_skill) = 1;
	}
	if (sti(_chref.skill.(_skill)) > SKILL_MAX )
	{
	    _chref.skill.(_skill) = SKILL_MAX;
	}
	_chref.skill.(_skill_exp) = 0;
	if (_addValue >= 0)
	{
	   ApplayNewSkill(_chref, _skill, _addValue);
	}
    else if (_addValue < 0 ) Event(EVENT_CT_UPDATE_FELLOW, "a", _chref);

	return sti(_chref.skill.(_skill));
}

void AddCharacterSkillDontClearExp(ref _chref, string _skill, int _addValue)
{
    /*if (_addValue > 0)
	{
	    if ((sti(_chref.skill.(_skill)) + _addValue) > SKILL_MAX)
	    {
	        _addValue = SKILL_MAX - sti(_chref.skill.(_skill));
	    }
	} */
	_chref.skill.(_skill) = sti(_chref.skill.(_skill)) + _addValue;

	if (sti(_chref.skill.(_skill)) < 1)
	{
        _chref.skill.(_skill) = 1;
	}
	if (sti(_chref.skill.(_skill)) > SKILL_MAX )
	{
	    _chref.skill.(_skill) = SKILL_MAX;
	}
	if (_addValue >= 0)
	{
	   ApplayNewSkill(_chref, _skill, _addValue);
	}
}


float GetSkillValueExp(ref _refCharacter, string _skillName)
{
    string skillName_exp = _skillName + "_exp";
    if (!CheckAttribute(_refCharacter, "Skill."+skillName_exp))
	{
		_refCharacter.Skill.(skillName_exp) = 0;
	}
    return stf(_refCharacter.Skill.(skillName_exp));
}

void AddCharacterSkillPoints(ref _chref, string _skill, int _addValue)
{
	_chref.skill.(_skill) = sti(_chref.skill.(_skill)) + _addValue;

	if (sti(_chref.skill.(_skill)) < 1)
	{
        _chref.skill.(_skill) = 1;
	}
	if (sti(_chref.skill.(_skill)) > SKILL_MAX )
	{
	    _chref.skill.(_skill) = SKILL_MAX;
	}
	if (_addValue >= 0)
	{
	   ApplayNewSkill(_chref, _skill, _addValue);
	   notification(XI_ConvertString(_skill) + " + " + _addValue, _skill);
	}
}


// прирост НР
int GetCharacterAddHPValue(ref _refCharacter)
{
	int Ers = GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E);
	int ret = makeint(2 + Ers * 0.55 + 0.5);

	if (CheckCharacterPerk(_refCharacter, "HPPlus"))
	{
		ret = ret + 1;
		if(CheckAttribute(_refCharacter, "chr_ai.hp_max_back"))
		{
			_refCharacter.chr_ai.hp_max_back = stf(_refCharacter.chr_ai.hp_max_back) + ret;
		}
	}
	else
	{
		if(CheckAttribute(_refCharacter, "chr_ai.hp_max_back"))
		{
			_refCharacter.chr_ai.hp_max_back = stf(_refCharacter.chr_ai.hp_max_back) + ret;
		}
	}
	return ret;
}