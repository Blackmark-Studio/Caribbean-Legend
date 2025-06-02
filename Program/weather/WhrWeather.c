#define WEATHER_DEBUG			0

int	wRain = 0; 

#include "weather\WhrUtils.c"
#include "weather\WhrLightning.c"
#include "weather\WhrRain.c"
#include "weather\WhrSea.c"
#include "weather\WhrSky.c"
#include "weather\WhrSun.c"
#include "weather\WhrTornado.c"
#include "weather\WhrAstronomy.c"

#define WIND_NORMAL_POWER		20.0
#define MAX_WEATHERS   			50

object	Weather, WeatherParams, WhrCommonParams;

int		iNextWeatherNum 		= -1;
int		iCurWeatherNum 			= -1;
int		iBlendWeatherNum 		= -1;
int		iCurWeatherHour 		= -1;
bool	bCurWeatherStorm 		= false;
int		iTotalNumWeathers 		= 0;
string	sLightingPath 			= "day";
string	sLmLightingPath 		= "day";
string	sInsideBack 			= "";
int		sNewExecuteLayer, sNewRealizeLayer;
string	sCurrentFog;
string  sBlendedFog;
float	fWeatherDelta 			= 0.0;
float	fWeatherAngle, fWeatherSpeed;
float	fFogDensity;
int		iShadowDensity[2];
int		iPrevWeather 			= -1;
bool	sunIsShine 				= true;
bool	bWeatherLoaded 			= false;
bool	bWeatherIsNight 		= false;
bool	bWeatherIsLight 		= false;
bool	bWeatherIsRain 			= false;
bool	bWeatherIsStorm 		= false;

object Weathers[MAX_WEATHERS];

extern int InitWeather();

#event_handler("EWhr_GetWindAngle", "Whr_GetWindAngle");
#event_handler("EWhr_GetWindSpeed", "Whr_GetWindSpeed");
#event_handler("EWhr_GetShadowDensity", "Whr_GetShadowDensity");
#event_handler("EWhr_GetFogDensity", "Whr_GetFogDensity");
#event_handler("WeatherTimeUpdate", "Whr_TimeUpdate" );

//Mett: дебаг-лог для погоды
void Whr_DebugLog(string _text)
{
	if(bBettaTestMode && WEATHER_DEBUG)
	{
		Log_SetStringToLog(_text);
		Trace("Whr_DebugLog: " + _text);
	}
}

string sWeatherDayCycleType = "Caribbean";	//Mett: глобальная переменная для контроля суточного цикла

//Установка суточного цикла
void SetDayCycle(string sType)
{
	if(!isEntity(&Weather))
	{
		Whr_DebugLog("SetDayCycle: Error! Weather not created! Use engine settings.");
		return;
	}
	switch(sType)
	{
		//Sith: Новый суточный цикл для карибов
		case "Caribbean":
			Weather.Sun.Height 		= 3.5/4.0 * PId2;
			Weather.Sun.BegAngle 	= 0.3;
			Weather.Sun.BegTime 	= 5.5;
			Weather.Sun.EndAngle 	= -3.25;
			Weather.Sun.EndTime 	= 20.5;
			Weather.Moon.Height 	= 2.5/4.0 * PId2;
			Weather.Moon.BegAngle 	= 0.0;
			Weather.Moon.BegTime 	= 21.0;
			Weather.Moon.EndAngle 	= 3.0;
			Weather.Moon.EndTime 	= 5.0;
			Weather.DayCycle 		= sType;
		break;
	}
}

void GenerateSkyCurrentDay()
{
	int		iYear, iMonth, iDay, dDay;
	float   fTime;
	bool 	isGenerated = false, 
	bool 	bOk1 = false;
	bool 	bOk2 = false;
	float	dTime = 0.0;
	
	//~!~ TODO добавить зависимость от сезона дождей	
	if(CheckAttribute(&WeatherParams,"weather_sky.year") && !bMainMenu) // есть погода текущего дня и не главное меню
	{
		iYear 	= sti(WeatherParams.weather_sky.year);
		iMonth 	= sti(WeatherParams.weather_sky.month);
		iDay 	= sti(WeatherParams.weather_sky.day);
		fTime 	= stf(WeatherParams.weather_sky.time);

		dDay 	= GetPastTime("day", iYear, iMonth, iDay, fTime, GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
		dTime 	= GetTime() - fTime;
		Whr_DebugLog("dDay : " + dDay + " dTime :" + dTime);
		
		bOk1 = dDay == 0 && dTime < 0.0;
		bOk2 = dDay == 1 && dTime > 0.0; 
		
		if(bOk1 || bOk2)
		{
			switch(sti(WeatherParams.weather_sky))
			{
				// генерим новую погоду на основании погоды предыдущего дня
				case 1: WeatherParams.weather_sky = rand(2) + 1;		break;	
				case 2: WeatherParams.weather_sky = rand(2) + 1;		break;  
				case 3: WeatherParams.weather_sky = rand(2) + 1;		break;	
			}
			isGenerated = true;			
		}
		else isGenerated = false;				
				
		if(dDay > 1)	// генерируем заново, прошло больше 1-го дня
		{
			switch(rand(2))
			{
				case 0: WeatherParams.weather_sky = 1; 	break;	// ясное небо
				case 1: WeatherParams.weather_sky = 2; 	break;	// облачность				
				case 2: WeatherParams.weather_sky = 3; 	break;	// серьёзная облачность				
			}
			isGenerated = true;			
		}			
	}
	else	// если нет погоды текущего дня или главное меню
	{
		switch(rand(2))
		{
			case 0: WeatherParams.weather_sky = 1; 	break;	// ясное небо
			case 1: WeatherParams.weather_sky = 2; 	break;	// облачность				
			case 2: WeatherParams.weather_sky = 3; 	break;	// серьёзная облачность				
		}	
		isGenerated = true;
	}

	if(isGenerated && !bMainMenu)
	{
		// запоминаем время генерации
		WeatherParams.weather_sky.year 	= GetDataYear();		
		WeatherParams.weather_sky.month = GetDataMonth();
		WeatherParams.weather_sky.day 	= GetDataDay();
		WeatherParams.weather_sky.time 	= GetTime();
		Whr_DebugLog("Генерация скайбоксов : год :" + WeatherParams.weather_sky.year + " месяц :" + WeatherParams.weather_sky.month + " день :" + WeatherParams.weather_sky.day + " время :" + WeatherParams.weather_sky.time);
	}
}	

void SetNextWeather(string sWeatherID)
{
	// find weather
	iNextWeatherNum = -1;
	for (int i=0; i<MAX_WEATHERS; i++)
	{
		if (!CheckAttribute(&Weathers[i], "id")) { continue; }
		if (Weathers[i].id == sWeatherID)
		{
			iNextWeatherNum = i;
			Whr_DebugLog("iNextWeatherNum = " + iNextWeatherNum + " Lighting:" + Weathers[i].Lighting);
			return;
		}
	}
}

void WeatherInit()
{
	if (LoadSegment("weather\WhrInit.c"))
	{
		iTotalNumWeathers = InitWeather();
		UnloadSegment("weather\WhrInit.c");
	}
}

void DeleteWeatherEnvironment()
{
	iBlendWeatherNum = -1;
	if (isEntity(&Weather))
	{
		DeleteClass(&Weather);
	}
	DeleteAttribute(&Weather,"");

	WhrDeleteRainEnvironment();
	WhrDeleteSkyEnvironment();
	WhrDeleteSunGlowEnvironment();
	WhrDeleteLightningEnvironment();
	WhrDeleteTornadoEnvironment();
	WhrDeleteSeaEnvironment();
	WhrDeleteAstronomyEnvironment();

	DelEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor");
	DelEventHandler("frame","Whr_OnWindChange");

	bWeatherLoaded = false;
}

aref GetCurrentWeather()
{
	if(iCurWeatherNum < 0) //Mett: fix
	{
		iCurWeatherNum = iTotalNumWeathers - 1;
	}
	aref arWeather; 
	makearef(arWeather,Weathers[iCurWeatherNum]);
	return arWeather;
}

void Whr_OnWindChange()
{
	float fDeltaTime = MakeFloat(GetDeltaTime()) * 0.001;
	fWeatherDelta = fWeatherDelta + fDeltaTime;

	float fSpd = fWeatherSpeed + (fWeatherSpeed / 8.0) * 0.1 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));
	float fAng = fWeatherAngle + 0.02 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));

	Weather.Wind.Angle = fAng;
	Weather.Wind.Speed = fSpd;
}

int Whr_OnCalcFogColor()
{
	int		iAlpha, iColor;
	float	x, y, z;
	float 	fH = 0.0;
	int		iColorTmp = 0;

	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	if( iBlendWeatherNum < 0 )
	{
		aref aCurWeather = GetCurrentWeather();
		iAlpha = 255 - MakeInt(255.0 * Clampf(y / stf(aCurWeather.(sCurrentFog).Height)));

		int iFogColor = sti(Weather.Fog.Color);
		iColor = or(shl(iAlpha, 24), iFogColor);
	}
	else
	{
		float fBlend = stf(Environment.time) - sti(Environment.time);
		if(bSeaActive)
		{
			fH 			= Whr_BlendFloat(fBlend, stf(Weathers[iCurWeatherNum].(sCurrentFog).Height), stf(Weathers[iBlendWeatherNum].(sCurrentFog).Height));
			iColorTmp 	= Whr_BlendColor(fBlend, sti(Weathers[iCurWeatherNum].(sCurrentFog).Color), sti(Weathers[iBlendWeatherNum].(sCurrentFog).Color));			
		}
		else
		{
			fH 			= Whr_BlendFloat(fBlend, stf(Weathers[iCurWeatherNum].(sCurrentFog).Height), stf(Weathers[iBlendWeatherNum].(sBlendedFog).Height));
			iColorTmp 	= Whr_BlendColor(fBlend, sti(Weathers[iCurWeatherNum].(sCurrentFog).Color), sti(Weathers[iBlendWeatherNum].(sBlendedFog).Color));	
		}		
		
		iAlpha = 255 - MakeInt(255.0 * Clampf(y / fH));
		iColor = or(shl(iAlpha, 24), iColorTmp);
	}
	return iColor;
}

#event_handler("eChangeDayNight", "eChangeDayNight");

void Whr_UpdateWeatherHour()
{
	bool bOldIsDay 	= Whr_IsDay();
	
	bWeatherIsLight = Whr_GetLong(&Weathers[iCurWeatherNum],"Lights");
	bWeatherIsNight = Whr_GetLong(&Weathers[iCurWeatherNum],"Night");

	aref aCurWeather = GetCurrentWeather();
	aref aStars;
	makearef(aStars, aCurWeather.Stars);

	FillStars(aStars);
	Astronomy.TimeUpdate = 1;
	Astronomy.isDone = true;

	if(Whr_IsDay() != bOldIsDay)
	{
//		Whr_ChangeDayNight();
		Event("eChangeDayNight");
 	}

	if(CheckAttribute(pchar, "debuger_weather")) //Mett: если в дебагере
	{
		fWeatherAngle = stf(pchar.debuger_weather.windAngle);
		fWeatherSpeed = stf(pchar.debuger_weather.windSpeed);
		WhrCreateSeaEnvironment();
		return;
	}

	if(CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain) == 0 )
    {
        ClearRainEnvironment();
//        Lightning.Clear = "";
    }

	Whr_WindChange(); // изменение ветра каждый час - а нужно ли оно ????? и почему только на море ????
	//~!~
 	if(bSeaActive && !bAbordageStarted)
	{
		WhrCreateSeaEnvironment();
 	}
}

void SetCameraForWeather()
{
    if(!bSeaActive) return;
    if(GetCharacterShipType(pchar) == SHIP_NOTUSED) return;
    
    float ch            = 2.0;
    float bh            = 2.0;
    aref  aCurWeather   = GetCurrentWeather();
	int   shipType      = sti(RealShips[sti(pchar.ship.type)].basetype);   

    switch (aCurWeather.Lighting)
    {
        case "storm1" : ch = 1.7; bh = 1.7; break;
        case "storm2" : ch = 1.5; bh = 1.6; break;
        case "storm3" : ch = 1.6; bh = 1.7; break;
        case "storm4" : ch = 1.5; bh = 1.6; break;
        ch = 2.0; bh = 2.0;
    }        
    switch (shipType)
    {
		// пример корабля из ships.h
		case SHIP_LUGGER:
			ch = 1.2; bh = 1.2;
        break;
		
	}

	SeaShipCamera.cam_height = ch;
	SeaShipCamera.box_height = bh;
}

void Whr_CheckLocation()
{
    ref     loc;
	aref 	aCurWeather 		= GetCurrentWeather();
	int 	loadLocationIndex 	= FindLoadedLocation();
    string  sCurLmLightingPath  = "day";
    
    if(loadLocationIndex >= 0) // проверяем только сушу
    {
        loc = &Locations[loadLocationIndex];
        if(CheckAttribute(loc,"models.always.grassPatch"))
        {
            LocLoadGrass(loc, "models.always.grassPatch"); // проверяем траву при каждом апдейте погоды
        }
        
        if(CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
        {
            sCurLmLightingPath = "storm";
        }
        else
        {
            sCurLmLightingPath = Whr_GetString(aCurWeather,"LightingLm");
        }
        
        if(sCurLmLightingPath != sLmLightingPath)
        {
            sLmLightingPath = sCurLmLightingPath;  
            Trace("Whr_CheckLocation  change sLmLightingPath : " + sLmLightingPath);
            SendMessage(loc, "ls", MSG_LOCATION_SHADOWPATH, sLmLightingPath);
        }
    }
}

void Whr_ChangeDayNight()
{
	ref     loc;
	int 	i, j, iCharIdx;
	aref 	aCurWeather 	= GetCurrentWeather();
	bool 	isSeaEnt 		= false;
	ref 	rChar;
	int		loadLocationIndex = FindLoadedLocation();
	
	if(IsEntity(&Sea)) isSeaEnt = true;
	
	if(loadLocationIndex >= 0) // суша
	{
        loc = &Locations[loadLocationIndex];
		LocationSubstituteGeometry(loc);
		LocationSetLights(loc);
        SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
		if(Whr_IsDay() && !Whr_CheckInsideLoc()) // если день и улица
		{
			SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "DelFlys");
			SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "DelAllLights"); // удаляем все свечения
		}

		// фонарь у гг
		if(CheckAttribute(pchar, "LanternOnChar") != 0 && CheckAttribute(pchar, "HandLight"))
		{
			SendMessage(pchar, "lss", MSG_CHARACTER_EX_MSG, "HandLightOn", "lantern");
		}
	
		if(isSeaEnt) // море загружено или нет
		{	
			Sea.Lights = aCurWeather.Lights;
//            trace("Whr_ChangeDayNight Lights (land) : " + sti(Sea.Lights));
			if(Whr_CheckSeashore() || Whr_CheckSeaTown() || Whr_CheckSeaFix() || Whr_CheckSeaHeightFix()) // проверка на тип локации где могут быть установлены корабли
			{	
				for(int n = 0; n < locNumShips; n++)	// ставим/отключаем всё освещение на кораблях в локации
				{
					rChar = GetCharacter(iShips[n]);
					Ship_SetLightsAndFlares(rChar);
					SendMessage(rChar, "ll", MSG_SHIP_LIGHTSRESET,sti(Sea.Lights));
				}
			}
		}
		CreateParticles(loc);
	}
	else	// море
	{
		if(isSeaEnt)	
		{
			Sea.Lights = aCurWeather.Lights;
//            trace("Whr_ChangeDayNight Lights (sea) : " + sti(Sea.Lights));
			for(j = 0; j < iNumShips; j++) // ставим/отключаем все освещение на кораблях в режиме моря
			{
		        iCharIdx = Ships[j];
                if (iCharIdx < 0 || iCharIdx >= TOTAL_CHARACTERS) continue;
                rChar = GetCharacter(iCharIdx);
				Ship_SetLightsAndFlares(rChar);	
				SendMessage(rChar, "ll", MSG_SHIP_LIGHTSRESET,sti(Sea.Lights));
			}			
		}			
	}		
	// общий код
	//Mett: для смены цвета воды при изменении времени суток 
	DoQuestCheckDelay("update_sea_environment", 0.1);		
}

void Whr_TestShipLights()
{
	ref rShip;
	rShip = GetRealShip(sti(pchar.Ship.Type));
//    trace("Whr_TestShipLights");
	if(CheckAttribute(&WeatherParams, "Test"))
	{
		Ship_SetLightsAndFlares(pchar);
		SendMessage(pchar, "ll", MSG_SHIP_LIGHTSRESET,sti(WeatherParams.test));
		if(sti(WeatherParams.test)) WeatherParams.test = 0;
		else						WeatherParams.test = 1;
	}
	else
	{
		WeatherParams.test = 0;
		Ship_SetLightsAndFlares(pchar);
		SendMessage(pchar, "ll", MSG_SHIP_LIGHTSRESET,sti(WeatherParams.test));
		WeatherParams.test = 1;
	}		
}

void FillWeatherData(int nw1, int nw2)
{	
	if(nw1 < 0 || nw1 >= MAX_WEATHERS) { return; }

	string sCurFog = Whr_GetCurrentFog();
	string sBldFog = Whr_GetBlendedFog();
	float fFogAdd = 0.002;
	float fFogRain = 0.005;
	bool bRain  = CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) // дождь
	bool bStorm = CheckAttribute(&WeatherParams,"Storm") && sti(WeatherParams.Storm)  // шторм
	bool bOk = Whr_CheckFogLocAdd() && Whr_CheckFogLocFix();
	if(nw2 < 0)
	{
		Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");
		Weather.Fog.Start = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start");
		if(bRain || bStorm)
		{
			if(bOk && sCurFog == "Fog") Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density") + fFogAdd + fFogRain;
			else Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density") + fFogRain;
		}
		else 
		{
			if(bOk && sCurFog == "Fog") Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density") + fFogAdd;
			Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density");
		}
		Weather.Fog.Color = Whr_GetColor(&Weathers[nw1], sCurFog + ".Color");
		Weather.Fog.IslandDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity");
		Weather.Fog.SeaDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity");

        if(bSeaActive)
        {
            if(CheckAttribute(&Weathers[nw1],"Sun.SeaColor"))   Weather.Sun.Color   = Whr_GetColor(&Weathers[nw1],"Sun.SeaColor");
            else                                                Weather.Sun.Color   = Whr_GetColor(&Weathers[nw1],"Sun.Color");
            if(CheckAttribute(&Weathers[nw1],"Sun.SeaAmbient")) Weather.Sun.Ambient = Whr_GetColor(&Weathers[nw1],"Sun.SeaAmbient");
            else                                                Weather.Sun.Ambient = Whr_GetColor(&Weathers[nw1],"Sun.Ambient");
        }
        else
        {
            Weather.Sun.Color	= Whr_GetColor(&Weathers[nw1],"Sun.Color");
            Weather.Sun.Ambient	= Whr_GetColor(&Weathers[nw1],"Sun.Ambient");
        }
	}
	else
	{
		float fBlend = stf(Environment.Time) - sti(Environment.Time);
        string sColor1, sColor2;
        string sAmbient1, sAmbient2;

        if(bSeaActive)
        {
            if(CheckAttribute(&Weathers[nw1],"Sun.SeaColor"))   sColor1     = "Sun.SeaColor";
            else                                                sColor1     = "Sun.Color";
            if(CheckAttribute(&Weathers[nw2],"Sun.SeaColor"))   sColor2     = "Sun.SeaColor";
            else                                                sColor2     = "Sun.Color";
            if(CheckAttribute(&Weathers[nw1],"Sun.SeaAmbient")) sAmbient1   = "Sun.SeaAmbient";
            else                                                sAmbient1   = "Sun.Ambient";
            if(CheckAttribute(&Weathers[nw2],"Sun.SeaAmbient")) sAmbient2   = "Sun.SeaAmbient";
            else                                                sAmbient2   = "Sun.Ambient";
            Weather.Sun.Color	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],sColor1), Whr_GetColor(&Weathers[nw2],sColor2));
            Weather.Sun.Ambient	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],sAmbient1), Whr_GetColor(&Weathers[nw2],sAmbient2));	
        }
        else
        {
            Weather.Sun.Color	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Color"), Whr_GetColor(&Weathers[nw2],"Sun.Color"));
            Weather.Sun.Ambient	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Ambient"), Whr_GetColor(&Weathers[nw2],"Sun.Ambient"));	
        }
		
		Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");

		if(bSeaActive)
		{	
			Weather.Fog.Start			= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Start"));
			Weather.Fog.Density			= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Density"));
			Weather.Fog.Color			= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1], sCurFog + ".Color"), Whr_GetColor(&Weathers[nw2], sCurFog + ".Color"));
			Weather.Fog.IslandDensity	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".IslandDensity"));
			Weather.Fog.SeaDensity		= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".SeaDensity"));
		}
		else
		{
			Weather.Fog.Start			= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Start"));
			if(bRain || bStorm)
			{
				if(bOk && sBldFog == "Fog") Weather.Fog.Density	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density")) + fFogAdd + fFogRain;
				else Weather.Fog.Density = Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density")) + fFogRain;
			}
			else
			{
				if(bOk && sBldFog == "Fog") Weather.Fog.Density	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density")) + fFogAdd;
				else Weather.Fog.Density	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density"));
			}
			Weather.Fog.Color			= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1], sCurFog + ".Color"), Whr_GetColor(&Weathers[nw2], sBldFog + ".Color"));
			Weather.Fog.IslandDensity	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".IslandDensity"));
			Weather.Fog.SeaDensity		= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".SeaDensity"));			
		}		
	}
}

void CreateWeather(string sExecuteLayer, string sRealizeLayer)
{
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sExecuteLayer, sRealizeLayer);
}

void DeleteWeather()
{
	DeleteWeatherEnvironment();
}

void MoveWeatherToLayers(int sExecuteLayer, int sRealizeLayer)
{
	LayerDelObject(EXECUTE,&Weather);
	LayerDelObject(REALIZE,&Weather);
	LayerDelObject(SEA_EXECUTE,&Weather);
	LayerDelObject(SEA_REALIZE,&Weather);

	sNewExecuteLayer = sExecuteLayer;
	sNewRealizeLayer = sRealizeLayer;

	LayerAddObject(sExecuteLayer,&Weather,1000000);
	LayerAddObject(sRealizeLayer,&Weather,65530);

	MoveRainToLayers(sExecuteLayer, sRealizeLayer);
	MoveLightningToLayers(sExecuteLayer, sRealizeLayer);
	MoveSkyToLayers(sExecuteLayer, sRealizeLayer);
	MoveSunGlowToLayers(sExecuteLayer, sRealizeLayer);
	MoveAstronomyToLayers(sExecuteLayer, sRealizeLayer);
}

float Whr_GetFogDensity() { return fFogDensity; }

float Whr_GetWindAngle()
{
	if (!CheckAttribute(&Weather,"Wind.Angle")) { return 0.0; }
	return stf(Weather.Wind.Angle);
}

float Whr_GetWindSpeed()
{
	if (!CheckAttribute(&Weather,"Wind.Speed")) { return 3.0; }
	return stf(Weather.Wind.Speed);
}

ref Whr_GetShadowDensity()
{
	aref aCurWeather = GetCurrentWeather();

	iShadowDensity[0] = argb(255,96,96,96);
	iShadowDensity[1] = argb(255,96,96,64);

	if (bWeatherLoaded)
	{
		iShadowDensity[0] = Whr_GetColor(aCurWeather,"Shadow.Density.Head");
		iShadowDensity[1] = Whr_GetColor(aCurWeather,"Shadow.Density.Foot");
	}	
	return &iShadowDensity;
}

string	Whr_GetCurrentFog() { return sCurrentFog; }
string	Whr_GetBlendedFog() { return sBlendedFog; }
string	Whr_GetInsideBack() { return sInsideBack; }

string GetLightingPath()
{
	if(sti(InterfaceStates.DYNAMICLIGHTS)) //Mett: для динамического освещения нет col'ов
	{
		return "";
	}	
	if(CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
	return sLightingPath;
}

string GetLightingPathLoc()
{	
	if(CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
	return sLightingPath;
}

//путь до col файлов для островов
string GetIslandLightingPath()
{
	if(sti(InterfaceStates.DYNAMICLIGHTS)) //для динамического освещения нет col файлов
	{
		return "";
	}	
	if(CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
	return sLightingPath;
}

string GetLmLightingPath() 
{ 
	if(CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return "storm";
	}
	return sLmLightingPath; 
}

bool	Whr_IsDay() 	{ return !bWeatherIsNight; 	}
bool	Whr_IsNight() 	{ return  bWeatherIsNight; 	}
bool	Whr_IsLight()	{ return  bWeatherIsLight; 	}
bool	Whr_IsRain() 	{ return  bWeatherIsRain; 	}
bool	Whr_IsStorm() 	{ return  bWeatherIsStorm; 	}

int FindWeather(string sWeatherID)
{
	for (int i = 0; i < MAX_WEATHERS; i++)
	{
		if(!CheckAttribute(&Weathers[i], "id")) 	continue; 
		if(Weathers[i].id == sWeatherID)			return i;
	}
	return -1;
}

void Whr_SetRainSound(bool _set, bool _isNight)
{
	if(bMainMenu)
	{
		scheme = "sea_rain";
		SetSoundScheme(scheme);
		return;
	}		
	
	string scheme = "land";
	if(!bSeaActive || bAbordageStarted)
	{
		if(IsEntity(loadedLocation) && CheckAttribute(loadedLocation, "type"))
		{
			switch (loadedLocation.type)
			{
				case "town": scheme = "town"; break;
				case "land": scheme = "land"; break;
				case "deck": scheme = "deck"; break;
			}
		}
	}
	else			scheme = "sea";
	if(_isNight)	scheme = scheme + "_night";
	else			scheme = scheme + "_day";
	if(_set)		scheme = scheme + "_rain";
//	trace(": Set Rain Sound... " + _set);
	SetSoundScheme(scheme);
}

string Whr_GetRainyLightningPath()
{
	//fix кривого освещения в пещерах и тюрьмах
	if(loadedLocation.type == "dungeon" 
		|| loadedLocation.type == "jail" 
		|| loadedLocation.type == "cave" 
		|| loadedLocation.type == "Alcove") 
	{
		return "evening23";
	}
	return "storm1";
}

void Whr_WindChange()
{
	float fRainSpeed	= 0.0;
	float fCurAngle, fAngleChange;
	float fCurSpeed, fSpeedChange;

	/// sith пока базовая смена ветра, можно расписать различные условия сезонов и т.д.
	if(CheckAttribute(pchar, "wind.angle") && CheckAttribute(pchar, "wind.speed"))
	{	
		Whr_DebugLog("Whr_WindChange(before) wind.angle: " + pchar.wind.angle + " wind.speed: " + pchar.wind.speed);
	}
	// смена направления ветра
	fCurAngle = Whr_GetWindAngle();
	if(CheckAttribute(pchar, "wind.angle"))
    {
		// выставляем смену угла через диапазон
		if(rand(8) == 0)
		{
			fAngleChange = uniform_angle(-45.0, 45.0); // меньшая вероятность
		}
		else
		{
			fAngleChange = uniform_angle(-15.0, 15.0); // большая вероятность
		}
		if(Whr_CheckStorm()) Weather.Wind.Angle = fCurAngle;  // в шторм не меняем ветер
		else Weather.Wind.Angle = fCurAngle + fAngleChange;
		if(stf(Weather.Wind.Angle) < 0)  Weather.Wind.Angle = PIm2 + stf(Weather.Wind.Angle);
		if(stf(Weather.Wind.Angle) > PIm2) Weather.Wind.Angle = stf(Weather.Wind.Angle) - PIm2;
	}
	else
	{
		Weather.Wind.Angle = fCurAngle;
	}
	Whr_DebugLog("AngleChange: " + fAngleChange*180.0/PI);
	pchar.wind.angle = Weather.Wind.Angle;
	// смена скорости ветра
	fCurSpeed = Whr_GetWindSpeed();
	if(CheckAttribute(pchar, "wind.angle"))
	{
		fSpeedChange = uniform(-2.0,2.0); // базовое изменение скорости ветра в заданных пределах
		// добавим скорость ветра в дождь
		if(fCurSpeed < 12.0)
		{
			if(wRain == 1) fRainSpeed = frand(1.0) + 1.0;
			if(wRain == 2) fRainSpeed = frand(2.0) + 2.0;
		}
		if(Whr_CheckStorm()) Weather.Wind.Speed = fCurSpeed; // в шторм не меняем ветер
		else Weather.Wind.Speed = fClamp(3.0, 18.0, fCurSpeed + fSpeedChange + fRainSpeed);
	}
	else
	{
		Weather.Wind.Speed = fCurSpeed;
	}
	Whr_DebugLog("SpeedChange: " + fSpeedChange);
	pchar.wind.speed = Weather.Wind.Speed;

	pchar.quest.EraseWind.win_condition.l1 	= "ExitFromSea";
	pchar.quest.EraseWind.win_condition 	= "EraseWind";  		/////  --->>> DeleteAttribute(pchar, "wind");

	Whr_DebugLog("Whr_WindChange(after) wind.angle: " + pchar.wind.angle + " wind.speed: " + pchar.wind.speed);
	Whr_DebugLog("RainSpeed add: " + fRainSpeed);
	
	fWeatherAngle = stf(Weather.Wind.Angle);
	fWeatherSpeed = stf(Weather.Wind.Speed);
	
	if(sti(InterfaceStates.DIRECTSAIL) != 0 && bSeaActive && !bAbordageStarted)  // belamour по чекбоксу
	{	
		CheckIslandChange();
	}

    Event("event_WindChange");
}

bool Whr_isRainEnable()
{
	bool bRain  = true;
	//ГГ в локации
    if (CheckAttribute(GetMainCharacter(), "HeroParam") && IsEntity(loadedLocation)) // pchar проверяется для гл меню
	{
        if (CheckAttribute(loadedLocation, "environment.weather.rain") && !sti(loadedLocation.environment.weather.rain))
		{
		    bRain = false;
		}
	}
	else
	{
		if (bSeaActive && bAbordageStarted ) // в море не срабатывает bLandInterfaceStart
		{
			if (IsEntity(&loadedLocation)) 
			{
			    if(CheckAttribute(&loadedLocation, "environment.weather.rain")) 
				{
                    if(!sti(loadedLocation.environment.weather.rain)) bRain = false;
			    }
			}
		}
	}
	return bRain;
}

//Mett: перерасчет направления ветра
float Whr_SetWindAngle()
{
	//ветер дует в ту же сторону, что и на глобалке
	float angle = GetAngleY(stf(worldMap.WindX), stf(worldMap.WindZ));
	//квестовый угол ветра	
	if(CheckAttribute(pchar, "quest.weather.windAngle")) 
	{
		angle = stf(pchar.quest.weather.windAngle);
		DeleteAttribute(pchar, "quest.weather.windAngle");
	}
	Weather.Wind.Angle = wRangeFloat(angle, -180.0, 180.0);
	return stf(Weather.Wind.Angle);
}

//Mett: перерасчет силы ветра
float Whr_SetWindSpeed()
{
	//новый расчет скорости ветра
	float speed = makefloat(stf(worldMap.WindF) * (WIND_NORMAL_POWER - 2.0));
	//квестовая скорость ветра
	if(CheckAttribute(pchar, "quest.weather.windSpeed")) 
	{
		speed = stf(pchar.quest.weather.windSpeed); 
		DeleteAttribute(pchar, "quest.weather.windSpeed");
	}
	Weather.Wind.Speed = wRangeFloat(speed, 3.9, 19.9);
	return stf(Weather.Wind.Speed);
}

void Whr_UpdateWeather()
{
	if(!isEntity(&Weather))
	{
		return;
	}
	CreateWeatherEnvironment();
	Whr_ChangeDayNight();
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
}

int FindWeatherByHour(int nHour)
{
	for(int n = 0; n < MAX_WEATHERS; n++)
	{
		if(!CheckAttribute(&Weathers[n], "hour")) { continue; }
		if(CheckAttribute(&Weathers[n], "skip") && sti(Weathers[n].skip) == true) { continue; }
		
		if(Whr_CheckStorm())
		{
			if(sti(Weathers[n].Storm))
			{
				if(sti(Weathers[n].hour.min) == nHour) { return n; }
			}
			else continue;
		}
		else
		{
			if(!sti(Weathers[n].Storm))
			{
				if(sti(Weathers[n].hour.min) == nHour) { return n; }
			}
			else continue;				
		}		
	}
	return -1;
}

int FindBlendWeather(int iWeatherNum)
{
	if(iWeatherNum < 0 || iWeatherNum >= MAX_WEATHERS) { return -1; }

	if(!CheckAttribute(&Weathers[iWeatherNum], "hour") ) { return -1; }
	if(CheckAttribute(&Weathers[iWeatherNum],"skip") && sti(Weathers[iWeatherNum].skip) == true ) { return -1; }
	
	int nBlendWeatherHour = sti(Weathers[iWeatherNum].hour.min) + 1;
	
	if(Whr_CheckStorm())
	{
		if(sti(Weathers[iWeatherNum].Storm))
		{
			if(nBlendWeatherHour >= 24) { nBlendWeatherHour = 0; }
		}
	}
	else
	{
		if(!sti(Weathers[iWeatherNum].Storm))
		{
			if(nBlendWeatherHour >= 24) { nBlendWeatherHour = 0; }
		}
	}		
	Whr_DebugLog("nBlendWeatherHour : " + nBlendWeatherHour);
	return FindWeatherByHour(nBlendWeatherHour);
}

void Whr_TimeUpdate()
{
	int loadedLocationIndex = FindLoadedLocation();
	bool isTimeLock = (loadedLocationIndex >= 0) && (CheckAttribute(&locations[loadedLocationIndex], "timeLock")) && (sti(locations[loadedLocationIndex].timeLock));
	if (CheckAttribute(pchar, "questTemp.TimeLock") || isTimeLock) {
		return;
	}
	float fTime 			= GetEventData();
	Environment.time 		= fTime;
	int nOldHour 			= sti(Environment.date.hour);
	int nNewHour 			= makeint(fTime);
	int nNewMin 			= makeint((fTime - nNewHour) * 60);
	int nNewSec 			= makeint(((fTime - nNewHour) * 60 - nNewMin) * 60);
	
	Environment.date.min 	= nNewMin;
	Environment.date.hour 	= nNewHour;
	Environment.date.sec 	= nNewSec;
	worldMap.date.hour 		= nNewHour;
	worldMap.date.min  		= nNewMin;
	
	aref aCurWeather = GetCurrentWeather();
    
    SetCameraForWeather();
	
	Whr_DebugLog("Whr_TimeUpdate : Hour : " + nNewHour + " min : " + nNewMin + " sec : " + nNewSec + " oldHour : " + nOldHour);
	
	if(nNewHour < nOldHour)
	{
		AddDataToCurrent(0,0,1);
		Weather.Time.time = GetTime();
	}
	if( iBlendWeatherNum < 0 ) return;
	//navy --> Rain
	int iTmp, iTime;
	bool bRain = false;
	if (CheckAttribute(&WeatherParams,"Rain"))
	{
		bRain = sti(WeatherParams.Rain);
		Whr_DebugLog("bRain : " + bRain);
	} 
	//navy <-- Rain
	
	Whr_DebugLog("Whr_CheckStorm() : " + Whr_CheckStorm());
	
	iCurWeatherNum 		= FindWeatherByHour(makeint(fTime));
	iBlendWeatherNum 	= FindBlendWeather(iCurWeatherNum);
	
	Whr_DebugLog("iCurWeatherNum : " + iCurWeatherNum + " iBlendWeatherNum : " + iBlendWeatherNum);

	if(bSeaActive)
	{
		//Mett: для динамического освещения островов
		Island.LightingPath = GetIslandLightingPath(); 
		Island.FogDensity 	= Weather.Fog.IslandDensity;

		//Mett: выставляем туман, если есть модель для отражения, то вешаем туман на неё, если нет, то на модель острова
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));

		//Mett: опрос на обновление моря при каждой смене игровых минут
		DoQuestCheckDelay("update_sea_environment", 0.1); 
		//Mett: смена текста локации в баттлинтерфейсе
		DoQuestCheckDelay("update_battle_interface", 0.1);	
		
		if (CheckAttribute(aCurWeather, "SpecialSeaFog")) sCurrentFog = "SpecialSeaFog";
	}
	else			// суша - туманы по утрам
	{
		if (CheckAttribute(&WeatherParams, "Fog.ThisDay") && sti(WeatherParams.Fog.ThisDay))
		{
            if (iBlendWeatherNum > -1)
            {
                if(CheckAttribute(&Weathers[iBlendWeatherNum],"SpecialLandFog") && (sti(WeatherParams.Fog.Type) == sti(Weathers[iBlendWeatherNum].SpecialLandFog.Type))) 
                {	
                    if (Whr_CheckInsideLoc()) sBlendedFog = "Fog";
                    else sBlendedFog = "SpecialLandFog";
                }	
                else
                {		
                    sBlendedFog = "Fog";
                }
            }
			
			if(CheckAttribute(&Weathers[iCurWeatherNum],"SpecialLandFog") && (sti(WeatherParams.Fog.Type) == sti(Weathers[iCurWeatherNum].SpecialLandFog.Type))) 
			{	
				if (Whr_CheckInsideLoc()) sCurrentFog = "Fog";
				else sCurrentFog = "SpecialLandFog";
			}	
			else
			{		
				sCurrentFog = "Fog";
			}
		}
	}			

	//navy --> Rain
	//Mett: переработал систему дождей
	bool bIsRainEnable = Whr_isRainEnable() && !Whr_CheckStorm();

	if(CheckAttribute(&WeatherParams,"Rain") && bIsRainEnable) // не для локаций, где низя дождить + не для штормов где своя специфика
	{
		//Mett: дожди 13.11.2019
		if(CheckAttribute(&WeatherParams,"Rain.Type"))
		{	
			if(sti(WeatherParams.Rain.Type) == 0)	Whr_SetRainExt1(iCurWeatherNum, iBlendWeatherNum, bRain);
			else									Whr_SetRainExt2(iCurWeatherNum, iBlendWeatherNum, bRain);			
		}
		else
		{		
			Whr_SetRainExt1(iCurWeatherNum, iBlendWeatherNum, bRain);			
		}	
	}
	//navy <-- Rain

    Whr_CheckLocation();

	if( nNewHour != nOldHour )	
	{	
		bool bUpdate = false;
		Whr_UpdateWeatherHour();
		if(bSeaActive && !bAbordageStarted)
		{
			if(nNewHour == 6 || nNewHour == 7 || nNewHour == 18 || nNewHour == 19 || nNewHour == 20) bUpdate = true;
		}
		if(bUpdate) 
		{
			if(CheckAttribute(&InterfaceStates,"FoliageDrawDistance") && sti(InterfaceStates.FoliageDrawDistance) >= 1000) 
			{
				Sea_UpdateIslandGrass(AISea.Island); // апдейт растительности на островах
			}
		}
	}

	// update weather: sun lighting
	FillWeatherData(iCurWeatherNum, iBlendWeatherNum);

	Whr_ModifySeaFog( fWeatherSpeed );

	if( nNewHour != nOldHour )	// апдейт фонарей только утром и вечером
	{
		if(nNewHour == 6 || nNewHour == 20) Whr_ChangeDayNight();
	}
	Weather.isDone = "";

	//update rain: rain drops, rain colors, rain size, rainbow
	//navy -- попробуем такую проверку, есть подозрение, что это оно. 5.03.07
	if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) && bIsRainEnable) 
	{
        Whr_DebugLog("FillRainData");
		FillRainData(iCurWeatherNum, iBlendWeatherNum);
		Rain.isDone = "";
	}

	// update sun glow: sun\moon, flares
	WhrFillSunGlowData(iCurWeatherNum, iBlendWeatherNum);
	SunGlow.isDone = true;

	// update sky: fog
	Sky.TimeUpdate = fTime;
}

void CreateWeatherEnvironment()
{
	string 	sAttrName;
	string 	sSky = "";
	int 	iWeatherFound[MAX_WEATHERS];
	int 	iNumWeatherFound = 0;
	int 	iHour = MakeInt(GetHour());
	int		hYear, hMonth, hDay, hHour;
	float 	fTime;
	float 	fTmp;

	bool 	bWhrStorm 		= false; 
	bool 	bWhrTornado 	= false; 
	bool 	bRain 			= false;

	int 	iCurLocation;
	int 	iTestWeather;
	bool 	bQuestlockWeather;
	
	if (CheckAttribute(&WeatherParams,"Storm")) 	bWhrStorm 	= sti(WeatherParams.Storm);
	if (CheckAttribute(&WeatherParams,"Tornado")) 	bWhrTornado = sti(WeatherParams.Tornado); 

	Whr_CheckLocationStorm(&bWhrStorm, &bWhrTornado);
	
	if(bWhrStorm)	WeatherParams.Storm 	= 1;
	if(bWhrTornado)	WeatherParams.Tornado 	= 1;

	if (CheckAttribute(&WeatherParams,"Rain") && !Whr_CheckStorm()) { bRain = sti(WeatherParams.Rain); 	} // в штормах своя специфика дождей 
	if (bRain)
	{
		fTmp = stf(WeatherParams.Rain.StartTime) + stf(WeatherParams.Rain.Duration)/60.0;
		if (GetTime() > fTmp)
		{
			bRain 						= false;
			WeatherParams.Rain 			= false;
			WeatherParams.Rain.ThisDay 	= false;
		}
	}

	if (iNextWeatherNum != -1)
	{
		if (iPrevWeather == -1) { iPrevWeather = iCurWeatherNum; }
		iCurWeatherHour = iHour;
		iCurWeatherNum = iNextWeatherNum;
		iNextWeatherNum = -1;
		Whr_DebugLog("Weather: used preset weather " + iCurWeatherNum);
	}
	else
	{
		// search weather for hour
		for (int i = 0;i < MAX_WEATHERS; i++)
		{		
			if (!CheckAttribute(&Weathers[i], "hour")) { continue; }
			if (CheckAttribute(&Weathers[i], "skip") && sti(Weathers[i].skip))  { continue; }

			bool bCanStorm 		= sti(Weathers[i].Storm);
			bool bCanTornado 	= sti(Weathers[i].Tornado);
			
			int iMin = sti(Weathers[i].Hour.Min);
			int iMax = sti(Weathers[i].Hour.Max);
			if (iMin == iMax && iMin != iHour) { continue; }
			if (iMin > iMax)
			{
				if (iHour < iMin && iHour > iMax) { continue; }
			}
			if (iMin < iMax)
			{
				if (iHour < iMin || iHour > iMax) { continue; }
			}
			
			if (bWhrStorm != bCanStorm) { continue; }
			//if (bWhrTornado == true && bWhrTornado != bCanTornado) { continue; }
				
			iWeatherFound[iNumWeatherFound] = i;
			iNumWeatherFound++;
		}

		iCurWeatherHour = iHour;

		if (iNumWeatherFound == 0)
		{
			Trace("Error: iNumWeatherFound = 0, for hour = " + iHour);
			iCurWeatherNum = 0;
		}
		else
		{
			iCurWeatherNum = iWeatherFound[rand(iNumWeatherFound-1)];
			Whr_DebugLog("iCurWeatherNum : " + iCurWeatherNum + " iNumWeatherFound :" + iNumWeatherFound);
		}
	}

	bQuestlockWeather 	= false;
	sunIsShine 			= true; 

	if(CheckAttribute(pchar, "location"))
	{
		iCurLocation = reload_location_index;
		if(iCurLocation != -1)
		{
			if(CheckAttribute(&locations[iCurLocation], "QuestlockWeather"))
			{
				iTestWeather = FindWeather(locations[iCurLocation].QuestlockWeather);
				if(iTestWeather != -1)
				{
					iCurWeatherNum = iTestWeather;
					bQuestlockWeather = true;
					if (CheckAttribute(&locations[iCurLocation], "lockWeather") && locations[iCurLocation].lockWeather == "Inside")
					{
						sunIsShine = false; //выключить солнце
					}
				}
			}
		}
		if(iCurLocation == -1)
		{		
			iCurLocation = FindIsland(pchar.location);
			if(iCurLocation != -1)
			{
				if(CheckAttribute(&Islands[iCurLocation], "QuestlockWeather"))
				{
					iTestWeather = FindWeather(Islands[iCurLocation].QuestlockWeather);
					if(iTestWeather != -1)
					{
						iCurWeatherNum = iTestWeather;
						bQuestlockWeather = true;
					}
				}
			}
		}
	}

	bWeatherIsStorm 	= bWhrStorm;
	bCurWeatherStorm 	= bWhrStorm;

	if (!bQuestlockWeather)	{	iBlendWeatherNum = FindBlendWeather(iCurWeatherNum);	}
	else					{	iBlendWeatherNum = -1; 	}
	
	Whr_DebugLog("iBlendWeatherNum found : " + iBlendWeatherNum + " bQuestlockWeather : " + bQuestlockWeather);

/*
	//ставим погоду, сгенеренную в главном меню
	if (bMainMenu)
	{
		iTestWeather = sti(InterfaceStates.mainmenuweather);
		if(iTestWeather != -1)
		{
			iCurWeatherNum = iTestWeather;
			bQuestlockWeather = true;
		}
	}
*/	
	if (startGameWeather)
	{
		iTestWeather = sti(InterfaceStates.startGameWeather);
		if(iTestWeather != -1)
		{
			iCurWeatherNum = iTestWeather;
			bQuestlockWeather = true;
		}
		startGameWeather = false;
	}

	// create main module Weather
	DeleteAttribute(&Weather,"");
	if (!isEntity(&Weather))
	{
		CreateEntity(&Weather, "Weather");
	}
	SetDayCycle(sWeatherDayCycleType); //Mett: установка суточного цикла

	aref aCurWeather = GetCurrentWeather();

	sLightingPath 		= Whr_GetString(aCurWeather,"Lighting");
	sLmLightingPath 	= Whr_GetString(aCurWeather,"LightingLm");
	sInsideBack 		= Whr_GetString(aCurWeather,"InsideBack");
	bWeatherIsNight 	= Whr_GetLong(aCurWeather,"Night");
	bWeatherIsLight 	= Whr_GetLong(aCurWeather,"Lights");

	if(CheckAttribute(pchar, "wind.angle"))
	{
		Weather.Wind.Angle = pchar.wind.angle;
	}
	else
	{
		Weather.Wind.Angle = frand(PIm2);
		pchar.wind.angle = Weather.Wind.Angle;
	}

	if (CheckAttribute(pchar, "wind.speed"))
	{
		Weather.Wind.Speed = pchar.wind.speed;
	}
	else
	{
		Weather.Wind.Speed = Whr_GetFloat(aCurWeather,"Wind.Speed");
		pchar.wind.speed = Weather.Wind.Speed;
	}
	
	// ~!~
	if(CheckAttribute(pchar,"WorldMap.WindAngle")) //если идем с глобы на локальное море
	{
		Weather.Wind.Angle = stf(pchar.WorldMap.WindAngle);
	}	
	else
	{	
		pchar.wind.angle = Weather.Wind.Angle;
		DeleteAttribute(pchar, "WorldMap.WindAngle");				
	}
	if(CheckAttribute(pchar,"WorldMap.WindForce")) 
	{
		Weather.Wind.Speed = stf(pchar.WorldMap.WindForce) * (WIND_NORMAL_POWER - 2.0);
		pchar.wind.speed = Weather.Wind.Speed;
		DeleteAttribute(pchar, "WorldMap.WindForce");				
	}

	pchar.quest.EraseWind.win_condition.l1 	= "ExitFromSea";
	pchar.quest.EraseWind.win_condition 	= "EraseWind";

	sCurrentFog = "Fog";
	sBlendedFog = "Fog";
	if (bSeaActive) // море
	{ 
		if (CheckAttribute(aCurWeather, "SpecialSeaFog")) sCurrentFog = "SpecialSeaFog"; 
	}
	else			// суша - туманы по утрам и вечерам
	{
		if (CheckAttribute(&WeatherParams, "Fog.ThisDay") && sti(WeatherParams.Fog.ThisDay))
		{
            if (iBlendWeatherNum > -1)
            {
                if(CheckAttribute(&Weathers[iBlendWeatherNum],"SpecialLandFog") && (sti(WeatherParams.Fog.Type) == sti(Weathers[iBlendWeatherNum].SpecialLandFog.Type))) 
                {	
                    if (Whr_CheckInsideLoc()) sBlendedFog = "Fog";
                    else sBlendedFog = "SpecialLandFog";
                }	
                else
                {		
                    sBlendedFog = "Fog";	
                }
            }
			
			if(CheckAttribute(&Weathers[iCurWeatherNum],"SpecialLandFog") && (sti(WeatherParams.Fog.Type) == sti(Weathers[iCurWeatherNum].SpecialLandFog.Type))) 
			{	
				if (Whr_CheckInsideLoc()) sCurrentFog = "Fog";
				else sCurrentFog = "SpecialLandFog";
			}	
			else
			{		
				sCurrentFog = "Fog";	
			}
		}
	}		

	FillWeatherData(iCurWeatherNum, iBlendWeatherNum);
	Whr_ModifySeaFog( fWeatherSpeed );

	if (iBlendWeatherNum < 0 || bQuestlockWeather) 
	{
		Weather.Time.time = GetTime();
		Weather.Time.speed = 350.0; // количество секунд на смену погоды
		Weather.Time.updatefrequence = 12; // количество обновлений на смену погоды	
	}
	else
	{
		Weather.Time.time = GetTime();	
		Weather.Time.speed = 450;
		Weather.Time.updatefrequence = 15; // количество обновлений на смену погоды
		
		if (bSeaActive && !bAbordageStarted)
		{
			if (iArcadeSails == 1)  // скорости в аркаде больше, время быстрее
			{
				Weather.Time.speed = 250; // количество секунд на смену погоды .. 25 секунд а не 250
				Weather.Time.updatefrequence = 10;		// каждые 6 минут		
			}
		}
		else
		{ // суша
																							
			Weather.Time.speed = 350;
			Weather.Time.updatefrequence = 12; // количество обновлений на смену погоды	..каждые 5 минут
		}
		
		if (bMainMenu)
		{ // меню
			Weather.Time.speed = 2000;
			Weather.Time.updatefrequence = 12; // количество обновлений на смену погоды	..каждые 5 минут
		}

		if (CheckAttribute(pchar, "questTemp.TimeLock")) Weather.Time.speed = 99999;// лочим 
	}
	Weather.isDone = "";

	SetEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor",0);
	SetEventHandler("frame","Whr_OnWindChange",0);

	fFogDensity = stf(Weather.Fog.Density);

	fWeatherDelta = 0.0;	
	fWeatherAngle = stf(Weather.Wind.Angle);
	//fWeatherAngle = GetAngleY(stf(worldMap.WindX), stf(worldMap.WindZ));
	fWeatherSpeed = stf(Weather.Wind.Speed);

	// fWeatherAngle = Whr_SetWindAngle(); //Mett: перерасчет направления ветра
	// fWeatherSpeed = Whr_SetWindSpeed(); //Mett: перерасчет силы ветра

    string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref rLoc = &Locations[iLocation];
		
		if (CheckAttribute(rLoc, "environment.weather.rain") && !sti(rLoc.environment.weather.rain))
		{
			bRain = false;
		}
		else
		{
			if (CheckAttribute(rLoc, "type"))
			{
				if(rLoc.type == "tavern"
					|| rLoc.type == "house"
					|| rLoc.type == "residence"
					|| rLoc.type == "shop"
					|| rLoc.type == "shipyard"
					|| rLoc.type == "church" 
					|| rLoc.type == "jail" 
					|| rLoc.type == "dungeon"
					|| rLoc.type == "cave"
					|| rLoc.type == "grotto"
					|| rLoc.type == "LSC_inside"
					|| rLoc.type == "ammo"
					|| rLoc.type == "europe"
					|| rLoc.type == "teno_inside"
					|| rLoc.type == "Alcove"
					|| rLoc.type == "underwater")
				{
					bRain = false;
				}
			}
		}
	}
	
	if (bRain || bWeatherIsStorm)	
    {    
        WhrCreateRainEnvironment();		// итак, если может быть дождь или шторм, создаем окружение
    }    
	else
    {        
        ClearRainEnvironment();			// если не может, удаляем.
    }
	    
	GenerateSkyCurrentDay();

	WhrCreateSunGlowEnvironment();
	WhrCreateLightningEnvironment();
	WhrCreateSkyEnvironment();
	WhrCreateSeaEnvironment();
	WhrCreateAstronomyEnvironment();

    if(bWeatherIsStorm)
    {
        Whr_DebugLog("Start LightningInStorm");
        WhrStartLightning();
    }

	if(iLocation != -1)
	{
		if(CheckAttribute(&Locations[iLocation], "lockWeather"))	bWhrTornado = false;
	}
	if (bWhrTornado)	WhrCreateTornadoEnvironment();
	
	bWeatherLoaded = true;

	if(bSeaActive)
	{
		Island.LightingPath = GetIslandLightingPath(); //Mett: для динамического освещения островов
		Island.FogDensity = Weather.Fog.IslandDensity;

		//Mett: выставляем туман, если есть модель для отражения, то вешаем туман на неё, если нет, то на модель острова
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));
	}
	Whr_ModifySeaFog( fWeatherSpeed );
	Whr_DebugLog(" GetTime() : " + GetTime());
    SetCameraForWeather();
	if (!bQuestlockWeather) Event("WeatherTimeUpdate", "f", GetTime());
}

void Whr_LoadNextWeather(int nPlus)
{
	if(!isEntity(&Weather))	return;
		
	iCurWeatherNum 	= iCurWeatherNum + nPlus;	
	Whr_DebugLog("Whr_LoadNextWeather :  iCurWeatherNum " + iCurWeatherNum);
	
	if(Whr_CheckStorm())
	{
		if(iCurWeatherNum < 0)		iCurWeatherNum = 47;
		if(iCurWeatherNum >= 48)	iCurWeatherNum = 24;
	}
	else
	{
		if(iCurWeatherNum < 0)		iCurWeatherNum = 23;
		if(iCurWeatherNum >= 24)	iCurWeatherNum = 0;
	}		
	
	Whr_DebugLog("ПОГОДА: " + Weathers[iCurWeatherNum].id + " ОСВЕЩЕНИЕ: " + Weathers[iCurWeatherNum].Lighting);

//	iNextWeatherNum = iCurWeatherNum;	
	iNextWeatherNum = -1;	
	iCurWeatherHour = sti(Weathers[iCurWeatherNum].Hour.Min);
	
	SetCurrentTime(iCurWeatherHour, 0);
	
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
	
	Whr_DebugLog("Whr_LoadNextWeather :  iCurWeatherHour :" + iCurWeatherHour + " iNextWeatherNum :" + iNextWeatherNum);
	Weather.Time.time = GetTime();
}

bool Whr_CheckInsideLoc() // фильтр внутренних локаций без погодных условий
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			if(loc.type == "residence"
				|| loc.type == "tavern"
				|| loc.type == "house"
				|| loc.type == "shop"
				|| loc.type == "shipyard"
				|| loc.type == "church" 
				|| loc.type == "jail" 
				|| loc.type == "dungeon" 
				|| loc.type == "cave"
				|| loc.type == "LSC_inside"
				|| loc.type == "fort_attack"
                || loc.type == "boarding_cabine"
				|| loc.type == "ammo"
				|| loc.type == "europe"
				|| loc.type == "teno_inside"
				|| loc.type == "Alcove")
			{
				if(loc.id == "Deck_Near_Ship") return false;
				else return true;
			}
		}
	}
	return false;
}

bool Whr_CheckFogLocAdd() // фильтр локаций для повышенного тумана
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			if(loc.type == "jungle"
				|| loc.type == "seashore"
				|| loc.type == "town"
				|| loc.type == "fort"
				|| loc.type == "fort_attack"
				|| loc.type == "questisland"
				|| loc.type == "mayak")
			{
				return true;
			}
		}
	}
	return false;
}

bool Whr_CheckFogLocFix() // фильтр локаций исключений в рамках одного типа
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "id"))
		{
			if(loc.id == "Mayak3"// Маяк Ямайки
				|| loc.id == "PortRoyal_town")
			{
				return false;
			}
		}
	}
	return true;
}

// new boarding locations
bool Whr_CheckNewBoardingDeck()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "id"))
		{
			if(loc.id == "boarding_3_war" 
				|| loc.id == "boarding_3_trade"
				|| loc.id == "boarding_4_war"
				|| loc.id == "boarding_4_trade"
				|| loc.id == "boarding_5_war"
				|| loc.id == "boarding_5_trade"
				|| loc.id == "Ship_deck_Medium_trade"
				|| loc.id == "Ship_deck_Medium_war"
				|| loc.id == "Ship_deck_Low"
				|| loc.id == "Deck_Near_Ship"
				|| loc.id == "Deck_Near_Ship_Medium_war"
				|| loc.id == "Deck_Near_Ship_Memento"
				|| loc.id == "Ship_deck_Memento"
				|| loc.id == "Quest_Ship_deck_Medium_trade")
			{
				return true;
			}
		}
	}
	return false;
}