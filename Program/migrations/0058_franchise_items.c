
void ApplyMigration(ref migrationState)
{
	InitMusket_0058();
	InitBook_0058();
}

void InitMusket_0058()
{
	// Мушкет вождя по интеграции франшизы
	ref mushket_indian = InitStdMusketCommon("mushket_indian", "mushket_indian", "ITEMS_42", 6, 0.0001, 1, 1831, 110.0, 145.0, 14.0, 1, B_UNIQUE, 55.0);
	InitGunWithAmmoParams(mushket_indian, "t1", "cartridge", "",       127.0, 167.0, 0.0,  1, 0,  29, 0);
	InitGunWithAmmoParams(mushket_indian, "t2", "bullet", "gunpowder", 110.0, 145.0, 0.0,  0, 0,  38, 1);
	mushket_indian.PriceDublon = 450;
}

void InitBook_0058()
{
	object newItem;
	ref item;
	newItem.id = "legendGuide";
	newItem.name = "itmname_legendGuide";
	newItem.describe = "itmdescr_legendGuide";
	newItem.model = "";
	newItem.picIndex = 5;
	newItem.picTexture = "ITEMS_42";
	newItem.Weight = 0.1;
	newItem.price = 0;
	newItem.ItemType = "SUPPORT";
	newItem.TradeType = ITEM_TRADE_NORMAL;
	newItem.groupID	= TOOL_ITEM_TYPE;
	item = InitNewItem(&newItem);
}