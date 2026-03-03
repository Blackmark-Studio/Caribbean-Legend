
void ApplyMigration(ref migrationState)
{
	ref refShip;
	makeref(refShip, ShipsTypes[SHIP_LSHIP_FRA]);
	refship.NationExclusive             = FRANCE;
	refship.NationalLineShip            = true;

	makeref(refShip, ShipsTypes[SHIP_LSHIP_HOL]);
	refship.NationExclusive             = HOLLAND;
	refship.NationalLineShip            = true;

	makeref(refShip, ShipsTypes[SHIP_LSHIP_SPA]);
	refship.NationExclusive             = SPAIN;
	refship.NationalLineShip            = true;

	makeref(refShip, ShipsTypes[SHIP_LSHIP_ENG]);
	refship.NationExclusive             = ENGLAND;
	refship.NationalLineShip            = true;
}
