// тут разруливаем запуск случайных событий
#define RE_STORY_PATH "story_frames\RandomEvents"
#define RE_SEASON_COOLDOWN 7 // количество дней после смены сезона без случайных событий
#define RE_COOLDOWN 25       // количество дней, после которого возможно новое случайное событие
#define RE_COOLDOWN_RAND 10  // дополнительный разброс дней от 0 до этого значения, добавляемые к RE_COOLDOWN

object RandEventSystem;

void RE_RunEvent()
{
	int now = TMSTD_Timestamp(0);
	if (!_RE_GlobalConditions()) return;

	// не даём событий после недавней смены сезона
	if (now - GetAttributeInt(&SeasonSystem, "lastChangeTimestamp") < RE_SEASON_COOLDOWN) 
	{
		Log_TestInfo("Случайное событие отложено из-за недавней смены сезона, осталось дней: " + (RE_SEASON_COOLDOWN - (now - GetAttributeInt(&SeasonSystem, "lastChangeTimestamp"))));
		return;
	}

	// недавно уже было событие
	if (now < GetAttributeInt(&RandEventSystem, "nextEventTimestamp"))
	{
		Log_TestInfo("Случайное событие отложено, осталось дней: " + (GetAttributeInt(&RandEventSystem, "nextEventTimestamp") - now));
		return;
	}

	if (!_RE_SituationalConditions()) return;

	int delay = RE_COOLDOWN + DateRandom(RE_COOLDOWN_RAND, "SE");
	Log_TestInfo("В следующий раз событие возможно через: " + delay);
	_RE_CheckEventsList();
	string eventId = _RE_PickEvent(now);
	RandEventSystem.nextEventTimestamp = TMSTD_Timestamp(delay);
	if (eventId == "")
	{
		Log_TestInfo("Случайное событие не произошло: нет подходящего");
		return;
	}

	LaunchStoryFrame(nullptr, "RandomEvents\" +eventId);
}

// Условия для запуска системы ивентов вообще, один раз выполняются и больше не проверяем
bool _RE_GlobalConditions()
{
	if (CheckAttribute(&RandEventSystem, "ready")) return true;

	string reason = "";
	if (!GetDLCenabled(DLC_APPID_8)) reason = "нет DLC";
	if (int(pchar.rank) < 5) reason = "низкий ранг";

	if (reason != "")
	{
		Log_TestInfo("Случайное событие не произошло по причине: " + reason);
		return false;
	}

	RandEventSystem.ready = true;

	// расставляем флаги для одноразовых историй
	RandEventSystem.witnessGhostNotGiven = true;
	RandEventSystem.greenIdolNotGiven = true;
	RandEventSystem.hat12NotGiven = true;
	RandEventSystem.blade_34NotGiven = true;
	return true;
}

// Условия для запуска системы ивентов в зависимости о текущей ситуации в игре
bool _RE_SituationalConditions()
{
	string reason = "";
	if (g_ActiveActionName != "EnterToSea") reason = "движуха в море"; // мы на глобалке с какой-то активной движухой, скипаем
	else if (GetCharacterShipClass(pchar) > 6) reason = "мы на лодке";   // на лодках ничего не происходит

	if (reason == "") return true;

	Log_TestInfo("Случайное событие не произошло по причине: " + reason);
	return false;
}

/*
	Единоразово подгрузим список возможных событий из файлов
	Чтобы обновить список, в миграции удаляем флаг `eventsLoaded`
*/
void _RE_CheckEventsList()
{
	if (CheckAttribute(&RandEventSystem, "eventsLoaded")) return;

	object fileFinder;
	aref fileResList, eventsList;
	eventsList = GetAref(&RandEventSystem, "eventsList", true);
	fileFinder.dir = "Program\" + RE_STORY_PATH;
	fileFinder.mask = "*";
	fileFinder.onlydirs = "1";
	fileFinder.onlyfiles = "0";
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinder);
	makearef(fileResList, fileFinder.filelist);
	CopyAttributes(&eventsList, &fileResList);
	RandEventSystem.eventsLoaded = true;
}

// Выберем событие
string _RE_PickEvent(int now)
{
	aref fullList = GetAref(&RandEventSystem, "eventsList", true);
	object currentList;
	CopyAttributes(&currentList, &fullList);

	int eventsQty = GetAttributesNum(&currentList);
	int eventIdx = DateRandom(eventsQty-1, "SE");

	// Перебираем список, начиная со случайного индекса
	for (int i = 0; i < eventsQty; i++)
	{
		aref arEvent = GetAttributeN(&currentList, eventIdx);
		
		string eventId = GetAttributeValue(arEvent);
		if (_Re_CanRunEvent(eventId, now))
		{
			return eventId;
		}

		eventIdx++;
		if (eventIdx == eventsQty) eventIdx = 0;
	}

	return "";
}

extern bool SF_InitConditions(ref context, ref situation, bool fromStory = false);
bool _Re_CanRunEvent(string eventId, int now)
{
	if (now < GetAttributeInt(&RandEventSystem, "recentEvents." + eventId)) return false;

	bool result = false;
	string path = RE_STORY_PATH + "\" + eventId + "\condition.c";
	if (LoadSegment(path))
	{
		object temp;
		result = SF_InitConditions(&temp, &temp);
		UnloadSegment(path);
	}

	return result;
}