
void ApplyMigration(ref migrationState)
{
    ref sld;
    int iChar, i;

    // Фикс фортов
    for (i=0; i<MAX_COLONIES; i++)
	{
		if(Colonies[i].nation == "none") continue;
		if(CheckAttribute(&Colonies[i], "HasNoFort")) continue;
        if(!CheckAttribute(&Colonies[i], "Commander")) continue;

		iChar = GetCharacterIndex(Colonies[i].Commander);
        if(iChar == -1) continue;
        sld = &Characters[iChar];
        sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS48;
	}

    // Китаец
    if(CharacterIsAlive("Longway_FP"))
    {
        sld = CharacterFromId("Longway_FP");
        sld.CanTakeMushket = true;
    }

    // Правки энок (реинит)
    ref  rEnc;
    aref aShip;

	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_CROWN]);
    DeleteAttribute(rEnc, "Ships");
    rEnc.Index = ENCOUNTER_TYPE_MERCHANT_CROWN;
    rEnc.Chance = 100;
    rEnc.Skip = false;
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "bark";
	Enc_ExcludeNation(rEnc, PIRATE);
    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 1, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 2, 4, 5);
    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      1, 1, 3, 5);

	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_EXPEDITION]);
    DeleteAttribute(rEnc, "Ships");
    rEnc.Index = ENCOUNTER_TYPE_MERCHANT_EXPEDITION;
    rEnc.Chance = 80;
    rEnc.Skip = false;
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "galleon";
	Enc_ExcludeNation(rEnc, PIRATE);
    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 1, 2, 3);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 2, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      0, 1, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      1, 2, 2, 3);

	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PIRATE]);
    DeleteAttribute(rEnc, "Ships");
    rEnc.Index = ENCOUNTER_TYPE_PIRATE;
    rEnc.Chance = 150;
    rEnc.Skip = false;
 	rEnc.Type = ENCOUNTER_WAR;
    rEnc.worldMapShip = "sloop";
    rEnc.Stage = 0;
	Enc_ExcludeNation(rEnc, ENGLAND);
	Enc_ExcludeNation(rEnc, FRANCE);
	Enc_ExcludeNation(rEnc, SPAIN);
	Enc_ExcludeNation(rEnc, HOLLAND);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 1, 6, 6);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      0, 1, 6, 6);
    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      0, 1, 6, 6);

	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_SLAVES]);
    DeleteAttribute(rEnc, "Ships");
    rEnc.Index = ENCOUNTER_TYPE_MERCHANT_SLAVES;
    rEnc.Chance = 80;
    rEnc.Skip = false;
 	rEnc.Type = ENCOUNTER_TRADE;
    rEnc.worldMapShip = "galleon";
    Enc_ExcludeNation(rEnc, PIRATE);
    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 2, 2, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 1, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      1, 1, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      0, 1, 3, 4);

    int Rank = sti(PChar.Rank);
    if(Rank >= 9)
    {
        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PIRATE];
        rEnc.Stage = 1;
        Enc_ConvertShipsCls(rEnc, "All", 5, 6);
        Enc_AddShips(rEnc, SHIP_SPEC_WAR, "War", 1, 1, 5, 6);
		PChar.quest.Pirate_Notification.win_condition.l1 = "MapEnter";
	    PChar.quest.Pirate_Notification.function         = "PirateNotificationUPD";
    }
    if(Rank >= 12)
    {
        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_CROWN];
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 4, 5);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_EXPEDITION];
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 2, 2);
        Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT, "Merchant", 1, 1, 2, 2);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_SLAVES];
        Enc_AddShips(rEnc, SHIP_SPEC_RAIDER, "War", 1, 1, 3, 4);
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 3, 4);
        Enc_ConvertShipsCls(rEnc, SHIP_SPEC_MERCHANT, 2, 2);
    }
    if(Rank >= 17)
    {
        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PIRATE];
        rEnc.Stage = 2;
        rEnc.worldMapShip = "bark";
        Enc_ConvertShipsCls(rEnc, "All", 4, 5);
        Enc_AddShips(rEnc, SHIP_SPEC_RAIDER, "War", 1, 1, 4, 5);
		PChar.quest.Pirate_Notification.win_condition.l1 = "MapEnter";
	    PChar.quest.Pirate_Notification.function         = "PirateNotificationUPD";
    }
    if(Rank >= 22)
    {
        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_CROWN];
        Enc_ConvertShipsCls(rEnc, SHIP_SPEC_RAIDER, 3, 5);
        Enc_ConvertShipsCls(rEnc, SHIP_SPEC_UNIVERSAL, 3, 5);

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_EXPEDITION];
        Enc_ConvertShipsCls(rEnc, SHIP_SPEC_RAIDER, 2, 4);
        aShip = Enc_FindShip(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 2, 2);
        aShip.ShipSpec = SHIP_SPEC_WAR;
    }
    if(Rank >= 26)
    {
        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PIRATE];
        rEnc.Stage = 3;
        Enc_ConvertShipsCls(rEnc, "All", 3, 4);
        Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War", 1, 1, 3, 4);
		PChar.quest.Pirate_Notification.win_condition.l1 = "MapEnter";
	    PChar.quest.Pirate_Notification.function         = "PirateNotificationUPD";
    }
    if(Rank >= 31)
    {
        rEnc = &EncountersTypes[ENCOUNTER_TYPE_PIRATE];
        rEnc.Stage = 4;
        rEnc.worldMapShip = "frigate";
        Enc_ConvertShipsCls(rEnc, "All", 2, 3);
		PChar.quest.Pirate_Notification.win_condition.l1 = "MapEnter";
	    PChar.quest.Pirate_Notification.function         = "PirateNotificationUPD";

        rEnc = &EncountersTypes[ENCOUNTER_TYPE_MERCHANT_SLAVES];
        Enc_AddShips(rEnc, SHIP_SPEC_WAR, "War", 1, 1, 2, 2);
        Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT, "Merchant", 1, 1, 2, 2);
    }
}
