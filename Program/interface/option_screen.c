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
float   SEACAMPERSP = sti(InterfaceStates.SEACAMPERSP)/100.0; // belamour перспектива МК
string 	sFoliageDrawDistance;
string 	sGrassDrawDistance;
int		curDifficulty;
int		curFoliageDrawDistance;
int		curGrassDrawDistance;
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
	SetEventHandler("eventKeyChange","procKeyChange",0);
	SetEventHandler("ConfirmExitClick","ProcessOkExit",0);
	SetEventHandler("ConfirmExitCancel","ConfirmExitCancel",0);

	SetEventHandler("CheckButtonChange","procCheckBoxChange",0);
	SetEventHandler("eSlideChange","procSlideChange",0);

	SetEventHandler("evntKeyChoose","procKeyChoose",0);
	SetEventHandler("ShowInfo", "ShowInfo", 0);
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
	
	// belamour перспектива морской камеры
	if(!CheckAttribute(&InterfaceStates, "SEACAMPERSP"))
	{
		InterfaceStates.SEACAMPERSP = 25; 
	}
	SEACAMPERSP = sti(InterfaceStates.SEACAMPERSP)/100.0;
	GameInterface.nodes.SEACAMPERSP_SLIDE.value = SEACAMPERSP;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "SEACAMPERSP_SLIDE", 0, SEACAMPERSP);
	
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
	// sith сложность игры
	if(CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
    {
		curDifficulty = MOD_SKILL_ENEMY_RATE;
		iDifficulty = MOD_SKILL_ENEMY_RATE;
	}
	SetFormatedText("DIFFICULTY_DESCRIP_TEXT", DifficultyDes(iDifficulty));
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
	SEACAMPERSP = InterfaceStates.SEACAMPERSP; // belamour перспектива МК
	// if(CheckAttribute(&InterfaceStates,"Difficulty") && sti(InterfaceStates.Difficulty) != curDifficulty){
		// MOD_SKILL_ENEMY_RATE = sti(InterfaceStates.Difficulty); // sith сохраняем сложность
		// MOD_EXP_RATE = makeint(5 + MOD_SKILL_ENEMY_RATE);
		// MOD_EXP_RATE =  makeint(MOD_EXP_RATE + MOD_SKILL_ENEMY_RATE * MOD_EXP_RATE / 1.666666666);
		// if (MOD_EXP_RATE < 10) MOD_EXP_RATE = 10;
		// if(CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
		// Log_Info (XI_ConvertString("DifficultyChanged") + DifficultyDes(MOD_SKILL_ENEMY_RATE));
	// }
	// sith дальность прорисовки растительности на островах
	if(CheckAttribute(&InterfaceStates,"FoliageDrawDistance") && sti(InterfaceStates.FoliageDrawDistance) != curFoliageDrawDistance)
    {
		if(bSeaActive && !bAbordageStarted) Sea_UpdateIslandGrass(AISea.Island);
	}
	// sith дальность прорисовки травы
	if(CheckAttribute(&InterfaceStates,"GrassDrawDistance") && sti(InterfaceStates.GrassDrawDistance) != curGrassDrawDistance)
    {
		int iLocation = FindLocation(pchar.location);
		if(iLocation != -1)
        {
			object objGrass;
			GetEntity(&objGrass,"grass"));
			float fMaxDist = stf(InterfaceStates.GrassDrawDistance);
			SendMessage(objGrass,"lffffff",42666, 1.0, 1.0, 0.2, 10.0, fMaxDist, 0.0);
		}
	}
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
	XI_WindowDisable("GAME_WINDOW",true);
	XI_WindowDisable("SCREEN_WINDOW",true);
	XI_WindowDisable("GRAPHICS_WINDOW",true);
	XI_WindowDisable("CONTROLS_WINDOW",true);
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
	XI_WindowDisable("GAME_WINDOW",false);
	XI_WindowDisable("SCREEN_WINDOW",false);
	XI_WindowDisable("GRAPHICS_WINDOW",false);
	XI_WindowDisable("CONTROLS_WINDOW",false);
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
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ShowInfo", "ShowInfo");
	DelEventHandler("MouseRClickUP","HideInfo");
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
	SetFormatedText("HERB_DESCRIP_TEXT", HerbDes(iGrassQuality));
	GetControlsStatesData();

	if(CheckAttribute(&InterfaceStates,"FontType")) {
		iFontType = sti(InterfaceStates.FontType);
	}
	SetFormatedText("FONT_DESCRIP_TEXT", FontDes(iFontType));

	if(CheckAttribute(&InterfaceStates,"MoreInfo")) {
		iMoreInfo = sti(InterfaceStates.MoreInfo);
	}
	SetFormatedText("MOREINFO_DESCRIP_TEXT", MoreInfoDes(iMoreInfo));

	if(CheckAttribute(&InterfaceStates,"ControlsMode")) {
		iControlsMode = sti(InterfaceStates.ControlsMode);
	}
	SetFormatedText("CONTROLS_MODE_DESCRIP_TEXT", ControlsModeDes(iControlsMode));

	if(CheckAttribute(&InterfaceStates,"CompassPos")) {
		iCompassPos = sti(InterfaceStates.CompassPos);
	}
	SetFormatedText("COMPASS_POS_DESCRIP_TEXT", CompassPosDes(iCompassPos));

	if(CheckAttribute(&InterfaceStates,"ControlsTips")) {
		iControlsTips = sti(InterfaceStates.ControlsTips);
	}
	SetFormatedText("CONTROLS_TIPS_DESCRIP_TEXT", ControlsTipsDes(iControlsTips));

	iEnabledShipMarks = 1;
	if(CheckAttribute(&InterfaceStates,"EnabledShipMarks")) {
		iEnabledShipMarks = sti(InterfaceStates.EnabledShipMarks);
		if(iEnabledShipMarks > 0) bDrawBars = 1;
		else bDrawBars = iEnabledShipMarks;
	}
	SetFormatedText("SHIPMARKS_DESCRIP_TEXT", EnabledShipMarksDes(iEnabledShipMarks));

	if(CheckAttribute(&InterfaceStates,"ArcadeSails")) {
		iArcadeSails = sti(InterfaceStates.ArcadeSails);
	}
	SetFormatedText("ARCADESAILS_DESCRIP_TEXT", ArcadeSailsDes(iArcadeSails));
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

	int nShowStealthAlarm = 1;
	if(CheckAttribute(&InterfaceStates,"ShowStealthAlarm")) {
		nShowStealthAlarm = sti(InterfaceStates.ShowStealthAlarm);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"STEALTH_ALARM_CHECKBOX", 2, 1, nShowStealthAlarm);
	
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
	
	// belamour --> 
	int nEnabledDIRECTSAIL = 0;
	if(CheckAttribute(&InterfaceStates,"DIRECTSAIL")) 
	{
		nEnabledDIRECTSAIL = sti(InterfaceStates.DIRECTSAIL);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"DIRECTSAIL_CHECKBOX", 2, 1, nEnabledDIRECTSAIL);
	
	int nEnabledCREWONDECK = 1;
	if(CheckAttribute(&InterfaceStates,"CREWONDECK")) 
	{
		nEnabledCREWONDECK = sti(InterfaceStates.CREWONDECK);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREWONDECK_CHECKBOX", 2, 1, nEnabledCREWONDECK);
	
	int nEnabledENHANCEDSAILING = 0;
	if(CheckAttribute(&InterfaceStates,"ENHANCEDSAILING")) 
	{
		nEnabledENHANCEDSAILING = sti(InterfaceStates.ENHANCEDSAILING);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ENHANCEDSAILING_CHECKBOX", 2, 1, nEnabledENHANCEDSAILING);

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
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"DYNAMICLIGHTS_CHECKBOX", 2, 1, nEnabledDYNAMICLIGHTS);
	// <-- belamour
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
	if(sNodName == "BTN_GAME") {
		if(iComIndex==ACTION_MOUSECLICK) {
			XI_WindowDisable("GAME_WINDOW", false);
			XI_WindowShow("GAME_WINDOW", true);
			XI_WindowShow("SCREEN_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			bControlsWin = false;
		}	
		if(iComIndex==ACTION_ACTIVATE) {
			XI_WindowDisable("GAME_WINDOW", false);
			XI_WindowShow("GAME_WINDOW", true);
			XI_WindowShow("SCREEN_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			bControlsWin = false;
			SetCurrentNode("MUSIC_SLIDE_FRAME");
		}
		return;
	}
	if(sNodName == "BTN_SCREEN") {
		if(iComIndex==ACTION_MOUSECLICK) {
			XI_WindowDisable("SCREEN_WINDOW", false);
			XI_WindowShow("GAME_WINDOW", false);
			XI_WindowShow("SCREEN_WINDOW", true);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			bControlsWin = false;
		}	
		if(iComIndex==ACTION_ACTIVATE) {
			XI_WindowDisable("SCREEN_WINDOW", false);
			XI_WindowShow("GAME_WINDOW", false);
			XI_WindowShow("SCREEN_WINDOW", true);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", false);
			bControlsWin = false;
			SetCurrentNode("HUD_SLIDE_FRAME");
		}
		return;
	}
	if(sNodName == "BTN_GRAPHICS") {
		if(iComIndex==ACTION_MOUSECLICK) {
			XI_WindowDisable("GRAPHICS_WINDOW", false);
			XI_WindowShow("GAME_WINDOW", false);
			XI_WindowShow("SCREEN_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", true);
			XI_WindowShow("CONTROLS_WINDOW", false);
			bControlsWin = false;
		}	
		if(iComIndex==ACTION_ACTIVATE) {
			XI_WindowDisable("GRAPHICS_WINDOW", false);
			XI_WindowShow("GAME_WINDOW", false);
			XI_WindowShow("SCREEN_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", true);
			XI_WindowShow("CONTROLS_WINDOW", false);
			bControlsWin = false;
			SetCurrentNode("GLOW_SLIDE_FRAME");
		}
		return;
	}
	if(sNodName == "BTN_CONTROLS") {
		if(iComIndex==ACTION_MOUSECLICK) {
			XI_WindowDisable("CONTROLS_WINDOW", false);
			XI_WindowShow("GAME_WINDOW", false);
			XI_WindowShow("SCREEN_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", true);
			bControlsWin = true;
			SetAlertMarksControls();
		}
		if(iComIndex==ACTION_ACTIVATE) {
			XI_WindowDisable("CONTROLS_WINDOW", false);
			XI_WindowShow("GAME_WINDOW", false);
			XI_WindowShow("SCREEN_WINDOW", false);
			XI_WindowShow("GRAPHICS_WINDOW", false);
			XI_WindowShow("CONTROLS_WINDOW", true);
			bControlsWin = true;
			SetCurrentNode("LOC_MOUSE_SENSITIVITY_FRAME");
			SetAlertMarksControls();
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
	if(sNodName == "LEFTCHANGE_HERB") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP ) 
		{
			if(iGrassQuality > 2) return;
			iGrassQuality += 1;
			SetFormatedText("HERB_DESCRIP_TEXT", HerbDes(iGrassQuality));
		}
		return;
	}	
	if(sNodName == "RIGHTCHANGE_HERB") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP) 
		{
			if(iGrassQuality < 1) return;
			iGrassQuality -= 1;
			SetFormatedText("HERB_DESCRIP_TEXT", HerbDes(iGrassQuality));
		}
		return;
	}
	if(sNodName == "LEFTCHANGE_FONT") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP ) 
		{
			if(iFontType < 1) return;
			iFontType -= 1;
			SetFormatedText("FONT_DESCRIP_TEXT", FontDes(iFontType));
			InterfaceStates.FontType = iFontType;
		}
		return;
	}	
	if(sNodName == "RIGHTCHANGE_FONT") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP) 
		{
			if(iFontType > 1) return;
			iFontType += 1;
			SetFormatedText("FONT_DESCRIP_TEXT", FontDes(iFontType));
			InterfaceStates.FontType = iFontType;
		}
		return;
	}
	if(sNodName == "LEFTCHANGE_MOREINFO") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP ) 
		{
			if(iMoreInfo < 1) return;
			iMoreInfo -= 1;
			SetFormatedText("MOREINFO_DESCRIP_TEXT", MoreInfoDes(iMoreInfo));
			InterfaceStates.MoreInfo = iMoreInfo;
		}
		return;
	}	
	if(sNodName == "RIGHTCHANGE_MOREINFO") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP) 
		{
			if(iMoreInfo > 0) return;
			iMoreInfo += 1;
			SetFormatedText("MOREINFO_DESCRIP_TEXT", MoreInfoDes(iMoreInfo));
			InterfaceStates.MoreInfo = iMoreInfo;
		}
		return;
	}	
	if(sNodName == "LEFTCHANGE_CONTROLS_MODE") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP ) 
		{
			if(iControlsMode < 1) return;
			iControlsMode -= 1;
			SetFormatedText("CONTROLS_MODE_DESCRIP_TEXT", ControlsModeDes(iControlsMode));
			ControlSettings(iControlsMode);
			InterfaceStates.ControlsMode = iControlsMode;
		}
		return;
	}	
	if(sNodName == "RIGHTCHANGE_CONTROLS_MODE") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP) 
		{
			if(iControlsMode > 0) return;
			iControlsMode += 1;
			SetFormatedText("CONTROLS_MODE_DESCRIP_TEXT", ControlsModeDes(iControlsMode));
			ControlSettings(iControlsMode);
			InterfaceStates.ControlsMode = iControlsMode;
		}
		return;
	}	
	if(sNodName == "LEFTCHANGE_COMPASS_POS") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP ) 
		{
			if(iCompassPos < 1) return;
			iCompassPos -= 1;
			SetFormatedText("COMPASS_POS_DESCRIP_TEXT", CompassPosDes(iCompassPos));
			InterfaceStates.CompassPos = iCompassPos;
		}
		return;
	}	
	if(sNodName == "RIGHTCHANGE_COMPASS_POS") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP) 
		{
			if(iCompassPos > 0) return;
			iCompassPos += 1;
			SetFormatedText("COMPASS_POS_DESCRIP_TEXT", CompassPosDes(iCompassPos));
			InterfaceStates.CompassPos = iCompassPos;
		}
		return;
	}
	if(sNodName == "LEFTCHANGE_CONTROLS_TIPS") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP ) 
		{
			if(iControlsTips < 1) return;
			iControlsTips -= 1;
			SetFormatedText("CONTROLS_TIPS_DESCRIP_TEXT", ControlsTipsDes(iControlsTips));
			InterfaceStates.ControlsTips = iControlsTips;
		}
		return;
	}	
	if(sNodName == "RIGHTCHANGE_CONTROLS_TIPS") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP) 
		{
			if(iControlsTips > 2) return;
			iControlsTips += 1;
			SetFormatedText("CONTROLS_TIPS_DESCRIP_TEXT", ControlsTipsDes(iControlsTips));
			InterfaceStates.ControlsTips = iControlsTips;
		}
		return;
	}	
	if(sNodName == "LEFTCHANGE_SHIPMARKS") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP ) 
		{
			if(iEnabledShipMarks < 1) return;
			iEnabledShipMarks -= 1;
			SetFormatedText("SHIPMARKS_DESCRIP_TEXT", EnabledShipMarksDes(iEnabledShipMarks));
			InterfaceStates.EnabledShipMarks = iEnabledShipMarks;
		}
		return;
	}	
	if(sNodName == "RIGHTCHANGE_SHIPMARKS") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP) 
		{
			if(iEnabledShipMarks > 1) return;
			iEnabledShipMarks += 1;
			SetFormatedText("SHIPMARKS_DESCRIP_TEXT", EnabledShipMarksDes(iEnabledShipMarks));
			InterfaceStates.EnabledShipMarks = iEnabledShipMarks;
		}
		return;
	}	
	if(sNodName == "LEFTCHANGE_DIFFICULTY") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP) 
		{
			if(CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true) 
			{
				if(iDifficulty > 9) return;
			}
			if(iDifficulty < 3) return;
			iDifficulty -= 2;
			SetFormatedText("DIFFICULTY_DESCRIP_TEXT", DifficultyDes(iDifficulty));
			InterfaceStates.Difficulty = iDifficulty;
		}
		return;
	}
	if(sNodName == "RIGHTCHANGE_DIFFICULTY") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP) 
		{
			if(CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true) // в процессе игры
			{ 
				if(iDifficulty > 7) return;
			} 
			else 
			{
				if(iDifficulty > 9) return;
			}
			iDifficulty += 2;
			SetFormatedText("DIFFICULTY_DESCRIP_TEXT", DifficultyDes(iDifficulty));
			InterfaceStates.Difficulty = iDifficulty;
		}
		return;
	}
	if(sNodName == "LEFTCHANGE_ARCADESAILS") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP ) 
		{
			if(iArcadeSails > 0) return;
			iArcadeSails += 1;

			SetFormatedText("ARCADESAILS_DESCRIP_TEXT", ArcadeSailsDes(iArcadeSails));
			InterfaceStates.ArcadeSails = iArcadeSails;
		}
		return;
	}	
	if(sNodName == "RIGHTCHANGE_ARCADESAILS") 
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP) 
		{
			if(iArcadeSails < 1) return;
			iArcadeSails -= 1;
			SetFormatedText("ARCADESAILS_DESCRIP_TEXT", ArcadeSailsDes(iArcadeSails));
			InterfaceStates.ArcadeSails = iArcadeSails;
		}
		return;
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
	if(sNodName == "STEALTH_ALARM_CHECKBOX") 
	{
		{
			InterfaceStates.ShowStealthAlarm = bBtnState;
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
	// belamour -->
	if(sNodName == "DIRECTSAIL_CHECKBOX") 
	{
		{ 
			InterfaceStates.DIRECTSAIL = bBtnState;
		}
	}
	
	if(sNodName == "CREWONDECK_CHECKBOX") 
	{
		{ 
			InterfaceStates.CREWONDECK = bBtnState;
		}
	}
	
	if(sNodName == "ENHANCEDSAILING_CHECKBOX") 
	{
		{ 
			InterfaceStates.ENHANCEDSAILING = bBtnState;
		}
	}
	if(sNodName == "ROTATESKY_CHECKBOX") 
	{
		{ 
			InterfaceStates.ROTATESKY = bBtnState;
		}
	}
	if(sNodName == "DYNAMICLIGHTS_CHECKBOX") 
	{
		{ 
			InterfaceStates.DYNAMICLIGHTS = bBtnState;
		}
	}
	// <-- belamour
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
	// belamour перспектива МК
	if(sNodeName == "SEACAMPERSP_SLIDE")
	{
		InterfaceStates.SEACAMPERSP = fVal*100;
		return;
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

string HerbDes(int gq)
{
	string sText = " "; 
	switch (iGrassQuality)
	{
		case 0: sText =  XI_ConvertString("Herb Large"); break;
		case 1: sText =  XI_ConvertString("Herb Medium"); break;
		case 2: sText =  XI_ConvertString("Herb Small"); break;
		case 3: sText =  XI_ConvertString("Herb None"); break;
	}
	return sText;
}

string FontDes(int ft)
{
	string sText = " "; 
	switch (iFontType)
	{
		case 0: sText =  XI_ConvertString("Font_Italic"); break;
		case 1: sText =  XI_ConvertString("Font_Normal"); break;
		case 2: sText =  XI_ConvertString("Font_Mixed"); break;
	}
	return sText;
}

string MoreInfoDes(int mi)
{
	string sText = " "; 
	switch (iMoreInfo)
	{
		case 0: sText =  XI_ConvertString("FightMode"); break;
		case 1: sText =  XI_ConvertString("Always"); break;
	}
	return sText;
}

string ControlsModeDes(int cm)
{
	string sText = " "; 
	switch (iControlsMode)
	{
		case 0: sText =  XI_ConvertString("Key Layout1"); break;
		case 1: sText =  XI_ConvertString("Key Layout2"); break;
	}
	return sText;
}

string CompassPosDes(int csm)
{
	string sText = " "; 
	switch (iCompassPos)
	{
		case 0: sText =  XI_ConvertString("CompassBot"); break;
		case 1: sText =  XI_ConvertString("CompassTop"); break;
	}
	return sText;
}

string ControlsTipsDes(int ct)
{
	string sText = " "; 
	switch (iControlsTips)
	{
		case 0: sText =  XI_ConvertString("Off"); break;
		case 1: sText =  XI_ConvertString("BaseTips"); break;
		case 2: sText =  XI_ConvertString("ExtendedTips"); break;
		case 3: sText =  XI_ConvertString("AllTips"); break;
	}
	return sText;
}

string EnabledShipMarksDes(int esm)
{
	string sText = " "; 
	switch (iEnabledShipMarks)
	{
		case 0: sText =  XI_ConvertString("Off"); break;
		case 1: sText =  XI_ConvertString("All"); break;
		case 2:	sText =  XI_ConvertString("OnlyChars"); break;
	}
	return sText;
}

string ArcadeSailsDes(int as)
{
	string sText = " "; 
	switch (iArcadeSails)
	{
		case 0: sText =  XI_ConvertString("SailType_2"); break;
		case 1: sText =  XI_ConvertString("SailType_1"); break;
	}
	return sText;
}

string DifficultyDes(int df)
{
	string sText = " "; 
	switch (iDifficulty)
	{
		case 1: sText =  XI_ConvertString("m_Complexity_1"); break;
		case 2: sText =  XI_ConvertString("m_Complexity_2"); break;
		case 3: sText =  XI_ConvertString("m_Complexity_3"); break;
		case 4: sText =  XI_ConvertString("m_Complexity_4"); break;
		case 5: sText =  XI_ConvertString("m_Complexity_5"); break;
		case 6: sText =  XI_ConvertString("m_Complexity_6"); break;
		case 7: sText =  XI_ConvertString("m_Complexity_7"); break;
		case 8: sText =  XI_ConvertString("m_Complexity_8"); break;
		case 9: sText =  XI_ConvertString("m_Complexity_9"); break;
		case 10: sText =  XI_ConvertString("m_Complexity_10"); break;
	}
	return sText;
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
	else DeleteAttribute(&objControlsState, "keygroups.AltPressedGroup" + "." + sControl);

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
                else if(sti(aFriend.(sName)) == 2) BI_CheckWASD(arControlGroup.(sName) == CI_GetKeyName(keyCode));
                else if(sti(aFriend.(sName)) == 3) BI_CheckWASDSail(arControlGroup.(sName) == CI_GetKeyName(keyCode));
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
	g_bToolTipStarted = true;
	string sHeader = " ";
	string sNode = GetCurrentNode();

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	switch (sNode)
	{
		case "GAMMA_SLIDE":
			sHeader = XI_ConvertString("gamma");
			sText1 = XI_ConvertString("gamma_descr");
		break;
		case "BRIGHT_SLIDE":
			sHeader = XI_ConvertString("Brightness");
			sText1 = XI_ConvertString("brightness_descr");
		break;
		case "CONTRAST_SLIDE":
			sHeader = XI_ConvertString("Contrast");
			sText1 = XI_ConvertString("Contrast_descr");
		break;
		
		case "GLOW_SLIDE":
			sHeader = XI_ConvertString("Glow");
			sText1 = XI_ConvertString("Glow_descr");
			sText2 = XI_ConvertString("PostProcessOnly");
		break;
		
		case "SEA_DETAILS_SLIDE":
			sHeader = XI_ConvertString("Sea Detail");
			sText1 = XI_ConvertString("Sea Detail_descr");
		break;

		case "FOLIAGE_DRAW_DISTANCE_SLIDE":
			sHeader = XI_ConvertString("Foliage Draw Distance");
			sText1 = XI_ConvertString("Foliage Draw Distance_descr");
		break;

		case "GRASS_DRAW_DISTANCE_SLIDE":
			sHeader = XI_ConvertString("Grass Draw Distance");
			sText1 = XI_ConvertString("Grass Draw Distance_descr");
		break;
		
		case "HERB_DESCRIP_TEXT":
			sHeader = XI_ConvertString("Herb Quantity");
			sText1 = XI_ConvertString("Herb Quantity_descr");
		break;

		case "MUSIC_SLIDE":
			sHeader = XI_ConvertString("Music Volume");
			sText1 = XI_ConvertString("Music Volume_descr");
		break;

		case "SOUND_SLIDE":
			sHeader = XI_ConvertString("Sound Volume");
			sText1 = XI_ConvertString("Sound Volume_descr");
		break;

		case "DIALOG_SLIDE":
			sHeader = XI_ConvertString("Dialog Volume");
			sText1 = XI_ConvertString("Dialog Volume_descr");
		break;
		
		case "CLASSIC_SOUNDSCENE_CHECKBOX":
			sHeader = XI_ConvertString("Classic Soundscene");
			sText1 = XI_ConvertString("Classic Soundscene_descr");
		break;
		
		case "DIFFICULTY_DESCRIP_TEXT":
			sHeader = XI_ConvertString("m_Complexity");
			sText1 = GetRPGText("LevelComplexity_desc");
		break;

		case "FONT_DESCRIP_TEXT":
			sHeader = XI_ConvertString("Questbook Font");
			sText1 = XI_ConvertString("Questbook Font_descr");
		break;

		case "MOREINFO_DESCRIP_TEXT":
			sHeader = XI_ConvertString("More Info");
			sText1 = XI_ConvertString("More Info_descr");
		break;

		case "ARCADESAILS_DESCRIP_TEXT":
			sHeader = XI_ConvertString("Sailing Mode");
			sText1 = GetRPGText("ArcadeSailMode_desc");
		break;

		case "ALWAYS_RUN_CHECKBOX":
			sHeader = XI_ConvertString("Always Run");
			sText1 = XI_ConvertString("Always Run_descr");
		break;

		case "ADVANCEDCHANGE_CHECKBOX":
			sHeader = XI_ConvertString("AdvancedChangeControls");
			sText1 = XI_ConvertString("AdvancedChangeControls_descr");
		break;

		case "CONTROLS_MODE_DESCRIP_TEXT":
			sHeader = XI_ConvertString("Key Layout");
			sText1 = XI_ConvertString("Key Layout_descr");
		break;
		
		case "CONTROLS_LIST":
			sHeader = XI_ConvertString("Button Settings");
			sText1 = XI_ConvertString("Button Settings_descr");
			sText2 = XI_ConvertString("Button Settings_descr2");
		break;

		case "COMPASS_POS_DESCRIP_TEXT":
			sHeader = XI_ConvertString("CompassPos");
			sText1 = XI_ConvertString("CompassPos_descr");
		break;

		case "CONTROLS_TIPS_DESCRIP_TEXT":
			sHeader = XI_ConvertString("Show Controls");
			sText1 = XI_ConvertString("Show Controls_descr");
		break;

		case "INVERT_MOUSE_CHECKBOX":
			sHeader = XI_ConvertString("Invert Vertical Mouse Control");
			sText1 = XI_ConvertString("Invert Vertical Mouse Control_descr");
		break;

		case "LOC_MOUSE_SENSITIVITY_SLIDE":
			sHeader = XI_ConvertString("Location Mouse Sensitivity");
			sText1 = XI_ConvertString("Location Mouse Sensitivity_descr");
		break;

		case "SEA_MOUSE_SENSITIVITY_SLIDE":
			sHeader = XI_ConvertString("Sea Mouse Sensitivity");
			sText1 = XI_ConvertString("Sea Mouse Sensitivity_descr");
		break;

		case "BATTLE_MODE_CHECKBOX":
			sHeader = XI_ConvertString("Show battle mode");
			sText1 = XI_ConvertString("Show battle mode_descr");
		break;

		case "STEALTH_ALARM_CHECKBOX":
			sHeader = XI_ConvertString("Show stealth alarm");
			sText1 = XI_ConvertString("Show stealth alarm_descr");
		break;
		
		case "CHAR_STRING_CHECKBOX":
			sHeader = XI_ConvertString("Show characters strings");
			sText1 = XI_ConvertString("Show characters strings_descr");
		break;

		case "TUTORIAL_CHECKBOX":
			sHeader = XI_ConvertString("Show tutorial");
			sText1 = XI_ConvertString("Show tutorial_descr");
		break;
		
		case "AUTOSAVE_CHECKBOX":
			sHeader = XI_ConvertString("AutoSave Mode");
			sText1 = XI_ConvertString("AutoSave Mode_descr");
		break;

		case "AUTOSAVE2_CHECKBOX":
			sHeader = XI_ConvertString("AutoSave Mode2");
			sText1 = XI_ConvertString("AutoSave Mode2_descr");
		break;

		case "QUESTMARK_CHECKBOX":
			sHeader = XI_ConvertString("QuestMark Mode");
			sText1 = XI_ConvertString("QuestMark Mode_descr");
		break;

		case "SHIPMARKS_DESCRIP_TEXT":
			sHeader = XI_ConvertString("ShipMark Mode");
			sText1 = XI_ConvertString("ShipMark Mode_descr");
		break;

		case "SIMPLESEA_CHECKBOX":
			sHeader = XI_ConvertString("SimpleSea Mode");
			sText1 = XI_ConvertString("SimpleSea Mode_descr");
		break;
		// belamour
		case "DIRECTSAIL_CHECKBOX":
			sHeader = XI_ConvertString("DIRECTSAIL Mode");
			sText1 = XI_ConvertString("DIRECTSAIL Mode_descr");
		break;

		case "ENHANCEDSAILING_CHECKBOX":
			sHeader = XI_ConvertString("ENHANCEDSAILING Mode");
			sText1 = XI_ConvertString("ENHANCEDSAILING Mode_descr");
		break;
		
		case "CREWONDECK_CHECKBOX":
			sHeader = XI_ConvertString("CREWONDECK Mode");
			sText1 = XI_ConvertString("CREWONDECK Mode_descr");
		break;
		
		case "ROTATESKY_CHECKBOX":
			sHeader = XI_ConvertString("ROTATESKY Mode");
			sText1 = XI_ConvertString("ROTATESKY Mode_descr");
			sText2 = XI_ConvertString("ROTATESKYatt Mode_descr");
		break;
		
		case "DYNAMICLIGHTS_CHECKBOX":
			sHeader = XI_ConvertString("DYNAMICLIGHTS Mode");
			sText1 = XI_ConvertString("DYNAMICLIGHTS Mode_descr");
		break;
		
		case "SEACAMPERSP_SLIDE":
			sHeader = XI_ConvertString("SEACAMPERSP_SLIDE Mode");
			sText1 = XI_ConvertString("SEACAMPERSP_SLIDE Mode_descr");
			sText2 = XI_ConvertString("NeedToExitFromSea");
		break;

		case "HUD_SLIDE":
			sHeader = XI_ConvertString("HUD_SLIDE Mode");
			sText1 = XI_ConvertString("HUD_SLIDE Mode_descr");
		break;	
		
	}

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void HideInfo()
{
	if(g_bToolTipStarted) {
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("OK_BUTTON");
	}
}

bool KeyAlreadyUsed(string sGrpName, string sControl, string sKey, bool bAltPress, ref controlReplacement)
{
	bool bAPgroup = false;
	if(CheckAttribute(&objControlsState,"keygroups.AltPressedGroup." + sControl))
	{
		bAPgroup = objControlsState.keygroups.AltPressedGroup.(sControl) == sKey;
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
	SetFormatedText("CONTROLS_MODE_DESCRIP_TEXT", ControlsModeDes(iControlsMode));
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
	
	iGrassQuality = 0;
	SetFormatedText("HERB_DESCRIP_TEXT", HerbDes(iGrassQuality));
	
	InterfaceStates.FontType = 0;
	iFontType = 0;
	SetFormatedText("FONT_DESCRIP_TEXT", FontDes(iFontType));

	InterfaceStates.MoreInfo = 0;
	iMoreInfo = 0;
	SetFormatedText("MOREINFO_DESCRIP_TEXT", MoreInfoDes(iMoreInfo));

	InterfaceStates.ControlsMode = 0;
	iControlsMode = 0;
	SetFormatedText("CONTROLS_MODE_DESCRIP_TEXT", ControlsModeDes(iControlsMode));
	ControlSettings(iControlsMode);

	InterfaceStates.AdvancedChange =  0;
	bAdvancedChange = false;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ADVANCEDCHANGE_CHECKBOX", 2, 1, 0);

	InterfaceStates.CompassPos = 0;
	iCompassPos = 0;
	SetFormatedText("COMPASS_POS_DESCRIP_TEXT", CompassPosDes(iCompassPos));

	InterfaceStates.ControlsTips = 2;
	iControlsTips = 2;
	SetFormatedText("CONTROLS_TIPS_DESCRIP_TEXT", ControlsTipsDes(iControlsTips));

	InterfaceStates.ArcadeSails = 1;
	iArcadeSails = 1;
	SetFormatedText("ARCADESAILS_DESCRIP_TEXT", ArcadeSailsDes(iArcadeSails));

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

	GameInterface.nodes.SEACAMPERSP_SLIDE.value = 0.25;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "SEACAMPERSP_SLIDE", 0, 0.25);
	
	InterfaceStates.ShowBattleMode = 0
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"BATTLE_MODE_CHECKBOX", 2, 1, 0);

	InterfaceStates.ShowStealthAlarm = 1
	// iShowStealthAlarm = 1;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"STEALTH_ALARM_CHECKBOX", 2, 1, 1);
	
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

	InterfaceStates.EnabledShipMarks = 1;
	iEnabledShipMarks = 1;
	bDrawBars = 1;
	SetFormatedText("SHIPMARKS_DESCRIP_TEXT", EnabledShipMarksDes(iEnabledShipMarks));

	InterfaceStates.SimpleSea = 0;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SIMPLESEA_CHECKBOX", 2, 1, 0);
	
	InterfaceStates.DIRECTSAIL = 0;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"DIRECTSAIL_CHECKBOX", 2, 1, 0);
	
	InterfaceStates.CREWONDECK = 1;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREWONDECK_CHECKBOX", 2, 1, 1);
	
	InterfaceStates.ROTATESKY = 0;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ROTATESKY_CHECKBOX", 2, 1, 0);
	
	InterfaceStates.DYNAMICLIGHTS = 1;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"DYNAMICLIGHTS_CHECKBOX", 2, 1, 1);
	
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
void BI_CheckWASD(bool bSame)
{
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
        makearef(arControlGroup, objControlsState.keygroups.PrimaryLand);
        bSame = arControlGroup.ChrForward     == arControlGroup.BICommandsUp   ||
                arControlGroup.ChrBackward    == arControlGroup.BICommandsDown ||
                arControlGroup.ChrStrafeLeft  == arControlGroup.BICommandsLeft ||
                arControlGroup.ChrStrafeRight == arControlGroup.BICommandsRight;
        makearef(arControlGroup, objControlsState.keygroups.FightModeControls);
        bSame = bSame ||
                arControlGroup.ChrForward     == arControlGroup.BICommandsUp   ||
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

void BI_CheckWASDSail(bool bSame)
{
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
        makearef(arControlGroup, objControlsState.keygroups.PrimaryLand);
        bSame = arControlGroup.Ship_SailUp    == arControlGroup.BICommandsUp   ||
                arControlGroup.Ship_SailDown  == arControlGroup.BICommandsDown ||
                arControlGroup.Ship_TurnLeft  == arControlGroup.BICommandsLeft ||
                arControlGroup.Ship_TurnRight == arControlGroup.BICommandsRight;
        makearef(arControlGroup, objControlsState.keygroups.FightModeControls);
        bSame = bSame ||
                arControlGroup.Ship_SailUp    == arControlGroup.BICommandsUp   ||
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
