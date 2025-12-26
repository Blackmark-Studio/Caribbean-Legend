void ApplyMigration(ref migrationState)
{
	PerksPotionInit();
	ref itm = ItemsFromID("cirass1");
	itm.weight = 27;
	itm.price = 21000;
}

void PerksPotionInit()
{
	int i, n;
	ref itm;
	aref callback;
	object tempItems[TOTAL_ITEMS];
	
	for(i = 0; i < TOTAL_ITEMS; i++)
	{
		CopyAttributes(&tempItems[i], &Items[i]);
		//trace("Index " + i + " ID temp " + tempItems[i].id + " ID real " + Items[i].id);
	}
	
	ExpandItemsArray();
	
	ITEMS_QUANTITY++;
	
	DeleteAttribute(&Items[ITEMS_QUANTITY - 1], "");
	InitAddItem(ITEMS_QUANTITY - 1);
	
	InitStdRecipies0028(ITEMS_QUANTITY - 1, "recipe_PerksPotion", "PerksPotion", 20000);
	
	for(i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		DeleteAttribute(&Items[i], "");
		CopyAttributes(&Items[i], &tempItems[i - 1]);
		Items[i].index = i;
	}
	
	ExpandItemsArray();
	
	n = TOTAL_ITEMS - 1;
	makeref(itm,Items[n]);
	itm.id = "PerksPotion";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_PerksPotion";
	itm.describe = "itmdescr_PerksPotion";
    itm.model = "balsam";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_41";
	itm.price = 20000;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = 0.001;
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.multiobject.alchemy = true;
	itm.ItemType = "SUPPORT";
	AddOnUseCallback(itm, "RevokePerksPotionEffect");
	AddOnUseCallback(itm, "NotifyPlayerUse");
	callback = AddCanBeUsedCallback(itm, "IsFellowOurCrew");
	callback.argumentsConfig = "chr";
	
	InitMultiObject0028(		"PerksPotion",	    "t1",     "gold_dublon",  "Component", 	666); // дублон
	InitMultiObject0028(		"PerksPotion",	    "t2",     "cannabis1",   "Component", 	  5); // дурман
	InitMultiObject0028(		"PerksPotion",	    "t3",     "cannabis2", 	  "Component", 	  5); // Сабадилла
	InitMultiObject0028(		"PerksPotion",	    "t4",     "cannabis3", 	  "Component", 	  5); // вербена
	InitMultiObject0028(		"PerksPotion",	    "t5",     "cannabis4", 	  "Component", 	  5); // Ипекакуана
	InitMultiObject0028(  		"PerksPotion",	    "t6",  	  "cannabis5",    "Component", 	  5); // гуарана
	InitMultiObject0028(  		"PerksPotion",      "t7",     "cannabis7", 	  "Component", 	 10); // Мангароса
	InitMultiObject0028(  		"PerksPotion",      "t8",     "cannabis6",    "Component", 	  5); // ямайский перец
	InitMultiObject0028(  		"PerksPotion",      "t9",     "mineral14",   "Component", 	  2); // крыло вампира
	InitMultiObject0028(  		"PerksPotion",     "t10",     "jewelry19",   "Component", 	  2); // коралл
	InitMultiObject0028(  		"PerksPotion",     "t11",     "mineral17",   "Component", 	  1); // флакон
	InitMultiObject0028(  		"PerksPotion",     "t12",     "mineral31",   "Component", 	  2); // заговоренная кость
	InitMultiObject0028(  		"PerksPotion",     "t13",     "mineral4",   "Component", 	  3); // Жук-Геркулес
	InitMultiObject0028(  		"PerksPotion",     "t14",   "alchemy_tool", "AlchemyTool", 	  1); // Алхимический набор
}

int InitStdRecipies0028(int ItemIndex, string id, string result, int Price)
{
	ref	recipe;
	int	recipeIndex;
	
	recipeIndex = ItemIndex;
	makeref(recipe, Items[recipeIndex]);
	
	recipe.id			= id;	
	recipe.result 		= result;
	recipe.groupID		= SPECIAL_ITEM_TYPE;
	recipe.name			= "itmname_" + id;
	recipe.describe		= "itmdescr_" + id;		
	recipe.model		= "letter";
	recipe.picTexture	= "ITEMS_26";
	recipe.picIndex		= 16;
	recipe.price		= Price;	
	recipe.rare 		= 0.0001;
	recipe.minlevel 	= 1;
	recipe.Weight 		= 0.1;
	recipe.ItemType 	= "SUPPORT";
	//recipe.TradeType 	= ITEM_TRADE_POTION;
	
	recipeIndex++;
	return recipeIndex;
}

void InitMultiObject0028(	string id,			
						string sAttr,       
						string component_id,
						string component_use,
						int    component_qty)
{
	ref rItem = ItemsFromID(id);
	rItem.component.(sAttr).id 	=  component_id;
	rItem.component.(sAttr).use =  component_use;
	rItem.component.(sAttr).qty =  component_qty;
}
