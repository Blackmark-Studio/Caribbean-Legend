void InitShipLights()
{
	string __default = "default"; // default is a keyword now
	aref rlights;

	ShipLights.LightTypes = "";
	ShipLights.MaxD3DLights = 7;
	ShipLights.CoronaTextureX = 1;
	ShipLights.CoronaTextureY = 1;
	ShipLights.CoronaTexture = "ShipsFlares\corona.tga.tx";
	ShipLights.FlareSunRoadTexture = "ShipsFlares\FlareSunRoad.tga.tx";
	ShipLights.CoronaTechnique = "Coronas";
	ShipLights.SunRoadFlareSize = 4.0;

    makearef(rlights, ShipLights.LightTypes);

	// default light emitter for ship
	rlights.(__default).light.r = 1.0;
	rlights.(__default).light.g = 0.9;
	rlights.(__default).light.b = 0.0;
	rlights.(__default).light.range = 15.0;

	rlights.(__default).light.Attenuation0 = 0.0;
	rlights.(__default).light.Attenuation1 = 0.3;
	rlights.(__default).light.Attenuation2 = 0.0;
	
	rlights.(__default).Oscillator1.Flicker = 0.15;
	rlights.(__default).Oscillator1.Freq = 5.0;

	rlights.(__default).Oscillator2.Flicker = 0.1;
	rlights.(__default).Oscillator2.Freq = 1.0;

	rlights.(__default).corona.r = 1.0;
	rlights.(__default).corona.g = 1.0;
	rlights.(__default).corona.b = 1.0;
	rlights.(__default).corona.subtexture = 0;
	rlights.(__default).corona.Range = 5.0
	rlights.(__default).corona.Size = 1.0
	rlights.(__default).SunRoadFlareFadeDistance = 600.0;

	// cannon default light emitter
	rlights.cannondefault.light.r = 2.0;
	rlights.cannondefault.light.g = 2.0;
	rlights.cannondefault.light.b = 2.0;
	rlights.cannondefault.light.range = 20.0;

	rlights.cannondefault.light.Attenuation0 = 0.0;
	rlights.cannondefault.light.Attenuation1 = 0.3;
	rlights.cannondefault.light.Attenuation2 = 0.0;	

	rlights.cannondefault.LifeTime = 0.2;
	rlights.cannondefault.UpTime = 0.1;

	// default flare for ship
	rlights.flare.light.r = 1.2;
	rlights.flare.light.g = 1.0;
	rlights.flare.light.b = 2.2;
	rlights.flare.light.range = 15.0;

	rlights.flare.light.Attenuation0 = 0.0;
	rlights.flare.light.Attenuation1 = 0.3;
	rlights.flare.light.Attenuation2 = 0.0;

	rlights.flare.Oscillator1.Flicker = 0.15;
	rlights.flare.Oscillator1.Freq = 5.0;

	rlights.flare.Oscillator2.Flicker = 0.1;
	rlights.flare.Oscillator2.Freq = 1.0;

	rlights.flare.corona.r = 1.0;
	rlights.flare.corona.g = 1.0;
	rlights.flare.corona.b = 1.0;
	rlights.flare.corona.subtexture = 0;
	rlights.flare.corona.Range = 5.0
	rlights.flare.corona.Size = 1.0
	rlights.flare.SunRoadFlareFadeDistance = 600.0;
}
