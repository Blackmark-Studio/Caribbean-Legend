



void RefreshStoresForTheNewGood(int idx)
{
	ref curGood;
	makeref(curGood, Goods[idx]);
	
	
	for(int i=0; i<STORE_QUANTITY; i++)
    {
		ref refStore = &stores[i];
		string goodName = curGood.name;
		if (!CheckAttribute(refStore,"Goods."+goodName))
		{
			stores[i].Goods.(goodName).TradeType = curGood.TradeType;
			stores[i].Goods.(goodName).Type      = curGood.Type;
			stores[i].Goods.(goodName).NotUsed 			= false;
			stores[i].Goods.(goodName).Quantity 		= 0;
			stores[i].Goods.(goodName).canbecontraband 	= 0;
			
			CalculateGoodStoreNorm(&stores[i], idx);
			
			int iColony = FindColony(stores[i].Colony);
			if (iColony != -1)
			{
				ref rColony = GetColonyByIndex(iColony);
				SetPriceForGoodByStoreMan(rColony, i, true);
			}
			
		}
    }
}

void CalculateGoodStoreNorm(ref pRef, int goodIdx)
{
	ref pGood = &Goods[goodIdx];
	string goodName = pGood.Name;
	
	int iColony = FindColony(pRef.Colony); // город магазина

    float 	RndPriceModify;
	float 	RndPriceModifySign = -1.0;
	
	if (iColony != -1)
	{
		ref rColony = GetColonyByIndex(iColony);
		int islandIdx 	= FindIsland(rColony.island); 	// остров города
		if (islandIdx!=-1)
		{
			ref rIsland = GetIslandByIndex(islandIdx);
			if(CheckAttribute(rIsland,"RndPriceModify")) 
			{
				RndPriceModify = stf(rIsland.RndPriceModify);
				if(CheckAttribute(rIsland,"RndPriceModifySign")) 
					RndPriceModifySign = stf(rIsland.RndPriceModifySign);
			}	
			else
			{	
				trace("Uninitialized island rng:  id="+rColony.island);
			}			
		}		
		else
		{		
			trace("Mistake island id into store:  id="+rColony.island);
		}	
	}
	else
	{
		trace("Mistake Colony id into store:  id=" + pRef.Colony);
	}

	switch(sti(pRef.Goods.(goodName).TradeType))
	{
		case T_TYPE_NORMAL:
		    pRef.Goods.(goodName).Quantity = sti(sti(pGood.Norm)*0.75 + rand(sti(sti(pGood.Norm)*0.1)));
			pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
			break;

		case T_TYPE_EXPORT:
		    pRef.Goods.(goodName).Quantity = sti(sti(pGood.Norm)*0.9 + rand(sti(sti(pGood.Norm)*0.2))); 
			pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
			break;

		case T_TYPE_IMPORT:
		    pRef.Goods.(goodName).Quantity = sti(sti(pGood.Norm)*0.4 + rand(sti(sti(pGood.Norm)*0.05)));
			pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign; 
			break;
			
		case T_TYPE_AGGRESSIVE:
			pRef.Goods.(goodName).Quantity = sti(sti(pGood.Norm)*0.1 + rand(sti(sti(pGood.Norm)*0.05)));
			pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
			break;	

		case T_TYPE_CONTRABAND:
		    pRef.Goods.(goodName).Quantity = sti(sti(pGood.Norm)*0.1 + rand(sti(sti(pGood.Norm)*0.05)));
			pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
			break;
			
		case T_TYPE_AMMUNITION:  //делаю все тоже, что и для нормального товара, а тип нужен, чтоб на корабле не скупали лишнее.				
			pRef.Goods.(goodName).Quantity = sti(sti(pGood.Norm)*0.75 + rand(sti(sti(pGood.Norm)*0.1)));				
			pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
			break;
			
		case T_TYPE_CANNONS: 
			if(sti(pGood.NotSale) == 1) // 1.2.5 --> старшие калибры не продаем !!!
			{
				pRef.Goods.(goodName).Quantity = 0;
			}
			else
			{
				pRef.Goods.(goodName).Quantity = sti(sti(pGood.Norm)*0.4 + rand(sti(sti(pGood.Norm)*0.4)));
			}	
			pRef.Goods.(goodName).RndPriceModify = (frnd() * 0.03 + RndPriceModify + 0.10) * RndPriceModifySign; 
			pRef.Goods.(goodName).canbecontraband = CONTRA_SELL;			// все орудия можем продавать контрабандистам !!
			break;	
	}
}

// запоминаем цены в ГГ
void SetPriceForGoodByStoreMan(ref rchar, int i, bool single)
{
    ref refStore, nulChr;
    string attr1, sGoods;
    int tradeType;
    string tmpstr;
    aref   refGoods;

    nulChr = &NullCharacter;

    if (sti(rchar.StoreNum) >= 0)
    {
        refStore = &stores[sti(rchar.StoreNum)];
        attr1 = rchar.id; // ветка, где храним цены

        sGoods = "Gidx" + i;
        tmpstr = Goods[i].name;
        tradeType = 0;
        if (CheckAttribute(refStore,"Goods."+tmpstr))
        {
           makearef(refGoods, refStore.Goods.(tmpstr));
           tradeType = MakeInt(refGoods.TradeType);
        }
        nulChr.PriceList.(attr1).(sGoods).tradeType = tradeType; // тип торговли            
        nulChr.PriceList.(attr1).(sGoods).Buy  = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY,  pchar, 1);            
		if (tradeType == T_TYPE_CONTRABAND && !bBettaTestMode)
        {
            nulChr.PriceList.(attr1).(sGoods).Buy  = "???";
        }
        nulChr.PriceList.(attr1).(sGoods).Sell = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);  
		if (tradeType == T_TYPE_CONTRABAND && !bBettaTestMode)
        {
            nulChr.PriceList.(attr1).(sGoods).Sell  = "???";
        }			
        nulChr.PriceList.(attr1).(sGoods).Qty  = GetStoreGoodsQuantity(refStore, i);
		if (tradeType == T_TYPE_CONTRABAND && !bBettaTestMode)
        {
            nulChr.PriceList.(attr1).(sGoods).Qty  = "???";
        }

    }
	
	if (single)
	{
		nulChr.PriceList.(attr1).AltDate = GetQuestBookDataDigit();
	}
}
