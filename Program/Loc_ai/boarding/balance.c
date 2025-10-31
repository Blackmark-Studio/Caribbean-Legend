void BRD_InjectBalanceWithGenerator(ref attacker, ref defender, int attackerCrew, int defenderCrew)
{
	// инициализируем общую хранилку всей чушни
	DeleteAttribute(&TEV, "boarding");

	// соберем возможных персонажей-подменышей
	aref playerPerkChars, enemyPerkChars;
	makearef(playerPerkChars, TEV.boarding.perkChars.player);
	makearef(enemyPerkChars, TEV.boarding.perkChars.brdenemy);
	// пока что исходим из того,что игрок всегда атакующий
	BRD_FillPerkChars(attacker, defender, &playerPerkChars);
	BRD_FillPerkChars(defender, attacker, &enemyPerkChars);

	if (GetOfficersPerkUsing(attacker, "BoardingPrepare")) TEV.boarding.attacker.elixir = true;
	if (GetOfficersPerkUsing(defender, "BoardingPrepare")) TEV.boarding.defender.elixir = true;

	// посчитаем преимущества в рангах
	SetRankOffsets(attacker, defender, attackerCrew, defenderCrew);
}

void SetRankOffsets(ref attacker, ref defender, int attackerCrew, int defenderCrew)
{
	float crewMtp = 1.2;
	float atk = pow(attackerCrew, crewMtp);
	float def = pow(defenderCrew, crewMtp);
	float result = (atk - def) / (atk + def + 1);

	bool attackerTstantsa = IsCharacterEquippedArtefact(attacker, "indian_5");
	bool defenderTstantsa = IsCharacterEquippedArtefact(attacker, "indian_5");
	if (result < 0 && attackerTstantsa) result -= result * 0.3;
	else if (result > 0 && defenderTstantsa) result -= result * 0.3;
	
	// оффест от -10 до 10
	int attackerRank = makeint(10 * result);
	int defenderRank = -attackerRank;
	TEV.boarding.attacker = attackerCrew;
	TEV.boarding.defender = defenderCrew;
	TEV.boarding.attacker.rank = attackerRank;
	TEV.boarding.defender.rank = defenderRank;
	if (attackerTstantsa) TEV.boarding.attacker.tsantsa = true;
	if (defenderTstantsa) TEV.boarding.defender.tsantsa = true;
}

void BRD_InjectPerks(ref chr, int curIdx, ref perkChars, ref location, bool giveElixir)
{
	bool replaced = false;
	if (giveElixir) GiveItem2Character(chr, "potion2");

	// сначала пробуем компаньона
	if (CheckAttribute(perkChars, "companion") && CheckAttribute(location, "UpDeckType"))
	{
		ref companion = GetCharacter(sti(perkChars.companion));
		ChangeAttributesFromCharacter(chr, companion, false);
		DeleteAttribute(chr, "payment");
		chr.PersonalityCloneType = "companion";
		chr.PersonalityCloneIdx = companion.index;
		chr.CantLoot = true;
		DeleteAttribute(perkChars, "companion");
		replaced = true;
	}

	// затем боцмана только на верхнюю палубу
	if (!replaced && CheckAttribute(perkChars, "boatswain") && CheckAttribute(location, "UpDeckType"))
	{
		ref boatswain = GetCharacter(sti(perkChars.boatswain));
		if (!IsOfficer(boatswain)) // и так уже абордажник
		{
			ChangeAttributesFromCharacter(chr, boatswain, false);
			DeleteAttribute(chr, "payment");
			chr.PersonalityCloneType = "boatswain";
			chr.PersonalityCloneIdx = boatswain.index;
			chr.CantLoot = true;
			replaced = true;
		}
		DeleteAttribute(perkChars, "boatswain");
	}

	// затем все остальные
	if (!replaced && GetAttributesNum(perkChars > 0))
	{
		string charType = GetAttributeName(GetAttributeN(perkChars, 0));

		if (HasSubStr(charType, "bruteforce"))
		{
			BRD_UpgradeToPerkChar(chr, "bruteforce");
		}
		else if (HasSubStr(charType, "ambuscade"))
		{
			BRD_UpgradeToPerkChar(chr, "ambuscade");
		}

		chr.PersonalityCloneType = charType;
		DeleteAttribute(perkChars, charType);
		replaced = true;
	}

	if (replaced) CT_UpdateCashTables(chr);
}

void BRD_FillPerkChars(ref attacker, ref defender, ref perkChars)
{
	if (IsMainCharacter(attacker) && CheckAttribute(defender, "CoordinatedCharIdx"))
	{
		perkChars.companion = defender.CoordinatedCharIdx;
	}

	if (IsMainCharacter(attacker) && CheckOfficersPerk(attacker, "Involvement"))
	{
		int boatswainIdx = sti(pchar.Fellows.Passengers.boatswain);
		if (boatswainIdx > 0) perkChars.boatswain = boatswainIdx;
	}

	if (CheckOfficersPerk(attacker, "BruteForce"))
	{
		perkChars.bruteForce_1;
		perkChars.bruteForce_2;
	}

	if (CheckOfficersPerk(attacker, "Ambuscade"))
	{
		perkChars.Ambuscade_1;
		perkChars.Ambuscade_2;
	}
}

void BRD_InjectBalance(ref chr, int offsetRank, ref boardingObject, ref location)
{
	string mark = "";
	if (CheckAttribute(chr, "PersonalityCloneType")) mark = chr.PersonalityCloneType;
	if (CheckAttribute(chr, "CaptanId") || CheckAttribute(chr, "PersonalityCloneIdx"))
	{
		SetAttribute(boardingObject, location.id + "." + chr.chr_ai.group + "." + chr.id, "cap|" + chr.rank + "|" + chr.personality.powerLvl + "|" + mark);
		return;
	}

	int targetRank = sti(pchar.rank) + offsetRank;
	ForceAdaptivelevel(chr, targetRank, GEN_TYPE_ENEMY, GEN_BY_RANK, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);

	SetAttribute(boardingObject, location.id + "." + chr.chr_ai.group + "." + chr.id, targetRank + "|" + chr.rank + "|" + chr.personality.powerLvl + "|" + mark);
}

void BRD_UpgradeToPerkChar(ref chr, string perkName)
{
	if (perkName == "bruteforce")
	{
		GiveItem2Character(chr, "topor_04");
		GiveItem2Character(chr, "cirass1");
		EquipCharacterByItem(chr, "topor_04");
		EquipCharacterByItem(chr, "cirass1");
		chr.model = BRD_FindModelFromPerk(chr, "bruteforce");
	}
	else if (perkName == "ambuscade")
	{
		GiveItem2Character(chr, "blade_39");
		EquipCharacterByItem(chr, "blade_39");
		GiveItem2Character(chr, "cirass6");
		EquipCharacterByItem(chr, "cirass6");
		GiveItem2Character(chr, "pistol6");
		EquipCharacterByItem(chr, "pistol6");
		chr.model = BRD_FindModelFromPerk(chr, "ambuscade");
	}
}

string BRD_FindModelFromPerk(ref chr, string perkName)
{
	
	if (HasSubStr(chr.model, "sold_")) return chr.model; // заплатка для солдат
	if (HasSubStr(chr.model, "Skel"))  return chr.model; // заплатка для скелетов
	object models;
	if (perkName == "bruteForce")
	{
		models.mercen_24 = true;
		models.mercen_25 = true;
		models.mercen_26 = true;
		models.mercen_28 = true;
		models.mercen_29 = true;
		models.mercen_30 = true;
		models.citiz_51 = true;
		models.citiz_52 = true;
	}
	else if (perkName == "ambuscade")
	{
		models.questCaptain = true;
		models.garke = true;
		models.officer_6 = true;
		models.officer_4 = true;
		models.officer_2 = true;
		models.citiz_30 = true;
		models.citiz_10 = true;
	}

	return GetRandomAttrName(&models);
}