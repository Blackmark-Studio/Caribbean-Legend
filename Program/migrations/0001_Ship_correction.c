
void ApplyMigration(ref migrationState)
{
    ref rBaseShip;
    int i, iClass, iSpec;
    float fSpec;

    for(i = SHIP_TARTANE; i < SHIP_FORT; i++)
    {
        rBaseShip = &ShipsTypes[i];
        if(CheckAttribute(rBaseShip, "Power"))
        {
            iClass = sti(rBaseShip.Class);
            iSpec  = sti(rBaseShip.Spec);
            switch(iSpec)
            {
                case SHIP_SPEC_MERCHANT:	fSpec = 0.75;	break;
                case SHIP_SPEC_UNIVERSAL:	fSpec = 1.1;	break;
                case SHIP_SPEC_RAIDER:		fSpec = 1.3;	break;
                case SHIP_SPEC_WAR:			fSpec = 1.5;	break;
            }
            rBaseShip.Power = 23.0 * (7.0 - iClass) * 1.6 * fSpec;
        }
    }

    ShipsTypes[SHIP_LSHIP_FRA].CanEncounter = true;
    ShipsTypes[SHIP_LSHIP_HOL].CanEncounter = true;
    ShipsTypes[SHIP_LSHIP_SPA].CanEncounter = true;
    ShipsTypes[SHIP_LSHIP_ENG].CanEncounter = true;
    ShipsTypes[SHIP_EASTINDIAMAN].Type.War  = true;

    if(CheckAttribute(PChar, "quest.SeaHunterCheck"))
        PChar.quest.SeaHunterCheck.over = "yes";
    SetFunctionTimerCondition("SeaHunterCheck_eng", 0, 0, 6, true);
    SetFunctionTimerCondition("SeaHunterCheck_fra", 0, 0, 6, true);
    SetFunctionTimerCondition("SeaHunterCheck_spa", 0, 0, 6, true);
    SetFunctionTimerCondition("SeaHunterCheck_hol", 0, 0, 6, true);

    SetFunctionTimerCondition("FireBrigade_spa", 0, 0, 5, true);
    if(SandBoxMode)
    {
        if(!CharacterIsAlive("Kneepel_FP"))
            SetFunctionTimerCondition("FireBrigade_eng", 0, 0, 5, true);
        if(!CharacterIsAlive("FraBrigadier"))
            SetFunctionTimerCondition("FireBrigade_fra", 0, 0, 5, true);
        if(!CharacterIsAlive("Longway_FP"))
            SetFunctionTimerCondition("FireBrigade_hol", 0, 0, 5, true);
    }
}
