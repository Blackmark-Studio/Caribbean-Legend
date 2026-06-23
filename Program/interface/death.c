// Sith смерть
void InitInterface(string iniName)
{
    GameInterface.title = "";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("ShowButtons","ShowButtons",0);

	PlayStereoOGG("music_death");
	if (CheckAttribute(&InterfaceStates, "DeathPic")) 
	{
		SetNewPicture("DEATH_PIC", InterfaceStates.DeathPic);
	}
	HideButtons();
	PostEvent("ShowButtons",2000);
}

void IDoExit(int exitCode)
{
    DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ShowButtons","ShowButtons");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
        case "MB_LOAD":
    		if(comName=="activate" || comName=="click")
    		{
				LoadLastSave();
    		}
    	break;

    	case "MB_MENU":
    		if(comName=="activate" || comName=="click")
    		{
				IDoExit(RC_INTERFACE_MAIN_MENU_EXIT);
    		}
    	break;
	}
}

void LoadLastSave()
{    
    SetEventHandler("evntLoad","LoadGame",0);
    PostEvent("evntLoad",0,"s", GetLastSavePathFromCurrentProfile());
    IDoExit(-1);
}
void HideButtons()
{
	SetNodeUsing("MB_LOAD",false);
	SetNodeUsing("MB_MENU",false);
}

void ShowButtons()
{
	SetNodeUsing("MB_MENU",true);
	// кнопка "продолжить игру" --->
	string saveName = GetLastSavePathFromCurrentProfile();
	string saveData;
	if(saveName != "") SendMessage(&GameInterface,"lse",MSG_INTERFACE_GET_SAVE_DATA,saveName,&saveData);
	if(saveName == "" || saveData == "") 
	{
		SetNodeUsing("MB_LOAD", false); // нет сохранений
		SetCurrentNode("MB_MENU");
	}
	else 
	{
		SetNodeUsing("MB_LOAD", true);
		SetCurrentNode("MB_LOAD");
	}
	// <---
}