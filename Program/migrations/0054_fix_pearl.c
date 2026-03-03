
void ApplyMigration(ref migrationState)
{
	MAX_ISLANDS = GetArraySize(&Islands);
	worldMap.labels.Pearl.text = GetIslandNameByID("Pearl");
}
