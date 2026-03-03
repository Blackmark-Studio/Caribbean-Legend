// Общий модуль для всех сторей, связанных со скрытностью, подключаемый на время открытия стори-фрейма

// Проникновение в город
void StealthCheck_EnterTown(string type, int status)
{
	string validTypes[] = {"gates", "port", "tavern", "tavernEntrance"};
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

// Есть торговая лицензия ИЛИ верительная грамота по квесту
void StealthCheck_CheckVerifyPapers(string letterIndex)
{
	action = SF_AddAction(letterIndex, "", "", SF_Icon("item", "HolTradeLicence"));
	bool hasPapers = false;
	if (CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && storyObject.context.colonyId == "santiago" && GetNationRelation2MainCharacter(StealthNat) != RELATION_ENEMY) hasPapers = true;
	if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && storyObject.context.colonyId == "portspein" && GetNationRelation2MainCharacter(StealthNat) != RELATION_ENEMY) hasPapers = true;
	if (!LICENSE_HasLicense() && !hasPapers) action.disabled = true; // вырубаем кнопку
	if (hasPapers) action.text = SF_Convert("ShowPapersAction");     // подменяем текст кнопки
}