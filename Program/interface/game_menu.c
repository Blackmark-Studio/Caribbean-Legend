#define CONFIRMMODE_EXIT_MAINMENU	1
#define CONFIRMMODE_EXIT_GAME		2

bool DLCState;
int	 DLCCount; 	
int	 DLCAppID = 0; 

int g_nConfirmMode;
string g_sConfirmReturnWindow;

void InitInterface_gm(string iniName)
{
	GameInterface.title = "titleGameMenu";
	StartAboveForm(true);

	bGameMenuStart = true; // меню запущено, скрываем landinterface
	SetTimeScale(0.0);
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);

	SetEventHandler("QuitProcess","QuitProcess",0);
	SetEventHandler("evntSteamOverlayActivated","UpdateInterface",0);
	SetEventHandler("eventConfirm","procConfirm",0);

	InterfaceStates.showGameMenuOnExit = true;

	// логотип
	SetMenuLogo();

	if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
	{
		SetSelectable("MB_RESUME", true);
	} 
	else 
	{
		SetSelectable("MB_RESUME", false);
	}

	if (QuickSaveGameEnabledHardcore()) // boal 09.07.06
	{
		SetSelectable("MB_SAVE", true);
	} 
	else 
	{
		SetSelectable("MB_SAVE", false);
	}

	if (!CheckSaveGameEnabled())
	{
		SetSelectable("MB_SAVE", false);
	}
	
	string Vers = VERSION_NUMBER1 + GetVerNum();	
	SetFormatedText("VERSION_TEXT", Vers);

	// if(LAi_IsBoardingProcess())	SetSelectable("MB_RESUME",false); // Sith не блокируем кнопку продолжить игру во время абордажа

	if(bSteamAchievements && GetSteamEnabled())
	{
			DLCAppID = CheckUpdates();	
			if(DLCAppID > 0) // есть обновления
			{
				SetSelectable("MB_UPDATES", true);
			}
			else
			{	// обновлений нет
				SetSelectable("MB_UPDATES", false);
			}
	}
	else
	{ // обновлений нет
		SetSelectable("MB_UPDATES", false);
	}
}

void ProcessCancelExit()
{
	bGameMenuStart = false; // выход из меню, показываем landinterface
	if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
}

void IDoExit(int exitCode, bool bClear)
{
	EndAboveForm(true);
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");

    DelEventHandler("QuitProcess","QuitProcess");
	DelEventHandler("evntSteamOverlayActivated","UpdateInterface");
	DelEventHandler("eventConfirm","procConfirm");

	interfaceResultCommand = exitCode;

	if( interfaceResultCommand == RC_INTERFACE_DO_RESUME_GAME ) 
	{
		DeleteEntitiesByType("scrshoter");
	}
	EndCancelInterface(bClear);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "MB_RESUME":
			if (comName == "click" || comName == "activate"){
				bGameMenuStart = false; // выход из меню, показываем landinterface
				IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
			}
		break;
		case "MB_SAVE":
			if (comName == "click" || comName == "activate"){
				IDoExit(RC_INTERFACE_DO_SAVE_GAME, true);
			}
		break;		

		case "MB_LOAD":
			if (comName == "click" || comName == "activate"){
				IDoExit(RC_INTERFACE_DO_LOAD_GAME, true);
			}
		break;

		case "MB_OPTIONS":
			if (comName == "click" || comName == "activate"){
				IDoExit(RC_INTERFACE_DO_OPTIONS, true);
			}
		break;
		
		case "MB_EXITMENU":
			if (comName == "click" || comName == "activate"){
				DoConfirm(CONFIRMMODE_EXIT_MAINMENU);
			}
		break;

		case "MB_EXITGAME":
			if (comName == "click" || comName == "activate"){
				DoConfirm(CONFIRMMODE_EXIT_GAME);
			}
		break;

		case "MB_UPDATES":
			if (comName == "click" || comName == "activate")
			{
				if(DLCAppID > 0 && bSteamAchievements && GetSteamEnabled())
				{
					DLCState = DLCStartOverlay(MAIN_APPID); // открываем окошко в стиме для главной игры а не для дополнения
				}
			}
		break;
	}
}

void DoConfirm( int nConfirmMode )
{
	g_sConfirmReturnWindow = "MAIN_WINDOW";
	XI_WindowDisable( g_sConfirmReturnWindow, true );
	// enable confirm window
	XI_WindowDisable( "CONFIRM_WINDOW", false );
	XI_WindowShow( "CONFIRM_WINDOW", true );
	SetCurrentNode( "CONFIRM_YES" );

	g_nConfirmMode = nConfirmMode;
	switch( nConfirmMode )
	{
	case CONFIRMMODE_EXIT_MAINMENU:
		SetFormatedText( "CONFIRM_TEXT", XI_ConvertString("Confirm_exit_to_mainmenu"));
		break;
	case CONFIRMMODE_EXIT_GAME:
		SetFormatedText( "CONFIRM_TEXT", XI_ConvertString("Confirm_exit_from_menu"));
		break;
	}
	SendMessage( &GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONFIRM_TEXT", 5 ); // центрируем по вертикали
}

void procConfirm()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if( iComIndex==ACTION_ACTIVATE || iComIndex==ACTION_MOUSECLICK ) {
		if( sNodName=="CONFIRM_YES" ) {
			UndoConfirm(true);
			bGameMenuStart = false; // выход из меню, показываем landinterface
		}
		if( sNodName=="CONFIRM_NO" ) {
			UndoConfirm(false);
		}
	}
	if( iComIndex==ACTION_DEACTIVATE ) {
		UndoConfirm(false);
	}
}

void UndoConfirm(bool bPositiveChoose)
{
	// disable confirm
	XI_WindowDisable( "CONFIRM_WINDOW", true );
	XI_WindowShow( "CONFIRM_WINDOW", false );
	// enable window where confirm was started
	XI_WindowDisable( g_sConfirmReturnWindow, false );

	int nTmp = g_nConfirmMode;
	if( bPositiveChoose ) {
		switch( nTmp )
		{
		case CONFIRMMODE_EXIT_MAINMENU: IDoExit(RC_INTERFACE_MAIN_MENU_EXIT,true); break;
		case CONFIRMMODE_EXIT_GAME: QuitProcess(); break;
		}
	}
	// ser current nodes with confirm windows exit
	switch( nTmp )
	{
	case CONFIRMMODE_EXIT_MAINMENU: SetCurrentNode("MB_EXITMENU"); break;
	case CONFIRMMODE_EXIT_GAME: SetCurrentNode("MB_EXITGAME"); break;
	}
}

void QuitProcess()
{
   // вылетам у форта НЕТ -->
	PauseParticles(true);
	EngineLayersOffOn(false);
    if (bSeaActive && !bAbordageStarted)
    {
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	IDoExit(-1, false);
	ExitProgram();
}

void UpdateInterface()
{
	bool isSteamOverlayEnabled = GetEventData();

	if(!bSteamAchievements || !GetSteamEnabled()) return;
	
	trace("isSteamOverlayEnabled : " + isSteamOverlayEnabled );
	if(!isSteamOverlayEnabled) // оверлей закрыт
	{
		DLCAppID = CheckUpdates();	
		if(DLCAppID > 0) 
		{   // есть обновления
			SetSelectable("MB_UPDATES", true);
		}
		else
		{	// обновлений нет
			SetSelectable("MB_UPDATES", false);
		}
	}
	else // оверлей открыт, ничего не делаем
	{
	}
}

bool CheckUpdates()
{
	bool   bOk  = false;
	bool   bOk1 = false;
	bool   bOk2 = false;
	int	   i;
	int	   appID;
	string sText = "";
	int    dlcCount = 0; 

	if(bSteamAchievements && GetSteamEnabled())
	{
		dlcCount = GetDLCCount();
		for(i = 0; i < dlcCount; i++)
		{
			appID = GetDLCData(i);
			if( appID > 0 )
			{
				bOk = GetDLCenabled(appID);
				if(!bOk) 
				{
					bOk1 = true;
				}	
				else
				{
					switch (i)
					{
						case 0:						
							sText = sText + " + 'Калеуче'";
						break;
					
						case 1:
							sText = sText + " + 'Последний урок'";		
						break;
						
						case 2:
							sText = sText + " + 'Под черным флагом'";		
						break;
						
						case 3:
							sText = sText + NewStr() + " + 'Герой нации'";		
							bOk2 = true;							
						break;
						
						case 4:
							if(bOk2)   	sText = sText + " + 'Долго и счастливо'";		
							else 		sText = sText + NewStr() + " + 'Долго и счастливо'";		
						break;
						
					}
				}
			}
		}
		SetFormatedText("DLC_TEXT", sText);
	}
	return bOk1;
}


