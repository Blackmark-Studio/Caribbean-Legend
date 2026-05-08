// Здесь особенный файт в каюте

// Стартуем файт в каюте
void InitCabinFight(ref location, ref enemy, ref boardingObject)
{
	if (!BRD_IsOfficersFight(enemy, location)) return;
	if (CheckAttribute(enemy, "Situation") && bSeaCanGenerateShipSituation) return; // ситуации, в которых нет файта
	if (CheckAttribute(enemy, "BoardingFaith.CaptainPreferSuicide")) return;       // суицид капитана
	ChangeCharacterAddressGroup(pchar, location.id, "rld", "cabin_boarding_ally1");

	object enemyModels[2];
	object enemySoldierItems[1];
	GenerateCrew(enemy, "officer", &enemyModels);
	GenerateItemsForCharacter(enemy, ITEM_PACK_ELITE, &enemySoldierItems);

	object allyModels[2];
	object allySoldierItems[1];
	GenerateCrew(pchar, "soldier", &allyModels);
	GenerateItemsForCharacter(pchar, ITEM_PACK_ELITE, &allySoldierItems);

	BRDC_SpawnFighters(location, "ally", pchar, boardingObject, &allyModels, &allySoldierItems);
	BRDC_SpawnFighters(location, "enemy", enemy, boardingObject, &enemyModels, &enemySoldierItems);
}

// Закидываем в каюту бойцов на локаторы cabin_boarding
void BRDC_SpawnFighters(ref location, string type, ref captain, ref boardingObject, ref models, ref items)
{
	int locIdx = 2; // на первом локаторе капитаны
	int fighterIdx = 0;
	aref locators = GetAref(location, "locators.rld");
	while (true)
	{
		string locator = "cabin_boarding_" + type + locIdx;
		if (!CheckAttribute(&locators, locator)) break; // закончились слоты

		ref fighter = BRDC_GetNextFighter(boardingObject, type, fighterIdx, captain, models, items);
		if (fighter == nullptr) break; // закончились бойцы

		ChangeCharacterAddressGroup(fighter, location.id, "rld", locator);
		fighterIdx++;
		locIdx++;
	}
}

ref BRDC_GetNextFighter(ref boardingObject, string type, int fighterIdx, ref captain, ref models, ref items)
{
	if (type == "ally")
	{
		int chrIdx = GetOfficersIndex(captain, fighterIdx+1);
		if (chrIdx > -1) return GetCharacter(chrIdx);
	}

	if (type == "ally" && sti(boardingObject.attacker < 1)) return nullptr; // совсем нет матросов

	ref genOfficer = GetCharacter(NPC_GenerateCharacter("GenChar_", models[fighterIdx].model, "man", models[fighterIdx].ani, sti(pchar.rank), sti(captain.nation), 0, false, "officer"));
	genOfficer.id = "GenChar_" + genOfficer.index;

	// Если совсем нет абордажников, будет Алонсо
	if (fighterIdx == 0 && type == "ally")
	{
		genOfficer.model = "Alonso";
		genOfficer.name = GetCharacterName("Alonso");
		genOfficer.lastname = "";
		genOfficer.CantLoot = true;
	}

	SetNPCEquip(genOfficer, items);
	LAi_NPC_Equip(genOfficer, sti(genOfficer.rank), true, true);
	LAi_SetWarriorType(genOfficer);
	genOfficer.AboardFantom = true;
	if (type == "ally") 
	{
		// За нас чуть более бойцовые матросы
		ForceAutolevel(genOfficer, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
		LAi_group_MoveCharacter(genOfficer, LAI_GROUP_PLAYER);
	}
	else
	{
		// А против нас элитные офицеры, но могут быть вовсе не бойцы по профессии
		ForceAutolevel(genOfficer, GEN_TYPE_OFFICER, GEN_ELITE, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.5);
		LAi_group_MoveCharacter(genOfficer, LAI_GROUP_BRDENEMY);
	}
	return genOfficer;
}
