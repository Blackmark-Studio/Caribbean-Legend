// Additional localization functions

// Localized ship class with cases like "corvette, Корвет, Корвета, Корвету"
string DLG_ShipClass(ref args, ref chr)
{
  string end = "";
  if (CheckAttribute(&args, "var0")) end = DLG_A0(&args);
  return xiStr(GetShipTypeName(&chr) + end);
}

// Return phrase based on char's nobility
string DLG_GoodBad(ref args, ref chr)
{
  int nobility = makeint(chr.reputation.nobility);
  if (nobility > 70) return DLG_A0(&args);
  if (nobility > 30) return DLG_A1(&args);
  return DLG_A2(&args);
}

// Localized prhase for the male/female ship class name
string DLG_ShipManWoman(ref args, ref chr)
{
  int nShipType = GetCharacterShipType(&chr);
  ref rBaseShip = GetRealShip(nShipType);
  return GetShipSexWord(rBaseShip.BaseName, DLG_A0(&args), DLG_A1(&args));
}

// Return another localized key with the same context in LocalizeAssets format
string DLG_Link(ref args, ref context)
{
  return DLGO(StringFromKey(DLG_A0(&args)), &context);
}

// Return another localized key with the same context
string DLG_GetKey(ref args, ref context)
{
  string key = DLG_A0(args);
  string filename = GetAttributeOrDefault(context, "filename", "");
  if (DLG_HasArgument(args, 1)) filename = DLG_A1(args);

  string result = xiStr(key);
  if (result != "" && result != " ") return result;

  return DLG_Convert(DLG_A0(args), filename, context);
}

string DLG_IfHasAttribute(ref args, ref context)
{
  if (CheckAttribute(context, DLG_A0(args))) return DLG_A1(args);
  if (DLG_HasArgument(args, 2)) return DLG_A2(args);
  return "";
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

string DLG_Abs(string input)
{
  if (strleft(input, 1) != "-") return input;
  return strcut(input, 1, strlen(input)-1);
}

string _DLG_DeclensionString(ref args)
{
  string form5 = DLG_HasArgument(args, 3) ? DLG_A(args, 3) : DLG_A2(args);
  return DLG_A0(args) + " " + DLG_DeclensionForm(int(DLG_A0(args)), DLG_A1(args), DLG_A2(args), form5);
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
