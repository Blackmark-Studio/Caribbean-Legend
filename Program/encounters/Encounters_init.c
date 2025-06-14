
// INIT Базовых эскадр
// Изменения по уровням в Encounter_Progress

void InitEncounters()
{
	int i;
	ref rEnc;

	for (i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		makeref(rEnc, EncountersTypes[i]);
		rEnc.Index = i;
		rEnc.Chance = 150;
		rEnc.Skip = false;
		rEnc.Type = ENCOUNTER_TRADE;
	}

	// boal баг фикс для квестовых, а то генерились в К3
    makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_ALONE]);
 	rEnc.Chance = 0;
	rEnc.Skip   = true;

	///////////////////////////////////////////////////////////////////////////////////////
	/// Торговый караван - Малый
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_SMALL]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "sloop";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 2, 5, 6);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      0, 1, 5, 6);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      0, 1, 5, 6);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Торговый караван - Средний
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_MEDIUM]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "bark";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 3, 3, 5);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      0, 1, 4, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      1, 2, 3, 5);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Торговый караван - Большой
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_LARGE]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "galleon";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 2, 4, 2, 3);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 2, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      1, 2, 3, 4);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Торговая экспедиция - Средняя (Коронный торговец)
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_CROWN]);
    rEnc.Chance = 100;
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "bark";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 1, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 2, 4, 5);
    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      1, 1, 3, 5);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Торговая экспедиция - Большая
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_EXPEDITION]);
    rEnc.Chance = 80;
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "galleon";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 1, 2, 3);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 2, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      0, 1, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      1, 2, 2, 3);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Работорговцы
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_SLAVES]);
 	rEnc.Chance = 80;
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "galleon";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 2, 2, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 1, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      1, 1, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      0, 1, 3, 4);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Военная эскадра - Средняя
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_NAVAL_MEDIUM]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.worldMapShip = "frigate";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      1, 2, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      0, 1, 4, 5);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      0, 1, 4, 5);
    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 1, 5, 5);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Военная эскадра - Большая
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_NAVAL_LARGE]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.worldMapShip = "manowar";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      2, 3, 2, 3);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 2, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_UNIVERSAL, "War",      1, 1, 3, 4);
    Enc_AddShips(rEnc, SHIP_SPEC_MERCHANT,  "Merchant", 1, 1, 3, 3);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Патруль - Малый
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PATROL_SMALL]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.worldMapShip = "bark";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      0, 1, 5, 6);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 2, 5, 6);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Патруль - Средний
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PATROL_MEDIUM]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.worldMapShip = "frigate";
	Enc_ExcludeNation(rEnc, PIRATE);

    Enc_AddShips(rEnc, SHIP_SPEC_WAR,       "War",      1, 1, 4, 5);
    Enc_AddShips(rEnc, SHIP_SPEC_RAIDER,    "War",      1, 3, 3, 5);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Контрабандисты (TO_DO)
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_SMUGGLERS]);
 	rEnc.Chance = 0;
	rEnc.Skip   = true;
	Enc_ExcludeNation(rEnc, ENGLAND);
	Enc_ExcludeNation(rEnc, FRANCE);
	Enc_ExcludeNation(rEnc, SPAIN);
	Enc_ExcludeNation(rEnc, HOLLAND);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Пираты
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PIRATE]);
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

	///////////////////////////////////////////////////////////////////////////////////////
	/// Бочонок
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_BARREL]);
	rEnc.Type = ENCOUNTER_SPECIAL;
	rEnc.Chance = 45;
	rEnc.worldMapShip = "barrel";
	Enc_ExcludeNation(rEnc, PIRATE);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Кораблекрушенец
	/////////////////////////////////////////////////////////////////////////////////////// 
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_BOAT]);
	rEnc.Type = ENCOUNTER_SPECIAL;
	rEnc.Chance = 25;
	rEnc.worldMapShip = "boat";

	Trace("Init encounters complete.");
}