
//JOKERTODO: выделение столбцов, скрытие незаполненных
void SetItemStatsTooltip(string sCurrentNode, string header, string text, string badText, string goodText)
{
	if (sCurrentNode != "TABLE_ITEM_STATS") return;
	CloseTooltipNew();
	int iColumn = GetSelectedColumn("TABLE_ITEM_STATS");
	aref itemStats, stat;
	object itemInfo;
	string statName;
	makearef(itemStats, itemInfo.stats);
	SetUIAttributesItem(currentItem, &itemStats);
	if (GetAttributesNum(itemStats) < iColumn + 1) return;

	stat = GetAttributeN(itemStats, iColumn);
	statName = GetAttributeName(stat);
	if (statName == "mainEffect") statName = currentItem.id;
	else if (statName == "secondaryEffect") statName = "secondary_" + currentItem.id;
	header = GetConvertStrB("itm_stat_" + statName, "ItemsStats.txt");
	text = 
		GetAssembledString(GetConvertStrB("itm_stat_descr_" + statName, "ItemsStats.txt"), currentItem);
	badText = "";
	goodText = "";
}

void SetUIAttributesItem(ref ref_Id_Idx, ref result)
{
	ref item = FindItem_VT(&ref_Id_Idx);

	result.weight.iconGroup = "EQUIP_ICONS";
	result.weight.iconName = "weight";
	result.weight.value = FloatToString(stf(item.weight), 1) + " " + xiStr("pounds.");
	if (HasDescriptor(item, "healPotion" )) SetUIAttributesHealPotion(item, result);
	if (!CheckAttribute(item, "groupID")) return;
	string func = "SetUIAttributes" + item.groupId;
	call func(item, result);
	if (HasDescriptor(item, "Special") || HasDescriptor(item, "EnhancingPotion")) SetUIAttributesEffects(item, result, false);
}

void SetUIAttributesEffects(ref item, ref result, bool withSecondary)
{
	result.mainEffect.iconGroup = "EQUIP_ICONS";
	result.mainEffect.iconName = "mainEffect";
	result.mainEffect.value = GetConvertStrB("itm_stat_mainEffect", "ItemsStats.txt");

	if (!withSecondary) return;
	result.secondaryEffect.iconGroup = "EQUIP_ICONS";
	result.secondaryEffect.iconName = "secondaryEffect";
	result.secondaryEffect.value = GetConvertStrB("itm_stat_secondaryEffect", "ItemsStats.txt");
}

void SetUIAttributesTool(ref item, ref result)
{
//
}

void SetUIAttributeslantern(ref item, ref result)
{
//
}

void SetUIAttributesMaps(ref item, ref result)
{
//
}

void SetUIAttributesSpecial(ref item, ref result)
{
//
}

void SetUIAttributesPatent(ref item, ref result)
{
//
}

// JOKERTODO бонусы
void SetUIAttributesSpyGlass(ref item, ref result)
{
	result.radius.iconGroup = "EQUIP_ICONS";
	result.radius.iconName = "radius";
	result.radius.value = ToHumanNumber(item.radius) + " " + xiStr("yard.");

	// result.worldMapBonus.iconGroup = "EQUIP_ICONS";
	// result.worldMapBonus.iconName = "mapBonus";
	// result.worldMapBonus.value = ToHumanNumber(item.worldMapBonus) + " %";
}


void SetUIAttributesHealPotion(ref item, ref result)
{
	result.healAmount.iconGroup = "EQUIP_ICONS";
	result.healAmount.iconName = "Life";
	result.healAmount.value = ToHumanNumber(item.potion.health) + " " + xiStr("ye.");
}

void SetUIAttributesHat(ref item, ref result)
{
	SetUIAttributesEffects(item, result, true);
}

void SetUIAttributesBlade(ref item, ref result)
{
	result.attack.iconGroup = "EQUIP_ICONS";
	result.attack.iconName = "damage";
	if (!CheckAttribute(item, "attack.min")) trace("missing attack for: " + item.id);
	result.attack.value = ToHumanNumber(item.Attack.min) + " - " + ToHumanNumber(item.Attack.max) + " " + xiStr("ye.");
}

void SetUIAttributesMusket(ref item, ref result)
{
	result.attack.iconGroup = "EQUIP_ICONS";
	result.attack.iconName = "damage";
	result.attack.value = ToHumanNumber(item.Attack) + " " + xiStr("ye.");

	result.gunDamage.iconGroup = "EQUIP_ICONS";
	result.gunDamage.iconName = "gunDamage";
	if (IsBulletGrape(item.type.t1.bullet)) result.gunDamage.value = sti(item.type.t1.dmgmin) + "-" + sti(item.type.t1.dmgmax) + " " + xiStr("ye.");
	else result.gunDamage.value = sti(item.dmg_min) + "-" + sti(item.dmg_max) + " " + xiStr("ye.");

	SetUIAttributesGun(item, result);
}

void SetUIAttributesCirass(ref item, ref result)
{
	result.damageReduction.iconGroup = "EQUIP_ICONS";
	result.damageReduction.iconName = "defence";
	result.damageReduction.value = ToHumanPercent(GetAttributeFloat(item, "modifiers." + M_REDUCE_DAMAGE));
}

void SetUIAttributesSlot(ref item, ref result)
{
	result.duration.iconGroup = "EQUIP_ICONS";
	result.duration.iconName = "time";
	result.duration.value = item.time + " " + xiStr("days");
	SetUIAttributesEffects(item, result, false);
}

void SetUIAttributesTalisman(ref item, ref result)
{
	SetUIAttributesEffects(item, result, false);
}

void SetUIAttributesAmmo(ref item, ref result)
{
// JOKERTODO Усиление урона?
}

void SetUIAttributesGun(ref item, ref result)
{
	result.gunDamage.iconGroup = "EQUIP_ICONS";
	result.gunDamage.iconName = "gunDamage";

	if (IsBulletGrape(item.type.t1.bullet)) result.gunDamage.value = sti(item.type.t1.dmgmin) + "-" + sti(item.type.t1.dmgmax) + " " + xiStr("ye.");
	else result.gunDamage.value = sti(item.dmg_min) + "-" + sti(item.dmg_max) + " " + xiStr("ye.");

	result.reloadTime.iconGroup = "EQUIP_ICONS";
	result.reloadTime.iconName = "reloadTime";
	result.reloadTime.type = "float"
	result.reloadTime.value = ToHumanNumber(item.chargespeed) + " " + xiStr("sec.");
}

void FillUpStats(ref item)
{
	aref statTable;
	makearef(statTable, GameInterface.TABLE_ITEM_STATS);
	Table_Clear("TABLE_ITEM_STATS", false, true, false);

	object itemInfo;
	aref itemStats;
	makearef(itemStats, itemInfo.stats);
	SetUIAttributesItem(item, &itemStats);

	for (int y = 0; y < GetAttributesNum(itemStats); y++)
	{
		string sCol = "td" + (y+1);
		aref itemStat = GetAttributeN(itemStats, y);
		string statName = GetAttributeName(itemStat);
		statTable.tr1.(sCol).icon.group  = itemStats.(statName).iconGroup;
		statTable.tr1.(sCol).icon.width = 32;
		statTable.tr1.(sCol).icon.height = 32;
		statTable.tr1.(sCol).icon.image  = itemStats.(statName).iconName;
		statTable.tr1.(sCol).icon.offset = "32, 0";
		statTable.tr2.(sCol).str = itemStats.(statName).value;
		statTable.tr2.(sCol).align = "center";
		statTable.tr2.(sCol).textoffset = "6, 0";
	}

	Table_UpdateWindow("TABLE_ITEM_STATS");
}
