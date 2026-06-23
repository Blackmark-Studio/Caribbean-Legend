
void OSL_WriteGameOption()
{
	object gopt;
	PrepareDefaultOption(&gopt);
	GetRealOptions(&gopt);
	SaveSavedOptions(&gopt);
}

void OSL_ReadGameOption()
{
	object gopt;
	PrepareDefaultOption(&gopt);
	ReadSavedOptions(&gopt);
	SetCurentOptions(&gopt);
}

void PrepareDefaultOption(ref optref)
{   
	optref.volume.music = 0.25;
	optref.volume.sound = 0.25;
	optref.volume.dialog = 0.25;
	optref.cameramode.SFW = false;
	optref.cameramode.follow_on = true;
	/*
	optref.arcademode.bArcadeSails = true;
	optref.arcademode.bArcadeShipSpeed = true;
	optref.arcademode.bArcadeCannonsReload = true;
	optref.arcademode.bArcadeCannonsAccuracy = true;
	optref.arcademode.bArcadeFencingAI = true;
	optref.arcademode.bArcadeFencingDamage = true;
	optref.arcademode.bArcadeFencingEquip = true;
	optref.arcademode.bArcadeSailTo = true;
	*/
	optref.alwaysrun = true;
	optref.AdvancedChange = false;
	optref.video.grassquality = 0;
	optref.seadetails = 1.0;
	optref.ifov = 1;
	optref.ifonttype = 0;
	optref.imoreinfo = 0;
	optref.icontrolsmode = 0;
	optref.icompasspos = 0;
	optref.icontrolstips = 2;
	optref.ihelptime = 1;
	optref.icamera = 1;
	optref.ienemytype = 1;
	optref.itarget = 2;
	optref.FoliageDrawDistance = 1000;
	optref.GrassDrawDistance = 50;
	optref.ivisualscheme = 0;
	optref.idialogscale = 0;
	optref.ibestcourse = 0;
	
	SeaParametrs.MaxVertices = MaxVertices;
	SeaParametrs.MaxIndices = MaxIndices;
	SeaParametrs.GridStepX = GridStepX;
	SeaParametrs.GridStepPC = GridStepPC;
	SeaParametrs.LodScale = LodScale;
	SeaParametrs.MaxWaveDistance = MaxWaveDistance;
}

void GetRealOptions(ref optref)
{
	float ftmp1,ftmp2,ftmp3;

	ftmp1 = float(optref.volume.sound);
	ftmp2 = float(optref.volume.music);
	ftmp3 = float(optref.volume.dialog);
	SendMessage(&sound,"leee", MSG_SOUND_GET_MASTER_VOLUME, &ftmp1, &ftmp2,	&ftmp3 );
	optref.volume.sound = ftmp1;
	optref.volume.music = ftmp2;
	optref.volume.dialog = ftmp3;

	/*
	optref.arcademode.bArcadeSails = bArcadeSails;
	optref.arcademode.bArcadeShipSpeed = bArcadeShipSpeed;
	optref.arcademode.bArcadeCannonsReload = bArcadeCannonsReload;
	optref.arcademode.bArcadeCannonsAccuracy = bArcadeCannonsAccuracy;
	optref.arcademode.bArcadeFencingAI = bArcadeFencingAI;
	optref.arcademode.bArcadeFencingDamage = bArcadeFencingDamage;
	optref.arcademode.bArcadeFencingEquip = bArcadeFencingEquip;
	optref.arcademode.bArcadeSailTo = bArcadeSailTo;
	*/

	optref.cameramode.follow_on = !locCameraEnableSpecialMode;

	optref.video.grassquality = iGrassQuality;

	if( CheckAttribute(&InterfaceStates,"Fov") ) {
		optref.ifov = int(InterfaceStates.Fov);
	} else {
		optref.ifov = 1;
	}

	if( CheckAttribute(&InterfaceStates,"FontType") ) {
		optref.ifonttype = int(InterfaceStates.FontType);
	} else {
		optref.ifonttype = 0;
	}

	if( CheckAttribute(&InterfaceStates,"MoreInfo") ) {
		optref.imoreinfo = int(InterfaceStates.MoreInfo);
	} else {
		optref.imoreinfo = 0;
	}

	if( CheckAttribute(&InterfaceStates,"ControlsMode") ) {
		optref.icontrolsmode = int(InterfaceStates.ControlsMode);
	} else {
		optref.icontrolsmode = 0;
	}

	if( CheckAttribute(&InterfaceStates,"CompassPos") ) {
		optref.icompasspos = int(InterfaceStates.CompassPos);
	} else {
		optref.icompasspos = 0;
	}

	if( CheckAttribute(&InterfaceStates,"ControlsTips") ) {
		optref.icontrolstips = int(InterfaceStates.ControlsTips);
	} else {
		optref.icontrolstips = 2;
	}

	if( CheckAttribute(&InterfaceStates,"HelpTime") ) {
		optref.ihelptime = int(InterfaceStates.HelpTime);
	} else {
		optref.ihelptime = 1;
	}

	if( CheckAttribute(&InterfaceStates,"Camera") ) {
		optref.icamera = int(InterfaceStates.Camera);
	} else {
		optref.icamera = 1;
	}

	if( CheckAttribute(&InterfaceStates,"EnemyType") ) {
		optref.ienemytype = int(InterfaceStates.EnemyType);
	} else {
		optref.ienemytype = 1;
	}

	if( CheckAttribute(&InterfaceStates,"Target") ) {
		optref.itarget = int(InterfaceStates.Target);
	} else {
		optref.itarget = 2;
	}
	
	if( CheckAttribute(&InterfaceStates,"VisualScheme") ) {
		optref.ivisualscheme = int(InterfaceStates.VisualScheme);
	} else {
		optref.ivisualscheme = 0;
	}
	
	if( CheckAttribute(&InterfaceStates,"DialogScale") ) {
		optref.idialogscale = int(InterfaceStates.DialogScale);
	} else {
		optref.idialogscale = 0;
	}
	
	if( CheckAttribute(&InterfaceStates,"BestCourse") ) {
		optref.ibestcourse = int(InterfaceStates.BestCourse);
	} else {
		optref.ibestcourse = 0;
	}
	
	if( CheckAttribute(&InterfaceStates,"SeaDetails") ) {
		optref.seadetails = float(InterfaceStates.SeaDetails);
	}

	if( CheckAttribute(&InterfaceStates,"FoliageDrawDistance") ) {
		if (int(optref.FoliageDrawDistance)>3000) optref.FoliageDrawDistance = 3000;
		else optref.FoliageDrawDistance = float(InterfaceStates.FoliageDrawDistance);
	} else {
		optref.FoliageDrawDistance = 1000;
	}

	if( CheckAttribute(&InterfaceStates,"GrassDrawDistance") ) {
		optref.GrassDrawDistance = float(InterfaceStates.GrassDrawDistance);
	} else {
		optref.GrassDrawDistance = 50;
	}

	if( CheckAttribute(&InterfaceStates,"ClassicSoundScene") ) {
		optref.cameramode.ClassicSoundScene = int(InterfaceStates.ClassicSoundScene);
	} else {
		optref.cameramode.ClassicSoundScene = true;
	}

	if( CheckAttribute(&InterfaceStates,"SFW") ) {
		optref.cameramode.SFW = int(InterfaceStates.SFW);
	} else {
		optref.cameramode.SFW = false;
	}

	if( CheckAttribute(&InterfaceStates,"InvertCameras") ) {
		optref.cameramode.InvertCameras = int(InterfaceStates.InvertCameras);
	} else {
		optref.cameramode.InvertCameras = false;
	}

	if( CheckAttribute(&InterfaceStates,"ShowBattleMode") ) {
		optref.cameramode.ShowBattleMode = int(InterfaceStates.ShowBattleMode);
	} else {
		optref.cameramode.ShowBattleMode = true;
	}

	if( CheckAttribute(&InterfaceStates,"ShowCharString") ) {
		optref.cameramode.ShowCharString = int(InterfaceStates.ShowCharString);
	} else {
		optref.cameramode.ShowCharString = true;
	}

	if( CheckAttribute(&InterfaceStates,"ShowTutorial") ) {
		optref.cameramode.ShowTutorial = int(InterfaceStates.ShowTutorial);
	} else {
		optref.cameramode.ShowTutorial = true;
	}
	
	// автосейвы
	string sAutoSave;
	for(int i = 0; i < 13; i++)
	{
		sAutoSave = "AutoSave_" + GetAutoSaveType(i);
		if(CheckAttribute(&InterfaceStates, sAutoSave))
			optref.(sAutoSave) = int(InterfaceStates.(sAutoSave));
		else
			optref.(sAutoSave) = -1;
	}

	if( CheckAttribute(&InterfaceStates,"EnabledQuestsMarks") ) {
		optref.cameramode.EnabledQuestsMarks = int(InterfaceStates.EnabledQuestsMarks);
	} else {
		optref.cameramode.EnabledQuestsMarks = true;
	}

	if( CheckAttribute(&InterfaceStates,"EnabledShipMarks") ) {
		optref.cameramode.EnabledShipMarks = int(InterfaceStates.EnabledShipMarks);
	} else {
		optref.cameramode.EnabledShipMarks = 1;
	}
	if (int(optref.cameramode.EnabledShipMarks)>0) bDrawBars = true;
	else bDrawBars = bool(optref.cameramode.EnabledShipMarks);

	if( CheckAttribute(&InterfaceStates,"SimpleSea") ) {
		optref.cameramode.SimpleSeaMode = int(InterfaceStates.SimpleSea);
	} else {
		optref.cameramode.SimpleSeaMode = true;
	}

	if( CheckAttribute(&InterfaceStates,"CREWONDECK") ) {
		optref.cameramode.CREWONDECKMode = int(InterfaceStates.CREWONDECK);
	} else {
		optref.cameramode.CREWONDECKMode = true;
	}

	if( CheckAttribute(&InterfaceStates,"ROTATESKY") ) {
		optref.cameramode.ROTATESKYMode = int(InterfaceStates.ROTATESKY);
	} else {
		optref.cameramode.ROTATESKYMode = false;
	}
	if( CheckAttribute(&InterfaceStates,"DYNAMICLIGHTS") ) {
		optref.cameramode.DYNAMICLIGHTSMode = int(InterfaceStates.DYNAMICLIGHTS);
	} else {
		optref.cameramode.DYNAMICLIGHTSMode = true;
	}
	GetControlsOptions(optref);

	// mouse
	if( CheckAttribute(&InterfaceStates,"mouse.loc_sens") ) {
		optref.mouse.loc_sensitivity = InterfaceStates.mouse.loc_sens;
	} else {
		optref.mouse.loc_sensitivity = 0.5;
	}
	if( CheckAttribute(&InterfaceStates,"mouse.sea_sens") ) {
		optref.mouse.sea_sensitivity = InterfaceStates.mouse.sea_sens;
	} else {
		optref.mouse.sea_sensitivity = 0.5;
	}
	// video colors
	if( CheckAttribute(&InterfaceStates,"video.contrast") ) {
		optref.video.contrast = InterfaceStates.video.contrast;
	} else {
		optref.video.contrast = 1.0;
	}
	if( CheckAttribute(&InterfaceStates,"video.gamma") ) {
		optref.video.gamma = InterfaceStates.video.gamma;
	} else {
		optref.video.gamma = 1.0;
	}
	if( CheckAttribute(&InterfaceStates,"video.brightness") ) {
		optref.video.brightness = InterfaceStates.video.brightness;
	} else {
		optref.video.brightness = 0.0;
	}
	
	// Warship 07.07.09 Эффект свечения
	if(CheckAttribute(&InterfaceStates, "GlowEffect"))
	{
		optref.GlowEffect = InterfaceStates.GlowEffect;
	}
	else
	{
		optref.GlowEffect = 0;
	}
	
	SeaParametrs.MaxVertices = MaxVertices;
	SeaParametrs.MaxIndices = MaxIndices;
	SeaParametrs.GridStepX = GridStepX;
	SeaParametrs.GridStepPC = GridStepPC;
	SeaParametrs.MaxWaveDistance = MaxWaveDistance;
	SeaParametrs.LodScale = LodScale;

	// always run
	if( CheckAttribute(&InterfaceStates,"alwaysrun") ) {
		optref.alwaysrun = InterfaceStates.alwaysrun;
	} else {
		optref.alwaysrun = false;
	}
	// advancedchange
	if( CheckAttribute(&InterfaceStates,"AdvancedChange") ) {
		optref.AdvancedChange = InterfaceStates.AdvancedChange;
	} else {
		optref.AdvancedChange = false;
	}

	// belamour legendary edition информация о текущем профиле
	if(CheckAttribute(&PlayerProfile,"name")) 
		optref.StartGameParam.PlayerProfile  = PlayerProfile.name;

}

void SetCurentOptions(ref optref)
{
	SendMessage(&sound,"lfff", MSG_SOUND_SET_MASTER_VOLUME, float(optref.volume.sound), float(optref.volume.music), float(optref.volume.dialog));

	/*bArcadeSails = int(optref.arcademode.bArcadeSails);
	bArcadeShipSpeed = int(optref.arcademode.bArcadeShipSpeed);
	bArcadeCannonsReload = int(optref.arcademode.bArcadeCannonsReload);
	bArcadeCannonsAccuracy = int(optref.arcademode.bArcadeCannonsAccuracy);
	bArcadeFencingAI = int(optref.arcademode.bArcadeFencingAI);
	bArcadeFencingDamage = int(optref.arcademode.bArcadeFencingDamage);
	bArcadeFencingEquip = int(optref.arcademode.bArcadeFencingEquip);
	bArcadeSailTo = int(optref.arcademode.bArcadeSailTo);
	*/
	locCameraEnableSpecialMode = !int(optref.cameramode.follow_on);
	
	/*
	SeaMaxVertices
	SeaMaxIndices
	SeaGridStep
	SeaMaxWaveDistance
	*/
	if( CheckAttribute(optref,"cameramode.ClassicSoundScene") ) {
		InterfaceStates.ClassicSoundScene = optref.cameramode.ClassicSoundScene;
	} else {
		InterfaceStates.ClassicSoundScene = true;
	}

	if( CheckAttribute(optref,"cameramode.SFW") ) {
		bSFW = bool(optref.cameramode.SFW);
		InterfaceStates.SFW = bSFW;
	} else {
		InterfaceStates.SFW = false;
	}

	if( CheckAttribute(optref,"cameramode.ShowBattleMode") ) {
		InterfaceStates.ShowBattleMode = optref.cameramode.ShowBattleMode;
	} else {
		InterfaceStates.ShowBattleMode = true;
	}

	if( CheckAttribute(optref,"cameramode.ShowCharString") ) {
		InterfaceStates.ShowCharString = optref.cameramode.ShowCharString;
	} else {
		InterfaceStates.ShowCharString = true;
	}

	if( CheckAttribute(optref,"cameramode.ShowTutorial") ) {
		InterfaceStates.ShowTutorial = optref.cameramode.ShowTutorial;
	} else {
		InterfaceStates.ShowTutorial = true;
	}
	
	// автосейвы
	string sAutoSave;
	for(int i = 0; i < 13; i++)
	{
		sAutoSave = "AutoSave_" + GetAutoSaveType(i);
		if(CheckAttribute(optref, sAutoSave))
			InterfaceStates.(sAutoSave) = int(optref.(sAutoSave));
		else
			InterfaceStates.(sAutoSave) = -1;
	}

	if( CheckAttribute(optref,"cameramode.EnabledQuestsMarks") ) {
		InterfaceStates.EnabledQuestsMarks = optref.cameramode.EnabledQuestsMarks;
	} else {
		InterfaceStates.EnabledQuestsMarks = true;
	}

	if( CheckAttribute(optref,"cameramode.EnabledShipMarks") ) {
		InterfaceStates.EnabledShipMarks = optref.cameramode.EnabledShipMarks;
	} else {
		InterfaceStates.EnabledShipMarks = 1;
	}

	if( CheckAttribute(optref,"cameramode.SimpleSeaMode") ) {
		InterfaceStates.SimpleSea = optref.cameramode.SimpleSeaMode;
	} else {
		InterfaceStates.SimpleSea = false;
	}
	
	if( CheckAttribute(optref,"cameramode.CREWONDECKMode") ) {
		InterfaceStates.CREWONDECK = optref.cameramode.CREWONDECKMode;
	} else {
		InterfaceStates.CREWONDECK = true; // заполнить чекбокс
	}
	
	if( CheckAttribute(optref,"cameramode.ROTATESKYMode") ) {
		InterfaceStates.ROTATESKY = optref.cameramode.ROTATESKYMode;
	} else {
		InterfaceStates.ROTATESKY = false;
	}

	if( CheckAttribute(optref,"cameramode.DYNAMICLIGHTSMode") ) {
		InterfaceStates.DYNAMICLIGHTS = optref.cameramode.DYNAMICLIGHTSMode;
	} else {
		InterfaceStates.DYNAMICLIGHTS = true;
	}

	// mouse
	if( CheckAttribute(optref,"cameramode.InvertCameras") ) {
		InterfaceStates.InvertCameras = optref.cameramode.InvertCameras;
	} else {
		InterfaceStates.InvertCameras = false;
	}

	if( CheckAttribute(optref,"mouse.loc_sensitivity") ) {
		InterfaceStates.mouse.loc_sens = optref.mouse.loc_sensitivity;
	} else {
		InterfaceStates.mouse.loc_sens = 0.5;
	}

	if( CheckAttribute(optref,"mouse.sea_sensitivity") ) {
		InterfaceStates.mouse.sea_sens = optref.mouse.sea_sensitivity;
	} else {
		InterfaceStates.mouse.sea_sens = 0.5;
	}
	// video colors
	if( CheckAttribute(optref,"video.contrast") ) {
		InterfaceStates.video.contrast = optref.video.contrast;
	} else {
		InterfaceStates.video.contrast = 1.0;
	}

	if( CheckAttribute(optref,"video.gamma") ) {
		InterfaceStates.video.gamma = optref.video.gamma;
	} else {
		InterfaceStates.video.gamma = 1.0;
	}

	if( CheckAttribute(optref,"video.brightness") ) {
		InterfaceStates.video.brightness = optref.video.brightness;
	} else {
		InterfaceStates.video.brightness = 0.0;
	}
	
	// Warship 07.07.09 Эффект свечения
	if(CheckAttribute(optref, "GlowEffect"))
	{
		InterfaceStates.GlowEffect = optref.GlowEffect;
	} else {
		InterfaceStates.GlowEffect = 0;
	}
	
	SetGlowParams(1.0, int(InterfaceStates.GlowEffect), 2);
	
	if( CheckAttribute(optref,"video.grassquality") ) {
		iGrassQuality = int(optref.video.grassquality);
	} else {
		iGrassQuality = 0;
	}

	if( CheckAttribute(optref,"ifov") ) {
		InterfaceStates.Fov = int(optref.ifov);
		Render.CorrectFov = int(InterfaceStates.Fov);
	} else {
		InterfaceStates.Fov = 1;
	}

	if( CheckAttribute(optref,"ifonttype") ) {
		InterfaceStates.FontType = int(optref.ifonttype);
	} else {
		InterfaceStates.FontType = 0;
	}

	if( CheckAttribute(optref,"imoreinfo") ) {
		InterfaceStates.MoreInfo = int(optref.imoreinfo);
	} else {
		InterfaceStates.MoreInfo = 0;
	}

	if( CheckAttribute(optref,"icontrolsmode") ) {
		InterfaceStates.ControlsMode = int(optref.icontrolsmode);
	} else {
		InterfaceStates.ControlsMode = 0;
	}

	if( CheckAttribute(optref,"icompasspos") ) {
		InterfaceStates.CompassPos = int(optref.icompasspos);
	} else {
		InterfaceStates.CompassPos = 0;
	}

	if( CheckAttribute(optref,"icontrolstips") ) {
		InterfaceStates.ControlsTips = int(optref.icontrolstips);
	} else {
		InterfaceStates.ControlsTips = 2;
	}

	if( CheckAttribute(optref,"ihelptime") ) {
		iGlobalHelpTime = int(optref.ihelptime);
		InterfaceStates.HelpTime = iGlobalHelpTime;
	} else {
		InterfaceStates.HelpTime = 1;
	}

	if( CheckAttribute(optref,"icamera") ) {
		iGlobalCamera = int(optref.icamera);
		InterfaceStates.Camera = iGlobalCamera;
	} else {
		InterfaceStates.Camera = 1;
	}

	if( CheckAttribute(optref,"ienemytype") ) {
		iGlobalEnemyType = int(optref.ienemytype);
		InterfaceStates.EnemyType = iGlobalEnemyType;
	} else {
		InterfaceStates.EnemyType = 1;
	}

	if( CheckAttribute(optref,"itarget") ) {
		iGlobalTarget = int(optref.itarget);
		InterfaceStates.Target = iGlobalTarget;
	} else {
		InterfaceStates.Target = 2;
	}
	
	if( CheckAttribute(optref,"ivisualscheme") ) {
		iVisualScheme = int(optref.ivisualscheme);
		InterfaceStates.VisualScheme = iVisualScheme;
	} else {
		InterfaceStates.VisualScheme = 2;
	}
	
	if( CheckAttribute(optref,"idialogscale") ) {
		iDialogScale = int(optref.idialogscale);
		InterfaceStates.DialogScale = iDialogScale;
	} else {
		InterfaceStates.DialogScale = 2;
	}
	
	if( CheckAttribute(optref,"ibestcourse") ) {
		iBestCourse = int(optref.ibestcourse);
		InterfaceStates.BestCourse = iBestCourse;
	} else {
		InterfaceStates.BestCourse = 2;
	}

	if( CheckAttribute(optref,"seadetails") ) {
		InterfaceStates.SeaDetails = float(optref.seadetails);
	}

	if( CheckAttribute(optref,"FoliageDrawDistance") ) {
		if (int(optref.FoliageDrawDistance)>3000) InterfaceStates.FoliageDrawDistance = 3000;
		else InterfaceStates.FoliageDrawDistance = float(optref.FoliageDrawDistance);
	} else {
		InterfaceStates.FoliageDrawDistance = 1000;
	}

	if( CheckAttribute(optref,"GrassDrawDistance") ) {
		InterfaceStates.GrassDrawDistance = float(optref.GrassDrawDistance);
	} else {
		InterfaceStates.GrassDrawDistance = 50;
	}

	XI_SetColorCorrection(float(InterfaceStates.video.contrast),float(InterfaceStates.video.gamma),float(InterfaceStates.video.brightness));

	aref arControls;
	makearef(arControls,optref.controls);
	RestoreKeysFromOptions(arControls);

	// always run
	if( CheckAttribute(&optref,"alwaysrun") ) {
		InterfaceStates.alwaysrun = optref.alwaysrun;
	} else {
		InterfaceStates.alwaysrun = false;
	}
	// advancedchange
	if( CheckAttribute(&optref,"AdvancedChange") ) {
		InterfaceStates.AdvancedChange = optref.AdvancedChange;
	} else {
		InterfaceStates.AdvancedChange = false;
	}

	ControlsMakeInvert();
	SetRealMouseSensitivity();
}

// belamour legendary edition теперь пишется все в один общий файл, а в option_screen.c сбрысывается в дефолт
void ReadSavedOptions(ref gopt)
{
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_LOADOPTIONS, "options", gopt);
}

void SaveSavedOptions(ref gopt)
{
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_SAVEOPTIONS, "options", gopt);
}

//старые опции
// void ReadSavedOptions(ref gopt)
// {
	// string sFileName = "options";
	// if( CheckAttribute(&PlayerProfile,"name") && PlayerProfile.name!="" ) {
		// sFileName = "save\"+PlayerProfile.name+"\options\options";
	// }
	// SendMessage(&GameInterface, "lsa", MSG_INTERFACE_LOADOPTIONS, sFileName, gopt);
// }

// void SaveSavedOptions(ref gopt)
// {
	// string sFileName = "options";
	// if( CheckAttribute(&PlayerProfile,"name") && PlayerProfile.name!="" ) {
		// sFileName = "save\"+PlayerProfile.name+"\options\options";
	// }
	// SendMessage(&GameInterface, "lsa", MSG_INTERFACE_SAVEOPTIONS, sFileName, gopt);
// }

void GetControlsOptions(ref optref)
{
	int ng,qg, nc,qc;
	aref arIn, arOut, arGrp, arCntrl;
	string grName, cntrlName;

	makearef(arOut,objControlsState.keygroups);
	optref.controls = true;
	makearef(arIn,optref.controls);

	qg = GetAttributesNum(arOut);
	for(ng=0; ng<qg; ng++)
	{
		arGrp = GetAttributeN(arOut,ng);
		grName = GetAttributeName(arGrp);
		if( CheckAttribute(&objControlsState,"grouplist."+grName) && int(objControlsState.grouplist.(grName))==true )
		{
			qc = GetAttributesNum(arGrp);
			for(nc=0; nc<qc; nc++)
			{
				arCntrl = GetAttributeN(arGrp,nc);
				cntrlName = GetAttributeName(arCntrl);
				arIn.(grName).(cntrlName) = GetAttributeValue(arCntrl);
				arIn.(grName).(cntrlName).state = arCntrl.state;
				arIn.(grName).(cntrlName).remapping = arCntrl.remapping;
			}
		}
	}
}
