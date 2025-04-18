
#event_handler("frame","procUpdateControlKeyGroup");

// control flags
#define USE_AXIS_AS_BUTTON				1
#define USE_AXIS_AS_INVERSEBUTTON		2
#define INVERSE_CONTROL					4

string curKeyGroupName = "";
object objControlsState;
extern void ExternControlsInit(bool bFirst, int iControlKeys);

native int AddControlTreeNode(int nParent,string sBaseControl,string sOutControl,float fTimeOut);

void ControlsTreeInit()
{
	int n;
	// belamour финт и пари на отдельные кнопки
	/* n = AddControlTreeNode(-1,"ChrAttackFient1","ChrAttackFient",0.0);
	n = AddControlTreeNode(-1,"ChrParry1","ChrParry",0.0); */
}

void ControlsInit(string sPlatformName,bool bFirst, int iControlKeys)
{
	DeleteAttribute(&objControlsState,"");

	string initFileName = "";
	
	
	initFileName = "controls\init_pc.c";
	if(IsSteamDeck()) initFileName = "controls\init_sd.c";

	if(initFileName=="")
	{
		trace("Can`t init controls because not right platform");
		return;
	}
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
	aref arRootKey,arKey;
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
			CI_CreateAndSetControls( grName, ctrlName, keyCode, state, arKey.remapping);
		}
	}

	RunControlsContainers();
}

void CI_CreateContainer( string groupName, string containerName, float containerVal )
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
		sti(objControlsState.key_codes.(keyName).stick)==true )
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

void SyncControls(string groupName, string controlName1, string controlName2) // TO_DO: DEL
{
	if(CheckAttribute(&objControlsState,"keygroups."+groupName+"."+controlName1))
        objControlsState.keygroups.(groupName).(controlName1).sync = controlName2;
    if(CheckAttribute(&objControlsState,"keygroups."+groupName+"."+controlName2))
		objControlsState.keygroups.(groupName).(controlName2).sync = controlName1;
}

void DesyncControls(string groupName, string controlName1, string controlName2) // TO_DO: DEL
{
	if(CheckAttribute(&objControlsState,"keygroups."+groupName+"."+controlName1))
        objControlsState.keygroups.(groupName).(controlName1).desync = controlName2;
    if(CheckAttribute(&objControlsState,"keygroups."+groupName+"."+controlName2))
		objControlsState.keygroups.(groupName).(controlName2).desync = controlName1;
}

string CI_CreateAndSetControls( string groupName, string controlName, int keyCode, int controlState, bool bRemappingEnable )
{
	if(controlName=="") return "";
	string retString = "";

	if( !CheckAttribute(&objControlsState,"map.controls."+controlName) )
	{	objControlsState.map.controls.(controlName) = CreateControl(controlName);
	}
	int cntrlCode = sti(objControlsState.map.controls.(controlName));

	if(keyCode>=0)
	{	string keyName = "key_" + keyCode;
		objControlsState.map.keys.(keyName) = controlName;
	}
	MapControl(cntrlCode,keyCode);

	if(keyCode<0 && controlState==0)
	{	controlState = USE_AXIS_AS_BUTTON;
	}

	if(controlState!=-1)
	{	SetControlFlags(cntrlCode,controlState);
	}
	else
	{	controlState=0;
	}

	if(groupName!="")
	{
		if( CheckAttribute(&objControlsState,"keygroups."+groupName+"."+controlName) )
		{	retString = objControlsState.keygroups.(groupName).(controlName);
		}
		else
		{	objControlsState.keygroups.(groupName).(controlName) = "";
		}
		SetControlsByKey(controlName,CI_GetKeyName(keyCode),controlState);
		objControlsState.keygroups.(groupName).(controlName).remapping = bRemappingEnable;
	}

	return retString;
}

void SetControlsByKey(string controlName, string keyName, int state)
{
	int i,nGQ;
	aref arKGRoot, arKG;

	makearef(arKGRoot,objControlsState.keygroups);
	nGQ = GetAttributesNum(arKGRoot);

	for(i=0; i<nGQ; i++)
	{
		arKG = GetAttributeN(arKGRoot,i);
		if( CheckAttribute(arKG,controlName) )
		{	arKG.(controlName) = keyName;
			arKG.(controlName).state = state;
		}
	}
}

void MapControlToGroup(string controlName,string groupName)
{
	// Найдем использование контрола
	int i,nRootSize;
	aref arRoot,arGroup;

	makearef(arRoot,objControlsState.keygroups);
	nRootSize = GetAttributesNum(arRoot);

	for(i=0; i<nRootSize; i++)
	{
		arGroup = GetAttributeN(arRoot,i);
		if( CheckAttribute(arGroup,controlName) )
		{
			objControlsState.keygroups.(groupName).(controlName) = arGroup.(controlName);
			objControlsState.keygroups.(groupName).(controlName).state = arGroup.(controlName).state;
			if( CheckAttribute(arGroup,controlName+".invisible") ) {
				objControlsState.keygroups.(groupName).(controlName).invisible = arGroup.(controlName).invisible;
			}
			if( CheckAttribute(arGroup,controlName+".remapping") ) {
				objControlsState.keygroups.(groupName).(controlName).remapping = arGroup.(controlName).remapping;
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
		if( sti(GetAttributeValue(arCur)) == code )
		{	return GetAttributeName(arCur);
		}
	}

	return "";
}

int ControlNameToCode(string cname)
{
	if( CheckAttribute(&objControlsState,"map.controls."+cname) )
	{	return sti(objControlsState.map.controls.(cname));
	}
	return -1;
}

string ControlNameToName(string cname) // belamour определение клавиши от контролки
{
	int qC, n, grp, i; 
	string sControl, sKey; 
	aref arGrp, arC, arCnt, arCurgr; 

	makearef(arGrp, objControlsState.keygroups);
	grp = GetAttributesNum(arGrp);
	for( i=0; i<grp; i++ ) // группы конролок 
	{
		arCurgr = GetAttributeN(arGrp,i);
		string sGroup = GetAttributeName(arCurgr);
		makearef(arCnt,objControlsState.keygroups.(sGroup));
		qC = GetAttributesNum(arCnt);
		for( n=0; n<qC; n++ ) // кеи и контролки
		{
			arC = GetAttributeN(arCnt,n);
			sControl = GetAttributeName(arC);
			if(sControl != cname) continue;
			sKey = GetAttributeValue(arC);
		}
	}
	return sKey;
}

string GetKeyCodeImg(string _cval) // belamour определить картинку кнопки
{
	string cname = ControlNameToName(_cval);
	if(CheckAttribute(&objControlsState,"keygroups.AltPressedGroup."+_cval))
		return objControlsState.key_codes.vk_menu.img + objControlsState.key_codes.(cname).img;
	if(cname == "") return "";
	return objControlsState.key_codes.(cname).img;
}

void procUpdateControlKeyGroup()
{
	string newCurGroup = GetCurControlGroup();
	if(curKeyGroupName==newCurGroup) return;

	FreezeGroupControls(curKeyGroupName,true);
	FreezeGroupControls(newCurGroup,false);
	curKeyGroupName = newCurGroup;
}

string GetCurControlGroup()
{
	if( IsEntity(&aviVideoObj) ) return "VideoPlayer";
	//if( bRunHelpChooser ) return "HelpChooser";

	if( sti(InterfaceStates.Launched) == true ) return "MainInterface";

	if( DialogRun ) return "DialogControls";

	if(IsEntity(&worldMap))
	{
		if( CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0 )
			return "BattleInterfaceControls";
		return "WorldMapControls";
	}

	if(bSeaActive && !bAbordageStarted)
	{
		if( CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0 )
			return "BattleInterfaceControls";

		if( SeaCameras.Camera == "SeaDeckCamera" )	{ return "Sailing1Pers"; }
		else { return "Sailing3Pers"; }
	}

	if( CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0 )
		return "BattleInterfaceControls";

	ref mchref = GetMainCharacter();
	if( SendMessage(mchref,"ls",MSG_CHARACTER_EX_MSG,"CheckFightMode") != 0 )
		return "FightModeControls";

	return "PrimaryLand";
}

void FreezeGroupControls(string grName, bool bFreeze)
{
	if(grName=="")
	{
		AllControlsFreeze(bFreeze);
		return;
	}
	if( !CheckAttribute(&objControlsState,"keygroups."+grName) ) return;

	int i,nq;
	aref arKeyRoot, arKey;

	makearef(arKeyRoot,objControlsState.keygroups.(grName));
	nq = GetAttributesNum(arKeyRoot);
	for(i=0; i<nq; i++)
	{
		arKey = GetAttributeN(arKeyRoot,i);
		LockControl(GetAttributeName(arKey),bFreeze);
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