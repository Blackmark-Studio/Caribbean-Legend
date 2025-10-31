
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

    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_MERCHANT,  1, 1, 6, 6);
    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SMALL, SHIP_SPEC_UNIVERSAL, 1, 1, 6, 6);
    SetEncSlot_SpecRandom(ENCOUNTER_TYPE_MERCHANT_SMALL, 1, 0, 0, 1);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Торговый караван - Средний
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_MEDIUM]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "bark";
	Enc_ExcludeNation(rEnc, PIRATE);

    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_MERCHANT,  1, 1, 5, 5);
    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_MEDIUM, SHIP_SPEC_UNIVERSAL, 1, 1, 5, 5);
    SetEncSlot_SpecRandom(ENCOUNTER_TYPE_MERCHANT_MEDIUM, 1, 0, 0, 1);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Торговый караван - Большой
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_LARGE]);
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "galleon";
	Enc_ExcludeNation(rEnc, PIRATE);

    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_MERCHANT,  1, 1, 4, 4);
    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_LARGE, SHIP_SPEC_UNIVERSAL, 1, 1, 4, 4);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Торговая экспедиция - Средняя (Коронный торговец)
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_CROWN]);
    rEnc.Chance = 100;
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "bark";
	Enc_ExcludeNation(rEnc, PIRATE);

    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_MERCHANT,  1, 1, 3, 4);
    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_CROWN, SHIP_SPEC_WAR,       1, 1, 3, 5);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Торговая экспедиция - Большая
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_EXPEDITION]);
    rEnc.Chance = 80;
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "galleon";
	Enc_ExcludeNation(rEnc, PIRATE);

    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_MERCHANT,  1, 1, 2, 4);
    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_UNIVERSAL, 0, 1, 3, 4);
    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_EXPEDITION, SHIP_SPEC_WAR,       1, 1, 2, 3);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Работорговцы
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_MERCHANT_SLAVES]);
 	rEnc.Chance = 80;
	rEnc.Type = ENCOUNTER_TRADE;
	rEnc.worldMapShip = "galleon";
	Enc_ExcludeNation(rEnc, PIRATE);

    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_MERCHANT,  1, 1, 2, 4);
    SetEncSlot_Params(ENCOUNTER_TYPE_MERCHANT_SLAVES, SHIP_SPEC_WAR,       1, 1, 2, 4);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Военная эскадра - Средняя
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_NAVAL_MEDIUM]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.worldMapShip = "frigate";
	Enc_ExcludeNation(rEnc, PIRATE);

    SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_MERCHANT,  1, 1, 6, 6);
    SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_MEDIUM, SHIP_SPEC_WAR,       1, 1, 5, 5);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Военная эскадра - Большая
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_NAVAL_LARGE]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.worldMapShip = "manowar";
	Enc_ExcludeNation(rEnc, PIRATE);

    SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_RAIDER,    1, 1, 3, 4);
    SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_MERCHANT,  1, 1, 3, 3);
    SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_UNIVERSAL, 1, 1, 3, 4);
    SetEncSlot_Params(ENCOUNTER_TYPE_NAVAL_LARGE, SHIP_SPEC_WAR,       2, 2, 2, 3);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Патруль - Малый
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PATROL_SMALL]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.worldMapShip = "bark";
	Enc_ExcludeNation(rEnc, PIRATE);

    SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_SMALL, SHIP_SPEC_RAIDER,    1, 1, 6, 6);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Патруль - Средний
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_PATROL_MEDIUM]);
	rEnc.Type = ENCOUNTER_WAR;
	rEnc.worldMapShip = "frigate";
	Enc_ExcludeNation(rEnc, PIRATE);

    SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_MEDIUM, SHIP_SPEC_RAIDER,    1, 1, 3, 5);
    SetEncSlot_Params(ENCOUNTER_TYPE_PATROL_MEDIUM, SHIP_SPEC_WAR,       1, 1, 4, 5);

	///////////////////////////////////////////////////////////////////////////////////////
	/// Контрабандисты (TO_DO)
	///////////////////////////////////////////////////////////////////////////////////////
	makeref(rEnc, EncountersTypes[ENCOUNTER_TYPE_SMUGGLERS]);
 	rEnc.Chance = 0;
	rEnc.Skip   = true;
    rEnc.worldMapShip = "boat";
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
    iGPThreatMax = THREAT_LVL_1;
    Enc_ExcludeNation(rEnc, ENGLAND);
	Enc_ExcludeNation(rEnc, FRANCE);
	Enc_ExcludeNation(rEnc, SPAIN);
	Enc_ExcludeNation(rEnc, HOLLAND);

    SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_RAIDER,    1, 1, 6, 6);
    SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_UNIVERSAL, 1, 1, 6, 6);
    SetEncSlot_Params(ENCOUNTER_TYPE_PIRATE, SHIP_SPEC_WAR,       1, 1, 6, 6);
    SetEncSlot_SpecRandom(ENCOUNTER_TYPE_PIRATE, 0, 1, 1, 1);

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

void InitEncountersBaseWeight()
{
    EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SMALL]  = 27;
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_SMALL] = 27;

    EncWeightCur[ENCOUNTER_TYPE_MERCHANT_MEDIUM]  = 17;
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_MEDIUM] = 17;

    EncWeightCur[ENCOUNTER_TYPE_MERCHANT_LARGE]  = 11;
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_LARGE] = 11;

    EncWeightCur[ENCOUNTER_TYPE_MERCHANT_CROWN]  = 5;
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_CROWN] = 5;

    EncWeightCur[ENCOUNTER_TYPE_MERCHANT_EXPEDITION]  = 4;
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_EXPEDITION] = 4;

    EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SLAVES]  = 6;
    EncWeightBase[ENCOUNTER_TYPE_MERCHANT_SLAVES] = 6;

    EncWeightCur[ENCOUNTER_TYPE_PATROL_SMALL]  = 9;
    EncWeightBase[ENCOUNTER_TYPE_PATROL_SMALL] = 9;

    EncWeightCur[ENCOUNTER_TYPE_PATROL_MEDIUM]  = 8;
    EncWeightBase[ENCOUNTER_TYPE_PATROL_MEDIUM] = 8;

    EncWeightCur[ENCOUNTER_TYPE_NAVAL_MEDIUM]  = 4;
    EncWeightBase[ENCOUNTER_TYPE_NAVAL_MEDIUM] = 4;

    EncWeightCur[ENCOUNTER_TYPE_NAVAL_LARGE]  = 3;
    EncWeightBase[ENCOUNTER_TYPE_NAVAL_LARGE] = 3;

    EncWeightCur[ENCOUNTER_TYPE_SMUGGLERS]  = 0;
    EncWeightBase[ENCOUNTER_TYPE_SMUGGLERS] = 0;

    EncWeightCur[ENCOUNTER_TYPE_PIRATE]  = 8;
    EncWeightBase[ENCOUNTER_TYPE_PIRATE] = 8;
}
