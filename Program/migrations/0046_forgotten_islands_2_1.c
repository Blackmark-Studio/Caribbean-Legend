
void ApplyMigration(ref migrationState)
{
	worldMap.labels.Pearl.text = GetIslandNameByID("Pearl");

	int n = FindIsland("IslaMona");
	Islands[n].reload.l2.go = "Shore76";
	Islands[n].reload.l2.emerge = "sea";
	Islands[n].reload.l2.disable = true;

	n = FindIsland("Ksochitam");
	Islands[n].reload.l2.go = "Shore66";
	Islands[n].reload.l2.emerge = "sea";
	Islands[n].reload.l2.disable = true;
}
