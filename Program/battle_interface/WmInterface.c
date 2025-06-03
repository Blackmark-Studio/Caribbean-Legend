void InitWmInterface()
{
	if (bGameMenuStart)
	{
		return;
	}
	DeleteAttribute(&BattleInterface,"");
	WM_InitializeCommands();
	WM_SetParameterData();

	CreateEntity(&BattleInterface,"WM_INTERFACE");
	LayerAddObject(EXECUTE,&BattleInterface,-1);
	LayerAddObject(REALIZE,&BattleInterface,-1);

	SetEventHandler("BI_CommandEndChecking","WM_CommandEndChecking",0);
	SetEventHandler("BI_LaunchCommand","WM_LaunchCommand",0);
	SetEventHandler("WM_SetPossibleCommands","WM_SetPossibleCommands",0);
	SetEventHandler("WM_UpdateCurrentAction","WM_UpdateCurrentAction",0);

	CreateILogAndActions(LOG_FOR_WORLDMAP);
	Log_SetActiveAction("EnterToSea");

	SetEventHandler("BI_UpdateWmInterface","BI_UpdateWmInterface",0);
	PostEvent("BI_UpdateWmInterface",1000);
	SetEventHandler("Control Activation","WM_ProcessControlPress",0); // boal
}
// boal -->
void WM_ProcessControlPress()
{
	string ControlName = GetEventData();
	if( sti(InterfaceStates.Launched) != 0 ) {return;}

	switch(ControlName)
	{
		case "BICommandsActivate": 
			PlaySound("interface\ok.wav"); // boal даёшь звуки!
		break;
	}
}
// boal <--

void BI_UpdateWmInterface()
{
	WM_SetShipData(); // после перемещения команды или обмена
	SendMessage(&BattleInterface,"l",BI_MSG_REFRESH);
	PostEvent("BI_UpdateWmInterface",1000);
}

void DeleteWmInterface()
{
	DeleteClass(&BattleInterface);
	DelEventHandler("BI_CommandEndChecking", "WM_CommandEndChecking");
	DelEventHandler("BI_LaunchCommand", "WM_LaunchCommand");
	DelEventHandler("WM_SetPossibleCommands","WM_SetPossibleCommands");
	DelEventHandler("WM_UpdateCurrentAction","WM_UpdateCurrentAction");

	DelEventHandler("BI_UpdateWmInterface","BI_UpdateWmInterface");
	DelEventHandler("Control Activation","WM_ProcessControlPress"); // boal
	Log_SetActiveAction("Nothing");
}

ref WM_CommandEndChecking()
{
	BI_retComValue = 0;
	string comName = GetEventData();

	switch(comName)
	{
	case "cancel":
		BI_retComValue = -1;
		break;
	}

	return &BI_retComValue;
}

void WM_LaunchCommand()
{
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

	switch(commandName)
	{
	case "EnterToSea":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToIsland":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToShip":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToStorm":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToAttack":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToEnemy":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	}

	BI_SetSpecCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1, 0);
}

void WM_SetPossibleCommands()
{
	int chIdx = GetEventData();
	int mainIdx = sti(pchar.index);

	if( chIdx<0 || CharacterIsDead(GetCharacter(chIdx)) )
	{
		// отключим все команды
		aref aroot,arcur;
		makearef(aroot,BattleInterface.Commands);
		int q = GetAttributesNum(aroot);
		for(int i=0; i<q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		return;
	}

	BattleInterface.Commands.Cancel.enable = true;
	BattleInterface.Commands.EnterToAttack.enable = false;
	BattleInterface.Commands.EnterToShip.enable	= false;
	BattleInterface.Commands.EnterToSea.enable = false;
	BattleInterface.Commands.EnterToIsland.enable = false;
	BattleInterface.Commands.EnterToStorm.enable = false;
	BattleInterface.Commands.EnterToEnemy.enable = false;

	bool bDefault = true;
	switch( sti(worldMap.encounter_type) )
	{
	case 0:
		BattleInterface.Commands.EnterToIsland.enable = true;
		//Log_SetActiveAction("EnterToIsland");
		Log_SetActiveAction("EnterToSea");  //boal
		bDefault = false;
		break;
	case 1:
		BattleInterface.Commands.EnterToShip.enable	= true;
		Log_SetActiveAction("EnterToShip");
		bDefault = false;
		break;
	case 2:
		BattleInterface.Commands.EnterToAttack.enable = true;
		Log_SetActiveAction("EnterToAttack");
		bDefault = false;
		break;
	case 3:
		BattleInterface.Commands.EnterToEnemy.enable = true;
		Log_SetActiveAction("EnterToEnemy");
		bDefault = false;
		break;
	case 4:
		BattleInterface.Commands.EnterToStorm.enable = true;
		Log_SetActiveAction("EnterToStorm");
		bDefault = false;
		break;
	}

	if( bDefault )
	{
		if( sti(worldMap.encounter_island) ) {
			BattleInterface.Commands.EnterToIsland.enable = true;
			//Log_SetActiveAction("EnterToIsland");
			Log_SetActiveAction("EnterToSea");  //boal
		} else {
			BattleInterface.Commands.EnterToSea.enable = true;
			Log_SetActiveAction("EnterToSea");
		}
	}
}

void WM_UpdateCurrentAction()
{
	bool bDefault = true;
	switch( sti(worldMap.encounter_type) )
	{
	case 0:
		//Log_SetActiveAction("EnterToIsland");
		Log_SetActiveAction("EnterToSea");  //boal
		bDefault = false;
		break;
	case 1:
		if(FindRealEncounterTypeFromId(worldMap.areaEncId) > ENCOUNTER_TYPE_ALONE)
		{
			Log_SetActiveAction("GetOnBoard");
			bDefault = false;
			break;
		}
		Log_SetActiveAction("EnterToShip");
		bDefault = false;
		break;
	case 2:
		Log_SetActiveAction("EnterToAttack");
		bDefault = false;
		break;
	case 3:
		Log_SetActiveAction("EnterToEnemy");
		bDefault = false;
		break;
	case 4:
		Log_SetActiveAction("EnterToStorm");
		bDefault = false;
		break;
	}
	if( bDefault ) {
		if( sti(worldMap.encounter_island) ) {
			//Log_SetActiveAction("EnterToIsland");
			Log_SetActiveAction("EnterToSea");  //boal
		} else {
			Log_SetActiveAction("EnterToSea");
		}
	}
	SendMessage(&BattleInterface,"l",BI_MSG_REFRESH);
}

void WM_InitializeCommands()
{
	int idLngFile = LanguageOpenFile("commands_name.txt");

	BattleInterface.Commands.EnterToSea.enable			= false;
 	BattleInterface.Commands.EnterToSea.picNum			= 1;
	BattleInterface.Commands.EnterToSea.selPicNum		= 9;
	BattleInterface.Commands.EnterToSea.texNum			= 1;
	BattleInterface.Commands.EnterToSea.event			= "EnterToSea";
	BattleInterface.Commands.EnterToSea.note			= LanguageConvertString(idLngFile, "worldmap_tosea");

	BattleInterface.Commands.EnterToIsland.enable		= false;
	BattleInterface.Commands.EnterToIsland.picNum		= 1;
	BattleInterface.Commands.EnterToIsland.selPicNum	= 9;
	BattleInterface.Commands.EnterToIsland.texNum		= 1;
	BattleInterface.Commands.EnterToIsland.event		= "EnterToIsland";
	BattleInterface.Commands.EnterToIsland.note			= LanguageConvertString(idLngFile, "worldmap_toisland");

	BattleInterface.Commands.EnterToShip.enable			= false;
	BattleInterface.Commands.EnterToShip.picNum			= 4;
	BattleInterface.Commands.EnterToShip.selPicNum		= 12;
	BattleInterface.Commands.EnterToShip.texNum			= 1;
	BattleInterface.Commands.EnterToShip.event			= "EnterToShip";
	BattleInterface.Commands.EnterToShip.note			= LanguageConvertString(idLngFile, "worldmap_toship");

	BattleInterface.Commands.EnterToStorm.enable		= false;
	BattleInterface.Commands.EnterToStorm.picNum		= 5;
	BattleInterface.Commands.EnterToStorm.selPicNum		= 13;
	BattleInterface.Commands.EnterToStorm.texNum		= 1;
	BattleInterface.Commands.EnterToStorm.event			= "EnterToStorm";
	BattleInterface.Commands.EnterToStorm.note			= LanguageConvertString(idLngFile, "worldmap_tostorm");

	BattleInterface.Commands.EnterToAttack.enable		= false;
	BattleInterface.Commands.EnterToAttack.picNum		= 2;
	BattleInterface.Commands.EnterToAttack.selPicNum	= 10;
	BattleInterface.Commands.EnterToAttack.texNum		= 1;
	BattleInterface.Commands.EnterToAttack.event		= "EnterToAttack";
	BattleInterface.Commands.EnterToAttack.note			= LanguageConvertString(idLngFile, "worldmap_toattack");

	BattleInterface.Commands.EnterToEnemy.enable		= false;
	BattleInterface.Commands.EnterToEnemy.picNum		= 3;
	BattleInterface.Commands.EnterToEnemy.selPicNum		= 11;
	BattleInterface.Commands.EnterToEnemy.texNum		= 1;
	BattleInterface.Commands.EnterToEnemy.event			= "EnterToEnemy";
	BattleInterface.Commands.EnterToEnemy.note			= LanguageConvertString(idLngFile, "worldmap_toenemy");

	BattleInterface.Commands.Cancel.enable				= false;
	BattleInterface.Commands.Cancel.picNum				= 1;
	BattleInterface.Commands.Cancel.selPicNum			= 0;
	BattleInterface.Commands.Cancel.texNum				= 0;
	BattleInterface.Commands.Cancel.event				= "Cancel";
	BattleInterface.Commands.Cancel.note				= LanguageConvertString(idLngFile, "sea_Cancel");

	LanguageCloseFile(idLngFile);

	worldMap.encounter_type = -1;
}

void WM_SetParameterData()
{
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	int fTmp, fTmp2, fTmp3, fTmp4;
	BattleInterface.CommandTextures.list.t0.name = "interfaces\le\battle_interface\cancel.tga.tx";
	BattleInterface.CommandTextures.list.t0.xsize = 2;
	BattleInterface.CommandTextures.list.t0.ysize = 1;

	BattleInterface.CommandTextures.list.t1.name = "interfaces\le\battle_interface\worldmapcommands.tga.tx";
	BattleInterface.CommandTextures.list.t1.xsize = 8;
	BattleInterface.CommandTextures.list.t1.ysize = 2;

	float fRes = 1.0; // для ресайза компаньонов
	BattleInterface.wm_sign.fontid					= "interface_normal";
	BattleInterface.wm_sign.fontcolor				= argb(255,255,255,168); //argb(255,255,255,255);
	BattleInterface.wm_sign.fontscale				= 1.5 * fHtRatio;
    fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(40.0 * fRes * fHtRatio);
    BattleInterface.wm_sign.fontoffset       		= fTmp + "," + fTmp2;

	BattleInterface.wm_sign.shipnamefontid			= "interface_normal";
	BattleInterface.wm_sign.shipnamefontcolor		= argb(255,255,255,255);
	BattleInterface.wm_sign.shipnamefontscale		= 1.3 * fHtRatio;
    fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(60.0 * fHtRatio);
    BattleInterface.wm_sign.shipnamefontoffset      = fTmp + "," + fTmp2;

	BattleInterface.wm_sign.backmctexturename			= "interfaces\le\battle_interface\ShipBackIcon1.tga.tx";
	BattleInterface.wm_sign.backtexturename			= "interfaces\le\battle_interface\ShipBackIcon2.tga.tx";
	BattleInterface.wm_sign.backcolor				= argb(255,128,128,128);
	BattleInterface.wm_sign.backuv					= "0.0,0.0,1.0,1.0";
	BattleInterface.wm_sign.backoffset				= "0,0";
    fTmp = makeint(128.0 * fRes * fHtRatio);
	BattleInterface.wm_sign.backiconsize			= fTmp + "," + fTmp;

	BattleInterface.wm_sign.shipstatetexturename	= "interfaces\le\battle_interface\ShipState.tga.tx";
	BattleInterface.wm_sign.shipstatecolor			= argb(255,128,128,128);
	BattleInterface.wm_sign.shiphpuv				= "0.0,0.1875,0.5,0.7968";
	BattleInterface.wm_sign.shipspuv				= "0.5,0.1875,1.0,0.7968";
    fTmp = makeint(-33.0 * fHtRatio);
    fTmp2 = makeint(0.0 * fHtRatio);
    BattleInterface.wm_sign.shiphpoffset			= fTmp + "," + fTmp2;
    fTmp = makeint(33.0 * fHtRatio);
	BattleInterface.wm_sign.shipspoffset			= fTmp + "," + fTmp2;
	
    fTmp = makeint(60.0 * fHtRatio);
    fTmp2 = makeint(76.0 * fHtRatio);
    BattleInterface.wm_sign.shiphpiconsize			= fTmp + "," + fTmp2;
	BattleInterface.wm_sign.shipspiconsize			= fTmp + "," + fTmp2;


	BattleInterface.wm_sign.shipclasstexturename	= "interfaces\le\battle_interface\ShipClass.tga.tx";
	BattleInterface.wm_sign.shipclasscolor			= argb(255,102,102,102); //argb(255,128,128,128);
	BattleInterface.wm_sign.shipclassuv				= "0.0,0.0,1.0,1.0";

	fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(-54.0 * fHtRatio);
    BattleInterface.wm_sign.shipclassoffset			= fTmp + "," + fTmp2;
	
    fTmp = makeint(128.0 * fRes * fHtRatio);
    fTmp2 = makeint(32.0 * fRes * fHtRatio);
    BattleInterface.wm_sign.shipclassiconsize		= fTmp + "," + fTmp2;

	BattleInterface.wm_sign.gunchargeprogress		= "0.0625, 0.211, 0.359, 0.5, 0.633, 0.781, 0.983";

	BattleInterface.wm_sign.shiptexturename			= "interfaces\le\battle_interface\ship_icons2.tga.tx";
	BattleInterface.wm_sign.shipcolor				= argb(255,128,128,128);
	
    fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(0.0 * fHtRatio);
    BattleInterface.wm_sign.shipoffset				= fTmp + "," + fTmp2;

    fTmp = makeint(90.0 * fRes * fHtRatio);
    BattleInterface.wm_sign.shipiconsize			= fTmp + "," + fTmp;

    fTmp = makeint(-20 * fHtRatio);
    BattleInterface.wm_sign.commandlistverticaloffset = fTmp;

    fTmp = makeint(75.0 * fHtRatio);
    fTmp3 = fTmp;
    fTmp2 = makeint(150.0 * fHtRatio);
    BattleInterface.wm_sign.iconoffset1 = fTmp + "," + fTmp;
    fTmp3 += fTmp2;
    BattleInterface.wm_sign.iconoffset2 = fTmp + "," + fTmp3;
	fTmp3 += fTmp2;
    BattleInterface.wm_sign.iconoffset3 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.wm_sign.iconoffset4 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.wm_sign.iconoffset5 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.wm_sign.iconoffset6 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.wm_sign.iconoffset7 = fTmp + "," + fTmp3;
    fTmp3 += fTmp2;
    BattleInterface.wm_sign.iconoffset8 = fTmp + "," + fTmp3;

	BattleInterface.CommandList.CommandMaxIconQuantity = 8;
	BattleInterface.CommandList.CommandIconSpace = 1;
	BattleInterface.CommandList.CommandIconLeft = makeint(160 * fHtRatio);//157;
	BattleInterface.CommandList.CommandIconWidth = RecalculateHIcon(makeint(55 * fHtRatio));
	BattleInterface.CommandList.CommandIconHeight = RecalculateVIcon(makeint(55 * fHtRatio));

	BattleInterface.CommandList.CommandNoteFont = "interface_normal_bold";
	BattleInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
	BattleInterface.CommandList.CommandNoteScale = 0.65 * fHtRatio;
	BattleInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(makeint(-50 * fHtRatio));

	// BattleInterface.CommandList.CommandNoteFont = "interface_normal";
	// BattleInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
	// BattleInterface.CommandList.CommandNoteScale = 1.0 * fHtRatio;
	// BattleInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(makeint(-42 * fHtRatio));

	BattleInterface.CommandList.UDArrow_Texture = "interfaces\le\battle_interface\arrowly.tga.tx";
	BattleInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
	BattleInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
	BattleInterface.CommandList.UDArrow_Size = RecalculateHIcon(makeint(30 * fHtRatio)) + "," + RecalculateVIcon(makeint(30 * fHtRatio));
	BattleInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(makeint(-30 * fHtRatio)) + "," + RecalculateVIcon(makeint(-45 * fHtRatio));
	BattleInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(makeint(-30 * fHtRatio)) + "," + RecalculateVIcon(makeint(45 * fHtRatio));

	BattleInterface.maincharindex = pchar.index;
	
	// evganat - динамический интерфейс
	WM_SetNationsThreat();

	WM_SetShipData();
}

void WM_SetShipData()
{
	int i,n,cn;
	string signattr;
	float uvleft,uvtop, uvright,uvbottom;

	i = 1;
	for(n=0; n<COMPANION_MAX; n++)
	{
		cn = GetCompanionIndex(pchar,n);
		if( cn!=-1 )
		{
			signattr = "sign" + i;
			BattleInterface.wm_sign.(signattr).leftprogress = GetHullPercent(&Characters[cn]) * 0.01;
			BattleInterface.wm_sign.(signattr).rightprogress = GetSailPercent(&Characters[cn]) * 0.01;
			GetStarProgressByValue(GetCharacterShipClass(&Characters[cn]), &uvleft, &uvtop, &uvright, &uvbottom);
			BattleInterface.wm_sign.(signattr).starprogress = uvleft+","+uvtop + "," + uvright+","+uvbottom;
			GetTextureUVForShip( sti(RealShips[sti(characters[cn].Ship.Type)].basetype), &uvleft,&uvtop, &uvright,&uvbottom);
			BattleInterface.wm_sign.(signattr).faceuv = uvleft+","+uvtop + "," + uvright+","+uvbottom;
			BattleInterface.wm_sign.(signattr).text = GetCrewQuantity(&Characters[cn]);
			BattleInterface.wm_sign.(signattr).shipname = Characters[cn].Ship.Name;
			i++;
		}
	}
}

//belamour присвоить uv классу корабля (замена progressbar)
void GetStarProgressByValue(int n, ref rLeft, ref rTop, ref rRight, ref rBottom)
{
	float fLeft = 0.0;
	float fRight = 0.0;
	
	float pw = 1.0/8.0; 
	
	fLeft = pw*n;
    fRight = fLeft + pw;
	
	rLeft = fLeft;
    rTop = 0.0; 
    rRight = fRight;
    rBottom = 1.0; 
}

void WM_NullNationsThreat()
{
	DeleteAttribute(&BattleInterface, "wm_dynamic.images");
//	BattleInterface.wm_dynamic.images.backtexture.group = "TUTORIAL_BACK";
//	BattleInterface.wm_dynamic.images.backtexture.picture = "background";
	BattleInterface.wm_dynamic.images.englandflag.group = "message_icons";
	BattleInterface.wm_dynamic.images.englandflag.picture = "england";
	BattleInterface.wm_dynamic.images.englandthreat.group = "message_icons";
	BattleInterface.wm_dynamic.images.englandthreat.picture = "threat0";
	BattleInterface.wm_dynamic.images.franceflag.group = "message_icons";
	BattleInterface.wm_dynamic.images.franceflag.picture = "france";
	BattleInterface.wm_dynamic.images.francethreat.group = "message_icons";
	BattleInterface.wm_dynamic.images.francethreat.picture = "threat0";
	BattleInterface.wm_dynamic.images.spainflag.group = "message_icons";
	BattleInterface.wm_dynamic.images.spainflag.picture = "spain";
	BattleInterface.wm_dynamic.images.spainthreat.group = "message_icons";
	BattleInterface.wm_dynamic.images.spainthreat.picture = "threat0";
	BattleInterface.wm_dynamic.images.hollandflag.group = "message_icons";
	BattleInterface.wm_dynamic.images.hollandflag.picture = "holland";
	BattleInterface.wm_dynamic.images.hollandthreat.group = "message_icons";
	BattleInterface.wm_dynamic.images.hollandthreat.picture = "threat0";
	BattleInterface.wm_dynamic.images.pirateflag.group = "message_icons";
	BattleInterface.wm_dynamic.images.pirateflag.picture = "pirate";
	BattleInterface.wm_dynamic.images.piratethreat.group = "message_icons";
	BattleInterface.wm_dynamic.images.piratethreat.picture = "threat0";
}

void WM_SetNationsThreat()
{
	WM_NullNationsThreat();
	int iNation;
	int iThreat[5];
	int nLevels = 0;
	for(iNation = ENGLAND; iNation <= PIRATE; iNation++)
	{
		iThreat[iNation] = wdmGetNationThreat(iNation);
		if(iThreat[iNation] > 0 && !wdmCompareEncPower(iNation))
			nLevels++;
	}
	
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	int x1, y1, x2, y2;
	int backwidth, widthFlag, heightFlag, widthThreat, heightThreat, spaceM, spaceL, voffset, vspace, offsetThreat;

	// задаём все размеры и интервалы
	widthFlag = makeint(60 * fHtRatio);
	heightFlag = makeint(60 * fHtRatio);
	widthThreat = makeint(28 * fHtRatio);
	heightThreat = makeint(28 * fHtRatio);
	offsetThreat = makeint(30 * fHtRatio);
	spaceM = makeint(4 * fHtRatio);
	spaceL = makeint(18 * fHtRatio);
	voffset = makeint(20 * fHtRatio);
	vspace = makeint(8 * fHtRatio);
	
	// задаём задник через размеры и интервалы
	backwidth = spaceL + widthFlag * nLevels + spaceM * (nLevels - 1) + spaceL;
	y1 = sti(showWindow.top) + voffset;
	y2 = y1 + vspace + heightFlag + vspace;
	int centerH = sti(showWindow.right) / 2;
	x1 = centerH - backwidth / 2;
	x2 = x1 + backwidth;
	
	// выставляем задник
	aref arImage;
//	makearef(arImage, BattleInterface.wm_dynamic.images.backtexture);
//	arImage.pos = GetPosString(x1, y1, x2, y2);
	if(nLevels == 0)
		DeleteAttribute(&BattleInterface, "wm_dynamic.images.backtexture");
	
	// выставляем флаги и значки угрозы
	string sFlag, sThreat, sNation;
	int iFlag = 0;
	for(iNation = ENGLAND; iNation <= PIRATE; iNation++)
	{
		sNation = Nations[iNation].name;
		sFlag = sNation + "flag";
		sThreat = sNation + "threat";
		if(iThreat[iNation] > 0 && !wdmCompareEncPower(iNation))
		{
			// флаг
			makearef(arImage, BattleInterface.wm_dynamic.images.(sFlag));
			// задаём позицию через размеры и интервалы
			x1 = centerH - backwidth / 2 + spaceL + (widthFlag + spaceM) * iFlag;
			x2 = x1 + widthFlag;
			y1 = sti(showWindow.top) + voffset + vspace;
			y2 = y1 + heightFlag;
			arImage.pos = GetPosString(x1, y1, x2, y2);
			// угроза
			makearef(arImage, BattleInterface.wm_dynamic.images.(sThreat));
			arImage.picture = "threat" + iThreat[iNation];
			// задаём позицию через размеры и интервалы
			x1 = centerH - backwidth / 2 + spaceL + (widthFlag + spaceM) * iFlag + offsetThreat;
			x2 = x1 + widthThreat;
			y1 = sti(showWindow.top) + voffset + vspace + offsetThreat;
			y2 = y1 + heightThreat;
			arImage.pos = GetPosString(x1, y1, x2, y2);
			
			iFlag++;
		}
	}
}

string GetPosString(int x1, int y1, int x2, int y2)
{
	return x1 + "," + y1 + "," + x2 + "," + y2;
}