// Стандартное свойство предмета, для любого предмета работает и выглядит одинаково
void AddDescriptor(ref rObject, string descriptorId, int variant)
{
	bool universalDescriptor = false; // может ли дескриптор быть у разного типа предметов
	aref modifier;
	switch (descriptorId)
	{
		case M_AMULET_TYPE: universalDescriptor = true; break;
		case "SingleCharge": universalDescriptor = true; break;
		case "Fragile": universalDescriptor = true; break;
		case "MultiCharge": universalDescriptor = true; break;
		case M_ARMOR_TYPE:
		{
			AddModifier(rObject, SET + M_ARMOR_TYPE, variant);
			switch (variant)
			{
				case ARMOR_MEDIUM: AddModifier(rObject, M_MOVE_SPEED, ARMOR_MEDIUM_MOVE_SPEED_MTP); break;
				case ARMOR_HEAVY:  AddModifier(rObject, M_MOVE_SPEED, ARMOR_HEAVY_MOVE_SPEED_MTP); break;
			}
		}
		break;
		case M_ARMOR_MATERIAL:
		{
			AddModifier(rObject, SET + M_ARMOR_MATERIAL, variant);
			switch (variant)
			{
				case ARMOR_FABRIC:  AddModifier(rObject, M_REDUCE_DAMAGE, ARMOR_FABRIC_DAMAGE_REDUCTION); break;
				case ARMOR_LEATHER: AddModifier(rObject, M_REDUCE_DAMAGE, ARMOR_LEATHER_DAMAGE_REDUCTION); break;
				case ARMOR_PLATES:  AddModifier(rObject, M_REDUCE_DAMAGE, ARMOR_PLATES_DAMAGE_REDUCTION); break;
				case ARMOR_STAMPS:  AddModifier(rObject, M_REDUCE_DAMAGE, ARMOR_STAMPS_DAMAGE_REDUCTION); break;
				case ARMOR_MOLDED:  AddModifier(rObject, M_REDUCE_DAMAGE, ARMOR_MOLDED_DAMAGE_REDUCTION); break;
			}
		}
		break;
		case "TwoHanded":
		{
			SetWeaponDamageByStrikes(rObject, MUSKET_ITEM_TYPE, 0.7, 1.3);
		}
		break;
		case M_WEAPON_TYPE:
		{
			AddModifier(rObject, SET + M_WEAPON_TYPE, variant);
			switch (variant)
			{
				case WEAPON_MEDIUM: AddModifier(rObject, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED, WEAPON_MEDIUM_ATTACK_SPEED_MTP); break;
				case WEAPON_HEAVY:  AddModifier(rObject, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED, WEAPON_HEAVY_ATTACK_SPEED_MTP); break;
			}
		}
		break;
		case M_WEAPON_LENGTH:
		{
			AddModifier(rObject, SET + M_WEAPON_LENGTH, variant);
		}
		break;
		case M_WEAPON_CURVATURE:
		{
			AddModifier(rObject, SET + M_WEAPON_CURVATURE, variant);
		}
		break;
		case "Exotic":
		{
			AddModifier(rObject, M_SQUADRON_POWER, DescriptorBaseValue("Exotic"));
			universalDescriptor = true;
		}
		break;
		case "HighQuality":
		{
			AddModifier(rObject, rObject.groupId + M_CRIT_DAMAGE, DescriptorBaseValue("HighQuality")); // пистолет, клинки и мушкеты имеют отдельные модификаторы
			universalDescriptor = true;
		}
		break;
		case "Fancy":
		{
			AddModifier(rObject, SKILL_TYPE + SKILL_LEADERSHIP, DescriptorBaseValue("Fancy"));
			universalDescriptor = true;
		}
		break;
		case "GoodFit":
		{
			AddModifier(rObject, BLADE_ITEM_TYPE + "_" + M_ACTION_SPEED, DescriptorBaseValue("GoodFit"));
		}
		break;
		case "HeartDefence":
		{
			AddModifier(rObject, M_REDUCE_CRIT_DAMAGE, DescriptorBaseValue("HeartDefence"));
		}
		break;
		case "Unremarkable":
		{
			AddModifier(rObject, SKILL_TYPE + SKILL_SNEAK, DescriptorBaseValue("Unremarkable"));
			universalDescriptor = true;
		}
		break;
		case "Bayonet":
		{
			AddToAttributeFloat(rObject, M_DAMAGE + FAST_STRIKE + MUSKET_ITEM_TYPE, DescriptorBaseValue("Bayonet"));
		}
		break;
	}

	if (variant >= 0) descriptorId += ("_" + variant);
	rObject.descriptors.(descriptorId);
	if (universalDescriptor) rObject.descriptors.(descriptorId).universal = true;
}

// Особое свойство предмета, внешний вид всех особых дескрипторов в интерфейсе одинаковый, но эффекты разные
void AddSpecialDescriptor(ref item, string descriptorId)
{
	item.descriptors.special = descriptorId;
	item.descriptors.special.universal = true;

	switch (descriptorId)
	{
		case "MonsterGun":
		{
			AddModifier(item, SKILL_TYPE + SKILL_F_HEAVY, DescriptorBaseValue("MonsterGun"));
		}
		break;
		case "Jian":
		{
			AddCallback(item, CT_EQUIP, "Jian");
		}
		break;
		case "IronsideArmor":
		{
			AddModifier(item, GUN_ITEM_TYPE + "_" + M_RELOAD_SPEED, DescriptorBaseValue("IronsideArmor"));
			AddModifier(item, MUSKET_ITEM_TYPE + "_" + M_RELOAD_SPEED, DescriptorBaseValue("IronsideArmor"));
		}
		break;
		case "LamportSuit":
		{
			AddModifier(item, M_SQUADRON_POWER, DescriptorBaseValue("LamportSuit"));
		}
		break;
	}
}

bool HasDescriptor(ref rObject, string descriptor)
{
	return CheckAttribute(rObject, "descriptors." + descriptor);
}

int CountItemsWithDescriptor(ref chr, string descriptor)
{
	return GetAttributeInt(chr, "ct.equip.descriptors." + descriptor);
}

aref GetEquipDescriptors(ref chr)
{
	aref result;
	makearef(result, chr.ct.equip.descriptors);
	return result;
}