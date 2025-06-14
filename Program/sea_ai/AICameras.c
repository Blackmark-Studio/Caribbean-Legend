bool bSeePeoplesOnDeck = false; // Warship 08.06.09 видеть матросов на палубе при виде от первого лица или нет

// ugeen 13.09.20
#define DEFAULT_CAM_PERSP 				1.285
#define DEFAULT_CAM_PERSP_DEN 			1.25

object	SeaCameras;
aref	Crosshair;
object	SeaShipCamera, SeaFreeCamera, SeaDeckCamera, SeaFireCamera;
ref		SeaShipCharacterForCamera;
bool	bCanSwitchCameras = true;

void DeleteSeaCamerasEnvironment()
{
	DeleteClass(&SeaCameras);
	DeleteClass(&SeaFreeCamera);
	DeleteClass(&SeaShipCamera);
	DeleteClass(&SeaDeckCamera);
	DeleteClass(&SeaFireCamera);
	DelEventHandler("SeaCameras_Switch", "SeaCameras_Switch");
	DelEventHandler(TELESCOPE_ACTIVE, "SeaCameras_TelescopeActive");
}

void SetPerspectiveSettings()
{
    float fCamPersp = CalcSeaPerspective();

    SeaFreeCamera.Perspective = fCamPersp;
	SeaShipCamera.Perspective = fCamPersp;
}

float CalcSeaPerspective()
{
    float fCamPerspAdj = 0.0;
    //fCamPerspAdj = SEA_CAM_PERSP / DEFAULT_CAM_PERSP_DEN;
	// belamour
	float fSCP = sti(InterfaceStates.SEACAMPERSP)/100.0;
	fCamPerspAdj = fSCP / DEFAULT_CAM_PERSP_DEN;
    return (DEFAULT_CAM_PERSP + fCamPerspAdj);
}

void CreateSeaCamerasEnvironment()
{
	bCanSwitchCameras = true;

	CreateEntity(&SeaCameras, "SEA_CAMERAS");
	CreateEntity(&SeaFreeCamera, "FREE_CAMERA");
	CreateEntity(&SeaShipCamera, "SHIP_CAMERA");
	CreateEntity(&SeaDeckCamera, "DECK_CAMERA");
	CreateEntity(&SeaFireCamera, "FIRE_CAMERA");

	//LayerAddObject("system_messages", &SeaCameras, 1);
	LayerAddObject(SEA_EXECUTE, &SeaShipCamera, iShipPriorityExecute + 5);
	LayerAddObject(SEA_EXECUTE, &SeaFreeCamera, 1);
	LayerAddObject(SEA_EXECUTE, &SeaDeckCamera, iShipPriorityExecute + 5);
	LayerAddObject(SEA_EXECUTE, &SeaFireCamera, iShipPriorityExecute + 5);
	
	SetPerspectiveSettings();

	//SeaFreeCamera.Perspective = 1.285;

	// Ship camera paramerets
	//SeaShipCamera.Perspective = 1.285;
	SeaShipCamera.SensivityDistance = 5.0;
	SeaShipCamera.SensivityHeightAngle = 0.02;
	SeaShipCamera.SensivityHeightAngleOnShip = 0.005;
	SeaShipCamera.SensivityAzimuthAngle = 0.04;
	SeaShipCamera.MaxAngleX = 0.07;
	SeaShipCamera.MinAngleX = -1.4;
	SeaShipCamera.Distance = 70.0;
	SeaShipCamera.MinDistance = 5.0;
	SeaShipCamera.MaxDistance = 1500.0; //90.0;
	SeaShipCamera.MinHeightOnSea = 1.0;
//	SeaShipCamera.MaxHeightOnShip = 16.0;
	SeaShipCamera.MaxHeightOnShip = 5.0;
	SeaShipCamera.InvertMouseX = 1.0;
	SeaShipCamera.InvertMouseY = -1.0;
	SeaShipCamera.kBoxSizeX = 0.5;
	SeaShipCamera.kBoxSizeY = 1.6;
	SeaShipCamera.kBoxSizeZ = 0.8;
	
	// Deck camera paramerets
	// SeaDeckCamera.Perspective = 1.285;
	SeaDeckCamera.Perspective = 1.185;
	SeaDeckCamera.SensivityDistance = 0.01;
	SeaDeckCamera.SensivityHeightAngle = 0.0015;
	SeaDeckCamera.SensivityAzimuthAngle = 0.0015;
	SeaDeckCamera.StepUp = 0.5;
	SeaDeckCamera.StepMin = 0.01;
	SeaDeckCamera.h_max = 2.0;
	SeaDeckCamera.h_min = 0.5;
	SeaDeckCamera.h_step = 0.1;
	SeaDeckCamera.h_def = 1.6;
	SeaDeckCamera.MaxAngleX = 0.7;
	SeaDeckCamera.MinAngleX = -1.3;
	SeaDeckCamera.RockingX = 0.5;
	SeaDeckCamera.RockingZ = 0.5;
	
	// evganat - атрибуты SeaFireCamera
	SeaFireCamera.Perspective = 1.185;
	SeaFireCamera.SensivityDistance = 0.01;
	SeaFireCamera.SensivityHeightAngle = 0.0015;
	SeaFireCamera.SensivityAzimuthAngle = 0.0015;
	SeaFireCamera.MaxAngleX = 0.3;
	SeaFireCamera.MinAngleX = -0.3;
	SeaFireCamera.RockingX = 0.5;
	SeaFireCamera.RockingZ = 0.5;
	SeaFireCamera.MouseSpeedAy = 0.8;

	makearef(Crosshair,SeaCameras.Crosshair);

	if (!bSeaLoad)
	{
		SeaCameras.Camera = "SeaShipCamera";
	
		Crosshair.OutsideCamera = true;
	}

	
/*	Crosshair.Colors.Default = argb(128, 230, 220, 150);
	Crosshair.Colors.Enemy = argb(128, 255, 0, 0);
	Crosshair.Colors.Friend = argb(128, 0, 255, 0);
	Crosshair.Colors.Neutral = argb(128, 128, 128, 128);	*/
	
	//кружки
	Crosshair.Texture = "interfaces\le\battle_interface\crossballs.tga";
	Crosshair.Technique = "battle_tex_col_Rectangle";
	Crosshair.SubTexX = 2;
	Crosshair.SubTexY = 2;
	Crosshair.Colors.Normal = argb(190, 228, 200, 154);
	Crosshair.Colors.Uncharged = argb(140, 106, 27, 27);
	Crosshair.Colors.Damaged = argb(125, 80, 0, 0);
	Crosshair.Colors.Center = argb(210, 139, 45, 45);
	Crosshair.Colors.TargetNeutral = argb(120, 180, 160, 140);
	Crosshair.Colors.TargetFriend = argb(120, 80, 220, 80);
	Crosshair.Colors.TargetEnemy = argb(120, 220, 80, 80);
	
	Crosshair.TargetSize = 0.75;
	
	Crosshair.CrosshairSizeMin = 1.0;
	Crosshair.CrosshairSizeMaxDefault = 8.0;
	Crosshair.CrosshairSizeMaxSpyglass = 4.0;
	
	Crosshair.CrosshairSizeMax = Crosshair.CrosshairSizeMaxDefault;
	
	// стартовая координата мыши (дистанция)
	Crosshair.StartMouseDist = -140.0;

	//флуктуации - пороги
	Crosshair.MaxDeltaDist = 2.5; //порог для начала флуктуации, считывается за 1 кадр.
	Crosshair.MaxDeltaAy = 0.007;
	Crosshair.MaxDeltaHeight = 2.0;
	
	Crosshair.TargetDeltaDist = 0.01;
	Crosshair.TargetBoxIncreaseWidth = 2.2;
	Crosshair.TargetBoxIncreaseLength = 1.8;

	SendMessage(&AISea, "la", AI_MESSAGE_SET_CAMERAS_ATTRIBUTE, &SeaCameras);

	SetEventHandler("SeaCameras_Switch", "SeaCameras_Switch", 1);
	SetEventHandler(TELESCOPE_ACTIVE, "SeaCameras_TelescopeActive", 0);

	// add cameras to list
	SendMessage(&SeaCameras, "li", AI_CAMERAS_ADD_CAMERA, &SeaShipCamera);
	SendMessage(&SeaCameras, "li", AI_CAMERAS_ADD_CAMERA, &SeaFreeCamera);
	SendMessage(&SeaCameras, "li", AI_CAMERAS_ADD_CAMERA, &SeaDeckCamera);
	SendMessage(&SeaCameras, "li", AI_CAMERAS_ADD_CAMERA, &SeaFireCamera);
}

void SeaCameras_TelescopeActive()
{
	int iTelescopeActive = GetEventData();
	if (iTelescopeActive)
	{
		bCanSwitchCameras = false;
		Crosshair.CrosshairSizeMax = Crosshair.CrosshairSizeMaxSpyglass;
	}
	else
	{
		bCanSwitchCameras = true;
		Crosshair.CrosshairSizeMax = Crosshair.CrosshairSizeMaxDefault;
	}
}

void SeaCameras_Switch()
{
	if (!bCanSwitchCameras) return;

	int bSwitch = false;
	
	// Коммент - выбираем состояние, ИЗ КОТОРОГО ПЕРЕКЛЮЧАЕМСЯ
	// Sailors.IsOnDeck = 1; - Флаг, находимя ли мы на палубе
	// если Sailors.IsOnDeck == 1, значит, мы на палубе, и матросов бегающих мы не увидем
	switch (SeaCameras.Camera)
	{
		case "SeaFreeCamera":
			SeaCameras.Camera = "SeaShipCamera";
			Crosshair.OutsideCamera = true;
			Sailors.IsOnDeck = 0;
			bSwitch = true;
		break;
		case "SeaDeckCamera":
			//SeaCameras.Camera = "SeaFreeCamera"; break;		// Debug : SeaFreeCamera, release : SeaShipCamera
			SeaCameras.Camera = "SeaShipCamera"; 
			// boal -->
			if (locCameraEnableFree)
            {
			    SeaCameras.Camera = "SeaFreeCamera";
			}
			// boal <--
			Crosshair.OutsideCamera = true;
			Sailors.IsOnDeck = 0;
			bSwitch = true;
		break;
		case "SeaShipCamera":
			if (!LAi_IsDead(&Characters[nMainCharacterIndex]))
			{
				SeaCameras.Camera = "SeaDeckCamera";
				Crosshair.OutsideCamera = true;//CrosshairHidden(); // was false;  LDH 17Jan17
//				Sailors.IsOnDeck = !bSeePeoplesOnDeck;
				Sailors.IsOnDeck = !sti(InterfaceStates.CREWONDECK); //  belamour !CREW_ON_DECK; // LDH 15Jan17 show crew on deck
				bSwitch = true;
			}
		break;
	}
	if (bSwitch) SeaCameras_UpdateCamera();
}

void SeaCameras_SetFireCamera()
{
	if(!bCanSwitchCameras)
		return;

	if(SeaCameras.Camera == "SeaFreeCamera")
		return;
	
	if(SeaCameras.Camera != "SeaFireCamera")
	{
		float fAng = 0.0;
		SeaFireCamera.LastCamera = SeaCameras.Camera;
		SeaCameras.Camera = "SeaFireCamera";
		Crosshair.OutsideCamera = false;
		Sailors.IsOnDeck = 1;
	}
	else
	{
		if(!CheckAttribute(SeaFireCamera, "LastCamera"))
			SeaFireCamera.LastCamera = "SeaShipCamera";
		SeaCameras.Camera = SeaFireCamera.LastCamera;
		Crosshair.OutsideCamera = true;
		if(SeaCameras.Camera == "SeaShipCamera")
			Sailors.IsOnDeck = !sti(InterfaceStates.CREWONDECK);
		else
			Sailors.IsOnDeck = 0;
	}
	
	SeaCameras_UpdateCamera();
}

void SeaCameras_SetShipCameraAy(float ay)
{
	TEV.ShipCameraAy = Degree2Radian(ay);
}

void SeaCameras_UpdateCamera()
{
	switch (SeaCameras.Camera)
	{
		case "SeaShipCamera":
			SendMessage(&SeaCameras, "lia", AI_CAMERAS_SET_CAMERA, &SeaShipCamera, &SeaShipCharacterForCamera);
			if(CheckAttribute(&TEV, "ShipCameraAy"))
			{
				SendMessage(&SeaShipCamera, "lf", MSG_SHIP_CAMERA_SET_AY, stf(TEV.ShipCameraAy));
				DeleteAttribute(&TEV, "ShipCameraAy");
			}
			
			// TUTOR-ВСТАВКА
			if(TW_IsActive() && objTask.sea_battle == "4_AimingFire")
			{
				TW_ColorWeak(TW_GetTextARef("AimingFire_exit"));
				TW_FinishSea_Battle_2_AimingFire();
			}
		break;
		case "SeaFreeCamera":
			SendMessage(&SeaCameras, "lia", AI_CAMERAS_SET_CAMERA, &SeaFreeCamera, &SeaShipCharacterForCamera);
		break;
		case "SeaDeckCamera":
			SendMessage(&SeaCameras, "lia", AI_CAMERAS_SET_CAMERA, &SeaDeckCamera, &SeaShipCharacterForCamera);
		break;
		case "SeaFireCamera":
			string sBort = "";
			float fAng = 0.0;
			GetFireCameraBort(&sBort, &fAng);
			SeaFireCamera.Bort = sBort;
			SendMessage(&AISea, "la", AI_MESSAGE_FIRE_CAMERA_RESET, &Characters[GetMainCharacterIndex()]);
			SendMessage(&SeaCameras, "liasf", AI_CAMERAS_SET_CAMERA, &SeaFireCamera, &SeaShipCharacterForCamera, "cam_"+sBort, fAng);
			
			// TUTOR-ВСТАВКА
			if(TW_IsActive() && objTask.sea_battle == "2_AimingFire")
            {
				objTask.sea_battle = "3_AimingFire";
				TW_ColorWeak(TW_GetTextARef("AimingFire_enter"));
				string sText = StringFromKey("Tutorial_15", GKIC("Ship_Fire", "SailingFire"));
				TW_AddBottomText("AimingFire_do", sText, "Default");
				
				TW_RecalculateLayout();
            }
		break;
	}
}

void SeaCameras_SetDieCamera()
{
	bool bOldCanSwitchCameras;
	if (SeaCameras.Camera == "SeaDeckCamera" || SeaCameras.Camera == "SeaFireCamera")
	{
		SeaCameras.Camera = "SeaShipCamera";
		Crosshair.OutsideCamera = true;
		Sailors.IsOnDeck = 0;
		DeleteClass(&Telescope);
		SeaCameras_UpdateCamera();
		SendMessage(&objISpyGlass, "ll", MSG_TELESCOPE_REQUEST,0); // выключить телескоп
	}
}

bool SeaCameras_isCameraOutside()
{
	if (SeaCameras.Camera == "SeaShipCamera") return true;
	if (SeaCameras.Camera == "SeaFreeCamera") return true;
	if (SeaCameras.Camera == "SeaDeckCamera") return true;
	return false;
}

void SeaCameras_SetShipForSeaCamera(object Character)
{
	makeref(SeaShipCharacterForCamera, Character);
	SeaCameras_UpdateCamera();
}

// LDH 17Jan17 hide crosshair -->
void ToggleCrosshair()
{
    if (GetCurControlGroup() != "SailingFire") return;

    if ( ! CheckAttribute(Crosshair, "hidden")) Crosshair.hidden = 1;   // hide crosshair by default
    switch (makeint(Crosshair.hidden))
    {
        case 0:
            Crosshair.hidden = 1;           // hide the crosshair
            Crosshair.OutsideCamera = true;
        break;

        case 1:
            Crosshair.hidden = 0;           // show the crosshair
            Crosshair.OutsideCamera = false;
        break;
    }
}

bool CrosshairHidden()
{
    if ( ! CheckAttribute(Crosshair, "hidden")) Crosshair.hidden = 1;   // hide crosshair by default
    if (sti(Crosshair.hidden) == 1) return true;
    return false;
}
// LDH 17Jan17 <--

void GetFireCameraBort(ref sBort, ref fAng)
{
	float period = 3.14159265359;
//	float fAng;
	if(!CheckAttribute(SeaFireCamera, "LastCamera"))
		SeaFireCamera.LastCamera = "SeaShipCamera";
	switch(SeaFireCamera.LastCamera)
	{
		case "SeaShipCamera":
			SendMessage(&SeaShipCamera, "le", MSG_SHIP_CAMERA_GET_AY, &fAng);
			fAng += period;
		break;
		case "SeaDeckCamera":
			SendMessage(&SeaDeckCamera, "le", MSG_DECK_CAMERA_GET_AY, &fAng);
		break;
	}
	while(fAng > period)
		fAng -= 2*period;
	while(fAng < -period)
		fAng += 2*period;
	if(fAng > -period/6.0 && fAng < period/6.0)
	{
		sBort = "f";
		return;
	}
	if(fAng >= period/6.0 && fAng <= period*5.0/6.0)
	{
		sBort = "r";
		return;
	}
	if(fAng >= -period*5.0/6.0 && fAng <= -period/6.0)
	{
		sBort = "l";
		return;
	}
	sBort = "b";
	return;
}

#event_handler("GetCurBort", "GetCurBort");
string GetCurBort()
{
	if(CheckAttribute(SeaFireCamera, "Bort"))
		return "cannon" + SeaFireCamera.Bort;
	return "cannonr";
}

#event_handler("FireCamera_UpdateAttributes", "FireCamera_UpdateAttributes");
void FireCamera_UpdateAttributes()
{
	makearef(Crosshair, SeaCameras.Crosshair);
	
	float fCannons = stf(pchar.TmpSkill.Cannons);
	float fAccuracy = stf(pchar.TmpSkill.Accuracy);
	float fCrewExp = stf(GetCrewExp(pchar, "Cannoners"));
	float kCrewExp = Bring2Range(0.8, 1.2, 1.0, 100.0, fCrewExp);
	
	//скорость движения прицельных кружков
	Crosshair.DistSpeed = Bring2Range(35.0, 70.0, 0.01, 1.0, fCannons) * kCrewExp; //дистанция
	Crosshair.AySpeed = Bring2Range(0.08, 0.14, 0.01, 1.0, fCannons) * kCrewExp; //угол (горизонталь)
	Crosshair.HeightSpeed = Bring2Range(3.5, 7.0, 0.01, 1.0, fCannons) * kCrewExp; //высота
	
	//плотность сведения
	Crosshair.Density = Bring2Range(0.2, 0.65, 0.01, 1.0, fAccuracy); //0 - не сводятся, 1 - в точку.
	Crosshair.DensitySpeed = Bring2Range(0.45, 2.5, 0.01, 1.0, fAccuracy) * kCrewExp; //скорость досведения
	
	//флуктуации - коэффициенты влияния. Расчитываются на основе дельты при превышении порога
	Crosshair.FluctuationDistToDist = Bring2Range(0.003, 0.0007, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationDistToAy = Bring2Range(0.0009, 0.0003, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationDistToHeight = Bring2Range(0.00016, 0.00008, 0.01, 1.0, fAccuracy);
	
	Crosshair.FluctuationAyToDist = Bring2Range(100.0, 35.0, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationAyToAy = Bring2Range(12.5, 4.25, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationAyToHeight = Bring2Range(55.0, 25.0, 0.01, 1.0, fAccuracy);
	
	Crosshair.FluctuationHeightToDist = 0.0;
	Crosshair.FluctuationHeightToAy = Bring2Range(0.05, 0.015, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationHeightToHeight = Bring2Range(0.045, 0.007, 0.01, 1.0, fAccuracy);
}

/*
#event_handler("FireCamera_UpdateAX", "FireCamera_UpdateAX");
void FireCamera_UpdateAX()
{
	bool bCapture = GetEventData();
	float ax = GetEventData();
	if(!bCanSwitchCameras && bCapture)
		SeaFireCamera.CamAX = -ax;
	else
		SeaFireCamera.CamAX = 0.0;
}

#event_handler("GetInfo1", "GetInfo1");
void GetInfo1()
{
	string string1 = GetEventData();
	float float1 = GetEventData();
	log_info(string1 + " " + float1);
}

#event_handler("GetInfo2", "GetInfo2");
void GetInfo2()
{
	string string1 = GetEventData();
	float float1 = GetEventData();
	string string2 = GetEventData();
	float float2 = GetEventData();
	log_info(string1 + " " + float1 + ", " + string2 + " " + float2);
}

#event_handler("GetInfo3", "GetInfo3");
void GetInfo3()
{
	string string1 = GetEventData();
	float float1 = GetEventData();
	string string2 = GetEventData();
	float float2 = GetEventData();
	string string3 = GetEventData();
	float float3 = GetEventData();
	log_info(string1 + " " + float1 + ", " + string2 + " " + float2 + ", " + string3 + " " + float3);
}
*/
