
#include "Locations\particles.c"

#define EVENT_LOCATION_LOAD		"EventLoadLocation"
#define EVENT_LOCATION_UNLOAD	"EventUnloadLocation"

#define MAX_SHIPS_IN_LOCATION	32

ref loadedLocation;
object locWeather;
object locSea;
object locCamera;
object locShips[MAX_SHIPS_IN_LOCATION];

int iShips[MAX_SHIPS_IN_LOCATION];
int	locNumShips = 0;

float locTmpTime = 0.0;
bool locDisableUpdateTime = false;

int FindLocation(string id)
{
	/*
	for(int i = 0; i < nLocationsNum; i++)
	{
		if(Locations[i].id == id)
		{
			return i;
		}
	}

	return -1;
	*/
	
	return NativeFindLocation(&locations, id);
	
}

void SetCamShuttle(ref loc) // boal вынес в метод
{
	if(CheckAttribute(pchar, "GenQuest.CamShuttle"))
	{
		float fshut = stf(Pchar.GenQuest.CamShuttle)/10;
		float ftmp = 0.1;
		if (fshut > 0.4) fshut = 0.4;
		if (fshut < 0.2) ftmp = 0.05;
		Log_TestInfo("Как штормит сегодня, однако... нажрался, скотина!");
		Log_TestInfo(""+fshut+"");
		SendMessage(&LocCamera, "lffffff", -1, 0.5, -1.0, 1.0, 1.0, ftmp, fshut);
	}
	else
	{
		//скорость, время, мин, макс, скорость наклона, макс наклон
		SendMessage(&LocCamera, "lffffff", -1, 0.5, 1.0, 1.0, 1.0, 0.00, 0.0);
		//SendMessage(&LocCamera, "lffffff", -1, 0.0, 0, 0.0, 0.0, 0.00, 0.0);
	}
}

bool LoadLocation(ref loc)
{
	//trace("LoadLocation(ref loc) " + loc.id);
	PostEvent(EVENT_LOCATION_LOAD,0);

	int i;
	bool res;
	
	for (i = 0; i < MAX_SHIPS_IN_LOCATION; i++) { iShips[i] = -1; }
	
	//Time update==========================================================================
	locTmpTime += 5;
	CalcLocalTime(3);
	//Environment==========================================================================
	chrWaitReloadLocator = ""; // fix перехода в таверну при клики на диалог
	chrWaitReloadIsNoLink = false;
		
    loadedLocation = loc; // первое присвоение boal
	//Environment==========================================================================

	if(CheckAttribute(loc, "type"))
	{
		res = true;
		switch(loc.type)
		{
		case "cave":			// пещера
			ExecuteTechnique("amb_cave");
			res = false;
			Achievment_SetStat(40, 1);
		break;
		case "inca_temple":		// храм инков
			ExecuteTechnique("amb_inca_temple");
			res = false;
			break;
		case "house":			// дом
			ExecuteTechnique("amb_house");
			res = false;
			break;
		case "tavern":			// таверна
			ExecuteTechnique("amb_tavern");
			res = false;
			break;
		case "shop":			// магазин
			ExecuteTechnique("amb_shop");
			res = false;
			break;
		case "residence":		// резиденция
			ExecuteTechnique("amb_residence");
			res = false;
			break;
		case "church":			// церковь
			ExecuteTechnique("amb_church");
			res = false;
			break;
		case "fort_attack":			// тюрьма
			ExecuteTechnique("amb_jail");
			res = false;
			break;
		case "dungeon":
			ExecuteTechnique("amb_dungeon");
			res = false;
			break;
		}
		if(res)
		{
			ExecuteTechnique("amb_other");
		}
	}
	//
	
	if(CheckAttribute(loc, "QuestlockWeather"))
	{		
		if (CheckAttribute(loc, "QuestlockWeather.hours") && CheckAttribute(loc, "QuestlockWeather.minutes"))
		{
			SetCurrentTime(sti(loc.QuestlockWeather.hours), sti(loc.QuestlockWeather.minutes));
			DeleteAttribute(loc, "QuestlockWeather.hours");
			DeleteAttribute(loc, "QuestlockWeather.minutes");
		}
		//SetNextWeather(loc.QuestlockWeather);
	}

	
	bool isNoBoarding = true;
	bool isFort = false;
	if(CheckAttribute(loc, "boarding") == true)
	{
		if(loc.boarding == "true") isNoBoarding = false;
		if(loc.boarding == "fort")
		{
			isNoBoarding = false;
			isFort = true;
		}
		if (loc.id == "Quest_Cabin_Medium" || loc.id == "Quest_Deck_Medium" || loc.id == "Quest_Campus" || loc.id == "Quest_Deck")
		{
			//Sea
			if(loc.environment.sea == "true") CreateSea(EXECUTE,REALIZE);
			//Weather
			if(loc.environment.weather == "true") CreateWeather(EXECUTE,REALIZE);
		}
	}
	if(isNoBoarding)
	{
		//Sea
		if(loc.environment.sea == "true") 
		{
			CreateSea(EXECUTE, REALIZE);
			if (!CheckAttribute(loc, "notCreateFoam"))
			{
				CreateCoastFoamEnvironment(loc.id, EXECUTE, REALIZE);
			}
		}
		//Weather
		if(loc.environment.weather == "true") CreateWeather(EXECUTE,REALIZE);
		//Ship env
		CreateShipEnvironment();
	}
	if(isFort)
	{
		//Sea
		if(loc.environment.sea == "true") CreateSea(EXECUTE,REALIZE);
		//Weather
		if(loc.environment.weather == "true") CreateWeather(EXECUTE,REALIZE);
	}

	ReloadProgressUpdate();
	//SendMessage(Sound,"lf",MSG_SOUND_SET_MASTER_VOLUME,0.0);

	//Create location======================================================================
	if(CreateEntity(&loc, "location") == 0) return 0;
	//Set models path
	if(CheckAttribute(loc, "filespath.models"))
	{		
		SendMessage(loc, "ls", MSG_LOCATION_MODELSPATH, loc.filespath.models);
	}
	//Set textures path
	if(CheckAttribute(loc, "filespath.textures"))
	{
		SendMessage(loc, "ls", MSG_LOCATION_TEXTURESPATH, loc.filespath.textures);
	}
	//Set lighting path
	bool dLight = LocCheckDLight(loc);
	if(!dLight) // inside
	{	
		SendMessage(loc, "ls", MSG_LOCATION_LIGHTPATH, GetLightingPathLoc());
	}		
	else // outside
	{
		if(sti(InterfaceStates.DYNAMICLIGHTS))
		{
			SendMessage(loc, "ls", MSG_LOCATION_LIGHTPATH, "");
		}			
		else
		{
			SendMessage(loc, "ls", MSG_LOCATION_LIGHTPATH, GetLightingPath());
		}			
	}	
	
	SendMessage(loc, "ls", MSG_LOCATION_SHADOWPATH, GetLmLightingPath());
    
    // башенные часы
    if(loc.id == "Villemstad_town")
    {
        float fTime = GetTime();
        int Hour 	= makeint(fTime);
        int Min 	= makeint((fTime - Hour) * 60);
        float delta = makefloat(Min)/60.0;
        
        if(hour < 1 ) hour  = 12;
        if(hour > 12) hour -= 12;
        
        // часовая стрелка
        loc.models.always.clockh = "hourhand";
        loc.models.always.clockh.locator.group = "WindMill";
        loc.models.always.clockh.locator.name ="Fan3";	
        loc.models.always.clockh.rotate.x = 0.0;
        loc.models.always.clockh.rotate.y = 0.0;
        loc.models.always.clockh.rotate.z = 0.00145;  
        
        loc.models.always.clockh.rotate.dx = 0.0;
        loc.models.always.clockh.rotate.dy = 0.0;
        loc.models.always.clockh.rotate.dz = 0.523 * hour + 0.523 * delta;

        // минутная стрелка
        loc.models.always.clock = "hand_clock";
        loc.models.always.clock.locator.group = "WindMill";
        loc.models.always.clock.locator.name ="Fan2";	
        loc.models.always.clock.rotate.x = 0.0;
        loc.models.always.clock.rotate.y = 0.0;
        loc.models.always.clock.rotate.z = 0.016;

        loc.models.always.clock.rotate.dx = 0.0;
        loc.models.always.clock.rotate.dy = 0.0;
        loc.models.always.clock.rotate.dz = 6.28 * delta;

        //Log_SetStringToLog("Villemstad_town  - Hour : " + Hour + " min : " + Min);
    }

	// ворота в резиденцию PortRoyal
	if(loc.id == "PortRoyal_town")
	{
		if(chrCheckReload(loc, "reload3_back")) // локатор резиденции
		{
			loc.models.night.gates = "PortRoyal_gates_day";
			loc.models.night.charactersPatch = "PortRoyal_patch_day";
		}
		else
		{
			loc.models.night.gates = "PortRoyal_gates_night";
			loc.models.night.charactersPatch = "PortRoyal_patch_night";
		}
	}

	// инит данных для режима скрытности
	StealthEnable = false;
	if(CheckAttribute(loc,"soldiers"))
	{
		if(CheckAttribute(loc,"fastreload") && CheckAttribute(&Colonies[FindColony(loc.fastreload)],"nation"))
		{
			
			StealthNat = Colonies[FindColony(loc.fastreload)].nation;
			if(GetNationRelation2MainCharacter(StealthNat) == RELATION_ENEMY || GetNationRelation(StealthNat, GetBaseHeroNation()) == RELATION_ENEMY)
				StealthEnable = true;
			if(GetRelation2BaseNation(StealthNat) == RELATION_ENEMY) StealthEnable = true;
			if(StealthNat == PIRATE) StealthEnable = false;
		}
	}
 
	//Loading always models================================================================
	aref st, at, lit, lit1;
	string sat;
	makearef(st, loc.models.always);
	int num = GetAttributesNum(st);
	float fMaxDist;
	for(i = 0; i < num; i++)
	{
		at = GetAttributeN(st, i);
		sat = GetAttributeName(at);
        if(sat != "grassPatch")
		{
			sat = "models.always." + sat;
			res = LocLoadModel(loc, sat, "");
			if(res == 0)
			{
				Trace("LocationLoader: not loaded model location." + sat + ", id = " + loc.id);
				Trace("Unload location.");
				UnloadLocation(loc);
				return 0;
			}
		}else{
			LocLoadGrass(loc, "models.always." + sat);
			object objGrass;
			GetEntity(&objGrass,"grass"));
			if(CheckAttribute(&InterfaceStates,"GrassDrawDistance"))
			{
				fMaxDist = stf(InterfaceStates.GrassDrawDistance);
				if(CheckLocGrassOpt() && fMaxDist > 100) fMaxDist = 100;
			} else fMaxDist = 50;

			// MSG_GRASS_SET_PARAM имеет параметры (в скобках цифры из движка по умолчанию):
			// m_fDataScale(1.0); m_fMaxWidth(1.0); m_fMaxHeight(0.2); m_fMinVisibleDist(10.0); m_fMaxVisibleDist(50.0); m_fMinGrassLod(0.0);
			SendMessage(objGrass,"lffffff",42666, 1.0, 1.0, 0.2, 10.0, fMaxDist, 0.0); // #define MSG_GRASS_SET_PARAM 42666
		}
	}
	//Loading background model=============================================================
	if(CheckAttribute(loc, "models.back") == true)
	{
		if(LocLoadModel(loc, "models.back", Whr_GetInsideBack()) == 0)
		{
			Trace("LocationLoader: not loaded back model location." + sat + ", id = " + loc.id);
		}		
	}

	ReloadProgressUpdate();

	
	//--> проверяем наличие контры для установки нужного патча
	string smg = "";
	if (loc.type == "seashore" || loc.type == "mayak") 
	{
		makearef(st, loc.models.always);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);	
			sat = GetAttributeName(at);
			if(st.(sat) == "smg")
			{
				smg = "smg";
                                break;
			}
		}			
	}
	//<-- проверяем наличие контры для установки нужного патча
	
	//Loading day/night models=============================================================
	if(Whr_IsDay() != 0)	//Day
	{
		makearef(st, loc.models.day);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			sat = GetAttributeName(at);
			if((sat != "charactersPatch") && (sat != "jumpPatch") && (sat != "lights"))
			{
				sat = "models.day." + sat;
				res = LocLoadModel(loc, sat, "");
				if(res == 0)
				{
                    Trace("LocationLoader: not loaded model location." + sat + ", id = " + loc.id);
					Trace("Unload location.");
					UnloadLocation(loc);
					return 0;
				}
			}
			ReloadProgressUpdate();
		}
		//Loading patches
		if(CheckAttribute(loc, "models.day.charactersPatch") != 0)
		{
			res = SendMessage(loc, "ls", MSG_LOCATION_SET_CHRS_PATCH, loc.models.day.charactersPatch + smg);
			if(res == 0)
			{
				Trace("Character patch not loaded!");
				UnloadLocation(loc);
				return 0;
			}
		}
		else
		{
			Trace("Character patch not setting for location.models.day.charactersPatch!");
			UnloadLocation(loc);
			return 0;
		}
		if(CheckAttribute(loc, "models.day.jumpPatch") != 0)
		{
			SendMessage(loc, "ls", MSG_LOCATION_SET_JMP_PATCH, loc.models.day.jumpPatch);
		}
	}
	else	//Night
	{
		makearef(st, loc.models.night);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			sat = GetAttributeName(at);
			if((sat != "charactersPatch") && (sat != "jumpPatch") && (sat != "lights"))
			{
				sat = "models.night." + sat;
				res = LocLoadModel(loc, sat, "");
				if(res == 0)
				{
                    Trace("LocationLoader: not loaded model location." + sat + ", id = " + loc.id);
					Trace("Unload location.");
					UnloadLocation(loc);
					return 0;
				}
                ReloadProgressUpdate();
			}
		}
		
		//Loading patches
		if(CheckAttribute(loc, "models.night.charactersPatch") != 0)
		{			
			res = SendMessage(loc, "ls", MSG_LOCATION_SET_CHRS_PATCH, loc.models.night.charactersPatch + smg);
			if(res == 0)
			{
				Trace("Character patch not loaded!");
				UnloadLocation(loc);
				return 0;
			}
		}
		else
		{
			Trace("Character patch not setting for location.models.night.charactersPatch!");
			UnloadLocation(loc);
			return 0;
		}
		if(CheckAttribute(loc, "models.night.jumpPatch") != 0)
		{
			SendMessage(loc, "ls", MSG_LOCATION_SET_JMP_PATCH, loc.models.night.jumpPatch);
		}
	}
	
	//Entry models=========================================================================
	if(LocIsEntryLocation(loc) == true)
	{
		makearef(st, loc.models.entry);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			sat = "models.entry." + GetAttributeName(at);
			res = LocLoadModel(loc, sat, "");
			if(res == 0)
			{
                Trace("LocationLoader: not loaded model location." + sat + ", id = " + loc.id);
				Trace("Unload location.");
				UnloadLocation(loc);
				return 0;
			}
		}
	}

	ReloadProgressUpdate();

	//Locators=============================================================================
	Sea.MaxSeaHeight = Whr_SetLocationMaxSeaHeight();//Mett: old 0.5;
	if(CheckAttribute(loc, "MaxWaveHeigh"))
	{
		if(stf(loc.MaxWaveHeigh) > 0.0)
		{
			Sea.MaxSeaHeight = stf(loc.MaxWaveHeigh);
		}
	}
	//Locator's radiuses
	int j, k, gnum, lnum;
	aref locator_rad;
	if(CheckAttribute(loc, "locators_radius") != 0)
	{
		makearef(locator_rad, loc.locators_radius);
		gnum = GetAttributesNum(locator_rad);
		for(j = 0; j < gnum; j++)
		{
			//Group radius
			aref rdgrp = GetAttributeN(locator_rad, j);
			string rdgname = GetAttributeName(rdgrp);			
			float rad = MakeFloat("" + rdgrp);
			SetLocatorGroupRadius(loc, rdgname, rad);
			//Some locators radius
			lnum = GetAttributesNum(rdgrp);
			for(k = 0; k < lnum; k++)
			{
				aref rdloc = GetAttributeN(rdgrp, k);
				string rdlname = GetAttributeName(rdloc);
				rad = MakeFloat("" + rdloc);
				SetLocatorRadius(loc, rdgname, rdlname, rad);
			}
		}
	}
	//Updatelocators=======================================================================
	SendMessage(loc, "l", MSG_LOCATION_UPDATELOCATORS);
	loadedLocation = loc;

	ReloadProgressUpdate();

	//Lights===============================================================================
	LocationSetLights(loc);
	//Particles============================================================================
	CreateParticles(loc);
	//Ships================================================================================
	if (isNoBoarding && loc.environment.sea == "true") 
	{
		LocLoadShips(loc); // boal fix!!!!!!!!
	}	
	//Animals===========================================================================
	CreateAnimals(loc);
	//Characters===========================================================================
	LoginCharactersInLocation(loc);
	//CheckEnemyLocators(loc);
	//Main character options===============================================================
	ref mainCharacter = GetMainCharacter();
	if(IsEntity(mainCharacter) == 0)
	{
		Trace("Main character not loaded!");
		UnloadLocation(loc);
		return 0;		
	}
	AddCharacterLocatorGroup(mainCharacter, "reload");
	AddCharacterLocatorGroup(mainCharacter, "camdetector");
	AddCharacterLocatorGroup(mainCharacter, "item");
	AddCharacterLocatorGroup(mainCharacter, "randitem");
	AddCharacterLocatorGroup(mainCharacter, "box");
	AddCharacterLocatorGroup(mainCharacter, "teleport");
	AddCharacterLocatorGroup(mainCharacter, "event");

	ReloadProgressUpdate();
	
	SendMessage(loc, "ll", MSG_LOCATION_VIEWSTATEBARS, bDrawBars);

 	//Camera===============================================================================
	CreateEntity(&locCamera, "locationcamera");
	SendMessage(&locCamera, "li", MSG_CAMERA_SETTARGET, mainCharacter);
	locCameraFollow();
	PChar.CameraHoldPos = false; //boal
	if(CheckAttribute(loc, "lockCamAngle") == true && !Whr_CheckNewBoardingDeck())// в новых абордажках отвязана камера
	{
		float lockCamAngle = stf(loc.lockCamAngle);
		if(lockCamAngle < -1.5) lockCamAngle = -1.5;
		if(lockCamAngle > 1.5) lockCamAngle = 1.5;
		if(CheckAttribute(loc, "type"))
		{
			if(loc.type == "deck" || loc.type == "deck_fight" || loc.type == "residence") lockCamAngle = 0.2;
		}
		SendMessage(&locCamera, "lf", MSG_CAMERA_MOVE, lockCamAngle);
	}
    SetCamShuttle(loc);

	float fRatio = stf(showWindow.right)/stf(showWindow.bottom);
	locCamera.maxRadius = Bring2RangeNoCheck(4.5, 8.0, 16.0/9.0, 32.0/9.0, fRatio);

	if(!CheckAttribute(&locCamera, "zoom"))
	{
		locCamera.zoom = 0.75;
	}
	SendMessage(&locCamera, "lf", MSG_CAMERA_SET_RADIUS, stf(locCamera.maxRadius)*stf(locCamera.zoom)); // belamour высота камеры
	SetEventHandler("Control Activation","locCameraSwitch",1);
	/*if(isNoBoarding) мешало релоду на абордаже и каюте*/ SetEventHandler("Control Activation","chrCharacterKeys",1);
    if(!LAi_IsCharacterControl(PChar)) SendMessage(&locCamera, "ll", MSG_CAMERA_SPECIALMODE, true); // Не доворачивать за камерой

	bool crtAnimals;

	if(CheckAttribute(loc, "type"))
	{
		if(loc.type == "jungle")
		{
			//Орёл
			if(rand(100) < 80)
			{
				crtAnimals = true;
				if(!IsDay()) crtAnimals = false;
				if(Whr_GetWindSpeed() > 10.0) crtAnimals = false;
				if(Whr_IsRain()) crtAnimals = false;
				if(Whr_IsStorm()) crtAnimals = false;
				if(Whr_GetFogDensity() > 0.008) crtAnimals = false;
				if(crtAnimals)
				{
					SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "AddEagle");
				}
			}
			//Ящерецы
			if(rand(100) < 95)
			{
				crtAnimals = true;
				if(Whr_IsStorm()) crtAnimals = false;
				if(Whr_GetFogDensity() > 0.008) crtAnimals = false;
				if(Whr_GetWindSpeed() > 10.0) crtAnimals = false;
				if(crtAnimals)
				{
					SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "AddLizards");
				}
			}
			//Крысы
			if(rand(100) < 50)
			{
				if(IsDay())
				{
					if(rand(100) < 50)
					{
						SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 1 + rand(2));
					}
				}else{
					SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 1 + rand(4));
				}
			}
		}
		if(loc.type == "Dungeon")
		{
			//Крысы
			if(rand(100) < 95)
			{
				SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 16 + rand(16));
			}
			
			Achievment_SetStat(40, 1);
		}
		if(loc.type == "jail")
		{
			//Крысы
			if(rand(100) < 75)
			{
				SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 1 + rand(3));
			}
		}
		if(loc.type == "town")
		{
			// Почему бы орлу не летать над городом
			if(rand(100) < 60)
			{
				crtAnimals = true;
				if(!IsDay()) crtAnimals = false;
				if(Whr_GetWindSpeed() > 10.0) crtAnimals = false;
				if(Whr_IsRain()) crtAnimals = false;
				if(Whr_IsStorm()) crtAnimals = false;
				if(Whr_GetFogDensity() > 0.008) crtAnimals = false;
				if(crtAnimals)
				{
					SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "AddEagle");
				}
			}
			//Крысы
			if(rand(100) < 35)
			{
				crtAnimals = true;
				if(Whr_IsStorm()) crtAnimals = false;
				if(Whr_GetFogDensity() > 0.008) crtAnimals = false;
				if(Whr_GetWindSpeed() > 10.0) crtAnimals = false;
				if(crtAnimals)
				{
					if(IsDay())
					{
						SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 1 + rand(2));
					}else{
						SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 2 + rand(4));
					}
				}
			}
		}

		// boal -->
        if (loc.id == "My_Deck_Medium" || loc.id == "My_Deck")
        {
            SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 2 + rand(3));
        }
        // boal <--
		// -->> ugeen
		if(loc.type == "seashore" || loc.type == "port")
		{		
			SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddCrabs", rand(5) - 1);
		}	
		// <<-- ugeen
	}

    // boal debug info -->
	if (bLocatorShow)
	{
        ShowAllLocators();
    }
    // boal debug info <--
	//DumpAttributes(loc);
	//SendMessage(Sound,"lf",MSG_SOUND_SET_MASTER_VOLUME,1.0);
	
	//VisibleLocatorsGroup("torchlightes_o", 0.1, 15.0, 55, 0, 0, 255);
	/*
	VisibleLocatorsGroup("candles", 1.0, 15.0, 255, 255, 255, 55);
	VisibleLocatorsGroup("candles_medium", 1.0, 15.0, 255, 255, 255, 55);
	VisibleLocatorsGroup("chandeliers", 1.0, 15.0, 255, 128, 0, 128);
	VisibleLocatorsGroup("torchlightes", 1.0, 15.0, 255, 255, 155, 0);
	VisibleLocatorsGroup("outside", 1.0, 15.0, 255, 155, 155, 255);	
	VisibleLocatorsGroup("fonar", 1.0, 15.0, 255, 155, 255, 155);
	VisibleLocatorsGroup("heaters", 1.0, 15.0, 255, 155, 255, 155);
	VisibleLocatorsGroup("incas_light", 1.0, 15.0, 255, 155, 255, 255);
	VisibleLocatorsGroup("incas_sky", 1.0, 15.0, 255, 0, 255, 255);
	*/
	Item_OnLoadLocation(loc.id);

	ReloadProgressUpdate();

	//ResumeAllSounds();
	//SetSchemeForLocation(loc);

	if (isNoBoarding) { Island_Start(); }

	if(CheckAttribute(&mainCharacter, "lastFightMode") != 0)
	{
		if(sti(mainCharacter.lastFightMode) != 0)
		{
			if(CheckAttribute(loc, "noFight") && loc.noFight != "1") //eddy. для переходов в режиме боя, чтобы не було эррорлога. счас только при читовых телепортах вылазит, сам смотри.
			{
				LAi_InstantFightMode(mainCharacter);
			}
		}
	}
	if (loc.type == "residence") //eddy. в резиденции нельзя дебоширить
	{
		if (!IsLocationCaptured(loc.id) && !CheckAttribute(loc, "boarding"))// захват города
		{
			LAi_LockFightMode(Pchar, true);
		}
	}
	
	// фонарь у гг
	if(CheckAttribute(pchar, "LanternOnChar") != 0)
	{
		if(CheckAttribute(pchar, "HandLight")){
			SendMessage(pchar, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", 9, "lantern_belton", "Lantern_belt",1);
			SendMessage(pchar, "lss", MSG_CHARACTER_EX_MSG, "HandLightOn", "lantern");
		} else {
			SendMessage(pchar, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", 9, "lantern_beltoff", "Lantern_belt",1);
			SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "HandLightOff");
		}
	}
	
	// belamour cle 1.3 маркеры направления
	if(CheckAttribute(loc, "QuestPointer"))
	{
		aref arMrk, arGr, arLctr, arLct;
		makearef(arMrk, loc.QuestPointer);
		int	QtyG = GetAttributesNum(arMrk);
		for (int n=0; n<QtyG; n++)
		{
			arGr = GetAttributeN(arMrk, n);
			string group = GetAttributeName(arGr);
			makearef(arLctr, loc.QuestPointer.(group));
			int	QtyL = GetAttributesNum(arLctr);
			for (int jj=0; jj<QtyL; jj++)
			{
				arLct = GetAttributeN(arLctr, jj);
				string locator = GetAttributeName(arLct);
				SetQuestPointer(group, locator);
			}
		}
	}

	// ADDED BY VANO
	// сбрасываем цвет фона на 0
	Render.BackColor = 0;
	// выключаем эффект моря
	Render.SeaEffect = false;
	// включаем плавание в локации
	loc.Swimming = true;
	// 14.07.2007 - отключаем подводную часть
	Sea.UnderWater = false;
	
	// если мы под водой
	if(CheckAttribute(loc, "underwater") != 0)
	{
		if (sti(loc.underwater))
		{
			aref arWeather = GetCurrentWeather();

			// отключаем плавание - персонаж ходит в воде
			loc.Swimming = false;

			// включаем эффект воды
			Render.SeaEffect = true;
			// я не помню, тут 0.02 или 0.002 должно быть, если сильно колбасит - то надо уменьшить :)
			Render.SeaEffectSize = 0.003;
			Render.SeaEffectSpeed = 3.0;
			// ставим цвет фона равным цвету тумана
			Render.BackColor = arWeather.Fog.Color;

			// 14.07.2007 - включаем подводную часть в море
			Sea.UnderWater = true;

			Loc.Caustic.scale = 0.2;
			Loc.Caustic.fogdensity = 0.00;
			Loc.Caustic.distance = 30.0;
			Loc.Caustic.color = argb(128, 255, 255, 255);
			Loc.Caustic.speed = 10.0;
			
			SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "LoadCaustic");
			SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "EnableCaustic", 1);
		}
	}
	// ADDED BY VANO
//	else
//	{
//		if(bSeaActive && bAbordageStarted)
//		{
//			WhrCreateSeaEnvironment();
//		}			
//	}		
		
	/////
	/* if (CheckAttribute(loc, "time"))
	{
		int time = sti(loc.time);
		WaitDate("", 0, 0, 0, 0, time); //крутим время
		RecalculateJumpTable();
	} */
	/////
	// Sith
	if (loc.id == "Shore79")
	{
		DeleteParticles();//фикс костра на Кабо-Рохо
	}	
	// Jason
	if (loc.id == "Shore67")
	{	
		if (CheckAttribute(loc, "hell_fire_1"))
		{
			CreateLocationParticles("shipfire", "quest", "fire3", 0.5, 0, 0, "");
			CreateLocationParticles("item", "quest", "top", 1.0, 0, 0, "");
			for (i=1; i<=25; i++)
			{
				CreateLocationParticles("torch", "item", "fire"+i, 0.1, 0, 0, "");
			}
		}
		if (CheckAttribute(loc, "hell_fire_2"))
		{
			CreateLocationParticles("shipfire", "quest", "entrance", 0.5, 0, 0, "");
			CreateLocationParticles("item", "quest", "rock", 1.0, 0, 0, "");
			for (i=26; i<=40; i++)
			{
				CreateLocationParticles("torch", "item", "fire"+i, 0.1, 0, 0, "");
			}
		}
		if (CheckAttribute(loc, "hell_fire_3"))
		{
			CreateLocationParticles("item", "quest", "wall", 1.0, 0, 0, "");
			CreateLocationParticles("shipfire", "quest", "fire1", 0.5, 0, 0, "");
			CreateLocationParticles("shipfire", "quest", "fire2", 0.5, 0, 0, "");
		}
	}
	// Jason 010912
	if (loc.id == "Temple_great")
	{	
		if (CheckAttribute(loc, "sun")) CreateLocationParticles("shadowstar", "item", "button01", 2, 0, 0, "");
		if (CheckAttribute(loc, "rain")) CreateLocationParticles("fountain", "item", "button02", 2, 0, 0, "");
		if (CheckAttribute(loc, "fire")) CreateLocationParticles("torch", "item", "button03", 2, 0, 0, "");
	}
	// Jason 050912
	if (loc.id == "Tenochtitlan" && CheckAttribute(loc, "setquestofficers"))
	{
		float locx, locy, locz;
		for(int off=1; off<=3; off++)
		{
			int idx = GetOfficersIndex(pchar, off);
			if(idx < 0) continue;
			ref sld = &Characters[idx];
			if (CheckAttribute(sld, "quest.teleportation"))
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(sld, "Tenochtitlan", "officers", LAi_FindNearestLocator("officers", locx, locy, locz));
			}
		}
	}
	if (CheckAttribute(loc, "canteleport"))
	{	
		CreateLocationParticles("shadowstar", "camera", "dolly", 1.15, 0, 0, "");
	}
	if (loc.id == "KhaelRoa_Treasure_Alcove") // калеуче
	{	
		CreateLocationParticles("signstar", "teleport", "teleport6", 0.3, 0, 0, "");
		CreateLocationParticles("signstar", "teleport", "teleport6", 0.6, 0, 0, "");
		CreateLocationParticles("signstar", "teleport", "teleport6", 0.9, 0, 0, "");
		CreateLocationParticles("signstar", "teleport", "teleport6", 1.2, 0, 0, "");
		CreateLocationParticles("signstar", "teleport", "teleport6", 1.5, 0, 0, "");
		CreateLocationParticles("signstar", "teleport", "teleport6", 1.8, 0, 0, "");
		CreateLocationParticles("signstar", "teleport", "teleport6", 2.1, 0, 0, "");
	}
	// Addon 2016-1 Jason Пиратская линейка
	if (loc.id == "Judgement_dungeon_09")
	{	
		for (i=1; i<=112; i++) // горячие фонтанчики
		{
			if(i == 102) continue;
			CreateLocationParticles("Fountain", "item", "fontain"+i, 0.5, 0, 0, "");
			CreateLocationParticles("waterfall", "item", "fontain"+i, -2.0, 0, 0, "");
		}
		for (i=1; i<=10; i++)
		{
			CreateLocationParticles("large_smoke", "item", "smoke"+i, 1.0, 0, 0, ""); // дым
			CreateLocationParticles("large_smoke", "item", "smoke"+i, 1.0, 0, 0, ""); // дым
		}
		DoQuestFunctionDelay("Mtraxx_RetributionHellSplash", 1.5); // гейзеры
	}
	if (loc.id == "Judgement_dungeon_10")
	{
		DoQuestFunctionDelay("Mtraxx_RetributionHellSplashStatic", 1.0);
		for (i=1; i<=8; i++) // статичные гейзеры
		{
			CreateLocationParticles("waterfall", "item", "fontain"+i, 1, 0, 0, "");
		}
		for (i=1; i<=6; i++) // гейзеры
		{
			string sTemp = "Mtraxx_RetributionHellSplash"+i;
			DoQuestFunctionDelay(sTemp, 1.5);
		}
	}
	// belamour CLE опыт за исследования
	string TownId = loc.id;
	if(CheckAttribute(loc, "type") && loc.type == "town" && CheckAttribute(worldMap, "labels."+(TownId)+".type"))
	{
		if(!CheckAttribute(pchar, "questTemp.TownVisit."+TownId)) 
		{
			notification(StringFromKey("locations_loader_1") + XI_ConvertString("Colony"+ loc.townsack + "Gen") + "!", "Discovery");
			pchar.questTemp.TownVisit.(TownId) = true;
			pchar.questTemp.TownVisit.counter = sti(pchar.questTemp.TownVisit.counter) + 1;
			AddCharacterExpToSkill(pchar, "Sailing", 15.0);
		}
		if(!CheckAttribute(pchar, "questTemp.TownVisit.counter.All") && sti(pchar.questTemp.TownVisit.counter) == 28)
		{
			notification(StringFromKey("locations_loader_2"), "none");
			AddCharacterExpToSkill(pchar, "Sailing", 200.0);
			pchar.questTemp.TownVisit.counter.All = true;
		}
	}
	if (TownId == "KhaelRoa_port" ||
		TownId == "Shore65" || 
		TownId == "LostShipsCity_town" || 
		TownId == "IslaMona_town" ||
		TownId == "Shore74" ||
		TownId == "IslaDeCoche_Grot")
	{
		if(!CheckAttribute(pchar, "questTemp.MysteriousPlaceVisit."+TownId)) 
		{
			notification(StringFromKey("locations_loader_3"), "none");
			pchar.questTemp.MysteriousPlaceVisit.(TownId) = true;
			AddCharacterExpToSkill(pchar, "Sailing", 25.0);
		}
	}
	
	return 1;
}

void LocationSetLights(ref loc)
{
	SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "DelAllLights");

	string lightPath,lightName,lightGroupName;
	string sat;
	aref st,at,lit,lit1;
	int i,num, lnum,j;
	bool bOk = false;

	if(Whr_IsLight() == 0)
	{
		if(CheckAttribute(loc, "fonarlights") == true) lightPath = "models.night.lights"; // включаем фонари всегда в нужных локах
		else lightPath = "models.day.lights";
	}else{
		lightPath = "models.night.lights";
	}

	if(CheckAttribute(loc, lightPath) != 0)
	{
		makearef(st, loc.(lightPath));
		num = GetAttributesNum(st);
		//Trace("numLights = " + num);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			lightGroupName = GetAttributeName(at);
			sat = lightPath + "." + lightGroupName;
			lightName = loc.(sat);
			sat = "locators." + lightGroupName;
            if(lightGroupName == "candles" || lightGroupName == "candles_medium") bOk = true;
            if(bOk && !Whr_CheckInsideLoc() && Whr_IsDay()) continue;
			if(CheckAttribute(loc, sat) != 0)
			{
				makearef(lit, loc.(sat));
				lnum = GetAttributesNum(lit);
				for(j = 0; j < lnum; j++)
				{
					lit1 = GetAttributeN(lit, j);
					float litX = stf(lit1.x);
					float litY = stf(lit1.y);
					float litZ = stf(lit1.z);
					//Trace("     AddLight: " + lightName + " (" + litX + ", " + litY + ", " + litZ);
					SendMessage(loc, "lsfff", MSG_LOCATION_ADD_LIGHT, lightName, litX, litY, litZ);
					if(lightName == "lamp")
					{
						if(!CheckAttribute(loc, "fonarlights") == true)
						SendMessage(loc, "lsfff", MSG_LOCATION_EX_MSG, "AddFlys", litX, litY, litZ);
					}
				}
			}
		}
	}
}

// подмена фонарей на лету в тех локациях где они есть при смене день/ночь
void LocationSubstituteGeometry(ref loc)
{
	aref 	st, at;
	string 	sat, sat1, sat2;
	int		i, num;
	
	if(Whr_IsDay() != 0)	// наступил день - грузим дневной патч фонарей
	{
		makearef(st, loc.models.day);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			sat = GetAttributeName(at);
			if(sat == "fonar" 
				|| sat == "fonars"
				|| sat == "fortVFonarsDay"
				|| sat == "deckBigFonarsDay"
				|| sat == "deckFonarsDay")
			{
				sat1 = "models.day." + sat;
				sat2 = "models.night." + sat;
				SendMessage(loc, "lss", MSG_LOCATION_EX_MSG, "DeleteLocationModel",loc.(sat2));
				LocLoadModel(loc, sat1, "");
			}				
		}		
	}
	else					// наступила ночь - грузим ночной патч
	{
		makearef(st, loc.models.night);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			sat = GetAttributeName(at);
			if(sat == "fonar" 
				|| sat == "fonars"
				|| sat == "fortVBigNight"
				|| sat == "deckMediumBigNight")
			{
				sat1 = "models.night." + sat;
				sat2 = "models.day." + sat;				
				SendMessage(loc, "lss", MSG_LOCATION_EX_MSG, "DeleteLocationModel",loc.(sat2));
				LocLoadModel(loc, sat1, "");
			}				
		}
		SendMessage(loc, "l", MSG_LOCATION_UPDATELOCATORS);	
	}
    // SendMessage(loc, "l", MSG_LOCATION_UPDATELOCATORS);	
}

bool UnloadLocation(aref loc)
{
	// ADDED BY VANO
	// сбрасываем цвет фона на 0
	Render.BackColor = 0;
	// выключаем эффект моря
	Render.SeaEffect = false;
	// ADDED BY VANO
	// 14.07.2007 - отключаем подводную часть
	Sea.UnderWater = false;

	//trace("UnloadLocation(aref loc) " + loc.id);
	DialogExit();

    LocUnloadGrass(loc);
	ref mainCharacter = GetMainCharacter();
	if(SendMessage(&mainCharacter, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode") != 0)
	{
		mainCharacter.lastFightMode = "1";
	}else{
		mainCharacter.lastFightMode = "0";
	}

	Event(EVENT_LOCATION_UNLOAD,"");

	int n;

	DeleteCoastFoamEnvironment();

	bool isNoBoarding = true;
	bool isFort = false;
	if(CheckAttribute(loc, "boarding") == true)
	{
		if(loc.boarding == "true") isNoBoarding = false;
		if(loc.boarding == "fort")
		{
			isNoBoarding = false;
			isFort = true;
		}
	}
	if(isNoBoarding)
	{
		DeleteParticles();
		//DeleteClass(&Island);
		DeleteAnimals();
		DeleteSea();
		DeleteWeather();
		DeleteShipEnvironment(); 
		for(n = 0; n < locNumShips; n++) {DeleteClass(locShips[n]);}
		locNumShips = 0;
	}
	else
	{
        //DeleteParticles();  // фикс костров
		SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
	}
	if(isFort)
	{
		DeleteSea();
		DeleteWeather();
	}

	DelEventHandler("Control Activation","locCameraSwitch");
	/*if(isNoBoarding) fix 31.03.05 */ DelEventHandler("Control Activation","chrCharacterKeys");
	Item_OnUnLoadLocation();
	LocAi_Release();
	DeleteClass(&loc);
	DeleteClass(&locCamera);
	return true;
}

bool LocCheckDLight(ref loc)
{
	bool checkDLight = true;

	if (CheckAttribute(loc, "type"))
	{
		//trace("location type : " + loc.type);
		if(loc.type == "tavern"
			|| loc.type == "house"
			|| loc.type == "residence"
			|| loc.type == "shop"
			|| loc.type == "shipyard"
			|| loc.type == "church" 
			|| loc.type == "jail" 
			|| loc.type == "dungeon"
			// || loc.type == "cave"
			|| loc.type == "LSC_inside"
			// || loc.type == "fort_attack"
//			|| loc.type == "fort"
			|| loc.type == "ammo"
			|| loc.type == "europe"
			// || loc.type == "teno"
			|| loc.type == "teno_inside"
			|| loc.type == "alcove"
			|| loc.type == "boarding_cabine"
			|| loc.type == "deck"
			// || loc.type == "deck_fight"
			|| loc.type == "underwater")
			// || Whr_CheckDeck())
		{
			checkDLight = false;
			// для внутрянок корабля сначала надо АОшки запечь
			// if(loc.id == "My_Campus" || loc.id == "My_Deck" || loc.id == "My_Deck_Medium" || loc.id == "Deck_Near_Ship") checkDLight = true;
			if(loc.id == "Ship_deck_Medium_trade" 
				|| loc.id == "Ship_deck_Medium_war"
				|| loc.id == "Ship_deck_Low"
				|| loc.id == "Deck_Near_Ship"
				|| loc.id == "Deck_Near_Ship_Medium_trade"
				|| loc.id == "Deck_Near_Ship_Medium_war"
				|| loc.id == "Deck_Near_Ship_Memento"
				|| loc.id == "Ship_deck_Memento"
				|| loc.id == "Quest_Ship_deck_Medium_trade"
				|| loc.id == "Deck_Near_Ship")
			checkDLight = true;
		}
	}
	if (CheckAttribute(loc, "id")) // фильтр отдельных локаций
	{
		if(loc.id == "Cartahena_Cave"
			|| loc.id == "Curacao_Cave"
			|| loc.id == "IslaMona_Cave"
			|| loc.id == "Maracaibo_Cave"
			|| loc.id == "SantaCatalina_Cave"
			|| loc.id == "SantaQuiteria_Cave"
			|| loc.id == "Marigo_Cave"
            || loc.id == "Serpentine_cave"
            || loc.id == "Bermudes_Cavern"
            || loc.id == "Ksochitam_Grot"
            || loc.id == "Antigua_Grot"
			// || loc.id == "BOARDING_SMALL_DECK"
			// || loc.id == "BOARDING_MEDIUM_DECK"
			// || loc.id == "BOARDING_BIG_DECK"
			|| loc.id == "Boarding_Cargohold"
			|| loc.id == "Boarding_Campus"
			|| loc.id == "Boarding_GunDeck"
			|| loc.id == "IslaMona_Basement"
			|| loc.id == "Quest_Deck_Medium" // тутор гандек
			|| loc.id == "Quest_Campus" // тутор кк
			|| loc.id == "Quest_Deck") // тутор трюм
		{
			checkDLight = false;
		}
	}
	return checkDLight;
}



bool LocLoadModel(aref loc, string sat, string addition)
{
	//Пропустим пустое имя
	if(loc.(sat) == "") return true;
	//Считываем параметры модельки
	string attr, attr1;
	bool res;
	bool dLight;
	string tech = "";
	int level = 10;
	
    attr = sat + ".level";
    if(CheckAttribute(loc, attr)) 
	{	
		level = MakeInt(loc.(attr));
		if(!bSeaActive) level += 10;
	}	
	
	int dynamicLightsOn = sti(InterfaceStates.DYNAMICLIGHTS); //  belamour динамический свет
	attr = sat + ".tech";
	if(CheckAttribute(loc, attr)) tech = loc.(attr);
	if(tech == "LocationModelBlend" && dynamicLightsOn) tech = "LocationModelBlendLighting";
	dLight = LocCheckDLight(loc);
	//Trace("Load model: " + loc.(sat) + " lights :" + dynamicLightsOn + " tech :" + tech + " dLight :" + dLight);
	
	int bOk;
	if(!dLight) // внутренние локи
	{		
		bOk = 0;	
		attr = sat + ".lights";
		if(CheckAttribute(loc, attr)) 
		{
			bOk = MakeInt(loc.(attr)); 
		}		
	}	
	else // внешние
	{	
		if(!CheckAttribute(loc, attr) && dynamicLightsOn && dLight)
		{
			tech = "DLightModel"; 
		}				
		bOk = dLight && dynamicLightsOn; 
	}
	
    //Грузим модельку
	res = SendMessage(loc, "lssll", MSG_LOCATION_ADD_MODEL, loc.(sat) + addition, tech, level, bOk);
	if(res == 0) return 0;
	//Устанавливаем флаги
	object mdl;
	if(SendMessage(loc, "le", MSG_LOCATION_GET_MODEL, &mdl) != 0)
	{
		// belamour флаг для SP2 на каймане
		if(loc.id == "Caiman_Jungle_01" && loc.models.always.jungle == "Jungle_SP2")
		{
			SetTownFlag(loc, &mdl);
		}
		string sAreal = GiveArealByLocation(loc);
		if (sAreal != "none")
		{
			string sCity = GetCityNameByIsland(sAreal);
			if (sCity != "none")
			{
				SetTownFlag(loc, &mdl); // ugeen
			}
		}
	}
	// Проверяем на пену
	attr = sat + ".foam";
	if(CheckAttribute(loc, attr) != 0)
	{
		if (loc.(attr) == "1")
		{
			/*if (!isEntity(&Island))
			{
				CreateEntity(&Island, "Island");
				LayerAddObject(REALIZE, &Island, 65529);
			}

			SendMessage(&Island, "liss", MSG_LOCATION_ADD_MODEL, &mdl, loc.id, loc.filespath.models);*/
			//Trace("<> Model " + attr + ", have a foam!!!");
		}
	}
	//Ставим модификаторы
	//locator
	attr = sat + ".locator.group";
	Trace("> " + attr);
	if(CheckAttribute(loc, attr) != 0)
	{
		res = 0;
		attr1 = sat + ".locator.name";
		Trace("> " + attr1);
		if(CheckAttribute(loc, attr1) != 0)
		{
			res = SendMessage(loc, "lss", MSG_LOCATION_MODEL_SET_POS, loc.(attr), loc.(attr1));
		}
		if(res == 0) 
		{
			Trace("Can't set locator modifier to model: " + loc.(sat));
		}
	}
	//rotate
	attr = sat + ".rotate";
	if(CheckAttribute(loc, attr) != 0)
	{        
        float dx = 0.0; 
        float dy = 0.0;
        float dz = 0.0;
        attr1 = attr + ".dx";
        if(CheckAttribute(loc, attr1) != 0) dx = MakeFloat(loc.(attr1));
        attr1 = attr + ".dy";
		if(CheckAttribute(loc, attr1) != 0) dy = MakeFloat(loc.(attr1));
		attr1 = attr + ".dz";
		if(CheckAttribute(loc, attr1) != 0) dz = MakeFloat(loc.(attr1));
        res = SendMessage(loc, "lfff", MSG_LOCATION_MODEL_SET_ROT_ANGLE, dx, dy, dz);
		if(res == 0) Trace("Can't set rotate modifier to model: " + loc.(sat));
        
		float x, y, z;
		attr1 = attr + ".x";
		if(CheckAttribute(loc, attr1) != 0) x = MakeFloat(loc.(attr1));
		attr1 = attr + ".y";
		if(CheckAttribute(loc, attr1) != 0) y = MakeFloat(loc.(attr1));
		attr1 = attr + ".z";
		if(CheckAttribute(loc, attr1) != 0) z = MakeFloat(loc.(attr1));
		res = SendMessage(loc, "lfff", MSG_LOCATION_MODEL_SET_ROT, x, y, z);
		if(res == 0) Trace("Can't set rotate modifier to model: " + loc.(sat));
	}	
	//uvslide
	attr = sat + ".uvslide";
	if(CheckAttribute(loc, attr) != 0)
	{
		float u0, v0, u1, v1;
		u0 = 0; v0 = 0; u1 = 0; v1 = 0;
		attr1 = attr + ".u0";
		if(CheckAttribute(loc, attr1) != 0) u0 = MakeFloat(loc.(attr1));
		attr1 = attr + ".v0";
		if(CheckAttribute(loc, attr1) != 0) v0 = MakeFloat(loc.(attr1));
		attr1 = attr + ".u1";
		if(CheckAttribute(loc, attr1) != 0) u1 = MakeFloat(loc.(attr1));
		attr1 = attr + ".v1";
		if(CheckAttribute(loc, attr1) != 0) v1 = MakeFloat(loc.(attr1));
		res = SendMessage(loc, "lffff", MSG_LOCATION_MODEL_SET_UVS, u0, v0, u1, v1);
		if(res == 0) Trace("Can't set uvslide modifier to model: " + loc.(sat));
	}
	//rotate
	attr = sat + ".lamps";
	if(CheckAttribute(loc, attr) != 0)
	{
		if(loc.(attr) != "0")
		{
			SendMessage(loc, "l", MSG_LOCATION_MODEL_LAMPS);
		}
	}
	//reflection
	attr = sat + ".reflection";
	if(CheckAttribute(loc, attr) != 0)
	{
		SendMessage(loc, "lf", MSG_LOCATION_MODEL_REFLECTION, stf(loc.(attr)));
	}
	//reflection
	attr = sat + ".sea_reflection";
	if(CheckAttribute(loc, attr) != 0)
	{
		LayerAddObject(SEA_REFLECTION2, &mdl, 4);
	}
	return 1;
}

float GetAngleY(float x, float z)
{
	return atan2(x,z);
}

void LocLoadShips(ref Location)
{
	int		i, j;
	int		iShipsType[MAX_SHIPS_IN_LOCATION];
	int		iShipType, iMainCharacterShipType;
	aref	locator_ships,locator_otherships;
	aref	locator;

	locNumShips = 0;

	bool bMainCharacterHere = LocIsEntryLocation(Location);

	ref rPlayer = GetMainCharacter();
	
	if (!CheckAttribute(Location, "locators")) 
	{
		//Trace("LocLoadShips: Can't find Location.locators in location: " + Location.id);
		return;
	}

	int iMCI = GetMainCharacterIndex();

	if(IslamonaCreateShips(Location)) return;

	if (!CheckAttribute(Location, "locators.ships"))
	{
		Trace("LocLoadShips: Can't find Location.locators.ships in location: " + Location.id); return;
	}
	if (!CheckAttribute(Location, "locators.ships_other"))
	{
		Trace("LocLoadShips: Can't find Location.locators.ships_other in location: " + Location.id); return;
	}
	makearef(locator_ships, location.locators.ships);
	makearef(locator_otherships, location.locators.ships_other);

	iMainCharacterShipType = sti(Characters[iMCI].Ship.Type);

	// create our characters ships
	if (bMainCharacterHere)
	{
		for (i=0;i<COMPANION_MAX;i++)
		{
			if (locNumShips >= MAX_SHIPS_IN_LOCATION) continue;
			int iCompanionIndex = GetCompanionIndex(&Characters[iMCI],i);
			if (iCompanionIndex==-1) continue;
			ref rCompanion = GetCharacter(iCompanionIndex);
			SetCharacterShipLocation(&Characters[iCompanionIndex],Location.id);
			iShipType = sti(Characters[iCompanionIndex].Ship.Type);
			if (iShipType == SHIP_NOTUSED) continue;
			iShips[locNumShips] = iCompanionIndex;
			iShipsType[locNumShips] = 0;
			locNumShips++;
			Characters[iCompanionIndex].Ship.Stopped = true; // boal fix
		}
	}

	// create other quest characters ships
	for (i=1;i<MAX_CHARACTERS;i++)  // начало не с 0
	{
		if (i == iMCI) continue;
		if (locNumShips >= MAX_SHIPS_IN_LOCATION) continue;
		if (!Character_LocIsEntryLocation(&Characters[i],Location)) continue;
		bool bExist = false;
		for (j=0;j<locNumShips;j++) 
		{
			if (i == iShips[j]) 
			{
				bExist = true; break;
			}
		}
		if (bExist) continue;
		iShipType = sti(Characters[i].Ship.Type);
		if (iShipType == SHIP_NOTUSED) continue;
		iShips[locNumShips] = i; 
		locNumShips++;
		iShipsType[locNumShips] = 1;
		Characters[i].Ship.Stopped = true; // boal fix
	}
//----> Малые суда у пирса
	bool bSmallShip = 0;
	if(CheckAttribute(pchar,"Ship.Type") && sti(pchar.ship.type) != SHIP_NOTUSED) 
	{
		ref refBaseShip = GetRealShip(sti(pchar.ship.type));
		int iShipClass = sti(refBaseShip.Class);
		if(CheckAttribute(Location, "type"))
		{			
			if(Location.type == "town" || Location.type == "port") // фильтр городов
			{
				if (iShipClass > 6) bSmallShip = 1;
				if (iShipClass > 3 && iShipClass < 7  && sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FLEUT)
				{
					if (CheckAttribute(Location, "locators.reload.boat2")) bSmallShip = 1; // проверка наличия локатора для корабля побольше
					else bSmallShip = 0;
				}
			}
		}
		if(CheckAttribute(Location, "id")) // фильтр отдельных локаций
		{
			if(Location.id == "LeFransua_town") bSmallShip = 0;
		}
	}
//<----Малые суда у пирса

	int iNumShips = GetAttributesNum(locator_ships);
	int iNumOtherShips = GetAttributesNum(locator_otherships);
	int iCurNumShips = 0;
	int iCurNumOtherShips = 0;
	for(int n = 0; n < locNumShips; n++)
	{
		bool bContinue = false;
		//switch(iShipsType[locNumShips]) <--- такое было написано сивардом :)
		switch(iShipsType[n])
		{
			case 0:
				if (iCurNumShips >= iNumShips) 
				{ 
					Trace("LocLoadShips: need (ships): " + iCurNumShips + ", but max_num_ships: " + iNumShips);
					bContinue = true; 
				}
				locator = GetAttributeN(locator_ships, iCurNumShips);
				iCurNumShips++;
			break;
			case 1:
				if (iCurNumOtherShips >= iNumOtherShips) 
				{ 
					Trace("LocLoadShips: need (ships_other): " + iCurNumOtherShips + ", but max_num_ships_other: " + iNumOtherShips);
					bContinue = true; 
				}
				locator = GetAttributeN(locator_otherships, iCurNumOtherShips);
				iCurNumOtherShips++;
			break;
		}
		if (bContinue) continue;
		
		if (CreateEntity(&locShips[n], "ship") == 0) break;
		//if (iShips[n] == 0) Log_info("Bad index");
		ref rCharacter = GetCharacter(iShips[n]);
		ref rShip = GetRealShip(sti(rCharacter.Ship.Type));
		//SetTextureForShip(rShip, rCharacter);
		Ship_SetLightsAndFlares(rCharacter);
		//rCharacter.Ship.TexturePath = "";
		rCharacter.Ship.Pos.x = stf(locator.x);
		rCharacter.Ship.Pos.z = stf(locator.z);
		rCharacter.Ship.Ang.y = GetAngleY(stf(locator.vZ.x),stf(locator.vZ.z));
		rCharacter.Ship.stopped = true;
		rCharacter.Ship.Speed.z = 0.0;
		Ship_PrepareShipForLocation(rCharacter);
//----> Малые суда у пирса
		if (bSmallShip == 1)
		{	
			if (n == 0) { DeleteClass(&locShips[n]); }
			else SendMessage(&locShips[n],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
		}			
		else SendMessage(&locShips[n],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
	}

	// load boat 2 location
	if (CheckAttribute(Location, "locators.reload.boat"))
	{
		if (bMainCharacterHere && iMainCharacterShipType != SHIP_NOTUSED && CreateEntity(&locShips[n], "ship"))
		{			
			makearef(locator,Location.locators.reload.boat);
			if (bSmallShip == 1)
			{		
				if (iShipClass > 6)
				{
					makearef(locator,Location.locators.reload.boat);
					rCharacter = GetCharacter(iShips[0]);
				}
				else			
				{
					if (CheckAttribute(Location, "locators.reload.boat2")) // новый локатор для кораблей.
					{
						makearef(locator,Location.locators.reload.boat2);
						rCharacter = GetCharacter(iShips[0]);
					}
					else rCharacter = CharacterFromId("BoatChar");
				}
			}
			else rCharacter = CharacterFromId("BoatChar"); // boal && ugeen		
//<----Малые суда у пирса

			rShip = GetRealShip(sti(rCharacter.Ship.Type));
			rCharacter.Ship.TexturePath = "";
			rCharacter.Ship.Pos.x = stf(locator.x);
			rCharacter.Ship.Pos.z = stf(locator.z);
			rCharacter.Ship.Ang.y = GetAngleY(stf(locator.vZ.x),stf(locator.vZ.z));
			rCharacter.Ship.stopped = true;
			rCharacter.Ship.Speed.z = 0.0;
			rCharacter.nation = sti(rPlayer.nation); // ugeen --> для флага на шлюпке
			if (!CheckAttribute(rPlayer, "Flags.Pirate")) rCharacter.Flags.Pirate = rand(2);
			else 										  rCharacter.Flags.Pirate = rPlayer.Flags.Pirate;
			Ship_SetLightsAndFlares(rCharacter);
			Ship_PrepareShipForLocation(rCharacter);
			SendMessage(&locShips[n],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
			iShips[locNumShips] = rCharacter.index; 
			locNumShips++;
		}
	}
	else 
	{
		if (bMainCharacterHere)
		{
			Trace("LocLoadShips: Can't find boat locator in location: " + Location.id);
		}
	}
}

bool Character_LocIsEntryLocation(ref rCharacter, ref rLocation)
{
	if (CheckAttribute(rCharacter,"location.from_sea") && !LAi_IsDead(rCharacter))  // boal superfix 26/05/06
	{
		if (rCharacter.location.from_sea == rLocation.id) return true;
	}
	return false;
}

bool LocIsEntryLocation(ref Location)
{
	ref rPlayer = GetMainCharacter();
	//Trace("LocIsEntryLocation = " + rPlayer.location.from_sea);
	if(rPlayer.location.from_sea != Location.id) return false;
	return true;
}

void LocLoadGrass(aref loc, string sat)
{
    bool   bOk = true;
	string grs = loc.(sat);
	string tex = "";
	if (GetTime() >=  5.5 && GetTime() < 19.8) {
		if(Whr_IsStorm()) tex = "grass\grasstown.tga.tx";
		else {
			tex = "grass\grasstown.tga.tx";
			if (GetTime() >=  5.5 && GetTime() < 7.0) tex = "grass\grasstownm.tga.tx";
			if (GetTime() >=  18.0 && GetTime() < 19.0) tex = "grass\grasstowne1.tga.tx";
			if (GetTime() >=  19.0 && GetTime() < 19.8) tex = "grass\grasstowne2.tga.tx";
		}
	} else tex = "grass\grasstownn.tga.tx";
	sat = sat + ".texture";
	if(CheckAttribute(loc, sat) != 0)
	{
		if (GetTime() >=  5.5 && GetTime() < 19.8) {
			if(Whr_IsStorm()) tex = "grass\grassshore.tga.tx";
			else {
				tex = loc.(sat);
				if (GetTime() >=  5.5 && GetTime() < 7.0) tex = "grass\grassshorem.tga.tx";
				if (GetTime() >=  18.0 && GetTime() < 19.0) tex = "grass\grassshoree1.tga.tx";
				if (GetTime() >=  19.0 && GetTime() < 19.8) tex = "grass\grassshoree2.tga.tx";
			}
		} else tex = "grass\grassshoren.tga.tx";
	}
	if(CheckAttribute(loc, "texGrass")) 
	{
		if(loc.texGrass == tex)
		{
            if(actLoadFlag == 0) bOk = true;
            else bOk = false;
		}
		else
		{
			loc.texGrass = tex;
			if(CheckAttribute(&InterfaceStates,"GrassDrawDistance") && stf(InterfaceStates.GrassDrawDistance) >= 250.0 && !iGrassQuality)
			{
				bOk = false;
			}
		}
	}
	else
	{
		loc.texGrass = tex;         
		bOk = false;
	}
    
    // Trace("bOk = " + bOk);
    if(!bOk) 
	{
		SendMessage(loc, "lss", MSG_LOCATION_SET_GRS_PATCH, grs, tex); // grass tex update
		object objGrass;
		GetEntity(&objGrass,"grass"));
		float fMaxDist = stf(InterfaceStates.GrassDrawDistance);
		SendMessage(objGrass,"lffffff",42666, 1.0, 1.0, 0.2, 10.0, fMaxDist, 0.0); // grass distance update
	}
}

void LocUnloadGrass(aref loc)
{
    if(CheckAttribute(loc, "texGrass")) DeleteAttribute(loc, "texGrass");
}

#event_handler("LocationTimeUpdate", "LocationTimeUpdateFunc");
void LocationTimeUpdateFunc()
{
	float dltTime = GetEventData();
	if(locDisableUpdateTime) return;
	locTmpTime = locTmpTime + dltTime;
	//if(locTmpTime > 100000.0) locTmpTime = 100000.0;
	// boal -->
	if (locTmpTime > 9)//14)
	{
		/*if (LAi_IsFightMode(GetMainCharacter()) && LAi_group_IsActivePlayerAlarm())
		{
			if (locTmpTime > 29)
			{
				CalcLocalTime(6);
				RefreshLandTime();
			}
		}
		else
		{ */
		    CalcLocalTime(3);
		    RefreshLandTime();
		//}
	}
	// boal <--
}

void CheckAndDisableLocator(ref loc, string locatorname, string checkdestination, bool bDisable)
{
	string sLocTo = "";
	if( CheckAttribute(loc,locatorname) ) {
		sLocTo = loc.fastreload + checkdestination;
		if( loc.(locatorname).go == sLocTo ) {
			if( CheckAttribute(loc,locatorname+".storyloc_disable") ) {
				loc.(locatorname).disable = loc.(locatorname).storyloc_disable;
			} else {
				loc.(locatorname).disable = bDisable;
			}
		}
	}
}

void StoryLineEnableLocator(string locID, string locname, bool bEnable)
{
	int nLoc = FindLocation(locID);
	if( nLoc >= 0 ) {
		if( CheckAttribute(&Locations[nLoc],"reload."+locname) ) {
			chrEnableReloadLocator(locID,Locations[nLoc].reload.(locname).name,bEnable);
		}
		if( CheckAttribute(&Locations[nLoc],"reload."+locname+".disable") ) {
			Locations[nLoc].reload.(locname).storyloc_disable = Locations[nLoc].reload.(locname).disable;
		} else {
			DeleteAttribute(&Locations[nLoc],"reload."+locname+".storyloc_disable");
		}
	}
}

void ShowAllLocators()
{
    VisibleLocatorsGroup("rld", 1.0, 15.0, 255, 128, 200, 120);
    VisibleLocatorsGroup("reload", 1.0, 15.0, 255, 0, 255, 0);
    VisibleLocatorsGroup("goto", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("sit", 1.0, 15.0, 255, 255, 0, 0);
	VisibleLocatorsGroup("lay", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("item", 1.0, 15.0, 255, 255, 0, 255);
    VisibleLocatorsGroup("randitem", 1.0, 15.0, 255, 255, 0, 255);
    VisibleLocatorsGroup("characters", 1.0, 15.0, 155, 255, 0, 0);
    VisibleLocatorsGroup("Merchant", 1.0, 15.0, 105, 0, 255, 125);
    VisibleLocatorsGroup("box", 1.0, 15.0, 255, 0, 255, 255);
    VisibleLocatorsGroup("encdetector", 1.0, 15.0, 255, 0, 255, 255);
    VisibleLocatorsGroup("outside", 1.0, 15.0, 255, 155, 155, 255);
    VisibleLocatorsGroup("officers", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("waitress", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("barmen", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("teleport", 1.0, 15.0, 255, 255, 0, 0);
	VisibleLocatorsGroup("event", 1.0, 15.0, 155, 155, 50, 155);
    VisibleLocatorsGroup("magsteleport", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("greenteleport", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("redteleport", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("blueteleport", 1.0, 15.0, 255, 255, 0, 0);
	VisibleLocatorsGroup("effect", 1.0, 15.0, 155, 0, 200, 155);
    VisibleLocatorsGroup("monsters", 1.0, 15.0, 255, 255, 200, 0);
    VisibleLocatorsGroup("Smugglers", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("camera", 1.0, 15.0, 155, 0, 255, 255);
    VisibleLocatorsGroup("soldiers", 1.0, 15.0, 255, 255, 100, 200);
    VisibleLocatorsGroup("quest", 1.0, 15.0, 255, 255, 200, 200);
    VisibleLocatorsGroup("patrol", 1.0, 15.0, 255, 255, 100, 200);
    VisibleLocatorsGroup("tables", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("windmill", 1.0, 15.0, 255, 255, 255, 125);
}

void HideAllLocators()
{
    HideLocatorsGroup("rld");
    HideLocatorsGroup("reload");
    HideLocatorsGroup("goto");
    
    HideLocatorsGroup("sit");
	HideLocatorsGroup("lay");
    HideLocatorsGroup("item");
    HideLocatorsGroup("randitem");
    HideLocatorsGroup("characters");
    HideLocatorsGroup("Merchant");
    HideLocatorsGroup("box");
    HideLocatorsGroup("encdetector");
    HideLocatorsGroup("outside");
    HideLocatorsGroup("officers");
    HideLocatorsGroup("waitress");
    HideLocatorsGroup("barmen");
    HideLocatorsGroup("teleport");
	HideLocatorsGroup("event");
    HideLocatorsGroup("magsteleport");
    HideLocatorsGroup("greenteleport");
    HideLocatorsGroup("redteleport");
    HideLocatorsGroup("blueteleport");
	HideLocatorsGroup("effect");
    HideLocatorsGroup("monsters");
    HideLocatorsGroup("Smugglers");
    HideLocatorsGroup("camera");
    HideLocatorsGroup("soldiers");
    HideLocatorsGroup("quest");
    HideLocatorsGroup("patrol");
    HideLocatorsGroup("tables");
    HideLocatorsGroup("windmill");
}

bool IslamonaCreateShips(ref Location)
{
	if(Location.id != "Islamona_town") return false;
	
	int		i, j;
	int		iShipsType[MAX_SHIPS_IN_LOCATION];
	int		iShipType, iMainCharacterShipType;
	aref	locator_ships;
	aref	locator;
	ref rCharacter;
	ref rShip;

	locNumShips = 0;

	ref rPlayer = GetMainCharacter();
	int iMCI = GetMainCharacterIndex();
	
	if (!CheckAttribute(Location, "locators.ships"))
	{
		Trace("IslaMonaLoadShips: Can't find Location.locators.ships in location: " + Location.id); return false;
	}
	makearef(locator_ships, location.locators.ships);
	
	iMainCharacterShipType = sti(Characters[iMCI].Ship.Type);
	if (iMainCharacterShipType == SHIP_NOTUSED) return false;
	iShips[locNumShips] = iMCI;
	iShipsType[locNumShips] = 0;
	locNumShips = 1;
	for (i=1;i<MAX_CHARACTERS;i++)  
	{
		if (i == iMCI) continue;
		if (locNumShips >= MAX_SHIPS_IN_LOCATION) continue;
		bool AtIslamona = false;
		if (CheckAttribute(&Characters[i],"location.from_sea") && !LAi_IsDead(Characters[i]))  
		{
			
			if(Characters[i].location.from_sea == "shore75" || Characters[i].location.from_sea == "shore77" || Characters[i].location.from_sea == "islamona_town" || Characters[i].location.from_sea == "shore76") AtIslamona = true;
			if(AtIslamona)
			{
				if(CheckAttribute(&Characters[i],"ShipInStockMan") && Characters[i].ShipInStockMan != "Islamona_carpenter")  AtIslamona = false;
			}
		}
		if(!AtIslamona) continue;
		bool bExist = false;
		for (j=0;j<locNumShips;j++) 
		{
			if (i == iShips[j]) 
			{
				bExist = true; break;
			}
		}
		if (bExist) continue;
		iShipType = sti(Characters[i].Ship.Type);
		if (iShipType == SHIP_NOTUSED) continue;
		iShips[locNumShips] = i; 
		locNumShips++;
		iShipsType[locNumShips] = 1;
	}
	
	int iNumShips = GetAttributesNum(locator_ships);
	int iCurNumShips = 0;
	for(int n = 0; n < locNumShips; n++)
	{
		if (iCurNumShips >= iNumShips) 
		{ 
			Trace("LocLoadShips: need (ships): " + iCurNumShips + ", but max_num_ships: " + iNumShips);
			continue;
		}
		locator = GetAttributeN(locator_ships, iCurNumShips);
		iCurNumShips++;
		if (CreateEntity(&locShips[n], "ship") == 0) break;
		rCharacter = GetCharacter(iShips[n]);
		rShip = GetRealShip(sti(rCharacter.Ship.Type));
		Ship_SetLightsAndFlares(rCharacter);
		rCharacter.Ship.Pos.x = stf(locator.x);
		rCharacter.Ship.Pos.z = stf(locator.z);
		rCharacter.Ship.Ang.y = GetAngleY(stf(locator.vZ.x),stf(locator.vZ.z));
		rCharacter.Ship.stopped = true;
		rCharacter.Ship.Speed.z = 0.0;
		Ship_PrepareShipForLocation(rCharacter);
		SendMessage(&locShips[n],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
		iShips[locNumShips] = rCharacter.index; 
		//locNumShips++;
	}
	return true;
}

// locations grass optimisation
bool CheckLocGrassOpt()
{
	if(pchar.location == "Caiman_Jungle_01") return true;
	
	return false;
}