
void SZN_ChangeEncounters(string seasonName)
{
	// EncWeightCur[ENCOUNTER_TYPE_SMUGGLERS] здесь не переопределяется
	switch (seasonName)
	{
		case CROWN_SEASON:
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_CROWN] = 9;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_EXPEDITION] = 7;
			EncWeightCur[ENCOUNTER_TYPE_PATROL_SMALL]= 14;
			EncWeightCur[ENCOUNTER_TYPE_PATROL_MEDIUM] = 12;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SMALL] = 19;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_MEDIUM] = 12;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_LARGE] = 8;
			EncWeightCur[ENCOUNTER_TYPE_PIRATE] = 3;
			EncWeightCur[ENCOUNTER_TYPE_NAVAL_MEDIUM] = 4;
			EncWeightCur[ENCOUNTER_TYPE_NAVAL_LARGE] = 3;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SLAVES] = 5;

			SeasonSystem.rates.fight = WDM_WARRING_RATE;
			SeasonSystem.rates.storm = WDM_STORM_RATE * 0.45;
			SeasonSystem.rates.special = WDM_SPECIAL_RATE * 0.30;
			SeasonSystem.rates.general = WDM_GENERAL_RATE * 1.40;
		break;
		case REED_SEASON:
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_CROWN] = 5;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_EXPEDITION] = 4;
			EncWeightCur[ENCOUNTER_TYPE_PATROL_SMALL]= 9;
			EncWeightCur[ENCOUNTER_TYPE_PATROL_MEDIUM] = 8;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SMALL] = 27;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_MEDIUM] = 17;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_LARGE] = 11;
			EncWeightCur[ENCOUNTER_TYPE_PIRATE] = 8;
			EncWeightCur[ENCOUNTER_TYPE_NAVAL_MEDIUM] = 2;
			EncWeightCur[ENCOUNTER_TYPE_NAVAL_LARGE] = 1;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SLAVES] = 9;

			SeasonSystem.rates.fight = WDM_WARRING_RATE * 0.80;
			SeasonSystem.rates.storm = WDM_STORM_RATE * 0.70;
			SeasonSystem.rates.special = WDM_SPECIAL_RATE * 0.70;
			SeasonSystem.rates.general = WDM_GENERAL_RATE * 1.20;
		break;
		case STORM_SEASON:
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_CROWN] = 4;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_EXPEDITION] = 3;
			EncWeightCur[ENCOUNTER_TYPE_PATROL_SMALL]= 5;
			EncWeightCur[ENCOUNTER_TYPE_PATROL_MEDIUM] = 4;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SMALL] = 14;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_MEDIUM] = 9;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_LARGE] = 6;
			EncWeightCur[ENCOUNTER_TYPE_PIRATE] = 5;
			EncWeightCur[ENCOUNTER_TYPE_NAVAL_MEDIUM] = 3;
			EncWeightCur[ENCOUNTER_TYPE_NAVAL_LARGE] = 2;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SLAVES] = 3;

			SeasonSystem.rates.fight = WDM_WARRING_RATE * 0.50;
			SeasonSystem.rates.storm = WDM_STORM_RATE * 1.75;
			SeasonSystem.rates.special = WDM_SPECIAL_RATE * 1.80;
			SeasonSystem.rates.general = WDM_GENERAL_RATE * 0.50;
		break;
		case SHADOW_SEASON:
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_CROWN] = 3;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_EXPEDITION] = 2;
			EncWeightCur[ENCOUNTER_TYPE_PATROL_SMALL]= 7;
			EncWeightCur[ENCOUNTER_TYPE_PATROL_MEDIUM] = 6;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SMALL] = 10;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_MEDIUM] = 6;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_LARGE] = 4;
			EncWeightCur[ENCOUNTER_TYPE_PIRATE] = 15;
			EncWeightCur[ENCOUNTER_TYPE_NAVAL_MEDIUM] = 7;
			EncWeightCur[ENCOUNTER_TYPE_NAVAL_LARGE] = 6;
			EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SLAVES] = 6;

			SeasonSystem.rates.fight = WDM_WARRING_RATE * 1.60;
			SeasonSystem.rates.storm = WDM_STORM_RATE * 1.00;
			SeasonSystem.rates.special = WDM_SPECIAL_RATE * 1.00;
			SeasonSystem.rates.general = WDM_GENERAL_RATE * 0.70;
		break;
	}

	EncWeightBase = EncWeightCur;
}
