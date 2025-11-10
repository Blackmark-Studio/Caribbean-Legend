// Здесь таблица со скиллами и пиратес, кроме статусных эффектов типа алкоголя и перевеса
void CT_UpdateCommonTable(ref chr)
{
	DeleteAttribute(chr, "ct."+CT_COMMON);
	bool bHero = false;
	bool bHealth = false;
	bool bOfficer = false;
	bool bCompanion = false;
	bool bEnableEffects = false;
	bool bAdmiralHat = false;
	aref table = CT_GetTable(chr, CT_COMMON);
	aref equipTable = CT_GetTable(chr, CT_EQUIP);
	int healthImpact = 0;
	if (IsMainCharacter(chr))
	{
		bHero = true;
		bHealth = MOD_SKILL_ENEMY_RATE > 1;
		Log_TestInfo("Обновили кэш-таблицу ГГ");
	}
	else bHealth = CheckAttribute(chr, "OfficerImmortal");
	
	if (bHealth) healthImpact = GetHealthNum(chr) - 6;
	if (CheckAttribute(chr, "Payment")) bOfficer = true;
	if (IsCompanion(chr) && GetRemovable(chr) && !bHero) bCompanion = true;


	// bEnableEffects = bHero || bCompanion || bOfficer;
	bEnableEffects = LAi_IsArmed(chr);
	table.flags.bHero = bHero;
	table.flags.bCompanion = bCompanion;
	table.flags.bEnableEffects = bEnableEffects;
	if (bHero && GetCharacterEquipByGroup(pchar, HAT_ITEM_TYPE) == "hat5")
	{
		bAdmiralHat = true;
		table.flags.bAdmiralHat = bAdmiralHat;
	}

	if (bCompanion) Log_TestInfo("Обновили кэш-таблицу компаньона: " + chr.name);

	CT_SetSpecial(chr, &table, &equipTable, SPECIAL_S, bHero, healthImpact);
	CT_SetSpecial(chr, &table, &equipTable, SPECIAL_P, bHero, healthImpact);
	CT_SetSpecial(chr, &table, &equipTable, SPECIAL_E, bHero, healthImpact);
	CT_SetSpecial(chr, &table, &equipTable, SPECIAL_C, bHero, healthImpact);
	CT_SetSpecial(chr, &table, &equipTable, SPECIAL_I, bHero, healthImpact);
	CT_SetSpecial(chr, &table, &equipTable, SPECIAL_A, bHero, healthImpact);
	CT_SetSpecial(chr, &table, &equipTable, SPECIAL_L, bHero, healthImpact);

	healthImpact *= 5; // домножаем для личных
	CT_SetSkill(chr, &table, &equipTable, SKILL_F_LIGHT,    bHero, healthImpact, bEnableEffects, true);
	CT_SetSkill(chr, &table, &equipTable, SKILL_FENCING,    bHero, healthImpact, bEnableEffects, true);
	CT_SetSkill(chr, &table, &equipTable, SKILL_F_HEAVY,    bHero, healthImpact, bEnableEffects, true);
	CT_SetSkill(chr, &table, &equipTable, SKILL_PISTOL,     bHero, healthImpact, bEnableEffects, true);
	CT_SetSkill(chr, &table, &equipTable, SKILL_FORTUNE,    bHero, healthImpact, bEnableEffects, true);
	CT_SetSkill(chr, &table, &equipTable, SKILL_LEADERSHIP, bHero, healthImpact, bEnableEffects, true);
	CT_SetSkill(chr, &table, &equipTable, SKILL_SNEAK,      bHero, healthImpact, bEnableEffects, true);

	healthImpact = 0; // на корабельные не влияет
	CT_SetSkill(chr, &table, &equipTable, SKILL_COMMERCE,  bHero, healthImpact, bEnableEffects, false);
	CT_SetSkill(chr, &table, &equipTable, SKILL_ACCURACY,  bHero, healthImpact, bEnableEffects, false);
	CT_SetSkill(chr, &table, &equipTable, SKILL_CANNONS,   bHero, healthImpact, bEnableEffects, false);
	CT_SetSkill(chr, &table, &equipTable, SKILL_SAILING,   bHero, healthImpact, bEnableEffects, false);
	CT_SetSkill(chr, &table, &equipTable, SKILL_REPAIR,    bHero, healthImpact, bEnableEffects, false);
	CT_SetSkill(chr, &table, &equipTable, SKILL_GRAPPLING, bHero, healthImpact, bEnableEffects, false);
	CT_SetSkill(chr, &table, &equipTable, SKILL_DEFENCE,   bHero, healthImpact, bEnableEffects, false);

	CT_SetNavyPenalty(chr, &table, bHero, bCompanion);
	if (bHero) CT_UpdateCashTablesAdmiral(&table);
	RunTableCallbacks(chr, CT_COMMON, &equipTable, &table);
}

void CT_SetSkill(ref chr, aref table, aref itemsTable, string skillName, bool bHero, int healthImpact, bool bEnableEffects, bool bSelfSkill)
{
	aref modificator;
	string modifierName = SKILL_TYPE + skillName;
	makearef(modificator, table.(modifierName));

	if (!CheckAttribute(chr, "Skill."+skillName))
	{
		table.(modifierName) = 1;
		modificator.base = 1;
		return;
	}

	int skillN = sti(chr.Skill.(skillName));
	
	if (!bEnableEffects)
	{
		table.(modifierName) =	skillN;
		return;
	}
	
	modificator.base = skillN;
	if (bSelfSkill) 
	{
		skillN += healthImpact;
		modificator.health = healthImpact;
	}
	
	// Экипировка
	int equipN = 0;
	equipN += GetAttributeInt(itemsTable, modifierName);

	if (equipN > 0)
	{
		aref equipModifier;
		makearef(equipModifier, itemsTable.(modifierName));
		CopyAttributesSafe(modificator, equipModifier);
	}
	skillN += equipN;

	table.(modifierName) = skillN;
	if (bSelfSkill || !bHero) return;
	SetAttribute(table, modifierName + ".officer.backup", skillN);
	CT_SetOfficerOverride(&table, &skillName);
}

void CT_SetSpecial(ref chr, aref table, aref itemsTable, string skillName, bool bHero, int healthImpact)
{
	aref modificator;
	string modifierName = SPECIAL_TYPE + skillName;
	makearef(modificator, table.(modifierName));
	if (!CheckAttribute(chr, "SPECIAL."+skillName))
	{
		table.(modifierName) = 3;
		modificator.base = 3;
		return;
	}

	int equipN = 0;
	int skillN = sti(chr.SPECIAL.(skillName));
	modificator.base = skillN;

	// Здоровье
	skillN += healthImpact;
	modificator.health = healthImpact;

	// Экипировка
	equipN += GetAttributeInt(itemsTable, modifierName);
	if (equipN > 0)
	{
		aref equipModifier;
		makearef(equipModifier, itemsTable.(modifierName));
		CopyAttributesSafe(modificator, equipModifier);
	}

	skillN += equipN;
	table.(modifierName) = skillN;
}
