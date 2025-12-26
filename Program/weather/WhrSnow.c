object Snow;

void CreateSnow()
{
	DeleteSnow();
	if (!isEntity(&Snow))
	{
		CreateEntity(&Snow,"snow");
		LayerAddObject(REALIZE, &Snow, 999999);
	}
}

void CreateDust()
{
	DeleteSnow();
	if (!isEntity(&Snow))
	{
		CreateEntity(&Snow,"snow");
		DustData();
		LayerAddObject(REALIZE, &Snow, 999999);
	}
}

void DeleteSnow()
{
	if (isEntity(&Snow))
	{
		DeleteClass(&Snow);
	}
	DeleteAttribute(&Snow,"");
}

void SnowData()
{
}

void DustData()
{
	Snow.flakeTexture = "dustflakes.tga";
	Snow.flakesMax = 4096;
	Snow.fallSpeedMin = 0.15;
	Snow.fallSpeedMax = 0.35;
	Snow.visibilityRadius = 5.5;
	Snow.visibilityHeight = 3.5;
}

#define SNOW_TEST 1

void Snow_ProcessMessage(int mesId)
{
	switch(mesId)
	{
		case SNOW_TEST:
			SendMessage(&Snow, "l", SNOW_TEST);
		break;
	}
}

