void ApplyMigration(ref migrationState)
{
	Ships_speedrate();
	SetCharacterPerk(pchar, "Rush");
	SetCharacterPerk(pchar, "Energaiser");
}

void Ships_speedrate()
{
	int i;
	bool bOk;
	ref   shTo;

	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		bOk = false;
		if (!CheckAttribute(&RealShips[i], "BaseType")) continue;

		switch (sti(RealShips[i].BaseType))
		{
			// Квестовые, перезаписываем:
			case SHIP_PINK:           bOk = true; break;  // Пинк "Принципио"
			case SHIP_LADYBETH:       bOk = true; break;  // Патрульная шнява "Леди Бет"
			case SHIP_MEMENTO:        bOk = true; break; // "Мементо"
			case SHIP_MAYFANG:        bOk = true; break;  // Лёг. шебека "Мейфенг"
			case SHIP_MIRAGE:         bOk = true; break;  // Приватный кеч "Мираж"
			case SHIP_VALCIRIA:       bOk = true; break; // Патр. бриг "Валькирия"
			case SHIP_HIMERA:         bOk = true; break; // Воен. кеч "Химера"

			case SHIP_POLACRE_QUEST:  bOk = true; break;  // Тяж. полакр "Тореро"
			case SHIP_GALEON_SM:      bOk = true; break;  // Королевский галеон "Святое Милосердие"

			case SHIP_ELCASADOR:      bOk = true; break;  // Исп. галеон "Эль касадор"
			case SHIP_CORVETTE_QUEST: bOk = true; break; // Тяжелый корвет "Гриффондор"
			case SHIP_FRIGATE_L:      bOk = true; break; // Быстрый фрегат "Фортуна"

			case SHIP_CURSED_FDM:     bOk = true; break;  // "Летящее сердце" (Калючка 1)
			case SHIP_FDM:            bOk = true; break;  // "Летящее сердце" (Калючка 2)
			case SHIP_RENOVATED_FDM:  bOk = true; break;  // "Летящее сердце" (Калючка 3)

			case SHIP_ECLIATON:       bOk = true; break; // Фр. линейный кор. "Эклятон"
		}
		if(bOk)
		{
			shTo = &RealShips[i];
			if(CheckAttribute(shTo, "Tuning.SpeedRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}    
			}
		}
    }
}
