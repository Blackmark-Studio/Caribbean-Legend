void FillPersonTemplateTreasurer(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.BasicCommerce;
		template.list.Intendant;
		template.list.ProfessionalCommerce;
	}
	else
	{
		template.list.BasicCommerce;
		template.list.AdvancedCommerce;
		template.list.ProfessionalCommerce;
	}
}

void FillPersonTemplateLeftovers(ref template, string exclude1, string exclude2)
{
	template.random = true;
	if (exclude1 != "treasurer" && exclude2 != "treasurer") FillPersonTemplateTreasurer(template);
	if (exclude1 != "cannoner"  && exclude2 != "cannoner")  FillPersonTemplateCannoner(template); 
	if (exclude1 != "boatswain" && exclude2 != "boatswain") FillPersonTemplateBoatswain(template);
	if (exclude1 != "carpenter" && exclude2 != "carpenter") FillPersonTemplateCarpenter(template);
	if (exclude1 != "navigator" && exclude2 != "navigator") FillPersonTemplateNavigator(template);
	if (exclude1 != "doctor"    && exclude2 != "doctor")    FillPersonTemplateDoctor(template);
}

void FillPersonTemplateCannoner(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.HullDamageUp;
		template.list.SailsDamageUp;
		template.list.CrewDamageUp;
		template.list.CannonProfessional;
	}
	else
	{
		template.list.FastReload;
		template.list.ImmediateReload;
		template.list.LongRangeShoot;
		template.list.CannonProfessional;
	}
}

void FillPersonTemplateBoatswain(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.Ambuscade;
		template.list.CoordinatedBoarding;
		template.list.GrapplingProfessional;
	}
	else
	{
		template.list.BruteForce;
		template.list.GrapplingProfessional;
	}
}

void FillPersonTemplateCarpenter(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.AdvancedBattleState;
		template.list.ShipDefenseProfessional;
	}
	else
	{
		template.list.Carpenter;
		template.list.LightRepair;
		template.list.Builder;
		template.list.BasicBattleState;
		template.list.AdvancedBattleState;
		template.list.ShipDefenseProfessional;
	}
}

void FillPersonTemplateNavigator(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.ShipSpeedUp;
		template.list.LoneWolf;
		template.list.Thrift;
		template.list.SailingProfessional;
	}
	else
	{
		template.list.ShipTurnRateUp;
		template.list.Turn180;
		template.list.SailingProfessional;
	}
}

void FillPersonTemplateDoctor(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.Moonshiner;
		template.list.Quartermaster;
	}
	else
	{
		template.list.BoardingPrepare;
		template.list.Quartermaster;
	}
}

void FillPersonTemplatePirate(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.PerfectBalance;
		template.list.Dragoon;
		template.list.SabreHurricane;
		template.list.OttomanGrip;
		template.list.BladeDancer;
	}
	else
	{
		template.list.Dragoon;
		template.list.Flanking;
		template.list.BladeDancer;
		template.list.SabreHurricane;
		template.list.OttomanGrip;
	}
}

void FillPersonTemplateSoldier(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.AdvancedDefense;
		template.list.HardHitter;
		template.list.Medic;
		template.list.PalaceGuard;
	}
	else
	{
		template.list.Muscles;
		template.list.Inertia;
		template.list.IronWill;
		template.list.PalaceGuard;
	}
}

void FillPersonTemplateDuelist(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.HeartBreaker;
		template.list.Virtuosity;
		template.list.Exhaustion;
		template.list.Puncher;
		template.list.Reaper;
	}
	else
	{
		template.list.Dodgy;
		template.list.NeckStrike;
		template.list.Sliding;
		template.list.Reach;
		template.list.Reaper;
	}
}

void FillPersonTemplateGunman(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.KeenEye;
		template.list.Chance;
		template.list.LeadRain;
		template.list.GunProfessional;
	}
	else
	{
		template.list.Chance;
		template.list.ShootToKill;
		template.list.Kern;
		template.list.GunProfessional;
	}
}

void FillPersonTemplatePeasant(ref template)
{
	if (sti(template.seed) < 2)
	{
		template.list.HPPlus;
		template.list.AdvancedDefense;
		template.list.Dragoon;
		template.list.Inertia;
		template.list.IronWill;
		template.list.ByWorker;
	}
	else
	{
		template.list.EnergyPlus;
		template.list.CriticalHit;
		template.list.Virtuosity;
		template.list.Trustworthy;
		template.list.Strychnine;
		template.list.ByWorker;
	}
}

void FillPersonTemplateUtility(ref template)
{
	template.random = true;
	template.list.HPPlus;
	template.list.AdvancedDefense;
	template.list.Dragoon;
	template.list.Inertia;
	template.list.IronWill;
	template.list.EnergyPlus;
	template.list.CriticalHit;
	template.list.Virtuosity;
	template.list.Trustworthy;
	template.list.Strychnine;
}

void FillPersonTemplate(ref template, string type)
{
	string patternFunc = "FillPersonTemplate" + type;
	call patternFunc(template);
}

string GetPatternType(string pattern)
{
	switch(pattern)
	{
		case GEN_ARCHETYPE_SOLDIER: return "personal"; break;
		case GEN_ARCHETYPE_DUELIST: return "personal"; break;
		case GEN_ARCHETYPE_GUNMAN:  return "personal"; break;
		case GEN_ARCHETYPE_PIRATE:  return "personal"; break;
		case GEN_ARCHETYPE_PEASANT: return "personal"; break;
	}
	return "ship";
}
