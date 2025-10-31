#include "encounters\encounters.h"
#include "encounters\encounters_map.c"

//#include "scripts\utils.c"

#define MAX_MAP_ENCOUNTERS		128
object MapEncounters[MAX_MAP_ENCOUNTERS];

int WorldMapRandomEncQty = 12; // Без квестовых и специальных
int	EncWeightCur[12];
int	EncWeightBase[12];

extern void InitEncounters();
extern void InitEncountersBaseWeight();

void EncountersInit()
{
	if(LoadSegment("Encounters\Encounters_init.c"))
	{
		InitEncounters();
		InitEncountersBaseWeight();
		UnloadSegment("Encounters\Encounters_init.c");
	}

	ReleaseMapEncounters();
}

int FindEncounter(int type, int nat)
{
	int iTypes[2]; 
	int i;
	SetArraySize(&iTypes, MAX_ENCOUNTER_TYPES * 10);
	for(i = 0; i < MAX_ENCOUNTER_TYPES*10; i++) iTypes[i] = -1;
	int iNumTypes = 0;

	ref rCharacter = GetMainCharacter();
	int iCharacterRank = sti(rCharacter.rank);

	int iChance = rand(250);

	for (i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		if(sti(EncountersTypes[i].Type) == type)
		{
			if(sti(EncountersTypes[i].Skip) || !Encounter_CanNation(i, nat)) { continue; }
			// check chance
			if (iChance > sti(EncountersTypes[i].Chance)) { continue; }

			iTypes[iNumTypes] = i;
			iNumTypes++;
		}
	}
	if(iNumTypes == 0) 
	{
		return -1;
	}
	int findnum = rand(iNumTypes-1);
	while(findnum >=0 && iTypes[findnum] == -1) findnum--;
	return iTypes[findnum];
}

int FindWarEncounter()
{
	int iTypes[100];
	int iNumTypes = 0;

	ref rCharacter = GetMainCharacter();
	int iCharacterRank = sti(rCharacter.rank);

	int iChance = rand(250);// boal 13.03.2004

	for (int i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		if (sti(EncountersTypes[i].Type) == ENCOUNTER_WAR)
		{
			if (sti(EncountersTypes[i].Skip)) { continue; }
			// check chance
			if (iChance > sti(EncountersTypes[i].Chance)) { continue; }

            iTypes[iNumTypes] = i;
            iNumTypes++;
		}
	}
	if (iNumTypes == 0) 
	{
		//Trace("FindWarEncounter: not find any war encounters!");
		return -1;
	}
	return iTypes[rand(iNumTypes-1)];
}

int FindMerchantEncounter()
{
	int iTypes[100];
	int iNumTypes = 0;

	ref rCharacter = GetMainCharacter();
	int iCharacterRank = sti(rCharacter.rank);

	int iChance = rand(250);// boal 13.03.2004

	for (int i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		if (sti(EncountersTypes[i].Type) == ENCOUNTER_TRADE)
		{
            if (sti(EncountersTypes[i].Skip)) { continue; } // fix
			// check chance
			if (iChance > sti(EncountersTypes[i].Chance)) continue;

            iTypes[iNumTypes] = i;
            iNumTypes++;
		}
	}
	if (iNumTypes == 0)
	{
		//Trace("FindMerchantEncounter: not find any merchant!");
		return -1;
	}
	return iTypes[rand(iNumTypes - 1)];
}

int FindSpecialEncounter()
{
	int iTypes[100];
	int iNumTypes = 0;
	
	ref rCharacter = GetMainCharacter();
	int iCharacterRank = sti(rCharacter.rank);
	
	int iChance = rand(200);// boal 13.03.2004
	
	for (int i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		if (sti(EncountersTypes[i].Type) == ENCOUNTER_SPECIAL)	
		{
            if (sti(EncountersTypes[i].Skip)) { continue; } // fix
			// check chance
			if (iChance > sti(EncountersTypes[i].Chance)) continue;

            iTypes[iNumTypes] = i;
            iNumTypes++;	
		}
	}
	if (iNumTypes == 0) 
	{
		return -1;
	}
	return iTypes[rand(iNumTypes-1)];
}

bool Encounter_CanNation(int iEncounter, int iNation)
{
	string sNation = "Nation.Exclude." + Nations[iNation].Name;
	if (!CheckAttribute(&EncountersTypes[iEncounter], sNation)) return true;
	return !sti(EncountersTypes[iEncounter].(sNation));
}

bool Encounter_GetClassesFromRank(int iEncounter, int iRank, ref rMClassMin, ref rMClassMax, ref rWClassMin, ref rWClassMax)
{
	ref rEnc = &EncountersTypes[iEncounter];

	rMClassMin = 0; rMClassMax = 0; 
	rWClassMin = 0; rWClassMax = 0;

	string sRank = "Rank." + iRank;
	
	trace("sRank : " + sRank + " iEncounter : " + iEncounter);
	
	if (!CheckAttribute(rEnc, sRank))
	{
		// find nearest rank 
		if (CheckAttribute(rEnc, "Rank"))
		{
			int iLastRank = -1;
			int iBestRank = 1000;

			aref aRanks; makearef(aRanks, rEnc.Rank);
			int iNumRanks = GetAttributesNum(aRanks);
			for (int i=0; i<iNumRanks; i++)
			{
				aref aRank = GetAttributeN(aRanks, i);
				string sName = GetAttributeName(aRank);
				int iCurRank = sti(sName);
				if (abs(iRank - iCurRank) < iBestRank)
				{
					iBestRank = abs(iRank - iCurRank);
					iLastRank = iCurRank;
				}
			}
			if (iLastRank == -1) return false;
			sRank = "Rank." + iLastRank;
		}
		else
		{
			return false;
		}
	}

	rMClassMin = rEnc.(sRank).1;
	rMClassMax = rEnc.(sRank).0;

	rWClassMin = rEnc.(sRank).3;
	rWClassMax = rEnc.(sRank).2;

	trace("rMClassMin " + rMClassMin + " rMClassMax " + rMClassMax + " rWClassMin " + rWClassMin + " rWClassMax " + rWClassMax);

	return true;
}

//belamour найти подтип энкаунтера от айди
int FindRealEncounterTypeFromId(string _id)
{
    if(_id == "") return -1;
    if (!CheckAttribute(&worldMap, "encounters." + _id)) return -1;
    aref rEnc;
    makearef(rEnc, worldMap.encounters.(_id).encdata);
    return sti(rEnc.RealEncounterType);
}

void Enc_ExcludeNation(ref rEnc, int iNation)
{
	string sNation = Nations[iNation].Name;
	rEnc.Nation.Exclude.(sNation) = true;
}

// Биты каждой ячейки справа налево:
// 4 bit мин кол-во, 4 bit макc кол-во, 4 bit мин класс, 4 bit макс класс
int ENC_MERCHANT_SLOT[12]   = {0,0,0,0,0,0,0,0,0,0,0,0};
int ENC_WAR_SLOT[12]        = {0,0,0,0,0,0,0,0,0,0,0,0};
int ENC_RAIDER_SLOT[12]     = {0,0,0,0,0,0,0,0,0,0,0,0};
int ENC_UNIVERSAL_SLOT[12]  = {0,0,0,0,0,0,0,0,0,0,0,0};
// Биты справа налево:
// 4 bit маска участников рандома специализаций (cell >> SHIP_SPEC) & 1
// Через (cell & 15 != 0) можно узнать есть ли рандом вообще
// 4 bit кол-во участников рандома, offset = rand(((cell >> 4) & 15) - 1)
// До 8 bit последовательность до 4 участников 2-битных масок (SHIP_SPEC от 0 до 3)
// Через (cell >> (8 + offset * 2)) & 3 получаем двухбитную маску (кого-то из SHIP_SPEC)
int ENC_RANDOM_PARAMS[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

// Установить параметры для слота специализации
void SetEncSlot_Params(int iEncType, int iSpec, int qMin, int qMax, int cMin, int cMax)
{
    int BitMask = qMin + shl(qMax, 4) + shl(cMin, 8) + shl(cMax, 12);
    switch (iSpec)
    {
        case SHIP_SPEC_MERCHANT:  ENC_MERCHANT_SLOT[iEncType]  = BitMask; break;
        case SHIP_SPEC_WAR:       ENC_WAR_SLOT[iEncType]       = BitMask; break;
        case SHIP_SPEC_RAIDER:    ENC_RAIDER_SLOT[iEncType]    = BitMask; break;
        case SHIP_SPEC_UNIVERSAL: ENC_UNIVERSAL_SLOT[iEncType] = BitMask; break;
    }
}

// Получить количество кораблей
int GetEncSlotQty(int BitMask)
{
    int min = and(BitMask, 15);
    int max = and(shr(BitMask, 4), 15);
    return min + rand(max - min);
}

// Установить параметры для рандома между некоторыми специализациями
void SetEncSlot_SpecRandom(int iEncType, bool bM, bool bW, bool bR, bool bU)
{
    /*bM - SHIP_SPEC_MERCHANT  0
      bW - SHIP_SPEC_WAR       1
      bR - SHIP_SPEC_RAIDER    2
      bU - SHIP_SPEC_UNIVERSAL 3*/

    int qty = bM + bW + bR + bU;
    int BitMask = bM + shl(bW, 1) + shl(bR, 2) + shl(bU, 3) + shl(qty, 4);
    for (int i = 0; i < qty; i++) {
        int offset = 8 + (i*2);
        if (bM) {BitMask += shl(SHIP_SPEC_MERCHANT, offset); bM = 0;}
        else if (bW) {BitMask += shl(SHIP_SPEC_WAR, offset); bW = 0;}
        else if (bR) {BitMask += shl(SHIP_SPEC_RAIDER, offset); bR = 0;}
        else if (bU) {BitMask += shl(SHIP_SPEC_UNIVERSAL, offset); bU = 0;}
    }

    ENC_RANDOM_PARAMS[iEncType] = BitMask;
}

// Проверить, участвует ли конкретная специализация в рандоме
bool CheckEncRand_Spec(int BitMask, int iSpec)
{
    return and(shr(BitMask, iSpec), 1);
}

// Выбрать специализацию из участвующих в рандоме
int GetEncRandSpec(int BitMask)
{
    int qty = and(shr(BitMask, 4), 15);
    int offset = rand(qty-1);
    return and(shr(BitMask, 8 + offset*2), 3);
}

bool EncProgress[60];
#event_handler("PlayerLevelUp", "Encounter_Progress");
void Encounter_Progress()
{
    ref rEnc;
    int Rank = sti(PChar.Rank);

    if(Rank >= 3 && !EncProgress[3])
    {
        EncProgress[3] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_RAIDER,    0, 1, 4, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_MERCHANT,  1, 2, 4, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_UNIVERSAL, 1, 1, 4, 5);
        ENC_RANDOM_PARAMS[ENCOUNTER_TYPE_MERCHANT_MEDIUM] = 0; // off random

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_RAIDER,    0, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_MERCHANT,  1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_UNIVERSAL, 1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_WAR,       0, 1, 3, 4);
    }

    if(Rank >= 4 && !EncProgress[4])
    {
        EncProgress[4] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_MERCHANT,  1, 1, 5, 6);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_UNIVERSAL, 0, 1, 5, 6);
        ENC_RANDOM_PARAMS[ENCOUNTER_TYPE_MERCHANT_SMALL] = 0; // off random

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_RAIDER,    0, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_MERCHANT,  1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_WAR,       1, 1, 3, 5);

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_RAIDER,    0, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_MERCHANT,  1, 1, 2, 3);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_UNIVERSAL, 0, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_WAR,       1, 2, 2, 3);

        SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_SMALL, SHIP_SPEC_RAIDER,    1, 1, 5, 6);
    }

    if(Rank >= 5 && !EncProgress[5])
    {
        EncProgress[5] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_MERCHANT,  1, 1, 5, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_WAR,       1, 1, 3, 4);
    }

    if(Rank >= 8 && !EncProgress[8])
    {
        EncProgress[8] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_RAIDER, 0, 1, 5, 6);

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_RAIDER,    0, 1, 3, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_MERCHANT,  1, 2, 4, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_UNIVERSAL, 1, 1, 3, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_WAR,       0, 1, 3, 5);

        iGPThreatMax = THREAT_LVL_2;
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_RAIDER,    1, 1, 5, 6);
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_UNIVERSAL, 0, 1, 5, 6);
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_WAR,       1, 1, 5, 6);
        SetEncSlot_SpecRandom(ENCOUNTER_TYPE_PIRATE, 0, 1, 1, 0);
        SetFunctionMapEnterCondition("PirateNotificationUPD", false);
    }

    if(Rank >= 11 && !EncProgress[11])
    {
        EncProgress[11] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_RAIDER,    1, 2, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_MERCHANT,  1, 2, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_UNIVERSAL, 1, 2, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_WAR,       0, 2, 2, 4);

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_RAIDER,    0, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_MERCHANT,  1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_UNIVERSAL, 1, 1, 4, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_WAR,       1, 1, 3, 5);

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_RAIDER,    1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_MERCHANT,  2, 2, 2, 3);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_UNIVERSAL, 1, 1, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_WAR,       1, 2, 2, 3);

        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_MERCHANT,  1, 1, 5, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_UNIVERSAL, 1, 1, 4, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_WAR,       1, 1, 3, 4);

        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_RAIDER,    1, 1, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_MERCHANT,  1, 2, 3, 3);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_UNIVERSAL, 1, 2, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_WAR,       2, 2, 2, 3);
    }

    if(Rank >= 12 && !EncProgress[12])
    {
        EncProgress[12] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_RAIDER,    1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_MERCHANT,  1, 1, 2, 2);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_UNIVERSAL, 0, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_WAR,       1, 1, 3, 4);

        SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_SMALL, SHIP_SPEC_RAIDER,    2, 2, 5, 6);

        SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_MEDIUM, SHIP_SPEC_RAIDER,    1, 1, 3, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_MEDIUM, SHIP_SPEC_UNIVERSAL, 1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_MEDIUM, SHIP_SPEC_WAR,       1, 1, 4, 5);
    }

    if(Rank >= 13 && !EncProgress[13])
    {
        EncProgress[13] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_RAIDER,    0, 1, 4, 6);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_MERCHANT,  1, 2, 4, 6);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_UNIVERSAL, 1, 1, 5, 6);
    }

    if(Rank >= 14 && !EncProgress[14])
    {
        EncProgress[14] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_RAIDER,    1, 1, 3, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_MERCHANT,  1, 2, 3, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_UNIVERSAL, 1, 2, 3, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_WAR,       1, 1, 3, 5);

        iGPThreatMax = THREAT_LVL_3;
        EncountersTypes[ENCOUNTER_TYPE_PIRATE].worldMapShip = "bark";
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_RAIDER,    1, 2, 4, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_WAR,       1, 1, 4, 5);
        ENC_UNIVERSAL_SLOT[ENCOUNTER_TYPE_PIRATE] = 0;
        ENC_RANDOM_PARAMS[ENCOUNTER_TYPE_PIRATE] = 0; // off random
        SetFunctionMapEnterCondition("PirateNotificationUPD", false);
    }

    if(Rank >= 18 && !EncProgress[18])
    {
        EncProgress[18] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_RAIDER,    1, 1, 4, 6);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_MERCHANT,  2, 2, 4, 6);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_UNIVERSAL, 1, 1, 4, 6);
    }

    if(Rank >= 19 && !EncProgress[19])
    {
        EncProgress[19] = true;

        iGPThreatMax = THREAT_LVL_4;
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_RAIDER,    1, 2, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_WAR,       0, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_UNIVERSAL, 1, 1, 3, 4);
        SetFunctionMapEnterCondition("PirateNotificationUPD", false);
    }

    if(Rank >= 20 && !EncProgress[20])
    {
        EncProgress[20] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_RAIDER,    1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_MERCHANT,  1, 2, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_UNIVERSAL, 1, 2, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_WAR,       1, 1, 3, 4);

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_RAIDER,    1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_MERCHANT,  1, 1, 2, 2);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_UNIVERSAL, 0, 2, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_WAR,       2, 2, 2, 2);

        SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_SMALL, SHIP_SPEC_RAIDER,    2, 3, 4, 5);

        SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_MEDIUM, SHIP_SPEC_RAIDER,    2, 2, 2, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_MEDIUM, SHIP_SPEC_UNIVERSAL, 1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_MEDIUM, SHIP_SPEC_WAR,       1, 1, 4, 5);
    }

    if(Rank >= 21 && !EncProgress[21])
    {
        EncProgress[21] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_RAIDER,    0, 1, 3, 3);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_MERCHANT,  1, 1, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_UNIVERSAL, 1, 1, 3, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_WAR,       1, 1, 3, 5);

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_RAIDER,    1, 2, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_MERCHANT,  2, 2, 2, 3);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_UNIVERSAL, 1, 2, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_WAR,       2, 2, 2, 3);

        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_MERCHANT,  2, 2, 5, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_UNIVERSAL, 1, 1, 4, 5);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_WAR,       2, 2, 3, 4);

        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_RAIDER,    1, 1, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_MERCHANT,  2, 2, 3, 3);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_UNIVERSAL, 1, 2, 3, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_WAR,       2, 2, 1, 3);
    }

    if(Rank >= 22 && !EncProgress[22])
    {
        EncProgress[22] = true;

        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_RAIDER,    1, 2, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_MERCHANT,  1, 2, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_UNIVERSAL, 2, 2, 2, 3);
        SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_WAR,       1, 2, 2, 4);
    }

    if(Rank >= 24 && !EncProgress[24])
    {
        EncProgress[24] = true;

        iGPThreatMax = THREAT_LVL_5;
        EncountersTypes[ENCOUNTER_TYPE_PIRATE].worldMapShip = "frigate";
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_RAIDER,    1, 2, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_WAR,       1, 1, 2, 4);
        SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_UNIVERSAL, 1, 2, 2, 4);
        SetFunctionMapEnterCondition("PirateNotificationUPD", false);
    }
}

void PirateNotificationUPD(string qName){Notification(StringFromKey("QuestsUtilite_276"), "pirhunter");}
void PiratesIncreaseNotif(string qName){ Notification(StringFromKey("QuestsUtilite_330"), "pirhunter");}
void PiratesDecreaseNotif(string qName){ Notification(StringFromKey("QuestsUtilite_329"), "pirhunter");}
