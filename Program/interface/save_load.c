#define MAX_SAVE_SLOTS 10

#define SAVE_NAME 1
#define SAVE_GAMETIME 2
#define SAVE_RANK 3
#define SAVE_SQUADPOWER 4
#define SAVE_MONEY 5
#define SAVE_DOUBLOONS 6
#define SAVE_VERSION 7

#define PROFILE_NAME 1
#define PROFILE_HERONAME 2
#define PROFILE_HEROTYPE 3
#define PROFILE_DIFFICULTY 4
#define PROFILE_GAMEMODE 5

#define LIST_NAME 1
#define LIST_SYSTEMTIME 2
#define LIST_PLAYTIME 3

#define CONFIRMMODE_PROFILE_DELETE	1
#define CONFIRMMODE_SAVE_DELETE		2
#define CONFIRMMODE_SAVE_OVERWRITE	3
#define CONFIRMMODE_LOAD_GAME		4

int g_SaveSlots;
bool bSave;	// флаг интерфейса сохранения
aref scrshot;	// скриншотер
object emptyscrshot;
object g_oSaveList[MAX_SAVE_SLOTS];	// сейвы
int g_nCurrentSaveIndex = 0;	// выделенный сейв
int g_nFirstSaveIndex = -1;	// первый сейв на странице
string currentProfile = "";
object g_oSaveContainer;
int g_nSaveQuantity = 0;
bool bQuick = true;
bool bAuto = true;
bool bBadSave = false;
bool bGameProcess = true;
int g_nInterfaceFileID = -1;

string g_sReturnWindow;
int g_nConfirmMode;

void InitInterface_BB(string iniName, bool isSave, bool isMainMenu)
{
	if(CheckAttribute(&PlayerProfile, "name"))
		PlayerProfile.old_name = PlayerProfile.name;
	StartAboveForm(!isMainMenu);
	bSave = isSave;
	if(bSave)
		GameInterface.title = "titleSave";
	else
		GameInterface.title = "titleLoad";
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
	bGameProcess = !isMainMenu;
	g_nInterfaceFileID = LanguageOpenFile("interface_strings.txt");
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("ievnt_command", "ProcessCommandExecute", 0);
	SetEventHandler("ScrollPosChange", "ScrollPosChange", 0);
	SetEventHandler("RefreshSaves", "RefreshSaves", 0);
	SetEventHandler("eventConfirm", "ProcessConfirm", 0);
	SetEventHandler("eProfileBtnAction", "procProfileBtnAction", 0);
	SetEventHandler("eventSaveCustom", "ProcessCustomSaveAction", 0);
	SetEventHandler("ReadScreenshot", "ReadScreenshot", 1);
	SetMenuLogo();
	FillProfileList();	// заполняем объект профилей
	FindScrshotClass();	// подключаем скриншотер
	SetSaveLoadParams();
}

void SetSaveLoadParams()
{	
	if(bGameProcess)
	{
		SetFormatedTextButton("BUTTON_1", "Resume Game");
		if(bSave)
			SetFormatedTextButton("BUTTON_2", "Load");
		else
			SetFormatedTextButton("BUTTON_2", "Save");
		SetFormatedTextButton("BUTTON_3", "Back");
		SetNodeUsing("BUTTON_PROFILE", !bSave);
	}
	else
	{
		SetFormatedTextButton("BUTTON_1", "New Game");
		SetFormatedTextButton("BUTTON_2", "Back");
		SetNodeUsing("BUTTON_3", false);
	}
	InitSaveList();	// создаём сейвлист
	InitSortState();
	if(!bSave && !bGameProcess)// && currentProfile == "")
	{
		BLI_DisableShow();
		SetCurrentProfile(GetLastProfileFromCurrentProfile());
	}
	else
		SetCurrentProfile(GetCurrentProfile());
}

void ProcessCancelExit()
{
	if(CheckAttribute(&PlayerProfile, "old_name"))
		PlayerProfile.name = PlayerProfile.old_name;		// бэкап профиля
	if(CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == 1)
	{
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}
	IDoExit(RC_INTERFACE_SAVELOAD_EXIT);
	if(!CheckAttribute(&InterfaceStates,"InstantExit") || sti(InterfaceStates.InstantExit) == 0)
		ReturnToMainMenu();
}

void IDoExit(int exitCode)
{
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("ievnt_command", "ProcessCommandExecute");
	DelEventHandler("ScrollPosChange", "ScrollPosChange");
	DelEventHandler("RefreshSaves", "RefreshSaves");
	DelEventHandler("eventConfirm", "ProcessConfirm");
	DelEventHandler("eProfileBtnAction", "procProfileBtnAction");
	DelEventHandler("eventSaveCustom", "ProcessCustomSaveAction");
	DelEventHandler("ReadScreenshot", "ReadScreenshot");
	LanguageCloseFile(g_nInterfaceFileID);
	EndAboveForm(true);
	DeleteAttribute(&PlayerProfile,"old_name");
	GameInterface.SavePath = "SAVE";
    interfaceResultCommand = exitCode;
	if(CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit) == 1)
		EndCancelInterface(false);
	else
		EndCancelInterface(true);
}

void ProcessCommandExecute()
{
	string sCommand = GetEventData();
	string sNode = GetEventData();
	int iSlot;
	bool bFrame = IsStrLeft(sNode, "SAVEFRAME");
	bool bSaveButton = IsStrLeft(sNode, "SAVEBUTTON");
	if(bFrame || bSaveButton)
	{
		if(sCommand == "click" || sCommand == "dblclick")
		{
			iSlot = sti(strright(sNode, strlen(sNode) - 9)) - 1;
			SelectSlot(iSlot);
			if(bSaveButton || sCommand == "dblclick")
			{
				if(bSave)
				{
					if(iSlot == -1)
						LaunchCustomSaveGame();
					else
						ShowConfirmWindow(CONFIRMMODE_SAVE_OVERWRITE);					
				}
				else if(bGameProcess)
					ShowConfirmWindow(CONFIRMMODE_LOAD_GAME);
				else
					ProcessLoad();
			}
		}
		else if(sCommand == "upstep")
			ScrollSaveSlot(-1);
		else if(sCommand == "downstep")
			ScrollSaveSlot(1);
		else if(sCommand == "leftstep")
			SetCurrentNode("BUTTON_1");
		return;
	}
	if(IsStrLeft(sNode, "DELETEBUTTON"))
	{
		iSlot = sti(strright(sNode, strlen(sNode) - 9)) - 1;
		SelectSlot(iSlot);
		ShowConfirmWindow(CONFIRMMODE_SAVE_DELETE);
		return;
	}
	if(sNode == "BUTTON_PROFILE" && sCommand == "click")
	{
		ProcChooseProfileFromList();
		return;
	}
	if(sNode == "BUTTON_1")
	{
		if(sCommand == "rightstep")
		{
			iSlot = g_nCurrentSaveIndex - g_nFirstSaveIndex;
			SetCurrentNode("SAVEFRAME" + (iSlot + 1));
		}
		else if(sCommand == "click" || sCommand == "activate")
		{
			if(bGameProcess)
			{
				bGameMenuStart = false;
				IDoExit(RC_INTERFACE_DO_RESUME_GAME);
			}
			else
				IDoExit(RC_INTERFACE_DO_NEW_GAME);
		}
		return;
	}
	if(sNode == "BUTTON_2")
	{
		if(sCommand == "rightstep")
		{
			iSlot = g_nCurrentSaveIndex - g_nFirstSaveIndex;
			SetCurrentNode("SAVEFRAME" + (iSlot + 1));
		}
		else if(sCommand == "downstep" && bGameProcess)
			SetCurrentNode("BUTTON_3");
		else if(sCommand == "click" || sCommand == "activate")
		{
			if(bGameProcess)
			{
				bSave = !bSave;
				if(CheckAttribute(&PlayerProfile, "old_name"))
					PlayerProfile.name = PlayerProfile.old_name;
				if(bSave)
					GameInterface.title = "titleSave";
				else
					GameInterface.title = "titleLoad";
				SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TITLE", 0);
				SetSaveLoadParams();
			}
			else
				PostEvent("exitCancel", 1);
		}
		return;
	}
	if(sNode == "BUTTON_3")
	{
		if(sCommand == "rightstep")
		{
			iSlot = g_nCurrentSaveIndex - g_nFirstSaveIndex;
			SetCurrentNode("SAVEFRAME" + (iSlot + 1));
		}
		else if(sCommand == "click" || sCommand == "activate")
			IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
	}
}

void InitSortState()
{
	if(!CheckAttribute(&InterfaceStates, "ShowAutosaves"))
		InterfaceStates.ShowAutosaves = bAuto;
	else
		bAuto = sti(InterfaceStates.ShowAutosaves);
	if(!CheckAttribute(&InterfaceStates, "ShowQuicksaves"))
		InterfaceStates.ShowQuicksaves = bQuick;
	else
		bQuick = sti(InterfaceStates.ShowQuicksaves);
	
	CheckButton_SetState("SHOW_AUTOSAVES", 1, bAuto);
	CheckButton_SetState("SHOW_QUICKSAVES", 1, bQuick);
}

void RefreshSaves()
{
	bAuto = CheckButton_GetState("SHOW_AUTOSAVES", 1);
	bQuick = CheckButton_GetState("SHOW_QUICKSAVES", 1);
	
	InterfaceStates.ShowAutosaves = bAuto;
	InterfaceStates.ShowQuicksaves = bQuick;
	
	SetCurrentProfile(currentProfile);
	SendMessage(&GameInterface, "lsf", MSG_INTERFACE_SET_SCROLLER, "SAVESCROLL", 0.0);
}

void ScrollSaveSlot(int diff)
{
	if(diff == 0)
		return;
	if(g_nCurrentSaveIndex + diff < 0)
		return;
	if(g_nCurrentSaveIndex + diff >= g_nSaveQuantity)
		return;
	int oldSlot = g_nCurrentSaveIndex - g_nFirstSaveIndex;
	int newSlot = oldSlot + diff;
	if(newSlot < 0)
	{
		newSlot = 0;
		FillSaveList(g_nCurrentSaveIndex + diff);
		SendMessage(&GameInterface, "lsf", MSG_INTERFACE_SET_SCROLLER, "SAVESCROLL", makefloat(g_nFirstSaveIndex + diff) / makefloat(g_nSaveQuantity - g_SaveSlots + 1));
	}
	if(newSlot >= g_SaveSlots)
	{
		newSlot = g_SaveSlots - 1;
		FillSaveList(g_nCurrentSaveIndex + diff - g_SaveSlots + 1);
		SendMessage(&GameInterface, "lsf", MSG_INTERFACE_SET_SCROLLER, "SAVESCROLL", makefloat(g_nFirstSaveIndex + diff) / makefloat(g_nSaveQuantity - g_SaveSlots + 1));
	}
	SelectSlot(newSlot);
}

void ScrollPosChange()
{
	float fPos = GetEventData();
	string sNode = GetEventData();
	if(sNode == "SAVESCROLL")
	{
		if(g_nSaveQuantity <= g_SaveSlots)
			return;
		int oldPage = g_nFirstSaveIndex;
		int n = g_nSaveQuantity - g_SaveSlots + 1; // количество страниц
		int newPage = makeint(n * fPos);	// новая страница
		if(newPage == n)
			newPage -= 1;
		int diff = newPage - oldPage;	// на сколько листнули
		if(diff != 0)
			ScrollSavePage(diff, newPage);
	}
}

void ScrollSavePage(int diff, int newPage)
{
	int oldSlot = -1;
	if(g_nCurrentSaveIndex >= 0)
		oldSlot = g_nCurrentSaveIndex - g_nFirstSaveIndex;	// предыдущий выделенный слот
	int newSlot = oldSlot - diff;
	if(newSlot < 0)
		newSlot = 0;
	if(newSlot >= g_SaveSlots)
		newSlot = g_SaveSlots - 1;
	if(oldSlot == -1)
		newSlot = -1;
	int iSlot;
	if(diff != 0)
	{
		FillSaveList(newPage);
		SelectSlot(newSlot);
	}
}

void FillProfileList()
{
	PlayerProfile.profilesQuantity = 0;
	object FolderList;
	XI_FindFoldersWithoutNetsave("SAVE\*", &FolderList);
	int num = GetAttributesNum(&FolderList);
	string folderName;
	int i = 0;
	string attr;
	for(i = 0; i < num; i++)
	{
		attr = "profile_" + i;
		PlayerProfile.(attr) = GetAttributeValue(GetAttributeN(&FolderList, i));
	}
	PlayerProfile.profilesQuantity = num;
}

string GetCurrentProfile()
{
	if(CheckAttribute(&PlayerProfile, "name") && PlayerProfile.name != "")
		return PlayerProfile.name;
	
	trace("error (save_load.c) : PlayerProfile.name attribute not found.");

	object FolderList;
	XI_FindFoldersWithoutNetsave("SAVE"+ "\*", &FolderList);

	int num = GetAttributesNum(&FolderList);
	if(num > 0)
		return GetAttributeValue(GetAttributeN(&FolderList, num - 1));
	return "";
}

void FindScrshotClass()
{
	if(!GetEntity(&scrshot, "scrshoter"))
		makearef(scrshot, emptyscrshot);
}

void InitSaveList()
{
	int i;
	int x1, y1, x2, y2;
	GetNodePosition("PAPER", &x1, &y1, &x2, &y2);
	log_info(x1 + "," + y1 + "," + x2 + "," + y2);
	int x_base = x1 + 30;
	int y_base = y1 + 90;
	int y_max = y2 - 90;
	float kScreen = 1920.0 / 1080.0;
	float kSpace = 0.5;
	int height = makeint((y_max - y_base) / ((1.0 + kSpace) * MAX_SAVE_SLOTS));
	int space = makeint(height * kSpace);
	int width = makeint(height * kScreen);
	int y_cur;
	int text_width = 280;
	int button_width = height / 2;
	int button_space = 15;
	string sNode;
	XI_DeleteNode("SAVELIST_INFO");
	XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "STRINGCOLLECTION", "SAVELIST_INFO", 250);
	XI_WindowAddNode("MAIN_WINDOW", "SAVELIST_INFO");
	
	int nSlots = MAX_SAVE_SLOTS;
	if(bSave)
		nSlots -= 1;
	
	for(i = 0; i < nSlots; i++)
	{
		g_oSaveList[i].saveidx = -1;
		// оставляем место под "новое сохранение"
		if(bSave)
			y_cur = y_base + (i + 1) * (height + space);
		else
			y_cur = y_base + i * (height + space);
		
		// создаём рамки
		sNode = "SAVEFRAME" + (i + 1);
		XI_DeleteNode(sNode);
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "FRAME_CLICKABLE", sNode, 190);
		XI_WindowAddNode("MAIN_WINDOW", sNode);
		SetNodePosition(sNode, x_base - 5, y_cur - 5, x_base + width + text_width + 2 * button_width + button_space + 10, y_cur + height + 5);
		Picture_SetGroupPicture(sNode, "SAVELOAD", "frame_bronze");

		// создаём картинки
		sNode = "SAVEIMG" + (i + 1);
		XI_DeleteNode(sNode);
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", sNode, 200);
		XI_WindowAddNode("MAIN_WINDOW", sNode);
		SetNodePosition(sNode, x_base, y_cur, x_base + width, y_cur + height);
		
		// создаём кнопки
		sNode = "SAVEBUTTON" + (i + 1);
		XI_DeleteNode(sNode);
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "FRAME_CLICKABLE", sNode, 200);
		XI_WindowAddNode("MAIN_WINDOW", sNode);
		SetNodePosition(sNode, x_base + width + text_width, y_cur + (height - button_width) / 2, x_base + width + text_width + button_width, y_cur + height - (height - button_width) / 2);
		Picture_SetGroupPicture(sNode, "SAVELOAD", "save");
		
		sNode = "DELETEBUTTON" + (i + 1);
		XI_DeleteNode(sNode);
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "FRAME_CLICKABLE", sNode, 200);
		XI_WindowAddNode("MAIN_WINDOW", sNode);
		SetNodePosition(sNode, x_base + width + text_width + button_width + button_space, y_cur + (height - button_width) / 2, x_base + width + text_width + 2 * button_width + button_space, y_cur + height - (height - button_width) / 2);
		Picture_SetGroupPicture(sNode, "SAVELOAD", "delete");

		// создаём подписи
		StringCollection_AddText("SAVELIST_INFO", "name" + (i+1), "SaveName", "interface_normal", x_base + width + text_width / 2, y_cur, argb(255,148,148,148), argb(0,128,128,128), 2, false, 1.2 * 10.0 / (1.0 * MAX_SAVE_SLOTS), text_width);
		StringCollection_AddText("SAVELIST_INFO", "systemtime" + (i+1), "SystemTime", "interface_normal", x_base + width + text_width / 2, y_cur + 2 * height / 5, argb(255,148,148,148), argb(0,128,128,128), 2, false, 1.0 * 10.0 / (1.0 * MAX_SAVE_SLOTS), text_width);
		StringCollection_AddText("SAVELIST_INFO", "playtime" + (i+1), "PlayTime", "interface_normal", x_base + width + text_width / 2, y_cur + 2 * height / 3, argb(255,148,148,148), argb(0,128,128,128), 2, false, 1.0 * 10.0 / (1.0 * MAX_SAVE_SLOTS), text_width);
	}
	if(bSave)
	{
		sNode = "SAVEFRAME_NEW";
		XI_DeleteNode(sNode);
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "FRAME_CLICKABLE", sNode, 190);
		XI_WindowAddNode("MAIN_WINDOW", sNode);
		SetNodePosition(sNode, x_base - 5, y_base - 5, x_base + width + text_width + 2 * button_width + button_space + 10, y_base + height + 5);
		Picture_SetGroupPicture(sNode, "SAVELOAD", "frame_newsave");

		sNode = "SAVEBUTTON_NEW";
		XI_DeleteNode(sNode);
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "FRAME_CLICKABLE", sNode, 200);
		XI_WindowAddNode("MAIN_WINDOW", sNode);
		SetNodePosition(sNode, x_base + width + text_width, y_base + (height - button_width) / 2, x_base + width + text_width + button_width, y_base + height - (height - button_width) / 2);
		Picture_SetGroupPicture(sNode, "SAVELOAD", "save");

		StringCollection_AddText("SAVELIST_INFO", "newsave", XI_ConvertString("NewSave"), "interface_normal", x_base + width + text_width / 2, y_base + height / 4, argb(255,148,148,148), argb(0,128,128,128), 2, false, 1.2 * 10.0 / (1.0 * MAX_SAVE_SLOTS), text_width);
	}
}

void SetCurrentProfile(string sProfileName)
{
	currentProfile = sProfileName;
	PlayerProfile.name = sProfileName;
	DeleteAttribute(&g_oSaveContainer, "");
	int nSaveNum = 0;
	string saveName;
	int nSaveSize;
	string attr;
	GameInterface.SavePath = "SAVE\" + currentProfile;
	string sData;
	while(FindSaveFile(nSaveNum, &saveName, nSaveSize))	// ищем файлы, заполняем контейнер
	{
		attr = "s" + nSaveNum;
		sData = "";
		g_oSaveContainer.(attr).savename = saveName;
		g_oSaveContainer.(attr).savesize = nSaveSize;
		nSaveNum++;
	}
	g_nSaveQuantity = nSaveNum;
	ResetSlots();
	PostEvent("ReadScreenshot", 0, "l", 0);	
	FillSaveList(0);	// заполняем интерфейс
	// выделяем новое сохранение или первый лоад
	if(bSave)
		SelectSlot(-1);
	else
		SelectSlot(0);
	// заполняем инфо
	StringCollection_SetText("PROFILE_INFO", PROFILE_NAME, "#" + XI_ConvertString("ProfileName") + ": " + currentProfile);
}

void ResetSlots()
{
	int nSlots = MAX_SAVE_SLOTS;
	if(bSave)
		nSlots -= 1;
	g_SaveSlots = nSlots;
	if(g_nSaveQuantity < g_SaveSlots)
		g_SaveSlots = g_nSaveQuantity;
	for(int i = 0; i < nSlots; i++)
	{
		if(i < g_SaveSlots)
		{
			SetNodeUsing("SAVEFRAME" + (i + 1), true);
			SetNodeUsing("SAVEIMG" + (i + 1), true);
			SetNodeUsing("SAVEBUTTON" + (i + 1), true);
			SetNodeUsing("DELETEBUTTON" + (i + 1), true);
		}
		else
		{
			SetNodeUsing("SAVEFRAME" + (i + 1), false);
			SetNodeUsing("SAVEIMG" + (i + 1), false);
			SetNodeUsing("SAVEBUTTON" + (i + 1), false);
			SetNodeUsing("DELETEBUTTON" + (i + 1), false);
			StringCollection_ChangeColor("SAVELIST_INFO", i * 3 + LIST_NAME, argb(0,0,0,0));
			StringCollection_ChangeColor("SAVELIST_INFO", i * 3 + LIST_SYSTEMTIME, argb(0,0,0,0));
			StringCollection_ChangeColor("SAVELIST_INFO", i * 3 + LIST_PLAYTIME, argb(0,0,0,0));
		}
	}
	
	SetNodeUsing("SAVEIMG_BIG", false);
	SetNodeUsing("FADER_LEFT", false);
	SetNodeUsing("FADER_RIGHT", false);
	SetNodeUsing("FADER_LONG", false);
	SetNodeUsing("ICON_MONEY", false);
	SetNodeUsing("SAVE_INFO", false);
	SetNodeUsing("SAVE_LOCATION", false);
	SetNodeUsing("SAVE_TAG", false);
	SetNodeUsing("OFFICERSPROFESSION", false);
	for(i = 1; i <= 9; i++)
	{
		SetNodeUsing("OFFICER_" + i, false);
	}
	
	StringCollection_ChangeColor("PROFILE_INFO", PROFILE_HERONAME, argb(0,0,0,0));
	StringCollection_ChangeColor("PROFILE_INFO", PROFILE_HEROTYPE, argb(0,0,0,0));
	StringCollection_ChangeColor("PROFILE_INFO", PROFILE_GAMEMODE, argb(0,0,0,0));
	StringCollection_ChangeColor("PROFILE_INFO", PROFILE_DIFFICULTY, argb(0,0,0,0));
	
	SetNodeUsing("SHOW_AUTOSAVES", false);
	SetNodeUsing("SHOW_QUICKSAVES", false);
	
	Picture_SetGroupPicture("HERO_FACE", "FACE128_captain", "face");
}

void ReadScreenshot()
{
	int iSave = GetEventData();
	if(iSave >= g_nSaveQuantity)
		return;
	string attr = "s" + iSave;
	if(!CheckAttribute(&g_oSaveContainer, attr))
		return;
	string saveName = g_oSaveContainer.(attr).savename;
	string sData = "";
	g_oSaveContainer.(attr).screenshot = Screenshoter_GetData(currentProfile, saveName, &sData);
	g_oSaveContainer.(attr).savedata = sData;
	PostEvent("ReadScreenshot", 0, "l", iSave + 1);
}

bool FindSaveFile(int nSaveNum, ref saveName, ref nSaveSize)
{
	return SendMessage(&GameInterface, "llee", MSG_INTERFACE_SAVE_FILE_FIND, nSaveNum, &saveName, &nSaveSize) != 0;
}

void FillSaveList(int nFirstSaveIndex)
{
	if(nFirstSaveIndex < 0)
		nFirstSaveIndex = 0;
	g_nFirstSaveIndex = nFirstSaveIndex;
	string attr;
	int iSaveIdx;
	// проходим по каждому слоту
	int iSlot = 0;
	int iSkip = 0;
	bool bLoad;
	while (iSlot < g_SaveSlots)
	{
		bLoad = false;
		iSaveIdx = nFirstSaveIndex + iSlot + iSkip;
		attr = "s" + iSaveIdx;
		ClearSaveInfoByIndex(iSlot);	// чистим слот
		if(CheckAttribute(&g_oSaveContainer, attr))
		{
			if(CheckAttribute(&g_oSaveContainer, attr + ".screenshot") && CheckAttribute(&g_oSaveContainer, attr + ".savedata"))
				bLoad = LoadInfo(iSlot, iSaveIdx, g_oSaveContainer.(attr).savename, sti(g_oSaveContainer.(attr).screenshot), g_oSaveContainer.(attr).savedata);	// заполняем слот, если есть чем
			else
			{
				bLoad = LoadInfo(iSlot, iSaveIdx, g_oSaveContainer.(attr).savename, -1, "");
				if(bLoad)
					Screenshoter_Release(g_oSaveContainer.(attr).savename);
			}
		}
		else
			break;
		if(bLoad)
			iSLot++;
		else
			iSkip++;
	}
	SetNodeUsing("SAVESCROLL", g_nSaveQuantity > g_SaveSlots);
}

void ClearSaveInfoByIndex(int iSlot)
{
    if(g_oSaveList[iSlot].saveidx == "-1")
		return;
	// удаляем данные из сейвлиста
    DeleteAttribute(&g_oSaveList[iSlot], "");
    g_oSaveList[iSlot].saveidx = -1;
}

bool LoadInfo(int iSlot, int iSaveIdx, string sSaveName, int iTexture, string sData)
{
	g_oSaveList[iSlot].saveidx = iSaveIdx;
	g_oSaveList[iSlot].savefile = sSaveName;
	g_oSaveList[iSlot].loaded = 0;	// флаг того, что данные ещё не загружены
	return ReadSaveData(iSlot, iTexture, sData);	// загружаем данные сейва
}

bool ReadSaveData(int iSlot, int iTexture, string sData)
{
	if(sti(g_oSaveList[iSlot].saveidx) == -1)
		return false;
	if(CheckAttribute(&g_oSaveList[iSlot], "loaded") && sti(g_oSaveList[iSlot].loaded) != 0)
		return true;
	string sFile = g_oSaveList[iSlot].savefile;
	// считываем данные
	if(iTexture == -1 || sData == "")
		iTexture = Screenshoter_GetData(currentProfile, sFile, &sData);
	// десериализуем сейв
	ref saveInfo = &g_oSaveList[iSlot];
	object saveAttributes = DeserializeAttributes(sData);
	CopyAttributesSafe(saveInfo, &saveAttributes);
	// проверяем сортировку
	if(CheckAttribute(saveInfo, "savetype"))
	{
		if(saveInfo.savetype == "auto" && !bAuto)
			return false;
		if(saveInfo.savetype == "quick" && !bQuick)
			return false;
	}
	
	g_oSaveList[iSlot].loaded = 1;	// флаг того, что данные загружены
	
	// выставляем рамку
	string sNode = "SAVEFRAME" + (iSlot + 1);
	if(CheckAttribute(saveInfo, "savetype") && saveInfo.savetype == "auto")
		Picture_SetGroupPicture(sNode, "SAVELOAD", "frame_silver");
	else
		Picture_SetGroupPicture(sNode, "SAVELOAD", "frame_bronze");
	
	// выставляем скрин
	sNode = "SAVEIMG" + (iSlot + 1);
	Picture_SetTexture(sNode, iTexture);
	// выставляем системное время
	string sSystemTimeString = XI_ConvertString("No Time");
	if(CheckAttribute(&g_oSaveList[iSlot], "savefile") && g_oSaveList[iSlot].savefile != "")
		sSystemTimeString = GetSystemTimeString(iSlot);
	int iTimeIndex = iSlot * 3 + LIST_SYSTEMTIME;
	StringCollection_SetText("SAVELIST_INFO", iTimeIndex, "#" + sSystemTimeString);
	
	// выставляем название сейва
	string saveName = "Unknown";
	if(CheckAttribute(saveInfo, "locname"))
		saveName = "#" + saveInfo.locname;
	int iNameIndex = iSlot * 3 + LIST_NAME;
	StringCollection_SetText("SAVELIST_INFO", iNameIndex, saveName);
	// выставляем часы в игре
	string playTime = "No time";
	if(CheckAttribute(saveInfo, "playtime"))
		playTime = "#" + saveInfo.playtime;
	int iPlayTimeIndex = iSlot * 3 + LIST_PLAYTIME;
	StringCollection_SetText("SAVELIST_INFO", iPlayTimeIndex, playTime);
	return true;
}

int Screenshoter_GetData(string sProfile, string sFile, ref sData)
{
	return SendMessage(scrshot, "lsse", MSG_SCRSHOT_READ, "SAVE\" + sProfile, sFile, &sData);
}

void Screenshoter_Release(string sFile)
{
	SendMessage(scrshot, "ls", MSG_SCRSHOT_RELEASE, sFile);
}

string GetSystemTimeString(int iSlot)
{
	string fileSystemTime = "";
	string fileSystemDate = "";
	SendMessage(&GameInterface, "lsee", MSG_INTERFACE_GETTIME, "SAVE\" + currentProfile + "\" + g_oSaveList[iSlot].savefile, &fileSystemTime, &fileSystemDate);
	return fileSystemTime + " " + fileSystemDate;
}

void SelectSlot(int iSlot)
{
	if(iSlot >= g_SaveSlots)
		return;
	if(iSLot < -1)
		return;
	if(!bSave && iSlot < 0)
		return;
	bool bNewSave = false;
	if(bSave && iSlot == -1)
		bNewSave = true;
	
	if(!bNewSave)
		g_nCurrentSaveIndex = g_nFirstSaveIndex + iSlot;
	else
		g_nCurrentSaveIndex = -1;
	
	StringCollection_ChangeColor("PROFILE_INFO", PROFILE_HERONAME, argb(255,255,255,255));
	StringCollection_ChangeColor("PROFILE_INFO", PROFILE_HEROTYPE, argb(255,255,255,255));
	StringCollection_ChangeColor("PROFILE_INFO", PROFILE_GAMEMODE, argb(255,255,255,255));
	StringCollection_ChangeColor("PROFILE_INFO", PROFILE_DIFFICULTY, argb(255,255,255,255));
	
	SetNodeUsing("SHOW_AUTOSAVES", true);
	SetNodeUsing("SHOW_QUICKSAVES", true);
	
	int i;
	// выделяем ноду в списке
	for(i = 0; i < g_SaveSlots; i++)
	{
		if(i == iSlot)
		{
			Picture_SetColor("SAVEFRAME" + (i + 1), argb(255,128,128,128));
			StringCollection_ChangeColor("SAVELIST_INFO", i * 3 + LIST_NAME, argb(255,255,255,255));
			StringCollection_ChangeColor("SAVELIST_INFO", i * 3 + LIST_SYSTEMTIME, argb(255,255,255,255));
			StringCollection_ChangeColor("SAVELIST_INFO", i * 3 + LIST_PLAYTIME, argb(255,255,255,255));
			SetNodeUsing("SAVEBUTTON" + (i + 1), true);
			SetNodeUsing("DELETEBUTTON" + (i + 1), true);
			SetCurrentNode("SAVEFRAME" + (i + 1));
		}
		else
		{
			Picture_SetColor("SAVEFRAME" + (i + 1), argb(255,70,70,70));
			StringCollection_ChangeColor("SAVELIST_INFO", i * 3 + LIST_NAME, argb(255,148,148,148));
			StringCollection_ChangeColor("SAVELIST_INFO", i * 3 + LIST_SYSTEMTIME, argb(255,148,148,148));
			StringCollection_ChangeColor("SAVELIST_INFO", i * 3 + LIST_PLAYTIME, argb(255,148,148,148));
			SetNodeUsing("SAVEBUTTON" + (i + 1), false);
			SetNodeUsing("DELETEBUTTON" + (i + 1), false);
		}
	}
	if(bSave)
	{
		Picture_SetGroupPicture("SAVEFRAME_NEW", "SAVELOAD", "frame_newsave");
		if(bNewSave)
		{
			Picture_SetColor("SAVEFRAME_NEW", argb(255,128,128,128));
			StringCollection_ChangeColor("SAVELIST_INFO", g_SaveSlots * 3 + 1, argb(255,255,255,255));
			SetNodeUsing("SAVEBUTTON_NEW", true);
		}
		else
		{
			Picture_SetColor("SAVEFRAME_NEW", argb(255,70,70,70));
			StringCollection_ChangeColor("SAVELIST_INFO", g_SaveSlots * 3 + 1, argb(255,148,148,148));
			SetNodeUsing("SAVEBUTTON_NEW", false);
		}
	}
	string sInfo;
	if(bNewSave)
	{
		SetNodeUsing("SAVEIMG_BIG", false);
		sInfo = "#" + GetFullName(pchar);
		StringCollection_SetText("PROFILE_INFO", PROFILE_HERONAME, sInfo);
		sInfo = "#";
		switch(NullCharacter.HeroParam.HeroType)
		{
			case "HeroType_1":	sInfo += XI_ConvertString("Gymnast");		break;
			case "HeroType_2":	sInfo += XI_ConvertString("Accountant");	break;
			case "HeroType_3":	sInfo += XI_ConvertString("Athlete");		break;
			case "HeroType_4":	sInfo += XI_ConvertString("Shooter");		break;
		}
		StringCollection_SetText("PROFILE_INFO", PROFILE_HEROTYPE, sInfo);
		sInfo = "#" + XI_ConvertString("Difficulty") + ": " + (GetNormalizedDifficultyLevel() + 1);
		StringCollection_SetText("PROFILE_INFO", PROFILE_DIFFICULTY, sInfo);
		if(SandBoxMode)
			sInfo = "SandboxMode";
		else
			sInfo = "StoryMode";
		StringCollection_SetText("PROFILE_INFO", PROFILE_GAMEMODE, sInfo);
		Picture_SetGroupPicture("HERO_FACE", "face128_" + pchar.FaceId, "face");
		SetNodeUsing("FADER_LEFT", false);
		SetNodeUsing("FADER_RIGHT", false);
		SetNodeUsing("FADER_LONG", false);
		SetNodeUsing("ICON_MONEY", false);
		SetNodeUsing("SAVE_INFO", false);
		SetNodeUsing("SAVE_LOCATION", false);
		SetNodeUsing("SAVE_TAG", false);
		SetNodeUsing("OFFICERSPROFESSION", false);
		for(i = 1; i <= 9; i++)
		{
			SetNodeUsing("OFFICER_" + i, false);
		}
		return;
	}
	else
	{
		SetNodeUsing("SAVEIMG_BIG", true);
		SetNodeUsing("FADER_LEFT", true);
		SetNodeUsing("FADER_RIGHT", true);
		SetNodeUsing("FADER_LONG", true);
		SetNodeUsing("ICON_MONEY", true);
		SetNodeUsing("SAVE_INFO", true);
		SetNodeUsing("SAVE_LOCATION", true);
		SetNodeUsing("SAVE_TAG", true);
		SetNodeUsing("OFFICERSPROFESSION", true);
		for(i = 1; i <= 9; i++)
		{
			SetNodeUsing("OFFICER_" + i, true);
		}
	}
		
	// считываем скрин
	int iTexture;
	string sNode = "SAVEIMG" + (iSlot + 1);
	Picture_GetTexture(sNode, &iTexture);	
	// ставим скрин
	if(iTexture != -1)
		Picture_SetTexture("SAVEIMG_BIG", iTexture);
	// заполняем инфу
	ref saveInfo = &g_oSaveList[iSlot];
	if(CheckAttribute(saveInfo, "locname") && saveInfo.locname != "")
	{
		sInfo = "#" + saveInfo.locname;	// название сейва
		StringCollection_SetText("SAVE_INFO", SAVE_NAME, sInfo);
	}
	if(CheckAttribute(saveInfo, "location") && saveInfo.location != "")
	{
		sInfo = saveInfo.location;	// локация
		SetFormatedText("SAVE_LOCATION", sInfo);
		SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "SAVE_LOCATION", 5);
	}
	if(CheckAttribute(saveInfo, "timeStr") && saveInfo.timeStr != "")
	{
		sInfo = "#" + saveInfo.timeStr;	// игровое время
		StringCollection_SetText("SAVE_INFO", SAVE_GAMETIME, sInfo);
	}
	if(CheckAttribute(saveInfo, "rank") && saveInfo.rank != "")
	{
		sInfo = "#" + XI_ConvertString("Rank") + ": " + saveInfo.rank;	// ранг
		StringCollection_SetText("SAVE_INFO", SAVE_RANK, sInfo);
	}
	if(CheckAttribute(saveInfo, "SquadPower") && saveInfo.SquadPower != "")
	{
		sInfo = "#" + XI_ConvertString("SquadPower") + ": " + saveInfo.SquadPower;	// мощь эскадры
		StringCollection_SetText("SAVE_INFO", SAVE_SQUADPOWER, sInfo);
	}
	if(CheckAttribute(saveInfo, "money") && saveInfo.money != "")
	{
		sInfo = "#" + FindRussianMoneyString(sti(saveInfo.money));	// песо
		StringCollection_SetText("SAVE_INFO", SAVE_MONEY, sInfo);
	}
	if(CheckAttribute(saveInfo, "doubloons") && saveInfo.doubloons != "")
	{
		sInfo = "#" + FindRussianDublonString(sti(saveInfo.doubloons));	// дублоны
		StringCollection_SetText("SAVE_INFO", SAVE_DOUBLOONS, sInfo);
	}
	if(CheckAttribute(saveInfo, "SaveVer") && saveInfo.SaveVer != "")
	{
		sInfo = "#" + XI_ConvertString("GameVersion") + ": " + saveInfo.SaveVer;	// версия
		StringCollection_SetText("SAVE_INFO", SAVE_VERSION, sInfo);
		bBadSave = (sti(saveInfo.SaveVer) != VERSION_NUM_PRE);
	}
	else
		bBadSave = true;
	if(CheckAttribute(saveInfo, "questUniqueID") && CheckAttribute(saveInfo, "questID"))
	{
		string tag = "";
		string idQuest = saveInfo.questUniqueID;
	//	SetFormatedText("TEXTLOG", saveInfo.questID);
	//	SetFormatedText("TEXTLOG1", saveInfo.questUniqueID);
		if(CheckAttribute(saveInfo, "questUserData") && saveInfo.questUserData != "")
			pchar.QuestInfo.(idQuest).UserData = saveInfo.questUserData;
		SendMessage(&GameInterface, "lsse", MSG_INTERFACE_GET_QUEST_NAME, saveInfo.questID, saveInfo.questUniqueID, &tag);
		if(tag != "")
		{
			if(CheckAttribute(saveInfo, "questClosed") && sti(saveInfo.questClosed) == true)
				sInfo = XI_ConvertString("QuestCompleted") + " - ";
			else
				sInfo = XI_ConvertString("QuestActive") + " - ";
			sInfo += tag;	// дополнительный тег
			SetFormatedText("SAVE_TAG", sInfo);
		}
		else
			SetFormatedText("SAVE_TAG", "");
	}
	else
		SetFormatedText("SAVE_TAG", "");
	
	// инфа в шапке профиля
	if(CheckAttribute(saveInfo, "HeroName") && saveInfo.HeroName != "")
	{
		sInfo = "#" + saveInfo.HeroName;	// имя ГГ
		StringCollection_SetText("PROFILE_INFO", PROFILE_HERONAME, sInfo);
	}
	if(CheckAttribute(saveInfo, "HeroType") && saveInfo.HeroType != "")
	{
		sInfo = "#" + saveInfo.HeroType;	// тип ГГ
		StringCollection_SetText("PROFILE_INFO", PROFILE_HEROTYPE, sInfo);
	}
	if(CheckAttribute(saveInfo, "difficulty") && saveInfo.difficulty != "")
	{
		sInfo = "#" + XI_ConvertString("Difficulty") + ": " + saveInfo.difficulty;	// сложность
		StringCollection_SetText("PROFILE_INFO", PROFILE_DIFFICULTY, sInfo);
	}
	if(CheckAttribute(saveInfo, "GameMode") && saveInfo.GameMode != "")
	{
		sInfo = "#" + saveInfo.GameMode;	// режим игры
		StringCollection_SetText("PROFILE_INFO", PROFILE_GAMEMODE, sInfo);
	}
	if(CheckAttribute(saveInfo, "faceinfo"))
	{
		sInfo = saveInfo.faceinfo;
		ShowFaces(sInfo);	// портреты ГГ и офицеров
	}
	
}

void ShowFaces(string sData)
{
	string str = sData;
	string faceData;
	string sNode;
	for(int i = 0; i < 10; i++)
	{
		faceData = "";
		if(GetNextSubStr(str, &faceData, &str, ","))
		{
			if(faceData == "" || faceData == "*")
			{
				faceData = "face128_fighter";
				switch(i)
				{
					case 0:		faceData = "face128_captain";		break;
					case 4:		faceData = "face128_navigator";		break;
					case 5:		faceData = "face128_boatswain";		break;
					case 6:		faceData = "face128_cannoner";		break;
					case 7:		faceData = "face128_doctor";		break;
					case 8:		faceData = "face128_treasurer";		break;
					case 9:		faceData = "face128_carpenter";		break;
				}
			}
			if(i == 0)
				sNode = "HERO_FACE";
			else
				sNode = "OFFICER_" + i;
			Picture_SetGroupPicture(sNode, faceData, "face");
		}
	}
}

string GetCurSaveName()
{
	if(g_nCurrentSaveIndex < 0 || g_nCurrentSaveIndex >= g_nSaveQuantity)
		return "";
	string attr = "s" + g_nCurrentSaveIndex;
	if(CheckAttribute(&g_oSaveContainer, attr + ".savename"))
		return g_oSaveContainer.(attr).savename;
	return "";
}

void ProcessLoad()
{
	string sCurSave = GetCurSaveName();
	PlayerProfile.name = currentProfile;

	IDoExit(RC_INTERFACE_SAVELOAD_EXIT);
	ResetSound();

	SetEventHandler("evntLoad", "LoadGame", 1);
	PostEvent("evntLoad", 0, "s", "SAVE\" + PlayerProfile.name + "\" + sCurSave);
	Event("evntPreLoad");
}

void ProcessSave()
{
	if(g_nCurrentSaveIndex >= 0)
	{
		string curSave = GetCurSaveName();
		if(curSave != "")
			SendMessage(&GameInterface, "ls", MSG_INTERFACE_DELETE_SAVE_FILE, curSave);
	}
	string saveName = GameInterface.CUSTOM_SAVE_NAME.str;
	string sSaveDescriber = GetSaveDataString(saveName, "manual");
	SetEventHandler("evntSave", "SaveGame", 1);
	PostEvent("evntSave", 0, "ss", "SAVE\" + currentProfile + "\" + saveName, sSaveDescriber);
	object OptionsList;
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_LOADOPTIONS, "options", &OptionsList);
	OptionsList.StartGameParam.PlayerProfile  = PlayerProfile.name;
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_SAVEOPTIONS, "options", &OptionsList);
	bGameMenuStart = false;
	IDoExit(RC_INTERFACE_SAVELOAD_EXIT);
}

void ShowConfirmWindow(int iMode)
{
	g_sReturnWindow = "MAIN_WINDOW";
	if(XI_IsWindowEnable("PROFILE_WINDOW"))
		g_sReturnWindow = "PROFILE_WINDOW";
	XI_WindowDisable(g_sReturnWindow, true);
	XI_WindowDisable("CONFIRM_WINDOW", false);
	XI_WindowShow("CONFIRM_WINDOW", true);
	bool bOk = false;
	g_nConfirmMode = iMode;
	switch(iMode)
	{
		case CONFIRMMODE_PROFILE_DELETE:
			SetFormatedText("CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Delete profile confirm"));
		break;
		case CONFIRMMODE_SAVE_DELETE:
			SetFormatedText("CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Delete savefile confirm"));
		break;
		case CONFIRMMODE_SAVE_OVERWRITE:
			SetFormatedText("CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Overwrite savefile confirm"));
		break;
		case CONFIRMMODE_LOAD_GAME:
			if (bBadSave)
			{
				SetFormatedText("CONFIRM_TEXT", XI_ConvertString("BadSaveInfo"));
				bOk = true;
			}
			else
				SetFormatedText("CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Load game confirm"));
		break;
	}
	if(bOk)
	{
		SetNodeUsing("CONFIRM_YES", false);
		SetNodeUsing("CONFIRM_YES1", true);
		SetNodeUsing("CONFIRM_NO", false);
		SetCurrentNode("CONFIRM_YES1");
	}
	else
	{
		SetNodeUsing("CONFIRM_YES", true);
		SetNodeUsing("CONFIRM_YES1", false);
		SetNodeUsing("CONFIRM_NO", true);
		SetCurrentNode("CONFIRM_YES");
	}
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONFIRM_TEXT", 5); // центрируем по вертикали
}

void ProcessConfirm()
{
	int iCommand = GetEventData();
	string sNode = GetEventData();
	if(iCommand == ACTION_ACTIVATE || iCommand == ACTION_MOUSECLICK)
		DoConfirm(sNode == "CONFIRM_YES");
	else if(iCommand == ACTION_DEACTIVATE)
		DoConfirm(false);
}

void DoConfirm(bool bYes)
{
	XI_WindowDisable("CONFIRM_WINDOW", true);
	XI_WindowShow("CONFIRM_WINDOW", false);
	XI_WindowDisable(g_sReturnWindow, false);
	if(bYes)
	{
		switch(g_nConfirmMode)
		{
			case CONFIRMMODE_PROFILE_DELETE: 	ProcDeleteProfile(); 		break;
			case CONFIRMMODE_SAVE_DELETE: 		ProcessDeleteSaveFile(); 	break;
			case CONFIRMMODE_SAVE_OVERWRITE:	LaunchCustomSaveGame();		break;
			case CONFIRMMODE_LOAD_GAME: 		ProcessLoad(); 				break;
		}
	}
}

void ProcChooseProfileFromList()
{
	SetNodeUsing("BUTTON_1", false);
	SetNodeUsing("BUTTON_2", false);
	SetNodeUsing("BUTTON_3", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowDisable("PROFILE_WINDOW", false);
	XI_WindowShow("PROFILE_WINDOW", true);
	FillProfileListIntoTable();
	SetCurrentNode("PROFILE_WINDOW_LIST");
}

void FillProfileListIntoTable()
{
	int q, n;
	string src_attr, dst_attr, sCurProfile;
	q = sti(PlayerProfile.profilesQuantity);
	n = 1;
	if(CheckAttribute(&PlayerProfile,"name"))
		sCurProfile = PlayerProfile.name;
	else
		sCurProfile = "";
	DeleteAttribute(&GameInterface, "PROFILE_WINDOW_LIST");
	for(int i = 0; i < q; i++)
	{
		src_attr = "profile_" + i;
		dst_attr = "tr" + (i+1);
		GameInterface.PROFILE_WINDOW_LIST.(dst_attr).td1.str = PlayerProfile.(src_attr);
		if(PlayerProfile.(src_attr) == sCurProfile)
			n = i+1;
	}
	GameInterface.PROFILE_WINDOW_LIST.select = n;
	Table_UpdateWindow("PROFILE_WINDOW_LIST");
}

void ProcExitProfile()
{
	SetNodeUsing("BUTTON_1", true);
	SetNodeUsing("BUTTON_2", true);
	if(bGameProcess)
		SetNodeUsing("BUTTON_3", true);
	XI_WindowShow("PROFILE_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
}

void procProfileBtnAction()
{
	int iCommand = GetEventData();
	string sNode = GetEventData();
	if(iCommand == ACTION_ACTIVATE || iCommand == ACTION_MOUSECLICK)
	{
		if(sNode == "PROFILE_WINDOW_BTN_EXIT")
		{
			if(!bGameProcess && g_nSaveQuantity == 0)
			{
				SetCurrentProfile("");
				ProcExitProfile();
			}
			else
				ProcExitProfile();
		}
		else if(sNode == "PROFILE_WINDOW_BTN_CHOOSE")
			ProcChooseProfile();
		else if(sNode == "PROFILE_WINDOW_BTN_DELETE")
			ShowConfirmWindow(CONFIRMMODE_PROFILE_DELETE);
		return;
	}
	if(iCommand == ACTION_DEACTIVATE)
		ProcExitProfile();
}

void ProcChooseProfile()
{
	string attr = "profile_" + (sti(GameInterface.PROFILE_WINDOW_LIST.select) - 1);
	if(CheckAttribute(&PlayerProfile, attr))
		SetCurrentProfile(PlayerProfile.(attr));
	ProcExitProfile();
}

void ProcDeleteProfile()
{
	int selectProfile = sti(GameInterface.PROFILE_WINDOW_LIST.select) - 1;
	string attr = "profile_" + selectProfile;
	string sThisProfile = PlayerProfile.(attr);
	DeleteProfile(sThisProfile);

	int nProfilesQ = sti(PlayerProfile.profilesQuantity);
	nProfilesQ--;
	string attrSrc, attrDst;
	for(int iProfile = selectProfile; iProfile < nProfilesQ; iProfile++)
	{
		attrDst = "profile_" + iProfile;
		attrSrc = "profile_" + (iProfile + 1);
		PlayerProfile.(attrDst) = PlayerProfile.(attrSrc);
	}
	DeleteAttribute(&PlayerProfile, "profile_" + nProfilesQ);
	PlayerProfile.profilesQuantity = nProfilesQ;
	FillProfileListIntoTable();
	if(sThisProfile == currentProfile)
		SetCurrentProfile("");
}

void DeleteProfile(string sProfile)
{
	string oldpath = "";
	if(CheckAttribute(&GameInterface, "SavePath"))
		oldpath = GameInterface.SavePath;
	GameInterface.SavePath = "SAVE\" + sProfile;
	int nSaveNum = 0;
	string saveName;
	int nSaveSize;
	while(SendMessage(&GameInterface, "llee", MSG_INTERFACE_SAVE_FILE_FIND, nSaveNum, &saveName, &nSaveSize) != 0)
	{
		nSaveNum++;
		SendMessage(&GameInterface, "ls", MSG_INTERFACE_DELETE_SAVE_FILE, saveName);
	}
	XI_DeleteFolder(GameInterface.SavePath);
	GameInterface.SavePath = oldpath;
}

void ProcessDeleteSaveFile()
{
	string curSave = GetCurSaveName();
	if(curSave == "")
		return;
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_DELETE_SAVE_FILE,curSave);

	int nDst, nSrc;
	string attrDst, attrSrc;
	aref arSrc, arDst;
	g_nSaveQuantity--;
	for(int i = g_nCurrentSaveIndex; i <= g_nSaveQuantity; i++)
	{
		attrDst = "s" + i;
		makearef(arDst, g_oSaveContainer.(attrDst));
		if(i < g_nSaveQuantity)
		{
			attrSrc = "s" + (i + 1);
			makearef(arSrc, g_oSaveContainer.(attrSrc));
			CopyAttributes(arDst, arSrc);
		}
		else
			DeleteAttribute(&g_oSaveContainer, attrDst);
	}
	ResetSlots();
	if(g_nFirstSaveIndex + g_SaveSlots >= g_nSaveQuantity)
		FillSaveList(g_nFirstSaveIndex - 1);
	else
		FillSaveList(g_nFirstSaveIndex);
}

void LaunchCustomSaveGame()
{
	string curLocName = GetCurLocationName();
	string saveName;
	saveName = GetClampedSaveName(curLocName, 0);
	int idx = 0;
	while(SendMessage(&GameInterface, "ls", MSG_INTERFACE_NEW_SAVE_FILE_NAME, saveName) == 1)
	{
		saveName = GetClampedSaveName(curLocName, idx + 1);
		idx++;
	}

	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowDisable("CUSTOM_SAVE_WINDOW", false);
	XI_WindowShow("CUSTOM_SAVE_WINDOW", true);    

	GameInterface.CUSTOM_SAVE_NAME.str = saveName;
	if(GetCurSaveName() != "" && !HasSubStr(GetCurSaveName(), "QuickSave"))
		GameInterface.CUSTOM_SAVE_NAME.str = GetCurSaveName();
	SetFormatedText("CUSTOM_SAVE_MSG", XI_ConvertString("SaveName"));
}

void ExitSaveCustomGame()
{
	XI_WindowShow( "CUSTOM_SAVE_WINDOW", false );
	XI_WindowDisable( "MAIN_WINDOW", false );
}

void ProcessCustomSaveAction()
{
	int iCommand = GetEventData();
	string sNode = GetEventData();
	
	if(iCommand == ACTION_ACTIVATE || iCommand == ACTION_MOUSECLICK)
	{
		if(sNode == "CUSTOM_SAVE_BTN_OK")
            ProcessSave();
		else if(sNode == "CUSTOM_SAVE_BTN_CANCEL")
			ExitSaveCustomGame();
	}
	if(iCommand == ACTION_DEACTIVATE)
		ExitSaveCustomGame();
}