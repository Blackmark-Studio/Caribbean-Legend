
void ApplyMigration(ref migrationState)
{
    if (!CheckAttribute(&objControlsState, "map.controls.Rest"))
	{
        CI_CreateAndSetControls("PrimaryLand", "Rest", CI_GetKeyCode("KEY_T"), 0, true);
        MapControlToGroup("Rest","BattleInterfaceControls");
    }

	if (LoadSegment("battle_interface\fast_reload_table.c"))
	{
		initFastReloadTable();
		UnloadSegment("battle_interface\fast_reload_table.c");
	}

    ref rLoc = FindLocationById("Villemstad_KeepersHouse");
    rLoc.fastreload = "Villemstad";
    rLoc = FindLocationById("Havana_KeepersHouse");
    rLoc.fastreload = "Havana";
    rLoc = FindLocationById("PortRoyal_KeepersHouse");
    rLoc.fastreload = "PortRoyal";
    rLoc = FindLocationById("Charles_KeepersHouse");
    rLoc.fastreload = "Charles";
}
