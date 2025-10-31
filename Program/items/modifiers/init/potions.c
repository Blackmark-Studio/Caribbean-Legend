bool InitPotionModifiers(ref item)
{
	if (item.id == "cannabis7")
	{
		AddDescriptor(item, "Herb", -1);
		AddDescriptor(item, "Valuable", -1);
	}

	if (CheckAttribute(item, "TradeType") && item.TradeType != ITEM_TRADE_POTION) return false;

	string realId = item.id;
	if (CheckAttribute(item, "DefItemID")) realId = item.DefItemID; // для ген-предметов принимаем id базовых

	switch (realId)
	{
		case "potion5":
		{
			AddDescriptor(item, "HealPotion", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "potionrum":
		{
			AddDescriptor(item, "HealPotion", -1);
			AddDescriptor(item, "Alcohol", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "potionwine":
		{
			AddDescriptor(item, "HealPotion", -1);
			AddDescriptor(item, "Alcohol", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "potion1":
		{
			AddDescriptor(item, "HealPotion", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "potion3":
		{
			AddDescriptor(item, "HealPotion", -1);
			AddDescriptor(item, "AntidotePotion", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "potion2":
		{
			AddDescriptor(item, "HealPotion", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "potion4":
		{
			AddDescriptor(item, "HealPotion", -1);
			AddDescriptor(item, "AntidotePotion", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "PerksPotion":
		{
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
	}

	// Трава
	switch (realId)
	{
		case "cannabis1":
		{
			AddDescriptor(item, "Herb", -1);
		}
		break;
		case "cannabis2":
		{
			AddDescriptor(item, "Herb", -1);
		}
		break;
		case "cannabis3":
		{
			AddDescriptor(item, "Herb", -1);
		}
		break;
		case "cannabis4":
		{
			AddDescriptor(item, "Herb", -1);
		}
		break;
		case "cannabis5":
		{
			AddDescriptor(item, "Herb", -1);
		}
		break;
		case "cannabis6":
		{
			AddDescriptor(item, "Herb", -1);
		}
		break;
	}

	return true;
}
