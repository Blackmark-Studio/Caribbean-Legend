
#include "locations\locations_loader.c"
#include "locations\locations_camera.c"


extern void InitLocations();


native int NativeFindCharacter(ref charactersArray, string id);
native int NativeFindLocation(ref charactersArray, string id);
native int NativeFindLoadCharacter();
native void SetReloadProgressBackImage(string imageName);
native void ReloadProgressStart();
native void ReloadProgressUpdate();
native void ReloadProgressEnd();
native void SystemDelay(int millsec);
native void ExecuteTechnique(string techName);
native string GetNextLineString();
native void SetReloadNextTipsImage();

#libriary "ScriptLocationLibrary"


void LocationInit()
{
	locCameraInit();
	if(LoadSegment("locations\locations_init.c"))
	{
		InitLocations();
		UnloadSegment("locations\locations_init.c");
	}
	locDisableUpdateTime = false;
	locTmpTime = 0.0;
}
/*
void LocationTestProcess()
{
	SetReloadProgressBackImage("Loading\initialization.tga.tx");
	ReloadProgressStart();
	LocationInit();
	Locations_TestAll();
	ReloadProgressEnd();
}
*/

int FindLoadedLocation()
{
	return NativeFindLoadCharacter();
}

bool SetLocatorGroupRadius(ref loc, string grpName, float rad)
{
	return SendMessage(loc, "lsf", MSG_LOCATION_GRP_RADIUS, grpName, rad);
}

bool SetLocatorRadius(ref loc, string grpName, string locName, float rad)
{
	return SendMessage(loc, "lssf", MSG_LOCATION_LOC_RADIUS, grpName, locName, rad);
}


bool VisibleLocatorsGroup(string group, float kRadius, float viewLabelsDist, int a, int r, int g, int b)
{
	
	int i = FindLoadedLocation();
	if(i < 0) return false;
	int color = argb(a, r, g, b);
	return SendMessage(&Locations[i], "lsffl", MSG_LOCATION_VIEWLGROUP, group, kRadius, viewLabelsDist, color);
}

void HideLocatorsGroup(string group)
{
	int i = FindLoadedLocation();
	if(i < 0) return;
	SendMessage(&Locations[i], "ls", MSG_LOCATION_HIDELGROUP, group);
}

// belamour cle блок маркеров направлений 
void SetQuestPointer(string group, string locator)
{
	int i = FindLoadedLocation();
	if(i < 0) return;
	SendMessage(&Locations[i], "lss", MSG_LOCATION_SETQUESTPOINTER, group, locator);
}

void HideQuestPointer(string group, string locator)
{
	int i = FindLoadedLocation();
	if(i < 0) return;
	SendMessage(&Locations[i], "lss", MSG_LOCATION_HIDEQUESTPOINTER, group, locator);
}

void QuestPointerToLoc(string Id, string group, string locator)
{
	int i = FindLocation(Id);
	if(i < 0) return;
	Locations[i].QuestPointer.(group).(locator) = true;
	if(i == FindLoadedLocation()) SetQuestPointer(group, locator);
}

void QuestPointerToLocTime(string Id, string group, string locator, float startTime, float endTime)
{
	int i = FindLocation(Id);
	if(i < 0) return;
	Locations[i].QuestPointer.(group).(locator) = true;
	if(startTime < 0.0) startTime = 0.0;
	if(startTime >= 24.0) startTime = 23.99999999;
	if(endTime < 0.0) endTime = 0.0;
	if(endTime >= 24.0) endTime = 23.99999999;
	Locations[i].QuestPointer.(group).(locator).startTime = startTime;
	Locations[i].QuestPointer.(group).(locator).endTime = endTime;
	aref arLocator;
	makearef(arLocator, Locations[i].QuestPointer.(group).(locator));
	if(i == FindLoadedLocation() && QuestPointer_CheckTime(arLocator)) 
		SetQuestPointer(group, locator);
}

void QuestPointerDelLoc(string Id, string group, string locator)
{
	int i = FindLocation(Id);
	if(i < 0) return;
	
	if(CheckAttribute(&Locations[i], "QuestPointer."+group+"."+locator))
	{
		DeleteAttribute(&Locations[i], "QuestPointer."+group+"."+locator));
		if(i == FindLoadedLocation()) HideQuestPointer(group, locator);
	}
	// убрать атрибут, если нет маркерованных
	if(!CheckAttribute(&Locations[i], "QuestPointer")) return;
	aref arLocator;
	makearef(arLocator, Locations[i].QuestPointer.(group));
	int	Qty = GetAttributesNum(arLocator);
	if (Qty < 1) DeleteAttribute(&Locations[i], "QuestPointer."+group);
	aref arGroup;
	makearef(arGroup, Locations[i].QuestPointer);
	Qty = GetAttributesNum(arGroup);
	if (Qty < 1) DeleteAttribute(&Locations[i], "QuestPointer");
}

bool QuestPointer_CheckTime(aref arLocator)
{
	if(!CheckAttribute(arLocator,"startTime") || !CheckAttribute(arLocator,"endTime")) return true;
	
	float start = stf(arLocator.startTime);
	float end = stf(arLocator.endTime);
	float curTime = GetTime();
	if(start <= end)
	{
		if((curTime >= start) && (curTime <= end)) return true;
	}else{
		if(curTime >= start) return true;
		if(curTime <= end) return true;
	}
	return false;
}

bool WaitNight()
{
	return true;
}


bool WaitNightPause(bool paused)
{
	return true;
}

void LocationWaitNihgtEndFadeOut()
{
	bool isFadeIn = GetEventData();
	aref fader = GetEventData();
	if(isFadeIn == false)
	{
		SendMessage(&fader, "lfl", FADER_IN, 1.0, true);
	}
	SetEventHandler("FaderEvent_EndFadeIn", "LocationWaitNihgtEndFadeIn", 0);
	DelEventHandler("FaderEvent_EndFade", "LocationWaitNihgtEndFadeOut");
}

void LocationWaitNihgtEndFadeIn()
{
	bool isFadeIn = GetEventData();
	aref fader = GetEventData();
	if(isFadeIn != false)
	{
		DelEventHandler("FaderEvent_EndFadeIn", "LocationWaitNihgtEndFadeIn");
		int i = FindLoadedLocation();
		if(i >= 0)
		{
			SendMessage(&Locations[i], "ll", MSG_LOCATION_PAUSE, false);
		}
		PostEvent("LocationWaitNihgtEnd", 1);
	}	
}

//navy -->
void LocationMakeClone(string _locId)
{
	ref rOrg, rClone;
	int iOrg, iClone;

	iOrg = FindLocation(_locId);
	iClone = FindLocation("Clone_location");

	makeref(rOrg, Locations[iOrg]);
	makeref(rClone, Locations[iClone]);

	DeleteAttribute(rClone, "");
	CopyAttributes(rClone, rOrg);
	rClone.id = "Clone_location";
	rClone.type = "clone";
	rClone.index = iClone;
//а так не работает... :) проверка только на аттрибут ;)	
//	rClone.habitues = false;
	DeleteAttribute(rClone, "habitues");

	pchar.questTemp.LocationClone = true;
	pchar.questTemp.LocationClone.id = rOrg.id;
}
//navy <--

// mitrokosta - аналог функции выше, но без лишних атрибутов
void CloneLocation(string fromLoc, string targetLoc) {
	ref rOrg, rClone;
	int iOrg, iClone;

	iOrg = FindLocation(fromLoc);
	iClone = FindLocation(targetLoc);

	makeref(rOrg, Locations[iOrg]);
	makeref(rClone, Locations[iClone]);

	DeleteAttribute(rClone, "");
	CopyAttributes(rClone, rOrg);
	rClone.id = targetLoc;
	rClone.index = iClone;
}

// Warship -->
// Подключить к локации ещё одну модельку
// Ввел доп. проверки в иф, чтобы можно было этим методом "прилеплять" к локации модели ещё при инициализации
bool Location_AddNewModel(String _LocID, String _GroupName, String _LocatorName, String _Model, String _Type, String _Tech, int _Level, bool _Now)
{
	int iLoc =  FindLocation(_LocID);
	if(iLoc == -1) return false;
	ref rLoc = &locations[iLoc];
	rLoc.models.(_Type).(_Model) = _Model; // Название модели
	if(_GroupName != "" && _LocatorName != "")
	{
		rLoc.models.(_Type).(_Model).locator.group = _GroupName; // Название группы локаторов, куда грузим модель
		rLoc.models.(_Type).(_Model).locator.name = _LocatorName; // Название локатора, где будет модель
	}
	if(_Tech != "") rLoc.models.(_Type).(_Model).tech = _Tech; // Техника
	if(_Level > 0) rLoc.models.(_Type).(_Model).level = _Level; // Порядок загрузки
	if(_Now) LocLoadModel(rLoc, "models." + _Type + "." +_Model, ""); // Грузим модель динамически!
	return true;
}

// Удалить модель из локации (удалится токо позле перегруза локации)
bool Location_DeleteModel(String _LocID, String sType, String _Model)
{
	int iLoc =  FindLocation(_LocID);
	if(iLoc == -1) return false;
	ref rLoc = &locations[iLoc];
	DeleteAttribute(rLoc, "models." + sType + "." +_Model);
	return true;
}

// Находится ли перс в заданном локаторе?
bool IsCharacterInLocator(ref rChar, string LocGroup, string LocName)
{
	float fx, fy, fz;
	if(GetCharacterPos(rChar, &fx, &fy, &fz))
	{
		if(CheckCurLocator(LocGroup, LocName, fx, fy, fz)) return true;
	}
	return false;
}

bool Location_AddReload(string _LocID, int iNum, string _name, string _go, string _emerge, bool _autoreload, string _label, float _radius)
{
	int iLoc =  FindLocation(_LocID);
	if(iLoc == -1) return false;
	ref rLoc = &locations[iLoc];
	string sNum = "l"+iNum;
	rLoc.reload.(sNum).name = _name;
	rLoc.reload.(sNum).go = _go;
	rLoc.reload.(sNum).emerge = _emerge;
	if(_autoreload)
		rLoc.reload.(sNum).autoreload = "1";
	else
		rLoc.reload.(sNum).autoreload = "0";
	rLoc.reload.(sNum).label = _label;
	rLoc.locators_radius.reload.(_name) = _radius;
	return true;
}
// <-- Warship

// belamour добавление новой локации
void ExpandLocationsArray() 
{
	MAX_LOCATIONS++;
	SetArraySize(&locations, MAX_LOCATIONS);
	InitAddLoc(MAX_LOCATIONS - 1);
} 

void InitAddLoc(int index)
{
	ref loc;
	makeref(loc, Locations[index]);
	DeleteAttribute(loc, "");
	loc.id = "";
	loc.index = index;
	loc.image = "loading\sea_0" + rand(2) + ".tga";
	loc.music = "enplav.ogg";
	loc.locators_radius.reload = 1.0;
	loc.locators_radius.rld = 1.0;
	loc.locators_radius.camdetector = 1.0;
	loc.locators_radius.camera = 0.3;
	loc.locators_radius.characters = 0.5;
	loc.locators_radius.goto = 0.5;		
	loc.locators_radius.sit = 0.5;		
	loc.locators_radius.lay = 0.5;		
	loc.locators_radius.item = 0.5;		
	loc.locators_radius.officers = 0.5;
	loc.locators_radius.merchant = 1.0;
	loc.locators_radius.box = 1.0;
	loc.locators_radius.candles = 0.1;
	loc.locators_radius.candles_medium = 0.2;
	loc.locators_radius.chandeliers = 0.5;
	loc.locators_radius.heaters = 1.0;
	loc.locators_radius.torchlightes = 0.3;
	loc.locators_radius.torchlightes_o = 0.3;
	loc.locators_radius.fonar = 0.4;
	loc.locators_radius.outside = 2.0;
	loc.locators_radius.incas_light = 0.8;
	loc.locators_radius.incas_sky = 1.0;
	loc.locators_radius.randitem = 1.5;
	loc.locators_radius.waitress = 1.0;
	loc.locators_radius.tables = 0.5;
	loc.locators_radius.barmen = 1.0;
	loc.locators_radius.lamp = 0.2;
	loc.locators_radius.blueteleport = 0.2;
	loc.locators_radius.redteleport = 0.2;
	loc.locators_radius.greenteleport = 0.2;
	loc.locators_radius.magsteleport = 0.2;
	loc.locators_radius.effect = 0.3;
	loc.locators_radius.EncDetector = 8.0;
	loc.locators_radius.teleport = 1.0;
	loc.locators_radius.event = 1.0;
	loc.locators_radius.quest = 1.0;
	if (MOD_BETTATESTMODE == "On")
	{// чтоб было видно в отладке Boal 18.08.06
		loc.locators_radius.soldiers = 0.5;
		loc.locators_radius.patrol = 0.5;
		loc.locators_radius.Smugglers = 0.5;
		loc.locators_radius.monsters = 0.5;
	}
	
	//Day dynamic light
	loc.models.day.lights.candles = "candle";
	loc.models.day.lights.candles_medium = "candelabrum";
	loc.models.day.lights.chandeliers = "chandelier";
	loc.models.day.lights.heaters = "heater";
	loc.models.day.lights.torchlightes = "torchlight";		
	loc.models.day.lights.fireglows = "fireglow";		
	loc.models.day.lights.outside = "outside_day";
	loc.models.day.lights.incas_light = "incas";
	loc.models.day.lights.incas_sky = "incasskyday";
	loc.models.day.lights.lamp = "lamp";
	loc.models.day.lights.blueteleport = "blueteleport";
	loc.models.day.lights.redteleport = "redteleport";
	loc.models.day.lights.greenteleport = "greenteleport";
	loc.models.day.lights.magsteleport = "magsteleport";

	//Night dynamic light
	loc.models.night.lights.candles = "candle";
	loc.models.night.lights.candles_medium = "candelabrum";
	loc.models.night.lights.chandeliers = "chandelier";
	loc.models.night.lights.heaters = "heater";
	loc.models.night.lights.torchlightes = "torchlight";
	loc.models.night.lights.torchlightes_o = "torchlight";
	loc.models.night.lights.fireglows = "fireglow";		
	loc.models.night.lights.fonar = "lamp";
	loc.models.night.lights.outside = "outside_night";		
	loc.models.night.lights.incas_light = "incas";
	loc.models.night.lights.incas_sky = "incasskynight";
	loc.models.night.lights.lamp = "lamp";
	loc.models.night.lights.blueteleport = "blueteleport";
	loc.models.night.lights.redteleport = "redteleport";
	loc.models.night.lights.greenteleport = "greenteleport";
	loc.models.night.lights.magsteleport = "magsteleport";
}