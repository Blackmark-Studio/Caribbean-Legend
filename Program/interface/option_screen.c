#include "interface\utils\selector_frames.c"
// Sith меню настроек
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню на TAB
int currentTab = 0;
bool bKeyChangeWin = false;
int g_nCurControlsMode = -1;
int g_ControlsLngFile = -1;
string sBtn1 = "";
bool bControlsWin = false;
bool bAdvancedChange = false;
bool g_bToolTipStarted = false;

float 	fHUDRatio 	= 1.0;
int 	iHUDBase 	= iHudScale;
int 	newBase 	= iHudScale;
string 	sFoliageDrawDistance;
string 	sGrassDrawDistance;
int		curFoliageDrawDistance;
int		curGrassDrawDistance;
int		curFov = 1;
int		iFov;
int		iEnabledShipMarks;

#define BI_LOW_RATIO 	0.25
#define BI_HI_RATIO 	4.0
#define BI_DIF_RATIO 	3.75

int CalcHUDBase(float fSlider, float MyScreen)
{
    float fRes = BI_DIF_RATIO * fSlider;
    float curBase = MyScreen / (BI_LOW_RATIO + fRes);

    return makeint(curBase + 0.5);
}

float CalcHUDSlider(float fRatio)
{
    float fRes = fRatio - BI_LOW_RATIO;
    fRes /= BI_DIF_RATIO;

    return fRes;
}

void InitInterface_B(string iniName, bool isMainMenu)
{ 
	StartAboveForm(true);
	if(isMainMenu == true)
	{
		SetTimeScale(1.0);
		BLI_DisableShow();
	}
    else
    {
		SetTimeScale(0.0);
	}
	float glowEffect;

    fHUDRatio = stf(Render.screen_y) / iHudScale;
    iHUDBase = makeint(iHudScale);
    newBase = iHUDBase;
	
	trace("2 : " + iHudScale);
	g_nCurControlsMode = -1;
	GameInterface.title = "titleOptions";
	g_ControlsLngFile = LanguageOpenFile("ControlsNames.txt");

	if(CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
    {
		LoadGameOptions();
	}
    else
    {
		DeleteAttribute(&PlayerProfile, "name");
		LoadGameOptions();
	}

	IReadVariableBeforeInit();
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	IReadVariableAfterInit();

	SetControlsTabMode(1);

	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);  // boal
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("eventBtnAction","procBtnAction",0);
	SetEventHandler("SelectorValueChanged","SelectorValueChanged",0);
	SetEventHandler("eventKeyChange","procKeyChange",0);
	SetEventHandler("ConfirmExitClick","ProcessOkExit",0);
	SetEventHandler("ConfirmExitCancel","ConfirmExitCancel",0);

	SetEventHandler("CheckButtonChange","procCheckBoxChange",0);
	SetEventHandler("eSlideChange","procSlideChange",0);

	SetEventHandler("evntKeyChoose","procKeyChoose",0);
	SetEventHandler("ShowInfo", "ShowInfo", 0);
	SetEventHandler("ShowInfoWindow", "ShowInfo", 0);
	SetEventHandler("HideInfoWindow", "HideInfo", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);

	SetEventHandler("evFaderFrame","FaderFrame",0);

	aref ar; makearef(ar,objControlsState.key_codes);
	SendMessage(&GameInterface,"lsla",MSG_INTERFACE_MSG_TO_NODE,"KEY_CHOOSER", 0, ar);

	// if(sti(Render.full_screen)==0)
	// {
		// SetSelectable("GAMMA_SLIDE",false);
		// SetSelectable("BRIGHT_SLIDE",false);
		// SetSelectable("CONTRAST_SLIDE",false);
	// }

	float ftmp1 = -1.0;
	float ftmp2 = -1.0;
	float ftmp3 = -1.0;
	SendMessage(&sound,"leee",MSG_SOUND_GET_MASTER_VOLUME,&ftmp1,&ftmp2,&ftmp3);
	if(ftmp1==-1.0 && ftmp2==-1.0 && ftmp3==-1.0)
	{
		SetSelectable("MUSIC_SLIDE",false);
		SetSelectable("SOUND_SLIDE",false);
		SetSelectable("DIALOG_SLIDE",false);
	}

	// логотип
	SetMenuLogo();
	
	// Warship 07.07.09 Эффект свечения
	if(!CheckAttribute(&InterfaceStates, "GlowEffect"))
	{
		InterfaceStates.GlowEffect = 0;
	}
	
	glowEffect = sti(InterfaceStates.GlowEffect) / 250.0;
	
	GameInterface.nodes.GLOW_SLIDE.value = glowEffect;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "GLOW_SLIDE", 0, glowEffect);
	
	fHUDRatio = stf(Render.screen_y) / iHudScale;
	float sl = CalcHUDSlider(fHUDRatio);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "HUD_SLIDE", 2, makeint(sl * 100.0));
	GameInterface.nodes.hud_slide.value = sl;
	iHUDBase = CalcHUDBase(sl, stf(Render.screen_y));
	SetFormatedText("HUD_DESCRIP_TEXT", Render.screen_y + "  / " + newBase + " : " + fHUDRatio);
	
	// sith дальность прорисовки растительности на островах
	if(!CheckAttribute(&InterfaceStates, "FoliageDrawDistance"))
	{
		InterfaceStates.FoliageDrawDistance = 1000;
	}
	float fFoliageDrawDistance = sti(InterfaceStates.FoliageDrawDistance) / 3000.0; 
	GameInterface.nodes.FOLIAGE_DRAW_DISTANCE_SLIDE.value = fFoliageDrawDistance;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "FOLIAGE_DRAW_DISTANCE_SLIDE", 0, fFoliageDrawDistance);
	sFoliageDrawDistance = sti(InterfaceStates.FoliageDrawDistance);
	curFoliageDrawDistance = sti(InterfaceStates.FoliageDrawDistance);
	SetFormatedText("FOLIAGE_DESCRIP_TEXT", sFoliageDrawDistance);
	// sith дальность прорисовки травы
	if(!CheckAttribute(&InterfaceStates, "GrassDrawDistance"))
	{
		InterfaceStates.GrassDrawDistance = 50;
	}
	float fGrassDrawDistance = sti(InterfaceStates.GrassDrawDistance) / 500.0; 
	GameInterface.nodes.GRASS_DRAW_DISTANCE_SLIDE.value = fGrassDrawDistance;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "GRASS_DRAW_DISTANCE_SLIDE", 0, fGrassDrawDistance);
	sGrassDrawDistance = sti(InterfaceStates.GrassDrawDistance);
	curGrassDrawDistance = sti(InterfaceStates.GrassDrawDistance);
	SetFormatedText("GRASS_DESCRIP_TEXT", sGrassDrawDistance);
	// sith fov
	if(CheckAttribute(&InterfaceStates,"Fov"))
	{
		curFov = sti(InterfaceStates.Fov);
	}
	// продвинутые настройки контролок
	if(CheckAttribute(&InterfaceStates,"AdvancedChange"))
	{
		bAdvancedChange = sti(InterfaceStates.AdvancedChange);
	}
}

// TAB переключает вкладки таблицы
void ProcessInterfaceControls() 
{
    string controlName = GetEventData();
	if (controlName == "InterfaceTabSwitch" && !bKeyChangeWin)
    {
		currentTab = (currentTab + 1) % 5;
		SetControlsTabMode(currentTab + 1);
	}
}

void ProcessCancelExit()
{
	LoadGameOptions();
	ProcessExit();
}

void ProcessOkExit()
{
	// Warship 07.07.09 Эффект свечения
	SetGlowParams(1.0, sti(InterfaceStates.GlowEffect), 2));
	iHudScale = newBase;
	trace("3 : " + iHudScale);
	// sith дальность прорисовки растительности на островах
	if(CheckAttribute(&InterfaceStates,"FoliageDrawDistance") && sti(InterfaceStates.FoliageDrawDistance) != curFoliageDrawDistance)
    {
		if(bSeaActive && !bAbordageStarted) Sea_UpdateIslandGrass(AISea.Island);
	}
	int iLocation = FindLocation(pchar.location);
	// sith дальность прорисовки травы
	if(CheckAttribute(&InterfaceStates,"GrassDrawDistance") && sti(InterfaceStates.GrassDrawDistance) != curGrassDrawDistance)
    {
		if(iLocation != -1)
        {
			object objGrass;
			GetEntity(&objGrass,"grass");
			float fMaxDist = stf(InterfaceStates.GrassDrawDistance);
			SendMessage(objGrass,"lffffff",42666, 1.0, 1.0, 0.2, 10.0, fMaxDist, 0.0);
		}
	}
	// sith fov
	if(CheckAttribute(&InterfaceStates,"Fov") && sti(InterfaceStates.Fov) != curFov)
    {
		Render.CorrectFov = sti(InterfaceStates.Fov);
		if(!bSeaActive || bAbordageStarted)
			SendMessage(&locCamera, "lf", MSG_CAMERA_SET_PERSPECTIVE, 1.285);
	}

	// Применяем дальность исчезновения меток с названиями бухт
	ApplyLabelsMode(GetAttributeInt(&InterfaceStates, "MapLabelsMode"));

	// Количество травы
	if(GetAttributeInt(&InterfaceStates, "HerbQuantity") != iGrassQuality)
	{
		iGrassQuality = GetAttributeInt(&InterfaceStates, "HerbQuantity");
	}
	
	if(iEnabledShipMarks > 0) bDrawBars = true;
	else bDrawBars = false;
	
	if(iLocation != -1)
		SetLocationCharacterMarksOptions(&Locations[iLocation]);
	Camera_CheckPreset();

	SaveGameOptions();

	ProcessExit();
	Event("eventChangeOption");

	// change sea settings
	SetSeaGridStep(stf(InterfaceStates.SeaDetails));
}

void ProcessExit()
{
	if(CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
    {
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}

	IDoExit(RC_INTERFACE_OPTIONSCREEN_EXIT);
	if(!CheckAttribute(&InterfaceStates,"InstantExit") || sti(InterfaceStates.InstantExit) == false)
    {
		ReturnToMainMenu();
	}
}

void ShowConfirmExitWindow()
{
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowDisable("INTERFACE_WINDOW",true);
	XI_WindowDisable("GRAPHICS_WINDOW",true);
	XI_WindowDisable("CONTROLS_WINDOW",true);
	XI_WindowDisable("AUDIO_WINDOW",true);
	XI_WindowDisable("OTHER_WINDOW",true);
	XI_WindowDisable("CONFIRM_EXIT_WINDOW",false);
	XI_WindowShow("CONFIRM_EXIT_WINDOW", true);
	SetFormatedText("CONFIRM_EXIT_TEXT",XI_ConvertString("ControlsAtt"));
	AddLineToFormatedText("CONFIRM_EXIT_TEXT", " ");
	AddLineToFormatedText("CONFIRM_EXIT_TEXT", XI_ConvertString("Save Settings") + "?");
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CONFIRM_EXIT_TEXT", 8, 0, argb(255,255,128,128));
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"CONFIRM_EXIT_TEXT", 5);
	SetCurrentNode("CONFIRM_EXIT_NO");
}

void ConfirmExitCancel()
{
    XI_WindowDisable("CONFIRM_EXIT_WINDOW",true);
	XI_WindowDisable("MAIN_WINDOW",false);
	XI_WindowShow("CONFIRM_EXIT_WINDOW",false);
	XI_WindowDisable("INTERFACE_WINDOW",false);
	XI_WindowDisable("GRAPHICS_WINDOW",false);
	XI_WindowDisable("CONTROLS_WINDOW",false);
	XI_WindowDisable("AUDIO_WINDOW",false);
	XI_WindowDisable("OTHER_WINDOW",false);
	SetCurrentNode("BTN_OK");
}

void IDoExit(int exitCode)
{
	EndAboveForm(true);
	DelEventHandler("evntKeyChoose","procKeyChoose");
	DelEventHandler("eSlideChange","procSlideChange");
	DelEventHandler("CheckButtonChange","procCheckBoxChange");

	DelEventHandler("eventKeyChange","procKeyChange");
	DelEventHandler("ConfirmExitClick","ProcessOkExit");
	DelEventHandler("ConfirmExitCancel","ConfirmExitCancel");
	DelEventHandler("eventBtnAction","procBtnAction");
	DelEventHandler("SelectorValueChanged","SelectorValueChanged");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ShowInfo", "ShowInfo");
	DelEventHandler("ShowInfoWindow", "ShowInfo");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("HideInfoWindow","HideInfo");
	DelEventHandler("evFaderFrame","FaderFrame");
	DelEventHandler("InterfaceBreak","ProcessCancelExit");  // boal

	LanguageCloseFile(g_ControlsLngFile);

	interfaceResultCommand = exitCode;
	if(CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit)==true) {
		EndCancelInterface(true);
	} else {
		EndCancelInterface(false);
	}
	ControlsMakeInvert();
}

void IReadVariableBeforeInit()
{
	GetSoundOptionsData();
	GetMouseOptionsData();
	GetVideoOptionsData();
}

void IReadVariableAfterInit()
{
	InitSelectors("ControlsMode", "CONTROLS_MODE", &iControlsMode);
	InitSelectors("HerbQuantity", "HERB", &iGrassQuality); // не перемеиноввывал глоб. переменную для совместимости
	InitSelectors("MapLabelsMode", "MAP_LABELS", 0);      // нет глоб переменной
	InitSelectors("FOV", "FOV", &iFov);
	InitSelectors("FontType", "FONT", &iFontType);
	InitSelectors("MoreInfo", "MOREINFO", &iMoreInfo);
	InitSelectors("CompassPos", "COMPASS_POS", &iCompassPos);
	InitSelectors("ControlsTips", "CONTROLS_TIPS", &iControlsTips);
	InitSelectors("EnabledShipMarks", "SHIPMARKS", &iEnabledShipMarks);
	InitSelectors("HelpTime", "HELPTIME", &iGlobalHelpTime);
	InitSelectors("Camera", "CAMERA", &iGlobalCamera);
	InitSelectors("EnemyType", "ENEMYTYPE", &iGlobalEnemyType);
	InitSelectors("Target", "TARGET", &iGlobalTarget);

	if(iEnabledShipMarks > 0) bDrawBars = true;
	else bDrawBars = false;

	GetControlsStatesData();

	int nClassicSoundScene = 0;
	if(CheckAttribute(&InterfaceStates,"ClassicSoundScene")) {
		nClassicSoundScene = sti(InterfaceStates.ClassicSoundScene);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CLASSIC_SOUNDSCENE_CHECKBOX", 2, 1, nClassicSoundScene);

	int nAdvancedChange = 0;
	if(CheckAttribute(&InterfaceStates,"AdvancedChange")) {
		nAdvancedChange = sti(InterfaceStates.AdvancedChange);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ADVANCEDCHANGE_CHECKBOX", 2, 1, nAdvancedChange);
	
	int nShowBattleMode = 0;
	if(CheckAttribute(&InterfaceStates,"ShowBattleMode")) {
		nShowBattleMode = sti(InterfaceStates.ShowBattleMode);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"BATTLE_MODE_CHECKBOX", 2, 1, nShowBattleMode);

	int nShowCharString = 1;
	if(CheckAttribute(&InterfaceStates,"ShowCharString")) {
		nShowCharString = sti(InterfaceStates.ShowCharString);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHAR_STRING_CHECKBOX", 2, 1, nShowCharString);

	int nShowTutorial = 1;
	if(CheckAttribute(&InterfaceStates,"ShowTutorial")) {
		nShowTutorial = sti(InterfaceStates.ShowTutorial);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TUTORIAL_CHECKBOX", 2, 1, nShowTutorial);
	
	int nEnabledAutoSaveMode = 1;
	if(CheckAttribute(&InterfaceStates,"EnabledAutoSaveMode")) {
		nEnabledAutoSaveMode = sti(InterfaceStates.EnabledAutoSaveMode);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"AUTOSAVE_CHECKBOX", 2, 1, nEnabledAutoSaveMode);

	int nEnabledAutoSaveMode2 = 0;
	if(CheckAttribute(&InterfaceStates,"EnabledAutoSaveMode2")) {
		nEnabledAutoSaveMode2 = sti(InterfaceStates.EnabledAutoSaveMode2);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"AUTOSAVE2_CHECKBOX", 2, 1, nEnabledAutoSaveMode2);

	int nEnabledQuestsMarks = 1;
	if(CheckAttribute(&InterfaceStates,"EnabledQuestsMarks")) {
		nEnabledQuestsMarks = sti(InterfaceStates.EnabledQuestsMarks);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"QUESTMARK_CHECKBOX", 2, 1, nEnabledQuestsMarks);

	int nEnabledSimpleSea = 0;
	if(CheckAttribute(&InterfaceStates,"SimpleSea")) 
	{
		nEnabledSimpleSea = sti(InterfaceStates.SimpleSea);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SIMPLESEA_CHECKBOX", 2, 1, nEnabledSimpleSea);
	
	int nEnabledCREWONDECK = 1;
	if(CheckAttribute(&InterfaceStates,"CREWONDECK")) 
	{
		nEnabledCREWONDECK = sti(InterfaceStates.CREWONDECK);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREWONDECK_CHECKBOX", 2, 1, nEnabledCREWONDECK);
	
	int nEnabledROTATESKY = 0;
	if(CheckAttribute(&InterfaceStates,"ROTATESKY")) 
	{
		nEnabledROTATESKY = sti(InterfaceStates.ROTATESKY);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ROTATESKY_CHECKBOX", 2, 1, nEnabledROTATESKY);
	
	int nEnabledDYNAMICLIGHTS = 1;
	if(CheckAttribute(&InterfaceStates,"DYNAMICLIGHTS")) 
	{
		nEnabledDYNAMICLIGHTS = sti(InterfaceStates.DYNAMICLIGHTS);
	}
}

// метод на TAB переключает вкладки таблицы
void SetControlsTabModeManual(int mode) 
{
    currentTab = mode - 1;
    SetControlsTabMode(mode);
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(125,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;
	int nColor5 = nColor1;

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;
	string sPic5 = sPic1;
	
	string sPic6 = sPic1;
	string sPic7 = sPic1;
	string sPic8 = sPic1;
	string sPic9 = sPic1;
	string sPic10 = sPic1;

	switch(nMode)
	{
	case 1: // режим путешествий на земле
		sPic1 = "TabSelected";
		sPic6 = "TabSelectedMark";
		nColor1 = argb(255,255,255,255);
	break;
	case 2: // режим боя на земле
		sPic2 = "TabSelected";
		sPic7 = "TabSelectedMark";		
		nColor2 = argb(255,255,255,255);
	break;
	case 3: // море от 3-го лица
		sPic3 = "TabSelected";
		sPic8 = "TabSelectedMark";			
		nColor3 = argb(255,255,255,255);
	break;
	case 4: // море от первого лица	
		sPic4 = "TabSelected";
		sPic9 = "TabSelectedMark";	
		nColor4 = argb(255,255,255,255);
	break;
	case 5: // глобальная карта	
		sPic5 = "TabSelected";
		sPic10 = "TabSelectedMark";	
		nColor5 = argb(255,255,255,255);
	break;
	}

	SetNewGroupPicture("TABBTN_PRIMARY_LAND", "TABS3", sPic1);
	SetNewGroupPicture("TABBTN_FIGHT_MODE", "TABS3", sPic2);
	SetNewGroupPicture("TABBTN_SAILING_3RD", "TABS3", sPic3);
	SetNewGroupPicture("TABBTN_SAILING_1ST", "TABS3", sPic4);
	SetNewGroupPicture("TABBTN_WORLDMAP", "TABS3", sPic5);
	SetNewGroupPicture("TABBTN_PRIMARY_LAND_MARK", "TABS3", sPic6);
	SetNewGroupPicture("TABBTN_FIGHT_MODE_MARK", "TABS3", sPic7);
	SetNewGroupPicture("TABBTN_SAILING_3RD_MARK", "TABS3", sPic8);
	SetNewGroupPicture("TABBTN_SAILING_1ST_MARK", "TABS3", sPic9);
	SetNewGroupPicture("TABBTN_WORLDMAP_MARK", "TABS3", sPic10);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_PRIMARY_LAND", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_FIGHT_MODE", 8,0,nColor2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SAILING_3RD", 8,0,nColor3);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SAILING_1ST", 8,0,nColor4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_WORLDMAP", 8,0,nColor5);
	
	FillControlsList(nMode);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();


	if(sNodName == "TABBTN_PRIMARY_LAND") {
		SetControlsTabModeManual(1);
		return;
	}
	if(sNodName == "TABBTN_FIGHT_MODE") {
		SetControlsTabModeManual(2);
		return;
	}
	if(sNodName == "TABBTN_SAILING_3RD") {
		SetControlsTabModeManual(3);
		return;
	}
	if(sNodName == "TABBTN_SAILING_1ST") {
		SetControlsTabModeManual(4);
		return;
	}
	if(sNodName == "TABBTN_WORLDMAP") {
		SetControlsTabModeManual(5);
		return;
	}	
}

void procBtnAction()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	if(sNodName == "BTN_INTERFACE") {
		if(iComIndex==ACTION_MOUSECLICK) {
			XI_WindowDisable("INTERFACE_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", true);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			XI_WindowShow("AUDIO_WINDOW", false);
			XI_WindowShow("OTHER_WINDOW", false);
			bControlsWin = false;
		}	
		if(iComIndex==ACTION_ACTIVATE) {
			XI_WindowDisable("INTERFACE_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", true);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			XI_WindowShow("AUDIO_WINDOW", false);
			XI_WindowShow("OTHER_WINDOW", false);
			bControlsWin = false;
			SetCurrentNode("HUD_SLIDE_FRAME");
		}
		return;
	}
	if(sNodName == "BTN_GRAPHICS") {
		if(iComIndex==ACTION_MOUSECLICK) {
			XI_WindowDisable("GRAPHICS_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", true);
			XI_WindowShow("CONTROLS_WINDOW", false);
			XI_WindowShow("AUDIO_WINDOW", false);
			XI_WindowShow("OTHER_WINDOW", false);
			bControlsWin = false;
		}	
		if(iComIndex==ACTION_ACTIVATE) {
			XI_WindowDisable("GRAPHICS_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", true);
			XI_WindowShow("CONTROLS_WINDOW", false);
			XI_WindowShow("AUDIO_WINDOW", false);
			XI_WindowShow("OTHER_WINDOW", false);
			bControlsWin = false;
			SetCurrentNode("GLOW_SLIDE_FRAME");
		}
		return;
	}
	if(sNodName == "BTN_CONTROLS") {
		if(iComIndex==ACTION_MOUSECLICK) {
			XI_WindowDisable("CONTROLS_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", true);
			XI_WindowShow("AUDIO_WINDOW", false);
			XI_WindowShow("OTHER_WINDOW", false);
			bControlsWin = true;
			SetAlertMarksControls();
		}
		if(iComIndex==ACTION_ACTIVATE) {
			XI_WindowDisable("CONTROLS_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", true);
			XI_WindowShow("AUDIO_WINDOW", false);
			XI_WindowShow("OTHER_WINDOW", false);
			bControlsWin = true;
			SetCurrentNode("LOC_MOUSE_SENSITIVITY_SLIDE_FRAME");
			SetAlertMarksControls();
		}
		return;
	}
	if(sNodName == "BTN_AUDIO") {
		if(iComIndex==ACTION_MOUSECLICK) {
			XI_WindowDisable("AUDIO_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			XI_WindowShow("AUDIO_WINDOW", true);
			XI_WindowShow("OTHER_WINDOW", false);
			bControlsWin = false;
		}	
		if(iComIndex==ACTION_ACTIVATE) {
			XI_WindowDisable("AUDIO_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			XI_WindowShow("AUDIO_WINDOW", true);
			XI_WindowShow("OTHER_WINDOW", false);
			bControlsWin = false;
			SetCurrentNode("MUSIC_SLIDE_FRAME");
		}
		return;
	}
	if(sNodName == "BTN_OTHER") {
		if(iComIndex==ACTION_MOUSECLICK) {
			XI_WindowDisable("OTHER_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			XI_WindowShow("AUDIO_WINDOW", false);
			XI_WindowShow("OTHER_WINDOW", true);
			bControlsWin = false;
		}	
		if(iComIndex==ACTION_ACTIVATE) {
			XI_WindowDisable("OTHER_WINDOW", false);
			XI_WindowShow("INTERFACE_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			XI_WindowShow("AUDIO_WINDOW", false);
			XI_WindowShow("OTHER_WINDOW", true);
			bControlsWin = false;
			SetCurrentNode("MUSIC_SLIDE_FRAME");
		}
		return;
	}
	if(sNodName == "BTN_OK") {
		if(iComIndex==ACTION_ACTIVATE || iComIndex==ACTION_MOUSECLICK) {
			if(TestForEmptyControls()) ShowConfirmExitWindow();
			else ProcessOkExit();
		}
		return;
	}
	if(sNodName == "BTN_SETTINGS_DEFAULT") {
		if(bControlsWin) 
		{
			RestoreDefaultKeys();
			SetAlertMarksControls();
		}
		else RestoreDefaultSettings();
		return;
	}
}

void SelectorValueChanged()
{
	int iComIndex = GetEventData();
	string sNodeName = GetEventData();
	int direction = 0;

	switch (iComIndex)
	{
		case ACTION_LEFTSTEP: direction = -1; break;
		case ACTION_RIGHTSTEP: direction = 1; break;
		case ACTION_MOUSECLICK:
		{
			if      (FindSubStr(sNodeName, "LEFTCHANGE_", 0) == 0) direction = -1; // клик левая стрелка
			else if (FindSubStr(sNodeName, "RIGHTCHANGE_", 0) == 0) direction = 1; // клик правая стрелка
		}
		break;
	}
	if (direction == 0) return;

	if (HandleSelector(&sNodeName, "ControlsMode",		&direction, "CONTROLS_MODE",	1, &iControlsMode)) return;
	if (HandleSelector(&sNodeName, "HerbQuantity",		-direction, "HERB",				3, &iGrassQuality)) return; // -direction для инверсии справа налево
	if (HandleSelector(&sNodeName, "FOV",				&direction, "FOV",				1, &iFov)) return;
	if (HandleSelector(&sNodeName, "EnabledShipMarks",	&direction, "SHIPMARKS",		2, &iEnabledShipMarks)) return;
	if (HandleSelector(&sNodeName, "FontType",			&direction, "FONT",				2, &iFontType)) return;
	if (HandleSelector(&sNodeName, "MoreInfo",			&direction, "MOREINFO",			1, &iMoreInfo)) return;
	if (HandleSelector(&sNodeName, "ControlsTips",		&direction, "CONTROLS_TIPS",	2, &iControlsTips)) return;
	if (HandleSelector(&sNodeName, "CompassPos",		&direction, "COMPASS_POS",		1, &iCompassPos)) return;
	if (HandleSelector(&sNodeName, "MapLabelsMode",		&direction, "MAP_LABELS",		2, 0)) return;
	
	if (HandleSelector(&sNodeName, "HelpTime",			&direction, "HELPTIME",			3, &iGlobalHelpTime)) return;
	if (HandleSelector(&sNodeName, "Camera",			&direction, "CAMERA",			1, &iGlobalCamera)) return;
	if (HandleSelector(&sNodeName, "EnemyType",			&direction, "ENEMYTYPE",		2, &iGlobalEnemyType)) return;
	if (HandleSelector(&sNodeName, "Target",			&direction, "TARGET",			3, &iGlobalTarget)) return;
}

void ApplyLabelsMode(int newMode)
{
	aref allLabels;
	makearef(allLabels, worldMap.labels);
	int shoreHeight = 0;
	switch (newMode)
	{
		case 0: shoreHeight = 200;  break;
		case 1: shoreHeight = 300;  break;
		case 2: shoreHeight = 4000; break;
	}

	for (int x=0; x<GetAttributesNum(allLabels); x++) 
	{
		aref label = GetAttributeN(allLabels, x);
		switch (label.type)
		{
			case "shore": label.heightview = shoreHeight; break;
		}
	}
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if(sNodName == "ALWAYS_RUN_CHECKBOX") 
	{
		{
			SetAlwaysRun(bBtnState);
		}
	}
	if(sNodName == "ADVANCEDCHANGE_CHECKBOX") 
	{
		{
			InterfaceStates.AdvancedChange = bBtnState;
			bAdvancedChange = bBtnState;
		}
	}
	if(sNodName == "INVERT_MOUSE_CHECKBOX") 
	{
		{
			InterfaceStates.InvertCameras = bBtnState;
		}
	}
	if(sNodName == "BATTLE_MODE_CHECKBOX") 
	{
		{
			InterfaceStates.ShowBattleMode = bBtnState;
		}
	}
	if(sNodName == "CHAR_STRING_CHECKBOX") 
	{
		{
			InterfaceStates.ShowCharString = bBtnState;
		}
	}
	if(sNodName == "TUTORIAL_CHECKBOX") 
	{
		{
			InterfaceStates.ShowTutorial = bBtnState;
		}
	}
	if(sNodName == "CLASSIC_SOUNDSCENE_CHECKBOX") 
	{
		{
			InterfaceStates.ClassicSoundScene = bBtnState;
		}
	}	
	if(sNodName == "AUTOSAVE_CHECKBOX") 
	{
		{
			InterfaceStates.EnabledAutoSaveMode = bBtnState;
		}
	}
	if(sNodName == "AUTOSAVE2_CHECKBOX") 
	{
		{
			InterfaceStates.EnabledAutoSaveMode2 = bBtnState;
		}
	}
	if(sNodName == "QUESTMARK_CHECKBOX") 
	{
		{
			InterfaceStates.EnabledQuestsMarks = bBtnState;
		}
	}

	if(sNodName == "SIMPLESEA_CHECKBOX") 
	{
		{
			InterfaceStates.SimpleSea = bBtnState;
		}
	}

	if(sNodName == "CREWONDECK_CHECKBOX") 
	{
		{ 
			InterfaceStates.CREWONDECK = bBtnState;
		}
	}
	
	if(sNodName == "ROTATESKY_CHECKBOX") 
	{
		{ 
			InterfaceStates.ROTATESKY = bBtnState;
		}
	}
}

void procSlideChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();

	if(sNodeName=="GAMMA_SLIDE" || sNodeName=="BRIGHT_SLIDE" || sNodeName=="CONTRAST_SLIDE") {
		ChangeVideoColor();
		return;
	}
	
	// Warship 07.07.09 эффект свечения
	if(sNodeName == "GLOW_SLIDE")
	{
		InterfaceStates.GlowEffect = fVal*250;
		return;
	}
	
	if(sNodeName == "SEA_DETAILS_SLIDE") {
		ChangeSeaDetail();
		return;
	}
	if(sNodeName == "FOLIAGE_DRAW_DISTANCE_SLIDE") {
		InterfaceStates.FoliageDrawDistance = fVal*3000;
		sFoliageDrawDistance = sti(InterfaceStates.FoliageDrawDistance);
		SetFormatedText("FOLIAGE_DESCRIP_TEXT", sFoliageDrawDistance);
		return;
	}
	if(sNodeName == "GRASS_DRAW_DISTANCE_SLIDE") {
		InterfaceStates.GrassDrawDistance = fVal*500;
		sGrassDrawDistance = sti(InterfaceStates.GrassDrawDistance);
		SetFormatedText("GRASS_DESCRIP_TEXT", sGrassDrawDistance);
		return;
	}
	if(sNodeName=="MUSIC_SLIDE" || sNodeName=="SOUND_SLIDE" || sNodeName=="DIALOG_SLIDE") {
		ChangeSoundSetting();
		return;
	}
	if(sNodeName == "HUD_SLIDE") {
		ChangeHUDDetail();
		return;
	}
	if(sNodeName=="LOC_MOUSE_SENSITIVITY_SLIDE" || sNodeName=="SEA_MOUSE_SENSITIVITY_SLIDE") {
		ChangeMouseSensitivity();
	}
}

void ChangeMouseSensitivity()
{
	InterfaceStates.mouse.loc_sens = stf(GameInterface.nodes.loc_mouse_sensitivity_slide.value);
	InterfaceStates.mouse.sea_sens = stf(GameInterface.nodes.sea_mouse_sensitivity_slide.value);
	SetRealMouseSensitivity();
}

void ChangeVideoColor()
{
	float fCurContrast = stf(GameInterface.nodes.contrast_slide.value);
	float fCurGamma = stf(GameInterface.nodes.GAMMA_SLIDE.value);
	float fCurBright = stf(GameInterface.nodes.BRIGHT_SLIDE.value);

	float fContrast = ConvertContrast(fCurContrast,false);
	float fGamma = ConvertGamma(fCurGamma,false);
	float fBright = ConvertBright(fCurBright,false);

	if(!CheckAttribute(&InterfaceStates,"video.contrast") ||
		(stf(InterfaceStates.video.contrast)!=fContrast) ||
		(stf(InterfaceStates.video.gamma)!=fGamma) ||
		(stf(InterfaceStates.video.brightness)!=fBright)) {
			InterfaceStates.video.contrast = fContrast;
			InterfaceStates.video.gamma = fGamma;
			InterfaceStates.video.brightness = fBright;
			XI_SetColorCorrection(fContrast,fGamma,fBright);
	}
}

void ChangeSeaDetail()
{
	float fCurSeaDetail = stf(GameInterface.nodes.sea_details_slide.value);
	float fSeaDetail = ConvertSeaDetails(fCurSeaDetail,false);
	if(!CheckAttribute(&InterfaceStates,"SeaDetails") ||
		(stf(InterfaceStates.SeaDetails)!=fSeaDetail)) {
			InterfaceStates.SeaDetails = fSeaDetail;
	}
}

void ChangeSoundSetting()
{
	float fMusic = stf(GameInterface.nodes.music_slide.value);
	float fSound = stf(GameInterface.nodes.sound_slide.value);
	float fDialog = stf(GameInterface.nodes.dialog_slide.value);
	SendMessage(&sound,"lfff", MSG_SOUND_SET_MASTER_VOLUME, fSound,	fMusic,	fDialog);
}

void FillControlsList(int nMode)
{
	int n,qC,idx;
	string groupName;
	aref arGrp, arC;

	if(nMode == g_nCurControlsMode) {return;}
	g_nCurControlsMode = nMode;
	DeleteAttribute(&GameInterface,"controls_list");
	GameInterface.controls_list.select = 1;
	GameInterface.controls_list.top = 0;

	groupName = GetGroupNameByMode(nMode);
	if(CheckAttribute(&objControlsState,"keygroups."+groupName))
    {
		makearef(arGrp,objControlsState.keygroups.(groupName));
		qC = GetAttributesNum(arGrp);
		idx = 0;
		for(n=0; n<qC; n++)
        {
			arC = GetAttributeN(arGrp,n);
			if(!CheckAttribute(arC,"invisible") || arC.invisible!="1")
            {
				if(AddToControlsList(idx, GetAttributeName(arC), GetAttributeValue(arC), CheckAttribute(arC,"remapping") && arC.remapping=="1"))
                {
					idx++;
				}
			}
		}
	}

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONTROLS_LIST", 0);
	SendMessage(&GameInterface, "lsf", MSG_INTERFACE_SET_SCROLLER, "SCROLL_CONTROLS", 0);
}

bool AddToControlsList(int row, string sControl, string sKey, bool bRemapable)
{
	string rowname = "tr" + (row+1);
	GameInterface.controls_list.(rowname).userdata.remapable = bRemapable;
	GameInterface.controls_list.(rowname).userdata.control = sControl;
	GameInterface.controls_list.(rowname).userdata.key = sKey;
	GameInterface.controls_list.(rowname).td1.str = LanguageConvertString(g_ControlsLngFile,sControl);
	if(GameInterface.controls_list.(rowname).td1.str == "")
    {
		trace("Warning!!! " + sControl + " hav`t translate value");
	}
	if(!bRemapable) // выделение контролок которые нельзя поменять
    {
		GameInterface.controls_list.(rowname).td1.color = argb(255,128,128,128);
	}
	if(CheckAttribute(&objControlsState,"key_codes."+sKey+".img"))
    {
		GameInterface.controls_list.(rowname).td2.fontidx = 0;
		GameInterface.controls_list.(rowname).td2.textoffset = "78,-10";
		GameInterface.controls_list.(rowname).td2.scale = 1.00;
		GameInterface.controls_list.(rowname).td2.str = objControlsState.key_codes.(sKey).img;
		if(CheckAttribute(&objControlsState,"keygroups.AltPressedGroup"+"."+sControl))
		{
			GameInterface.controls_list.(rowname).td3.fontidx = 0;
			GameInterface.controls_list.(rowname).td3.textoffset = "-17,-10";
			GameInterface.controls_list.(rowname).td3.scale = 1.00;
			GameInterface.controls_list.(rowname).td3.str = objControlsState.key_codes.VK_MENU.img;
			
			GameInterface.controls_list.(rowname).td4.fontidx = 2;
			GameInterface.controls_list.(rowname).td4.textoffset = "-15,-8";
			GameInterface.controls_list.(rowname).td4.scale = 1.00;
			GameInterface.controls_list.(rowname).td4.str = "+";
		}
	}
	else GameInterface.controls_list.(rowname).td1.color = argb(255,255,128,128); // красим пустые кнопки
	return true;
}

void RefreshControlsList()
{
	string groupName = GetGroupNameByMode(g_nCurControlsMode);
	
	aref rows;
	makearef(rows, GameInterface.controls_list);
	int rowsCount = GetAttributesNum(rows);
	for (int i = 0; i < rowsCount; i++) {
		aref row = GetAttributeN(rows, i);
		if (!CheckAttribute(row, "userdata.control")) {
			continue;
		}
		string controlName = row.userdata.control;
		string key = objControlsState.keygroups.(groupName).(controlName);
		RefreshControlInList(GetAttributeName(row), controlName, key, sti(row.userdata.remapable));
	}
	
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONTROLS_LIST", 0);
}

void RefreshControlInList(string rowname, string sControl, string sKey, bool bRemapable)
{
	aref rowData;
	makearef(rowData, GameInterface.controls_list.(rowname));
	DeleteAttribute(rowData, "");
	
	GameInterface.controls_list.(rowname).userdata.remapable = bRemapable;
	GameInterface.controls_list.(rowname).userdata.control = sControl;
	GameInterface.controls_list.(rowname).userdata.key = sKey;
	GameInterface.controls_list.(rowname).td1.str = LanguageConvertString(g_ControlsLngFile,sControl);
	if(GameInterface.controls_list.(rowname).td1.str == "") {
		trace("Warning!!! " + sControl + " hav`t translate value");
	}
	if(!bRemapable) // выделение контролок которые нельзя поменять
    {
		GameInterface.controls_list.(rowname).td1.color = argb(255,128,128,128);
	}
	if(CheckAttribute(&objControlsState,"key_codes."+sKey+".img")) {
		GameInterface.controls_list.(rowname).td2.fontidx = 0;
		GameInterface.controls_list.(rowname).td2.textoffset = "78,-10";
		GameInterface.controls_list.(rowname).td2.scale = 1.00;
		GameInterface.controls_list.(rowname).td2.str = objControlsState.key_codes.(sKey).img;
		if(CheckAttribute(&objControlsState,"keygroups.AltPressedGroup"+"."+sControl))
		{
			GameInterface.controls_list.(rowname).td3.fontidx = 0;
			GameInterface.controls_list.(rowname).td3.textoffset = "-17,-10";
			GameInterface.controls_list.(rowname).td3.scale = 1.00;
			GameInterface.controls_list.(rowname).td3.str = objControlsState.key_codes.VK_MENU.img;
			
			GameInterface.controls_list.(rowname).td4.fontidx = 2;
			GameInterface.controls_list.(rowname).td4.textoffset = "-15,-8";
			GameInterface.controls_list.(rowname).td4.scale = 1.00;
			GameInterface.controls_list.(rowname).td4.str = "+";
		}
	}
	else GameInterface.controls_list.(rowname).td1.color = argb(255,255,128,128); // красим пустые кнопки
	//AddToControlsList(row, sControl, sKey, bRemapable);
}

string GetGroupNameByMode(int nMode)
{
	switch(nMode) 
	{
		case 1: return "PrimaryLand"; break;
		case 2: return "FightModeControls"; break;
		case 3: return "Sailing3Pers"; break;
		case 4: return "Sailing1Pers"; break;
		case 5: return "WorldMapControls"; break;
	}
	return "unknown";
}

void GetSoundOptionsData()
{   // belamour побережем уши)))
	float fCurMusic = 0.1;
	float fCurSound = 0.1;
	float fCurDialog = 0.1;
	SendMessage(&sound,"leee",MSG_SOUND_GET_MASTER_VOLUME,&fCurSound,&fCurMusic,&fCurDialog);
	GameInterface.nodes.music_slide.value = fCurMusic;
	GameInterface.nodes.sound_slide.value = fCurSound;
	GameInterface.nodes.dialog_slide.value = fCurDialog;
}

void GetMouseOptionsData()
{
	float fCurLocSens = 0.5;
	float fCurSeaSens = 0.5;
	if(CheckAttribute(&InterfaceStates,"mouse.sea_sens")) {fCurSeaSens=stf(InterfaceStates.mouse.sea_sens);}
	if(CheckAttribute(&InterfaceStates,"mouse.loc_sens")) {fCurLocSens=stf(InterfaceStates.mouse.loc_sens);}
	if(fCurSeaSens<0.0) fCurSeaSens = 0.0;
	if(fCurSeaSens>1.0) fCurSeaSens = 1.0;
	if(fCurLocSens<0.0) fCurLocSens = 0.0;
	if(fCurLocSens>1.0) fCurLocSens = 1.0;
	GameInterface.nodes.sea_mouse_sensitivity_slide.value = fCurSeaSens;
	GameInterface.nodes.loc_mouse_sensitivity_slide.value = fCurLocSens;
}

void GetVideoOptionsData()
{
	float fC = 1.0;
	float fG = 1.0;
	float fB = 0.0;
	float fD = 1.0;
	if(CheckAttribute(&InterfaceStates,"video.contrast")) {
		fC = stf(InterfaceStates.video.contrast);
	}
	if(CheckAttribute(&InterfaceStates,"video.gamma")) {
		fG = stf(InterfaceStates.video.gamma);
	}
	if(CheckAttribute(&InterfaceStates,"video.brightness")) {
		fB = stf(InterfaceStates.video.brightness);
	}

	if(CheckAttribute(&InterfaceStates,"SeaDetails")) {
		fD = stf(InterfaceStates.SeaDetails);
	}
	ISetColorCorrection(fC, fG, fB, fD);
}

void ISetColorCorrection(float fContrast, float fGamma, float fBright, float fSeaDetails)

{
	float fCurContrast = ConvertContrast(fContrast,true);
	float fCurGamma = ConvertGamma(fGamma,true);
	float fCurBright = ConvertBright(fBright,true);
	float fCurSeaDetails = ConvertSeaDetails(fSeaDetails, true);
	if(fCurContrast>1.0) fCurContrast = 1.0;
	if(fCurContrast<0.0) fCurContrast = 0.0;
	if(fCurGamma>1.0) fCurGamma = 1.0;
	if(fCurGamma<0.0) fCurGamma = 0.0;
	if(fCurBright>1.0) fCurBright = 1.0;
	if(fCurBright<0.0) fCurBright = 0.0;
	if(fCurSeaDetails>1.0) fCurSeaDetails = 1.0;
	if(fCurSeaDetails<0.0) fCurSeaDetails = 0.0;

	GameInterface.nodes.CONTRAST_SLIDE.value = fCurContrast;
	GameInterface.nodes.GAMMA_SLIDE.value = fCurGamma;
	GameInterface.nodes.BRIGHT_SLIDE.value = fCurBright;
	GameInterface.nodes.SEA_DETAILS_SLIDE.value = fCurSeaDetails;
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CONTRAST_SLIDE", 0,fCurContrast);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"GAMMA_SLIDE", 0,fCurGamma);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"BRIGHT_SLIDE", 0,fCurBright);

	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SEA_DETAILS_SLIDE", 0, fCurSeaDetails);
	XI_SetColorCorrection(fContrast,fGamma,fBright);
	//Set sea detail
}

float ConvertContrast(float fContrast, bool Real2Slider)
{ // контрастность от 0.75 до 1.25
	if(Real2Slider) {
		return fContrast*2.0-1.5;
	}
	return fContrast*0.5+0.75;
}

float ConvertGamma(float fGamma, bool Real2Slider)
{ // гамма от 0.5 до 2.0
	if(Real2Slider)
	{
		if(fGamma<=1.0) {return fGamma-0.5;}
		return fGamma*0.5;
	}
	if(fGamma<=0.5) {return fGamma+0.5;}
	return fGamma*2.0;
}

float ConvertBright(float fBright, bool Real2Slider)
{
	if(Real2Slider) {
		return (fBright+50.0)/100.0;
	}
	return fBright*100-50;
}

float ConvertSeaDetails(float fDetails, bool Real2Slider)
{
	return fDetails;
}

void GetControlsStatesData()
{
	int nAlwaysRun = 0;
	if(CheckAttribute(&InterfaceStates,"alwaysrun")) {
		nAlwaysRun = sti(InterfaceStates.alwaysrun);
	}
	int nInvertCam = 0;
	if(CheckAttribute(&InterfaceStates,"InvertCameras")) {
		nInvertCam = sti(InterfaceStates.InvertCameras);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALWAYS_RUN_CHECKBOX", 2, 1, nAlwaysRun);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INVERT_MOUSE_CHECKBOX", 2, 1, nInvertCam);
}

void SetAlwaysRun(bool bRun)
{
	InterfaceStates.alwaysrun = bRun;
	pchar.alwaysrun = bRun;
}

void procKeyChange()
{
	//FillControlsList();
	string srow = "tr" + GameInterface.controls_list.select;
	if(!CheckAttribute(&GameInterface,"controls_list."+srow)) {return;}
	if(sti(GameInterface.controls_list.(srow).userdata.remapable)!=1) {return;}
	ChooseOtherControl();
}

void ChooseOtherControl()
{
	bKeyChangeWin = true;
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowDisable("CONTROLS_WINDOW",true);
	XI_WindowShow("CHANGEKEY_WINDOW",true);
	SetCurrentNode("KEY_CHOOSER");
	string srow = "tr" + GameInterface.controls_list.select;
	if(CheckAttribute(&GameInterface,"controls_list." + srow + ".td2.str")) SetFormatedText("CHANGEKEY_TEXT_BTN", GameInterface.controls_list.(srow).td2.str);
	else SetFormatedText("CHANGEKEY_TEXT_BTN", "");
	SetFormatedText("CHANGEKEY_TEXT", XI_ConvertString("Press any key"));
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", XI_ConvertString("KeyAlreadyUsed"));
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 0, argb(255,255,128,128));
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 4, argb(0,255,64,64));
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 5);
}

int glob_retVal;
ref procKeyChoose()
{
	int keyIdx = GetEventData();
	int stickUp = GetEventData();

	glob_retVal = false;

    // ~!~ DANGER ШИЗА
    // 78 - НОМЕР АТРИБУТА VK_ESCAPE ИЗ ИНИТОВ
	if (keyIdx == 78) {
		ReturnFromReassign();
		glob_retVal = true;
		return &glob_retVal;
	}

	if(DoMapToOtherKey(keyIdx,stickUp))
	{
		ReturnFromReassign();
		glob_retVal = true;
	}

	return &glob_retVal;
}

void ReturnFromReassign()
{
	sBtn1 = "";
	XI_WindowShow("CHANGEKEY_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
	XI_WindowDisable("CONTROLS_WINDOW",false);
	SetCurrentNode("CONTROLS_LIST");
	bKeyChangeWin = false;
	SetAlertMarksControls();
}

// проверка пустых клавиш в конкретной группе
bool TestGroupForEmptyControls(string group) {
	aref keyGroup;

	makearef(keyGroup, objControlsState.keygroups.(group));
	
	int keyGroupControlsNum = GetAttributesNum(keyGroup);
	for (int i = 0; i < keyGroupControlsNum; i++) {
		aref keyGroupControl = GetAttributeN(keyGroup, i);
		if (GetAttributeValue(keyGroupControl) == "") {
			trace("Control " + GetAttributeName(keyGroupControl) + " has empty key");
			return true;
		}
	}
	
	return false;
}

// проверка пустых клавиш во всех группах
bool TestForEmptyControls()
{
    string keyGroupName;
	aref keyGroups, keyGroup;
	makearef(keyGroups, objControlsState.keygroups);

	int keyGroupsNum = GetAttributesNum(keyGroups);
	for(int i = 0; i < keyGroupsNum; i++)
    {
		keyGroup = GetAttributeN(keyGroups, i);
		keyGroupName = GetAttributeName(keyGroup);
		if (TestGroupForEmptyControls(keyGroupName))
        {
			trace("Group " + keyGroupName + " has empty key");
			return true;
		}
	}
	
	return false;
}

bool DoMapToOtherKey(int keyIdx, int stickUp)
{
	string srow = "tr" + GameInterface.controls_list.select;
	string groupName = GetGroupNameByMode(g_nCurControlsMode);
	string sControl = GameInterface.controls_list.(srow).userdata.control;
	string sKey = GameInterface.controls_list.(srow).userdata.key;
	bool bAltPress = XI_IsKeyPressed("alt");

	aref arControlGroup;
	aref arKeyRoot, arKey;
	string sName;
	int keyCode;

	if(stickUp)
	{
		//SetStickNotAvailable();
		return false;
	}

	makearef(arControlGroup, objControlsState.keygroups.(groupName));
	makearef(arKeyRoot, objControlsState.key_codes);
	arKey = GetAttributeN(arKeyRoot, keyIdx);
	keyCode = sti(GetAttributeValue(arKey));

	// Check for not allowed keys (belamour)
	if (keyCode == sti(objControlsState.key_codes.VK_F6)  ||
		keyCode == sti(objControlsState.key_codes.VK_F7)  ||
		keyCode == sti(objControlsState.key_codes.VK_F8)  ||
		keyCode == sti(objControlsState.key_codes.VK_F9)  ||
		keyCode == sti(objControlsState.key_codes.VK_F10) ||
		keyCode == sti(objControlsState.key_codes.VK_F11) ||
		keyCode == sti(objControlsState.key_codes.VK_F12))
	{
		return false;
	}
	
	if(CheckAttribute(arKey,"stick") && sti(arKey.stick)==true) return false;

	string controlReplacement = ""; // friends текущей клавиши сюда не кладутся
	if(KeyAlreadyUsed(groupName, sControl, GetAttributeName(arKey), bAltPress, &controlReplacement) && controlReplacement == "")
	{
        // Есть на кнопке, которой запрещено переназначение
		SetKeyChooseWarning(XI_ConvertString("KeyAlreadyUsed"));
		return false;
	}

	if(controlReplacement != "" && sBtn1 != controlReplacement)
	{
        // Предупреждаем, что кнопка занята, и только на второе нажатие её зачистит
		SetKeyChooseWarning(XI_ConvertString("KeyAlreadyUsed2"));
		sBtn1 = controlReplacement;
		return false;
	}

	sName = arControlGroup.(sControl);
	if(CheckAttribute(arKeyRoot,sName+".stick") && sti(arKeyRoot.(sName).stick) == true) return false;

	if(bAltPress) MapControlToGroup(sControl, "AltPressedGroup");
	else DeleteAttribute(&objControlsState, "keygroups.AltPressedGroup." + sControl);

    // Обновим клавишу
    GroupKeyUpdate(sControl, keyCode, groupName);

    int num, i;
    aref aFriend;
	if (controlReplacement != "")
    {
        if(!bAdvancedChange || IsSyncLock(sControl))
        {
            // Затереть всех дублёров во всех группах, кроме friends
            EraseCopiesInAllGroups(sControl);
        }
        else
        {
            // Если меняем внутри одной группы, достаточно проверить дублёра и его friends
            GroupKeyUpdate(controlReplacement, -1, groupName);
            if(CheckAttribute(&objControlsState, "map.controls." + controlReplacement + ".friends"))
            {
                makearef(aFriend, objControlsState.map.controls.(controlReplacement).friends);
                num = GetAttributesNum(aFriend);
                for(i = 0; i < num; i++)
                {
                    sName = GetAttributeName(GetAttributeN(aFriend, i));
                    if(CheckAttribute(arControlGroup, sName) && arControlGroup.(sName) == arControlGroup.(sControl))
                    {
                        GroupKeyUpdate(sName, -1, groupName);
                    }
                }
            }
        }
	}

    if(CheckAttribute(&objControlsState, "map.controls." + sControl + ".friends"))
    {
        makearef(aFriend, objControlsState.map.controls.(sControl).friends);
        num = GetAttributesNum(aFriend);
        for(i = 0; i < num; i++)
        {
            sName = GetAttributeName(GetAttributeN(aFriend, i));
            if(CheckAttribute(arControlGroup, sName))
            {
                if(sti(aFriend.(sName)) == 1)
                {
                    // Если дружественная клавиша синхронизирована, обновим и её тоже
                    // Здесь предполагается, что синхронизированные клавиши в тех же группах
                    // Иначе при их апдейте может быть неучтённый дубль в другой группе, где есть
                    // синхронизированная, но нет текущей обновляемой (sControl)
                    GroupKeyUpdate(sName, keyCode, groupName); 
                }
                else if(sti(aFriend.(sName)) == 2) BI_CheckWASD(arControlGroup.(sName) == CI_GetKeyName(keyCode), groupName);
                else if(sti(aFriend.(sName)) == 3) BI_CheckWASDSail(arControlGroup.(sName) == CI_GetKeyName(keyCode), groupName);
            }   
        }
    }

	RefreshControlsList();
	return true;
}

void ControlSettings(int iControlMode)
{
	SetMouseToDefault();
	ControlsInit(GetTargetPlatform(),false, iControlMode);
	int nMode = g_nCurControlsMode;
	g_nCurControlsMode = -1;
	FillControlsList(nMode);
}

void SetMouseToDefault()
{
	InterfaceStates.InvertCameras = false;
	InterfaceStates.mouse.sea_sens = 0.5;
	InterfaceStates.mouse.loc_sens = 0.5;

	SetRealMouseSensitivity();
	SetAlwaysRun(true);

	GetControlsStatesData();
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"LOC_MOUSE_SENSITIVITY_SLIDE", 0,stf(InterfaceStates.mouse.loc_sens));
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SEA_MOUSE_SENSITIVITY_SLIDE", 0,stf(InterfaceStates.mouse.sea_sens));
}

void ShowInfo()
{
//	g_bToolTipStarted = true;
	string sHeader = " ";
	string sNode = GetEventData();

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "-1";
	int	picW = 128;
	int	picH = 128;

	switch (sNode)
	{
		case "HUD_SLIDE_FRAME":
			sHeader = XI_ConvertString("HUD_SLIDE Mode");
			sText1 = XI_ConvertString("HUD_SLIDE Mode_descr");
		break;
		case "TUTORIAL_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("Show tutorial");
			sText1 = XI_ConvertString("Show tutorial_descr");
		break;
		case "QUESTMARK_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("QuestMark Mode");
			sText1 = XI_ConvertString("QuestMark Mode_descr");
		break;
		case "BATTLE_MODE_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("Show battle mode");
			sText1 = XI_ConvertString("Show battle mode_descr");
		break;
		case "CHAR_STRING_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("Show characters strings");
			sText1 = XI_ConvertString("Show characters strings_descr");
		break;
// Graphics
		case "GAMMA_SLIDE_FRAME":
			sHeader = XI_ConvertString("gamma");
			sText1 = XI_ConvertString("gamma_descr");
		break;
		case "BRIGHT_SLIDE_FRAME":
			sHeader = XI_ConvertString("Brightness");
			sText1 = XI_ConvertString("brightness_descr");
		break;
		case "CONTRAST_SLIDE_FRAME":
			sHeader = XI_ConvertString("Contrast");
			sText1 = XI_ConvertString("Contrast_descr");
		break;
		case "GLOW_SLIDE_FRAME":
			sHeader = XI_ConvertString("Glow");
			sText1 = XI_ConvertString("Glow_descr");
			sText2 = XI_ConvertString("PostProcessOnly");
		break;
		case "SEA_DETAILS_SLIDE_FRAME":
			sHeader = XI_ConvertString("Sea Detail");
			sText1 = XI_ConvertString("Sea Detail_descr");
		break;
		case "FOLIAGE_DRAW_DISTANCE_SLIDE_FRAME":
			sHeader = XI_ConvertString("Foliage Draw Distance");
			sText1 = XI_ConvertString("Foliage Draw Distance_descr");
		break;
		case "GRASS_DRAW_DISTANCE_SLIDE_FRAME":
			sHeader = XI_ConvertString("Grass Draw Distance");
			sText1 = XI_ConvertString("Grass Draw Distance_descr");
		break;
		case "ROTATESKY_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("ROTATESKY Mode");
			sText1 = XI_ConvertString("ROTATESKY Mode_descr");
			sText2 = XI_ConvertString("ROTATESKYatt Mode_descr");
		break;
		case "CREWONDECK_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("CREWONDECK Mode");
			sText1 = XI_ConvertString("CREWONDECK Mode_descr");
		break;
		case "SIMPLESEA_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("SimpleSea Mode");
			sText1 = XI_ConvertString("SimpleSea Mode_descr");
		break;
		case "FRAME_FOV":
			picW = 645;
			picH = 430;
			sPicture = "interfaces\le\help\fov.tga";
		break;
// Controls
		case "CONTROLS_LIST":
			sHeader = XI_ConvertString("Button Settings");
			sText1 = XI_ConvertString("Button Settings_descr");
			sText2 = XI_ConvertString("Button Settings_descr2");
		break;
		case "LOC_MOUSE_SENSITIVITY_SLIDE_FRAME":
			sHeader = XI_ConvertString("Location Mouse Sensitivity");
			sText1 = XI_ConvertString("Location Mouse Sensitivity_descr");
		break;
		case "SEA_MOUSE_SENSITIVITY_SLIDE_FRAME":
			sHeader = XI_ConvertString("Sea Mouse Sensitivity");
			sText1 = XI_ConvertString("Sea Mouse Sensitivity_descr");
		break;
		case "INVERT_MOUSE_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("Invert Vertical Mouse Control");
			sText1 = XI_ConvertString("Invert Vertical Mouse Control_descr");
		break;
		case "ALWAYS_RUN_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("Always Run");
			sText1 = XI_ConvertString("Always Run_descr");
		break;
		case "ADVANCEDCHANGE_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("AdvancedChangeControls");
			sText1 = XI_ConvertString("AdvancedChangeControls_descr");
		break;
// Audio
		case "MUSIC_SLIDE_FRAME":
			sHeader = XI_ConvertString("Music Volume");
			sText1 = XI_ConvertString("Music Volume_descr");
		break;
		case "SOUND_SLIDE_FRAME":
			sHeader = XI_ConvertString("Sound Volume");
			sText1 = XI_ConvertString("Sound Volume_descr");
		break;
		case "DIALOG_SLIDE_FRAME":
			sHeader = XI_ConvertString("Dialog Volume");
			sText1 = XI_ConvertString("Dialog Volume_descr");
		break;
		case "CLASSIC_SOUNDSCENE_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("Classic Soundscene");
			sText1 = XI_ConvertString("Classic Soundscene_descr");
		break;
// Other
		case "AUTOSAVE2_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("AutoSave Mode2");
			sText1 = XI_ConvertString("AutoSave Mode2_descr");
		break;
		case "AUTOSAVE_CHECKBOX_FRAME":
			sHeader = XI_ConvertString("AutoSave Mode");
			sText1 = XI_ConvertString("AutoSave Mode_descr");
		break;
	}

	HandleSelectorDescription(&sNode, &sHeader, &sText1, "FOV", "FOV");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "ControlsMode", "CONTROLS_MODE");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "HerbQuantity", "HERB");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "EnabledShipMarks", "SHIPMARKS");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "FontType", "FONT");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "MoreInfo", "MOREINFO");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "ControlsTips", "CONTROLS_TIPS");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "CompassPos", "COMPASS_POS");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "MapLabelsMode", "MAP_LABELS");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "HelpTime", "HELPTIME");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "Camera", "CAMERA");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "EnemyType", "ENEMYTYPE");
	HandleSelectorDescription(&sNode, &sHeader, &sText1, "Target", "TARGET");
	CreateTooltipNew(sNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, picW, picH, false);
}

void HideInfo()
{
	CloseTooltipNew();
/*	if(g_bToolTipStarted) {
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("OK_BUTTON");
	}*/
}

bool KeyAlreadyUsed(string sGrpName, string sControl, string sKey, bool bAltPress, ref controlReplacement)
{
	bool bAPgroup = false;
	if(CheckAttribute(&objControlsState,"keygroups.AltPressedGroup." + sControl))
	{
		bAPgroup = (objControlsState.keygroups.AltPressedGroup.(sControl) == sKey);
	}
	if(!CheckAttribute(&objControlsState,"keygroups." + sGrpName + "." + sControl)) return false;

	// belamour legendary edition смотрим, если кей в текущем значении контролки, то даем добро и сворачиваем кейчузер
	if(bAltPress == bAPgroup && objControlsState.keygroups.(sGrpName).(sControl) == sKey) return false;

	// belamour контролки без группы не переназначаются
	if(sKey == "VK_ADD" || sKey == "VK_SUBTRACT") return true; 

	int grp, i, q, n;
	aref arGrp, arCntrl, arGrpList;
    string sName;
	
    if(!bAdvancedChange || IsSyncLock(sControl))
    {
        // Проверка во всех группах, где есть клавиша
        makearef(arGrpList, objControlsState.keygroups);
        grp = GetAttributesNum(arGrpList);
        for(n=0; n<grp; n++)
        {
            arGrp = GetAttributeN(arGrpList,n);
            if(CheckAttribute(arGrp, sControl))
            {
                q = GetAttributesNum(arGrp);
                for(i=0; i<q; i++)
                {
                    arCntrl = GetAttributeN(arGrp,i);
                    if(GetAttributeValue(arCntrl) == sKey)
                    {
                        sName = GetAttributeName(arCntrl);
                        if(CheckAttribute(&objControlsState, "map.controls." + sControl + ".friends." + sName))  continue;
                        if(bAltPress != CheckAttribute(&objControlsState, "keygroups.AltPressedGroup." + sName)) continue;
                        if(sti(arCntrl.remapping)) controlReplacement = sName;
                        return true;
                    }
                }
            }
        }
    }
    else
    {
        // Проверка на совпадение в той же группе
        makearef(arGrp,objControlsState.keygroups.(sGrpName));
        q = GetAttributesNum(arGrp);
        for(i=0; i<q; i++)
        {
            arCntrl = GetAttributeN(arGrp,i);
            if(GetAttributeValue(arCntrl) == sKey)
            {
                sName = GetAttributeName(arCntrl);
                if(CheckAttribute(&objControlsState, "map.controls." + sControl + ".friends." + sName))  continue;
                if(bAltPress != CheckAttribute(&objControlsState, "keygroups.AltPressedGroup." + sName)) continue;
                if(sti(arCntrl.remapping)) controlReplacement = sName;
                return true;
            }
        }
    }

	return false;
}

void SetKeyChooseWarning(string sWarningText)
{
	SendMessage(&GameInterface,"lslle",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 10, 4, &sWarningText);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 5);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 4, argb(255,255,64,64));
	PostEvent("evFaderFrame",2000,"lll",500,0,50);
}

void FaderFrame()
{
	int nTotalTime = GetEventData();
	int nCurTime = GetEventData();
	int nDeltaTime = GetEventData();

	nCurTime = nCurTime + nDeltaTime;
	if(nCurTime>nTotalTime) {nCurTime=nTotalTime;}

	int nAlpha = 255*(nTotalTime-nCurTime) / nTotalTime;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 4, argb(nAlpha,255,64,64));

	if(nCurTime<nTotalTime) {
		PostEvent("evFaderFrame",nDeltaTime,"lll",nTotalTime,nCurTime,nDeltaTime);
	}
}

void ChangeHUDDetail()
{
    float sl = stf(GameInterface.nodes.hud_slide.value);
	newBase = CalcHUDBase(sl, stf(Render.screen_y));
	if(newBase != iHUDBase) 
	{
        fHUDRatio = stf(Render.screen_y) / newBase;
		SetFormatedText("HUD_DESCRIP_TEXT", Render.screen_y + "  / " + newBase + " : " + fHUDRatio);
	}
}

void RestoreDefaultKeys()
{
	InterfaceStates.ControlsMode = 0;
	iControlsMode = 0;
	SetSelectorNewTextValue("ControlsMode", "CONTROLS_MODE", iControlsMode);
	ControlSettings(iControlsMode);
	InterfaceStates.AdvancedChange =  0;
	bAdvancedChange = false;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ADVANCEDCHANGE_CHECKBOX", 2, 1, 0);
}

void RestoreDefaultSettings()
{
	SendMessage(&sound,"lfff", MSG_SOUND_SET_MASTER_VOLUME, 0.25, 0.25, 0.25);
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "MUSIC_SLIDE", 0, 0.25);
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "SOUND_SLIDE", 0, 0.25);
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "DIALOG_SLIDE", 0, 0.25);

	SetSelectorDefault("HerbQuantity", "HERB", 0, &iGrassQuality);
	SetSelectorDefault("Fov", "FOV", 1, &iFov);
	SetSelectorDefault("FontType", "FONT", 0, &iFontType);
	SetSelectorDefault("MoreInfo", "MOREINFO", 0, &iMoreInfo);
	SetSelectorDefault("ControlsMode", "CONTROLS_MODE", 0, &iControlsMode);
	SetSelectorDefault("CompassPos", "COMPASS_POS", 0, &iCompassPos);
	SetSelectorDefault("MapLabelsMode", "MAP_LABELS", 0, 0);
	SetSelectorDefault("ControlsTips", "CONTROLS_TIPS", 2, &iControlsTips);
	SetSelectorDefault("EnabledShipMarks", "SHIPMARKS", 1, &iEnabledShipMarks);
	SetSelectorDefault("HelpTime", "HELPTIME", 1, &iGlobalHelpTime);
	SetSelectorDefault("Camera", "CAMERA", 1, &iGlobalCamera);
	SetSelectorDefault("EnemyType", "ENEMYTYPE", 1, &iGlobalEnemyType);
	SetSelectorDefault("Target", "TARGET", 2, &iGlobalTarget);
	ControlSettings(iControlsMode);
	bDrawBars = true;

	InterfaceStates.AdvancedChange =  0;
	bAdvancedChange = false;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ADVANCEDCHANGE_CHECKBOX", 2, 1, 0);

	InterfaceStates.ClassicSoundScene =  1;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CLASSIC_SOUNDSCENE_CHECKBOX", 2, 1, 1);

	GameInterface.nodes.GAMMA_SLIDE.value = 0.5;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "GAMMA_SLIDE", 0, 0.5);
	
	GameInterface.nodes.BRIGHT_SLIDE.value = 0.5;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "BRIGHT_SLIDE", 0, 0.5);

	GameInterface.nodes.CONTRAST_SLIDE.value = 0.5;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "CONTRAST_SLIDE", 0, 0.5);

	GameInterface.nodes.GLOW_SLIDE.value = 0;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "GLOW_SLIDE", 0, 0);
	
	// SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "HUD_SLIDE", 2, 20);
	// GameInterface.nodes.hud_slide.value = 0.2;
	// float sl = stf(GameInterface.nodes.hud_slide.value);
	// newBase = CalcHUDBase(sl, stf(Render.screen_y));
	// fHUDRatio = stf(Render.screen_y) / newBase;
	// SetFormatedText("HUD_DESCRIP_TEXT", Render.screen_y + "  / " + newBase + " : " + fHUDRatio);

	InterfaceStates.ShowBattleMode = 0
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"BATTLE_MODE_CHECKBOX", 2, 1, 0);

	InterfaceStates.ShowCharString = 1
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHAR_STRING_CHECKBOX", 2, 1, 1);

	InterfaceStates.ShowTutorial = 1
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TUTORIAL_CHECKBOX", 2, 1, 1);

	InterfaceStates.EnabledAutoSaveMode = 1;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"AUTOSAVE_CHECKBOX", 2, 1, 1);

	InterfaceStates.EnabledAutoSaveMode2 = 0;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"AUTOSAVE2_CHECKBOX", 2, 1, 0);

	InterfaceStates.EnabledQuestsMarks = 1;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"QUESTMARK_CHECKBOX", 2, 1, 1);

	InterfaceStates.SimpleSea = 0;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SIMPLESEA_CHECKBOX", 2, 1, 0);
	
	InterfaceStates.CREWONDECK = 1;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREWONDECK_CHECKBOX", 2, 1, 1);
	
	InterfaceStates.ROTATESKY = 0;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ROTATESKY_CHECKBOX", 2, 1, 0);
	
	InterfaceStates.DYNAMICLIGHTS = 1;
	
	InterfaceStates.SeaDetails = 1.0;
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SEA_DETAILS_SLIDE", 0, 1.0);
	
	InterfaceStates.FoliageDrawDistance = 1000;
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"FOLIAGE_DRAW_DISTANCE_SLIDE", 0, 0.4);

	InterfaceStates.GrassDrawDistance = 50;
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"GRASS_DRAW_DISTANCE_SLIDE", 0, 0.1);
}

void SetAlertMarksControls()
{
	SetNodeUsing("A_PRIMARY_LAND",false);
	SetNodeUsing("A_FIGHT_MODE",false);
	SetNodeUsing("A_SAILING_3RD",false);
	SetNodeUsing("A_SAILING_1ST",false);
	SetNodeUsing("A_WORLDMAP",false);
	if(TestGroupForEmptyControls("PrimaryLand"))       SetNodeUsing("A_PRIMARY_LAND",true);
	if(TestGroupForEmptyControls("FightModeControls")) SetNodeUsing("A_FIGHT_MODE",true);
	if(TestGroupForEmptyControls("Sailing3Pers"))      SetNodeUsing("A_SAILING_3RD",true);
	if(TestGroupForEmptyControls("Sailing1Pers"))      SetNodeUsing("A_SAILING_1ST",true);
	if(TestGroupForEmptyControls("WorldMapControls"))  SetNodeUsing("A_WORLDMAP",true);
}

void GroupKeyUpdate(string controlName, int keyCode, string sGroupName)
{
	int i, nGQ;
	aref arKGRoot, arKG;
    string sName;

    // cntrlCode - индекс контролки; controlName - имя контролки;
    // keyCode   - индекс бинда;     sKeyName    - имя бинда;

    int cntrlCode = sti(objControlsState.map.controls.(controlName));
    string sKeyName = CI_GetKeyName(keyCode);

    makearef(arKGRoot, objControlsState.keygroups);
    nGQ = GetAttributesNum(arKGRoot);

    if(!bAdvancedChange || IsSyncLock(controlName))
    {
        for(i = 0; i < nGQ; i++)
        {
            arKG = GetAttributeN(arKGRoot,i);
            if(CheckAttribute(arKG, controlName))
            {
                arKG.(controlName) = sKeyName;
                sName = GetAttributeName(arKG);
                if(sName != "AltPressedGroup")
                    MapControl(cntrlCode, keyCode, GetGroupIDX(sName));
            }
        }
    }
    else
    {
        makearef(arKG, objControlsState.keygroups.(sGroupName));
        if(!CheckAttribute(arKG, controlName)) return;
        arKG.(controlName) = sKeyName;
        if(sGroupName != "AltPressedGroup")
            MapControl(cntrlCode, keyCode, GetGroupIDX(sGroupName));

        // Пройдёмся по группам, не отображаемым в интерфейсе, где есть эта контролка
        // Их бинды привязываются к первой валидной отображаемой группе
        int j;
        aref arKG2;
        string sName2;
        for(i=0; i<nGQ; i++)
        {
            arKG  = GetAttributeN(arKGRoot, i);
            sName = GetAttributeName(arKG);
            if(IsSettingsGroup(sName)) continue;
            if(CheckAttribute(arKG, controlName))
            {
                for(j = 0; j < nGQ; j++)
                {
                    arKG2  = GetAttributeN(arKGRoot, j);
                    sName2 = GetAttributeName(arKG2);
                    if(!IsSettingsGroup(sName2)) continue;
                    if(CheckAttribute(arKG2, controlName))
                    {
                        arKG.(controlName) = arKG2.(controlName);
                        if(sName != "AltPressedGroup")
                        {
                            keyCode = CI_GetKeyCode(arKG.(controlName));
                            MapControl(cntrlCode, keyCode, GetGroupIDX(sName));
                        }
                        break;
                    }
                }
            }
        }
    }
}

void EraseCopiesInAllGroups(string sControl)
{
    string sName, sGroupName;
	int i, nGQ, j, num;
	aref arKGRoot, arKG;

    makearef(arKGRoot, objControlsState.keygroups);
    nGQ = GetAttributesNum(arKGRoot);
    for(i = 0; i < nGQ; i++)
    {
        arKG = GetAttributeN(arKGRoot, i);
        if(CheckAttribute(arKG, sControl))
        {
            sGroupName = GetAttributeName(arKG);
            num = GetAttributesNum(arKG);
            for(j = 0; j < num; j++)
            {
                sName = GetAttributeName(GetAttributeN(arKG, j));
                if(sName == sControl)
                    continue;
                if(CheckAttribute(&objControlsState, "map.controls." + sControl + ".friends." + sName))
                    continue;
                if(arKG.(sName) == arKG.(sControl))
                {
                    GroupKeyUpdate(sName, -1, sGroupName);
                }
            }
        }
    }
}

// Особые указания на случай дубля WASD и Стрелок
void BI_CheckWASD(bool bSame, string sGroup)
{
    if(bAdvancedChange && sGroup != "FightModeControls") return;

    aref arControlGroup;

    if(bSame)
    {
        // Если появился дубль, то управление уходит из BI
        makearef(arControlGroup, objControlsState.keygroups.BattleInterfaceControls);
        DeleteAttribute(arControlGroup, "ChrForward");
        DeleteAttribute(arControlGroup, "ChrBackward");
        DeleteAttribute(arControlGroup, "ChrStrafeLeft");
        DeleteAttribute(arControlGroup, "ChrStrafeRight");
    }
    else if(!CheckAttribute(&objControlsState, "keygroups.BattleInterfaceControls.ChrForward"))
    {
        // Если дубля нет, то проверим остальные, можем ли вернуть в BI
        makearef(arControlGroup, objControlsState.keygroups.FightModeControls);
        bSame = arControlGroup.ChrForward     == arControlGroup.BICommandsUp   ||
                arControlGroup.ChrBackward    == arControlGroup.BICommandsDown ||
                arControlGroup.ChrStrafeLeft  == arControlGroup.BICommandsLeft ||
                arControlGroup.ChrStrafeRight == arControlGroup.BICommandsRight;
        if(!bSame)
        {
            MapControlToGroup("ChrForward",     "BattleInterfaceControls");
            MapControlToGroup("ChrBackward",    "BattleInterfaceControls");
            MapControlToGroup("ChrStrafeLeft",  "BattleInterfaceControls");
            MapControlToGroup("ChrStrafeRight", "BattleInterfaceControls");
        }
    }
}

void BI_CheckWASDSail(bool bSame, string sGroup)
{
    if(bAdvancedChange && sGroup != "Sailing3Pers") return;

    aref arControlGroup;

    if(bSame)
    {
        // Если появился дубль, то управление уходит из BI
        makearef(arControlGroup, objControlsState.keygroups.BattleInterfaceControls);
        DeleteAttribute(arControlGroup, "Ship_SailUp");
        DeleteAttribute(arControlGroup, "Ship_SailDown");
        DeleteAttribute(arControlGroup, "Ship_TurnLeft");
        DeleteAttribute(arControlGroup, "Ship_TurnRight");
    }
    else if(!CheckAttribute(&objControlsState, "keygroups.BattleInterfaceControls.Ship_SailUp"))
    {
        // Если дубля нет, то проверим остальные, можем ли вернуть в BI
        makearef(arControlGroup, objControlsState.keygroups.Sailing3Pers);
        bSame = arControlGroup.Ship_SailUp    == arControlGroup.BICommandsUp   ||
                arControlGroup.Ship_SailDown  == arControlGroup.BICommandsDown ||
                arControlGroup.Ship_TurnLeft  == arControlGroup.BICommandsLeft ||
                arControlGroup.Ship_TurnRight == arControlGroup.BICommandsRight;
        if(!bSame)
        {
            MapControlToGroup("Ship_SailUp",    "BattleInterfaceControls");
            MapControlToGroup("Ship_SailDown",  "BattleInterfaceControls");
            MapControlToGroup("Ship_TurnLeft",  "BattleInterfaceControls");
            MapControlToGroup("Ship_TurnRight", "BattleInterfaceControls");
        }
    }
}

bool IsSyncLock(string sControl)
{
    return CheckAttribute(&objControlsState, "map.controls." + sControl + ".SyncLock");
}
