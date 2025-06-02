#define ENCOUNTER_GROUP		"egroup__"

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

	bool bReturn = false;
	int iNearIslandNation = PIRATE;

	if (sIslandID != "" && !Island_IsEncountersEnable(sIslandID)) return false;

	switch(iMapEncounterType)
	{
		case WDM_ETYPE_MERCHANT:		// merchant ship
			bReturn = GenerateMapEncounter_Merchant(sIslandID, iEncounter1);
		break;
		case WDM_ETYPE_FOLLOW:			// war ship
			bReturn = GenerateMapEncounter_War(sIslandID, iEncounter1, GetMainCharacterIndex(), true);
		break;
		case WDM_ETYPE_WARRING:			// war-war or war-trade ships in battle; TO_DO: trade-trade
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
		rEncounter1.GroupName = ENCOUNTER_GROUP + iEncounter1;
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
		rEncounter2.GroupName = ENCOUNTER_GROUP + iEncounter2;
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
	if (iNation < 0)
	{
		return false;
	}
	rEncounter.nation = iNation;
	//trace("iNation is " + iNation);

	iEncounter = iEncounterSlot;
	rEncounter.bUse = true;
	rEncounter.Type = "trade";

	rEncounter.Task = AITASK_MOVE;
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
	if (iNation < 0)
	{
		return false;
	}
	rEncounter.nation = iNation;

	iEncounter = iEncounterSlot;
	rEncounter.bUse = true;
	rEncounter.Type = "special";

	rEncounter.Task = AITASK_MOVE;

	WME_FixShipTypes(rEncounter, 12); //boal
	return GenerateMapEncounter_SetMapShipModel(rEncounter);
}

bool GenerateMapEncounter_War(string sIslandID, ref iEncounter, int iCharacterIndexAsEnemy, bool bFixTypes)
{
	int iEncounterType = -1;

	// find free slot in dynamic encounter table for map
	int iEncounterSlot = FindFreeMapEncounterSlot();
	if (iEncounterSlot == -1) return false;
	ManualReleaseMapEncounter(iEncounterSlot);

	ref rEncounter = &MapEncounters[iEncounterSlot];

	// try to find quest encounters
	if (iCharacterIndexAsEnemy != -1)
	{
		// try to find Quest encounter
		int iQEncounter = Encounter_FindFirstQuestMapEncounter(ENCOUNTER_WAR);
		if (iQEncounter >= 0)
		{
			ref rQEncounter = Encounter_GetQuestMapEncounter(iQEncounter);
			if (rand(99) < sti(rQEncounter.Rand))
			{
				string sGroupID = rQEncounter.ID;
				if (!sti(rQEncounter.Permanent)) Encounter_DeleteQuestMapEncounter(sGroupID);
				ref rGCommander = Group_GetGroupCommander(sGroupID);

				rEncounter.Nation = sti(rGCommander.Nation);
				rEncounter.bUse = true;
				rEncounter.qID = sGroupID;
				rEncounter.GroupName = sGroupID;
				rEncounter.GeraldSails = true;

				iEncounter = iEncounterSlot;
				return true;
			}
		}
	}

	int iNation = -1;

	// find real encounter if not punitive
	if (iEncounterType == -1)
	{
		iEncounterType = FindWarEncounter();
        if (iEncounterType == -1) return false;
	}

	rEncounter.RealEncounterType = iEncounterType;

	// nation find
	if (iNation == -1)
	{
		iNation = GetRandomNationForMapEncounter(sIslandID, false);
	}

	if (iNation < 0)
	{
		return false;
	}

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

    if(bFixTypes)
        WME_FixShipTypes(rEncounter, 12); //boal
    GenerateMapEncounter_SetMapShipModel(rEncounter);
	return true;
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
		if (!GenerateMapEncounter_War(sIslandID, iEncounter1, -1, true))
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
	if (!GenerateMapEncounter_War(-1, iEncounter2, -1, false))
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

	rEncounter1.Lock = true;
	rEncounter1.bUse = true;
	rEncounter1.Task = AITASK_ATTACK;
    rEncounter1.Task.Target = ENCOUNTER_GROUP + iEncounter2;

    rEncounter2.Lock = true;
    rEncounter2.bUse = true;
	rEncounter2.Task = AITASK_ATTACK;
    rEncounter2.Task.Target = ENCOUNTER_GROUP + iEncounter1;

	GenerateMapEncounter_SetMapShipModel(rEncounter1);
	GenerateMapEncounter_SetMapShipModel(rEncounter2);

	return true;
}

void WME_FixShipTypes(ref rEncounter, int iMaxShipNum)
{
    int iNation = sti(rEncounter.Nation);
    int iEType  = sti(rEncounter.RealEncounterType);
    ref rEncTemplate = &EncountersTypes[iEType];

    // Общая классификация для уведомлений
    int iNumMerchantShips = 0;
    int iNumWarShips = 0;

    string sAttr;
    int count = 0;
    int cMin, cMax;
    int iShipType, i, j, max_i, qty_j;
    aref rEncShips, rShip;
    float fPower = 0.0;

    makearef(rEncShips, rEncTemplate.Ships);
    max_i = GetAttributesNum(rEncShips);
    for(i = 0; i < max_i; i++)
    {
        rShip = GetAttributeN(rEncShips, i);
        qty_j = sti(rShip.qMin) + rand(sti(rShip.qMax) - sti(rShip.qMin));
        cMin = sti(rShip.cMin);
        cMax = sti(rShip.cMax);
        for(j = 0; j < qty_j; j++)
        {
            if(count+1 > iMaxShipNum) break;

            iShipType = WME_GetShipTypeExt(cMin, cMax, rShip.Type, rShip.ShipSpec, -1); // ~!~ TO_DO: iNation
            if (iShipType >= SHIP_LSHIP_FRA && iShipType <= SHIP_LSHIP_ENG && rand(100) > 8)
            {
                iShipType = SHIP_LINESHIP; // Дополнительный тест на линейник
            }
            if (iShipType == INVALID_SHIP_TYPE) continue;

            count++;
            sAttr = count;
            rEncounter.ShipTypes.(sAttr) = iShipType;
            fPower += GetBaseShipPower(iShipType);
            if(rShip.Type == "Merchant")
            {
                rEncounter.ShipModes.(sAttr) = "trade";
                iNumMerchantShips++;
            }
            else
            {
                if (iEType >= ENCOUNTER_TYPE_SMUGGLERS && iEType <= ENCOUNTER_TYPE_PIRATE)
                    rEncounter.ShipModes.(sAttr) = "pirate";
                else
                    rEncounter.ShipModes.(sAttr) = "war";
                iNumWarShips++;
            }
        }
        if(count+1 > iMaxShipNum) break;
    }

    rEncounter.Power = fPower; // Механика мощи
    rEncounter.NumMerchantShips = iNumMerchantShips;
    rEncounter.NumWarShips = iNumWarShips;
    rEncounter.FixedTypes = true;
}

int WME_GetShipTypeExt(int iClassMin, int iClassMax, string sShipType, string sShipSpec, int iNation)
{
	int iShips[60];
	int i, j, q, iShipsNum;
	iShipsNum = 0;
	aref aNation;
	string sAttr;
	bool bOk;

    // Энкаунтеры только до линкора, квестовые корабли отдельно
	for (i = SHIP_TARTANE; i <= SHIP_LSHIP_ENG; i++) 
	{
		object rShip = GetShipByType(i);

		if (sti(rShip.CanEncounter) != true)     continue;
		if (sti(rShip.Type.(sShipType)) != true) continue;
        if (rShip.Spec != sShipSpec)             continue;

		int iClass = MakeInt(rShip.Class);
        // Сравнение классов числовое, то есть iClassMin - это большие корабли
		if (iClass < iClassMin || iClass > iClassMax) continue;

        if(iNation != -1) // Скип
        {
            bOk = false;
            if(CheckAttribute(rShip, "nation"))
            {
                makearef(aNation, rShip.nation);
                q = GetAttributesNum(aNation);
                for(j = 0; j < q; j++)
                {
                    sAttr = GetAttributeName(GetAttributeN(aNation, j)); 
                    if(GetNationTypeByName(sAttr) == iNation && rShip.nation.(sAttr) == true) {
                        bOk = true;
                        break;
                    }
                }
            }	
            if(!bOk) continue;
        }

		iShips[iShipsNum] = i;
		iShipsNum++;
	}

	if (iShipsNum == 0) 
	{
		Trace("Can't find ship type '" + sShipType + "' with ClassMin = " + iClassMin + " and ClassMax = " + iClassMax);
		return INVALID_SHIP_TYPE;
	}

	return iShips[rand(iShipsNum - 1)];
}
