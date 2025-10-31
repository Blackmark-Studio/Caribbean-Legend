void ApplyMigration(ref migrationState) {

	ChangeTalismanDurations0023();

	shipsReInitNewSpeeds();
	
	cabins_reload_locators();
}

void ChangeTalismanDurations0023()
{
	ref item;
	item = ItemsFromId("totem_01");
	item.time = 50;
	item = ItemsFromId("totem_02");
	item.time = 50;
	item = ItemsFromId("totem_03");
	item.time = 50;
	item = ItemsFromId("totem_04");
	item.time = 50;
	item = ItemsFromId("totem_06");
	item.time = 50;
	item = ItemsFromId("totem_05");
	item.time = 50;
	item = ItemsFromId("totem_07");
	item.time = 50;
	item = ItemsFromId("totem_08");
	item.time = 50;
	item = ItemsFromId("totem_09");
	item.time = 50;
	item = ItemsFromId("totem_10");
	item.time = 50;
	item = ItemsFromId("totem_11");
	item.time = 50;
	item = ItemsFromId("totem_12");
	item.time = 50;
	item = ItemsFromId("totem_13");
	item.time = 50;
}

void shipsReInitNewSpeeds()
{
    ref refShip;
    int i;

    // === Переинициализация SpeedRate по ID (ShipsTypes) ===
    // 7 класс
    makeref(refShip, ShipsTypes[SHIP_TARTANE]);           refShip.SpeedRate = 7.10;  // Баркас
    makeref(refShip, ShipsTypes[SHIP_WAR_TARTANE]);       refShip.SpeedRate = 7.25;  // Тартана

    // 6 класс
    makeref(refShip, ShipsTypes[SHIP_CAREERLUGGER]);      refShip.SpeedRate = 8.20;  // Кур. люггер
    makeref(refShip, ShipsTypes[SHIP_LUGGER]);            refShip.SpeedRate = 7.65;  // Люггер
    makeref(refShip, ShipsTypes[SHIP_BARKENTINE]);        refShip.SpeedRate = 7.90;  // Баркентина
    makeref(refShip, ShipsTypes[SHIP_SLOOP]);             refShip.SpeedRate = 7.50; refShip.WindAgainstSpeed = 1.35; // Шлюп
    makeref(refShip, ShipsTypes[SHIP_PINK]);              refShip.SpeedRate = 8.60;  // Пинк "Принципио" (КВ)

    // 5 класс
    makeref(refShip, ShipsTypes[SHIP_SCHOONER_W]);        refShip.SpeedRate = 8.50;  // Воен. шхуна
    makeref(refShip, ShipsTypes[SHIP_SCHOONER]);          refShip.SpeedRate = 8.15;  // Шхуна
    makeref(refShip, ShipsTypes[SHIP_BARQUE]);            refShip.SpeedRate = 9.70;  // Барк
    makeref(refShip, ShipsTypes[SHIP_SHNYAVA]);           refShip.SpeedRate = 8.95;  // Шнява
    makeref(refShip, ShipsTypes[SHIP_LADYBETH]);          refShip.SpeedRate = 9.65;  // Патрульная шнява "Леди Бет" (КВ)

    // 4 класс
    makeref(refShip, ShipsTypes[SHIP_XebekVML]);          refShip.SpeedRate = 8.55;  // Шебека
    makeref(refShip, ShipsTypes[SHIP_BRIG]);              refShip.SpeedRate = 11.25; // Бриг
    makeref(refShip, ShipsTypes[SHIP_BRIGANTINE]);        refShip.SpeedRate = 9.85;  // Бригантина
    makeref(refShip, ShipsTypes[SHIP_FLEUT]);             refShip.SpeedRate = 8.60;  // Флейт
    makeref(refShip, ShipsTypes[SHIP_CARAVEL]);           refShip.SpeedRate = 7.85;  // Каравелла
    makeref(refShip, ShipsTypes[SHIP_MEMENTO]);           refShip.SpeedRate = 10.40; // "Мементо" (КВ)
    makeref(refShip, ShipsTypes[SHIP_MAYFANG]);           refShip.SpeedRate = 9.00;  // Лёг. шебека "Мейфенг" (КВ)
    makeref(refShip, ShipsTypes[SHIP_MIRAGE]);            refShip.SpeedRate = 8.85;  // Прив. кеч "Мираж" (КВ)
    makeref(refShip, ShipsTypes[SHIP_VALCIRIA]);          refShip.SpeedRate = 11.20; // Патр. бриг "Валькирия" (КВ)
    makeref(refShip, ShipsTypes[SHIP_HIMERA]);            refShip.SpeedRate = 10.00; // Воен. кеч "Химера" (КВ)

    // 3 класс
    makeref(refShip, ShipsTypes[SHIP_CORVETTE]);          refShip.SpeedRate = 10.85; // Корвет
    makeref(refShip, ShipsTypes[SHIP_POLACRE]);           refShip.SpeedRate = 8.20;  // Полакр
    makeref(refShip, ShipsTypes[SHIP_PINNACE]);           refShip.SpeedRate = 8.15;  // Пинас
    makeref(refShip, ShipsTypes[SHIP_GALEON_L]);          refShip.SpeedRate = 8.00;  // Галеон
    makeref(refShip, ShipsTypes[SHIP_POLACRE_QUEST]);     refShip.SpeedRate = 9.60;  // Тяж. полакр "Тореро" (КВ)
    makeref(refShip, ShipsTypes[SHIP_GALEON_SM]);         refShip.SpeedRate = 8.85;  // Королевский галеон "Святое Милосердие" (КВ)

    // 2 класс
    makeref(refShip, ShipsTypes[SHIP_FRIGATE]);           refShip.SpeedRate = 10.05; // Фрегат
    makeref(refShip, ShipsTypes[SHIP_EASTINDIAMAN]);      refShip.SpeedRate = 8.65;  // Ост-индец
    makeref(refShip, ShipsTypes[SHIP_NAVIO]);             refShip.SpeedRate = 8.50;  // Навио
    makeref(refShip, ShipsTypes[SHIP_FRIGATE_H]);         refShip.SpeedRate = 8.20;  // Тяж. фрегат
    makeref(refShip, ShipsTypes[SHIP_GALEON_H]);          refShip.SpeedRate = 7.80;  // Тяж. галеон
    makeref(refShip, ShipsTypes[SHIP_ELCASADOR]);         refShip.SpeedRate = 8.95;  // Исп. галеон "Эль касадор" (КВ)
    makeref(refShip, ShipsTypes[SHIP_CORVETTE_QUEST]);    refShip.SpeedRate = 11.40; // Тяжелый корвет "Гриффондор" (КВ)
    makeref(refShip, ShipsTypes[SHIP_FRIGATE_L]);         refShip.SpeedRate = 11.95; // Быстрый фрегат "Фортуна" (КВ)

    // Все версии FDM получают одно значение
    makeref(refShip, ShipsTypes[SHIP_CURSED_FDM]);        refShip.SpeedRate = 9.15;  // "Летящее сердце" (Калючка 1) (КВ)
    makeref(refShip, ShipsTypes[SHIP_FDM]);               refShip.SpeedRate = 9.15;  // "Летящее сердце" (Калючка 2) (КВ)
    makeref(refShip, ShipsTypes[SHIP_RENOVATED_FDM]);     refShip.SpeedRate = 9.15;  // "Летящее сердце" (Калючка 3) (КВ)

    // 1 класс
    makeref(refShip, ShipsTypes[SHIP_LINESHIP]);          refShip.SpeedRate = 8.80;  // Военный корабль
    makeref(refShip, ShipsTypes[SHIP_LSHIP_ENG]);         refShip.SpeedRate = 9.30;  // Анг. линейный кор.
    makeref(refShip, ShipsTypes[SHIP_LSHIP_FRA]);         refShip.SpeedRate = 8.95;  // Фр. линейный кор.
    makeref(refShip, ShipsTypes[SHIP_LSHIP_SPA]);         refShip.SpeedRate = 9.30;  // Исп. линейный кор.
    makeref(refShip, ShipsTypes[SHIP_LSHIP_HOL]);         refShip.SpeedRate = 9.10;  // Голл. линейный кор.
    makeref(refShip, ShipsTypes[SHIP_ECLIATON]);          refShip.SpeedRate = 10.00; // Фр. линейный кор. "Эклятон" (КВ)


    // === Обновление уже созданных RealShips (ТОЛЬКО квестовые) ===
    for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
    {
        if (!CheckAttribute(&RealShips[i], "BaseType")) continue;

        switch (sti(RealShips[i].BaseType))
        {
            // Квестовые, перезаписываем:
            case SHIP_PINK:           RealShips[i].SpeedRate = 8.60; break;  // Пинк "Принципио"
            case SHIP_LADYBETH:       RealShips[i].SpeedRate = 9.65; break;  // Патрульная шнява "Леди Бет"
            case SHIP_MEMENTO:        RealShips[i].SpeedRate = 10.40; break; // "Мементо"
            case SHIP_MAYFANG:        RealShips[i].SpeedRate = 9.00; break;  // Лёг. шебека "Мейфенг"
            case SHIP_MIRAGE:         RealShips[i].SpeedRate = 8.85; break;  // Приватный кеч "Мираж"
            case SHIP_VALCIRIA:       RealShips[i].SpeedRate = 11.20; break; // Патр. бриг "Валькирия"
            case SHIP_HIMERA:         RealShips[i].SpeedRate = 10.00; break; // Воен. кеч "Химера"

            case SHIP_POLACRE_QUEST:  RealShips[i].SpeedRate = 9.60; break;  // Тяж. полакр "Тореро"
            case SHIP_GALEON_SM:      RealShips[i].SpeedRate = 8.85; break;  // Королевский галеон "Святое Милосердие"

            case SHIP_ELCASADOR:      RealShips[i].SpeedRate = 8.95; break;  // Исп. галеон "Эль касадор"
            case SHIP_CORVETTE_QUEST: RealShips[i].SpeedRate = 11.40; break; // Тяжелый корвет "Гриффондор"
            case SHIP_FRIGATE_L:      RealShips[i].SpeedRate = 11.95; break; // Быстрый фрегат "Фортуна"

            case SHIP_CURSED_FDM:     RealShips[i].SpeedRate = 9.15; break;  // "Летящее сердце" (Калючка 1)
            case SHIP_FDM:            RealShips[i].SpeedRate = 9.15; break;  // "Летящее сердце" (Калючка 2)
            case SHIP_RENOVATED_FDM:  RealShips[i].SpeedRate = 9.15; break;  // "Летящее сердце" (Калючка 3)

            case SHIP_ECLIATON:       RealShips[i].SpeedRate = 10.00; break; // Фр. линейный кор. "Эклятон"

        }
    }
}

void cabins_reload_locators()
{
	int n;
	
	n = FindLocation("My_Cabin_Medium2");
	
	Locations[n].locators_radius.reload.reload1 = 0.8;
    Locations[n].locators_radius.reload.reload2 = 0.5;
	
	n = FindLocation("Cabin_Medium2");
	Locations[n].locators_radius.reload.reload1 = 0.8;
    Locations[n].locators_radius.reload.reload2 = 0.5;
	
	n = FindLocation("My_Cabin_Medium");
	Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;
	
	n = FindLocation("Cabin_Medium");
	Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;
	
	n = FindLocation("My_Cabin_Small");
	Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;
	
	n = FindLocation("Cabin_Small");
	Locations[n].locators_radius.reload.reload1 = 0.5;
    Locations[n].locators_radius.reload.reload2 = 0.5;
}