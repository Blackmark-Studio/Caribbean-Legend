
#define REAL_SHIPS_QUANTITY 900

object	RealShips[REAL_SHIPS_QUANTITY];
#define SAILSCOLOR_PRICE_RATE    0.1 
#define SAILSGERALD_PRICE_RATE   0.2 

#define SAIL_COST_PERCENT 18
#define HULL_COST_PERCENT 25
#define HULL_REPAIR_EXP_MTP 8.0
#define SAIL_REPAIR_EXP_MTP 11.0

string GetShipDescr(ref refRealShip)
{
	ref refShip;
	makeref(refShip, ShipsTypes[int(refRealShip.basetype)]);
	return GetConvertStr(refRealShip.BaseName, "ShipsDescribe.txt");
}

ref GetRealShip(int iType) 
{ 
	if(iType >= REAL_SHIPS_QUANTITY)
	{
		trace ("--- Wrong Ship Index. iType is " + iType);
		Log_TestInfo("--- Wrong Ship Index. iType is " + iType);
		return &ShipsTypes[SHIP_TYPES_QUANTITY + 1]; // для отлова
	}
	return &RealShips[iType]; 
}

//генерация кораблей в море
int GenerateShip(int iBaseType, bool isLock)
{
	int iShip = CreateBaseShip(iBaseType);

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}
	
	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(int(rRealShip.BaseType));
    // boal 26/05/06 изменим
	if (!CheckAttribute(rRealShip, "maxHulls") || int(rRealShip.maxHulls) <= 1) {
		rRealShip.ship.upgrades.hull = 1;
		trace("New ship " + rBaseShip.Name + " has no hull, default is set to 1");
	} else {
		rRealShip.ship.upgrades.hull = 1 + rand(int(rRealShip.maxHulls) - 1);
		trace("New ship " + rBaseShip.Name + " has hull " + rRealShip.ship.upgrades.hull);
	}
    //rRealShip.ship.upgrades.hull  = 1 + rand(2);  //признак корабля теперь
	rRealShip.ship.upgrades.sails = 1 + rand(2);  // только визуальная разница
	
	if (!CheckAttribute(rRealShip, "isFort"))
	{
	    int iCaliber = int(rRealShip.MaxCaliber);
		//string sCannonType = GetCannonType(rRealShip.Cannon);
	    if (int(rRealShip.Class) != 7)
	    {  // чтоб не было баркаса с 16ф				
		    switch(iCaliber)
		    {
                case 3:  iCaliber = 0;  break;
                case 6:  iCaliber = 1;  break;
                case 8:  iCaliber = 2;  break;
                case 12: iCaliber = 3;  break;
                case 16: iCaliber = 4;  break;
                case 18: iCaliber = 5;  break;
                case 20: iCaliber = 6;  break;
                case 24: iCaliber = 7;  break;
                case 32: iCaliber = 8;  break;
                case 36: iCaliber = 9;  break;
                case 42: iCaliber = 10; break;
		    }
		    iCaliber = iCaliber - rand(1); // фикс перебора калибра орудий
		    if (iCaliber < 0) iCaliber = 0;
			if (int(rRealShip.Class) == 1)
		    {
		    	if (iCaliber > 10) iCaliber = 10;
		    }
		    else
		    {
		    	if (iCaliber > 9) iCaliber = 9;
		    }
		    switch(iCaliber)
		    {			
                case 0:  iCaliber = 3;  break;
                case 1:  iCaliber = 6;  break;
                case 2:  iCaliber = 8;  break;
                case 3:  iCaliber = 12; break;
                case 4:  iCaliber = 16; break;
                case 5:  iCaliber = 18; break;
                case 6:  iCaliber = 20; break;
                case 7:  iCaliber = 24; break;
                case 8:  iCaliber = 32; break;
                case 9:  iCaliber = 36; break;
                case 10: iCaliber = 42; break;
		    }
		    rRealShip.MaxCaliber = iCaliber;						
	    }
		//генерация статов кораблей, на море баланс чуть смещен в плюс, чтобы была мотивация искать корабли именно там.
	    float fTemp = float(rRealShip.SpeedRate) * (0.93 + frandSmall(0.16));
		rRealShip.SpeedRate = fTemp;
		fTemp = float(rRealShip.TurnRate) * (0.93 + frandSmall(0.18));
		rRealShip.TurnRate = fTemp;
		fTemp = float(rRealShip.HP) * (0.89 + frandSmall(0.24));
		rRealShip.HP = int(fTemp);
	}
    rRealShip.Capacity        = int(rRealShip.Capacity) + rand(int(int(rRealShip.Capacity)/4)) - int(int(rRealShip.Capacity)/8);
    rRealShip.OptCrew         = int(int(rRealShip.OptCrew) + rand(int(int(rRealShip.OptCrew)/3)) - int(int(rRealShip.OptCrew)/6));
    rRealShip.MaxCrew         = int(int(rRealShip.OptCrew) * 1.25 + 0.5);  // 25% перегруза
    rRealShip.MinCrew         = int(int(rRealShip.MinCrew) + rand(int(int(rRealShip.MinCrew)/3)) - int(int(rRealShip.MinCrew)/6));

	rRealShip.Weight		  = int(rRealShip.Weight) + rand(int(rRealShip.Weight)/20) - rand(int(rRealShip.Weight)/20);
	
	// to_do del -->
	rRealShip.BoardingCrew    = 0;
	rRealShip.GunnerCrew      = 0;
	rRealShip.CannonerCrew    = 0;
	rRealShip.SailorCrew      = int(rRealShip.OptCrew);
    // to_do del <--
    
	int iDiffWeight			= int(rRealShip.Weight) - int(rBaseShip.Weight);
	int iDiffCapacity		= int(rRealShip.Capacity) - int(rBaseShip.Capacity);
	int iDiffMaxCrew		= int(rRealShip.MaxCrew) - int(rBaseShip.MaxCrew);
	int iDiffMinCrew		= int(rRealShip.MinCrew) - int(rBaseShip.MinCrew);
	float fDiffSpeedRate	= float(rRealShip.SpeedRate) - float(rBaseShip.SpeedRate);
	int iDiffTurnRate		= int(rRealShip.TurnRate) - int(rBaseShip.TurnRate);
	int iDiffHP	    		= int(rRealShip.HP) - int(rBaseShip.HP);

	rRealShip.Price	= (iDiffWeight + iDiffCapacity + iDiffMaxCrew*2 + iDiffMinCrew + fDiffSpeedRate*2 + iDiffTurnRate*2 + iDiffHP)*5 + int(rRealShip.Price);

	if (int(rRealShip.Price) <= 0) rRealShip.Price = 100;
	
	rRealShip.Stolen = isLock;  // ворованность

	return iShip;
}

//генерация кораблей на верфи
int GenerateShipExt(int iBaseType, bool isLock, ref chr)
{
	string  attr, sCity;
	int 	i;
	aref 	refShip;
	float	Кdckyrd = 1.0;
	bool	isShipyard = false; 

	int iShip = CreateBaseShip(iBaseType);

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}

	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(int(rRealShip.BaseType));
	// boal 26/05/06 изменим
	// rRealShip.ship.upgrades.hull  = 1 + rand(2);  //признак корабля теперь
	if (!CheckAttribute(rRealShip, "maxHulls") || int(rRealShip.maxHulls) <= 1) {
		rRealShip.ship.upgrades.hull = 1;
		trace("New ship " + rBaseShip.Name + " has no hull, default is set to 1");
	} else {
		rRealShip.ship.upgrades.hull = 1 + rand(int(rRealShip.maxHulls) - 1);
		trace("New ship " + rBaseShip.Name + " has hull " + rRealShip.ship.upgrades.hull);
	rRealShip.ship.upgrades.sails = 1 + rand(4);  // только визуальная разница
	}
	rRealShip.Bonus_Capacity 	= 0;
	rRealShip.Bonus_HP			= 0;
	rRealShip.Bonus_SpeedRate   = 0.0;
	rRealShip.Bonus_TurnRate	= 0.0;
	
	// ugeen --> если кораблик генерится на верфи, разброс статов более узкий
	if (CheckAttribute(chr, "City")) 
	{
		sCity = chr.City; 
		if(CheckCharacterID(chr, sCity + "_shipyarder"))
		{
			Кdckyrd 	= 0.8;
			isShipyard 	= true;
		}
	}	
	// ugeen

	if (!CheckAttribute(rRealShip, "isFort"))
	{
		int iCaliber = int(rRealShip.MaxCaliber);
		if (int(rRealShip.Class) != 7 && !CheckAttribute(rRealShip, "QuestShip"))
		{  // чтоб не было баркаса с 16ф
			switch(iCaliber)
			{
                case 3:  iCaliber = 0;  break;
                case 6:  iCaliber = 1;  break;
                case 8:  iCaliber = 2;  break;
                case 12: iCaliber = 3;  break;
                case 16: iCaliber = 4;  break;
                case 18: iCaliber = 5;  break;
                case 20: iCaliber = 6;  break;
                case 24: iCaliber = 7;  break;
                case 32: iCaliber = 8;  break;
                case 36: iCaliber = 9;  break;
                case 42: iCaliber = 10; break;
			}
			//iCaliber = iCaliber + rand(2) - 1;
			iCaliber = iCaliber - rand(1); //Jason: согласно новой системе орудий калибр должен быть постоянен, но пока поставим рандом на единицу меньше, а больше - нельзя по определению, на рез. тестов решим, фиксировать или рандомить
			if (iCaliber < 0) iCaliber = 0;
			if (int(rRealShip.Class) == 1)
			{			
				if (iCaliber > 10) iCaliber = 10;
			}
			else
			{
				if (iCaliber > 9) iCaliber = 9;
			}
			switch(iCaliber)
			{
                case 0:  iCaliber = 3;  break;
                case 1:  iCaliber = 6;  break;
                case 2:  iCaliber = 8;  break;
                case 3:  iCaliber = 12; break;
                case 4:  iCaliber = 16; break;
                case 5:  iCaliber = 18; break;
                case 6:  iCaliber = 20; break;
                case 7:  iCaliber = 24; break;
                case 8:  iCaliber = 32; break;
                case 9:  iCaliber = 36; break;
                case 10: iCaliber = 42; break;
			}
			rRealShip.MaxCaliber = iCaliber;
		}

		int   iCannonDiff 		= rand(int(int(rRealShip.rcannon) * 10 / 100 + 1));
		int   iDiffClass  		= 6 - int(int(rRealShip.Class)/2);
		
		if(CheckAttribute(rRealShip, "QuestShip") || isShipyard) iCannonDiff = 0;

		// ---> собственно сам рэндом стволов
		makearef(refShip, chr.Ship);
		ResetShipCannonsDamages(chr);
		
		// куда-нить запишем максимально возможное и минимальное кол-во орудий (потом нужно будет, если захотим проапгрейдиться на этот счёт)		
		rRealShip.CannonsQuantityMax	= int(rRealShip.CannonsQuantity);
		refShip.CannonsQuantityMax 		= int(rRealShip.CannonsQuantity);
		refShip.CannonsQuantityMin 		= int(rRealShip.CannonsQuantityMin);
		refShip.CannonDiff 				= iCannonDiff;
				
		for (i = 0; i < int(rRealShip.cannonr); i++)
		{
			attr = "c" + i;
			refShip.Cannons.Borts.cannonr.damages.(attr) = 0.0; 				
			if(iCannonDiff > 0 && i >= int(rRealShip.cannonr) - iCannonDiff)
			{
				refShip.Cannons.Borts.cannonr.damages.(attr) = 2.0; 
			}
		}	
		for (i = 0; i < int(rRealShip.cannonl); i++)
		{
			attr = "c" + i;
			refShip.Cannons.Borts.cannonl.damages.(attr) = 0.0; 
			if(iCannonDiff > 0 && i >= int(rRealShip.cannonl) - iCannonDiff)
			{
				refShip.Cannons.Borts.cannonl.damages.(attr) = 2.0; 
			}
		}	
		for (i = 0; i < int(rRealShip.cannonf); i++)
		{
			attr = "c" + i;			
			refShip.Cannons.borts.cannonf.damages.(attr) = 0.0; 
		}		
		for (i = 0; i < int(rRealShip.cannonb); i++)
		{
			attr = "c" + i;
			refShip.Cannons.borts.cannonb.damages.(attr) = 0.0; 
		}			
			
		rRealShip.Cannons 				= int(refShip.CannonsQuantityMax) - iCannonDiff * 2;
		rRealShip.CannonsQuantity 		= int(rRealShip.Cannons);
		rRealShip.CannonDiff 			= iCannonDiff;
		refShip.Cannons 				= int(rRealShip.Cannons);
		// <--- собственно сам рэндом стволов

		if(!CheckAttribute(rRealShip, "QuestShip"))
		{	
			rRealShip.Bonus_Capacity 	= int((int(rRealShip.Capacity)*iCannonDiff)/(15 * iDiffClass));
			rRealShip.Bonus_HP 			= int((int(rRealShip.HP)*iCannonDiff)/(15 * iDiffClass));
			rRealShip.Bonus_SpeedRate   = (float(rRealShip.SpeedRate)*iCannonDiff)/(15 * iDiffClass);
			rRealShip.Bonus_TurnRate    = (float(rRealShip.TurnRate)*iCannonDiff)/(15 * iDiffClass);
		
			rRealShip.SpeedRate	   		= float(rRealShip.SpeedRate) + Кdckyrd * (frandSmall(float(rRealShip.SpeedRate) / 5.0) - float(rRealShip.SpeedRate) / 10.0);
			rRealShip.TurnRate         	= float(rRealShip.TurnRate) + Кdckyrd * (frandSmall(float(rRealShip.TurnRate) / 5.0) - float(rRealShip.TurnRate) / 10.0);
			rRealShip.HP               	= int(rRealShip.HP) + int(Кdckyrd * (rand(int(int(rRealShip.HP)/5)) - int(int(rRealShip.HP)/10)));
		}	
	}
	
	if(!CheckAttribute(rRealShip, "QuestShip"))
	{
		rRealShip.Capacity        = int(rRealShip.Capacity) + int(Кdckyrd * (rand(int(int(rRealShip.Capacity)/4)) - int(int(rRealShip.Capacity)/8)));
		rRealShip.OptCrew         = int(int(rRealShip.OptCrew) + Кdckyrd * (rand(int(int(rRealShip.OptCrew)/3)) - int(int(rRealShip.OptCrew)/6)));
		rRealShip.MaxCrew         = int(int(rRealShip.OptCrew) * 1.25 + 0.5);  // 25% перегруза
		rRealShip.MinCrew         = int(int(rRealShip.MinCrew) + Кdckyrd * (rand(int(int(rRealShip.MinCrew)/3)) - int(int(rRealShip.MinCrew)/6)));
		rRealShip.Weight		  = int(rRealShip.Weight) + int(Кdckyrd * (rand(int(rRealShip.Weight)/20) - rand(int(rRealShip.Weight)/20)));
	}	

	// to_do del -->
	rRealShip.BoardingCrew    = 0;
	rRealShip.GunnerCrew      = 0;
	rRealShip.CannonerCrew    = 0;
	rRealShip.SailorCrew      = int(rRealShip.OptCrew);
	// to_do del <--

	if(!CheckAttribute(rRealShip, "QuestShip"))
	{
		rRealShip.Capacity  = int(rRealShip.Capacity) + int(rRealShip.Bonus_Capacity);
		rRealShip.HP        = int(rRealShip.HP) + int(rRealShip.Bonus_HP);
		rRealShip.SpeedRate = float(rRealShip.SpeedRate) + float(rRealShip.Bonus_SpeedRate);
		rRealShip.TurnRate  = float(rRealShip.TurnRate) + float(rRealShip.Bonus_TurnRate);
	}
	
	if(int(rRealShip.CannonsQuantityMin) > 0) // баркасы не учитываем
	{
		if(int(rRealShip.CannonsQuantityMax) == int(rRealShip.CannonsQuantity)) // это в основном квестовые корабли, но мало ли .....
		{
			float fTuningMod = (GetShipSpec(rRealShip) == SHIP_SPEC_UNIVERSAL) ? 0.35 : 0.2;
			if ("Bonus_Capacity" in rRealShip)
				rRealShip.Capacity = (float(rRealShip.Capacity) - float(rRealShip.Bonus_Capacity)) * (1.0 + fTuningMod) + float(rRealShip.Bonus_Capacity);
			else
				rRealShip.Capacity = float(rRealShip.Capacity) * (1.0 + fTuningMod);
			rRealShip.Tuning.Capacity = true;
		}
	}

	int 	iDiffWeight		= int(rRealShip.Weight) 	- int(rBaseShip.Weight);
	int 	iDiffCapacity	= int(rRealShip.Capacity) 	- int(rBaseShip.Capacity);
	int 	iDiffMaxCrew	= int(rRealShip.MaxCrew) 	- int(rBaseShip.MaxCrew);
	int 	iDiffMinCrew	= int(rRealShip.MinCrew) 	- int(rBaseShip.MinCrew);
	float 	fDiffSpeedRate	= float(rRealShip.SpeedRate) 	- float(rBaseShip.SpeedRate);
	int 	iDiffTurnRate	= int(rRealShip.TurnRate) 	- int(rBaseShip.TurnRate);
	int 	iDiffHP	    	= int(rRealShip.HP) 		- int(rBaseShip.HP);

	rRealShip.Price	= (iDiffWeight + iDiffCapacity + iDiffMaxCrew*2 + iDiffMinCrew + fDiffSpeedRate*2 + iDiffTurnRate*2 + iDiffHP)*5 + int(rRealShip.Price);

	if (int(rRealShip.Price) <= 0) rRealShip.Price = 100;
	
	rRealShip.Stolen = isLock;  // ворованность

	if (iBaseType == SHIP_MAYFANG) UPGRD_UpgradeShipAudit(rRealShip);

	return iShip;
}
// -> ugeen

// belamour установить максимальные характеристики кораблю
void SetMaxShipStats(ref chr)
{
	int iShipType = GetCharacterShipType(chr);
	if(iShipType == SHIP_NOTUSED) return;
	
	ref rRealShip = GetRealShip(iShipType);
	ref rBaseShip = GetShipByType(int(rRealShip.BaseType));
	if(CheckAttribute(rRealShip, "QuestShip")) return;
	
	int iCannonDiff = int(int(rBaseShip.rcannon) * 10 / 100 + 1);
	int iClass = int(rRealShip.Class);
	int iDiffClass  = 6 - int(iClass/2);
	
	if (iClass > 6) iCannonDiff = 0;
	
	rRealShip.Bonus_Capacity 	= int((int(rBaseShip.Capacity)*iCannonDiff)/(15 * iDiffClass));
	rRealShip.Bonus_HP 			= int((int(rBaseShip.HP)*iCannonDiff)/(15 * iDiffClass));
	rRealShip.Bonus_SpeedRate   = (float(rBaseShip.SpeedRate)*iCannonDiff)/(15 * iDiffClass);
	rRealShip.Bonus_TurnRate    = (float(rBaseShip.TurnRate)*iCannonDiff)/(15 * iDiffClass);
	
	rRealShip.SpeedRate	   		= float(rBaseShip.SpeedRate) + (float(rBaseShip.SpeedRate) / 10.0);
	rRealShip.TurnRate         	= float(rBaseShip.TurnRate) + (float(rBaseShip.TurnRate) / 10.0);
	rRealShip.HP               	= int(rBaseShip.HP) + int(int(rBaseShip.HP)/10);
	rRealShip.Capacity        	= int(rBaseShip.Capacity) + int(int(rBaseShip.Capacity)/8);
	rRealShip.OptCrew         	= int(rBaseShip.OptCrew) + int(int(rBaseShip.OptCrew)/6);
	rRealShip.MaxCrew         	= int(int(rBaseShip.OptCrew) * 1.25 + 0.5);  // 25% перегруза
	rRealShip.MinCrew         	= int(rBaseShip.MinCrew) + int(int(rBaseShip.MinCrew)/6);
	
	rRealShip.Capacity  = int(rRealShip.Capacity) + int(rRealShip.Bonus_Capacity);
	rRealShip.HP        = int(rRealShip.HP) + int(rRealShip.Bonus_HP);
	rRealShip.SpeedRate = float(rRealShip.SpeedRate) + float(rRealShip.Bonus_SpeedRate);
	rRealShip.TurnRate  = float(rRealShip.TurnRate) + float(rRealShip.Bonus_TurnRate);
}

//Jason, генерация корабля с заданными статами; кроме числа орудий - всегда макс.
int GenerateShipHand(ref chr, int iType, int cc, int cp, int cr, int hp, int pr, float sr, float tr)
{
	aref 	refShip;

	int iShip = CreateBaseShip(iType);

	if (iShip == -1) return SHIP_NOTUSED;

	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(int(rRealShip.BaseType));
    rRealShip.ship.upgrades.hull  = 1;//всегда первый
	rRealShip.ship.upgrades.sails = 3;// всегда хлопок
	
	rRealShip.MaxCaliber = cc;	
	rRealShip.SpeedRate = sr;
	rRealShip.TurnRate = tr;
	rRealShip.HP = hp;
    rRealShip.Capacity = cp;
    rRealShip.OptCrew = cr;
    rRealShip.MaxCrew = int(int(rRealShip.OptCrew) * 1.25 + 0.5);
    rRealShip.MinCrew = int(int(rRealShip.MinCrew) + int(int(rRealShip.MinCrew)/4)) - int(int(rRealShip.MinCrew)/7);
	rRealShip.Weight = int(rRealShip.Weight) + int(rRealShip.Weight)/20 - int(rRealShip.Weight)/20;
	rRealShip.Price	= pr;
	
	makearef(refShip, chr.Ship);
	ResetShipCannonsDamages(chr);
	rRealShip.CannonsQuantityMax	= int(rRealShip.CannonsQuantity);
	
	refShip.CannonsQuantityMax 		= int(rRealShip.CannonsQuantity);
	refShip.CannonsQuantityMin 		= int(rRealShip.CannonsQuantityMin);
	refShip.CannonDiff 				= 0;
	
	rRealShip.Cannons 				= int(refShip.CannonsQuantityMax);
	rRealShip.CannonsQuantity 		= int(rRealShip.Cannons);
	refShip.Cannons 				= int(rRealShip.Cannons);
	
	// to_do del -->
	rRealShip.BoardingCrew    = 0;
	rRealShip.GunnerCrew      = 0;
	rRealShip.CannonerCrew    = 0;
	rRealShip.SailorCrew      = int(rRealShip.OptCrew);
    // to_do del <--

	if (int(rRealShip.Price) <= 0) rRealShip.Price = 100;
	
	rRealShip.Stolen = false;

	return iShip;
}

int CreateBaseShip(int iBaseType)
{
	int iShip = FindFirstEmptyShip();

	if(iShip == -1)
	{
        trace("Can not find empty ship slot");
		return SHIP_NOTUSED;
	}

	ref rBaseShip = GetShipByType(iBaseType);
	ref rRealShip = GetRealShip(iShip);
	DeleteAttribute(rRealShip, "");
	CopyAttributes(rRealShip, rBaseShip);
    rRealShip.index = iShip;
    rRealShip.BaseType = iBaseType;
    if (!CheckAttribute(rRealShip, "ship.upgrades.hull")) // если задано в базе, то квестовый тип, не перебивать
    {
    	rRealShip.ship.upgrades.hull = 1;  //признак корабля теперь
    }
	rRealShip.ship.upgrades.sails = 1;
	
    rRealShip.BaseName = rRealShip.name; // запоминалка для нужд, тк далее идёт "странное"
	if (rRealShip.name != "Fort" && rRealShip.name != "Boat") // не знаю зачем :(
	{
		rRealShip.name = rRealShip.name + "1"; // без этого вылет, но почему!!!!!!!!!!!!!!
		// выяснил - папка с моделью имеет на конце 1, вот и ответ
	}
    rRealShip.Stolen = 0;  // ворованность - честный
    
	if (iArcadeSails == 0) // момент инерции ниже для тактики
	{
	    rRealShip.InertiaAccelerationY = float(rRealShip.InertiaAccelerationY) / 2.0;
	}
	
	SetShipTraits(rRealShip);
	
	// belamour пропишем сразу поворотные лафеты
	if(CheckAttribute(rRealShip, "Traits") && rRealShip.Traits == "trait11")
	{
		rRealShip.Cannons.Borts.cannonl.FireZone = float(rRealShip.Cannons.Borts.cannonl.FireZone) + Degree2Radian(7.0);
		rRealShip.Cannons.Borts.cannonr.FireZone = float(rRealShip.Cannons.Borts.cannonr.FireZone) + Degree2Radian(7.0);
		rRealShip.Cannons.Borts.cannonf.FireZone = float(rRealShip.Cannons.Borts.cannonf.FireZone) + Degree2Radian(7.0);
		rRealShip.Cannons.Borts.cannonb.FireZone = float(rRealShip.Cannons.Borts.cannonb.FireZone) + Degree2Radian(7.0);
	}
    
	return iShip;
}

void ResetShipCannonsDamages(ref refCharacter)
{
	aref refShip;
	
	makearef(refShip, refCharacter.Ship);
	refShip.Cannons.Borts = "";		
	if (CheckAttribute(refShip, "Cannons.Borts.cannonf.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonf.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.cannonb.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonb.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.cannonl.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonl.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.cannonr.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonr.damages"); }
}

void SetShipCannonsDamagesNull(ref refCharacter)
{
	int i;
	aref refShip;
	string attr;
	
	makearef(refShip, refCharacter.Ship);
	int nShipType = int(refCharacter.Ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + refCharacter.id + " have invalid ship!");
		return;
	}
	ref rRealShip = GetRealShip(nShipType);
	
	refShip.CannonsQuantityMax 	= int(rRealShip.CannonsQuantity);
	refShip.CannonsQuantityMin 	= int(rRealShip.CannonsQuantityMin);
	refShip.CannonDiff 			= 0;
				
	for (i = 0; i < int(rRealShip.cannonr); i++)
	{
		attr = "c" + i;
		refShip.Cannons.Borts.cannonr.damages.(attr) = 0.0; 				
	}	
	for (i = 0; i < int(rRealShip.cannonl); i++)
	{
		attr = "c" + i;
		refShip.Cannons.Borts.cannonl.damages.(attr) = 0.0; 			
	}	
	for (i = 0; i < int(rRealShip.cannonf); i++)
	{
		attr = "c" + i;			
		refShip.Cannons.borts.cannonf.damages.(attr) = 0.0; 
	}		
	for (i = 0; i < int(rRealShip.cannonb); i++)
	{
		attr = "c" + i;
		refShip.Cannons.borts.cannonb.damages.(attr) = 0.0; 
	}			
			

	rRealShip.Cannons 			= int(refShip.CannonsQuantityMax);
	rRealShip.CannonsQuantity 	= int(rRealShip.Cannons);
	refShip.Cannons 			= int(rRealShip.Cannons);
}

// Генерация корабля для верфи
int GenerateStoreShip(int iBaseType)
{
	int iShip = GenerateShip(iBaseType, false); // честный

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}
	
	ref rRealShip = GetRealShip(iShip);
    rRealShip.StoreShip = true;  // корабль на верфи, трется отдельным методом
    
	return iShip;	
}

// -> ugeen 25.01.09 -> для верфи
int GenerateStoreShipExt(int iBaseType, ref chr)
{
	int iShip = GenerateShipExt(iBaseType, false, chr); // честный

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}
	
	ref rRealShip = GetRealShip(iShip);
	rRealShip.StoreShip = true;  // корабль на верфи, трется отдельным методом
    
	return iShip;	
}
// <- ugeen

// переработка метода 26.05.06 boal
// идея: трем все корабли, где нет НПС-владельца, все галки пофиг
void EmptyAllFantomShips()
{
	int  i;
	ref  chr;
	// оптимальный код - два прохода, а не вложенный цикл. В начале всем сносим флаг удаляемости, потом проставляем, где есть НПС
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        DeleteAttribute(&RealShips[i], "lock");
	}
	// лодку ставим, тк он имеет индекс НПС за пределами MAX_CHARACTERS
	//RealShips[int(Characters[BOAT_CHARACTER].ship.type)].lock = true;
	// теперь НПС-кэпы
	for (i = 0; i < MAX_CHARACTERS; i++)
	{
        chr = &Characters[i];
        if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED)
        {
            RealShips[int(chr.ship.type)].lock = true;
        }
        // очистка для верфи
		if (CheckAttribute(chr, "shipyard"))
		{
		    FreeShipFromShipyard(chr);
		}
	}
	// теперь сборка мусора
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        if (!CheckAttribute(&RealShips[i], "lock") && !CheckAttribute(&RealShips[i], "StoreShip"))  // на верфи корабли не трем
        {
			DeleteAttribute(&RealShips[i], "");
		}
	}
}

int GetRealShipsCount()
{ // метод для отладки
	int result = 0;

	for (int i= 0; i< REAL_SHIPS_QUANTITY; i++)
	{
		if (checkAttribute(&RealShips[i], "name"))
		{
			result++;
		}
	}

	return result;
}

// поиск пустого слота
int FindFirstEmptyShip()
{
	for(int i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if(!checkAttribute(&RealShips[i], "name"))
		{
			return i;
		}
	}

	return -1;
}

float FindShipSpeed(ref refCharacter)
{
	if(!CheckAttribute(refCharacter, "Ship.type"))
	{
		trace("Character " + refCharacter.id + " have no ship!");
		return 0.0;
	}
	int nShipType = int(refCharacter.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + refCharacter.id + " have invalid ship!");
		return 1.0;
	}
	ref rShip = GetRealShip(nShipType);
	
	float fMaxSpeedZ = float(rShip.SpeedRate);  // базовая скорость
	float fShipHp = float(refCharacter.ship.hp);
	float fShipMaxHp = float(rShip.HP);
	float fSpeedFromHp = fShipHp/fShipMaxHp;
	fSpeedFromHp = 0.8 + fSpeedFromHp*0.3;

	if(fSpeedFromHp > 1.0) // некий запас перед снижением скорости
	{
		fSpeedFromHp = 1.0;
	}
			
	fMaxSpeedZ = fMaxSpeedZ * AIShip_isPerksUse(CheckCharacterPerk(refCharacter, "MapMaker"), 1.0, 1.05) * isEquippedArtefactUse(refCharacter, "obereg_9", 1.0, 1.10);
	//if(IsEquipCharacterByItem(refCharacter, "sextant2")) fMaxSpeedZ *= 1.05; // belamour legendary edition Секстант Алексуса
	if(IsCharacterEquippedArtefact(refCharacter, "talisman19")) fMaxSpeedZ *= 1.0 + Bring2Range(0.0, 0.375, 0.0, 50.0, (100.0 - GetHullPercent(refCharacter)) / 2.0);
	
	if(CheckAttribute(refCharacter, "cheats.ArcadeSailing")) return fMaxSpeedZ*SpeedBySkill(refCharacter);
	
	float fSailsDamage = float(refCharacter.ship.sp);
	fSailsDamage += GetFloatByCondition(CheckCharacterPerk(refCharacter, "Thrift"), 0.0, PERK_VALUE_THRIFT);

	//float	fTRFromSailDamage = Bring2Range(0.1, 1.0, 0.1, 100.0, fSailsDamage); //0.3
	float	fTRFromSailDamage = CalculateSpeedDebuff_SP(fSailsDamage);
	// if(refCharacter.id == "blaze") log_testinfo("fTRFromSailDamage "+FloatToString(fTRFromSailDamage,2));

	float fTRFromShipState = fSpeedFromHp * fTRFromSailDamage;
	
	float	fLoad = Clampf(float(refCharacter.Ship.Cargo.Load) / float(rShip.Capacity));
	float	fTRFromWeight = Clampf(1.03 - float(rShip.SpeedDependWeight) * fLoad * GetFloatByCondition(HasShipTrait(refCharacter, "trait02"), 1.0, 0.85) * GetWeightMtpWithIntendant(refCharacter));
	float   fTRFromSkill = SpeedBySkill(refCharacter);

	float fTRFomBreaches = 1;
	if (CheckAttribute(refCharacter, "Ship.breachImmersion")) fTRFomBreaches = GetBreachesMtp(float(refCharacter.Ship.breachImmersion));

	// от команды
	float fCrewMax = float(rShip.MaxCrew);
	float fCrewOpt = float(rShip.OptCrew);
	float fCrewCur = float(refCharacter.Ship.Crew.Quantity);
	if (fCrewCur > fCrewMax)
	{
		fCrewCur = fCrewMax;
	}
	float  fTRFromPeople;
	fTRFromPeople = 0.85 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.15;
	if (fTRFromPeople > 1) fTRFromPeople = 1;
	
	if(HasShipTrait(refCharacter, "trait04"))
	{
		if(GetHullPercent(refCharacter) < 40 || CheckAttribute(refCharacter, "Tmp.trait04.timer"))
		{
			fMaxSpeedZ *= 1.2;
			refCharacter.Tmp.trait04 = true;
		}
		else
		{
			if(CheckAttribute(refCharacter, "Tmp.trait04") && !CheckAttribute(refCharacter, "Tmp.trait04.timer"))
			{
				refCharacter.Tmp.trait04.timer = true;
				DoQuestFunctionDelay("ReactivateTrait04", 20.0);
			}
		}
	}
	
	if(HasShipTrait(refCharacter, "trait21"))
	{
		float rb, lb, fb, bb;
		if(CheckAttribute(refCharacter, "Ship.Cannons.borts.cannonr.ChargeRatio"))
			rb = float(refCharacter.Ship.Cannons.borts.cannonr.ChargeRatio);
		if(CheckAttribute(refCharacter, "Ship.Cannons.borts.cannonl.ChargeRatio"))
			lb = float(refCharacter.Ship.Cannons.borts.cannonl.ChargeRatio);
		if(CheckAttribute(refCharacter, "Ship.Cannons.borts.cannonf.ChargeRatio"))
			fb = float(refCharacter.Ship.Cannons.borts.cannonf.ChargeRatio);
		if(CheckAttribute(refCharacter, "Ship.Cannons.borts.cannonb.ChargeRatio"))
			bb = float(refCharacter.Ship.Cannons.borts.cannonb.ChargeRatio);
		
		int rcc = 0;
		
		if (rb > 0.0 && rb < 1.0) rcc++;
		if (lb > 0.0 && lb < 1.0) rcc++;
		if (fb > 0.0 && fb < 1.0) rcc++;
		if (bb > 0.0 && bb < 1.0) rcc++;
		
		fMaxSpeedZ *= 1.0 + 0.05 * float(rcc);
	}

	fMaxSpeedZ = fMaxSpeedZ * fTRFromWeight * fTRFromSkill * fTRFromShipState * fTRFromPeople * fTRFomBreaches;
	fMaxSpeedZ *= 1.0 + GetAttributeFloat(rShip, "tuning.modifiers." + M_SHIP_SPEED);

	return fMaxSpeedZ;
}

// Макс скорость для интерфейса, тут сток + бонусы от апгрейдов
float FindShipSpeedMax(ref chr)
{
	ref realShip = GetRealShip(GetCharacterShipType(chr));
	float base = float(realShip.SpeedRate);
	base *= 1.0 + GetAttributeFloat(realShip, "tuning.modifiers." + M_SHIP_SPEED);
	return base;
}

// Макс маневр для интерфейса, тут сток + бонусы от апгрейдов
float FindShipTurnrateMax(ref chr)
{
	ref realShip = GetRealShip(GetCharacterShipType(chr));
	float base = float(realShip.TurnRate);
	base *= 1.0 + GetAttributeFloat(realShip, "tuning.modifiers." + M_SHIP_TURNRATE);
	return base;
}

float SpeedBySkill(ref refCharacter)
{
	float fSpeedPerk;

	float fSkill = GetSummonSkillFromNameToOld(refCharacter, SKILL_SAILING);
	//float fTRFromSkill = 0.7 + (0.03 *  fSkill);
	float fTRFromSkill = 0.8 + (0.55 * pow(fSkill / 100.0, 0.45));
		
    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "ShipSpeedUp"), 1.0, 1.15);   //slib
    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SailingProfessional"), fSpeedPerk, 1.20);
	
	return fTRFromSKill*fSpeedPerk;
}

float FindShipTurnRate(ref refCharacter)
{
	if(!CheckAttribute(refCharacter, "Ship.type"))
	{
		trace("Character " + refCharacter.id + " have no ship!");
		return 0.0;
	}
	int nShipType = int(refCharacter.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + refCharacter.id + " have invalid ship!");
		return 1.0;
	}
	ref rShip = GetRealShip(nShipType);

	float fShipHp = float(refCharacter.ship.hp);
	float fShipMaxHp = float(rShip.HP);
	float fSpeedFromHp = fShipHp/fShipMaxHp;
	if (fSpeedFromHp < 0.0) fSpeedFromHp += AIShip_isPerksUse(int(refCharacter.TmpPerks.Thrift), 0, 0.1); // JOKERTODO переписать более явно
	fSpeedFromHp = 0.7 + fSpeedFromHp * 0.3;

	float fLoad = Clampf(float(refCharacter.Ship.Cargo.Load) / float(rShip.Capacity));
	float fTRFromWeight;
	
	fTRFromWeight = Clampf(1.03 - 1.5 * float(rShip.TurnDependWeight) * fLoad * GetWeightMtpWithIntendant(refCharacter));
	
	// не реализовано, всегда 1 float fTRFromSpeed = 1.0 - float(rShip.TurnDependSpeed);
	// от команды
	//float fCrewMin = float(rShip.MinCrew);
	float fCrewMax = float(rShip.MaxCrew);
	float fCrewOpt = float(rShip.OptCrew);
	float fCrewCur = float(refCharacter.Ship.Crew.Quantity);
	if (fCrewCur > fCrewMax)
	{
		fCrewCur = fCrewMax;
	}
	float  fTRFromPeople;
	
	fTRFromPeople = 0.35 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.65;
	
	if (fTRFromPeople > 1) fTRFromPeople = 1;
	
	float fTRFromSKill = TurnBySkill(refCharacter);
	//float fTRFromSailDamage = Bring2Range(0.05, 1.0, 0.1, 100.0, float(refCharacter.ship.sp));

	float fTurn = fTRFromWeight * fTRFromSkill * fTRFromPeople * fSpeedFromHp * isEquippedArtefactUse(refCharacter, "obereg_10", 1.0, 1.15);

	fTurn = fTurn * isEquippedArtefactUse(refCharacter, "amulet_5", 1.0, 0.9); // гаденыш Согбо belamour 
	if (IsEquipCharacterByItem(refCharacter, "nocturlabe")) fTurn *= int(rShip.Class) <= 2 ? 1.35 : 1.10; // Ноктурлабия
	fTurn *= 1.0 + GetAttributeFloat(rShip, "tuning.modifiers." + M_SHIP_TURNRATE);
	
	if(CheckAttribute(refCharacter, "Ship.hulls.baller_destroyed")) fTurn *= 0.3; // потеряли руль - уменьшаем манёвренность
	//Log_info(refCharacter.id + "  " + fTurn);
	return fTurn;	
}

float TurnBySkill(ref refCharacter)
{
	float fSkill = GetSummonSkillFromNameToOld(refCharacter, SKILL_SAILING);
	float fTRFromSKill;

	//fTRFromSKill = 0.4 + (0.06 * fSkill);
	fTRFromSkill = 0.7 + (0.75 * pow(fSkill / 100.0, 0.45));
	
    float fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "ShipTurnRateUp"), 1.0, 1.15);   //slib
    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SailingProfessional"), fSpeedPerk, 1.20);
    float fFastTurn180 = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "Turn180"), 1.0, 4.0);
    
	return fTRFromSKill*fSpeedPerk*fFastTurn180;
}

int GetCannonsNum(ref chr)
{
	int nShipType = int(chr.ship.type);
    ref refBaseShip = GetRealShip(nShipType);
	
	int iCannons = GetBortIntactCannonsNum(chr, "cannonf", int(refBaseShip.fcannon)) +
	               GetBortIntactCannonsNum(chr, "cannonb", int(refBaseShip.bcannon)) +
				   GetBortIntactCannonsNum(chr, "cannonl", int(refBaseShip.lcannon)) +
				   GetBortIntactCannonsNum(chr, "cannonr", int(refBaseShip.rcannon));
	return iCannons;
}

int GetBortCannonsBaseQty(ref chr, string sBort)
{
	int nShipType = int(chr.ship.type);
	ref rRealShip = GetRealShip(nShipType);
	ref rBaseShip = GetShipByType(int(rRealShip.BaseType));
	
	int iCannons = int(rBaseShip.(sBort));
	return iCannons;
}

int GetBortCannonsQty(ref chr, string sBort)
{
	int iCannonsMax = GetBortCannonsQtyMax(chr, sBort);
	return GetBortIntactCannonsNum(chr, sBort, iCannonsMax);
}

///////////////////////  ВЕРФИ //////////////////////
void SetShipyardStore(ref NPChar)
{
    int    iTest_ship, i;
	string attrName;
	
	if (CheckAttribute(NPChar, "shipyard")) return; // ещё есть корабли с того раза
	
	SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // дата заполнения верфи
    
    if (bBettaTestMode)
    {
        int num = 1;
        for (i = 0; i < GetArraySize(&ShipsTypes); i++)
        {
			ref refShip;
			makeref(refShip,ShipsTypes[i]);
			if (!CheckAttribute(refShip, "Class"))
			{
				continue;
			}
			if (CheckAttribute(refShip, "ShipHolder") && int(refShip.ShipHolder))
			{
				continue;
			}
            attrName = "ship" + num;
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(i, NPChar), attrName);
			num++;
        }        
        return;
    }
	int iNationFlag = GetNationFlag(int(NPChar.nation));
	
	FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
	
	
	iTest_ship = rand(2);
	if (iTest_ship != 0) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_7+FLAG_SHIP_CLASS_6+FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship2");
	iTest_ship = rand(2);
	if (iTest_ship != 0) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship3");
	iTest_ship = rand(3);
	if (iTest_ship != 0) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship4");
	iTest_ship = rand(1);
	if (iTest_ship != 0) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship5");
	
	if (int(PChar.rank) > 3)
	{
		iTest_ship = rand(4);
		if (iTest_ship <= 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship6");
		iTest_ship = rand(4);
		if (iTest_ship <= 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship7");
	}
	
	if (int(PChar.rank) > 7)
	{
		iTest_ship = rand(6);
		if (iTest_ship <= 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship8");
		iTest_ship = rand(6);
		if (iTest_ship <= 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship9");
		iTest_ship = rand(6);
		if (iTest_ship <= 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship10");
	}
	
	if (int(PChar.rank) > 9)
	{
		iTest_ship = rand(8);
		if (iTest_ship <= 4) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship11");
		iTest_ship = rand(6);
		if (iTest_ship <= 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship12");
		iTest_ship = rand(6);
		if (iTest_ship <= 3) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship13");
	}
	
	if (int(PChar.rank) > 11)
	{
		iTest_ship = rand(30);
		if (iTest_ship <= 5) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship14");
		iTest_ship = rand(40);
		if (iTest_ship <= 6) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship15");
		iTest_ship = rand(30);
		if (iTest_ship <= 1) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship16");
	}
	
	if (int(PChar.rank) > 16)
	{
		iTest_ship = rand(30);
		if (iTest_ship <= 7) FillShipParamShipyard(NPChar, GenerateStoreShipExt(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY, iNationFlag), NPChar), "ship17");

	}
}

void FreeShipFromShipyard(ref NPChar)
{
	if (GetNpcQuestPastDayParam(NPChar, "shipyardDate") > (3 + rand(6)))
	{
        aref   arDest, arImt;
		string sAttr;
		int    iNum, i, iShip;
		makearef(arDest, NPChar.shipyard);
		iNum = GetAttributesNum(arDest);
		
		for (i = 0; i < iNum; i++)
		{
	    	arImt = GetAttributeN(arDest, i);
	    	iShip = int(arImt.Type); //GetAttributeValue(arImt));
	    	DeleteAttribute(&RealShips[iShip], "StoreShip"); // можно тереть
	    }		
        DeleteAttribute(NPChar, "shipyard");
	}
}

void RemoveCannonsFromBortShipyard(ref chr, string sBort)
{
	int maxQty = GetBortCannonsQtyMax(chr, sBort);
	// нулим кол-во пушек на борту
	for (int i = 0; i < maxQty; i++)
	{
		string attr = "c" + i;
		chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;  // поломана на 100%, не палит, те нет её
	}	
	RecalculateCargoLoad(chr);  // пересчет, тк пушки снялись
}

void RemoveAllCannonsShipyardShip(ref NPChar)
{
    RemoveCannonsFromBortShipyard(NPChar, "cannonf");
    RemoveCannonsFromBortShipyard(NPChar, "cannonb");
    RemoveCannonsFromBortShipyard(NPChar, "cannonr");
    RemoveCannonsFromBortShipyard(NPChar, "cannonl");
}

void FillShipParamShipyard(ref NPChar, int _iType, string _sShipNum)
{
	aref arTo, arFrom;

	DeleteAttribute(NPChar, "ship");
	NPChar.Ship.Type = _iType;

	SetRandomNameToShip(NPChar);
	SetBaseShipData(NPChar);
	SetCrewQuantity(NPChar, 0);
	if (int(NPChar.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
	{
		ref refBaseShip = GetRealShip(_iType);
		NPChar.Ship.Cannons.Type = GetRandomCaliber(GetRandomCannonType(), refBaseShip);
	}
	DeleteAttribute(NPChar, "Ship.Cargo");  //пустой трюм
	SetGoodsInitNull(NPChar);
	RecalculateCargoLoad(NPChar);

	FillShipyardShipBack(NPChar, _sShipNum);
}

// Берем максимальный калибр корабля и рандомим понижение вплоть до четверти от калибра
int GetRandomCaliber(string sCulevrinOrCanonn, ref baseShip)
{
  int caliber = GetAttributeInt(baseShip, "MaxCaliber");
  if (caliber > 3)
  {
    float reductionMtp = 0.25;
    if (sCulevrinOrCanonn == "culverine") reductionMtp = 0.15;
    int minus = int(float(caliber) * reductionMtp + 0.5); // минимально выйдет 24ф для 42 калибра
    caliber -= rand(minus);
  }

  return GetCannonByTypeAndCaliber(sCulevrinOrCanonn, caliber);
}

string GetRandomCannonType()
{
  if (rand(4) > 0) return "cannon";
  return "culverine";
}


void FillShipyardShip(ref NPChar, string _sShipNum)
{
    aref    arTo, arFrom;

	DeleteAttribute(NPChar, "ship");

    makearef(arFrom,   NPChar.shipyard.(_sShipNum));
    NPChar.Ship = "";
	makearef(arTo, NPChar.Ship);
	CopyAttributes(arTo, arFrom);
}

void FillShipyardShipBack(ref NPChar, string _sShipNum)
{
    aref    arTo, arFrom;

  	DeleteAttribute(NPChar, "shipyard." + _sShipNum);
    NPChar.shipyard.(_sShipNum) = "";
    makearef(arTo,   NPChar.shipyard.(_sShipNum));
	makearef(arFrom, NPChar.Ship);
	CopyAttributes(arTo, arFrom);
}

int GetSailsTuningPrice(ref _chr, ref _shipyard, float _rate)
{
	int st  = GetCharacterShipType(_chr);
	ref shref;
	
	if (st==SHIP_NOTUSED) return 0;
	shref = GetRealShip(st);

	return int(float(_shipyard.ShipCostRate) * int(shref.Price) * _rate / 10) * 10; // кратно 10
}

int GetHullTuningPrice(ref _chr, ref _shipyard)
{
	int st  = GetCharacterShipType(_chr);
	ref shref;
	
	if (st==SHIP_NOTUSED) return 0;
	shref = GetRealShip(st);

	return int(float(_shipyard.ShipCostRate) * int(shref.Price) / 10) * 10; // кратно 10
}

// Warship 26.07.09 Вынес сюда
// int st - GetCharacterShipType(_character)
// ref _shipyard - референс на верфиста
int GetShipPriceByType(int st, ref _shipyard)
{
	if(st==SHIP_NOTUSED) return 0;
	ref shref = GetRealShip(st);

	return int(float(_shipyard.ShipCostRate) * int(shref.Price));
}

// Цена пушек на корабле для верфи
int GetCannonsPrice(ref chr, ref shipyard, int priceType)
{
	int cannonsNum = GetCannonsNum(chr);
	int cannonsGoodsIndex = GetCannonGoodsIdxByType(GetCaracterShipCannonsType(chr));
	int result = GetStoreGoodsPrice(&stores[GetStorage(shipyard.city)], cannonsGoodsIndex, priceType, pchar, cannonsNum);
	return result;
}

// Метод вернет цену продажи корабля персонажа с учётом всех скилов (для верфи)
int GetShipSellPrice(ref _chr, ref _shipyard)
{
	int st = GetCharacterShipType(_chr);
	int price = GetShipPriceByType(st, _shipyard);
	price = int(price - 1.5*GetSailRepairCost(st, GetSailDamagePercent(_chr), _shipyard));
	price = int(price - 1.5*GetHullRepairCost(st, GetHullDamagePercent(_chr), _shipyard));

	float nCommerce   = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE) + 0.001;

	if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}

	price = price - price / (nCommerce*10.5);

	ref rRealShip = GetRealShip(st);

	if (int(rRealShip.Stolen) == true) //проверка на ворованный
	{
		price = int(price/3);
	}
	if (price < 100 && int(_chr.Ship.Type) != SHIP_NOTUSED)
	{
		price = 100;			// символическая цена в 100 песо
	}

	price += GetCannonsPrice(_chr, _shipyard, PRICE_TYPE_SELL);
	return price;
}

// Метод вернет цену покупки корабля персонажа с учётом всех скилов (для верфи)
int GetShipBuyPrice(int iType, ref _shipyard)
{
	float nCommerce = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE);

	if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}
	ref shref = GetRealShip(iType);
	int price = int(GetShipPriceByType(iType, _shipyard) + GetShipPriceByType(iType, _shipyard)/(nCommerce*10)) * (8 - int(shref.Class));
	price += GetCannonsPrice(_shipyard, _shipyard, PRICE_TYPE_BUY); // добавляем цену пушек
	return price;
}

int GetSailRepairCost(int shipType, int repairPercent, ref _shipyard)
{
	int SailRepairCoeff = int(2.0 + MOD_SKILL_ENEMY_RATE/2.0);
	int shipPrice = GetShipPriceByType(shipType, _shipyard);
	if(shipPrice<=0) return 0;
	ref shref = GetRealShip(shipType);
	if(CheckAttribute(shref,"Tuning.GhostShip")) SailRepairCoeff *= 3;
	float scost = SailRepairCoeff * (shipPrice*SAIL_COST_PERCENT+99.0)/100.0;
	scost *= SZN_GetModifierMtp(M_REPAIR_COST, 1.0, 0.01);
	return int((scost*repairPercent+99.0)/100.0);
}

int GetHullRepairCost(int shipType,int repairPercent, ref _shipyard)
{
	int HullRepairCoeff = int(2.0 + MOD_SKILL_ENEMY_RATE/2.0);
	int shipPrice = GetShipPriceByType(shipType, _shipyard);
	if(shipPrice<=0) return 0;
	ref shref = GetRealShip(shipType);
	if(CheckAttribute(shref,"Tuning.GhostShip")) HullRepairCoeff *= 3;
	float scost = HullRepairCoeff * (shipPrice*HULL_COST_PERCENT+99.0)/100.0;
	scost *= SZN_GetModifierMtp(M_REPAIR_COST, 1.0, 0.01);
	return int((scost*repairPercent+99.0)/100.0);
}

int GetSailDamagePercent(ref _chr)
{
	return 100 - int(GetSailPercent(_chr));
}

int GetHullDamagePercent(ref _chr)
{
	return 100 - int(GetHullPercent(_chr));
}
///////////////////////////////////////////////////////////////   ВЕРФИ  <--
// палуба от типа корабля
string GetShip_deck(ref chr, bool map2sea)
{
	string ret, add;

	int    iType = int(chr.Ship.Type);
	if (map2sea)
	{
	    ret = "Ship_deck_";
	}
	else
	{
	    ret = "Deck_Near_Ship_";
	}
	add = "Low"; // если нет типа
	if (iType != SHIP_NOTUSED)
	{
        ref rRealShip = GetRealShip(iType);
        
		add = rRealShip.DeckType;
	}
	if (chr.id == "GOT_boatsvanDega") return "Deck_Galeon_Ship"; // Jason
	return ret + add;
}

void MakeCloneShipDeck(ref chr, bool map2sea)
{
	ref rOrg, rClone;
	int iOrg, iClone;
    string locId, toLocId;
    
    locId = GetShip_deck(chr, map2sea);
    if (map2sea)
	{
	    toLocId = "Ship_deck";
	}
	else
	{
	    toLocId = "Deck_Near_Ship";
	}
	
	iOrg = FindLocation(locId);
	iClone = FindLocation(toLocId);

	makeref(rOrg, Locations[iOrg]);
	makeref(rClone, Locations[iClone]);

	DeleteAttribute(rClone, "");
	CopyAttributes(rClone, rOrg);
	rClone.id = toLocId;
	rClone.index = iClone;
}

void MakeCloneFortBoarding(string fromLocId)
{
	ref rOrg, rClone;
	int iOrg, iClone;
    string toLocId;
    
    toLocId = "BOARDING_FORT";

	iOrg = FindLocation(fromLocId);
	iClone = FindLocation(toLocId);

	makeref(rOrg, Locations[iOrg]);
	makeref(rClone, Locations[iClone]);

	DeleteAttribute(rClone, "");
	CopyAttributes(rClone, rOrg);
	rClone.id = toLocId;
	rClone.index = iClone;
	
    rClone.type = "fort_attack";
	LAi_LocationFantomsGen(rClone, false);
	DeleteAttribute(rClone, "reload");
	//это подкручивание другого файла локаторов. там нет goto, soldiers и пр. есть rld и дополн.сундуки
	if (rClone.models.always.locators == "fortV_locators") 
	{
		rClone.models.always.locators = "fortV_lAttack";
		rClone.models.always.fortV = "fortV_attack";	
	}
	else
	{
		rClone.models.always.locators = "fortVRight_lAttack";
		rClone.models.always.fortV = "fortVRight_attack";
	}
	rClone.boarding.locatorNum = 25;
	rClone.boarding = "false";
	rClone.boarding.nextdeck = "Boarding_fortyard"; // Jason
	rClone.image = "loading\FortShturm_" + rand(2) + ".tga";
}

// Warship 31.05.09 Установка на корабль персонажа определённого паруса
// Путь относительно папки Textures
bool SetShipSailsFromFile(ref _char, String _sailTexturePath)
{
	ref realShip;
	int shipType = int(_char.Ship.Type);

	if(shipType == SHIP_NOTUSED) // Есть ли корабль вообще
	{
		return false;
	}

	realShip = GetRealShip(shipType);
	
	realShip.EmblemedSails.normalTex = _sailTexturePath;
	
	return true;
}

string GetLocalShipAttrib(ref ship, string attrib) 
{
	if (CheckAttribute(ship, attrib)) return ship.(attrib);
	return ""; 
}

bool CheckShipAttribute(ref ship, string attrib)
{
	if(CheckAttribute(ship, attrib)) return true;
	return false;
}

string GetBaseShipParamFromType(int iType, string _param)
{
	object rBaseShip = GetShipByType(iType);
	return rBaseShip.(_param);
}

int GetShipMastsQuantity(ref chr)
{
	if (!CheckAttribute(chr, "ship.type")) return 0;    
	int iShip = int(chr.ship.type);
	if (iShip == SHIP_NOTUSED) return 0;
	if (CheckAttribute(chr,"Ship.MastsQty")) return int(chr.Ship.MastsQty);
	else
	{
		if (CheckAttribute(chr,"Ship.Masts"))
		{
			aref arMasts;
			makearef(arMasts, chr.Ship.Masts);
			return GetAttributesNum(arMasts);			
		}
	}
	return 0;
}

int GetShipFallMastsQuantity(ref chr)
{
	int ret = 0;
	if (!CheckAttribute(chr, "ship.type")) return 0;    
	int iShip = int(chr.ship.type);
	if (iShip == SHIP_NOTUSED) return 0;
	if (CheckAttribute(chr,"Ship.Masts"))
	{
		aref arMasts;
		makearef(arMasts, chr.Ship.Masts);
		int nMasts = GetAttributesNum(arMasts);
		for(int i = 0; i < nMasts; i++)
		{
			string sMast = GetAttributeName(GetAttributeN(arMasts, i));
			if(chr.Ship.Masts.(sMast) == 1) ret++;
		}
	}
	return ret;
}

// belamour расчет скорости по диапазонам (Состояние парусов)
float CalculateSpeedDebuff_SP(float sailsIntegrity) 
{
	if(sailsIntegrity >= 91.0) return Bring2Range(0.95, 1.0, 91.0, 100.0, sailsIntegrity);  // минимальный штраф
	else if(sailsIntegrity >= 61.0) return Bring2Range(0.8, 0.94, 61.0, 90.0, sailsIntegrity);  // Умеренный диапазон
	else return Bring2Range(0.1, 0.6, 0.0, 60.0, sailsIntegrity); // дефолт
	
    return 1.0;
}

// belamour выбираем трейт для корабля
void SetShipTraits(ref rRealShip)
{
	int spec = int(rRealShip.Spec);
	
	if(spec == SHIP_SPEC_UNIVERSAL) return;
	if(CheckAttribute(rRealShip, "QuestSP")) return;
	
	int traitesQty = 3; // - 1 для рандома
	if(spec == SHIP_SPEC_MERCHANT) traitesQty = 4;
	
	rRealShip.Traits = "trait" + spec + (rand(traitesQty) + 1);
}

int GetShipSpec(ref rShip)
{
	return int(rShip.Spec);
}

string GetShipSpecDesc(ref chr)
{
	int nShipType = GetCharacterShipType(chr);
	if(nShipType == SHIP_NOTUSED) return "";
	
	return "special" + int(RealShips[nShipType].Spec);
}

string GetShipTraitDesc(ref chr)
{
	int nShipType = GetCharacterShipType(chr);
	if(nShipType == SHIP_NOTUSED) return "";
	if(CheckAttribute(&RealShips[nShipType], "QuestSP"))
	{
		if(GetShipTypeName(chr) == "Galeon_sm")  return "sp1"; 
		if(GetShipTypeName(chr)  == "LadyBeth")  return "sp2"; 
		if(GetShipTypeName(chr)  == "Memento")   return "sp3"; 
		if(GetShipTypeName(chr)  == "Amsterdam") return "sp4"; 
	}
	if(!CheckAttribute(&RealShips[nShipType],"Traits")) return "";
	
	return RealShips[nShipType].Traits;
}

bool HasShipTrait(ref chr, string trait)
{
	if(int(chr.index) != GetMainCharacterIndex()) return false;
	
	int nShipType = GetCharacterShipType(chr);
	if(nShipType == SHIP_NOTUSED) return false;
	if(!CheckAttribute(&RealShips[nShipType],"Traits")) return false;
	
	return RealShips[nShipType].Traits == trait;
}

void ReactivateTrait04(string quest)
{
	DeleteAttribute(pchar, "Tmp.trait04");
}

// Механика мощи -->
float GetBaseShipPower(int iBaseType)
{
    ref rBaseShip = &ShipsTypes[iBaseType];
    if(CheckAttribute(rBaseShip, "Power"))
        return float(rBaseShip.Power); // Однажды вычислили, больше не надо

	int iClass = int(rBaseShip.Class);
	int iSpec  = int(rBaseShip.Spec);
	float fSpec;
	switch(iSpec)
	{
		case SHIP_SPEC_MERCHANT:	fSpec = 0.75;	break;
		case SHIP_SPEC_UNIVERSAL:	fSpec = 1.1;	break;
		case SHIP_SPEC_RAIDER:		fSpec = 1.3;	break;
		case SHIP_SPEC_WAR:			fSpec = 1.5;	break;
	}
	float fPower = 23.0 * (7.0 - iClass) * 1.6 * fSpec;
    rBaseShip.Power = fPower;
    return fPower;
}

// Увеличенная базовая мощь корабля засчёт эффектов персонажа
float GetModifiedBaseShipPower(ref chr, int baseType)
{
	float fMaxPower = GetBaseShipPower(baseType);
	if (!IsCompanion(chr)) return fMaxPower;

	ref rBaseShip = &ShipsTypes[baseType];
	float mtp = 1.0;
	if (GetCharacterEquipByGroup(pchar, HAT_ITEM_TYPE) == "hat6")
	{
		if (int(rBaseShip.Spec) == SHIP_SPEC_MERCHANT) mtp += 0.4;
	}

	return fMaxPower * mtp;
}

float GetRealShipPower(ref rChar)
{
	ref rShip = GetRealShip(int(rChar.Ship.Type));
	float fMaxPower = GetModifiedBaseShipPower(rChar, int(rShip.BaseType));
	float fPower = fMaxPower;
	float kCrew = float(GetCrewQuantity(rChar)) / float(rShip.MaxCrew); // ~!~ OptCrew
	if (kCrew > 1.0) kCrew = 1.0;
	float kHull = float(rChar.ship.HP) / float(rShip.HP);
	float kSails = float(rChar.ship.SP) / float(rShip.SP);
	float kCannons = 1.0;
	if (rShip.CannonsQuantity != "0")
		kCannons = float(GetCannonsNum(rChar)) / float(rShip.CannonsQuantity);

	// Шляпа Грима
	if (GetCharacterEquipByGroup(rChar, HAT_ITEM_TYPE) == "hat9")
	{
		kHull = kHull + (1.0 - kHull) * 0.3;
		kSails = kSails + (1.0 - kSails) * 0.3;
		kCannons = kCannons + (1.0 - kCannons) * 0.3;
	}

	fPower *= 1 + GetAttributeFloat(rShip, "tuning.modifiers." + M_SQUADRON_POWER);
	fPower *= pow(kCrew, 2.25) * 0.45 + pow(kSails, 2.25) * 0.25 + pow(kHull, 2.25) * 0.2 + pow(kCannons, 2.25) * 0.1;
	return fPower;
}

void UpdatePlayerSquadronPower() // Кэш
{
    ref rChar;
    int i, idx, iShipType;
    float fPower = 0.0;
	for(i = 0; i < COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(PChar, i);
		if(idx != -1)
		{
			rChar = GetCharacter(idx);
			iShipType = int(rChar.ship.type);
			if(iShipType == SHIP_NOTUSED) continue;
            fPower += GetRealShipPower(rChar);
		}
	}
	PChar.Squadron.RawPower = fPower;
	PChar.Squadron.ModPower = SquadronPowerWithMods(fPower);
	Achievments_SquadronPower();
}

float SquadronPowerWithMods(float rawPower)
{
	float fPowerMtp = 1 + GetSquadronPowerMtp(pchar);
	if (CheckOfficersPerk(pchar, "LoneWolf") && GetCompanionQuantity(pchar) < 2) fPowerMtp += PERK_VALUE_LONE_WOLF;
	return rawPower * fPowerMtp;
}
// Механика мощи <--

// belamour добавить бонус "Мементо"
void AddMementoShipBonus(int deadCrew)
{
	if(!GetDLCenabled(DLC_APPID_6)) return;
	if(!ShipBonus2Artefact(pchar, SHIP_MEMENTO)) return;
	
	ref rShip;
	
	makeref(rShip, RealShips[int(pchar.Ship.Type)]);
	
	if(!CheckAttribute(rShip,"DeadSailors"))
	{
		rShip.DeadSailors = 0;
		rShip.DeadSailors.SailorsExpBonus = 0;     // бонус к опыту экипажа
		rShip.DeadSailors.SailorsMoraleBonus = 0;  // бонус к морали
		rShip.DeadSailors.SailorsBoardingBonus = 0;  // бонус команды на абордаже
		rShip.DeadSailors.SurrenderChanceBonus = 0; // бонус к шансу сдачи врага
		rShip.DeadSailors.RecruitPiratesBonus = 0; // бонус к рекрутам пиратам
		rShip.DeadSailors.RecruitSlaveBonus = 0;  // увеличение количества рабов - рекрутов
   	}
	
	int deadSailors = int(rShip.DeadSailors) + deadCrew;
	rShip.DeadSailors = deadSailors;

	rShip.DeadSailors.SailorsExpBonus = func_min((deadSailors * 2), 100); // 0...100
	rShip.DeadSailors.SailorsMoraleBonus = func_min(deadSailors, 100); //0...100
	rShip.DeadSailors.SailorsBoardingBonus = func_min((deadSailors / 50), 10); //0...5
	rShip.DeadSailors.SurrenderChanceBonus = func_min((deadSailors / 100), 20); // 0...20
	rShip.DeadSailors.RecruitPiratesBonus = Bring2Range(0.0, 10.0, 0.0, 0.2, float(rShip.DeadSailors.SailorsBoardingBonus)); // 0.0...0.2
	rShip.DeadSailors.RecruitSlaveBonus = float(rShip.DeadSailors.RecruitPiratesBonus); // 0.0...0.2
}

/// установить орудия по борту (сперва расчитать дельту было стало - лишнее в запасы)
void SetCannonsToBort(ref chr, string sBort, int iQty)
{
	int     curQty = GetBortCannonsQty(chr, sBort);
	int     maxQty = GetBortCannonsQtyMax(chr, sBort);
	int     i, delta;
	string  attr;
	int     center, left, right; // счетчики орудий для распределения
	bool    bLeft; // направление хода
	float	ax = 0.0;
	float 	az = 0.0;
		
	if (iQty > maxQty) iQty = maxQty; 
	if (iQty < 0) iQty = 0;
	
	int idx = GetCannonGoodsIdxByType(int(chr.Ship.Cannons.Type));
    delta = iQty - curQty;
    if (delta > 0)
    {
    	if (GetCargoGoods(chr, idx) < delta) iQty = curQty + GetCargoGoods(chr, idx);
    }
	if (iQty > curQty)
	{ // списать со склада
		RemoveCharacterGoodsSelf(chr, idx, (iQty - curQty));
	}
	else
	{
		if (iQty < curQty)
		{// лишние на склад
			SetCharacterGoods(chr, idx, GetCargoGoods(chr, idx) + (curQty - iQty)); // этот метод, тк перегруз может быть, а  AddCharacterGoodsSimple режет перегруз
		}
	}
	// нулим колво пушек на борту и распределяем заново от центра (как они на модели по номерам не знаю, допуск, что подряд)
	for (i = 0; i < maxQty; i++)
	{
		attr = "c" + i;
		chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0; // поломана на 100%, не палит, те нет её
	}
	// распределяем
	if (iQty > 0)		 
	{
		center = int(maxQty / 2); // целочисленное деление
		left   = center - 1;
		right  = center;
		i = 0; // сколько распределили уже
		bLeft = true;
		while (i < iQty)
		{
			if (bLeft)
			{
				if (left >= 0)
				{
					attr = "c" + left;
					left--;
				}
				else
				{
					attr = "c" + right;	
					right++;
				}
				if (right < maxQty) bLeft = false;
			}
			else
			{
				if (right < maxQty)
				{
					attr = "c" + right;	
					right++;
				}
				else
				{
					attr = "c" + left;
					left--;
				}
				if (left >= 0) bLeft = true;
			}				
			chr.Ship.Cannons.borts.(sBort).damages.(attr) = 0.0; // новая, не битая
			i++;
		}	
	}
	RecalculateCargoLoad(chr);  // пересчет, тк пушки снялись
}

float GetAmsterdamMtp(string _temp)
{
	return 0.08 * (5-wdmGetNationThreat(PIRATE));
}

bool ShipTraitCanBeChanged(ref chr, ref reason)
{
	int nShipType = GetCharacterShipType(chr);
	if (nShipType == SHIP_NOTUSED) reason = "EmptyShip";
	else if (!IsFellowOurCrew(chr)) reason = "QuestCompanion";                            // не наш чел
	else if (CheckAttribute(&RealShips[nShipType], "QuestSP")) reason = "QuestSP";        // шипспаковый
	else if (int(RealShips[nShipType].Spec) == SHIP_SPEC_UNIVERSAL) reason = "Universal"; // универсал

	return reason == "";
}

int GetChangeShipTraitCost(ref chr)
{
	int shipClass = GetCharacterShipClass(chr);
	switch (shipClass)
	{
		case 1: return 2000; break;
		case 2: return 1400; break;
		case 3: return 1000; break;
		case 4: return 700; break;
		case 5: return 350; break;
		case 6: return 150; break;
		case 7: return 50; break;
	}
}

int GetAuditShipCost(ref chr)
{
	int shipClass = GetCharacterShipClass(chr);
	switch (shipClass)
	{
		case 1: return 2500; break;
		case 2: return 1600; break;
		case 3: return 1000; break;
		case 4: return 625; break;
		case 5: return 350; break;
		case 6: return 200; break;
		case 7: return 75; break;
	}
}

int GetSpecialityUpgradeShipCost(ref chr)
{
	int shipClass = GetCharacterShipClass(chr);
	switch (shipClass)
	{
		case 1: return 3000; break;
		case 2: return 1800; break;
		case 3: return 1000; break;
		case 4: return 550; break;
		case 5: return 350; break;
		case 6: return 250; break;
		case 7: return 100; break;
	}
}

// Получить кол-во опыта за процент отремонтированного корпуса/парусов корабля
float GetExpForRepair(ref chr, int percentRepaired, string type)
{
	float divider = HULL_REPAIR_EXP_MTP;
	if (type == "sails") divider = SAIL_REPAIR_EXP_MTP;

	return percentRepaired * (8-GetCharacterShipClass(chr)) / divider;
}

// Распределить команду компаньона по эскадре, вернуть остаток
int DistributeCrewFromShipToSquadron(ref squadronLeader, ref chr)
{
	int crewQty = GetCrewQuantity(chr);

	for(int i=0; i<COMPANION_MAX; i++)
	{
		if (crewQty <= 0) break;

		int companionIdx = GetCompanionIndex(squadronLeader, i);
		if (companionIdx < 0 || companionIdx == int(chr.index)) continue;

		ref companion = GetCharacter(companionIdx);
		if (!GetRemovable(companion)) continue;

		int shortage = GetFreeCrewQuantity(companion);
		int transferQty = func_min(shortage, crewQty);
		AddCharacterCrew(companion, transferQty);
		AddCharacterCrew(chr, -transferQty);
		crewQty -= shortage;
	}

	return crewQty;
}

// Установить экипаж по всем кораблям вплоть до лимита, вернуть остаток
int SetCrewToSquadron(ref squadronleader, int crewQty, bool skipQuestShips = true)
{
	for(int i=0; i<COMPANION_MAX; i++)
	{
		int companionIdx = GetCompanionIndex(squadronLeader, i);
		if (companionIdx < 0) continue;

		ref companion = GetCharacter(companionIdx);
		if (skipQuestShips && !GetRemovable(companion)) continue;

		int maxCrew = GetMaxCrewQuantity(companion);
		int resultCrew = func_min(maxCrew, crewQty);
		SetCrewQuantity(companion, resultCrew);
		crewQty -= resultCrew;
	}

	return crewQty;
}