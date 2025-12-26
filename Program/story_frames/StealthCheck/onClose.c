// Общий модуль для всех сторей, связанных со скрытностью, подключаемый к OnClose

// Проникновение в город
void SF_TeleportTo(ref storyObject)
{
	string teleportTo = storyObject.teleportTo;
	string colonyId = storyObject.context.colonyId;
	aref townInfo = GetAref(&StealthSystem, "colonies." + colonyId);

	switch (teleportTo)
	{
		case "tavern":
			townInfo.SneakTo.locationId = colonyId + "_tavern";
			townInfo.SneakTo.groupId = "reload";
			townInfo.SneakTo.locatorId = "reload1";
		break;
	}

	if (bSeaLoaded) Sea_LandLoad();
	else DoReloadCharacterToLocation(colonyId + "_town", "reload", "gate_back");
}