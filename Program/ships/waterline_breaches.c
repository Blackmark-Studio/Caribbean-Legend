// Чекаем пробоины при попадании
void BreachTheHull(ref targetCaptain, ref shooterCaptain, float ballDistance, float canonDmgMtp )
{
	if (ballDistance > 450.0 ) return;                           // навесом борта не пробиваем
	if (GetAttributeInt(shooterCaptain, "TmpPerks.BeneathWaterline") != 1) return;  // перка нет
	if (rand(35 - makeint(canonDmgMtp)) != 1) return;            // большой пушка – чаще дырка

	int curBreaches = GetAttributeInt(targetCaptain, "Ship.WaterlineBreaches");
	if (curBreaches > 4) return;                                 // больше 5 пробоин не делаем

	targetCaptain.Ship.WaterlineBreaches = curBreaches + 1;
	notification(StringFromKey("perks_3", targetCaptain.Ship.Name), "Brander");
}

// Применяем пробоины к осадке
float GetShipBreachedImmersion(ref captain, ref ship, float baseImmersion, float currentHP, float baseHP)
{
	float breachImmersion = 0;
	int waterLineBreaches = 0;
	if (CheckAttribute(ship, "breachImmersion")) breachImmersion = stf(ship.breachImmersion);       // текущий уровень погружения от пробоин
	float resultImmersion = baseImmersion + breachImmersion;                                        // текущее погружение итого
	if (rand(2) != 1) return resultImmersion;                                                       // процесс неравномерный, да и нам нет нужды каждую секунду всё пересчитывать
	if (CheckAttribute(ship, "waterlineBreaches")) waterLineBreaches = sti(ship.waterlineBreaches); // текущее количество пробоин, макс. 5
	if (breachImmersion == 0 && waterLineBreaches == 0) return resultImmersion;                     // всё починили

	float targetImmersion = fClamp(0, 2.4 - (currentHP / baseHP) * 2, waterLineBreaches + 0.5);     // ограничиваем погружение целостностью корпуса в некоторой степени
	if (waterLineBreaches == 0 ) targetImmersion = 0;                                               // если всё заделали, надо бы всплывать
	float immersionStep = 0.01 + 0.01 * waterLineBreaches;                                          // скорость погружения за одну проверку

	// если текущее погружение ниже целевого, погружаем
	if (breachImmersion < targetImmersion)
	{
		ship.breachImmersion = breachImmersion + immersionStep; 
		resultImmersion = resultImmersion + immersionStep;

		int repair = makeint(50 - stf(captain.TmpSkill.Repair) * 50);
		// экипаж не тратит время на выкачивание воды, а латает пробоину
		if (rand(20 + repair) == 1) {
			notification(StringFromKey("perks_2", ship.name), "Repair"); // на корабле n залатали пробоину
			ship.waterlineBreaches = iClamp(0, 5, waterLineBreaches - 1); 
		}
	}
	else // часть пробоин заделали, откачиваем воду
	{
		ship.breachImmersion = breachImmersion - 0.03; 
		resultImmersion = resultImmersion - 0.03;
		if (stf(ship.breachImmersion) <= 0) DeleteAttribute(ship, "breachImmersion");
	}

	return resultImmersion;
}

// Влияние погружения от пробоин на скорость
float GetBreachesMtp(float breacheImmersion)
{
	return 1.0 - breacheImmersion * 0.1; // 1.00..0.50 при 0..5 пробоинах в пересчете на текущее погружение от протечки
}

// Починка всех пробоин
void RemoveAllBreaches()
{
	DeleteAttribute(pchar, "Ship.waterlineBreaches");
	DeleteAttribute(pchar, "Ship.breachImmersion");

	ref chref;
	int chrIndex;
	for (int i=1; i<COMPANION_MAX; i++)
	{
		chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex == -1) continue;

		makeref(chref, Characters[i]);
		DeleteAttribute(chref, "Ship.waterlineBreaches");
		DeleteAttribute(chref, "Ship.breachImmersion");
	}
}