// Получить уникальные индексы всех персонажей, имеющих должности
void GetAllFellowsWithJob(ref result, ref captain, bool includeBoarders = true)
{
	aref passengers, officers;
	makearef(passengers, captain.fellows.passengers);
	makearef(officers, passengers.officers);

	for (int i=0; i < JOBS_MAX-1; i++)
	{
		string job = JobByIdx(i);
		if (!CheckAttribute(passengers, job)) continue;
		AddFellow(result, sti(passengers.(job)));
	}

	if (!includeBoarders) return;

	// Абордажники
	int officersQty = GetAttributesNum(officers);
	for(i=0; i < officersQty; i++)
	{
		AddFellow(result, sti(GetAttributeValue(GetAttributeN(officers, i))));
	}
}

// Собрать индексы всей команды капитана с сортировкой абордажники => офицеры => компаньоны => пассажиры/пленники
// Fellow -- член экипажа ГГ в любом статусе, будь то абордажник, офицер, компаньон или пассажир
// [!] Этот метод возвращает в том числе квестовых персонажей
void AddAllFellows(ref result, ref captain, bool includeCaptain)
{
	if (includeCaptain) result.f1 = captain.index;

	aref passengers, officers, companions;
	makearef(passengers, captain.fellows.passengers);
	makearef(officers, passengers.officers);
	makearef(companions, captain.fellows.companions);

	// Абордажники
	for(int i=0; i < GetAttributesNum(officers); i++)
	{
		AddFellow(result, sti(GetAttributeValue(GetAttributeN(officers, i))));
	}

	// Корабельные офицеры
	for (i=0; i < JOBS_MAX-1; i++)
	{
		string job = JobByIdx(i);
		if (!CheckAttribute(passengers, job)) continue;
		AddFellow(result, sti(passengers.(job)));
	}

	// Компаньоны
	for (i=0; i < GetAttributesNum(companions); i++)
	{
		AddFellow(result, sti(GetAttributeValue(GetAttributeN(companions, i))));
	}

	// Пассажиры
	for (i=1; i <= GetPassengersQuantity(captain); i++)
	{
		string idAttr = "id" + i;
		if (!CheckAttribute(passengers, idAttr)) continue;
		AddFellow(result, sti(passengers.(idAttr)));
	}
}

void AddFellow(ref result, int chrIdx)
{
	if (chrIdx < 0) return;

	string sIndex = "f"+chrIdx;
	result.(sIndex) = chrIdx;
}

// Братишка не квестовый, пленник, короче действительно наш братишка
// Метод предназначен для фильтра персонажей из функций типа GetAllFellows, то есть мы уже предполагаем
// что передаём сюда кого-то из списка пассажиров, а не любого персонажа в принципе
bool IsFellowOurCrew(ref chr)
{
	if (AttributeIsTrue(chr, "prisoned")) return false;
	if (CheckAttribute(chr, "isquest")) return false;
	return GetRemovable(chr);
}

// Участвует ли братишка в торговле
bool IsFellowAbleToTrade(ref chr)
{
	if (!IsFellowOurCrew(chr)) return false;
	if (IsShipSafeReachableNow()) return true;
	return pchar.location == chr.location;
}

// Можно ли сейчас открыть обмен с братишкой
bool IsFellowAbleToExchange(ref chr)
{
	if (IsMainCharacter(chr)) return false;
	return IsFellowAbleToLoot(chr);
}

// Может ли братишка сейчас лутать сундук
bool IsFellowAbleToLoot(ref chr)
{
	if (!IsFellowOurCrew(chr)) return false;
	if (bAbordageStarted && IsOfficer(chr)) return true;
	if (IsInSeaNow()) return true;
	if (!IsMainCharacter(chr) && !IsShipInside(loadedLocation.id) && !CheckAttribute(&loadedLocation, "locators.officers")) return false; // костыль для кражи в локациях, куда не спавнятся офицеры
	if (IsShipSafeReachableNow()) return true;

	return pchar.location == chr.location;
}

// Может ли братишка сейчас стать компаньоном
bool IsFellowAbleToBeCompanion(ref chr)
{
	if (!IsFellowOurCrew(chr)) return false;
	if (AttributeIsTrue(chr, "CompanionDisable")) return false;
	if (IsCompanion(chr)) return false;
	if (IsOfficer(chr) && !IsShipSafeReachableNow()) return false; // абордажников нельзя, если небезопасно
	return true;
}

// Может ли братишка сейчас стать компаньоном при захвате корабля
bool IsFellowAbleToBeCompanionOnBoarding(ref chr)
{
	if (!IsFellowOurCrew(chr)) return false;
	if (AttributeIsTrue(chr, "CompanionDisable")) return false;
	if (IsCompanion(chr)) return false;
	return true;
}

// Может ли братишка сейчас занять новую должность
bool IsFellowAbleToGetShipJob(ref chr)
{
	if (!IsFellowOurCrew(chr)) return false;
	if (IsCompanion(chr)) return false;

	int jobLimit = 1;
	if (CheckCharacterPerk(chr, "ByWorker")) jobLimit = 2;
	return GetAttributeInt(chr, "isbusy") < jobLimit;
}

// Может ли братишка сейчас стать абордажником
bool IsFellowAbleToGetBoarderJob(ref chr)
{
	if (!IsFellowAbleToGetShipJob(chr)) return false;
	return !IsOfficer(chr);
}

// Является ли чар братишкой, не совсем надёжная проверка, но хотя бы её тут потом можно будет поменять в одном месте
bool IsFellow(ref chr)
{
	if (!CheckAttribute(&chr, "Payment")) return false;
	if (chr.chr_ai.group != LAI_GROUP_PLAYER) return false;
	return true;
}

// Все должности офицера
void FillFellowJobs(ref chrVT, ref result)
{
	ref chr = FindChar_VT(&chrVT);
	int chrIdx = sti(chr.index);
	aref passengers;
	makearef(passengers, pchar.Fellows.Passengers);

	for (int i=0; i < JOBS_MAX-1; i++)
	{
		string job = JobByIdx(i);
		if (!CheckAttribute(passengers, job)) continue;
		if (chr.index != passengers.(job)) continue;

		result.(job) = true;
	}

	for (i=1; i<4; i++)
	{
		if (GetOfficersIndex(pchar, i) != chrIdx) continue;
		result.fighter = true;
	}

	for (i=0; i<COMPANION_MAX; i++)
	{
		if (GetCompanionIndex(pchar, i) == chrIdx) 
		{
			result.companion = true;
			return;
		}
	}
}

bool CanHirePrisoner(ref chr)
{
	int rankDiff = func_max(0, GetAttributeInt(chr, "rank") - GetAttributeInt(pchar, "rank"));
	if (rankDiff > 5) return false; // 5 рангов разницы макс

	int leadershipDebuff = rankDiff * 5;
	return GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP) + 20 >= GetSkillAfterPenalty(chr, SKILL_LEADERSHIP) + leadershipDebuff;
}

object GetFellowJobs(ref ref_Id_Idx)
{
	object result;
	ref chr = FindChar_VT(ref_Id_Idx);
	int chrIdx = int(chr.index);
	aref passengers;
	makearef(passengers, pchar.Fellows.Passengers);
	int found = 0;

	for (int i=0; i < JOBS_MAX-1; i++)
	{
		string job = JobByIdx(i);
		if (!CheckAttribute(passengers, job)) continue;
		if (chr.index != passengers.(job)) continue;

		result.(job) = true;
		found++;
	}

	for (i=1; i<4; i++)
	{
		if (GetOfficersIndex(pchar, i) != chrIdx) continue;
		result.fighter = true;
		found++;
	}

	if (found > 1) return result;

	for (i=0; i<COMPANION_MAX; i++)
	{
		if (GetCompanionIndex(pchar, i) != chrIdx) continue;
		result.companionship = true;
		return result;
	}

	if (found == 0) result.passenger = true;
	return result;
}

string GetMainJob(ref chr)
{
	object jobs = GetFellowJobs(chr);
	return GetAttributeName(GetAttributeN(&jobs, 0));
}

bool IsFellowHasJob(ref chr, string jobName)
{
	return pchar.Fellows.Passengers.(jobName) == chr.index;
}

// Собрать всех персонажей на должностях для случайных событий
int RE_GetAllFellows(ref result)
{
	aref passengers = GetAref(pchar, "fellows.passengers");
	int found = 0;
	for (int i=0; i < JOBS_MAX-1; i++)
	{
		string job = JobByIdx(i);
		if (!CheckAttribute(passengers, job)) continue;
		ref chr = GetCharacterSafe(int(passengers.(job)), true);
		if (chr == nullptr) continue;
		if (chr.sex != "man") continue;

		SetAttribute(result, chr.id, chr.id);
	}

	for (i=1; i<4; i++)
	{
		ref fighter = GetCharacterSafe(GetOfficersIndex(pchar, i), true);
		if (fighter == nullptr) continue;
		if (chr.sex != "man") continue;

		SetAttribute(result, fighter.id, fighter.id);
	}

	return GetAttributesNum(result);
}