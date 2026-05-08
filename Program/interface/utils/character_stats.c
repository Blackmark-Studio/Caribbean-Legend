// Здесь разруливаем всплывашки по характеристикам персонажа и предметов в разрезе персонажа

void SetCharacterStatsTooltip(ref chr, string statName, ref header, ref text, ref badText, ref goodText)
{
	float base;
	aref equipTable = CT_GetTable(chr, CT_EQUIP);
	object tempTable;
	CopyAttributes(&tempTable, equipTable);

	switch (statName)
	{
		case "life":
			text += newStr() + " " + newStr() + " ";
			base = GetCharacterBaseHPValue(chr);
			text += GetConvertStr("SourceBase", "RPGDescribe.txt") + ": " + sti(base);
			_AddByRankModifierAsFlatValue(chr, &tempTable, M_HP_PER_RANK, M_HP_MAX);
			SetCharacterStat(chr, &tempTable, M_HP_MAX, &goodText, "ToHumanModifier", 0);
			SetCharacterStat(chr, &tempTable, M_MTP_HP_MAX, &goodText, "ToHumanModifierPercent", 0);
		break;
		case "energy":
			text += newStr() + " " + newStr() + " ";
			base = GetCharacterBaseEnergy(chr);
			_AddByRankModifierAsFlatValue(chr, &tempTable, M_ENERGY_PER_RANK, M_ENERGY_MAX);
			text += GetConvertStr("SourceBase", "RPGDescribe.txt") + ": " + sti(base);
			SetCharacterStat(chr, &tempTable, M_ENERGY_MAX, &goodText, "ToHumanModifier", 0);
			SetCharacterStat(chr, &tempTable, M_MTP_ENERGY_MAX, &goodText, "ToHumanModifierPercent", 0);
		break;
		case "critDamage":
			SetCharacterStatGroup(chr, &equipTable, BLADE_ITEM_TYPE + "_" + M_CRIT_DAMAGE, &text, &goodText, 1+CRIT_MTP);
			goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, GUN_ITEM_TYPE + "_" + M_CRIT_DAMAGE, &text, &goodText, 1+CRIT_MTP);
			if (!IsMusketer(chr)) break;
			goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, MUSKET_ITEM_TYPE + "_" + M_CRIT_DAMAGE, &text, &goodText, 1+CRIT_MTP);
		break;
		case "crit":
			base = GetBaseCritChance(chr);
			SetCharacterStatGroup(chr, &equipTable, BLADE_ITEM_TYPE + "_" + M_CRIT_CHANCE, &text, &goodText, base);
			goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, GUN_ITEM_TYPE + "_" + M_CRIT_CHANCE, &text, &goodText, base);
			if (!IsMusketer(chr)) break;
			goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, MUSKET_ITEM_TYPE + "_" + M_CRIT_CHANCE, &text, &goodText, base);
		break;
		case "critCharDefence":
			SetCharacterStat(chr, &equipTable, M_REDUCE_CRIT_DAMAGE, &goodText, "ToHumanModifierPercent", 0)
		break;
		case "CharDefence":
			SetCharacterStat(chr, &equipTable, M_REDUCE_DAMAGE, &goodText, "ToHumanModifierPercent", 0);
			if (GetAttributeFloat(&equipTable, RANGE + M_REDUCE_DAMAGE) > 0) goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, RANGE + M_REDUCE_DAMAGE, &text, &goodText, 0);
		break;
	}
}

// Добавляем в статы предмета модификаторы персонажа
void AddItemUICharacterModifiers(ref chr, ref result, ref stat, ref item)
{
	// используем куклу, чтобы обсчитать статы предмета так, будто он надет
	aref dummy;
	makearef(dummy, TEV.dummy);
	CopyAttributes(&dummy, chr);
	dummy.dummy = true;
	GiveItem2Character(&dummy, item.id);
	EquipCharacterbyItem(&dummy, item.id, true);
	CT_UpdateCashTables(&dummy);

	aref landTable = CT_GetTable(&dummy, CT_LAND);
	aref equipTable = CT_GetTable(&dummy, CT_EQUIP);
	aref sources, source;
	string modifier;
	float value;

	switch (GetAttributeName(stat))
	{
		case "reloadTime":
		{
			int time = makeint(1.0 / LAi_GunReloadSpeed(&dummy, item.groupId) + 0.5);
			modifier = item.groupId + "_" + M_RELOAD_SPEED;
			makearef(sources, equipTable.(modifier));
			sources.skill = 0.3*LAi_GetCharacterGunLevel(&dummy);
			result += xiStr("itemStatsModifiersTitle") + ": " + ToHumanNumber(time) + " " + xiStr("sec.");
			result += newStr() + " " +  newStr();
			SetCharacterStat(&dummy, &equipTable, modifier, result, "ToHumanModifierPercent", 0.0);
		}
		break;
		case "attack":
		{
			result += xiStr("itemStatsModifiersTitle") + ": ";
			result += newStr() + " ";
			if (item.groupID != MUSKET_ITEM_TYPE) LAi_BladeFencingType(&dummy, item.FencingType);
			SetUIAttackDamge(&dummy, item, result, &landTable, FAST_STRIKE);
			SetUIAttackDamge(&dummy, item, result, &landTable, FORCE_STRIKE);
			SetUIAttackDamge(&dummy, item, result, &landTable, ROUND_STRIKE);
			SetUIAttackDamge(&dummy, item, result, &landTable, BREAK_STRIKE);

			// JOKERBACKLOG подумать тут над выводом источников, пока что так сойдёт
		}
		break;
		case "gunDamage":
		{
			object tempTable;
			ApplyModifierAsAnother(&tempTable, equipTable, SHOT_STRIKE + "_" + M_DAMAGE, SHOT_STRIKE + "_" + M_DAMAGE);
			string ammoModifier = GetGunAmmoType(&dummy, item) + "_" + M_DAMAGE;
			ApplyModifierAsAnother(&tempTable, equipTable, SHOT_STRIKE + "_" + M_DAMAGE, ammoModifier);
			SetCharacterStatGroup(&dummy, &tempTable, SHOT_STRIKE + "_" + M_DAMAGE, "", result, 1.0);

			result += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(&dummy, equipTable, M_HEADSHOT_DAMAGE, "", result, (1.0+HEADSHOT_MTP));
		}
		break;
	}

	DeleteAttribute(&TEV, "dummy");
}

string GetGunAmmoType(ref chr, ref item)
{
	if (GetCharacterEquipByGroup(chr, item.groupId) == item.id)
	{
		string ammoType = LAi_GetCharacterBulletType(chr, item.groupId);
		if (IsBulletGrape(ammoType)) return GRAPESHOT;
		else return BULLET;
	}
	else if (IsBulletGrape(item.type.t1.bullet)) return GRAPESHOT;

	return BULLET;
}

void SetUIAttackDamge(ref chr, ref item, ref result, ref landTable, string strikeType)
{
	float mtp = 1+GetDamageMtp(&landTable, strikeType, item.groupId);
	string skillType = "melee";
	if (item.groupID == MUSKET_ITEM_TYPE) skillType = "range";
	float skillMtp = DamageSkillMtp(chr, skillType);
	result += GetConvertStr("ChrAttack"+strikeType, "ControlsNames.txt") + ": " + makeint(stf(item.attack.(strikeType).min) * mtp * skillMtp) + "-" + makeint(stf(item.attack.(strikeType).max) * mtp * skillMtp) + NewStr();
}

void SetCharacterStatGroup(ref chr, ref equipTable, string modifier, ref text, ref goodText, float base)
{
	float modifierBonus = GetAttributeFloat(&equipTable, modifier);
	float overallValue = modifierBonus + base;
	if (overallValue == 0) return;

	goodText += GetModifierName(modifier) + ": " + ToHumanPercent(overallValue);
	if (modifierBonus == 0) return;

	goodText += newStr() + " ";
	SetCharacterStat(chr, &equipTable, modifier, goodText, "ToHumanModifierPercent", 0);
}

void SetCharacterStat(ref chr, ref equipTable, string modifier, ref result, string formatter, float base)
{
	aref sources, source;
	makearef(sources, equipTable.(modifier));
	for (int i = 0; i < GetAttributesNum(sources); i++)
	{
		source = GetAttributeN(sources, i);
		string reason = GetAttributeName(source);
		result += GetHumanReadableReason(reason, chr) + ": " + call formatter(base+stf(GetAttributeValue(source))) + NewStr();
	}
}

// Пересчитываем статы-за-уровень в текущий бонус к стату.
// Например, 2хп за ранг здесь добавят 2*ранг к максимальному хп, с тем же названием источника
// Только для интерфейсного отображения
void _AddByRankModifierAsFlatValue(ref chr, ref rObject, string modifierFrom, string modifierTo)
{
	aref sources, source;
	makearef(sources, rObject.(modifierFrom));
	int sourcesQty = GetAttributesNum(sources);
	for (int i = 0; i < sourcesQty; i++)
	{
		source = GetAttributeN(sources, i);
		float value = stf(GetAttributeValue(source)) * (sti(chr.rank) - 1);
		if (value > 0.0) IncreaseModifierFromSourceDirect(rObject, modifierTo, value, GetAttributeName(source));
	}
}