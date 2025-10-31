void initShipPerks(ref list)
{
	object temp;
	aref perks;
	aref modifier;
	makearef(perks, temp.perks);

	/////////////////////////  КОРАБЕЛЬНЫЕ /////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/// Перки для боцмана
	/////////////////////////////////////////////////////////////

	perks.CoordinatedBoarding.cost = 1;
	perks.CoordinatedBoarding.OfficerType = "boatswain";

	perks.Troopers.cost = 2; // боцман
	perks.Troopers.OfficerType = "boatswain";
	perks.Troopers.condition.CoordinatedBoarding = true;

	perks.LongRangeGrappling.cost = 1; // боцман
	perks.LongRangeGrappling.OfficerType = "boatswain";

	perks.Involvement.cost = 1;
	perks.Involvement.OfficerType = "boatswain";
	perks.Involvement.condition.LongRangeGrappling = true;

	perks.MusketsShoot.cost = 2; // боцман
	perks.MusketsShoot.condition.LongRangeGrappling = true;
	perks.MusketsShoot.OfficerType = "boatswain";

	perks.BruteForce.cost = 3;
	perks.BruteForce.condition.MusketsShoot = true;
	perks.BruteForce.OfficerType = "boatswain";

	perks.Ambuscade.cost = 3;
	perks.Ambuscade.condition.Involvement = true;
	perks.Ambuscade.OfficerType = "boatswain";

	perks.GrapplingProfessional.cost = 4; // боцман
	perks.GrapplingProfessional.condition.BruteForce = true;
	perks.GrapplingProfessional.condition.Ambuscade = true;
	perks.GrapplingProfessional.OfficerType = "boatswain";
	/////////////////////////////////////////////////////////////
	/// Перки для казначея
	/////////////////////////////////////////////////////////////

	perks.Mimicry.cost = -1; // счетовод(ht2)
	perks.Mimicry.PlayerOnly = true;
	perks.Mimicry.HeroType = "HT2";

	perks.RatsWolf.cost = -1; // счетовод(ht2)
	perks.RatsWolf.PlayerOnly = true;
	perks.RatsWolf.HeroType = "HT2";



	perks.BasicCommerce.cost = 1; // казначей
	perks.BasicCommerce.OfficerType = "treasurer";

	perks.QuickGlance.cost = 2;
	perks.QuickGlance.OfficerType = "treasurer";
	perks.QuickGlance.condition.BasicCommerce = true;

	perks.AdvancedCommerce.cost = 2; // казначей
	perks.AdvancedCommerce.OfficerType = "treasurer";
	perks.AdvancedCommerce.condition.BasicCommerce = true;

	perks.TrainedEye.cost = 3;
	perks.TrainedEye.OfficerType = "treasurer";
	perks.TrainedEye.condition.QuickGlance = true;

	perks.TradeConnections.cost = 3;
	perks.TradeConnections.OfficerType = "treasurer";
	perks.TradeConnections.condition.QuickGlance = true;
	perks.TradeConnections.condition.AdvancedCommerce = true;

	perks.ProfessionalCommerce.cost = 3; // казначей
	perks.ProfessionalCommerce.OfficerType = "treasurer";
	perks.ProfessionalCommerce.condition.AdvancedCommerce = true;

	perks.Intendant.cost = 4;
	perks.Intendant.condition.TrainedEye = true;
	perks.Intendant.condition.TradeConnections = true;
	perks.Intendant.condition.ProfessionalCommerce = true;
	perks.Intendant.OfficerType = "treasurer";

	/////////////////////////////////////////////////////////////
	/// Перки для канонира
	/////////////////////////////////////////////////////////////
	perks.FastReload.cost = 1; // канонир
	perks.FastReload.OfficerType = "cannoner";

	perks.LongRangeShoot.cost = 2; // канонир
	perks.LongRangeShoot.condition.FastReload = true;
	perks.LongRangeShoot.OfficerType = "cannoner";

	perks.ImmediateReload.cost = 2; // канонир
	perks.ImmediateReload.condition.FastReload = true;
	perks.ImmediateReload.TimeDelay = 300;
	perks.ImmediateReload.TimeDuration = 60;
	perks.ImmediateReload.OfficerType = "cannoner";

	perks.HullDamageUp.cost = 1; // канонир
	perks.HullDamageUp.OfficerType = "cannoner";

	perks.SailsDamageUp.cost = 1; // канонир
	perks.SailsDamageUp.OfficerType = "cannoner";

	perks.CrewDamageUp.cost = 2; // канонир
	perks.CrewDamageUp.OfficerType = "cannoner";
	perks.CrewDamageUp.condition.HullDamageUp = true;

	perks.BeneathWaterline.cost = 2;
	perks.BeneathWaterline.OfficerType = "cannoner";
	perks.BeneathWaterline.condition.SailsDamageUp = true;

	perks.CriticalShoot.cost = 3; // канонир
	perks.CriticalShoot.condition.ImmediateReload = true;
	perks.CriticalShoot.condition.LongRangeShoot = true;
	perks.CriticalShoot.condition.CrewDamageUp = true;
	perks.CriticalShoot.condition.BeneathWaterline = true;
	perks.CriticalShoot.OfficerType = "cannoner";


	perks.CannonProfessional.cost = 4; // канонир
	perks.CannonProfessional.condition.CriticalShoot = true;
	perks.CannonProfessional.OfficerType = "cannoner";

	perks.Bombardier.cost = -1; // стрелок(ht4)
	perks.Bombardier.PlayerOnly = true;
	perks.Bombardier.HeroType = "HT4";

	//================================================================
	/////////////////////////////////////////////////////////////
	/// Перки для плотника
	/////////////////////////////////////////////////////////////
	perks.BasicBattleState.cost = 1;
	perks.BasicBattleState.OfficerType = "carpenter";

	perks.Carpenter.cost = 2;
	perks.Carpenter.OfficerType = "carpenter";
	perks.Carpenter.condition.BasicBattleState = true;

	perks.LightRepair.cost = 2;
	perks.LightRepair.condition.BasicBattleState = true;
	perks.LightRepair.TimeDelay = 240;
	perks.LightRepair.TimeDuration = 60;
	perks.LightRepair.OfficerType = "carpenter";

	perks.AdvancedBattleState.cost = 3;
	perks.AdvancedBattleState.condition.Carpenter = true;
	perks.AdvancedBattleState.condition.LightRepair = true;
	perks.AdvancedBattleState.OfficerType = "carpenter";

	perks.Builder.cost = 3;
	perks.Builder.OfficerType = "carpenter";
	perks.Builder.condition.Carpenter = true;
	perks.Builder.condition.LightRepair = true;

	if (MOD_SKILL_ENEMY_RATE < 9) // belamour legendary edition для всех кроме ОК
	{
		perks.InstantRepair.cost = 3;
		perks.InstantRepair.condition.LightRepair = true;
		perks.InstantRepair.condition.Carpenter = true;
		perks.InstantRepair.TimeDelay = 120;
		perks.InstantRepair.TimeDuration = 30;
		perks.InstantRepair.OfficerType = "carpenter";
		perks.ShipDefenseProfessional.condition.InstantRepair = true;
	}

	perks.ShipDefenseProfessional.cost = 4;
	perks.ShipDefenseProfessional.condition.AdvancedBattleState = true;
	perks.ShipDefenseProfessional.condition.Builder = true;
	perks.ShipDefenseProfessional.OfficerType = "carpenter";
	

	/////////////////////////////////////////////////////////////
	/// Перки для штурмана
	/////////////////////////////////////////////////////////////
	perks.ShipSpeedUp.cost = 2;
	perks.ShipSpeedUp.OfficerType = "navigator";
	perks.ShipSpeedUp.condition.WindCatcher = true;

	perks.ShipTurnRateUp.cost = 2;
	perks.ShipTurnRateUp.OfficerType = "navigator";
	perks.ShipTurnRateUp.condition.SailsMan = true;

	perks.WindCatcher.cost = 2;
	perks.WindCatcher.OfficerType = "navigator";

	perks.SailsMan.cost = 1;
	perks.SailsMan.OfficerType = "navigator";

	perks.LoneWolf.cost = 2;
	perks.LoneWolf.OfficerType = "navigator";
	perks.LoneWolf.condition.SailsMan = true;

	perks.Turn180.cost = 2;
	perks.Turn180.condition.ShipTurnRateUp = true;
	perks.Turn180.TimeDelay = 240;
	perks.Turn180.TimeDuration = 60;
	perks.Turn180.OfficerType = "navigator";

	perks.Thrift.cost = 3;
	perks.Thrift.OfficerType = "navigator";
	perks.Thrift.condition.ShipSpeedUp = true;

	perks.SailingProfessional.cost = 4;
	perks.SailingProfessional.condition.Turn180 = true;
	perks.SailingProfessional.condition.Thrift = true;
	perks.SailingProfessional.OfficerType = "navigator";



	/////////////////////////////////////////////////////////////
	/// Перки для доктора
	/////////////////////////////////////////////////////////////
	perks.Doctor1.cost = 1;
	perks.Doctor1.OfficerType = "doctor";

	perks.Doctor2.cost = 2;
	perks.Doctor2.condition.Doctor1 = true;
	perks.Doctor2.OfficerType = "doctor";

	perks.BoardingPrepare.cost = 3;
	perks.BoardingPrepare.OfficerType = "doctor";
	perks.BoardingPrepare.condition.Doctor2 = true;

	perks.Cook.cost = 1;
	perks.Cook.OfficerType = "doctor";

	perks.ChiefCook.cost = 2;
	perks.ChiefCook.OfficerType = "doctor";
	perks.ChiefCook.condition.Cook = true;

	perks.Bartender.cost = 2;
	perks.Bartender.OfficerType = "doctor";
	perks.Bartender.condition.Cook = true;

	perks.Moonshiner.cost = 3;
	perks.Moonshiner.OfficerType = "doctor";
	perks.Moonshiner.condition.Bartender = true;
	perks.Moonshiner.condition.ChiefCook = true;

	perks.Quartermaster.cost = 4;
	perks.Quartermaster.OfficerType = "doctor";
	perks.Quartermaster.condition.Moonshiner = true;
	perks.Quartermaster.condition.BoardingPrepare = true;
	/////////////////////////////////////////////////////////////
	/// Перки для ГГ
	/////////////////////////////////////////////////////////////
	perks.SeaDogProfessional.cost = 3;
	perks.SeaDogProfessional.rank = 15;
	perks.SeaDogProfessional.PlayerOnly = true;
	SetArefModifier(perks, "SeaDogProfessional", M_SQUADRON_POWER, PERK_VALUE_SEA_DOG_PROFESSIONAL);

	perks.FlagPir.cost = 1; // лично ГГ
	perks.FlagPir.PlayerOnly = true;

	perks.FlagEng.cost = 1;
	perks.FlagEng.PlayerOnly = true;

	perks.FlagFra.cost = 1;
	perks.FlagFra.PlayerOnly = true;

	perks.FlagSpa.cost = 1;
	perks.FlagSpa.PlayerOnly = true;

	perks.FlagHol.cost = 1;
	perks.FlagHol.PlayerOnly = true;


	for (int i = 0; i < GetAttributesNum(perks); i++)
	{
		aref perk = GetAttributeN(perks, i);
		perk.BaseType = "ship";
		if (CheckAttribute(perk, "OfficerType")) SetAttribute(perk, "descriptors." + perk.OfficerType, true);
	}

	CopyAttributesSafe(list, perks);
}
