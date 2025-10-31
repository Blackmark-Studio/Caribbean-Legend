
void ApplyMigration(ref migrationState) {
	
	NewQuests();
	Goods_Refactoring();
	BoardingDeks();
	Cabins();
	CamCollider();
	Remove_ShipHP_Penalty();
	SchoonerWaterLine();
	LeFransua_Letter();
	SP_Letter();
}

void NewQuests()
{
	ref loc, itm;
	int n;
	
	// Изменяем Порто Белло
	n = FindLocation("PortoBello_town");
	locations[n].reload.l27.name = "houseH3";
	locations[n].reload.l27.go = "PortoBello_houseH3";
	locations[n].reload.l27.emerge = "reload1";
	locations[n].reload.l27.autoreload = "0";
	locations[n].reload.l27.label = "House";
	
	locations[n].reload.l32.name = "houseSp1";
	locations[n].reload.l32.go = "PortoBello_houseSp1";
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.autoreload = "0";
	locations[n].reload.l32.label = "House";
	
	// Квестовый дом в Порто Белло
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
	locations[n].id = "PortoBello_houseH3";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse10.tga";
 	//Town sack
	locations[n].townsack = "PortoBello";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortoBello";
 	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse07";
	locations[n].models.always.house = "mediumhouse07";
	locations[n].models.always.house.level = 65538;
	locations[n].models.day.locators = "mediumhouse07_locators";
	locations[n].models.night.locators = "mediumhouse07_Nlocators";

	Locations[n].models.always.mediumhouse07windows = "mediumhouse07_windows";
	Locations[n].models.always.mediumhouse07windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse07windows.level = 65539;
	locations[n].models.always.tul = "mediumhouse07_tul";
	Locations[n].models.always.tul.tech = "LocationWaterFall";
	locations[n].models.always.tul.level = 180;

	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.mediumhouse07rand= "mediumhouse07_rand";
	locations[n].models.day.charactersPatch = "mediumhouse07_patch";
	//Night
	locations[n].models.night.charactersPatch = "mediumhouse07_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortoBello_town";
	locations[n].reload.l1.emerge = "houseH3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	LAi_LocationFightDisable(&locations[n], true);
	
	// Квестовый дом Долорес в Порто Белло
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
	locations[n].id = "PortoBello_houseSp1";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\largehouse01.tga";
 	//Town sack
	locations[n].townsack = "PortoBello";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortoBello";
 	locations[n].islandId = "Mein";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\largehouse01";
	locations[n].models.always.largehouse01 = "largehouse01";
	locations[n].models.always.largehouse01.level = 65538;
	locations[n].models.always.locators = "largehouse01_locators";

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
	locations[n].reload.l1.go = "PortoBello_town";
	locations[n].reload.l1.emerge = "houseSp1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	
	LAi_LocationFightDisable(&locations[n], true);
	
	// Изменяем Сан-Хосе
	n = FindLocation("PortSpein_town");
	locations[n].reload.l20.name = "houseS1";
	locations[n].reload.l20.go = "PortSpein_houseS1";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";
	locations[n].reload.l20.close_for_night = 1;
	
	// Квестовый дом в Сан-Хосе
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
	locations[n].id = "PortSpein_houseS1";
	locations[n].filespath.models = "locations\inside\CobHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CobHouse.tga";
	//Town sack
	locations[n].townsack = "PortSpein";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
 	locations[n].islandId = "Trinidad";
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
	locations[n].reload.l1.go = "PortSpein_town";
	locations[n].reload.l1.emerge = "houseS1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	
	// Изменяем Белиз
	n = FindLocation("Beliz_town");
	locations[n].reload.l25.name = "houseSp1";
	locations[n].reload.l25.go = "Beliz_houseSp1";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "House";
	
	// Квестовый дом в Белизе
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
	locations[n].id = "Beliz_houseSp1"; //с комнатой на втором этаже
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\largehouse01.tga";
	//Town sack
	locations[n].townsack = "Beliz";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Beliz";
 	locations[n].islandId = "Mein";
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
	locations[n].reload.l1.go = "Beliz_town";
	locations[n].reload.l1.emerge = "houseSp1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].box1.QuestClosed = true;
	LAi_LocationFightDisable(&locations[n], true);
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Квестовая палуба на корабле, где проходят похороны
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
  	Locations[n].id = "Quest_ShipboardFuneral";
	Locations[n].image = "loading\Quarter_" + rand(1) + ".tga";
	locations[n].id.label = "Boarding deck";
	//Sound
	Locations[n].type = "residence";
	// Locations[n].lockCamAngle = 0.4;
	//Models  
	Locations[n].filespath.models = "locations\decks\outside_deck_QuestMary"; // бриг, сцена похорон
	//Always
	Locations[n].models.always.main = "outside_deck_QuestMary";
	Locations[n].models.always.parts = "outside_deck_QuestMary_parts";
	Locations[n].models.always.ropes = "outside_deck_QuestMary_ropes";
	Locations[n].models.always.locators = "outside_deck_QuestMary_locators";
	Locations[n].models.always.windows = "outside_deck_QuestMary_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	Locations[n].models.always.watermask = "outside_deck_QuestMary_watermask";
	Locations[n].models.always.watermask.tech = "WaterMask";
	Locations[n].models.always.watermask.level = 65500;
	Locations[n].models.always.table_corpse = "outside_deck_QuestMary_table_corpse";
	//Day
	locations[n].models.day.charactersPatch = "outside_deck_QuestMary_patch";
	Locations[n].models.day.deckMediumFonarsDay = "outside_deck_QuestMary_fd";
	//Night
	locations[n].models.night.charactersPatch = "outside_deck_QuestMary_patch";
	Locations[n].models.night.deckMediumFonarsNight = "outside_deck_QuestMary_fd";
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Флейт La Espada del Rey на Бермудах
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
	locations[n].id = "Bermudes_DelRey";
	locations[n].id.label = "La Espada Del Rey";
	locations[n].filespath.models = "locations\Inside\DelRey";
	locations[n].image = "loading\IntsideLSC_" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "Pirates";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "LSC_inside";
	//locations[n].fastreload = "Pirates";
	locations[n].islandId = "Bermudes";
	//Models
	//Always
	Locations[n].models.always.inside = "DelRey";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.seabed = "DelRey_sb";
	Locations[n].models.always.outdoor = "DelRey_outdoor";
	Locations[n].models.always.windows = "DelRey_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;  
	Locations[n].models.always.plan1 = "DelRey_plan1";
	Locations[n].models.always.plan1.tech = "LocationWindows";
	Locations[n].models.always.plan1.level = 65533;
	Locations[n].models.always.plan1.sea_reflection = 1;
	Locations[n].models.always.locators = "DelRey_locators";  
	//Day
	locations[n].models.day.charactersPatch = "DelRey_patch_day";
	//Night
	locations[n].models.night.charactersPatch = "DelRey_patch_day";

	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Shore_ship1";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Shore_ship1";
	
	locations[n].private1.key = "LEDR_key";
	locations[n].private1.key.delItem = true;
	locations[n].private1.items.gold_dublon = 300;
	locations[n].private1.items.amulet_6 = 1;
	locations[n].private1.items.amulet_2 = 1;
	locations[n].private1.items.Mineral3 = 10;
	locations[n].private1.items.Mineral5 = 1;
	locations[n].private1.items.Mineral21 = 1;
	locations[n].private1.items.LEDR_Book = 1;
	locations[n].locators_radius.item.item1 = 1;
	
	// Изменяем бухту Сабу-Матила
	n = FindLocation("Shore_ship1");
	locations[n].reload.l3.name = "reload2";
	locations[n].reload.l3.go = "Bermudes_DelRey";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "La Espada Del Rey";
	locations[n].reload.l3.disable = true;
	locations[n].locators_radius.reload.reload2 = 3;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					НОВЫЕ КВЕСТОВЫЕ ПРЕДМЕТЫ
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	// Письмо для Марисы Кальдера
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	
	makeref(itm,Items[n]);
	itm.id = "LFD_letter"; 
	itm.name = "itmname_LFD_letter";
	itm.describe = "itmdescr_LFD_letter";
	itm.model = "Letter_sp2";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_26";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.ItemType = "QUESTITEMS";
	
	// Книга кузнеца
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	
	makeref(itm,Items[n]); // Книга кузнеца
	itm.id = "OZ_book";
	itm.name = "itmname_OZ_book";
	itm.describe = "itmdescr_OZ_book";
	itm.model = "";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_22";
	itm.Weight = 0.1;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	
	// Записка с убитого шулера
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	
	makeref(itm,Items[n]); // Записка с убитого шулера
	itm.id = "OZ_letter";
	itm.name = "itmname_OZ_letter";
	itm.describe = "itmdescr_OZ_letter";
	itm.model = "letter";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_22";
	itm.Weight = 0.1;
	itm.price = 10;
	itm.ItemType = "QUESTITEMS";
	
	// Кандалы
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	
	makeref(itm,Items[n]); //Кандалы
	itm.id = "Shackles";
	itm.name = "itmname_Shackles";
	itm.describe = "itmdescr_Shackles";
	itm.model = "Shackles";
	itm.picIndex = 15;
	itm.picTexture = "ITEMS_29";
	itm.price = 0;
	itm.Weight = 0.3;
	itm.ItemType = "QUESTITEMS";
	
	// Дневник Диего Веласкеса де Куэльяра
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	
	makeref(itm,Items[n]);
	itm.id = "LEDR_Book";
	itm.name = "itmname_LEDR_Book";
	itm.describe = "itmdescr_LEDR_Book";
    itm.model = "OpenBook";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_26";
	itm.price = 0;
	itm.Weight = 0.2;
	itm.ItemType = "QUESTITEMS";
	
	// Ключ от сундука на флейте "La Espada del Rey"
	makeref(itm, items[FindItem("Reserve_item_12")]);
	itm.id = "LEDR_key";
	itm.name = "itmname_LEDR_key";
	itm.describe = "itmdescr_LEDR_key";
	itm.model = "keysimple";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_36";
	itm.Weight = 0.1;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	
	// Новые предметы для квеста Мэри
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	
	makeref(itm,Items[n]); // Шляпа Терезы
	itm.id = "hat11";
	itm.groupID	= HAT_ITEM_TYPE;
	itm.name = "itmname_hat11";
	itm.describe = "itmdescr_hat11";
	itm.model = "hat11";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_40";
	itm.price = 50000;
	itm.Weight = 0.1;
	itm.ItemType = "SUPPORT";
	itm.TradeType = ITEM_TRADE_AMMUNITION;
	
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	
	InitStdBlade160(n, "blade_WR", "ITEMS_41", 14,    TGT_QUEST,  B_EXCELLENT, "FencingH", 22, 1.05, 1.10, 0, 0, 0, 	  10000);	// Палаш Возрождённый
	
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	
	InitStdTalisman160(n, "talisman21", "", "ITEMS_41", 15, rand(5000), 0.5,             ""); // Оберег контрабандиста
}

void Goods_Refactoring()
{
	int n, i, agQty, oldAgQty, importQty, new_importQty;
	aref arCurType;
	string sAttr, sAttr1;
	
	for (n = 0; n < MAX_ISLANDS; n++)
	{
		if(CheckAttribute(&Islands[n],"Trade.Import"))
		{
			makearef(arCurType, Islands[n].Trade.Import);
			importQty = GetAttributesNum(arCurType);
		}
		if(CheckAttribute(&Islands[n],"Trade.Aggressive"))
		{
			makearef(arCurType, Islands[n].Trade.Aggressive);
			agQty = GetAttributesNum(arCurType);
			for(new_importQty = importQty; new_importQty <= importQty + agQty; new_importQty++)
			{
				sAttr = "id" + new_importQty;
				for(oldAgQty = 1; oldAgQty <= agQty; oldAgQty++)
				{
					sAttr1 = "id" + oldAgQty;
					Islands[n].Trade.Import.(sAttr) = Islands[n].Trade.Aggressive.(sAttr1);
				}
			}
			DeleteAttribute(&Islands[n],"Trade.Aggressive");
		}
	}
	
	for(i = 0; i < STORE_QUANTITY; i++)
    {
		for (n = 0; n < GetArraySize(&Goods); n++)
		{
			sAttr = Goods[n].name;
			if(CheckAttribute(&stores[i], "Goods." + sAttr + ".TradeType"))
			{
				 if(stores[i].Goods.(sAttr).TradeType == T_TYPE_AGGRESSIVE)
				 {
					 stores[i].Goods.(sAttr).TradeType = T_TYPE_IMPORT;
				 }
			}
		}
    }
	
	if(CheckAttribute(NullCharacter, "PriceList"))
	{
		makearef(arCurType, NullCharacter.PriceList);
		agQty = GetAttributesNum(arCurType);
		for(i = 0; i < agQty; i++)
		{
			aref arCity = GetAttributeN(arCurType, i);
			SetPriceListByStoreMan(&Colonies[FindColony(GetAttributeName(arCity))]);
		}
	}
	
	int quantity = GetArraySize(&Goods);
	SetArraySize(&Goods, quantity + 1);

	n = quantity;
	ref curGood;
	makeref(curGood, Goods[n]);

	curGood.Name             = "Cannon_48";
    curGood.CannonIdx        = CANNON_TYPE_CANNON_LBS48;
    curGood.Cost             = Cannon[CANNON_TYPE_CANNON_LBS48].Cost;
    curGood.Weight           = Cannon[CANNON_TYPE_CANNON_LBS48].Weight;
    curGood.Units            = 1;
    curGood.AfraidWater      = 0;
    curGood.type             = T_TYPE_CANNONS;
    curGood.trade_type       = T_TYPE_CANNONS;
    curGood.NotSale          = 1;
    curGood.NotGenerate      = 1;
    curGood.FireRange        = Cannon[CANNON_TYPE_CANNON_LBS48].FireRange;
    curGood.DamageMultiply   = Cannon[CANNON_TYPE_CANNON_LBS48].DamageMultiply;
    curGood.ReloadTime       = sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS48]));
    curGood.Norm             = 10; 
    curGood.MediumNorm       = 1.0;
    curGood.SmallNorm        = 1.0;

    
    for(i=0; i<STORE_QUANTITY; i++)
    {
       stores[i].Goods.Cannon_48.TradeType = T_TYPE_CANNONS;
       stores[i].Goods.Cannon_48.Type      = T_TYPE_CANNONS;
       stores[i].Goods.Cannon_48.Norm      = 0;
       stores[i].Goods.Cannon_48.Quantity  = 0;
    }

   
   Cannon[CANNON_TYPE_CULVERINE_LBS36].RealCaliber = 36;
   
   Goods[GOOD_COFFEE].Flags                 = FLAG_GOODS_EXPORT_PLANTS;
   Goods[GOOD_TOBACCO].Flags                = FLAG_GOODS_EXPORT_PLANTS;
   Goods[GOOD_CHOCOLATE].Flags              = FLAG_GOODS_EXPORT_PLANTS;
   
   Goods[GOOD_EBONY].Flags                   = FLAG_GOODS_VALUABLE_EXPORT + FLAG_GOODS_VALUABLE_WOOD;    
   Goods[GOOD_MAHOGANY].Flags                = FLAG_GOODS_VALUABLE_EXPORT + FLAG_GOODS_VALUABLE_WOOD;
   Goods[GOOD_CINNAMON].Flags                = FLAG_GOODS_VALUABLE_EXPORT;
   Goods[GOOD_SANDAL].Flags                  = FLAG_GOODS_VALUABLE_WOOD;
   Goods[GOOD_CANNON_36].Flags               = FLAG_GOODS_CROWN_CANNONS;
   Goods[GOOD_CANNON_42].Flags               = FLAG_GOODS_CROWN_CANNONS;
   Goods[GOOD_CULVERINE_36].Flags            = FLAG_GOODS_CROWN_CANNONS;
   Goods[GOOD_CANNON_48].Flags               = FLAG_GOODS_CROWN_CANNONS;
   
   for(i=0; i<STORE_QUANTITY; i++)
	{
		ref refStore = &stores[i];
		DeleteAttribute(refStore, "Goods.Cannon_48");
	}
	
	RefreshStoresForTheNewGood(GOOD_CANNON_48);
	UpdateAllStores();
}

void BoardingDeks()
{
	int n;
	
	/////////////////////
	n = FindLocation("Boarding_Campus");
	
	DeleteAttribute(&Locations[n], "models");
	SetDefaultLightingModels(n);
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_gundeck_3";
	//Always
	Locations[n].models.always.main = "inside_gundeck_3";
	Locations[n].models.always.parts = "inside_gundeck_3_parts";
	Locations[n].models.always.outside = "inside_gundeck_3_outside";
	Locations[n].models.always.locators = "inside_gundeck_3_locators_combat";
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
	
	/////////////////////////////////////////////
	n = FindLocation("Boarding_Cargohold");
	DeleteAttribute(&Locations[n], "models");
	SetDefaultLightingModels(n);
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_hold_4"; // трюм под бриг и т.п.
	//Always
	Locations[n].models.always.main = "inside_hold_4";
	Locations[n].models.always.parts = "inside_hold_4_parts";
	Locations[n].models.always.outside = "inside_hold_4_outside";
	Locations[n].models.always.locators = "inside_hold_4_locators_combat";
	Locations[n].models.always.rays = "inside_hold_4_rays"; // лучи
	Locations[n].models.always.rays.uvslide.v0 = 0.08;
	Locations[n].models.always.rays.uvslide.v1 = 0.0;
	Locations[n].models.always.rays.tech = "LocationWaterFall";
	Locations[n].models.always.rays.level = 99950;
	Locations[n].models.always.camcollider = "inside_hold_4_camcollider"; // коллайдер
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_hold_4_patch";
	Locations[n].models.day.fonar = "inside_hold_4_fd";
	Locations[n].fonarlights = true; // фонари всегда горят
	//Night
	Locations[n].models.night.charactersPatch = "inside_hold_4_patch";
	Locations[n].models.night.fonar = "inside_hold_4_fn";
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";

    Locations[n].boarding = "true";
	Locations[n].boarding.locatorNum = 10;
	Locations[n].boarding.nextdeck = "";
	Locations[n].InsideDeckType = true;

	//Locations[n].camshuttle = 1;
	locations[n].environment.weather.rain = false;
	
	/////////////////////////////////////////////////////////////////////////
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
	//----------------------------------- товарный трюм - для кораблей большых классов ---------------------------- 
	Locations[n].id = "Boarding_Cargohold_Big";
	Locations[n].id.label = "My_Deck";
	//Info
	Locations[n].image = "loading\Boarding_B" + rand(3) + ".tga";
	//Sound
	Locations[n].type = "deck_fight";

	//Models
	Locations[n].filespath.models = "locations\decks\inside_hold_3";
	//Always
	Locations[n].models.always.main = "inside_hold_3";
	Locations[n].models.always.parts = "inside_hold_3_parts";
	Locations[n].models.always.outside = "inside_hold_3_outside";
	Locations[n].models.always.locators = "inside_hold_3_locators_combat";
	Locations[n].models.always.camcollider = "inside_hold_3_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
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

    Locations[n].boarding = "true";
	Locations[n].boarding.locatorNum = 12;
	Locations[n].boarding.nextdeck = "";
	Locations[n].InsideDeckType = true;

	//Locations[n].camshuttle = 1;
	locations[n].environment.weather.rain = false;
	
	////////////////////////////////////////////////////////////////
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
	//----------------------------------- товарный трюм - для кораблей малых классов ---------------------------- 
	Locations[n].id = "Boarding_Cargohold_Low";
	Locations[n].id.label = "My_Deck";
	//Info
	Locations[n].image = "loading\Boarding_B" + rand(3) + ".tga";
	//Sound
	Locations[n].type = "deck_fight";

	//Models
	Locations[n].filespath.models = "locations\decks\inside_hold_5"; // трюм шлюпа
	//Always
	Locations[n].models.always.main = "inside_hold_5";
	Locations[n].models.always.parts = "inside_hold_5_parts";
	Locations[n].models.always.outside = "inside_hold_5_outside";
	Locations[n].models.always.locators = "inside_hold_5_locators_combat"; // по 7 абордажников
	Locations[n].models.always.camcollider = "inside_hold_5_camcollider"; // коллайдер
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_hold_5_patch";
	Locations[n].models.day.fonar = "inside_hold_5_fd";
	Locations[n].models.always.rays = "inside_hold_5_rays"; // лучи днем
	Locations[n].models.always.rays.uvslide.v0 = 0.08;
	Locations[n].models.always.rays.uvslide.v1 = 0.0;
	Locations[n].models.always.rays.tech = "LocationWaterFall";
	Locations[n].models.always.rays.level = 99950;
	Locations[n].fonarlights = true; // фонари всегда горят
	//Night
	Locations[n].models.night.charactersPatch = "inside_hold_5_patch";
	Locations[n].models.night.fonar = "inside_hold_5_fn";
	
    // Locators_combat
	Locations[n].locators_radius.box.box1 = 0.75;
    Locations[n].locators_radius.box.box2 = 0.75;
    Locations[n].locators_radius.box.box3 = 0.75;
    Locations[n].locators_radius.box.box4 = 0.75;
	//Environment
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";

    Locations[n].boarding = "true";
	Locations[n].boarding.locatorNum = 7;
	Locations[n].boarding.nextdeck = "";
	Locations[n].InsideDeckType = true;

	//Locations[n].camshuttle = 1;
	locations[n].environment.weather.rain = false;
	
	/////////////////////////////////////////////////////
	// абордажный трюм для 1-2 кл
	n = FindLocation("Boarding_GunDeck");
	
	Locations[n].boarding.nextdeck = "Boarding_Cargohold_Big";
}

void Cabins()
{
	int n;
	
	// малая с окнами
	n = FindLocation("Cabin_Medium");
	
	DeleteAttribute(&Locations[n], "models");
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_5"; // каюта шлюпа (малая, с окнами)
	//Always
	Locations[n].models.always.main = "inside_cabin_5";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_5_parts";
	Locations[n].models.always.locators = "inside_cabin_5_locators";
	Locations[n].models.always.camcollider = "inside_cabin_5_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_5_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_5_patch";
	Locations[n].models.day.fonar = "inside_cabin_5_fd";
	Locations[n].models.day.rays = "inside_cabin_5_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_5_patch";
	Locations[n].models.night.fonar = "inside_cabin_5_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

     // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
    Locations[n].locators_radius.box.box2 = 0.5; // дополнительный сундук
    Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.box.box4 = 0.5; // угол стола
	
    Locations[n].locators_radius.interactive.bed = 0.8;
    Locations[n].locators_radius.interactive.bookcase = 0.5;
    Locations[n].locators_radius.interactive.shelf = 0.5;
    Locations[n].locators_radius.interactive.shelf1 = 0.1;
    Locations[n].locators_radius.interactive.shelf2 = 0.1;
    Locations[n].locators_radius.interactive.shelf3 = 0.1;
    Locations[n].locators_radius.interactive.shelf4 = 0.1;
    Locations[n].locators_radius.interactive.shelf5 = 0.1;
    Locations[n].locators_radius.interactive.shelf6 = 0.1;
    Locations[n].locators_radius.interactive.table_capt = 0.5;
    Locations[n].locators_radius.interactive.wardrobe = 0.5;

    Locations[n].locators_radius.randitem.randitem1 = 1;
    Locations[n].locators_radius.randitem.randitem2 = 1;

    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.rld.loc0 = 0.5;
    Locations[n].locators_radius.rld.loc1 = 0.5;
	Locations[n].locators_radius.rld.loc2 = 0.5;
    Locations[n].locators_radius.rld.aloc0 = 0.5;
    Locations[n].locators_radius.rld.aloc1 = 0.5;
	Locations[n].locators_radius.rld.aloc2 = 0.5;
	
	n = FindLocation("My_Cabin_Medium");
	
	DeleteAttribute(&Locations[n], "models");
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_5"; // каюта шлюпа (малая, с окнами)
	//Always
	Locations[n].models.always.main = "inside_cabin_5";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_5_parts";
	Locations[n].models.always.locators = "inside_cabin_5_locators";
	Locations[n].models.always.camcollider = "inside_cabin_5_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_5_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_5_patch";
	Locations[n].models.day.fonar = "inside_cabin_5_fd";
	Locations[n].models.day.rays = "inside_cabin_5_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_5_patch";
	Locations[n].models.night.fonar = "inside_cabin_5_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

     // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
    Locations[n].locators_radius.box.box2 = 0.5; // дополнительный сундук
    Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.box.box4 = 0.5; // угол стола
	
    Locations[n].locators_radius.interactive.bed = 0.8;
    Locations[n].locators_radius.interactive.bookcase = 0.5;
    Locations[n].locators_radius.interactive.shelf = 0.5;
    Locations[n].locators_radius.interactive.shelf1 = 0.1;
    Locations[n].locators_radius.interactive.shelf2 = 0.1;
    Locations[n].locators_radius.interactive.shelf3 = 0.1;
    Locations[n].locators_radius.interactive.shelf4 = 0.1;
    Locations[n].locators_radius.interactive.shelf5 = 0.1;
    Locations[n].locators_radius.interactive.shelf6 = 0.1;
    Locations[n].locators_radius.interactive.table_capt = 0.5;
    Locations[n].locators_radius.interactive.wardrobe = 0.5;

    Locations[n].locators_radius.randitem.randitem1 = 1;
    Locations[n].locators_radius.randitem.randitem2 = 1;

    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.rld.loc0 = 0.5;
    Locations[n].locators_radius.rld.loc1 = 0.5;
	Locations[n].locators_radius.rld.loc2 = 0.5;
    Locations[n].locators_radius.rld.aloc0 = 0.5;
    Locations[n].locators_radius.rld.aloc1 = 0.5;
	Locations[n].locators_radius.rld.aloc2 = 0.5;
	
	// средняя корвет
	n = FindLocation("My_Cabin_Medium2");
	
	DeleteAttribute(&Locations[n], "models");
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_3"; // каюта корвета (средняя, с окнами)
	//Always
	Locations[n].models.always.main = "inside_cabin_3";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_3_parts";
	Locations[n].models.always.locators = "inside_cabin_3_locators";
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
	
	
	n = FindLocation("Cabin_Medium2");
	
	DeleteAttribute(&Locations[n], "models");
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_3"; // каюта корвета (средняя, с окнами)
	//Always
	Locations[n].models.always.main = "inside_cabin_3";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_3_parts";
	Locations[n].models.always.locators = "inside_cabin_3_locators";
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
	
	// малая без окон
	n = FindLocation("Cabin_Small");
	
	DeleteAttribute(&Locations[n], "models");
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_6"; // каюта военной шхуны (малая, без окон)
	//Always
	Locations[n].models.always.main = "inside_cabin_6";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_6_parts";
	Locations[n].models.always.outside = "inside_cabin_6_outside";
	Locations[n].models.always.locators = "inside_cabin_6_locators";
	Locations[n].models.always.camcollider = "inside_cabin_6_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_6_patch";
	Locations[n].models.day.fonar = "inside_cabin_6_fd";
	Locations[n].models.day.rays = "inside_cabin_6_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_6_patch";
	Locations[n].models.night.fonar = "inside_cabin_6_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

	 // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
    Locations[n].locators_radius.box.box2 = 0.5; // дополнительный сундук
    Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.box.box4 = 0.5; // угол стола
	
    Locations[n].locators_radius.interactive.bed = 0.8;
    Locations[n].locators_radius.interactive.bookcase = 0.5;
    Locations[n].locators_radius.interactive.shelf = 0.5;
    Locations[n].locators_radius.interactive.shelf1 = 0.1;
    Locations[n].locators_radius.interactive.shelf2 = 0.1;
    Locations[n].locators_radius.interactive.shelf3 = 0.1;
    Locations[n].locators_radius.interactive.shelf4 = 0.1;
    Locations[n].locators_radius.interactive.shelf5 = 0.1;
    Locations[n].locators_radius.interactive.shelf6 = 0.1;
    Locations[n].locators_radius.interactive.table_capt = 0.5;
    Locations[n].locators_radius.interactive.wardrobe = 0.5;

    Locations[n].locators_radius.randitem.randitem1 = 1;

    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.rld.loc0 = 0.5;
    Locations[n].locators_radius.rld.loc1 = 0.5;
	Locations[n].locators_radius.rld.loc2 = 0.5;
    Locations[n].locators_radius.rld.aloc0 = 0.5;
    Locations[n].locators_radius.rld.aloc1 = 0.5;
	Locations[n].locators_radius.rld.aloc2 = 0.5;
	
	// малая без окон у ГГ
	n = FindLocation("My_Cabin_Small");
	
	DeleteAttribute(&Locations[n], "models");
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_6"; // каюта военной шхуны (малая, без окон)
	//Always
	Locations[n].models.always.main = "inside_cabin_6";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_6_parts";
	Locations[n].models.always.outside = "inside_cabin_6_outside";
	Locations[n].models.always.locators = "inside_cabin_6_locators";
	Locations[n].models.always.camcollider = "inside_cabin_6_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_6_patch";
	Locations[n].models.day.fonar = "inside_cabin_6_fd";
	Locations[n].models.day.rays = "inside_cabin_6_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_6_patch";
	Locations[n].models.night.fonar = "inside_cabin_6_fn";
	
	//Environment
	Locations[n].environment.sea = "true";
	Locations[n].environment.weather = "true";

	locations[n].box1 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box2 = Items_MakeTime(0, 1, 1, 2003);
	locations[n].box3 = Items_MakeTime(0, 1, 1, 2003);

	 // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
    Locations[n].locators_radius.box.box2 = 0.5; // дополнительный сундук
    Locations[n].locators_radius.box.box3 = 0.5; // тумбочка
    Locations[n].locators_radius.box.box4 = 0.5; // угол стола
	
    Locations[n].locators_radius.interactive.bed = 0.8;
    Locations[n].locators_radius.interactive.bookcase = 0.5;
    Locations[n].locators_radius.interactive.shelf = 0.5;
    Locations[n].locators_radius.interactive.shelf1 = 0.1;
    Locations[n].locators_radius.interactive.shelf2 = 0.1;
    Locations[n].locators_radius.interactive.shelf3 = 0.1;
    Locations[n].locators_radius.interactive.shelf4 = 0.1;
    Locations[n].locators_radius.interactive.shelf5 = 0.1;
    Locations[n].locators_radius.interactive.shelf6 = 0.1;
    Locations[n].locators_radius.interactive.table_capt = 0.5;
    Locations[n].locators_radius.interactive.wardrobe = 0.5;

    Locations[n].locators_radius.randitem.randitem1 = 1;

    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.rld.loc0 = 0.5;
    Locations[n].locators_radius.rld.loc1 = 0.5;
	Locations[n].locators_radius.rld.loc2 = 0.5;
    Locations[n].locators_radius.rld.aloc0 = 0.5;
    Locations[n].locators_radius.rld.aloc1 = 0.5;
	Locations[n].locators_radius.rld.aloc2 = 0.5;
	
	// большая каюта
	n = FindLocation("Cabin");
	DeleteAttribute(&Locations[n], "models");
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_2"; // большая каюта
	//Always
	Locations[n].models.always.main = "inside_cabin_2";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_2_parts";
	//Locations[n].models.always.outside = "inside_cabin_2_outside";
	Locations[n].models.always.locators = "inside_cabin_2_locators";
	Locations[n].models.always.bsp = "inside_cabin_2_bsp";
	Locations[n].models.always.camcollider = "inside_cabin_2_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_2_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_2_patch";
	Locations[n].models.day.fonar = "inside_cabin_2_fd";
	Locations[n].models.day.rays = "inside_cabin_2_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_2_patch";
	Locations[n].models.night.fonar = "inside_cabin_2_fn";
	// Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	
	// большая каюта
	n = FindLocation("My_Cabin");
	DeleteAttribute(&Locations[n], "models");
	
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_2"; // большая каюта
	//Always
	Locations[n].models.always.main = "inside_cabin_2";
	Locations[n].models.always.main.level = 65538;
	Locations[n].models.always.parts = "inside_cabin_2_parts";
	//Locations[n].models.always.outside = "inside_cabin_2_outside";
	Locations[n].models.always.locators = "inside_cabin_2_locators";
	Locations[n].models.always.bsp = "inside_cabin_2_bsp";
	Locations[n].models.always.camcollider = "inside_cabin_2_camcollider";
	Locations[n].models.always.camcollider.tech = "LocationWindows";
	locations[n].models.always.camcollider.level = 65539;
	Locations[n].models.always.windows = "inside_cabin_2_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_2_patch";
	Locations[n].models.day.fonar = "inside_cabin_2_fd";
	Locations[n].models.day.rays = "inside_cabin_2_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_2_patch";
	Locations[n].models.night.fonar = "inside_cabin_2_fn";
	
	 // Locators
	Locations[n].locators_radius.box.box1 = 0.5; // основной сундук
	
    Locations[n].locators_radius.interactive.bed = 0.8;
    Locations[n].locators_radius.interactive.bookcase = 0.5;
    Locations[n].locators_radius.interactive.shelf = 0.5;
    Locations[n].locators_radius.interactive.shelf1 = 0.1;
    Locations[n].locators_radius.interactive.shelf2 = 0.1;
    Locations[n].locators_radius.interactive.shelf3 = 0.1;
    Locations[n].locators_radius.interactive.shelf4 = 0.1;
    Locations[n].locators_radius.interactive.shelf5 = 0.1;
    Locations[n].locators_radius.interactive.shelf6 = 0.1;
    Locations[n].locators_radius.interactive.table_capt = 0.5;
    Locations[n].locators_radius.interactive.wardrobe = 0.5;

    Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.rld.loc0 = 0.5;
    Locations[n].locators_radius.rld.loc1 = 0.5;
	Locations[n].locators_radius.rld.loc2 = 0.5;
    Locations[n].locators_radius.rld.aloc0 = 0.5;
    Locations[n].locators_radius.rld.aloc1 = 0.5;
	Locations[n].locators_radius.rld.aloc2 = 0.5;
	
	ref refShip;
	
	// Общий пулл кораблей (иниты)
	int maxShips = GetArraySize(&ShipsTypes);
	for (i = 0; i < maxShips; i++)
	{
		makeref(refShip,ShipsTypes[i]);
		if(!CheckAttribute(refShip,"Class")) continue;
		if(sti(refShip.Class) == 6) refship.CabinType = "Cabin_Small";
		if(sti(refShip.Class) == 5) refship.CabinType = "Cabin_Medium";
		if(sti(refShip.Class) == 4) refship.CabinType = "Cabin_Medium2";
		if(sti(refShip.Class) == 3) refship.CabinType = "Cabin_Medium2";
		if(refship.CabinType == "CabineFDM") continue;
		if(sti(refShip.Class) == 2) refship.CabinType = "Cabin";
		if(sti(refShip.Class) == 1) refship.CabinType = "Cabin";
	}
	
	
	// Сгенерированные корабли
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
		
		if(sti(RealShips[i].Class) == 6) RealShips[i].CabinType = "Cabin_Small";
		if(sti(RealShips[i].Class) == 5) RealShips[i].CabinType = "Cabin_Medium";
		if(sti(RealShips[i].Class) == 4) RealShips[i].CabinType = "Cabin_Medium2";
		if(sti(RealShips[i].Class) == 3) RealShips[i].CabinType = "Cabin_Medium2";
		if(RealShips[i].CabinType == "CabineFDM") continue;
		if(sti(RealShips[i].Class) == 2) RealShips[i].CabinType = "Cabin";
		if(sti(RealShips[i].Class) == 1) RealShips[i].CabinType = "Cabin";
	}
}

void CamCollider()
{
	for(int n = 0; n < MAX_LOCATIONS; n++)
	{
		if(CheckAttribute(&Locations[n], "models.always.camcollider"))
		{
			Locations[n].models.always.camcollider.tech = "LocationWindows";
			locations[n].models.always.camcollider.level = 65539;
		}
	}
}

void Remove_ShipHP_Penalty()
{
	int i;
	
	for(i = 0; i < TOTAL_CHARACTERS; i++)
	{
		DeleteAttribute(&Characters[i], "Ship.HP_penalty");
		if(Characters[i].id == "Pirates_shipyarder")
		{
			if(Characters[i].dialog.currentnode == "ship_repair_HP_again" || Characters[i].dialog.currentnode == "ship_repair_again")
			{
				Characters[i].dialog.currentnode = "node_3";
				CloseQuestHeader("ShipRepair");
			}
			DeleteAttribute(&Characters[i], "Repair");
		}
	}
}

void SchoonerWaterLine()
{
	ref refShip;
	int i, j;
	
	// Общий пулл кораблей (иниты)
	makeref(refShip,ShipsTypes[SHIP_SCHOONER]);
	refship.WaterLine					= -0.3;
	refShip.MaxCrew   = 76;
	refShip.OptCrew   = 61;
	refShip.MinCrew   = 15;
	
	makeref(refShip,ShipsTypes[SHIP_BARKENTINE]);
	refship.WaterLine					= -0.25;
	
	makeref(refShip,ShipsTypes[SHIP_FDM]);
	refShip.Name = "Flyingdutchman";
	
	makeref(refShip,ShipsTypes[SHIP_TARTANE]);
	refShip.SpeedRate = 10.15;
	
	makeref(refShip,ShipsTypes[SHIP_CAREERLUGGER]);
	refShip.SpeedRate = 12.75;
	refShip.MaxCrew   = 48;
	refShip.OptCrew   = 38;
	refShip.MinCrew   = 10;
	
	makeref(refShip,ShipsTypes[SHIP_LUGGER]);
	refShip.SpeedRate = 12.45;
	refShip.MaxCrew   = 55;
	refShip.OptCrew   = 44;
	refShip.MinCrew   = 11;
	
	makeref(refShip,ShipsTypes[SHIP_BARKENTINE]);
	refShip.SpeedRate = 13.65;
	refShip.MaxCrew   = 50;
	refShip.OptCrew   = 40;
	refShip.MinCrew   = 10;
	
	makeref(refShip,ShipsTypes[SHIP_BARQUE]);
	refShip.MaxCrew   = 68;
	refShip.OptCrew   = 54;
	refShip.MinCrew   = 14;
	
	makeref(refShip,ShipsTypes[SHIP_BRIGANTINE]);
	refShip.MaxCrew   = 89;
	refShip.OptCrew   = 71;
	refShip.MinCrew   = 18;
	
	makeref(refShip,ShipsTypes[SHIP_FLEUT]);
	refShip.MaxCrew   = 80;
	refShip.OptCrew   = 64;
	refShip.MinCrew   = 16;
	
	makeref(refShip,ShipsTypes[SHIP_FLEUT]);
	refShip.MaxCrew   = 144;
	refShip.OptCrew   = 115;
	refShip.MinCrew   = 29;
	
	makeref(refShip,ShipsTypes[SHIP_PINK]);
	refShip.SpeedRate = 13.90;
	
	makeref(refShip,ShipsTypes[SHIP_BRIG]);
	refShip.SpeedRate = 18.05;

	makeref(refShip,ShipsTypes[SHIP_CORVETTE]);
	refShip.SpeedRate = 17.80;

	makeref(refShip,ShipsTypes[SHIP_SCHOONER_W]);
	refShip.SpeedRate = 14.45;

	makeref(refShip,ShipsTypes[SHIP_SCHOONER]);
	refShip.SpeedRate = 13.55;
	
	makeref(refShip,ShipsTypes[SHIP_XebekVML]);
	refShip.SpeedRate = 12.15;
	
	makeref(refShip,ShipsTypes[SHIP_CARAVEL]);
	refShip.SpeedRate = 12.45;
	
	makeref(refShip,ShipsTypes[SHIP_MAYFANG]);
	refShip.SpeedRate = 11.65;
	
	makeref(refShip,ShipsTypes[SHIP_MIRAGE]);
	refShip.SpeedRate = 13.65;
	
	makeref(refShip,ShipsTypes[SHIP_HIMERA]);
	refShip.SpeedRate = 15.20;
	
	makeref(refShip,ShipsTypes[SHIP_POLACRE]);
	refShip.SpeedRate = 13.10;
	
	makeref(refShip,ShipsTypes[SHIP_CURSED_FDM]);
	refShip.CannonsQuantity				= 62;	// 6,4,26,26
	refShip.CannonsQuantityMax          = 62;
	refShip.CannonsQuantityMin			= 62;
	refShip.rcannon 					= 26;
	refShip.lcannon 					= 26;
	refship.WaterLine					= -0.4;
	refShip.cannonr  = refShip.rcannon;
	refShip.cannonl  = refShip.lcannon;
	refShip.cannonf  = refShip.fcannon;
	refShip.cannonb  = refShip.bcannon;
	
	// Сгенерированные корабли
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
		
		if(sti(RealShips[i].BaseType) == SHIP_SCHOONER)
		{
			RealShips[i].WaterLine = -0.3;
		}
		if(sti(RealShips[i].BaseType) == SHIP_BARKENTINE)
		{
			RealShips[i].WaterLine = -0.25;
		}
		
		if(sti(RealShips[i].BaseType) == SHIP_FDM)
		{
			RealShips[i].Name = "Flyingdutchman";
		}
		
		if(sti(RealShips[i].BaseType) == SHIP_PINK)
		{
			RealShips[i].SpeedRate = 13.90;
		}
		
		if(sti(RealShips[i].BaseType) == SHIP_MAYFANG)
		{
			RealShips[i].SpeedRate = 11.65;
		}
		
		if(sti(RealShips[i].BaseType) == SHIP_MIRAGE)
		{
			RealShips[i].SpeedRate = 13.65;
		}
		
		if(sti(RealShips[i].BaseType) == SHIP_HIMERA)
		{
			RealShips[i].SpeedRate = 15.20;
		}
		if(sti(RealShips[i].BaseType) == SHIP_CURSED_FDM)
		{
			RealShips[i].CannonsQuantity = 62;
			RealShips[i].CannonsQuantityMax = 62;
			RealShips[i].CannonsQuantityMin = 62;
			RealShips[i].rcannon = 26;
			RealShips[i].lcannon = 26;
			RealShips[i].WaterLine	= -0.4;
			RealShips[i].cannonr  = RealShips[i].rcannon;
			RealShips[i].cannonl  = RealShips[i].lcannon;
			RealShips[i].cannonf  = RealShips[i].fcannon;
			RealShips[i].cannonb  = RealShips[i].bcannon;
		}
		/* if(sti(RealShips[i].BaseType) == SHIP_TARTANE)
		{
			RealShips[i].SpeedRate = 10.15;
		}
		
		if(sti(RealShips[i].BaseType) == SHIP_CAREERLUGGER)
		{
			RealShips[i].SpeedRate = 10.15;
		} */
	}
	/* for(j = 0; j < MAX_CHARACTERS; j++)
	{
		if(!CheckAttribute(&characters[j],"Ship.Cannons.borts")) continue;
		if(!CheckAttribute(&characters[j],"Ship.Type")) continue;
		if(sti(characters[j].Ship.Type) > 899) continue;
		if(RealShips[sti(characters[j].Ship.Type)].BaseType != SHIP_CURSED_FDM) continue;
		
		for (i = 0; i < 26; i++)
		{
			string attr1 = "c" + i;
			characters[j].Ship.Cannons.borts.cannonr.damages.(attr1) = 0.0;
			characters[j].Ship.Cannons.borts.cannonl.damages.(attr1) = 0.0;
		}
		//RecalculateCargoLoad(&characters[j]);
	} */
}

void LeFransua_Letter()
{
	ref itm;
	
	makeref(itm, items[FindItem("Reserve_item_11")]); // ключ Тайны ЛеФрансуа
	
	itm.id = "key_candlestick_LeFransua";
	itm.name = "itmname_key_candlestick_LeFransua";
	itm.describe = "itmdescr_key_candlestick_LeFransua";
	itm.model = "keysimple";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_34";
	itm.Weight = 0.3;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	
	SetItemInLocation("PR_Letter", "LeFransua_town", "letter1");
	locations[FindLocation("LeFransua_town")].locators_radius.item.letter1 = 1.0;
	QuestPointerToLoc("LeFransua_town", "item", "letter1");
	
	SetItemInLocation("PR_Letter", "LeFransua_town", "letter2");
	locations[FindLocation("LeFransua_town")].locators_radius.item.letter2 = 1.2;
	QuestPointerToLoc("LeFransua_town", "item", "letter2");
	
	SetItemInLocation("PR_Letter", "LeFransua_town", "letter3");
	locations[FindLocation("LeFransua_town")].locators_radius.item.letter3 = 1.0;
	QuestPointerToLoc("LeFransua_town", "item", "letter3");
}

void SP_Letter()
{
	int n;
	ref itm;
	
	n = FindLocation("FortFrance_town");
	
	SetItemInLocation("PR_Letter", "FortFrance_town", "letter1");
	locations[n].locators_radius.item.letter1 = 1.2;
	QuestPointerToLoc("FortFrance_town", "item", "letter1");
	
	SetItemInLocation("PR_Letter", "FortFrance_town", "letter2");
	locations[n].locators_radius.item.letter2 = 2.0;
	QuestPointerToLoc("FortFrance_town", "item", "letter2");
	
	SetItemInLocation("PR_Letter", "FortFrance_town", "letter3");
	locations[n].locators_radius.item.letter3 = 1.0;
	QuestPointerToLoc("FortFrance_town", "item", "letter3");
	
	SetItemInLocation("PR_Letter", "FortFrance_town", "letter4");
	locations[n].locators_radius.item.letter4 = 1.2;
	QuestPointerToLoc("FortFrance_town", "item", "letter4");
	
	n = FindLocation("FortFrance_Dungeon");
	
	locations[n].models.always.Maltains_Door = "Malta_door_closed";
	
	//Day
	locations[n].models.day.charactersPatch = "Malta_patch_closed";
	//Night
	locations[n].models.night.charactersPatch = "Malta_patch_closed";
	
	makeref(itm, items[FindItem("key_candlestick_FortFrance")]);
	
	itm.useLocation = "FortFrance_Dungeon";

}

int InitStdBlade160(int	    ItemIndex, 
					string 	ModelID, 
					string 	picTexture,
					int		picIndex,
					string  TargetGroup,
					int     Quality,
					string  BladeType,
					int     BladeNum,
					float   Lenght,
					float   Curve,
					bool    isGenerable,
					int     GenerationQty, 
					bool 	isGenerablePrice,
					int     Price)
{
	ref	blade;
	int	bladeIndex;
	float MaxAttack = 0.0;
	
	bladeIndex = ItemIndex;
	makeref(blade, Items[bladeIndex]);
	
	blade.id				= ModelID;		
	blade.groupID 			= BLADE_ITEM_TYPE;
	blade.model				= ModelID;
	blade.name				= "itmname_" + ModelID;
	blade.describe			= "itmdescr_" + ModelID;		
	blade.folder 			= "ammo";
	blade.picTexture		= picTexture;
	blade.picIndex			= picIndex;
	blade.param.time 		= 0.1;
	blade.param.colorstart 	= argb(64, 64, 64, 64);
	blade.param.colorend 	= argb(0, 32, 32, 32);
	blade.ItemType 			= "WEAPON";
	blade.lenght 			= Lenght;
	blade.curve				= Curve;
 	blade.FencingType       = BladeType;
	blade.quality			= Quality;
	blade.target			= TargetGroup;
	blade.TradeType 		= ITEM_TRADE_AMMUNITION;
		
	if(isGenerable)				blade.Generation.qty 	= GenerationQty;
	if(isGenerablePrice)    	
	{
		blade.Generation.price 	= true; // Флаг "генерить цену"	
	}
	else blade.price 	= Price;	
	
	switch (BladeType) 
	{
		case "FencingL" :
			blade.Weight 	= 2.0 + fRandSmall(1.0); 
			MaxAttack		= FencingL_MaxAttack;
		break;
		case "FencingS" :
			blade.Weight 	= 2.4 + fRandSmall(1.2);
			MaxAttack		= FencingS_MaxAttack;			
		break;
		case "FencingH" :
			blade.Weight 	= 3.0 + fRandSmall(1.5); 
			MaxAttack		= FencingH_MaxAttack;
		break;
	}
	
	if(ModelID == "blade_WR")    blade.Weight = 3.6;
	
	blade.Balance = fRandSmall(2.0);
	switch (Quality)
	{
		case B_POOR :
			blade.Attack 	= MaxAttack * (42.5 + fRandSmall(15.0))/100.0;			
			blade.rare 	 	= 0.1;
			blade.minlevel 	= 1;
		break;
		case B_ORDINARY :
			blade.Attack 	= MaxAttack * (55.0 + fRandSmall(15.0))/100.0;
			blade.rare 	 	= 0.01;
			blade.minlevel 	= 1;
		break;
		case B_GOOD :
			blade.Attack 	= MaxAttack * (70.0 + fRandSmall(15.0))/100.0;
			blade.rare 	 	= 0.001;
			blade.minlevel 	= 10;
			if(TargetGroup == TGT_QUEST) // для квестового оружия атаку считаем по максимуму
			{
				blade.Attack 	= MaxAttack * 0.85;	
			}
			if(BladeType == "FencingL") blade.Balance = 0.0 + fRandSmall(1.0);
			if(BladeType == "FencingS") blade.Balance = 2.0 - fRandSmall(1.0);
			if(BladeType == "FencingH") blade.Balance = 2.0 - fRandSmall(1.0);
		break;
		case B_EXCELLENT :
			blade.Attack 	= MaxAttack * (85.0 + fRandSmall(15.0))/100.0;
			blade.rare 	 	= 0.0001;
			blade.minlevel 	= 15;
			if(TargetGroup == TGT_QUEST) // для квестового оружия атаку считаем по максимуму
			{
				blade.Attack 	= MaxAttack;	
			}
			if(BladeType == "FencingL") blade.Balance = 0.0 + fRandSmall(0.5);
			if(BladeType == "FencingS") blade.Balance = 2.0 - fRandSmall(0.5);
			if(BladeType == "FencingH") blade.Balance = 2.0 - fRandSmall(0.5);
		break;
	}
	
	switch (BladeType) 
	{
		case "FencingL" :
			blade.WeightAttack = stf(blade.Attack) * (0.5 + 0.2 * stf(blade.Weight));
			if(isGenerablePrice) 
			{
				blade.price  = makeint(35.0 * (1.0/Curve + Lenght) * (stf(blade.Attack) * 2.0 - 30.0));
			}	
			else blade.price = Price;			
		break;
		case "FencingS" :
			blade.WeightAttack = stf(blade.Attack) * (0.25 + 0.25 * stf(blade.Weight));
			if(isGenerablePrice) 
			{
				blade.price  = makeint(25.0 * (Curve + Lenght) * (stf(blade.Attack) * 2.0 - 40.0));
			}	
			else blade.price = Price;			
		break;
		case "FencingH" :
			blade.WeightAttack = stf(blade.Attack) * (0.25 + 0.2 * stf(blade.Weight));
			if(isGenerablePrice) 
			{
				blade.price  = makeint(20.0 * ((Curve + 1.0) * 1.0/Lenght) * (stf(blade.Attack) * 2.0 - 50.0));
			}	
			else blade.price = Price;			
		break;
	}
	//trace("blade.id : " + blade.id + " blade.price : " + blade.price + " blade.Attack : " + blade.Attack + " blade.Balance : " + blade.Balance + " blade.Weight : " + blade.Weight);
	
	return bladeIndex;
}

int InitStdTalisman160(	int		ItemIndex, 
						string 	id, 
						string 	ModelID, 
						string 	picTexture,
						int		picIndex, 
						int		Price, 
						float 	Weight,
						string	kind 	)
{
	ref	talisman;
	int	talismanIndex;
	
	talismanIndex = ItemIndex;
	makeref(talisman, Items[talismanIndex]);
	
	talisman.id				= id;		
	talisman.groupID		= TALISMAN_ITEM_TYPE;
	talisman.name			= "itmname_" + id;
	talisman.describe		= "itmdescr_" + id;		
	talisman.model			= ModelID;
	talisman.picTexture		= picTexture;
	talisman.picIndex		= picIndex;
	talisman.price			= Price + 10000;	
	talisman.rare 			= 0.0001;
	talisman.minlevel 		= 1;
	talisman.Weight 		= Weight;
	talisman.unique			= true;	
	talisman.ItemType 		= "ARTEFACT";
	if(kind != "") talisman.kind = kind;
	talisman.TradeType 		= ITEM_TRADE_JEWELRY;
	
	if(talisman.id == "talisman20") 
	{
		talisman.multiobject		= true;
		talisman.multiobject.qty 	= 1;
		talisman.multiobject.alchemy = false;
	}
	
	return talismanIndex;
}