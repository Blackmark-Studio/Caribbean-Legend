
//=========================================================================================
//Events
//=========================================================================================

void wdmEvent_EncounterCreate()
{
	float dltTime = GetEventData();
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();	
	//Skip encounters ------ даёт тормоза
//	if(CheckAttribute(worldMap, "noenc") != 0)
//	{
//		if(worldMap.noenc == "true") return;
//	}
	//Save player ship position
	worldMap.playerShipX = playerShipX;
	worldMap.playerShipZ = playerShipZ;
	worldMap.playerShipAY = playerShipAY;
	//Generate encounters		
	wdmStormGen(dltTime, playerShipX, playerShipZ, playerShipAY);
	wdmShipEncounter(dltTime, playerShipX, playerShipZ, playerShipAY);	// даёт тормоза
}

void wdmEvent_PlayerInStorm()
{
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	int stormIndex = GetEventData();
	if(!IsCharacterEquippedArtefact(pchar, "talisman2")) wdmReloadToSea();
}

void wdmEvent_ShipEncounter()
{
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();

    // Выделенный игроком корабль, либо догнавший преследователь
    // То есть тот, из-за кого открылся интерфейс
	int eshipIndex = GetEventData();

	LaunchMapScreen(eshipIndex);
}

void wdmEvent_UpdateDate()
{
	Environment.date.day = worldMap.date.day;
	Environment.date.month = worldMap.date.month;	
	Environment.date.year = worldMap.date.year;
	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = GetEventData();
}

//Добавляем по запросу квестовых энкоунтеров
#event_handler("WorldMap_AddQuestEncounters", "wdmEvent_AddQuestEncounters");
void wdmEvent_AddQuestEncounters()
{
	int idx = -1;
	string encID = "";
	string encPath = "";
	aref encs, at;
	makearef(encs, worldMap.addQuestEncounters);
	int num = GetAttributesNum(encs);
	for(int i = 0; i < num; i++)
	{
		at = GetAttributeN(encs, i);

		if (CheckAttribute(at, "characterID")) // boal fix 14.09.06
		{
			if(at.type == "trader")
			{
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_TraderSucces", 100, "s", at.characterID);
					continue;
				}
				//Создаём в карте энкоунтера
				encID = "";
				if (CheckAttribute(at, "XZGoto")) // покоординатный boal 04/10/06
				{
					if(!wdmCreateMerchantShipXZByIndex(1.0, idx, &encID, float(at.x1), float(at.z1), float(at.x2), float(at.z2), int(at.TimeOut)))
					{
						PostEvent("Map_TraderSucces", 100, "s", at.characterID);
						continue;
					}
				}
				else
				{
					if(!wdmCreateMerchantShipByIndex(1.0, idx, &encID, at.beginlocator, at.endLocator, int(at.TimeOut)))
					{
						PostEvent("Map_TraderSucces", 100, "s", at.characterID);
						continue;
					}
				}
				//Путь до энкоунтера
				encPath = "encounters." + encID;
				//Сохраняем принадлежность к квестовым энкоунтеров
				worldMap.(encPath).quest.event = "Map_TraderSucces";
				worldMap.(encPath).quest.chrID = at.characterID;
			}
			if(at.type == "cooltrader")
			{
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_TraderSucces", 100, "s", at.characterID);
					continue;
				}
				//Создаём в карте энкоунтера
				encID = "";
				if(!wdmCreateMerchantShipByIndex(float(at.speed), idx, &encID, at.beginlocator, at.endLocator, int(at.TimeOut)))
				{
					PostEvent("Map_TraderSucces", 100, "s", at.characterID);
					continue;
				}
				//Путь до энкоунтера
				encPath = "encounters." + encID;
				//Сохраняем принадлежность к квестовым энкоунтеров
				worldMap.(encPath).quest.event = "Map_TraderSucces";
				worldMap.(encPath).quest.chrID = at.characterID;
			}
			if(at.type == "warrior")
			{			
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					continue;
				}
				//Создаём в карте энкоунтера
				encID = "";
				//if(!wdmCreateFollowShipByIndex(1.0, idx, &encID, at.beginlocator, int(at.TimeOut)))
				if(!wdmCreateRealFollowShipByIndex(1.0, idx, &encID, int(at.TimeOut)))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					continue;
				}
				//Путь до энкоунтера
				encPath = "encounters." + encID;
				//Сохраняем принадлежность к квестовым энкоунтеров
				worldMap.(encPath).quest.event = "Map_WarriorEnd";
				worldMap.(encPath).quest.chrID = at.characterID;
			}
			if(at.type == "coolwarrior")
			{
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					continue;
				}
				//Создаём в карте энкоунтера
				encID = "";
				//if(!wdmCreateFollowShipByIndex(1.0, idx, &encID, at.beginlocator, int(at.TimeOut)))
				if(!wdmCreateRealFollowShipByIndex(1.7, idx, &encID, int(at.TimeOut)))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					continue;
				}
				//Путь до энкоунтера
				encPath = "encounters." + encID;
				//Сохраняем принадлежность к квестовым энкоунтеров
				worldMap.(encPath).quest.event = "Map_WarriorEnd";
				worldMap.(encPath).quest.chrID = at.characterID;
			}
			if(at.type == "battle")
			{
				//wdmQuestCreateBattle(at.characterID, int(at.iEnemyNation), int(at.TimeOut));
			}
		}
	}

	DeleteAttribute(&worldMap, "addQuestEncounters");
	worldMap.addQuestEncounters = "";
	ReleaseMapEncounters();
}

#event_handler("WorldMap_IsSkipEnable", "wdmIsSkipEnable");
bool wdmIsSkipEnable()
{
	// НЕ ИСПОЛЬЗУЕТСЯ
	return false;
}

void wdmDeleteLoginEncounter(string encID)
{
	Event("WorldMap_EncounterDelete", "s", encID);
}

#event_handler("WorldMap_EncounterDelete", "wdmEncounterDelete");
ref wdmEncounterDelete()
{
	BI_intRetValue = true;

	string encID = GetEventData();
	string encPath = "encounters." + encID;
	if(!CheckAttribute(&worldMap, encPath))
	{
		return &BI_intRetValue;
	}

	aref enc;
	makearef(enc, worldMap.(encPath));

	//Сохраняем событие
	bool needEvent = false;
	string eventName = "";
	string chrID = "";
	
	if(CheckAttribute(enc, "quest.chrID"))
	{
		//homo 14/04/07 не ясно если энкоутер ещё не доплыл до пункта назанчения значит его нельзя тереть?
		//Даже если его трет программист?
    	if(CheckAttribute(&enc, "Gotox") && CheckAttribute(&enc, "Gotoz"))
		{
			float fDeltaX = (float(enc.x) - float(enc.Gotox));
			float fDeltaZ = (float(enc.z) - float(enc.Gotoz));
			float fRadSqr = fDeltaX*fDeltaX + fDeltaZ*fDeltaZ;
			if( fRadSqr > 100.0 && float(enc.livetime) > 1.0)
			{
				BI_intRetValue = false;
			}
		}

		if(CheckAttribute(enc, "quest.event") != 0)
		{
			eventName = enc.quest.event;
			chrID = enc.quest.chrID;
			needEvent = true;
		}		
	}

	//Отмечаем, что удалён
	enc.needDelete = "wdmEncounterDelete";
	//Удаляем квестовую пометку
	DeleteAttribute(&enc, "quest");

	if (!IsEntity(&worldMap))
	{
	   //Трем сам энкаутер сразу homo 10/04/07
        DeleteAttribute(&worldMap, encPath);
    }

	//Отправляем квестовый эвент, если надо
	if(needEvent)
	{
		PostEvent(eventName, 100, "s", chrID);
	}	
	return &BI_intRetValue;
}

#event_handler("WorldMap_GetMoral", "wdmGetMoral");
float wdmGetMoral()
{
	int iMorale = 0;
	int cn = -1;
	int iRealCompNum = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			iMorale = iMorale + GetCharacterCrewMorale(&characters[cn]);
			iRealCompNum++;
		}
	}
	iMorale = iMorale / iRealCompNum;
	return float(iMorale);
}

//  квестовый отлов входа в море по наличию НПС в случайке
void wdmEnterSeaQuest(string _chrId)
{
	ref NPChar = characterFromID(_chrId);
		// homo 19/07/06 GlodFleet
	if (_chrId == "Head_of_Gold_Squadron")
	{
        string sQuest = "GoldFleetEncounter";
        pchar.quest.(sQuest).win_condition.l1 = "EnterToSea";  // fix homo 20/01/07
        pchar.quest.(sQuest).win_condition = "GoldFleetEncounter";
        pchar.quest.(sQuest).function = "GoldFleetEncounter";
	}
	//homo 27/09/06
	if (findsubstr(_chrId, "SiegeCap_1" , 0) != -1)// Осаждающая эскадра
	{
        SiegeSquadronOnMap(_chrId);
	}
	
	if (_chrId == "Tonzag_Hunter_1") {
		AddQuestRecord("Tonzag", "5");
		bQuestDisableMapEnter = true;
	}
	
	if (_chrId == "SantaMisericordia_cap") 
	{
		Log_testinfo("Напали на ГАЛЕОН");
		SantaMisericordia_fromMapBattle(_chrId);
	}
}

#event_handler("WorldMap_GetWindParameters", "wdmGetWindParameters");
void wdmGetWindParameters()
{
	PChar.WorldMap.WindForce = GetEventData();
	PChar.WorldMap.WindAngle = GetEventData();
}

// belamour модель корабля главного героя на глобальной карте
#event_handler("WorldMap_GetPlayerShipModel", "GetPlayerShipModel");
string GetPlayerShipModel()
{
	if(GetCharacterShipType(pchar) != SHIP_NOTUSED)
	{
		if(int(RealShips[int(pchar.Ship.Type)].BaseType) == SHIP_GALEON_SM) return "galeon_sm_player";
		if(int(RealShips[int(pchar.Ship.Type)].BaseType) == SHIP_LADYBETH) return "shnyava_sp2_player";
		if(int(RealShips[int(pchar.Ship.Type)].BaseType) == SHIP_MEMENTO) return "memento_player";
		if(int(RealShips[int(pchar.Ship.Type)].BaseType) == SHIP_AMSTERDAM) return "amsterdam_sp4_player";
	}
	return "Ship";
}

#event_handler("ShipInArea", "ShipInArea");
void ShipInArea()
{
	string s = GetEventData();
	ref rIsland = GetIslandByID(s);
	if(!int(rIsland.visible))
		s = "Open Sea";
	if(s == "Open Sea")
		s = XI_ConvertString(s);
	else
		s = GetConvertStr(s, "LocLables.txt");
	WM_SetShipAreaInfo(s);
}

#event_handler("WorldMap_GetSeasonsRingAngle", "WorldMap_GetSeasonsRingAngle");
float WorldMap_GetSeasonsRingAngle()
{
	int iMonth = GetDataMonth();
	int numSeasonDays = 90;
	int iSeason;
	if(iMonth >= 3 && iMonth <= 5)
	{
		iSeason = 0;
		numSeasonDays = GetMonthDays(3) + GetMonthDays(4) + GetMonthDays(5);
	}
	else if(iMonth >= 6 && iMonth <= 8)
	{
		iSeason = 1;
		numSeasonDays = GetMonthDays(6) + GetMonthDays(7) + GetMonthDays(8);
	}
	else if(iMonth >= 9 && iMonth <= 11)
	{
		iSeason = 2;
		numSeasonDays = GetMonthDays(9) + GetMonthDays(10) + GetMonthDays(11);
	}
	else
	{
		iSeason = 3;
		numSeasonDays = GetMonthDays(12) + GetMonthDays(1) + GetMonthDays(2);
	}
	int curSeasonDay = 1;
	switch(iMonth)
	{
		case 1:		curSeasonDay = GetMonthDays(12) + GetDataDay();							break;
		case 2:		curSeasonDay = GetMonthDays(12) + GetMonthDays(1) + GetDataDay();		break;
		case 3:		curSeasonDay = GetDataDay();											break;
		case 4:		curSeasonDay = GetMonthDays(3) + GetDataDay();							break;
		case 5:		curSeasonDay = GetMonthDays(3) + GetMonthDays(4) + GetDataDay();		break;
		case 6:		curSeasonDay = GetDataDay();											break;
		case 7:		curSeasonDay = GetMonthDays(6) + GetDataDay();							break;
		case 8:		curSeasonDay = GetMonthDays(6) + GetMonthDays(7) + GetDataDay();		break;
		case 9:		curSeasonDay = GetDataDay();											break;
		case 10:	curSeasonDay = GetMonthDays(9) + GetDataDay();							break;
		case 11:	curSeasonDay = GetMonthDays(9) + GetMonthDays(10) + GetDataDay();		break;
		case 12:	curSeasonDay = GetDataDay();											break;
	}
	return (iSeason + float(curSeasonDay) / float(numSeasonDays)) * PId2;
}