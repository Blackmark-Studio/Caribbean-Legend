object Lightning;

#define WHR_LIGHTNING			"whr_lightn"
#define WHR_LIGHTNING_SOUND		"whr_lightn_snd"
#define WHR_LIGHTNING_DOIT		"whr_lightn_doit"

float fLightningScaleX,	fLightningScaleY;

void WhrDeleteLightningEnvironment()
{
    WhrStopLightning();
    
	if (isEntity(&Lightning)) 
	{ 
		DeleteClass(&Lightning);
		DeleteAttribute(&Lightning,"");
	}

//	DelEventHandler(WHR_LIGHTNING_SOUND,"Lightning_Sound");
//	DelEventHandler(WHR_LIGHTNING_DOIT, "Lightning_DoIt");
}

void WhrCreateLightningEnvironment()
{
    Whr_DebugLog("WhrCreateLightningEnvironment()");
//	aref aCurWeather = GetCurrentWeather();
//	aref aLightning; 	makearef(aLightning,aCurWeather.Lightning);
	
	DeleteAttribute(&Lightning,"");
	Lightning.Clear = "";
    Lightning.Enable = false;
	DelEventHandler(WHR_LIGHTNING_DOIT,"Lightning_DoIt");

//	if (int(aLightning.Enable) != true) return;

	if (!isEntity(&Lightning)) 
	{ 
		CreateEntity(&Lightning,"Lightning");
	}

	LayerAddObject(SEA_REFLECTION, &Lightning, 10);

/*
	SetEventHandler(WHR_LIGHTNING_SOUND,"Lightning_Sound",0);
	SetEventHandler(WHR_LIGHTNING_DOIT,"Lightning_DoIt",0);

	Lightning.Texture = Whr_GetString(aLightning,"Texture");
	Lightning.Flash.Texture = Whr_GetString(aLightning,"Flash.Texture");
	Lightning.SubTexX = Whr_GetLong(aLightning,"SubTexX");
	Lightning.SubTexY = Whr_GetLong(aLightning,"SubTexY");
	fLightningScaleX = Whr_GetFloat(aLightning,"ScaleX");
	fLightningScaleY = Whr_GetFloat(aLightning,"ScaleY");
	Lightning.isDone = "";

	PostEvent(WHR_LIGHTNING_DOIT,1000 + rand(1000));
*/    
}

void WhrStartLightning()
{
    if(CheckAttribute(&WeatherParams,"Lighting") && int(WeatherParams.Lighting) == 1)
    {    
        Whr_DebugLog("Lightning already started");
        return;
    }
    
    Whr_DebugLog("WhrStartLightning !!");
    
	aref aCurWeather = GetCurrentWeather();
	aref aLightning; 	makearef(aLightning,aCurWeather.Lightning);    
    
    SetEventHandler(WHR_LIGHTNING_SOUND,"Lightning_Sound",0);
	SetEventHandler(WHR_LIGHTNING_DOIT,"Lightning_DoIt",0);

	Lightning.Texture = Whr_GetString(aLightning,"Texture");
	Lightning.Flash.Texture = Whr_GetString(aLightning,"Flash.Texture");
	Lightning.SubTexX = Whr_GetLong(aLightning,"SubTexX");
	Lightning.SubTexY = Whr_GetLong(aLightning,"SubTexY");
	fLightningScaleX = Whr_GetFloat(aLightning,"ScaleX");
	fLightningScaleY = Whr_GetFloat(aLightning,"ScaleY");
    Lightning.Enable = true;
	Lightning.isDone = "";

	PostEvent(WHR_LIGHTNING_DOIT,1000 + rand(1000));

    WeatherParams.Lighting = true;
}

void WhrStopLightning()
{
    if(CheckAttribute(&WeatherParams,"Lighting") && int(WeatherParams.Lighting) == 1)
    {    
        Lightning.Enable = false;
        DelEventHandler(WHR_LIGHTNING_SOUND,"Lightning_Sound");
        DelEventHandler(WHR_LIGHTNING_DOIT, "Lightning_DoIt");
        
        DeleteAttribute(&WeatherParams,"Lighting");
    }   
}

void MoveLightningToLayers(int sExecuteLayer, int sRealizeLayer)
{
	LayerDelObject(EXECUTE,&Lightning);
	LayerDelObject(REALIZE,&Lightning);
	LayerDelObject(SEA_EXECUTE,&Lightning);
	LayerDelObject(SEA_REALIZE,&Lightning);

	LayerAddObject(sExecuteLayer, &Lightning, -2);
	LayerAddObject(sRealizeLayer, &Lightning, -2);
}

void Lightning_DoIt()
{
	if (!isEntity(&Lightning)) 
    { 
        Whr_DebugLog("No Lightning entity !!!");
        return; 
    }

	// next lightning
	PostEvent(WHR_LIGHTNING_DOIT, 500 + rand(5000));

	// if interface launched, return
	if (int(InterfaceStates.Launched) && CurrentInterface != INTERFACE_MAINMENU) { return; }

	aref aCurWeather = GetCurrentWeather();

	int iTimeLightning = 1000;

	float cx = float(Camera.Pos.x);
	float cy = float(Camera.Pos.y);
	float cz = float(Camera.Pos.z);

	float fDist = 1000.0 + frnd() * 2000.0;
	if (rand(30) == 15) { fDist = 20.0 + frnd() * 200.0; }	// nearest lightning
	float fAngle = frnd() * PIm2;
	int iTimeSound = int(fDist / 333.0);

	float fTime = frnd() * 0.1 + 0.1;
	float x = cx + fDist * sin(fAngle);
	float y = 590.0;
	float z = cz + fDist * cos(fAngle);

	int iFlickerTime = Whr_GetLong(aCurWeather, "Lightning.FlickerTime");

	int iSubTexture = rand(int(Lightning.SubTexX) * int(Lightning.SubTexY) - 1);

	float fFlashSize = 1500.0;
	float fLightningSize = 600.0;
	float fScaleX = fLightningScaleX;
	float fScaleY = fLightningScaleY;
	
	if (fDist < 1000.0)
	{
		fLightningSize = 600.0 * fDist / 1000.0;
		if (fLightningSize < 25) { fLightningSize = 25.0; }
		y = fLightningSize - 10.0 * fDist / 1000.0;
	}
	
	SendMessage(&Lightning, "llsflffffffsff", MSG_WHR_LIGHTNING_ADD, iSubTexture, "lightning", fTime, iFlickerTime, fLightningSize, fScaleX, fScaleY, x, y, z, "flash_lightning", fFlashSize, fTime / 2.0);

	bool bSound = false;
	if (fDist < 120.0)	{ bSound = true; }
	if (rand(3) == 1)	{ bSound = true; }

	if (bSound) { PostEvent(WHR_LIGHTNING_SOUND, iTimeSound, "fff", x, y, z); }

	Event(WHR_LIGHTNING, "fff", x, y, z);
}

void Lightning_Sound()
{	
	{
		float x = GetEventData();
		float y = GetEventData();
		float z = GetEventData();
		Play3DSound("thunder", x, y, z);
	}
}
