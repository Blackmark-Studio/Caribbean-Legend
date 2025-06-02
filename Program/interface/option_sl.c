
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
	optref.ifonttype = 0;
	optref.imoreinfo = 0;
	optref.icontrolsmode = 0;
	optref.icompasspos = 0;
	optref.icontrolstips = 2;
	optref.iarcadesails = 1;
	optref.FoliageDrawDistance = 1000;
	optref.GrassDrawDistance = 50;
	
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

	ftmp1 = stf(optref.volume.sound);
	ftmp2 = stf(optref.volume.music);
	ftmp3 = stf(optref.volume.dialog);
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
	if( CheckAttribute(&InterfaceStates,"FontType") ) {
		optref.ifonttype = sti(InterfaceStates.FontType);
	} else {
		optref.ifonttype = 0;
	}

	if( CheckAttribute(&InterfaceStates,"MoreInfo") ) {
		optref.imoreinfo = sti(InterfaceStates.MoreInfo);
	} else {
		optref.imoreinfo = 0;
	}

	if( CheckAttribute(&InterfaceStates,"ControlsMode") ) {
		optref.icontrolsmode = sti(InterfaceStates.ControlsMode);
	} else {
		optref.icontrolsmode = 0;
	}

	if( CheckAttribute(&InterfaceStates,"CompassPos") ) {
		optref.icompasspos = sti(InterfaceStates.CompassPos);
	} else {
		optref.icompasspos = 0;
	}

	if( CheckAttribute(&InterfaceStates,"ControlsTips") ) {
		optref.icontrolstips = sti(InterfaceStates.ControlsTips);
	} else {
		optref.icontrolstips = 2;
	}

	if( CheckAttribute(&InterfaceStates,"ArcadeSails") ) {
		optref.iarcadesails = sti(InterfaceStates.ArcadeSails);
	} else {
		optref.iarcadesails = 1;
	}
	
	if( CheckAttribute(&InterfaceStates,"SeaDetails") ) {
		optref.seadetails = stf(InterfaceStates.SeaDetails);
	}

	if( CheckAttribute(&InterfaceStates,"FoliageDrawDistance") ) {
		if (sti(optref.FoliageDrawDistance)>3000) optref.FoliageDrawDistance = 3000;
		else optref.FoliageDrawDistance = stf(InterfaceStates.FoliageDrawDistance);
	} else {
		optref.FoliageDrawDistance = 1000;
	}

	if( CheckAttribute(&InterfaceStates,"GrassDrawDistance") ) {
		optref.GrassDrawDistance = stf(InterfaceStates.GrassDrawDistance);
	} else {
		optref.GrassDrawDistance = 50;
	}

	if( CheckAttribute(&InterfaceStates,"ClassicSoundScene") ) {
		optref.cameramode.ClassicSoundScene = sti(InterfaceStates.ClassicSoundScene);
	} else {
		optref.cameramode.ClassicSoundScene = true;
	}

	if( CheckAttribute(&InterfaceStates,"InvertCameras") ) {
		optref.cameramode.InvertCameras = sti(InterfaceStates.InvertCameras);
	} else {
		optref.cameramode.InvertCameras = false;
	}

	if( CheckAttribute(&InterfaceStates,"ShowBattleMode") ) {
		optref.cameramode.ShowBattleMode = sti(InterfaceStates.ShowBattleMode);
	} else {
		optref.cameramode.ShowBattleMode = true;
	}

	if( CheckAttribute(&InterfaceStates,"ShowStealthAlarm") ) {
		optref.cameramode.ShowStealthAlarm = sti(InterfaceStates.ShowStealthAlarm);
	} else {
		optref.cameramode.ShowStealthAlarm = true;
	}
	
	if( CheckAttribute(&InterfaceStates,"ShowCharString") ) {
		optref.cameramode.ShowCharString = sti(InterfaceStates.ShowCharString);
	} else {
		optref.cameramode.ShowCharString = true;
	}

	if( CheckAttribute(&InterfaceStates,"ShowTutorial") ) {
		optref.cameramode.ShowTutorial = sti(InterfaceStates.ShowTutorial);
	} else {
		optref.cameramode.ShowTutorial = true;
	}

	if( CheckAttribute(&InterfaceStates,"EnabledAutoSaveMode") ) {
		optref.cameramode.EnabledAutoSaveMode = sti(InterfaceStates.EnabledAutoSaveMode);
	} else {
		optref.cameramode.EnabledAutoSaveMode = true;
	}

	if( CheckAttribute(&InterfaceStates,"EnabledAutoSaveMode2") ) {
		optref.cameramode.EnabledAutoSaveMode2 = sti(InterfaceStates.EnabledAutoSaveMode2);
	} else {
		optref.cameramode.EnabledAutoSaveMode2 = false;
	}

	if( CheckAttribute(&InterfaceStates,"EnabledQuestsMarks") ) {
		optref.cameramode.EnabledQuestsMarks = sti(InterfaceStates.EnabledQuestsMarks);
	} else {
		optref.cameramode.EnabledQuestsMarks = true;
	}

	if( CheckAttribute(&InterfaceStates,"EnabledShipMarks") ) {
		optref.cameramode.EnabledShipMarks = sti(InterfaceStates.EnabledShipMarks);
	} else {
		optref.cameramode.EnabledShipMarks = 1;
	}
	if (sti(optref.cameramode.EnabledShipMarks)>0) bDrawBars = 1;
	else bDrawBars = sti(optref.cameramode.EnabledShipMarks);

	if( CheckAttribute(&InterfaceStates,"SimpleSea") ) {
		optref.cameramode.SimpleSeaMode = sti(InterfaceStates.SimpleSea);
	} else {
		optref.cameramode.SimpleSeaMode = true;
	}
	// belamour -->
	if( CheckAttribute(&InterfaceStates,"DIRECTSAIL") ) {
		optref.cameramode.DIRECTSAILMode = sti(InterfaceStates.DIRECTSAIL);
	} else {
		optref.cameramode.DIRECTSAILMode = false;
	}
	
	if( CheckAttribute(&InterfaceStates,"CREWONDECK") ) {
		optref.cameramode.CREWONDECKMode = sti(InterfaceStates.CREWONDECK);
	} else {
		optref.cameramode.CREWONDECKMode = true;
	}

	if( CheckAttribute(&InterfaceStates,"ENHANCEDSAILING") ) {
		optref.cameramode.ENHANCEDSAILINGMode = sti(InterfaceStates.ENHANCEDSAILING);
	} else {
		optref.cameramode.ENHANCEDSAILINGMode = false;
	}
	
	if( CheckAttribute(&InterfaceStates,"ROTATESKY") ) {
		optref.cameramode.ROTATESKYMode = sti(InterfaceStates.ROTATESKY);
	} else {
		optref.cameramode.ROTATESKYMode = false;
	}
	if( CheckAttribute(&InterfaceStates,"DYNAMICLIGHTS") ) {
		optref.cameramode.DYNAMICLIGHTSMode = sti(InterfaceStates.DYNAMICLIGHTS);
	} else {
		optref.cameramode.DYNAMICLIGHTSMode = true;
	}
	// <-- belamour
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
	// belamour перспектива морской камеры
	if(CheckAttribute(&InterfaceStates, "SEACAMPERSP")) optref.SEACAMPERSP = InterfaceStates.SEACAMPERSP;
	else optref.SEACAMPERSP = 25;

	// belamour legendary edition информация о текущем профиле
	if(CheckAttribute(&PlayerProfile,"name")) 
		optref.StartGameParam.PlayerProfile  = PlayerProfile.name;

}

void SetCurentOptions(ref optref)
{
	SendMessage(&sound,"lfff", MSG_SOUND_SET_MASTER_VOLUME, stf(optref.volume.sound),	stf(optref.volume.music),	stf(optref.volume.dialog));

	/*bArcadeSails = sti(optref.arcademode.bArcadeSails);
	bArcadeShipSpeed = sti(optref.arcademode.bArcadeShipSpeed);
	bArcadeCannonsReload = sti(optref.arcademode.bArcadeCannonsReload);
	bArcadeCannonsAccuracy = sti(optref.arcademode.bArcadeCannonsAccuracy);
	bArcadeFencingAI = sti(optref.arcademode.bArcadeFencingAI);
	bArcadeFencingDamage = sti(optref.arcademode.bArcadeFencingDamage);
	bArcadeFencingEquip = sti(optref.arcademode.bArcadeFencingEquip);
	bArcadeSailTo = sti(optref.arcademode.bArcadeSailTo);
	*/
	locCameraEnableSpecialMode = !sti(optref.cameramode.follow_on);
	
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

	if( CheckAttribute(optref,"cameramode.ShowBattleMode") ) {
		InterfaceStates.ShowBattleMode = optref.cameramode.ShowBattleMode;
	} else {
		InterfaceStates.ShowBattleMode = true;
	}

	if( CheckAttribute(optref,"cameramode.ShowStealthAlarm") ) {
		InterfaceStates.ShowStealthAlarm = optref.cameramode.ShowStealthAlarm;
	} else {
		InterfaceStates.ShowStealthAlarm = true;
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

	if( CheckAttribute(optref,"cameramode.EnabledAutoSaveMode") ) {
		InterfaceStates.EnabledAutoSaveMode = optref.cameramode.EnabledAutoSaveMode;
	} else {
		InterfaceStates.EnabledAutoSaveMode = true;
	}

	if( CheckAttribute(optref,"cameramode.EnabledAutoSaveMode2") ) {
		InterfaceStates.EnabledAutoSaveMode2 = optref.cameramode.EnabledAutoSaveMode2;
	} else {
		InterfaceStates.EnabledAutoSaveMode2 = false;
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
	// belamour
	if( CheckAttribute(optref,"cameramode.DIRECTSAILMode") ) {
		InterfaceStates.DIRECTSAIL = optref.cameramode.DIRECTSAILMode;
	} else {
		InterfaceStates.DIRECTSAIL = false;
	}
	
	if( CheckAttribute(optref,"cameramode.CREWONDECKMode") ) {
		InterfaceStates.CREWONDECK = optref.cameramode.CREWONDECKMode;
	} else {
		InterfaceStates.CREWONDECK = true; // заполнить чекбокс
	}
	
	if( CheckAttribute(optref,"cameramode.ENHANCEDSAILINGMode") ) {
		InterfaceStates.ENHANCEDSAILING = optref.cameramode.ENHANCEDSAILINGMode;
	} else {
		InterfaceStates.ENHANCEDSAILING = false;
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
	
	SetGlowParams(1.0, sti(InterfaceStates.GlowEffect), 2);
	
	if( CheckAttribute(optref,"video.grassquality") ) {
		iGrassQuality = sti(optref.video.grassquality);
	} else {
		iGrassQuality = 0;
	}
	if( CheckAttribute(optref,"ifonttype") ) {
		InterfaceStates.FontType = sti(optref.ifonttype);
	} else {
		InterfaceStates.FontType = 0;
	}

	if( CheckAttribute(optref,"imoreinfo") ) {
		InterfaceStates.MoreInfo = sti(optref.imoreinfo);
	} else {
		InterfaceStates.MoreInfo = 0;
	}

	if( CheckAttribute(optref,"icontrolsmode") ) {
		InterfaceStates.ControlsMode = sti(optref.icontrolsmode);
	} else {
		InterfaceStates.ControlsMode = 0;
	}

	if( CheckAttribute(optref,"icompasspos") ) {
		InterfaceStates.CompassPos = sti(optref.icompasspos);
	} else {
		InterfaceStates.CompassPos = 0;
	}

	if( CheckAttribute(optref,"icontrolstips") ) {
		InterfaceStates.ControlsTips = sti(optref.icontrolstips);
	} else {
		InterfaceStates.ControlsTips = 2;
	}

	if( CheckAttribute(optref,"iarcadesails") ) {
		InterfaceStates.ArcadeSails = sti(optref.iarcadesails);
	} else {
		InterfaceStates.ArcadeSails = 1;
	}		

	if( CheckAttribute(optref,"seadetails") ) {
		InterfaceStates.SeaDetails = stf(optref.seadetails);
	}

	if( CheckAttribute(optref,"FoliageDrawDistance") ) {
		if (sti(optref.FoliageDrawDistance)>3000) InterfaceStates.FoliageDrawDistance = 3000;
		else InterfaceStates.FoliageDrawDistance = stf(optref.FoliageDrawDistance);
	} else {
		InterfaceStates.FoliageDrawDistance = 1000;
	}

	if( CheckAttribute(optref,"GrassDrawDistance") ) {
		InterfaceStates.GrassDrawDistance = stf(optref.GrassDrawDistance);
	} else {
		InterfaceStates.GrassDrawDistance = 50;
	}

	XI_SetColorCorrection(stf(InterfaceStates.video.contrast),stf(InterfaceStates.video.gamma),stf(InterfaceStates.video.brightness));

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
	// belamour перспектива морской камеры
	if(CheckAttribute(optref, "SEACAMPERSP"))
	{
		InterfaceStates.SEACAMPERSP = optref.SEACAMPERSP;
	}
	else
	{
		InterfaceStates.SEACAMPERSP = 25;
	}
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
		if( CheckAttribute(&objControlsState,"grouplist."+grName) && sti(objControlsState.grouplist.(grName))==true )
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