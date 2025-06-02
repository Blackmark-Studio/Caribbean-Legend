// 11.08.05 Boal Модуль для новой РПГ системы S.P.E.C.I.A.L
// метод для совместимости с .ИНИ файлом (секция SKILLCHANGER)

#define MAX_ACHIEVMENTS		73

// имя персонажа
string GetCharacterName(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("CharactersStaticNames.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

// порог ранга
int GetCharacterRankRate(ref _refCharacter)
{
	if(CheckCharacterPerk(_refCharacter, "SharedExperience"))
	{
		return 34 - GetCharacterSPECIALSimple(_refCharacter, SPECIAL_I);
	}
	
    return 35 - GetCharacterSPECIALSimple(_refCharacter, SPECIAL_I);
}
int GetCharacterRankRateCur(ref _refCharacter)
{
    if(!CheckAttribute(_refCharacter, "rank_exp"))
	{
		_refCharacter.rank_exp = 0;
	}
    return sti(_refCharacter.rank_exp);
}
// прирост НР
int GetCharacterAddHPValue(ref _refCharacter)
{
	// --> убрать влияние кирас
	int Ers = GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E);
	if (GetCharacterEquipByGroup(_refCharacter, CIRASS_ITEM_TYPE) == "underwater") Ers = Ers+2;
	if (GetCharacterEquipByGroup(_refCharacter, CIRASS_ITEM_TYPE) == "cirass1") Ers = Ers+1;
	if (GetCharacterEquipByGroup(_refCharacter, CIRASS_ITEM_TYPE) == "cirass2") Ers = Ers+1;
	if (GetCharacterEquipByGroup(_refCharacter, CIRASS_ITEM_TYPE) == "cirass4") Ers = Ers+1;
	// <-- убрать влияние кирас

	int ret = makeint(2 + Ers * 0.55 + 0.5);
  //  int ret = makeint(2 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E) * 0.55 + 0.5);

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

int GetCharacterBaseHPValue(ref _refCharacter)
{
	int ret = makeint(30.0 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_S)*GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E)*0.5);
	return ret;
}

float GetCharacterMaxEnergyValue(ref _refCharacter)
{
    float ret = (30.0 + GetCharacterSPECIAL(_refCharacter, SPECIAL_A)*10);
	if (CheckAttribute(_refCharacter, "PerkValue.EnergyPlus"))
	{
  		ret = ret + stf(_refCharacter.PerkValue.EnergyPlus);
	}
	if (CheckAttribute(_refCharacter, "questTemp.ChickenGod.EnergyMod")) {
		ret += stf(_refCharacter.questTemp.ChickenGod.EnergyMod);
	}
	if(IsEquipCharacterByArtefact(_refCharacter, "indian_7"))
	{
		ret = ret + makeint(1500 / ret);
	}
	if(CheckAttribute(_refCharacter, "cheats.energyplus"))
	{
		ret += stf(_refCharacter.cheats.energyplus);
	}
	return ret;
}

float GetCharacterMaxEnergyABSValue(ref _refCharacter)
{
    // проверки перков to_do
	float ret = (30.0 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_A)*10);
	if (CheckAttribute(_refCharacter, "PerkValue.EnergyPlus"))
	{
  		ret = ret + stf(_refCharacter.PerkValue.EnergyPlus);
	}
	if (CheckAttribute(_refCharacter, "questTemp.ChickenGod.EnergyMod")) {
		ret += stf(_refCharacter.questTemp.ChickenGod.EnergyMod);
	}
	return ret;
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

int GetCharacterMaxOfficersQty(ref _refCharacter)
{
    return GetCharacterSPECIAL(_refCharacter, SPECIAL_C)*2;
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

int GetFreePoints_SelfRate(ref _chref)
{
	if (CheckCharacterPerk(_chref, "SharedExperience"))
	{
		return 39 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
	}
    return 40 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
}

int GetFreePoints_ShipRate(ref _chref)
{
	if (CheckCharacterPerk(_chref, "SharedExperience"))
	{
		return 39 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
	}
    return 40 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
}
/////////////////////////////////////////////////////////////////////////

void SetSelfSkill(ref _refCharacter, int _fl, int _f, int _fh, int _p, int _fr)
{
    _refCharacter.Skill.FencingL      = _fl;
    _refCharacter.Skill.FencingS      = _f;
    _refCharacter.Skill.FencingH      = _fh;
    _refCharacter.Skill.Pistol        = _p;
    _refCharacter.Skill.Fortune       = _fr;
//    _refCharacter.Skill.Leadership = _ld;
//    _refCharacter.Skill.Sneak      = _sn;
}

void SetShipSkill(ref _refCharacter, int _ld, int _cr, int _ac, int _cn, int _sl, int _re, int _gr, int _de, int _sn)
{
    _refCharacter.Skill.Leadership = _ld;
    _refCharacter.Skill.Commerce   = _cr;
    _refCharacter.Skill.Accuracy   = _ac;
    _refCharacter.Skill.Cannons    = _cn;
    _refCharacter.Skill.Sailing    = _sl;
    _refCharacter.Skill.Repair     = _re;
    _refCharacter.Skill.Grappling  = _gr;
    _refCharacter.Skill.Defence    = _de;
    _refCharacter.Skill.Sneak      = _sn;
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

/// влияет только на СПЕЦИАЛ
int ApplayNavyPenalty(ref _refCharacter, string skillName, int sumSkill)
{
    if (IsCompanion(_refCharacter) && GetRemovable(_refCharacter))//пусть будет для компаньонов тоже sti(_refCharacter.index) == GetMainCharacterIndex()) // только для главного, чтоб не тормозить всю игру
    {
        int sailSkill;
        int needSkill;
        // общее умение навигации
        if(CheckAttribute(_refCharacter, "TempSailing"))
             sailSkill = _refCharacter.TempSailing;
        else sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);

        int shipClass = GetCharacterShipClass(_refCharacter);
        needSkill = GetShipClassNavySkill(shipClass);
		
		if (CheckAttribute(_refCharacter, "NoNavyPenalty")) needSkill = 1;

        if (sailSkill < needSkill)
        {
			sailSkill = makeint((needSkill - sailSkill)/10.0 + 0.9); // округление до мах всегда
			sumSkill = sumSkill - sailSkill;
	        if (sumSkill < 1) sumSkill = 1;
			if(CheckAttribute(_refCharacter,"systeminfo.tutorial.navigator"))
			{
				pchar.quest.Tutorial_Navigator.win_condition.l1 = "EnterToSea";
				pchar.quest.Tutorial_Navigator.function = "Tutorial_Navigator";
			}
        }
    }
    return  sumSkill;
}
// пенальти в скилы
int ApplayNavyPenaltyToSkill(ref _refCharacter, string skillName, int sumSkill)
{
    if (IsCompanion(_refCharacter) && GetRemovable(_refCharacter))//пусть будет для компаньонов тоже sti(_refCharacter.index) == GetMainCharacterIndex()) // только для главного, чтоб не тормозить всю игру
    {
        int sailSkill;
        int needSkill;

        // общее умение навигации
        if(CheckAttribute(_refCharacter, "TempSailing"))
             sailSkill = _refCharacter.TempSailing;
        else sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);
        int shipClass = GetCharacterShipClass(_refCharacter);
        needSkill = GetShipClassNavySkill(shipClass);
		
		if (CheckAttribute(_refCharacter, "NoNavyPenalty")) needSkill = 1;
		
        if (sailSkill < needSkill)
        {
			sailSkill = needSkill - sailSkill;
			sumSkill = sumSkill - sailSkill;
	        if (sumSkill < 1) sumSkill = 1;
        }
    }
    return  sumSkill;
}

int NavyPenalty(ref _refCharacter)
{
	int sailSkill;
	int needSkill;

	// общее умение навигации
	sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);
	int shipClass = GetCharacterShipClass(_refCharacter);
	needSkill = GetShipClassNavySkill(shipClass);
	
	if (CheckAttribute(_refCharacter, "NoNavyPenalty")) needSkill = 1;
	
	if (sailSkill < needSkill)
	{
		return needSkill - sailSkill;
	}
	return 0;
}

// с пенальти и вещами +1
int GetCharacterSPECIAL(ref _refCharacter, string skillName)
{
    int skillN;

	skillN = GetCharacterSPECIALSimple(_refCharacter, skillName);

 	skillN = ApplayNavyPenalty(_refCharacter, skillName, skillN);
	
    return skillN;
}

int GetCharacterSPECIALSimple(ref _refCharacter, string skillName)
{
	if (!CheckAttribute(_refCharacter,"SPECIAL."+skillName)) return 3;
	int skillN = sti(_refCharacter.SPECIAL.(skillName));
	bool bHero = (sti(_refCharacter.index) == GetMainCharacterIndex());

    // Здоровье
    bool bHealth = bHero && MOD_SKILL_ENEMY_RATE > 1;
    if (bHealth || CheckAttribute(_refCharacter, "OfficerImmortal"))
    {
        skillN = skillN + GetHealthNum(_refCharacter) - 6; // max -5
    }

    if(bHero)
    {
        int i, num, idx;
        aref arEquip, curItem;
        string sItem;

        // ITEM_SLOT_TYPE
        makearef(arEquip, _refCharacter.equip_item);
        num = GetAttributesNum(arEquip);
        for (i=0; i<num; i++)
        {
            sItem = GetAttributeValue(GetAttributeN(arEquip,i));
            if(sItem == "") continue;
            idx = FindItem(sItem);
            if (idx < 0) continue;

            switch(Items[idx].id)
            {
                case "totem_13": // Джокер
                    if(skillName == SPECIAL_L) skillN += 1;
                break;
            }
        }

        // TALISMAN_ITEM_TYPE
        sItem = GetCharacterEquipByGroup(_refCharacter, TALISMAN_ITEM_TYPE);
        switch(sItem)
        {
            case "talisman9": // Орден Святого Людовика
                if(skillName == SPECIAL_C) skillN += 1;
            break;
        }
    }

	// Родовой кинжал
	if(GetCharacterEquipByGroup(_refCharacter, BLADE_ITEM_TYPE) == "knife_03") 
    {
		if(skillName == SPECIAL_L) skillN += 1;
    }

	// Кремневый револьвер
	if(GetCharacterEquipByGroup(_refCharacter, GUN_ITEM_TYPE) == "pistol13") 
    {
		if(skillName == SPECIAL_C) skillN += 1;
    }
    
	skillN += ApplySPECIALCirassPenalty(_refCharacter, skillName);
	skillN += ApplySPECIALMangarosaPotion(_refCharacter, skillName); // Jason
	
	if(CheckAttribute(_refCharacter, "GenQuest.EnergyPenalty")) 
	{
		skillN += ApplySPECIALQuestPenalty(_refCharacter, skillName); // Jason
	}

	if (skillN <= 1) skillN = 1;
	if (skillN > SPECIAL_MAX) skillN = SPECIAL_MAX;

	return skillN;
}


void InitRPGType()
{
    NullCharacter.SPECIALType.Strength = true;
    NullCharacter.SPECIALType.Perception = true;
    NullCharacter.SPECIALType.Endurance = true;
    NullCharacter.SPECIALType.Charisma = true;
    NullCharacter.SPECIALType.Intellect = true;
    NullCharacter.SPECIALType.Agility = true;
    NullCharacter.SPECIALType.Luck = true;
    
    NullCharacter.SelfType.Leadership = true;
	NullCharacter.SelfType.FencingL = true;
    NullCharacter.SelfType.FencingS = true;
    NullCharacter.SelfType.FencingH = true;
    NullCharacter.SelfType.Pistol = true;
    NullCharacter.SelfType.Fortune = true;
    NullCharacter.SelfType.Sneak = true;
    // остальные корабельные
    NullCharacter.ShipType.Commerce = true;
    NullCharacter.ShipType.Accuracy = true;
    NullCharacter.ShipType.Cannons = true;
    NullCharacter.ShipType.Sailing = true;
    NullCharacter.ShipType.Repair = true;
    NullCharacter.ShipType.Grappling = true;
    NullCharacter.ShipType.Defence = true;

}

bool isSPECIALTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "SPECIALType." + _param);
}

bool isShipTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "ShipType." + _param);
}
bool isSelfTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "SelfType." + _param);
}

string GetRPGText(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("RPGDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

string GetSkillNameByIdx(int idx)
{
    string ret = "";
    
    switch (idx)
    {
        case 1:    ret = SKILL_F_LIGHT;   break;
        case 2:    ret = SKILL_FENCING;   break;
        case 3:    ret = SKILL_F_HEAVY;   break;
        case 4:    ret = SKILL_PISTOL;    break;
        case 5:    ret = SKILL_FORTUNE;   break;
        
        case 6:    ret = SKILL_LEADERSHIP; break;
        case 7:    ret = SKILL_COMMERCE;   break;
        case 8:    ret = SKILL_ACCURACY;   break;
        case 9:    ret = SKILL_CANNONS;    break;
        case 10:   ret = SKILL_SAILING;    break;
        case 11:   ret = SKILL_REPAIR;     break;
        case 12:   ret = SKILL_GRAPPLING;  break;
        case 13:   ret = SKILL_DEFENCE;    break;
        case 14:   ret = SKILL_SNEAK;      break;
        
        case 15:   ret = SPECIAL_S;   break;
        case 16:   ret = SPECIAL_P;   break;
        case 17:   ret = SPECIAL_A;   break;
        case 18:   ret = SPECIAL_C;   break;
        case 19:   ret = SPECIAL_I;   break;
        case 20:   ret = SPECIAL_E;   break;
        case 21:   ret = SPECIAL_L;   break;
    }
    return ret;
}
//  _type   ShipType SelfType  SPECIALType
string GetSkillNameByTRIdx(string _type, int idx)
{
    string ret = "";

	switch (_type)
	{
		case "SelfType" :
		    switch (idx)
		    {
                case 1:    ret = SKILL_LEADERSHIP; break;
				case 2:    ret = SKILL_F_LIGHT;   break;
		        case 3:    ret = SKILL_FENCING;   break;
		        case 4:    ret = SKILL_F_HEAVY;   break;
		        case 5:    ret = SKILL_PISTOL;    break;
		        case 6:    ret = SKILL_FORTUNE;   break;
                case 7:    ret = SKILL_SNEAK;      break;
		    }
		break;
		
		case "ShipType" :
		    switch (idx)
		    {
                case 1:    ret = SKILL_SAILING; break;
				case 2:    ret = SKILL_ACCURACY;   break;
		        case 3:    ret = SKILL_CANNONS;   break;
		        case 4:    ret = SKILL_GRAPPLING;   break;
		        case 5:    ret = SKILL_DEFENCE;    break;
		        case 6:    ret = SKILL_REPAIR;   break;
                case 7:    ret = SKILL_COMMERCE;      break;
		    }
		break;
		
		case "SPECIALType" :
		    switch (idx)
		    {
                case 1:   ret = SPECIAL_S;   break;
		        case 2:   ret = SPECIAL_P;   break;
		        case 3:   ret = SPECIAL_A;   break;
		        case 4:   ret = SPECIAL_C;   break;
		        case 5:   ret = SPECIAL_I;   break;
		        case 6:   ret = SPECIAL_E;   break;
		        case 7:   ret = SPECIAL_L;   break;
		    }
		break;
    }
    return ret;
}
// по имени скила вернуть значение
int GetSkillValue(ref _refCharacter, string _type, string _skillName)
{
    if (CheckAttribute(_refCharacter, _type + "." + _skillName))
    {
        return sti(_refCharacter.(_type).(_skillName));
    }
    return 0;
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
            Event("PlayerLevelUp", "l", sti(_chref.rank));
            //QuestsCheck();
        }
    }
}
// по специал распередить скилы
void InitStartParam(ref _chref)
{
    int i;
    string  skillName;
    
    ClearCharacterExpRate(_chref);
    
    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        _chref.skill.(skillName) = makeint(MOD_EXP_RATE / GetCharacterExpRate(_chref, skillName) + 0.5);
    }
    LAi_SetHP(_chref, GetCharacterBaseHPValue(_chref), GetCharacterBaseHPValue(_chref));
}

int GetHPIncrease(ref chr) {
	// --> убрать влияние кирас
	int Ers = GetCharacterSPECIALSimple(chr, SPECIAL_E);
	if (GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "underwater") Ers = Ers+2;
	if (GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "cirass1") Ers = Ers+1;
	if (GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "cirass2") Ers = Ers+1;
	if (GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "cirass4") Ers = Ers+1;
	// <-- убрать влияние кирас

	int ret = makeint(2 + Ers * 0.55 + 0.5);
	
	return ret * (sti(chr.rank) - 1);
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

// table service
string GetReputationComplexName(int reputation, string repName)
{	
	switch(repName)
	{
		case "fame" 	:
			if(reputation < 21)  return "REPUTATION_FAME_1";
			if(reputation < 41)  return "REPUTATION_FAME_2";
			if(reputation < 61)  return "REPUTATION_FAME_3";
			if(reputation < 81)  return "REPUTATION_FAME_4";
			return "REPUTATION_FAME_5";
		break;
		
		case "nobility" :
			if(reputation < 6)   return "REPUTATION_NOBILITY_1";
			if(reputation < 16)  return "REPUTATION_NOBILITY_2";
			if(reputation < 31)  return "REPUTATION_NOBILITY_3";
			if(reputation < 48)  return "REPUTATION_NOBILITY_4";
			if(reputation < 53)  return "REPUTATION_NOBILITY_5";
			if(reputation < 71)  return "REPUTATION_NOBILITY_6";
			if(reputation < 86)  return "REPUTATION_NOBILITY_7";
			if(reputation < 96)  return "REPUTATION_NOBILITY_8";
			return "REPUTATION_NOBILITY_9";
		break;
	}
}

string GetFullReputationComplexName(ref chref)
{
	string sReputation, sFame, sNobility;
	
	if(CheckAttribute(chref,"reputation.fame")) 
	{
		sFame = GetReputationComplexName(sti(chref.reputation.fame), "fame");
	}	
	else 
	{
		sFame = "REPUTATION_FAME_1";	
	}	
	
	if(CheckAttribute(chref,"reputation.nobility")) 
	{
		sNobility = GetReputationComplexName(sti(chref.reputation.nobility), "nobility");
	}	
	else
	{
		sNobility = "REPUTATION_NOBILITY_5";	
	}	
	sReputation = XI_ConvertString(sFame) + " " + XI_ConvertString(sNobility);
	
	return sReputation;
}

// table service
string GetReputationName(int reputation)
{
    if(reputation<11)
        return "REPUTATIONT_BAD_4";
    if(reputation<21)
        return "REPUTATIONT_BAD_3";
    if(reputation<31)
        return "REPUTATIONT_BAD_2";
    if(reputation<41)
        return "REPUTATIONT_BAD_1";
    if(reputation<51)
        return "REPUTATIONT_NEUTRAL";
    if(reputation<61)
        return "REPUTATIONT_GOOD_1";
    if(reputation<71)
        return "REPUTATIONT_GOOD_2";
    if(reputation<81)
        return "REPUTATIONT_GOOD_3";
    if(reputation<=90)
        return "REPUTATIONT_GOOD_4";

	return "REPUTATIONT_GOOD_4";
}
// to_do  del
string GetFameName(int fame)
{
   return "TO_DO for del";
}

string GetMoraleName(int morale)
{
	if(morale<10)
		return MoraleTable[MORALET_TREACHEROUS];
	if(morale<20)
		return MoraleTable[MORALET_AWFUL];
	if(morale<30)
		return MoraleTable[MORALET_LOW];
	if(morale<40)
		return MoraleTable[MORALET_POOR];
	if(morale<50)
		return MoraleTable[MORALET_NORMAL];
	if(morale<60)
		return MoraleTable[MORALET_ELATED];
	if(morale<70)
		return MoraleTable[MORALET_GOOD];
	if(morale<80)
		return MoraleTable[MORALET_HIGH];
	if(morale<90)
		return MoraleTable[MORALET_EXCELLENT];
	if(morale<=100)
		return MoraleTable[MORALET_HEROIC];
	return "";
}

string GetLoyalityName(int iLoyality)
{
	if(iLoyality<10)
		return LoyalityTable[MORALET_TREACHEROUS];
	if(iLoyality<20)
		return LoyalityTable[MORALET_AWFUL];
	if(iLoyality<30)
		return LoyalityTable[MORALET_LOW];
	if(iLoyality<40)
		return LoyalityTable[MORALET_POOR];
	if(iLoyality<50)
		return LoyalityTable[MORALET_NORMAL];
	if(iLoyality<60)
		return LoyalityTable[MORALET_ELATED];
	if(iLoyality<70)
		return LoyalityTable[MORALET_GOOD];
	if(iLoyality<80)
		return LoyalityTable[MORALET_HIGH];
	if(iLoyality<90)
		return LoyalityTable[MORALET_EXCELLENT];
	if(iLoyality<=100)
		return LoyalityTable[MORALET_HEROIC];
	return "";
}

// boal 15/01/04 учёт вещей выношу в спец метод для простоты работы далее -->
int SetCharacterSkillByItem(ref _refCharacter, string _skillName, string _itemSkillName, string _item, int _addValue)
{
	int iRetValue = 0;

	if(_skillName == _itemSkillName && GetCharacterItem(_refCharacter, _item) > 0)
	{
		iRetValue = _addValue;
	}

	return iRetValue;
}

int SetCharacterSkillByEquippedItem(ref _refCharacter, string _skillName, string _itemSkillName, string _item, int _addValue)
{
	int iRetValue = 0;
	
	if(_skillName == _itemSkillName && IsEquipCharacterByArtefact(_refCharacter, _item))
	{
		iRetValue = _addValue;
	}
	
	return iRetValue;
}

float AddMultiplySkillByEquippedItem(ref _refCharacter, string _skillName, string _itemSkillName, string _item, float _addValue)
{
	float fRetValue = 1.0;
	
	if(_skillName == _itemSkillName && IsEquipCharacterByArtefact(_refCharacter, _item))
	{
		fRetValue = _addValue;
	}
	
	return fRetValue;
}

int ApplySPECIALCirassPenalty(ref rChar, String sSkillName)
{
	int iValue = 0;
	String sSuit = GetCharacterEquipSuitID(rChar);
	
	if(sSuit == INVALID_SUIT) return 0;
	// belamour legendary edition ребаланс доспехов 20.09.2021
	switch(sSuit)
	{	
		case "cirass1"	:
			if(sSkillName == SPECIAL_E)			iValue = -1;			
			if(sSkillName == SPECIAL_A)			iValue = -2;			
		break;
				
		case "cirass2"	:
			if(sSkillName == SPECIAL_E)			iValue = -1;
			if(sSkillName == SPECIAL_A)			iValue = -1;
		break;
				
		/*case "cirass3"	:
			if(sSkillName == SPECIAL_A)			iValue = -1;
		break;*/
		
		case "cirass4"	:
			if(sSkillName == SPECIAL_E)			iValue = -1;
		break;
		
		case "cirass6"	:
			if(sSkillName == SPECIAL_P)			iValue = -1;
		break;
		
		case "cirass7"	:
			if(sSkillName == SPECIAL_P)			iValue = -1;
		break;
		
		case "cirass10"	:
			if(sSkillName == SPECIAL_A)			iValue = -1;
		break;
		
		/*case "cirass8"	:
			if(sSkillName == SPECIAL_P)			iValue = -1;
		break;
		*/
		case "suit1"	:
			if(sSkillName == SPECIAL_C)			iValue = 1;
		break;
		
		case "suit2"	:
			if(sSkillName == SPECIAL_C)			iValue = 1;
		break;
		
		case "suit3"	:
			if(sSkillName == SPECIAL_C)			iValue = 1;
		break;
		
		case "suit4"	:
			if(sSkillName == SPECIAL_P)			iValue = -1; // калеуче
			if(sSkillName == SPECIAL_A)			iValue = 1;
		break;
		
		case "suit5"	:
			if(sSkillName == SPECIAL_C)			iValue = 2;
		break;
		
		case "underwater"	: //Jason: водолаз
			if(sSkillName == SPECIAL_P)			iValue = -2;
			if(sSkillName == SPECIAL_E)			iValue = -2;
			if(sSkillName == SPECIAL_A)			iValue = -1;
		break;
	}
		
	return iValue;
}

int GetCharacterSuitType(ref rChar)
{
	int iValue = 0;
	String sSuit = GetCharacterEquipSuitID(rChar);
	
	if(sSuit == INVALID_SUIT) return -1;

	switch(sSuit)
	{	
		// тяжелые доспехи
		case "cirass1"	:
			iValue = 2;
		break;		
		case "cirass2"	:
			iValue = 2;
		break;				
		case "cirass3"	:
			iValue = 2;
		break;				
		case "cirass4"	:
			iValue = 2;
		break;
		case "cirass10"	:
			iValue = 2;
		break;
		
		// легкие доспехи
		case "cirass5"	:
			iValue = 1;
		break;				
		case "cirass6"	:
			iValue = 1;
		break;				
		case "cirass7"	:
			iValue = 1;
		break;				
		case "cirass8"	:
			iValue = 1;
		break;
		case "cirass9"	:
			iValue = 1;
		break;
		
		// прочее
		case "underwater":
			iValue = 2;
		break;						
		case "suit1":
			iValue = 1;
		break;						
		case "suit2":
			iValue = 1;
		break;						
		case "suit3":
			iValue = 1;
		break;

		case "suit4":
			iValue = 1;
		break;
		
		case "suit5":
			iValue = 1;
		break;			
	}
		
	return iValue;
}

// Warship 25.10.08 Учет одежды
// belamour legendary edition ребаланс одежды 20.09.2021
int SetCharacterSkillBySuit(ref rChar, String sSkillName)
{
	int iValue = 0;
	String sSuit = GetCharacterEquipSuitID(rChar);
	
	if(sSuit == INVALID_SUIT) return 0;
	
	switch(sSuit)
	{	
		case "cirass1"	:
			if(sSkillName == SKILL_SNEAK)		iValue = -5;
		break;

		case "cirass2"	:
			if(sSkillName == SKILL_SNEAK)		iValue = -5;
		break;

		case "cirass3"	:
			if(sSkillName == SKILL_LEADERSHIP)	iValue = 15;
			if(sSkillName == SKILL_SNEAK)		iValue = -15;
		break;
		
		case "cirass4"	:
			if(sSkillName == SKILL_LEADERSHIP)	iValue = 10;
			if(sSkillName == SKILL_SNEAK)		iValue = -20;
		break;
		
		case "cirass6"	:
			if(sSkillName == SKILL_LEADERSHIP)	iValue = -5;
			if(sSkillName == SKILL_SNEAK)		iValue = -5;
		break;
		
		case "cirass7"	:
			if(sSkillName == SKILL_LEADERSHIP)	iValue = -10;
		break;
		
		case "cirass8"	:
			if(sSkillName == SKILL_LEADERSHIP)	iValue = -15;
			if(sSkillName == SKILL_SNEAK)		iValue = 15;
		break;
		
		case "cirass9"	:
			if(sSkillName == SKILL_F_LIGHT)	    iValue = 5;
			if(sSkillName == SKILL_FENCING)	    iValue = 5;
			if(sSkillName == SKILL_F_HEAVY)	    iValue = 5;
			if(sSkillName == SKILL_PISTOL)	    iValue = 5;
		break;
		
		case "suit1"	: // Французский офицерский мундир
			if(sSkillName == SKILL_LEADERSHIP)	iValue = 25;
			if(sSkillName == SKILL_SNEAK)		iValue = -25;
		break;
		
		case "suit2"	: // Английский офицерский мундир
			if(sSkillName == SKILL_LEADERSHIP)	iValue = 25;
			if(sSkillName == SKILL_SNEAK)		iValue = -25;
		break;
		
		case "suit3"	: // Испанский офицерский мундир
			if(sSkillName == SKILL_LEADERSHIP)	iValue = 25;
			if(sSkillName == SKILL_SNEAK)		iValue = -25;
		break;
		
		case "suit4"	: // костюм Лампорта (Калеуче)
			if(sSkillName == SKILL_LEADERSHIP)	iValue = -25;
			if(sSkillName == SKILL_SNEAK)		iValue = 30;
		break;
		
		case "suit5"	: // Французский адмиральский мундир
			if(sSkillName == SKILL_LEADERSHIP)	iValue = 40;
			if(sSkillName == SKILL_SNEAK)		iValue = -50;
			if(sSkillName == SKILL_SAILING)		iValue = 5;
		break;
		
		case "underwater"	: // Jason: водолаз
			if(sSkillName == SKILL_LEADERSHIP)	iValue = -20;
			if(sSkillName == SKILL_SNEAK)		iValue = -100;
			if(sSkillName == SKILL_F_LIGHT)		iValue = -15;
			if(sSkillName == SKILL_FENCING)		iValue = -15;
			if(sSkillName == SKILL_F_HEAVY)		iValue = -15;
			if(sSkillName == SKILL_PISTOL)		iValue = -50;
		break;
	}
	
	return iValue;
}

// Jason: учёт негенерируемых клинков
int SetCharacterSkillByQuestBlade(ref rChar, String sSkillName)
{
	int iValue = 0;
	String sBlade = GetCharacterEquipByGroup(rChar, BLADE_ITEM_TYPE);
    if(sBlade == "") return 0;

	// belamour генерабельные клинки
    int idx = FindItem(sBlade);
    if (idx < 0) return 0;
    ref rBlade = &Items[idx];
    if(CheckAttribute(rBlade, "DefItemID"))
    {
        if(sSkillName == SKILL_F_LIGHT)
        {
            if(rBlade.DefItemID == "blade_39")      return 10; // Рапира бретера cle
            else if(rBlade.DefItemID == "blade_38") return 5;  // Дуэльная шпага cle
        }
	}

	switch(sBlade)
	{	
		case "knife_01"	:
			if(sSkillName == SKILL_F_LIGHT) iValue = 5;
		break;
		
		case "knife_02"	:
			if(sSkillName == SKILL_F_LIGHT) iValue = 15;
		break;
		
		case "q_blade_10"	:
			if(sSkillName == SKILL_FENCING) iValue = 10;
		break;
		
		case "q_blade_13"	:
			if(sSkillName == SKILL_F_HEAVY) iValue = 10;
		break;
		
		case "q_blade_16"	:
			if(sSkillName == SKILL_F_LIGHT) iValue = 10;
		break;
		
		case "q_blade_18"	:
			if(sSkillName == SKILL_F_LIGHT) iValue = 12;
		break;
		
		case "q_blade_19"	:
			if(sSkillName == SKILL_FENCING) iValue = 12;
		break;
		
		case "q_blade_21"	:
			if(sSkillName == SKILL_F_HEAVY) iValue = 12;
		break;
		
		case "topor_06"	: // Addon 2016-1 Jason Пиратская линейка
			if(sSkillName == SKILL_F_HEAVY) iValue = 5;
		break;
		
		// Мачете конкистадора
		case "machete2"	:
			if(sSkillName == SKILL_FENCING) iValue = 5;
		break;
		
		// Хопеш обычный cle
		case "khopesh1"	:
			if(sSkillName == SKILL_FENCING) iValue = 5;
		break;
		
		// Хопеш золотой cle
		case "khopesh2"	:
			if(sSkillName == SKILL_FENCING) iValue = 15;
		break;
		
		// Хопеш обычный с кровью cle
		case "khopesh3"	:
			if(sSkillName == SKILL_FENCING) iValue = 10;
		break;
		
		// Кавалерийская сабля cle
		case "saber"	:
			if(sSkillName == SKILL_FENCING) iValue = 5;
		break;
		
		// сабля Блейза cle
		case "pirate_cutlass"	:
			if(sSkillName == SKILL_FENCING) iValue = 5;
		break;
		
		// Итальянская рапира cle
		case "blade_40"	:
			if(sSkillName == SKILL_LEADERSHIP) iValue = 10;
		break;
		
		// Армейский палаш cle
		case "blade_42"	:
			if(sSkillName == SKILL_F_HEAVY) iValue = 5;
		break;
	}
	
	return iValue;
}

int SetCharacterSkillByGun(ref rChar, String sSkillName)
{
	int iValue = 0;
	String sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	
	switch(sGun)
	{	
		case "pistol11"	: // Чудовище cle
			if(sSkillName == SKILL_F_HEAVY) iValue = 20;
		break;
		
		case "pistol5"	: // Дуэльный пистолет
			if(sSkillName == SKILL_PISTOL)  iValue = 5;
		break;
	}
	
	return iValue;
}

// Jason: спец.атрибут
int SetCharacterSkillByPenalty(ref rChar, String sSkillName)
{
	int iValue = 0;
	int iPenalty = sti(rChar.GenQuest.BladePenalty);
	
	if(sSkillName == SKILL_F_LIGHT)      iValue = -iPenalty;
	else if(sSkillName == SKILL_FENCING) iValue = -iPenalty;
	else if(sSkillName == SKILL_F_HEAVY) iValue = -iPenalty;
	
	return iValue;
}

// Jason: спец.атрибут
int ApplySPECIALQuestPenalty(ref rChar, String sSkillName)
{
	int iValue = 0;
	int iPenalty = sti(rChar.GenQuest.EnergyPenalty);
	
	if(sSkillName == SPECIAL_A) iValue = -iPenalty;
	
	return iValue;
}

// Jason: зелья мангаросы
int ApplySPECIALMangarosaPotion(ref rChar, String sSkillName) // 280313
{
	int iValue = 0;
	if (CheckAttribute(rChar, "questTemp.Mangarosa.Potion"))
	{
		if (CheckAttribute(rChar, "questTemp.Mangarosa.Potion.Power"))
		{
			if(sSkillName == SPECIAL_S)			iValue = 2;
			else if(sSkillName == SPECIAL_E)	iValue = 2;
		}
		if (CheckAttribute(rChar, "questTemp.Mangarosa.Potion.Fast"))
		{
			if(sSkillName == SPECIAL_A)			iValue = 2;
			else if(sSkillName == SPECIAL_P)    iValue = 2;
		}
		if (CheckAttribute(rChar, "questTemp.Mangarosa.Potion.Total"))
		{
			if(sSkillName == SPECIAL_S)         iValue = 1;
			else if(sSkillName == SPECIAL_E)    iValue = 1;
			else if(sSkillName == SPECIAL_A)    iValue = 1;
			else if(sSkillName == SPECIAL_P)    iValue = 1;
			else if(sSkillName == SPECIAL_C)    iValue = 1;
			else if(sSkillName == SPECIAL_L)    iValue = 2;
		}
	}
	return iValue;
}

int SetCharacterSkillByMangarosa(ref rChar, String sSkillName) // 280313
{
	int iValue = 0;
	if (CheckAttribute(rChar, "questTemp.Mangarosa.Potion"))
	{
		if (CheckAttribute(rChar, "questTemp.Mangarosa.Potion.Power"))
		{
			if(sSkillName == SKILL_F_HEAVY) iValue = 15;
			else if(sSkillName == SKILL_FENCING) iValue = 5;
		}
		if (CheckAttribute(rChar, "questTemp.Mangarosa.Potion.Fast"))
		{
			if(sSkillName == SKILL_F_LIGHT) iValue = 10;
			else if(sSkillName == SKILL_PISTOL) iValue = 10;
		}
		if (CheckAttribute(rChar, "questTemp.Mangarosa.Potion.Total"))
		{
			if(sSkillName == SKILL_F_HEAVY)         iValue = 5;
			else if(sSkillName == SKILL_F_LIGHT)    iValue = 5;
			else if(sSkillName == SKILL_PISTOL)     iValue = 5;
			else if(sSkillName == SKILL_LEADERSHIP) iValue = 5;
			else if(sSkillName == SKILL_FORTUNE)    iValue = 5;
		}
	}
	
	return iValue;
}

// Jason: Калеуче - амулеты Туттуатхапака
int SetCharacterSkillByTuttuat(ref rChar, String sSkillName)
{
	int iValue = 0;
	
	if(sSkillName == SKILL_F_LIGHT)      iValue = 25;
	else if(sSkillName == SKILL_FENCING) iValue = 25;
	else if(sSkillName == SKILL_F_HEAVY) iValue = 25;
	else if(sSkillName == SKILL_PISTOL)  iValue = 25;
	
	return iValue;
}

//Sinistra: Стартовый морской бой
int SetCharacterSkillMaxSailing(ref rChar, String sSkillName)
{
	int iValue = 0;

	if(sSkillName == SKILL_SAILING)       iValue = 100;
	else if(sSkillName == SKILL_ACCURACY) iValue = 100;
	else if(sSkillName == SKILL_CANNONS)  iValue = 100;

	return iValue;
}

// boal 15/01/04 учёт вещей выношу в спец метод для простоты работы далее <--
float GetCharacterSkillToOld(ref _refCharacter, string skillName)
{
    return makefloat(GetCharacterSkill(_refCharacter, skillName) / SKILL_TO_OLD);
}
int GetCharacterSkill(ref _refCharacter, string skillName)
{
    int skillN;

    // boal 051104 метод тормозит страшно - проверка +1 вещей, будет опрос раз в 10
    if (CheckAttribute(_refCharacter, "BakSkill." + skillName))
    {
        if (sti(_refCharacter.BakSkillCount.(skillName)) < 20 )
        {
            _refCharacter.BakSkillCount.(skillName) = sti(_refCharacter.BakSkillCount.(skillName)) + 1;
            return sti(_refCharacter.BakSkill.(skillName));
        }
    }

	skillN = GetCharacterSkillSimple(_refCharacter, skillName);


    // 14.03.05 пенальти от класса корабля -->
 	skillN = ApplayNavyPenaltyToSkill(_refCharacter, skillName, skillN);
	// 14.03.05 пенальти от класса корабля <--

	_refCharacter.BakSkill.(skillName)      =  skillN; // значение
    _refCharacter.BakSkillCount.(skillName) = rand(5); // счетчик немного размажем пересчет

    return skillN;
}

// Функция часто вызывается, поэтому здесь соблюдаем осторожность в плане производительности
int GetCharacterSkillSimple(ref _refCharacter, string skillName)
{
	if(!CheckAttribute(_refCharacter,"Skill."+skillName)) return 1;
	int skillN = sti(_refCharacter.Skill.(skillName));
	bool bHero = (sti(_refCharacter.index) == GetMainCharacterIndex());
	
    // Модификаторы
    if (bHero || CheckAttribute(_refCharacter, "Payment")) //IsCompanion(_refCharacter) || IsOfficer(_refCharacter))
    {
        // Здоровье
        bool bHealth = bHero && MOD_SKILL_ENEMY_RATE > 1;
        if (bHealth || CheckAttribute(_refCharacter, "OfficerImmortal"))
        {
            if (isSelfTypeSkill(skillName))
            {
                skillN = skillN + 5*(GetHealthNum(_refCharacter) - 6); // max -5
            }
        }

        // Переносимые вещи
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, 		"SkullAztec", 	-20);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, 	"SkullAztec", 	 10);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_PISTOL, 		"KnifeAztec", 	-30);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, 		"KnifeAztec", 	-20);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, 		"KnifeAztec", 	-20);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, 		"KnifeAztec", 	-20);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, 		  "mineral8",   -10);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, 		 "mineral14",   -10);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, 			 "Coins",   -50);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, 	 "mineral30",   -10);
		skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, 	 "mineral31", 	-10);
    	skillN += SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE,       "mineral31", 	-10);

        // Экипировка (Rosarak. Переписал, чтобы работало быстрее)
        int i, num, idx;
        aref arEquip, curItem;
        string sItem;
        bool bOverloadCheck = true;
        float fScale = 1.0;

        // ITEM_SLOT_TYPE
        makearef(arEquip, _refCharacter.equip_item);
        num = GetAttributesNum(arEquip);
        for (i=0; i<num; i++)
        {
            sItem = GetAttributeValue(GetAttributeN(arEquip,i));
            //if(sItem == "") continue;
            idx = FindItem(sItem);
            if (idx < 0) continue;

            switch(Items[idx].id)
            {
                case "indian_9": // Бальд
                    if(skillName == SKILL_ACCURACY) fScale *= 1.1;
                    break;
                case "totem_06": // Гонтер
                    bOverloadCheck = false;
                    break;
                case "totem_12": // Сын ягуара
                    if(skillName == SKILL_ACCURACY && !IsDay())
                        fScale *= 2.0; // Получи фашист гранату по ночам!!!!
                    break;
                case "obereg_1": // Тередо
                    if(skillName == SKILL_REPAIR) skillN += 10;
                    break;
                case "obereg_2": // Шочипили
                    if(skillName == SKILL_REPAIR) skillN += 10;
                    break;
                case "obereg_4": // Веер цыганки
                    if(skillName == SKILL_SNEAK) skillN += 10;
                    break;
                case "obereg_5": // Нефритовая черепашка
                    if(skillName == SKILL_FORTUNE) skillN += 15;
                    break;
                case "obereg_6": // Обезьяний кулак
                    if(skillName == SKILL_LEADERSHIP) skillN += 10;
                    break;
                case "obereg_7": // Рыбак
                    if(skillName == SKILL_SAILING)
                    {
                        if(ShipBonus2Artefact(_refCharacter, SHIP_GALEON_SM)) skillN += 15;
                        else skillN += 10;
                    }
                    break;
                case "obereg_8": // Чётки торговца
                    if(skillName == SKILL_COMMERCE) skillN += 15;
                    break;
                case "amulet_6": // Мадонна
                    if(skillName == SKILL_SNEAK)
                    {
                        if(ShipBonus2Artefact(_refCharacter, SHIP_GALEON_SM)) fScale *= 0.75;
                        else fScale *= 0.5;
                    }
                    break;
                case "amulet_7": // Святая вода
                    if(skillName == SKILL_FORTUNE)
                    {
                        if(ShipBonus2Artefact(_refCharacter, SHIP_GALEON_SM)) fScale *= 0.75;
                        else fScale *= 0.5;
                    }
                    break;
            }
        }

        // TALISMAN_ITEM_TYPE
        sItem = GetCharacterEquipByGroup(_refCharacter, TALISMAN_ITEM_TYPE);
        switch(sItem)
        {
            case "talisman11": // Куриный бог
                skillN += 2;
                break;
            case "talisman14": // Жаньи
                if(skillName == SKILL_SAILING) skillN += 15;
                break;
            case "talisman17": // Liber Misericordiae
                if(bHero && skillName == SKILL_DEFENCE && ShipBonus2Artefact(_refCharacter, SHIP_GALEON_SM))
                    skillN += 10;
                break;
            case "kaleuche_amulet2": // Индейский амулет
                skillN += SetCharacterSkillByTuttuat(_refCharacter, skillName);
                break;
        }

        // BLADE_ITEM_TYPE
		skillN += SetCharacterSkillByQuestBlade(_refCharacter, skillName);

		// CIRASS_ITEM_TYPE
		skillN += SetCharacterSkillBySuit(_refCharacter, skillName);

		// GUN_ITEM_TYPE
		skillN += SetCharacterSkillByGun(_refCharacter, skillName);

        // Мангароса
        skillN += SetCharacterSkillByMangarosa(_refCharacter, skillName);

		// Jason: учёт специальных атрибутов
        if(CheckAttribute(_refCharacter, "GenQuest.BladePenalty")) 
        {
            skillN += SetCharacterSkillByPenalty(_refCharacter, skillName);
        }

		//Sinistra: Стартовый морской бой
		if (CheckAttribute(_refCharacter, "GenQuest.MaxSailing"))
		{
			skillN += SetCharacterSkillMaxSailing(_refCharacter, skillName);
		}

		// Действие алкоголя
		if (CheckAttribute(_refCharacter, "chr_ai.drunk.skill." + skillName))
		{
			skillN += sti(_refCharacter.chr_ai.drunk.skill.(skillName));
		}

        // Счетовод
		if(skillName == SKILL_SNEAK && CheckCharacterPerk(_refCharacter, "HT2")) //bHero
		{
			fScale *= 1.15;
		}

		// Множители (должны быть в конце)
		skillN = makeint(skillN * fScale);

    	// Перегруз
    	if (bOverloadCheck && GetItemsWeight(_refCharacter) > GetMaxItemsWeight(_refCharacter))
    	{
   	        skillN -= 20;
    	}
	}

	if (skillN < 1) skillN = 1;
	if (skillN > SKILL_MAX) skillN = SKILL_MAX;

	return skillN;
}
// boal 20.03.2004 -->
int GetShipClassNavySkill(int shipClass)
{
    int needSkill = 0;

    switch (shipClass)
    {
            case 1 : needSkill = 95; break;
            case 2 : needSkill = 80; break;
            case 3 : needSkill = 65; break;			
            case 4 : needSkill = 45; break;			
			case 5 : needSkill = 25; break;
            case 6 : needSkill = 5; break;
            case 7 : needSkill = 1; break;
    }
    return needSkill;
}
// boal 20.03.2004 <--
void DelBakSkillAttr(ref _refCharacter) // boal оптимизация скилов
{
    DeleteAttribute(_refCharacter, "BakSkill");
    DeleteAttribute(_refCharacter, "BakSkillCount");
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
    _chref.TempSailing = GetCharacterSkillSimple(_chref, SKILL_SAILING); // бэкапим её
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

float GetSummonSkillFromNameToOld(ref _refCharacter, string skillName)
{
    return (GetSummonSkillFromName(_refCharacter, skillName) / SKILL_TO_OLD);
}
int GetSummonSkillFromName(ref _refCharacter, string skillName)
{
    int sumSkill;

    // boal 051104 метод тормозит страшно - проверка +1 вещей, будет опрос раз в 10
    if (CheckAttribute(_refCharacter, "BakSkill." + skillName))
    {
        if (sti(_refCharacter.BakSkillCount.(skillName)) < 25 )
        {
            _refCharacter.BakSkillCount.(skillName) = sti(_refCharacter.BakSkillCount.(skillName)) + 1;
            return sti(_refCharacter.BakSkill.(skillName));
        }
    }

    sumSkill = GetSummonSkillFromNameSimple(_refCharacter, skillName);

    // boal 27.01.2004 пенальти за крутой корабль -->
 	sumSkill = ApplayNavyPenaltyToSkill(_refCharacter, skillName, sumSkill);
    // boal 27.01.2004 <--

    _refCharacter.BakSkill.(skillName)      =  sumSkill; // значение
    _refCharacter.BakSkillCount.(skillName) = rand(5); // счетчик немного размажем пересчет

    return sumSkill;
}

int GetSummonSkillFromNameSimple(ref _refCharacter, string skillName)
{
    int sumSkill = GetCharacterSkillSimple(_refCharacter,skillName);

	if (sti(_refCharacter.index) == sti(pchar.index))
	{
	    int iOfficer = -1;
		int iOffSkill = -1;
		switch (skillName)
		{
			/*case SKILL_LEADERSHIP:
				iOfficer = sti(pchar.Fellows.Passengers.boatswain);
			break;*/

			case SKILL_SAILING:
				iOfficer = sti(pchar.Fellows.Passengers.navigator);
			break;

			case SKILL_CANNONS:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;

			case SKILL_ACCURACY:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;

			case SKILL_GRAPPLING:
				iOfficer = sti(pchar.Fellows.Passengers.boatswain);
			break;

			case SKILL_DEFENCE:
				iOfficer = sti(pchar.Fellows.Passengers.doctor);
			break;

			case SKILL_REPAIR:
				iOfficer = sti(pchar.Fellows.Passengers.carpenter);
			break;

			case SKILL_COMMERCE:
				iOfficer = sti(pchar.Fellows.Passengers.treasurer);
			break;
		}

		if(iOfficer != -1)
		{
			iOffSkill = GetCharacterSkillSimple(&characters[iOfficer], skillName);
			if (iOffSkill > sumSkill)
			{
				sumSkill = iOffSkill;
			}
		}
	}
	if(GetCharacterEquipByGroup(pchar, HAT_ITEM_TYPE) == "hat5" && IsCompanion(_refCharacter) && isShipTypeSkill(skillName))
	{
		int mcSkill = GetCharacterSkillSimple(pchar, skillName);
		if (mcSkill > sumSkill)
		{
			sumSkill = mcSkill;
		}
	}
	return sumSkill;
}

void AddPartyExp(ref _refCharacter,int _exp)
{
	/*int cn,i;
	ref chref;
	i = GetOfficersQuantity(_refCharacter);
	_exp = (_exp+i)/(i+1);
	for(i=0; i<4; i++)
	{
		cn = GetOfficersIndex(_refCharacter,i);
		if(cn!=-1)
		{	AddCharacterExp(GetCharacter(cn),_exp);
		}
	}*/
}

void AddExpAndShow(ref chref, int _exp)
{
	// boal Log_SetStringToLog("+" + _exp + XI_ConvertString("add experience"));
	//AddCharacterExp(chref, _exp);
}
// boal -->


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

string GetPerkListText(ref _chref, string _type)
{
    int    perksQ,i;
    int    lngFilePerkID = -1;
	string perkName;
	string ret;
	aref   arPerksRoot;

    lngFilePerkID = LanguageOpenFile("AbilityDescribe.txt");
	// Варианты перков, которые можно добавить
	makearef(arPerksRoot, _chref.perks.list);
	perksQ = GetAttributesNum(arPerksRoot);
	ret = "";
	for(i=0; i<perksQ; i++)
	{
		perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));

        if (CheckAttribute(&ChrPerksList, "list." + perkName) && CheckAttribute(&ChrPerksList, "list." + perkName + ".BaseType"))
        {
            if (ChrPerksList.list.(perkName).BaseType == _type)
            {
                ret += "* " + LanguageConvertString(lngFilePerkID, perkName) + " ";
            }
        }
	}
	LanguageCloseFile(lngFilePerkID);
	return ret;
}
// boal Вес предметов 19.01.2004 -->
float GetItemsWeight(ref _chref)
{
    float   Amount = 0;
    int     j;
    string  itemID;
    ref     itm;

    if (bCabinStarted || bAbordageStarted || !bSeaActive || !CheckAttribute(_chref, "ItemsWeight"))
    {
        for (j=0; j<TOTAL_ITEMS; j++)
    	{
    		makeref(itm,Items[j]);
			
			if(CheckAttribute(itm, "ID"))
			{
				itemID = itm.id;
				if (CheckAttribute(_chref, "items."+itemID) && itemID != "MapsAtlas")      // ugeen - атлас карт не учитываем !!
				{
					Amount += sti(_chref.items.(itemID))*stf(itm.Weight);
				}
			}
        }
        _chref.ItemsWeight = Amount; // оптимицация тормозов в бою на море
    }
    else
    {
        Amount = stf(_chref.ItemsWeight);
    }
    return Amount;
}
int GetMaxItemsWeight(ref _chref)
{
	if (CheckAttribute(_chref, "Skill.FencingS"))
    {
        int iBonus = 0;
        if (IsCharacterPerkOn(_chref, "Grus")) iBonus = 30;
        //опасная рекурсия  если писать GetCharacterSPECIAL
        iBonus = iBonus + CHAR_ITEMS_WEIGHT + GetCharacterSPECIALSimple(_chref, SPECIAL_S)*(GetCharacterSPECIALSimple(_chref, SPECIAL_E) + 12 - MOD_SKILL_ENEMY_RATE);
		if(IsEquipCharacterByArtefact(_chref, "obereg_3")) iBonus = makeint(iBonus * 1.15);
		if(IsEquipCharacterByArtefact(_chref, "indian_7")) iBonus = makeint(iBonus * 0.9);
		if(IsEquipCharacterByArtefact(_chref, "totem_06")) iBonus = makeint(iBonus * 1.10); // belamour legendary edition гонтер
		if(IsEquipCharacterByArtefact(_chref, "talisman13")) iBonus *= 2; // расширенное издание Оберег Таино
		if(CheckAttribute(_chref, "cheats.dopgrus")) iBonus += 1000;
        return  iBonus;
    }
    else
    {
        return 10000; // сундук или труп не имееют скила и ограничения
    }
}
// boal 19.01.2004 <--

// boal -->
int Statistic_AddValue(ref _chref, string _attrName, int _add) // set and get(_add==0) value
{
    // KillShip_ 1..6
    // AbordShip_ 1..6
    // KillAbordShip_ 1..6
    // Solder_s  Solder_g ( s=sword g=gun)
    // Citizen_s  Citizen_g
    // Monster_s Monster_g
    // Warrior_s  Warrior_g
    // Fort
	
	if(!CheckAttribute(_chref, "index")) return 0;
	
    if (sti(_chref.index) != GetMainCharacterIndex()) return 0; // оптимизация
    
    if( !CheckAttribute(_chref,"Statistic." + _attrName) )
    {
        _chref.Statistic.(_attrName) = 0;
    }
    _chref.Statistic.(_attrName) = sti(_chref.Statistic.(_attrName)) + _add;

    if (sti(_chref.Statistic.(_attrName)) < 0)
    {
        _chref.Statistic.(_attrName) = 0;
    }
    return sti(_chref.Statistic.(_attrName));
}
void Statistic_KillChar(aref _attack, aref _enemy, string _attrName)
{
	if(_attrName == "_s") addBonusToBlade(_attack, _enemy);
	if (sti(_attack.index) != GetMainCharacterIndex()) return; // оптимизация
	string  name = GetCharType(_enemy);

		switch (name)
		{
			case "Solder" 	:
				Achievment_SetStat(34, 1);
			break;		
			case "Citizen" 	:
				Achievment_SetStat(35, 1);
			break;
			case "Indian"	:
				Achievment_SetStat(36, 1);
			break;
			case "Monster"	:
				Achievment_SetStat(37, 1);
			break;
			case "Crab"		:
				Achievment_SetStat(38, 1);
			break;	
			case "Pirate"	:
				Achievment_SetStat(53, 1);
			break;
			case "Marginal"		:
				Achievment_SetStat(52, 1);
			break;
		}
	
	name = name + _attrName;

	Statistic_AddValue(_attack, name, 1);
}

string GetCharType(aref _enemy)  //TO_DO переделать на тип в НПС
{
    string  name  	= "Warrior"; // define
    string  model 	= _enemy.model;
	string  _type;
	int     iNation = sti(_enemy.nation);
	
    switch (_enemy.chr_ai.type)
	{
		case LAI_TYPE_PATROL :
		    name = "Solder";
		break
		case LAI_TYPE_GUARDIAN :
		    name = "Solder";
		break
		case LAI_TYPE_OFFICER :
		    name = "Solder";
		break;
        // Citizen
		case LAI_TYPE_ACTOR :
		    name = "Citizen";
		break;
		case LAI_TYPE_BARMAN :
		    name = "Citizen";
		break;
		case LAI_TYPE_CITIZEN :
		    name = "Citizen";
		break;
		case LAI_TYPE_HUBER :
		    name = "Citizen";
		break;
		case LAI_TYPE_HUBERSTAY :
		    name = "Citizen";
		break;
		case LAI_TYPE_MERCHANT :
		    name = "Citizen";
		break;
		case LAI_TYPE_POOR :
		    name = "Citizen";
		break;
		case LAI_TYPE_PRIEST :
		    name = "Citizen";
		break;
		case LAI_TYPE_SIT :
		    name = "Citizen";
		break;
		case LAI_TYPE_STAY :
		    name = "Citizen";
		break;
		case LAI_TYPE_WAITRESS :
		    name = "Citizen";
		break;
		case LAI_TYPE_OWNER :
		    name = "Citizen";
		break;

		case LAI_TYPE_WARRIOR : // to_do преверить тип
			if (findsubstr(model, "canib_" , 0) != -1 || findsubstr(model, "itza_" , 0) != -1 || findsubstr(model, "miskito_" , 0) != -1)
			{
				name = "Indian";
			}
		    if (model == "mummy" || model == "Skel1" || model == "Skel2" || model == "Skel3" || model == "Skel4" || model == "skeletcap" || model == "giant")
		    {
		        name = "Monster";
		    }
		    else
		    {
				if (model == "crabBig")
				{
					name = "Crab";
				}				
                if (findsubstr(model, "off_" , 0) != -1)
                {
                    name = "Solder";
                }
                else
                {
                    if (findsubstr(model, "sold_" , 0) != -1)
	                {
	                    name = "Solder";
	                }
                }
				
				if (findsubstr(model, "pirate_" , 0) != -1 || findsubstr(model, "citiz_" , 0) != -1 || findsubstr(model, "mercen_" , 0) != -1 ) // ugeen 2016
				{
				
					if(CheckAttribute(_enemy,"PhantomType")) 
					{
						_type = _enemy.PhantomType;
						if(_type == "marginal" ) 
						{
							name = "marginal";
						}
					}
					else 
					{
						if(iNation == PIRATE)
						{
							name = "Pirate";
						}					
					}
				}					
				
		    }
		break;
	}

	return  name;
}
// boal statistic info 17.12.2003 <--

// boal Блок здоровье ГГ -->
int GetHealthNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.HP) + 9) / 10.0); // до целого

    return i;
}

int GetHealthMaxNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.maxHP) + 9) / 10.0); // до целого

    return i;
}

string GetHealthName(ref ch)
{
    string name = "";

    switch (GetHealthNum(ch))
    {
        case 1:
            name = ToUpper(StringFromKey("RPGUtilite_2"));
        break;
        case 2:
            name = ToUpper(StringFromKey("RPGUtilite_3"));
        break;
        case 3:
            name = ToUpper(StringFromKey("RPGUtilite_4"));
        break;
        case 4:
            name = ToUpper(StringFromKey("RPGUtilite_5"));
        break;
        case 5:
            name = ToUpper(StringFromKey("RPGUtilite_6"));
        break;
        case 6:
            name = ToUpper(StringFromKey("RPGUtilite_7"));
        break;
    }
    return name;
}

string GetHealthNameMaxSmall(ref ch)
{
    string name = "";

    switch (GetHealthMaxNum(ch))
    {
        case 1:
            name = StringFromKey("RPGUtilite_2");
        break;
        case 2:
            name = StringFromKey("RPGUtilite_3");
        break;
        case 3:
            name = StringFromKey("RPGUtilite_4");
        break;
        case 4:
            name = StringFromKey("RPGUtilite_5");
        break;
        case 5:
            name = StringFromKey("RPGUtilite_6");
        break;
        case 6:
            name = StringFromKey("RPGUtilite_7");
        break;
    }
    return name;
}

void SetNewDayHealth()
{
    ref mainChr = GetMainCharacter();

    float maxhp = stf(mainChr.chr_ai.hp_max);
    float damg  = stf(mainChr.Health.Damg);
    int   add   = 0;

    mainChr.Health.Damg = 0.0;

    if (IsCharacterPerkOn(mainChr, "Medic"))
    {
        add = 1;
    }
	if(IsEquipCharacterByArtefact(mainChr, "amulet_6"))
	{
		if(ShipBonus2Artefact(mainChr, SHIP_GALEON_SM)) add += 1;
		add += 1;
	}
    if (damg >= (maxhp / 1.5) )
    {
        if ((damg / maxhp) > add)
        {
            AddCharacterHealth(mainChr, -damg / maxhp + add);
        }
    }
    else
    {
        if (!IsEntity(&worldMap)) // не на карте
        {
            AddCharacterHealth(mainChr, 1 + add);
        }
        else
        {
            AddCharacterHealth(mainChr, 0.5 + add / 2.0);
        }
    }
}

void SetNewDayHealthMax()
{
    ref mainChr = GetMainCharacter();

    float maxhp = stf(mainChr.chr_ai.hp_max);
    float damg  = stf(mainChr.Health.weekDamg);

    mainChr.Health.weekDamg = 0.0;
	// belamour legendary edition отменное здоровье защищает от инвалидности
	if(CheckCharacterPerk(mainChr, "Medic")) maxhp *= 1.3;
    float fShipBonus = 1.15;
	if(ShipBonus2Artefact(mainChr, SHIP_GALEON_SM)) fShipBonus = 1.25;
    if (damg > (maxhp * 3.5 * isEquippedAmuletUse(mainChr, "amulet_6", 1.0, fShipBonus)))
    {
        AddCharacterMaxHealth(mainChr, -1);
    }
}

void AddCharacterHealth(ref mainChr, float add)
{
	// belamour расширенное издание
	if(mainChr.id == "Blaze" && IsEquipCharacterByArtefact(pchar, "talisman12")) return;
	
    float maxhp = stf(mainChr.chr_ai.hp_max);
    int   remHP = GetHealthNum(mainChr);

    mainChr.Health.HP = makefloat(stf(mainChr.Health.HP) + add);

    if (stf(mainChr.Health.HP) < 1)
    {
        mainChr.Health.HP = 1.0;
    }

    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }

    if (GetHealthNum(mainChr) > remHP)
    {
		notification(StringFromKey("RPGUtilite_8"),"HealthUp");
        //Log_Info("Здоровье стало лучше");
    }

    if (GetHealthNum(mainChr) < remHP)
    {
        //Log_Info("Здоровье стало хуже");
		notification(StringFromKey("RPGUtilite_9"),"HealthDown");
		if(CheckAttribute(mainChr,"systeminfo.tutorial.health"))
		{
			LaunchTutorial("Health", 1);
			DeleteAttribute(mainChr,"systeminfo.tutorial.health");
		}
    }
}

void AddCharacterMaxHealth(ref mainChr, float add)
{
	// belamour расширенное издание
	if(mainChr.id == "Blaze" && IsEquipCharacterByArtefact(pchar, "talisman12")) return;
	
    mainChr.Health.maxHP = makefloat(stf(mainChr.Health.maxHP) + add);

    if (stf(mainChr.Health.maxHP) < 1)
    {
        mainChr.Health.maxHP = 1.0;
    }

    if (stf(mainChr.Health.maxHP) > 60)
    {
        mainChr.Health.maxHP = 60.0;
    }

    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }
}
// boal Блок здоровье ГГ <--

// увеличение счетчика награды за голову -->
int ChangeCharacterHunterScore(ref chref, string _huntName, int incr)
{
	int prevVal = -5; // мин набор

	if (_huntName == "pirhunter") return 0;
	if (CheckAttribute(chref, "GenQuest.HunterScore2Pause")) incr = 0;

	if (CheckAttribute(chref, "reputation." + _huntName) )	prevVal = sti(chref.reputation.(_huntName));

	int newVal = prevVal + incr;
	if (newVal < -100)  newVal = -100;
	if (newVal > 100)   newVal = 100;

	chref.reputation.(_huntName) = newVal;

	if( sti(chref.index) != GetMainCharacterIndex() ) return newVal;

	if (newVal >= 10)
	{
	 	if (prevVal < newVal)
		{
			//Log_SetStringToLog(XI_ConvertString(_huntName) + " увеличила награду за Вашу голову");
			notification(StringFromKey("RPGUtilite_10"), _huntName);
		}

	    if (prevVal > newVal)
		{
			notification(StringFromKey("RPGUtilite_11"), _huntName);
	        //Log_SetStringToLog(XI_ConvertString(_huntName) + " снизила награду за Вашу голову");
		}
	}
	else
	{
		if (incr<0)
		{
			notification(StringFromKey("RPGUtilite_12"), _huntName);
		}
		if (incr>0)
		{
			notification(StringFromKey("RPGUtilite_13"), _huntName);
		}
		/* int iNation = 0;
		switch (_huntName) // код для совместимости со старым
		{
		    case "enghunter":  iNation = ENGLAND; break;
		    case "frahunter":  iNation = FRANCE; break;
		    case "spahunter":  iNation = SPAIN; break;
		    case "holhunter":  iNation = HOLLAND; break;
		}
		string prevName = GetNationReputationName(iNation, -prevVal);
		string newName  = GetNationReputationName(iNation, -newVal);
		if (prevName!=newName)
		{
			string outString = XI_ConvertString("Your reputation with country")+ XI_ConvertString(Nations[iNation].Name + "Gen") +" ";
			if (incr<0)	{outString+=XI_ConvertString("increase");}
			else	{outString+=XI_ConvertString("decrease");}
			outString += " "+XI_ConvertString("to")+" "+newName;
			Log_SetStringToLog(outString);
		} */
	}
	return newVal;
}

int ChangeCharacterNationReputation(ref chref, int _Nation, int incr)
{
	return -ChangeCharacterHunterScore(chref, NationShortName(_Nation) + "hunter", -incr); // все наоборот, - это хорошо, + есть НЗГ
}

string GetNationReputation(ref chref, int _Nation)
{
    return GetNationReputationName(_Nation, ChangeCharacterNationReputation(chref, _Nation, 0));
}

string GetNationReputationName(int _Nation, int i)
{
	if (i <= -50)  return StringFromKey("RPGUtilite_14");
	if (i <= -30)  return StringFromKey("RPGUtilite_15");
	if (i <= -16)  return StringFromKey("RPGUtilite_16");
	if (i <= -10)  return StringFromKey("RPGUtilite_17");
	if (i <= 20)  return StringFromKey("RPGUtilite_18");
	if (i <= 50)  return StringFromKey("RPGUtilite_19");
	if (i <= 80)  return StringFromKey("RPGUtilite_20");
	if (i <= 100) return StringFromKey("RPGUtilite_21");

    return StringFromKey("RPGUtilite_18"); // Нейтралитет
}

string GetFactionReputationName(int i)
{
	if (i <= 5)  return StringFromKey("RPGUtilite_14");
	if (i <= 19)  return StringFromKey("RPGUtilite_15");
	if (i <= 39)  return StringFromKey("RPGUtilite_16");
	if (i <= 60)  return StringFromKey("RPGUtilite_18");
	if (i <= 80)  return StringFromKey("RPGUtilite_19");
	if (i <= 94)  return StringFromKey("RPGUtilite_20");
	if (i <= 100)  return StringFromKey("RPGUtilite_21");

    return StringFromKey("RPGUtilite_18"); // Нейтралитет
}
// boal 04.04.04
string NationShortName(int iNation)
{
    switch(iNation)
	{
		case ENGLAND:
            return "eng";
		break;
		case FRANCE:
            return "fra";
		break;
		case SPAIN:
            return "spa";
		break;
		case HOLLAND:
			return "hol";
		break;
		case PIRATE:
			return "pir";
		break;
	}
	return "eng";
}
// увеличение счетчика награды за голову <--


void setWDMPointXZ(string _location)
{
    // координаты на глобал карте -->
    int n;
	string sTemp;

    n = FindIslandBySeaLocation(_location);
	if(n!=-1)
	{
		worldMap.island = Islands[n].id;
		Pchar.curIslandId = worldMap.island; // fix
		sTemp = worldMap.island;
		if (CheckAttribute(&worldMap, "islands." + sTemp))
		{
		    worldMap.zeroX = worldMap.islands.(sTemp).position.x;
			worldMap.zeroZ = worldMap.islands.(sTemp).position.z;
			if (CheckAttribute(&worldMap, "islands." + sTemp + "." + _location))
			{
			    worldMap.playerShipX = worldMap.islands.(sTemp).(_location).position.x;
				worldMap.playerShipZ = worldMap.islands.(sTemp).(_location).position.z;
				//trace(sTemp + "." + _location);
			}
			else
			{// для бухт с незаданными координатами
			    worldMap.playerShipX = worldMap.zeroX;
				worldMap.playerShipZ = worldMap.zeroZ;
			}
		}
	}
	// координаты на гловал карте <--
}


// нужно не перекрывать еще и признаки фантома
void ChangeAttributesFromCharacter(ref CopyChref, ref PastChref, bool _dialogCopy)
{
    aref arToChar;
    aref arFromChar;

    CopyChref.model            = PastChref.model;
    CopyChref.model.animation  = PastChref.model.animation;
    CopyChref.sex              = CopyChref.sex;
    CopyChref.headModel        = PastChref.headModel;
    CopyChref.FaceId           = PastChref.FaceId;
    CopyChref.nation           = PastChref.nation;

	CopyChref.name             = PastChref.name;
    CopyChref.lastname         = PastChref.lastname;

    CopyChref.rank             = PastChref.rank;
    CopyChref.reputation       = makeint(PastChref.reputation);
	
	CopyChref.baseCapIdx       = PastChref.index; //Id оригинального в структуру клона

    if (CheckAttribute(PastChref, "loyality"))
    {
    	CopyChref.loyality         = PastChref.loyality;
	}
	else DeleteAttribute(CopyChref, "loyality");
	if (CheckAttribute(PastChref, "alignment"))
	{
    	CopyChref.alignment        = PastChref.alignment;
    }
    else DeleteAttribute(CopyChref, "alignment");

    CopyChref.Money            = PastChref.Money;

    CopyChref.chr_ai.hp         = makeint(PastChref.chr_ai.hp);
    CopyChref.chr.chr_ai.hp_max = makeint(PastChref.chr_ai.hp_max);

    LAi_SetHP(CopyChref, makeint(PastChref.chr_ai.hp_max), makeint(PastChref.chr_ai.hp_max));
	LAi_SetCurHPMax(CopyChref);
	
	//копируем структуру quest от оригинального кэпа, очень нужно по квестам :)
	if (CheckAttribute(PastChref, "quest"))
    {
	    aref arToCharQuest, arFromCharQuest;
		makearef(arFromCharQuest, PastChref.quest);
		makearef(arToCharQuest, CopyChref.quest);
		DeleteAttribute(arToCharQuest, "");
		CopyAttributes(arToCharQuest, arFromCharQuest);
	}
	
	if (CheckAttribute(PastChref, "quest.officertype"))
    {
        CopyChref.quest.officertype     =   PastChref.quest.officertype;
    }
    else
    {
        DeleteAttribute(CopyChref, "quest.officertype");
    }

    if (CheckAttribute(PastChref, "Payment"))
    {
        CopyChref.Payment     =   PastChref.Payment; // платить ЗП
    }
    else
    {
        DeleteAttribute(CopyChref, "Payment");
    }
    if (CheckAttribute(PastChref, "HoldEquip"))
    {
        CopyChref.HoldEquip   =   PastChref.HoldEquip; // не отдавать саблю и пистоль
    }
	else
    {
        DeleteAttribute(CopyChref, "HoldEquip");
    }
    if (CheckAttribute(PastChref, "SaveItemsForDead"))
    {
        CopyChref.SaveItemsForDead   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "SaveItemsForDead");
    }
    if (CheckAttribute(PastChref, "DontClearDead"))
    {
        CopyChref.DontClearDead   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "DontClearDead");
    }
    if (CheckAttribute(PastChref, "OfficerWantToGo.DontGo"))
    {
        CopyChref.OfficerWantToGo.DontGo   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "OfficerWantToGo.DontGo");
    }
    // skill
    DeleteAttribute(CopyChref, "skill");
    CopyChref.skill = "";

    makearef(arToChar, CopyChref.skill);
    makearef(arFromChar, PastChref.skill);

    CopyAttributes(arToChar,arFromChar);

    // SPECIAL
    DeleteAttribute(CopyChref, "SPECIAL");
    CopyChref.SPECIAL = "";

    makearef(arToChar, CopyChref.SPECIAL);
    makearef(arFromChar, PastChref.SPECIAL);

    CopyAttributes(arToChar,arFromChar);

    // Statistic
    DeleteAttribute(CopyChref, "Statistic");
    CopyChref.Statistic = "";

    makearef(arToChar, CopyChref.Statistic);
    makearef(arFromChar, PastChref.Statistic);

    CopyAttributes(arToChar,arFromChar);

    // perks
    DeleteAttribute(CopyChref, "perks");
    CopyChref.perks = "";

    makearef(arToChar, CopyChref.perks);
    makearef(arFromChar, PastChref.perks);

    CopyAttributes(arToChar,arFromChar);
    // items
    DeleteAttribute(CopyChref, "Items");
    CopyChref.Items = "";

    makearef(arToChar, CopyChref.Items);
    makearef(arFromChar, PastChref.Items);

    CopyAttributes(arToChar,arFromChar);
	
	// equipped items
	DeleteAttribute(CopyChref, "equip_item");
	CopyChref.equip_item = "";
	makearef(arToChar, CopyChref.equip_item);
    makearef(arFromChar, PastChref.equip_item);

    CopyAttributes(arToChar,arFromChar);
	

    if (CheckAttribute(PastChref, "equip.blade"))
    {
		CopyChref.equip.blade =   PastChref.equip.blade;
	}
	if (CheckAttribute(PastChref, "equip.gun"))
    {
		CopyChref.equip.gun   =   PastChref.equip.gun;
	}
	if (CheckAttribute(PastChref, "equip.musket"))
    {
		CopyChref.equip.musket =   PastChref.equip.musket;
	}
	if (CheckAttribute(PastChref, "CanTakeMushket"))
    {
		CopyChref.CanTakeMushket = PastChref.CanTakeMushket;
	}
	if (CheckAttribute(PastChref, "PriorityMode"))
    {
		CopyChref.PriorityMode = sti(PastChref.PriorityMode);
	}
	if (CheckAttribute(PastChref, "MusketerDistance"))
    {
		CopyChref.MusketerDistance = sti(PastChref.MusketerDistance);
	}
	// belamour legendary edition зарядим огнестрел 
	if (CheckAttribute(PastChref, "chr_ai.gun.bullet"))
	{
		LAi_SetCharacterUseBullet(CopyChref, GUN_ITEM_TYPE, PastChref.chr_ai.gun.bullet); 
	}
	if (CheckAttribute(PastChref, "chr_ai.musket.bullet"))
	{
		LAi_SetCharacterUseBullet(CopyChref, MUSKET_ITEM_TYPE, PastChref.chr_ai.musket.bullet); 
	}
	// health
	if (CheckAttribute(PastChref, "Health.TotalDamg"))
    {
		CopyChref.Health.TotalDamg =   PastChref.Health.TotalDamg;
	}
	else
	{
        CopyChref.Health.TotalDamg = 0;
	}
	
	if (CheckAttribute(PastChref, "PerkValue.EnergyPlus"))
	{
		CopyChref.PerkValue.EnergyPlus =   PastChref.PerkValue.EnergyPlus;
	}

	// ugeen --> нужно для генерации различных ситуации в каюте абордированного кэпа
	if (CheckAttribute(PastChref,"Situation")) // если в каюте кэпа возникла ситуация 
	{
		CopyChref.Situation = PastChref.Situation;
		CopyChref.Situation.type = PastChref.Situation.type;
	}
	
	if (CheckAttribute(PastChref,"EncType"))
	{
		CopyChref.EncType = PastChref.EncType;
	}
	
	if (CheckAttribute(PastChref,"RealEncounterType"))
	{
		CopyChref.RealEncounterType = PastChref.RealEncounterType;
	}

	if (CheckAttribute(PastChref,"Ship"))
	{
		makearef(arToChar, CopyChref.Back.Ship);
		makearef(arFromChar, PastChref.Ship);
		CopyAttributes(arToChar, arFromChar);		
	}	
	// <-- ugeen
	
	if (_dialogCopy && CheckAttribute(PastChref, "Dialog.Filename"))
	{
	    CopyChref.Dialog.Filename    = PastChref.Dialog.Filename;
	    CopyChref.Dialog.CurrentNode = PastChref.Dialog.CurrentNode;
	    if (CheckAttribute(PastChref, "greeting")) CopyChref.greeting = PastChref.greeting; //eddy.нет логам!
		else
		{
			DeleteAttribute(CopyChref, "greeting");
		}
	}
	SetEnergyToCharacter(CopyChref);
	//SetNewModelToChar(CopyChref);  // чтоб сабли были правильные
}

int GetCharacterLoyality(ref chr)
{
    if (CheckAttribute(chr, "loyality"))
    {
        if (sti(chr.loyality) > MAX_LOYALITY)
        {
            chr.loyality = MAX_LOYALITY;
        }
        if (sti(chr.loyality) < 0)
        {
            chr.loyality = 0;
        }
        return sti(chr.loyality);
    }
    else
    {
        return  0; // для пленных и гг
    }
}

void CCS_SetNewMainCharacter(ref ch, int num)
{
	if(num < 1) num = 1;
	switch (num)
	{
		case 1: //Шарль де Мор
			ch.FaceId 				= 201;
			ch.HeroModel 			= "Sharle_1,Sharle_2,Sharle_3,Sharle_4,Sharle_5,protocusto,Sharle_6,Sharle_8,Sharle_7,Sharle_9,Sharle_1,Sharle_11,Sharle_12,Sharle_13,Sharle_14"
			ch.name 				= GetNewMainCharacterParam("heroName_1");
			ch.lastname				= GetNewMainCharacterParam("heroLastname_1");
			ch.nameGen				= GetNewMainCharacterParam("heroNameGen_1");
			ch.lastnameGen			= GetNewMainCharacterParam("heroLastnameGen_1");
			ch.nameDat				= GetNewMainCharacterParam("heroNameDat_1");
			ch.lastnameDat			= GetNewMainCharacterParam("heroLastNameDat_1");
			ch.sex					= "man";
			ch.model.animation 		= "Sharle_1";
			ch.HeroParam.HeroType 	= "HeroType_1";
			ch.nation				= FRANCE;
			ch.BaseNation			= FRANCE;
			ch.info					= GetNewMainCharacterParam("hero_1");
		break;
		case 2: // Диего  де Монтойя
//			return;			
			
			ch.FaceId 				= 203;
			ch.HeroModel 			= "Diego_1,Diego_2,Diego_3,Diego_4,Diego_5,protocusto,Diego_6,Diego_8,Diego_1,Diego_9,Diego_1,Diego_11,Diego_12,Diego_13,Diego_14";
			ch.name 				= GetNewMainCharacterParam("heroName_2");
			ch.lastname				= GetNewMainCharacterParam("heroLastname_2");
			ch.nameGen				= GetNewMainCharacterParam("heroNameGen_2");
			ch.lastnameGen			= GetNewMainCharacterParam("heroLastnameGen_2");
			ch.nameDat				= GetNewMainCharacterParam("heroNameDat_2");
			ch.lastnameDat			= GetNewMainCharacterParam("heroLastNameDat_2");
			ch.sex					= "man";
			ch.model.animation 		= "Diego_1";
			ch.HeroParam.HeroType 	= "HeroType_3";
			ch.nation				= SPAIN;
			ch.BaseNation			= SPAIN;
			ch.info					= GetNewMainCharacterParam("hero_2");
		break;		
		case 3: // Паттерсон
//			return;
			
			ch.FaceId 				= 202;
			ch.HeroModel 			= "Willy_1,Willy_2,Willy_3,Willy_4,Willy_5,protocusto,Willy_6,Willy_8,Willy_1,Willy_9,Willy_1,Willy_11,Willy_12,Willy_13,Willy_14";
			ch.name 				= GetNewMainCharacterParam("heroName_3");
			ch.lastname				= GetNewMainCharacterParam("heroLastname_3");
			ch.nameGen				= GetNewMainCharacterParam("heroNameGen_3");
			ch.lastnameGen			= GetNewMainCharacterParam("heroLastnameGen_3");
			ch.nameDat				= GetNewMainCharacterParam("heroNameDat_3");
			ch.lastnameDat			= GetNewMainCharacterParam("heroLastNameDat_3");
			ch.sex					= "man";
			ch.model.animation 		= "Willy_1";
			ch.HeroParam.HeroType 	= "HeroType_2";
			ch.nation				= ENGLAND;
			ch.BaseNation			= ENGLAND;
			ch.info 				= GetNewMainCharacterParam("hero_3");
		break;
		case 4: // Элен
//			return;
			
			ch.FaceId 				= 250;
			ch.HeroModel 			= "Rumba";
			ch.name 				= GetNewMainCharacterParam("heroName_4");
			ch.lastname				= GetNewMainCharacterParam("heroLastname_4");
			ch.nameGen				= GetNewMainCharacterParam("heroNameGen_4");
			ch.lastnameGen			= GetNewMainCharacterParam("heroLastnameGen_4");
			ch.nameDat				= GetNewMainCharacterParam("heroNameDat_4");
			ch.lastnameDat			= GetNewMainCharacterParam("heroLastNameDat_4");
			ch.sex					= "woman";
			ch.model.animation 		= "rumba";
			ch.HeroParam.HeroType 	= "HeroType_1";
			ch.nation				= ENGLAND;
			ch.BaseNation			= ENGLAND;
			ch.info 				= GetNewMainCharacterParam("hero_4");
		break;
	}	
	
	ch.model = GetSubStringByNum(ch.HeroModel, 0);
	ch.cirassIDX = 0;
	
	if(ch.sex == "woman")
	{
		ch.model.height = 1.75;
	}
    else
    {
		ch.model.height = 1.8;
	}
}

int CCS_GetNewMainCharacterFace(ref ch)
{
    return sti(ch.FaceId);
}

// boal 091004 много героев  -->
// boal 23.01.2004 выбор персонажа-->
void setNewMainCharacter(ref ch, int num)
{
	string heroModel, heroFaceId;
	int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    totalInfo = LanguageConvertString(idLngFile, "heroFace_" + num);
    heroFaceId  = sti(totalInfo);
    ch.FaceId   = heroFaceId;

    totalInfo = LanguageConvertString(idLngFile, "heroModel_" + num);
    ch.HeroModel = totalInfo;
    ch.model	= GetSubStringByNum(ch.HeroModel, 0);
    ch.headModel = "h_" + ch.model;

    totalInfo = LanguageConvertString(idLngFile, "heroName_" + num);
    ch.name 	=  totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "heroLastname_" + num);
    ch.lastname = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "sex_" + num);
    ch.sex = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "animation_" + num);
    ch.model.animation = totalInfo;

    if(ch.sex == "woman")
	{
		ch.model.height = 1.75;
	}
    else
    {
		ch.model.height = 1.8;
	}

    LanguageCloseFile(idLngFile);
    // для НПС
    ch.HeroParam.HeroType = GetNewMainCharacterType(num);
    ch.nation             = GetNewMainCharacterNation(num);
}

string GetNewMainCharacterType(int _startHeroType)
{
	string ret;
    switch (_startHeroType) 
	{
        case 1:
    	    ret = "HeroType_1";
	    break;
        case 2:
    	    ret = "HeroType_2";
	    break;
        case 3:
    	    ret = "HeroType_3";
	    break;
        case 4:
    	    ret = "HeroType_4";
	    break;	    
	}
	return ret;
}


void initNewMainCharacter()//инициализация главного героя
{
	ref ch = GetMainCharacter();
	string sTemp;
	int    iTmp, i;

    CCS_SetNewMainCharacter(ch, startHeroType);
    // контроль версий -->
    InitMigrations();
    // контроль версий <--

	// Установим начальный дневной рандом
    UpdateSeeds();
    ch.PersonalSeed = rand(1000000); // уникальное число для рандома с хэшем
    // ROSARAK WEIGHT RANDOM (ВАЖНО ТУТ)
    InitWeightParameters();

    MOD_EXP_RATE =  makeint(MOD_EXP_RATE + MOD_SKILL_ENEMY_RATE * MOD_EXP_RATE / 1.666666666); // разные уровни для всех
    if (MOD_EXP_RATE < 10) MOD_EXP_RATE = 10; // иначе будет развал целостности данных, порог релиховой версии бля всех сложностей.

	// куда плывем	
	switch (sti(ch.nation))
	{
		case ENGLAND : 
			if(startHeroType == 4) ch.HeroParam.ToCityId = "SantaCatalina";
			else ch.HeroParam.ToCityId = "PortRoyal";
		break;
		case FRANCE  : 
			if(SandBoxMode) ch.HeroParam.ToCityId = "BasTer";
			else ch.HeroParam.ToCityId = "Charles";
		break;
		case SPAIN :   ch.HeroParam.ToCityId = "Santiago"; break;
		case HOLLAND : FindAlliedColonyForNation(sti(ch.nation), true); break;
		case PIRATE :  ch.HeroParam.ToCityId = "Pirates"; break;
	}

	// откуда плывем
    ch.HeroParam.FromCityId  = Colonies[FindNonEnemyColonyForAdventure(sti(ch.nation), ch.HeroParam.ToCityId, true)].id;

	// где появимся	
	ch.HeroParam.Location = ch.HeroParam.ToCityId + "_town";
	ch.HeroParam.Group    = "reload";
	ch.HeroParam.Locator  = "reload1";
	
	setCharacterShipLocation(ch, ch.HeroParam.Location);
    setWDMPointXZ(ch.HeroParam.Location);  // коорд на карте
    
	// а надо ли нам это ?
	SetTimerCondition("Move_Govenour", 0, 0, 25 + rand(10), true); // to_do перенести в один метод инициации
	
	//Запускаем проверку на падение здоровья раз в 5 дней
    SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
    
    SetTimerCondition("Nation_Legend", 0, 0, 25 + rand(10), true);

	// Jason: новая усадка генерал-губернаторов. На постоянке - Пуанси, Виндзор, Фокс, де Кордова
	SetGovenoursToResidence();

	ReloadProgressUpdate();

 	SetNationRelations();
 	// от кого драпаем
	ch.HeroParam.EnemyNation  = FindEnemyNation2Nation(sti(ch.nation));
	
    // boal вешаем прерывание на охотников навечно (для моря и земли) -->
    SetTimerCondition("SeaHunterCheck", 0, 0, 6, true);
    SaveCurrentQuestDateParam("Land_HunterTimerEng");
    SaveCurrentQuestDateParam("Land_HunterTimerFra");
    SaveCurrentQuestDateParam("Land_HunterTimerSpa");
    SaveCurrentQuestDateParam("Land_HunterTimerHol");
    // boal вешаем прерывание на охотников навечно (для моря и земли) <--
    LAi_SetHP(ch, LAI_DEFAULT_HP, LAI_DEFAULT_HP);

    ch.HeroParam.HeroType = NullCharacter.HeroParam.HeroType;

	SetSPECIAL(ch, 4,4,4,4,4,4,4);
	switch (ch.HeroParam.HeroType)
	{        
		case "HeroType_1":	//Дуэлянт
			SetSPECIAL(ch, 5, 7, 6, 5, 6, 9, 5);
			SetSelfSkill(ch, 15, 5, 3, 5, 10);
			SetShipSkill(ch, 12, 5, 6, 3, 3, 3, 3, 3, 15);
			SetCharacterPerk(ch, "CriticalHit");
			SetCharacterPerk(ch, "HT1");
			SetCharacterPerk(ch, "FencingMaster");
			SetCharacterPerk(ch, "TannedLeather");
		break;
		
		case "HeroType_2":	//Счетовод
			SetSPECIAL(ch,  6, 5, 6, 9, 6, 4, 7);
			SetSelfSkill(ch, 4, 15, 4, 5, 8);
			SetShipSkill(ch, 15, 15, 3, 3, 3, 3, 3, 3, 8);
			SetCharacterPerk(ch, "Trustworthy");
			SetCharacterPerk(ch, "HT2");
			SetCharacterPerk(ch, "RatsWolf");
			SetCharacterPerk(ch, "Mimicry");
			SetCharacterPerk(ch, "TreasureHunter");
		break;
		
		case "HeroType_3":	//Атлет
			SetSPECIAL(ch, 9, 5, 8, 4, 5, 6, 6);
			SetSelfSkill(ch, 3, 5, 15, 5, 7);
			SetShipSkill(ch, 5, 3, 3, 8, 3, 10, 8, 3, 3);
			SetCharacterPerk(ch, "Tireless");
			SetCharacterPerk(ch, "HT3");
			SetCharacterPerk(ch, "Dragoon");
			SetCharacterPerk(ch, "SecondWind");
		break;
		
		case "HeroType_4":	//Стрелок
			SetSPECIAL(ch, 4, 8, 7, 4, 5, 6, 9);
			SetSelfSkill(ch, 5, 5, 5, 15, 20);
			SetShipSkill(ch, 10, 3, 15, 12, 3, 3, 3, 3, 12);
			SetCharacterPerk(ch, "Gunman");
			SetCharacterPerk(ch, "HT4");
			SetCharacterPerk(ch, "Jager");
			SetCharacterPerk(ch, "Bombardier");
			SetCharacterPerk(ch, "Sniper");
		break;
	}
	
	ch.skill.freeskill   = 0;
	ch.Skill.FreeSPECIAL = 0;
	sGlobalTemp   = "Flag" + NationShortName(sti(ch.nation));
	SetCharacterPerk(ch, sGlobalTemp); // перк флага нации
	SetCharacterPerk(ch, "FlagPir");
	SetCharacterPerk(ch, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
	SetCharacterPerk(ch, "Rush");
    ch.BonusPush = ""; // Rosarak - Коллизии
	// начальные скилы задать
    //InitStartParam(ch); // Jason - fix
	LAi_SetHP(ch, GetCharacterBaseHPValue(ch), GetCharacterBaseHPValue(ch));
    SetEnergyToCharacter(ch);
    TreasureTiersInit(SandBoxMode); // Инитим сокровища ДО выдачи карты
    if (!SandBoxMode) initMainCharacterItem(); // Сюжет
    else initMainFreePlayCharacterItem();
	
	ReloadProgressUpdate();	
    DeleteAttribute(ch, "Ship");
    
	if (!SandBoxMode)	// Сюжет
	{
		ch.Ship.Type = SHIP_NOTUSED;
		/*Ch.GenQuest.VideoAVI = "intro_Sharle";
		Ch.GenQuest.VideoAfterQuest = "SharlieTutorial_StartGame";
		DoQuestCheckDelay("PostVideo_Start", 0.2);*/
		loadedLocation = &Locations[0];
		pchar.systeminfo.LockFader = "loading\Start_Loading.tga";
		pchar.systeminfo.BLIoff = true;
		QuestToSeaLogin_Prepare(0.0, 0.0, "");
		QuestToSeaLogin_Launch();
		
		bQuestDisableMapEnter = true;
		pchar.GenQuest.CabinLock = true;
		bDisableCharacterMenu = true;
		InterfaceStates.Buttons.Save.enable = false;
		bCannonsRangeShow = false;
		//SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, argb(0,255,255,255), argb(0,255,255,255), argb(0,255,0,0), argb(0,255,0,0), 0.002, 0.002, 0);
		//DoQuestFunctionDelay("ChangeInterface", 1.1);
		DoQuestFunctionDelay("SharlieTutorial_Music", 1.1);
		DoQuestFunctionDelay("SharlieTutorial_PogodaRefresh", 0.1);
		DoQuestFunctionDelay("SharlieTutorial_RadiusCannonsOff", 1.5);
		
		pchar.Ship.Type = GenerateShipExt(SHIP_PINNACE, true, pchar);
		pchar.Ship.name = StringFromKey("SharlieTutorial_6");
		SetBaseShipData(pchar);
		RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull = 2;
		SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
		realships[sti(pchar.ship.type)].SpeedRate = 18;
		realships[sti(pchar.ship.type)].Capacity = 6500;
		realships[sti(pchar.ship.type)].WindAgainstSpeed = 1.3;
		pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
		SetCrewQuantityFull(pchar);
		pchar.ship.Crew.Morale = 100;
		ChangeCrewExp(pchar, "Sailors", 100);
		ChangeCrewExp(pchar, "Cannoners", 100);
		ChangeCrewExp(pchar, "Soldiers", 100);
		SetCharacterGoods(pchar, GOOD_BALLS, 0);
		SetCharacterGoods(pchar, GOOD_GRAPES, 0);
		SetCharacterGoods(pchar, GOOD_KNIPPELS, 0);
		SetCharacterGoods(pchar, GOOD_BOMBS, 0);
		SetCharacterGoods(pchar, GOOD_POWDER, 0);
		SetCharacterGoods(pchar, GOOD_WEAPON, 0);
		
		SetCurrentTime(19, 00);
		CreateWeatherEnvironment();
		WeatherParams.Rain 			= false;
		WeatherParams.Rain.ThisDay 	= false;
		pchar.questTemp.TimeLock = true;
		
		SeaCameras_SetShipCameraAy(115.0);
		
		DoQuestCheckDelay("SharlieTutorial_StartGame", 4.0);
	}
	else
	{
		if(startHeroType == 4) ch.Ship.Type = GenerateShipExt(SHIP_SCHOONER_W, 0, ch);//элен
		else ch.Ship.Type = GenerateShipExt(SHIP_WAR_TARTANE, 0, ch);//остальные
		SetBaseShipData(ch);
		if(startHeroType == 4)
		{
			RealShips[sti(ch.Ship.Type)].MaxCaliber = 18;
			//RealShips[sti(ch.Ship.Type)].CannonsQuantity = 10;
			RealShips[sti(ch.Ship.Type)].MinCrew = 13;
			RealShips[sti(ch.Ship.Type)].OptCrew = 96;
			RealShips[sti(ch.Ship.Type)].MaxCrew = 120;
			RealShips[sti(ch.Ship.Type)].SpeedRate = 15.00;
			RealShips[sti(ch.Ship.Type)].TurnRate = 60.00;
			RealShips[sti(ch.Ship.Type)].Capacity = 1500;
			RealShips[sti(ch.Ship.Type)].HP = 1600;
			SetCrewQuantity(ch, GetMaxCrewQuantity(ch));
		}
		if(startHeroType == 4) ch.Ship.Name = StringFromKey("RPGUtilite_22");
		else ch.Ship.Name = StringFromKey("RPGUtilite_23");
		RealShips[sti(ch.Ship.Type)].MinCrew = 3;
		RealShips[sti(ch.Ship.Type)].OptCrew = 12;
		RealShips[sti(ch.Ship.Type)].MaxCrew = 15;
		RealShips[sti(ch.Ship.Type)].SpeedRate = 11.50;
		RealShips[sti(ch.Ship.Type)].TurnRate = 74.00;
		RealShips[sti(ch.Ship.Type)].HP = 400;
		/* UpgradeShipParameter(ch, "SpeedRate");
		UpgradeShipParameter(ch, "TurnRate");
		UpgradeShipParameter(ch, "WindAgainstSpeed");
		UpgradeShipParameter(ch, "HP");
		UpgradeShipParameter(ch, "MaxCrew"); */
		if(startHeroType != 4) UpgradeShipFull(ch);
		if(CheckAttribute(&RealShips[sti(ch.Ship.Type)], "Tuning.Capacity"))
		{
			DegradeShipParameter(ch, "Capacity");
			DeleteAttribute(&RealShips[sti(ch.Ship.Type)],"DontTuning.Capacity");
			DeleteAttribute(&RealShips[sti(ch.Ship.Type)],"Tuning.Capacity");
		}
		RealShips[sti(ch.Ship.Type)].Capacity = 334;
		UpgradeShipParameter(ch, "Capacity");
		SetCrewQuantity(ch, GetOptCrewQuantity(ch));
		SetCharacterGoods(ch, GOOD_BALLS, 20);
		SetCharacterGoods(ch, GOOD_GRAPES, 20);
		SetCharacterGoods(ch, GOOD_KNIPPELS, 20);
		SetCharacterGoods(ch, GOOD_BOMBS, 0);
		SetCharacterGoods(ch, GOOD_FOOD, 110);
		SetCharacterGoods(ch, GOOD_POWDER, 60);
		SetCharacterGoods(ch, GOOD_WEAPON, 20);
		SetCharacterGoods(ch, GOOD_MEDICAMENT, 60);
		SetCharacterGoods(ch, GOOD_RUM, 90);
		if(startHeroType == 4) SetCharacterGoods(ch, GOOD_SANDAL, 50);
		if(startHeroType == 4) ch.Skill.Sailing = 45;
		else ch.Skill.Sailing = 1;
		bWorldAlivePause = false;
		// коцаем корабль
		// ch.ship.SP = sti(ch.ship.SP) - 10; <-- этот код не имеет смысла
		//ch.ship.HP = sti(ch.ship.HP) - makeint(sti(ch.ship.HP)/2);
		//Tutorial - НАЧАЛО ИГРЫ
	    ch.quest.Tut_start.win_condition.l1          = "location";
	    ch.quest.Tut_start.win_condition.l1.location = "Ship_deck_Low";
	    ch.quest.Tut_start.function                  = "Tut_StartGame";
		ch.questTemp.StatusCity = ch.HeroParam.ToCityId;
		ch.systeminfo.tutorial.firstfight1_SandBox = true;
		ch.systeminfo.tutorial.firstSea_SandBox = true;
		ch.systeminfo.tutorial.firstSeaBattle_SandBox = true;
		ch.systeminfo.tutorial.navigator = true;
		ch.quest.Tut_WorldMap.win_condition.l1          = "MapEnter";
	    ch.quest.Tut_WorldMap.function                  = "Tutorial_WorldMap";
		SetFunctionTimerCondition("Tutorial_Salary", 0, 0, 28, true);
		ch.quest.Tutorial_Dubloons.win_condition.l1 = "item";
		ch.quest.Tutorial_Dubloons.win_condition.l1.item = "gold_dublon";
		ch.quest.Tutorial_Dubloons.function = "Tutorial_Dubloons";
		ch.quest.Tutorial_Mushket.win_condition.l1 = "ItemGroup";
		ch.quest.Tutorial_Mushket.win_condition.l1.group = MUSKET_ITEM_TYPE;
		ch.quest.Tutorial_Mushket.function = "Tutorial_Mushket";
		ch.quest.Tutorial_Box.win_condition.l1 = "My_Cabine";
		ch.quest.Tutorial_Box.function = "Tutorial_Box";
		ch.systeminfo.tutorial.health = true;
		ch.systeminfo.tutorial.Amulet = true;
		ch.systeminfo.tutorial.Perk = true;
		ch.systeminfo.tutorial.Fighter = true;
		if(startHeroType == 4)
		{
			SetItemInLocation("pirate_cutlass", "Pirates_townhall_upstairs", "item1");
			locations[FindLocation("Pirates_townhall_upstairs")].locators_radius.item.item1 = 1.0;
			DeleteAttribute(&locations[FindLocation("Pirates_town")],"reload.l3.disable"); //открыть резиденцию на ИТ
			DeleteAttribute(&locations[FindLocation("SantaCatalina_houseSp3_bedroom")],"box1.QuestClosed"); //открыть резиденцию на ИТ
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.obereg_7 = 1;
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.obereg_9 = 1;
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.obereg_10 = 1;
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.obereg_11 = 1;
			ch.GenQuestBox.SantaCatalina_houseSp3_bedroom.box1.items.amulet_5 = 1;
		}
		
		SetCurrentTime(11,30); // вытавим время и отменим дождь
		WeatherParams.Rain 			= false;
		WeatherParams.Rain.ThisDay 	= false;
	}	
	// Warship Для разных квестов
	// Важно: функция MaryCelesteInit() должна быть тут, а не в initStartState2Character()
	// т.к. в ней идёт выборка колоний, которые в функции initStartState2Character() еще не инитились
	OtherQuestCharactersInit(); // Инициализация прочих квестов
	MaryCelesteInit(); // Warship 07.07.09 Пасхалка "Мэри Селест"
	ChickenGod_PreInit();
}

void initMainCharacterItem()
{
    ref ch = GetMainCharacter();
	String itemID;
	
	ch.systeminfo.NoNotifications = true;
	switch (ch.HeroParam.HeroType)
	{
		case "HeroType_1":
			itemID = GetGeneratedItem("blade_09");	// карцолетта
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
			TakenItems(ch, "jewelry3", 1);
			TakenItems(ch, "jewelry42", 1);
			TakenItems(ch, "jewelry43", 2);
			TakenItems(ch, "jewelry46", 3);
         	ch.money = 500;		
		break;
		
		case "HeroType_2":
			itemID = GetGeneratedItem("blade_12");	// полусабля
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
			TakenItems(ch, "jewelry3", 2);
			TakenItems(ch, "jewelry42", 2);
			TakenItems(ch, "jewelry43", 4);
			TakenItems(ch, "jewelry46", 6);
         	ch.money = 500;
		break;
		
		case "HeroType_3":
			itemID = GetGeneratedItem("blade_14");	// валлонская шпага
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
			TakenItems(ch, "jewelry3", 1);
			TakenItems(ch, "jewelry42", 1);
			TakenItems(ch, "jewelry43", 2);
			TakenItems(ch, "jewelry46", 3);
         	ch.money = 500;				
		break;
		
		case "HeroType_4":
			itemID = GetGeneratedItem("blade_08");	// бильбо
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);			
			AddItems(ch, "pistol3", 1);
			EquipCharacterbyItem(ch, "pistol3");			
			AddItems(ch, "grapeshot", 5);
			AddItems(ch, "gunpowder", 5);
			LAi_SetCharacterUseBullet(ch, GUN_ITEM_TYPE, "grapeshot");
			TakenItems(ch, "jewelry3", 1);
			TakenItems(ch, "jewelry42", 1);
			TakenItems(ch, "jewelry43", 2);
			TakenItems(ch, "jewelry46", 3);
         	ch.money = 500;
		break;
	}
	if(GetDLCenabled(DLC_APPID_1))
	{
		AddItems(ch, "knife_03", 1);
	}
	DeleteAttribute(ch,"systeminfo.NoNotifications");
}

void initMainFreePlayCharacterItem()
{
    ref ch = GetMainCharacter();
	String itemID;
	ch.systeminfo.NoNotifications = true;
	switch (ch.HeroParam.HeroType)
	{
		case "HeroType_1":
			itemID = GetGeneratedItem("blade_09");	// карцолетта
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
         	ch.money = 500;		
		break;
		
		case "HeroType_2":
			itemID = GetGeneratedItem("blade_12");	// полусабля
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
         	ch.money = 500;
		break;
		
		case "HeroType_3":
			itemID = GetGeneratedItem("blade_14");	// валлонская шпага
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);
         	ch.money = 500;				
		break;
		
		case "HeroType_4":
			itemID = GetGeneratedItem("blade_08");	// бильбо
            GiveItem2Character(ch, itemID);
            EquipCharacterbyItem(ch, itemID);			
			AddItems(ch, "pistol3", 1);
			EquipCharacterbyItem(ch, "pistol3");
			//AddItems(ch, "mushket1", 1);			
			AddItems(ch, "grapeshot", 5);
			AddItems(ch, "bullet", 5);
			AddItems(ch, "gunpowder", 10);
			LAi_SetCharacterUseBullet(ch, GUN_ITEM_TYPE, "grapeshot");
         	ch.money = 500;				
		break;
	}
	aref item;
	Items_FindItem("map_full", &item);
	FillMapForTreasure(item);
	GiveItem2Character(ch, "map_full");
	GiveItem2Character(ch, "map_normal");
	AddItems(ch, "potion1", 5);
	AddItems(ch, "potion2", 1);
	AddItems(ch, "potion3", 1);
	//AddItems(ch, "obereg_8", 1);
	//AddItems(ch, "amulet_7", 1);
	//AddItems(ch, "obereg_4", 1);
	//AddItems(ch, "talisman2", 1);
	//AddItems(ch, "gold_dublon", 20);
	//AddItems(ch, "alchemy_tool", 1);
	AddItems(ch, "Tailor_Tool", 1);
	AddItems(ch, "Mechanic_Tool", 1);
	AddItems(ch, "spyglass1", 1);
	
	SetCharacterPerk(ch, "FlagHol");
	//GiveNationLicence(HOLLAND, 180);
	ch.alchemy.known = 1;
	AddQuestRecordInfo("Recipe", "cartridge");
	SetAlchemyRecipeKnown("cartridge");
    AddQuestRecordInfo("Recipe", "clock2");
	SetAlchemyRecipeKnown("clock2");
	if(GetDLCenabled(DLC_APPID_1))
	{
		AddItems(ch, "knife_03", 1);
	}
	DeleteAttribute(ch,"systeminfo.NoNotifications");
}

int GetNewMainCharacterFace()
{
    return sti(GetNewMainCharacterParam("heroFace_" + startHeroType));
}

string GetNewMainCharacterName()
{
    return GetHeroName(startHeroType);
}

string GetMainCharacterNameGen()  // ==> eddy. родительный падеж полного имени ГГ
{
    return GetHeroNameGen(startHeroType);
}

string GetMainCharacterNameDat()  // ==> eddy. дательный падеж полного имени ГГ
{
    return GetHeroNameDat(startHeroType);
}

string GetHeroName(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroName_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastname_" + _n);

    return totalInfo;
}

string GetHeroNameGen(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameGen_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameGen_" + _n);

    return totalInfo;
}

string GetHeroNameDat(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameDat_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameDat_" + _n);

    return totalInfo;
}

int GetNewMainCharacterNation(int _startHeroType)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, "heroNation_" + _startHeroType);
    LanguageCloseFile(idLngFile);

    switch(totalInfo)
	{
		case "Англия":
            return ENGLAND;
		break;
		case "Франция":
            return FRANCE;
		break;
		case "Испания":
            return SPAIN;
		break;
		case "Голландия":
			return HOLLAND;
		break;
		case "Береговое братство":
			return PIRATE;
		break;

		case "ENGLAND":
            return ENGLAND;
		break;
		case "FRANCE":
            return FRANCE;
		break;
		case "SPAIN":
            return SPAIN;
		break;
		case "HOLLAND":
			return HOLLAND;
		break;
		case "PIRATE":
			return PIRATE;
		break;
	}
	return PIRATE;
}

string GetNewMainCharacterParam(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

// вернуть базовую нацию ГГ или патент
int GetBaseHeroNation()
{
	if (isMainCharacterPatented())
	{
	    return sti(Items[sti(pchar.EquipedPatentId)].Nation);
	}
	return sti(pchar.BaseNation);
}

// belamour максимальный шанс нанести критический удар по противнику
int GetAttackCritical(ref chr)
{
	int chance 	= 0;
	
	if(IsEquipCharacterByArtefact(chr, "indian_3")) chance += 15;
	if(IsEquipCharacterByArtefact(chr, "amulet_4")) chance -= 10;
	if(CheckCharacterPerk(chr, "HT1")) chance += 10;
	if(IsCharacterPerkOn(chr, "CriticalHit")) chance += 5;
	if(IsCharacterPerkOn(chr, "SwordplayProfessional")) chance += 10;
	if(GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "cirass9") chance += 5;
	// dlc для Патронов
	if(GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE) == "khopesh1") chance += 1;
	if(GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE) == "khopesh2") chance += 3;
	if(GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE) == "khopesh3") chance += 2;
	
	if(chance > 0) chance += GetCharacterSPECIAL(chr, SPECIAL_L);
	
	return 100*chance/100;
}

// belamour максимальный шанс критического выстрела
int GetShotCritical(ref chr)
{
	int chance = 0;
	
	if(GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE) == "pistol5") chance += 15;
	if(GetCharacterEquipByGroup(chr, MUSKET_ITEM_TYPE) == "mushket5") chance += 10;
	if(GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE) == "pistol9") chance += 3;
	if(GetCharacterEquipByGroup(chr, MUSKET_ITEM_TYPE) == "mushket3") chance += 3;
	if(GetCharacterEquipByGroup(chr, MUSKET_ITEM_TYPE) == "mushket7") chance += 6;
	if(GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE) == "pistol11") chance += 6;
	if(GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE) == "pistol14") chance += 9;
	if(GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE) == "cirass10")) chance += 5;
	if(IsEquipCharacterByArtefact(chr, "indian_1")) chance += 3;
	if(IsEquipCharacterByArtefact(chr, "indian_2")) chance += 3;
	if(IsEquipCharacterByArtefact(chr, "totem_12")) chance += 3;
	if(chance > 0)
	{
		int si = sti(GetCharacterSPECIAL(chr, SPECIAL_L)+GetCharacterSPECIAL(chr, SPECIAL_P))/2;
		if(si > 10) si = 10;
		chance += si;
	}
	return chance;
}

// защита от хо
int GetDefenceBlade(ref chr)
{
	float dmg = 1.0;
	float kDmg = 1.0;
	if(IsCharacterPerkOn(chr, "BasicDefense")) kDmg = 0.9;
	if(IsCharacterPerkOn(chr, "AdvancedDefense")) kDmg = 0.8;
	if(IsCharacterPerkOn(chr, "SwordplayProfessional")) kDmg = 0.7;
	dmg *= kDmg;
	if(CheckAttribute(chr, "cirassId"))
	{
		dmg *= 1.0 - stf(Items[sti(chr.cirassId)].B_CirassLevel);
		//if(CheckCharacterPerk(chr, "HT3") && GetCharacterSuitType(chr) == 2)
		if(CheckCharacterPerk(chr, "Dragoon") && GetCharacterSuitType(chr) == 2)
		{
			dmg *= 0.85;
		}
		if(CheckCharacterPerk(chr, "HT1") && GetCharacterSuitType(chr) == 1 )
		{
			dmg *= 0.80;	
		} 
	}
	if(IsCharacterEquippedArtefact(chr, "kaleuche_amulet3"))
	{
		dmg = dmg * 0.75;
	}
	if(CheckAttribute(chr,"ReducedDamage")) dmg = dmg * makefloat(chr.ReducedDamage);
	dmg *= fLiberMisBonus(chr);
	
	return 100 - sti(dmg*100.0);
}

// защита от огнестрела
int GetDefenceGun(ref chr)
{
	float dmg = 1.0;
	if(IsEquipCharacterByArtefact(chr,  "indian_2")) dmg *= 1.1;
	if(IsEquipCharacterByArtefact(chr,  "amulet_1")) dmg *= 0.85;
	if(CheckAttribute(chr, "cirassId"))
	{
		dmg *= 1.0 - stf(Items[sti(chr.cirassId)].G_CirassLevel);
		//if(CheckCharacterPerk(chr, "HT3") && GetCharacterSuitType(chr) == 2)
		if(CheckCharacterPerk(chr, "Dragoon") && GetCharacterSuitType(chr) == 2)
		{
			dmg *= 0.85;
		}
		if(CheckCharacterPerk(chr, "HT1") && GetCharacterSuitType(chr) == 1 )
		{
			dmg *= 0.80;	
		}
	}
	if(CheckAttribute(chr,"ReducedDamage")) dmg = dmg * makefloat(chr.ReducedDamage);
	dmg *= fLiberMisBonus(chr);
	
	return 100 - sti(dmg*100.0);
}

// защита от критиклов
int GetDefenceCritical(ref chr)
{
	int chance 	= 100;
	if(IsEquipCharacterByArtefact(chr, "indian_4")) chance += 10;
	if(IsEquipCharacterByArtefact(chr,  "amulet_3"))
	{
		if(ShipBonus2Artefact(chr, SHIP_GALEON_SM)) chance  -= 20;
		else chance  -= 15;
	}
	if(CheckAttribute(chr, "cirassId"))
	{
		chance = sti(chance * stf(Items[sti(chr.cirassId)].critical));
	}
	return 100 - chance;
}
