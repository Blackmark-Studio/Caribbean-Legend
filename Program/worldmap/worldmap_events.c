
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
	//DeleteAttribute(pchar, "SkipEshipIndex");// boal
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
	int eshipIndex = GetEventData();	
	if (CheckAttribute(pchar, "SkipEshipIndex") && pchar.SkipEshipIndex == eshipIndex) return; // boal
	pchar.eshipIndex = eshipIndex;
	LaunchMapScreen();

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
					if(!wdmCreateMerchantShipXZByIndex(1.0, idx, &encID, stf(at.x1), stf(at.z1), stf(at.x2), stf(at.z2), sti(at.TimeOut)))
					{
						PostEvent("Map_TraderSucces", 100, "s", at.characterID);
						continue;
					}
				}
				else
				{
					if(!wdmCreateMerchantShipByIndex(1.0, idx, &encID, at.beginlocator, at.endLocator, sti(at.TimeOut)))
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
				if(!wdmCreateMerchantShipByIndex(stf(at.speed), idx, &encID, at.beginlocator, at.endLocator, sti(at.TimeOut)))
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
				//if(!wdmCreateFollowShipByIndex(1.0, idx, &encID, at.beginlocator, sti(at.TimeOut)))
				if(!wdmCreateRealFollowShipByIndex(1.0, idx, &encID, sti(at.TimeOut)))
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
				//if(!wdmCreateFollowShipByIndex(1.0, idx, &encID, at.beginlocator, sti(at.TimeOut)))
				if(!wdmCreateRealFollowShipByIndex(1.7, idx, &encID, sti(at.TimeOut)))
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
				//wdmQuestCreateBattle(at.characterID, sti(at.iEnemyNation), sti(at.TimeOut));
			}
		}
	}

	DeleteAttribute(&worldMap, "addQuestEncounters");
	worldMap.addQuestEncounters = "";
	ReleaseMapEncounters();
}

#event_handler("WorldMap_IsSkipEnable", "wdmIsSkipEnable");
bool wdmSkipReturnBool = false;
bool wdmIsSkipEnable()
{
	wdmSkipReturnBool = false;
	if(CheckOfficersPerk(pchar, "SailingProfessional")) //to_do del
	{
		if(rand(100) <= 50)
		{
			wdmSkipReturnBool = true;
		}
	}
	return wdmSkipReturnBool;
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
	if(CheckAttribute(enc,"encdata.Task.Target") && enc.encdata.Task.Target == PLAYER_GROUP)
	{
		DeleteAttribute(pchar, "worldmap.FollowCounter");
		log_testinfo("worldmap преследователь Task Target "+enc.encdata.Task.Target+" удалён");
	}
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
			float fDeltaX = (stf(enc.x) - stf(enc.Gotox));
			float fDeltaZ = (stf(enc.z) - stf(enc.Gotoz));
			float fRadSqr = fDeltaX*fDeltaX + fDeltaZ*fDeltaZ;
			if( fRadSqr > 100.0 && stf(enc.livetime) > 1.0) 
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
	return stf(iMorale);
}

#event_handler("WorldMap_GetFood", "wdmGetFood");
float wdmGetFood()
{
	return makefloat(CalculateFood());
}

#event_handler("WorldMap_GetRum", "wdmGetRum");
float wdmGetRum()
{
	return makefloat(CalculateShipRum(pchar));
}

//  квестовый отлов входа в море по начилию НПС в случайке
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
	float WindForce = GetEventData();
	float WindAngle = GetEventData();
	
	pchar.WorldMap.WindForce = WindForce;
	pchar.WorldMap.WindAngle = WindAngle;
	
	//trace("WorldMap.WindAngle " + WindAngle + " worldMap.playerShipAY " + worldMap.playerShipAY);
}

// belamour модель корабля главного героя на глобальной карте
#event_handler("WorldMap_GetPlayerShipModel", "GetPlayerShipModel");
string GetPlayerShipModel()
{
	if(GetCharacterShipType(pchar) != SHIP_NOTUSED)
	{
		if(sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_SM) return "galeon_sm_player";
		if(sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_LADYBETH) return "shnyava_sp2_player";
		if(sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_MEMENTO) return "memento_player";
	}
	return "Ship";
}
