#event_handler("frame", "UpdateSky");

object Sky;

float fPrevCameraAX = 0;

void WhrDeleteSkyEnvironment()
{
	if(isEntity(&Sky))
	{
		DeleteClass(&Sky);
	}	
	DeleteAttribute(&Sky, "");
}

void WhrCreateSkyEnvironment()
{
	aref aCurWeather = GetCurrentWeather();
	aref aSky;
	makearef(aSky, aCurWeather.Sky);

	DeleteAttribute(&Sky, "")
	if(!isEntity(&Sky))
	{
		CreateEntity(&Sky, "Sky");
		LayerAddObject(SEA_REFLECTION,&Sky,1);
	}
	FillSkyDir(&Sky);

	Sky.Color 		= Whr_GetColor(aSky, "Color");
	Sky.RotateSpeed = Whr_GetFloat(aSky, "Rotate"); // Warship 02.06.09 - ротация неба ниже
	Sky.Angle 		= Whr_GetFloat(aSky, "Angle");
	Sky.Size 		= Whr_GetFloat(aSky, "Size");
	
	Sky.isDone = "";
}

// Warship 02.06.09 - апдейт параметров неба (например, скорость ротации в зависимости от силы ветра)
void UpdateSky()
{
	float windSpeed = 5.0;
	float timeScale = 1.0 + TimeScaleCounter * 0.25; // Текущее ускорение времени

	// Вычисление делителя для ускорения, чтоб на x8 бешенно не крутились
	if(timeScale <= 2)
	{
		timeScale = 1.0;
	}
	else
	{
		timeScale /= 2.0;
	}
	
	if(CheckAttribute(Weather, "Wind.Speed"))
	{
		windSpeed = stf(Weather.Wind.Speed);
	}
	
	if(CheckAttribute(&InterfaceStates,"ROTATESKY") && sti(InterfaceStates.ROTATESKY) == 1) // belamour ( ROTATE_SKY == 1)
	{	
		if( GetTime() >= 5.0 && GetTime() < 8.0 ) 
		{
			Sky.RotateSpeed = 0.0;
		}	
		else 
		{
			if( GetTime() >= 18.0 && GetTime() < 21.0 ) 
			{
				Sky.RotateSpeed = 0.0;
			}
		}
		else 
		{
			Sky.RotateSpeed = windSpeed / 16000 / timeScale;
		}
	}
	else
	{
		Sky.RotateSpeed = 0.0;
	}	
}

void FillSkyDir(aref aSky)
{
	int 		i;
	float		nStart, nDur;
	string 		satr;
	aref 		aCurWeather = GetCurrentWeather();
	string 		sDir;
	string		sSubDir;
	int			fog 	= 0;
	int			sunAmb 	= 0;
	int			sky		= 1;

	DeleteAttribute(aSky,"Dir");
	
	if(CheckAttribute(WeatherParams,"weather_sky"))		
	{	
		sSubDir = "weather\skies" + sti(WeatherParams.weather_sky) + "\";	
		sky		= sti(WeatherParams.weather_sky);
	}	
	else
	{	
		sSubDir = "weather\skies1\";
		sky		= 1;
	}	
	Whr_DebugLog("SkySubDir : " + sSubDir + " sky :" + sky);	
	
	if( iBlendWeatherNum < 0 )
	{
		if(CheckAttribute(aCurWeather,"Sky.SubDir")) 	aSky.Dir.d1 = sSubDir + aCurWeather.Sky.SubDir + "\\";
		else											aSky.Dir.d1 = aCurWeather.Sky.Dir;
			
		Whr_DebugLog("aSky.Dir.d1 " + aSky.Dir.d1);
		aSky.Dir = GetHour();
	} 
	else 
	{		
		for (i = 0;i < MAX_WEATHERS; i++)
		{
			if (!CheckAttribute(&Weathers[i], "Hour")) {continue;}
			if ( CheckAttribute(&Weathers[i], "Skip") 	&& 	sti(Weathers[i].Skip)  == true	) {continue;}
			
			satr = "d" + sti(Weathers[i].Hour.Min);
			
			if(Whr_CheckStorm())		// если идёт шторм
			{
				if(sti(Weathers[i].Storm))
				{
					sDir = Whr_SetStormSkyData(stf(Weathers[i].Hour.Min), &fog, &sunAmb);
					Weathers[i].Fog.Color 				= fog;
					Weathers[i].Sun.Ambient 			= sunAmb;
				}
				else continue;	
			}
			else	                    // если шторма нет, т.е. штатная погода
			{
				if(!sti(Weathers[i].Storm))
				{
					sDir = sSubDir + Weathers[i].Sky.SubDir + "\\";	
					Whr_SetSkyFogData( sky, sti(Weathers[i].Hour.Min), &fog);	
					Weathers[i].Fog.Color = fog;
								
					if (CheckAttribute(&WeatherParams, "Rain.ThisDay") && sti(WeatherParams.Rain.ThisDay))
					{
						nStart 	= stf(WeatherParams.Rain.StartTime);
						nDur 	= stf(WeatherParams.Rain.Duration)/60.0;
						
						if (sti(Weathers[i].Hour.Min) >= makeint(nStart - 1.0) && sti(Weathers[i].Hour.Max) <= makeint(nStart + nDur + 1.0))
						{	
							sDir = Whr_SetRainSkyData( Weathers[i].Hour.Min, &fog, &sunAmb );
							Weathers[i].Fog.Color 				= fog;
							Weathers[i].Sun.Ambient 			= sunAmb;
							Whr_DebugLog("RainDir : " + sDir + " hour :" + sti(Weathers[i].Hour.Min) );	
						}
					}					
				}
				else continue;	
			}					
			aSky.Dir.(satr) = sDir;
		}
		aSky.Dir = GetTime();
	}
}

void Whr_SetSkyFogData( int _sky, int curTime, ref _fog)
{
	switch(_sky)
	{
		case 1 :
			switch(curTime)
			{
				case  0: _fog = argb(  0,  6, 13, 23);break;
				case  1: _fog = argb(  0,  5, 12, 19);break;
				case  2: _fog = argb(  0,  5, 12, 19);break;
				case  3: _fog = argb(  0,  3,  8, 15);break;
				case  4: _fog = argb(  0,  5, 13, 26);break;
				case  5: _fog = argb(  0, 29, 46, 54);break;
				case  6: _fog = argb(  0, 99, 74, 70);break;
				case  7: _fog = argb(  0,152,164,155);break;
				case  8: _fog = argb(  0,181,209,221);break;
				case  9: _fog = argb(  0,193,218,228);break;
				case 10: _fog = argb(  0,193,218,228);break;
				case 11: _fog = argb(  0,193,218,228);break;
				case 12: _fog = argb(  0,193,218,228);break;
				case 13: _fog = argb(  0,193,218,228);break;
				case 14: _fog = argb(  0,193,218,228);break;
				case 15: _fog = argb(  0,193,218,228);break;
				case 16: _fog = argb(  0,193,218,228);break;
				case 17: _fog = argb(  0,174,204,215);break;
				case 18: _fog = argb(  0,156,163,164);break;
				case 19: _fog = argb(  0, 98, 82, 76);break;
				case 20: _fog = argb(  0, 60, 54, 54);break;
				case 21: _fog = argb(  0,  7, 15, 23);break;
				case 22: _fog = argb(  0,  5, 12, 20);break;
				case 23: _fog = argb(  0,  6, 13, 21);break;
			}
		break;
		
		case 2 :
			switch(curTime)
			{
				case  0: _fog = argb(  0,  6, 14, 21);break;
				case  1: _fog = argb(  0,  6, 14, 21);break;
				case  2: _fog = argb(  0,  6, 14, 21);break;
				case  3: _fog = argb(  0,  5, 10, 17);break;
				case  4: _fog = argb(  0,  4,  9, 15);break;
				case  5: _fog = argb(  0, 29, 46, 54);break;
				case  6: _fog = argb(  0, 83, 90, 95);break;
				case  7: _fog = argb(  0,130,159,190);break;
				case  8: _fog = argb(  0,150,174,196);break;
				case  9: _fog = argb(  0,144,171,196);break;
				case 10: _fog = argb(  0,144,171,196);break;
				case 11: _fog = argb(  0,144,171,196);break;
				case 12: _fog = argb(  0,144,171,196);break;
				case 13: _fog = argb(  0,144,171,196);break;
				case 14: _fog = argb(  0,144,171,196);break;
				case 15: _fog = argb(  0,144,171,196);break;
				case 16: _fog = argb(  0,144,171,196);break;
				case 17: _fog = argb(  0,144,171,196);break;
				case 18: _fog = argb(  0,156,163,164);break;
				case 19: _fog = argb(  0,135,123,109);break;
				case 20: _fog = argb(  0, 38, 38, 37);break;
				case 21: _fog = argb(  0, 12, 18, 23);break;
				case 22: _fog = argb(  0,  9, 15, 21);break;
				case 23: _fog = argb(  0,  9, 15, 21);break;
			}		
		break;
		
		case 3 :
			switch(curTime)
			{
				case  0: _fog = argb(  0,  6, 14, 21);break;
				case  1: _fog = argb(  0,  6, 14, 21);break;
				case  2: _fog = argb(  0,  6, 14, 21);break;
				case  3: _fog = argb(  0,  5, 10, 17);break;
				case  4: _fog = argb(  0,  4,  9, 15);break;
				case  5: _fog = argb(  0, 29, 46, 54);break;
				case  6: _fog = argb(  0, 29, 46, 54);break;
				case  7: _fog = argb(  0,115,140,156);break;
				case  8: _fog = argb(  0,150,174,196);break;
				case  9: _fog = argb(  0,144,171,196);break;
				case 10: _fog = argb(  0,144,171,196);break;
				case 11: _fog = argb(  0,144,171,196);break;
				case 12: _fog = argb(  0,144,171,196);break;
				case 13: _fog = argb(  0,144,171,196);break;
				case 14: _fog = argb(  0,144,171,196);break;
				case 15: _fog = argb(  0,144,171,196);break;
				case 16: _fog = argb(  0,144,171,196);break;
				case 17: _fog = argb(  0,144,171,196);break;
				case 18: _fog = argb(  0,156,163,164);break;
				case 19: _fog = argb(  0, 41, 47, 69);break;
				case 20: _fog = argb(  0, 20, 26, 35);break;
				case 21: _fog = argb(  0, 12, 18, 23);break;
				case 22: _fog = argb(  0,  9, 15, 21);break;
				case 23: _fog = argb(  0,  9, 15, 21);break;
			}		
		break;		
	}
}

void MoveSkyToLayers(int sExecuteLayer, int sRealizeLayer)
{
	LayerDelObject(EXECUTE,&Sky);
	LayerDelObject(REALIZE,&Sky);
	LayerDelObject(SEA_EXECUTE,&Sky);
	LayerDelObject(SEA_REALIZE,&Sky);

    LayerAddObject(sExecuteLayer,&Sky,2);
    LayerAddObject(sRealizeLayer,&Sky,3);
}