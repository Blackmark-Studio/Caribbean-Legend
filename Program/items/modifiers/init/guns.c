bool InitGunsModifiers(ref item)
{
	if (item.groupID != GUN_ITEM_TYPE && item.groupID != MUSKET_ITEM_TYPE) return false;

	string realId = item.id;
	if (CheckAttribute(item, "DefItemID")) realId = item.DefItemID; // для ген-предметов принимаем id базовых

	if (GetAttributeInt(item, "chargeq") > 1) AddDescriptor(item, "MultiCharge", -1);
	else AddDescriptor(item, "SingleCharge", -1);

	if (item.groupID == MUSKET_ITEM_TYPE) AddDescriptor(item, "TwoHanded", -1);
	else AddDescriptor(item, "OneHanded", -1);

	switch (realId)
	{
		case "pistol1":
		{
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "pistol3":
		{
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "pistol5":
		{
			AddDescriptor(item, "Fancy", -1);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "pistol7":
		{
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "pistol8":
		{
			AddDescriptor(item, "Exotic", -1);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "pistol10":
		{
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "pistol11":
		{
			AddDescriptor(item, "Special", -1);
			AddSpecialDescriptor(item, "MonsterGun");
		}
		break;
		case "pistol12":
		{
			AddDescriptor(item, "Special", -1);
			AddSpecialDescriptor(item, "Sawn-Off");
		}
		break;
		case "pistol14":
		{
			AddDescriptor(item, "Fancy", -1);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "howdah":
		{
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "mortairgun":
		{
			AddDescriptor(item, "Exotic", -1);
		}
		break;

		// Дальше мушкеты
		case "mushket1":
		{
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "mushket2":
		{
			AddDescriptor(item, "Bayonet", -1);
			AddDescriptor(item, "Fancy", -1);
		}
		break;

		case "mushket3":
		{
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "grape_mushket":
		{
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "mushket5":
		{
			AddDescriptor(item, "HighQuality", -1);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "mushket6":
		{
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "mushket2x2":
		{
			AddDescriptor(item, "HighQuality", -1);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "mushket7":
		{
			AddDescriptor(item, "HighQuality", -1);
			
		}
		break;
		case "mushket8":
		{
			AddDescriptor(item, "Special", -1);
			AddSpecialDescriptor(item, "Musket");

		}
		break;
		case "mushket9":
		{
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "mushket10":
		{
			AddDescriptor(item, "TwoHanded", -1);
			AddDescriptor(item, "SingleCharge", -1);
			AddDescriptor(item, "Fancy", -1);
			AddDescriptor(item, "Bayonet", -1);
		}
		break;
	}

	return true;
}
