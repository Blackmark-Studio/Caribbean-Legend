#include "characters\RPG\cash_tables\cash_tables.h"
#include "characters\RPG\cash_tables\helpers.c"
#include "characters\RPG\cash_tables\common_table.c"
#include "characters\RPG\cash_tables\equip_table.c"
#include "characters\RPG\cash_tables\land_table.c"
#include "characters\RPG\cash_tables\static_table.c"

// Чтобы не пересчитывать постоянно вещи, офицеров и прочее, что может влиять на умения/скиллы
// сохраняем результат в таблицу, откуда и выдаем потом стандартными методами GetCharacterSkill и т. п.
// Таблицу обновляем при событиях, когда значения внутри могут измениться
// Например, при надевании/снятии шмотки, при переназначении офицера и т. п.

#event_handler(EVENT_CT_UPDATE, "UpdateCashTables");                 // обновляем персонажа
#event_handler(EVENT_CT_UPDATE_FELLOW, "UpdateCashTablesFellow");    // обновляем персонажа и ГГ
#event_handler(EVENT_CT_UPDATE_FELLOWS, "UpdateCashTablesFellows");  // обновляем всю команду
#event_handler(EVENT_LOCATION_LOAD, "CT_UpdateCharsInLocation");     // обновляем всех в локе
#event_handler(EVENT_CT_UPDATE_LAND, "UpdateLandTable");             // сняли/надели шмотку, пересчитываем боевку
#event_handler(EVENT_CT_APPLY_ADMIRAL, "UpdateCashTablesAdmiral");   // обновили табличку ГГ-адмирала
#event_handler(EVENT_CHARACTER_DEAD, "UpdateCashTablesOnDead");      // может, убили офицера?
#event_handler(EVENT_CT_APPLY_COMPANION, "UpdateCashTablesCompanion");

// Если умер офицер, обновим таблицу ГГ
void UpdateCashTablesOnDead()
{
	aref chr = GetEventData();
	if (!IsFellow(chr)) return;
	Postevent(EVENT_CT_UPDATE, 500, "a", pchar);
}

void UpdateSpeedByWeight(ref chr)
{
	if (!LAi_IsArmed(chr)) return;
	CheckAndSetOverloadMode(chr);
	aref landTable = CT_GetTable(chr, CT_LAND);
	aref equipTable = CT_GetTable(chr, CT_EQUIP);
	ref blade = ItemsFromID(GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE));

	CT_SetAllMoveSpeed(&landTable, &equipTable, &chr);
	CT_SetAllAttackSpeed(&landTable, &equipTable, chr, blade);
}

void UpdateLandTable()
{
	aref chr = GetEventData();
	CT_UpdateLandTable(&chr);
}

// Формирование/обновление таблицы для всех персонажей на локации
void CT_UpdateCharsInLocation()
{
	CT_UpdateCashTables(pchar);

	for(int i=0; i < LAi_numloginedcharacters; i++)
	{
		int index = LAi_loginedcharacters[i];
		if (index < 0) continue;
		if (GetMainCharacterIndex() == index) continue;

		ref chr = &Characters[index];
		if (LAi_IsDead(chr)) continue;
		if (!LAi_IsArmed(chr)) continue; // невооруженные пофигу
		PostEvent(EVENT_CT_UPDATE, 500+i*50, "a", chr); // чтобы не чпекать всех за один кадр
	}
}

// Обновление братишки вызывает обновление ГГ из-за зависимых бонусов
void UpdateCashTablesFellow()
{
	aref chr = GetEventData();
	CT_UpdateCashTablesFellow(&chr);
}

// Основная функция обновления таблиц, пока оставляем только общую
void CT_UpdateCashTables(ref chr)
{
	CT_UpdateEquipTable(chr);
	CT_UpdateCommonTable(chr);
}

// Обновить таблицы ГГ и офицеров
void UpdateCashTablesFellows()
{
	CT_UpdateCashTables(pchar); // гг на случай шляпы
	object fellows = GetAllFellows(pchar, false);
	for (int i=0; i < GetAttributesNum(fellows); i++)
	{
		ref chr = GetCharacter(sti(GetAttributeValue(GetAttributeN(fellows, i))));
		CT_UpdateCashTables(chr);
	}
	CT_UpdateCashTables(pchar); // гг ещё раз из-за бонуса от оффов
}

void UpdateCashTables()
{
	aref chr = GetEventData();
	CT_UpdateCashTables(chr);
}

// Процессим зависимость компаньонов от ГГ засчёт адмиральской шляпы
void UpdateCashTablesAdmiral()
{
	aref admiralTable = CT_GetTable(pchar, CT_COMMON);
	CT_UpdateCashTablesAdmiral(&admiralTable);
}

void UpdateCashTablesCompanion()
{
	aref chr = GetEventData();
	aref admiralTable = CT_GetTable(pchar, CT_COMMON);
	aref chrTable = CT_GetTable(&chr, CT_COMMON);

	CT_UpdateCashTablesAdmiral(&admiralTable);
	CT_SetNavyPenalty(chr, &chrTable, true, false);
}

ref InitTableForFight(ref chr)
{
	if (!CheckAttribute(chr, "ct." + CT_LAND)) CT_UpdateLandTable(chr);
	return CT_GetTable(chr, CT_LAND);
}