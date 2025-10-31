#define WDM_MAP_TO_SEA_SCALE				50
#define WDM_MAP_ENCOUNTERS_TO_SEA_SCALE		25	// boal	18.02.06 80 - это много, нужно обязательнй бой, когда догнали	// 80 VANO был тут, чисто для того чтобы корабли ближе появлялись в море, а то они на горизонте тусуются

#define WDM_NONE_ISLAND				""

#define WDM_ETYPE_MERCHANT	0
#define WDM_ETYPE_FOLLOW	1
#define WDM_ETYPE_WARRING	2
#define WDM_ETYPE_SPECIAL	3

#define THREAT_LVL_0    0
#define THREAT_LVL_1    10
#define THREAT_LVL_2    15
#define THREAT_LVL_3    20
#define THREAT_LVL_4    30
#define THREAT_LVL_5    50

object worldMap;

//=========================================================================================
//Quest functions  - Квестовые энкаунтеры. Все эвенты приходят с параметром characterID
//=========================================================================================

//военный (догоняющий). TimeOut в днях, если -1, то неиспользуеться.
//торговец - в случае успешного достижения пункта назначения придёт эвент Map_TraderSucces
void Map_CreateTrader(string beginlocator, string endLocator, string characterID, int TimeOut)  //boal
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID); //boal fix
	encField.type = "trader";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.endLocator = endLocator;
	encField.TimeOut = TimeOut; //boal
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

// boal 04/10/06
//военный (догоняющий). TimeOut в днях, если -1, то неиспользуеться.
//торговец - в случае успешного достижения пункта назначения придёт эвент Map_TraderSucces
void Map_CreateTraderXZ(float x1, float z1, float x2, float z2, string characterID, int TimeOut)  
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID); 
	encField.type = "trader";
	encField.XZGoto = true;
	encField.characterID = characterID;
	encField.x1 = x1;
	encField.z1 = z1;
	encField.x2 = x2;
	encField.z2 = z2;
	encField.TimeOut = TimeOut; //boal
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

// Jason - скоростной торговец
void Map_CreateCoolTrader(string beginlocator, string endLocator, string characterID, int TimeOut, float sp)  //boal
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID); //boal fix
	encField.type = "cooltrader";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.endLocator = endLocator;
	encField.TimeOut = TimeOut; //boal
	encField.speed = sp;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

//военный (догоняющий). TimeOut в днях, если -1, то неиспользуеться.
//При таймауте придёт эвент Map_WarriorEnd
void Map_CreateWarrior(string beginLocator, string characterID, int TimeOut)
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "warrior";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.TimeOut = TimeOut;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

//Jason Квестовый скоростной энкаунтер. Уйти от него невозможно.
void Map_CreateCoolWarrior(string beginLocator, string characterID, int TimeOut)
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "coolwarrior";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.TimeOut = TimeOut;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

//воюющий. TimeOut в днях. При таймауте придёт эвент Map_BattleEnd
//если же игрок вошел в этот энкаунтер до истечения таймаута удалиться энкоунтер из карты
void Map_CreateBattle(string characterID, int iEnemyNation, int TimeOut)
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "battle";
	encField.characterID = characterID;
	encField.iEnemyNation = iEnemyNation;
	encField.TimeOut = TimeOut;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

//Удалить квестового энкоунтера
// ~!~ TO_DO: Почему тут другим методом, нежели в wdmFindOrCreateQuestEncounter?
void Map_ReleaseQuestEncounter(string characterID)
{
    int i, num;
    aref encs, enc;

	//Просматриваем список создаваемых
	makearef(encs, worldMap.addQuestEncounters);
	num = GetAttributesNum(encs);
    for(i = 0; i < num; i++)
    {
        enc = GetAttributeN(encs, i);
        if(enc.characterID == characterID)
        {
            DeleteAttribute(enc, "characterID");
            //pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
            //break;
        }
    }

	//Просматриваем список созданных
	makearef(encs, worldMap.encounters);
	num = GetAttributesNum(encs);
	for(i = num-1; i >= 0; i--)
	{
		enc = GetAttributeN(encs, i);
		if(!CheckAttribute(enc, "quest.chrID")) continue;
		if(enc.quest.chrID == characterID)
        {
			wdmDeleteLoginEncounter(GetAttributeName(enc));
            //pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
        }
	}

	worldMap.deleteUpdate = "";
}

//=========================================================================================
//Util functions
//=========================================================================================

//Storm functions

int wdmGetNumberStorms()
{
	return MakeInt(worldMap.storm.num);
}

//Ship encounter functions

int wdmGetNumberShipEncounters()
{
	return MakeInt(worldMap.encounter.num);
}

bool wdmSetCurrentShipData(int shipIndex)
{
	worldMap.encounter.cur = shipIndex;
	int i = MakeInt(worldMap.encounter.cur);
	if(i < 0 || i != shipIndex) return 0;
	return 1;
}

//Создание энкоунтеров...

// Динамический весовой рандом
bool wdmChoseAndCreateShip()
{
	string sIslandID = worldMap.island;
	if (sIslandID != "" && !Island_IsEncountersEnable(sIslandID)) return false;

	bool  res;
	float kSpeed;

	// Развесовка
    int i, n, Summ = -1;
    for (i = 0; i < WorldMapRandomEncQty; i++) Summ += EncWeightCur[i];
    n = rand(Summ);
    for (i = 0; n >= 0; i++)
	{
		if(EncWeightCur[i] > 0) n -= EncWeightCur[i];
	}

    int  iType = i-1;
	bool bTrade = (sti(EncountersTypes[iType].Type) == ENCOUNTER_TRADE);

    if (bBettaTestMode && bGlobalVar4)
    {
        if (sti(TEV.LastEnc) != iType) bGlobalVar4 = 1;
        else bGlobalVar4++;
        TEV.LastEnc = iType;
    }

	// find free slot in dynamic encounter table for map
	int iEncounterSlot = FindFreeMapEncounterSlot();
	if (iEncounterSlot == -1) return false;
	ManualReleaseMapEncounter(iEncounterSlot);

	// find real encounter
	int iNation;
	ref rEncounter = &MapEncounters[iEncounterSlot];
	rEncounter.RealEncounterType = iType;

	// nation find
	if(iType >= ENCOUNTER_TYPE_SMUGGLERS && iType <= ENCOUNTER_TYPE_PIRATE)
	{
		iNation = PIRATE;
	}
	else
	{
		iNation = GetRandomNationForMapEncounter(sIslandID, bTrade);
		if (iNation < 0) return false;
		if (iNation == PIRATE) // ~!~
		{
			if(iType < ENCOUNTER_TYPE_SMUGGLERS || iType > ENCOUNTER_TYPE_PIRATE)
			{
				return false;
			}
		}
	}
	rEncounter.Nation = iNation;

	if (bTrade) rEncounter.Type = "trade";
    else if (iNation == PIRATE) rEncounter.Type = "pirate";
	else rEncounter.Type = "war";

	if(bTrade || GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY)
	{
		rEncounter.Task = AITASK_MOVE;
		DeleteAttribute(rEncounter, "Task.Target");
	}
	else
	{
		rEncounter.Task = AITASK_ATTACK;
		rEncounter.Task.Target = PLAYER_GROUP;
	}

	rEncounter.bUse = true;
    WME_FixShipTypes(rEncounter, 12);
    if (!GenerateMapEncounter_SetMapShipModel(rEncounter)) return false;
	rEncounter.GroupName = ENCOUNTER_GROUP + GetEncStamp();

	// Создаём энкоунтера
	string encID = "";
	if (bTrade)
	{
		kSpeed = 0.8 + rand(10)*0.03;
		res = wdmCreateMerchantShipByIndex(kSpeed, iEncounterSlot, &encID, "", "", 4+rand(4));
	}
	else
	{
        if (iNation != PIRATE) n = 3 + rand(5);
        else n = 2 + rand(4);
		kSpeed = 0.8 + rand(10)*0.05;
		res = wdmCreateFollowShipByIndex(kSpeed, iEncounterSlot, &encID, n);
	}

	// Меняем веса, если создался
	if (res)
	{
		for (i = 0; i < WorldMapRandomEncQty; i++)
		{
			if(i == iType) EncWeightCur[i] = EncWeightBase[i];
			else if (EncWeightCur[i] > 0) EncWeightCur[i]++;
		}
		
	}

	//Очищаем массив энкоунтеров
	ReleaseMapEncounters();
	return res;
}

// Специальный энкоунтер (сундук или кораблекрушенец)
bool wdmCreateSpecial(float kSpeed)
{
	//Получим описание энкоунтера в море
	int i1 = -1;
	int i2 = -1;
	//Создаём энкоунтера
	if(GenerateMapEncounter(WDM_ETYPE_SPECIAL, worldMap.island, &i1, &i2) == false) return false;
	string encID = "";
	bool res = wdmCreateSpecialByIndex(kSpeed, i1, &encID, "", "", 5+rand(5)); //boal new //homo 07/10/06
	//Очищаем массив энкоунтеров
	//Log_TestInfo("Create Special Encounter");
	ReleaseMapEncounters();
	return res;
}

//Бочонок или кораблекрушенец
bool wdmCreateSpecialByIndex(float kSpeed, int index, ref encID, string from, string to, int timeOutInDays)  // boal
{
	//Нация энкоунтера (моделька)
	string nationShipName = wdmEncounterModelName(index);
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	// boal правки в ядре -->
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); 
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = SendMessage(&worldMap, "lsssff", MSG_WORLDMAP_CREATEENC_MER, nationShipName, from, to, kSpeed, timeOutInSec);
	// boal <--
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	//Вернём идентификатор
	encID = worldMap.EncounterID1;
	return res;
}

//Торговец
bool wdmCreateMerchantShip(float kSpeed)
{
	//Получим описание энкоунтера в море
	int i1 = -1;
	int i2 = -1;
	if(GenerateMapEncounter(WDM_ETYPE_MERCHANT, worldMap.island, &i1, &i2) == false) return false;
	//Создаём энкоунтера
	string encID = "";
	bool res = wdmCreateMerchantShipByIndex(kSpeed, i1, &encID, "", "", 5+rand(5)); //boal new //homo 07/10/06
	//Очищаем массив энкоунтеров
	ReleaseMapEncounters();
	return res;
}

//Торговец
bool wdmCreateMerchantShipByIndex(float kSpeed, int index, ref encID, string from, string to, int timeOutInDays)  // boal
{
	//Нация энкоунтера (моделька)
	string nationShipName = wdmEncounterModelName(index);
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	// boal правки в ядре -->
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); 
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = SendMessage(&worldMap, "lsssff", MSG_WORLDMAP_CREATEENC_MER, nationShipName, from, to, kSpeed, timeOutInSec);
	// boal <--
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	//Вернём идентификатор
	encID = worldMap.EncounterID1;
	return res;
}
// boal 04/10/06
bool wdmCreateMerchantShipXZByIndex(float kSpeed, int index, ref encID, float x1, float z1, float x2, float z2, int timeOutInDays)  
{
	//Нация энкоунтера (моделька)
	string nationShipName = wdmEncounterModelName(index);
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); 
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = SendMessage(&worldMap, "lsffffff", MSG_WORLDMAP_CREATEENC_MER_XZ, nationShipName, x1, z1, x2, z2, kSpeed, timeOutInSec);
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	//Вернём идентификатор
	encID = worldMap.EncounterID1;
	return res;
}

//Преследователь
bool wdmCreateFollowShip(float kSpeed)
{
	//Получим описание энкоунтера в море
	int i1 = -1;
	int i2 = -1;
	if(GenerateMapEncounter(WDM_ETYPE_FOLLOW, worldMap.island, &i1, &i2) == false) return false;
	//Создаём энкоунтера
	string encID = "";
	bool res = wdmCreateFollowShipByIndex(kSpeed, i1, &encID, 5+rand(5)); //homo 07/10/06
	//Очищаем массив энкоунтеров
	ReleaseMapEncounters();
	return res;
}

//Преследователь
bool wdmCreateFollowShipByIndex(float kSpeed, int index, ref encID, int timeOutInDays)
{
	//Нация энкоунтера
	string nationShipName = wdmEncounterModelName(index);
	//проверим нацию
	ref rEnc = GetMapEncounterRef(index);
	int iNation = PIRATE;
	if(CheckAttribute(rEnc, "nation"))
	{
		iNation = sti(rEnc.Nation);
	}
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	//Время жизни в секундах
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec);
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = false;
	bool PowerCheck = (iNation == PIRATE) && wdmCompareEncPower(iNation); // Механика мощи
	if (PowerCheck || (GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY))
	{
		res = SendMessage(&worldMap, "lsssff", MSG_WORLDMAP_CREATEENC_MER, nationShipName, "", "", kSpeed, timeOutInSec);
	}
	else
	{   // boal - код этот полный абзац, я Вам, господа акеловцы, аплодирую - метод Следовать даёт убегание - и так весь код. плакаль
		// погано, что метод имеет право быть, но название должно быть иным, нужно чтоб мирные не доставали патрулями.
		res = SendMessage(&worldMap, "lsff", MSG_WORLDMAP_CREATEENC_FLW, nationShipName, kSpeed, timeOutInSec);
	}
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	encID = worldMap.EncounterID1;
	return res;
}

//Преследователь НАСТОЯЩИЙ
bool wdmCreateRealFollowShipByIndex(float kSpeed, int index, ref encID, int timeOutInDays)
{
	//Нация энкоунтера
	string nationShipName = wdmEncounterModelName(index);
	//проверим нацию
	ref rEnc = GetMapEncounterRef(index);
	int iNation = PIRATE;
	if(CheckAttribute(rEnc, "nation"))
	{
		iNation = sti(rEnc.Nation);
	}
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	//Время жизни в секундах
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); // Boal супер бага была - делили на 24. Математику в школе прогуливали?
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = false;
	/*if(GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY)
	{
		res = SendMessage(&worldMap, "lsssf", MSG_WORLDMAP_CREATEENC_MER, nationShipName, "", "", kSpeed);
	}
	else
	{ */  // boal - код этот полный абзац, я Вам, господа акеловцы, аплодирую - метод Следовать даёт убегание - и так весь код. плакаль
		res = SendMessage(&worldMap, "lsff", MSG_WORLDMAP_CREATEENC_FLW, nationShipName, kSpeed, timeOutInSec);
	//}
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	encID = worldMap.EncounterID1;
	return res;
}

//Воюющие корабли
bool wdmCreateWarringShips()
{
	//Получим описание энкоунтера в море
	int i1 = -1;
	int i2 = -1;
	if(GenerateMapEncounter(WDM_ETYPE_WARRING, worldMap.island, &i1, &i2) == false) 
	{
		ReleaseMapEncounters();
		return false;
	}
	//Создаём энкоунтера
	string encID1 = "";
	string encID2 = "";
	bool res = wdmCreateWarringShipsByIndex(i1, i2, &encID1, &encID2, 5+rand(5));  //homo 07/10/06
	//Очищаем массив энкоунтеров
	ReleaseMapEncounters();
	return res;
}

//Воюющие корабли
bool wdmCreateWarringShipsByIndex(int index1, int index2, ref encID1, ref encID2, int timeOutInDays)
{
	//Нации энкоунтера
	string nationShipName1 = wdmEncounterModelName(index1);
	string nationShipName2 = wdmEncounterModelName(index2);
	//Создадим ссылки на атрибуты
	ref mapEncSlotRef1 = GetMapEncounterRef(index1);
	ref mapEncSlotRef2 = GetMapEncounterRef(index2);
	//Время жизни в секундах
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); // Boal супер бага была - делили на 24. Математику в школе прогуливали?
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = SendMessage(&worldMap, "lssf", MSG_WORLDMAP_CREATEENC_WAR, nationShipName1, nationShipName2, timeOutInSec);
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef1, worldMap.EncounterID1);
	WdmCopyEncounterData(mapEncSlotRef2, worldMap.EncounterID2);
	encID1 = worldMap.EncounterID1;
	encID2 = worldMap.EncounterID2;
	return res;
}

//Шторм
void wdmCreateStorm()
{
    if(bEncOffGlobal) return;

	int isTornado = 0;
	if(worldMap.island == WDM_NONE_ISLAND)
	{
		int r = rand(1000);
		if(r != 0)
		{
			if(r < 450)
			{
				isTornado = 1;
			}
		}
	}
	// тест торнадор
	isTornado = 1;
	// конец теста
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_CREATESTORM, isTornado);
}

//Получить модельку кораблика по индексу нации
string wdmEncounterModelName(int encIndex)
{
	ref rEnc = GetMapEncounterRef(encIndex);
	if(CheckAttribute(rEnc, "worldMapShip") != 0)
	{
		return rEnc.worldMapShip;
	}
	return "ship";
}

//Скопировать данные об энкоутере
void WdmCopyEncounterData(ref mapEncSlotRef, string encStringID)
{
	encStringID = "encounters." + encStringID + ".encdata";
	worldMap.(encStringID) = "";
	aref destRef;
	makearef(destRef, worldMap.(encStringID));
	CopyAttributes(destRef, mapEncSlotRef);
}

//Зарезервировать место для добавления нового энкоунтера
aref wdmCreateNewQuestEncDescription()
{
	aref encs;
	makearef(encs, worldMap.addQuestEncounters);
    string attr = "QEnc" + (GetAttributesNum(encs)+1);
    while(CheckAttribute(encs, attr)) attr += "_a";
	makearef(encs, worldMap.addQuestEncounters.(attr));
	return encs;
}

// boal
void wdmEmptyAllDeadQuestEncounter()
{
    int  i, iChar, num;
    aref encs, enc;
	bool isWMap = IsEntity(&worldMap);

    makearef(encs, worldMap.encounters);
    num = GetAttributesNum(encs);
    for(i = num-1; i >= 0; i--)
    {
        enc = GetAttributeN(encs, i);
        DeleteAttribute(enc, "dirSailEnc");
        if(CheckAttribute(enc, "quest.chrID"))
        {
            iChar = GetCharacterIndex(enc.quest.chrID)
            if (iChar == -1 || CharacterIsDead(&characters[iChar]))
            {
	            if (!isWMap)
				{
					DeleteAttribute(encs, GetAttributeName(enc));
	                pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	            }
	            else
	            {
	            	enc.livetime = 0;
	            }
	        }
        }
    }

   	makearef(encs, worldMap.addQuestEncounters);
    num = GetAttributesNum(encs);
	for(i = num-1; i >= 0; i--)
	{
		enc = GetAttributeN(encs, i);
		if (CheckAttribute(enc, "characterID"))
		{
	        iChar = GetCharacterIndex(enc.characterID);
	        if (iChar == -1 || CharacterIsDead(&characters[iChar]))
	        {
	            DeleteAttribute(encs, GetAttributeName(enc));
	            pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	        }
        }
    }
}

// чистка энкоутеров на карте
void  wdmEmptyAllOldEncounter()
{
    int  i, num;
    aref encs, enc;
	bool isWMap = IsEntity(&worldMap); // ???

    makearef(encs, worldMap.encounters);
    num = GetAttributesNum(encs);
    for(i = num-1; i >= 0; i--)
    {
        enc = GetAttributeN(encs, i);
        if(CheckAttribute(enc, "needDelete") && enc.needDelete == "wdmEncounterDelete")
        {
			if(CheckAttribute(enc, "quest")) // ???
                pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
			DeleteAttribute(encs, GetAttributeName(enc));
        }
    }
}
// время жизни на карте для квестовых энкоутеров
void  wdmUpdateAllEncounterLivetime()
{
    int ihours, i, num;
    aref encs, enc;
    string sChar, sEvent;
    //float b,k;

    if(!actLoadFlag)
    {
		ihours = GetQuestPastTimeParam("WordMapEncounters_DailyUpdate");
		if (ihours > 0)
		{
            Log_TestInfo("Прошло дней : "+makeint(ihours/24.0));
            float timeOutInSec = ihours/stf(worldMap.date.hourPerSec);

            makearef(encs, worldMap.encounters);
            num = GetAttributesNum(encs);
            for (i = num-1; i >= 0; i--)
            {
                enc = GetAttributeN(encs, i);
                if (CheckAttribute(enc, "livetime") && CheckAttribute(enc, "quest"))
                {
                    Log_TestInfo(enc.livetime+" - "+timeOutInSec+" : "+stf(stf(enc.livetime) - timeOutInSec));
                    /* По идее можно и координату приращивтаь, чтоб не просто время шло, но ещё и плыли.
                    k = (enc.gotoz - enc.z)/(enc.gotox - enc.x);
                    b = enc.z - k*enc.x
                    ...
                    */
                    enc.livetime = stf(enc.livetime) - timeOutInSec;

                    if (sti(enc.livetime)<=0)
                    {
                        sEvent = enc.quest.event; // TO_DO: REF
                        sChar  = enc.quest.chrID;
                        DeleteAttribute(encs,  GetAttributeName(enc));
						pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
						if(sEvent == "Map_TraderSucces")    Map_TraderSucces_quest(sChar); // belamour теперь запустим обработку нпс-кэпов
                        else if(sEvent == "Map_WarriorEnd") Map_WarriorEnd_quest(sChar);
                    }
                }
            }
		}
	}
}

// найти сущ случайку для НПС
// ~!~ TO_DO: Почему тут другим методом, нежели в Map_ReleaseQuestEncounter?
aref wdmFindOrCreateQuestEncounter(string _chrId)
{
    int i, num, iChar;
    aref encs, enc;
	bool isWMap = IsEntity(&worldMap);

    //Просматриваем список создаваемых
   	makearef(encs, worldMap.addQuestEncounters);
    num = GetAttributesNum(encs);
	for(i = num-1; i >= 0; i--)
	{
		enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "characterID"))
		{
	        iChar = GetCharacterIndex(enc.characterID);
	        if(iChar == -1 || characters[iChar].id == _chrId)
	        {
	            DeleteAttribute(encs, GetAttributeName(enc));
	            pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	        }
        }
    }

    //Просматриваем список созданных
    makearef(encs, worldMap.encounters);
    num = GetAttributesNum(encs);
    for(i = num-1; i >= 0; i--)
    {
        enc = GetAttributeN(encs, i);
        if(CheckAttribute(enc, "quest.chrID"))
        {
            iChar = GetCharacterIndex(enc.quest.chrID)
            if(iChar == -1 || characters[iChar].id == _chrId)
            {
	            if(!isWMap)
				{
					DeleteAttribute(encs, GetAttributeName(enc));
	                pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	            }
	            else
	            {
	            	enc.livetime = 0;
	            }
	        }
        }
    }

	return wdmCreateNewQuestEncDescription();
}

void wdmShowInterface(bool showUI)
{
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_WIND_UI_SET_SHOW, showUI);
}

// Механика мощи
bool wdmCompareEncPower(int iNation) //(ref rEnc)
{
    /*
    if(!CheckAttribute(rEnc, "Power")) return false;
    float encPow = stf(rEnc.Power);
    float pchPow = stf(PChar.Squadron.ModPower);
    return (pchPow > encPow);
    */

    return (stf(PChar.Squadron.ModPower) > wdmGetPowerThreshold(iNation));
    
}

int GetBattleDifficulty(ref rEnc)
{
    float encPow = 0.0;
    float pchPow = stf(PChar.Squadron.RawPower);
    if(CheckAttribute(rEnc, "CharacterID"))
    {
        string sTemp;
        ref chr = CharacterFromID(rEnc.CharacterID);
        if(CheckAttribute(chr, "SeaAI.Group.Name"))
            sTemp = chr.SeaAI.Group.Name;
        else return 0;	// XI_ConvertString("Unknown dif");
        encPow = CalculateGroupPower(sTemp);
        if (encPow == -1.0) return 0;
        rEnc.CurPower = encPow;
    }
    else
    {
        if(!CheckAttribute(rEnc, "Power")) return 0;	// XI_ConvertString("Unknown dif"); // TO_DO: DEL
        encPow = stf(rEnc.Power);
    }
    if(pchPow == 0.0)
    {
        if(encPow == 0.0) return 3;	// XI_ConvertString("Medium dif");
        return 5;	// XI_ConvertString("Fatal dif");
    }

    float fRatio = (encPow * 0.9) / pchPow;

    if(fRatio >= 1.7)  return 5;	// XI_ConvertString("Fatal dif");    // +70% и выше
    if(fRatio > 1.35)  return 4;	// XI_ConvertString("High dif");     // +36% до +69%
    if(fRatio >= 0.65) return 3;	// XI_ConvertString("Medium dif");   // -35% до +35%
    if(fRatio >= 0.31) return 2;	// XI_ConvertString("Low dif");      // -69% до -36%
    return 1;	// XI_ConvertString("Elementary dif");                  // -70% и ниже
}

// Получить суммарный уровень угрозы от пиратов и наций
int wdmGetSummaryThreat()
{
	int result = 0;
	for (int j=0; j< MAX_NATIONS; j++)
	{
		result += wdmGetNationThreat(j);
	}
	return result;
}

// iGP - int Global Pirate
int iGPThreat = 0;
int iGPThreatMax = THREAT_LVL_1;
int iGPThreatRate = 0;
int wdmGetNationThreat(int iNation)
{
	if(iNation == PIRATE)
        return iGPThreat;

	int iRel = ChangeCharacterNationReputation(PChar, iNation, 0);
	if (iRel > -THREAT_LVL_1)     return 0;
	else if(iRel > -THREAT_LVL_2) return 1;
	else if(iRel > -THREAT_LVL_3) return 2;
	else if(iRel > -THREAT_LVL_4) return 3;
	else if(iRel > -THREAT_LVL_5) return 4;
	else                          return 5;
}

int wdmGetPowerThreshold(int iNation)
{
    int iThreat = wdmGetNationThreat(iNation);
    if(iThreat == 0) return -1;
    if(iThreat == 1) return 200;
    if(iThreat == 2) return 325;
    if(iThreat == 3) return 475;
    if(iThreat == 4) return 675;
    if(iThreat == 5) return 925;
}

float CalculateGroupPower(string sGroup)
{
    int	iGroupIndex = Group_FindGroup(sGroup);
    if (iGroupIndex < 0)
        return -1.0;

    ref rGroup = Group_GetGroupByIndex(iGroupIndex);
    if (!CheckAttribute(rGroup, "Quest"))
        return -1.0;

    return CalculateGroupPowerR(rGroup);
}

float CalculateGroupPowerR(ref rGroup)
{
    float encPow = 0.0;
    aref aCompanions, aCharInfo;
    makearef(aCompanions, rGroup.Quest);
    int qty = GetAttributesNum(aCompanions);

    ref rChar, rShip;
    int iShipType, idx;
    for(int i = 0; i < qty; i++)
    {
        aCharInfo = GetAttributeN(aCompanions, i);
        idx = sti(aCharInfo.index);
        if(idx == -1) continue;
        rChar = GetCharacter(idx);
        if(LAi_IsDead(rChar)) continue;
        iShipType = sti(rChar.Ship.Type);
        if(iShipType == SHIP_NOTUSED) continue;
        rShip = GetRealShip(iShipType);
        encPow += GetRealShipPower(rChar);
    }

    return encPow;
}

bool bFreezePirateThreat = false;
void RaisePirateThreat()
{
    // Квестовые ситуативные фризы
    if (bFreezePirateThreat)
        return;
    // Суточный инкремент
    iGPThreatRate++;
    // Проверяем взятие порога
    bool bThreshold = (iGPThreatRate == THREAT_LVL_1) || (iGPThreatRate == THREAT_LVL_2) ||
                      (iGPThreatRate == THREAT_LVL_3) || (iGPThreatRate == THREAT_LVL_4) ||
                      (iGPThreatRate == THREAT_LVL_5);
    if (bThreshold)
    {
        int iCurThreat;
        switch (iGPThreatRate)
        {
            case THREAT_LVL_1: iCurThreat = 1; break;
            case THREAT_LVL_2: iCurThreat = 2; break;
            case THREAT_LVL_3: iCurThreat = 3; break;
            case THREAT_LVL_4: iCurThreat = 4; break;
            case THREAT_LVL_5: iCurThreat = 5; break;
        }
        if (iGPThreat != iCurThreat)
        {
            iGPThreat = iCurThreat;
            PiratesIncreaseNotif("");
        }
    }
    // Клампим   
    if (iGPThreatRate > iGPThreatMax)
        iGPThreatRate = iGPThreatMax;
}

void ChangePirateThreat(int add)
{
    iGPThreatRate = iClamp(0, iGPThreatMax, iGPThreatRate + add);

    int iCurThreat;
    // Для понижения нужно уйти до предыдущего порога или ниже
    if (add < 0)
    {
        if (iGPThreatRate == THREAT_LVL_0)      iCurThreat = 0;
        else if (iGPThreatRate <= THREAT_LVL_1) iCurThreat = 1;
        else if (iGPThreatRate <= THREAT_LVL_2) iCurThreat = 2;
        else if (iGPThreatRate <= THREAT_LVL_3) iCurThreat = 3;
        else if (iGPThreatRate <= THREAT_LVL_4) iCurThreat = 4;
        else                                    iCurThreat = 5;

        if (iGPThreat > iCurThreat)
        {
            iGPThreat = iCurThreat;
            SetFunctionMapEnterCondition("PiratesDecreaseNotif", false);
        }
        return;
    }

    // Для повышения достаточно перейти за порог
    // (но пока что повышений вне ежесуточного апдейтера не предполагается)
    if (iGPThreatRate < THREAT_LVL_1)      iCurThreat = 0;
    else if (iGPThreatRate < THREAT_LVL_2) iCurThreat = 1;
    else if (iGPThreatRate < THREAT_LVL_3) iCurThreat = 2;
    else if (iGPThreatRate < THREAT_LVL_4) iCurThreat = 3;
    else if (iGPThreatRate < THREAT_LVL_5) iCurThreat = 4;
    else                                   iCurThreat = 5;

    if (iGPThreat < iCurThreat)
    {
        iGPThreat = iCurThreat;
        SetFunctionMapEnterCondition("PiratesIncreaseNotif", false);
    }
}
