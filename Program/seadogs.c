// BOAL 07.09.03  Mods on_off mode -->
#include "_LSC_on_off.h"
// BOAL 07.09.03  Mods on_off mode <--
#include "storm-engine\layers.h"
#include "storm-engine\events.h"
#include "globals.c"
#include "animals.c"
#include "NumberUtilities.c" // Warship 26.07.09. Работа с числами
#include "RandomUtilities.c" // Legendary edition Работа с рандомом
#include "sea_ai\sea.c"
#include "ships\ships.c"
#include "Encounters\Encounters.c"
#include "worldmap\worldmap.c"
#include "locations\locations.c"
#include "Loc_ai\LAi_init.c"
#include "store\goods.h"
#include "cannons\cannons.c"
#include "nations\nations.c"
#include "particles.c"
#include "characters\characters.c"
#include "interface\interface.h"
#include "store\storeutilite.c"
#include "dialog.c"
#include "quests\quests.c"
#include "islands\islands.c"
#include "colonies\colonies.c"
#include "reload.c"
#include "battle_interface\loginterface.c"
#include "calendar.c"
#include "teleport.c"
#include "utils.c"
#include "weather\WhrWeather.c"
#include "controls\controls.c"
#include "ITEMS\items.h"
#include "ITEMS\itemLogic.c"
#include "ITEMS\items_utilite.c"
#include "store\store.h"
#include "interface\interface.c"
#include "fleet_cmds.c"
#include "controls\controls_func.c" // belamour процессирование контролок 
#include "migrations.c"
#include "achievements.c"
#include "ships\ships_generator.c"


extern void InitBaseCannons();
extern void InitCharacters();
extern void InitBaseInterfaces();

extern void wdmInitWorldMap();
extern void InitGoods();
extern void InitStores();
extern int  InitItems();
extern void InitCharactersTables();
extern void InitCharactersNames();
extern void InitPiratesNames();
extern void InitGeneratorNames();
extern void InitIndianNames(); //Jason имена индейцев
extern void CreateCharacters();

extern void ActiveF4Control(); // boal debuger
extern void ActiveF5Control(); // boal debuger
extern void ActiveF7Control(); // boal debuger
extern void ActiveF10Control(); // boal debuger
extern void ActiveF12Control(); // boal debuger
extern void ActiveINSERTControl(); // boal debuger

native float Bring2RangeNoCheck(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Bring2Range(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Clampf(float fValue);
native float Degree2Radian(float fDegree);
native int RDTSC_B();
native int RDTSC_E(int iRDTSC);

native int SetTexturePath(int iLevel, string sPath);
native int SetGlowParams(float fBlurBrushSize, int Intensivity, int BlurPasses);
native int RPrint(int x, int y, string sPrint);
native int GetTexture(string fileName);
native void ReleaseTexture(int texId);

native int GetSteamEnabled();
native int GetDLCenabled(int enable);
native int GetDLCCount();
native int GetDLCData(int id);
native int DLCStartOverlay(int id);
native int SetAchievement(string id);
native int GetAchievement(string id);
native int SetStat(string id, int value);
native int GetStat(string id);
native int StoreStats();
native int ClearAchievement(string id);
native int ResetStats(int bAchievementsToo);
native bool IsVerified();
native bool Verify();
native string GetPersonaName();
native int GetAppID();
native bool IsSteamDeck();
native bool IsVirtualKeyboardShowing();
// Virtual Keyboard Mode:
// 0 - Single Line (Enter closes the keyboard)
// 1 - Multiple Lines (Enter makes a new line)
// 2 - Email ('@' character is on last row)
// 3 - Numeric (only numbers, 0123456789)
native bool ShowSteamVirtualKeyboard(int iVKMode, int iTextFieldX, int iTextFieldY, int iTextFieldWidth, int iTextFieldHeight);
// GetOverlaysInfo function usage example:
// {
//     object itemsInfo[2]; // MUST BE of size [2] !!!
//     int itemsInfoSize = GetOverlaysInfo(&itemsInfo);
//     for (int i = 0; i < itemsInfoSize; i++) {
//         string itemId = itemsInfo[i].itemId;
//         string itemPath = itemsInfo[i].itemPath;
//         // itemId: Steam UGC ID of the item (int64 as a string)
//         // itemPath: Full absolute path to the item's content directory (somewhere inside steamapps)
//         //           (^ can be used in FINDFILESINTODIRECTORY!)
//     }
// }
native int GetOverlaysInfo(ref paOutOverlaysInfo);
native bool GameOverlayToWebPage(string url);
//GameOverlayToWebPage("https://steamcommunity.com/app/2230980/workshop/");

#libriary "script_libriary_test"
#libriary "dx9render_script_libriary"
#libriary "SteamApiScriptLib"

#event_handler(NEW_GAME_EVENT,"NewGame");
#event_handler(GAME_OVER_EVENT,"GameOverE");
#event_handler("Control Activation","ProcessControls");
#event_handler("MainMenuKey","ProcessMainMenuKey");
#event_handler("InterfaceKey","ProcessInterfaceKey");
#event_handler("CameraPosAng","ProcessCameraPosAng");
#event_handler("Cheat","ProcessCheat");
#event_handler("SeaDogs_ClearSaveData", "ClearLocationsSaveData");
#event_handler("StopQuestCheckProcessFreeze","ProcessStopQuestCheckProcessFreeze"); // boal 240804

float fHighPrecisionDeltaTime;	

void ProcessStopQuestCheckProcessFreeze() // boal 240804
{
    bQuestCheckProcessFreeze = false;
    wdmLockReload            = false;
    QuestsCheck(); // выполнить отложенные

    if (rand(20) == 10) // 16.01.06 не помню уже зачем разлочивал ГГ, но на деле мешает до квестам, но если где повиснет, то спасет ф2
    {
    	DoQuestCheckDelay("pchar_back_to_player", 0.5); // если в диалоге залочило, вернём управление
    }
}

void ProcessCheat()
{
	string sCheatName;
	ref mc;
	sCheatName = GetEventData();
	mc = GetMainCharacter();

	switch(sCheatName)
	{
		case "Immortal":
			if(LAi_IsImmortal(GetMainCharacter()))
			{				
				LAi_SetImmortal(GetMainCharacter(), false);
				Log_SetStringToLog("God mode OFF");
			}else{
				
				LAi_SetImmortal(GetMainCharacter(), true);
				Log_SetStringToLog("God mode ON");
			}
		break;
		case "ShotGun":
			if(globalSGMode != false)
			{
				globalSGMode = false;
				Log_SetStringToLog("Shotgun mode OFF");
			}else{
				globalSGMode = true;
				Log_SetStringToLog("Shotgun mode ON");
			}
		break;

		case "Gold":
			mc.money = sti(mc.money) + 100000;
			Log_SetStringToLog(" + 100000 G");
		break;
		case "Skill":
			mc.skill.freeskill = 1;
	
			mc.skill.freeskill = sti(mc.skill.freeskill) + 50;
			Log_SetStringToLog(" + 50 SP");
		break;
		case "Reputation":
			mc.reputation = REPUTATION_NEUTRAL;
			Log_SetStringToLog("Reputation Set to NEUTRAL");
		break;
		case "Morale":

		break;
		case "Encounters":
			if(CheckAttribute(mc,"worldmapencountersoff") == 0)
			{
				mc.worldmapencountersoff = "1";
				Log_SetStringToLog("Worldmap encounters OFF");
			}
			else
			{
				if(mc.worldmapencountersoff == "1") 
				{
					mc.worldmapencountersoff = "0";
					Log_SetStringToLog("Worldmap encounters ON");
				}
				else 
				{
					mc.worldmapencountersoff = "1";
					Log_SetStringToLog("Worldmap encounters OFF");
				}
			}
		break;
		case "MainCharacter":
			mc.model	= "Danielle";
			mc.sex = "woman";
			mc.FaceId = 30;
			mc.model.animation = "woman";
			mc.model.height = 1.75;
		break;
		case "soundoff":
			SendMessage(&Sound,"ll",MSG_SOUND_SET_ENABLED,0);
			Log_SetStringToLog("Sound OFF");
		break;
	}
}

object Camera;

void ProcessCameraPosAng()
{
	Camera.Pos.x = GetEventData();
	Camera.Pos.y = GetEventData();
	Camera.Pos.z = GetEventData();

	Camera.Ang.x = GetEventData();
	Camera.Ang.y = GetEventData();
	Camera.Ang.z = GetEventData();
}

void proc_break_video()
{
	trace("proc_break_video()");
	if (sti(InterfaceStates.videoIdx) != 1)
	{
		//InterfaceStates.videoIdx = -1;
		//Event("ievntEndVideo");
	}
}

// специально очень тупое имя, чтобы ловить тех кто будет менять имя этой функции...
string Yarr0x0319CrackCheckNik(string abc)
{
	return abc + abc + abc;
}

void Main()
{
	string abc = "a";
	if (Yarr0x0319CrackCheckNik(abc) != (abc + abc + abc))
	{
		trace("chicken god complete");
		ExitProgram();
	}

	iHudScale = BI_COMPARE_HEIGHT;
	
	ControlsInit(GetTargetPlatform(),true, 0);
	nTeleportLocation = 1;

	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();

	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	
	SetEventHandler("Control Activation","proc_break_video",0);
	InterfaceStates.Launched = false;
	SetEventHandler(EVENT_END_VIDEO,"Main_LogoVideo",0);
	InterfaceStates.videoIdx = 0;
	Event(EVENT_END_VIDEO);

	SetGlowParams(1.0, 50, 2);
}

void Main_InitGame()
{
	nTeleportLocation      = 1;
    bDisableLandEncounters = false;
	bDisableCharacterMenu  = false;
	bWorldAlivePause       = true;
	bPauseContrabandMetro  = false;
	bMonstersGen           = false;
	bLandEncountersGen     = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload         = false;
	bDisableMapEnter           = false;
	bDisableSailTo             = false;
	bEnableIslandSailTo        = false;
	bReloadCanBe               = false;
	bMapEnter                  = false;
	bQuestDisableMapEnter      = false;
    bAbordageStarted           = false;
    bCabinStarted              = false;
	bDeckBoatStarted           = false;
	LAi_IsCapturedLocation     = false;
	LAi_IsBoarding             = false;
	LAi_restoreStates          = false;
	LAi_boarding_process       = false;
	boarding_location          = -1;
	
	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();

	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
}
void Main_LogoVideo()
{
	int i = sti(InterfaceStates.videoIdx);
	switch(i)
	{

	case 0:
		InterfaceStates.videoIdx = 1;
		StartPostVideo("Blackmark",1);
	break;

	case 1:
		InterfaceStates.videoIdx = 2;
		StartPostVideo("Valkyrie",1);
	break;
	
	default:
		DelEventHandler(EVENT_END_VIDEO,"Main_LogoVideo");
		DeleteClass(&aviVideoObj);
		Event("DoInfoShower","sl","game prepare",true);
		SetEventHandler("frame","Main_Start",1);
	break;
	}
}

void Main_Start()
{
	ReloadProgressStart();
	
	DelEventHandler("Control Activation","proc_break_video");
	DelEventHandler("frame","Main_Start");
	if( GetTargetPlatform()=="pc" )	ControlsInit(GetTargetPlatform(),false, 0);
	
	ReloadProgressUpdate();
	InitGame();
	ReloadProgressUpdate();

	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0;
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;

	InterfaceStates.Buttons.Load.enable = true;
	
	Event("DoInfoShower","sl","game prepare",false);

	StartLanguageSetting(LanguageGetLanguage());
 	LoadPlayerProfileDefault(); // boal
	LaunchMainMenu();

	CharacterIsDead(GetMainCharacter());
	
	ReloadProgressEnd();
}

void SaveGame()
{
	string saveName = GetEventData();
	string saveData = GetEventData();
	DelEventHandler("evntSave","SaveGame");

	aref arTmp;
	if( !GetEntity(arTmp,"fader") )
	{
		//implemet interface
		// LaunchQuickSaveMenu();
		//pchar.version_number = 104;
		SaveEngineState(saveName);
		ISetSaveData(saveName,saveData);
	}

	//hide interface
	PostEvent("DoInfoShower",1,"sl","save game",false);
	DeleteEntitiesByType("scrshoter");
	HideQuickSaveMenu();
	SaveLastSavePathToCurrentProfile(saveName);
	SaveLastProfileToCurrentProfile();
	SaveCurrentShipToCurrentProfile();
	SaveCurrentCharactersToCurrentProfile();
	SaveCurrentMoneyToCurrentProfile();
	PostEvent("evntSaveGameAfter",2);// boal спец прерывание для автосейва
}

void LoadGame()
{
    PauseParticles(true); //fix вылета у форта
    // не помогло DeleteFortEnvironment();  //fix
    
	PauseAllSounds(); // boal fix
    ResetSound();  // fix
    // вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	
	string saveName = GetEventData();
	DelEventHandler("evntLoad","LoadGame");

	string retStr="";
	SendMessage(&GameInterface,"lse",MSG_INTERFACE_GET_SAVE_DATA,saveName,&retStr);
	if( retStr=="" ) {return;}

	DeleteEntities();
	ClearEvents();
	ClearPostEvents();
	SetTimeScale(1.0);
	TimeScaleCounter = 0;

    string loadScr="";
	loadScr = "loading\start_loading.tga";

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	SendMessage(&reload_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&reload_fader, "ls",FADER_PICTURE, loadScr);
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	ReloadProgressStart();
	pchar.savegamename = saveName;
	SetEventHandler("frame","LoadGame_continue",1);
	
	iCalculateSaveLoadCount("Load");
}

void LoadGame_continue()
{
	DelEventHandler("frame","LoadGame_continue");
	FreezeGroupControls(curKeyGroupName,true);
	LoadEngineState(pchar.savegamename);
}

void InterfaceDoExit()
{
	DelEventHandler("frame","InterfaceDoExit");
	InterfaceStates.Launched=false;
	if(sti(InterfaceStates.doUnFreeze)==true)
	{
		SendMessage(&GameInterface,"l",MSG_INTERFACE_RELEASE);
		if(!IsEntity(&aviVideoObj))
		{
			if( bSeaActive && !bAbordageStarted )
			{
				LayerFreeze(SEA_REALIZE,false);
				LayerFreeze(SEA_EXECUTE,false);
			}
			else
			{
				LayerFreeze(REALIZE,false);
				LayerFreeze(EXECUTE,false);
			}
		}
		DeleteAttribute(&GameInterface,"");
	}
	switch(interfaceResultCommand)
	{
		case RC_INTERFACE_FORTCAPTURE_EXIT:
			ReloadAfterFortCapture();
			break;

		case RC_INTERFACE_DO_NOTHING:
			break;
		case RC_INTERFACE_MAIN_MENU_EXIT:
			GameOverMainMenu();
			break;
		case RC_INTERFACE_DO_CHECK_UPDATES:
            break;		
		case RC_INTERFACE_DO_NEW_GAME:
			LaunchSelectCharacter();
		break;
		
		case RC_INTERFACE_DO_LOAD_GAME:
			if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
			{
				LaunchLoadGame(false);
			}
			else
			{
				LaunchLoadGame(true);
			}
			break;

		case RC_INTERFACE_DO_SAVE_GAME:
			LaunchSaveGame();
			break;

		case RC_INTERFACE_DO_OPTIONS:
			if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
			{
				LaunchOptionScreen(false);
			}
			else
			{
				LaunchOptionScreen(true);
			}
			break;
			
		case RC_INTERFACE_DO_CREDITS:
		    LaunchAboutScreen();
		break;

		case RC_INTERFACE_DO_RESUME_GAME:
		break;	
		
		case RC_INTERFACE_RANSACK_MAIN_EXIT:
			Return2SeaAfterAbordage();
		break;
		
		case RC_INTERFACE_CHARACTER_SELECT_EXIT:
			DeleteEntities();
			ClearEvents();
			SetEventHandler("frame","NewGame",1);
			InterfaceStates.doUnFreeze = false;
		break;
				
		case RC_INTERFACE_TO_CHAR:
			pchar = GetMainCharacter();
			LaunchCharacter(pchar);
		break;

		case RC_INTERFACE_INVENTORY:
			LaunchInventory();
		break;
				
		case RC_INTERFACE_TO_SHIP:
			LaunchShipState();
		break;
				
		case RC_INTERFACE_TO_QUESTBOOK:
			LaunchQuestBook();
		break;

		case RC_INTERFACE_TO_TRADEBOOK:
			LaunchTradeBook();
		break;		

		case RC_INTERFACE_TO_CANNONS:
			ref NPChar;
			makeref(NPChar,CharacterRef);
			int iTest = FindColony(NPChar.City); // город магазина
			ref rColony = GetColonyByIndex(iTest);
			LaunchCannons(sti(rColony.StoreNum));
		break;
		
		case RC_INTERFACE_TO_SHIPYARD:
			makeref(NPChar,CharacterRef);
			LaunchShipyard(npchar);
		break;

		case RC_INTERFACE_MAPVIEW:
			LaunchMapViewScreen(); // Смотрим атлас карт
		break;

		case RC_INTERFACE_ABILITIES:
			LaunchAbilities(); // навыки
		break;
		
		case RC_INTERFACE_DEATH:
			LaunchDeath(); // смерть
		break;
		
		case RC_INTERFACE_NATIONRELATION:
			LaunchNationRelation(); // нации
		break;		
		
		case RC_INTERFACE_LAUNCH_GAMEMENU:
			LaunchGameMenuScreen();
			break;
	
		// boal -->
  		case RC_INTERFACE_DO_BOAL_BETA:
		    LaunchBoalBetaScreen();
        break;
  		case RC_INTERFACE_DEBUGER:
		    LaunchDebuderMenu();
        break;
		// boal <--
		
		// Warship -->
		case RC_INTERFACE_BEST_MAP:
			LaunchBestMapScreen(); // Смотрим отличную карту
		break;
		// <-- Warship
		case RC_INTERFACE_BLACKMARK_CHEAT:
		    LaunchCheatsMenu();
        break;
		
		case RC_INTERFACE_CHEAT_CHARACTER:
		    LaunchCheatsCharcter();
        break;
		
		case RC_INTERFACE_CHEAT_ITEMS:
		    LaunchCheatsItems();
        break;
	}
}

void EngineLayersOffOn(bool on)
{
	on = !on;
	if( on ) {
		LayerFreeze(REALIZE,on);
		LayerFreeze(EXECUTE,on);
		LayerFreeze(SEA_REALIZE,on);
		LayerFreeze(SEA_EXECUTE,on);
	} else {
		if(bSeaActive && !bAbordageStarted) {
			LayerFreeze(SEA_REALIZE,on);
			LayerFreeze(SEA_EXECUTE,on);
		} else {
			LayerFreeze(REALIZE,on);
			LayerFreeze(EXECUTE,on);
		}
	}
}

string seadogs_saveFrom = "";

void OnSave()
{
	seadogs_saveFrom = "";
	if(IsEntity(&worldMap) != 0)
	{
		seadogs_saveFrom = "world map";
	}
	else
	{
		if(IsEntity(&AISea) != 0)
		{
			Sea_Save();
			seadogs_saveFrom = "sea";
		}
		else
		{
			int ldLoc = FindLoadedLocation();
			if(ldLoc >= 0)
			{
				seadogs_saveFrom = "location";
				SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_SETCHRPOSITIONS);
				LAi_SaveInfo();
				PostEvent("SeaDogs_ClearSaveData", 400, "a", &Locations[ldLoc]);
			}
			else
			{
				Trace("OnSave() -> unknow character location");
				return;
			}
		}
	}

	iCalculateSaveLoadCount("Save");
}

void ClearLocationsSaveData()
{
	aref loc = GetEventData();
	if (loc) SendMessage(loc, "l", MSG_LOCATION_CLRCHRPOSITIONS);
}

int actLoadFlag = 0;

void OnLoad()
{
	actLoadFlag = 1;
	
	if(iHudScale < 50) iHudScale = BI_COMPARE_HEIGHT;

	DeleteAttribute( pchar, "abordage_active_count" );
	FreezeGroupControls(curKeyGroupName,false);
	if(CheckAttribute(pchar,"questTemp.TrackNonStop")) DeleteAttribute(pchar,"questTemp.TrackNonStop");

	if( CharacterIsDead(pchar) ) {
		pchar.chr_ai.hp = 1.0;
	}

	//Nation_InitAfterLoading();
	ResetSound();

	//CreateClass("dummy");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		//InitBaseInterfaces_main();
		InitBaseInterfaces();
		InitInterfaceTables();
		UnloadSegment("Interface\BaseInterface.c");
	}
	
	ReloadProgressUpdate();
	
	DialogsInit();
	//IslandsInit();
	//LocationInit();

	ReloadProgressUpdate();

	InitCharacterEvents();
	ReloadProgressUpdate();

	QuestsInit();
	ReloadProgressUpdate();
	
	InitTeleport();
	ReloadProgressUpdate();
	
	InitParticles();
	ReloadProgressUpdate();
	
	ApplyMigrations();
	
	WeatherInit();
	ReloadProgressUpdate();

	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;

	ReloadProgressUpdate();
	ControlsInit(GetTargetPlatform(), false, 0);
	LoadGameOptions();

	if(seadogs_saveFrom == "location")
	{
		ref mainchar;
		mainchar = GetMainCharacter();
		// boal: лажа это!!  есть actLoadFlag  //mainchar.isload = 1;
		bool verifierReturn = Verifier_OnLoad();
		LoadMainCharacterInFirstLocation(mainchar.location,"", mainchar.location.from_sea);
		int ldLoc = FindLoadedLocation();
		if(ldLoc >= 0 && !verifierReturn)
		{
			SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_TLPCHRPOSITIONS);
		}
	}
	else
	{
		if (seadogs_saveFrom == "sea")
		{
			Sea_Load();
 		}
		else
		{
			if(seadogs_saveFrom == "world map")
			{
				wdmLoadSavedMap();
			}
			else
			{
				Trace("Unknow seadogs_saveFrom == " + seadogs_saveFrom);
			}
		}
	}

	//ReloadEndFade();
	EngineLayersOffOn(true);
	//NewGame();
	DialogRun = false;
	InterfaceStates.Launched = false;
	
	ReloadProgressUpdate();

	PerkLoad();

	// ReloadProgressUpdate();
	// LoadGameOptions();

	ReloadProgressEnd();

    // fix by Hokkins
    BattleInterface.ShifInfoVisible = InterfaceStates.enabledshipmarks;
    BattleInterface.battleborder.used = InterfaceStates.ShowBattleMode;

	if( CheckAttribute(&InterfaceStates,"WorldSituationUpdateStep") &&
		sti(InterfaceStates.WorldSituationUpdateStep) < 10 )
	{
		Event("EvSituationsUpdate", "l", sti(InterfaceStates.WorldSituationUpdateStep));
	}

	actLoadFlag = 0;
	////
	
	iCalculateSaveLoadCount("Load");
	
	String sCondition;
	for(int i=0; i<MAX_GAMEMODE_CONDITIONS; i++)
	{
		sCondition = GameModeConditions[i];
		if(sCondition == "") continue;
		SetEventHandler(sCondition, sCondition, 0); // Обновим евент, т.к. терся
		Log_TestInfo("Обновлено прерывание - " + sCondition);
		if(sCondition == "JunglesSitBand_InFlameLocator")
		{
			CreateFireParticles("Sit", "KosterFlame");
			Log_TestInfo("Обновлен партикл огня");
		}
	}
}

void NewGame()
{
	DeleteEntities();
	DelEventHandler("frame","NewGame");

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	SendMessage(&reload_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	//SendMessage(&reload_fader, "ls",FADER_PICTURE, RandPhraseSimple("loading\battle.tga", "loading\Start_Loading.tga"));
	SendMessage(&reload_fader, "ls",FADER_PICTURE, "loading\Start_Loading.tga");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);

	SetEventHandler("frame","NewGame_continue",1);
}

void NewGame_continue()
{
	DeleteAttribute( pchar, "abordage_active_count" );  // это тут не рабоатет :)  Но и не мешает Boal

	ReloadProgressStart();

	DelEventHandler("frame","NewGame_continue");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	InitGame();
	
	ReloadProgressUpdate();
	
	CreateColonyCommanders();

	ReloadProgressUpdate();

	SetNames();
		
	ReloadProgressUpdate();
	
	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0; //boal
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;

	InterfaceStates.WorldSituationUpdateStep = 100;
	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;
	
	pchar = GetMainCharacter(); //fix
		
	initNewMainCharacter(); // все там
	
	ReloadProgressUpdate();
		
	InitPsHeros();   // boal 05/07/06 ПГГ	
	ReloadProgressUpdate();
	
    RumourInit();  //homo 23/06/06	
	ReloadProgressUpdate();
	
	ActivateTimeEvents();
	ReloadProgressUpdate();
			
	startGameWeather = true;
		
	InterfaceStates.startGameWeather = FindWeather("11 Hour");
	if (SandBoxMode) 
	{
		if(startHeroType == 4) 
		{
			LoadMainCharacterInFirstLocationGroup(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
			SetFunctionTimerCondition("SanBoxStatusCityRemove", 0, 0, 30, false);
			bGameMenuStart = false;
			//AddQuestRecordInfo("Guide_AtSea", "1");
			//AddQuestRecordInfo("Guide_OnLand", "1");
			DoQuestFunctionDelay("Tutorial_CameraControlFP", 2.5);
		}
		else LoadMainCharacterInFirstLocationGroup("Ship_deck_Low", "goto", "goto7");
	}
    	
	UpdateCrewInColonies(); // пересчет наёмников в городах
	
	ReloadProgressEnd();
}

void InitGame()
{	
	InitSound();
	ReloadProgressUpdate();

	DeleteSeaEnvironment();
	if(LoadSegment("worldmap\worldmap_init.c"))
	{
		wdmInitWorldMap();
		UnloadSegment("worldmap\worldmap_init.c");
	}
    ReloadProgressUpdate();

    InitPerks();
    ReloadProgressUpdate();
    
	IslandsInit();
	ReloadProgressUpdate();
	
	LocationInit();
	ReloadProgressUpdate();
	
	DialogsInit();
	ReloadProgressUpdate();
	
	InitTeleport();
	ReloadProgressUpdate();
	
	InitParticles();
	ReloadProgressUpdate();

    if(LoadSegment("items\initItems.c"))
	{
		InitItems();
		UnloadSegment("items\initItems.c");
	}
	ReloadProgressUpdate();

	GenerateGenerableItems(); // <-- ugeen генерация предметов
	ReloadProgressUpdate();
	
	CharactersInit();
	ReloadProgressUpdate();
	
	ColoniesInit();
	ReloadProgressUpdate();
	
	if(LoadSegment("store\initStore.c"))
	{
		InitStores();
		UnloadSegment("store\initStore.c");
	}
	ReloadProgressUpdate();

	QuestsInit();
	ReloadProgressUpdate();
	
	SeaAIGroupsInit();
	ReloadProgressUpdate();
	
	InitQuestMapEncounters();
	ReloadProgressUpdate();

	ResetQuestMovie();
	ReloadProgressUpdate();
	
	LoadGameOptions();
	ReloadProgressUpdate();

	InfoShowSetting();
}

int counter = 0;
void ProcessControls()
{
	string _ControlName = GetEventData();
	Process_Controls(_ControlName);
}

void Teleport(int step)
{
	nTeleportLocation = nTeleportLocation + step;
	if(nTeleportLocation >=	nLocationsNum) nTeleportLocation = 1;
	if(nTeleportLocation <=	0) nTeleportLocation = nLocationsNum - 1;
	
	sTeleportLocName = Locations[nTeleportLocation].id;
	Trace("Teleport to '" + sTeleportLocName + "'");

	ReleaseSound(0);
	ClearEvents();
	ClearPostEvents();
	DeleteEntities();
	SetEventHandler("frame","NewGame",1);
}

void ProcessMainMenuKey()
{
	if (interfacestates.buttons.resume.enable == "1")
	{
		//LaunchMainMenu();
		LaunchGameMenuScreen();
	}
}
// вызов меню по Ф2
void ProcessInterfaceKey()
{
	if(bMenuEnter()) LaunchSelectMenu();
}

bool bMenuEnter() // доступность меню F2
{
	if(CharacterIsDead(GetMainCharacter())) return false;
	if(bSeaActive && !bAbordageStarted) 
	{
		if(CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0) return false;
	} 
	else 
	{
		if(SendMessage(GetMainCharacter(),"ls",MSG_CHARACTER_EX_MSG,"CheckFightMode") != 0) return false;
		if(CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0) return false;
	}
	if(bDisableCharacterMenu) return false;// boal
	if(bAbordageStarted && !bCabinStarted && !bDeckBoatStarted) return false;
	if(loadedLocation.type == "underwater") return false; // belamour фикс прогулок под водой
	if(CheckAttribute(pchar,"chr_ai.type") && pchar.chr_ai.type != "player") return false;
	if(questMovieIsLockPlayerCtrl) return false;
	return true;
}

// ===> Sith выход в главное меню
void GameOverMainMenu()
{
    if (bSeaActive && !bAbordageStarted)
    {
		PauseParticles(true); //fix вылета у форта
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	bMainMenu = true; // вышли в меню из игры
	pchar.mainmenu = true; // вышли в меню из игры
	GameOver("mainmenu");
}
// <===
void GameOverE()
{
	// вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		PauseParticles(true); //fix вылета у форта
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	GameOver("sea");
	// DeleteSeaEnvironment();
}

void GameOver(string sName)
{
	ref mc;
	int nSelect;
	string sFileName;
	// ResetSoundScheme();
	PauseAllSounds();
	ResetSound();
	EngineLayersOffOn(false);
	
	mc = GetMainCharacter();
	
	ClearEvents();
	ClearPostEvents();
	DeleteEntities();

	if(sti(InterfaceStates.Launched)) {
		UnloadSegment(Interfaces[CurrentInterface].SectionName);
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	InterfaceStates.showGameMenuOnExit = false;
	InterfaceStates.Buttons.Resume.enable = false;
	InterfaceStates.Buttons.Save.enable = false;

	InitSound();
	SetEventHandler(EVENT_END_VIDEO,"LaunchMainMenu_afterVideo",0);
    trace("GameOver " + sName);							   
	switch(sName)
	{
		case "sea":
			InterfaceStates.Death = true;							 
			InterfaceStates.DeathPic = "loading\seadeath.tga";				
			LaunchDeath();
		break;

		case "boarding":
			InterfaceStates.Death = true;							 
			InterfaceStates.DeathPic = "loading\seadeath.tga";
			DeleteSeaEnvironment();
			LaunchDeath();
		break;

		case "land":
			InterfaceStates.Death = true;							 
			InterfaceStates.DeathPic = "loading\death.tga";
			LaunchDeath();
		break;

		case "mutiny":
			InterfaceStates.Death = true;							 
			InterfaceStates.DeathPic = "loading\finalbad2.tga";	
			LaunchDeath();
		break;

		case "town":
			InterfaceStates.Death = true;							 
			InterfaceStates.DeathPic = "loading\finalbad1.tga";	
			LaunchDeath();
		break;

		case "blood":
			InterfaceStates.Death = true;							 
			InterfaceStates.DeathPic = "loading\finalbad1.tga";	
			// StartPictureAsVideo( "loading\finalbad2.tga", 5.3 );
			// PlayStereoOGG("music_death");
			LaunchDeath();
		break;
		
		case "complete_bad": 
			InterfaceStates.Death = true;	
			InterfaceStates.MainMenu.InstantCredits = true;
			StartPictureAsVideo( "loading\Start_Loading.tga", 3.0 );
		break;

		case "complete":
			// StartPostVideo("credits",1);
			InterfaceStates.MainMenu.InstantCredits = true;
			StartPictureAsVideo( "loading\Start_Loading.tga", 3.0 );
		break;

		case "mainmenu":
			// InterfaceStates.Death = true;										 
			StartPictureAsVideo( "loading\Start_Loading.tga", 3.0 );
		break;
	}

    reload_location_index = -1;

    DeleteSeaEnvironment();

    InterfaceStates.BackEnvironmentIsCreated = false;

    LayerDelObject(EXECUTE, &InterfaceBackScene);
    LayerDelObject(REALIZE, &InterfaceBackScene);

    if(isEntity(&InterfaceBackScene))
    {
        DeleteClass(&InterfaceBackScene);
	}
	DeleteAttribute( &PlayerProfile, "name" );
	LoadGameOptions();
}

string its(int iNumber)
{
	string sText = iNumber;
	return sText;
}

// тяжкая игра - сайв токо в церкви 17.03.05 boal
bool QuickSaveGameEnabledHardcore()
{
    bool TmpBool = false;
    ref mchref = GetMainCharacter();
	if (bHardcoreGame)
	{
		int idxLoadLoc = FindLoadedLocation();
	    if( idxLoadLoc!=-1 )
	    {
	        if (CheckAttribute(&Locations[idxLoadLoc], "type"))
	        {
	            if (Locations[idxLoadLoc].type == "church" || Locations[idxLoadLoc].id == "GloriaChurch")
	            {
	                TmpBool = true;
	            }
				// belamour legendary edition
				if(Locations[idxLoadLoc].id == "Judgement_church") TmpBool = true;
	        }
	    }
    }
    else
    {
        TmpBool = true;
    }

    return TmpBool;
}

bool CheckBattleSeaSaveEnabled()
{
	return bSeaBattleSave;
}


bool CheckSaveGameEnabled()
{
    bool TmpBool = true;
    ref mchref = GetMainCharacter();
	
    if (CheckAttribute(&InterfaceStates, "Buttons.Save.enable")) 
	{
		if(InterfaceStates.Buttons.Save.enable != 1) 
		{
			TmpBool = false;
		}
	} 
	else 
	{
		TmpBool = false;
	}
	
	if(CheckAttribute(loadedLocation, "type") && loadedLocation.type == "underwater") 
	{
		TmpBool = false; // belamour запрет в подводной локации
	}
	
	if (bAbordageStarted) {TmpBool = false;}

	if(LAi_IsBoardingProcess()) {TmpBool = false;}

	if( CharacterIsDead(mchref) ) {TmpBool = false;}
		
	if(LAi_IsFightMode(mchref) && MOD_SKILL_ENEMY_RATE > 1) {TmpBool = false;} 
	
	if(bDisableMapEnter && !CheckBattleSeaSaveEnabled() && bSeaActive) {TmpBool = false;} 
	
	if (TmpBool)
	{
		int idxLoadLoc = FindLoadedLocation();
	    if (idxLoadLoc != -1 )
	    {
	        if (Locations[idxLoadLoc].id == "Ship_deck" || Locations[idxLoadLoc].id == "Deck_Near_Ship") // сайв на палубе глюкавый
	        {
	            TmpBool = false;
	        }
	    }
	}
    return TmpBool;
}

// Статистика по сэйвам/лоадам
// Просто чтоб код был в одном месте. _SaveLoad - только "Save" или "Load". Метод вернет общее кол-во загрузок/сохранения
int iCalculateSaveLoadCount(string _SaveLoad)
{
	int iCount;
	ref MChref = GetMainCharacter();
	string sAttrName = _SaveLoad + "Count";	
	iCount = sti(MChref.SystemInfo.(sAttrName));
	iCount++;
	MChref.SystemInfo.(sAttrName) = iCount;
	return iCount;
}

void SaveLastSavePathToCurrentProfile(string path) {
    object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
    opt.LastSavePath = path;
    SaveSavedOptionsEx(&opt, "SAVE\currentprofile");
}

string GetLastSavePathFromCurrentProfile() {
    object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
    if (!CheckAttribute(&opt, "LastSavePath")) {
        return "";
    }
    
    return opt.LastSavePath;
}

void SaveLastProfileToCurrentProfile() {
    string name = "Player";
    if (CheckAttribute(&PlayerProfile, "name")) {
        name = PlayerProfile.name;
    }
    
    object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
    opt.LastProfile = name;
    SaveSavedOptionsEx(&opt, "SAVE\currentprofile");
}

string GetLastProfileFromCurrentProfile() {
    object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
    if (!CheckAttribute(&opt, "LastProfile")) {
        return "Player";
    }
    
    return opt.LastProfile;
}

void SaveCurrentShipToCurrentProfile() {
	object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
    
	DeleteAttribute(&opt, "ship");
	if (pchar.ship.type != SHIP_NOTUSED) {
		aref ship;
		makearef(ship, opt.ship);
		
		ref realShip = GetRealShip(sti(pchar.ship.type));
		CopyAttributes(ship, realShip);
		ship.flag = pchar.nation;
	}
	
    SaveSavedOptionsEx(&opt, "SAVE\currentprofile");
}

object GetCurrentShipFromCurrentProfile() {
	object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
	
	object ship;
	if (!CheckAttribute(&opt, "ship")) {
		return ship;
	}
	
	aref shipFrom;
	makearef(shipFrom, opt.ship);
	CopyAttributes(&ship, shipFrom);
	return ship;
}

void CopyCharacterAppearance(aref to, aref from) {
	to.id = from.id;
	to.sex = from.sex;
	to.model = from.model;
	to.model.animation = from.model.animation;
	
	if (CheckAttribute(from, "equip.blade")) {
		to.equip.blade = from.equip.blade;
		GiveItem2Character(to, from.equip.blade);
	}
	
	if (CheckAttribute(from, "equip.gun")) {
		to.equip.gun = from.equip.gun;
		GiveItem2Character(to, from.equip.gun);
	}
}

void SaveCurrentCharactersToCurrentProfile() {
	object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
	
	DeleteAttribute(&opt, "characters");
	aref chars, character;
	makearef(chars, opt.characters);
	
	makearef(character, chars.mc);
	//CopyAttributes(character, pchar);
	CopyCharacterAppearance(character, pchar);
	
	int offCount = 0;
	int idx;
	ref chr;
	object offUsed;
	string id, attrName;
	
	int gfIdx = -1;
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) {
		gfIdx = GetCharacterIndex("Mary");
	}
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) {
		gfIdx = GetCharacterIndex("Helena");
	}
	// Log_info(""+gfIdx);
	
	for(int i = 1; i <= 3; i++) {
		idx = GetOfficersIndex(pchar, i);
		if (idx < 0 || idx == gfIdx) {
			continue;
		}
		chr = GetCharacter(idx);
		id = chr.id;
		
		// фильтр несовместимых анимаций
		if (chr.model.animation != "man" && chr.model.animation != "man_B") {
			continue;
		}
		
		attrName = "off" + (offCount + 1);
		makearef(character, chars.(attrName));
		//CopyAttributes(character, chr);
		CopyCharacterAppearance(character, chr);
		
		offUsed.(id) = true;
		offCount++;
	}
	
	int passQty = GetPassengersQuantity(pchar);
	for (i = 0; i < passQty; i++) {
		if (offCount >= 3) {
			break;
		}
		
		idx = GetPassenger(pchar, i);
		if (idx < 0 || idx == gfIdx) {
			continue;
		}
		chr = GetCharacter(idx);
		id = chr.id;
		
		// фильтр несовместимых анимаций
		if (chr.model.animation != "man" && chr.model.animation != "man_B") {
			continue;
		}
		
		// это уже сидящий абордажник
		if (CheckAttribute(&offUsed, id)) {
			continue;
		}
		
		// пленник
		if (CheckAttribute(chr, "prisoned") && chr.prisoned == true) {
			continue;
		}
		
		// не офф
		if (!GetRemovable(chr)) {
			continue;
		}
		
		attrName = "off" + (offCount + 1);
		makearef(character, chars.(attrName));
		//CopyAttributes(character, chr);
		CopyCharacterAppearance(character, chr);
		
		offUsed.(id) = true;
		offCount++;
	}
	
	if (gfIdx >= 0) {
		makearef(character, chars.gf);
		//CopyAttributes(character, GetCharacter(gfIdx));
		CopyCharacterAppearance(character, GetCharacter(gfIdx));
	}
	
	SaveSavedOptionsEx(&opt, "SAVE\currentprofile");
}

object GetCurrentCharactersFromCurrentProfile() {
	object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
	
	object chars;
	if (!CheckAttribute(&opt, "characters")) {
		return chars;
	}
	
	aref charsFrom;
	makearef(charsFrom, opt.characters);
	CopyAttributes(&chars, charsFrom);
	return chars;
}

void SaveCurrentMoneyToCurrentProfile() {
	object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
	
	// карманы
	int money = 0;
	if (CheckAttribute(pchar, "money")) {
		trace("В карманах найдено " + pchar.money + " песо");
		money += sti(pchar.money);
	}
	
	int dublon = 0;
	if (CheckAttribute(pchar, "dublon")) {
		trace("В карманах найдено " + GetCharacterItem(pchar, "gold_dublon") + " дублонов");
		dublon += GetCharacterItem(pchar, "gold_dublon");
	}
	
	int cabinIdx = FindLocation(Get_My_Cabin());
	if (cabinIdx >= 0) {
		ref cabin = &locations[cabinIdx];
		for (int n = 1; n <= 4; n++) {
			string boxId = "box" + n;
			
			if (CheckAttribute(cabin, boxId)) {
				aref box;
				makearef(box, cabin.(boxId));
				
				if (CheckAttribute(box, "money")) {
					trace("В каюте в " + boxId + " найдено " + box.money + " песо");
					money += sti(box.money);
				}
				
				if (CheckAttribute(box, "items.gold_dublon")) {
					trace("В каюте в " + boxId + " найдено " + box.items.gold_dublon + " дублонов");
					dublon += sti(box.items.gold_dublon);
				}
			}
		}
	}

	if (CheckAttribute(pchar, "Quest.Deposits")) {
		aref deposits;
		makearef(deposits, pchar.Quest.Deposits);
		
		int depositsNum = GetAttributesNum(deposits);
		for (int i = 0; i < depositsNum; i++) {
			aref deposit = GetAttributeN(deposits, i);
			string depositName = GetAttributeName(deposit);
			
			if (CheckAttribute(deposit, "sum")) {
				if(HasSubStr(depositName, "_type1")) {
					trace("У ростовщика города " + GetCityName(deposit.City) + " найден вклад в размере " + deposit.sum + " песо");
					money += sti(deposit.sum);
				} else {
					trace("У ростовщика города " + GetCityName(deposit.City) + " найден вклад в размере " + deposit.sum + " дублонов");
					dublon += sti(deposit.sum);
				}
			}
		}
	}
	
	int total = money + 100 * dublon;
	trace("Итого " + money + " песо и " + dublon + " дублонов = " + total + " денег");
	opt.money = total;
	
	SaveSavedOptionsEx(&opt, "SAVE\currentprofile");
}

int GetCurrentMoneyFromCurrentProfile() {
	object opt;
    ReadSavedOptionsEx(&opt, "SAVE\currentprofile");
	
	if (!CheckAttribute(&opt, "money")) {
		return 0;
	}
	
	return sti(opt.money);
}
