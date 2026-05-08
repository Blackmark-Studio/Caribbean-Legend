
void ApplyMigration(ref migrationState)
{
	InitHat_0065();
	InitBlade_0065();
	InitIdol_0065();
	if(LoadSegment("items\modifiers\init\init.c"))
	{
		InitModifiers();
		UnloadSegment("items\modifiers\init\init.c");
	}

	switch (iGlobalHelpTime)
	{
		case 1: iGlobalHelpTime = 0; break;
		case 2: iGlobalHelpTime = 1; break;
		case 3: iGlobalHelpTime = 2; break;
	}
}

void InitHat_0065()
{
	object newItem;
	ref item;
	newItem.id = "hat12";
	newItem.groupID	= HAT_ITEM_TYPE;
	newItem.name = "itmname_hat12";
	newItem.describe = "itmdescr_hat12";
	newItem.model = "hat12";
	newItem.picIndex = 8;
	newItem.picTexture = "ITEMS_42";
	newItem.price = 70000;
	newItem.Weight = 0.1;
	newItem.ItemType = "SUPPORT";
	newItem.TradeType = ITEM_TRADE_AMMUNITION;
	item = InitNewItem(&newItem);
}

void InitBlade_0065()
{
	ref item = ItemsFromID("blade_34");
	item.groupID 			= BLADE_ITEM_TYPE;
	item.model				= "blade_34";
	item.name				= "itmname_blade_34";
	item.describe			= "itmdescr_blade_34";
	item.folder 			= "ammo";
	item.picTexture		= "ITEMS_42";
	item.picIndex			= 9;
	item.param.time 		= 0.1;
	item.param.colorstart 	= argb(65, 65, 65, 65);
	item.param.colorend 	= argb(0, 32, 32, 32);
	item.ItemType 			= "WEAPON";
	item.lenght 			= 1.0;
	item.weight = 2.7;
	item.curve				= 1.0;
 	item.FencingType  = FencingL;
	item.quality			= B_EXCELLENT;
	item.target			= TGT_QUEST;
	item.TradeType 		= ITEM_TRADE_AMMUNITION;
	item.price = 35000;
	ReinitBladeDamage(item);
}

void InitIdol_0065()
{
	object newItem;
	ref item;
	newItem.id = "greenIdol";
	newItem.name = "itmname_greenIdol";
	newItem.describe = "itmdescr_greenIdol";
	newItem.model = "";
	newItem.picIndex = 7;
	newItem.picTexture = "ITEMS_42";
	newItem.Weight = 1.0;
	newItem.price = 19260;
	newItem.ItemType = "SUPPORT";
	newItem.TradeType = ITEM_TRADE_NORMAL;
	newItem.groupID	= TOOL_ITEM_TYPE;
	item = InitNewItem(&newItem);
}