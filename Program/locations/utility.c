// Можно ли свободно дойти до корабля, используем для ограничений торговли/лута/переназначения абордажников
bool IsShipSafeReachableNow()
{
	if (isShipInside(loadedLocation.id)) return true; // у себя на корабле
	if (IsInSeaNow()) return true;
	if (bAbordageStarted) return false;

	// Мы в городе, опасно ли тут?
	if (loadedLocation.type == "town" || CheckAttribute(&loadedLocation, "fastreload"))
	{
		if (LAi_group_IsActivePlayerAlarm() || LAi_grp_playeralarm > 0) return false; // тревога
		if (CheckAttribute(&loadedLocation, "from_sea") && loadedLocation.from_sea != "" && pchar.location.from_sea != loadedLocation.from_sea) return false; // корабль не в порту
		if (CheckNationLicence(HOLLAND)) return true; // есть лицензия

		// квестовые исключения
		if (CheckAttribute(&pchar, "questTemp.Guardoftruth") && CheckCharacterItem(&pchar, "VerifyPaper") && loadedLocation.fastreload == "santiago" && GetNationRelation2MainCharacter(StealthNat) != RELATION_ENEMY) return true;
		if (CheckAttribute(&pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(&pchar, "VerifyPaper") && loadedLocation.fastreload == "portspein" && GetNationRelation2MainCharacter(StealthNat) != RELATION_ENEMY) return true;
		
		int iColony = FindColony(loadedLocation.fastreload);
		return GetRelation2BaseNation(sti(Colonies[iColony].nation)) != RELATION_ENEMY;
	}

	if (loadedLocation.id == pchar.location.from_sea) return true; // в бухте высадки безопасно

	return pchar.itemlocationindex == "-1";
}

// Идёт бой? Проверка для снятия пушек, пока оставляю нативную реализацию
bool IsInBattle()
{
	if (!bSeaActive && LAi_grp_alarmactive) return true;
	if (bAbordageStarted && !bCabinStarted) return true;
	if (bDisableMapEnter && !CheckAttribute(pchar, "GenQuest.MapClosedNoBattle")) return true;
	return false;
}
