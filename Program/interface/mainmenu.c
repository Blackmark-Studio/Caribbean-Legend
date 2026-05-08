#define NEWS_INI_PATH "Resource\INI\texts\news.ini"
#include "interface\utils\items\stats.c"
#include "interface\utils\items\descriptors.c"
#include "interface\utils\popup_error.c"
// Sith,mitrokosta,ugeen для LE
// Главное меню учитывает прогресс в игре
string isUsersName="";

bool DLCState;
int	 DLCCount; 	
int	 DLCAppID = 0; 
bool bFire = false;
int iChar;
string title, descr;
object rewardsInfo;
ref currentReward = nullptr;

void InitInterface(string iniName)
{
	Event("DoInfoShower","sl","MainMenuLaunch",false);

	aref arScrShoter;
	if( !GetEntity(&arScrShoter,"scrshoter") ) 
	{
		CreateScreenShoter();
	}
	
	if(bSteamAchievements || GetSteamEnabled())
	{
		DLCAppID = CheckUpdates();	
	}
	else
	{ 
		DLCAppID = 0;
	}

	CreateBackEnvironment();
	
	if(!CheckAttribute(&InterfaceStates, "MainMenu.DoNotClearCharacters"))
	{
		MainMenu_CreateLocation();
		if(!CheckAttribute(&InterfaceStates,"Death"))MainMenu_CreateCharacters();
	}
	else
	{
		DeleteAttribute(&InterfaceStates, "MainMenu.DoNotClearCharacters");
	}
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	string Version = VERSION_NUMBER1 + GetVerNum();
	string Copyright = " BlackMark Studio - 2026 ";
	
	SetFormatedText("VERSION_TEXT", Version);
	SetFormatedText("COPYRIGHT_TEXT", Copyright);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);	

	SetEventHandler("evntSteamOverlayActivated","UpdateInterface",0);
	
	SetEventHandler("ConfirmExitClick","ConfirmExitClick",0);
	SetEventHandler("ConfirmExitCancel","ConfirmExitCancel",0);
	SetEventHandler("NewsCancel","NewsCancel",0);
	SetEventHandler("AttentionCancel","AttentionCancel",0);
	SetEventHandler("CuratorCheckResult","MM_ProcessCuratorCheckResult",0);
	SetEventHandler("ShowInfoWindow", "ShowHelpHint", 0);
	SetEventHandler("HideInfoWindow", "HideHelpHint", 0);
	SetEventHandler("MM_ShowReward", "MM_ShowReward", 0);

	GameInterface.SavePath = "SAVE";

	// логотип
	SetMenuLogo();

	// кнопка "продолжить игру" --->
	string saveName = GetLastSavePathFromCurrentProfile();
	string saveData;
	if(saveName != "") SendMessage(&GameInterface,"lse",MSG_INTERFACE_GET_SAVE_DATA,saveName,&saveData);
	if(saveName == "" || saveData == "") SetSelectable("RESUME_GAME", false); // нет сохранений
	else 
	{
		if(!HasSubStr(saveData, "SaveVer="+VERSION_NUM_PRE)) SetSelectable("RESUME_GAME", false);
		else SetSelectable("RESUME_GAME", true);
	}
	// <---
	
	// кнопка "новая игра" --->
	SetNodeUsing("NEW_GAME_INFO", false); // предупреждение НИ
	if(CheckAttribute(pchar,"mainmenu")) 
	{
		// SetSelectable("NEW_GAME", false); // блок кнопки НИ после выхода в меню
		SetNodeUsing("NEW_GAME", false); // блок кнопки НИ после выхода в меню
		SetNodeUsing("NEW_GAME_INFO", true); // предупреждение НИ
	}
	// <---

	if(bSteamAchievements && GetSteamEnabled())
	{
			DLCAppID = CheckUpdates();	
			if(DLCAppID > 0) // есть обновления
			{
				SetSelectable("UPDATES", true);
				SetNodeUsing("A_UPDATES", true);
			}
			else
			{	// обновлений нет
				SetSelectable("UPDATES", false);
				SetNodeUsing("A_UPDATES", false);
			}
	}
	else
	{ // обновлений нет
		SetSelectable("UPDATES", false);
		SetNodeUsing("A_UPDATES", false);
	}
	
	if(!CheckNews()) ShowNews(); // есть новости

    // при выходе в главное меню сбрасываем звуки
	if(!bMainMenu)
    {
        PauseAllSounds();
        ResetSound(); 
    }

	// запуск титров после прохождения игры
	if(CheckAttribute(&InterfaceStates, "MainMenu.InstantCredits"))
    {
		DeleteAttribute(&InterfaceStates, "MainMenu.InstantCredits");
		InterfaceStates.MainMenu.DoNotClearCharacters = true;
		IDoExit(RC_INTERFACE_DO_CREDITS, false);
		bMainMenu = true;
        return;
	}

	// belamour ачивка за установленный мод
	object itemsInfo[2];
	if(!GetAchievement("ach_CL_153") && GetOverlaysInfo(&itemsInfo) > 0) Achievment_Set("ach_CL_153");

	// ВВОД СВОИХ СХЕМ В ЗАВИСИМОСТИ ОТ ПОГОДЫ (BY LOKK)
	if(Whr_IsRain())
	{ 
		if(Whr_IsNight())
		{
            if (!CheckScheme("mainmenu_night_rain"))
                UpdateSoundScheme("mainmenu_night_rain", true);
		}
		else
		{
            if (!CheckScheme("mainmenu_day_rain"))
                UpdateSoundScheme("mainmenu_day_rain", true);
		}
    }
	else
	{ 
		if(Whr_IsNight())
		{
            if (!CheckScheme("mainmenu_night"))
                UpdateSoundScheme("mainmenu_night", true);
		}
		else
		{
            if (!CheckScheme("mainmenu_day"))
                UpdateSoundScheme("mainmenu_day", true);
		}
	}

	SetMusic("music_MainMenu");

	// if("Условие") // условие на появление окна с предупреждением
		// ShowAttention();

	// Награды за франшизу
	MM_InitFranchiseRewards();
}

void MM_InitFranchiseRewards()
{
	if (!CheckAttribute(&rewardsInfo, "mushket_indian"))
	{
		rewardsInfo.mushket_indian = BIsSubscribedApp(3549020);
		SetNewGroupPicture("REWARD_ITEM_1","ITEMS_42", "itm6");
		SetNodeUsing("REWARD_AVAILABLE_1", rewardsInfo.mushket_indian == "1");
	}

	if (!CheckAttribute(&rewardsInfo, "legendGuide"))
	{
		SetNewGroupPicture("REWARD_ITEM_2","ITEMS_42", "itm5");
		SetNodeUsing("REWARD_AVAILABLE_2", false);
		int status = GetSteamEnabled() ? BeginCuratorCheckAsync("45734318", 10) : -1;
		if (status == 0) Log_Info("Error while checking your Steam subscription. Please try restarting the game");
	}

	SetNewGroupPicture("REWARD_ITEM_3","ITEMS_EMPTY", "empty");
	Picture_SetColor("REWARD_ITEM_3", argb(220,50,50,50));
	SetNewGroupPicture("REWARD_ITEM_4","ITEMS_EMPTY", "empty");
	Picture_SetColor("REWARD_ITEM_4", argb(220,50,50,50));
	SetNewGroupPicture("REWARD_ITEM_5","ITEMS_EMPTY", "empty");
	Picture_SetColor("REWARD_ITEM_5", argb(220,50,50,50));
}

void MM_ShowReward()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	ref item = nullptr;
	switch (nodName)
	{
		case "REWARD_ITEM_1": item = ItemsFromID("mushket_indian"); break;
		case "REWARD_ITEM_2": item = ItemsFromID("legendGuide"); break;
		case "REWARD_CLOSE_BUTTON": 
		{
			MM_HideReward();
			return;
		}
		break;
	}

	if (item == nullptr) MM_ShowEmptyReward();
	else MM_ShowRewardItem(item);
}

void MM_ShowEmptyReward()
{
	ShowError(GetConvertStr("noRewardYetMessage", "franchiseRewards.txt"));
	XI_WindowDisable("REWARD_WINDOW", true);
	XI_WindowShow("REWARD_WINDOW", false);
}

void MM_ShowRewardItem(ref item, bool forceShow = false)
{
	SetFormatedText("REWARD_CONDITIONS", GetConvertStr("condition_" + item.id, "franchiseRewards.txt"));
	if (MM_ToggleReward(currentReward != item || forceShow)) return;

	currentReward = item;
	SetNewGroupPicture("REWARD_PICTURE", item.picTexture, "itm" + item.picIndex);
	SetFormatedText("REWARD_NAME", GetItemName(item));
	SetFormatedText("REWARD_DESCRIPTION", GetItemDescr(item));
	FillUpDescriptors(item, !XI_IsWindowEnable("REWARD_WINDOW"));
	FillUpStats(item, &NullCharacter);

	string steamButtonText = GetConvertStr("steamButtonGet", "franchiseRewards.txt");
	bool alreadyGot = CheckAttributeEqualTo(&rewardsInfo, item.id, "1");
	SetSelectable("GET_REWARD_BUTTON", !alreadyGot);
	if (alreadyGot) steamButtonText = GetConvertStr("steamButtonAlreadyGot", "franchiseRewards.txt");
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"GET_REWARD_BUTTON",0, "#"+steamButtonText);
}

bool MM_ToggleReward(bool forceShow = false)
{
	bool isShowed = XI_IsWindowEnable("REWARD_WINDOW");
	if (forceShow) isShowed = false;

	if (!isShowed) MM_InitFranchiseRewards();
	XI_WindowDisable("REWARD_WINDOW", isShowed);
	XI_WindowShow("REWARD_WINDOW", !isShowed);
	SetCurrentNode("REWARD_DESCRIPTION");
	return isShowed;
}

void MM_HideReward()
{
	XI_WindowDisable("REWARD_WINDOW", true);
	XI_WindowShow("REWARD_WINDOW", false);
}

void ShowHelpHint()
{
	string sCurrentNode = GetEventData();
	string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";
	SetDescriptorsTooltip(sCurrentNode, &sHeader, &sText1, &sText2, &sText3, currentReward);
	SetItemStatsTooltip(nullptr, sCurrentNode, &sHeader, &sText1, &sText2, &sText3, currentReward);

	if (sHeader != "") CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, 64, 64, false, false);
}

void MM_ProcessCuratorCheckResult()
{
	string sResult = GetEventData();
	if (sResult == "success")
	{
		rewardsInfo.legendGuide = true;
		if (currentReward != nullptr && currentReward.id == "legendGuide")
		{
			SetSelectable("GET_REWARD_BUTTON", false);
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"GET_REWARD_BUTTON",0, "#"+GetConvertStr("steamButtonAlreadyGot", "franchiseRewards.txt"));
		}
		SetNodeUsing("REWARD_AVAILABLE_2", true);
		return;
	}

	SetNodeUsing("REWARD_AVAILABLE_2", false);
	if (sResult == "notsubscribedfailure")
	{
		Trace("ProcessCuratorCheckResult: NotSubscribedFailure! ;-(");
	}
	else
	{
		Trace("ProcessCuratorCheckResult: Unknown sResult=" + sResult);
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "RESUME_GAME":
			if(comName == "click" || comName == "activate"){
				LoadLastSave();
			}
		break;

		case "NEW_GAME":
			if(comName == "click" || comName == "activate"){
				IDoExit( RC_INTERFACE_DO_NEW_GAME, false );
				bMainMenu = true;
			}
		break;		

		case "LOAD_GAME":
			if(comName == "click" || comName == "activate"){
				IDoExit( RC_INTERFACE_DO_LOAD_GAME, false );
				bMainMenu = true;
			}
		break;

		case "OPTIONS":
			if(comName == "click" || comName == "activate"){
				IDoExit( RC_INTERFACE_DO_OPTIONS, false );
				bMainMenu = true;
			}
		break;
		
		case "CREDITS":
			if(comName == "click" || comName == "activate"){
				InterfaceStates.MainMenu.DoNotClearCharacters = true;
				IDoExit( RC_INTERFACE_DO_CREDITS, false );
				bMainMenu = true;
			}
		break;

		case "QUIT":
			if(comName == "click" || comName == "activate"){
				XI_WindowDisable("MAIN_WINDOW",true);
				XI_WindowDisable("CONFIRM_EXIT_WINDOW",false);
				XI_WindowDisable("REWARD_WINDOW", true);
				XI_WindowShow("REWARD_WINDOW", false);
				XI_WindowShow("CONFIRM_EXIT_WINDOW", true);
				SetCurrentNode("CONFIRM_EXIT_NO");
			}
			if(comName == "downstep"){
				if(DLCAppID > 0 && bSteamAchievements && GetSteamEnabled()) 
					SetCurrentNode("UPDATES");
				else
					SetCurrentNode("NEWS");
			}			
		break;

		case "UPDATES":
			if(comName == "click" || comName == "activate"){
				if(DLCAppID > 0 && bSteamAchievements && GetSteamEnabled())
					DLCState = DLCStartOverlay(MAIN_APPID); // открываем окошко в стиме для главной игры а не для дополнения
			}
		break;

		case "NEWS":
			if(comName == "click" || comName == "activate"){
				ShowNews();
			}
			if(comName == "upstep"){
				if(DLCAppID > 0 && bSteamAchievements && GetSteamEnabled()) 
					SetCurrentNode("UPDATES");
				else
					SetCurrentNode("QUIT");
			}			
		break;

		case "WORKSHOP":
			if(comName == "click" || comName == "activate"){
				if(GetSteamEnabled())
					GameOverlayToWebPage("https://steamcommunity.com/app/2230980/workshop/");
			}
		break;

		case "B_MORE":
			if(comName == "click" || comName == "activate"){
				if(GetSteamEnabled())
					GameOverlayToWebPage("https://steamcommunity.com/app/2230980/allnews/");
			}
		break;

		case "GET_REWARD_BUTTON":
			if (!GetSteamEnabled()) break;
			if (comName != "click" && comName != "activate") break;
		
			string url;
			if (currentReward.id == "mushket_indian") url = "https://store.steampowered.com/app/3549020/Caribbean_Legend_Age_of_Pirates/";
			else if (currentReward.id == "legendGuide") url = "https://store.steampowered.com/franchise/caribbeanlegend";
			GameOverlayToWebPage(url);
		break;
	}

	if (comName == "deactivate") MM_HideReward();
}

void ShowNews()
{
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowShow("NEWS_WINDOW", true);
	XI_WindowDisable("NEWS_WINDOW",false);
	XI_WindowDisable("REWARD_WINDOW", true);
	XI_WindowShow("REWARD_WINDOW", false);
	SetCurrentNode("NEWS_TEXT");
	title = GetConvertStr("News", "News.txt");
	descr = GetConvertStr("News" + "_descr", "News.txt");
	SetFormatedText("NEWS_TITLE", title);
	SetFormatedText("NEWS_TEXT", descr);
	int nStrings = GetNumberOfStringsInFormatedText("NEWS_TEXT", descr); // считаем сколько строк в форме
	// Log_TestInfo("Всего строк " + nStrings);
	if(nStrings <18)// Запрет на скроллинг
	{
		SetNodeUsing("NEWS_SCROLL_TEXT",false);
		SendMessage( &GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"NEWS_TEXT", 13, 1 ); //1 - запрет, 0 - нет
	}
	SendMessage(&GameInterface, "lssss", MSG_INTERFACE_SAVE_STRINGS_TO_FILE, NEWS_INI_PATH, "News", "key", GetNewsKey());
}

void NewsCancel()
{
    XI_WindowDisable("NEWS_WINDOW",true);
	XI_WindowShow("NEWS_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
	SetCurrentNode("NEWS");
}

void ShowAttention()
{
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowShow("ATTENTION_WINDOW", true);
	XI_WindowDisable("ATTENTION_WINDOW",false);
	XI_WindowDisable("REWARD_WINDOW", true);
	XI_WindowShow("REWARD_WINDOW", false);
	descr = GetConvertStr("News" + "_Attention", "News.txt");
	SetFormatedText("ATTENTION_TEXT", descr);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"ATTENTION_TEXT",5);
	SetCurrentNode("ATTENTION_OK");
}

void AttentionCancel()
{
    XI_WindowDisable("ATTENTION_WINDOW",true);
	XI_WindowShow("ATTENTION_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
}

void LoadLastSave()
{    
    SetEventHandler("evntLoad","LoadGame",0);
    PostEvent("evntLoad",0,"s", GetLastSavePathFromCurrentProfile());
    IDoExit(-1, false);
	DeleteAttribute(pchar, "mainmenu"); // чистим атрибут если до этого вышли в меню									   
}

void ConfirmExitClick()
{
    DeleteBackEnvironment();
	EngineLayersOffOn(false);
    if(CheckAttribute(&InterfaceStates,"Death"))
    {
        DeleteAttribute(&InterfaceStates,"Death");
    }
	IDoExit(-1, false); 	 
	ExitProgram();
}

void ConfirmExitCancel()
{
    XI_WindowDisable("CONFIRM_EXIT_WINDOW",true);
	XI_WindowShow("CONFIRM_EXIT_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
	SetCurrentNode("QUIT");
}

void IDoExit(int exitCode, bool bClear)
{
	trace("IDoExit : exitCode = " + exitCode);											  
	bMainMenu = false; 
	InterfaceStates.BackEnvironmentIsCreated = true;
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	
	DelEventHandler("evntSteamOverlayActivated","UpdateInterface");
	
	DelEventHandler("ConfirmExitClick","ConfirmExitClick");
	DelEventHandler("ConfirmExitCancel","ConfirmExitCancel");
	DelEventHandler("NewsCancel","NewsCancel");
	DelEventHandler("AttentionCancel","AttentionCancel");
	DelEventHandler("CuratorCheckResult","MM_ProcessCuratorCheckResult");
	DelEventHandler("ShowInfoWindow", "ShowHelpHint");
	DelEventHandler("HideInfoWindow", "ShowHelpHint");
	DelEventHandler("MM_ShowReward", "MM_ShowReward");
	
	if(!CheckAttribute(&InterfaceStates, "MainMenu.DoNotClearCharacters"))
	{
		MainMenu_DeleteCharacters();
		MainMenu_DeleteLocation();
	}
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(bClear);
}

void HideHelpHint()
{
	CloseTooltipNew();
}

void ExitCancel()
{
	IDoExit(-1,true);
}

void CreateBackEnvironment()
{
	LayerFreeze(EXECUTE,false);
	LayerFreeze(REALIZE,false); 	

    bMainMenu = true;

    if( CheckAttribute(&InterfaceStates,"BackEnvironmentIsCreated") && InterfaceStates.BackEnvironmentIsCreated == "1" ) 
	{
        trace("BackEnvironmentIsCreated !");
		return;
	}

	// сбрасываем цвет фона на 0
	Render.BackColor = 0;
	// выключаем эффект моря
	Render.SeaEffect = false;
	// 14.07.2007 - отключаем подводную часть
	Sea.UnderWater = false;
	bMainCharacterInFire = false;

	// create weather
	ICreateWeather();

	CreateEntity(&InterfaceBackScene,"InterfaceBackScene");
	LayerAddObject(EXECUTE, &InterfaceBackScene, -1);
	LayerAddObject(REALIZE, &InterfaceBackScene, 1000);

    if(CheckAttribute(&InterfaceStates,"Death"))
    {    
        SendMessage(&InterfaceBackScene, "ls", 0, "MainMenu\MainMenu_death"); // set model
    }
    else
    {
        SendMessage(&InterfaceBackScene, "ls", 0, "MainMenu\MainMenu"); // set model

    }
	SendMessage(&InterfaceBackScene, "ls", 1, "camera"); // set camera

    trace("mainmenu CreateShip 0");
	// create ship
	MainMenu_CreateShip();
    trace("mainmenu CreateShip 1");
	MainMenu_CreateAnimals();
	MainMenu_CreateTreasure();
	MainMenu_CreatePalmTrees();	
}

void DeleteBackEnvironment()
{
    trace("DeleteBackEnvironment()");
    InterfaceStates.BackEnvironmentIsCreated = false;

    LayerDelObject(EXECUTE, &InterfaceBackScene);
    LayerDelObject(REALIZE, &InterfaceBackScene);
        
    if(isEntity(&InterfaceBackScene))
    {
        DeleteClass(&InterfaceBackScene);
    }	
}

void MainMenu_CreateShip()
{
	object currentShip = GetCurrentShipFromCurrentProfile();
	if(!CheckAttribute(&currentShip, "name") || !CheckAttribute(&currentShip, "flag")) return;
	
	int shipIndex = FindFirstEmptyShip();
	ref realShip = GetRealShip(shipIndex);
	CopyAttributes(realShip, &currentShip);
	realShip.index = shipIndex;
	
	//int
	iChar = GenerateCharacter(sti(currentShip.flag), WITHOUT_SHIP, "citizen", MAN, 0, WARRIOR);   //PIRATE
	characters[iChar].id = "menuCharacter";
	ref	rCharacter = &characters[iChar];
	LAi_SetImmortal(rCharacter, true);

	// защита от несуществующих моделей кораблей, грузим лодку
	string shipModel = "ships\" + currentShip.name + "\" + currentShip.name;
	if(!ModelExists(shipModel)) rCharacter.ship.type = GenerateShip(SHIP_BOAT, false);
	else rCharacter.ship.type = shipIndex;

	realShip.SpeedRate = 5.0; // чтоб не летал
	Ship_SetFantomData( rCharacter );
	Ship_ClearImpulseStrength( rCharacter );
	Ship_SetLightsAndFlares( rCharacter );
	Ship_SetTrackSettings( rCharacter );

	rCharacter.Features.GeraldSails = true;
	rCharacter.Ship.Speed.z = 5.0;
	rCharacter.Ship.Stopped = false;
	rCharacter.Ship.Pos.Mode = SHIP_SAIL;
	if(CheckAttribute(&InterfaceStates,"Death"))
    {    
		rCharacter.Ship.Pos.x = -105.0;
        rCharacter.Ship.Pos.z = -6.0;
        rCharacter.Ship.Ang.y = 350.0;
    }
    else
    {
        rCharacter.Ship.Stopped = true;
		rCharacter.Features.GeraldSails = false;
		rCharacter.Ship.Pos.x = -90.0;
        rCharacter.Ship.Pos.z = 25.0;
        rCharacter.Ship.Ang.y = 0.0;
    }
    trace("Ship.Pos.x = " + rCharacter.Ship.Pos.x + " Ship.Pos.z = " + rCharacter.Ship.Pos.z);										  
	rCharacter.Ship.Strand = false;
	rCharacter.Ship.Strand.SndID = -1;
	
	rCharacter.Ship.LastBallCharacter = -1;
	rCharacter.Ship.WindDotShip = 1.0;
	
	rCharacter.TmpPerks = "";
	aref aTmpPerks; makearef(aTmpPerks, rCharacter.TmpPerks);
	
	SendMessage(&InterfaceBackScene, "lsa", 2, "ship", &rCharacter); // set ship position
	CreateEntity(rCharacter, "ship");
	ref rBaseShip = GetRealShip(sti(rCharacter.ship.type));
	SendMessage(rCharacter, "laa", MSG_SHIP_CREATE, &rCharacter, &rBaseShip);
}

void MainMenu_CreateLocation() {
	ref loc = &locations[FindLocation("MainMenu")];
	CreateEntity(loc, "location");

	SendMessage(loc, "ls", MSG_LOCATION_MODELSPATH, "MainMenu");
	SendMessage(loc, "lssll", MSG_LOCATION_ADD_MODEL, "MainMenu_locators", "", 10, false);
	SendMessage(loc, "ls", MSG_LOCATION_SET_CHRS_PATCH, "MainMenu_patch");
	SendMessage(loc, "l", MSG_LOCATION_UPDATELOCATORS);
}

void MainMenu_DeleteCharacters() {
	if(GetCharacterIndex("MenuChar_mc") >= 0) {
		sld = CharacterFromID("MenuChar_mc");
		sld.lifeday = 0;
		sld.location = "none";
	}
	
	for (int i = 1; i <= 3; i++) {
		string attrName = "off" + i;
		
		if(GetCharacterIndex("MenuChar_" + attrName) >= 0) {
			sld = CharacterFromID("MenuChar_" + attrName);
			sld.lifeday = 0;
			sld.location = "none";
		}
	}
}

// обязательно удалять после выхода!!!
void MainMenu_DeleteLocation() {
	LocAi_Release();
	DeleteClass(&locations[FindLocation("MainMenu")]);
}

void MainMenu_CreateCharacters() {
	object chars = GetCurrentCharactersFromCurrentProfile();
	aref character;
	int index;
	
	// if(CheckAttribute(&chars, "gf")) // если девушка у ГГ есть, выставляем двоих
	if(CheckAttribute(&chars, "gf") && !CheckAttribute(pchar,"mainmenu")) // если девушка у ГГ есть, выставляем двоих + временный фикс выхода в меню
	{
		makearef(character, chars.gf);
		string gfId = character.id;
		if(GetCharacterIndex("MenuChar_gf") < 0) {
			sld = GetCharacter(NPC_GenerateCharacter("TmpChar", "none", "man", "man", 1, PIRATE, 0, false, "citizen"));
		} else {
			sld = CharacterFromID("MenuChar_gf");
		}
		
		index = sti(sld.index);
		//CopyAttributes(sld, character);
		CopyCharacterAppearance(sld, character);
		sld.id = "MenuChar_gf";
		sld.index = index;
		// sld.model.animation = "main_menu_gf";
		sld.model.animation = "main_menu_" + gfId; // main_menu_mary или main_menu_helena
		sld.model.entity = "NPCharacter";
		sld.location = "MainMenu";
		sld.location.group = "locators";
		// sld.location.locator = "girl"; // локатор девушки
		sld.location.locator = "girl_" + gfId; // локатор _mary или _helena
		LAi_SetStayType(sld);
		if(CheckAttribute(&chars, "mc")) // выставляем ГГ
		{
			makearef(character, chars.mc);
			
			if(GetCharacterIndex("MenuChar_mc") < 0) {
				sld = GetCharacter(NPC_GenerateCharacter("TmpChar", "none", "man", "man", 1, PIRATE, 0, false, "citizen"));
			} else {
				sld = CharacterFromID("MenuChar_mc");
			}
			
			index = sti(sld.index);
			//CopyAttributes(sld, character);
			CopyCharacterAppearance(sld, character);
			sld.id = "MenuChar_mc";
			sld.index = index;
			sld.model.animation = "main_menu_mc_" + gfId; // // main_menu_mc_mary или main_menu_mc_helena
			sld.model.entity = "NPCharacter";
			sld.location = "MainMenu";
			sld.location.group = "locators";
			sld.location.locator = "char2"; // локатор ГГ
			LAi_SetStayType(sld);
		}
	}
	else // если девушки у ГГ нет, выставляем только ГГ
	{
		if(CheckAttribute(&chars, "mc")) 
		{
			makearef(character, chars.mc);
			
			if(GetCharacterIndex("MenuChar_mc") < 0) {
				sld = GetCharacter(NPC_GenerateCharacter("TmpChar", "none", "man", "man", 1, PIRATE, 0, false, "citizen"));
			} else {
				sld = CharacterFromID("MenuChar_mc");
			}
			
			index = sti(sld.index);
			//CopyAttributes(sld, character);
			CopyCharacterAppearance(sld, character);
			sld.id = "MenuChar_mc";
			sld.index = index;
			sld.model.animation = "main_menu_mc"; // анимация для одного ГГ
			if(CheckAttribute(sld,"model") && sld.model == "rumba") sld.model.animation = "main_menu_mc_rumba";
			if(CheckAttribute(sld,"model") && sld.model == "Kneepel") sld.model.animation = " main_menu_mc_man_b";
			sld.model.entity = "NPCharacter";
			sld.location = "MainMenu";
			sld.location.group = "locators";
			sld.location.locator = "char"; // локатор ГГ
			LAi_SetStayType(sld);
		}
	}
	
	for (int i = 1; i <= 3; i++) { // оффы у костра
		string attrName = "off" + i;
		if(!CheckAttribute(&chars, attrName)) {
			continue;
		}
		bFire = true;
		makearef(character, chars.(attrName));
		
		if(GetCharacterIndex("MenuChar_" + attrName) < 0) {
			sld = GetCharacter(NPC_GenerateCharacter("TmpChar", "none", "man", "man", 1, PIRATE, 0, false, "citizen"));
		} else {
			sld = CharacterFromID("MenuChar_" + attrName);
		}
		
		index = sti(sld.index);
		//CopyAttributes(sld, character);
		CopyCharacterAppearance(sld, character);
		sld.id = "MenuChar_" + attrName;
		sld.index = index;
		sld.location = "MainMenu";
		sld.location.group = "locators";
		sld.location.locator = attrName;
		LAi_SetGroundSitType(sld);
	}
	
	LoginCharactersInLocation(&locations[FindLocation("MainMenu")]);
	// правка наложения локаторов
	if(CheckAttribute(&chars, "mc" ) && CheckAttribute(&chars, "gf")) {
		aref locator;
		makearef(locator, locations[FindLocation("MainMenu")].locators.locators.char2);
		sld = CharacterFromID("MenuChar_mc");
		TeleportCharacterToPos(sld, stf(locator.x), stf(locator.y), stf(locator.z));// перемещаем принудительно ГГ на нужный локатор
	}
	
	if(bFire && Whr_IsNight()) MainMenu_CreateFire(); // костер с появлением персонажей
}

void MainMenu_CreateAnimals()
{
	InterfaceBackScene.seagull.locator = "seagull";
	InterfaceBackScene.seagull.model = "mainmenu\seagull";
	InterfaceBackScene.seagull.animation = "seagull";
	InterfaceBackScene.seagull.aniaction = "idle";
	SendMessage(&InterfaceBackScene, "ls", 9, "seagull" );
	CreateEntity(&Animals, "Animals");
	SendMessage(Animals, "l", MSG_ANIMALS_SEAGULLS_SHOW);
}

void MainMenu_DeleteAnimals()
{
	if(IsEntity(&Animals)) DeleteClass(Animals);
}

void MainMenu_CreateFire()
{
	InterfaceBackScene.fire.locator = "fire";
	InterfaceBackScene.fire.model = "mainmenu\bfire";
	SendMessage(&InterfaceBackScene, "ls", 9, "fire" );	

	ref rLoc = &locations[FindLocation("MainMenu")];
	string sGroup = "locators";
	string sLocator = "fire";
	
	float x = stf(rLoc.locators.(sGroup).(sLocator).x);
	float y = stf(rLoc.locators.(sGroup).(sLocator).y);
	float z = stf(rLoc.locators.(sGroup).(sLocator).z);

	CreateParticleSystemX("Fire", x, y+0.15, z, x, y+0.15, z, 0); // Огонь
	CreateParticleSystemX("Fire", x, y+0.3, z, x, y+0.3, z, 0); // Для пущей красоты создаем два партикла
	CreateParticleSystemX("smoke_light", x, y+1.15, z, x, y+1.15, z, 0); // Дым
	
	LocationSetLights(rLoc);
}

void MainMenu_CreateTreasure()
{
	int currentMoney = GetCurrentMoneyFromCurrentProfile();
	if(CheckAttribute(&InterfaceStates,"Death")) return;
	if(currentMoney < 5000000) return; // проверка текущего состояния у гг
    // фонарь на сокровищах
	if( Whr_IsNight() ) 
	{
		InterfaceBackScene.light.turnon = true;
		InterfaceBackScene.light.model = "mainmenu\Treasure_fonar";
		InterfaceBackScene.light.lightcolormin = argb(0,200,200,120);//argb(255,114,114,80);
		InterfaceBackScene.light.lightcolormax = argb(48,255,255,180);
		InterfaceBackScene.light.colorperiod = 0.5;
		InterfaceBackScene.light.addcolorperiod = 2.0;
		InterfaceBackScene.light.rangemin = 10.0;
		InterfaceBackScene.light.rangemax = 14.0;
		InterfaceBackScene.light.rangeperiod = 1.5;
		InterfaceBackScene.light.locator = "treasure";
		InterfaceBackScene.light.lightlocator = "fonar";
		InterfaceBackScene.light.flarelocator = "fonar";
		InterfaceBackScene.light.flaresize = 0.5;
		InterfaceBackScene.light.minflarecolor = 120.0;
		InterfaceBackScene.light.maxflarecolor = 200.0;
		CreateParticleSystem("candle",-13.2683,9.6656,21.1611,-1.57,0,0,0);
	} 
    else 
    {
		InterfaceBackScene.light.turnon = false;
		InterfaceBackScene.light.model = "mainmenu\Treasure_fonar";
		InterfaceBackScene.light.locator = "treasure";
		InterfaceBackScene.light.lightlocator = "fonar";
	}
	SendMessage(&InterfaceBackScene, "ls", 8, "light" );
	InterfaceBackScene.treasure.locator = "treasure";
	InterfaceBackScene.treasure.model = "mainmenu\treasure";
	SendMessage(&InterfaceBackScene, "ls", 9, "treasure" );
}

void MainMenu_CreatePalmTrees()
{
	InterfaceBackScene.palm.locator = "palm";
	InterfaceBackScene.palm.model = "mainmenu\palm";
	InterfaceBackScene.palm.animation = "main_menu_palm";
	InterfaceBackScene.palm.aniaction = "idle";
	SendMessage(&InterfaceBackScene, "ls", 9, "palm" );
}

void ICreateWeather()
{
    int n = 0;
    DeleteAttribute(&WeatherParams,"");
    if(CheckAttribute(&InterfaceStates,"Death"))
    {
        n = 20; // evening 20 lights on
        SetCurrentTime(19,20);
        
        WeatherParams.Rain.ThisDay 		= true;	
		WeatherParams.Rain.StartTime 	= 18;	
		WeatherParams.Rain.Duration  	= 280; 	
		WeatherParams.Rain.sDay			= rand(8);
		WeatherParams.Rain.sMorning		= rand(5);
		WeatherParams.Rain.sEvening		= 6;
		WeatherParams.Rain.sNight		= rand(6);
		WeatherParams.Rain.sTwilight 	= sti(WeatherParams.Rain.sNight);
		WeatherParams.Rain.Type			= rand(1);	
		WeatherParams.Rain.year 		= GetDataYear();		
		WeatherParams.Rain.month 		= GetDataMonth();
		WeatherParams.Rain.day 			= GetDataDay();
		WeatherParams.Rain.time 		= stf(WeatherParams.Rain.StartTime);
    }
    else
    {    
		// тест закатов в обычном меню
        n = 20; // evening 20 lights on
        SetCurrentTime(19,20);
    }

    SetNextWeather(Weathers[n].id);
    
    CreateSea(EXECUTE,REALIZE);
	CreateWeather(EXECUTE,REALIZE);
	
	CreateShipEnvironment();
    CreateCoastFoamEnvironment("MainMenu", EXECUTE, REALIZE);
}

void UpdateInterface()
{
	bool isSteamOverlayEnabled = GetEventData();

	if(!bSteamAchievements || !GetSteamEnabled()) return;
	
	if(!isSteamOverlayEnabled) // оверлей закрыт
	{
		DLCAppID = CheckUpdates();	
		if(DLCAppID > 0) 
		{   // есть обновления
			SetSelectable("UPDATES", true);
			SetNodeUsing("A_UPDATES", true);
		}
		else
		{	// обновлений нет
			SetSelectable("UPDATES", false);
			SetNodeUsing("A_UPDATES", false);
		}
	}
}

int CheckUpdates()
{
	bool bOk = false;
	int	 i;
	int	 appID;

	if(!bSteamAchievements || !GetSteamEnabled()) return 0;
	
	dlcCount = GetDLCCount();
	
	for(i = 0; i < dlcCount; i++)
	{
		appID = GetDLCData(i);
        if( appID > 0 )
        {
			bOk = GetDLCenabled(appID);
			if(!bOk) return appID;
		}
		else continue;	
	}
	return 0;
}

// mitrokosta проверка наличия модели корабля в ресурсах
bool ModelExists(string path) {
    object testModel;
    CreateEntity(&testModel, "MODELR");
    bool result = SendMessage(&testModel, "ls", MSG_MODEL_LOAD_GEO, path);
    DeleteClass(&testModel);
    return result;
}

/*
Проверяем прочитана ли новость
Для апдейтов меняем ключ key в файле news.txt
В качестве key ставим дату изменения новостей dd.mm.yyyy
*/
bool CheckNews()
{
	string value = "none";
	SendMessage(&GameInterface, "lssse", MSG_INTERFACE_READ_STRINGS_FROM_FILE, NEWS_INI_PATH, "News", "key", &value);
	return value == GetNewsKey();
}

string GetNewsKey()
{
	string key = GetConvertStr("key", "News.txt");
	if (key == "") key = "none";
	return key;
}
