
void ApplyMigration(ref migrationState)
{
	ClockTower_Sp4();
	Amsterdam();
	InitPistol_SP4();
	ReapplyPerksItems0037();
}

// Обновляем перки/дескрипторы
void ReapplyPerksItems0037()
{
	InitPerks();

	if(LoadSegment("items\modifiers\init\init.c"))
	{
		InitModifiers();
		UnloadSegment("items\modifiers\init\init.c");
	}

	object fellows = GetAllFellows(pchar, true);
	for (int i=0; i < GetAttributesNum(&fellows); i++)
	{
		int idx = sti(GetAttributeValue(GetAttributeN(&fellows, i)));
		ref chr = GetCharacter(idx);
		if (!CheckAttribute(chr, "perks.list")) continue;
		ReapplyAllPerks(chr);
	}
	trace("Применили фикс перков/предметов");
}


void InitPistol_SP4()
{
	ref gun = ItemsFromID("pistol15");
	gun.chargeQ = 1;
	gun.weight = 1.4;
	gun.cost = 72000;
	gun.model = "pistol15";
	gun.picIndex = 4;
	gun.picTexture = "ITEMS_42";

	InitGunExt_SP4("pistol15", "t1", "cartridge",     "",          109.0, 138.0, 0.0, 0, 2,  19, 0);
	InitGunExt_SP4("pistol15", "t2", "bullet",        "gunpowder", 95.0, 120.0,  0.0, 0, 2,  25, 1);
	InitGunExt_SP4("pistol15", "t3", "bullet_double", "",          190.0, 240.0, 0.0, 0, 0,  12, 0);
}

void InitGunExt_SP4(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin,   
				float  DmgMax,
				float  EnergyP, 
				bool   MultiDamage, 
				int    MisFire,     
				int    ChargeSpeed, 
				bool   isDefault )
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).bullet 		= sBullet;
	gun.type.(sAttr).gunpowder 		= sGunPowder;
	gun.type.(sAttr).DmgMin			= DmgMin;
	gun.type.(sAttr).DmgMax			= DmgMax;
	gun.type.(sAttr).EnergyP		= EnergyP;
	gun.type.(sAttr).multidmg       = MultiDamage;
	gun.type.(sAttr).misfire        = MisFire;
	gun.type.(sAttr).ChargeSpeed    = ChargeSpeed;
	gun.type.(sAttr).Default        = isDefault;
}

void ClockTower_Sp4()
{
	int n;
	
	ExpandLocationsArray();
	n = MAX_LOCATIONS - 1;
	locations[n].id = "Villemstad_ClockTower";
	locations[n].id.label = "HWIC_flat";
	locations[n].image = "loading\inside\smallresidence.tga";
	locations[n].HWIC = true;
	locations[n].CannotWait = true;
    locations[n].SpecialHandlers.l1 = "HWIC_SetClockSound";
	//Town sack
	locations[n].townsack = "Villemstad";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	//locations[n].fastreload = "Villemstad";
 	locations[n].islandId = "Curacao";
	//Models
	Locations[n].filespath.models = "Locations\Inside\ClockTower"; // Контора корабельного учёта
	//Always
	Locations[n].models.always.main = "ClockTower";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "ClockTower_parts";
	Locations[n].models.always.outside = "ClockTower_outside";
	Locations[n].models.always.bsp = "ClockTower_bsp";
	Locations[n].models.always.camcollider = "ClockTower_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "ClockTower_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	Locations[n].models.always.dust = "ClockTower_dust"; // пыль
	Locations[n].models.always.dust.uvslide.v0 = 0.08;
	Locations[n].models.always.dust.uvslide.v1 = 0.0;
	Locations[n].models.always.dust.tech = "LocationWaterFall";
	Locations[n].models.always.dust.level = 99950;
	//Day
	Locations[n].models.day.locators = "ClockTower_locators_D";
	Locations[n].models.day.charactersPatch = "ClockTower_patch";
	Locations[n].models.day.fonar = "ClockTower_fd";
	Locations[n].models.day.rays = "ClockTower_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.locators = "ClockTower_locators_N";
	Locations[n].models.night.charactersPatch = "ClockTower_patch";
	Locations[n].models.night.fonar = "ClockTower_fn";
	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Villemstad_town";
	locations[n].reload.l1.emerge = "HouseO2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Villemstad_ClockCellar";
	locations[n].reload.l2.emerge = "Reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Van Doorn's Cellar";
	locations[n].reload.l2.disable = 1;
	
	LAi_LocationFightDisable(&locations[n], true);
	
	n = FindLocation("Villemstad_town");
	locations[n].reload.l12.name = "HouseO2";
	locations[n].reload.l12.go = "Villemstad_ClockTower";
	locations[n].reload.l12.emerge = "reload1";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "Office of Naval Registry";
	
	DeleteAttribute(&locations[n], "reload.l12.close_for_night");
	locations[n].reload.l12.close_for_alarm = 1;
	
	n = FindLocation("GVIK");
    locations[n].SpecialHandlers.l1 = "HWIC_SetClockSound";
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "GVIK";
	locations[n].reload.l4.emerge = "reload4";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "residence";
	locations[n].reload.l4.disable  = true;

    n = FindLocation("GVIK_residence");
	locations[n].SpecialHandlers.l1 = "HWIC_SetClockSound";

	ExpandLocationsArray();
	n = MAX_LOCATIONS - 1;
	
	locations[n].id = "Villemstad_ClockCellar";
	locations[n].image = "loading\inside\sklad.tga";
	locations[n].id.label = "Office of Naval Registry";
	locations[n].HWIC = true;
	locations[n].CannotWait = true;
    locations[n].SpecialHandlers.l1 = "HWIC_SetClockSound";
	//Sound
	locations[n].townsack = "Villemstad";
	locations[n].type = "house";
	//locations[n].fastreload = "Villemstad";
	locations[n].islandId = "Curacao";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\WineCellar";
	locations[n].models.always.WineCellar = "WineCellar";
	locations[n].models.always.WineCellar_parts = "WineCellar_parts";
	locations[n].models.always.WineCellar_Room = "WineCellar_RoomClosed";
	locations[n].models.always.locators = "WineCellar_locators";
	//Day
	//locations[n].models.day.charactersPatch = "WineCellar_RoomOpened_patch";
	locations[n].models.day.charactersPatch = "WineCellar_RoomClosed_patch";
	//Night
	//locations[n].models.night.charactersPatch = "WineCellar_RoomOpened_patch";
	locations[n].models.night.charactersPatch = "WineCellar_RoomClosed_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
 	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Villemstad_ClockTower";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Office of Naval Registry";
}

void Amsterdam()
{
	ref refShip;
	
	makeref(refShip,ShipsTypes[SHIP_AMSTERDAM]);
	refShip.Name            			= "Amsterdam";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(920);
	refShip.Capacity        			= 5000;
	refShip.CannonsQuantity				= 42;	// 2,4,18,18
	refShip.CannonsQuantityMin			= 42;
	refShip.rcannon 					= 18;
	refShip.lcannon 					= 18;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 4;
	
	refShip.MaxCrew         			= 481;
	refShip.OptCrew         			= 385;
	refShip.MinCrew         			= 96;
	
	refShip.SpeedRate       			= 12.15;
	refShip.TurnRate        			= 45.2;
	refShip.Price           			= 95000;
	refShip.HP              			= 5200;
	refShip.SP              			= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.Spec                		= SHIP_SPEC_RAIDER;
	refship.QuestShip					= true;
	refship.QuestSP						= true;

	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;	
	refship.WaterLine					= -1.7;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 0.62;
	refship.CabinType          			= "Cabin"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.4;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 5.3;	refShip.Height.Grapes.DY	= 1.575;
	refShip.Height.Knippels.Y			= 19.5;	refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 3.4;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";	

	refship.icons.FirstIconPos = 12+5*16;
	refship.icons.SecondIconPos = 12+5*16 + 1;
	
	refShip.cannonr  = refShip.rcannon;
	refShip.cannonl  = refShip.lcannon;
	refShip.cannonf  = refShip.fcannon;
	refShip.cannonb  = refShip.bcannon;
	
	DeleteAttribute(refship, "ShipHolder");
	
	makeref(refShip,ShipsTypes[SHIP_FRIGATE]);
	refShip.CannonsQuantity				= 42;
	refShip.CannonsQuantityMin			= 36;
	refShip.rcannon 					= 16;
	refShip.lcannon 					= 16;
	refShip.cannonr  = refShip.rcannon;
	refShip.cannonl  = refShip.lcannon;
	refShip.cannonf  = refShip.fcannon;
	refShip.cannonb  = refShip.bcannon;
	refShip.Capacity        			= 4100;
	refShip.SpeedRate       			= 10.25;
	refShip.TurnRate        			= 42.0;
	refShip.HP              			= 3900;
	
	makeref(refShip,ShipsTypes[SHIP_GALEON_H]);
	refShip.MaxCaliber      			= 32;
	
	makeref(refShip,ShipsTypes[SHIP_FRIGATE_H]);
	refShip.MaxCaliber      			= 24;
	
}
