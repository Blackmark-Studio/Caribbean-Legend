// Кок/Старший кок
float GetCookMtp(ref rchar)
{
	float result = 1;

	if (IsMainCharacter(rchar)) 
	{
		if (CheckOfficersPerkEnable("Cook")) result -= PERK_VALUE_COOK;
		if (CheckOfficersPerkEnable("ChiefCook")) result -= PERK_VALUE_CHIEF_COOK;
		return result;
	}

	if (HasPerk(rchar, "Cook")) result -= PERK_VALUE_COOK;
	if (HasPerk(rchar, "ChiefCook")) result -= PERK_VALUE_CHIEF_COOK;

	return result;
}

// Бармен/Винокур
float GetBartenderMtp(ref rchar)
{
	float result = 1;

	if (IsMainCharacter(rchar)) 
	{
		if (CheckOfficersPerkEnable("Bartender")) result -= PERK_VALUE_BARTENDER;
		if (CheckOfficersPerkEnable("Moonshiner")) result -= PERK_VALUE_MOONSHINER;
		return result;
	}

	if (HasPerk(rchar, "Bartender")) result -= PERK_VALUE_BARTENDER;
	if (HasPerk(rchar, "Moonshiner")) result -= PERK_VALUE_MOONSHINER;

	return result;
}

// Видимо, кто-то снял врача с должности...
void DailyCheckIfQuartermaster(ref rchar)
{
	int maxCrew = GetMaxCrewQuantity(rchar);
	int diff = GetCrewQuantity(rchar) - maxCrew;
	if (diff <= 0) return;

	SetCrewQuantity(rchar, maxCrew);
	Log_Info(StringFromKey("perks_6", rchar.Ship.Name, FindRussianSailorString(diff, "No")));
}

// Квартирмейстер
int GetBonusCrewQuartermaster(ref rchar, int optCrew, int maxCrew)
{
	if (IsMainCharacter(rchar) && CheckOfficersPerkEnable("Quartermaster")) return maxCrew + optCrew * PERK_VALUE_QUARTERMASTER;
	else if (HasPerk(rchar, "Quartermaster")) return maxCrew + optCrew * PERK_VALUE_QUARTERMASTER;
	return maxCrew;
}

void CheckTradeConnections(aref location)
{
	if (LAi_IsCapturedLocation) return;
	if (location.type != "town" && location.id != "LaVega_port" && location.id != "PuertoPrincipe_town" && location.id != "Shore35") return;
	if (!CheckOfficersPerkEnable("TradeConnections")) return;
	if (!bFastEnable()) return; // Нет быстрого перехода, вероятно, враждебная колония или квестовое ограничение, энивей не будем

	ref rColony = GetColonyRefByID(location.townsack);
	string colonyId = rColony.id;
	if (CheckAttribute(&NullCharacter, "Pricelist." + colonyId) && strcut(NullCharacter.PriceList.(colonyId).AltDate, 5, 15) == strcut(GetQuestBookDataDigit(), 5, 15)) return; // не обновляем цены чаще раза в день по данным из журнала

	SetPriceListByStoreMan(rColony);
	notification(StringFromKey("perks_1"), "LogBook");
}