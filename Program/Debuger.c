// BOAL нажатие на F12 вызывает этот код. Его можно править с alt-tab в игре, изменения будут сразу
//native string GetHello();
//#libriary "b_engine"

void ActiveINSERTControl()
{
    //DoReloadCharacterToLocation(Pchar.location, "goto", "goto2");
    //DoReloadCharacterToLocation("PlutoStoreSmall", "reload", "reload1");
	//DoReloadCharacterToLocation("Panama_TownhallRoom", "reload", "reload1");
}

void ActiveF4Control()
{
	/*Log_Info("Test F4 button");
    SetRandGeraldSail(pchar, rand(4));*/
	
	/////////////////////////////////////
	
	Rat_GenerateRat();
	
	Log_Info("Сгенерили крысу!");
}

// Warship. Сюда повесил дамп аттрибутов - по Ф12 не нужно это
void ActiveF5Control()
{
	int characterIndex = LAi_FindNearestVisCharacter(PChar, 15);
	ref characterRef;
	
    if(characterIndex != -1)
    {
        characterRef = GetCharacter(characterIndex);
		
		trace("==================== " + characterRef.ID + " ====================");
		DumpAttributes(characterRef);
		trace("========================================");
		
		string sGun = GetCharacterEquipByGroup(characterRef, GUN_ITEM_TYPE);
		if(sGun != "") 
		{
			ref rItm = ItemsFromID(sGun); 
			trace("==================== " + rItm.ID + " ====================");
			DumpAttributes(rItm);
			trace("========================================");
		}	
	}

	Log_Info("Дамп аттрибутов ближайшего персонажа");
}

void ActiveF7Control()
{
	// Warship. Убить боижайшего персонажа
	int characterIndex = LAi_FindNearestVisCharacter(PChar, 25);
	ref characterRef;
	
    if(characterIndex != -1)
	{
		characterRef = &Characters[characterIndex];
		
		if(!LAi_IsImmortal(characterRef)) // Квестовые
		{
			LAi_KillCharacter(characterRef);
			Log_Info("Убили персонажа с ID == " + characterRef.Id);
		}
		else
		{
			Log_Info("Нельзя убить персонажа с ID == " + characterRef.Id);
		}
	}
}

void setclock()
{
	int hour =  GetHour();
	if(hour < 1 ) hour = 12;
	if(hour > 12) hour -= 12;
	int n = FindLoadedLocation();
	locations[n].models.always.L3 = "hourhand"+hour;
//    Locations[n].models.always.L3.locator.group = "WindMill";
//	Locations[n].models.always.L3.locator.name ="Fan3";	
//	Locations[n].models.always.L3.rotate.x = 0.0;
//	Locations[n].models.always.L3.rotate.y = 0.0;
//	Locations[n].models.always.L3.rotate.z = 0.0017;  
    
	locations[n].models.always.clock = "hand_clock";
	Locations[n].models.always.clock.locator.group = "WindMill";
	Locations[n].models.always.clock.locator.name ="Fan2";	
	Locations[n].models.always.clock.rotate.x = 0.0;
	Locations[n].models.always.clock.rotate.y = 0.0;
	Locations[n].models.always.clock.rotate.z = 0.02;  
	log_info("setclock "+hour);
}

void ActiveF10Control()
{
	Log_Info("ЛОГЛОГ");
	
}

void AdvanceTime() {
    int hour;
    if (!CheckAttribute(pchar, "hour")) {
        hour = 0;
    } else {
        hour = sti(pchar.hour);
    }
    
    SetCurrentTime(hour, 0);
    DoReloadCharacterToLocation(pchar.location, pchar.location.group, pchar.location.locator);
    
    if (hour < 23) {
        pchar.hour = hour + 1;
    } else {
        Log_Info("Конец.");
    }
}

void SummonStorm() {
    ref location = &loadedLocation;
    if (CheckAttribute(location, "alwaysStorm"))
    {
        DeleteAttribute(location, "alwaysStorm");
        DeleteAttribute(location, "storm");
        DeleteAttribute(location, "tornado");
        DeleteAttribute(location, "QuestlockWeather");
    }
    else
    {
        location.alwaysStorm = true; 
        location.storm = true;
        location.tornado = true;
    }
    
    DoReloadCharacterToLocation(pchar.location, pchar.location.group, pchar.location.locator);
}

//void ActiveF10Control()
//{
	/*int i = FindIsland("IslaMona");
	Islands[i].visible = true;
	Islands[i].reload_enable = true;
	pchar.quest.mtraxx_wolfreek_islamona.win_condition.l1 = "location";
	pchar.quest.mtraxx_wolfreek_islamona.win_condition.l1.location = "Shore75";
	pchar.quest.mtraxx_wolfreek_islamona.function = "Mtraxx_WolfreekIslaMona";
	pchar.quest.mtraxx_wolfreek_islamona1.win_condition.l1 = "location";
	pchar.quest.mtraxx_wolfreek_islamona1.win_condition.l1.location = "Shore77";
	pchar.quest.mtraxx_wolfreek_islamona1.function = "Mtraxx_WolfreekIslaMona";
	// характеристики топора викинга
	sld = ItemsFromID("topor_06");
	sld.Balance = 2.0;
	sld.Weight = 3.5;
	sld.Attack = 88.0;*/
//	IslaMona_AdvanceStageToTwo();
//	IslaMona_AdvanceStageToThree();
	//IslaMona_SetCannonPeace();
//}

///  статы персонажа в близи
void ActiveF12Control()
{
	ref mainCh = GetMainCharacter();
    
    //Найти ближайшего видимого персонажа в заданном радиусе
    int res = LAi_FindNearestVisCharacter(mainCh, 15);
    if (res != -1)
    {
        ref findCh = GetCharacter(res);
        if(findCh.name == "") return;
        res = findCh.chr_ai.hp;
        Log_SetStringToLog("" + GetFullName(findCh) +
                           " "+XI_ConvertString("Rank")+" " + findCh.rank + " "+XI_ConvertString("Health")+" "+res + "/" + LAi_GetCharacterMaxHP(findCh));

		if (bBettaTestMode)
        {
            Log_SetStringToLog("Id= " + findCh.id);
            Log_SetStringToLog("Idx= " + findCh.index);
            
            if(CheckAttribute(findCh, "LifeDay"))
			Log_Info("LifeDay - " + findCh.LifeDay);
		
			if(CheckAttribute(findCh, "City"))
	    	Log_Info("City - " + findCh.City);
            
            if (CheckAttribute(findCh, "equip.blade"))
            {
                Log_SetStringToLog("Blade= " + findCh.equip.blade);
            }
            if (CheckAttribute(findCh, "equip.pistol"))
            {
                Log_SetStringToLog("Pistol= " + findCh.equip.pistol);
            }
            Log_SetStringToLog("model= " + findCh.model);
            Log_SetStringToLog("model.animation= " + findCh.model.animation);
            Log_SetStringToLog("face= " + findCh.faceId);
            Log_SetStringToLog("chr_ai.type= " + findCh.chr_ai.type);
            Log_SetStringToLog("Group= "+findCh.location.group + " locator= " + findCh.location.locator);
            if (CheckAttribute(findCh, "cirassId"))
            {
                Log_SetStringToLog("cirassId= " + sti(findCh.cirassId));
            }
            else
            {
                Log_SetStringToLog("Нет брони");
            }
            if (CheckAttribute(findCh, "chr_ai.FencingType"))
            {
                Log_SetStringToLog("chr_ai.FencingType= " + findCh.chr_ai.FencingType));
            }
            else
            {
                Log_SetStringToLog("Нет FencingType - error");
            }
			if (CheckAttribute(findCh, "CanTakeMushket"))
			{
				Log_SetStringToLog("CanTakeMushket - 1");
			}
			
            /*int dchr_index;
            ref deadCh;
            dchr_index = Dead_FindCloseBody();
            if (dchr_index != -1)
            {
                deadCh = &Dead_Characters[dchr_index];
                Log_SetStringToLog("Dead=" + deadCh.id);
            } */
			Log_SetStringToLog("Нация: " + findCh.nation);
			Log_SetStringToLog("Пол: " + findCh.sex);
			Log_SetStringToLog("Группа: " + findCh.chr_ai.group);
			Log_SetStringToLog("Темплейт: " + findCh.chr_ai.tmpl);

			//Log_SetStringToLog("Стейт: " + findCh.chr_ai.tmpl.state);
		//	dumpattributes(findCh);

            mainCh.SystemInfo.OnlyShowCharacter = true;
			LaunchCharacter(findCh);
        }
        else
        {
            if (MOD_BETTATESTMODE == "Test")
	        {
	            Log_SetStringToLog("Id= " + findCh.id);
	        }
        }
    }
}

///////////////////////////// test //////////////
void TestColonyCommanders()
{
	int iChar;

	string sColony;

	int i;
	float x, y, z;  // boal

	for (i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation == "none") continue; // необитайки
		// зададим базовых мэров городов
		iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
		if (iChar != -1)
		{   // мэр есть
        	Log_Info("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        	trace("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        }

		// добавить проверку на пиратов, у них нет фортов, нафиг им коммандер?
		if (CheckAttribute(&colonies[i], "HasNoFort"))
		{
			continue;
		}
		iChar = GetCharacterIndex(colonies[i].id + " Fort Commander");
		Log_Info("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
  		trace("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
	}
}
// проверка ликвидности товара - цена-вес, что выгоднее - выводим в компил.лог список, строим заполняя трюм товаром по одной пачке
void TestGoodsLiquidity()
{
	int i, j, idx;
	float fMaxCost;
	
	for (i = 0; i< GOODS_QUANTITY; i++)
	{
		SetCharacterGoods(pchar, i, sti(Goods[i].Units));
	}
	trace("======= TestGoodsLiquidity ======== start ");
	for (j = 0; j< GOODS_QUANTITY; j++)
	{
		fMaxCost = 0;
		idx = -1; 
		for (i = 0; i< GOODS_QUANTITY; i++)
		{
			if (GetCargoGoods(pchar, i) > 0)
			{
				if (fMaxCost < stf(Goods[i].Cost)/stf(Goods[i].Weight)) 
				{
					fMaxCost = stf(Goods[i].Cost)/stf(Goods[i].Weight);
					idx = i;
				} 
			}
		}
		if (fMaxCost > 0)
		{
			SetCharacterGoods(pchar, idx, 0);	
			trace(Goods[idx].Name + " = " + fMaxCost);
			Log_info(Goods[idx].Name + " = " + fMaxCost);
		}
	}
	trace("======= TestGoodsLiquidity ======== end ");
}
