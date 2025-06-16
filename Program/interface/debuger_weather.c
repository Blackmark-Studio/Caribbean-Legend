//Mett: дебагер для погоды
//пока только море 03.12.2017
//направление ветра и штормовое море 07.12.2017
//доработка направления ветра 27.12.2017

float windMin = 0.1;
float windMax = 20.0;

float foamMin = 75.0;
float foamMax = 125.0;

int iHourWait = 0;

string sWindSpeed, sWindAngle, sFoamHeight;

void InitInterface(string iniName)
{
	pchar.debuger_weather = true; //зашли в дебагер
	pchar.debuger_weather.maxSeaHeight = MAX_SEA_HEIGHT;
	pchar.debuger_weather.windSpeed = windMin;
	pchar.debuger_weather.windAngle = 0.0;
	pchar.debuger_weather.windAngle.x = cos(0.0);	//направление x
	pchar.debuger_weather.windAngle.z = sin(0.0);	//направление z
	pchar.debuger_weather.storm = false;
	pchar.debuger_weather.globalSeaHeight = false;
	pchar.debuger_weather.hideInterface = false;
	pchar.debuger_weather.FoamEnable = sti(Sea.Sea2.FoamEnable);

	float fF, fX, fZ, fAY;
	fF = stf(pchar.debuger_weather.windSpeed);		//сила ветра
	fX = stf(pchar.debuger_weather.windAngle.x);	//направление x
	fZ = stf(pchar.debuger_weather.windAngle.z);	//направление z
	fAY = stf(pchar.debuger_weather.windAngle);

	EngineLayersOffOn(true);
	SetTimeScale(1.0);
	TimeScaleCounter = 0;
	DelPerkFromActiveList("TimeSpeed");
	DeleteAttribute(pchar, "pause");

	IReadVariableBeforeInit();
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	IReadVariableAfterInit();

	SetEventHandler("InterfaceBreak", "ProcessCancelExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("ievnt_command", "ProcessCommandExecute", 0);
	SetEventHandler("eSlideChange", "procSlideChange", 0);
	SetEventHandler("CheckButtonChange", "procCheckBoxChange", 0);

	GameInterface.oldWeatherSpeed = fWeatherSpeed;
	GameInterface.oldWeatherAngle = fWeatherAngle;
	fWeatherSpeed = fF;
	fWeatherAngle = GetAngleY(fX, fZ);
	GameInterface.oldMaxSeaHeight = stf(Sea.MaxSeaHeight);
	GameInterface.oldGlobalFoamV = fGlobalFoamV;
	WhrCreateSeaEnvironment();
	
	GameInterface.nodes.HOURS_SLIDE.value = 0.5;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 0, 0.5);

	sWindSpeed = "Wind speed";
	sWindAngle = "Wind angle";
	sFoamHeight = "Foam height";
	
	SetFormatedText("WIND_SPEED_STR", sWindSpeed + " (" + FloatToString(fWeatherSpeed, 1) + ")");	//Скорость ветра
	SetFormatedText("WIND_ANGLE_STR", sWindAngle + " (" + FloatToString(Radian2Degree(GetWindAngle(fAY)), 1) + ")");	//Направление ветра
	SetFormatedText("FOAM_STR", sFoamHeight + " (" + FloatToString(fGlobalFoamV, 1) + ")");	//Высота пены

	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetActorType(pchar);
	}
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_DEBUGER_WEATHER_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak", "ProcessCancelExit");
    DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("ievnt_command", "ProcessCommandExecute");
	DelEventHandler("eSlideChange", "procSlideChange");
	DelEventHandler("CheckButtonChange", "procCheckBoxChange");

    interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	if(pchar.debuger_weather.storm == true) //если не отключили штормовую погоду, иначе вылет!
	{
		pchar.debuger_weather.storm = false;
		bWeatherIsStorm = false;
		CreateWeatherEnvironment();	//это важно!!! без этой строки вылет
	}
	if(pchar.debuger_weather.hideInterface == true)
	{
		pchar.debuger_weather.hideInterface = false;
		ChangeShowIntarface();
	}
	DeleteAttribute(pchar, "debuger_weather"); //вышли из дебагера
	CreateWeatherEnvironment();
	fWeatherSpeed = stf(GameInterface.oldWeatherSpeed);
	fWeatherAngle = stf(GameInterface.oldWeatherAngle);
	Sea.MaxSeaHeight = stf(GameInterface.oldMaxSeaHeight);
	fGlobalFoamV = stf(GameInterface.oldGlobalFoamV);
	WhrCreateSeaEnvironment();
	DeleteAttribute(&GameInterface, "oldWeatherSpeed");
	DeleteAttribute(&GameInterface, "oldWeatherAngle");
	DeleteAttribute(&GameInterface, "oldMaxSeaHeight");
	DeleteAttribute(&GameInterface, "oldGlobalFoamV");

	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetPlayerType(pchar);
	}
}

void IReadVariableBeforeInit()
{
	GetWindSpeedOptionsData();
	GetWindAngleOptionsData();
	GetFoamOptionsData();
}

void IReadVariableAfterInit()
{
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "HIDEINTERFACE_CHECKBOX", 2, 1, false);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "GLOBALSEAHEIGHT_CHECKBOX", 2, 1, false);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "STORM_CHECKBOX", 2, 1, false);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "FOAMENABLE_CHECKBOX", 2, 1, sti(pchar.debuger_weather.FoamEnable));
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	ref chr = GetMainCharacter();

	switch(nodName)
	{
    	case "test":
		break;
		
		case "OK_BTN":
			if(comName=="activate" || comName=="click")
				WaitProcess(iHourWait);		
		break;
	}
}

void procSlideChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();

	if(sNodeName == "WIND_SPEED_SLIDE")
	{
		ChangeWindSpeed();
	}
	if(sNodeName == "WIND_ANGLE_SLIDE")
	{
		ChangeWindAngle();
	}
	if(sNodeName == "FOAM_SLIDE")
	{
		ChangeFoam();
	}
	if(sNodeName == "HOURS_SLIDE")
	{
		iHourWait = sti(fVal*24);
		CanWait();
		SetFormatedText("INFO_TEXT", GetCorrectHourString(iHourWait));
	}
}

void WaitProcess(int _iHour)
{
	ProcessCancelExit();
	
	if( bSeaActive && !bAbordageStarted )
    {
    	Sea_ReloadStart();
	}
	else
	{
	    DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
	}
	
	pchar.quest.waithours = _iHour;
	WaitDate("", 0, 0, 0, sti(pchar.quest.waithours), 0);
	DeleteAttribute(pchar,"quest.waithours");
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void CanWait()
{
	if(iHourWait <= 0)
		SetSelectable("OK_BTN", false);
	else
		SetSelectable("OK_BTN", true);
}

string GetCorrectHourString(int _hour)
{
	string sRetStr = "";
	
	switch(_hour)
	{
		case "0": 	sRetStr = "0.5 hour"; 	break;
		case "1": 	sRetStr = "1 hour"; 	break;
		case "2": 	sRetStr = "2 hour"; 	break;
		case "3": 	sRetStr = "3 hour"; 	break;
		case "4": 	sRetStr = "4 hour"; 	break;
		case "5": 	sRetStr = "5 hour"; 	break;
		case "6": 	sRetStr = "6 hour"; 	break;
		case "7": 	sRetStr = "7 hour"; 	break;
		case "8": 	sRetStr = "8 hour"; 	break;
		case "9": 	sRetStr = "9 hour"; 	break;
		case "10": 	sRetStr = "10 hour"; 	break;
		case "11": 	sRetStr = "11 hour"; 	break;
		case "12": 	sRetStr = "12 hour"; 	break;
		case "13": 	sRetStr = "13 hour"; 	break;
		case "14": 	sRetStr = "14 hour"; 	break;
		case "15": 	sRetStr = "15 hour"; 	break;
		case "16": 	sRetStr = "16 hour"; 	break;
		case "17": 	sRetStr = "17 hour"; 	break;
		case "18": 	sRetStr = "18 hour"; 	break;
		case "19": 	sRetStr = "19 hour"; 	break;
		case "20": 	sRetStr = "20 hour"; 	break;
		case "21": 	sRetStr = "21 hour"; 	break;
		case "22": 	sRetStr = "22 hour"; 	break;
		case "23": 	sRetStr = "23 hour"; 	break;
		case "24": 	sRetStr = "1 day"; 		break;
	}

	return sRetStr;
}

void ChangeWindSpeed()
{
	float fCurWind = stf(GameInterface.nodes.WIND_SPEED_SLIDE.value);

	if(!CheckAttribute(&InterfaceStates, "WindSpeed") || stf(InterfaceStates.WindSpeed) != fCurWind)
	{
		InterfaceStates.WindSpeed = fCurWind;

		fWeatherSpeed = GetWindSpeed(fCurWind);
		UpdateSea();
		SetFormatedText("WIND_SPEED_STR", sWindSpeed + " (" + FloatToString(fWeatherSpeed, 1) + ")");	//Скорость ветра
		pchar.debuger_weather.windSpeed = fWeatherSpeed;	//для корректной волны при смене часов в дебагере
	}
}

void GetWindSpeedOptionsData()
{
	float fCurWind = 0.0;
	fCurWind = Clampf(fCurWind);
	GameInterface.nodes.WIND_SPEED_SLIDE.value = fCurWind;
}

float GetWindSpeed(float wind)
{
	wind = makefloat(windMin + (wind * windMax));
	if(wind > windMax) wind = windMax;
	if(wind < windMin) wind = windMin;
	return wind;
}

void ChangeWindAngle()
{
	float fX, fZ;
	float fCurWind = stf(GameInterface.nodes.WIND_ANGLE_SLIDE.value);

	if(!CheckAttribute(&InterfaceStates, "WindAngle") || stf(InterfaceStates.WindAngle) != fCurWind)
	{
		InterfaceStates.WindAngle = fCurWind;

		pchar.debuger_weather.windAngle.x = cos(GetWindAngle(fCurWind));	//направление x
		pchar.debuger_weather.windAngle.z = sin(GetWindAngle(fCurWind));	//направление z
		fX = stf(pchar.debuger_weather.windAngle.x);
		fZ = stf(pchar.debuger_weather.windAngle.z);
		fWeatherAngle = GetAngleY(fX, fZ);
		UpdateSea();
		SetFormatedText("WIND_ANGLE_STR", sWindAngle + " (" + FloatToString(Radian2Degree(GetWindAngle(fCurWind)), 1) + ")");	//Направление ветра
		pchar.debuger_weather.windAngle = fWeatherAngle;
	}
}

void GetWindAngleOptionsData()
{
	float fCurWind = 0.0;
	fCurWind = Clampf(fCurWind);
	GameInterface.nodes.WIND_ANGLE_SLIDE.value = fCurWind;
}

float GetWindAngle(float wind)
{
	wind = makefloat(0.0 + (wind * 360.0));
	if(wind > 360.0) wind = 360.0;
	if(wind < 0.0) wind = 0.0;
	return Degree2Radian(wind);
}

void GetFoamOptionsData()
{
	float fFoam = 1.0 - ((foamMax - foamMin) / foamMin);
	fFoam = Clampf(fFoam);
	GameInterface.nodes.FOAM_SLIDE.value = fFoam;
}

float GetFoam(float foam)
{
	foam = makefloat(foamMin + (foam * foamMax * 0.4));	//хз почему 0.4, мне лень ломать голову над формулами
	if(foam > foamMax) foam = foamMax;
	if(foam < foamMin) foam = foamMin;
	return foam;
}

void ChangeFoam()
{
	float fFoam = stf(GameInterface.nodes.FOAM_SLIDE.value);

	if(!CheckAttribute(&InterfaceStates, "Foam") || stf(InterfaceStates.Foam) != fFoam)
	{
		InterfaceStates.Foam = fFoam;

		fGlobalFoamV = GetFoam(stf(InterfaceStates.Foam));
		UpdateSea();
		SetFormatedText("FOAM_STR", sFoamHeight + " (" + FloatToString(fGlobalFoamV, 1) + ")");	//Высота пены
	}
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if(sNodName == "STORM_CHECKBOX") 
	{
		InterfaceStates.Storm = bBtnState;
		ChangeStormSea();
	}
	if(sNodName == "GLOBALSEAHEIGHT_CHECKBOX") 
	{
		InterfaceStates.GlobalSeaHeight = bBtnState;
		ChangeGlobalSeaHeight();
	}
	if(sNodName == "HIDEINTERFACE_CHECKBOX") 
	{
		InterfaceStates.HideInterface = bBtnState;
		ChangeHideInterface();
	}
	if(sNodName == "FOAMENABLE_CHECKBOX") 
	{
		InterfaceStates.FoamEnable = bBtnState;
		ChangeFoamEnable();
	}
}

void ChangeStormSea()
{
	float fX, fZ;
	fX = stf(pchar.debuger_weather.windAngle.x);
	fZ = stf(pchar.debuger_weather.windAngle.z);

	if(pchar.debuger_weather.storm == false)
	{
		pchar.debuger_weather.storm = true;
		bWeatherIsStorm = true;
		SelectStormByHour();
		CreateWeatherEnvironment();
		fWeatherSpeed = GetWindSpeed(stf(GameInterface.nodes.WIND_SPEED_SLIDE.value));
		fWeatherAngle = GetAngleY(fX, fZ);
		bWeatherIsStorm = false;
		UpdateSea();
	}
	else
	{
		pchar.debuger_weather.storm = false;
		CreateWeatherEnvironment();
		fWeatherSpeed = GetWindSpeed(stf(GameInterface.nodes.WIND_SPEED_SLIDE.value));
		fWeatherAngle = GetAngleY(fX, fZ);
		UpdateSea();
	}
}

void SelectStormByHour()
{
	if(GetTime() >=  0.00 && GetTime() <  1.00)		SetNextWeather("Storm00");
	if(GetTime() >=  1.00 && GetTime() <  2.00)		SetNextWeather("Storm01");
	if(GetTime() >=  2.00 && GetTime() <  3.00)		SetNextWeather("Storm02");
	if(GetTime() >=  3.00 && GetTime() <  4.00)		SetNextWeather("Storm03");
	if(GetTime() >=  4.00 && GetTime() <  5.00)		SetNextWeather("Storm04");	
	if(GetTime() >=  5.00 && GetTime() <  6.00)		SetNextWeather("Storm05");
	if(GetTime() >=  6.00 && GetTime() <  7.00)		SetNextWeather("Storm06");
	if(GetTime() >=  7.00 && GetTime() <  8.00)		SetNextWeather("Storm07");
	if(GetTime() >=  8.00 && GetTime() <  9.00)		SetNextWeather("Storm08");
	if(GetTime() >=  9.00 && GetTime() < 10.00)		SetNextWeather("Storm09");
	if(GetTime() >= 10.00 && GetTime() < 11.00)		SetNextWeather("Storm10");	
	if(GetTime() >= 11.00 && GetTime() < 12.00)		SetNextWeather("Storm11");
	if(GetTime() >= 12.00 && GetTime() < 13.00)		SetNextWeather("Storm12");
	if(GetTime() >= 13.00 && GetTime() < 14.00)		SetNextWeather("Storm13");
	if(GetTime() >= 14.00 && GetTime() < 15.00)		SetNextWeather("Storm14");
	if(GetTime() >= 15.00 && GetTime() < 16.00)		SetNextWeather("Storm15");
	if(GetTime() >= 16.00 && GetTime() < 17.00)		SetNextWeather("Storm16");	
	if(GetTime() >= 17.00 && GetTime() < 18.00)		SetNextWeather("Storm17");
	if(GetTime() >= 18.00 && GetTime() < 19.00)		SetNextWeather("Storm18");
	if(GetTime() >= 19.00 && GetTime() < 20.00)		SetNextWeather("Storm19");
	if(GetTime() >= 20.00 && GetTime() < 21.00)		SetNextWeather("Storm20");
	if(GetTime() >= 21.00 && GetTime() < 22.00)		SetNextWeather("Storm21");
	if(GetTime() >= 22.00 && GetTime() < 23.00)		SetNextWeather("Storm22");
	if(GetTime() >= 23.00 && GetTime() < 23.99)		SetNextWeather("Storm23");	
}

void ChangeGlobalSeaHeight()
{
	if(pchar.debuger_weather.globalSeaHeight == false)
	{
		pchar.debuger_weather.globalSeaHeight = true;
		pchar.debuger_weather.maxSeaHeight = stf(GameInterface.oldMaxSeaHeight);
		UpdateSea();
	}
	else
	{
		pchar.debuger_weather.globalSeaHeight = false;
		pchar.debuger_weather.maxSeaHeight = MAX_SEA_HEIGHT;
		UpdateSea();
	}
	Log_Info("Debug: MaxSeaHeight " + FloatToString(stf(pchar.debuger_weather.maxSeaHeight), 1));
}

void ChangeHideInterface()
{
	if(pchar.debuger_weather.hideInterface == false)
	{
		pchar.debuger_weather.hideInterface = true;
		ChangeShowIntarface();
	}
	else
	{
		pchar.debuger_weather.hideInterface = false;
		ChangeShowIntarface();
	}
	Log_Info("Debug: HideInterface == " + sti(pchar.debuger_weather.hideInterface));
}

void ChangeFoamEnable()
{
	if(pchar.debuger_weather.FoamEnable == false)
	{
		pchar.debuger_weather.FoamEnable = true;
		UpdateSea();
	}
	else
	{
		pchar.debuger_weather.FoamEnable = false;
		UpdateSea();		
	}
	Log_Info("Debug: FoamEnable == " + sti(Sea.Sea2.FoamEnable));
}

void UpdateSea()
{
	WhrCreateSeaEnvironment();
}