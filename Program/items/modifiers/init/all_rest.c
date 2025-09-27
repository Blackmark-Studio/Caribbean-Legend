bool InitRestModifiers(ref item)
{

	string realId = item.id;
	if (CheckAttribute(item, "DefItemID")) realId = item.DefItemID; // для ген-предметов принимаем id базовых

	// Все карты
	if (CheckAttributeEqualTo(item, "ItemType", "MAP"))
	{
		AddDescriptor(item, "Map", -1);
		AddDescriptor(item, "Valuable", -1);
	}
	// Все рецепты
	if (findsubstr(item.id, "recipe_" , 0) != -1)
	{
		AddDescriptor(item, "Alchemy", -1);
		AddDescriptor(item, "Valuable", -1);
	}

	// Драгоценности
	switch (realId)
	{
		case "jewelry2":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry1":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry7":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry4":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry9":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry3":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry8":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry14":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry15":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry16":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry17":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry18":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry20":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry21":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry22":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry23":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "gold_dublon":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry53":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry52":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral10":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Tailor_Tool":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mechanic_Tool":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Tigel":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral27":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral15":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral16":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral32":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral21":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "bussol":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "sextant2":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "Mechanic_Tool":
		{
			AddDescriptor(item, "Tool", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
	}

	// Украшения
	switch (realId)
	{
		case "jewelry40":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry41":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry42":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry43":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry44":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry45":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry46":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry47":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry48":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry49":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry50":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry24":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry51":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry25":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry26":
		{
			AddDescriptor(item, "Trinket", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
	}

	// Хлам
	switch (realId)
	{
		case "OxyHydSilver":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "Mineral23":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral11":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "crab_pincers":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "Mineral24":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral12":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "crab_jaw":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral25":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral13":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "ArmoryPaper":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "Mineral1":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral26":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral14":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral2":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry19":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral3":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral28":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral4":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral29":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "Mineral17":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral30":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral18":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral6":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral31":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral19":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral7":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral20":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral8":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral33":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral34":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral22":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral35":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "clock1":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "sand_clock":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "compass1":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "astrolab":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "sextant1":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "clock3":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "Mineral5":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "Mineral9":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "chest_open":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "m8_barrel":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "icollection":
		{
			AddDescriptor(item, "Jewelery", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "jewelry13":
		{
			AddDescriptor(item, "Metal", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry5":
		{
			AddDescriptor(item, "Metal", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry12":
		{ 
			AddDescriptor(item, "Metal", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry11":
		{ 
			AddDescriptor(item, "Metal", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry10":
		{ 
			AddDescriptor(item, "Metal", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "jewelry6":
		{ 
			AddDescriptor(item, "Metal", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "potion6":
		{
			AddDescriptor(item, "EnhancingPotion", -1);
		}
		break;
		case "berserker_potion":
		{
			AddDescriptor(item, "EnhancingPotion", -1);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "mangarosafast":
		{
			AddDescriptor(item, "EnhancingPotion", -1);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "mangarosapower":
		{
			AddDescriptor(item, "EnhancingPotion", -1);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "mangarosatotal":
		{
			AddDescriptor(item, "EnhancingPotion", -1);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "vodka":
		{
			AddDescriptor(item, "EnhancingPotion", -1);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
	}

	return true;
}
