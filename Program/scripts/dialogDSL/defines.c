// List for all DSL $handlers to use
// Define all the new ones here

// Predefined DSL-functions
// Access global variables: pchar, CharacterRef + context object
string DLG_RunKnownFunction(string functionName, ref context, ref args, int argsCount)
{
  ref NPC = &CharacterRef; // just for consistency

  switch (functionName)
  {
    case "manWoman":        return GetSexPhrase(DLG_A0(&args), DLG_A1(&args));                  break;
    case "npcManWoman":     return NPCharSexPhrase(&NPC, DLG_A0(&args), DLG_A1(&args));         break;
    case "ctxManWoman":     return NPCharSexPhrase(&context, DLG_A0(&args), DLG_A1(&args));     break;
    case "days":            return FindRussianDaysString(sti(DLG_A0(&args)));                   break;
    case "dublon":          return FindRussianDublonString(sti(DLG_A0(&args)));                 break;
    case "qty":             return FindRussianQtyString(sti(DLG_A0(&args)));                    break;
    case "month":           return FindRussianMonthString(sti(DLG_A0(&args)));                  break;
    case "people":          return FindRussianPeoplesString(sti(DLG_A0(&args))), DLG_A1(&args); break;
    case "slaves":          return FindRussianSlavesString(sti(DLG_A0(&args))), DLG_A1(&args);  break;
    case "sailors":         return FindRussianSailorString(sti(DLG_A0(&args))), DLG_A1(&args);  break;
    case "rand":            return DLG_RandArgument(&args, argsCount);                          break;
    case "attr":            return DLG_A0(&args);                                               break;
    case "shipClass":       return DLG_ShipClass(&args, &pchar);                                break;
    case "npcShipClass":    return DLG_ShipClass(&args, &NPC);                                  break;
    case "ctxShipClass":    return DLG_ShipClass(&args, &context);                              break;
    case "goodBad":         return DLG_GoodBad(&args, &pchar);                                  break;
    case "npcGoodBad":      return DLG_GoodBad(&args, &NPC);                                    break;
    case "key":             return DLG_GetKey(args, context);                                   break;
    case "link":            return DLG_Link(args, context);                                     break;
    case "shipManWoman":    return DLG_ShipManWoman(&args, &pchar);                             break;
    case "npcShipManWoman": return DLG_ShipManWoman(&args, &NPC);                               break;
    case "ctxShipManWoman": return DLG_ShipManWoman(&args, &context);                           break;
    case "workType":        return GetWorkTypeOfMan(&NPC, DLG_A0(&args));                       break;
    case "hasAttr":         return DLG_IfHasAttribute(&args, &pchar);                           break;
    case "npcHasAttr":      return DLG_IfHasAttribute(&args, &NPC);                             break;
    case "ctxHasAttr":      return DLG_IfHasAttribute(&args, &context);                         break;
    case "modifier":        return HumanModifierValue(&args, &context);                         break;
    case "modifierPercent": return ToHumanPercent(stf(HumanModifierValue(&args, &context)));    break;
    case "number":          return ToHumanNumber(DLG_A0(&args));                                break;
    case "percent":         return ToHumanPercent(stf(DLG_A0(&args)));                          break;
    case "nationGen":       return DLG_NationGen(sti(DLG_A0(&args)));                           break;
    case "colonyVoc":       return DLG_ColonyVoc(DLG_A0(&args))                                 break;
  }

  return "$custom";
}

// Predefined DSL-shortcuts replaces
// If you wants to add new shortcut – add here and to function DLG_ReplaceSimpleKeys as well
string DLG_RunReplace(string key, ref context)
{
  switch(key)
  {
    case "$sir":         return GetAddress_FormToNPC(pchar);         break; // → Sir, Ledy for pchar sex
    case "$npcSir":      return GetAddress_FormToNPC(CharacterRef);  break; // → Sir, Ledy for NPC sex
    case "$name":        return pchar.name;                          break; // → Sharlie, Diego, Helen (pchar name)
    case "$npcName":     return CharacterRef.name;                   break; // → Robert, Carl, James (npcName)
    case "$swear":       return RandSwear();                         break; // → God damn it!
    case "$bye":         return Goodbye(true);                       break; // → Good bye!
    case "$hello":       return TimeGreeting();                      break; // → Greetings!
    case "$city":        return GetCityName(CharacterRef.city);      break; // → VIllemstad
    case "$shipName":    return pchar.ship.name;                     break; // → Adelina
    case "$npcShipName": return CharacterRef.ship.name;              break; // → Adelina
    case "$ctxShipName": return context.ship.name;                   break; // → Adelina
    case "$playerNationAbl": return xiStr("adjective_" + GetNationNameByType(GetBaseHeroNation())); break;
  }

  return "Error: missing replacement for " + key;
}

// Predefined DSL-shortcuts keys
void DLG_ReplaceSimpleKeys(ref input, ref context)
{
  DLG_Replace(&input, context, "$sir");
  DLG_Replace(&input, context, "$npcSir");
  DLG_Replace(&input, context, "$name");
  DLG_Replace(&input, context, "$npcName");
  DLG_Replace(&input, context, "$swear");
  DLG_Replace(&input, context, "$bye");
  DLG_Replace(&input, context, "$hello");
  DLG_Replace(&input, context, "$city");
  DLG_Replace(&input, context, "$shipName");
  DLG_Replace(&input, context, "$npcShipName");
  DLG_Replace(&input, context, "$ctxShipName");
  DLG_Replace(&input, context, "$playerNationAbl");
}
