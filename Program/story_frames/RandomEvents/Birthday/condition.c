bool SF_InitConditions(ref context, ref situation, bool fromStory = false)
{
	int targetMonth = -1;
	int targetDay = -1;
	switch (startHeroType)
	{
		case 1: // Шарль
			targetMonth = 4;
			targetDay = 20;
			situation.a.a = 100;
		break;
		case 2: // Диего
			targetMonth = 11;
			targetDay = 27;
			situation.a.b = 100;
		break;
		case 3: // Вилли
			targetMonth = 5;
			targetDay = 11;
			situation.a.c = 100;
		break;
	}

	int month = GetDataMonth();
	if (month != targetMonth) return false;

	int day = GetDataDay();
	if (day < targetDay) return false;
	if (day > targetDay+7) return false;

	return true;
}