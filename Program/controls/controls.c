
#event_handler("frame","procUpdateControlKeyGroup");

// Control flags
#define USE_AXIS_AS_BUTTON				1
#define USE_AXIS_AS_INVERSEBUTTON		2
#define INVERSE_CONTROL					4

// Control groups (в соответствии с GetCurControlGroup)
#define INVALID_BIND_GROUP    -1
#define BIND_ALL_GROUPS       -2
#define BIND_VIDEO_PLAYER     0
#define BIND_MAIN_INTERFACE   1
#define BIND_DIALOG           2
#define BIND_BATTLE_INTERFACE 3
#define BIND_WORLD_MAP        4
#define BIND_SAILING_1PERS    5
#define BIND_SAILING_3PERS    6
#define BIND_SAILING_FIRE     7
#define BIND_FIGHT_MODE       8
#define BIND_PRIMARY_LAND     9
#define BIND_NETWORK          10

string curKeyGroupName = "";
object objControlsState;
extern void ExternControlsInit(bool bFirst, int iControlKeys);

native int AddControlTreeNode(int nParent,string sBaseControl,string sOutControl,float fTimeOut);

void ControlsInit(string sPlatformName, bool bFirst, int iControlKeys)
{
	DeleteAttribute(&objControlsState,"");

	string initFileName = "controls\init_pc.c";
	if(IsSteamDeck()) initFileName = "controls\init_sd.c";

	if(LoadSegment(initFileName))
	{
		ExternControlsInit(bFirst, !iControlKeys);
		UnloadSegment(initFileName);
	}
	else
	{
		trace("Can`t init controls because not loaded segment "+initFileName);
		return;
	}
}

void RestoreKeysFromOptions(aref arControlsRoot)
{
	aref arRootKey, arKey;
	int nGroupQ,nKeyQ, i,j, state,ctrlCode,keyCode;
	string ctrlName,grName;

	nGroupQ = GetAttributesNum(arControlsRoot);
	for(i=0; i<nGroupQ; i++)
	{
		arRootKey = GetAttributeN(arControlsRoot,i);
		grName = GetAttributeName(arRootKey);
		nKeyQ = GetAttributesNum(arRootKey);
		for(j=0; j<nKeyQ; j++)
		{
			arKey = GetAttributeN(arRootKey,j);
			state = 0;
			if(CheckAttribute(arKey,"state"))
			{
				state = sti(arKey.state);
			}

			ctrlName = GetAttributeName(arKey);
			keyCode = CI_GetKeyCode(GetAttributeValue(arKey));
			CI_CreateAndSetControls(grName, ctrlName, keyCode, state, arKey.remapping);
		}
	}

    // --> ВРЕМЕННЫЙ КОСТЫЛЬ НА ВОЗМОЖНЫЕ НЕСОВПАДЕНИЯ (TO_DO: REF)
    makearef(arRootKey, objControlsState.keygroups.AltPressedGroup);
    nKeyQ = GetAttributesNum(arRootKey);
    for(j = nKeyQ-1; j >= 0; j--)
    {
        arKey = GetAttributeN(arRootKey,j);
        ctrlName = GetAttributeName(arKey);
        if(!CheckAttribute(arControlsRoot, "AltPressedGroup." + ctrlName))
            DeleteAttribute(&objControlsState, "keygroups.AltPressedGroup." + ctrlName);
    }
    makearef(arRootKey, objControlsState.keygroups.BattleInterfaceControls);
    if(!CheckAttribute(&arControlsRoot, "BattleInterfaceControls.ChrForward"))
    {
        DeleteAttribute(arRootKey, "ChrForward");
        DeleteAttribute(arRootKey, "ChrBackward");
        DeleteAttribute(arRootKey, "ChrStrafeLeft");
        DeleteAttribute(arRootKey, "ChrStrafeRight");
    }
    if(!CheckAttribute(&arControlsRoot, "BattleInterfaceControls.Ship_SailUp"))
    {
        DeleteAttribute(arRootKey, "Ship_SailUp");
        DeleteAttribute(arRootKey, "Ship_SailDown");
        DeleteAttribute(arRootKey, "Ship_TurnLeft");
        DeleteAttribute(arRootKey, "Ship_TurnRight");
    }
    // <-- ВРЕМЕННЫЙ КОСТЫЛЬ НА ВОЗМОЖНЫЕ НЕСОВПАДЕНИЯ (TO_DO: REF)

	RunControlsContainers();
}

void CI_CreateContainer(string groupName, string containerName, float containerVal)
{
	objControlsContainer.(containerName) = containerVal;
	CI_CreateAndSetControls(groupName, containerName, -1, 0, false);
	DoControlInvisible(groupName, containerName);
}

void AddToContainer(string groupName, string containerName, string controlName, int KeyCode, int controlState, bool inverse )
{
	float fVal = objControlsContainer.(containerName);
	string keyName = CI_GetKeyName(KeyCode);
	if( CheckAttribute(&objControlsState,"key_codes."+keyName+".stick") &&
		sti(objControlsState.key_codes.(keyName).stick) == true)
	{
		fVal /= 15.0;
	}
	if(inverse) fVal = -fVal;
	objControlsContainer.(containerName).(controlName) = fVal;
	CI_CreateAndSetControls(groupName, controlName, KeyCode, controlState, false);
	DoControlInvisible(groupName, controlName);
}

void DoControlInvisible(string groupName, string controlName)
{
	if( CheckAttribute(&objControlsState,"keygroups."+groupName+"."+controlName) )
	{
		objControlsState.keygroups.(groupName).(controlName).invisible = true;
	}
}

// iSync: 0 меняются независимо, 1 меняются одновременно,
//        2, 3 меняются независимо, но в случае дубля нужна проверка (WASD)
void SameBindingAllowed(string controlName1, string controlName2, int iSync)
{
    objControlsState.map.controls.(controlName1).friends.(controlName2) = iSync;
    objControlsState.map.controls.(controlName2).friends.(controlName1) = iSync;
}

void ControlSyncLock(string controlName)
{
    objControlsState.map.controls.(controlName).SyncLock = "";
}

void CI_CreateAndSetControls(string groupName, string controlName, int keyCode, int controlState, bool bRemappingEnable)
{
    // MapControl под конкретные группы
    // SetControlFlags для всех использований

	if(controlName == "") return;

	if(!CheckAttribute(&objControlsState,"map.controls."+controlName))
	{
        objControlsState.map.controls.(controlName) = CreateControl(controlName);
	}

	int cntrlCode = sti(objControlsState.map.controls.(controlName));
    if(groupName != "AltPressedGroup")
        MapControl(cntrlCode, keyCode, GetGroupIDX(groupName));

	if(keyCode < 0 && controlState == 0)
	{
        controlState = USE_AXIS_AS_BUTTON;
	}

	if(controlState != -1)
	{	
        // Битмаска через двоичную сумму:
        // USE_AXIS_AS_BUTTON         001
        // USE_AXIS_AS_INVERSEBUTTON  010
        // INVERSE_CONTROL            100
        SetControlFlags(cntrlCode, controlState);
	}
	else
	{
        controlState = 0;
	}

	if(groupName != "")
	{
        objControlsState.keygroups.(groupName).(controlName) = CI_GetKeyName(keyCode);
        objControlsState.keygroups.(groupName).(controlName).state = controlState;
        objControlsState.keygroups.(groupName).(controlName).remapping = bRemappingEnable;
	}
}

// Параметры берутся из первой валидной группы
void MapControlToGroup(string controlName, string groupName)
{
	int i,nRootSize;
	aref arRoot,arGroup;

	makearef(arRoot,objControlsState.keygroups);
	nRootSize = GetAttributesNum(arRoot);

	for(i=0; i<nRootSize; i++)
	{
		arGroup = GetAttributeN(arRoot,i);
		if(CheckAttribute(arGroup,controlName))
		{
			objControlsState.keygroups.(groupName).(controlName) = arGroup.(controlName);
			objControlsState.keygroups.(groupName).(controlName).state = arGroup.(controlName).state;
			if(CheckAttribute(arGroup,controlName+".invisible"))
            {
				objControlsState.keygroups.(groupName).(controlName).invisible = arGroup.(controlName).invisible;
			}
			if(CheckAttribute(arGroup,controlName+".remapping"))
            {
				objControlsState.keygroups.(groupName).(controlName).remapping = arGroup.(controlName).remapping;
			}
            if(groupName != "AltPressedGroup")
            {
                int keyCode   = CI_GetKeyCode(arGroup.(controlName));
                int cntrlCode = sti(objControlsState.map.controls.(controlName));
                MapControl(cntrlCode, keyCode, GetGroupIDX(groupName));
			}
            return;
		}
	}
}

void AddControlToGroups(string controlName, string g1, string g2, string g3, string g4)
{
	if(g1 != "") MapControlToGroup(controlName, g1);
	if(g2 != "") MapControlToGroup(controlName, g2);
	if(g3 != "") MapControlToGroup(controlName, g3);
	if(g4 != "") MapControlToGroup(controlName, g4);
}

void AddControlToSettingsGroups(string controlName)
{
    string sName;
    aref arKGRoot, arKG;
    makearef(arKGRoot, objControlsState.keygroups);
    int nGQ = GetAttributesNum(arKGRoot);
    for(int i = 0; i < nGQ; i++)
    {
        arKG  = GetAttributeN(arKGRoot, i);
        sName = GetAttributeName(arKG);
        if(!IsSettingsGroup(sName)) continue;
        if(CheckAttribute(arKG, controlName)) continue;
        MapControlToGroup(controlName, sName);
    }
}

int CI_GetKeyCode(string keyName)
{
	if( CheckAttribute(&objControlsState,"key_codes."+keyName) )
	{	return sti(objControlsState.key_codes.(keyName));
	}

	trace("Can`t key named as: " + keyName);
	return -1;
}

string CI_GetKeyName(int code)
{
	aref arKeys,arCur;
	makearef(arKeys,objControlsState.key_codes);
	int nq = GetAttributesNum(arKeys);

	for(int i=0; i<nq; i++)
	{
		arCur = GetAttributeN(arKeys,i);
		if(sti(GetAttributeValue(arCur)) == code)
            return GetAttributeName(arCur);
	}

	return "";
}

int ControlNameToCode(string cname)
{
	if(CheckAttribute(&objControlsState,"map.controls."+cname))
	{
        return sti(objControlsState.map.controls.(cname));
	}
	return -1;
}

// Определение релевантного бинда контролки
// НЕ РАБОТАЕТ ДЛЯ КОНТРОЛОК БЕЗ КОНКРЕТНЫХ ГРУПП
string GetKeyByControl(string controlName)
{
    // Смотрим текущую группу
    if(CheckAttribute(&objControlsState, "keygroups." + curKeyGroupName + "." + controlName))
    {
        return objControlsState.keygroups.(curKeyGroupName).(controlName);
    }

    // Если нет, то в соответствии с принятым соглашением:
    // В приоритете бинд из первой валидной settings группы, потом остальные
    string sName, sKey = "";
    aref arKG, arKGRoot;
	makearef(arKGRoot, objControlsState.keygroups);
	int num = GetAttributesNum(arKGRoot);
    for(int i=0; i<num; i++)
    {
        arKG = GetAttributeN(arKGRoot, i);
        if(CheckAttribute(arKG, controlName))
        {
            sName = GetAttributeName(arKG);
            if(!IsSettingsGroup(sName))
            {
                if(sKey == "") sKey = arKG.(controlName);
            }
            else return arKG.(controlName);
        }
    }

    return sKey;
}

// belamour определить картинку кнопки
string GetKeyCodeImg(string _cval)
{
	string cname = GetKeyByControl(_cval);
    if(cname == "") return "";
	if(CheckAttribute(&objControlsState,"keygroups.AltPressedGroup."+_cval))
		return objControlsState.key_codes.vk_menu.img + objControlsState.key_codes.(cname).img;
	return objControlsState.key_codes.(cname).img;
}

void procUpdateControlKeyGroup()
{
	string newCurGroup = SetCurControlGroup();
	if(curKeyGroupName == newCurGroup) return;

	FreezeGroupControls(curKeyGroupName,true);
	FreezeGroupControls(newCurGroup,false);
	curKeyGroupName = newCurGroup;
}

string GetCurControlGroup()
{
	if(IsEntity(&aviVideoObj)) return "VideoPlayer";
	//if(bRunHelpChooser) return "HelpChooser";

	if(sti(InterfaceStates.Launched) == true) return "MainInterface";

	if(DialogRun) return "DialogControls";

	if(IsEntity(&worldMap))
	{
		if(CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0)
			return "BattleInterfaceControls";
		return "WorldMapControls";
	}

	if(bSeaActive && !bAbordageStarted)
	{
		if(CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0)
			return "BattleInterfaceControls";

		if(SeaCameras.Camera == "SeaDeckCamera" )
			return "Sailing1Pers";
		
		if(SeaCameras.Camera == "SeaFireCamera")
			return "SailingFire";
		
		return "Sailing3Pers";
	}

	if(CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0)
		return "BattleInterfaceControls";

	if(SendMessage(&Characters[nMainCharacterIndex],"ls",MSG_CHARACTER_EX_MSG,"CheckFightMode") != 0)
		return "FightModeControls";

	return "PrimaryLand";
}

string SetCurControlGroup()
{
    int iCurGroupIDX;
	if(IsEntity(&aviVideoObj)) iCurGroupIDX = BIND_VIDEO_PLAYER;
	else if(sti(InterfaceStates.Launched) == true) iCurGroupIDX = BIND_MAIN_INTERFACE;
	else if(DialogRun) iCurGroupIDX = BIND_DIALOG;
	else if(IsEntity(&worldMap))
	{
		if(CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0)
			iCurGroupIDX = BIND_BATTLE_INTERFACE;
		else
            iCurGroupIDX = BIND_WORLD_MAP;
	}
	else if(bSeaActive && !bAbordageStarted)
	{
		if(CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0)
			iCurGroupIDX = BIND_BATTLE_INTERFACE;
		else if(SeaCameras.Camera == "SeaDeckCamera")
            iCurGroupIDX = BIND_SAILING_1PERS;
		else if(SeaCameras.Camera == "SeaFireCamera")
			iCurGroupIDX = BIND_SAILING_FIRE;
		else
            iCurGroupIDX = BIND_SAILING_3PERS;
	}
	else if(CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0)
    {
		iCurGroupIDX = BIND_BATTLE_INTERFACE;
    }
    else if(SendMessage(&Characters[nMainCharacterIndex],"ls",MSG_CHARACTER_EX_MSG,"CheckFightMode") != 0)
    {
        iCurGroupIDX = BIND_FIGHT_MODE;
    }
    else iCurGroupIDX = BIND_PRIMARY_LAND;

    UpdateControlGroup(iCurGroupIDX);
    return GetGroupName(iCurGroupIDX);
}

void FreezeGroupControls(string grName, bool bFreeze)
{
	if(grName == "")
	{
		AllControlsFreeze(bFreeze);
		return;
	}
	if(!CheckAttribute(&objControlsState,"keygroups."+grName)) return;

	int i,nq;
	aref arKeyRoot, arKey;

	makearef(arKeyRoot,objControlsState.keygroups.(grName));
	nq = GetAttributesNum(arKeyRoot);
	for(i=0; i<nq; i++)
	{
		arKey = GetAttributeN(arKeyRoot,i);
		LockControl(GetAttributeName(arKey), bFreeze);
	}
}

void AllControlsFreeze(bool bFreeze)
{
	int i,ngq, j,ncq;
	aref arRoot,arGroup;

	makearef(arRoot,objControlsState.keygroups);
	ngq = GetAttributesNum(arRoot);

	for(i=0; i<ngq; i++)
	{
		arGroup = GetAttributeN(arRoot,i);
		ncq = GetAttributesNum(arGroup);
		for(j=0; j<ncq; j++)
		{
			LockControl(GetAttributeName(GetAttributeN(arGroup,j)),bFreeze);
		}
	}
}

object objControlsContainer;
void RunControlsContainers()
{
	//CreateEntity(&objControlsContainer,"controls_container");
	//LayerAddObject(INTERFACE_EXECUTE,&objControlsContainer,1);
}

void ControlsMakeInvert()
{
	int bInvert;
	bool bAllInvert = false;
	if( CheckAttribute(&InterfaceStates,"InvertCameras") && sti(InterfaceStates.InvertCameras)==true ) {
		bAllInvert = true;
	}

	aref arRoot, arCur;
	makearef(arRoot,objControlsState.Inverting);
	int q = GetAttributesNum(arRoot);
	for(int n=0; n<q; n++)
	{
		arCur = GetAttributeN(arRoot,n);
		if(bAllInvert) {bInvert = !sti(GetAttributeValue(arCur));}
		else {bInvert = sti(GetAttributeValue(arCur));}
		XI_ControlMakeInvert( GetAttributeName(arCur), bInvert );
	}

/*
	if (CheckAttribute(&InterfaceStates,"alwaysrun") && sti(InterfaceStates.alwaysrun) == false)
		CI_CreateAndSetControls("PrimaryLand", "ChrRun", CI_GetKeyCode("VK_SHIFT"), USE_AXIS_AS_BUTTON + INVERSE_CONTROL, true);
	else
		CI_CreateAndSetControls("PrimaryLand", "ChrRun", CI_GetKeyCode("VK_SHIFT"), USE_AXIS_AS_BUTTON, true);
*/
}

void SetControlForInverting(string controlName, bool invertState)
{
	objControlsState.Inverting.(controlName) = invertState;
}

void SetRealMouseSensitivity()
{
	XI_SetMouseSensitivity(1.0, 1.0);

	float fLoc = 0.5;
	float fSea = 0.5;
	if(CheckAttribute(InterfaceStates,"mouse.loc_sens"))
		fLoc = stf(InterfaceStates.mouse.loc_sens);
	if(CheckAttribute(InterfaceStates,"mouse.sea_sens"))
		fSea = stf(InterfaceStates.mouse.sea_sens);
	float fRealMouseLocSens = Calculate_sensitivity(fLoc);
	float fRealMouseSeaSens = Calculate_sensitivity(fSea);

	SeaShipCamera.MouseSensitivity = fRealMouseSeaSens;
	SeaDeckCamera.MouseSensitivity = fRealMouseSeaSens * 0.25;
	locCamera.MouseSensitivity = fRealMouseLocSens;
}

// расчет чувствительности мыши
float Calculate_sensitivity(float slider_value) 
{
	float fBase = 5.0;
	if(slider_value < 0.5)
		fBase = 10.0;
	float fPow = Bring2Range(-1.0, 1.0, 0.0, 1.0, slider_value);
	return pow(fBase, fPow);
}

int GetGroupIDX(string sGroupName)
{
    switch(sGroupName)
    {
        case "":
            return BIND_ALL_GROUPS;
            break;
        case "VideoPlayer":
            return BIND_VIDEO_PLAYER;
            break;
        case "MainInterface":
            return BIND_MAIN_INTERFACE;
            break;
        case "DialogControls":
            return BIND_DIALOG;
            break;
        case "BattleInterfaceControls":
            return BIND_BATTLE_INTERFACE;
            break;
        case "WorldMapControls":
            return BIND_WORLD_MAP;
            break;
        case "Sailing1Pers":
            return BIND_SAILING_1PERS;
            break;
        case "Sailing3Pers":
            return BIND_SAILING_3PERS;
            break;
        case "SailingFire":
        	return BIND_SAILING_FIRE;
        	break;
        case "FightModeControls":
            return BIND_FIGHT_MODE;
            break;
        case "PrimaryLand":
            return BIND_PRIMARY_LAND;
            break;
        case "NetShipControls":
            return BIND_NETWORK;
            break;
    }

    CollectCallStack();
    Log_Info("АХТУНГ! НЕИЗВЕСТНАЯ ГРУППА КЛАВИШ! " + sGroupName);
    return INVALID_BIND_GROUP;
}

string GetGroupName(int iGroupIDX)
{
    switch(iGroupIDX)
    {
        case BIND_VIDEO_PLAYER:
            return "VideoPlayer";
            break;
        case BIND_MAIN_INTERFACE:
            return "MainInterface";
            break;
        case BIND_DIALOG:
            return "DialogControls";
            break;
        case BIND_BATTLE_INTERFACE:
            return "BattleInterfaceControls";
            break;
        case BIND_WORLD_MAP:
            return "WorldMapControls";
            break;
        case BIND_SAILING_1PERS:
            return "Sailing1Pers";
            break;
        case BIND_SAILING_3PERS:
            return "Sailing3Pers";
            break;
        case BIND_SAILING_FIRE:
        	return "SailingFire";
        	break;
        case BIND_FIGHT_MODE:
            return "FightModeControls";
            break;
        case BIND_PRIMARY_LAND:
            return "PrimaryLand";
            break;
        case BIND_NETWORK:
            return "NetShipControls";
            break;
    }

    CollectCallStack();
    Log_Info("АХТУНГ! НЕИЗВЕСТНАЯ ГРУППА КЛАВИШ! ИНДЕКС: " + iGroupIDX);
    return "";
}

bool IsSettingsGroup(string sName)
{
    if(sName == "PrimaryLand"  || sName == "FightModeControls" ||
       sName == "Sailing3Pers" || sName == "Sailing1Pers"      ||
       sName == "WorldMapControls") return true;

    return false;
}
