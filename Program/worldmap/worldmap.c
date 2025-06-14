/*
	Programm interface:

	Init world map in start
		void wdmInitWorldMap();
	Create world map object
		void wdmCreateMap();
	Release world map object
		void wdmReleaseMap();


	SPI (Script program interface):
	Получение данных от карты
	(const) поля только для прочтения
	(var) поля только для записи и прочтения, запись в них приводит к обновления остальных полей,
	      принадлежащих этой группе

	Шторма
	worldMap.storm.num - текущие количество штормов в карте (const)
	worldMap.storm.cur - индекс текущего шторма 0..num-1, надо перезаписывать для обновления полей (var)
	worldMap.storm.x - позиция шторма по x (const)
	worldMap.storm.z - позиция шторма по z (const)
	worldMap.storm.time - оставшееся время жизни в секундах (const)

	Кораблики событий
	worldMap.encounter.num - текущие количество корабликов в карте (const)
	worldMap.encounter.cur - индекс текущего кораблика в карте (var)
	worldMap.encounter.x - позиция кораблика по x (const)
	worldMap.encounter.z - позиция кораблика по z (const)
	worldMap.encounter.time - оставшееся время жизни в секундах (const)
	worldMap.encounter.type - тип события, обозначаемый этим корабликом (define в таблице типов энкоунтеров)
	worldMap.encounter.attack - индекс кораблика, который атакуем (стоя на месте)
	worldMap.encounter.id - название описания энкоунтера: worldMap.encounters.(worldMap.encounter.id)...

	Разная информация
	worldMap.info.playerInStorm - если 1 то плеер находиться в шторме
	worldMap.info.updateinfo - апдейт информации


	//Внутреняя информация - !!!Осторожно, ни каких проверок!!!
	worldMap.enemyshipViewDistMin;		//Растояние на котором корабль начинает исчезать
	worldMap.enemyshipViewDistMax;		//Растояние на котором корабль исчезает полностью
	worldMap.enemyshipDistKill;			//Расстояние на котором убиваем корабль
	worldMap.enemyshipBrnDistMin;		//Минимальное растояние на котором рожается корабль
	worldMap.enemyshipBrnDistMax;		//Максимальное растояние на котором рожается корабль

	worldMap.stormViewDistMin;			//Растояние на котором шторм начинает исчезать
	worldMap.stormViewDistMax;			//Растояние на котором шторм исчезает полностью
	worldMap.stormDistKill;				//Расстояние на котором убиваем шторм
	worldMap.stormBrnDistMin;			//Минимальное растояние на котором рожается шторм
	worldMap.stormBrnDistMax;			//Максимальное растояние на котором рожается шторм

*/

#include "worldmap\worldmap_globals.c"
#include "worldmap\worldmap_events.c"
#include "worldmap\worldmap_reload.c"
#include "worldmap\worldmap_encgen.c"
#include "worldmap\worldmap_coords.c"


//=========================================================================================


#event_handler("WorldMap_EncounterCreate", "wdmEvent_EncounterCreate");
#event_handler("WorldMap_PlayerInStorm", "wdmEvent_PlayerInStorm");
#event_handler("WorldMap_ShipEncounter", "wdmEvent_ShipEncounter");
#event_handler("WorldMap_UpdateDate", "wdmEvent_UpdateDate");
#event_handler("ExitFromWorldMap", "wdmReloadToSea");
//#event_handler("NextDay", "wdmNextDayUpdate");

#event_handler("EventTimeUpdate", "wdmTimeUpdate");
#event_handler("EventAddNavyExp", "wdmAddNavyExp");


//=========================================================================================
// Programm interface
//=========================================================================================


void wdmCreateMap(float x, float z, float ay)
{
	//Координаты острова с которого уплыли
	float zeroX = MakeFloat(worldMap.zeroX);
	float zeroZ = MakeFloat(worldMap.zeroZ);
	float ShipX, ShipZ;
	//Находим новыве координаты на карте
	int scale = WDM_MAP_TO_SEA_SCALE;
	if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina" 
		|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo"
		|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
	{
		scale = 25;
	}
	shipX = (x/scale) + zeroX;
	shipZ = (z/scale) + zeroZ;
	worldMap.playerShipX = (x/scale) + zeroX;
	worldMap.playerShipZ = (z/scale) + zeroZ;
	worldMap.playerShipAY = ay;
//	trace(" X :" + x + " Z :" + z + " scale :" + scale + " ZeroX :" + zeroX + " ZeroZ:" + zeroZ + " WDMShipX:"+worldMap.playerShipX + " WDMShipZ:" + worldMap.playerShipZ + " ShipX:" + ShipX + " ShipZ:" + ShipZ);
	//Загружаем карту
	wdmCreateWorldMap();
}

void wdmTimeUpdate()
{
	//QuestsTimeCheck();
	// boal -->
	QuestsCheck();
	PostEvent("EventTimeUpdate", 5000);
	// boal <--
}

void wdmCreateWorldMap()
{
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	// belamour legendary edition задать течение времени и скорость корабля ГГ
	if(bImCasual) worldMap.date.hourPerSec = 0.6 + (MOD_SKILL_ENEMY_RATE/20.0);
	float fSpeedBonus = 0.0;
	if(bImCasual) fSpeedBonus += 0.05;
	if(IsEquipCharacterByItem(pchar, "sextant2")) fSpeedBonus += 0.05;
	else
	{
		if(IsEquipCharacterByItem(pchar, "bussol")) fSpeedBonus += 0.02;
		if(IsCharacterEquippedArtefact(pchar, "clock2")) fSpeedBonus += 0.03;
	}
	if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_FRIGATE_L) fSpeedBonus += 0.10;
	if(CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed")) fSpeedBonus += 0.05;
    if(CheckAttribute(&RealShips[sti(pchar.ship.type)], "Tuning.All")) fSpeedBonus += 0.05;
	if(HasShipTrait(pchar, "trait01")) fSpeedBonus += 0.05;
	worldMap.kPlayerMaxSpeed = 1.0 + fSpeedBonus;
	worldMap.shipSpeedOppositeWind = 0.55;
	bool IsEquipGlassSP3 = GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE) == "itmname_spyglassSP3";
	worldMap.enemyshipViewDistMin = GetFloatByCondition(IsEquipGlassSP3, 60.0, 69.0);
	worldMap.enemyshipViewDistMax = GetFloatByCondition(IsEquipGlassSP3, 120.0, 138.0);
	worldMap.stormViewDistMin = GetFloatByCondition(IsEquipGlassSP3, 90.0, 103.5);
	worldMap.stormViewDistMax = GetFloatByCondition(IsEquipGlassSP3, 180.0, 207.0);
	wdmLockReload = false;
    // Механика мощи
    UpdatePlayerSquadronPower();
	//Уберём все сообщения для игрока
	ClearAllLogStrings();
	//
	ReloadProgressStart();

	//Настраиваем имена месяцев
	worldMap.date.monthnames.m01 = XI_ConvertString("target_month_1");
	worldMap.date.monthnames.m02 = XI_ConvertString("target_month_2");
	worldMap.date.monthnames.m03 = XI_ConvertString("target_month_3");
	worldMap.date.monthnames.m04 = XI_ConvertString("target_month_4");
	worldMap.date.monthnames.m05 = XI_ConvertString("target_month_5");
	worldMap.date.monthnames.m06 = XI_ConvertString("target_month_6");
	worldMap.date.monthnames.m07 = XI_ConvertString("target_month_7");
	worldMap.date.monthnames.m08 = XI_ConvertString("target_month_8");
	worldMap.date.monthnames.m09 = XI_ConvertString("target_month_9");
	worldMap.date.monthnames.m10 = XI_ConvertString("target_month_10");
	worldMap.date.monthnames.m11 = XI_ConvertString("target_month_11");
	worldMap.date.monthnames.m12 = XI_ConvertString("target_month_12");

	int	fOffX = makeint(50.0 * fHtRatio);
	int	fOffY = makeint(50.0 * fHtRatio);
	int cx = sti(showWindow.right) - makeint(64.0 * fHtRatio) - fOffX;
	int cy = sti(showWindow.top) + makeint(64.0 * fHtRatio) + fOffY;
	float fRes = 1.0; // для ресайза

	fRes = 1.4;
	worldMap.sky.texture     = "interfaces\le\battle_interface\worldmap\sky.tga.tx";
	worldMap.sky.maskTexture = "interfaces\le\battle_interface\worldmap\sky_mask.tga.tx";
	worldMap.sky.leftPos = cx - makeint(64.0 * fRes * fHtRatio);
	worldMap.sky.topPos = cy - makeint(64.0 * fRes * fHtRatio);
	worldMap.sky.width = makeint(128.0 * fRes * fHtRatio);
	worldMap.sky.height = makeint(128.0 * fRes * fHtRatio);
	worldMap.sky.color = argb(128,255,255,255);

	fRes = 1.54;
	worldMap.windPointer.texture = "interfaces\le\battle_interface\worldmap\wind_pointer.tga.tx";
	worldMap.windPointer.leftPos = cx - makeint(64.0 * fRes * fHtRatio);
	worldMap.windPointer.topPos = cy - makeint(64.0 * fRes * fHtRatio);
	worldMap.windPointer.width = makeint(128.0 * fRes * fHtRatio);
	worldMap.windPointer.height = makeint(128.0 * fRes * fHtRatio);
	worldMap.windPointer.color = argb(255,255,255,255);

	fRes = 1.21;
	worldMap.windBar.texture     = "interfaces\le\battle_interface\worldmap\bar.tga.tx";
	worldMap.windBar.maskTexture = "interfaces\le\battle_interface\worldmap\bar_mask.tga.tx";
	worldMap.windBar.leftPos = cx - makeint(64.0 * fRes * fHtRatio);
	worldMap.windBar.topPos = cy + makeint(5.0 * fRes * fHtRatio) ;
	worldMap.windBar.width = makeint(128.0 * fRes * fHtRatio);
	worldMap.windBar.height = makeint(128.0 * fRes * fHtRatio);
	worldMap.windBar.color = argb(255,255,255,255);

	fRes = 1.6;
	worldMap.frame.texture = "interfaces\le\battle_interface\worldmap\back.tga.tx";
	worldMap.frame.leftPos = cx - makeint(64.0 * fRes * fHtRatio);
	worldMap.frame.topPos = cy - makeint(64.0 * fRes * fHtRatio);
	worldMap.frame.width = makeint(128.0 * fRes * fHtRatio);
	worldMap.frame.height = makeint(128.0 * fRes * fHtRatio);
	worldMap.frame.color = argb(255,255,255,255);

	worldMap.windText.font = "interface_normal";
	worldMap.windText.scale = 1.2 * fHtRatio;
	worldMap.windText.color = argb(255,255,255,255);
	worldMap.windText.pos.x = cx;
	worldMap.windText.pos.y = cy + makeint(73.0 * fHtRatio);

	worldMap.dateText.font = "interface_normal_bold";
	worldMap.dateText.scale = 0.7 * fHtRatio;
	worldMap.dateText.color = argb(255,255,255,255);
	worldMap.dateText.pos.x = cx;
	worldMap.dateText.pos.y = cy + makeint(105.0 * fHtRatio); // 16.0 is CharHeight for font = "normal"

	// Center
	cy = cy + makeint(128.0 * fHtRatio) + 32.0;

	fRes = 1.4;
	worldMap.morale.texture     = "interfaces\le\battle_interface\worldmap\morale.tga.tx";
	worldMap.morale.barTexture  = "interfaces\le\battle_interface\worldmap\morale_bar.tga.tx";
	worldMap.morale.maskTexture = "interfaces\le\battle_interface\worldmap\morale_mask.tga.tx";
	worldMap.morale.leftPos = cx - makeint(64.0 * fRes * fHtRatio);
	worldMap.morale.topPos = cy - makeint(18.0 * fRes * fHtRatio);
	worldMap.morale.width = makeint(128.0 * fRes * fHtRatio);
	worldMap.morale.height = makeint(64.0 * fRes * fHtRatio);
	worldMap.morale.color = argb(255,255,255,255);

	worldMap.foodText.font = "interface_normal";
	worldMap.foodText.scale = 1.3 * fHtRatio;
	worldMap.foodText.color = argb(255,255,255,255);
	worldMap.foodText.pos.x = cx - makeint(32.0 * fHtRatio);
	worldMap.foodText.pos.y = cy + makeint(55.0 * fHtRatio);

	worldMap.rumText.font = "interface_normal";
	worldMap.rumText.scale = 1.3 * fHtRatio;
	worldMap.rumText.color = argb(255,255,255,255);
	worldMap.rumText.pos.x = cx + makeint(33.0 * fHtRatio);
	worldMap.rumText.pos.y = cy + makeint(55.0 * fHtRatio);

	worldMap.coord.texture = "interfaces\le\battle_interface\worldmap\coord.tga.tx";
	worldMap.coord.leftPos = cx - makeint(64.0 * fHtRatio);
	worldMap.coord.topPos = cy + makeint(84.0 * fHtRatio);
	worldMap.coord.width = makeint(128.0 * fHtRatio);
	worldMap.coord.height = makeint(64.0 * fHtRatio);
	worldMap.coord.color = argb(225, 255, 255, 255);

	worldMap.stCoordText.font = "interface_normal";
	worldMap.stCoordText.scale = 1.2 * fHtRatio;
	worldMap.stCoordText.color = argb(255,255,255,255);
	worldMap.stCoordText.pos.x = cx;
	worldMap.stCoordText.pos.y = cy + makeint((84.0 + 13) * fHtRatio);
	worldMap.stCoordText.text = XI_ConvertString("Coordinates");

	worldMap.coordText.font = "interface_normal";
	worldMap.coordText.scale = 1.2 * fHtRatio;
	worldMap.coordText.color = argb(255,255,255,255);
	worldMap.coordText.pos.x = cx;
	worldMap.coordText.pos.y = cy + makeint((84.0 + 32.0) * fHtRatio);

	fRes = 1.4;
	worldMap.nationFlag.texture  = "interfaces\le\nations.tga.tx";
	worldMap.nationFlag.count = 8;
	worldMap.nationFlag.leftPos = cx - makeint(48.0 * fRes * fHtRatio / 2);
	worldMap.nationFlag.topPos = cy + makeint(115.0 * fRes * fHtRatio);
	worldMap.nationFlag.width = makeint(48.0 * fRes * fHtRatio);
	worldMap.nationFlag.height = makeint(48.0 * fRes * fHtRatio);
	worldMap.nationFlag.color = argb(255,255,255,255);

	//Удалим все устаревшие энкаунтеры
	worldMap.resizeRatio = fHtRatio;
	wdmRemoveOldEncounters();
//	Trace("Save check ---------------================--------------")
//	DumpAttributes(&worldMap);
//	Trace("Save check ###########----================--------------")
	worldMap.playerInStorm = "0";
	//Сбросим счётчики генерации энкоунтеров
	wdmReset();
	//Создаём карту
	CreateEntity(&worldMap,"worldmap");
	worldMap.isLoaded = "true";
	//Обновляем параметры
	worldMap.update = "";
	//Фейдер
/*	  
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeInTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_IN, fadeInTime, true);
	SendMessage(&wdm_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&wdm_fader, "ls",FADER_PICTURE,"loading\sea_0" + rand(2) + ".tga");	
*/	  
	//Установим звуковую схему
	SetSchemeForMap();
	//Сообщим, что загрузились
	PostEvent("EventWorldMapInit", 830); //fix boal
	ReloadProgressEnd();
	PostEvent("EventTimeUpdate", 100);	
	PostEvent("EventAddNavyExp", 100);	
	PostEvent("EventCoordUpdate", 100);	
	//Создаём накопившиеся квестовые энкаунтеры
	worldMap.addQuestEncounters = "updateQuest";
	wdmSetNationFlag(sti(pchar.nation));
	InitWmInterface();
}

void wdmLoadSavedMap()
{
	//Загружаем карту
	wdmCreateWorldMap();
}

void wdmRemoveOldEncounters()
{
	//Пометим протухшие энкаунтеры
	wdmMarkDeleteEncounters();
	//Собираем всех желающих
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	object forDelete;
	string attr, encID;
	int count = 0;
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "needDelete") != 0)
		{
			attr = "del" + count;
			forDelete.(attr) = GetAttributeName(enc);
			count = count + 1;
		}
	}
	for(i = 0; i < count; i++)
	{
		attr = "del" + i;
		encID = "encounters." + forDelete.(attr);
		DeleteAttribute(&worldMap, encID);
	}
}

float wdmGetDays(int year, int month, int day, int hour)
{
	//Считаем дни по годам
	if(year < 0) year = 0;
	if(year > 3000) year = 3000;
	year = year*365;
	//Считаем целые дни
	for(int i = 1; i < month; i++)
	{
		day = day + GetMonthDays(i);
	}
	//Считаем полные дни
	float days = year + day + (hour/24.0);
	return days;
}

void wdmSetNationFlag(int iNation)
{
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_SET_NATION_FLAG, iNation);
}

void wdmMarkDeleteEncounters()
{
	//Получаем дату
	int year = sti(worldMap.date.year);
	int month = sti(worldMap.date.month);
	int day = sti(worldMap.date.day);
	int hour = sti(worldMap.date.hour);
	float days = wdmGetDays(year, month, day, hour);
	int encYear, encMonth, encDay, encHour;
	//Перебираем все энкаунтеры, помечая на удаление
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "Quest") != 0)
		{
			continue;
		}
		bool deleteMe = false;
		if(CheckAttribute(enc, "year") != 0)
		{
			encYear = sti(enc.year);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "month") != 0)
		{
			encMonth = sti(enc.month);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "day") != 0)
		{
			encDay = sti(enc.day);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "hour") != 0)
		{
			encHour = sti(enc.hour);
		}else{
			deleteMe = true;
		}
		if(deleteMe != true)
		{
			float deltaDays = wdmGetDays(encYear, encMonth, encDay, encHour) - days;
			if(deltaDays < 0)
			{
				deltaDays = -deltaDays;
			}
			if(deltaDays > 1.0)
			{
				deleteMe = true;
			}
		}
		if(deleteMe != false)
		{
			enc.needDelete = "Time delete";
		}
	}
}

void wdmAddNavyExp()
{
	if(!isEntity(&WorldMap)) return;
	
	float hour = GetHour();
	
	if(hour == 12.00 || hour == 0.00)
	{
		if(IsEquipCharacterByItem(pchar, "bussol") && IsCharacterEquippedArtefact(pchar, "clock2"))
			AddCharacterExpToSkill(pchar, "Sailing", 2.0);
		else
			AddCharacterExpToSkill(pchar, "Sailing", 1.5);
		// belamour пока на тесты раз в три дня
		if(hour == 0.00 && GetDataDay() % 3 == 0) notification(StringFromKey("RPGUtilite_1"), "Sailing");
			
	}
	if(GetSkillValue(pchar, SKILL_TYPE, "Sailing") < 100)
	{
		PostEvent("EventAddNavyExp", 1000);
	}
}