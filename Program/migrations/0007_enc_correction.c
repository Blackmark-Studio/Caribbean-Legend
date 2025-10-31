
void ApplyMigration(ref migrationState)
{
	LoyaltyPack();
}

void LoyaltyPack()
{
	DeleteAttribute(&TreasureTiers[11], "Equip.pistol10");
	DeleteAttribute(&TreasureTiers[12], "Equip.pistol10");
	DeleteAttribute(&TreasureTiers[13], "Equip.pistol10");
	DeleteAttribute(&TreasureTiers[14], "Equip.pistol10");
	
	TreasureTiers[0].QuestSlot.LoyaltyPack = "LoyaltyPack_Treasure";
	
	Add_LP_Items();
	
	if(startHeroType == 1)
	{
		pchar.HeroModel 			= "Sharle_1,Sharle_2,Sharle_3,Sharle_4,Sharle_5,protocusto,Sharle_6,Sharle_8,Sharle_7,Sharle_9,Sharle_1,Sharle_11,Sharle_12,Sharle_13,Sharle_14,Sharle_15";
	}
	else if(startHeroType == 2)
	{
		pchar.HeroModel 			= "Diego_1,Diego_2,Diego_3,Diego_4,Diego_5,protocusto,Diego_6,Diego_8,Diego_1,Diego_9,Diego_1,Diego_11,Diego_12,Diego_13,Diego_14,Diego_15";
	}
	else if(startHeroType == 3)
	{
		pchar.HeroModel 			= "Willy_1,Willy_2,Willy_3,Willy_4,Willy_5,protocusto,Willy_6,Willy_8,Willy_1,Willy_9,Willy_1,Willy_11,Willy_12,Willy_13,Willy_14,Willy_15";
	}
}

void Add_LP_Items()
{
	int n;
	ref itm;
	
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	InitStdMusketLP(n, "mushket10",       "mushket10",  "ITEMS_41",  9, 0.0001,  1,   52000,   140.0,   270.0, 14.8,  1,     B_UNIQUE); // Имперский мушкет
	Items[n].Attack = 55.0;
	
	InitGunExtLP(	   "mushket10", "t1", 	     "cartridge",               "", 140.0, 270.0, 140.0, 270.0,  0.0,  0.0, 1, 1, 0, 0, 0, 0, 95, 14, 0);	
	InitGunExtLP(	   "mushket10", "t2", 		    "bullet",      "gunpowder", 140.0, 270.0, 140.0, 270.0,  0.0,  0.0, 1, 1, 0, 0, 0, 0, 90, 28, 1);
	
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	InitStdSuitLP(n, "cirass11",  	"15","ITEMS_41",  13,  45000, 23,   0.01, 20, false, 0.22, 0.22, 0.5 ); // Зерцальный нагрудник
	
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	makeref(itm,Items[n]); // Солдатская шляпа
	itm.id = "hat10";
	itm.groupID	= HAT_ITEM_TYPE;
	itm.name = "itmname_hat10";
	itm.describe = "itmdescr_hat10";
	itm.model = "hat10";
	itm.picIndex = 10;
	itm.picTexture = "ITEMS_40";
	itm.price = 7500;
	itm.Weight = 1.4;
	itm.ItemType = "SUPPORT";
	itm.TradeType = ITEM_TRADE_AMMUNITION;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.multiobject.alchemy = false;
	
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	makeref(itm,Items[n]);
	itm.id = "vodka";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_vodka";
	itm.describe = "itmdescr_vodka";
    itm.model = "balsam";
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_41";
	itm.price = 3500;
	itm.Weight = 0.7;
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.multiobject.alchemy = false;
	itm.ItemType = "SUPPORT";
	
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	InitStdTalismanLP(n, "talisman20", "", "ITEMS_41", 10,       4200, 1.2,             ""); // Берендейка стрельца
	
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	
	makeref(itm,Items[n]); // пороховница (Сломанная Берендейка)
	itm.id = "talisman20_part";
	itm.name = "itmname_talisman20_part";
	itm.describe = "itmdescr_talisman20_part";
	itm.model = "";
	itm.picIndex = 9;
	itm.picTexture = "ITEMS_18";
	itm.price = 1;
	itm.Weight = 1.0;
	itm.ItemType = "SUPPORT";
	itm.TradeType = ITEM_TRADE_NORMAL;
	
	ExpandItemsArray();
	n = TOTAL_ITEMS - 1;
	makeref(itm,Items[n]); // клепаный ремень (Сломанная Шляпа Стрельца)
	itm.id = "hat10_part";
	itm.name = "itmname_hat10_part";
	itm.describe = "itmdescr_hat10_part";
	itm.model = "";
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_41";
	itm.price = 1;
	itm.Weight = 1.0;
	itm.ItemType = "SUPPORT";
	itm.TradeType = ITEM_TRADE_NORMAL;
	
	// Царская Водка
	InitMultiObjectLP(		"vodka",	    "t1",     "potionrum", 	  "Component", 	  1); // ром
	InitMultiObjectLP(		"vodka",	    "t2",     "potionwine",   "Component", 	  1); // вино
	InitMultiObjectLP(		"vodka",	    "t3",     "potion4", 	  "Component", 	  1); // микстура
	InitMultiObjectLP(		"vodka",	    "t4",     "mineral17", 	  "Component", 	  1); // флакончик
	InitMultiObjectLP(		"vodka",	    "t5",     "jewelry8", 	  "Component", 	  3); // янтарь
	InitMultiObjectLP(  		"vodka",	    "t6",  	  "jewelry1",    "Component", 	  3); // аметист
	InitMultiObjectLP(  		"vodka",        "t7",     "cannabis7", 	  "Component", 	  1); // Мангароса
	InitMultiObjectLP(  		"vodka",        "t8",     "mineral10",  "AlchemyTool", 	  1); // огниво
	InitMultiObjectLP(  		"vodka",        "t9",     "mineral1",   "AlchemyTool", 	  1); // Медный кувшин
	
	// Берендейка стрельца LP
	InitMultiObjectLP(  		 "talisman20",	"t1",     "Mineral24",    "Component", 	   3); // Ремень
	InitMultiObjectLP(  		 "talisman20",	"t2",     "Mineral22",    "Component", 	   3); //  Шпагат
	InitMultiObjectLP(  		 "talisman20",	"t3",     "jewelry13",    "Component", 	   2); // железный слиток
	InitMultiObjectLP(  		 "talisman20",	"t4",     "cartridge",    "Component", 	  20); // бумажный патрон
	InitMultiObjectLP(  		 "talisman20",	"t5",     "mineral10",   "AlchemyTool",    1); // огниво
	InitMultiObjectLP(  		 "talisman20",	"t6",     "mineral15",   "AlchemyTool",    1); // складной нож
	InitMultiObjectLP(  		 "talisman20",	"t7",    "tailor_tool",  "AlchemyTool",    1); // портняжный набор
	InitMultiObjectLP(  		 "talisman20",	"t8",  "talisman20_part",  "Component",    1); // пороховница (Сломанная Берендейка)
	
	// Солдатская шляпа LP
	InitMultiObjectLP(  		 "hat10",	"t1",     "jewelry13",    "Component", 	   10); // железный слиток
	InitMultiObjectLP(  		 "hat10",	"t2",     "jewelry12",    "Component", 	    4); // медный слиток
	InitMultiObjectLP(  		 "hat10",	"t3",     "mineral23",    "Component",      6); // гвоздь
	InitMultiObjectLP(  		 "hat10",	"t4",     "Mineral22",    "Component", 	    6); //  Шпагат
	InitMultiObjectLP(  		 "hat10",	"t5",     "Mineral24",    "Component", 	    1); // Ремень
	InitMultiObjectLP(  		 "hat10",	"t6",     "mineral15",   "AlchemyTool",     1); // складной нож
	InitMultiObjectLP(  		 "hat10",	"t7",    "tailor_tool",  "AlchemyTool",     1); // портняжный набор
	InitMultiObjectLP(  		 "hat10",	"t8",    "hat10_part",    "Component",      1); // клепаный ремень (Сломанная Шляпа Стрельца)
}

int InitStdMusketLP(	int		ItemIndex, 
				string 	id, 
				string 	ModelID, 
				string 	picTexture,
				int		picIndex, 
				float	Rare, 
				int 	MinLevel, 
				int		Price, 
				float 	DmgMin, 
				float 	DmgMax, 
				float 	Weight,
				int 	Charges, 
				int 	Quality )
{
	ref	Mus;
	int	MusIndex;
	
	MusIndex = ItemIndex;
	makeref(Mus, Items[MusIndex]);
	
	Mus.id				= id;		
	Mus.groupID			= MUSKET_ITEM_TYPE;
	Mus.name			= "itmname_" + id;
	Mus.describe		= "itmdescr_" + id;		
	Mus.model			= ModelID;
	Mus.folder 			= "ammo";
	Mus.chargeQ			= Charges;
	Mus.picTexture		= picTexture;
	Mus.picIndex		= picIndex;
	Mus.dmg_min			= DmgMin;
	Mus.dmg_max			= DmgMax;
	Mus.price			= Price;	
	Mus.ItemType 		= "WEAPON";
	Mus.rare 			= Rare;
	Mus.quality 		= Quality;
	Mus.minlevel 		= MinLevel;
	Mus.Weight 			= Weight;
	Mus.ChargeSpeed 	= 10.0; // by default
	Mus.accuracy 		= 50.0; // by default
	Mus.TradeType 		= ITEM_TRADE_AMMUNITION;
	
	return MusIndex;
}

void InitGunExtLP(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin_NC,   
				float  DmgMax_NC,   
				float  DmgMin_C,    
				float  DmgMax_C,    
				float  EnergyP_NC,  
				float  EnergyP_C,   
				bool   Stun_NC,     
				bool   Stun_C,      
				bool   MultiDamage, 
				int    MisFire,     
				bool   SelfDamage,  
				bool   Explosion,   
				float  Accuracy,    
				int    ChargeSpeed, 
				bool   isDefault )
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).bullet 		= sBullet;
	gun.type.(sAttr).gunpowder 		= sGunPowder;
	gun.type.(sAttr).DmgMin_NC		= DmgMin_NC;
	gun.type.(sAttr).DmgMax_NC		= DmgMax_NC;
	gun.type.(sAttr).DmgMin_C		= DmgMin_C;
	gun.type.(sAttr).DmgMax_C		= DmgMax_NC;
	gun.type.(sAttr).EnergyP_NC		= EnergyP_NC;
	gun.type.(sAttr).EnergyP_C		= EnergyP_C;
	gun.type.(sAttr).Stun_NC		= Stun_NC;
	gun.type.(sAttr).Stun_C			= Stun_C;
	gun.type.(sAttr).multidmg       = MultiDamage;
	gun.type.(sAttr).misfire        = MisFire;
	gun.type.(sAttr).SelfDamage     = SelfDamage;
	gun.type.(sAttr).Explosion      = Explosion;
	gun.type.(sAttr).Accuracy       = Accuracy;
	gun.type.(sAttr).ChargeSpeed    = ChargeSpeed;
	gun.type.(sAttr).Default        = isDefault;
}

int InitStdSuitLP(	int		ItemIndex, 
					string 	id, 
					string 	ModelID, 
					string 	picTexture,
					int		picIndex, 
					int		Price, 
					float 	Weight,
					float	Rare, 
					int 	MinLevel,
					bool    isClothes,
					float	CirassLevel_blade,
					float   CirassLevel_gun, 
					float   Critical)
{
	ref	suit;
	int	suitIndex;
	
	suitIndex = ItemIndex;
	makeref(suit, Items[suitIndex]);
	
	suit.id					= id;		
	suit.groupID			= CIRASS_ITEM_TYPE;
	suit.name				= "itmname_" + id;
	suit.describe			= "itmdescr_" + id;		
	suit.folder 			= "items";
	suit.model				= ModelID;
	suit.picTexture			= picTexture;
	suit.picIndex			= picIndex;
	suit.price				= Price;	
	suit.rare 				= Rare;
	suit.minlevel 			= MinLevel;
	suit.Weight 			= Weight;
	suit.Clothes 			= isClothes;
	suit.B_CirassLevel 		= CirassLevel_blade;
	suit.G_CirassLevel 		= CirassLevel_gun;
	
	suit.critical			= Critical;
	
	suit.ItemType 			= "SUPPORT";
	suit.TradeType 			= ITEM_TRADE_AMMUNITION;
	
	return suitIndex;
}

int InitStdTalismanLP(	int		ItemIndex, 
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

void InitMultiObjectLP(	string id,			
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