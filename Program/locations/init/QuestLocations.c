

int LocationInitQuestLocations(int n)
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Локация клон
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Clone_location";
	locations[n].id.label = "Farm Field";
	locations[n].filespath.models = "locations\";
	locations[n].image = "loading\Farmfield.tga";
	//Sound
	locations[n].type = "land";
	//Models
	//Always
	locations[n].models.always.house = "farmfield";
	locations[n].models.always.locators = "farmfield_locators";
	locations[n].models.always.grassPatch = "farmfield_grass";

	locations[n].models.always.plan = "farmfield_plan";
	locations[n].models.always.plan.level = 9;

	//Day
	locations[n].models.day.charactersPatch = "farmfield_patch";
	locations[n].models.day.fonar = "farmfield_fd";

	//Night
	locations[n].models.night.charactersPatch = "farmfield_patch";
	locations[n].models.night.fonar = "farmfield_fn";

	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_tavern";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Cob_house";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "House";

	n = n + 1;
	
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Локация клон 1
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Clone_location_1";
	locations[n].id.label = "Farm Field";
	locations[n].filespath.models = "locations\";
	locations[n].image = "loading\Farmfield.tga";
	//Sound
	locations[n].type = "land";
	//Models
	//Always
	locations[n].models.always.house = "farmfield";
	locations[n].models.always.locators = "farmfield_locators";
	locations[n].models.always.grassPatch = "farmfield_grass";

	locations[n].models.always.plan = "farmfield_plan";
	locations[n].models.always.plan.level = 9;

	//Day
	locations[n].models.day.charactersPatch = "farmfield_patch";
	locations[n].models.day.fonar = "farmfield_fd";

	//Night
	locations[n].models.night.charactersPatch = "farmfield_patch";
	locations[n].models.night.fonar = "farmfield_fn";

	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_tavern";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Cob_house";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "House";

	n = n + 1;
	
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Локация клон 2
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Clone_location_2";
	locations[n].id.label = "Farm Field";
	locations[n].filespath.models = "locations\";
	locations[n].image = "loading\Farmfield.tga";
	//Sound
	locations[n].type = "land";
	//Models
	//Always
	locations[n].models.always.house = "farmfield";
	locations[n].models.always.locators = "farmfield_locators";
	locations[n].models.always.grassPatch = "farmfield_grass";

	locations[n].models.always.plan = "farmfield_plan";
	locations[n].models.always.plan.level = 9;

	//Day
	locations[n].models.day.charactersPatch = "farmfield_patch";
	locations[n].models.day.fonar = "farmfield_fd";

	//Night
	locations[n].models.night.charactersPatch = "farmfield_patch";
	locations[n].models.night.fonar = "farmfield_fn";

	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_tavern";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Town";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Cob_house";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "House";

	n = n + 1;
	
	////////////////////////////////////////////////////////////
	/// Корабельная палуба  для карта - море
	////////////////////////////////////////////////////////////
	Locations[n].id = "Ship_deck";
	Locations[n].image = "loading\art\open_sea_clear.tga";
	locations[n].id.label = "Boarding deck";
	//Sound
	Locations[n].type = "deck";
	// нельзя, иначе нет моря Locations[n].boarding = "true";
	Locations[n].lockCamAngle = 0.4;
	//Locations[n].camshuttle = 1;
	//Models
	//Always
	Locations[n].filespath.models = "locations\decks\deckMedium";
	Locations[n].models.always.deckMedium = "deckMedium";
	Locations[n].models.always.locators = "deckMedium_locators";
	//Day
	locations[n].models.day.charactersPatch = "deckMedium_patch";
	Locations[n].models.day.deckMediumFonarsDay = "deckMedium_fd";
	//Night
	locations[n].models.night.charactersPatch = "deckMedium_patch";
	Locations[n].models.night.deckMediumFonarsNight= "deckMedium_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";

	n = n + 1;
	
	////////////////////////////////////////////////////////////
	/// Корабельная палуба  для море - море
	////////////////////////////////////////////////////////////
    //ID
	Locations[n].id = "Deck_Near_Ship";   // выслать туда шлюпку
	Locations[n].id.label = "Boarding deck";
	//Info
	Locations[n].image = "loading\Quarter_" + rand(1) + ".tga";
	//Sound
	Locations[n].type = "residence";
	Locations[n].boarding = "true";
	Locations[n].lockCamAngle = 0.4;
	//Locations[n].camshuttle = 1;
	//Models
	//Always
	Locations[n].filespath.models = "locations\decks\deckMedium";
	Locations[n].models.always.deckMedium = "deckMedium";
	Locations[n].models.always.locators = "deckMedium_locators";
	//Day
	locations[n].models.day.charactersPatch = "deckMedium_patch";
	Locations[n].models.always.deckMediumFonarsDay = "deckMedium_fd";
	//Night
	locations[n].models.night.charactersPatch = "deckMedium_patch";
	Locations[n].models.always.deckMediumFonarsNight= "deckMedium_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;
	
	////////////////////////////////////////////////////////////
	/// Квестовая корабельная палуба  для море - море
	////////////////////////////////////////////////////////////
    //ID
	Locations[n].id = "Deck_Galeon_Ship";   // выслать туда шлюпку
	Locations[n].id.label = "Boarding deck";
	//Info
	Locations[n].image = "loading\Quarter_" + rand(1) + ".tga";
	//Sound
	Locations[n].type = "residence";
	//Locations[n].boarding = "true";
	Locations[n].lockCamAngle = 0.4;
	//Locations[n].camshuttle = 1;
	//Models
	//Always
	Locations[n].filespath.models = "locations\decks\deck01";
	Locations[n].models.always.deckGaleon = "deck01";
	Locations[n].models.always.locators = "deck01_locators";
	locations[n].models.always.charactersJumpPatch = "deck01_jump_patch";
	Locations[n].models.always.Fonars = "deck01_fonars";
	Locations[n].models.always.alpha = "deck01_alpha";
	Locations[n].models.always.window = "deck01_window";
	//Day
	locations[n].models.day.charactersPatch = "deck01_patch";
	//Night
	locations[n].models.night.charactersPatch = "deck01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;

  	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Имение Оглторпа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Estate";
	locations[n].id.label = "Estate";
	locations[n].filespath.models = "locations\Estate";
	locations[n].image = "loading\EstateN.tga";
	//Sound
	locations[n].type = "europe";
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
	Locations[n].QuestlockWeather = "20 Hour";
	Locations[n].QuestlockWeather.hours = 20;
	Locations[n].QuestlockWeather.minutes = 00;
	//Reload map
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "EstateBadRoom1";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Bedroom";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "EstateBadRoom2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Bedroom";

	locations[n].reload.l3.name = "reload5";
	locations[n].reload.l3.go = "EstateOffice";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Cabinet";
	locations[n].locators_radius.item.item1 = 1.0;
	
	locations[n].private1.key = "key3";
	locations[n].private1.key.delItem = true;
	locations[n].private1.items.blade_03 = 1;
	locations[n].private1.items.pistol1 = 1;
	locations[n].private1.items.bullet = 10;
	locations[n].private1.items.GunPowder = 10;
	n = n + 1;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Спальня #1 Оглторпа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "EstateBadRoom1";
	locations[n].id.label = "Bedroom";
	locations[n].filespath.models = "locations\EstateRooms\EstateBadRoom1";
	locations[n].image = "loading\EstateRoomN.tga";		
	//Models
	//Sound
	locations[n].type = "house";
	//Always
	locations[n].models.always.estateBadRoom = "estateBadRoom1";	
	locations[n].models.always.windows = "estateBadRoom1_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66532;	
	//VolumeLight	
	Locations[n].models.always.vlight = "estateBadRoom1_vlight";
	Locations[n].models.always.vlight.uvslide.v0 = 0.05;
    Locations[n].models.always.vlight.uvslide.v1 = 0.0;
	Locations[n].models.always.vlight.tech = "LocationWaterFall";
	Locations[n].models.always.vlight.level = 99950;
	
	locations[n].models.always.locators = "estateBadRoom1_locators";
	locations[n].models.always.grassPatch = "estateRooms_grass";
	//Day
	locations[n].models.day.charactersPatch = "estateBadRoom1_patch";
	locations[n].models.day.fonar = "estateRooms_fd";
	//Night
	locations[n].models.night.charactersPatch = "estateBadRoom1_patch";
	locations[n].models.night.fonar = "estateRooms_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	Locations[n].QuestlockWeather = "20 Hour";	
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Estate";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Estate";
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Подводная Локация
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "UnderWater";
	locations[n].id.label = "UnderWater";
	locations[n].filespath.models = "locations\UnderWater";	
	locations[n].image = "loading\UnderWater_" + rand(1) + ".tga";
	//Sound	
	locations[n].type = "underwater";
	locations[n].type.LSC = true; //локация ГПК
	locations[n].dolly = 2;
	//Models
	//Always	
	Locations[n].models.always.UnderWater = "UnderWater";
	Locations[n].models.always.UnderWater.tech = "DLightModel";	
	
	Locations[n].models.always.outside = "UnderWater_outside";
	Locations[n].models.always.outside.tech = "DLightModel";
			
	Locations[n].models.always.reflect = "UnderWater_reflect";
	Locations[n].models.always.reflect.tech = "DLightModel";	
	Locations[n].models.always.reflect.sea_reflection = 1;
		
	Locations[n].models.always.sails = "UnderWater_sails";	
	Locations[n].models.always.sails.tech = "DLightModel";
		
	Locations[n].models.always.plants = "UnderWater_plants";	
	Locations[n].models.always.plants.tech = "DLightModel";
	//Locations[n].models.always.plants.tech = "LocationWindows";
	//Locations[n].models.always.plants.level = 66532;
		
	Locations[n].models.always.plan1 = "Plan1";
	Locations[n].models.always.plan1.sea_reflection = 1;
		
	Locations[n].models.always.plan2 = "Plan2";
		
	Locations[n].models.always.locators = "UnderWater_locators";	
	
	Locations[n].models.always.grassPatch = "UnderWater_grass";
	Locations[n].models.always.grassPatch.texture = "grass\algaeU2.tga.tx";						
	//Day
	locations[n].models.day.charactersPatch = "UnderWater_patch_day";
	//Night
	locations[n].models.night.charactersPatch = "UnderWater_patch_day";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	locations[n].underwater = true;
	Locations[n].QuestlockWeather = "Underwater";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LostShipsCity_town";
	locations[n].reload.l1.emerge = "reload73";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "LSC Town";

	locations[n].DisableOfficers = "1";

	locations[n].locators_radius.reload.reload1 = 2.0;
	locations[n].locators_radius.item.dolly2 = 1.0;
	locations[n].locators_radius.item.item1 = 0.6;
	locations[n].locators_radius.item.item2 = 0.6;
	locations[n].locators_radius.item.item3 = 0.6;
	locations[n].locators_radius.item.item4 = 0.6;
	locations[n].locators_radius.item.item5 = 0.6;

	//в сундуках
	locations[n].private1.items.gold_dublon = 154;
	locations[n].private1.items.jewelry5 = 166;
	locations[n].private1.items.jewelry6 = 211;
	locations[n].private1.items.jewelry10 = 3;
	
	locations[n].private2.money = 38745;
	locations[n].private2.items.jewelry1 = 90;
	locations[n].private2.items.jewelry2 = 65;
	locations[n].private2.items.jewelry3 = 144;
	locations[n].private2.items.jewelry4 = 48;
	locations[n].private2.items.jewelry8 = 72;

	locations[n].private3.key = "key3";
	locations[n].private3.skel = true;
	locations[n].private3.money = 58931;
	locations[n].private3.items.jewelry40 = 101;
	locations[n].private3.items.jewelry41 = 88;
	locations[n].private3.items.jewelry42 = 52;
	locations[n].private3.items.jewelry43 = 67;
	locations[n].private3.items.jewelry46 = 115;
	locations[n].private3.items.jewelry48 = 195;
	locations[n].private3.items.jewelry50 = 21;
	locations[n].private3.items.jewelry52 = 954;
	locations[n].private3.items.jewelry53 = 2087;

	locations[n].private4.key = "key3";
	locations[n].private4.skel = true;
	locations[n].private4.items.icollection = 2;
	locations[n].private4.items.Chest = 3;
	locations[n].private4.items.jewelry8 = 57;
	locations[n].private4.items.talisman8 = 1;

	locations[n].private5.money = 60802;
	locations[n].private5.items.jewelry5 = 220;
	locations[n].private5.items.jewelry6 = 310;

	locations[n].private6.items.gold_dublon = 100;
	locations[n].private6.items.jewelry5 = 10;
	locations[n].private6.items.jewelry6 = 2000;
	locations[n].private6.items.jewelry10 = 33;

	locations[n].private7.key = "key_betancur"; // сундук Бетанкура
	locations[n].private7.key.delItem = true;
	locations[n].private7.money = 100000; 
	locations[n].private7.items.gold_dublon = 500;
	locations[n].private7.items.icollection = 12; // чтоб удавиться от жадности
	locations[n].private7.items.jewelry5 = 400;
	locations[n].private7.items.jewelry6 = 1000;
	locations[n].private7.items.jewelry10 = 19;
	locations[n].private7.items.talisman1 = 1;

	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Спецлокация
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Terrain";
	//locations[n].image = "loading\outside\jungle_" + rand(2) + ".tga";
	locations[n].MustSetReloadBack = true;
	//Sound
	locations[n].type = "shore";
	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Terrain";
	Locations[n].models.always.Terrain = "Terrain";	
	Locations[n].models.always.locators = "Terrain_locators";
	//Day
	locations[n].models.day.charactersPatch = "Terrain_patch";
	//Night
	locations[n].models.night.charactersPatch = "Terrain_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Улицы поселения Зееланда, Остров Формоза
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Formosa";
	locations[n].id.label = "Zeelanda";
	
	locations[n].filespath.models = "locations\Town_Formosa\Town\";
	locations[n].image = "loading\Town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//Sound
	locations[n].type = "town";
	//Models
	//Always
	locations[n].models.always.town = "Curacao";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.L1 = "Curacao_signsA";
	locations[n].models.always.L2 = "Curacao_signsB";
    locations[n].models.always.L2.tech = "DLightModel"
	locations[n].models.always.locators = "Curacao_locators";
	locations[n].models.always.grassPatch = "Curacao_grass";
	locations[n].models.always.seabed = "Curacao_sb";

	//River
	locations[n].models.always.Waterfall1 = "river1";
	locations[n].models.always.Waterfall1.uvslide.v0 = 0.2;
    locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall1.level = 50;
	
	locations[n].models.always.Waterfall2 = "river2";
	locations[n].models.always.Waterfall2.uvslide.v0 = 0.4;
    locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall2.level = 49;

	//WindMill Fan
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";	
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.3;

	locations[n].models.always.MillFan1 = "Flugger";
    locations[n].models.always.MillFan1.tech = "DLightModel";
    Locations[n].models.always.MillFan1.locator.group = "WindMill";
    Locations[n].models.always.MillFan1.locator.name ="Fan1";    
    Locations[n].models.always.MillFan1.rotate.x = 0.0;
    Locations[n].models.always.MillFan1.rotate.y = 0.3;
    Locations[n].models.always.MillFan1.rotate.z = 0.0;
	
	//Day
	locations[n].models.day.fonar = "Curacao_fd";
	locations[n].models.day.charactersPatch = "Curacao_patch_day";
	locations[n].models.day.rinok = "Curacao_rinok";
	//Night
	locations[n].models.night.fonar = "Curacao_fn";
	locations[n].models.night.charactersPatch = "Curacao_patch_night";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	
	// --> Типовые городские локации, четкая фиксация на 10 номеров.
	// В таверне
	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Formosa_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";
	// В дом Йохана ван Мердена
	locations[n].reload.l21.name = "houseSp1";
	locations[n].reload.l21.go = "Formosa_houseSp1";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House"; 
	// За городские ворота
	locations[n].reload.l22.name = "gate_back";
	locations[n].reload.l22.go = "Formosa_ExitTown";
	locations[n].reload.l22.emerge = "reload4";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "ExitTown"; 
	
	LAi_LocationFightDisable(&Locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Таверна, Остров Формоза
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Formosa_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern01\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	//Models
	//Always
	locations[n].models.always.tavern = "Tavern01";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "Tavern01_locators";
	locations[n].models.always.window = "tavern01_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.window.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "tavern01_patch";
	//Night
	locations[n].models.night.charactersPatch = "tavern01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Formosa";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом Йохана ван Мердена, Остров Формоза
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Formosa_houseSp1"; //с комнатой на втором этаже
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\largehouse01.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\largehouse01";
	locations[n].models.always.largehouse01 = "largehouse01";
	locations[n].models.always.largehouse01.level = 65538;
	locations[n].models.day.locators = "largehouse01_locators";
	locations[n].models.night.locators = "largehouse01_Nlocators";

	Locations[n].models.always.largehouse01windows = "largehouse01_windows";
	Locations[n].models.always.largehouse01windows.tech = "LocationWindows";
	locations[n].models.always.largehouse01windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.largehouse01rand= "largehouse01_rand";
	locations[n].models.day.charactersPatch = "largehouse01_patch";
	//Night
	locations[n].models.night.charactersPatch = "largehouse01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Formosa";
	locations[n].reload.l1.emerge = "houseSp1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].box1.QuestClosed = true;
	LAi_LocationFightDisable(&locations[n], true);
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города, Остров Формоза
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Formosa_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate" + rand(1) + ".tga";
	//Sound
	locations[n].type = "jungle";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitW";
	Locations[n].models.always.townExit = "townExitW";
	Locations[n].models.always.townWalls = "townExitW_wood";
	
	Locations[n].models.always.locators = "townExitW_locators";
		
	Locations[n].models.always.grassPatch = "townExitW_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "townExitW_patch";
	locations[n].models.day.fonars = "townExitW_fd";
	//Night
	locations[n].models.night.charactersPatch = "townExitW_patch";
	locations[n].models.night.fonars = "townExitW_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload4";
	locations[n].reload.l1.go = "Formosa";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Zeelanda";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Улицы поселения Батавии, Остров Ява
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Batavia";
	locations[n].id.label = "Batavia";
	
	locations[n].filespath.models = "locations\Town_Batavia\Town\";
	locations[n].image = "loading\Town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//Sound
	locations[n].type = "town";
	//Models
	//Always
	locations[n].models.always.town = "Martinique";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.L1 = "Martinique_signsA";
	locations[n].models.always.L2 = "Malta_doors";
	locations[n].models.always.L2.tech = "DLightModel";
	locations[n].models.always.seabed = "Martinique_sb";
	locations[n].models.always.locators = "Martinique_locators";
	locations[n].models.always.grassPatch = "Martinique_grass";
	
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 9;

	//Fontain
	locations[n].models.always.Waterfall1 = "fontain1";
	locations[n].models.always.Waterfall1.uvslide.v0 = 0.5;
    locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall1.level = 50;
	
	locations[n].models.always.Waterfall2 = "fontain2";
	locations[n].models.always.Waterfall2.uvslide.v0 = 0.2;
    locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall2.level = 49;

	//WindMill Fan
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";	
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.2;

	//Day
	locations[n].models.day.fonar = "Martinique_fd";
	locations[n].models.day.charactersPatch = "Martinique_patch_day";
	locations[n].models.day.rinok = "Martinique_rinok";
	//Night
	locations[n].models.night.fonar = "Martinique_fn";
	locations[n].models.night.charactersPatch = "Martinique_patch_night";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Batavia_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;
	
	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Batavia_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;
	
	locations[n].reload.l11.name = "houseF3";
	locations[n].reload.l11.go = "Batavia_houseF3";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "House";
	locations[n].reload.l11.close_for_night = 1;
	
	locations[n].reload.gate1.name = "gate_back";
	locations[n].reload.gate1.go = "Batavia_Plantation";
	locations[n].reload.gate1.emerge = "reload1";
	locations[n].reload.gate1.autoreload = "0";
	locations[n].reload.gate1.label = "Plantation";
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Магазин, Батавия
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Batavia_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store01\";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	//Models
	//Always
	locations[n].models.always.locators = "Store01_locators";
	locations[n].models.always.store = "Store01";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Store01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Store01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Batavia";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция, Батавия
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Batavia_townhall";
	locations[n].id.label = "Townhall";
	locations[n].filespath.models = "locations\inside\Residence01";
	locations[n].image = "loading\inside\residence.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	//Models
	//Always
	locations[n].models.always.locators = "Residence01_locators";
	locations[n].models.always.l1 = "Residence01";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "residence01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Residence01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Residence01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map

	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Batavia";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Batavia_townhallRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Кабинет в резиденции, Батавия
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Batavia_townhallRoom";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\BigHouse02.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\BigHouse02\";
	locations[n].models.always.models = "BigHouse02";
	locations[n].models.always.models.level = 65538;
	locations[n].models.always.boxes = "BigHouse02_boxes";
	locations[n].models.always.boxes.level = 65539;
	locations[n].models.always.window = "BigHouse02_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65540;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "BigHouse02_patch";
	locations[n].models.day.locators = "BigHouse02_PrLocators";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse02_patch";
	locations[n].models.night.locators = "BigHouse02_PrNlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Batavia_townhall";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Townhall";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом любовницы Димена, Батавия
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Batavia_houseF3";
	locations[n].filespath.models = "locations\inside\CobHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CobHouse.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	//Models
	//Always
	locations[n].models.always.tavern = "CobHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "CobHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "CobHouse_locators";
	locations[n].models.night.locators = "CobHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "CobHouse_patch";
	//Night
	locations[n].models.night.charactersPatch = "CobHouse_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Batavia";
	locations[n].reload.l1.emerge = "houseF3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Плантация, Батавия
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Batavia_Plantation";
	locations[n].id.label = "Plantation";
	locations[n].image = "loading\jonny_load\quest\BarbadosPlantation_(Caiman).tga";
	//Town sack
	locations[n].citizens = true;    //homo жители
	locations[n].soldiers = true;    //homo солдаты
	locations[n].carrier = true;
	//Sound
	locations[n].type = "town";
	//Models
	//Always
	locations[n].filespath.models = "locations\BarbadosPlantation";
	locations[n].models.always.BarbadosPlantation = "BarbadosPlantation";
	locations[n].models.always.reflect = "BarbadosPlantation_reflect";
	Locations[n].models.always.reflect.sea_reflection = 1;
	locations[n].models.always.gate = "BarbadosPlantation_gateopen";
	locations[n].models.always.locators = "BarbadosPlantation_locators";
	locations[n].models.always.grassPatch = "BarbadosPlantation_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.Waterfall = "waterfall";
	Locations[n].models.always.Waterfall.uvslide.v0 = 0.3;
    Locations[n].models.always.Waterfall.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall.level = 99949;
	locations[n].models.always.plan1 = "plan1";
	locations[n].models.always.plan1.level = 9;
	locations[n].models.always.plan2 = "plan2";
	locations[n].models.always.plan2.level = 8;
	locations[n].models.always.plan3 = "plan3";
	locations[n].models.always.plan3.level = 7;
	locations[n].models.always.plan4 = "plan4";
	locations[n].models.always.plan4.level = 6;
	//Day
	locations[n].models.day.charactersPatch = "BarbadosPlantation_patchopen";
	locations[n].models.day.fonar = "BarbadosPlantation_fd";
	//Night
	locations[n].models.night.charactersPatch = "BarbadosPlantation_patchopen";
	locations[n].models.night.fonar = "BarbadosPlantation_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Batavia";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

    locations[n].locators_radius.quest.detector1 = 5.0; //homo
    n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Улицы поселения Капстервиля, квестовый для Лонгвея
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Kapstervil";
	locations[n].id.label = "Charles";

	locations[n].filespath.models = "locations\Town_Nevis\Town\";

	locations[n].image = "loading\Town.tga";
	//Sound
	locations[n].type = "town";
	//Models
	//Always
	locations[n].models.always.town = "Nevis";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.l1 = "Nevis_signsA";
	locations[n].models.always.locators = "Nevis_locators";
	locations[n].models.always.grassPatch = "Nevis_grass";
	locations[n].models.always.seabed = "Nevis_sb";
	locations[n].models.always.plan.level = 9;

	//WindMill Fan
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";	
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.3;

	//Day
	locations[n].models.day.fonar = "Nevis_fd";
	locations[n].models.day.charactersPatch = "Nevis_patch_day";
	locations[n].models.day.rinok = "Nevis_rinok";

	//Night
	locations[n].models.night.fonar = "Nevis_fn";
	locations[n].models.night.charactersPatch = "Nevis_patch_night";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "Kapstervil_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";
	
	locations[n].reload.gate.name = "gate_back";
	locations[n].reload.gate.go = "Kapstervil_ExitTown";
	locations[n].reload.gate.emerge = "reload1";
	locations[n].reload.gate.autoreload = "0";
	locations[n].reload.gate.label = "ExitTown";
	locations[n].locators_radius.reload.gate_back = 2.0;
	
	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Kapstervil_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";
	
	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Kapstervil_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;
	
    /*locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Charles_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "Charles_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "Charles_bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload9_back";
	locations[n].reload.l9.go = "Charles_brothel";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Brothel";

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "Charles_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;
	
	locations[n].reload.jail.name = "reload_jail";
	locations[n].reload.jail.go = "Charles_prison";
	locations[n].reload.jail.emerge = "reload1";
	locations[n].reload.jail.autoreload = "0";
	locations[n].reload.jail.label = "Prison";*/
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ Капстервиля, квестовый для Лонгвея
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Kapstervil_church";
	locations[n].id.label = "Church";
	locations[n].filespath.models = "locations\inside\Church01";
	locations[n].image = "loading\inside\church.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	//Models
	//Always
	locations[n].models.always.locators = "Church01_locators";
	locations[n].models.always.tavern = "Church01";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Church01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Church01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Church01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Kapstervil";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТАВЕРНА Капстервиля, квестовый для Лонгвея
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Kapstervil_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern08\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	//Models
	locations[n].models.always.tavern = "Tavern08";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "Tavern08_locators";
	locations[n].models.always.window = "tavern08_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.window.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern08_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern08_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Kapstervil";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// МАГАЗИН Капстервиля, квестовый для Лонгвея
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Kapstervil_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store05\";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	//Models
	//Always
	locations[n].models.always.locators = "Store05_locators";
	locations[n].models.always.store = "Store05";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Store05_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Store05_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store05_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Kapstervil";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.camdetector.camera1 = 5;
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Городские ворота Капстервиля, квестовый для Лонгвея
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Kapstervil_ExitTown";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Kapstervil";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Charles";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли Капстервиля, квестовый для Лонгвея
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Kapstervil_Jungle";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle6";
	Locations[n].models.always.jungle = "jungle6";	
	Locations[n].models.always.locators = "jungle6_locators";		
	Locations[n].models.always.grassPatch = "jungle6_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle6_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle6_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	/*locations[n].reload.l1.name = "reload1_back";			//УДАЛИТЬ ПОТОМ
	locations[n].reload.l1.go = "Kapstervil_Grot";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;*/
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот Капстервиля, квестовый для Лонгвея
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Kapstervil_Grot";
	locations[n].id.label = "Grot";
    locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto2";
	locations[n].models.always.grotto2 = "grotto2";
	locations[n].models.always.grotto2.sea_reflection = 1;
	locations[n].models.always.grotto2alpha = "grotto2_alpha";
	Locations[n].models.always.grotto2alpha.tech = "LocationWindows";	
	locations[n].models.always.grotto2alpha.level = 65532;	
	locations[n].models.always.locators = "grotto2_locators";

	locations[n].locators_radius.item.duhi1 = 0.0;
	//Day
	locations[n].models.day.charactersPatch = "grotto2_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	/*locations[n].reload.l1.name = "reload1_back";			//УДАЛИТЬ ПОТОМ
	locations[n].reload.l1.go = "Kapstervil_Jungle";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;*/
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Квестовая верхняя палуба Пинаса
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Quest_Ship_deck_Medium_trade";
	Locations[n].image = "loading\Quarter_" + rand(1) + ".tga";
	locations[n].id.label = "Boarding deck";
	//Sound
	Locations[n].type = "residence";
	// нельзя, иначе нет моря Locations[n].boarding = "true";
	//Models	
	Locations[n].filespath.models = "locations\decks\outside_deck_3_tutorial"; // пинас_туториал
	//Always
	Locations[n].models.always.main = "outside_deck_3_tutorial";
	Locations[n].models.always.parts = "outside_deck_3_tutorial_parts";
	Locations[n].models.always.ropes = "outside_deck_3_tutorial_ropes";
	Locations[n].models.always.locators = "outside_deck_3_tutorial_locators";
	Locations[n].models.always.windows = "outside_deck_3_tutorial_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.watermask = "outside_deck_3_tutorial_watermask";
	Locations[n].models.always.watermask.tech = "WaterMask";
	Locations[n].models.always.watermask.level = 65500;
	//Day
	locations[n].models.day.charactersPatch = "outside_deck_3_tutorial_patch";
	Locations[n].models.day.deckMediumFonarsDay = "outside_deck_3_tutorial_fd";  
	Locations[n].models.day.jumpPatch = "outside_deck_3_tutorial_jump";
	//Night
	locations[n].models.night.charactersPatch = "outside_deck_3_tutorial_patch";
	Locations[n].models.night.deckMediumFonarsNight = "outside_deck_3_tutorial_fn";  
	Locations[n].models.night.jumpPatch = "outside_deck_3_tutorial_jump";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";

	locations[n].box1 = Items_MakeTime(0, 0, 1, 2003);
	locations[n].box2 = Items_MakeTime(0, 0, 1, 2003);
    locations[n].box3 = Items_MakeTime(0, 0, 1, 2003);
    locations[n].box4 = Items_MakeTime(0, 0, 1, 2003);
	locations[n].locators_radius.reload.reload_cabin = 0.75;
	locations[n].locators_radius.reload.reload_camp1 = 0.75;
	locations[n].locators_radius.reload.reload_arsenal = 0.75;
	locations[n].locators_radius.reload.reload_kitchen = 0.75;
	locations[n].locators_radius.reload.reload_gundeck = 0.75;
	locations[n].locators_radius.box.private1 = 0.6;
	locations[n].locators_radius.box.private2 = 0.6;
	locations[n].locators_radius.box.private3 = 0.6;
	locations[n].locators_radius.item.item1 = 1.0;
	
	locations[n].reload.l1.name = "reload_cabin";
	locations[n].reload.l1.go = "Quest_Cabin_Medium";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.label = "cabine";
	locations[n].reload.l1.disable = true;
	
	locations[n].reload.l2.name = "reload_camp1";
	locations[n].reload.l2.go = "Quest_Campus";
	locations[n].reload.l2.emerge = "reload_deck1";
	locations[n].reload.l2.label = "My_Campus";
	locations[n].reload.l2.disable = false;
	
	locations[n].reload.l3.name = "reload_arsenal";
	locations[n].reload.l3.go = "Quest_Deck_Medium";
	locations[n].reload.l3.emerge = "reload_deck";
	locations[n].reload.l3.label = "My_Deck_Medium";
	locations[n].reload.l3.disable = false;
	
	locations[n].reload.l4.name = "reload_kitchen";
	locations[n].reload.l4.go = "Quest_Deck_Medium";
	locations[n].reload.l4.emerge = "reload_deck";
	locations[n].reload.l4.label = "My_Deck_Medium";
	locations[n].reload.l4.disable = false;
	
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Квестовая каюта в начале игры
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Quest_Cabin_Medium";
	Locations[n].id.label = "cabine";
	Locations[n].filespath.models = "locations\decks\capmd";
    Locations[n].image = "loading\Capdeck_" + rand(4) + ".tga";
	//Sound
	Locations[n].type = "residence";
	//Models
	//Always
	Locations[n].models.always.l1 = "capmd";
	locations[n].models.always.l1.level = 65538;

	Locations[n].models.always.window = "capmd_w";
	Locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	//Day
	Locations[n].models.day.l2 = "capmd_md"; //пушки по бортам, карты на столе
    Locations[n].models.day.l2.level = 65538;
    Locations[n].models.day.locators = "capmd_quest_locators"; //протагонист в центре каюты, клевреты стоят вокруг, ближе к стенам
    Locations[n].models.day.charactersPatch = "capmd_pmd"; //дерево + ковёр - стул
    Locations[n].models.day.fonar = "capmd_fd";

	//Night
	Locations[n].models.night.l3 = "capmd_mn"; //пушки по бортам, новые портреты
    Locations[n].models.night.l3.level = 65538;
    Locations[n].models.night.locators = "capmd_quest_locators"; //протагонист так же в центре каюты, клевреты располагаются вокруг
    Locations[n].models.night.charactersPatch = "capmd_pmn"; //дерево + ковёр
    Locations[n].models.night.fonar = "capmd_fn";

	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

	locations[n].box1 = Items_MakeTime(0, 1, 1, 2013); //капитанский рундук, у левого борта
    locations[n].box2 = Items_MakeTime(0, 1, 1, 2013); //сундук у правого борта
    locations[n].box3 = Items_MakeTime(0, 1, 1, 2013); //шкатулка с принадлежностями, на столе, ночью слева, днём справа
    locations[n].box4 = Items_MakeTime(0, 1, 1, 2013); //шкап

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
	//Locations[n].camshuttle = 1;
	locations[n].environment.weather.rain = false;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Квестовая нижняя палуба в начале игры
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Quest_Deck_Medium";
	Locations[n].id.label = "My_Deck_Medium";
	//Info
	Locations[n].filespath.models = "locations\decks\deck2"; //7
	Locations[n].image = "loading\Gundeck_" + rand(2) + ".tga";
	//Sound
	Locations[n].type = "residence";

	//Models
	Locations[n].filespath.models = "locations\decks\inside_gundeck_3";
	//Always
	Locations[n].models.always.main = "inside_gundeck_3";
	Locations[n].models.always.parts = "inside_gundeck_3_parts";
	Locations[n].models.always.outside = "inside_gundeck_3_outside";
	Locations[n].models.always.locators = "inside_gundeck_3_locators_tutorial";
	Locations[n].models.always.camcollider = "inside_gundeck_3_camcollider";
	Locations[n].models.always.rays = "inside_gundeck_3_rays"; // лучи
	Locations[n].models.always.rays.uvslide.v0 = 0.08;
	Locations[n].models.always.rays.uvslide.v1 = 0.0;
	Locations[n].models.always.rays.tech = "LocationWaterFall";
	Locations[n].models.always.rays.level = 99950;
	//Day
	Locations[n].models.day.charactersPatch = "inside_gundeck_3_patch";
	Locations[n].models.day.fonar = "inside_gundeck_3_fn"; // тоже ночные
	//Night
	Locations[n].models.night.charactersPatch = "inside_gundeck_3_patch";
	Locations[n].models.night.fonar = "inside_gundeck_3_fn";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "true";

	Locations[n].boarding = "true";

    locations[n].box1 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box2 = Items_MakeTime(0, 1, 1, 2003);
    locations[n].box3 = Items_MakeTime(0, 1, 1, 2003);
    locations[n].box4 = Items_MakeTime(0, 1, 1, 2003);
	
	Locations[n].locators_radius.item.item1 = 1.1;
	Locations[n].locators_radius.item.item2 = 1.0;

    LAi_LocationFightDisable(&Locations[n], true);
	
	Locations[n].reload.l1.name = "reload_deck";
	Locations[n].reload.l1.go = "Quest_Ship_deck_Medium_trade";
	Locations[n].reload.l1.emerge = "reload_kitchen";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Boarding deck";
	
	Locations[n].reload.l2.name = "reload_camp";
	Locations[n].reload.l2.go = "Quest_Campus";
	Locations[n].reload.l2.emerge = "reload_gundeck";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.label = "My_Campus";

	Locations[n].reload.l3.name = "reload_hold1";
	Locations[n].reload.l3.go = "Quest_Deck";
	Locations[n].reload.l3.emerge = "reload_gundeck1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "My_Deck.";
	
	//Locations[n].camshuttle = 1;
	locations[n].environment.weather.rain = false;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Квестовая кают-компания в начале игры
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Quest_Campus";
	Locations[n].id.label = "My_Campus";
    Locations[n].image = "loading\Capdeck_" + rand(4) + ".tga";
	//Sound
	Locations[n].type = "residence";
	//Models
	Locations[n].filespath.models = "locations\decks\inside_campdeck_3";
	//Always
	Locations[n].models.always.main = "inside_campdeck_3";
	Locations[n].models.always.parts = "inside_campdeck_3_parts";
	Locations[n].models.always.outside = "inside_campdeck_3_outside";
	Locations[n].models.always.locators = "inside_campdeck_3_locators_tutorial";
	Locations[n].models.always.sleeper = "inside_campdeck_3_sleeper";
	Locations[n].models.always.camcollider = "inside_campdeck_3_camcollider";
	Locations[n].models.always.rays = "inside_campdeck_3_rays"; // лучи
	Locations[n].models.always.rays.uvslide.v0 = 0.08;
	Locations[n].models.always.rays.uvslide.v1 = 0.0;
	Locations[n].models.always.rays.tech = "LocationWaterFall";
	Locations[n].models.always.rays.level = 99950;
	//Day
	Locations[n].models.day.charactersPatch = "inside_campdeck_3_patch";
	Locations[n].models.day.fonar = "inside_campdeck_3_fn"; // ночные
	//Night
	Locations[n].models.night.charactersPatch = "inside_campdeck_3_patch";
	Locations[n].models.night.fonar = "inside_campdeck_3_fn";

	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

	locations[n].box1 = Items_MakeTime(0, 1, 1, 2013);

    Locations[n].locators_radius.rld.loc0 = 0.5;
    Locations[n].locators_radius.rld.loc1 = 0.5;
    Locations[n].locators_radius.rld.loc2 = 0.5;
    Locations[n].locators_radius.rld.loc3 = 0.5;
    Locations[n].locators_radius.rld.aloc0 = 0.5;
    Locations[n].locators_radius.rld.aloc1 = 0.5;
    Locations[n].locators_radius.rld.aloc2 = 0.5;
    Locations[n].locators_radius.rld.aloc3 = 0.5;

    LAi_LocationFightDisable(&Locations[n], true);

	Locations[n].reload.l1.name = "reload_deck1";
	Locations[n].reload.l1.go = "Quest_Ship_deck_Medium_trade";
	Locations[n].reload.l1.emerge = "reload_camp1";
	Locations[n].reload.l1.label = "Boarding deck";
	
	Locations[n].reload.l2.name = "reload_gundeck";
	Locations[n].reload.l2.go = "Quest_Deck_Medium";
	Locations[n].reload.l2.emerge = "reload_camp";
	Locations[n].reload.l2.label = "Cabin.";

	Locations[n].items.randitem2 = "";
	Locations[n].items.randitem1 = "";

	Locations[n].boarding = "true";
	//Locations[n].camshuttle = 1;
	locations[n].environment.weather.rain = false;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Квестовый трюм в начале игры
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Quest_Deck";
	Locations[n].id.label = "My_Deck";
	//Info
	Locations[n].filespath.models = "locations\decks\hold";
	Locations[n].image = "loading\Hold_" + rand(1) + ".tga";
	//Sound
	Locations[n].type = "residence";
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_hold_3";
	//Always
	Locations[n].models.always.main = "inside_hold_3";
	Locations[n].models.always.parts = "inside_hold_3_parts";
	Locations[n].models.always.outside = "inside_hold_3_outside";
	Locations[n].models.always.locators = "inside_hold_3_locators_tutorial";
	Locations[n].models.always.camcollider = "inside_hold_3_camcollider";
	Locations[n].models.always.rays = "inside_hold_3_rays"; // лучи
	Locations[n].models.always.rays.uvslide.v0 = 0.08;
	Locations[n].models.always.rays.uvslide.v1 = 0.0;
	Locations[n].models.always.rays.tech = "LocationWaterFall";
	Locations[n].models.always.rays.level = 99950;
	//Day
	Locations[n].models.day.charactersPatch = "inside_hold_3_patch";
	Locations[n].models.day.fonar = "inside_hold_3_fn"; // тоже ночные
	Locations[n].fonarlights = true; // фонари всегда горят
	//Night
	Locations[n].models.night.charactersPatch = "inside_hold_3_patch";
	Locations[n].models.night.fonar = "inside_hold_3_fn";
	
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";

	locations[n].box1 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box2 = Items_MakeTime(0, 1, 1, 2003);
    locations[n].box3 = Items_MakeTime(0, 1, 1, 2003);
    locations[n].box4 = Items_MakeTime(0, 1, 1, 2003);
	
	Locations[n].locators_radius.item.item1 = 1.0;
	Locations[n].locators_radius.item.item2 = 1.0;

    LAi_LocationFightDisable(&Locations[n], true);

    Locations[n].reload.l1.name = "reload_gundeck1";
	Locations[n].reload.l1.go = "Quest_Deck_Medium";
	Locations[n].reload.l1.emerge = "reload_hold1";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "Cabin.";

	Locations[n].boarding = "true";
	//Locations[n].camshuttle = 1;
	locations[n].environment.weather.rain = false;

	n = n + 1;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// резервные локации
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 1
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 2
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_02";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 3
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 4 // Jason Долго и счастливо
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_04";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 5	// Sinistra Одноразовая локация для всего
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_05";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 6	// Sinistra Длинные тени старых грехов
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_06";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 7
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_07";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 8
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_08";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 9
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_09";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 10
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_10";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 11
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_11";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 12
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_12";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 13
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_13";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 14
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_14";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 15
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_15";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 16
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_16";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 17
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_17";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 18
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_18";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 19
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_19";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 20
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_20";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 21
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_21";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 22
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_22";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 23
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_23";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 24
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_24";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 25
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_25";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 26
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_26";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 27
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_27";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 28
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_28";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 29
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_29";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 30
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_30";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 31
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_31";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 32
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_32";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 33
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_33";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 34
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_34";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 35
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_35";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 36
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_36";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 37
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_37";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 38
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_38";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 39
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_39";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 40
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_40";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 41
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_41";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 42
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_42";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 43
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_43";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 44
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_44";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 45
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_45";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 46
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_46";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 47
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_47";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 48
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_48";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 49
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_49";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "";
	locations[n].reload.l3.emerge = "";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// резервная локация 50
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Location_reserve_50";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "SentJons";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Antigua";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\murdoch_room";
	locations[n].models.always.room = "murdoch_room";
	locations[n].models.always.room.level = 65538;
	locations[n].models.day.locators = "murdoch_room_locators";
	locations[n].models.night.locators = "murdoch_room_Nlocators";

	Locations[n].models.always.windows = "murdoch_room_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "murdoch_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "murdoch_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "";
	locations[n].reload.l1.emerge = "";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	n = n + 1;
	
	// Фиктивная пустая локация для главного меню
	// подгружается вручную через месседжы, а не через LoadLocation
	locations[n].id = "MainMenu";
	locations[n].id.label = "MainMenu";
	locations[n].type = "MainMenu";
	n = n + 1;
	
	return n;
}
