
void ApplyMigration(ref migrationState)
{
	ref rShip;
	for (int i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		rShip = &RealShips[i];
		if("BaseType" !in rShip)
			continue;
		if ("Tuning.WindAgainst" in rShip)
			rShip.Tuning.rig = true;
	}

	JunkChangeWeight_0063();
}

void JunkChangeWeight_0063()
{
	ref item;
	item = ItemsFromID("mineral1");
	item.weight = 1.2; // медный кувшин
	item = ItemsFromID("mineral3");
	item.weight = 0.2; // свеча
	item = ItemsFromID("mineral4");
	item.weight = 0.5; // жук-геркулес
	item = ItemsFromID("mineral5");
	item.weight = 1.0; // бронзовая лампадка
	item = ItemsFromID("mineral6");
	item.weight = 0.7; // зеркальце
	item = ItemsFromID("mineral7");
	item.weight = 0.4; // фарфоровая трубка
	item = ItemsFromID("mineral8");
	item.weight = 0.8; // туфель
	item = ItemsFromID("mineral9");
	item.weight = 0.7; // кружка
	item = ItemsFromID("mineral10");
	item.weight = 0.3; // огниво
	item = ItemsFromID("mineral14");
	item.weight = 1.5; // крыло вампира
	item = ItemsFromID("mineral35");
	item.weight = 3.5; // лютня
	item = ItemsFromID("crab_pincers");
	item.weight = 2.2; // клешни
	item = ItemsFromID("crab_jaw");
	item.weight = 1.7; // жвалы
}