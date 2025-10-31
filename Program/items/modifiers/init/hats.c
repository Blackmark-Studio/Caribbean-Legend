bool InitHatModifiers(ref item)
{
	if (item.groupID != HAT_ITEM_TYPE) return false;

	string realId = item.id;
	aref modifier;
	if (CheckAttribute(item, "DefItemID")) realId = item.DefItemID; // для ген-предметов принимаем id базовых

	switch (realId)
	{
		case "hat1":
		{
			AddDescriptor(item, "Unremarkable", -1);
			modifier = AddCallback(item, CT_EQUIP, "CondottieresHat");
			modifier.arg0 = 0.05;
		}
		break;
		case "hat2":
		{
			AddDescriptor(item, "Fancy", -1);
			modifier = AddCallback(item, CT_EQUIP, "CavaliersHat");
			modifier.arg0 = 0.07;
		}
		break;
		case "hat3":
		{
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "hat4":
		{
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "hat5":
		{
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "hat6":
		{
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "hat7":
		{
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "hat8":
		{
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "hat9":
		{
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "hat10":
		{
			AddDescriptor(item, "Alchemy", -1);
			AddDescriptor(item, "ArmorMaterial_2", -1);
			AddDescriptor(item, "Fragile", -1);
			SetModifier(item, M_REDUCE_DAMAGE, 0.18);
		}
		break;
		case "hat11":
		{
			AddDescriptor(item, "Exotic", -1);
			AddDescriptor(item, "Special", -1);
			SetModifier(item, SPECIAL_TYPE + SPECIAL_E, 2);
		}
		break;
	}

	return true;
}
