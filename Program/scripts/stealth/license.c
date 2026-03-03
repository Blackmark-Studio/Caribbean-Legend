// Механика торговой лицензии

// Дать лицензию на n дней. Передача нации здесь – легаси
void GiveNationLicence(int _nation, int addDays)
{
	LICENSE_AddDays(addDays);
}

// Дать лицензию на n дней
void LICENSE_AddDays(int addDays)
{
	aref license;
	makearef(license, StealthSystem.license);
	int daysLeft = GetAttributeInt(license, "validUntil") - TMSTD_Timestamp(0);
	if (daysLeft < 0) daysLeft = 0;

	license.validUntil = TMSTD_Timestamp(addDays + daysLeft);
	DeleteAttribute(&license, "violations");
}

void LICENSE_CheckExpired()
{
	int validUntil = GetAttributeInt(&StealthSystem, "license.validUntil");
	if (validUntil == 0) return;
	if (validUntil - TMSTD_Timestamp(0) > 0) return;

	LICENSE_RemoveLicense();
	Notification(GetConvertStrB("license_expired", "Stealth.txt"), "Document");
}

// Сколько осталось дней лицензии? Если нет: -1
int LICENSE_GetDaysLeft()
{
	int daysLeft = GetAttributeInt(&StealthSystem, "license.validUntil") - TMSTD_Timestamp(0);
	if (daysLeft <= 0) return -1;

	return daysLeft;
}

// Дата, когда лицензия истечёт (включительно). Если лицензии нет → пустая строка.
string LICENSE_GetExpireDateString()
{
	int daysLeft = LICENSE_GetDaysLeft();
	if (daysLeft < 1) return "";

	return GetDateStringEx(GetAddingDataYear(0, 0, daysLeft), GetAddingDataMonth(0, 0, daysLeft), GetAddingDataDay(0, 0, daysLeft));
}

// Сколько сейчас нарушений лицензии, если нет лицензии → 0
int LICENSE_GetViolations()
{
	return GetAttributeInt(&StealthSystem, "license.violations");
}

// Есть ли активная лицензия?
bool LICENSE_HasLicense()
{
	return LICENSE_GetDaysLeft() > 0;
}

// Проверяем, является ли действие против персонажа нарушением
void LICENSE_CheckViolationAgainstGroup_Land(ref chr)
{
	if (!LICENSE_HasLicense()) return;
	if (GetAttributeInt(chr, "nation") == PIRATE) return; // пираты не считаются
	if (!CheckAttribute(chr, "City")) return; // не горожане

	STH_SetColonyEnemy(chr.city, 1);
	_LICENSE_AddViolationFromGroup(chr);
}

// Проверяем, является ли действие против корабля нарушением
void LICENSE_CheckViolationAgainstGroup_Sea(ref chr)
{
	if (!LICENSE_HasLicense()) return;
	if (GetAttributeInt(chr, "nation") == PIRATE) return; // пираты не считаются

	_LICENSE_AddViolationFromGroup(chr);
}

// Нарушили условия контракта против группы персонажей, нарушение возможно единожды в течение суток
void _LICENSE_AddViolationFromGroup(ref chr)
{
	int timestamp = TMSTM_Timestamp(0);
	if (GetAttributeIntOrDefault(chr, "tradeLicenseViolation", timestamp) < timestamp) return;

	chr.tradeLicenseViolation = TMSTM_Timestamp(TMSTM_DAYS); // через сутки
	LICENSE_AddViolation();
}

// Добавляем нарушение контракта, отбираем лицензию, если превысили лимит
void LICENSE_AddViolation()
{
	if (!LICENSE_HasLicense()) return;

	aref license;
	makearef(license, StealthSystem.license);
	int violations = GetAttributeInt(license, "violations");

	violations++;
	license.violations = violations;
	if (violations > 2) LICENSE_RemoveLicense();
	Notification(GetConvertStrB("license_violation_" + violations, "Stealth.txt"), "Document");
}

void LICENSE_RemoveLicense()
{
	DeleteAttribute(&StealthSystem, "license");
	PlaySound("interface\important_item.wav");
}

// Легаси отнимание лицензии, сейчас поведение не определено
// JOKERTODO прошерстить использование, развести по случаям, когда лицензию надо отобрать и когда не надо
void TakeNationLicence(int _nation)
{
	// string sTemp; 
	// if (_nation != PIRATE && CheckNationLicence(_nation)) 
	// {
	// 	sTemp = NationShortName(_nation)+"TradeLicence";
	// 	TakeItemFromCharacter(pchar, sTemp);
	// 	DeleteAttribute(ItemsFromID(sTemp), "Action_date");
	// 	DeleteAttribute(ItemsFromID(sTemp), "Validity");
	// }
}

//проверить наличие лицензии
bool CheckNationLicence(int _nation)
{
	return LICENSE_HasLicense();
}

//проверить сроки лицензии, сколько осталось дней. если -1, то просрочена или отсутствует
int GetDaysContinueNationLicence(int _nation)
{
	return LICENSE_GetDaysLeft();
}
//дать наименование лицензии, например 'Лицензия Голландской Вест-Индской компании'
string GetRusNameNationLicence(int _nation)
{
	string sTemp, itmTitle;
	if (_nation != PIRATE) 
	{
		if (CheckNationLicence(_nation))
		{
			sTemp = NationShortName(_nation)+"TradeLicence";
			itmTitle = GetItemName(&Items[GetItemIndex(sTemp)]);
		}
	}
	return itmTitle;
}