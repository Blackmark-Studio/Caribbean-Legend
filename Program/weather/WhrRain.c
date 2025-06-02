object Rain;

void WhrDeleteRainEnvironment()
{
	if (isEntity(&Rain))
	{
		DeleteClass(&Rain);
	}
	DeleteAttribute(&Rain,"");
}

void WhrCreateRainEnvironment()
{
	bWeatherIsRain = false;

	if (!isEntity(&Rain))
	{
		CreateEntity(&Rain,"rain");
	}

	FillRainData(iCurWeatherNum,iBlendWeatherNum);
	Rain.isDone = "";

	if( sti(Rain.NumDrops) > 0 ) 
	{
		bWeatherIsRain = true;
	}
}

void ClearRainEnvironment()
{
	if (!isEntity(&Rain))
	{
		CreateEntity(&Rain,"rain");
	}

	FillRainData(iCurWeatherNum,iBlendWeatherNum);
	Rain.NumDrops = 0.0;
	Rain.DropLength = 0.1;
	Rain.isDone = "";

	bWeatherIsRain = false;
}

void FillRainData(int nw1, int nw2)
{
	if( nw1 < 0 || nw1 >= MAX_WEATHERS ) {return;}

	aref aRain1; makearef(aRain1, Weathers[nw1].Rain);
	aref aRainbow1; makearef(aRainbow1, Weathers[nw1].Rainbow);

	Rain.Clear = "";
	DeleteAttribute(&Rain,"");

	if( nw2 < 0 )
	{
		Rain.NumDrops = Whr_GetLong(aRain1,"NumDrops");
		Rain.Color = Whr_GetColor(aRain1,"Color");
		Rain.DropLength = Whr_GetFloat(aRain1,"DropLength");
		Rain.Height = Whr_GetFloat(aRain1,"Height");
		Rain.Radius = Whr_GetFloat(aRain1,"Radius");
		Rain.Speed = Whr_GetFloat(aRain1,"Speed");
		Rain.Jitter = Whr_GetFloat(aRain1,"Jitter");
		Rain.WindSpeedJitter = Whr_GetFloat(aRain1,"WindSpeedJitter");
		Rain.TimeBlend = Whr_GetLong(aRain1,"TimeBlend");
		Rain.MaxBlend = Whr_GetLong(aRain1,"MaxBlend");

		Rain.RainDrops.DropsNearNum = Whr_GetLong(aRain1, "DropsNearNum");
		Rain.RainDrops.DropsFarNum = Whr_GetLong(aRain1, "DropsFarNum");
		Rain.RainDrops.DropsNearRadius = Whr_GetFloat(aRain1, "DropsNearRadius");
		Rain.RainDrops.DropsFarRadius = Whr_GetFloat(aRain1, "DropsFarRadius");
		Rain.RainDrops.DropsLifeTime = Whr_GetFloat(aRain1, "DropsLifeTime");
		Rain.RainDrops.DropsSize = Whr_GetFloat(aRain1, "DropsSize");
		Rain.RainDrops.DropsColor = Whr_GetLong(aRain1, "DropsColor");
		Rain.RainDrops.DropsTexture = Whr_GetString(aRain1, "DropsTexture");

		Rain.Rainbow.Enable = Whr_GetLong(aRainbow1,"Enable");
		Rain.Rainbow.Texture = Whr_GetString(aRainbow1,"Texture");
	}
	else
	{
		aref aRain2; makearef(aRain2, Weathers[nw2].Rain);
		aref aRainbow2; makearef(aRainbow2, Weathers[nw2].Rainbow);
		float fBlend = stf(Environment.Time) - sti(Environment.Time);

		Rain.NumDrops = Whr_BlendLong( fBlend, Whr_GetLong(aRain1,"NumDrops"), Whr_GetLong(aRain2,"NumDrops") );
		Rain.Color = Whr_BlendColor( fBlend, Whr_GetColor(aRain1,"Color"), Whr_GetColor(aRain2,"Color") );
		Rain.DropLength = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"DropLength"), Whr_GetFloat(aRain2,"DropLength") );
		Rain.Height = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"Height"), Whr_GetFloat(aRain2,"Height") );
		Rain.Radius = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"Radius"), Whr_GetFloat(aRain2,"Radius") );
		Rain.Speed = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"Speed"), Whr_GetFloat(aRain2,"Speed") );
		Rain.Jitter = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"Jitter"), Whr_GetFloat(aRain2,"Jitter") );
		Rain.WindSpeedJitter = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"WindSpeedJitter"), Whr_GetFloat(aRain2,"WindSpeedJitter") );
		Rain.TimeBlend = Whr_BlendLong( fBlend, Whr_GetLong(aRain1,"TimeBlend"), Whr_GetLong(aRain2,"TimeBlend") );
		Rain.MaxBlend = Whr_BlendLong( fBlend, Whr_GetLong(aRain1,"MaxBlend"), Whr_GetLong(aRain2,"MaxBlend") );
		
		Rain.RainDrops.DropsNearNum = Whr_BlendLong( fBlend, Whr_GetLong(aRain1, "DropsNearNum"), Whr_GetLong(aRain2, "DropsNearNum"));
		Rain.RainDrops.DropsFarNum = Whr_BlendLong( fBlend, Whr_GetLong(aRain1, "DropsFarNum"), Whr_GetLong(aRain2, "DropsFarNum"));
		Rain.RainDrops.DropsNearRadius = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1, "DropsNearRadius"), Whr_GetFloat(aRain2, "DropsNearRadius"));
		Rain.RainDrops.DropsFarRadius = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1, "DropsFarRadius"), Whr_GetFloat(aRain2, "DropsFarRadius"));
		Rain.RainDrops.DropsLifeTime = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1, "DropsLifeTime"), Whr_GetFloat(aRain2, "DropsLifeTime"));
		Rain.RainDrops.DropsSize = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1, "DropsSize"), Whr_GetFloat(aRain2, "DropsSize"));
		Rain.RainDrops.DropsColor = Whr_GetLong(aRain1, "DropsColor"); //Whr_BlendColor( fBlend, Whr_GetColor(aRain1, "DropsColor"), Whr_GetColor(aRain2, "DropsColor"));
		Rain.RainDrops.DropsTexture = Whr_GetString(aRain1, "DropsTexture");

		Rain.Rainbow.Enable = Whr_GetLong(aRainbow1,"Enable") || Whr_GetLong(aRainbow2,"Enable");
		Rain.Rainbow.Texture = Whr_GetString(aRainbow1,"Texture");
	}
    Whr_DebugLog("Rainbow.Enable :" + sti(Rain.Rainbow.Enable));
}

void MoveRainToLayers(int sExecuteLayer, int sRealizeLayer)
{
	LayerDelObject(EXECUTE,&Rain);
	LayerDelObject(REALIZE,&Rain);
	LayerDelObject(SEA_EXECUTE,&Rain);
	LayerDelObject(SEA_REALIZE,&Rain);

	LayerAddObject(sExecuteLayer, &Rain, 65537);
	LayerAddObject(sRealizeLayer, &Rain, 65537);
}

void ShowRain(int bShow)
{
	SendMessage(&Rain,"ll",1,bShow);
}

string Whr_SetStormSkyData(float curTime, ref _fog, ref _sAmbient)
{
	string 	skyDir = "";
	int		iDay, iMorning, iEvening, iNight, iTwilight;

	// для штормов
	iDay 		= hrand(2);
	iMorning 	= hrand(2);
	iEvening 	= hrand(2);
	iTwilight 	= hrand(2);
	iNight 		= 0;
	
	if(curTime >= 23.00 && curTime < 23.99) // night
	{		
		skyDir = "weather\skies_storm\night\01\\"; 					_fog = argb(  0,  2,  2,  2 );
	}
	
	if(curTime >= 0.00 && curTime < 3.00) // night
	{
		skyDir = "weather\skies_storm\night\01\\"; 					_fog = argb(  0,  2,  2,  2 );
	}

	if(curTime >= 3.00 && curTime < 6.00) // twilight
	{
		switch(iTwilight)
		{
			case 0: skyDir = "weather\skies_storm\twilight\01\\"; 	_fog = argb(  0,  4,  5,  8 );	break;
			case 1: skyDir = "weather\skies_storm\twilight\02\\"; 	_fog = argb(  0,  0,  0,  0 );	break;
			case 2: skyDir = "weather\skies_storm\twilight\03\\"; 	_fog = argb(  0,  7,  7,  7 );	break;
		}
	}
	
	if(curTime >= 6.00 && curTime < 11.00) // morning
	{
		switch(iMorning)
		{
			case 0: skyDir = "weather\skies_storm\morning\01\\"; 	_fog = argb(  0, 12, 14, 16 );	break;
			case 1: skyDir = "weather\skies_storm\morning\02\\"; 	_fog = argb(  0, 12, 14, 16 );	break;
			case 2: skyDir = "weather\skies_storm\morning\03\\"; 	_fog = argb(  0, 19, 19, 20 );	break;
		}		
	}
	
	if(curTime >= 11.00 && curTime < 19.00) // day
	{
		switch(iDay)
		{
			case 0: skyDir = "weather\skies_storm\day\01\\"; 		_fog = argb(  0, 33, 34, 34 );	break;
			case 1: skyDir = "weather\skies_storm\day\02\\"; 		_fog = argb(  0, 30, 30, 31 );	break;
			case 2: skyDir = "weather\skies_storm\day\03\\";		_fog = argb(  0, 15, 20, 23 );	break;
		}		
	}

	if(curTime >= 19.00 && curTime < 21.00) // evening
	{
		switch(iEvening)
		{
			case 0: skyDir = "weather\skies_storm\evening\01\\"; 	_fog = argb(  0,  8, 10, 14 );	break;
			case 1: skyDir = "weather\skies_storm\evening\02\\"; 	_fog = argb(  0, 12, 13, 14 );	break;
			case 2: skyDir = "weather\skies_storm\evening\03\\"; 	_fog = argb(  0,  8,  9,  9 );	break;
		}			
	}
	
	if(curTime >= 21.00 && curTime < 23.00) // twilight
	{
		switch(iTwilight)
		{
			case 0: skyDir = "weather\skies_storm\twilight\01\\"; 	_fog = argb(  0,  4,  5,  8 );	break;
			case 1: skyDir = "weather\skies_storm\twilight\02\\"; 	_fog = argb(  0,  0,  0,  0 );	break;
			case 2: skyDir = "weather\skies_storm\twilight\03\\"; 	_fog = argb(  0,  7,  7,  7 );	break;
		}		
	}
	
	if(curTime >=  0.00 && curTime <  4.00)		_sAmbient = argb(  0, 28, 28, 28 );
	if(curTime >=  4.00 && curTime <  5.00)		_sAmbient = argb(  0, 45, 45, 45 );
	if(curTime >=  5.00 && curTime <  6.00)		_sAmbient = argb(  0, 55, 55, 55 );
	if(curTime >=  6.00 && curTime <  7.00)		_sAmbient = argb(  0,105,105,105 );
	if(curTime >=  7.00 && curTime < 19.00)		_sAmbient = argb(  0,128,128,128 );
	if(curTime >= 19.00 && curTime < 20.00)		_sAmbient = argb(  0,105,105,105 );
	if(curTime >= 20.00 && curTime < 21.00)		_sAmbient = argb(  0, 45, 45, 45 );
	if(curTime >= 21.00 && curTime < 23.99)		_sAmbient = argb(  0, 28, 28, 28 );

	return skyDir;	
}

string Whr_SetRainSkyData( float curTime, ref _fog, ref _sAmbient )
{
	string 	skyDir = "";
	int		iDay, iMorning, iEvening, iNight, iTwilight;

	// для дождей
	if(CheckAttribute(&WeatherParams,"Rain.sDay"))		iDay 		= sti(WeatherParams.Rain.sDay);
	else												iDay 		= 0;

	if(CheckAttribute(&WeatherParams,"Rain.sMorning"))	iMorning 	= sti(WeatherParams.Rain.sMorning);
	else												iMorning 	= 0;

	if(CheckAttribute(&WeatherParams,"Rain.sEvening"))	iEvening 	= sti(WeatherParams.Rain.sEvening);
	else												iEvening 	= 0;

	if(CheckAttribute(&WeatherParams,"Rain.sNight"))	iNight 		= sti(WeatherParams.Rain.sNight);
	else												iNight 		= 0;

	if(CheckAttribute(&WeatherParams,"Rain.sTwilight"))	iTwilight 	= sti(WeatherParams.Rain.sTwilight);
	else												iTwilight 	= 0;

	if(curTime >= 23.00 && curTime < 23.99) // night
	{
		switch(iNight)
		{
			case 0: skyDir = "weather\skies_rain\night\01\\"; 		_fog = argb(  0,  2,  5,  9 ); 	break;
			case 1: skyDir = "weather\skies_rain\night\02\\"; 		_fog = argb(  0,  0,  0,  3 );	break;
			case 2: skyDir = "weather\skies_rain\night\03\\"; 		_fog = argb(  0,  2,  5,  9 );	break;
			case 3: skyDir = "weather\skies_rain\night\04\\";		_fog = argb(  0,  2,  4,  7 );	break;
			case 4: skyDir = "weather\skies_rain\night\05\\"; 		_fog = argb(  0,  0,  0,  0 );	break;
			case 5: skyDir = "weather\skies_rain\night\06\\"; 		_fog = argb(  0,  1,  2,  2 );	break;
			case 6: skyDir = "weather\skies_rain\night\07\\"; 		_fog = argb(  0,  5,  5,  5 );	break;
		}
	}
	
	if(curTime >= 0.00 && curTime < 3.00) // night
	{
		switch(iNight)
		{
			case 0: skyDir = "weather\skies_rain\night\01\\"; 		_fog = argb(  0,  2,  5,  9 ); 	break;
			case 1: skyDir = "weather\skies_rain\night\02\\"; 		_fog = argb(  0,  0,  0,  3 );	break;
			case 2: skyDir = "weather\skies_rain\night\03\\"; 		_fog = argb(  0,  2,  5,  9 );	break;
			case 3: skyDir = "weather\skies_rain\night\04\\";		_fog = argb(  0,  2,  4,  7 );	break;
			case 4: skyDir = "weather\skies_rain\night\05\\"; 		_fog = argb(  0,  0,  0,  0 );	break;
			case 5: skyDir = "weather\skies_rain\night\06\\"; 		_fog = argb(  0,  1,  2,  2 );	break;
			case 6: skyDir = "weather\skies_rain\night\07\\"; 		_fog = argb(  0,  5,  5,  5 );	break;
		}
	}

	if(curTime >= 3.00 && curTime < 6.00) // twilight
	{
		switch(iTwilight)
		{
			case 0: skyDir = "weather\skies_rain\twilight\01\\"; 	_fog = argb(  0,  7, 22, 41 );	break;
			case 1: skyDir = "weather\skies_rain\twilight\02\\"; 	_fog = argb(  0,  0,  0, 12 );	break;
			case 2: skyDir = "weather\skies_rain\twilight\03\\"; 	_fog = argb(  0,  5, 17, 39 );	break;
			case 3: skyDir = "weather\skies_rain\twilight\04\\"; 	_fog = argb(  0, 11, 17, 33 );	break;
			case 4: skyDir = "weather\skies_rain\twilight\05\\"; 	_fog = argb(  0,  0,  0,  0 );	break;
			case 5: skyDir = "weather\skies_rain\twilight\06\\"; 	_fog = argb(  0, 11, 15, 16 );	break;
			case 6: skyDir = "weather\skies_rain\twilight\07\\"; 	_fog = argb(  0, 14, 14, 16 );	break;
		}
	}
	
	if(curTime >= 6.00 && curTime < 11.00) // morning
	{
		switch(iMorning)
		{
			case 0: skyDir = "weather\skies_rain\morning\01\\"; 	_fog = argb(  0, 67, 77, 89 );	break;
			case 1: skyDir = "weather\skies_rain\morning\02\\"; 	_fog = argb(  0, 62, 74, 90 );	break;
			case 2: skyDir = "weather\skies_rain\morning\03\\"; 	_fog = argb(  0, 77, 87, 97 );	break;
			case 3: skyDir = "weather\skies_rain\morning\04\\";		_fog = argb(  0, 55, 72, 88 );	break;
			case 4: skyDir = "weather\skies_rain\morning\05\\"; 	_fog = argb(  0, 87,116,132 );	break;
			case 5: skyDir = "weather\skies_rain\morning\06\\"; 	_fog = argb(  0, 93, 96,105 );	break;
		}
	}
	
	if(curTime >= 11.00 && curTime < 19.00) // day
	{
		switch(iDay)
		{
			case 0: skyDir = "weather\skies_rain\day\01\\"; 		_fog = argb(  0,132,134,131 );	break;
			case 1: skyDir = "weather\skies_rain\day\02\\"; 		_fog = argb(  0,157,155,158 );	break;
			case 2: skyDir = "weather\skies_rain\day\03\\";			_fog = argb(  0,143,144,148 );	break;
			case 3: skyDir = "weather\skies_rain\day\04\\"; 		_fog = argb(  0,103,115,131 );	break;
			case 4: skyDir = "weather\skies_rain\day\05\\"; 		_fog = argb(  0, 71, 85, 98 );	break;
			case 5: skyDir = "weather\skies_rain\day\06\\"; 		_fog = argb(  0, 66, 72, 68 );	break;
			case 6: skyDir = "weather\skies_rain\day\07\\"; 		_fog = argb(  0, 82, 94, 92 );	break;
			case 7:	skyDir = "weather\skies_rain\day\08\\"; 		_fog = argb(  0,104,119,138 );	break;
			case 8:	skyDir = "weather\skies_rain\day\09\\"; 		_fog = argb(  0, 77, 81, 92 );	break;
		}
	}

	if(curTime >= 19.00 && curTime < 21.00) // evening
	{
		switch(iEvening)
		{
			case 0: skyDir = "weather\skies_rain\evening\01\\"; 	_fog = argb(  0, 33, 45, 67 );	break;
			case 1: skyDir = "weather\skies_rain\evening\02\\"; 	_fog = argb(  0, 58, 76, 90 );	break;
			case 2: skyDir = "weather\skies_rain\evening\03\\"; 	_fog = argb(  0, 55, 69, 95 );	break;
			case 3: skyDir = "weather\skies_rain\evening\04\\"; 	_fog = argb(  0, 43, 56, 72 );	break;
			case 4: skyDir = "weather\skies_rain\evening\05\\"; 	_fog = argb(  0, 30, 39, 46 );	break;
			case 5: skyDir = "weather\skies_rain\evening\06\\"; 	_fog = argb(  0, 35, 42, 58 );	break;
			case 6: skyDir = "weather\skies_rain\evening\07\\"; 	_fog = argb(  0, 42, 59, 67 );	break;
			case 7: skyDir = "weather\skies_rain\evening\08\\"; 	_fog = argb(  0, 30, 40, 41 );	break;
		}
	}
	
	if(curTime >= 21.00 && curTime < 23.00) // twilight
	{
		switch(iTwilight)
		{
			case 0: skyDir = "weather\skies_rain\twilight\01\\"; 	_fog = argb(  0,  7, 22, 41 );	break;
			case 1: skyDir = "weather\skies_rain\twilight\02\\"; 	_fog = argb(  0,  0,  0, 12 );	break;
			case 2: skyDir = "weather\skies_rain\twilight\03\\"; 	_fog = argb(  0,  5, 17, 39 );	break;
			case 3: skyDir = "weather\skies_rain\twilight\04\\"; 	_fog = argb(  0, 11, 17, 33 );	break;
			case 4: skyDir = "weather\skies_rain\twilight\05\\"; 	_fog = argb(  0,  0,  0,  0 );	break;
			case 5: skyDir = "weather\skies_rain\twilight\06\\"; 	_fog = argb(  0, 11, 15, 16 );	break;
			case 6: skyDir = "weather\skies_rain\twilight\07\\"; 	_fog = argb(  0, 14, 14, 16 );	break;
		}
	}
	
	if(curTime >=  0.00 && curTime <  4.00)		_sAmbient = argb(  0, 28, 28, 28 );
	if(curTime >=  4.00 && curTime <  5.00)		_sAmbient = argb(  0, 45, 45, 45 );
	if(curTime >=  5.00 && curTime <  6.00)		_sAmbient = argb(  0, 55, 55, 55 );
	if(curTime >=  6.00 && curTime <  7.00)		_sAmbient = argb(  0,105,105,105 );
	if(curTime >=  7.00 && curTime < 19.00)		_sAmbient = argb(  0,128,128,128 );
	if(curTime >= 19.00 && curTime < 20.00)		_sAmbient = argb(  0,105,105,105 );
	if(curTime >= 20.00 && curTime < 21.00)		_sAmbient = argb(  0, 45, 45, 45 );
	if(curTime >= 21.00 && curTime < 23.99)		_sAmbient = argb(  0, 28, 28, 28 );

	return skyDir;
}	

//*******************************************************
//ugeen: перенес всю логику дождей сюда из WhrWeather.c 
//*******************************************************

// генератор дождей и утренних туманов в локациях
void Whr_RainFogGenerator()
{
	int iMonth = GetDataMonth();
	
	WeatherParams.Rain 			= false;
	WeatherParams.Rain.ThisDay 	= false;
	
	WeatherParams.Fog 			= false;
	WeatherParams.Fog.ThisDay 	= false;
	
	int chance = 100;
	
	// дожди
	switch(iMonth)
	{
		case 1:  chance = 10; 	break;
		case 2:  chance = 5; 	break;
		case 3:  chance = 5; 	break;
		case 4:  chance = 5; 	break;
		case 5:  chance = 15; 	break; // начало сезона дождей
		case 6:  chance = 20; 	break;
		case 7:  chance = 30; 	break;
		case 8:  chance = 45; 	break;
		case 9:  chance = 90; 	break; // высокий шанс ежедневного дождя
		case 10: chance = 85; 	break; // высокий шанс ежедневного дождя
		case 11: chance = 35; 	break;
		case 12: chance = 15; 	break; // сухой сезон
	}	
	
	if(WEATHER_DEBUG || hrand(100) < chance)
	{
		if(hrand(100) < 30)
		{			
			WeatherParams.Rain.StartTime = 2 + rand(13) + rand(59)/60.0; 	// время старта с минутами
			WeatherParams.Rain.Duration  = 180 + rand(360); 				// затяжной дождь
		}
		else
		{
			WeatherParams.Rain.StartTime = 2 + rand(19) + rand(59)/60.0;	// время старта с минутами
			WeatherParams.Rain.Duration  = 60 + rand(120); 					// короткий дождь
		}		
		WeatherParams.Rain.ThisDay 		= true;								// дождь сегодня будет
		WeatherParams.Rain.sDay			= rand(8);
		WeatherParams.Rain.sMorning		= rand(5);
		WeatherParams.Rain.sEvening		= rand(7);
		WeatherParams.Rain.sNight		= rand(6);
		WeatherParams.Rain.sTwilight 	= sti(WeatherParams.Rain.sNight);
		WeatherParams.Rain.Type			= rand(1);							// тип дождя 
		WeatherParams.Rain.year 		= GetDataYear();
		WeatherParams.Rain.month 		= GetDataMonth();
		WeatherParams.Rain.day 			= GetDataDay();
		WeatherParams.Rain.time 		= stf(WeatherParams.Rain.StartTime);
				
		Log_TestInfo("Дождь начнется в " + WeatherParams.Rain.time + " Выбран дождь : " + (sti(WeatherParams.Rain.Type) + 1));
		Log_TestInfo("Продолжительность дождя: " + WeatherParams.Rain.Duration + " мин.");
		
		if(WEATHER_DEBUG || hrand(100) < 40)    WeatherParams.Rain.IsLightingActive = true;		// гроза будет или нет
		else				                    WeatherParams.Rain.IsLightingActive = false;
	}
	else
	{
		Log_TestInfo("Дождя сегодня не будет");
	}		
	
	// туманы по утрам в локациях, простой рэндом
	// ~!~ TO_DO добавить зависимость от типа скайбокса и дождей в этот день
	if(WEATHER_DEBUG || hrand(100) < 101) // 10% вероятность (TO_DO: WTF)
	{
		WeatherParams.Fog 			= true;
		WeatherParams.Fog.ThisDay 	= true;
		WeatherParams.Fog.Type		= rand(1);	// тип тумана - утренний или вечерний 
		if(sti(WeatherParams.Fog.Type) == 0)	Log_TestInfo("Будет утренний туман в локациях");
		else									Log_TestInfo("Будет вечерний туман в локациях");
	}
	else
	{
		Log_TestInfo("Тумана сегодня не будет");
	}		
}

// ****************************************************************************************
// Mett: настройки дождя
// Ugeen : + куча моих правок (дождь может начаться в любое время часа, правка логики стадий)
// ****************************************************************************************

// настройки дождя
// 0 стадия - дождя нет, заканчиваем дождь, убираем молнии и звук дождя, запускем радугу
// 1 стадия - дождь усиливается
// 2 стадия - дождь льет как из ведра
// 3 стадия - дождь идёт на убыль
// по завершению мы возвращаемся на 0 стадию
void Whr_SetRainExt1(int iCurWeatherNum, int iBlendWeatherNum, bool bRain)
{
	float 	fTime = GetTime();
	float 	fTmp, fDuration;
	int 	iHour = MakeInt(GetHour());
	int 	iTmp;
	
	if(!CheckAttribute(&WeatherParams, "Rain.StartTime")) return;
	
	fDuration	= stf(WeatherParams.Rain.Duration)/60.0;
	fTmp 		= stf(WeatherParams.Rain.StartTime) + fDuration;
	
	if(bRain)
	{
		iTmp = 0;
		if(fTime >= fTmp)														// 0 стадия - заканчиваем дождь
		{
			iTmp 					= 0;
			bRain 					= false;
			WeatherParams.Rain 		= false;
            WhrStopLightning();
            Weathers[iCurWeatherNum].Rainbow.Enable   = false;
			Whr_DebugLog("Заканчиваем дождь. Время : " + fTime + " время остановки дождя : " + fTmp );
		}	

		if(fTime < (stf(WeatherParams.Rain.StartTime) + 4 * (fDuration/5.0)))	iTmp = 3;	// 3 стадия - дождь идёт на убыль
		if(fTime < (stf(WeatherParams.Rain.StartTime) + 2 * (fDuration/3.0)))	iTmp = 2;	// 2 стадия - дождь льет как из ведра
		if(fTime < (stf(WeatherParams.Rain.StartTime) + fDuration/3.0) )		iTmp = 1;	// 1 стадия - дождь усиливается

		Whr_DebugLog("Дождь - время : " + fTime + " время остановки дождя : " + fTmp + " стадия: " + iTmp);	//лог будет идти только во время дождя, чтоб не грузило

		switch(iTmp)
		{
			case 0:			// 0 стадия - дождя нет, заканчиваем дождь, убираем молнии и звук дождя, запускаем радугу
				if(CheckAttribute(&WeatherParams, "Rain.Sound") && sti(WeatherParams.Rain.Sound))
				{
					WeatherParams.Rain 			= false;
					WeatherParams.Rain.Sound 	= false;
                    WhrStopLightning();
					Whr_SetRainSound(false, sti(Weathers[iCurWeatherNum].Night));
                    Weathers[iCurWeatherNum].Rainbow.Enable   = false;
					Weathers[iCurWeatherNum].Rain.NumDrops 	= 0;
					DeleteAttribute(&WeatherParams, "Rain.StartTime");
					Whr_DebugLog("Стадия 0");
				}
				WeatherParams.Rain.ThisDay = false;	
				wRain = 0;
			break;

			case 1:		// 1 стадия - дождь усиливается
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 1500 + rand(2000);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 6 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
				WeatherParams.Rain.Sound = true;
                WhrStopLightning();
				Whr_DebugLog("Стадия 1");
				wRain = 1;
			break;
			
			case 2:		// 2 стадия - дождь льет как из ведра
				if(CheckAttribute(&WeatherParams,"Rain.IsLightingActive") && sti(WeatherParams.Rain.IsLightingActive) == 1)
				{                    
					Whr_DebugLog("Дождь : будут молнии");					
					Weathers[iCurWeatherNum].Rainbow.Enable   			= false;
                    Weathers[iCurWeatherNum].Lightning.Enable 		    = true; 
                    WhrStartLightning();
				}
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 3500 + rand(1500);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 8 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);	
				Whr_DebugLog("Стадия 2");
				wRain = 2;
			break;
			
			case 3:		// 3 стадия - дождь идёт на убыль
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 2500 + rand(1000);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 6 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
                if(fTime > 7.0 && fTime < 20.0) 
				{
					Weathers[iCurWeatherNum].Rainbow.Enable     = true;
                    Weathers[iCurWeatherNum].Rainbow.Texture 	= "weather\rainbow\rainbow.tga";
				}
                if(CheckAttribute(&WeatherParams,"Rain.IsLightingActive") && sti(WeatherParams.Rain.IsLightingActive) == 1)
				{                    
					Whr_DebugLog("Дождь : будут молнии");					
                    Weathers[iCurWeatherNum].Lightning.Enable 		    = true;
                    WhrStartLightning();    
				}
				Whr_DebugLog("Стадия 3");
				wRain = 1;
			break;
		}
		if(iTmp != 0)	// пока идёт дождь держим туман, не врубаем солнце 
		{
			Whr_SetRainBlendWeather(iBlendWeatherNum, false); 
		}
	}
	else	//начало дождя... если генератор не запущен...
	{
		if(CheckAttribute(&WeatherParams, "Rain.ThisDay") && sti(WeatherParams.Rain.ThisDay))
		{
			if(fTime >= stf(WeatherParams.Rain.StartTime) && fTime < fTmp)		// можем начинать
			{
				Whr_SetRainBlendWeather(iBlendWeatherNum, true); 				// Mett: интенсивность - лёгкий дождь
				WeatherParams.Rain = true;										// флаг "дождь"
                WhrStopLightning();
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
                Weathers[iCurWeatherNum].Rainbow.Enable   = false;	
				Whr_DebugLog("Стартуем дождь. Стартовое время : " + stf(WeatherParams.Rain.StartTime) + " продолжительность : " + (stf(WeatherParams.Rain.Duration)/60.0));
			}
		}
	}
}

// второй вариант дождя
void Whr_SetRainExt2(int iCurWeatherNum, int iBlendWeatherNum, bool bRain)
{
	float 	fTime = GetTime();
	float 	fTmp, fDuration;
	int 	iHour = MakeInt(GetHour());
	int 	iTmp;
	
	if(!CheckAttribute(&WeatherParams, "Rain.StartTime")) return;
	
	fDuration	= stf(WeatherParams.Rain.Duration)/60.0;
	fTmp 		= stf(WeatherParams.Rain.StartTime) + fDuration;
	
	if (bRain)
	{
		iTmp = 4;	//по-умолчанию пятая стадия
		if(fTime >= fTmp)														// 5 стадия - заканчиваем дождь
		{
			iTmp 					= 4;
			bRain 					= false;
			WeatherParams.Rain 		= false;
            WhrStopLightning();
            Weathers[iCurWeatherNum].Rainbow.Enable   = false;
			Whr_DebugLog("Заканчиваем дождь. Время : " + fTime + " время остановки дождя : " + fTmp );
		}

		if(fTime < (stf(WeatherParams.Rain.StartTime) + 5 * (fDuration)/7.0)) iTmp = 3;// четвертая стадия, дождь идёт на убыль
		if(fTime < (stf(WeatherParams.Rain.StartTime) + 4 * (fDuration)/7.0)) iTmp = 2;// третья стадия, дождь идёт на убыль
		if(fTime < (stf(WeatherParams.Rain.StartTime) + 3 * (fDuration)/7.0)) iTmp = 1;// вторая стадия, дождь льет как из ведра
		if(fTime < (stf(WeatherParams.Rain.StartTime) + 1 * (fDuration)/5.0)) iTmp = 0;// первая стадия, дождь усиливается
		
		Whr_DebugLog("Дождь - время : " + fTime + " время остановки дождя : " + fTmp + " стадия: " + iTmp);	//лог будет идти только во время дождя, чтоб не грузило
		
		switch(iTmp)	//в зависимости от заданной стадия моделируем дождь, всего 4 стадий (0-3)
		{
			case 0:	//стадия 1: дождь усиливается
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 1500 + rand(2000);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
				Weathers[iCurWeatherNum].Rainbow.Enable   				= false;
                WhrStopLightning();
				Whr_DebugLog("Стадия 1");
				wRain = 1;
			break;
			case 1:	//стадия 2: дождь льет как из ведра
				if(CheckAttribute(&WeatherParams,"Rain.IsLightingActive") && sti(WeatherParams.Rain.IsLightingActive) == 1)
				{
					Whr_DebugLog("Дождь : будут молнии");
                    Weathers[iCurWeatherNum].Rainbow.Enable   			= false;
                    Weathers[iCurWeatherNum].Lightning.Enable 		    = true; 
                    WhrStartLightning();
				}
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 3500 + rand(1500);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
				Whr_DebugLog("Стадия 2");
				wRain = 2;
			break;
			case 2:	//стадия 3: дождь идёт на убыль
                if(CheckAttribute(&WeatherParams,"Rain.IsLightingActive") && sti(WeatherParams.Rain.IsLightingActive) == 1)
				{
					Weathers[iCurWeatherNum].Rainbow.Enable   			= false;
					Whr_DebugLog("Дождь : будут молнии");
                    Weathers[iCurWeatherNum].Lightning.Enable 		    = true; 
                    WhrStartLightning();
				}
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 2500 + rand(1000);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);	
				Whr_DebugLog("Стадия 3");
				wRain = 1;
			break;
			case 3:	//стадия 4: дождь идёт на убыль
                WhrStopLightning();
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 1000 + rand(500);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
                if(fTime > 7.0 && fTime < 20.0) 
				{
					Weathers[iCurWeatherNum].Rainbow.Enable     = true;
                    Weathers[iCurWeatherNum].Rainbow.Texture 	= "weather\rainbow\rainbow.tga";
				}
				Whr_DebugLog("Стадия 4");
				wRain = 1;
			break;
			case 4:	//стадия 5: заканчиваем дождь, убираем молнии и звук дождя
				if(CheckAttribute(&WeatherParams, "Rain.Sound") && sti(WeatherParams.Rain.Sound))
				{
					WeatherParams.Rain = false;
					WeatherParams.Rain.Sound = false;
                    Weathers[iCurWeatherNum].Lightning.Enable 	= false;
                    WhrStopLightning();
					Whr_SetRainSound(false, sti(Weathers[iCurWeatherNum].Night));
					Weathers[iCurWeatherNum].Rainbow.Enable   = false;																	  
					Weathers[iCurWeatherNum].Rain.NumDrops 	= 0;
					DeleteAttribute(&WeatherParams, "Rain.StartTime");
					Whr_DebugLog("Стадия 5");
				}
				WeatherParams.Rain.ThisDay = false;
				wRain = 0;
			break;
		}
		if(iTmp != 4)	//пока идёт дождь держим туман, не врубаем солнце 
		{
			Whr_SetRainBlendWeather(iBlendWeatherNum, false); 	//Mett: без дождя
		}
	}
	else	//начало дождя... если генератор не запущен...
	{	//начинаем...
		if(CheckAttribute(&WeatherParams, "Rain.ThisDay") && sti(WeatherParams.Rain.ThisDay))
		{
			if(fTime >= stf(WeatherParams.Rain.StartTime) && fTime < fTmp)		// можем начинать
			{
				Whr_SetRainBlendWeather(iBlendWeatherNum, true); 				// Mett: интенсивность - лёгкий дождь
				WeatherParams.Rain = true;										// флаг "дождь"
                WhrStopLightning();
				Weathers[iCurWeatherNum].Rainbow.Enable   = false;	
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
				Whr_DebugLog("Стартуем дождь. Стартовое время : " + stf(WeatherParams.Rain.StartTime) + " продолжительность : " + (stf(WeatherParams.Rain.Duration)/60.0));
			}
		}
	}
}

//общие настройки погоды в дождь
void Whr_SetRainBlendWeather(int iBlendWeatherNum, bool bRain)
{
	if(bRain)	//идёт лёгкий дождь?
	{
		Weathers[iBlendWeatherNum].Rain.NumDrops 	= 500 + rand(500);
		Weathers[iBlendWeatherNum].Rain.DropLength 	= 4 + rand(8);
		Weathers[iBlendWeatherNum].Rain.Color 		= argb(0,23,23,23);
	}

    Whr_DebugLog("iCurWeatherNum : " + iCurWeatherNum + " curHour : " + Weathers[iCurWeatherNum].Hour.Min);
	Whr_DebugLog("iBlendWeatherNum : " + iBlendWeatherNum + " blendHour : " + Weathers[iBlendWeatherNum].Hour.Min);

	if(wRain == 1)
	{
		Weathers[iBlendWeatherNum].LightingLm				= "storm";
	}
	if(wRain == 2)
	{
		Weathers[iBlendWeatherNum].LightingLm				= "storm";
		Weathers[iBlendWeatherNum].InsideBack 				= "n";
	}	
} 
