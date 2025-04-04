
int LocationInitTortuga(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "Tortuga";
	locations[n].filespath.models = "locations\Town_Margarita\Town\";
	locations[n].image = "loading\Town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true; //Экку Korsar - новая Маргарита адекватно поддерживает грузчиков
	
	//Town sack
	locations[n].townsack = "Tortuga";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "Tortuga";
	locations[n].islandId = "Tortuga";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	//Always
	//Экку Korsar - адаптация маргариты под ГПК/ККС
	locations[n].models.always.town = "Margarita_GPK";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.seabed = "Margarita_GPK_seabed";
	locations[n].models.always.locators = "Margarita_GPK_locators";
	locations[n].models.always.grassPatch = "Margarita_GPK_grass";
	
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

	// подгружаемые модели
	locations[n].models.always.mill_movie = "mill_movie";
	Locations[n].models.always.mill_movie.locator.group = "Upgrades";
	Locations[n].models.always.mill_movie.locator.name = "mill_movie";
	Locations[n].models.always.mill_movie.rotate.x = 0.0;
	Locations[n].models.always.mill_movie.rotate.y = 0.0;
	Locations[n].models.always.mill_movie.rotate.z = 0.2;
	
	//Day
	locations[n].models.day.fonar = "Margarita_GPK_fd";
	locations[n].models.day.charactersPatch = "Margarita_GPK_patch_day";
	locations[n].models.day.rinok = "Margarita_rinok";
	
	//Night
	locations[n].models.night.fonar = "Margarita_GPK_fn";
	locations[n].models.night.charactersPatch = "Margarita_GPK_patch_night";
	
	Locations[n].models.day.jumpPatch = "Margarita_jump_patch"; 	
	Locations[n].models.night.jumpPatch = "Margarita_jump_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	 // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 1.8;

	locations[n].reload.l2.name = "reload_grot";
	locations[n].reload.l2.go = "Tortuga";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	//locations[n].locators_radius.reload.reload_grot = 1.8;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Tortuga_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Tortuga_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "Tortuga_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Tortuga_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "Tortuga_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";
	//locations[n].reload.l7.close_for_night = 1;

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "Tortuga_bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload9_back";
	locations[n].reload.l9.go = "Tortuga_brothel";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Brothel";

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "Tortuga_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;

	locations[n].reload.gate.name = "gate_back";
	locations[n].reload.gate.go = "Tortuga_ExitTown";
	locations[n].reload.gate.emerge = "reload4";
	locations[n].reload.gate.autoreload = "0";
	locations[n].reload.gate.label = "ExitTown";
	
	locations[n].reload.jail.name = "reload_jail";
	locations[n].reload.jail.go = "Tortuga_prison";
	locations[n].reload.jail.emerge = "reload1";
	locations[n].reload.jail.autoreload = "0";
	locations[n].reload.jail.label = "Prison";

    // --> Квестовые локации.
	locations[n].reload.l13.name = "basement1";
	locations[n].reload.l13.go = "Tortuga_Cave";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "Cave";

	locations[n].reload.l14.name = "houseS2";
	locations[n].reload.l14.go = "Tortuga_houseS2";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "Tibo House";
	locations[n].reload.l14.close_for_night = 1;
	
	locations[n].reload.l15.name = "houseS3"; 
	locations[n].reload.l15.go = "Tortuga_houseS3";
	locations[n].reload.l15.emerge = "reload1";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "Gaspard_Gold House";
	locations[n].reload.l15.disable = 1; // В релизе закрыть
	
	locations[n].reload.l22.name = "houseS4";
	locations[n].reload.l22.go = "Tortuga_brothelElite";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";
	locations[n].reload.l22.disable = 1;
	
    // --> Комоны, загрушки. Номера с начинаются с 20.
	locations[n].reload.l20.name = "houseF2"; // 2*
	locations[n].reload.l20.go = "Tortuga_HouseHut";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";

	locations[n].reload.l23.name = "houseS1"; // 2*
	locations[n].reload.l23.go = "CommonStoneHouse";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseS6"; // 1*
	locations[n].reload.l24.go = "CommonRoom_MH5";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";
	
	locations[n].reload.l25.name = "houseH2"; // 1*
	locations[n].reload.l25.go = "CommonRoom_MH7";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "House";

	locations[n].reload.l26.name = "houseSp3"; 
	locations[n].reload.l26.go = "CommonResidence_BackHall";
	locations[n].reload.l26.emerge = "reload1";
	locations[n].reload.l26.autoreload = "0";
	locations[n].reload.l26.label = "House";

	locations[n].reload.l27.name = "houseF1"; //1*
	locations[n].reload.l27.go = "CommonRoom_MH10";
	locations[n].reload.l27.emerge = "reload1";
	locations[n].reload.l27.autoreload = "0";
	locations[n].reload.l27.label = "House";

	locations[n].reload.l28.name = "houseSp2"; //2*
	locations[n].reload.l28.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l28.emerge = "reload1";
	locations[n].reload.l28.autoreload = "0";
	locations[n].reload.l28.label = "House";

	locations[n].reload.l29.name = "houseS5"; //1*
	locations[n].reload.l29.go = "CommonRoom_MH9";
	locations[n].reload.l29.emerge = "reload1";
	locations[n].reload.l29.autoreload = "0";
	locations[n].reload.l29.label = "House";
	
	locations[n].reload.l30.name = "houseH3"; //1*
	locations[n].reload.l30.go = "CommonRoom_MH2";
	locations[n].reload.l30.emerge = "reload1";
	locations[n].reload.l30.autoreload = "0";
	locations[n].reload.l30.label = "House";
	
	locations[n].reload.l31.name = "houseH4"; //1*
	locations[n].reload.l31.go = "CommonRoom_MH3";
	locations[n].reload.l31.emerge = "reload1";
	locations[n].reload.l31.autoreload = "0";
	locations[n].reload.l31.label = "House";
	
	locations[n].reload.l32.name = "houseH1"; //1*
	locations[n].reload.l32.go = "CommonRoom_MH4";
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.autoreload = "0";
	locations[n].reload.l32.label = "House";
	
	locations[n].reload.l33.name = "houseF3"; //1*
	locations[n].reload.l33.go = "CommonFlamHouse";
	locations[n].reload.l33.emerge = "reload1";
	locations[n].reload.l33.autoreload = "0";
	locations[n].reload.l33.label = "House";
	
	locations[n].reload.l34.name = "houseF4"; //1*
	locations[n].reload.l34.go = "CommonCobHouse";
	locations[n].reload.l34.emerge = "reload1";
	locations[n].reload.l34.autoreload = "0";
	locations[n].reload.l34.label = "House";
	
	locations[n].reload.l35.name = "houseSp4"; //2*
	locations[n].reload.l35.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l35.emerge = "reload1";
	locations[n].reload.l35.autoreload = "0";
	locations[n].reload.l35.label = "House";
	
	locations[n].reload.l36.name = "houseSp5"; //2*
	locations[n].reload.l36.go = "CommonDoubleflourHouse_2";
	locations[n].reload.l36.emerge = "reload1";
	locations[n].reload.l36.autoreload = "0";
	locations[n].reload.l36.label = "House";
	
	locations[n].locators_radius.quest.roof = 1.5;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	n = n + 1;

  	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТАВЕРНА
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\Tavern07\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "Tortuga";
  	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].models.always.tavern = "tavern07";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "tavern07_locators";
	locations[n].models.always.window = "tavern07_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "tavern07_patch";
	//Night
	locations[n].models.night.charactersPatch = "tavern07_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tortuga_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	
	locations[n].reload.l3.name = "reload4_back";
	locations[n].reload.l3.go = "Tortuga_tavern_passageroom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Tavern upstairs";
	
	locations[n].reload.l4.name = "reload5_back";
	locations[n].reload.l4.go = "Tortuga_tavern_passageroom";
	locations[n].reload.l4.emerge = "reload2";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern upstairs";
	
	locations[n].reload.l5.name = "reload3_back";
	locations[n].reload.l5.go = "Tortuga_tavern_passageroom";
	locations[n].reload.l5.emerge = "reload3";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Tavern upstairs";
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// КОМНАТА В ТАВЕРНЕ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
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
	locations[n].reload.l1.go = "Tortuga_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// КОМНАТА В ТАВЕРНЕ для прохода на балкон
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_tavern_passageroom";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
 	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\BigHouse06\";
	locations[n].models.always.house = "BigHouse06";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouse06_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.locators = "BigHouse06_locators";

	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "BigHouse06_patch";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse06_patch";
	locations[n].models.night.locators = "BigHouse06_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_tavern";
	locations[n].reload.l1.emerge = "reload4_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tortuga_tavern";
	locations[n].reload.l2.emerge = "reload5_back";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern";
	
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tortuga_tavern";
	locations[n].reload.l3.emerge = "reload3_back";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Tavern";

	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// МАГАЗИН
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store01\";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
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
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

    ////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РОСТОВЩИК
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_Bank";
	locations[n].id.label = "Usurer House";
	locations[n].filespath.models = "locations\inside\bank01\";
	locations[n].image = "loading\inside\bank.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Tortuga";
  	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].models.always.locators = "Bank01_locators";
	locations[n].models.always.store = "Bank01";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Bank01_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "bank01_patch";
	//Night
	locations[n].models.night.charactersPatch = "bank01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "reload8";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonResidence_5";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// БОРДЕЛЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_Brothel";
	locations[n].id.label = "Brothel";
	locations[n].filespath.models = "locations\inside\Brothel\";
	locations[n].image = "loading\inside\brothell_hall.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	locations[n].brothel = true;
	//Models
	//Always
	locations[n].models.always.locators = "Brothel_locators";
	locations[n].models.always.store = "Brothel";
	locations[n].models.always.window = "brothel_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Brothel_patch";
	//Night
	locations[n].models.night.charactersPatch = "Brothel_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tortuga_Brothel_room";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Brothel Room";
	locations[n].reload.l2.disable = 1;  //закроем, но связка пусть будет для квестов.

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Tortuga_SecBrRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комнаты в борделе
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_Brothel_room";
	locations[n].id.label = "Brothel Room";
	locations[n].filespath.models = "locations\inside\Brothel_room\";
	locations[n].image = "loading\inside\brothell_room.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].models.always.locators = "Brothel_room_locators";
	locations[n].models.always.store = "Brothel_room";
	locations[n].models.always.window = "Brothel_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Brothel_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Brothel_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_brothel";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].locators_radius.item.item1 = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_SecBrRoom"; // вторая комната борделя
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\BigHouse03.tga";
 	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
  	locations[n].islandId = "Tortuga";
	locations[n].brothel = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\BigHouse03\";
	locations[n].models.always.house = "BigHouse03";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouse03_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "BigHouse03_patch";
	locations[n].models.day.locators = "BigHouse03_locators";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse03_patch";
	locations[n].models.night.locators = "BigHouse03_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_Brothel";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";

	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ВЕРФЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\Shipyard02\";
	locations[n].image = "loading\inside\shipyard.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "Tortuga";
  	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].models.always.locators = "Shipyard02_locators";
	locations[n].models.always.shipyard = "Shipyard02";
	locations[n].models.always.shipyard.level = 65538;
	locations[n].models.always.window = "shipyard02_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Shipyard02_patch";
	//Night
	locations[n].models.night.charactersPatch = "Shipyard02_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	locations[n].locators_radius.item.item1 = 1.0;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РЕЗИДЕНЦИЯ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_townhall";
	locations[n].id.label = "Townhall";
	locations[n].filespath.models = "locations\inside\Residence01";
	locations[n].image = "loading\inside\residence.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
 	// стража
	locations[n].soldiers = true;
	LAi_LocationFantomsGen(&locations[n], true);
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
	locations[n].locators_radius.reload.dialog_event = 0.2;
	locations[n].locators_radius.camdetector.dialog_event = 2.2;

	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonResidence_4";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";

	locations[n].reload.l3.name = "reload3"; //кабинет направо от входа
	locations[n].reload.l3.go = "Tortuga_townhallRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_townhallRoom"; // c переходом в спальню
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\BigHouse02.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
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
	locations[n].reload.l1.go = "Tortuga_townhall";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Room";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Tortuga_townhallBedroom"; // Rebbebion, пришлось, ибо коммон :(
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Bedroom";
	
	locations[n].private1.key = "key_levasser";
	locations[n].private1.key.delItem = true;
	locations[n].private1.money = 10000;
	locations[n].private1.items.chest = 2;
	locations[n].private1.items.icollection = 1;
	locations[n].private1.items.blade_24 = 1;
	locations[n].private1.items.potion2 = 10;
	locations[n].private1.items.berserker_potion = 2;
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Квестовые покои Марселины
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_townhallBedroom";
	locations[n].id.label = "Bedroom";
	locations[n].image = "loading\inside\Bedroom.tga";
	locations[n].MustSetReloadBack = true;
	locations[n].Bedroom = true; //различаем типы локаций в резиденции, надо т.к. id.label затирается
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Always
	locations[n].filespath.models = "locations\inside\bedRoom1";
	locations[n].models.always.bedRoom1 = "bedRoom1";
	locations[n].models.always.bedRoom1.level = 65538;
	Locations[n].models.always.bedRoom1windows = "mediumhouse01_windows";
	Locations[n].models.always.bedRoom1windows.tech = "LocationWindows";
	locations[n].models.always.bedRoom1windows.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.locators = "bedRoom1_locators";
	Locations[n].models.day.bedRoom1rand = "bedRoom1_rand";
	locations[n].models.day.charactersPatch = "bedRoom1_patch";
	//Night
	locations[n].models.night.locators = "bedRoom1_Nlocators";
	locations[n].models.night.charactersPatch = "bedRoom1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_townhallRoom";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Room";
	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_church";
	locations[n].id.label = "Church";
	locations[n].image = "loading\inside\church.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\churchInside2";
	locations[n].models.always.churchInside2 = "churchInside2";
	locations[n].models.always.churchInside2.level = 65538;
	locations[n].models.always.locators = "churchInside2_locators";
	
	locations[n].models.always.backgroundInsides = "backgroundInsides";
	locations[n].models.always.backgroundInsides.level = 65529;
	
	Locations[n].models.always.churchInside2windows = "churchInside2_windows";
	Locations[n].models.always.churchInside2windows.tech = "LocationWindows";
	locations[n].models.always.churchInside2windows.level = 65539;
	
	Locations[n].models.always.churchInside2alpha = "churchInside2_alpha";
	Locations[n].models.always.churchInside2alpha.tech = "LocationWindows";
	locations[n].models.always.churchInside2alpha.level = 65540;
	
	Locations[n].models.always.churchInside2gold = "churchInside2_gold";
	Locations[n].models.always.churchInside2gold.reflection = 0.6;
	Locations[n].models.always.churchInside2gold.tech = "EnvironmentShader";
	locations[n].models.always.churchInside2gold.level = 65541;
	//Day
	locations[n].models.day.charactersPatch = "churchInside2_patch";
	//Night
	locations[n].models.night.charactersPatch = "churchInside2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ПОРТОВЫЙ ОФИС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\portoffice.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\PortOffice4";
	locations[n].models.always.housePortOffice = "PortOffice";
	locations[n].models.always.housePortOffice.level = 65538;
	locations[n].models.always.locators = "PortOffice_locators";

	Locations[n].models.always.PortOffice = "PortOffice_windows";
	Locations[n].models.always.PortOffice.tech = "LocationWindows";
	locations[n].models.always.PortOffice.level = 65539;

	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "PortOffice_patch";
	//Night
	locations[n].models.night.charactersPatch = "PortOffice_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Элитный бордель
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_brothelElite";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\BigHouseBack.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\brothelElite";
	locations[n].models.always.house = "brothelElite";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "brothelElite_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "brothelElite_patch";
	locations[n].models.day.locators = "brothelElite_locators";
	//Night
	locations[n].models.night.charactersPatch = "brothelElite_patch";
	locations[n].models.night.locators = "brothelElite_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload2";
	locations[n].reload.l1.go = "Tortuga_brothelElite_room2";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Townhall";
	locations[n].reload.l1.disable = 1;

	locations[n].reload.l2.name = "reload3";
	locations[n].reload.l2.go = "Tortuga_brothelElite_room1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "BedRoom";
	locations[n].reload.l2.disable = 1;

	locations[n].reload.l3.name = "reload1";
	locations[n].reload.l3.go = "Tortuga_town";
	locations[n].reload.l3.emerge = "houseS4";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Элитный бордель, верхняя комната
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_brothelElite_room1";
	locations[n].id.label = "Bedroom";
	locations[n].image = "loading\inside\Bedroom.tga";
	locations[n].Bedroom = true; //различаем типы локаций в резиденции, надо т.к. id.label затирается
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Always
	locations[n].filespath.models = "locations\inside\brothelElite_room1";
	locations[n].models.always.bedRoom1 = "brothelElite_room1";
	locations[n].models.always.bedRoom1.level = 65538;
	Locations[n].models.always.bedRoom1windows = "brothelElite_room1_windows";
	Locations[n].models.always.bedRoom1windows.tech = "LocationWindows";
	locations[n].models.always.bedRoom1windows.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.locators = "brothelElite_room1_locators";
	Locations[n].models.day.bedRoom1rand = "brothelElite_room1_rand";
	locations[n].models.day.charactersPatch = "brothelElite_room1_patch";
	//Night
	locations[n].models.night.locators = "brothelElite_room1_Nlocators";
	locations[n].models.night.charactersPatch = "brothelElite_room1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_brothelElite";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Элитный бордель, нижняя комната
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_brothelElite_room2";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\BigHouse01.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\brothelElite_room2";
	locations[n].models.always.model = "brothelElite_room2";
	locations[n].models.always.model.level = 65538;
	locations[n].models.day.locators = "brothelElite_room2_locators";
	locations[n].models.night.locators = "brothelElite_room2_Nlocators";
	locations[n].models.always.window = "brothelElite_room2_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "brothelElite_room2_patch";
	//Night
	locations[n].models.night.charactersPatch = "brothelElite_room2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_brothelElite";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// дом по работорговцу
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_HouseHut";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\TwoFloorHouse.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\TwoFloorHouse";
	locations[n].models.always.house = "TwoFloorHouse";
	locations[n].models.always.house.level = 65538;
	locations[n].models.day.locators = "TwoFloorHouse_locators";
	locations[n].models.night.locators = "TwoFloorHouse_Nlocators";
	locations[n].models.always.window = "TwoFloorHouse_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.TwoFloorHouseRand= "TwoFloorHouse_rand";
	locations[n].models.day.charactersPatch = "TwoFloorHouse_patch";
	//Night
	locations[n].models.night.charactersPatch = "TwoFloorHouse_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "houseF2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.item.item2 = 0.9;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом Анри Тибо
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_houseS2";
	locations[n].filespath.models = "locations\inside\FlamHouse";
	locations[n].id.label = "Tibo House";
	locations[n].image = "loading\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].models.always.tavern = "FlamHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "FlamHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "FlamHouse_locators";
	locations[n].models.night.locators = "FlamHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "FlamHouse_patch";
	//Night
	locations[n].models.night.charactersPatch = "FlamHouse_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "houseS2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload3";
	locations[n].reload.l2.go = "CommonPirateResidence";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";

	locations[n].reload.l3.name = "reload4";
	locations[n].reload.l3.go = "CommonDoubleflourRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";
	
	locations[n].box1.QuestClosed = true;
	locations[n].box2.QuestClosed = true;
	LAi_LocationFightDisable(&locations[n], true);
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом Гаспара Златозубого
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_houseS3";
	locations[n].filespath.models = "locations\inside\store06";
	locations[n].id.label = "Gaspard_Gold House";
	locations[n].image = "loading\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Tortuga";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].models.always.locators = "Store06_locators";
	locations[n].models.always.store = "Store06";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Store06_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Store06_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store06_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_town";
	locations[n].reload.l1.emerge = "houseS3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].box1.QuestClosed = true;
	locations[n].box2.QuestClosed = true;
	LAi_LocationFightDisable(&locations[n], true);
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пещера Тортуги с выходом в бухту
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_Cave";
	locations[n].image = "loading\inside\dungeon.tga";
	locations[n].id.label = "dungeon";
	//Sound
	locations[n].townsack = "Tortuga";
	locations[n].type = "Dungeon";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\DungeonVault1";
	locations[n].models.always.DungeonVault1 = "DungeonVault1";
	locations[n].models.always.InquisitionDungeonVault1Fonars = "DungeonVault1_fonars";
	locations[n].models.always.locators = "DungeonVault1TR_locators";	
/*
	Locations[n].models.always.rays = "DungeonVault1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;	
*/	
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
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "Shore58";
	locations[n].reload.l1.emerge = "reload2";

	locations[n].reload.l2.name = "reload1";
	locations[n].reload.l2.go = "Tortuga_town";
	locations[n].reload.l2.emerge = "basement1";
	locations[n].reload.l2.autoreload = "0";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пыточная Левассера
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_Torture_room";
	locations[n].id.label = "Torture room";
	locations[n].image = "loading\Crypt_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].lockWeather = "Inside";
	//Sound
	//locations[n].type = "Dungeon";
	locations[n].type = "alcove";
	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Torture_room";
	locations[n].models.always.cryptbig = "Torture_room";
	locations[n].models.always.locators = "Torture_room_locators";
	//Day
	locations[n].models.day.charactersPatch = "Torture_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Torture_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Tortuga_Cave";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Crypt";
	n = n + 1;	
	
	////////////////////// prison ////////////////////////////
	Locations[n].id = "Tortuga_prison";
	locations[n].id.label = "Prison";
	Locations[n].image = "loading\inside\prison.tga";
	locations[n].townsack = "Tortuga";
    locations[n].parent_colony = "Tortuga";
 	locations[n].fastreload = "Tortuga";
	locations[n].islandId = "Tortuga";
	//Sound
	locations[n].type = "jail";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\prison1";
	locations[n].models.always.prison1 = "prison1";
	locations[n].models.always.lamps = "prison1_lamps";
	locations[n].models.always.locators = "prison1_locators";	
	locations[n].models.always.chest = "chest1";
	//Day
	locations[n].models.day.charactersPatch = "prison1_patch";
	//Night
	locations[n].models.night.charactersPatch = "prison1_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
    //Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "Tortuga_town";
	Locations[n].reload.l1.emerge = "reload_jail";
	Locations[n].reload.l1.autoreload = "0";
	
	locations[n].locators_radius.box.box1 = 0.8;
	locations[n].box1.QuestClosed = true;
	n = n + 1;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	//Sound
	locations[n].type = "jungle";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitW";
	Locations[n].models.always.townExit = "townExitW";
	Locations[n].models.always.townWalls = "townExitW_stone";
	
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
	locations[n].reload.l1.name = "reload3_back";
	locations[n].reload.l1.go = "Mayak6";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Mayak6";
	locations[n].locators_radius.reload.reload3_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tortuga_jungle_01";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Tortuga_Fort";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Tortuga Fort";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Tortuga_town";
	locations[n].reload.l4.emerge = "gate_back";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tortuga";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маяк Торгуги
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Mayak6";
	locations[n].id.label = "Mayak6";
	locations[n].worldmap = "Mayak6";
	locations[n].image = "loading\outside\lighthouse.tga";
	//Sound
	locations[n].type = "mayak";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Lighthouse";
	Locations[n].models.always.lighthouse = "lighthouse";
	locations[n].models.always.lighthouse.sea_reflection = 1;
	Locations[n].models.always.lighthouseSeabed = "lighthouse_sb";
	Locations[n].models.always.locators = "lighthouse_locators";
	
	Locations[n].models.always.dooropen = "lighthouse_dooropen";
	Locations[n].models.always.dooropen.tech = "DLightModel";	
	
	Locations[n].models.always.windows = "lighthouse_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66530;
		
	Locations[n].models.always.grassPatch = "lighthouse_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";		
	//Day
	locations[n].models.day.winday = "lighthouse_winday";
	locations[n].models.day.winday.tech = "LocationWindows";
	locations[n].models.day.winday.level = 66530;
	locations[n].models.day.fonar = "lighthouse_fd";
	locations[n].models.day.charactersPatch = "lighthouse_patch";
	Locations[n].models.day.jumpPatch = "lighthouse_jamp";
	
	locations[n].models.day.glassinday = "lighthouse_glassinday";
	Locations[n].models.day.glassinday.tech = "LocationWindows";
	locations[n].models.day.glassinday.level = 66531;
	
	locations[n].models.day.glassonday = "lighthouse_glassonday";
	Locations[n].models.day.glassonday.tech = "LocationWindows";
	locations[n].models.day.glassonday.level = 66532;	
	//Night
	locations[n].models.night.volumeLight= "lighthouse_volumeLight";
	locations[n].models.night.volumeLight.tech = "LighthouseLight";
	locations[n].models.night.volumeLight.level = 66529;	
	
	locations[n].models.night.fonar = "lighthouse_fn";
	locations[n].models.night.winnight = "lighthouse_winnight";
	locations[n].models.night.winnight.tech = "LocationWindows";
	locations[n].models.night.winnight.level = 66530;
	locations[n].models.night.charactersPatch = "lighthouse_patch";	
	Locations[n].models.night.jumpPatch = "lighthouse_jamp";
	
	locations[n].models.night.glassinnight = "lighthouse_glassinnight";
	Locations[n].models.night.glassinnight.tech = "LocationWindows";
	locations[n].models.night.glassinnight.level = 66531;
	
	locations[n].models.night.glassonnight = "lighthouse_glassonnight";
	Locations[n].models.night.glassonnight.tech = "LocationWindows";
	locations[n].models.night.glassonnight.level = 66532;
	
	locations[n].models.night.fonaronnight = "lighthouse_fonaronnight";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_ExitTown";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload1_back = 3.0;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Tortuga";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 12.0;
	
	locations[n].reload.l3.name = "reload2";
	locations[n].reload.l3.go = "Mayak6_Lighthouseroom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.label = "room";
	locations[n].locators_radius.reload.reload2 = 1.0;
	n = n + 1;
	
	////////////////////////////////////////////////////////////////////////////////
	//////////комната на маяке
	////////////////////////////////////////////////////////////////////////////////
	
	locations[n].id = "Mayak6_Lighthouseroom";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "Tortuga";
	locations[n].islandId = "Tortuga";
	//Sound
	locations[n].type = "house";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse09";
	locations[n].models.always.house = "mediumhouse09";
	locations[n].models.always.house.level = 65538;
	locations[n].models.day.locators = "mediumhouse09_locators";
	locations[n].models.night.locators = "mediumhouse09_Nlocators";

	Locations[n].models.always.mediumhouse09windows = "mediumhouse09_windows";
	Locations[n].models.always.mediumhouse09windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse09windows.level = 65539;

	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.mediumhouse09rand= "mediumhouse09_rand";
	locations[n].models.day.charactersPatch = "mediumhouse09_patch";
	//Night
	locations[n].models.night.charactersPatch = "mediumhouse09_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Mayak6";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Mayak6";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle13";
	Locations[n].models.always.jungle = "jungle13";	
	Locations[n].models.always.locators = "jungle13_locators";		
	Locations[n].models.always.grassPatch = "jungle13_grass";
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
	locations[n].models.day.charactersPatch = "jungle13_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle13_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore58";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore58";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tortuga_ExitTown";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "ExitTown";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Tortuga_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	//Sound
	locations[n].type = "jungle";
 	locations[n].islandId = "Tortuga";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt2";
	Locations[n].models.always.caveEnt2 = "caveEnt2";	
	Locations[n].models.always.locators = "caveEnt2_locators";		
	Locations[n].models.always.grassPatch = "caveEnt2_grass";
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
	Locations[n].models.always.l4 = "plan4";
	Locations[n].models.always.l4.level = 6;
	Locations[n].models.always.l4.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "caveEnt2_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt2_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_Grot";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Grot";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tortuga_jungle_01";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Tortuga_Grot";
	locations[n].id.label = "Grot";
    locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
 	locations[n].islandId = "Tortuga";
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
/*	
	Locations[n].models.always.rays = "grotto2_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;
*/	
	//Day
	locations[n].models.day.charactersPatch = "grotto2_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Tortuga_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж 58
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore58";
	locations[n].id.label = "Shore58";
	locations[n].worldmap = "Shore58";
	locations[n].image = "loading\outside\harbor3.tga";
	//Sound
	locations[n].type = "seashore";
 	locations[n].islandId = "Tortuga";
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
	locations[n].reload.l1.go = "Tortuga_jungle_01";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 1;
	
	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Tortuga_Cave";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Cave";
    locations[n].locators_radius.reload.reload2_back = 1.5;

	locations[n].reload.l3.name = "boat";
	locations[n].reload.l3.go = "Tortuga";
	locations[n].reload.l3.emerge = "reload_3";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Sea";
	locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;
	
	return n;
}
