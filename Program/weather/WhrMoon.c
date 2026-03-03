object MoonGlow;

void WhrDeleteMoonGlowEnvironment()
{
	if (isEntity(&Moon))
	{
		DeleteClass(&MoonGlow);
	}
	DeleteAttribute(&MoonGlow,"");
}

// TO_DO: Currently this not using
void WhrCreateMoonGlowEnvironment()
{
	// create moon
	if (!isEntity(&MoonGlow))
	{
		CreateEntity(&MoonGlow,"SunGlow");
		LayerAddObject(SEA_SUNROAD,&MoonGlow,-1);
	}
	WhrFillMoonGlowData(iCurWeatherNum, iBlendWeatherNum);
	MoonGlow.isDone = true;

    // See SunGlow code
}

void MoveMoonGlowToLayers(int sExecuteLayer, int sRealizeLayer)
{
	LayerDelObject(EXECUTE,&MoonGlow);
	LayerDelObject(REALIZE,&MoonGlow);

	LayerDelObject(SEA_EXECUTE,&MoonGlow);
	LayerDelObject(SEA_REALIZE,&MoonGlow);

	LayerAddObject(sExecuteLayer, &MoonGlow, -2);
	LayerAddObject(sRealizeLayer, &MoonGlow, -2);
}

void WhrFillMoonGlowData(int nw1, int nw2)
{
	if (nw1 < 0 || nw1 >= MAX_WEATHERS) return;

	MoonGlow.Clear = "";
	DeleteAttribute(&MoonGlow,"");

    // See SunGlow code
}
