#include "interface\utils\modifiers.c"

//JOKERTODO: выделение столбцов, скрытие незаполненных
void SetItemStatsTooltip(ref chr, string sCurrentNode, string header, string text, string badText, string goodText)
{
	if (sCurrentNode != "TABLE_ITEM_STATS") return;
	CloseTooltipNew();
	int iColumn = GetSelectedColumn("TABLE_ITEM_STATS");
	aref itemStats, stat;
	object itemInfo;
	string statName;
	makearef(itemStats, itemInfo.stats);
	SetUIAttributesItem(currentItem, &itemStats, &NullCharacter);
	if (GetAttributesNum(itemStats) < iColumn + 1) return;

	stat = GetAttributeN(itemStats, iColumn);
	statName = GetAttributeName(stat);
	if (statName == "mainEffect") statName = currentItem.id;
	else if (statName == "secondaryEffect") statName = "secondary_" + currentItem.id;
	header = GetConvertStrB("itm_stat_" + statName, "ItemsStats.txt");
	text = DLG_Convert("itm_stat_descr_" + statName, "ItemsStats.txt", currentItem);
	badText = "";
	goodText = "";
	AddItemUICharacterModifiers(chr, &goodText, stat, currentItem);
}

void SetUIAttributesItem(ref ref_Id_Idx, ref result, ref chr)
{
	ref item = FindItem_VT(&ref_Id_Idx);

	result.weight.iconGroup = "EQUIP_ICONS";
	result.weight.iconName = "weight";
	result.weight.value = FloatToString(stf(item.weight), 1) + " " + xiStr("pounds.");
	if (HasDescriptor(item, "healPotion" )) SetUIAttributesHealPotion(item, result, chr);
	if (!CheckAttribute(item, "groupID")) return;
	
	float damageReduction = GetAttributeFloat(item, "modifiers." + M_REDUCE_DAMAGE);
	if (damageReduction > 0)
	{
		result.damageReduction.iconGroup = "EQUIP_ICONS";
		result.damageReduction.iconName = "defence";
		result.damageReduction.value = ToHumanPercent(damageReduction);
	}
	
	string func = "SetUIAttributes" + item.groupId;
	call func(item, result, chr);
	SetUIAttributesEffects(item, result, false);
	if (CheckAttribute(item, "time"))
	{
		result.duration.iconGroup = "EQUIP_ICONS";
		result.duration.iconName = "time";
		result.duration.value = item.time + " " + xiStr("days");
	}
}

void SetUIAttributesEffects(ref item, ref result, bool withSecondary)
{
	bool showMain = GetConvertStr("itm_stat_" + item.id, "ItemsStats.txt") != "";
	if (!showMain) return;
	
	result.mainEffect.iconGroup = "EQUIP_ICONS";
	result.mainEffect.iconName = "mainEffect";
	result.mainEffect.value = GetConvertStrB("itm_stat_mainEffect", "ItemsStats.txt");
	
	bool showSecondary = GetConvertStr("itm_stat_secondary_" + item.id, "ItemsStats.txt") != "";
	if (!showSecondary) return;
	result.secondaryEffect.iconGroup = "EQUIP_ICONS";
	result.secondaryEffect.iconName = "secondaryEffect";
	result.secondaryEffect.value = GetConvertStrB("itm_stat_secondaryEffect", "ItemsStats.txt");
}

void SetUIAttributesTool(ref item, ref result, ref chr)
{
//
}

void SetUIAttributeslantern(ref item, ref result, ref chr)
{
//
}

void SetUIAttributesMaps(ref item, ref result, ref chr)
{
//
}

void SetUIAttributesSpecial(ref item, ref result, ref chr)
{
//
}

void SetUIAttributesPatent(ref item, ref result, ref chr)
{
//
}

void SetUIAttributesSpyGlass(ref item, ref result, ref chr)
{
	result.radius.iconGroup = "EQUIP_ICONS";
	result.radius.iconName = "radius";
	result.radius.value = ToHumanNumber(item.radius) + " " + xiStr("yard.");

	if (GetAttributeInt(item, "worldMapBonus") < 1) return;
	result.worldMapBonus.iconGroup = "EQUIP_ICONS";
	result.worldMapBonus.iconName = "mapBonus";
	result.worldMapBonus.value = ToHumanNumber(item.worldMapBonus) + " %";
}


void SetUIAttributesHealPotion(ref item, ref result, ref chr)
{
	result.healAmount.iconGroup = "EQUIP_ICONS";
	result.healAmount.iconName = "Life";
	result.healAmount.value = ToHumanNumber(item.potion.health) + " " + xiStr("ye.");
}

void SetUIAttributesHat(ref item, ref result, ref chr)
{
	SetUIAttributesEffects(item, result, true);
}

void SetUIAttributesBlade(ref item, ref result, ref chr)
{
	result.attack.iconGroup = "EQUIP_ICONS";
	result.attack.iconName = "damage";
	if (!CheckAttribute(item, "attack.min")) trace("missing attack for: " + item.id);
	int min, max;
	WeaponSetVisualDamages(item, &min, &max);
	result.attack.value = ToHumanNumber(min) + " - " + ToHumanNumber(max) + " " + xiStr("ye.");
}

void SetUIAttributesMusket(ref item, ref result, ref chr)
{
	result.attack.iconGroup = "EQUIP_ICONS";
	result.attack.iconName = "damage";
	result.attack.value = ToHumanNumber(item.Attack) + " " + xiStr("ye.");

	SetUIAttributesGun(item, result, chr);
}

void SetUIAttributesCirass(ref item, ref result, ref chr)
{
//
}

void SetUIAttributesSlot(ref item, ref result, ref chr)
{
	SetUIAttributesEffects(item, result, false);
}

void SetUIAttributesTalisman(ref item, ref result, ref chr)
{
	SetUIAttributesEffects(item, result, false);
}

void SetUIAttributesAmmo(ref item, ref result, ref chr)
{
// JOKERTODO Усиление урона?
}

void SetUIAttributesGun(ref item, ref result, ref chr)
{
	result.gunDamage.iconGroup = "EQUIP_ICONS";
	result.gunDamage.iconName = "gunDamage";

	// костыль для пушек без патрона
	if (GetAttributeInt(item, "chargespeed") == 10) 
	{
		FixEmptyGunStats(item, result);
		return;
	}

	result.gunDamage.iconGroup = "EQUIP_ICONS";
	result.gunDamage.iconName = "gunDamage";
	int dmgMax, dmgMin;

	// оружия в руках персонажа, подставляем выбранный заряд
	if (GetCharacterEquipByGroup(chr, item.groupId) == item.id)
	{
		string ammoType = LAi_GetCharacterBulletType(chr, item.groupId)
		if (IsBulletGrape(ammoType))
		{
			dmgMin = GetAttributeInt(chr, "chr_ai." + item.groupId + ".shards");
			dmgMax = GetAttributeInt(chr, "chr_ai." + item.groupId + ".basedmg");
			result.gunDamage.value = dmgMin + " x " + DmgMax + " " + xiStr("ye.");
		}
		else
		{
			dmgMin = GetAttributeInt(chr, "chr_ai." + item.groupId + ".dmgmin");
			dmgMax = GetAttributeInt(chr, "chr_ai." + item.groupId + ".dmgmax");
			result.gunDamage.value = dmgMin + "-" + DmgMax + " " + xiStr("ye.");
		}
	}
	else if (IsBulletGrape(item.type.t1.bullet)) // иначе дефолт
	{
		dmgMin = sti(item.type.t1.dmgmin);
		dmgMax = sti(item.type.t1.dmgmax);
		result.gunDamage.value = dmgMin + "-" + DmgMax + " " + xiStr("ye.");
	}
	else
	{
		dmgMin = sti(item.dmg_min);
		dmgMax = sti(item.dmg_max);
		result.gunDamage.value = dmgMin + "-" + DmgMax + " " + xiStr("ye.");
	}

	result.reloadTime.iconGroup = "EQUIP_ICONS";
	result.reloadTime.iconName = "reloadTime";
	result.reloadTime.rawValue = item.chargespeed;
	result.reloadTime.value = ToHumanNumber(result.reloadTime.rawValue) + " " + xiStr("sec.");
}

void FillUpStats(ref item, ref chr)
{
	aref statTable;
	makearef(statTable, GameInterface.TABLE_ITEM_STATS);
	Table_Clear("TABLE_ITEM_STATS", false, true, false);

	object itemInfo;
	aref itemStats;
	makearef(itemStats, itemInfo.stats);
	SetUIAttributesItem(item, &itemStats, chr);
	int statsQty = GetAttributesNum(&itemStats);

	for (int y = 0; y < statsQty; y++)
	{
		string sCol = "td" + (y+1);
		aref itemStat = GetAttributeN(itemStats, y);
		string statName = GetAttributeName(itemStat);
		statTable.tr1.(sCol).icon.group  = itemStats.(statName).iconGroup;
		statTable.tr1.(sCol).icon.width = 32;
		statTable.tr1.(sCol).icon.height = 32;
		statTable.tr1.(sCol).icon.image  = itemStats.(statName).iconName;
		statTable.tr1.(sCol).icon.image  = itemStats.(statName).iconName;
		statTable.tr1.(sCol).icon.offset = "34, 0";
		statTable.tr1.(sCol).str = itemStats.(statName).value;
		statTable.tr1.(sCol).align = "center";
		statTable.tr1.(sCol).textoffset = "6, 18";
	}

	Table_UpdateWindow("TABLE_ITEM_STATS");
	// CropTableColsFrameByElementsQty("TABLE_ITEM_STATS", statsQty, 100);
}

//JOKERTODO ещё попыхтеть над скрытием общего фрейма и мб сделать универсально
void CropTableColsFrameByElementsQty(string tableName, int count, int width)
{
	int x1, x2, y1, y2;
	GetTriggerFramePosition(tableName, &x1, &y1, &x2, &y2);

	int target = GetAttributeInt(&GameInterface, "CropTableShift." + tableName);
	if (target == 0) 
	{
		SetAttribute(&GameInterface, "CropTableShift." + tableName, x1);
		target = x1;
	}

	int result = makeint(target + (width * count));
	SetTriggerFramePosition(tableName, x1, y1, result, y2);
}

void FixEmptyGunStats(ref item, ref result)
{
	// костыль для пушек без патрона
	string defaultType = LAi_GetCharacterDefaultBulletType(item.id);
	aref types, type;
	makearef(types, item.type);
	for (int i = 0; i < GetAttributesNum(types); i++)
	{
		type = GetAttributeN(types, i);
		string typeName = GetAttributeName(type);
		if (item.type.(typeName).bullet != defaultType) continue;

		result.reloadTime.iconGroup = "EQUIP_ICONS";
		result.reloadTime.iconName = "reloadTime";
		result.reloadTime.type = "float"
		result.reloadTime.rawValue = item.type.(typeName).chargespeed;
		result.reloadTime.value = ToHumanNumber(result.reloadTime.rawValue) + " " + xiStr("sec.");
		result.gunDamage.value = sti(item.type.(typeName).dmgmin) + "-" + sti(item.type.(typeName).dmgmax) + " " + xiStr("ye.");
	}
}