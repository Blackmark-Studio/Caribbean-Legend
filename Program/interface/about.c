// Mitrokosta/Sith Авторы

float fNewPos;
float factor;
int aboutFileId;
int totalLines;

void InitInterface(string iniName)
{
	EngineLayersOffOn(true);
	GameInterface.title = "";
	
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak", "ProcessCancelExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("My_MoveText", "MoveText", 0);

	SetFormatedText("INFO_TEXT", "");

	aboutFileId = LanguageOpenFile("about.txt");
	int headers = 0;
	string sValue, sAttr;
	sValue = LanguageConvertString(aboutFileId, "headers");
	if (sValue != "") headers = sti(sValue);
	
	for (int i = 1; i <= headers; i++) {
		int lines = 0;
		sAttr = "header_" + i;
		sValue = LanguageConvertString(aboutFileId, sAttr + "_lines");
		if (sValue != "") lines = sti(sValue);
		
		int skip = 1;
		sValue = LanguageConvertString(aboutFileId, sAttr + "_skip");
		if (sValue != "") skip = sti(sValue);
		
		sValue = LanguageConvertString(aboutFileId, sAttr + "_text");
		AddTextToCredits(sValue);
		
		sValue = LanguageConvertString(aboutFileId, sAttr + "_color");
		// if (sValue != "") SetLineColor(sValue);
		if (sValue == "") sValue = "yellow";
		SetLineColor(sValue);
		
		for (int j = 1; j <= lines; j++) {
			sValue = LanguageConvertString(aboutFileId, sAttr + "_line_" + j);
			AddTextToCredits(sValue);
			sValue = LanguageConvertString(aboutFileId, sAttr + "_line_" + j + "_color");
			if (sValue != "") SetLineColor(sValue);
		}
		
		for (j = 1; j <= skip; j++) {
			AddTextToCredits("");
		}
	}
	
	LanguageCloseFile(aboutFileId);

	PostEvent("My_MoveText", 600);
	fNewPos = 0;
	ResetSound();
	SetMusic("music_credits");
}

void AddTextToCredits(string text) {
	SendMessage(&GameInterface, "lsle", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 0, text + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	totalLines++;
}

int GetColorFromPreset(string preset) {
	switch (preset) {
		case "yellow":
			return argb(255,251,237,68);
		break;
		
		case "red":
			return argb(255,255,162,162);
		break;
		
		case "blue":
			return argb(255,0,255,255);
		break;
	}
	
	return argb(255,255,255,255);
}

void SetLineColor(string preset) {
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, totalLines - 1, GetColorFromPreset(preset));
}

void IDoExit(int exitCode)
{
 	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("My_MoveText","MoveText");
    
	interfaceResultCommand = exitCode;
	if(CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit) == true)
		EndCancelInterface(true);
	else
		EndCancelInterface(false);
	ResetSound();
}

void ProcessCancelExit()
{
	if(CheckAttribute(&InterfaceStates, "showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}
	IDoExit(RC_INTERFACE_ABOUT_EXIT);
	if(!CheckAttribute(&InterfaceStates, "InstantExit") || sti(InterfaceStates.InstantExit) == false) ReturnToMainMenu();
}

void MoveText()
{
	if(fNewPos >= 1)
	{
		ProcessCancelExit();
	}
	else
	{
		SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_MSG_TO_NODE,"LOGO",0, 80, makeint(50 - fNewPos * factor), 470, makeint(250 - fNewPos * factor));
		SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_MSG_TO_NODE,"BMS",0, 120, makeint(210 - fNewPos * factor), 430, makeint(360 - fNewPos * factor));
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",2, fNewPos);
		PostEvent("My_MoveText", 20);
		factor = 7800; // скорость лого (больше быстрее)
		// fNewPos = fNewPos + 0.00015;// скорость текста (больше быстрее)
		fNewPos = fNewPos + 0.00022;// скорость текста (больше быстрее)
	}
}
