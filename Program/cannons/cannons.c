#include "cannons\cannons.h"

extern void InitCannons();

void CannonsInit()
{
	if(LoadSegment("cannons\cannons_init.c"))
	{
		InitCannons();
		UnloadSegment("cannons\cannons_init.c");
	}

	SetEventHandler(GET_CANNON_BY_TYPE_EVENT,"CannonGetByTypeEvent",0);
}

aref CannonGetByTypeEvent()
{
	int iCannonType = GetEventData();
	return &Cannon[iCannonType];
}

int GetCannonByTypeAndCaliber(string sCannonType, int iCaliber)
{
	int typeIdx = GetCannonTypeIndex(sCannonType);
	if (typeIdx == -1)
	{
		return CANNON_TYPE_NONECANNON;
	}
	
	//Если есть орудие подходящего типа - будем брать максимально допустимый калибр. Например в 8ф слот выбираем 6ф пушку, хотя и существует 8ф кулеврина - предпочтение отдается нужному типу.
	int result = CANNON_TYPE_NONECANNON;
	int maxCaliber = -1;
	
	//Если орудия подходящего типа вообще нет - будем брать максимально допустимый калибр из всех типов. Например, если нет кулеврины, влезающей в 3ф слот - будем брать пушку.
	int resultIgnoreType = CANNON_TYPE_NONECANNON;
	int maxCaliberIgnoreType = -1;
	
	for (int i = 0; i <GetArraySize(&Cannon) ; i++) 
	{
		ref curCannon;
		makeref(curCannon, Cannon[i]);
		
		int caliber = GetCannonCaliberNominal(i);
		int type = sti(curCannon.type);
		
		if (typeIdx == type && caliber <= iCaliber && caliber > maxCaliber)
		{
			maxCaliber = caliber;
			result = i;
		}
		
		
		if (caliber <= iCaliber && caliber > maxCaliberIgnoreType)
		{
			maxCaliberIgnoreType = caliber;
			resultIgnoreType = i;
		}
	}
	
	
	if (result != CANNON_TYPE_NONECANNON)
	{
		return result;
	}
	
	if (resultIgnoreType != CANNON_TYPE_NONECANNON)
	{
		return resultIgnoreType;
	}
	
	return CANNON_TYPE_NONECANNON;
}

int FindCannonByText(string sId)
{
	for(int i = 0; i < GetArraySize(&Cannon); i++)
	{
		if(Cannon[i].picture == sId)
		{
			return i;
		}
	}
	return -1;
}

string GetCannonType(int iCannon)
{
	if (iCannon != CANNON_TYPE_NONECANNON) //fix
	{
		int iCannonType = sti(Cannon[iCannon].type);

		switch(iCannonType)
		{
			case CANNON_NAME_CULVERINE:
				return "Culverine";
			break;
			case CANNON_NAME_CANNON:
				return "Cannon";
			break;
		}
	}
	return "NoneCannon";
}

int GetCannonTypeIndex(string type)
{
	switch(type)
	{
		case "culverine":
			return CANNON_NAME_CULVERINE;
		break;
		case "cannon":
			return CANNON_NAME_CANNON;
		break;
		case "special":
			return CANNON_NAME_SPECIAL_CANNON;
		break;
	}

	return -1;
}


// boal 09/02/05
float GetCannonReloadTime(ref rCannon)
{
	if (!iArcadeSails)
	{
	    return  stf(rCannon.ReloadTime) * 3;
	}
	else
	{
	    return  stf(rCannon.ReloadTime);
	}
}

int GetCannonGoodsIdxByType(int iCannon)
{
	int i;
	
	for (i = 0; i< GetArraySize(&Goods); i++)
	{
		if (CheckAttribute(&Goods[i], "CannonIdx"))
		{
			if (sti(Goods[i].CannonIdx) == iCannon) return i;
		}
	}
	return -1;	
}