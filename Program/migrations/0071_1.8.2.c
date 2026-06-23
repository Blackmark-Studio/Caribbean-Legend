
void ApplyMigration(ref migrationState)
{
	InitTool_0071();
	if(LoadSegment("items\modifiers\init\init.c"))
	{
		InitModifiers();
		UnloadSegment("items\modifiers\init\init.c");
	}
}

void InitTool_0071()
{
	object newItem;
	ref item;
	newItem.id = "nocturlabe";
	newItem.name = "itmname_nocturlabe";
	newItem.describe = "itmdescr_nocturlabe";
	newItem.model = "";
	newItem.picIndex = 10;
	newItem.picTexture = "ITEMS_42";
	newItem.Weight = 0.2;
	newItem.price = 130000;
	newItem.ItemType = "SUPPORT";
	newItem.TradeType = ITEM_TRADE_NORMAL;
	newItem.groupID	= TOOL_ITEM_TYPE;
	item = InitNewItem(&newItem);
	item.PriceDublon = 250;
}
