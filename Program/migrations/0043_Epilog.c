void ApplyMigration(ref migrationState)
{
	Epilog_Locations();
	Epilog_FixLongHappy();
}

void Epilog_Locations()
{
	int n;
	
	//////////////////////////////////////////////////////////////////////
	// Франция, поместье де Монпе
	//////////////////////////////////////////////////////////////////////
	ExpandLocationsArray();
	n = MAX_LOCATIONS - 1;
	locations[n].id = "EstateDM1";
	locations[n].id.label = "DeMonpe_Estate";
	locations[n].filespath.models = "locations\Estate";
	locations[n].image = "loading\EstateN.tga";
	//Sound
	locations[n].type = "europe";
	locations[n].islandId = "Europe";
	locations[n].countryId = "France";
	//Models
	//Always
	locations[n].models.always.estate = "estate";
	
	locations[n].models.always.windows = "estate_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";	
	Locations[n].models.always.windows.level = 66532;	
	//VolumeLight	
	Locations[n].models.always.vlight = "estate_vlight";
	Locations[n].models.always.vlight.uvslide.v0 = 0.05;
    Locations[n].models.always.vlight.uvslide.v1 = 0.0;
	Locations[n].models.always.vlight.tech = "LocationWaterFall";
	Locations[n].models.always.vlight.level = 99950;
	
	locations[n].models.always.locators = "estate_locators";
	locations[n].models.always.grassPatch = "estate_grass";
	//Day
	locations[n].models.day.charactersPatch = "estate_patch";
	locations[n].models.day.fonar = "estate_fd";
	//Night
	locations[n].models.night.charactersPatch = "estate_patch";
	locations[n].models.night.fonar = "estate_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "EstateDM1_Kitchen";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Bedroom";
	
	locations[n].locators_radius.item.item1 = 1.0;
	
	//////////////////////////////////////////////////////////////////////
	// Франция, поместье де Монпе - столовая
	//////////////////////////////////////////////////////////////////////
	ExpandLocationsArray();
	n = MAX_LOCATIONS - 1;
	locations[n].id = "EstateDM1_Kitchen";
	locations[n].id.label = "DeMonpe_Estate";
	Locations[n].filespath.models = "Locations\EstateRooms\EstateKitchen";
	locations[n].image = "loading\EstateRoomN.tga";		
	//Models
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Europe";
	locations[n].countryId = "France";
	//Always
	Locations[n].models.always.main = "EstateKitchen";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "EstateKitchen_parts";
	Locations[n].models.always.outside = "EstateKitchen_outside";
	Locations[n].models.always.locators = "EstateKitchen_locators";
	locations[n].models.always.grassPatch = "EstateKitchen_grass";
	locations[n].models.always.window = "EstateKitchen_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "EstateKitchen_patch";
	//Night
	Locations[n].models.night.charactersPatch = "EstateKitchen_patch";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "EstateDM1";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "DeMonpe_Estate";
	
	//////////////////////////////////////////////////////////////////////
	// Квестовая каюта на Улисс
	//////////////////////////////////////////////////////////////////////
	n = FindLocation("Quest_Cabin_Medium");
	DeleteAttribute(&Locations[n], "models");
	Locations[n].id.label = "cabine";
	Locations[n].filespath.models = "locations\decks\inside_cabin_3";
    Locations[n].image = "loading\Capdeck_" + rand(4) + ".tga";
	//Sound
	Locations[n].type = "residence";
	//Models
	//Always
	Locations[n].models.always.main = "inside_cabin_3";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_3_parts";
	Locations[n].models.always.locators = "inside_cabin_3_locators_quest";
	Locations[n].models.always.camcollider = "inside_cabin_3_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.bsp = "inside_cabin_3_bsp";
	Locations[n].models.always.windows = "inside_cabin_3_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_3_patch";
	Locations[n].models.day.fonar = "inside_cabin_3_fd";
	Locations[n].models.day.rays = "inside_cabin_3_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_3_patch";
	Locations[n].models.night.fonar = "inside_cabin_3_fn";

	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

    Locations[n].locators_radius.randitem.randitem1 = 1;
    Locations[n].locators_radius.randitem.randitem2 = 1;

    Locations[n].locators_radius.rld.loc0 = 0.5;
    Locations[n].locators_radius.rld.loc1 = 0.5;
    Locations[n].locators_radius.rld.loc2 = 0.5;
    Locations[n].locators_radius.rld.aloc0 = 0.5;
    Locations[n].locators_radius.rld.aloc1 = 0.5;
    Locations[n].locators_radius.rld.aloc2 = 0.5;
	Locations[n].locators_radius.item.item1 = 1.0;
	Locations[n].locators_radius.item.item2 = 1.0;

    LAi_LocationFightDisable(&Locations[n], true);

    Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Quest_Ship_deck_Medium_trade";
	Locations[n].reload.l1.emerge = "reload_cabin";
	Locations[n].reload.l1.label = "Boarding deck";

	Locations[n].items.randitem2 = "";
	Locations[n].items.randitem1 = "";

	Locations[n].boarding = "true";
	locations[n].environment.weather.rain = false;
}

void Epilog_FixLongHappy()
{
	if (CheckAttributeEqualTo(pchar, "questTemp.LongHappy", "end"))
	{
		// Бейкер
		if (GetCharacterIndex("Baker") != -1)
		{
			ReturnOfficer_Baker();
		}
		// офицер Гамбита
		if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
		{
			if (pchar.questTemp.LongHappy.HambitOfficer == "Longway") ReturnOfficer_Longway();
			if (pchar.questTemp.LongHappy.HambitOfficer == "Knippel") ReturnOfficer_Knippel();
			if (pchar.questTemp.LongHappy.HambitOfficer == "Tonzag") ReturnOfficer_Tonzag();
		}
		// Тичингиту
		if (GetCharacterIndex("Tichingitu") != -1)
		{
			ReturnOfficer_Tichingitu();
		}
	}
}
