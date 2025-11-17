bool InitWeaponModifiers(ref item)
{
	if (item.groupID != BLADE_ITEM_TYPE) return false;

	string realId = item.id;
	if (CheckAttribute(item, "DefItemID")) realId = item.DefItemID; // для ген-предметов принимаем id базовых

	switch (realId)
	{
		case "unarmed":
		{
			AddDescriptor(item, M_WEAPON_TYPE, WEAPON_LIGHT);
			SetWeaponDamageByStrikes(item, WEAPON_LIGHT, 0.85, 1.15);
		}
		break;
		case "slave_01":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_CURVE, 0.85, 1.15);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "blade_01":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_STRAIGHT, 0.85, 1.15);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "blade_02":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_STRAIGHT, 0.75, 1.25);
		}
		break;
		case "blade_03":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_LONG, WEAPON_STRAIGHT, 0.75, 1.25);
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "blade_04":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_STRAIGHT, 0.75, 1.25);
		}
		break;
		case "blade_08":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_LONG, WEAPON_CURVE, 0.75, 1.25);
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "blade_09":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_STRAIGHT, 0.65, 1.35);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "blade_15":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_STRAIGHT, 0.75, 1.25);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "blade_16":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_STRAIGHT, 0.65, 1.35);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "blade_22":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_LONG, WEAPON_CURVE, 0.65, 1.35);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "blade_27":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_LONG, WEAPON_STRAIGHT, 0.85, 1.15);
		}
		break;
		case "blade_39":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_STRAIGHT, 0.85, 1.15);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "blade_38":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_LONG, WEAPON_STRAIGHT, 0.75, 1.25);
		}
		break;
		case "blade_40":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_STRAIGHT, 0.65, 1.35);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "blade_17":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_STRAIGHT, 0.75, 1.25);
		}
		break;
		case "blade_18":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_LONG, WEAPON_STRAIGHT, 0.85, 1.15);
		}
		break;
		case "q_blade_18":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_LONG, WEAPON_STRAIGHT, 0.85, 1.15);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "blade_25":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_LONG, WEAPON_CURVE, 0.65, 1.35);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "blade_26":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_LONG, WEAPON_STRAIGHT, 0.65, 1.35);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "slave_02":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.75, 1.25);
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "machete2":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.65, 1.35);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "khopesh1":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.85, 1.15);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "khopesh2":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.85, 1.15);
		}
		break;
		case "blade_33":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_STRAIGHT, 0.85, 1.15);
		}
		break;
		case "blade_36":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_STRAIGHT, 0.85, 1.15);
		}
		break;
		case "blade_05":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_CURVE, 0.65, 1.35);
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "blade_11":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_STRAIGHT, 0.85, 1.15);
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "blade_12":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.75, 1.25);
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "blade_10":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.85, 1.15);
		}
		break;
		case "blade_23":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.75, 1.25);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "blade_30":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.65, 1.35);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "shamshir":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_CURVE, 0.85, 1.15);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "blade_SP_3low":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.75, 1.25);
			AddSpecialDescriptor(item, "Hungman");
			AddDescriptor(item, "Special", -1);
		}
		break;
		case "blade_SP_3":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.75, 1.25);
			AddSpecialDescriptor(item, "Hungman");
			AddDescriptor(item, "Special", -1);
		}
		break;
		case "blade_20":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_CURVE, 0.75, 1.25);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "blade_28":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_CURVE, 0.85, 1.15);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "blade_29":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_CURVE, 0.75, 1.25);
		}
		break;
		case "khopesh3":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.85, 1.15);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "pirate_cutlass":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_SHORT, WEAPON_CURVE, 0.65, 1.35);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "saber":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_STRAIGHT, 0.75, 1.25);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "blade_19":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_CURVE, 0.85, 1.15);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "blade_41":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_STRAIGHT, 0.75, 1.25);
			AddSpecialDescriptor(item, "Jian");
			AddDescriptor(item, "Special", -1);
		}
		break;
		case "topor_05":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_SHORT, WEAPON_CURVE, 0.85, 1.15);
		}
		break;
		case "blade_14":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_STRAIGHT, 0.85, 1.15);
		}
		break;
		case "topor_02":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_SHORT, WEAPON_CURVE, 0.75, 1.25);
		}
		break;
		case "topor_03":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_CURVE, 0.65, 1.35);
		}
		break;
		case "blade_06":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_STRAIGHT, 0.75, 1.25);
		}
		break;
		case "blade_13":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_CURVE, 0.65, 1.35);
		}
		break;
		case "blade_42":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_SHORT, WEAPON_CURVE, 0.65, 1.35);
		}
		break;
		case "topor_01":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_SHORT, WEAPON_CURVE, 0.75, 1.25);
		}
		break;
		case "topor_04":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_CURVE, 0.65, 1.35);
		}
		break;
		case "topor_06":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_SHORT, WEAPON_CURVE, 0.75, 1.25);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "lacrima_patris":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_STRAIGHT, 0.85, 1.15);
			AddDescriptor(item, "Special", -1);
		}
		break;
		case "blade_24":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_CURVE, 0.85, 1.15);
			AddDescriptor(item, "Exotic", -1);
		}
		break;
		case "blade_31":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_STRAIGHT, 0.65, 1.35);
		}
		break;
		case "topor_07":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_CURVE, 0.85, 1.15);
		}
		break;
		case "blade_21":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_STRAIGHT, 0.75, 1.25);
		}
		break;
		case "q_blade_10":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_STRAIGHT, 0.85, 1.15);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "q_blade_13":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_SHORT, WEAPON_CURVE, 0.65, 1.35);
		}
		break;
		case "q_blade_16":
		{
			SetWeaponDescriptors(item, WEAPON_LIGHT, WEAPON_SHORT, WEAPON_STRAIGHT, 0.65, 1.35);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "q_blade_21":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_STRAIGHT, 0.75, 1.25);
		}
		break;
		case "q_blade_19":
		{
			SetWeaponDescriptors(item, WEAPON_MEDIUM, WEAPON_LONG, WEAPON_STRAIGHT, 0.85, 1.15);
			AddDescriptor(item, "Fancy", -1);
		}
		break;
		case "blade_32":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_CURVE, 0.75, 1.25);
			AddDescriptor(item, "HighQuality", -1);
		}
		break;
		case "blade_07":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_STRAIGHT, 0.75, 1.25);
			AddDescriptor(item, "Unremarkable", -1);
		}
		break;
		case "blade_WR":
		{
			SetWeaponDescriptors(item, WEAPON_HEAVY, WEAPON_LONG, WEAPON_CURVE, 0.75, 1.25);
			AddDescriptor(item, "Special", -1);
		}
		break;
	}

	return true;
}