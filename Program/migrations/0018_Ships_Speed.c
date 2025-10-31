void ApplyMigration(ref migrationState) {
	
	shipsReInit();
	setMangarosaDurations();
	Cannon[CANNON_TYPE_CANNON_LBS3].Sound  = "Cannon_Shot/Cannon_small";
	Cannon[CANNON_TYPE_CANNON_LBS6].Sound  = "Cannon_Shot/Cannon_small";
	Cannon[CANNON_TYPE_CANNON_LBS8].Sound  = "Cannon_Shot/Cannon_small";
	Cannon[CANNON_TYPE_CANNON_LBS12].Sound = "Cannon_Shot/Cannon_small";
	Cannon[CANNON_TYPE_CANNON_LBS16].Sound = "Cannon_Shot/Cannon_middle";
	Cannon[CANNON_TYPE_CANNON_LBS18].Sound = "Cannon_Shot/Cannon_middle";
	Cannon[CANNON_TYPE_CANNON_LBS20].Sound = "Cannon_Shot/Cannon_middle";
	Cannon[CANNON_TYPE_CANNON_LBS24].Sound = "Cannon_Shot/Cannon_middle";
	Cannon[CANNON_TYPE_CANNON_LBS32].Sound = "Cannon_Shot/Cannon_large";
	Cannon[CANNON_TYPE_CANNON_LBS36].Sound = "Cannon_Shot/Cannon_large";
	Cannon[CANNON_TYPE_CANNON_LBS42].Sound = "Cannon_Shot/Cannon_large";
	Cannon[CANNON_TYPE_CANNON_LBS48].Sound = "Cannon_Shot/Cannon_large";
	Cannon[CANNON_TYPE_CULVERINE_LBS8].Sound  = "Cannon_Shot/Cannon_small";
	Cannon[CANNON_TYPE_CULVERINE_LBS18].Sound = "Cannon_Shot/Cannon_middle";
	Cannon[CANNON_TYPE_CULVERINE_LBS36].Sound = "Cannon_Shot/Cannon_large";
}

void setMangarosaDurations()
{
	// сроки мангаросы
	ref item;
	item = ItemsFromID("mangarosapower");
	item.time = 50;
	item = ItemsFromID("mangarosatotal");
	item.time = 50;
	item = ItemsFromID("mangarosafast");
	item.time = 50;
}

void shipsReInit()
{
	ref refShip;
	int i;
	
	// Общий пулл кораблей (иниты)
	
	makeref(refShip,ShipsTypes[SHIP_TARTANE]); //баркас
	refShip.SpeedRate = 8.75;

	makeref(refShip,ShipsTypes[SHIP_WAR_TARTANE]); //тартана // ку
	refShip.SpeedRate = 8.90;
	refShip.WindAgainstSpeed = 1.12;

	makeref(refShip,ShipsTypes[SHIP_CAREERLUGGER]); //кур. люггер
	refShip.SpeedRate = 10.05;

	makeref(refShip,ShipsTypes[SHIP_LUGGER]); //люггер
	refShip.SpeedRate = 9.45;

	makeref(refShip,ShipsTypes[SHIP_BARKENTINE]); //баркентина //ку
	refShip.SpeedRate = 9.70;
	refShip.WindAgainstSpeed = 1.25;

	makeref(refShip,ShipsTypes[SHIP_SLOOP]); //шлюп //ку
	refShip.SpeedRate = 9.90;
	refShip.WindAgainstSpeed = 0.85;

	makeref(refShip,ShipsTypes[SHIP_SCHOONER_W]); // воен. шхуна
	refShip.SpeedRate = 10.45;
	
	makeref(refShip,ShipsTypes[SHIP_SCHOONER]); // шхуна
	refShip.SpeedRate = 10.00;

	makeref(refShip,ShipsTypes[SHIP_BARQUE]); // барк
	refShip.SpeedRate = 11.90;

	makeref(refShip,ShipsTypes[SHIP_SHNYAVA]); // шнява
	refShip.SpeedRate = 11.00;

	makeref(refShip,ShipsTypes[SHIP_XebekVML]); // шебека
	refShip.SpeedRate = 10.50;

	makeref(refShip,ShipsTypes[SHIP_BRIG]); // бриг
	refShip.SpeedRate = 13.80;

	makeref(refShip,ShipsTypes[SHIP_BRIGANTINE]); // бригантина
	refShip.SpeedRate = 12.10;

	makeref(refShip,ShipsTypes[SHIP_FLEUT]); // флейт
	refShip.SpeedRate = 10.60;

	makeref(refShip,ShipsTypes[SHIP_CARAVEL]); // каравелла
	refShip.SpeedRate = 9.65;
	
	makeref(refShip,ShipsTypes[SHIP_CORVETTE]); // корвет
	refShip.SpeedRate = 13.35;

	makeref(refShip,ShipsTypes[SHIP_POLACRE]); // полакр
	refShip.SpeedRate = 10.05;

	makeref(refShip,ShipsTypes[SHIP_PINNACE]); // пинас
	refShip.SpeedRate = 10.05;

	makeref(refShip,ShipsTypes[SHIP_GALEON_L]); // галеон
	refShip.SpeedRate = 9.85;

	makeref(refShip,ShipsTypes[SHIP_FRIGATE]); // фрегат
	refShip.SpeedRate = 12.35;

	makeref(refShip,ShipsTypes[SHIP_EASTINDIAMAN]); //ост-индец //ку
	refShip.SpeedRate = 10.65;
	refShip.WindAgainstSpeed = 0.84;

	makeref(refShip,ShipsTypes[SHIP_NAVIO]); // навиo
	refShip.SpeedRate = 10.45;

	makeref(refShip,ShipsTypes[SHIP_FRIGATE_H]); // тяж. фрегат //ку
	refShip.SpeedRate = 10.05;
	refShip.WindAgainstSpeed = 0.61;
	
	makeref(refShip,ShipsTypes[SHIP_GALEON_H]); // тяж. галеон //ку
	refShip.SpeedRate = 9.55;
	refShip.WindAgainstSpeed = 0.78;

	makeref(refShip,ShipsTypes[SHIP_LINESHIP]); // военный корабль
	refShip.SpeedRate = 8.80;

	makeref(refShip,ShipsTypes[SHIP_LSHIP_ENG]); // анг. линейный кор.
	refShip.SpeedRate = 9.30;

	makeref(refShip,ShipsTypes[SHIP_LSHIP_FRA]); // фр. линейный кор.
	refShip.SpeedRate = 8.95;
	
	makeref(refShip,ShipsTypes[SHIP_LSHIP_SPA]); // исп. линейный кор.
	refShip.SpeedRate = 9.30;
	
	makeref(refShip,ShipsTypes[SHIP_LSHIP_HOL]); // голл. линейный кор.
	refShip.SpeedRate = 9.10;

	// Сгенерированные корабли
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
		
        if(sti(RealShips[i].BaseType) == SHIP_PINK) // пинк "Принципио"
        {
            RealShips[i].SpeedRate = 10.35;
        }

        if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
            
        if(sti(RealShips[i].BaseType) == SHIP_LADYBETH) // патрульная шнява "Леди Бет"
        {
            RealShips[i].SpeedRate = 11.60;
        }

        if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
            
        if(sti(RealShips[i].BaseType) == SHIP_MEMENTO) // "Мементо"
        {
            RealShips[i].SpeedRate = 11.90;
        }
            
        if(sti(RealShips[i].BaseType) == SHIP_MAYFANG) // лёг. шебека "Мейфенг"
        {
            RealShips[i].SpeedRate = 10.90;
        }
            
        if(sti(RealShips[i].BaseType) == SHIP_MIRAGE) // прив. кеч "Мираж"
        {
            RealShips[i].SpeedRate = 10.65;
        }

        if(sti(RealShips[i].BaseType) == SHIP_VALCIRIA) // патр. бриг "Валькирия"
        {
            RealShips[i].SpeedRate = 13.50;
        }

        if(sti(RealShips[i].BaseType) == SHIP_HIMERA) // воен. кеч "Химера"
        {
            RealShips[i].SpeedRate = 10.85;
        }

        if(sti(RealShips[i].BaseType) == SHIP_POLACRE_QUEST) // тяж. полакр "Тореро" //ку
        {
            RealShips[i].SpeedRate = 11.55;
            RealShips[i].WindAgainstSpeed = 0.98;
        }

        if(sti(RealShips[i].BaseType) == SHIP_GALEON_SM) // королевский галеон "Святое Милосердие"
        {
            RealShips[i].SpeedRate = 10.65;
        }

        if(sti(RealShips[i].BaseType) == SHIP_ELCASADOR) // исп. галеон "Эль Касадор"
        {
            RealShips[i].SpeedRate = 10.75;
        }

        if(sti(RealShips[i].BaseType) == SHIP_CORVETTE_QUEST) // тяжёлый корвет "Гриффондор"
        {
            RealShips[i].SpeedRate = 13.75;
        }

        if(sti(RealShips[i].BaseType) == SHIP_FRIGATE_L) // быстрый фрегат "Фортуна"
        {
            RealShips[i].SpeedRate = 14.15;
        }

        if(sti(RealShips[i].BaseType) == SHIP_CURSED_FDM) // линейный галеон "Летящее сердце" (Калючка 1)
        {
            RealShips[i].SpeedRate = 11.00;
        }
        if(sti(RealShips[i].BaseType) == SHIP_FDM) // "Летящее сердце" (Калючка 2)
        {
            RealShips[i].SpeedRate = 11.00;
        }
        if(sti(RealShips[i].BaseType) == SHIP_RENOVATED_FDM) // "Летящее сердце" (Калючка 3)
        {
            RealShips[i].SpeedRate = 11.00;
        }

        if(sti(RealShips[i].BaseType) == SHIP_ECLIATON) // фр. линейный кор. "Эклятон"
        {
            RealShips[i].SpeedRate = 10.00;
        }
    }
}


