#include "characters\RPG\cash_tables\cash_tables.c"
#include "characters\RPG\health.c"
#include "characters\RPG\init.c"
#include "characters\RPG\skills.c"
#include "characters\RPG\special.c"
#include "characters\RPG\statistic.c"
#include "characters\RPG\utility.c"
#include "characters\RPG\weight.c"
#include "characters\RPG\leveling.c"
#include "characters\RPG\reputation_loyality_nobility.c"
#include "characters\RPG\status_effects.c"
#include "characters\RPG\jobs.c"
#include "characters\RPG\fightparams.c"
#include "characters\RPG\perks\perks.c"

#define MAX_ACHIEVMENTS		73
#define MAIN_HP_BONUS		30.0
#define MAIN_ENERGY_BONUS	15.0

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


int GetCharacterBaseHPValue(ref _refCharacter)
{
	int ret = makeint(30.0 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_S)*GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E)*0.5);
	if(IsMainCharacter(_refCharacter))	// бонус хп у ГГ
	{
		_refCharacter.chr_ai.main_hp_bonus = MAIN_HP_BONUS;
		ret += makeint(MAIN_HP_BONUS);
	}
	return ret;
}

float GetCharacterMaxEnergyValue(ref _refCharacter)
{
	if (!CheckAttribute(_refCharacter, "equip.blade")) return 100.0; // невооруженные пофигу

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
		ret *= 1.12; // JOKERTODO переписать на суммирование модификаторов и добавить восстановление
	}
	if(CheckAttribute(_refCharacter, "cheats.energyplus"))
	{
		ret += stf(_refCharacter.cheats.energyplus);
	}
	if(CheckAttribute(_refCharacter, "bonusEnergy"))
	{
		ret = ret + stf(_refCharacter.bonusEnergy);
	}
	if(IsMainCharacter(_refCharacter))	// бонус энергии у ГГ
	{
		_refCharacter.chr_ai.main_energy_bonus = MAIN_ENERGY_BONUS;
		ret += makeint(MAIN_ENERGY_BONUS);
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
	if(IsMainCharacter(_refCharacter))	// бонус энергии у ГГ
	{
		_refCharacter.chr_ai.main_energy_bonus = MAIN_ENERGY_BONUS;
		ret += makeint(MAIN_ENERGY_BONUS);
	}
	return ret;
}

void AddBonusEnergyToCharacter(ref _refCharacter, int iEnrg)
{
	if(CheckAttribute(_refCharacter, "bonusEnergy"))
	{
		_refCharacter.bonusEnergy = sti(_refCharacter.bonusEnergy) + iEnrg;
	}
	else
	{
		_refCharacter.bonusEnergy = iEnrg;
	}
	SetEnergyToCharacter(_refCharacter);
}

void RemoveBonusEnergyFromCharacter(ref _refCharacter, int howMuch)
{
	_refCharacter.bonusEnergy = sti(_refCharacter.bonusEnergy) - howMuch;
	if (sti(_refCharacter.bonusEnergy) <= 0)
	{
		DeleteAttribute(_refCharacter, "bonusEnergy");
	}
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

int GetCharacterMaxOfficersQty(ref _refCharacter)
{
    return GetCharacterSPECIAL(_refCharacter, SPECIAL_C)*2;
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

// вернуть базовую нацию ГГ или патент
int GetBaseHeroNation()
{
	if (isMainCharacterPatented())
	{
	    return sti(Items[sti(pchar.EquipedPatentId)].Nation);
	}
	return sti(pchar.BaseNation);
}

// Бонусный шанс обмануть корабли/укрепления
float GetBonusDeceptionChance(ref chr)
{
	if (!IsCharacterEquippedArtefact(chr, "indian_11")) return 1.0;
	return 1 + 0.05 * CountItemsWithDescriptor(chr, "Fancy");
}