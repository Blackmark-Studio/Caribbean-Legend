#include "characters\generator\patterns.c"
#include "characters\generator\helpers.c"
#include "characters\generator\difficulty.c"
#include "characters\generator\generator.h"
#include "characters\generator\hero_init_helpers.c"
#include "characters\generator\virtual_officers.c"

void InitChrRebalance(ref chr)
{
	int chrtype = GetAttributeInt(chr, "personality.chrtype");
	int powerLvl = GetAttributeInt(chr, "personality.powerLvl");
	int oldPowerLvl = powerLvl;
	bool randomPirates = AttributeIsTrue(chr, "personality.randomPirates");
	float selfToShip = GetAttributeFloat(chr, "personality.selfToShip");
	int playerRank = sti(pchar.rank);
	int targetRank = playerRank;

// костыль для квестовых персонажей, им нужен минимальный ранг
	if (CheckAttribute(chr, "personality.adaptiveRankMin"))
	{
		targetRank = func_max(sti(chr.personality.adaptiveRankMin), playerRank);
		if (powerLvl == GEN_BY_RANK) powerLvl = GEN_GetPowerLvlByRank(targetRank);
	}
	else if (CheckAttribute(chr, "personality.adaptiveRank")) // костыль для персонажей с адаптивной сложностью, им от ранга выдаем разряд
	{
		int adaptiveRank = sti(chr.personality.adaptiveRank);
		if (adaptiveRank < playerRank) adaptiveRank = playerRank;
		targetRank = GEN_GetTargetRankFromFixed(adaptiveRank);
		powerLvl = func_max(GEN_GetPowerLvlByRank(targetRank), powerLvl);
	}
	else
	{
		targetRank += GEN_GetPowerLevelRankOffset(powerLvl); // иначе добавляем ранг от разряда
		if (targetRank < 1) targetRank = 1;
	}
	

	GEN_ModifyCaptainsRankByShip(chr, &targetRank, playerRank, &powerLvl);
	// trace("Итого powerLvl: " + chr.id + " с " + oldPowerLvl + " на " + powerLvl + ". Целевой ранг: " + targetRank + ", а фиксированный был: " + GetAttributeInt(chr, "personality.adaptiveRank"));
	ChrRebalance(chr, targetRank, chrtype, powerLvl, randomPirates, selfToShip)
}

void GEN_ModifyCaptainsRankByShip(ref chr, int targetRank, int playerRank, int powerLvl)
{
	if (CheckAttribute(chr, "personality.adaptiveRankMin")) return; // этих и так уже бафнули
	int shipClass = GetCharacterShipClass(chr);
	if (shipClass > 6) return; // лодочники или не капитаны
	int newRank = 32 - shipClass*5 + shipClass;

	targetRank = func_max(makeint(newRank), playerRank);
	int tempRank = targetRank;
	int tempLvl = powerLvl;
	powerLvl = func_max(GEN_GetPowerLvlByRank(tempRank), tempLvl);
}

void ChrRebalance(ref chr, int targetRank, int chrtype, int powerLvl, bool randomPirates, float selfToShip)
{
	chr.BusyRebalancing = true; // отключаем уведомления о новых перках и отвязываем рандом от даты
	chr.personality.chrtype = chrtype;
	chr.personality.powerLvl = powerLvl;
	chr.personality.randomPirates = randomPirates;
	chr.personality.selfToShip = selfToShip;

	GEN_SetArchetype(chr, chrtype);
	if (randomPirates) GEN_SetPirates(chr, powerLvl);

	aref skills;
	makearef(skills, chr.skill);
	ClearCharacterExpRate(chr);
	int score = GetPersonGenScore(targetRank); // задаем примерный уровень скиллов

	GEN_SetSkills(chr, &skills, score, selfToShip, targetRank); // выдаем скиллы
	GEN_ModifyMusketers(chr);         // мушкетеров слегка заостряем на пистолетах
	GEN_AddSkillsFromSpecials(chr, &skills);   // добавляем от пиратес, чтобы было похоже на правду
	GEN_LimitSkills(chr, chrtype);    // потолочим
	GEN_BuyPerks(chr, false);         // бахаем перки
	// SetRankFromSkill(chr);            // меняем ранг
	chr.rank = targetRank;
	GEN_OverrideAppearance(chr, -1);  // внешка

	DeleteAttribute(chr, "BusyRebalancing");
	if (chrtype == GEN_TYPE_OFFICER) 
	{
		// chr.quest.OfficerPrice    = (11 + 2*sti(chr.rank))*(150 + MOD_SKILL_ENEMY_RATE*20) + rand(5)*10;
		// chr.quest.OfficerLowPrice = makeint(sti(chr.quest.OfficerPrice)/1.5 + 0.5);
		chr.quest.officertype = ArcheTypeToOfficerType(chr.Personality.mainArchetype);
		chr.quest.officertype_2 = "";
	}

	DeleteAttribute(&TEV, "QCharAutolevel." + chr.id);
	GEN_ApplyDifficulty(chr, chrtype, powerLvl);
	if (CheckAttribute(chr, "personality.hasCrew")) GiveCaptainOfficers(chr, sti(chr.personality.HasCrew));
	else CT_UpdateCashTables(chr);

	SetFantomHP(chr);                 // хпшечку в макс
	SetEnergyToCharacter(chr);        // энергию в макс
	UpdateNpcFightAI(chr);            // апдейт всех желаний стрелять, бить определенными ударами и т. п.
}

void GEN_ModifyMusketers(ref chr, )
{
	if (!IsMusketer(chr)) return;

	int bonus = GEN_SmoothBonusByRank(GEN_MUSKETERS_OFFSET, sti(pchar.rank));
	AddToAttributeInt(chr, "skill." + SKILL_PISTOL, bonus);
	AddToAttributeInt(chr, "skill." + SKILL_FENCING, -bonus);
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

void GEN_SetPirates(ref chr, int powerLvl)
{
	int base, random;
	int _p = 0;
	int _i = 0;
	int _r = 0;
	int _a = 0;
	int _t = 0;
	int _e = 0;
	int _s = 0;
	GEN_GetPowerLevelPirates(powerLvl, &base, &random);
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

void GEN_LimitSkills(ref chr, int chrtype)
{
	if (chrtype != GEN_TYPE_OFFICER) return;

	chr.skill.sailing = iClamp(1, 75, sti(chr.skill.sailing));
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
		RemoveAllPerksNoCash(chr);
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
	else templateVar = GEN_RandLock(chr, 99, "");

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
			perkPoints.ship = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.ship), &primaryTemplate, &secondaryTemplate, &restTemplate, "001");
		break;
		case "fighter": // боец с корабельным хобби
			perkPoints.self = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.self), &primaryTemplate, &utilityTemplate, &NullObj, "000010001001001010101");
			perkPoints.ship = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.ship), &secondaryTemplate, &restTemplate, &NullObj, "0");
		break;
		case "manager": // корабельщик с бойцовским хобби
			perkPoints.self = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.self), &secondaryTemplate, &utilityTemplate, &NullObj, "001010101010101");
			perkPoints.ship = GenPerksForPoints(chr, &chrPerks, sti(perkPoints.ship), &primaryTemplate, &restTemplate, &NullObj, "0");
		break;
	}


	SetFreePerkPoints(chr, sti(perkPoints.self), "self");
	SetFreePerkPoints(chr, sti(perkPoints.ship), "ship");
	SetAttribute(chr, "perks.FreePoints_self_exp", sti(perkPoints.self_left));
	SetAttribute(chr, "perks.FreePoints_ship_exp", sti(perkPoints.ship_left));
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
	if (CheckAttribute(primaryTemplate, "free")) return points;

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
				perkName = GetPerkFromTemplate(chr, chrPerks, primaryTemplate, dayLock, i);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, secondaryTemplate, dayLock, i);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, resTemplate, dayLock, i);
			break;
			case 1:
				perkName = GetPerkFromTemplate(chr, chrPerks, secondaryTemplate, dayLock, i);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, primaryTemplate, dayLock, i);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, resTemplate, dayLock, i);
			break;
			case 2:
				perkName = GetPerkFromTemplate(chr, chrPerks, resTemplate, dayLock, i);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, secondaryTemplate, dayLock, i);
				if (perkName == "") perkName = GetPerkFromTemplate(chr, chrPerks, primaryTemplate, dayLock, i);
			break;
		}
		sequenceIdx++;

		if (perkName == "Utility") perkName = GetPerkFromTemplate(chr, chrPerks, &secondaryTemplate, dayLock, i);
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
		SetCharacterPerkNoCash(chr, perkName, false);
		points -= perkPrice;
	}
	return points;
}

// Получаем следующий перк по шаблону
string GetPerkFromTemplate(ref chr, ref chrPerks, ref template, bool dayLock, int index)
{
	if (!CheckAttribute(template, "list")) return "";

	aref perkList;
	makearef(perkList, template.list);
	int templateSize = GetAttributesNum(perkList);
	int perk_index = 0;

	if (CheckAttribute(template, "random")) 
	{
		perk_index = GEN_RandLock(chr, templateSize - 1, index);
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

void GEN_OverrideAppearance(ref chr, int forceIcon)
{
	string path;
	if (CheckAttribute(chr, "animal")) return; // животным не даём иконок
	if (forceIcon >= 0)
	{
		path = "Interfaces\\LE\\Battle_interface\\Archetypes\\" + forceIcon + ".tga";
		SendMessage(chr, "lss", MSG_CHARACTER_EX_MSG, "SetArchetypeTexture", path);
		return;
	}

	int chrType = GetAttributeInt(chr, "personality.chrtype");
	int powerLvl = GetAttributeInt(chr, "personality.powerLvl");

	string icon = "";
	if (GetCharacterShipType(chr) != SHIP_NOTUSED ) icon = "6";
	else if (powerLvl == GEN_BOSS) icon = "8";
	else if (powerLvl == GEN_MINIBOSS) icon = "7";
	
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
	path = "Interfaces\\LE\\Battle_interface\\Archetypes\\" + icon + ".tga";
	SendMessage(chr, "lss", MSG_CHARACTER_EX_MSG, "SetArchetypeTexture", path);
}

// Устанавливаем среднее значение скиллов для генерации от ранга ГГ или адаптивного ранга
int GetPersonGenScore(int targetRank)
{
	int middleByRank = 6 + makeint(targetRank*3.0);

	return iClamp(3, 100, middleByRank);
}

void GEN_SetSkills(ref chr, ref skills, int score, float selfToShip, int targetRank)
{
	int i;
	string skillName;
	int baseBonus =  GEN_SmoothBonusByRank(ARCHETYPE_M_BONUS, targetRank);
	int primaryBonus = baseBonus + GEN_RandLock(chr, GEN_SmoothBonusByRank(ARCHETYPE_M_RANDBONUS, targetRank), "");
	int secondaryBonus = GEN_SmoothBonusByRank(ARCHETYPE_S_BONUS, targetRank);
	float selfMtp = selfToShip * 2;
	float shipMtp = (1.0-selfToShip) * 2;
	if (selfMtp > 1) selfMtp = pow(selfMtp, 0.75);
	else if (shipMtp > 1) shipMtp = pow(shipMtp, 0.75);
	int selfScore = makeint(score * selfMtp);
	int shipScore = makeint(score * shipMtp);
	for (i=1; i<8; i++)
	{
		skillName = GetSkillNameByTRIdx("SelfType", i);
		GEN_SetSkill(chr, skills, targetRank, skillName, selfScore, baseBonus, primaryBonus, secondaryBonus);
	}

	for (i=1; i<8; i++)
	{
		skillName = GetSkillNameByTRIdx("ShipType", i);
		GEN_SetSkill(chr, skills, targetRank, skillName, shipScore, baseBonus, primaryBonus, secondaryBonus);
	}
}

void GEN_SetSkill(ref chr, ref skills, int targetRank, string skillName, int score, int baseBonus, int primaryBonus, int secondaryBonus)
{
	score += GEN_SmoothBonusByRank(GEN_RandLock(chr, GEN_CHAOS_VALUE, "") - GEN_RandLock(chr, GEN_CHAOS_VALUE, "") - GEN_RandLock(chr, GEN_CHAOS_VALUE, "") * 2, targetRank);
	score += GEN_GetArchetypeBonus(skillName, chr.Personality.mainArchetype, primaryBonus, baseBonus);
	score += GEN_GetArchetypeBonus(skillName, chr.Personality.secondaryArchetype, secondaryBonus, secondaryBonus);
	skills.(skillName) = score;
}

// Имитируем прокачку навыков в соответствии с пиратес, типа чел быстрее качался имея подходящие характеристики
void GEN_AddSkillsFromSpecials(ref chr, ref skills)
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

		float mtp = Bring2Range(0.8, 1.2, 30.0, 100.0, makefloat(bonus));
		skills.(skillName) = iClamp(3, 100, makeint(stf(skills.(skillName)) * mtp));
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
		case GEN_ARCHETYPE_FREE:
			return 0;
		break;
	}
	return -makeint(bonus * 0.2);
}

// Приводим типы офицеров к архетипам должностей, т. к. теперь они равноценны
// Разделяем файтеров по владению оружием 
void GEN_SetArchetype(ref chr, int chrtype)
{
	string mainArchetype = chr.personality.mainArchetype;
	string secondaryArchetype = chr.personality.secondaryArchetype;

		if (chrtype == GEN_TYPE_ENEMY || chrtype == 2) //JOKERTODO здесь двойка из-за наличия раньше типа капитана, её можно удалить со следующим патчем, требующим новой игры
		{
			if (mainArchetype == GEN_ARCHETYPE_RANDOM) mainArchetype = GEN_GetArchetypeByWeapon(chr);
			if (secondaryArchetype == GEN_ARCHETYPE_RANDOM) secondaryArchetype = GEN_GetArchetypeByIndex(rand(GEN_MAX_ARCHETYPES-1));
		}
		else if (chrtype == GEN_TYPE_OFFICER)
		{
			int a, b;
			SetTwoRandomNums(GEN_MAX_ARCHETYPES, &a, &b, "");
			if (mainArchetype == GEN_ARCHETYPE_RANDOM) mainArchetype = GEN_GetArchetypeByIndex(a);
			if (secondaryArchetype == GEN_ARCHETYPE_RANDOM) secondaryArchetype = GEN_GetArchetypeByIndex(b);
		}

	chr.Personality.mainArchetype = mainArchetype;
	chr.Personality.secondaryArchetype = secondaryArchetype;
	chr.Personality.TemplateVar = GEN_RandLock(chr, 99, "");
}

string GEN_GetArchetypeByWeapon(ref chr)
{
	if (IsMusketer(chr)) return GEN_ARCHETYPE_GUNMAN; // с мушкетом всегда стрелок

	string gunId = GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE);
	// if (gunId != "" && PercentChance(50)) return GEN_ARCHETYPE_GUNMAN; // с пистолетом половина стрелков

	// остальные получают боевой тип по оружию в руках
	string bladeId = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
	if (bladeId == "" && HasSubStr(chr.model, "mush_")) return GEN_ARCHETYPE_GUNMAN; // мушкетера дабл-чекаем по модельке
	if (bladeId == "")
	{
		trace("missing weapon for: " + chr.id);
		return GEN_ARCHETYPE_PEASANT;
	}

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
	int seed = rand(2);
	if (seed == 0) return       GEN_ARCHETYPE_DUELIST;
	else if (seed == 1) return  GEN_ARCHETYPE_PIRATE;
	else if (seed == 2) return  GEN_ARCHETYPE_SOLDIER;
}