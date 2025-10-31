
void ApplyMigration(ref migrationState)
{
	int i;
	bool bOk;
	ref   shTo;
	
	ref refShip;
	
	makeref(refShip,ShipsTypes[SHIP_PINK]);
	refShip.Capacity  = 1950;
	refShip.MaxCrew   = 86;
	refShip.OptCrew   = 69;
	refShip.MinCrew   = 17;	
	refShip.SpeedRate = 9.10;
	refShip.TurnRate  = 57.0;
	refShip.HP        = 1500;
	
	makeref(refShip,ShipsTypes[SHIP_LADYBETH]);
	refShip.Capacity   = 3300;
	refShip.MaxCrew    = 135;
	refShip.OptCrew    = 108;
	refShip.MinCrew    = 27;	
	refShip.SpeedRate  = 10.15;
	refShip.TurnRate   = 54.5;
	refShip.HP         = 2450;
	
	makeref(refShip,ShipsTypes[SHIP_MEMENTO]);
	refShip.Capacity        			= 4450;
	refShip.MaxCrew         			= 189;
	refShip.OptCrew         			= 151;
	refShip.MinCrew         			= 38;	
	refShip.SpeedRate       			= 10.95;
	refShip.TurnRate        			= 53.5;
	refShip.HP              			= 3600;

	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		bOk = false;
		if (!CheckAttribute(&RealShips[i], "BaseType")) continue;

		switch (sti(RealShips[i].BaseType))
		{
			case SHIP_PINK:
				bOk = true;
				RealShips[i].Capacity  = 1950;
				RealShips[i].MaxCrew   = 86;
				RealShips[i].OptCrew   = 69;
				RealShips[i].MinCrew   = 17;	
				RealShips[i].SpeedRate = 9.10;
				RealShips[i].TurnRate  = 57.0;
				RealShips[i].HP        = 1500;
			break;
				
			case SHIP_LADYBETH:
				bOk = true;
				RealShips[i].Capacity   = 3300;
				RealShips[i].MaxCrew    = 135;
				RealShips[i].OptCrew    = 108;
				RealShips[i].MinCrew    = 27;	
				RealShips[i].SpeedRate  = 10.15;
				RealShips[i].TurnRate   = 54.5;
				RealShips[i].HP         = 2450;
			break;
			
			case SHIP_MEMENTO: 
				bOk = true;
				RealShips[i].Capacity        			= 4450;
				RealShips[i].MaxCrew         			= 189;
				RealShips[i].OptCrew         			= 151;
				RealShips[i].MinCrew         			= 38;	
				RealShips[i].SpeedRate       			= 10.95;
				RealShips[i].TurnRate        			= 53.5;
				RealShips[i].HP              			= 3600;
			break;
		}
		if(bOk)
		{
			shTo = &RealShips[i];
			if(CheckAttribute(shTo, "Tuning.SpeedRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}    
			}
			if(CheckAttribute(shTo, "Tuning.TurnRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_TurnRate"))
				{
					shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
				}
				else
				{
					shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
				}
			}
			if(CheckAttribute(shTo, "Tuning.HP"))
			{
				if(!CheckAttribute(shTo, "Bonus_HP"))
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
				else
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
				}
			}
			if(CheckAttribute(shTo, "Tuning.Capacity"))
			{
				if(!CheckAttribute(shTo, "Bonus_Capacity"))
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}					
			}	
			if(CheckAttribute(shTo, "Tuning.MaxCrew"))
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);	
			}
			if(CheckAttribute(shTo, "Tuning.MinCrew"))
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
				if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
			}	
		}
    }
}
