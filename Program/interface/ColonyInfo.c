//  интерфейс смены владельца города
string totalInfo;
string sCity;
int    iNation, iDay;

void InitInterface(string iniName)
{
    StartAboveForm(true);
    // лочим квест и карту
    bQuestCheckProcessFreeze = true;
    
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    if (CheckAttribute(Pchar, "GenQuestFort.ColonySiegeId"))
    {
        // режим осады
        sCity    = pchar.GenQuestFort.ColonySiegeId;
		iNation  = int(pchar.GenQuestFort.ColonySiegeNation);
		DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeId");
		DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeNation");
		
		if (CheckAttribute(Pchar, "GenQuestFort.ColonySiegeEnd"))
		{// конец осады
            DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeEnd");
			CalculateEndSiegeCity();
		}
		else
		{
            iDay     = int(pchar.GenQuestFort.ColonySiegeTime);
            DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeTime");
			CalculateSiegeCity();
		}
    }
    else
    {
		// режим захвата города, не используется
		sCity    = pchar.GenQuest.CapturedCity;
		iNation  = int(pchar.GenQuest.CaptureNation);
		CalculateCapturedCity();
	}
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
    
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
    PostEvent("StopQuestCheckProcessFreeze", 100);//заморозка проверки квестов
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
    	case "B_OK":
    		if(comName=="activate" || comName=="click")
    		{
                IDoExit(RC_INTERFACE_SALARY_EXIT);
    		}
    	break;
	}
}

void CalculateEndSiegeCity()
{
    string sTemp =  GetNationNameByType(iNation);
    
	totalInfo = GetCityName(sCity) + XI_ConvertString("CapColony1_2") + XI_ConvertString(sTemp + "Gen") + ".";

    SetNewGroupPicture("Nat1", "NATIONS",  sTemp);
    SetFormatedText("INFO_TEXT",totalInfo);
}

void CalculateSiegeCity()
{
    string sTemp =  GetNationNameByType(iNation);
    
	if (!isCityHasFort(sCity)) // сухопутный город
	{
	    totalInfo = XI_ConvertString("CapColony2_1") + XI_ConvertString(sTemp + "Gen") + XI_ConvertString("CapColony2_2") + GetCityName(sCity) + XI_ConvertString("CapColony2_3") + FindRussianDaysString(iDay) + XI_ConvertString("CapColony2_4");
	}
	else
	{
		totalInfo = XI_ConvertString("CapColony3_1") + XI_ConvertString(sTemp + "Gen") + XI_ConvertString("CapColony3_2") + GetCityName(sCity)+XI_ConvertString("CapColony3_3") + FindRussianDaysString(iDay) + XI_ConvertString("CapColony3_4");
	}
    SetNewGroupPicture("Nat1", "NATIONS",  sTemp);
    SetFormatedText("INFO_TEXT",totalInfo);
}

void CalculateCapturedCity()
{

    totalInfo = XI_ConvertString("CapColony4_1") + XI_ConvertString("Colony" + sCity) + XI_ConvertString("CapColony4_2");

    SetNewGroupPicture("Nat1", "NATIONS",  GetNationNameByType(iNation));
    SetFormatedText("INFO_TEXT",totalInfo);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}