bool InitAmuletModifiers(ref item)
{
	if (item.groupID != ITEM_SLOT_TYPE && item.groupID != TALISMAN_ITEM_TYPE) return false;

	string realId = item.id;
	aref modifier;
	if (CheckAttribute(item, "DefItemID")) realId = item.DefItemID; // для ген-предметов принимаем id базовых

	switch (realId)
	{
		case "knife_01":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
		}
		break;
		case "totem_09":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, JOB_BOATSWAIN, -1);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "indian_3":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
			SetModifier(item, BLADE_ITEM_TYPE + "_" + M_CRIT_DAMAGE, 0.15);
		}
		break;
		case "indian_9":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_CANNONER, -1);
		}
		break;
		case "totem_03":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "obereg_4":
		{
			SetModifier(item, SKILL_TYPE + SKILL_SNEAK, 10);
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
		}
		break;
		case "totem_06":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "indian_7":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
			SetModifier(item, M_MTP_ENERGY_MAX, 0.12);
		}
		break;
		case "totem_13":
		{
			SetModifier(item, SPECIAL_TYPE + SPECIAL_L, 1);
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "totem_05":
		{
			SetModifier(item, M_REDUCE_CRIT_DAMAGE, 0.18);
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "indian_10":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
			SetModifier(item, M_POISON_CHANCE, 0.15);
		}
		break;
		case "totem_04":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "indian_6":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_BOATSWAIN, -1);
		}
		break;
		case "indian_1":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
			SetModifier(item, M_HEADSHOT_DAMAGE, 0.2);
		}
		break;
		case "totem_01":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "amulet_6":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "indian_11":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "totem_07":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "amulet_2":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_FIGHTER, -1);
			modifier = AddCallback(item, CT_EQUIP, "Euchologion"); // Молитвослов
			modifier.arg0 = 0.05;
		}
		break;
		case "amulet_3":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_FIGHTER, -1);
			modifier = AddCallback(item, CT_EQUIP, "Crucifix"); // Нательный крест
			modifier.arg0 = 0.15;
		}
		break;
		case "obereg_5":
		{
			SetModifier(item, SKILL_TYPE + SKILL_FORTUNE, 15);
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
		}
		break;
		case "obereg_3":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "obereg_6":
		{
			SetModifier(item, SKILL_TYPE + SKILL_LEADERSHIP, 10);
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
		}
		break;
		case "obereg_11":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_NAVIGATOR, -1);
		}
		break;
		case "totem_08":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "indian_2":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "talisman16":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			modifier = AddCallback(item, CT_EQUIP, "GoldenKnife");
			modifier.arg0 = 0.15;
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "obereg_7":
		{
			SetModifier(item, SKILL_TYPE + SKILL_SAILING, 10);
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, JOB_NAVIGATOR, -1);
		}
		break;
		case "amulet_7":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_FIGHTER, -1);
			modifier = AddCallback(item, CT_EQUIP, "HolyWater");
			modifier.arg0 = 0.15;
		}
		break;
		case "indian_4":
		{
			modifier = AddCallback(item, CT_EQUIP, "Battleaxe");
			modifier.arg0 = 0.15;
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "obereg_10":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, JOB_NAVIGATOR, -1);
		}
		break;
		case "amulet_5":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_CANNONER, -1);
		}
		break;
		case "totem_02":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, JOB_BOATSWAIN, -1);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "totem_12":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, "Alchemy", -1);
			AddDescriptor(item, JOB_FIGHTER, -1);
			modifier = AddCallback(item, CT_EQUIP, "JaguarSon");
			modifier.arg0 = 0.10;
		}
		break;
		case "totem_10":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
			AddDescriptor(item, JOB_FIGHTER, -1);
			modifier = AddCallback(item, CT_EQUIP, "TasmanianDevil");
			modifier.arg0 = 0.15;
		}
		break;
		case "obereg_1":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_CARPENTER, -1);
		}
		break;
		case "indian_5":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_BOATSWAIN, -1);
		}
		break;
		case "totem_11":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
		}
		break;
		case "obereg_8":
		{
			SetModifier(item, SKILL_TYPE + SKILL_COMMERCE, 10);
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_TREASURER, -1);
		}
		break;
		case "amulet_11":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_BOATSWAIN, -1);
		}
		break;
		case "amulet_10":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_DOCTOR, -1);
		}
		break;
		case "indian_8":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_CANNONER, -1);
		}
		break;
		case "obereg_2":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_CARPENTER, -1);
		}
		break;
		case "amulet_1":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
			modifier = AddCallback(item, CT_EQUIP, "NgomboShield");
			modifier.arg0 = 1;
			modifier.arg1 = 0.10;
		}
		break;
		case "amulet_4":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
			modifier = AddCallback(item, CT_EQUIP, "ElTrozo");
			modifier.arg0 = 0.025;
		}
		break;
		case "amulet_9":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_CARPENTER, -1);
		}
		break;
		case "obereg_9":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_NAVIGATOR, -1);
		}
		break;
		case "amulet_8":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, JOB_CARPENTER, -1);
		}
		break;
		case "rat_poison":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, JOB_TREASURER, -1);
		}
		break;
		case "clock2":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, JOB_NAVIGATOR, -1);
		}
		break;
		case "KhaelRoa_item":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			SetModifier(item, SHOT_STRIKE + "_" + M_DAMAGE, 10.0);
		}
		break;
		case "indian_poison":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
		}
		break;
		case "talisman2":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_NAVIGATOR, -1);
		}
		break;
		case "talisman1":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_TREASURER, -1);
		}
		break;
		case "talisman6":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_TREASURER, -1);
		}
		break;
		case "talisman14":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			SetModifier(item, SKILL_TYPE + SKILL_SAILING, 15);
			AddDescriptor(item, JOB_NAVIGATOR, -1);
		}
		break;
		case "talisman11":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			SetModifier(item, SKILL_TYPE + SKILL_LEADERSHIP, 2);
			SetModifier(item, SKILL_TYPE + SKILL_F_LIGHT, 2);
			SetModifier(item, SKILL_TYPE + SKILL_FENCING, 2);
			SetModifier(item, SKILL_TYPE + SKILL_F_HEAVY, 2);
			SetModifier(item, SKILL_TYPE + SKILL_PISTOL, 2);
			SetModifier(item, SKILL_TYPE + SKILL_SNEAK, 2);
			SetModifier(item, SKILL_TYPE + SKILL_FORTUNE, 2);
			SetModifier(item, SKILL_TYPE + SKILL_SAILING, 2);
			SetModifier(item, SKILL_TYPE + SKILL_ACCURACY, 2);
			SetModifier(item, SKILL_TYPE + SKILL_CANNONS, 2);
			SetModifier(item, SKILL_TYPE + SKILL_GRAPPLING, 2);
			SetModifier(item, SKILL_TYPE + SKILL_DEFENCE, 2);
			SetModifier(item, SKILL_TYPE + SKILL_REPAIR, 2);
			SetModifier(item, SKILL_TYPE + SKILL_COMMERCE, 2);
		}
		break;
		case "talisman3":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_CANNONER, -1);
		}
		break;
		case "talisman7":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_CARPENTER, -1);
		}
		break;
		case "talisman8":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			SetModifierFromSource(item, HAS + M_CANT_BE_POISONED, true, TALISMAN_ITEM_TYPE);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "talisman13":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "talisman15":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			SetModifierFromSource(item, M_SQUADRON_POWER, 0.15, TALISMAN_ITEM_TYPE);
		}
		break;
		case "talisman4":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_BOATSWAIN, -1);
		}
		break;
		case "talisman10":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
		}
		break;
		case "talisman12":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "talisman9":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			SetModifier(item, SPECIAL_TYPE + SPECIAL_C, 1);
		}
		break;
		case "talisman18":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_BOATSWAIN, -1);
		}
		break;
		case "talisman19":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
		}
		break;
		case "talisman17":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_DOCTOR, -1);
			SetModifier(item, M_REDUCE_DAMAGE, 0.05);
			modifier = AddCallback(item, CT_EQUIP, "LiberMisericordiae");
		}
		break;
		case "talisman20":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
			AddDescriptor(item, "Alchemy", -1);
			AddDescriptor(item, "Fragile", -1);
			SetModifier(item, M_HEADSHOT_DAMAGE, 0.2);
			SetModifier(item, GUN_ITEM_TYPE + "_" + M_RELOAD_SPEED, 0.2);
			SetModifier(item, MUSKET_ITEM_TYPE + "_" + M_RELOAD_SPEED, 0.2);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "talisman21":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_COMMON);
		}
		break;
		case "knife_01":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
		}
		break;
		case "knife_03":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			SetModifier(item, BLADE_ITEM_TYPE   + "_" + M_CRIT_CHANCE, 0.03);
			SetModifier(item, GUN_ITEM_TYPE     + "_" + M_CRIT_CHANCE, 0.03);
			SetModifier(item, MUSKET_ITEM_TYPE  + "_" + M_CRIT_CHANCE, 0.03);
			SetModifier(item, BLADE_ITEM_TYPE  + "_" + M_CRIT_DAMAGE, 0.10);
			SetModifier(item, GUN_ITEM_TYPE    + "_" + M_CRIT_DAMAGE, 0.10);
			SetModifier(item, MUSKET_ITEM_TYPE + "_" + M_CRIT_DAMAGE, 0.10);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "knife_02":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_CHURCH);
			AddDescriptor(item, JOB_FIGHTER, -1);
		}
		break;
		case "kaleuche_amulet2":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			modifier = AddCallback(item, CT_COMMON, "KaleucheAmuletAttack");
			modifier.arg0 = 0.25;
		}
		break;
		case "kaleuche_amulet3":
		{
			AddDescriptor(item, M_AMULET_TYPE, AMULET_PAGAN);
			SetModifierFromSource(item, HAS + M_CANT_BE_POISONED, true, TALISMAN_ITEM_TYPE);
			SetModifier(item, M_REDUCE_DAMAGE, 0.25);
		}
		break;
	}

	return true;
}
