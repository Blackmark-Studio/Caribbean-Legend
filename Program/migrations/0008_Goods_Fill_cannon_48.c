
void ApplyMigration(ref migrationState)
{
	for(int i=0; i<STORE_QUANTITY; i++)
	{
		ref refStore = &stores[i];
		DeleteAttribute(refStore, "Goods.Cannon_48");
	}
	
	RefreshStoresForTheNewGood(GOOD_CANNON_48);
	UpdateAllStores();
}
