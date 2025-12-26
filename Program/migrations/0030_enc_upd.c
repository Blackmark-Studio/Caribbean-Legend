
void ApplyMigration(ref migrationState)
{
    EncountersInit();
    for(int i = 0; i < 60; i++) EncProgress[i] = false;
	Encounter_Progress();
    PChar.quest.PirateNotificationUPD.over = "yes";
	
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
		
		if(sti(RealShips[i].BaseType) == SHIP_RENOVATED_FDM)
		{
			RealShips[i].Name = "NewFlyingdutchman1";  
		}
	}
	
	i = FindLocation("Tortuga_town");
	locations[i].models.always.L1 = "Margarita_GPK_signsA";
}
