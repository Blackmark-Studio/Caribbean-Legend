// Общий модуль для всех сторей, связанных со скрытностью, подключаемый на время открытия стори-фрейма

// Проникновение в город
void StealthCheck_EnterTown(string type, int status)
{
	string validTypes[] = {"gates", "port", "tavern"};
	if (ValueIsBad(&validTypes, type)) return;

	string colonyId = storyObject.context.colonyId;
	if (status == STH_LEGAL) STH_SetColonyLegal(colonyId, 15);
	else if (status == STH_ENEMY) STH_SetColonyEnemy(colonyId, 1);
	else
	{
		trace("Error: Wrong status for EnterTown");
		return;
	}

	storyObject.exit = true;
	storyObject.onClose.SF_TeleportTo = true;
	storyObject.teleportTo = type;
}

// iNation города, куда проникаем
int StealthCheck_Nation()
{
	return sti(Colonies[FindColony(storyObject.context.colonyId)].nation);
}