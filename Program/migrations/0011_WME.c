void ApplyMigration(ref migrationState)
{
	if (CheckAttribute(PChar, "worldmapencountersoff"))
    {
		bEncOffGlobal = sti(PChar.worldmapencountersoff);
        DeleteAttribute(PChar, "worldmapencountersoff");
    }

	EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SMALL]  = 22;
	EncWeightBase[ENCOUNTER_TYPE_MERCHANT_SMALL] = 22;
	EncWeightCur[ENCOUNTER_TYPE_MERCHANT_MEDIUM]  = 14;
	EncWeightBase[ENCOUNTER_TYPE_MERCHANT_MEDIUM] = 14;
	EncWeightCur[ENCOUNTER_TYPE_MERCHANT_LARGE]  = 8;
	EncWeightBase[ENCOUNTER_TYPE_MERCHANT_LARGE] = 8;
	EncWeightCur[ENCOUNTER_TYPE_MERCHANT_CROWN]  = 4;
	EncWeightBase[ENCOUNTER_TYPE_MERCHANT_CROWN] = 4;
	EncWeightCur[ENCOUNTER_TYPE_MERCHANT_EXPEDITION]  = 3;
	EncWeightBase[ENCOUNTER_TYPE_MERCHANT_EXPEDITION] = 3;
	EncWeightCur[ENCOUNTER_TYPE_MERCHANT_SLAVES]  = 6;
	EncWeightBase[ENCOUNTER_TYPE_MERCHANT_SLAVES] = 6;
	EncWeightCur[ENCOUNTER_TYPE_PATROL_SMALL] = 10;
	EncWeightBase[ENCOUNTER_TYPE_PATROL_SMALL] = 10;
	EncWeightCur[ENCOUNTER_TYPE_PATROL_MEDIUM]  = 9;
	EncWeightBase[ENCOUNTER_TYPE_PATROL_MEDIUM] = 9;
	EncWeightCur[ENCOUNTER_TYPE_NAVAL_MEDIUM]  = 4;
	EncWeightBase[ENCOUNTER_TYPE_NAVAL_MEDIUM] = 4;
	EncWeightCur[ENCOUNTER_TYPE_NAVAL_LARGE]  = 3;
	EncWeightBase[ENCOUNTER_TYPE_NAVAL_LARGE] = 3;
	EncWeightCur[ENCOUNTER_TYPE_SMUGGLERS]  = 0;
	EncWeightBase[ENCOUNTER_TYPE_SMUGGLERS] = 0;
	EncWeightCur[ENCOUNTER_TYPE_PIRATE]  = 22;
	EncWeightBase[ENCOUNTER_TYPE_PIRATE] = 22;

	bool bSingleItems[22];
	bSingleItems[0]  = CheckAttribute(&TreasureTiers[0], "indian_poison");
	bSingleItems[1]  = CheckAttribute(&TreasureTiers[0], "blade_29");
	bSingleItems[2]  = CheckAttribute(&TreasureTiers[0], "suit4");
	bSingleItems[3]  = CheckAttribute(&TreasureTiers[0], "underwater");
	bSingleItems[4]  = CheckAttribute(&TreasureTiers[0], "cirass9");
	bSingleItems[5]  = CheckAttribute(&TreasureTiers[0], "topor_06");
	bSingleItems[6]  = CheckAttribute(&TreasureTiers[0], "blade_28");
	bSingleItems[7]  = CheckAttribute(&TreasureTiers[0], "blade_41");
	bSingleItems[8]  = CheckAttribute(&TreasureTiers[0], "knife_02");
	bSingleItems[9]  = CheckAttribute(&TreasureTiers[0], "blade_36");
	bSingleItems[10] = CheckAttribute(&TreasureTiers[0], "blade_32");
	bSingleItems[11] = CheckAttribute(&TreasureTiers[0], "Mushket2x2");
	bSingleItems[12] = CheckAttribute(&TreasureTiers[0], "pistol7");
	bSingleItems[13] = CheckAttribute(&TreasureTiers[0], "spyglass5");
	bSingleItems[14] = CheckAttribute(&TreasureTiers[0], "recipe_GunEchin");
	bSingleItems[15] = CheckAttribute(&TreasureTiers[0], "Mineral32");
	bSingleItems[16] = CheckAttribute(&TreasureTiers[0], "Tigel");
	bSingleItems[17] = CheckAttribute(&TreasureTiers[0], "chemistry");
	bSingleItems[18] = CheckAttribute(&TreasureTiers[0], "Map_Best");
	bSingleItems[19] = CheckAttribute(&TreasureTiers[0], "sextant2");
    bSingleItems[20] = CheckAttribute(&TreasureTiers[0], "QuestSlot.LoyaltyPack");
    bSingleItems[21] = CheckAttribute(&TreasureTiers[0], "QuestSlot.LadyBeth");
    int i, j, idx;
    for (i = 0; i <= 15; i++)
    {
        DeleteAttribute(&TreasureTiers[i], "");
    }
	TreasureTiersInit(SandBoxMode);
	if(!bSingleItems[0])  DeleteUniqTreasure("Special", "indian_poison");
	if(!bSingleItems[1])  DeleteUniqTreasure("Equip", "blade_29");
	if(!bSingleItems[2])  DeleteUniqTreasure("Equip", "suit4");
	if(!bSingleItems[3])  DeleteUniqTreasure("Equip", "underwater");
	if(!bSingleItems[4])  DeleteUniqTreasure("Equip", "cirass9");
	if(!bSingleItems[5])  DeleteUniqTreasure("Equip", "topor_06");
	if(!bSingleItems[6])  DeleteUniqTreasure("Equip", "blade_28");
	if(!bSingleItems[7])  DeleteUniqTreasure("Equip", "blade_41");
	if(!bSingleItems[8])  DeleteUniqTreasure("Equip", "knife_02");
	if(!bSingleItems[9])  DeleteUniqTreasure("Equip", "blade_36");
	if(!bSingleItems[10]) DeleteUniqTreasure("Equip", "blade_32");
	if(!bSingleItems[11]) DeleteUniqTreasure("Equip", "Mushket2x2");
	if(!bSingleItems[12]) DeleteUniqTreasure("Equip", "pistol7");
	if(!bSingleItems[13]) DeleteUniqTreasure("Equip", "spyglass5");
	if(!bSingleItems[14]) DeleteUniqTreasure("Jewelry", "recipe_GunEchin");
	if(!bSingleItems[15]) DeleteUniqTreasure("Jewelry", "Mineral32");
	if(!bSingleItems[16]) DeleteUniqTreasure("Jewelry", "Tigel");
	if(!bSingleItems[17]) DeleteUniqTreasure("Jewelry", "chemistry");
	if(!bSingleItems[18]) DeleteUniqTreasure("Special", "Map_Best");
	if(!bSingleItems[19]) DeleteUniqTreasure("Special", "sextant2");
    if(!bSingleItems[20]) DeleteAttribute(&TreasureTiers[0], "QuestSlot.LoyaltyPack");
    if(bSingleItems[21])  TreasureTiers[0].QuestSlot.LadyBeth = "LadyBeth_Treasure";

    ref rChar;
    string id;
    for (i = 1; i <= 4; i++)
    {
        for (j = 0; j < MAX_NATIONS; j++)
        {
            id = NationShortName(j)+"Hunter0"+i;
            idx = GetCharacterIndex(id);
            if (idx != -1)
            {
                rChar = CharacterFromID(id);
                rChar.mapEnc.Marker = "BountyHunter";
            }
        }
    }
    for (i = 1; i <= 6; i++)
    {
        for (j = 0; j < MAX_NATIONS; j++)
        {
            id = NationShortName(j)+"Brigadier0"+i;
            idx = GetCharacterIndex(id);
            if (idx != -1)
            {
                rChar = CharacterFromID(id);
                rChar.mapEnc.Marker = "Brigadier";
            }
        }
    }
}

void DeleteUniqTreasure(string sType, string sItem)
{
	for(i = 1; i <= 15; i++)
	{
		DeleteAttribute(&TreasureTiers[i], sType + "." + sItem);
	}
	DeleteAttribute(&TreasureTiers[0], sItem);
}
