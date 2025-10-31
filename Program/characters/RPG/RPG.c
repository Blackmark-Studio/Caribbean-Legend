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
#include "characters\RPG\energy.c"
#include "characters\RPG\hp.c"
#include "characters\RPG\personality.c"
#include "characters\RPG\perks\perks.c"

int GetCharacterMaxOfficersQty(ref _refCharacter)
{
    return GetCharacterSPECIAL(_refCharacter, SPECIAL_C)*2;
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

// boal 20.03.2004 -->
int GetShipClassNavySkill(int shipClass)
{
    int needSkill = 0;

    switch (shipClass)
    {
            case 1 : needSkill = 90; break; //переработал пороги с учетом новой скорости прогрессии и будущего отказа от бонусов к умениям, а также с учетом механики убегания - теперь запас превышения класса более равномерный
            case 2 : needSkill = 70; break;
            case 3 : needSkill = 55; break;			
            case 4 : needSkill = 40; break;			
            case 5 : needSkill = 20; break;
            case 6 : needSkill = 1;  break;
            case 7 : needSkill = 1;  break; // технический класс для всяких контрабандистов и баркасов - у них тоже найдется применение
    }
    return needSkill;
}
// boal 20.03.2004 <--
void DelBakSkillAttr(ref _refCharacter) // boal оптимизация скилов
{
    DeleteAttribute(_refCharacter, "BakSkill");
    DeleteAttribute(_refCharacter, "BakSkillCount");
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