void FillPersonTemplateTreasurer(ref template)
{
	if (int(template.seed) < 50)
	{
		touchattr(template.list.BasicCommerce);
		touchattr(template.list.TrainedEye);
		touchattr(template.list.Intendant);
	}
	else
	{
		touchattr(template.list.BasicCommerce);
		touchattr(template.list.ProfessionalCommerce);
		touchattr(template.list.Intendant);
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
	if (int(template.seed) < 50)
	{
		touchattr(template.list.HullDamageUp);
		touchattr(template.list.SailsDamageUp);
		touchattr(template.list.CrewDamageUp);
		touchattr(template.list.CannonProfessional);
	}
	else
	{
		touchattr(template.list.FastReload);
		touchattr(template.list.ImmediateReload);
		touchattr(template.list.LongRangeShoot);
		touchattr(template.list.CannonProfessional);
	}
}
void FillPersonTemplateFree(ref template)
{
	template.free = true;
	// тут ничего нет, очки остаются у персонажа
}

void FillPersonTemplateBoatswain(ref template)
{
	if (int(template.seed) < 50)
	{
		touchattr(template.list.Ambuscade);
		touchattr(template.list.CoordinatedBoarding);
		touchattr(template.list.GrapplingProfessional);
	}
	else
	{
		touchattr(template.list.BruteForce);
		touchattr(template.list.GrapplingProfessional);
	}
}

void FillPersonTemplateCarpenter(ref template)
{
	if (int(template.seed) < 50)
	{
		touchattr(template.list.AdvancedBattleState);
		touchattr(template.list.ShipDefenseProfessional);
	}
	else
	{
		touchattr(template.list.Carpenter);
		touchattr(template.list.LightRepair);
		touchattr(template.list.Builder);
		touchattr(template.list.BasicBattleState);
		touchattr(template.list.AdvancedBattleState);
		touchattr(template.list.ShipDefenseProfessional);
	}
}

void FillPersonTemplateNavigator(ref template)
{
	if (int(template.seed) < 50)
	{
		touchattr(template.list.ShipSpeedUp);
		touchattr(template.list.LoneWolf);
		touchattr(template.list.Thrift);
		touchattr(template.list.SailingProfessional);
	}
	else
	{
		touchattr(template.list.ShipTurnRateUp);
		touchattr(template.list.Turn180);
		touchattr(template.list.SailingProfessional);
	}
}

void FillPersonTemplateDoctor(ref template)
{
	if (int(template.seed) < 50)
	{
		touchattr(template.list.Moonshiner);
		touchattr(template.list.Quartermaster);
	}
	else
	{
		touchattr(template.list.BoardingPrepare);
		touchattr(template.list.Quartermaster);
	}
}

void FillPersonTemplatePirate(ref template)
{
	if (int(template.seed) < 50)
	{
		touchattr(template.list.PerfectBalance);
		touchattr(template.list.Dragoon);
		touchattr(template.list.SabreHurricane);
		touchattr(template.list.OttomanGrip);
		touchattr(template.list.BladeDancer);
	}
	else
	{
		touchattr(template.list.Dragoon);
		touchattr(template.list.Flanking);
		touchattr(template.list.BladeDancer);
		touchattr(template.list.SabreHurricane);
		touchattr(template.list.OttomanGrip);
	}
}

void FillPersonTemplateSoldier(ref template)
{
	if (int(template.seed) < 50)
	{
		touchattr(template.list.AdvancedDefense);
		touchattr(template.list.HardHitter);
		touchattr(template.list.Medic);
		touchattr(template.list.PalaceGuard);
	}
	else
	{
		touchattr(template.list.Muscles);
		touchattr(template.list.Inertia);
		touchattr(template.list.IronWill);
		touchattr(template.list.PalaceGuard);
	}
}

void FillPersonTemplateDuelist(ref template)
{
	if (int(template.seed) < 50)
	{
		touchattr(template.list.HeartBreaker);
		touchattr(template.list.Virtuosity);
		touchattr(template.list.Exhaustion);
		touchattr(template.list.Puncher);
		touchattr(template.list.Reaper);
	}
	else
	{
		touchattr(template.list.Dodgy);
		touchattr(template.list.NeckStrike);
		touchattr(template.list.Sliding);
		touchattr(template.list.Reach);
		touchattr(template.list.Reaper);
	}
}

void FillPersonTemplateGunman(ref template)
{
	if (int(template.seed) < 50)
	{
		touchattr(template.list.Gunman);
		touchattr(template.list.KeenEye);
		touchattr(template.list.Chance);
		touchattr(template.list.LeadRain);
		touchattr(template.list.GunProfessional);
	}
	else
	{
		touchattr(template.list.Gunman);
		touchattr(template.list.Chance);
		touchattr(template.list.ShootToKill);
		touchattr(template.list.Kern);
		touchattr(template.list.GunProfessional);
	}
}

void FillPersonTemplatePeasant(ref template)
{
	int seed = int(template.seed);
	if (seed < 40)
	{
		touchattr(template.list.HPPlus);
		touchattr(template.list.AdvancedDefense);
		touchattr(template.list.Dragoon);
		touchattr(template.list.ByWorker);
		touchattr(template.list.Inertia);
		touchattr(template.list.IronWill);
		touchattr(template.list.Captain);
	}
	else if (seed < 80)
	{
		touchattr(template.list.EnergyPlus);
		touchattr(template.list.CriticalHit);
		touchattr(template.list.Virtuosity);
		touchattr(template.list.Trustworthy);
		touchattr(template.list.ByWorker);
		touchattr(template.list.Strychnine);
		touchattr(template.list.Captain);
	}
	else if (seed < 90)
	{
		touchattr(template.list.Practice);
		touchattr(template.list.ByWorker);
		touchattr(template.list.DarkHorse);
		touchattr(template.list.Captain);
		touchattr(template.list.Master);
		touchattr(template.list.Collection);
	}
	else
	{
		touchattr(template.list.SharedExperience);
		touchattr(template.list.Grus);
		touchattr(template.list.Tiefit);
		touchattr(template.list.Captain);
		touchattr(template.list.Gossip);
		touchattr(template.list.Looting);
	}
}

void FillPersonTemplateUtility(ref template)
{
	template.random = true;
	touchattr(template.list.HPPlus);
	touchattr(template.list.AdvancedDefense);
	touchattr(template.list.Dragoon);
	touchattr(template.list.Inertia);
	touchattr(template.list.IronWill);
	touchattr(template.list.EnergyPlus);
	touchattr(template.list.CriticalHit);
	touchattr(template.list.Virtuosity);
	touchattr(template.list.Trustworthy);
	touchattr(template.list.Strychnine);
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
