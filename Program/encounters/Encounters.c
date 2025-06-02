#include "encounters\encounters.h"
#include "encounters\encounters_map.c"
#include "encounters\encounters_quest.c"

//#include "scripts\utils.c"

#define MAX_MAP_ENCOUNTERS		128
object MapEncounters[MAX_MAP_ENCOUNTERS];

extern void InitEncounters();

void EncountersInit()
{
	if(LoadSegment("Encounters\Encounters_init.c"))
	{
		InitEncounters();
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
    aref rEnc;
    makearef(rEnc, worldMap.encounters.(_id).encdata);
    return sti(rEnc.RealEncounterType);
}

void Enc_ExcludeNation(ref rEnc, int iNation)
{
	string sNation = Nations[iNation].Name;
	rEnc.Nation.Exclude.(sNation) = true;
}

// Энкаунтер, специализация, количество, классы
// Бонусы определяются отдельно циклом по рангам при логине
void Enc_AddShips(ref rEnc,
                  string ShipSpec, string Type,
                  int qMin, int qMax,
                  int cMin, int cMax)
{
    aref arEShips;
    makearef(arEShips, rEnc.Ships);
    string attr = GetAttributesNum(arEShips) + 1;

    arEShips.(attr).qMin = qMin;
    arEShips.(attr).qMax = qMax;
    arEShips.(attr).cMin = cMin;
    arEShips.(attr).cMax = cMax;
    arEShips.(attr).Type = Type;         // War or Merchant
    arEShips.(attr).ShipSpec = ShipSpec; // SHIP_SPEC_<>
}

void Enc_ConvertShips(ref rEnc, string ShipSpec, int cMin, int cMax)
{
    aref arEShips, aShip;
    makearef(arEShips, rEnc.Ships);
    int qty = GetAttributesNum(arEShips);
    for(int i = 0; i < qty; i++)
    {
        aShip = GetAttributeN(arEShips, i);
        if(aShip.ShipSpec == ShipSpec || ShipSpec == "All")
        {
            aShip.cMin = cMin;
            aShip.cMax = cMax;
        }
    }
}

void Enc_ConvertSpec(ref rEnc, string ShipSpec_from, string ShipSpec_to)
{
    aref arEShips, aShip;
    makearef(arEShips, rEnc.Ships);
    int qty = GetAttributesNum(arEShips);
    for(int i = 0; i < qty; i++)
    {
        aShip = GetAttributeN(arEShips, i);
        if(aShip.ShipSpec == ShipSpec_from)
            aShip.ShipSpec = ShipSpec_to;
    }
}

void Enc_DelShip(ref rEnc,
                 string ShipSpec, string Type,
                 int qMin, int qMax,
                 int cMin, int cMax)
{
    aref arEShips, aShip;
    makearef(arEShips, rEnc.Ships);
    int qty = GetAttributesNum(arEShips);
    for(int i = 0; i < qty; i++)
    {
        aShip = GetAttributeN(arEShips, i);
        if(aShip.ShipSpec == ShipSpec && aShip.Type == Type &&
           aShip.qMin     == qMin     && aShip.qMax == qMax &&
           aShip.cMin     == cMin     && aShip.cMin == cMax)
           {
                DeleteAttribute(arEShips, GetAttributeName(aShip));
                break;
           }
    }
}

// Сюда все апдейты, чтобы не переусложнять генерацию
// Через >= на случай читерских повышений
bool EncProgress[60];
#event_handler("PlayerLevelUp", "Encounter_Progress");
void Encounter_Progress()
{
    ref rEnc;
    int Rank = GetEventData();

    if(Rank >= 8 && !EncProgress[8])
    {
        EncProgress[8] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_SMALL];
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 5, 6);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_MEDIUM];
        Enc_AddShips(rEnc, SHIP_SPEC_WAR, "War", 1, 1, 3, 5);
        Enc_ConvertShips(rEnc, SHIP_SPEC_UNIVERSAL, 3, 4);
    }

    if(Rank >= 9 && !EncProgress[9])
    {
        EncProgress[9] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PIRATE];
        Enc_ConvertShips(rEnc, "All", 5, 5);
        Enc_AddShips(rEnc, SHIP_SPEC_WAR, "War", 1, 1, 5, 5);
		PChar.quest.Pirate_Notification.win_condition.l1 = "MapEnter";
	    PChar.quest.Pirate_Notification.function         = "PirateNotificationUPD";
    }

    if(Rank >= 12 && !EncProgress[12])
    {
        EncProgress[12] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_LARGE];
        Enc_ConvertShips(rEnc, SHIP_SPEC_RAIDER, 2, 4);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_CROWN];
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 4, 5);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_EXPEDITION];
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 2, 2);
        Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT, "Merchant", 1, 1, 2, 2);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PATROL_SMALL];
        Enc_AddShips(rEnc, SHIP_SPEC_RAIDER, "War", 1, 1, 5, 6);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PATROL_MEDIUM];
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 3, 4);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_NAVAL_MEDIUM];
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 4, 5);
    }

    if(Rank >= 13 && !EncProgress[13])
    {
        EncProgress[13] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_SMALL];
        Enc_AddShips(rEnc, SHIP_SPEC_RAIDER, "War",        1, 1, 4, 4);
        Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT, "Merchant", 1, 1, 5, 6);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_MEDIUM];
        Enc_AddShips(rEnc, SHIP_SPEC_RAIDER, "War", 1, 1, 3, 5);
        Enc_ConvertShips(rEnc, SHIP_SPEC_RAIDER, 3, 5);
    }

    if(Rank >= 17 && !EncProgress[17])
    {
        EncProgress[17] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PIRATE];
        rEnc.worldMapShip = "bark";
        Enc_DelShip(rEnc, SHIP_SPEC_UNIVERSAL, "War", 0, 1, 5, 5);
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 4, 4);
        Enc_ConvertShips(rEnc, "All", 4, 4);
		PChar.quest.Pirate_Notification.win_condition.l1 = "MapEnter";
	    PChar.quest.Pirate_Notification.function         = "PirateNotificationUPD";
    }

    if(Rank >= 20 && !EncProgress[20])
    {
        EncProgress[20] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_LARGE];
        Enc_ConvertSpec(rEnc, SHIP_SPEC_UNIVERSAL, SHIP_SPEC_WAR);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PATROL_SMALL];
        Enc_AddShips(rEnc, SHIP_SPEC_RAIDER, "War", 1, 1, 5, 6);
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 5, 6);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PATROL_MEDIUM];
        Enc_AddShips(rEnc, SHIP_SPEC_RAIDER, "War", 1, 1, 2, 2);
    }

    if(Rank >= 21 && !EncProgress[21])
    {
        EncProgress[21] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_NAVAL_MEDIUM];
        Enc_ConvertShips(rEnc, SHIP_SPEC_RAIDER, 3, 5);
        Enc_AddShips(rEnc, SHIP_SPEC_WAR, "War",           1, 1, 3, 5);
        Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT, "Merchant", 1, 1, 3, 5);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_NAVAL_LARGE];
        Enc_ConvertShips(rEnc, SHIP_SPEC_RAIDER, 2, 4);
    }

    if(Rank >= 22 && !EncProgress[22])
    {
        EncProgress[22] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_CROWN];
        Enc_ConvertShips(rEnc, SHIP_SPEC_RAIDER, 3, 5);
        Enc_ConvertShips(rEnc, SHIP_SPEC_UNIVERSAL, 3, 5);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_EXPEDITION];
        Enc_DelShip(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 2, 2);
        Enc_AddShips(rEnc, SHIP_SPEC_WAR, "War", 1, 1, 2, 2);
    }

    if(Rank >= 26 && !EncProgress[26])
    {
        EncProgress[26] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PIRATE];
        Enc_ConvertShips(rEnc, "All", 3, 3);
        Enc_AddShips(rEnc, SHIP_SPEC_RAIDER, "War", 1, 1, 3, 3);
		PChar.quest.Pirate_Notification.win_condition.l1 = "MapEnter";
	    PChar.quest.Pirate_Notification.function         = "PirateNotificationUPD";
    }

    if(Rank >= 31 && !EncProgress[31])
    {
        EncProgress[31] = true;

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_NAVAL_LARGE];
        Enc_ConvertShips(rEnc, SHIP_SPEC_WAR, 1, 3);
        Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT, "Merchant", 1, 1, 3, 3);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PIRATE];
        rEnc.worldMapShip = "frigate";
        Enc_ConvertShips(rEnc, "All", 2, 3);
		PChar.quest.Pirate_Notification.win_condition.l1 = "MapEnter";
	    PChar.quest.Pirate_Notification.function         = "PirateNotificationUPD";
    }
}

void PirateNotificationUPD(string qName)
{
    Notification(StringFromKey("QuestsUtilite_276"), "pirhunter");
}
