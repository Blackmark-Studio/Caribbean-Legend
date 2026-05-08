//Sith, mitrokosta меню ожидания в таверне. 
//Добавлены варианты проматывания времени. Выведена информация до какого времени отдыхаем.
int iHourWait = 1;
bool days = false;

void InitInterface(string iniName)
{
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	StartAboveForm(true);
    SetEventHandler("frame","ProcessFrame",0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("exitcancel", "ExitCancel", 0);
	SetEventHandler("eSlideChange", "ProcSlideChange", 0);
	SetEventHandler("RefreshVariables","RefreshVariables",0);

	string sDate = " ";
	sDate = GetDateString();
	string sTime; 
	sTime = GetTimeString();
    SetFormatedText("CURRENT_DATE_CAPTION", sDate + " " + sTime);

	SetVariable();
    SetTimeSlider();
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"HOURS_SLIDE", 2,11);
	SetCurrentNode("HOURS_SLIDE");
}

void ProcessFrame()
{
	string sDate, sTime;
	int hour = sti(worldMap.date.hour);
	int minute = sti(worldMap.date.min);
	bool addDays = true;

	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 1))
	{
		days = false;
		SetSelectable("HOURS_SLIDE", false);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"HOURS_SLIDE", 0,0);
		SetFormatedText("TIME_TEXT", " ");
		SetFormatedText("RESTTIME_TEXT", "");
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));		
		sTime = GetTimeStringEx(0, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
	}       

	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 2))
	{
		days = false;
		SetSelectable("HOURS_SLIDE", false);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"HOURS_SLIDE", 0,0);
		SetFormatedText("TIME_TEXT", " ");
		if (hour < 7) addDays = false;
		SetFormatedText("RESTTIME_TEXT", "");
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));		
		sTime = GetTimeStringEx(7, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
	}

	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3))
	{
		days = false;
		SetSelectable("HOURS_SLIDE", true);
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 4))
	{
		days = true;
		SetSelectable("HOURS_SLIDE", true);
	}
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "HOURS_SLIDE":
			if(comName=="downstep")
			{
				if(GetSelectable("OK_BTN"))
					SetCurrentNode("OK_BTN");
				else
					SetCurrentNode("CANCEL_BTN");
			}
		break;
	
		case "OK_BTN":
			if(comName=="activate" || comName=="click")
				WaitProcess(iHourWait);
				
			if(comName=="rightstep")
				SetCurrentNode("CANCEL_BTN");
			
			if(comName=="upstep")
				SetCurrentNode("HOURS_SLIDE");
		break;
			
		case "CANCEL_BTN":
			if(comName=="leftstep")
			{
				if(GetSelectable("OK_BTN"))
					SetCurrentNode("OK_BTN");
			}
		
			if(comName=="upstep")
				SetCurrentNode("HOURS_SLIDE");
		break;
	}
}

//Sith обновляем вывод инфы, когда кликаем по чекбоксам
void RefreshVariables()
{
	SetTimeSlider();
	string sDate, sTime;
	int hour = sti(worldMap.date.hour);
	int minute = sti(worldMap.date.min);
	int addDays;
	
	if (days == false)
    {
		if (SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3))
        {
			addDays = (hour + iHourWait) / 24;
			hour = (hour + iHourWait) % 24;
			sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));		
			sTime = GetTimeStringEx(hour, minute);
			SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
			SetFormatedText("TIME_TEXT", (iHourWait) + GetCorrectHourString(iHourWait));
		}
        else SetFormatedText("TIME_TEXT", "");
	}
    else
    {
		addDays = iHourWait;
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(hour, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
		SetFormatedText("TIME_TEXT", (iHourWait) + GetCorrectDayString(iHourWait));
	}
}

//Sith крутим вертим часы и дни
void ProcSlideChange()
{
	string sCurDayTime, sDate, sTime;
	string 	sNodeName 	= GetEventData();
	int 	iVal 		= GetEventData(); // int GameInterface.nodes.<node_name>.value
	float 	fVal 		= GetEventData(); // float GameInterface.nodes.<node_name>.value
	sCurDayTime 		= GetDayTime();

	int hour = sti(worldMap.date.hour);
	int minute = sti(worldMap.date.min);
	int addDays;

	SetFormatedText("RESTTIME_TEXT", "");
// Проверяем на галки дней или часов. Учитываем сменяемость суток, дней, месяцев, годов	
	//галка часы
	if(sNodeName == "HOURS_SLIDE" && days == false)
	{
		iHourWait = 1 + iVal;
		addDays = (hour + iHourWait) / 24;
		hour = (hour + iHourWait) % 24;
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(hour, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
		SetFormatedText("TIME_TEXT", (iHourWait) + GetCorrectHourString(iHourWait));
	}
	else
	//галка дней
	{
		iHourWait = 1 + iVal;
		addDays = iHourWait;
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(hour, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
		SetFormatedText("TIME_TEXT", (iHourWait) + GetCorrectDayString(iHourWait));
	}
}

void SetTimeSlider()
{
	bool inTavern = (CheckAttribute(loadedLocation, "fastreload")) && (pchar.location == loadedLocation.fastreload + "_tavern");
	if (days == false)
	{
		GameInterface.nodes.HOURS_SLIDE.value = iHourWait;
		GameInterface.nodes.HOURS_SLIDE.maxlimit = 23;

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"HOURS_SLIDE", 1,23);
	}
	else
	{
		GameInterface.nodes.HOURS_SLIDE.value = iHourWait;
		GameInterface.nodes.HOURS_SLIDE.maxlimit = 6;

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"HOURS_SLIDE", 1,6);
	}
	// if(pchar.location != Get_My_Cabin() && != inTavern ) return; // не сбрасываем слайдер на недоступной промотке дней
	if(!inTavern ) return; // не сбрасываем слайдер на недоступной промотке дней
	else SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"HOURS_SLIDE", 2,0);
}

void SetVariable()
{
	int color1 = argb(255,128,128,128);
	int color2 = argb(255,196,196,196);
	string sCurDayTime;
	sCurDayTime = GetDayTime();
	bool inTavern = (CheckAttribute(loadedLocation, "fastreload")) && (pchar.location == loadedLocation.fastreload + "_tavern");																															 
	// только в каюте и таверне
	// if(pchar.location != Get_My_Cabin() && !inTavern )
	if(!inTavern ) // пока только в таверне
	{
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TIME_CHECK", 5, 4,1);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"DAYS_INFO", 8,0,Color1);
	} 
	else 
	{
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TIME_CHECK", 5, 4,0);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"DAYS_INFO", 8,0,Color2);
	}
}

void WaitProcess(int _iHour)
{
	int iCurrentTime = sti(environment.time);
    int iAddtime = 0;
    int iOldDay = GetDataDay();
    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 1))
    {
        if (iCurrentTime < 24) iAddtime = 24 - iCurrentTime;
    }
	
    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 2))
    {
        if (iCurrentTime >= 21) iAddTime = 24 - iCurrentTime + 7;
		if (iCurrentTime < 7) iAddTime = 7 - iCurrentTime;
		if (iCurrentTime >= 7 && iCurrentTime < 21) iAddTime = 24  + 7 - iCurrentTime;
    }
    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3))
    {
            iAddtime = _iHour;
    }	
    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 4))
    {
            iAddtime = _iHour;
    }
	
	pchar.quest.waithours = iAddtime;
	
    if (days == false)
	{
		DoQuestFunctionDelay("WaitNextHours", 0.1);
	}
	else
	{
		DoQuestFunctionDelay("WaitNextDays", 0.1);
	}
	
	ExitCancel();
}

void IDoExit(int exitCode, bool bClear)
{
	EndAboveForm(true);

	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("ievnt_command", "ProcCommand");
	DelEventHandler("exitcancel", "ExitCancel");
	DelEventHandler("eSlideChange", "ProcSlideChange");
	DelEventHandler("RefreshVariables","RefreshVariables");
	interfaceResultCommand = exitCode;
	EndCancelInterface(bClear);
}

void ExitCancel()
{
	IDoExit(RC_INTERFACE_TAVERN_WAIT, true);
}

void CanWait()
{
	if(iHourWait <= 0 || chrDisableReloadToLocation)
		SetSelectable("OK_BTN", false);
	else
		SetSelectable("OK_BTN", true);
}

string GetCorrectHourString(int _hour)
{
	string sRetStr = " " + XI_ConvertString("rhours");
	if(_hour == 1 || _hour == 21) sRetStr = " " + XI_ConvertString("rhour");
	if(_hour > 1 && _hour < 5) sRetStr = " " + XI_ConvertString("rhours2");
	if(_hour > 21 && _hour < 25) sRetStr = " " + XI_ConvertString("rhours2");	
	return sRetStr;
}

string GetCorrectDayString(int _day)
{
	string sRetStr = " " + XI_ConvertString("rdays");
	if(_day == 1) sRetStr = " " + XI_ConvertString("rday");
	if(_day > 1 && _day < 5) sRetStr = " " + XI_ConvertString("rdays2");
	return sRetStr;
}
