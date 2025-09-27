// метод расчета от опыта солдат, даёт бонус в НР (или пенальти) с учётом второй команды
void GetCoordinatedBoardingHP(ref player, ref companion, int playerCrew, int companionCrew, ref float_boarding_player_hp)
{
	int totalCrew = playerCrew + companionCrew;
	float baseHP = LAi_GetCharacterMaxHP(player) / 3.0;  // нативное, треть от НР кэпа идет в базу бонуса;

	// опыты
	float playerExp    = GetCrewExp(player, "Soldiers");
	float companionExp = GetCrewExp(companion, "Soldiers");
	float totalExp = (playerExp * playerCrew + companionExp * companionCrew) / totalCrew;

	// морали
	int playerMoral    = GetCharacterCrewMorale(player);
	int companionMoral = GetCharacterCrewMorale(companion);
	int totalMoral = (playerMoral * playerCrew + companionMoral * companionCrew) / totalCrew;

	// игнорируем минимальную команду, оставшуюся у компаньона, этим можно пренебречь
	player.Ship.Crew.Morale          = totalMoral; 
	player.Ship.Crew.Exp.Soldiers    = totalExp;
	companion.Ship.Crew.Morale       = totalMoral; 
	companion.Ship.Crew.Exp.Soldiers = totalExp;

	// нативная формула из GetBoardingHP
	baseHP = baseHP * (totalExp / GetCrewExpRate() - 0.7 + makefloat(totalMoral - MORALE_NORMAL)); 
	
	if (MOD_BETTATESTMODE == "On") 
	{
		Log_Info("Опыт " + playerExp + " К " + companionExp + " = " + totalExp);
		Log_Info("Мораль " + playerMoral + " К " + companionMoral + " = " + totalMoral);
		Log_Info("Итого хпшечка: " + baseHP);
	}

	float_boarding_player_hp = baseHP;
}

// получаем соседний корабль (to do надо бы искать ближайший или с наибольшей командой)
ref GetNearestCompanion(ref chr, ref enemy)
{
	int cn;
	ref officer;

	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(chr,i);
		if (cn ==-1) continue;

		officer = GetCharacter(cn);
		if (!GetRemovable(officer) || IsMainCharacter(officer)) continue;
		if (Ship_GetDistance2D(officer, enemy) < 200) return officer;
	}

	return &NullCharacter;
}

// поиск корабля компаньона и расчёт команды
void CoordinatedBoardingStart(ref player, ref enemy, ref boarding_player_hp, ref playerCrew, ref playerHpCrew)
{
	ref companion = GetNearestCompanion(player, enemy);
	if (companion.id == "none" ) return;
	if (NavyPenalty(companion) > 0) {
		notification(StringFromKey("boarding_11"), "Sailing"); //не даём читерить с компаньоном на большом корабле
		return;
	}

	int iBonusCrew = GetWeaponCrew(companion, iClamp(0,2000,GetCrewQuantity(companion) - GetMinCrewQuantity(companion))); // учёт с оружием
	if (iBonusCrew == 0) return; // жаль, подмога не пришла, подкрепление не прислали...
	
	if (MOD_BETTATESTMODE == "On") Log_Info("Команда " + playerCrew + " + " + iBonusCrew);
	GetCoordinatedBoardingHP(player, companion, makeint(playerCrew), iBonusCrew, &boarding_player_hp); // считаем по новому хпшечку с учётом пропорции команд
	RemoveCharacterGoodsSelf(companion, GOOD_WEAPON, makeint(iBonusCrew/2 + 0.5)); // минусуем оружие у компаньона
	SetCrewQuantity(companion, GetCrewQuantity(companion) - iBonusCrew);           // оставляем минимальную команду
	AddCharacterExpToSkill(companion, "Defence",   makeint(iBonusCrew / 2 + 0.5)); // опыт выдаётся по аналогии с GetTroopersCrewQuantity для нативного штурма форта
	AddCharacterExpToSkill(companion, "Grappling", makeint(iBonusCrew / 2 + 0.5)); // опыт выдаётся по аналогии с GetTroopersCrewQuantity для нативного штурма форта
	enemy.CoordinatedCharIdx = companion.index;
	int sumCrew = makeint(playerCrew) + iBonusCrew;
	playerCrew = sumCrew;
	playerHpCrew = sumCrew; // пока не понял, зачем это две разных переменных, когда они всю дорогу равны
	Notification(StringFromKey("boarding_9", companion.ship.name, iBonusCrew), "CoordinatedBoarding"); 
}

void SetCompanionAsSwashbuckler(ref crewMember, int companionIdx, ref desk)
{
	ref companion = GetCharacter(companionIdx);
	if (makefloat(companion.Health.HP) <  50) return; // здоровье хотя бы Хорошее

	ChangeAttributesFromCharacter(crewMember, companion, false);
	crewMember.PersonalityCloneOrigIdx = companion.index;
	crewMember.CantLoot = true;
	if (!CheckAttribute(desk, "UpDeckType")) return;

	Notification(StringFromKey("boarding_4", companion.name), GetMessagePortrait(&companion));
}

// распределяем потери по кораблю ГГ и присоединившегося компаньона
void CoordinatedBoardingEnd(ref player, string companionIdx, int crewSurvived)
{
	ref companion = GetCharacter(sti(companionIdx));
	int maxCrew = GetMaxCrewQuantity(player);
	if (crewSurvived <= maxCrew) {
		SetCrewQuantity(player, crewSurvived);
		return;
	}

	SetCrewQuantity(player, maxCrew);
	int leftCrew = crewSurvived - maxCrew;
	SetCrewQuantity(companion, GetCrewQuantity(companion) + leftCrew);
	notification(StringFromKey("boarding_10", companion.ship.name, leftCrew), "Troopers"); 
}
