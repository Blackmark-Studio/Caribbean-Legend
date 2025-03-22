void ApplyMigration(ref migrationState) {
	
	ref refShip;
	makeref(refShip,ShipsTypes[SHIP_BOAT]);
	refShip.ShipHolder = true;
	
	makeref(refShip,ShipsTypes[SHIP_LSHIP_FRA]);
	refShip.CanEncounter = false;
	
	makeref(refShip,ShipsTypes[SHIP_LSHIP_HOL]);
	refShip.CanEncounter = false;
	
	makeref(refShip,ShipsTypes[SHIP_LSHIP_SPA]);
	refShip.CanEncounter = false;
	
	makeref(refShip,ShipsTypes[SHIP_LSHIP_ENG]);
	refShip.CanEncounter = false;
	
	makeref(refShip,ShipsTypes[SHIP_QUEST3]);
	refship.QuestShip	= true;
	refship.ShipHolder	= true;
	
	makeref(refShip,ShipsTypes[SHIP_QUEST4]);
	refShip.ShipHolder  = true;
	
	makeref(refShip,ShipsTypes[SHIP_QUEST5]);
	refship.QuestShip	= true;
	refship.ShipHolder	= true;
	
	makeref(refShip,ShipsTypes[SHIP_QUEST6]);
	refship.ShipHolder	= true;
	
	makeref(refShip,ShipsTypes[SHIP_QUEST7]);
	refship.QuestShip	= true;
	refship.ShipHolder	= true;
	
	makeref(refShip,ShipsTypes[SHIP_QUEST8]);
	refship.QuestShip	= true;
	refship.ShipHolder	= true;
	
	makeref(refShip,ShipsTypes[SHIP_FORT]);
	refShip.ShipHolder  = true;
	
	makeref(refShip,ShipsTypes[SHIP_FORT + 1]);
	refShip.ShipHolder  = true;
}
