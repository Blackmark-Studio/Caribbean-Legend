bool InitArmorModifiers(ref item)
{
	if (item.groupID != CIRASS_ITEM_TYPE) return false;

	string realId = item.id;
	if (CheckAttribute(item, "DefItemID")) realId = item.DefItemID; // для ген-предметов принимаем id базовых

	switch (realId)
	{
		case "cirass1":
		{
			SetArmorDescriptors(item, ARMOR_HEAVY, ARMOR_MOLDED);
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "cirass2":
		{
			SetArmorDescriptors(item, ARMOR_HEAVY, ARMOR_STAMPS);
			AddDescriptor(item, "HeartDefence", -1);
		}
		break;
		case "cirass3":
		{
			SetArmorDescriptors(item, ARMOR_MEDIUM, ARMOR_STAMPS);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "cirass4":
		{
			SetArmorDescriptors(item, ARMOR_HEAVY, ARMOR_MOLDED);
			AddDescriptor(item, "Fancy", -1);
			AddDescriptor(item, "HeartDefence", -1);
		}
		break;
		case "underwater":
		{
			SetArmorDescriptors(item, ARMOR_HEAVY, ARMOR_MOLDED);
			AddDescriptor(item, "Special", -1);
			AddSpecialDescriptor(item, "UnderwaterSuit");
		}
		break;
		case "cirass10":
		{
			SetArmorDescriptors(item, ARMOR_MEDIUM, ARMOR_STAMPS);
			AddSpecialDescriptor(item, "IronsideArmor");
			AddDescriptor(item, "Special", -1);
		}
		break;
		case "cirass11":
		{
			SetArmorDescriptors(item, ARMOR_MEDIUM, ARMOR_STAMPS);
			AddDescriptor(item, "Exotic", -1);
			AddDescriptor(item, "HeartDefence", -1);
		}
		break;
		case "suit1":
		{
			SetArmorDescriptors(item, ARMOR_LIGHT, ARMOR_FABRIC);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "suit2":
		{
			SetArmorDescriptors(item, ARMOR_LIGHT, ARMOR_FABRIC);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "suit3":
		{
			SetArmorDescriptors(item, ARMOR_LIGHT, ARMOR_FABRIC);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "suit4":
		{
			SetArmorDescriptors(item, ARMOR_MEDIUM, ARMOR_LEATHER);
			AddDescriptor(item, "Unremarkable", -1);
			AddSpecialDescriptor(item, "LamportSuit");
			AddDescriptor(item, "Special", -1);
		}
		break;
		case "suit5":
		{
			SetArmorDescriptors(item, ARMOR_LIGHT, ARMOR_FABRIC);
			AddDescriptor(item, "Fancy", -1);
			AddSpecialDescriptor(item, "FrenchAdmiralSuit");
		}
		break;
		case "cirass5":
		{
			SetArmorDescriptors(item, ARMOR_LIGHT, ARMOR_LEATHER);
			AddDescriptor(item, "GoodFit", -1);
		}
		break;
		case "cirass6":
		{
			SetArmorDescriptors(item, ARMOR_LIGHT, ARMOR_LEATHER);
			AddDescriptor(item, "Unremarkable", -1);
			AddDescriptor(item, "HeartDefence", -1);
		}
		break;
		case "cirass7":
		{
			SetArmorDescriptors(item, ARMOR_LIGHT, ARMOR_PLATES);
		}
		break;
		case "cirass8":
		{
			SetArmorDescriptors(item, ARMOR_LIGHT, ARMOR_PLATES);
			AddDescriptor(item, "GoodFit", -1);
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "cirass9":
		{
			SetArmorDescriptors(item, ARMOR_LIGHT, ARMOR_PLATES);
			AddDescriptor(item, "GoodFit", -1);
			AddDescriptor(item, "HeartDefence", -1);
		}
		break;
	}

	return true;
}
