// Sith окно уведомления
string descr = "";
int curShowTutorial;

void InitInterface_S(string iniName, string messageName)
{
	StartAboveForm(true);
	//LAi_SetActorType(pchar);
	// лочим квест и карту
    bQuestCheckProcessFreeze = true;
    if(IsEntity(&worldMap))
    {
    	wdmLockReload = true;
    }

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	PlaySound("Ambient\SEA\Ship_bell_OneShot.wav");											

	descr = messageName;//GetConvertStr(messageName, "MessageDescribe.txt"));
	SetFormatedText("INFO_TEXT", descr);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	int nStrings = GetNumberOfStringsInFormatedText("INFO_TEXT", descr); // считаем сколько строк в форме
	if(nStrings <8)// Запрет на скроллинг
	{
		SetNodeUsing("SCROLL_TEXT",false);
		SendMessage( &GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 13, 1 ); //1 - запрет, 0 - нет
	}
	
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); // Выход
	SetEventHandler("exitCancel","ProcessCancelExit",0); // Выход по крестику или Esc
	SetEventHandler("ievnt_command","ProcCommand",0); // выход только тут (по НЕТ)
	SetEventHandler("CheckButtonChange","procCheckBoxChange",0);
	
	if(CheckAttribute(&InterfaceStates,"ShowTutorial")) 
	{
		curShowTutorial = int(InterfaceStates.ShowTutorial);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TUTORIAL_CHECKBOX", 2, 1, curShowTutorial);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_MESSAGE);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_MESSAGE);
}

void IDoExit(int exitCode)
{
	if(CheckAttribute(&InterfaceStates,"ShowTutorial"))
	{
		if(int(InterfaceStates.ShowTutorial) != curShowTutorial) SaveGameOptions();
	}
	EndAboveForm(true);
	//LAi_SetPlayerType(pchar);
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("CheckButtonChange","procCheckBoxChange");
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	PostEvent("StopQuestCheckProcessFreeze", 100);// заморозка проверки квестов
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
				IDoExit(RC_INTERFACE_MESSAGE);
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
