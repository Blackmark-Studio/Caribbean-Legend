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

// Return another localized key with the same context
string DLG_Link(ref args, ref context)
{
  return DLGO(StringFromKey(DLG_A0(&args)), &context);
}

string DLG_IfHasAttribute(ref args, ref context)
{
  if (CheckAttribute(&context, DLG_A0(&args))) return DLG_A1(&args);
  return DLG_A2(&args);
}
