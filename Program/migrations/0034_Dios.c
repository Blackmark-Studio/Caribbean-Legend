
void ApplyMigration(ref migrationState)
{
	ref item = ItemsFromId("talisman18");
	item.kind = "boatswain";

	// это кейс, когда игрок в 1.5 отдал все отличные карты Диосу и пошёл по квесту для снятия копий, но это больше не нужно
	// выдаем карты обратно и выставляем диалог в продолжение
	ref chr = CharacterFromID("Dios");
	if (chr.dialog.currentNode == "amapcopy_waitchest" || chr.dialog.currentNode == "amapcopy_waitmonth") 
	{
		chr.dialog.currentNode = "best_map";
		pchar.questTemp.AdmiralMap = true;
		for (int i = 0; i < 25; i++)
		{
			GiveAdmiralMapToCharacter(pchar, 0);
		}
		DeleteAttribute(pchar, "questTemp.AdmiralMap");
	}
}