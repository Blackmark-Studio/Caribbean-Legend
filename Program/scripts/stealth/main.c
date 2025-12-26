#include "scripts\stealth\flags.c"
#include "scripts\stealth\license.c"

#define STH_UNKNOWN 0
#define STH_LEGAL 1
#define STH_ENEMY 2
#define STH_SNEAK 3

void STH_CheckIfTownFriendly(ref location)
{
	ref colony = VT_GetColony(GetAttributeOrDefault(location, "fastreload", ""));
	if (colony == nullptr) return;

	int status = STH_GetColonyStatus(location.fastreload);
	if (status == STH_ENEMY) STH_AlarmTown(colony);
	else STH_CheckOnEnter(colony);
}

void STH_CheckOnEnter(ref colony)
{
	aref townInfo = GetAref(&StealthSystem, "colonies." +colony.id);
	if (townInfo == nullptr) return;
	if (!CheckAttribute(&townInfo, "SneakTo")) return;
	
	if (!chrDisableReloadToLocation)
	{
		SetEventHandler("STH_SneakTo", "STH_SneakTo", 1);
		PostEvent("STH_SneakTo", 100, "sss", townInfo.SneakTo.locationId, townInfo.SneakTo.groupId, townInfo.SneakTo.locatorId);
	}
	DeleteAttribute(&townInfo, "SneakTo");
}

void STH_SneakTo()
{
	DelEventHandler("STH_SneakTo", "STH_SneakTo");
	string locationId = GetEventData();
	string groupId = GetEventData();
	string locatorId = GetEventData();
	DoReloadCharacterToLocation(locationId, groupId, locatorId);
}

ref VT_GetColony(ref ref_Id_Idx)
{
	switch (VarType(ref_Id_Idx))
	{
		case "aref": return ref_Id_Idx; break;
		case "int":
			{
				if (ref_Id_Idx < 0) return nullptr;
				return GetColonyByIndex(ref_Id_Idx);
			}
		break;
		case "string":
		{
			if (ref_Id_Idx == "") return nullptr;
			int colonyIdx = FindColony(ref_Id_Idx);
			if (colonyIdx < 0) return nullptr;
			return GetColonyByIndex(colonyIdx);
		}
		break;
	}

	trace("Error: Can't find colony by vartype");
	return nullptr;
}

bool STH_CanEnterTown(string sColony)
{
	int status = STH_GetColonyStatus(sColony);
	if (status == STH_LEGAL || status == STH_UNKNOWN || status == STH_ENEMY) return true;

	return false;
}

int STH_GetColonyStatus(string sColony)
{
	int iColony = FindColony(sColony);
	if (iColony < 0) return STH_UNKNOWN;

	int nation = sti(Colonies[iColony].nation);
	bool enemyNation = nation != PIRATE && GetRelation2BaseNation(nation) == RELATION_ENEMY;
	
	aref townInfo = GetAref(&StealthSystem, "colonies." +sColony);
	if (townInfo != nullptr)
	{
		if (TMSTM_Timestamp(0) < GetAttributeInt(&townInfo, "passUntil")) return STH_LEGAL;
		if (TMSTM_Timestamp(0) < GetAttributeInt(&townInfo, "enemyUntil")) return STH_ENEMY;
	}

	if (enemyNation) return STH_SNEAK;
	else return STH_LEGAL;
}

// Проникли в город с боем
void STH_AlarmTown(ref colony)
{
	int iNation = sti(colony.nation);
	string sNation = GetNationNameByType(iNation);

	LAi_group_AttackGroup(sNation + "_citizens", LAI_GROUP_PLAYER);
	if (rand(3) != 1) SetNationRelation2MainCharacter(iNation, RELATION_ENEMY);
	AddDialogExitQuest("MainHeroFightModeOn");
}

// Колония враждебна на n суток (не дней!)
void STH_SetColonyEnemy(string colonyId, int days)
{
	DeleteAttribute(&StealthSystem, "colonies." + colonyId + ".passUntil");
	StealthSystem.colonies.(colonyId).enemyUntil = TMSTM_Timestamp(days * TMSTM_DAYS);
}

// Колония признаёт легальное присутствие игрока на n суток (не дней!)
void STH_SetColonyLegal(string colonyId, int days)
{
	DeleteAttribute(&StealthSystem, "colonies." + colonyId + ".enemyUntil");
	StealthSystem.colonies.(colonyId).passUntil = TMSTM_Timestamp(days * TMSTM_DAYS);
}

// Проверяем, не запомнил ли форт/портовые корабли ГГ как врага
void STH_CheckShip(ref chr)
{
	string sColony = "";
	if (CheckAttribute(chr, "islandships")) sColony = chr.islandships;
	else if (CheckAttribute(chr, "fort")) sColony = chr.city;
	if (sColony == "") return;
	
	int colonyIdx = FindColony(sColony);
	int status = STH_GetColonyStatus(sColony);
	if (status == STH_ENEMY)
	{
		SetCharacterRelationBoth(sti(chr.index), GetMainCharacterIndex(), RELATION_ENEMY);
		DoQuestCheckDelay(NationShortName(GetBaseHeroNation()) + "_flag_rise", 0.1);
	}
}

// Запретить ближайшему форту стрелять на n секунд
void STH_DelayFort(string sColony, float delayTime)
{
	int fortIdx = GetCharacterIndex(sColony + " Fort Commander");
	if (fortIdx < 0)
	{
		trace("Error: Can't found fortCommander in DelayFort with sColony: " + sColony);
		return;
	}

	ref fortChr = GetCharacter(fortIdx);
	fortChr.fort.mode = FORT_HOLD_FIRE;
	aref callback = STH_Timer(delayTime, "STH_DelayFortEnd");
	callback.fortIdx = fortIdx;
	DeleteAttribute(fortChr, "CheckFlagDate");
}

// Реализация таймера в море для задач скрытности
aref STH_Timer(float delay, string funcName)
{
	SetShowTimer(delay);
	aref callback;
	makearef(callback, pchar.showTimer);
	callback.funcName = funcName;
	SetEventHandler("TimerDelay", "STH_TimerDelay", 1);
	PostEvent("TimerDelay", 1000);
	return callback;
}

// Реализация таймера в море для задач скрытности
void STH_TimerDelay()
{
	if (!CheckAttribute(pchar, "showTimer"))
	{
		DelEventHandler("TimerDelay", "STH_TimerDelay");
		return;
	}

	Log_AStr("" + sti(pchar.showTimer));
	if (GetAttributeInt(pchar, "showTimer") < 2)
	{
		Log_Clear();
		if (CheckAttributeHasValue(pchar, "showTimer.funcName"))
		{
			aref callback = GetAref(pchar, "showTimer");
			string func = callback.funcName;
			call func(&callback);
		}

		DeleteAttribute(pchar, "showTimer");
		DelEventHandler("TimerDelay", "STH_TimerDelay");
		return;
	}

	AddToAttributeFloat(pchar, "showTimer", -1.0);
	PostEvent("TimerDelay", 1000);
}

// Разрешаем форту стрелять
void STH_DelayFortEnd(ref callback)
{
	int fortIdx = GetAttributeIntOrDefault(callback, "fortIdx", -1);
	if (fortIdx < 0)
	{
		trace("Error: Missing fortIdx value in DelayFortEnd");
		return;
	}

	ref fortChr = GetCharacter(fortIdx);
	if (sti(fortChr.fort.mode) == FORT_HOLD_FIRE) fortChr.fort.mode = FORT_NORMAL;
}

// Разрешаем быстрый переход, если есть лицензия или проникли через сторю
bool STH_IsEnableFastReload(string sColony)
{
	if (LICENSE_HasLicense()) return true;
	if (STH_GetColonyStatus(sColony) == STH_LEGAL) return true;

	return false;
}