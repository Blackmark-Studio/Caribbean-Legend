
// table service
string GetReputationName(int reputation)
{
		if(reputation<11)
				return "REPUTATIONT_BAD_4";
		if(reputation<21)
				return "REPUTATIONT_BAD_3";
		if(reputation<31)
				return "REPUTATIONT_BAD_2";
		if(reputation<41)
				return "REPUTATIONT_BAD_1";
		if(reputation<51)
				return "REPUTATIONT_NEUTRAL";
		if(reputation<61)
				return "REPUTATIONT_GOOD_1";
		if(reputation<71)
				return "REPUTATIONT_GOOD_2";
		if(reputation<81)
				return "REPUTATIONT_GOOD_3";
		if(reputation<=90)
				return "REPUTATIONT_GOOD_4";

	return "REPUTATIONT_GOOD_4";
}

string GetMoraleName(int morale)
{
	if(morale<10)
		return MoraleTable[MORALET_TREACHEROUS];
	if(morale<20)
		return MoraleTable[MORALET_AWFUL];
	if(morale<30)
		return MoraleTable[MORALET_LOW];
	if(morale<40)
		return MoraleTable[MORALET_POOR];
	if(morale<50)
		return MoraleTable[MORALET_NORMAL];
	if(morale<60)
		return MoraleTable[MORALET_ELATED];
	if(morale<70)
		return MoraleTable[MORALET_GOOD];
	if(morale<80)
		return MoraleTable[MORALET_HIGH];
	if(morale<90)
		return MoraleTable[MORALET_EXCELLENT];
	if(morale<=100)
		return MoraleTable[MORALET_HEROIC];
	return "";
}

string GetLoyalityName(int iLoyality)
{
	if(iLoyality<10)
		return LoyalityTable[MORALET_TREACHEROUS];
	if(iLoyality<20)
		return LoyalityTable[MORALET_AWFUL];
	if(iLoyality<30)
		return LoyalityTable[MORALET_LOW];
	if(iLoyality<40)
		return LoyalityTable[MORALET_POOR];
	if(iLoyality<50)
		return LoyalityTable[MORALET_NORMAL];
	if(iLoyality<60)
		return LoyalityTable[MORALET_ELATED];
	if(iLoyality<70)
		return LoyalityTable[MORALET_GOOD];
	if(iLoyality<80)
		return LoyalityTable[MORALET_HIGH];
	if(iLoyality<90)
		return LoyalityTable[MORALET_EXCELLENT];
	if(iLoyality<=100)
		return LoyalityTable[MORALET_HEROIC];
	return "";
}


int ChangeCharacterNationReputation(ref chref, int _Nation, int incr)
{
	return -ChangeCharacterHunterScore(chref, NationShortName(_Nation) + "hunter", -incr); // все наоборот, - это хорошо, + есть НЗГ
}

string GetNationReputation(ref chref, int _Nation)
{
		return GetNationReputationName(_Nation, ChangeCharacterNationReputation(chref, _Nation, 0));
}

string GetNationReputationName(int _Nation, int i)
{
	if (i <= -50)  return StringFromKey("RPGUtilite_14");
	if (i <= -30)  return StringFromKey("RPGUtilite_15");
	if (i <= -16)  return StringFromKey("RPGUtilite_16");
	if (i <= -10)  return StringFromKey("RPGUtilite_17");
	if (i <= 20)  return StringFromKey("RPGUtilite_18");
	if (i <= 50)  return StringFromKey("RPGUtilite_19");
	if (i <= 80)  return StringFromKey("RPGUtilite_20");
	if (i <= 100) return StringFromKey("RPGUtilite_21");

		return StringFromKey("RPGUtilite_18"); // Нейтралитет
}

string GetFactionReputationName(int i)
{
	if (i <= 5)  return StringFromKey("RPGUtilite_14");
	if (i <= 19)  return StringFromKey("RPGUtilite_15");
	if (i <= 39)  return StringFromKey("RPGUtilite_16");
	if (i <= 60)  return StringFromKey("RPGUtilite_18");
	if (i <= 80)  return StringFromKey("RPGUtilite_19");
	if (i <= 94)  return StringFromKey("RPGUtilite_20");
	if (i <= 100)  return StringFromKey("RPGUtilite_21");

	return StringFromKey("RPGUtilite_18"); // Нейтралитет
}
// boal 04.04.04
string NationShortName(int iNation)
{
	switch(iNation)
	{
		case ENGLAND:
		return "eng";
		break;
		case FRANCE:
		return "fra";
		break;
		case SPAIN:
		return "spa";
		break;
		case HOLLAND:
		return "hol";
		break;
		case PIRATE:
		return "pir";
		break;
	}
	return "eng";
}

// table service
string GetReputationComplexName(int reputation, string repName)
{	
	switch(repName)
	{
		case "fame" 	:
			if(reputation < 21)  return "REPUTATION_FAME_1";
			if(reputation < 41)  return "REPUTATION_FAME_2";
			if(reputation < 61)  return "REPUTATION_FAME_3";
			if(reputation < 81)  return "REPUTATION_FAME_4";
			return "REPUTATION_FAME_5";
		break;
		
		case "nobility" :
			if(reputation < 6)   return "REPUTATION_NOBILITY_1";
			if(reputation < 16)  return "REPUTATION_NOBILITY_2";
			if(reputation < 31)  return "REPUTATION_NOBILITY_3";
			if(reputation < 48)  return "REPUTATION_NOBILITY_4";
			if(reputation < 53)  return "REPUTATION_NOBILITY_5";
			if(reputation < 71)  return "REPUTATION_NOBILITY_6";
			if(reputation < 86)  return "REPUTATION_NOBILITY_7";
			if(reputation < 96)  return "REPUTATION_NOBILITY_8";
			return "REPUTATION_NOBILITY_9";
		break;
	}
}

string GetFullReputationComplexName(ref chref)
{
	string sReputation, sFame, sNobility;
	
	if(CheckAttribute(chref,"reputation.fame")) 
	{
		sFame = GetReputationComplexName(sti(chref.reputation.fame), "fame");
	}	
	else 
	{
		sFame = "REPUTATION_FAME_1";	
	}	
	
	if(CheckAttribute(chref,"reputation.nobility")) 
	{
		sNobility = GetReputationComplexName(sti(chref.reputation.nobility), "nobility");
	}	
	else
	{
		sNobility = "REPUTATION_NOBILITY_5";	
	}	
	sReputation = XI_ConvertString(sFame) + " " + XI_ConvertString(sNobility);
	
	return sReputation;
}

int GetCharacterLoyality(ref chr)
{
    if (CheckAttribute(chr, "loyality"))
    {
        if (sti(chr.loyality) > MAX_LOYALITY)
        {
            chr.loyality = MAX_LOYALITY;
        }
        if (sti(chr.loyality) < 0)
        {
            chr.loyality = 0;
        }
        return sti(chr.loyality);
    }
    else
    {
        return  0; // для пленных и гг
    }
}