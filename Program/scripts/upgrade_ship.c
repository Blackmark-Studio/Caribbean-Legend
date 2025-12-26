float GetShipModifierBonus(ref chr, string modifier)
{
	ref realShip = &RealShips[sti(chr.Ship.Type)];
	return GetAttributeFloat(realShip, "tuning.modifiers." + modifier);
}

void UPGRD_RemoveShipModifier(ref realShip, string sourceName)
{
	aref modifiers;
	makearef(modifiers, realShip.tuning.modifiers);

	for (int i = 0; i < GetAttributesNum(modifiers); i++)
	{
		aref modifier = GetAttributeN(modifiers, i);
		if (!CheckAttribute(modifier, sourceName)) continue;

		string modifierName = GetAttributeName(modifier);
		float value = stf(modifier.(sourceName));
		modifiers.(modifierName) = stf(GetAttributeValue(modifier)) - value; // вычитаем эффект
		DeleteAttribute(modifier, sourceName);                               // убираем источник
	}
}

void UpgradeShipAudit(ref chr)
{
	ref realShip = GetRealShip(GetCharacterShipType(chr));
	UPGRD_UpgradeShipAudit(realShip);
}

bool CanUpgradeShip(ref chr, string reason, string type)
{
	int nShipType = GetCharacterShipType(chr);
	if (nShipType == SHIP_NOTUSED)
	{
		reason = "EmptyShip";
		return false;
	}

	ref realShip = GetRealShip(GetCharacterShipType(chr));
	if (!IsFellowOurCrew(chr)) reason = "QuestCompanion";                                // не наш чел
	else if (CheckAttribute(realShip, "tuning." + type)) reason = "alreadyUpgraded";     // уже апгрейднут
	else if (nShipType == SHIP_CURSED_FDM || nShipType == SHIP_FDM) reason = "Kaleuche"; // Калеуче

	return reason == "";
}


void UPGRD_UpgradeShipAudit(ref realShip)
{
	string sourceName = "Audit";
	realShip.tuning.Audit = true;
	// realShip.tuning.Audit.offset = -10 + rand(20); // JOKERBACKLOG мб позже вкрутить случайный поворот/офсет
	// realShip.tuning.Audit.offset = rand(10);
	UPGRD_SetShipModifier(realShip, M_SHIP_CAPACITY, 0.10, sourceName);
	UPGRD_SetShipModifier(realShip, M_SHIP_SPEED, 0.05, sourceName);
	UPGRD_SetShipModifier(realShip, M_SHIP_TURNRATE, 0.10, sourceName);
	UPGRD_SetShipModifier(realShip, M_SHIP_MAXCREW, 0.05, sourceName);
}

void UpgradeAmsterdam(ref realShip)
{
	string sourceName = "trait_SP4";
	float value = GetAttributeFloat(realShip, "tuning.modifiers." + M_SHIP_SPEED + "." + sourceName);
	if (value == 15.0) return;

	value = fClamp(0, 15.0, value + 0.003);
	if (value == 15.0) Achievment_Set("ach_CL_201");
	UPGRD_SetShipModifier(realShip, M_SHIP_SPEED, value, sourceName);
	UPGRD_SetShipModifier(realShip, M_SHIP_TURNRATE, value, sourceName);
	UPGRD_SetShipModifier(realShip, M_SHIP_FIRE_DISTANCE, value, sourceName);
	UPGRD_SetShipModifier(realShip, M_SHIP_RELOAD_SPEED, value, sourceName);
}

void UpgradeShipSpeciality(ref chr)
{
	ref realShip = GetRealShip(GetCharacterShipType(chr));
	int speciality = sti(realShip.Spec);
	string sourceName = "SpecialityUpgrade";
	string modifier;
	float value;

	UPGRD_SetShipModifier(realShip, M_SQUADRON_POWER, 0.4, sourceName);
	realShip.tuning.SpecialityUpgrade = true;

	if (speciality == SHIP_SPEC_UNIVERSAL)
	{
		UPGRD_SetShipModifier(realShip, M_SHIP_CAPACITY, 0.1, sourceName);
		UPGRD_SetShipModifier(realShip, M_SHIP_MAXCREW, 0.1, sourceName);
		UPGRD_SetShipModifier(realShip, M_SHIP_SPEED, 0.06, sourceName);
		return;
	}
	
	switch (speciality)
	{
		case SHIP_SPEC_RAIDER:
			modifier = M_SHIP_CAPACITY;
			value = 0.2;
		break;
		case SHIP_SPEC_MERCHANT:
			modifier = M_SHIP_MAXCREW;
			value = 0.2;
		break;
		case SHIP_SPEC_WAR:
			modifier = M_SHIP_SPEED;
			value = 0.12;
		break;
	}

	UPGRD_SetShipModifier(realShip, modifier, value, sourceName);
}

void UPGRD_SetShipModifier(ref realShip, string modifier, ref value, string sourceName)
{
	aref modifiers;
	makearef(modifiers, realShip.tuning.modifiers);
	SetModifierFromSourceDirect(modifiers, modifier, value, sourceName);
}

void SetShipParameterByModifier(ref chr, string modifier, ref value, string sourceName)
{
	ref realShip = GetRealShip(GetCharacterShipType(chr));
	UPGRD_SetShipModifier(realShip, modifier, value, sourceName);
}

void UpgradeShipParameter(ref _chr, string _param)
{
	ref 	shTo;
	aref 	refShip;
	int 	iCaliber;
	int		iCannonDiff;
	int		i;
	string  attr; 
	
	shTo = &RealShips[sti(_chr.Ship.Type)];
	makearef(refShip, _chr.Ship);
	
	switch(_param)
	{
		case "SpeedRate":		
			if(!CheckAttribute(shTo, "Tuning.SpeedRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}		
				shTo.Tuning.SpeedRate = true;		
			}				
		break;		
		
		case "TurnRate":		
			if(!CheckAttribute(shTo, "Tuning.TurnRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_TurnRate"))
				{
					shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
				}
				else
				{
					shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
				}	
				shTo.Tuning.TurnRate = true;
			}				
		break;
		
		case "HP":		
			if(!CheckAttribute(shTo, "Tuning.HP"))
			{
				if(!CheckAttribute(shTo, "Bonus_HP"))
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
				else
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
				}	
				shTo.Tuning.HP = true;
				ProcessHullRepair(_chr, 100.0);
			}				
		break;
		
		case "WindAgainstSpeed":
			if(!CheckAttribute(shTo, "Tuning.WindAgainst"))
			{
				shTo.WindAgainstSpeed   = FloatToString(stf(shTo.WindAgainstSpeed) +  0.20 * stf(shTo.WindAgainstSpeed), 2);
				shTo.Tuning.WindAgainst = true;
			}				
		break;
		
		case "Capacity":		
			if(!CheckAttribute(shTo, "Tuning.Capacity"))
			{
				if(!CheckAttribute(shTo, "Bonus_Capacity"))
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}					
				shTo.Tuning.Capacity = true;
			}				
		break;
		
		case "MaxCrew":		
			if(!CheckAttribute(shTo, "Tuning.MaxCrew"))
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
				shTo.Tuning.MaxCrew = true;				
			}				
		break;
		
		case "MinCrew":
			if(!CheckAttribute(shTo, "Tuning.MinCrew"))
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
				if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
				shTo.Tuning.MinCrew = true;
			}	
		break;
		
		case "Cannons":					
			if(!CheckAttribute(shTo, "Tuning.Cannon") && GetPossibilityCannonsUpgrade(_chr, true) > 0)
			{
				iCannonDiff = sti(refShip.CannonDiff);
				iCannonDiff -= 1;
								
				for (i = 0; i < sti(shTo.cannonr); i++)
				{
					attr = "c" + i;										
					
					if(i < (sti(shTo.cannonr) - iCannonDiff) )	
					{
						if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
						{
							refShip.Cannons.Borts.cannonr.damages.(attr) = 0.0; 
						}	
					}					
				}	
				for (i = 0; i < sti(shTo.cannonl); i++)
				{
					attr = "c" + i;
					if(i < (sti(shTo.cannonl) - iCannonDiff) )	
					{
						if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
						{
							refShip.Cannons.Borts.cannonl.damages.(attr) = 0.0; 
						}	
					}										
				}	
				
				shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
				shTo.CannonsQuantity = sti(shTo.Cannons);
		
				refShip.Cannons = sti(shTo.Cannons);
				refShip.CannonDiff = iCannonDiff;
			
				shTo.Tuning.Cannon = true;		
			}
			else
			{
				if(!CheckAttribute(shTo, "Tuning.Cannon"))
				{
					shTo.Tuning.Cannon = true;
				}
			}
		break;
		
		// belamour только для методов с использованием GetAttributeName shTo.Tuning.XXX
		case "WindAgainst":
			if(!CheckAttribute(shTo, "Tuning.WindAgainst"))
			{
				shTo.WindAgainstSpeed   = FloatToString(stf(shTo.WindAgainstSpeed) +  0.20 * stf(shTo.WindAgainstSpeed), 2);
				shTo.Tuning.WindAgainst = true;
			}				
		break;
	}
}
// ugeen

void UpgradeShipFull(ref _chr)
{
	UpgradeShipParameter(_chr, "SpeedRate");
	UpgradeShipParameter(_chr, "TurnRate");
	UpgradeShipParameter(_chr, "WindAgainstSpeed");
	UpgradeShipParameter(_chr, "Capacity");
	UpgradeShipParameter(_chr, "HP");
	UpgradeShipParameter(_chr, "MaxCrew");
	UpgradeShipParameter(_chr, "MinCrew");
	UpgradeShipParameter(_chr, "Cannons");
	RealShips[sti(_chr.ship.type)].Tuning.All = true;
}


// ugeen 03.06.09 - вероятность корабликов быть проапгрейженными на 1, 2 ...  все параметры
void Fantom_SetUpgrade(ref rFantom, string sFantomType)
{
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix
	
	// ship class
	int iSClass = GetCharacterShipClass(rFantom);
	int i = rand(100);

	if (sFantomType != "pirate")
	{
		int specialUpgradesRand = TagRandom(99, rFantom.id);
		if (5 > specialUpgradesRand) UpgradeShipAudit(rFantom);
		if (3 > specialUpgradesRand) UpgradeShipSpeciality(rFantom);
	}

	switch (sFantomType)
	{
		case "pirate":   // апгрейдим параметр(ы)  шипа пиратских случаек
			if(i < (6 - iSClass)*4)  
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
		case "hunter":   // апгрейдим параметр(ы) шипа ДУ или ОЗГов
			if(i < ((6 - iSClass)*4 +10)) 
			{
				GenerateShipUpgradeParameters(rFantom);
			}			
		break;
		case "war":   // апгрейдим параметр(ы)  военных кораблей
			if(i < (6 - iSClass)*4)  
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
		case "trade":   // апгрейдим параметр(ы)  торгашей
			if(i < (6 - iSClass)*4 +10)  
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
	}
}

int GetPossibilityCannonsUpgrade(ref rFantom, bool isUpgrade)
{
	ref 	shTo;
	
	shTo = &RealShips[sti(rFantom.Ship.Type)];

	int  cannonQ       = sti(shTo.CannonsQuantity);		
	int	 cannonMaxQ;	
	int	 cannonMinQ    = sti(shTo.CannonsQuantityMin); 
	
	if(CheckAttribute(shTo,"CannonsQuantityMax")) 	cannonMaxQ = sti(shTo.CannonsQuantityMax); 
	else
	{		
		cannonMaxQ = sti(shTo.CannonsQuantity); 
		shTo.CannonsQuantityMax = sti(shTo.CannonsQuantity);
	}	
	
	//trace("cannonQ :" + cannonQ + " cannonMaxQ :" + cannonMaxQ + " cannonMinQ :" + cannonMinQ);
	
	if(isUpgrade) 
	{
		if( (cannonMaxQ - cannonQ) == 0) return 0;		// максимум орудий - апгрейд невозможен
	}	
	else	
	{
		if( (cannonQ - cannonMinQ) == 0) return 0;		// минимум орудий - даунгрейд невозможен
	}		
	return 1;
}

void GenerateShipUpgradeParameters(ref rFantom)
{
	int iNation = sti(rFantom.nation);
	
	switch (iNation)
	{
		case ENGLAND: // SW: SpeedRate&fWindAgainstSpeed
			if(rand(1) == 0) 
			{
				UpgradeShipParameter(rFantom, "SpeedRate");
			}	
			else
			{
				UpgradeShipParameter(rFantom, "WindAgainstSpeed");
			}
		break;
		
		case FRANCE: // TM: TurnRate&MinCrew
			if(rand(1) == 0) 
			{
				UpgradeShipParameter(rFantom, "TurnRate");
			}
			else
			{
				UpgradeShipParameter(rFantom, "MinCrew");
			}
		break;
		
		case SPAIN: // CC: Cannons&Capacity
			if(rand(1) == 0) 
			{
				if(GetPossibilityCannonsUpgrade(rFantom, true) > 0)
				{
					UpgradeShipParameter(rFantom, "Cannons");
				}	
			}
			else
			{
				if(GetPossibilityCannonsUpgrade(rFantom, false) > 0)
				{
					UpgradeShipParameter(rFantom, "Capacity");
				}	
			}
		break;
		
		case HOLLAND: // HP&MMaxCrew
			if(rand(1) == 0) 
			{
				UpgradeShipParameter(rFantom, "HP");
			}
			else
			{
				UpgradeShipParameter(rFantom, "MaxCrew");
			}
		break;
		
		case PIRATE:
			switch(rand(3))
			{
				case 0: 
					if(rand(1) == 0) 
					{
						UpgradeShipParameter(rFantom, "SpeedRate");
					}	
					else
					{
						UpgradeShipParameter(rFantom, "WindAgainstSpeed");
					}				
				break;
				case 1: 
					if(rand(1) == 0) 
					{
						UpgradeShipParameter(rFantom, "TurnRate");
					}
					else
					{
						UpgradeShipParameter(rFantom, "MinCrew");
					}					
				break;
				case 2: 
					if(rand(1) == 0) 
					{
						if(GetPossibilityCannonsUpgrade(rFantom, true) > 0)
						{
							UpgradeShipParameter(rFantom, "Cannons");
						}	
					}
					else
					{
						if(GetPossibilityCannonsUpgrade(rFantom, false) > 0)
						{
							UpgradeShipParameter(rFantom, "Capacity");
						}	
					}				
				break;
				case 3: 
					if(rand(1) == 0) 
					{
						UpgradeShipParameter(rFantom, "HP");
					}
					else
					{
						UpgradeShipParameter(rFantom, "MaxCrew");
					}				
				break;
			}
		break;
	}
}