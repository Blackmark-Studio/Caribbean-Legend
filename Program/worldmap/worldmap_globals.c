#define WDM_MAP_TO_SEA_SCALE				50
#define WDM_MAP_ENCOUNTERS_TO_SEA_SCALE		25	// boal	18.02.06 80 - это много, нужно обязательнй бой, когда догнали	// 80 VANO был тут, чисто для того чтобы корабли ближе появлялись в море, а то они на горизонте тусуются

#define WDM_NONE_ISLAND				""

#define WDM_ETYPE_MERCHANT	0
#define WDM_ETYPE_FOLLOW	1
#define WDM_ETYPE_WARRING	2
#define WDM_ETYPE_SPECIAL	3

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
    if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
	{  // boal убиралка шторма
		if(sti(pchar.worldmapencountersoff)) return;
	}
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

string GetBattleDifficulty(ref rEnc)
{
    float encPow = 0.0;
    float pchPow = stf(PChar.Squadron.RawPower);
    if(CheckAttribute(rEnc, "CharacterID"))
    {
        string sTemp;
        ref chr = CharacterFromID(rEnc.CharacterID);
        if(CheckAttribute(chr, "SeaAI.Group.Name"))
            sTemp = chr.SeaAI.Group.Name;
        else 
            return XI_ConvertString("Unknown dif");

        // ВАЖНО: МЫ НИГДЕ НЕ НАЗНАЧАЕМ КОМПАНЬОНОВ СЕЙЧАС
        // ДЛЯ NPC ТОЛЬКО ГРУППЫ

        int	iGroupIndex = Group_FindGroup(sTemp);
        if (iGroupIndex < 0)
        {
            Log_TestInfo("НЕТ ГРУППЫ В GetBattleDifficulty");
            trace("НЕТ ГРУППЫ В GetBattleDifficulty");
            return XI_ConvertString("Unknown dif");
        }

        ref rGroup = Group_GetGroupByIndex(iGroupIndex);
        if (!CheckAttribute(rGroup, "Quest")) return XI_ConvertString("Unknown dif");

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
    		if(!CheckAttribute(rChar, "index") || rChar.index == "none" || LAi_IsDead(rChar)) continue;
            iShipType = sti(rChar.Ship.Type);
            if(iShipType == SHIP_NOTUSED) continue;
            rShip = GetRealShip(iShipType);
            encPow += GetRealShipPower(rChar);
        }

        rEnc.CurPower = encPow;
    }
    else
    {
        if(!CheckAttribute(rEnc, "Power")) return XI_ConvertString("Unknown dif"); // TO_DO: DEL
        encPow = stf(rEnc.Power);
    }
    if(pchPow == 0.0)
    {
        if(encPow == 0.0) return XI_ConvertString("Medium dif");
        return XI_ConvertString("Fatal dif");
    }

    float fRatio = (encPow * 0.9) / pchPow;

    if(fRatio >= 1.7)  return XI_ConvertString("Fatal dif");    // +70% и выше
    if(fRatio > 1.35)  return XI_ConvertString("High dif");     // +36% до +69%
    if(fRatio >= 0.65) return XI_ConvertString("Medium dif");   // -35% до +35%
    if(fRatio >= 0.31) return XI_ConvertString("Low dif");      // -69% до -36%
    return XI_ConvertString("Elementary dif");                  // -70% и ниже
}

int wdmGetNationThreat(int iNation)
{
	if(iNation == PIRATE)
	{
		int iRank = sti(pchar.rank);
		if(iRank <= 8)       return 1;
		else if(iRank <= 16) return 2;
		else if(iRank <= 25) return 3;
		else if(iRank <= 30) return 4;
		else                 return 5;
	}

	int iRel = ChangeCharacterNationReputation(PChar, iNation, 0);
	if (iRel > -10)     return 0;
	else if(iRel > -15) return 1;
	else if(iRel > -20) return 2;
	else if(iRel > -30) return 3;
	else if(iRel > -50) return 4;
	else                return 5;
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
