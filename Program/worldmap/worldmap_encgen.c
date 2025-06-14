

//--------------------------------------------------------------------------------------
//Генерация энкоунтеров
//--------------------------------------------------------------------------------------

//Частота штормов в секунду
#define WDM_STORM_RATE   		0.0001
//Частота торговцев в секунду
#define WDM_MERCHANTS_RATE		0.08
//Частота воюищих кораблей в секунду
#define WDM_WARRING_RATE		0.012
//Частота нападающих кораблей в секунду
#define WDM_FOLLOW_RATE  		0.015
//Частота специальных событий  (бочка или шлюпка) в секунду
#define WDM_SPECIAL_RATE  		0.0015

//MAX, это поменял Я!!!!!!! Шуршунчик.
// Boal - учите мат. часть, г-н Шуршунчик. не работает это до начала новой игры, всегда по уполчанию идёт. Дефайн правильно, тем более  iEncountersRate далее работает
//float WDM_FOLLOW_RATE = 0.025 * iEncountersRate;
//float WDM_STORM_RATE = 0.0001 * iEncountersRate;


//--------------------------------------------------------------------------------------


float wdmTimeOfLastStorm = 0.0;
float wdmTimeOfLastMerchant = 0.0;
float wdmTimeOfLastWarring = 0.0;
float wdmTimeOfLastFollow = 0.0;
float wdmTimeOfLastSpecial = 0.0;


void wdmReset()
{
	wdmTimeOfLastStorm = 0.0;
	wdmTimeOfLastMerchant = 0.0;
	wdmTimeOfLastWarring = 0.0;
	wdmTimeOfLastFollow = 0.0;
	wdmTimeOfLastSpecial = 0.0;
}

//Storm
void wdmStormGen(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	bool encoff = false;
	if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
	{
		if(sti(pchar.worldmapencountersoff)) return;
	}
	int numStorms = wdmGetNumberStorms();
	if(numStorms < 1)
	{
		wdmTimeOfLastStorm = wdmTimeOfLastStorm + dltTime*WDM_STORM_RATE*1000.0*iEncountersRate;
		if(rand(1001) < wdmTimeOfLastStorm)
		{
			wdmCreateStorm();
			wdmTimeOfLastStorm = 0.0;
		}
	}else{
		wdmTimeOfLastStorm = 0.0;
	}
}

//Random ships
void wdmShipEncounter(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	int numShips = wdmGetNumberShipEncounters();
	if(CheckAttribute(pchar,"worldmap.shipcounter")) {
		numShips = numShips - sti(pchar.worldmap.shipcounter);
	}
	if(numShips < 0)
	{
//		trace("Warning! World map ship quantity < 0 : numShips = " + numShips);
//		trace("pchar.worldmap.shipcounter = " + pchar.worldmap.shipcounter);
		numShips = 0;
	}
	if(numShips < 8)
	{
		//Вероятности появления
		wdmTimeOfLastMerchant = wdmTimeOfLastMerchant + dltTime * WDM_MERCHANTS_RATE * 1000.0 * iEncountersRate;
		wdmTimeOfLastWarring  = wdmTimeOfLastWarring  + dltTime * WDM_WARRING_RATE   * 1000.0 * iEncountersRate;
		wdmTimeOfLastFollow   = wdmTimeOfLastFollow   + dltTime * WDM_FOLLOW_RATE    * 1000.0 * iEncountersRate;
		wdmTimeOfLastSpecial  = wdmTimeOfLastSpecial  + dltTime * WDM_SPECIAL_RATE   * 1000.0 * iEncountersRate;
		//Вероятность от количества созданных
		float nump = 1.0 - numShips*0.15;
		//Выбираем
		if(rand(1001) + 1 < wdmTimeOfLastMerchant)
		{
			wdmTimeOfLastMerchant = 0.0;
			wdmCreateMerchantShip(0.8 + rand(10)*0.03);
		}
		else
		{
			bool encoff = false;
			if(CheckAttribute(pchar,"worldmapencountersoff"))
			{
				encoff = sti(pchar.worldmapencountersoff);
			}
			if(encoff == false)
			{
				if(rand(1001) + 1 < wdmTimeOfLastWarring)
				{
					wdmTimeOfLastWarring = 0.0;
					wdmCreateWarringShips();
				}
				else
				{
					if(rand(1001) + 1 < wdmTimeOfLastFollow)
					{
						wdmTimeOfLastFollow = 0.0;
						if(!IsStopMapFollowEncounters() && !CheckAttribute(pchar, "worldmap.FollowCounter"))
						{
							if(wdmCreateFollowShip(0.8 + rand(10)*0.05))
							{
								// belamour cle не генерим, если есть преследователь
								if(sti(pchar.rank) < 15 && rand(sti(pchar.rank)) < 4)
									pchar.worldmap.FollowCounter = true;
							}
						}						
					}
				}
				if(rand(1001) + 1 < wdmTimeOfLastSpecial)
				{
					wdmTimeOfLastSpecial = 0.0;
					wdmCreateSpecial(0.05 + rand(10)*0.02);
				}					
			}
		}
	}
	else
	{
		wdmTimeOfLastMerchant = 0.0;
		wdmTimeOfLastWarring = 0.0;
		wdmTimeOfLastFollow = 0.0;
		wdmTimeOfLastSpecial = 0.0;
	}
}

// to_do: Map_BattleEnd
#event_handler("Map_TraderSucces", "Map_TraderSucces");
#event_handler("Map_WarriorEnd", "Map_WarriorEnd");

void Map_WarriorEnd()
{
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		return;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	if(sti(pchar.worldmap.shipcounter) < 0)
	{
		sti(pchar.worldmap.shipcounter) = 0;
	}
    string sChar = GetEventData();

    Map_WarriorEnd_quest(sChar);
}

void Map_WarriorEnd_quest(string sChar)
{
    //int iChar = GetCharacterIndex(sChar);
    //if (iChar != -1)
    ref rChar = CharacterFromID(sChar);

    if(FindSubStr(sChar, "Brigadier0", 0) != -1)
        FireBrigadeRefresh(rChar, sti(rChar.Nation), 1);
}

void Map_TraderSucces()
{
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{		
		return;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	if(sti(pchar.worldmap.shipcounter) < 0)
	{
		pchar.worldmap.shipcounter = 0;
	}
	string sChar = GetEventData();

	Map_TraderSucces_quest(sChar); //обработка квестов по поиску кэпов

	//homo 03/08/06 Наводка на купца
	if (findsubstr(sChar, "_QuestMerchant" , 0) != -1)
	{
        Map_ReleaseQuestEncounter(sChar);
        Group_DeleteGroup("Sea_"+sChar);
        CloseQuestHeader("MerchantOnMap");
	}
    else if (sChar == "Head_of_Gold_Squadron") // homo 07/10/06 GoldFleet
	{
        RouteGoldFleet();
	}
	else if (findsubstr(sChar, "SiegeCap_" , 0) != -1)
	{
        SiegeProgress();
	}

	/*if(GetCharacterIndex(sChar) != -1)  // типа пример
	{
		if(CheckAttribute(&characters[GetCharacterIndex(sChar)], "hovernor"))
		{
			if(sti(characters[GetCharacterIndex(sChar)].hovernor) == 1)
			{
				//  to_do MakeNewCapital(sChar);
				return;
			}
		}
	}
	else
	{
		trace("Can't find character with character id " + sChar);
		return;
	}

	if(sChar == "Head of Gold Squadron")
	{
		PrepareContinueGoldConvoy();
		return;
	}
	if(CheckAttribute(&characters[GetCharacterIndex(sChar)], "mapEnc.quest"))
	{
		int iQuest = sti(characters[GetCharacterIndex(sChar)].mapEnc.quest);
		string sQuest = "sink_ship_character_" + sChar + "_wait_before_travel";
		pchar.quest.(sQuest).win_condition.l1 = "timer";
		pchar.quest.(sQuest).win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
		pchar.quest.(sQuest).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
		pchar.quest.(sQuest).win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
		pchar.quest.(sQuest).win_condition.l1.date.hour = rand(23);
		pchar.quest.(sQuest).win_condition = "sink_ship_travel";
		pchar.quest.(sQuest).quest = iQuest;

		return;
	}  */
}

void Map_TraderSucces_quest(string sChar)
{
	ref character = CharacterFromID(sChar);
	
	// Warship 08.07.09 Пасхалка с бригантиной Мэри Селест
	if(sChar == "MaryCelesteCapitan")
	{
		Map_ReleaseQuestEncounter("MaryCelesteCapitan");
		
		// Для палубы, при Map_ReleaseQuestEncounter() рассылалось событие, а ставить ещё раз не нужно
		if(PChar.QuestTemp.MaryCeleste != "OnDeck")
		{
			character.fromCity = character.toCity; // Колония, из бухты которой выйдет
			character.fromShore = character.toShore;
			character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
			character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
			
			Map_CreateTrader(character.fromShore, character.toShore, "MaryCelesteCapitan", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)));
			
			Log_TestInfo("Бригантина Мэри Селест вышла из " + character.fromCity + " и направилась в " + character.toShore);
		}
	}
	else if(sChar == "PiratesOnUninhabited_BadPirate")
	{
        // Warship Генер "Пираты на необитайке"
        // В город не выходит, только по глобалке: город - это лишние телодвижения, которые погоды особо не сделают
		Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate");
		
		if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.ClearShip"))
		{
			character.fromCity = character.toCity; // Колония, из бухты которой выйдет
			character.fromShore = character.toShore;
			character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
			character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
			
			Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", -1);
			
			Log_TestInfo("Пираты на необитайке: кэп вышел из " + character.fromCity + " и направился в: " + character.toShore);
		}
	}
	else if(sChar == "ShipWreck_BadPirate") // лесник - добавил блок по генеру "потерпевшие кораблекрушение"
	{
		Map_ReleaseQuestEncounter("ShipWreck_BadPirate");
		
		if(!CheckAttribute(PChar, "GenQuest.ShipWreck_BadPirate.ClearShip")) // проверка на срок действия квеста. 
		{
			character.fromCity = character.toCity; // Колония, из бухты которой выйдет
			character.fromShore = character.toShore;
			character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
			character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
			
			Map_CreateTrader(character.fromShore, character.toShore, "ShipWreck_BadPirate", -1);
			
			Log_TestInfo("Кораблекрушенцы: корабль вышел из " + character.fromCity + " и направился в: " + character.toCity);
		}
	}
	else if(sChar == "PirateCapt") // ugeen --> генератор "Повод для спешки"
	{
		Log_TestInfo("Пиратский корабль дошёл до места назначения.");
		Map_ReleaseQuestEncounter(sChar);
		AddQuestRecord("ReasonToFast","26");
		CloseQuestHeader("ReasonToFast");
		DeleteAttribute(pchar,"questTemp.ReasonToFast");
	}
	else if (findsubstr(sChar, "PortmansCap_" , 0) != -1 && characters[GetCharacterIndex(sChar)].quest == "InMap")
	{
        //розыск и отдача кэпу судового журнала
		SetCapitainFromSeaToCity(sChar);
		Log_TestInfo("Энканутер рассеянного кэпа " + sChar + " дошёл до места назначения.");
	}
	else if (findsubstr(sChar, "SeekCap_" , 0) != -1 && characters[GetCharacterIndex(sChar)].quest == "InMap")
	{
        //поиски кэпа-вора
		SetRobberFromMapToSea(sChar);
		Log_TestInfo("Энканутер кэпа-вора " + sChar + " дошёл до места назначения.");
	}
	else if (findsubstr(sChar, "SeekCitizCap_" , 0) != -1) //поиски кэпа, квест дают горожане
	{
		if(character.quest == "InMap")
		{
			CitizCapFromMapToCity(sChar);
			Log_TestInfo("Энканутер кэпа " + sChar + " дошёл до места назначения.");
		}
		else if(character.quest == "outMap")
		{
			string sTemp = "SCQ_" + character.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			character.lifeDay = 0;
		}
	}
	else if(sChar == "SGFcurierCap") // belamour legendary edition на пару с акулой
	{
		Map_ReleaseQuestEncounter(sChar);
		character.lifeDay = 0;
		Group_DeleteGroup("Sea_SGFcurierCap1");
		SGF_Curier_ReleaseInGlobal();
	}
	else if (sChar == "SantaMisericordia_cap" /* && characters[GetCharacterIndex(sChar)].quest == "InMap" */)
	{
		SantaMisericordia_ToCity(sChar);
	}
	else if (sChar == "LadyBeth_cap"/*  && characters[GetCharacterIndex(sChar)].quest == "InMap" */)
	{
		LadyBeth_ToCity(sChar);
	}
	else if (sChar == "Memento_cap")
	{
		Memento_ToCity(sChar);
	}
    else if(FindSubStr(sChar, "Brigadier0", 0) != -1)
    {
        FireBrigadeRefresh(character, sti(character.nation), 5 + rand(4));
    }
}
