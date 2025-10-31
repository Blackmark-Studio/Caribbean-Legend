void ApplyMigration(ref migrationState) {
	if(isMultiObjectKnown("bullet_double"))
	{
		InitGunExt3009(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,    0.0,  0, 0,  20, 0);
		InitGunExt3009(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,     0.0,  0, 0,  30, 0);
		InitGunExt3009(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,     0.0,  0, 2,  30, 0);
		InitGunExt3009(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,     0.0,  0, 0,  20, 0);
		InitGunExt3009(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,     0.0,  0, 0,  30, 0);
		InitGunExt3009(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0,    0.0,  0, 0,  30, 0);
		InitGunExt3009(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,   40.0,   0, 0, 100, 0);
		InitGunExt3009(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,    0.0,   0, 0,  20, 0);
		InitGunExt3009(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  15.0,    0, 0,  30, 0);
		InitGunExt3009(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,   0.0,    0, 4,  34, 0);
	}
	if(isMultiObjectKnown("grapeshot_double"))
	{
		InitGunExt3009( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,      0.0,  1, 0,  20, 0);
		InitGunExt3009(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,    0.0,  1, 2,  20, 0);
		InitGunExt3009(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,    5.0,   1, 0,  20, 0);
		InitGunExt3009(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,   5.0,    1, 0,  30, 0);
		InitGrapeGunExt3009(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
		InitGrapeGunExt3009(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
		InitGrapeGunExt3009(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
		InitGrapeGunExt3009(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	}

    // wdm веса
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_MEDIUM] = 15;
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_LARGE] = 9;
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_EXPEDITION] = 4;
    EncWeightBase[ENCOUNTER_TYPE_PATROL_SMALL] = 11;
    EncWeightBase[ENCOUNTER_TYPE_PATROL_MEDIUM] = 10;
    EncWeightBase[ENCOUNTER_TYPE_NAVAL_MEDIUM] = 5;
    EncWeightBase[ENCOUNTER_TYPE_PIRATE] = 16;
}

void InitGunExt3009(string id,			
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

void InitGrapeGunExt3009(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}