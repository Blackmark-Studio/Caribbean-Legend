
int LocationInitBermudes(int n)
{
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pirates_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "Pirates_town";
	
	locations[n].townsack = "Pirates";
	locations[n].fastreload = "Pirates";
 	locations[n].islandId = "Bermudes";
	
	locations[n].filespath.models = "locations\Town_IslaMona\Town\";
	locations[n].image = "loading\towns\pearl1.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;

	//Sound
	locations[n].type = "town";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	//Always
	locations[n].models.always.L1 = "IslaMona";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.locators = "IslaMona_locators";
	locations[n].models.always.grassPatch = "IslaMona_grass";
	locations[n].models.always.seabed = "IslaMona_sb";
	
	locations[n].models.always.plan = "IslaMona_plan";
	locations[n].models.always.plan.level = 9;

	//River
	locations[n].models.always.Waterfall1 = "Islamona_river1";
	locations[n].models.always.Waterfall1.uvslide.v0 = 0.2;
    locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall1.level = 50;
	
	locations[n].models.always.Waterfall2 = "Islamona_river2";
	locations[n].models.always.Waterfall2.uvslide.v0 = -0.3;
    locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall2.level = 49;

	//Day
	locations[n].models.day.fonar = "IslaMona_fd";
	locations[n].models.day.charactersPatch = "IslaMona_patch";
	//locations[n].models.day.rinok = "IslaMona_rinok";
	//Night
	locations[n].models.night.fonar = "IslaMona_fn";
	locations[n].models.night.charactersPatch = "IslaMona_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map

    // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bermudes";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 1.8;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Pirates_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.disable = true; //закрыто до поры

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Pirates_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "Pirates_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Pirates_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

	// --> Квестовые локации.

	// --> Комоны, загрушки. Номера с начинаются с 20.
	locations[n].reload.l20.name = "houseH1";
	locations[n].reload.l20.go = "CommonHut";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";
	
	locations[n].reload.l21.name = "houseSp1";
	locations[n].reload.l21.go = "CommonFlamHouse";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";
	
	locations[n].reload.l22.name = "houseS1";
	locations[n].reload.l22.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";
	
	locations[n].reload.l23.name = "houseF1";
	locations[n].reload.l23.go = "CommonRoom_MH";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТАВЕРНА
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pirates_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern04\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "Pirates";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "Pirates";
 	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].models.always.tavern = "tavern04";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "tavern04_locators";
	locations[n].models.always.window = "tavern04_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "tavern04_patch";
	//Night
	locations[n].models.night.charactersPatch = "tavern04_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pirates_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Pirates_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// КОМНАТА В ТАВЕРНЕ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pirates_tavern_upstairs";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "Pirates";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Pirates";
 	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].models.always.locators = "Tavern_room_locators";
	locations[n].models.always.tavern = "Tavern_room";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "tavern_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pirates_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// МАГАЗИН
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pirates_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store02\";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "Pirates";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Pirates";
 	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].models.always.locators = "Store02_locators";
	locations[n].models.always.store = "Store02";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Store02_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Store02_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store02_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pirates_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ВЕРФЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pirates_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\ShipyardPirates\";
	locations[n].image = "loading\inside\shipyard.tga";
	//Town sack
	locations[n].townsack = "Pirates";
	//locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "Pirates";
 	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].models.always.locators = "ShipyardPirates_locators";
	locations[n].models.always.shipyard = "ShipyardPirates";
	locations[n].models.always.shipyard.level = 65538;
	locations[n].models.always.rock = "ShipyardPirates_rock";

	locations[n].models.always.window = "ShipyardPirates_fn";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	//Day
	locations[n].models.day.charactersPatch = "ShipyardPirates_patch";
	//Night
	locations[n].models.night.charactersPatch = "ShipyardPirates_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pirates_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Bermudes_Dungeon";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "";
    Locations[n].reload.l2.disable = 1;
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].DisableOfficers = "1"; // 280912 надо по квесту
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РЕЗИДЕНЦИЯ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pirates_townhall";
	locations[n].id.label = "Townhall";
	locations[n].filespath.models = "locations\inside\Residence05";
	locations[n].image = "loading\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "Pirates";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Pirates";
 	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].models.always.locators = "Residence05_locators";
	locations[n].models.always.l1 = "Residence05";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "residence05_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "residence05_patch";
	//Night
	locations[n].models.night.charactersPatch = "residence05_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Pirates_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Pirates_townhall_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////// Резиденция
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Pirates_townhall_upstairs";
	locations[n].id.label = "Residence";
	locations[n].image = "loading\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "Pirates";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Pirates";
	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\SmallResidence";
	locations[n].models.always.locators = "SmallResidence_locators";
	locations[n].models.always.house = "SmallResidence";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "SmallResidence_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "SmallResidence_patch";
	//Night
	locations[n].models.night.charactersPatch = "SmallResidence_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Pirates_townhall";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Подземелье Бермудов
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bermudes_Dungeon";
	locations[n].id.label = "Dungeon";
	locations[n].image = "loading\inside\dungeon.tga";
	//Town sack
	locations[n].townsack = "Pirates";
	//Sound
	locations[n].type = "Dungeon";
	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\DungeonVault1";
	locations[n].models.always.DungeonVault1 = "DungeonVault1";
	locations[n].models.always.InquisitionDungeonVault1Fonars = "DungeonVault1_fonars";
	locations[n].models.always.locators = "DungeonVault1_locators";	

	locations[n].locators_radius.item.duhi1 = 0.0;
	//Day
	locations[n].models.day.charactersPatch = "DungeonVault1_patch";
	//Night
	locations[n].models.night.charactersPatch = "DungeonVault1_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Pirates_Shipyard";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore3";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore3";
	locations[n].locators_radius.reload.reload2_back = 1.5;
	
	locations[n].private1.key = "key3"; // сундучок Алекса
	locations[n].private1.key.delItem = true;
	locations[n].private1.items.alexs_chest = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж 3  (два выхода)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore3";
	locations[n].id.label = "Shore3";
	locations[n].worldmap = "Shore3";
	locations[n].image = "loading\outside\harbor3.tga";
	SetItemInLocation("cannabis7", locations[n].id, "qflower1");
	//Sound
	locations[n].type = "seashore";
 	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore04";
	Locations[n].models.always.shore04 = "shore04";
	locations[n].models.always.shore04.sea_reflection = 1;
	Locations[n].models.always.shore04seabed = "shore04_sb";
	Locations[n].models.always.locators = "shore04_locators";
		
	Locations[n].models.always.grassPatch = "shore04_grass";
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
	locations[n].models.day.charactersPatch = "shore04_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore04_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bermudes_jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 1;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Bermudes_Dungeon";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Dungeon";
    locations[n].locators_radius.reload.reload2_back = 1.5;

	locations[n].reload.l3.name = "boat";
	locations[n].reload.l3.go = "Bermudes";
	locations[n].reload.l3.emerge = "reload_2";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Sea";
	locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Bermudes_jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle8\";
	Locations[n].models.always.jungle = "jungle8";	
	Locations[n].models.always.locators = "jungle8_locators";		
	Locations[n].models.always.grassPatch = "jungle8_grass";
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
	locations[n].models.day.charactersPatch = "jungle8_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle8_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bermudes_CaveEntrance";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore3";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore3";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bermudes_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
 	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt1";
	Locations[n].models.always.caveEnt1 = "caveEnt1";	
	Locations[n].models.always.locators = "caveEnt1_locators";		
	Locations[n].models.always.grassPatch = "caveEnt1_grass";
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
	locations[n].models.day.charactersPatch = "caveEnt1_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt1_patch";	
	//Environment	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bermudes_Cavern";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Bermudes_jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Сковозная пещера
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	locations[n].id = "Bermudes_Cavern";
	locations[n].id.label = "Cave";
	locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
 	locations[n].islandId = "Bermudes";
	SetItemInLocation("cannabis7", locations[n].id, "qflower1");
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernLow1";
	locations[n].models.always.cavernLow1 = "cavernLow1";
		
	locations[n].models.always.cavernLow1Lamps = "cavernLow1_lamps";
	locations[n].models.always.cavernLow1Crystals = "cavernLow1_crystals";
	locations[n].models.always.cavernLow1Crystals.tech = "EnvironmentShader";
	locations[n].models.always.cavernLow1Crystals.reflection = 0.25;
	
	locations[n].models.always.Waterfall = "water";
	locations[n].models.always.Waterfall.uvslide.v0 = 0.0;
	locations[n].models.always.Waterfall.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall.level = 51;

	locations[n].models.always.Cfall = "cfall";
	locations[n].models.always.Cfall.uvslide.v0 = 0.3;
    locations[n].models.always.Cfall.uvslide.v1 = 0.0;
	locations[n].models.always.Cfall.tech = "LocationWaterFall";
	locations[n].models.always.Cfall.level = 50;
	
	locations[n].models.always.locators = "cavernLow1_locators";

	locations[n].locators_radius.item.duhi1 = 0.0;
/*	
	Locations[n].models.always.rays = "cavernLow1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;
*/	
	//Day
	locations[n].models.day.charactersPatch = "cavernLow1_patch";
	//Night
	locations[n].models.night.charactersPatch = "cavernLow1_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bermudes_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore_ship1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].locators_radius.reload.reload2_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Бухта с кораблём
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore_ship1";
	locations[n].id.label = "Shore_ship1";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore_ship1";
	locations[n].Chestgennot = true; // не генерить сундуки
    //Sound
	locations[n].type = "seashore";
 	locations[n].islandId = "Bermudes";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\ShoreShip1";
	Locations[n].models.always.shore = "shoreShip1";
	locations[n].models.always.shore.sea_reflection = 1;
	Locations[n].models.always.shoreShip1seabed = "shoreShip1_sb";
	Locations[n].models.always.locators = "shoreShip1_locators";		
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
	locations[n].models.day.charactersPatch = "shoreShip1_patch";
	//Night
	locations[n].models.night.charactersPatch = "shoreShip1_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bermudes_Cavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload2_back = 3;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Bermudes";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;
	
	return n;
}
