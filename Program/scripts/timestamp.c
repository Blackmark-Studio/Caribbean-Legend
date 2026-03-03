
#define TMSTS_DAYS 86400 // секунд в дне
#define TMSTS_HOURS 3600 // секунд в часе
#define TMSTS_MINUTES 60 // секунд в минуте

#define TMSTM_DAYS 1440 // минут в дне
#define TMSTM_HOURS 60  // минут в часе

// Timestamp в минутах
int TMSTM_Timestamp(int plus)
{
	int result = TMSTD_Timestamp(0) * TMSTM_DAYS;                          // здесь всего дней в минутах
	result += sti(Environment.date.hour) * 60 + sti(Environment.date.min); // добавляем минуты
	return result + plus;
}

// Timestamp в секундах
int TMSTS_Timestamp(int plus)
{
	int result = TMSTD_Timestamp(0) * TMSTS_DAYS;                                 // здесь всего дней в секундах
	result += sti(Environment.date.hour) * 3600 + sti(Environment.date.min) * 60; // добавляем минуты
	result += sti(Environment.date.sec);                                          // добавляем секунды
	return result + plus;
}

// Timestamp в днях
int TMSTD_Timestamp(int plus)
{
	int year = sti(Environment.date.year) - STARTGAME_YEAR; // не считаем годы до начала игры
	int month = sti(Environment.date.month);
	int day = sti(Environment.date.day);
	day += _TMST_GetMonthDaysPast(month); // дни за прошедшие месяцы
	return year * 365 + day + plus;
}

// Суммированные дни, прошедшие ДО переданного сюда месяца
// Если сейчас февраль, значит прошло 31 дней января
// Как и везде, не учитываем високосные года
int _TMST_GetMonthDaysPast(int month)
{
	switch (month)
	{
		case 1:  return 0; break;
		case 2:  return 31; break;
		case 3:  return 59; break;
		case 4:  return 90; break;
		case 5:  return 120; break;
		case 6:  return 151; break;
		case 7:  return 181; break;
		case 8:  return 212; break;
		case 9:  return 243; break;
		case 10: return 273; break;
		case 11: return 304; break;
		case 12: return 334; break;
	}
}
