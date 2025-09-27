
// Вывести таблицы персонажа
void CT_DumpTable(ref chr, string tableName)
{
	aref table;
	makearef(table, chr.ct.(tableName));
	DumpAttributes(table);
}

// Получить таблицу в сыром виде
ref CT_GetTable(ref chr, string tableName)
{
	aref result;
	makearef(result, chr.ct.(tableName));
	return &result;
}

// Получить интовое значение из таблицы
int CT_GetInt(ref chr, string tableName, string skillName)
{
	return GetAttributeInt(chr, "ct." + tableName + "." + skillName);
}

void CT_SetNavyPenalty(ref chr, ref table, bool bHero, bool bCompanion)
{
	int sailSkill = GetAttributeInt(table, SKILL_SAILING);
	int needSkill = GetShipClassNavySkill(GetCharacterShipClass(chr));
	int diff = func_max(0, needSkill - sailSkill);

	if (CheckAttribute(chr, "NoNavyPenalty")) diff = 0;
	if (!bHero && !bCompanion) diff = 0;

	int navyPen = 0;
	if (diff > 0) navyPen = makeint(makefloat(diff) / 10.0 + 0.9);

	table.navyPenaltySpecial = navyPen;
	table.navyPenaltySkill = diff;

	if(CheckAttribute(chr,"systeminfo.tutorial.navigator"))
	{
		pchar.quest.Tutorial_Navigator.win_condition.l1 = "EnterToSea";
		pchar.quest.Tutorial_Navigator.function = "Tutorial_Navigator";
	}
}

// Записываем скилл ГГ-адмирала и меняем итог, если он больше
void CT_SetCompanionOverride(ref chr, ref admiralTable, ref companionTable)
{
	for (int i=1; i<=7; i++)
	{
		string skillName = GetSkillNameByTRIdx("ShipType", i);
		int compSkillValue = sti(companionTable.(skillName));
		int admiralSkillValue = sti(admiralTable.(skillName).officer.backup);
		int diff = admiralSkillValue - compSkillValue;
		companionTable.(skillName).admiral = diff;
		companionTable.(skillName).admiral.backup = compSkillValue;
		companionTable.flags.admiral = true;
		if (diff < 0) continue;

		companionTable.(skillName) = admiralSkillValue;
	}

	CT_SetNavyPenalty(chr, companionTable, false, true);
}

// Шляпы нет, отменяем эффекты
void CT_RemoveCompanionOverride(ref chr, ref companionTable)
{
	if (!CheckAttribute(companionTable, "flags.admiral")) return;

	DeleteAttribute(companionTable, "flags.admiral");
	for (int i=1; i<=7; i++)
	{
		string skillName = GetSkillNameByTRIdx("ShipType", i);
		companionTable.(skillName) = companionTable.(skillName).admiral.backup;
		DeleteAttribute(companionTable, skillName+".admiral");
		if (skillName != SKILL_SAILING) continue;
	}

	CT_SetNavyPenalty(chr, companionTable, false, true);
}

// Записываем скилл офицера и меняем итог, если он больше
void CT_SetOfficerOverride(ref table, string skillName)
{
	string jobName = GetJobBySkillName(skillName);
	int iOfficer = sti(pchar.Fellows.Passengers.(jobName));
	int pcharSKill = sti(table.(skillName).officer.backup);
	int officerSkill = 0;
	if (iOfficer > -1) officerSkill = GetSkillWithEffects(&Characters[iOfficer], skillName);

	int diff = func_max(0, officerSkill - pcharSKill);
	if (diff > 0) table.(skillName) = officerSkill;
	else table.(skillName) = pcharSKill;

	table.(skillName).officer = diff;
}

// Процессим зависимость компаньонов от ГГ засчёт адмиральской шляпы
void CT_UpdateCashTablesAdmiral(ref admiralTable)
{
	bool bHat = AttributeIsTrue(&admiralTable, "flags.bAdmiralHat");

	for(int i=1; i<COMPANION_MAX; i++)
	{
		int cn = GetCompanionIndex(pchar,i);
		if (cn < 0) continue;
		ref chr = &Characters[cn];
		aref companionTable = CT_GetTable(chr, CT_COMMON);
		CT_RemoveCompanionOverride(chr, &companionTable);
		if (!bHat) continue;

		CT_SetCompanionOverride(chr, &admiralTable, &companionTable);
	}
}

void CT_UpdateCashTablesFellow(ref chr)
{
	CT_UpdateCashTables(chr);
	if (IsMainCharacter(chr)) return;

	aref pcharTable = CT_GetTable(pchar, CT_COMMON);
	for (int i=1; i<=7; i++)
	{
		string skillName = GetSkillNameByTRIdx("ShipType", i);
		CT_SetOfficerOverride(&pcharTable, skillName);
	}
	CT_SetNavyPenalty(pchar, &pcharTable, true, false);
}

void CT_MergeTables(ref tableA, ref tableB)
{
	for (int i = 0; i < GetAttributesNum(tableB); i++)
	{
		aref modifierB = GetAttributeN(tableB, i);
		string modifierName = GetAttributeName(modifierB);
		float value = stf(GetAttributeValue(modifierB));
		AddToAttributeFloat(tableA, modifierName, value);

		aref modifierA;
		makearef(modifierA, tableA.(modifierName));
		CopyAttributes(modifierA, modifierB);
	}
}