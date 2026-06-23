// DSL for localizations files


// Main function to use
//string DLGO(string input, ref context);

// Universal translate function
//string DLG_Convert(string key, string filename, ref context = nullptr);

// Universal translate function with empty result
//string DLG_ConvertE(string key, string filename, ref context);


// func("aXbXcX", "X", "Y", 0) → "aYbYcY"
// func("aXbXcX", "X", "Y", 3) → "aXbYcY"
//void DLG_ReplaceAllMatches(ref input, string key, string replace, int curPos);

string DLG_ShipManWomanArgs(ref chr, string arg0, string arg1)
{
	int nShipType = GetCharacterShipType(&chr);
	ref rBaseShip = GetRealShip(nShipType);
	return GetShipSexWord(rBaseShip.BaseName, arg0, arg1);
}

string DLG_HumanModifierValue(string modifier, ref rObject)
{
	if (CheckAttribute(rObject, "modifiers." +modifier)) return rObject.modifiers.(modifier);

	trace("Missing modifier " + modifier + " for object" + rObject.id);
	return "Missing modifier";
}

string DLG_HumanModifierValuePercent(string modifier, ref rObject)
{
	return ToHumanPercent(float(DLG_HumanModifierValue(modifier, rObject)));
}

string DLG_NationGen(int iNation)
{
	return XI_ConvertString(GetNationNameByType(iNation) + "Gen");
}

string DLG_ColonyVoc(string sColony)
{
	return XiStr("Colony" + sColony + "Voc");
}

string DLG_GoodName(string input)
{
	return Goods[int(input)].name;
}


string DLG_PlayerNationAbl()
{
	return NationNameSK(GetBaseHeroNation());
}

string DLG_DeclensionString(int num, string form1, string form2, string form5 = "")
{
	return num + " " + DLG_DeclensionForm(num, form1, form2, form5);
}

string DLG_DeclensionForm(int num, string form1, string form2, string form5 = "")
{
	if (form5 == "") form5 = form2;

	int remainder = num % 100;
	if (remainder >= 11 && remainder <= 14) return form5;

	switch (num % 10) {
		case 1: return form1; break;
		case 2: return form2; break;
		case 3: return form2; break;
		case 4: return form2; break;
	}

	return form5;
}