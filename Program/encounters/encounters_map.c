#define ENCOUNTER_GROUP		"egroup__"
int iEncStamp = 0;
int GetEncStamp()
{
    iEncStamp++; // overflow allowed
    return iEncStamp;
}

int FindFreeMapEncounterSlot()
{
	for (int i=0;i<MAX_MAP_ENCOUNTERS;i++)
	{
		if (sti(MapEncounters[i].bUse) == false)
		{
			return i;
		}

		if(i > 0)
		{
			if (CheckAttribute(&MapEncounters[i], "groupname") && CheckAttribute(&MapEncounters[i-1], "groupname"))
			{
				if(MapEncounters[i].realencountertype == MapEncounters[i - 1].realencountertype &&
					MapEncounters[i].groupname == MapEncounters[i - 1].groupname &&
					MapEncounters[i].characterid == MapEncounters[i - 1].characterid &&
					MapEncounters[i].nation == MapEncounters[i - 1].nation)
				{
					MapEncounters[i].bUse = false;
					return i;
				}
			}
		}

	}
	//Trace("FindFreeMapEncounterSlot: Can't find free slot!!!");
	return -1;
}

void ManualReleaseMapEncounter(int iEncounterSlot)
{
	DeleteAttribute(&MapEncounters[iEncounterSlot], "");
	MapEncounters[iEncounterSlot].bUse = false;
}

void ReleaseMapEncounters()
{
    if (wdmLockRelease) return;
	for (int i=0;i<MAX_MAP_ENCOUNTERS;i++)
	{
		DeleteAttribute(&MapEncounters[i],"");
		MapEncounters[i].bUse = false;
	}
}

void ReleaseMapEncounter(int iEncounterSlot)
{
	Trace("Release encounter with slot " + iEncounterSlot);
	if (sti(MapEncounters[iEncounterSlot].bUse) == true)
	{
		DeleteAttribute(&MapEncounters[iEncounterSlot],"");
		MapEncounters[iEncounterSlot].bUse = false;
		return;
	}
	//Trace("ReleaseMapEncounter: ERROR: Encounter not used idx = " + iEncounterSlot);
}

ref GetMapEncounterRef(int iEncounterSlot)
{
	return &MapEncounters[iEncounterSlot];
}

ref GetMapEncounterNationRef(int iEncounterSlot)
{
	if (sti(MapEncounters[iEncounterSlot].bUse) == true)
	{
		return GetNationByType(sti(MapEncounters[iEncounterSlot].Nation));
	}
	//Trace("GetMapEncounterNationString: error: not found use slot iEncounterSlot = " + iEncounterSlot);
	return GetNationByType(ENGLAND);
}

bool GenerateMapEncounter(int iMapEncounterType, string sIslandID, ref iEncounter1, ref iEncounter2)
{
	iEncounter1 = -1;
	iEncounter2 = -1;

    bool bSetGrp = true;
	bool bReturn = false;

	if (sIslandID != "" && !Island_IsEncountersEnable(sIslandID)) return false;

	switch(iMapEncounterType)
	{
		case WDM_ETYPE_MERCHANT:		// merchant ship
			bReturn = GenerateMapEncounter_Merchant(sIslandID, iEncounter1);
		break;
		case WDM_ETYPE_FOLLOW:			// war ship
			bReturn = GenerateMapEncounter_War(sIslandID, iEncounter1, true);
		break;
		case WDM_ETYPE_WARRING:			// war-war or war-trade ships in battle; TO_DO: trade-trade
            bSetGrp = false;
			bReturn = GenerateMapEncounter_Battle(sIslandID, iEncounter1, iEncounter2);
		break;
		case WDM_ETYPE_SPECIAL:			// barrel or shipwreck
			bReturn = GenerateMapEncounter_Special(sIslandID, iEncounter1);
		break;
	}

	if (!bReturn)
	{
		return false;
	}

	ref rEncounter1, rEncounter2;

	if (iEncounter1 != -1)
	{
		rEncounter1 = &MapEncounters[iEncounter1];
        if(bSetGrp)
            rEncounter1.GroupName = ENCOUNTER_GROUP + GetEncStamp();
		if(sti(rEncounter1.nation) == PIRATE)
		{
            // ~!~
			if(sti(rEncounter1.RealEncounterType) < ENCOUNTER_TYPE_SMUGGLERS || sti(rEncounter1.RealEncounterType) > ENCOUNTER_TYPE_PIRATE)
			{
				iEncounter1 = -1;
				iEncounter2 = -1;
				return false;
			}
		}
	}
	if (iEncounter2 != -1)
	{
		rEncounter2 = &MapEncounters[iEncounter2];
        if(bSetGrp)
            rEncounter2.GroupName = ENCOUNTER_GROUP + GetEncStamp();
		if(sti(rEncounter2.nation) == PIRATE)
		{
            // ~!~
			if(sti(rEncounter2.RealEncounterType) < ENCOUNTER_TYPE_SMUGGLERS || sti(rEncounter2.RealEncounterType) > ENCOUNTER_TYPE_PIRATE)
			{
				iEncounter1 = -1;
				iEncounter2 = -1;
				return false;
			}
		}
	}


	if(iEncounter1 != -1 && iEncounter2 != -1)
	{
		if(GetNationRelation(sti(rEncounter1.nation), sti(rEncounter2.nation)) != RELATION_ENEMY)
		{
			iEncounter1 = -1;
			iEncounter2 = -1;
			return false;
		}
	}

	int i1 = iEncounter1;
	int i2 = iEncounter2;

	//Trace("Create encounter with slot " + iEncounter1 + ", Real = " + i1);
	//Trace("Create encounter with slot " + iEncounter2 + ", Real = " + i2);

	return true;
}

bool GenerateMapEncounter_SetMapShipModel(ref rEncounter)
{
	string sLastName;
	if(!CheckAttribute(rEncounter, "Nation"))
	{
		trace("У ЭНКАУНТЕРА НЕТ НАЦИИИ!!!");
		return false;
	}
	string sFirstName = Nations[sti(rEncounter.Nation)].worldMapShip;

	if (sti(rEncounter.RealEncounterType) == ENCOUNTER_TYPE_ALONE)
	{
		if(!CheckAttribute(rEncounter, "CharacterID"))
		{
			trace("Квестовому энкаунтеру не назначен персонаж!");
			return false;
		}
		int iCharIndex = GetCharacterIndex(rEncounter.CharacterID);
		if (iCharIndex < 0)
		{
			trace("Квестовому энкаунтеру назначен персонаж, но его нет!");
			return false;
		}

		ref rCharacter = GetCharacter(iCharIndex);
		if (CheckAttribute(rCharacter, "MapEnc.worldMapShip")) // boal fix
		{
			rEncounter.worldMapShip = rCharacter.MapEnc.worldMapShip;
		}
		else
		{
		    rEncounter.worldMapShip = sFirstName + "_bark";  // boal new
		}
	}
	else
	{
		sLastName = EncountersTypes[sti(rEncounter.RealEncounterType)].worldMapShip;
		rEncounter.worldMapShip = sFirstName + "_" + sLastName;
		Trace(" rEncounter.worldMapShip = " + rEncounter.worldMapShip);
	}

	return true;
}

bool GenerateMapEncounter_Merchant(string sIslandID, ref iEncounter)
{
	// find free slot in dynamic encounter table for map
	int iEncounterSlot = FindFreeMapEncounterSlot();
	if (iEncounterSlot == -1) return false;
	ManualReleaseMapEncounter(iEncounterSlot);

	ref rEncounter = &MapEncounters[iEncounterSlot];

	// find real encounter
	int iEncounterType = FindMerchantEncounter();
	if (iEncounterType == -1) return false;
	rEncounter.RealEncounterType = iEncounterType;

	// nation find
	int iNation = GetRandomNationForMapEncounter(sIslandID, true);
	if (iNation < 0) return false;

	rEncounter.nation = iNation;
	//trace("iNation is " + iNation);

	iEncounter = iEncounterSlot;
	rEncounter.bUse = true;
	rEncounter.Type = "trade";

	rEncounter.Task = AITASK_MOVE;
    DeleteAttribute(rEncounter, "Task.Target");
	// create move point coordinates here

	WME_FixShipTypes(rEncounter, 12); //boal
	return GenerateMapEncounter_SetMapShipModel(rEncounter);
}

bool GenerateMapEncounter_Special(string sIslandID, ref iEncounter)
{
	// find free slot in dynamic encounter table for map
	int iEncounterSlot = FindFreeMapEncounterSlot();
	if (iEncounterSlot == -1) return false;
	ManualReleaseMapEncounter(iEncounterSlot);

	ref rEncounter = &MapEncounters[iEncounterSlot];

	// find real encounter
	int iEncounterType = FindSpecialEncounter();
	if (iEncounterType == -1) return false;
	rEncounter.RealEncounterType = iEncounterType;

	// nation find
	int iNation = GetRandomNationForMapEncounter(sIslandID, true);
	if (iNation < 0) return false;

	rEncounter.nation = iNation;

	iEncounter = iEncounterSlot;
	rEncounter.bUse = true;
	rEncounter.Type = "special";

	rEncounter.Task = AITASK_MOVE;
    DeleteAttribute(rEncounter, "Task.Target");

	WME_FixShipTypes(rEncounter, 12); //boal
	return GenerateMapEncounter_SetMapShipModel(rEncounter);
}

bool GenerateMapEncounter_War(string sIslandID, ref iEncounter, bool bFixTypes)
{
	// find free slot in dynamic encounter table for map
	int iEncounterSlot = FindFreeMapEncounterSlot();
	if (iEncounterSlot == -1) return false;
	ManualReleaseMapEncounter(iEncounterSlot);

	ref rEncounter = &MapEncounters[iEncounterSlot];

	// find real encounter if not punitive
	int iEncounterType = FindWarEncounter();
	if (iEncounterType == -1) return false;

	rEncounter.RealEncounterType = iEncounterType;

	// nation find
	int iNation = GetRandomNationForMapEncounter(sIslandID, false);
	if (iNation < 0) return false;

	//trace("iNation is " + iNation);

	if(iEncounterType >= ENCOUNTER_TYPE_SMUGGLERS && iEncounterType <= ENCOUNTER_TYPE_PIRATE)
	{
		iNation = PIRATE;
	}

	rEncounter.Nation = iNation;
    rEncounter.Type = "war";

	if(GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY)
	{
		rEncounter.Task = AITASK_MOVE;
		DeleteAttribute(rEncounter, "Task.Target");
	}
	else
	{
		rEncounter.Task = AITASK_ATTACK;
		rEncounter.Task.Target = PLAYER_GROUP;
	}
	iEncounter = iEncounterSlot;

	if (sti(rEncounter.Nation) == PIRATE)
	{
		rEncounter.Type = "pirate";
	}

	rEncounter.bUse = true;

    if(bFixTypes) WME_FixShipTypes(rEncounter, 12); //boal
    return GenerateMapEncounter_SetMapShipModel(rEncounter);
}

bool GenerateMapEncounter_Alone(string sCharacterID, ref iEncounterIndex)
{
	iEncounterIndex = -1;
	int iCharIndex = GetCharacterIndex(sCharacterID);
	if (iCharIndex < 1) { return false; }  //fix

	ref rCharacter = GetCharacter(iCharIndex);

	int iEncounterSlot = FindFreeMapEncounterSlot();
	if (iEncounterSlot == -1) return false;
	ManualReleaseMapEncounter(iEncounterSlot);

	ref rEncounter = &MapEncounters[iEncounterSlot];

	rEncounter.RealEncounterType = ENCOUNTER_TYPE_ALONE;

	rEncounter.GroupName = sCharacterID;
	rEncounter.CharacterID = sCharacterID;
	rEncounter.Nation = rCharacter.Nation;

	iEncounterIndex = iEncounterSlot;

	rEncounter.bUse = true;

	if(!CheckAttribute(rCharacter, "MapEnc.type"))
	{
		trace ("Character "+ rCharacter.id + " have no MapEnc.type field");
		return false;
	}
	else
	{
		if (rCharacter.MapEnc.Type == "war")
		{
			rEncounter.NumWarShips = 1;
			rEncounter.NumMerchantShips = 0;
			rEncounter.Type = "war";
			rEncounter.Task = AITASK_ATTACK;
			rEncounter.Task.Target = PLAYER_GROUP;
		}
		else
		{
			rEncounter.NumMerchantShips = 1;
			rEncounter.NumWarShips = 0;
			rEncounter.Type = "trade";
			rEncounter.Task = AITASK_MOVE;
			DeleteAttribute(rEncounter, "Task.Target");
		}
	}

	GenerateMapEncounter_SetMapShipModel(rEncounter);

	// create move point coordinates here

	return true;
}

bool GenerateMapEncounter_Battle(string sIslandID, ref iEncounter1, ref iEncounter2)
{
	//check for trade opposition
	int iIsTrade = rand(3);

	// generate first encounter
	if (iIsTrade != 0)
	{
		if (!GenerateMapEncounter_War(sIslandID, iEncounter1, true))
		{
			iEncounter1 = -1; iEncounter2 = -1;
			return false;
		}
	}
	else
	{
		if (!GenerateMapEncounter_Merchant(sIslandID, iEncounter1))
		{
			iEncounter1 = -1; iEncounter2 = -1;
			return false;
		}

		float fAngle = frnd() * PIm2;
		MapEncounters[iEncounter1].Task.Pos.x = 10000.0 * sin(fAngle);
		MapEncounters[iEncounter1].Task.Pos.z = 10000.0 * cos(fAngle);
	}

	// generate second encounter; TO_DO: also Merchant
	if (!GenerateMapEncounter_War(-1, iEncounter2, false))
	{
		ManualReleaseMapEncounter(iEncounter1);
		iEncounter1 = -1; iEncounter2 = -1;
		return false;
	}

	ref rEncounter1 = &MapEncounters[iEncounter1];
	ref rEncounter2 = &MapEncounters[iEncounter2];

	int iRealEncounterType1 = rEncounter1.RealEncounterType;
	int iRealEncounterType2 = rEncounter2.RealEncounterType;

	// find nations for battle between two encounters

	int iNationsCanBe[MAX_NATIONS];
	int iNumNationsCanBe = 0;

	int iNation1 = sti(rEncounter1.Nation);
	int iNation2 = sti(rEncounter2.Nation);

	// if we hit the target with nations - return
	if (GetNationRelation(iNation1, iNation2) != RELATION_ENEMY)
	{
		// search enemy for iNation1
		for (int i=0; i<MAX_NATIONS; i++)
		{
			bool bCanBe = Encounter_CanNation(iRealEncounterType2, i);
			if (!bCanBe) continue;
			if (GetNationRelation(i, iNation1) != RELATION_ENEMY) continue;
			iNationsCanBe[iNumNationsCanBe] = i;
			iNumNationsCanBe++;
		}

		if (iNumNationsCanBe == 0)
		{
			ManualReleaseMapEncounter(iEncounter1);
			ManualReleaseMapEncounter(iEncounter2);
			iEncounter1 = -1; iEncounter2 = -1;
			return false;
		}

		rEncounter2.Nation = iNationsCanBe[rand(iNumNationsCanBe - 1)];
	}

	if(iRealEncounterType1 >= ENCOUNTER_TYPE_SMUGGLERS && iRealEncounterType1 <= ENCOUNTER_TYPE_PIRATE)
	{
		rEncounter1.Nation = PIRATE;
	}
	if(iRealEncounterType2 >= ENCOUNTER_TYPE_SMUGGLERS && iRealEncounterType2 <= ENCOUNTER_TYPE_PIRATE)
	{
		rEncounter2.Nation = PIRATE;
	}
    WME_FixShipTypes(rEncounter2, 12);

    rEncounter1.GroupName = ENCOUNTER_GROUP + GetEncStamp();
    rEncounter2.GroupName = ENCOUNTER_GROUP + GetEncStamp();

	rEncounter1.Lock = true;
	rEncounter1.bUse = true;
	rEncounter1.Task = AITASK_ATTACK;
    rEncounter1.Task.Target = rEncounter2.GroupName;

    rEncounter2.Lock = true;
    rEncounter2.bUse = true;
	rEncounter2.Task = AITASK_ATTACK;
    rEncounter2.Task.Target = rEncounter1.GroupName;

	GenerateMapEncounter_SetMapShipModel(rEncounter1);
	GenerateMapEncounter_SetMapShipModel(rEncounter2);

	return true;
}

void WME_FixShipTypes(ref rEncounter, int iMaxShipNum)
{
    int iNation = sti(rEncounter.Nation);
    int iEType  = sti(rEncounter.RealEncounterType);
    //ref rEncTemplate = &EncountersTypes[iEType];

    // Общая классификация для уведомлений
    int iNumMerchantShips = 0;
    int iNumWarShips = 0;

    string sAttr;
    int count = 0;
    int cMin, cMax;
    int iShipType, i, j, qty_j;
    //aref rEncShips, rShip;
    float fPower = 0.0;

    //makearef(rEncShips, rEncTemplate.Ships);
    //int max_i = GetAttributesNum(rEncShips);
    
    if (iEType < WorldMapRandomEncQty)
    {
        string sType, sCurSpec;
        int BitParams;
        int RandParams = ENC_RANDOM_PARAMS[iEType];
        bool bRand = and(RandParams, 15); // Есть ли рандом
        bool bWasRand = false; // Если есть рандом, то был ли он
        for(i = 0; i < 4; i++)
        {
            if (bRand && CheckEncRand_Spec(RandParams, i))
            {
                if (bWasRand) continue;
                bWasRand = true;
                j = GetEncRandSpec(RandParams);
            }
            else j = i;

            switch (j)
            {
                case 0:
                    BitParams = ENC_MERCHANT_SLOT[iEType];
                    if (!BitParams) continue;
                    sCurSpec = "0"; //SHIP_SPEC_MERCHANT;
                    break;
                case 1:
                    BitParams = ENC_WAR_SLOT[iEType];
                    if (!BitParams) continue;
                    sCurSpec = "1"; //SHIP_SPEC_WAR;
                    break;
                case 2:
                    BitParams = ENC_RAIDER_SLOT[iEType];
                    if (!BitParams) continue;
                    sCurSpec = "2"; //SHIP_SPEC_RAIDER;
                    break;
                case 3:
                    BitParams = ENC_UNIVERSAL_SLOT[iEType];
                    if (!BitParams) continue;
                    sCurSpec = "3"; //SHIP_SPEC_UNIVERSAL;
                    break;
            }
            // rShip = GetAttributeN(rEncShips, i);
            qty_j = GetEncSlotQty(BitParams);
            cMin = and(shr(BitParams, 8), LBITS_4);
            cMax = and(shr(BitParams, 12),LBITS_4);
            for(j = 0; j < qty_j; j++)
            {
                if(count+1 > iMaxShipNum) break;

                iShipType = WME_GetShipTypeExt(cMin, cMax, sCurSpec, iNation, false); // ~!~ TO_DO: true
                if (iShipType == INVALID_SHIP_TYPE) continue;

                count++;
                sAttr = "s" + count;
                rEncounter.FixedShips.(sAttr).type = iShipType;
                fPower += GetBaseShipPower(iShipType);
                //             sCurSpec == SHIP_SPEC_UNIVERSAL
                bool bTrade = (sCurSpec == "3") && (rEncounter.type == "trade");
                if(sCurSpec == "0" || bTrade)
                {
                    rEncounter.FixedShips.(sAttr).mode = "trade";
                    iNumMerchantShips++;
                }
                else
                {
                    if (iEType >= ENCOUNTER_TYPE_SMUGGLERS && iEType <= ENCOUNTER_TYPE_PIRATE)
                        rEncounter.FixedShips.(sAttr).mode = "pirate";
                    else
                        rEncounter.FixedShips.(sAttr).mode = "war";
                    iNumWarShips++;
                }
            }
            if(count+1 > iMaxShipNum) break;
        }
    }

    rEncounter.Power = fPower; // Механика мощи
    rEncounter.NumMerchantShips = iNumMerchantShips;
    rEncounter.NumWarShips = iNumWarShips;
}

int WME_GetShipTypeExt(int iClassMin, int iClassMax, string sShipSpec, int iNation, bool bNationCheck)
{
	int classFlags = 0;
	int typeFlags = 0;
	int nationFlags = 0;

	for (int i = iClassMin; i <= iClassMax; i++)
	{
		classFlags += GetClassFlag(i);
	}

	int iType = sti(sShipSpec);
	typeFlags = gShipTypeFlags[iType];

	nationFlags = GetNationFlag(iNation);

	int iShipType = GetRandomShipTypeEx(classFlags, typeFlags, nationFlags, !bNationCheck);

	if (iShipType == SHIP_NOTUSED)
	{
        Log_TestInfo("WARNING! CANT FIND SHIP IN WME_GetShipTypeExt!");
		Trace("Can't find ship with spec " + wdmGetSpec(sti(sShipSpec)) + " and ClassMin = " + iClassMin + ", ClassMax = " + iClassMax);
		return INVALID_SHIP_TYPE;
	}

	ref refShip;
	makeref(refShip, ShipsTypes[iShipType]);

	if (CheckAttribute(refShip, "NationalLineShip") && sti(refShip.NationalLineShip))
	{
		// Доля линейников 10% от кораблей первого класса
		// В ваниле ещё может выпасть только военник
		if(rand(99) >= 20) iShipType = SHIP_LINESHIP;
	}

	return iShipType;
}

string wdmGetSpec(int iSpec)
{
    switch(iSpec)
    {
        case SHIP_SPEC_UNIVERSAL: return "Универсал"; break;
        case SHIP_SPEC_MERCHANT: return "Торговец"; break;
        case SHIP_SPEC_RAIDER: return "Рейдер"; break;
        case SHIP_SPEC_WAR: return "Военный"; break;
    }
    return "UNKNOWN";
}
