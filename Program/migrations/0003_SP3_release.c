
void ApplyMigration(ref migrationState) {
	
	MementoReinit();
	AddMementoCabine();
	AddMementoItems();
	MementoDeckReinit();
	DiegoDeLanda();
}

void MementoReinit()
{
	ref refShip;
	
	makeref(refShip,ShipsTypes[SHIP_MEMENTO]);
	refShip.Name            			= "Memento";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS18;
	refShip.MaxCaliber      			= 18;	
	refShip.Weight						= Tonnes2CWT(430);	
	refShip.Capacity        			= 4250;
	refShip.CannonsQuantity				= 22; // 9,9,2,2
	refShip.CannonsQuantityMin			= 22;
	refShip.rcannon 					= 9;
	refShip.lcannon 					= 9;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;		
	refShip.MaxCrew         			= 175;
	refShip.OptCrew         			= 140;
	refShip.MinCrew         			= 35;	
	refShip.SpeedRate       			= 17.25;
	refShip.TurnRate        			= 50.5;
	refShip.Price           			= 52000;
	refShip.HP              			= 3420;
	refShip.SP              			= 100;

	refship.Type.War					= true;
	refship.Spec                        = SHIP_SPEC_WAR;
	refship.QuestShip                   = true;
	refship.QuestSP						= true;
	
	refShip.lowpolycrew 				= 12;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.04;
	
	refship.WaterLine					= 0.3;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 0.65;
	
	refship.CabinType          			= "Cabin_memento";
	refship.DeckType           			= "memento";

	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 13.2;		refShip.Height.Knippels.DY	= 11.6;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_a33		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 1.0;
	refShip.GeraldSails.rey_b2.hscale		= 1.0;
	refShip.GeraldSails.rey_b3.vscale		= 1.0;
	refShip.GeraldSails.rey_b3.hscale		= 1.0;
	refShip.GeraldSails.rey_a33.vscale		= 1.0;
	refShip.GeraldSails.rey_a33.hscale		= 1.0;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	DeleteAttribute(refship, "Type.Merchant");
	
	makeref(refShip,ShipsTypes[SHIP_ELCASADOR]);
	refship.WaterLine					= 0.0;
}

void AddMementoCabine()
{
	int n;
	
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
	Locations[n].id = "Cabin_Memento";
	Locations[n].id.label = "cabine";
	//Locations[n].filespath.models = "locations\decks\capmd";
    Locations[n].image = "loading\Capdeck_" + rand(4) + ".tga";
	//Sound
	locations[n].type = "boarding_cabine";
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_4"; // каюта брига/"Мементо"
	//Always
	Locations[n].models.always.main = "inside_cabin_4";
	Locations[n].models.always.parts = "inside_cabin_4_parts";
	Locations[n].models.always.partsQ = "inside_cabin_4_partsMemento"; // декор "Мементо"
	Locations[n].models.always.locators = "inside_cabin_4_locators";
	//Locations[n].models.always.locators = "inside_cabin_4_locators_private"; // приватные сундуки
	Locations[n].models.always.camcollider = "inside_cabin_4_camcollider";
	Locations[n].models.always.windows = "inside_cabin_4_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_4_patch";
	Locations[n].models.day.fonar = "inside_cabin_4_fd";
	Locations[n].models.day.rays = "inside_cabin_4_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_4_patch";
	Locations[n].models.night.fonar = "inside_cabin_4_fn";

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

	Locations[n].boarding = "true";
	Locations[n].boarding.nextdeck = "";
	//Locations[n].camshuttle = 1;
	Locations[n].boarding.locatorNum = 1;
	Locations[n].CabinType = true;
	locations[n].environment.weather.rain = false;
	Locations[n].boarding.Loc.Hero = "loc2";
    Locations[n].boarding.Loc.Capt = "loc0";
	
	ExpandLocationsArray();
	
	n = MAX_LOCATIONS - 1;
	
	Locations[n].id = "My_Cabin_Memento";
	Locations[n].id.label = "cabine";
	//Locations[n].filespath.models = "locations\decks\capmd";
    Locations[n].image = "loading\Capdeck_" + rand(4) + ".tga";
	//Sound
	locations[n].type = "residence";
	//Models
	Locations[n].filespath.models = "locations\decks\inside_cabin_4"; // каюта брига/"Мементо"
	//Always
	Locations[n].models.always.main = "inside_cabin_4";
	Locations[n].models.always.parts = "inside_cabin_4_parts";
	Locations[n].models.always.partsQ = "inside_cabin_4_partsMemento"; // декор "Мементо"
	Locations[n].models.always.locators = "inside_cabin_4_locators";
	//Locations[n].models.always.locators = "inside_cabin_4_locators_private"; // приватные сундуки
	Locations[n].models.always.camcollider = "inside_cabin_4_camcollider";
	Locations[n].models.always.windows = "inside_cabin_4_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	//Day
	Locations[n].models.day.charactersPatch = "inside_cabin_4_patch";
	Locations[n].models.day.fonar = "inside_cabin_4_fd";
	Locations[n].models.day.rays = "inside_cabin_4_rays"; // лучи только днем
	Locations[n].models.day.rays.uvslide.v0 = 0.08;
	Locations[n].models.day.rays.uvslide.v1 = 0.0;
	Locations[n].models.day.rays.tech = "LocationWaterFall";
	Locations[n].models.day.rays.level = 99950;
	//Night
	Locations[n].models.night.charactersPatch = "inside_cabin_4_patch";
	Locations[n].models.night.fonar = "inside_cabin_4_fn";

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

    LAi_LocationFightDisable(&Locations[n], true);

    Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "My_Deck";
	Locations[n].reload.l1.emerge = "reload1";
	Locations[n].reload.l1.label = "Deck.";

	Locations[n].items.randitem2 = "";
	Locations[n].items.randitem1 = "";

	Locations[n].boarding = "true";
	//Locations[n].camshuttle = 1;
	locations[n].environment.weather.rain = false;
	
}

void AddMementoItems()
{
	ExpandItemsArray();
	InitStdBladeSP3(TOTAL_ITEMS - 1, "blade_SP_3low", 	"ITEMS_41",     5,  TGT_QUEST,   B_EXCELLENT, "FencingS", 9, 1.05, 1.10, 0, 0, 0,100000); // Катлас висельник без черепа
	ExpandItemsArray();
	InitStdBladeSP3(TOTAL_ITEMS - 1, "blade_SP_3", 	"ITEMS_41",     6,  TGT_QUEST,   B_EXCELLENT, "FencingS", 9, 1.05, 1.10, 0, 0, 0,100000); // Катлас висельник с черепом
	
	ref rItem = ItemsFromID("talisman19");
	rItem.Weight = 2.2;
	rItem.picIndex = 7;
	rItem.picTexture = "ITEMS_41";
	
	rItem = ItemsFromID("BoxOfBalls");
	rItem.picIndex = 3;
	rItem.picTexture = "ITEMS_41";
	
	// катлас Висельник с черепом
	InitMultiObjectSP3(  		 "blade_SP_3",	"t1",     "talisman19",   "Component", 	  1); // череп
	InitMultiObjectSP3(  		 "blade_SP_3",	"t2",      "blade_SP_3low",    "Component", 	  1); // стоковый катлас
	
	// катлас Висельник без черепа
	InitMultiObjectSP3(  		 "blade_SP_3low",	"t1",      "blade_SP_3",    "Component", 	  1); // катлас с черепом
	InitMultiObjectSP3(  		 "blade_SP_3low",	"t2",      "talisman19",   "Additional",  0); // череп
	
	ref itm;
	
	ExpandItemsArray();
	
	makeref(itm,Items[TOTAL_ITEMS - 1]);
	itm.id = "spyglassSP3"; // подзорная труба SP3
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglassSP3";
	itm.describe = "itmdescr_spyglassSP3";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_41";
	itm.price = 75000;
	// boal 19.01.2004 -->
	itm.Weight = 2;
    // boal 19.01.2004 <--
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.radius = 850.0;
	itm.scope.texture = "eye_GoodTub.tga";
	itm.scope.zoom = 7.0;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 1;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 1;
	itm.scope.show.sail = 1;
	itm.scope.show.crew = 0;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 0;
	itm.scope.show.cannontype = 1;
	itm.scope.show.captain_skills = 0;
	itm.scope.show.mushketshot = 1;
	itm.scope.show.CheckSurrender = 1;
	itm.minlevel = 1;
	itm.rare = 0.0001;
	itm.ItemType = "SUPPORT";
	itm.TradeType = ITEM_TRADE_AMMUNITION;
	
	ExpandItemsArray();
	
	makeref(itm,Items[TOTAL_ITEMS - 1]); // Шляпа Грима
	itm.id = "hat9";
	itm.groupID	= HAT_ITEM_TYPE;
	itm.name = "itmname_hat9";
	itm.describe = "itmdescr_hat9";
	itm.model = "hat9";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_40";
	itm.price = 450000;
	itm.Weight = 0.1;
	itm.ItemType = "SUPPORT";
	itm.TradeType = ITEM_TRADE_AMMUNITION;
	
	ExpandItemsArray();
	
	makeref(itm,Items[TOTAL_ITEMS - 1]); //щётка
	itm.id = "Brush_Props";
	itm.name = "itmname_Brush_Props";
	itm.describe = "itmdescr_Brush_Props";
	itm.model = "Brush_Props";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_33";
	itm.price = 0;
	itm.Weight = 0.2;
	itm.ItemType = "QUESTITEMS";
}

void InitMultiObjectSP3(string id,			
						string sAttr,       
						string component_id,
						string component_use,
						int    component_qty)
{
	ref rItem = ItemsFromID(id);
	rItem.component.(sAttr).id 	=  component_id;
	rItem.component.(sAttr).use =  component_use;
	rItem.component.(sAttr).qty =  component_qty;
}

int InitStdBladeSP3(int	    ItemIndex, 
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
	
	if(ModelID == "blade_SP_3low") blade.Weight = 1.6;
	if(ModelID == "blade_SP_3") blade.Weight = 3.8;
	
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
	if(ModelID == "blade_SP_3low") blade.Balance = 1.2;
	if(ModelID == "blade_SP_3") blade.Balance = 1.2;
	
	if(ModelID == "blade_SP_3low") blade.Attack = 77.0;
	if(ModelID == "blade_SP_3") blade.Attack = 77.0;
	
	SetBladeWeightAttack(blade);
	
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
	
	if(blade.id == "blade_SP_3low")
	{
		blade.multiobject = true;		
		blade.multiobject.qty = 1;
		blade.multiobject.alchemy = false;
	}
	if(blade.id == "blade_SP_3")
	{
		blade.multiobject = true;		
		blade.multiobject.qty = 1;
		blade.multiobject.alchemy = false;
	}
	//trace("blade.id : " + blade.id + " blade.price : " + blade.price + " blade.Attack : " + blade.Attack + " blade.Balance : " + blade.Balance + " blade.Weight : " + blade.Weight);
	
	return bladeIndex;
}

void MementoDeckReinit()
{
	int n;
	
	n = FindLocation("Ship_deck_Memento");
	
	DeleteAttribute(&Locations[n], "models");
	
	//Models	
	Locations[n].filespath.models = "locations\decks\outside_deck_4_Memento"; // бриг "Мементо"
	//Always
	Locations[n].models.always.main = "outside_deck_4_Memento";
	Locations[n].models.always.parts = "outside_deck_4_Memento_parts";
	Locations[n].models.always.ropes = "outside_deck_4_Memento_ropes";
	Locations[n].models.always.locators = "outside_deck_4_Memento_locators";
	Locations[n].models.always.windows = "outside_deck_4_Memento_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	Locations[n].models.always.watermask = "outside_deck_4_Memento_watermask";
	Locations[n].models.always.watermask.tech = "WaterMask";
	Locations[n].models.always.watermask.level = 65500;
	//Day
	locations[n].models.day.charactersPatch = "outside_deck_4_Memento_patch";
	Locations[n].models.day.deckMediumFonarsDay = "outside_deck_4_Memento_fd";  
	//Locations[n].models.day.jumpPatch = "outside_deck_4_Memento_jump";
	//Night
	locations[n].models.night.charactersPatch = "outside_deck_4_Memento_patch";
	Locations[n].models.night.deckMediumFonarsNight = "outside_deck_4_Memento_fn";  
	//Locations[n].models.night.jumpPatch = "outside_deck_4_Memento_jump";
	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	
	n = FindLocation("Deck_Near_Ship_Memento");
	
	DeleteAttribute(&Locations[n], "models");
	
	//Models	
	Locations[n].filespath.models = "locations\decks\outside_deck_4_Memento"; // бриг "Мементо"
	//Always
	Locations[n].models.always.main = "outside_deck_4_Memento";
	Locations[n].models.always.parts = "outside_deck_4_Memento_parts";
	Locations[n].models.always.ropes = "outside_deck_4_Memento_ropes";
	Locations[n].models.always.locators = "outside_deck_4_Memento_locators";
	Locations[n].models.always.windows = "outside_deck_4_Memento_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;
	Locations[n].models.always.watermask = "outside_deck_4_Memento_watermask";
	Locations[n].models.always.watermask.tech = "WaterMask";
	Locations[n].models.always.watermask.level = 65500;
	//Day
	locations[n].models.day.charactersPatch = "outside_deck_4_Memento_patch";
	Locations[n].models.day.deckMediumFonarsDay = "outside_deck_4_Memento_fd";  
	//Locations[n].models.day.jumpPatch = "outside_deck_4_Memento_jump";
	//Night
	locations[n].models.night.charactersPatch = "outside_deck_4_Memento_patch";
	Locations[n].models.night.deckMediumFonarsNight = "outside_deck_4_Memento_fn";  
	//Locations[n].models.night.jumpPatch = "outside_deck_4_Memento_jump";
}

void DiegoDeLanda()
{
	// Диего де Ланда
	sld = GetCharacter(NPC_GenerateCharacter("DiegoDeLanda", "priest_sp1", "man", "man2", 100, SPAIN, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_279");
	sld.lastname = StringFromKey("QuestsUtilite_280");
	sld.dialog.filename = "Quest\ShipsPack\DiegoDeLanda_dialog.c";
	sld.dialog.currentnode = "DiegoDeLanda_Meeting";
	LAi_SetHP(sld, 999.0, 999.0);
	LAi_SetImmortal(sld, true);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}