// инициализация базовых параметров погоды
int InitWeather()
{	
	int n = 0;
	
	n = Whr_InitStdWeather( n, 		"0 Hour",	0.00,	0.99,		"night0",	"storm",	"n",	0,	0,	0,	1,	1,	1,	1,	1,	0, 		"24", 	1, 	1,	1,	0 );
	n = Whr_InitStdWeather( n, 		"1 Hour",	1.00,	1.99,		"night1",	"storm",	"n",	0,	0,	0,	1,	1,	1,	1,	1,	0,		"01", 	1, 	1,	1,	0 );
	n = Whr_InitStdWeather( n, 		"2 Hour",	2.00,	2.99,		"night2",	"storm",	"n",	0,	0,	0,	1,	1,	1,	1,	1,	0,		"02", 	1, 	1,	1,	0 );
	n = Whr_InitStdWeather( n, 		"3 Hour",	3.00,	3.99,		"night3",	"storm",	"n",	0,	0,	0,	1,	1,	1,	1,	1,	0, 		"03", 	1, 	1,	1,	0 );
	n = Whr_InitStdWeather( n, 		"4 Hour",	4.00,	4.99,		"night4",	"storm",	"n",	0,	0,	0,	1,	1,	1,	1,	1,	0, 		"04", 	1, 	1,	1,	0 );
	n = Whr_InitStdWeather( n, 		"5 Hour",	5.00,	5.99,		"night5",	"storm",	"n",	0,	0,	0,	1,	1,	1,	1,	1,	0, 		"05", 	1, 	1,	0,	0 );	
	n = Whr_InitStdWeather( n, 		"6 Hour",	6.00,	6.99,	  "morning6", "morning",	"m",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"06", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 		"7 Hour",	7.00,	7.99,     "morning7", "morning",	"m",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"07", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 		"8 Hour",	8.00,	8.99,     "morning8", "morning",	"m",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"08", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 		"9 Hour",	9.00,	9.99,     "morning9", "morning",	"m",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"09", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "10 Hour",  10.00,  10.99,    "morning10", "morning",	"m",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"10", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "11 Hour",  11.00,  11.99,        "day11",    "day1",	"d",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"11", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "12 Hour",  12.00,  12.99,        "day12",    "day1",	"d",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"12", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "13 Hour",  13.00,  13.99,        "day13",    "day2",	"d",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"13", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "14 Hour",  14.00,  14.99,        "day14",    "day2",	"d",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"14", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "15 Hour",  15.00,  15.99,        "day15",    "day3",	"d",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"15", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "16 Hour",  16.00,  16.99,        "day16",    "day3",	"d",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"16", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "17 Hour",  17.00,  17.99,        "day17",    "day4",	"d",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"17", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "18 Hour",  18.00,  18.99,        "day18",    "day4",	"d",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"18", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "19 Hour",  19.00,  19.99,    "evening19", "evening",	"e",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"19", 	1, 	1,	1,	1 );
	n = Whr_InitStdWeather( n, 	   "20 Hour",  20.00,  20.99,    "evening20", "evening",	"e",	0,	0,	0,	1,	1,	1,	0,	0,	0, 		"20", 	1, 	1,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "21 Hour",  21.00,  21.99,    "evening21", "evening",	"e",	0,	0,	0,	1,	1,	1,	0,	0,	0, 		"21", 	1, 	1,	1,	0 );
	n = Whr_InitStdWeather( n, 	   "22 Hour",  22.00,  22.99,    "evening22", "evening",	"e",	0,	0,	0,	1,	1,	1,	0,	0,	0, 		"22", 	1, 	1,	1,	0 );
	n = Whr_InitStdWeather( n, 	   "23 Hour",  23.00,  23.99,    "evening23", "evening",	"e",	0,	0,	0,	1,	1,	1,	1,	1,	0, 		"23", 	1, 	1,	1,	0 );	
	n = Whr_InitStdWeather( n, 	   "Storm00",   0.00,   0.99,       "storm4",   "storm",	"s",	1,	1,	1,	1,	1,	0,	0,	0,	1,    "night", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm01",   1.00,   1.99,       "storm4",   "storm",	"s",	1,	1,	1,	1,	1,	0,	0,	0,	1,    "night", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm02",   2.00,   2.99,       "storm4",   "storm",	"s",	1,	1,	1,	1,	1,	0,	0,	0,	1,    "night", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm03",   3.00,   3.99,       "storm4",   "storm",	"s",	1,	1,	1,	1,	1,	0,	0,	0,	1, "twilight", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm04",   4.00,   4.99,       "storm4",   "storm",	"s",	1,	1,	1,	1,	1,	0,	0,	0,	1, "twilight", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm05",   5.00,   5.99,       "storm4",   "storm",	"s",	1,	1,	1,	1,	1,	0,	0,	0,	1, "twilight", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm06",   6.00,   6.99,       "storm1",   "storm",	"s",	1,	1,	0,	0,	0,	0,	0,	0,	1,  "morning", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm07",   7.00,   7.99,       "storm1",   "storm",	"s",	1,	1,	0,	0,	0,	0,	0,	0,	1,  "morning", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm08",   8.00,   8.99,       "storm1",   "storm",	"s",	1,	1,	0,	0,	0,	0,	0,	0,	1,  "morning", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm09",   9.00,   9.99,       "storm1",   "storm",	"s",	1,	1,	0,	0,	0,	0,	0,	0,	1,  "morning", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm10",  10.00,  10.99,       "storm1",   "storm",	"s",	1,	1,	0,	0,	0,	0,	0,	0,	1,  "morning", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm11",  11.00,  11.99,       "storm2",   "storm",	"s",	1,	1,	1,	0,	0,	0,	0,	0,	1,      "day", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm12",  12.00,  12.99,       "storm2",   "storm",	"s",	1,	1,	1,	0,	0,	0,	0,	0,	1,      "day", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm13",  13.00,  13.99,       "storm2",   "storm",	"s",	1,	1,	1,	0,	0,	0,	0,	0,	1,      "day", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm14",  14.00,  14.99,       "storm2",   "storm",	"s",	1,	1,	1,	0,	0,	0,	0,	0,	1,      "day", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm15",  15.00,  15.99,       "storm2",   "storm",	"s",	1,	1,	1,	0,	0,	0,	0,	0,	1,      "day", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm16",  16.00,  16.99,       "storm2",   "storm",	"s",	1,	1,	1,	0,	0,	0,	0,	0,	1,      "day", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm17",  17.00,  17.99,       "storm2",   "storm",	"s",	1,	1,	1,	0,	0,	0,	0,	0,	1,      "day", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm18",  18.00,  18.99,       "storm3",   "storm",	"s",	1,	1,	1,	0,	0,	0,	0,	0,	1,  "evening", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm19",  19.00,  19.99,       "storm3",   "storm",	"s",	1,	1,	1,	0,	0,	0,	0,	0,	1,  "evening", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm20",  20.00,  20.99,       "storm3",   "storm",	"s",	1,	1,	1,	1,	0,	0,	0,	0,	1,  "evening", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm21",  21.00,  21.99,       "storm4",   "storm",	"s",	1,	1,	1,	1,	1,	0,	0,	0,	1, "twilight", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm22",  22.00,  22.99,       "storm4",   "storm",	"s",	1,	1,	1,	1,	1,	0,	0,	0,	1, "twilight", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	   "Storm23",  23.00,  23.99,       "storm4",   "storm",	"s",	1,	1,	1,	1,	1,	0,	0,	0,	1,    "night", 	0,  0,	0,	0 );
	n = Whr_InitStdWeather( n, 	    "Inside",   0.00,  23.99,       "inside",  "inside",	 "",	0,	0,	0,	0,	0,	0,	0,	0,	0, 		"10", 	0,	1,	0,	1 );
	n = Whr_InitStdWeather( n, 	"Underwater",   0.00,  23.99,    "morning10", "morning",	"m",	0,	0,	1,	0,	0,	0,	0,	0,	0, 		"10", 	0,	1,	0,	0 );

	Trace("Init weathers complete. " + n + " weathers found.");

	return n;
}

int Whr_InitStdWeather( int		_index,
						string 	id, 
						float	hourMin,
						float	hourMax,
						string 	Lighting,
						string 	LightingLm,
						string	InsideBack,
						bool	_storm,
						bool	_tornado,
						bool	_shark,
						bool	_lights,
						bool	_night, 
						bool	_stars,
						bool	_planets,
						bool	_moon,
						bool	_lightning,
						string  skyBoxSubDir,
						bool	sunGlow,
						bool	sunReflection,
						bool	sunOverflow,
						bool	sunFlares)
{
	ref	whr;
	
	int	whrIndex = _index;
	
	makeref(whr, Weathers[whrIndex]);
	
	whr.id						= id;
	whr.Hour.Min 				= hourMin;
	whr.Hour.Max 				= hourMax;
	whr.Lighting				= Lighting;
	whr.LightingLm				= LightingLm;
	whr.InsideBack				= InsideBack;
	whr.Sky.SubDir				= skyBoxSubDir;
	
	whr.Storm 					= _storm;
	whr.Tornado 				= _tornado;
	whr.Shark 					= _shark;
	whr.Lights 					= _lights;
	whr.Night 					= _night;
	whr.Stars.Enable 			= _stars;
	whr.Planets.enable			= _planets;
	whr.Sun.Moon				= _moon;
	
	// common stars
	whr.Stars.Texture 			= "weather\astronomy\stars.tga";
	whr.Stars.Color 			= argb(0,255,255,255);
	whr.Stars.Radius 			= 2000.0;
	whr.Stars.Size 				= 27.0;
	whr.Stars.HeightFade 		= 200.0;
	whr.Stars.SunFade 			= 1.0;
	whr.Stars.VisualMagnitude 	= 8.0;	
	
    whr.Lightning.Enable		= _lightning;
	whr.Lightning.Texture 		= "weather\lightning\lightning_storm.tga";
	whr.Lightning.FlickerTime 	= 32;
	whr.Lightning.SubTexX 		= 4;
	whr.Lightning.SubTexY 		= 1;
	whr.Lightning.ScaleX 		= 0.7;
	whr.Lightning.ScaleY 		= 1.0;
	whr.Lightning.Flash.Texture = "weather\lightning\flash.tga";
	
	whr.Sounds.Sea.Postfix 			= "";
	
	//common fog
	whr.Fog.Enable 					= true;	
	whr.Fog.Height 					= 200;
	whr.Fog.Start 					= 10;
	whr.Fog.Density 				= 0.001;
	whr.Fog.IslandDensity 			= 0.0003;
	whr.Fog.SeaDensity 				= 0.0001;
	
	// common shadow
	whr.Shadow.Density.Head 		= argb(255,96,96,96);
	whr.Shadow.Density.Foot 		= argb(255,96,96,64);
	
	// common sky
	whr.Sky.Rotate.Min 				= 0.0;
	whr.Sky.Rotate.Max 				= 0.0;
	whr.Sky.Size 					= 1024;
	whr.Sky.Angle 					= 0.0;
	whr.Sky.Color 					= argb(0,255,255,255);
	
	// common rainbow
	whr.Rainbow.Enable 				= false;
	whr.Rainbow.Texture 			= "weather\rainbow\rainbow.tga";
	
	// common sun
	whr.Sun.Glow.Enable 			= sunGlow;
	whr.Sun.Glow.Dist 				= 3500.0;
	whr.Sun.Glow.Size 				= 1250.0;
	whr.Sun.Glow.Texture 			= "weather\sun\glow\sun.tga";
	whr.Sun.Glow.DecayTime 			= 8.0;
	whr.Sun.Glow.TechniqueNoZ 		= "sunglow_noz";
	whr.Sun.Glow.TechniqueZ 		= "sunglow_z";
	whr.Sun.Glow.Color 				= argb(0,255,255,255);

	whr.Sun.Overflow.Enable 		= sunOverflow;
	whr.Sun.Overflow.Texture 		= "weather\sun\overflow\overflow.tga";
	whr.Sun.Overflow.Color 			= argb(0,100,100,100);
	whr.Sun.Overflow.Size 			= 5500.0;
	whr.Sun.Overflow.Technique 		= "sunoverflow";
	whr.Sun.Overflow.Start 			= 0.7;

	whr.Sun.Reflection.Enable 		= sunReflection;
	whr.Sun.Reflection.Texture 		= "weather\sun\reflection\refl_day.tga";
	whr.Sun.Reflection.Technique 	= "sunreflection";
	whr.Sun.Reflection.Dist 		= 3500.0;
	whr.Sun.Reflection.Size 		= 500.0;
	whr.Sun.Reflection.Color 		= argb(0,200,200,200);

	whr.Sun.Flare.Enable 			= sunFlares;
	whr.Sun.Flare.Texture 			= "weather\sun\flare\allflares.tga";
	whr.Sun.Flare.Dist 				= 3000.0;
	whr.Sun.Flare.TexSizeX 			= 4;
	whr.Sun.Flare.TexSizeY 			= 4;
	whr.Sun.Flare.Technique 		= "sunflare";
	whr.Sun.Flare.Scale 			= 2.0;
	
	whr.Sun.Flares.f1 				= "1.0,600.0,0,808080";
	whr.Sun.Flares.f2 				= "1.0,250.0,1,606060";
	whr.Sun.Flares.f3 				= "0.90,100.0,2,404040";
	whr.Sun.Flares.f4 				= "0.85,300.0,3,606060";
	whr.Sun.Flares.f5 				= "0.75,50.0,12,808080";
	whr.Sun.Flares.f6 				= "0.66,60.0,15,404040";
	whr.Sun.Flares.f7 				= "0.59,50.0,13,202020";
	whr.Sun.Flares.f8 				= "0.55,70.0,5,404040";
	whr.Sun.Flares.f9 				= "0.42,100.0,5,404040";
	whr.Sun.Flares.f10 				= "0.48,70.0,13,303030";
	whr.Sun.Flares.f11				= "0.41,60.0,14,404040";
	whr.Sun.Flares.f12 				= "0.30,130.0,7,202020";
	whr.Sun.Flares.f13 				= "0.32,110.0,6,404040";
	whr.Sun.Flares.f14 				= "0.26,50.0,12,404040";
	whr.Sun.Flares.f15 				= "0.22,60.0,13,202020";
	whr.Sun.Flares.f16 				= "0.20,60.0,15,303030";
	whr.Sun.Flares.f17 				= "0.15,50.0,12,404040";
	whr.Sun.Flares.f18 				= "0.10,40.0,11,808080";
	whr.Sun.Flares.f19 				= "0.13,400.0,10,404040";

	// common rain
	whr.Rain.NumDrops 				= 0;
	whr.Rain.Color 					= argb(0,73,73,73);
	whr.Rain.DropLength 			= 2.12;
	whr.Rain.Height 				= 30.0;
	whr.Rain.Radius 				= 30.0;
	whr.Rain.Speed 					= 18.0;
	whr.Rain.Jitter 				= 0.4;
	whr.Rain.WindSpeedJitter 		= 0.5;
	whr.Rain.MaxBlend 				= 49;
	whr.Rain.TimeBlend 				= 2000;

	whr.Rain.DropsNearNum 			= 500;
	whr.Rain.DropsFarNum 			= 500;
	whr.Rain.DropsNearRadius 		= 25.0;
	whr.Rain.DropsFarRadius 		= 75.0;
	whr.Rain.DropsLifeTime 			= 0.25;
	whr.Rain.DropsSize 				= 0.06;
	whr.Rain.DropsTexture 			= "weather\rain_drops.tga";
	whr.Rain.DropsColor 			= argb(43,255,255,255);
	
	// common wind
	whr.Wind.Angle 					= 2.0;
	whr.Wind.Speed.Min 				= WIND_MIN_POWER;
	whr.Wind.Speed.Max 				= WIND_MAX_POWER;
		
	if(_storm)
	{
		whr.Sounds.Sea.Postfix 				= "_storm";
		
		whr.Fog.Height 						= 700;
		whr.Fog.Start 						= 0;
		whr.Fog.Density 					= 0.008;
		whr.Fog.IslandDensity 				= 0.005;
		whr.Fog.SeaDensity 					= 0.002;
		
		whr.Rain.NumDrops 					= 50000;
		
		whr.Wind.Speed.Min 					= 15.0;
		whr.Wind.Speed.Max 					= 19.0;	
	}		
		
	switch (id)
	{
		// night (0 - 5)
		case "0 Hour" 			:
			whr.Sun.Color 						= argb(  0, 45, 55, 65 );
			whr.Sun.Ambient 					= argb(  0, 25, 30, 35 );
            whr.Sun.SeaColor 					= argb(  0, 45, 55, 65 );
			whr.Sun.SeaAmbient 					= argb(  0, 25, 30, 35 );
			whr.Fog.Color 						= argb(  0,  6, 13, 23 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
		break;
		
		case "1 Hour" 			:
			whr.Sun.Color 						= argb(  0, 45, 55, 65 );
			whr.Sun.Ambient 					= argb(  0, 25, 30, 35 );
            whr.Sun.SeaColor 					= argb(  0, 45, 55, 65 );
			whr.Sun.SeaAmbient 					= argb(  0, 25, 30, 35 );
			whr.Fog.Color 						= argb(  0,  5, 12, 19 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
		break;
		
		case "2 Hour" 			:
			whr.Sun.Color 						= argb(  0, 45, 55, 65 );
			whr.Sun.Ambient 					= argb(  0, 25, 30, 35 );
            whr.Sun.SeaColor 					= argb(  0, 45, 55, 65 );
			whr.Sun.SeaAmbient 					= argb(  0, 25, 30, 35 );
			whr.Fog.Color 						= argb(  0,  5, 12, 19 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
		break;	

		case "3 Hour" 			:
			whr.Sun.Color 						= argb(  0, 45, 55, 65 );
			whr.Sun.Ambient 					= argb(  0, 25, 30, 35 );
            whr.Sun.SeaColor 					= argb(  0, 45, 55, 65 );
			whr.Sun.SeaAmbient 					= argb(  0, 25, 30, 35 );
			whr.Fog.Color 						= argb(  0,  3,  8, 15 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
		break;	

		case "4 Hour" 			:
			whr.Sun.Color 						= argb(  0, 45, 55, 65 );
			whr.Sun.Ambient 					= argb(  0, 25, 30, 35 );
            whr.Sun.SeaColor 					= argb(  0, 45, 55, 65 );
			whr.Sun.SeaAmbient 					= argb(  0, 25, 30, 35 );
			whr.Fog.Color 						= argb(  0,  5, 13, 26 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
		break;	

		case "5 Hour" 			:
			whr.Sun.Color 						= argb(  0, 45, 55, 65 );
			whr.Sun.Ambient 					= argb(  0, 25, 30, 35 );
            whr.Sun.SeaColor 					= argb(  0, 45, 55, 65 );
			whr.Sun.SeaAmbient 					= argb(  0, 25, 30, 35 );
			whr.Fog.Color 						= argb(  0, 29, 46, 54 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );

			whr.SpecialLandFog.Color			= argb(  0, 10, 21, 37 );
			whr.SpecialLandFog.Height 			= 700;
			whr.SpecialLandFog.Start 			= 0;
			whr.SpecialLandFog.Density 			= 0.015;
			whr.SpecialLandFog.IslandDensity 	= 0.006;
			whr.SpecialLandFog.SeaDensity 		= 0.0006;
			whr.SpecialLandFog.Enable 			= true;	
			whr.SpecialLandFog.Type				= 0;
		break;		
		
		// morning (6 - 10)
		case "6 Hour" 			:
			whr.Sun.Color 						= argb(  0,255,215, 100);
			whr.Sun.Ambient 					= argb(  0, 73, 55, 47 );
			whr.Fog.Color 						= argb(  0, 99, 74, 70 );
			whr.Rain.DropsColor 				= argb( 50,255,255,255 );
			
			whr.Sun.Flares.f20 					= "0.2,1000.0,9,606060";
			
			whr.SpecialLandFog.Color			= argb(  0, 68, 70, 74 );
			whr.SpecialLandFog.Height 			= 2200;
			whr.SpecialLandFog.Start 			= 0;
			whr.SpecialLandFog.Density 			= 0.020;
			whr.SpecialLandFog.IslandDensity 	= 0.020;
			whr.SpecialLandFog.SeaDensity 		= 0.0006;
			whr.SpecialLandFog.Enable 			= true;	
			whr.SpecialLandFog.Type				= 0;
		break;
		
		case "7 Hour" 			:
			whr.Sun.Color 						= argb(  0, 98, 94, 84 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,152,164,155 );
			whr.Rain.DropsColor 				= argb( 50,255,255,255 );
			
			whr.SpecialLandFog.Color			= argb(  0,116,147,166 );
			whr.SpecialLandFog.Height 			= 1700;
			whr.SpecialLandFog.Start 			= 0;
			whr.SpecialLandFog.Density 			= 0.015;
			whr.SpecialLandFog.IslandDensity 	= 0.012;
			whr.SpecialLandFog.SeaDensity 		= 0.0006;
			whr.SpecialLandFog.Enable 			= true;
			whr.SpecialLandFog.Type				= 0;
		break;
		
		case "8 Hour" 			:
			whr.Sun.Color 						= argb(  0,115,110, 95 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,181,209,221 );
			whr.Rain.DropsColor 				= argb( 55,255,255,255 );
			
			whr.SpecialLandFog.Color			= argb(  0,152,176,198 );
			whr.SpecialLandFog.Height 			= 700;
			whr.SpecialLandFog.Start 			= 0;
			whr.SpecialLandFog.Density 			= 0.010;
			whr.SpecialLandFog.IslandDensity 	= 0.006;
			whr.SpecialLandFog.SeaDensity 		= 0.0006;
			whr.SpecialLandFog.Enable 			= true;
			whr.SpecialLandFog.Type				= 0;
		break;	

		case "9 Hour" 			:			
			whr.Sun.Color 						= argb(  0,155,148,125 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,193,218,228 );
			whr.Rain.DropsColor 				= argb( 59,255,255,255 );
		break;	

		case "10 Hour" 			:
			whr.Sun.Color 						= argb(  0,180,170,145 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,193,218,228 );
			whr.Rain.DropsColor 				= argb( 61,255,255,255 );
		break;		
		
		// day (11 - 18)
		case "11 Hour" 			:			
			whr.Sun.Color 						= argb(  0,195,185,157 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,193,218,228 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );
		break;		
		
		case "12 Hour" 			:			
			whr.Sun.Color 						= argb(  0,200,190,160 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,193,218,228 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );
		break;	

		case "13 Hour" 			:
			whr.Sun.Color 						= argb(  0,200,190,160 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,193,218,228 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );
		break;	

		case "14 Hour" 			:
			whr.Sun.Color 						= argb(  0,195,185,156 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,193,218,228 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );
		break;	

		case "15 Hour" 			:
			whr.Sun.Color 						= argb(  0,185,175,148 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,193,218,228 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );
		break;	

		case "16 Hour" 			:
			whr.Sun.Color 						= argb(  0,170,161,137 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,193,218,228 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );
		break;	

		case "17 Hour" 			:
			whr.Sun.Color 						= argb(  0,160,153,129 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,174,204,215 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );
		break;	

		case "18 Hour" 			:
			whr.Sun.Color 						= argb(  0,145,138,119 );
			whr.Sun.Ambient 					= argb(  0,128,128,128 );
			whr.Fog.Color 						= argb(  0,156,163,164 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );
		break;	

		// evening (19 - 23)
		case "19 Hour" 			:
			whr.Sun.Color 						= argb(  0,255,180, 85 );
			whr.Sun.Ambient 					= argb(  0,113, 79, 54 );
			whr.Rain.DropsColor 				= argb( 60,255,255,255 );
			                            
			whr.Sun.Flares.f20 					= "0.2,1000.0,9,606060";
		break;	

		case "20 Hour" 			:
			whr.Sun.Color 						= argb(  0, 67, 70, 77 );
			whr.Sun.Ambient 					= argb(  0, 35, 30, 30 );
            whr.Sun.SeaColor 					= argb(  0, 67, 70, 77 );
			whr.Sun.SeaAmbient 					= argb(  0, 35, 30, 30 );
			whr.Fog.Color 						= argb(  0, 60, 54, 54 );
			whr.Rain.DropsColor 				= argb( 58,255,255,255 );

			whr.SpecialLandFog.Color			= argb(  0, 47, 46, 53 );
			whr.SpecialLandFog.Height 			= 700;
			whr.SpecialLandFog.Start 			= 0;
			whr.SpecialLandFog.Density 			= 0.015;
			whr.SpecialLandFog.IslandDensity 	= 0.005;
			whr.SpecialLandFog.SeaDensity 		= 0.0006;
			whr.SpecialLandFog.Enable 			= true;	
			whr.SpecialLandFog.Type				= 1;
		break;	

		case "21 Hour" 			:
			whr.Sun.Color 						= argb(  0, 45, 55, 65 );
			whr.Sun.Ambient 					= argb(  0, 25, 30, 35 );
            whr.Sun.SeaColor 					= argb(  0, 45, 55, 65 );
			whr.Sun.SeaAmbient 					= argb(  0, 25, 30, 35 );
			whr.Fog.Color 						= argb(  0,  7, 15, 23 );
			whr.Rain.DropsColor 				= argb( 56,255,255,255 );

			whr.SpecialLandFog.Color			= argb(  0, 26, 25, 30 );
			whr.SpecialLandFog.Height 			= 2200;
			whr.SpecialLandFog.Start 			= 0;
			whr.SpecialLandFog.Density 			= 0.025;
			whr.SpecialLandFog.IslandDensity 	= 0.020;
			whr.SpecialLandFog.SeaDensity 		= 0.0006;
			whr.SpecialLandFog.Enable 			= true;
			whr.SpecialLandFog.Type				= 1;
		break;	

		case "22 Hour" 			:
			whr.Sun.Color 						= argb(  0, 45, 55, 65 );
			whr.Sun.Ambient 					= argb(  0, 25, 30, 35 );
            whr.Sun.SeaColor 					= argb(  0, 45, 55, 65 );
			whr.Sun.SeaAmbient 					= argb(  0, 25, 30, 35 );
			whr.Fog.Color 						= argb(  0,  5, 12, 20 );
			whr.Rain.DropsColor 				= argb( 52,255,255,255 );

			whr.SpecialLandFog.Color			= argb(  0,  14, 14, 23 );
			whr.SpecialLandFog.Height 			= 1700;
			whr.SpecialLandFog.Start 			= 0;
			whr.SpecialLandFog.Density 			= 0.025;
			whr.SpecialLandFog.IslandDensity 	= 0.008;
			whr.SpecialLandFog.SeaDensity 		= 0.0006;
			whr.SpecialLandFog.Enable 			= true;
			whr.SpecialLandFog.Type				= 1;
		break;	

		case "23 Hour" 			:
			whr.Sun.Color 						= argb(  0, 45, 55, 65 );
			whr.Sun.Ambient 					= argb(  0, 25, 30, 35 );
            whr.Sun.SeaColor 					= argb(  0, 45, 55, 65 );
			whr.Sun.SeaAmbient 					= argb(  0, 25, 30, 35 );
			whr.Fog.Color 						= argb(  0,  6, 13, 21 );
			whr.Rain.DropsColor 				= argb( 46,255,255,255 );

			whr.SpecialLandFog.Color			= argb(  0,  13, 13, 23 );
			whr.SpecialLandFog.Height 			= 700;
			whr.SpecialLandFog.Start 			= 0;
			whr.SpecialLandFog.Density 			= 0.015;
			whr.SpecialLandFog.IslandDensity 	= 0.003;
			whr.SpecialLandFog.SeaDensity 		= 0.0006;
			whr.SpecialLandFog.Enable 			= true;
			whr.SpecialLandFog.Type				= 1;
		break;	

		// штормовая погода - на все часы
		// ночь
		case "Storm00"			:
			whr.Fog.Color 						= argb(  0,  5,  5,  5 );
		
			whr.Rain.Color 						= argb(  0, 43, 43, 33 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
                                        
			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm01"			:
			whr.Fog.Color 						= argb(  0,  5,  5,  5 );
		
			whr.Rain.Color 						= argb(  0, 43, 43, 33 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
                                        
			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm02"			:
			whr.Fog.Color 						= argb(  0,  5,  5,  5 );
		
			whr.Rain.Color 						= argb(  0, 43, 43, 33 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
                                        
			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		// рассвет
		case "Storm03"			:
			whr.Fog.Color 						= argb(  0, 14, 14, 16 );
		
			whr.Rain.Color 						= argb(  0, 43, 43, 33 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
                                        
			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm04"			:
			whr.Fog.Color 						= argb(  0, 14, 14, 16 );
		
			whr.Rain.Color 						= argb(  0, 43, 43, 33 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
                                        
			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm05"			:
			whr.Fog.Color 						= argb(  0, 14, 14, 16 );
		
			whr.Rain.Color 						= argb(  0, 43, 43, 33 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );
                                        
			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		// утро
		case "Storm06"			:
			whr.Fog.Color 						= argb(  0, 55, 72, 88 );
		
			whr.Rain.Color 						= argb(  0, 23, 23, 23 );
			whr.Rain.DropsColor 				= argb( 55,255,255,255 );

			whr.Sun.Color 						= argb(  0, 50, 50, 50 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm07"			:
			whr.Fog.Color 						= argb(  0, 55, 72, 88 );
		
			whr.Rain.Color 						= argb(  0, 23, 23, 23 );
			whr.Rain.DropsColor 				= argb( 55,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm08"			:
			whr.Fog.Color 						= argb(  0, 55, 72, 88 );
		
			whr.Rain.Color 						= argb(  0, 23, 23, 23 );
			whr.Rain.DropsColor 				= argb( 55,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm09"			:
			whr.Fog.Color 						= argb(  0, 55, 72, 88 );
		
			whr.Rain.Color 						= argb(  0, 23, 23, 23 );
			whr.Rain.DropsColor 				= argb( 55,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm10"			:
			whr.Fog.Color 						= argb(  0, 55, 72, 88 );
		
			whr.Rain.Color 						= argb(  0, 23, 23, 23 );
			whr.Rain.DropsColor 				= argb( 55,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		// день
		case "Storm11"			:
			whr.Fog.Color 						= argb(  0,157,155,158 );
		
			whr.Rain.Color 						= argb(  0, 13, 13, 13 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm12"			:
			whr.Fog.Color 						= argb(  0,157,155,158 );
		
			whr.Rain.Color 						= argb(  0, 13, 13, 13 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm13"			:
			whr.Fog.Color 						= argb(  0,157,155,158 );
		
			whr.Rain.Color 						= argb(  0, 13, 13, 13 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm14"			:
			whr.Fog.Color 						= argb(  0,157,155,158 );
		
			whr.Rain.Color 						= argb(  0, 13, 13, 13 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );

			whr.Sun.Color 						= argb(  0, 82, 99,123 );
			whr.Sun.Ambient 					= argb(  0, 135, 135, 135 );
		break;

		case "Storm15"			:
			whr.Fog.Color 						= argb(  0,157,155,158 );
		
			whr.Rain.Color 						= argb(  0, 13, 13, 13 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );

			whr.Sun.Color 						= argb(  0, 82, 99,123 );
			whr.Sun.Ambient 					= argb(  0, 135, 135, 135 );
		break;

		case "Storm16"			:
			whr.Fog.Color 						= argb(  0,157,155,158 );
		
			whr.Rain.Color 						= argb(  0, 13, 13, 13 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm17"			:
			whr.Fog.Color 						= argb(  0,157,155,158 );
		
			whr.Rain.Color 						= argb(  0, 13, 13, 13 );
			whr.Rain.DropsColor 				= argb( 63,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		// вечер
		case "Storm18"			:
			whr.Fog.Color 						= argb(  0, 30, 40, 41 );
		
			whr.Rain.Color 						= argb(  0, 33, 33, 33 );
			whr.Rain.DropsColor 				= argb( 60,255,255,255 );

			whr.Sun.Color 						= argb(  0, 60, 60, 60 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm19"			:
			whr.Fog.Color 						= argb(  0, 30, 40, 41 );
		
			whr.Rain.Color 						= argb(  0, 33, 33, 33 );
			whr.Rain.DropsColor 				= argb( 60,255,255,255 );

			whr.Sun.Color 						= argb(  0, 50, 50, 50 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm20"			:
			whr.Fog.Color 						= argb(  0, 30, 40, 41 );
		
			whr.Rain.Color 						= argb(  0, 33, 33, 33 );
			whr.Rain.DropsColor 				= argb( 60,255,255,255 );

			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		// закат
		case "Storm21"			:
			whr.Fog.Color 						= argb(  0, 14, 14, 16 );
		
			whr.Rain.Color 						= argb(  0, 43, 43, 33 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );

			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Storm22"			:
			whr.Fog.Color 						= argb(  0, 14, 14, 16 );
		
			whr.Rain.Color 						= argb(  0, 43, 43, 33 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );

			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		// ночь
		case "Storm23"			:
			whr.Fog.Color 						= argb(  0,  5,  5,  5 );
		
			whr.Rain.Color 						= argb(  0, 43, 43, 33 );
			whr.Rain.DropsColor 				= argb( 43,255,255,255 );

			whr.Sun.Color 						= argb(  0, 40, 40, 40 );
			whr.Sun.Ambient 					= argb(  0, 35, 35, 35 );
		break;

		case "Inside"			:
			whr.Skip 							= true;
			whr.Fog.Enable 						= false;	
			whr.Sun.Color 						= argb(  0, 80, 80, 68 );
			whr.Sun.Ambient 					= argb(  0, 40, 30, 20 );
		break;
		
		case "Underwater"		:
			whr.Skip 							= true;

			whr.Fog.Enable 						= true;
			whr.Fog.Height 						= 2000;
			whr.Fog.Start 						= 1;
			whr.Fog.Density 					= 0.1;
			whr.Fog.IslandDensity 				= 0.002;
			whr.Fog.SeaDensity 					= 0.006;
			whr.Fog.Color 						= argb(  0, 2, 95, 138 );

			whr.Sun.Color 						= argb(  0, 10, 40, 43 );
			whr.Sun.Ambient 					= argb(  0,134,199,209 );

			whr.Wind.Speed.Min 					= 7.0;
			whr.Wind.Speed.Max 					= 14.5;
		break;                          
	}                                   		

	whrIndex++;                         
	return whrIndex;                    		
}				                        		
