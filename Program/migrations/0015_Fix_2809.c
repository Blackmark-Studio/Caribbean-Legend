void ApplyMigration(ref migrationState) {
	
	ref refShip;
	int i, n;
	
	// Общий пулл кораблей (иниты)
	makeref(refShip,ShipsTypes[SHIP_MEMENTO]);
	refship.CabinType = "Cabin_memento";
	
	
	// Сгенерированные корабли
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if(!CheckAttribute(&RealShips[i],"BaseType")) continue;
		
		if(sti(RealShips[i].BaseType) == SHIP_MEMENTO)
		{
			RealShips[i].CabinType = "Cabin_memento";
		}
	}
	
	/* if(Get_My_Cabin() != "")
	{
		ref loc = &Locations[FindLocation(Get_My_Cabin())];
		string sBoxName, attr;
		aref arBoxItems;
		aref arCurItem;
		aref arBox;
		
		for (n = 2; n < 5; n++)
		{
			sBoxName = "box" + n;
			
			if (CheckAttribute(loc, sBoxName + ".money")) 
			{
				loc.box1.money = sti(loc.box1.money) + sti(loc.(sBoxName).money);
			}
			makearef(arBoxItems, loc.(sBoxName).items);
			makearef(arBox, loc.(sBoxName));
			
			for( i = 0; i < GetAttributesNum(arBoxItems); i++)
			{
				arCurItem = GetAttributeN(arBoxItems, i);
				attr = GetAttributeName(arCurItem);
				if (attr != "") 
				{
					if (!CheckAttribute(loc, "box1.items." + attr))
					{
						arBox.items.(attr) = 0;
					}
					
					loc.box1.items.(attr) = makeint(sti(loc.box1.items.(attr)) + makeint(GetAttributeValue(arCurItem)));
				}
			}
			// del
			DeleteAttribute(loc, sBoxName + ".items");
			loc.(sBoxName).items = "";
			loc.(sBoxName) = Items_MakeTime(0, 0, 1, 2003);
			loc.(sBoxName).money = 0;
		}
	} */
}