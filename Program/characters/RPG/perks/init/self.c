void initSelfPerks(ref list)
{
	object temp;
	aref perks;
	aref modifier;
	makearef(perks, temp.perks);

	// Мушкетёр
	perks.FastHands.cost = 1;
	SetArefModifier(perks, "FastHands", M_CROSSHAIR_UPDATE_SPEED, PERK_VALUE_FAST_HANDS);
	SetArefModifier(perks, "FastHands", FIRE_MOVE + "_" + M_ACTION_SPEED, PERK_VALUE_FAST_HANDS);
	SetAttribute(perks,"FastHands.descriptors.OneHanded", true);	
	SetAttribute(perks,"FastHands.descriptors.TwoHanded", true);

	perks.AmmoRig.cost = 1;
	SetArefModifier(perks, "AmmoRig", GUN_ITEM_TYPE    + "_" + M_RELOAD_SPEED, PERK_VALUE_AMMO_RIG);
	SetArefModifier(perks, "AmmoRig", MUSKET_ITEM_TYPE + "_" + M_RELOAD_SPEED, PERK_VALUE_AMMO_RIG);
	SetAttribute(perks,"AmmoRig.descriptors.OneHanded", true);	
	SetAttribute(perks,"AmmoRig.descriptors.TwoHanded", true);

	perks.Preaim.cost = 1;
	SetAttribute(perks,"Preaim.descriptors.OneHanded", true);	
	SetAttribute(perks,"Preaim.descriptors.TwoHanded", true);
	SetAttribute(perks,"Preaim.descriptors.Alternate", true);

	perks.Gunman.cost = 2;
	perks.Gunman.condition.ammoRig = true;
	perks.Gunman.condition.preaim = true;
	SetArefModifier(perks, "Gunman", GUN_ITEM_TYPE    + "_" + M_RELOAD_SPEED, PERK_VALUE_GUNMAN);
	SetArefModifier(perks, "Gunman", MUSKET_ITEM_TYPE + "_" + M_RELOAD_SPEED, PERK_VALUE_GUNMAN);
	SetArefModifier(perks, "Gunman", SHOT_STRIKE      + "_" + M_DAMAGE, PERK_VALUE_GUNMAN);
	SetAttribute(perks,"Gunman.descriptors.OneHanded", true);	
	SetAttribute(perks,"Gunman.descriptors.MultiCharge", true);	
	SetAttribute(perks,"Gunman.descriptors.TwoHanded", true);

	perks.KeenEye.cost = 2;
	perks.KeenEye.condition.fastHands = true;
	perks.KeenEye.condition.ammoRig = true;
	SetArefModifier(perks, "KeenEye", M_HEADSHOT_DAMAGE, PERK_VALUE_KEEN_EYE);
	SetAttribute(perks,"KeenEye.descriptors.OneHanded", true);
	SetAttribute(perks,"KeenEye.descriptors.TwoHanded", true);
	SetAttribute(perks,"KeenEye.descriptors.Alternate", true);



	perks.PowderFeel.cost = 2;
	perks.PowderFeel.condition.keenEye = true;
	SetAttribute(perks,"PowderFeel.descriptors.Alchemy", true);
	SetAttribute(perks,"PowderFeel.descriptors.Alternate", true);

	perks.Drill.cost = 2;
	perks.Drill.condition.Gunman = true;
	SetArefModifier(perks, "Drill", MUSKET_RUN_MOVE  + "_" + M_ACTION_SPEED, PERK_VALUE_DRILL);
	SetArefModifier(perks, "Drill", AIMING_WALK_MOVE + "_" + M_ACTION_SPEED, PERK_VALUE_DRILL);
	SetAttribute(perks,"Drill.descriptors.TwoHanded", true);


	perks.LeadRain.cost = 2;
	perks.LeadRain.mtp = PERK_VALUE_LEAD_RAIN;
	perks.LeadRain.condition.keenEye = true;
	SetAttribute(perks,"LeadRain.descriptors.OneHanded", true);	
	SetAttribute(perks,"LeadRain.descriptors.TwoHanded", true);

	perks.ShootToKill.cost = 2;
	perks.ShootToKill.condition.Gunman = true;
	SetAttribute(perks,"ShootToKill.descriptors.OneHanded", true);	
	SetAttribute(perks,"ShootToKill.descriptors.TwoHanded", true);

	perks.GunProfessional.cost = 3;
	perks.GunProfessional.condition.shootToKill = true;
	perks.GunProfessional.condition.leadRain = true;
	SetArefModifier(perks, "GunProfessional", GUN_ITEM_TYPE    + "_" + M_RELOAD_SPEED, PERK_VALUE_GUN_PROFESSIONAL);
	SetArefModifier(perks, "GunProfessional", MUSKET_ITEM_TYPE + "_" + M_RELOAD_SPEED, PERK_VALUE_GUN_PROFESSIONAL);
	SetArefModifier(perks, "GunProfessional", SHOT_STRIKE  + "_" + M_DAMAGE, PERK_VALUE_GUN_PROFESSIONAL);
	SetAttribute(perks,"GunProfessional.descriptors.TwoHanded", true);	
	SetAttribute(perks,"GunProfessional.descriptors.MultiCharge", true);


	// Солдат
	// 1 cлой

	perks.BasicDefense.cost = 1;
	SetArefModifier(perks, "BasicDefense", M_REDUCE_DAMAGE, PERK_VALUE_BASIC_DEFENSE);
	
	perks.Medic.cost = 1;
	SetArefModifier(perks, "Medic", M_HP_MAX, PERK_VALUE_MEDIC);
	
	//2 слой

	perks.PalaceGuard.cost = 2;
	perks.PalaceGuard.condition.BasicDefense = true;
	AddArefCallback(perks, "PalaceGuard", CT_EQUIP, "Perk_PalaceGuard");
	SetAttribute(perks,"PalaceGuard.descriptors." +M_WEAPON_TYPE + "_" +  WEAPON_HEAVY, true);
	SetAttribute(perks,"PalaceGuard.descriptors." +M_WEAPON_CURVATURE + "_" +  WEAPON_CURVE, true);

	perks.IronWill.cost = 2;
	perks.IronWill.condition.BasicDefense = true;
	perks.IronWill.TimeDelay    = 180; 
	perks.IronWill.TimeDuration = 180;

	perks.Conquest.cost = 2;
	perks.Conquest.condition.Medic = true;
	AddArefCallback(perks, "Conquest", CT_EQUIP, "Perk_Conquest");
	SetAttribute(perks,"Conquest.descriptors." +M_WEAPON_LENGTH + "_" +  WEAPON_LONG, true);

	perks.Muscles.cost = 2;
	perks.Muscles.condition.Medic = true;
	AddArefCallback(perks, "Muscles", CT_EQUIP, "Perk_Muscles");
	SetArefModifier(perks, "Muscles", M_STAGGER_SPEED, PERK_VALUE3_MUSCLES);
	SetAttribute(perks,"Muscles.descriptors." +M_WEAPON_TYPE + "_" +  WEAPON_HEAVY, true);

	//3 слой

	perks.AdvancedDefense.cost = 3;
	perks.AdvancedDefense.condition.IronWill = true;
	SetArefModifier(perks, "AdvancedDefense", M_REDUCE_DAMAGE, PERK_VALUE_ADVANCED_DEFENSE);
	SetArefModifier(perks, "AdvancedDefense", M_REDUCE_CRIT_DAMAGE, PERK_VALUE2_ADVANCED_DEFENSE);

	perks.HPPlus.cost = 3;
	perks.HPPlus.condition.Conquest = true;
	SetArefModifier(perks, "HPPlus", M_HP_PER_RANK, PERK_VALUE_HP_PLUS);

	//4 слой (мастер-перк)
	
	perks.HardHitter.cost = 3;
	perks.HardHitter.condition.HPPlus = true;
	perks.HardHitter.condition.AdvancedDefense = true;
	AddArefCallback(perks, "HardHitter", CT_EQUIP, "Perk_HardHitter");
	SetAttribute(perks, "HardHitter.descriptors." + M_WEAPON_TYPE + "_" +  WEAPON_HEAVY, true);

	

	

	// Фехтовальщик
	perks.CunningStrike.cost = 1;
	AddArefCallback(perks, "CunningStrike", CT_EQUIP, "Perk_CunningStrike");
	SetAttribute(perks,"CunningStrike.descriptors." +M_WEAPON_TYPE + "_" +  WEAPON_LIGHT, true);

	perks.Heartbreaker.cost = 2;
	perks.Heartbreaker.condition.CunningStrike = true;
	AddArefCallback(perks, "Heartbreaker", CT_EQUIP, "Perk_Heartbreaker");
	SetAttribute(perks,"Heartbreaker.descriptors." +M_WEAPON_CURVATURE + "_" +  WEAPON_STRAIGHT, true);	

	perks.Dodgy.cost = 2;
	perks.Dodgy.condition.CunningStrike = true;

	perks.CriticalHit.cost = 3;
	perks.CriticalHit.condition.CunningStrike = true;
	SetArefModifier(perks, "CriticalHit", BLADE_ITEM_TYPE  + "_" + M_CRIT_CHANCE, PERK_VALUE_CRITICAL_HIT);
	SetArefModifier(perks, "CriticalHit", GUN_ITEM_TYPE    + "_" + M_CRIT_CHANCE, PERK_VALUE_CRITICAL_HIT);
	SetArefModifier(perks, "CriticalHit", MUSKET_ITEM_TYPE + "_" + M_CRIT_CHANCE, PERK_VALUE_CRITICAL_HIT);


	perks.Sliding.cost = 3;
	perks.Sliding.condition.CriticalHit = true;
	perks.Sliding.condition.Dodgy = true;
	SetAttribute(perks,"Sliding.descriptors." +M_WEAPON_TYPE + "_" +  WEAPON_LIGHT, true);

	perks.Exhaustion.cost = 3;
	perks.Exhaustion.condition.Heartbreaker = true;
	perks.Exhaustion.condition.CriticalHit = true;
	SetAttribute(perks,"Exhaustion.descriptors." +M_WEAPON_LENGTH + "_" +  WEAPON_SHORT, true);

	perks.Reaper.cost = 3;
	perks.Reaper.condition.Exhaustion = true;
	perks.Reaper.condition.Sliding = true;
	SetArefModifier(perks, "Reaper", BLADE_ITEM_TYPE  + "_" + M_CRIT_DAMAGE, PERK_VALUE_REAPER);
	SetArefModifier(perks, "Reaper", GUN_ITEM_TYPE    + "_" + M_CRIT_DAMAGE, PERK_VALUE_REAPER);
	SetArefModifier(perks, "Reaper", MUSKET_ITEM_TYPE + "_" + M_CRIT_DAMAGE, PERK_VALUE_REAPER);



	// Пират
	// 1 cлой

	perks.Tireless.cost = 1;

	// 2 cлой 

	perks.PerfectBalance.cost = 2;
	perks.PerfectBalance.condition.Tireless = true;
	AddArefCallback(perks, "PerfectBalance", CT_EQUIP, "Perk_PerfectBalance");
	SetAttribute(perks,"PerfectBalance.descriptors." +M_WEAPON_TYPE + "_" +  WEAPON_MEDIUM, true);

	perks.MarathonRunner.cost = 2;
	perks.MarathonRunner.condition.Tireless = true;
	SetArefModifier(perks, "MarathonRunner", SPRINT_MOVE + "_" + M_ACTION_SPEED, PERK_VALUE2_MARATHON_RUNNER);
	SetAttribute(perks,"MarathonRunner.descriptors.Alternate", true);

	//3 слой
	perks.BladeDancer.cost = 3;
	perks.BladeDancer.condition.PerfectBalance = true;
	AddArefCallback(perks, "BladeDancer", CT_EQUIP, "Perk_BladeDancer");
	SetAttribute(perks,"BladeDancer.descriptors." +M_WEAPON_CURVATURE + "_" +  WEAPON_CURVE, true);

	perks.EnergyPlus.cost = 3;
	perks.EnergyPlus.condition.MarathonRunner = true;
	SetArefModifier(perks, "EnergyPlus", M_ENERGY_PER_RANK, PERK_VALUE_ENERGY_PLUS);

	
	//4 слой (мастер-перки)
	perks.Flanking.cost = 3;
	perks.Flanking.condition.BladeDancer = true;
	AddArefCallback(perks, "Flanking", CT_EQUIP, "Perk_Flanking");
	SetAttribute(perks,"Flanking.descriptors." +M_WEAPON_CURVATURE + "_" +  WEAPON_CURVE, true);

	
	perks.SabreHurricane.cost = 3;
	perks.SabreHurricane.condition.EnergyPlus = true;
	AddArefCallback(perks, "SabreHurricane", CT_EQUIP, "Perk_SabreHurricane");
	SetAttribute(perks,"SabreHurricane.descriptors." +M_WEAPON_TYPE + "_" +  WEAPON_MEDIUM, true);	
	SetAttribute(perks,"SabreHurricane.descriptors." +M_WEAPON_CURVATURE + "_" +  WEAPON_CURVE, true);

	// Авантюрист
	perks.Alchemy.cost = 1;
	SetAttribute(perks,"Alchemy.descriptors.Alchemy", true);
	SetAttribute(perks,"Alchemy.descriptors.Alternate", true);

	perks.Practice.cost = 2;
	perks.Practice.condition.Alchemy = true;
	SetAttribute(perks,"Practice.descriptors.Alchemy", true);
	AddArefCallback(perks, "Practice", CT_EQUIP, "Perk_Practice");

	perks.Strychnine.cost = 2;
	perks.Strychnine.condition.Practice = true;
	SetArefModifier(perks, "Strychnine", M_POISON_CHANCE, PERK_VALUE_STRYCHNINE);

	perks.DarkHorse.cost = 2;
	perks.DarkHorse.condition.Practice = true;
	AddArefCallback(perks, "DarkHorse", CT_EQUIP, "Perk_DarkHorse");

	perks.Master.cost = 3;
	perks.Master.condition.DarkHorse = true;
	perks.Master.condition.Strychnine = true;
	SetAttribute(perks,"Master.descriptors.Alchemy", true);
	SetAttribute(perks,"Master.descriptors.Alternate", true);

	perks.Grus.cost = 1;

	perks.Quiet.cost = 2;
	perks.Quiet.condition.Grus = true;
	SetAttribute(perks,"Quiet.descriptors.Alternate", true);

	perks.Looting.cost = 2;
	perks.Looting.condition.Quiet = true;
	SetAttribute(perks,"Looting.descriptors.Alternate", true);

	perks.Collection.cost = 3;
	perks.Collection.condition.Looting = true;
	SetAttribute(perks,"Collection.descriptors.Exotic", true);
	SetAttribute(perks,"Collection.descriptors.Alternate", true);
	AddArefCallback(perks, "Collection", CT_EQUIP, "Perk_Collection");

	perks.Trustworthy.cost = 1;
	SetAttribute(perks,"Trustworthy.descriptors.Alternate", true);

	perks.TieFit.cost = 2;
	perks.TieFit.condition.Trustworthy = true;
	AddArefCallback(perks, "TieFit", CT_EQUIP, "Perk_TieFit");
	AddArefCallback(perks, "TieFit", CT_EQUIP, "Perk_TieFitAlternate");
	SetAttribute(perks,"Tiefit.descriptors.Unremarkable", true);	
	SetAttribute(perks,"Tiefit.descriptors.Fancy", true);

	perks.Investor.cost = 2;
	perks.Investor.condition.Trustworthy = true;
	SetAttribute(perks,"Investor.descriptors.Alternate", true);

	perks.Gossip.cost = 3;
	perks.Gossip.condition.TieFit = true;
	perks.Gossip.condition.Investor = true;
	AddArefCallback(perks, "Gossip", CT_EQUIP, "Perk_Gossip");
	SetAttribute(perks,"Gossip.descriptors.Exotic", true);
	SetAttribute(perks,"Gossip.descriptors.Alternate", true);

	// Офицерская ветка
	perks.SharedExperience.cost = 1;
	perks.SharedExperience.NPCOnly = true;
	perks.ByWorker.cost = 2;
	perks.ByWorker.condition.SharedExperience = true;
	perks.ByWorker.NPCOnly = true;
	perks.Captain.cost = 3;
	perks.Captain.condition.ByWorker = true;
	perks.Captain.NPCOnly = true;

	// Мастерство
	perks.Chance.cost = 1;
	SetAttribute(perks,"Chance.descriptors.OneHanded", true);
	SetAttribute(perks,"Chance.descriptors.SingleCharge", true);
	SetArefModifier(perks, "Chance", GUN_ITEM_TYPE + "_" + M_CRIT_DAMAGE, PERK_VALUE_CHANCE);
	SetArefModifier(perks, "Chance", GUN_ITEM_TYPE + "_" + M_CRIT_CHANCE, PERK_VALUE_CHANCE2);

	
	perks.Bayonet.cost = 2;
	perks.Bayonet.condition.Chance = true;
	AddArefCallback(perks, "Bayonet", CT_EQUIP, "Perk_Bayonet");
	SetAttribute(perks,"Bayonet.descriptors.TwoHanded", true);
	SetAttribute(perks,"Bayonet.descriptors.Bayonet", true);



	perks.Kern.cost = 3;
	perks.Kern.condition.Bayonet = true;
	SetAttribute(perks,"Kern.descriptors.MultiCharge", true);


	perks.Dragoon.cost = 1;
	SetAttribute(perks,"Dragoon.descriptors." +M_WEAPON_TYPE + "_" +  WEAPON_MEDIUM, true);
	AddArefCallback(perks, "Dragoon", CT_EQUIP, "Perk_Dragoon");

	perks.MeatGrinder.cost = 2;
	perks.MeatGrinder.condition.Dragoon = true;
	SetAttribute(perks,"MeatGrinder.descriptors." +M_WEAPON_LENGTH + "_" +  WEAPON_SHORT, true);
	AddArefCallback(perks, "MeatGrinder", CT_EQUIP, "Perk_MeatGrinder");

	perks.NeckStrike.cost = 2;
	perks.NeckStrike.condition.Dragoon = true;
	SetAttribute(perks,"NeckStrike.descriptors." +M_WEAPON_LENGTH + "_" +  WEAPON_LONG, true);
	AddArefCallback(perks, "NeckStrike", CT_EQUIP, "Perk_NeckStrike");

	perks.Stabbing.cost = 1;
	SetAttribute(perks,"Stabbing.descriptors." +M_WEAPON_LENGTH + "_" +  WEAPON_SHORT, true);
	AddArefCallback(perks, "Stabbing", CT_EQUIP, "Perk_Stabbing");

	perks.Virtuosity.cost = 2;
	perks.Virtuosity.condition.Stabbing = true;
	SetAttribute(perks,"Virtuosity.descriptors." +M_WEAPON_TYPE + "_" +  WEAPON_LIGHT, true);
	AddArefCallback(perks, "Virtuosity", CT_EQUIP, "Perk_Virtuosity");

	perks.Puncher.cost = 3;
	perks.Puncher.condition.Virtuosity = true;
	SetAttribute(perks,"Puncher.descriptors." +M_WEAPON_CURVATURE + "_" +  WEAPON_STRAIGHT, true);
	AddArefCallback(perks, "Puncher", CT_EQUIP, "Perk_Puncher");

	perks.Reach.cost = 1;
	SetAttribute(perks,"Reach.descriptors." +M_WEAPON_LENGTH + "_" +  WEAPON_LONG, true);
	AddArefCallback(perks, "Reach", CT_EQUIP, "Perk_Reach");
	
	perks.Inertia.cost = 2;
	perks.Inertia.condition.Reach = true;
	SetAttribute(perks,"Inertia.descriptors." +M_WEAPON_TYPE + "_" +  WEAPON_HEAVY, true);
	AddArefCallback(perks, "Inertia", CT_EQUIP, "Perk_Inertia");

	perks.OttomanGrip.cost = 2;
	perks.OttomanGrip.condition.Reach = true;
	SetAttribute(perks,"OttomanGrip.descriptors." +M_WEAPON_CURVATURE + "_" +  WEAPON_CURVE, true);
	AddArefCallback(perks, "OttomanGrip", CT_EQUIP, "Perk_OttomanGrip");

	// Предыстория
	perks.TannedLeather.PlayerOnly = true;
	perks.TannedLeather.HeroType = "HT1";
	perks.TannedLeather.cost = -1;
	AddArefCallback(perks, "TannedLeather", CT_EQUIP, "Perk_TannedLeather");
	SetAttribute(perks,"TannedLeather.descriptors."+M_ARMOR_TYPE + "_" + ARMOR_LIGHT, true);

	perks.Mule.PlayerOnly = true;
	perks.Mule.HeroType = "HT3";
	perks.Mule.cost = -1;
	SetAttribute(perks,"Mule.descriptors."+M_WEAPON_TYPE + "_" + WEAPON_HEAVY, true);
	SetAttribute(perks,"Mule.descriptors."+M_ARMOR_TYPE + "_" + ARMOR_HEAVY, true);
	AddArefCallback(perks, "Mule", CT_EQUIP, "Perk_Mule");

	perks.Sniper.PlayerOnly = true;
	perks.Sniper.HeroType = "HT4";
	perks.Sniper.cost = -1;
	SetAttribute(perks,"Sniper.descriptors.OneHanded", true);	
	SetAttribute(perks,"Sniper.descriptors.TwoHanded", true);

	perks.TreasureHunter.PlayerOnly = true;
	perks.TreasureHunter.HeroType = "HT2";
	perks.TreasureHunter.cost = -1;

	for (int i = 0; i < GetAttributesNum(perks); i++)
	{
		aref perk = GetAttributeN(perks, i);
		perk.BaseType = "self";
	}

	CopyAttributesSafe(list, perks);
}
