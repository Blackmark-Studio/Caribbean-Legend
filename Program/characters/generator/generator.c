#include "characters\generator\patterns.c"
#include "characters\generator\helpers.c"
#include "characters\generator\generator.h"
#include "characters\generator\hero_init_helpers.c"

void InitChrRebalance(ref chr, int chrtype, int powerLevel, bool genPirates, float selfOverShip)
{
	chr.BusyRebalancing = true; // отключаем уведомления о новых перках и отвязываем рандом от даты
	chr.personality.type = chrtype;
	chr.personality.powerLvl = powerLevel;

	GEN_SetArchetype(chr, chrtype);
	if (genPirates) GEN_SetPirates(chr, powerLevel);
	Log_TestInfo("rebalance: " + chr.id + " " + chr.Personality.mainArchetype + " " + chr.Personality.secondaryArchetype + " " + powerLevel + " " + chrtype);

	ClearCharacterExpRate(chr);
	int score = GetPersonGenScore(chr, powerLevel); // задаем примерный уровень скиллов
	GEN_SetSkills(chr, score);        // выдаем скиллы
	GEN_AddSkillsFromSpecials(chr);   // добавляем от пиратес, чтобы было похоже на правду
	GEN_LimitSkills(chr);             // потолочим
	GEN_BuyPerks(chr, false);         // бахаем перки
	SetRankFromSkill(chr);            // меняем ранг
	SetFantomHP(chr);                 // хпшечку пересчитываем
	GEN_AddSkillsToCaptains(chr, chrtype); // добавляем бонус капитанов от офицеров
	GEN_OverrideAppearance(chr); // внешка

	// chr.quest.OfficerPrice    = (11 + 2*sti(chr.rank))*(150 + MOD_SKILL_ENEMY_RATE*20) + rand(5)*10;
	// chr.quest.OfficerLowPrice = makeint(sti(chr.quest.OfficerPrice)/1.5 + 0.5);
	DeleteAttribute(chr, "BusyRebalancing");
	if (chrtype == GEN_TYPE_OFFICER) 
	{
		chr.quest.officertype = ArcheTypeToOfficerType(chr.Personality.mainArchetype);
		chr.quest.officertype_2 = "";
	}

	CT_UpdateEquipTable(chr);
	CT_UpdateCommonTable(chr);
	CT_UpdateLandTable(chr);
}

void InitHeroRebalance(ref chr, float selfOverShip, string mainA, string secondaryA)
{
	chr.personality.MainArchetype = mainA;
	chr.personality.secondaryArchetype = secondaryA;
	InitChrRebalance(chr, GEN_TYPE_HERO, GEN_MINIBOSS, false, 0.6);
}

// временная заплатка для диалогов и прочей логики на officertype
string ArcheTypeToOfficerType(string archetype)
{
	switch (archetype)
	{
		case GEN_ARCHETYPE_DUELIST: return  "Fighter"; break;
		case GEN_ARCHETYPE_PIRATE:  return  "Fighter"; break;
		case GEN_ARCHETYPE_GUNMAN:  return  "Fighter"; break;
		case GEN_ARCHETYPE_SOLDIER: return  "Fighter"; break;
		case GEN_ARCHETYPE_PEASANT: return  "Fighter"; break;
	}
	return archetype;
}

void GEN_AddSkillsToCaptains(ref chr, int chrtype)
{
	RemoveChrModifier(chr, "officer");
	if (chrtype != GEN_TYPE_CAPTAIN) return;
	GEN_SetCharHiredOfficers(chr, true);
}

void GEN_SetPirates(ref chr, int powerLevel)
{
	int base, random;
	int _p = 0;
	int _i = 0;
	int _r = 0;
	int _a = 0;
	int _t = 0;
	int _e = 0;
	int _s = 0;
	GEN_GetPowerLevelPirates(powerLevel, &base, &random);
	GEN_GetArchetypePirates(chr, &_p, &_i, &_r, &_a, &_t, &_e, &_s);

	SetSPECIAL(chr,
				(iClamp(1, 10, base + rand(random) + _p)),
				(iClamp(1, 10, base + rand(random) + _i)),
				(iClamp(1, 10, base + rand(random) + _r)),
				(iClamp(1, 10, base + rand(random) + _a)),
				(iClamp(1, 10, base + rand(random) + _t)),
				(iClamp(1, 10, base + rand(random) + _e)),
				(iClamp(1, 10, base + rand(random) + _s))
			);
}

void GEN_LimitSkills(ref chr)
{
	chr.SKILL_SAILING = iClamp(1, 75, sti(chr.SKILL_SAILING));
}

void GEN_BuyPerks(ref chr, bool continueLeveling)
{
	if (CheckAttribute(chr, "animal")) return; // животным не даём

	object temp, NullObj;
	aref chrPerks, perkPoints, personality;
	makearef(perkPoints, temp.perkPoints);
	makearef(personality, chr.Personality);

	if (continueLeveling) {
		perkPoints.self = GetFreePerkPoints(chr, "self");
		perkPoints.ship = GetFreePerkPoints(chr, "ship");
	}
	else
	{
		GEN_SummPerkPoints(chr, &perkPoints);
		DeleteAttribute(chr, "perks.list");
	}

	string mainArchetype = personality.mainArchetype;
	string secondaryArchetype = personality.secondaryArchetype;
	makearef(chrPerks, chr.perks.list);

	aref primaryTemplate, secondaryTemplate, restTemplate, eggheadTemplate, utilityTemplate;
	makearef(primaryTemplate, temp.primaryTemplate);
	makearef(secondaryTemplate, temp.secondaryTemplate);
	makearef(restTemplate, temp.resTemplate);
	makearef(utilityTemplate, temp.utilityTemplate);
	makearef(eggheadTemplate, temp.eggheadTemplate);

	int templateVar;
	if (CheckAttribute(chr, "Personality.TemplateVar")) templateVar = sti(personality.TemplateVar);
	else templateVar = rand(2);

	primaryTemplate.seed   = templateVar;
	eggheadTemplate.seed   = templateVar;
	secondaryTemplate.seed = templateVar;
	restTemplate.seed      = templateVar;
	utilityTemplate.seed   = templateVar;

	FillPersonTemplate(&primaryTemplate, mainArchetype);
	FillPersonTemplate(&secondaryTemplate, secondaryArchetype);
	FillPersonTemplateUtility(&utilityTemplate);
	FillPersonTemplateLeftovers(&restTemplate, mainArchetype, secondaryArchetype);

	switch(GEN_GetArchetypeCategory(mainArchetype, secondaryArchetype))
	{
		case "egghead": // яйцеголовый, оба занятия корабельные
			FillPersonTemplatePeasant(&eggheadTemplate);
			perkPoints.self = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.self), &eggheadTemplate, &utilityTemplate, &NullObj, "00010001001001010101");
			perkPoints.ship = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.ship), &primaryTemplate, &secondaryTemplate, &restTemplate, "001012021201");
		break;
		case "fighter": // боец с корабельным хобби
			perkPoints.self = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.self), &primaryTemplate, &utilityTemplate, &NullObj, "000010001001001010101");
			perkPoints.ship = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.ship), &secondaryTemplate, &restTemplate, &NullObj, "001001001001010101");
		break;
		case "manager": // корабельщик с бойцовским хобби
			perkPoints.self = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.self), &secondaryTemplate, &utilityTemplate, &NullObj, "001010101010101");
			perkPoints.ship = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.ship), &primaryTemplate, &restTemplate, &NullObj, "001011011101");
		break;
	}


	SetFreePerkPoints(chr, sti(perkPoints.self), "self");
	SetFreePerkPoints(chr, sti(perkPoints.ship), "ship");
}

string GEN_GetArchetypeCategory(string mainArchetype, string secondaryArchetype)
{
	string mainCategory = GetPatternType(mainArchetype);
	string secondaryCategory = GetPatternType(secondaryArchetype);

	if (mainCategory == secondaryCategory)  return "egghead";
	if (mainCategory == "personal") return "fighter";
	return "manager";
}

// Идём по набранным шаблонам для персонажа в соответствии с последовательностью и покупаем перки
int GenPerksForPoints(ref chr, ref chrPerks, int points, ref primaryTemplate, ref secondaryTemplate, ref resTemplate, string sequence)
{
	int sequenceSize = strlen(sequence);
	int sequenceIdx = 0;
	string perkName;
	bool dayLock = !CheckAttribute(chr, "BusyRebalancing");
	for(int i=0; true ; i++)
	{
		if (sequenceIdx == sequenceSize) sequenceIdx = 0; // начинаем последовательность заново

		switch(sti(strcut(sequence, sequenceIdx, sequenceIdx)))
		{
			case 0:
				perkName = GetPerkFromTemplate(chr, chrPerks, primaryTemplate, dayLock);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, secondaryTemplate, dayLock);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, resTemplate, dayLock);
			break;
			case 1:
				perkName = GetPerkFromTemplate(chr, chrPerks, secondaryTemplate, dayLock);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, primaryTemplate, dayLock);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, resTemplate, dayLock);
			break;
			case 2:
				perkName = GetPerkFromTemplate(chr, chrPerks, resTemplate, dayLock);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, secondaryTemplate, dayLock);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, primaryTemplate, dayLock);
			break;
		}
		sequenceIdx++;

		if (perkName == "Utility") perkName = GetPerkFromTemplate(chr, chrPerks, &secondaryTemplate, dayLock);
		if (perkName == "") break; // закончились перки в шаблонах
		if (perkName == "GotAlready") continue; // уже есть перк, цикл продолжится со следующим индексом
		if (perkName == "Disabled") continue;  // нельзя взять перк, цикл продолжится со следующим индексом

		int perkPrice = GetPerkPrice(perkName);

		if (points < perkPrice) break; // закончились очки

		// if(!CheckAttribute(chr, "BusyRebalancing")) 
		// {
		// 	string perkLocName = GetConvertStr(perkName, "AbilityDescribe.txt");
		// 	if (perkLocName == "") perkLocName = GetConvertStr(perkName, "PerksReworkedAbilityDescribe.txt");

		// 	PerksReworkedNotification(StringFromKey("personality_19", person.name, perkLocName), GetMessagePortrait(chr));
		// }
		chrPerks.(perkName) = true;
		points -= perkPrice;
	}
	return points;
}

// Получаем следующий перк по шаблону
string GetPerkFromTemplate(ref chr, ref chrPerks, ref template, bool dayLock)
{
	if (!CheckAttribute(template, "list")) return "";

	aref perkList;
	makearef(perkList, template.list);
	int templateSize = GetAttributesNum(perkList);
	int perk_index = 0;

	if (CheckAttribute(template, "random")) 
	{
		perk_index = DateRandom(templateSize - 1, "templateGen");
	}

	if (templateSize == 0) return "";

	string perkName = GetAttributeName(GetAttributeN(perkList, perk_index));

	// уже есть перк, для автолевелинга
	if (CheckAttribute(chrPerks, perkName))
	{
		DeleteAttribute(&perkList, perkName);
		return "GotAlready"; // возвращаемся к последовательности, убрав перк из шаблона
	}

	if (CheckPerkFilter(chr, perkName)) 
	{ 
		DeleteAttribute(&perkList, perkName);
		return "Disabled"; // возвращаемся к последовательности, убрав перк из шаблона
	}

	perkName = GetPerkOrRequired(chrPerks, perkName);
	DeleteAttribute(&perkList, perkName);
	return perkName;
}

void GEN_OverrideAppearance(ref chr)
{
	if (CheckAttribute(chr, "animal")) return; // животным не даём иконок
	int chrType = GetAttributeInt(chr, "personality.type");
	int powerLevel = GetAttributeInt(chr, "personality.powerLvl");
	
	string icon = "";
	if (chrType == GEN_TYPE_CAPTAIN) icon = "6";
	else if (powerLevel == GEN_BOSS) icon = "8";
	else if (powerLevel == GEN_MINIBOSS) icon = "7";
	
	if (icon == "")
	{
		string mainArchetype = GEN_GetArchetype(chr, 0);
		switch (mainArchetype)
		{
			case GEN_ARCHETYPE_DUELIST: icon = "2"; break;
			case GEN_ARCHETYPE_PIRATE:  icon = "4"; break;
			case GEN_ARCHETYPE_GUNMAN:  icon = "3"; break;
			case GEN_ARCHETYPE_SOLDIER: icon = "1"; break;
		}
	}

	if (icon == "") icon = "5";
	string path = "Interfaces\\LE\\Battle_interface\\Archetypes\\" + icon + ".tga";
	SendMessage(chr, "lss", MSG_CHARACTER_EX_MSG, "SetArchetypeTexture", path);
}

// Проверяем, надо ли взять другой перк, чтобы взять этот и возвращаем соответствующий
string GetPerkOrRequired(ref chrPerks, string perkName)
{
	if (!CheckAttribute(&ChrPerksList, "list." + perkName + ".condition")) return perkName;

	aref conditions;
	makearef(conditions, ChrPerksList.list.(perkName).condition);

	for(int i=0; i < GetAttributesNum(conditions); i++)
	{
		string tempPerkName = GetAttributeName(GetAttributeN(conditions, i));
		if (!CheckAttribute(chrPerks, tempPerkName)) return GetPerkOrRequired(chrPerks, tempPerkName);
	}

	return perkName;
}

// Устанавливаем среднее значение скиллов для генерации от среднего для ГГ
int GetPersonGenScore(ref chr, int powerLevel)
{
	int result = makeint(GetMiddleMainSkill()); // от 10 до 100
	result += GEN_GetPowerLevelSkillBonus(powerLevel);
	result += iClamp(0, makeint(GEN_CHAOS_VALUE*1.5), rand(GEN_CHAOS_VALUE) + rand(GEN_CHAOS_VALUE)); // рандомный бонус

	return iClamp(10, 100, result);
}

void GEN_SetSkills(ref chr, int score)
{
	int baseBonus =  GEN_SmoothBonusByRank(ARCHETYPE_M_BONUS);
	int primaryBonus = baseBonus + rand(GEN_SmoothBonusByRank(ARCHETYPE_M_RANDBONUS));
	int secondaryBonus = GEN_SmoothBonusByRank(ARCHETYPE_S_BONUS);
	for (int i=1; i<15; i++)
	{
		int tempScore = score + rand(GEN_CHAOS_VALUE) - rand(GEN_CHAOS_VALUE) - rand(GEN_CHAOS_VALUE) * 2;
		string skillName = GetSkillNameByIdx(i);
		tempScore += GEN_GetArchetypeBonus(skillName, chr.Personality.mainArchetype, primaryBonus, baseBonus);
		tempScore += GEN_GetArchetypeBonus(skillName, chr.Personality.secondaryArchetype, secondaryBonus, secondaryBonus);
		chr.skill.(skillName) = tempScore;
	}
}

// Имитируем прокачку навыков в соответствии с пиратес, типа чел быстрее качался имея подходящие характеристики
void GEN_AddSkillsFromSpecials(ref chr)
{
	int bonus;
	for (int i=1; i<15; i++)
	{
		string skillName = GetSkillNameByIdx(i);

		switch (skillName)
		{
				case SKILL_F_LIGHT:
						bonus = GetSpecialBase(chr, SPECIAL_A) * 9 + GetSpecialBase(chr, SPECIAL_P) * 1;
				break;
				case SKILL_FENCING:
						bonus = GetSpecialBase(chr, SPECIAL_S) * 6 + GetSpecialBase(chr, SPECIAL_A) * 4;
				break;
				case SKILL_F_HEAVY:
						bonus = GetSpecialBase(chr, SPECIAL_S) * 9 + GetSpecialBase(chr, SPECIAL_E) * 1;
				break;
				case SKILL_PISTOL:
						bonus = GetSpecialBase(chr, SPECIAL_A) * 5 + GetSpecialBase(chr, SPECIAL_L) * 5;
				break;
				case SKILL_FORTUNE:
						bonus = GetSpecialBase(chr, SPECIAL_L) * 10;
				break;
				case SKILL_LEADERSHIP:
						bonus = GetSpecialBase(chr, SPECIAL_I) * 1 + GetSpecialBase(chr, SPECIAL_C) * 9;
				break;
				case SKILL_COMMERCE:
						bonus = GetSpecialBase(chr, SPECIAL_I) * 8 + GetSpecialBase(chr, SPECIAL_C) * 2;
				break;
				case SKILL_ACCURACY:
						bonus = GetSpecialBase(chr, SPECIAL_P) * 8 + GetSpecialBase(chr, SPECIAL_L) * 2;
				break;
				case SKILL_CANNONS:
						bonus = GetSpecialBase(chr, SPECIAL_I) * 6 + GetSpecialBase(chr, SPECIAL_S) * 4;
				break;
				case SKILL_SAILING:
						bonus = GetSpecialBase(chr, SPECIAL_P) * 2 + GetSpecialBase(chr, SPECIAL_I) * 8;
				break;
				case SKILL_REPAIR:
						bonus = GetSpecialBase(chr, SPECIAL_P) * 2 + GetSpecialBase(chr, SPECIAL_E) * 8;
				break;
				case SKILL_GRAPPLING:
						bonus = GetSpecialBase(chr, SPECIAL_A) * 7 + GetSpecialBase(chr, SPECIAL_I) * 3;
				break;
				case SKILL_DEFENCE:
						bonus = GetSpecialBase(chr, SPECIAL_C) * 5 + GetSpecialBase(chr, SPECIAL_E) * 5;
				break;
				case SKILL_SNEAK:
						bonus = GetSpecialBase(chr, SPECIAL_P) * 5 + GetSpecialBase(chr, SPECIAL_L) * 5;
				break;
		}

		int result = iClamp(0, GEN_SmoothBonusByRank(GEN_PIRATES_MAX_IMPACT), makeint(bonus / GEN_PIRATES_IMPACT_LEVEL));
		chr.skill.(skillName) = iClamp(1, 100, sti(chr.skill.(skillName)) + result);
	}
}

// Чем больше чел крут в своей основной профе, тем слабее будет в остальных
int GEN_GetArchetypeBonus(string skillName, string type, int bonus, int secondBonus)
{
	switch(type)
	{
		case GEN_ARCHETYPE_TREASURER: if (skillName == SKILL_COMMERCE)  return bonus; break;
		case GEN_ARCHETYPE_BOATSWAIN: if (skillName == SKILL_GRAPPLING) return bonus; break;
		case GEN_ARCHETYPE_NAVIGATOR: if (skillName == SKILL_SAILING)   return bonus; break;
		case GEN_ARCHETYPE_DOCTOR:    if (skillName == SKILL_DEFENCE)   return bonus; break;
		case GEN_ARCHETYPE_CARPENTER: if (skillName == SKILL_REPAIR)    return bonus; break;
		case GEN_ARCHETYPE_CANNONER:
			if (skillName == SKILL_ACCURACY)  return bonus;
			if (skillName == SKILL_CANNONS)   return bonus;
		break;
		case GEN_ARCHETYPE_PIRATE:
			if (skillName == SKILL_FENCING) return bonus; 
			if (skillName == SKILL_PISTOL)  return secondBonus; 
		break;
		case GEN_ARCHETYPE_DUELIST:
			if (skillName == SKILL_F_LIGHT) return bonus;
			if (skillName == SKILL_FENCING) return makeint(secondBonus * 0.6);
			if (skillName == SKILL_PISTOL)  return makeint(secondBonus * 0.4);
		break;
		case GEN_ARCHETYPE_SOLDIER:
			if (skillName == SKILL_F_HEAVY) return bonus;
			if (skillName == SKILL_FENCING) return makeint(secondBonus * 0.8);
			if (skillName == SKILL_PISTOL)  return makeint(secondBonus * 0.2);
		break;
		case GEN_ARCHETYPE_GUNMAN:
			if (skillName == SKILL_PISTOL)  return bonus;
			if (skillName == SKILL_FENCING) return secondBonus;
		break;
		case GEN_ARCHETYPE_PEASANT:
			return 0; 
		break;
	}
	return -(bonus / 2);
}

// Приводим типы офицеров к архетипам должностей, т. к. теперь они равноценны
// Разделяем файтеров по владению оружием 
void GEN_SetArchetype(ref chr, int chrtype)
{
	if (chrtype == GEN_TYPE_HERO) return;

	string mainArche;
	string secondaryArche;

		if (chrtype == GEN_TYPE_ENEMY || chrtype == GEN_TYPE_CAPTAIN)
		{
			mainArche = GEN_GetArchetypeByWeapon(chr);
			secondaryArche = GEN_GetArchetypeByIndex(rand(GEN_MAX_ARCHETYPES-1));
		}
		else if (chrtype == GEN_TYPE_OFFICER)
		{
			int a, b;
			SetTwoRandomNums(GEN_MAX_ARCHETYPES, &a, &b, "");
			mainArche = GEN_GetArchetypeByIndex(a);
			secondaryArche = GEN_GetArchetypeByIndex(b);
		}

	chr.Personality.mainArchetype = mainArche;
	chr.Personality.secondaryArchetype = secondaryArche;
	chr.Personality.TemplateVar = rand(2);
}

string GEN_GetArchetypeByWeapon(ref chr)
{
	if (IsMusketer(chr)) return GEN_ARCHETYPE_GUNMAN; // с мушкетом всегда стрелок

	string gunId = GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE);
	if (gunId != "" && PercentChance(50)) return GEN_ARCHETYPE_GUNMAN; // с пистолетом половина стрелков

	// остальные получают боевой тип по оружию в руках
	string bladeId = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
	if (bladeId == "") return GEN_ARCHETYPE_PEASANT;

	ref blade = ItemsFromID(bladeId);
	switch (blade.fencingType)
	{
			case SKILL_F_LIGHT: return GEN_ARCHETYPE_DUELIST; break;
			case SKILL_FENCING: return GEN_ARCHETYPE_PIRATE;  break;
			case SKILL_F_HEAVY: return GEN_ARCHETYPE_SOLDIER; break;
	}
}

string GEN_GetArchetypeByIndex(int index)
{
	switch (index)
	{
		case 0: return GEN_ARCHETYPE_TREASURER; break;
		case 1: return GEN_ARCHETYPE_CARPENTER; break;
		case 2: return GEN_ARCHETYPE_BOATSWAIN; break;
		case 3: return GEN_ARCHETYPE_CANNONER;  break;
		case 4: return GEN_ARCHETYPE_NAVIGATOR; break;
		case 5: return GEN_ARCHETYPE_DOCTOR;    break;
	}

	// для индекса 6 дальше рандом
	int seed = rand(3);
	if (seed == 0) return       GEN_ARCHETYPE_DUELIST;
	else if (seed == 1) return  GEN_ARCHETYPE_PIRATE;
	else if (seed == 2) return  GEN_ARCHETYPE_GUNMAN;
	else if (seed == 3) return  GEN_ARCHETYPE_SOLDIER;
}