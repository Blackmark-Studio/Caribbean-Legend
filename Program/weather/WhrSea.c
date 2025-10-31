//********************************************************************
// Mett: базовая физика и структура моря
// Sith: настройка моря и туманов
// Ugeen: туманы от силы ветра, правки + фиксы
//********************************************************************

//базовое значение сетки без учёта настроек качества моря
#define LOCATION_GRID_STEP		0.151
#define SEA_GRID_STEP			0.051

//отдельный объект, в котором будут храниться настройки нового моря
object SeaSettings;	

int iSkyColor = argb(0, 255, 255, 255);

void WhrDeleteSeaEnvironment()
{
	DeleteAttribute(&Sea,"");
}

void WhrCreateSeaEnvironment()
{
	aref	aCurWeather = GetCurrentWeather();
	aref	aSea; makearef(aSea,aCurWeather.Sea);
	aref	aSea2; makearef(aSea2, aCurWeather.Sea2);
	aref	aCommon; makearef(aCommon, WhrCommonParams.Sea);
	
	float fMaxSeaHeight;
	float fMaxSeaDistance = 1600;

	if (CheckAttribute(&Sea,"MaxSeaHeight")) 
	{ 
		fMaxSeaHeight = stf(Sea.MaxSeaHeight); 
	}
	DeleteAttribute(&Sea,"");

	Sea.Clear = "";

	ref mchr 			= GetMainCharacter();
	string sLocation 	= mchr.location;

	float FogDensity 	= 1.0;
	float FogSeaDensity = 1.0

	int iLocation 		= FindLocation(sLocation);
	int iIsland 		= FindIsland(sLocation);

	if(bMainMenu)
	{
		SetSeaSettings();
		Sea.MaxDim = 65536*2;
		fMaxSeaHeight 	= Whr_SetLocationMaxSeaHeight();	
	}
	else
	{
		if(iLocation != -1)
		{
			trace("sLocation : " + sLocation + " iLocation :" + iLocation);
			SetSeaSettings();
			Sea.MaxDim = 65536*2;
			FogDensity 		= 20.0;
			FogSeaDensity 	= 20.0;
			fMaxSeaHeight = Whr_SetLocationMaxSeaHeight();
			fMaxSeaDistance = 3000;
		}
		else
		{
			//изменил расчет детализации волн около островов
			SetSeaSettings();
			fMaxSeaHeight = SetMaxSeaHeight(iIsland);
			if(CheckAttribute(pchar, "debuger_weather"))
			{
				fMaxSeaHeight = stf(pchar.debuger_weather.maxSeaHeight);
			}
			fMaxSeaDistance = 20000;
		}
	}
	Sea.Lights = aCurWeather.Lights;

	Sea.Sun.Color = Whr_GetColor(aCurWeather,"Sun.Color");
	Sea.Sun.HeightAngle = Whr_GetFloat(aCurWeather,"Sun.HeightAngle");
	Sea.Sun.AzimuthAngle = Whr_GetFloat(aCurWeather,"Sun.AzimuthAngle");

	string sCurFog = Whr_GetCurrentFog();
	Sea.Fog.Color = Whr_GetColor(aCurWeather, sCurFog + ".Color");
	Sea.Fog.Enable = Whr_GetLong(aCurWeather, sCurFog + ".Enable");
	Sea.Fog.Start = Whr_GetFloat(aCurWeather, sCurFog + ".Start");
	Sea.Fog.Density = Whr_GetFloat(aCurWeather, sCurFog + ".Density") * FogDensity;
	Sea.Fog.SeaDensity = Whr_GetFloat(aCurWeather, sCurFog + ".SeaDensity") * FogSeaDensity;

	// Advanced Sea initialize	
	Whr_SetSeaFromWind(fWeatherSpeed, fMaxSeaHeight);

	Sea.Sea2.WaterColor = Whr_GetColor(SeaSettings, "WaterColor");
	Sea.Sea2.SkyColor = Whr_GetColor(SeaSettings, "SkyColor");
	Sea.Sea2.BumpScale = Whr_GetFloat(SeaSettings, "BumpScale");

	Sea.Sea2.Amp1 = Whr_GetFloat(SeaSettings, "Amp1");
	Sea.Sea2.AnimSpeed1 = Whr_GetFloat(SeaSettings, "AnimSpeed1");
	Sea.Sea2.Scale1 = Whr_GetFloat(SeaSettings, "Scale1");
	Sea.Sea2.MoveSpeed1 = Whr_GetString(SeaSettings, "MoveSpeed1");

	Sea.Sea2.Amp2 = Whr_GetFloat(SeaSettings, "Amp2");
	Sea.Sea2.AnimSpeed2 = Whr_GetFloat(SeaSettings, "AnimSpeed2");
	Sea.Sea2.Scale2 = Whr_GetFloat(SeaSettings, "Scale2");
	Sea.Sea2.MoveSpeed2 = Whr_GetString(SeaSettings, "MoveSpeed2");

	Sea.Sea2.PosShift = Whr_GetFloat(SeaSettings, "PosShift");

	Sea.Sea2.Reflection = Whr_GetFloat(SeaSettings, "Reflection");
	Sea.Sea2.Transparency = Whr_GetFloat(SeaSettings, "Transparency");
	Sea.Sea2.Attenuation = Whr_GetFloat(SeaSettings, "Attenuation");
	Sea.Sea2.Frenel = Whr_GetFloat(SeaSettings, "Frenel");

	Sea.Sea2.FoamK = Whr_GetFloat(SeaSettings, "FoamK"); //пена на волнах
	Sea.Sea2.FoamV = Whr_GetFloat(SeaSettings, "FoamV");
	Sea.Sea2.FoamUV = Whr_GetFloat(SeaSettings, "FoamUV");
	Sea.Sea2.FoamTexDisturb = Whr_GetFloat(SeaSettings, "FoamTexDisturb");

	Sea.Sea2.FoamEnable = Whr_SetSeaFoam(); //пена на волнах
	Sea.Sea2.SimpleSea = sti(InterfaceStates.SimpleSea);

	Sea.MaxSeaHeight = fMaxSeaHeight;
	Sea.MaxSeaDistance = fMaxSeaDistance;
	
	Sea.CubeMap.Size = 1024;	
	Sea.CubeMap.VectorsSize = 512;
	
	Sea.CubeMap.Format = "r5g6b5";
	
	Sea.isDone = "";
	Whr_DebugLog("MaxSeaDistance - " + fMaxSeaDistance);

	// boal 14/09/06 запоминаем среднюю волну для моря (не локации)
//	if (bSeaActive && !bAbordageStarted)
//	{
//		pchar.SystemInfo.ScaleSeaHeight = GetScaleSeaHeight();
//	}
}

void SetSeaSettings()
{
	Sea.LodScale = LodScale;
	Sea.MaxVertices = MaxVertices;
	Sea.MaxIndices = MaxIndices;
	Sea.MaxWaveDistance = MaxWaveDistance;
	Sea.MaxDim = 65536*14;
	Sea.MinDim = 128;
	Sea.GridStep = SEA_GRID_STEP + SeaDetailsCoeff();

	Sea.Sea2.LodScale = 0.5;
	Sea.Sea2.GridStep = SEA_GRID_STEP + SeaDetailsCoeff();
}

void SetSeaGridStep(float SeaDetails)
{
	if (!IsEntity(&Sea)) { return; }

	ref mchr = GetMainCharacter();
	string sLocation = mchr.location;

	// if current location is land - return
	if(FindLocation(sLocation) != -1)
	{
		if(CheckAttribute(&locations[FindLocation(sLocation)], "fastreload"))
		{
			return;
		}
	}

	Sea.Sea2.GridStep = SEA_GRID_STEP + SeaDetailsCoeff();

	Sea.Sea2.SimpleSea = sti(InterfaceStates.SimpleSea);
}

// boal 14.09.06 относительная высота волны
float GetScaleSeaHeight()
{
	float fMaxSeaHeight = 0.0;

	if (CheckAttribute(&Sea, "MaxSeaHeight")) { fMaxSeaHeight = stf(Sea.MaxSeaHeight); }
	
	aref arWeath = GetCurrentWeather();
	float fAmp1, fAmp2;
	
	if(CheckAttribute(arWeath,"Sea2.Amp1")) fAmp1 = stf(arWeath.Sea2.Amp1);
	else									fAmp1 = 1.0;
	
	if(CheckAttribute(arWeath,"Sea2.Amp2")) fAmp2 = stf(arWeath.Sea2.Amp2);
	else									fAmp2 = 1.0;
	
	float fScale;
	if (fMaxSeaHeight >= (fAmp1 + fAmp2))
	{
		fScale = 1.0; 
	}
	else
	{
		fScale = fMaxSeaHeight / (fAmp1 + fAmp2);
	}

	fAmp1 = fAmp1 * fScale;
	fAmp2 = fAmp2 * fScale;
		
	return (fAmp1 + fAmp2) / 2.0;
}

//настройка сетки в интерфейсе, вынес в отдельную функцию
float SeaDetailsCoeff()
{
	if(!CheckAttribute(InterfaceStates, "SeaDetails"))
	{
		trace("SeaDetailsCoeff: missing attribute 'SeaDetails'!");
		return 0.05;
	}

	float fSeaDetailsCoeff = 0.1 * (1.0 - fclamp(0.4, 1.0, stf(InterfaceStates.SeaDetails)));
	return fSeaDetailsCoeff;
}

//направление волн в море соответствует направлению ветра
string Whr_SetSeaAngle()
{
	float xAng, zAng;
	string _angle = "0.0, 0.0, 2.0";
	if(CheckAttribute(pchar, "debuger_weather")) //если в дебагере
	{
		xAng = -1.0 * stf(pchar.debuger_weather.windAngle.x);
		zAng = -1.0 * stf(pchar.debuger_weather.windAngle.z);
	}
	else
	{
		if(bMainMenu)
		{
			xAng = -3.0;
			zAng = 0.0;
		}
		else
		{
			xAng = -1.0 * stf(worldMap.WindX);
			zAng = -1.0 * stf(worldMap.WindZ);	
		}
	}
	_angle = xAng + ", 0.0, " + zAng;
	return _angle;
}

//шторм
bool Whr_CheckStorm()
{
	bool bRealStorm = CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == true; 				//реальный игровой шторм
	bool bDebugerStorm = CheckAttribute(pchar, "debuger_weather.storm") && pchar.debuger_weather.storm == true; //шторм вызываемый через дебагер

	if(bRealStorm || bDebugerStorm)
	{
		return true;
	}
	return false;
}

//Ugeen: проверка атрибутов шторма и торнадо в текущей локации или на острове
//Sith: пока здесь не используется
void Whr_CheckLocationStorm(ref _storm, ref _tornado)
{
	int 	iCurLocation;
		
	if(CheckAttribute(pchar, "location"))
	{
		iCurLocation = reload_location_index;
		if(iCurLocation != -1)	// локация
		{
			if(CheckAttribute(&locations[iCurLocation], "storm"))
			{
				_storm 				= 1; 
			}
			if(CheckAttribute(&locations[iCurLocation], "tornado"))
			{
				_tornado 			= 1;
			}
			//малый шторм в локациях
			if(CheckAttribute(&locations[iCurLocation], "alwaysStorm"))
			{
				_storm 				= 1; 
				_tornado 			= 1;				
				if (CheckAttribute(&locations[iCurLocation], "alwaysStorm.WaveHeigh")) locations[iCurLocation].MaxWaveHeigh = 2.5; 		// установим уровень воды
			}
			//большой шторм в локациях (в ККС не используется но пусть будет)
			if(CheckAttribute(&locations[iCurLocation], "alwaysStorm_2"))
			{
				_storm 				= 1; 
				_tornado 			= 1;				
				if (CheckAttribute(&locations[iCurLocation], "alwaysStorm_2.WaveHeigh")) locations[iCurLocation].MaxWaveHeigh = 40.0; 	// установим уровень воды
			}			
		}
		else	// остров
		{		
			iCurLocation = FindIsland(pchar.location);
			if(iCurLocation != -1)
			{
				if(CheckAttribute(&Islands[iCurLocation], "storm"))
				{
					_storm 			= 1; 
				}
				if(CheckAttribute(&Islands[iCurLocation], "tornado"))
				{
					_tornado 		= 1;
				}
				if(CheckAttribute(&Islands[iCurLocation], "alwaysStorm"))
				{
					_storm 			= 1; 
					_tornado 		= 1;
				}
			}		
		}
	}	
}

//Sith: шторм в локациях упрощенная функция. Можно потом заменить. 
//Island не используется, т.к. обычно у островов работает открытое море, а там свои ограничения на высоту волн у островов в шторм
bool Whr_CheckLandStorm()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	int iIsland = FindIsland(sLocation);
	if(iLocation != -1) // локация
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "alwaysStorm"))
		{
			bool bLocationStorm = loc.alwaysStorm == true;
			if(bLocationStorm)
			{
				return true;
			}
		}
		
	}
	return false;	
}

//локации с пляжами
bool Whr_CheckSeashore()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			bool bOk = 	loc.type == "seashore" ||
						loc.type == "questisland" ||						
						loc.type == "mayak" || 
						loc.type == "teno";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

//локации порта, города и форта
bool Whr_CheckSeaTown()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			bool bOk = 	loc.type == "town" || 
						loc.type == "port" || 
						loc.type == "fort" || 
						loc.type == "fort_attack";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

//проблемные локации. Сюда можно записывать локации, где слишком видно дно или другие шероховатости
bool Whr_CheckSeaFix()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "id"))
		{
			bool bOk = 	loc.id == "Tortuga_town"||
						loc.id == "Shore67";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

//проблемные локации. Сюда можно записывать локации, где вода затапливает причал
bool Whr_CheckSeaHeightFix()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "id"))
		{
			bool bOk = 	loc.id == "FortFrance_town"||
						loc.id == "SantoDomingo_town"||
                        loc.id == "Serpentine1"||
						loc.id == "PortRoyal_town";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

//локация палубы
bool Whr_CheckDeck()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			bool bOk = 	loc.type == "deck" ||
						loc.type == "deck_fight";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

//локация каюты
bool Whr_CheckCabine()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			bool bOk = 	loc.type == "residence" || 
						loc.type == "boarding_cabine";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

//локация пещеры/подземелья (может быть с водой)
bool Whr_CheckCave()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			bool bOk = loc.type == "cave" || loc.type == "dungeon" || loc.type == "Judgement_dungeon" || loc.type == "Judgement_hell_dungeon";
			if(bOk)
			{
				return true;
			}
		}
	}	
	return false;
}

//локация грота с водой
bool Whr_CheckGrotto()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			bool bOk = loc.type == "grotto";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

//локации ГПК
bool Whr_CheckLSC()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			bool bOk = loc.type == "LostShipsCity" || loc.type == "LSC_inside";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

//подводные локации
bool Whr_CheckUnderwater()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			bool bOk = loc.type == "underwater";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

float fGlobalFoamV = 95.0;	//процент высоты пены относительно средней высоты волны

//где используется пена на волнах
bool Whr_SetSeaFoam()
{
	bool bSet = false;

	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation == -1)
	{		
		bSet = true;
	}
	if(iLocation != -1)
	{
		if(Whr_CheckSeashore() || Whr_CheckSeaTown() || Whr_CheckSeaFix() || Whr_CheckSeaHeightFix() || Whr_CheckGrotto() || Whr_CheckDeck() || Whr_CheckCabine() || Whr_CheckLSC() || Whr_CheckLandStorm())
		{
			bSet = true;
		}
	}
	if(CheckAttribute(pchar, "debuger_weather"))
	{		
		bSet = sti(pchar.debuger_weather.FoamEnable);
	}
	return bSet;
}

//расчет высоты волны в локации
float Whr_SetLocationMaxSeaHeight()
{
	aref aCurWeather = GetCurrentWeather();
	float fMaxSeaHeight = 0.5;	//базовое значение 0.5

	if(CheckAttribute(Sea, "CabinSeaHeight"))
	{
		fMaxSeaHeight = stf(Sea.CabinSeaHeight);
		DeleteAttribute(Sea, "CabinSeaHeight");
		return fMaxSeaHeight;
	}
	if(CheckAttribute(Sea, "AbordageSeaHeight"))
	{
		fMaxSeaHeight = stf(Sea.AbordageSeaHeight);
		DeleteAttribute(Sea, "AbordageSeaHeight");
		return fMaxSeaHeight;
	}
	if(Whr_CheckStorm() || Whr_CheckLandStorm())
	{
		fMaxSeaHeight = 2.5;	//сильное волнение на пляжах и т.д.
		if(Whr_CheckSeaTown()) fMaxSeaHeight = 2.0;	//умеренное волнение
		if(Whr_CheckSeaHeightFix())	fMaxSeaHeight = 1.5;	//слабое волнение
	}
	else
	{
		if(Whr_CheckSeashore() || Whr_CheckSeaTown() || Whr_CheckSeaFix() || Whr_CheckGrotto() || Whr_CheckDeck() || Whr_CheckCabine() || Whr_CheckLSC())
		{
			fMaxSeaHeight = 1.1;	//небольшое волнение
		}
		if (Whr_CheckSeaHeightFix())
		{
			fMaxSeaHeight = 0.75;	//небольшое волнение
		}
		if(Whr_CheckCave())
		{
			fMaxSeaHeight = 0.25;	//стоячая вода без волнения
		}
		if(bMainMenu)
		{
			fMaxSeaHeight = 4.0;	//волнение в меню
		}
	}
	return fMaxSeaHeight;
}

//расчет высоты пены
float Whr_SetFoamHeight(float fAmp1, float fAmp2, float fMaxSeaHeight)
{
	float fScale = (fAmp1 + fAmp2) / 2.0;
	float fFoamV = 0.25 + wPercentFloat(fScale, fGlobalFoamV);

	bool bCheckStorm = Whr_CheckStorm(); //шторм

	float fCoeff = 0.5523;

	if(fMaxSeaHeight < MAX_SEA_HEIGHT)
	{
		if(!bCheckStorm)	//в обычном море
		{
			wRange(&fFoamV, 0.1, fMaxSeaHeight * fCoeff);
		}
		if(bCheckStorm)		//в штормовом море
		{
			wRange(&fFoamV, fMaxSeaHeight * 0.5, fMaxSeaHeight * fCoeff);
		}
	}
	else
	{
		if(bCheckStorm)
		{
			wRange(&fFoamV, 8.5, 8.5);
		}
	}
	return fFoamV;
}

//настройка цвета воды
int Whr_SetWaterColor(float fMaxSeaHeight)
{
	int iLocation = FindLocation(pchar.location);
	int iWaterColor = argb(  0,  0, 70,120 );				
	bool bRain = CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain); // дождь
	// цвет моря в шторм
	if(Whr_CheckStorm() || Whr_CheckLandStorm())
	{
		if (GetTime() >=  0.0) 						iWaterColor = argb(  0,  5, 15, 22 );
		if (GetTime() >=  1.0) 						iWaterColor = argb(  0,  5, 15, 22 );
		if (GetTime() >=  2.0) 						iWaterColor = argb(  0,  5, 17, 26 );
		if (GetTime() >=  3.0)						iWaterColor = argb(  0,  5, 18, 31 );
		if (GetTime() >=  4.0)					 	iWaterColor = argb(  0,  5, 20, 35 );
		if (GetTime() >=  5.0) 						iWaterColor = argb(  0,  5, 23, 39 );
		if (GetTime() >=  6.0) 						iWaterColor = argb(  0,  5, 25, 42 );
		if (GetTime() >=  7.0) 						iWaterColor = argb(  0,  5, 40, 52 );
		if (GetTime() >=  8.0 && GetTime() < 18.0) 	iWaterColor = argb(  0,  4, 45, 65 );
		if (GetTime() >= 18.0) 						iWaterColor = argb(  0,  5, 40, 52 );
		if (GetTime() >= 19.0) 						iWaterColor = argb(  0,  5, 25, 42 );
		if (GetTime() >= 20.0) 						iWaterColor = argb(  0,  5, 23, 39 );
		if (GetTime() >= 21.0) 						iWaterColor = argb(  0,  5, 20, 35 );
		if (GetTime() >= 22.0) 						iWaterColor = argb(  0,  5, 18, 31 );
		if (GetTime() >= 23.0) 						iWaterColor = argb(  0,  5, 17, 26 );		
	}
	else
	{
		if (bRain)// цвет моря в дождь
		{
			// цвет моря на суше с пляжами
			if(Whr_CheckSeashore())
			{
				if (GetTime() >=  0.0) iWaterColor = argb(  0,  3, 16, 16 );
				if (GetTime() >=  1.0) iWaterColor = argb(  0,  4, 18, 18 );
				if (GetTime() >=  2.0) iWaterColor = argb(  0,  6, 26, 26 );
				if (GetTime() >=  3.0) iWaterColor = argb(  0,  9, 35, 35 );
				if (GetTime() >=  4.0) iWaterColor = argb(  0, 12, 46, 46 );
				if (GetTime() >=  5.0) iWaterColor = argb(  0, 14, 61, 58 );
				if (GetTime() >=  6.0) iWaterColor = argb(  0, 18, 78, 70 );
				if (GetTime() >=  7.0) iWaterColor = argb(  0, 21, 98, 84 );
				if (GetTime() >=  8.0) iWaterColor = argb(  0, 26,118,102 );
				if (GetTime() >=  9.0) iWaterColor = argb(  0, 30,140,121 );
				if (GetTime() >= 10.0) iWaterColor = argb(  0, 35,165,143 );
				if (GetTime() >= 11.0) iWaterColor = argb(  0, 41,188,165 );
				if (GetTime() >= 12.0) iWaterColor = argb(  0, 44,203,179 );
				if (GetTime() >= 13.0) iWaterColor = argb(  0, 43,202,178 );
				if (GetTime() >= 14.0) iWaterColor = argb(  0, 38,178,155 );
				if (GetTime() >= 15.0) iWaterColor = argb(  0, 31,145,126 );
				if (GetTime() >= 16.0) iWaterColor = argb(  0, 25,114, 98 );
				if (GetTime() >= 17.0) iWaterColor = argb(  0, 20, 94, 81 );
				if (GetTime() >= 18.0) iWaterColor = argb(  0, 17, 74, 68 );
				if (GetTime() >= 19.0) iWaterColor = argb(  0, 14, 58, 56 );
				if (GetTime() >= 20.0) iWaterColor = argb(  0, 11, 44, 45 );
				if (GetTime() >= 21.0) iWaterColor = argb(  0,  8, 32, 34 );
				if (GetTime() >= 22.0) iWaterColor = argb(  0,  6, 23, 24 );
				if (GetTime() >= 23.0) iWaterColor = argb(  0,  3, 17, 17 );
			} else {
				// цвет моря на суше в порту, у форта, в гпк, у островов, в пещерах и гротах
				if(Whr_CheckSeaTown() || Whr_CheckSeaFix() || Whr_CheckSeaHeightFix() || Whr_CheckLSC() || fMaxSeaHeight == 3.0 || fMaxSeaHeight == 5.0 || Whr_CheckCave() || Whr_CheckGrotto() || bMainMenu)
				{
					if (GetTime() >=  0.0) iWaterColor = argb(  0,  0, 11, 11 );
					if (GetTime() >=  1.0) iWaterColor = argb(  0,  0, 14, 14 );
					if (GetTime() >=  2.0) iWaterColor = argb(  0,  0, 17, 17 );
					if (GetTime() >=  3.0) iWaterColor = argb(  0,  0, 22, 22 );
					if (GetTime() >=  4.0) iWaterColor = argb(  0,  0, 29, 29 );
					if (GetTime() >=  5.0) iWaterColor = argb(  0,  0, 39, 39 );
					if (GetTime() >=  6.0) iWaterColor = argb(  0,  0, 54, 54 );
					if (GetTime() >=  7.0) iWaterColor = argb(  0,  0, 68, 68 );
					if (GetTime() >=  8.0) iWaterColor = argb(  0,  0, 82, 82 );
					if (GetTime() >=  9.0) iWaterColor = argb(  0,  0, 94, 94 );
					if (GetTime() >= 10.0) iWaterColor = argb(  0,  0,108,108 );
					if (GetTime() >= 11.0) iWaterColor = argb(  0,  0,120,120 );
					if (GetTime() >= 12.0) iWaterColor = argb(  0,  0,128,128 );
					if (GetTime() >= 13.0) iWaterColor = argb(  0,  0,126,126 );
					if (GetTime() >= 14.0) iWaterColor = argb(  0,  0,119,119 );
					if (GetTime() >= 15.0) iWaterColor = argb(  0,  0, 98, 98 );
					if (GetTime() >= 16.0) iWaterColor = argb(  0,  0, 80, 80 );
					if (GetTime() >= 17.0) iWaterColor = argb(  0,  0, 66, 66 );
					if (GetTime() >= 18.0) iWaterColor = argb(  0,  0, 51, 51 );
					if (GetTime() >= 19.0) iWaterColor = argb(  0,  0, 38, 38 );
					if (GetTime() >= 20.0) iWaterColor = argb(  0,  0, 27, 27 );
					if (GetTime() >= 21.0) iWaterColor = argb(  0,  0, 20, 20 );
					if (GetTime() >= 22.0) iWaterColor = argb(  0,  0, 15, 15 );
					if (GetTime() >= 23.0) iWaterColor = argb(  0,  0, 12, 12 );
				}
			} else {
				// остальное море
			if (GetTime() >=  0.0) 	iWaterColor = argb(  0,  5, 11, 22 );
			if (GetTime() >=  1.0) 	iWaterColor = argb(  0,  5, 11, 22 );
			if (GetTime() >=  2.0) 	iWaterColor = argb(  0,  5, 13, 26 );
			if (GetTime() >=  3.0) 	iWaterColor = argb(  0,  5, 15, 31 );
			if (GetTime() >=  4.0) 	iWaterColor = argb(  0,  5, 17, 36 );
			if (GetTime() >=  5.0) 	iWaterColor = argb(  0,  4, 15, 32 );
			if (GetTime() >=  6.0) 	iWaterColor = argb(  0,  5, 21, 42 );
			if (GetTime() >=  7.0) 	iWaterColor = argb(  0,  5, 24, 48 );
			if (GetTime() >=  8.0) 	iWaterColor = argb(  0,  4, 34, 65 );
			if (GetTime() >=  9.0) 	iWaterColor = argb(  0,  3, 40, 74 );
			if (GetTime() >= 10.0) 	iWaterColor = argb(  0,  3, 47, 84 );
			if (GetTime() >= 11.0) 	iWaterColor = argb(  0,  2, 53, 93 );
			if (GetTime() >= 12.0) 	iWaterColor = argb(  0,  1, 57, 99 );
			if (GetTime() >= 13.0) 	iWaterColor = argb(  0,  1, 58,100 );
			if (GetTime() >= 14.0) 	iWaterColor = argb(  0,  1, 58,100 );
			if (GetTime() >= 15.0) 	iWaterColor = argb(  0,  1, 56, 94 );
			if (GetTime() >= 16.0) 	iWaterColor = argb(  0,  1, 52, 86 );
			if (GetTime() >= 17.0) 	iWaterColor = argb(  0,  1, 47, 78 );
			if (GetTime() >= 18.0) 	iWaterColor = argb(  0,  2, 41, 68 );
			if (GetTime() >= 19.0) 	iWaterColor = argb(  0,  3, 33, 55 );
			if (GetTime() >= 20.0) 	iWaterColor = argb(  0,  3, 25, 42 );
			if (GetTime() >= 21.0) 	iWaterColor = argb(  0,  4, 17, 30 );
			if (GetTime() >= 22.0) 	iWaterColor = argb(  0,  5, 11, 21 );
			if (GetTime() >= 23.0) 	iWaterColor = argb(  0,  5, 10, 20 );
		}
		}
		else// цвет моря в хорошую погоду
		{
			// цвет моря на суше с пляжами
		if(Whr_CheckSeashore())
		{
				if (GetTime() >=  0.0) iWaterColor = argb(  0,  4, 20, 20 );
				if (GetTime() >=  1.0) iWaterColor = argb(  0,  5, 23, 23 );
				if (GetTime() >=  2.0) iWaterColor = argb(  0,  8, 32, 33 );
				if (GetTime() >=  3.0) iWaterColor = argb(  0, 11, 43, 45 );
				if (GetTime() >=  4.0) iWaterColor = argb(  0, 15, 58, 58 );
				if (GetTime() >=  5.0) iWaterColor = argb(  0, 18, 77, 73 );
				if (GetTime() >=  6.0) iWaterColor = argb(  0, 22, 99, 88 );
				if (GetTime() >=  7.0) iWaterColor = argb(  0, 27,122,106 );
				if (GetTime() >=  8.0) iWaterColor = argb(  0, 31,147,126 );
				if (GetTime() >=  9.0) iWaterColor = argb(  0, 37,175,151 );
				if (GetTime() >= 10.0) iWaterColor = argb(  0, 84,206,188 );
				if (GetTime() >= 11.0) iWaterColor = argb(  0, 90,229,208 );
				if (GetTime() >= 12.0) iWaterColor = argb(  0, 95,245,224 );
				if (GetTime() >= 13.0) iWaterColor = argb(  0, 94,243,223 );
				if (GetTime() >= 14.0) iWaterColor = argb(  0, 87,218,199 );
				if (GetTime() >= 15.0) iWaterColor = argb(  0, 78,185,169 );
				if (GetTime() >= 16.0) iWaterColor = argb(  0, 31,144,123 );
				if (GetTime() >= 17.0) iWaterColor = argb(  0, 25,117,101 );
				if (GetTime() >= 18.0) iWaterColor = argb(  0, 21, 93, 85 );
				if (GetTime() >= 19.0) iWaterColor = argb(  0, 18, 73, 70 );
				if (GetTime() >= 20.0) iWaterColor = argb(  0, 14, 55, 55 );
				if (GetTime() >= 21.0) iWaterColor = argb(  0, 10, 41, 42 );
				if (GetTime() >= 22.0) iWaterColor = argb(  0,  7, 29, 30 );
				if (GetTime() >= 23.0) iWaterColor = argb(  0,  4, 21, 21 );
			} else {
		// цвет моря на суше в порту, у форта, в гпк, у островов, в пещерах и гротах
		if(Whr_CheckSeaTown() || Whr_CheckSeaFix() || Whr_CheckSeaHeightFix() || Whr_CheckLSC() || fMaxSeaHeight == 3.0 || fMaxSeaHeight == 5.0 || Whr_CheckCave() || Whr_CheckGrotto() || bMainMenu)
		{
				if (GetTime() >=  0.0) iWaterColor = argb(  0,  0, 14, 14 );
				if (GetTime() >=  1.0) iWaterColor = argb(  0,  0, 18, 18 );
				if (GetTime() >=  2.0) iWaterColor = argb(  0,  0, 21, 21 );
				if (GetTime() >=  3.0) iWaterColor = argb(  0,  0, 27, 27 );
				if (GetTime() >=  4.0) iWaterColor = argb(  0,  0, 36, 36 );
				if (GetTime() >=  5.0) iWaterColor = argb(  0,  0, 49, 49 );
				if (GetTime() >=  6.0) iWaterColor = argb(  0,  0, 66, 66 );
				if (GetTime() >=  7.0) iWaterColor = argb(  0,  0, 85, 85 );
				if (GetTime() >=  8.0) iWaterColor = argb(  0,  0,102,102 );
				if (GetTime() >=  9.0) iWaterColor = argb(  0,  0,118,118 );
				if (GetTime() >= 10.0) iWaterColor = argb(  0,  0,136,136 );
				if (GetTime() >= 11.0) iWaterColor = argb(  0,  0,150,150 );
				if (GetTime() >= 12.0) iWaterColor = argb(  0,  0,160,160 );
				if (GetTime() >= 13.0) iWaterColor = argb(  0,  0,158,158 );
				if (GetTime() >= 14.0) iWaterColor = argb(  0,  0,144,144 );
				if (GetTime() >= 15.0) iWaterColor = argb(  0,  0,121,121 );
				if (GetTime() >= 16.0) iWaterColor = argb(  0,  0,100,100 );
				if (GetTime() >= 17.0) iWaterColor = argb(  0,  0, 82, 82 );
				if (GetTime() >= 18.0) iWaterColor = argb(  0,  0, 64, 64 );
				if (GetTime() >= 19.0) iWaterColor = argb(  0,  0, 47, 47 );
				if (GetTime() >= 20.0) iWaterColor = argb(  0,  0, 34, 34 );
				if (GetTime() >= 21.0) iWaterColor = argb(  0,  0, 25, 25 );
				if (GetTime() >= 22.0) iWaterColor = argb(  0,  0, 19, 19 );
				if (GetTime() >= 23.0) iWaterColor = argb(  0,  0, 15, 15 );
			}
			} else {			
				// остальное море
				if (GetTime() >=  0.0) 	iWaterColor = argb(  0,  5, 11, 22 );
				if (GetTime() >=  1.0) 	iWaterColor = argb(  0,  5, 11, 22 );
				if (GetTime() >=  2.0) 	iWaterColor = argb(  0,  5, 13, 27 );
				if (GetTime() >=  3.0) 	iWaterColor = argb(  0,  5, 16, 33 );
				if (GetTime() >=  4.0) 	iWaterColor = argb(  0,  5, 19, 40 );
				if (GetTime() >=  5.0) 	iWaterColor = argb(  0,  5, 23, 48 );
				if (GetTime() >=  6.0) 	iWaterColor = argb(  0,  5, 27, 56 );
				if (GetTime() >=  7.0) 	iWaterColor = argb(  0,  5, 33, 64 );
				if (GetTime() >=  8.0) 	iWaterColor = argb(  0,  4, 39, 75 );
				if (GetTime() >=  9.0) 	iWaterColor = argb(  0,  3, 48, 87 );
				if (GetTime() >= 10.0) 	iWaterColor = argb(  0,  2, 57,101 );
				if (GetTime() >= 11.0) 	iWaterColor = argb(  0,  1, 64,111 );
				if (GetTime() >= 12.0) 	iWaterColor = argb(  0,  0, 69,118 );
				if (GetTime() >= 13.0) 	iWaterColor = argb(  0,  0, 70,120 );
				if (GetTime() >= 14.0) 	iWaterColor = argb(  0,  0, 70,120 );
				if (GetTime() >= 15.0) 	iWaterColor = argb(  0,  0, 67,112 );
				if (GetTime() >= 16.0) 	iWaterColor = argb(  0,  0, 62,103 );
				if (GetTime() >= 17.0) 	iWaterColor = argb(  0,  0, 59, 92 );
				if (GetTime() >= 18.0) 	iWaterColor = argb(  0,  1, 49, 80 );
				if (GetTime() >= 19.0) 	iWaterColor = argb(  0,  2, 39, 65 );
				if (GetTime() >= 20.0) 	iWaterColor = argb(  0,  3, 28, 48 );
				if (GetTime() >= 21.0) 	iWaterColor = argb(  0,  4, 18, 32 );
				if (GetTime() >= 22.0) 	iWaterColor = argb(  0,  5, 11, 21 );
				if (GetTime() >= 23.0) 	iWaterColor = argb(  0,  5, 10, 20 );
			}
		}
	}
	return iWaterColor;
}

//волны от силы ветра
void Whr_SetSeaFromWind(float fSpeed, float fMaxSeaHeight)
{
	int iLocation = FindLocation(pchar.location);
	string sType = "";
	string sMoveSpeed 	= Whr_SetSeaAngle();				//направление волн в море
	Whr_ModifySeaFog( fSpeed );
	bool bRain = CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain); // дождь
	float fFrenel = 0.3;
	
	int iWaterColor = Whr_SetWaterColor(fMaxSeaHeight);		//цвет воды
	int iSkyColor = argb(0, 255, 255, 255);

	//настройки волн
	float fAmp1 = 0.1 + fSpeed * 0.5; 						//амплитуда 1 волны
	wRange(&fAmp1, 0.1, 20.0);
	float fAnimSpeed1 = fSpeed * 0.165; 					//скорость анимации
	wRange(&fAnimSpeed1, 0.1, 3.5);
	float fAmp2 = 0.1 + (fSpeed * 1.5) * 0.05; 				//амплитуда 2 волны
	wRange(&fAmp2, 0.1, 1.35);
	float fAnimSpeed2 = fSpeed * 0.215; 					//скорость анимации
	wRange(&fAnimSpeed2, 0.1, 5.0);

	float fFoamK = 1.0 - fSpeed * 0.05;
	if(GetTime() >= 5.0 && GetTime() <= 20.0)
	{
		wRange(&fFoamK, 0.2, 0.5);
	}
	else
	{
		fFoamK = 0.2;
	}

	float fFoamV = Whr_SetFoamHeight(fAmp1, fAmp2, fMaxSeaHeight); //высота пены
	wRange(&fFoamV, 0.1, 20.0);
	float fFoamUV = 1.0 - fSpeed * 0.025;
	wRange(&fFoamUV, 0.5, 1.0);
	float fFoamTexDisturb = 0.1;

	//размер длины волн
	float fScale1 = 0.75 - fSpeed * 0.025;
	wRange(&fScale1, 0.25, 0.75);
	float fScale2 = 3.75 - fSpeed * 0.075;
	wRange(&fScale2, 2.25, 3.75);
	float fPosShift = 1.25 + fSpeed * 0.025;	//1.65
	wRange(&fPosShift, 1.5, 2.75);

	//дополнительные настройки волн
	float fReflection = 1.0 - fSpeed * 0.035;
	float fTransparency = 1.0 - fSpeed * 0.05;
	float fAttenuation = 1.0 - fSpeed * 0.05;
	float fBumpScale = -10.0 + fSpeed;
	wRange(&fBumpScale, 0.05, 0.08);
	if (fMaxSeaHeight == 3.0 || fMaxSeaHeight == 5.0)
	{
		if (GetTime() >= 5.0 && GetTime() <= 20.0)
		{
			wRange(&fReflection, 0.6, 0.7);	
			wRange(&fAttenuation, 0.2, 0.4);
			if (fMaxSeaHeight < 4.0)
			{
				wRange(&fTransparency, 0.6, 0.8);
			}
			else
			{
				wRange(&fTransparency, 0.1, 0.3);			
			}
		}
		else
		{
			wRange(&fReflection, 0.2, 0.3);	
			wRange(&fTransparency, 0.1, 0.3);
			wRange(&fAttenuation, 0.2, 0.4);
		}
	}
	else
	{
		if (GetTime() >= 5.0 && GetTime() <= 20.0)
		{
			wRange(&fReflection, 0.45, 0.7);
			wRange(&fTransparency, 0.1, 0.3);
			wRange(&fAttenuation, 0.4, 0.6);
		}
		else
		{
			wRange(&fReflection, 0.2, 0.3);	
			wRange(&fTransparency, 0.1, 0.3);
			wRange(&fAttenuation, 0.2, 0.4);
		}
	}
	if (bRain) 
	{
		fReflection = 1.0 - fSpeed * 0.065;
		if (GetTime() >= 5.0 && GetTime() <= 20.0) wRange(&fReflection, 0.45, 0.6);
		else wRange(&fReflection, 0.2, 0.3);
	}
	
	DeleteAttribute(SeaSettings, "");

	if(Whr_CheckStorm() && bSeaActive) //фиксированные настройки для шторма в море
	{
		fAmp1 = 30.0;
		fAnimSpeed1 = 4.0;
		fScale1 = 0.12;

		fAmp2 = 2.0;
		fAnimSpeed2 = 9.0;
		fScale2 = 1.3;

		fFoamK = 0.02;
		fFoamV = 10.0;
		fFoamUV = 0.2;
		fFoamTexDisturb = 0.1;
		fReflection = 0.5;
		fTransparency = 0.1;
		fFrenel = 0.3;
		fAttenuation = 0.3;
		sType = "Storm";

		fBumpScale = 0.05;
		fPosShift = 2.0;
	}
	else
	{
		if (bMainMenu)
		{
			fFoamV = 1.85;
			fPosShift = 3.0;
			fBumpScale = 0.085;
			if (GetTime() >= 5.0 && GetTime() <= 20.0)
			{
				fReflection = 0.7;
				fTransparency = 0.4;
				fAttenuation = 0.5;
				fFoamK= 0.8;
			}
			else
			{
				fReflection = 0.3;
				fTransparency = 0.2;
				fAttenuation = 0.2;
				fFoamK= 0.2;
			}
			sType = "MainMenu";	
		}
        else
        {
            if(iLocation != -1)
            {
                Whr_SetLocationSeaWaves(&fAmp1, &fAmp2, &fScale1, &fScale2, &fFoamK, &fFoamV, &fFoamUV);
                Whr_SetLocationSeaParams(&fReflection, &fTransparency, &fFrenel, &fAttenuation, &fBumpScale, &fPosShift);
                sType = "Location";	
            }
            else
            {
                sType = "Island";		
            }
        }
	}
	
	SeaSettings.Amp1 = fAmp1;						//амплитуда 1 волны
	SeaSettings.AnimSpeed1 = fAnimSpeed1;			//скорость анимации
	SeaSettings.Scale1 = fScale1; 					//размеры волны
	SeaSettings.MoveSpeed1 = sMoveSpeed; 			//скорость движения

	SeaSettings.Amp2 = fAmp2;						//амплитуда 2 волны
	SeaSettings.AnimSpeed2 = fAnimSpeed2;			//скорость анимации
	SeaSettings.Scale2 = fScale2; 					//размеры волны
	SeaSettings.MoveSpeed2 = sMoveSpeed; 			//скорость движения

	SeaSettings.FoamK = fFoamK;						//яркость пены
	SeaSettings.FoamV = fFoamV;						//высота с которой начинается пена
	SeaSettings.FoamUV = fFoamUV; 					//тайлинг пены
	SeaSettings.FoamTexDisturb = fFoamTexDisturb;	//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

	SeaSettings.Reflection = fReflection;			//отражения
	SeaSettings.Transparency = fTransparency;		//прозрачность
	SeaSettings.Frenel = fFrenel;					//степень отражений Френеля от 0 до 1
	SeaSettings.Attenuation = fAttenuation;			//затухание
	SeaSettings.BumpScale = fBumpScale; 			//скейлинг бампа
	SeaSettings.PosShift = fPosShift; 				//остроконечность волн
	SeaSettings.WaterColor = iWaterColor;			//цвет воды
	SeaSettings.SkyColor = iSkyColor;				//цвет неба

	Whr_DebugLog(" - - - - - - - - - - - - - - - - - - - - - - - ");
	Whr_DebugLog("SeaFromWind: " + sType);
	Whr_DebugLog("SeaFromWind: Wind " + fSpeed + "   Amp1 " + fAmp1 + "   AnimSpeed1 " + fAnimSpeed1);
	Whr_DebugLog("SeaFromWind: MoveSpeed " + sMoveSpeed + "   Amp2 " + fAmp2 + "   AnimSpeed2 " + fAnimSpeed2);
	Whr_DebugLog("MaxSeaHeight - " + fMaxSeaHeight + "   Scale1 - " + fScale1 + "   Scale2 - " + fScale2);
	Whr_DebugLog("FoamK - " + fFoamK + "   FoamV - " + fFoamV + "   FoamUV - " + fFoamUV);
	Whr_DebugLog("Reflection - " + fReflection + "   Transparency - " + fTransparency + "   Frenel - " + fFrenel + "   Attenuation - " + fAttenuation);
	Whr_DebugLog("BumpScale - " + fBumpScale + "   PosShift - " + fPosShift + "   WaterColor - " + iWaterColor);	
	Whr_DebugLog(" - - - - - - - - - - - - - - - - - - - - - - - ");
}

void Whr_SetLocationSeaWaves(ref rAmp1, ref rAmp2, ref rScale1, ref rScale2, ref rFoamK, ref rFoamV, ref rFoamUV)
{
	aref weather = GetCurrentWeather();
	string sParams = "Empty";
	bool 	bOk = CheckAttribute(&WeatherParams, "Fog.ThisDay") && sti(WeatherParams.Fog.ThisDay) && CheckAttribute(weather, "SpecialLandFog");
	float fMaxSeaHeight = Whr_SetLocationMaxSeaHeight();
	if(Whr_CheckStorm() || Whr_CheckLandStorm())
	{
		rAmp1 = rAmp1 * 0.33;
		wRange(&rAmp1, 0.1, 3.0);

		rScale1 = rScale1 * 2.0;
		wRange(&rScale1, 1.75, 2.0);

		rAmp2 = rAmp2 * 0.33;
		wRange(&rAmp2, 0.1, 3.0);

		rScale2 = rScale2 * 2.0;
		wRange(&rScale2, 1.75, 2.0);
		if(GetTime() >= 5.0 && GetTime() <= 20.0)
		{
			rFoamK = 0.4;
		}
		else
		{
			rFoamK = 0.2;
		}
		rFoamUV = 0.3;
		rFoamV = abs(makefloat(rAmp2) - fMaxSeaHeight) - 0.25;
		wRange(&rFoamV, 0.35, 0.6);

		sParams = "LandStorm";
	}
	else
	{
		if(Whr_CheckSeaTown() || Whr_CheckSeaFix() || Whr_CheckSeashore() || Whr_CheckGrotto() || Whr_CheckDeck() || Whr_CheckCabine())
		{
			rAmp1 = rAmp1 * 0.33;
			wRange(&rAmp1, 0.1, 3.0);

			rScale1 = rScale1 * 2.0;
			wRange(&rScale1, 1.75, 2.0);

			rAmp2 = rAmp2 * 0.33;
			wRange(&rAmp2, 0.1, 3.0);

			rScale2 = rScale2 * 2.0;
			wRange(&rScale2, 1.75, 2.0);

			if(GetTime() >= 5.0 && GetTime() <= 20.0)
			{
				rFoamK = 2.0;
			}
			else
			{
				rFoamK = 0.5;
			}
			rFoamUV = 0.3;
			rFoamV = abs(makefloat(rAmp2) - fMaxSeaHeight) - 0.25;
			wRange(&rFoamV, 0.45, 0.6);

			sParams = "Town/Seashore/Grotto/Deck/Cabine";
		}
		if(Whr_CheckSeaHeightFix())
		{
			rAmp1 = rAmp1 * 0.33;
			wRange(&rAmp1, 0.1, 3.0);

			rScale1 = rScale1 * 2.0;
			wRange(&rScale1, 1.75, 2.0);

			rAmp2 = rAmp2 * 0.33;
			wRange(&rAmp2, 0.1, 3.0);

			rScale2 = rScale2 * 2.0;
			wRange(&rScale2, 1.75, 2.0);

			if(GetTime() >= 5.0 && GetTime() <= 20.0)
			{
				rFoamK = 2.0;
			}
			else
			{
				rFoamK = 0.5;
			}
			rFoamUV = 0.8;
			rFoamV = abs(makefloat(rAmp2) - fMaxSeaHeight) - 0.125;
			wRange(&rFoamV, 0.25, 0.35);

			sParams = "SeaHeightFix/";
		}
		if(Whr_CheckLSC())
		{
			rAmp1 = rAmp1 * 0.33;
			wRange(&rAmp1, 0.1, 0.5);

			rScale1 = rScale1 * 2.0;
			wRange(&rScale1, 0.25, 8.0);

			rAmp2 = rAmp2 * 0.33;
			wRange(&rAmp2, 0.1, 0.75);

			rScale2 = rScale2 * 2.0;
			wRange(&rScale2, 5.0, 8.0);

			rFoamK = 2.0;

			rFoamV = abs(makefloat(rAmp2) - fMaxSeaHeight) - 0.125;
			wRange(&rFoamV, 0.4, 0.5);

			sParams = "LSC";
		}
	}
	if(Whr_CheckCave())
	{
		sParams = "Cave";
	}
	if(bOk)
	{
		if(GetTime() >= 5.0 && GetTime() <= 20.0)
		{
			rFoamK = 1.5;
		}
		else
		{
			rFoamK = 0.5;
		}
		sParams = "Fog";
	}

	Whr_DebugLog("LocationSeaWaves: " + sParams);
}

void Whr_SetLocationSeaParams(ref rReflection, ref rTransparency, ref rFrenel, ref rAttenuation, ref rBumpScale, ref rPosShift)
{
	aref weather = GetCurrentWeather();
	string sParams = "Empty";
	bool 	bOk = CheckAttribute(&WeatherParams, "Fog.ThisDay") && sti(WeatherParams.Fog.ThisDay) && CheckAttribute(weather, "SpecialLandFog");	
	if(Whr_CheckStorm() || Whr_CheckLandStorm())
	{
		rReflection = 0.625;
		rTransparency = 0.125;
		rFrenel = 0.325;
		rAttenuation = 0.325;
		rBumpScale = 0.25; //МЕЛКИЕ ВОЛНЫ
		rPosShift = 1.45;
		sParams = "LandStorm";
	}
	else
	{
		if(Whr_CheckSeaTown())
		{
			rReflection = 0.725;
			rTransparency = 0.425;
			rFrenel = 0.5325;
			rAttenuation = 0.275;	
			rBumpScale = 0.15; //МЕЛКИЕ ВОЛНЫ
			rPosShift = 1.75;
			sParams = "Town/Fort";
		}
		if(Whr_CheckSeaFix()|| Whr_CheckSeaHeightFix())
		{
			rReflection = 0.725;
			rTransparency = 0.325;
			rFrenel = 0.5325;
			rAttenuation = 0.5275;	
			rBumpScale = 0.15; //МЕЛКИЕ ВОЛНЫ
			rPosShift = 1.75;
			sParams = "SeaFix";
		}
		if(Whr_CheckSeashore() || Whr_CheckGrotto())
		{
			rReflection = 0.725;
			rFrenel = 0.325;
			rAttenuation = 0.475;	
			rBumpScale = 0.15; //МЕЛКИЕ ВОЛНЫ
			rPosShift = 1.75;
			if(GetTime() >= 5.0 && GetTime() <= 20.0)
			{
				rTransparency = 1.025;
			}
			else
			{
				rTransparency = 0.325;
			}
			sParams = "Seashore/Grotto";
		}
		if(Whr_CheckDeck() || Whr_CheckCabine())
		{
			rReflection = 0.725;
			rTransparency = 0.325;
			rFrenel = 0.325;
			rAttenuation = 0.325;
			rBumpScale = 0.15; //МЕЛКИЕ ВОЛНЫ
			rPosShift = 1.75;
			sParams = "Deck/Cabine";
		}
		if(Whr_CheckLSC())
		{
			rReflection = 0.625;
			rTransparency = 0.425;
			rFrenel = 0.6325;
			rAttenuation = 0.325;
			rBumpScale = 0.09; //МЕЛКИЕ ВОЛНЫ
			rPosShift = 1.75;
			sParams = "LSC";
		}
	}
	if(Whr_CheckCave())
	{
		rReflection = 0.525;
		rTransparency = 0.125;
		rFrenel = 0.475; 
		rAttenuation = 0.125;
		rBumpScale = 0.09; //МЕЛКИЕ ВОЛНЫ
		rPosShift = 0.25;
		sParams = "Cave";
	}
	if(bOk)
	{
		rTransparency = 0.2;
		sParams = "Fog";
	}
	Whr_DebugLog("LocationSeaParams: " + sParams);
}

// Усиливаем туман по ветру - чем больше ветер, тем больше волны, чем больше волны - тем больше ляпы вдали, прячем в тумане.
void Whr_ModifySeaFog( float fWind )
{
	float 	additionalNightFog = 0.0000;
	
	float 	fDensity 	= 0.0000; // туман на суше
	float 	iDensity 	= 0.0000; // туман для островов
	float 	sDensity 	= 0.0000; // туман на море
    float   fBlend      = 0.0000; // текущий коэффициент блендинга
    float   blendCoeff  = 0.00035;// максимальный коэффициент блендинга
	
	float 	currentHour = GetTime();
	
	bool 	bOk1 = false;
	
	if(Whr_CheckUnderwater()) return;  // под водой пропускаем
	if(Whr_CheckStorm()) return;  // в шторм пропускаем
	
	if (currentHour >= 0.0 && currentHour <= 7.0)
	{
        if(currentHour >= 6.0)
        {
            fBlend = blendCoeff + (stf(currentHour) - sti(currentHour)) * (-1.0 * blendCoeff);
            additionalNightFog = fBlend;
        }
        else
        {
            if(currentHour <= 1.0)
            {
                fBlend = (stf(currentHour) - sti(currentHour)) * (blendCoeff);
                additionalNightFog = fBlend;
            }
            else additionalNightFog = blendCoeff;
        }
	}
	
	aref weather = GetCurrentWeather();

	iDensity 		= 0.00025 + 0.00003 * pow(fWind/12.0, 3) + additionalNightFog;
	sDensity 		= 0.00065 + 0.00003 * pow(fWind/12.0, 3) + additionalNightFog;
	// fDensity 		= 0.00025 + 0.00003 * pow(fWind/12.0, 3) + additionalNightFog;
	bOk1 	= 	CheckAttribute(&WeatherParams, "Fog.ThisDay") && sti(WeatherParams.Fog.ThisDay) && CheckAttribute(weather, "SpecialLandFog");
	
	// штатный туман в режиме моря и если не установлен утренний туман в локе
	if(bSeaActive || !bOk1 )
	{
		weather.Fog.Height 	= 	200;
		weather.Fog.Start 	= 	10.0;
	
		Whr_DebugLog("Fog - Density: " + fDensity + " IDensity: " + iDensity + " SDensity: " + sDensity + " wind:" + fWind + " Time:" + currentHour + " hour:" + sti(currentHour) + " blend:" + fBlend);

		weather.Fog.IslandDensity	=	iDensity;
		weather.Fog.SeaDensity		=	sDensity;
		// weather.Fog.Density			=	fDensity;// сейчас туман сбрасывается с каждым часом

		Island.FogDensity 			= 	weather.Fog.IslandDensity;
		Sea.Fog.SeaDensity 			= 	weather.Fog.SeaDensity;
		// Sea.Fog.Density 			= 	weather.Fog.Density;
	}	
}

