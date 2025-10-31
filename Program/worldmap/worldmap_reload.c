
object wdmLoginToSea;
object wdm_fader;
bool wdmLockRelease = false;
bool wdmLockReload = false;
bool questwdmLockReload = false;

void wdmReloadToSea()
{
	//Если запрещена перегрузка, ничего не делаем
	if(wdmLockReload)
	{
		return;
	}
	if(questwdmLockReload)
	{
		Log_Info(XI_ConvertString("questwdmLock"));
		return;
	}
	// расчеты ВМЛ -->
	EmptyAllFantomCharacter();
	PGG_DailyUpdate();
	Siege_DailyUpdate();//homo осады 05/11/06
	SaveCurrentQuestDateParam("WordMapEncounters_DailyUpdate"); //homo карта 25/03/07
	// расчеты <--
	
	wdmLockReload = true;
	//Обновим текст перегрузки
	SetReloadNextTipsImage();
	//Очищаем объект логина
	DeleteAttribute(&wdmLoginToSea, "");
	//Обновляем параметры
	worldMap.encounter.type = "";
	worldMap.playerShipUpdate = "";
	worldMap.info.updateinfo = "";
	//Добавляем группу игрока
	WdmAddPlayerGroup();
	//Добавляем энкаунтеры
	bool isShipEncounterType;
	isShipEncounterType = WdmAddEncountersData();
	//Отконектим все энкаунтеры от атрибутов и поставим в очередь удаления
	SendMessage(&worldMap, "l", MSG_WORLDMAP_CREATEENC_RELEASE);
	//Погодные эффекты
	WdmStormEncounter();
	//Удаляем атрибуты выделенных энкаунтеров
	worldMap.deleteUpdate = "";
	
	//  AutoSave boal 17.04.24 -->
	if (sti(wdmLoginToSea.storm) == 0 && !isShipEncounterType && MakeAutoSave2()) // не в шторме, не в бою
	{
		SetEventHandler("evntSaveGameAfter","WdmReloadAferSave", 0);
	}
	else
	{
		WdmReloadStart(isShipEncounterType);
	}
	//  AutoSave boal 17.04.24 <--
	
	
}
//  AutoSave boal 17.04.24 -->
void WdmReloadAferSave()
{
	DelEventHandler("evntSaveGameAfter","WdmReloadAferSave"); // убрать прерывание
	WdmReloadStart(false); // то, что было бы сразу
}
void WdmReloadStart(bool isShipEncounterType)
{
	//Фейдер
	SetEventHandler("FaderEvent_StartFade", "WdmStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "WdmEndFade", 0);
	wdm_fader.thisWorldMapFader = "";
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeOutTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
	SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
	//Установим картинку для фейдера
	string imageName = "loading\sea_0" + rand(2) + ".tga";
	if(isShipEncounterType)
	{
		imageName = RandPhraseSimple("loading\battle.tga", "loading\shipcannon.tga"));
	}
	if(MakeInt(wdmLoginToSea.storm) != 0)
	{
		imageName = "loading\Storm.tga";
		/*if(MakeInt(wdmLoginToSea.tornado) != 0)
		{
			imageName = "loading\Twister.tga";
		}*/ // boal пусть будет одна
	}
	wdmLoginToSea.imageName = imageName;
	SendMessage(&wdm_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&wdm_fader, "ls",FADER_PICTURE, imageName);
}
//  AutoSave boal 17.04.24 <--
void WdmStartFade()
{
	PauseAllSounds();
	//Delete EventHandler
	DelEventHandler("FaderEvent_StartFade", "WdmStartFade");
	//Delete entity
	worldMap.playerShipUpdate = "";
	DeleteClass(&worldMap);
	worldMap.isLoaded = "false";
	DeleteWmInterface();
}

void WdmEndFade()
{
	int a = GetEventData();
	aref reload_fader = GetEventData();
	//Delete EventHandler
	DelEventHandler("FaderEvent_EndFade", "WdmEndFade");
	//Switch to sea
	ReloadProgressStart();	
	sIslandID = worldMap.island;
	SeaLogin(&wdmLoginToSea);
	LayerAddObject(SEA_REALIZE, &reload_fader, -1);
	ReloadProgressEnd();
}

void QuitFromWorldMap()
{
	//Fade out
	SetEventHandler("FaderEvent_StartFade", "WdmStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "WdmEndFadeA", 0);
	wdm_fader.thisWorldMapFader = "";
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeOutTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
	SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
}

void WdmEndFadeA()
{
	//Delete EventHandler
	DelEventHandler("FaderEvent_EndFade", "WdmEndFadeA");
	//Switch to sea
	Event("QuitFromWorldMap");

}

// VANO function: return sea coordinates
void WdmPrepareMapForAbordage(aref arPos)
{
	//Координаты игрока на карте
	float psX = MakeFloat(worldMap.playerShipX);
	float psZ = MakeFloat(worldMap.playerShipZ);
	//Учитываем остров
	if(worldMap.island != WDM_NONE_ISLAND)
	{
		//Island
		wdmLoginToSea.island = worldMap.island;
		float ix = MakeFloat(worldMap.island.x);
		float iz = MakeFloat(worldMap.island.z);
		int scale = WDM_MAP_TO_SEA_SCALE;
		if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina"
			|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo"
			|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
		{
			scale = 25;
		}
		arPos.x = (psX - ix)*scale;
		arPos.z = (psZ - iz)*scale;
		arPos.y = worldMap.playerShipAY;
		worldMap.zeroX = ix;
		worldMap.zeroZ = iz;
	}else{
		//no Island
		wdmLoginToSea.island = "";
		//Player ship
		arPos.x = 0;
		arPos.z = 0;
		arPos.y = worldMap.playerShipAY;
		worldMap.zeroX = worldMap.playerShipX;
		worldMap.zeroZ = worldMap.playerShipZ;
	}
}

void WdmAddPlayerGroup()
{
	//Координаты игрока на карте
	float psX = MakeFloat(worldMap.playerShipX);
	float psZ = MakeFloat(worldMap.playerShipZ);
	//if (CheckAttribute(pchar, "questTemp.Sharlie.Sea"))//Jason
	//{
	//	psX = 600.524;
	//	psZ = -500.507;
	//}
	//Учитываем остров
	if(worldMap.island != WDM_NONE_ISLAND)
	{
		//Island
		wdmLoginToSea.island = worldMap.island;
		float ix = MakeFloat(worldMap.island.x);
		float iz = MakeFloat(worldMap.island.z);
		int scale = WDM_MAP_TO_SEA_SCALE;
		if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina"
			|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo" 
			|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
		{
			scale = 25;
		}
		wdmLoginToSea.playerGroup.x = (psX - ix)*scale;
		wdmLoginToSea.playerGroup.z = (psZ - iz)*scale;
		wdmLoginToSea.playerGroup.ay = worldMap.playerShipAY;
		worldMap.zeroX = ix;
		worldMap.zeroZ = iz;
	}else{
		//no Island
		wdmLoginToSea.island = "";
		//Player ship
		wdmLoginToSea.playerGroup.x = 0;
		wdmLoginToSea.playerGroup.z = 0;
		wdmLoginToSea.playerGroup.ay = worldMap.playerShipAY;
		worldMap.zeroX = worldMap.playerShipX;
		worldMap.zeroZ = worldMap.playerShipZ;
	}
}

bool WdmAddEncountersData()
{
	bool isShipEncounter = false;

	//Удалим все существующие записи об морских энкоунтерах
	ReleaseMapEncounters();

	//Количество корабельных энкоунтеров в карте
	int i, j, idx;
    int numShips = 0;
    for(i = 0; i < COMPANION_MAX; i++)
    {
        idx = GetCompanionIndex(PChar, i);
        if (idx != -1) numShips++;
    }
	int numEncounters = wdmGetNumberShipEncounters();

    int  iPlayer = SendMessage(&worldMap, "l", MSG_GET_PLAYERSHIP_IDX);
    int  iMapTarget = -1;
    int  iSort[2];
    bool bSort[2];

    if (CheckAttribute(&TEV, "iTarget"))
    {
        iMapTarget = sti(TEV.iTarget);
        DeleteAttribute(&TEV, "iTarget");
        if (iMapTarget >= 0)
        {
            idx = 1;
            iSort[0] = iMapTarget; // Здесь он уже откалиброван
        }
        else idx = 0;
    }
    else idx = 0;

    if (numEncounters > 0)
    {
        SetArraySize(&iSort, numEncounters);
        SetArraySize(&bSort, numEncounters);
        j = 0;
        int numEncountersReal = numEncounters + (iPlayer != -1);
        // В этом цикле скипаем игрока
        for (i = 0; i < numEncountersReal; i++)
        {
            if (i == iPlayer) continue;

            bSort[j] = SendMessage(&worldMap, "ll", MSG_WORLDMAP_IS_ENEMY, i);
            if (j != iMapTarget && bSort[j])
            {
                iSort[idx] = j;
                idx++;
            }
            j++;
        }
        // В предыдущем уже скипали, поэтому здесь сразу проверяем
        for (i = 0; i < numEncounters; i++)
        {
            if (i != iMapTarget && !bSort[i])
            {
                iSort[idx] = i;
                idx++;
            }
        }
    }

	//Позиция игрока на карте
	float mpsX = MakeFloat(worldMap.playerShipX);
	float mpsZ = MakeFloat(worldMap.playerShipZ);
	//Позиция игрока в мире
	float wpsX = MakeFloat(wdmLoginToSea.playerGroup.x);
	float wpsZ = MakeFloat(wdmLoginToSea.playerGroup.z);
    // Участники катавасии
    bool PickedByPlayer = false;
    string grp, attr;
    int numLoadEnc = 0;
    object LoadEnc;

	//Перебираем все энкоунтеры карты
	for(i = 0; i < numEncounters; i++)
	{
		//Получим информацию о данном энкоунтере
        if(numShips >= MAX_SHIPS_LOAD_FROM_WDM) break;
		if(wdmSetCurrentShipData(iSort[i]))
		{
			//Если не активен, то пропустим его
			if(MakeInt(worldMap.encounter.select) == 0) continue;
			//Добавляем информацию об морских энкоунтере
			string encStringID = worldMap.encounter.id;
			if(encStringID == "") continue;
			encStringID = "encounters." + encStringID + ".encdata";
			if(!CheckAttribute(&worldMap, encStringID)) continue;
			int mapEncSlot = FindFreeMapEncounterSlot();
			if(mapEncSlot < 0) continue;
			ref mapEncSlotRef = GetMapEncounterRef(mapEncSlot);

            bool bTaskLock;
			aref encDataForSlot;
			makearef(encDataForSlot, worldMap.(encStringID));
			if (CheckAttribute(encDataForSlot, "CharacterID"))
			{
                idx = GetCharacterIndex(encDataForSlot.CharacterID);
                if (idx != -1 && CheckAttribute(&Characters[idx], "SeaAI.Group.Name"))
                {
                    grp = Characters[idx].SeaAI.Group.Name;
                    ref rGroup = Group_FindOrCreateGroup(grp);
                    numShips += Group_GetLiveCharactersNumR(rGroup);
                    bTaskLock = Group_CheckTaskLockR(rGroup);
                    attr = "e" + numLoadEnc;
                    LoadEnc.(attr).x = worldMap.encounter.x;
                    LoadEnc.(attr).z = worldMap.encounter.z;
                    LoadEnc.(attr).type  = encDataForSlot.type;
                    LoadEnc.(attr).Power = CalculateGroupPowerR(rGroup);
                    LoadEnc.(attr).slot  = mapEncSlot;
                    LoadEnc.(attr).group = grp;
                    LoadEnc.(attr).nation = encDataForSlot.nation;
                    if (CheckAttribute(&Characters[idx], "AlwaysEnemy"))
                        LoadEnc.(attr).rel = "1";
                    else if (CheckAttribute(&Characters[idx], "AlwaysFriend"))
                        LoadEnc.(attr).rel = "2";
                    else
                        LoadEnc.(attr).rel = "0";
                    if (!PickedByPlayer && Group_CheckAttackPlayerR(rGroup))
                    {   // Только единожды группе, атакующей игрока, сразу ставится
                        // picked, то есть считаем, что она пикнута игроком
                        LoadEnc.(attr).picked = "1";
                        PickedByPlayer = true;
                        // playerPicked не ставится, иначе халява какая-то
                    }
                    else LoadEnc.(attr).picked = "0";
                    LoadEnc.(attr).havetask = bTaskLock;
                    numLoadEnc++;
                }
			}
            else
            {
                if (encDataForSlot.type != "special")
                {
                    bTaskLock = CheckAttribute(encDataForSlot, "Lock");
                    attr = "e" + numLoadEnc;
                    LoadEnc.(attr).x = worldMap.encounter.x;
                    LoadEnc.(attr).z = worldMap.encounter.z;
                    LoadEnc.(attr).type  = encDataForSlot.type;
                    LoadEnc.(attr).Power = encDataForSlot.Power;
                    LoadEnc.(attr).slot  = mapEncSlot;
                    LoadEnc.(attr).group = encDataForSlot.GroupName;
                    LoadEnc.(attr).nation = encDataForSlot.nation;
                    LoadEnc.(attr).picked   = bTaskLock; // "1" у сражений
                    LoadEnc.(attr).havetask = bTaskLock;
                    LoadEnc.(attr).rel = "0";
                    numLoadEnc++;
                }
                if (CheckAttribute(encDataForSlot, "NumMerchantShips"))
                    numShips += sti(encDataForSlot.NumMerchantShips);
                if (CheckAttribute(encDataForSlot, "NumWarShips"))
                    numShips += sti(encDataForSlot.NumWarShips);
            }

			CopyAttributes(mapEncSlotRef, encDataForSlot);
			//Отмечаем свершение корабельного энкоунтера
			isShipEncounter = true;
			//Описываем его параметры
			grp = "group" + i;
			float encX = MakeFloat(worldMap.encounter.x);
			float encZ = MakeFloat(worldMap.encounter.z);
			wdmLoginToSea.encounters.(grp).x = wpsX + (encX - mpsX)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).z = wpsZ + (encZ - mpsZ)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).deltax = (encX - mpsX)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).deltaz = (encZ - mpsZ)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).ay = worldMap.encounter.ay;
            // Fix. Не чистим массив, пока не выгузит корабли -->
			wdmLoginToSea.encounters.(grp).type = mapEncSlot;
            wdmLockRelease = true;
            // <-- Fix
			wdmLoginToSea.encounters.(grp).id = worldMap.encounter.id;
			// Помечаем энку на удаление
			encStringID = worldMap.encounter.id;
			encStringID = "encounters." + encStringID;
			if(CheckAttribute(&worldMap, encStringID + ".quest") == 0)
			{
				worldMap.(encStringID).needDelete = "Reload delete fantom encounter";
			}
		}
	}

    if(!GetAchievement("ach_CL_194") && numLoadEnc > 4)
        Achievment_Set("ach_CL_194");

    // Катавасия
    object enemies;
    bool  playerPicked = false;
    float pchPow = stf(PChar.Squadron.RawPower);
    for (i = 0; i < numLoadEnc; i++)
    {
        aref CurEnc = GetAttributeN(&LoadEnc, i);
        if (CurEnc.havetask == "1") continue;
        // Посмотрим на ближайшего
        DeleteAttribute(&enemies, "");
        bool HaveEnemy = false;
        int iEnemy = -1;
        float dist;
        float minD = -1.0;
        idx  = sti(CurEnc.nation);
		encX = stf(CurEnc.x);
		encZ = stf(CurEnc.z);
        if (or(GetNationRelation2MainCharacter(idx) == RELATION_ENEMY, CurEnc.rel == "1") && CurEnc.rel != "2")
        {
            attr = "-2";
            enemies.(attr) = "";
            HaveEnemy = true;
            if (!playerPicked)
            {
                iEnemy = -2; // Игрок
                minD = GetDistance2DRel(mpsX, mpsZ, encX, encZ);
            }
        }
        for (j = 0; j < numLoadEnc; j++)
        {
            if (j == i) continue;
            aref CurEnemy = GetAttributeN(&LoadEnc, j);
            if (GetNationRelation(idx, sti(CurEnemy.nation)) != RELATION_ENEMY) continue;
            HaveEnemy = true;
            attr = j;
            enemies.(attr) = "";
            if (CurEnemy.picked == "1") continue;
            dist = GetDistance2DRel(stf(CurEnemy.x), stf(CurEnemy.x), encX, encZ);
            if (dist > minD && minD != -1.0) continue;
            else
            {
                iEnemy = j;
                minD = dist;
            }
        }
        // Враги есть, но все заняты, берём случайного
        if (iEnemy == -1 && HaveEnemy)
            iEnemy = sti(GetAttributeName(GetAttributeN(&enemies, hrand(GetAttributesNum(&enemies)-1, CurEnc.group))));
        // Нашёлся враг
        if (iEnemy != -1)
        {
            bool MorePower;
            if (iEnemy == -2)
                MorePower = (stf(CurEnc.Power) > pchPow);
            else
            {
                CurEnemy = GetAttributeN(&LoadEnc, iEnemy);
                MorePower = (stf(CurEnc.Power) > stf(CurEnemy.Power));
            }
            if (MorePower || CurEnc.type != "trade")
            {
                // Атаковать
                CurEnc.havetask = "1";
                if (iEnemy == -2)
                {
                    if (!PickedByPlayer)
                    {
                        CurEnc.picked = "1";
                        PickedByPlayer = true;
                    }
                    playerPicked = true;
                    grp = PLAYER_GROUP;
                }
                else
                {
                    CurEnemy.picked = "1";
                    grp = CurEnemy.group;
                }
                mapEncSlotRef = GetMapEncounterRef(sti(CurEnc.slot));
                mapEncSlotRef.Katavasia = "";
                mapEncSlotRef.Task = AITASK_ATTACK;
                mapEncSlotRef.Task.Target = grp;
                if (iEnemy != -2 && CurEnemy.havetask == "0")
                {
                    grp = CurEnc.group;
                    mapEncSlotRef = GetMapEncounterRef(sti(CurEnemy.slot));
                    if (!MorePower)
                    {   // Вызов принят
                        CurEnc.picked = "1";
                        CurEnemy.havetask = "1";
                        mapEncSlotRef.Katavasia = "";
                        mapEncSlotRef.Task = AITASK_ATTACK;
                        mapEncSlotRef.Task.Target = grp;
                    }
                    else if (CurEnemy.type == "trade" && hrand(1, grp))
                    {   // Будет убегать
                        CurEnemy.havetask = "1";
                        mapEncSlotRef.Katavasia = "";
                        mapEncSlotRef.Task = AITASK_RUNAWAY;
                        mapEncSlotRef.Task.Target = grp;
                    }
                }
            }
        }
    }

	return isShipEncounter;
}

void WdmStormEncounter()
{
	wdmLoginToSea.storm = worldMap.playerInStorm;
	if(MakeInt(wdmLoginToSea.storm) != 0)
	{
		wdmLoginToSea.tornado = worldMap.stormWhithTornado;
	}else{
		wdmLoginToSea.tornado = "0";
	}

	//wdmLoginToSea.tornado = "1";

	if(CheckAttribute(&worldMap, "stormId") != 0)
	{
		if(worldMap.stormId != "")
		{
			string encStringID = worldMap.stormId;
			encStringID = "encounters." + encStringID;
			worldMap.(encStringID).needDelete = "Reload delete storm";
		}
	}	
}