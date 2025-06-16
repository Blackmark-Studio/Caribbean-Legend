#define GOODS_QUANTITY  	50
// порядок не менять !!! порядок важен для AI фантомов ! <-- ugeen


#define FLAG_GOODS_EXPORT_PLANTS    1
#define FLAG_GOODS_VALUABLE_EXPORT  2
#define FLAG_GOODS_VALUABLE_WOOD    4
#define FLAG_GOODS_CROWN_CANNONS    8

#define FLAG_GOODS_NONE             0
#define FLAG_GOODS_ALL              7

#define MAX_GOODS_TYPES 7

#define FLAG_GOODS_TYPE_NORMAL			1		// повседневные товары
#define FLAG_GOODS_TYPE_AMMUNITION		2		// боеприпасы
#define FLAG_GOODS_TYPE_CROWN			4		// коронные товары
#define FLAG_GOODS_TYPE_EXPORT			8		// колониальные товары
#define FLAG_GOODS_TYPE_IMPORT			16		// импортные товары
#define FLAG_GOODS_TYPE_UNIQUE			32		// уникальные товары
#define FLAG_GOODS_TYPE_CANNONS 		64		// орудия
#define FLAG_GOODS_TYPE_ALL 	        63		// все

int gGoodsTypeFlags[MAX_GOODS_TYPES] = {1, 2, 4, 8, 16, 32, 64}

// боеприпасы
#define GOOD_BALLS	    	0
#define GOOD_GRAPES	    	1
#define GOOD_KNIPPELS		2
#define GOOD_BOMBS	    	3

// товары повседневного спроса
#define GOOD_FOOD       	4
#define GOOD_SAILCLOTH  	5
#define GOOD_PLANKS     	6
#define GOOD_BRICK      	7
#define GOOD_WHEAT      	8
#define GOOD_CLOTHES		9
#define GOOD_FRUITS     	10

// колониальные (экспортные) товары
#define GOOD_COFFEE	    	11   // FLAG_GOODS_EXPORT_PLANTS
#define GOOD_CHOCOLATE		12   // FLAG_GOODS_EXPORT_PLANTS
#define GOOD_TOBACCO		13   // FLAG_GOODS_EXPORT_PLANTS
#define GOOD_SUGAR	    	14
#define GOOD_COTTON	    	15
#define GOOD_LEATHER		16
#define GOOD_EBONY      	17   // FLAG_GOODS_VALUABLE_EXPORT + FLAG_GOODS_VALUABLE_WOOD
#define GOOD_MAHOGANY 		18   // FLAG_GOODS_VALUABLE_EXPORT + FLAG_GOODS_VALUABLE_WOOD
#define GOOD_CINNAMON   	19   // FLAG_GOODS_VALUABLE_EXPORT
#define GOOD_COPRA      	20
#define GOOD_PAPRIKA    	21

// привозные товары из Европы
#define GOOD_POWDER     	22
#define GOOD_WEAPON	    	23
#define GOOD_MEDICAMENT 	24
#define GOOD_WINE	    	25
#define GOOD_RUM	    	26
#define GOOD_ALE	    	27

// уникальные товары
#define GOOD_SHIPSILK	    28
#define GOOD_ROPES	    	29
#define GOOD_SANDAL	    	30  // FLAG_GOODS_VALUABLE_WOOD
#define GOOD_OIL        	31

// коронные товары
#define GOOD_SLAVES     	32
#define GOOD_GOLD       	33
#define GOOD_SILVER	    	34

//   орудия
#define GOOD_CANNON_3    	35
#define GOOD_CANNON_6    	36
#define GOOD_CANNON_8    	37
#define GOOD_CANNON_12   	38
#define GOOD_CANNON_16   	39
#define GOOD_CANNON_18   	40
#define GOOD_CANNON_20   	41
#define GOOD_CANNON_24   	42
#define GOOD_CANNON_32   	43
#define GOOD_CANNON_36   	44 // FLAG_GOODS_CROWN_CANNONS
#define GOOD_CANNON_42   	45 // FLAG_GOODS_CROWN_CANNONS

#define GOOD_CULVERINE_8  	46
#define GOOD_CULVERINE_18 	47
#define GOOD_CULVERINE_36 	48 // FLAG_GOODS_CROWN_CANNONS
#define GOOD_CANNON_48 	    49 // FLAG_GOODS_CROWN_CANNONS


object  Goods[GOODS_QUANTITY];

ref GetGoodByType(int iGoodType)
{
	return &Goods[iGoodType];
}

int FindGood(string sGood)
{
	for (int i=0; i<GetArraySize(&Goods); i++) 
	{ 
		if (Goods[i].Name == sGood) return i; 
	}
	return -1;
}

ref GetGoodByID(string sGood)
{
	for (int i=0; i<GetArraySize(&Goods); i++) 
	{ 
		if (Goods[i].Name == sGood) 
		{
			return &Goods[i];
		}
	}
	trace("WARNING! Goods ID (" + sGood +") not found!");
}

int GetGoodWeightByType(int iGoodType,int quantity)
{
	int unitSize = sti(Goods[iGoodType].Units);
	int unitQuantity = (quantity+unitSize-1)/unitSize;
	int weight = makeint(unitQuantity*stf(Goods[iGoodType].Weight) + 0.05);
	return weight;
}

int GetGoodQuantityByWeight(int iGoodType,int weight)
{
	int unitSize = sti(Goods[iGoodType].Units);
	int uqnt = makeint( weight / stf(Goods[iGoodType].Weight) );
	return unitSize*uqnt;
}


// Usage: GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_EXPORT_PLANTS + FLAG_GOODS_VALUABLE_WOOD)
// Gives random export or unique good with, FLAG_GOODS_EXPORT_PLANTS or FLAG_GOODS_VALUABLE_WOOD flags
//
// GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_NONE)
// Gives random export or unique good disregard the flags


int GetRandomGood(int typeFlags, int goodsFlags) 
{
	int goodsArr[2];
	SetArraySize(&goodsArr, GetArraySize(&Goods));
	
	int goodsCount = 0;
	
	for (int i = 0; i < GetArraySize(&Goods); i++)
	{
		ref refGood;
		makeref(refGood, Goods[i]);
		
		if (goodsFlags != FLAG_GOODS_NONE)
		{
			if (!CheckAttribute(refGood, "Flags"))
			{
				continue;
			}
			int curFlags = sti(refGood.Flags);
			if (!and(curFlags, goodsFlags))
			{
				continue;
			}
		}

		if (!CheckAttribute(refGood, "Type"))
		{
			continue;
		}

		int type = sti(refGood.Type);

		if (!and(typeFlags, gGoodsTypeFlags[type]))
		{
			continue;
		}

		goodsArr[goodsCount] = i;
		goodsCount++;
	}

	if (goodsCount == 0) 
	{
		return -1;
	}

	int goodIdx = rand(goodsCount - 1)
	return goodsArr[goodIdx];
}
