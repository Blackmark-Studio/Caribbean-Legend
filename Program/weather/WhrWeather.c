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
#include "weather\WhrSnow.c"

#define WIND_NORMAL_POWER		20.0
#define WIND_MAX_POWER			18.0
#define WIND_MIN_POWER			7.0
#define MAX_WEATHERS   			50

object	Weather, WeatherParams, WhrCommonParams;

int		iNextWeatherNum 		= -1;
int		iCurWeatherNum 			= -1;
int		iBlendWeatherNum 		= -1;
int		iCurWeatherHour 		= -1;
int		iTotalNumWeathers 		= 0;
string	sLightingPath 			= "day";
string	sLmLightingPath 		= "day";
string	sInsideBack 			= "";
int		sNewExecuteLayer, sNewRealizeLayer; // ~!~ не стринг это
string	sCurrentFog;
string  sBlendedFog;
float	fWeatherDelta = 0.0;
float	fWeatherAngle, fWeatherSpeed;
float	fFogDensity;
int		iShadowDensity[2];
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
	if (bBettaTestMode && WEATHER_DEBUG)
	{
		Log_SetStringToLog(_text);
		Trace("Whr_DebugLog: " + _text);
	}
}

string sWeatherDayCycleType = "Caribbean";	//Mett: глобальная переменная для контроля суточного цикла

//Установка суточного цикла
void SetDayCycle(string sType)
{
	if (!isEntity(&Weather))
	{
		Whr_DebugLog("SetDayCycle: Error! Weather not created! Use engine settings.");
		return;
	}
	switch (sType)
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
	bool 	isGenerated = false;
	bool 	bOk1 = false;
	bool 	bOk2 = false;
	float	dTime = 0.0;

	//~!~ TODO добавить зависимость от сезона дождей	
	if (CheckAttribute(&WeatherParams,"weather_sky.year") && !bMainMenu) // есть погода текущего дня и не главное меню
	{
		iYear 	= int(WeatherParams.weather_sky.year);
		iMonth 	= int(WeatherParams.weather_sky.month);
		iDay 	= int(WeatherParams.weather_sky.day);
		fTime 	= float(WeatherParams.weather_sky.time);

		dDay 	= GetPastTime("day", iYear, iMonth, iDay, fTime, GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
		dTime 	= GetTime() - fTime;
		Whr_DebugLog("dDay : " + dDay + " dTime :" + dTime);

		bOk1 = dDay == 0 && dTime < 0.0;
		bOk2 = dDay == 1 && dTime > 0.0; 

		if (bOk1 || bOk2)
		{
			switch (int(WeatherParams.weather_sky))
			{
				// генерим новую погоду на основании погоды предыдущего дня ~!~
				case 1: WeatherParams.weather_sky = rand(2) + 1;		break;	
				case 2: WeatherParams.weather_sky = rand(2) + 1;		break;  
				case 3: WeatherParams.weather_sky = rand(2) + 1;		break;	
			}
			isGenerated = true;			
		}
		else isGenerated = false;				

		if (dDay > 1) // генерируем заново, прошло больше 1-го дня
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
	else // если нет погоды текущего дня или главное меню
	{
		switch (rand(2))
		{
			case 0: WeatherParams.weather_sky = 1; 	break;	// ясное небо
			case 1: WeatherParams.weather_sky = 2; 	break;	// облачность				
			case 2: WeatherParams.weather_sky = 3; 	break;	// серьёзная облачность				
		}	
		isGenerated = true;
	}

	if (isGenerated && !bMainMenu)
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
		if (!CheckAttribute(&Weathers[i], "id")) continue;
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
	if (iCurWeatherNum < 0) // Mett: fix
        iCurWeatherNum = iTotalNumWeathers - 1;
	aref arWeather; 
	makearef(arWeather,Weathers[iCurWeatherNum]);
	return arWeather;
}

void Whr_OnWindChange()
{
	float fDeltaTime = float(GetDeltaTime()) * 0.001;
	fWeatherDelta = fWeatherDelta + fDeltaTime;

	float fSpd = fWeatherSpeed + (fWeatherSpeed / 8.0) * 0.1 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));
	float fAng = fWeatherAngle + 0.02 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));
	
	if (fSpd < WIND_MIN_POWER) fSpd = WIND_MIN_POWER;
	Weather.Wind.Angle = fAng;
	Weather.Wind.Speed = fSpd;
    // PChar.Wind.Angle = fAng;
	// PChar.Wind.Speed = fSpd;
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

	if (iBlendWeatherNum < 0)
	{
		aref aCurWeather = GetCurrentWeather();
		iAlpha = 255 - int(255.0 * Clampf(y / float(aCurWeather.(sCurrentFog).Height)));

		int iFogColor = int(Weather.Fog.Color);
		iColor = or(shl(iAlpha, 24), iFogColor);
	}
	else
	{
		float fBlend = float(Environment.time) - int(Environment.time);
		if(bSeaActive)
		{
			fH 			= Whr_BlendFloat(fBlend, float(Weathers[iCurWeatherNum].(sCurrentFog).Height), float(Weathers[iBlendWeatherNum].(sCurrentFog).Height));
			iColorTmp 	= Whr_BlendColor(fBlend, int(Weathers[iCurWeatherNum].(sCurrentFog).Color), int(Weathers[iBlendWeatherNum].(sCurrentFog).Color));
		}
		else
		{
			fH 			= Whr_BlendFloat(fBlend, float(Weathers[iCurWeatherNum].(sCurrentFog).Height), float(Weathers[iBlendWeatherNum].(sBlendedFog).Height));
			iColorTmp 	= Whr_BlendColor(fBlend, int(Weathers[iCurWeatherNum].(sCurrentFog).Color), int(Weathers[iBlendWeatherNum].(sBlendedFog).Color));
		}		
		
		iAlpha = 255 - int(255.0 * Clampf(y / fH));
		iColor = or(shl(iAlpha, 24), iColorTmp);
	}
	return iColor;
}

#event_handler("eChangeDayNight", "eChangeDayNight");

void Whr_UpdateWeatherHour()
{
	bool bOldIsDay 	= Whr_IsDay();

	bWeatherIsLight = bool(Whr_GetLong(&Weathers[iCurWeatherNum],"Lights"));
	bWeatherIsNight = bool(Whr_GetLong(&Weathers[iCurWeatherNum],"Night"));

	aref aCurWeather = GetCurrentWeather();
	aref aStars;
	makearef(aStars, aCurWeather.Stars);

	FillStars(aStars);
	Astronomy.TimeUpdate = 1;
	Astronomy.isDone = true;

	if (Whr_IsDay() != bOldIsDay)
	{
        // Whr_ChangeDayNight();
		Event("eChangeDayNight");
 	}

	if (CheckAttribute(pchar, "debuger_weather")) //Mett: если в дебагере
	{
		fWeatherAngle = float(pchar.debuger_weather.windAngle);
		fWeatherSpeed = float(pchar.debuger_weather.windSpeed);
		WhrCreateSeaEnvironment();
		return;
	}

	if (CheckAttribute(&WeatherParams, "Rain") && int(WeatherParams.Rain) == 0)
    {
        ClearRainEnvironment();
        // Lightning.Clear = "";
    }

	Whr_WindChange();

 	if (bSeaActive && !bAbordageStarted)
	{   //~!~
		WhrCreateSeaEnvironment();
 	}
}

void SetCameraForWeather()
{
    if (!bSeaActive) return;
    if (GetCharacterShipType(pchar) == SHIP_NOTUSED) return;

    float ch            = 2.0;
    float bh            = 2.0;
    aref  aCurWeather   = GetCurrentWeather();
	int   shipType      = int(RealShips[int(pchar.ship.type)].basetype);

    switch (aCurWeather.Lighting)
    {
        case "storm1" : ch = 1.7; bh = 1.7; break;
        case "storm2" : ch = 1.5; bh = 1.6; break;
        case "storm3" : ch = 1.6; bh = 1.7; break;
        case "storm4" : ch = 1.5; bh = 1.6; break;
        default: ch = 2.0; bh = 2.0; break;
    }
    switch (shipType)
    {
		// пример корабля из ships.h
        case SHIP_LUGGER:
            ch = 1.2; bh = 1.2;
            break;
        // TO_DO ?
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

    if (loadLocationIndex >= 0) // проверяем только сушу
    {
        loc = &Locations[loadLocationIndex];
        if (CheckAttribute(loc,"models.always.grassPatch"))
        {
            LocLoadGrass(loc, "models.always.grassPatch"); // проверяем траву при каждом апдейте погоды
        }

        if (CheckAttribute(&WeatherParams, "Rain") && int(WeatherParams.Rain))
        {
            sCurLmLightingPath = "storm";
        }
        else sCurLmLightingPath = Whr_GetString(aCurWeather,"LightingLm");

        if (sCurLmLightingPath != sLmLightingPath)
        {
            sLmLightingPath = sCurLmLightingPath;  
            Trace("Whr_CheckLocation  change sLmLightingPath : " + sLmLightingPath);
            SendMessage(loc, "ls", MSG_LOCATION_SHADOWPATH, sLmLightingPath);
        }
    }
}

void Whr_ChangeDayNight()
{
	ref  loc;
	int  i, j, iCharIdx;
	aref aCurWeather = GetCurrentWeather();
	bool isSeaEnt    = IsEntity(&Sea);
	ref  rChar;
	int  loadLocationIndex = FindLoadedLocation();
	
	if (loadLocationIndex >= 0) // суша
	{
        loc = &Locations[loadLocationIndex];
		LocationSubstituteGeometry(loc);
		LocationSetLights(loc);
        SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
		if (Whr_IsDay() && !Whr_CheckInsideLoc()) // если день и улица
		{
			SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "DelFlys");
			SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "DelAllLights"); // удаляем все свечения
		}

		// фонарь у гг
		if (CheckAttribute(pchar, "LanternOnChar") != 0 && CheckAttribute(pchar, "HandLight"))
		{
			SendMessage(pchar, "lss", MSG_CHARACTER_EX_MSG, "HandLightOn", "lantern");
		}

		if (isSeaEnt) // море загружено или нет
		{	
			Sea.Lights = aCurWeather.Lights;
//            trace("Whr_ChangeDayNight Lights (land) : " + int(Sea.Lights));
			if (Whr_CheckSeashore() || Whr_CheckSeaTown() || Whr_CheckSeaFix() || Whr_CheckSeaHeightFix()) // проверка на тип локации где могут быть установлены корабли
			{	
				for(int n = 0; n < locNumShips; n++) // ставим/отключаем всё освещение на кораблях в локации
				{
					rChar = GetCharacter(iShips[n]);
					Ship_SetLightsAndFlares(rChar);
					SendMessage(rChar, "ll", MSG_SHIP_LIGHTSRESET,int(Sea.Lights));
				}
			}
		}
		CreateParticles(loc);
	}
	else // море
	{
		if (isSeaEnt)	
		{
			Sea.Lights = aCurWeather.Lights;
//            trace("Whr_ChangeDayNight Lights (sea) : " + int(Sea.Lights));
			for(j = 0; j < iNumShips; j++) // ставим/отключаем все освещение на кораблях в режиме моря
			{
		        iCharIdx = Ships[j];
                if (iCharIdx < 0 || iCharIdx >= TOTAL_CHARACTERS) continue;
                rChar = GetCharacter(iCharIdx);
				Ship_SetLightsAndFlares(rChar);	
				SendMessage(rChar, "ll", MSG_SHIP_LIGHTSRESET,int(Sea.Lights));
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
	rShip = GetRealShip(int(pchar.Ship.Type));
//    trace("Whr_TestShipLights");
	if (CheckAttribute(&WeatherParams, "Test"))
	{
		Ship_SetLightsAndFlares(pchar);
		SendMessage(pchar, "ll", MSG_SHIP_LIGHTSRESET,int(WeatherParams.test));
		if(int(WeatherParams.test)) WeatherParams.test = 0;
		else						WeatherParams.test = 1;
	}
	else
	{
		WeatherParams.test = 0;
		Ship_SetLightsAndFlares(pchar);
		SendMessage(pchar, "ll", MSG_SHIP_LIGHTSRESET,int(WeatherParams.test));
		WeatherParams.test = 1;
	}		
}

void FillWeatherData(int nw1, int nw2)
{	
	if (nw1 < 0 || nw1 >= MAX_WEATHERS) return;

	string sCurFog = Whr_GetCurrentFog();
	string sBldFog = Whr_GetBlendedFog();
	float fFogAdd = 0.002;
	float fFogRain = 0.005;
	bool bRain  = CheckAttribute(&WeatherParams,"Rain") && bool(WeatherParams.Rain);   // дождь
	bool bStorm = CheckAttribute(&WeatherParams,"Storm") && bool(WeatherParams.Storm); // шторм
	bool bOk = Whr_CheckFogLocAdd() && Whr_CheckFogLocFix();
	if (nw2 < 0)
	{
		Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");
		Weather.Fog.Start = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start");
		if (bRain || bStorm)
		{
			if (bOk && sCurFog == "Fog")
                Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density") + fFogAdd + fFogRain;
			else
                Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density") + fFogRain;
		}
		else 
		{
			if(bOk && sCurFog == "Fog")
                Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density") + fFogAdd;
            else
                Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density");
		}
		Weather.Fog.Color = Whr_GetColor(&Weathers[nw1], sCurFog + ".Color");
		Weather.Fog.IslandDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity");
		Weather.Fog.SeaDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity");

        if (bSeaActive)
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
		float fBlend = float(Environment.Time) - int(Environment.Time);
        string sColor1, sColor2;
        string sAmbient1, sAmbient2;

        if (bSeaActive)
        {
            if (CheckAttribute(&Weathers[nw1],"Sun.SeaColor"))  sColor1     = "Sun.SeaColor";
            else                                                sColor1     = "Sun.Color";
            if (CheckAttribute(&Weathers[nw2],"Sun.SeaColor"))  sColor2     = "Sun.SeaColor";
            else                                                sColor2     = "Sun.Color";
            if (CheckAttribute(&Weathers[nw1],"Sun.SeaAmbient")) sAmbient1   = "Sun.SeaAmbient";
            else                                                 sAmbient1   = "Sun.Ambient";
            if (CheckAttribute(&Weathers[nw2],"Sun.SeaAmbient")) sAmbient2   = "Sun.SeaAmbient";
            else                                                 sAmbient2   = "Sun.Ambient";
            Weather.Sun.Color	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],sColor1), Whr_GetColor(&Weathers[nw2],sColor2));
            Weather.Sun.Ambient	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],sAmbient1), Whr_GetColor(&Weathers[nw2],sAmbient2));	
        }
        else
        {
            Weather.Sun.Color	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Color"), Whr_GetColor(&Weathers[nw2],"Sun.Color"));
            Weather.Sun.Ambient	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Ambient"), Whr_GetColor(&Weathers[nw2],"Sun.Ambient"));	
        }

		Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");

		if (bSeaActive)
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
			if (bRain || bStorm)
			{
				if(bOk && sBldFog == "Fog")
                    Weather.Fog.Density	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density")) + fFogAdd + fFogRain;
				else
                    Weather.Fog.Density = Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density")) + fFogRain;
			}
			else
			{
				if (bOk && sBldFog == "Fog")
                    Weather.Fog.Density	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density")) + fFogAdd;
				else
                    Weather.Fog.Density	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density"));
			}
			Weather.Fog.Color			= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1], sCurFog + ".Color"), Whr_GetColor(&Weathers[nw2], sBldFog + ".Color"));
			Weather.Fog.IslandDensity	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".IslandDensity"));
			Weather.Fog.SeaDensity		= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".SeaDensity"));			
		}
	}
}

void CreateWeather(int sExecuteLayer, int sRealizeLayer)
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
	if (!CheckAttribute(&Weather,"Wind.Angle")) return 0.0;
	return float(Weather.Wind.Angle);
}

float Whr_GetWindSpeed()
{
	if (!CheckAttribute(&Weather,"Wind.Speed")) return WIND_MIN_POWER;
	return float(Weather.Wind.Speed);
}

ref Whr_GetShadowDensity()
{
	aref aCurWeather = GetCurrentWeather();

	iShadowDensity[0] = argb(255,96,96,96);
	iShadowDensity[1] = argb(255,96,96,64);

	if (bWeatherLoaded) // ~!~
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
	if(int(InterfaceStates.DYNAMICLIGHTS)) //Mett: для динамического освещения нет col'ов
	{
		return "";
	}	
	if(CheckAttribute(&WeatherParams, "Rain") && int(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
	return sLightingPath;
}

string GetLightingPathLoc()
{	
	if(CheckAttribute(&WeatherParams, "Rain") && int(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
	return sLightingPath;
}

//путь до col файлов для островов
string GetIslandLightingPath()
{
	if(int(InterfaceStates.DYNAMICLIGHTS)) //для динамического освещения нет col файлов
	{
		return "";
	}	
	if(CheckAttribute(&WeatherParams, "Rain") && int(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
	return sLightingPath;
}

string GetLmLightingPath() 
{ 
	if(CheckAttribute(&WeatherParams, "Rain") && int(WeatherParams.Rain))
	{
		return "storm";
	}
	return sLmLightingPath; 
}

bool Whr_IsDay()   {return !bWeatherIsNight;}
bool Whr_IsNight() {return  bWeatherIsNight;}
bool Whr_IsLight() {return  bWeatherIsLight;}
bool Whr_IsRain()  {return  bWeatherIsRain; }
bool Whr_IsStorm() {return  bWeatherIsStorm;}

int FindWeather(string sWeatherID)
{
	for (int i = 0; i < MAX_WEATHERS; i++)
	{
		if(!CheckAttribute(&Weathers[i], "id")) continue; 
		if(Weathers[i].id == sWeatherID) return i;
	}
	return -1;
}

void Whr_SetRainSound(bool _set, bool _isNight)
{
	if (bMainMenu)
	{
		scheme = "sea_rain";
		SetSoundScheme(scheme);
		return;
	}		

	string scheme = "land";
	if (!bSeaActive || bAbordageStarted)
	{
		if (IsEntity(loadedLocation) && CheckAttribute(loadedLocation, "type"))
		{
			switch (loadedLocation.type)
			{
				case "town": scheme = "town"; break;
				case "land": scheme = "land"; break;
				case "deck": scheme = "deck"; break;
			}
		}
	}
	else          scheme = "sea";
	if (_isNight) scheme = scheme + "_night";
	else          scheme = scheme + "_day";
	if (_set)     scheme = scheme + "_rain";
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
	float fRainSpeed = 0.0;
	float fCurAngle, fAngleChange;
	float fCurSpeed, fSpeedChange;

	// Sith пока базовая смена ветра, можно расписать различные условия сезонов и т.д.
	if (CheckAttribute(PChar, "wind.angle") && CheckAttribute(PChar, "wind.speed"))
	{	
		Whr_DebugLog("Whr_WindChange(before) wind.angle: " + PChar.wind.angle + " wind.speed: " + PChar.wind.speed);
	}
	// смена направления ветра
	fCurAngle = Whr_GetWindAngle();
	if (CheckAttribute(PChar, "wind.angle"))
    {
		// выставляем смену угла через диапазон
		if (rand(8) == 0) fAngleChange = uniform_angle(-45.0, 45.0);
		else fAngleChange = uniform_angle(-15.0, 15.0);
		if (Whr_CheckStorm()) Weather.Wind.Angle = fCurAngle; // в шторм не меняем ветер
		else Weather.Wind.Angle = fCurAngle + fAngleChange;
		if (float(Weather.Wind.Angle) < 0)  Weather.Wind.Angle = PIm2 + float(Weather.Wind.Angle);
		if (float(Weather.Wind.Angle) > PIm2) Weather.Wind.Angle = float(Weather.Wind.Angle) - PIm2;
	}
	else Weather.Wind.Angle = fCurAngle;

	Whr_DebugLog("AngleChange: " + fAngleChange*180.0/PI);
	PChar.wind.angle = Weather.Wind.Angle;
	// смена скорости ветра
	fCurSpeed = Whr_GetWindSpeed();
	if (CheckAttribute(PChar, "wind.angle"))
	{
		fSpeedChange = uniform(-2.0,2.0); // базовое изменение скорости ветра в заданных пределах
		// добавим скорость ветра в дождь
		if (fCurSpeed < 12.0)
		{
			if (wRain == 1) fRainSpeed = frand(1.0) + 1.0;
			else if (wRain == 2) fRainSpeed = frand(2.0) + 2.0;
		}
		if (Whr_CheckStorm()) Weather.Wind.Speed = fCurSpeed; // в шторм не меняем ветер
		else Weather.Wind.Speed = fClamp(WIND_MIN_POWER, WIND_MAX_POWER, fCurSpeed + fSpeedChange + fRainSpeed);
	}
	else Weather.Wind.Speed = fCurSpeed;

	Whr_DebugLog("SpeedChange: " + fSpeedChange);
	PChar.wind.speed = Weather.Wind.Speed;

	Whr_DebugLog("Whr_WindChange(after) wind.angle: " + PChar.wind.angle + " wind.speed: " + PChar.wind.speed);
	Whr_DebugLog("RainSpeed add: " + fRainSpeed);

	fWeatherAngle = float(Weather.Wind.Angle);
	fWeatherSpeed = float(Weather.Wind.Speed);

	// убрал пока
	// if(int(InterfaceStates.DIRECTSAIL) != 0 && bSeaActive && !bAbordageStarted)  // belamour по чекбоксу
	// {
		// CheckIslandChange();
	// }

    Event("event_WindChange");
}

bool Whr_isRainEnable()
{
	bool bRain  = true;
	//ГГ в локации
    if (CheckAttribute(GetMainCharacter(), "HeroParam") && IsEntity(loadedLocation)) // pchar проверяется для гл меню
	{
        if (CheckAttribute(loadedLocation, "environment.weather.rain") && !int(loadedLocation.environment.weather.rain))
		{
		    bRain = false;
		}
	}
	else
	{
		if (bSeaActive && bAbordageStarted) // в море не срабатывает bLandInterfaceStart
		{
			if (IsEntity(loadedLocation)) 
			{
			    if (CheckAttribute(loadedLocation, "environment.weather.rain")) 
				{
                    if (!int(loadedLocation.environment.weather.rain)) bRain = false;
			    }
			}
		}
	}
	return bRain;
}

//Mett: перерасчет направления ветра (Не используется)
float Whr_SetWindAngle()
{
	//ветер дует в ту же сторону, что и на глобалке
	float angle = GetAngleY(float(worldMap.WindX), float(worldMap.WindZ));
	//квестовый угол ветра	
	if(CheckAttribute(pchar, "quest.weather.windAngle")) 
	{
		angle = float(pchar.quest.weather.windAngle);
		DeleteAttribute(pchar, "quest.weather.windAngle");
	}
	Weather.Wind.Angle = wRangeFloat(angle, -180.0, 180.0);
	return float(Weather.Wind.Angle);
}

//Mett: перерасчет силы ветра (Не используется)
float Whr_SetWindSpeed()
{
	//новый расчет скорости ветра
	float speed = float(float(worldMap.WindF) * WIND_MAX_POWER);
	//квестовая скорость ветра
	if (CheckAttribute(pchar, "quest.weather.windSpeed")) 
	{
		speed = float(pchar.quest.weather.windSpeed);
		DeleteAttribute(pchar, "quest.weather.windSpeed");
	}
	Weather.Wind.Speed = wRangeFloat(speed, WIND_MIN_POWER, WIND_NORMAL_POWER);
	return float(Weather.Wind.Speed);
}

void Whr_UpdateWeather()
{
	if (!isEntity(&Weather))
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
		if (CheckAttribute(&Weathers[n], "skip") && int(Weathers[n].skip) == true) continue;
        if (Whr_CheckStorm() != int(Weathers[n].Storm)) continue;
		if (int(Weathers[n].hour.min) == nHour) return n;
	}
	return -1;
}

int FindBlendWeather(int iWeatherNum)
{
    if (iWeatherNum < 0 || iWeatherNum >= MAX_WEATHERS)
        return iTotalNumWeathers - 1;
	int nBlendWeatherHour = int(Weathers[iWeatherNum].hour.min) + 1;
    if (nBlendWeatherHour >= 24) nBlendWeatherHour = 0;
	Whr_DebugLog("nBlendWeatherHour : " + nBlendWeatherHour);
	return FindWeatherByHour(nBlendWeatherHour);
}

void Whr_TimeUpdate()
{
	int loadedLocationIndex = FindLoadedLocation();

	bool isTimeLock = (loadedLocationIndex >= 0) && (CheckAttribute(&locations[loadedLocationIndex], "timeLock")) && (int(locations[loadedLocationIndex].timeLock));
	if (CheckAttribute(pchar, "questTemp.TimeLock") || isTimeLock) return;

	float fTime = GetEventData();
    if (int(fTime) == 24) fTime -= 24.0; // ugeen fix

	Environment.time = fTime;
	int nOldHour     = int(Environment.date.hour);
	int nNewHour     = int(fTime);
	int nNewMin      = int((fTime - nNewHour) * 60);
	int nNewSec      = int(((fTime - nNewHour) * 60 - nNewMin) * 60);

	Environment.date.min  = nNewMin;
	Environment.date.hour = nNewHour;
	Environment.date.sec  = nNewSec;
	worldMap.date.hour    = nNewHour;
	worldMap.date.min     = nNewMin;

	// aref aCurWeather = GetCurrentWeather(); ~!~ Не тут, ниже

    SetCameraForWeather();

	Whr_DebugLog("Whr_TimeUpdate : Hour : " + nNewHour + " min : " + nNewMin + " sec : " + nNewSec + " oldHour : " + nOldHour);

	if (nNewHour < nOldHour)
	{
		AddDataToCurrent(0,0,1);
		Weather.Time.time = GetTime();
	}

    if (nOldHour != nNewHour)
        Event("NextHour", "l", nNewHour);

	if (iBlendWeatherNum < 0) return;

	bool bRain = false;
	if (CheckAttribute(&WeatherParams,"Rain"))
	{
		bRain = bool(WeatherParams.Rain);
		Whr_DebugLog("bRain : " + bRain);
	} 

	Whr_DebugLog("Whr_CheckStorm() : " + Whr_CheckStorm());

	iCurWeatherNum   = FindWeatherByHour(int(fTime));
	iBlendWeatherNum = FindBlendWeather(iCurWeatherNum);

	Whr_DebugLog("iCurWeatherNum : " + iCurWeatherNum + " iBlendWeatherNum : " + iBlendWeatherNum);

	if (bSeaActive)
	{
		//Mett: для динамического освещения островов
		Island.LightingPath = GetIslandLightingPath();
		Island.FogDensity 	= Weather.Fog.IslandDensity;

		//Mett: выставляем туман, если есть модель для отражения, то вешаем туман на неё, если нет, то на модель острова
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, float(Weather.Fog.IslandDensity));

		//Mett: опрос на обновление моря при каждой смене игровых минут
		DoQuestCheckDelay("update_sea_environment", 0.1); 
		//Mett: смена текста локации в баттлинтерфейсе
		DoQuestCheckDelay("update_battle_interface", 0.1);	

		if (CheckAttribute(&Weathers[iCurWeatherNum], "SpecialSeaFog"))
            sCurrentFog = "SpecialSeaFog";
	}
	else // суша - туманы по утрам и вечерам
	{
		if (CheckAttribute(&WeatherParams, "Fog.ThisDay") && int(WeatherParams.Fog.ThisDay))
		{
            if (iBlendWeatherNum > -1)
            {
                if (CheckAttribute(&Weathers[iBlendWeatherNum],"SpecialLandFog") && (int(WeatherParams.Fog.Type) == int(Weathers[iBlendWeatherNum].SpecialLandFog.Type)))
                {
                    if (Whr_CheckInsideLoc()) sBlendedFog = "Fog";
                    else sBlendedFog = "SpecialLandFog";
                }
                else sBlendedFog = "Fog";
            }

			if (CheckAttribute(&Weathers[iCurWeatherNum],"SpecialLandFog") && (int(WeatherParams.Fog.Type) == int(Weathers[iCurWeatherNum].SpecialLandFog.Type)))
			{
				if (Whr_CheckInsideLoc()) sCurrentFog = "Fog";
				else sCurrentFog = "SpecialLandFog";
			}
			else sCurrentFog = "Fog";
		}
	}			

	// Mett: переработал систему дождей
    // Фильтр локаций, где низя дождить + не для штормов где своя специфика
	bool bIsRainEnable = Whr_isRainEnable() && !Whr_CheckStorm();
	if (CheckAttribute(&WeatherParams,"Rain") && bIsRainEnable)
	{
		if (CheckAttribute(&WeatherParams,"Rain.Type"))
		{
			if (int(WeatherParams.Rain.Type) == 0)
                Whr_SetRainExt1(iCurWeatherNum, iBlendWeatherNum, bRain);
			else if (int(WeatherParams.Rain.Type) == 1)
                Whr_SetRainExt2(iCurWeatherNum, iBlendWeatherNum, bRain);
			else if (int(WeatherParams.Rain.Type) == 2)
                Whr_SetRainExt3(iCurWeatherNum, iBlendWeatherNum, bRain);
		}
		else Whr_SetRainExt1(iCurWeatherNum, iBlendWeatherNum, bRain);
	}

    Whr_CheckLocation();

	if (nNewHour != nOldHour)
	{
		bool bUpdate = false;
		Whr_UpdateWeatherHour();
		if (bSeaActive && !bAbordageStarted)
		{
			if (nNewHour == 6 || nNewHour == 7 || nNewHour == 18 || nNewHour == 19 || nNewHour == 20) bUpdate = true;
		}
		if (bUpdate) 
		{
			if (CheckAttribute(&InterfaceStates,"FoliageDrawDistance") && int(InterfaceStates.FoliageDrawDistance) >= 1000)
			{
				Sea_UpdateIslandGrass(AISea.Island); // апдейт растительности на островах
			}
		}
	}

	// update weather: sun lighting
	FillWeatherData(iCurWeatherNum, iBlendWeatherNum);
	Whr_ModifySeaFog(fWeatherSpeed);
    fFogDensity = float(Weather.Fog.Density);

	if (nNewHour != nOldHour) // апдейт фонарей только утром и вечером
	{
		if (nNewHour == 6 || nNewHour == 20) Whr_ChangeDayNight();
	}
	Weather.isDone = "";

	//update rain: rain drops, rain colors, rain size, rainbow
	if (CheckAttribute(&WeatherParams,"Rain") && int(WeatherParams.Rain) && bIsRainEnable)
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
    float fTmp, fTmp2;
	int  iTestWeather;
	bool bQuestlockWeather;

    iCurWeatherHour = int(GetHour());

    // По умолчанию текущее состояние штормов/торнадо
    // TO_DO: Сейчас шторм на суше не прекратится до выхода в море и нет синхронизации
    bWeatherIsStorm = CheckAttribute(&WeatherParams,"Storm") && int(WeatherParams.Storm);
    bool bWhrTornado = CheckAttribute(&WeatherParams,"Tornado") && int(WeatherParams.Tornado);
    // Проверка принудительного переключения в локациях
	Whr_CheckLocationStorm(&bWeatherIsStorm, &bWhrTornado);
    // Синхронизируем с атрибутами
	WeatherParams.Storm = bWeatherIsStorm;
	WeatherParams.Tornado = bWhrTornado;

    bool bRain = false;
	if (CheckAttribute(&WeatherParams,"Rain") && !Whr_CheckStorm())
        bRain = bool(WeatherParams.Rain); // в штормах своя специфика дождей

	if (bRain)
	{
		fTmp = float(WeatherParams.Rain.StartTime) + float(WeatherParams.Rain.Duration)/60.0;
		if (GetTime() > fTmp)
		{
			bRain 						= false;
			WeatherParams.Rain 			= false;
			WeatherParams.Rain.ThisDay 	= false;
		}
	}

	if (iNextWeatherNum != -1)
	{
		iCurWeatherNum = iNextWeatherNum;
		iNextWeatherNum = -1;
		Whr_DebugLog("Weather: used preset weather " + iCurWeatherNum);
	}
	else
	{
        int iWeatherFound[MAX_WEATHERS];
        int iNumWeatherFound = 0;
		// search weather for hour
		for (int i = 0; i < MAX_WEATHERS; i++)
		{
			if (CheckAttribute(&Weathers[i], "Skip") && int(Weathers[i].skip)) continue;

			int iMin = int(Weathers[i].Hour.Min);
			int iMax = int(Weathers[i].Hour.Max);
			if (iMin == iMax && iMin != iCurWeatherHour) continue;
			if (iMin > iMax) {
				if (iCurWeatherHour < iMin && iCurWeatherHour > iMax) continue;
			}
			if (iMin < iMax) {
				if (iCurWeatherHour < iMin || iCurWeatherHour > iMax) continue;
			}

			if (bWeatherIsStorm != int(Weathers[i].Storm)) continue;
			//if (bWhrTornado == true && !int(Weathers[i].Tornado)) continue;

			iWeatherFound[iNumWeatherFound] = i;
			iNumWeatherFound++;
		}

		if (iNumWeatherFound == 0)
		{
			Trace("Error: iNumWeatherFound = 0, for hour = " + iCurWeatherHour);
			iCurWeatherNum = 0;
		}
		else
		{
			iCurWeatherNum = iWeatherFound[rand(iNumWeatherFound-1)];
			Whr_DebugLog("iCurWeatherNum : " + iCurWeatherNum + " iNumWeatherFound :" + iNumWeatherFound);
		}
	}

	sunIsShine = true;
	bQuestlockWeather = false;

	if (CheckAttribute(pchar, "location"))
	{
        int iCurLocation = reload_location_index;
		if (iCurLocation != -1)
		{   // Суша
			if (CheckAttribute(&locations[iCurLocation], "QuestlockWeather"))
			{
				iTestWeather = FindWeather(locations[iCurLocation].QuestlockWeather);
				if (iTestWeather != -1)
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
		else
		{   // Море
			iCurLocation = FindIsland(pchar.location);
			if (iCurLocation != -1)
			{
				if (CheckAttribute(&Islands[iCurLocation], "QuestlockWeather"))
				{
					iTestWeather = FindWeather(Islands[iCurLocation].QuestlockWeather);
					if (iTestWeather != -1)
					{
						iCurWeatherNum = iTestWeather;
						bQuestlockWeather = true;
					}
				}
			}
		}
	}

	if (!bQuestlockWeather)
        iBlendWeatherNum = FindBlendWeather(iCurWeatherNum);
	else
        iBlendWeatherNum = -1;

	Whr_DebugLog("iBlendWeatherNum found : " + iBlendWeatherNum + " bQuestlockWeather : " + bQuestlockWeather);

	if (startGameWeather)
	{
		iTestWeather = int(InterfaceStates.startGameWeather);
		if (iTestWeather != -1)
		{
			iCurWeatherNum = iTestWeather;
			bQuestlockWeather = true;
		}
		startGameWeather = false;
	}

	// create main module Weather
	DeleteAttribute(&Weather,"");
	if (!isEntity(&Weather)) CreateEntity(&Weather, "Weather");
	SetDayCycle(sWeatherDayCycleType); //Mett: установка суточного цикла

	aref aCurWeather = GetCurrentWeather();

	sLightingPath    = Whr_GetString(aCurWeather,"Lighting");
	sLmLightingPath  = Whr_GetString(aCurWeather,"LightingLm");
	sInsideBack      = Whr_GetString(aCurWeather,"InsideBack");
	bWeatherIsNight  = bool(Whr_GetLong(aCurWeather,"Night"));
	bWeatherIsLight  = bool(Whr_GetLong(aCurWeather,"Lights"));

    // Ветер -->
	if (CheckAttribute(PChar, "WorldMap.WindAngle"))
	{
        fTmp  = float(PChar.WorldMap.WindAngle);
        fTmp2 = float(worldMap.WindF) * WIND_MAX_POWER;
        DeleteAttribute(PChar, "WorldMap.WindAngle");
        DeleteAttribute(PChar, "WorldMap.WindForce");
	}
	else
    {
        fTmp  = GetAttributeFloatOrDefault(PChar, "Wind.Angle", frand(PIm2));
        fTmp2 = GetAttributeFloatOrDefault(PChar, "Wind.Speed", Whr_GetFloat(aCurWeather, "Wind.Speed"));
    }
	fWeatherAngle = fTmp;  Weather.Wind.Angle = fTmp;  PChar.Wind.Angle = fTmp;
	fWeatherSpeed = fTmp2; Weather.Wind.Speed = fTmp2; PChar.Wind.Speed = fTmp2;
    fWeatherDelta = 0.0;
    SetEventHandler("frame","Whr_OnWindChange",0);
    // <-- Ветер

    // Туманы (+ color, ambient) -->
	sCurrentFog = "Fog";
	sBlendedFog = "Fog";
	if (bSeaActive) // Море ~!~
	{
		if (CheckAttribute(aCurWeather, "SpecialSeaFog")) sCurrentFog = "SpecialSeaFog"; 
	}
	else // Суша - туманы по утрам и вечерам
	{
		if (CheckAttribute(&WeatherParams, "Fog.ThisDay") && int(WeatherParams.Fog.ThisDay))
		{
            if (iBlendWeatherNum > -1)
            {
                if(CheckAttribute(&Weathers[iBlendWeatherNum],"SpecialLandFog") && (int(WeatherParams.Fog.Type) == int(Weathers[iBlendWeatherNum].SpecialLandFog.Type)))
                {
                    if (Whr_CheckInsideLoc()) sBlendedFog = "Fog";
                    else sBlendedFog = "SpecialLandFog";
                }
                else sBlendedFog = "Fog";
            }

			if(CheckAttribute(aCurWeather,"SpecialLandFog") && (int(WeatherParams.Fog.Type) == int(aCurWeather.SpecialLandFog.Type)))
			{
				if (Whr_CheckInsideLoc()) sCurrentFog = "Fog";
				else sCurrentFog = "SpecialLandFog";
			}
			else sCurrentFog = "Fog";
		}
	}

	FillWeatherData(iCurWeatherNum, iBlendWeatherNum); // Бленд туманов и освещения
	Whr_ModifySeaFog(fWeatherSpeed); // TO_DO: Здесь 2 вызова...
    fFogDensity = float(Weather.Fog.Density);
    SetEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor",0);
    // <-- Туманы (+ color, ambient)

    Weather.Time.time = GetTime();
	if (iBlendWeatherNum < 0 || bQuestlockWeather) 
	{
		Weather.Time.speed = 350.0; // количество секунд на смену погоды
		Weather.Time.updatefrequence = 12.0; // количество обновлений на смену погоды	
	}
	else
	{
        if (bMainMenu)
		{   // меню
			Weather.Time.speed = 2000.0;
			Weather.Time.updatefrequence = 12; // количество обновлений на смену погоды
		}
		else if (bSeaActive && !bAbordageStarted)
		{
			if (iArcadeSails == 1) // скорости в аркаде больше, время быстрее
			{
				Weather.Time.speed = 250.0; // количество секунд на смену погоды
				Weather.Time.updatefrequence = 10; // каждые 6 минут		
			}
            else
            {
                Weather.Time.speed = 450.0;
                Weather.Time.updatefrequence = 15;
            }
		}
		else
		{   // суша
			Weather.Time.speed = 350.0;
			Weather.Time.updatefrequence = 12; // количество обновлений на смену погоды
		}

		if (CheckAttribute(PChar, "questTemp.TimeLock"))
            Weather.Time.speed = 99999.0; // лочим ~!~
	}
	Weather.isDone = "";

	int iLocation = FindLocation(PChar.location);
	if (iLocation != -1)
	{
		ref rLoc = &Locations[iLocation];

		if (CheckAttribute(rLoc, "environment.weather.rain") && !int(rLoc.environment.weather.rain))
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
        WhrCreateRainEnvironment();
	else
        ClearRainEnvironment();

	GenerateSkyCurrentDay();

	WhrCreateSunGlowEnvironment();
	WhrCreateLightningEnvironment();
	WhrCreateSkyEnvironment();
	WhrCreateSeaEnvironment();
	WhrCreateAstronomyEnvironment();

    if (bWeatherIsStorm)
    {
        Whr_DebugLog("Start LightningInStorm");
        WhrStartLightning();
    }

	if (iLocation != -1)
	{
		if(CheckAttribute(&Locations[iLocation], "lockWeather"))
            bWhrTornado = false;
	}
	if (bWhrTornado) WhrCreateTornadoEnvironment();

	bWeatherLoaded = true;

	if (bSeaActive)
	{
		Island.LightingPath = GetIslandLightingPath();
        Island.FogDensity = Weather.Fog.IslandDensity;
		//Mett: выставляем туман, если есть модель для отражения, то вешаем туман на неё, если нет, то на модель острова
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, float(Weather.Fog.IslandDensity));
	}
    Whr_ModifySeaFog(fWeatherSpeed); // TO_DO: Здесь 2 вызова...

	Whr_DebugLog(" GetTime() : " + GetTime());
    SetCameraForWeather();
	if (!bQuestlockWeather) Event("WeatherTimeUpdate", "f", GetTime());
}

void Whr_LoadNextWeather(int nPlus)
{
	if(!isEntity(&Weather))	return;

	iCurWeatherNum 	= iCurWeatherNum + nPlus;	
	Whr_DebugLog("Whr_LoadNextWeather :  iCurWeatherNum " + iCurWeatherNum);

	if (Whr_CheckStorm())
	{
		if(iCurWeatherNum < 0)   iCurWeatherNum = 47;
		if(iCurWeatherNum >= 48) iCurWeatherNum = 24;
	}
	else
	{
		if(iCurWeatherNum < 0)   iCurWeatherNum = 23;
		if(iCurWeatherNum >= 24) iCurWeatherNum = 0;
	}		

	Whr_DebugLog("ПОГОДА: " + Weathers[iCurWeatherNum].id + " ОСВЕЩЕНИЕ: " + Weathers[iCurWeatherNum].Lighting);

//	iNextWeatherNum = iCurWeatherNum;	
	iNextWeatherNum = -1;	
	iCurWeatherHour = int(Weathers[iCurWeatherNum].Hour.Min);

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
	if (iLocation != -1)
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
                || loc.type == "quest_deck"
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

void CreateSky(int SkyOption)
{
	WeatherParams.weather_sky = SkyOption;
	Whr_UpdateWeather();
}

void CreateRain(int DurationTime, bool WhrLight, bool WhrRainbow)
{
	if (WhrLight == true) WeatherParams.Rain.WhrLight = true;
	if (WhrRainbow == true) WeatherParams.Rain.WhrRainbow = true;

	WeatherParams.Rain.ThisDay 		= true;
	WeatherParams.Rain.StartTime    = float(Environment.time);
	WeatherParams.Rain.Duration     = DurationTime;
	WeatherParams.Rain.sDay			= rand(8);
	WeatherParams.Rain.sMorning		= rand(5);
	WeatherParams.Rain.sEvening		= rand(7);
	WeatherParams.Rain.sNight		= rand(6);
	WeatherParams.Rain.sTwilight 	= WeatherParams.Rain.sNight;
	WeatherParams.Rain.Type			= 2;
	WeatherParams.Rain.year 		= GetDataYear();
	WeatherParams.Rain.month 		= GetDataMonth();
	WeatherParams.Rain.day 			= GetDataDay();
	WeatherParams.Rain.time 		= float(WeatherParams.Rain.StartTime);
	Whr_UpdateWeather();
}

void CreateRainSky(int RainSkyOption)
{
	WeatherParams.Rain.sDay			= RainSkyOption;
	WeatherParams.Rain.sMorning		= RainSkyOption;
	WeatherParams.Rain.sEvening		= RainSkyOption;
	WeatherParams.Rain.sNight		= RainSkyOption;
	Whr_UpdateWeather();
}

void CreateWind(int WindSide, int WindSpeed)
{
	pchar.wind.angle = WindSide;
	fWeatherAngle = float(WindSide);
	pchar.wind.speed = WindSpeed;
	fWeatherSpeed = float(WindSpeed);
	Whr_UpdateWeather();
}

void CreateFog()
{
	// Туман работает с 5-8 и 20-23 часов
	WeatherParams.Fog 			= true;
	WeatherParams.Fog.ThisDay 	= true;
	if (GetHour() >= 5 && GetHour() < 9)   WeatherParams.Fog.Type	= 0;
	if (GetHour() >= 20 && GetHour() < 24) WeatherParams.Fog.Type	= 1;
	Whr_UpdateWeather();
}

void StopRain()
{
	WeatherParams.Rain 			= false;
	WeatherParams.Rain.ThisDay 	= false;
	Whr_UpdateWeather();
}

void StopFog()
{
	WeatherParams.Fog 			= false;
	WeatherParams.Fog.ThisDay 	= false;
	Whr_UpdateWeather();
}
