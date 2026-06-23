void InitMultiObjectCommon(
	ref    ref_id_idx,
	string sAttr,
	string component_id,
	string component_use,
	int    component_qty)
{
	ref rItem = FindItem_VT(ref_id_idx);
	rItem.component.(sAttr).id 	= component_id;
	rItem.component.(sAttr).use = component_use;
	rItem.component.(sAttr).qty = component_qty;
}

ref InitStdMusketCommon(
	string id,
	string ModelID,
	string picTexture,
	int picIndex,
	float Rare,
	int MinLevel,
	int Price,
	float DmgMin,
	float DmgMax,
	float Weight,
	int Charges,
	int Quality,
	float Attack )
{
	object Mus;
	Mus.id				= id;		
	Mus.groupID			= MUSKET_ITEM_TYPE;
	Mus.name			= "itmname_" + id;
	Mus.describe		= "itmdescr_" + id;		
	Mus.model			= ModelID;
	Mus.folder 			= "ammo";
	Mus.chargeQ			= Charges;
	Mus.picTexture		= picTexture;
	Mus.picIndex		= picIndex;
	Mus.dmg_min			= DmgMin;
	Mus.dmg_max			= DmgMax;
	Mus.price			= Price;	
	Mus.ItemType 		= "WEAPON";
	Mus.rare 			= Rare;
	Mus.quality 		= Quality;
	Mus.minlevel 		= MinLevel;
	Mus.Weight 			= Weight;
	Mus.ChargeSpeed 	= 10.0; // by default
	Mus.TradeType 		= ITEM_TRADE_AMMUNITION;
	Mus.attack = Attack;
	return InitNewItem(&Mus);
}

void InitGunWithAmmoParams(
	ref ref_id_idx,
	string sAttr,
	string sBullet,
	string sGunPowder,
	float  DmgMin,
	float  DmgMax,
	float  EnergyP,
	bool   MultiDamage,
	int    MisFire,
	int    ChargeSpeed,
	bool   isDefault )
{
	ref gun = FindItem_VT(ref_id_idx);
	gun.type.(sAttr).bullet 		= sBullet;
	gun.type.(sAttr).gunpowder 		= sGunPowder;
	gun.type.(sAttr).DmgMin			= DmgMin;
	gun.type.(sAttr).DmgMax			= DmgMax;
	gun.type.(sAttr).EnergyP		= EnergyP;
	gun.type.(sAttr).multidmg       = MultiDamage;
	gun.type.(sAttr).misfire        = MisFire;
	gun.type.(sAttr).ChargeSpeed    = ChargeSpeed;
	gun.type.(sAttr).Default        = isDefault;
}

ref InitNewItem(ref newItem)
{
	int i;
	ref itm;
	object tempItems[TOTAL_ITEMS];

	for(i = 0; i < TOTAL_ITEMS; i++)
	{
		CopyAttributes(&tempItems[i], &Items[i]);
		// trace("Index " + i + " ID temp " + tempItems[i].id + " ID real " + Items[i].id);
	}
	
	ExpandItemsArray();
	
	ITEMS_QUANTITY++;
	
	DeleteAttribute(&Items[ITEMS_QUANTITY - 1], "");
	InitAddItem(ITEMS_QUANTITY - 1);
	
	makeref(itm,Items[ITEMS_QUANTITY - 1]);
	CopyAttributes(&itm, newItem);
	itm.index = ITEMS_QUANTITY - 1;
	
	for(i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		DeleteAttribute(&Items[i], "");
		CopyAttributes(&Items[i], &tempItems[i - 1]);
		Items[i].index = i;
	}
	
	// belamour просто финальное логирование (пока оставить)
	// for(i = 0; i < TOTAL_ITEMS; i++)
	// {
	// 	trace("New object full loop" + i + " ID real " + Items[i].id);
	// }
	return itm;
}


void ReinitBladeDamage(ref blade)
{
	bool wasGenerated = CheckAttribute(blade, "DefItemID");
	if (wasGenerated)
	{
		ref originalBlade = ItemsFromID(blade.DefItemID);
		blade.attack = GetGeneratableDamageFromOriginalBlade(originalBlade);
		return;
	}

	switch (blade.id)
	{
		case "blade_40": blade.attack = 22; break;
		case "slave_01": blade.attack = 25; break;
		case "blade_03": blade.attack = 29; break;
		case "blade_09": blade.attack = 31; break;
		case "blade_01": blade.attack = 33; break;
		case "blade_08": blade.attack = 30; break;
		case "blade_22": blade.attack = 36; break;
		case "blade_16": blade.attack = 39; break;
		case "blade_39": blade.attack = 41; break;
		case "blade_15": blade.attack = 40; break;
		case "q_blade_16": blade.attack = 46; break;
		case "blade_27": blade.attack = 42; break;
		case "blade_17": blade.attack = 47; break;
		case "blade_18": blade.attack = 49; break;
		case "blade_26": blade.attack = 50; break;
		case "blade_38": blade.attack = 52; break;
		case "q_blade_18": blade.attack = 55; break;
		case "blade_25": blade.attack = 55; break;
		case "slave_02": blade.attack = 30; break;
		case "blade_11": blade.attack = 35; break;
		case "blade_05": blade.attack = 37; break;
		case "blade_12": blade.attack = 36; break;
		case "blade_02": blade.attack = 38; break;
		case "khopesh1": blade.attack = 39; break;
		case "blade_10": blade.attack = 44; break;
		case "q_blade_10": blade.attack = 54; break;
		case "shamshir": blade.attack = 48; break;
		case "blade_04": blade.attack = 46; break;
		case "blade_23": blade.attack = 50; break;
		case "blade_30": blade.attack = 47; break;
		case "saber": blade.attack = 50; break;
		case "blade_19": blade.attack = 52; break;
		case "q_blade_19": blade.attack = 62; break;
		case "blade_20": blade.attack = 53; break;
		case "blade_28": blade.attack = 55; break;
		case "blade_29": blade.attack = 54; break;
		case "machete2": blade.attack = 60; break;
		case "khopesh3": blade.attack = 65; break;
		case "blade_SP_3low": blade.attack = 70; break;
		case "blade_SP_3": blade.attack = 70; break;
		case "pirate_cutlass": blade.attack = 75; break;
		case "blade_41": blade.attack = 75; break;
		case "topor_05": blade.attack = 40; break;
		case "topor_02": blade.attack = 44; break;
		case "blade_07": blade.attack = 45; break;
		case "blade_14": blade.attack = 43; break;
		case "topor_03": blade.attack = 47; break;
		case "blade_42": blade.attack = 46; break;
		case "topor_01": blade.attack = 51; break;
		case "blade_06": blade.attack = 49; break;
		case "blade_13": blade.attack = 53; break;
		case "topor_04": blade.attack = 55; break;
		case "topor_06": blade.attack = 85; break;
		case "q_blade_13": blade.attack = 85; break;
		case "lacrima_patris": blade.attack = 90; break;
		case "blade_21": blade.attack = 92; break;
		case "blade_24": blade.attack = 99; break;
		case "blade_31": blade.attack = 100; break;
		case "blade_32": blade.attack = 100; break;
		case "topor_07": blade.attack = 100; break;
		case "blade_36": blade.attack = 100; break;
		case "q_blade_21": blade.attack = 100; break;
		case "blade_WR": blade.attack = 100; break;
		case "blade_34": blade.attack = 48; break;
	}
}

// Разброс урона генерируемого клинка от клинка-оригинала
float GetGeneratableDamageFromOriginalBlade(ref blade)
{
	return float(blade.attack) * (0.94 + fRandSmall(0.14));
}