void ApplyMigration(ref migrationState) {
	GEN_ApplyPlayerDifficulty(pchar);
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.EnergyMod")) {
		float mod = stf(pchar.questTemp.ChickenGod.EnergyMod);
		ChickenGod_ModifyStats(mod);
	}
}
