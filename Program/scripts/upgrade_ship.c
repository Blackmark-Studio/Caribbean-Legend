float GetShipModifierBonus(ref chr, string modifier)
{
	ref realShip = &RealShips[int(chr.Ship.Type)];
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
		float value = float(modifier.(sourceName));
		modifiers.(modifierName) = float(GetAttributeValue(modifier)) - value; // вычитаем эффект
		DeleteAttribute(modifier, sourceName);                               // убираем источник
	}
}

void UpgradeShipAudit(ref chr)
{
	ref realShip = GetRealShip(GetCharacterShipType(chr));
	UPGRD_UpgradeShipAudit(realShip);
}

bool CanUpgradeShip(ref chr, ref reason, string type)
{
	int nShipType = GetBaseShipType(chr);
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
	float value = GetAttributeFloat(realShip, "tuning.modifiers." + M_SHIP_RELOAD_SPEED + "." + sourceName);
	if (value == 0.15) return;

	value = fClamp(0, 0.15, value + 0.003);
	if (value == 0.15) Achievment_Set("ach_CL_201");
	UPGRD_SetShipModifier(realShip, M_GLOBAL_SPEED, value, sourceName);
	UPGRD_SetShipModifier(realShip, M_SHIP_TURNRATE, value, sourceName);
	UPGRD_SetShipModifier(realShip, M_SHIP_FIRE_DISTANCE, value, sourceName);
	UPGRD_SetShipModifier(realShip, M_SHIP_RELOAD_SPEED, value, sourceName);
}

void UpgradeShipSpeciality(ref chr)
{
	ref realShip = GetRealShip(GetCharacterShipType(chr));
	int speciality = int(realShip.Spec);
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

void UpgradeShipParameter(ref chr, string param)
{
	ref rShip = GetRealShip(int(chr.Ship.Type));
	aref arShip;
	makearef(arShip, chr.Ship);
	
	float fTuningMod = (GetShipSpec(rShip) == SHIP_SPEC_UNIVERSAL) ? 0.35 : 0.2;
	
	if (("Tuning." + param) in rShip)
		return;
	
	rShip.Tuning.(param) = true;
	switch(param)
	{
		case "SpeedRate":
			if ("Bonus_SpeedRate" in rShip)
				rShip.SpeedRate = (float(rShip.SpeedRate) - float(rShip.Bonus_SpeedRate)) * (1.0 + fTuningMod) + float(rShip.Bonus_SpeedRate);
			else
				rShip.SpeedRate = float(rShip.SpeedRate) * (1.0 + fTuningMod);
		break;
		case "TurnRate":
			if ("Bonus_TurnRate" in rShip)
				rShip.TurnRate = (float(rShip.TurnRate) - float(rShip.Bonus_TurnRate)) * (1.0 + fTuningMod) + float(rShip.Bonus_TurnRate);
			else
				rShip.TurnRate = float(rShip.TurnRate) * (1.0 + fTuningMod);
		break;
		case "HP":
			if ("Bonus_HP" in rShip && float(rShip.HP) > float(rShip.Bonus_HP))
				rShip.HP = (float(rShip.HP) - float(rShip.Bonus_HP)) * (1.0 + fTuningMod) + float(rShip.Bonus_HP);
			else
				rShip.HP = float(rShip.HP) * (1.0 + fTuningMod);
			ProcessHullRepair(chr, 100.0);
		break;
		case "Capacity":
			if ("Bonus_Capacity" in rShip)
				rShip.Capacity = (float(rShip.Capacity) - float(rShip.Bonus_Capacity)) * (1.0 + fTuningMod) + float(rShip.Bonus_Capacity);
			else
				rShip.Capacity = float(rShip.Capacity) * (1.0 + fTuningMod);
		break;
		case "MaxCrew":
			rShip.MaxCrew = int(int(rShip.MaxCrew) * (1.0 + fTuningMod));		
		break;
		case "MinCrew":
			rShip.MinCrew = int(int(rShip.MinCrew) * (1.0 - fTuningMod));		
			if (int(rShip.MinCrew) < 1)
				rShip.MinCrew = 1;
		break;
		case "Cannons":					
			if(GetPossibilityCannonsUpgrade(chr, true) > 0)
			{
				int i;
				string attr;								
				for (i = 0; i < int(rShip.cannonr); i++)
				{
					attr = "c" + i;										
					if (float(arShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0)
						arShip.Cannons.Borts.cannonr.damages.(attr) = 0.0;			
				}
				for (i = 0; i < int(rShip.cannonl); i++)
				{
					attr = "c" + i;										
					if (float(arShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0)
						arShip.Cannons.Borts.cannonl.damages.(attr) = 0.0;				
				}
				rShip.Cannons = rShip.CannonsQuantityMax;
				rShip.CannonsQuantity = rShip.Cannons;
				arShip.Cannons = rShip.Cannons;
				arShip.CannonDiff = 0;	
			}
		break;
	}
}

void UpgradeShipFull(ref _chr)
{
	UpgradeShipParameter(_chr, "SpeedRate");
	UpgradeShipParameter(_chr, "TurnRate");
	UpgradeShipParameter(_chr, "Rig");
	UpgradeShipParameter(_chr, "Capacity");
	UpgradeShipParameter(_chr, "HP");
	UpgradeShipParameter(_chr, "MaxCrew");
	UpgradeShipParameter(_chr, "MinCrew");
	UpgradeShipParameter(_chr, "Cannons");
	RealShips[int(_chr.ship.type)].Tuning.All = true;
}

// ugeen 03.06.09 - вероятность корабликов быть проапгрейженными на 1, 2 ...  все параметры
void Fantom_SetUpgrade(ref rFantom, string sFantomType)
{
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = int(rFantom.ship.type);
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
	
	shTo = &RealShips[int(rFantom.Ship.Type)];

	int  cannonQ       = int(shTo.CannonsQuantity);
	int	 cannonMaxQ;	
	int	 cannonMinQ    = int(shTo.CannonsQuantityMin);
	
	if(CheckAttribute(shTo,"CannonsQuantityMax")) 	cannonMaxQ = int(shTo.CannonsQuantityMax);
	else
	{		
		cannonMaxQ = int(shTo.CannonsQuantity);
		shTo.CannonsQuantityMax = int(shTo.CannonsQuantity);
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
	int iNation = int(rFantom.nation);
	
	switch (iNation)
	{
		case ENGLAND: // SW: SpeedRate & Rig
			if(rand(1) == 0) 
				UpgradeShipParameter(rFantom, "SpeedRate");
			else
				UpgradeShipParameter(rFantom, "Rig");
		break;
		
		case FRANCE: // TM: TurnRate&MinCrew
			if(rand(1) == 0) 
				UpgradeShipParameter(rFantom, "TurnRate");
			else
				UpgradeShipParameter(rFantom, "MinCrew");
		break;
		
		case SPAIN: // CC: Cannons&Capacity
			if(rand(1) == 0) 
			{
				if(GetPossibilityCannonsUpgrade(rFantom, true) > 0)
					UpgradeShipParameter(rFantom, "Cannons");
			}
			else
			{
				if(GetPossibilityCannonsUpgrade(rFantom, false) > 0)
					UpgradeShipParameter(rFantom, "Capacity");
			}
		break;
		
		case HOLLAND: // HP&MMaxCrew
			if(rand(1) == 0) 
				UpgradeShipParameter(rFantom, "HP");
			else
				UpgradeShipParameter(rFantom, "MaxCrew");
		break;
		
		case PIRATE:
			switch(rand(3))
			{
				case 0: 
					if(rand(1) == 0) 
						UpgradeShipParameter(rFantom, "SpeedRate");
					else
						UpgradeShipParameter(rFantom, "Rig");			
				break;
				case 1: 
					if(rand(1) == 0) 
						UpgradeShipParameter(rFantom, "TurnRate");
					else
						UpgradeShipParameter(rFantom, "MinCrew");
				break;
				case 2: 
					if(rand(1) == 0) 
					{
						if(GetPossibilityCannonsUpgrade(rFantom, true) > 0)
							UpgradeShipParameter(rFantom, "Cannons");
					}
					else
					{
						if(GetPossibilityCannonsUpgrade(rFantom, false) > 0)
							UpgradeShipParameter(rFantom, "Capacity");
					}				
				break;
				case 3: 
					if(rand(1) == 0) 
						UpgradeShipParameter(rFantom, "HP");
					else
						UpgradeShipParameter(rFantom, "MaxCrew");
				break;
			}
		break;
	}
}