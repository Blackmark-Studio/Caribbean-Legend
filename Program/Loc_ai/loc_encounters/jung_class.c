
object JungleEncList; // JEL

void JEL_AddEncounter(string sName, int iBaseWeight)
{
    aref arEnc = touchattr(JungleEncList.Data.(sName));
    arEnc.BaseWeight := iBaseWeight;
    arEnc.CurWeight  := iBaseWeight;
    arEnc.isValid  := fref("JungleEncCheck_" + sName);
    arEnc.Generate := fref("JungleEncGenerate_" + sName);
}

void JEL_DeleteEncounter(string sName)
{
    DeleteAttribute(&JungleEncList, "Data." + sName);
}

// New logic (discrete distribution)
aref JEL_GetRandomEnc(ref loc)
{
    int Weights[];
    aref aData = &JungleEncList.Data;
    @Weights = @aData;

    int Summ = -1;
    for (int i = 0; i < @aData; i++)
    {
        Weights[i] = aData[i].CurWeight;
        Summ += Weights[i];
	}

    int n = rand(Summ);
    for (int i = 0; n >= 0; i++)
	{
		if (Weights[i] > 0)
            n -= Weights[i];
	}

    return aData[i-1];
}

// Old logic for uninhabited islands
aref JEL_GetUninhabited(ref loc)
{
    // Крушенцы
    if (loc.type == "seashore")
    {
        if (rand(4) == 1)
            return rand(1) ? &JungleEncList.Data.PiratesOnUninhabited : &JungleEncList.Data.ShipWreck;

        return &JungleEncList.Data.None;
    }

    // Индейцы
    return rand(10) > 7 ? &JungleEncList.Data.None : &JungleEncList.Data.Indians;
}

void JEL_UpdateWeights(string sChosen)
{
    aref aData = &JungleEncList.Data;
    for (int i = 0; i < @aData; i++)
    {
        aref aEnc = aData[i];
        if (aEnc.BaseWeight == 0) continue; // Always skip
        if (nameattr(aEnc) != sChosen)
        {
            aEnc.CurWeight += aEnc.BaseWeight / 4;
            if (aEnc.CurWeight > 1000)
                aEnc.CurWeight := 1000;
        }
        else aEnc.CurWeight := 1;
    }
}

float JEL_CalcChancePercent(aref aEnc)
{
    float fSumm = 0.0;
    aref aData = &JungleEncList.Data;
    for (int i = 0; i < @aData; i++)
         fSumm += aData[i].CurWeight;
    return 100.0 * float(aEnc.CurWeight) / fSumm;
}

void JungleEncountersInit()
{
    // Create class
    JungleEncList.AddEncounter    := &JEL_AddEncounter;
    JungleEncList.DeleteEncounter := &JEL_DeleteEncounter;
    JungleEncList.GetRandomEnc    := &JEL_GetRandomEnc;
    JungleEncList.GetUninhabited  := &JEL_GetUninhabited;
    JungleEncList.UpdateWeights   := &JEL_UpdateWeights;

    // Default encounters
    JungleEncList.AddEncounter("None",         210);
    JungleEncList.AddEncounter("Bitch",         65);
    JungleEncList.AddEncounter("Fight",         70);
    JungleEncList.AddEncounter("Corpse",        95);
    JungleEncList.AddEncounter("Patrol",        60);
    JungleEncList.AddEncounter("Bandits",       80);
    JungleEncList.AddEncounter("Slaves",        50);
    JungleEncList.AddEncounter("Indians",       75);
    JungleEncList.AddEncounter("Smugglers",     50);
    JungleEncList.AddEncounter("Alone_Citiz",   80);
    JungleEncList.AddEncounter("Alone_Sold",    60);
    JungleEncList.AddEncounter("Alone_Indian",  55);
    JungleEncList.AddEncounter("Alone_Injured", 50);

    // Uninhabited encounters
    JungleEncList.AddEncounter("ShipWreck", 0);
    JungleEncList.AddEncounter("PiratesOnUninhabited", 0);
}
