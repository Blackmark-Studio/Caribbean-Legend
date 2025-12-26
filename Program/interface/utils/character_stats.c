// Здесь разруливаем всплывашки по характеристикам персонажа и предметов в разрезе персонажа

void SetCharacterStatsTooltip(ref chr, string statName, string header, string text, string badText, string goodText)
{
	float base;
	aref equipTable = CT_GetTable(chr, CT_EQUIP);

	switch (statName)
	{
		case "life":
			text += newStr() + " " + newStr() + " ";
			base = GetCharacterBaseHPValue(chr);
			base += GetAttributeFloat(&equipTable, M_HP_PER_RANK) * (sti(chr.rank) - 1);
			text += GetConvertStr("SourceBase", "RPGDescribe.txt") + ": " + fts(base, 0);
			SetCharacterStat(chr, &equipTable, M_HP_MAX, &goodText, "ToHumanNumber", 0)
			SetCharacterStat(chr, &equipTable, M_MTP_HP_MAX, &goodText, "ToHumanPercent", 0);
		break;
		case "energy":
			text += newStr() + " " + newStr() + " ";
			base = GetCharacterBaseEnergy(chr);
			base += GetAttributeFloat(&equipTable, M_ENERGY_PER_RANK) * (sti(chr.rank) - 1);
			text += GetConvertStr("SourceBase", "RPGDescribe.txt") + ": " + fts(base, 0);
			SetCharacterStat(chr, &equipTable, M_ENERGY_MAX, &goodText, "ToHumanNumber", 0)
			SetCharacterStat(chr, &equipTable, M_MTP_ENERGY_MAX, &goodText, "ToHumanPercent", 0);
		break;
		case "critDamage":
			SetCharacterStatGroup(chr, &equipTable, BLADE_ITEM_TYPE + "_" + M_CRIT_DAMAGE, &text, &goodText, 1+CRIT_MTP);
			goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, GUN_ITEM_TYPE + "_" + M_CRIT_DAMAGE, &text, &goodText, 1+CRIT_MTP);
			if (!IsMusketer(chr)) break;
			goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, MUSKET_ITEM_TYPE + "_" + M_CRIT_DAMAGE, &text, &goodText, 1+CRIT_MTP);
		break;
		case "crit":
			base = GetBaseCritChance(chr);
			SetCharacterStatGroup(chr, &equipTable, BLADE_ITEM_TYPE + "_" + M_CRIT_CHANCE, &text, &goodText, base);
			goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, GUN_ITEM_TYPE + "_" + M_CRIT_CHANCE, &text, &goodText, base);
			if (!IsMusketer(chr)) break;
			goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, MUSKET_ITEM_TYPE + "_" + M_CRIT_CHANCE, &text, &goodText, base);
		break;
		case "critCharDefence":
			SetCharacterStat(chr, &equipTable, M_REDUCE_CRIT_DAMAGE, &goodText, "ToHumanPercent", 0)
		break;
		case "CharDefence":
			SetCharacterStat(chr, &equipTable, M_REDUCE_DAMAGE, &goodText, "ToHumanPercent", 0);
			if (GetAttributeFloat(&equipTable, RANGE + M_REDUCE_DAMAGE) > 0) goodText += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, &equipTable, RANGE + M_REDUCE_DAMAGE, &text, &goodText, 0);
		break;
	}
}

// Добавляем в статы предмета модификаторы персонажа
void AddItemUICharacterModifiers(ref chr, string result, ref stat, ref item)
{
	// используем куклу, чтобы обсчитать статы предмета так, будто он надет
	aref dummy;
	makearef(dummy, TEV.dummy);
	CopyAttributes(&dummy, chr);
	EquipCharacterbyItem(&dummy, item.id);
	CT_UpdateCashTables(&dummy);

	aref landTable = CT_GetTable(&dummy, CT_LAND);
	aref equipTable = CT_GetTable(&dummy, CT_EQUIP);
	aref sources, source;
	string modifier;
	float value;

	switch (GetAttributeName(stat))
	{
		case "reloadTime": // JOKERTODO время перезарядки не совсем сходится, можно ещё покрутить
		{
			modifier = item.groupId + "_" + M_RELOAD_SPEED;
			makearef(sources, equipTable.(modifier));
			value = GetAttributeFloat(stat, "rawValue");
			sources.skill = 0.3*LAi_GetCharacterGunLevel(chr);
			value *= 1.0 - (GetReloadSpeed(&landTable, item.groupId) - 1.0);
			result += xiStr("itemStatsModifiersTitle") + ": " + ToHumanNumber(makeint(value + 0.5)) + " " + xiStr("sec.");
			result += newStr() + " " +  newStr();
			SetCharacterStat(chr, &equipTable, modifier, result, "ToHumanPercent", 0.0);
		}
		break;
		case "attack":
		{
			result += xiStr("itemStatsModifiersTitle") + ": ";
			result += newStr() + " ";
			if (item.groupID != MUSKET_ITEM_TYPE) LAi_BladeFencingType(&dummy, item.FencingType);
			SetUIAttackDamge(&dummy, item, result, &landTable, FAST_STRIKE);
			SetUIAttackDamge(&dummy, item, result, &landTable, FORCE_STRIKE);
			SetUIAttackDamge(&dummy, item, result, &landTable, ROUND_STRIKE);
			SetUIAttackDamge(&dummy, item, result, &landTable, BREAK_STRIKE);

			// JOKERTODO подумать тут над выводом источников, пока что так сойдёт
		}
		break;
		case "gunDamage":
		{
			SetCharacterStatGroup(chr, equipTable, SHOT_STRIKE + "_" + M_DAMAGE, "", result, 1.0);
			result += newStr() + " " + newStr() + " ";
			SetCharacterStatGroup(chr, equipTable, M_HEADSHOT_DAMAGE, "", result, (1.0+HEADSHOT_MTP));
		}
		break;
	}

	DeleteAttribute(&TEV, "dummy");
}

void SetUIAttackDamge(ref chr, ref item, string result, ref landTable, string strikeType)
{
	float mtp = 1+GetDamageMtp(&landTable, strikeType, item.groupId);
	string skillType = "melee";
	if (item.groupID == MUSKET_ITEM_TYPE) skillType = "range";
	float skillMtp = DamageSkillMtp(chr, skillType);
	result += GetConvertStr("ChrAttack"+strikeType, "ControlsNames.txt") + ": " + makeint(stf(item.attack.(strikeType).min) * mtp * skillMtp) + "-" + makeint(stf(item.attack.(strikeType).max) * mtp * skillMtp) + NewStr();
}

void SetCharacterStatGroup(ref chr, ref equipTable, string modifier, string text, string goodText, float base)
{
	float modifierBonus = GetAttributeFloat(&equipTable, modifier);
	float overallValue = modifierBonus + base;
	if (overallValue == 0) return;

	goodText += GetModifierName(modifier) + ": " + ToHumanPercent(overallValue);
	if (modifierBonus == 0) return;

	goodText += newStr() + " ";
	SetCharacterStat(chr, &equipTable, modifier, &goodText, "ToHumanPercent", 0);
}

void SetCharacterStat(ref chr, ref equipTable, string modifier, string result, string formatter, float base)
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