void ApplyMigration(ref migrationState)
{
	int n, i;
	
	// каюта галеона
	n = FindLocation("My_Cabin_Huge");
	
	DeleteAttribute(&Locations[n], "models");
	SetDefaultLightingModels(n);
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_2G"; // каюта галеона
	//Always
	Locations[n].models.always.main = "inside_cabin_2G";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_2G_parts";
	//Locations[n].models.always.outside = "inside_cabin_2G_outside";
	Locations[n].models.always.locators = "inside_cabin_2G_locators";
	Locations[n].models.always.bsp = "inside_cabin_2G_bsp";
	Locations[n].models.always.camcollider = "inside_cabin_2G_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_2G_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_2G_patch";
	Locations[n].models.day.fonar = "inside_cabin_2G_fd";
	Locations[n].models.day.rays = "inside_cabin_2G_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_2G_patch";
	Locations[n].models.night.fonar = "inside_cabin_2G_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

    // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;
	
	locations[n].box1 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box2 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box3 = Items_MakeTime(0, 1, 1, 2003);
	
	// каюта галеона
	n = FindLocation("Cabin_Huge");
	
	DeleteAttribute(&Locations[n], "models");
	SetDefaultLightingModels(n);
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_2G"; // каюта галеона
	//Always
	Locations[n].models.always.main = "inside_cabin_2G";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_2G_parts";
	//Locations[n].models.always.outside = "inside_cabin_2G_outside";
	Locations[n].models.always.locators = "inside_cabin_2G_locators";
	Locations[n].models.always.bsp = "inside_cabin_2G_bsp";
	Locations[n].models.always.camcollider = "inside_cabin_2G_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_2G_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_2G_patch";
	Locations[n].models.day.fonar = "inside_cabin_2G_fd";
	Locations[n].models.day.rays = "inside_cabin_2G_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_2G_patch";
	Locations[n].models.night.fonar = "inside_cabin_2G_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

    // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;
	
	// каюта ЛГ проклятый
	n = FindLocation("CabineFDM");
	
	DeleteAttribute(&Locations[n], "models");
	SetDefaultLightingModels(n);
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_C1"; // каюта Калеуче (проклятый)
	//Always
	Locations[n].models.always.main = "inside_cabin_C1";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_C1_parts";
	//Locations[n].models.always.outside = "inside_cabin_C1_outside";
	Locations[n].models.always.locators = "inside_cabin_C1_locators";
	Locations[n].models.always.bsp = "inside_cabin_C1_bsp";
	Locations[n].models.always.camcollider = "inside_cabin_C1_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_C1_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_C1_patch";
	Locations[n].models.day.fonar = "inside_cabin_C1_fd";
	Locations[n].models.day.rays = "inside_cabin_C1_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_C1_patch";
	Locations[n].models.night.fonar = "inside_cabin_C1_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";
	
	Locations[n].boarding.Loc.Hero = "loc0";
    Locations[n].boarding.Loc.Capt = "aloc1";

    // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;
	
	// каюта ЛГ проклятый
	n = FindLocation("My_CabineFDM");
	
	DeleteAttribute(&Locations[n], "models");
	SetDefaultLightingModels(n);
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_C1"; // каюта Калеуче (проклятый)
	//Always
	Locations[n].models.always.main = "inside_cabin_C1";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_C1_parts";
	//Locations[n].models.always.outside = "inside_cabin_C1_outside";
	Locations[n].models.always.locators = "inside_cabin_C1_locators";
	Locations[n].models.always.bsp = "inside_cabin_C1_bsp";
	Locations[n].models.always.camcollider = "inside_cabin_C1_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_C1_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_C1_patch";
	Locations[n].models.day.fonar = "inside_cabin_C1_fd";
	Locations[n].models.day.rays = "inside_cabin_C1_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_C1_patch";
	Locations[n].models.night.fonar = "inside_cabin_C1_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

    // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;
	
	ExpandLocationsArray();
	n = MAX_LOCATIONS - 1;
	
	//абордажная каюта ЛГ RENOVATED
  	Locations[n].id = "CabineFDMR"; 
    locations[n].id.label = "cabine";
	locations[n].image = "loading\Capdeck_" + rand(4) + ".tga";
	//Sound
	locations[n].type = "boarding_cabine";
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_C2"; // каюта Калеуче (отремонтирован)
	//Always
	Locations[n].models.always.main = "inside_cabin_C2";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_C2_parts";
	//Locations[n].models.always.outside = "inside_cabin_C2_outside";
	Locations[n].models.always.locators = "inside_cabin_C2_locators";
	Locations[n].models.always.bsp = "inside_cabin_C2_bsp";
	Locations[n].models.always.camcollider = "inside_cabin_C2_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_C2_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_C2_patch";
	Locations[n].models.day.fonar = "inside_cabin_C2_fd";
	Locations[n].models.day.rays = "inside_cabin_C2_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_C2_patch";
	Locations[n].models.night.fonar = "inside_cabin_C2_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

    // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;

	Locations[n].boarding = "true";
	Locations[n].boarding.nextdeck = "";
	//Locations[n].camshuttle = 1;
	Locations[n].boarding.locatorNum = 1;
	Locations[n].CabinType = true;
	locations[n].environment.weather.rain = false;
	Locations[n].boarding.Loc.Hero = "loc0";
    Locations[n].boarding.Loc.Capt = "aloc1";
	
	ExpandLocationsArray();
	n = MAX_LOCATIONS - 1;
	
	// RENOVATED
	Locations[n].id = "My_CabineFDMR"; 
    locations[n].id.label = "cabine";
	locations[n].image = "loading\Capdeck_" + rand(4) + ".tga";
	//Sound
	locations[n].type = "residence";
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_C2"; // каюта Калеуче (отремонтирован)
	//Always
	Locations[n].models.always.main = "inside_cabin_C2";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_C2_parts";
	//Locations[n].models.always.outside = "inside_cabin_C2_outside";
	Locations[n].models.always.locators = "inside_cabin_C2_locators";
	Locations[n].models.always.bsp = "inside_cabin_C2_bsp";
	Locations[n].models.always.camcollider = "inside_cabin_C2_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_C2_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_C2_patch";
	Locations[n].models.day.fonar = "inside_cabin_C2_fd";
	Locations[n].models.day.rays = "inside_cabin_C2_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_C2_patch";
	Locations[n].models.night.fonar = "inside_cabin_C2_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

    // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	Locations[n].locators_radius.box.box2 = 0.5; // гардероб
	Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;

	Locations[n].boarding = "true";
	//Locations[n].camshuttle = 1;
	
	locations[n].box1 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box2 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box3 = Items_MakeTime(0, 1, 1, 2003);
	//locations[n].box4 = Items_MakeTime(0, 1, 1, 2003);

    LAi_LocationFightDisable(&Locations[n], true);
	Locations[n].locators_radius.randitem.randitem1 = 1;
    Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "My_Deck";
	Locations[n].reload.l1.emerge = "reload1";
	Locations[n].reload.l1.label = "Deck.";
	Locations[n].items.randitem1 = "";
	locations[n].environment.weather.rain = false;
	
	ref refShip;
	
	makeref(refShip,ShipsTypes[SHIP_GALEON_H]);
	refShip.CabinType = "Cabin_huge";
	makeref(refShip,ShipsTypes[SHIP_GALEON_SM]);
	refShip.CabinType = "Cabin_huge";
	makeref(refShip,ShipsTypes[SHIP_NAVIO]);
	refShip.CabinType = "Cabin_huge";
	makeref(refShip,ShipsTypes[SHIP_ELCASADOR]);
	refShip.CabinType = "Cabin_huge";
	makeref(refShip,ShipsTypes[SHIP_RENOVATED_FDM]);
	refShip.Name            			= "NewFlyingdutchman";  
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(1500);
	refShip.Capacity        			= 7700;
	refShip.CannonsQuantity				= 62;	// 6,4,26,26
	refShip.CannonsQuantityMax          = 62;
	refShip.CannonsQuantityMin			= 62;
	refShip.rcannon 					= 26;
	refShip.lcannon 					= 26;
	refShip.fcannon 					= 6;
	refShip.bcannon 					= 4;		
	refShip.MaxCrew         			= 735;
	refShip.OptCrew         			= 588;
	refShip.MinCrew         			= 147;	
	refShip.SpeedRate					= 9.75;
	refShip.TurnRate        			= 42.0;
	refShip.Price           			= 200000;
	refShip.HP              			= 8950;
	refShip.SP              			= 100;
	refship.EmblemedSails.normalTex 	= "ships/parus_silk.tga";	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.Spec                		= SHIP_SPEC_WAR;
	refship.QuestShip					= true; 
	
	refShip.lowpolycrew 				= 24;	
	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
	
	refship.WaterLine					= -0.3;

	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   			= 0.72;
	
	refship.CabinType          			= "CabineFDMR"; 
	refship.DeckType           			= "Big";
	
	refShip.cannonr  = refShip.rcannon;
	refShip.cannonl  = refShip.lcannon;
	refShip.cannonf  = refShip.fcannon;
	refShip.cannonb  = refShip.bcannon;
	
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
		
		if(sti(RealShips[i].BaseType) == SHIP_GALEON_H)
			RealShips[i].CabinType = "Cabin_huge";
		if(sti(RealShips[i].BaseType) == SHIP_GALEON_SM)
			RealShips[i].CabinType = "Cabin_huge";
		if(sti(RealShips[i].BaseType) == SHIP_NAVIO)
			RealShips[i].CabinType = "Cabin_huge";
		if(sti(RealShips[i].BaseType) == SHIP_ELCASADOR)
			RealShips[i].CabinType = "Cabin_huge";
		if(sti(RealShips[i].BaseType) == SHIP_RENOVATED_FDM)
		{
			RealShips[i].Class						= 2;
			RealShips[i].Cannon          			= CANNON_TYPE_CANNON_LBS32;
			RealShips[i].MaxCaliber      			= 42;
			RealShips[i].Weight						= Tonnes2CWT(1500);
			RealShips[i].Capacity        			= 7700;
			RealShips[i].CannonsQuantity			= 62;	// 6,4,26,26
			RealShips[i].CannonsQuantityMax         = 62;
			RealShips[i].CannonsQuantityMin			= 62;
			RealShips[i].rcannon 					= 26;
			RealShips[i].lcannon 					= 26;
			RealShips[i].fcannon 					= 6;
			RealShips[i].bcannon 					= 4;		
			RealShips[i].MaxCrew         			= 735;
			RealShips[i].OptCrew         			= 588;
			RealShips[i].MinCrew         			= 147;	
			RealShips[i].SpeedRate					= 9.75;
			RealShips[i].TurnRate        			= 42.0;
			RealShips[i].Price           			= 200000;
			RealShips[i].HP              			= 8950;
			RealShips[i].SP              			= 100;
			RealShips[i].EmblemedSails.normalTex 	= "ships/parus_silk.tga";	
			RealShips[i].Type.Merchant				= false;
			RealShips[i].Type.War					= true;
			RealShips[i].Spec                		= SHIP_SPEC_WAR;
			RealShips[i].QuestShip					= true; 
			
			RealShips[i].lowpolycrew 				= 24;	
			RealShips[i].Rocking.y 					= 0.5;
			RealShips[i].Rocking.az 				= 0.035;
			
			RealShips[i].WaterLine					= -0.3;

			RealShips[i].SpeedDependWeight			= 0.35;
			RealShips[i].SubSeaDependWeight			= 1.0;
			RealShips[i].TurnDependWeight			= 0.4;
			RealShips[i].WindAgainstSpeed   			= 0.72;
			
			RealShips[i].CabinType          			= "CabineFDMR"; 
			RealShips[i].DeckType           			= "Big";
			
			RealShips[i].cannonr  = RealShips[i].rcannon;
			RealShips[i].cannonl  = RealShips[i].lcannon;
			RealShips[i].cannonf  = RealShips[i].fcannon;
			RealShips[i].cannonb  = RealShips[i].bcannon;
		}
	}

	SpyGlassUpdate_0029();
}

void SpyGlassUpdate_0029()
{
	ref item;
	item = ItemsFromId("spyglass1");
	item.worldMapBonus = 0;
	item.radius = 350.0;
	item = ItemsFromId("spyglass2");
	item.worldMapBonus = 10;
	item.radius = 500.0;
	item = ItemsFromId("spyglass3");
	item.worldMapBonus = 10;
	item.radius = 650.0;
	item = ItemsFromId("spyglass4");
	item.worldMapBonus = 18;
	item.radius = 1000.0;
	item = ItemsFromId("spyglass5");
	item.worldMapBonus = 25;
	item.radius = 1609.0;
	item = ItemsFromId("spyglassSP3");
	item.worldMapBonus = 14;
	item.radius = 666.0;
}