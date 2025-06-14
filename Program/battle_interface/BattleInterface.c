#include "storm-engine\battle_interface\msg_control.h"
#include "storm-engine\sea_ai\script_defines.h"
#include "battle_interface\landinterface.c"
#include "battle_interface\TaskWindow\TaskWindow.c"
#include "battle_interface\ispyglass.c"
#include "battle_interface\reload_tables.c"
#include "battle_interface\utils.c"
#include "battle_interface\ActivePerksShow.c"
//#include "battle_interface\backgroundtask.c"
#include "battle_interface\WmInterface.c"

#define BI_ICONS_SHIPS_TEXTURE_NAME "interfaces\le\battle_interface\icons.tga"
#define BI_ICONS_TEXTURE_FIRST_MOD 6

#define BI_ICONS_ST_NONE			0
#define BI_ICONS_ST_MYSHIPS			1
#define BI_ICONS_ST_COMMAND			2
#define BI_ICONS_ST_TARGETING		3

#define BI_ICONS_TEXTURE_COMMAND	0
#define BI_ICONS_TEXTURE_SHIP1		1
#define BI_ICONS_TEXTURE_ABILITY	2

#define SAILDIR_POS_DIF             10000.0

#define FLAG_CMN		0	// общие флаги
#define FLAG_SHP		1	// адмиральские флаги
#define FLAG_FRT		2	// флаги для фортов и городских администраций
#define FLAG_MER		3	// торговые флаги
#define FLAG_WHT		4	// белые флаги
#define FLAG_QST		5	// квестовые флаги
#define FLAG_PER		6	// персональные флаги
#define	FLAG_PIR		7	// пиратские флаги

int bi_icons_ShowType;
int bi_icons_CommandMode;

int bi_idxSelectedPicture;

object BattleInterface;

bool bDisableSailTo = false;

bool bDisableMapEnter = false;

bool bReloadCanBe = false;
bool bMapEnter = false;
bool bSailTo=false;
bool bAttack=false;
bool bAbordage = false;
bool bDefend=false;

//speak interface
//bool bCanSpeak = false;

bool bEnableIslandSailTo = false;
bool bEnableSailToNotif = false;
bool bSailToNotifSuccess = false;

int BI_intRetValue;
int BI_retComValue;
int BI_ChargeState[5];
float BI_g_fRetVal;

int BI_intNRetValue[12];

object BI_objRetValue;
object objShipPointer;
// boal -->
bool boal_soundOn = true;
// boal <--
int rColor1, rColor2, rColor3, rColor4; // 1-2-центр/край заряжено, 3-4-центр/край разряжено
float fblindUpTime, fblindDownTime; // время возрастания/убывания

int numLine = 7; // количество строк в подсказках управления
string sAttr = "";
string sAttrDes = "";
string sAttrB = "";

#event_handler("evntRandomSailDmg","ProcessRandomSailDmg");
#event_handler("evntGetSailStatus","procGetSailStatus");
//#event_handler("NextDay","ProcessDayRepair");
#event_handler("GetSailTextureData","procGetSailTextureData");
#event_handler("EventMastFall","procMastFall");
#event_handler("evntGetSmallFlagData","procGetSmallFlagData");

#event_handler(SHIP_CREATE,"BI_CreateShip");
#event_handler("GetRiggingData","procGetRiggingData");

void InitBattleInterface()
{
	BI_InitializeCommands();
	bi_icons_CommandMode = 0;
	BattleInterface.comstate = 0;
	BattleInterface.SelCharacter = -1;
	bi_idxSelectedPicture = -1;
	BattleInterface.boardRadius = 50;
	BattleInterface.freeDistance = MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;

	SetParameterData();

	BattleInterface.blindSpeed = 0.003;
	BattleInterface.MaxWind = 30.0;
	BattleInterface.MaxShipSpeed = 20.0;
	if (iArcadeSails == 1) 
	{
		BattleInterface.ShipSpeedScaler = (1.0 / 2.5);
	} 
	else 
	{
		BattleInterface.ShipSpeedScaler = (1.0 / 1.0);
	}
	
	BattleInterface.ShowNavigator = InterfaceStates.BattleShow.Navigator;
	BattleInterface.ShowCommands = InterfaceStates.BattleShow.Command;
	BattleInterface.MainChrIndex = nMainCharacterIndex;
	CreateEntity(&BattleInterface,"battle_interface");
	DeleteAttribute(&BattleInterface,"CommandTextures");
	DeleteAttribute(&BattleInterface,"CommandShowParam");
	LayerAddObject(SEA_EXECUTE,&BattleInterface,-1);
	LayerAddObject(SEA_REALIZE,&BattleInterface,-1);
	
	SetEventHandler(SHIP_DELETE,"BI_DeleteShip",0);
	SetEventHandler(SHIP_DEAD,"BI_DeadShip",0);

	SetEventHandler("BI_CommandEndChecking","BI_CommandEndChecking",0);
	SetEventHandler("BI_LaunchCommand","BI_LaunchCommand",0);
	SetEventHandler("BI_GetChargeQuantity","BI_GetChargeQuantity",0);
	SetEventHandler("BI_SetPossibleCommands","BI_SetPossibleCommands",0);
	SetEventHandler("GetCurrentCharge","GetCurrentCharge",0);
	SetEventHandler("evntGetCharacterShipClass","biGetCharacterShipClass",0);
	SetEventHandler(BI_EVENT_SET_VISIBLE,"BI_CommandVisible",0);
	SetEventHandler(BI_EVENT_SET_SEA_STATE,"BI_SetSeaState",0);
	SetEventHandler(BI_EVENT_GET_DATA,"BI_GetData",0);
	SetEventHandler(BI_EVENT_CHECK_SHIPSTATE_SHOW,"BI_GetSSShow",0);
	SetEventHandler("evntGetLandData","BI_GetLandData",0);
	SetEventHandler(BI_EVENT_GET_FORT_RELATION,"BI_GetFortRelation",0);
	SetEventHandler(EVENT_CHANGE_COMPANIONS,"RefreshBattleInterface",0);
	SetEventHandler("BI_CallUpdateShip","BI_UpdateShip",0);
	SetEventHandler("frame","BI_Frame",1);
	SetEventHandler("evntPerkAgainUsable","BI_PerkAgainUsable",0);
	SetEventHandler("evntSetUsingAbility","procSetUsingAbility",0);
	SetEventHandler("evntCheckEnableLocator","procCheckEnableLocator",0);
	SetEventHandler("evntCheckEnableShip","procCheckEnableShip",0);
	SetEventHandler("evntGetSRollSpeed","procGetSRollSpeed",0);
	SetEventHandler("DoSailHole","ProcessSailDamage",0);
	SetEventHandler("evntBISelectShip","procBISelectShip",0);

	procLoadIntoNew(); // Проинитим таблицу активных перков
	SetEventHandler("Control Activation","BI_ProcessControlPress",0);
	SendMessage(&BattleInterface,"ll",BI_MSG_SHOW_EXT_INFO, bShowExtInfo());
	SendMessage(&BattleInterface,"ll",BI_MSG_SHOW_SHIP_STATES, bShowShipStates());
	CreateILogAndActions(LOG_FOR_SEA);
	ControlsDesc();	
	Log_SetActiveAction("Nothing");
	ResetTimeScale(); // boal
	bEnableSailToNotif = !bSailToEnable();
	
	if(CheckAttribute(pchar, "systeminfo.BLIoff"))
	{
		ChangeShowIntarface();
		DeleteAttribute(pchar, "systeminfo.BLIoff");
	}
}

ref BI_GetFortRelation()
{
	BI_intRetValue = BI_RELATION_NEUTRAL;
	aref arLoc = GetEventData();
	int chrIdx = Fort_FindCharacter(AISea.Island,"reload",arLoc.name);
	if(chrIdx>=0)
	{
		switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
		{
		case RELATION_FRIEND:	BI_intRetValue = BI_RELATION_FRIEND;	break;
		case RELATION_NEUTRAL:	BI_intRetValue = BI_RELATION_NEUTRAL;	break;
		case RELATION_ENEMY:	BI_intRetValue = BI_RELATION_ENEMY;		break;
		}
	}
	/*string sColony = arLoc.colonyname;
	if (BI_intRetValue == BI_RELATION_ENEMY || CheckForDeclineLoadToColony(sColony) == 1)
	{
		bCanSneak = true;
	}      */
	return &BI_intRetValue;
}

ref BI_GetSSShow()
{
	BI_intRetValue = false;
	int charIdx = GetEventData();
	switch( GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE) )
	{
	case CHEAP_SPYGLASS:	BI_intRetValue = false;	break;
	case COMMON_SPYGLASS:	BI_intRetValue = true;	break;
	case GOOD_SPYGLASS:		BI_intRetValue = true;	break;
	case SUPERIOR_SPYGLASS:	BI_intRetValue = true;	break;
	}
	return &BI_intRetValue;
}

void BI_CommandVisible()
{
	int visibleFlag = GetEventData();
	SendMessage(&BattleInterface,"ll",BI_SET_VISIBLE,visibleFlag);
}

int bi_nReloadTarget=-1;
bool biold_bCanEnterToLand = false;
bool biold_bAbordageShipCanBe = false;
bool biold_bAbordageFortCanBe = false;
bool biold_bReloadCanBe = false;
bool biold_bMapEnter = false;
bool bOldNotEnoughBalls = false;

void BI_Frame()
{
	bool bYesUpdateCommand = false;
	if(bNotEnoughBalls!=bOldNotEnoughBalls)
	{
		bOldNotEnoughBalls = bNotEnoughBalls;
		if(bNotEnoughBalls)
		{
			SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,true);
		}
		else
		{
			SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,false);
		}
	}

	if(biold_bAbordageShipCanBe!=bAbordageShipCanBe)
	{
		bYesUpdateCommand = true;
		biold_bAbordageShipCanBe = bAbordageShipCanBe;
	}
	if(biold_bAbordageFortCanBe!=bAbordageFortCanBe)
	{
		bYesUpdateCommand = true;
		biold_bAbordageFortCanBe = bAbordageFortCanBe;
	}
	if(biold_bCanEnterToLand!=bCanEnterToLand)
	{
		bYesUpdateCommand = true;
		biold_bCanEnterToLand = bCanEnterToLand;
	}
	if(biold_bReloadCanBe!=bReloadCanBe)
	{
		bYesUpdateCommand = true;
		biold_bReloadCanBe = bReloadCanBe;
	}
	if(biold_bMapEnter!=bMapEnter)
	{
		bYesUpdateCommand = true;
		biold_bMapEnter = bMapEnter;
	}
	if(bEnableSailToNotif && !bSailToNotifSuccess)
	{
		if(bSailToEnable())
		{
			bSailToNotifSuccess = true;
			notification(XI_ConvertString("SeaFastNote"), "SeaFast");
		}
	}

	if(bYesUpdateCommand)
	{
		BI_SetCommandMode(-1,-1,-1,-1);
	}

	if(bAbordageShipCanBe)
	{
		Log_SetActiveAction("Board");
		// boal -->
		if (boal_soundOn)
		{
		    boal_soundOn = false;
            PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard0.wav");
		}
		// boal <--
		return;
	}
	if(bAbordageFortCanBe)
	{
		Log_SetActiveAction("LandTroops");
		// boal -->
		if (boal_soundOn)
		{
		    boal_soundOn = false;
            PlaySound("interface\" + LanguageGetLanguage() + "\_Abandon0.wav");
		}
		// boal <--
		return;
	}
	if(bReloadCanBe)
	{
		Log_SetActiveAction("Reload");
		return;
	}
	if(bGlobalTutor)
	{
		if(CheckAttribute(pchar, "TutorialToDeck_1") ||
		   CheckAttribute(pchar, "TutorialToDeck_2") ||
		   CheckAttribute(pchar, "TutorialToPort"))
	   {
		Log_SetActiveAction("Deck");
		return;
	   }
	}
	if(bCanEnterToLand)
	{
		Log_SetActiveAction("Moor");
		// boal -->
		if (boal_soundOn)
		{
		    boal_soundOn = false;
            PlaySound("interface\_Yakordrop.wav");
		}
		// boal <--
		return;
	}
	// boal -->
	boal_soundOn = true;
	// boal <--
	if(bMapEnter)
	{
		Log_SetActiveAction("Map");
		return;
	}
	Log_SetActiveAction("Nothing");
}

void StartBattleInterface()
{
	bi_nReloadTarget = -1;
	bi_icons_ShowType = BI_ICONS_ST_MYSHIPS;
	BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
	BI_SetIslandData();
	InterfaceSpyGlassInit(false);
	objShipPointer.textures.friend = "interfaces\le\battle_interface\Friendly.tga";
	objShipPointer.textures.enemy = "interfaces\le\battle_interface\Enemy.tga";
	CreateEntity(&objShipPointer,"shippointer");
	LayerAddObject(SEA_EXECUTE,&objShipPointer,222222);
	LayerAddObject(SEA_REALIZE,&objShipPointer,-1);
	CannonsRangeRefresh();
    TW_Init();
}

void RefreshBattleInterface()
{
	BI_SetCommandMode(0,-1,-1,-1);
	SendMessage(&BattleInterface,"l",BI_MSG_REFRESH);
	BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
	CannonsRangeRefresh();
	SendMessage(&BattleInterface,"ll",BI_MSG_SHOW_EXT_INFO, bShowExtInfo());
}

void CannonsRangeRefresh()
{
	/*belamour legendary edition подсветка рэнджа установленных пушек:
	AI_MESSAGE_CANNONS_RANGE   "lllllffl"
	пушки заряжены:
	1 - цвет у борта, 2 - цвет по краям
	пушки разряжены:
	3 - цвет у борта, 4 - цвет по краям, 5 - время возрастания альфы, 6 - время затухания,
	! чем больше альфа, тем больше должны быть показатели 5 и 6
	7 - показывать/ не показывать дистанцию пушек
	*/
	if(bCannonsRangeShow)
	{
		rColor1 = argb(0,255,255,255);
		rColor3 = argb(0,255,0,0);
		fblindUpTime = 0.002;
		fblindDownTime = 0.002;
		if (Whr_IsNight()) { // цвета ночью
			rColor2 = argb(15,255,255,255);
			rColor4 = argb(55,255,0,0);
		} else { // цвета днём
			rColor2 = argb(25,255,255,255);
			rColor4 = argb(75,255,0,0);
		}
		SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, rColor1, rColor2, rColor3, rColor4, fblindUpTime, fblindDownTime, 1);
	}
}

void DeleteBattleInterface()
{
    ResetTimeScale(); // boal
    
	Log_SetActiveAction("Nothing");
	InterfaceSpyGlassRelease();

    DeleteClass(&BattleInterface);
	DeleteClass(&objShipPointer);
	DeleteClass(&objActivePerkShower);
	
	DelEventHandler(SHIP_DELETE, "BI_DeleteShip");
	DelEventHandler(SHIP_DEAD,"BI_DeadShip");
	DelEventHandler("BI_CommandEndChecking", "BI_CommandEndChecking");
	DelEventHandler("BI_LaunchCommand", "BI_LaunchCommand");
	DelEventHandler("BI_GetChargeQuantity","BI_GetChargeQuantity");
	DelEventHandler("BI_SetPossibleCommands","BI_SetPossibleCommands");
	DelEventHandler("GetCurrentCharge","GetCurrentCharge");
	DelEventHandler("evntGetCharacterShipClass","biGetCharacterShipClass");
	DelEventHandler(BI_EVENT_SET_VISIBLE,"BI_CommandVisible");
	DelEventHandler(BI_EVENT_SET_SEA_STATE,"BI_SetSeaState");
	DelEventHandler(BI_EVENT_GET_DATA,"BI_GetData");
	DelEventHandler(BI_EVENT_CHECK_SHIPSTATE_SHOW,"BI_GetSSShow");
	DelEventHandler("evntGetLandData","BI_GetLandData");
	DelEventHandler(BI_EVENT_GET_FORT_RELATION,"BI_GetFortRelation");
	DelEventHandler(EVENT_CHANGE_COMPANIONS,"RefreshBattleInterface");
	DelEventHandler("BI_CallUpdateShip","BI_UpdateShip");
	DelEventHandler("frame","BI_Frame");
	DelEventHandler("evntPerkAgainUsable","BI_PerkAgainUsable");
	DelEventHandler("evntSetUsingAbility","procSetUsingAbility");
	DelEventHandler("evntCheckEnableLocator","procCheckEnableLocator");
	DelEventHandler("evntCheckEnableShip","procCheckEnableShip");
	DelEventHandler("evntGetSRollSpeed","procGetSRollSpeed");
	DelEventHandler("Control Activation","BI_ProcessControlPress");
	DelEventHandler("DoSailHole","ProcessSailDamage");
	DelEventHandler("evntBISelectShip","procBISelectShip");

    TW_Close();
	// был сброс времени, выше поднял

	//DeleteClass(&BattleInterface);
	//DeleteClass(&objShipPointer);
}

ref BI_CommandEndChecking()
{
	BI_retComValue = 0;
	string comName = GetEventData();

	switch(comName)
	{
	// каюта
    case "BI_Cabin":
		BI_retComValue = 0;
		break;
	// выслать шлюпку для разговора --
	case "BI_Boat":
		BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT;
        BattleInterface.Commands.Boat.EffectRadius = DistanceToShipTalk;
		break;
	case "BI_Bomb":
		BI_retComValue = 0;
		break;
	case "cancel":
		BI_retComValue = -1;
		break;
	case "BI_Moor":
		BI_retComValue = 0;
		break;
	case "BI_SailTo":
		int iIsland = FindIsland(pchar.location);
		if(iIsland > 0 && !sti(Islands[iIsland].reload_enable))
		{
			bEnableIslandSailTo	= false;
		}
		if(bEnableIslandSailTo) {
            // LDH 25Oct17 broke long line into shorter ones, fix broken sail-to?
			BI_retComValue =  BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT;
            BI_retComValue += BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_NEUTRAL_FORT_SELECT+BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_DISEASED_TOWN;
            BI_retComValue += BI_COMMODE_NOTDISEASED_TOWN+BI_COMMODE_LAND_SELECT; //+BI_COMMODE_ALLLOCATOR_SELECT;
		} else {
			BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT;//+BI_COMMODE_ALLLOCATOR_SELECT;
		}
		if (bBettaTestMode || CheckAttribute(pchar, "Cheats.SeaTeleport"))
		{
		    BattleInterface.Commands.SailTo.EffectRadius	= 900000;
		}
  		else
  		{
			if(iIsland > 0 && CheckAttribute(&Islands[iIsland],"EffectRadius"))
			{
				BattleInterface.Commands.SailTo.EffectRadius = sti(Islands[iIsland].EffectRadius); 
			}
			else
			{
				string sSpyGlass = GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE);
				if(sSpyGlass != "")
				{
					ref rItm = ItemsFromID(sSpyGlass);
					BattleInterface.Commands.SailTo.EffectRadius	= 5000 + sti(rItm.radius);
				}
				else BattleInterface.Commands.SailTo.EffectRadius	= 5000; //boal
			}	
		}
		break;
	case "BI_Board":
		BI_retComValue = 0;
		break;
	case "BI_LandTroops":
		BI_retComValue = 0;
		break;
	case "BI_Map":
		BI_retComValue = 0;
		break;
	case "BI_Attack":
		BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
        BattleInterface.Commands.Attack.EffectRadius	= 2000; //boal
		break;
	case "BI_Abordage":
		BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT;
		BattleInterface.Commands.Abordage.EffectRadius	= 2000; //boal
		break;
	case "BI_Defend":
		BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		BattleInterface.Commands.Defend.EffectRadius	= 2000; //boal
		break;
	case "BI_SailAway":
		BI_retComValue = 0;
		break;
    case "BI_SailDir":
	    BI_SailDirIconSet();
		BI_retComValue = BI_COMMODE_USER_ICONS;
		break;
	case "BI_HeaveToDrift":
		BI_retComValue = 0;
		break;
	case "BI_Reload":
		BI_retComValue = 0;
		break;
	case "BI_Charge":
		BI_retComValue = BI_COMMODE_CANNON_CHARGE;
		break;
	case "BI_Speed":
        BI_SailSpeedIconSet();
		BI_retComValue = BI_COMMODE_USER_ICONS;
		break;
	case "BI_CompanionCommand":
		BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
		
	case "BI_Brander":
		BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
	case "BI_ImmediateReload":
		BI_retComValue = 0;
		break;
	case "BI_LightRepair":
		BI_retComValue = 0;
		break;		
	case "BI_InstantRepair":
		BI_retComValue = 0;
		break;
		
	case "BI_Turn180":
		BI_retComValue = 0;
		break;
		
	case "BI_Ability":
		BI_retComValue = BI_COMMODE_ABILITY_ICONS;
		break;

	case "BI_ImmDeath":
		BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_NEUTRAL_FORT_SELECT+BI_COMMODE_ENEMY_FORT_SELECT;
		BattleInterface.Commands.ImmediateDeath.EffectRadius	= 900000;
	break;

	case "BI_InstantBoarding":
		BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT;
	break;
	}

	return &BI_retComValue;
}
void BI_SailDirIconSet()
{
    BattleInterface.UserIcons.ui1.enable = false;
    BattleInterface.UserIcons.ui2.enable = false;
    BattleInterface.UserIcons.ui3.enable = false;

    BattleInterface.UserIcons.ui4.enable = true;
    BattleInterface.UserIcons.ui5.enable = true;
    BattleInterface.UserIcons.ui6.enable = true;
    BattleInterface.UserIcons.ui7.enable = true;
    BattleInterface.UserIcons.ui8.enable = true;
    BattleInterface.UserIcons.ui9.enable = true;
    BattleInterface.UserIcons.ui10.enable = true;
    BattleInterface.UserIcons.ui11.enable = true;
}

void BI_SailSpeedIconSet()
{
    BattleInterface.UserIcons.ui1.enable = true;
    BattleInterface.UserIcons.ui2.enable = true;
    BattleInterface.UserIcons.ui3.enable = true;

    BattleInterface.UserIcons.ui4.enable = false;
    BattleInterface.UserIcons.ui5.enable = false;
    BattleInterface.UserIcons.ui6.enable = false;
    BattleInterface.UserIcons.ui7.enable = false;
    BattleInterface.UserIcons.ui8.enable = false;
    BattleInterface.UserIcons.ui9.enable = false;
    BattleInterface.UserIcons.ui10.enable = false;
    BattleInterface.UserIcons.ui11.enable = false;
}

void BI_LaunchCommand()
{
	bool bOk;
	int charIdx = GetEventData();
	string commandName = GetEventData();
	int targetNum = GetEventData();
	string locName = GetEventData();
	ref chRef = GetCharacter(charIdx);
	if( LAi_IsDead(chRef) ) return;

	aref arFader;
	if( GetEntity(arFader,"fader") ) {return;}

	if(targetNum==-1 && locName=="cancel") {
		SendMessage(&BattleInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}
	if(commandName=="cancel") {
		SendMessage(&BattleInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}

	string alternativeCommand;
	if( CheckAttribute( &BattleInterface, "AbilityIcons."+commandName+".quest" ) )
	{
		alternativeCommand = commandName;
		commandName = "BI_UseItemAbilitie";
	}

	switch(commandName)
	{
    case "BI_Cabin":
        Sea_CabinStartNow();
		break;
	case "BI_Boat":
		// Warship 09.07.09 Мэри Селест
		// Второй раз на нее выслать шлюпку низя
		if(Characters[targetNum].id != "MaryCelesteCapitan" || PChar.QuestTemp.MaryCeleste != "OnDeck")
		{
			Sea_DeckBoatLoad(targetNum);
		}
		else
		{
			PlaySound("interface\knock.wav");
		}
    break;
	
	 case "BI_Bomb":
        if (GetCargoGoods(chRef, GOOD_POWDER) >= 200 && GetRemovable(chRef)) SetMineFree(chRef, 1); // fix ugeen 21.12.13
		else PlaySound("interface\knock.wav");
		break;
		
	case "BI_Charge":
		int chargeType=GOOD_BALLS;
		switch(targetNum)
		{
		case 1:
			//Log_SetStringToLog("Cannonballs");
			PlaySound("interface\" + LanguageGetLanguage() + "\_balls.wav");
			chargeType=GOOD_BALLS;
			break;
		case 2:
			//Log_SetStringToLog("Grapes");
			PlaySound("interface\" + LanguageGetLanguage() + "\_grapes.wav");
			chargeType=GOOD_GRAPES;
			break;
		case 3:
			//Log_SetStringToLog("Knippels");
			PlaySound("interface\" + LanguageGetLanguage() + "\_chain.wav");
			chargeType=GOOD_KNIPPELS;
			break;
		case 4:
			//Log_SetStringToLog("Bombs");
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs.wav");
			chargeType=GOOD_BOMBS;
			break;
		}
		Ship_ChangeCharge(chRef, chargeType);
		// исходим из того, что приказы через команды дают токо ГГ и его офам, офы выбирают какой снаряд, поэтому команду запоминаем для них
		chRef.ShipCannonChargeType = chargeType;

		// на будущее, не стирать!! !! ugeen
        if(chRef.id != pchar.id) 
        {
			if(CheckAttribute(chRef, "Ship.Cannons.chargeoverride") && chRef.Ship.Cannons.chargeoverride == chargeType) {
				// already set to request, so unset manual ball choice
				DeleteAttribute(chRef,"Ship.Cannons.chargeoverride");
				chRef.Ship.Cannons.chargeoverridecancel = 1;
				// Log_SetStringToLog(chRef.Ship.name + xiStr("MSG_AIShip_27"));
			} else {
				chRef.Ship.Cannons.chargeoverride = chargeType;
				// Log_SetStringToLog(chRef.Ship.name + xiStr("MSG_AIShip_28") + Goods[chargeType].name);
			}
		}
		
		break;
	case "BI_Map":
		if (bMapEnter)  // boal не помню уже зачем, в ВМЛ было
        {
            //pchar.location = "";
			Sea_MapLoad();
        }
        else
        {
            Log_Info(XI_ConvertString("NoMapAccess"));
        }
		break;
	case "BI_Moor":
		Sea_LandLoad();
		break;
	case "BI_Board":
		Sea_AbordageLoad(SHIP_ABORDAGE,true);
		break;
	case "BI_LandTroops":
		Sea_AbordageLoad(FORT_ABORDAGE,true);
		break;
	case "BI_SailAway":
		if (CheckAttribute(&characters[charIdx], "SeaAI.Task.Target"))  //fix
		{
			Ship_SetTaskRunAway(SECONDARY_TASK, charIdx, sti(characters[charIdx].SeaAI.Task.Target));
		}
		else
		{
			Ship_SetTaskRunAway(SECONDARY_TASK, charIdx, GetMainCharacterIndex()); // boal fix если вдруг нет, то от ГГ удаляться
		}
	break;
	case "BI_HeaveToDrift":
		Ship_SetTaskDrift(SECONDARY_TASK,charIdx);
		break;
	case "BI_Defend":
		Ship_SetTaskDefend(SECONDARY_TASK,charIdx,GetTargChrIndex(targetNum,locName));
		DeleteAttribute(chRef, "ShipCannonChargeType"); // флаг офов, чем пулять постоянно, ставится игроком командами, до след приказа Атака или конца снарядов
		break;
	case "BI_Attack":
		Ship_SetTaskAttack(SECONDARY_TASK,charIdx,GetTargChrIndex(targetNum,locName));
		DeleteAttribute(chRef, "ShipCannonChargeType"); // флаг офов, чем пулять постоянно, ставится игроком командами, до след приказа Атака или конца снарядов
	break;
	case "BI_Abordage":
		Ship_SetTaskAbordage(SECONDARY_TASK,charIdx,GetTargChrIndex(targetNum,locName));
	break;
	case "BI_Reload":
		if(bi_nReloadTarget!=-1)
		{
			LaunchTransferMain(chRef, GetCharacter(bi_nReloadTarget), "Transfer");
		}
		break;
	case "BI_SailTo":
		/*if(targetNum==-1)
		{ // приплыть в локатор с именем locName
			if( !IsEntity(&SailToFader) ) {SeaAI_SailToLocator(locName);}
		}
		else
		{ // догнать перса с индексом targetNum
			if( !IsEntity(&SailToFader) ) {SeaAI_SailToCharacter(targetNum);}
		} */
		// boal 09.02.2004 -->
	    if (bDisableMapEnter && !bBettaTestMode && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.MapClosedNoBattle") && !CheckAttribute(pchar, "Cheats.SeaTeleport"))//Jason
	    {
           PlaySound("interface\knock.wav");
	       break;
	    }
	    if (!CheckEnemyCompanionDistance2GoAway(false) && !bBettaTestMode && !CheckAttribute(pchar, "Cheats.SeaTeleport"))  // компаньон в беде
	    {
           PlaySound("interface\knock.wav");
	       break;
	    }
	    // boal 09.02.2004 <--
		if (targetNum == -1)
		{ // приплыть в локатор с именем locName
            bOk = true;

			if (MOD_SKILL_ENEMY_RATE >= 2 && !bBettaTestMode && !CheckAttribute(pchar, "Cheats.SeaTeleport"))
            {
                targetNum = Fort_FindCharacter(AISea.Island,"reload",locName);
                if (targetNum == -1)
                {
                    // тут нужна проверка на город-враг ищем форт по порту
                    targetNum = Fort_FindCharacterByPort(AISea.Island, locName);
                }
            }
			if (targetNum >= 0)
			{
				if (GetRelation(sti(pchar.index), targetNum) == RELATION_ENEMY && !CheckAttribute(&Characters[targetNum], "CanBeSailTo"))
				{
                  	if (sti(Characters[targetNum].Fort.Mode) == FORT_NORMAL)
					{
						bOk = false;
					}
				}
			}
			if (bOk)
   			{
    			if( !IsEntity(&SailToFader) ) {trace("SailToLocator : " + locName); SeaAI_SailToLocator(locName); }
			}
			else
			{
                PlaySound("interface\knock.wav");
			}
		}
		else
		{ // догнать перса с индексом targetNum
		    // boal плывем только к друзьям или спец персам (потопить пирата) -->
            if (GetRelation(sti(pchar.index), targetNum) != RELATION_ENEMY || CheckAttribute(&Characters[targetNum], "CanBeSailTo") || bBettaTestMode || CheckAttribute(pchar, "Cheats.SeaTeleport"))
            {
			    if( !IsEntity(&SailToFader) ) {SeaAI_SailToCharacter(targetNum); }
			}
			else
			{
                PlaySound("interface\knock.wav");
			}
			// boal плывем только к друзьям или спец персам (потопить пирата) <--
		}
		break;
	case "BI_Speed":
		switch(locName)
		{
		case "sail_none":
			Ship_SetSailState(charIdx,0.0);
		break;
		case "sail_midi":
			Ship_SetSailState(charIdx,0.5);
		break;
		case "sail_fast":
			Ship_SetSailState(charIdx,1.0);
		break;
		}
		break;
    case "BI_SailDir":
        float posX = stf(Characters[charIdx].Ship.Pos.x);
        float posZ = stf(Characters[charIdx].Ship.Pos.z);
        float fAng;
        switch(locName)
		{
			case "dir_n":
				posZ += SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
			break;
			case "dir_ne":
				fAng = PIm2 * 0.125;
				posX = posX + sin(fAng) * SAILDIR_POS_DIF;
				posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
			break;
			case "dir_e":
				posX += SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
			break;
			case "dir_se":
				fAng = PIm2 * 0.375;
				posX = posX + sin(fAng) * SAILDIR_POS_DIF;
				posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
			break;
			case "dir_s":
				posZ -= SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
			break;
			case "dir_sw":
				fAng = PIm2 * 0.625;
				posX = posX + sin(fAng) * SAILDIR_POS_DIF;
				posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
			break;
			case "dir_w":
				posX -= SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
			break;
			case "dir_nw":
				fAng = PIm2 * 0.875;
				posX = posX + sin(fAng) * SAILDIR_POS_DIF;
				posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
			break;
		}
        break;
	case "BI_CompanionCommand":
		BI_SetSpecCommandMode(BI_COMMODE_COMMAND_SELECT,-1,-1,targetNum,1);
		return;
		break;
	case "BI_ImmDeath":
		if(targetNum==-1)
		{ // смерть форта
			targetNum = Fort_FindCharacter(AISea.Island,"reload",locName);
			if(targetNum>=0)
			{
				Fort_SetAbordageMode(pchar, GetCharacter(targetNum));
			}
		}
		else
		{
			ShipDead(targetNum,KILL_BY_BALL,nMainCharacterIndex);
		}
		break;

	case "BI_InstantBoarding":
  		ActivateCharacterPerk(GetCharacter(charIdx),"InstantBoarding");
		CharacterPerkOff(GetCharacter(charIdx),"InstantBoarding");
		if( CheckSuccesfullBoard(GetCharacter(charIdx),GetCharacter(targetNum)) ) {
			Sea_AbordageStartNow(SHIP_ABORDAGE,targetNum,true,true);
		} else {
			Log_SetStringToLog( XI_ConvertString("failed to board") );
			Event("BI_LaunchCommand","lsls", charIdx, "BI_SailTo", targetNum, locName);
			return;
		}
		break;

	case "BI_Brander":
		//ActivateCharacterPerk(pchar,"Brander"); - многоразовый приказ
		Ship_SetTaskBrander(SECONDARY_TASK, charIdx, targetNum);
		break;
	case "BI_ImmediateReload":
		ActivateCharacterPerk(GetCharacter(charIdx),"ImmediateReload");
		break;
	case "BI_LightRepair":
		ActivateCharacterPerk(GetCharacter(charIdx),"LightRepair");
		ActivateSpecRepair(GetCharacter(charIdx),0);
		break;		
	case "BI_InstantRepair":
		ActivateCharacterPerk(GetCharacter(charIdx),"InstantRepair");
		ActivateSpecRepair(GetCharacter(charIdx),1);
		break;		
	case "BI_Turn180":
		ActivateCharacterPerk(GetCharacter(charIdx),"Turn180");
		Ship_Turn180(GetCharacter(charIdx));
		break;

	// items abilities
	case "BI_UseItemAbilitie":
		CompleteQuestName( BattleInterface.AbilityIcons.(alternativeCommand).quest, "");
	break;
	
	/*case "BI_Ability":
  		Event("evntSetUsingAbility","l", charIdx);
	break;*/
	}

	//BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
	BI_SetSpecCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1, 0);
}

void BI_SetIslandData()
{
    if( !CheckAttribute(AISea,"Island"))
	{
		trace("BI_SetIslandData - has bug");
		return; // boal 26.03.04 fix
	}
	int isln = FindIsland(AISea.Island);
	if(isln==-1) return;

	ref atmp;
	atmp = GetIslandByIndex(isln);
	SendMessage(&BattleInterface,"la",BI_MSG_SET_ISLAND,atmp);
}

void BI_UpdateShip()
{
	int charIndex = GetEventData();
	AddShipToInterface(charIndex);
}

void BI_CreateShip()
{
	int charIndex = GetEventData();
	//if(charIndex>=0) ClearActiveChrPerks(GetCharacter(charIndex));
	if( IsEntity(&BattleInterface) ) {
		AddShipToInterface(charIndex);
	}
}

void AddShipToInterface(int charIndex)
{
	if(charIndex==-1)
	{
		Trace("ERROR: Invalid character index for create ship");
		return;
	}
	ref chRef = GetCharacter(charIndex);
	int st = GetCharacterShipType(chRef);
	if( st==SHIP_NOTUSED )
	{
		Trace("WARNING!!! Character id = "+chRef.id+" hav`t ship.");
		return;
	}
	ref shipRef = GetRealShip(st);
	int myShip = false;
	int shipRelation = BI_RELATION_NEUTRAL;
	switch( SeaAI_GetRelation(charIndex,nMainCharacterIndex) )
	{
	case RELATION_FRIEND:
		shipRelation = BI_RELATION_FRIEND;
		break;
	case RELATION_ENEMY:
		shipRelation = BI_RELATION_ENEMY;
		break;
	}

	for(int i=0; i<COMPANION_MAX; i++)
	{
		if(GetCompanionIndex(pchar,i) == charIndex)
		{
			myShip = true;
		}
	}


	if( CharacterIsDead(chRef) )
	{
		if( !CheckAttribute(chRef,"ship.shipsink") || sti(chRef.ship.shipsink)==false )
			return;
	}

	/*if (myShip != true)
	{
		bCanSpeak = true;
	}*/
	//заглушка, убирающая интерфейс разговоров в море.
	//кому из аддонщиков будет интересно привести систему разговоров в норм - раскоментарьте
	//а у нас поставили сроки жесткие, програмеры в отпуске, и я банально не успеваю все оттестить
	//и поправить, ибо некоторые баги програмерские
	//для изьятия заглушки удалите нах следующую строчку
	//bCanSpeak = false;

	SendMessage(&BattleInterface,"llaall",BI_IN_CREATE_SHIP,charIndex,chRef,shipRef,myShip,shipRelation);
}

void BI_DeleteShip()
{
	int charIndex = GetEventData();
	if(charIndex==-1)
	{
		Trace("ERROR: Invalid character index");
		return;
	}
	if( IsCompanion(GetCharacter(charIndex)) )
	{
		RemoveCharacterCompanion(pchar,GetCharacter(charIndex));
	}
	DeleteAttribute(GetCharacter(charIndex),"ship.shipsink");
	RefreshBattleInterface();
}

void BI_DeadShip()
{
	int charIndex = GetEventData();
	if(charIndex==-1)
	{
		Trace("ERROR: Invalid character index");
		return;
	}
	if( IsCompanion(GetCharacter(charIndex)) )
	{
		RemoveCharacterCompanion(pchar,GetCharacter(charIndex));
	}
	Characters[charIndex].ship.shipsink = true;
	RefreshBattleInterface();
}

void BI_SetCommandMode(int commode, int texNum, int picNum, int chIdx)
{
	bi_icons_CommandMode = commode;
	SendMessage(&BattleInterface,"llllll",BI_IN_SET_COMMAND_MODE,commode,texNum,picNum,chIdx,-1);
}

void BI_SetSpecCommandMode(int commode, int texNum, int picNum, int chIdx, int comState)
{
	bi_icons_CommandMode = commode;
	SendMessage(&BattleInterface,"llllll",BI_IN_SET_COMMAND_MODE,commode,texNum,picNum,chIdx,comState);
}

void BI_SetPossibleCommands()
{
	int chIdx = GetEventData();
	int mainIdx = sti(pchar.index);

	if( chIdx<0 || CharacterIsDead(GetCharacter(chIdx)) )
	{
		aref aroot,arcur;
		makearef(aroot,BattleInterface.Commands);
		int q = GetAttributesNum(aroot);
		for(int i=0; i<q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		//BattleInterface.Commands.Cancel.enable = true;
		return;
	}

	// для главного персонажа
	if(mainIdx==chIdx)
	{
		//speak interface
		BattleInterface.Commands.ImmediateDeath.enable	= bBettaTestMode; // boal cheat
		if(CheckAttribute(pchar, "Cheats.ImmediateDeath"))
		{
			BattleInterface.Commands.ImmediateDeath.enable	= true; // belamour cheat menu
		}
		BattleInterface.Commands.InstantBoarding.enable	= bBettaTestMode; // boal cheat
		//BattleInterface.Commands.Speak.enable			= bCanSpeak;
		//BattleInterface.Commands.Sneak.enable			= bCanSneak;
		
		BattleInterface.Commands.Moor.enable			= bCanEnterToLand;
		BattleInterface.Commands.Board.enable			= bAbordageShipCanBe;
		BattleInterface.Commands.SailAway.enable		= false;
		BattleInterface.Commands.HeaveToDrift.enable	= false;
		BattleInterface.Commands.Charge.enable			= false;//CheckAttribute(pchar,"Ship.Cannons.Charge.Type"); // 
		BattleInterface.Commands.LandTroops.enable		= bAbordageFortCanBe;
		BattleInterface.Commands.Attack.enable			= false;
		BattleInterface.Commands.Defend.enable			= false;
		BattleInterface.Commands.Reload.enable			= bReloadCanBe;
		BattleInterface.Commands.Abordage.enable		= false;
		BattleInterface.Commands.SailTo.enable			= !bDisableSailTo && bSailTo;
		BattleInterface.Commands.SailDir.enable			= false;
		/*if( !bEnableIslandSailTo && iArcadeSailTo != 1)
		{
			BattleInterface.Commands.SailTo.enable		= false;
		}*/
		BattleInterface.Commands.Map.enable				= bMapEnter;
		BattleInterface.Commands.Speed.enable			= false;//true;
		//BattleInterface.Commands.CCommand.enable		= GetCompanionQuantity(pchar)>1;
		//BattleInterface.Commands.Ability.enable			= true;
		//  проверка на 7 класс
		if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) > SHIP_WAR_TARTANE) // pchar.Ship.Type != SHIP_NOTUSED
        {
            BattleInterface.Commands.Cabin.enable		= true;
        }
        BattleInterface.Commands.Boat.enable           = true;
	}
	// для спутников
	else
	{
		BattleInterface.Commands.Moor.enable			= false;
		BattleInterface.Commands.Board.enable			= false;
		BattleInterface.Commands.SailAway.enable		= true;
		BattleInterface.Commands.HeaveToDrift.enable	= true;
		BattleInterface.Commands.Charge.enable			= CheckAttribute(GetCharacter(chIdx), "Ship.Cannons.Charge.Type"); // 1.2.4
		BattleInterface.Commands.LandTroops.enable		= false;
		BattleInterface.Commands.Attack.enable			= bAttack;
		BattleInterface.Commands.Abordage.enable		= bAbordage;
		BattleInterface.Commands.Defend.enable			= bDefend;
		BattleInterface.Commands.Reload.enable			= false;
		BattleInterface.Commands.SailTo.enable			= false;
		BattleInterface.Commands.SailDir.enable			= true;
		BattleInterface.Commands.Map.enable				= false;
		BattleInterface.Commands.Speed.enable			= false;
		//BattleInterface.Commands.CCommand.enable		= false;
		//BattleInterface.Commands.Ability.enable			= true;
		//BattleInterface.Commands.Speak.enable			= false;
		//BattleInterface.Commands.Sneak.enable			= false;
		BattleInterface.Commands.ImmediateDeath.enable  = false; // boal
		BattleInterface.Commands.InstantBoarding.enable  = false; // boal
		BattleInterface.Commands.Cabin.enable			= false;
        BattleInterface.Commands.Boat.enable			= false; //boal
	}
    Event("evntSetUsingAbility","l", chIdx);
}

void BI_InitializeCommands()
{
	int idLngFile = LanguageOpenFile("commands_name.txt");

	DeleteAttribute(&BattleInterface,"Commands");
	DeleteAttribute(&BattleInterface,"AbilityIcons");

	BattleInterface.Commands.Cancel.enable			= false;
	BattleInterface.Commands.Cancel.picNum			= 1;
	BattleInterface.Commands.Cancel.selPicNum		= 0;
	BattleInterface.Commands.Cancel.texNum			= 2;
	BattleInterface.Commands.Cancel.event			= "Cancel";
	BattleInterface.Commands.Cancel.note			= LanguageConvertString(idLngFile, "sea_Cancel");

	BattleInterface.Commands.Moor.enable			= false;
	BattleInterface.Commands.Moor.picNum			= 29;
	BattleInterface.Commands.Moor.selPicNum			= 13;
	BattleInterface.Commands.Moor.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Moor.event				= "BI_Moor";
	BattleInterface.Commands.Moor.note				= LanguageConvertString(idLngFile, "sea_Moor");
	//
	BattleInterface.Commands.SailTo.enable			= false;
	BattleInterface.Commands.SailTo.picNum			= 16;
	BattleInterface.Commands.SailTo.selPicNum		= 0;
	BattleInterface.Commands.SailTo.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailTo.event			= "BI_SailTo";
	BattleInterface.Commands.SailTo.note			= LanguageConvertString(idLngFile, "sea_SailTo");
	//
	BattleInterface.Commands.Board.enable			= false;
	BattleInterface.Commands.Board.picNum			= 30;
	BattleInterface.Commands.Board.selPicNum		= 14;
	BattleInterface.Commands.Board.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Board.event			= "BI_Board";
	BattleInterface.Commands.Board.note				= LanguageConvertString(idLngFile, "sea_Board");
	//
	BattleInterface.Commands.LandTroops.enable		= false;
	BattleInterface.Commands.LandTroops.picNum		= 42;
	BattleInterface.Commands.LandTroops.selPicNum	= 45;
	BattleInterface.Commands.LandTroops.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.LandTroops.event		= "BI_LandTroops";
	BattleInterface.Commands.LandTroops.note		= LanguageConvertString(idLngFile, "sea_LandTroops");
	//
	BattleInterface.Commands.Map.enable				= false;
	BattleInterface.Commands.Map.picNum				= 28;
	BattleInterface.Commands.Map.selPicNum			= 12;
	BattleInterface.Commands.Map.texNum				= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Map.event				= "BI_Map";
	BattleInterface.Commands.Map.note				= LanguageConvertString(idLngFile, "sea_Map");
	//
	BattleInterface.Commands.Attack.enable			= false;
	BattleInterface.Commands.Attack.picNum			= 49;
	BattleInterface.Commands.Attack.selPicNum		= 33;
	BattleInterface.Commands.Attack.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Attack.event			= "BI_Attack";
	BattleInterface.Commands.Attack.note			= LanguageConvertString(idLngFile, "sea_Attack");
	//
	BattleInterface.Commands.Abordage.enable		= false;
	BattleInterface.Commands.Abordage.picNum		= 30;
	BattleInterface.Commands.Abordage.selPicNum		= 14;
	BattleInterface.Commands.Abordage.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Abordage.event			= "BI_Abordage";
	BattleInterface.Commands.Abordage.note			= LanguageConvertString(idLngFile, "sea_Abordage");
	//
	BattleInterface.Commands.Defend.enable			= false;
	BattleInterface.Commands.Defend.picNum			= 51;
	BattleInterface.Commands.Defend.selPicNum		= 35;
	BattleInterface.Commands.Defend.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Defend.event			= "BI_Defend";
	BattleInterface.Commands.Defend.note			= LanguageConvertString(idLngFile, "sea_Defend");
	//
	BattleInterface.Commands.SailAway.enable		= false;
	BattleInterface.Commands.SailAway.picNum		= 50;
	BattleInterface.Commands.SailAway.selPicNum		= 34;
	BattleInterface.Commands.SailAway.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailAway.event			= "BI_SailAway";
	BattleInterface.Commands.SailAway.note			= LanguageConvertString(idLngFile, "sea_SailAway");
	//
	BattleInterface.Commands.HeaveToDrift.enable	= false;
	BattleInterface.Commands.HeaveToDrift.picNum	= 25;
	BattleInterface.Commands.HeaveToDrift.selPicNum	= 9;
	BattleInterface.Commands.HeaveToDrift.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.HeaveToDrift.event		= "BI_HeaveToDrift";
	BattleInterface.Commands.HeaveToDrift.note		= LanguageConvertString(idLngFile, "sea_HeaveToDrift");
	//
	BattleInterface.Commands.Reload.enable			= false;
	BattleInterface.Commands.Reload.picNum			= 48;
	BattleInterface.Commands.Reload.selPicNum		= 32;
	BattleInterface.Commands.Reload.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Reload.event			= "BI_Reload";
	BattleInterface.Commands.Reload.note			= LanguageConvertString(idLngFile, "sea_Reload");
	//
	BattleInterface.Commands.Charge.enable			= false;
	BattleInterface.Commands.Charge.picNum			= 17;
	BattleInterface.Commands.Charge.selPicNum		= 1;
	BattleInterface.Commands.Charge.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Charge.event			= "BI_Charge";
	BattleInterface.Commands.Charge.note			= LanguageConvertString(idLngFile, "sea_Charge");
	//
	BattleInterface.Commands.Speed.enable			= false;
	BattleInterface.Commands.Speed.picNum			= 22;
	BattleInterface.Commands.Speed.selPicNum		= 6;
	BattleInterface.Commands.Speed.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Speed.event			= "BI_Speed";
	BattleInterface.Commands.Speed.note				= LanguageConvertString(idLngFile, "sea_Speed");
	//
	/*BattleInterface.Commands.CCommand.enable		= false;
	BattleInterface.Commands.CCommand.picNum		= 22;
	BattleInterface.Commands.CCommand.selPicNum		= 30;
	BattleInterface.Commands.CCommand.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.CCommand.event			= "BI_CompanionCommand";
	BattleInterface.Commands.CCommand.note			= LanguageConvertString(idLngFile, "sea_CCommand");*/
	//
	BattleInterface.Commands.Ability.enable			= false;
	BattleInterface.Commands.Ability.picNum			= 27;
	BattleInterface.Commands.Ability.selPicNum		= 11;
	BattleInterface.Commands.Ability.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Ability.event			= "BI_Ability";
	BattleInterface.Commands.Ability.note			= LanguageConvertString(idLngFile, "sea_Ability");
	//
	BattleInterface.Commands.Boat.enable			= false;
	BattleInterface.Commands.Boat.picNum			= 26;
	BattleInterface.Commands.Boat.selPicNum			= 10;
	BattleInterface.Commands.Boat.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Boat.event				= "BI_Boat";
	BattleInterface.Commands.Boat.note				= LanguageConvertString(idLngFile, "sea_Boat");
	
	BattleInterface.Commands.Cabin.enable			= false;
	BattleInterface.Commands.Cabin.picNum			= 27;
	BattleInterface.Commands.Cabin.selPicNum		= 11;
	BattleInterface.Commands.Cabin.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Cabin.event			= "BI_Cabin";
	BattleInterface.Commands.Cabin.note	    		= LanguageConvertString(idLngFile, "sea_Cabin");
	
	BattleInterface.Commands.Bomb.enable			= false;
	BattleInterface.Commands.Bomb.picNum			= 67;
	BattleInterface.Commands.Bomb.selPicNum			= 66;
	BattleInterface.Commands.Bomb.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Bomb.event				= "BI_Bomb";
	BattleInterface.Commands.Bomb.note	    		= LanguageConvertString(idLngFile, "sea_Bomb");
	
	BattleInterface.Commands.ImmediateDeath.enable	= false;
	BattleInterface.Commands.ImmediateDeath.picNum	= 65;    // это чит
	BattleInterface.Commands.ImmediateDeath.selPicNum	= 64;
	BattleInterface.Commands.ImmediateDeath.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.ImmediateDeath.event	= "BI_ImmDeath";
	BattleInterface.Commands.ImmediateDeath.note	= LanguageConvertString(idLngFile, "sea_ImmediateDeath");

	BattleInterface.Commands.Brander.enable			= false;
	BattleInterface.Commands.Brander.picNum			= 52;
	BattleInterface.Commands.Brander.selPicNum		= 36;
	BattleInterface.Commands.Brander.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Brander.event			= "BI_Brander";
    BattleInterface.Commands.Brander.note			= GetConvertStr("Brander", "AbilityDescribe.txt");
    
	BattleInterface.Commands.ImmediateReload.enable		= false;
	BattleInterface.Commands.ImmediateReload.picNum		= 53;
	BattleInterface.Commands.ImmediateReload.selPicNum	= 37;
	BattleInterface.Commands.ImmediateReload.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.ImmediateReload.event		= "BI_ImmediateReload";
    BattleInterface.Commands.ImmediateReload.note		= GetConvertStr("ImmediateReload", "AbilityDescribe.txt");
    
	BattleInterface.Commands.InstantBoarding.enable		= false;
	BattleInterface.Commands.InstantBoarding.picNum		= 30;   // это чит
	BattleInterface.Commands.InstantBoarding.selPicNum	= 14;
	BattleInterface.Commands.InstantBoarding.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.InstantBoarding.event		= "BI_InstantBoarding";
    BattleInterface.Commands.InstantBoarding.note		= GetConvertStr("InstantBoarding", "AbilityDescribe.txt");
    
	BattleInterface.Commands.LightRepair.enable			= false;
	BattleInterface.Commands.LightRepair.picNum			= 54;
	BattleInterface.Commands.LightRepair.selPicNum		= 38;
	BattleInterface.Commands.LightRepair.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.LightRepair.event			= "BI_LightRepair";
	BattleInterface.Commands.LightRepair.note			= GetConvertStr("LightRepair", "AbilityDescribe.txt");
	
	BattleInterface.Commands.InstantRepair.enable		= false;
	BattleInterface.Commands.InstantRepair.picNum		= 55;
	BattleInterface.Commands.InstantRepair.selPicNum	= 39;
	BattleInterface.Commands.InstantRepair.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.InstantRepair.event		= "BI_InstantRepair";
	BattleInterface.Commands.InstantRepair.note			= GetConvertStr("InstantRepair", "AbilityDescribe.txt");

	BattleInterface.Commands.Turn180.enable				= false;
	BattleInterface.Commands.Turn180.picNum				= 56;
	BattleInterface.Commands.Turn180.selPicNum			= 40;
	BattleInterface.Commands.Turn180.texNum				= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Turn180.event				= "BI_Turn180";
	BattleInterface.Commands.Turn180.note				= GetConvertStr("Turn180", "AbilityDescribe.txt");
	
	BattleInterface.Commands.SailDir.enable			= false;
	BattleInterface.Commands.SailDir.picNum			= 69;
	BattleInterface.Commands.SailDir.selPicNum		= 68;
	BattleInterface.Commands.SailDir.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailDir.event			= "BI_SailDir";
	BattleInterface.Commands.SailDir.note			= LanguageConvertString(idLngFile, "sea_SailDir");
	LanguageCloseFile(idLngFile);
}

ref BI_GetChargeQuantity()
{
	int chIdx = GetEventData();
	ref chr = GetCharacter(chIdx);
	BI_ChargeState[0] = 4;
	BI_ChargeState[1] = GetCargoGoods(chr,GOOD_BALLS);
	BI_ChargeState[2] = GetCargoGoods(chr,GOOD_GRAPES);
	BI_ChargeState[3] = GetCargoGoods(chr,GOOD_KNIPPELS);
	BI_ChargeState[4] = GetCargoGoods(chr,GOOD_BOMBS);

	return &BI_ChargeState;
}

ref GetCurrentCharge()
{
	/* belamour legendary edition измененная нумерация в storm engine для новых интерфейсов:
	   0 - ядра, 1 - картечь, 2 - книппели, 3 - бомбы,
	   4 - паруса, 5 - ветер, 6 - порох,  7 - оружие,
	   8 - доски, 9 - парусина, 10 - пушки */
	int eColor = argb(155,255,255,255);
	int fColor = argb(255,255,255,255);
	BI_intNRetValue[0] = -1;
	
	if( CheckAttribute(pchar,"Ship.Cannons.Charge.Type") )
	{
		switch(sti(pchar.Ship.Cannons.Charge.Type))
		{
		case GOOD_BALLS:
			BI_intNRetValue[0] = 121;
			BI_intNRetValue[1] = 122;
			BI_intNRetValue[2] = 124;
			BI_intNRetValue[3] = 126;
			break;
		case GOOD_GRAPES:
			BI_intNRetValue[0] = 120;
			BI_intNRetValue[1] = 123;
			BI_intNRetValue[2] = 124;
			BI_intNRetValue[3] = 126;
			break;
		case GOOD_KNIPPELS:
			BI_intNRetValue[0] = 120;
			BI_intNRetValue[1] = 122;
			BI_intNRetValue[2] = 125;
			BI_intNRetValue[3] = 126;
			break;
		case GOOD_BOMBS:
			BI_intNRetValue[0] = 120;
			BI_intNRetValue[1] = 122;
			BI_intNRetValue[2] = 124;
			BI_intNRetValue[3] = 127;
			break;
		}
	} 

	float fState = Ship_GetSailState(pchar);
	if(fState < 0.33)
    {
		if(iCompassPos) BI_intNRetValue[4] = 9;
		else BI_intNRetValue[4] = 93;
	}
    else
    {
		if(fState < 0.66)
        {
			if(iCompassPos) BI_intNRetValue[4] = 8;
			else BI_intNRetValue[4] = 94;
		}
        else
        {
			if(iCompassPos) BI_intNRetValue[4] = 7;
			else BI_intNRetValue[4] = 95;
		}
	}

    // TUTOR-ВСТАВКА
    if(TW_IsActive())
    {
        if(objTask.sea == "3_Sails" || objTask.sea == "4_Sails")
        {
			if(objTask.sea == "3_Sails")
			{
				if(fState < 0.33)
					objTask.sea.texts.Battle_Sails.text = StringFromKey("Tutorial_9", GKIC("Ship_SailUp", "Sailing3Pers"));
				else if(fState > 0.66)
					objTask.sea.texts.Battle_Sails.text = StringFromKey("Tutorial_9", GKIC("Ship_SailDown", "Sailing3Pers"));
			}
            if(or(objTask.sea == "3_Sails" && fState > 0.33 && fState < 0.66, objTask.sea == "4_Sails" && fState < 0.33))
            {
                if(!CheckAttribute(&TEV, "Tutor.SailStateTimer"))
                {
                    TEV.Tutor.SailStateTimer = GetDeltaTime() * 0.001;
                }
                else
                {
                    TEV.Tutor.SailStateTimer = stf(TEV.Tutor.SailStateTimer) + GetDeltaTime() * 0.001;
                    if(stf(TEV.Tutor.SailStateTimer) >= 9.0)
                    {
                        if(objTask.sea == "3_Sails")
                        {
                            objTask.sea = "4_Sails";
                            TW_ColorWeak(TW_GetTextARef("Battle_Sails"));
                            TW_AddBottomText("Lower_Sails", StringFromKey("Tutorial_10", GKIC("Ship_SailDown", "Sailing3Pers")), "Default");
                            TW_RecalculateLayout();
							DeleteAttribute(&TEV, "Tutor.SailStateTimer");
                        }
                        else
                        {
                            TW_ColorWeak(TW_GetTextARef("Lower_Sails"));
							TW_FinishSea_3_Sails();
                        }
                    }
                }
            }
            else DeleteAttribute(&TEV, "Tutor.SailStateTimer");
        }
    }

	if(iCompassPos) BI_intNRetValue[5] = 60;
	else BI_intNRetValue[5] = 92;
	BI_intNRetValue[6] = 108;
	BI_intNRetValue[7] = 109;
	BI_intNRetValue[8] = 110;
	BI_intNRetValue[9] = 111;
	if(CheckAttribute(pchar,"Ship.Cannons.Type") && pchar.Ship.Cannons.Type != CANNON_TYPE_NONECANNON && GetCannonsNum(pchar) > 0)
	{
		BI_intNRetValue[10] = sti(pchar.Ship.Cannons.Type);
		BattleInterface.textinfo.Cannonf.text = GetBortCannonsQty(pchar, "cannonf");
		BattleInterface.textinfo.Cannonb.text = GetBortCannonsQty(pchar, "cannonb");
		BattleInterface.textinfo.Cannonl.text = GetBortCannonsQty(pchar, "cannonl");
		BattleInterface.textinfo.Cannonr.text = GetBortCannonsQty(pchar, "cannonr");
	}
	else
	{
		BI_intNRetValue[10] = 15;
		BattleInterface.textinfo.Cannonf.text = 0;
		BattleInterface.textinfo.Cannonb.text = 0;
		BattleInterface.textinfo.Cannonl.text = 0;
		BattleInterface.textinfo.Cannonr.text = 0;
	}
	if(bShowExtInfo())
	{
		BattleInterface.textinfo.Balls.text = sti(pchar.ship.cargo.goods.balls);
		BattleInterface.textinfo.Grapes.text = sti(pchar.ship.cargo.goods.grapes);
		BattleInterface.textinfo.Knippels.text = sti(pchar.ship.cargo.goods.knippels);
		BattleInterface.textinfo.Bombs.text = sti(pchar.ship.cargo.goods.bombs);
		BattleInterface.textinfo.Powder.text = sti(pchar.ship.cargo.goods.powder);
		BattleInterface.textinfo.Weapon.text = sti(pchar.ship.cargo.goods.weapon);
		BattleInterface.textinfo.Planks.text = sti(pchar.ship.cargo.goods.planks);
		BattleInterface.textinfo.Sailcloth.text = sti(pchar.ship.cargo.goods.sailcloth);
		BattleInterface.textinfo.BallsKey.text = GetKeyCodeImg("hk_charge1");
		BattleInterface.textinfo.GrapesKey.text = GetKeyCodeImg("hk_charge2");
		BattleInterface.textinfo.KnippelsKey.text = GetKeyCodeImg("hk_charge3");
		BattleInterface.textinfo.BombsKey.text = GetKeyCodeImg("hk_charge4");
	}
	else
	{
		BattleInterface.textinfo.Cannonf.text = "";
		BattleInterface.textinfo.Cannonb.text = "";
		BattleInterface.textinfo.Cannonl.text = "";
		BattleInterface.textinfo.Cannonr.text = "";
		BattleInterface.textinfo.Balls.text = "";
		BattleInterface.textinfo.Grapes.text = "";
		BattleInterface.textinfo.Knippels.text = "";
		BattleInterface.textinfo.Bombs.text = "";
		BattleInterface.textinfo.Powder.text = "";
		BattleInterface.textinfo.Weapon.text = "";
		BattleInterface.textinfo.Planks.text = "";
		BattleInterface.textinfo.Sailcloth.text = "";
		BattleInterface.textinfo.BallsKey.text = "";
		BattleInterface.textinfo.GrapesKey.text = "";
		BattleInterface.textinfo.KnippelsKey.text = "";
		BattleInterface.textinfo.BombsKey.text = "";
	}
	SendMessage(&BattleInterface,"ll",BI_MSG_SHOW_SHIP_STATES, bShowShipStates());
	
	if (sti(pchar.ship.cargo.goods.balls) > 0) BattleInterface.textinfo.Balls.color = fColor;
	else BattleInterface.textinfo.Balls.color = eColor;
	if (sti(pchar.ship.cargo.goods.grapes)> 0) BattleInterface.textinfo.Grapes.color = fColor;
	else BattleInterface.textinfo.Grapes.color = eColor;
	if (sti(pchar.ship.cargo.goods.knippels) > 0) BattleInterface.textinfo.Knippels.color = fColor;
	else BattleInterface.textinfo.Knippels.color = eColor;
	if (sti(pchar.ship.cargo.goods.bombs)> 0) BattleInterface.textinfo.Bombs.color = fColor;
	else BattleInterface.textinfo.Bombs.color = eColor;
	if (sti(pchar.ship.cargo.goods.powder)> 0) BattleInterface.textinfo.Powder.color = fColor;
	else BattleInterface.textinfo.Powder.color = eColor;
	if (sti(pchar.ship.cargo.goods.weapon)> 0) BattleInterface.textinfo.Weapon.color = fColor;
	else BattleInterface.textinfo.Weapon.color = eColor;
	if (sti(pchar.ship.cargo.goods.planks)> 0) BattleInterface.textinfo.Planks.color = fColor;
	else BattleInterface.textinfo.Planks.color = eColor;
	if (sti(pchar.ship.cargo.goods.sailcloth)> 0) BattleInterface.textinfo.Sailcloth.color = fColor;
	else BattleInterface.textinfo.Sailcloth.color = eColor;
	if (GetBortCannonsQty(pchar, "cannonf") > 0) BattleInterface.textinfo.Cannonf.color = fColor;
	else BattleInterface.textinfo.Cannonf.color = eColor;
	if (GetBortCannonsQty(pchar, "cannonb") > 0) BattleInterface.textinfo.Cannonb.color = fColor;
	else BattleInterface.textinfo.Cannonb.color = eColor;
	if (GetBortCannonsQty(pchar, "cannonl") > 0) BattleInterface.textinfo.Cannonl.color = fColor;
	else BattleInterface.textinfo.Cannonl.color = eColor;
	if (GetBortCannonsQty(pchar, "cannonr") > 0) BattleInterface.textinfo.Cannonr.color = fColor;	
	else BattleInterface.textinfo.Cannonr.color = eColor;
	
	if(GetHullPercent(pchar) > 70.0 && GetHullPercent(pchar) < 81.0) ControlsDesc();
	if(GetSailPercent(pchar) > 70.0 && GetSailPercent(pchar) < 81.0) ControlsDesc();
	
	return &BI_intNRetValue;
}

ref biGetCharacterShipClass()
{
	int nChrIdx = GetEventData();
	BI_intRetValue = 1;
	if( nChrIdx>=0 && nChrIdx<MAX_CHARACTERS ) {
		BI_intRetValue = GetCharacterShipClass( &Characters[nChrIdx] );
	}
	return &BI_intRetValue;
}

void BI_SetSeaState()
{
	bool bTmp;
	bSailTo = GetEventData();
	bTmp = GetEventData();
	bMapEnter = GetEventData();
	bAttack = GetEventData();
	bAbordage = bAttack;

	bDefend = GetEventData();
	bReloadCanBe = GetEventData();
	bi_nReloadTarget = GetEventData();
	bEnableIslandSailTo = bMapEnter;
	if(bDisableMapEnter)	bMapEnter = false;

	// boal хрен вам убираем - нужное это делов в игре bReloadCanBe = 0;//убираем перегруз товара кроме как через меню.
}

void SetShipPictureDataByShipType(int idx)
{
	if(idx < 0 || idx >= GetArraySize(&ShipsTypes))
	{
		return;
	}

	ref refShip;
	makeref(refShip,ShipsTypes[idx]);

	BI_intNRetValue[3] = false;

	if (CheckAttribute(refShip, "modname"))
	{
		BI_intNRetValue[2] = FindIconTextureIndexWithInserting(idx, BI_ICONS_TEXTURE_FIRST_MOD);
	}
	else
	{
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
	}

	if (CheckAttribute(refShip, "icons"))
	{
		BI_intNRetValue[0] = sti(refShip.icons.FirstIconPos);
		BI_intNRetValue[1] = sti(refShip.icons.SecondIconPos);
	}
	else
	{
		BI_intNRetValue[0] = 0;
		BI_intNRetValue[1] = 1;
	}
}

ref BI_GetData()
{
	int dataType = GetEventData();
	int chrIdx;
	ref chRef;

	switch(dataType)
	{
	// Получаем номер картинки корабля
	case BIDT_SHIPPICTURE:
		chrIdx = GetEventData();
		chRef = GetCharacter(chrIdx);
		if( CharacterIsDead(chRef) && chrIdx != GetMainCharacterIndex())
		{
			BI_intNRetValue[0] = 65;
			BI_intNRetValue[1] = 64; // выбранная черепушка
			BI_intNRetValue[2] = BI_ICONS_TEXTURE_COMMAND;
			BI_intNRetValue[3] = true;
			return &BI_intNRetValue;
			break;
		}
		int st = sti(chRef.Ship.Type);
		if (!CheckAttribute(&RealShips[st], "basetype")) Log_TestInfo("BIDT_SHIPPICTURE нет basetype у корабля НПС ID=" + chRef.id);
		st = sti(RealShips[st].basetype);
		SetShipPictureDataByShipType( st );
		break;

	case BIDT_GERALD_DATA:
		{
			chrIdx = GetEventData();
			if(chrIdx<0) break;
			chRef = GetCharacter(chrIdx);
			BI_intNRetValue[0] = 8;
			switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
			{
				case RELATION_FRIEND:	
					BI_intNRetValue[1] = 7; 
				break;
				case RELATION_NEUTRAL:	
					BI_intNRetValue[1] = -1; 
				break;
				case RELATION_ENEMY:	
					BI_intNRetValue[1] = 6; 
				break;
			}
			BI_intNRetValue[2] = 8;
			switch( sti(chRef.nation) )
			{
				//case SMUGGLER:
				//	BI_intNRetValue[3] = 1;
				//break;
				case ENGLAND:		
					BI_intNRetValue[3] = 3; 
				break;
				case FRANCE:		
					BI_intNRetValue[3] = 2; 
				break;
				case SPAIN:			
					BI_intNRetValue[3] = 0; 
				break;
				case HOLLAND:		
					BI_intNRetValue[3] = 4; 
				break;
				case PIRATE:		
					BI_intNRetValue[3] = 5; 
				break;
			}

		}
		break;
	}
	return &BI_intNRetValue;
}

int FindIconTextureIndexWithInserting(int idx, int startIdx)
{
	ref refShip;
	makeref(refShip,ShipsTypes[idx]);
	string modname = refShip.modname;

	object mods;
	int ret = startIdx;
	for (int i = 0; i < idx; i++)
	{
		makeref(refShip,ShipsTypes[i]);

		if (CheckAttribute(refShip, "modname"))
		{
			string curModname = refShip.modname;
			if (!CheckAttribute(mods, curModname)) 
			{
				mods.(curModname) = 1;
				ret++;
			}
		}
	}

	return ret;
}


int GetIconTextureIndexWithInserting(int idx, int startIdx)
{
	ref refShip;
	makeref(refShip,ShipsTypes[idx]);

	string modname = refShip.modname;


	string smallFilePath = "interfaces\le\battle_interface\mods\"+modname+"\ship_icons1.tga.tx";
	string largeFilePath = "interfaces\le\battle_interface\mods\"+modname+"\ship_icons2.tga.tx";

	int i = startIdx;

	aref smallTextureList;
	makearef(smallTextureList,BattleInterface.CommandTextures.list);
	aref largeTextureList;
	makearef(largeTextureList,BattleInterface.IconTextures.list);
	while (true)
	{
		string attName = "t"+i;
		if (!CheckAttribute(smallTextureList, attName))
		{
			smallTextureList.(attName).name = smallFilePath;
			smallTextureList.(attName).xsize = 16;
			smallTextureList.(attName).ysize = 8;

			largeTextureList.(attName).name = largeFilePath;
			largeTextureList.(attName).xsize = 16;
			largeTextureList.(attName).ysize = 8;
			return i;
		}

		if (!CheckAttribute(largeTextureList, attName))
		{
			continue;
		}

		if (smallTextureList.(attName).name == smallFilePath && largeTextureList.(attName).name == largeFilePath)
		{
			return i;
		}
		i++;
	}

	return BI_ICONS_TEXTURE_SHIP1;
}

void InitShipsTextures(int startPos)
{
	ref refShip;
	for (i = 0; i < SHIP_TYPES_QUANTITY; i++)
	{
		makeref(refShip,ShipsTypes[i]);
		if (CheckAttribute(refShip, "modname"))
		{
			GetIconTextureIndexWithInserting(i, startPos);
		}
	}
}


void FillEmptyLargeTextures(int firstIdx, int lastIdx)
{
	aref textureList;
	makearef(textureList,BattleInterface.IconTextures.list);
	for (int i = firstIdx; i < lastIdx; i++)
	{
		string attName = "t"+i;
		textureList.(attName).name = "interfaces\le\battle_interface\ship_icons2.tga.tx";
		textureList.(attName).xsize = 16;
		textureList.(attName).ysize = 8;
	}
}

void SetParameterData()
{
    float fHtRatio = stf(Render.screen_y) / iHudScale;
    int fTmp, fTmp2, fTmp3, fTmp4;
	int idLngFile = LanguageOpenFile("commands_name.txt");
	
	BattleInterface.CommandTextures.list.t0.name = "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.CommandTextures.list.t0.xsize = 16;
	BattleInterface.CommandTextures.list.t0.ysize = 8;

	BattleInterface.CommandTextures.list.t1.name = "interfaces\le\battle_interface\ship_icons1.tga.tx";
	BattleInterface.CommandTextures.list.t1.xsize = 16;
	BattleInterface.CommandTextures.list.t1.ysize = 8;

	BattleInterface.CommandTextures.list.t2.name = "interfaces\le\battle_interface\cancel.tga.tx";
	BattleInterface.CommandTextures.list.t2.xsize = 2;
	BattleInterface.CommandTextures.list.t2.ysize = 1;

	BattleInterface.CommandTextures.list.t3.name = "interfaces\le\battle_interface\small_nations.tga.tx";
	BattleInterface.CommandTextures.list.t3.xsize = 8;
	BattleInterface.CommandTextures.list.t3.ysize = 1;

	BattleInterface.CommandTextures.list.t4.name = "interfaces\le\battle_interface\LandCommands.tga.tx";
	BattleInterface.CommandTextures.list.t4.xsize = 16;
	BattleInterface.CommandTextures.list.t4.ysize = 2;
	
	BattleInterface.CommandTextures.list.t5.name = "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.CommandTextures.list.t5.xsize = 16;
	BattleInterface.CommandTextures.list.t5.ysize = 8;

	FillEmptyLargeTextures(0, BI_ICONS_TEXTURE_FIRST_MOD);
	InitShipsTextures(BI_ICONS_TEXTURE_FIRST_MOD);

	BattleInterface.charge.charge1.picNum = 19; // balls
	BattleInterface.charge.charge1.selPicNum = 3;
	BattleInterface.charge.charge2.picNum = 18; // grapes
	BattleInterface.charge.charge2.selPicNum = 2;
	BattleInterface.charge.charge3.picNum = 21; // "knippels"
	BattleInterface.charge.charge3.selPicNum = 5;
	BattleInterface.charge.charge4.picNum = 20; // bombs
	BattleInterface.charge.charge4.selPicNum = 4;

	BattleInterface.CommandTextures.ChargeTexNum = 0;
	BattleInterface.CommandTextures.CommandTexNum = 0;

	BattleInterface.CommandShowParam.maxShowQuantity = 10;
	BattleInterface.CommandShowParam.iconDistance = makeint(4 * fHtRatio);
	BattleInterface.CommandShowParam.iconWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.iconHeight = RecalculateVIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.leftIconsOffset = sti(showWindow.left)+RecalculateHIcon(makeint(16 * fHtRatio));
	BattleInterface.CommandShowParam.downIconsOffset = sti(showWindow.bottom)-RecalculateVIcon(makeint(80 * fHtRatio));
	BattleInterface.CommandShowParam.buttonWidth = RecalculateHIcon(makeint(8 * fHtRatio));
	BattleInterface.CommandShowParam.buttonHeight = RecalculateVIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.buttonOffset = RecalculateHIcon(makeint(4 * fHtRatio));
	BattleInterface.CommandShowParam.buttonTexture = "interfaces\le\battle_interface\lr_buttons.tga.tx";
	BattleInterface.CommandShowParam.shipStateWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.shipStateHeight = RecalculateVIcon(makeint(16 * fHtRatio));
	BattleInterface.CommandShowParam.shipStateTexture = "interfaces\le\battle_interface\indicators.tga.tx";
	BattleInterface.CommandShowParam.shipStateOffset = RecalculateVIcon(0);
	BattleInterface.CommandShowParam.GeraldWidth = RecalculateHIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandShowParam.GeraldHeight = RecalculateVIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandShowParam.commandFont = "bold_numbers";
	BattleInterface.CommandShowParam.printXOffset = RecalculateHIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandShowParam.printYOffset = RecalculateVIcon(makeint(-26 * fHtRatio));
	BattleInterface.CommandShowParam.commandNoteFont = "interface_normal";
	BattleInterface.CommandShowParam.noteXOffset = RecalculateHIcon(0);
	BattleInterface.CommandShowParam.noteYOffset = RecalculateVIcon(makeint(-30 * fHtRatio));
	BattleInterface.CommandShowParam.argbTFactorColor = argb(256,64,64,64);

	BattleInterface.UserIcons.ui1.enable = true;
	BattleInterface.UserIcons.ui1.pic = 25;
	BattleInterface.UserIcons.ui1.selpic = 9;
	BattleInterface.UserIcons.ui1.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui1.name = "sail_none";
	//----------------------------------------------
	BattleInterface.UserIcons.ui2.enable = true;
	BattleInterface.UserIcons.ui2.pic = 24;
	BattleInterface.UserIcons.ui2.selpic = 8;
	BattleInterface.UserIcons.ui2.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui2.name = "sail_midi";
	//----------------------------------------------
	BattleInterface.UserIcons.ui3.enable = true;
	BattleInterface.UserIcons.ui3.pic = 23;
	BattleInterface.UserIcons.ui3.selpic = 7;
	BattleInterface.UserIcons.ui3.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui3.name = "sail_fast";
	//----------------------------------------------
	BattleInterface.UserIcons.ui4.enable = true;
	BattleInterface.UserIcons.ui4.selpic = 96;
	BattleInterface.UserIcons.ui4.pic = 112;
	BattleInterface.UserIcons.ui4.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui4.name = "dir_n";
	BattleInterface.UserIcons.ui4.note = LanguageConvertString(idLngFile, "sea_SailN");

	BattleInterface.UserIcons.ui5.enable = true;
	BattleInterface.UserIcons.ui5.selpic = 97;
	BattleInterface.UserIcons.ui5.pic = 113;
	BattleInterface.UserIcons.ui5.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui5.name = "dir_ne";
	BattleInterface.UserIcons.ui5.note = LanguageConvertString(idLngFile, "sea_SailNE");

	BattleInterface.UserIcons.ui6.enable = true;
	BattleInterface.UserIcons.ui6.selpic = 98;
	BattleInterface.UserIcons.ui6.pic = 114;
	BattleInterface.UserIcons.ui6.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui6.name = "dir_e";
	BattleInterface.UserIcons.ui6.note = LanguageConvertString(idLngFile, "sea_SailE");

	BattleInterface.UserIcons.ui7.enable = true;
	BattleInterface.UserIcons.ui7.selpic = 99;
	BattleInterface.UserIcons.ui7.pic = 115;
	BattleInterface.UserIcons.ui7.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui7.name = "dir_se";
	BattleInterface.UserIcons.ui7.note = LanguageConvertString(idLngFile, "sea_SailSE");

	BattleInterface.UserIcons.ui8.enable = true;
	BattleInterface.UserIcons.ui8.selpic = 100;
	BattleInterface.UserIcons.ui8.pic = 116;
	BattleInterface.UserIcons.ui8.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui8.name = "dir_s";
	BattleInterface.UserIcons.ui8.note = LanguageConvertString(idLngFile, "sea_SailS");

	BattleInterface.UserIcons.ui9.enable = true;
	BattleInterface.UserIcons.ui9.selpic = 101;
	BattleInterface.UserIcons.ui9.pic = 117;
	BattleInterface.UserIcons.ui9.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui9.name = "dir_sw";
	BattleInterface.UserIcons.ui9.note = LanguageConvertString(idLngFile, "sea_SailSW");

    BattleInterface.UserIcons.ui10.enable = true;
	BattleInterface.UserIcons.ui10.selpic = 102;
	BattleInterface.UserIcons.ui10.pic = 118;
	BattleInterface.UserIcons.ui10.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui10.name = "dir_w";
	BattleInterface.UserIcons.ui10.note = LanguageConvertString(idLngFile, "sea_SailW");

	BattleInterface.UserIcons.ui11.enable = true;
	BattleInterface.UserIcons.ui11.selpic = 103;
	BattleInterface.UserIcons.ui11.pic = 119;
	BattleInterface.UserIcons.ui11.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui11.name = "dir_nw";
	BattleInterface.UserIcons.ui11.note = LanguageConvertString(idLngFile, "sea_SailNW");

	BattleInterface.MessageIcons.IconWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	BattleInterface.MessageIcons.IconHeight = RecalculateVIcon(makeint(24 * fHtRatio));
	BattleInterface.MessageIcons.IconDist = RecalculateVIcon(2);
	BattleInterface.MessageIcons.IconBottom = sti(showWindow.bottom)-RecalculateVIcon(makeint((80+20) * fHtRatio));
	BattleInterface.MessageIcons.IconMaxQuantity = 4;
	BattleInterface.MessageIcons.BlendTime = 3.0;
	BattleInterface.MessageIcons.FallSpeed = 22.0;
	BattleInterface.MessageIcons.argbHighBlind = argb(255,128,128,128);
	BattleInterface.MessageIcons.argbLowBlind = argb(255,68,68,68);
	BattleInterface.MessageIcons.BlindUpTime = 0.5;
	BattleInterface.MessageIcons.BlindDownTime = 1.0;
	BattleInterface.MessageIcons.texture = "interfaces\le\battle_interface\MessageIcons.tga.tx";
	BattleInterface.MessageIcons.TexHSize = 2;
	BattleInterface.MessageIcons.TexVSize = 2;

	BattleInterface.navigation.aspectRatio				= showWindow.aspectRatio;
	BattleInterface.navigation.navigatorWidth			= RecalculateHIcon(makeint(256 * fHtRatio));
	BattleInterface.navigation.navigatorHeight			= RecalculateVIcon(makeint(256 * fHtRatio));
	BattleInterface.navigation.rightPos					= sti(showWindow.right) - RecalculateHIcon(makeint(20 * fHtRatio));

	BattleInterface.navigation.speedShowFont			= "interface_normal";
	if(iCompassPos) 
	{
		BattleInterface.navigation.topPos				= sti(showWindow.top) + RecalculateVIcon(makeint(20 * fHtRatio));
		BattleInterface.navigation.speedOutYOffset		= RecalculateVIcon(makeint(250 * fHtRatio));// смещение текста скорости и силы ветра по Y
		BattleInterface.navigation.shipSpeedXOffset		= RecalculateHIcon(makeint(40 * fHtRatio));// смещение текста скорости по X от центра компаса
		BattleInterface.navigation.windSpeedXOffset		= RecalculateHIcon(makeint(-40 * fHtRatio));// смещение текста силы ветра по X от центра компаса
	}
	else 
	{
		BattleInterface.navigation.topPos				= sti(showWindow.bottom) - RecalculateVIcon(makeint(276 * fHtRatio));
		BattleInterface.navigation.speedOutYOffset		= RecalculateVIcon(makeint(20 * fHtRatio));// смещение текста скорости и силы ветра по Y
		BattleInterface.navigation.shipSpeedXOffset		= RecalculateHIcon(makeint(50 * fHtRatio));// смещение текста скорости по X от центра компаса
		BattleInterface.navigation.windSpeedXOffset		= RecalculateHIcon(makeint(-50 * fHtRatio));// смещение текста силы ветра по X от центра компаса
	}
	BattleInterface.navigation.fontScale				= 1.3 * fHtRatio;
	BattleInterface.navigation.windWidth				= makeint(246 * fHtRatio);
	BattleInterface.navigation.windHeight				= makeint(246 * fHtRatio);

    BattleInterface.navigation.compasTexture			= "interfaces\le\battle_interface\compass.tga.tx";
    BattleInterface.navigation.emptyTexture				= "interfaces\le\battle_interface\indicators_dark_and_center_ship.tga.tx";
    BattleInterface.navigation.windTexture				= "interfaces\le\battle_interface\wind_pointer.tga.tx";
	BattleInterface.navigation.bestCourseTexture		= "interfaces\le\battle_interface\best_courseS.tga";

	BattleInterface.ammo.leftChargeBegAngle		        = 214;
	BattleInterface.ammo.leftChargeEndAngle		        = 326;
	BattleInterface.ammo.rightChargeBegAngle		    = 146;
	BattleInterface.ammo.rightChargeEndAngle		    = 34;
	BattleInterface.ammo.forwardChargeBegAngle	        = 343;
	BattleInterface.ammo.forwardChargeEndAngle	        = 378;
	BattleInterface.ammo.backwardChargeBegAngle	        = 198;
	BattleInterface.ammo.backwardChargeEndAngle	        = 162;
	BattleInterface.navigation.mapRadius				= makeint(94 * fHtRatio);
	BattleInterface.navigation.horizontRadius			= 400;
	BattleInterface.navigation.minScale					= 1;
	BattleInterface.navigation.maxScale					= 10;
	BattleInterface.navigation.curScale					= 2;
	BattleInterface.navigation.scaleStep				= 0.1;

    BattleInterface.ammo.aspectRatio			    	= showWindow.aspectRatio;
	BattleInterface.ammo.argbReadyCannonColor		    = argb(255,214,189,138);
	BattleInterface.ammo.argbChargeCannonColor	        = argb(255,227,214,156);
	BattleInterface.ammo.argbDamageCannonColor	        = argb(255,155,30,35);
	BattleInterface.navigation.argbSeaColor				= argb(255,10,40,80);
	BattleInterface.navigation.argbFireZoneColor		= argb(30,250,250,250);
	BattleInterface.navigation.argbEnemyShipColor		= argb(255,255,0,0);
	BattleInterface.navigation.argbFrendShipColor		= argb(255,0,255,0);
	BattleInterface.navigation.argbNeutralShipColor		= argb(255,128,128,128);
	BattleInterface.navigation.argbDeadShipColor		= argb(255,0,0,255);
	BattleInterface.navigation.argbBackMaxColor			= argb(255,0,0,128);
	BattleInterface.navigation.argbBackMinColor			= argb(0,0,0,128);
	BattleInterface.navigation.shipShowRadius			= 8.0;

	/* BattleInterface.navigation.chargeTexture			= "battle_interface\list_icon2.tga.tx";
	BattleInterface.navigation.chargeTextureGreed		= "8,8";
	BattleInterface.navigation.chargePos				= "0,"+RecalculateVIcon(makeint(270 * fHtRatio));
	BattleInterface.navigation.chargePictureSize		= RecalculateHIcon(makeint(48 * fHtRatio))+","+RecalculateVIcon(makeint(48 * fHtRatio)); */
    
    BattleInterface.ammo.cannonsTexture		        	= "interfaces\le\battle_interface\indicators_cannons_reload.tga.tx";
	
	BattleInterface.ammo.BallsTexture	    			= "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.ammo.BallsTextureGreed	        	= "16,8";
	BattleInterface.ammo.BallsPos					    = (sti(showWindow.right)/2 - RecalculateHIcon(makeint(276 * fHtRatio)))+","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.BallsPictureSize			    = RecalculateHIcon(makeint(64 * fHtRatio))+","+RecalculateVIcon(makeint(64 * fHtRatio));
	
	BattleInterface.ammo.GrapesTexture			        = "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.ammo.GrapesTextureGreed		        = "16,8";
	BattleInterface.ammo.GrapesPos				        = (sti(showWindow.right)/2 - RecalculateHIcon(makeint(212 * fHtRatio)))+","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.GrapesPictureSize		        = RecalculateHIcon(makeint(64 * fHtRatio))+","+RecalculateVIcon(makeint(64 * fHtRatio));
	
	BattleInterface.ammo.KnippelsTexture			    = "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.ammo.KnippelsTextureGreed		    = "16,8";
	BattleInterface.ammo.KnippelsPos				    = (sti(showWindow.right)/2 - RecalculateHIcon(makeint(148 * fHtRatio)))+","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.KnippelsPictureSize		    = RecalculateHIcon(makeint(64 * fHtRatio))+","+RecalculateVIcon(makeint(64 * fHtRatio));
	
	BattleInterface.ammo.BombsTexture				    = "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.ammo.BombsTextureGreed		        = "16,8";
	BattleInterface.ammo.BombsPos					    = (sti(showWindow.right)/2 - RecalculateHIcon(makeint(84 * fHtRatio)))+","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.BombsPictureSize			    = RecalculateHIcon(makeint(64 * fHtRatio))+","+RecalculateVIcon(makeint(64 * fHtRatio));
	
	BattleInterface.ammo.PowderTexture			        = "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.ammo.PowderTextureGreed		        = "16,8";
	BattleInterface.ammo.PowderPos				        = (sti(showWindow.right)/2 + RecalculateHIcon(makeint(84 * fHtRatio)))+","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.PowderPictureSize		        = RecalculateHIcon(makeint(64 * fHtRatio))+","+RecalculateVIcon(makeint(64 * fHtRatio));
	
	BattleInterface.ammo.WeaponTexture			        = "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.ammo.WeaponTextureGreed		        = "16,8";
	BattleInterface.ammo.WeaponPos				        = (sti(showWindow.right)/2 + RecalculateHIcon(makeint(148 * fHtRatio)))+","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.WeaponPictureSize		        = RecalculateHIcon(makeint(64 * fHtRatio))+","+RecalculateVIcon(makeint(64 * fHtRatio));
	
	BattleInterface.ammo.PlanksTexture			        = "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.ammo.PlanksTextureGreed		        = "16,8";
	BattleInterface.ammo.PlanksPos				        = (sti(showWindow.right)/2 + RecalculateHIcon(makeint(212 * fHtRatio)))+","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.PlanksPictureSize		        = RecalculateHIcon(makeint(64 * fHtRatio))+","+RecalculateVIcon(makeint(64 * fHtRatio));
	
	BattleInterface.ammo.SailclothTexture			    = "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.ammo.SailclothTextureGreed	        = "16,8";
	BattleInterface.ammo.SailclothPos				    = (sti(showWindow.right)/2 + RecalculateHIcon(makeint(276 * fHtRatio)))+","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.SailclothPictureSize		    = RecalculateHIcon(makeint(64 * fHtRatio))+","+RecalculateVIcon(makeint(64 * fHtRatio));
	
	BattleInterface.ammo.CannonsGTexture			    = "interfaces\le\battle_interface\cannons.tga";
	BattleInterface.ammo.CannonsGTextureGreed		    = "8,2";
	BattleInterface.ammo.CannonsGPos				    = sti(showWindow.right)/2 +","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.CannonsGPictureSize		    = RecalculateHIcon(makeint(70 * fHtRatio))+","+RecalculateVIcon(makeint(70 * fHtRatio));
	
	BattleInterface.navigation.sailstateTexture			= "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.navigation.sailstateTextureGreed	= "16,8";

	BattleInterface.navigation.windStateTexture			= "interfaces\le\battle_interface\list_icons.tga.tx";
	BattleInterface.navigation.windTextureGreed			= "16,8";
	if(iCompassPos)
	{
		BattleInterface.navigation.sailstatePos			= RecalculateHIcon(makeint(40 * fHtRatio))+","+RecalculateVIcon(makeint(215 * fHtRatio));
		BattleInterface.navigation.sailstatePictureSize	= RecalculateHIcon(makeint(50 * fHtRatio))+","+RecalculateVIcon(makeint(50 * fHtRatio));
		BattleInterface.navigation.windPos				= RecalculateHIcon(makeint(-40 * fHtRatio))+","+RecalculateVIcon(makeint(215 * fHtRatio));
		BattleInterface.navigation.windPictureSize		= RecalculateHIcon(makeint(50 * fHtRatio))+","+RecalculateVIcon(makeint(50 * fHtRatio));
	}
	else
	{
		BattleInterface.navigation.sailstatePos			= RecalculateHIcon(makeint(50 * fHtRatio))+","+RecalculateVIcon(makeint(-5 * fHtRatio));
		BattleInterface.navigation.sailstatePictureSize	= RecalculateHIcon(makeint(40 * fHtRatio))+","+RecalculateVIcon(makeint(40 * fHtRatio));
		BattleInterface.navigation.windPos				= RecalculateHIcon(makeint(-50 * fHtRatio))+","+RecalculateVIcon(makeint(-5 * fHtRatio));
		BattleInterface.navigation.windPictureSize		= RecalculateHIcon(makeint(40 * fHtRatio))+","+RecalculateVIcon(makeint(40 * fHtRatio));
	}

	BattleInterface.ammo.CannonsChargePos			    = sti(showWindow.right)/2 +","+(sti(showWindow.bottom) - RecalculateVIcon(makeint(80 * fHtRatio)));
	BattleInterface.ammo.CannonsChargePictureSize	    = RecalculateHIcon(makeint(148 * fHtRatio))+","+RecalculateVIcon(makeint(148 * fHtRatio));

	//cannons reload back icon --->
	fTmp = sti(showWindow.right)/2 - RecalculateHIcon(makeint(75* fHtRatio));
	fTmp2 = sti(showWindow.bottom) - RecalculateVIcon(makeint(155* fHtRatio));
	fTmp3 = sti(showWindow.right)/2 + RecalculateHIcon(makeint(75* fHtRatio));
	fTmp4 = sti(showWindow.bottom) - RecalculateVIcon(makeint(5* fHtRatio));
	string cpos	= fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	BattleInterface.imageslist.CannonsReloadBack.texture = "interfaces\le\battle_interface\indicators_cannons_back.tga.tx";
	BattleInterface.imageslist.CannonsReloadBack.color = argb(255,128,128,128);
	BattleInterface.imageslist.CannonsReloadBack.uv = "0.0,0.0,1.0,1.0";
	BattleInterface.imageslist.CannonsReloadBack.pos = cpos;
	//<---

	BattleInterface.textinfo.Location.font = "interface_normal_bold";
	BattleInterface.textinfo.Location.scale = 0.7 * fHtRatio;
	BattleInterface.textinfo.Location.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(148 * fHtRatio));
	if(iCompassPos) BattleInterface.textinfo.Location.pos.y = RecalculateVIcon(makeint(278 * fHtRatio));
	else BattleInterface.textinfo.Location.pos.y = RecalculateVIcon(makeint(28 * fHtRatio));
	BattleInterface.textinfo.Location.text = GetBILocationName();	// Display MoorName or region name in location
	BattleInterface.textinfo.Location.refreshable = true;			// Enable updates

	BattleInterface.textinfo.Date.font = "interface_normal_bold";
	BattleInterface.textinfo.Date.scale = 0.7 * fHtRatio;
	BattleInterface.textinfo.Date.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(148 * fHtRatio));
	if(iCompassPos) BattleInterface.textinfo.Date.pos.y = RecalculateVIcon(makeint(300 * fHtRatio));
	else BattleInterface.textinfo.Date.pos.y = RecalculateVIcon(makeint(52 * fHtRatio));
	BattleInterface.textinfo.Date.text = GetQuestBookData();//GetDataDay()+" "+XI_ConvertString("target_month_" + GetDataMonth())+" "+GetDataYear();
	BattleInterface.textinfo.Date.refreshable = true;

	BattleInterface.textinfo.Balls.font = "interface_normal";
	BattleInterface.textinfo.Balls.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Balls.color = argb(255,255,255,255);
	BattleInterface.textinfo.Balls.pos.x = sti(showWindow.right)/2 - RecalculateHIcon(makeint(276 * fHtRatio));
	BattleInterface.textinfo.Balls.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(125 * fHtRatio));
	BattleInterface.textinfo.Balls.text = 0;
	BattleInterface.textinfo.Balls.refreshable = true;

	BattleInterface.textinfo.Grapes.font = "interface_normal";
	BattleInterface.textinfo.Grapes.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Grapes.color = argb(255,255,255,255);
	BattleInterface.textinfo.Grapes.pos.x = sti(showWindow.right)/2 - RecalculateHIcon(makeint(212 * fHtRatio));
	BattleInterface.textinfo.Grapes.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(125 * fHtRatio));
	BattleInterface.textinfo.Grapes.text = 0;
	BattleInterface.textinfo.Grapes.refreshable = true;
	
	BattleInterface.textinfo.Knippels.font = "interface_normal";
	BattleInterface.textinfo.Knippels.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Knippels.color = argb(255,255,255,255);
	BattleInterface.textinfo.Knippels.pos.x = sti(showWindow.right)/2 - RecalculateHIcon(makeint(148 * fHtRatio));
	BattleInterface.textinfo.Knippels.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(125 * fHtRatio));
	BattleInterface.textinfo.Knippels.text = 0;
	BattleInterface.textinfo.Knippels.refreshable = true;
	
	BattleInterface.textinfo.Bombs.font = "interface_normal";
	BattleInterface.textinfo.Bombs.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Bombs.color = argb(255,255,255,255);
	BattleInterface.textinfo.Bombs.pos.x = sti(showWindow.right)/2 - RecalculateHIcon(makeint(84 * fHtRatio));
	BattleInterface.textinfo.Bombs.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(125 * fHtRatio));
	BattleInterface.textinfo.Bombs.text = 0;
	BattleInterface.textinfo.Bombs.refreshable = true;

	BattleInterface.textinfo.BallsKey.font = "keyboard_symbol";
	BattleInterface.textinfo.BallsKey.scale = 0.6 * fHtRatio;
	BattleInterface.textinfo.BallsKey.color = argb(255,255,255,255);
	BattleInterface.textinfo.BallsKey.pos.x = sti(showWindow.right)/2 - RecalculateHIcon(makeint(296 * fHtRatio));
	BattleInterface.textinfo.BallsKey.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(75 * fHtRatio));
	BattleInterface.textinfo.BallsKey.text = GetKeyCodeImg("hk_charge1");
	BattleInterface.textinfo.BallsKey.refreshable = true;
	
	BattleInterface.textinfo.GrapesKey.font = "keyboard_symbol";
	BattleInterface.textinfo.GrapesKey.scale = 0.6 * fHtRatio;
	BattleInterface.textinfo.GrapesKey.color = argb(255,255,255,255);
	BattleInterface.textinfo.GrapesKey.pos.x = sti(showWindow.right)/2 - RecalculateHIcon(makeint(232 * fHtRatio));
	BattleInterface.textinfo.GrapesKey.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(75 * fHtRatio));
	BattleInterface.textinfo.GrapesKey.text = GetKeyCodeImg("hk_charge2");
	BattleInterface.textinfo.GrapesKey.refreshable = true;

	BattleInterface.textinfo.KnippelsKey.font = "keyboard_symbol";
	BattleInterface.textinfo.KnippelsKey.scale = 0.6 * fHtRatio;
	BattleInterface.textinfo.KnippelsKey.color = argb(255,255,255,255);
	BattleInterface.textinfo.KnippelsKey.pos.x = sti(showWindow.right)/2 - RecalculateHIcon(makeint(168 * fHtRatio));
	BattleInterface.textinfo.KnippelsKey.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(75 * fHtRatio));
	BattleInterface.textinfo.KnippelsKey.text = GetKeyCodeImg("hk_charge3");
	BattleInterface.textinfo.KnippelsKey.refreshable = true;
	
	BattleInterface.textinfo.BombsKey.font = "keyboard_symbol";
	BattleInterface.textinfo.BombsKey.scale = 0.6 * fHtRatio;
	BattleInterface.textinfo.BombsKey.color = argb(255,255,255,255);
	BattleInterface.textinfo.BombsKey.pos.x = sti(showWindow.right)/2 - RecalculateHIcon(makeint(104 * fHtRatio));
	BattleInterface.textinfo.BombsKey.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(75 * fHtRatio));
	BattleInterface.textinfo.BombsKey.text = GetKeyCodeImg("hk_charge4");
	BattleInterface.textinfo.BombsKey.refreshable = true;

	BattleInterface.textinfo.Powder.font = "interface_normal";
	BattleInterface.textinfo.Powder.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Powder.color = argb(255,255,255,255);
	BattleInterface.textinfo.Powder.pos.x = sti(showWindow.right)/2 + RecalculateHIcon(makeint(84 * fHtRatio));
	BattleInterface.textinfo.Powder.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(125 * fHtRatio));
	BattleInterface.textinfo.Powder.text = 0;
	BattleInterface.textinfo.Powder.refreshable = true;
	
	BattleInterface.textinfo.Weapon.font = "interface_normal";
	BattleInterface.textinfo.Weapon.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Weapon.color = argb(255,255,255,255);
	BattleInterface.textinfo.Weapon.pos.x = sti(showWindow.right)/2 + RecalculateHIcon(makeint(148 * fHtRatio));
	BattleInterface.textinfo.Weapon.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(125 * fHtRatio));
	BattleInterface.textinfo.Weapon.text = 0;
	BattleInterface.textinfo.Weapon.refreshable = true;
	
	BattleInterface.textinfo.Planks.font = "interface_normal";
	BattleInterface.textinfo.Planks.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Planks.color = argb(255,255,255,255);
	BattleInterface.textinfo.Planks.pos.x = sti(showWindow.right)/2 + RecalculateHIcon(makeint(212 * fHtRatio));
	BattleInterface.textinfo.Planks.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(125 * fHtRatio));
	BattleInterface.textinfo.Planks.text = 0;
	BattleInterface.textinfo.Planks.refreshable = true;
	
	BattleInterface.textinfo.Sailcloth.font = "interface_normal";
	BattleInterface.textinfo.Sailcloth.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Sailcloth.color = argb(255,255,255,255);
	BattleInterface.textinfo.Sailcloth.pos.x = sti(showWindow.right)/2 + RecalculateHIcon(makeint(276 * fHtRatio));
	BattleInterface.textinfo.Sailcloth.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(125 * fHtRatio));
	BattleInterface.textinfo.Sailcloth.text = 0;
	BattleInterface.textinfo.Sailcloth.refreshable = true;
	
	BattleInterface.textinfo.Cannonf.font = "interface_normal";
	BattleInterface.textinfo.Cannonf.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Cannonf.color = argb(255,255,255,255);
	BattleInterface.textinfo.Cannonf.pos.x = sti(showWindow.right)/2+1;
	BattleInterface.textinfo.Cannonf.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(120 * fHtRatio));
	BattleInterface.textinfo.Cannonf.text = "";
	BattleInterface.textinfo.Cannonf.refreshable = true;
	
	BattleInterface.textinfo.Cannonb.font = "interface_normal";
	BattleInterface.textinfo.Cannonb.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Cannonb.color = argb(255,255,255,255);
	BattleInterface.textinfo.Cannonb.pos.x = sti(showWindow.right)/2+1;
	BattleInterface.textinfo.Cannonb.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(60 * fHtRatio));
	BattleInterface.textinfo.Cannonb.text = "";
	BattleInterface.textinfo.Cannonb.refreshable = true;
	
	BattleInterface.textinfo.Cannonl.font = "interface_normal";
	BattleInterface.textinfo.Cannonl.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Cannonl.color = argb(255,255,255,255);
	BattleInterface.textinfo.Cannonl.pos.x = sti(showWindow.right)/2 - RecalculateHIcon(makeint(30 * fHtRatio));
	BattleInterface.textinfo.Cannonl.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(90 * fHtRatio));
	BattleInterface.textinfo.Cannonl.text = "";
	BattleInterface.textinfo.Cannonl.refreshable = true;
	
	BattleInterface.textinfo.Cannonr.font = "interface_normal";
	BattleInterface.textinfo.Cannonr.scale = 1.4 * fHtRatio;
	BattleInterface.textinfo.Cannonr.color = argb(255,255,255,255);
	BattleInterface.textinfo.Cannonr.pos.x = sti(showWindow.right)/2 + RecalculateHIcon(makeint(30 * fHtRatio));
	BattleInterface.textinfo.Cannonr.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(90 * fHtRatio));
	BattleInterface.textinfo.Cannonr.text = "";
	BattleInterface.textinfo.Cannonr.refreshable = true;

	// подсказки управления
	for(numLine = 1; numLine < 8; numline ++)
	{
		sAttr = "Con"+numLine;
		sAttrDes = "Con"+numLine+"desc";
		sAttrB = "Con"+numLine+"Back";
		
		int boff = -85 + (numLine-1)*45;
		int coff = -84 + (numLine-1)*45;
		int doff = -79 + (numLine-1)*45;
	
		BattleInterface.textinfo.(sAttrB).font = "Info_fader_ls";
		BattleInterface.textinfo.(sAttrB).scale = 0.6 * fHtRatio;
		BattleInterface.textinfo.(sAttrB).color = argb(155,255,255,255);
		BattleInterface.textinfo.(sAttrB).pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(50 * fHtRatio));
		BattleInterface.textinfo.(sAttrB).pos.y = sti(showWindow.bottom)/4*3 + RecalculateVIcon(makeint(boff * fHtRatio));
		BattleInterface.textinfo.(sAttrB).align = "left";
		BattleInterface.textinfo.(sAttrB).text = "";
		BattleInterface.textinfo.(sAttrB).refreshable = true;
		
		BattleInterface.textinfo.(sAttr).font = "KEYBOARD_SYMBOL";
		BattleInterface.textinfo.(sAttr).scale = 0.9 * fHtRatio;
		BattleInterface.textinfo.(sAttr).color = argb(255,255,255,255);
		BattleInterface.textinfo.(sAttr).pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(75 * fHtRatio));
		BattleInterface.textinfo.(sAttr).pos.y = sti(showWindow.bottom)/4*3 + RecalculateVIcon(makeint(coff * fHtRatio));
		BattleInterface.textinfo.(sAttr).text = "";
		BattleInterface.textinfo.(sAttr).refreshable = true;
		
		BattleInterface.textinfo.(sAttrDes).font = "interface_normal";
		BattleInterface.textinfo.(sAttrDes).scale = 1.3 * fHtRatio;
		BattleInterface.textinfo.(sAttrDes).color = argb(255,255,255,255);
		BattleInterface.textinfo.(sAttrDes).pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(105 * fHtRatio));
		BattleInterface.textinfo.(sAttrDes).pos.y = sti(showWindow.bottom)/4*3 + RecalculateVIcon(makeint(doff * fHtRatio));
		BattleInterface.textinfo.(sAttrDes).align = "left";
		BattleInterface.textinfo.(sAttrDes).text = "";
		BattleInterface.textinfo.(sAttrDes).refreshable = true;
	}
	
	if( CheckAttribute(&InterfaceStates,"ShowBattleMode") ) {
		BattleInterface.battleborder.used = InterfaceStates.ShowBattleMode;
	} else {
		BattleInterface.battleborder.used = false;
	}
	BattleInterface.battleborder.color1 = argb(125,255,255,255);
	BattleInterface.battleborder.color2 = argb(35,255,255,255);
	BattleInterface.battleborder.extpos = "0,0," + ShowWindow.right + "," + ShowWindow.bottom;
	BattleInterface.battleborder.intpos1 = RecalculateHIcon(20) + "," + RecalculateVIcon(20) + "," + (sti(ShowWindow.right)-RecalculateHIcon(20)) + "," + (sti(ShowWindow.bottom)-RecalculateVIcon(20));
	BattleInterface.battleborder.intpos2 = RecalculateHIcon(10) + "," + RecalculateVIcon(10) + "," + (sti(ShowWindow.right)-RecalculateHIcon(10)) + "," + (sti(ShowWindow.bottom)-RecalculateVIcon(10));
	BattleInterface.battleborder.speed = 1.0;
	BattleInterface.battleborder.texture = "interfaces\le\battle_interface\battleborder.tga.tx";

	float fRes = 0.85; // для ресайза компаньонов
	BattleInterface.ShipIcon.sailorfontid			= "interface_normal";
	BattleInterface.ShipIcon.sailorfontcolor		= argb(255,255,255,255);
    BattleInterface.ShipIcon.mcsailorfontscale		= 1.5 * fHtRatio;																 
    BattleInterface.ShipIcon.sailorfontscale		= 1.2 * fHtRatio;
    fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(40.0 * fHtRatio);
    BattleInterface.ShipIcon.mcsailorfontoffset       = fTmp + "," + fTmp2;
	fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(39.0 * fRes * fHtRatio);
    BattleInterface.ShipIcon.sailorfontoffset       = fTmp + "," + fTmp2;

	BattleInterface.ShipIcon.shipnamefontidmc		= "interface_normal";
	BattleInterface.ShipIcon.shipnamefontcolormc	= argb(255,255,255,255);
	BattleInterface.ShipIcon.shipnamefontscalemc	= 1.4 * fHtRatio;	
	fTmp = makeint(180.0 * fHtRatio);
    fTmp2 = makeint(-30.0 * fHtRatio);
    BattleInterface.ShipIcon.shipnamefontoffsetmc   = fTmp + "," + fTmp2;

	BattleInterface.ShipIcon.shipnamefontid			= "interface_normal";
	BattleInterface.ShipIcon.shipnamefontcolor		= argb(255,255,255,255);
	BattleInterface.ShipIcon.shipnamefontscale		= 1.4 * fHtRatio;
    fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(50.0 * fHtRatio);
    BattleInterface.ShipIcon.shipnamefontoffset     = fTmp + "," + fTmp2;

	BattleInterface.ShipIcon.backmctexturename		= "interfaces\le\battle_interface\ShipBackIcon0.tga.tx";
	BattleInterface.ShipIcon.backmccolor			= argb(255,128,128,128);
	BattleInterface.ShipIcon.backmcuv				= "0.0,0.0,1.0,1.0";
	BattleInterface.ShipIcon.backmmccoffset			= "0,0";
    fTmp = makeint(128.0 * fHtRatio);
    BattleInterface.ShipIcon.backmciconsize			= fTmp + "," + fTmp;

	BattleInterface.ShipIcon.backtexturename		= "interfaces\le\battle_interface\ShipBackIcon2.tga.tx";
	BattleInterface.ShipIcon.backcolor				= argb(255,128,128,128);
	BattleInterface.ShipIcon.backuv					= "0.0,0.0,1.0,1.0";
	BattleInterface.ShipIcon.backoffset				= "0,0";	

    fTmp = makeint(128.0 * fRes * fHtRatio);
    BattleInterface.ShipIcon.backiconsize			= fTmp + "," + fTmp;

	BattleInterface.ShipIcon.shipstatebacktexturename	= "interfaces\le\battle_interface\ShipStateBackIcon.tga.tx";
	BattleInterface.ShipIcon.shipstatebackcolor		= argb(255,128,128,128);
	BattleInterface.ShipIcon.shipstatebackuv		= "0.0,0.0,1.0,1.0";
	fTmp = makeint(180.0 * fHtRatio);
    fTmp2 = makeint(0.0 * fHtRatio);	
	BattleInterface.ShipIcon.shipstatebackoffset	= fTmp + "," + fTmp2;
	fTmp = makeint(256.0 * fHtRatio);
	fTmp2 = makeint(64.0 * fHtRatio);
    BattleInterface.ShipIcon.shipstatebackiconsize	= fTmp + "," + fTmp2;

	BattleInterface.ShipIcon.shipstatemctexturename	= "interfaces\le\battle_interface\ShipStateHorizontal.tga.tx";
	BattleInterface.ShipIcon.shipstatemccolor		= argb(255,128,128,128);
	BattleInterface.ShipIcon.shiphpmcuv				= "0.1171,0.4218,0.9765,0.5781";
	BattleInterface.ShipIcon.shipspmcuv				= "0.1171,0.7031,0.9765,0.8593";

	BattleInterface.ShipIcon.shipstatetexturename	= "interfaces\le\battle_interface\ShipState.tga.tx";
	BattleInterface.ShipIcon.shipstatecolor			= argb(255,128,128,128);
	BattleInterface.ShipIcon.shiphpuv				= "0.0,0.1875,0.5,0.7968";
	BattleInterface.ShipIcon.shipspuv				= "0.5,0.1875,1.0,0.7968";

	fTmp = makeint(192.0 * fHtRatio);
    fTmp2 = makeint(0.0 * fHtRatio);
    BattleInterface.ShipIcon.shiphpmcoffset			= fTmp + "," + fTmp2;
	fTmp2 = makeint(18.0 * fHtRatio);
    BattleInterface.ShipIcon.shipspmcoffset			= fTmp + "," + fTmp2;

	fTmp = makeint(220.0 * fHtRatio);
    fTmp2 = makeint(10.0 * fHtRatio);
    BattleInterface.ShipIcon.shiphpmciconsize		= fTmp + "," + fTmp2;
    BattleInterface.ShipIcon.shipspmciconsize		= fTmp + "," + fTmp2;

    fTmp = makeint(-25.0 * fHtRatio);
    fTmp2 = makeint(0.0 * fHtRatio);
    BattleInterface.ShipIcon.shiphpoffset			= fTmp + "," + fTmp2;
    fTmp = makeint(25.0 * fHtRatio);
    BattleInterface.ShipIcon.shipspoffset			= fTmp + "," + fTmp2; 

    fTmp = makeint(60.0 * fHtRatio);
    fTmp2 = makeint(67.0 * fHtRatio);
    BattleInterface.ShipIcon.shiphpiconsize			= fTmp + "," + fTmp2;
    BattleInterface.ShipIcon.shipspiconsize			= fTmp + "," + fTmp2;

	BattleInterface.ShipIcon.shipclasstexturename	= "interfaces\le\battle_interface\ShipClass.tga.tx";
	BattleInterface.ShipIcon.shipclasscolor			= argb(255,128,128,128);
	BattleInterface.ShipIcon.shipclassuv			= "0.0,0.0,1.0,1.0";

	fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(-54.0 * fHtRatio);
	BattleInterface.ShipIcon.mcshipclassoffset		= fTmp + "," + fTmp2;

    fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(-46.0 * fHtRatio);
    BattleInterface.ShipIcon.shipclassoffset		= fTmp + "," + fTmp2;

	fTmp = makeint(128.0 * fHtRatio);
    fTmp2 = makeint(32.0 * fHtRatio);
    BattleInterface.ShipIcon.mcshipclassiconsize		= fTmp + "," + fTmp2;

    fTmp = makeint(128.0 * fRes * fHtRatio);
    fTmp2 = makeint(32.0 * fRes * fHtRatio);
    BattleInterface.ShipIcon.shipclassiconsize		= fTmp + "," + fTmp2;

	BattleInterface.ShipIcon.gunchargeprogress		= "0.0625, 0.211, 0.359, 0.5, 0.633, 0.781, 0.983"; //Tymofei: подогнал под точную обрезку, в игре не видно, на скринах при скалинге - легко!

	BattleInterface.ShipIcon.shiptexturename		= "interfaces\le\battle_interface\ship_icons2.tga.tx";
	BattleInterface.ShipIcon.xsize 					= 16;
	BattleInterface.ShipIcon.ysize 					= 16;
	BattleInterface.ShipIcon.shipcolor				= argb(255,128,128,128);

    fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(0.0 * fHtRatio);
    BattleInterface.ShipIcon.shipoffset				= fTmp + "," + fTmp2;
    fTmp = makeint(90.0 * fHtRatio);
    BattleInterface.ShipIcon.mcshipiconsize			= fTmp + "," + fTmp;
    fTmp = makeint(90.0 * fRes * fHtRatio);
    BattleInterface.ShipIcon.shipiconsize			= fTmp + "," + fTmp;

    fTmp = makeint(54.0 * fHtRatio);
    BattleInterface.ShipIcon.commandlistverticaloffsetmc = fTmp;
    fTmp = makeint(-20 * fHtRatio);
    BattleInterface.ShipIcon.commandlistverticaloffset = fTmp;
	
    fTmp = makeint(75.0 * fHtRatio);
    fTmp3 = fTmp;
    fTmp2 = makeint(130.0 * fHtRatio);
    BattleInterface.ShipIcon.iconoffset1 = fTmp + "," + fTmp;
    fTmp3 += fTmp2;
    BattleInterface.ShipIcon.iconoffset2 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.ShipIcon.iconoffset3 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.ShipIcon.iconoffset4 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.ShipIcon.iconoffset5 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.ShipIcon.iconoffset6 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.ShipIcon.iconoffset7 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.ShipIcon.iconoffset8 = fTmp + "," + fTmp3;

	BattleInterface.CommandList.CommandMaxIconQuantity = 12;
	BattleInterface.CommandList.CommandIconSpace = 1;
	BattleInterface.CommandList.CommandIconLeft = makeint(160 * fHtRatio);//157;
	BattleInterface.CommandList.CommandIconWidth = RecalculateHIcon(makeint(55 * fHtRatio));
	BattleInterface.CommandList.CommandIconHeight = RecalculateVIcon(makeint(55 * fHtRatio));

	BattleInterface.CommandList.CommandNoteFont = "interface_normal_bold";
	BattleInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
	BattleInterface.CommandList.CommandNoteScale = 0.65 * fHtRatio;
	BattleInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(makeint(-50 * fHtRatio));

	BattleInterface.CommandList.UDArrow_Texture = "interfaces\le\battle_interface\arrowly.tga.tx";
	BattleInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
	BattleInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
	BattleInterface.CommandList.UDArrow_Size = RecalculateHIcon(makeint(30 * fHtRatio)) + "," + RecalculateVIcon(makeint(30 * fHtRatio));
	BattleInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(makeint(-30 * fHtRatio)) + "," + RecalculateVIcon(makeint(-45 * fHtRatio));
	BattleInterface.CommandList.UDArrow_Offset_Down0 = RecalculateHIcon(makeint(-30 * fHtRatio)) + "," + RecalculateVIcon(makeint(20 * fHtRatio));
	BattleInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(makeint(-30 * fHtRatio)) + "," + RecalculateVIcon(makeint(45 * fHtRatio));

	BattleInterface.ShipInfoImages.RelationTexture = "interfaces\le\battle_interface\ship_arrows1.tga.tx";
	BattleInterface.ShipInfoImages.RelationOffset.x = 0.0;
	BattleInterface.ShipInfoImages.RelationOffset.y = 0.0;
	BattleInterface.ShipInfoImages.RelationOffset.z = 0.0;
	BattleInterface.ShipInfoImages.RelationSize = "0.6,0.3";
	BattleInterface.ShipInfoImages.RelationUV1 = "0.0,0.0,0.25,1.0"; // friend
	BattleInterface.ShipInfoImages.RelationUV2 = "0.25,0.0,0.5,1.0"; // enemy
	BattleInterface.ShipInfoImages.RelationUV3 = "0.5,0.0,0.75,1.0"; // neutral

	BattleInterface.ShipInfoImages.ProgressTexture = "interfaces\le\battle_interface\indicators.tga.tx";
	BattleInterface.ShipInfoImages.ProgressSize = "2.48,0.06";
	//
	BattleInterface.ShipInfoImages.ProgressBackOffset.x = 0.0;
	BattleInterface.ShipInfoImages.ProgressBackOffset.y = 0.3;
	BattleInterface.ShipInfoImages.ProgressBackOffset.z = 0.0;
	BattleInterface.ShipInfoImages.ProgressBackSize = "2.5,0.2";
	BattleInterface.ShipInfoImages.ProgressBackUV = "0.0,0.5,1.0,1.0";
	//
	BattleInterface.ShipInfoImages.HullOffset.x = 0.0;
	BattleInterface.ShipInfoImages.HullOffset.y = 0.36;
	BattleInterface.ShipInfoImages.HullOffset.z = 0.0;
	BattleInterface.ShipInfoImages.HullUV = "0.016,0.016,0.992,0.172";
	//
	BattleInterface.ShipInfoImages.CrewOffset.x = 0.0;
	BattleInterface.ShipInfoImages.CrewOffset.y = 0.30;
	BattleInterface.ShipInfoImages.CrewOffset.z = 0.0;
	BattleInterface.ShipInfoImages.CrewUV = "0.016,0.172,0.992,0.328";
	//
	BattleInterface.ShipInfoImages.SailOffset.x = 0.0;
	BattleInterface.ShipInfoImages.SailOffset.y = 0.24;
	BattleInterface.ShipInfoImages.SailOffset.z = 0.0;
	BattleInterface.ShipInfoImages.SailUV = "0.016,0.328,0.992,0.484";

	if(CheckAttribute(&InterfaceStates, "EnabledShipMarks") && sti(InterfaceStates.EnabledShipMarks) == 1) BattleInterface.ShifInfoVisible = 1;
	else BattleInterface.ShifInfoVisible = 0;
	
	LanguageCloseFile(idLngFile);
}

ref ProcessSailDamage()
{
	// от кого удар
	int shootIdx = GetEventData();
	// перс
	int chrIdx = GetEventData();

	string sMastName = GetEventData();
	// координаты паруса
	string reyName = GetEventData();
	int groupNum = GetEventData();
	// данные о дырках
	int holeCount = GetEventData();
	int holeData = GetEventData();
	int maxHoleCount = GetEventData();
	// мощность паруса
	float sailPower = GetEventData();

	ref chref = GetCharacter(chrIdx);
	
	string groupName = ""+groupNum;
	aref arSail;
	makearef(arSail,chref.ship.sails.(reyName).(groupName));

	float sailDmg = 0.0;
	float sailDmgMax = GetCharacterShipSP(chref) * sailPower;
	if( !CheckAttribute(arSail,"dmg") )	{ sailDmg = 0.0; }

	if(sMastName=="*")
	{
		sailDmg = sailDmg + GetRigDamage(shootIdx,sti(AIBalls.CurrentBallType),chref);
		if(sailDmg>sailDmgMax)	{ sailDmg = sailDmgMax; }
		int needHole = GetNeedHoleFromDmg(sailDmg,sailDmgMax,maxHoleCount);
		if(holeCount!=needHole)
		{
			if(holeCount<needHole)
			{
				holeData = RandomHole2Sail(chrIdx,reyName,groupNum, maxHoleCount, holeData, needHole-holeCount);
				holeCount = needHole;
			}
			else
			{
				sailDmg = GetNeedDmgFromHole(holeCount,sailDmgMax,maxHoleCount);
			}
		}
	}
	else
	{
		if(sMastName!="#")	{ arSail.mastFall = sMastName; }
		sailDmg = sailDmgMax;
	}
	
	arSail.hc = holeCount;
	arSail.hd = holeData;
	arSail.mhc = maxHoleCount;
	arSail.sp = sailPower;
	arSail.dmg = sailDmg;
	
	if (LAi_IsImmortal(chref)) 
	{
		SetEventHandler("evntRepairDelay","RepairDelay",0);
		PostEvent("evntRepairDelay",499,"l", chrIdx);
	}
	BI_g_fRetVal = sailDmg;
	return &BI_g_fRetVal;
}

void RepairDelay()
{
	int idx = GetEventData();
	ProcessSailRepair(&Characters[idx], 100.0);
	DelEventHandler("evntRepairDelay","RepairDelay");
}

// ugeen -> учет безвозвратной убыли корпуса
void ProcessHullDecrease()
{
	int i, cn, hp;
	ref chref;
	ref mchar = GetMainCharacter();
	
	if (!bSeaActive || mchar.location == mchar.SystemInfo.CabinType) // спим в каюте
	{
		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(mchar,i);
			if(cn == -1) continue;
			chref = GetCharacter(cn);
	
			if(CheckAttribute(chref, "Ship.HP_penalty"))
			{
				hp = sti(RealShips[sti(chref.ship.type)].HP);	// текущий максимум
				if(hp > makeint(stf(chref.Ship.HP_penalty)) ) RealShips[sti(chref.ship.type)].HP = hp - makeint(stf(chref.Ship.HP_penalty)); 
				else RealShips[sti(chref.ship.type)].HP = 1;
				if( GetCurrentShipHP(chref) > sti(RealShips[sti(chref.ship.type)].HP) )
				{
					chref.ship.hp =	sti(RealShips[sti(chref.ship.type)].HP);
				}
				DeleteAttribute(chref, "Ship.HP_penalty");
			}	
		}
	}	
}
// <-- ugeen

bool CheckRepairPerks(ref chref)
{	
	if( CheckOfficersPerk(chref, "Carpenter") 		||
	    CheckOfficersPerk(chref, "LightRepair")		||
		CheckOfficersPerk(chref, "Builder")			||
		CheckOfficersPerk(chref, "SelfRepair"))	return true;
	return false;	
}

// перенес из ВМЛ 25/09/06
void ProcessDayRepair()
{
	int i, cn;
	float matQ, tmpf, repPercent;
	ref chref;
	ref mchar = GetMainCharacter();
	// boal 21.01.2004 на лету в море не чиним, тк идут дни прям в море -->
	//if (bSeaActive == false || mchar.location == mchar.SystemInfo.CabinType) // спим в каюте
	if (!bSeaActive || mchar.location != mchar.SystemInfo.CabinType) // при отдыхе в каюте не чинимся
	{		
		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(mchar,i);
			if(cn==-1) continue;
			chref = GetCharacter(cn);
			if(CheckRepairPerks(chref) || IsCharacterEquippedArtefact(chref, "obereg_1") || IsCharacterEquippedArtefact(chref, "obereg_2"))
			{	
				// расчёт починки корпуса
				if (GetHullPercent(chref) < 100.0 )
				{
					repPercent = GetHullRPD(chref);
					matQ = repPercent*GetHullPPP(chref);
					tmpf = GetRepairGoods(true,chref);
					if (tmpf > 0)
					{
						if (tmpf < matQ)	{ repPercent = tmpf/GetHullPPP(chref); }  
						repPercent = ProcessHullRepair(chref, repPercent);
						matQ = repPercent*GetHullPPP(chref);
						RemoveRepairGoods(true,chref,matQ);
						// boal  check skill -->
						AddCharacterExpToSkill(chref, "Repair", matQ / 3.0);
						// boal <--
					}
				}
				
				// расчёт починки парусов
				if (GetSailPercent(chref) < GetAllSailsDamagePercent(chref) )
				{
					repPercent = GetSailRPD(chref);
					matQ = repPercent*GetSailSPP(chref);
					tmpf = GetRepairGoods(false,chref);
					
					if (tmpf > 0)
					{
						if (tmpf < matQ)	{ repPercent = tmpf/GetSailSPP(chref); }
						repPercent = ProcessSailRepair(chref,repPercent);
						matQ = repPercent*GetSailSPP(chref);
						RemoveRepairGoods(false,chref,matQ);
						// boal  check skill -->
						AddCharacterExpToSkill(chref, "Repair", matQ / 4.0);
						// boal <--
					}
				}
			}
		}
	}
	// boal 21.01.2004 <--
}

ref procGetSailTextureData()
{
	int st,i,sq;
	ref shref;
	aref arEmbl,arSail;
	string attrName;

	int chrIdx = GetEventData();

	DeleteAttribute(&BI_objRetValue,"");
    if (chrIdx>=0)
	{
		st = GetCharacterShipType(GetCharacter(chrIdx));
		if (st != SHIP_NOTUSED)
		{
			//string sUpgrade = "common";
			string sUpgrade = "usual0";
		
			shref = GetRealShip(st); 
		
			int iUpgrade = sti(shref.ship.upgrades.sails);  
			/*switch(iUpgrade)
			{
				case 1:
					sUpgrade = "common";
				break;
				case 2: 
					sUpgrade = "pat";
				break;
				case 3:
					sUpgrade = "silk";
				break;
			}*/
			// Jason: новые типы парусов, унифицируем в одно целое
			switch(iUpgrade)
			{
				case 1:
					sUpgrade = "usual0";
				break;
				case 2: 
					sUpgrade = "usual1";
				break;
				case 3:
					sUpgrade = "usual2";
				break;
				case 4:
					sUpgrade = "usual3";
				break;
				case 5:
					sUpgrade = "usual4";
				break;
				case 6:
					sUpgrade = "wing"; // белый
				break;
				case 7:
					sUpgrade = "win0"; // синие полоски
				break;
				case 8:
					sUpgrade = "win1"; // красные полоски
				break;
				case 9:
					sUpgrade = "win2"; // сине-красный крест
				break;
				case 10:
					sUpgrade = "win3"; // трехцветные
				break;
				case 11:
					sUpgrade = "win4"; // красные ромбы
				break;
				case 12:
					sUpgrade = "torn"; // рванина
				break;
				case 13:
					sUpgrade = "silk"; // шелк
				break;
			}
		
			string nationFileName = "ships\parus_" + sUpgrade + ".tga";
			string tmpStr;
		
			BI_objRetValue.normalTex = nationFileName;
			BI_objRetValue.geraldTex = "";//"ships\gerald\chuckskull.tga";
			BI_objRetValue.sailscolor = argb(255,255,255,255);  // белый парус
		
			//BI_objRetValue.geraldTexPointer = 0; // (IDirect3DTexture8*)
			
			//if (CheckAttribute(&characters[chrIdx], "ShipSails.SailsColor"))
			if (CheckAttribute(shref, "ShipSails.SailsColor")) // 1.2.3 цвет теперь атрибут корабля, а не НПС
			{
				BI_objRetValue.sailscolor = sti(shref.ShipSails.SailsColor);
			}
			//if( CheckAttribute(&characters[chrIdx],"ShipSails.gerald_name") ) // не наследуется при обмене кораблей, потому не в  ship.
			if( CheckAttribute(shref,"ShipSails.gerald_name") ) // 1.2.3 герб теперь атрибут корабля, а не НПС
			{
				// belamour legemdary edition фикс отображения гербов в море
				BI_objRetValue.geraldTex = "Ships\Gerald\" + shref.ShipSails.gerald_name; 
			}
			/*
			switch(sti(Characters[chrIdx].nation))  // Не работает это :(
			{
				case ENGLAND:	
					nationFileName = "ships\parus_" + sUpgrade + "_england.tga";		
				break;
				case FRANCE:	
					nationFileName = "ships\parus_" + sUpgrade + "_france.tga";		
				break;
				case SPAIN:		
					nationFileName = "ships\parus_" + sUpgrade + "_spain.tga";	
				break;
				case PIRATE:
					nationFileName = "ships\parus_" + sUpgrade + "_pirate.tga";
					//BI_objRetValue.normalTex = "ships\sail_Pirates.tga";
				break;
				case HOLLAND:	
					nationFileName = "ships\parus_" + sUpgrade + "_holland.tga";	
				break;
			}
			*/
			
			BI_objRetValue.maxSP = shref.sp;
			// boal -->
			if (CheckAttribute(shref, "EmblemedSails.normalTex")) // заднанный в типе парус
		    {
		        BI_objRetValue.normalTex = shref.EmblemedSails.normalTex;
		        nationFileName           = shref.EmblemedSails.normalTex;
		    }
			if( CheckAttribute(&Characters[chrIdx],"Features.GeraldSails") && sti(Characters[chrIdx].Features.GeraldSails)==true) 
			{
				makearef(arEmbl,shref.GeraldSails);
			} else {
				makearef(arEmbl,shref.EmblemedSails);
			} 
			/*if (CheckAttribute(shref, "GeraldSails"))
		    {
		        makearef(arEmbl, shref.GeraldSails);  */
				// boal <--
			sq = GetAttributesNum(arEmbl);
			for(i=0; i<sq; i++)
			{
				arSail = GetAttributeN(arEmbl,i);
				attrName = GetAttributeName(arSail);
				tmpStr = GetAttributeValue(arSail);
				if( CheckAttribute(arSail,"hscale") ) {
					BI_objRetValue.(attrName).hscale = arSail.hscale;
				}
				if( CheckAttribute(arSail,"vscale") ) {
					BI_objRetValue.(attrName).vscale = arSail.vscale;
				}
				if(tmpStr=="1") {
					//BI_objRetValue.(attrName).Gerald = nationFileName;  
					BI_objRetValue.(attrName) = nationFileName;
				} else {
					BI_objRetValue.(attrName).Gerald = tmpStr;
				}
				//BI_objRetValue.(attrName).Gerald = "ships\chuckskull.tga"; // текстура герба (если не указана, то берется BI_objRetValue.geraldTex или BI_objRetValue.geraldTexPointer)
				//BI_objRetValue.(attrName).hscale = 0.5; // масштаб в размере паруса (0.5 - герб занимает половину паруса)
				//BI_objRetValue.(attrName).vscale = 0.5; // если нет vscale, то используется = scale
			}
			//}
		}
	}

	return &BI_objRetValue;
}

ref procGetRiggingData()
{
	int i,n,s;

	string datName = GetEventData();
	i = GetEventData();
	n = GetEventData();
	s = GetEventData();	// isSpecial Flag ??	
	
	if(datName == "GetShipFlagTexNum")
	{
		aref rCharacter = GetEventData();

		switch(n)
		{
			case HOLLAND: 	BI_intNRetValue[0] = 0; break;						
			case ENGLAND: 	BI_intNRetValue[0] = 1; break;
			case FRANCE: 	BI_intNRetValue[0] = 2; break;
			case SPAIN: 	BI_intNRetValue[0] = 3; break;
			
			case PIRATE: 	
					BI_intNRetValue[0] = GetPirateFlag(rCharacter); 
					BI_intNRetValue[1] = FLAG_PIR; 		
			break;			
		}
		if(n != PIRATE)
		{
			if(s == 1)	BI_intNRetValue[1] = GetShipFlagTextureNum(rCharacter); 	
			else 		BI_intNRetValue[1] = FLAG_CMN; 
		}			
	}
	
	if(datName == "GetTownFlagTexNum")
	{				
		switch(n)
		{
			case HOLLAND: 	BI_intNRetValue[0] = 0; break;						
			case ENGLAND: 	BI_intNRetValue[0] = 1; break;
			case FRANCE: 	BI_intNRetValue[0] = 2; break;
			case SPAIN: 	BI_intNRetValue[0] = 3; break;						
			case PIRATE: 	
				BI_intNRetValue[0] = 0; 		
				BI_intNRetValue[1] = FLAG_PIR; 		
			break;
		}		
		if(n != PIRATE)
		{	
			if(s == 1) BI_intNRetValue[1] = FLAG_FRT; 
			else	   BI_intNRetValue[1] = FLAG_FRT; 	// приходится вот так вот изгаляться, тк не все модели тулом читаются :( 
		}				
	}	
	return &BI_intNRetValue;
}

// --> ugeen
void SetTownFlag(ref loc, object mdl)
{
	if(loc.id == "Caiman_Jungle_01")
	{
		SendMessage(&Flag, "lil", MSG_FLAG_INIT_TOWN, &mdl, ENGLAND);
		return;
	}
	if (!CheckAttribute(loc, "townsack")) return;
	int iNation = GetCityNation(loc.townsack);
	if(iNation == PIRATE) 
	{	
		SendMessage(&Flag, "lil", MSG_FLAG_INIT_TOWN, &mdl, iNation);
		return;
	}
	SendMessage(&Flag, "lil", MSG_FLAG_INIT_TOWN, &mdl, iNation);
}

void SetFortFlag(ref rModel)
{
	if (!CheckAttribute(rModel, "fortcmdridx")) return;
	int idx = sti(rModel.fortcmdridx);
	if (idx < 0) return;
	ref chr = GetCharacter(idx);
	int iNation = sti(chr.nation);
	if(iNation == PIRATE) 
	{		
		SendMessage(&Flag, "lil", MSG_FLAG_INIT_TOWN, &rModel, iNation);
		return;
	}		
	SendMessage(&Flag, "lil", MSG_FLAG_INIT_TOWN, &rModel, iNation);	
}

int GetPirateFlag(ref chr)
{
	if(!CheckAttribute(chr,"id")) return 0;
	if(CheckAttribute(chr, "Flags.Pirate")) 
	{
		return sti(chr.Flags.Pirate);
	}	
	string sGroup = GetGroupIDFromCharacter(chr);
	if(sGroup == "") return 0;
	ref cmdr = Group_GetGroupCommander(sGroup);
	if (!CheckAttribute(cmdr, "Flags.Pirate")) 
	{
		cmdr.Flags.Pirate = rand(2);
	}	
	return sti(cmdr.Flags.Pirate); 
}

bool IsShipCommander(ref chr)
{
	string sGroup = GetGroupIDFromCharacter(chr);
	if(sGroup == "") return 0;
	ref cmdr = Group_GetGroupCommander(sGroup);
	if(chr.id == cmdr.id) return true;
	return false;
}

bool IsShipMerchant(ref chr)
{
	if (CheckAttribute(chr, "RealEncounterType") && 
	    CheckAttribute(chr, "Ship.Mode") && 
		chr.Ship.Mode == "trade") return true;
	return false;
}

int GetShipFlagTextureNum(ref chr)
{
	if(!CheckAttribute(chr,"id")) return 0;	
	int iNation = sti(chr.nation);
	
	if(iNation == PIRATE) return FLAG_PIR;
	else
	{		
		//если сдался - выбрасывает белый флаг
		if(CheckAttribute(chr,"surrendered")) return FLAG_WHT;			
		else
		{		
			if(IsCompanion(chr) || IsMainCharacter(chr) || chr.id == "BoatChar") // ГГ , компаньоны, шлюпка у берега
			{
				if(iNation != PIRATE) return FLAG_PER;								
				else				  return FLAG_PIR; 	
			}			
			else
			{			
				// командующие эскадрами
				if(IsShipCommander(chr)) return FLAG_SHP;								
				else
				{
					// купчишки
					if(IsShipMerchant(chr)) return FLAG_MER;								
					// все прочие .. военные патрули, эскорты и т.п.
					else 					return FLAG_FRT;									
				}				
			}			
		}					
	}		
	return FLAG_CMN;
}
// <-- ugeen

void procBISelectShip()
{
	int chrIdx = GetEventData();
	int isMyChr = GetEventData();

	if(chrIdx==nMainCharacterIndex)	chrIdx = -1;

	float fShSpeed = 0.005;
	float fShAmp = 1.0;
	float fShW = 1.0;
	float fShH = 1.0;
	float fTop = 5.0;

	SendMessage(&objShipPointer,"lllfffff",MSG_SP_CHANGESHIP,chrIdx,isMyChr,fShSpeed,fShAmp,fShW,fShH,fTop);
}

ref procGetSmallFlagData()
{
	int chrIdx = GetEventData();
	BI_intNRetValue[0] = 3;
	BI_intNRetValue[1] = 0;
	if( chrIdx >= 0 ) {
		int iNation = sti(Characters[chrIdx].nation);
		switch( iNation )
		{
		case ENGLAND: BI_intNRetValue[1]=3; break;
		case FRANCE: BI_intNRetValue[1]=2; break;
		case SPAIN: BI_intNRetValue[1]=0; break;
		case HOLLAND: BI_intNRetValue[1]=4; break;
		case PIRATE: BI_intNRetValue[1]=5; break;
		//case SMUGGLER: BI_intNRetValue[1]=1; break;
		}

		BI_intNRetValue[2] = 7;
		switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
		{
			case RELATION_FRIEND:	BI_intNRetValue[2] = 7; break;
			case RELATION_NEUTRAL:	BI_intNRetValue[2] = 7; break;
			case RELATION_ENEMY:	BI_intNRetValue[2] = 6; break;
		}
	}
	return &BI_intNRetValue;
}

void procMastFall()
{
	int chrIdx = GetEventData();
	string mastName = GetEventData();
	int bFirstFall = GetEventData();

	if(chrIdx<0) return;
	int mastNum = strcut(mastName,4,strlen(mastName)-1);

	//trace("For character "+chrIdx+" fall Mast name "+mastName+" has index "+mastNum);
	SendMessage(&Sailors, "lal", MSG_PEOPLES_ON_SHIP_MASTFALL, GetCharacter(chrIdx), mastNum);
}

bool CheckInstantRepairCondition(ref chref)
{
//boal -->
	if(MOD_SKILL_ENEMY_RATE > 9) return false; // belamour legendary edition только для ОК
    if (CheckOfficersPerk(chref,"InstantRepair")) return false;  // уже в деле
    if (!GetOfficersPerkUsing(chref,"InstantRepair")) return false;  // можно включить?
//boal <--

	float chrShipHP = GetHullPercent(chref);
	float chrShipSP = GetSailPercent(chref);

	bool bYesHPRepair = chrShipHP < InstantRepairRATE;// boal 23.01.2004
	bool bYesSPRepair = chrShipSP < InstantRepairRATE; // boal 23.01.2004

	if( bYesHPRepair )	{ bYesHPRepair = GetCargoGoods(chref,GOOD_PLANKS)>0; }
	if( bYesSPRepair )	{ bYesSPRepair = GetCargoGoods(chref,GOOD_SAILCLOTH)>0; }

	return bYesHPRepair || bYesSPRepair;
}

void BI_PerkAgainUsable()
{
	BI_SetCommandMode(-1,-1,-1,-1);
}

float GetRepairGoods(bool bIsHull, ref chref)
{
	float fGoodsQ = 0.0;

	if( bIsHull )
	{
		fGoodsQ = GetCargoGoods(chref,GOOD_PLANKS);
		if( CheckAttribute(chref,"RepairMaterials.forHull") )   // погрешность округления списания колва досок за процент
		{	
			fGoodsQ += stf(chref.RepairMaterials.forHull);
		}
	}
	else
	{
		fGoodsQ = GetCargoGoods(chref,GOOD_SAILCLOTH);
		if( CheckAttribute(chref,"RepairMaterials.forSails") )
		{	
			fGoodsQ += stf(chref.RepairMaterials.forSails);
		}
	}

	return fGoodsQ;
}

void RemoveRepairGoods(bool bIsHull, ref chref, float matQ)
{
	int nGoodsQ = 0;
	float fGoodsQ = GetRepairGoods(bIsHull,chref);

	if( bIsHull )
	{
		if(fGoodsQ<=matQ)	{ DeleteAttribute(chref,"RepairMaterials.forHull"); }
		else
		{
			fGoodsQ -= matQ;
			nGoodsQ = makeint(fGoodsQ);
			chref.RepairMaterials.forHull = fGoodsQ - nGoodsQ;
		}
		SetCharacterGoods(chref,GOOD_PLANKS,nGoodsQ);
	}
	else
	{
		if(fGoodsQ<=matQ)	{ DeleteAttribute(chref,"RepairMaterials.forSails"); }
		else
		{
			fGoodsQ -= matQ;
			nGoodsQ = makeint(fGoodsQ);
			chref.RepairMaterials.forSails = fGoodsQ - nGoodsQ;
		}
		SetCharacterGoods(chref,GOOD_SAILCLOTH,nGoodsQ);
	}

}

float GetRigDamage(int shootIdx, int iBallType, ref damage_chr)
{
	if (LAi_IsImmortal(damage_chr)) return 0.0;
	ref rBall = GetGoodByType(iBallType);
	float fDistanceDamageMultiply = Bring2Range(1.2, 0.25, 0.0, stf(AIBalls.CurrentMaxBallDistance), stf(AIBalls.CurrentBallDistance));
	float fDmgRig = fDistanceDamageMultiply * stf(rBall.DamageRig);
	//float fDmgRig = stf(rBall.DamageRig);
    if (shootIdx>=0 )
	{
		ref shoot_chr = GetCharacter(shootIdx);
		if (CheckOfficersPerk(shoot_chr,"CannonProfessional") )	{ fDmgRig *= 1.3; }
		else
		{
			if( CheckOfficersPerk(shoot_chr,"SailsDamageUp") )	{ fDmgRig *= 1.15; }
		}
	}
	
	if (CheckOfficersPerk(damage_chr,"ShipDefenseProfessional") )	{ fDmgRig *= 0.65; } // fix
	else
	{
		if (CheckOfficersPerk(damage_chr,"AdvancedBattleState") )	{ fDmgRig *= 0.75; } // fix
		else
		{
			if (CheckOfficersPerk(damage_chr,"BasicBattleState") )	{ fDmgRig *= 0.85; } // fix
		}
	}
	
	fDmgRig = fDmgRig * isEquippedArtefactUse(shoot_chr, "indian_8", 1.0, 1.05 ); // belamour фикс читерства амулета
	fDmgRig = fDmgRig * isEquippedArtefactUse(damage_chr, "amulet_9", 1.0, 0.95 ); // belamour 
    fDmgRig = fDmgRig * isEquippedArtefactUse(damage_chr, "talisman7", 1.0, 0.95 ); // belamour legendary edition скарабей
	if(IsCharacterEquippedArtefact(shoot_chr, "talisman19")) 
	{
		fDmgRig *= 1.0 + Bring2Range(0.0, 0.25, 0.0, 50.0, (100.0 - GetHullPercent(shoot_chr)) / 2.0);
	}
	// Addon 2016-1 Jason Пиратская линейка
	if (CheckAttribute(damage_chr, "SeaBoss")) { fDmgRig *= 0.1; }

	return fDmgRig;
}

void MakeSailDmg(int chrIdx, float dmg)
{
	object objSail;
	if( !GetEntity(&objSail,"sail") )
	{
		return;
	}
	int iSailsUpgrade = 1;
	if(!CheckAttribute(&characters[chrIdx], "upgrades.sails"))
	{
		characters[chrIdx].upgrades.sails = 1;
	}
	//убираем 1 вариант апгрейда (паруса по умолчанию))
	iSailsUpgrade = sti(characters[chrIdx].upgrades.sails) - 1;
	dmg = dmg + ((dmg/100)*iSailsUpgrade*5);
	SendMessage(&objSail,"lslf", MSG_SAIL_SCRIPT_PROCESSING,"RandomSailsDmg", chrIdx,dmg);
}

ref ProcessRandomSailDmg()
{
	BI_g_fRetVal = 0.0;
	//"lslfflll"
	int chrIdx = GetEventData();
	string nodeName = GetEventData();
	int grNum = GetEventData();
	float fDmg = GetEventData();
	float fSPow = GetEventData();
	int hc_new = GetEventData();
	int mhc = GetEventData();
	int hdat_new = GetEventData();

	if(chrIdx<0) return &BI_g_fRetVal;
	ref chref = GetCharacter(chrIdx);
    if(LAi_IsImmortal(chref)) return &BI_g_fRetVal;

	aref arSail;
	string groupName = ""+grNum;
	makearef(arSail,chref.ship.sails.(nodeName).(groupName));

	int hc_old = 0;
	if( CheckAttribute(arSail,"hc") )	hc_old = sti(arSail.hc);
	float fDmg_old = 0.0;
	if( CheckAttribute(arSail,"dmg") )	fDmg_old = stf(arSail.dmg);

	int itmp = hc_new;
	float sailDmgMax = GetCharacterShipSP(chref) * fSPow;

	float fTopDmg = sailDmgMax;
	if(itmp<mhc)	fTopDmg = GetNeedDmgFromHole(itmp+1,sailDmgMax,mhc) - 0.0001;
	if(fTopDmg>fDmg_old+fDmg)	fTopDmg = fDmg_old+fDmg;

	fDmg = fTopDmg-fDmg_old;
	if(fDmg<=0.0)	return &BI_g_fRetVal;
	chref.ship.SP = stf(chref.ship.SP)-fDmg;

	itmp = GetNeedHoleFromDmg(fTopDmg,sailDmgMax,mhc);
	if(itmp>hc_old)
	{
		BI_g_fRetVal = fDmg;
		arSail.hc = hc_new;
		arSail.hd = hdat_new;
	}
	else
	{
		BI_g_fRetVal = -fDmg;
		if( !CheckAttribute(arSail,"hc") )	arSail.hc = 0;
		if( !CheckAttribute(arSail,"hd") )	arSail.hd = 0;
	}

	arSail.mhc = mhc;
	arSail.sp = fSPow;
	arSail.dmg = fTopDmg;

	return &BI_g_fRetVal;
}

// ~!~
void GetSailStatus(int chrIdx)
{	
	object objSail;
	if( !GetEntity(&objSail,"sail") )
	{
		return;
	}
	if(chrIdx < 0) return;
	ref chref = GetCharacter(chrIdx);
	DeleteAttribute(chref,"ship.sailstatus"));
	SendMessage(&objSail,"lsl", MSG_SAIL_SCRIPT_PROCESSING,"GetSailStatus", chrIdx);
}	

void procGetSailStatus()
{
	int chrIdx 		= GetEventData();
	string nodeName = GetEventData();
	int grNum 		= GetEventData();
	float fSPow 	= GetEventData();
	int hc 			= GetEventData();
	int mhc 		= GetEventData();
	
	if(chrIdx < 0) return;
	ref chref = GetCharacter(chrIdx);
	
	aref arSail;
	string groupName = ""+grNum;
	chref.ship.sailstatus = sti(chref.ship.sailstatus) + 1;
	
	makearef(arSail,chref.ship.sailstatus.(nodeName).(groupName));
	
	arSail.mhc 	= mhc;
	arSail.hc 	= hc;
	arSail.sp 	= fSPow;
}

void procSetUsingAbility()
{
	//Log_Info("procSetUsingAbility");
	int q;
	int chIdx = GetEventData();
	int mainIdx = sti(pchar.index);
	aref aroot,arcur;
	string tmpStr;

	if( chIdx<0 || CharacterIsDead(GetCharacter(chIdx)) )
	{
		makearef(aroot,BattleInterface.AbilityIcons);
		q = GetAttributesNum(aroot);
		for(int i=0; i<q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		return;
	}

	// для главного персонажа
	if(mainIdx==chIdx)
	{
		
        BattleInterface.Commands.Bomb.enable = true;
		BattleInterface.Commands.Brander.enable			= false;
		//BattleInterface.AbilityIcons.Troopers.enable		= false;

        //if (bBettaTestMode) BattleInterface.AbilityIcons.InstantBoarding.enable	= bAttack;
		////////////////////////////////////////////
		BattleInterface.Commands.ImmediateReload.enable	= false; //GetCharacterPerkUsing
        if (!CheckOfficersPerk(pchar, "ImmediateReload") && GetOfficersPerkUsing(pchar, "ImmediateReload"))
        {
            BattleInterface.Commands.ImmediateReload.enable = true;
        }
		BattleInterface.Commands.LightRepair.enable		= false;
		if (!CheckOfficersPerk(pchar, "LightRepair") && GetOfficersPerkUsing(pchar,"LightRepair"))
		{
            if(GetHullPercent(pchar)<10.0 || GetSailPercent(pchar)<10.0)
			{
                BattleInterface.Commands.LightRepair.enable = true;
			}
		}
		BattleInterface.Commands.InstantRepair.enable	= CheckInstantRepairCondition(pchar);
		BattleInterface.Commands.Turn180.enable = false;
		if (!CheckOfficersPerk(pchar, "Turn180") && GetOfficersPerkUsing(pchar, "Turn180"))
        {
			BattleInterface.Commands.Turn180.enable = true;
        }
		// Set items abilities
		q = FindQuestUsableItem(&arcur,0);
		while( q>0 )
		{
			tmpStr = arcur.id;
			if( GetCharacterItem(pchar,arcur.id)>0 )
			{
				BattleInterface.AbilityIcons.(tmpStr).enable	= true;
				BattleInterface.AbilityIcons.(tmpStr).picNum	= arcur.quest.pic;
				BattleInterface.AbilityIcons.(tmpStr).texNum	= 9;
				BattleInterface.AbilityIcons.(tmpStr).event		= arcur.id;
				BattleInterface.AbilityIcons.(tmpStr).quest		= arcur.quest;
			}
			else
			{
				BattleInterface.AbilityIcons.(tmpStr).enable	= false;
			}
			q = FindQuestUsableItem(&arcur,q+1);
		}
		ControlsDesc();
	}

	else
	{
		BattleInterface.Commands.Brander.enable			= false;
		BattleInterface.Commands.Bomb.enable = true;
		if(bAttack && GetRemovable(GetCharacter(chIdx)) && GetOfficersPerkUsing(pchar,"Brander"))
		{
			BattleInterface.Commands.Brander.enable		= true;
		}
		//BattleInterface.AbilityIcons.Troopers.enable		= GetCharacterPerkUsing(pchar,"Troopers");

		BattleInterface.Commands.InstantRepair.enable	= CheckInstantRepairCondition(GetCharacter(chIdx));		
		BattleInterface.Commands.ImmediateReload.enable	= GetCharacterPerkUsing(GetCharacter(chIdx), "ImmediateReload");//false;
		BattleInterface.Commands.InstantBoarding.enable	= false;
		BattleInterface.Commands.LightRepair.enable		= GetCharacterPerkUsing(GetCharacter(chIdx), "LightRepair");//false;
		if (GetCharacterPerkUsing(GetCharacter(chIdx),"LightRepair"))
		{
            if(GetHullPercent(GetCharacter(chIdx))<10.0 || GetSailPercent(GetCharacter(chIdx))<10.0)
			{
                BattleInterface.Commands.LightRepair.enable = true;
			}
		}
		BattleInterface.Commands.Turn180.enable			= GetCharacterPerkUsing(GetCharacter(chIdx), "Turn180");//false;
	}
}

ref procCheckEnableLocator()
{
	BI_intRetValue = true;

	string comName = GetEventData();
	aref arLoc = GetEventData();

	if(comName=="BI_SailTo")
	{
		if( CheckAttribute(&AISea,"Island") && CheckAttribute(arLoc,"name") )
		{
			BI_intRetValue = Island_isGotoEnableLocal(AISea.Island,arLoc.name);
		}
	}

	return &BI_intRetValue;
}

ref procCheckEnableShip()
{
	BI_intRetValue = true;

	string comName = GetEventData();
	int cn = GetEventData();

	ref rCommander;

	if(cn>=0)
	{
		switch(comName)
		{
		case "BI_InstantBoarding":
			BI_intRetValue = true;
		break;
		
		/*case "BI_Speak":
			BI_intRetValue = true;
		break;*/
		}
	}

	return &BI_intRetValue;
}

void BI_ProcessControlPress()
{
	string ControlName = GetEventData();
	if( sti(InterfaceStates.Launched) != 0 ) {return;}
	if(XI_IsKeyPressed("alt") && !CheckAttribute(&objControlsState,"keygroups.AltPressedGroup"+"."+ControlName)) return;
	if(!XI_IsKeyPressed("alt") && CheckAttribute(&objControlsState,"keygroups.AltPressedGroup"+"."+ControlName)) return;
	switch(ControlName)
	{
		case "hk_charge1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_balls.wav");
			Ship_ChangeCharge(pchar, GOOD_BALLS);
		break;
	
		case "hk_charge2":
			PlaySound("interface\" + LanguageGetLanguage() + "\_grapes.wav");
			Ship_ChangeCharge(pchar, GOOD_GRAPES);
		break;
	
		case "hk_charge3":
			PlaySound("interface\" + LanguageGetLanguage() + "\_chain.wav");
			Ship_ChangeCharge(pchar, GOOD_KNIPPELS);
		break;
	
		case "hk_charge4":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs.wav");
			Ship_ChangeCharge(pchar, GOOD_BOMBS);
		break;
		
		case "hk_Cabin":
			if(sti(RealShips[sti(pchar.Ship.Type)].BaseType) > SHIP_WAR_TARTANE && !bSeaReloadStarted) // pchar.Ship.Type != SHIP_NOTUSED
			{
				Sea_CabinStartNow();
			}
		break;
		
		case "hk_ImmediateReload":
			if(!CheckOfficersPerk(pchar, "ImmediateReload") && GetOfficersPerkUsing(pchar,"ImmediateReload"))
			{
				ActivateCharacterPerk(pchar,"ImmediateReload");
				ControlsDesc();
			}
			else PlaySound("interface\knock.wav");
		break;
		
		case "hk_InstantRepair":
			if(CheckInstantRepairCondition(pchar))
			{
				ActivateCharacterPerk(pchar,"InstantRepair");
				ActivateSpecRepair(pchar,1);
			}
			else PlaySound("interface\knock.wav");
		break;
		
		case "hk_LightRepair":
			if(!CheckOfficersPerk(pchar, "LightRepair") && GetOfficersPerkUsing(pchar,"LightRepair"))
			{
				if(GetHullPercent(pchar)<10.0 || GetSailPercent(pchar)<10.0)
				{
					ActivateCharacterPerk(pchar,"LightRepair");
					ActivateSpecRepair(pchar,0);
				}
				else PlaySound("interface\knock.wav");
			}
			else PlaySound("interface\knock.wav");
		break;
		
		case "hk_Turn180":
			if(!CheckOfficersPerk(pchar, "Turn180") && GetOfficersPerkUsing(pchar,"Turn180"))
			{
				ActivateCharacterPerk(pchar,"Turn180");
				Ship_Turn180(pchar);
				ControlsDesc();
			}
			else PlaySound("interface\knock.wav");
		break;
		
		case "CannonsRange":
			bCannonsRangeShow = !bCannonsRangeShow;
			if (Whr_IsNight()) SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, argb(0,255,255,255), argb(15,255,255,255), argb(0,255,0,0), argb(55,255,0,0), 0.002, 0.002, bCannonsRangeShow);
			else SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, argb(0,255,255,255), argb(25,255,255,255), argb(0,255,0,0), argb(75,255,0,0), 0.002, 0.002, bCannonsRangeShow);
		break;

		case "IRightShift":
			ControlsDesc();
		break;

		case "ShiftUp":
			ControlsDesc();
		break;
		
		case "BICommandsActivate": 
			PlaySound("interface\ok.wav"); // boal даешь звуки!
		break;
	}
}

ref procGetSRollSpeed()
{
	int chrIdx = GetEventData();
	BI_g_fRetVal = 0.0;
	if(chrIdx>=0) BI_g_fRetVal = GetRSRollSpeed(GetCharacter(chrIdx));
	return &BI_g_fRetVal;
}
// скорость подъема паруса
float GetRSRollSpeed(ref chref)
{
	int iShip = sti(chref.ship.type);
	if( iShip<0 || iShip>=REAL_SHIPS_QUANTITY ) {return 0.0;}
	
	float fRollSpeed = 0.5 + 0.05 * makefloat( GetSummonSkillFromNameToOld(chref,SKILL_SAILING) ); //fix skill
	int crewQ = GetCrewQuantity(chref);
	//int crewMin = sti(RealShips[iShip].MinCrew);
	if (!CheckAttribute(&RealShips[iShip], "MaxCrew"))
	{
		Log_TestInfo("GetRSRollSpeed нет MaxCrew у корабля НПС ID=" + chref.id);
		return 0.0;
	}
 	int crewMax = sti(RealShips[iShip].MaxCrew);
 	int crewOpt = sti(RealShips[iShip].OptCrew);//boal
 	if (crewMax < crewQ) crewQ  = crewMax; // boal
	//if(crewQ < crewMin) fRollSpeed *= makefloat(crewQ)/makefloat(2*crewMin);
	//fRollSpeed = fRollSpeed * (0.5 + makefloat(crewQ)/makefloat(2*crewMax)); // уменьшение скорости разворота от команды
	//fRollSpeed = fRollSpeed * makefloat(crewQ)/makefloat(crewMax);
	// опыт матросов 
	float  fExp;
	
	if (crewOpt <= 0) crewOpt = 0; // fix для профилактики деления на ноль
	
	fExp = 0.05 + stf(GetCrewExp(chref, "Sailors") * crewQ) / stf(crewOpt * GetCrewExpRate());
	if (fExp > 1) fExp = 1;
	fRollSpeed = fRollSpeed * fExp;
	// мораль
	float  fMorale = stf(stf(GetCharacterCrewMorale(chref)) / MORALE_MAX);
	fRollSpeed = fRollSpeed * (0.7 + fMorale / 2.0);

	if (iArcadeSails != 1)
	{
		fRollSpeed = fRollSpeed / 2.5;
	}
	if(CheckOfficersPerk(chref, "SailsMan"))
	{
		fRollSpeed = fRollSpeed * 1.1; // 10%
	}
	return fRollSpeed;
}

ref BI_GetLandData()
{
	int iTmp;
	string attrName;
	aref arLoc, arIsl, arList;
	arLoc = GetEventData();

	BI_intNRetValue[0] = 0;
	BI_intNRetValue[1] = BI_RELATION_NEUTRAL;
	BI_intNRetValue[2] = -1;
	BI_intNRetValue[3] = -1;
	BI_intNRetValue[4] = -1;
	BI_intNRetValue[5] = -1;
	BI_intNRetValue[6] = 0;

	if( CheckAttribute(arLoc,"fort.model") )
	{
		BI_intNRetValue[0] = 1; // тип форт
		int chrIdx = Fort_FindCharacter(AISea.Island,"reload",arLoc.name);
		if(chrIdx>=0)
		{
			switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
			{
			case RELATION_FRIEND:	BI_intNRetValue[1] = BI_RELATION_FRIEND; break;
			case RELATION_NEUTRAL:	BI_intNRetValue[1] = BI_RELATION_NEUTRAL; break;
			case RELATION_ENEMY:	BI_intNRetValue[1] = BI_RELATION_ENEMY; break;
			}
			BI_intNRetValue[5] = chrIdx;
		}
	}
	else
	{
		if( CheckAttribute(arLoc,"istown") && arLoc.istown=="1" )
		{
			iTmp = FindLocation( arLoc.go );
			if( iTmp>=0 ) {
				iTmp = FindColony( Locations[iTmp].fastreload );
				if( iTmp>=0 ) {
					BI_intNRetValue[0] = 2; // тип город
					switch( GetNationRelation2MainCharacter(sti(Colonies[iTmp].nation)) )
					{
					case RELATION_FRIEND:	BI_intNRetValue[1] = BI_RELATION_FRIEND; break;
					case RELATION_NEUTRAL:	BI_intNRetValue[1] = BI_RELATION_NEUTRAL; break;
					case RELATION_ENEMY:	BI_intNRetValue[1] = BI_RELATION_ENEMY; break;
					}
					BI_intNRetValue[6] = sti(Colonies[iTmp].disease);
				}
			}
		}
		else
		{// не форт, не город - маяк/бухта!
			if(CheckAttribute(arLoc,"label") && HasSubStr(arLoc.label, "mayak")) BI_intNRetValue[0] = 4; // тип маяк
			else BI_intNRetValue[0] = 3; // тип бухта
		}
	}
	/*if( CheckAttribute(arLoc,"tex") && CheckAttribute(arLoc,"pic") )
	{
		makearef( arIsl, Islands[FindIsland(AISea.Island)] );
		attrName = "InterfaceTextures." + arLoc.tex;
		if( CheckAttribute(arIsl,attrName) )
		{
			BI_intNRetValue[2] = AddTextureToList( &BattleInterface, arIsl.(attrName), sti(arIsl.(attrName).h)*2, sti(arIsl.(attrName).v) );
			BI_intNRetValue[3] = sti(arLoc.pic);
			BI_intNRetValue[4] = sti(arLoc.pic) + sti(arIsl.(attrName).h);
		}
	}*/

	int g_LocLngFileID = LanguageOpenFile("LocLables.txt");
	if( CheckAttribute(arLoc,"label") ) {
		arLoc.labelLoc = LanguageConvertString(g_LocLngFileID,arLoc.label);
		if( arLoc.labelLoc == "" ) {
			Trace("Warning! Language: string <"+arLoc.label+"> hav`t translation into file <LocLables.txt>");
		}
	}
	LanguageCloseFile(g_LocLngFileID);

	if( BI_intNRetValue[2]<0 || BI_intNRetValue[3]<0 )
	{
		BI_intNRetValue[2] = 0;//AddTextureToList( &BattleInterface, "battle_interface\cicons_locators.tga", 8, 1 );
		switch (BI_intNRetValue[0])
		{
			case 1: // форт
				BI_intNRetValue[3] = 62;
				BI_intNRetValue[4] = 46;
			break;
			case 2: // город
				BI_intNRetValue[3] = 63;
				BI_intNRetValue[4] = 47;
            break;
            case 3: // бухта
				BI_intNRetValue[3] = 31;
				BI_intNRetValue[4] = 15;
            break;
            case 4: // маяк
				BI_intNRetValue[3] = 79;
				BI_intNRetValue[4] = 78;
            break;
		}
	}

	return &BI_intNRetValue;
}

int GetTargChrIndex(int targNum, string locName)
{
	if(targNum==-1) {
		return Fort_FindCharacter(AISea.Island,"reload",locName);
	} else {
		return targNum;
	}
}

bool CheckSuccesfullBoard(ref rBoarderChr, ref rSieger)
{
	if (bBettaTestMode) return true;
	if (LAi_IsDead(rSieger)) return false;  // fix
	// skill = 1 -> k = 0.5; skill = 10 -> k = 2.0
	float k = 0.333 + GetSummonSkillFromNameToOld(rBoarderChr, SKILL_SNEAK)*0.167;

	// skill = 1 -> limit = 0.45 -> 0.2^0.5 (20%);   skill = 10 -> limit = 0.81 -> 0.9^2 (90%)
	float topLimit = 0.41 + GetSummonSkillFromNameToOld(rBoarderChr, SKILL_GRAPPLING)*0.04;

	if( pow(rand(1000)/1000.0, k) < topLimit ) return true;
	return false;
}

// НОВОЕ ГПК патч 1.2.3
// рандомный герб на парус
void SetRandGeraldSail(ref chr, int nation)
{
	string ret = "";
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	// 1.2.3 переделка на герб привязан к кораблю, то есть при обмене сохранится
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		switch (nation)
		{
		    case ENGLAND:
		        ret = "eng_" + (1 + rand(4));
		    break;
	
	        case FRANCE:
	            ret = "fra_" + (1 + rand(5));
	        break;
	
	        case SPAIN:
	            ret = "spa_" + (1 + rand(4));
	        break;
	
	        case HOLLAND:
	            ret = "hol_" + (1 + rand(3));
	        break;
	
	        case PIRATE:
	            ret = "pir_" + (1 + rand(5));
	        break;
		}
		shref.ShipSails.Gerald_Name = ret + ".tga.tx";
	}		
}

void SetSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		
		shref.SailsColorIdx   = col;
		shref.ShipSails.SailsColor = SailsColors[col].color;
	}		
}

// Warship 04.06.09 Проверка, можно ли на паруса корабля персонажа поставить герб
bool CanSetSailsGerald(ref _char)
{
	int shipClass = GetCharacterShipClass(_char); // Если корабля нет, вернет 7 (лодка)
	
	if(shipClass > 4) // Проверка на класс корабля > 4
	{
		return false;
	}

	return true;
}

// LDH 13Feb17 - return moor location name or map region, adjusted for long strings and enlarged fonts
string GetBILocationName()
{
	string Name;
	if(CheckAttribute(pchar,"MoorName"))
	{	
		if (pchar.MoorName == " ")
			Name = GetCurLocationName();
		else
			Name = pchar.MoorName;
	}
	float fHtRatio = stf(Render.screen_y) / iHudScale;

	if (LanguageGetLanguage() != "russian" && strlen(Name) > 24 && fHtRatio > 1.0)
	{
		Name += strcut("               ", 0, makeint((fHtRatio - 1.0) * 10.0 + 0.5));
	}
	return Name;
}

void ControlsDesc()
{
	if(iControlsTips > 0 && !IsSteamDeck())
	{
		numLine = 7;
		sAttrB = "Con"+numLine+"Back";
		sAttr = "Con"+numLine;
		sAttrDes = "Con"+numLine+"desc";
		int colorbase	= argb(255,255,255,255);
		int colorused	= argb(255,255,255,192);
		int colorcd 	= argb(155,255,64,64);
		int colorempty	= argb(155,255,255,255);
		
		string cname = "";
		for(numline = 1; numline < 8; numline ++)
		{
			sAttrB = "Con"+numLine+"Back";
			sAttr = "Con"+numLine;
			sAttrDes = "Con"+numLine+"desc";

			BattleInterface.textinfo.(sAttrB).text = "" ;
			BattleInterface.textinfo.(sAttr).text = "";
			BattleInterface.textinfo.(sAttrDes).text = "" ;

			BattleInterface.textinfo.(sAttr).color = colorbase;
			BattleInterface.textinfo.(sAttrDes).color = colorbase;
			
		}

		numLine = 7;
		sAttrB = "Con"+numLine+"Back";
		sAttr = "Con"+numLine;
		sAttrDes = "Con"+numLine+"desc";

        // TUTOR-ВСТАВКА
		if(TW_IsActive())
		{
			if(objTask.sea == "1_Turn")
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("Ship_TurnRight");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Ship_TurnRight","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
				
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("Ship_TurnLeft");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Ship_TurnLeft","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
			}
			else if(objTask.sea == "2_TimeScale" || objTask.sea == "3_TimeScale")
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("TimeScale");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("TimeScale","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
			}
			else if(objTask.sea == "4_TimeScale")
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("TimeScaleFasterBA");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("TimeScaleFasterBA","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
			}
			else if(objTask.sea == "5_TimeScale")
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("TimeScaleSlowerBA");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("TimeScaleSlowerBA","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
				
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("TimeScale");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("TimeScale","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
			}
			else if(objTask.sea == "3_Sails" || objTask.sea == "4_Sails")
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("Ship_SailDown");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Ship_SailDown","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
			}
			return;
		}
		
		if(CheckAttribute(pchar,"Ship.POS.Mode") && pchar.Ship.POS.Mode != SHIP_WAR)
		{
			if(iControlsMode == 1)
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("BI_MapEnter");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("BI_MapEnter","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
			}

			BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("BICommandsActivate");
			BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("BICommandsActivate","ControlsNames.txt");
			BattleInterface.textinfo.(sAttrB).text = "1" ;
			numLine --;
			
			sAttr = "Con"+numLine;
			sAttrDes = "Con"+numLine+"desc";
			sAttrB = "Con"+numLine+"Back";
			
			if(!bGlobalTutor && sti(RealShips[sti(pchar.Ship.Type)].BaseType) > SHIP_WAR_TARTANE) // pchar.Ship.Type != SHIP_NOTUSED
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("hk_Cabin");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("hk_Cabin","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
			
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
			}

			BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("FireCamera_Set");
			BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("FireCamera_Set","ControlsNames.txt");
			BattleInterface.textinfo.(sAttrB).text = "1" ;
			numLine --;
			
			sAttr = "Con"+numLine;
			sAttrDes = "Con"+numLine+"desc";
			sAttrB = "Con"+numLine+"Back";

			if(GetCharacterEquipByGroup(pchar,SPYGLASS_ITEM_TYPE)!="" && or(SeaCameras.Camera == "SeaDeckCamera", SeaCameras.Camera == "SeaFireCamera"))
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("TelescopeMode");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("TelescopeMode","ControlsNames.txt");
			}
			else
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("ShipCamera_Forward");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("ChrCamCameraRadius","ControlsNames.txt");
			}
			BattleInterface.textinfo.(sAttrB).text = "1" ;
			numLine --;
			
			sAttr = "Con"+numLine;
			sAttrDes = "Con"+numLine+"desc";
			sAttrB = "Con"+numLine+"Back";
			
			BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("Ship_SailDown");
			BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Ship_SailDown","ControlsNames.txt");
			BattleInterface.textinfo.(sAttrB).text = "1" ;
			numLine --;
			
			sAttr = "Con"+numLine;
			sAttrDes = "Con"+numLine+"desc";
			sAttrB = "Con"+numLine+"Back";
			
			BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("Ship_SailUp");
			BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Ship_SailUp","ControlsNames.txt");
			BattleInterface.textinfo.(sAttrB).text = "1" ;
		}
		else
		{ 
			if(XI_IsKeyPressed("shift") && sti(GetCompanionQuantity(pchar) > 1))
			{
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("FLT_ProtFlagship");
				BattleInterface.textinfo.(sAttrDes).text = XI_ConvertString("msg_AIShip_7short");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
				
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("FLT_LowerSails");
				BattleInterface.textinfo.(sAttrDes).text = XI_ConvertString("msg_AIShip_6short");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
				
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("FLT_SailAway");
				BattleInterface.textinfo.(sAttrDes).text = XI_ConvertString("msg_AIShip_5short");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
				
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("FLT_LoadBombs");
				BattleInterface.textinfo.(sAttrDes).text = XI_ConvertString("msg_AIShip_4short");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
				
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("FLT_LoadChain");
				BattleInterface.textinfo.(sAttrDes).text = XI_ConvertString("msg_AIShip_3short");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
				
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("FLT_LoadGrapes");
				BattleInterface.textinfo.(sAttrDes).text = XI_ConvertString("msg_AIShip_2short");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
				
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("FLT_LoadBalls");
				BattleInterface.textinfo.(sAttrDes).text = XI_ConvertString("msg_AIShip_1short");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
			}
			else
			{
				if(sti(GetCompanionQuantity(pchar) > 1))
				{
					BattleInterface.textinfo.(sAttr).text = objControlsState.key_codes.VK_SHIFT.img;
					BattleInterface.textinfo.(sAttrDes).text = XI_ConvertString("FLT_Commands");
					BattleInterface.textinfo.(sAttrB).text = "1" ;

					numLine --;
					
					sAttr = "Con"+numLine;
					sAttrDes = "Con"+numLine+"desc";
					sAttrB = "Con"+numLine+"Back";
				}
				
				if(CheckOfficersPerkEnable("Turn180"))
				{
					BattleInterface.textinfo.(sAttrB).text = "1" ;
					BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("hk_Turn180");
					BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Turn180", "AbilityDescribe.txt");
					
					if(!CheckOfficersPerk(pchar, "Turn180") && GetOfficersPerkUsing(pchar,"Turn180"))
					{
						BattleInterface.textinfo.(sAttr).color = colorbase;
						BattleInterface.textinfo.(sAttrDes).color = colorbase;
					}
					else
					{
						if(AbilityTimeDuration("active", "Turn180") > 0)
						{
							BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Turn180", "AbilityDescribe.txt")+ " : "+ AbilityTimeDuration("active", "Turn180");
							BattleInterface.textinfo.(sAttr).color = colorused;
							BattleInterface.textinfo.(sAttrDes).color = colorused;
							
						}
						else
						{
							if(AbilityTimeDuration("delay", "Turn180") > 0)
							{
								BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Turn180", "AbilityDescribe.txt")+ " : "+ AbilityTimeDuration("delay", "Turn180");
								BattleInterface.textinfo.(sAttr).color = colorcd; 
								BattleInterface.textinfo.(sAttrDes).color = colorcd;
								
							}
						}
					}
					numLine --;
					
					sAttrB = "Con"+numLine+"Back"; 
					sAttr = "Con"+numLine;
					sAttrDes = "Con"+numLine+"desc";
					
				}
				
				if(CheckOfficersPerkEnable("InstantRepair") && MOD_SKILL_ENEMY_RATE < 9)
				{
					BattleInterface.textinfo.(sAttrB).text = "1" ;
					BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("hk_InstantRepair");
					BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("InstantRepair", "AbilityDescribe.txt");
					BattleInterface.textinfo.(sAttr).color = colorempty;
					BattleInterface.textinfo.(sAttrDes).color = colorempty;
					
					if(CheckInstantRepairCondition(pchar))
					{
						BattleInterface.textinfo.(sAttr).color = colorbase;
						BattleInterface.textinfo.(sAttrDes).color = colorbase;
					}
					else
					{
						if(AbilityTimeDuration("active", "InstantRepair") > 0)
						{
							BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("InstantRepair", "AbilityDescribe.txt")+ " : "+ AbilityTimeDuration("active", "InstantRepair");
							BattleInterface.textinfo.(sAttr).color = colorused; 
							BattleInterface.textinfo.(sAttrDes).color = colorused;
							
						}
						else
						{
							if(AbilityTimeDuration("delay", "InstantRepair") > 0)
							{
								BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("InstantRepair", "AbilityDescribe.txt")+ " : "+ AbilityTimeDuration("delay", "InstantRepair");
								BattleInterface.textinfo.(sAttr).color = colorcd; 
								BattleInterface.textinfo.(sAttrDes).color = colorcd;
								
							}
						}
					}
					numLine --;
					
					sAttrB = "Con"+numLine+"Back";
					sAttr = "Con"+numLine;
					sAttrDes = "Con"+numLine+"desc";
					
				}
				
				if(CheckOfficersPerkEnable("ImmediateReload"))
				{
					BattleInterface.textinfo.(sAttrB).text = "1" ;
					BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("hk_ImmediateReload");
					BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("ImmediateReload", "AbilityDescribe.txt");
					
					if(!CheckOfficersPerk(pchar, "ImmediateReload") && GetOfficersPerkUsing(pchar,"ImmediateReload"))
					{
						BattleInterface.textinfo.(sAttr).color = colorbase;
						BattleInterface.textinfo.(sAttrDes).color = colorbase;
					}
					else
					{
						if(AbilityTimeDuration("active", "ImmediateReload") > 0)
						{
							BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("ImmediateReload", "AbilityDescribe.txt")+ " : "+ AbilityTimeDuration("active", "ImmediateReload");
							BattleInterface.textinfo.(sAttr).color = colorused; 
							BattleInterface.textinfo.(sAttrDes).color = colorused;
							
						}
						else
						{
							if(AbilityTimeDuration("delay", "ImmediateReload") > 0)
							{
								BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("ImmediateReload", "AbilityDescribe.txt")+ " : "+ AbilityTimeDuration("delay", "ImmediateReload");
								BattleInterface.textinfo.(sAttr).color = colorcd; 
								BattleInterface.textinfo.(sAttrDes).color = colorcd;
								
							}
						}
					}
					numLine --;
					
					sAttrB = "Con"+numLine+"Back"; 
					sAttr = "Con"+numLine;
					sAttrDes = "Con"+numLine+"desc";
					
				}
				
				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("CannonsRange");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("CannonsRange","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";

				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("FireCamera_Set");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("FireCamera_Set","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";

				BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("Ship_Fire");
				BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Ship_Fire","ControlsNames.txt");
				BattleInterface.textinfo.(sAttrB).text = "1" ;
			}
		}
	}
}

bool bShowExtInfo()
{
	if(CheckAttribute(pchar,"Ship.POS.Mode"))
	{
		if(pchar.Ship.POS.Mode != SHIP_WAR && !iMoreInfo) return false;
	}
	return true;
}

bool bShowShipStates()
{
	if(!bShowExtInfo())
	{
		if(sti(pchar.ship.hp) >= GetCharacterShipHP(pchar) && sti(pchar.ship.sp) > 99)
		return false;
	}
	return true;
}

// belamour cle доступность быстрого перехода
bool bSailToEnable()
{
	int EffectRadius = 0;
	int iIsland = FindIsland(pchar.location);
	float x = stf(pchar.Ship.Pos.x);
	float z = stf(pchar.Ship.Pos.z);
	
	if(iIsland < 0) return false;
	
	if(!sti(Islands[iIsland].reload_enable))
	{
		return false;
	}
	if (bBettaTestMode || CheckAttribute(pchar, "Cheats.SeaTeleport"))
	{
		return true;
	}
	else
	{
		if(CheckAttribute(&Islands[iIsland],"EffectRadius"))
		{
			EffectRadius = sti(Islands[iIsland].EffectRadius); 
		}
		else
		{
			string sSpyGlass = GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE);
			if(sSpyGlass != "")
			{
				ref rItm = ItemsFromID(sSpyGlass);
				EffectRadius	= 5000 + sti(rItm.radius);
			}
			else EffectRadius	= 5000;
		}	
	}
	ref	rIsland = GetIslandByIndex(iIsland);
	aref arReload, arLocator;
	makearef(arReload, rIsland.reload);
	int	iNumReload = GetAttributesNum(arReload);
	for (int i=0;i<iNumReload;i++)
	{
		arLocator = GetAttributeN(arReload, i);
		float x1 = stf(arLocator.x);
		float z1 = stf(arLocator.z);
		if(sqr(x1 - x) + sqr(z1 - z) < sqr(EffectRadius)) return true;
	}
	
	return false;
}
