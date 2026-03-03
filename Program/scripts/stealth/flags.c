#define FLAG_MISSING -1 // флага нет вовсе
#define FLAG_JOKER 0    // имеем флаг из-за джокера
#define FLAG_LICENCE 1  // имеем флаг из-за лицензии
#define FLAG_CAPTURED 2 // флаг захвачен
#define FLAG_NATIVE 9   // флаг нации ГГ

aref _STH_GetFlags(int nation)
{
	aref flags;
	string nationName = GetNationNameByType(nation);
	makearef(flags, StealthSystem.flags.(nationName));
	return flags;
}

int STH_GetFlagState(int nation, int shipRank)
{
	if (nation == GetBaseHeroNation()) return FLAG_NATIVE;
	if (nation == PIRATE) return FLAG_NATIVE;

	aref flags = _STH_GetFlags(nation);
	if (CheckAttribute(flags, "shipRank" + shipRank)) return FLAG_CAPTURED;
	if (LICENSE_HasLicense()) return FLAG_LICENCE; // механика лицензии
	if (CheckAttribute(flags, "joker")) return FLAG_JOKER;
	return FLAG_MISSING;
}

void STH_StealShipFlag(int nation, int shipRank) {
	bool newFlag = _STH_AddFlagToUse(nation, shipRank);
	if (!newFlag) return;

	Notification(GetConvertStrB("flags_newFlagTaken", "Stealth.txt"), "IronWill");
}

// Добавить флаг ранга, вернём false если флаг уже был
bool _STH_AddFlagToUse(int nation, int shipRank) {
	if (_STH_HasFlag(nation, shipRank, false)) return false;

	aref flags = _STH_GetFlags(nation);
	SetAttribute(flags, "shipRank" + shipRank, true);
	_STH_CheckFlagsForPerk(nation);
	return true;
}

// Если собрали все флаги → выдаём перк
void _STH_CheckFlagsForPerk(int nation)
{
	bool hasAll = true;
	for (int i = 1; i < 7; i++)
	{
		if (!_STH_HasFlag(nation, i, false)) hasAll = false;
	}

	if (!hasAll) return;

	SetCharacterPerk(pchar, "Flag" + NationShortName(nation));
	Notification(GetConvertStrB("flags_allFlagsCollected", "Stealth.txt"), "IronWill");
}

// Можем сменить флаг сейчас?
bool STH_CanUseFlag(int nation) {
	if (nation == PIRATE) return true;
	if (nation == GetBaseHeroNation()) return true;
	if (LICENSE_HasLicense()) return true; // механика лицензии

	aref flags = _STH_GetFlags(nation);
	if (CheckAttribute(flags, "joker")) return true;

	for (int i=0; i<COMPANION_MAX; i++)
	{
		int companionIdx = GetCompanionIndex(pchar, i);
		if (companionIdx < 0) continue;

		ref companion = GetCharacter(companionIdx);
		if (!IsFellowOurCrew(companion)) continue;

		if (!CheckAttributeEqualTo(flags, "shipRank" + GetCharacterShipClass(companion), true)) return false;
	}

	return true;
}

// Есть ли конкретный флаг нации для ранга
bool _STH_HasFlag(int nation, int shipRank, bool withTemp)
{
	int state = STH_GetFlagState(nation, shipRank);
	if (withTemp) return state >= FLAG_JOKER;
	return state >= FLAG_CAPTURED;
}

// Добавить/убрать временный флаг любого ранга для нации
void STH_SetJokerFlag(int nation, bool enable) {
	aref flags = _STH_GetFlags(nation);
	if (enable) SetAttribute(flags, "joker", true);
	else DeleteAttribute(flags, "joker");
}

// Вернуть iNation по перку флага
int _STH_GetNationByPerk(string perkName)
{
	switch(perkName)
	{
		case "flageng": return ENGLAND; break;
		case "flagfra": return FRANCE;  break;
		case "flagspa": return SPAIN;   break;
		case "flaghol": return HOLLAND; break;
		case "flagpir": return PIRATE;  break;
	}
	return PIRATE;
}

