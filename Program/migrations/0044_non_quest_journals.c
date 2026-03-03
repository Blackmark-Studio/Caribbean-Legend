void ApplyMigration(ref migrationState)
{
	// на момент миграции журналов может не быть в игре, поэтому сэйфовые вызовы
	int itemIdx;
	itemIdx = GetItemIndex("piratesJournal_1");
	if (itemIdx != -1) Items[itemIdx].price = 1;
	itemIdx = GetItemIndex("piratesJournal_2");
	if (itemIdx != -1) Items[itemIdx].price = 1;
	itemIdx = GetItemIndex("piratesJournal_3");
	if (itemIdx != -1) Items[itemIdx].price = 1;
}
