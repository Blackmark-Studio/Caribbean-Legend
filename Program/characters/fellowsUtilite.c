// Собрать индексы всей команды капитана с сортировкой абордажники => офицеры => компаньоны => пассажиры
// Fellow -- член экипажа ГГ в любом статусе, будь то абордажник, офицер, компаньон или пассажир
object GetAllFellows(ref captain, bool includeCaptain)
{
	object result;
	AddAllFellows(&result, captain, includeCaptain);
	return result;
}

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
	if (!IsMainCharacter(chr) && !CheckAttribute(&loadedLocation, "locators.officers")) return false; // костыль для кражи в локациях, куда не спавнятся офицеры
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

// Может ли братишка сейчас занять новую должность
bool IsFellowAbleToGetJob(ref chr)
{
	if (!IsFellowOurCrew(chr)) return false;
	if (IsCompanion(chr)) return false;

	int jobLimit = 1;
	if (CheckCharacterPerk(chr, "ByWorker")) jobLimit = 2;
	return GetAttributeInt(chr, "isbusy") < jobLimit;
}

// Является ли чар братишкой, не совсем надёжная проверка, но хотя бы её тут потом можно будет поменять в одном месте
bool IsFellow(ref chr)
{
	if (!CheckAttribute(&chr, "Payment")) return false;
	if (chr.chr_ai.group != LAI_GROUP_PLAYER) return false;
	return true;
}