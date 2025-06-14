#include "storm-engine\battle_interface\log_msg.h"

#define LOG_FOR_SEA			1
#define LOG_FOR_LAND		2
#define LOG_FOR_WORLDMAP	3

object showWindow;

object ILogAndActions;
object IBoardingStatus;
bool   bYesBoardStatus;
string g_ActiveActionName;
string cname = "";

#define NOTIFICATIONS_SPEED 0.03
object Notifications[9];
int notificationsQty = -1;
int fTmp,fTmp2;

#event_handler("blieGetMsgIconRoot","BI_GetMsgIconRoot");

void InitLogInterface()
{
	SetEventHandler("SetWindowSize","LI_SetWindowSize",0);
	CreateEntity(&ILogAndActions,"ILogAndActions");
	DelEventHandler("SetWindowSize","LI_SetWindowSize");
	DeleteAttribute(&ILogAndActions,"");
	ILogAndActions.type = "";
	CreateLogEnvironment();
	CreatePicInfoEnvironment();
	CreateTimeSpeedEnvironment();
	CreateLevelUpEnvironment();							
	SendMessage(&ILogAndActions,"lll",LOG_AND_ACTIONS_INIT,sti(InterfaceStates.BattleShow.FastCommand),sti(InterfaceStates.BattleShow.LogString));
	// SetEventHandler(EVENT_LOCATION_LOAD,"LI_LocationLoad",0);
	SetEventHandler("BI_FastCommand","BI_FastCommand",0);
	SetEventHandler(BI_EVENT_SET_VISIBLE,"SetLogInterfaceVisible",0);
	LayerAddObject(EXECUTE,&ILogAndActions,-257);
	LayerAddObject(REALIZE,&ILogAndActions,-1);
	LayerAddObject(SEA_EXECUTE,&ILogAndActions,-257);
	LayerAddObject(SEA_REALIZE,&ILogAndActions,-1);
	
	for(int i = 0; i < 9; i++)
	{
		if(CheckAttribute(&Notifications[i],"printing")) DeleteAttribute(&Notifications[i],"printing");
		if(CheckAttribute(&Notifications[i],"str")) DeleteAttribute(&Notifications[i],"str");
		if(CheckAttribute(&Notifications[i],"index")) DeleteAttribute(&Notifications[i],"index");
		if(CheckAttribute(&Notifications[i],"lt")) DeleteAttribute(&Notifications[i],"lt");
	}
	notificationsQty = -1;

	InitActivePerkShower();
}

void Log_RemoveFromSingleLayers()
{
	LayerDelObject(EXECUTE,&ILogAndActions);
	LayerDelObject(REALIZE,&ILogAndActions);
	LayerDelObject(SEA_EXECUTE,&ILogAndActions);
	LayerDelObject(SEA_REALIZE,&ILogAndActions);
}

void Log_MoveToSingleLayers()
{
	LayerAddObject(EXECUTE,&ILogAndActions,-257);
	LayerAddObject(REALIZE,&ILogAndActions,-1);
	LayerAddObject(SEA_EXECUTE,&ILogAndActions,-257);
	LayerAddObject(SEA_REALIZE,&ILogAndActions,-1);
}

void LI_SetWindowSize()
{
	int w = GetEventData();
	int h = GetEventData();
	int bTVused = GetEventData();
	if(bTVused)	SetShowWindowParameters(bTVused,w,h,40,24,w-40,h-24);
	else	SetShowWindowParameters(bTVused,w,h,0,0,w,h);
}

void SetLogInterfaceVisible()
{
	int visibleFlag = GetEventData();
	SendMessage(&ILogAndActions,"ll",LI_SET_VISIBLE,visibleFlag);
}

void LI_LocationLoad()
{
	CreateILogAndActions(LOG_FOR_LAND);
}

void InitBattleInterfacesParameters()
{
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");
	bYesBoardStatus = false;
}

void CreateILogAndActions(int loadType)
{
	DeleteAttribute(&IBoardingStatus,"ActiveActions");
	if(loadType==LOG_FOR_SEA)
	{
		CreateSeaActionsEnvironment();
	}
	if(loadType==LOG_FOR_LAND)
	{
		CreateLandActionsEnvironment();
	}
	if(loadType==LOG_FOR_WORLDMAP)
	{
		CreateWorldMapActionsEnvironment();
	}
	SendMessage(&ILogAndActions,"lll",LOG_AND_ACTIONS_CHANGE,sti(InterfaceStates.BattleShow.FastCommand),sti(InterfaceStates.BattleShow.LogString));
	Log_SetActiveAction(g_ActiveActionName);
	CreatePicInfoEnvironment();
	SendMessage(&ILogAndActions,"l", LOG_REFRESH_PIC);
}

void Log_SetActiveAction(string actionName)
{
	if(bMainMenu) return;
	if(questMovieIsLockPlayerCtrl) return;
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	string sActionText, sTextFont;
	float fFontScale;
	int iTextWidth;
	int iKeyWidth = makeint(20 * fHtRatio);
	int iTextOffset = makeint(5 * fHtRatio);
	
	if(ILogAndActions.type=="sea" && g_ActiveActionName!=actionName)
	{
		// LDH 13Feb17 clear MoorName when leave moor location
		if (actionName != "Moor") pchar.MoorName = " ";
		RefreshBattleInterface();
	}
	
	g_ActiveActionName = actionName;
	// change text
	if(CheckAttribute(&ILogAndActions,"ActiveActions."+actionName+".Text") && actionName != "Map" && actionName != "EnterToSea" && !dialogRun)
    {
		if(iControlsTips > 1)//подсказки включены в настройках
		{
			sActionText = ILogAndActions.ActiveActions.(actionName).Text;
			sTextFont	= ILogAndActions.ActiveActions.text2.font;
			fFontScale	= ILogAndActions.ActiveActions.text1.scale;
			iTextWidth	= GetStringWidth(sActionText, sTextFont, fFontScale);
			if(actionName == "Closed")
            {
				ILogAndActions.ActiveActions.text1.text = "";
				ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2;
			}
            else 
            {
                cname = GetKeyByControl(FindControlFromActionName(actionName));
				if(CheckAttribute(&objControlsState,"key_codes."+cname+".img"))
					ILogAndActions.ActiveActions.text1.text = objControlsState.key_codes.(cname).img;
				ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right)/2 - makeint(iTextWidth/2) - iTextOffset;
				ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2 + iKeyWidth + iTextOffset;
			}
			ILogAndActions.ActiveActions.text2.text = ILogAndActions.ActiveActions.(actionName).Text;
		}
        else 
        {
			ILogAndActions.ActiveActions.text1.text = "";
			ILogAndActions.ActiveActions.text2.text = "";
		}
	}
    else
    {
		ILogAndActions.ActiveActions.text1.text = "";
		ILogAndActions.ActiveActions.text2.text = "";
	}
	SendMessage(&ILogAndActions,"ls",LOG_SET_ACTIVE_ACTION,actionName);
}

void Log_SetStringToLog(string strLog)
{
	SendMessage(&ILogAndActions,"lls",LOG_ADD_STRING, false, strLog);
}

void Notification(string strLog, string ability)
{
	if(Ability == "") return;
	if(CheckAttribute(pchar,"systeminfo.NoNotifications")) return;
	int IconIndex = -1;
	float fLifeTime = 30.0/NOTIFICATIONS_SPEED*0.01;
	
	switch (ability)
	{
		case "BasicDefense": IconIndex = 0; break;
		case "AdvancedDefense": IconIndex = 1; break;
		case "CriticalHit": IconIndex = 2; break;
		case "Dragoon": IconIndex = 3; break;
		case "FencingMaster": IconIndex = 4; break;
		case "Grus": IconIndex = 5; break;
		case "Berserker": IconIndex = 6; break;
		case "Tireless": IconIndex = 7; break;
		case "IronWill": IconIndex = 13; break;
		case "Medic": IconIndex = 15; break;
		case "Trustworthy": IconIndex = 18; break;
		case "MusketsShoot": IconIndex = 29; break;
		case "Brander": IconIndex = 47; break;
		case "Troopers": IconIndex = 48; break;
		case "Carpenter": IconIndex = 51; break;
		case "HPPlus": IconIndex = 57; break;
		case "EnergyPlus": IconIndex = 58; break;
		case "Mimicry": IconIndex = 65; break;
		case "Icollection": IconIndex = 71; break;
		case "Leadership": IconIndex = 72; break;
		case "FencingL": IconIndex = 73; break;
		case "FencingS": IconIndex = 74; break;
		case "FencingH": IconIndex = 75; break;
		case "Pistol": IconIndex = 76; break;
		case "Fortune": IconIndex = 77; break;
		case "Sneak": IconIndex = 78; break;
		case "X": IconIndex = 79; break;
		//case "кораблик": IconIndex = 80; break;
		case "Sailing": IconIndex = 81; break;
		case "Accuracy": IconIndex = 82; break;
		case "Cannons": IconIndex = 83; break;
		case "Grappling": IconIndex = 84; break;
		case "Defence": IconIndex = 85; break;
		case "Repair": IconIndex = 86; break;
		case "Commerce": IconIndex = 87; break;
		case "Document": IconIndex = 88; break;
		case "HealthDown": IconIndex = 89; break;
		case "HealthUp": IconIndex = 57; break;
		case "RepDown": IconIndex = 90; break;
		case "RepUp": IconIndex = 91; break;
		case "SeaFast": IconIndex = 92; break;
		case "DeadShip": IconIndex = 95; break;
		case "Dubloon": IconIndex = 96; break;
		case "Money": IconIndex = 97; break;
		case "Drunk": IconIndex = 98; break;
		//case "MapsAtlas": IconIndex = 99; break;
		case "SneakFail": IconIndex = 101; break;
		case "AmmoSelect": IconIndex = 102; break;
		case "AmmoNotSelect": IconIndex = 103; break;
		case "Capacity": IconIndex = 104; break;
		case "Alchemy": IconIndex = 106; break;
		case "BoxPlus": IconIndex = 107; break;
		case "BoxMinus": IconIndex = 108; break;
		case "MapsAtlas": IconIndex = 110; break;
		case "LogBook": IconIndex = 111; break;
		case "Cotton": IconIndex = 112; break;
		case "Ale": IconIndex = 113; break;
		case "Oil": IconIndex = 114; break;
		case "Fruits": IconIndex = 115; break;
		case "Chocolate": IconIndex = 116; break;
		case "ShipSilk": IconIndex = 117; break;
		case "Wine": IconIndex = 118; break;
		case "Ropes": IconIndex = 119; break;
		case "Wheat": IconIndex = 120; break;
		case "Rum": IconIndex = 121; break;
		case "Sailcloth": IconIndex = 122; break;
		case "Sugar": IconIndex = 123; break;
		case "Tobacco": IconIndex = 124; break;
		case "Leather": IconIndex = 125; break;
		case "Copra": IconIndex = 126; break;
		case "Clothes": IconIndex = 127; break;
		case "Paprika": IconIndex = 128; break;
		case "Balls": IconIndex = 129; break;
		case "Grapes": IconIndex = 130; break;
		case "Bombs": IconIndex = 131; break;
		case "Knippels": IconIndex = 132; break;
		case "Cinnamon": IconIndex = 133; break;
		case "Mahogany": IconIndex = 134; break;
		case "Ebony": IconIndex = 135; break;
		case "Coffee": IconIndex = 136; break;
		case "Sandal": IconIndex = 137; break;
		case "Slaves": IconIndex = 138; break;
		case "Planks": IconIndex = 139; break;
		case "Food": IconIndex = 140; break;
		case "Weapon": IconIndex = 141; break;
		case "Gold": IconIndex = 142; break;
		case "Silver": IconIndex = 143; break;
		case "Powder": IconIndex = 144; break;
		case "Brick": IconIndex = 145; break;
		case "Medicament": IconIndex = 146; break;
		case "Cannon_3": IconIndex = 147; break;
		case "Cannon_6": IconIndex = 148; break;
		case "Cannon_8": IconIndex = 149; break;
		case "Cannon_12": IconIndex = 150; break;
		case "Cannon_16": IconIndex = 151; break;
		case "Cannon_18": IconIndex = 152; break;
		case "Cannon_20": IconIndex = 153; break;
		case "Cannon_24": IconIndex = 154; break;
		case "Cannon_32": IconIndex = 155; break;
		case "Cannon_36": IconIndex = 156; break;
		case "Cannon_42": IconIndex = 157; break;
		case "Culverine_8": IconIndex = 158; break;
		case "Culverine_18": IconIndex = 159; break;
		case "Culverine_36": IconIndex = 175; break;
		case "Tichingitu": IconIndex = 165; break;
		case "Helena": IconIndex = 166; break;
		case "Mary": IconIndex = 167; break;
		case "Longway": IconIndex = 168; break;
		case "Tonzag": IconIndex = 169; break;
		case "Knippel": IconIndex = 170; break;
		case "Folke": IconIndex = 171; break;
		case "Duran": IconIndex = 172; break;
		case "Irons": IconIndex = 174; break;
		case "Threat1": IconIndex = 177; break;
		case "Threat2": IconIndex = 178; break;
		case "Threat3": IconIndex = 179; break;
		case "Threat4": IconIndex = 180; break;
		case "Threat5": IconIndex = 181; break;
		case "Threat0": IconIndex = 182; break;
		case "Discovery": IconIndex = 187; break;
		case "Indians": IconIndex = 188; break;
		case "Smugglers": IconIndex = 189; break;
		case "FstTravel": IconIndex = 190; break;
		case "Rats": IconIndex = 191; break;
		case "Personal abilities": IconIndex = 4; break;
		case "Ship abilities": IconIndex = 41; break;
		case "enghunter": IconIndex = 42; break;
		case "holhunter": IconIndex = 43; break;
		case "spahunter": IconIndex = 44; break;
		case "frahunter": IconIndex = 45; break;
		case "pirhunter": IconIndex = 46; break;
		case "Key": IconIndex = 186; break;
		case "Hat9": IconIndex = 185; break;
		case "None": IconIndex = 239; break;
	}
	if(notificationsQty < 8)
	{
		notificationsQty++;
		Notifications[notificationsQty].str = strLog;
		Notifications[notificationsQty].index = IconIndex;
		Notifications[notificationsQty].lt = fLifeTime;
		if(notificationsQty < 1) SetEventHandler("frame","PushNotification",0);
	}
}

void PushNotification()
{
	for(int i = 0; i < 3; i++)
	{
		if(CheckAttribute(&Notifications[i],"lt"))
		{
			if(!CheckAttribute(&Notifications[i],"printing"))
			{
				Notifications[i].printing = true;
				Pic_Info( Notifications[i].str, makeint(Notifications[i].index));
				//log_info(" Not "+Notifications[i].str+ " " +stf(Notifications[i].lt));
			}
			Notifications[i].lt = stf(Notifications[i].lt) - MakeFloat(GetDeltaTime()) * 0.001;
			if(stf(Notifications[i].lt) < 0.1)
			{
				DeleteAttribute(&Notifications[i],"str");
				DeleteAttribute(&Notifications[i],"index");
				DeleteAttribute(&Notifications[i],"lt");
			}
		}
	}
	if(CheckAttribute(&Notifications[0],"lt")) return;
	if(CheckAttribute(&Notifications[1],"lt")) return;
	if(CheckAttribute(&Notifications[2],"lt")) return;
	
	for( i = 3; i < 6; i++)
	{
		if(CheckAttribute(&Notifications[i],"lt"))
		{
			
			if(!CheckAttribute(&Notifications[i],"printing"))
			{
				Notifications[i].printing = true;
				Pic_Info( Notifications[i].str, makeint(Notifications[i].index));
			}
			Notifications[i].lt = stf(Notifications[i].lt) - MakeFloat(GetDeltaTime()) * 0.001;
			if(stf(Notifications[i].lt) < 0.1)
			{
				DeleteAttribute(&Notifications[i],"str");
				DeleteAttribute(&Notifications[i],"index");
				DeleteAttribute(&Notifications[i],"lt");
			}
		}
	}
	if(CheckAttribute(&Notifications[3],"lt")) return;
	if(CheckAttribute(&Notifications[4],"lt")) return;
	if(CheckAttribute(&Notifications[5],"lt")) return;
	
	for( i = 6; i < 9; i++)
	{
		if(CheckAttribute(&Notifications[i],"lt"))
		{
			if(!CheckAttribute(&Notifications[i],"printing"))
			{
				Notifications[i].printing = true;
				Pic_Info( Notifications[i].str, makeint(Notifications[i].index));
			}
			Notifications[i].lt = stf(Notifications[i].lt) - MakeFloat(GetDeltaTime()) * 0.001;
			if(stf(Notifications[i].lt) < 0.1)
			{
				DeleteAttribute(&Notifications[i],"str");
				DeleteAttribute(&Notifications[i],"index");
				DeleteAttribute(&Notifications[i],"lt");
			}
		}
	}
	if(CheckAttribute(&Notifications[6],"lt")) return;
	if(CheckAttribute(&Notifications[7],"lt")) return;
	if(CheckAttribute(&Notifications[8],"lt")) return;
	
	for(i = 0; i < 9; i++)
	{
		if(CheckAttribute(&Notifications[i],"printing")) DeleteAttribute(&Notifications[i],"printing");
	}
	notificationsQty = -1;
	DelEventHandler("frame","PushNotification");
}

bool ShowExpNotifications()
{
	if(LAi_IsFightMode(pchar)) return false;
	if(CheckAttribute(pchar,"systeminfo.InGameNotifications")) return true;
	if(CheckAttribute(pchar,"chr_ai.type") &&  Pchar.chr_ai.type != "player")) return false;
	if(CheckAttribute(pchar,"Ship.POS.Mode"))
	{
		if(pchar.Ship.POS.Mode == SHIP_WAR) return false;
	}
	if(isEntity(&WorldMap)) return false;
	
	return true;
}

void Pic_Info(string strLog, int IconIndex)
{
	SendMessage(&ILogAndActions,"lsl", LOG_ADD_PIC, strLog, IconIndex);
}

void TimeScale_Info(string strLog)
{
	bool bShow = false;
	if(strLog != "") bShow = true;
	SendMessage(&ILogAndActions,"lsl", LOG_TIME_SPEED, strLog, bShow);
}

void LA_LevelUp(string strLog, string Rank)
{
	PlayStereoSound("interface\new_level.wav");
	SendMessage(&ILogAndActions,"lss", LOG_LEVEL_UP, strLog, Rank);
}

void Log_Chr(ref chr, string sText)
{
	if(ShowCharString())
	{
		SendMessage(chr, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, sText, 255.0, 255.0, 255.0);
	}
}

bool ShowCharString()
{
	//if (bBettaTestMode) return true;
	if(CheckAttribute(&InterfaceStates,"ShowCharString") && sti(InterfaceStates.ShowCharString) > 0) return true;
	
	return false;
}

void Log_SetEternalString(string strLog)
{
	SendMessage(&ILogAndActions,"lls",LOG_ADD_STRING, true, strLog);
}

void CreateLogEnvironment()
{
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	ILogAndActions.Log.width = sti(showWindow.right)/2;
	ILogAndActions.Log.height = sti(showWindow.bottom)-makeint(80 * fHtRatio);
	ILogAndActions.Log.right = sti(showWindow.right) - RecalculateHIcon(makeint(300 * fHtRatio));
	ILogAndActions.Log.up = sti(showWindow.top) + makeint(16 * fHtRatio);
	if(bBettaTestMode) {
		ILogAndActions.Log.font = "interface_log";
		ILogAndActions.Log.fontscale = 1.2 * (1.0 + (fHtRatio-1.0)*0.4);
	} else {
		ILogAndActions.Log.font = "interface_normal";
		ILogAndActions.Log.fontscale = 1.5 * (1.0 + (fHtRatio-1.0)*0.4);
	}
	ILogAndActions.Log.color = argb(0,255,255,255);
	ILogAndActions.Log.offsetString = makeint(24 * fHtRatio);
	ILogAndActions.Log.speed = 0.05;
	ILogAndActions.Log.color_speed = 0.02;
}

void CreatePicInfoEnvironment()
{
	/* belamour legendary edition боковые уведомления основные настройки:
	ILogAndActions.PicInfo - настройки текста в уведомлении
	ILogAndActions.PicInfoBack - настройки текстуры подложки
	ILogAndActions.PicInfoIcon - настройки текстуры иконки
	
	общие для всех настройки:
	ILogAndActions.PicInfo.color_speed - скорость блендинга (пропадания) подсказки. 
	ILogAndActions.PicInfo.maxcolor, ILogAndActions.PicInfo.mincolor - максимальное(минимальное значение для альфа каналов (влияет на скорость затухания) 
	ILogAndActions.PicInfo.right - можно менять на left и наоборот в зависимости от нужного равнения по краю */
	
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	ILogAndActions.PicInfo.width = sti(showWindow.right)/2;
	ILogAndActions.PicInfo.height = sti(showWindow.bottom)-makeint(350 * fHtRatio);
	ILogAndActions.PicInfo.right = sti(showWindow.right) - RecalculateHIcon(makeint(75 * fHtRatio));
	if(iCompassPos) 
	{
		if(!isEntity(&WorldMap))
		{
			ILogAndActions.PicInfo.up = sti(showWindow.top) + makeint(425 * fHtRatio);
		}
		else
		{
			ILogAndActions.PicInfo.up = sti(showWindow.bottom)/2 + makeint(75 * fHtRatio);
		}
	}
	else 
	{
		if(!isEntity(&WorldMap))
		{
			ILogAndActions.PicInfo.up = sti(showWindow.top) + makeint(165 * fHtRatio);
		}
		else
		{
			ILogAndActions.PicInfo.up = sti(showWindow.bottom)/2 + makeint(75 * fHtRatio);
		}
	}
	ILogAndActions.PicInfo.font = "interface_normal";
	ILogAndActions.PicInfo.fontscale = 1.4 * fHtRatio;
	ILogAndActions.PicInfo.color = argb(255,255,255,255);
	ILogAndActions.PicInfo.offsetString = makeint(50 * fHtRatio);
	ILogAndActions.PicInfo.color_speed = NOTIFICATIONS_SPEED;
	ILogAndActions.PicInfo.maxcolor = argb(255,128,128,128);
	ILogAndActions.PicInfo.mincolor = argb(0,128,128,128); // не менять!!! 
	
	ILogAndActions.PicInfoBack.TextureName = "interfaces\le\battle_interface\info_fader_r.tga.tx";
	ILogAndActions.PicInfoBack.width = RecalculateHIcon(makeint(350 * fHtRatio));
	ILogAndActions.PicInfoBack.height = RecalculateHIcon(makeint(40 * fHtRatio));
	ILogAndActions.PicInfoBack.right = sti(showWindow.right) + RecalculateHIcon(makeint(5 * fHtRatio));
	if(iCompassPos)
	{
		if(!isEntity(&WorldMap))
		{
			ILogAndActions.PicInfoBack.top = sti(showWindow.top) + makeint(420 * fHtRatio);
		}
		else
		{
			ILogAndActions.PicInfoBack.top = sti(showWindow.bottom)/2 + makeint(70 * fHtRatio);
		}
	}
	else 
	{
		if(!isEntity(&WorldMap))
		{
			ILogAndActions.PicInfoBack.top = sti(showWindow.top) + makeint(160 * fHtRatio);
		}
		else
		{
			ILogAndActions.PicInfoBack.top = sti(showWindow.bottom)/2 + makeint(70 * fHtRatio);
		}
	}
	
	ILogAndActions.PicInfoIcon.TextureName = "interfaces\le\battle_interface\MessageIcons.tga.tx";
	ILogAndActions.PicInfoIcon.horzQ = 16;
	ILogAndActions.PicInfoIcon.vertQ = 16;
	ILogAndActions.PicInfoIcon.width = RecalculateHIcon(makeint(50 * fHtRatio));
	ILogAndActions.PicInfoIcon.height = RecalculateHIcon(makeint(50 * fHtRatio));
	ILogAndActions.PicInfoIcon.left = sti(showWindow.right) - RecalculateHIcon(makeint(60 * fHtRatio));
	if(iCompassPos)
	{
		if(!isEntity(&WorldMap))
		{
			ILogAndActions.PicInfoIcon.top = sti(showWindow.top) + makeint(415 * fHtRatio);
		}
		else
		{
			ILogAndActions.PicInfoIcon.top = sti(showWindow.bottom)/2 + makeint(65 * fHtRatio);
		}
	}
	else 
	{
		if(!isEntity(&WorldMap))
		{
			ILogAndActions.PicInfoIcon.top = sti(showWindow.top) + makeint(155 * fHtRatio);
		}
		else
		{
			ILogAndActions.PicInfoIcon.top = sti(showWindow.bottom)/2 + makeint(65 * fHtRatio);
		}
	}
}

void CreateTimeSpeedEnvironment()
{
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	
	ILogAndActions.timespeedtext.left = sti(showWindow.right) - RecalculateHIcon(makeint(100 * fHtRatio));
	ILogAndActions.timespeedtext.up = sti(showWindow.bottom)/2 - RecalculateVIcon(makeint(0 * fHtRatio));
	ILogAndActions.timespeedtext.font = "interface_normal";
	ILogAndActions.timespeedtext.fontscale = 1.75 * fHtRatio;
	ILogAndActions.timespeedtext.color = argb(255,255,255,255);
	
	ILogAndActions.timespeedicon.TextureName = "interfaces\le\battle_interface\timescale.tga.tx";
	ILogAndActions.timespeedicon.width = RecalculateHIcon(makeint(60 * fHtRatio));
	ILogAndActions.timespeedicon.height = RecalculateHIcon(makeint(60 * fHtRatio));
	ILogAndActions.timespeedicon.left = sti(showWindow.right) - RecalculateHIcon(makeint(100 * fHtRatio));
	ILogAndActions.timespeedicon.top = sti(showWindow.bottom)/2 - RecalculateVIcon(makeint(0 * fHtRatio));		
	ILogAndActions.timespeedicon.color = argb(255,128,128,128);
}

void CreateLevelUpEnvironment()
{
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	ILogAndActions.levelupstring.width = sti(showWindow.right)/2;
	ILogAndActions.levelupstring.height = sti(showWindow.bottom)/2;
	ILogAndActions.levelupstring.left = sti(showWindow.right)/2;
	ILogAndActions.levelupstring.up = sti(showWindow.bottom)/2 - makeint(50 * fHtRatio);
	ILogAndActions.levelupstring.font = "interface_normal_bold";
	ILogAndActions.levelupstring.fontscale = 1.4 * fHtRatio;
	ILogAndActions.levelupstring.color = argb(0,255,255,255); // альфу не менять
	ILogAndActions.levelupstring.color_speed = 0.05;
	
	ILogAndActions.leveluprank.width = sti(showWindow.right)/2;
	ILogAndActions.leveluprank.height = sti(showWindow.bottom)/2;
	ILogAndActions.leveluprank.left = sti(showWindow.right)/2;
	ILogAndActions.leveluprank.up = sti(showWindow.bottom)/2 + makeint(0 * fHtRatio);
	ILogAndActions.leveluprank.font = "bold_numbers";
	ILogAndActions.leveluprank.fontscale = 1.7 * fHtRatio;
	ILogAndActions.leveluprank.color = argb(0,255,255,255);
	//ILogAndActions.leveluprank.color_speed = 0.02;
	
	ILogAndActions.levelupback.TextureName = "interfaces\le\battle_interface\info_fader_c.tga.tx";
	ILogAndActions.levelupback.width = RecalculateHIcon(makeint(450 * fHtRatio));
	ILogAndActions.levelupback.height = RecalculateVIcon(makeint(100 * fHtRatio));
	ILogAndActions.levelupback.left = sti(showWindow.right)/2 - RecalculateHIcon(makeint(225 * fHtRatio));
	ILogAndActions.levelupback.top = sti(showWindow.bottom)/2 - RecalculateVIcon(makeint(50 * fHtRatio)); 
	ILogAndActions.levelupback.color = argb(0,128,128,128); // альфу не менять
}
void CreateSeaActionsEnvironment()
{
	float fHtRatio = stf(Render.screen_y) / iHudScale;

	ILogAndActions.type = "sea";
	ILogAndActions.ActiveActions.TextureName = "interfaces\le\battle_interface\list_icons.tga";
	ILogAndActions.ActiveActions.horzQ = 16;
	ILogAndActions.ActiveActions.vertQ = 8;
	ILogAndActions.ActiveActions.width = RecalculateHIcon(makeint(60 * fHtRatio));
	ILogAndActions.ActiveActions.height = RecalculateHIcon(makeint(60 * fHtRatio));
	ILogAndActions.ActiveActions.left = sti(showWindow.right) - RecalculateHIcon(makeint(100 * fHtRatio));
	ILogAndActions.ActiveActions.top = sti(showWindow.bottom)/2 - RecalculateVIcon(makeint(62 * fHtRatio));

	ILogAndActions.ActiveActions.text1.font = "keyboard_symbol";
	ILogAndActions.ActiveActions.text1.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text1.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));
	// ILogAndActions.ActiveActions.text1.text = XI_ConvertString("Press_F3");
	ILogAndActions.ActiveActions.text2.font = "interface_normal_bold";
	ILogAndActions.ActiveActions.text2.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text2.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));
	ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");
	
	fTmp = sti(showWindow.right)/2;
	fTmp2 = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));

	ILogAndActions.ActiveActions.Moor.IconNum		= 13;
	ILogAndActions.ActiveActions.Moor.Text			= XI_ConvertString("for_quick_action_Moor");//Причалить
	ILogAndActions.ActiveActions.Moor.pos.x			= fTmp;
	ILogAndActions.ActiveActions.Moor.pos.y			= fTmp2;
	ILogAndActions.ActiveActions.Board.IconNum		= 14;
	ILogAndActions.ActiveActions.Board.Text			= XI_ConvertString("for_quick_action_Board");//Взять на абордаж
	ILogAndActions.ActiveActions.Board.pos.x		= fTmp;
	ILogAndActions.ActiveActions.Board.pos.y		= fTmp2;
	ILogAndActions.ActiveActions.LandTroops.IconNum	= 45;
	ILogAndActions.ActiveActions.LandTroops.Text	= XI_ConvertString("for_quick_action_LandTroops");//Высадка союзного десанта
	ILogAndActions.ActiveActions.LandTroops.pos.x	= fTmp;
	ILogAndActions.ActiveActions.LandTroops.pos.y	= fTmp2;
	ILogAndActions.ActiveActions.Map.IconNum		= 12;
	ILogAndActions.ActiveActions.Map.Text			= XI_ConvertString("for_quick_action_Map");//На глобальную карту
	ILogAndActions.ActiveActions.Map.pos.x			= fTmp;
	ILogAndActions.ActiveActions.Map.pos.y			= fTmp2;
	ILogAndActions.ActiveActions.Reload.IconNum		= 32;
	ILogAndActions.ActiveActions.Reload.Text		= XI_ConvertString("for_quick_action_Reload_Sea");//Обмен с кораблем
	ILogAndActions.ActiveActions.Reload.pos.x		= fTmp;
	ILogAndActions.ActiveActions.Reload.pos.y		= fTmp2;
	ILogAndActions.ActiveActions.Deck.IconNum		= 34;
	ILogAndActions.ActiveActions.Deck.Text			= XI_ConvertString("for_quick_action_Deck");//Палуба
	ILogAndActions.ActiveActions.Deck.pos.x			= fTmp;
	ILogAndActions.ActiveActions.Deck.pos.y			= fTmp2;
	ILogAndActions.ActiveActions.Nothing.IconNum	= -1;
	ILogAndActions.ActiveActions.Nothing.Text		= XI_ConvertString("for_quick_action");

	ILogAndActions.ActiveActionsBack.TextureName = "interfaces\le\battle_interface\info_fader_b.tga.tx";
	ILogAndActions.ActiveActionsBack.width = RecalculateHIcon(makeint(100 * fHtRatio)); // ширина текcтуры также зависит от длины текста
	ILogAndActions.ActiveActionsBack.height = RecalculateVIcon(makeint(50 * fHtRatio));
	ILogAndActions.ActiveActionsBack.centr = sti(showWindow.right)/2; // центр текстуры по Х
	ILogAndActions.ActiveActionsBack.top = sti(showWindow.bottom) - RecalculateVIcon(makeint(205 * fHtRatio))
	ILogAndActions.ActiveActionsBack.color = argb(255,128,128,128);
}

void CreateLandActionsEnvironment()
{
    float fHtRatio = stf(Render.screen_y) / iHudScale;
	ILogAndActions.type = "land";
	ILogAndActions.ActiveActions.TextureName = "interfaces\le\battle_interface\LandCommands.tga";
	ILogAndActions.ActiveActions.horzQ = 16;
	ILogAndActions.ActiveActions.vertQ = 4;
	ILogAndActions.ActiveActions.width = RecalculateHIcon(makeint(60 * fHtRatio));
	ILogAndActions.ActiveActions.height = RecalculateHIcon(makeint(60 * fHtRatio));
	ILogAndActions.ActiveActions.left = sti(showWindow.right) - RecalculateHIcon(makeint(100 * fHtRatio));
	ILogAndActions.ActiveActions.top = sti(showWindow.bottom)/2 - RecalculateVIcon(makeint(62 * fHtRatio));

	ILogAndActions.ActiveActions.text1.font = "keyboard_symbol";
	ILogAndActions.ActiveActions.text1.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text1.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));
	// ILogAndActions.ActiveActions.text1.text = XI_ConvertString("Press_F3");
	ILogAndActions.ActiveActions.text2.font = "interface_normal_bold";
	ILogAndActions.ActiveActions.text2.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text2.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));
	ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");

	fTmp = sti(showWindow.right)/2;
	fTmp2 = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));

	ILogAndActions.ActiveActions.ToSea.IconNum			= 14;
	ILogAndActions.ActiveActions.ToSea.Text				= XI_ConvertString("for_quick_action_ToSea");
	ILogAndActions.ActiveActions.ToSea.pos.x			= fTmp;
	ILogAndActions.ActiveActions.ToSea.pos.y			= fTmp2;

	ILogAndActions.ActiveActions.Talk.IconNum			= 1;
	ILogAndActions.ActiveActions.Talk.Text				= XI_ConvertString("for_quick_action_Talk");
	ILogAndActions.ActiveActions.Talk.pos.x				= fTmp;
	ILogAndActions.ActiveActions.Talk.pos.y				= fTmp2;

	ILogAndActions.ActiveActions.Look.IconNum			= 0;
	ILogAndActions.ActiveActions.Look.Text				= XI_ConvertString("for_quick_action_Look");
	ILogAndActions.ActiveActions.Look.pos.x				= fTmp;
	ILogAndActions.ActiveActions.Look.pos.y				= fTmp2;
	
	ILogAndActions.ActiveActions.Pick.IconNum			= 0;
	ILogAndActions.ActiveActions.Pick.Text				= XI_ConvertString("for_quick_action_Pick");
	ILogAndActions.ActiveActions.Pick.pos.x				= fTmp;
	ILogAndActions.ActiveActions.Pick.pos.y				= fTmp2;
	
	ILogAndActions.ActiveActions.Action.IconNum			= 0;
	ILogAndActions.ActiveActions.Action.Text			= XI_ConvertString("for_quick_action_Action");
	ILogAndActions.ActiveActions.Action.pos.x			= fTmp;
	ILogAndActions.ActiveActions.Action.pos.y			= fTmp2;

	ILogAndActions.ActiveActions.OpenBox.IconNum		= 35;
	ILogAndActions.ActiveActions.OpenBox.Text			= XI_ConvertString("for_quick_action_OpenBox");
	ILogAndActions.ActiveActions.OpenBox.pos.x			= fTmp;
	ILogAndActions.ActiveActions.OpenBox.pos.y			= fTmp2;

	ILogAndActions.ActiveActions.DeadBox.IconNum		= 35;
	ILogAndActions.ActiveActions.DeadBox.Text			= XI_ConvertString("for_quick_action_DeadBox");
	ILogAndActions.ActiveActions.DeadBox.pos.x			= fTmp;
	ILogAndActions.ActiveActions.DeadBox.pos.y			= fTmp2;

	ILogAndActions.ActiveActions.Reload.IconNum			= 13;
	ILogAndActions.ActiveActions.Reload.Text			= XI_ConvertString("for_quick_action_Reload");
	ILogAndActions.ActiveActions.Reload.pos.x			= fTmp;
	ILogAndActions.ActiveActions.Reload.pos.y			= fTmp2;

	ILogAndActions.ActiveActions.BoardingReload.IconNum	= 13;
	ILogAndActions.ActiveActions.BoardingReload.Text	= XI_ConvertString("for_quick_action_BoardingReload");
	ILogAndActions.ActiveActions.BoardingReload.pos.x	= fTmp;
	ILogAndActions.ActiveActions.BoardingReload.pos.y	= fTmp2;

	ILogAndActions.ActiveActions.BoardingEnd.IconNum	= 13;
	ILogAndActions.ActiveActions.BoardingEnd.Text		= XI_ConvertString("for_quick_action_BoardingEnd");
	ILogAndActions.ActiveActions.BoardingEnd.pos.x		= fTmp;
	ILogAndActions.ActiveActions.BoardingEnd.pos.y		= fTmp2;

	ILogAndActions.ActiveActions.PlayEvent.IconNum		= 0;
	ILogAndActions.ActiveActions.PlayEvent.Text			= XI_ConvertString("for_quick_action_Use");
	ILogAndActions.ActiveActions.PlayEvent.pos.x		= fTmp;
	ILogAndActions.ActiveActions.PlayEvent.pos.y		= fTmp2;

	ILogAndActions.ActiveActions.Closed.IconNum			= 29;
	ILogAndActions.ActiveActions.Closed.Text			= XI_ConvertString("for_quick_action_Closed");
	ILogAndActions.ActiveActions.Closed.pos.x			= fTmp;
	ILogAndActions.ActiveActions.Closed.pos.y			= fTmp2;
	
	ILogAndActions.ActiveActions.Nothing.IconNum		= -1;
	ILogAndActions.ActiveActions.Nothing.Text			= XI_ConvertString("for_quick_action");
	
	ILogAndActions.ActiveActionsBack.TextureName = "interfaces\le\battle_interface\info_fader_b.tga.tx";
	ILogAndActions.ActiveActionsBack.width = RecalculateHIcon(makeint(100 * fHtRatio)); // ширина текcтуры также зависит от длины текста
	ILogAndActions.ActiveActionsBack.height = RecalculateVIcon(makeint(50 * fHtRatio));
	ILogAndActions.ActiveActionsBack.centr = sti(showWindow.right)/2; // центр текстуры по Х
	ILogAndActions.ActiveActionsBack.top = sti(showWindow.bottom) - RecalculateVIcon(makeint(205 * fHtRatio))
	ILogAndActions.ActiveActionsBack.color = argb(255,128,128,128);
}

void CreateWorldMapActionsEnvironment()
{
    float fHtRatio = stf(Render.screen_y) / iHudScale;
	ILogAndActions.type = "map";
	ILogAndActions.ActiveActions.TextureName = "interfaces\le\battle_interface\WorldMapCommands.tga";
	ILogAndActions.ActiveActions.horzQ = 8;
	ILogAndActions.ActiveActions.vertQ = 2;
	ILogAndActions.ActiveActions.width = RecalculateHIcon(makeint(60 * fHtRatio));
	ILogAndActions.ActiveActions.height = RecalculateVIcon(makeint(60 * fHtRatio));
	ILogAndActions.ActiveActions.left = sti(showWindow.right) - RecalculateHIcon(makeint(280 * fHtRatio));
	ILogAndActions.ActiveActions.top = sti(showWindow.top) + RecalculateVIcon(makeint(20 * fHtRatio));

	ILogAndActions.ActiveActions.text1.font = "keyboard_symbol";
	ILogAndActions.ActiveActions.text1.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text1.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));
	// ILogAndActions.ActiveActions.text1.text = XI_ConvertString("Press_F3");
	ILogAndActions.ActiveActions.text2.font = "interface_normal_bold";
	ILogAndActions.ActiveActions.text2.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text2.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));
	ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");

	fTmp = sti(showWindow.right)/2;
	fTmp2 = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));

	ILogAndActions.ActiveActions.EnterToIsland.IconNum		= 8;
	ILogAndActions.ActiveActions.EnterToIsland.Text			= XI_ConvertString("for_quick_action_EnterToIsland");
	ILogAndActions.ActiveActions.EnterToSea.IconNum			= 9;
	ILogAndActions.ActiveActions.EnterToSea.Text			= XI_ConvertString("for_quick_action_EnterToSea");//Выйти в море
	ILogAndActions.ActiveActions.EnterToSea.pos.x			= fTmp;
	ILogAndActions.ActiveActions.EnterToSea.pos.y			= fTmp2;
	ILogAndActions.ActiveActions.EnterToAttack.IconNum		= 10;
	ILogAndActions.ActiveActions.EnterToAttack.Text			= XI_ConvertString("for_quick_action_EnterToAttack");//Присоединиться к бою
	ILogAndActions.ActiveActions.EnterToAttack.pos.x		= fTmp;
	ILogAndActions.ActiveActions.EnterToAttack.pos.y		= fTmp2;
	ILogAndActions.ActiveActions.EnterToEnemy.IconNum		= 11;
	ILogAndActions.ActiveActions.EnterToEnemy.Text			= XI_ConvertString("for_quick_action_EnterToEnemy");//Защищаться
	ILogAndActions.ActiveActions.EnterToEnemy.pos.x			= fTmp;
	ILogAndActions.ActiveActions.EnterToEnemy.pos.y			= fTmp2;
	ILogAndActions.ActiveActions.EnterToShip.IconNum		= 12;
	ILogAndActions.ActiveActions.EnterToShip.Text			= XI_ConvertString("for_quick_action_EnterToShip");//Атаковать
	ILogAndActions.ActiveActions.EnterToShip.pos.x			= fTmp;
	ILogAndActions.ActiveActions.EnterToShip.pos.y			= fTmp2;
	ILogAndActions.ActiveActions.GetOnBoard.IconNum			= 12;
	ILogAndActions.ActiveActions.GetOnBoard.Text			= XI_ConvertString("for_quick_action_GetOnBoard");//Взять на борт
	ILogAndActions.ActiveActions.GetOnBoard.pos.x			= fTmp;
	ILogAndActions.ActiveActions.GetOnBoard.pos.y			= fTmp2;	
	ILogAndActions.ActiveActions.EnterToStorm.IconNum		= 13;
	ILogAndActions.ActiveActions.EnterToStorm.Text			= XI_ConvertString("for_quick_action_EnterToStorm");//Шторм
	ILogAndActions.ActiveActions.EnterToStorm.pos.x			= fTmp;
	ILogAndActions.ActiveActions.EnterToStorm.pos.y			= fTmp2;

	ILogAndActions.ActiveActionsBack.TextureName = "interfaces\le\battle_interface\info_fader_b.tga.tx";
	ILogAndActions.ActiveActionsBack.width = RecalculateHIcon(makeint(100 * fHtRatio)); // ширина текcтуры также зависит от длины текста
	ILogAndActions.ActiveActionsBack.height = RecalculateVIcon(makeint(50 * fHtRatio));
	ILogAndActions.ActiveActionsBack.centr = sti(showWindow.right)/2; // центр текстуры по Х
	ILogAndActions.ActiveActionsBack.top = sti(showWindow.bottom) - RecalculateVIcon(makeint(205 * fHtRatio))
}

void DrawCharacterHP(float myHP,float enemyHP)
{
	if(bYesBoardStatus==false)
	{
		CreateEntity(&IBoardingStatus,"IBoardingStatus");
		IBoardingStatus.myLeft = sti(showWindow.left)+16;
		IBoardingStatus.myTop = sti(showWindow.bottom)-140;
		IBoardingStatus.enemyLeft = sti(showWindow.left)+16;
		IBoardingStatus.enemyTop = sti(showWindow.bottom)-128;
		IBoardingStatus.height = RecalculateVIcon(8);
		IBoardingStatus.width = RecalculateHIcon(120);
		IBoardingStatus.myColor = argb(255,0,0,128);
		IBoardingStatus.enemyColor = argb(255,128,0,0);
		SendMessage(&IBoardingStatus,"l",LOG_INIT_CHARCTER_HP);
		bYesBoardStatus = true;
	}
	if(myHP==0)
	{
		bYesBoardStatus=false;
		DeleteClass(&IBoardingStatus);
		DeleteAttribute(&IBoardingStatus,"");
	}
	if(enemyHP==0)
	{
		bYesBoardStatus=false;
		DeleteClass(&IBoardingStatus);
		DeleteAttribute(&IBoardingStatus,"");
	}
	SendMessage(&IBoardingStatus,"lff",LOG_SET_CHARCTER_HP,myHP,enemyHP);
}

void BI_FastCommand()
{
	int tmpi;
	string FComName = GetEventData();

	if( LAi_IsDead(pchar) ) {return;}

	aref arFader;
	if( GetEntity(arFader,"fader") ) {return;}

	bool bEC = false;

	if( ILogAndActions.type == "sea" )
	{
		switch(FComName)
		{
		case "Moor":		bEC = true; Sea_LandLoad(); break;
		case "Board":		bEC = true; Sea_AbordageLoad(SHIP_ABORDAGE,true); break;
		case "LandTroops":	bEC = true; Sea_AbordageLoad(FORT_ABORDAGE,true); break;
		case "Map":			bEC = true; Sea_MapLoad(); break; //  pchar.location = ""; тут нах не нужно
		case "Deck":
				bEC = true;
				if(CheckAttribute(pchar, "TutorialToDeck_1"))
					DoFunctionReloadToLocation("Quest_Ship_deck_Medium_trade", "quest", "quest6", "SharlieTutorial_StartKino");
				if(CheckAttribute(pchar, "TutorialToDeck_2"))
					DoFunctionReloadToLocation("Quest_Deck", "rld", "loc0", "SharlieTutorial_ActThree");
				if(CheckAttribute(pchar, "TutorialToPort"))
					SharlieTutorial_StartGameInMartinique();
		break;			
		case "Reload":
			if(bi_nReloadTarget!=-1)
			{
				bEC = true;
				LaunchTransferMain(pchar,GetCharacter(bi_nReloadTarget),"Transfer");
			}
		break;
		}
	}
	if( ILogAndActions.type == "land" )
	{
		if(CheckAttribute(pchar,"Quests.quest_act"))
		{
			Event("evntQuestComplete","s",Characters[nMainCharacterIndex].Quests.quest_act);
			return;
		}
		switch(FComName)
		{
			case "OpenBox":
				if(iControlsMode == 0)
				{
					if (!LAi_IsFightMode(pchar)) // в бою быстрой командой низя открыть сундук
					{
						bEC = true; 
						OpenBoxProcedure();	
					}
				}
				else // с альтернативной раскладкой можем обыскивать
				{
					bEC = true; 
					OpenBoxProcedure();	
				}
			break;
				
			case "Pick": bEC = true; Item_OnPickItem(); break;
			case "Action": bEC = true; Item_OnUseItem(); break;
			case "Talk":
				bEC = true;
				tmpi = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");
				if(tmpi>=0)	{Event("dlgReady","l",tmpi);}
			break;
			case "Reload":
				bEC = true;
				if (bCabinStarted)   // boal
	            {
	                // раставление НПС при переходах - миниквесты
	                BOAL_ReloadToLoc(chrWaitReloadRef, chrWaitReloadLocator);
	            }
	            else
					Event("Control Activation","s","ChrAction");
			break;
			case "ToSea": bEC = true; Event("Control Activation","s","ChrAction"); break;
			case "BoardingReload":  break;
			case "BoardingEnd":  break;
			case "PlayEvent":
				bEC = true; 
				PlayLocatorEvent();
			break;
		}
	}
	if( ILogAndActions.type == "map" )
	{
		switch(FComName)
		{
		case "EnterToSea":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToIsland":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToShip":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToStorm":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToAttack":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToEnemy":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "GetOnBoard":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		}
	}

	if( bEC )
	{
		g_ActiveActionName = "";
		SendMessage(&ILogAndActions,"ls",LOG_SET_ACTIVE_ACTION,"");
	}
}

void ClearAllLogStrings()
{
	SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
}

void BI_GetMsgIconRoot()
{
	aref arTmp;
	aref pARef[4];
	int i,idx,cn;
	idx = 0;

	if(bSeaActive && !bAbordageStarted)
	{
		for(i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar,i);
			if(cn<0) {continue;}
			Characters[cn].MessageIcons = true;
			makearef(arTmp,Characters[cn].MessageIcons);
			pARef[idx] = arTmp;
			idx++;
		}
		SendMessage(&BattleInterface,"le", BI_MSG_SET_MSG_ICONS, &pARef);
	}
	else
	{
		for(i=0; i<4; i++)
		{
			cn = GetOfficersIndex(pchar,i);
			if(cn<0) {continue;}
			Characters[cn].MessageIcons = true;
			makearef(arTmp,Characters[cn].MessageIcons);
			pARef[idx] = arTmp;
			idx++;
		}
		SendMessage(&objLandInterface,"le", MSG_BATTLE_LAND_SET_MSGICONS, &pARef);
	}
}

void LoadLIStates()
{
	pchar = GetMainCharacter();//нужно, чтобы не ругалось
	if(!CheckAttribute(pchar, "id")) return;
	int i,cn;
	ref chref;

	DeleteAttribute(pchar,"MessageIcons");
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetOfficersIndex(pchar,i);
		if(cn>=0)
		{
			chref = GetCharacter(cn);
			DeleteAttribute(chref,"MessageIcons");
		}
		cn = GetCompanionIndex(pchar,i);
		if(cn>=0)
		{
			chref = GetCharacter(cn);
			DeleteAttribute(chref,"MessageIcons");
		}
	}
}

string FindControlFromActionName(string _actionName)
{
	string control = "BIFastCommand";
	
	switch(_actionName)
	{
		case "DeadBox": control = "BOAL_DeadSearch"; break;
		case "BoardingReload": control = "ChrAction"; break;
		case "BoardingEnd": control = "ChrAction"; break;
		case "Talk":
			if(iControlsMode == 0) control = "ChrAction";
		break;
		case "Reload": 
			if(iControlsMode == 0) 
			{
				if(ILogAndActions.type == "sea") control = "IAction";
				else control = "ChrAction";
			}
		break;
		case "ToSea": 
			if(iControlsMode == 0) control = "ChrAction";
		break;
	}
	
	return control;
}

#event_handler("Event_ErrorLog","Event_ErrorLog");
void Event_ErrorLog()
{
	string string1 = GetEventData();
	string string2 = GetEventData();
	log_info(string1 + string2);
}