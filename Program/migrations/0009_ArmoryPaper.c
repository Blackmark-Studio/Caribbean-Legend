
void ApplyMigration(ref migrationState) {
	
	GunsRebalance();
	ArmoryPaperInit();
	CraftRebalance();
	ReinitGunsDamage();
}

void GunsRebalance()
{
	int i;
	ref gun;
	
	string sAttr, sGun;
	
	for(i = 0; i < TOTAL_CHARACTERS; i++)
	{
		sAttr = GUN_ITEM_TYPE;
		sGun = GetCharacterEquipByGroup(&Characters[i], GUN_ITEM_TYPE);
		
		if(sGun != "")
		{
			if(CheckAttribute(&Characters[i], "chr_ai." + sAttr + ".DmgMin_NC"))
			{
				Characters[i].chr_ai.(sAttr).DmgMin	= Characters[i].chr_ai.(sAttr).DmgMin_NC;
			}
			if(CheckAttribute(&Characters[i], "chr_ai." + sAttr + ".DmgMax_NC"))
			{
				Characters[i].chr_ai.(sAttr).DmgMax	= Characters[i].chr_ai.(sAttr).DmgMax_NC;
			}
			if(CheckAttribute(&Characters[i], "chr_ai." + sAttr + ".DmgMax_NC"))
			{
				Characters[i].chr_ai.(sAttr).DmgMax	= Characters[i].chr_ai.(sAttr).DmgMax_NC;
			}
		}
		
		sAttr = MUSKET_ITEM_TYPE;
		sGun = GetCharacterEquipByGroup(&Characters[i], MUSKET_ITEM_TYPE);
		
		if(sGun != "")
		{
			if(CheckAttribute(&Characters[i], "chr_ai." + sAttr + ".DmgMin_NC"))
			{
				Characters[i].chr_ai.(sAttr).DmgMin	= Characters[i].chr_ai.(sAttr).DmgMin_NC;
			}
			if(CheckAttribute(&Characters[i], "chr_ai." + sAttr + ".DmgMax_NC"))
			{
				Characters[i].chr_ai.(sAttr).DmgMax	= Characters[i].chr_ai.(sAttr).DmgMax_NC;
			}
			if(CheckAttribute(&Characters[i], "chr_ai." + sAttr + ".DmgMax_NC"))
			{
				Characters[i].chr_ai.(sAttr).DmgMax	= Characters[i].chr_ai.(sAttr).DmgMax_NC;
			}
		}
	}
}

void ArmoryPaperInit()
{
	int i;
	ref itm;
	object tempItems[TOTAL_ITEMS];
	
	for(i = 0; i < TOTAL_ITEMS; i++)
	{
		CopyAttributes(&tempItems[i], &Items[i]);
		//trace("Index " + i + " ID temp " + tempItems[i].id + " ID real " + Items[i].id);
	}
	
	ExpandItemsArray();
	
	ITEMS_QUANTITY++;
	
	DeleteAttribute(&Items[ITEMS_QUANTITY - 1], "");
	InitAddItem(ITEMS_QUANTITY - 1);
	
	makeref(itm,Items[ITEMS_QUANTITY - 1]); // Оружейная бумага
	itm.id = "ArmoryPaper";
	itm.name = "itmname_ArmoryPaper";
	itm.describe = "itmdescr_ArmoryPaper";
	itm.model = "pursel";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_41";
	itm.Weight = 0.1;
	itm.price = 140;
	itm.minlevel = 0;
	itm.rare = 0.3;
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";
	itm.TradeType = ITEM_TRADE_NORMAL;
	
	for(i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		DeleteAttribute(&Items[i], "");
		CopyAttributes(&Items[i], &tempItems[i - 1]);
		Items[i].index = i;
	}
	
	// belamour просто финальное логирование (пока оставить)
	/* for(i = 0; i < TOTAL_ITEMS; i++)
	{
		trace("New object full loop" + i + " ID real " + Items[i].id);
	} */
}

void CraftRebalance()
{
	ref rItem;
	
	rItem = ItemsFromID("cartridge");
	rItem.component.t3.id 	=  "ArmoryPaper";
	rItem.component.t3.use =  "Component";
	rItem.component.t3.qty =  1;
	rItem.component.t4.id 	=  "mineral15";
	rItem.component.t4.use =  "AlchemyTool";
	rItem.component.t4.qty =  1;
	rItem.price = 240;
	rItem.Weight = 0.3;
	
	rItem = ItemsFromID("bullet_double");
	rItem.component.t3.id 	=  "gold_dublon";
	rItem.component.t3.use =  "Component";
	rItem.component.t3.qty =  7;
	rItem.component.t4.id =  "ArmoryPaper";
	rItem.component.t4.use =  "Component";
	rItem.component.t4.qty =  1;
	rItem.component.t5.id 	=  "mineral15";
	rItem.component.t5.use =  "AlchemyTool";
	rItem.component.t5.qty =  1;
	rItem.price = 480;
	rItem.Weight = 1.2;
	
	rItem = ItemsFromID("grapeshot_double");
	rItem.component.t3.id 	=  "gold_dublon";
	rItem.component.t3.use =  "Component";
	rItem.component.t3.qty =  7;
	rItem.component.t4.id =  "ArmoryPaper";
	rItem.component.t4.use =  "Component";
	rItem.component.t4.qty =  1;
	rItem.component.t5.id 	=  "mineral15";
	rItem.component.t5.use =  "AlchemyTool";
	rItem.component.t5.qty =  1;
	rItem.price = 480;
	rItem.Weight = 1.2;
}

void ReinitGunsDamage()
{
	//InitGunExt(id,	sAttr,  sBullet,  sGunPowder, DmgMin, DmgMax, EnergyP, MultiDamage, MisFire, ChargeSpeed,isDefault);
	InitGunExt0008(		 "pistol1", "t1",  	     "cartridge",               "",  52.0,  86.0,   0.0,  0, 0, 26, 0);	
	InitGunExt0008(		 "pistol1", "t2", 		    "bullet",      "gunpowder",  45.0,  75.0,   0.0,  0, 0, 35, 1);	
	InitGunExt0008( 	 "pistol2", "t1", 	     "grapeshot",      "gunpowder",  30.0,  80.0,   0.0,  1, 0, 40, 1);	
	InitGunExt0008(		 "pistol3", "t1", 	     "grapeshot",      "gunpowder",  40.0,  90.0,   0.0, 1, 2, 40, 1);
	InitGunExt0008(		 "pistol4", "t1", 	     "cartridge",              "",   40.0,  63.0,   0.0, 0, 0,  45, 0);	
	InitGunExt0008(		 "pistol4", "t2", 		    "bullet",      "gunpowder",  35.0,  55.0,   0.0, 0, 0,  60, 1);	
	InitGunExt0008(		 "pistol5", "t1", 	     "cartridge",              "",   81.0, 132.0,   0.0, 0, 2,  36, 0);	
	InitGunExt0008(		 "pistol5", "t2", 		    "bullet",      "gunpowder",  70.0, 115.0,   0.0, 0, 2,  48, 1);	
	InitGunExt0008(		 "pistol6", "t1", 	     "cartridge",               "",  46.0,  75.0,   0.0, 0, 0,  34, 0);	
	InitGunExt0008(		 "pistol6", "t2", 		    "bullet",      "gunpowder",  40.0,  65.0,   0.0, 0, 0,  45, 1);	
	InitGunExt0008(		 "pistol7", "t1","shotgun_cartridge",    "GunCap_colt", 125.0, 200.0,   10.0, 0, 0, 30, 1);	
	InitGunExt0008(		 "pistol8", "t1", 	     "grapeshot",      "gunpowder",  25.0,  50.0,    5.0, 1, 0, 40, 1);	
	InitGunExt0008(		 "pistol8", "t2", 		   "harpoon",      "gunpowder", 150.0, 250.0,   20.0, 0, 0, 40, 0);	
	InitGunExt0008(		 "pistol8", "t3", 		  "GunEchin",               "", 120.0, 220.0,   20.0, 1, 0, 20, 0);
	InitGunExt0008(		 "pistol9", "t1", 	     "cartridge",               "",  63.0, 144.0,    0.0, 0, 0, 41, 0);	
	InitGunExt0008(		 "pistol9", "t2", 		    "bullet",      "gunpowder",  55.0, 125.0,    0.0, 0, 0, 55, 1);	
	InitGunExt0008(		 "pistol10", "t1", 	     "cartridge",               "",  58.0,  98.0,    0.0, 0, 0, 45, 0); // Золотой орёл cle
	InitGunExt0008(		 "pistol10", "t2", 		    "bullet",      "gunpowder",  50.0,  85.0,    0.0, 0, 0, 60, 1); // Золотой орёл cle
	InitGunExt0008(		 "pistol11", "t1", 	     "cartridge",               "",   6.0, 403.0,  30.0,  0, 0, 58, 0); // Чудовище cle
	InitGunExt0008(		 "pistol11", "t2", 		    "bullet",      "gunpowder",   5.0, 350.0,  30.0,  0, 0, 77, 1); // Чудовище cle
	InitGunExt0008(		 "pistol12", "t1", 	     "cartridge",               "",  52.0,  98.0,  0.0,  0, 0,  39, 0); // Обрез штуцера cle
	InitGunExt0008(		 "pistol12", "t2", 		    "bullet",      "gunpowder",  45.0,  85.0,  0.0,  0, 0,  52, 1); // Обрез штуцера cle
	InitGunExt0008(		 "pistol13", "t1",       "cartridge",               "",  58.0,  75.0, 10.0,  0, 0,  38, 0); // Кремневый револьвер cle
	InitGunExt0008(		 "pistol13", "t2",          "bullet",      "gunpowder",  50.0,  65.0, 10.0,  0, 0,  50, 1); // Кремневый револьвер cle
	InitGunExt0008(		 "pistol14", "t1", 		    "bullet",      "gunpowder",  80.0, 135.0,  0.0,  0, 4,  54, 1); // Дуэльный двухзарядный пистоль cle 1.3
	InitGunExt0008(		 "pistol14", "t2", 		   "cartridge",      "",         92.0, 155.0,  0.0,  0, 4,  41, 0);
	InitGunExt0008(		 "howdah",  "t1",		 "grapeshot",	   "gunpowder",  25.0,  70.0,  5.0,  1, 0,  40, 1);		
    InitGunExt0008(		 "howdah",  "t2",		  "GunEchin",         		"", 115.0, 215.0,  20.0,  1, 0,  20, 0);
	InitGunExt0008(	  "mortairgun", "t1", 	       "grenade",               "", 120.0, 360.0,  20.0,  1, 0,  30, 1); // Ручная мортирка cle
	InitGunExt0008(   "mortairgun", "t2",    "powder_pellet",               "",   5.0,  10.0, 120.0,  1, 0,  30, 0); // Ручная мортирка cle
	InitGunExt0008(		"mushket1", "t1", 	     "cartridge",               "", 109.0, 196.0,   0.0,  0, 0,  34, 0);	
	InitGunExt0008(		"mushket1", "t2", 		    "bullet",      "gunpowder",  95.0, 170.0,   0.0,  0, 0,  45, 1);	
	InitGunExt0008(		"mushket2", "t1", 	     "cartridge",               "", 144.0, 230.0,   0.0,  0, 0,  33, 0);	
	InitGunExt0008(		"mushket2", "t2", 		    "bullet",      "gunpowder", 125.0, 200.0,   0.0,  0, 0,  44, 1);	
	InitGunExt0008(		"mushket3", "t1", 	     "grapeshot",      "gunpowder",  70.0, 120.0,   0.0,  1, 0,  25, 1);	
	InitGunExt0008("grape_mushket", "t1", 	       "grenade",               "", 240.0, 440.0,  10.0,  1, 0,  25, 1);	
	InitGunExt0008("grape_mushket", "t2",    "powder_pellet",               "",  15.0,  85.0, 120.0,  1, 0,  15, 0);	
	InitGunExt0008(		"mushket5", "t1", 	     "cartridge",               "", 132.0, 397.0,  15.0,  0, 0,  30, 0);	
	InitGunExt0008(		"mushket5", "t2", 		    "bullet",      "gunpowder", 115.0, 345.0,  15.0,  0, 0,  40, 1);	
	InitGunExt0008(		"mushket6", "t1", 	     "grapeshot",      "gunpowder",  90.0, 155.0,  20.0,  1, 0,  30, 1);	
	InitGunExt0008(		"mushket6", "t2", 	      "GunEchin",               "", 115.0, 180.0,  20.0,  1, 0,  15, 0);
	InitGunExt0008(		"mushket7", "t1", 	     	"bullet",      "gunpowder", 135.0, 210.0,   0.0,  0, 0,  38, 1); // Качественный мушкет cle
	InitGunExt0008(		"mushket7", "t2", 	     "cartridge",               "", 155.0, 242.0,   0.0,  0, 0,  29, 0); // Качественный мушкет cle
	InitGunExt0008(		"mushket8", "t1", 	     	"bullet",      "gunpowder",  95.0, 160.0,   0.0,  0, 0,  42, 1); // Четырехзарядный штуцер cle
	InitGunExt0008(		"mushket8", "t2", 	     "cartridge",               "", 109.0, 184.0,   0.0,  0, 0,  32, 0); // Четырехзарядный штуцер cle
	InitGunExt0008(	  "mushket2x2", "t1", 	     "cartridge",               "", 138.0, 224.0,  15.0,  0, 0,  23, 0);	
	InitGunExt0008(	  "mushket2x2", "t2", 		    "bullet",      "gunpowder", 120.0, 195.0,  15.0,  0, 0,  30, 1);
	InitGunExt0008(		"mushket9", "t1", 	     "grapeshot",      "gunpowder",  70.0, 120.0,   0.0,  1, 0,  45, 1); // Аркебуза конкистадора SP2
	InitGunExt0008(		"mushket9", "t2", 	      "GunEchin",               "",  70.0, 120.0,   0.0,  1, 0,  35, 0); // Аркебуза конкистадора SP2
	InitGunExt0008(	   "mushket10", "t1", 	     "cartridge",               "", 150.0, 253.0,  0.0,   0, 0,  32, 0);	
	InitGunExt0008(	   "mushket10", "t2", 		    "bullet",      "gunpowder", 130.0, 220.0,  0.0,   0, 0,  42, 1);
	
	if(isMultiObjectKnown("bullet_double"))
	{
		InitGunExt0008(		"mushket1", "t3",    "bullet_double",      			"", 240.0, 440.0,   0.0,   0, 0,  20, 0);
		InitGunExt0008(		"mushket2", "t3", 	 "bullet_double",      			"", 270.0, 470.0,   0.0,   0, 0,  15, 0);
		InitGunExt0008(		"mushket5", "t3", 	 "bullet_double",      			"", 400.0, 600.0,  15.0,   0, 0,  15, 0);
		InitGunExt0008(		"mushket7", "t3", 	 "bullet_double",      			"", 300.0, 440.0,   0.0,   0, 0,  18, 0); // Качественный мушкет cle
		InitGunExt0008(		"mushket8", "t3", 	 "bullet_double",      			"", 200.0, 400.0,   0.0,   0, 0,  20, 0); // Четырехзарядный штуцер cle
		InitGunExt0008(	  "mushket2x2", "t3", 	 "bullet_double",      			"", 360.0, 560.0,  15.0,   0, 0,  15, 0);
		InitGunExt0008(	  "mushket10",  "t3", 	 "bullet_double",      			"", 360.0, 440.0,   0.0,   0, 0,  21, 0);
	}
	if(isMultiObjectKnown("grapeshot_double"))
	{
		InitGunExt0008(		"mushket3", "t2", "grapeshot_double",	            "", 140.0, 240.0,   0.0,   1, 0, 13, 0);
		InitGunExt0008(		"mushket6", "t3", "grapeshot_double",	            "", 180.0, 310.0,  20.0,   1, 0,  15, 0);
		InitGunExt0008(		"mushket9", "t3", "grapeshot_double",	            "", 140.0, 240.0,   0.0,   1, 0,  23, 0);
		
		ref itm;
		
		makeref(itm, items[FindItem("mushket9")]);
		
		itm.type.t3.basedmg  = 3;
		itm.type.t3.shards  = 110;
		itm.type.t3.width   = 8.5;
		itm.type.t3.height  = 7.85;
		itm.type.t3.area    = XI_ConvertString("grapes_area_4");
		
		if(CheckAttribute(itm, "UpgradeStage"))
		{
			int iUpgradeStage = sti(itm.UpgradeStage);
			
			switch (iUpgradeStage)
			{
				case 2:	
					itm.type.t3.basedmg  = 3;
					itm.type.t3.shards  = 120;
					itm.type.t3.width   = 7.0;
					itm.type.t3.height  = 5.75;
					itm.type.t3.area    = XI_ConvertString("grapes_area_4");
				break;
				
				case 3:	
					itm.type.t3.basedmg  = 4;
					itm.type.t3.shards  = 130;
					itm.type.t3.width   = 5.5;
					itm.type.t3.height  = 4.5;
					itm.type.t3.area    = XI_ConvertString("grapes_area_3");
				break;
				
				case 4:	
					itm.type.t3.basedmg  = 5;
					itm.type.t3.shards  = 130;
					itm.type.t3.width   = 4.5;
					itm.type.t3.height  = 3.75;
					itm.type.t3.area    = XI_ConvertString("grapes_area_2");
					itm.type.t3.ChargeSpeed = 18;
				break;
			}
		}
	}
}

void InitGunExt0008(string id,			
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