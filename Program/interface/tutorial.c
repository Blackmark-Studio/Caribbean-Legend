// Sith окно обучения
string descr = "";
string loadScr = "";
string cimg1 = "";
string cimg2 = "";
string cimg3 = "";
string cimg4 = "";
string cimg5 = "";
string cimg6 = "";
int curShowTutorial;
object obGKIC;

void InitInterface_SB(string iniName, string tutorialName, bool bShowVideo)
{
	// if(bShowVideo) PauseAllSounds(); // ставим звуки на паузу если видео
	StartAboveForm(true);
	//LAi_SetActorType(pchar);
	// лочим квест и карту
    bQuestCheckProcessFreeze = true;
    if(IsEntity(&worldMap))
    {
    	wdmLockReload = true;
    }

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    SetFormatedText("TITLE", GetConvertStr(tutorialName, "TutorialDescribe.txt"));
	if(bShowVideo) // если играем видео
	{
		SetNodeUsing("INFO_PICTURE", false);
		SetNodeUsing("INFO_VIDEO", true);
		loadScr = "tutorial\" + tutorialName + ".webm";
		SetNewVideo("INFO_VIDEO", loadScr);
		SetNewVideo("INFO_VIDEOZ", loadScr);
	}
	else
	{
		SetNodeUsing("INFO_PICTURE", true);
		SetNodeUsing("INFO_VIDEO", false);
		SetNodeUsing("ZOOM",false);
		SetNodeUsing("ZOOMPLUS",false);
		SetNodeUsing("VFRAME",false);
		loadScr = "interfaces\le\salary.tga";
		SetNewPicture("INFO_PICTURE", loadScr);
	}

	cimg1 = GetConvertStr(tutorialName + "_controlsimg1", "TutorialDescribe.txt");
	cimg2 = GetConvertStr(tutorialName + "_controlsimg2", "TutorialDescribe.txt");
	cimg3 = GetConvertStr(tutorialName + "_controlsimg3", "TutorialDescribe.txt");
	cimg4 = GetConvertStr(tutorialName + "_controlsimg4", "TutorialDescribe.txt");
	cimg5 = GetConvertStr(tutorialName + "_controlsimg5", "TutorialDescribe.txt");
	cimg6 = GetConvertStr(tutorialName + "_controlsimg6", "TutorialDescribe.txt");
	SetFormatedText("CONTROLS_TEXT", XI_ConvertString("Controls") + ":");
	if(cimg1 !="" || cimg2 !="" || cimg3 !="" || cimg4 !="" || cimg5 !="" || cimg6 !="")
	{
		string cimTotal = "";
		if(cimg1 !="") cimTotal += GetKeyCodeImg(cimg1);
		if(cimg2 !="") cimTotal += GetKeyCodeImg(cimg2);
		if(cimg3 !="") cimTotal += GetKeyCodeImg(cimg3);
		if(cimg4 !="") cimTotal += GetKeyCodeImg(cimg4);
		if(cimg5 !="") cimTotal += GetKeyCodeImg(cimg5);
		if(cimg6 !="") cimTotal += GetKeyCodeImg(cimg6);
		SetFormatedText("CONTROLS_IMG", cimTotal);
		/* if(cimg2 !="") SetFormatedText("CONTROLS_IMG", GetKeyCodeImg(cimg1)+GetKeyCodeImg(cimg2));		
		else SetFormatedText("CONTROLS_IMG", GetKeyCodeImg(cimg1)); */
		SetNodeUsing("B_OK", false);
		SetNodeUsing("B_OK2", true);
		SetNodeUsing("CONTROLS_TEXT", true);
		SetNodeUsing("CONTROLS_IMG", true);
	}
	else
	{
		SetFormatedText("CONTROLS_TEXT", "");
		SetNodeUsing("B_OK", true);
		SetNodeUsing("B_OK2", false);		
		SetNodeUsing("CONTROLS_TEXT", false);
		SetNodeUsing("CONTROLS_IMG", false);
	}

	PlaySound("Ambient\SEA\Ship_bell_Two.wav");											

    SetKeyAttrs();
	descr = GetConvertStr(tutorialName + "_descr", "TutorialDescribe.txt");
    descr = GetAssembledString(descr, &obGKIC);
	SetFormatedText("INFO_TEXT", descr);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	int nStrings = GetNumberOfStringsInFormatedText("INFO_TEXT", descr); // считаем сколько строк в форме
	// Log_TestInfo("Всего строк " + nStrings);
	if(nStrings <9)// Запрет на скроллинг
	{
		SetNodeUsing("SCROLL_TEXT",false);
		SendMessage( &GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 13, 1 ); //1 - запрет, 0 - нет
	}
	
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); // Выход
	SetEventHandler("exitCancel","ProcessCancelExit",0); // Выход по крестику или Esc
	SetEventHandler("ievnt_command","ProcCommand",0); // выход только тут (по НЕТ)
	SetEventHandler("CheckButtonChange","procCheckBoxChange",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0); // выход из интерфейса
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);

	if(CheckAttribute(&InterfaceStates,"ShowTutorial")) 
	{
		curShowTutorial = sti(InterfaceStates.ShowTutorial);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TUTORIAL_CHECKBOX", 2, 1, curShowTutorial);
	SetNodeUsing("TUTORIAL_CHECKBOX",!bGlobalTutor);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_TUTORIAL);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_TUTORIAL);
}

void IDoExit(int exitCode)
{
	if(CheckAttribute(&InterfaceStates,"ShowTutorial"))
	{
		if(sti(InterfaceStates.ShowTutorial) != curShowTutorial) SaveGameOptions();
	}
	EndAboveForm(true);
	//LAi_SetPlayerType(pchar);
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("CheckButtonChange","procCheckBoxChange");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	PostEvent("StopQuestCheckProcessFreeze", 100);// заморозка проверки квестов
	// SetSchemeAfterFlagRise(); // возвращаем звуки если видео
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
				IDoExit(RC_INTERFACE_TUTORIAL);
			}
		break;
		case "B_OK2":
			if(comName=="activate" || comName=="click")
			{
				IDoExit(RC_INTERFACE_TUTORIAL);
			}
		break;
	}
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if(sNodName == "TUTORIAL_CHECKBOX") 
	{
		{
			InterfaceStates.ShowTutorial = bBtnState;
		}
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void ShowInfoWindow()
{
	XI_WindowDisable("INFO_WINDOW", false);
	XI_WindowShow("INFO_WINDOW", true);
}

void HideInfoWindow()
{
	XI_WindowDisable("INFO_WINDOW", true);
	XI_WindowShow("INFO_WINDOW", false);
}

void SetKeyAttrs()
{
    // GKIC - взять из конкретной группы
    // GetKeyCodeImg - взять из релевантной группы
    obGKIC.Ship_TurnLeft = GKIC("Ship_TurnLeft", "Sailing3Pers");
    obGKIC.TimeScale = GetKeyCodeImg("TimeScale");
}