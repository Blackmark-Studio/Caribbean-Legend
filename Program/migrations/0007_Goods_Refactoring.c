void ApplyMigration(ref migrationState) {
	
    int quantity = GetArraySize(&Goods);
	SetArraySize(&Goods, quantity + 1);

	int n = quantity;
	ref curGood;
	makeref(curGood, Goods[n]);

	curGood.Name             = "Cannon_48";
    curGood.CannonIdx        = CANNON_TYPE_CANNON_LBS48;
    curGood.Cost             = Cannon[CANNON_TYPE_CANNON_LBS48].Cost;
    curGood.Weight           = Cannon[CANNON_TYPE_CANNON_LBS48].Weight;
    curGood.Units            = 1;
    curGood.AfraidWater      = 0;
    curGood.type             = T_TYPE_CANNONS;
    curGood.trade_type       = T_TYPE_CANNONS;
    curGood.NotSale          = 1;
    curGood.NotGenerate      = 1;
    curGood.FireRange        = Cannon[CANNON_TYPE_CANNON_LBS48].FireRange;
    curGood.DamageMultiply   = Cannon[CANNON_TYPE_CANNON_LBS48].DamageMultiply;
    curGood.ReloadTime       = sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS48]));
    curGood.Norm             = 10; 
    curGood.MediumNorm       = 1.0;
    curGood.SmallNorm        = 1.0;

    
    for(int i=0; i<STORE_QUANTITY; i++)
    {
       stores[i].Goods.Cannon_48.TradeType = T_TYPE_CANNONS;
       stores[i].Goods.Cannon_48.Type      = T_TYPE_CANNONS;
       stores[i].Goods.Cannon_48.Norm      = 0;
       stores[i].Goods.Cannon_48.Quantity  = 0;
    }

   
   Cannon[CANNON_TYPE_CULVERINE_LBS36].RealCaliber = 36;
   
   Goods[GOOD_COFFEE].Flags                 = FLAG_GOODS_EXPORT_PLANTS;
   Goods[GOOD_TOBACCO].Flags                = FLAG_GOODS_EXPORT_PLANTS;
   Goods[GOOD_CHOCOLATE].Flags              = FLAG_GOODS_EXPORT_PLANTS;
   
   Goods[GOOD_EBONY].Flags                   = FLAG_GOODS_VALUABLE_EXPORT + FLAG_GOODS_VALUABLE_WOOD;    
   Goods[GOOD_MAHOGANY].Flags                = FLAG_GOODS_VALUABLE_EXPORT + FLAG_GOODS_VALUABLE_WOOD;
   Goods[GOOD_CINNAMON].Flags                = FLAG_GOODS_VALUABLE_EXPORT;
   Goods[GOOD_SANDAL].Flags                  = FLAG_GOODS_VALUABLE_WOOD;
   Goods[GOOD_CANNON_36].Flags               = FLAG_GOODS_CROWN_CANNONS;
   Goods[GOOD_CANNON_42].Flags               = FLAG_GOODS_CROWN_CANNONS;
   Goods[GOOD_CULVERINE_36].Flags            = FLAG_GOODS_CROWN_CANNONS;
   Goods[GOOD_CANNON_48].Flags               = FLAG_GOODS_CROWN_CANNONS;
}
